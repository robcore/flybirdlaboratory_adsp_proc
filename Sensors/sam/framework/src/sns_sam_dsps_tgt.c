/*============================================================================
  FILE: sns_sam_dsps_tgt.c

  This file contains Sensors Algorithm Manager implementation specific to DSPS
  and target

  Copyright (c) 2011-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/sam/framework/src/sns_sam_dsps_tgt.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-12-17  ps   Branched out from 8974 directory
  2013-09-03  ag   Remove double free when sam_mr_send fails
  2013-06-11  ae   Added QDSP SIM playback support
  2013-03-16  lka  Returns service ID when motion interrupt occurs
  2013-02-14  agk  Support for GPIO for QMD latency test
  2013-02-12  gju  Use SMR message allocation functions
  2012-12-08  lka  added support for multiple clients to MD interrupt
  2012-12-07  gju  Use updated SAM framework API
  2012-12-05  lka  Re-enabled and modified QMI-based messaging to SMGR.
  2012-11-08  vh   Added malloc for QMI message request
  2012-10-31  jhh  Add additional parameter for sns_sam_update_power_vote to keep
                   track of number of clients for INACTIVE power state vote
  2012-10-14  sc   Temporarily disabled MD interrupt message to SMGR
  2012-09-14  sc   Enable SAM as a client of PM
                   (dependency: sns_pm_init must be done)
  2012-09-13  sc   Disabled SAM being client of PM (until PM is tested)
  2012-08-29  ag   Registered SMGR int service via QCSI
  2012-08-02  ag   Fix client user handle used when sending requests
  2012-07-23  ag   Porting from SMR to QMI
  2011-11-14  jhh  Updated alloc and free function calls to meet new API
  2011-09-21  ad   disable interrupt mode when non-AMD algorithms are active
  2011-07-18  ad   refactor SAM for memory optimization
  2011-04-20  ad   added support for low power QMD
  2011-04-18  ad   initial version

 ============================================================================*/

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_sam_priv.h"
#include "sns_debug_str.h"
#include "sns_memmgr.h"

#include "sns_pm_api_v01.h"
#include "sns_smgr_internal_api_v01.h"
#include "sns_sam_qmd_v01.h"
#include "qurt_elite_diag.h"

#ifdef FEATURE_TEST_QMD_GPIO
#include "DDITlmm.h"
#include "DALDeviceId.h"
#endif

#include "qmi_client.h"
#include "qmi_cci_target.h"
#include "qmi_cci_common.h"
extern qmi_client_type        sam_pm_cl_user_handle;
extern qmi_client_type        sam_smgr_cl_user_handle;
extern qmi_client_type        sam_smgr_int_cl_user_handle;

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define SNS_SAM_QMD_MAX_NUM_DATA_REQ  2   /* use a very small value */

#ifdef FEATURE_TEST_QMD_GPIO
#define SNS_SAM_QMD_REPORT_GPIO_NUM   79  /* GPIO num indicating QMD report to AP */
#define SNS_SAM_QMD_RESULT_GPIO_NUM   80  /* GPIO num indicating QMD result : Motion/rest */
#endif

/*---------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef enum {
   SNS_SAM_MOTION_INT_ENABLE = SNS_SMGR_REG_HW_MD_INT_ENABLED_V01,
   SNS_SAM_MOTION_INT_DISABLE = SNS_SMGR_REG_HW_MD_INT_DISABLED_V01,
   SNS_SAM_MOTION_INT_OCCUR = SNS_SMGR_REG_HW_MD_INT_OCCURRED_V01
} sns_sam_mot_int_state_e;

typedef struct {
   sns_sam_motion_state_e_v01 motState;
   sns_sam_mot_int_state_e intState;
   uint8_t dataReqId;
   uint8_t algoSvcId;
} sns_sam_mot_det_state_s;

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
/* motion detection request database */
static sns_sam_mot_det_state_s sns_sam_mot_det[SNS_SAM_QMD_MAX_NUM_DATA_REQ];

/* interrupt state from motion interrupt indication message */
static uint8_t sns_sam_qmd_motint_state;

/* active count of data requests for motion interrupt */
static uint8_t sns_sam_qmd_motint_client_count;

/* client count for those that do not use motion interrupt in SMGR */
static uint8_t sns_sam_qmd_non_motint_client_count;

/* initialization flag */
static bool sns_sam_mot_det_init_flag = false;

#ifdef FEATURE_TEST_QMD_GPIO
/* GPIO handle used to handle GPIOs */
static DalDeviceHandle *gpio_handle;
#endif

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

#ifdef FEATURE_TEST_QMD_GPIO
/*=========================================================================
  FUNCTION: sns_sam_enable_gpio 
  =========================================================================*/
/*!
  @brief Configure and enable GPIOs 
 
  @return None
*/
/*=======================================================================*/
static void sns_sam_enable_gpio(uint16_t gpio_num)
{
  int32_t result = DAL_ERROR;
  DALGpioSignalType gpio_cfg;

  gpio_cfg = DAL_GPIO_CFG_OUT(gpio_num, 
                              0, 
                              DAL_GPIO_OUTPUT,
                              DAL_GPIO_NO_PULL, 
                              DAL_GPIO_2MA,
                              DAL_GPIO_LOW_VALUE);


  result = DalTlmm_ConfigGpio(gpio_handle,
                              gpio_cfg, 
                              DAL_TLMM_GPIO_ENABLE);
  if( result != DAL_SUCCESS )
  {
    SNS_SAM_PRINTF2(ERROR, "Error enabling gpio: %d, result: %d", gpio_num, result);
  }
}
#endif

/*=========================================================================
  FUNCTION:  sns_sam_init_gpios
  =========================================================================*/
/*!
  @brief Initialize GPIOs 
 
  @return None
*/
/*=======================================================================*/
void sns_sam_init_gpios(void)
{
#ifdef FEATURE_TEST_QMD_GPIO
  int32_t result = DAL_ERROR;

  result = DAL_DeviceAttach(DALDEVICEID_TLMM, &gpio_handle);
  if( result != DAL_SUCCESS )
  {
    SNS_SAM_PRINTF1(ERROR, "Error initializing gpio handle, result: %d", result);
    return; 
  }

  sns_sam_enable_gpio(SNS_SAM_QMD_REPORT_GPIO_NUM);
  sns_sam_enable_gpio(SNS_SAM_QMD_RESULT_GPIO_NUM);

#endif    
}

#ifdef FEATURE_TEST_QMD_GPIO
/*=========================================================================
  FUNCTION:  sns_sam_set_gpio_out
  =========================================================================*/
/*!
  @brief Pulls the GPIO pin up/down depending on input.

  @detail

  @param [in] gpio_num  : the GPIO number for the pin to be triggered
  @param [in] b_to_high : TRUE to go high, FALSE low
  @return
   DAL_SUCCESS -- GPIO was successfully triggered.\n
   DAL_ERROR   -- the GPIO pin is not usable as ouput
*/
/*=======================================================================*/
static int32_t sns_sam_set_gpio_out(uint16_t gpio_num, bool b_to_high)
{
  int32_t result = DAL_ERROR;
  DALGpioSignalType gpio_cfg;

  gpio_cfg = DAL_GPIO_CFG_OUT(gpio_num, 
                              0, 
                              DAL_GPIO_OUTPUT,
                              DAL_GPIO_NO_PULL, 
                              DAL_GPIO_2MA,
                              DAL_GPIO_LOW_VALUE);

  result = DalTlmm_GpioOut(gpio_handle, 
                           gpio_cfg, 
                           b_to_high ? DAL_GPIO_HIGH_VALUE : DAL_GPIO_LOW_VALUE);

  if( DAL_SUCCESS != result )
  {
    SNS_SAM_PRINTF2(ERROR, "Error setting QMD GPIO: %d, err: %d", gpio_num, result);
  }

  return result;
}
#endif

/*=========================================================================
  FUNCTION:  sns_sam_set_qmd_report_gpio
  =========================================================================*/
/*!
  @brief Set QMD report GPIO. Pulls the GPIO up when device is in motion.
  Pulls it low when in rest.

  @param[i] motionState: current QMD motion state

  @return None
*/
/*=======================================================================*/
void sns_sam_set_qmd_report_gpio(
   int32_t motionState
)
{
#ifdef FEATURE_TEST_QMD_GPIO
  bool b_to_high;
  int32_t result = DAL_ERROR;

  if( !((SNS_SAM_MOTION_MOVE_V01 == motionState) || (SNS_SAM_MOTION_REST_V01 == motionState)) )
    return;

  b_to_high = (motionState == SNS_SAM_MOTION_MOVE_V01) ? true : false;

  result = sns_sam_set_gpio_out(SNS_SAM_QMD_REPORT_GPIO_NUM, b_to_high);

  if( result != DAL_SUCCESS)
  {
    SNS_SAM_PRINTF1(ERROR, "Error setting QMD report GPIO, err %d", result);
  }
#endif
}

/*=========================================================================
  FUNCTION:  sns_sam_set_qmd_result_gpio
  =========================================================================*/
/*!
  @brief Set QMD result GPIO. Pulls the GPIO up when device is in motion.
  Pulls it low when in rest.

  @param[i] motionState: current QMD motion state

  @return None
*/
/*=======================================================================*/
void sns_sam_set_qmd_result_gpio(
   int32_t motionState
)
{
#ifdef FEATURE_TEST_QMD_GPIO
  bool b_to_high;
  int32_t result = DAL_ERROR;

  if( !((SNS_SAM_MOTION_MOVE_V01 == motionState) || (SNS_SAM_MOTION_REST_V01 == motionState)) )
    return;

  b_to_high = (motionState == SNS_SAM_MOTION_MOVE_V01) ? true : false;

  result = sns_sam_set_gpio_out(SNS_SAM_QMD_RESULT_GPIO_NUM, b_to_high);

  if( result != DAL_SUCCESS)
  {
    SNS_SAM_PRINTF1(ERROR, "Error setting QMD result GPIO, err: %d", result);
  }
#endif
}

/*=========================================================================
  FUNCTION:  sns_sam_update_power_vote
  =========================================================================*/
/*!
  @brief Update algorithm configuration per client specification

  @param[i] clientReqPtr: pointer to client request
  @param[i] addClientReq: indication if request is to add client

  @return None
*/
/*=======================================================================*/
void sns_sam_update_power_vote(
   const sns_sam_client_req_s* clientReqPtr,
   bool addClientReq)
{
#ifndef SNS_QDSP_SIM
   //count of clients on application processor requesting periodic reports
   static uint8_t sns_sam_periodic_apps_client_count;

   bool sendPowerVote = false;

   if (clientReqPtr->reqModule == SNS_MODULE_APPS_SAM ||
       clientReqPtr->reqModule == SNS_MODULE_APPS_ACM)
   {
      if (addClientReq)
      {
         //if first client registers vote power state high
         if (sns_sam_periodic_apps_client_count++ == 0)
         {
            sendPowerVote = true;
         }
      }
      else if (sns_sam_periodic_apps_client_count > 0)
      {
         //if last client deregisters vote power state low
         if (--sns_sam_periodic_apps_client_count == 0)
         {
            sendPowerVote = true;
         }
      }
   }

   if (sendPowerVote)
   {
      sns_smr_header_s msgHdr;
      uint16_t msgSize = sizeof(sns_pm_active_pwr_st_change_req_msg_v01);
      sns_err_code_e rv;

      sns_pm_active_pwr_st_change_req_msg_v01 *msgPtr = 
         (sns_pm_active_pwr_st_change_req_msg_v01*)sns_smr_msg_alloc(SNS_SAM_DBG_MOD,msgSize);
      SNS_ASSERT(msgPtr != NULL);

      SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
      msgHdr.src_module = SNS_SAM_MODULE;
      msgHdr.svc_num = SNS_PM_SVC_ID_V01;
      msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
      msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
      msgHdr.msg_id = SNS_PM_ACTIVE_PWR_ST_CHANGE_REQ_V01;
      msgHdr.body_len = msgSize;
      msgHdr.txn_id = 0;
      msgHdr.ext_clnt_id = 0;

      if (addClientReq)
      {
         msgPtr->vote_value = SNS_PM_ST_ACTIVE_HIGH_V01;
      }
      else
      {
         msgPtr->vote_value = SNS_PM_ST_ACTIVE_LOW_V01;
      }

      sns_smr_set_hdr(&msgHdr, msgPtr);
      if ((rv=sns_sam_mr_send(msgPtr, 0)) != SNS_SUCCESS)
      {
         SNS_SAM_PRINTF1(ERROR, "QMI send failed with error: %d", rv);
      }

      SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_POWER_VOTE_INFO, addClientReq,
                     clientReqPtr->mrClientId, sns_em_get_timestamp());
   }
#endif
}
/*=========================================================================
  FUNCTION:  sns_sam_send_motion_int_reg
  =========================================================================*/
/*!
  @brief Send motion interrupt registration/deregistration request

  @param[i] dataReqId: data request ID
  @param[i] enableInt: indication if request is to enable motion interrupt

  @return None
*/
/*=======================================================================*/
void sns_sam_send_motion_int_reg(
   uint8_t dataReqId,
   bool enableInt)
{
   sns_smr_header_s msgHdr;
   uint16_t msgSize = sizeof(sns_smgr_reg_hw_md_int_req_msg_v01);
   sns_smgr_reg_hw_md_int_req_msg_v01 *msgPtr;
   sns_err_code_e rv;

   if (dataReqId == SNS_SAM_INVALID_ID)
   {
      return;
   }

   msgPtr = (sns_smgr_reg_hw_md_int_req_msg_v01*)sns_smr_msg_alloc(SNS_SAM_DBG_MOD,msgSize);
   SNS_ASSERT(msgPtr != NULL);

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_SMGR_INTERNAL_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.msg_id = SNS_SMGR_REG_HW_MD_INT_REQ_V01;
   msgHdr.body_len = msgSize;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = 0;

   msgPtr->SrcModule_valid = 1;
   msgPtr->SrcModule = SNS_SAM_MODULE;
   msgPtr->ReportId = dataReqId;
   if (enableInt)
   {
      msgPtr->Action = SNS_SMGR_REG_HW_MD_INT_ADD_V01;
   }
   else
   {
      msgPtr->Action = SNS_SMGR_REG_HW_MD_INT_DEL_V01;
   }

   msgPtr->SrcModule_valid = true;
   msgPtr->SrcModule = SNS_SAM_MODULE;

   sns_smr_set_hdr(&msgHdr, msgPtr);
   if ((rv=sns_sam_mr_send(msgPtr, 0)) != SNS_SUCCESS)
   {
      SNS_SAM_PRINTF1(ERROR, "QMI send failed with error: %d", rv);
   }

   SNS_SAM_PRINTF1(MEDIUM, "MD interrupt: dataReqId %d", dataReqId);
   SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_REG_INFO,
                  enableInt, sns_em_get_timestamp());
}
/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_mot_int_resp
  =========================================================================*/
/*!
  @brief Process motion interrupt registration/deregistration response

  @param[i] smgrRespPtr: Pointer to motion interrupt registration
            response message from sensors manager

  @return None
*/
/*=======================================================================*/
void sns_sam_process_smgr_mot_int_resp(
   const void *smgrRespPtr)
{
   uint8_t r;

   if (sns_sam_qmd_motint_client_count == 0)
   {
      //response to deregister need not be processed regardless of
      //success/failure per sensors manager design
      return;
   }

   sns_smgr_reg_hw_md_int_resp_msg_v01* respPtr = 
      (sns_smgr_reg_hw_md_int_resp_msg_v01*)smgrRespPtr;

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      if(sns_sam_mot_det[r].dataReqId == respPtr->ReportId)
      {
         if (respPtr->Resp.sns_result_t == SNS_RESULT_SUCCESS_V01)
         {
            sns_sam_qmd_motint_state = (sns_sam_mot_int_state_e)(respPtr->result);
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_CLIENT_INFO,
                           sns_sam_mot_det[r].algoSvcId,
                           sns_sam_mot_det[r].dataReqId);
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_RESP,
                           sns_sam_mot_det[r].motState,
                           sns_sam_qmd_motint_state);
         }
         else
         {
            SNS_SAM_DEBUG3(ERROR, DBG_SAM_MOTION_REG_FAIL,
                           respPtr->Resp.sns_err_t,
                           sns_sam_mot_det[r].motState, 
                           sns_sam_qmd_motint_state);
            sns_sam_qmd_motint_state = SNS_SAM_MOTION_INT_OCCUR;
         }

         break;
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_mot_int_ind
  =========================================================================*/
/*!
  @brief Process motion interrupt indication for a specific target

  @param[i] smgrRespPtr: Pointer to motion interrupt indication message

  @return algorithm service ID associated with the message
*/
/*=======================================================================*/
uint8_t sns_sam_process_smgr_mot_int_ind(
   const void *smgrIndPtr)
{
   uint8_t r;
   uint8_t algoSvcId = SNS_SAM_INVALID_ID;
   sns_smgr_reg_hw_md_int_ind_msg_v01* indPtr = 
      (sns_smgr_reg_hw_md_int_ind_msg_v01*)smgrIndPtr;

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      if(sns_sam_mot_det[r].dataReqId == indPtr->ReportId)
      {
         sns_sam_qmd_motint_state = (sns_sam_mot_int_state_e)(indPtr->indication);

         if (sns_sam_mot_det[r].motState != SNS_SAM_MOTION_REST_V01)
         {
            SNS_SAM_DEBUG3(ERROR, DBG_SAM_MOTION_IND_DROP,
                           indPtr->indication, 
                           sns_sam_mot_det[r].motState,
                           sns_sam_qmd_motint_state);
            return SNS_SAM_INVALID_ID;
         }

         if (indPtr->indication == SNS_SMGR_REG_HW_MD_INT_OCCURRED_V01)
         {   
            sns_sam_mot_det[r].motState = SNS_SAM_MOTION_UNKNOWN_V01;
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_CLIENT_INFO,
                           sns_sam_mot_det[r].algoSvcId,
                           sns_sam_mot_det[r].dataReqId);
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_OCCUR,
                           sns_sam_mot_det[r].motState, sns_sam_qmd_motint_state);

            algoSvcId = sns_sam_mot_det[r].algoSvcId;
         }
         else
         {
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_CLIENT_INFO,
                           sns_sam_mot_det[r].algoSvcId,
                           sns_sam_mot_det[r].dataReqId);
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_IND,
                           sns_sam_mot_det[r].motState, sns_sam_qmd_motint_state);
         }

         break;
      }
   }

   return algoSvcId;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sam_resp
  =========================================================================*/
/*!
  @brief Process the response received from another SAM module

  @param[i] samRespPtr: Pointer to the sam response message

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_sam_resp(const void *samRespPtr)
{
   // Empty shell for DSPS 
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_motion_state_init
  =========================================================================*/
/*!
  @brief Initialize the motion state

  @param[i] motionState: new motion state of device

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_state_init(void)
{
   uint8_t r;

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      sns_sam_mot_det[r].motState = SNS_SAM_MOTION_UNKNOWN_V01;
      sns_sam_mot_det[r].dataReqId = SNS_SAM_INVALID_ID;
      sns_sam_mot_det[r].algoSvcId = SNS_SAM_INVALID_ID;
   }

   sns_sam_qmd_motint_client_count = 0;
   sns_sam_qmd_non_motint_client_count = 0;
   sns_sam_qmd_motint_state = SNS_SAM_MOTION_INT_OCCUR;
}

/*=========================================================================
  FUNCTION:  sns_sam_motion_state_update
  =========================================================================*/
/*!
  @brief Update the motion state

  @param[i] algoSvcId: algorithm service ID
  @param[i] motionState: new motion state of device

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_state_update(
   uint8_t algoSvcId,
   sns_sam_motion_state_e_v01 motionState)
{
   uint8_t r;

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      if(sns_sam_mot_det[r].algoSvcId == algoSvcId)
      {
         if(sns_sam_mot_det[r].motState == motionState)
         {
            return;
         }
         break;
      }
   }

   if (r >= SNS_SAM_QMD_MAX_NUM_DATA_REQ)
   {
      return;
   }

   SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_CLIENT_INFO,
                  sns_sam_mot_det[r].algoSvcId,
                  sns_sam_mot_det[r].dataReqId);
   SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_STATE_UPDATE,
                  sns_sam_mot_det[r].motState, motionState);

   sns_sam_mot_det[r].motState = motionState;

   if (sns_sam_qmd_non_motint_client_count == 0)
   {
      if (sns_sam_mot_det[r].motState == SNS_SAM_MOTION_REST_V01)
      {
         sns_sam_send_motion_int_reg(sns_sam_mot_det[r].dataReqId, true);
      }
      else
      {
         sns_sam_send_motion_int_reg(sns_sam_mot_det[r].dataReqId, false);
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_motion_state_start
  =========================================================================*/
/*!
  @brief Initialize the motion state

  @param[i] algoSvcId: algorithm service ID
  @param[i] motionState: new motion state of device

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_state_start(
   uint8_t algoSvcId,
   uint8_t dataReqId)
{
   uint8_t r;

   if(!sns_sam_mot_det_init_flag)
   {
      sns_sam_motion_state_init();
      sns_sam_mot_det_init_flag = true;
   }

   if(dataReqId >= SNS_SAM_MAX_DATA_REQS)
   {
      return;
   }

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      /* Request exists */
      if (sns_sam_mot_det[r].dataReqId != SNS_SAM_INVALID_ID &&
          sns_sam_mot_det[r].algoSvcId == algoSvcId)
      {
         return;
      }

      /* Adds request */
      if (sns_sam_mot_det[r].dataReqId == SNS_SAM_INVALID_ID)
      {
         sns_sam_qmd_motint_client_count++;
         sns_sam_qmd_motint_state = SNS_SAM_MOTION_INT_OCCUR;

         SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_MOTION_INT_CLIENT_INFO,
                        algoSvcId, dataReqId);
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_MOTION_STATE_START, dataReqId);

         /* Assumption: the new client separately sends an accel request.
            Motion interrupt should be disabled at this time. */
         sns_sam_mot_det[r].motState = SNS_SAM_MOTION_UNKNOWN_V01; 
         sns_sam_mot_det[r].algoSvcId = algoSvcId;
         sns_sam_mot_det[r].dataReqId = dataReqId;
         break;
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_sensor_data_stop_ind
  =========================================================================*/
/*!
  @brief Data request stop indication

  @param[i] dataReqId: index to data request in database

  @return None
*/
/*=======================================================================*/
void sns_sam_sensor_data_stop_ind(
   uint8_t dataReqId)
{
   uint8_t r;

   for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
   {
      if (dataReqId == sns_sam_mot_det[r].dataReqId)
      {
         sns_sam_qmd_motint_client_count--;

         SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_MOTION_STATE_STOP,
                        sns_sam_mot_det[r].motState,
                        sns_sam_qmd_motint_state,
                        sns_sam_mot_det[r].dataReqId);

         /* De-registers motion interrupt */
         if(sns_sam_qmd_motint_state != SNS_SAM_MOTION_INT_OCCUR &&
            sns_sam_qmd_non_motint_client_count == 0)
         {
            sns_sam_send_motion_int_reg(sns_sam_mot_det[r].dataReqId, false);
         }

         //re-initialize motion state
         sns_sam_mot_det[r].motState = SNS_SAM_MOTION_UNKNOWN_V01;
         sns_sam_mot_det[r].dataReqId = SNS_SAM_INVALID_ID;
         sns_sam_mot_det[r].algoSvcId = SNS_SAM_INVALID_ID;
         break;
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_motion_client_update
  =========================================================================*/
/*!
  @brief Update client count for motion state

  @param[i] addClient: true if client is to be added,
                       false if client is to be removed

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_client_update(
   bool addClient)
{
   uint8_t r;

   if (addClient)
   {
      if (sns_sam_qmd_non_motint_client_count == 0)
      {
         for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
         {
            sns_sam_send_motion_int_reg(sns_sam_mot_det[r].dataReqId, false);
         }
      }
      sns_sam_qmd_non_motint_client_count++;
   }
   else
   {
      sns_sam_qmd_non_motint_client_count--;
      if (sns_sam_qmd_non_motint_client_count == 0)
      {
         for(r = 0; r < SNS_SAM_QMD_MAX_NUM_DATA_REQ; r++)
         {
            if(sns_sam_mot_det[r].motState == SNS_SAM_MOTION_REST_V01)
            {
               sns_sam_send_motion_int_reg(sns_sam_mot_det[r].dataReqId, true);
            }
         }
      }
   }
}

