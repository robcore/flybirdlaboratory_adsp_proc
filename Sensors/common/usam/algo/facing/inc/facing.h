#ifndef FACING_H
#define FACING_H

/*=============================================================================
  Qualcomm Facing header file

  Copyright (c) 2011, 2014 Qualcomm Technologies Inc.  All Rights Reserved.
  Qualcomm Technologies Inc. Proprietary and Confidential.
=============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/

#include <stdint.h>
#include "circular_buffer.h"
#include "fixed_point.h"
#include "sns_sam_facing_v01.h"
#include "sns_sam_rmd_v01.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define FACING_DATA_COLS     (3)

/*============================================================================
  Type Declarations
  ===========================================================================*/

typedef enum
{
  FACING_UNKNOWN = 0,
  FACING_UP      = 1,
  FACING_DOWN    = 2,
  FACING_NEUTRAL = 3
} facing_state_e;

typedef struct
{
  q16_t sample_rate;            // sample rate in Hz, Q16
  q16_t facing_angle_threshold; // angle in radians, Q16
  int32_t report_neutral;         // flag to indicate whether Neutral state to be reported
} facing_config_s;

typedef struct
{
  q16_t a[FACING_DATA_COLS];    // accel, m/s/s, Q16
  int32_t motion_state;           // rest, motion, unknown
} facing_input_s;

typedef struct
{
  facing_state_e facing_state;
  sns_sam_timestamp timestamp;         // accel timestamp; ssc ticks
} facing_output_s;

typedef struct
{
  facing_config_s config;
  buffer_type buf;
  int32_t buf_sum[FACING_DATA_COLS];
  int32_t facing_thresh_sum;
  facing_state_e last_facing_state;
  facing_state_e current_facing_state;
  int32_t report_neutral;
  int32_t input_motion_state;
} facing_state_s;

/* facing persistant data */
typedef struct {
  bool regDataRecv; /* If the registry data has been received*/
  int32_t facing_angle_threshold;  /* angle in radians, Q16 */
  int32_t report_neutral;  /* flag to indicate whether Neutral state to be reported */
  uint64_t power; /* Consumption for the accel sensor as reported by SMGR */
  q16_t defSampleRate; /* Default sampling rate if none specified */
  q16_t defSensorReportRate;
  q16_t minSampleRate;
  q16_t maxSampleRate;
  sns_sam_sensor_uid const *rmdSUID;   /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *accelSUID; /* SUID saved in dep_sensors_met() */
} facing_persist_s;

#endif /* FACING_H */
