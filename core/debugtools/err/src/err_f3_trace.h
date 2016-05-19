#ifndef ERR_F3_TRACE_H
#define ERR_F3_TRACE_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      Deprecated

GENERAL DESCRIPTION
  Packet processing routines for FEATURE_SAVE_DEBUG_TRACE and
  FEATURE_SAVE_DEBUG_TRACE.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  No requirements

Copyright (c) 2004 - 2009 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_f3_trace.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
12/14/09   tbg     File renamed to err_f3_trace.c; APIs and variables
                   renamed accordingly.
11/30/09   ps      Fixed compiler warnings & added F3trace support(SW).
09/09/09   jwh     Add FEATURE_DOGTEST_TASK code.
10/03/08   vg      Updated code to use PACK() vs. PACKED
04/24/08   tbg     Created err_f3_trace_id_type to help id source build for logs
12/19/06   as      Reverted FEATURE_ERR_SMALL_BUFFER change.
12/18/06   as      Added support to decrease buffer size under
                   FEATURE_ERR_SMALL_BUFFER.
04/06/06   tbg     Allow optional external definitions of default CONTROL and
                   DETAIL values. Only applicable if the feature
                   FEATURE_SAVE_TRACE_ON_BY_DEFAULT is defined.
11/11/05   tbg     Changed naming conventions of err f3 trace files.
10/04/05   tbg     Added ability to turn on F3 trace saving by default,
                   if FEATURE_SAVE_TRACE_ON_BY_DEFAULT is defined
08/11/05   eav     Added ERR_F3_TRACE_BUFFER_CORRUPTED
11/30/04   as      Added FEATURE_AUTO_RESET. This feature resets the phone
                   automatically without user intervention if the phone
                   encounters a critical failure
08/26/04   eav     Added support  for timestamp-saving optimizations
05/20/04   eav     Added supp rt to event-tracing.  Added support to put
                   event trace and F3 trace into a single trace buffer.
05/07/04   eav     File created.

===========================================================================*/

// DEPRECATED API ONLY EXPOSES UNIONS AND STRUCTS FOR SIZE INFORMATION

#if defined(__ARMCC_VERSION)
#message "REMOVE REFERENCES TO UNSUPPORTED PRIVATE API HEADER FILE"
#elif defined(__GCC__)
#pragma message "REMOVE REFERENCES TO UNSUPPORTED PRIVATE API HEADER FILE"
#endif

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "diag_f3_tracei.h"

#endif /* ERR_F3_TRACE_H */
