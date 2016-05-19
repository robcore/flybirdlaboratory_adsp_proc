#ifndef _CORE_PEDOMETER_H
#define _CORE_PEDOMETER_H

/*============================================================================
  @file core_pedometer.h

  Core Pedometer header file

  Copyright (c) 2012-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include "sns_buffer.h"
#include "circular_buffer.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_internal_ped_v01.h"
#include "sns_sam_amd_v01.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define PED_ACCEL_COLS    3 // No of accelerometer axes

#ifdef SNS_USES_ISLAND
#define SNS_PED_UIMAGE_CODE __attribute__((section ("text.PED")))
#define SNS_PED_UIMAGE_DATA __attribute__((section ("data.PED")))
#define SNS_PED_UIMAGE_BSS __attribute__((section ("bss.PED")))
#else
#define SNS_PED_UIMAGE_CODE
#define SNS_PED_UIMAGE_DATA
#define SNS_PED_UIMAGE_BSS
#endif /* USES_ISLAND */

#define FILTER_ORDER     (4)
#define FILTER_NUM_SECTIONS (FILTER_ORDER/2)

/*============================================================================
  Type Declarations
  ===========================================================================*/

// Pedometer algorithm configuration structure
typedef struct
{
   q16_t sample_rate;          // sample rate, Hz, Q16
   float step_threshold;       // Min accel magnitude to be considered a step, in m/s/s
   float swing_threshold;      // Min accel magnitude for swing detection, in m/s/s
   float step_prob_threshold;  // Probability threshold for step detection
} core_ped_config_s;

// Pedometer algorithm input structure
typedef struct
{
   q16_t  accel[ PED_ACCEL_COLS ]; // accel, m/s/s, Q16
   sns_sam_motion_state_e_v01 motionState;
} core_ped_input_s;

// Client specific output structure
typedef struct
{
   uint8_t  step_event;      // Indicates if a step event has been detected
   uint8_t  step_confidence; // Probability with which latest step was detected
                             // Ranges from 0 to 100 (in percentage)
   uint32_t step_count;      // Count of steps detected since the last client
                             // initiated reset
   int32_t  step_count_error;// Error metric associated with reported step
                             // count, in steps
   float    step_rate;       // Rate in Hz at which steps are detected since
                             // the last client report/reset whichever is later
   sns_sam_timestamp timestamp;       // Timestamp of input corresponding to the latest
                             // step detection (in ticks)
} core_ped_output_s;

// Chebyshev filter
typedef struct
{
   float a[FILTER_NUM_SECTIONS][2];
   float b[FILTER_NUM_SECTIONS];
   float gain;
   float u0_delay1;
   float u0_delay2;
   float u1_delay1;
   float u1_delay2;
   float u2_delay1;
   float u2_delay2;
   int num_settling_samples;
   int num_samples;
} chebyshev_filter_s;

// Pedometer algorithm state structure
typedef struct
{
   core_ped_config_s config;   // Algo config
   float sample_rate;          // Average sample rate, in Hz
   chebyshev_filter_s chebyshev_filter; // LPF state
   sns_sam_timestamp prev_input_timestamp; // Timestamp of previous sample
   sns_buffer_type accel_buf;  // Circular buffer of filtered accel magnitudes
   buffer_type timestamp_buf;  // Circular buffer of accel sample timestamps
   sns_sam_timestamp xcorr_timestamp;   // Time at which autocorrelation was calculated
   sns_sam_timestamp periodic_time;     // Timestamp of sample at which periodicity was established
   float deltaTx;              // Step interval calculated using autocorrelation
   uint32_t prev_valley_index; // Index of previous valley in accel_buf
   sns_sam_timestamp prev_valley_time;  // Timestamp of sample at which previous valley was detected
   float max_spread;           // Max accel spread between two consecutive valleys
   float pstate[2];            // Vector of walking and fidgeting probabilities
   core_ped_output_s output;   // Current output
   uint32_t swing_step_count;  // No of steps detected in swing detection stage
   uint32_t overcount;         // No of steps with 0.49 < step_prob <= 0.7
   uint32_t undercount;        // No of steps with 0.3 < step_prob <= 0.49
   bool accel_status;          // Whether buffered accel should be enabled
   bool prev_valley_exists;    // Indicates if valley was detected before
   int8_t periodic;            // Indicates if acceleration is periodic
   int8_t prev_in_step;        // Sign of previous accel spread
} core_ped_state_s;

/**
* Pedometer persisitant data
*/
typedef struct {
  bool accelAvailable; /* Accel availibility */
  bool regDataAvailable; /* Registry data available*/
  bool amdAvailable; /* SAM AMD algorithm available */
  q16_t reportRate; /* Default reporting rate */
  uint64_t power;
  uint64_t minSample;
  uint64_t maxSample;
  core_ped_config_s defConfig;
  int32_t sensor_report_rate;
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *amdSUID;
} core_ped_persist_s;

#endif /* _CORE_PEDOMETER_H */