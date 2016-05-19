#ifndef SPI_H
#define SPI_H

/*============================================================================
  @file spi.h

  Stationary position indicator header file

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/common/usam/algo/qmd/common/inc/spi.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2011-03-20  ad   remove cust header file inclusion and non API constants
  2011-03-14  jh   include custsensorsimg.h only in DSPS build
  2011-01-24  ad   initial version

============================================================================*/

#include <stdint.h>
#include "circular_buffer.h"
#include "fx_iir.h"

#define SPI_ACCEL_COLS               (3)

enum SPI_STATES
{
  SPI_UNKNOWN = 0,
  SPI_REST    = 1,
  SPI_MOVING  = 2
};

typedef struct
{
  int32_t sample_rate;        // Hz      (Q16)
  int32_t detect_threshold;   // accel, m/s/s, (Q16)
  int32_t accel_window_time;  // seconds (Q16)
  int32_t op_interval_time;   // seconds (Q16)
  int32_t filter_enabled;     // boolean
  int32_t fc;                 // filter cutoff frequency in Hz, if enabled (Q16)
} spi_config_s;

typedef struct
{
  int32_t a[SPI_ACCEL_COLS];  // accel, m/s/s, (Q16)
} spi_input_s;

typedef struct
{
  int32_t spi_state;
  int32_t event;
} spi_output_s;

typedef struct
{
  spi_config_s config;
  buffer_type buf;
  int32_t buf_sum[SPI_ACCEL_COLS];
  int32_t buf_sum_sq[SPI_ACCEL_COLS];
  int32_t spi_state;
  fx_iir_state_s *fx_iir_lpf;
  int32_t motion_timer;
  int32_t op_interval_samples;
  int32_t detect_threshold;
} spi_state_s;

int32_t spi_sam_mem_req(spi_config_s *config_data);
spi_state_s* spi_sam_state_reset(spi_config_s *config_data,
                                 void *mem);
void spi_sam_update(spi_state_s *spi_algo,
                    spi_input_s *input,
                    spi_output_s *output);

#endif /* SPI_H */
