/** vi: tw=128 ts=3 sw=3 et
@file rcinit_dal_task.c
@brief This file contains the API for the Run Control Framework, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_dal_task.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#if defined(RCINIT_TRACER_SWEVT)
#include "tracer.h"
#include "rcinit_tracer_swe.h"
#endif

#include "rcinit_dal.h"
#include "rcinit_internal.h"
#include "sys_m_messages.h"

DALSYSEventHandle hEventCoreStarted;

/*===========================================================================

 FUNCTION rcinit_task

 DESCRIPTION
 hlos task thread to process sequnece groups

 DEPENDENCIES
 none

 RETURN VALUE
 none

 SIDE EFFECTS
 none

 ===========================================================================*/

DALResult rcinit_task(DALSYSEventHandle hEvent, void* arg_p)
{
   RCEVT_SIGEX_SIGDAL sig;
   DALSYSEventHandle hEventShutdownTask;

   rcinit_internal.process_state = rcinit_process_init;

   DALSYS_InitMod(NULL);                                                         // prerequsite dependency

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEventShutdownTask, NULL))
   {
      ERR_FATAL("create event shutdown", 0, 0, 0);
   }

   // rcinit init
   rcinit_init();

   // register as client to system monitor
   sig.signal = hEventShutdownTask;
   rcevt_register_sigex_name(SYS_M_SHUTDOWN, RCEVT_SIGEX_TYPE_SIGDAL, &sig);

   if (DAL_SUCCESS != DALSYS_EventCtrl(hEventCoreStarted, DALSYS_EVENT_CTRL_TRIGGER))
   {
      ERR_FATAL("fail corestarted trigger", 0, 0, 0);
   }

   // signal for observers
   rcecb_signal_name(RCINIT_RCECB_INITGROUPS);
   rcevt_signal_name(RCINIT_RCEVT_INITGROUPS);
#if defined(RCINIT_TRACER_SWEVT)
   tracer_event_simple(RCINIT_SWE_INITGROUPS);
#endif

   MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "group initializations end %d %d %d", 0, 0, 0);

   rcinit_internal.process_state = rcinit_process_blocking;

   // block for system monitor notification
   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_EventWait(hEventShutdownTask))
   {
      ERR_FATAL("task wait event shutdown", 0, 0, 0);
   }

   rcinit_internal.process_state = rcinit_process_running;

   // unregister further system monitor notifications
   rcevt_unregister_sigex_name(SYS_M_SHUTDOWN, RCEVT_SIGEX_TYPE_SIGDAL, &sig);

   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_EventCtrl(hEventShutdownTask, DALSYS_EVENT_CTRL_RESET))
   {
      ERR_FATAL("task wait event shutdown", 0, 0, 0);
   }

   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_DestroyObject(hEventShutdownTask))
   {
      ERR_FATAL("create event shutdown", 0, 0, 0);
   }

   MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, "group terminations begin");

   // signal for observers
#if defined(RCINIT_TRACER_SWEVT)
   tracer_event_simple(RCINIT_SWE_TERMGROUPS);
#endif
   rcevt_signal_name(RCINIT_RCEVT_TERMGROUPS);
   rcecb_signal_name(RCINIT_RCECB_TERMGROUPS);

   // rcinit termination
   rcinit_term();

   // client ack to system monitor
   rcevt_signal_name(SYS_M_SHUTDOWN_ACK);

   // termination
   rcinit_internal.process_state = rcinit_process_term;

   arg_p = arg_p;
   hEvent = hEvent;

   return DAL_SUCCESS;
}

void rcinit_fail(void)
{
   static unsigned long unused = 0;

   for (;;)                                                                      // punt, no exception handler
   {
   }

   /* NOTREACHED */                                                              // lint, CR421030

   unused = unused;
}

#define dwMaxNumEvents        1
#define wlPriority            rcinit_lookup_prio("rcinit")
#define wlStackSize           rcinit_lookup_stksz("rcinit")

void bootstrap_rcinit_task(void)
{
   DALSYSEventHandle hEvent;                                                     // context "lost" on scope exit, reclaimed at task
   DALSYSWorkLoopHandle hWorkLoop;                                               // context "lost" on scope exit, but remains active, not reclaimed

   // Initialize NHLOS Layers Needed

   DALSYS_InitMod(NULL);                                                         // prerequsite dependency

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_WORKLOOP_EVENT, &hEvent, NULL) ||
       DAL_SUCCESS != DALSYS_RegisterWorkLoopEx("RCINIT", wlStackSize, wlPriority, dwMaxNumEvents, &hWorkLoop, NULL) ||
       NULL == hWorkLoop || NULL == hEvent ||
       DAL_SUCCESS != DALSYS_AddEventToWorkLoop(hWorkLoop, rcinit_task, NULL, hEvent, NULL) ||
       DAL_SUCCESS != DALSYS_EventCtrl(hEvent, DALSYS_EVENT_CTRL_TRIGGER))
   {
      rcinit_fail();
   }

   // Block for RCINIT Framework Startup to Complete

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEventCoreStarted, NULL))
   {
      ERR_FATAL("task wait event shutdown", 0, 0, 0);
   }
   else
   {
      if (DAL_SUCCESS != DALSYS_EventWait(hEventCoreStarted))
      {
         ERR_FATAL("task wait event occurance", 0, 0, 0);
      }
   }
}
