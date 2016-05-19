#ifndef __CLOCKSWEVT_H__
#define __CLOCKSWEVT_H__
/*============================================================================
  @file clock_trace.h

  This header provides a variety of preprocessor definitions, type, data, and
  function declarations for QDSS event logging.

  This file provides an abstraction layer for QDSS tracer features.

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/
/* $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/inc/ClockSWEVT.h#1 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#ifdef CLOCK_TRACER_SWEVT
#include "tracer.h"
#include "ClockSWEventId.h"
#endif

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

#ifdef CLOCK_TRACER_SWEVT
  #define Clock_SWEvent(evtid, numArgs, ...) \
             tracer_event_simple_vargs((evtid), (numArgs), ##__VA_ARGS__);
#else 
  #define Clock_SWEvent(evtid, args, ...)
#endif


#endif /* __CLOCKSWEVT_H__ */

