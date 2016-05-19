/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        ERR EXCEPTION TASK MODULE

GENERAL DESCRIPTION
  This module contains the task definition for err exception handler, when not running in main().

EXTERNALIZED FUNCTIONS
  None

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_pd_exception_task.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/27/14   din     Replaced snprintf with mutex free calls.
07/31/14   din     File created to support Error on User PD.
===========================================================================*/
#include "DALSys.h"
#include "erri.h"
#include "tms_utils.h"

#define dwMaxNumEvents                          2                                // DALSys Worker Loop Event Queue Depth for DALTASK
#define wlPriority                              190                              // SHARED_DRIVER_SERVICE_PRI_ORDER

void err_exception_handler(void);                                                // forward declaration; exception handler

/*===========================================================================
FUNCTION ERR_TASK

DESCRIPTION
  Create a context for err_exception_handler when main() is not available.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS

===========================================================================*/

DALResult err_exception_task(DALSYSEventHandle hEvent, void* tid)
{

   err_exception_handler(); // does not return

   return(DAL_SUCCESS);
}

void bootstrap_exception_handler(void)
{
   const unsigned long wlStackSize = 4096;   // minimal (KB)
   static DALSYSEventHandle hEventStart;     // context for the error exception handler
   static DALSYSWorkLoopHandle hWorkLoop;    // context for the error exception handler

   char err_task_name[13];

   if ( sizeof(err_task_name) <= tms_utils_fmt(err_task_name, 12, "err_pd_ex_%d", qurt_getpid()) )
   {
     MSG(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Failed to copy task name in err_task_name ");
   }

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_WORKLOOP_EVENT, &hEventStart, NULL))
   {
      ERR_FATAL("Exception Handler initialization failure",0,0,0);
   }
   if (DAL_SUCCESS != DALSYS_RegisterWorkLoopEx(err_task_name, wlStackSize, wlPriority, dwMaxNumEvents, &hWorkLoop, NULL))
   {
      ERR_FATAL("Exception Handler initialization failure",0,0,0);
   }
   if (DAL_SUCCESS != DALSYS_AddEventToWorkLoop(hWorkLoop, err_exception_task, NULL, hEventStart, NULL))
   {
      ERR_FATAL("Exception Handler initialization failure",0,0,0);
   }
   if (DAL_SUCCESS != DALSYS_EventCtrl(hEventStart, DALSYS_EVENT_CTRL_TRIGGER))
   {
      ERR_FATAL("Exception Handler initialization failure",0,0,0);
   }

}

