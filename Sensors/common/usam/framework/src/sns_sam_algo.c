/*============================================================================
  @file sns_sam_algo.c

  @brief
  This here is the only file that may be changes while adding new SAM
  algorithms into the SAM Framework.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include "sns_sam.h"
#include "sns_sam_algo_api.h"

#include "sns_sam_amd_v01.h"
#include "sns_sam_rmd_v01.h"
#include "sns_sam_internal_ped_v01.h"
#include "sns_sam_ped_v01.h"

/*============================================================================
  Algorithm Registration Function Declarations
  ===========================================================================*/

sns_sam_err amd_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err quat_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err core_ped_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err ped_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err fmv_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err gravity_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err rmd_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err rotation_vector_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err threshold_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err orientation_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err cmc_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err db_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err smd_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err dpc_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err game_rv_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err basic_gestures_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err tilt_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err oem_1_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err facing_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

sns_sam_err egs_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

/*============================================================================
  Global Data
  ===========================================================================*/

const sns_sam_algo_register samAlgoRegisterFuncs[] =
{
  amd_sam_register,
  rmd_sam_register,
  threshold_sam_register,
  core_ped_sam_register,
  ped_sam_register,
  smd_sam_register,
  tilt_sam_register,
  egs_sam_register,
  quat_sam_register,
  gravity_sam_register,
  orientation_sam_register,
  game_rv_sam_register,
  fmv_sam_register,
  rotation_vector_sam_register,
  cmc_sam_register,
  dpc_sam_register,
  db_sam_register,
  basic_gestures_sam_register,
  facing_sam_register,
  oem_1_sam_register
};

const uint32_t samAlgoRegisterFuncsSize =
  sizeof(samAlgoRegisterFuncs) / sizeof(samAlgoRegisterFuncs[0]);


const sns_sam_sensor_uid samUImageAlgoSUIDs[] =
{
  SNS_SAM_AMD_SUID_V01,
  SNS_SAM_RMD_SUID_V01,
  SNS_SAM_INTERNAL_PED_SUID_V01,
  SNS_SAM_PED_SUID_V01,
};

const uint32_t samUImageAlgoSUIDsSize =
  sizeof(samUImageAlgoSUIDs) / sizeof(samUImageAlgoSUIDs[0]);

