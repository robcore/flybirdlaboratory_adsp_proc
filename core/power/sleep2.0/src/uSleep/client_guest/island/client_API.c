/*==============================================================================
  FILE:         client_API.c

  OVERVIEW:     This file provides uSleep API functions for guest PD that are
                located in the ISLAND section

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/client_guest/island/client_API.c#2 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "sleep_os_misc.h"
#include "uSleep_log.h"
#include "uSleep_util.h"
#include "uSleep_timer.h"
#include "qurt.h"
#include "smd.h"
#include "island_mgr.h"

/*==============================================================================
                           TYPE & MACRO DEFINITIONS
 =============================================================================*/
/* Macros for locking/unlocking the mutex around uSleep API's that will change
 * internal states */ 
#define USLEEP_LOCK()  qurt_mutex_lock(&g_uSleepMutex);
#define USLEEP_FREE()  qurt_mutex_unlock(&g_uSleepMutex);

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* API lock */
qurt_mutex_t g_uSleepMutex;

/*==============================================================================
                       EXTERNAL GUEST SECTION FUNCTIONS
 =============================================================================*/
/*
 * uSleep_exit
 */
uint32 uSleep_exit(void)
{
  uSleep_internal_state       state;
  uint32                      pendingInt    = qurt_system_vid_get();
  uSleep_transition_profiling *profileData  = uSleep_getProfilingDataPtr();
  qurt_thread_t               taskID        = qurt_thread_get_id();

  /* Since we are modifying the uSleep state to exit, only allow one client to
   * do that at a time */
  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                   " Try exit mutex (0x%x)",
                   taskID);
  USLEEP_LOCK();

  state = uSleep_getStateInternal();

  /* If we are currently active, turn on DDR and wait for full exit to happen */
  if(state & uSLEEP_INTERNAL_STATE_ACTIVE)
  {
    /* Record the start of the exit sequence */
    profileData->exit_start_time = uTimetick_Get();

    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING, 
                         USLEEP_EXIT_START_NUM_ARGS,
                         USLEEP_EXIT_START_STR, 
                         USLEEP_EXIT_START,
                         pendingInt);

    /* Clear the existing uTimer that was created based on the first normal
     * mode non-deferrable timer. */
    uSleepTimer_clearTimer();

    /* Enable XO mode so if we are currently in a cached mode, it's exit
     * function is run. This will allow uSleep to exit. */
    uSleep_setCXOModeInternal(USLEEP_CXO_SHUTDOWN_ENABLE);

    /* Reset the exit signal so we can block the caller until uSleep has fully 
     * exited */
    qurt_signal_clear(&g_uSleepExitSignal, 0x01);

    /* Exit island mode */
    uSleep_islandControl(UIMAGE_EXIT);

    /* Block until the system has fully transitioned back to normal operational
     * mode */
    qurt_signal_wait(&g_uSleepExitSignal, 0x01, QURT_SIGNAL_ATTR_WAIT_ALL);
  }
  else if(0 == (state & uSLEEP_INTERNAL_STATE_IN_DDR))
  {
    /* Can not be in a transition state when calling this function */
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0,
                     "ERROR: exit called while in transition");
    CORE_VERIFY(0);
  }

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1, 
                   " Give exit mutex (0x%x)",
                   taskID);
  USLEEP_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_setCXOMode
 */
uint32 uSleep_setCXOMode(uSleep_CXO_mode mode)
{
  USLEEP_LOCK();
  uSleep_setCXOModeInternal(mode);
  USLEEP_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_exitOnError
 */
void uSleep_exitOnError(void)
{
  /* Enable XO mode so if we are currently in a cached mode, it's exit
   * function is run. This will allow uSleep to exit. */
  uSleep_setCXOModeInternal(USLEEP_CXO_SHUTDOWN_ENABLE);

  /* Exit island mode */
  uSleep_islandControl(UIMAGE_EXIT_FAST);

  /* Set sleep function pointer to main entry.  System is in quick normal
   * operational mode where DDR is on, but subsystems are unaware of this
   * state */ 
  uSleep_setIdleFunctionPtr(sleepOS_uSleepPerformError);  

  /* Exit immediately */
  if(ISLAND_MGR_EOK != island_mgr_island_exit())
  {
    /* Fatal error exit is broke, nothing more we can do here. */
    while(1);
  }

  return;
}

/*
 * uSleep_notifyDDRTransitionComplete
 */
void uSleep_notifyDDRTransitionComplete(uint8 ddrOn)
{
  uSleep_internal_state state = uSleep_getStateInternal();

  uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION, 
                       USLEEP_DDR_TRANS_END_NUM_ARGS,
                       USLEEP_DDR_TRANS_END_STR, 
                       USLEEP_DDR_TRANS_END,
                       TRUE == ddrOn ? "On" : "Off");

  if(TRUE == ddrOn)
  {
    /* Only need to take action on a normal exit */
    if(uSLEEP_INTERNAL_STATE_REQ_TRANS_EXIT == state)
    {
      /* Update the internal state so we can continue the exit process in STM */
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_REQ_FULL_EXIT);
    }
  }
  else
  {
    /* Don't care about DDR off on entry into uImage */
  }

  return;
}

