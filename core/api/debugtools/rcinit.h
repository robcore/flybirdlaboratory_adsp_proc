#ifndef RCINIT_H
#define RCINIT_H
/** vi: tw=128 ts=3 sw=3 et
@file rcinit.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcinit.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

// USE THE APPROPRIATE NHLOS HEADER FILE TO ACCESS THE API AS DEPENDENCY.
// DIRECT CLIENT DEPENDENCY THROUGH THIS HEADER FILE ALONE IS NOT A SUPPORTED
// OPERATION.

// #include "rcinit_dal.h"     // NHLOS DAL
// #include "rcinit_posix.h"   // NHLOS POSIX
// #include "rcinit_qurt.h"    // NHLOS QURT
// #include "rcinit_rex.h"     // NHLOS REX

#include "rcevt.h" // internal use, supplies RCEVT_SIGEX

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcinit_api @{ */

/**
API, Exposed Events for Observers
*/
#define RCINIT_RCECB_PREFIX                  ""                                  /**< prefix for rcinit events (localized protection domain) */
#define RCINIT_RCECB_INITGROUPS              RCINIT_RCECB_PREFIX "initgroups"    /**< observers ok */
#define RCINIT_RCECB_TERMGROUPS              RCINIT_RCECB_PREFIX "termgroups"    /**< observers ok */
#define RCINIT_RCEVT_PREFIX                  ""                                  /**< prefix for rcinit events (localized protection domain) */
#define RCINIT_RCEVT_INITGROUPS              RCINIT_RCEVT_PREFIX "initgroups"    /**< observers ok */
#define RCINIT_RCEVT_TERMGROUPS              RCINIT_RCEVT_PREFIX "termgroups"    /**< observers ok */

/**
API, Enumeration for Return Type
*/
typedef enum
{
   RCINIT_SUCCESS = 0,
   RCINIT_ERROR = -1

} RCINIT_RESULT;

#define RCINIT_NULL           ((void*)0)                                         /**< return result */
#define RCINIT_ZERO           (0)                                                /**< return result */

/**
API, Enumeration for Group Representation
*/
typedef enum
{
   RCINIT_GROUP_0 = 0,                                                           /**< internal representation group 0 */
   RCINIT_GROUP_1 = 1,                                                           /**< internal representation group 1 */
   RCINIT_GROUP_2 = 2,                                                           /**< internal representation group 2 */
   RCINIT_GROUP_3 = 3,                                                           /**< internal representation group 3 */
   RCINIT_GROUP_4 = 4,                                                           /**< internal representation group 4 */
   RCINIT_GROUP_5 = 5,                                                           /**< internal representation group 5 */
   RCINIT_GROUP_6 = 6,                                                           /**< internal representation group 6 */
   RCINIT_GROUP_7 = 7,                                                           /**< internal representation group 7 */
   RCINIT_GROUP_NONE = 8,
   RCINIT_GROUP_MAX = RCINIT_GROUP_NONE                                          /**< end of list (overloaded to NONE) */

} RCINIT_GROUP;

/**
API, Enumeration for Task/Function Type Representation
*/
typedef enum
{
   RCINIT_TASK_POLICYFN = 1,                                                     /**< policy function callbacks (not task) */
   RCINIT_TASK_INITFN = 2,                                                       /**< initialization function callbacks (not task) */
   RCINIT_TASK_TERMFN = 3,                                                       /**< termination function callbacks (not task) */
   RCINIT_TASK_DAL = 4,                                                          /**< dalsys tasks */
   RCINIT_TASK_POSIX = 5,                                                        /**< pthread tasks */
   RCINIT_TASK_QURT = 6,                                                         /**< qurt tasks */
   RCINIT_TASK_REX = 7,                                                          /**< rex tasks */
   RCINIT_TASK_LEGACY = 8,                                                       /**< deprecated rex tasks with feature guard (tmc) */
   RCINIT_TASK_NONE                                                              /**< end of list */

} RCINIT_TASK;

#define RCINIT_TASK_DALTASK   RCINIT_TASK_DAL                                    /**< Deprecated Alias */
#define RCINIT_TASK_QURTTASK  RCINIT_TASK_QURT                                   /**< Deprecated Alias */
#define RCINIT_TASK_REXTASK   RCINIT_TASK_REX                                    /**< Deprecated Alias */

/**
API, Task Priority Representation
*/
typedef short RCINIT_PRIO;

#define RCINIT_PRIO_MAX            (255)                                         /**< Priority HIGH = 255, to LOW = 1, mapping performed internally for nonhlos use */
#define RCINIT_PRIO_MIN            (1)                                           /**< Priority HIGH = 255, to LOW = 1, mapping performed internally for nonhlos use */
#define RCINIT_PRIO_NONE           (-1)                                          /**< Not Assigned */
#define RCINIT_PRIO_INITFN         (-2)                                          /**< Place Holder (not actual priority initfn run at) */
#define RCINIT_PRIO_POLICYFN       (-3)                                          /**< Place Holder (not actual priority policyfn run at) */

/**
API, Task Stack Size Representation
*/
typedef unsigned long RCINIT_STKSZ;                                              /**< Stack Size (KB) */

#define RCINIT_STKSZ_ZERO (0)                                                    /**< Zero Length Stack (Initialization Decision) */
#define RCINIT_STKSZ_NONE (-1)                                                   /**< No Stack (Initialization Decision) */

/**
API, Task CPU (Hardware Thread) Affinity Representation
*/
typedef unsigned char RCINIT_AFFINITY;                                           /**< Place holder; not all nonhlos kernel interfaces use this */

typedef void* RCINIT_ENTRY;                                                      /**< Entry Point */

typedef int RCINIT_POLICY;                                                       /**< Policy Filter Result */

#define RCINIT_POLICY_NONE                   (-1)
#define RCINIT_POLICY_NAME_DEFAULT           "default"                           /**< Maps to Arbitrary Placement at Runtime */

typedef void (*RCINIT_FNSIG_VOID_VOID)(void);                                    /**< Specific Function Signature */
typedef void* (*RCINIT_FNSIG_VOIDP_VOID)(void);                                  /**< Specific Function Signature */

typedef void* RCINIT_INFO;                                                       /**< Opaque Handle */
typedef const char* RCINIT_NAME;                                                 /**< Pointer to const char */

#define RCINIT_NAME_MAX 16                                                       /**< Tracks All NHLOS Maximum Task Name + NULL Terminator */

/**
API, Unique Identifier
*/
typedef unsigned long RCINIT_HASH;                                               /**< Unique Identifier */

/**
API, name to RCINIT_INFO Opaque handle
@param[in] name NULL terminated string, string identifier for task context
@returns
NULL -- Error
RCINIT_INFO -- Opaque handle representing an RCINIT_INFO object
*/
RCINIT_INFO rcinit_lookup(RCINIT_NAME name);

/**
API, RCINIT_INFO Opaque handle to name
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
NULL -- Error
RCINIT_NAME -- NULL terminated string, string identifier for task context
*/
RCINIT_NAME rcinit_lookup_name_info(RCINIT_INFO info);

/**
API, name to Policy Extension Inclusion (returns only First Occurance if Multiple)
@param[in] name NULL terminated string, string identifier for task context
@returns
RCINIT_POLICY -- Returns the Policy Representation
*/
RCINIT_POLICY rcinit_lookup_policy(RCINIT_NAME name);

/**
API, Current Policy Extension (eg, returns default)
@returns
RCINIT_POLICY -- Returns the Policy Representation
*/
RCINIT_POLICY rcinit_lookup_policy_current(void);

/**
API, name to Task Priority Provisioned at Compile Time
@param[in] name NULL terminated string, string identifier for task context
@returns
RCINIT_PRIO -- Returns the Priority Representation
*/
RCINIT_PRIO rcinit_lookup_prio(RCINIT_NAME name);

/**
API, RCINIT_INFO Opaque handle to Task Priority Provisioned at Compile Time
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
RCINIT_PRIO -- Returns the Priority Representation
*/
RCINIT_PRIO rcinit_lookup_prio_info(RCINIT_INFO info);

/**
API, name to Task Group Provisioned at Compile Time
@param[in] name NULL terminated string, string identifier for task context
@returns
RCINIT_GROUP -- Returns the Group Representation
*/
RCINIT_GROUP rcinit_lookup_group(RCINIT_NAME name);

/**
API, entry to Task Group Provisioned at Compile Time
@param[in] entry Address of entry point
@returns
RCINIT_GROUP -- Returns the Group Representation
*/
RCINIT_GROUP rcinit_lookup_group_entry(void* entry);

/**
API, Current group processing during initialization or termination
@returns
RCINIT_GROUP -- Returns the Group Representation
*/
RCINIT_GROUP rcinit_lookup_group_current(void);

/**
API, name to Task Stack Size Provisioned at Compile Time
@param[in] name NULL terminated string, string identifier for task context
@returns
unsigned long -- Returns the Stack Size Representation
*/
unsigned long rcinit_lookup_stksz(RCINIT_NAME name);

/**
API, RCINIT_INFO Opaque handle to Task Stack Size Provisioned at Compile Time
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
unsigned long -- Returns the Stack Size Representation
*/
unsigned long rcinit_lookup_stksz_info(RCINIT_INFO info);

/**
API, name to Pointer Provisioned at Compile Time Presense
@param[in] name NULL terminated string, string identifier for task context
@returns
NULL -- Netagive Query for Presense
void* -- Positive Query for Presense
*/
void* rcinit_lookup_entry(RCINIT_NAME name);

/**
API, RCINIT_INFO Opaque handle to Pointer Provisioned at Compile Time Presense
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
NULL -- Netagive Query for Presense
void* -- Positive Query for Presense
*/
void* rcinit_lookup_entry_info(RCINIT_INFO info);

/**
API, Required Handshake at Startup by All Tasks, Logical Barrier Rendevous
@returns
None.
*/
void rcinit_handshake_init(void);

/**
API, Required Handshake at Startup by All Tasks, Logical Barrier Rendevous (ALIAS)
@returns
None.
*/
void rcinit_handshake_startup(void);

/**
API, Required Handshake at Termination by Registered Tasks, Logical Barrier Rendevous
@returns
None.
*/
void rcinit_handshake_term(void);

/**
API, Required Handshake at Termination by Registered Tasks, Logical Barrier Rendevous (ALIAS)
@returns
None.
*/
void rcinit_handshake_shutdown(void);

/**
API, Runtime Termination Registeration by Tasks, General Interface required RCEVT SIGEX Setup
@param[in] type RCEVT SIGEX Notification Type
@param[in] sigex RCEVT SIGEX Type Specific Union
@returns
None.
*/
void rcinit_register_term(RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Runtime Termination Unegisteration by Tasks, General Interface required RCEVT SIGEX Setup
@param[in] type RCEVT SIGEX Notification Type
@param[in] sigex RCEVT SIGEX Type Specific Union
@returns
None.
*/
void rcinit_unregister_term(RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Runtime Termination Registeration by Tasks, General Interface required RCEVT SIGEX Setup
@param[in] group RCINIT Termination Group Enumeration
@param[in] type RCEVT SIGEX Notification Type
@param[in] sigex RCEVT SIGEX Type Specific Union
@returns
None.
*/
void rcinit_register_term_group(RCINIT_GROUP group, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Runtime Termination Unegisteration by Tasks, General Interface required RCEVT SIGEX Setup
@param[in] group RCINIT Termination Group Enumeration
@param[in] type RCEVT SIGEX Notification Type
@param[in] sigex RCEVT SIGEX Type Specific Union
@returns
None.
*/
void rcinit_unregister_term_group(RCINIT_GROUP group, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex);

/**
API, Runtime Termination Registeration by Functions
@param[in] fn RCINIT Callback Function
@returns
None.
*/
void rcinit_register_termfn(RCINIT_FNSIG_VOID_VOID fn);

/**
API, Runtime Termination Registeration by Functions
@param[in] group RCINIT Termination Group Enumeration
@param[in] fn RCINIT Callback Function
@returns
None.
*/
void rcinit_register_termfn_group(RCINIT_GROUP group, RCINIT_FNSIG_VOID_VOID fn);

/**
API, Runtime Termination Unegisteration by Functions
@param[in] group RCINIT Termination Group Enumeration
@param[in] fn RCINIT Callback Function
@returns
None.
*/
void rcinit_unregister_termfn_group(RCINIT_GROUP group, RCINIT_FNSIG_VOID_VOID fn);

/**
API, Highly Specialized Use Case to Start Tasks Before GROUP_0, Very Specialized
Use Case that is utilized by Timers to start their task before Functions of GROUP_0
are executed. This API is not intended for general technology area utilization.
@param[in] info_p RCINIT_INFO Opaque Handle
@param[in] entry Task Entry Point
@returns
None.
*/
void rcinit_initfn_spawn_task(RCINIT_INFO info_p, void* entry);

/** @} end_addtogroup rcinit_api */

#if defined(__cplusplus)
}
#endif

// DEPRECATED INTERFACE (A-FAMILY BACKWARDS COMPATIBILITY, REX ONLY API, USE RCINIT_REX.H INSTEAD)
#if !defined(IMAGE_ADSP_PROC) // REX API NOT PRESENT ON ADSP_PROC
#include "rcinit_rex.h" // not instrumented out; remove this when tech areas include the proper header file for rex.
#endif
// DEPRECATED INTERFACE (A-FAMILY BACKWARDS COMPATIBILITY, REX ONLY API, USE RCINIT_REX.H INSTEAD)

#endif
