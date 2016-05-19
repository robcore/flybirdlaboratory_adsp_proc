/*==============================================================================
  FILE:         uSleep_ddr.c

  OVERVIEW:     This file provides uSleep API and functions that reside in DDR
                memory space

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/uSleep_ddr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "sleep_os_misc.h"
#include "uSleep_util.h"
#include "uSleep_log.h"
#include "uSleep_lpr.h"
#include "uSleep_qdi.h"
#include "qurt.h"
#include "timer.h"
#include "utimer.h"
#include "uSleep_timer.h"
#include "island_mgr.h"
#include "npa.h"

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
extern uSleep_callback_data   g_uSleepCallbacks;

/*==============================================================================
                            INTERNAL VARIABLES
 =============================================================================*/

/* NPA client to uSleep resource which would vote for or against uSleep
 * depending on change in latency and transition time constraints. */
static npa_client_handle g_uSleepResourceClient;

/* Latency constraint imposed on /core/sleep/latency node. It will be
 * updated in that resource state change callback registered at init time. */
static uint32 g_latencyConstraint = UINT32_MAX;

/* Mutex to synchronize request to uSleep resource as it can be issued 
 * from multiple contexts. */
static qurt_mutex_t g_uSleepLatencyLock;

/*==============================================================================
                           INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleep_resetTransitionTimes
 * 
 * @brief Resets transition statistic values
 * 
 * @param transPtr: Pointer to transition data 
 */
static void uSleep_resetTransitionTimes(uSleep_transition_profiling *transPtr) 
{
  memset(&transPtr->entry_stats, 0, sizeof(sleepStats_generic));
  memset(&transPtr->exit_stats, 0, sizeof(sleepStats_generic));
  
  transPtr->entry_stats.min  = UINT64_MAX;
  transPtr->exit_stats.min   = UINT64_MAX;

  return;
}

/**
 * uSleep_processUpdatedLatencies
 *
 * @brief This function performs necessary actions when there is a change in
 *        transition latency or driver latency restrictions. Currently it 
 *        votes for or against uSleep based on those inputs.
 *
 * @note This function can be called from multiple contexts so it needs
 *       locking for synchronization.
 */
static void uSleep_processUpdatedLatencies(void)
{
  qurt_mutex_lock(&g_uSleepLatencyLock);

  if(NULL != g_uSleepResourceClient)
  {
    if( g_latencyConstraint < uSleep_getTransitionTime() )
    {
      /* Latency restriction are strict not to allow uSleep */
      npa_issue_required_request(g_uSleepResourceClient, 0);
    }
    else
    {
      /* Ok to vote for uSleep */
      npa_issue_required_request(g_uSleepResourceClient, 1);
    } 
  }

  qurt_mutex_unlock(&g_uSleepLatencyLock);
}

/**
 * uSleep_latencyResourceStateCB
 *
 * @brief Callback to notify any change in latency npa resource state.
 */
static void uSleep_latencyResourceStateCB(void         *context, 
                                          unsigned int eventType,
                                          void         *data, 
                                          unsigned int dataSize)
{
  npa_event_data *eventData = (npa_event_data *)data;

  if( eventData != NULL )
  {
    g_latencyConstraint = eventData->state;
    uSleep_processUpdatedLatencies();
  }
}

/**
 * uSleep_resourceAvailCB
 *
 * @brief Callback which will be invoked once uSleep NPA resource is 
 *        available. This will create a internal client to that resouce.
 *
 * @param context:   Context for this call back (unused).
 * @param eventType: Event type for the call back - resouce available (unused)
 * @param data:      Name of the resource
 * @param dataSize:  Size of above data (unused)
 */
static void uSleep_resourceAvailCB(void         *context, 
                                   unsigned int eventType,
                                   void         *data, 
                                   unsigned int dataSize)
{
  const char *resourceName = (const char *)data;
  
  g_uSleepResourceClient = npa_create_sync_client(resourceName,
                                                  "uSleepInternal",
                                                  NPA_CLIENT_CUSTOM1);

  CORE_VERIFY(NULL != g_uSleepResourceClient);

  uSleep_processUpdatedLatencies();
}

/**
 * uSleep_latencyAvailCB
 *
 * @brief Callback which will be invoked once Latency NPA resource is
 *        available. We will register state change event for that resource 
 *        from here.
 *
 * @param context:   Context for this call back (unused).
 * @param eventType: Event type for the call back - resouce available (unused)
 * @param data:      Name of the resource
 * @param dataSize:  Size of above data (unused)
 */
static void uSleep_latencyAvailCB(void         *context, 
                                  unsigned int eventType,
                                  void         *data, 
                                  unsigned int dataSize)
{
  const char *resourceName = (const char *)data;
  npa_event_handle eventHandle;
  npa_query_type query;
  
  eventHandle = npa_create_change_event_cb(resourceName,
                                           "LatencyChanged",
                                           uSleep_latencyResourceStateCB,
                                           NULL);

  CORE_VERIFY(NULL != eventHandle);

  /* Get the current state of the latency resource */
  CORE_VERIFY(NPA_QUERY_SUCCESS == 
              npa_query_by_event(eventHandle, NPA_QUERY_CURRENT_STATE, &query));

  /* update our internal variable based on above query */
  g_latencyConstraint = (uint32)query.data.state;

}

/**
 * uSleep_initInternal
 *
 * @brief Intializes some of the internal objects which are used to interact
 *        with surrounding systems especially Sleep.
 */
void uSleep_initInternal(void)
{
  /* Initializing the mutex for uSleep resource request */
  qurt_mutex_init(&g_uSleepLatencyLock);

  /* Registering NPA callback on uSleep resource for its client creation */
  npa_resource_available_cb("/core/uSleep", uSleep_resourceAvailCB, NULL);

  /* Registering a state change event callback once resource is available */
  npa_resource_available_cb("/core/cpu/latency", uSleep_latencyAvailCB, NULL);
}

/*==============================================================================
                           EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * uSleep_entry
 */
void uSleep_entry(uint64 ddrWakeupTime)
{
  uint64                      startTime     = CoreTimetick_Get64();
  uSleep_internal_state       state         = uSleep_getStateInternal();
  uSleep_transition_profiling *profileData  = uSleep_getProfilingDataPtr();

  CORE_VERIFY_PTR(profileData);

  /* Set timestamp of the start of the uSleep entry point */
  profileData->entry_start_time = startTime;

  /* Fast exit and reentry is not currently allowed */
  CORE_VERIFY(uSLEEP_INTERNAL_STATE_FAST_EXIT != state);

  /* Set full entry state */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_FULL_ENTRY);
  
  /* Update the PMI handler function to the uImage version */
  sleepOSMisc_setPMIHandlerFunctionPTR(0, uSleepLPR_PMIPerformer);

  /* Call LPR init functions. This must be done before any CB's as it will
   * set the default power mode and the CB's could change that with an XO
   * API call. */
  uSleepLPR_init(TRUE);

  /* Call notification CB's while still in normal operational mode */
  uSleep_transitionNotify(USLEEP_STATE_ENTER);

  /* Transfer normal operational wakeup time to island system */
  uSleep_setDDRWakeupTimeInternal(ddrWakeupTime);

  /* Update the idle function pointer to the main uSleep function */
  uSleep_setIdleFunctionPtr(uSleep_worker);

  return;
}

/*
 * uSleep_initialize
 */
void uSleep_initialize(void)
{
  /* Setup uSleep logging system */
  uSleepLog_initialize();

  /* Setup default uSleep entry point */
  uSleep_setIdleFunctionPtr(sleepOS_uSleepPerformDefault);

  /* Internal initialization */
  uSleep_initInternal();

  /* Setup guest OS client */
  uSleep_guestClientInit();

  /* Set uSleep initial internal state */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_IN_DDR);

  /* Setup the handler for the DDR timer while in uImage */
  uSleepTimer_init();

  /* Setup uSleep Node */
  uSleepNode_initialize();

  /* Setup uSleep QDI interface */
  uSleep_QDIInit();

  /* Setup callback exit signal */
  qurt_signal_init(&g_uSleepExitSignal);

  return;
}

/*
 * uSleep_transitionNotify
 */
void uSleep_transitionNotify(uSleep_state_notification state)
{
  uSleep_callback_list      *guestFunction;
  uSleep_user_callback_list *userFunction;

  /* Notify registered client callback functions of uImage transition */
  guestFunction = g_uSleepCallbacks.functionList;
  userFunction  = g_uSleepCallbacks.userFunctionList;

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                   "uSleep image notification (State: %s)",
                   USLEEP_STATE_ENTER == state ? "Entry" : "Exit");

  /* Call guest OS notification functions */
  while(NULL != guestFunction)
  {
    guestFunction->callbackFcn(state);
    guestFunction = guestFunction->next;
  }

  /* Call user OS notification functions. This will actually signal
   * a thread to run in user space and wait for it to finish calling all user
   * CB's for that particular PD */
  while(NULL != userFunction)
  {
    userFunction->callbackFcn(state, userFunction->signals);
    userFunction = userFunction->next;
  }

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0,
                   "uSleep notification complete");

  return;
}

/* 
 * uSleep_updateTransitionTimes
 */ 
void uSleep_updateTransitionTimes(void)
{
  uSleep_transition_profiling *transPtr = uSleep_getProfilingDataPtr();

  if(transPtr->adjust_count < 4)
  {
    /* Initialize data values */
    uSleep_resetTransitionTimes(transPtr);

    /* Set initial adjustment match value */
    transPtr->adjust_count = 4;
  }
  else if(transPtr->entry_stats.count >= transPtr->adjust_count)
  {
    uint32 enterAvg;
    uint32 exitAvg;
    uint64 enterTotal = transPtr->entry_stats.total;
    uint64 exitTotal  = transPtr->exit_stats.total;
    
    /* Throw out worst cases */
    enterTotal = enterTotal - transPtr->entry_stats.max - transPtr->entry_stats.min;
    exitTotal  = exitTotal - transPtr->exit_stats.max - transPtr->exit_stats.min;

    /* Compute average transition enter and exit latency */
    enterAvg  = (uint32)(enterTotal / (transPtr->entry_stats.count - 2));
    exitAvg   = (uint32)(exitTotal / (transPtr->exit_stats.count - 2));

    uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 2,
                     "Updating uSleep transition times "
                     "(enter: %d) "
                     "(exit: %d)",
                     enterAvg,
                     exitAvg);

    /* Update transition times */
    uSleep_setTransitionTime(enterAvg, exitAvg);

    /* Reset the data for the next adjustment */
    uSleep_resetTransitionTimes(transPtr);

    /* Set next adjustment */
    if(transPtr->adjust_count < 0x000000400)
    {
      transPtr->adjust_count = transPtr->adjust_count << 2;
    }
  }

  return;
}

/*
 * uSleep_setTransitionTime
 */
void uSleep_setTransitionTime(uint32 entryTicks, 
                              uint32 exitTicks)
{
  uSleep_transition_profiling *dataPtr = uSleep_getProfilingDataPtr();
  
  /* Set new values for enter and exit transition latency */
  dataPtr->entry_latency = entryTicks;
  dataPtr->exit_latency = exitTicks;

  /* Take necessary actions for updated transition latency if any */
  uSleep_processUpdatedLatencies();

  return;
}

/*
 * uSleep_getTransitionTime
 */
uint32 uSleep_getTransitionTime(void)
{
  uSleep_transition_profiling *dataPtr = uSleep_getProfilingDataPtr();

  return (dataPtr->entry_latency + dataPtr->exit_latency);
}

