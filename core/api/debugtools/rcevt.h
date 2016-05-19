#ifndef RCEVT_H
#define RCEVT_H
/** vi: tw=128 ts=3 sw=3 et
@file rcevt.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

// USE THE APPROPRIATE NHLOS HEADER FILE TO ACCESS THE API AS DEPENDENCY.
// DIRECT CLIENT DEPENDENCY THROUGH THIS HEADER FILE ALONE IS NOT A SUPPORTED
// OPERATION.

// #include "rcevt_dal.h"     // NHLOS DAL
// #include "rcevt_posix.h"   // NHLOS POSIX
// #include "rcevt_qurt.h"    // NHLOS QURT
// #include "rcevt_rex.h"     // NHLOS REX

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

/**
API, Typedefs and Enumerations
*/
typedef char const* RCEVT_NAME;                                                  /**< Name */
typedef void* RCEVT_HANDLE;                                                      /**< Opaque Handle */
typedef enum {RCEVT_FALSE, RCEVT_TRUE } RCEVT_BOOL;                              /**< Boolean Query Return */
typedef unsigned long RCEVT_THRESHOLD;                                           /**< Threshold */

/**
API, Enumeration of Supported Notification Types
*/
typedef enum
{
   RCEVT_SIGEX_TYPE_CALLBACK,                                                    /**< Type RCECB (Shares Pool, Use RCECB API) */
   RCEVT_SIGEX_TYPE_SIGDAL,                                                      /**< Type RCEVT DAL */
   RCEVT_SIGEX_TYPE_SIGPOSIX,                                                    /**< Type RCEVT POSIX */
   RCEVT_SIGEX_TYPE_SIGQURT,                                                     /**< Type RCEVT QURT */
   RCEVT_SIGEX_TYPE_SIGQURT_USER,                                                /**< Type RCEVT QURT USER_PD */
   RCEVT_SIGEX_TYPE_SIGREX,                                                      /**< Type RCEVT REX */
   RCEVT_SIGEX_TYPE_NONE                                                         /**< None */

} RCEVT_SIGEX_TYPE;

typedef void* RCEVT_SIGEX;                                                       /**< Opaque Handle to Abstracted Event Notification Structures */

#define RCEVT_NULL ((void*)0)                                                    /**< ISO/ANSI-C, Forward reference NULL pointer */

/**
API, Service initialization
@param
None
@return
None
*/
void rcevt_init(void);

/**
API, Service termination
@param
None
@return
None
*/
void rcevt_term(void);

/**
API, Create an event, with name

Prerequsite call before posting event -- create the event
before use to avoid a potential "race condition" between
contexts that will post the event and concurrently wait on
the event being posted.

For performance, cache the resulting handle for use within
the API. Name based use cases will take a penalty when doing
a dictionary lookup on every call.

@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_create_name(RCEVT_NAME const name);

/**
API, Search an event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_BOOL -- Boolean reflecting event previously created
*/
RCEVT_BOOL rcevt_search_handle(RCEVT_HANDLE const handle);

/**
API, Search an event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_BOOL -- Boolean reflecting event previously created
*/
RCEVT_BOOL rcevt_search_name(RCEVT_NAME const name);

/**
API, Count of registrants for event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
int -- Count of registrants for specific event
*/
int rcevt_getcontexts_handle(RCEVT_HANDLE const handle);

/**
API, Count of registrants for event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
int -- Count of registrants for specific event
*/
int rcevt_getcontexts_name(RCEVT_NAME const name);

/**
API, Count of times event signaled, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_THRESHOLD -- Count of registrants for specific event
*/
RCEVT_THRESHOLD rcevt_getcount_handle(RCEVT_HANDLE const handle);

/**
API, Count of times event signaled, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_THRESHOLD -- Count of registrants for specific event
*/
RCEVT_THRESHOLD rcevt_getcount_name(RCEVT_NAME const name);

/**
API, Register notification to event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_sigex_handle(RCEVT_HANDLE const handle, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX signal);

/**
API, Register notification to event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_sigex_name(RCEVT_NAME const name, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX signal);

/**
API, Unegister notification to event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_sigex_handle(RCEVT_HANDLE const handle, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Unegister notification to event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_sigex_name(RCEVT_NAME const name, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Signal event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_signal_handle(RCEVT_HANDLE const handle);

/**
API, Signal event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_signal_name(RCEVT_NAME const name);

/**
API, Wait for event at specific threshold, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] threshold Notification begins with threshold and continues until unregistered
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_sigex_handle(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Wait for event at specific threshold, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] threshold Notification begins with threshold and continues until unregistered
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_sigex_name(RCEVT_NAME const name, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Wait for event, one time per call, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_handle(RCEVT_HANDLE const handle);

/**
API, Wait for event, one time per call, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_name(RCEVT_NAME const name);

/**
API, Wait for event, one time per call, until threshold met, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_count_handle(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold);

/**
API, Wait for event, one time per call, until threshold met, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_count_name(RCEVT_NAME const name, RCEVT_THRESHOLD threshold);

/**
The following function signatures should not be used. The correct dependency
mechanism is to use RCEVT_REX.H supplied API. These functions cannot be universal.
*/
typedef unsigned long RCEVT_SIGNAL;                                              /**< Deprecated API, Use RCEVT_REX.H */
RCEVT_HANDLE rcevt_register_handle(RCEVT_HANDLE const handle, RCEVT_SIGNAL signal); /**< Deprecated API, Use RCEVT_REX.H */
RCEVT_HANDLE rcevt_register_name(RCEVT_NAME const name, RCEVT_SIGNAL signal);    /**< Deprecated API, Use RCEVT_REX.H */

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
