#ifndef TILT_DETECTOR_H
#define TILT_DETECTOR_H

/*============================================================================
 @file tilt_detector.h

 tilt detection header file

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

/*============================================================================
 EDIT HISTORY

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.

 when        who  what, where, why
 ----------  ---  -----------------------------------------------------------
 2014-06-03  tc   Added support for AMD input and various improvements
 2014-05-05  px   initial version

 ============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "fixed_point.h"
#include "sns_buffer.h"
#include "sns_sam_qmd_v01.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define TILT_ACCEL_COLS                  (3)               // # of accel axes
#define TILT_SAMPLE_RATE                 (10.0)            // Hz
#define TILT_ACCEL_TIME_WINDOW_DEF       (2.0)             // seconds
#define TILT_INIT_ACCEL_TIME_WINDOW_DEF  (1.0)             // seconds
#define TILT_ANGLE_THRES_DEF             (35.0*PI/180.0)   // radians
#define TILT_GRAV_BUFF_LEN_DEF           (2.0)             // seconds

/*============================================================================
  Type Declarations
  ===========================================================================*/

// Tilt Detector algorithm configuration structure
typedef struct
{
  q16_t sample_rate;             // Hz (Q16)
  float angle_threshold;         // radians
  float init_accel_window_time;  // time window to average accel for initial grav (seconds)
  float accel_window_time;       // time window to average accel for current grav (seconds)
} tilt_config_s;

// Tilt Detector algorithm input type enumeration
typedef enum
{
  TILT_INPUT_ACCEL = 0,
  TILT_INPUT_AMD   = 1
} tilt_input_type_e;

// Tilt Detector algorithm input structure
typedef struct
{
  union
  {
    /* accel, m/s/s, Q16 */
    q16_t accel[TILT_ACCEL_COLS];
    /* device motion state */
    sns_sam_motion_state_e_v01 amd_state;
  } input_data;
  tilt_input_type_e input_type;
} tilt_input_s;

// Tilt Detector output structure
typedef struct
{
  /* reported event timestamp, end of the observation period, SSC ticks */
  uint32_t event_ts;
} tilt_output_s;

// Tilt Detector algorithm state structure
typedef struct
{
  /* accel and dot product buffers */
  sns_buffer_type accel_buf;
  tilt_config_s config;
  float dprod_threshold;              //dot product threshold
  // todo: instead of using grav_init_set, considering checking to see if reference_grav is non-zero
  bool grav_init_set;                 //indicates if the initial gravity has been stored
  float reference_grav[TILT_ACCEL_COLS];   //initial gravity vector
  float cos_theta_sq; // cosf(config_data->angle_threshold)^2;
  uint32_t init_accel_window_size;    //average window size for initial gravity calculation
  uint32_t accel_window_size;         //average window size for current gravity calculation
  sns_sam_motion_state_e_v01 motion_state;
  bool accel_status;                  // Whether buffered accel should be enabled
} tilt_state_s;

/**
* Tilt Detector persistent data
*/
typedef struct {
  /* Accel availibility */
  bool accelAvailable;
  /* Registry data available*/
  bool regDataAvailable;
  /* SAM AMD algorithm available */
  bool amdAvailable;
  uint64_t power;
  uint64_t minSample;
  uint64_t maxSample;
  tilt_config_s defConfig;
  /* Default sensor reporting rate */
  q16_t sensor_report_rate;
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *amdSUID;
} tilt_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
 * Calculates moving average if buffer has enough samples to
 * average. If buffer does not have sufficient samples, no filtering is
 * done. Filtering is performed on all the accel cols.
 *
 * @param[i] buffer: Circular buffer containing unfiltered accel samples
 * @param[i] window: Number of samples to average over
 * @param[o] xyz_sum: Sum of all of the samples in the window
 * @param[o] xyz_sum_mag_sq: Squared magnitude of the sum of the samples
 */
void tilt_box_filter(
    sns_buffer_type * buffer,
    uint32_t window,
    float xyz_sum[TILT_ACCEL_COLS],
    float *xyz_sum_mag_sq);

#endif /* TILT_DETECTOR_H */
