/*=============================================================================
  @file sns_smgr_ddf_if.c

  This file implements the interface between SMGR and DDF

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_ddf_if_uimg.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-08  pn   Remembers and votes for current image mode when exiting big image
  2014-08-25  vy   Enabled QDSS logging
  2014-08-24  vy   Added an api to get uimage status of driver using sns handle
  2014-08-05  pn   Let RH task processs ODR_CHANGED event before SMGR task does
  2014-07-31  pn   Obsoleted FEATURE_TEST_DRI
  2014-07-27  vy   Moved sns_ddf_smgr_notify_event to uImage code
  2014-07-14  VY   Fixed a compiler error
  2014-07-20  VY   Disabled logging in uImage
  2014-07-09  vy   Refactored to support uImage
  2014-04-23  pn   Initial version

============================================================================*/


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#ifdef SNS_USES_ISLAND
#include "qurt_island.h"
#endif

#include "sns_ddf_signal.h"
#include "sns_em.h"
#include "sns_profiling.h"
#include "sns_rh_util.h"
#include "sns_smgr_ddf_if.h"
#include "sns_smgr_main.h"
#include "sns_smgr_pm_if.h"
#include "sns_smgr_priv.h"
#include "sns_smgr_reg.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Global Variables
 * -------------------------------------------------------------------------*/
extern sns_smgr_s              sns_smgr;

#ifdef SNS_QDSP_SIM
extern sns_dri_sim_s sns_dri_sim;
extern bool md_int_happened;
#endif

/*----------------------------------------------------------------------------
 *  Local Functions
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_timer

===========================================================================*/
/*!
  @brief DDF, device driver call back. Entered on interrupt.
    Queue the argument

  @detail

  @param[i]  timer
  @return   none
 */
/*=========================================================================*/
void sns_ddf_smgr_notify_timer(void* timer)
{
  int32_t dif;

  /* ---------------------------------------------------------------------- */

  if ( (dif = sns_smgr.timer_que_out - sns_smgr.timer_que_in) < 0 )
  {
    dif += SNS_SMGR_TIMER_QUEUE_SIZE;
  }
  /* Queue only if that will not use up the last empty slot */
  if ( 1 != dif )
  {
    sns_smgr.timer_que[sns_smgr.timer_que_in++] = timer;
  }
  if ( sns_smgr.timer_que_in >= SNS_SMGR_TIMER_QUEUE_SIZE )
  {
    sns_smgr.timer_que_in = 0;
  }
  sns_smgr_signal_me(SNS_SMGR_DD_SERVICE_SIG);
}


/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_irq

===========================================================================*/
/*!
  @brief DDF, device driver call back. Entered on interrupt.
    Queue the argument

  @detail  After Driver registers callback with DDF.
    ISR calls sns_ddf_smgr_notify_irq, irq gets queued
    sns_smgr_dd_service gets called in SMGR context, and calls sns_ddf_signal_dispatch()
    DDF calls the driver's registered callback
    Finally, if the driver has an event (like motion detect)
    it'll call sns_ddf_smgr_notify_event to let SMGR know

  @param[i]  param  interrupt param
  @return   none
 */
/*=========================================================================*/
void sns_ddf_smgr_notify_irq(uint32_t param)
{
  sns_profiling_log_qdss(SNS_SMGR_NOTIFY_IRQ, 1, param);
  sns_ddf_signal_post(param);

  // Notify the SMGR task that a driver interrupt requires handling.
  sns_smgr_signal_me(SNS_SMGR_DD_SERVICE_SIG);
}


/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_data

===========================================================================*/
/*!
  @brief  A device driver calls this function to deliver data that was previously
    requested using get_data()

  @Detail

  @param[i] smgr_handle - A value supplied when initializing the device driver. It is the
                         index to the sensor structures
  @param[i] data - pointer to an array of data types (known as sensors in DDF)
  @param[i] data_len - Number of data types
  @return
   SNS_DDF_SUCCESS
   SNS_DDF_EFAIL
*/
/*=========================================================================*/
sns_ddf_status_e sns_ddf_smgr_notify_data (
    sns_ddf_handle_t       smgr_handle,
    sns_ddf_sensor_data_s  data[],
    uint32_t               data_len)
{
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  sns_smgr_sensor_s* sensor_ptr = (sns_smgr_sensor_s*)smgr_handle;

  /* ---------------------------------------------------------------------- */

  if ( sensor_ptr->const_ptr->flags & SNS_REG_SSI_FLAG_LTCY_ENABLE )
  {
    sns_latency.dri_get_data_end_ts = sns_em_get_timestamp();
    sns_latency.dri_notify_irq_ts = data[0].timestamp;
    //sns_profiling_log_latency_dri(sns_latency, data[0].sensor);
  }
  if ( SMGR_HANDLE_VALID(sensor_ptr) &&
       (data_len <= SMGR_MAX_DATA_TYPES_PER_DEVICE) )
  {
    uint8_t i;
    for ( i = 0; i < data_len; i++ )
    {
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
        sns_smgr_match_ddf_sensor(sensor_ptr, data[i].sensor);
      if ( ddf_sensor_ptr != NULL )
      {
        smgr_process_dri_fifo_async_data(ddf_sensor_ptr, &data[i]);
      }
    }
    status = SNS_DDF_SUCCESS;
  }
  return status;
}


/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_event

===========================================================================*/
/*!
  @brief  A device driver calls this function to deliver an event

  @Detail

  @param[i] smgr_handle  smgr handle passed to DD
  @param[i] sensor  sensor enum
  @param[i] event   event name
  @return
   SNS_DDF_SUCCESS
   SNS_DDF_EINVALID_PARAM if event with the sensor is not expected
*/
/*=========================================================================*/
sns_ddf_status_e sns_ddf_smgr_notify_event(
    sns_ddf_handle_t  smgr_handle,
    sns_ddf_sensor_e  sensor,
    sns_ddf_event_e   event)
{
  sns_smgr_sensor_s*    sensor_ptr = (sns_smgr_sensor_s*)smgr_handle;
  sns_ddf_status_e  rc = SNS_DDF_SUCCESS;

  /* ---------------------------------------------------------------------- */
  if( SMGR_HANDLE_VALID(sensor_ptr) && event == SNS_DDF_EVENT_FIFO_WM_INT )
  {
    rc = sns_smgr_fifo_on_event_fifo_wm_int( sensor_ptr, sensor );
  }
  else
  {
    sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
    sns_smgr_vote_image_mode(SNS_IMG_MODE_BIG);
    rc = sns_smgr_notify_event_in_bigimage(smgr_handle, sensor, event);
    sns_smgr_vote_image_mode(curr_mode);
  }
  
  return rc;
}


/*===========================================================================  

  FUNCTION:   sns_ddf_smgr_is_in_uimage

===========================================================================*/  
/*!
 * @brief Gets from SMGR if it is in uImage mode
 *
 * @param[in]  None.
 *
 * @return True if in uImage mode, False otherwise
 * */ 
/*=========================================================================*/ 
bool sns_ddf_smgr_is_in_uimage(
  void)
{
  unsigned int retval = 0; 

#ifdef SNS_USES_ISLAND
  retval = qurt_island_get_status(); 
  // qurt_island_get_status = {1=uImage, 0=BigImage}
#endif

  return (bool)retval;
}


/*===========================================================================

  FUNCTION:   sns_smgr_get_uimg_refac

===========================================================================*/
/*!
  @brief This function returns the uimage refac status for a particular sensor

  @detail Must return false if handle is NULL

  @param   pointer to sensor data 
  @return  return TRUE if refac for uimage else FALSE
 */
/*=========================================================================*/
bool sns_smgr_get_uimg_refac(sns_ddf_handle_t sensor_handle)
{
  sns_smgr_sensor_s *sensor_ptr;
  if (sensor_handle == NULL)
  {
    return false;
  }
  else
  {
    sensor_ptr = (sns_smgr_sensor_s *)sensor_handle; 
    return (sensor_ptr->is_uimg_refac);
  }  
}

