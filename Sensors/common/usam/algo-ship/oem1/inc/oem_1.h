/*============================================================================
  @file oem_1.h

  @brief
  Data structures and constants used by OEM_1 custom algorithm template.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/

#include <stdint.h>
#include "fixed_point.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define OEM_1_ELEMS 3

/*============================================================================
  Type Declarations
  ===========================================================================*/

/* OEM_1 configuration structure */
typedef struct
{
  int32_t sample_rate;
  int32_t report_period;
} oem_1_config_s;


/* OEM_1 input structure */
typedef struct
{
  int32_t sample_1[OEM_1_ELEMS];   //input sample from sensor 1
  //sns_sam_timestamp timestamp_1;            //timestamp  from sensor 1
  //int32_t sample_2[OEM_1_ELEMS];   //input sample from sensor 2
  //sns_sam_timestamp timestamp_2;            //input sample from sensor 2
} oem_1_input_s;


/* OEM_1 output structure */
typedef struct
{
  int32_t data[OEM_1_ELEMS];
  sns_sam_timestamp timestamp;
} oem_1_output_s;


/* OEM_1 state structure */
typedef struct
{
  uint32_t state_param1;
  oem_1_config_s config;
  int32_t data[OEM_1_ELEMS]; // Most recent OEM_1 calculation
  sns_sam_timestamp timestamp; // Timestamp of the most recent sensor sample
  float samplePeriod; // Current/instantaneous sample period
} oem_1_state_s;


/* OEM_1 persistant data */
typedef struct {
  bool regDataRecv; /* If the registry data has been received*/
  uint64_t power; /* Consumption for the sensor as reported by SMGR */
  q16_t defSampleRate; /* Default sampling rate if none specified */
  q16_t minSampleRate; /* Minimum sampling rate */
  q16_t maxSampleRate; /* Maximum sampling rate */
  sns_sam_sensor_uid const *accelSUID; /* SUID saved in dep_sensors_met() */
} oem_1_persist;


/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the OEM_1 algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err oem_1_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );
