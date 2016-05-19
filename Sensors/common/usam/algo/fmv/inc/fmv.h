#ifndef _FILTERED_MAGNETIC_VECTOR_H
#define _FILTERED_MAGNETIC_VECTOR_H
/*=============================================================================
  Filtered Magnetic Vector Interface Definition

  @brief
  Data structures and constants used internally by the quaternion algorithm.

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
#include "sns_sam_filtered_mag_v01.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
/* Absolute rest sum square threshold in (rad/s)^2
   2.56dps gyro offset error (in absolute rest) */
#define FMV_ABS_REST_SUMSQ_THOLD (0.002)
/* Square of min valid mag vec in Gauss^2 */
#define FMV_MIN_VALID_MAG_NORM_GAUSS_SQ (0.0225)
/* Square of max valid mag vec in Gauss^2 */
#define FMV_MAX_VALID_MAG_NORM_GAUSS_SQ (0.81)

/*============================================================================
  Type Declarations
  ===========================================================================*/
typedef enum
{
  FMV_INPUT_TYPE_MAG,
  FMV_INPUT_TYPE_GYRO,
  FMV_INPUT_TYPE_QUAT
} fmv_input_type_e;

typedef enum
{
   FMV_DEV_STATE_UNKNOWN,    // device state is unknown
   FMV_DEV_ABS_REST,         // device is in absolute rest
   FMV_DEV_REL_REST,         // device is in relative rest
   FMV_DEV_MOTION,           // device is moving
   FMV_DEV_STATES            // number of device states
} fmv_device_state_e;

/**
 * Accuracy levels of the FMV algorithm output.  May be used as array indices.
 */
typedef enum
{
   FMV_ACC_MIN = 0,
   FMV_ACC_LOW,
   FMV_ACC_HIGH,
   FMV_ACC_MAX,

   FMV_ACC_CNT
} fmv_accuracy_e;

typedef struct
{
  /* Sample rate in Hz */
  q16_t sample_rate;
  /* minimum report rate requested for dependent sensors */
  q16_t min_report_rate;
  /* Time constants for each accuracy level (ms) */
  uint32_t fmv_tcs[FMV_ACC_CNT];
  /* Reset filter if quat/gyro time diff exceeds this threshold(ms) */
  uint32_t max_gyro_sample_gap_tolerance;
  /* Reset filter if mag time diff exceeds this threshold * tc(ms) */
  float  max_mag_sample_gap_factor;
  /* Assume Zero turn if sample is below this number (rad/s) */
  float  min_turn_rate;
  /* Clamp norm(innov) to this (Gauss) */
  float max_mag_innovation;
  /* Motion detect period in seconds */
  float motion_detect_period;
  /* Absolute rest variance threshold in (rad/s)^2 */
  float abs_rest_var_thold;
  /* Relative rest variance threshold in (rad/s)^2 */
  float rel_rest_var_thold;
  /* Mag calibration latency in sample number */
  uint8_t mag_cal_lat_num_samps;
  /* Maximum mag sampling rate*/
  q16_t max_mag_sample_rate;
} fmv_config_s;


/**
 * Gyro and Mag will be streaming at the same rate, and should be approximately
 * matching in this structure.  If one is missing, this input object should be
 * tossed.  It is assumed that quaternion data will not be received at the same
 * rate, and hence may be placed into its own input object if necessary.
 */
typedef struct
{
  fmv_input_type_e input_type;
  union
  {
  /* calibrated magnetometer data */
  float mag[3];
  /* Quaternion data */
  float quat[4];
  /* Gyro Data */
  float gyro[3];
  }data;
  /* Calibrated mag accuracy */
  uint8_t acc;
} fmv_input_s;

typedef struct
{
  /* Timestamp associated with the Filtered Mag Vector output */
  uint32_t ts;
  /* Filtered magnetometer output vector */
  float  filtered_mag[3];
  /* FMV output accuracy */
  fmv_accuracy_e accuracy;
} fmv_output_s;

typedef struct
{
  fmv_config_s config;
  /* Filter constants by accuracy level */
  float alpha[FMV_ACC_CNT];

  /* Filtered magnetic vector as of now */
  float fmv[3];
  /* Time stamp of FMV estimate  */
  uint32_t fmv_ts;
  /* Our accuracy estimate of the FMV */
  fmv_accuracy_e accuracy;
  bool fmv_valid;

  /* Time stamp of latched gyro sample */
  uint32_t gyro_ts;
  /* Last latched gyro sample */
  float gyro[3];
  bool gyro_ts_valid;

  /* Time interval between gyro samples */
  float gyro_period;
  bool gyro_period_valid;

  /* Time stamp of last received mag sample */
  uint32_t mag_ts;
  bool     mag_ts_valid;

  /* Time stamp of last quaternion update */
  uint32_t quat_ts;
  /* Last quaternion input received */
  float quat[4];
  bool quat_ts_valid;

  /* Number of mag samples received since we reset */
  uint32_t mag_samples_since_reset;
  /* Declare "outage" if 2 gyro/quat samples are farther apart than this threshold */
  uint32_t max_gyro_outage;
  /* Declare outage if two mag samples are farther apart than this threshold */
  uint32_t max_mag_outage[FMV_ACC_CNT];

  /* Derived from minimum turn rate in config */
  float cos_min_turn_rate;

  /* Gyro samples */
  sns_buffer_type gyro_buf;
  /* Sum of gyro samples */
  double gyro_buf_sum[3];
  /* Sum of square of gyro samples */
  double gyro_buf_sum_sq[3];
  /* Absolute rest variance threshold in (rad/s)^2 */
  float abs_rest_var_thold;
  /* Relative rest variance threshold in (rad/s)^2 */
  float rel_rest_var_thold;

  /* Device state */
  fmv_device_state_e dev_state;
  /* Number of mag samples received since we detected device at abs reset */
  uint32_t mag_samples_since_dev_abs_rest;
  /* Number of mag samples that must be received while the device is at
     absolute rest state for MAR (magnetic anomaly rejection) to occur */
  uint32_t mag_samples_for_mar;
  /* effective report rate requested for dependent sensor*/
  q16_t report_rate;
} fmv_state_struct_t;

/* FMV persisitant data */
typedef struct {
  /* If the registry data for FMV has been received*/
  bool fmv_reg_data;
  /* If the registry data from Gyro AMD has been received*/
  bool amd_reg_data;
  /* Consumption for the gyro sensor as reported by SMGR */
  uint64_t power_gyro;
  /* Consumption for the mag sensor as reported by SMGR */
  uint64_t power_mag;
  /* Maximum sampling rate*/
  q16_t max_sample_rate;
  /* Minimum sampling rate*/
  q16_t min_sample_rate;
  /* Default configuration values */
  fmv_config_s def_config;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *gyro_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *mag_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *quat_suid;
} fmv_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the FMV algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err fmv_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

#endif // End include guard
