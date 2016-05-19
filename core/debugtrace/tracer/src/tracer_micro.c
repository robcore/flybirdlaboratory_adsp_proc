/*=============================================================================

FILE:         tracer_micro.c

DESCRIPTION:    Minimal tracer functions and data that are required to be
                in micro image to facilitate SW events 

================================================================================
            Copyright (c) 2014 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/
#include "tracer.h"
#include "tracer_event_ids.h"
#include "tracer_config_int.h"

#include "tracer_portmgr.h"
#include "tracer_stp.h"
#include "tracer_ost.h"
#include "tracer_micro.h"


/*-------------------------------------------------------------------------*/
boolean _is_event_simple_go(tracer_event_id_t eventId)
{
   return ( ( tcfg_is_event_on(eventId) && tcfg_is_op_enabled() &&
              (tcfg_is_event_initialized()) ) ? TRUE : FALSE );
}

/*-------------------------------------------------------------------------*/
void tracer_event_simple(tracer_event_id_t event_id) 
{
#if TRACER_SWEVT
   if (_is_event_simple_go(event_id))
   {
      tracer_stp_send_event(tracer_port_d32(), event_id);
   }
#endif
   return;
}
/*-------------------------------------------------------------------------*/
void tracer_event_simple_vargs(tracer_event_id_t event_id, uint32 num_args, ...)
{
#if TRACER_SWEVT
   STMTracePortType port;
   int key;
   va_list pArgs;

   if (_is_event_simple_go(event_id))
   {
      port = tracer_port_get(&key);
      va_start(pArgs, num_args);
      tracer_ost_send_event_simple_vargs(port, event_id, num_args, pArgs);
      va_end(pArgs);
      tracer_port_free(key);
   }
#endif
   return;
}


#ifdef TRACER_MICRO_TEST
//This should link with out any dependencies outside the uimage
void tracer_micro_test(void) 
{
   UTRACER_EVENT(10);
   UTRACER_EVENT(20,30,40);
}
#endif
