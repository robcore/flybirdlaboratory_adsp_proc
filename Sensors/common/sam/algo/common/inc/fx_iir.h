#ifndef FX_IIR_H
#define FX_IIR_H

/*============================================================================
  @file fx_iir.h

  IIR filter utility header file 

  Copyright (c) 2010-2011 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/common/sam/algo/common/inc/fx_iir.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2011-01-24  ad   initial version  

============================================================================*/

#include <stdint.h>
#include "matrix.h"

#define FX_IIR_FILTER_ORDER 2

typedef struct
{
  int32_t fc; // LPF cutoff frequency (Q16)
  int32_t fs; // sample frequency (Q16)
  int32_t channels;
} fx_iir_config_s;

typedef struct
{
  int32_t *filter_input; // pointer to an array of length channels
} fx_iir_input_s;

typedef struct
{
  int32_t *filter_output; // pointer to an array of length channels
} fx_iir_output_s;

typedef struct
{
  fx_iir_config_s config;
  int32_t num[FX_IIR_FILTER_ORDER+1];
  int32_t den[FX_IIR_FILTER_ORDER+1];  
  matrix_type input;
  matrix_type output;
  int32_t settling_samples;
  int32_t filter_count;
} fx_iir_state_s;

int32_t fx_iir_lpf_mem_req(fx_iir_config_s *config_data);
fx_iir_state_s* fx_iir_lpf_state_reset(fx_iir_config_s *config_data, 
                                       void *mem);
void fx_iir_lpf_update(fx_iir_state_s *fx_iir, 
                       fx_iir_input_s *input,
                       fx_iir_output_s *output);
int32_t filter_settled(fx_iir_state_s *fx_iir);

#endif /* FX_IIR_H */
