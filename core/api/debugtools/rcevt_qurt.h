#ifndef RCEVT_QURT_H
#define RCEVT_QURT_H
/** vi: tw=128 ts=3 sw=3 et
@file rcevt_qurt.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt_qurt.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "qurt.h"
#include "rcevt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

////////////////////////////////////////
// REGISTER
////////////////////////////////////////

// qurt_anysignal_t client_qurt_signal;
// qurt_anysignal_init(&client_qurt_signal);
//
// if (RCEVT_NULL == rcevt_register_name_qurt(CLIENT_EVENTNAME, &client_qurt_signal, CLIENT_QURT_SIGNAL_MASK))
// {
// MSG("error"); // handle error
// }

////////////////////////////////////////
// BLOCKING WAIT
////////////////////////////////////////

// unsigned int recv = qurt_anysignal_wait(&qurt_signal, CLIENT_QURT_SIGNAL_MASK);
// if (0 != (recv & RCEVT_QURT_SIGNAL_MASK))
// {
// MSG("event handler");
// }

////////////////////////////////////////
// UNREGISTER
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_unregister_name_qurt(CLIENT_EVENTNAME, &client_qurt_signal, CLIENT_QURT_SIGNAL_MASK))
// {
// MSG("error"); // handle error
// }
//
// qurt_anysignal_destroy(&qurt_signal);

////////////////////////////////////////
// SIGNAL FROM OTHER CONTEXT
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_create_name(CLIENT_EVENTNAME)) // Prior to Use
// {
// MSG("error"); // handle error
// }

// if (RCEVT_NULL == rcevt_signal_name(CLIENT_EVENTNAME))
// {
// MSG("error"); // handle error
// }

/**
API, NHLOS Specific Structure
*/
typedef struct
{
   qurt_anysignal_t* signal;
   unsigned int mask;

} RCEVT_SIGEX_SIGQURT;

/**
API, Register notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_handle_qurt(RCEVT_HANDLE const handle, qurt_anysignal_t* signal, unsigned int mask);

/**
API, Register notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_name_qurt(RCEVT_NAME const name, qurt_anysignal_t* signal, unsigned int mask);

/**
API, Unegister notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_handle_qurt(RCEVT_HANDLE const handle, qurt_anysignal_t* signal, unsigned int mask);

/**
API, Unegister notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@param[in] mask Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_name_qurt(RCEVT_NAME const name, qurt_anysignal_t* signal, unsigned int mask);

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
