/*=============================================================================
  @file sns_rh_rpt_gen.c

  Implementation of Report Generation functions

******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_rpt_gen.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-10-06  jc   Grab mutex before accessing depot
  2014-09-25  pn   Uses depot selected for report item
  2014-06-16  pn   Removed references to unused circular buffer
  2014-04-29  pn   Refactored to support microImage
  2014-04-23  pn   Initial version

============================================================================*/

#define __SNS_MODULE__ SNS_RH

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_memmgr.h"
#include "sns_rh.h"
#include "sns_rh_main.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_mr.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_sample_proc_uimg.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_QUERY_DEBUG
#ifdef SNS_SMGR_QUERY_DEBUG
#define SNS_SMGR_QUERY_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_QUERY_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_QUERY_DBG3 SNS_SMGR_PRINTF3
#else
#define SNS_SMGR_QUERY_DBG1(level,msg,p1)
#define SNS_SMGR_QUERY_DBG2(level,msg,p1,p2)
#define SNS_SMGR_QUERY_DBG3(level,msg,p1,p2,p3)
#endif

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

  FUNCTION:   sns_rh_rpt_gen_pack_query_sample

===========================================================================*/
/*!
  @brief Packs the given sample into indication message.

  @param[i]  query_ptr          - pointer to the query spec
  @param[i]  ind_ptr            - pointer to the query indication
  @param[i]  timestamp_ptr      - pointer to the sample timestamp
  @param[io] prev_timestamp_ptr - pointer to the previous timestamp

  @return   None
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_rpt_gen_pack_query_sample(
  sns_rh_query_s*                       query_ptr,
  sns_smgr_buffering_query_ind_msg_v01* ind_ptr,
  const uint32_t*                       timestamp_ptr,
  uint32_t*                             prev_timestamp_ptr,
  uint8_t                               quality)
{
  sns_rh_rpt_item_s*                item_ptr       = query_ptr->item_ptr;
  sns_smgr_buffering_sample_s_v01*  ind_sample_ptr =
    &ind_ptr->Samples[ind_ptr->Samples_len];
  /* -------------------------------------------------------------------- */

  ind_sample_ptr->Flags = sns_rh_apply_calibration(ind_sample_ptr->Data,
                                                   item_ptr->ddf_sensor_ptr,
                                                   item_ptr->cal_sel);

  ind_sample_ptr->Quality = quality;

  if ( ind_ptr->Samples_len++ == 0 )
  {
    ind_ptr->FirstSampleTimestamp   = *timestamp_ptr;
    ind_sample_ptr->TimeStampOffset = 0;
  }
  else
  {
    ind_sample_ptr->TimeStampOffset = *timestamp_ptr - *prev_timestamp_ptr;
  }
  *prev_timestamp_ptr = *timestamp_ptr;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_send_empty_query_indication

===========================================================================*/
/*!
  @brief Generates one Query indication message with no samples.

  @param[i] query_ptr

  @return TRUE if indication sent; FALSE otherwise
*/
/*=========================================================================*/
bool sns_rh_rpt_gen_send_empty_query_indication(
  const sns_rh_query_s* query_ptr)
{
  sns_smgr_buffering_query_ind_msg_v01* ind_ptr = sns_rh_get_query_ind_buf();
  /* -------------------------------------------------------------------- */

  SNS_OS_MEMZERO(ind_ptr, sizeof(sns_smgr_buffering_query_ind_msg_v01));
  ind_ptr->QueryId              = query_ptr->query_id;
  ind_ptr->FirstSampleTimestamp = 0;
  ind_ptr->SamplingRate         = 0;
  ind_ptr->Samples_len          = 0;
  SNS_SMGR_PRINTF1(HIGH, "send_empty_query_ind - id=0x%x", ind_ptr->QueryId);
  sns_rh_mr_send_indication(
    query_ptr->item_ptr->parent_report_ptr->msg_header.connection_handle,
    ind_ptr, SNS_SMGR_BUFFERING_QUERY_IND_V01,
    sizeof(sns_smgr_buffering_query_ind_msg_v01),
    false); /* don't free ind buf */
  return true;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_generate_query_indication

===========================================================================*/
/*!
  @brief Generates one Query indication message.

  @param[i] query_ptr

  @return
    true if indication sent, false otherwise

*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_rpt_gen_generate_query_indication(
  sns_rh_query_s* query_ptr)
{
  sns_smgr_buffering_query_ind_msg_v01* ind_ptr = sns_rh_get_query_ind_buf();
  sns_rh_interpolator_obj_s t0_t1_interp_obj;
  uint32_t                  previous_timestamp;
  const sns_smgr_sample_s*  sample_ptr;
  sns_rh_rpt_item_s*        item_ptr = query_ptr->item_ptr;
  /* -------------------------------------------------------------------- */

  if ( item_ptr == NULL )
  {
    return false;
  }

  sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 0);

  SNS_OS_MEMZERO(ind_ptr, sizeof(sns_smgr_buffering_query_ind_msg_v01));
  ind_ptr->QueryId      = query_ptr->query_id;
  ind_ptr->SamplingRate = item_ptr->effective_rate_hz;

  SNS_OS_MEMZERO(&t0_t1_interp_obj, sizeof(sns_rh_interpolator_obj_s));
  t0_t1_interp_obj.desired_timestamp = query_ptr->T0;
  item_ptr->interpolator_obj.desired_timestamp = query_ptr->T0;
  item_ptr->interpolator_obj.sample1_ptr = NULL;
  item_ptr->interpolator_obj.sample2_ptr = NULL;
  item_ptr->last_processed_sample_timestamp = 0;

  /* skip invalid samples */
  while ( (sample_ptr != NULL) && (sample_ptr->status != SNS_DDF_SUCCESS) )
  {
    sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1);
  }

  if ( sample_ptr != NULL )
  {
    /* feeds interpolator with first valid sample */
    sns_rh_interpolator_update(&t0_t1_interp_obj, sample_ptr);
  }

  /* skip old samples */
  while ( (sample_ptr != NULL) && 
          TICK1_GTR_TICK2(query_ptr->T0, sample_ptr->time_stamp) )
  {
    sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1);
    sns_rh_interpolator_update(&t0_t1_interp_obj, sample_ptr);
  }

  if ( (t0_t1_interp_obj.sample1_ptr != NULL) &&
       (sample_ptr != NULL) && (query_ptr->T0 != sample_ptr->time_stamp))
  {
    SNS_SMGR_QUERY_DBG3(
      HIGH, "query_ind - s1=%u T0=%u s2=%u",
      t0_t1_interp_obj.sample1_ptr->time_stamp, query_ptr->T0,
      t0_t1_interp_obj.sample2_ptr->time_stamp);
    sns_rh_interpolate(
      &t0_t1_interp_obj, ind_ptr->Samples[ind_ptr->Samples_len].Data);
    sns_rh_rpt_gen_pack_query_sample(
      query_ptr, ind_ptr, &query_ptr->T0, &previous_timestamp,
      SNS_SMGR_ITEM_QUALITY_INTERPOLATED_V01);

    /* compute next desired timestamp in case it's needed*/
    RH_UPDATE_INTERP_TIMESTAMP(&item_ptr->interpolator_obj);
  }

  /* prepares to interpolate for T1*/
  t0_t1_interp_obj.desired_timestamp = query_ptr->T1;
  sns_rh_interpolator_update(&t0_t1_interp_obj, sample_ptr);

  if ( item_ptr->quality != SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01 )
  {
    SNS_SMGR_QUERY_DBG3(
      MED, "query_ind - quality=%d interp_intvl=%d desired_ts=%u",
      item_ptr->quality, item_ptr->interpolator_obj.interval_ticks,
      item_ptr->interpolator_obj.desired_timestamp);
  }

  while ( (sample_ptr != NULL) &&
          (ind_ptr->Samples_len < ARR_SIZE(ind_ptr->Samples)) &&
          TICK1_GEQ_TICK2(query_ptr->T1, sample_ptr->time_stamp) )
  {
    sns_ddf_status_e status;
    sns_ddf_time_t   timestamp;

    status = sns_rh_process_sample(item_ptr, sample_ptr, &timestamp,
                                   ind_ptr->Samples[ind_ptr->Samples_len].Data);
    if ( status == SNS_DDF_SUCCESS )
    {
      SNS_SMGR_QUERY_DBG1(MED, "query_ind - ts=%u", timestamp);
      sns_rh_rpt_gen_pack_query_sample(
        query_ptr, ind_ptr, &timestamp, &previous_timestamp, item_ptr->quality);

      /* prepare for next sample */
      RH_UPDATE_INTERP_TIMESTAMP(&item_ptr->interpolator_obj);
    }
    else if ( status != SNS_DDF_PENDING )
    {
      SNS_SMGR_QUERY_DBG2(
        ERROR, "query_ind - ts=%u status=%d", sample_ptr->time_stamp, status);
    }
    if ( ((item_ptr->quality != SNS_SMGR_ITEM_QUALITY_INTERPOLATED_V01) &&
          (item_ptr->quality != SNS_SMGR_ITEM_QUALITY_INTERPOLATED_FILTERED_V01) &&
          (query_ptr->T1 != sample_ptr->time_stamp)) ||
         (status != SNS_DDF_SUCCESS) )
    {
      sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1);
      sns_rh_interpolator_update(&t0_t1_interp_obj, sample_ptr);
    }
  }
  if ( (sample_ptr != NULL) &&
       (ind_ptr->Samples_len < ARR_SIZE(ind_ptr->Samples)) &&
       TICK1_GTR_TICK2(sample_ptr->time_stamp, query_ptr->T1) )
  {
    SNS_SMGR_QUERY_DBG3(
      HIGH, "query_ind - s1=%u T1=%u s2=%u",
      t0_t1_interp_obj.sample1_ptr->time_stamp, query_ptr->T1,
      t0_t1_interp_obj.sample2_ptr->time_stamp);
    sns_rh_interpolate(
      &t0_t1_interp_obj, ind_ptr->Samples[ind_ptr->Samples_len].Data);
    sns_rh_rpt_gen_pack_query_sample(
      query_ptr, ind_ptr, &query_ptr->T1, &previous_timestamp,
      SNS_SMGR_ITEM_QUALITY_INTERPOLATED_V01);
  }
  SNS_SMGR_PRINTF2(HIGH, "send_query_ind - ID=0x%x samples=%u",
                   ind_ptr->QueryId, (unsigned)ind_ptr->Samples_len);
  sns_rh_mr_send_indication(
    item_ptr->parent_report_ptr->msg_header.connection_handle,
    ind_ptr, SNS_SMGR_BUFFERING_QUERY_IND_V01,
    sizeof(sns_smgr_buffering_query_ind_msg_v01),
    false); /* don't free ind buf */
  item_ptr->parent_report_ptr->ind_count++;
  return TRUE;
}

/*===========================================================================

  FUNCTION:   sns_smgr_send_query_indication

===========================================================================*/
/*!
  @brief Generates one Query indication message.

  @param[i] NONE

  @return
   NONE

*/
/*=========================================================================*/
bool sns_rh_rpt_gen_send_query_indication(sns_rh_rpt_spec_s* rpt_ptr)
{
  bool sent = false;
  uint8_t i;
  /* -------------------------------------------------------------------- */

  for ( i=0; i<rpt_ptr->num_items; i++ )
  {
    sns_rh_query_s* query_ptr = rpt_ptr->item_list[i]->query_ptr;
    if ( query_ptr != NULL )
    {
      sns_ddf_time_t first_ts = 0, last_ts = 0;
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr = item_ptr->ddf_sensor_ptr;

      if ( ddf_sensor_ptr->depot_mutex_ptr != NULL )
      {
        uint8_t never_err;
        sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, &never_err);
      }

      const sns_smgr_sample_s* sample_ptr =
        sns_smgr_depot_init_iter(item_ptr->depot_ptr,
                                 query_ptr->T0, &item_ptr->depot_iter);
      if (sample_ptr != NULL)
      {
        /* iterate to previous sample so T0 would be included in indication */
        sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, -1);
      }
      while ( (sample_ptr != NULL) && (sample_ptr->status != SNS_DDF_SUCCESS) )
      {
        /* skip invalid samples */
        sample_ptr = sns_smgr_depot_get_sample(&item_ptr->depot_iter, 1);
      }
      if ( ddf_sensor_ptr->depot_mutex_ptr != NULL )
      {
        sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
      }

      SNS_SMGR_QUERY_DBG3(
         MED, "send_query_ind - T0=%u iter_sample_ts=%u status=%d",
         query_ptr->T0, sample_ptr?sample_ptr->time_stamp:0,
         sample_ptr?sample_ptr->status:-1);

      if ( sample_ptr != NULL )
      {
        first_ts = sample_ptr->time_stamp;
      }
      if ( first_ts != 0 )
      {
        if ( NULL != (sample_ptr = sns_smgr_depot_get_latest_sample(
                                     item_ptr->depot_ptr)) )
        {
          last_ts = sample_ptr->time_stamp;
        }
        if ( TICK1_GTR_TICK2(first_ts, query_ptr->T1) )
        {
          SNS_SMGR_PRINTF2(
            LOW, "send_query_ind - no valid samples between %u and %u",
            (unsigned)query_ptr->T0, (unsigned)query_ptr->T1);
          /* the requested time period is in the past; no samples to send */
          sent = sns_rh_rpt_gen_send_empty_query_indication(query_ptr);
        }
        else if ( TICK1_GEQ_TICK2(last_ts, query_ptr->T1) )
        {
          /* some or all of available samples fall within requested time period */
          sent = sns_rh_rpt_gen_generate_query_indication(query_ptr);
        }
        /* else, not time to send indication for this Query */
      }
      else if ( TICK1_GTR_TICK2(sns_em_get_timestamp(), query_ptr->T1) )
      {
        SNS_SMGR_PRINTF0(LOW, "send_query_ind - no valid samples available");
        /* the requested time period is in the past; no samples to send */
        sent = sns_rh_rpt_gen_send_empty_query_indication(query_ptr);
      }
      /* else, not time to send indication for this Query */

      if ( sent )
      {
        rpt_ptr->item_list[i]->query_ptr = query_ptr->next_query_ptr;
        SNS_OS_FREE(query_ptr);
      }
    }
  }

  return sent;
}

