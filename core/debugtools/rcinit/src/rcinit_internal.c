/** vi: tw=128 ts=3 sw=3 et
@file rcinit_internal.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_internal.c#1 $
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

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

RCXH_DEF(RCXH_RCINIT);                                                           /**< Exception Base Class */
RCXH_DEFSUB(RCXH_RCINIT_TASK, RCXH_RCINIT);                                      /**< Exception Task Class */
RCXH_DEFSUB(RCXH_RCINIT_TASK_END, RCXH_RCINIT_TASK);                             /**< Specific Exception */
RCXH_DEFSUB(RCXH_RCINIT_TASK_RESTART, RCXH_RCINIT_TASK);                         /**< Specific Exception */

const RCECB_NAME rcinit_init_rcecb[RCINIT_GROUP_MAX] =
{
   RCINIT_RCECB_INIT_GROUP_0, RCINIT_RCECB_INIT_GROUP_1, RCINIT_RCECB_INIT_GROUP_2, RCINIT_RCECB_INIT_GROUP_3,
   RCINIT_RCECB_INIT_GROUP_4, RCINIT_RCECB_INIT_GROUP_5, RCINIT_RCECB_INIT_GROUP_6, RCINIT_RCECB_INIT_GROUP_7
};

const RCECB_NAME rcinit_term_rcecb[RCINIT_GROUP_MAX] =
{
   RCINIT_RCECB_TERM_GROUP_0, RCINIT_RCECB_TERM_GROUP_1, RCINIT_RCECB_TERM_GROUP_2, RCINIT_RCECB_TERM_GROUP_3,
   RCINIT_RCECB_TERM_GROUP_4, RCINIT_RCECB_TERM_GROUP_5, RCINIT_RCECB_TERM_GROUP_6, RCINIT_RCECB_TERM_GROUP_7
};

const RCEVT_NAME rcinit_init_rcevt[RCINIT_GROUP_MAX] =
{
   RCINIT_RCEVT_INIT_GROUP_0, RCINIT_RCEVT_INIT_GROUP_1, RCINIT_RCEVT_INIT_GROUP_2, RCINIT_RCEVT_INIT_GROUP_3,
   RCINIT_RCEVT_INIT_GROUP_4, RCINIT_RCEVT_INIT_GROUP_5, RCINIT_RCEVT_INIT_GROUP_6, RCINIT_RCEVT_INIT_GROUP_7
};

const RCEVT_NAME rcinit_term_rcevt[RCINIT_GROUP_MAX] =
{
   RCINIT_RCEVT_TERM_GROUP_0, RCINIT_RCEVT_TERM_GROUP_1, RCINIT_RCEVT_TERM_GROUP_2, RCINIT_RCEVT_TERM_GROUP_3,
   RCINIT_RCEVT_TERM_GROUP_4, RCINIT_RCEVT_TERM_GROUP_5, RCINIT_RCEVT_TERM_GROUP_6, RCINIT_RCEVT_TERM_GROUP_7
};

const RCINIT_NAME rcinit_swe_name_init[RCINIT_GROUP_MAX] =
{
   "RCINIT_SWE_INIT_GROUP_0", "RCINIT_SWE_INIT_GROUP_1", "RCINIT_SWE_INIT_GROUP_2", "RCINIT_SWE_INIT_GROUP_3",
   "RCINIT_SWE_INIT_GROUP_4", "RCINIT_SWE_INIT_GROUP_5", "RCINIT_SWE_INIT_GROUP_6", "RCINIT_SWE_INIT_GROUP_7"
};

const RCINIT_NAME rcinit_swe_name_term[RCINIT_GROUP_MAX] =
{
   "RCINIT_SWE_TERM_GROUP_0", "RCINIT_SWE_TERM_GROUP_1", "RCINIT_SWE_TERM_GROUP_2", "RCINIT_SWE_TERM_GROUP_3",
   "RCINIT_SWE_TERM_GROUP_4", "RCINIT_SWE_TERM_GROUP_5", "RCINIT_SWE_TERM_GROUP_6", "RCINIT_SWE_TERM_GROUP_7"
};

#if defined(RCINIT_TRACER_SWEVT)
const tracer_event_id_t rcinit_swe_event_init[RCINIT_GROUP_MAX] =
{
   RCINIT_SWE_INIT_GROUP_0, RCINIT_SWE_INIT_GROUP_1, RCINIT_SWE_INIT_GROUP_2, RCINIT_SWE_INIT_GROUP_3,
   RCINIT_SWE_INIT_GROUP_4, RCINIT_SWE_INIT_GROUP_5, RCINIT_SWE_INIT_GROUP_6, RCINIT_SWE_INIT_GROUP_7
};
#endif

#if defined(RCINIT_TRACER_SWEVT)
const tracer_event_id_t rcinit_swe_event_term[RCINIT_GROUP_MAX] =
{
   RCINIT_SWE_TERM_GROUP_0, RCINIT_SWE_TERM_GROUP_1, RCINIT_SWE_TERM_GROUP_2, RCINIT_SWE_TERM_GROUP_3,
   RCINIT_SWE_TERM_GROUP_4, RCINIT_SWE_TERM_GROUP_5, RCINIT_SWE_TERM_GROUP_6, RCINIT_SWE_TERM_GROUP_7
};
#endif

// Compile Time Defaults

// Use of RCINIT_DALCFG to Alter Defaults; Changes are not
// performed in the source module. IMAGE Owner will supply
// rcinit_dalcfg.xml at IMAGE_ROOT to modify runtime
// behavior.

long rcinit_term_err_fatal = 0;

long rcinit_term_latency_enable = 0;

long rcinit_term_timeout = 8500;

unsigned long rcinit_term_tmo[RCINIT_GROUP_MAX] =
{
   2000,                                                                         // RCINIT_GROUP_0
   250,                                                                          // RCINIT_GROUP_1
   250,                                                                          // RCINIT_GROUP_2
   250,                                                                          // RCINIT_GROUP_3
   250,                                                                          // RCINIT_GROUP_4
   250,                                                                          // RCINIT_GROUP_5
   250,                                                                          // RCINIT_GROUP_6
   5000                                                                          // RCINIT_GROUP_7
};

struct rcinit_internal_s rcinit_internal;                                        // Internal Runtime Instruments
