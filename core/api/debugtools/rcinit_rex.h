#ifndef RCINIT_REX_H
#define RCINIT_REX_H
/** vi: tw=128 ts=3 sw=3 et
@file rcinit_rex.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcinit_rex.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

// USE THE APPROPRIATE NHLOS HEADER FILE TO ACCESS THE API AS DEPENDENCY.

// #include "rcinit_dal.h"     // NHLOS DAL
// #include "rcinit_posix.h"   // NHLOS POSIX
// #include "rcinit_qurt.h"    // NHLOS QURT
// #include "rcinit_rex.h"     // NHLOS REX

#include "rex.h"

#include "rcxh.h"
#include "rcecb.h"
#include "rcevt_rex.h"
#include "rcinit.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcinit_api @{ */

/**
API, Routine maps NHLOS task context identifier to RCINIT_INFO Opaque handle
@param[in] tid NHLOS task context identifier
@returns
NULL -- Error
RCINIT_INFO -- Opaque handle representing an RCINIT_INFO object
*/
RCINIT_INFO rcinit_lookup_info_rextask(rex_tcb_type* tid);

/**
API, Routine maps NHLOS task context identifier to RCINIT_INFO Opaque handle
@param[in] tid NHLOS task context identifier
@returns
RCINIT_GROUP -- Enumeration represents startup group for NHLOS tid
*/
RCINIT_GROUP rcinit_lookup_group_rextask(rex_tcb_type* tid);

/**
API, Routine maps NHLOS task name to RCINIT_INFO Opaque handle
@param[in] name NULL terminated string, string identifier for task context
@returns
rex_tcb_type* -- NHLOS task context identifier
*/
rex_tcb_type* rcinit_lookup_rextask(RCINIT_NAME name);

/**
API, Routine maps RCINIT_INFO Opaque handle to NHLOS task context identifier
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
rex_tcb_type* -- NHLOS task context identifier
*/
rex_tcb_type* rcinit_lookup_rextask_info(RCINIT_INFO info);

/** @} end_addtogroup rcinit_api */

#if defined(__cplusplus)
}
#endif

#endif
