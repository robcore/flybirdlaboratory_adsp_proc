/*========================================================================
 $Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/utils/inc/algo_logging.h#3 $

 Edit History

 when       who     what, where, why
 --------   ---     -------------------------------------------------------
 7/22/2014   rv       Created

 ==========================================================================*/

/*-----------------------------------------------------------------------
 This file contains Algorithm logging related apis.

 Copyright (c) 2012-2015 Qualcomm  Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 -----------------------------------------------------------------------*/

#ifndef _ALGO_LOGGING_H_
#define _ALGO_LOGGING_H_

/*==========================================================================
 Include files
 ========================================================================== */
#include "qurt_elite_types.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

/*==========================================================================
 Macro Defines
 ========================================================================== */

typedef struct algo_data_logging_t algo_data_logging_t;

/**
 * This function initializes logging for algo tuning variables
 *
 */
ADSPResult algo_data_logging_init(algo_data_logging_t **algo_data_logging_pptr);

/**
 * This function deinitializes logging for algo tuning variables
 *
 *
 */
void algo_data_logging_deinit(algo_data_logging_t **algo_data_logging_pptr);

/**
 * This function is for registering for logging algo tuning variables
 *
 * @param[in] log_interval_in_ms logging interval in milli sec 
 * @param[in] log_size logging size in bytes
 * @param[in] client_handle_ptr pointer to the client handle
 *  	 pointer
 * @return ADSPResult, retuns success or failure
 *
 */
ADSPResult algo_data_logging_register(algo_data_logging_t *algo_data_logging_ptr,
                                      uint16_t log_interval_in_ms,
                                      uint16_t log_commit_interval_in_ms,
                                      uint32_t log_size,
                                      uint32_t log_code,
                                      uint32_t *client_handle_ptr);

/**
 * This function is for deregistering for logging algo tuning 
 * variabls 
 *
 * @param[in] client_handle_ptr client handle pointer 
 * @return ADSPResult, retuns success or failure
 *
 */
ADSPResult algo_data_logging_deregister(algo_data_logging_t *algo_data_logging_ptr,
                                        uint32_t client_handle);

/**
 * This function does the logging for algo tuning variables
 *
 * @param[in] log_buffer Ptr to the buffer to be logged. 
 * @param[in] log_size logging size in bytes 
 * @param[in] client_handle_ptr client handle pointer 
 *  
 */
ADSPResult algo_data_log_now(algo_data_logging_t *algo_data_logging_ptr,
                             int8_t *log_buffer,
                             uint32_t log_size,
                             uint32_t client_handle);

/**
 * This function is for checking log code status whether it is 
 * enable or not. 
 *
 * @param[in] log_code log code to be checked 
 * @param[out] ADSP_EOK if the code is enabled otherwise 
 *  	 ADSP_EFAILED
 * 
 */
ADSPResult algo_log_status(uint32_t log_code);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* _ALGO_LOGGING_H_ */
