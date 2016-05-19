#ifndef REL_REST_H
#define REL_REST_H

/*============================================================================
  @file rel_rest.h

  Relative rest detector header file

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/common/sam/algo/common/inc/rel_rest.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-03-16  lka  removed state variable for clearing buffer
  2012-12-08  lka  added support for episodic processing of sensor samples
  2011-03-20  ad   remove non API constants
  2011-01-24  ad   initial version

============================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include "fixed_point.h"
#include "spi.h"

#define REL_REST_ACCEL_COLS        (3)

enum REL_REST_STATES
{
  REL_REST_UNKNOWN = 0,
  REL_REST_REST    = 1,
  REL_REST_MOVING  = 2
};

typedef struct
{
  int32_t sample_rate;             // Hz (Q16)
  int32_t accel_window_time;       // seconds, Q16
  int32_t gravity_angle_threshold; // radians, Q16
  spi_config_s spi_config;
} rel_rest_config_s;

typedef struct
{
  int32_t a[REL_REST_ACCEL_COLS];  // accel, m/s/s, Q16
} rel_rest_input_s;

typedef struct
{
  int32_t motion_state;
  int32_t event;
} rel_rest_output_s;

typedef struct
{
  spi_state_s *spi_algo;
  buffer_type buf;
  fx_iir_state_s *fx_iir_lpf;
  rel_rest_config_s config;
  int32_t rel_rest_state;
  int32_t angle_threshold;
} rel_rest_state_s;

int32_t rel_rest_sam_mem_req(rel_rest_config_s *config_data);
rel_rest_state_s* rel_rest_sam_state_reset(rel_rest_config_s *config_data,
                                           void *mem);
void rel_rest_sam_update(rel_rest_state_s *rel_rest_algo,
                         rel_rest_input_s *input,
                         rel_rest_output_s *output);

#endif /* REL_REST_H */
