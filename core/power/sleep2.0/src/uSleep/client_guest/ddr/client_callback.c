/*==============================================================================
  FILE:         client_callback.c

  OVERVIEW:     This file provides uSleep client callback functions

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/client_guest/ddr/client_callback.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdlib.h>
#include "DALStdDef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_log.h"
#include "qurt.h"

/*==============================================================================
                           TYPE & MACRO DEFINITIONS
 =============================================================================*/
/* Macros for locking/unlocking the mutex around uSleep callback data access */
#define USLEEP_CB_LOCK()  qurt_mutex_lock(&g_uSleepCallbackMutex);
#define USLEEP_CB_FREE()  qurt_mutex_unlock(&g_uSleepCallbackMutex);

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Master callback structure that contains the user & guest callback data.
 * This structure will be populated as clients register their callbacks */
uSleep_callback_data g_uSleepCallbacks = {0, 0, NULL, NULL};

/* Lock for callback registration */
static qurt_mutex_t g_uSleepCallbackMutex;

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern qurt_mutex_t g_uSleepMutex;

/*==============================================================================
                        INTERNAL DDR SECTION FUNCTIONS
 =============================================================================*/
/**
 * uSleep_userSignalCallback
 * 
 * @brief Callback function that is added to the guest PD callback list that
 *        simply triggers and waits for the user PD callbacks to execute
 * 
 * @param state:    enum to indicate if uImage is entering or exiting
 * @param signals:  signal structure that was given to the registration
 *                  function.  These are the handshake signals used to
 *                  coordinate the guest-user PD callback system
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
static uint32 uSleep_userSignalCallback(uSleep_state_notification  state, 
                                        uSleep_signals             *signals)
{
  /* Callback to simply signal user task to execute its callbacks and wait */
  if(USLEEP_STATE_ENTER == state)
  {
    qurt_anysignal_set(&signals->start, USLEEP_SIGNAL_START_ENTER);
  }
  else
  {
    qurt_anysignal_set(&signals->start, USLEEP_SIGNAL_START_EXIT);
  }

  qurt_signal_wait(&signals->done,
                   USLEEP_SIGNAL_DONE_FINISHED,
                   QURT_SIGNAL_ATTR_WAIT_ALL);

  qurt_signal_clear(&signals->done, USLEEP_SIGNAL_DONE_FINISHED);

  return USLEEP_SUCCESS;
}

/*==============================================================================
                    EXTERNAL DDR SECTION API FUNCTIONS
 =============================================================================*/
/*
 * uSleep_guestClientInit
 */
void uSleep_guestClientInit(void)
{
  qurt_mutex_init(&g_uSleepMutex);
  qurt_mutex_init(&g_uSleepCallbackMutex);
  return;
}

/*
 * uSleep_registerNotificationCallback
 */
uSleep_notification_cb_handle uSleep_registerNotificationCallback(
                                uint32                      enterLat,
                                uint32                      exitLat,
                                uSleep_notification_cb_type callback)
{
  uSleep_callback_list **workingList;

  /* If caller didn't provide a callback, there is nothing to do. */
  if(NULL == callback)
  {
    return 0;
  }

  /* Lock data access */
  USLEEP_CB_LOCK();

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 1,
                   "Registering guest notification callback "
                   "(callback 0x%x)",
                   (uint32)callback);

  workingList = &g_uSleepCallbacks.functionList;

  if(NULL != *workingList)
  {
    /* Move to last one in the list */
    do
    {
      /* Verify callback is not already registered */
      CORE_VERIFY((*workingList)->callbackFcn != callback);
      workingList = &((*workingList)->next);
    }while(NULL != *workingList);
  }

  CORE_VERIFY_PTR(*workingList = calloc(1, sizeof(uSleep_callback_list)));
  
  (*workingList)->callbackFcn = callback;

  /* Add latency here since we already have the mutex */
  g_uSleepCallbacks.enterLat  += enterLat;
  g_uSleepCallbacks.exitLat   += exitLat;
  
  USLEEP_CB_FREE();
  
  return (uSleep_notification_cb_handle)(*workingList);
}

/*
 * uSleep_addUserCallbackLatency
 */
uint32 uSleep_addUserCallbackLatency(uint32 enterLat, uint32 exitLat)
{
  USLEEP_CB_LOCK();
  g_uSleepCallbacks.enterLat  += enterLat;
  g_uSleepCallbacks.exitLat   += exitLat;
  USLEEP_CB_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_registerUserNotificationCallback
 */
uint32 uSleep_registerUserNotificationCallback(uSleep_signals *signals)
{
  /* The user signaling callback will be added to the function list */
  uSleep_user_callback_list **workingList;

  /* Lock data access */
  USLEEP_CB_LOCK();

  workingList = &g_uSleepCallbacks.userFunctionList;

  if(NULL != *workingList)
  {
    /* Move to last one in the list */
    do
    {
      /* Verify callback is not already registered */
      CORE_VERIFY((*workingList)->signals != signals);
      workingList = &((*workingList)->next);
    }while(NULL != *workingList);
  }
  
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                   "Registering user notification callback");

  /* Add initial callback element */
  CORE_VERIFY_PTR(*workingList = calloc(1, sizeof(uSleep_user_callback_list)));
  
  (*workingList)->signals     = signals;
  (*workingList)->callbackFcn = uSleep_userSignalCallback;

  USLEEP_CB_FREE();

  return USLEEP_SUCCESS;
}


