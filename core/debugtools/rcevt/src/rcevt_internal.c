/**
@file rcevt_internal.c
@brief This file contains the API for the Run Control Event Notification, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_internal.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcevt.h"
#include "rcevt_internal.h"

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

struct rce_internal_s rce_internal;
rce_nfy_pool_t rce_nfy_pool_static;                                              // first pool static storage
rce_nde_pool_t rce_nde_pool_static;                                              // first pool static storage
rce_nde_p rce_hashtab[RCEVT_HASHTABLE_BUCKETS];                                  // hashtable lookup buckets
