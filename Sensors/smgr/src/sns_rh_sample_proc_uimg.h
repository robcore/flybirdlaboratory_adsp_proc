#ifndef SNS_RH_SAMPLE_PROC_UIMG_H
#define SNS_RH_SAMPLE_PROC_UIMG_H

/*============================================================================

  @file sns_rh_sample_proc_uimg.h

  @brief
  This file contains sample processing function for Request Handler task
  that executes in microImage

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_sample_proc_uimg.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $*/
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-11-04  jc   Changed accumulator type to float to avoid overflow
  2014-06-16  pn   Avoided unnecessary recalculation of CIC timestamp adjustment 
  2014-06-16  pn   Removed references to unused circular buffer
  2014-05-12  tc   Changed CIC input freq to a fixed point Q16 value (Q16 is
                   used because the Q6 does not have hardware-support for
                   floating point division)
  2014-04-29  pn   Initial version (renamed from sns_rh_sample_proc.h)
 
============================================================================*/
#include "sns_ddf_common.h"
#include "sns_rh.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_depot.h"

/*===========================================================================

                   SMGR MACRO

===========================================================================*/


/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/

/*===========================================================================

                   STRUCTURE DEFINITIONS

===========================================================================*/
struct sns_rh_cic_obj_s
{
  float             accumulator[SNS_SMGR_SENSOR_DIMENSION_V01];
  q16_t             input_frequency;
  uint16_t          count;
  uint16_t          factor;
  uint8_t           axis_cnt;
  sns_ddf_status_e  status;
  sns_ddf_time_t    delay_ticks;
};

struct sns_rh_interpolator_obj_s
{
  /** interpolator object can produce new sample with desired_timestamp 
      when sample1's timestamp <= desired_timestamp <= sample2's timestamp */
  const sns_smgr_sample_s* sample1_ptr; /**< 1st known sample */
  const sns_smgr_sample_s* sample2_ptr; /**< 2nd known sample */
  sns_ddf_time_t       desired_timestamp; 
  uint32_t             interval_ticks; /**< interval computed from desired frequency */
};

/*===========================================================================

                          FUNCTIONS

===========================================================================*/
extern void sns_rh_interpolator_update(
  sns_rh_interpolator_obj_s*  int_obj_ptr,
  const sns_smgr_sample_s*    sample_ptr);

extern sns_ddf_status_e sns_rh_interpolate(
  sns_rh_interpolator_obj_s*  int_obj_ptr,
  int32_t                     dest_sample[SNS_SMGR_SENSOR_DIMENSION_V01]);

extern uint8_t sns_rh_apply_calibration(
  q16_t                       sample_data[],
  sns_smgr_ddf_sensor_s*      ddf_sensor_ptr,
  uint8_t                     cal_sel);

extern sns_ddf_status_e sns_rh_process_sample(
  sns_rh_rpt_item_s*          item_ptr,
  const sns_smgr_sample_s*    sample_ptr,
  sns_ddf_time_t*             timestamp_ptr,
  int32_t                     dest_data[SNS_SMGR_SENSOR_DIMENSION_V01]);

#endif /* SNS_RH_SAMPLE_PROC_UIMG_H */

