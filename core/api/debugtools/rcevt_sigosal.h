#ifndef RCEVT_SIGOSAL_H
#define RCEVT_SIGOSAL_H
/**
@file rcevt_sigosal.h
@brief This file contains the API for the Run Control Event Notification, API 1.0
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt_sigosal.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
===============================================================================*/

// DEPRECATED AND UNSUPPORTED
// REMEDIATION: REMOVE REFERENCES TO THIS HEADER FILE, USE RCEVT_REX.H INSTEAD

//#if defined(__GNUC__)
//#pragma message "NHLOS API, DEPRECATED AND UNSUPPORTED, Use RCEVT_REX.H instead"
//#elif defined(__ARMCC_VERSION)
//#pragma diag_remark 1215
//#warning "NHLOS API, DEPRECATED AND UNSUPPORTED, Use RCEVT_REX.H instead"
//#endif

#include "rcevt_rex.h"

#define RCEVT_SIGEX_SIGOSAL RCEVT_SIGEX_SIGREX
#define RCEVT_SIGEX_TYPE_SIGOSAL RCEVT_SIGEX_TYPE_SIGREX

#endif
