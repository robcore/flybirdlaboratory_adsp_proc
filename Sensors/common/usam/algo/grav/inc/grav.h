#ifndef GRAVITY_H
#define GRAVITY_H

/*=============================================================================
  Qualcomm gravity vector / linear acceleration detector header file

  Copyright (c) 2011-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "fixed_point.h"
#include "sns_buffer.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_gravity_vector_v01.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
/* Number of elements in the computed gravity vector */
#define GRAVITY_NUM_ELEMS      (3)
/* Number of elements in the input quaternion vector */
#define GRAVITY_NUM_QUAT_ELEMS (4)

#define GRAVITY_ACCEL_OUTAGE_PERIOD (500)    // milliseconds
#define GRAVITY_QUAT_OUTAGE_PERIOD  (500)    // milliseconds

/*============================================================================
  Type Declarations
  ===========================================================================*/
typedef enum
{
  GRAVITY_INPUT_TYPE_ACCEL = 0,
  GRAVITY_INPUT_TYPE_QUAT = 1
} gravity_input_type_e;

typedef enum
{
  GRAVITY_ACCURACY_UNRELIABLE = 0,
  GRAVITY_ACCURACY_LOW,
  GRAVITY_ACCURACY_MEDIUM,
  GRAVITY_ACCURACY_HIGH,
} gravity_accuracy_e;

typedef enum
{
  GRAVITY_DEV_STATE_UNKNOWN = 0,    // device state is unknown
  GRAVITY_DEV_ABS_REST,         // device is in absolute rest
  GRAVITY_DEV_REL_REST,         // device is in relative rest
  GRAVITY_DEV_MOTION,           // device is moving
  GRAVITY_DEV_STATES            // number of device states
} gravity_device_state_e;

/* Gravity configuration structure */
typedef struct
{
  /* Sample rate in Hz */
  q16_t sample_rate;
  /* minimum report rate requested for dependent sensors */
  q16_t min_report_rate;
  /* Filter time constants in millisec */
  uint32_t filter_tc[GRAVITY_DEV_STATES];
  /* Quaternion input outage period in msec */
  uint32_t quat_outage_period;
  /* Accelerometer input outage period in msec */
  uint32_t accel_outage_period;
  /* Motion detect period in seconds */
  float motion_detect_period;
  /* Absolute rest variance threshold (m/s/s)2 */
  float abs_rest_var_thold;
  /* Relative rest variance threshold (m/s/s)2 */
  float rel_rest_var_thold;
} gravity_config_s;

/* Gravity input structure */
typedef struct
{
  /* input type */
  gravity_input_type_e input_type;
  union
  {
  /* Accelerometer sample */
  q16_t accel[GRAVITY_NUM_ELEMS];
  float quat[GRAVITY_NUM_QUAT_ELEMS];
  }data;
} gravity_input_s;

/* Gravity output structure */
typedef struct
{
  /* Gravity Vector */
  float gravity[GRAVITY_NUM_ELEMS];
  /* Linear acceleration */
  float lin_accel[GRAVITY_NUM_ELEMS];
  /* Common timestamp for gravity and linear accel (SSC ticks) */
  sns_sam_timestamp timestamp;
  /* Accuracy Metric */
  gravity_accuracy_e accuracy;
  /* Device state */
  gravity_device_state_e dev_state;
} gravity_output_s;

/* Gravity state structure */
typedef struct
{
  gravity_config_s config;

  /* Last input quaternion */
  float quat[GRAVITY_NUM_QUAT_ELEMS];
  /* Last input quaternion timestamp */
  sns_sam_timestamp quat_ts;

  /* Last input Accel */
  float accel[GRAVITY_NUM_ELEMS];
  /* Last input accelerometer timestamp */
  sns_sam_timestamp accel_ts;

  /* Calculated gravity */
  float gravity[GRAVITY_NUM_ELEMS];
  /* Normalized gravity */
  float gravity_result[GRAVITY_NUM_ELEMS];
  /* Accuracy Metric */
  gravity_accuracy_e accuracy;
  /* Gravity filter constant */
  float filter_alpha[GRAVITY_DEV_STATES];
  /* Instantaneous quaternion sample period */
  uint32_t quat_samp_per;
  /* Instantaneous accelerometer sample period */
  uint32_t accel_samp_per;

  /* Sample count for initial alpha */
  uint32_t num_accel_samples; //
  /* Accelerometer sample buffer */
  sns_buffer_type acc_buf;
  /* Sum of accelerometer samples */
  double acc_buf_sum[GRAVITY_NUM_ELEMS];
  /* Sum of square of accel samples */
  double acc_buf_sum_sq[GRAVITY_NUM_ELEMS];
  /* Absolute rest variance threshold (m/s/s)2 */
  float abs_rest_var_thold;
  /* Relative rest variance threshold (m/s/s)2 */
  float rel_rest_var_thold;
  /* Currently computed device state */
  gravity_device_state_e dev_state;
  /* effective report rate requested for dependent sensor*/
  q16_t report_rate; 
} gravity_state_s;

/* Gravity persisitant data */
typedef struct {
  /* If the registry data for Gravity has been received*/
  bool grav_reg_data;
  /* If the registry data from Gyro AMD has been received*/
  bool amd_reg_data;
  /* Consumption for the gyro sensor as reported by SMGR */
  uint64_t power_quat;
  /* Consumption for the mag sensor as reported by SMGR */
  uint64_t power_accel;
  /* Maximum sampling rate*/
  q16_t max_sample_rate;
  /* Minimum sampling rate*/
  q16_t min_sample_rate;
  /* Default configuration values */
  gravity_config_s def_config;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *accel_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *quat_suid;
} gravity_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the Gravity algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err gravity_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

#endif // End include guard
