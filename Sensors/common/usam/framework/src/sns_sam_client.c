/*============================================================================
  @file sns_sam_client.c

  @brief
  The SAM Framework both acts as a QMI service and a QMI client.  This file
  contains the implementation of all client duties.

  Once a dependent service becomes available, SAM will initialize a connection,
  and maintain that connection throughout its life.

  @note Response messages are processed first, then request messages, and
        finally indications

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_reg_api_v02.h"
#include "sns_init.h"
#include "sns_usmr.h"
#include "sns_debug_str.h"
#include "sns_sam.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_init.h"
#include "sns_sam_req.h"
#include "sns_sam_ind.h"
#include "sns_sam_resp.h"
#include "sns_sam_pm.h"
#include "sns_sam_memmgr.h"
#include "sns_profiling.h"

/*============================================================================
  Type Declarations
  ===========================================================================*/

/**
 * If an error callback is received from SMR, it's data is stored in this
 * object, and processed asychronously later, within the SAM main thread.
 */
struct sns_sam_client_error
{
  /* Data fields necessary to add this object to a SAM list */
  sns_q_link_s qLink;

  /* Used by the infrastructure to identify unique clients */
  smr_client_hndl clientHndl;
  /* SMR error code */
  smr_err error;
   /* Data registered during client init. Pointer to the sensor object */
  void *errCBData;
};
typedef struct sns_sam_client_error sns_sam_client_error;

struct sns_sam_client_resp_cb_data
{
  sns_sam_sensor_req *sensorReq;
  sns_sam_resp *respMsg;
};
typedef struct sns_sam_client_resp_cb_data sns_sam_client_resp_cb_data;

struct sns_sam_release_event
{
  /* Data fields necessary to add this object to a SAM list */
  sns_q_link_s qLink;

  sns_sam_sensor_req *sensorReq;
};
typedef struct sns_sam_release_event sns_sam_release_event;

/**
 * limit the maximum number of indication in samIndMsgQ. If above this
 * value, drop the new sample
 */
#define SNS_SAM_IND_MSG_Q_MAX 75

/*============================================================================
  Static Data
  ===========================================================================*/

/* Contains all unprocessed incoming response messages */
static sns_q_s samRespMsgQ SNS_SAM_UIMAGE_DATA;
static OS_EVENT *samRespMsgQMutex SNS_SAM_UIMAGE_DATA;

/* Contains all unprocessed incoming indication messages */
sns_q_s samIndMsgQ SNS_SAM_UIMAGE_DATA;
OS_EVENT *samIndMsgQMutex SNS_SAM_UIMAGE_DATA;

/* Queue of sns_sam_client_error objects associated with error callbacks */
static sns_q_s samClientErrCBQ;
static OS_EVENT *samClientErrCBQMutex;

/* Queue of sns_sam_release_event objects associated with client release callbacks */
static sns_q_s samReleaseQ;
static OS_EVENT *samReleaseQMutex;

static sns_sam_sensor sensorSMGR;
static sns_sam_sensor sensorSMGRI;
static sns_sam_sensor sensorREG;

/*============================================================================
  Global Data
  ===========================================================================*/

sns_sam_sensor_req sensorReqREG SNS_SAM_UIMAGE_DATA =
  { .sensor = &sensorREG, .clientHndl = NULL };
sns_sam_sensor_req sensorReqSMGR SNS_SAM_UIMAGE_DATA =
  { .sensor = &sensorSMGR, .clientHndl = NULL };
sns_sam_sensor_req sensorReqSMGRI SNS_SAM_UIMAGE_DATA =
  { .sensor = &sensorSMGRI, .clientHndl = NULL };

/*============================================================================
  Static Function Definitions
  ===========================================================================*/

/**
 * @brief
 * This callback function is called by the SMR infrastructure when a response
 * is received after a request is sent using smr_client_send_req()
 *
 * @param[i] clientHndl Handle used by the infrastructure to identify different clients.
 * @param[i] msgID Message ID
 * @param[i] respStruct Pointer to the response
 * @param[i] respStructLen Length of the response
 * @param[i] respCBData User-data
 * @param[i] transpErr Error code
 */
STATIC void
sns_sam_client_resp_cb( smr_client_hndl clientHndl, unsigned int msgID,
    void *respStruct, unsigned int respStructLen, void *respCBData,
    smr_err transpErr )
{
  UNREFERENCED_PARAMETER(clientHndl);
  UNREFERENCED_PARAMETER(respStruct);
  uint8_t errOS;
  sns_sam_client_resp_cb_data *cbData = respCBData;

  if( SMR_NO_ERR == transpErr )
  {
    sns_sam_resp *respMsg = cbData->respMsg;

    SNS_PRINTF_STRING_LOW_2( samModule,
      "Received response message %i from %x",
      msgID, cbData->sensorReq->sensor->sensorUID );

    respMsg->msg.msg.bufSize = respStructLen;
    respMsg->msg.msgID = msgID;
    respMsg->msg.sensorUID = &cbData->sensorReq->sensor->sensorUID;
    respMsg->sensorReq = cbData->sensorReq;

    sns_q_link( respMsg, (sns_q_link_s*)respMsg );

    sns_os_mutex_pend( samRespMsgQMutex, 0, &errOS );
    sns_q_put( &samRespMsgQ, (sns_q_link_s*)respMsg );
    sns_os_mutex_post( samRespMsgQMutex );

    sns_os_sigs_post( sns_sam_sig_event, SNS_SAM_RESP_MSG_SIG, OS_FLAG_SET, &errOS );
  }
  else
  {
    sns_sam_resp *respMsg = cbData->respMsg;

    SNS_PRINTF_STRING_ERROR_3( samModule,
        "SMR Transport error %i for sensor UID %x, msg ID: %i",
        transpErr, cbData->sensorReq->sensor->sensorUID, msgID );

    if(NULL != respMsg)
    {
      SNS_SAM_MEM_FREE(respMsg->msg.msg.buf);
      SNS_SAM_MEM_FREE(respMsg);
    }
  }

  SNS_SAM_MEM_FREE( (void*)respCBData );
}

/**
 * @brief
 * See smr_client_ind_cb.
 */
SNS_SAM_UIMAGE_CODE STATIC void
sns_sam_client_ind_cb( smr_client_hndl clientHndl, unsigned int msgID,
  void *indBuf, unsigned int indBufLen, void *indCBData )
{
  UNREFERENCED_PARAMETER(clientHndl);
  uint8_t errOS;
  bool adjustMips = false;
  sns_sam_sensor_req *sensorReq = indCBData;

  if(samIndMsgQ.cnt < SNS_SAM_IND_MSG_Q_MAX)
  {
    sns_sam_ind *indMsg = SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD, sizeof(sns_sam_ind) );
    SNS_ASSERT(NULL != indMsg);

    indMsg->msg.msg.buf = (intptr_t)SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD, indBufLen );
    SNS_ASSERT(NULL != (void*)indMsg->msg.msg.buf);
    SNS_OS_MEMCOPY( (void*)indMsg->msg.msg.buf, indBuf, indBufLen );
    indMsg->msg.msg.bufSize = indBufLen;

    indMsg->msg.msgID = msgID;
    indMsg->msg.sensorUID = &sensorReq->sensor->sensorUID;
    indMsg->sensorReq = sensorReq;
    sns_q_link( indMsg, (sns_q_link_s*)indMsg );

    sns_os_mutex_pend( samIndMsgQMutex, 0, &errOS );
    sns_q_put( &samIndMsgQ, (sns_q_link_s*)indMsg );
    adjustMips = (samIndMsgQ.cnt > SNS_SAM_Q_UPPER_THRESH)? true : false;
    sns_os_mutex_post( samIndMsgQMutex );

    if(adjustMips)
    {
      sns_sam_pm_vote_mips( SNS_SAM_MIPS_TURBO );
    }

    sns_os_sigs_post( sns_sam_sig_event,
      SNS_SAM_IND_MSG_SIG, OS_FLAG_SET, &errOS );
  }
  else
  {
    sns_sam_sensor *sensor = indCBData;
    sns_profiling_log_qdss( SNS_SAM_DROPPED_IND_MSG, 2,
      (uint32_t)sensor->sensorUID, (uint32_t)samIndMsgQ.cnt );
    SNS_PRINTF_STRING_LOW_0( samModule, "Dropping samples due to large number of unprocessed ind");
  }
}

/**
 * @brief
 * This callback function is called by the SMR infrastructure when the service
 * terminates or deregisters
 *
 * @param[i] clientHndl Used by the infrastructure to identify unique clients
 * @param[i] error Error code
 * @param[i] errCBData User-data
 */
STATIC void
sns_sam_client_error_cb( smr_client_hndl clientHndl, smr_err error,
    void *errCBData )
{
  UNREFERENCED_PARAMETER(clientHndl);
  uint8_t errOS;
  sns_sam_client_error *clientErrCB = SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD,
    sizeof(sns_sam_client_error) );
  SNS_ASSERT(NULL != clientErrCB);

  clientErrCB->clientHndl = clientHndl;
  clientErrCB->error = error;
  clientErrCB->errCBData = errCBData;

  SNS_PRINTF_STRING_LOW_0( samModule, "sns_sam_client_error_cb" );

  sns_q_link( clientErrCB, (sns_q_link_s*)clientErrCB );

  sns_os_mutex_pend( samClientErrCBQMutex, 0, &errOS );
  sns_q_put( &samClientErrCBQ, (sns_q_link_s*)clientErrCB );
  sns_os_mutex_post( samClientErrCBQMutex );

  sns_os_sigs_post( sns_sam_sig_event, SNS_SAM_CLIENT_ERROR_SIG, OS_FLAG_SET, &errOS );
}

/**
 * @brief
 * This callback function is called by the SMR infrastructure when a service
 * becomes available, or if the client-specified timeout passes.
 *
 * @param[i] serviceObj QMI service object
 * @param[i] instanceID Instance ID of the service found
 * @param[i] timeoutExpired Whether the timeout expired
 */
STATIC void
sns_sam_client_init_cb( qmi_idl_service_object_type serviceObj,
    qmi_service_instance instanceID, bool timeoutExpired )
{
  sns_sam_client_init_data *initData = SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD,
    sizeof(sns_sam_client_init_data) );
  SNS_ASSERT(NULL != initData);

  initData->serviceObj = serviceObj;
  initData->instanceID = instanceID;
  initData->timeoutExpired = timeoutExpired;

  SNS_PRINTF_STRING_LOW_0( samModule, "sns_sam_client_init_cb" );

  sns_q_link( initData, (sns_q_link_s*)initData );
  sns_sam_handle_client_init_cb( initData );
}

/**
 * Comparison function to be used when a queue needs to be emptied.
 *
 * @param[i] queueItem
 * @param[i] unused
 *
 * @return 1
 */
STATIC int
sns_sam_compare_true( void *queueItem, void *unused )
{
  UNREFERENCED_PARAMETER(queueItem);
  UNREFERENCED_PARAMETER(unused);
  return 1;
}

/**
 * Client release callback handler.  Add release event to queue and signal
 * for asynchronous processing.
 *
 * @param[i] data Sensor Request object to delete
 */
STATIC void
sns_sam_client_release_cb( void *data )
{
  uint8_t errOS;
  sns_sam_release_event *releaseData = SNS_OS_MALLOC( SNS_SAM_DBG_MOD,
    sizeof(sns_sam_release_event) );
  SNS_ASSERT(NULL != releaseData);

  releaseData->sensorReq = (sns_sam_sensor_req*)data;

  SNS_PRINTF_STRING_LOW_0( samModule, "sns_sam_client_release_cb" );

  sns_q_link( releaseData, (sns_q_link_s*)releaseData );

  sns_os_mutex_pend( samReleaseQMutex, 0, &errOS );
  sns_q_put( &samReleaseQ, (sns_q_link_s*)releaseData );
  sns_os_mutex_post( samReleaseQMutex );

  sns_os_sigs_post( sns_sam_sig_event, SNS_SAM_CLIENT_RELEASE_SIG,
      OS_FLAG_SET, &errOS );
}

/**
 * Drop all response and indication messages associated with the sensor req.
 * Free all memory associated with the sensor request object.
 *
 * @param[i] sensorReq Sensor Request object to delete
 */
STATIC void
sns_sam_handle_release(sns_sam_sensor_req *sensorReq)
{
  sns_q_link_s *qCurr;
  uint8_t errOS;

  SNS_PRINTF_STRING_MEDIUM_1( samModule,
    "Released sensor request %x", sensorReq );

  sns_os_mutex_pend( samIndMsgQMutex, 0, &errOS );
  qCurr = sns_q_check( &samIndMsgQ );
  while( NULL != qCurr )
  {
    sns_sam_ind *indMsg = (sns_sam_ind*)qCurr;
    qCurr = sns_q_next( &samIndMsgQ, qCurr );

    if( sensorReq == indMsg->sensorReq )
    {
      sns_q_delete( &indMsg->msg.qLink );
      SNS_SAM_MEM_FREE( (void*)indMsg->msg.msg.buf );
      SNS_SAM_MEM_FREE( (void*)indMsg );
    }
  }
  sns_os_mutex_post( samIndMsgQMutex );

  sns_os_mutex_pend( samRespMsgQMutex, 0, &errOS );
  qCurr = sns_q_check( &samRespMsgQ );
  while( NULL != qCurr )
  {
    sns_sam_resp *respMsg = (sns_sam_resp*)qCurr;
    qCurr = sns_q_next( &samRespMsgQ, qCurr );

    if( sensorReq == respMsg->sensorReq )
    {
      sns_q_delete( &respMsg->msg.qLink );
      SNS_SAM_MEM_FREE( (void*)respMsg->msg.msg.buf );
      SNS_SAM_MEM_FREE( (void*)respMsg );
    }
  }
  sns_os_mutex_post( samRespMsgQMutex );

  if( NULL != sensorReq->enableReq )
  {
    SNS_SAM_MEM_FREE( (void*)sensorReq->enableReq->msg.buf );
    SNS_SAM_MEM_FREE( (void*)sensorReq->enableReq );
  }
  SNS_SAM_MEM_FREE( sensorReq );
}

/*============================================================================
  Public Function Definitions
  ===========================================================================*/

sns_sam_err
sns_sam_client_init_fw( void )
{
  const uint8_t priority0 = 0;
  uint8_t errOS = 0;

  sensorSMGR.serviceObj = SNS_SMGR_SVC_get_service_object_v01();
  sensorSMGRI.serviceObj = SNS_SMGR_INTERNAL_SVC_get_service_object_v02();
  sensorREG.serviceObj = SNS_REG2_SVC_get_service_object_v02();

  samRespMsgQMutex = sns_os_mutex_create_uimg( priority0, &errOS );
  if( 0 != errOS )
  {
    SNS_PRINTF_STRING_FATAL_1( samModule, "Cannot create mutex %i", errOS );
    return SAM_EFAILED;
  }

  samIndMsgQMutex = sns_os_mutex_create_uimg( priority0, &errOS );
  if( 0 != errOS )
  {
    SNS_PRINTF_STRING_FATAL_1( samModule, "Cannot create mutex %i", errOS );
    return SAM_EFAILED;
  }

  samClientErrCBQMutex = sns_os_mutex_create( priority0, &errOS );
  if( 0 != errOS )
  {
    SNS_PRINTF_STRING_FATAL_1( samModule, "Cannot create mutex %i", errOS );
    return SAM_EFAILED;
  }

  samReleaseQMutex = sns_os_mutex_create( priority0, &errOS );
  if( 0 != errOS )
  {
    SNS_PRINTF_STRING_FATAL_1( samModule, "Cannot create mutex %i", errOS );
    return SAM_EFAILED;
  }

  sns_q_init( &samRespMsgQ );
  sns_q_init( &samIndMsgQ );
  sns_q_init( &samClientErrCBQ );
  sns_q_init( &samReleaseQ );

  return SAM_ENONE;
}

sns_sam_err
sns_sam_client_init( sns_sam_sensor_req *sensorReq )
{
  smr_err err = SAM_ENONE;
  void *indCBData = sensorReq;
  void *errCBData = sensorReq;

  if( NULL == sensorReq->clientHndl )
  {
    err = smr_client_init( sensorReq->sensor->serviceObj, SMR_CLIENT_INSTANCE_ANY,
        sns_sam_client_ind_cb, indCBData, 0, sns_sam_client_error_cb,
        errCBData, &sensorReq->clientHndl );

    if( SMR_NO_ERR != err )
    {
      SNS_PRINTF_STRING_ERROR_1( samModule,
        "smr_client_init error %i", err );
      err = SAM_ESMR;
    }
  }
  else
  {
    err = SAM_ENOT_AVAILABLE;
  }

  return err;
}

sns_sam_err
sns_sam_client_check( qmi_idl_service_object_type serviceObj,
    qmi_service_instance instanceID, uint32_t timeout )
{
  UNREFERENCED_PARAMETER(serviceObj);
  UNREFERENCED_PARAMETER(instanceID);
  UNREFERENCED_PARAMETER(timeout);
  smr_err err = SAM_ENONE;

  SNS_PRINTF_STRING_LOW_0( samModule, "Checking for service" );

  err = smr_client_check( serviceObj, instanceID, timeout,
      sns_sam_client_init_cb );

  return ( SMR_NO_ERR == err ) ? SAM_ENONE : SAM_ESMR;
}

sns_sam_err
sns_sam_client_send( sns_sam_sensor_req *sensorReq,
  struct sns_sam_msg *reqMsg )
{
  sns_sam_err rv = SAM_ENONE;
  uint32_t respMsgSize = 0;
  int32_t errQMI;
  smr_txn_handle txnHandle = NULL;
  smr_err errSMR;
  sns_sam_client_resp_cb_data *respCBData = SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD,
    sizeof(sns_sam_client_resp_cb_data) );
  SNS_ASSERT(NULL != respCBData);

  respCBData->sensorReq = sensorReq;

  SNS_PRINTF_STRING_LOW_2( samModule,
    "Sending request %i to %x", reqMsg->msgID, sensorReq->sensor->sensorUID );

  errQMI = qmi_idl_get_message_c_struct_len( sensorReq->sensor->serviceObj,
      QMI_IDL_RESPONSE, reqMsg->msgID, &respMsgSize );

  if( QMI_IDL_LIB_NO_ERR == errQMI )
  {
    sns_sam_resp *respMsg = SNS_SAM_MEM_ALLOC( SNS_SAM_DBG_MOD, sizeof(sns_sam_resp) );
    SNS_ASSERT(NULL != respMsg);
    respCBData->respMsg = respMsg;

    respMsg->msg.msg.buf = (intptr_t)SNS_OS_MALLOC( SNS_SAM_DBG_MOD, respMsgSize );
    SNS_ASSERT(NULL != (void*)respMsg->msg.msg.buf);
    SNS_OS_MEMZERO( (void*)respMsg->msg.msg.buf, respMsgSize );
    respMsg->msg.msg.bufSize = respMsgSize;

    errSMR = smr_client_send_req( sensorReq->clientHndl, reqMsg->msgID,
      (void*)reqMsg->msg.buf, reqMsg->msg.bufSize, (void*)respMsg->msg.msg.buf,
      respMsgSize, sns_sam_client_resp_cb, respCBData, &txnHandle );

    if( SMR_NO_ERR != errSMR )
    {
      SNS_PRINTF_STRING_ERROR_1( samModule,
        "smr_client_send_req error %i", errSMR );
      rv = SAM_ESMR;
      SNS_SAM_MEM_FREE( (void*)respMsg->msg.msg.buf );
      SNS_SAM_MEM_FREE( respMsg );
      SNS_SAM_MEM_FREE( respCBData );
    }
  }
  else
  {
    SNS_SAM_MEM_FREE( respCBData );
    rv = SAM_ETYPE;
  }

  return rv;
}

void
sns_sam_process_error_q( void )
{
  struct sns_sam_client_error *clientErr = NULL;
  sns_q_link_s *qCurr;
  uint32_t i;
  sns_sam_err err;
  uint8_t errOS;

  sns_os_mutex_pend( samClientErrCBQMutex, 0, &errOS );
  while( NULL != ( clientErr = sns_q_get( &samClientErrCBQ ) ) )
  {
    sns_sam_sensor_req *sensorReq =  (sns_sam_sensor_req*)clientErr->errCBData;

    for( qCurr = sns_q_check( &algoInstQ ); NULL != qCurr;
         qCurr = sns_q_next( &algoInstQ, qCurr ) )
    {
      sns_sam_algo_inst *algoInst = (sns_sam_algo_inst*)qCurr;

      for( i = 0; i < SNS_SAM_MAX_DEPENDENT_SENSOR; i++ )
      {
        if( sensorReq == algoInst->sensorRequests[ i ] )
        {
          SNS_PRINTF_STRING_HIGH_1( samModule,
            "Disabling SAM algorithm %x",
            algoInst->algorithm->sensor.sensorUID );

          sns_q_linear_delete( &algoInst->clientRequests,
            sns_sam_compare_true, NULL,
            (q_action_func_t)sns_sam_remove_client_req );
          break;
        }
      }
    }

    sensorReq->clientHndl = NULL;
    sensorReq->sensor->isAvailable = false;
    err = sns_sam_client_check( sensorReq->sensor->serviceObj,
            SMR_CLIENT_INSTANCE_ANY, 0 );

    if( SAM_ENONE != err )
    {
      SNS_PRINTF_STRING_ERROR_1( samModule,
        "Unable to register for SMR service check: %x",
        sensorReq->sensor->sensorUID );
    }
  }
  sns_os_mutex_post( samClientErrCBQMutex );
}

void
sns_sam_process_resp_q( void )
{
  sns_q_link_s *qCurr;
  uint8_t errOS;
  sns_sam_resp *respMsg = NULL;

  do
  {
    sns_os_mutex_pend( samRespMsgQMutex, 0, &errOS );
    qCurr = sns_q_get( &samRespMsgQ );
    respMsg = (sns_sam_resp*)qCurr;
    sns_os_mutex_post( samRespMsgQMutex );

    if( NULL != respMsg )
    {
      sns_sam_handle_resp( respMsg );

      SNS_SAM_MEM_FREE( (void*)respMsg->msg.msg.buf );
      SNS_SAM_MEM_FREE( (void*)respMsg );
    }
  } while( NULL != respMsg );
}

SNS_SAM_UIMAGE_CODE void
sns_sam_process_ind_q( void )
{
  sns_q_link_s *qCurr;
  uint8_t errOS;
  sns_sam_ind *indMsg;

  sns_sam_pm_adjust_mips( );
  do
  {
    sns_os_mutex_pend( samIndMsgQMutex, 0, &errOS );
    qCurr = sns_q_get( &samIndMsgQ );
    indMsg = (sns_sam_ind*)qCurr;
    sns_os_mutex_post( samIndMsgQMutex );

    if( NULL != qCurr )
    {
      sns_sam_handle_ind( indMsg );
      SNS_SAM_MEM_FREE( (void*)indMsg->msg.msg.buf );
      SNS_SAM_MEM_FREE( (void*)indMsg );
    }
  } while( NULL != qCurr );
}

void
sns_sam_process_release_q( void )
{
  uint8_t errOS;
  sns_sam_release_event *releaseEvent;

  do
  {
    sns_os_mutex_pend( samReleaseQMutex, 0, &errOS );
    releaseEvent = (sns_sam_release_event*)sns_q_get( &samReleaseQ );
    sns_os_mutex_post( samReleaseQMutex );

    if( NULL != releaseEvent )
    {
      sns_sam_handle_release( releaseEvent->sensorReq );
      SNS_OS_FREE( releaseEvent );
    }
  } while( NULL != releaseEvent );
}

void
sns_sam_client_release( sns_sam_sensor_req *sensorReq )
{
  SNS_PRINTF_STRING_MEDIUM_1( samModule,
    "Releasing sensor request %x", sensorReq );

  smr_client_release( sensorReq->clientHndl,
    sns_sam_client_release_cb, sensorReq );
}
