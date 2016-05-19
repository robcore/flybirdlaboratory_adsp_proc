#ifndef AMD_H
#define AMD_H

/*============================================================================
  @file amd.h

  Absolute motion detector header file

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
============================================================================*/

#include <stdint.h>
#include "sns_sam_qmd_v01.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_sam_algo_utils.h"
#include "sns_sam_algo_api.h"
#include "qmd.h"
#include "spi.h"

#define AMD_SUID              SNS_SAM_AMD_SUID_V01

//Default config values
#define QMD_OP_INTERVAL_ABS    (FX_FLTTOFIX_Q16(0.5))         // seconds
#define QMD_FILTER_ENABLED_ABS (false)                        // boolean
#define QMD_FC_ABS             (FX_FLTTOFIX_Q16(0.0))         // Hz

/**
* amd_state
* Internal state data used by the algorithm
*/
typedef struct
{
  spi_state_s *absRest;
  qmd_config config;
  qmd_output currentOutput;
  qmd_output lastOutput;
  qmd_accel_stream_type accelStatus;
  qmd_persist *persistPtr;
  uint64_t  lastInputTime;
} amd_state;


/* SAM Algo API */

/**
* Generates memory requirements for algorithm data buffers.
*
* See sns_sam_algo_mem_req
*/
sns_sam_err amd_mem_req( sns_sam_algo_config const *configData,
                         sns_sam_algo_buf_size *bufferSizes );

/**
* Resets and initializes AMD algorithm state data.
*
* See sns_sam_algo_reset
*/
sns_sam_err amd_reset( sns_sam_algo_config const *configData,
                       sns_sam_algo_callback const *cbFunc,
                       sns_sam_algo_persist *persistData,
                       sns_sam_algo_state *algoState );

/**
* Update algorithm with input data and update the algorithm output
*
* See sns_sam_algo_update
*/
sns_sam_err amd_update( sns_sam_algo_state *algoState,
                        sns_sam_algo_callback const *cbFunc,
                        sns_sam_input_q const *inputData,
                        sns_sam_algo_persist *persistData,
                        uint32_t *processedCnt );

/**
* Generate output data based on current state of algorithm.
*
* AMD will only copy the previous output in this function.
* See sns_sam_algo_generate
*/
sns_sam_err amd_generate( sns_sam_algo_state *algoState,
                          sns_sam_algo_callback const *cbFunc,
                          sns_sam_algo_output *outputData );

/**
* Determine if given configuration is compatible with existing algorithm
* instance
*
* See sns_sam_algo_check_config
*/
bool amd_check_config( sns_sam_algo_state const *algoState,
                       sns_sam_algo_config const *configData );


/* AMD Message API */


/**
* Determine whether the algorithm's registry dependencies have been met.
*
* See sns_sam_algo_dep_registry_met
*/
void amd_dep_registry_met( struct sns_sam_sensor_algo const *algo,
                           sns_sam_algo_all_dep_met depMetFunc,
                           sns_sam_algo_persist *persistData,
                           sns_sam_reg_data const *regData );

/**
* Provide a list of an algorithm's registry groups.
*
* See sns_sam_algo_reg_grps
*/
sns_sam_err amd_reg_grps( uint32_t *registryGrpCount,
                          sns_sam_reg_group registryGroups[] );

/**
* Process an incoming enable IDL request message for this algorithm.
*
* See sns_sam_algo_process_enable_req
*/
sns_sam_err amd_process_enable_req( sns_sam_enable_req const *enableReq,
                                    sns_sam_algo_persist *persistData,
                                    sns_sam_client_attr *clientAttr,
                                    sns_sam_algo_config *configData );

/**
* Generates the enable request message for the given dependent sensor.
*
* See sns_sam_algo_gen_req
*/
sns_sam_err amd_gen_req( sns_sam_algo_state const *algoState,
                              sns_sam_sensor_uid const *sensorUID,
                              sns_sam_enable_req *enableReqMsg );

#endif /* AMD_H */
