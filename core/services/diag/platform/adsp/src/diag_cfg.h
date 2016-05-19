#ifndef DIAG_CFG_H
#define DIAG_CFG_H
/*===========================================================================

                                  D I A G _ C F G . H

  GENERAL DESCRIPTION
  Contains configuration information for diag per platform

Copyright (c) 2009 - 2012 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                            EDIT HISTORY FOR FILE
                                      
  $Header: //components/rel/core.adsp/2.6.1/services/diag/platform/adsp/src/diag_cfg.h#1 $

when        who    what, where, why
--------    ---    ----------------------------------------------------------
04/29/13    ph    Added a limit on active listeners.
12/14/12    is    Use proper NRT values to resolve issues with buffering mode
11/11/12    sg    Reverted 8 byte alignment for q6
10/15/12    rh    Changed diagbuf NRT drain parameters
11/18/10    vs    Moved diagbuf_next_aligned_byte definition from diagbuf
10/27/10    SG    Moved DIAG_TX_SLEEP_THRESHOLD_DEFAULT,DIAG_TX_SLEEP_TIME_DEFAULT
                  to here from diagbuf_v.h
10/27/10    sg    Increased diagbuf size to 32k for adsp
09/28/10    sg    Moved diag_time_get from diagtarget.h to here
05/11/10    JV    New heap for events
07/17/09    JV    Created
===========================================================================*/
#include "diag_v.h"
#if defined (DIAG_QDSP6_APPS_PROC)
#include "diagstub.h" /* For stubbed ts_get(); for Q6 modem */
#else
#include "time_svc.h" /* for time_get(); for Q6 apps and all other targets */
#endif

#define DIAGBUF_NEXT_ALIGNED_BYTE(p) (((p) + 3) & ~3)

/* Diag uses unprotected timestamp call on QDSP6 modem */
#if defined DIAG_IMAGE_QDSP6_PROC && defined DIAG_IMAGE_MODEM_PROC
#define diag_time_get(x) time_tod_get_no_mutex(x)
#else
#define diag_time_get(x) time_get(x)
#endif
/* Not adding the DIAG_MAX_TX_PKT_SIZ and DIAG_MAX_RX_PKT_SIZ here because 
they need to be exposed to clients. Currently defined in diagpkt.h */

/* DIAGBUF_SIZE is the size, in bytes, of diag's output buffer.  If this buffer
 * fills up, logs and messages will be dropped.  It is recommended to make this
 * number a power of 2 to allow the compiler to optimize the arithmetic using
 * this number to use shift operations instead of brute force math.
 *
 * Note: This must be larger than DIAG_MAX_TX_PKT_SIZ. */

#ifndef DIAGBUF_SIZE
#define DIAGBUF_SIZE (1024*32)
#endif

#ifndef DIAG_TX_SLEEP_THRESHOLD_DEFAULT
#define DIAG_TX_SLEEP_THRESHOLD_DEFAULT (1024*4)
#endif

#ifndef DIAG_TX_SLEEP_TIME_DEFAULT
#define DIAG_TX_SLEEP_TIME_DEFAULT 5
#endif

#define DIAGBUF_COMMIT_THRESHOLD (1024*2)	               /* # of bytes committed to Diag buffer before draining. */
/* The size of the DIAG heap.  Currently, it is only used for events, response 
   packets and allocating tasks for stress testing.  DIAGBUF_SIZE only 
   impacts MSG and LOG packets. */
#define DIAG_HEAP_SIZE (1024 * 4)

#define DIAG_EVENT_HEAP_SIZE (1024 * 2)

#define DIAG_EVENT_SEC_HEAP_SIZE (1024 * 2)

/*Arbitrary limit on active listeners to avoid exhaustion of system heap */
#define DIAG_MAX_ACTIVE_LISTENERS ( 18 )

/* These are the non real time values that are used when diag is in power savings mode*/
#define DIAGBUF_COMMIT_THRESHOLD_NRT (1024*16)

#define DIAG_TX_SLEEP_THRESHOLD_NRT  (1024*8)

#define DIAG_TX_SLEEP_TIME_NRT       5 

#define EVENT_RPT_PKT_SIZE_NRT (128)

#define DIAG_HDLC_PAD_LEN (150)                            /* # of bytes padding to account for hdlc/crc bytes when filling DSM item */

#endif /* DIAG_CFG_H */


