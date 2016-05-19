/**
@file rcevt_rex.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_rex.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcevt_rex.h"
#include "rcevt_internal.h"

/**
The following function signature should not be used. The correct dependency
mechanism is to use RCEVT_REX.H supplied API.
*/
RCEVT_HANDLE rcevt_register_handle(RCEVT_HANDLE const handle, RCEVT_SIGNAL signal) /**< Deprecated API, Use RCEVT_REX.H */
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = (rex_sigs_type)signal;
   return rcevt_register_sigex_handle(handle, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}

/**
The following function signature should not be used. The correct dependency
mechanism is to use RCEVT_REX.H supplied API.
*/
RCEVT_HANDLE rcevt_register_name(RCEVT_NAME const name, RCEVT_SIGNAL signal)     /**< Deprecated API, Use RCEVT_REX.H */
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = (rex_sigs_type)signal;
   return rcevt_register_sigex_name(name, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}

/**
API, Register notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_handle_rex(RCEVT_HANDLE const handle, rex_sigs_type signal)
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = signal;
   return rcevt_register_sigex_handle(handle, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}

/**
API, Register notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_name_rex(RCEVT_NAME const name, rex_sigs_type signal)
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = signal;
   return rcevt_register_sigex_name(name, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}

/**
API, Unegister notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_handle_rex(RCEVT_HANDLE const handle, rex_sigs_type signal)
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = signal;
   return rcevt_unregister_sigex_handle(handle, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}

/**
API, Unegister notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_name_rex(RCEVT_NAME const name, rex_sigs_type signal)
{
   RCEVT_SIGEX_SIGREX rcevt_sigex;
   rcevt_sigex.signal = rex_self();
   rcevt_sigex.mask = signal;
   return rcevt_unregister_sigex_name(name, RCEVT_SIGEX_TYPE_SIGREX, &rcevt_sigex);
}
