#ifndef ORIENTATION_H
#define ORIENTATION_H

/*=============================================================================
  Qualcomm Orientation header file

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
#include "sns_sam_orientation_v01.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define ORIENTATION_QUAT_COLS   (4)
#define ORIENTATION_VECTOR_COLS (3)

// Initial samples over which a simple averaging is applied to
// prepopulate the filter registers. The prepopulation of the
// filter with the initial values ensures that filter settles
// quickly. The averaging eliminates some of the initial noise
#define ORIENTATION_FILTER_STARTUP_SAMPLES 4

// square of min valid mag vec in Gauss^2
#define ORIENTATION_MIN_VALID_MAG_NORM_GAUSS_SQ (0.0225f)
// square of max valid mag vec in Gauss^2
#define ORIENTATION_MAX_VALID_MAG_NORM_GAUSS_SQ (0.81f)

// mag filter time constant in sec
#define ORIENTATION_MAG_FILTER_TC_SEC (0.5f)

/*============================================================================
  Type Declarations
  ===========================================================================*/

typedef enum
{
  ORIENTATION_INPUT_ACC     = 0,
  ORIENTATION_INPUT_MAG     = 1
} orientation_input_e;

typedef enum
{
  ORIENTATION_ANDROID_COORD_SYS = 0, // Android (ENU = East North Up)
  ORIENTATION_SAE_COORD_SYS = 1  // SAE (NED = North East Down)
} orientation_coord_sys_e;

#define ORIENTATION_DEFAULT_COORD_SYS ORIENTATION_ANDROID_COORD_SYS

typedef enum
{
  ORIENTATION_DEV_STATE_UNKNOWN,    // device state is unknown
  ORIENTATION_DEV_ABS_REST,         // device is in absolute rest
  ORIENTATION_DEV_REL_REST,         // device is in relative rest
  ORIENTATION_DEV_MOTION,           // device is moving
  ORIENTATION_DEV_STATES            // number of device states
} orientation_device_state_e;

typedef struct
{
} orientation_mag_data;

typedef struct
{
  q16_t sample_rate;       // sample rate in Hz
  q16_t min_report_rate;   // minimum report rate requested for dependent sensors
  uint32_t accel_filter_tc;  // accel filter tc, msec
  uint32_t mag_filter_tc;    // mag filter tc, msec
  float motion_detect_period;// motion detect period, secs
  float abs_rest_var_thold;  // absolute rest variance threshold (m/s/s)2
  orientation_coord_sys_e coordinate_sys; // coordinate system used in output
} orientation_config_s;

typedef struct
{
  orientation_input_e input_type;
  union
  {
   q16_t acc_vector[ORIENTATION_VECTOR_COLS];
   q16_t mag_vector[ORIENTATION_VECTOR_COLS];
  } data;
  uint8_t mag_accuracy;  // accuracy metric
} orientation_input_s;

typedef struct
{
  float rotation_vector[ORIENTATION_QUAT_COLS];
  float gravity[ORIENTATION_VECTOR_COLS];   // gravity vector m/s2
  float lin_accel[ORIENTATION_VECTOR_COLS]; // linear acceleartion m/s2
  sns_sam_timestamp timestamp;
  uint8_t accuracy;                   // accuracy metric
  orientation_coord_sys_e coordinate_sys;
} orientation_output_s;

typedef struct
{
  orientation_config_s config;
  float filt_acc_vector[ORIENTATION_VECTOR_COLS];
  float filt_mag_vector[ORIENTATION_VECTOR_COLS];
  float accel_filter_alpha;
  float mag_filter_alpha;
  uint32_t filt_acc_ts;
  uint32_t filt_mag_ts;
  uint32_t num_accel_samples; // sample count for accel filter register prepopulation
  uint32_t num_mag_samples; // sample count for mag filter register prepopulation
  sns_buffer_type acc_buf;                        // accelerometer samples
  double acc_buf_sum[ORIENTATION_VECTOR_COLS];    //sum of accelerometer samples
  double acc_buf_sum_sq[ORIENTATION_VECTOR_COLS]; //sum of square of accel samples
  // Squared magnitude of the last input mag vector, used to detect magnetic anomalies
  double mag_vec_norm_sq;
  orientation_device_state_e dev_state;           // device state
  uint32_t mag_samps_at_rest;    // mag samples since rest was detected
  bool acc_received;
  bool mag_received;
  orientation_output_s output;  // Active output buffer; most recent output
  /* Maximum sample rate for Orientation, as provided by mag sensor */
  q16_t sample_rate_max;
  /* effective report rate requested for dependent sensor*/
  q16_t report_rate; 
} orientation_state_s;

/* Orientation persisitant data */
typedef struct {
  /* If the registry data for Orientation has been received*/
  bool ori_reg_data;
  /* If the registry data for AMD has been received*/
  bool amd_reg_data;
  /* Consumption for the accel sensor as reported by SMGR */
  uint64_t power_acc;
  /* Consumption for the mag sensor as reported by SMGR */
  uint64_t power_mag;
  /* Maximum sample rate for Orientation*/
  q16_t sample_rate_max;
  /* Minimum sample rate for Orientation*/
  q16_t sample_rate_min;
  /* Default configuration values */
  orientation_config_s def_config;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *accel_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *mag_suid;
} orientation_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

#endif
