#ifndef RCECB_H
#define RCECB_H
/** vi: tw=128 ts=3 sw=3 et
@file rcecb.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcecb.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

/**
API, Typedefs and Enumerations
*/
typedef char const* RCECB_NAME;                                                  /**< Name */
typedef void* RCECB_HANDLE;                                                      /**< Opaque Handle */
typedef enum {RCECB_FALSE, RCECB_TRUE } RCECB_BOOL;                              /**< Boolean Query Return */
typedef unsigned long RCECB_THRESHOLD;                                           /**< Threshold */
typedef void (*RCECB_FNSIG_VOID_VOID)(void);                                     /**< Specific Function Signature */
typedef void* RCECB_CONTEXT;                                                     /**< Unique Function Pointer */

#define RCECB_NULL ((void*)0)                                                    /**< ISO/ANSI-C, Forward reference NULL pointer */

/**
API, Service initialization
@param
None
@return
None
*/
void rcecb_init(void);

/**
API, Service termination
@param
None
@return
None
*/
void rcecb_term(void);

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
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_create_name(RCECB_NAME const name);

/**
API, Search an event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_context_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context);

/**
API, Search an event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_context_name(RCECB_NAME const name, RCECB_CONTEXT const context);

/**
API, Search an event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_handle(RCECB_HANDLE const handle);

/**
API, Search an event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_name(RCECB_NAME const name);

/**
API, Count of registrants for event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
int -- Count of registrants for specific event
*/
int rcecb_getcontexts_handle(RCECB_HANDLE const handle);

/**
API, Count of registrants for event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
int -- Count of registrants for specific event
*/
int rcecb_getcontexts_name(RCECB_NAME const name);

/**
API, Count of times event signaled, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
RCECB_THRESHOLD -- Count of registrants for specific event
*/
RCECB_THRESHOLD rcecb_getcount_handle(RCECB_HANDLE const handle);

/**
API, Count of times event signaled, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
RCECB_THRESHOLD -- Count of registrants for specific event
*/
RCECB_THRESHOLD rcecb_getcount_name(RCECB_NAME const name);

/**
API, Register callback to event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_register_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context);
#define rcecb_register_context_handle rcecb_register_handle

/**
API, Register callback to event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_register_name(RCECB_NAME const name, RCECB_CONTEXT const context);
#define rcecb_register_context_name rcecb_register_name

/**
API, Unegister callback to event, with handle
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_unregister_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context);
#define rcecb_unregister_context_handle rcecb_unregister_handle

/**
API, Unegister callback to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_unregister_name(RCECB_NAME const name, RCECB_CONTEXT const context);
#define rcecb_unregister_context_name rcecb_unregister_name

/**
API, Signal event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_signal_handle(RCECB_HANDLE const handle);

/**
API, Signal event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_signal_name(RCECB_NAME const name);

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
