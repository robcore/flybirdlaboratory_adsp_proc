#ifndef RCEVT_POSIX_H
#define RCEVT_POSIX_H
/** vi: tw=128 ts=3 sw=3 et
@file rcevt_posix.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt_posix.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "pthread.h"
#include "rcevt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

////////////////////////////////////////
// REGISTER
////////////////////////////////////////

// pthread_mutex_t client_mutex;
// pthread_cond_t client_cond;
//
// pthread_mutex_init(&client_mutex, NULL);
// pthread_cond_init(&client_cond, NULL);
//
// if (RCEVT_NULL == rcevt_register_name_posix(CLIENT_EVENTNAME, &client_cond, &client_mutex))
// {
// MSG("error"); // handle error
// }

////////////////////////////////////////
// BLOCKING WAIT
////////////////////////////////////////

// pthread_mutex_lock(&client_mutex);
// pthread_cond_wait(&client_cond, &client_mutex);
// pthread_mutex_unlock(&client_mutex);
//
// MSG("event handler");

////////////////////////////////////////
// UNREGISTER
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_unregister_name_posix(CLIENT_EVENTNAME, &client_cond, &client_mutex))
// {
// MSG("error"); // handle error
// }
//
// pthread_cond_destroy(&client_cond);
// pthread_mutex_destroy(&client_mutex);

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
   pthread_mutex_t* mutex_p;
   pthread_cond_t* cond_p;

} RCEVT_SIGEX_SIGPOSIX;

/**
API, Register notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] cond_p Notification NHLOS specific notification information
@param[in] mutex_p Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_handle_posix(RCEVT_HANDLE const handle, pthread_cond_t* cond_p, pthread_mutex_t* mutex_p);

/**
API, Register notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] cond_p Notification NHLOS specific notification information
@param[in] mutex_p Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_name_posix(RCEVT_NAME const name, pthread_cond_t* cond_p, pthread_mutex_t* mutex_p);

/**
API, Unegister notification to event, with handle
@param[in] handle Opaque handle of the event
@param[in] cond_p Notification NHLOS specific notification information
@param[in] mutex_p Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_handle_posix(RCEVT_HANDLE const handle, pthread_cond_t* cond_p, pthread_mutex_t* mutex_p);

/**
API, Unegister notification to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] cond_p Notification NHLOS specific notification information
@param[in] mutex_p Notification NHLOS specific notification information
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_name_posix(RCEVT_NAME const name, pthread_cond_t* cond_p, pthread_mutex_t* mutex_p);

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
