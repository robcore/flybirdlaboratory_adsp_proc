/*============================================================================
  FILE: sns_sam_ext.c

  This file contains the Sensors Algorithm Manager implementation

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_sam_priv.h"

#include "sns_osa.h"
#include "sns_init.h"
#include "sns_memmgr.h"
#include "sns_debug_str.h"
#include "sns_reg_common.h"

#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v01.h"
#include "sns_reg_api_v02.h"
#include "sns_time_api_v02.h"

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//SAM initialization timeout period of 10sec
#define SNS_SAM_INIT_TIMER_PERIOD_USEC 10000000

#define DSPS_HZ       DSPS_SLEEP_CLK
#define NSEC_PER_SEC  1000000000
#define USEC_PER_SEC  1000000
#define NSEC_PER_USEC 1000

/*---------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
//SAM event signal
static OS_FLAG_GRP *sns_sam_init_sig_event;

//SAM initialization timer
static sns_em_timer_obj_t sns_sam_init_timer;

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/*=========================================================================
  FUNCTION:  sns_sam_init_timer_cb
  =========================================================================*/
/*!
  @brief Callback registered for initialization timer expiry

  @param[i] argPtr: pointer to argument for callback function

  @return None
*/
/*=======================================================================*/
static void sns_sam_init_timer_cb(
   void *argPtr)
{
   uint8_t err;

   UNREFERENCED_PARAMETER(argPtr);

   sns_os_sigs_post(sns_sam_init_sig_event,
                    SNS_SAM_REPORT_TIMER_SIG,
                    OS_FLAG_SET,
                    &err);
   if (err != OS_ERR_NONE)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_TIMER_CB_SIGNALERR, err);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_reg_init_timer
  =========================================================================*/
/*!
  @brief Register timer for for SAM initialization

  @param[i] sigEventFlags: Event signal flags
  @param[i] timeout: timeout value in microseconds

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_init_timer(
   OS_FLAG_GRP *sigEventFlags,
   uint32_t timeout)
{
   sns_err_code_e err;

   sns_sam_init_sig_event = sigEventFlags;

   err = sns_em_create_timer_obj(sns_sam_init_timer_cb,
                                 NULL,
                                 SNS_EM_TIMER_TYPE_ONESHOT,
                                 &(sns_sam_init_timer));
   if (err == SNS_SUCCESS)
   {
      err = sns_em_register_timer(sns_sam_init_timer,
                                  sns_em_convert_usec_to_localtick(timeout));
      if (err == SNS_SUCCESS)
      {

        SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_REG_TIMER_STARTED, 0, timeout);
      }
   }
   if (err != SNS_SUCCESS)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_REG_TIMER_FAILED, err);
   }
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_dereg_init_timer
  =========================================================================*/
/*!
  @brief Deregister timer for SAM initialization

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_dereg_init_timer(void)
{
   sns_err_code_e err;

   err = sns_em_cancel_timer(sns_sam_init_timer);
   if (err != SNS_SUCCESS)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_DEREG_TIMER_FAILED, err);
   }

   err = sns_em_delete_timer_obj(sns_sam_init_timer);
   if (err == SNS_SUCCESS)
   {
      sns_sam_init_timer = NULL;

      SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_DEREG_TIMER_DELETED,
                     0,
                     0,
                     sns_em_get_timestamp());
   }
   else
   {
     SNS_SAM_DEBUG1(ERROR, DBG_SAM_DEREG_TIMER_FAILED, err);
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_reg_group_read_resp
  =========================================================================*/
/*!
  @brief Process registry response to group item read request

  @param[i] regRespPtr: Pointer to registry response message

  @return None
*/
/*=======================================================================*/
static void sns_sam_process_reg_group_read_resp(
   const void *regRespPtr)
{
   sns_reg_group_read_resp_msg_v02* msgPtr
      = (sns_reg_group_read_resp_msg_v02*)regRespPtr;

   if (msgPtr->resp.sns_result_t == SNS_SUCCESS)
   {
      sns_sam_process_reg_data(SNS_SAM_REG_ITEM_TYPE_GROUP,
                               msgPtr->group_id,
                               msgPtr->data_len,
                               msgPtr->data);
   }
   else
   {
      SNS_SAM_DEBUG3(HIGH, DBG_SAM_REG_RESP_ERR,
                     msgPtr->group_id,
                     msgPtr->resp.sns_result_t,
                     msgPtr->resp.sns_err_t);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_reg_single_read_resp
  =========================================================================*/
/*!
  @brief Process registry response to single item read request

  @param[i] regRespPtr: Pointer to registry response message

  @return None
*/
/*=======================================================================*/
static void sns_sam_process_reg_single_read_resp(
   const void *regRespPtr)
{
   sns_reg_single_read_resp_msg_v02* msgPtr
      = (sns_reg_single_read_resp_msg_v02*)regRespPtr;

   if (msgPtr->resp.sns_result_t == SNS_SUCCESS)
   {
      sns_sam_process_reg_data(SNS_SAM_REG_ITEM_TYPE_SINGLE,
                               msgPtr->item_id,
                               msgPtr->data_len,
                               msgPtr->data);
   }
   else
   {
      SNS_SAM_DEBUG3(HIGH, DBG_SAM_REG_RESP_ERR,
                     msgPtr->item_id,
                     msgPtr->resp.sns_result_t,
                     msgPtr->resp.sns_err_t);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_init_msg
  =========================================================================*/
/*!
  @brief Process messages from SAM's input queue during initialization

  @return Number of messages processed
*/
/*=======================================================================*/
static uint8_t sns_sam_process_init_msg(void)
{
   void *msgPtr;
   sns_smr_header_s msgHdr;
   sns_err_code_e err;
   uint8_t numMsgProcessed = 0;

   while ((msgPtr = sns_sam_mr_msg_rcv()) != NULL)
   {
      err = sns_smr_get_hdr(&msgHdr, msgPtr);
      if (err != SNS_SUCCESS)
      {
         SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROC_MSG_HDR_ERR, err);

         sns_smr_msg_free(msgPtr);
         continue;
      }

      err = SNS_ERR_FAILED;

      if (msgHdr.src_module == SNS_MODULE_APPS_REG)
      {
         if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
         {
            if (msgHdr.msg_id == SNS_REG_GROUP_READ_RESP_V02)
            {
               sns_sam_process_reg_group_read_resp(msgPtr);
               err = SNS_SUCCESS;
               numMsgProcessed++;
            }
            else if (msgHdr.msg_id == SNS_REG_SINGLE_READ_RESP_V02)
            {
               sns_sam_process_reg_single_read_resp(msgPtr);
               err = SNS_SUCCESS;
               numMsgProcessed++;
            }
         }
      }

      if (err != SNS_SUCCESS)
      {
         SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_MSG_DROP,
                        msgHdr.msg_id, msgHdr.src_module, msgHdr.svc_num);
      }

      sns_smr_msg_free(msgPtr);
   }

   return numMsgProcessed;
}

/*=========================================================================
  FUNCTION:  sns_sam_req_reg_data
  =========================================================================*/
/*!
  @brief Request registry data

  @param[i] regItemType: Registry item type (single / group)
  @param[i] regItemId: Registry item identifier

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_req_reg_data(
   sns_sam_reg_item_type_e regItemType,
   uint32_t regItemId)
{
   void*            reqMsgPtr = NULL;
   sns_smr_header_s reqMsgHdr;
   sns_err_code_e   err;

   SNS_OS_MEMZERO(&reqMsgHdr, sizeof(sns_smr_header_s));
   reqMsgHdr.src_module = SNS_SAM_MODULE;
   reqMsgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   reqMsgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   reqMsgHdr.svc_num = SNS_REG2_SVC_ID_V01;

   reqMsgHdr.txn_id = 0;
   reqMsgHdr.ext_clnt_id = 0;

   if (regItemType == SNS_SAM_REG_ITEM_TYPE_GROUP)
   {
     reqMsgHdr.msg_id = SNS_REG_GROUP_READ_REQ_V02;
     reqMsgHdr.body_len = sizeof(sns_reg_group_read_req_msg_v02);
   }
   else if (regItemType == SNS_SAM_REG_ITEM_TYPE_SINGLE)
   {
     reqMsgHdr.msg_id = SNS_REG_SINGLE_READ_REQ_V02;
     reqMsgHdr.body_len = sizeof(sns_reg_single_read_req_msg_v02);
   }
   else
   {
     return SNS_ERR_FAILED;
   }

   reqMsgPtr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD,reqMsgHdr.body_len);

   if(reqMsgPtr == NULL)
   {
     return SNS_ERR_NOMEM;
   }

   if (regItemType == SNS_SAM_REG_ITEM_TYPE_GROUP)
   {
     ((sns_reg_group_read_req_msg_v02*)reqMsgPtr)->group_id = regItemId;
   }
   else
   {
     ((sns_reg_single_read_req_msg_v02*)reqMsgPtr)->item_id = regItemId;
   }

   sns_smr_set_hdr(&reqMsgHdr, reqMsgPtr);

   err = sns_sam_mr_send(reqMsgPtr, NULL);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_registry_read_resp
  =========================================================================*/
/*!
  @brief Gets response to registry read request

  @detail
  Waits for a maximum of tiemout microseconds to get and process response
  to one registry read request

  @param[i] timeout: time in microseconds to wait for response

  @return None
*/
/*=======================================================================*/
void sns_sam_get_registry_read_resp(
   uint32_t timeout)
{
   if (sns_sam_reg_init_timer(sns_sam_sig_event_acc(), timeout) == SNS_SUCCESS)
   {
      uint8_t err;
      OS_FLAGS sigFlags;

      //wait for event
      sigFlags = sns_os_sigs_pend(sns_sam_sig_event_acc(),
                                  SNS_SAM_SIGNAL_MASK,
                                  OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                  0,
                                  &err);
      SNS_ASSERT(err == 0);

      //message event check
      if (sigFlags & SNS_SAM_MSG_SIG)
      {
         uint8_t numMsgProcessed = 0;
         sigFlags &= (~SNS_SAM_MSG_SIG);
         numMsgProcessed = sns_sam_process_init_msg();
         SNS_SAM_PRINTF1( LOW, "SAM processed %d registry read reqs", numMsgProcessed );
      }
      //client report timer event check
      if (sigFlags & SNS_SAM_REPORT_TIMER_SIG)
      {
         sigFlags &= (~SNS_SAM_REPORT_TIMER_SIG);
         SNS_SAM_PRINTF0( ERROR, "SAM: Registry read timeout expired" );
      }
      if (sigFlags != 0)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_PROCESS_EVT_UNKWN_EVT, sigFlags);
      }
   }

   sns_sam_dereg_init_timer();
}

/*=========================================================================
  FUNCTION:  sns_sam_send_sensor_info_req
  =========================================================================*/
/*!
  @brief Request sensor information

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_sensor_info_req(void)
{
   sns_smr_header_s msgHdr;
   void *reqMsgPtr = NULL;
   sns_err_code_e   err;

   reqMsgPtr = (void *)sns_smr_msg_alloc(SNS_SAM_DBG_MOD,0);
   if(reqMsgPtr == NULL)
   {
     return SNS_ERR_NOMEM;
   }

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_SMGR_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.msg_id = SNS_SMGR_ALL_SENSOR_INFO_REQ_V01;
   msgHdr.body_len = 0;

   msgHdr.txn_id = 0;
   //SAM uses external client id 0 for requests to SMGR
   msgHdr.ext_clnt_id = 0;

   sns_smr_set_hdr(&msgHdr, reqMsgPtr);

   err = sns_sam_mr_send(reqMsgPtr, NULL);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_type_from_sensor_id
  =========================================================================*/
/*!
  @brief Returns sensor type for given sensor ID

  @param[i] sensorId: Sensor ID from SMGR

  @return Sensor type
*/
/*=======================================================================*/
static int sns_sam_get_type_from_sensor_id(
   int sensorId)
{
   int i = -1;
   switch( sensorId )
   {
   case SNS_SMGR_ID_ACCEL_V01:
      i = SNS_SAM_ACCEL;
      break;
   case SNS_SMGR_ID_GYRO_V01:
      i = SNS_SAM_GYRO;
      break;
   case SNS_SMGR_ID_MAG_V01:
      i = SNS_SAM_MAG;
      break;
   case SNS_SMGR_ID_PRESSURE_V01:
      i = SNS_SAM_PRESSURE;
      break;
   case SNS_SMGR_ID_PROX_LIGHT_V01:
      i = SNS_SAM_PROX_LIGHT;
      break;
   default:
      break;
   }
   return i;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_single_sensor_info_response
  =========================================================================*/
/*!
  @brief Process single sensor information response

  @param[i] respMsgPtr: response message pointer
  @param[o] sensorInfo: sensor status information

  @return None
*/
/*=======================================================================*/
static void sns_sam_process_single_sensor_info_response(
   void* respMsgPtr,
   sns_sam_sensor_info_s sensorInfo[])
{
   int i = -1;
   uint32_t j;
   sns_smgr_single_sensor_info_resp_msg_v01* msgPtr =
     (sns_smgr_single_sensor_info_resp_msg_v01 *)respMsgPtr;

   if (msgPtr->Resp.sns_result_t == SNS_SUCCESS)
   {
      for( j = 0; j < msgPtr->SensorInfo.data_type_info_len; j++ )
      {
         i = sns_sam_get_type_from_sensor_id( msgPtr->SensorInfo.data_type_info[j].SensorID );
         if( i != -1 )
         {
            sensorInfo[i].maxPower = FX_CONV_Q16(msgPtr->SensorInfo.data_type_info[j].MaxPower, 0)/1000; // convert to mA in Q16
            sensorInfo[i].maxSampleRate = FX_CONV_Q16(msgPtr->SensorInfo.data_type_info[j].MaxSampleRate, 0);
         }
      }
   }

   sns_smr_msg_free(msgPtr);
}

/*=========================================================================
  FUNCTION:  sns_sam_send_single_sensor_info_req
  =========================================================================*/
/*!
  @brief Request attributes for given sensor ID

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_send_single_sensor_info_req(
   uint8_t sensorId)
{
   sns_smr_header_s msgHdr;
   sns_smgr_single_sensor_info_req_msg_v01 *reqMsgPtr = NULL;
   sns_err_code_e   err;
   int msgSize = sizeof(sns_smgr_single_sensor_info_req_msg_v01);

   reqMsgPtr = (sns_smgr_single_sensor_info_req_msg_v01 *)sns_smr_msg_alloc(SNS_SAM_DBG_MOD,
               msgSize);
   if(reqMsgPtr == NULL)
   {
     return SNS_ERR_NOMEM;
   }
   reqMsgPtr->SensorID = sensorId;

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_SMGR_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.msg_id = SNS_SMGR_SINGLE_SENSOR_INFO_REQ_V01;
   msgHdr.body_len = msgSize;

   msgHdr.txn_id = 0;
   //SAM uses external client id 0 for requests to SMGR
   msgHdr.ext_clnt_id = 0;

   sns_smr_set_hdr(&msgHdr, reqMsgPtr);

   err = sns_sam_mr_send(reqMsgPtr, NULL);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_all_sensor_attributes
  =========================================================================*/
/*!
  @brief Get attributes for all sensors registered with SMGR

  @param[i] sigEventPtr: pointer to the signal group flag
  @param[o] sensorInfo: sensor status information

  @return None
*/
/*=======================================================================*/
static void sns_sam_get_all_sensor_attributes(
   OS_FLAG_GRP *sigEventPtr,
   sns_sam_sensor_info_s sensorInfo[])
{
   int reqCnt = 0;
   OS_FLAGS sigFlags = 0;
   void* msgPtr;
   sns_smr_header_s msgHdr;
   uint8_t err, i;

   for( i = 0; i < SNS_SAM_NUM_SENSORS; i++ )
   {
      if (sensorInfo[i].valid == true)
      {
         sns_sam_send_single_sensor_info_req(sensorInfo[i].sensorId);
         reqCnt++;
      }

   }

   if( reqCnt > 0 )
   {
      if (sns_sam_reg_init_timer(sigEventPtr, SNS_SAM_INIT_TIMER_PERIOD_USEC) == SNS_SUCCESS)
      {
         while( reqCnt > 0 )
         {
            //wait for sensor info response
            sigFlags = sns_os_sigs_pend(sns_sam_init_sig_event,
                                        SNS_SAM_SIGNAL_MASK,
                                        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                        0,
                                        &err);
            SNS_ASSERT(err == 0);

            //message event check
            if (sigFlags & SNS_SAM_MSG_SIG)
            {
               while ((msgPtr = sns_sam_mr_msg_rcv()) != NULL)
               {
                  err = sns_smr_get_hdr(&msgHdr, msgPtr);
                  if (err != SNS_SUCCESS)
                  {
                     SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROC_MSG_HDR_ERR, err);

                     sns_smr_msg_free(msgPtr);
                     continue;
                  }

                  if (msgHdr.src_module == SNS_MODULE_DSPS_SMGR)
                  {
                     if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
                     {
                        if (msgHdr.msg_id == SNS_SMGR_SINGLE_SENSOR_INFO_RESP_V01)
                        {
                           sns_sam_process_single_sensor_info_response(msgPtr, sensorInfo);
                           reqCnt--;
                        }
                        else
                        {
                           sns_smr_msg_free(msgPtr);
                           continue;
                        }
                     }
                  }
               }
               sigFlags &= (~SNS_SAM_MSG_SIG);
            }
            //client report timer event check
            if (sigFlags & SNS_SAM_REPORT_TIMER_SIG)
            {
               SNS_SAM_PRINTF1(ERROR, "sns_sam_get_all_sensor_attrib: Timer expired. %d responses pending", reqCnt);
               sigFlags &= (~SNS_SAM_REPORT_TIMER_SIG);
               break;
            }
            if (sigFlags != 0)
            {
               SNS_SAM_PRINTF1(ERROR, "sns_sam_get_all_sensor_attrib: Unknown event %x", sigFlags);
            }
         }
      }
      sns_sam_dereg_init_timer();
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sensor_info_response
  =========================================================================*/
/*!
  @brief Process response information response

  @param[i] respMsgPtr: response message pointer
  @param[o] sensorInfo: sensor status information

  @return boolean indicating if sensor info was received.
*/
/*=======================================================================*/
bool sns_sam_process_sensor_info_response(
   void* respMsgPtr,
   sns_sam_sensor_info_s sensorInfo[])
{
   uint8_t i;
   int j = -1;
   sns_smgr_all_sensor_info_resp_msg_v01* msgPtr =
     (sns_smgr_all_sensor_info_resp_msg_v01 *)respMsgPtr;
   bool gotSnsInfo = false;

   if (msgPtr->Resp.sns_result_t == SNS_SUCCESS)
   {
      gotSnsInfo = true;
      for (i=0; i<msgPtr->SensorInfo_len && i<SNS_SMGR_MAX_SENSOR_NUM_V01; i++)
      {
         j = sns_sam_get_type_from_sensor_id( msgPtr->SensorInfo[i].SensorID );
         if( j != -1 )
         {
            sensorInfo[j].valid = true;
            sensorInfo[j].sensorId = msgPtr->SensorInfo[i].SensorID;
         }
      }
   }

   sns_smr_msg_free(msgPtr);

   return gotSnsInfo;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_sensor_info
  =========================================================================*/
/*!
  @brief Get sensor information from sensor manager

  @param[i] sigEventPtr: pointer to the signal group flag
  @param[o] sensorInfo: sensor status information

  @return true, if response was received from SMGR; false, otherwise
*/
/*=======================================================================*/
bool sns_sam_get_sensor_info(
   OS_FLAG_GRP *sigEventPtr,
   sns_sam_sensor_info_s sensorInfo[])
{
   OS_FLAGS sigFlags = 0;
   void* msgPtr;
   sns_smr_header_s msgHdr;
   uint8_t err, i;
   bool gotSnsInfo = false;

   //request sensor info
   if (sns_sam_send_sensor_info_req() == SNS_SUCCESS)
   {
      if (sns_sam_reg_init_timer(sigEventPtr, SNS_SAM_INIT_TIMER_PERIOD_USEC) == SNS_SUCCESS)
      {
         while( !gotSnsInfo )
         {
            //wait for sensor info response
            sigFlags = sns_os_sigs_pend(sns_sam_init_sig_event,
                                        SNS_SAM_SIGNAL_MASK,
                                        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                        0,
                                        &err);
            SNS_ASSERT(err == 0);

            //message event check
            if (sigFlags & SNS_SAM_MSG_SIG)
            {
               while ((msgPtr = sns_sam_mr_msg_rcv()) != NULL)
               {
                  err = sns_smr_get_hdr(&msgHdr, msgPtr);
                  if (err != SNS_SUCCESS)
                  {
                     SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROC_MSG_HDR_ERR, err);

                     sns_smr_msg_free(msgPtr);
                     continue;
                  }

                  if (msgHdr.src_module == SNS_MODULE_DSPS_SMGR)
                  {
                     if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
                     {
                        if (msgHdr.msg_id == SNS_SMGR_ALL_SENSOR_INFO_RESP_V01)
                        {
                           gotSnsInfo =
                              sns_sam_process_sensor_info_response(msgPtr, sensorInfo);
                           break;
                        }
                        else
                        {
                           sns_smr_msg_free(msgPtr);
                           continue;
                        }
                     }
                  }
               }
               sigFlags &= (~SNS_SAM_MSG_SIG);
            }
            //client report timer event check
            if (sigFlags & SNS_SAM_REPORT_TIMER_SIG)
            {
               sigFlags &= (~SNS_SAM_REPORT_TIMER_SIG);
               break;
            }
            if (sigFlags != 0)
            {
               SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_PROCESS_EVT_UNKWN_EVT, sigFlags);
            }
         }
      }
      sns_sam_dereg_init_timer();
   }

   //if sensor info is not received from sensor manager default to
   //all algorithms supported
   if (!gotSnsInfo)
   {
      for (i = 0; i < SNS_SAM_NUM_SENSORS; i++)
      {
         sensorInfo[i].valid = true;
      }
   }
   else
   {
      sns_sam_get_all_sensor_attributes(sigEventPtr, sensorInfo);
   }
   return gotSnsInfo;
}

/*=========================================================================
  FUNCTION:  sns_sam_time_send_sync_req
  =========================================================================*/
/*!
  @brief    Sends a message to Time Service within SAM framework

  @return   None
*/
/*=======================================================================*/
void sns_sam_time_send_sync_req()
{
   sns_reg_single_read_req_msg_v02  *time_msg_ptr = NULL;
   sns_smr_header_s time_msg_hdr;

   /* Populates msg header */
   SNS_OS_MEMZERO(&time_msg_hdr, sizeof(sns_smr_header_s));
   time_msg_hdr.src_module   = SNS_SAM_MODULE;
   time_msg_hdr.dst_module   = SNS_MODULE_APPS_TIME;
   time_msg_hdr.msg_type     = SNS_SMR_MSG_TYPE_REQ;
   time_msg_hdr.priority     = SNS_SMR_MSG_PRI_LOW;
   time_msg_hdr.svc_num      = SNS_TIME2_SVC_ID_V01;
   time_msg_hdr.msg_id       = SNS_TIME_TIMESTAMP_REQ_V02;
   time_msg_hdr.ext_clnt_id  = 0;
   time_msg_hdr.body_len     = 0;

   /* Populates msg body */
   time_msg_ptr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD, 0);
   SNS_ASSERT(time_msg_ptr != NULL);

   sns_smr_set_hdr(&time_msg_hdr, time_msg_ptr);
   sns_sam_mr_send(time_msg_ptr, NULL);
}

/*=========================================================================
  FUNCTION:  sns_sam_process_time_response
  =========================================================================*/
sns_err_code_e sns_sam_process_time_response(
    const void *msgPtr,
    const sns_smr_header_s *msgHdr)
{
   sns_err_code_e   err = SNS_SUCCESS;

   if (msgHdr->msg_id == SNS_TIME_TIMESTAMP_RESP_V02)
   {
      switch (msgHdr->svc_num)
      {
      case SNS_TIME2_SVC_ID_V01:
      {
         sns_time_timestamp_resp_msg_v02 *timePtr =
            (sns_time_timestamp_resp_msg_v02*) msgPtr;

         if( 0 == timePtr->resp.sns_result_t )
         {
            if(timePtr->timestamp_dsps_valid && timePtr->timestamp_apps_valid)
            {
               uint64_t apps_us = timePtr->timestamp_apps / NSEC_PER_USEC;
               uint64_t dsps_us = ((uint64_t)timePtr->timestamp_dsps * USEC_PER_SEC) / (DSPS_HZ);

               sns_sam_time_state_s sam_time_state = sns_sam_get_time_state();

               /* Computes time offset (usec) */
               sam_time_state.ts_offset = apps_us - dsps_us;
               sam_time_state.ts_offset_valid = true;

               /* Checks for DSPS clock rollover
                * Note: This will eventually be done in SNS Time Service instead
                */
               if (dsps_us < sam_time_state.ts_dsps_prev)
               {
                  (sam_time_state.ts_dsps_ro_cnt)++;
                  sam_time_state.ts_offset += (sam_time_state.ts_dsps_ro_cnt * UINT32_MAX);
               }

               sam_time_state.ts_dsps_prev = dsps_us;
               sns_sam_set_time_state(&sam_time_state);
            }
         }
         break;
      }
      default:
         // Should not happen.
         err = SNS_ERR_BAD_PARM;
         break;
      }
   }
   else
   {
      err = SNS_ERR_BAD_PARM;
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_registry_version_req
  =========================================================================*/
/*!
  @brief  Sends version request message to Registry service.

  @return  None
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_send_registry_version_req( void )
{
   sns_err_code_e err;

   // Send SMGR API version request
   sns_smr_header_s msgHdr;
   uint16_t msgSize = 0; // no payload
   void* msgPtr = (void *) sns_smr_msg_alloc(SNS_SAM_DBG_MOD, msgSize);
   SNS_ASSERT(msgPtr != NULL);

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.dst_module = SNS_MODULE_APPS_REG;
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_REG2_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   msgHdr.body_len = msgSize;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = 0;
   msgHdr.msg_id = SNS_REG_VERSION_REQ_V02;

   sns_smr_set_hdr(&msgHdr, msgPtr);
   err = sns_sam_mr_send(msgPtr, NULL);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_registry_version
  =========================================================================*/
/*!
  @brief  Get registry version to check if default sensor report rates are
          available.

  @return  registry version, 0 if unavailable
*/
/*=======================================================================*/
uint32_t sns_sam_get_registry_version(
   OS_FLAG_GRP *sigEventPtr)
{
   OS_FLAGS sigFlags = 0;
   void* msgPtr;
   sns_smr_header_s msgHdr;
   uint8_t err;
   bool gotVersion = false;
   uint32_t sensor_registry_version = 0;

   //request sensor info
   if (sns_sam_send_registry_version_req() == SNS_SUCCESS)
   {
      if (sns_sam_reg_init_timer(sigEventPtr, SNS_SAM_INIT_TIMER_PERIOD_USEC) == SNS_SUCCESS)
      {
         while( !gotVersion )
         {
            //wait for sensor info response
            sigFlags = sns_os_sigs_pend(sns_sam_init_sig_event,
                                        SNS_SAM_SIGNAL_MASK,
                                        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                        0,
                                        &err);
            SNS_ASSERT(err == 0);

            //message event check
            if (sigFlags & SNS_SAM_MSG_SIG)
            {
               while ((msgPtr = sns_sam_mr_msg_rcv()) != NULL)
               {
                  err = sns_smr_get_hdr(&msgHdr, msgPtr);
                  if (err != SNS_SUCCESS)
                  {
                     SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROC_MSG_HDR_ERR, err);

                     sns_smr_msg_free(msgPtr);
                     continue;
                  }

                  if (msgHdr.src_module == SNS_MODULE_APPS_REG)
                  {
                     if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
                     {
                        if (msgHdr.msg_id == SNS_REG_VERSION_RESP_V02)
                        {
                           sns_common_version_resp_msg_v01* respMsgPtr =
                              (sns_common_version_resp_msg_v01 *)msgPtr;
                           if (respMsgPtr->resp.sns_result_t == SNS_SUCCESS)
                           {
                              sensor_registry_version =
                                 respMsgPtr->interface_version_number;
                           }
                           gotVersion = true;
                           break;
                        }
                        else
                        {
                           sns_smr_msg_free(msgPtr);
                           continue;
                        }
                     }
                  }
               }
               sigFlags &= (~SNS_SAM_MSG_SIG);
            }
            //client report timer event check
            if (sigFlags & SNS_SAM_REPORT_TIMER_SIG)
            {
               sigFlags &= (~SNS_SAM_REPORT_TIMER_SIG);
               break;
            }
            if (sigFlags != 0)
            {
               SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_PROCESS_EVT_UNKWN_EVT, sigFlags);
            }
         }
      }
      sns_sam_dereg_init_timer();
   }

   return sensor_registry_version;
}
