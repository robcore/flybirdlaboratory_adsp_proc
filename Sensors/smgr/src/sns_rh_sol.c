/*=============================================================================
  @file sns_rh_sol.c

  This file contains functions for managing the Standing Orders List (SOL) of
  the Request Handler task

******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_sol.c#13 $ */
/* $DateTime: 2015/05/14 20:46:38 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-05-01  pn   Updates more bookkeeping info of pending reports
  2015-04-21  pn   Removed references to deprecated field new_sample_idx
  2015-04-07  pn   Updates pending report after its predecessor is flushed
  2015-02-05  pn   No need to reschedule report to be sent early when WM is 1
  2015-02-03  pn   - Changed reportable initial sample timestamp
                   - Fixed report schedule adjustment errors
                   - SubHz requests will always use bigImage depot
  2015-01-23  pn   Periodic-like Buffering reports do not need to be flushed
  2015-01-13  pn   Fixed Flush command handling
  2014-12-30  pn   - No longer necessary to set event_done_tick
                   - Does not update sensor event when adding/deleting event gated requests
  2014-12-19  pn   Updates sensor events when report is deleted
  2014-12-18  tc   Fixed the minimum calculation when setting the report timer
  2014-12-16  pn   Fixed memory leaks when replacing reports
  2014-12-09  pn   Updates event_done_tick only if sensor is not being configured
  2014-12-05  pn   - Handles report delete the same regardless of how it's initiated
                   - Removed a flawed condition in sns_rh_select_item_depot()
  2014-12-03  pn   - Handles report replacement for Periodic reports
                   - Uses uImage depot whenever possible
  2014-11-24  pn   Fixed report interval calculation for reports with multiple 
                   FIFO sensors
  2014-11-18  jc   Removed quantization error in report time interval
  2014-11-14  pn   Sends sensor status indication when updating client count
  2014-11-12  pn   Sets depot_ptr of report item before releasing sensor mutex
  2014-11-11  tc   Allow subHz sampling requests to be periodic-like
  2014-11-06  pn   Correctly selects sample depot
  2014-11-04  pn   Enables sensor events discrimately
  2014-10-28  jms  Rpt sending with effective_rate_hz=0 fix
  2014-10-26  pn   Resets bookkeeping info when using bigImage depot
  2014-10-22  pn   Buffering report scheduling improvements
  2014-10-15  rt   Added 'deleting' state to reports
  2014-10-14  pn   Updated algorithm for making Buffering request periodic-like 
  2014-10-02  pn   - Uses ODR in determining which depot to assign to report item
                   - Synchronizes reports with same report rate
  2014-09-25  pn   - Selects appropriate depot for report item
                   - Keeps track whether big-image depot is in use
  2014-09-23  pn   Added QDSS logging
  2014-09-16  pn   Event gated reports can be deactivated and reactivated
  2014-09-11  pn   Report rate of 0 should not be rejected
  2014-09-11  pn   Protects all shared sensor state variables, not just client DB
  2014-09-08  pn   Maintains external report rate 
  2014-09-04  pn   Simplified report interval calculation
  2014-09-02  rt   Added signal for UPDATE_REPORT_TIMER
  2014-08-08  pn   Replaced SMGR_U_ALLOC_STRUCT with SMGR_ANY_ALLOC_STRUCT
  2014-08-05  pn   FIFO must be flushed when clients send Flush command
  2014-07-31  pn   Obsoleted FEATURE_TEST_DRI
  2014-07-25  pn   Makes sure report is set up completely before flushing it
  2014-07-21  pn   Restructured to support event_gated_buffering
  2014-06-16  pn   Reduced unnecessary updates to report info; removed unused code
  2014-06-16  pn   Removed references to unused circular buffer
  2014-05-28  tc   SubHz Sampling
  2014-05-12  tc   Converted frequencies to fixed point, Q16. This is to
                   accommodate frequencies less than 1. Q16 fixed point is
                   used, instead of floating point, because the Q6 does not
                   have hardware-support for floating point division.
                   Also added support for the overloaded sub-Hz sampling rate
                   fields in the SMGR API.
  2014-05-13  vy   Added interface to PM for stat reporting
  2014-04-29  pn   Refactored to support microImage
  2014-04-24  pn   Initial version

============================================================================*/

#define __SNS_MODULE__ SNS_RH

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <float.h>    // This is included to gain access to the FLT_MAX macro

#include "sns_memmgr.h"
#include "sns_rh_internal_svc.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_mr.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"
#include "sns_smgr_pm_if.h"

#ifdef SNS_QDSP_SIM
#include "sns_qdsp_playback_utils.h"
extern int playback_next_sample_ts;
#endif

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define RH_SOL_INTERPLTN_RANGE_LOW_PCT      10
#define RH_SOL_INTERPLTN_RANGE_HIGH_PCT     5

/* When ratio of max sampling rate and report rate in a buffering request 
   is below this threshold the report is considered periodic-like. */
#define RH_SOL_PERIODIC_LIKE_RATIO_THRESHOLD        1.9f


/*===========================================================================

                   MACROS

===========================================================================*/
/* check if ( a/b >(1-r/100)
   Note: a and b MUST be in the same format */
#define RH_SOL_LO_THRESHOLD_TEST(a,b,r) ( ((b)*(100-(r))) <= (a)*100 )
/* check if ( a/b < (1+r/100)
   Note: a and b MUST be in the same format */
#define RH_SOL_HI_THRESHOLD_TEST(a,b,r) ( ((b)*(100+(r))) >= (a)*100 )


/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local Functions
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_rh_cic_init

===========================================================================*/
/*!
  @brief Initializes CIC filter object

  @param[io] cic_obj_ptr: CIC filter state structure
  @param[i] factor: Decimation factor, must be >0, >= 2 for practical uses
  @param[i] freq_q16: frequency of input data
  @param[i] num_axes: Number of axes (example 3 for XYZ)

  @return
    void
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_cic_init(
  sns_rh_cic_obj_s* cic_obj_ptr,
  uint16_t          factor,
  q16_t             freq_q16,
  uint8_t           num_axes)
{
  sns_ddf_odr_t in_freq_hz = DDF_FIXTOODR_FLOOR_Q16(freq_q16);
  SNS_OS_MEMZERO(cic_obj_ptr, sizeof(sns_rh_cic_obj_s));
  cic_obj_ptr->factor          = factor;
  cic_obj_ptr->input_frequency = freq_q16;
  cic_obj_ptr->axis_cnt        = num_axes;
  cic_obj_ptr->delay_ticks     = 
    sns_em_convert_usec_to_localtick((1000000/in_freq_hz)*(factor-1)/2);
  SNS_SMGR_PRINTF4(
    HIGH, "cic_init - factor=%u freq=0x%x/%u delay=%u",
    factor, freq_q16, in_freq_hz, cic_obj_ptr->delay_ticks);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_test_rate_thresholds

===========================================================================*/
SMGR_STATIC void sns_rh_sol_test_rate_thresholds(sns_rh_rpt_item_s* item_ptr)
{
  q16_t dev_sampling_rate =
    item_ptr->sampling_rate_hz * item_ptr->sampling_factor;

  item_ptr->rate_thresholds_met = false;
  if ( RH_SOL_LO_THRESHOLD_TEST(item_ptr->ddf_sensor_ptr->depot_data_rate, 
                                dev_sampling_rate, 
                                RH_SOL_INTERPLTN_RANGE_LOW_PCT) &&
       RH_SOL_HI_THRESHOLD_TEST(item_ptr->ddf_sensor_ptr->depot_data_rate, 
                                dev_sampling_rate,
                                RH_SOL_INTERPLTN_RANGE_HIGH_PCT) )
  {
    item_ptr->rate_thresholds_met = true;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_compute_cic_factor

===========================================================================*/
SMGR_STATIC void sns_rh_sol_compute_cic_factor(
  sns_rh_rpt_item_s* item_ptr)
{
  uint16_t cic_factor;
  q16_t    cic_frequency;
  uint16_t old_count = item_ptr->cic_obj.count;
  /* ---------------------------------------------------------------------- */

  if ( SMGR_BIT_CLEAR_TEST(item_ptr->flags, RH_RPT_ITEM_FLAGS_DECIM_FILTER_B) )
  {
    cic_factor = 1;
    cic_frequency = item_ptr->sampling_rate_hz;
  }
  else
  {
    cic_factor = item_ptr->sampling_factor;
    
    if ( SMGR_BIT_TEST(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B) &&
         item_ptr->rate_thresholds_met )
    {
      cic_frequency = item_ptr->ddf_sensor_ptr->depot_data_rate;
    }
    else
    {
      cic_frequency = item_ptr->sampling_rate_hz * cic_factor;
    }
  }

  if ( (cic_factor != item_ptr->cic_obj.factor) ||
       (cic_frequency != item_ptr->cic_obj.input_frequency) )
  {
    sns_rh_cic_init(&item_ptr->cic_obj, cic_factor, cic_frequency,
                    item_ptr->depot_ptr->num_axes);
  }
  SNS_SMGR_PRINTF4(
    LOW, "comp_cic_factor - factor=%d freq=0x%X count=%u/%u",
    cic_factor, cic_frequency, old_count, item_ptr->cic_obj.count);
}

/*===========================================================================

  FUNCTION:   sns_rh_calculate_sample_factor

===========================================================================*/
SMGR_STATIC uint8_t sns_rh_calculate_sample_factor( 
  const sns_smgr_ddf_sensor_s* ddf_sensor_ptr, 
  q16_t                        sampling_rate_hz)
{
  uint8 sample_factor1, sample_factor2, sample_factor;
  q16_t depot_data_rate_hz = ddf_sensor_ptr->depot_data_rate;
  /* ---------------------------------------------------------------------- */

  if ( sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) ||
       (depot_data_rate_hz <= sampling_rate_hz) )
  {
    sample_factor = 1;
  }
  else
  {
    sample_factor1 = depot_data_rate_hz/sampling_rate_hz;
    if ( depot_data_rate_hz == sample_factor1*sampling_rate_hz )
    {
      sample_factor = sample_factor1;
    }
    else
    {
      sample_factor2 = sample_factor1+1;
      /* choose sample factor so depot rate divided by sample rate 
         is closer to sample rate
        if ( (dr/sf1 - sr) <= (sr - dr/sf2) )
           choose sf1 
        else
           choose sf2 
       */
      if ( (depot_data_rate_hz - sampling_rate_hz*sample_factor1)*sample_factor2 <=
           (sampling_rate_hz*sample_factor2 - depot_data_rate_hz)*sample_factor1 )
      {
        sample_factor = sample_factor1;
      }
      else
      {
        sample_factor = sample_factor2;
      }
    }
  }
  SNS_SMGR_PRINTF1(MED, "calc_sample_factor - factor=%u", sample_factor);
  return sample_factor;
}

/*===========================================================================

  FUNCTION:   smgr_interpolation_required

===========================================================================*/
/*!
  @Detail Interpolation is not required if
          - sensor is event sensor, or
          - the requested rate is the polling rate, or
          - the requested rate falls within threshold delta of DRI rate

  @param[i] item_ptr - the report item associated with a sensor

  @return true if interpolation is required
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_interpolation_required(
  const sns_rh_rpt_item_s* item_ptr)
{
  bool interpolation_required = false;

  if ( !sns_smgr_ddf_sensor_is_event_sensor(item_ptr->ddf_sensor_ptr) )
  {
    if ( SMGR_BIT_TEST(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B) )
    {
      if ( !item_ptr->rate_thresholds_met )
      {
        interpolation_required = true;
      }
    }
    else
    {
      if ( item_ptr->ddf_sensor_ptr->depot_data_rate != item_ptr->sampling_rate_hz)
      {
        interpolation_required = true;  
      }
    }
  }
  return interpolation_required;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_determine_sample_quality

===========================================================================*/
SMGR_STATIC void sns_rh_sol_determine_sample_quality(
  sns_rh_rpt_item_s* item_ptr)
{
  /* determines sample quality to be used in indications */
  if ( sns_rh_sol_interpolation_required(item_ptr) )
  {
    if ( item_ptr->cic_obj.factor > 1 )
    {
      item_ptr->quality = SNS_SMGR_ITEM_QUALITY_INTERPOLATED_FILTERED_V01;
      item_ptr->interpolator_obj.interval_ticks =
        sns_smgr_get_sched_intval(item_ptr->cic_obj.input_frequency);
    }
    else
    {
      item_ptr->quality = SNS_SMGR_ITEM_QUALITY_INTERPOLATED_V01;
      item_ptr->interpolator_obj.interval_ticks = item_ptr->sampling_interval;
    }
  }
  else
  {
    if ( item_ptr->cic_obj.factor > 1 )
    {
      item_ptr->quality = SNS_SMGR_ITEM_QUALITY_FILTERED_V01;
    }
    else
    {
      item_ptr->quality = SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01;
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_init_interp_time

===========================================================================*/
void sns_rh_sol_init_interp_time(sns_rh_rpt_item_s* item_ptr)
{
  if ( ((item_ptr->quality == SNS_SMGR_ITEM_QUALITY_INTERPOLATED_V01) ||
        (item_ptr->quality == SNS_SMGR_ITEM_QUALITY_INTERPOLATED_FILTERED_V01)) &&
       (item_ptr->interpolator_obj.interval_ticks != 0) )
  {
    sns_rh_interpolator_obj_s* iobj_ptr = &item_ptr->interpolator_obj;
    iobj_ptr->desired_timestamp =
      (item_ptr->ts_last_sent + iobj_ptr->interval_ticks)/
      iobj_ptr->interval_ticks * iobj_ptr->interval_ticks;

    SNS_SMGR_PRINTF2(
      LOW, "init_interp - desired=%u last_sent=%u",
      iobj_ptr->desired_timestamp, item_ptr->ts_last_sent);

    while ( (iobj_ptr->interval_ticks >> 1) >
            (iobj_ptr->desired_timestamp - item_ptr->ts_last_sent) )
    {
      iobj_ptr->desired_timestamp += iobj_ptr->interval_ticks;
    }
    SNS_SMGR_PRINTF3(
      MED, "init_interp - ts1=%u desired=%u ts2=%u",
      iobj_ptr->sample1_ptr ? iobj_ptr->sample1_ptr->time_stamp : 0,
      iobj_ptr->desired_timestamp,
      iobj_ptr->sample2_ptr ? iobj_ptr->sample2_ptr->time_stamp : 0);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_compute_effective_rate

===========================================================================*/
/*!
  @brief Computes the effective sampling rate of the given sensor/data type.

  @detail

  @param[i]  item_ptr - the report item representing a sensor/data type
  @return
    The effective sampling rate
 */
/*=========================================================================*/
SMGR_STATIC q16_t sns_rh_sol_compute_effective_rate(const sns_rh_rpt_item_s* item_ptr)
{
  const sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_ptr->ddf_sensor_ptr;
  q16_t effective_rate;
  /* ---------------------------------------------------------------------- */

  if ( item_ptr->cic_obj.factor > 1 )
  {
    effective_rate = item_ptr->cic_obj.input_frequency/item_ptr->cic_obj.factor;
  }
  else if ( SMGR_BIT_TEST(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B) &&
            item_ptr->rate_thresholds_met )
  {
    effective_rate = ddf_sensor_ptr->depot_data_rate/item_ptr->sampling_factor;
  }
  else
  {
    effective_rate = item_ptr->sampling_rate_hz;
  }
  return effective_rate;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_compute_report_interval

===========================================================================*/
/*!
  @brief Determines the report interval for the given report spec

  @details Called after ODR configuration is done

  @param[i] rpt_ptr - report spec representing a report request

  @return true of report interval is (re)computed
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_compute_report_interval(sns_rh_rpt_spec_s* rpt_ptr)
{
  bool recompute_required = false;
  uint8_t i;
  uint8_t ready_sensors = 0;
  /* ---------------------------------------------------------------------- */

  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    sns_smgr_ddf_sensor_s* ddf_sensor_ptr = rpt_ptr->item_list[i]->ddf_sensor_ptr;
    if ( ddf_sensor_ptr->sensor_ptr->sensor_state != SENSOR_STATE_READY ||
         rpt_ptr->item_list[i]->state < RH_RPT_ITEM_STATE_IDLE )
    {
      break;
    }
    ready_sensors++;
    if ( !recompute_required &&
         TICK1_GTR_TICK2(ddf_sensor_ptr->client_stat.client_modifier.last_updated, 
                         rpt_ptr->ts_last_updated) )
    {
      recompute_required = true;
    }
  }

  SNS_SMGR_PRINTF4(
    LOW, "compute_rpt_intvl - id=%u/0x%x #ready=%u recomp=%u",
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle,
    ready_sensors, recompute_required);

  if ( (ready_sensors == rpt_ptr->num_items) && recompute_required )
  {
    float req_rpt_intvl_ms, min_rpt_intvl_ms;

    req_rpt_intvl_ms = 1000.0f / FX_FIXTOFLT_Q16_SP(rpt_ptr->q16_rpt_rate);
    min_rpt_intvl_ms = FLT_MAX;
    rpt_ptr->min_sampling_interval = UINT32_MAX;

    RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_ptr->ddf_sensor_ptr;
      float depot_fill_ms, orig_depot_fill_ms, depot_data_intvl_ms;
      float rpt_intvl_ms = req_rpt_intvl_ms;
      uint32_t max_sample_count = sns_smgr_depot_get_depth(item_ptr->depot_ptr);
      uint16_t fifo_wm = MAX(1, ddf_sensor_ptr->sensor_ptr->fifo_cfg.current_watermark);

      if ( fifo_wm > 1 )
      {
        /* adjusts buffer depth for FIFO sensors */
        max_sample_count = (max_sample_count/fifo_wm)*fifo_wm;
      }
      else if ( item_ptr->quality != SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01 )
      {
        /* adjusts buffer depth for interpolated/filtered samples */
        max_sample_count--;
      }

      depot_data_intvl_ms = 1000.0f / FX_FIXTOFLT_Q16_SP(ddf_sensor_ptr->depot_data_rate);

      orig_depot_fill_ms = depot_fill_ms = 
        depot_data_intvl_ms * max_sample_count;
      if ( SMGR_SENSOR_IS_SELF_SCHED(ddf_sensor_ptr->sensor_ptr) &&
           !sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) )
      {
        /* self-scheduling sensors can sample up to 15% faster than expected */
        depot_fill_ms = depot_fill_ms * 85 /100;
      }
      SNS_SMGR_PRINTF4(
        LOW, "compute_rpt_intvl - sensor=%u #samples=%u depot_fill_ms/adjusted=%u/%u", 
        SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
        max_sample_count, orig_depot_fill_ms, depot_fill_ms);

      rpt_ptr->min_sampling_interval =
        MIN(rpt_ptr->min_sampling_interval, ddf_sensor_ptr->depot_data_interval);
      if ( fifo_wm > 1 )
      {
        /* report interval should be multiple of fifo interval */
        float fifo_intvl_ms = fifo_wm * depot_data_intvl_ms;
        rpt_intvl_ms = (uint32_t)(req_rpt_intvl_ms/fifo_intvl_ms)*fifo_intvl_ms;

        /* Makes report interval one sampling interval longer to prevent 
        report timer from expiring before FIFO interrupt.  This attempts to 
        save power by not bringing system out of sleep before there are samples
        to send */
        rpt_intvl_ms += depot_data_intvl_ms;
      }
      min_rpt_intvl_ms = MIN(min_rpt_intvl_ms, rpt_intvl_ms);
      min_rpt_intvl_ms = MIN(min_rpt_intvl_ms, depot_fill_ms);
    }
    rpt_ptr->rpt_interval = 
      sns_em_convert_usec_to_dspstick((uint32_t)(min_rpt_intvl_ms*1000));
    SNS_SMGR_PRINTF3(
      MED, "compute_rpt_intvl - min_samp_intvl=%u rpt_tick(last/next)=%u/%u",
      rpt_ptr->min_sampling_interval, rpt_ptr->ts_last_rpt_sent, rpt_ptr->rpt_tick);
    SNS_SMGR_PRINTF3(
      MED, "compute_rpt_intvl - req_intvl_ms=%u computed_intvl(ms/ticks)=%u/%u",
      req_rpt_intvl_ms, min_rpt_intvl_ms, rpt_ptr->rpt_interval);
    rpt_ptr->ts_last_updated = sns_em_get_timestamp();
  }
  return ((ready_sensors == rpt_ptr->num_items) && recompute_required);
}

/*===========================================================================

  FUNCTION:   sns_rh_update_bimg_depot_usage

===========================================================================*/
/*!
  @brief  Determines whether big-image depot will be in use
  @param [io] ddf_sensor_ptr - the sensor owner of the depot of interest
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_update_bimg_depot_usage(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  sns_rh_rpt_item_s* item_ptr = ddf_sensor_ptr->client_stat.rpt_item_ptr;
  bool bimg_depot_in_use = false;
  /* ---------------------------------------------------------------------- */

  while ( item_ptr != NULL && !bimg_depot_in_use )
  {
    if ( item_ptr->state != RH_RPT_ITEM_STATE_UNLINKING &&
         item_ptr->depot_ptr != NULL && 
         item_ptr->depot_ptr == ddf_sensor_ptr->bimg_depot_ptr )
    {
      bimg_depot_in_use = true;
    }
    item_ptr = item_ptr->next_item_ptr;
  }

  if ( ddf_sensor_ptr->bimg_depot_in_use != bimg_depot_in_use )
  {
    sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
    ddf_sensor_ptr->bimg_depot_in_use = bimg_depot_in_use;
    if ( bimg_depot_in_use && ddf_sensor_ptr->uimg_depot_ptr != NULL )
    {
      ddf_sensor_ptr->num_new_samples = 0;
    }

    SNS_SMGR_PRINTF2(
      LOW, "sensor=%u bimg_depot_in_use=%u", 
      SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
      bimg_depot_in_use);

    sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_find_same_report_rate

===========================================================================*/
/*!
  @brief  Searches the report queue for a report with the same report rate
          as that of the given report.

  @param [i] new_rpt_ptr - the new report
  @return the first report with same report rate is given report, or NULL
 */
/*=========================================================================*/
SMGR_STATIC sns_rh_rpt_spec_s* sns_rh_find_same_report_rate(
  const sns_rh_rpt_spec_s* new_rpt_ptr)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_rh_rpt_spec_s* found_rpt_ptr = NULL;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( rpt_queue_ptr, rpt_ptr, rpt_link )
  {
    if ( (rpt_ptr != new_rpt_ptr) && 
         (rpt_ptr->state == RH_RPT_STATE_ACTIVE) && (rpt_ptr->rpt_tick != 0) && 
         (rpt_ptr->rpt_interval == new_rpt_ptr->rpt_interval) )
    {
      found_rpt_ptr = rpt_ptr;
    }
  }
  return found_rpt_ptr;
}

/*===========================================================================

  FUNCTION:   sns_rh_add_reason_code

===========================================================================*/
/*!
  @brief  Add a pair (item # and reason code) to the list of reasons for failure or
    modification that will be sent in the response message.

  @detail

  @param[i]   item_idx      - 0 for report body, item 1...
  @param[i]   reason_code   - see enumeration
  @param[io]  num_pairs_ptr - number of existing items in reason pairs array
  @param[o]   reason_pairs  - array of reason pairs
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_add_reason_code(
  uint32_t                   item_idx,
  uint8_t                    reason_code,
  uint32_t*                  num_pairs_ptr,
  sns_smgr_reason_pair_s_v01 reason_pairs[])
{
  SNS_SMGR_PRINTF3(LOW, "add_reason_code - idx=%d reason=%d pairs=%d",
                   (int)item_idx, reason_code, (int)*num_pairs_ptr );
  if ( *num_pairs_ptr < SNS_SMGR_MAX_NUM_REASONS_V01 )
  {
    reason_pairs[*num_pairs_ptr].ItemNum = (uint8_t)item_idx;
    reason_pairs[*num_pairs_ptr].Reason  = reason_code;
    (*num_pairs_ptr)++;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_prepare_report_for_flushing

===========================================================================*/
/*!
  @brief Flushes accumulated samples

  @param[i] rpt_ptr - the report to flush

  @return   none
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_prepare_report_for_flushing(sns_rh_rpt_spec_s* rpt_ptr)
{
  if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) && (rpt_ptr->q16_rpt_rate != 0) &&
       (rpt_ptr->rpt_tick != 0) && !rpt_ptr->periodic_like )
  {
    uint8_t i;
    bool fifo_flush_pending = false;

    RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      if ( SMGR_SENSOR_FIFO_IS_ENABLE(item_ptr->ddf_sensor_ptr->sensor_ptr) &&
           item_ptr->ddf_sensor_ptr->sensor_ptr->sensor_state == SENSOR_STATE_READY )
      {
        SMGR_BIT_SET(item_ptr->ddf_sensor_ptr->flags, 
                     SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);
        SMGR_BIT_SET(item_ptr->ddf_sensor_ptr->sensor_ptr->flags, 
                     SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);
        fifo_flush_pending = true;
      }
    }
    if ( !fifo_flush_pending )
    {
      rpt_ptr->state = RH_RPT_STATE_FLUSHING;
      sns_rh_add_to_ready_list(rpt_ptr);
    }
    else
    {
      rpt_ptr->state = RH_RPT_STATE_FIFO_FLUSH_PENDING;
    }
    SNS_SMGR_PRINTF3(
      MED, "prepare_4_flushing - rpt_id=%u/0x%x state=%u", 
      rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, rpt_ptr->state);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_flush_report

===========================================================================*/
/*!
  @brief Called when a new report is added or an existing report is removed
         resulting in changes to ODRs of associated sensors.

  @param    none

  @return   number of reports generated
 */
/*=========================================================================*/
SMGR_STATIC bool sns_rh_flush_report(sns_rh_rpt_spec_s *rpt_ptr)
{
  bool sent = false;
  if ( rpt_ptr->state == RH_RPT_STATE_FLUSHING )
  {
    if ( sns_rh_ok_to_send_report(rpt_ptr) )
    {
      SNS_SMGR_PRINTF3(
        MED, "flush_reports - rpt_id=%u/0x%x ind_count=%u",
        rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, rpt_ptr->ind_count);
      if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) )
      {
        sent = sns_rh_rpt_gen_send_buffering_indications(rpt_ptr);
      }
      else
      {
        sent = sns_rh_rpt_gen_generate_periodic_report(rpt_ptr);
      }
      if ( sent )
      {
        SNS_SMGR_PRINTF4(
          MED, "flush_report - rpt_id=%u/0x%x intvl=%d next_tick=%u",
          rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
          rpt_ptr->rpt_interval, rpt_ptr->rpt_tick);
      }
      sns_rh_rpt_gen_remove_from_ready_list(rpt_ptr);
    }
    rpt_ptr->state = RH_RPT_STATE_ACTIVE;
  }
  return sent;
}

/*===========================================================================

  FUNCTION:   sns_rh_flush_reports

===========================================================================*/
/*!
  @brief Called when a new report is added or an existing report is removed
         resulting in changes to ODRs of associated sensors.

  @param    none

  @return   number of reports generated
 */
/*=========================================================================*/
uint32_t sns_rh_flush_reports(void)
{
  uint32_t           num_rpt_sent = 0;
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( rpt_queue_ptr, rpt_ptr, rpt_link )
  {
    if ( sns_rh_flush_report(rpt_ptr) )
    {
      num_rpt_sent++;
    }
  }
  return num_rpt_sent;
}

/*===========================================================================

  FUNCTION:  sns_rh_sol_get_ddf_sensor_list

===========================================================================*/
/*!
  @brief Returns the list of DDF sensors used by the given report

  @param[i] rpt_ptr   - the report of interest
  @param[o] ddf_sensor_ptrs - destination for the list

  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_get_ddf_sensor_list(
  const sns_rh_rpt_spec_s* rpt_ptr,
  sns_smgr_ddf_sensor_s*   ddf_sensor_ptrs[SNS_SMGR_MAX_ITEMS_PER_REPORT_V01])
{
  uint32_t i;

  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    ddf_sensor_ptrs[i] = rpt_ptr->item_list[i]->ddf_sensor_ptr;
  }
}

/*===========================================================================

  FUNCTION:  sns_rh_sol_update_sensor_events

===========================================================================*/
/*!
  @brief Affects possbible event for the DDF sensors in the given list
 
  @details After a report is deleted its associated sensors might be in
           the right condition to have their events (re)enabled.
           For example, Accel sensors that support Motion Dectect (MD) attribute
           can have MD event (re)enabled if MD is requested and Accel streaming
           is not.
 
  @param[io] ddf_sensor_ptrs - list of DDF sensors on which to operate

  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_update_sensor_events(
  sns_smgr_ddf_sensor_s*   ddf_sensor_ptrs[SNS_SMGR_MAX_ITEMS_PER_REPORT_V01])
{
  uint32_t i = 0;
  while ( ddf_sensor_ptrs[i] != NULL )
  {
    sns_rh_update_sensor_event(ddf_sensor_ptrs[i++]);
  }
}

/*===========================================================================

  FUNCTION:  sns_rh_sol_find_and_delete_report

===========================================================================*/
/*!
  @brief Searches report queue for the given report and deletes it.

  @param[i]  conn_handle - connection handle to match
  @param[i]  report_id - report ID to match
  @param[i]  flush     - true if samples should be flushed before report deleted

  @return SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 or SNS_SMGR_RESPONSE_NAK_REPORT_ID_V01
 */
/*=========================================================================*/
uint8_t sns_rh_sol_find_and_delete_report(
  const void* conn_handle,
  uint8_t     report_id,
  bool        flush)
{
  uint8_t            ack_nak = SNS_SMGR_RESPONSE_NAK_REPORT_ID_V01;
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( rpt_queue_ptr, rpt_ptr, rpt_link )
  {
    if ( (conn_handle == rpt_ptr->msg_header.connection_handle) &&
         (report_id == rpt_ptr->rpt_id) )
    {
      SNS_SMGR_PRINTF2(MED, "find_and_delete_rpt - state=%d items=%d",
                       rpt_ptr->state, rpt_ptr->num_items);

      if ( flush && (rpt_ptr->rpt_tick != 0) &&
           SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) && (rpt_ptr->q16_rpt_rate != 0) )
      {
        /* Buffering report may have accumulated samples waiting to be sent */
        rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        sns_rh_flush_report(rpt_ptr);
      }
      sns_rh_sol_delete_report(rpt_ptr);

      ack_nak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
      break;
    }
  }
  return ack_nak;
}

/*===========================================================================

  FUNCTION:  sns_rh_sol_find_report

===========================================================================*/
/*!
  @brief Searches active queue and suspended queue for the same report
         from the same client and deletes it.

  @param[i]  hdr_ptr   - message header of new request
  @param[i]  report_id - report ID to match

  @return pointer to the report if found, NULL otherwise
 */
/*=========================================================================*/
sns_rh_rpt_spec_s* sns_rh_sol_find_report(
  const sns_rh_mr_header_s*  hdr_ptr,
  uint8_t                    report_id)
{
  sns_rh_rpt_spec_s* found_rpt_ptr = NULL;
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();

  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM(rpt_queue_ptr, rpt_ptr, rpt_link)
  {
    if ( (hdr_ptr->connection_handle == rpt_ptr->msg_header.connection_handle) &&
         (report_id == rpt_ptr->rpt_id) )
    {
      SNS_SMGR_PRINTF2(LOW, "find_report - found rpt_id=%u/0x%x",
                       rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
      found_rpt_ptr = rpt_ptr;
      break;
    }
  }
  return found_rpt_ptr;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_find_query_item

===========================================================================*/
/*!
  @brief Searches for the report item in the Buffering request corresponding
  to the given Query request.

  @param[i] hdr_ptr  - message header
  @param[i] req_ptr  - incoming request message body
  @param[i] item_ptr_ptr - destination for address of the corresponding item, if found

  @return
   SNS_SMGR_RESPONSE_ACK_SUCCESS_V01   - found what we're looking for
   SNS_SMGR_RESPONSE_NAK_REPORT_ID_V01 - if no matching Buffering report found
   SNS_SMGR_RESPONSE_NAK_SENSOR_ID_V01 - if Buffering report does not include the
     requested sensor type
*/
/*=========================================================================*/
SMGR_STATIC uint8_t sns_rh_sol_find_query_item(
  const sns_rh_mr_header_s*                   hdr_ptr,
  const sns_smgr_buffering_query_req_msg_v01* req_ptr,
  sns_rh_rpt_item_s**                         item_ptr_ptr)
{
  uint8_t report_id = (uint8_t)req_ptr->QueryId;
  sns_rh_rpt_spec_s* report_ptr = sns_rh_sol_find_report(hdr_ptr, report_id);
  uint8_t ackNak = SNS_SMGR_RESPONSE_NAK_REPORT_ID_V01;

  /* ---------------------------------------------------------------------- */

  if ( report_ptr != NULL )
  {
    /* found the corresponding Buffering request */
    uint8_t i;
    RH_FOR_EACH_REPORT_ITEM( report_ptr, i )
    {
      if ( (SMGR_SENSOR_ID(report_ptr->item_list[i]->ddf_sensor_ptr->sensor_ptr) ==
            req_ptr->SensorId) &&
           (report_ptr->item_list[i]->ddf_sensor_ptr->data_type == req_ptr->DataType) )
      {
        *item_ptr_ptr = report_ptr->item_list[i];
        ackNak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
        break;
      }
    }
    if ( ackNak != SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 )
    {
      ackNak = SNS_SMGR_RESPONSE_NAK_SENSOR_ID_V01;
    }
  }
  return ackNak;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_override_response_ack

===========================================================================*/
/*!
  @brief

  @detail

  @param[io]  orig_ack_ptr - pointer to original ack code
  @param[i]   ack_code     -  ack code to be put in response

  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_override_response_ack(
  uint8_t* orig_ack_ptr, 
  uint8_t  ack_code)
{
  SNS_SMGR_PRINTF2(HIGH, "override_resp_ack - new=%d orig=%d", 
                   ack_code, *orig_ack_ptr );
  switch ( ack_code )
  {
    case SNS_SMGR_RESPONSE_ACK_SUCCESS_V01:
      break;
    case SNS_SMGR_RESPONSE_ACK_MODIFIED_V01:
      if ( SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 == *orig_ack_ptr )
      {
        *orig_ack_ptr = ack_code;
      }
      break;
    default:
      if ( (SNS_SMGR_RESPONSE_ACK_SUCCESS_V01  == *orig_ack_ptr) ||
           (SNS_SMGR_RESPONSE_ACK_MODIFIED_V01 == *orig_ack_ptr) )
      {
        *orig_ack_ptr = ack_code;
      }
      break;
  }
}

/*===========================================================================

  FUNCTION:  sns_rh_sol_update_max_frequencies

===========================================================================*/
/*!
  @brief Updates max requested HP and overall frequencies for the given DDF sensor

  @param[i] ddf_sensor_ptr - the DDF sensor

  @return  None
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_update_max_frequencies(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  sns_smgr_client_stat_s* client_stat_ptr = &ddf_sensor_ptr->client_stat;
  sns_rh_rpt_item_s* item_ptr = client_stat_ptr->rpt_item_ptr;
  q16_t max_freq    = 0;
  q16_t max_hp_freq = 0;
  uint8_t  flags    = 0;
  /* ---------------------------------------------------------------------- */

  while ( item_ptr != NULL )
  {
    if ( item_ptr->state != RH_RPT_ITEM_STATE_UNLINKING )
    {
      flags |= item_ptr->flags;
      if ( SMGR_BIT_TEST(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B) )
      {
        max_hp_freq = MAX(max_hp_freq, item_ptr->sampling_rate_hz);
      }
      max_freq = MAX(max_freq, item_ptr->sampling_rate_hz);
    }
    item_ptr = item_ptr->next_item_ptr;
  }
  client_stat_ptr->max_requested_freq_hz = max_freq;
  client_stat_ptr->max_high_perf_freq_hz = max_hp_freq;
  client_stat_ptr->flags                 = flags;

  SNS_SMGR_PRINTF4(
    MED, "update_max_freq = sensor=%d max=0x%X max_hp=0x%X flags=0x%X",
    SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
    client_stat_ptr->max_requested_freq_hz, client_stat_ptr->max_high_perf_freq_hz,
    client_stat_ptr->flags);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_mark_reports_for_flushing

===========================================================================*/
/*!
  @brief Changes state of affected reports to FLUSHING if ODR for their sensors
         would change.

  @param[i] ddf_sensor_ptr

  @return None
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_mark_reports_for_flushing(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  uint32_t new_odr = sns_smgr_choose_odr(ddf_sensor_ptr->sensor_ptr);
  /* ---------------------------------------------------------------------- */

  if ( ((new_odr > 0) && (new_odr != ddf_sensor_ptr->current_odr)) ||
       (sns_smgr_compute_depot_data_rate(ddf_sensor_ptr) !=
        ddf_sensor_ptr->depot_data_rate) )
  {
    sns_rh_rpt_item_s* item_ptr = ddf_sensor_ptr->client_stat.rpt_item_ptr;

    SMGR_BIT_CLEAR(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);
    SMGR_BIT_CLEAR(ddf_sensor_ptr->sensor_ptr->flags, SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);

    while ( item_ptr != NULL )
    {
      sns_rh_rpt_spec_s* rpt_ptr = item_ptr->parent_report_ptr;
      if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) &&
           (item_ptr->state != RH_RPT_ITEM_STATE_LINKING) )
      {
        SNS_SMGR_PRINTF3(
          LOW, "mark_4_flushing - sensor=%u rpt_id=%u/0x%x", 
          SMGR_SENSOR_ID(ddf_sensor_ptr->sensor_ptr), 
          rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
        sns_rh_sol_prepare_report_for_flushing(rpt_ptr);
      }
      item_ptr = item_ptr->next_item_ptr;
    }
  }
}

/*===========================================================================

  FUNCTION:   smgr_update_sensor_when_item_changed

===========================================================================*/
/*!
  @brief Updates bookeeping info when an item is linked to or unlinked from
         the given DDF sensor.

  @param[i] ddf_sensor_ptr
  @param[i] in_item_spec_ptr the item spec in the new report or to bedeleted
  @return None
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_update_sensor_when_item_changed (
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr,
  sns_rh_rpt_item_s*     in_item_spec_ptr)
{
  sns_smgr_sensor_s* sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  sns_smgr_client_stat_s* cs_ptr = &ddf_sensor_ptr->client_stat;
  int8_t change;
  uint8_t sensor_flags_bit;
  /* ---------------------------------------------------------------------- */

  if ( in_item_spec_ptr->state == RH_RPT_ITEM_STATE_LINKING )
  {
    change           = 1;
    sensor_flags_bit = SMGR_SENSOR_FLAGS_ITEM_ADD_B;
  }
  else
  {
    change           = -1;
    sensor_flags_bit = SMGR_SENSOR_FLAGS_ITEM_DEL_B;
  }

  if ( SNS_RH_REPORT_IS_PERIODIC(in_item_spec_ptr->parent_report_ptr) ||
       in_item_spec_ptr->parent_report_ptr->periodic_like )
  {
    cs_ptr->num_periodic_reports += change;
  }

  cs_ptr->num_rpt_items += change;
  cs_ptr->sensor_status.last_status_ts = sns_em_get_timestamp();

  sns_rh_sol_update_max_frequencies(ddf_sensor_ptr);

  SMGR_BIT_SET(sensor_ptr->flags, sensor_flags_bit);

  sns_rh_sol_update_sensor_status(ddf_sensor_ptr);

  sns_profiling_log_qdss(SNS_RH_LINK_SENSOR, 3, 
                         SMGR_SENSOR_ID(ddf_sensor_ptr->sensor_ptr), 
                         change, cs_ptr->num_rpt_items);

  SNS_SMGR_PRINTF4(
    HIGH, "item_changed - sensor=%d flags=0x%x #items=%d item_state=%d",
    SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type), sensor_ptr->flags,
    cs_ptr->num_rpt_items, in_item_spec_ptr->state);

  sns_rh_sol_mark_reports_for_flushing(ddf_sensor_ptr);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_link_item_to_sensor

===========================================================================*/
/*!
  @brief associate a item spec from the sensor that the item have associated with

  @Detail if this is the first for the data type, invalidate the latest issued tick

  @param[i] in_item_spec_ptr - Point to the report specification structure

  @return
   TRUE the item spec associated successfully to the sensor
   FALSE  the item spec could not associate to the sensor because of some reasons
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_link_item_to_sensor(
  sns_rh_rpt_item_s* in_item_spec_ptr)
{
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr;
  sns_rh_rpt_item_s**     item_ptr_ptr;
  uint8_t never_err;
  /* ---------------------------------------------------------------------- */

  ddf_sensor_ptr = in_item_spec_ptr->ddf_sensor_ptr;
  sns_os_mutex_pend(ddf_sensor_ptr->sensor_ptr->mutex_ptr, 0, &never_err);

  item_ptr_ptr = &ddf_sensor_ptr->client_stat.rpt_item_ptr;

  while ( *item_ptr_ptr != NULL )
  {
    item_ptr_ptr = &(*item_ptr_ptr)->next_item_ptr;
  }
  *item_ptr_ptr = in_item_spec_ptr;
  in_item_spec_ptr->state = RH_RPT_ITEM_STATE_LINKING;
  sns_rh_sol_update_sensor_when_item_changed(ddf_sensor_ptr, in_item_spec_ptr);
  if ( in_item_spec_ptr->parent_report_ptr->proc_type != SNS_PROC_SSC_V01 )
  {
    sns_smgr_update_bw_reqd(
      (uint16_t)DDF_FIXTOODR_CEIL_Q16(in_item_spec_ptr->sampling_rate_hz), 0);
  }
  sns_rh_select_item_depot(in_item_spec_ptr);
  if ( in_item_spec_ptr->parent_report_ptr->msg_header.svc_num == SNS_SMGR_SVC_ID_V01 )
  {
    sns_rh_update_sensor_event(ddf_sensor_ptr);
  }

  sns_os_mutex_post(ddf_sensor_ptr->sensor_ptr->mutex_ptr);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_unlink_item_to_sensor

===========================================================================*/
/*!
  @brief de-associate a item spec from the sensor that the item have associated with

  @Detail

  @param[i] ItemSpec_p - Point to the report specification structure

  @return
   TRUE the item spec de-associated successfully
   FAIL could not de-associate because the item spec was not associated with the sensor
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_unlink_item_to_sensor(
  sns_rh_rpt_item_s* in_item_spec_ptr)
{
  bool found = false;
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr;
  sns_rh_rpt_item_s** item_ptr_ptr;
  uint8_t never_err;
  /* ---------------------------------------------------------------------- */

  ddf_sensor_ptr = in_item_spec_ptr->ddf_sensor_ptr;
  sns_os_mutex_pend(ddf_sensor_ptr->sensor_ptr->mutex_ptr, 0, &never_err);

  item_ptr_ptr = &ddf_sensor_ptr->client_stat.rpt_item_ptr;
  while ( (*item_ptr_ptr != in_item_spec_ptr) && (*item_ptr_ptr != NULL) )
  {
    item_ptr_ptr = &(*item_ptr_ptr)->next_item_ptr;
  }
  if ( *item_ptr_ptr == in_item_spec_ptr )     /* found the element */
  {
    *item_ptr_ptr  = in_item_spec_ptr->next_item_ptr;
    in_item_spec_ptr->next_item_ptr = NULL;
    in_item_spec_ptr->state = RH_RPT_ITEM_STATE_UNLINKING;

    sns_rh_sol_update_sensor_when_item_changed(ddf_sensor_ptr, in_item_spec_ptr);
    if ( in_item_spec_ptr->parent_report_ptr->proc_type != SNS_PROC_SSC_V01 )
    {
      sns_smgr_update_bw_reqd(
        0, (uint16_t)DDF_FIXTOODR_CEIL_Q16(in_item_spec_ptr->sampling_rate_hz));
    }

    found = true;
  }
  sns_os_mutex_post(ddf_sensor_ptr->sensor_ptr->mutex_ptr);
  return found;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_parse_item_decimation

===========================================================================*/
/*!
  @brief Parses Decimation field of report request.

  @Detail

  @param[i] decimation - the Decimation from report request
  @param[i] item_ptr   - the report item to be updated based on decimation value

  @return
   SNS_SMGR_REASON_NULL_V01 - everything's fine
   SNS_SMGR_REASON_DEFAULT_DECIM_V01 - Decimation value requested can not be honored
*/
/*=========================================================================*/
uint8_t sns_rh_sol_parse_item_decimation(
  uint8_t             decimation,
  sns_rh_rpt_item_s*  item_ptr)
{
  uint8_t reason_code  = SNS_SMGR_REASON_NULL_V01;
  sns_ddf_sensor_e ddf_sensor_type;

  /* ---------------------------------------------------------------------- */

  ddf_sensor_type = SMGR_SENSOR_TYPE(item_ptr->ddf_sensor_ptr->sensor_ptr,
                                     item_ptr->ddf_sensor_ptr->data_type);

  if ( (SNS_SMGR_DECIMATION_FILTER_V01  == decimation) ||
       (SNS_SMGR_DECIMATION_AVERAGE_V01 == decimation) )
  {
    if ( !sns_smgr_is_on_change_sensor(ddf_sensor_type) )
    {
      SMGR_BIT_SET(item_ptr->flags, RH_RPT_ITEM_FLAGS_DECIM_FILTER_B);
    }
    else
    {
      SNS_SMGR_PRINTF2(ERROR, "parse_item_decim - ddf_sensor=%d decim=%d",
                       ddf_sensor_type, decimation);
      reason_code = SNS_SMGR_REASON_DEFAULT_DECIM_V01;
    }
  }
  else if ( SNS_SMGR_DECIMATION_RECENT_SAMPLE_V01 != decimation )
  {
    reason_code = SNS_SMGR_REASON_DEFAULT_DECIM_V01;
  }
  return reason_code;
}

/*===========================================================================

  FUNCTION:   smgr_rate_hz_to_q16

===========================================================================*/
/*!
  @brief Interprets the sampling or report rate as a rate value in Hz, when it
         is below the pre-defined threshold. Or it interprets the sampling or
         report rate as a period value in ms. Then it converts it into a
         corresponding rate value in Hz, Q16-format.

  @note Q16 fixed point format is used, instead of floating point, because
        the Q6 does not have hardware-support for floating point division.
        Thus, the code will run faster if fixed point is used instead.

  @param[i]  rate - integer value passed in with the message. This ONLY applies
                    to the following message:field(:field) items!!!!!
                    - sns_smgr_periodic_report_req_msg_v01:ReportRate
                    - sns_smgr_buffering_req_msg_v01:Item:SamplingRate

  @return
   The rate in Hz (Q16 format)
*/
/*=========================================================================*/
q16_t smgr_rate_hz_to_q16(uint16_t rate)
{
  if (rate > SNS_SMGR_SAMPLING_RATE_INVERSION_POINT_V01)
  {
    return FX_FLTTOFIX_Q16(1000)/rate;
  }
  else
  {
    return FX_FLTTOFIX_Q16(rate);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_update_event_sensor_only_flag

===========================================================================*/
/*!
  @brief Sets the report's event_sensor_only flag.

  @param [io] rpt_ptr - the report of interest

  @return none
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_update_event_sensor_only_flag(sns_rh_rpt_spec_s* rpt_ptr)
{
  uint8_t i;
  rpt_ptr->event_sensors_only = true;
  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    if ( !sns_smgr_ddf_sensor_is_event_sensor(rpt_ptr->item_list[i]->ddf_sensor_ptr) )
    {
      rpt_ptr->event_sensors_only = false;
      break;
    }
  }
  SNS_SMGR_PRINTF3(
    LOW, "event_sensor_only - rpt_id=%u/0x%x only=%u",
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, rpt_ptr->event_sensors_only);
}

/*===========================================================================

  FUNCTION:   sns_rh_parse_periodic_report_item

===========================================================================*/
/*!
  @brief Fill the item spec structure with the input parameter

  @Detail: SNS_SMGR_RESPONSE_ACK_MODIFIED_V01 could override SNS_SMGR_RESPONSE_ACK_SUCCESS_V01
    NAK could overide any ACKs.

  @param ItemDef_p[i] points to the structure of incoming request message
  @param[i] ItemSpec_p - Point to the report specification structure
  @param[i] ItemSpec_p - Point to the report specification structure
  @param[i] cal_sel - calibraion selection
  @resp_ptr[i] Point to instance of response message structure

  @return
   TRUE Successfully filled the item spec
   FALSE Failed to fill the itemp spec because:
   - the sensor state is SENSOR_STATE_FAILED or otherwise not ready
   - Linking the item to the sensor had failed
   - etc
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_parse_periodic_report_item(
  uint8_t                                     item_idx,
  const sns_smgr_periodic_report_req_msg_v01* req_ptr,
  sns_rh_rpt_item_s*                          item_ptr,
  uint32_t*                                   num_pairs_ptr,
  sns_smgr_reason_pair_s_v01*                 reason_pairs)
{
  bool success = false;
  const sns_smgr_periodic_report_item_s_v01* in_item_ptr = &req_ptr->Item[item_idx];
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
    sns_smgr_find_ddf_sensor(in_item_ptr->SensorId, in_item_ptr->DataType);
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF2(LOW, "parse_periodic_item - sensor=%d dtype=%d",
                   in_item_ptr->SensorId, in_item_ptr->DataType);

  if ( ddf_sensor_ptr == NULL )
  {
    /* Unknown sensor ID, delete incoming item */
    sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_UNKNOWN_SENSOR_V01,
                               num_pairs_ptr, reason_pairs);
  }
  else if ( (SENSOR_STATE_FAILED   == ddf_sensor_ptr->sensor_ptr->sensor_state) ||
            (SENSOR_STATE_PRE_INIT == ddf_sensor_ptr->sensor_ptr->sensor_state) ||
            (SENSOR_STATE_TESTING  == ddf_sensor_ptr->sensor_ptr->sensor_state) )
  {
    /* Device not ready, delete incoming item */
    sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_FAILED_SENSOR_V01,
                               num_pairs_ptr, reason_pairs);
  }
  else if ( (FX_FLTTOFIX_Q16(req_ptr->ReportRate) >
             ddf_sensor_ptr->max_supported_freq_hz) &&
            (req_ptr->ReportRate <= SNS_SMGR_SAMPLING_RATE_INVERSION_POINT_V01) &&
            !sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) )
  {
    sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_SAMPLING_RATE_V01,
                               num_pairs_ptr, reason_pairs);
    SNS_SMGR_PRINTF2(ERROR, "parse_periodic_item - req_rate=%d max_freq=0x%X",
                     req_ptr->ReportRate, ddf_sensor_ptr->max_supported_freq_hz);
  }
  else if ( (req_ptr->ReportRate == 0) && (req_ptr->Item_len > 1) &&
            ( FX_FLTTOFIX_Q16(SNS_SMGR_REPORT_RATE_DEFAULT_V01) >
              ddf_sensor_ptr->max_supported_freq_hz ) )
  {
    sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_SAMPLING_RATE_V01,
                               num_pairs_ptr, reason_pairs);
  }
  else
  {
    SNS_OS_MEMZERO(item_ptr, sizeof(sns_rh_rpt_item_s));
    item_ptr->ddf_sensor_ptr          = ddf_sensor_ptr;
    item_ptr->resulting_sample.status = SNS_DDF_PENDING;
    item_ptr->sampling_rate_hz        = smgr_rate_hz_to_q16(req_ptr->ReportRate);
    if ( item_ptr->sampling_rate_hz > item_ptr->ddf_sensor_ptr->max_supported_freq_hz )
    {
      item_ptr->sampling_rate_hz  = ddf_sensor_ptr->max_supported_freq_hz;
      sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_DEFAULT_RATE_V01,
                                 num_pairs_ptr, reason_pairs);
      SNS_SMGR_PRINTF2(
        ERROR, "parse_periodic_item - req_rate=%d max_freq=0x%X",
        req_ptr->ReportRate, ddf_sensor_ptr->max_supported_freq_hz);
    }
    if ( item_ptr->sampling_rate_hz == 0 )
    {
      item_ptr->sampling_rate_hz = smgr_rate_hz_to_q16(SNS_SMGR_REPORT_RATE_DEFAULT_V01);
      if ( item_ptr->sampling_rate_hz > ddf_sensor_ptr->max_supported_freq_hz )
      {
        item_ptr->sampling_rate_hz = ddf_sensor_ptr->max_supported_freq_hz;
      }
    }
    item_ptr->sampling_interval = sns_smgr_get_sched_intval(item_ptr->sampling_rate_hz);
    item_ptr->sampling_factor   = 1;

    item_ptr->sensitivity = in_item_ptr->Sensitivity;
    if ( sns_rh_sol_parse_item_decimation(in_item_ptr->Decimation, item_ptr) != 0 )
    {
      sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_DEFAULT_DECIM_V01,
                                 num_pairs_ptr, reason_pairs);
    }

    /* when cal_sel_valid is FALSE, cal_sel[i] shall be 0 */
    item_ptr->cal_sel = req_ptr->cal_sel[item_idx];
    if ( !req_ptr->cal_sel_valid || (item_idx >= req_ptr->cal_sel_len ) )
    {
      item_ptr->cal_sel = SNS_SMGR_CAL_SEL_FULL_CAL_V01;
    }

    if ( req_ptr->SampleQuality_valid &&
         (item_idx < req_ptr->SampleQuality_len) &&
         (req_ptr->SampleQuality[item_idx] &
          SNS_SMGR_SAMPLE_QUALITY_ACCURATE_TIMESTAMP_V01) )
    {
      if ( SMGR_SENSOR_IS_SELF_SCHED(ddf_sensor_ptr->sensor_ptr) )
      {
        SMGR_BIT_SET(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B);
      }
      else
      {
        sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_SAMPLE_QUALITY_NORMAL_V01,
                                   num_pairs_ptr, reason_pairs);
      }
    }
    SNS_SMGR_PRINTF1(LOW, "parse_periodic_item - flags=0x%x", item_ptr->flags);
    success = true;
  }
  return success;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_parse_buffering_item

===========================================================================*/
/*!
  @brief Fill the item spec with the input

  @Detail: SNS_SMGR_RESPONSE_ACK_MODIFIED_V01 could override SNS_SMGR_RESPONSE_ACK_SUCCESS_V01
    NAK could overide any ACKs.

  @param ItemDef_p[i] points to the structure of incoming request message
  @param[i] ItemSpec_p - Point to the report specification structure
  @param[i] ItemSpec_p - Point to the report specification structure
  @param[i] cal_sel - calibraion selection
  @resp_ptr[i] Point to instance of response message structure

  @return
   TRUE Successfully filled the item spec
   FALSE Failed to fill the itemp spec becasue of:
   - the sensor state is SENSOR_STATE_FAILED
   - Linking the item to the sensor was fail
   - etc
*/
/*=========================================================================*/
bool sns_rh_sol_parse_buffering_item(
  uint8_t                                  item_idx,
  const sns_smgr_buffering_req_item_s_v01* in_item_ptr,
  sns_rh_rpt_item_s*                       item_ptr,
  uint32_t*                                num_pairs_ptr,
  sns_smgr_reason_pair_s_v01*              reason_pairs)
{
  bool success = false;
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = 
    sns_smgr_find_ddf_sensor(in_item_ptr->SensorId, in_item_ptr->DataType);
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF3(LOW, "parse_buffering_item - sensor=%d dtype=%d rate=%d",
                   in_item_ptr->SensorId, in_item_ptr->DataType,
                   in_item_ptr->SamplingRate);

  if ( ddf_sensor_ptr == NULL )
  {
    sns_rh_sol_add_reason_code(
      item_idx+1, SNS_SMGR_REASON_UNKNOWN_SENSOR_V01,
      num_pairs_ptr, reason_pairs);
  }
  else if ( (SENSOR_STATE_FAILED   == ddf_sensor_ptr->sensor_ptr->sensor_state) ||
            (SENSOR_STATE_PRE_INIT == ddf_sensor_ptr->sensor_ptr->sensor_state) ||
            (SENSOR_STATE_TESTING  == ddf_sensor_ptr->sensor_ptr->sensor_state) )
  {
    /* Unknown sensor ID, delete incoming item */
    sns_rh_sol_add_reason_code(
      item_idx+1, SNS_SMGR_REASON_FAILED_SENSOR_V01,
      num_pairs_ptr, reason_pairs);
    SNS_SMGR_PRINTF2(
      ERROR, "parse_buffering_item - sensor=%d state=%d",
      in_item_ptr->SensorId, ddf_sensor_ptr->sensor_ptr->sensor_state);
  }
  else if ( (in_item_ptr->SamplingRate < 1) ||
            ((FX_FLTTOFIX_Q16(in_item_ptr->SamplingRate) > 
              ddf_sensor_ptr->max_supported_freq_hz) &&
             (in_item_ptr->SamplingRate <= SNS_SMGR_SAMPLING_RATE_INVERSION_POINT_V01)) )
  {
    sns_rh_sol_add_reason_code(
      item_idx+1, SNS_SMGR_REASON_SAMPLING_RATE_V01,
      num_pairs_ptr, reason_pairs);
    SNS_SMGR_PRINTF2(
      ERROR, "parse_buffering_item - req_rate=%d max=0x%X",
      in_item_ptr->SamplingRate, ddf_sensor_ptr->max_supported_freq_hz);
  }
  else
  {
    SNS_OS_MEMZERO(item_ptr, sizeof(sns_rh_rpt_item_s));
    item_ptr->ddf_sensor_ptr    = ddf_sensor_ptr;
    item_ptr->sampling_rate_hz  = smgr_rate_hz_to_q16(in_item_ptr->SamplingRate);
    /* Cannot directly convert DSPS_SLEEP_CLK to Q16 due to overflow.
       Just going to manually apply the left-shifts instead. */
    item_ptr->sampling_interval = (DSPS_SLEEP_CLK << FX_QFACTOR) /
                                    ((uint32_t) item_ptr->sampling_rate_hz);
    item_ptr->sampling_factor   = 1;

    if ( sns_rh_sol_parse_item_decimation(in_item_ptr->Decimation, item_ptr) != 0 )
    {
      sns_rh_sol_add_reason_code(item_idx+1, SNS_SMGR_REASON_DEFAULT_DECIM_V01,
                                 num_pairs_ptr, reason_pairs);
    }

    /* when cal_sel_valid is FALSE, cal_sel[i] shall be 0 */
    item_ptr->cal_sel = in_item_ptr->Calibration;

    if ( in_item_ptr->SampleQuality & SNS_SMGR_SAMPLE_QUALITY_ACCURATE_TIMESTAMP_V01 )
    {
      if ( SMGR_SENSOR_IS_SELF_SCHED(ddf_sensor_ptr->sensor_ptr) )
      {
        SMGR_BIT_SET(item_ptr->flags, RH_RPT_ITEM_FLAGS_ACCURATE_TS_B);
      }
      else
      {
        sns_rh_sol_add_reason_code(
          item_idx+1, SNS_SMGR_REASON_SAMPLE_QUALITY_NORMAL_V01,
          num_pairs_ptr, reason_pairs);
      }
    }
    SNS_SMGR_PRINTF1(LOW, "parse_buffering_item - flags=0x%x", item_ptr->flags);
    success = true;
  }
  return success;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_parse_notify_suspend

===========================================================================*/
SMGR_STATIC void sns_rh_sol_parse_notify_suspend(
  uint8_t                               src_module,
  bool                                  suspend_notif_valid,
  const sns_suspend_notification_s_v01* suspend_notif_ptr,
  sns_rh_rpt_spec_s*                    rpt_ptr)
{
  if ( suspend_notif_valid )
  {
    rpt_ptr->proc_type = suspend_notif_ptr->proc_type;
    rpt_ptr->send_ind_during_suspend = 
      suspend_notif_ptr->send_indications_during_suspend;
  }
  else
  {
    if ( src_module < SNS_MODULE_DSPS )
    {
      rpt_ptr->proc_type = SNS_PROC_APPS_V01;
    }
    else if ( src_module < SNS_MODULE_MDM )
    {
      rpt_ptr->proc_type = SNS_PROC_SSC_V01;
    }
    else
    {
      rpt_ptr->proc_type = SNS_PROC_MODEM_V01;
    }
    rpt_ptr->send_ind_during_suspend = false;
  }
  SNS_SMGR_PRINTF2(
    HIGH, "parse_notify_suspend - proc=%u send=%u",
    rpt_ptr->proc_type, rpt_ptr->send_ind_during_suspend);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_parse_periodic_report_request

===========================================================================*/
/*!
  @brief Parses the incoming periodic report request

  @param[i]  hdr_ptr  - message header
  @param[i]  req_ptr  - the incoming report request
  @param[io] resp_ptr - response to the request
  @param[io] rpt_ptr  - report specification

  @return
    SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 - if all goes well
    SNS_SMGR_RESPONSE_NAK_RESOURCES_V01 - out of mem
    SNS_SMGR_RESPONSE_NAK_NO_ITEMS_V01 - no item saved
*/
/*=========================================================================*/
SMGR_STATIC uint8_t sns_rh_sol_parse_periodic_report_request(
  const sns_rh_mr_header_s*              hdr_ptr,
  sns_smgr_periodic_report_req_msg_v01*  req_ptr,
  sns_smgr_periodic_report_resp_msg_v01* resp_ptr,
  sns_rh_rpt_spec_s*                     rpt_ptr)
{
  uint8_t i, ackNak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF1(HIGH, "parse_periodic_report - rate=%u",  req_ptr->ReportRate);

  sns_rh_sol_parse_notify_suspend(
    hdr_ptr->src_module, req_ptr->notify_suspend_valid, 
    &req_ptr->notify_suspend, rpt_ptr);

  rpt_ptr->q16_rpt_rate = 
    smgr_rate_hz_to_q16(req_ptr->ReportRate ? 
                        req_ptr->ReportRate : SNS_SMGR_REPORT_RATE_DEFAULT_V01);

  for (i=0; i<req_ptr->Item_len && ackNak==SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 &&
            rpt_ptr->num_items < ARR_SIZE(rpt_ptr->item_list); i++)
  {
    sns_rh_rpt_item_s* item_ptr = SMGR_ANY_ALLOC_STRUCT(sns_rh_rpt_item_s);
    if ( NULL != item_ptr )
    {
      bool success = sns_rh_parse_periodic_report_item(
        i, req_ptr, item_ptr, &resp_ptr->ReasonPair_len, resp_ptr->ReasonPair);
      if ( !success )
      {
        SNS_SMGR_PRINTF1(ERROR, "parse_periodic_report - deleting item %u", i);
        SNS_OS_ANY_FREE(item_ptr);
      }
      else
      {
        item_ptr->parent_report_ptr = rpt_ptr;
        rpt_ptr->item_list[rpt_ptr->num_items++] = item_ptr;
      }
    }
    else
    {
      ackNak = SNS_SMGR_RESPONSE_NAK_RESOURCES_V01;
      SNS_SMGR_PRINTF1(ERROR, "parse_periodic_report - no resource for rpt_id=%d",
                       rpt_ptr->rpt_id);
    }
  }

  if ( resp_ptr->ReasonPair_len > 0 )
  {
    sns_rh_sol_override_response_ack(
      &resp_ptr->AckNak, SNS_SMGR_RESPONSE_ACK_MODIFIED_V01);
  }

  if ( (ackNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) || 
       (ackNak == SNS_SMGR_RESPONSE_ACK_MODIFIED_V01) )
  {
    if ( rpt_ptr->num_items > 0 )
    {
      sns_q_link(rpt_ptr, &rpt_ptr->rpt_link);
      rpt_ptr->msg_header = *hdr_ptr;
      rpt_ptr->rpt_id = req_ptr->ReportId;

      if ( req_ptr->ReportRate == 0 )
      {
        req_ptr->ReportRate = SNS_SMGR_REPORT_RATE_DEFAULT_V01;
        sns_rh_sol_add_reason_code(0, SNS_SMGR_REASON_DEFAULT_RATE_V01,
                                   &resp_ptr->ReasonPair_len, resp_ptr->ReasonPair);
        sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                         SNS_SMGR_RESPONSE_ACK_MODIFIED_V01);
      }
      rpt_ptr->q16_rpt_rate = smgr_rate_hz_to_q16(req_ptr->ReportRate);
      sns_rh_update_event_sensor_only_flag(rpt_ptr);
    }
    else
    {
      ackNak = SNS_SMGR_RESPONSE_NAK_NO_ITEMS_V01;
    }
  }

  SNS_SMGR_PRINTF3(LOW, "parse_periodic_report - rpt_id=%d #items=%d ackNak=%u",
                   rpt_ptr->rpt_id, rpt_ptr->num_items, ackNak);
  return ackNak;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_parse_buffering_report_request

===========================================================================*/
/*!
  @brief Parses the incoming periodic or buffering report request

  @param[i]  req_ptr  - the incoming report request
  @param[io] resp_ptr - response to the request
  @param[io] rpt_ptr  - report specification

  @return
    SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 - if all goes well
    SNS_SMGR_RESPONSE_NAK_RESOURCES_V01 - out of mem
    SNS_SMGR_RESPONSE_NAK_NO_ITEMS_V01 - no item saved
*/
/*=========================================================================*/
SMGR_STATIC uint8_t sns_rh_sol_parse_buffering_report_request(
  const sns_rh_mr_header_s*        hdr_ptr,
  sns_smgr_buffering_req_msg_v01*  req_ptr,
  sns_smgr_buffering_resp_msg_v01* resp_ptr,
  sns_rh_rpt_spec_s*               rpt_ptr)
{
  uint8_t i, ackNak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF1(HIGH, "parse_buffering_report - rate=0x%x",  req_ptr->ReportRate);
  
  sns_rh_sol_parse_notify_suspend(
    hdr_ptr->src_module, req_ptr->notify_suspend_valid, 
    &req_ptr->notify_suspend, rpt_ptr);
  rpt_ptr->q16_rpt_rate = req_ptr->ReportRate;

  for (i=0; i<req_ptr->Item_len && ackNak==SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 &&
            rpt_ptr->num_items < ARR_SIZE(rpt_ptr->item_list); i++)
  {
    sns_rh_rpt_item_s* item_ptr = SMGR_ANY_ALLOC_STRUCT(sns_rh_rpt_item_s);
    if ( NULL != item_ptr )
    {
      bool success = sns_rh_sol_parse_buffering_item(
        i, &req_ptr->Item[i], item_ptr, 
        &resp_ptr->ReasonPair_len, resp_ptr->ReasonPair);
      if ( !success )
      {
        SNS_SMGR_PRINTF1(ERROR, "parse_buffering_report - deleting item %u", i);
        SNS_OS_ANY_FREE(item_ptr);
      }
      else
      {
        item_ptr->parent_report_ptr = rpt_ptr;
        rpt_ptr->item_list[rpt_ptr->num_items++] = item_ptr;
      }
    }
    else
    {
      ackNak = SNS_SMGR_RESPONSE_NAK_RESOURCES_V01;
      SNS_SMGR_PRINTF1(ERROR, "parse_buffering_report - no resource for rpt_id=%d",
                       rpt_ptr->rpt_id);
    }
  }

  if ( resp_ptr->ReasonPair_len > 0 )
  {
    sns_rh_sol_override_response_ack(
      &resp_ptr->AckNak, SNS_SMGR_RESPONSE_ACK_MODIFIED_V01);
  }
  if ( (ackNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) || 
       (ackNak == SNS_SMGR_RESPONSE_ACK_MODIFIED_V01) )
  {
    if ( rpt_ptr->num_items > 0 )
    {
      sns_q_link(rpt_ptr, &rpt_ptr->rpt_link);
      rpt_ptr->msg_header = *hdr_ptr;
      rpt_ptr->rpt_id = req_ptr->ReportId;
      sns_rh_update_event_sensor_only_flag(rpt_ptr);
      sns_rh_update_periodic_like_flag(rpt_ptr);
      SNS_SMGR_PRINTF2(LOW, "schedule_buffering_rpt - rpt_rate=0x%X per_like=%u",
                       rpt_ptr->q16_rpt_rate, rpt_ptr->periodic_like);
    }
    else
    {
      ackNak = SNS_SMGR_RESPONSE_NAK_NO_ITEMS_V01;
    }
  }
  SNS_SMGR_PRINTF3(LOW, "parse_buffering_report - rpt_id=%d #items=%d ackNak=%u",
                   rpt_ptr->rpt_id, rpt_ptr->num_items, ackNak);
  return ackNak;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_validate_buffering_rate

===========================================================================*/
/*!
  @brief Validates report rate and sampling rates.

  @param[i] req_ptr - points to the structure of incoming request message

  @return
   SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 - rates in proper ranges
   SNS_SMGR_RESPONSE_NAK_REPORT_RATE_V01 - see the code
*/
/*=========================================================================*/
SMGR_STATIC uint8_t sns_rh_sol_validate_buffering_rate(
  const sns_smgr_buffering_req_msg_v01*  req_ptr)
{
  uint8_t ackNak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
  q16_t min_sampling_rate = FX_MAX_Q16;
  q16_t max_sampling_rate = 1; //~0.0000153 Hz
  q16_t item_sampling_rate;
  uint8_t i;

  /* ---------------------------------------------------------------------- */

  for ( i=0; i<req_ptr->Item_len && i<ARR_SIZE(req_ptr->Item); i++ )
  {
    item_sampling_rate = smgr_rate_hz_to_q16(req_ptr->Item[i].SamplingRate);
    min_sampling_rate = MIN(min_sampling_rate, item_sampling_rate);
    max_sampling_rate = MAX(max_sampling_rate, item_sampling_rate);
  }

  if ( (req_ptr->ReportRate > max_sampling_rate) ||
       ((req_ptr->ReportRate == 0) &&
        (min_sampling_rate < SMGR_MIN_EIS_SAMPLING_RATE)) )
  {
    ackNak = SNS_SMGR_RESPONSE_NAK_REPORT_RATE_V01;
    SNS_SMGR_PRINTF3(
      ERROR, "validate_buffering_rate - rpt_rate=0x%x sampling(min/max)=0x%x/0x%x",
      req_ptr->ReportRate, min_sampling_rate, max_sampling_rate);
  }
  return ackNak;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_compare_reports

===========================================================================*/
/*!
  @brief Checks if the given reports are identical.

  @param[i] existing_rpt_ptr
  @param[i] new_rpt_ptr

  @return   true if the reports are identical
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_compare_reports(
  const sns_rh_rpt_spec_s*  existing_rpt_ptr,
  const sns_rh_rpt_spec_s*  new_rpt_ptr)
{
  bool identical = true;
  uint8_t i;
  /* ---------------------------------------------------------------------- */

  if ( existing_rpt_ptr->num_items != new_rpt_ptr->num_items ||
       existing_rpt_ptr->q16_rpt_rate != new_rpt_ptr->q16_rpt_rate )
  {
    identical = false;
  }

  if ( identical )
  {
    RH_FOR_EACH_REPORT_ITEM( existing_rpt_ptr, i )
    {
      sns_rh_rpt_item_s* new_item_ptr = new_rpt_ptr->item_list[i];
      sns_rh_rpt_item_s* old_item_ptr = existing_rpt_ptr->item_list[i];

      if ( (old_item_ptr->ddf_sensor_ptr != new_item_ptr->ddf_sensor_ptr) ||
           (old_item_ptr->sampling_rate_hz != new_item_ptr->sampling_rate_hz) || 
           (old_item_ptr->flags != new_item_ptr->flags) || 
           (old_item_ptr->cal_sel != new_item_ptr->cal_sel))
      {
        identical = false;
        break;
      }
    }
  }

  return identical;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_update_pending_report

===========================================================================*/
/*!
  @brief Updates pending report so it won't send samples already sent

  @param[i] existing_rpt_ptr
  @param[i] pending_rpt_ptr

  @return   none
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_update_pending_report(
  sns_rh_rpt_spec_s* existing_rpt_ptr,
  sns_rh_rpt_spec_s* pending_rpt_ptr)
{
  uint32_t i, j;
  for ( i=0; i<pending_rpt_ptr->num_items; i++ )
  {
    for ( j=0; j<existing_rpt_ptr->num_items; j++ )
    {
      if ( pending_rpt_ptr->item_list[i]->ddf_sensor_ptr == 
           existing_rpt_ptr->item_list[j]->ddf_sensor_ptr &&
           existing_rpt_ptr->item_list[j]->samples_sent )
      {
        pending_rpt_ptr->item_list[i]->samples_sent = true;
        pending_rpt_ptr->item_list[i]->ts_last_sent = 
          existing_rpt_ptr->item_list[j]->ts_last_sent;
        pending_rpt_ptr->item_list[i]->last_processed_sample_timestamp =
          existing_rpt_ptr->item_list[j]->last_processed_sample_timestamp;
        SNS_SMGR_PRINTF3(
          LOW, "update_pending_report - sensor=%u last_sent=%u last_proc=%u",
          SMGR_SENSOR_ID(pending_rpt_ptr->item_list[i]->ddf_sensor_ptr->sensor_ptr),
          pending_rpt_ptr->item_list[i]->ts_last_sent,
          pending_rpt_ptr->item_list[i]->last_processed_sample_timestamp);
        break;
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_schedule_existing_report

===========================================================================*/
/*!
  @brief   Schedules flush, deletes/attaches new reports if those already exist.
  @detail  Schedules fifo flush and depot flush for existing report
           (existing_rpt_ptr) if new report (new_rpt_ptr) should replace it.
           Removes and frees pending report (rpt_pending) and replaces it by
           new pending one.

  @param[i/o] new_rpt_ptr      - the new report to schedule
  @param[i/o] existing_rpt_ptr - the existing report to replace or schedule
  @param[o]   pending_resp     - the resp to schedule for later

  @return
   modified sns_rh_rpt_spec_s* report_ptr
*/
/*=========================================================================*/
SMGR_STATIC sns_rh_rpt_spec_s* sns_rh_sol_schedule_existing_report(
  sns_rh_rpt_spec_s*  new_rpt_ptr,
  sns_rh_rpt_spec_s*  existing_rpt_ptr,
  bool*               pending_resp_ptr )
{
  bool identical = sns_rh_sol_compare_reports(existing_rpt_ptr, new_rpt_ptr);
  sns_rh_rpt_spec_s* rpt_pending = existing_rpt_ptr->pending_rpt_ptr;
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF4(
    MED, "sched_existing_report - state=%u/%u identical=%u rpt_pending=%u",
    existing_rpt_ptr->state, existing_rpt_ptr->state_extended,
    identical, rpt_pending ? true : false);

  if ( rpt_pending != NULL )
  {
    /* Cant buffer more rpts waiting for activation */
    if ( SNS_RH_REPORT_IS_PERIODIC(rpt_pending) )
    {
      ((sns_smgr_periodic_report_resp_msg_v01*)rpt_pending->resp_ptr)->AckNak =
        SNS_SMGR_RESPONSE_NAK_RESOURCES_V01;
    }
    else
    {
      ((sns_smgr_buffering_resp_msg_v01*) rpt_pending->resp_ptr)->AckNak = 
        SNS_SMGR_RESPONSE_NAK_RESOURCES_V01;
    }
    rpt_pending->resp_ptr->sns_result_t = SNS_RESULT_FAILURE_V01;
    rpt_pending->resp_ptr->sns_err_t    = SENSOR1_EFAILED;
    sns_rh_mr_send_resp(&rpt_pending->mr_hdr, rpt_pending->resp_ptr);
    sns_rh_sol_delete_report(rpt_pending);

    existing_rpt_ptr->pending_rpt_ptr = NULL;
  }

  if ( existing_rpt_ptr->state_extended == RH_RPT_STATE_EXT_NONE )
  {
    sns_rh_sol_prepare_report_for_flushing(existing_rpt_ptr); 
  }

  if ( existing_rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_PENDING )
  {
    existing_rpt_ptr->pending_rpt_ptr = new_rpt_ptr;
    new_rpt_ptr       = NULL;  /* do not activate new rpt here */
    *pending_resp_ptr = true;  /* do not send resp now */

    if ( !identical )
    {
      existing_rpt_ptr->state_extended = RH_RPT_STATE_EXT_FLUSH_AND_DELETE_PENDING;
    }
    else
    {
      existing_rpt_ptr->state_extended = RH_RPT_STATE_EXT_RESP_PENDING;
    }
  }
  else
  {
    sns_rh_flush_report(existing_rpt_ptr);
    if ( !identical )
    {
      sns_rh_sol_update_pending_report(existing_rpt_ptr, new_rpt_ptr);
      sns_rh_sol_delete_report(existing_rpt_ptr);
    }
    else
    {
      sns_rh_sol_delete_report(new_rpt_ptr);
      new_rpt_ptr = NULL;
    }
  }

  return new_rpt_ptr;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_activate_report

===========================================================================*/
/*!
  @brief Activates a report by updating its requested sensors

  @param[i] rpt_ptr - the report to be activated

  @return None
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_sol_activate_report(sns_rh_rpt_spec_s* rpt_ptr)
{
  uint8_t  i;
  sns_q_s* rpt_queue_ptr = sns_rh_get_report_queue();
  sns_q_put(rpt_queue_ptr, &rpt_ptr->rpt_link);

  SNS_SMGR_PRINTF4(
    HIGH, "activate_report - rpt_id=%u/0x%x type=%u/0x%x", 
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
    rpt_ptr->msg_header.svc_num, rpt_ptr->msg_header.msg_id);
  SNS_SMGR_PRINTF2(
    HIGH, "activate_report - proc=%u #reports=%u", 
    rpt_ptr->proc_type, sns_q_cnt(rpt_queue_ptr));

  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    sns_rh_sol_link_item_to_sensor(rpt_ptr->item_list[i]);
  }

  sns_smgr_update_eff_rept_rate_est(rpt_ptr->q16_rpt_rate, 0, rpt_ptr->proc_type);
  sns_smgr_update_avgitems();
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_schedule_report

===========================================================================*/
/*!
  @brief Schedules a report.

  @param[i] report_ptr - the new report to schedule

  @return
   bool pending_resp
*/
/*=========================================================================*/
bool sns_rh_sol_schedule_report(
  const sns_rh_mr_header_s* hdr_ptr,
  sns_rh_rpt_spec_s*        report_ptr)
{
  bool pending_resp = false;
  sns_rh_rpt_spec_s* existing_report_ptr =
    sns_rh_sol_find_report(hdr_ptr, report_ptr->rpt_id);
  /* ---------------------------------------------------------------------- */

  if ( existing_report_ptr != NULL )
  {
    report_ptr =
      sns_rh_sol_schedule_existing_report(report_ptr, existing_report_ptr, &pending_resp);
  }

  if ( report_ptr != NULL )
  {
    sns_rh_sol_activate_report(report_ptr);
  }
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);

  return pending_resp;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_schedule_buffering_report

===========================================================================*/
/*!
  @brief Insert a buffering report to a schedule block.

  @param[i] hdr_ptr - Point to header structure for the incoming request
  @param[i] req_ptr - points to the structure of incoming request message
  @param[i] resp_ptr - Point to instance of response message structure

  @return
   None
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_schedule_buffering_report(
  const sns_rh_mr_header_s*        hdr_ptr,
  sns_smgr_buffering_req_msg_v01*  req_ptr,
  sns_smgr_buffering_resp_msg_v01* resp_ptr)
{
  bool pending_resp = false;
  sns_rh_rpt_spec_s* rpt_ptr = NULL;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* -------------------------------------------------------------------- */

  if ( SNS_SMGR_MAX_REPORT_CNT > sns_q_cnt(rpt_queue_ptr) )
  {
    rpt_ptr = SMGR_ANY_ALLOC_STRUCT(sns_rh_rpt_spec_s);
  }
  else
  {
    sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                     SNS_SMGR_RESPONSE_NAK_RESOURCES_V01);
    SNS_SMGR_PRINTF0(ERROR, "schedule_buffering_report - max# of reports present");
  }

  if ( NULL == rpt_ptr )
  {
    sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                     SNS_SMGR_RESPONSE_NAK_RESOURCES_V01);
    SNS_SMGR_PRINTF1(ERROR, "schedule_buffering_rpt - alloc %d bytes failed",
                     sizeof(sns_rh_rpt_spec_s));
  }
  else
  {
    uint8_t ackNak = sns_rh_sol_validate_buffering_rate(req_ptr);
    if ( ackNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 )
    {
      ackNak = sns_rh_sol_parse_buffering_report_request(hdr_ptr, req_ptr, resp_ptr, rpt_ptr);
    }
    if ( ackNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 )
    {
      /* Store resp for later send */
      rpt_ptr->resp_ptr = (sns_common_resp_s_v01*) resp_ptr;
      rpt_ptr->mr_hdr   = *hdr_ptr;
      pending_resp = sns_rh_sol_schedule_report(hdr_ptr, rpt_ptr);
    }
    else
    {
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak, ackNak);
      sns_rh_sol_delete_report(rpt_ptr);
    }
  }

  return pending_resp;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_delete_report

===========================================================================*/
/*!
  @brief Remove report block and item blocks.

  @param[i] rpt_ptr: the report to be deleted

  @return
   None
*/
/*=========================================================================*/
void sns_rh_sol_delete_report(sns_rh_rpt_spec_s* rpt_ptr)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptrs[SNS_SMGR_MAX_ITEMS_PER_REPORT_V01];
  SNS_OS_MEMZERO(ddf_sensor_ptrs, sizeof(ddf_sensor_ptrs));

  rpt_ptr->sensor_event_q = NULL;
  rpt_ptr->state = RH_RPT_STATE_DELETING;

  sns_rh_sol_get_ddf_sensor_list(rpt_ptr, ddf_sensor_ptrs);
  sns_rh_sol_deactivate_report(rpt_ptr);
  sns_rh_sol_update_sensor_events(ddf_sensor_ptrs);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_deactivate_report

===========================================================================*/
/*!
  @brief Deactivates a report
 
  @details
  Disassociates the report from its requested sensors, removes it from
  the report queue, and either puts it in its holding queue or frees its
  resources.

  @param[i] rpt_ptr - the report to be deactivated

  @return None
*/
/*=========================================================================*/
void sns_rh_sol_deactivate_report(sns_rh_rpt_spec_s* rpt_ptr)
{
  uint8_t  i;
  sns_q_s* q_ptr = SMGR_QUE_HEADER_FROM_LINK(&rpt_ptr->rpt_link);
  /* -------------------------------------------------------------------- */

  SNS_SMGR_PRINTF4(
    HIGH, "deactivate_report - rpt_id=%u/0x%x type=%u/0x%x", 
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
    rpt_ptr->msg_header.svc_num, rpt_ptr->msg_header.msg_id);
  SNS_SMGR_PRINTF4(
    HIGH, "deactivate_report - proc=%u state=%u #inds=%u queued=%u", 
    rpt_ptr->proc_type, rpt_ptr->state, rpt_ptr->ind_count, q_ptr ? true : false);

  sns_rh_rpt_gen_remove_from_ready_list(rpt_ptr);

  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];

    while ( item_ptr->query_ptr != NULL )
    {
      sns_rh_query_s* query_ptr = item_ptr->query_ptr;
      item_ptr->query_ptr = query_ptr->next_query_ptr;
      sns_rh_rpt_gen_send_empty_query_indication(query_ptr);
      SNS_OS_ANY_FREE(query_ptr);
    }
    sns_rh_sol_unlink_item_to_sensor(item_ptr);

    if ( rpt_ptr->sensor_event_q != NULL )
    {
      sns_rh_cic_obj_s* cic_obj_ptr = &item_ptr->cic_obj;
      SNS_OS_MEMZERO(&item_ptr->interpolator_obj, sizeof(sns_rh_interpolator_obj_s));
      sns_rh_cic_init(cic_obj_ptr, cic_obj_ptr->factor, cic_obj_ptr->input_frequency,
                      item_ptr->depot_ptr->num_axes);
      item_ptr->quality = SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01;
      item_ptr->effective_rate_hz = 0;
      item_ptr->last_processed_sample_timestamp = 0;
      item_ptr->ts_last_sent = 0;
    }
    else
    {
      SNS_OS_ANY_FREE(item_ptr);
    }
  }

  if ( NULL != q_ptr )
  {
    sns_smgr_update_eff_rept_rate_est(0, rpt_ptr->q16_rpt_rate, rpt_ptr->proc_type);
    sns_smgr_update_avgitems();
    sns_q_delete(&rpt_ptr->rpt_link);
  }

  if ( rpt_ptr->sensor_event_q != NULL )
  {
    rpt_ptr->rpt_tick  = 0;
    rpt_ptr->ind_count = 0;
    sns_q_put(rpt_ptr->sensor_event_q, &rpt_ptr->rpt_link);
  }
  else
  {
    SNS_OS_ANY_FREE(rpt_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_schedule_periodic_report

===========================================================================*/
/*!
  @brief Schedules new Periodic report.

  @param[i]  hdr_ptr  - header for the incoming request
  @param[i]  req_ptr  - incoming request message
  @param[io] resp_ptr - response message structure

  @return
   None
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_sol_schedule_periodic_report(
  const sns_rh_mr_header_s*              hdr_ptr,
  sns_smgr_periodic_report_req_msg_v01*  req_ptr,
  sns_smgr_periodic_report_resp_msg_v01* resp_ptr)
{
  bool pending_resp = false;
  sns_rh_rpt_spec_s *rpt_ptr = NULL;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* -------------------------------------------------------------------- */

  if ( SNS_SMGR_MAX_REPORT_CNT > sns_q_cnt(rpt_queue_ptr) )
  {
    rpt_ptr = SMGR_ANY_ALLOC_STRUCT(sns_rh_rpt_spec_s);
  }
  else
  {
    sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                     SNS_SMGR_RESPONSE_NAK_RESOURCES_V01);
    SNS_SMGR_PRINTF0(ERROR, "schedule_periodic_report - max# of reports present");
  }

  if ( NULL == rpt_ptr )
  {
    if ( resp_ptr->AckNak != SNS_SMGR_RESPONSE_NAK_RESOURCES_V01 )
    {
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                       SNS_SMGR_RESPONSE_NAK_RESOURCES_V01);
      SNS_SMGR_PRINTF1(ERROR, "schedule_periodic_report - alloc %d bytes failed",
                       sizeof(sns_rh_rpt_spec_s));
    }
  }
  else
  {
    uint8_t ackNak =
      sns_rh_sol_parse_periodic_report_request(hdr_ptr, req_ptr, resp_ptr, rpt_ptr);
    if ( ackNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 )
    {
      rpt_ptr->resp_ptr = (sns_common_resp_s_v01*)resp_ptr;
      rpt_ptr->mr_hdr   = *hdr_ptr;
      pending_resp = sns_rh_sol_schedule_report(hdr_ptr, rpt_ptr);
    }
    else
    {
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak, ackNak);
      sns_rh_sol_delete_report(rpt_ptr);
    }
  }
  return pending_resp;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_process_periodic_request

===========================================================================*/
/*!
  @brief Processes SNS_SMGR_REPORT_REQ_V01
 
  @details
    - Add, modify or delete a SOL entry consisting of the report spec structure
      plus subordinate item structures. Subordinate structures have
      dependencies on sensor sampling structures. When possible, connect to or
      disconnect from sensors without causing changes in the established
      sampling pattern. Set flags if sensor plan must be recalculated.
    - Send a response message for the request message providing ACK or NAK.
      Provide reasons for NAK or dropped items. Notify when defaults have been
      applied.

  @param[i] req_ptr  - incoming request message

  @return SNS_ERR_NOMEM or SNS_SUCCESS
*/
/*=========================================================================*/
sns_err_code_e sns_rh_sol_process_periodic_request(
  sns_rh_mr_req_q_item_s* msg_ptr)
{
  uint8_t ack_nak;
  bool success = true;
  bool rpt_pending_activation_and_resp = false;
  sns_smgr_periodic_report_req_msg_v01*  req_ptr = &msg_ptr->request.periodic_report;
  sns_smgr_periodic_report_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_periodic_report_resp_msg_v01);
  /* ---------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  sns_profiling_log_qdss(SNS_RH_RPT_REQ, 4, 
                         req_ptr->ReportId, msg_ptr->header.connection_handle, 
                         SNS_SMGR_REPORT_REQ_V01, req_ptr->Action );

  SNS_SMGR_PRINTF4(
    MED, "periodic_req - rpt_id=%u/0x%x action=%u rate=%u",
    req_ptr->ReportId, msg_ptr->header.connection_handle, 
    req_ptr->Action, req_ptr->ReportRate);

  if ( req_ptr->SrcModule_valid )
  {
    msg_ptr->header.src_module = req_ptr->SrcModule;
  }

  msg_ptr->header.msg_id   = SNS_SMGR_REPORT_RESP_V01;
  msg_ptr->header.body_len = sizeof(sns_smgr_periodic_report_resp_msg_v01);

  resp_ptr->ReportId = req_ptr->ReportId;
  resp_ptr->ReasonPair_len = 0;
  resp_ptr->AckNak = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
  resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
  resp_ptr->Resp.sns_err_t = SENSOR1_SUCCESS;

  switch( req_ptr->Action )
  {
    case SNS_SMGR_REPORT_ACTION_ADD_V01:
      rpt_pending_activation_and_resp =
        sns_rh_sol_schedule_periodic_report(&msg_ptr->header, req_ptr, resp_ptr);
      break;
    case SNS_SMGR_REPORT_ACTION_DELETE_V01:
      ack_nak = sns_rh_sol_find_and_delete_report(
                  msg_ptr->header.connection_handle, req_ptr->ReportId, false);
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak, ack_nak);
      break;
    default:
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                       SNS_SMGR_RESPONSE_NAK_UNK_ACTION_V01);
      break;
  }

  if ( (resp_ptr->AckNak != SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (resp_ptr->AckNak != SNS_SMGR_RESPONSE_ACK_MODIFIED_V01) )
  {
     resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
     resp_ptr->Resp.sns_err_t = SENSOR1_EFAILED;
     success = false;
  }

  if ( success )
  {
    sns_rh_flush_reports();
    sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  }

  if ( !rpt_pending_activation_and_resp )
  {
    sns_rh_mr_send_resp(&msg_ptr->header, resp_ptr);
  }

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_process_buffering_request

===========================================================================*/
/*!
  @brief Processes SNS_SMGR_BUFFERING_REQ_V01
 
  @details
    - Add, modify or delete a SOL entry consisting of the report spec structure
      plus subordinate item structures. Subordinate structures have
      dependencies on sensor sampling structures. When possible, connect to or
      disconnect from sensors without causing changes in the established
      sampling pattern. Set flags if sensor plan must be recalculated.
    - Sends a response message for the request message providing ACK or NAK.
      Provides reasons for NAK or dropped items. Notifies when defaults have been
      applied.

  @param[i] req_ptr  - incoming request message

  @return SNS_ERR_NOMEM or SNS_SUCCESS
*/
/*=========================================================================*/
sns_err_code_e sns_rh_sol_process_buffering_request(
  sns_rh_mr_req_q_item_s*  msg_ptr)
{
  bool rpt_pending_activation_and_resp = false;
  bool success = true;
  uint8_t ack_nak;
  sns_smgr_buffering_req_msg_v01*  req_ptr = &msg_ptr->request.buffering_report;
  sns_smgr_buffering_resp_msg_v01* resp_ptr = 
    SMGR_ALLOC_STRUCT(sns_smgr_buffering_resp_msg_v01);
  /* ---------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  sns_profiling_log_qdss(SNS_RH_RPT_REQ, 4, 
                         req_ptr->ReportId, msg_ptr->header.connection_handle, 
                         SNS_SMGR_BUFFERING_REQ_V01, req_ptr->Action );

  SNS_SMGR_PRINTF4(
    MED, "buffering_req - rpt_id=%u/0x%x action=%d items=%d",
    req_ptr->ReportId, msg_ptr->header.connection_handle, 
    req_ptr->Action, req_ptr->Item_len);

  msg_ptr->header.msg_id   = SNS_SMGR_BUFFERING_RESP_V01;
  msg_ptr->header.body_len = sizeof(sns_smgr_buffering_resp_msg_v01);

  resp_ptr->ReportId          = req_ptr->ReportId;
  resp_ptr->ReportId_valid    = true;
  resp_ptr->ReasonPair_len    = 0;
  resp_ptr->AckNak            = SNS_SMGR_RESPONSE_ACK_SUCCESS_V01;
  resp_ptr->AckNak_valid      = true;
  resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
  resp_ptr->Resp.sns_err_t    = SENSOR1_SUCCESS;

  SNS_SMGR_PRINTF3(MED, "buffering_req - src_valid=%d src=%d conn=0x%x",
                   req_ptr->SrcModule_valid, req_ptr->SrcModule,
                   msg_ptr->header.connection_handle);

  if ( req_ptr->SrcModule_valid )
  {
    msg_ptr->header.src_module = req_ptr->SrcModule;
  }

  switch( req_ptr->Action )
  {
    case SNS_SMGR_BUFFERING_ACTION_ADD_V01:
      rpt_pending_activation_and_resp =
        sns_rh_sol_schedule_buffering_report(&msg_ptr->header, req_ptr, resp_ptr);
      break;
    case SNS_SMGR_BUFFERING_ACTION_DELETE_V01:
      ack_nak = sns_rh_sol_find_and_delete_report(
                  msg_ptr->header.connection_handle, req_ptr->ReportId, false);
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak, ack_nak);
      break;
    default:
      /* Unknown action code */
      sns_rh_sol_override_response_ack(&resp_ptr->AckNak,
                                       SNS_SMGR_RESPONSE_NAK_UNK_ACTION_V01);
      break;
  }

  if ( (resp_ptr->AckNak != SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (resp_ptr->AckNak != SNS_SMGR_RESPONSE_ACK_MODIFIED_V01) )
  {
     resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
     resp_ptr->Resp.sns_err_t = SENSOR1_EFAILED;
     success = false;
  }
  if ( resp_ptr->ReasonPair_len > 0 )
  {
    resp_ptr->ReasonPair_valid = true;
  }

  if ( success )
  {
    sns_rh_flush_reports();
    sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  }

  if ( !rpt_pending_activation_and_resp )
  {
    sns_rh_mr_send_resp(&msg_ptr->header, resp_ptr);
  }

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_process_buffering_query_request

===========================================================================*/
/*! 
  @brief Processes SNS_SMGR_BUFFERING_QUERY_REQ_V01
 
  @details
  Called from the input driver when a queued message has been identified
  as a Buffering Query request.  The same client is expected to have already
  sent Buffering request for the sensor specified in this Query request.

  @param[i] req_ptr  - incoming request message

  @return SNS_ERR_NOMEM or SNS_SUCCESS
*/
/*=========================================================================*/
sns_err_code_e sns_rh_sol_process_buffering_query_request(
  sns_rh_mr_req_q_item_s* msg_ptr)
{
  sns_smgr_buffering_query_req_msg_v01*  req_ptr = &msg_ptr->request.query_report;
  sns_smgr_buffering_query_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_buffering_query_resp_msg_v01);
  uint32_t           time_now = sns_em_get_timestamp();
  sns_rh_rpt_item_s* item_ptr = NULL;
  sns_rh_query_s**   qpp = NULL;
  sns_rh_query_s*    query_ptr = NULL;
  /* ---------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF3(
    MED, "query_req - id=0x%x sensor=%d dtype=%d",
    req_ptr->QueryId, req_ptr->SensorId, req_ptr->DataType);
  SNS_SMGR_PRINTF3(
    MED, "query_req - T0=%u T1=%u now=%u",
    req_ptr->TimePeriod[0], req_ptr->TimePeriod[1], 
    time_now);

  resp_ptr->QueryId_valid  = true;
  resp_ptr->QueryId        = req_ptr->QueryId;
  resp_ptr->AckNak_valid   = true;
  resp_ptr->AckNak         = 
    sns_rh_sol_find_query_item(&msg_ptr->header, req_ptr, &item_ptr);

  /* Verify that Query ID is unique and there are fewer than max outstanding queries */
  if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (item_ptr != NULL) )
  {
    uint8_t outstanding_queries = 0;
    for ( qpp=&item_ptr->query_ptr; *qpp!=NULL && (query_ptr=*qpp)!=FALSE;
          qpp=&(*qpp)->next_query_ptr )
    {
      if ( query_ptr->query_id == req_ptr->QueryId )
      {
        /* Query IDs must be unique; reject this request */
        resp_ptr->AckNak = SNS_SMGR_RESPONSE_NAK_QUERY_ID_V01;
        break;
      }
      outstanding_queries++;
    }
    if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
         (outstanding_queries >= SMGR_MAX_EIS_QUERY_REQUESTS) )
    {
      resp_ptr->AckNak = SNS_SMGR_REASON_OTHER_FAILURE_V01;
      SNS_SMGR_PRINTF0(ERROR, "query_req - max outstanding queries");
    }
  }

  /* Sanity check for T0 and T1 */
  if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (req_ptr->TimePeriod[0] >= req_ptr->TimePeriod[1]) )
  {
    resp_ptr->AckNak = SNS_SMGR_RESPONSE_NAK_TIME_PERIOD_V01;
    SNS_SMGR_PRINTF0(ERROR, "query_req - T1 < T0");
  }

  /* Verify that T0 and T1 meet the requirements */
  if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 ) &&
       (item_ptr != NULL) )
  {
    uint8_t num_samples = ((req_ptr->TimePeriod[1] - req_ptr->TimePeriod[0])/
                           item_ptr->sampling_interval);
    uint32_t time_for_max_samples =
      item_ptr->sampling_interval * SMGR_MAX_EIS_QUERY_SAMPLES;
    uint32_t lower_time_limit = time_now - time_for_max_samples;
    uint32_t upper_time_limit = time_now + time_for_max_samples;

    if ( (num_samples > SMGR_MAX_EIS_QUERY_SAMPLES) ||
         (req_ptr->TimePeriod[0] > upper_time_limit) ||
         (req_ptr->TimePeriod[1] < lower_time_limit) )
    {
      resp_ptr->AckNak = SNS_SMGR_RESPONSE_NAK_TIME_PERIOD_V01;
      SNS_SMGR_PRINTF3(
        ERROR, "query_req - samples=%d lower=%u upper=%u",
        num_samples, lower_time_limit, upper_time_limit);
    }
  }

  /* Everything checks out */
  if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (qpp != NULL) )
  {
    query_ptr = SMGR_ALLOC_STRUCT(sns_rh_query_s);
    if ( query_ptr != NULL )
    {
      SNS_OS_MEMZERO(query_ptr, sizeof(sns_rh_query_s));
      query_ptr->item_ptr = item_ptr;
      query_ptr->query_id = req_ptr->QueryId;
      query_ptr->T0       = req_ptr->TimePeriod[0];
      query_ptr->T1       = req_ptr->TimePeriod[1];
      query_ptr->msg_header = msg_ptr->header;
      *qpp = query_ptr;
    }
    else
    {
      resp_ptr->AckNak = SNS_SMGR_RESPONSE_NAK_RESOURCES_V01;
    }
  }

  /* See if data is available for the requested time period */
  if ( (resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01) &&
       (item_ptr != NULL) )
  {
    const sns_smgr_sample_s* oldest_sample_ptr =
      sns_smgr_depot_get_oldest_sample(item_ptr->depot_ptr);
    const sns_smgr_sample_s* latest_sample_ptr =
      sns_smgr_depot_get_latest_sample(item_ptr->depot_ptr);
    if ( (oldest_sample_ptr != NULL) && (latest_sample_ptr != NULL) )
    {
      SNS_SMGR_PRINTF2(
        LOW, "query_req - oldest=%u latest=%u",
        oldest_sample_ptr->time_stamp, latest_sample_ptr->time_stamp);
    }
    if ( (latest_sample_ptr != NULL) &&
         (req_ptr->TimePeriod[1] < latest_sample_ptr->time_stamp) )
    {
      /* data available for the time period */
      sns_rh_add_to_ready_list(item_ptr->parent_report_ptr);
    }
    /* else, when T1 is reached, report will be generated */
  }

  if ( resp_ptr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 )
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_SUCCESS;
  }
  else
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EFAILED;
  }
  SNS_SMGR_PRINTF1(HIGH, "query_req - ackNak=%d", resp_ptr->AckNak);

  msg_ptr->header.msg_id   = SNS_SMGR_BUFFERING_QUERY_RESP_V01;
  msg_ptr->header.body_len = sizeof(sns_smgr_buffering_query_resp_msg_v01);
  sns_rh_mr_send_resp(&msg_ptr->header, resp_ptr);

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_update_sensor_status

===========================================================================*/
/*!
  @brief Sends Sensor Status indication to all clients interested in the given
         sensor's status
 
  @details Called when some aspects of the given sensor have changed

  @param[i] ddf_sensor_ptr - the DDF sensor
 
  @return  none
 */
/*=========================================================================*/
void sns_rh_sol_update_sensor_status(sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  sns_q_s* ssr_q_ptr = &ddf_sensor_ptr->client_stat.sensor_status.request_queue;
  sns_rh_mr_req_q_item_s* req_q_item_ptr;
  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( ssr_q_ptr, req_q_item_ptr, q_link )
  {
    sns_rh_generate_sensor_status_ind(ddf_sensor_ptr, req_q_item_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_update_items_info

===========================================================================*/
/*!
  @brief After DDF sensor is configured with new ODR its associated report
         items must be updated.

  @param[i] ddf_sensor_ptr - the DDF sensor
  @param[i] new_items_only - whether to update only items in LINKING state

  @return
*/
/*=========================================================================*/
void sns_rh_sol_update_items_info(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr,
  bool                    new_items_only)
{
  sns_rh_rpt_item_s*  item_ptr;
  sns_rh_rpt_item_s** item_ptr_ptr;
  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF4(
    MED, "update_items_info - ddf_sensor=%d new_only=%u odr=%u depot_data_rate=0x%X",
    SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
    new_items_only, ddf_sensor_ptr->current_odr, ddf_sensor_ptr->depot_data_rate);

  SMGR_FOR_EACH_ASSOC_ITEM( ddf_sensor_ptr, item_ptr, item_ptr_ptr )
  {
    uint8_t old_quality = item_ptr->quality;

    if ( new_items_only && (item_ptr->state != RH_RPT_ITEM_STATE_LINKING) )
    {
      continue;
    }
    if ( item_ptr->ts_last_sent == 0 )
    {
#ifndef SNS_QDSP_SIM
      item_ptr->ts_last_sent = item_ptr->parent_report_ptr->msg_header.timestamp;
#else
      item_ptr->ts_last_sent = 
        playback_next_sample_ts - QDSP_PLAYBACK_SAMPLE_LAST_TICK_DELTA;
#endif
    }

    item_ptr->sampling_factor = 
      sns_rh_calculate_sample_factor(ddf_sensor_ptr, item_ptr->sampling_rate_hz);
    sns_rh_sol_test_rate_thresholds(item_ptr);
    sns_rh_sol_compute_cic_factor(item_ptr);
    sns_rh_sol_determine_sample_quality(item_ptr);
    if ( old_quality != item_ptr->quality )
    {
      sns_rh_sol_init_interp_time(item_ptr);
    }

    item_ptr->effective_rate_hz = sns_rh_sol_compute_effective_rate(item_ptr);
    item_ptr->sampling_count    = 0;
    if ( item_ptr->state < RH_RPT_ITEM_STATE_IDLE )
    {
      const sns_smgr_sample_s* sample_ptr;
      item_ptr->state           = RH_RPT_ITEM_STATE_IDLE;
      if ( sns_smgr_ddf_sensor_is_event_sensor(item_ptr->ddf_sensor_ptr) &&
           (NULL != (sample_ptr = sns_smgr_depot_get_latest_sample(
                                    item_ptr->depot_ptr))) )
      {
        item_ptr->ts_last_sent  = sample_ptr->time_stamp - 1;
        if ( item_ptr->parent_report_ptr->num_items == 1 )
        {
          /* this is the only requested sensor in the report; send indication now */
          sns_rh_signal_me(SNS_RH_SAMPLE_READY_SIG);
        } /* else, indication sent when other requested sensors provide samples */
      }
    }
    SNS_SMGR_PRINTF4(
      MED, "items_info - rpt_id=%u/0x%x ind_cnt=%u quality=%d",
      item_ptr->parent_report_ptr->rpt_id, 
      item_ptr->parent_report_ptr->msg_header.connection_handle,
      item_ptr->parent_report_ptr->ind_count, item_ptr->quality);
    SNS_SMGR_PRINTF4(
      LOW, "items_info - state=%u rate=0x%x samp_intvl=%u samp_factor=%u",
      item_ptr->state, item_ptr->effective_rate_hz, item_ptr->sampling_interval,
      item_ptr->sampling_factor);
    SNS_SMGR_PRINTF3(
      LOW, "items_info - interp_intvl=%u desired=%u last=%u",
      item_ptr->interpolator_obj.interval_ticks,
      item_ptr->interpolator_obj.desired_timestamp,
      item_ptr->ts_last_sent);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_update_periodic_like_flag

===========================================================================*/
/*!
  @brief Sets periodic_like field based on report rate and sampling rates
  @param [io] rpt_ptr - the report of interest
  @return none
*/
/*=========================================================================*/
void sns_rh_update_periodic_like_flag(sns_rh_rpt_spec_s* rpt_ptr)
{
  rpt_ptr->periodic_like = true;
  if ( rpt_ptr->q16_rpt_rate != 0 )
  {
    q16_t max_sampling_rate = rpt_ptr->item_list[0]->sampling_rate_hz;
    uint8_t i;
    RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
    {
      max_sampling_rate = MAX(max_sampling_rate,
                              rpt_ptr->item_list[i]->sampling_rate_hz);
    }

    if ( (float)((float)max_sampling_rate/(float)rpt_ptr->q16_rpt_rate) < 
         RH_SOL_PERIODIC_LIKE_RATIO_THRESHOLD )
    {
      rpt_ptr->q16_rpt_rate = max_sampling_rate;
    }

    /* TODO - Consider making sub-hz request-handling smarter, such that sub-hz
       for high-sampling-rate sensors (like gyro), do not incur a higher power
       penalty. The higher power penalty comes from the RH having to check if
       a report is ready to go out after receiving every sample. This could be
       optimized in reports where the report rate is sub-hz while the sampling
       rate is very high (like 50 Hz or higher). */
    if ( rpt_ptr->q16_rpt_rate != max_sampling_rate )
    {
      rpt_ptr->periodic_like = false;
    }
    rpt_ptr->q16_rpt_rate = MIN(rpt_ptr->q16_rpt_rate, max_sampling_rate);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_reschedule_reports

===========================================================================*/
/*!
  @brief Reschedules reports associated with the given sensor
 
  @details Called when the given sensor completes ODR (re)configuration.

  @param   ddf_sensor_ptr
 
  @return  none
 */
/*=========================================================================*/
void sns_rh_sol_reschedule_reports(sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  bool reports_rescheduled = false;
  sns_rh_rpt_item_s*  item_ptr;
  sns_rh_rpt_item_s** item_ptr_ptr;
  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_ASSOC_ITEM( ddf_sensor_ptr, item_ptr, item_ptr_ptr )
  {
    sns_rh_rpt_spec_s* rpt_ptr = item_ptr->parent_report_ptr;
    int old_rpt_intvl = (int) rpt_ptr->rpt_interval;
    uint32_t time_now;

    if ( SNS_RH_REPORT_IS_PERIODIC(rpt_ptr) || rpt_ptr->periodic_like ||
         rpt_ptr->q16_rpt_rate == 0 ||
         rpt_ptr->state == RH_RPT_STATE_DELETING ||
         item_ptr->effective_rate_hz == 0 )
    {
      /* skips scheduling Periodic, Periodic-like, and Query reports, and 
         reports being deleted or being added */
      continue;
    }

    if ( !sns_rh_sol_compute_report_interval(rpt_ptr) ||
         rpt_ptr->rpt_interval == 0 )
    {
      continue; /* report still not set up completely */
    }

#ifndef SNS_QDSP_SIM
    time_now = sns_em_get_timestamp();
#else
    time_now = sns_qdsp_sim_low_tick();
#endif

    reports_rescheduled = true;
    if ( (rpt_ptr->rpt_tick == 0) || (old_rpt_intvl == 0) )
    {
      sns_rh_rpt_spec_s* same_rate_rpt_ptr = sns_rh_find_same_report_rate(rpt_ptr);
      SNS_SMGR_PRINTF4(
         MED, "resched_rpts - old tick/intvl=%u/%u same(id/tick)=%u/%u",
         rpt_ptr->rpt_tick, old_rpt_intvl, 
         same_rate_rpt_ptr ? same_rate_rpt_ptr->rpt_id : 999,
         same_rate_rpt_ptr ? same_rate_rpt_ptr->rpt_tick : 0);

      if ( same_rate_rpt_ptr != NULL )
      {
        rpt_ptr->rpt_tick = same_rate_rpt_ptr->rpt_tick;
      }
      else
      {
        rpt_ptr->rpt_tick = rpt_ptr->rpt_interval + time_now;
      }
    }
    else
    {
      sns_ddf_time_t latest_sample_ts = 0;
      uint32_t old_rpt_tick = rpt_ptr->rpt_tick;
      int delta_intvl = (int) rpt_ptr->rpt_interval - old_rpt_intvl;
      sns_err_code_e get_result = 
        sns_rh_get_latest_sample_timestamp(item_ptr, &latest_sample_ts);
      SNS_SMGR_PRINTF4(
         MED, "resched_rpts - old rpt_tick=%u delta_intvl=%d #inds=%u sample_ts=%u",
         rpt_ptr->rpt_tick, delta_intvl, rpt_ptr->ind_count, latest_sample_ts);
      if ( (ddf_sensor_ptr->sensor_ptr->fifo_cfg.current_watermark > 1) &&
           (rpt_ptr->ind_count > 0) && (SNS_SUCCESS == get_result) &&
           TICK1_GTR_TICK2(latest_sample_ts, item_ptr->last_processed_sample_timestamp) )
      {
        rpt_ptr->rpt_tick = latest_sample_ts;
      }
      else
      {
        sns_ddf_time_t next_samples_ts;
        rpt_ptr->rpt_tick += delta_intvl;
        next_samples_ts = 
          ddf_sensor_ptr->sensor_ptr->fifo_cfg.current_watermark * 
          ddf_sensor_ptr->depot_data_interval + time_now;
        if ( TICK1_GTR_TICK2(next_samples_ts, rpt_ptr->rpt_tick) )
        {
          rpt_ptr->rpt_tick = time_now;
        }
      }
      if ( TICK1_GTR_TICK2(rpt_ptr->rpt_tick, old_rpt_tick)  )
      {
        sns_rh_signal_me(SNS_RH_REPORT_TIMER_SIG);
      }
    }

    SNS_SMGR_PRINTF4(
      HIGH, "resched_rpts - rpt_id=%u/0x%x intvl=%d tick=%u", 
      rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle,
      rpt_ptr->rpt_interval, rpt_ptr->rpt_tick);
    SNS_SMGR_PRINTF3(
      HIGH, "resched_rpts - ddf_sensor=%d samples_sent=%d last=%u",
      SMGR_SENSOR_TYPE(item_ptr->ddf_sensor_ptr->sensor_ptr,
                       item_ptr->ddf_sensor_ptr->data_type),
      item_ptr->samples_sent, item_ptr->ts_last_sent);
  }
  if ( reports_rescheduled )
  {
    /* Signal the RH thread to update the report timer */
    sns_rh_signal_me(SNS_RH_UPDATE_REPORT_TIMER_SIG);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_select_item_depot

===========================================================================*/
/*!
  @brief Selects the sample depot to be used by the given item 
  @param [io] item_ptr - the report item of interest
  @return none
*/
/*=========================================================================*/
void sns_rh_select_item_depot(sns_rh_rpt_item_s* item_ptr)
{
  uint8_t code = 0;
  if ( item_ptr->ddf_sensor_ptr->ddf_sensor_info->uimg_depot_info.depth == 0 )
  {
    /* no uImage buffer available */ 
    item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->bimg_depot_ptr;
    code = 1;
  }
  else if ( item_ptr->sampling_rate_hz < FX_ONE_Q16 )
  {
    /* subHz request must use bigImage depot */
    item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->bimg_depot_ptr;
    code = 5;
  }
  else if ( SNS_RH_REPORT_IS_PERIODIC(item_ptr->parent_report_ptr) ||
            item_ptr->parent_report_ptr->periodic_like )
  {
    /* Periodic reports can pull samples directly from uImage depot */ 
    item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->uimg_depot_ptr;
    code = 2;
  }
  else if ( item_ptr->parent_report_ptr->q16_rpt_rate == 0 )
  {
    /* Query reports can pull samples directly from uImage depot */ 
    item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->uimg_depot_ptr;
    code = 3;
  }
  else
  {
    uint32_t odr = sns_smgr_choose_odr(item_ptr->ddf_sensor_ptr->sensor_ptr);
    q16_t odr_q16 = smgr_rate_hz_to_q16(odr);
    uint16_t samples_per_report = odr_q16 / item_ptr->parent_report_ptr->q16_rpt_rate;

    if ( item_ptr->ddf_sensor_ptr->ddf_sensor_info->uimg_depot_info.depth > 
         samples_per_report )
    {
      /* uImage buffer is sufficient for requested batch period */
      item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->uimg_depot_ptr;
      code = 4;
    }
    else
    {
      /* external client requesting buffered samples of non-wakeup sensor
         at rates resulting in more samples than can be held in uImage depot */
      item_ptr->depot_ptr = item_ptr->ddf_sensor_ptr->bimg_depot_ptr;
      code = 6;
    }
  }

  SNS_SMGR_PRINTF3(LOW, "select_item_depot - sensor=%u depth=%u case=%u",
                   SMGR_SENSOR_ID(item_ptr->ddf_sensor_ptr->sensor_ptr),
                   item_ptr->depot_ptr->max_bufs, code);

  sns_rh_update_bimg_depot_usage(item_ptr->ddf_sensor_ptr);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_handle_pending_rpt

===========================================================================*/
/*!
  @brief Delete marked report after fifo and depot flush is done.

  @detail  Report in extended state == RH_RPT_STATE_EXT_FLUSH_AND_DELETE_PENDING
           is deleted in this function.
           Also pending report attached to rpt_ptr will be activated here.

  @param[i/o]  rpt_ptr  - pointer to report
  @return   none
 */
/*=========================================================================*/
void sns_rh_sol_handle_pending_rpt(sns_rh_rpt_spec_s* rpt_ptr)
{
  sns_rh_rpt_spec_s* pending_rpt_ptr = rpt_ptr->pending_rpt_ptr;

  SNS_SMGR_PRINTF4(
    HIGH, "handle_pending_rpt - rpt_id=%u/0x%x ext_state=%u pending=%u", 
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
    rpt_ptr->state_extended, pending_rpt_ptr ? true : false);

  if ( pending_rpt_ptr != NULL )  /* Available new pending rpt */
  {
    if ( rpt_ptr->state_extended == RH_RPT_STATE_EXT_FLUSH_AND_DELETE_PENDING )
    {
      /* updates and activates pending, sends reponse, and deletes existing */
      sns_rh_sol_update_pending_report(rpt_ptr, pending_rpt_ptr);
      sns_rh_sol_activate_report(pending_rpt_ptr);
      sns_rh_mr_send_resp(&pending_rpt_ptr->mr_hdr, pending_rpt_ptr->resp_ptr);
      pending_rpt_ptr->resp_ptr       = NULL;
      sns_rh_sol_delete_report(rpt_ptr);
      sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
    }
    else
    {
      /* sends reponse and deletes pending */
      sns_rh_mr_send_resp(&pending_rpt_ptr->mr_hdr, pending_rpt_ptr->resp_ptr);
      sns_rh_sol_delete_report(pending_rpt_ptr);
      rpt_ptr->state_extended  = RH_RPT_STATE_EXT_NONE;
      rpt_ptr->pending_rpt_ptr = NULL;
    }
  }
  else
  {
    SNS_SMGR_PRINTF0(ERROR, "handle_pending_rpt - missing pending report");
    rpt_ptr->state_extended = RH_RPT_STATE_EXT_NONE;
  }
}

