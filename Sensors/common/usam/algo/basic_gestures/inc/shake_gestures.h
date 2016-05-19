#ifndef SHAKE_GESTURES_H
#define SHAKE_GESTURES_H

/*=============================================================================
  Qualcomm Basic Gestures header file

  Copyright (c) 2011, 2014 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.
=============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who  what, where, why
 * ----------  ---  -----------------------------------------------------------
 * 2011-12-13  pd   initial version
 *
 *============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/

#include <stdint.h>
#include "circular_buffer.h"
#include "rel_rest.h"
#include "fixed_point.h"
#include "sns_sam_basic_gestures_v01.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

#define BASIC_SAMPLE_RATE_DEF_HZ    (30)
#define BASIC_SAMPLE_RATE_DEF_Q16   (FX_CONV_Q16(30, 0))
#define BASIC_TIME_WINDOW           (FX_FLTTOFIX_Q16(0.15))   // seconds, Q16
#define BASIC_SLEEP_DEF             (FX_FLTTOFIX_Q16(0.3))    // seconds, Q16; change to .3
#define BASIC_PUSH_THRESH_DEF       (FX_FLTTOFIX_Q16(1.5*G))  // m/s/s, Q16, change to 1.5
#define BASIC_PULL_THRESH_DEF       (FX_FLTTOFIX_Q16(1.5*G))  // m/s/s, Q16, "
#define BASIC_SHAKE_THRESH_DEF      (FX_FLTTOFIX_Q16(1.5*G))  // m/s/s, Q16, "
#define BASIC_LOADED_Z_THRESH       (FX_FLTTOFIX_Q16(1.1  ))  // unitless, Q16
#define BASIC_SIGNAL_DELAY          (FX_FLTTOFIX_Q16(0.11))   // seconds, Q16
#define BASIC_HOME_THRESH           (FX_FLTTOFIX_Q16(0.15))   // unitless threshold, Q16
#define BASIC_HOME_WINDOW           (FX_FLTTOFIX_Q16(0.07))   // seconds, Q16
#define BASIC_REVERSAL_THRESH       (FX_FLTTOFIX_Q16(1.1))    // unitless threshold, Q16
#define BASIC_SHAKE_DIR             (FX_FLTTOFIX_Q16(1.0))    // unitless threshold, Q16
#define BASIC_REST_WINDOW           (FX_FLTTOFIX_Q16(0.1))    // seconds, Q16
#define BASIC_DATA_COLS             (3)

#define BASIC_REL_REST_ACCEL_TIME_WINDOW (FX_FLTTOFIX_Q16(0.1))           // seconds
#define BASIC_REL_REST_ANGLE_THRESH      (FX_FLTTOFIX_Q16(15.0*PI/180.0)) // radians, Q16
#define BASIC_REL_REST_DETECT_THRESH_SPI (FX_FLTTOFIX_Q16(0.5*G))         // m/s/s, Q16

/*============================================================================
  Type Declarations
  ===========================================================================*/

enum BASIC_GESTURE_STATES
{
  BASIC_GESTURE_UNKNOWN           = 0,
  BASIC_GESTURE_PUSH              = 1,
  BASIC_GESTURE_PULL              = 2,
  BASIC_GESTURE_SHAKE_AXIS_LEFT   = 3,
  BASIC_GESTURE_SHAKE_AXIS_RIGHT  = 4,
  BASIC_GESTURE_SHAKE_AXIS_TOP    = 5,
  BASIC_GESTURE_SHAKE_AXIS_BOTTOM = 6,
  BASIC_GESTURE_SHAKE_AXIS_UNK    = 7
};

typedef struct {
  q16_t   sample_rate;     // sample rate, Hz, Q16
  int32_t sleep;           // after gesture is generated, sleep for this long, seconds, Q16
  q16_t   push_threshold;  // m/s/s, Q16
  q16_t   pull_threshold;  // m/s/s, Q16
  q16_t   shake_threshold; // m/s/s, Q16
  int32_t internal_config_param1;
  int32_t internal_config_param2;
  int32_t internal_config_param3;
  int32_t internal_config_param4;
} basic_gestures_config_s;

typedef struct {
  q16_t   a[BASIC_DATA_COLS]; // accel, m/s/s (Q16)
  int32_t motion_state;       // rest, motion, unknown
} basic_gestures_input_s;

typedef struct {
  int32_t basic_state;
  int32_t event;
  sns_sam_timestamp timestamp;
} basic_gestures_output_s;

typedef struct {
  basic_gestures_config_s config;
  buffer_type buf;
  int32_t buf_sprd[BASIC_DATA_COLS];
  int32_t max_sprd[BASIC_DATA_COLS];
  int32_t pending;
  int32_t pending_value;
  int32_t z_at_rest;
  int32_t in_home_zone;
  int32_t home_zone;
  int32_t to_delay;
  int32_t resting;
  int32_t rest_window;
  int32_t home_window;
  int32_t sleep;
  int32_t signal_delay;
  int32_t to_sleep;
  int32_t basic_state;
  int32_t input_motion_state;  //save the motion_state from RMD input; rest, motion, unknown
} basic_gestures_state_s;

/* basic gestures persisitant data */
typedef struct {
  bool regDataRecv; /* If the registry data has been received*/
  int32_t sleep;           // after gesture is generated, sleep for this long, seconds, Q16
  q16_t   push_threshold;  // m/s/s, Q16
  q16_t   pull_threshold;  // m/s/s, Q16
  q16_t   shake_threshold; // m/s/s, Q16
  int32_t internal_config_param1;
  int32_t internal_config_param2;
  int32_t internal_config_param3;
  int32_t internal_config_param4;
  uint64_t power; /* Consumption for the accel sensor as reported by SMGR */
  q16_t defSampleRate; /* Default sampling rate if none specified */
  q16_t minSampleRate;
  q16_t maxSampleRate;
  q16_t defSensorReportRate;
  sns_sam_sensor_uid const *rmdSUID;   /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *accelSUID; /* SUID saved in dep_sensors_met() */
} basic_gestures_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the Basic Gestures algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err basic_gestures_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

#endif /* SHAKE_GESTURES_H */
