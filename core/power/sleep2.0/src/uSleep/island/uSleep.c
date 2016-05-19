/*==============================================================================
  FILE:         uSleep.c

  OVERVIEW:     This file provides the main uSleep functions that reside in
                island memory space

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/uSleep.c#2 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleepi.h"
#include "sleepi.h"
#include "sleep_osi.h"
#include "sleep_statsi.h"
#include "uSleep_util.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "qurt.h"
#include "spm.h"
#include "timer.h"
#include "utimer.h"
#include "uTimetick.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Signal used to block caller when uSleep exit is requested */
qurt_signal_t g_uSleepExitSignal;

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Entry point for next idle cycle */
static uSleep_idle_entry_ptr_type g_uSleepIdleEntryPtr = NULL;

/* Selected LPR from last solver run */
static uSleep_LPR *g_chosenLPR = NULL;

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/** 
 * uSleep_completeTransitionTouSleep
 * 
 * @brief Transitions to uSleep mode 
 *  
 * @param transProfileData: Transition profiling data pointer 
 *  
 * @return FALSE  -> Indicates that the transition into island mode has already
 *                   been completed.
 *         TRUE   -> Indicates that the appropriate steps have taken place
 *                   to complete the transition into island mode.
 */ 
static boolean uSleep_completeTransitionTouSleep
(
  uSleep_transition_profiling *transProfileData
)
{
  boolean               status  = FALSE;
  uSleep_internal_state state   = uSleep_getStateInternal();
  
  /* Verify that we are in a transition or active state. */
  CORE_VERIFY(0 != (state & (uSLEEP_INTERNAL_STATE_ACTIVE       |
                             uSLEEP_INTERNAL_STATE_FAST_ENTRY   |
                             uSLEEP_INTERNAL_STATE_FULL_ENTRY)));

  /* If uImage transition is occuring we are already in STM. */
  if(state & (uSLEEP_INTERNAL_STATE_FAST_ENTRY  |
              uSLEEP_INTERNAL_STATE_FULL_ENTRY))
  {
    /* Indicate that the transition to island mode is completes. */
    status = TRUE;

    /* Enter island mode.
     * This must be called from uImage memory section as it will turn off DDR */
    uSleep_islandControl(UIMAGE_ENTER);
    
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                     "uSleep transition done (Override: %s)",
                     USLEEP_CXO_SHUTDOWN_DISABLE == 
                      uSleep_getCXOModeInternal() ? "Enable" : "Disable");

    /* Record the uSleep entry transition time */
    sleepStats_updateValue(&transProfileData->entry_stats,
                           uTimetick_Get() - transProfileData->entry_start_time);

    transProfileData->total_entries++;
  }

  return status;
}

/*==============================================================================
                            EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleep_setIdleFunctionPtr
 */
void uSleep_setIdleFunctionPtr(uSleep_idle_entry_ptr_type newIdleEntryPtr)
{
  g_uSleepIdleEntryPtr = newIdleEntryPtr;
}

/*
 * uSleep_getIdleFunctionPtr
 */
uSleep_idle_entry_ptr_type uSleep_getIdleFunctionPtr(void)
{
  return g_uSleepIdleEntryPtr;
}

/* 
 * uSleep_worker
 */
uint32 uSleep_worker(void)
{
  uSleep_internal_state       state;
  uint64                      localEnterLatency;
  uint64                      ddrWakeupTime;
  uint64                      now;
  uint64                      hardDeadline;
  uSleep_transition_profiling *transProfileData = uSleep_getProfilingDataPtr();

  /* Complete the transition to island mode if necessary. */
  uSleep_completeTransitionTouSleep(transProfileData);

  /* Wait for all other HW threads to go idle. Two things can happen here:
   * 1. If override is set, we will enter all-wait when all threads go idle and
   *    this function does not return.
   * 2. If override is not set, this call will return when all threads go
   *    idle and we will be in STM */
  qurt_power_wait_for_idle();
 
  /* Mark beginning of this sleep cycle. This will be subtracted below to
   * calculate the enter latency */
  localEnterLatency = uTimetick_Get();

  /* This check should never be true unless the OS scheduled the sleep task
   * during a fatal error case (which should also never happen). */
  if((FALSE == sleepOS_verifyIdleModeConfig(0, SLEEP_OS_IDLE_MODE_USLEEP)) ||
     (uSleep_getIdleFunctionPtr() != uSleep_worker))
  {
    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION,
                         USLEEP_EXIT_NUM_ARGS,
                         USLEEP_EXIT_STR, 
                         USLEEP_EXIT,
                         "Function change");
    /* Exit STM */
    qurt_power_exit();

    return 1;
  }

  /* Get current state of uSleep to verify that an exit request has not been
   * made. */
  state = uSleep_getStateInternal();
    
  /* Check for exit request */
  if(state & (uSLEEP_INTERNAL_STATE_REQ_FAST_EXIT | 
              uSLEEP_INTERNAL_STATE_REQ_FULL_EXIT))
  {
    /* An exit request has been made and is in progress, call the transition
     * function to finish the process of exiting island mode. */ 
    uSleep_transitionToNormalOperation();

    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION, 
                         USLEEP_EXIT_NUM_ARGS,
                         USLEEP_EXIT_STR, 
                         USLEEP_EXIT,
                         "Requested");

    /* Record the exit transition time */
    sleepStats_updateValue(&transProfileData->exit_stats,
                           CoreTimetick_Get64() - transProfileData->exit_start_time); 

    /* Exit STM */
    qurt_power_exit();

    /* Someone requested an exit, unblock their exit call */
    qurt_signal_set(&g_uSleepExitSignal, 0x01);

    /* Undefer normal operational timers that were deferred on the way into
     * uSleep after we have exited STM. */
    timer_undefer_match_interrupt();

    return 0;
  }

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0, "uSleep start");

  /* Get first timer to expire */
  hardDeadline = utimer_get_first_non_deferrable_timer_expiry();

  /* DDR timer has already been adjusted for transition latency. */
  ddrWakeupTime = uSleep_getDDRWakeupTimeInternal();

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, (2*2),
                   "Wakeup deadline "
                   "(Hard: 0x%llx) "
                   "(DDR: 0x%llx)", 
                   ULOG64_DATA(hardDeadline),
                   ULOG64_DATA(ddrWakeupTime));
  
  /* Solve and set the mode to enter. Given that the adjusted DDR wakeup
   * timer has been added as a non-deferrable uTimer on the entry transition, we
   * can simply base our next wakeup on the hardDeadline. */
  CORE_VERIFY_PTR(g_chosenLPR = uSleepLPR_idleSolver(hardDeadline));
  
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 1,
                   "Solver "
                   "(Mode: %s)",
                   g_chosenLPR->name);

  if(NULL != g_chosenLPR->enter_func)
  {
    /* Adjust wakeup time by LPRM backoff time */
    hardDeadline -= g_chosenLPR->backoff;

    /* Defer the uImage timers */
    utimer_defer_match_interrupt_64();

    /* Last check to make sure we can enter the mode still. */
    now = uTimetick_Get();
    if(hardDeadline <= now)
    {
      uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                       "Skipping LPM - wakeup in past");

      utimer_undefer_match_interrupt_64();

      /* Exit STM */
      qurt_power_exit();
      return 0;
    }

    /* Compute uSleep enter latency overhead */
    localEnterLatency = now - localEnterLatency;

    /* Run the enter functions for the selected LPR that was previously chosen. */
    uSleepLPR_runLPRFunctions(TRUE, hardDeadline);
  }
  else
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                     "Skipping LPM - no mode chosen");

    g_chosenLPR = NULL;

    /* Exit STM */
    qurt_power_exit();
  }

  return 0;
}

/*
 * uSleep_workerExit
 */
void uSleep_workerExit(void)
{
  uint64          STMExit;
  uint64          lastPMITime = uSleep_getLastPMITimestampInternal();
  unsigned int    interrupt   = qurt_system_vid_get();
  
  /* Verify that an exit funtion needs to be called */
  if(NULL != g_chosenLPR && 
     NULL != g_chosenLPR->exit_func)
  {
    /* Run exit function */
    uSleepLPR_runLPRFunctions(FALSE, 0);
  }
  
  g_chosenLPR = NULL; 

  /* Record STM exit time */
  STMExit = uTimetick_Get();

  /* Exit STM */
  qurt_power_exit();
  utimer_undefer_match_interrupt_64();

  uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING, 
                       USLEEP_MASTER_WAKEUP_NUM_ARGS,
                       USLEEP_MASTER_WAKEUP_STR, 
                       USLEEP_MASTER_WAKEUP,
                       interrupt,
                       MICRO_ULOG64_DATA(uSleep_getLastSleepWakeupInternal()),
                       MICRO_ULOG64_DATA(STMExit),
                       MICRO_ULOG64_DATA(lastPMITime));

  return;
}

