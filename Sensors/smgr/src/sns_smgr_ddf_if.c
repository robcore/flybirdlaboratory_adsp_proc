/*=============================================================================
  @file sns_smgr_ddf_if.c

  This file implements the interface between SMGR and DDF

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_ddf_if.c#2 $ */
/* $DateTime: 2014/12/05 22:23:17 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-12-05  pn   Added sns_smgr_set_power_attr()
  2014-09-14  vy   Used new uImage supported DDF api to free memhandler
  2014-08-08  pn   Replaced SMGR_U_ALLOC_STRUCT with SMGR_ANY_ALLOC_STRUCT
  2014-07-27  vy   Moved sns_ddf_smgr_notify_event to uImage code
  2014-07-09  vy   Further refactored to support uImage mode
  2014-06-16  pn   Modified sns_smgr_update_sampling_setting() signature
  2014-05-07  pn   Added support for MD deregistration
  2014-04-23  pn   Initial version

============================================================================*/


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_em.h"
#include "sns_osa.h"
#include "sns_memmgr.h"

#include "sns_ddf_signal.h"
#include "sns_log_types.h"
#include "sns_log_api.h"

#include "sns_rh_util.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_priv.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"
#include "sns_smgr_ddf_if.h"
#include "sns_smgr_reg.h"

#include "sns_profiling.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
#ifdef SNS_QDSP_SIM
extern sns_dri_sim_s sns_dri_sim;
extern bool md_int_happened;
#endif

/*----------------------------------------------------------------------------
 *  Local Functions
 * -------------------------------------------------------------------------*/

#ifdef SNS_QDSP_SIM
#define QDSP_PLAYBACK_SENSOR_READY_TIME_US 1000 

/*===========================================================================

  FUNCTION:   sns_simulate_dri

===========================================================================*/
 /**
     * @brief Simulates Sensor device Data Ready Interrupts (DRI) for
     *        QDSP SIM Playback.
     */
/*=========================================================================*/
SMGR_STATIC void sns_simulate_dri(void *argPtr)
{
  uint8_t err=0;
  sns_dri_sim.sns_dri_sig_grp = sns_os_sigs_create(SNS_DRI_SIMULATE, &err);

  SMGR_DELAY_US(QDSP_PLAYBACK_SENSOR_READY_TIME_US);

  while(1) 
  {
    sns_ddf_smgr_notify_irq(0);
    sns_os_sigs_pend(sns_dri_sim.sns_dri_sig_grp, SNS_DRI_SIMULATE,
                     OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);
    if(md_int_happened)
    {
        SMGR_DELAY_US(QDSP_PLAYBACK_SENSOR_READY_TIME_US); 
    }
  }
}
#endif

/*===========================================================================

  FUNCTION:   sns_smgr_log_md_irq

===========================================================================*/
/*!
  @brief Log an occurence of a motion detect interrupt.

  @detail Logs the last recorded timestamp, saved by SMGR at the time the
          last motion detect interrupt time ocurred.
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_log_md_irq(uint32_t md_timestamp)
{
  // Currently the threshold used for motion detect is neither configurable nor
  // retrievable. It is simply hard-coded in the driver as 48mG.
  const uint8_t md_accel_threshold = 48;
  sns_err_code_e status;
  sns_log_md_irq_s* log;

  /* ---------------------------------------------------------------------- */

  status = sns_logpkt_malloc(SNS_LOG_DRV_MD_IRQ, sizeof(sns_log_md_irq_s), 
                             (void**)&log);
  if ( status == SNS_SUCCESS && log != NULL )
  {
    log->version = SNS_LOG_MD_IRQ_VERSION;
    log->timestamp = md_timestamp;
    log->threshold = md_accel_threshold;
    sns_logpkt_commit(SNS_LOG_DRV_MD_IRQ, log);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_dd_handle_md_int

===========================================================================*/
/*!
  @brief MD int handler

  @detail Disable MD interrupt, send indication etc.

  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_dd_handle_md_int(sns_smgr_sensor_s* sensor_ptr)
{
  uint32_t ts = sns_em_get_timestamp();

  SNS_SMGR_PRINTF3(
    HIGH, "MD int handler - sensor=%d state=%d ts=%u",
    SMGR_SENSOR_ID(sensor_ptr), sensor_ptr->sensor_state, (unsigned)ts);

  sns_smgr_log_md_irq(ts);
  if ( sensor_ptr->sensor_state == SENSOR_STATE_MD )
  {
    uint32_t set_data;
    sns_smgr_set_sensor_state(sensor_ptr, SENSOR_STATE_IDLE);

    set_data = (uint32_t)false;
    sns_smgr_set_attr(
      sensor_ptr, SNS_DDF_SENSOR_ACCEL, SNS_DDF_ATTRIB_MOTION_DETECT, &set_data);

    if ( smgr_get_max_requested_freq(sensor_ptr) == 0 )
    {
      sns_smgr_set_power_attr(sensor_ptr, SNS_DDF_POWERSTATE_LOWPOWER);
    }
    sns_rh_signal_me(SNS_RH_MD_INT_SIG);
  }
  sns_smgr_update_power_state();
}

/*----------------------------------------------------------------------------
 * Global Functions
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_daf_ind

===========================================================================*/
/**
 * @brief Notifies a Sensor1 client of a Driver Access message from the driver.
 *        Asynchronous API.
 *
 * @param[in]  ind_id        Indication identifier.
 * @param[in]  ind_msg       Pointer to the Indication message. This is allocated
 *                           by the device driver and must be freed by the driver
 *                           upon returning from this function!
 * @param[in]  ind_size      The number of bytes in @ind_msg. If there is no
 *                           indication message for the indication, then this
 *                           will be 0 to show that the DAF indication is not
 *                           present. This cannot be larger than
 *                           @SNS_SMGR_MAX_DAF_MESSAGE_SIZE_V01 bytes. If it is
 *                           the indication message will be truncated.
 * @param[in]  trans_id_ptr  Pointer to the transaction identifier. If there is
                             no transaction ID, this field will be null.
 * @param[in]  conn_handle   The connection handle for the request message.
 *                           This value must be saved by the device driver if the
 *                           corresponding request is expected to generate
 *                           indications. Upon notifying the SMGR of an
 *                           indication, this value must be provided to the SMGR
 *                           so the SMGR can forward the indication to the client.
 *
 * @return Success if the message was correctly sent. Otherwise a specific
 *         error code is returned.
 */
/*=========================================================================*/
sns_ddf_status_e sns_ddf_smgr_notify_daf_ind(
  uint32_t               ind_id,
  const void*            ind_msg,
  uint32_t               ind_size,
  const uint8_t*         trans_id_ptr,
  void*                  conn_handle)
{
  sns_smgr_indication_s* smgr_ind_ptr;
  sns_smgr_driver_access_ind_msg_v01* ind_ptr;

  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF2(MED, "DAF Indication ID: %d  size: %d", ind_id, ind_size);

  if ( conn_handle == NULL || (ind_msg == NULL && ind_size > 0) )
  {
    SNS_SMGR_PRINTF3(
      ERROR, "notify_daf_ind - conn_handle=0x%x ind_msg=0x%x ind_size=%u",
      conn_handle, ind_msg, ind_size);
    return SNS_DDF_EINVALID_PARAM;
  }

  // Allocate the indication message
  smgr_ind_ptr = SMGR_ANY_ALLOC_STRUCT(sns_smgr_indication_s);

  if (smgr_ind_ptr == NULL)
  {
    return SNS_DDF_ENOMEM;
  }

  smgr_ind_ptr->conn_handle = conn_handle;
  smgr_ind_ptr->msg_id = SNS_SMGR_DRIVER_ACCESS_IND_V01;
  smgr_ind_ptr->ind_len = sizeof(sns_smgr_driver_access_ind_msg_v01);

  ind_ptr = &smgr_ind_ptr->ind.driver_access;
  ind_ptr->IndicationId = ind_id;

  if ( ind_size > 0 )
  {
    ind_ptr->IndicationMsg_valid = true;
    ind_ptr->IndicationMsg_len = 
      SNS_OS_MEMSCPY(ind_ptr->IndicationMsg, sizeof(ind_ptr->IndicationMsg), 
                     ind_msg, ind_size);
    // Check for overflow condition
    if ( ind_ptr->IndicationMsg_len < ind_size )
    {
      // TODO: CONSIDER ADDING AN ERROR CODE FOR "MESSAGE TOO LARGE FOR BUFFER"
      SNS_SMGR_PRINTF2(ERROR, "Indication size of %d is truncated to %d", 
                       ind_size, ind_ptr->IndicationMsg_len);
    }
  }

  if ( trans_id_ptr != NULL )
  {
    ind_ptr->TransactionId_valid = true;
    ind_ptr->TransactionId = *trans_id_ptr;
  }

  // Forward the indication message to Request Handler
  sns_rh_put_next_indication(smgr_ind_ptr);

  return SNS_DDF_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_ddf_smgr_notify_test_complete

===========================================================================*/
/*!
  @brief  A device driver calls this function to notify the completion of
    a factory test which was previously requested using run_test()

  @Detail

  @param[i] smgr_handle  smgr handle passed to DD
  @param[i] sensor  sensor enum
  @param[i] status  pass or fail
  @param[i] err     driver-specific error code

  @return
   SNS_DDF_SUCCESS
   DDF error codes
*/
/*=========================================================================*/
sns_ddf_status_e sns_ddf_smgr_notify_test_complete(
    sns_ddf_handle_t  smgr_handle,
    sns_ddf_sensor_e  sensor,
    sns_ddf_status_e  status,
    uint32_t          err)
{
  sns_smgr_sensor_s* sensor_ptr = (sns_smgr_sensor_s*)smgr_handle;

  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF3(MED, "notify_test_cmplt - sensor=%d status=%d err=%u",
                   sensor, status, (unsigned)err);

  if ( !SMGR_HANDLE_VALID(sensor_ptr) ||
       (sns_smgr.self_test.ddf_sensor_ptr == NULL) ||
       (sensor_ptr != sns_smgr.self_test.ddf_sensor_ptr->sensor_ptr) )
  {
    return SNS_DDF_EINVALID_PARAM;
  }

  sns_smgr.self_test.result.result = (status == SNS_DDF_SUCCESS)
     ? SNS_SMGR_TEST_STATUS_SUCCESS_V01 : SNS_SMGR_TEST_STATUS_FAIL_V01;
  sns_smgr.self_test.result.test_specific_error = err;

  SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_SELF_TEST_DONE_B);
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  return SNS_DDF_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_smgr_set_attr

===========================================================================*/
 /**
     * @brief Sets a sensor attribute to a specific value.
     *
     * @param[in] drv_fn_ptr    Driver interface pointer
     * @param[in] dd_handle  Handle to a driver instance.
     * @param[in] sensor     Sensor for which this attribute is to be set. When
     *                       addressing an attribute that refers to the driver
     *                       this value is set to SNS_DDF_SENSOR__ALL.
     * @param[in] attrib     Attribute to be set.
     * @param[in] value      Value to set this attribute.
     *
     * @return Success if the value of the attribute was set properly. Otherwise
     *         a specific error code is returned.
     */
/*=========================================================================*/
sns_ddf_status_e sns_smgr_set_attr(
  const sns_smgr_sensor_s* sensor_ptr,
  sns_ddf_sensor_e     sensor,
  sns_ddf_attribute_e  attrib,
  void*                value)
{
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  bool qup_clck_state = sns_hw_qup_clck_status();
  uint32_t before, after;

  /* ---------------------------------------------------------------------- */

  sns_hw_set_qup_clk(true);
  before = sns_em_get_timestamp();
  if ( SENSOR_STATE_FAILED != sensor_ptr->sensor_state )
  {
    status = SMGR_DRV_FN_PTR(sensor_ptr)->set_attrib(sensor_ptr->dd_handle,
                                                     sensor,
                                                     attrib,
                                                     value);
  }
  after = sns_em_get_timestamp();
  sns_hw_set_qup_clk(qup_clck_state);

  SNS_SMGR_PRINTF3(MED, "set_attr - ddf_sensor=%d attrib=%d value=%d",
                   sensor, attrib, *((uint8_t*)value) );
  SNS_SMGR_PRINTF2(MED, "set_attr - status=%d (took %u ticks)",
                   status, (unsigned)(after-before));

  return status;
}


/*===========================================================================

  FUNCTION:   sns_smgr_get_attr

===========================================================================*/
/*!
  @brief Called by the SMGR to retrieves the value of an attribute of
  the sensor.

  @detail
  - range and resolution info is from the device data sheet.
  @param[in]  drv_fn_ptr    Driver interface pointer
  @param[in]  dd_handle   Handle to a driver instance.
  @param[in]  sensor       Sensor whose attribute is to be retrieved.
  @param[in]  attrib      Attribute to be retrieved.
  @param[in]  memhandler  Memory handler used to dynamically allocate
                         output parameters, if applicable.
  @param[out] value      Pointer that this function will allocate or set
                         to the attribute's value.
  @param[out] num_elems  Number of elements in @a value.

  @return
    The error code definition within the DDF
    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS

*/
/*=========================================================================*/
sns_ddf_status_e sns_smgr_get_attr(
  sns_smgr_sensor_s*     sensor_ptr,
  sns_ddf_sensor_e       sensor,
  sns_ddf_attribute_e    attrib,
  void**                 value,
  uint32_t*              num_elems)
{
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  /* ---------------------------------------------------------------------- */

  if ( SENSOR_STATE_FAILED != sensor_ptr->sensor_state )
  {
    status = SMGR_DRV_FN_PTR(sensor_ptr)->get_attrib(sensor_ptr->dd_handle,
                                                     sensor,
                                                     attrib,
                                                     &sensor_ptr->memhandler,
                                                     value,
                                                     num_elems);
  }
  if ( status != SNS_DDF_SUCCESS )
  {
    SNS_SMGR_PRINTF3(ERROR, "get_attr - ddf_sensor=%d attrib=%d status=%d",
                     sensor, attrib, status);
  }
  return status;
}


/*===========================================================================
  FUNCTION:   sns_smgr_dd_reset
===========================================================================*/
sns_ddf_status_e sns_smgr_dd_reset(const sns_smgr_sensor_s* sensor_ptr)
{
  sns_ddf_status_e  status = SNS_DDF_EFAIL;

  /* ---------------------------------------------------------------------- */

  if ( (SMGR_DRV_FN_PTR(sensor_ptr) != NULL) && (sensor_ptr->dd_handle != NULL) &&
       (sensor_ptr->sensor_state != SENSOR_STATE_FAILED) )
  {
    bool qup_clck_state = sns_hw_qup_clck_status();
    sns_hw_set_qup_clk(true);
    status = SMGR_DRV_FN_PTR(sensor_ptr)->reset(sensor_ptr->dd_handle);
    sns_hw_set_qup_clk(qup_clck_state);

    SNS_SMGR_PRINTF2(
      HIGH, "dd_reset - sensor=%u status=%u", SMGR_SENSOR_ID(sensor_ptr), status);
  }
  return status;
}

/*===========================================================================
  FUNCTION:   sns_smgr_dd_run_test
===========================================================================*/
sns_ddf_status_e sns_smgr_dd_run_test(const sns_smgr_sensor_s* sensor_ptr)
{
  sns_ddf_status_e  status = SNS_DDF_EFAIL;
  bool qup_clck_state = sns_hw_qup_clck_status();

  /* ---------------------------------------------------------------------- */

  sns_hw_set_qup_clk(true);
  status = SMGR_DRV_FN_PTR(sensor_ptr)->
    run_test(sensor_ptr->dd_handle,
             SMGR_SENSOR_TYPE(sensor_ptr, 
                              sns_smgr.self_test.ddf_sensor_ptr->data_type),
             (sns_ddf_test_e)(sns_smgr.self_test.self_test_req->TestType), 
             &sns_smgr.self_test.result.test_specific_error);
  sns_hw_set_qup_clk(qup_clck_state);

  SNS_SMGR_PRINTF2(
    HIGH, "dd_run_test - sensor=%u status=%u", SMGR_SENSOR_ID(sensor_ptr), status);

  return status;
}

/*===========================================================================
  FUNCTION:   sns_smgr_dd_driver_access
===========================================================================*/
sns_ddf_status_e sns_smgr_dd_driver_access(
  sns_smgr_sensor_s*                  sensor_ptr,
  sns_smgr_driver_access_req_msg_v01* req_ptr,
  void**                              dd_resp_ptr_ptr,
  uint32_t*                           dd_resp_len_ptr,
  void*                               conn_handle)
{
  sns_ddf_status_e  status = SNS_DDF_EFAIL;
  bool qup_clck_state = sns_hw_qup_clck_status();

  /* ---------------------------------------------------------------------- */

  sns_hw_set_qup_clk(true);
  status = SMGR_DRV_FN_PTR(sensor_ptr)->
    process_daf_req(sensor_ptr->dd_handle,
                    req_ptr->RequestId,
                    req_ptr->RequestMsg_valid ?  req_ptr->RequestMsg : NULL,
                    req_ptr->RequestMsg_valid ?  req_ptr->RequestMsg_len : 0,
                    &sensor_ptr->memhandler,
                    dd_resp_ptr_ptr,
                    dd_resp_len_ptr,
                    req_ptr->TransactionId_valid ? &req_ptr->TransactionId : NULL,
                    conn_handle);
  sns_hw_set_qup_clk(qup_clck_state);

  SNS_SMGR_PRINTF2(
    HIGH, "dd_driver_access - sensor=%u status=%u", 
    SMGR_SENSOR_ID(sensor_ptr), status);

  return status;
}

/*===========================================================================
  FUNCTION:   sns_smgr_dd_driver_access_cancel
===========================================================================*/
void sns_smgr_dd_driver_access_cancel(
  sns_smgr_sensor_s*                  sensor_ptr,
  void*                               conn_handle)
{
  bool qup_clck_state = sns_hw_qup_clck_status();
  /* ---------------------------------------------------------------------- */

  sns_hw_set_qup_clk(true);
  SMGR_DRV_FN_PTR(sensor_ptr)->cancel_daf_trans(sensor_ptr->dd_handle, conn_handle);
  sns_hw_set_qup_clk(qup_clck_state);

  SNS_SMGR_PRINTF1(
    HIGH, "dd_driver_access_cancel - sensor=%u", SMGR_SENSOR_ID(sensor_ptr));
}


/*===========================================================================

  FUNCTION:   sns_ddf_smgr_set_uimg_refac

===========================================================================*/
/*!
  @brief  A device driver calls this function to set uimg refac flag
  Should be called only if the driver has been refactored to support uImage.

  @Detail

  @param[i] smgr_handle  smgr handle passed to DD
  @return None
*/
/*=========================================================================*/
void sns_ddf_smgr_set_uimg_refac(
  sns_ddf_handle_t  smgr_handle)
{
  sns_smgr_sensor_s *sensor_ptr = (sns_smgr_sensor_s *)smgr_handle;
  if (sensor_ptr != NULL)
  {
    sensor_ptr->is_uimg_refac = TRUE;
  }
}



/*===========================================================================  

  FUNCTION:   sns_ddf_smgr_get_uimg_refac

===========================================================================*/  
/*!
  @brief  Called by sns_signal_register to get status of uImage support .   

  @Detail                                                                      

  @param[i] dd_handle  dd handle passed to DD                              
  @return Sensor uImage support status
*/
/*=========================================================================*/ 
bool sns_ddf_smgr_get_uimg_refac(
  sns_ddf_handle_t  dd_handle)
{
  sns_smgr_sensor_s *sensor_ptr;
  int i;
  
  if ( dd_handle == NULL )
  {
    return FALSE;
  }
  for (i = 0; i < ARR_SIZE(sns_smgr.sensor); i++)
  {
    sensor_ptr = &sns_smgr.sensor[i];
    if (sensor_ptr->dd_handle == dd_handle)
    {
      return sensor_ptr->is_uimg_refac;
    }
  }
  return FALSE;
}


/*===========================================================================

  FUNCTION:   sns_smgr_notify_event_in_bigimage

===========================================================================*/
/*!
  @brief  Process a DD event in big image mode

  @Detail

  @param[i] smgr_handle  smgr handle passed to DD
  @param[i] sensor  sensor enum
  @param[i] event   event name
  @return
   SNS_DDF_SUCCESS
   SNS_DDF_EINVALID_PARAM if event with the sensor is not expected
*/
/*=========================================================================*/
sns_ddf_status_e sns_smgr_notify_event_in_bigimage(
    sns_ddf_handle_t  smgr_handle,
    sns_ddf_sensor_e  sensor,
    sns_ddf_event_e   event)
{
  sns_smgr_sensor_s*    sensor_ptr = (sns_smgr_sensor_s*)smgr_handle;
  sns_ddf_status_e  rc = SNS_DDF_SUCCESS;

  /* ---------------------------------------------------------------------- */

  if ( SMGR_HANDLE_VALID(sensor_ptr) )
  {
    switch (event)
    {
      case SNS_DDF_EVENT_BIAS_READY:
      {
        sns_ddf_bias_t *bias_ptr;
        uint32_t len;

        /* Read the bias attribute */
        if ( sns_smgr_get_attr(sensor_ptr,
                               sensor,
                               SNS_DDF_ATTRIB_BIAS,
                               (void**)&bias_ptr,
                               &len) == SNS_DDF_SUCCESS )
        {
          bool save_to_registry = true;
          bool apply_calibration = true;

          /* only process further if we can read all 3-axis bias */
          if (len != SNS_SMGR_SENSOR_DIMENSION_V01)
          {
            sns_ddf_memhandler_free_ex( &sensor_ptr->memhandler, sensor_ptr );
            rc = SNS_DDF_EFAIL;
            break;
          }
          SNS_SMGR_PRINTF3(
            LOW, "bias - 0x%08x 0x%08x 0x%08x",
            (unsigned)bias_ptr[0], (unsigned)bias_ptr[1], (unsigned)bias_ptr[2]);

          if ( sns_smgr.self_test.self_test_req != NULL )
          {
            if ( sns_smgr.self_test.self_test_req->SaveToRegistry_valid &&
                 !sns_smgr.self_test.self_test_req->SaveToRegistry )
            {
              save_to_registry = false;
            }
            if ( sns_smgr.self_test.self_test_req->ApplyCalNow_valid &&
                 !sns_smgr.self_test.self_test_req->ApplyCalNow )
            {
              apply_calibration = false;
            }
          }
          if ( save_to_registry )
          {
             sns_ddf_bias_t *local_bias_ptr = bias_ptr;

             /* Write to registry file */
             if (sensor == SNS_DDF_SENSOR_ACCEL)
             {
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_X_BIAS_V02,
                                      SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                      sizeof(sns_ddf_bias_t),
                                      (uint8_t*)local_bias_ptr++);
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_Y_BIAS_V02,
                                      SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                      sizeof(sns_ddf_bias_t),
                                      (uint8_t*)local_bias_ptr++);
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_Z_BIAS_V02,
                                      SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                      sizeof(sns_ddf_bias_t),
                                      (uint8_t*)local_bias_ptr);
             }
             else if (sensor == SNS_DDF_SENSOR_GYRO)
             {
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_X_BIAS_V02,
                                     SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                     sizeof(sns_ddf_bias_t),
                                     (uint8_t*)local_bias_ptr++);
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_Y_BIAS_V02,
                                     SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                     sizeof(sns_ddf_bias_t),
                                     (uint8_t*)local_bias_ptr++);
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_Z_BIAS_V02,
                                     SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                     sizeof(sns_ddf_bias_t),
                                     (uint8_t*)local_bias_ptr);
             }
             else
             {
                sns_ddf_memhandler_free_ex( &sensor_ptr->memhandler, sensor_ptr );
                rc = SNS_DDF_EINVALID_PARAM;
                break;
             }
          }
          /* Update calibration information in sensor structure */
          if ( (sensor_ptr->ddf_sensor_ptr[0] != NULL) &&
               (sensor_ptr->ddf_sensor_ptr[0]->all_cal_ptr != NULL) &&
               sensor_ptr->ddf_sensor_ptr[0]->all_cal_ptr->auto_cal.used &&
               save_to_registry )
          {
             /* reset autocal parameters in registry */
             int32_t def_auto_bias = 0;
             if (sensor == SNS_DDF_SENSOR_ACCEL)
             {
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_X_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_Y_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
                sns_smgr_update_reg_data(SNS_REG_ITEM_ACC_Z_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
             }
             else if (sensor == SNS_DDF_SENSOR_GYRO)
             {
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_X_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_Y_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
                sns_smgr_update_reg_data(SNS_REG_ITEM_GYRO_Z_DYN_BIAS_V02,
                                         SNS_SMGR_REG_ITEM_TYPE_SINGLE,
                                         sizeof(int32_t),
                                         (uint8_t *)&def_auto_bias);
             }
          }

          if ( apply_calibration &&
               (sensor_ptr->ddf_sensor_ptr[0] != NULL) &&
               (sensor_ptr->ddf_sensor_ptr[0]->all_cal_ptr != NULL) )
          {
            sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sensor_ptr->ddf_sensor_ptr[0];
            sns_smgr_all_cal_s* all_cal_ptr = ddf_sensor_ptr->all_cal_ptr;

             /* reset autocal parameters in SMGR */
            sns_smgr_load_default_cal( &(all_cal_ptr->auto_cal) );
              /* update factory cal params */
            SNS_OS_MEMCOPY(all_cal_ptr->factory_cal.zero_bias,
                           bias_ptr, sizeof(sns_ddf_bias_t) * len);

            /* update full cal params */
            all_cal_ptr->full_cal.zero_bias[0] =
                    all_cal_ptr->factory_cal.zero_bias[0] +
                    all_cal_ptr->auto_cal.zero_bias[0];
            all_cal_ptr->full_cal.zero_bias[1] =
                    all_cal_ptr->factory_cal.zero_bias[1] +
                    all_cal_ptr->auto_cal.zero_bias[1];
            all_cal_ptr->full_cal.zero_bias[2] =
                    all_cal_ptr->factory_cal.zero_bias[2] +
                    all_cal_ptr->auto_cal.zero_bias[2];

            all_cal_ptr->auto_cal.used     = false;
            all_cal_ptr->factory_cal.used  = true;
            all_cal_ptr->full_cal.used     = true;
          }
        }
        sns_ddf_memhandler_free_ex( &sensor_ptr->memhandler, sensor_ptr );
        break;
      }
      case  SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP:
      {
        sns_ddf_registry_group_s* reg_group_ptr = NULL;
        uint32_t len = 0;
        rc = SNS_DDF_EFAIL;

        if ( sns_smgr_get_attr(sensor_ptr,
                               sensor,
                               SNS_DDF_ATTRIB_REGISTRY_GROUP,
                               (void**)&reg_group_ptr,
                               &len) == SNS_DDF_SUCCESS )
        {
         if ( sns_smgr_update_reg_data(sensor_ptr->const_ptr->driver_reg_id,
                                       sensor_ptr->const_ptr->driver_reg_type,
                                       reg_group_ptr->size,
                                       (uint8_t*) reg_group_ptr->group_data) == SNS_SUCCESS )
         {
           rc = SNS_DDF_SUCCESS;
         }
        }
        sns_ddf_memhandler_free_ex( &sensor_ptr->memhandler, sensor_ptr );
        break;
      }
      case SNS_DDF_EVENT_MOTION:
      {
        sns_smgr_dd_handle_md_int(sensor_ptr);
        break;
      }
      case SNS_DDF_EVENT_ODR_CHANGED:
      {
        sns_smgr_ddf_sensor_s*  ddf_sensor_ptr;

        /* Determines the new ODR */
        if( sensor_ptr->odr_attr_supported )
        {
          ddf_sensor_ptr = sns_smgr_match_ddf_sensor(sensor_ptr, sensor);

          if ( ddf_sensor_ptr != NULL )
          {
            sns_smgr_update_odr(ddf_sensor_ptr);
            sns_smgr_update_sampling_setting(ddf_sensor_ptr);
            sns_smgr_fifo_on_event_odr_changed( ddf_sensor_ptr, sensor );
          }
        }
        else
        {
          rc = SNS_DDF_EINVALID_PARAM;
        }        
        break;
      }

      //--------------- FIFO events -----------------
      case SNS_DDF_EVENT_FIFO_OVERFLOW:
      {
        rc = sns_smgr_fifo_on_event_fifo_overflow( sensor_ptr, sensor );
        break;
      }
      case SNS_DDF_EVENT_FIFO_AVAILABLE:
      {
        rc = sns_smgr_fifo_on_event_fifo_available( sensor_ptr, sensor );
        break;
      }
      case SNS_DDF_EVENT_FIFO_UNAVAILABLE:
      {
        rc = sns_smgr_fifo_on_event_fifo_unavailable( sensor_ptr, sensor );
        break;
      }
      
      default:
      {
        rc = SNS_DDF_EINVALID_PARAM;
        break;
      }
    }  /* switch (event) */
  }
  else
  {
    rc = SNS_DDF_EINVALID_PARAM;
  }
  return rc;
}


/*===========================================================================

  FUNCTION:   sns_smgr_dd_enable_sched_data

===========================================================================*/
 /**
     * @brief Begins device-scheduled sampling and enables notification via Data
     *        Ready Interrupts (DRI).
     *
     * @param[in/out] sensor_ptr The sensor of interest
     * @param[in] sensor     Primary or secondary
     * @param[in] enable     Enable or disable
     *
     * @return NS_DDF_SUCCESS if sensor was successfully configured and
     *         internal sampling has commenced or ceased. Otherwise an
     *         appropriate error code.
     */
/*=========================================================================*/
sns_ddf_status_e sns_smgr_dd_enable_sched_data(
  sns_smgr_sensor_s*  sensor_ptr,
  sns_ddf_sensor_e    sensor,
  bool                enable)
{
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  bool qup_clck_state = sns_hw_qup_clck_status();
  uint32_t before, after;

  /* ---------------------------------------------------------------------- */

  SNS_SMGR_PRINTF1(
    MED, "enable_sched_data - intr_enabled=%d", 
    sensor_ptr->is_self_sched_intr_enabled);

  sns_hw_set_qup_clk(true);
  before = sns_em_get_timestamp();
  
  if ( (SENSOR_STATE_FAILED != sensor_ptr->sensor_state) &&
       (NULL != SMGR_DRV_FN_PTR(sensor_ptr)->enable_sched_data) )
  {
    status = SMGR_DRV_FN_PTR(sensor_ptr)->enable_sched_data(sensor_ptr->dd_handle,
                                                            sensor,
                                                            enable);
    if ( status == SNS_DDF_SUCCESS )
    {
      sensor_ptr->is_self_sched_intr_enabled = enable;
    }

  }

  after = sns_em_get_timestamp();
  sns_hw_set_qup_clk(qup_clck_state);
  SNS_SMGR_PRINTF3(MED, "enable_sched_data - ddf_sensor=%d enable=%d stat=%d",
                   sensor, enable, status);
  SNS_SMGR_PRINTF1(MED, "enable_sched_data - took %u ticks", (unsigned)(after-before));

#ifdef SNS_QDSP_SIM
  if(!sns_dri_sim.dri_sim_task_created)
  {
    sns_os_task_create_ext(sns_simulate_dri, NULL,
                           &sns_dri_sim.DRITask[SNS_MODULE_STK_SIZE_DRI_SIM - 1],
                           SNS_MODULE_PRI_DRI_SIM,
                           SNS_MODULE_PRI_DRI_SIM,
                           &sns_dri_sim.DRITask[0],
                           SNS_MODULE_STK_SIZE_DRI_SIM,
                           (void *)0,
                           OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR,
                           (uint8_t *)"SNS_SIMULATE_DRI");

    sns_dri_sim.dri_sim_task_created = true;
  }
#endif
  return status;
}

/*===========================================================================

  FUNCTION:   sns_smgr_set_power_attr

===========================================================================*/
 /**
     * @brief Sets POWERSTATE attribute for given sensor
     *
     * @param[io] sensor_ptr   the sensor for which to set POWERSTATE
     * @param[i]  powerstate   the desired powerstate
     *
     * @return Success if the value of the attribute was set properly. Otherwise
     *         a specific error code is returned.
     */
/*=========================================================================*/
sns_ddf_status_e sns_smgr_set_power_attr(
  sns_smgr_sensor_s*    sensor_ptr,
  sns_ddf_powerstate_e  powerstate)
{
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  SNS_SMGR_PRINTF3(LOW, "set_power_attr - sensor=%u powerstate(curr/want)=%u/%u",
                   SMGR_SENSOR_ID(sensor_ptr), sensor_ptr->powerstate, powerstate);
  if ( sensor_ptr->powerstate != powerstate )
  {
    status = sns_smgr_set_attr(sensor_ptr, SNS_DDF_SENSOR__ALL, 
                               SNS_DDF_ATTRIB_POWER_STATE, (uint32_t*)&powerstate);
    if ( status == SNS_DDF_SUCCESS )
    {
      sensor_ptr->powerstate = powerstate;
    }
  }
  return status;
}

