/*==============================================================================
  FILE:         uSleep_timer.c

  OVERVIEW:     This file provides the functions located in the island section
                to handle exit requirements for a DDR timer

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/uSleep_timer.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_log.h"
#include "utimer.h"
#include "uTimetick.h"
#include "uSleep_timer.h"
#include "uSleep_util.h"

/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
/* Statically allocated stack memory for the task */
uint8 g_uSleepDDRTimerTaskStack[DDR_TIMER_HANDLER_STACK_SIZE];

/* Signal that indicates to begin the uImage exit process due to our expired 
 * utimer */
qurt_anysignal_t g_uSleepDDRTimerSignal;

/* Client handle of the registered utimer */
utimer_type g_uSleepTimerClient; 

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepTimer_exitSignalTask
 */
void uSleepTimer_exitSignalTask
(
  /* Parameter received from Main Control task - ignored */
  void *ignored
)
{
  /* Begin task loop */
  while(1)
  {
    /* Wait for the uTimer to expire */
    qurt_anysignal_wait(&g_uSleepDDRTimerSignal, 0x01);

    /* The timer exit task should never be signaled outside of island mode
     * so ensure that it is currently active. */
    CORE_VERIFY(uSleep_getStateInternal() == uSLEEP_INTERNAL_STATE_ACTIVE);

    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, "Timer exit");

    /* Begin the exit process so that we can handle the DDR timer */
    uSleep_exit();

    /* Reset the signal for next time */
    qurt_anysignal_clear(&g_uSleepDDRTimerSignal, 0x01);
  }
   
  return;
}

/*
 * uSleepTimer_clearTimer
 */
void uSleepTimer_clearTimer(void)
{
  uint64 timeLeft;

  timeLeft = utimer_clr_64(&g_uSleepTimerClient, UT_TICK);

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, (1 * 2), 
                   "Timer stop (Remain: 0x%llx)",
                   MICRO_ULOG64_DATA(timeLeft));
  return;
}
