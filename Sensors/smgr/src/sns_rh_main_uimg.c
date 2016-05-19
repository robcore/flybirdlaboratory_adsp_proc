/*=============================================================================
  @file sns_rh_main_uimg.c

  This file implements portion of Request Handler task that executes in microImage.

*******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_main_uimg.c#10 $ */
/* $DateTime: 2015/05/08 10:28:56 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-05-08  pn   Restarts report timer after report flushing is triggered by AP resume
  2015-04-21  pn   Changed report flushing to AP
  2015-02-26  vy    Moved uImage logging out
  2015-02-03  pn   Made sns_rh_get_latest_sample_timestamp() global
  2015-01-29  pn   Must not update queue while using SMGR_FOR_EACH_Q_ITEM()
  2015-01-23  pn   Fixed problem of no response to report replacement request
  2015-01-13  pn   Correctly handles pending reports
  2014-12-12  sd   relaxed report ready check
  2014-12-03  pn   Moved sns_rh_delete_rpt_after_flush() to bigImage
  2014-11-24  pn   - Only flushes reports to AP when sending Buffering indications
                   - Added handler for SNS_RH_FIFO_SAMPLES_SIG
  2014-11-11  dk   Added support for handling SNS_RH_LOGPKT_DROP_SIG
  2014-11-04  pn   ts_last_sent of Periodic reports being setup does not get updated
  2014-10-28  jms  Rpt sending with effective_rate_hz=0 fix
  2014-10-28  pn   Periodic report scheduling improvements
  2014-10-22  pn   Buffering report scheduling improvements
  2014-10-10  pn   Only synchronizes reports to AP clients if waking up AP
  2014-10-02  pn   Added report synchronization
  2014-09-25  pn   Uses depot selected for report item
  2014-09-23  pn   Added QDSS logging
  2014-09-16  pn   Makes sure not to send indications to suspended AP
  2014-09-08  pn   Maintains external report rate
  2014-09-04  pn   Changed how the next indication is scheduled
  2014-09-03  jhh  Added client name on pm client
  2014-09-02  rt   Added signal for UPDATE_REPORT_TIMER
  2014-08-05  pn   Added handlers for ODR_CHANGED and FIFO_FLUSHED signals
  2014-07-31  pn   Removed POWER_INTERFACE featurization
  2014-07-27  vy   Added vote for NoClient mode
  2014-07-25  pn   Makes sure report is set up completely before adding it to ready list
  2014-07-21  pn   Added unsignal_me()
  2014-06-16  pn   Unshared sns_rh_uimg
  2014-06-05  vy   Further refactored to support uImage
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Initial version
============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_osa.h"
#include "sns_rh_main.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_sol.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_util.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define __SNS_MODULE__ SNS_RH

#define SNS_RH_FIFO_READY(ip) \
  (SMGR_SENSOR_FIFO_IS_ENABLE((ip)->ddf_sensor_ptr->sensor_ptr) && \
   (ip)->ddf_sensor_ptr->sensor_ptr->sensor_state == SENSOR_STATE_READY)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef union
{
  sns_smgr_periodic_report_ind_msg_v01  periodic;
  sns_smgr_buffering_ind_msg_v01        buffering;
  sns_smgr_buffering_query_ind_msg_v01  query;
} sns_rh_report_indication_u;

typedef struct
{
  OS_STK                          task_stack[SNS_MODULE_STK_SIZE_DSPS_RH];

  OS_FLAG_GRP*                    sig_grp;
  OS_FLAGS                        sig_mask;

  sns_em_timer_obj_t              report_timer;

  sns_pm_handle_t                 pm_client_handle;

  /* queue for reports built from report requests messages */
  sns_q_s                         report_queue;

  /* linked list of reports ready to be sent */
  sns_rh_rpt_spec_s*              ready_report_ptr;
  sns_rh_report_indication_u      report_ind;

  bool                            app_is_awake;
  uint32_t                        app_state_toggle_count;

} sns_rh_uimg_s;

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_rh_uimg_s sns_rh_uimg;

/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * External Function Declarations
 * -------------------------------------------------------------------------*/
extern void sns_sam_ap_state_change_cb(bool suspend_state);

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_flush_reports_to_same_processor

===========================================================================*/
/*!
  @brief Send all available samples to clients on the given processor.

  @detail
  @param[i] proc         - processor type
  @param[i] piggybacking - true if sending report opportunistically
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_flush_reports_to_same_processor(
  sns_proc_type_e_v01 proc,
  bool                piggybacking )
{
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( (rpt_ptr->proc_type == proc) &&
         (rpt_ptr->state == RH_RPT_STATE_ACTIVE) && (rpt_ptr->q16_rpt_rate != 0) )
    {
      if ( (rpt_ptr->rpt_tick != 0) || 
           (!piggybacking && 
            (rpt_ptr->periodic_like || SNS_RH_REPORT_IS_PERIODIC(rpt_ptr))) )
      {
        if ( sns_rh_add_to_ready_list(rpt_ptr) )
        {
          rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        }
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_flush_reports_to_ap

===========================================================================*/
/*!
  @details If the given report belongs to a client on AP, (and if AP is to be
           woken up,) flushes reports belonging to other AP clients.

  @param  rpt_ptr - the report being sent
  @return none

*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_flush_reports_to_ap(const sns_rh_rpt_spec_s* rpt_ptr)
{
  if ( rpt_ptr->proc_type == SNS_PROC_APPS_V01 /* && !sns_rh_uimg.app_is_awake */ )
  {
    sns_rh_flush_reports_to_same_processor(SNS_PROC_APPS_V01, true);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_send_report_indications

===========================================================================*/
/*!
  @brief Generates indications for all ready reports.

  @param  none
 
  @return true if indications were sent
*/
/*=========================================================================*/
SMGR_STATIC bool sns_rh_send_report_indications(void)
{
  bool ind_sent = false;
  sns_rh_rpt_spec_s* rpt_spec_ptr;
  /* -------------------------------------------------------------------- */

  while ( (rpt_spec_ptr = sns_rh_uimg.ready_report_ptr) != NULL )
  {
    bool sent = false;
    bool sam_alerted = false;

    sns_rh_uimg.ready_report_ptr = rpt_spec_ptr->next_ready_report_ptr;
    rpt_spec_ptr->next_ready_report_ptr = NULL;

    if ( SNS_RH_REPORT_IS_PERIODIC(rpt_spec_ptr) )
    {
      sent = sns_rh_rpt_gen_generate_periodic_report(rpt_spec_ptr);
    }
    else if ( rpt_spec_ptr->q16_rpt_rate != 0 )
    {
      sent = sns_rh_rpt_gen_send_buffering_indications(rpt_spec_ptr);
    }
    else
    {
      sns_rh_leave_island();
      sent = sns_rh_rpt_gen_send_query_indication(rpt_spec_ptr);
      sns_rh_enter_island();
    }

    if ( !sam_alerted && sent &&
         rpt_spec_ptr->proc_type == SNS_PROC_APPS_V01 &&
         !sns_rh_uimg.app_is_awake )
    {
      /* notifies SAM that AP will be woken up */
      sns_sam_ap_state_change_cb(false);
      sam_alerted = true;
    }
    if ( sent )
    {
      ind_sent = true;
    }
  }
  return ind_sent;
}

/*===========================================================================

  FUNCTION:   sns_rh_get_latest_sample_timestamp

===========================================================================*/
/*!
  @brief Get timestamp of the latest available sample for the given report item

  @param [i] item_ptr - the report item of interest
  @param [o] ts_ptr   - destination for timestamp

  @return
  SNS_SUCCESS if depot is not empty and timestamp copied
  SNS_ERR_FAILED if no samples found

*/
/*=========================================================================*/
sns_err_code_e sns_rh_get_latest_sample_timestamp(
  const sns_rh_rpt_item_s* item_ptr,
  sns_ddf_time_t*          ts_ptr)
{
  sns_err_code_e result = SNS_ERR_FAILED;
  const sns_smgr_sample_s* sample_ptr;

  if ( item_ptr->ddf_sensor_ptr->uimg_depot_ptr != NULL )
  {
    sample_ptr =
      sns_smgr_depot_get_latest_sample(item_ptr->ddf_sensor_ptr->uimg_depot_ptr);
    if ( sample_ptr != NULL )
    {
      result = SNS_SUCCESS;
      *ts_ptr = sample_ptr->time_stamp;
    }
  }
  else
  {
    sns_rh_leave_island();
    sample_ptr = sns_smgr_depot_get_latest_sample(item_ptr->depot_ptr);
    if ( sample_ptr != NULL )
    {
      result = SNS_SUCCESS;
      *ts_ptr = sample_ptr->time_stamp;
    }
    sns_rh_enter_island();
  }
  return result;
}

/*===========================================================================

  FUNCTION:   sns_rh_handle_app_wake_sig

===========================================================================*/
/*!
  @brief Handles APP_WAKE signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_handle_app_wake_sig(void)
{
  SNS_SMGR_PRINTF2(
    HIGH, "WAKE_SIG curr state(%d) change count(%u)",
    sns_rh_uimg.app_is_awake, sns_rh_uimg.app_state_toggle_count);

  sns_rh_uimg.app_is_awake = true;
  sns_rh_uimg.app_state_toggle_count++;

  sns_rh_flush_reports_to_same_processor(SNS_PROC_APPS_V01, false);
  if ( sns_rh_send_report_indications() )
  {
    sns_rh_update_report_timer();
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_handle_app_sleep_sig

===========================================================================*/
/*!
  @brief Handles APP_SLEEP signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_handle_app_sleep_sig(void)
{
  SNS_SMGR_PRINTF2(
    HIGH, "SLEEP_SIG curr state(%d), change count(%u)",
    sns_rh_uimg.app_is_awake, sns_rh_uimg.app_state_toggle_count);

  sns_rh_uimg.app_is_awake = false;
  sns_rh_uimg.app_state_toggle_count++;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_ready_sample_sig

===========================================================================*/
/*!
  @brief Processes SNS_RH_SAMPLE_READY_SIG
  @param none
  @return none
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_ready_sample_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( (SNS_RH_REPORT_IS_PERIODIC(rpt_ptr) || rpt_ptr->periodic_like) &&
         sns_rh_ok_to_send_report(rpt_ptr) )
    {
      uint32_t i;
      bool queued = false;
      for ( i=0; i<rpt_ptr->num_items && !queued; i++ )
      {
        sns_ddf_time_t latest_sample_ts;
        sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
        sns_err_code_e get_result =
          sns_rh_get_latest_sample_timestamp(item_ptr, &latest_sample_ts);

        if ( get_result == SNS_SUCCESS &&
             item_ptr->state != RH_RPT_ITEM_STATE_LINKING &&
             TICK1_GTR_TICK2(latest_sample_ts, item_ptr->ts_last_sent) &&
             ((item_ptr->quality == SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01) ||
              (item_ptr->quality == SNS_SMGR_ITEM_QUALITY_FILTERED_V01) ||
              TICK1_GTR_TICK2(latest_sample_ts,
                              item_ptr->interpolator_obj.desired_timestamp)) )
        {
          sns_rh_add_to_ready_list(rpt_ptr);
          queued = true;
        }
      }
    }
  }
  sns_rh_send_report_indications();
}

/*===========================================================================

  FUNCTION:   sns_rh_process_odr_changed_sig

===========================================================================*/
SMGR_STATIC void sns_rh_process_odr_changed_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_rh_rpt_spec_s* rpt_ptrs[SNS_SMGR_MAX_REPORT_CNT];
  uint8_t i, num_rpts = 0;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    uint32_t i;
    for ( i=0; i<rpt_ptr->num_items; i++ )
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      if ( SMGR_BIT_TEST(item_ptr->ddf_sensor_ptr->flags,
                         SMGR_SENSOR_FLAGS_ODR_CHANGED_B) &&
           sns_rh_ok_to_send_report(rpt_ptr) )
      {
        SNS_SMGR_PRINTF1(HIGH, "odr_changed_sig - rpt_id=%u", rpt_ptr->rpt_id);
        rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        rpt_ptrs[num_rpts++] = rpt_ptr;
        sns_rh_add_to_ready_list(rpt_ptr);
        break;
      }
    }
  }
  for ( i=0; i<num_rpts; i++ )
  {
    sns_rh_flush_reports_to_ap(rpt_ptrs[i]);
  }
  sns_rh_send_report_indications();
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================

  FUNCTION:   sns_rh_process_fifo_flushed_sig

===========================================================================*/
SMGR_STATIC void sns_rh_process_fifo_flushed_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_rh_rpt_spec_s* rpt_ptrs[SNS_SMGR_MAX_REPORT_CNT];
  uint8_t i, num_rpts = 0;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_READY )
    {
      if ( sns_rh_ok_to_send_report(rpt_ptr) )
      {
        SNS_SMGR_PRINTF2(HIGH, "fifo_flushed_sig - rpt_id=%u/0x%x", 
                         rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
        rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        rpt_ptrs[num_rpts++] = rpt_ptr;
        sns_rh_add_to_ready_list(rpt_ptr);
      }
      else
      {
        rpt_ptr->state = RH_RPT_STATE_ACTIVE;
      }
    }
  }
  for ( i=0; i<num_rpts; i++ )
  {
    sns_rh_flush_reports_to_ap(rpt_ptrs[i]);
  }
  sns_rh_send_report_indications();

  /* Delete marked reports after flushing indications */
  num_rpts = 0;
  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->state          == RH_RPT_STATE_ACTIVE &&
         rpt_ptr->state_extended != RH_RPT_STATE_EXT_NONE )
    {
      rpt_ptrs[num_rpts++] = rpt_ptr;
    }
  }

  sns_rh_leave_island();
  for ( i=0; i<num_rpts; i++ )
  {
    sns_rh_sol_handle_pending_rpt(rpt_ptrs[i]);
  }
  sns_rh_enter_island();

}

/*===========================================================================

  FUNCTION:   sns_rh_report_timer_cb

===========================================================================*/
/*!
  @brief Time to send report(s).

  @detail

  @param[i]  cb_arg  callback argument
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_report_timer_cb(void *cb_arg)
{
  uint8_t os_err;
  sns_os_sigs_post(
    (OS_FLAG_GRP*)cb_arg, SNS_RH_REPORT_TIMER_SIG, OS_FLAG_SET, &os_err);
}

/*===========================================================================

  FUNCTION:   sns_rh_process_buffering_report_sigs

===========================================================================*/
/*!
  @brief Processes SNS_RH_REPORT_TIMER_SIG and SNS_RH_FIFO_SAMPLES_SIG

  @details Finds in report queue all Buffering report due to be sent
           and adds them to ready list.

           This function is called when a FIFO of samples become
           available, or by report timer expiring.  To prevent report timer
           from expiring before there are samples to send, the report interval
           is increased by one (1) sampling interval.  A report is considered
           ready when the timestamp of the latest sample is within two (2)
           sampling interval from the scheduled report time.

  @param [i] timer_sig - true if called because of SNS_RH_REPORT_TIMER_SIG
 
  @return none
*/
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_buffering_report_sigs(bool timer_sig)
{
  bool sent = false;
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) && !rpt_ptr->periodic_like &&
         sns_rh_ok_to_send_report(rpt_ptr) && (rpt_ptr->rpt_tick != 0) )
    {
      bool report_ready = false;
      if ( !rpt_ptr->event_sensors_only )
      {
        uint32_t i;
        for ( i=0; i<rpt_ptr->num_items && !report_ready; i++ )
        {
          sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
          if ( (!timer_sig && SNS_RH_FIFO_READY(item_ptr)) ||
               !sns_smgr_ddf_sensor_is_event_sensor(item_ptr->ddf_sensor_ptr) )
          {
            sns_ddf_time_t latest_sample_ts;
            sns_err_code_e get_result =
              sns_rh_get_latest_sample_timestamp(item_ptr, &latest_sample_ts);
            uint32_t four_sampling_intvl = rpt_ptr->min_sampling_interval<<2;

            if ( get_result == SNS_SUCCESS &&
                 TICK1_GTR_TICK2(latest_sample_ts,
                                 rpt_ptr->rpt_tick - four_sampling_intvl) )
            {
              report_ready = true;
            }
          }
        }
      }
      else if ( timer_sig && 
                TICK1_GEQ_TICK2(sns_em_get_timestamp(), rpt_ptr->rpt_tick) )
      {
        report_ready = true;
      }

      if ( report_ready )
      {
        sns_rh_add_to_ready_list(rpt_ptr);
        sns_rh_flush_reports_to_ap(rpt_ptr);

        if ( rpt_ptr->state_extended != RH_RPT_STATE_EXT_NONE )
        {
          /* this report has a pending response which would not be sent 
             unless and until FIFO_FLUSHED signal is processed */
          sns_rh_signal_me(SNS_RH_FIFO_FLUSHED_SIG);
        }
      }
    }
  }
  sent = sns_rh_send_report_indications();
  if ( timer_sig || sent )
  {
    sns_rh_update_report_timer();
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_app_state_change

===========================================================================*/
/*!
  @brief Called by Power module when AP state changes

  @detail
  @param[i] app_is_asleep - true if AP entered sleep state, false wake state
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_app_state_change(bool app_is_asleep)
{
  uint8_t  err;
  uint32_t set_bit = app_is_asleep ? SNS_RH_APP_SLEEP_SIG : SNS_RH_APP_WAKE_SIG;
  uint32_t clr_bit = app_is_asleep ? SNS_RH_APP_WAKE_SIG  : SNS_RH_APP_SLEEP_SIG;
  sns_os_sigs_post(sns_rh_uimg.sig_grp, clr_bit, OS_FLAG_CLR, &err);
  sns_os_sigs_post(sns_rh_uimg.sig_grp, set_bit, OS_FLAG_SET, &err);
}

/*===========================================================================
  FUNCTION:   sns_rh_pm_client_init
===========================================================================*/
SMGR_STATIC void sns_rh_pm_client_init(void)
{
  sns_pm_err_code_e pm_err =
    sns_pm_client_init(&sns_rh_uimg.pm_client_handle, sns_rh_app_state_change, "SMGR_RH");
  if ( pm_err != SNS_PM_SUCCESS )
  {
    SNS_SMGR_PRINTF1(FATAL, "Failed to register as PM client; err=%u", pm_err);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_update_report_timer

===========================================================================*/
/*!
  @brief Resets report timer as the schedule may have changed
  @param none
  @return none
*/
/*=========================================================================*/
void sns_rh_update_report_timer(void)
{
  uint32_t time_now = sns_em_get_timestamp();
  uint32_t earliest_report_time = 0xFFFFFFFF;
  int32_t offset = 0;
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  sns_em_cancel_utimer(sns_rh_uimg.report_timer);

  if ( sns_q_cnt(&sns_rh_uimg.report_queue) > 0 )
  {
    uint32_t num_buffering_reports = 0;
    SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
    {
      if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) && !rpt_ptr->periodic_like &&
           (rpt_ptr->rpt_tick != 0) && sns_rh_ok_to_send_report(rpt_ptr) )
      {
        num_buffering_reports++;
        if ( TICK1_GTR_TICK2(rpt_ptr->rpt_tick, time_now) )
        {
          earliest_report_time = MIN(earliest_report_time, rpt_ptr->rpt_tick);
        }
      }
    }

    if ( earliest_report_time != 0xFFFFFFFF)
    {
      offset = earliest_report_time - time_now;
      if ( sns_em_register_utimer(sns_rh_uimg.report_timer, offset) != SNS_SUCCESS )
      {
        SNS_SMGR_PRINTF2(
          ERROR, "report_timer - now=%u offset=%d", time_now, offset);
      }
      sns_profiling_log_qdss(SNS_RH_RPT_TIMER_SET, 2, earliest_report_time, offset);
    }
    else
    {
      SNS_SMGR_PRINTF2(LOW, "report_timer - #reports=%u now=%u",
                       num_buffering_reports, time_now);
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_add_to_ready_list

===========================================================================*/
/*!
  @brief Adds the given report to the list of reports ready to be sent.

  @param[i] report_ptr - the report to add

  @return none
*/
/*=========================================================================*/
bool sns_rh_add_to_ready_list(sns_rh_rpt_spec_s* report_ptr)
{
  bool added = false;
  sns_rh_rpt_spec_s** rpp = &sns_rh_uimg.ready_report_ptr;
  /* -------------------------------------------------------------------- */

  while ( *rpp != NULL )
  {
    if ( *rpp == report_ptr )
    {
      /* already on ready list */
      break;
    }
    rpp = &(*rpp)->next_ready_report_ptr;
  }
  if (*rpp == NULL)
  {
    /* not already on ready list */
    *rpp = report_ptr;
    added = true;
  }
  return added;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_remove_from_ready_list

===========================================================================*/
/*!
  @brief Removes the given report from the list of reports ready to be sent.

  @param[i] report_ptr - the report to remove from ready list

  @return none
*/
/*=========================================================================*/
void sns_rh_rpt_gen_remove_from_ready_list(sns_rh_rpt_spec_s* rpt_ptr)
{
  sns_rh_rpt_spec_s** rpp = &sns_rh_uimg.ready_report_ptr;
  /* -------------------------------------------------------------------- */

  while ( *rpp != NULL )
  {
    if ( *rpp == rpt_ptr )
    {
      /* remove this report from ready list */
      *rpp = rpt_ptr->next_ready_report_ptr;
      rpt_ptr->next_ready_report_ptr = NULL;
      SNS_SMGR_PRINTF2(
        MED, "remove_from_ready_list - rpt_id=%u/0x%x",
        rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
      break;
    }
    rpp = &(*rpp)->next_ready_report_ptr;
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_init_uimg
===========================================================================*/
OS_FLAG_GRP* sns_rh_init_uimg(void)
{
  uint8_t  err;

  sns_rh_uimg.sig_grp = sns_os_sigs_create(0, &err);
  SNS_ASSERT(sns_rh_uimg.sig_grp != NULL);

  sns_rh_uimg.app_is_awake = true;

  sns_q_init(&sns_rh_uimg.report_queue);

  sns_em_create_utimer_obj(&sns_rh_report_timer_cb, sns_rh_uimg.sig_grp,
                           SNS_EM_TIMER_TYPE_ONESHOT, &sns_rh_uimg.report_timer);

  sns_rh_pm_client_init();

  sns_rh_uimg.sig_mask =
    SNS_RH_SELF_TEST_DONE_SIG         |
    SNS_RH_FIFO_SAMPLES_SIG           |
    SNS_RH_SAMPLE_READY_SIG           |
    SNS_RH_REPORT_TIMER_SIG           |
    SNS_RH_MD_INT_ENABLED_SIG         |
    SNS_RH_MD_INT_DISABLED_SIG        |
    SNS_RH_MD_INT_SIG                 |
    SNS_RH_ODR_CHANGED_SIG            |
    SNS_RH_FIFO_FLUSHED_SIG           |
    SNS_RH_RESP_Q_SIG                 |
    SNS_RH_IND_Q_SIG                  |
    SNS_RH_SMR_MSG_SIG                |
    SNS_RH_SMR_DISC_SIG               |
    SNS_RH_APP_WAKE_SIG               |
    SNS_RH_APP_SLEEP_SIG              |
    SNS_RH_UPDATE_REPORT_TIMER_SIG;

  return sns_rh_uimg.sig_grp;
}

/*===========================================================================

  FUNCTION:   sns_rh_task_loop

===========================================================================*/
/*!
  @brief Request Handler task

  @detail

  @param[i]  sig_grp
  @param[i]  sig_mask

  @return   none
 */
/*=========================================================================*/
void sns_rh_task_loop(void)
{
  OS_FLAGS  sig_flags;
  OS_FLAGS  big_image_sig_mask =
    SNS_RH_SMR_DISC_SIG             |
    SNS_RH_SELF_TEST_DONE_SIG       |
    SNS_RH_MD_INT_ENABLED_SIG       |
    SNS_RH_MD_INT_DISABLED_SIG      |
    SNS_RH_MD_INT_SIG               |
    SNS_RH_RESP_Q_SIG               |
    SNS_RH_IND_Q_SIG                |
    SNS_RH_SMR_MSG_SIG;
  /* -------------------------------------------------------------------- */

  sns_os_sigs_add(sns_rh_uimg.sig_grp, sns_rh_uimg.sig_mask);

  while ( 1 )
  {
    uint8_t  err;

    sns_profiling_log_qdss(SNS_RH_EXIT, 0);

    /* OS_FLAG_CONSUME will make the SMR clear the flag after the call */
    sig_flags = sns_os_sigs_pend(sns_rh_uimg.sig_grp, sns_rh_uimg.sig_mask,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);

    sns_profiling_log_qdss(SNS_RH_ENTER, 2, sig_flags, sns_em_get_timestamp());

    if ( sig_flags & SNS_RH_APP_WAKE_SIG )
    {
      sns_rh_handle_app_wake_sig();
    }
    if ( sig_flags & SNS_RH_APP_SLEEP_SIG )
    {
      sns_rh_handle_app_sleep_sig();
    }
    if ( sig_flags & SNS_RH_SAMPLE_READY_SIG )
    {
      sns_rh_process_ready_sample_sig();
    }
    if ( sig_flags & SNS_RH_REPORT_TIMER_SIG )
    {
      sns_rh_process_buffering_report_sigs(true);
    }
    if ( sig_flags & SNS_RH_FIFO_SAMPLES_SIG )
    {
      sns_rh_process_buffering_report_sigs(false);
    }
    if ( sig_flags & SNS_RH_ODR_CHANGED_SIG )
    {
      sns_rh_process_odr_changed_sig();
    }
    if ( sig_flags & SNS_RH_FIFO_FLUSHED_SIG )
    {
      sns_rh_process_fifo_flushed_sig();
    }
    if ( sig_flags & SNS_RH_UPDATE_REPORT_TIMER_SIG )
    {
      sns_rh_update_report_timer();
    }
    if ( sig_flags & big_image_sig_mask )
    {
      sns_rh_leave_island();
      sns_rh_process_big_image_signals(sig_flags);
      sns_rh_enter_island();
      sig_flags &= ~big_image_sig_mask;
    }

    sig_flags &= ~sns_rh_uimg.sig_mask;
    if ( sig_flags )
    {
      SNS_SMGR_PRINTF1(ERROR, "rh_task - unknown sigs(0x%08x)", sig_flags);
    }
  } /* while */
}

/*===========================================================================

  FUNCTION:   sns_rh_signal_me

===========================================================================*/
/*!
  @brief Posts a signal to RH task

  @detail
  @param[i] sig - the signal to post
  @return   none
 */
/*=========================================================================*/
void sns_rh_signal_me(uint32_t sig)
{
  uint8_t os_err;
  sns_os_sigs_post(sns_rh_uimg.sig_grp, sig, OS_FLAG_SET, &os_err);
}

/*===========================================================================

  FUNCTION:   sns_rh_unsignal_me

===========================================================================*/
/*!
  @brief Clears the given signal that might have been sent to RH task

  @detail
  @param[i] sig - the signal to post
  @return   none
 */
/*=========================================================================*/
void sns_rh_unsignal_me(uint32_t sig)
{
  sns_os_sigs_post(sns_rh_uimg.sig_grp, sig, OS_FLAG_CLR, NULL);
}

/*===========================================================================
  FUNCTION:   sns_rh_leave_island
===========================================================================*/
void sns_rh_leave_island(void)
{
  if ( sns_rh_uimg.pm_client_handle != NULL )
  {
    sns_pm_vote_img_mode(sns_rh_uimg.pm_client_handle, SNS_IMG_MODE_BIG);
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_enter_island
===========================================================================*/
void sns_rh_enter_island(void)
{
  if ( sns_rh_uimg.pm_client_handle != NULL )
  {
    if ( sns_rh_get_report_count() == 0 )
    {
      sns_pm_vote_img_mode(sns_rh_uimg.pm_client_handle, SNS_IMG_MODE_NOCLIENT);
    }
    else
    {
      sns_pm_vote_img_mode(sns_rh_uimg.pm_client_handle, SNS_IMG_MODE_MICRO);
    }
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_get_report_queue
===========================================================================*/
sns_q_s* sns_rh_get_report_queue(void)
{
  return &sns_rh_uimg.report_queue;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_report_count
  =========================================================================*/
int sns_rh_get_report_count(void)
{
  return sns_q_cnt(&sns_rh_uimg.report_queue);
}

/*=========================================================================
  FUNCTION:  sns_rh_get_report_count
  =========================================================================*/
bool sns_rh_ok_to_send_report(const sns_rh_rpt_spec_s* rpt_ptr)
{
  return ((rpt_ptr->proc_type != SNS_PROC_APPS_V01) ||
           sns_rh_uimg.app_is_awake || rpt_ptr->send_ind_during_suspend);
}

/*=========================================================================
  FUNCTION:  sns_rh_get_periodic_ind_buf
  =========================================================================*/
sns_smgr_periodic_report_ind_msg_v01* sns_rh_get_periodic_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.periodic;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_buffering_ind_buf
  =========================================================================*/
sns_smgr_buffering_ind_msg_v01* sns_rh_get_buffering_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.buffering;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_query_ind_buf
  =========================================================================*/
sns_smgr_buffering_query_ind_msg_v01* sns_rh_get_query_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.query;
}

/*===========================================================================

  FUNCTION:   sns_rh_task_init

===========================================================================*/
/*!
  @brief Called by SMGR task to create Request Handler task.

  @detail

  @param   none
  @return  return SNS_SUCCESS always
 */
/*=========================================================================*/
sns_err_code_e sns_rh_task_init(void)
{
  uint32_t stack_size = ARR_SIZE(sns_rh_uimg.task_stack);
  sns_os_task_create_ext(sns_rh_task, NULL,
                         &sns_rh_uimg.task_stack[stack_size - 1],
                         SNS_MODULE_PRI_DSPS_RH,
                         SNS_MODULE_PRI_DSPS_RH,
                         sns_rh_uimg.task_stack,
                         stack_size,
                         (void *)0,
                         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR |
                         OS_TASK_OPT_ISLAND,
                         (uint8_t *)"SNS_RH");
  return SNS_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_rh_get_pm_client_handle

===========================================================================*/
/*!
  @brief Returns RH's handle for PM

  @detail

  @param   none
  @return  return RH PM handle
 */
/*=========================================================================*/
sns_pm_handle_t sns_rh_get_pm_client_handle(void)
{
  return sns_rh_uimg.pm_client_handle;
}


