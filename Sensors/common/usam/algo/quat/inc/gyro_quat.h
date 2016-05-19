#ifndef GYRO_QUAT_H
#define GYRO_QUAT_H

/*============================================================================
  @file gyro_quat.h

  @brief
  Data structures and constants used internally by the quaternion algorithm.

  Copyright (c) 2011-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
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

/* Number of elements in the quaternion result */
#define GYRO_QUAT_ELEMS       (4)
/* Number of elements/axis in the gyroscope input */
#define GYRO_QUAT_GYRO_ELEMS  (3)

/*============================================================================
  Type Declarations
  ===========================================================================*/

/* Quaternion configuration structure */
typedef struct
{
  /* sample rate in Hz */
  q16_t sampleRate;
  /* minimum report rate requested for dependent sensors */
  q16_t minReportRate;
  /* Unit of seconds */
  q16_t reportPeriod;
  /* The report mode is used to determine when to reset the quaternion */
  sns_sam_report_mode reportMode;
} gyro_quat_config;

/* Quaternion input structure */
typedef struct
{
   q16_t gyro[ GYRO_QUAT_GYRO_ELEMS ]; // gyro sample, radians/second
} gyro_quat_input;

/* Quaternion output structure */
typedef struct
{
   float quat[ GYRO_QUAT_ELEMS ]; // Quaternion output
   sns_sam_timestamp timestamp; // Sensor data timestamp; SSC clock ticks
} gyro_quat_output;

/* Quaternion state structure */
typedef struct
{
   gyro_quat_config config; // Quaternion algorithm configuration
   q16_t gyro[ GYRO_QUAT_GYRO_ELEMS ]; // Angular rate, radians/second
   sns_sam_timestamp timestamp; // Timestamp of the most recent gyro sample; clock ticks
   float quat[ GYRO_QUAT_ELEMS ]; // Most recent quaternion calculation
   float samplePeriod; // Current/instantaneous gyro sample period
   q16_t reportRate; // effective report rate requested for dependent sensor
} gyro_quat_state;

/* Quaternion persisitant data */
typedef struct {
  bool regDataRecv; /* If the registry data has been received*/
  uint64_t power; /* Consumption for the gyro sensor as reported by SMGR */
  q16_t maxSampleRate; /* Maximum sampling rate of the algorithm */
  q16_t minSampleRate; /* Minimum sampling rate of the algorithm */
  gyro_quat_config defConfig;/* Default configuration values */
  sns_sam_sensor_uid const *gyroSUID; /* SUID saved in dep_sensors_met() */
} gyro_quat_persist;

/*============================================================================
  Function Declarations
  ===========================================================================*/


#endif /* GYRO_QUAT_H */
