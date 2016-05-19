/*============================================================================
  @file oem_1_msg.c

  @brief
    Implementation of the MSG APIs for OEM_1, custom algorithm template with SAM 2.0.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <math.h>
#include "log_codes.h"
#include "log.h"
#include "oem_1.h"
#include "fixed_point.h"
#include "sns_memmgr.h"
#include "sns_reg_common.h"
#include "sns_sam_algo_utils.h"
#include "sns_reg_api_v02.h"
#include "sns_smgr_api_v01.h"
#include "sns_sam_algo_api.h"
#include "sns_oem_1_v01.h"
#include "sns_sam_common_v01.h"
#include "sns_debug_str.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define SNS_SAM_MAX_OEM_1_REPORT_RATE_Q16 FX_CONV_Q16(200,0)

#define OEM_1_ALGO_REVISION 1

/*===========================================================================
  Static Function Definitions
  ===========================================================================*/

static void
oem_1_mem_const_req( sns_sam_algo_const_buf_size *bufferSizes )
{
  bufferSizes->configDataSize = sizeof(oem_1_config_s);
  bufferSizes->persistDataSize = sizeof(oem_1_persist);
}


static void
oem_1_dep_sensors_met( struct sns_sam_sensor_algo const *algo,
  sns_sam_algo_all_dep_met depMetFunc, sns_sam_algo_persist *persistData,
  sns_sam_sensor_uid const *sensorUID,
  sns_sam_algo_attr const (*sns_sam_attr_array)[ SAM_ALGO_ATTR_CNT ] )
{
  sns_sam_algo_attr *attr_array;
  oem_1_persist *oem_1PersistData = (oem_1_persist*)persistData->buf;
  uint32_t i;
  attr_array = (sns_sam_algo_attr*)sns_sam_attr_array;

  if( SNS_SMGR_SUID_ACCEL_1_V01 == *sensorUID )
  {
    for( i = 0;
         i < SAM_ALGO_ATTR_CNT && SAM_ALGO_ATTR_CNT != attr_array[i].attribute;
         i++ )
    {
      if( attr_array[i].supported )
      {
        if( SAM_ALGO_ATTR_POWER == attr_array[i].attribute )
        {
          oem_1PersistData->power = FX_CONV_Q16(attr_array[i].attrValue, 0) / 1000;
        }
        else if( SAM_ALGO_ATTR_MIN_SAMPLE == attr_array[i].attribute )
        {
          oem_1PersistData->minSampleRate = attr_array[i].attrValue;
        }
        else if( SAM_ALGO_ATTR_MAX_SAMPLE == attr_array[i].attribute )
        {
          oem_1PersistData->maxSampleRate = FX_CONV_Q16(200,0) > attr_array[i].attrValue
            ? attr_array[i].attrValue : FX_CONV_Q16(200,0);
        }
      }
    }
    oem_1PersistData->accelSUID = sensorUID;
  }

  if( NULL != oem_1PersistData->accelSUID)
  {
    depMetFunc( algo );
  }

}

static void
oem_1_get_attr( sns_sam_algo_persist const *persistData,
  sns_sam_algo_attr attributes[] )
{
  uint8_t i;
  oem_1_persist *oem_1PersistData = (oem_1_persist*)persistData->buf;

  for( i = 0;
       i < SAM_ALGO_ATTR_CNT && SAM_ALGO_ATTR_CNT != attributes[i].attribute;
       i++ )
  {
    switch( attributes[i].attribute )
    {
    case SAM_ALGO_ATTR_POWER:
      attributes[i].attrValue = oem_1PersistData->power;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_REPORT_MODE:
      attributes[i].attrValue =
        SNS_SAM_PERIODIC_REPORT_V01 | SNS_SAM_SYNC_REPORT_V01;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_MIN_REPORT:
      attributes[i].attrValue = 0;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_MAX_REPORT:
      attributes[i].attrValue = oem_1PersistData->maxSampleRate;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_MIN_SAMPLE:
      attributes[i].attrValue = oem_1PersistData->minSampleRate;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_MAX_SAMPLE:
      attributes[i].attrValue = oem_1PersistData->maxSampleRate;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_REVISION:
      attributes[i].attrValue = OEM_1_ALGO_REVISION;
      attributes[i].supported = true;
      break;

    case SAM_ALGO_ATTR_MAX_BATCH:
      attributes[i].attrValue = 0;
      attributes[i].supported = false;
      break;

    default:
      attributes[i].supported = false;
    }
  }

}

static sns_sam_err
oem_1_dep_sensors( uint32_t *sensorCount,
  struct sns_sam_algo_dep_sensor dependentSensors[] )
{

  if( *sensorCount >= 1 )
  {
    *sensorCount = 1;
    dependentSensors[0].sensorUID = SNS_SMGR_SUID_ACCEL_1_V01;
    dependentSensors[0].serviceObj = SNS_SMGR_SVC_get_service_object_v01();

    return SAM_ENONE;
  }
  else
  {
    return SAM_EMAX;
  }
}

static sns_sam_err
oem_1_reg_grps( uint32_t *registryGrpCount, sns_sam_reg_group registryGroups[] )
{
  *registryGrpCount = 0;
  return SAM_ENONE;
}


static sns_sam_err
oem_1_process_enable_req( sns_sam_enable_req const *enableReq,
  sns_sam_algo_persist *persistData, sns_sam_client_attr *clientAttr,
  sns_sam_algo_config *configData )
{
  oem_1_persist *oem_1Persist = (oem_1_persist*)persistData->buf;
  oem_1_config_s *oem_1Config = (oem_1_config_s*)configData->buf;
  sns_oem_1_enable_req_msg_v01 *reqMsg =
    (sns_oem_1_enable_req_msg_v01*) enableReq->msg.buf;

  clientAttr->dcPercentOn = 0;
  clientAttr->reportMode = SNS_SAM_REPORT_MODE_SYNC;

  if( !reqMsg->sample_rate_valid )
  {
    oem_1Config->sample_rate = oem_1Persist->defSampleRate;
  }
  else if( oem_1Persist->minSampleRate < (q16_t)reqMsg->sample_rate &&
           oem_1Persist->maxSampleRate > (q16_t)reqMsg->sample_rate )
  {
    oem_1Config->sample_rate = reqMsg->sample_rate;
  }
  else
  {
    return SAM_EFAILED;
  }

  clientAttr->reportPeriod =
    FX_FLTTOFIX_Q16(1.0f / FX_FIXTOFLT_Q16_SP(oem_1Config->sample_rate));
  oem_1Config->report_period = clientAttr->reportPeriod;

  return SAM_ENONE;
}

static sns_sam_err
oem_1_gen_req( sns_sam_algo_state const *algoState,
  sns_sam_sensor_uid const *sensorUID, sns_sam_enable_req *enableReqMsg )
{
  oem_1_state_s *oem_1State = (oem_1_state_s*)algoState->buf;

  if( SNS_SMGR_SUID_ACCEL_1_V01 == *sensorUID )
  {
    sns_sam_sensor_data_info_req accelReq;

    accelReq.sensorCount = 1;
    accelReq.sampleRate = oem_1State->config.sample_rate;
    accelReq.sensorDbase[0].dataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
    accelReq.sensorDbase[0].sampleQual = SNS_SAM_DEFAULT_SAMPLE_QUALITY;
    accelReq.sensorDbase[0].sensorId = SNS_SMGR_ID_ACCEL_V01;
    accelReq.sensorDbase[0].buffered_sampleRate = oem_1State->config.sample_rate;
    accelReq.srcUID = SNS_OEM_1_SUID_V01;
    accelReq.reportRate = oem_1State->config.sample_rate;

    return sns_sam_util_gen_smgr_buffer_req( &accelReq, enableReqMsg );
  }
  return SAM_ESTATE;
}

static sns_sam_err
oem_1_gen_ind( sns_sam_algo_callback const *cbFunc,
  sns_sam_algo_output const *outputData, uint8_t extInstanceID,
  sns_sam_ind_msg *indMsg)
{
  oem_1_output_s *output = (oem_1_output_s*)outputData->data;
  sns_oem_1_report_ind_msg_v01 *ind_msg =
    (sns_oem_1_report_ind_msg_v01*)indMsg->msg.buf;

  ind_msg->timestamp = output->timestamp;
  SNS_OS_MEMCOPY( ind_msg->output.data, output->data,
    sizeof(ind_msg->output.data) );
  ind_msg->output.data_len = OEM_1_ELEMS;

  return SAM_ENONE;
}

static sns_sam_err
oem_1_gen_report( sns_sam_algo_output const *outputData,
  sns_sam_resp_msg *respMsg)
{
  oem_1_output_s *output = (oem_1_output_s*)outputData->data;
  sns_oem_1_get_report_resp_msg_v01 *reportResp =
    (sns_oem_1_get_report_resp_msg_v01*)respMsg->msg.buf;

  reportResp->resp.sns_result_t = SNS_SUCCESS;

  reportResp->output_valid = true;
  SNS_OS_MEMCOPY( reportResp->output.data, output->data,
    sizeof(reportResp->output.data) );

  reportResp->timestamp_valid = true;
  reportResp->timestamp = output->timestamp;

  return SAM_ENONE;
}

static bool
oem_1_check_sensor( sns_sam_algo_state const *algoState,
  sns_sam_enable_req const *enableReq )
{
  oem_1_state_s *oem_1State = (oem_1_state_s*)algoState->buf;

  if( SNS_SMGR_SUID_ACCEL_1_V01 == *enableReq->sensorUID)
  {
    sns_smgr_buffering_req_msg_v01 *accelReq =
      (sns_smgr_buffering_req_msg_v01*)enableReq->msg.buf;

    if( (q16_t)accelReq->ReportRate == oem_1State->config.sample_rate &&
        accelReq->Item[0].SamplingRate == oem_1State->config.sample_rate &&
        accelReq->Item[0].SampleQuality == SNS_SAM_DEFAULT_SAMPLE_QUALITY )
    {
      return true;
    }

  }
  return false;
}

static sns_sam_err
oem_1_process_ind( sns_sam_algo_callback const *cbFunc,
  sns_sam_ind_msg const *indMsg, sns_sam_input_q *inputData )
{
  UNREFERENCED_PARAMETER(inputData);

  if( SNS_SMGR_SUID_ACCEL_1_V01 == *indMsg->sensorUID)
  {
    uint32_t buf_samples_cnt = 0;
    sns_smgr_buffering_ind_msg_v01 *bufInd =
      (sns_smgr_buffering_ind_msg_v01*)indMsg->msg.buf;
    sns_sam_buffered_data bufSample;
    uint32_t i;
    sns_sam_err err;

    sns_sam_buffered_data_init( &bufSample );


    for(err = sns_sam_get_single_buffered_sample( bufInd, &bufSample, &buf_samples_cnt);
      SAM_EMAX != err; err = sns_sam_get_single_buffered_sample( bufInd, &bufSample,
      &buf_samples_cnt) )
    {
      if( SAM_ENONE == err)
      {
        oem_1_input_s input;
      for(i = 0; i < 3; i++)
        {
          input.sample_1[i] = bufSample.current_sample.data[i];
        }

        cbFunc->sns_sam_algo_add_input(
        cbFunc->algoInst, (intptr_t)&input, bufSample.current_sample.timestamp );
      }
    }
  }

  return SAM_ENONE;
}

/*===========================================================================
  Public Definitions
  ===========================================================================*/

sns_sam_algo_msg_api oem_1_algo_msg_api =
{
  sizeof(sns_sam_algo_msg_api),
  &oem_1_mem_const_req,
  &oem_1_get_attr,
  &oem_1_dep_sensors_met,
  NULL,
  &oem_1_dep_sensors,
  &oem_1_reg_grps,
  &oem_1_process_enable_req,
  NULL,
  &oem_1_process_ind,
  &oem_1_gen_ind,
  NULL,
  &oem_1_gen_report,
  &oem_1_gen_req,
  &oem_1_check_sensor
};
