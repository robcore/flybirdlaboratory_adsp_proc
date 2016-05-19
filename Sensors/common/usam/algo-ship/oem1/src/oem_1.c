/*============================================================================
  @file oem_1.c

  @brief
  Implementation of the OEM_1, custom algorithm template with SAM 2.0.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <math.h>
#include "sns_log_types.h"
#include "oem_1.h"
#include "fixed_point.h"
#include "sns_sam_algo_api.h"
#include "sns_memmgr.h"
#include "sns_oem_1_v01.h"
#include "sns_debug_str.h"


/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

//DSPS clock frequency 32768Hz
#define OEM_1_DSPS_CLK_FREQ 32768

/*============================================================================
  Extern Definitions
  ===========================================================================*/
extern sns_sam_algo_msg_api oem_1_algo_msg_api;

/*============================================================================
  Static Function Definitions
  ===========================================================================*/

/**
 * See sns_sam_algo_mem_req
 */
static sns_sam_err
oem_1_mem_req( sns_sam_algo_config const *configData,
  sns_sam_algo_buf_size *bufferSizes )
{
  UNREFERENCED_PARAMETER(configData);
  bufferSizes->algoStateSize = sizeof(oem_1_state_s);
  bufferSizes->inputDataSize = sizeof(oem_1_input_s);
  bufferSizes->outputDataSize = sizeof(oem_1_output_s);
  return SAM_ENONE;
}

/**
 * See sns_sam_algo_reset
 */
static sns_sam_err
oem_1_reset( sns_sam_algo_config const *configData,
  sns_sam_algo_callback const *cbFunc, sns_sam_algo_persist *persistData,
  sns_sam_algo_state *algoState )
{
  UNREFERENCED_PARAMETER(persistData);
  oem_1_state_s *oem_1State = (oem_1_state_s*)algoState->buf;
  oem_1_config_s *oem_1Config = (oem_1_config_s*)configData->buf;
  oem_1State->state_param1= 0;
  oem_1State->config = *oem_1Config;
  return SAM_ENONE;
}

/**
 * See sns_sam_algo_generate
 */
static sns_sam_err
oem_1_generate( sns_sam_algo_state *algoState,
  sns_sam_algo_callback const *cbFunc, sns_sam_algo_output *outputData )
{
  UNREFERENCED_PARAMETER(cbFunc);
  oem_1_state_s *oem_1State = (oem_1_state_s*)algoState->buf;
  oem_1_output_s *output = (oem_1_output_s*)outputData->data;

  SNS_OS_MEMCOPY( output->data, oem_1State->data, sizeof(output->data) );
  output->timestamp = oem_1State->timestamp;
  return SAM_ENONE;
}

/**
 * See sns_sam_algo_check_config
 */
static bool
oem_1_check_config( sns_sam_algo_state const *algoState,
  sns_sam_algo_config const *configData )
{
  oem_1_state_s *oem_1State = (oem_1_state_s*)algoState->buf;
  oem_1_config_s *oem_1Config = (oem_1_config_s*)configData->buf;
  return oem_1State->config.sample_rate == oem_1Config->sample_rate;
}


/**
 * See sns_sam_algo_update
 */
static sns_sam_err
oem_1_update( sns_sam_algo_state *algoState,
  sns_sam_algo_callback const *cbFunc, sns_sam_input_q const *inputData,
  sns_sam_algo_persist *persistData, uint32_t *processedCnt)
{
  UNREFERENCED_PARAMETER(persistData);
  oem_1_state_s *state = (oem_1_state_s*)algoState->buf;
  oem_1_output_s output;
  oem_1_input_s *input;
  sns_sam_algo_input *algoInputBuf;

  *processedCnt = 0;
  algoInputBuf = (sns_sam_algo_input *)sns_q_check( (sns_q_s*)inputData );
  if( NULL == algoInputBuf )
  {
    return SAM_EFAILED;
  }
  input = (oem_1_input_s*)algoInputBuf->data;
  *processedCnt = 1;
  state->data[0] = input->sample_1[0];
  state->data[1] = input->sample_1[1];
  state->data[2] = input->sample_1[2];
  state->timestamp = algoInputBuf->timestamp;

  //OEM_1 algorithm logic
  //   [0] = 1 if SAE Z-axis is negative and 2 if SAE Z-axis is positive
  //   [1] = SAE accel z value
  //   [2] = hardcoded value, 100
  output.data[0] = (state->data[2] < 0) ? (1) : (2);
  output.data[1] = state->data[2];
  output.data[2] = 100;
  output.timestamp = algoInputBuf->timestamp;
  cbFunc->sns_sam_algo_add_output( cbFunc->algoInst, (intptr_t)&output );
  return SAM_ENONE;
}


/*============================================================================
  Public Function Definitions
  ===========================================================================*/

/**
* OEM_1 Algo API
*
* See sns_sam_algo_api
*/
static sns_sam_algo_api oem_1_algo_api =
{
  sizeof(sns_sam_algo_api),
  &oem_1_mem_req,
  &oem_1_reset,
  &oem_1_update,
  &oem_1_generate,
  &oem_1_check_config
};

sns_sam_err oem_1_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID )
{
  *algoAPI = &oem_1_algo_api;
  *msgAPI = &oem_1_algo_msg_api;
  *serviceObj = SNS_OEM_1_SVC_get_service_object_v01();
  *sensorUID = SNS_OEM_1_SUID_V01;
  return SAM_ENONE;
}
