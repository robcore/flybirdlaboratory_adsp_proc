/**
@file rcevt_qurt.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_qurt.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcevt_qurt.h"
#include "rcevt_internal.h"

/**
API, Register notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_handle_qurt(RCEVT_HANDLE const handle, qurt_anysignal_t* signal, unsigned int mask)
{
   RCEVT_SIGEX_SIGQURT rcevt_sigex;
   rcevt_sigex.signal = signal;
   rcevt_sigex.mask = mask;
   return rcevt_register_sigex_handle(handle, RCEVT_SIGEX_TYPE_SIGQURT, &rcevt_sigex);
}

/**
API, Register notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_name_qurt(RCEVT_NAME const name, qurt_anysignal_t* signal, unsigned int mask)
{
   RCEVT_SIGEX_SIGQURT rcevt_sigex;
   rcevt_sigex.signal = signal;
   rcevt_sigex.mask = mask;
   return rcevt_register_sigex_name(name, RCEVT_SIGEX_TYPE_SIGQURT, &rcevt_sigex);
}

/**
API, Unegister notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_handle_qurt(RCEVT_HANDLE const handle, qurt_anysignal_t* signal, unsigned int mask)
{
   RCEVT_SIGEX_SIGQURT rcevt_sigex;
   rcevt_sigex.signal = signal;
   rcevt_sigex.mask = mask;
   return rcevt_unregister_sigex_handle(handle, RCEVT_SIGEX_TYPE_SIGQURT, &rcevt_sigex);
}

/**
API, Unegister notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_name_qurt(RCEVT_NAME const name, qurt_anysignal_t* signal, unsigned int mask)
{
   RCEVT_SIGEX_SIGQURT rcevt_sigex;
   rcevt_sigex.signal = signal;
   rcevt_sigex.mask = mask;
   return rcevt_unregister_sigex_name(name, RCEVT_SIGEX_TYPE_SIGQURT, &rcevt_sigex);
}
