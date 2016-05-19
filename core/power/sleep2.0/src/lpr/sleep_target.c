/*==============================================================================
  FILE:         sleep_target.c

  OVERVIEW:     This file provides target-specific functionality for the
                ADSP Subsystem.

  DEPENDENCIES: None

                Copyright (c) 2011-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/sleep_target.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdint.h>
#include "sleep.h"
#include "sleep_target.h"
#include "timer.h"
#include "CoreTime.h"
#include "CoreVerify.h"
#include "sleep_log.h"
#include "com_dtypes.h"
#include "npa_resource.h"
#include "sleep_lpri.h"
#include "atomic_ops.h"
#include "DDIInterruptController.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "sleepi.h"
#include "HALhwio.h"
#include "HALsleep_hwio.h"
#include "msmhwiobase.h"
#include "vmpm.h"
#include "synthTypes.h"
#include "synthLPR.h"

#ifdef USLEEP_ISLAND_MODE_ENABLE
#include "utimer.h"
#endif

/*==============================================================================
                             INTERNAL DEFINITIONS
 =============================================================================*/
/* Time required from ramping up the frequency to just before entering
 * low power modes. This will change based on current frequncy. */
#define SLEEP_ENTRY_TICKS 4225

/* Time required from removing backoff time to logging wakeup event while
 * exiting from sleep. Like entry time, this will change based on frequency
 * before entering sleep. */
#define SLEEP_EXIT_TICKS 385

/* Timer used to holdoff sleep for a certain amount of time at initial
 * boot-up. */
#define SLEEP_INIT_DELAY_MS 10000

/* Interrupt vector value for the wakeup trigger from RPM */
#define RPM_WAKEUP_INTERRUPT_VALUE 14

/*==============================================================================
                               GLOBAL VARIABLES
 =============================================================================*/
/* Sleep Target configuration parameters */
sleep_target_config g_sleepTargetConfig = 
{
  .entry_ticks    = SLEEP_ENTRY_TICKS,
  .exit_ticks     = SLEEP_EXIT_TICKS,
  .init_delay_ms  = SLEEP_INIT_DELAY_MS,
  .chip_family    = DALCHIPINFO_FAMILY_UNKNOWN,
  .chip_ver       = 0
};

/* Variable for indication of entry to RPM assisted modes */
static boolean g_synthLPRMisRPMAssisted = FALSE;

/* Dependencies to wait on before registering any LPRs. */
static const char *g_LPRDependencies[] =
{
  "/sleep/lpr"
};

/* Dal data struct to hold DAL Interrupt Controller Handle */
static DalDeviceHandle *g_DALInterruptCtrlHndl;

/* Handle to the DAL "WakeupTimer" timetick driver, for calculating the
 * wakeup tick during sleep. This timer is used by the DAL and timer services
 * to provide "sleep time". */
static DalDeviceHandle *g_DALWakeTimerHandle;

/*==============================================================================
                           EXTERNAL REFERENCES
 =============================================================================*/
/* deferrable timer groups */
extern timer_group_type timer_null_group;

/* target-specific nodes that are implemented & initialized in this module */
extern sleep_synth_lpr SleepLPR_synth;

extern npa_node_definition sleep_vdd_dig_node;
extern npa_node_definition sleep_l2cache_node;

/*==============================================================================
                           FORWARD DECLARATIONS
 =============================================================================*/
static void sleepTarget_wakeupHandler(uint32 param) USLEEP_CODE_SECTION;
static void sleepTarget_RPMWakeupHandler(uint32 param) USLEEP_CODE_SECTION;

static uint64 sleepTarget_enableQTMR(uint64 wakeupTick);
static void sleepTarget_disableQTMR(void);

/**
 * Functions to enable/disable dog on LPASS/ADSP. They are defined as
 * weak symbols because these functions are needed in sleep (corebsp)
 * and they are not defined in corebsp but they are defined in 
 * full ADSP image. So in order to avoid conflict of multiple defintions
 * and let corebsp image build independently, we are defining them as
 * weak symbols.
 */
void WDT_active(void) __attribute__((weak));
void WDT_idle(void) __attribute__((weak));

/*==============================================================================
                        STATIC FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * sleepTarget_registerLPRs 
 *  
 * @brief  Register the LPRs & nodes that are owned by sleep.
*/
static void sleepTarget_registerLPRs( void         *context,
                                      unsigned int  event_type,
                                      void         *data,
                                      unsigned int  data_size )
{
  npa_resource_state  initial_state                = 0;
  npa_client_handle   sleep_npa_rpm_sync_client    = NULL;
  npa_client_handle   sleep_npa_cpuVdd_sync_client = NULL;

  /* Register the NPA nodes that this module currently owns. */
  npa_define_node(&sleep_vdd_dig_node, &initial_state, NULL);
  npa_define_node(&sleep_l2cache_node, &initial_state, NULL);

  /* Register cpu-vdd lpr */
  CORE_VERIFY_PTR(sleep_npa_cpuVdd_sync_client =
                  npa_create_sync_client(SLEEP_LPR_NODE_NAME,
                                         "/core/cpu/vdd",
                                         NPA_CLIENT_REQUIRED));
  sleepLPR_define("cpu_vdd", sleep_npa_cpuVdd_sync_client);

  npa_issue_required_request(sleep_npa_cpuVdd_sync_client, SLEEP_ALL_LPRMS);

  /* Register rpm lpr */
  CORE_VERIFY_PTR(sleep_npa_rpm_sync_client =
                  npa_create_sync_client(SLEEP_LPR_NODE_NAME,
                                         "core/power/sleep/rpm",
                                         NPA_CLIENT_REQUIRED));
  sleepLPR_define("rpm", sleep_npa_rpm_sync_client);

  npa_issue_required_request(sleep_npa_rpm_sync_client, SLEEP_ALL_LPRMS);

  return;
}

/** 
 * sleepTarget_wakeupHandler
 * 
 * @brief Null handler for the registered idle timer interrupts
 */
static void sleepTarget_wakeupHandler(uint32 param)
{
  return;
}

/**
 * sleepTarget_RPMWakeupHandler
 *
 * @brief Null handler for the RPM wakeup (timed trigger) interrupt.
 */
static void sleepTarget_RPMWakeupHandler(uint32 param)
{
  return;
}

/**
 * sleepTarget_initialize
 */
void sleepTarget_initialize(void)
{
  uint32  timerIntN;
  uint32  islandMode  = 0;

#ifdef USLEEP_ISLAND_MODE_ENABLE
  islandMode = 1;
#endif

  /* Register a callback for when the necessary dependencies are available,
   * in order to register the nodes and LPRs that sleep owns. */
  npa_resources_available_cb( NPA_ARRAY( g_LPRDependencies ),
                              sleepTarget_registerLPRs, NULL );

  /* set below groups as deferrable */
  timer_group_set_deferrable( &timer_null_group, TRUE );

  /* use qtimer frame that is available on all other targets */
  DalTimetick_Attach( "WakeUpTimer", &g_DALWakeTimerHandle );
  CORE_VERIFY_PTR( g_DALWakeTimerHandle );

  DalTimetick_GetInterruptVectorNum(g_DALWakeTimerHandle, &timerIntN);

  /* Attaching to interrupt controller and registering interrupt handlers */
  CORE_VERIFY( DAL_DeviceAttach( DALDEVICEID_INTERRUPTCONTROLLER,
                                 &g_DALInterruptCtrlHndl ) == DAL_SUCCESS );

  CORE_VERIFY(DAL_SUCCESS == DalInterruptController_RegisterISR(
      g_DALInterruptCtrlHndl,
      timerIntN,
      (DALIRQ)sleepTarget_wakeupHandler,
      (const DALIRQCtx) 0,
      DALINTRCTRL_ENABLE_CONFIG_EX(DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER,
                                   0, 
                                   islandMode)));

  CORE_VERIFY(DAL_SUCCESS == DalInterruptController_RegisterISR(
      g_DALInterruptCtrlHndl,
      RPM_WAKEUP_INTERRUPT_VALUE,
      (DALIRQ)sleepTarget_RPMWakeupHandler,
      (const DALIRQCtx) 0,
      DALINTRCTRL_ENABLE_CONFIG_EX(DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER,
                                   0, 
                                   islandMode)));

  return;
}

/**
 * sleepTarget_getCPUArchitecture
 */
void sleepTarget_getCPUArchitecture(DalChipInfoFamilyType   *chipFamily,
                                    DalChipInfoVersionType  *chipVer)
{
  static uint32 init = 0;

  if(init == 0)
  {
    DalDeviceHandle *hChipInfo;

    /* Get global chip architecture  */
    if( DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &hChipInfo) == DAL_SUCCESS )
    {
      DalDevice_Open(hChipInfo, DAL_OPEN_SHARED);
      DalChipInfo_GetChipFamily(hChipInfo, &g_sleepTargetConfig.chip_family);
      DalChipInfo_GetChipVersion(hChipInfo, &g_sleepTargetConfig.chip_ver);
      DalDevice_Close(hChipInfo);
      init = 1;
    }
  }

  if(chipFamily != NULL)
    *chipFamily = g_sleepTargetConfig.chip_family;

  if(chipVer != NULL)
    *chipVer    = g_sleepTargetConfig.chip_ver;

  return;
}

/*
 * sleepTarget_initializeLPR
 */
void sleepTarget_initializeLPR(void)
{
  /* Register the pre-synthesized LPRMs here.  This must be done
   * before any of the component LPRMs are registered, so we do
   * it when the /sleep/lpr node is being initialized. */
  synthLPR_define( &SleepLPR_synth );

  return;
}


/** 
 * sleepTarget_enableQTMR 
 *  
 * @brief Sets wake-up duration for local QTimer
 */
static uint64 sleepTarget_enableQTMR(uint64 wakeupTick)
{
  uint64 matchTick;
  uint64 now = CoreTimetick_Get64();

  /* Setting up a new match value */
  DalTimetick_SetNextInterrupt64(g_DALWakeTimerHandle,
                                 wakeupTick,
                                 now, &matchTick );

  /* Re-enable qtimer interrupt */
  CORE_VERIFY( DalTimetick_Enable(g_DALWakeTimerHandle, 1) == DAL_SUCCESS );

  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, (1*2),
                  " Program QTMR (match tick: 0x%llx)",
                  ULOG64_DATA(matchTick) );

  return matchTick;
}

/** 
 * sleepTarget_disableQTMR 
 *  
 * @breif Disables the Sleep QTimer
 */
static void sleepTarget_disableQTMR( void )
{
  if ( g_DALWakeTimerHandle )
  {
    /* Disable qtimer interrupt */
    CORE_VERIFY( DalTimetick_Enable(g_DALWakeTimerHandle, 0)
                 == DAL_SUCCESS );
  }
  return;
}

/*
 * sleepTarget_enableSleepTimer 
 */
uint64 sleepTarget_enableSleepTimer( uint64 wakeup_tick )
{
  /* Ensure that wakeup_tick is in the future */
  CORE_VERIFY( CoreTimetick_Get64() < wakeup_tick );
  return(sleepTarget_enableQTMR(wakeup_tick));
}

/*
 * sleepTarget_disableSleepTimer
 */
void sleepTarget_disableSleepTimer( void )
{
  sleepTarget_disableQTMR();
  return;
}

/*
 * sleepTarget_deferTimers 
 */
void sleepTarget_deferTimers(void)
{
  timer_defer_match_interrupt_64();
#ifdef USLEEP_ISLAND_MODE_ENABLE
  utimer_defer_match_interrupt_64();
#endif
  return;
}

/*
 * sleepTarget_undeferTimers  
 */
void sleepTarget_undeferTimers(void)
{
  timer_undefer_match_interrupt();
#ifdef USLEEP_ISLAND_MODE_ENABLE
  utimer_undefer_match_interrupt_64();
#endif
  return;
}

/*
 * sleepTarget_enableWatchdog 
 */
void sleepTarget_enableWatchdog(void)
{
/*  if(WDT_active)
  {
    WDT_active();
  } */
  return;
}

/*
 * sleepTarget_disableWatchdog 
 */
void sleepTarget_disableWatchdog(void)
{
/*  if(WDT_idle)
  {
    WDT_idle();
  } */
  return;
}

/*
 * sleepTarget_setRPMAssistedMode
 */
void sleepTarget_setRPMAssistedMode( boolean value )
{
  g_synthLPRMisRPMAssisted = value;
  return;
}

/*
 * sleepTarget_getRPMAssistedMode
 */
boolean sleepTarget_getRPMAssistedMode( void )
{
  return(g_synthLPRMisRPMAssisted);
}

/*
 * sleepTarget_getRPMStatisticsAddress
 */
void *sleepTarget_getRPMStatisticsAddress(void)
{
  uint32 rpm_stats_va = 0;

  /* RPM Stats Virtual Address is 128 bytes above
   * the mpm interrupt base virtual address
   */
  rpm_stats_va = (vmpm_getProcMpmBaseVA() - 128);
  return ((void*) rpm_stats_va);
}

/**
 * Stub dog enabld/disable functions. These implementations will be used only
 * when corebsp image is built. If entire ADSP image is built, they should be
 * replaced by actual implementation from ADSP.
 */
void WDT_idle(void)
{
}

void WDT_active(void)
{
}
