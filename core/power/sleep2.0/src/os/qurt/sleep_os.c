/*==============================================================================
  FILE:         sleep_os.c

  OVERVIEW:     This file provides the sleep task and OS-specific
                functionality for the processors with Qurt running on them.

  DEPENDENCIES: sleepOS_mainTask() is the entry point to the lowest-priority
                thread processing.

                Copyright (c) 2011-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/os/qurt/sleep_os.c#2 $
$DateTime: 2014/10/20 15:13:48 $
==============================================================================*/
#include <stdlib.h>
#include "sleepi.h"
#include "rcinit.h"
#include "qurt.h"
#include "npa.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "synthRegistry.h"
#include "timer.h"
#include "utimer.h"
#include "sleep_config.h"
#include "CoreIni.h"
#include "sleep_npa_scheduler.h"
#include "sleep_os.h"
#include "sleep_osi.h"
#include "sleep_os_misc.h"
#include "sleep_idle_plugin.h"
#include "sleep_target.h"
#include "sleep_solver.h"
#include "lookup_table_solver.h"
#include "rpmclient.h"
#include "sleep_stats.h"
#include "sleep_statsi.h"
#include "DDIClock.h"
#include "sleep_utils.h"
#include "HALhwio.h"
#include "HALsleep_hwio.h"

#ifdef USLEEP_ISLAND_MODE_ENABLE
#include "uSleepi.h"
#include "uSleep_util.h"
#endif

/*==============================================================================
                                  DEFINES
 =============================================================================*/
/* Size of main sleep task stack */
#define SLEEP_STACK_SIZE      2560

/* Sleep task priority, (needs to be lowest in the system) */
#define SLEEP_TASK_PRI        254

/* Size of PMI handler task stack */
#define SLEEP_PMI_STACK_SIZE  2048

/* PMI handler task priority */
#define SLEEP_PMI_TASK_PRI    8   /* as per OS team's suggestion */

/* PMI interupt ID and signal mask used to register the OS signal
 * that will be triggered as part of the APCR bringup sequence. */
#define SLEEP_PMI_ID          0
#define SLEEP_PMI_MASK        (1 << 0)

/* Max number of characters in the full path to the sleep ini file. */
#define MAX_INI_PATH_LEN      64

/* Macro to check if any interrupt is pending at L2Vic.
 *
 * On QDSP6 V4 and above, the L2 Interrupt Controller is attached to INT31
 * of QDSP6'es IPEND register. All User configurable interrupts in the system
 * are attached ot L2 VIC. This makes it sufficient to check for L2 MSB 
 */
#define IPEND_IS_MSB_SET(ipend_status)  ((ipend_status) & (1 << 31))

/*==============================================================================
                          INTERNAL TYPE DEFINITIONS
 =============================================================================*/
/**
 * sleep_idle_entry_ptr_type
 *
 * @brief Type definition for function pointer to sleep behavior when 
 *        processor goes idle.
 */
typedef uint32 (*sleep_idle_entry_ptr_type)(void);

/**
 * sleep_handles
 *
 * @brief Main sleep structure for various node and device handles used 
 *        during the current sleep cycle
 */
typedef struct sleep_handles_s
{
  /* Handle used to query the /core/cpu/wakeup node */
  npa_query_handle  wakeup_node_query_handle;

  /* Handle used to query the /sleep/max_duration node */
  npa_query_handle max_duration_node_query_handle;

  /* Handle used to query the /core/cpu/latency node */
  npa_query_handle  latency_node_query_handle;

  /* Handle used to query the /sleep/lpr node */
  npa_query_handle  sleep_lpr_query_handle;

  /* Handle used to query the /clk/cpu resource */
  npa_query_handle  cpu_clk_freq_query_handle;

  /* DAL Client of Clock driver for requesting cpu frequency during Sleep */
  DalDeviceHandle   *dal_clk_handle;
}sleep_handles;

/**
 * sleep_state
 *
 * @brief Main sleep state strucutre used for current sleep cycle data        
 */
typedef struct sleep_state_s
{
  /* The synthLPRM to notify if the sleep duration changes.
   * This is the output mode of the solver */
  sleep_synth_lprm *selected_synthLPRM;

  /* The hard deadline (expected sleep exit time) in absolute ticks. */
  uint64 hard_deadline;

  /* The soft deadline (hint of next wakeup) in absolute ticks. */
  uint64 soft_deadline;

  /* The deadline in absolute ticks based on non deferrable timer expiry.*/ 
  uint64 timer_deadline;

  /* Solver input object containing various restrictions for a given
   * sleep cycle. */
  sleep_solver_input solver_input;

  /* Object containing output from Sleep solver based on various
   * input restrictions. */
  sleep_solver_output solver_output;

  /* Object containing various statistics related information from
   * the last complete sleep cycle.*/
  sleepStats_input cycle_stats;

  /* Flag to avoid unnecessary execution of Sleep exit path logic 
   *
   * This flag is useful in two scenarios:
   * 1. Sleep was bailed due to one of the many restrictions.
   * 2. Target(Q6) woke up from APCR based low power modes and by the time
   *    control comes to Sleep task, exit logic is already executed from
   *    IST context. We don't need to execute it again.
   *
   * Must be set to TRUE if we were to enter solver based low power modes
   * at idle time and to FALSE while executing exit logic.
   */
  boolean execute_sleep_exit_path;

  /* Flag to indicate if processor is running in sleep context. */
  boolean processor_in_stm;

}sleep_state;

/*==============================================================================
                           FORWARD DECLARATIONS
 =============================================================================*/
uint32 sleepOS_performLPM(void);
uint32 sleepOS_holdoffNoMode(void);
uint32 sleepOS_SWFI(void);
void sleepOS_performLPMExit(void);
uint32 sleepOS_uSleepPerform(void) USLEEP_CODE_SECTION;

void sleepHoldoff_registerRCinitCompletionEvent(void);
static void sleepOS_pmiHandler(void *context) USLEEP_CODE_SECTION;

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
/* Stores target specific config */
extern sleep_target_config g_sleepTargetConfig;

/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
/* Global sleep state that contains various peices of data used in the current sleep cycle */
static sleep_state g_sleepState = {0};

/* Limit sleep time to force a periodic wakeup for debug/bringup purposes.
 * To use, set to a non-zero value representing the number of ticks of sleep
 * duration. */
static volatile uint32 g_sleepForceWakeupTimeForDebug = (0);

/* Various node and device handles */
static sleep_handles g_sleepHandles;

/* Boolean that indicates whether we should enter any low power modes or not.
 *
 * This variable provides a simpler mechanism to disable low power modes
 * for developing/testing features that are not quite dependent on low 
 * power modes. Note that in the production code, it will be set so that
 * low power modes are always allowed.
 */
#ifdef FEATURE_DISABLE_SLEEP_MODES
volatile boolean g_sleepAllowLowPowerModes = FALSE;
#else
volatile boolean g_sleepAllowLowPowerModes = TRUE;
#endif

/*==============================================================================
                   INTERNAL VARIABLES IN ISLAND SECTION
 =============================================================================*/
/* Pointer to use as the entry point when the system is idle.
 * This pointer is controlled by the /sleep/idle/plugin node. */
static sleep_idle_entry_ptr_type g_idleEntryPtr USLEEP_DATA_SECTION = NULL; 

/* Function pointer to use for PMI exit handling. The pointer is set based on
 * if the system is in normal operational or island mode */
static sleep_PMI_handler_ptr_type g_PMIFncPtr USLEEP_DATA_SECTION = NULL;

/* Main sleep task stack must be in TCM since task is also located in TCM. To
 * do that we have to statically declare an array in island section */
static uint8 g_sleepTaskStack[SLEEP_STACK_SIZE] USLEEP_DATA_SECTION;

/* PMI handler task stack must be in TCM since task is also located in TCM. To
 * do that we have to statically declare an array in island section */
static uint8 g_sleepPMITaskStack[SLEEP_PMI_STACK_SIZE] USLEEP_DATA_SECTION;

/* Signal that the PMI task waits on from the OS to begin the APCR exit process */ 
static qurt_anysignal_t g_pmiSignal USLEEP_DATA_SECTION;

/* Function pointer table for different Sleep behavior based on various
 * restrictions
 *
 *  DEFAULT   : Execute Idle-time Solver
 *  OVERRIDE  : qurt_override_wait_for_idle is used to prevent sleep
 *  UIMAGE    : uImage perform function is used
 *  HOLD_OFF  : No Low-power Mode selection is performed
 */
static sleep_idle_entry_ptr_type 
g_sleepIdleEntryTable[SLEEP_OS_IDLE_MODE_NUM_STATES] USLEEP_DATA_SECTION = 
{
  sleepOS_performLPM,        /* SLEEP_OS_IDLE_MODE_DEFAULT  */
  sleepOS_SWFI,              /* SLEEP_OS_IDLE_MODE_OVERRIDE */
  sleepOS_uSleepPerform,     /* SLEEP_OS_IDLE_MODE_USLEEP   */
  sleepOS_holdoffNoMode      /* SLEEP_OS_IDLE_MODE_HOLD_OFF */
};

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * sleepOS_pmiHandler
 *
 * @brief Function responsible for handling Power Manager Interrupt (PMI).
 *
 * @param context: Thread context or data. (used for prototype compliance only)
 */
static void sleepOS_pmiHandler(void *context)
{
  /* Registering for PMI and associated signal */
  qurt_anysignal_init(&g_pmiSignal);

  /* Interrupt registration must be done in the context of the handler. */
  if(QURT_EOK != qurt_interrupt_register(SLEEP_PMI_ID, &g_pmiSignal,
                                         SLEEP_PMI_MASK))
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_ERROR, 0, 
                    "Power Management Interrupt Registration failed");
    CORE_VERIFY(0);
  }

  /* PMI interrupt monitoring and handling task */
  while(1)
  {
    qurt_anysignal_wait(&g_pmiSignal, SLEEP_PMI_MASK);
   
    /* Call correct handler */
    g_PMIFncPtr();

    /* Signal is handled - Clear it */
    qurt_anysignal_clear(&g_pmiSignal, SLEEP_PMI_MASK);

    /* Interrupt has been handled, inform QuRT */
    qurt_interrupt_acknowledge(SLEEP_PMI_ID);
  }
}

/**
 * sleepOS_registerPMIHandler
 *
 * @brief As part interrupt registration with QuRT, this function creates 
 *        a thread that will execute function to handle the Power Management
 *        Interrupt (PMI).
 *
 * @Note
 * As per pthread specifics, must be called from thread which does not terminate
 * before the newly created thread does i.e. usually from Sleep task entry 
 * function.
 */
static void sleepOS_registerPMIHandler(void)
{
  qurt_thread_t      pmiHandlerThread;
  qurt_thread_attr_t pmiHandlerAttr;
  
  /* Set default handler */
  sleepOSMisc_setPMIHandlerFunctionPTR(0, sleepOS_PMIPerformer);

  /* Initialize attribute */
  qurt_thread_attr_init(&pmiHandlerAttr);

  /* setting up attributes for pmi handler thread */
  qurt_thread_attr_set_name(&pmiHandlerAttr, "PMI_Handler" );
  qurt_thread_attr_set_tcb_partition(&pmiHandlerAttr, 1); /* locate in uImage */
  qurt_thread_attr_set_priority(&pmiHandlerAttr, SLEEP_PMI_TASK_PRI );
  qurt_thread_attr_set_stack_size(&pmiHandlerAttr, SLEEP_PMI_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&pmiHandlerAttr, (void *)g_sleepPMITaskStack);
  
  /* Creating thread to run PMI handler */
  CORE_VERIFY(QURT_EOK == qurt_thread_create(&pmiHandlerThread, &pmiHandlerAttr,
                                             sleepOS_pmiHandler, NULL));

  return;
}

/**
 * sleepOS_qurtInit
 * 
 * @brief Initialize the sleep subsystem.
 */
static void sleepOS_qurtInit( void )
{
  /* Get clock handle first - Subsequent initialization can result in 
   * cpu frequency query through ATS. Initialize query handler first */
  CORE_VERIFY_PTR(g_sleepHandles.cpu_clk_freq_query_handle =
                  npa_create_query_handle("/clk/cpu"));

  /* Initialize the logging subsystem. */
  sleepLog_initialize();
  sleepLog_setLevel( SLEEP_LOG_LEVEL_MAX );

  /* Initialize target-independent NPA nodes. */
  sleepNPA_initialize();

  /* Initialize LPR / LPRM tracking subsystem. */
  sleepLPR_initialize();

  /* Initialize statistical data system */
  sleepStats_init();

  /* Initialize target-dependent stuff (nodes, modes, etc.). */
  sleepTarget_initialize();

  /* Initialize the uSleep system */
#ifdef USLEEP_ISLAND_MODE_ENABLE  
  uSleep_initialize();
#endif

  /* Register for RCInit completion event */
  sleepHoldoff_registerRCinitCompletionEvent();

  /* Register interrupt handler for interrupt 0 (also known as Power 
   * Management Interrupt) */
  sleepOS_registerPMIHandler();

  /* Try to get query handles for the resources we just created.
     These should be ready immediately, but check them anyway. */
  CORE_VERIFY_PTR(g_sleepHandles.wakeup_node_query_handle =
                  npa_create_query_handle( "/core/cpu/wakeup") );

  CORE_VERIFY_PTR(g_sleepHandles.max_duration_node_query_handle =
                  npa_create_query_handle( "/sleep/max_duration") );

  CORE_VERIFY_PTR(g_sleepHandles.latency_node_query_handle =
                  npa_create_query_handle( "/core/cpu/latency") );

  CORE_VERIFY_PTR(g_sleepHandles.sleep_lpr_query_handle =
                  npa_create_query_handle( "/sleep/lpr") );

  /* Set the initial solver configuration. */
  sleepSolver_setSolverFunction(&sleep_lookup_table_solver);

  /* Attaching Dal handle to clock driver */
  CORE_DAL_VERIFY(DAL_DeviceAttach(DALDEVICEID_CLOCK, 
                                   &g_sleepHandles.dal_clk_handle));

  return;
}

/** 
 * sleepOS_setFrequency 
 *  
 * @brief Sets max frequency at current voltage when executing sleep.
 *
 * This function sets the max frequency for current voltage level when 
 * executing the sleep solver and executing low power modes.
 *
 * @return Returns the new/updated frequency in KHz.
 */
static uint32 sleepOS_setFrequency(void)
{
  uint32  cpuFreqHz;
  uint32  cpuFreqKhz;
  bool    bRequired = TRUE;

  CORE_VERIFY_PTR(g_sleepHandles.dal_clk_handle);

  CORE_DAL_VERIFY(DalClock_SetCPUMaxFrequencyAtCurrentVoltage(
                   g_sleepHandles.dal_clk_handle,
                   bRequired,
                   &cpuFreqHz) );

  cpuFreqKhz = cpuFreqHz / 1000;
  
  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                  "Sleep CPU frequency set (%u Khz)", cpuFreqKhz);

  return cpuFreqKhz;
}

/**
 * sleepOS_unsetFrequency 
 *
 * @brief Releasing Sleep request on CPU clock
 */
static void sleepOS_unsetFrequency(void)
{
  uint32  cpuFreqHz;
  bool    bRequired = FALSE;

  CORE_DAL_VERIFY(DalClock_SetCPUMaxFrequencyAtCurrentVoltage(
                   g_sleepHandles.dal_clk_handle,
                   bRequired,
                   &cpuFreqHz) );

  return;
}

/**
 * sleepOS_waitForIdle 
 *
 * @brief Suspend Sleep until processor is idle
 *  
 * @note  This call prepares for power collapse and masks the 
 *        global interrupt if HW threads are all wait
 * 
 */
static void sleepOS_waitForIdle(void)
{
  qurt_power_wait_for_idle();
  return;
}

/**
 * sleepOS_enterIdle 
 *
 * @brief Execute Halt until interrupt
 */
static void sleepOS_enterIdle(void)
{
  /* Wait for active exits STM, clear flag */
  g_sleepState.processor_in_stm = FALSE;

  /* Unmask global interrupt which was masked in
   * call to sleep_os_wait_for_idle() and places 
   * sleep task in ready queue. 
   * Returns when any other thread is awakened */
  qurt_power_wait_for_active();
  return;
}

/**
 *  
 * sleepOS_getSleepDurations 
 *  
 * @brief Get the hard duration, soft duration, and latency budget to 
 *        be used for idle processing.
 *
 * @param hardDeadline:   [output] Buffer to write the hard deadline
 * @param softDeadline:   [output] Buffer to write the soft deadline
 * @param latency_budget: [output] Buffer to write the latency budget.
 */
static void sleepOS_getSleepDurations(uint64 *hardDeadline,
                                      uint64 *softDeadline,
                                      uint32 *latencyBudget)
{
  npa_query_type  qres;
  
  /* Query the hard wake-up time using the os abstraction function. */
  *hardDeadline = sleepOS_getHardWakeupTime(NULL);

  /* Obtain the soft wake-up time by querying max duration node and wakeup 
   * node, and getting the minimum amongst them */
  *softDeadline = sleepOS_getSoftWakeupTime();

  /* Get the latency budget from /core/cpu/latency.  The latency node will
   * return the minimum latency budget being requested by all clients.
   * This lets us know how quickly we need to respond to an interrupt when
   * it occurs. */
  CORE_VERIFY(NPA_QUERY_SUCCESS == 
              npa_query(g_sleepHandles.latency_node_query_handle,
                         NPA_QUERY_CURRENT_STATE,
                         &qres));

  *latencyBudget = qres.data.value;

  return;
}

/**
 * sleepOS_hasEnoughTime 
 *  
 * @brief Determine whether there is enough time to perform the selected low
 *        power mode or not.
 *
 * @param minWakeupTime: The expected sleep wakeup.
 * @param enterExitTime: Time to enter and exit the selected low power mode.
 *
 * @return TRUE if there is not enough time for sleep, otherwise FALSE.
 */
static boolean sleepOS_hasEnoughTime(uint64 minWakeupTime,
                                     uint64 enterExitTime)
{
  if(minWakeupTime <= ((uint64)g_sleepTargetConfig.entry_ticks +
                       (uint64)g_sleepTargetConfig.exit_ticks + 
                       enterExitTime + CoreTimetick_Get64()))
  {
    /* By the time we run through all of sleep, the timer will
     * have expired, so it's not worth it. */
    return FALSE;
  }

  return TRUE;
}

/** 
 * sleepOS_exitSTM 
 *  
 * @brief This function reverses any special requirements for sleep task
 *        It is designed to be called before exiting sleepOS_performLPM
 */
static void sleepOS_exitSTM(void)
{
  /* We are about to exit from Sleep context - set flag to false */
  g_sleepState.processor_in_stm = FALSE;

  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING,
                      SLEEP_EARLY_EXIT_STM_NUM_ARGS,
                      SLEEP_EARLY_EXIT_STM_STR, 
                      SLEEP_EARLY_EXIT_STM);

  g_sleepState.cycle_stats.sleep_exit_stm = CoreTimetick_Get64();
  qurt_power_exit();

  return;
}

/**
 * sleepOS_prepareForSleep 
 *  
 * @brief Common logic that will verify it is safe to enter a low power mode. 
 *  
 *        If there is an entry failure status, the appropriate action will have
 *        already occured, the caller will not need to take further action.
 *  
 *        If the function returns success, it will have already entered STM
 *        and the caller should continue to enter a low power mode.
 *  
 * @param idleModeCfg: Enum to indicate how processor idle is expected to 
 *                     be handled currently.
 *  
 * @return Time of STM entry (in ticks) or 0 if failure 
 */
static uint64 sleepOS_prepareForSleep(sleepOS_IdleModeType idleModeCfg)
{
  uint64 sleepStart;

  /* Wait for all other HW threads to go idle. If the override setting is 
   * disabled, this function will return and the system will already be in
   * STM. */
  sleepOS_waitForIdle();

  /* Mark start of this sleep cycle */
  sleepStart = CoreTimetick_Get64();
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, SLEEP_ENTER_IDLE_NUM_ARGS,
                      SLEEP_ENTER_IDLE_STR, SLEEP_ENTER_IDLE );

  /* Check to ensure that no rpm msgs are in-flight */
  if(FALSE == rpm_is_mq_empty())
  {
    sleepLog_QDSSEvent( SLEEP_EARLY_EXIT_STM_NUM_ARGS,
                        SLEEP_EARLY_EXIT_STM);

    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 0,
                    "Short SWFI (reason: RPM message in flight)" );
    sleepStart = 0;
    sleepOS_enterIdle();
  }
  /* Check the flag that allows low power modes */
  else if(0 == g_sleepAllowLowPowerModes)
  {
    sleepStart = 0;
    sleepOS_enterIdle();
  }
  /* Ensure that idle plugin has not changed */
  else if(FALSE == sleepOS_verifyIdleModeConfig(0, idleModeCfg))
  {
    sleepLog_QDSSEvent(SLEEP_EARLY_EXIT_STM_NUM_ARGS,
                       SLEEP_EARLY_EXIT_STM);

    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 0, 
                    "Sleep cycle skipped "
                    "(reason: Idle Plugin state changed)");

    sleepStart = 0;
    qurt_power_exit();
  }

  return sleepStart;
}

/**
 * sleepOS_performLPMEnter
 * 
 * @brief Function to execute Sleep entry path for solver based modes
 *        during idle time.
 *
 * @param context: Reference to the context from which it is being called. 
 *  
 * @return TRUE if sleep mode was entered 
 *         FALSE if any error or early exit occured 
 */
static boolean sleepOS_performLPMEnter(void* context)
{
  uint32               pendingInterrupts;
  uint32               curFrequency;
  uint64               sleepStart;
  uint64               minWakeup;
  uint64               currTime;
  sleepOS_IdleModeType idleModeCfg = (sleepOS_IdleModeType)context;

  /* Execute common sleep entry checks */
  if(0 == (sleepStart = sleepOS_prepareForSleep(idleModeCfg)))
  {
    return FALSE;
  }

  /* Setting flag to indicate that processor is in Sleep context */
  g_sleepState.processor_in_stm = TRUE;

  /* Querying sleep node for duration and latency constraints */
  sleepOS_getSleepDurations(&g_sleepState.hard_deadline, &g_sleepState.soft_deadline,
                            &g_sleepState.solver_input.latency_budget);

  minWakeup = MIN(g_sleepState.hard_deadline, g_sleepState.soft_deadline);

  /* Check for pending interrupts - 
   * Abandon LPM effort if true */
  pendingInterrupts = qurt_system_ipend_get();
  if(IPEND_IS_MSB_SET(pendingInterrupts))
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 1+(1*2),
                    "Early Exit (ints pending: 0x%08x) ",
                    pendingInterrupts);
  
    sleepOS_exitSTM();
    return FALSE;
  }

  /* Set the maximum frequency at current voltage for executing solver+lprs */
  curFrequency = sleepOS_setFrequency();

  /* Update frequency table pointer to match current core frequency.
   * Either an exact fLUT match or the closest fLUT will be returned */
  if(TRUE != sleepStats_getTableEntry(curFrequency,
                                      &g_sleepState.cycle_stats.fLUT)) 
  {
    /* If the function returns !TRUE, we need to allocate a new fLUT and realloc
     * all of the cache & statistic arrays outside of STM */ 
    sleepOS_exitSTM();
    g_sleepState.cycle_stats.fLUT = 
      sleepStats_addFrequencyTable(g_sleepState.cycle_stats.fLUT,
                                   curFrequency);
    sleepOS_unsetFrequency();
    return FALSE;
  }

  /* set current frequency index value for solver */
  g_sleepState.solver_input.fLUT = g_sleepState.cycle_stats.fLUT;

  /* Fill in solver durations to operate on.  This takes into account the
   * amount of time that's passed since we checked for the durations. */
  currTime = CoreTimetick_Get64();
  g_sleepState.solver_input.hard_duration = g_sleepState.hard_deadline - currTime;
  g_sleepState.solver_input.soft_duration = g_sleepState.soft_deadline - currTime;

  /* Set solver input mask to only select uncached modes */
  g_sleepState.solver_input.synth_attr_mask = SYNTH_MODE_ATTR_LPR_UNCACHEABLE;

  /* Run the solver.  This will get back a list of all low power modes that
   * can be entered based on these parameters. */
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_INFO, SLEEP_ENTER_SOLVER_NUM_ARGS,
                      SLEEP_ENTER_SOLVER_STR, SLEEP_ENTER_SOLVER, 
                      curFrequency, 
                      ULOG64_DATA(g_sleepState.solver_input.hard_duration),
                      ULOG64_DATA(g_sleepState.solver_input.soft_duration),
                      g_sleepState.solver_input.latency_budget);

  /* Run solver to select low power mode to enter */
  sleepSolver_solveMode(&g_sleepState.solver_input, &g_sleepState.solver_output);

  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_INFO, SLEEP_EXIT_SOLVER_NUM_ARGS,
                      SLEEP_EXIT_SOLVER_STR, SLEEP_EXIT_SOLVER);

  if (NULL == g_sleepState.solver_output.selected_synthLPRM)
  {
    /* No Modes were selected:
     * Execute ALL WAIT until interrupt or timer expiry */
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 1+(2*2),
                    "Short SWFI (reason: no modes chosen) "
                    "(hard duration: 0x%llx) "
                    "(soft duration: 0x%llx) (latency budget: 0x%08x)",
                    ULOG64_DATA(g_sleepState.solver_input.hard_duration),
                    ULOG64_DATA(g_sleepState.solver_input.soft_duration),
                    g_sleepState.solver_input.latency_budget);

    sleepOS_unsetFrequency();
    sleepOS_enterIdle();
    return FALSE;
  }

  /* Check for pending Interrupts: Abandon LPM effort if interrupt pending */
  pendingInterrupts = qurt_system_ipend_get();
  if(IPEND_IS_MSB_SET(pendingInterrupts))
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 1,
                    "Early Exit (ints pending: 0x%08x)",
                    pendingInterrupts);

    sleepOS_exitSTM();
    sleepOS_unsetFrequency();
    return FALSE;
  }

  /* Disable deferrable timers */
  sleepTarget_deferTimers();

  /* synth lprm to notify if sleep duration changes */
  g_sleepState.selected_synthLPRM = g_sleepState.solver_output.selected_synthLPRM;

  /* Set selected mode for later use in statistics */
  g_sleepState.cycle_stats.mode = g_sleepState.solver_output.selected_synthLPRM;

  /* Make sure there's still time to do the selected mode */
  if(FALSE == sleepOS_hasEnoughTime(minWakeup,
                                    g_sleepState.solver_output.enter_exit_time))
  {
    /* Not enough time:
     * Execute ALL WAIT until interrupt or timer expiry */
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 1 + (1*2),
                    "Short SWFI (reason: not enough time to enter and exit) " 
                    "(synth latency time: 0x%08x) " 
                    "(Hard deadline: 0x%llx)",
                    g_sleepState.solver_output.enter_exit_time,
                    ULOG64_DATA(g_sleepState.hard_deadline));

    sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING,
                        SLEEP_EARLY_EXIT_STM_NUM_ARGS,
                        SLEEP_EARLY_EXIT_STM_STR, 
                        SLEEP_EARLY_EXIT_STM);

    /* We are about to exit from Sleep context - set flag to false */
    g_sleepState.processor_in_stm = FALSE;
    g_sleepState.cycle_stats.sleep_exit_stm = CoreTimetick_Get64();
    qurt_power_exit();

    /* Undefer the timers after exiting STM. */
    sleepTarget_undeferTimers();

    sleepOS_unsetFrequency();
    sleepOS_enterIdle();  /* Enter all wait state */
    return FALSE;
  }

  /* Setting a flag to indicate that after this point we will need to
   * perform exit logic */
  g_sleepState.execute_sleep_exit_path = TRUE;

  /* Calculate the backoff deadline, and pass that to the enter functions. */
  g_sleepState.cycle_stats.backoff_deadline = 
    g_sleepState.hard_deadline - g_sleepState.solver_output.backoff_time;

  sleepStart = CoreTimetick_Get64() - sleepStart;

  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 2 + (2*2),
                  "Entering modes (hard deadline: 0x%llx) "
                  "(backoff deadline: 0x%llx) "
                  "(backoff: 0x%x) "
                  "(Sleep entry time: %d)",
                  ULOG64_DATA(g_sleepState.hard_deadline),
                  ULOG64_DATA(g_sleepState.cycle_stats.backoff_deadline),
                  g_sleepState.solver_output.backoff_time,
                  (uint32)sleepStart);

  synthLPRM_enter(g_sleepState.solver_output.selected_synthLPRM, 
                  g_sleepState.cycle_stats.backoff_deadline, 
                  g_sleepState.cycle_stats.fLUT);

  return TRUE;
}

/** 
 * sleepOS_performLPMExit 
 *  
 * @brief Function to execute Exit path while coming out of solver based 
 *        low power modes during idle time.
 *
 * Depending on the low power modes we enter, this could be called either
 * from Sleep or an IST context.
 *
 * @param context: Reference to context from which it is being called 
 *                 (unused for now - more for complying with prototype
 *                 of interrupt handler). But if we need to differentiate
 *                 this could be used.
 *
 * @return none
 */
void sleepOS_performLPMExit(void)
{
  uint64 currTick = CoreTimetick_Get64();
//  static uint32 WBCount = 0;

  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 0, "Exiting modes");

  g_sleepState.cycle_stats.os_overhead.sleep_resume = currTick;

  /* Logging point of return to stats module */
  sleepStats_putLprTimeData(currTick, SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

  /* Setting the flag to FALSE to avoid any unnecessary execution 
   * of the exit path afterwards. */
  g_sleepState.execute_sleep_exit_path = FALSE;

  /* Get VID register value to report last interrupt that fired */
  g_sleepState.cycle_stats.master_interrupt = qurt_system_vid_get();

  g_sleepState.selected_synthLPRM = NULL;

  /* Exit functions of low power modes */
  synthLPRM_exit(g_sleepState.solver_output.selected_synthLPRM, 
                 g_sleepState.cycle_stats.fLUT);

  /* NPA scheduler can update the hard dealine as part of the enter function. 
   * Set backoff deadline to updated value while still in STM */
  g_sleepState.cycle_stats.backoff_deadline = 
    g_sleepState.hard_deadline - g_sleepState.solver_output.backoff_time;

  /* Get sleep wakeup time & reason as recorded from standalone or RPM modes */ 
  g_sleepState.cycle_stats.actual_wakeup_time = 
    sleepStats_getLprTimeData(SLEEP_STATS_TIME_WAKEUP_TYPE);

  g_sleepState.cycle_stats.master_wakeup_reason = 
    (sleepStats_wakeup_reason)sleepStats_getMiscData(SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);

  /* Fill in remaining stat input data for logging */ 
  g_sleepState.cycle_stats.hard_deadline = g_sleepState.hard_deadline;

  /* Get last OS boot statistics */
#if 0
  /*Commenting out until qurt support is in place*/
  g_sleepState.cycle_stats.os_overhead.count =     
    qurt_power_shutdown_get_hw_ticks(&g_sleepState.cycle_stats.os_overhead.sleep_time,
                                     &g_sleepState.cycle_stats.os_overhead.awake_time);

  /* Set count to 0 if we performed APCR and WB didn't run which would mean
   * the timestamps are not valid */

  if(WBCount == g_sleepState.cycle_stats.os_overhead.count)
  {
    g_sleepState.cycle_stats.os_overhead.count = 0;
  }
  else
  {
    WBCount = g_sleepState.cycle_stats.os_overhead.count;
  }
#else
  g_sleepState.cycle_stats.os_overhead.count = 0;
#endif

  /* Sleep Exit STM */
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                      SLEEP_EXIT_STM_NUM_ARGS,
                      SLEEP_EXIT_STM_STR, 
                      SLEEP_EXIT_STM);

  /* We are about to exit from Sleep context - set flag to false */
  g_sleepState.processor_in_stm = FALSE;

  /* Actual sleep exit STM time */ 
  g_sleepState.cycle_stats.sleep_exit_stm = CoreTimetick_Get64();

  /* Exit STM
   * All statistical data must be filled in prior to exiting STM or a race
   * condition will be created between processing in the sleep task and the
   * PMI exit handler. */
  qurt_power_exit();
  sleepTarget_undeferTimers();

  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                      SLEEP_EXIT_IDLE_NUM_ARGS, 
                      SLEEP_EXIT_IDLE_STR, 
                      SLEEP_EXIT_IDLE,
                      ULOG64_DATA(g_sleepState.cycle_stats.sleep_exit_stm));
  
  sleepOS_unsetFrequency();

  return;
}

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * sleepOS_getFrequency
 */
uint32 sleepOS_getFrequency(void)
{
  npa_query_type query;

  query.data.value = 0;

  CORE_VERIFY(NPA_QUERY_SUCCESS == 
                npa_query(g_sleepHandles.cpu_clk_freq_query_handle, 
                          NPA_QUERY_CURRENT_STATE,
                          &query) );

  return query.data.value;
}

/*
 * sleepOS_PMIPerformer
 */
void sleepOS_PMIPerformer(void)
{
  /* Calling PMI handler */
  sleepOS_performLPMExit();
  return;
}

/*
 * sleepOS_getLastTimerDeadline
 */
uint64 sleepOS_getLastTimerDeadline(void)
{
  return g_sleepState.timer_deadline;
}

/*
 * sleepOS_offsetSleepDuration
 */
void sleepOS_offsetSleepDuration(uint64 offset)
{
  /* Adjust the sleep duration, so that the new duration gets passed
   * to the rest of the enter functions. */
  if(NULL != g_sleepState.selected_synthLPRM)
  {
    g_sleepState.selected_synthLPRM->wakeup_tick += offset;
  }

  /* Adjust the hard deadline as well, in order to correctly calculate
   * whether we woke up late before exiting sleep. */
  g_sleepState.hard_deadline += offset;

  return;
}

/*
 * sleepOS_getHardDeadline
 */
uint64 sleepOS_getHardDeadline(void)
{
  return g_sleepState.hard_deadline;
}

/*
 * sleepOS_getSoftDeadline
 */
uint64 sleepOS_getSoftDeadline(void)
{
  return g_sleepState.soft_deadline;
}

/*
 * sleepOS_getHardWakeupTime
 */
uint64 sleepOS_getHardWakeupTime(uint64 *firstNondeferrable)
{
  uint64 tempDeadline;
  uint64 utimerDeadline;
  uint64 npaDeadline;

  /* Retrieve the time (in ticks) of the next scheduled timer expiry. */
  tempDeadline    = (uint64)timer_get_first_non_deferrable_timer_expiry();
  utimerDeadline  = (uint64)utimer_get_first_non_deferrable_timer_expiry();

  /* Limit wakeup time for bringup or test */
  if(g_sleepForceWakeupTimeForDebug != 0)
  {
    uint64 now = CoreTimetick_Get64();
    if(tempDeadline > (now + g_sleepForceWakeupTimeForDebug))
    {
      tempDeadline = (now + g_sleepForceWakeupTimeForDebug);
    }
  }

  /* Populate first non-deferrable deadline if valid pointer was given */
  if(NULL != firstNondeferrable)
  {
    *firstNondeferrable = tempDeadline;
  }

  /* Use the first to expire between normal operational & island timer frames */
  g_sleepState.timer_deadline = MIN(tempDeadline, utimerDeadline);

  npaDeadline = sleepNPAScheduler_getTimer();

  sleepLog_printf( SLEEP_LOG_LEVEL_DEBUG, 2*3,
                   "Hard wakeup times (DDR deadline: 0x%llx) "
                   "(uTimer deadline: 0x%llx) "
                   "(NPA deadline: 0x%llx)",
                   ULOG64_DATA(tempDeadline),
                   ULOG64_DATA(utimerDeadline),
                   ULOG64_DATA(npaDeadline) );

  /* return earliest wakeup time */
  return(MIN(npaDeadline, g_sleepState.timer_deadline));
}

/*
 * sleepOS_getSoftWakeupTime
 */
uint64 sleepOS_getSoftWakeupTime(void)
{
  npa_query_type  qres;
  uint64          wakeupExpiry;
  uint64          maxDurationExpiry;

  /* Get the sleep wakeup from the wakeup node.  This will return the "soft"
   * wakeup time.  Soft wakeups are those that are hinted at by other
   * subsystems.  Soft wakeups allow us to calculate which mode we will enter,
   * so we don't waste time entering a mode that we are going to have to wake
   * up from soon anyway. */
  CORE_VERIFY(NPA_QUERY_SUCCESS == 
              npa_query(g_sleepHandles.wakeup_node_query_handle,
                        SLEEP_QUERY_ABS_WAKEUP_TIME,
                        &qres));

  wakeupExpiry =  qres.data.value64;

  /* Get the sleep duration from the max duration node.  This will return the
   * "soft" max duration.  Soft wakeups are those that are hinted at by other
   * subsystems.  Soft wakeups allow us to calculate which mode we will enter,
   * so we don't waste time entering a mode that we are going to have to wake
   * up from soon anyway. */
  CORE_VERIFY(NPA_QUERY_SUCCESS == 
              npa_query(g_sleepHandles.max_duration_node_query_handle,
                        NPA_QUERY_CURRENT_STATE,
                        &qres));

  /* Turn max duration into an ABS wakeup time */
  maxDurationExpiry = (uint64)qres.data.value + CoreTimetick_Get64();

  sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 2*2,
                  "Soft wakeup timers (Wakeup Node: 0x%llx) "
                  "(Max Node: 0x%llx)",
                  ULOG64_DATA(wakeupExpiry), 
                  ULOG64_DATA(maxDurationExpiry));

  /* return earliest soft wakeup time */
  return(MIN(wakeupExpiry, maxDurationExpiry));
}

/*
 * sleepOS_verifyIdleModeConfig
 */
boolean sleepOS_verifyIdleModeConfig(uint32 coreNum, 
                                     sleepOS_IdleModeType idleMode)
{
  CORE_VERIFY(idleMode < SLEEP_OS_IDLE_MODE_NUM_STATES);
  return (g_idleEntryPtr == g_sleepIdleEntryTable[idleMode])? TRUE : FALSE;
}

/*
 * sleepOS_configIdleMode
 */
void sleepOS_configIdleMode(uint32                coreNum,
                            sleepOS_IdleModeType  newIdleMode)
{
  CORE_VERIFY( newIdleMode < SLEEP_OS_IDLE_MODE_NUM_STATES );
  g_idleEntryPtr = g_sleepIdleEntryTable[newIdleMode];
  return;
}

/*
 * sleepOSMisc_setPMIHandlerFunctionPTR
 */
void sleepOSMisc_setPMIHandlerFunctionPTR(uint32                     coreNum,
                                          sleep_PMI_handler_ptr_type newPMIPtr)
{
  g_PMIFncPtr = newPMIPtr;
  return;
}

/**
 * sleepOS_holdoffNoMode
 *
 * @brief This function simply returns and does not perform any type of low 
 *        power mode. Usually this is during system initialization or in a
 *        situation where we don't want target to enter any low power modes
 *        at all (e.g. debug, bring up). 
 *
 * @note Controlled via idle plugin.
 */
uint32 sleepOS_holdoffNoMode(void)
{
  /* Due to some holdoff client, we cannot simply perform any low power modes.
   * Simply return. At some point, sleep function pointer would change when all
   * holdoff requests are released. Until then, we will keep coming here. */
  return 0;
}

/**
 * sleepOS_SWFI
 *
 * @brief This function is used to enter all wait or cached low power modes.
 *
 * @note This function will be removed once Sleep starts using OS override
 *       feature.
 *
 * @return Always 0 (for prototype compliance).
 */
uint32 sleepOS_SWFI(void)
{
  /* Wait for all other HW threads to go idle. */
  sleepOS_waitForIdle();

  /* Since we are in this function, sleep idle plugin was set to swfi only
   * when sleep task was last scheduled. Make sure the idle plugin has not 
   * changed since then. If changed, simply return. Else we can proceed
   * with wait_for_active().
   *
   * There is a chance an interrupt could come in after checking and change 
   * idle plugin state but the window is very small and we are relying on 
   * deferrable timers (e.g. dog that are present on all non hloses) which
   * will hopefully prevent target to stay in swfi indefinitely. */
  if(TRUE == sleepOS_verifyIdleModeConfig(0, SLEEP_OS_IDLE_MODE_SWFI_ONLY))
  {
    /* Wait for a thread to go active. */
    sleepOS_enterIdle();
  }
  else
  {
    /* Unmask global interrupt which was masked in
     * call to sleep_os_wait_for_idle() */
    qurt_power_exit();
  }

  return 0;
}

/**
 * sleepOS_uSleepPerform
 * 
 * @brief Entry to performing low power modes in uSleep.
 *
 * @return Potential error code (unused as of now)
 */
uint32 sleepOS_uSleepPerform(void)
{
  uint32 retVal = 0;

#ifdef USLEEP_ISLAND_MODE_ENABLE  
  /* island mode is defined and uSleep is compiled. */
  uSleep_idle_entry_ptr_type uSleepEntry = uSleep_getIdleFunctionPtr();
  if( NULL != uSleepEntry )
  {
    retVal = uSleepEntry();
  }
#else
  /* island mode is not defined and some is requesting uSleep. */
  CORE_VERIFY(0);
#endif

  return retVal;
}

/*
 * sleepOS_uSleepPerformError
 */ 
uint32 sleepOS_uSleepPerformError(void)
{
  /* Set via fatal error exit from uImage transition. This function should
   * NEVER be allowed to run from OS scheduler, but core verify just in case. */
  CORE_VERIFY(0);

  return 1; /* Just here for compliance with prototype. */
}

/*
 * sleepOS_uSleepPerformDefault
 */ 
uint32 sleepOS_uSleepPerformDefault(void)
{
#ifdef USLEEP_ISLAND_MODE_ENABLE

  uint64 hardDeadline;
  uint64 ddrTimerFrameDeadline;
  uint64 sleepStart;
  uint32 uSleepLatency;

  /* Update transition times if necessary */
  uSleep_updateTransitionTimes();

  /* Execute common sleep entry checks */
  sleepStart = sleepOS_prepareForSleep(SLEEP_OS_IDLE_MODE_USLEEP);
  if((0 == sleepStart) || 
     (uSleep_getIdleFunctionPtr() != sleepOS_uSleepPerformDefault))
  {
    g_sleepState.processor_in_stm = FALSE;
    return 0;
  }
 
  sleepLog_printf(SLEEP_LOG_LEVEL_PROFILING, 0,
                  "Begin uSleep Transition");

  /* Get the current latency for uSleep to transition in and out.
   * This will be used below to verify there is enough time to enter uImage */
  uSleepLatency = uSleep_getTransitionTime();

  /* Get the non-deferable timer deadlines */
  hardDeadline = sleepOS_getHardWakeupTime(&ddrTimerFrameDeadline);

  /* Perform a final check to see if there is enough time to enter & exit
   * uImage mode before the deadline expires. The comparison includes the
   * time to enable DDR and the general overhead of entry & exit code */
  if(hardDeadline <= (CoreTimetick_Get64() + uSleepLatency))
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 1 + (2*2),
                    "Short SWFI (reason: no time to enter) "
                    "(hard deadline: 0x%llx) "
                    "(DDR deadline: 0x%llx) "
                    "(uSleep Latency: %d)",
                    ULOG64_DATA(hardDeadline),
                    ULOG64_DATA(ddrTimerFrameDeadline),
                    uSleepLatency);

    sleepOS_enterIdle();
    return 0;
  }

  /* Only defer normal operational timers, island ones will be done once we
   * transition. */
  timer_defer_match_interrupt_64();

  /***** Begin transition to uImage *****/
  uSleep_entry(ddrTimerFrameDeadline);

#endif

  return 0;
}

/*
 * sleepOS_createConfigHandle
 */
CoreConfigHandle sleepOS_createConfigHandle(unsigned int core_num)
{
#if 0
  char path[MAX_INI_PATH_LEN];

  /* Build the path to the sleep_config.ini file */
  snprintf(path, MAX_INI_PATH_LEN,
           "/nv/item_files/sleep/core%d/sleep_config.ini", core_num);

  return(CoreIni_ConfigCreate(path));
#else
  return NULL;
#endif
}

/**
 * sleepOS_destroyConfigHandle
 */
void sleepOS_destroyConfigHandle(CoreConfigHandle config)
{
  /*CoreIni_ConfigDestroy(config);*/
  return;
}

/*
 * Functions below are for managing locks for the LPRMs in order to serialize
 * their enter and exit function calls during idle time. However, for single
 * core environment they are just stub functions and not used as of now. We
 * have to define them as they are called in common code. Once we have
 * CoreLock, we can probably use that instead of this.
 */

/*
 * sleepOS_createLPRMFunctionLock
 */
void sleepOS_createLPRMFunctionLock(sleep_lprm *mode)
{
  return;
}

/*
 * sleepOS_LPRMFunctionLock
 */
void sleepOS_LPRMFunctionLock(sleep_mode_fn_lock mode_lock)
{
  return;
}

/*
 * sleepOS_LPRMFunctionUnlock
 */
void sleepOS_LPRMFunctionUnlock(sleep_mode_fn_lock mode_lock)
{
  return;
}

/**
 * sleepOS_readEFSConfig 
 *  
 * @brief Initialize the sleep LPR subsystem.  When this callback is 
 *        called, the EFS subsystem has been initialized.  We rely on
 *        that in order to read the config files.
 *
 * @note Not all masters have access to EFS and require this function.
 */
void sleepOS_readEFSConfig(void)
{
#if 0
  boolean       sleep_config_value  = FALSE;
  unsigned int  ret                 = FALSE;

  /* Check to see if we should do any LPRMs at all. */
  ret = sleepConfig_readBool(0, 
                             (char *)"all_lprms", 
                             NULL,
                             (char *)"disable", 
                             &sleep_config_value );

  if(ret)
  {
    g_sleepAllowLowPowerModes = !sleep_config_value;
  }

  if(g_sleepAllowLowPowerModes == FALSE)
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_WARNING, 0,
                    "WARNING (message: \"All sleep modes are disabled"
                    " in the global config\")" );
  }
#endif

  return;
}

/**
 * sleepOS_performLPM
 *
 * @brief Put the system in to the lowest possible power state allowed by
 *        imposed restrictions at run time.
 *
 * This function usually solves for the low power modes that can be entered
 * in special sleep context.
 *
 * @return Always 0 (for prototype compliance)
 */ 
uint32 sleepOS_performLPM(void)
{
  boolean sleepModeEntered;
  void    *context = (void *)(SLEEP_OS_IDLE_MODE_DEFAULT);

  sleepModeEntered = sleepOS_performLPMEnter(context);

  /* Check if we need to execute exit path from here. It might already 
   * have been executed from other context.
   *
   * @Note
   * We are relying on a fact that when we come out of low power mode after
   * idle solver based Sleep, only one HW thread is running any SW. For modes,
   * that trigger PMI from SPM, exit path must be executed from IST context.
   * This is currently ensured by QuRT. If it changes, we will have to insert
   * additional check so that we don't execute exit path from here if we
   * had entered in to any mode with PMI.
   */
  if(g_sleepState.execute_sleep_exit_path)
  {
    sleepOS_performLPMExit();
  }

  if(TRUE == sleepModeEntered)
  {
    /* Log and update any statistic data in sleep task context, but only if
     * a low power mode was actually entered. */
    sleepStats_logWakeup(&g_sleepState.cycle_stats);
  }

  return 0;
}

/*
 * sleepOS_isProcessorInSTM
 */
uint32 sleepOS_isProcessorInSTM(void)
{
  return (TRUE == g_sleepState.processor_in_stm ? 1 : 0);
}

/**
 * sleepOS_mainTask
 * 
 * @brief Main sleep task that will call various low power modes
 *        when the system goes idle
 *
 * Note: located in uImage section
 */
void sleepOS_mainTask
(
  /* Parameter received from Main Control task - ignored */
  void *ignored    /*lint -esym(715,ignored) */
)
{
  /* Read NV items, etc. here to check for modes that are disabled. */
  sleepOS_readEFSConfig();

  /* Main sleep task processing - Enter as many low power modes as possible. */
  while(1)
  {
    /* Call the idle entry point.  This function pointer may be modified
     * by the /sleep/idle/plugin resource. */
    if(g_idleEntryPtr != NULL)
    {
      g_idleEntryPtr();
    }
  }

  CORE_VERIFY(0);
}

/**
 * sleepOS_taskInit
 * 
 * @brief RCInit function that will create the main sleep task and initilize 
 *        all of the sleep data structures 
 */
void sleepOS_taskInit(void)
{
  qurt_thread_attr_t  attr;
  qurt_thread_t       tid;

  /* Initialize the sleep subsystem */
  sleepOS_qurtInit();

  /* Initilize main sleep thread which needs to be located in the island
   * section */ 
  qurt_thread_attr_init(&attr);

  /* Stack memory has to be statically allocated due to island section
   * location requirement */
  qurt_thread_attr_set_stack_size(&attr, SLEEP_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&attr, (void *)g_sleepTaskStack);

  qurt_thread_attr_set_priority(&attr, SLEEP_TASK_PRI);
  qurt_thread_attr_set_tcb_partition(&attr, 1); /* task is located in island */
  qurt_thread_attr_set_name(&attr, "sleep");

  /* Create the main sleep task in island section memory */
  qurt_thread_create(&tid, &attr, sleepOS_mainTask, NULL);

  return;
}

