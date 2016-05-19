/*=============================================================================
  Copyright (c) 2011 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.
=============================================================================*/

#ifndef _INTEG_ANGLE_H
#define _INTEG_ANGLE_H

#include "fixed_point.h"
#include "comdef.h"

#define INTEG_ANGLE_MIN_GYRO_RATE 25 // Hz
#define INTEG_ANGLE_MAX_GYRO_RATE 100   // Hz
#define INTEG_ANGLE_DEF_GYRO_RATE 25   // Hz
#define INTEG_ANGLE_RESULT_LIMIT  3.14159265f  // radians

#define IA_MIN_GYRO_RATE_Q16  FX_FLTTOFIX_Q16(INTEG_ANGLE_MIN_GYRO_RATE)
#define IA_MAX_GYRO_RATE_Q16  FX_FLTTOFIX_Q16(INTEG_ANGLE_MAX_GYRO_RATE)
#define IA_DEF_GYRO_RATE_Q16  FX_FLTTOFIX_Q16(INTEG_ANGLE_DEF_GYRO_RATE)

#define FX_IA_RES_LIMIT  (FX_FLTTOFIX_Q16(INTEG_ANGLE_RESULT_LIMIT))

typedef struct
{
  int32 sample_rate; // sample rate, Hz, Q16
  int32 clip_threshold;   // threshold to clip
  uint32 init_ts;         // timestamps at which this algo was initialized
                          // used to distinguish between different algo
                          // instances for the SAM
} integ_angle_config_struct;

typedef struct
{
  int32 gyro[3]; // gyro, m/s/s, Q16
  uint32 ts;     // rest, motion, unknown
} integ_angle_input_struct;

typedef struct
{
  int32 angle_change[3];
  uint32 ts;
} integ_angle_output_struct;

typedef struct
{
  integ_angle_config_struct config;
  int32 angle_change[3];
  int32 last_gyro[3];
  uint32 last_gyro_ts;
  boolean first_reading;
} integ_angle_state_struct;

int32 integ_angle_sam_mem_req(integ_angle_config_struct *config_data);
integ_angle_state_struct* integ_angle_sam_state_reset(integ_angle_config_struct *config_data, void *mem);
void integ_angle_sam_update(integ_angle_state_struct *integ_angle_algo,
                    integ_angle_input_struct *input,
                    integ_angle_output_struct *output);

#endif /* _INTEG_ANGLE_H */
