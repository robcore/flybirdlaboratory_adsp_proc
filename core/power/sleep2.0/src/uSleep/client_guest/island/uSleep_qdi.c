/*============================================================================== 
  FILE:         uSleep_qdi.c

  OVERVIEW:     Implements QDI layer for uSleep API's in island mode

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/client_guest/island/uSleep_qdi.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdlib.h>
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "sleep_osi.h"
#include "uSleep_util.h"
#include "uSleep_qdi.h"
#include "uSleep_log.h"
#include "client_guest.h"
#include "qurt.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Client QDI opener object */
uSleep_qdi_opener g_uSleepClientObj;

/* Data structure required for QDI init */
const uSleep_qdi_opener g_uSleepOpenerData = 
{
  {uSleep_QDIInvoke, QDI_REFCNT_PERM, 0} 
};

/*==============================================================================
                           INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleep_QDISetCXOMode
 * 
 * @brief QDI interface function to set XO mode 
 *  
 * @return Status from function call (see function for values) 
 */
static inline uint32 uSleep_QDISetCXOMode(int             client_handle, 
                                          uSleep_CXO_mode mode) 
{
  return(uSleep_setCXOMode(mode));
}

/**
 * uSleep_QDIExit
 * 
 * @brief QDI interface function to exit uImage mode and return to normal 
 *        operational mode 
 *  
 * @return Status from function call (see function for values) 
 */
static inline uint32 uSleep_QDIExit(int client_handle)
{
  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, "User PD exit");
  return(uSleep_exit());
}

/**
 * uSleep_QDIInsertCallback
 * 
 * @brief QDI interface function to add a callback notification function 
 *  
 * @return Status from function call (see function for values)
 */
static inline uint32 uSleep_QDIInsertCallback(int             client_handle, 
                                              uSleep_signals  *signal)
{
  return (uSleep_registerUserNotificationCallback(signal));
}

/**
 * uSleep_QDIAddCallbackLatency
 * 
 * @brief QDI interface function to set the current callback latency of the 
 *        function being registered
 *  
 * @return Status from function call (see function for values)
 */
static inline uint32 uSleep_QDIAddCallbackLatency(int client_handle,
                                                  uint32 enterLat,
                                                  uint32 exitLat)
{
  return (uSleep_addUserCallbackLatency(enterLat, exitLat));
}

/*==============================================================================
                           EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * uSleep_QDIInvoke
 */
int uSleep_QDIInvoke(int             client_handle,
                     qurt_qdi_obj_t  *pobj,
                     int             method,
                     qurt_qdi_arg_t  a1,
                     qurt_qdi_arg_t  a2,
                     qurt_qdi_arg_t  a3,
                     qurt_qdi_arg_t  a4,
                     qurt_qdi_arg_t  a5,
                     qurt_qdi_arg_t  a6,
                     qurt_qdi_arg_t  a7,
                     qurt_qdi_arg_t  a8,
                     qurt_qdi_arg_t  a9)
{
   uSleep_qdi_opener *clntobj = (uSleep_qdi_opener *)pobj;
   
   switch(method)
   {
     case QDI_OPEN:
       return uSleep_QDIOpen(client_handle, clntobj);

     case USLEEP_QDI_EXIT: 
       return uSleep_QDIExit(client_handle);

     case USLEEP_QDI_SET_CXO:
       return uSleep_QDISetCXOMode(client_handle, (uSleep_CXO_mode)a1.num);

     case USLEEP_QDI_INSERT_CALLBACK:
       return uSleep_QDIInsertCallback(client_handle, 
                                       (uSleep_signals *)a1.ptr);

     case USLEEP_QDI_ADD_CALLBACK_LATENCY:
       return uSleep_QDIAddCallbackLatency(client_handle,
                                           (uint32)a1.num,
                                           (uint32)a2.num);
     default:
       return -1;
   }
}

