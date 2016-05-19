#ifndef SNS_SSM_SYNC_PROXY_C
#define SNS_SSM_SYNC_PROXY_C
/*=============================================================================
  @file sns_ssm_sync_proxy

  Sensors Service Manager's Synce Proxy Service

  This file contains the functions required by the sync proxy

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/ssm/framework/src/sns_ssm_sync_proxy.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*=============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  ------------------------------------------------------------
  2014-09-23  jtl   Initial version

=============================================================================*/


/*-----------------------------------------------------------------------------
 * Include Files
 * ---------------------------------------------------------------------------*/

#include "stdbool.h"
#include "sns_common.h"
#include "sns_common_v01.h"
#include "sns_debug_api.h"

#include "sns_smr_util.h"
#include "sns_debug_str.h"
#include "sns_ssm_priv.h"
#include "sns_sync_proxy_v01.h"
#include "sns_ssm_sync_proxy.h"
#include "sns_osa.h"

#include "sns_sam_amd_v01.h"
#include "sns_usmr.h"


/*-----------------------------------------------------------------------------
 * Global variables
 * ---------------------------------------------------------------------------*/

/* Connection handle for the AMD connection */
static smr_client_hndl sns_ssm_sync_proxy_amd_cli_hndl = NULL;

/* This connection handle is assigned to the service.
 * The handle is used to send responses & indications to the client using this
 * sync service */
static sns_ssm_qmi_connection_s *sns_ssm_sync_proxy_service_conn_hndl = NULL;

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_ind_cb
 * ---------------------------------------------------------------------------*/
static void sns_ssm_sync_proxy_ind_cb
(
 smr_client_hndl client_handle,
 unsigned int msg_id,
 void *ind_c_struct,
 unsigned int ind_struct_len,
 void *ind_cb_data
 )
{
  qmi_csi_error qmi_err;
  sns_sync_proxy_motion_ind_msg_v01 ind_msg;
  sns_sam_qmd_report_ind_msg_v01 *amd_ind = ind_c_struct;

  SNS_SSM_PRINTF1(LOW, "SSM: sync proxy ind cb. msg id %d", msg_id);

  switch( msg_id )
  {
    case SNS_SAM_AMD_REPORT_IND_V01:
      ind_msg.timestamp = amd_ind->timestamp;
      ind_msg.state = amd_ind->state;
      qmi_err = qmi_csi_send_ind( sns_ssm_sync_proxy_service_conn_hndl->client_handle,
                                  SNS_SYNC_PROXY_MOTION_IND_V01,
                                  &ind_msg, sizeof( ind_msg ) );
      if( QMI_CSI_NO_ERR != qmi_err )
      {
        SNS_SSM_PRINTF1(ERROR, "SSM: sync proxy error sending ind %d", qmi_err);
      }
      break;
    default:
      SNS_SSM_PRINTF1(ERROR, "SSM: sync proxy ind cb. UNKNOWN msg id %d", msg_id);
      break;
  }
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_prox_amd_enable_resp_cb
 * ---------------------------------------------------------------------------*/
static void sns_ssm_sync_prox_amd_resp_cb
(
 smr_client_hndl client_handle,
 unsigned int msg_id,
 void *resp_c_struct,
 unsigned int resp_c_struct_len,
 void *resp_cb_data,
 smr_err transp_err
 )
{
  uint8_t os_err;
  sns_os_sigs_post( sns_ssm.ssm_flag_grp, SNS_SSM_SYNC_PROXY_RESP_MSG_SIG,
                    OS_FLAG_SET, &os_err );
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_err_cb
 * ---------------------------------------------------------------------------*/
void sns_ssm_sync_proxy_err_cb
(
 smr_client_hndl client_handle,
 smr_err error,
 void *err_cb_data
 )
{
  SNS_SSM_PRINTF0(ERROR, "SSM: sync proxy err cb" );
  /* TODO: Implement client init error callback */
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_release_cb
 * ---------------------------------------------------------------------------*/
void sns_ssm_sync_proxy_release_cb( void* data )
{
  UNREFERENCED_PARAMETER( data );

  SNS_SSM_PRINTF0(HIGH, "SSM: sync proxy discon cb" );
  sns_ssm_sync_proxy_service_conn_hndl = NULL;
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_con_amd
 * ---------------------------------------------------------------------------*/
static void sns_ssm_sync_proxy_con_amd( void )
{
  uint8_t os_err;
  smr_err err;
  OS_FLAGS wakeup_flags = 0;
  OS_FLAGS pending_flags = 0;
  sns_sam_qmd_enable_req_msg_v01 amd_enable_req;
  sns_sam_qmd_enable_resp_msg_v01 amd_enable_resp;
  smr_txn_handle txn_handle;

  SNS_SSM_PRINTF0(HIGH, "SSM: Connecting to AMD" );
  err = smr_client_init( SNS_SAM_AMD_SVC_get_service_object_v01(),
                         SMR_CLIENT_INSTANCE_ANY,
                         sns_ssm_sync_proxy_ind_cb, NULL /* void *CBDATA */,
                         0 /* timeout */, sns_ssm_sync_proxy_err_cb,
                         NULL /* void *CBDATA */,
                         &sns_ssm_sync_proxy_amd_cli_hndl );
  if( err != SMR_NO_ERR )
  {
    SNS_SSM_PRINTF1(ERROR, "SSM: smr_client_init error %d", err );
    return;
  }

  /* Send enable request to AMD */
  amd_enable_req.report_period = 0;
  amd_enable_req.config_valid = 0;
  amd_enable_req.notify_suspend_valid = true;
  amd_enable_req.notify_suspend.proc_type = SNS_PROC_SSC_V01;
  amd_enable_req.notify_suspend.send_indications_during_suspend = true;
  err = smr_client_send_req( sns_ssm_sync_proxy_amd_cli_hndl,
                             SNS_SAM_AMD_ENABLE_REQ_V01,
                             &amd_enable_req, sizeof(amd_enable_req),
                             &amd_enable_resp, sizeof(amd_enable_resp),
                             sns_ssm_sync_prox_amd_resp_cb,
                             NULL /* CBDATA */, &txn_handle );
  if( err != SMR_NO_ERR )
  {
    SNS_SSM_PRINTF1(ERROR, "SSM: smr_client_send_req error %d", err );
    /* TODO: smr_client_release is broken, and doesn't call the callback function */
    smr_client_release( sns_ssm_sync_proxy_amd_cli_hndl,
                        sns_ssm_sync_proxy_release_cb, NULL /* CBDATA */ );
    sns_ssm_sync_proxy_amd_cli_hndl = NULL;
    return;
  }
  /* Wait for response */
  /* TODO: Fix sns_os_sigs_pend */
  /* sns_os_sigs_pend is broken and will wake up upon any signal. Work around that here */
  /* Also, the timeout in sns_os_sigs_pend is not honored, so this could lead to the thread
   * being blocked if AMD doesn't respond */
  while( (wakeup_flags & SNS_SSM_SYNC_PROXY_RESP_MSG_SIG) == 0)
  {
    wakeup_flags = sns_os_sigs_pend( sns_ssm.ssm_flag_grp, SNS_SSM_SYNC_PROXY_RESP_MSG_SIG,
                                     OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                     1000 /* timeout */, &os_err );
    pending_flags |= (wakeup_flags & ~SNS_SSM_SYNC_PROXY_RESP_MSG_SIG);
  }
  if( pending_flags != 0 )
  {
    SNS_SSM_PRINTF1(HIGH, "SSM: unexpected sigs set while awaiting AMD resp 0x%X.", wakeup_flags );
    sns_os_sigs_post( sns_ssm.ssm_flag_grp, pending_flags, OS_FLAG_SET, &os_err );
  }
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_discon_amd
 * ---------------------------------------------------------------------------*/
static void sns_ssm_sync_proxy_discon_amd( void )
{
  uint8_t os_err;

  if( sns_ssm_sync_proxy_service_conn_hndl == NULL )
  {
    SNS_SSM_PRINTF0(HIGH, "SSM: AMD already disconnected" );
    return;
  }

  sns_os_sigs_post( sns_ssm.ssm_flag_grp, SNS_SSM_SYNC_PROXY_DISCON_SIG,
                    OS_FLAG_SET, &os_err );
}
/*-----------------------------------------------------------------------------
* sns_ssm_sync_proxy_proc_discon
* ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_proc_discon(void)
{
  if( sns_ssm_sync_proxy_amd_cli_hndl != NULL )
  {
    /* TODO: smr_client_release is broken, and doesn't call the callback function */
    smr_client_release( sns_ssm_sync_proxy_amd_cli_hndl,
                        sns_ssm_sync_proxy_release_cb, NULL /* CBDATA */ );
    sns_ssm_sync_proxy_amd_cli_hndl = NULL;
  }
  return SNS_SUCCESS;
}

/*-----------------------------------------------------------------------------
 * sns_ssm_sync_proxy_proc_req
 * ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_proc_req(sns_ssm_qmi_connection_s *connection_handle,
                                           qmi_req_handle req_handle,
                                           unsigned int msg_id,
                                           void *req_c_struct )

{
  union {
    sns_common_cancel_resp_msg_v01 cancel;
    sns_common_version_resp_msg_v01 version;
    sns_sync_proxy_motion_enable_resp_msg_v01 enable;
  }resp_msg;
  unsigned int resp_msg_sz = 0;

  SNS_SSM_PRINTF1(LOW, "SSM: sync proxy proc req msg_id 0x%x", msg_id );

  switch( msg_id )
  {
    case SNS_SYNC_PROXY_CANCEL_REQ_V01:
      sns_ssm_sync_proxy_discon_amd();
      resp_msg.cancel.resp.sns_result_t = 0;
      resp_msg.cancel.resp.sns_err_t = SENSOR1_SUCCESS;
      resp_msg_sz = sizeof( sns_common_cancel_resp_msg_v01 );
      break;
    case SNS_SYNC_PROXY_VERSION_REQ_V01:
      resp_msg.version.resp.sns_result_t = 0;
      resp_msg.version.resp.sns_err_t = SENSOR1_SUCCESS;
      resp_msg.version.interface_version_number = SNS_SYNC_PROXY_SVC_V01_IDL_MINOR_VERS;
      resp_msg.version.max_message_id = SNS_SYNC_PROXY_SVC_V01_MAX_MESSAGE_ID;      
      resp_msg_sz = sizeof( sns_common_version_resp_msg_v01 );
      break;
    case SNS_SYNC_PROXY_MOTION_ENABLE_REQ_V01:
      {
        if( sns_ssm_sync_proxy_service_conn_hndl == connection_handle )
        {
          /* Re-request enable from existing client */
          SNS_SSM_PRINTF0(HIGH, "SSM: Sync Proxy enable from existing client" );
          resp_msg.enable.Resp.sns_result_t = 0;
          resp_msg.enable.Resp.sns_err_t = SENSOR1_SUCCESS;
          resp_msg.enable.num_sync_schedules_processed_valid = true;
          /* TODO: Set this value when actually doing sync wakeups */
          resp_msg.enable.num_sync_schedules_processed = 0;
          resp_msg_sz = sizeof( sns_sync_proxy_motion_enable_resp_msg_v01 );
        }
        else if( sns_ssm_sync_proxy_service_conn_hndl == NULL )
        {
          sns_ssm_sync_proxy_service_conn_hndl = connection_handle;

          /* Connect to AMD */
          sns_ssm_sync_proxy_con_amd();

          resp_msg.enable.Resp.sns_result_t = 0;
          resp_msg.enable.Resp.sns_err_t = SENSOR1_SUCCESS;
          resp_msg.enable.num_sync_schedules_processed_valid = true;
          /* TODO: Set this value when actually doing sync wakeups */
          resp_msg.enable.num_sync_schedules_processed = 0;
          resp_msg_sz = sizeof( sns_sync_proxy_motion_enable_resp_msg_v01 );
        }
        else
        {
          /* There is already a sync proxy conneciton */
          /* TODO: Support multiple connections */
          SNS_SSM_PRINTF0(HIGH, "SSM: Disallowing multiple AMD enable requests" );
          return SNS_ERR_NOTALLOWED;
        }
      }
      break;
    default:
      SNS_SSM_PRINTF1(HIGH, "SSM: sync proxy proc req -- bad msg id %d", msg_id );
      return SNS_ERR_BAD_MSG_ID;
      break;
  }

  qmi_csi_send_resp(req_handle, msg_id, &resp_msg, resp_msg_sz);
  
  return SNS_SUCCESS;
}

/*-----------------------------------------------------------------------------
* sns_ssm_sync_proxy_init
* ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_init(void)
{
  return SNS_SUCCESS;
}

#endif /* #ifndef SNS_SSM_SYNC_PROXY_C */
