/*============================================================================
  FILE: sns_sam.c

  This file contains the Sensors Algorithm Manager implementation

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

#define __SNS_MODULE__ SNS_SAM

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_sam_priv.h"

#include "sns_osa.h"
#include "sns_init.h"
#include "sns_memmgr.h"
#include "sns_debug_str.h"
#include "fixed_point.h"
#include "sns_reg_common.h"

#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v01.h"
#include "sns_reg_api_v02.h"

#ifdef SNS_DSPS_BUILD
#include "sns_profiling.h"
#endif

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

//SAM registry read timeout periods (low - 100ms; high - 1s)
#define SNS_SAM_REG_READ_TIMER_LOW_PERIOD_USEC   100000
#define SNS_SAM_REG_READ_TIMER_HIGH_PERIOD_USEC 1000000

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
//SAM task stack
static OS_STK sns_sam_task_stk[SNS_SAM_MODULE_STK_SIZE];

//SAM event signal
static OS_FLAG_GRP *sns_sam_sig_event;

//algorithm database
static sns_sam_algo_s* sns_sam_algo_dbase[SNS_SAM_MAX_ALGOS];

//algorithm instance database
static sns_sam_algo_inst_s* sns_sam_algo_inst_dbase[SNS_SAM_MAX_ALGO_INSTS];
//algorithm instance count
static uint8_t sns_sam_algo_inst_count;

//client request database
static sns_sam_client_req_s* sns_sam_client_req_dbase[SNS_SAM_MAX_CLIENT_REQS];
//client request count
static uint8_t sns_sam_client_req_count;

//sensor data request database
static sns_sam_data_req_s* sns_sam_data_req_dbase[SNS_SAM_MAX_DATA_REQS];
//data request count
static uint8_t sns_sam_data_req_count;

//SMGR Buffering Support flag
static bool sns_sam_smgr_buffering_flag = false;

static uint32_t sns_sam_sensor_registry_version = 0;

static sns_sam_time_state_s sns_sam_time_state;

#if defined(SNS_PLAYBACK_SKIP_SMGR) || defined(SNS_QDSP_SIM)
//time for next periodic report; initialized to maximum
static uint32_t nextReportTime[SNS_SAM_MAX_CLIENT_REQS] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
static uint8_t nextReportTimeEnable[SNS_SAM_MAX_CLIENT_REQS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#endif

OS_FLAGS sam_sig_mask;

static sns_sam_sensor_uuid_s sns_sam_sensor_uuids[SNS_SAM_NUM_SENSORS];
static sns_sam_sensor_info_s sns_sam_sensor_info_dbase[SNS_SAM_NUM_SENSORS];

// Client processor state database - uses sns_proc_type_e_v01 as index
static sns_sam_proc_monitor_s sns_sam_client_proc_dbase[SNS_SAM_MAX_CLIENT_PROCESSORS];

// Service id of last registered algorithm that needs item(s) from registry
static uint8_t sns_sam_last_algo_with_registry_dep;

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/
#ifdef SNS_SAM_UNIT_TEST
extern sns_err_code_e sns_sam_test_init(void);
#endif

static sns_err_code_e sns_sam_process_sam_ind(const void *samIndPtr);

static void sns_sam_handle_report_timeout(void);

extern void sns_smgr_app_state_change(bool new_suspend_state);

extern void sns_sam_get_modem_info_delayed(void);

/*=========================================================================
  FUNCTION:  sns_sam_get_time_state
  =========================================================================*/
sns_sam_time_state_s sns_sam_get_time_state()
{
  return sns_sam_time_state;
}

/*=========================================================================
  FUNCTION:  sns_sam_set_time_state
  =========================================================================*/
void sns_sam_set_time_state(sns_sam_time_state_s *sam_time_state)
{
  SNS_OS_MEMCOPY( &sns_sam_time_state, sam_time_state, sizeof(sns_sam_time_state_s) );
}

/*=========================================================================
  FUNCTION:  sns_sam_data_req_dbase_acc
  =========================================================================*/
/*!
  @brief Accessor function for the sns_sam_data_req_dbase array.

  @param[i] index: Index into the request database.

  @return Database entry, or NULL, if index is out of bounds.
*/
/*=======================================================================*/
sns_sam_data_req_s* sns_sam_data_req_dbase_acc(int32_t index)
{
  return ( index >= SNS_SAM_MAX_DATA_REQS || index < 0 ) ? NULL : sns_sam_data_req_dbase[ index ];
}

/*=========================================================================
  FUNCTION:  sns_sam_algo_dbase_acc
  =========================================================================*/
/*!
  @brief Accessor function for the sns_sam_algo_dbase array.

  @param[i] index: Index into the request database.

  @return Database entry, or NULL, if index is out of bounds.
*/
/*=======================================================================*/
sns_sam_algo_s* sns_sam_algo_dbase_acc(int32_t index)
{
  return ( index >= SNS_SAM_MAX_ALGOS || index < 0 ) ? NULL : sns_sam_algo_dbase[ index ];
}

/*=========================================================================
  FUNCTION:  sns_sam_sig_event_acc
  =========================================================================*/
/*!
  @brief Accessor function for the sns_sam_sig_event object.

  @return sns_sam_sig_event
*/
/*=======================================================================*/
OS_FLAG_GRP* sns_sam_sig_event_acc(void) { return sns_sam_sig_event; }

/*=========================================================================
  FUNCTION:  sns_sam_timer_cb
  =========================================================================*/
/*!
  @brief Callback registered for timer expiry

  @param[i] argPtr: pointer to argument for callback function

  @return None
*/
/*=======================================================================*/
void sns_sam_timer_cb(void *argPtr)
{
   uint32_t clientReqId = (uint32_t)(uintptr_t)argPtr;

   if (clientReqId < SNS_SAM_MAX_CLIENT_REQS &&
       sns_sam_client_req_dbase[clientReqId] != NULL)
   {
      sns_sam_client_req_dbase[clientReqId]->timeout = true;

#if defined(SNS_QDSP_SIM)
      sns_sam_handle_report_timeout();
#else
     {
      uint8_t err;
      sns_os_sigs_post(sns_sam_sig_event,
                       SNS_SAM_REPORT_TIMER_SIG,
                       OS_FLAG_SET,
                       &err);
      if (err != OS_ERR_NONE)
      {
         SNS_SAM_DEBUG1(ERROR, DBG_SAM_TIMER_CB_SIGNALERR, err);
      }
     }
#endif
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_reg_timer
  =========================================================================*/
/*!
  @brief Register timer for client reports

  @param[i] clientReqId: client request id
  @param[i] period: timer period

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_timer(
   uint32_t clientReqId,
   uint32_t period)
{
   sns_err_code_e err = SNS_SUCCESS;
   sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];

   sns_em_timer_type_e timerType;
   if (clientReqPtr->reportType == SNS_SAM_PERIODIC_REPORT)
   {
      timerType = SNS_EM_TIMER_TYPE_PERIODIC;
   }
   else if (clientReqPtr->reportType == SNS_SAM_ONE_SHOT_REPORT ||
           (clientReqPtr->batchInfo != NULL &&
            clientReqPtr->batchInfo->batchPeriod != 0))
   {
      timerType = SNS_EM_TIMER_TYPE_ONESHOT;
   }
   else
   {
      return SNS_ERR_FAILED;
   }

   if (clientReqPtr->timer == NULL)
   {
      err = sns_em_create_timer_obj(sns_sam_timer_cb,
                                    (void*)(intptr_t)clientReqId,
                                    timerType,
                                    &(clientReqPtr->timer));
   }

#if !defined(SNS_PLAYBACK_SKIP_SMGR) && !defined(SNS_QDSP_SIM)
   if (err == SNS_SUCCESS)
   {
      err = sns_em_register_timer(clientReqPtr->timer,
                                  period);
      if (err == SNS_SUCCESS)
      {

        SNS_SAM_DEBUG2(LOW, DBG_SAM_REG_TIMER_STARTED,
                       sns_sam_mr_get_client_id(clientReqPtr->mrClientId), clientReqPtr->period);
      }
      else
      {
        SNS_SAM_DEBUG1(ERROR, DBG_SAM_REG_TIMER_FAILED, err);
      }
   }
#endif

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_dereg_timer
  =========================================================================*/
/*!
  @brief Deregister timer

  @param[i] clientReqId: client request id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_dereg_timer(
   uint8_t clientReqId)
{
   sns_err_code_e err;

   if (sns_sam_client_req_dbase[clientReqId]->timer == NULL)
   {
      return SNS_SUCCESS;
   }

   err = sns_em_delete_timer_obj(sns_sam_client_req_dbase[clientReqId]->timer);
   if (err == SNS_SUCCESS)
   {
      sns_sam_client_req_dbase[clientReqId]->timer = NULL;

      SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_DEREG_TIMER_DELETED,
                     sns_sam_mr_get_client_id(sns_sam_client_req_dbase[clientReqId]->mrClientId),
                     sns_sam_client_req_dbase[clientReqId]->reportId,
                     sns_em_get_timestamp());
   }
   else
   {
     SNS_SAM_DEBUG1(ERROR, DBG_SAM_DEREG_TIMER_FAILED, err);
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_timer_get_remaining_time
  =========================================================================*/
/*!
  @brief Gets the timer remaining duration in microseconds

  @param[i] clientReqId: client request id
  @param[o] remaining: remaining duration in microseconds
 
  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_timer_get_remaining_time(
   uint8_t clientReqId, uint32_t *remaining)
{
   if (sns_sam_client_req_dbase[clientReqId]->timer == NULL)
   {
      return SNS_ERR_FAILED;
   }

   return sns_em_timer_get_remaining_time(sns_sam_client_req_dbase[clientReqId]->timer, remaining);
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_report
  =========================================================================*/
/*!
  @brief get the current algorithm report

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm report for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_rpt_s *sns_sam_get_algo_report(
   uint8_t algoInstId)
{
   sns_sam_algo_rpt_s *algoRepPtr = NULL;

   if (algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
       sns_sam_algo_inst_dbase[algoInstId] != NULL)
   {
      algoRepPtr = &(sns_sam_algo_inst_dbase[algoInstId]->outputData);
   }

   return algoRepPtr;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_config
  =========================================================================*/
/*!
  @brief get the current algorithm configuration

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm configuration for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_mem_s *sns_sam_get_algo_config(
   uint8_t algoInstId)
{
   sns_sam_algo_mem_s *algoConfigPtr = NULL;

   if (algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
       sns_sam_algo_inst_dbase[algoInstId] != NULL)
   {
      algoConfigPtr = &(sns_sam_algo_inst_dbase[algoInstId]->configData);
   }

   return algoConfigPtr;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_state
  =========================================================================*/
/*!
  @brief get the current algorithm state

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm state for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_mem_s *sns_sam_get_algo_state(
   uint8_t algoInstId)
{
   sns_sam_algo_mem_s *algoStatePtr = NULL;

   if (algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
       sns_sam_algo_inst_dbase[algoInstId] != NULL)
   {
      algoStatePtr = &(sns_sam_algo_inst_dbase[algoInstId]->stateData);
   }

   return algoStatePtr;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_inst_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified algorithm instance

  @param[i] algoInstId: index to the algorithm instance in the database

  @return handle to the specified algorithm instance if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_algo_inst_s* sns_sam_get_algo_inst_handle(
   uint8_t algoInstId)
{
    return ( (algoInstId < SNS_SAM_MAX_ALGO_INSTS) ?
               sns_sam_algo_inst_dbase[algoInstId] : NULL );
}

/*=========================================================================
  FUNCTION:  sns_sam_get_client_req_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified client request

  @param[i] clientReqId: index to the client request in the database

  @return handle to the specified client request if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_client_req_s* sns_sam_get_client_req_handle(
   uint8_t clientReqId)
{
    return ( (clientReqId < SNS_SAM_MAX_CLIENT_REQS) ?
               sns_sam_client_req_dbase[clientReqId] : NULL );
}

/*=========================================================================
  FUNCTION:  sns_sam_get_smgr_msg_req_type
  =========================================================================*/
/*!
  @brief  Determines the type of message request used to communicate with
          Sensor Manager.

  @param[i] algoSvcId: algorithm service ID

  @return  message request ID
*/
/*=======================================================================*/
uint8_t sns_sam_get_smgr_msg_req_type(
   uint8_t algoSvcId)
{
   uint8_t retVal = SNS_SMGR_REPORT_REQ_V01;
   if( sns_sam_smgr_buffering_flag )
   {
      if( algoSvcId == SNS_SAM_GYROINT_SVC_ID_V01 )
      {
         // Gyroint uses the buffering query API (report rate = 0)
         retVal = SNS_SMGR_BUFFERING_REQ_V01;
      }
      else
      {
         uint8_t algoIndex = sns_sam_get_algo_index(algoSvcId);
         if( algoIndex < SNS_SAM_MAX_ALGOS &&
             sns_sam_algo_dbase[algoIndex] != NULL &&
             sns_sam_algo_dbase[algoIndex]->defSensorReportRate != 0 )
         {
            // Other algorithms that want to support buffering have set nonzero
            // default sensor report rates in registry
            retVal = SNS_SMGR_BUFFERING_REQ_V01;
         }
      }
   }

   SNS_SAM_PRINTF2(LOW, "Using SMGR REQ %d for algo %d", retVal, algoSvcId);
   return retVal;
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_resp_msg
  =========================================================================*/
/*!
  @brief Prepares a response message for the specified request

  @param[i] reqMsgPtr: Pointer to request message for which
            response needs to be sent
  @param[i] respMsgPtr: Pointer to response message body,
            to be sent with header
  @param[i] respMsgBodyLen: Response message body length
            (excluding the header part)

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_resp_msg(
   const uint8_t *reqMsgPtr,
   void *respMsgPtr,
   uint16_t respMsgBodyLen)
{
   sns_smr_header_s reqMsgHdr, respMsgHdr;

   sns_smr_get_hdr(&reqMsgHdr, reqMsgPtr);
   if (reqMsgHdr.msg_type == SNS_SMR_MSG_TYPE_REQ)
   {
      SNS_OS_MEMZERO(&respMsgHdr, sizeof(sns_smr_header_s));
      respMsgHdr.dst_module = reqMsgHdr.src_module;
      respMsgHdr.src_module = reqMsgHdr.dst_module;
      respMsgHdr.svc_num = reqMsgHdr.svc_num;
      respMsgHdr.msg_type = SNS_SMR_MSG_TYPE_RESP;
      respMsgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
      respMsgHdr.body_len = respMsgBodyLen;

      respMsgHdr.txn_id = reqMsgHdr.txn_id;
      respMsgHdr.ext_clnt_id = reqMsgHdr.ext_clnt_id;

      //request and response messages are assumed to have same message ids
      respMsgHdr.msg_id = reqMsgHdr.msg_id;

      sns_smr_set_hdr(&respMsgHdr, respMsgPtr);

      SNS_SAM_DEBUG3(LOW, DBG_SAM_SEND_RSP_MSG,
                    reqMsgHdr.msg_id, reqMsgHdr.src_module, reqMsgHdr.svc_num);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_report_client_error
  =========================================================================*/
/*!
  @brief Report error message to client with error code if client request
  procesing fails.

  @param[i] clientReqMsgPtr: Pointer to client request message
            errCode: Error code
  @param[o] clientRespMsgPtr: Pointer to the response message created.

  @return None
*/
/*=======================================================================*/
void sns_sam_report_client_error(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   sns_err_code_e errCode)
{
   sns_smr_header_s msgHdr;
   uint8_t algoSvcId;

   sns_smr_get_hdr(&msgHdr, clientReqMsgPtr);
   if(msgHdr.msg_type != SNS_SMR_MSG_TYPE_REQ)
   {
      return;
   }

   algoSvcId = msgHdr.svc_num;

   switch (msgHdr.msg_id)
   {
   case SNS_SAM_ALGO_ENABLE_REQ:
      sns_sam_prep_algo_enable_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_DISABLE_REQ:
      sns_sam_prep_algo_disable_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_GET_REPORT_REQ:
      sns_sam_prep_algo_report_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_UPDATE_REQ:
      sns_sam_prep_algo_update_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_BATCH_REQ:
      sns_sam_prep_algo_batch_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_UPDATE_BATCH_PERIOD_REQ:
      sns_sam_prep_algo_update_batch_period_err(clientReqMsgPtr, clientRespMsgPtr, algoSvcId, errCode);
      break;

   case SNS_SAM_ALGO_GET_ATTRIB_REQ:
      {
         sns_sam_get_algo_attrib_resp_msg_v01 *attribRespMsgPtr =
            sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_get_algo_attrib_resp_msg_v01));
         SNS_ASSERT(attribRespMsgPtr != NULL);

         attribRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
         attribRespMsgPtr->resp.sns_err_t = errCode;

         sns_sam_prep_resp_msg(clientReqMsgPtr, attribRespMsgPtr,
             sizeof(sns_sam_get_algo_attrib_resp_msg_v01));
         *clientRespMsgPtr = attribRespMsgPtr;
      }
      break;

   case SNS_SAM_ALGO_CANCEL_REQ:
      {
         sns_common_cancel_resp_msg_v01 *cancelRespMsgPtr =
            sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_common_cancel_resp_msg_v01));
         SNS_ASSERT(cancelRespMsgPtr != NULL);

         cancelRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
         cancelRespMsgPtr->resp.sns_err_t = errCode;
         sns_sam_prep_resp_msg(clientReqMsgPtr, cancelRespMsgPtr,
             sizeof(sns_common_cancel_resp_msg_v01));
         *clientRespMsgPtr = cancelRespMsgPtr;
      }
      break;

   case SNS_SAM_ALGO_VERSION_REQ:
      {
         sns_common_version_resp_msg_v01 *versionRespMsgPtr =
            sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_common_version_resp_msg_v01));
         SNS_ASSERT(versionRespMsgPtr != NULL);

         versionRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
         versionRespMsgPtr->resp.sns_err_t = errCode;

         sns_sam_get_algo_version_resp(algoSvcId, versionRespMsgPtr);

         sns_sam_prep_resp_msg(clientReqMsgPtr, versionRespMsgPtr,
             sizeof(sns_common_version_resp_msg_v01));
         *clientRespMsgPtr = versionRespMsgPtr;
      }
      break;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_add_item_to_buffer
  =========================================================================*/
/*!
  @brief Add a batch item to circular buffer

  @param[i] clientReqId: index to client request in the database
  @param[i] batchItemPtr: pointer to batch item

  @return None
*/
/*=======================================================================*/
static void sns_sam_add_item_to_buffer(
   uint8_t clientReqId,
   void** batchItemPtr)
{
   sns_sam_client_req_s* clientReqPtr = sns_sam_get_client_req_handle(clientReqId);
   sns_proc_type_e_v01 procType;
   void * overflowItemPtr;

   if( !clientReqPtr )
   {
      SNS_SAM_PRINTF1(ERROR, "Invalid client request id %d", clientReqId );
      return;
   }

   procType = clientReqPtr->notify_suspend.proc_type;
   SNS_SAM_PRINTF2(LOW,"SAM: %d items in circ buffer for client id %d",
                   sns_circ_buffer_get_count(clientReqPtr->batchInfo->reportBuffer),
                   clientReqPtr->mrClientId);

   // Add item to circular buffer
   overflowItemPtr = sns_circ_buffer_add_item( clientReqPtr->batchInfo->reportBuffer, *batchItemPtr );
   if( overflowItemPtr )
   {
      // In case of overflow, free memory allocated for oldest item
      SNS_OS_FREE( overflowItemPtr );
      SNS_SAM_PRINTF0(LOW,"SAM: circ buffer overflow");
   }

   if( sns_circ_buffer_is_full( clientReqPtr->batchInfo->reportBuffer ) )
   {
      uint32_t batchPeriod = 0;
      bool notifySMGR = false;
      if( !sns_sam_client_proc_dbase[procType].suspendState )
      {
         batchPeriod = clientReqPtr->batchInfo->activeBatchPeriod;
      }
      else if( clientReqPtr->batchInfo->wakeClient )
      {
         batchPeriod = clientReqPtr->batchInfo->batchPeriod;
         notifySMGR = true;
      }
      if( batchPeriod != 0 )
      {
         // send batch indication to client
         sns_sam_send_algo_batch_ind( clientReqPtr );
         if( clientReqPtr->batchInfo->numTimeoutsToBatch != 0 )
         {
            // Periodic reporting timer is reused for batching
            // Reset timeout count
            clientReqPtr->batchInfo->numTimeouts = 0;
            clientReqPtr->batchInfo->numTimeoutsToBatch =
               batchPeriod / clientReqPtr->period;
         }
         else
         {
            // Reset batching timer
            sns_sam_dereg_timer( clientReqId );
            sns_sam_reg_timer( clientReqId, batchPeriod );
         }
         if( notifySMGR )
         {
            // Notify SMGR that AP will be woken up
            sns_smgr_app_state_change(false);
         }
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_report
  =========================================================================*/
/*!
  @brief Process report to specified client with specified algorithm output

  @param[i] clientReqId: index to client request in the database
  @param[i] algoRptPtr: pointer to algorithm report
  @param[i] mrClntId: MR Client ID

  @return Sensors error code
*/
/*=======================================================================*/
static void sns_sam_process_algo_report(
   uint8_t                  clientReqId,
   const sns_sam_algo_rpt_s *algoRptPtr,
   sns_sam_mr_conn_hndl     mrClntId)
{
   sns_smr_header_s msgHdr;
   uint8_t serviceId;
   sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];
   void* clientIndMsgPtr = NULL;
   bool send_indications_on_change_only = true;
   sns_err_code_e err = SNS_SUCCESS;

   serviceId = sns_sam_algo_inst_dbase[clientReqPtr->algoInstId]->serviceId;

   //Do not report to client before receiving initial sensor data
   //the probability for timestamp to roll over (and happen to be 0 again)
   //is very low, and missing one report indication isn't fatal.
   if (algoRptPtr->timestamp == 0)
   {
     SNS_SAM_PRINTF0(HIGH, "sns_sam_process_algo_report: Do not report to client before receiving initial sensor data");
      return;
   }

   //get on change reporting requirement for algorithm service
   send_indications_on_change_only = sns_sam_on_change_report_requirement(serviceId);

   //skip report if output has not been updated since last report for non QMD and non PED algos
   if (send_indications_on_change_only)
   {
      if (algoRptPtr->timestamp == clientReqPtr->timestamp)
      {
         return;
      }
   }

   sns_profiling_log_qdss(SNS_SAM_ALGO_REPORT_ENTER, 2, serviceId, clientReqPtr->algoInstId );

   //generate indication message to specified client
   msgHdr.dst_module = clientReqPtr->reqModule;
   msgHdr.src_module = SNS_SAM_MODULE;

   msgHdr.svc_num = serviceId;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_IND;

   if (clientReqPtr->reportType == SNS_SAM_ASYNC_REPORT ||
       clientReqPtr->reportType == SNS_SAM_ONE_SHOT_REPORT)
   {
      msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   }
   else
   {
      msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   }

   clientReqPtr->reportId++;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = sns_sam_mr_get_client_id(clientReqPtr->mrClientId);

   msgHdr.msg_id = SNS_SAM_ALGO_REPORT_IND;

   if( clientReqPtr->batchInfo != NULL &&
       clientReqPtr->batchInfo->batchPeriod > 0 )
   {
      sns_sam_create_batch_item( clientReqPtr, algoRptPtr, &clientIndMsgPtr );
      sns_sam_add_item_to_buffer( clientReqId, &clientIndMsgPtr );
   }
   else
   {
      err = sns_sam_prep_algo_report_ind(clientReqPtr, &clientIndMsgPtr, algoRptPtr, &msgHdr);
      if( err != SNS_SUCCESS )
      {
         SNS_SAM_PRINTF2( ERROR, "SAM: Failed to generate ind for client id %d from svc id %d",
            clientReqPtr->mrClientId, serviceId );
      }
      else if( clientReqPtr->directReportReq )
      {
         // Client is internal. No need to send a message. Process report synchronously
         SNS_SAM_PRINTF2( LOW, "SAM: Sending internal report to client id %d from svc id %d",
             clientReqPtr->mrClientId, serviceId );
         sns_sam_process_sam_ind( clientIndMsgPtr );
         sns_smr_msg_free( clientIndMsgPtr );
      }
      else
      {
         err = sns_sam_mr_send_ind(clientIndMsgPtr,
                                   mrClntId,
                                   clientReqPtr->notify_suspend.send_ind_during_suspend);
         if( err == SNS_SUCCESS )
         {
            // Send all pending batch indications when sending any indication
            sns_sam_send_pending_batch_inds( clientReqPtr->notify_suspend.proc_type );
         }
      }
   }

   if( err == SNS_SUCCESS )
   {
      //update client report timestamp
      clientReqPtr->timestamp = algoRptPtr->timestamp;

      SNS_SAM_DEBUG3(LOW, DBG_SAM_RPT_IND_MSG,
                     sns_sam_mr_get_client_id(clientReqPtr->mrClientId),
                     serviceId, clientReqPtr->reportId-1);
   }
   //For legacy SAM, feed "1" to the processedCnt field since the event is mainly designed for new
   //SAM and legacy SAM has been effectively deprecated
   sns_profiling_log_qdss(SNS_SAM_ALGO_REPORT_EXIT, 3, serviceId, clientReqPtr->algoInstId, 1);
}

/*=========================================================================
  FUNCTION:  sns_sam_send_report_ind_on_wakeup
  =========================================================================*/
/*!
  @brief Send a report indication to specific processor immediately on wakeup

  @return True, if at least one report ind was sent; False, otherwise
*/
/*=======================================================================*/
static bool sns_sam_send_report_ind_on_wakeup(
   sns_proc_type_e_v01 procType )
{
   int i;
   bool sentInd = false;

   if( procType >= SNS_SAM_MAX_CLIENT_PROCESSORS )
   {
      // processor state not tracked
      return sentInd;
   }

   for( i = 0; i < sns_sam_client_proc_dbase[procType].clientCount; i++ )
   {
      uint8_t clientReqId = sns_sam_client_proc_dbase[procType].clientReqIds[i];
      sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];

      if( clientReqPtr != NULL &&
          clientReqPtr->notify_suspend.send_ind_on_wakeup == true &&
          clientReqPtr->algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
          clientReqPtr->batchInfo == NULL )
      {
         sns_sam_algo_inst_s * algoInstPtr = sns_sam_algo_inst_dbase[clientReqPtr->algoInstId];

         if( !algoInstPtr )
         {
            continue;
         }

         // ignore if output hasn't changed since last report
         if( algoInstPtr->outputData.timestamp == clientReqPtr->timestamp )
         {
            continue;
         }

         // send latest report indication to client (only if batching is off)
         sns_sam_process_algo_report( clientReqId,
                                      &(algoInstPtr->outputData),
                                      clientReqPtr->mrClientId );
         sentInd = true;
      }
   }

   return sentInd;
}

/*=========================================================================
  FUNCTION:  sns_sam_handle_client_proc_wakeup
  =========================================================================*/
/*!
  @brief Handle the notification that client processor is now awake

  @return None
*/
/*=======================================================================*/
static void sns_sam_handle_client_proc_wakeup(
   sns_proc_type_e_v01 procType )
{
   if( !sns_sam_send_report_ind_on_wakeup( procType ) )
   {
      // If report ind was sent, buffers would have been emptied already
      sns_sam_send_pending_batch_inds( procType );
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_send_pending_batch_inds
  =========================================================================*/
/*!
  @brief Send pending batch indications to specific processor

  @return None
*/
/*=======================================================================*/
void sns_sam_send_pending_batch_inds(
   sns_proc_type_e_v01 procType )
{
   int i;

   if( procType >= SNS_SAM_MAX_CLIENT_PROCESSORS )
   {
      // processor state not tracked
      return;
   }

   for( i = 0; i < sns_sam_client_proc_dbase[procType].clientCount; i++ )
   {
      // Send batch indications to all interested clients on this processor
      uint8_t clientReqId = sns_sam_client_proc_dbase[procType].clientReqIds[i];
      sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];

      if (clientReqPtr && clientReqPtr->batchInfo && clientReqPtr->batchInfo->reportBuffer)
      {
         int numItems = sns_circ_buffer_get_count( clientReqPtr->batchInfo->reportBuffer );
         if( clientReqPtr->batchInfo->activeBatchPeriod != 0 && numItems > 0 )
         {
            if( clientReqPtr->batchInfo->numTimeoutsToBatch != 0 )
            {
               // Periodic reporting timer is reused for batching
               // Reset timeout count
               clientReqPtr->batchInfo->numTimeouts = 0;
               if( clientReqPtr->period != 0 )
               {
                  clientReqPtr->batchInfo->numTimeoutsToBatch =
                     clientReqPtr->batchInfo->activeBatchPeriod / clientReqPtr->period;
               }
               else
               {
                  // Retain old numTimeoutsToBatch if new value cannot be computed
                  SNS_SAM_PRINTF0(ERROR, "SAM: Invalid report period");
               }
            }
            else
            {
               // Reset batching timer
               sns_sam_dereg_timer( clientReqId );
               sns_sam_reg_timer( clientReqId, clientReqPtr->batchInfo->activeBatchPeriod );
            }
            // send batch indication to client
            sns_sam_send_algo_batch_ind( clientReqPtr );
         }
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sam_ind
  =========================================================================*/
/*!
  @brief Processes the indication received from sensors algorithm manager

  @param[i] smgrIndPtr: Pointer to sensors manager indication message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_sam_ind(
   const void *samIndPtr)
{
   sns_smr_header_s msgHdr;
   uint8_t algoInstId, i;
   sns_err_code_e err = SNS_SUCCESS;
   sns_sam_algo_inst_s* algoInstPtr;

   sns_smr_get_hdr(&msgHdr, samIndPtr);
   algoInstId = msgHdr.ext_clnt_id;

   if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_dbase[algoInstId] == NULL)
   {
      return SNS_ERR_FAILED;
   }

   algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   if (SNS_SAM_ALGO_REPORT_IND == msgHdr.msg_id)
   {
      //backup the algo report
      void *algoRptPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD,
                                       algoInstPtr->outputData.memSize);
      SNS_ASSERT(algoRptPtr != NULL);
      SNS_OS_MEMCOPY(algoRptPtr,
                     algoInstPtr->outputData.memPtr,
                     algoInstPtr->outputData.memSize);

      err = sns_sam_process_sam_report_ind(samIndPtr,
                                           algoInstPtr,
                                           msgHdr.svc_num,
                                           algoInstId);
      if (err == SNS_SUCCESS)
      {
         //send synchronous indication
         for (i = 0; i < SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST; i++)
         {
            if (algoInstPtr->clientReqDbase[i] < SNS_SAM_MAX_CLIENT_REQS)
            {
               uint8_t clientReqId = algoInstPtr->clientReqDbase[i];
               sns_sam_client_req_s* clientReqPtr =
                  sns_sam_client_req_dbase[clientReqId];

               if (clientReqPtr != NULL)
               {
                  if ((clientReqPtr->reportType == SNS_SAM_SYNC_REPORT) ||
                      ((clientReqPtr->reportType == SNS_SAM_ASYNC_REPORT) &&
                      (SNS_OS_MEMCMP(algoRptPtr,
                                     algoInstPtr->outputData.memPtr,
                                     algoInstPtr->outputData.memSize))))
                  {
                     //process algorithm report indication to client
                     sns_sam_process_algo_report(clientReqId,
                                                 &(algoInstPtr->outputData),
                                                 clientReqPtr->mrClientId);
                  }
                  else if (clientReqPtr->reportType == SNS_SAM_ONE_SHOT_REPORT)
                  {
                     sns_sam_process_one_shot_algo_report(clientReqId,
                                                          &(algoInstPtr->outputData));
                  }
               }
            }
         }

         sns_sam_log_dep_algo_result(algoInstId,
                                     sns_sam_algo_inst_dbase[algoInstId]);
      }
      SNS_OS_FREE(algoRptPtr);
   }
   else if (SNS_SAM_ALGO_ERROR_IND == msgHdr.msg_id)
   {
      //process algo error indication, currently ignored
   }
   else
   {
      err = SNS_ERR_BAD_PARM;
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_error_ind
  =========================================================================*/
/*!
  @brief Send indication to the specified client with asynchronous error

  @param[i] clientReqId: index to client request in the database
  @param[i] error: error status to be notified to client
  @param[i] mrClntId: MR Client ID

  @return Sensors error code
*/
/*=======================================================================*/
static void sns_sam_send_error_ind(
   uint8_t              clientReqId,
   uint8_t              error,
   sns_sam_mr_conn_hndl mrClntId)
{
   sns_smr_header_s msgHdr;
   uint8_t serviceId;
   void *msgIndPtr = NULL;
   sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];

   serviceId = sns_sam_algo_inst_dbase[clientReqPtr->algoInstId]->serviceId;

   //generate indication message to specified client
   msgHdr.dst_module = clientReqPtr->reqModule;
   msgHdr.src_module = SNS_SAM_MODULE;

   msgHdr.svc_num = serviceId;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_IND;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;

   clientReqPtr->reportId++;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = sns_sam_mr_get_client_id(clientReqPtr->mrClientId);
   msgHdr.msg_id = SNS_SAM_ALGO_ERROR_IND;

   sns_sam_prep_algo_error_ind(clientReqPtr->algoInstId, error, &msgHdr, &msgIndPtr);

   sns_sam_mr_send_ind(msgIndPtr, mrClntId, true);

   SNS_SAM_DEBUG3(HIGH, DBG_SAM_RPT_ERRIND_MSG,
                  sns_sam_mr_get_client_id(clientReqPtr->mrClientId),
                  serviceId, clientReqPtr->reportId-1);
}

/*=========================================================================
  FUNCTION:  sns_sam_handle_duty_cycle_timeout
  =========================================================================*/
/*!
  @brief Sets duty cycle state associated with algorithm instance

  @param[i] clientReqId: index to client request in the database
  @param[i] algoInstId: index to algorithm instance in the database

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_handle_duty_cycle_timeout(
   uint32_t clientReqId,
   uint8_t algoInstId)
{
   sns_sam_algo_inst_s *algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   bool dutycycleStateChange = false;

   if (algoInstPtr == NULL)
   {
      return SNS_ERR_FAILED;
   }

   /* if dutycycleTimerSource is SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE,
   indicates that duty cycling is disabled and will not enter if condition.*/
   if (algoInstPtr->dutycycleTimerSource == (int32_t)clientReqId)
   {
      uint8_t dutycycleResetCount = (uint8_t)(100/algoInstPtr->dutycycleOnPercent);

      algoInstPtr->dutycycleTimeoutCount++;

      if ((algoInstPtr->dutycycleTimeoutCount % dutycycleResetCount)==1)
      {
         algoInstPtr->dutycycleStateOn = false;
         dutycycleStateChange = true;
      }
      else if ((algoInstPtr->dutycycleTimeoutCount % dutycycleResetCount)==0)
      {
         algoInstPtr->dutycycleStateOn = true;
         algoInstPtr->dutycycleTimeoutCount = 0;
         dutycycleStateChange = true;
      }
   }

   if (dutycycleStateChange)
   {
      uint8_t algoIndex = sns_sam_get_algo_index(algoInstPtr->serviceId);
      sns_sam_algo_s *algoPtr;

      if (algoIndex >= SNS_SAM_MAX_ALGOS)
      {
         return SNS_ERR_FAILED;
      }

      algoPtr = sns_sam_algo_dbase[algoIndex];

      // Inform algorithm about duty cycle state change
      if( algoPtr && algoPtr->algoApi.sns_sam_algo_handle_duty_cycle_state_change )
      {
         void * statePtr = algoInstPtr->stateData.memPtr;
         void * outputPtr = algoInstPtr->outputData.memPtr;
         uint32_t timestamp = sns_em_get_timestamp();
         algoPtr->algoApi.sns_sam_algo_handle_duty_cycle_state_change(
                                                 algoInstPtr->dutycycleStateOn,
                                                 statePtr, outputPtr, timestamp);
      }

      sns_sam_handle_duty_cycle_state_change(
         algoInstId,
         algoInstPtr);
   }
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_handle_report_timeout
  =========================================================================*/
/*!
  @brief Handle the timeout indicating periodic report to client is due

  @return None
*/
/*=======================================================================*/
static void sns_sam_handle_report_timeout(void)
{
   uint8_t clientReqId, clientReqCnt;
   sns_sam_algo_rpt_s *algoRptPtr = NULL;

   //go through the client request database for periodic requests
   //check which responses are due
   for (clientReqId = 0, clientReqCnt = 0;
        clientReqCnt < sns_sam_client_req_count &&
        clientReqId < SNS_SAM_MAX_CLIENT_REQS;
        clientReqId++)
   {
      sns_sam_client_req_s* clientReqPtr =
         sns_sam_client_req_dbase[clientReqId];

      if (clientReqPtr != NULL)
      {
         if (clientReqPtr->timeout == true)
         {
            clientReqPtr->timeout = false;
            if (clientReqPtr->reportType == SNS_SAM_PERIODIC_REPORT ||
                clientReqPtr->reportType == SNS_SAM_ONE_SHOT_REPORT)
            {
               uint8_t algoInstId = clientReqPtr->algoInstId;
               sns_sam_algo_inst_s *algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];

               algoRptPtr = sns_sam_get_algo_report(algoInstId);

               if( algoRptPtr && algoInstPtr )
               {
                  //process algorithm report indication to client
                  sns_sam_update_algo_report_ts(algoInstPtr,
                                                clientReqPtr->mrClientId);
                  sns_sam_process_algo_report(clientReqId, algoRptPtr,
                                              clientReqPtr->mrClientId);
               }

               SNS_SAM_PRINTF3(LOW,
                   "Handled report timeout for client %d, period %d at time %d",
                   sns_sam_mr_get_client_id( clientReqPtr->mrClientId ),
                   clientReqPtr->period, sns_em_get_timestamp() );

               //if periodic reporting
               if (clientReqPtr->reportType == SNS_SAM_PERIODIC_REPORT)
               {
                  sns_sam_handle_duty_cycle_timeout(clientReqId,
                                                    algoInstId);
               }
            }
            if( clientReqPtr->batchInfo != NULL &&
                clientReqPtr->batchInfo->batchPeriod != 0 )
            {
               sns_proc_type_e_v01 procType = clientReqPtr->notify_suspend.proc_type;
               uint32_t batchPeriod = 0;
               bool sendInd = false;
               bool notifySMGR = false;

               if( !sns_sam_client_proc_dbase[procType].suspendState )
               {
                  batchPeriod = clientReqPtr->batchInfo->activeBatchPeriod;
               }
               else if( clientReqPtr->batchInfo->wakeClient )
               {
                  batchPeriod = clientReqPtr->batchInfo->batchPeriod;
                  notifySMGR = true;
               }
               if( batchPeriod != 0 &&
                   clientReqPtr->batchInfo->numTimeoutsToBatch != 0 )
               {
                  // Periodic reporting timer is reused for batching
                  int numTimeoutsToBatch = batchPeriod / clientReqPtr->period;
                  if( clientReqPtr->batchInfo->numTimeoutsToBatch != numTimeoutsToBatch )
                  {
                     // Reset batch period tracking if AP state has changed
                     clientReqPtr->batchInfo->numTimeoutsToBatch = numTimeoutsToBatch;
                     clientReqPtr->batchInfo->numTimeouts = 0;
                  }
                  else
                  {
                     // Send batch indication(s) if batch ratio is satisfied
                     clientReqPtr->batchInfo->numTimeouts++;
                     // Reset timeout count when expected timeouts occur
                     clientReqPtr->batchInfo->numTimeouts %= clientReqPtr->batchInfo->numTimeoutsToBatch;
                     sendInd = (clientReqPtr->batchInfo->numTimeouts == 0);
                  }
               }
               else if( batchPeriod != 0 &&
                        clientReqPtr->batchInfo->numTimeoutsToBatch == 0 )
               {
                  // Reset batching timer
                  sns_sam_dereg_timer( clientReqId );
                  sns_sam_reg_timer( clientReqId, batchPeriod );
                  sendInd = true;
               }
               if( sendInd )
               {
                  // send batch indication to client
                  sns_sam_send_algo_batch_ind( clientReqPtr );
                  if( notifySMGR )
                  {
                     // Notify SMGR that AP will be woken up
                     sns_smgr_app_state_change(false);
                  }
               }
            }
         }
         clientReqCnt++;
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_find_client_req
=========================================================================*/
/*!
  @brief Find the client request

  @param[i] msgHdrPtr: Pointer to client request message header
  @param[i] mrClntId: MR Client ID

  @return client request id if found, SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
uint8_t sns_sam_find_client_req(
   const sns_smr_header_s *msgHdrPtr,
   sns_sam_mr_conn_hndl   mrClntId)
{
   uint8_t clientReqId, clientReqCnt;

   for (clientReqId = 0, clientReqCnt = 0;
        clientReqCnt < sns_sam_client_req_count &&
        clientReqId < SNS_SAM_MAX_CLIENT_REQS;
        clientReqId++)
   {
      sns_sam_client_req_s* clientReqPtr =
         sns_sam_client_req_dbase[clientReqId];
      if (clientReqPtr != NULL)
      {
         if (sns_sam_mr_confirm_client_req(clientReqPtr, msgHdrPtr, mrClntId))
         {
            if (clientReqPtr->algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
                sns_sam_algo_inst_dbase[clientReqPtr->algoInstId] != NULL &&
                sns_sam_algo_inst_dbase[clientReqPtr->algoInstId]->serviceId ==
                msgHdrPtr->svc_num)
            {
               return clientReqId;
            }
         }

         clientReqCnt++;
      }
   }

   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_add_client_req
  =========================================================================*/
/*!
  @brief Adds the client request to the client request database

  @param[i] clientReqMsgPtr: pointer to the client request message
  @param[i] algoInstId: index to the algorithm instance in the database
  @param[i] mrClntId: MR Client ID
  @param[i] directReportReq: indicates if reporting using messages can be
                             bypassed using a direct function call instead

  @return client request id if successful, SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
static uint8_t sns_sam_add_client_req(
   const void           *clientReqMsgPtr,
   uint8_t              algoInstId,
   sns_sam_mr_conn_hndl mrClntId,
   bool                 directReportReq)
{
   uint8_t clientReqId;
   uint32_t reportPeriod;
   sns_sam_report_e reportType;
   uint32_t proc_type;
   bool notify_suspend;

   sns_smr_header_s msgHdr;

   if (sns_sam_client_req_count >= SNS_SAM_MAX_CLIENT_REQS)
   {
      SNS_SAM_DEBUG0(ERROR, DBG_SAM_ADD_CLIENT_MAX_ERR);
      return SNS_SAM_INVALID_ID;
   }

   reportPeriod = sns_sam_get_algo_report_period(
      sns_sam_algo_inst_dbase[algoInstId]->serviceId,
      clientReqMsgPtr,
      sns_sam_algo_inst_dbase[algoInstId]->configData.memPtr);

   if (reportPeriod == SNS_SAM_INVALID_PERIOD)
   {
      return SNS_SAM_INVALID_ID;
   }

   if( directReportReq )
   {
      // Always report synchronously to internal clients for Fusion algorithms
      switch (sns_sam_algo_inst_dbase[algoInstId]->serviceId)
      {
         case SNS_SAM_FILTERED_MAG_SVC_ID_V01:
         case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01:
         case SNS_SAM_QUATERNION_SVC_ID_V01:
         case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01:
         case SNS_SAM_ORIENTATION_SVC_ID_V01:
         case SNS_SAM_GAME_ROTATION_VECTOR_SVC_ID_V01:
            reportType = SNS_SAM_SYNC_REPORT;
            break;
         default:
            if( reportPeriod == 0 )
            {
               reportType = SNS_SAM_ASYNC_REPORT;
            }
            else
            {
               reportType = SNS_SAM_PERIODIC_REPORT;
            }
            break;
      }
   }
   else if (reportPeriod == 0)
   {
      /* reportPeriod = 0 indicates synchronous report at sampling rate for sensor fusion algorithms
         Add EIS algorithm (Gyroint): treat reportPeriod of 0 as sync reporting
         reportPeriod = 0 indicates asynchronous report for all other algorithms
       */
      switch (sns_sam_algo_inst_dbase[algoInstId]->serviceId)
      {
         case SNS_SAM_FILTERED_MAG_SVC_ID_V01:
         case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01:
         case SNS_SAM_QUATERNION_SVC_ID_V01:
         case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01:
         case SNS_SAM_ORIENTATION_SVC_ID_V01:
         case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
         case SNS_SAM_GYROINT_SVC_ID_V01:
         case SNS_SAM_PAM_SVC_ID_V01:
         case SNS_SAM_CMC_SVC_ID_V01:
         case SNS_SAM_GAME_ROTATION_VECTOR_SVC_ID_V01:
            reportType = SNS_SAM_SYNC_REPORT;
            break;
         case SNS_SAM_DISTANCE_BOUND_SVC_ID_V01:
            reportType = SNS_SAM_ONE_SHOT_REPORT;
            break;
         default:
            reportType = SNS_SAM_ASYNC_REPORT;
            break;
      }
   }
   else
   {
      reportType = SNS_SAM_PERIODIC_REPORT;
   }

   sns_smr_get_hdr(&msgHdr, clientReqMsgPtr);

   /* get the information about notifying during suspend from the client
      request message */
   sns_sam_get_request_suspend_notif_info(
      sns_sam_algo_inst_dbase[algoInstId]->serviceId,
      clientReqMsgPtr,
      &proc_type,
      &notify_suspend);

   for (clientReqId = 0; clientReqId < SNS_SAM_MAX_CLIENT_REQS; clientReqId++)
   {
      if (sns_sam_client_req_dbase[clientReqId] == NULL)
      {
         sns_sam_client_req_s* clientReqPtr;

         sns_sam_client_req_dbase[clientReqId] =
            SNS_OS_MALLOC(SNS_SAM_DBG_MOD, sizeof(sns_sam_client_req_s));
         SNS_ASSERT(sns_sam_client_req_dbase[clientReqId] != NULL);
         clientReqPtr = sns_sam_client_req_dbase[clientReqId];

         //add client req
         clientReqPtr->algoInstId = algoInstId;
         clientReqPtr->reqModule = msgHdr.src_module;
         clientReqPtr->reportId = 0;

         clientReqPtr->period = reportPeriod;
         clientReqPtr->timeout = false;
         clientReqPtr->timer = NULL;
         clientReqPtr->timestamp = 0;

         clientReqPtr->mrClientId = mrClntId;
         clientReqPtr->reportType = reportType;

         SNS_SAM_PRINTF2(LOW, "Client request id %d enabled with report type %d",
                         clientReqId, reportType);

         // update client request data base
         clientReqPtr->dutycycleOnPercent =
            sns_sam_algo_inst_dbase[algoInstId]->dutycycleOnPercent;

         // duty-cycle is not currently required for async algorithms
         if (clientReqPtr->reportType == SNS_SAM_PERIODIC_REPORT)
         {
            sns_sam_reg_timer(clientReqId, reportPeriod);
         }

         if ((clientReqPtr->reportType != SNS_SAM_ASYNC_REPORT) &&
             (clientReqPtr->reportType != SNS_SAM_ONE_SHOT_REPORT))
         {
            sns_sam_update_power_vote(clientReqPtr, true);
         }

         // save the proc type and notify during suspend information in client db
         clientReqPtr->notify_suspend.proc_type = proc_type;
         clientReqPtr->notify_suspend.send_ind_during_suspend = notify_suspend;

         // check if report indication should be sent immediately on client wakeup (for event sensors only)
         clientReqPtr->notify_suspend.send_ind_on_wakeup = ((notify_suspend == false) &&
                                                            (clientReqPtr->reportType == SNS_SAM_ASYNC_REPORT));
         if( clientReqPtr->notify_suspend.proc_type == SNS_PROC_APPS_V01 &&
             clientReqPtr->notify_suspend.send_ind_on_wakeup == true )
         {
            // Add client request ID to processor monitor database
            int clientCount = sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount;
            sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientReqIds[clientCount] = clientReqId;
            sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount++;
         }

         clientReqPtr->directReportReq = directReportReq;

         // batching is off by default
         clientReqPtr->batchInfo = NULL;

         sns_sam_client_req_count++;

#if defined(SNS_PLAYBACK_SKIP_SMGR) || defined(SNS_QDSP_SIM)
         // reportPeriod is in millisec, convert to DSPS clock ticks
         if (reportPeriod != 0)
         {
            nextReportTime[clientReqId] = reportPeriod;
         }
#endif

         SNS_SAM_DEBUG3(LOW, DBG_SAM_ADD_CLIENT_INFO,
                        clientReqId, clientReqPtr->reqModule,
                        clientReqPtr->algoInstId);

         return clientReqId;
      }
   }

   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_delete_client_req
  =========================================================================*/
/*!
  @brief Deletes the client request from the client request database

  @param[i] clientReqId: index to the client request in the database

  @return None
*/
/*=======================================================================*/
static void sns_sam_delete_client_req(
   uint8_t clientReqId)
{
   sns_sam_client_req_s* clientReqPtr = sns_sam_client_req_dbase[clientReqId];
   int i;

   // Disable batching
   if( clientReqPtr->batchInfo != NULL &&
       clientReqPtr->batchInfo->batchPeriod != 0 )
   {
      sns_sam_process_batch_req( clientReqId, 0, 0, false );
   }

   if( clientReqPtr->notify_suspend.send_ind_on_wakeup )
   {
      if( sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount > 0 )
      {
         // Remove client req id from tracking list
         for( i = 0; i < sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount; i++ )
         {
            if( sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientReqIds[i] == clientReqId )
            {
               break;
            }
         }

         if( i < sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount )
         {
            int clientCount = --sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientCount;
            sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientReqIds[i] =
               sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].clientReqIds[clientCount];
         }
      }
   }

   if (clientReqPtr->reportType == SNS_SAM_PERIODIC_REPORT ||
       clientReqPtr->reportType == SNS_SAM_ONE_SHOT_REPORT)
   {
      sns_sam_dereg_timer(clientReqId);
   }

   if ((clientReqPtr->reportType != SNS_SAM_ASYNC_REPORT) &&
       (clientReqPtr->reportType != SNS_SAM_ONE_SHOT_REPORT))
   {
      sns_sam_update_power_vote(clientReqPtr, false);
   }

   SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_DELETE_CLIENT_INFO,
                  clientReqId, clientReqPtr->reqModule,
                  clientReqPtr->algoInstId);

   SNS_OS_FREE(sns_sam_client_req_dbase[clientReqId]);
   sns_sam_client_req_dbase[clientReqId] = NULL;

   sns_sam_client_req_count--;
}

/*=========================================================================
  FUNCTION:  sns_sam_merge_sensor_requests
  =========================================================================*/
/*!
  @brief Merges sensor requests from a given data request to a base data
         request. This function assumes that the base data request has
         sufficient space to merge in the contents of the new data request

  @param[i/o] dataReq: data request to merge to
  @param[i] newDataReq: new data request

  @return None
*/
/*=======================================================================*/
static bool sns_sam_merge_sensor_requests(
   sns_sam_data_req_s * dataReq,
   const sns_sam_data_req_s * newDataReq)
{
   int8_t i, j, k;
   uint8_t sensorId;
   bool isNewStartRequestRequired = false;

   /* Move over all the algorithm instance IDs from the new data request to
   the existing one */
   for(i = 0; i < newDataReq->algoInstCount; i++)
   {
      uint8_t algoInstId = newDataReq->algoInstDbase[i];
      for(j = 0; j < dataReq->algoInstCount; j++)
      {
         /* Avoid duplicate algorithm instance IDs*/
         if(algoInstId == dataReq->algoInstDbase[j])
         {
            break;
         }
      }

      /* algoInstId is not present in existing data request */
      if(j == dataReq->algoInstCount)
      {
         dataReq->algoInstDbase[dataReq->algoInstCount] = algoInstId;
         dataReq->algoInstCount++;
      }
   }

   /* Check for duplicates and add sensor requests */
   for (i = 0; i < newDataReq->sensorCount; i++)
   {
      uint8_t existingSensorIndex = 0;
      sensorId = newDataReq->sensorDbase[i].sensorId;

      /* Identify which entry in the sensorDbase in the original dataReq matches
      the current sensorId */
      for( j = 0; j < dataReq->sensorCount; j++ )
      {
         if(sensorId == dataReq->sensorDbase[j].sensorId)
         {
            break;
         }
      }

      existingSensorIndex = j;

      /* Sensor is not present in the existing data request. Move it over as is. */
      if(existingSensorIndex == dataReq->sensorCount)
      {
         dataReq->sensorDbase[existingSensorIndex] = newDataReq->sensorDbase[i];
         dataReq->sensorCount++;
         isNewStartRequestRequired = true;
         continue;
      }

      for( j = 0; j < newDataReq->sensorDbase[i].algoInstCount; j++ )
      {
         uint8_t algoInstId = newDataReq->sensorDbase[i].algoInstIds[j];

         /* Avoid duplicate algorithm instance IDs*/
         for( k = 0; k < dataReq->sensorDbase[existingSensorIndex].algoInstCount; k++ )
         {
            if( algoInstId == dataReq->sensorDbase[existingSensorIndex].algoInstIds[k] )
            {
               break;
            }
         }

         /* algoInstId is not present in existing sensor's database */
         if( k == dataReq->sensorDbase[existingSensorIndex].algoInstCount )
         {
            dataReq->sensorDbase[existingSensorIndex].algoInstIds[k] = algoInstId;
            dataReq->sensorDbase[existingSensorIndex].algoInstCount++;
         }
      }
   }

   /* Update the report rate for the data request */
   if( newDataReq->reportRate > dataReq->reportRate )
   {
      dataReq->reportRate = newDataReq->reportRate;
      isNewStartRequestRequired = true;
   }

   return isNewStartRequestRequired;
}

/*=========================================================================
  FUNCTION:  sns_sam_find_data_req
  =========================================================================*/
/*!
  @brief Searches the active sensor data request database for an instance
  with all or few of the desired sensors at the requested sample rates

  @param[i] algoInstId: algorithm instance id
  @param[i] newDataReq: new data request

  @return  Index to data request matching the specified configuration
  SNS_SAM_INVALID_ID if match is not found
*/
/*=======================================================================*/
static uint8_t sns_sam_find_data_req(
   uint8_t algoInstId,
   const sns_sam_data_req_s * newDataReq)
{
   uint8_t dataReqId, dataReqCnt;

   for (dataReqId = 0, dataReqCnt = 0;
        dataReqCnt < sns_sam_data_req_count &&
        dataReqId < SNS_SAM_MAX_DATA_REQS;
        dataReqId++)
   {
      if (sns_sam_data_req_dbase[dataReqId] != NULL)
      {
         sns_sam_data_req_s *dataReq = sns_sam_data_req_dbase[dataReqId];
         uint8_t i, j, foundSensorCount = 0, foundAlgoInstCount = 0;

         // check if new request can completely be contained in an existing request
         // or can completely contain an existing request
         for (i = 0; i < dataReq->sensorCount; i++)
         {
            for (j = 0; j < newDataReq->sensorCount; j++)
            {
               if (dataReq->sensorDbase[i].sensorId == newDataReq->sensorDbase[j].sensorId &&
                   dataReq->sensorDbase[i].dataType == newDataReq->sensorDbase[j].dataType &&
                   dataReq->sensorDbase[i].sampleRate == newDataReq->sensorDbase[j].sampleRate &&
                   dataReq->sensorDbase[i].sampleQual == newDataReq->sensorDbase[j].sampleQual)
               {
                  foundSensorCount++;
                  break;
               }
            }
         }

         // Find the number of duplicate algorithm instances already in the database
         for (i = 0; i < dataReq->algoInstCount; i++)
         {
            for (j = 0; j < newDataReq->algoInstCount; j++)
            {
               if (dataReq->algoInstDbase[i] == newDataReq->algoInstDbase[j])
               {
                  foundAlgoInstCount++;
                  break;
               }
            }
         }

         if( foundSensorCount == dataReq->sensorCount || 
             foundSensorCount == newDataReq->sensorCount )
         {
            if( (newDataReq->algoInstCount + dataReq->algoInstCount - foundAlgoInstCount <= 
                 SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ) && 
                (newDataReq->sensorCount + dataReq->sensorCount - foundSensorCount <= 
                 SNS_SAM_MAX_SENSORS_PER_DATA_REQ) )
            {
               bool issueFreshStartReq = false;
               issueFreshStartReq = sns_sam_merge_sensor_requests(dataReq, newDataReq);
               SNS_SAM_PRINTF3(LOW,"SAM: added algoInstId %d for algoSvcId %d to existing req %d",
                                  algoInstId, sns_sam_algo_inst_dbase[algoInstId]->serviceId, dataReqId );

               if(issueFreshStartReq)
               {
                  sns_sam_send_smgr_start_req(dataReqId,
                                              sns_sam_algo_inst_dbase[algoInstId]->serviceId);
               }

               return dataReqId;
            }
         }
      }

      dataReqCnt++;
   }

   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_find_data_req_id
  =========================================================================*/
/*!
  @brief Searches the active sensor data request database for an instance
  with the same algorithm instance ID.

  @param[i] algoInstId: algorithm instance ID
  @param[i] forQuery: True if the data request is for a query request

  @return  Index to data request matching the specified configuration
           SNS_SAM_INVALID_ID if match is not found
*/
/*=======================================================================*/
uint8_t sns_sam_find_data_req_id(
   uint8_t algoInstId,
   bool forQuery)
{
   uint8_t dataReqId, dataReqCnt, i;
   sns_sam_data_req_s* dataReq;

   for (dataReqId = 0, dataReqCnt = 0;
        dataReqCnt < sns_sam_data_req_count &&
        dataReqId < SNS_SAM_MAX_DATA_REQS;
        dataReqId++)
   {
      if (sns_sam_data_req_dbase[dataReqId] != NULL)
      {
         dataReq = sns_sam_data_req_dbase[dataReqId];
         for (i = 0; i < dataReq->algoInstCount; i++)
         {
            if( (dataReq->algoInstDbase[i] == algoInstId) &&
                ( !forQuery || (dataReq->reportRate == 0) ) )
            {
               return dataReqId;
            }
         }
         dataReqCnt++;
      }
   }

   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_smgr_start_req
  =========================================================================*/
/*!
  @brief Send a request to sensors manager for sensor data

  @param[i] dataReqId: Index of data request in database
  @param[i] algoSvcId: algorithm service ID

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_smgr_start_req(
   uint8_t dataReqId,
   uint8_t algoSvcId)
{
   sns_smr_header_s msgHdr;
   uint_fast16_t msgSize = 0;
   sns_err_code_e err;
   uint8_t i;
   void *msgPtr = NULL;

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_SMGR_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.txn_id = 0;  //SAM uses external client id 0 for requests to SMGR
   msgHdr.ext_clnt_id = 0;

   if(sns_sam_get_smgr_msg_req_type(algoSvcId) == SNS_SMGR_BUFFERING_REQ_V01)
   {
      msgSize = sizeof(sns_smgr_buffering_req_msg_v01);
      sns_smgr_buffering_req_msg_v01* reqMsgPtr =
         (sns_smgr_buffering_req_msg_v01 *) sns_smr_msg_alloc(SNS_SAM_DBG_MOD, msgSize);
      SNS_ASSERT(reqMsgPtr != NULL);

      msgHdr.msg_id = SNS_SMGR_BUFFERING_REQ_V01;
      msgHdr.body_len = msgSize;

      reqMsgPtr->ReportId = dataReqId;
      reqMsgPtr->ReportRate = sns_sam_data_req_dbase[dataReqId]->reportRate;
      reqMsgPtr->Action = SNS_SMGR_BUFFERING_ACTION_ADD_V01;
      reqMsgPtr->Item_len = sns_sam_data_req_dbase[dataReqId]->sensorCount;

      SNS_SAM_PRINTF3(MED, "Buffering req, algo %d,  %d sensors, rep_rate %d",
                            algoSvcId, reqMsgPtr->Item_len, reqMsgPtr->ReportRate);

      for(i = 0; i < reqMsgPtr->Item_len; i++)
      {
         reqMsgPtr->Item[i].SensorId =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sensorId;
         reqMsgPtr->Item[i].DataType =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].dataType;
         reqMsgPtr->Item[i].SamplingRate =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sampleRate;
         reqMsgPtr->Item[i].SampleQuality =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sampleQual;
         reqMsgPtr->Item[i].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;
         if (reqMsgPtr->Item[i].SensorId == SNS_SMGR_ID_ACCEL_V01)
         {
            reqMsgPtr->Item[i].Calibration = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
         }
         else
         {
            reqMsgPtr->Item[i].Calibration = SNS_SMGR_CAL_SEL_FULL_CAL_V01;
         }
         SNS_SAM_PRINTF3(MED, "sensors %d, sample_rate %d, calibration %d",
                               reqMsgPtr->Item[i].SensorId,
                               reqMsgPtr->Item[i].SamplingRate,
                               reqMsgPtr->Item[i].Calibration);
      }

      if (SNS_SAM_MODULE == SNS_MODULE_DSPS_SAM)
      {
         reqMsgPtr->notify_suspend_valid = true;
         reqMsgPtr->notify_suspend.proc_type = SNS_PROC_SSC_V01;
         reqMsgPtr->notify_suspend.send_indications_during_suspend = true;
      }
      else if(SNS_SAM_MODULE == SNS_MODULE_APPS_SAM)
      {
         reqMsgPtr->notify_suspend_valid = true;
         reqMsgPtr->notify_suspend.proc_type = SNS_PROC_APPS_V01;
         reqMsgPtr->notify_suspend.send_indications_during_suspend = false;
      }
      else
      {
        reqMsgPtr->notify_suspend_valid = false;
      }

      reqMsgPtr->SrcModule_valid = true;
      reqMsgPtr->SrcModule = SNS_SAM_MODULE;

      msgPtr = (void*) reqMsgPtr;
   }
   else
   {
      msgSize = sizeof(sns_smgr_periodic_report_req_msg_v01);
      sns_smgr_periodic_report_req_msg_v01* reqMsgPtr =
         (sns_smgr_periodic_report_req_msg_v01 *) sns_smr_msg_alloc(SNS_SAM_DBG_MOD, msgSize);
      SNS_ASSERT(reqMsgPtr != NULL);

      msgHdr.msg_id = SNS_SMGR_REPORT_REQ_V01;
      msgHdr.body_len = msgSize;

      reqMsgPtr->BufferFactor = 1;
      reqMsgPtr->ReportId = dataReqId;
      reqMsgPtr->Action = SNS_SMGR_REPORT_ACTION_ADD_V01;
      reqMsgPtr->ReportRate = sns_sam_data_req_dbase[dataReqId]->reportRate;
      reqMsgPtr->cal_sel_valid = true;
      reqMsgPtr->cal_sel_len = sns_sam_data_req_dbase[dataReqId]->sensorCount;
      reqMsgPtr->SrcModule_valid = true;
      reqMsgPtr->SrcModule = SNS_SAM_MODULE;
      reqMsgPtr->Item_len = sns_sam_data_req_dbase[dataReqId]->sensorCount;
      reqMsgPtr->SampleQuality_valid = true;
      reqMsgPtr->SampleQuality_len = sns_sam_data_req_dbase[dataReqId]->sensorCount;

      SNS_SAM_PRINTF3(MED, "Periodic report req, algo %d,  %d sensors, rep_rate %d",
                            algoSvcId, reqMsgPtr->Item_len, reqMsgPtr->ReportRate);

      for (i = 0; i < sns_sam_data_req_dbase[dataReqId]->sensorCount; i++)
      {
         reqMsgPtr->Item[i].SensorId =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sensorId;
         reqMsgPtr->Item[i].DataType =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].dataType;
         reqMsgPtr->SampleQuality[i] =
            sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sampleQual;

         reqMsgPtr->Item[i].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;

         // Use factory calibrated accel, till accel autocal stabilizes
         // Since factory calibrated accelerometer is acceptable for
         // existing features, this will allow accel-autocal to be tested
         // in isolation with minimal impact on existing features
         if (reqMsgPtr->Item[i].SensorId == SNS_SMGR_ID_ACCEL_V01)
         {
            reqMsgPtr->cal_sel[i] = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
         }
         else
         {
            reqMsgPtr->cal_sel[i] = SNS_SMGR_CAL_SEL_FULL_CAL_V01;
         }
         SNS_SAM_PRINTF3(MED, "sensors %d, calibration %d qual %d",
                               reqMsgPtr->Item[i].SensorId,
                               reqMsgPtr->cal_sel[i],
                               reqMsgPtr->SampleQuality[i]);
      }

      if (SNS_SAM_MODULE == SNS_MODULE_DSPS_SAM)
      {
         reqMsgPtr->notify_suspend_valid = true;
         reqMsgPtr->notify_suspend.proc_type = SNS_PROC_SSC_V01;
         reqMsgPtr->notify_suspend.send_indications_during_suspend = true;
      }
      else if(SNS_SAM_MODULE == SNS_MODULE_APPS_SAM)
      {
         reqMsgPtr->notify_suspend_valid = true;
         reqMsgPtr->notify_suspend.proc_type = SNS_PROC_APPS_V01;
         reqMsgPtr->notify_suspend.send_indications_during_suspend = false;
      }
      else
      {
        reqMsgPtr->notify_suspend_valid = false;
      }

      msgPtr = (void*) reqMsgPtr;
   }

   sns_smr_set_hdr(&msgHdr, msgPtr);
   err = sns_sam_mr_send(msgPtr, NULL);

   SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_REQ_SNSR_DATA_MSG, dataReqId,
                  sns_sam_data_req_dbase[dataReqId]->sensorDbase[0].sensorId,
                  sns_sam_data_req_dbase[dataReqId]->reportRate);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_start_sensor_data
  =========================================================================*/
/*!
  @brief Request sensor data according to the algorithm needs

  @param[i] algoInstId: algorithm instance id
  @param[i] dataReq: sensor data request

  @return  Index to data request matching the specified configuration
  SNS_SAM_INVALID_ID if match is not found
*/
/*=======================================================================*/
uint8_t sns_sam_start_sensor_data(
   uint8_t algoInstId,
   const sns_sam_data_req_s * dataReq)
{
   uint8_t i, dataReqId = SNS_SAM_INVALID_ID;

   //check if there is an identical existing request
   dataReqId = sns_sam_find_data_req(algoInstId,
                                     dataReq);

   //add request if none exists
   if (dataReqId >= SNS_SAM_MAX_DATA_REQS &&
       sns_sam_data_req_count < SNS_SAM_MAX_DATA_REQS)
   {
      for (dataReqId = 0; dataReqId < SNS_SAM_MAX_DATA_REQS; dataReqId++)
      {
         if (sns_sam_data_req_dbase[dataReqId] == NULL)
         {
            sns_sam_data_req_dbase[dataReqId] =
               SNS_OS_MALLOC(SNS_SAM_DBG_MOD, sizeof(sns_sam_data_req_s));
            SNS_ASSERT(sns_sam_data_req_dbase[dataReqId] != NULL);

            for (i = 0; i < SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ; i++)
            {
               sns_sam_data_req_dbase[dataReqId]->algoInstDbase[i] =
                  SNS_SAM_INVALID_ID;
            }
            sns_sam_data_req_dbase[dataReqId]->reportRate = dataReq->reportRate;
            for (i = 0; i < dataReq->sensorCount; i++)
            {
              sns_sam_data_req_dbase[dataReqId]->sensorDbase[i] = dataReq->sensorDbase[i];
            }
            sns_sam_data_req_dbase[dataReqId]->sensorCount = dataReq->sensorCount;
            for (i = 0; i < dataReq->algoInstCount; i++)
            {
               sns_sam_data_req_dbase[dataReqId]->algoInstDbase[i] = dataReq->algoInstDbase[i];
            }
            sns_sam_data_req_dbase[dataReqId]->algoInstCount = dataReq->algoInstCount;
            sns_sam_data_req_dbase[dataReqId]->registerMDInterrupt = dataReq->registerMDInterrupt;

            //send message to sensors manager requesting required sensor data
            sns_sam_send_smgr_start_req(dataReqId,
                                        sns_sam_algo_inst_dbase[algoInstId]->serviceId);

            sns_sam_data_req_count++;

            break;
         }
      }
   }

   return dataReqId;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_smgr_stop_req
  =========================================================================*/
/*!
  @brief Send a request to sensors manager to stop sensor data received by
  specified algorithm

  @param[i] dataReqId: Index of data request in database
  @param[i] algoSvcId: algorithm service ID

  @return None
*/
/*=======================================================================*/
static void sns_sam_send_smgr_stop_req(
   uint8_t dataReqId,
   uint8_t algoSvcId)
{
   sns_smr_header_s msgHdr;
   void *msgPtr = NULL;

   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = SNS_SMGR_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.txn_id = 0; //SAM uses external client id 0 for requests to SMGR
   msgHdr.ext_clnt_id = 0;

   if(sns_sam_get_smgr_msg_req_type(algoSvcId) == SNS_SMGR_BUFFERING_REQ_V01)
   {
      sns_smgr_buffering_req_msg_v01* reqMsgPtr =
         (sns_smgr_buffering_req_msg_v01 *) sns_smr_msg_alloc(SNS_SAM_DBG_MOD,
                 sizeof(sns_smgr_buffering_req_msg_v01));
      SNS_ASSERT(reqMsgPtr != NULL);

      msgHdr.msg_id = SNS_SMGR_BUFFERING_REQ_V01;
      msgHdr.body_len = sizeof(sns_smgr_buffering_req_msg_v01);

      reqMsgPtr->ReportId = dataReqId;
      reqMsgPtr->Action = SNS_SMGR_BUFFERING_ACTION_DELETE_V01;
      reqMsgPtr->Item_len = 0;
      reqMsgPtr->notify_suspend_valid = false;
      reqMsgPtr->SrcModule_valid = true;
      reqMsgPtr->SrcModule = SNS_SAM_MODULE;

      msgPtr = (void*) reqMsgPtr;
   }
   else
   {
      //send request to stop sensor data by sensor manager
      sns_smgr_periodic_report_req_msg_v01* reqMsgPtr =
         (sns_smgr_periodic_report_req_msg_v01 *) sns_smr_msg_alloc(SNS_SAM_DBG_MOD,
                 sizeof(sns_smgr_periodic_report_req_msg_v01));
      SNS_ASSERT(reqMsgPtr != NULL);

      msgHdr.msg_id = SNS_SMGR_REPORT_REQ_V01;
      msgHdr.body_len = sizeof(sns_smgr_periodic_report_req_msg_v01);

      reqMsgPtr->Item_len = 0;
      reqMsgPtr->BufferFactor = 1;
      reqMsgPtr->ReportId = dataReqId;
      reqMsgPtr->Action = SNS_SMGR_REPORT_ACTION_DELETE_V01;
      reqMsgPtr->SrcModule_valid = true;
      reqMsgPtr->SrcModule = SNS_SAM_MODULE;

      msgPtr = (void*) reqMsgPtr;
   }
   sns_smr_set_hdr(&msgHdr, msgPtr);
   sns_sam_mr_send(msgPtr, NULL);

   sns_sam_sensor_data_stop_ind(dataReqId);

   SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_STOP_SNSR_DATA_MSG, dataReqId,
                  sns_sam_data_req_dbase[dataReqId]->sensorDbase[0].sensorId,
                  sns_sam_data_req_dbase[dataReqId]->reportRate);
}

/*=========================================================================
  FUNCTION:  sns_sam_update_data_req
  =========================================================================*/
/*!
  @brief Update sensor data request upon deletion of algorithm instance

  @param[i] dataReqId: Index of data request in database
  @param[i] algoInstId: Index of algorithm instance being deleted

  @return None
*/
/*=======================================================================*/
static void sns_sam_update_data_req(
   uint8_t dataReqId,
   uint8_t algoInstId)
{
   if( sns_sam_data_req_dbase[dataReqId] != NULL )
   {
      sns_sam_data_req_s * dataReq = sns_sam_data_req_dbase[dataReqId];
      bool dataReqChanged = false;
      int8_t i, j;
      uint8_t instId;

      for( i = 0; i < dataReq->sensorCount; i++ )
      {
         for( j = 0; j < dataReq->sensorDbase[i].algoInstCount; j++ )
         {
            instId = dataReq->sensorDbase[i].algoInstIds[j];
            if( instId == algoInstId ||
                instId >= SNS_SAM_MAX_ALGO_INSTS ||
                sns_sam_algo_inst_dbase[instId] == NULL )
            {
               dataReq->sensorDbase[i].algoInstCount--;
               dataReq->sensorDbase[i].algoInstIds[j] = 
                 dataReq->sensorDbase[i].algoInstIds[dataReq->sensorDbase[i].algoInstCount];
               dataReq->sensorDbase[i].algoInstIds[dataReq->sensorDbase[i].algoInstCount] =
                 SNS_SAM_INVALID_ID;
               j--;
            }
         }

         /* Remove sensor if no algorithm is subscribed to it */
         if( dataReq->sensorDbase[i].algoInstCount == 0 )
         {
            dataReq->sensorCount--;
            dataReq->sensorDbase[i] =
               dataReq->sensorDbase[dataReq->sensorCount];
            dataReqChanged = true;
            i--;
         }
      }

      for( i = 0; i < dataReq->algoInstCount; i++ )
      {
         instId = dataReq->algoInstDbase[i];
         if( instId >= SNS_SAM_MAX_ALGO_INSTS ||
             sns_sam_algo_inst_dbase[instId] == NULL )
         {
            dataReq->algoInstCount--;
            dataReq->algoInstDbase[i] =
               dataReq->algoInstDbase[dataReq->algoInstCount];
            dataReq->algoInstDbase[dataReq->algoInstCount] =
               SNS_SAM_INVALID_ID;
            i--;
         }
      }

      if( dataReqChanged && dataReq->sensorCount > 0 )
      {
         // send new request to SMGR
         instId =  dataReq->algoInstDbase[0];
         sns_sam_send_smgr_start_req( dataReqId,
                                      sns_sam_algo_inst_dbase[instId]->serviceId);
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_stop_sensor_data
  =========================================================================*/
/*!
  @brief Stop sensor data received for specified algorithm instance

  @param[i] algoInstId: Index of algorithm instance in database

  @return None
*/
/*=======================================================================*/
void sns_sam_stop_sensor_data(
   uint8_t algoInstId)
{
   uint8_t dataReqId, dataReqCnt, i;

   for (dataReqId = 0, dataReqCnt = 0;
        dataReqCnt < sns_sam_data_req_count &&
        dataReqId < SNS_SAM_MAX_DATA_REQS;
        dataReqId++)
   {
      if (sns_sam_data_req_dbase[dataReqId] != NULL)
      {
         sns_sam_data_req_s *dataReq = sns_sam_data_req_dbase[dataReqId];
         for (i = 0; i < dataReq->algoInstCount; i++)
         {
            if(dataReq->algoInstDbase[i] == algoInstId)
            {
               dataReq->algoInstCount--;
               dataReq->algoInstDbase[i] =
                  dataReq->algoInstDbase[dataReq->algoInstCount];
               dataReq->algoInstDbase[dataReq->algoInstCount] =
                  SNS_SAM_INVALID_ID;

               if( sns_sam_algo_inst_dbase[algoInstId] != NULL )
               {
                  // Update data request if sensor requirements
                  // are changing
                  sns_sam_update_data_req( dataReqId, algoInstId );
               }

               if(dataReq->algoInstCount == 0)
               {
                  sns_sam_send_smgr_stop_req(dataReqId,
                                             sns_sam_algo_inst_dbase[algoInstId]->serviceId);
                  SNS_OS_FREE(sns_sam_data_req_dbase[dataReqId]);
                  sns_sam_data_req_dbase[dataReqId] = NULL;

                  sns_sam_data_req_count--;
                  break;
               }
            }
         }
         dataReqCnt++;
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_index
  =========================================================================*/
/*!
  @brief Get the index into the algorithm database for the specified algorithm

  @param[i] algoSvcId: algorithm service id

  @return algorithm index for the specified algorithm if found,
          SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
uint8_t sns_sam_get_algo_index(
   uint8_t algoSvcId)
{
   uint8_t i;

   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->serviceId == algoSvcId)
      {
         return i;
      }
   }
   SNS_SAM_DEBUG1(ERROR, DBG_SAM_GET_ALGO_INDX_ERR, algoSvcId);

   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified algorithm in the algorithm database

  @param[i] algoSvcId: algorithm service id

  @return handle to the specified algorithm if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_algo_s* sns_sam_get_algo_handle(
   uint8_t algoSvcId)
{
   uint8_t i;

   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->serviceId == algoSvcId)
      {
         return sns_sam_algo_dbase[i];
      }
   }
   SNS_SAM_DEBUG1(ERROR, DBG_SAM_GET_ALGO_INDX_ERR, algoSvcId);

   return NULL;
}

/*=========================================================================
  FUNCTION:  sns_sam_find_algo_inst
  =========================================================================*/
/*!
  @brief Searches the active algorithm database for an instance
  of an algorithm with specified configuration

  @param[i] algoSvcId: algorithm service id
  @param[i] algoCfgPtr: pointer to configuration of specified algorithm

  @return  Index to algorithm instance matching the specified configuration
  if successful, SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
static uint8_t sns_sam_find_algo_inst(
   uint8_t algoSvcId,
   void *algoCfgPtr)
{
   uint8_t algoInstId, algoInstCnt;

   for (algoInstId = 0, algoInstCnt = 0;
        algoInstCnt < sns_sam_algo_inst_count &&
        algoInstId < SNS_SAM_MAX_ALGO_INSTS;
        algoInstId++)
   {
      sns_sam_algo_inst_s *algo_instance = sns_sam_algo_inst_dbase[algoInstId];
      if (algo_instance != NULL)
      {
         if ((algo_instance->serviceId == algoSvcId) &&
            (algoCfgPtr == NULL ||
             !SNS_OS_MEMCMP(algoCfgPtr,
                            algo_instance->configData.memPtr,
                            algo_instance->configData.memSize)) &&
            (algo_instance->clientReqCount < SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST))
         {
            return algoInstId;
         }
         algoInstCnt++;
      }
   }
   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_delete_algo_inst
  =========================================================================*/
/*!
  @brief Deletes the specified algorithm instance

  @param[i] algoInstId: index to algorithm instance in database

  @return None
*/
/*=======================================================================*/
static void sns_sam_delete_algo_inst(
   uint8_t algoInstId)
{
   sns_sam_algo_inst_s* algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];

   sns_sam_mr_delete_algo_inst( algoInstPtr->mrAlgoConnHndl );
   algoInstPtr->mrAlgoConnHndl = NULL;

   //free memory reserved for this algorithm instance
   SNS_OS_FREE(algoInstPtr->configData.memPtr);
   algoInstPtr->configData.memPtr = NULL;
   algoInstPtr->configData.memSize = 0;

   SNS_OS_FREE(algoInstPtr->stateData.memPtr);
   algoInstPtr->stateData.memPtr = NULL;
   algoInstPtr->stateData.memSize = 0;

   SNS_OS_FREE(algoInstPtr->inputData.memPtr);
   algoInstPtr->inputData.memPtr = NULL;
   algoInstPtr->inputData.memSize = 0;

   SNS_OS_FREE(algoInstPtr->outputData.memPtr);
   algoInstPtr->outputData.memPtr = NULL;
   algoInstPtr->outputData.memSize = 0;
   algoInstPtr->outputData.timestamp = 0;

   SNS_OS_FREE(sns_sam_algo_inst_dbase[algoInstId]);
   sns_sam_algo_inst_dbase[algoInstId] = NULL;

   sns_sam_algo_inst_count--;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_inst
  =========================================================================*/
/*!
  @brief
  If an instance of the specified algorithm doesnt exist,
  creates an instance and initializes the reference count.
  If an instance with identical configuration exists,
  updates the reference count.

  @param[i] algoIndex: index to algorithm in the algorithm database
  @param[i] clientReqMsgPtr: pointer to client request message

  @return index of the algorithm instance in database if successful,
          SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
static uint8_t sns_sam_get_algo_inst(
   uint8_t algoIndex,
   const void *clientReqMsgPtr)
{
   uint8_t algoInstId = SNS_SAM_INVALID_ID, instId;
   uint8_t algoSvcId = sns_sam_algo_dbase[algoIndex]->serviceId;
   void *algoDefCfgPtr = sns_sam_algo_dbase[algoIndex]->defConfigData.memPtr;
   void *algoCfgPtr = NULL;
   sns_sam_algo_inst_s* algoInstPtr = NULL;

   uint32_t memSize = sns_sam_algo_dbase[algoIndex]->defConfigData.memSize;
   if (memSize > 0)
   {
      algoCfgPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, memSize);
      SNS_ASSERT(algoCfgPtr != NULL);
      SNS_OS_MEMCOPY(algoCfgPtr, algoDefCfgPtr, memSize);

      //update algorithm configuration if specified by client
      if (NULL != clientReqMsgPtr)
      {
         sns_sam_update_algo_config(algoSvcId, clientReqMsgPtr, algoCfgPtr);
      }
   }

   if (sns_sam_algo_dbase[algoIndex]->disableAlgoInstReuse == FALSE)
   {
      //find algorithm instance with same configuration
      algoInstId = sns_sam_find_algo_inst(algoSvcId, algoCfgPtr);
   }

   //check if new algorithm instance is needed and can be created
   if (algoInstId < SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_count >= SNS_SAM_MAX_ALGO_INSTS)
   {
      SNS_SAM_PRINTF2(LOW,
                   "AlgoInst matching config already exists. Reusing it. AlgoSvcId=%d, AlgoInstId=%d",
                   algoSvcId, algoInstId);

      if (algoCfgPtr != NULL)
      {
         SNS_OS_FREE(algoCfgPtr);
      }
      return algoInstId;
   }

   SNS_SAM_PRINTF1(LOW,
                   "AlgoInst matching config does not exist. Creating new Algo Instance. AlgoSvcId=%d",
                   algoSvcId);

   //create algorithm instance
   for (instId = 0; instId < SNS_SAM_MAX_ALGO_INSTS; instId++)
   {
      if (sns_sam_algo_inst_dbase[instId] == NULL)
      {
         uint8_t i;
         void *statePtr = NULL;
         memSize = sizeof(sns_sam_algo_inst_s);

         //create algorithm instance
         sns_sam_algo_inst_dbase[instId] = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, memSize);
         SNS_ASSERT(sns_sam_algo_inst_dbase[instId] != NULL);
         algoInstPtr = sns_sam_algo_inst_dbase[instId];

         //initialize the algorithm instance
         algoInstPtr->clientReqCount = 0;
         // Initialize motion state to true to indicate that sensor data will be
         // requested when the algorithm is enabled
         algoInstPtr->motion_state = SNS_SAM_MOTION_MOVE_V01;
         for (i = 0; i < SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST; i++)
         {
            algoInstPtr->clientReqDbase[i] = SNS_SAM_INVALID_ID;
         }

         algoInstPtr->stateData.memPtr = NULL;
         algoInstPtr->inputData.memPtr = NULL;
         algoInstPtr->outputData.memPtr = NULL;

         algoInstPtr->configData.memPtr = algoCfgPtr;
         algoInstPtr->configData.memSize =
            sns_sam_algo_dbase[algoIndex]->defConfigData.memSize;

         memSize =
            sns_sam_algo_dbase[algoIndex]->algoApi.
            sns_sam_algo_mem_req(algoCfgPtr);
         if (memSize > 0)
         {
            algoInstPtr->stateData.memPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, memSize);
            SNS_ASSERT(algoInstPtr->stateData.memPtr != NULL);
            SNS_OS_MEMZERO(algoInstPtr->stateData.memPtr, memSize);
         }
         algoInstPtr->stateData.memSize = memSize;

         memSize = sns_sam_algo_dbase[algoIndex]->defInputDataSize;
         if (memSize > 0)
         {
            algoInstPtr->inputData.memPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, memSize);
            SNS_ASSERT(algoInstPtr->inputData.memPtr != NULL);
            SNS_OS_MEMZERO(algoInstPtr->inputData.memPtr, memSize);
         }
         algoInstPtr->inputData.memSize = memSize;

         memSize = sns_sam_algo_dbase[algoIndex]->defOutputDataSize;
         if (memSize > 0)
         {
            algoInstPtr->outputData.memPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, memSize);
            SNS_ASSERT(algoInstPtr->outputData.memPtr != NULL);
            SNS_OS_MEMZERO(algoInstPtr->outputData.memPtr, memSize);
         }
         algoInstPtr->outputData.memSize = memSize;
         algoInstPtr->outputData.timestamp = 0;

         // use default duty cycle config in sns_sam_algo_dbase
         algoInstPtr->dutycycleOnPercent =
            sns_sam_process_client_duty_cycle_req(algoSvcId, clientReqMsgPtr);
         algoInstPtr->dutycycleOnDuration =
            sns_sam_get_algo_report_period(algoSvcId,clientReqMsgPtr,algoCfgPtr);
         algoInstPtr->dutycycleStateOn = true;
         algoInstPtr->dutycycleTimeoutCount = 0;
         algoInstPtr->dutycycleTimerSource = (int16_t)SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE;

         statePtr = sns_sam_algo_dbase[algoIndex]->algoApi.
            sns_sam_algo_reset(algoInstPtr->configData.memPtr,
                               algoInstPtr->stateData.memPtr);
         if (statePtr == NULL)
         {
            SNS_SAM_DEBUG0(ERROR, DBG_SAM_ENABLE_ALGO_STATE_NULL);
         }

         algoInstPtr->serviceId = algoSvcId;

         algoInstId = instId;

         sns_sam_algo_inst_count++;

         if( SNS_SUCCESS != sns_sam_mr_init_algo_inst( &algoInstPtr->mrAlgoConnHndl, algoSvcId ) )
         {
            SNS_ASSERT(algoInstPtr->mrAlgoConnHndl != NULL);
         }

         //Log algorithm configuration
         sns_sam_log_algo_config(algoInstId, algoInstPtr, algoIndex);

         SNS_SAM_DEBUG3(LOW, DBG_SAM_ALGO_MEM_INFO,
                        algoInstPtr->serviceId,
                        sizeof(sns_sam_algo_inst_s),
                        algoInstPtr->configData.memSize);
         SNS_SAM_DEBUG3(LOW, DBG_SAM_ALGO_STATE_MEM_INFO,
                        algoInstPtr->stateData.memSize,
                        algoInstPtr->inputData.memSize,
                        algoInstPtr->outputData.memSize);

         break;
      }
   }

   return algoInstId;
}

/*=========================================================================
  FUNCTION:  sns_sam_update_duty_cycle_config_client_removal
  =========================================================================*/
/*!
  @brief
  updates the duty cycle config setting when a client is removed

  @param[i] deletedClientReqId: index of removed client request
  @param[i] algoInstId: index of algorithm instance
  @param[i] algoInstPtr: pointer to algo instance

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_update_duty_cycle_config_client_removal(
   uint8_t deletedClientReqId,
   uint8_t algoInstId,
   sns_sam_algo_inst_s *algoInstPtr)
{
   UNREFERENCED_PARAMETER(algoInstId);
   if ( (algoInstPtr->dutycycleTimerSource != SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE) &&
       (algoInstPtr->dutycycleTimerSource == deletedClientReqId) )
   {
      // algorithm instance uses dutycyling and the deleted client request
      // is the currently employed duty cycle timer source
      uint8_t j=0,k=0,clientReqId;

      uint8_t dutycycleOnDurationMin, dutycycleOnPercentMax;
      uint8_t clientIdList[SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST];
      SNS_OS_MEMZERO(clientIdList, sizeof(clientIdList));

      // find max requested duty cycle among all clients for the algo instance
      dutycycleOnPercentMax =
         sns_sam_client_req_dbase[algoInstPtr->clientReqDbase[0]]->dutycycleOnPercent;
      for (j=0; j<algoInstPtr->clientReqCount; j++)
      {
         clientReqId = algoInstPtr->clientReqDbase[j];
         if (sns_sam_client_req_dbase[clientReqId]->dutycycleOnPercent >
             dutycycleOnPercentMax)
         {
            dutycycleOnPercentMax =
               sns_sam_client_req_dbase[clientReqId]->dutycycleOnPercent;
         }
      }

      // find out if there are multiple clients requesting the same max duty cycle
      // on percentage
      k = 0;
      for (j=0; j<algoInstPtr->clientReqCount; j++)
      {
         clientReqId = algoInstPtr->clientReqDbase[j];
         if (sns_sam_client_req_dbase[clientReqId]->dutycycleOnPercent ==
             dutycycleOnPercentMax)
         {
            clientIdList[k]=clientReqId;
            k = k+1;
         }
      }

      // find the minimum requested On Duration among all the clients requsting the
      // max on percentage
      dutycycleOnDurationMin = sns_sam_client_req_dbase[clientIdList[0]]->period;
      clientReqId = clientIdList[0];
      for (j=1; j<k; j++)
      {
         if (sns_sam_client_req_dbase[clientIdList[j]]->period < dutycycleOnDurationMin)
         {
            dutycycleOnDurationMin = sns_sam_client_req_dbase[clientIdList[j]]->period;
            clientReqId = clientIdList[j];
         }
      }

      // reset duty cycle configuration for algo instance
      algoInstPtr->dutycycleOnDuration = dutycycleOnDurationMin;
      algoInstPtr->dutycycleOnPercent = dutycycleOnPercentMax;
      algoInstPtr->dutycycleTimerSource = clientReqId;
   }
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_update_duty_cycle_config_client_add
  =========================================================================*/
/*!
  @brief
  updates the duty cycle config setting when a client is added

  @param[i] algoInstId: index of algo instance data base
  @param[i] algoIndex: index of algorithm in database
  @param[i] clientReqId: index to client request database

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_update_duty_cycle_config_client_add(
   uint8_t algoInstId,
   uint8_t algoIndex,
   uint8_t clientReqId)
{
   bool dutycycleUpdateConfig = false;
   uint8_t dutycycleOnPercent =
      sns_sam_client_req_dbase[clientReqId]->dutycycleOnPercent;
   uint32_t dutycycleOnDuration =
      sns_sam_client_req_dbase[clientReqId]->period;
   sns_sam_algo_inst_s *algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];

   UNREFERENCED_PARAMETER(algoIndex);

   if(algoInstPtr->clientReqCount == 1)
   {
      // first client request for algo instance
      dutycycleUpdateConfig = true;
   }
   else if (dutycycleOnPercent > algoInstPtr->dutycycleOnPercent)
   {
      dutycycleUpdateConfig = true;
   }
   else if (dutycycleOnPercent == algoInstPtr->dutycycleOnPercent)
   {
      if (dutycycleOnDuration < algoInstPtr->dutycycleOnDuration)
      {
         dutycycleUpdateConfig = true;
      }
   }

   // update algo instance database
   if (dutycycleUpdateConfig)
   {
      algoInstPtr->dutycycleOnPercent = dutycycleOnPercent;
      algoInstPtr->dutycycleOnDuration = dutycycleOnDuration;
      algoInstPtr->dutycycleStateOn = true;
      algoInstPtr->dutycycleTimeoutCount = 0;
      algoInstPtr->dutycycleTimerSource = clientReqId;
   }

   if((algoInstPtr->dutycycleOnPercent >= 100) ||
      (algoInstPtr->dutycycleOnDuration <= 0))
   {
      // disable duty cycling
      algoInstPtr->dutycycleTimerSource =
         (int16_t)SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE;
   }
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_enable_algo
  =========================================================================*/
/*!
  @brief
  enables specified algorithm with the specified configuration

  @param[i] algoIndex: index to algorithm in the algorithm database
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[i] mrClntId: MR Client ID
  @param[i] directReportReq: indicates if reporting using messages can be
                             bypassed using a direct function call instead

  @return index of the algorithm instance in database if successful,
          SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
static uint8_t sns_sam_enable_algo(
   uint8_t              algoIndex,
   const void           *clientReqMsgPtr,
   sns_sam_mr_conn_hndl mrClntId,
   bool                 directReportReq)
{
   uint8_t algoInstId, clientReqId;
   sns_sam_algo_inst_s * algoInstPtr = NULL;

   algoInstId = sns_sam_get_algo_inst(algoIndex, clientReqMsgPtr);
   if( algoInstId >= SNS_SAM_MAX_ALGO_INSTS )
   {
      return SNS_SAM_INVALID_ID;
   }

   algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   if( algoInstPtr == NULL )
   {
      return SNS_SAM_INVALID_ID;
   }

   //add client request
   clientReqId = sns_sam_add_client_req(clientReqMsgPtr,
                                        algoInstId,
                                        mrClntId,
                                        directReportReq);
   if (clientReqId >= SNS_SAM_MAX_CLIENT_REQS)
   {
      SNS_SAM_PRINTF1(ERROR,"SAM: Add client req failed %d",sns_sam_client_req_count);
      return SNS_SAM_INVALID_ID;
   }

   //Register client with SAM
   algoInstPtr->clientReqDbase[algoInstPtr->clientReqCount] =
      clientReqId;
   algoInstPtr->clientReqCount++;

   // Register client with algorithm
   if( sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_register_client )
   {
      void * statePtr = algoInstPtr->stateData.memPtr;
      void * outputPtr = algoInstPtr->outputData.memPtr;
      uint8_t clientId = sns_sam_client_req_dbase[clientReqId]->mrClientId;
      uint32_t timestamp = sns_em_get_timestamp();
      sns_sam_algo_dbase[algoIndex]->algoApi.
         sns_sam_algo_register_client(clientId, true, statePtr, outputPtr, timestamp);
   }

   //send latest report to new client
   if (algoInstPtr->clientReqCount > 1)
   {
     // Check the buffering requirements for this algo request vs the current algo instance
     // if this algo request requires a faster rate, then flush and delete the old SMGR buffering request
     // and add a new SMGR buffering request at the faster rate
     if(sns_sam_algo_dbase[algoIndex]->dataSyncRequired &&
        sns_sam_get_smgr_msg_req_type(algoInstPtr->serviceId) == SNS_SMGR_BUFFERING_REQ_V01)
     {
       uint8_t dataReqId = sns_sam_find_data_req_id(algoInstId, false);

       if (dataReqId != SNS_SAM_INVALID_ID)
       {
         sns_sam_data_req_s *dataReq = sns_sam_data_req_dbase[dataReqId];

         float report_rate = (float)
             (SNS_SAM_USEC_PER_SEC /
              sns_em_convert_localtick_to_usec(sns_sam_client_req_dbase[clientReqId]->period));
         uint32_t new_report_rate = FX_FLTTOFIX_Q16(report_rate);

         if (dataReq->reportRate < new_report_rate)
         {
           // Restart the SMGR buffer request with the updated rate, this should flush the buffer
           SNS_SAM_PRINTF3(HIGH, "Updating data request %d. Old %d New %d", dataReqId, dataReq->reportRate, new_report_rate);
           dataReq->reportRate = new_report_rate;
           sns_sam_send_smgr_start_req(dataReqId,
                                       sns_sam_algo_inst_dbase[algoInstId]->serviceId);
         }
       }
     }

     sns_sam_algo_rpt_s *algoRptPtr = sns_sam_get_algo_report(algoInstId);
     if (NULL != algoRptPtr)
     {
       //process algorithm report indication to client
       sns_sam_process_algo_report(clientReqId, algoRptPtr, mrClntId);
     }
   }

   sns_sam_update_duty_cycle_config_client_add(algoInstId,
                                               algoIndex,
                                               clientReqId);

   if( !sns_sam_algo_dbase[algoIndex]->dataSyncRequired && 
       algoInstPtr->clientReqCount == 1 )
   {
      // If algorithm has no synchronous dependencies on other algorithms,
      // request for sensor data now. For algorithms that have dependencies,
      // sensor data will be requested after aggregating requests from all
      // dependent algorithms
      sns_sam_req_sensor_data(algoInstId, clientReqId);
   }

   SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_ENABLE_ALGO,
                  sns_sam_algo_dbase[algoIndex]->serviceId,
                  clientReqId,
                  algoInstId);

   return algoInstId;
}

/*=========================================================================
  FUNCTION:  sns_sam_disable_algo
  =========================================================================*/
/*!
  @brief Decrements the reference count of the algorithm instance.
         If count is zero, deletes an instance and frees up its resources

  @param[i] clientReqId: index to the client request in database

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_disable_algo(
   uint8_t clientReqId)
{
   uint8_t algoInstId, algoIndex, i, a, b;
   sns_sam_algo_inst_s *algoInstPtr;
   void * statePtr;
   void * outputPtr;

   algoInstId = sns_sam_client_req_dbase[clientReqId]->algoInstId;

   if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_DISABLE_ALGO_INSTANCE_ERR, algoInstId);
      return SNS_ERR_FAILED;
   }

   algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   if (algoInstPtr == NULL || algoInstPtr->clientReqCount == 0)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_DISABLE_ALGO_INSTANCE_ERR, algoInstId);
      return SNS_ERR_FAILED;
   }

   for (i = 0; i<algoInstPtr->clientReqCount; i++)
   {
      if (algoInstPtr->clientReqDbase[i] == clientReqId)
      {
         algoInstPtr->clientReqCount--;
         algoInstPtr->clientReqDbase[i] =
            algoInstPtr->clientReqDbase[algoInstPtr->clientReqCount];
         algoInstPtr->clientReqDbase[algoInstPtr->clientReqCount] =
            SNS_SAM_INVALID_ID;

         // Deregister client from algorithm instance
         algoIndex = sns_sam_get_algo_index(algoInstPtr->serviceId);
         if( algoIndex >= SNS_SAM_MAX_ALGOS ||
             sns_sam_algo_dbase[algoIndex] == NULL )
         {
            SNS_SAM_DEBUG1(ERROR, DBG_SAM_DISABLE_ALGO_INSTANCE_ERR, algoInstId);
            return SNS_ERR_FAILED;
         }

         if( algoIndex < SNS_SAM_MAX_ALGOS &&
             sns_sam_algo_dbase[algoIndex] != NULL &&
             sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_register_client )
         {
            statePtr = algoInstPtr->stateData.memPtr;
            outputPtr = algoInstPtr->outputData.memPtr;
            sns_sam_algo_dbase[algoIndex]->algoApi.
               sns_sam_algo_register_client(
                   sns_sam_client_req_dbase[clientReqId]->mrClientId,
                   false, statePtr, outputPtr, 0);
         }

         if (algoInstPtr->clientReqCount > 0)
         {
            sns_sam_delete_client_req(clientReqId);

            sns_sam_update_duty_cycle_config_client_removal(clientReqId,
                                                            algoInstId,
                                                            algoInstPtr);

            if( sns_sam_algo_dbase[algoIndex]->dataSyncRequired &&
                sns_sam_get_smgr_msg_req_type(algoInstPtr->serviceId) == SNS_SMGR_BUFFERING_REQ_V01 )
            {
               uint8_t dataReqId = sns_sam_find_data_req_id(algoInstId, false);

               if (dataReqId != SNS_SAM_INVALID_ID)
               {
                  sns_sam_data_req_s *dataReq = sns_sam_data_req_dbase[dataReqId];
                  sns_sam_algo_inst_s *algoInstIter;
                  sns_sam_client_req_s *clientReqIter;

                  float report_rate;
                  uint32_t new_report_rate = 0, temp_report_rate;

                  // Search through all of the dependent algo instances for the fastest report rate amongst the clients
                  for ( a = 0; a < dataReq->algoInstCount; a++ )
                  {
                     algoInstIter = sns_sam_algo_inst_dbase[dataReq->algoInstDbase[a]];

                     // Search for the fastest report rate amongst all of the clients for this algo instance
                     for ( b = 0; b < algoInstIter->clientReqCount; b++ )
                     {
                        clientReqIter = sns_sam_client_req_dbase[algoInstIter->clientReqDbase[b]];

                        report_rate = (float) (SNS_SAM_USEC_PER_SEC /
                            sns_em_convert_localtick_to_usec(clientReqIter->period));
                        temp_report_rate = FX_FLTTOFIX_Q16(report_rate);

                        if ( new_report_rate < temp_report_rate )
                        {
                           new_report_rate = temp_report_rate;
                        }
                     }
                  }

                  if (dataReq->reportRate > new_report_rate)
                  {
                      // Restart the SMGR buffer request with the updated rate, this should flush the buffer
                      dataReq->reportRate = new_report_rate;
                      sns_sam_send_smgr_start_req(dataReqId,
                                                  sns_sam_algo_inst_dbase[algoInstId]->serviceId);
                  }
               }
            }

            return SNS_SUCCESS;
         }

         break;
      }
   }

   algoIndex = sns_sam_get_algo_index(algoInstPtr->serviceId);
   if (algoIndex >= SNS_SAM_MAX_ALGOS || sns_sam_algo_dbase[algoIndex] == NULL)
   {
      return SNS_ERR_FAILED;
   }

   sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_reset(
      algoInstPtr->configData.memPtr,
      algoInstPtr->stateData.memPtr);

   //stop sensor data
   sns_sam_stop_sensor_data(algoInstId);

   SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_DISABLE_ALGO,
                  sns_sam_algo_dbase[algoIndex]->serviceId,
                  clientReqId,
                  algoInstId);

   sns_sam_delete_client_req(clientReqId);

   //delete the algo instance
   sns_sam_delete_algo_inst(algoInstId);

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sam_resp
  =========================================================================*/
/*!
  @brief Processes the response received from sensors algorithm manager

  @param[i] samRespPtr: Pointer to sensors algorithm manager response message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_sam_resp(
   const void *samRespPtr)
{
   uint8_t algoInstId, algoDepId;
   uint8_t depAlgoInstId;
   sns_err_code_e err = SNS_ERR_FAILED;
   sns_smr_header_s msgHdr;

   sns_smr_get_hdr(&msgHdr, samRespPtr);
   algoInstId = msgHdr.ext_clnt_id;
   algoDepId = msgHdr.txn_id;

   if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS)
   {
      return SNS_ERR_FAILED;
   }

   depAlgoInstId = sns_sam_process_sam_response(samRespPtr);

   if (depAlgoInstId < SNS_SAM_MAX_ALGO_INSTS)
   {
      if (msgHdr.msg_id == SNS_SAM_ALGO_ENABLE_RESP)
      {
         // Check to discard delayed enable response for
         // algorithm instance that has been disabled per client request
         if (sns_sam_algo_inst_dbase[algoInstId] != NULL &&
             algoDepId < SNS_SAM_MAX_ALGO_DEPS)
         {
            sns_sam_algo_inst_dbase[algoInstId]->algoReqDbase[algoDepId] =
               depAlgoInstId;
         }
      }
      else if (msgHdr.msg_id == SNS_SAM_ALGO_DISABLE_RESP)
      {
         SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_DISABLE_ALGO,
                        algoInstId, algoDepId, depAlgoInstId);
      }
      err = SNS_SUCCESS;
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_enable_msg
  =========================================================================*/
/*!
  @brief Send the algorithm enable request message

  @param[i] algoInstId: dependor algorithm instance id
  @param[i] algoServiceId: dependee algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[i] txnId: transaction id
  @param[i] mrClntId: Client ID

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_send_algo_enable_msg(
   uint8_t                       algoInstId,
   uint8_t                       algoServiceId,
   const void                    *clientReqMsgPtr,
   uint8_t                       algoDepId,
   sns_sam_mr_algo_conn_hndl     *mrAlgoConnHndl)
{
   sns_err_code_e err = SNS_ERR_FAILED;
   void* msgPtr = NULL;
   sns_sam_algo_inst_s *algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   void *resp_msg_ptr = NULL;
   uint8_t depAlgoIndex;
   sns_smr_header_s msgHdr;

   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   msgHdr.msg_id = SNS_SAM_ALGO_ENABLE_REQ;

   msgHdr.svc_num = algoServiceId;
   /* use external client id to detect dependent algorithm instance */
   msgHdr.ext_clnt_id = algoInstId;
   msgHdr.txn_id = algoDepId;

   msgPtr = sns_sam_gen_algo_enable_msg(algoInstPtr,
                                        clientReqMsgPtr,
                                        &msgHdr);

   depAlgoIndex = sns_sam_get_algo_index(algoServiceId);
   if( depAlgoIndex > SNS_SAM_MAX_ALGOS )
   {
      // Dependent algorithm is not co-located
      err = sns_sam_mr_send(msgPtr, mrAlgoConnHndl);
   }
   else
   {
      // Dependent algorithm is co-located. Skip QMI.
      err = sns_sam_process_client_req( msgPtr, SNS_SAM_MAX_CLI_ID + algoInstId, &resp_msg_ptr );
      if( err == SNS_SUCCESS )
      {
         err = sns_sam_process_sam_resp(resp_msg_ptr);
         sns_smr_msg_free(resp_msg_ptr);
      }
	  if( NULL != msgPtr )
	  {
	     sns_smr_msg_free(msgPtr);
	  }
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_disable_msg
  =========================================================================*/
/*!
  @brief Send the algorithm enable request message

  @param[i] algoSvcId: algorithm service id
  @param[i] algoInstId: algorithm instance id
  @param[i] extClientId: external client id
  @param[i] mrClntId: MR Client ID

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_send_algo_disable_msg(
   uint8_t                       algoSvcId,
   uint8_t                       algoInstId,
   uint8_t                       extClientId,
   sns_sam_mr_algo_conn_hndl     *mrAlgoConnHndl)
{
   sns_err_code_e err = SNS_ERR_FAILED;
   void* msgPtr = NULL;
   void *resp_msg_ptr = NULL;
   uint8_t depAlgoIndex;
   sns_smr_header_s msgHdr;

   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   msgHdr.msg_id = SNS_SAM_ALGO_DISABLE_REQ;

   msgHdr.svc_num = algoSvcId;

   /* use external client id to detect dependent algorithm instance */
   msgHdr.ext_clnt_id = extClientId;
   msgHdr.txn_id = 0;

   msgPtr = sns_sam_gen_algo_disable_msg(algoInstId, &msgHdr);

   depAlgoIndex = sns_sam_get_algo_index(algoSvcId);
   if( depAlgoIndex > SNS_SAM_MAX_ALGOS )
   {
      // Dependent algorithm is not co-located
      err = sns_sam_mr_send(msgPtr, mrAlgoConnHndl);
   }
   else
   {
      // Dependent algorithm is co-located. Skip QMI.
      err = sns_sam_process_client_req( msgPtr, SNS_SAM_MAX_CLI_ID + extClientId, &resp_msg_ptr );
      if( err == SNS_SUCCESS )
      {
         err = sns_sam_process_sam_resp(resp_msg_ptr);
         sns_smr_msg_free(resp_msg_ptr);
      }
	  if( NULL != msgPtr )
	  {
         sns_smr_msg_free(msgPtr);
      }
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_enable_sync_dependent_algos
  =========================================================================*/
/*!
  @brief    Recursively enables all dependent algorithms with the
            specified configuration

  @param[i] currAlgoInstId: algorithm instance ID
  @param[i] algo: pointer to algorithm structure
  @param[i] msgPtr: pointer to client request message
  @param[i/o] totalDataReq: pointer to aggregated data request

  @return   SNS_SUCCESS if algo is instantiated properly,
            SNS_ERR_FAILED otherwise

*/
/*=======================================================================*/
static sns_err_code_e sns_sam_enable_sync_dependent_algos(
   uint8_t currAlgoInstId,
   const sns_sam_algo_s* algo,
   const void* msgPtr,
   sns_sam_data_req_s * totalDataReq)
{
   uint8_t depAlgoIndex, sensorReqIndex, sensorIndex, algoInstIndex, algoIndex, algoInstId, clientReqId;
   sns_sam_data_req_s dataReq;

   if( !sns_sam_algo_inst_dbase[currAlgoInstId] )
   {
      SNS_SAM_PRINTF1( ERROR, "parent algo inst id %d unknown", currAlgoInstId );
      return SNS_ERR_FAILED;
   }

   if (sns_sam_algo_inst_dbase[currAlgoInstId]->clientReqCount >= 1)
   {
      for(depAlgoIndex = 0; depAlgoIndex < algo->algoDepCount; depAlgoIndex++)
      {
         void* enableMsgPtr;
         sns_smr_header_s enableMsgHdr;
         sns_err_code_e err;
         bool directReportReq = true;

         if( totalDataReq->algoInstCount == SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR )
         {
            // Cannot support another algorithm instance
            SNS_SAM_PRINTF0( ERROR, "SAM cannot support more algo insts in data req" );
            return SNS_ERR_FAILED;
         }

         enableMsgHdr.src_module = SNS_SAM_MODULE;
         enableMsgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
         enableMsgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
         enableMsgHdr.msg_id = SNS_SAM_ALGO_ENABLE_REQ;

         enableMsgHdr.svc_num = algo->algoDepDbase[depAlgoIndex];
         enableMsgHdr.ext_clnt_id = currAlgoInstId;
         enableMsgHdr.txn_id = depAlgoIndex;
         enableMsgPtr = sns_sam_gen_algo_enable_msg(
                              sns_sam_algo_inst_dbase[currAlgoInstId],
                              msgPtr, &enableMsgHdr);

         SNS_SAM_PRINTF2( LOW, "SAM enabling sync dep algo svc %d for parent svc %d",
            algo->algoDepDbase[depAlgoIndex], sns_sam_algo_inst_dbase[currAlgoInstId]->serviceId );

         if(enableMsgPtr == NULL)
         {
            continue;
         }

         algoIndex = sns_sam_get_algo_index(algo->algoDepDbase[depAlgoIndex]);
         if (algoIndex >= SNS_SAM_MAX_ALGOS)
         {
            if(enableMsgPtr != NULL)
            {
               sns_smr_msg_free(enableMsgPtr);
            }
            return SNS_ERR_FAILED;
         }
         algoInstId = sns_sam_get_algo_inst(algoIndex, enableMsgPtr);
         if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
            sns_sam_algo_inst_dbase[algoInstId] == NULL)
         {
            SNS_SAM_PRINTF1( ERROR, "SAM unknown algo inst id %d", algoInstId );
            if(enableMsgPtr != NULL)
            {
               sns_smr_msg_free(enableMsgPtr);
            }
            return SNS_ERR_FAILED;
         }
         if (sns_sam_algo_inst_dbase[algoInstId]->clientReqCount >=
            SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST)
         {
            SNS_SAM_PRINTF1( ERROR, "SAM - no space for more client reqs in algo inst %d", algoInstId );
            if(enableMsgPtr != NULL)
            {
               sns_smr_msg_free(enableMsgPtr);
            }
            return SNS_ERR_FAILED;
         }

         if( sns_sam_algo_inst_dbase[currAlgoInstId]->clientReqCount == 1 )
         {
            clientReqId = sns_sam_add_client_req(enableMsgPtr, algoInstId, SNS_SAM_MAX_CLI_ID + currAlgoInstId, directReportReq);
            if (clientReqId >= SNS_SAM_MAX_CLIENT_REQS)
            {
               SNS_SAM_PRINTF1( ERROR, "SAM - add client req failed for algo inst %d", algoInstId );
               if(enableMsgPtr != NULL)
               {
                  sns_smr_msg_free(enableMsgPtr);
               }
               return SNS_ERR_FAILED;
            }

            sns_sam_algo_inst_dbase[algoInstId]->
            clientReqDbase[sns_sam_algo_inst_dbase[algoInstId]->clientReqCount] =
               clientReqId;
            sns_sam_algo_inst_dbase[algoInstId]->clientReqCount++;
         }

         sns_sam_get_sensor_requirements(
            sns_sam_algo_inst_dbase[algoInstId]->serviceId,
            sns_sam_algo_inst_dbase[algoInstId]->configData.memPtr,
            &dataReq);

         // Adds new sensors to data request
         if (dataReq.sensorCount > 0)
         {
            for(sensorReqIndex = 0; sensorReqIndex < dataReq.sensorCount; sensorReqIndex++)
            {
               // Checks if the sensor already exists
               for(sensorIndex = 0; sensorIndex < totalDataReq->sensorCount; sensorIndex++)
               {
                  if( (dataReq.sensorDbase[sensorReqIndex].sensorId == totalDataReq->sensorDbase[sensorIndex].sensorId) &&
                      (dataReq.sensorDbase[sensorReqIndex].dataType == totalDataReq->sensorDbase[sensorIndex].dataType) &&
                      (dataReq.sensorDbase[sensorReqIndex].sampleRate == totalDataReq->sensorDbase[sensorIndex].sampleRate) &&
                      (dataReq.sensorDbase[sensorReqIndex].sampleQual == totalDataReq->sensorDbase[sensorIndex].sampleQual))
                  {
                     break;
                  }
               }

               if(sensorIndex >= totalDataReq->sensorCount)
               {
                  if( totalDataReq->sensorCount >= SNS_SAM_MAX_SENSORS_PER_DATA_REQ)
                  {
                     SNS_SAM_PRINTF0( ERROR, "SAM cannot add more sensor reqs to data req" );
                     if(enableMsgPtr != NULL)
                     {
                        sns_smr_msg_free(enableMsgPtr);
                     }
                     return SNS_ERR_FAILED;
                  }

                  totalDataReq->sensorDbase[totalDataReq->sensorCount].sensorId = dataReq.sensorDbase[sensorReqIndex].sensorId;
                  totalDataReq->sensorDbase[totalDataReq->sensorCount].dataType = dataReq.sensorDbase[sensorReqIndex].dataType;
                  totalDataReq->sensorDbase[totalDataReq->sensorCount].sampleRate = dataReq.sensorDbase[sensorReqIndex].sampleRate;
                  totalDataReq->sensorDbase[totalDataReq->sensorCount].sampleQual = dataReq.sensorDbase[sensorReqIndex].sampleQual;
                  totalDataReq->sensorDbase[totalDataReq->sensorCount].algoInstIds[0] = algoInstId;
                  totalDataReq->sensorDbase[totalDataReq->sensorCount].algoInstCount = 1;
                  (totalDataReq->sensorCount)++;
               }
               else
               {
                  // Sensor already exists - check if algo instance does too
                  for( algoInstIndex = 0; algoInstIndex < totalDataReq->sensorDbase[sensorIndex].algoInstCount; ++algoInstIndex )
                  {
                     if( totalDataReq->sensorDbase[sensorIndex].algoInstIds[algoInstIndex] == algoInstId )
                     {
                        break;
                     }
                  }

                  if( algoInstIndex == SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR )
                  {
                     // Cannot support another algorithm instance
                     SNS_SAM_PRINTF0( ERROR, "SAM cannot support more algo insts in sensor req" );
                     if(enableMsgPtr != NULL)
                     {
                        sns_smr_msg_free(enableMsgPtr);
                     }
                     return SNS_ERR_FAILED;
                  }
                  else if( algoInstIndex == totalDataReq->sensorDbase[sensorIndex].algoInstCount )
                  {
                     totalDataReq->sensorDbase[sensorIndex].algoInstIds[totalDataReq->sensorDbase[sensorIndex].algoInstCount] = 
                       algoInstId;
                     totalDataReq->sensorDbase[sensorIndex].algoInstCount++;
                  }
               }
            }
            // Add to algo inst table if not present already
            for( algoInstIndex = 0; algoInstIndex < totalDataReq->algoInstCount; algoInstIndex++ )
            {
               if( totalDataReq->algoInstDbase[algoInstIndex] == algoInstId )
               {
                  break;
               }
            }
            if( algoInstIndex == totalDataReq->algoInstCount &&
                algoInstIndex < SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR )
            {
               totalDataReq->algoInstDbase[algoInstIndex] = algoInstId;
               totalDataReq->algoInstCount++;
            }
         }

         // Enables other algos by recursion
         err = sns_sam_enable_sync_dependent_algos(algoInstId,
                                                   sns_sam_algo_dbase[algoIndex],
                                                   enableMsgPtr,
                                                   totalDataReq);

         if(enableMsgPtr != NULL)
         {
            sns_smr_msg_free(enableMsgPtr);
         }

         if( err != SNS_SUCCESS )
         {
            return err;
         }

         if (sns_sam_algo_inst_dbase[currAlgoInstId]->clientReqCount == 1)
         {
            // store algo instance id in dependent algorithm request database
            if (currAlgoInstId < SNS_SAM_MAX_ALGO_INSTS &&
                depAlgoIndex < SNS_SAM_MAX_ALGO_DEPS &&
                sns_sam_algo_inst_dbase[currAlgoInstId] != NULL)
            {
               sns_sam_algo_inst_dbase[currAlgoInstId]->algoReqDbase[depAlgoIndex] = algoInstId;
            }
            else
            {
               return SNS_ERR_FAILED;
            }
         }
      } /* for all dep algos */
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_enable_dependent_algos
  =========================================================================*/
/*!
  @brief Enables algorithms that are dependent on a given algorithm

  @param[i] algoInstId: Algorithm Instance ID
  @param[i] algoIndex: Index of algorithm in the algorithm database
  @param[i] clientReqMsgPtr: Pointer to client request message
  @param[i] mrClntId: external client ID set by SAM MR

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_enable_dependent_algos(
   uint8_t               algoInstId,
   uint8_t               algoIndex,
   const void           *clientReqMsgPtr,
   sns_sam_mr_conn_hndl  mrClntId)
{
   sns_err_code_e err = SNS_SUCCESS;

   if( algoIndex >= SNS_SAM_MAX_ALGOS ||
       sns_sam_algo_dbase[algoIndex] == NULL ||
       algoInstId  >= SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_dbase[algoInstId] == NULL ||
       clientReqMsgPtr == NULL )
   {
      return SNS_ERR_BAD_PARM;
   }

   if( sns_sam_algo_dbase[algoIndex]->dataSyncRequired )
   {
      // Algorithm requires synchronous sensor and dependent algo outputs
      // Enable dependent algorithms recursively for synchronization
      sns_sam_algo_inst_s * algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
      sns_sam_data_req_s dataReq;
      uint32_t i;

      sns_sam_get_sensor_requirements(algoInstPtr->serviceId,
                                      algoInstPtr->configData.memPtr,
                                      &dataReq);

      // Initialize data request
      dataReq.algoInstDbase[0] = algoInstId;
      dataReq.algoInstCount = 1;
      for( i = 0; i < dataReq.sensorCount; ++i )
      {
         dataReq.sensorDbase[i].algoInstIds[0] = algoInstId;
         dataReq.sensorDbase[i].algoInstCount = 1;
      }

      if( sns_sam_algo_dbase[algoIndex]->algoDepCount )
      {
         // Enable dependent algorithms and aggregate data request
         err = sns_sam_enable_sync_dependent_algos( algoInstId, sns_sam_algo_dbase[algoIndex],
                                                    clientReqMsgPtr, &dataReq );
      }

      SNS_SAM_PRINTF2( LOW, "SAM: sensor requirements - count %d, err %d",
          dataReq.sensorCount, err );
      for( i = 0; i < dataReq.sensorCount; ++i )
      {
         SNS_SAM_PRINTF3( LOW, "SAM: Item %d Sensor id %d Sample Rate %d", i,
             dataReq.sensorDbase[i].sensorId, dataReq.sensorDbase[i].sampleRate );
         SNS_SAM_PRINTF2( LOW, "SAM: Algo inst 1 %d Algo inst 2 %d",
             dataReq.sensorDbase[i].algoInstIds[0], dataReq.sensorDbase[i].algoInstIds[1] );
      }

      if( err == SNS_SUCCESS && dataReq.sensorCount > 0 )
      {
         // Request for sensor data
         uint8_t dataReqId;
         sns_smr_header_s msgHdr;
         uint8_t clientReqId;

         msgHdr.svc_num = algoInstPtr->serviceId;
         clientReqId = sns_sam_find_client_req( &msgHdr, mrClntId );

         if( clientReqId < SNS_SAM_MAX_CLIENT_REQS &&
             sns_sam_client_req_dbase[clientReqId] != NULL &&
             sns_sam_client_req_dbase[clientReqId]->reportType == SNS_SAM_PERIODIC_REPORT )
         {
            // Periodic reporting - use client report rate as sensor report rate
            float report_rate = (float)
               (SNS_SAM_USEC_PER_SEC /
                sns_em_convert_localtick_to_usec(sns_sam_client_req_dbase[clientReqId]->period));
            dataReq.reportRate = FX_FLTTOFIX_Q16(report_rate);
         }

         SNS_SAM_PRINTF1( LOW, "SAM: data request at report rate %d", dataReq.reportRate );
         dataReqId = sns_sam_start_sensor_data(algoInstId, &dataReq);
         if( dataReqId == SNS_SAM_INVALID_ID )
         {
            return SNS_ERR_FAILED;
         }
      }
   }
   else
   {
      if (sns_sam_algo_dbase[algoIndex]->algoDepCount)
      {
         // Send messages to enable dependent algorithms
         int32_t i;
         for (i = 0; i < sns_sam_algo_dbase[algoIndex]->algoDepCount; i++)
         {
            err = sns_sam_send_algo_enable_msg(algoInstId,
                                               sns_sam_algo_dbase[algoIndex]->algoDepDbase[i],
                                               clientReqMsgPtr,
                                               i,
                                               sns_sam_algo_inst_dbase[algoInstId]->mrAlgoConnHndl);

            if (err != SNS_SUCCESS)
            {
               return err;
            }
         }
      }
   }
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_disable_sync_dependent_algos
  =========================================================================*/
/*!
  @brief    Recursively disables all dependent algorithms from the bottom up

  @param[i] algoInstId: algorithm instance ID
  @param[i] algoIndex: index of algorithm in algo dbase
  @param[i] parentAlgoInstId: parent algorithm's instance ID

  @return   SNS_SUCCESS if algo is disabled properly,
            SNS_ERR_FAILED otherwise

*/
/*=======================================================================*/
static sns_err_code_e sns_sam_disable_sync_dependent_algos(
   uint8_t algoInstId,
   uint8_t algoIndex,
   uint8_t parentAlgoInstId)
{
   sns_err_code_e err= SNS_SUCCESS;
   uint8_t i, childAlgoInstId, childAlgoIndex, clientReqId;
   sns_sam_algo_inst_s *algoInstPtr;
   void * statePtr;
   void * outputPtr;
   sns_smr_header_s msgHdr;

   SNS_SAM_PRINTF1( LOW, "SAM disabling sync dep children of algo inst id %d", algoInstId );

   if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_DISABLE_ALGO_INSTANCE_ERR, algoInstId);
      return SNS_ERR_FAILED;
   }

   algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
   if (algoInstPtr == NULL || algoInstPtr->clientReqCount == 0)
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_DISABLE_ALGO_INSTANCE_ERR, algoInstId);
      return SNS_ERR_FAILED;
   }

   if( algoInstPtr->clientReqCount == 1 )
   {
      for (i = 0; i < sns_sam_algo_dbase[algoIndex]->algoDepCount; i++)
      {
         childAlgoInstId = algoInstPtr->algoReqDbase[i];
         childAlgoIndex = sns_sam_get_algo_index(sns_sam_algo_dbase[algoIndex]->algoDepDbase[i]);
         err = sns_sam_disable_sync_dependent_algos( childAlgoInstId, childAlgoIndex, algoInstId );
      }
   }

   msgHdr.svc_num = algoInstPtr->serviceId;
   clientReqId = sns_sam_find_client_req( &msgHdr, SNS_SAM_MAX_CLI_ID + parentAlgoInstId );
   if( clientReqId == SNS_SAM_INVALID_ID )
   {
      SNS_SAM_PRINTF2( ERROR, "Client req id not found: algo inst %d, parent algo inst %d",
          algoInstId, parentAlgoInstId );
      return SNS_ERR_FAILED;
   }

   for (i = 0; i<algoInstPtr->clientReqCount; i++)
   {
      if (algoInstPtr->clientReqDbase[i] == clientReqId)
      {
         algoInstPtr->clientReqCount--;
         algoInstPtr->clientReqDbase[i] =
            algoInstPtr->clientReqDbase[algoInstPtr->clientReqCount];
         algoInstPtr->clientReqDbase[algoInstPtr->clientReqCount] =
            SNS_SAM_INVALID_ID;

         // Deregister client from algorithm instance
         if( sns_sam_algo_dbase[algoIndex] != NULL &&
             sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_register_client )
         {
            statePtr = algoInstPtr->stateData.memPtr;
            outputPtr = algoInstPtr->outputData.memPtr;
            sns_sam_algo_dbase[algoIndex]->algoApi.
               sns_sam_algo_register_client(
                  sns_sam_client_req_dbase[clientReqId]->mrClientId,
                  false, statePtr, outputPtr, 0);
         }

         if (algoInstPtr->clientReqCount > 0)
         {
            sns_sam_delete_client_req(clientReqId);

            sns_sam_update_duty_cycle_config_client_removal(clientReqId,
                                                            algoInstId,
                                                            algoInstPtr);

            // othe client requests are pending - do not delete algo instance
            return SNS_SUCCESS;
         }

         break;
      }
   }

   sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_reset(
      algoInstPtr->configData.memPtr,
      algoInstPtr->stateData.memPtr);

   //stop sensor data
   sns_sam_stop_sensor_data(algoInstId);

   sns_sam_delete_client_req(clientReqId);

   //delete the algo instance
   sns_sam_delete_algo_inst(algoInstId);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_disable_dependent_algos
  =========================================================================*/
/*!
  @brief Disables algorithms that are dependent on a given algorithm

  @param[i] algoInstId: Algorithm Instance ID
  @param[i] algoIndex: Index of algorithm in the algorithm database

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_disable_dependent_algos(
   uint8_t algoInstId,
   uint8_t algoIndex)
{
   sns_err_code_e err = SNS_SUCCESS;

   if( algoIndex >= SNS_SAM_MAX_ALGOS ||
       sns_sam_algo_dbase[algoIndex] == NULL ||
       algoInstId  >= SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_dbase[algoInstId] == NULL )
   {
      return SNS_ERR_BAD_PARM;
   }

   if( sns_sam_algo_dbase[algoIndex]->dataSyncRequired )
   {
      // Disable all dependent algorithms synchronously
      int32_t i;
      for (i = 0; i < sns_sam_algo_dbase[algoIndex]->algoDepCount; i++)
      {
         uint8_t childAlgoInstId = sns_sam_algo_inst_dbase[algoInstId]->algoReqDbase[i];
         uint8_t childAlgoIndex = sns_sam_get_algo_index(sns_sam_algo_dbase[algoIndex]->algoDepDbase[i]);
         err = sns_sam_disable_sync_dependent_algos( childAlgoInstId, childAlgoIndex, algoInstId );

         if (err != SNS_SUCCESS)
         {
            return err;
         }
      }
   }
   else
   {
      // Send messages to disable dependent algorithms
      int32_t i;
      for (i = 0; i < sns_sam_algo_dbase[algoIndex]->algoDepCount; i++)
      {
         err = sns_sam_send_algo_disable_msg(
                  sns_sam_algo_dbase[algoIndex]->algoDepDbase[i],
                  sns_sam_algo_inst_dbase[algoInstId]->algoReqDbase[i],
                  algoInstId,
                  sns_sam_algo_inst_dbase[algoInstId]->mrAlgoConnHndl);

         if (err != SNS_SUCCESS)
         {
            return err;
         }
      }
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_enable_req
  =========================================================================*/
/*!
  @brief Processes the enable request for specified algorithm

  @param[i] clientReqMsgPtr: Pointer to client request message
  @param[i] mrClntId: Client ID
  @param[i] algoIndex: index of algorithm in algo database
  @param[i] msgHdr: SMR header from client request
  @param[o] algoInstId: algorithm instance id

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_algo_enable_req(
   const void           *clientReqMsgPtr,
   sns_sam_mr_conn_hndl  mrClntId,
   uint8_t               algoIndex,
   sns_smr_header_s     *msgHdr,
   uint8_t              *algoInstId)
{
   sns_err_code_e err = SNS_SUCCESS;
   bool directReportReq;

   if( !algoInstId || !clientReqMsgPtr || !msgHdr )
   {
      SNS_SAM_PRINTF0(ERROR, "sns_sam_process_algo_enable_req: Bad ptr");
      return SNS_ERR_BAD_PARM;
   }

   directReportReq = (msgHdr->src_module == SNS_SAM_MODULE);
   SNS_SAM_PRINTF1(LOW, "sns_sam_process_algo_enable_req: src_module = %d", msgHdr->src_module);
   *algoInstId = sns_sam_enable_algo(algoIndex, clientReqMsgPtr, mrClntId, directReportReq);

   if (*algoInstId  >= SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_dbase[*algoInstId] == NULL)
   {
      return SNS_ERR_FAILED;
   }

   //enable algorithms on which this algorithm depends
   if( sns_sam_algo_inst_dbase[*algoInstId]->clientReqCount == 1 )
   {
      err = sns_sam_enable_dependent_algos(*algoInstId,
                                           algoIndex,
                                           clientReqMsgPtr,
                                           mrClntId);

      if (err != SNS_SUCCESS)
      {
         return err;
      }
   }

   if (msgHdr->src_module == SNS_SAM_MODULE)
   {
      // store algo instance id in dependent algorithm request database
      if (msgHdr->ext_clnt_id < SNS_SAM_MAX_ALGO_INSTS &&
          msgHdr->txn_id < SNS_SAM_MAX_ALGO_DEPS &&
          sns_sam_algo_inst_dbase[msgHdr->ext_clnt_id] != NULL)
      {
         sns_sam_algo_inst_dbase[msgHdr->ext_clnt_id]->algoReqDbase[msgHdr->txn_id]
            = *algoInstId;
      }
      else
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_INS_ID_ERR, msgHdr->ext_clnt_id, msgHdr->txn_id);
         return SNS_ERR_BAD_PARM;
      }
   }
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_disable_req
  =========================================================================*/
/*!
  @brief Processes the enable request for specified algorithm

  @param[i] algoInstId: algorithm instance id
  @param[i] algoIndex: index of algorithm in algo database
  @param[i] clientReqId: client request id id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_algo_disable_req(
   uint8_t algoInstId,
   uint8_t algoIndex,
   uint8_t clientReqId)
{
   sns_err_code_e err;

   if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
       sns_sam_algo_inst_dbase[algoInstId] == NULL ||
       algoIndex >= SNS_SAM_MAX_ALGOS ||
       sns_sam_algo_dbase[algoIndex] == NULL)
   {
      SNS_SAM_PRINTF0(ERROR, "sns_sam_process_algo_disable_req: Bad ptr");
      return SNS_ERR_BAD_PARM;
   }

   if (sns_sam_algo_inst_dbase[algoInstId]->clientReqCount == 1)
   {
      //disable algorithms on which this algorithm depends
      if( sns_sam_algo_dbase[algoIndex]->algoDepCount )
      {
         err = sns_sam_disable_dependent_algos(algoInstId,
                                               algoIndex);

         if (err != SNS_SUCCESS)
         {
            return err;
         }
      }
   }

   err = sns_sam_disable_algo(clientReqId);
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_client_req
  =========================================================================*/
/*!
  @brief Processes the client request for specified algorithm

  @param[i] clientReqMsgPtr: Pointer to client request message
  @param[i] mrClntId: Client ID
  @param[o] clientRespMsgPtr: Pointer to the response message created.

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_client_req(
   const void           *clientReqMsgPtr,
   sns_sam_mr_conn_hndl mrClntId,
   void                 **clientRespMsgPtr)
{
   uint8_t algoSvcId, algoIndex;
   uint8_t algoInstId = SNS_SAM_INVALID_ID;
   uint8_t clientReqId = SNS_SAM_INVALID_ID;
   sns_smr_header_s msgHdr;
   sns_err_code_e err = SNS_SUCCESS;
   *clientRespMsgPtr = NULL;

   sns_smr_get_hdr(&msgHdr, clientReqMsgPtr);

   clientReqId = sns_sam_find_client_req(&msgHdr, mrClntId);
   if (clientReqId < SNS_SAM_MAX_CLIENT_REQS)
   {
      if (msgHdr.msg_id == SNS_SAM_ALGO_ENABLE_REQ)
      {
         return SNS_ERR_NOTALLOWED;
      }

      algoInstId = sns_sam_client_req_dbase[clientReqId]->algoInstId;
   }
   else
   {
      if ((msgHdr.msg_id == SNS_SAM_ALGO_DISABLE_REQ) ||
          (msgHdr.msg_id == SNS_SAM_ALGO_GET_REPORT_REQ))
      {
         return SNS_ERR_NOTALLOWED;
      }
      if (msgHdr.msg_id == SNS_SAM_ALGO_CANCEL_REQ)
      {
         sns_common_cancel_resp_msg_v01* cancelRespMsgPtr =
            sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_common_cancel_resp_msg_v01));
         SNS_ASSERT(cancelRespMsgPtr != NULL);
         cancelRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
         cancelRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;

         sns_sam_prep_resp_msg(clientReqMsgPtr, cancelRespMsgPtr,
             sizeof(sns_common_cancel_resp_msg_v01));
         *clientRespMsgPtr = cancelRespMsgPtr;
         return SNS_SUCCESS;
      }
   }

   algoSvcId = msgHdr.svc_num;
   algoIndex = sns_sam_get_algo_index(algoSvcId);

   if (algoIndex >= SNS_SAM_MAX_ALGOS || sns_sam_algo_dbase[algoIndex] == NULL)
   {
      return SNS_ERR_BAD_PARM;
   }

   switch (msgHdr.msg_id)
   {
   case SNS_SAM_ALGO_ENABLE_REQ:
   {
      //check request parameters
      err = sns_sam_validate_client_req_parameter(msgHdr.msg_id,clientReqMsgPtr,algoSvcId);

      if ( (err != SNS_SUCCESS) && (err != SNS_ERR_NOTSUPPORTED) )
      {
         return err;
      }

      //enable algorithm
      err = sns_sam_process_algo_enable_req(clientReqMsgPtr, mrClntId, algoIndex, &msgHdr, &algoInstId);

      if (err != SNS_SUCCESS)
      {
         return err;
      }

      if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
          sns_sam_algo_inst_dbase[algoInstId] == NULL)
      {
         return SNS_ERR_FAILED;
      }

      err = sns_sam_prep_algo_enable_resp(algoInstId,
                                          sns_sam_algo_inst_dbase[algoInstId]->serviceId,
                                          clientReqMsgPtr,
                                          clientRespMsgPtr);
      break;
   }

   case SNS_SAM_ALGO_DISABLE_REQ:
   {
      //disable algorithm
      err = sns_sam_process_algo_disable_req(algoInstId, algoIndex, clientReqId);

      if (err == SNS_SUCCESS)
      {
         err = sns_sam_prep_algo_disable_resp(algoInstId,
                                              algoSvcId,
                                              clientReqMsgPtr,
                                              clientRespMsgPtr);
      }
      break;
   }

   case SNS_SAM_ALGO_GET_REPORT_REQ:
   {
      if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
          sns_sam_algo_inst_dbase[algoInstId] == NULL)
      {
         return SNS_ERR_FAILED;
      }

      err = sns_sam_send_algo_report_req(algoInstId,
                                         sns_sam_algo_inst_dbase[algoInstId],
                                         clientReqMsgPtr);
      if( err != SNS_SUCCESS )
      {
         return err;
      }

      sns_sam_refresh_algo_output( algoInstId, clientReqId );

      err = sns_sam_prep_algo_report_resp(sns_sam_client_req_dbase[clientReqId],
                                          clientReqMsgPtr,
                                          clientRespMsgPtr,
                                          algoSvcId);
      break;
   }

   case SNS_SAM_ALGO_CANCEL_REQ:
   {
      sns_common_cancel_resp_msg_v01 *cancelRespMsgPtr;

      err = sns_sam_process_algo_disable_req(algoInstId, algoIndex, clientReqId);

      if (err == SNS_SUCCESS)
      {
         cancelRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_common_cancel_resp_msg_v01));
         SNS_ASSERT(cancelRespMsgPtr != NULL);
         cancelRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
         cancelRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;

         sns_sam_prep_resp_msg(clientReqMsgPtr, cancelRespMsgPtr,
             sizeof(sns_common_cancel_resp_msg_v01));
         *clientRespMsgPtr = cancelRespMsgPtr;
      }
      break;
   }

   case SNS_SAM_ALGO_VERSION_REQ:
   {
      sns_common_version_resp_msg_v01 *versionRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_common_version_resp_msg_v01));
      SNS_ASSERT(versionRespMsgPtr != NULL);

      versionRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      versionRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;

      sns_sam_get_algo_version_resp(algoSvcId, versionRespMsgPtr);

      sns_sam_prep_resp_msg(clientReqMsgPtr, versionRespMsgPtr,
          sizeof(sns_common_version_resp_msg_v01));
      *clientRespMsgPtr = versionRespMsgPtr;
      break;
   }

   case SNS_SAM_ALGO_UPDATE_REQ:
   {
      //check request parameters
      err = sns_sam_validate_client_req_parameter(msgHdr.msg_id,clientReqMsgPtr,algoSvcId);

      if ( (err != SNS_SUCCESS) && (err != SNS_ERR_NOTSUPPORTED) )
      {
         return err;
      }

      if( algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
          sns_sam_algo_inst_dbase[algoInstId] == NULL )
      {
         return SNS_ERR_BAD_PARM;
      }

      err = sns_sam_process_algo_update_req( algoInstId,
          sns_sam_client_req_dbase[clientReqId]->mrClientId, clientReqMsgPtr );

      if( err != SNS_SUCCESS )
      {
         return err;
      }

      // send response to client
      err = sns_sam_prep_algo_update_resp( clientReqMsgPtr, clientRespMsgPtr, algoSvcId );
      break;
   }

   case SNS_SAM_ALGO_BATCH_REQ:
   {
      err = sns_sam_process_algo_batch_req( sns_sam_algo_dbase[algoIndex], clientReqId, clientReqMsgPtr );

      if( err != SNS_SUCCESS )
      {
         return err;
      }

      // send response to client
      err = sns_sam_prep_algo_batch_resp( clientReqMsgPtr, clientRespMsgPtr, sns_sam_algo_dbase[algoIndex] );
      break;
   }

   case SNS_SAM_ALGO_UPDATE_BATCH_PERIOD_REQ:
   {
      err = sns_sam_process_algo_upd_batch_period_req( algoSvcId, clientReqId, clientReqMsgPtr );

      if( err != SNS_SUCCESS )
      {
         return err;
      }

      // send response to client
      err = sns_sam_prep_algo_upd_batch_period_resp( clientReqMsgPtr, clientRespMsgPtr, algoSvcId );
      break;
   }

   case SNS_SAM_ALGO_GET_ATTRIB_REQ:
   {
      sns_sam_get_algo_attrib_resp_msg_v01 *attribRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_get_algo_attrib_resp_msg_v01));
      SNS_ASSERT(attribRespMsgPtr != NULL);

      attribRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      attribRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;

      sns_sam_get_algo_attrib_resp(sns_sam_algo_dbase[algoIndex], attribRespMsgPtr);

      sns_sam_prep_resp_msg(clientReqMsgPtr, attribRespMsgPtr,
          sizeof(sns_sam_get_algo_attrib_resp_msg_v01));
      *clientRespMsgPtr = attribRespMsgPtr;
      break;
   }

   default:
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROCESS_REQ_INVALID_REQ, msgHdr.msg_id);
      err = SNS_ERR_FAILED;
      break;
   }

   if( err == SNS_SUCCESS && *clientRespMsgPtr == NULL )
   {
      err = SNS_ERR_FAILED;
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_item
  =========================================================================*/
/*!
  @brief    Processes an item in SMGR indication message

  @param[i] indMsgType: indication message type
  @param[i] smgrIndPtr: pointer to SMGR indication message
  @param[i] timestamp:  timestamp of the first sensor sample
  @param[i] dataReqId:  index of data request entry in dbase
  @param[i] algoInstIds:  list of algo instances that need this item
  @param[i] algoInstCount:  number of algo instances in algoInstIds[]
  @param[i] sensorID: SMGR Sensor ID for the indication
                      (invalid unless indMsgType==SNS_SMGR_BUFFERING_IND_V01)

  @return   Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_item(
   uint8_t indMsgType,
   const void* smgrIndPtr,
   uint32_t timestamp,
   uint8_t dataReqId,
   uint8_t algoInstIds[SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ],
   uint8_t algoInstCount,
   uint8_t sensorID)
{
   uint8_t i;
   sns_err_code_e err;

   for (i = 0; i < algoInstCount; i++)
   {
      void *algoRptPtr;
      sns_sam_algo_inst_s *algoInstPtr;
      uint8_t algoIndex, j;
      uint8_t algoInstId = algoInstIds[i];

      algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];
      if (NULL == algoInstPtr)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, algoInstId);
         continue;
      }

      algoIndex = sns_sam_get_algo_index(algoInstPtr->serviceId);
      if (algoIndex >= SNS_SAM_MAX_ALGOS || sns_sam_algo_dbase[algoIndex] == NULL)
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_SMGR_IND_INVALID, algoIndex, algoInstPtr->serviceId);
         continue;
      }

#if defined(SNS_PLAYBACK_SKIP_SMGR) || defined(SNS_QDSP_SIM)
      {
         //before first report, update nextReportTime with timestamp from smgr
         uint32_t count_pb_clientReqId = 0;
         while (sns_sam_client_req_dbase[count_pb_clientReqId]!=NULL)
         {
            if (nextReportTimeEnable[count_pb_clientReqId] == 0)
            {
               nextReportTime[count_pb_clientReqId] += timestamp;
               nextReportTimeEnable[count_pb_clientReqId]=1; // 1: Enabled 0: Not Assigned
            }
            else
            {
               //check if it is time to report
               if (timestamp > nextReportTime[count_pb_clientReqId])
               {
                  // report to client
                  sns_sam_client_req_s* clientReqPtr =
                  sns_sam_client_req_dbase[count_pb_clientReqId];

                  sns_sam_timer_cb((void *)count_pb_clientReqId);

                  // update next report time
                  nextReportTime[count_pb_clientReqId] = clientReqPtr->period;
               }
            }
            count_pb_clientReqId++;
         }
      }
#endif

      // Updates inputs of algorithm
      err = sns_sam_update_algo_input(algoInstPtr->serviceId,
                                      indMsgType, smgrIndPtr,
                                      algoInstPtr->inputData.memPtr,
                                      algoInstPtr->inputData.memSize,
                                      timestamp,
                                      sensorID);
      if (err != SNS_SUCCESS)
      {
         for (j = 0; j < algoInstPtr->clientReqCount; j++)
         {
            uint8_t clientReqId = algoInstPtr->clientReqDbase[j];
            sns_sam_client_req_s* clientReqPtr =
               sns_sam_client_req_dbase[clientReqId];

            if( clientReqPtr != NULL &&
                clientReqPtr->algoInstId == algoInstId )
            {
               // notify corresponding clients of internal error
               sns_sam_send_error_ind(clientReqId,
                                      SNS_ERR_FAILED,
                                      clientReqPtr->mrClientId);
            }
         }
        continue;
      }

      //backup the algo report
      algoRptPtr = SNS_OS_MALLOC(SNS_SAM_DBG_MOD,algoInstPtr->outputData.memSize);
      SNS_ASSERT(algoRptPtr != NULL);
      SNS_OS_MEMCOPY(algoRptPtr,
                     algoInstPtr->outputData.memPtr,
                     algoInstPtr->outputData.memSize);

#ifdef SNS_DSPS_BUILD
      sns_profiling_log_timestamp((uint64_t) (((uint64_t)(((uint64_t)SNS_SAM_ALGO_EXEC_PROFILE_START)<<32)) |
                                                          ((uint64_t)(algoInstPtr->serviceId))));
#endif
      sns_profiling_log_qdss(SNS_SAM_ALGO_UPDATE_ENTER, 2, algoInstPtr->serviceId, algoInstId);
      //execute the algorithm
      sns_sam_algo_dbase[algoIndex]->algoApi.sns_sam_algo_update(
         algoInstPtr->stateData.memPtr,
         algoInstPtr->inputData.memPtr,
         algoInstPtr->outputData.memPtr);
      sns_profiling_log_qdss(SNS_SAM_ALGO_UPDATE_EXIT, 3, algoInstPtr->serviceId, algoInstId, 1);
#ifdef SNS_DSPS_BUILD
      sns_profiling_log_timestamp((uint64_t) (((uint64_t)(((uint64_t)SNS_SAM_ALGO_EXEC_PROFILE_END)<<32)) |
                                                          ((uint64_t)(algoInstPtr->serviceId))));
#endif

      sns_sam_check_config_update(algoInstPtr, algoInstId);

      //update algorithm report timestamp
      algoInstPtr->outputData.timestamp = timestamp;

      for (j = 0; j < SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST; j++)
      {
         if (algoInstPtr->clientReqDbase[j] < SNS_SAM_MAX_CLIENT_REQS)
         {
            uint8_t clientReqId = algoInstPtr->clientReqDbase[j];
            sns_sam_client_req_s* clientReqPtr =
               sns_sam_client_req_dbase[clientReqId];

            //send synchronous and asynchronous indications
            if (clientReqPtr != NULL)
            {
               sns_sam_update_algo_report_ts(algoInstPtr, clientReqPtr->mrClientId);
               if ((clientReqPtr->reportType == SNS_SAM_SYNC_REPORT) ||
                   ((clientReqPtr->reportType == SNS_SAM_ASYNC_REPORT) &&
                    (SNS_OS_MEMCMP(algoRptPtr,
                                   algoInstPtr->outputData.memPtr,
                                   algoInstPtr->outputData.memSize))))
               {
                  //process algorithm report indication to client
                  sns_sam_process_algo_report(clientReqId,
                                              &(algoInstPtr->outputData),
                                              clientReqPtr->mrClientId);

                  SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_IND_DELIVERY_SUCC,
                                 sns_sam_mr_get_client_id(clientReqPtr->mrClientId));
               }
            }
         }
      }
      if(sns_sam_get_smgr_msg_req_type(algoInstPtr->serviceId) ==
         SNS_SMGR_BUFFERING_REQ_V01)
      {
         sns_sam_update_input_type(algoInstPtr->serviceId, dataReqId, algoRptPtr,
                                  algoInstPtr->outputData.memPtr);
      }
      sns_sam_log_algo_result(algoInstId, algoInstPtr, SNS_SAM_INVALID_ID);

      SNS_OS_FREE(algoRptPtr);
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_report_resp
  =========================================================================*/
/*!
  @brief Processes the response received from sensors manager

  @param[i] smgrRespPtr: Pointer to sensors manager response message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_report_resp(
   const void *smgrRespPtr)
{
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   sns_sam_client_req_s* clientReqPtr;

   sns_smgr_periodic_report_resp_msg_v01* respPtr =
      (sns_smgr_periodic_report_resp_msg_v01*)smgrRespPtr;

   dataReqId = respPtr->ReportId;

   if (respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 ||
       respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_MODIFIED_V01)
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_SUCCESS, dataReqId);
      return SNS_SUCCESS;
   }

   if (dataReqId < SNS_SAM_MAX_DATA_REQS &&
       sns_sam_data_req_dbase[dataReqId] != NULL)
   {
      uint8_t i, j;
      for (i = 0; i < sns_sam_data_req_dbase[dataReqId]->algoInstCount; i++)
      {
         uint8_t algoInstId =
            sns_sam_data_req_dbase[dataReqId]->algoInstDbase[i];

         for (j = 0;
              j < sns_sam_algo_inst_dbase[algoInstId]->clientReqCount;
              j++)
         {
            uint8_t clientReqId =
               sns_sam_algo_inst_dbase[algoInstId]->clientReqDbase[j];

            if (sns_sam_client_req_dbase[clientReqId] != NULL &&
                sns_sam_client_req_dbase[clientReqId]->algoInstId ==
                algoInstId)
            {
               clientReqPtr = sns_sam_client_req_dbase[clientReqId];
               // notify corresponding clients of internal error
               sns_sam_send_error_ind(clientReqId,
                                      SNS_ERR_FAILED,
                                      clientReqPtr->mrClientId);
            }
         }
      }
   }
   else
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_DROPPED, dataReqId);
   }

   SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_RESP_ACK_VAL,
                  respPtr->AckNak, respPtr->ReasonPair_len);

   if (respPtr->ReasonPair_len < SNS_SMGR_MAX_NUM_REASONS_V01)
   {
      uint32_t i;
      for (i = 0; i < respPtr->ReasonPair_len; i++)
      {
         SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_RESP_RESPINFO,
                        respPtr->ReasonPair[i].ItemNum,
                        respPtr->ReasonPair[i].Reason);
      }
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_report_ind
  =========================================================================*/
/*!
  @brief Processes the indication received from sensors manager

  @param[i] smgrIndPtr: Pointer to sensors manager indication message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_report_ind(
   const void *smgrIndPtr)
{
   sns_smgr_periodic_report_ind_msg_v01* indPtr;
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   uint32_t i, j;
   sns_err_code_e err = SNS_SUCCESS;
   uint8_t algoInstIds[SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ];
   uint8_t algoInstCount = 0;
   sns_sam_data_req_s* dataReqPtr = NULL;
   bool foundType = false;

   indPtr = (sns_smgr_periodic_report_ind_msg_v01*)smgrIndPtr;
   dataReqId = indPtr->ReportId;

   if (dataReqId >= SNS_SAM_MAX_DATA_REQS ||
       sns_sam_data_req_dbase[dataReqId] == NULL)
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SNS_ERR_FAILED;
   }

   if (indPtr->status != SNS_SMGR_REPORT_OK_V01)
   {
      SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_IND_STATUS,
                     dataReqId, indPtr->status);
      return SNS_ERR_FAILED;
   }

   dataReqPtr = sns_sam_data_req_dbase[dataReqId];
   if (indPtr->CurrentRate != dataReqPtr->reportRate)
   {
      SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_IND_STATUS,
                     dataReqId, indPtr->CurrentRate);
   }

   //Initialize instance ids for algorithms using this indication
   for( i = 0; i < dataReqPtr->algoInstCount; i++ )
   {
      algoInstIds[algoInstCount++] = dataReqPtr->algoInstDbase[i];
   }

   //Check for indication matching request
   for( i = 0; !foundType && i < indPtr->Item_len; i++ )
   {
      // Check if report has at least one of the types that was requested
      for( j = 0; !foundType && j < dataReqPtr->sensorCount; j++ )
      {
         if( dataReqPtr->sensorDbase[j].sensorId == indPtr->Item[i].SensorId &&
             dataReqPtr->sensorDbase[j].dataType == indPtr->Item[i].DataType )
         {
            foundType = true;
         }
      }
   }

   // If report does not have any type that was requested, bail
   if( !foundType )
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SNS_ERR_FAILED;
   }

   //Validate sensor data and process valid data only
   for (i = 0; i < indPtr->Item_len; i++)
   {
      if (indPtr->Item[i].ItemFlags == SNS_SMGR_ITEM_FLAG_INVALID_V01 ||
          indPtr->Item[i].ItemQuality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_FAILED_SENSOR_V01 ||
          indPtr->Item[i].ItemQuality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01 ||
          indPtr->Item[i].ItemQuality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_SUSPENDED_V01)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      }
      else
      {
         //execute algorithms waiting for this sensor data
         err = sns_sam_process_smgr_item(SNS_SMGR_REPORT_IND_V01,
                                         &(indPtr->Item[i]),
                                         indPtr->Item[i].TimeStamp, dataReqId,
                                         algoInstIds, algoInstCount, -1);
      }
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_find_max_sample_rate
  =========================================================================*/
/*!
  @brief Finds max sample rate in a data request

  @param[i] dataReqId: Index of data request in data request database

  @return sample rate in Hz (Q16 format)
*/
/*=======================================================================*/
int32_t sns_sam_find_max_sample_rate(
   const uint8_t dataReqId)
{
   int32_t maxSampleRate = 0;

   if( dataReqId < SNS_SAM_MAX_DATA_REQS &&
       sns_sam_data_req_dbase[dataReqId] != NULL )
   {
      int32_t i;
      for( i = 0; i < sns_sam_data_req_dbase[dataReqId]->sensorCount; i++ )
      {
         if( sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sampleRate >
             maxSampleRate )
         {
            maxSampleRate =
               sns_sam_data_req_dbase[dataReqId]->sensorDbase[i].sampleRate;
         }
      }
   }
   return FX_CONV_Q16(maxSampleRate,0);
}

/*=========================================================================
  FUNCTION:  sns_sam_switch_smgr_data_req
  =========================================================================*/
/*!
  @brief Switch from buffering to periodic data requests to SMGR

  @param[i] dataReqId: Index of data request in data request database

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_switch_smgr_data_req(
   const uint8_t dataReqId)
{
   sns_err_code_e err = SNS_ERR_FAILED;
   if( dataReqId < SNS_SAM_MAX_DATA_REQS &&
       sns_sam_data_req_dbase[dataReqId] != NULL &&
       sns_sam_data_req_dbase[dataReqId]->algoInstCount > 0 )
   {
      uint8_t algoInstId, svcId = 0;

      sns_sam_data_req_dbase[dataReqId]->reportRate =
          sns_sam_find_max_sample_rate(dataReqId);

      // Find one service associated with this data request
      algoInstId = sns_sam_data_req_dbase[dataReqId]->algoInstDbase[0];
      if( algoInstId < SNS_SAM_MAX_ALGO_INSTS &&
          sns_sam_algo_inst_dbase[algoInstId] != NULL )
      {
         svcId = sns_sam_algo_inst_dbase[algoInstId]->serviceId;

         // Send request to switch to new message type
         err = sns_sam_send_smgr_start_req( dataReqId, svcId );
      }
   }
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_buffering_resp
  =========================================================================*/
/*!
  @brief Processes the buffering response received from sensors manager

  @param[i] smgrRespPtr: Pointer to sensors manager response message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_buffering_resp(
   const void *smgrRespPtr)
{
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   sns_sam_client_req_s* clientReqPtr;

   sns_smgr_buffering_resp_msg_v01* respPtr =
      (sns_smgr_buffering_resp_msg_v01*) smgrRespPtr;

   if (respPtr->ReportId_valid)
   {
      dataReqId = respPtr->ReportId;
   }

   if( respPtr->Resp.sns_result_t != SNS_RESULT_SUCCESS_V01 &&
       respPtr->Resp.sns_err_t != SENSOR1_SUCCESS )
   {
     if( respPtr->Resp.sns_err_t == SENSOR1_EBAD_MSG_ID )
     {
        sns_sam_smgr_buffering_flag = false;
        if( sns_sam_switch_smgr_data_req( dataReqId ) == SNS_SUCCESS )
        {
           // Retrying with periodic data request
           return SNS_ERR_WOULDBLOCK;
        }
     }
     else if( respPtr->AckNak_valid &&
              respPtr->AckNak == SNS_SMGR_RESPONSE_NAK_REPORT_RATE_V01 )
     {
        if( sns_sam_switch_smgr_data_req( dataReqId ) == SNS_SUCCESS )
        {
           // Retrying with periodic data request
           return SNS_ERR_WOULDBLOCK;
        }
     }
   }

   if (respPtr->AckNak_valid &&
       (respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 ||
        respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_MODIFIED_V01))
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_SUCCESS, dataReqId);
      return SNS_SUCCESS;
   }

   if (dataReqId < SNS_SAM_MAX_DATA_REQS &&
       sns_sam_data_req_dbase[dataReqId] != NULL)
   {
      uint8_t i, j;
      for (i = 0; i < sns_sam_data_req_dbase[dataReqId]->algoInstCount; i++)
      {
         uint8_t algoInstId =
            sns_sam_data_req_dbase[dataReqId]->algoInstDbase[i];

         if (algoInstId >= SNS_SAM_MAX_ALGO_INSTS ||
             sns_sam_algo_inst_dbase[algoInstId]== NULL)
         {
            SNS_SAM_PRINTF2(ERROR,"SAM: Bad algoInstId %d in dataReqId %d", algoInstId, dataReqId);
            break;
         }

         for (j = 0;
              j < sns_sam_algo_inst_dbase[algoInstId]->clientReqCount;
              j++)
         {
            uint8_t clientReqId =
               sns_sam_algo_inst_dbase[algoInstId]->clientReqDbase[j];

            if (sns_sam_client_req_dbase[clientReqId] != NULL &&
                sns_sam_client_req_dbase[clientReqId]->algoInstId ==
                algoInstId)
            {
               clientReqPtr = sns_sam_client_req_dbase[clientReqId];
               // notify corresponding clients of internal error
               sns_sam_send_error_ind(clientReqId,
                                      SNS_ERR_FAILED,
                                      clientReqPtr->mrClientId);
            }
         }
      }
   }
   else
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_DROPPED, dataReqId);
   }

   SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_RESP_ACK_VAL,
                  respPtr->AckNak, respPtr->ReasonPair_len);

   if (respPtr->ReasonPair_valid &&
       (respPtr->ReasonPair_len < SNS_SMGR_MAX_NUM_REASONS_V01))
   {
      uint32_t i;
      for (i = 0; i < respPtr->ReasonPair_len; i++)
      {
         SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_RESP_RESPINFO,
                        respPtr->ReasonPair[i].ItemNum,
                        respPtr->ReasonPair[i].Reason);
      }
   }

   return SNS_ERR_FAILED;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_inst_in_data_req
  =========================================================================*/
/*!
  @brief    Gets the list of algorithm instances that requested for a
            particular sensor id

  @param[i] dataReqPtr: pointer to data request
  @param[i] sensorId:  sensor id
  @param[o] algoInstIds:  array of algorithm instance ids

  @return   number of algorithm instances in output array
*/
/*=======================================================================*/
static int32_t sns_sam_get_algo_inst_in_data_req(
   sns_sam_data_req_s* dataReqPtr,
   uint8_t sensorId,
   uint8_t algoInstIds[])
{
   int32_t j, k, algoInstCount = 0;

   if( dataReqPtr == NULL ||
       sensorId == SNS_SAM_INVALID_ID )
   {
      return 0;
   }

   for( j = 0; j < dataReqPtr->sensorCount; j++ )
   {
      if( dataReqPtr->sensorDbase[j].sensorId == sensorId )
      {
         for( k = 0; k < dataReqPtr->sensorDbase[j].algoInstCount; k++ )
         {
            algoInstIds[algoInstCount++] = dataReqPtr->sensorDbase[j].algoInstIds[k];
         }
         break;
      }
   }

   return algoInstCount;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_buffer
  =========================================================================*/
/*!
  @brief Processes samples in the buffering indication received from SMGR

  @param[i] indPtr: Pointer to buffering indication message
  @param[i] dataReqId: Index of entry in data request database

  @return None
*/
/*=======================================================================*/
static void sns_sam_process_smgr_buffer(
   sns_smgr_buffering_ind_msg_v01 *indPtr,
   uint8_t dataReqId)
{
   uint32_t i;
   sns_smgr_buffering_sample_s_v01 * samplePtr[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01];
   uint32_t sampleCount[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01];
   uint32_t timestamp[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01];
   uint32_t samplesProcessed = 0;
   uint8_t algoInstIds[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01][SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ];
   uint8_t algoInstCount[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01];

   SNS_OS_MEMSET( samplePtr, 0, sizeof(samplePtr) );
   SNS_OS_MEMSET( sampleCount, 0, sizeof(sampleCount) );
   SNS_OS_MEMSET( timestamp, 0, sizeof(timestamp) );
   SNS_OS_MEMSET( algoInstIds, 0, sizeof(algoInstIds) );
   SNS_OS_MEMSET( algoInstCount, 0, sizeof(algoInstCount) );

   for (i = 0; i < indPtr->Indices_len; i++)
   {
      uint8_t firstSampleIndex = indPtr->Indices[i].FirstSampleIdx;
      samplePtr[i] = &indPtr->Samples[firstSampleIndex];
      sampleCount[i] = indPtr->Indices[i].SampleCount;
      timestamp[i] = indPtr->Indices[i].FirstSampleTimestamp;
      // Find algo instances that need this sensor type
      algoInstCount[i] = sns_sam_get_algo_inst_in_data_req(sns_sam_data_req_dbase[dataReqId],
                                                           indPtr->Indices[i].SensorId,
                                                           algoInstIds[i]);
   }

   while( samplesProcessed < indPtr->Samples_len )
   {
      uint32_t minTimestamp = 0;
      uint32_t oldestSampleIdx = 0;
      sns_smgr_buffering_sample_s_v01 * oldestSamplePtr = NULL;

      samplesProcessed++;
      for (i = 0; i < indPtr->Indices_len; i++)
      {
         // Find first valid sample to initialize min timestamp
         if( samplePtr[i] != NULL )
         {
            minTimestamp = timestamp[i];
            oldestSampleIdx = i;
            break;
         }
      }

      for (i = oldestSampleIdx + 1; i < indPtr->Indices_len; i++)
      {
         // Find first minimum based on timestamp
         if( samplePtr[i] != NULL &&
             ((timestamp[i] < minTimestamp && (minTimestamp - timestamp[i] < UINT32_MAX / 2)) ||
              (timestamp[i] > minTimestamp && (timestamp[i] - minTimestamp > UINT32_MAX / 2)) ))
         {
            minTimestamp = timestamp[i];
            oldestSampleIdx = i;
         }
      }

      oldestSamplePtr = samplePtr[oldestSampleIdx];
      if( !oldestSamplePtr )
      {
         SNS_SAM_PRINTF1( ERROR, "SAM bad sample ptr for index %d", oldestSampleIdx );
         return;
      }

      if( sampleCount[oldestSampleIdx] > 1 )
      {
         samplePtr[oldestSampleIdx]++;
         timestamp[oldestSampleIdx] += (samplePtr[oldestSampleIdx]->TimeStampOffset);
         sampleCount[oldestSampleIdx]--;
      }
      else
      {
         samplePtr[oldestSampleIdx] =  NULL;
         timestamp[oldestSampleIdx] = UINT32_MAX;
      }

      if (oldestSamplePtr->Flags == SNS_SMGR_ITEM_FLAG_INVALID_V01 ||
          oldestSamplePtr->Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_FAILED_SENSOR_V01 ||
          oldestSamplePtr->Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01 ||
          oldestSamplePtr->Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_SUSPENDED_V01)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, oldestSampleIdx);
         continue;
      }

      //execute algorithms waiting for this sensor data
      sns_sam_process_smgr_item( SNS_SMGR_BUFFERING_IND_V01, oldestSamplePtr,
                                 minTimestamp, dataReqId,
                                 algoInstIds[oldestSampleIdx],
                                 algoInstCount[oldestSampleIdx],
                                 indPtr->Indices[oldestSampleIdx].SensorId );
   }
   SNS_SAM_PRINTF1( LOW, "SAM processed %d samples from buffering indication", samplesProcessed );
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_buffering_ind
  =========================================================================*/
/*!
  @brief Processes the buffering indication received from sensor manager

  @param[i] smgrIndPtr: Pointer to sensors manager indication message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_buffering_ind(
   const void *smgrIndPtr)
{
   sns_smgr_buffering_ind_msg_v01* indPtr;
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   sns_sam_data_req_s * dataReqPtr = NULL;
   uint32_t i, j;
   bool foundType = false;

   indPtr = (sns_smgr_buffering_ind_msg_v01*)smgrIndPtr;
   dataReqId = indPtr->ReportId;
   if (dataReqId >= SNS_SAM_MAX_DATA_REQS ||
       sns_sam_data_req_dbase[dataReqId] == NULL)
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SNS_ERR_FAILED;
   }

   if( indPtr->Indices_len == 0 || indPtr->Samples_len == 0 )
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SNS_ERR_FAILED;
   }

   SNS_SAM_PRINTF3( LOW, "SAM: Rxd buffering ind with %d samples and %d types for dataReqId %d",
       indPtr->Samples_len, indPtr->Indices_len, dataReqId );

   sns_profiling_log_qdss(SNS_SAM_PROCESS_IND_ENTER,1,dataReqId);
   //Validate sensor data
   dataReqPtr = sns_sam_data_req_dbase[dataReqId];
   for( i = 0; !foundType && i < indPtr->Indices_len; i++ )
   {
      // Check if report has at least one of the types that was requested
      for( j = 0; !foundType && j < dataReqPtr->sensorCount; j++ )
      {
         if( dataReqPtr->sensorDbase[j].sensorId == indPtr->Indices[i].SensorId &&
             dataReqPtr->sensorDbase[j].dataType == indPtr->Indices[i].DataType )
         {
            foundType = true;
         }
      }
   }
   // If report does not have any type that was requested, bail
   if( !foundType )
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      sns_profiling_log_qdss(SNS_SAM_PROCESS_IND_END,1,SNS_SAM_INVALID_ID); //Enter invalid ID as input to indicate error happens
      return SNS_ERR_FAILED;
   }

   //execute algorithms waiting for this sensor data
   sns_sam_process_smgr_buffer( indPtr, dataReqId);
   sns_profiling_log_qdss(SNS_SAM_PROCESS_IND_END,1, dataReqId);
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_buffering_query_resp
  =========================================================================*/
/*!
  @brief Processes the response received from sensors manager

  @param[i] smgrRespPtr: Pointer to sensors manager response message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_buffering_query_resp(
   const void *smgrRespPtr)
{
   sns_smgr_buffering_query_resp_msg_v01* respPtr =
      (sns_smgr_buffering_query_resp_msg_v01*) smgrRespPtr;

   /* SMGR request was successful. No further action required */
   if (respPtr->AckNak_valid && respPtr->QueryId_valid &&
      (respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 ||
       respPtr->AckNak == SNS_SMGR_RESPONSE_ACK_MODIFIED_V01))
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_SUCCESS,
                     (respPtr->QueryId & 0x00FF));
   }
   else
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_SMGR_RESP_DROPPED,
                     (respPtr->QueryId & 0x00FF));
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_buffering_query_ind
  =========================================================================*/
/*!
  @brief Processes the indication received from sensors manager

  @param[i] smgrIndPtr: Pointer to sensors manager indication message

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_smgr_buffering_query_ind(
   const void *smgrIndPtr)
{
   sns_err_code_e err;
   uint32_t i;
   uint8_t dataReqId;
   uint8_t algoInstIds[SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ];
   uint8_t algoInstCount = 0;

   sns_smgr_buffering_query_ind_msg_v01 *indPtr =
      (sns_smgr_buffering_query_ind_msg_v01*) smgrIndPtr;

   dataReqId = (uint8_t) (indPtr->QueryId & 0x00FF);

   if (dataReqId >= SNS_SAM_MAX_DATA_REQS ||
       sns_sam_data_req_dbase[dataReqId] == NULL)
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SNS_ERR_FAILED;
   }

   for (i = 0; i < indPtr->Samples_len; i++)
   {
      if (indPtr->Samples[i].Flags == SNS_SMGR_ITEM_FLAG_INVALID_V01 ||
          indPtr->Samples[i].Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_FAILED_SENSOR_V01 ||
          indPtr->Samples[i].Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01 ||
          indPtr->Samples[i].Quality ==
          SNS_SMGR_ITEM_QUALITY_INVALID_SUSPENDED_V01)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
         return SNS_ERR_FAILED;
      }
   }

   for( i = 0; i < sns_sam_data_req_dbase[dataReqId]->algoInstCount; i++ )
   {
      algoInstIds[algoInstCount++] = sns_sam_data_req_dbase[dataReqId]->algoInstDbase[i];
   }

   //execute algorithms waiting for this sensor data
   err = sns_sam_process_smgr_item(SNS_SMGR_BUFFERING_QUERY_IND_V01, smgrIndPtr,
                                   indPtr->FirstSampleTimestamp, dataReqId,
                                   algoInstIds, algoInstCount, -1 );

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_time_resp
  =========================================================================*/
/*!
  @brief Processes response from time service

  @param[i] : timeRespMsgPtr    pointer to message from Time Service

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_time_resp(
   const void *timeRespMsgPtr)
{
   sns_smr_header_s msgHdr;
   sns_err_code_e   err = SNS_SUCCESS;

   sns_smr_get_hdr(&msgHdr, timeRespMsgPtr);
   err = sns_sam_process_time_response(timeRespMsgPtr, &msgHdr);

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_msg
  =========================================================================*/
/*!
  @brief Process the messages from SAM's input message queue

  @return Sensors error code
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_process_msg(void)
{
   void *msgPtr;
   sns_smr_header_s msgHdr;
   sns_err_code_e err;

   while ((msgPtr = sns_sam_mr_msg_rcv()) != NULL)
   {
      err = sns_smr_get_hdr(&msgHdr, msgPtr);
      if (err != SNS_SUCCESS)
      {
         SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROC_MSG_HDR_ERR, err);
         sns_smr_msg_free(msgPtr);
         continue;
      }

      switch (msgHdr.src_module)
      {
         case SNS_MODULE_DSPS_SMGR:
         {
            if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
            {
               if (msgHdr.msg_id == SNS_SMGR_REPORT_RESP_V01)
               {
                  err = sns_sam_process_smgr_report_resp(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_REG_HW_MD_INT_RESP_V01)
               {
                  sns_sam_process_smgr_mot_int_resp(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_BUFFERING_RESP_V01)
               {
                  err = sns_sam_process_smgr_buffering_resp(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_BUFFERING_QUERY_RESP_V01)
               {
                  err = sns_sam_process_smgr_buffering_query_resp(msgPtr);
               }
               else
               {
                  SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_MSGID,
                                 msgHdr.msg_id);
               }
            }
            else if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_IND)
            {
               if (msgHdr.msg_id == SNS_SMGR_REPORT_IND_V01)
               {
                  err = sns_sam_process_smgr_report_ind(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_BUFFERING_IND_V01)
               {
                  err = sns_sam_process_smgr_buffering_ind(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_BUFFERING_QUERY_IND_V01)
               {
                  err = sns_sam_process_smgr_buffering_query_ind(msgPtr);
               }
               else if (msgHdr.msg_id == SNS_SMGR_REG_HW_MD_INT_IND_V01)
               {
                  sns_sam_process_smgr_mot_int_ind(msgPtr);
               }
               else
               {
                  SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_MSGID,
                                 msgHdr.msg_id);
               }
            }
            break;
         }

         case SNS_MODULE_DSPS_SAM:
         case SNS_MODULE_APPS_SAM:
         {
            if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
            {
               err = sns_sam_process_sam_resp(msgPtr);
            }
            else if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_IND)
            {
               err = sns_sam_process_sam_ind(msgPtr);
            }
            break;
         }

         case SNS_MODULE_APPS_TIME:
         {
            if (msgHdr.msg_type == SNS_SMR_MSG_TYPE_RESP)
            {
               err = sns_sam_process_time_resp(msgPtr);
            }
            break;
         }

         case SNS_MODULE_DSPS_PM:
         {
            SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_PROCESS_MSG_RCVD_MSG,
                           msgHdr.msg_id, msgHdr.src_module, msgHdr.svc_num);
            SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_PROCESS_MSG_STATUS,
                           msgHdr.msg_type, err);
            break;
         }

         default:
         {
            SNS_SAM_DEBUG3(MEDIUM, DBG_SAM_MSG_DROP,
                           msgHdr.msg_id, msgHdr.src_module, msgHdr.svc_num);
            break;
         }
      }

      sns_smr_msg_free(msgPtr);
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_reg_algo_svc
  =========================================================================*/
/*!
  @brief Register the algorithm with SAM. This is expected to be done
         at SAM initialization for all algorithms to be handled by SAM

  @param[i] algoSvcId: Algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_algo_svc(
   uint8_t algoSvcId)
{
   uint8_t i;
   sns_err_code_e err = SNS_ERR_FAILED;

   //check if algorithm already registered
   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->serviceId == algoSvcId)
      {
         SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_REG_ALGO_SUCCESS,
                        algoSvcId);
         return SNS_SUCCESS;
      }
   }

   //register algorithm
   if (i < SNS_SAM_MAX_ALGOS)
   {
      uint8_t algoIndex = i;

      sns_sam_algo_dbase[algoIndex] = SNS_OS_MALLOC(SNS_SAM_DBG_MOD, sizeof(sns_sam_algo_s));
      SNS_ASSERT(sns_sam_algo_dbase[algoIndex] != NULL);

      sns_sam_algo_dbase[algoIndex]->serviceId = algoSvcId;

      sns_sam_algo_dbase[algoIndex]->algoDepCount = 0;
      for (i = 0; i < SNS_SAM_MAX_ALGO_DEPS; i++)
      {
         sns_sam_algo_dbase[algoIndex]->algoDepDbase[i] = SNS_SAM_INVALID_ID;
      }
      sns_sam_algo_dbase[algoIndex]->regItemType = SNS_SAM_REG_ITEM_TYPE_NONE;
      sns_sam_algo_dbase[algoIndex]->defSensorReportRate = 0;
      sns_sam_algo_dbase[algoIndex]->dataSyncRequired = false;

      err = sns_sam_reg_algo(sns_sam_algo_dbase[algoIndex], sns_sam_sensor_uuids);
      if( sns_sam_algo_dbase[algoIndex]->regItemType != SNS_SAM_REG_ITEM_TYPE_NONE )
      {
         sns_sam_last_algo_with_registry_dep = algoSvcId;
      }
#ifndef  SNS_DSPS_BUILD
      if( err != SNS_SUCCESS )
      {
         SNS_OS_FREE( sns_sam_algo_dbase[algoIndex] );
         sns_sam_algo_dbase[algoIndex] = NULL;
      }
#endif
   }

   if (err == SNS_SUCCESS)
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_REG_ALGO_SUCCESS,
                     algoSvcId);
   }
   else
   {
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_REG_ALGO_ERR, algoSvcId);
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_events
  =========================================================================*/
/*!
  @brief Wait for events and process signaled events.

  @return None
*/
/*=======================================================================*/
static void sns_sam_process_events(void)
{
   uint8_t err;
   OS_FLAGS sigFlags;

   sns_profiling_log_qdss(SNS_SAM_EXIT, 0);
   //wait for event
   sigFlags = sns_os_sigs_pend(sns_sam_sig_event,
                               sam_sig_mask,
                               OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                               0,
                               &err);
   SNS_ASSERT(err == 0);
   sns_profiling_log_qdss(SNS_SAM_ENTER, 1, sigFlags);

   // AP state check
   if( sigFlags & SNS_SAM_AP_AWAKE_SIG )
   {
      sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].suspendState = false;
      sns_sam_handle_client_proc_wakeup( SNS_PROC_APPS_V01 );
      sigFlags &= (~SNS_SAM_AP_AWAKE_SIG);
   }
   if( sigFlags & SNS_SAM_AP_SUSPEND_SIG )
   {
      sns_sam_client_proc_dbase[SNS_PROC_APPS_V01].suspendState = true;
      sigFlags &= (~SNS_SAM_AP_SUSPEND_SIG);
   }

   //message event check
   if (sigFlags & SNS_SAM_MSG_SIG)
   {
      sns_sam_process_msg();
      sigFlags &= (~SNS_SAM_MSG_SIG);
   }
   //client report timer event check
   if (sigFlags & SNS_SAM_REPORT_TIMER_SIG)
   {
      sns_sam_handle_report_timeout();
      sigFlags &= (~SNS_SAM_REPORT_TIMER_SIG);
   }
   //initiate qmi client and get modem info
   if (sigFlags & SNS_SAM_MODEM_INFO_SIG)
   {
      sns_sam_get_modem_info_delayed();
      sigFlags &= (~SNS_SAM_MODEM_INFO_SIG);
   }

   sns_sam_mr_handle_event( &sigFlags );
   if (sigFlags != 0)
   {
      SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_PROCESS_EVT_UNKWN_EVT, sigFlags);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_config_algos
  =========================================================================*/
/*!
  @brief Configure algorithms

  @detail
  All algorithms are executed in this task context.
  Waits on events primarily from sensors manager or client.

  @param[i] argPtr: pointer to task argument

  @return None
*/
/*=======================================================================*/
static void sns_sam_config_algos(void)
{
   uint8_t i;
   sns_err_code_e err = SNS_SUCCESS;

   // Request for AMD group registry items
   // AMD config paras are applied to all algos implementing
   // the absolute rest detector.
   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->serviceId == SNS_SAM_AMD_SVC_ID_V01)
      {
         err = sns_sam_req_reg_data(SNS_SAM_REG_ITEM_TYPE_GROUP,
                                    SNS_REG_SAM_GROUP_AMD_V02);

         if (SNS_SUCCESS == err)
         {
            sns_sam_get_registry_read_resp(SNS_SAM_REG_READ_TIMER_LOW_PERIOD_USEC);
         }
         else
         {
            SNS_SAM_DEBUG1(HIGH, DBG_SAM_REG_REQ_FAIL, err);
         }
      }
   }

   // Request for Gyro AMD group registry items
   // Gyro AMD config paras are applied to all algos implementing
   // the gyro based absolute rest detector.
   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->serviceId == SNS_SAM_FILTERED_MAG_SVC_ID_V01)
      {
         err = sns_sam_req_reg_data(SNS_SAM_REG_ITEM_TYPE_GROUP,
                                 SNS_REG_SAM_GROUP_GYRO_AMD_V02);

         if (SNS_SUCCESS == err)
         {
            sns_sam_get_registry_read_resp(SNS_SAM_REG_READ_TIMER_LOW_PERIOD_USEC);
         }
         else
         {
            SNS_SAM_DEBUG1(HIGH, DBG_SAM_REG_REQ_FAIL, err);
         }
      }
   }

   for (i = 0;
        i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if (sns_sam_algo_dbase[i]->regItemType != SNS_SAM_REG_ITEM_TYPE_NONE)
      {
         uint32_t timeout = SNS_SAM_REG_READ_TIMER_LOW_PERIOD_USEC;
         if( sns_sam_last_algo_with_registry_dep == sns_sam_algo_dbase[i]->serviceId )
         {
            timeout = SNS_SAM_REG_READ_TIMER_HIGH_PERIOD_USEC;
         }

         err = sns_sam_req_reg_data(sns_sam_algo_dbase[i]->regItemType,
                                    sns_sam_algo_dbase[i]->regItemId);

         if (SNS_SUCCESS == err)
         {
            sns_sam_get_registry_read_resp(timeout);
         }
         else
         {
            /* Could not send request message. Use default cal. Already set for
               default at start of init process */
            SNS_SAM_DEBUG1(HIGH, DBG_SAM_REG_REQ_FAIL, err);
         }
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_init_time_state
  =========================================================================*/
void sns_sam_init_time_state(void)
{
  /* Resets time service parameters */
  sns_sam_time_state.ts_offset  = 0;
  sns_sam_time_state.ts_cnt     = 0;
  sns_sam_time_state.ts_offset_valid = false;

  /* Resets DSPS clock rollver parameters */
  /* Note: this is a temporary solution. MUST use the solution from Time
     Service eventually, because ts_dsps_ro_cnt is reset when SAM reset is
     called (that doesn't necessarily mean DSPS core was reset).
   */
  sns_sam_time_state.ts_dsps_prev   = 0;
  sns_sam_time_state.ts_dsps_ro_cnt = 0;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_mag_cal_module_support
  =========================================================================*/
/*!
  @brief Query for the module on which mag cal is supported

  @param[i] None

  @return None
*/
/*=======================================================================*/
static void sns_sam_get_mag_cal_module_support(void)
{
   sns_err_code_e err = SNS_SUCCESS;

   // QMag Cal Algo enable registry bit is used to determine whether Mag Cal is supported 
   // on ADSP or Apps.

   err = sns_sam_req_reg_data(SNS_SAM_REG_ITEM_TYPE_GROUP,
                              SNS_REG_SCM_GROUP_QMAG_CAL_ALGO_V02);

   if (SNS_SUCCESS == err)
   {
      sns_sam_get_registry_read_resp(SNS_SAM_REG_READ_TIMER_HIGH_PERIOD_USEC);
   }
   else
   {
      SNS_SAM_DEBUG1(HIGH, DBG_SAM_REG_REQ_FAIL, err);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_mr_reg_algos
  =========================================================================*/
/*!
  @brief Registers all supported algorithms with QCSI

  @param[i] None

  @return None
*/
/*=======================================================================*/
static void sns_sam_mr_reg_algos(void)
{
   uint8_t i;

   // Register supported algorithms with QCSI
   for (i = 0; i < SNS_SAM_MAX_ALGOS && sns_sam_algo_dbase[i] != NULL; i++)
   {
      if( SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01 != sns_sam_algo_dbase[i]->serviceId &&
          SNS_SAM_QUATERNION_SVC_ID_V01 != sns_sam_algo_dbase[i]->serviceId &&
          SNS_SAM_ROTATION_VECTOR_SVC_ID_V01 != sns_sam_algo_dbase[i]->serviceId &&
          SNS_SAM_FILTERED_MAG_SVC_ID_V01 != sns_sam_algo_dbase[i]->serviceId
          //SNS_SAM_ORIENTATION_SVC_ID_V01 != sns_sam_algo_dbase[i]->serviceId
        )
      {
        sns_sam_mr_qcsi_reg(sns_sam_algo_dbase[i]->serviceId);
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_task
  =========================================================================*/
/*!
  @brief Sensors algorithm manager task

  @detail
  All algorithms are executed in this task context.
  Waits on events primarily from sensors manager or client.

  @param[i] argPtr: pointer to task argument

  @return None
*/
/*=======================================================================*/
static void sns_sam_task(
   void *argPtr)
{
   uint8_t i;
   //uint32_t numModemContexts;
   //uint8_t modemContexts[32];
   bool gotSensorInfo = false;

   UNREFERENCED_PARAMETER(argPtr);

   sns_sam_init_time_state();

   SNS_OS_MEMSET( sns_sam_sensor_uuids, 0, sizeof(sns_sam_sensor_uuids) );
   SNS_OS_MEMSET( sns_sam_client_proc_dbase, 0, sizeof(sns_sam_client_proc_dbase) );
   SNS_OS_MEMSET( sns_sam_sensor_info_dbase, 0, sizeof(sns_sam_sensor_info_dbase) );

   //initialize algorithm database
   for (i = 0; i < SNS_SAM_MAX_ALGOS; i++)
   {
      sns_sam_algo_dbase[i] = NULL;
   }

   //initialize algorithm instance database
   for (i = 0; i < SNS_SAM_MAX_ALGO_INSTS; i++)
   {
      sns_sam_algo_inst_dbase[i] = NULL;
   }
   sns_sam_algo_inst_count = 0;

   //initialize client request database
   for (i = 0; i < SNS_SAM_MAX_CLIENT_REQS; i++)
   {
      sns_sam_client_req_dbase[i] = NULL;
   }
   sns_sam_client_req_count = 0;

   //initialize sensor data request database
   for (i = 0; i < SNS_SAM_MAX_DATA_REQS; i++)
   {
      sns_sam_data_req_dbase[i] = NULL;
   }
   sns_sam_data_req_count = 0;

   sam_sig_mask = SNS_SAM_SIGNAL_MASK;

   //register SAM to SMR so as to receive messages
   sns_sam_mr_init();

   //get information on supported sensors
   gotSensorInfo = sns_sam_get_sensor_info(sns_sam_sig_event, sns_sam_sensor_info_dbase);

   if( gotSensorInfo )
   {
      // Autodetect is done. Get UUIDs of detected sensors
      sns_sam_get_all_sensor_uuids(sns_sam_sig_event, sns_sam_sensor_uuids);
   }
   else
   {
      SNS_SAM_PRINTF0(ERROR, "SMGR not ready!");
   }


#if defined(SNS_PCSIM) || defined(SNS_QDSP_SIM)
   sns_sam_sensor_info_dbase[SNS_SAM_ACCEL].valid = true;
   sns_sam_sensor_info_dbase[SNS_SAM_GYRO].valid = true;
   sns_sam_sensor_info_dbase[SNS_SAM_MAG].valid = true;
   //numModemContexts = 0;
#endif

   sns_sam_smgr_buffering_flag = sns_sam_detect_smgr_buffering( sns_sam_sig_event );

   if( sns_sam_smgr_buffering_flag )
   {
      // If buffering is supported, get registry version to check if sensor report rates
      // are present in registry for respective algorithms.
      sns_sam_sensor_registry_version = sns_sam_get_registry_version( sns_sam_sig_event );
   }

   // query the module on which mag cal is supported
   sns_sam_get_mag_cal_module_support();

   //register algorithms with SAM
   sns_sam_last_algo_with_registry_dep = 0;
   sns_sam_reg_algos();

   //configure algorithms
   sns_sam_config_algos();

   //initialize GPIOs
   sns_sam_init_gpios();

   //register algorithm services with QCSI
   sns_sam_mr_reg_algos();

   SNS_SAM_DEBUG0(MEDIUM, DBG_SAM_SAM_TASK_SAMSTARTED);

   sns_init_done();

#if defined(SNS_DSPS_BUILD)
   // get information on what the modem supports, this call only starts a timer
   // but does not block startup
   sns_sam_get_modem_info();
#endif

#ifdef SNS_SAM_UNIT_TEST
   sns_sam_test_init();
#endif

   while (1)
   {
      sns_sam_process_events(); //wait for events and process received events
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_sensor_info_dbase_acc
  =========================================================================*/
/*!
  @brief Gets sensor info for specified type

  @param[i] type: sensor type from sns_sam_sensor_e

  @return Sensor info structure
*/
/*=======================================================================*/
sns_sam_sensor_info_s * sns_sam_sensor_info_dbase_acc(
   uint8_t type)
{
   if( type < SNS_SAM_NUM_SENSORS )
   {
      return &sns_sam_sensor_info_dbase[type];
   }
   return NULL;
}

/*---------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/*=========================================================================
  FUNCTION:  sns_sam_init
  =========================================================================*/
/*!
  @brief Sensors algorithm manager initialization.
         Creates the SAM task and internal databases.

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_init(void)
{
   uint8_t err;

   //initialize events
   sns_sam_sig_event = sns_os_sigs_create((OS_FLAGS)SNS_SAM_MSG_SIG, &err);
   sns_os_sigs_add(sns_sam_sig_event, SNS_SAM_REPORT_TIMER_SIG);
   sns_os_sigs_add(sns_sam_sig_event, SNS_SAM_QMI_DISC_SIG);
   sns_os_sigs_add(sns_sam_sig_event, SNS_SAM_AP_AWAKE_SIG);
   sns_os_sigs_add(sns_sam_sig_event, SNS_SAM_AP_SUSPEND_SIG);
   sns_os_sigs_add(sns_sam_sig_event, SNS_SAM_MODEM_INFO_SIG);
   SNS_ASSERT(sns_sam_sig_event != NULL);

   //create the SAM task
#if defined(SNS_DSPS_BUILD) || defined(SNS_PCSIM)
   err = sns_os_task_create_ext(sns_sam_task,
                            NULL,
                            &sns_sam_task_stk[SNS_SAM_MODULE_STK_SIZE-1],
                            SNS_SAM_MODULE_PRIORITY,
                            SNS_SAM_MODULE_PRIORITY,
                            &sns_sam_task_stk[0],
                            SNS_SAM_MODULE_STK_SIZE,
                            (void *)0,
                            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR,
                            (uint8_t*)("SNS_SAM"));
#else
   err = sns_os_task_create(sns_sam_task,
                            NULL,
                            &sns_sam_task_stk[SNS_SAM_MODULE_STK_SIZE-1],
                            SNS_SAM_MODULE_PRIORITY);
#endif
   SNS_ASSERT(err == 0);

   return SNS_SUCCESS;
}


/*=========================================================================
  FUNCTION:  sns_sam_req_sensor_data
  =========================================================================*/
/*!
  @brief Request sensor data for algorithm

  @param[i] algoInstId: algorithm instance id
  @param[i] clientReqId: client request id

  @return data request id for the request
*/
/*=======================================================================*/
uint8_t sns_sam_req_sensor_data(
   uint8_t algoInstId,
   uint8_t clientReqId)
{
   int32_t i;
   uint8_t dataReqId = SNS_SAM_INVALID_ID;

   if (algoInstId < SNS_SAM_MAX_ALGO_INSTS)
   {
      sns_sam_algo_inst_s* algoInstPtr = sns_sam_algo_inst_dbase[algoInstId];

      if (NULL != algoInstPtr)
      {
         sns_sam_data_req_s dataReq;
         sns_sam_get_sensor_requirements(algoInstPtr->serviceId,
                                         algoInstPtr->configData.memPtr,
                                         &dataReq);

         //send request to sensor manager
         dataReq.algoInstDbase[0] = algoInstId;
         dataReq.algoInstCount = 1;
         for( i = 0; i < dataReq.sensorCount; ++i )
         {
            dataReq.sensorDbase[i].algoInstIds[0] = algoInstId;
            dataReq.sensorDbase[i].algoInstCount = 1;
         }

         if( dataReq.sensorCount > 0 )
         {
            dataReqId = sns_sam_start_sensor_data(algoInstId, &dataReq);

            if (dataReqId != SNS_SAM_INVALID_ID)
            {
               if (dataReq.registerMDInterrupt)
               {
                  sns_sam_motion_state_start(algoInstPtr->serviceId, dataReqId);
               }
            }
         }
      }
   }

   return dataReqId;
}

/*=========================================================================
  FUNCTION:  sns_sam_add_sensor_for_algo
  =========================================================================*/
/*!
  @brief Add a sensor to a data request for a particular algorithm. This 
  function is limited only to algorithms that have existing data requests.

  @param[i] algoInstId: algorithm instance id
  @param[i] sensorReq: Individual sensor request

  @return data request id for the request
*/
/*=======================================================================*/
uint8_t sns_sam_add_sensor_for_algo(
   uint8_t algoInstId,
   sns_sam_sensor_req_s *sensorReq)
{
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   sns_sam_data_req_s *dataReq;

   if(NULL == sensorReq)
   {
      SNS_SAM_PRINTF0(ERROR, "Null sensorReq passed. Returning..");
      return dataReqId;
   }

   SNS_SAM_PRINTF2(LOW, "Add sensorId = %d for algoInstId = %d.", sensorReq->sensorId, algoInstId);

   /* Find data request for this algorithm instance */
   dataReqId = sns_sam_find_data_req_id(algoInstId, false);

   /*Data request found for the algorithm instance*/
   if (dataReqId != SNS_SAM_INVALID_ID)
   {
      uint8_t i, j;
      SNS_SAM_PRINTF2(LOW, "Found dataReqId = %d for algoInstId = %d.", dataReqId, algoInstId);
      dataReq = sns_sam_data_req_dbase[dataReqId];

      /* Find if the requested sensor is already part of the data request */
      for (j = 0; j < dataReq->sensorCount; j++)
      {
         if (dataReq->sensorDbase[j].sensorId == sensorReq->sensorId &&
             dataReq->sensorDbase[j].dataType == sensorReq->dataType &&
             dataReq->sensorDbase[j].sampleRate == sensorReq->sampleRate &&
             dataReq->sensorDbase[j].sampleQual == sensorReq->sampleQual)
         {
            break;
         }
      }

      /* Sensor wasn't found in the current data request. We need to add the 
      sensor to the data reqeust and issue a fresh sensor start request. */
      if(j == dataReq->sensorCount)
      {
         /* If the data request is already holding the maximum number of sensors 
         it can hold, return an invalid ID signifying error. */
         if(dataReq->sensorCount >= SNS_SAM_MAX_SENSORS_PER_DATA_REQ)
         {
            SNS_SAM_PRINTF1(ERROR, "dataReqId = %d cannot accommodate more sensors.", dataReqId);
            return SNS_SAM_INVALID_ID;
         }

         /* Add the new sensor to the data request and the algorithm instance ID to 
         the sensor structure */
         dataReq->sensorDbase[dataReq->sensorCount].sensorId = sensorReq->sensorId;
         dataReq->sensorDbase[dataReq->sensorCount].dataType = sensorReq->dataType;
         dataReq->sensorDbase[dataReq->sensorCount].sampleRate = sensorReq->sampleRate;
         dataReq->sensorDbase[dataReq->sensorCount].sampleQual = sensorReq->sampleQual;
         dataReq->sensorDbase[dataReq->sensorCount].algoInstIds[0] = algoInstId;
         dataReq->sensorDbase[dataReq->sensorCount].algoInstCount = 1;

         dataReq->sensorCount++;

         /* Issue sensor data start request */
         sns_sam_send_smgr_start_req(dataReqId, 
                                     sns_sam_algo_inst_dbase[algoInstId]->serviceId);
      }
      /* Sensor was found in the current data request. We need to add the 
      algorithm ID to the sensor's structure. */
      else
      {
         if (dataReq->sensorDbase[j].algoInstCount == SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR)
         {
            SNS_SAM_PRINTF1(ERROR, "sensorId = %d full. Cannot accommodate more algorithm instances.",
                            dataReq->sensorDbase[j].sensorId);
            return SNS_SAM_INVALID_ID;
         }
         else
         {
            for (i = 0; i < dataReq->sensorDbase[j].algoInstCount; j++)
            {
               /* Check for duplicates */
               if (algoInstId == dataReq->sensorDbase[j].algoInstIds[i])
               {
                  SNS_SAM_PRINTF0(LOW, "algoInstId already added to sensor's database.");
                  break;
               }
            }

            /* algoInstId not found in sensor database */
            if (i == dataReq->sensorDbase[j].algoInstCount)
            {
               dataReq->sensorDbase[j].algoInstIds[dataReq->sensorDbase[j].algoInstCount] = algoInstId;
               dataReq->sensorDbase[j].algoInstCount++;
            }
         }
      }
   }
   /* If data request is not found in the database, that means this algorithm instance wasn't 
   registered */
   else
   {
      SNS_SAM_PRINTF0(ERROR, "The algorithm is trying to add to a data request that doesn't exist.");
   }

   return dataReqId;
}

/*=========================================================================
  FUNCTION:  sns_sam_rm_sensor_for_algo
  =========================================================================*/
/*!
  @brief Remove a sensor from a data request for a particular algorithm.

  @param[i] algoInstId: algorithm instance id
  @param[i] sensorId: ID of the sensor to be disabled

  @return data request id for the request
*/
/*=======================================================================*/
uint8_t sns_sam_rm_sensor_for_algo(
   uint8_t algoInstId,
   uint8_t sensorId)
{
   uint8_t dataReqId = SNS_SAM_INVALID_ID;
   sns_sam_data_req_s *dataReq;

   SNS_SAM_PRINTF2(LOW, "Remove sensorId = %d for algoInstId = %d.", sensorId, algoInstId);

   /* Find data request for this algorithm instance */
   dataReqId = sns_sam_find_data_req_id(algoInstId, false);

   /* If data request is not found from the database, that means this 
   algorithm instance wasn't registered */
   if (dataReqId != SNS_SAM_INVALID_ID)
   {
      uint8_t i, j, k;
      SNS_SAM_PRINTF2(LOW, "Found dataReqId = %d for algoInstId = %d.", dataReqId, algoInstId);
      dataReq = sns_sam_data_req_dbase[dataReqId];

      /* Find if the sensor to be removed is part of the data request or has 
      already been removed */
      for (j = 0; j < dataReq->sensorCount; j++)
      {
         if (dataReq->sensorDbase[j].sensorId == sensorId)
         {
            break;
         }
      }

      /* Sensor was found in the current data request. We need to remove the 
      algorithm ID from the sensor's structure. */
      if (j < dataReq->sensorCount)
      {
         bool foundAlgoInstIndex = false;
         bool retainAlgoInst = false;
         bool updateRequest = false;

         SNS_SAM_PRINTF0(LOW, "Found required sensor in dataReq");

         /* Remove the algorithm instance ID from the desired sensor structure */
         for (i = 0; i < dataReq->sensorDbase[j].algoInstCount; i++)
         {
            if (algoInstId == dataReq->sensorDbase[j].algoInstIds[i])
            {
               foundAlgoInstIndex = true;
               dataReq->sensorDbase[j].algoInstCount--;
               dataReq->sensorDbase[j].algoInstIds[i] = 
                 dataReq->sensorDbase[j].algoInstIds[dataReq->sensorDbase[j].algoInstCount];
               dataReq->sensorDbase[j].algoInstIds[dataReq->sensorDbase[j].algoInstCount] = 
                 SNS_SAM_INVALID_ID;

               break;
            }
         }

         if (!foundAlgoInstIndex)
         {
            /* Algorithm instance ID is not present in the sensor database.*/
            SNS_SAM_PRINTF1(ERROR, "algoInstId = %d not found in the sensor database.", algoInstId);
            return SNS_SAM_INVALID_ID;
         }

         /* If the only algorithm subscribed to the sensor was removed, remove the sensor from 
         the data request and issue fresh start request */
         if (dataReq->sensorDbase[j].algoInstCount == 0)
         {
            dataReq->sensorCount--;
            dataReq->sensorDbase[j] = dataReq->sensorDbase[dataReq->sensorCount];

            /* If algorithms are still registered to this data request, a fresh sensor start
            request needs to be sent */
            updateRequest = true;
         }

         /*Figure out if we also need to remove the algorithm instance from the 
         data request*/
         for (i = 0; i < dataReq->sensorCount; i++)
         {
            for (k = 0; k < dataReq->sensorDbase[i].algoInstCount; k++)
            {
               if (algoInstId == dataReq->sensorDbase[i].algoInstIds[k])
               {
                  retainAlgoInst = true;
                  break;
               }
            }
         }

         /* If algorithm instance doesn't need to be retained, remove it */
         if (!retainAlgoInst)
         {
            for (i = 0; i < dataReq->algoInstCount; i++)
            {
               if(dataReq->algoInstDbase[i] == algoInstId)
               {
                  dataReq->algoInstCount--;
                  dataReq->algoInstDbase[i] =
                     dataReq->algoInstDbase[dataReq->algoInstCount];
                  dataReq->algoInstDbase[dataReq->algoInstCount] =
                     SNS_SAM_INVALID_ID;

                  break;
               }
            }
         }

         /* If no algorithms are using this data request any more, remove it from 
         the data request database and send a stop request to sensor manager */
         if(dataReq->algoInstCount == 0)
         {
            SNS_SAM_PRINTF1(HIGH, "Removing data request with Id = %d", dataReqId);
            sns_sam_send_smgr_stop_req(dataReqId,
                                       sns_sam_algo_inst_dbase[algoInstId]->serviceId);
            SNS_OS_FREE(sns_sam_data_req_dbase[dataReqId]);
            sns_sam_data_req_dbase[dataReqId] = NULL;

            sns_sam_data_req_count--;
         }
         /* Issue sensor data start request only if needed */
         else
         {
            /* Send a fresh start request only if a sensor was removed from the sensors database */
            if (updateRequest)
            {
               sns_sam_send_smgr_start_req(dataReqId, 
                                           sns_sam_algo_inst_dbase[algoInstId]->serviceId);
            }
         }
      }
      /* Sensor wasn't found in the current data request. Something went wrong. How did 
      we get here? */
      else
      {
         SNS_SAM_PRINTF1(ERROR, 
                         "algoInstId = %d requested a sensor to be turned off when it wasn't active.", 
                         algoInstId);
         return SNS_SAM_INVALID_ID;
      }
   }

   return dataReqId;
}

/*=========================================================================
  FUNCTION:  sns_sam_is_sensor_report_rate_available
  =========================================================================*/
/*!
  @brief    Detects sensor report rate availability in Registry

  @param[i] algoSvcId: algorithm service ID

  @return   'true' if sensor report rate is expected to be available;
            'false' otherwise.
*/
/*=======================================================================*/
bool sns_sam_is_sensor_report_rate_available(
   uint8_t algoSvcId)
{
   bool retVal = false;
   switch (algoSvcId)
   {
      case SNS_SAM_AMD_SVC_ID_V01:
      case SNS_SAM_RMD_SVC_ID_V01:
      case SNS_SAM_FILTERED_MAG_SVC_ID_V01:
      case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01:
      case SNS_SAM_QUATERNION_SVC_ID_V01:
      case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01:
      case SNS_SAM_ORIENTATION_SVC_ID_V01:
      case SNS_SAM_BASIC_GESTURES_SVC_ID_V01:
      case SNS_SAM_FACING_SVC_ID_V01:
      case SNS_SAM_PED_SVC_ID_V01:
         if (sns_sam_sensor_registry_version >= 0xB)
         {
            retVal = true;
         }
         break;
      case SNS_SAM_SMD_SVC_ID_V01:
         if (sns_sam_sensor_registry_version >= 0x13)
         {
            retVal = true;
         }
         break;
      case SNS_SAM_CMC_SVC_ID_V01:
         if (sns_sam_sensor_registry_version >= 0xD)
         {
            retVal = true;
         }
         break;
      case SNS_SAM_GAME_ROTATION_VECTOR_SVC_ID_V01:
         if (sns_sam_sensor_registry_version >= 0xE)
         {
            retVal = true;
         }
         break;
      default:
         break;
   }

   return retVal;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_batch_req
  =========================================================================*/
/*!
  @brief Processes a batch request

  @param[i] clientReqId: client request id
  @param[i] batchPeriod: requested batch period
  @param[i] batchSize: batch size
  @param[i] wakeClient: indicates if client should be woken up when FIFO
                        is full

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_batch_req(
   uint8_t clientReqId,
   int32_t batchPeriod,
   uint32_t batchSize,
   bool wakeClient)
{
   sns_sam_client_req_s* clientReqPtr;
   sns_err_code_e err = SNS_ERR_BAD_PARM;
   uint32_t batchPer = sns_em_convert_sec_in_q16_to_localtick(batchPeriod);

   SNS_SAM_PRINTF3(LOW,"SAM:Rxd batch request for client id %d, period %d, wakeclient %d",clientReqId, batchPeriod, wakeClient);

   clientReqPtr = sns_sam_get_client_req_handle(clientReqId);
   if( !clientReqPtr )
   {
      return err;
   }

   if( NULL == clientReqPtr->batchInfo )
   {
      // Check if batching was enabled before attempting to disable
      if ( batchPeriod <= 0 )
      {
         return SNS_SUCCESS;
      }
      else
      {
         // Allocate memory to store batching request
         clientReqPtr->batchInfo = SNS_OS_MALLOC( SNS_SAM_DBG_MOD, sizeof(sns_sam_batch_req_s) );
         SNS_ASSERT(clientReqPtr->batchInfo != NULL);

         clientReqPtr->batchInfo->batchPeriod = 0;
         clientReqPtr->batchInfo->numTimeoutsToBatch = 0;
         clientReqPtr->batchInfo->numTimeouts = 0;
         clientReqPtr->batchInfo->reportBuffer = NULL;
      }
   }
   else  // If batching is ongoing, flush existing reports
   {
      // send batch indication(s) with pending reports to client
      sns_sam_send_algo_batch_ind( clientReqPtr );
      if( clientReqPtr->batchInfo->batchPeriod == batchPer )
      {
         // No change in batch period - return
         clientReqPtr->batchInfo->wakeClient = wakeClient;
         return SNS_SUCCESS;
      }
   }

   // check report type
   switch( clientReqPtr->reportType )
   {
      case SNS_SAM_PERIODIC_REPORT:
      {
         uint32_t reportPer = clientReqPtr->period;
         uint32_t numTimeoutsToBatch = batchPer / reportPer;

         // Make batch period the least integral multiple of the report period to reuse timer
         batchPer = numTimeoutsToBatch * reportPer;
         if( batchPeriod != 0 && numTimeoutsToBatch == 0 )
         {
            // Batch period should at least be equal to the report period
            batchPer = reportPer;
            numTimeoutsToBatch = 1;
         }

         clientReqPtr->batchInfo->batchPeriod = batchPer;
         clientReqPtr->batchInfo->activeBatchPeriod = batchPer;
         clientReqPtr->batchInfo->numTimeoutsToBatch = numTimeoutsToBatch;
         clientReqPtr->batchInfo->numTimeouts = 0;
         err = SNS_SUCCESS;
         break;
      }
      case SNS_SAM_SYNC_REPORT:
      case SNS_SAM_ASYNC_REPORT: // break omitted intentionally
      {
         //TODO: check if batchPeriod is a sane value (greater than sample rate)
         clientReqPtr->batchInfo->batchPeriod = batchPer;
         clientReqPtr->batchInfo->activeBatchPeriod = batchPer;
         clientReqPtr->batchInfo->numTimeoutsToBatch = 0;
         clientReqPtr->batchInfo->numTimeouts = 0;
         if( batchPeriod == 0 )
         {
            err = sns_sam_dereg_timer( clientReqId );
         }
         else
         {
            err = sns_sam_reg_timer( clientReqId, batchPer );
         }
         break;
      }
      default:
      {
         // Oneshot and unknown report modes do not support batching
         err = SNS_ERR_NOTSUPPORTED;
      }
   }

   // Register/deregister with PM for client processor state change notification
   if( err == SNS_SUCCESS )
   {
      sns_proc_type_e_v01 procType = clientReqPtr->notify_suspend.proc_type;
      int i;

      // Find client processor id in dbase
      if( procType >= SNS_SAM_MAX_CLIENT_PROCESSORS )
      {
        err = SNS_ERR_NOTSUPPORTED;
      }
      else
      {
         clientReqPtr->batchInfo->wakeClient = wakeClient;
         if( clientReqPtr->batchInfo->batchPeriod != 0 )
         {
            if( clientReqPtr->batchInfo->reportBuffer == NULL )
            {
               // Enable batching - Create circular report buffer
               int memSize = sns_circ_buffer_get_mem_size( batchSize );

               clientReqPtr->batchInfo->reportBuffer = SNS_OS_MALLOC( SNS_SAM_DBG_MOD, memSize );
                SNS_ASSERT(clientReqPtr->batchInfo->reportBuffer != NULL);

               sns_circ_buffer_init( clientReqPtr->batchInfo->reportBuffer, batchSize );

               // Add client request ID to processor monitor database
               sns_sam_client_proc_dbase[procType].clientReqIds[sns_sam_client_proc_dbase[procType].clientCount++] =
                   clientReqId;
            }
         }
         else
         {
            // Disable batching - Cancel request only if ref count is 0
            err = SNS_ERR_FAILED;
            if( sns_sam_client_proc_dbase[procType].clientCount > 0 )
            {
               // Remove client req id from list
               for( i = 0; i < sns_sam_client_proc_dbase[procType].clientCount; i++ )
               {
                  if( sns_sam_client_proc_dbase[procType].clientReqIds[i] == clientReqId )
                  {
                     break;
                  }
               }

               if( i < sns_sam_client_proc_dbase[procType].clientCount )
               {
                  sns_sam_client_proc_dbase[procType].clientCount--;
                  sns_sam_client_proc_dbase[procType].clientReqIds[i] =
                     sns_sam_client_proc_dbase[procType].clientReqIds[sns_sam_client_proc_dbase[procType].clientCount];
                  err = SNS_SUCCESS;
               }
            }
            SNS_OS_FREE( clientReqPtr->batchInfo->reportBuffer );
            clientReqPtr->batchInfo->reportBuffer = NULL;
            SNS_OS_FREE( clientReqPtr->batchInfo );
            clientReqPtr->batchInfo = NULL;
         }
      }
   }
   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_proc_upd_batch_period_req
  =========================================================================*/
/*!
  @brief Processes an update batch period request

  @param[i] clientReqId: client request id
  @param[i] activeBatchPeriod: requested active batch period

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_proc_upd_batch_period_req(
   uint8_t clientReqId,
   int32_t activeBatchPeriod)
{
   sns_err_code_e err = SNS_SUCCESS;
   sns_sam_client_req_s * clientReqPtr = NULL;

   SNS_SAM_PRINTF2(LOW,"SAM:Rxd upd batch period request for client id %d, period %d",clientReqId, activeBatchPeriod);

   clientReqPtr = sns_sam_get_client_req_handle(clientReqId);
   if( !clientReqPtr )
   {
      return SNS_ERR_BAD_PARM;
   }

   // Allow changing active batch period only when batching is ongoing
   if( clientReqPtr->batchInfo != NULL )
   {
      uint32_t batchPeriod;
      sns_proc_type_e_v01 procType = clientReqPtr->notify_suspend.proc_type;

      if( activeBatchPeriod != 0 )
      {
         batchPeriod = sns_em_convert_sec_in_q16_to_localtick(activeBatchPeriod);
         if( clientReqPtr->period != 0 )
         {
            // Periodic reporting timer is reused for batching
            uint32_t reportPer = clientReqPtr->period;
            uint32_t numTimeoutsToBatch = batchPeriod / reportPer;

            // Make batch period the least integral multiple of the report period to reuse timer
            batchPeriod = numTimeoutsToBatch * reportPer;
            if( numTimeoutsToBatch == 0 )
            {
               // Batch period should at least be equal to the report period
               batchPeriod = reportPer;
            }
         }
         clientReqPtr->batchInfo->activeBatchPeriod = batchPeriod;
      }
      else
      {
         clientReqPtr->batchInfo->activeBatchPeriod = clientReqPtr->batchInfo->batchPeriod;
      }

      // send batch indication(s) with pending reports to client
      sns_sam_send_algo_batch_ind( clientReqPtr );

      // restart timer based on AP state
      if( !sns_sam_client_proc_dbase[procType].suspendState )
      {
         batchPeriod = clientReqPtr->batchInfo->activeBatchPeriod;
      }
      else
      {
         batchPeriod = clientReqPtr->batchInfo->batchPeriod;
      }

      if( clientReqPtr->period != 0 )
      {
         // Periodic reporting timer is reused for batching
         // Reset timeout count
         clientReqPtr->batchInfo->numTimeoutsToBatch = batchPeriod / clientReqPtr->period;
         clientReqPtr->batchInfo->numTimeouts = 0;
      }
      else
      {
         // Reset batching timer
         sns_sam_dereg_timer( clientReqId );
         sns_sam_reg_timer( clientReqId, batchPeriod );
      }
   }

   return err;
}
