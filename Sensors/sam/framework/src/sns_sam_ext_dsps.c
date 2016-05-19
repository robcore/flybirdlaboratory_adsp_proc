/*============================================================================
  FILE: sns_sam_dsps_ext.c

  This file contains Sensors Algorithm Manager implementation specific to DSPS

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/sam/framework/src/sns_sam_ext_dsps.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-14  sc   Remove legacy algorithm management
  2014-09-03  tc   Remove registration for migrated and deprecated algorithms
  2014-05-16  sc   Remove AMD algo from registering with legacy SAM
  2014-04-11  rt   Disable initializing modem scn to prevent crash on 8084 RCM
  2014-03-20  pk   Register Fusion algos on SSC if QCompass reg query fails
  2014-03-20  pk   Set algorithm_revision to 1 for initial versions of algos
  2014-03-14  rt   Fixes sensors hang issue during modem scn client init
  2014-02-19  pk   Reduced max rates for Ped, PAM and a few gestures
  2014-02-06  pk   Changed min/max report rates for algorithms
  2014-02-05  ks   Integrated Feature Motion Classifier support
  2013-10-20  ad   Fixed klocwork errors
  2013-10-14  sc   Added support for oem_1 algo
  2013-10-10  sc   Add relative threshold support
  2013-10-03  pk   Allow disabling SAM buffering
  2013-09-26  ps   Add BRINGUP_8084 flag to disable Modem client
  2013-09-16  pk   Enabled SAM buffering by default
  2013-09-06  dk   Increased the number of SMD tunable parameters supported
  2013-09-03  ag   Remove double free when sam_mr_send fails
  2013-08-28  ad   Enable SMD to use buffered data
  2013-07-31  hw   Fix Klocwork warning error
  2013-07-26  vh   Eliminated compiler warnings
  2013-07-11  pk   Use signals to receive AP suspend state notification from PM
  2013-06-27  gju  Remove Mag cal and use SMGR for mag instead
  2013-06-15  asj  Completed stubs for modem SCN algo
  2013-06-05  pd   Add Significant Motion Detection
  2013-06-05  tc   Added support for Game Rotation Vector
  2013-02-12  hw   Remove the Gravity vector service registration on ADSP
  2013-01-13  asj  Added Modem SCN algo
  2012-11-15  hw   Migrates Gestures Features from APPS to ADSP
  2012-11-08  sc   Merged from DSPS 1.1 mainline
  2012-10-09  hw   Changed default sensor_id in threshold algorithm to ACCEL
  2012-08-10  sc   Merged from mainline the gyrobuf algo service
  2012-08-09  ag   Updated to use official QMI service IDs
  2012-05-08  lka  Fixed (gyrobuf algorithm) the fixed-point conversion
  2012-04-11  lka  Added algorithm registration for Gyrobuf
  2011-11-21  ad   SAM registers algorithms supported by the sensors available on plaform
  2011-11-14  jhh  Updated alloc function calls to meet new API
  2011-11-04  sc   Added support for sensors threshold algorithm
  2011-09-09  sc   Update with registry service V02
  2011-07-18  ad   refactor SAM for memory optimization

 ============================================================================*/
/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <qmi_csi.h>
#include <qmi_client.h>
#include <qmi_idl_lib.h>
#include <qmi_cci_target_ext.h>

#include "sns_sam_priv.h"

#include "sns_osa.h"
#include "sns_memmgr.h"
#include "sns_reg_common.h"
#include "sns_debug_str.h"
#include "sns_em.h"

#include "sns_reg_api_v02.h"
#include "sns_smgr_api_v01.h"
#include "sns_time_api_v02.h"

#include "radio_frequency_radiated_performance_enhancement_v01.h"
#include "sns_sam_modem_scn_v01.h"

/* The face and shake algo interfaces */
#ifdef FEATURE_SNS_SAM_TILT
#include "integ_angle.h"
#include "sns_sam_integ_angle_v01.h"
#endif /* FEATURE_SNS_SAM_TILT */

#include "modem_scn.h"
#include "sns_sam_modem_scn_v01.h"

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define SNS_SAM_MODEM_INFO_TIMER_PERIOD_USEC 20000000

 //TODO: Move to target specific header
#ifdef ADSP_HWCONFIG_L
   #define SNS_SAM_MAX_BACK_TO_BACK_BATCH_INDS 50
#else
   #define SNS_SAM_MAX_BACK_TO_BACK_BATCH_INDS 4
#endif

// Max report rates
#define SNS_SAM_MAX_FUSION_REPORT_RATE_Q16    FX_CONV_Q16(120,0)
#define SNS_SAM_MAX_GYRO_QUAT_REPORT_RATE_Q16 FX_CONV_Q16(200,0)

// Max sample rates
#define SNS_SAM_MAX_PED_SAMPLE_RATE_Q16       FX_CONV_Q16(50,0)
#define SNS_SAM_MAX_GESTURES_SAMPLE_RATE_Q16  FX_CONV_Q16(100,0)

// Min report rates
#define SNS_SAM_MIN_ALGO_REPORT_RATE     (1.0f/60) // 60 seconds interval
#define SNS_SAM_MIN_ALGO_REPORT_RATE_Q16 FX_FLTTOFIX_Q16(SNS_SAM_MIN_ALGO_REPORT_RATE)
#define SNS_SAM_MIN_PED_REPORT_RATE      (1.0f/3600) // 60 minute interval
#define SNS_SAM_MIN_PED_REPORT_RATE_Q16  FX_FLTTOFIX_Q16(SNS_SAM_MIN_PED_REPORT_RATE)

/*---------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

// Mag Cal support on ADSP flag
static bool sns_sam_mag_cal_adsp_support_flag = true;

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
static sns_em_timer_obj_t sns_sam_modem_info_timer;
static qmi_client_type    modem_scn_user_handle;

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/*=========================================================================
  FUNCTION:  sns_sam_reg_algo
  =========================================================================*/
/*!
  @brief Register specified algorithm

  @param[i/o] algoPtr: pointer to algorithm
  @param[i] uuids: UUIDs of detected sensors

  @return None
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_algo(
   sns_sam_algo_s* algoPtr,
   const sns_sam_sensor_uuid_s* uuids)
{

   UNREFERENCED_PARAMETER(uuids);
   algoPtr->disableAlgoInstReuse = FALSE;

   if (algoPtr->serviceId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      modem_scn_config_s *defCfgPtr;

      algoPtr->defConfigData.memPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD,sizeof(modem_scn_config_s));
      SNS_ASSERT(algoPtr->defConfigData.memPtr != NULL);
      defCfgPtr = (modem_scn_config_s *)(algoPtr->defConfigData.memPtr);

      algoPtr->defConfigData.memSize = sizeof(modem_scn_config_s);
      algoPtr->defInputDataSize = sizeof(modem_scn_input_s);
      algoPtr->defOutputDataSize = sizeof(modem_scn_output_s);

      algoPtr->algoApi.sns_sam_algo_mem_req =
         (int32_t(*)(void*))modem_scn_sam_mem_req;
      algoPtr->algoApi.sns_sam_algo_reset =
         (void*(*)(void*,void*))modem_scn_sam_state_reset;
      algoPtr->algoApi.sns_sam_algo_update =
         (void(*)(void*,void*,void*))modem_scn_sam_update;
      algoPtr->algoApi.sns_sam_algo_register_client = NULL;
      algoPtr->algoApi.sns_sam_algo_reset_client_stats = NULL;
      algoPtr->algoApi.sns_sam_algo_register_client = NULL;
      algoPtr->algoApi.sns_sam_algo_reset_client_stats = NULL;
      algoPtr->algoApi.sns_sam_algo_handle_duty_cycle_state_change = NULL;

      algoPtr->regItemType = SNS_SAM_REG_ITEM_TYPE_NONE;

      /* set 1Hz PRX as default */
      defCfgPtr->sample_rate = FX_CONV_Q16(1, 0);
      defCfgPtr->quiet_period = MODEM_SCN_DEF_QUIET_PERIOD;
      defCfgPtr->thresh = MODEM_SCN_DEF_THRESH;  /* Max threshold*/

      return SNS_SUCCESS;
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == algoPtr->serviceId)
   {
      integ_angle_config_struct *defCfgPtr;

      algoPtr->defConfigData.memPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, sizeof(integ_angle_config_struct));
      SNS_ASSERT(algoPtr->defConfigData.memPtr != NULL);
      defCfgPtr = (integ_angle_config_struct *)(algoPtr->defConfigData.memPtr);

      algoPtr->defConfigData.memSize = sizeof(integ_angle_config_struct);
      algoPtr->defInputDataSize = sizeof(integ_angle_input_struct);
      algoPtr->defOutputDataSize = sizeof(integ_angle_output_struct);

      algoPtr->algoApi.sns_sam_algo_mem_req =
         (int32_t(*)(void*))integ_angle_sam_mem_req;
      algoPtr->algoApi.sns_sam_algo_reset =
         (void*(*)(void*,void*))integ_angle_sam_state_reset;
      algoPtr->algoApi.sns_sam_algo_update =
         (void(*)(void*,void*,void*))integ_angle_sam_update;
      algoPtr->algoApi.sns_sam_algo_register_client = NULL;
      algoPtr->algoApi.sns_sam_algo_reset_client_stats = NULL;
      algoPtr->algoApi.sns_sam_algo_handle_duty_cycle_state_change = NULL;

      defCfgPtr->sample_rate = IA_MIN_GYRO_RATE_Q16;
      defCfgPtr->clip_threshold = FX_IA_RES_LIMIT;

      algoPtr->algorithm_revision = 1;
      algoPtr->supported_reporting_modes = SNS_SAM_PERIODIC_REPORT_V01 |
                                           SNS_SAM_ASYNC_REPORT_V01;
      algoPtr->min_report_rate = SNS_SAM_MIN_ALGO_REPORT_RATE_Q16;
      algoPtr->max_report_rate = IA_MAX_GYRO_RATE_Q16;
      algoPtr->min_sample_rate = IA_MIN_GYRO_RATE_Q16;
      algoPtr->max_sample_rate = IA_MAX_GYRO_RATE_Q16;
      algoPtr->max_batch_size = 0;
      algoPtr->power = sns_sam_sensor_info_dbase_acc(SNS_SAM_GYRO)->maxPower;
      return SNS_SUCCESS;
   }
#endif /* FEATURE_SNS_SAM_TILT */

   else
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_REG_ALGO_DFLT_ERR, algoPtr->serviceId);
      return SNS_ERR_FAILED;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_reg_algos
  =========================================================================*/
/*!
  @brief Register all algorithms

  @return None
*/
/*=======================================================================*/
void sns_sam_reg_algos(void)
{
/*
   if (sns_sam_sensor_info_dbase_acc(SNS_SAM_GYRO)->valid)
   {
#ifdef FEATURE_SNS_SAM_TILT
     // DEPRECATED
     sns_sam_reg_algo_svc(SNS_SAM_INTEG_ANGLE_SVC_ID_V01);
#endif // FEATURE_SNS_SAM_TILT
   }
*/
   // TODO: ADD MODEM SCN BACK IN (IN EITHER LEGACY SAM OR USAM)
//   sns_sam_reg_algo_svc(SNS_SAM_MODEM_SCN_SVC_ID_V01);
}

/*=========================================================================
  FUNCTION:  sns_sam_process_reg_data
  =========================================================================*/
/*!
  @brief Process data received from registry

  @param[i] regItemType - registry item type
  @param[i] regItemId - registry item identifier
  @param[i] regDataLen - registry data length
  @param[i] regDataPtr - registry data pointer

  @return None
*/
/*=======================================================================*/
void sns_sam_process_reg_data(
   sns_sam_reg_item_type_e regItemType,
   uint16_t regItemId,
   uint32_t regDataLen,
   const uint8_t* regDataPtr)
{
   switch(regItemId)
   {
   case SNS_REG_SCM_GROUP_QMAG_CAL_ALGO_V02:
   {
      sns_reg_qmag_cal_algo_data_group_s *dataPtr =
         (sns_reg_qmag_cal_algo_data_group_s *)regDataPtr;

      if (!dataPtr->enable_algo)
      {
         // Mag Cal is not supported on ADSP
         // QFusion algos cannot be supported on ADSP SAM
         sns_sam_mag_cal_adsp_support_flag = false;
      }

      SNS_SAM_PRINTF2(MED, "sns_sam_process_reg_data: reg item id %d, sns_sam_mag_cal_adsp_support_flag: %d",
                      SNS_REG_SCM_GROUP_QMAG_CAL_ALGO_V02,(uint8_t)(sns_sam_mag_cal_adsp_support_flag));

      break;
   }
   default:
      break;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_modem_scn_ind_cb
  =========================================================================*/
static void sns_sam_modem_scn_ind_cb( qmi_client_type user_handle,
                             unsigned int msg_id,
    void *ind_buf, unsigned int ind_buf_len, void *ind_cb_data )
{
   SNS_SAM_PRINTF2(LOW,
                   "modem_scn_ind call back called  %u, %u", 0, 0);

}

/*=========================================================================
  FUNCTION:  sns_sam_kickstart_modem_scn_algo
  =========================================================================*/
bool sns_sam_kickstart_modem_scn_algo(void)
{
   sns_err_code_e err = SNS_ERR_FAILED;
   sns_smr_header_s msgHdr;
   sns_sam_modem_scn_enable_req_msg_v01 *enableMsgPtr =
               (sns_sam_modem_scn_enable_req_msg_v01 *)
                       sns_smr_msg_alloc( SNS_SAM_MODULE,
                                 sizeof(sns_sam_modem_scn_enable_req_msg_v01));


   if(enableMsgPtr == NULL)
   {
      SNS_PRINTF_STRING_ERROR_0( SNS_SAM_DBG_MOD,
                           "Cannot allocate memory to general scn_enable_req");
      return false;
   }

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   msgHdr.msg_id = SNS_SAM_ALGO_ENABLE_REQ;

   msgHdr.svc_num = SNS_SAM_MODEM_SCN_SVC_ID_V01;
   msgHdr.ext_clnt_id = 0;
   msgHdr.txn_id = 0;
   msgHdr.body_len = sizeof(sns_sam_modem_scn_enable_req_msg_v01);

   SNS_SAM_PRINTF2(LOW,
                   "Sending modem_scn enable src module %u, svc %u",
                   msgHdr.src_module, msgHdr.svc_num);

   enableMsgPtr->sample_rate = FX_CONV_Q16(5, 0);
   sns_smr_set_hdr(&msgHdr, enableMsgPtr);

   err = sns_sam_mr_send(enableMsgPtr, NULL);
   if (SNS_SUCCESS != err)
   {
      SNS_PRINTF_STRING_ERROR_1(SNS_SAM_DBG_MOD,
                        "Error sending msg - err %d", err);
      return(false);
   }
   else
   {
      return(true);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_set_modem_scn_cb
  =========================================================================*/
void sns_sam_set_modem_scn_cb( qmi_client_type user_handle, unsigned int msg_id,
    void *resp_c_struct, unsigned int resp_c_struct_len, void *cb_data,
    qmi_client_error_type transp_err )
{
   SNS_SAM_PRINTF0(LOW, "Received Set Scenario response");
   /* We are not doing any additional protocol here. Hoewever, the modem
      and the ADSP implementation can pass some information in this channel */
}

/*=========================================================================
  FUNCTION:  sns_sam_handle_prov_tbl
  =========================================================================*/
void sns_sam_handle_prov_tbl(rfrpe_get_provisioned_table_revision_resp_v01 *table)
{
   SNS_SAM_PRINTF3( LOW,
                    "Rcd Provisioned Table rsp successfully valid flags %d %d %d",
                    table->provisioned_table_revision,
                    table->provisioned_table_OEM[0],
                    table->provisioned_table_OEM[1]);

   /* Additional checks can be made here to determine if the algo can
      be kick started
   */
   if (table->provisioned_table_revision_valid &&
       table->provisioned_table_OEM_valid &&
       table->provisioned_table_OEM_len > 0
       //&& strncmp(table->provisioned_table_OEM, "Qualcomm") // for example
       )
   {
      if (sns_sam_kickstart_modem_scn_algo() != true)
      {
         SNS_SAM_PRINTF3(LOW,
                        "started modem_scn_algo %d %d %d",
                          0, 0, 0);
      }
      else
      {
         SNS_SAM_PRINTF3(LOW,
                         "Cannot start modem_scn_algo %d %d %d",
                          0, 0, 0);
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_send_modem_scenarios_req
  =========================================================================*/
/*!
  @brief Request modem scenarios information

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_modem_scenario(uint8_t scn)
{
   qmi_idl_service_object_type service;
   uint32_t resp_msg_size;
   void *resp_msg;
   qmi_txn_handle qmi_txn;
   qmi_client_error_type qmi_err;
   uint8_t *resp_cb_data;
   rfrpe_set_scenario_req_v01 *msgPtr;

   sns_err_code_e rv = SNS_SUCCESS;
   qmi_client_type service_handle = NULL;

   service = rfrpe_get_service_object_v01();
   service_handle = modem_scn_user_handle;

   if (NULL == service_handle)
   {
      SNS_PRINTF_STRING_ERROR_0(SNS_SAM_DBG_MOD,
                                "Unable to acquire service handle for modem RF service");
      rv = SNS_ERR_INVALID_HNDL;
   }
   else
   {
      qmi_idl_get_message_c_struct_len(service, QMI_IDL_RESPONSE,
                                       QMI_RFRPE_SET_RFM_SCENARIO_REQ_V01,
                                       &resp_msg_size);
      resp_msg = SNS_OS_MALLOC(SNS_SAM_MODULE, resp_msg_size);
      msgPtr = SNS_OS_MALLOC(SNS_SAM_MODULE,
                             sizeof(rfrpe_set_scenario_req_v01));
      resp_cb_data = NULL;

      if (NULL == resp_msg || NULL == msgPtr)
      {
         SNS_PRINTF_STRING_ERROR_0(SNS_SAM_DBG_MOD,
                                   "Failed to allocate resources");
         if (resp_msg)
         {
            SNS_OS_FREE(resp_msg);
         }

         if (msgPtr)
         {
            SNS_OS_FREE(msgPtr);
         }
         rv = SNS_ERR_NOMEM;
      }
      else
      {
         msgPtr->scenarios_len = 1;
         msgPtr->scenarios[0] = scn;

         qmi_err = qmi_client_send_msg_async(service_handle,
                                             QMI_RFRPE_SET_RFM_SCENARIO_REQ_V01,
                                             msgPtr,
                                             sizeof(rfrpe_set_scenario_req_v01),
                                             resp_msg, resp_msg_size,
                                             sns_sam_set_modem_scn_cb,
                                             (void *)resp_cb_data, &qmi_txn);

         if (QMI_NO_ERR != qmi_err)
         {
            SNS_PRINTF_STRING_ERROR_1(SNS_SAM_DBG_MOD,
                                      "Received error from QMI framework call %d",
                                      qmi_err);
            if (resp_cb_data)
            {
               SNS_OS_FREE(resp_cb_data);
            }

            if (resp_msg)
            {
               SNS_OS_FREE(resp_msg);
            }
            if (msgPtr)
            {
               SNS_OS_FREE(msgPtr);
            }
            rv = SNS_ERR_FAILED;

            SNS_SAM_PRINTF2(LOW,
                            "Could not send scenario %u to modem, err = %d", scn, qmi_err);
         }
         else
         {
            SNS_SAM_PRINTF2(LOW,
                            "Sent scenario %u to modem %u", scn, 0);
         }
      }
   }

   return rv;
}

/*=========================================================================
  FUNCTION:  sns_sam_init_modem_qmi_client
  =========================================================================*/
void sns_sam_init_modem_qmi_client(void)
{
   qmi_idl_service_object_type service;
   qmi_cci_os_signal_type os_params_tmp;
   qmi_client_error_type  qmi_err;
   uint8_t *ind_cb_data;
   os_params_tmp.ext_signal = NULL;
   os_params_tmp.sig = SNS_SAM_QMI_CLI_SIG;
   os_params_tmp.timer_sig = SNS_SAM_QMI_TIMER_SIG;

   modem_scn_user_handle = NULL;

   service = rfrpe_get_service_object_v01();
   ind_cb_data = NULL;

   qmi_err = qmi_client_init_instance(service, QMI_CLIENT_INSTANCE_ANY,
                                      sns_sam_modem_scn_ind_cb, ind_cb_data,
                                      &os_params_tmp, 1000 * 1,
                                      &modem_scn_user_handle);

   SNS_SAM_PRINTF3(LOW,
                   "QMI Client init - err %d, handle %u, service %u",
                   qmi_err, modem_scn_user_handle, service);

   if( QMI_NO_ERR != qmi_err  || service == NULL)
   {
     SNS_SAM_PRINTF2(LOW,
                     "qmi_client_notifier_init error %d, service %d", qmi_err, service);
   }
   else
   {
      SNS_SAM_PRINTF2(LOW,
                      "QMI Client initalized - handle %u, service %u",
                      modem_scn_user_handle, service);
   }
}


/*=========================================================================
  FUNCTION:  sns_sam_send_modem_scenarios_req
  =========================================================================*/
/*!
  @brief Request modem scenarios information

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_modem_scenarios_req(void)
{
   qmi_idl_service_object_type service;
   uint32_t resp_msg_size;
   void *resp_msg;
   qmi_client_error_type qmi_err;
   qmi_client_type service_handle = NULL;
   uint8_t *resp_cb_data;
   sns_err_code_e rv = SNS_SUCCESS;

   service = rfrpe_get_service_object_v01();
   service_handle = modem_scn_user_handle;

   if (NULL == service_handle)
   {
      SNS_PRINTF_STRING_ERROR_0(SNS_SAM_DBG_MOD,
                                "Unable to acquire service handle for modem RF service");
      rv = SNS_ERR_INVALID_HNDL;
   }
   else
   {
      qmi_err = qmi_idl_get_message_c_struct_len(service, QMI_IDL_RESPONSE,
                                                 QMI_RFRPE_GET_PROVISIONED_TABLE_REVISION_REQ_V01,
                                                 &resp_msg_size);
      resp_msg = sns_smr_msg_alloc(SNS_DBG_MOD_APPS_ACM, resp_msg_size);
      if (NULL == resp_msg || qmi_err != QMI_NO_ERR)
      {
         SNS_SAM_PRINTF2(LOW,
                         "Failed to allocate resources %d %d", qmi_err, 0);
         rv = SNS_ERR_NOMEM;
      }
      else
      {
         resp_cb_data = SNS_OS_MALLOC(SNS_SAM_MODULE, sizeof(uint8_t));
         if ( NULL == resp_cb_data )
         {
            SNS_SAM_PRINTF0(ERROR, "error in malloc for resp_cb_data");
            return SNS_ERR_NOMEM;
         }
         *resp_cb_data = 1;

         qmi_err = qmi_client_send_msg_sync(service_handle,
                                            QMI_RFRPE_GET_PROVISIONED_TABLE_REVISION_REQ_V01,
                                            NULL, 0,  // zero length message
                                            resp_msg, resp_msg_size,
                                            10);


         if (QMI_NO_ERR != qmi_err)
         {
            SNS_SAM_PRINTF1(LOW,
                            "Rcd Error from QMI framework %d",
                            qmi_err);
            SNS_OS_FREE(resp_cb_data);
            sns_smr_msg_free(resp_msg);
            rv = SNS_ERR_FAILED;
         }
         else
         {
            SNS_SAM_PRINTF0(LOW,
                            "Sent Provisioned Table req successfully");
            sns_sam_handle_prov_tbl(resp_msg);
         }
      }
   }

   return rv;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_modem_info_delayed
  =========================================================================*/
/*!
  @brief Get information from modem
         Specifically queries the modem to find out if mulitple RF scenarios
         are supported.

  @return none
*/
/*=======================================================================*/
void sns_sam_get_modem_info_delayed(void)
{
/* Temporarily featurizing this code off for 8084, since it causes a bootup
 * crash on the 8084 RCM when a QCN file is loaded */
#ifndef BRINGUP_8084
   sns_sam_init_modem_qmi_client();

   sns_sam_send_modem_scenarios_req();
#endif /* BRINGUP_8084 */
}

/*=========================================================================
  FUNCTION:  sns_sam_get_modem_info_cb
  =========================================================================*/
/*!
  @brief Callback registered for timer expiry

  @param[i] argPtr: pointer to argument for callback function

  @return None
*/
/*=======================================================================*/
void sns_sam_get_modem_info_cb(void *argPtr)
{
  uint8_t err;

  UNREFERENCED_PARAMETER(argPtr);

  sns_os_sigs_post(sns_sam_sig_event_acc(),
                   SNS_SAM_MODEM_INFO_SIG,
                   OS_FLAG_SET,
                   &err);
  if (err != OS_ERR_NONE)
  {
     SNS_SAM_DEBUG1(ERROR, DBG_SAM_MODEM_INFO_CB_SIGNALERR, err);
  }
}

/*=========================================================================
  FUNCTION:  sns_sam_get_modem_info
  =========================================================================*/
/*!
  @brief Sets a timer to trigger getting information abour the provisioned
        scenario table in the modem.
        This function does not actually do any processing to not delay SAM
        startup.

  @return none
*/
void sns_sam_get_modem_info(void)
{
   /* Start a timer to get modem information */
   sns_err_code_e err;

   err = sns_em_create_timer_obj(sns_sam_get_modem_info_cb,
                                 NULL,
                                 SNS_EM_TIMER_TYPE_ONESHOT,
                                 &(sns_sam_modem_info_timer));
   if (err == SNS_SUCCESS)
   {
      err = sns_em_register_timer(sns_sam_modem_info_timer,
                                  sns_em_convert_usec_to_localtick(
                                     SNS_SAM_MODEM_INFO_TIMER_PERIOD_USEC));
      if (err == SNS_SUCCESS)
      {
        SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_REG_TIMER_STARTED,
                       0, SNS_SAM_MODEM_INFO_TIMER_PERIOD_USEC);
      }
   }
   if (err != SNS_SUCCESS)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_REG_TIMER_FAILED, err);
   }
   return;
}

/*===========================================================================
  FUNCTION:   sns_sam_ap_state_change_cb
===========================================================================*/
/*!
  @brief Called by Power module when AP state changes

  @param[i] suspendState - true, if AP entered suspend; false, on wake up

  @return   none
 */
/*=========================================================================*/
void sns_sam_ap_state_change_cb( bool suspendState )
{
   uint32_t setBit, clearBit;
   uint8_t err;

   if( suspendState )
   {
      setBit = SNS_SAM_AP_SUSPEND_SIG;
      clearBit = SNS_SAM_AP_AWAKE_SIG;
   }
   else
   {
      setBit = SNS_SAM_AP_AWAKE_SIG;
      clearBit = SNS_SAM_AP_SUSPEND_SIG;
   }
   sns_os_sigs_post( sns_sam_sig_event_acc(), clearBit, OS_FLAG_CLR, &err );
   sns_os_sigs_post( sns_sam_sig_event_acc(), setBit, OS_FLAG_SET, &err );
}
