#ifndef _PEDOMETER_H
#define _PEDOMETER_H

/*============================================================================
  @file pedometer.h

  Pedometer wrapper header file

  Copyright (c) 2012-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include "sns_sam_algo_api.h"
#include "sns_sam_ped_v01.h"
#include "core_pedometer.h"

/*============================================================================
  Type Declarations
  ===========================================================================*/
// Pedometer algorithm configuration structure
typedef struct
{
   q16_t sample_rate;          // sample rate, Hz, Q16
   uint32_t step_count_threshold; // number of steps after which output is updated
   q16_t report_period;        // report period, seconds, Q16
} ped_config_s;

// Pedometer algorithm input structure
typedef core_ped_output_s ped_input_s;

// Client specific output structure
typedef core_ped_output_s ped_output_s;

// Pedometer algorithm state structure
typedef struct
{
   ped_config_s config;        // Algo config
   ped_output_s output;        // Statistics of latest step
   uint32_t step_count_offset; // First step count reported by core Ped
   uint32_t last_reported_step_count;// Last step count reported to the client
   int32_t step_count_error_offset; // First step count error reported by core Ped
} ped_state_s;

/**
* Pedometer persisitant data
*/
typedef struct {
  bool corePedAvailable; /* Core Pedometer algo availibility */
  uint64_t power;
  uint64_t minSample;
  uint64_t maxSample;
  uint64_t minReport;
  uint64_t maxReport;
  uint64_t revision;
  uint32_t sample_rate_def;
  sns_sam_sensor_uid const *corePedSUID;
} ped_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the Pedometer algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err ped_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

#endif /* _PEDOMETER_H */