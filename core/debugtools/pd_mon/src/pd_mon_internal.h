#ifndef PD_MON_INTERNAL_H
#define PD_MON_INTERNAL_H
/** vi: tw=128 ts=3 sw=3 et
@file pd_mon_internal.h
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2012 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/pd_mon/src/pd_mon_internal.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "err.h"
#include "msg.h"
#include "rcinit_qurt.h"

#include "pd_dump.h"

#include "stdarg.h"
#include "stdlib.h"
#include "stringl/stringl.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define PD_MON_MAX_PD         32
#define PD_MON_NAME_MAX       64                                     // Maximum Managed PD Name Length
#define PD_MON_STACK_SIZ      1024                                   // Maximum Stack Consumption for Each Program Monitor

#define PD_MON_SIG_UNLOCK     0x00000001                             // Signal Mask

typedef struct
{
   int cid;                                                          // Child Id of last qurt_spawn
   char name[PD_MON_NAME_MAX];                                       // PD Name
   PD_MON_RESTART restart;                                           // Restart Count
   int wid;                                                          // Child Id of last qurt_wait
   int status;                                                       // Status return of last qurt_wait

} PD_MON_STATUS_T, *PD_MON_STATUS_P;

#define PD_MON_STATUS_NO_CID -1

typedef struct
{
   qurt_mutex_t mutex;                                               // Concurrency Mutex

   int handle;                                                       // Dump Device Handle

} pd_mon_internal_user_t;

extern pd_mon_internal_user_t pd_mon_internal_user;

typedef struct
{
   qurt_mutex_t mutex;                                               // Concurrency Mutex
   qurt_anysignal_t signal;                                          // Concurrency Signal

   PD_MON_STATUS_P args_handle;                                      // Opaque Handle Return from Domain Monitor to API Callee (Mutex Protected for Concurrency)
   PD_MON_RESTART args_restart;                                      // (Mutex Protected for Concurrency)

   PD_MON_STATUS_T status[PD_MON_MAX_PD];                            // PD Monitor Status Array

} pd_mon_internal_t;

extern pd_mon_internal_t pd_mon_internal;

extern const char* pd_mon_internal_prefix;

extern const char* pd_mon_internal_basename;

// Function Signatures

#if defined(__cplusplus)
}
#endif

#endif
