/*=============================================================================
  @file sns_smgr_sensor_uimg.c

  This file contains the logic for managing sensor data sampling in SMGR

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_sensor_uimg.c#3 $ */
/* $DateTime: 2015/02/02 09:59:18 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-01-26  pn   - Changed FIFO full determination
                   - Changed FIFO timestamp calculation
                   - Changed sensor READY state determination
                   - Moved sns_smgr_schedule_sensor_event() out of uImage code space
  2014-12-30  pn   Added debug logging for infrequent sampling
  2014-11-24  pn   Sends SNS_RH_FIFO_SAMPLES_SIG when FIFO data is received
  2014-11-11  pn   Updated timestamp validation
  2014-10-28  pn   Validates FIFO sample timestamps before consuming them
  2014-10-22  pn   Defines depot full margin 
  2014-10-02  pn   Sends SNS_RH_REPORT_TIMER_SIG when FIFO data is received
  2014-09-25  pn   - Puts new samples into appropriate depot
                   - Monitors uImage depots and copies them to bigImage when full
  2014-09-23  pn   Added QDSS logging for notify_data
  2014-09-14  vy   Used new uImage supported DDF api to free memhandler
  2014-09-08  pn   Remembers and votes for current image mode when exiting big image
  2014-08-25  vy   Enabled QDSS logging
  2014-08-05  pn   Fixed problem of lost precision in FIFO data interval calculation
  2014-07-31  pn   Removed obsolete Power control code
  2014-06-05  vy   Added support for non-uimage DD
  2014-06-05  vy   Further refactored to support uImage
  2014-15-24  vy   Introduced utimers
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <math.h>

#include "sns_em.h"
#include "sns_memmgr.h"
#include "sns_profiling.h"
#include "sns_rh_util.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_ddf_if.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_pm_if.h"
#include "sns_smgr_util.h"

#if defined(SNS_QDSP_SIM)
#include "sns_qdsp_playback_utils.h"
#endif

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_SAMPLING_DEBUG
#ifdef SNS_SMGR_SAMPLING_DEBUG
#define SNS_SMGR_SAMPLING_DBG0 SNS_SMGR_PRINTF0
#define SNS_SMGR_SAMPLING_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_SAMPLING_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_SAMPLING_DBG3 SNS_SMGR_PRINTF3
#define SNS_SMGR_SAMPLING_DBG4 SNS_SMGR_PRINTF4
#else
#define SNS_SMGR_SAMPLING_DBG0(level,msg)
#define SNS_SMGR_SAMPLING_DBG1(level,msg,p1)
#define SNS_SMGR_SAMPLING_DBG2(level,msg,p1,p2)
#define SNS_SMGR_SAMPLING_DBG3(level,msg,p1,p2,p3)
#define SNS_SMGR_SAMPLING_DBG4(level,msg,p1,p2,p3,p4)
#endif

/* Sample depot full-alert should be sent when it reaches its high watermark */
#define SNS_SMGR_FULL_DEPOT_HI_WATERMARK    5

/*----------------------------------------------------------------------------
 *  Global Variables
 * -------------------------------------------------------------------------*/
extern sns_smgr_s              sns_smgr;


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_schedule_sensor_event

===========================================================================*/
/*!
  @brief Schedules the next sensor event processing

  @param[i] tick_offset - wait time (in ticks)

  @return none
*/
/*=========================================================================*/
void sns_smgr_schedule_sensor_event(uint32_t tick_offset)
{
  sns_err_code_e status = ADSP_EFAILED;
  uint8_t i;

  tick_offset = MAX(tick_offset, SMGR_TOO_SHORT_TICKS_FOR_TIMER);
  SNS_SMGR_PRINTF1(LOW, "sched_sensor_ev - offset=%u", (unsigned)tick_offset);
  sns_em_cancel_utimer(sns_smgr.sensor_ev_tmr_obj);
  for ( i=0; i<100 && status!=ADSP_EOK; i++ )
  {
    status = sns_em_register_utimer(sns_smgr.sensor_ev_tmr_obj, tick_offset);
  }
  if ( status != ADSP_EOK )
  {
    SNS_SMGR_PRINTF0(ERROR, "sched_sensor_ev - register_timer failed");
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_handle_new_sample

===========================================================================*/
/*!
  @brief  Saves the given data into given DDF sensor's depot and updates all
          associated items' state.

  @param[i] ddf_sensor_ptr - the DDF sensor
  @param[i] data_ptr       - sample polled from device

  @return
   None

*/
/*=========================================================================*/
SMGR_STATIC void sns_smgr_handle_new_sample(
  sns_smgr_ddf_sensor_s*       ddf_sensor_ptr,
  const sns_ddf_sensor_data_s* data_ptr)
{
  if ( ddf_sensor_ptr->uimg_depot_ptr != NULL )
  {
    (void)sns_smgr_depot_put_sample(ddf_sensor_ptr->uimg_depot_ptr, data_ptr);
  }
  else /* sensor is not uImage-ready */
  {
    sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
    sns_smgr_vote_image_mode(SNS_IMG_MODE_BIG);
    (void)sns_smgr_depot_put_sample(ddf_sensor_ptr->bimg_depot_ptr, data_ptr);
    sns_smgr_vote_image_mode(curr_mode);
  }
  ddf_sensor_ptr->sensor_type_state = SENSORTYPE_STATE_IDLE;

  if ( data_ptr->samples != NULL && 
       (data_ptr->status != SNS_DDF_SUCCESS || 
        ddf_sensor_ptr->depot_data_rate < FX_ONE_Q16 ||
        sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr)) )
  {
    SNS_SMGR_PRINTF3(
      MED, "new_sample - sensor=%u status=%d ts=%u",
      SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
      data_ptr->status, data_ptr->timestamp);
    SNS_SMGR_PRINTF3(
      LOW, "new_sample - X=%d Y=%d Z=%d",
      data_ptr->samples[0].sample, data_ptr->samples[1].sample, 
      data_ptr->samples[2].sample);
  }
  if ( ddf_sensor_ptr->client_stat.num_periodic_reports > 0 )
  {
    sns_rh_signal_me(SNS_RH_SAMPLE_READY_SIG);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_check_depot_full

===========================================================================*/
/*!
  @brief  Checks if uImage depot will be full soon and signals self to copy its
          contents to bigImage depot

  @param [io] ddf_sensor_ptr - the DDF sensor
  @param [i]  num_new_samples - number of samples just deposited

  @return none

*/
/*=========================================================================*/
SMGR_STATIC void sns_smgr_check_depot_full(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr,
  uint32_t               num_new_samples)
{
  if ( ddf_sensor_ptr->bimg_depot_in_use && ddf_sensor_ptr->uimg_depot_ptr != NULL )
  {
    uint32_t full_margin_sample_count;

    ddf_sensor_ptr->num_new_samples += num_new_samples;

    full_margin_sample_count = 
      MAX(ddf_sensor_ptr->sensor_ptr->fifo_cfg.current_watermark,
          SNS_SMGR_FULL_DEPOT_HI_WATERMARK);

    if ( (ddf_sensor_ptr->num_new_samples + full_margin_sample_count) >= 
         sns_smgr_depot_get_depth(ddf_sensor_ptr->uimg_depot_ptr) )
    {
      ddf_sensor_ptr->uimg_depot_full_alert = true;
      sns_smgr_signal_me(SNS_SMGR_DEPOT_COPY_SIG);
    }
  }

}

/*===========================================================================

  FUNCTION:   smgr_get_scheduled_sampling_time

===========================================================================*/
/*!
  @brief  Given a DDF sensor, returns its next scheduled sampling time.

  @param[i] ddf_sensor_ptr - the DDF sensor

  @return
   scheduled sampling time, or 0 if not scheduled

*/
/*=========================================================================*/
SMGR_STATIC sns_ddf_time_t smgr_get_scheduled_sampling_time(
  const sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  sns_ddf_time_t timestamp = 0;
  sns_q_s* q_ptr = SMGR_QUE_HEADER_FROM_LINK(&ddf_sensor_ptr->sched_link);
  if ( q_ptr != NULL )
  {
    smgr_sched_block_s* sched_ptr =
      SMGR_GET_ENTRY(q_ptr, smgr_sched_block_s, ddf_sensor_queue);
    timestamp = sched_ptr->next_tick;
  }
  return timestamp;
}

/*===========================================================================

  FUNCTION:   sns_smgr_validate_timestamps

===========================================================================*/
/*!
  @brief Makes sure samples provided by DD have ascending timestamps

  @param[i] new_data_ptr    - raw data from DD
  @param[i] last_sample_ptr - latest sample in depot
  @param[i] num_samples_set - number of samples in FIFO
  @param[i] dimension       - number of axes

  @return false if sample timestamps are not sane

*/
/*=========================================================================*/
SMGR_STATIC bool sns_smgr_validate_timestamps(
  const sns_ddf_sensor_data_s* new_data_ptr,
  const sns_smgr_sample_s*     last_sample_ptr,
  uint32_t                     num_samples_set,
  uint8_t                      dimension)
{
  bool in_order = true;
  if ( new_data_ptr->num_samples > dimension )
  {
    if ( (new_data_ptr->end_timestamp - new_data_ptr->timestamp) > SMGR_MAX_TICKS )
    {
      SNS_SMGR_PRINTF4(
        ERROR, "validate_timestamps - sensor=%u start=%u end=%u #sets=%u",
        new_data_ptr->sensor, new_data_ptr->timestamp, new_data_ptr->end_timestamp,
        num_samples_set);
      in_order = false;
    }
  }
  if ( last_sample_ptr != NULL && 
       (new_data_ptr->timestamp - last_sample_ptr->time_stamp) > SMGR_MAX_TICKS )
  {
    SNS_SMGR_PRINTF3(
      ERROR, "validate_timestamps - sensor=%u previous=%u new=%u",
      new_data_ptr->sensor, last_sample_ptr->time_stamp, new_data_ptr->timestamp);
    in_order = false;
  }
  return in_order;
}

/*===========================================================================

  FUNCTION:   sns_smgr_consume_async_data

===========================================================================*/
/*!
  @brief Consumes individual samples from given data array.

  @param[io] ddf_sensor_ptr - the sensor that produced the samples
  @param[i] data_ptr        - raw sample arrau from DD
  @param[i] num_samples_set - number of samples in array
  @param[i] dimension       - number of axes

  @return none
*/
/*=========================================================================*/
SMGR_STATIC void sns_smgr_consume_async_data(
  sns_smgr_ddf_sensor_s*        ddf_sensor_ptr,
  const sns_ddf_sensor_data_s*  data_ptr,
  uint32_t                      num_samples_set,
  uint8_t                       dimension)
{
  uint32_t i;
  sns_ddf_sensor_data_s single_data;
  const sns_ddf_time_t* end_ts_ptr = &data_ptr->timestamp;
  uint32_t samples_set_index = 0;
  float time_interval_offset = 0.0;
  float time_interval = 0.0;
  /* -------------------------------------------------------------------- */

  sns_profiling_log_qdss(
    SNS_SMGR_NOTIFY_DATA, 3, data_ptr->sensor, num_samples_set, 
    (num_samples_set > 1) ? data_ptr->end_timestamp : data_ptr->timestamp);

  single_data.sensor = data_ptr->sensor;
  single_data.status = data_ptr->status;
  if( num_samples_set > 0)
  {
    single_data.num_samples = dimension;
    if ( num_samples_set > 1 )
    {
      time_interval = 
        ((float)(data_ptr->end_timestamp-data_ptr->timestamp)/(num_samples_set-1));
      end_ts_ptr = &data_ptr->end_timestamp;
    }
  }
  else
  {
    single_data.num_samples = data_ptr->num_samples;
  }

  SNS_SMGR_SAMPLING_DBG3(
     LOW, "#sets=%d #dataSamples=%u intvl=%u", 
     num_samples_set, data_ptr->num_samples, time_interval);

  SNS_SMGR_SAMPLING_DBG3(
     LOW, "1st_ts=%u last_ts=%u invt*100=%u", 
     data_ptr->timestamp, data_ptr->end_timestamp, time_interval*100);

  for ( i=0; i<num_samples_set; i++ )
  {
    single_data.samples = &data_ptr->samples[samples_set_index];
    single_data.timestamp = data_ptr->timestamp + (sns_ddf_time_t)time_interval_offset;
    if ( i == 0 )
    {
      single_data.timestamp = data_ptr->timestamp;
    }
    else if ( i == num_samples_set-1 )
    {
      single_data.timestamp = *end_ts_ptr;
    }
    samples_set_index += dimension;
    time_interval_offset += time_interval;

    if ( ddf_sensor_ptr->sensor_ptr->sensor_state == SENSOR_STATE_READY ||
         (ddf_sensor_ptr->sensor_ptr->sensor_state == SENSOR_STATE_CONFIGURING &&
          TICK1_GTR_TICK2(single_data.timestamp,
                          ddf_sensor_ptr->sensor_ptr->event_done_tick)) )
    {
      SNS_SMGR_SAMPLING_DBG3(
        LOW, "dri_fifo_async - ddf_sensor=%d dri_count=%d data_poll_ts=%u",
        single_data.sensor, ddf_sensor_ptr->dri_count, ddf_sensor_ptr->data_poll_ts);
      if ( ddf_sensor_ptr->sensor_type_state == SENSORTYPE_STATE_IDLE )
      {
        if ( ddf_sensor_ptr->dri_count++ == 0 )
        {
          sns_smgr_handle_new_sample(ddf_sensor_ptr, &single_data);
        }
        else
        {
          SNS_SMGR_SAMPLING_DBG1(LOW, "skipping ts=%u", single_data.timestamp);
        }
        if ( ddf_sensor_ptr->dri_count >= ddf_sensor_ptr->device_sampling_factor )
        {
          ddf_sensor_ptr->dri_count = 0;
        }
      }
      else if ( ddf_sensor_ptr->data_poll_ts != 0 )
      {
        /* asynchronous response */
        SNS_SMGR_SAMPLING_DBG3(
          LOW, "dri_fifo_async - delay=%d poll_ts=%u sample_ts=%u",
          (sns_em_get_timestamp() - ddf_sensor_ptr->data_poll_ts),
          ddf_sensor_ptr->data_poll_ts, single_data.timestamp);
        sns_smgr_handle_new_sample(ddf_sensor_ptr, &single_data);
      }
      ddf_sensor_ptr->sensor_type_state = SENSORTYPE_STATE_IDLE;
    }
    else
    {
      SNS_SMGR_SAMPLING_DBG2(
        HIGH, "dri_fifo_async - ddf_sensor %d not ready ts=%u",
        single_data.sensor, single_data.timestamp);
      single_data.status = SNS_DDF_EINVALID_DATA;
      sns_smgr_handle_new_sample(ddf_sensor_ptr, &single_data);
    }
  }
}

/*===========================================================================

  FUNCTION:   smgr_process_dri_fifo_async_data

===========================================================================*/
/*!
  @brief Called by notify_data()

  @detail

  @param[i] ddf_sensor_ptr - the sensor from which to sample data

  @return
    true the sample data is availble
    false the sample data is not availble yet

*/
/*=========================================================================*/
void smgr_process_dri_fifo_async_data(
  sns_smgr_ddf_sensor_s*        ddf_sensor_ptr,
  const sns_ddf_sensor_data_s*  data_ptr)
{
  sns_smgr_sample_depot_s* depot_ptr = ddf_sensor_ptr->uimg_depot_ptr;
  const sns_smgr_sample_s* last_sample_ptr;
  uint32_t num_samples_set = 0;
  sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
  /* -------------------------------------------------------------------- */

  SNS_SMGR_SAMPLING_DBG4(
    LOW, "dri_fifo_async - ddf_sensor=%d state=%d type_state=%d #samples=%d",
    data_ptr->sensor, ddf_sensor_ptr->sensor_ptr->sensor_state,
    ddf_sensor_ptr->sensor_type_state, data_ptr->num_samples);

  if ( depot_ptr == NULL )
  {
    sns_smgr_vote_image_mode(SNS_IMG_MODE_BIG);
    depot_ptr = ddf_sensor_ptr->bimg_depot_ptr;
  }

  sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
  last_sample_ptr = sns_smgr_depot_get_latest_sample(depot_ptr);
  num_samples_set = 
    ((data_ptr->num_samples)+(depot_ptr->num_axes-1))/depot_ptr->num_axes;

  if ( sns_smgr_ddf_sensor_is_event_sensor(ddf_sensor_ptr) ||
       sns_smgr_validate_timestamps(data_ptr, last_sample_ptr, 
                                    num_samples_set, depot_ptr->num_axes) )
  {
    sns_smgr_consume_async_data(ddf_sensor_ptr, data_ptr, num_samples_set,
                                depot_ptr->num_axes);
    sns_smgr_check_depot_full(ddf_sensor_ptr, num_samples_set);
    if ( num_samples_set > 1 )
    {
      sns_rh_signal_me(SNS_RH_FIFO_SAMPLES_SIG);
    }
  }

  if ( (num_samples_set == 0) && (data_ptr->status != SNS_DDF_SUCCESS) )
  {
    ddf_sensor_ptr->sensor_type_state = SENSORTYPE_STATE_IDLE;
  }

  if ( last_sample_ptr != NULL )
  {
    uint32_t delta_time = data_ptr->timestamp - last_sample_ptr->time_stamp;
    uint8_t num_skipped_samples = delta_time / ddf_sensor_ptr->depot_data_interval;
    ddf_sensor_ptr->max_skipped_samples =
      MAX(ddf_sensor_ptr->max_skipped_samples, num_skipped_samples);
  }

  sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
  sns_smgr_vote_image_mode(curr_mode);
}

/*===========================================================================

  FUNCTION:   smgr_get_data

===========================================================================*/
/*!
  @brief issue driver get_data(), and save the sampled data into a saving area.

  @detail

  @param[i] ddf_sensor_ptr - the sensor from which to sample data

  @return
    true the sample data is availble
    false the sample data is not availble yet

*/
/*=========================================================================*/
void smgr_get_data(sns_smgr_ddf_sensor_s* in_ddf_sensor_ptr)
{
  sns_smgr_sensor_s*    sensor_ptr = in_ddf_sensor_ptr->sensor_ptr;
  sns_ddf_sensor_e      ddf_sensor_type[SMGR_MAX_DATA_TYPES_PER_DEVICE];
  uint8_t               i, num_data_types = 0;
  sns_ddf_status_e      driver_status = SNS_DDF_EFAIL;
  sns_ddf_sensor_data_s* data_ptr;
  sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();

  ddf_sensor_type[num_data_types++] =
    SMGR_SENSOR_TYPE(sensor_ptr, in_ddf_sensor_ptr->data_type);

  for ( i=0; i<ARR_SIZE(ddf_sensor_type) && num_data_types<ARR_SIZE(ddf_sensor_type); i++ )
  {
    if ( (i != in_ddf_sensor_ptr->data_type) &&
         (sensor_ptr->ddf_sensor_ptr[i] != NULL) &&
         (smgr_get_scheduled_sampling_time(sensor_ptr->ddf_sensor_ptr[i]) -
          sns_smgr.sched_tick.u.low_tick <= SMGR_SCHEDULE_GRP_TOGETHER_TICK) )
    {
      ddf_sensor_type[num_data_types++] = SMGR_SENSOR_TYPE(sensor_ptr, i);
      SNS_SMGR_SAMPLING_DBG2(MED, "get_data - ddf_s0=%d ddf_s1=%d",
                             ddf_sensor_type[0], ddf_sensor_type[1]);
    }
  }

  if ( sensor_ptr->const_ptr->flags & SNS_REG_SSI_FLAG_LTCY_ENABLE )
  {
    sns_latency.polling_get_data_start_ts = sns_em_get_timestamp();
  }

  sns_ddf_memhandler_init( &(sensor_ptr->memhandler) );
  sns_profiling_log_qdss(SNS_SMGR_DD_ENTER_GET_DATA, 1, sensor_ptr->const_ptr->sensor_id);
  if ( !sensor_ptr->is_uimg_refac )
  {
    sns_smgr_vote_image_mode(SNS_IMG_MODE_BIG);
  }
  driver_status = SMGR_DRV_FN_PTR(sensor_ptr)->get_data(sensor_ptr->dd_handle,
                                                        ddf_sensor_type,
                                                        num_data_types,
                                                        &sensor_ptr->memhandler,
                                                        &data_ptr);
  if ( !sensor_ptr->is_uimg_refac )
  {
    sns_smgr_vote_image_mode(curr_mode);
  }
  sns_profiling_log_qdss(SNS_SMGR_DD_EXIT, 1, SNS_QDSS_DD_GET_DATA);
  SNS_SMGR_SAMPLING_DBG3(LOW, "get_data - sensor=%d types=%d status=%d",
                         SMGR_SENSOR_ID(sensor_ptr), num_data_types, driver_status);

  for ( i=0;  i<num_data_types; i++ )
  {
    sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
      sns_smgr_match_ddf_sensor(sensor_ptr, ddf_sensor_type[i]);
    if ( ddf_sensor_ptr != NULL )
    {
      sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
      ddf_sensor_ptr->data_poll_ts = sns_smgr.sched_tick.u.low_tick;
      if ( driver_status == SNS_DDF_SUCCESS )
      {
        /* if latency measurement enabled, run latency measurement */
        if ( sensor_ptr->const_ptr->flags & SNS_REG_SSI_FLAG_LTCY_ENABLE )
        {
          sns_latency.polling_get_data_end_ts = data_ptr[i].timestamp;
          //sns_profiling_log_latency_poll(sns_latency, data_ptr[i].sensor);
        }
        sns_smgr_handle_new_sample(ddf_sensor_ptr, &data_ptr[i]);
        sns_smgr_check_depot_full(ddf_sensor_ptr, 1);
      }
      else if ( driver_status == SNS_DDF_PENDING )
      {
        ddf_sensor_ptr->sensor_type_state = SENSORTYPE_STATE_READ_PENDING;
      }
      else
      {
        sns_ddf_sensor_data_s  data;
        SNS_SMGR_PRINTF2(ERROR, "get_data - ddf_sensor=%d drv_stat=%d",
                         ddf_sensor_type[i], driver_status);
        SNS_OS_MEMZERO(&data, sizeof(data));
        data.status = SNS_DDF_EINVALID_DATA;
        data.timestamp = sns_em_get_timestamp();
        sns_smgr_handle_new_sample(ddf_sensor_ptr, &data);
        sns_smgr_check_depot_full(ddf_sensor_ptr, 1);
      }
      sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
    } /* valid data type */
  } /* for each data type */
  sns_ddf_memhandler_free_ex(&sensor_ptr->memhandler, sensor_ptr);
}

/*===========================================================================

  FUNCTION:   sns_smgr_proc_sampling_schedule

===========================================================================*/
/*!
  @brief  traverse the report schedule queue and make samples when its the time to sample.
          After sampling, save the result into a last sample saving area.
          Also, re-schdule the next time to sample.

  @detail Data gathering cycle is flagged for execution within sampling_cycle. Data gathering cycle calls
          the functions that occur after reading data: GenerateReports and etc.

  @param[i] NONE

  @return
    The next schedule timetick offset from now

*/
/*=========================================================================*/
SMGR_STATIC uint32_t sns_smgr_proc_sampling_schedule(void)
{
  smgr_sched_block_s*  sched_blk_ptr;
  uint32_t             next_tick_offset = SMGR_MAX_TICKS;

  sns_hw_set_qup_clk(true);

  /* Traverse all the schedule block */
  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.sched_que, sched_blk_ptr, sched_link)
  {
    uint32_t delta_time = sns_smgr.sched_tick.u.low_tick +
      SMGR_SCHEDULE_GRP_TOGETHER_TICK - sched_blk_ptr->next_tick;
    uint8_t num_skipped_samples = delta_time / sched_blk_ptr->sched_intvl;

    SNS_SMGR_SAMPLING_DBG4(
      LOW, "sampling_sched - rate=%d sched_tick=%u next=%u delta=%u",
      sched_blk_ptr->sampling_rate, sns_smgr.sched_tick.u.low_tick, 
      sched_blk_ptr->next_tick, delta_time);

    if ( delta_time <= SMGR_MAX_TICKS )
    {
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr;

      /* it's time to read the data */
      SMGR_FOR_EACH_Q_ITEM(&sched_blk_ptr->ddf_sensor_queue, ddf_sensor_ptr, sched_link)
      {
        sns_smgr_sensor_s *sensor_ptr = ddf_sensor_ptr->sensor_ptr;
        if ( SENSOR_STATE_READY == sensor_ptr->sensor_state)
        {
          SNS_SMGR_SAMPLING_DBG3(
            MED, "sampling_sched - sensor_state=%d type_state=%d poll_ts=%u",
            sensor_ptr->sensor_state, ddf_sensor_ptr->sensor_type_state, 
            ddf_sensor_ptr->data_poll_ts);
          if ( SENSORTYPE_STATE_READ_PENDING == ddf_sensor_ptr->sensor_type_state )
          {
            SNS_SMGR_SAMPLING_DBG0(LOW, "sampling_sched - pending");
          }
          else if ( TICK1_GTR_TICK2(sns_smgr.sched_tick.u.low_tick,
                                    ddf_sensor_ptr->data_poll_ts) )
          {
            smgr_get_data(ddf_sensor_ptr);
          }
        }
        else
        {
          sns_ddf_sensor_data_s data;
          data.status = SNS_DDF_EINVALID_DATA;
          data.timestamp = sns_em_get_timestamp();
          data.samples = NULL;
          SNS_SMGR_SAMPLING_DBG2(
            HIGH, "sampling_sched - ddf_sensor %d not ready ts=%u",
            SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr,
                             ddf_sensor_ptr->data_type), data.timestamp);
          sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
          sns_smgr_handle_new_sample(ddf_sensor_ptr, &data);
          sns_smgr_check_depot_full(ddf_sensor_ptr, 1);
          sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
        }
        ddf_sensor_ptr->max_skipped_samples =
          MAX(ddf_sensor_ptr->max_skipped_samples, num_skipped_samples);
        if ( num_skipped_samples > 0 )
        {
          SNS_SMGR_PRINTF3(ERROR, "sampling_sched - ddf_sensor=%d skipped=%d max=%d",
                           SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr,
                                            ddf_sensor_ptr->data_type),
                           num_skipped_samples, ddf_sensor_ptr->max_skipped_samples);
        }
      } /* for each sensor type in schedule block */

      sched_blk_ptr->next_tick =
        (uint32_t)((sns_smgr.sched_tick.tick64 + SMGR_SCHEDULE_GRP_TOGETHER_TICK +
                    sched_blk_ptr->sched_intvl) /
                   sched_blk_ptr->sched_intvl * sched_blk_ptr->sched_intvl);

    } /* ( sns_smgr.sched_tick.u.low_tick + SMGR_SCHEDULE_GRP_TOGETHER_TICK..*/
    next_tick_offset = MIN(next_tick_offset,
                           sched_blk_ptr->next_tick - sns_smgr.sched_tick.u.low_tick);
  } /* for each schedule block */

  sns_hw_set_qup_clk(false);

  return next_tick_offset;
}

/*===========================================================================

  FUNCTION:   sns_smgr_sampling_cycle

===========================================================================*/
/*!
  @brief  plans the the next schedule time and processing each sechedule which are:
          - event_schedule
          - cic_schedule
          - report_schedule

  @param[i] NONE

  @return
    NONE

*/
/*=========================================================================*/
void sns_smgr_sampling_cycle(void)
{
  uint32_t next_tick_offset;
  uint32_t time_now = sns_em_get_timestamp();

  sns_profiling_log_qdss(SNS_SMGR_FUNC_ENTER, 1, SNS_SMGR_SENSOR_READ_SIG);

  if ( ( time_now + SMGR_TOO_SHORT_TICKS_FOR_TIMER -
         sns_smgr.sched_tick.u.low_tick ) > SMGR_MAX_TICKS )
  {
    SNS_SMGR_PRINTF2(
      LOW, "sampling_cycle - sched=%u now=%u",
      sns_smgr.sched_tick.u.low_tick, time_now);
    return;
  }

  /* Process sampling schedule */
  next_tick_offset = sns_smgr_proc_sampling_schedule();

  if ( next_tick_offset < SMGR_MAX_TICKS )
  {
    uint32_t    tick_offset_for_timer;
    smgr_tick_s now_tick;

    sns_smgr.sched_tick.tick64 += next_tick_offset;
    now_tick.tick64 = sns_smgr_get_tick64();
    /* If the scheduling time was passed already, set it by the current time */
    sns_smgr.sched_tick.tick64 = MAX(sns_smgr.sched_tick.tick64, now_tick.tick64);

    tick_offset_for_timer =  sns_smgr.sched_tick.u.low_tick - now_tick.u.low_tick;

    SNS_SMGR_SAMPLING_DBG2(
      LOW, "sampling_cycle - offset(%u) real(%u)",
      next_tick_offset, tick_offset_for_timer);

    if ( (tick_offset_for_timer - SMGR_TOO_SHORT_TICKS_FOR_TIMER) > SMGR_MAX_TICKS )
    {
      sns_smgr_signal_me(SNS_SMGR_SENSOR_READ_SIG);
    }
    else
    {
      sns_em_cancel_utimer(sns_smgr.tmr_obj);
      if ( SNS_ERR_FAILED ==
           sns_em_register_utimer(sns_smgr.tmr_obj, tick_offset_for_timer) )
      {
        SNS_SMGR_PRINTF0(ERROR, "sampling_cycle - register_timer failed");
      }
    }
  }
}

