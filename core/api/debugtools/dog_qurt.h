#ifndef DOG_QURT_H
#define DOG_QURT_H
/**
@file dog_qurt.h
@brief This file contains the API details for the Dog Services, API 2.0
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
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/dog_qurt.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdint.h"

#include "qurt.h"
#include "qurt_qdi_driver.h"
#include "timer.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** TWO INTERFACES SUPPLIED : DOG_SW, DOG_HB */

/** @addtogroup dog_api @{ */

typedef enum
{
   DOG_SW_STATUS_SUCCESS = 0,                                                    /**< SUCCESS INDICATION, evaluates as >= DOG_SW_STATUS_SUCCESS */
   DOG_SW_STATUS_ERROR = -1                                                      /**< FAILURE INDICATION, evaluates as < DOG_SW_STATUS_SUCCESS */

} DOG_SW_STATUS;                                                                 /**< API, Status Result to Caller */

typedef int32_t DOG_SW_HANDLE;

typedef enum
{
   DOG_HB_STATUS_SUCCESS = 0,                                                    /**< SUCCESS INDICATION, evaluates as >= DOG_HB_STATUS_SUCCESS */
   DOG_HB_STATUS_ERROR = -1                                                      /**< FAILURE INDICATION, evaluates as < DOG_HB_STATUS_SUCCESS */

} DOG_HB_STATUS;                                                                 /**< API, Status Result to Caller */

typedef int32_t DOG_HB_HANDLE;

typedef enum
{
   DOG_HB_SIG_REXSIGNAL = 1,                                                     /**< Argument Supplied for REX API */
   DOG_HB_SIG_ANYSIGNAL = 2                                                      /**< Arguments Supplied for QURT ANYSIGNAL API */

} DOG_HB_SIG;

/**
API, dog_sw_init
@param[in]     char*                       NULL Terminated Device Name
#param[in]     unsigned int                  Device Operation Parameter
@return        DOG_SW_HANDLE                 Opaque Device Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1, 2)))
#endif
DOG_SW_HANDLE dog_sw_init(char const* name, time_timetick_type* timeout);

/**
API, dog_sw_destroy
@param[in]     DOG_SW_HANDLE                 Opaque Device Handle
@return        DOG_SW_STATUS                 Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
DOG_SW_STATUS dog_sw_destroy(DOG_SW_HANDLE handle);

/**
API, dog_sw_pong

@param[in]     DOG_SW_HANDLE                 Opaque Device Handle
@return        DOG_SW_STATUS                 Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
DOG_SW_STATUS dog_sw_report(DOG_SW_HANDLE handle);

/**
API, dog_sw_report_check

@param[in]     DOG_SW_HANDLE                 Opaque Device Handle
@return        DOG_SW_STATUS                 Error Indication
*/
//#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
//__attribute__((warn_unused_result))
//#endif
//DOG_SW_STATUS dog_sw_report_check(DOG_SW_HANDLE handle);

/**
API, dog_hb_init
@param[in]     char*                       NULL Terminated Device Name
@param[in]     DOG_HB_SIG                    Parameter
@param[in]     void*                         Parameter
@param[in]     unsigned int                  Parameter
@return        DOG_HB_HANDLE                 Opaque Device Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1, 3)))
#endif
DOG_HB_HANDLE dog_hb_init(char const* name, DOG_HB_SIG sig_t, void* sig_p, unsigned int sig_m);

/**
API, dog_hb_destroy
@param[in]     DOG_HB_HANDLE                 Opaque Device Handle
@return        DOG_HB_STATUS                 Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
DOG_HB_STATUS dog_hb_destroy(DOG_HB_HANDLE handle);

/**
API, dog_hb_pong

@param[in]     DOG_HB_HANDLE                 Opaque Device Handle
@return        DOG_HB_STATUS                 Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
DOG_HB_STATUS dog_hb_pong(DOG_HB_HANDLE handle);

// LEGACY API: Compatibility

typedef unsigned int dog_report_type;                                            /**< Represents the handle used in the Legacy DOG API */

/** @} end_addtogroup dog_api */

#if defined(__cplusplus)
}
#endif

#endif
