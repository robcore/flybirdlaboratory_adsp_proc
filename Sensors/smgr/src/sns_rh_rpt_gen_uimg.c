/*=============================================================================
  @file sns_rh_rpt_gen_uimg.c

  Implementation of Report Generation functions that execute in microImage

******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_rpt_gen_uimg.c#4 $ */
/* $DateTime: 2015/05/08 10:28:56 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-05-08  pn   Updates report state for reports with only event sensors
  2014-12-18  pn   - Fixed wrong indication type
                   - Fixed bigImage depot access when generating Periodic indications
  2014-12-08  pn   Fixed sample count estimates for Bufferring reports
  2014-11-24  pn   Corrected ts_last_rpt_sent for multi-sensor reports
  2014-11-06  pn   Updates report state when scheduling next Buffering indications
  2014-10-28  jms  Rpt sending with effective_rate_hz=0 fix
  2014-10-28  pn   Immediately requeues Periodic report until all samples are sent
  2014-10-28  jc   Skip the first sample in report if invalid
  2014-10-22  pn   Added debug messages for Buffering reports
  2014-10-10  pn   Only locks depot if it's going to be accessed
  2014-10-09  pn   Correctly updates report schedule
  2014-10-06  jc   Grab mutex before accessing depot
  2014-10-02  pn   Stays in big-image until report generation is done if 
                   using big-image depots
  2014-09-30  MW   Fixed end_ts for event sensors in 
                   sns_rh_rpt_gen_send_buffering_indications()
  2014-09-25  pn   - Uses depot selected for report item
                   - copies samples from uImage depot when generating indications
  2014-09-23  pn   Added QDSS logging
  2014-09-04  pn   Changed how the next indication is scheduled
  2014-08-21  tc   Allowed the reassignment of the FIRST_IND indType to adjust
                   for unsent first indications.
  2014-08-18  pn   Removed KW error
  2014-08-15  tc   Fixed overflow condition for CurrentRate in periodic ind
  2014-07-31  pn   Obsoleted FEATURE_TEST_DRI
  2014-07-21  pn   Added support for event_gated_buffering
  2014-06-16  pn   Replaced FLAGS_SAMPLES_SENT_B with boolean samples_sent
  2014-06-16  pn   Removed references to unused circular buffer
  2014-05-12  tc   Forced the separation of buffered subHz-sampled data into
                   back-to-back indications with each indication carrying only
                   one sample.
  2014-04-29  pn   Initial version

============================================================================*/

#define __SNS_MODULE__ SNS_RH

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_osa.h"
#include "sns_memmgr.h"

#include "sns_smgr_main.h"
#include "sns_smgr.h"
#include "sns_smgr_util.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_mr.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_sample_proc_uimg.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_B2B_IND_DEBUG
#ifdef SNS_SMGR_B2B_IND_DEBUG
#define SNS_SMGR_B2B_IND_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_B2B_IND_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_B2B_IND_DBG3 SNS_SMGR_PRINTF3
#define SNS_SMGR_B2B_IND_DBG4 SNS_SMGR_PRINTF4
#else
#define SNS_SMGR_B2B_IND_DBG1(level,msg,p1)
#define SNS_SMGR_B2B_IND_DBG2(level,msg,p1,p2)
#define SNS_SMGR_B2B_IND_DBG3(level,msg,p1,p2,p3)
#define SNS_SMGR_B2B_IND_DBG4(level,msg,p1,p2,p3,p4)
#endif

//#define SNS_SMGR_REPORT_DEBUG
#ifdef SNS_SMGR_REPORT_DEBUG
#define SNS_SMGR_REPORT_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_REPORT_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_REPORT_DBG3 SNS_SMGR_PRINTF3
#define SNS_SMGR_REPORT_DBG4 SNS_SMGR_PRINTF4
#else
#define SNS_SMGR_REPORT_DBG1(level,msg,p1)
#define SNS_SMGR_REPORT_DBG2(level,msg,p1,p2)
#define SNS_SMGR_REPORT_DBG3(level,msg,p1,p2,p3)
#define SNS_SMGR_REPORT_DBG4(level,msg,p1,p2,p3,p4)
#endif

#define SNS_RH_1000MS_IN_TICK sns_em_convert_usec_to_dspstick(1000*1000)
#define SNS_RH_100MS_IN_TICK sns_em_convert_usec_to_dspstick(100*1000)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_rh_sol_init_interp_time

===========================================================================*/

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_init_item_depot_iter

===========================================================================*/
/*!
  @brief Initializes given item's depot_iter object.

  @detail Also returned are timestamp of current sample in iterator.

  @param[i]  item_ptr - the report item whose depot_iter to initialize

  @return   None
 */
/*=========================================================================*/
SMGR_STATIC const sns_smgr_sample_s* sns_rh_rpt_gen_init_item_depot_iter(
  sns_rh_rpt_item_s* item_ptr)
{
  const sns_smgr_sample_s* sample_ptr;
  sns_rh_interpolator_obj_s* iobj_ptr = &item_ptr->interpolator_obj;
  /* -------------------------------------------------------------------- */

  if ( item_ptr->last_processed_sample_timestamp != 0 )
  {
    sample_ptr = sns_smgr_depot_init_iter(
                   item_ptr->depot_ptr,
                   item_ptr->last_processed_sample_timestamp,
                   &item_ptr->depot_iter);
  }
  else
  {
    sample_ptr = sns_smgr_depot_init_iter(
                   item_ptr->depot_ptr,
                   item_ptr->ts_last_sent,
                   &item_ptr->depot_iter);
  }

  if (  !item_ptr->samples_sent )
  {
    // Discards initial invalid samples
    while ( sample_ptr != NULL )
    {
      /* either sample is invalid or the one skipped in the previous report */
      if (( sample_ptr->status != SNS_DDF_SUCCESS ) ||
        ((item_ptr->resulting_sample.time_stamp == sample_ptr->time_stamp) &&
         (item_ptr->resulting_sample.status == SNS_DDF_EINVALID_DATA)))
      {
        SNS_SMGR_REPORT_DBG3(
          LOW, "rpt %u not using %u from sensor %u", 
          item_ptr->parent_report_ptr->rpt_id, sample_ptr->time_stamp,
          SMGR_SENSOR_ID(item_ptr->ddf_sensor_ptr->sensor_ptr));
        item_ptr->ts_last_sent = sample_ptr->time_stamp+1;
        sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1);
      }
      else
      {
        if ( iobj_ptr->interval_ticks != 0 )
        {
          iobj_ptr->desired_timestamp = 
            sample_ptr->time_stamp / iobj_ptr->interval_ticks * iobj_ptr->interval_ticks;
          sns_rh_interpolator_update(iobj_ptr, sample_ptr);
        }
        break;
      }
    }
    SNS_SMGR_REPORT_DBG3(
      LOW, "init_iter - sent/sample=%u / %u status=%u",
      item_ptr->ts_last_sent, sample_ptr ? sample_ptr->time_stamp : 99,
      sample_ptr ? sample_ptr->status : 99);
    SNS_SMGR_REPORT_DBG3(
      LOW, "init_iter - ts1=%u ts=%u ts2=%u",
      iobj_ptr->sample1_ptr ? iobj_ptr->sample1_ptr->time_stamp : 0,
      iobj_ptr->desired_timestamp,
      iobj_ptr->sample2_ptr ? iobj_ptr->sample2_ptr->time_stamp : 0);
  }
  return sample_ptr;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_pack_sample

===========================================================================*/
/*!
  @brief Packs the given sample into indication message.

  @param[i]  idx_ptr            - pointer to the sample indices array in indication
  @param[i]  ind_sample_ptr     - pointer to the sample array in indication
  @param[i]  item_spec_ptr      - pointer to item spec
  @param[i]  sample_ptr         - pointer to the source sample
  @param[io] prev_timestamp_ptr - pointer to the previous timestamp

  @return   None
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_rpt_gen_pack_sample(
  sns_smgr_buffering_sample_index_s_v01* idx_ptr,
  sns_smgr_buffering_sample_s_v01*       ind_sample_ptr,
  sns_rh_rpt_item_s*                     item_spec_ptr,
  sns_ddf_status_e                       sample_status,
  const uint32_t*                        timestamp_ptr,
  uint32_t*                              prev_timestamp_ptr)
{
  if ( sample_status == SNS_DDF_SUCCESS )
  {
    ind_sample_ptr->Quality = item_spec_ptr->quality;
    ind_sample_ptr->Flags   = 
      sns_rh_apply_calibration(ind_sample_ptr->Data,
                               item_spec_ptr->ddf_sensor_ptr,
                               item_spec_ptr->cal_sel);
  }
  else
  {
    ind_sample_ptr->Quality = SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01;
    ind_sample_ptr->Flags   = SNS_SMGR_ITEM_FLAG_INVALID_V01;
  }
  if ( idx_ptr->SampleCount == 0 )
  {
    ind_sample_ptr->TimeStampOffset = 0;
    idx_ptr->FirstSampleTimestamp   = *timestamp_ptr;
  }
  else
  {
    ind_sample_ptr->TimeStampOffset = *timestamp_ptr - *prev_timestamp_ptr;
  }
  *prev_timestamp_ptr = *timestamp_ptr;

  SNS_SMGR_REPORT_DBG2(
    LOW, "pack_sample - timestamp=%u offset=%d",
    *timestamp_ptr, ind_sample_ptr->TimeStampOffset);
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_generate_buffering_report

===========================================================================*/
/*!
  @brief This function generates buffering report indication messages.

  @detail

  @param[i]  rpt_spec_ptr  - the report spec
  @param[i]  end_timestamp - samples with timestamp newer than end_timestamp
                             should not be sent
  @return   number of samples sent
 */
/*=========================================================================*/
SMGR_STATIC uint32_t sns_rh_rpt_gen_generate_buffering_report(
  sns_rh_rpt_spec_s*  rpt_spec_ptr,
  uint32_t            end_timestamp,
  uint8_t             ind_type)
{
  uint8_t  i;
  sns_ddf_time_t last_sent = rpt_spec_ptr->ts_last_rpt_sent;
  sns_smgr_buffering_ind_msg_v01* ind_ptr;
  uint16_t ind_id = (rpt_spec_ptr->msg_header.svc_num == SNS_SMGR_SVC_ID_V01) ?
    SNS_SMGR_BUFFERING_IND_V01 : SNS_SMGR_EVENT_GATED_BUFFERING_IND_V02;
  /* -------------------------------------------------------------------- */

  SNS_SMGR_REPORT_DBG3(
    HIGH, "buffering_rpt - id=%u end_ts=%u ind_type=%u", 
    rpt_spec_ptr->rpt_id, end_timestamp, ind_type);

  ind_ptr = sns_rh_get_buffering_ind_buf();
  SNS_OS_MEMZERO(ind_ptr, sizeof(sns_smgr_buffering_ind_msg_v01));
  RH_FOR_EACH_REPORT_ITEM( rpt_spec_ptr, i )
  {
    sns_ddf_time_t previous_timestamp;
    sns_smgr_buffering_sample_index_s_v01* idx_ptr = NULL;
    sns_rh_rpt_item_s* item_spec_ptr = rpt_spec_ptr->item_list[i];
    sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_spec_ptr->ddf_sensor_ptr;
    const sns_smgr_sample_s *sample_ptr;

    if (ddf_sensor_ptr->sensor_ptr->sensor_state != SENSOR_STATE_READY)
    {
      continue;
    }
    if ( item_spec_ptr->effective_rate_hz == 0 )
    {
      continue;
    }

    SNS_SMGR_REPORT_DBG4(
      MED, "buffering_rpt - rpt_id=%u/%u ddf_sensor=%d rate=0x%x", 
      rpt_spec_ptr->msg_header.src_module, rpt_spec_ptr->rpt_id,
      SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
      item_spec_ptr->effective_rate_hz);
    SNS_SMGR_REPORT_DBG2(
      MED, "buffering_rpt - ts_last_sent=%u ts_last_processed=%u",
      item_spec_ptr->ts_last_sent, item_spec_ptr->last_processed_sample_timestamp);

    previous_timestamp = item_spec_ptr->ts_last_sent;
    idx_ptr = &ind_ptr->Indices[ind_ptr->Indices_len];
    idx_ptr->SensorId       = SMGR_SENSOR_ID(ddf_sensor_ptr->sensor_ptr);
    idx_ptr->DataType       = ddf_sensor_ptr->data_type;
    idx_ptr->FirstSampleIdx = ind_ptr->Samples_len;
    idx_ptr->FirstSampleTimestamp = 0;
    idx_ptr->SamplingRate   = item_spec_ptr->effective_rate_hz;

    sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
    sample_ptr = sns_smgr_depot_get_sample(&item_spec_ptr->depot_iter, 0);
    
    while ( (ind_ptr->Samples_len<ARR_SIZE(ind_ptr->Samples)) &&
            (sample_ptr != NULL) &&
            ((sample_ptr->status == SNS_DDF_SUCCESS) ||
             item_spec_ptr->samples_sent) &&
            TICK1_GEQ_TICK2(end_timestamp, sample_ptr->time_stamp) )
    {
      sns_smgr_buffering_sample_s_v01* ind_sample_ptr =
        &ind_ptr->Samples[ind_ptr->Samples_len];
      sns_ddf_time_t   timestamp;
      sns_ddf_status_e sample_status = 
        sns_rh_process_sample(item_spec_ptr, sample_ptr, &timestamp,
                              ind_sample_ptr->Data);
      SNS_SMGR_REPORT_DBG2(
        LOW, "buffering_rpt - ts=%u result=%u", 
        sample_ptr->time_stamp, sample_status);
      if ( (sample_status == SNS_DDF_SUCCESS) ||
           (sample_status == SNS_DDF_EINVALID_DATA) )
      {
        sns_rh_rpt_gen_pack_sample(idx_ptr, ind_sample_ptr, item_spec_ptr,
                                   sample_status, &timestamp, &previous_timestamp);
        idx_ptr->SampleCount++;
        ind_ptr->Samples_len++;
        item_spec_ptr->samples_sent = true;
        RH_UPDATE_INTERP_TIMESTAMP(&item_spec_ptr->interpolator_obj);
      }
      else
      {
        sample_ptr = sns_smgr_depot_get_sample(&item_spec_ptr->depot_iter, 1);
      }
    } /* while ( (ind_ptr->Samples_len<ARR_SIZE(ind_ptr->Samples)) &&
                 (sample_ptr != NULL) ) */

    item_spec_ptr->state = RH_RPT_ITEM_STATE_IDLE;
    item_spec_ptr->ts_last_sent = previous_timestamp;

    SNS_SMGR_REPORT_DBG3(
      LOW, "buffering_rpt - sensor=%d first=%u last=%u",
      idx_ptr->SensorId, idx_ptr->FirstSampleTimestamp, item_spec_ptr->ts_last_sent);

    if ( idx_ptr->SampleCount > 0 )
    {
      if ( ind_ptr->Indices_len == 0 )
      {
        last_sent = item_spec_ptr->last_processed_sample_timestamp;
      }
      else
      {
        last_sent = MIN(last_sent, item_spec_ptr->last_processed_sample_timestamp);
      }
      ind_ptr->Indices_len++;
    }
    else if ( item_spec_ptr->quality != SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01 )
    {
      SNS_SMGR_REPORT_DBG3(
        LOW, "buffering_rpt - quality=%u desired_ts=%u proc_ts=%u",
        item_spec_ptr->quality, item_spec_ptr->interpolator_obj.desired_timestamp,
        item_spec_ptr->last_processed_sample_timestamp);
    }
    sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
  }/* for each item in report spec */

  sns_profiling_log_qdss(SNS_RH_RPT_IND_START, 4, rpt_spec_ptr->rpt_id, 
                         rpt_spec_ptr->msg_header.connection_handle, 
                         ind_id, rpt_spec_ptr->num_items);

  if ( ind_ptr->Samples_len > 0 )
  {
    ind_ptr->ReportId      = rpt_spec_ptr->rpt_id;
    ind_ptr->IndType_valid = true;
    ind_ptr->IndType       = ind_type;

    if ( sns_rh_mr_send_indication(
           rpt_spec_ptr->msg_header.connection_handle,
           ind_ptr,
           ind_id,
           sizeof(sns_smgr_buffering_ind_msg_v01),
           false) ) /* don't free ind buf */
    {
      rpt_spec_ptr->ind_count++;
      rpt_spec_ptr->ts_last_rpt_sent = last_sent;
      if ( rpt_spec_ptr->ind_count == 1 )
      {
        SNS_SMGR_PRINTF4(
          HIGH, "send_buf_ind - id=%u/0x%x #samples=%u indices=%u",
          ind_ptr->ReportId, rpt_spec_ptr->msg_header.connection_handle,
          ind_ptr->Samples_len, ind_ptr->Indices_len);
      }
    }
    else
    {
      SNS_SMGR_PRINTF4(
         ERROR, "send_buf_ind - dropping id=%u/0x%x #samples=%u last_sent[0]=%u",
         ind_ptr->ReportId, rpt_spec_ptr->msg_header.connection_handle,
         ind_ptr->Samples_len, rpt_spec_ptr->item_list[0]->ts_last_sent);
      ind_ptr->Samples_len = 0;
    }
  }

  sns_profiling_log_qdss(SNS_RH_RPT_IND_END, 3, rpt_spec_ptr->rpt_id, 
                         ind_ptr->Indices_len, (ind_ptr->Samples_len > 0));

  return ind_ptr->Samples_len;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_generate_empty_buffering_report

===========================================================================*/
/*!
  @brief Sends an empty Buffering indication.

  @param[i]  rpt_ptr  - the report spec
  @param[i]  ind_type - indication type to use
 
  @return    none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_rpt_gen_generate_empty_buffering_report(
  sns_rh_rpt_spec_s*  rpt_ptr,
  uint8_t             ind_type)
{
  bool sent = false;
  uint16_t ind_id = (rpt_ptr->msg_header.svc_num == SNS_SMGR_SVC_ID_V01) ?
    SNS_SMGR_BUFFERING_IND_V01 : SNS_SMGR_EVENT_GATED_BUFFERING_IND_V02;
  sns_smgr_buffering_ind_msg_v01* ind_ptr = sns_rh_get_buffering_ind_buf();
  /* -------------------------------------------------------------------- */

  SNS_OS_MEMZERO(ind_ptr, sizeof(sns_smgr_buffering_ind_msg_v01));
  ind_ptr->ReportId      = rpt_ptr->rpt_id;
  ind_ptr->IndType_valid = true;
  ind_ptr->IndType       = ind_type;
  rpt_ptr->ind_count++;

  sent = sns_rh_mr_send_indication(
    rpt_ptr->msg_header.connection_handle,
    ind_ptr,
    ind_id,
    sizeof(sns_smgr_buffering_ind_msg_v01),
    false);
  SNS_SMGR_PRINTF3(
    HIGH, "send_empty_ind - rpt_id=%u/0x%x sent=%u", 
    rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, sent);
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_compute_num_avail_samples

===========================================================================*/
/*!
  @brief Computes number of samples available for given report since the
         previous report indication was sent.

  @detail Also returned are timestamps of oldest sample sent and latest sample available.

  @param[i]  rpt_spec_ptr            - the report for which to compute sample count
  @param[i]  oldest_last_sent_ts_ptr - destination for timestamp of oldest sample sent
  @param[i]  latest_sample_ts_ptr    - destination for timestamp of latest sample available

  @return   The computed number of samples available.
 */
/*=========================================================================*/
SMGR_STATIC uint32_t sns_rh_rpt_gen_compute_num_avail_samples(
  const sns_rh_rpt_spec_s*  rpt_spec_ptr,
  uint32_t*                 oldest_last_sent_ts_ptr,
  uint32_t*                 latest_sample_ts_ptr)
{
  uint32_t total_samples = 0;
  uint32_t max_samples = 0;
  uint8_t i;
  /* -------------------------------------------------------------------- */

  *oldest_last_sent_ts_ptr = 0xFFFFFFFF;
  *latest_sample_ts_ptr = 0;

  RH_FOR_EACH_REPORT_ITEM( rpt_spec_ptr, i )
  {
    sns_rh_rpt_item_s* item_ptr = rpt_spec_ptr->item_list[i];
    const sns_smgr_sample_s* sample_ptr = NULL;
    sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_ptr->ddf_sensor_ptr;

    if ( item_ptr->effective_rate_hz == 0 )
    {
      continue;
    }

    if ( item_ptr->ddf_sensor_ptr->bimg_depot_ptr == item_ptr->depot_ptr )
    {
      sns_rh_leave_island();
    }

    if ( item_ptr->ddf_sensor_ptr->uimg_depot_ptr != NULL &&
         item_ptr->ddf_sensor_ptr->uimg_depot_ptr != item_ptr->depot_ptr )
    {
      sns_smgr_copy_uimg_depot(item_ptr->ddf_sensor_ptr);
    }

    sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
    if ( sns_rh_rpt_gen_init_item_depot_iter(item_ptr) != NULL )
    {
      sample_ptr = sns_smgr_depot_get_latest_sample(item_ptr->depot_ptr);
    }
    sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);

    item_ptr->num_samples = 0;
    if ( sample_ptr == NULL )
    {
      continue;
    }
    if ( rpt_spec_ptr->periodic_like )
    {
      if ( sample_ptr->time_stamp != item_ptr->last_processed_sample_timestamp )
      {
        item_ptr->num_samples = 1;
      }
    }
    else if ( sns_smgr_ddf_sensor_is_event_sensor(item_ptr->ddf_sensor_ptr) )
    {
      item_ptr->num_samples = 1;
      sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
      while ( sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1) != NULL )
      {
        item_ptr->num_samples++;
      }
      sns_rh_rpt_gen_init_item_depot_iter(item_ptr);
      sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
    }
    else if ( TICK1_GTR_TICK2(sample_ptr->time_stamp, item_ptr->ts_last_sent) )
    {
      uint32_t delta_time = sample_ptr->time_stamp - item_ptr->ts_last_sent;
      uint32_t samp_intvl = item_ptr->sampling_interval;
      if ( SMGR_SENSOR_IS_SELF_SCHED(item_ptr->ddf_sensor_ptr->sensor_ptr) )
      {
        samp_intvl = samp_intvl * 95 / 100;
      }
      item_ptr->num_samples = delta_time / samp_intvl;
      if ( delta_time % samp_intvl )
      {
        item_ptr->num_samples++;
      }
    }

    total_samples += item_ptr->num_samples;
    if ( max_samples < item_ptr->num_samples )
    {
      max_samples = item_ptr->num_samples;
      *oldest_last_sent_ts_ptr = MIN(*oldest_last_sent_ts_ptr, item_ptr->ts_last_sent);
    }
    *latest_sample_ts_ptr = MAX(*latest_sample_ts_ptr, sample_ptr->time_stamp);
  }
  if ( total_samples > 0 )
  {
    SNS_SMGR_B2B_IND_DBG3(
      MED, "avail_sample_cnt=%d oldest=%u latest=%u",
      total_samples, *oldest_last_sent_ts_ptr, *latest_sample_ts_ptr);
  }
  else
  {
    SNS_SMGR_B2B_IND_DBG3(
      MED, "no samples for rpt_id=%u/0x%x rpt_tick=%u",
      rpt_spec_ptr->rpt_id, rpt_spec_ptr->msg_header.connection_handle,
      rpt_spec_ptr->rpt_tick);
  }
  return total_samples;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_schedule_next_report

===========================================================================*/
/*!
  @brief Schedules next report 
  @param [i]  rpt_ptr  - the report to schedule
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_rpt_gen_schedule_next_report(
  sns_rh_rpt_spec_s* rpt_ptr,
  bool               samples_sent)
{
  if ( rpt_ptr->event_sensors_only )
  {
    rpt_ptr->rpt_tick += rpt_ptr->rpt_interval;
    rpt_ptr->state = RH_RPT_STATE_ACTIVE;
  }
  else if ( samples_sent )
  {
    rpt_ptr->rpt_tick = rpt_ptr->ts_last_rpt_sent + rpt_ptr->rpt_interval;
    rpt_ptr->state = RH_RPT_STATE_ACTIVE;
  }
  else if ( rpt_ptr->state == RH_RPT_STATE_ACTIVE )
  {
    rpt_ptr->rpt_tick += rpt_ptr->min_sampling_interval;
  }
  else if ( rpt_ptr->state == RH_RPT_STATE_FLUSHING )
  {
    rpt_ptr->state = RH_RPT_STATE_ACTIVE;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_requeue_periodic_report

===========================================================================*/
/*!
  @brief Puts Periodic report back to ready queue if there are more
         samples to process.

  @param [io]  rpt_ptr  report pointer
 
  @return      none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_requeue_periodic_report(sns_rh_rpt_spec_s* rpt_ptr)
{
  uint8_t i;
  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    const sns_smgr_sample_s* sample_ptr =
      sns_smgr_depot_get_latest_sample(rpt_ptr->item_list[i]->depot_ptr);
    if ( sample_ptr != NULL &&
         sample_ptr->time_stamp !=
         rpt_ptr->item_list[i]->last_processed_sample_timestamp )
    {
      SNS_SMGR_REPORT_DBG3(
         LOW, "requeue_periodic_rpt - last_sent=%u last_proc=%u latest=%u",
         rpt_ptr->item_list[i]->ts_last_sent,
         rpt_ptr->item_list[i]->last_processed_sample_timestamp,
         sample_ptr ? sample_ptr->time_stamp : 0);
      break;
    }
  }
  if ( i >= rpt_ptr->num_items )
  {
    rpt_ptr->state = RH_RPT_STATE_ACTIVE;
  }
  else
  {
    /* add it back to end of ready report list */
    sns_rh_add_to_ready_list(rpt_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_generate_periodic_report

===========================================================================*/
/*!
  @brief This function generates periodic report indication message.

  @detail

  @param[i]  rpt_spec_ptr  report pointer
  @return   TRUE if report was generated
 */
/*=========================================================================*/
bool sns_rh_rpt_gen_generate_periodic_report(
  sns_rh_rpt_spec_s* rpt_ptr)
{
  bool                                  sent = false;
  sns_smgr_periodic_report_ind_msg_v01* ind_ptr = NULL;
  sns_smgr_data_item_s_v01*             item_ptr;
  uint8_t                               i;
  /* -------------------------------------------------------------------- */

  SNS_SMGR_REPORT_DBG3(
    MED, "periodic_rpt - id=%u/%u #items=%u",
    rpt_ptr->msg_header.src_module, rpt_ptr->rpt_id, rpt_ptr->num_items);

  ind_ptr = sns_rh_get_periodic_ind_buf();
  SNS_OS_MEMZERO(ind_ptr, sizeof(sns_smgr_periodic_report_ind_msg_v01));
  ind_ptr->ReportId = rpt_ptr->rpt_id;
  ind_ptr->status   = SNS_SMGR_REPORT_OK_V01;

  /* gather all items */
  item_ptr = ind_ptr->Item;
  RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
  {
    sns_rh_rpt_item_s* item_spec_ptr = rpt_ptr->item_list[i];
    sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_spec_ptr->ddf_sensor_ptr;
    const sns_smgr_sample_s* sample_ptr;

    item_spec_ptr->state = RH_RPT_ITEM_STATE_IDLE;
    SNS_SMGR_REPORT_DBG2(
      HIGH, "resulting_sample status=%d ts=%u",
      item_spec_ptr->resulting_sample.status,
      item_spec_ptr->resulting_sample.time_stamp);

    if ( item_spec_ptr->ddf_sensor_ptr->bimg_depot_ptr == item_spec_ptr->depot_ptr )
    {
      sns_rh_leave_island();
    }

    if ( !sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) )
    {
      sample_ptr = sns_rh_rpt_gen_init_item_depot_iter(item_spec_ptr);
      while ( (item_spec_ptr->state != RH_RPT_ITEM_STATE_DONE) && (sample_ptr != NULL) )
      {
        item_spec_ptr->resulting_sample.status =
          sns_rh_process_sample(item_spec_ptr, sample_ptr,
                                &item_spec_ptr->resulting_sample.time_stamp,
                                item_spec_ptr->resulting_sample.data);
        sample_ptr = sns_smgr_depot_get_sample(&item_spec_ptr->depot_iter, 1);
        SNS_SMGR_REPORT_DBG3(
          MED, "resulting_sample status=%d ts=%u sample_ts=%u",
          item_spec_ptr->resulting_sample.status,
          item_spec_ptr->resulting_sample.time_stamp,
          sample_ptr ? sample_ptr->time_stamp : 0);
      }
    }
    else
    {
      sample_ptr = sns_smgr_depot_get_latest_sample(item_spec_ptr->depot_ptr);
      if ( sample_ptr != NULL )
      {
        item_spec_ptr->resulting_sample.status =
          sns_rh_process_sample(item_spec_ptr, sample_ptr,
                                &item_spec_ptr->resulting_sample.time_stamp,
                                item_spec_ptr->resulting_sample.data);
      }
    }

    if ( (item_spec_ptr->state == RH_RPT_ITEM_STATE_DONE) &&
         ((item_spec_ptr->resulting_sample.status == SNS_DDF_SUCCESS) ||
          /* invalid samples only OK to be sent midstream */
          ((item_spec_ptr->resulting_sample.status == SNS_DDF_EINVALID_DATA) &&
           item_spec_ptr->samples_sent)) )
    {
      /* Calculate current reporting rate: Only for the first item */
      if ( 0 == ind_ptr->Item_len++ )
      {
        /* If the effective rate is less than 1 Hz, output the current rate as
           the period in milliseconds. */
        if ( item_spec_ptr->effective_rate_hz < FX_ONE_Q16 )
        {
          // If effective_rate_hz is 0x3E8 or less, this will overflow the 16-bit integer
          uint32_t period_ms = FX_FLTTOFIX_Q16(1000) / item_spec_ptr->effective_rate_hz;

          // If an overflow of the 16-bit CurrentRate happens, use UINT16_MAX instead
          ind_ptr->CurrentRate = (UINT16_MAX < period_ms) ?
              UINT16_MAX : period_ms;
        }
        else
        {
          ind_ptr->CurrentRate = 
            (uint16_t) FX_FIXTOFLT_Q16_SP(item_spec_ptr->effective_rate_hz);
        }
      }
      SNS_OS_MEMCOPY(item_ptr->ItemData,
                     item_spec_ptr->resulting_sample.data,
                     sizeof(item_ptr->ItemData));
      if ( item_spec_ptr->resulting_sample.status != SNS_DDF_SUCCESS )
      {
        item_ptr->ItemFlags   = SNS_SMGR_ITEM_FLAG_INVALID_V01;
        item_ptr->ItemQuality = SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01;
        SNS_SMGR_REPORT_DBG1(
          ERROR, "periodic_rpt - ts=%u", item_spec_ptr->resulting_sample.time_stamp);
      }
      else
      {
        item_ptr->ItemQuality = item_spec_ptr->quality;
        item_ptr->ItemFlags  |=
          sns_rh_apply_calibration(item_ptr->ItemData,
                                 item_spec_ptr->ddf_sensor_ptr,
                                 item_spec_ptr->cal_sel);
      }
      item_spec_ptr->samples_sent = true;
      RH_UPDATE_INTERP_TIMESTAMP(&item_spec_ptr->interpolator_obj);

      item_ptr->SensorId = SMGR_SENSOR_ID(ddf_sensor_ptr->sensor_ptr);
      item_ptr->DataType = ddf_sensor_ptr->data_type;
      item_ptr->ItemSensitivity = item_spec_ptr->sensitivity;
      item_ptr->TimeStamp   = item_spec_ptr->resulting_sample.time_stamp;

      SNS_SMGR_REPORT_DBG2(
        LOW, "periodic_rpt - sensor=%d ts=%u",
        item_ptr->SensorId, (unsigned)item_ptr->TimeStamp);

      {
        if ( TICK1_GEQ_TICK2(item_spec_ptr->ts_last_sent,
                             item_spec_ptr->resulting_sample.time_stamp) )
        {
          SNS_SMGR_PRINTF3(
            FATAL, "periodic_rpt - iter_idx=%u first=%u last=%u",
            item_spec_ptr->depot_iter.idx, 
            item_spec_ptr->depot_ptr->first_idx,
            item_spec_ptr->depot_ptr->last_idx);
          SNS_SMGR_PRINTF3(
            FATAL, "periodic_rpt - last=%u proc=%u resulting_sample=%u",
            item_spec_ptr->ts_last_sent, 
            item_spec_ptr->last_processed_sample_timestamp,
            item_spec_ptr->resulting_sample.time_stamp);
        }
      }

      item_spec_ptr->ts_last_sent = item_spec_ptr->resulting_sample.time_stamp;
      item_ptr++;       /* next item */

      if ( sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) ||
           item_spec_ptr->quality == SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01 )
      {
        item_spec_ptr->state = RH_RPT_ITEM_STATE_IDLE;
      }
    }

    if ( item_spec_ptr->ddf_sensor_ptr->bimg_depot_ptr == item_spec_ptr->depot_ptr )
    {
      sns_rh_enter_island();
    }
  }/* for each item in report */

  sns_profiling_log_qdss(SNS_RH_RPT_IND_START, 4, rpt_ptr->rpt_id, 
                         rpt_ptr->msg_header.connection_handle, 
                         SNS_SMGR_REPORT_IND_V01, rpt_ptr->num_items);

  if ( ind_ptr->Item_len > 0 )
  {
    sent = sns_rh_mr_send_indication(
             rpt_ptr->msg_header.connection_handle,
             ind_ptr,
             SNS_SMGR_REPORT_IND_V01,
             sizeof(sns_smgr_periodic_report_ind_msg_v01),
             false); /* don't free ind buf */
  }

  sns_profiling_log_qdss(SNS_RH_RPT_IND_END, 3, rpt_ptr->rpt_id, 
                         ind_ptr->Item_len, sent);

  if ( sent )
  {
    rpt_ptr->ind_count++;
    rpt_ptr->ts_last_rpt_sent = sns_em_get_timestamp();
    if ( rpt_ptr->ind_count == 1 || rpt_ptr->proc_type != SNS_PROC_APPS_V01 )
    {
      SNS_SMGR_PRINTF4(
        HIGH, "send_per_ind - id=%u/0x%x #items=%u #ind=%u",
        ind_ptr->ReportId, rpt_ptr->msg_header.connection_handle, 
        ind_ptr->Item_len, rpt_ptr->ind_count);
    }
    sns_rh_requeue_periodic_report(rpt_ptr);
  }
  else if ( ind_ptr->Item_len != 0 )
  {
    SNS_SMGR_PRINTF3(
      ERROR, "send_per_ind - id=%u/0x%x last_sent[0]=%u",
      ind_ptr->ReportId, rpt_ptr->msg_header.connection_handle, 
      rpt_ptr->item_list[0]->ts_last_sent);
  }
  else
  {
    SNS_SMGR_REPORT_DBG3(
      LOW, "periodic_rpt - no ready items for rpt %u/0x%x last_proc[0]=%u",
      rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
      rpt_ptr->item_list[0]->last_processed_sample_timestamp);
  }
  return sent;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_send_buffering_indications

===========================================================================*/
/*!
  @brief Determines number of indications required to send all available samples
         for the given report, generates and sends them.

  @param[i]  rpt_spec_ptr  - the report spec

  @return   TRUE if one or more indications were sent
 */
/*=========================================================================*/
bool sns_rh_rpt_gen_send_buffering_indications(
  sns_rh_rpt_spec_s* rpt_spec_ptr)
{
  uint8_t i, num_inds = 0;
  uint32_t estimated_num_samples;
  uint32_t num_samples_sent = 0;
  uint32_t total_num_samples_sent = 0;
  uint32_t oldest_last_sent_ts, latest_sample_ts;
  bool     samples_sent = false;
  rh_rpt_state_e old_state = rpt_spec_ptr->state;

  /* -------------------------------------------------------------------- */

  sns_profiling_log_qdss(SNS_RH_BUF_TRAIN_START, 3, rpt_spec_ptr->rpt_id, 
                         rpt_spec_ptr->msg_header.connection_handle, 
                         rpt_spec_ptr->num_items);

  SNS_SMGR_B2B_IND_DBG4(
    HIGH, "buff_rpt_prep - rpt_id=%u/0x%x rate=0x%x items=%d",
    rpt_spec_ptr->rpt_id, rpt_spec_ptr->msg_header.connection_handle, 
    rpt_spec_ptr->q16_rpt_rate, rpt_spec_ptr->num_items);

  estimated_num_samples = 
    sns_rh_rpt_gen_compute_num_avail_samples(rpt_spec_ptr,
                                             &oldest_last_sent_ts,
                                             &latest_sample_ts);
  if ( estimated_num_samples > 0 )
  {
    uint32_t time_span, time_per_ind, end_ts;

    num_inds = (estimated_num_samples / SNS_SMGR_BUFFERING_REPORT_MAX_SAMPLES_V01);
    if ( estimated_num_samples % SNS_SMGR_BUFFERING_REPORT_MAX_SAMPLES_V01 )
    {
      num_inds++;
    }

    /* If any items in the report have a sampling rate less than 1 Hz, set the
       number of indications to the number of samples. This will cause the SMGR
       to send all the samples as back-to-back (b2b) indications with each
       indication carrying just 1 sample. This ensures that the TimeStampOffset
       field in the indication message does not overflow (overflow happens
       when the sampling rate is 0.5 Hz or less).
       TODO: Send only back-to-back indications for the samples that will cause
       an overflow in the TimeStampOffset field. All other samples can be
       grouped in batches of 100 samples and sent together. */
    RH_FOR_EACH_REPORT_ITEM( rpt_spec_ptr, i )
    {
      sns_rh_rpt_item_s* item_ptr = rpt_spec_ptr->item_list[i];

      if ( item_ptr->effective_rate_hz > 0 && item_ptr->effective_rate_hz < FX_ONE_Q16 )
      {
        num_inds = estimated_num_samples;
        SNS_SMGR_PRINTF1(
          HIGH, "buff_rpt_prep - subHz detected, sending %u indications", num_inds);
        break;
      }
    }

    time_span = latest_sample_ts - oldest_last_sent_ts;
    time_per_ind = time_span / num_inds;

    SNS_SMGR_B2B_IND_DBG3(
      MED, "buff_rpt_prep - #ind=%d time_span=%d time/ind=%d",
      num_inds, time_span, time_per_ind);

    for ( i = 0, end_ts = oldest_last_sent_ts + time_per_ind;
          i < num_inds; i++, end_ts += time_per_ind )
    {
      uint8_t ind_type;
      if ( i == num_inds-1 )
      {
        if ( total_num_samples_sent == 0 )
        {
          ind_type = SNS_BATCH_ONLY_IND_V01;
        }
        else
        {
          ind_type = SNS_BATCH_LAST_IND_V01;
        }
        end_ts = latest_sample_ts;
      }
      else
      {
        if ( total_num_samples_sent == 0 )
        {
          ind_type = SNS_BATCH_FIRST_IND_V01;
        }
        else
        {
          ind_type = SNS_BATCH_INTERMEDIATE_IND_V01;
        }
      }
      num_samples_sent = 
        sns_rh_rpt_gen_generate_buffering_report(rpt_spec_ptr, end_ts, ind_type);
      total_num_samples_sent += num_samples_sent;

      if ( num_inds > 1 )
      {
        SNS_SMGR_B2B_IND_DBG3(
          LOW, "buff_inds - end_ts=%u #sent=%u ind_type=%u", 
          end_ts, num_samples_sent, ind_type);
      }
    }

    if ( num_samples_sent == 0 && total_num_samples_sent != 0 && num_inds > 1 )
    {
      /* last attempt failed, client still needs to receive LAST_IND */
      sns_rh_rpt_gen_generate_empty_buffering_report(
        rpt_spec_ptr, SNS_BATCH_LAST_IND_V01);
    }

    SNS_SMGR_B2B_IND_DBG2(
      MED, "buff_inds - %d samples, %d inds", total_num_samples_sent, num_inds);
  }

  sns_profiling_log_qdss(SNS_RH_BUF_TRAIN_END, 3, num_inds, total_num_samples_sent,
                         rpt_spec_ptr->rpt_tick);

  samples_sent = (total_num_samples_sent > 0);
  sns_rh_rpt_gen_schedule_next_report(rpt_spec_ptr, samples_sent);
  sns_rh_enter_island();

  /* debug logging */
  if ( samples_sent && 
       ((rpt_spec_ptr->proc_type != SNS_PROC_APPS_V01 && 
         rpt_spec_ptr->rpt_interval >= SNS_RH_100MS_IN_TICK) ||
        (old_state == RH_RPT_STATE_ACTIVE &&
         rpt_spec_ptr->rpt_interval >= SNS_RH_1000MS_IN_TICK)) )
  {
    SNS_SMGR_PRINTF4(
      HIGH, "buff_train - rpt_id=%u/0x%x #samples=%u #ind=%u",
      rpt_spec_ptr->rpt_id, rpt_spec_ptr->msg_header.connection_handle, 
      total_num_samples_sent, num_inds);
    SNS_SMGR_PRINTF3(
      HIGH, "buff_train - last_sent[0]=%u rpt(last/next)=%u/%u",
      rpt_spec_ptr->item_list[0]->ts_last_sent, rpt_spec_ptr->ts_last_rpt_sent,
      rpt_spec_ptr->rpt_tick);
  }

  return samples_sent;
}

