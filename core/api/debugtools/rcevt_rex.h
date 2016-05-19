#ifndef RCEVT_REX_H
#define RCEVT_REX_H
/** vi: tw=128 ts=3 sw=3 et
@file rcevt_rex.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt_rex.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rex.h"
#include "rcevt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

////////////////////////////////////////
// REGISTER
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_register_name_rex(CLIENT_EVENTNAME, CLIENT_REX_SIGNAL_MASK))
// {
// MSG("error"); // handle error
// }

////////////////////////////////////////
// BLOCKING WAIT
////////////////////////////////////////

// rex_sigs_type recv = rex_wait(CLIENT_REX_SIGNAL_MASK);
// if (0 != (recv & CLIENT_REX_SIGNAL_MASK))
// {
// MSG("event handler");
// }

////////////////////////////////////////
// UNREGISTER
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_unregister_name_rex(CLIENT_EVENTNAME, CLIENT_REX_SIGNAL_MASK))
// {
// MSG("error"); // handle error
// }

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
   rex_tcb_type* signal;
   rex_sigs_type mask;

} RCEVT_SIGEX_SIGREX;

/**
API, Register notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_handle_rex(RCEVT_HANDLE const handle, rex_sigs_type signal);
//#define rcevt_register_handle rcevt_register_handle_rex

/**
API, Register notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_name_rex(RCEVT_NAME const name, rex_sigs_type signal);
//#define rcevt_register_name rcevt_register_name_rex

/**
API, Unegister notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_handle_rex(RCEVT_HANDLE const handle, rex_sigs_type signal);

/**
API, Unegister notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] signal Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_name_rex(RCEVT_NAME const name, rex_sigs_type signal);

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
