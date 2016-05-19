/*=============================================================================
  @file sns_smgr_util.c

  This file implements the utility functions of Sensor Manager

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_util.c#2 $ */
/* $DateTime: 2015/05/14 20:46:38 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-04-21  pn   Fixed deficient depot copy method
  2014-11-24  pn   Removed debug printf from sns_smgr_copy_uimg_depot()
  2014-11-19  pn   Updated sns_smgr_get_max_sample_count()
  2014-11-11  pn   No longer clears flags when setting sensor state to OFF
  2014-10-26  pn   Changed sns_smgr_depot_dump() signature
  2014-09-25  pn   Added support for bigImage depots
  2014-09-08  pn   Clears sensors flags when they're set to OFF state
  2014-06-26  pn   Removed obsolete HP ODR table
  2014-06-16  pn   Used updated DDF sensor's client_status structure
  2014-06-05  vy   Further refactored to support uImage
  2014-05-28  tc   SubHz Sampling
  2014-04-23  pn   Initial version

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_em.h"
#include "sns_memmgr.h"
#include "sns_osa.h"
#include "sns_rh_sol.h"
#include "sns_smgr_main.h"
#include "sns_smgr_priv.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Function Prototypes
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   smgr_load_default_cal

===========================================================================*/
/*!
  @brief CTemporary function to load default calibration. Modify when final cal
    structure is in place
  @detail

  @param Cal_p Calibration pointer
  @return
   none
 */
/*=========================================================================*/
void sns_smgr_load_default_cal(sns_smgr_cal_s* cal_ptr)
{
  uint32  i;
  for ( i=0; i<ARR_SIZE(cal_ptr->zero_bias); i++ )
  {
    cal_ptr->zero_bias[i]    = 0;
    cal_ptr->scale_factor[i] = FX_FLTTOFIX_Q16(1.0);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_get_sched_intval

===========================================================================*/
/*!
  @brief Calculate an interval from requested freq

  @detail If the freq is factor of SMGR_ALIGN_FREQ, align its interval.
  @param[i] req_freq - The freq in Hz, in Q16 format

  @return
   The timetick of the scheduling period
*/
/*=========================================================================*/
uint32_t sns_smgr_get_sched_intval(q16_t req_freq)
{
  uint32_t interval_tick;

  /* check if the freq is factor of SMGR_ALIGN_FREQ, and align its interval */
  if ( 0 == (SMGR_ALIGN_FREQ_Q16 % req_freq) )
  {
    uint32_t us_per_tick = sns_em_convert_dspstick_to_usec(1);
    interval_tick = 1000000/us_per_tick/SMGR_ALIGN_FREQ;
    interval_tick *= SMGR_ALIGN_FREQ_Q16/req_freq;
  }
  else
  {
    /* Cannot directly convert DSPS_SLEEP_CLK to Q16 due to overflow.
       Just going to manually apply the left-shifts instead. */
    interval_tick = (DSPS_SLEEP_CLK << FX_QFACTOR)/((uint32_t) req_freq);
  }
  return interval_tick;
}

/*===========================================================================

  FUNCTION:   sns_smgr_find_sensor_by_driver_uuid

===========================================================================*/
/*!
  @brief Finds the associated sensor structure given a device driver UUID.

  @param[i] uuid - the device driver UUID passed in via Sensor1 API
 
  @return
   sensor structure, or NULL if not found
 */
/*=========================================================================*/
sns_smgr_sensor_s* sns_smgr_find_sensor_by_driver_uuid(uint8_t uuid[16])
{
  sns_smgr_sensor_s* sensor_ptr = NULL;
  uint8_t i;
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor) && sensor_ptr==NULL; i++ )
  {
    if ( SNS_OS_MEMCMP(uuid, sns_smgr.sensor[i].const_ptr->uuid, 16) == 0 )
    {
      SNS_SMGR_PRINTF4(
        LOW,"found driver uuid = %x %x %x %x", uuid[0], uuid[1], uuid[2], uuid[3]);
      sensor_ptr = &sns_smgr.sensor[i];
    }
  }
  return sensor_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_find_ddf_sensor

===========================================================================*/
/*!
  @brief Finds the associated DDF sensor structure given a sensor ID
         and data type.

  @detail
  @param[i] sensor_id - the sensor ID passed in via Sensor1 API
  @param[i] data_type - the data type passed in via Sensor1 API
 
  @return
   DDF sensor structure, or NULL if not found
 */
/*=========================================================================*/
sns_smgr_ddf_sensor_s* sns_smgr_find_ddf_sensor(
  smgr_sensor_id_e sensor_id,
  uint8_t          data_type)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = NULL;
  if ( (data_type == SNS_SMGR_DATA_TYPE_PRIMARY_V01) || 
       (data_type == SNS_SMGR_DATA_TYPE_SECONDARY_V01) )
  {
    sns_smgr_sensor_s* sensor_ptr = sns_smgr_find_sensor(sensor_id);
    if ( sensor_ptr != NULL )
    {
      ddf_sensor_ptr = sensor_ptr->ddf_sensor_ptr[data_type];
    }
  }
  return ddf_sensor_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_set_sensor_state

===========================================================================*/
/*!
  @brief Changes the state of the given sensor

  @Detail

  @param[i] sensor_ptr: the sensor whose state should be changed
  @param[i] state: the state to which to change

  @return
   NONE
*/
/*=========================================================================*/
void sns_smgr_set_sensor_state(
  sns_smgr_sensor_s* sensor_ptr, 
  sns_smgr_sensor_state_e state)
{
  if ( state != sensor_ptr->sensor_state )
  {
    SNS_SMGR_PRINTF4(
      HIGH, "set_sensor_state - sensor=%u was=%u now=%u flags=0x%x",
      SMGR_SENSOR_ID(sensor_ptr), sensor_ptr->sensor_state, state, sensor_ptr->flags);
    sensor_ptr->sensor_state = state;
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_set_all_sensors_state

===========================================================================*/
/*!
  @brief Changes all sensors to the given state

  @Detail

  @param[i] state: the state to which to change

  @return
   NONE
*/
/*=========================================================================*/
void sns_smgr_set_all_sensors_state(sns_smgr_sensor_state_e state)
{
  sns_smgr_sensor_s* sensor_ptr;
  uint8_t        i;
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor); i++ )
  {
    sensor_ptr = &sns_smgr.sensor[i];
    if ( sensor_ptr->sensor_state != SENSOR_STATE_FAILED )
    {
      sns_smgr_set_sensor_state(sensor_ptr, state);
      if ( state == SENSOR_STATE_OFF )
      {
        sensor_ptr->event_done_tick = 0;
      }
    }
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_get_adjacent_odrs

===========================================================================*/
/*!
  @brief Returns the two adjacent ODRs of the given frequency.

  @details If the given ODR is present, it is returned as both adjacent ODRs.

  @param[i] sensor_ptr    - the sensor of interest
  @param[i] frequency     - the base frequency, in Q16 format
  @param[o] adjacent_odrs - array of 2 for the next lower and higher ODRs
                            relative to the given ODR

  @return
   none
 */
/*=========================================================================*/
void sns_smgr_get_adjacent_odrs(
  const sns_smgr_sensor_s* sensor_ptr,
  q16_t                    frequency,
  uint32_t                 adjacent_odrs[2])
{
  sns_ddf_odr_t odr = DDF_FIXTOODR_CEIL_Q16(frequency);

  adjacent_odrs[0] = adjacent_odrs[1] = 0;

  if ( (frequency > 0) && (sensor_ptr->num_odrs > 0) )
  {
    int8_t i;
    for ( i=sensor_ptr->num_odrs-1; i>=0 && adjacent_odrs[0]==0; i-- )
    {
      if ( odr >= sensor_ptr->supported_odrs[i] )
      {
        adjacent_odrs[0] = sensor_ptr->supported_odrs[i];
      }
    }
    for ( i=0; i<sensor_ptr->num_odrs && adjacent_odrs[1]==0; i++ )
    {
      if ( odr <= sensor_ptr->supported_odrs[i] )
      {
        adjacent_odrs[1] = sensor_ptr->supported_odrs[i];
      }
    }
  }
  SNS_SMGR_PRINTF4(
    MED, "get_adj_odrs - lower=%u given=0x%X/%u higher=%u",
    (unsigned)adjacent_odrs[0], frequency, odr, (unsigned)adjacent_odrs[1]);
}

/*===========================================================================

  FUNCTION:   sns_smgr_choose_odr

===========================================================================*/
/*!
  @brief Chooses the appropriate ODR to be set for the given sensor.

  @details The chosen ODR must be high enough to support the max requested
           frequency of the sensor and its sibling.  However, to save power,
           a lower ODR that is within the delta threshold can be chosen.

  @param[i] sensor_ptr - the sensor of interest

  @return the chosen ODR
 */
/*=========================================================================*/
sns_ddf_odr_t sns_smgr_choose_odr(const sns_smgr_sensor_s* sensor_ptr)
{
  uint8_t odr_idx = 0;
  sns_ddf_odr_t adjacent_odrs[2] = {0, 0};
  q16_t odr_delta[2];
  q16_t odr_threshold_delta;
  q16_t max_rate;

  max_rate = smgr_get_max_requested_freq(sensor_ptr);
  if ( (sensor_ptr->num_lpf > 0) || sensor_ptr->odr_attr_supported )
  {
    odr_threshold_delta = FX_MUL_Q16(max_rate, 
                                     FX_FLTTOFIX_Q16(SMGR_ODR_THRESHOLD_DELTA_PCT));
    odr_threshold_delta = FX_DIV_Q16(odr_threshold_delta, FX_FLTTOFIX_Q16(100));

    sns_smgr_get_adjacent_odrs(sensor_ptr, max_rate, adjacent_odrs);
    odr_delta[0] = max_rate - DDF_ODRTOFIX_Q16(adjacent_odrs[0]);
    odr_delta[1] = DDF_ODRTOFIX_Q16(adjacent_odrs[1]) - max_rate;
    if ( (odr_delta[0] > odr_delta[1]) || (odr_delta[0] > odr_threshold_delta) )
    {
      odr_idx = 1;
    }
  }
  else
  {
    adjacent_odrs[odr_idx] = DDF_FIXTOODR_CEIL_Q16(max_rate);
  }
  SNS_SMGR_PRINTF2(
    LOW, "choose_odr - sensor=%d odr=%u",
    SMGR_SENSOR_ID(sensor_ptr), (unsigned)adjacent_odrs[odr_idx]);
  return adjacent_odrs[odr_idx];
}


/*===========================================================================

  FUNCTION:   sns_smgr_compute_depot_data_rate

===========================================================================*/
/*!
  @details

  @param[i] ddf_sensor_ptr  ddf sensor

  @return depot data rate (in Q16 Hz)
*/
/*=========================================================================*/
q16_t sns_smgr_compute_depot_data_rate(
  const sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  q16_t depot_data_rate;
  if ( SMGR_SENSOR_IS_SELF_SCHED(ddf_sensor_ptr->sensor_ptr) )
  {
    depot_data_rate =
      DDF_ODRTOFIX_Q16(ddf_sensor_ptr->current_odr) / 
      ddf_sensor_ptr->device_sampling_factor;
      /* in DRI mode, when there is any request for accurate timestamp or
       for CIC filtering, sampling_factor would be 1, and depot_data_rate
       would equal ODR */
  }
  else
  {
    const sns_smgr_client_stat_s* client_stat_ptr = &ddf_sensor_ptr->client_stat;

    if (  SMGR_BIT_TEST(client_stat_ptr->flags, RH_RPT_ITEM_FLAGS_DECIM_FILTER_B) &&
         (DDF_ODRTOFIX_Q16(ddf_sensor_ptr->current_odr) > 
          client_stat_ptr->max_requested_freq_hz) )
    {
      depot_data_rate = 
        FX_MUL_Q16(client_stat_ptr->max_requested_freq_hz,
                   FX_DIV_Q16(DDF_ODRTOFIX_Q16(ddf_sensor_ptr->current_odr), 
                              client_stat_ptr->max_requested_freq_hz));
    }
    else
    {
      depot_data_rate = client_stat_ptr->max_requested_freq_hz;
    }
  }
  SNS_SMGR_PRINTF3(
    MED, "compute_depot_rate - ddf_sensor=%d odr=%u depot_rate=0x%X",
    SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr, ddf_sensor_ptr->data_type),
    (unsigned)ddf_sensor_ptr->current_odr, depot_data_rate);

  return depot_data_rate;
}

/*=========================================================================
  FUNCTION:  sns_smgr_put_next_request
  =========================================================================*/
void sns_smgr_put_next_request(
  sns_smgr_sensor_s*            sensor_ptr,
  sns_smgr_request_response_s*  req_resp_ptr)
{
  sns_q_link(req_resp_ptr, &req_resp_ptr->q_link);
  sns_os_mutex_pend(sensor_ptr->request_queue.mutex_ptr, 0, NULL);
  sns_q_put(&sensor_ptr->request_queue.protected_q, &req_resp_ptr->q_link);
  (void)sns_os_mutex_post(sensor_ptr->request_queue.mutex_ptr );

  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*=========================================================================
  FUNCTION:  sns_smgr_get_next_request
  =========================================================================*/
sns_smgr_request_response_s* sns_smgr_get_next_request(
  sns_smgr_sensor_s*            sensor_ptr)
{
  sns_smgr_request_response_s* req_ptr = NULL;

  sns_os_mutex_pend(sensor_ptr->request_queue.mutex_ptr, 0, NULL);
  req_ptr = 
    (sns_smgr_request_response_s*)sns_q_get(&sensor_ptr->request_queue.protected_q);
  (void)sns_os_mutex_post(sensor_ptr->request_queue.mutex_ptr );

  return req_ptr;
}

/*=========================================================================
  FUNCTION:  sns_smgr_get_self_test_result
  =========================================================================*/
void sns_smgr_get_self_test_result(sns_smgr_self_test_result_s* result_ptr)
{
  *result_ptr = sns_smgr.self_test.result;
}

/*===========================================================================

  FUNCTION:   smgr_get_max_requested_freq

===========================================================================*/
/*!
  @brief Returns the max requested frequency of all sensor types

  @param[i] sensor_ptr - the sensor leader structure

  @return The highest requested frequency (in Q16 Hz)
*/
/*=========================================================================*/
q16_t smgr_get_max_requested_freq(const sns_smgr_sensor_s* sensor_ptr)
{
  uint8_t i;
  q16_t max_freq = 0;
  for ( i=0; i<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); i++ )
  {
    if ( sensor_ptr->ddf_sensor_ptr[i] != NULL )
    {
      max_freq = MAX(max_freq,
                     sensor_ptr->ddf_sensor_ptr[i]->client_stat.max_requested_freq_hz);
    }
  }
  return max_freq;
}

/*===========================================================================

  FUNCTION:   smgr_sensor_type_max_odr

===========================================================================*/
/*!
  @brief Returns the max ODR value of all sensor types

  @Detail

  @param[i] sensor_ptr - the sensor leader structure

  @return
    NONE
*/
/*=========================================================================*/
uint32_t smgr_sensor_type_max_odr(const sns_smgr_sensor_s* sensor_ptr)
{
  uint32_t max_odr = 0;
  uint32_t i;

  for ( i = 0; i < ARR_SIZE(sensor_ptr->ddf_sensor_ptr); i++ )
  {
    if ( sensor_ptr->ddf_sensor_ptr[i] != NULL )
    {
      max_odr = MAX(max_odr, sensor_ptr->ddf_sensor_ptr[i]->current_odr);
    }
  }
  return max_odr;
}

/*===========================================================================

  FUNCTION:   sns_smgr_get_max_req_freq

===========================================================================*/
/*!
  @brief Returns the max requested frequency of all sensors

  @param None

  @return The highest requested frequency (in Q16 Hz)
*/
/*=========================================================================*/
q16_t sns_smgr_get_max_req_freq(void)
{
  q16_t max_freq = 0;
  uint32_t i;

  for ( i=0; i < ARR_SIZE(sns_smgr.sensor); i++ )
  {
    max_freq = MAX(max_freq, smgr_get_max_requested_freq(&sns_smgr.sensor[i]));
  }
  return max_freq;
}

/*===========================================================================

  FUNCTION:   sns_smgr_get_max_sample_count

===========================================================================*/
/*!
  @brief Returns the depth of the depot into which new samples are to be deposited.

  @param ddf_sensor_ptr - the sensor whose depots are considered

  @return Depth of uImage depot if it exists, else depth of big-image depot.
*/
/*=========================================================================*/
uint16_t sns_smgr_get_max_sample_count(const sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  uint16_t max_sample_count;
  if ( ddf_sensor_ptr->uimg_depot_ptr != NULL )
  {
    max_sample_count = sns_smgr_depot_get_depth(ddf_sensor_ptr->uimg_depot_ptr);
  }
  else
  {
    max_sample_count = sns_smgr_depot_get_depth(ddf_sensor_ptr->bimg_depot_ptr);
  }
  SNS_SMGR_PRINTF1(LOW, "get_max_sample_count - %u", max_sample_count);
  return max_sample_count;
}

/*===========================================================================

  FUNCTION:   sns_smgr_copy_uimg_depot

===========================================================================*/
/*!
  @brief Transfers samples from uImge depot to big-image depot of the given sensor

  @param ddf_sensor_ptr - the sensor on which to operate

  @return none
*/
/*=========================================================================*/
void sns_smgr_copy_uimg_depot(sns_smgr_ddf_sensor_s* ddf_sensor_ptr)
{
  sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
  if ( ddf_sensor_ptr->num_new_samples > 0 )
  {
    sns_profiling_log_qdss(
      SNS_SMGR_COPY_DEPOT, 2, SMGR_SENSOR_ID(ddf_sensor_ptr->sensor_ptr), 
      ddf_sensor_ptr->num_new_samples);
    sns_smgr_depot_dump(ddf_sensor_ptr->uimg_depot_ptr, 
                        ddf_sensor_ptr->bimg_depot_ptr);
    ddf_sensor_ptr->num_new_samples = 0;
    ddf_sensor_ptr->uimg_depot_full_alert = false;
  }
  sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
}

