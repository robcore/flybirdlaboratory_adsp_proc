/******************************************************************************
  @file    sam_qmi_ping_clnt.c
  @brief   SAM QMI ping client

  DESCRIPTION
  Test client based on QMI ping client. Used to test SAM in ADSP only
  test scenario.

  ---------------------------------------------------------------------------
  Copyright (c) 2011-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-08-09  ps   Eliminate compilier warnings
*******************************************************************************/
#include "comdef.h"
#include "msg.h"
#include "qmi_client.h"
#include "qmi_idl_lib.h"
#include "qmi_cci_target.h"
#include "qmi_cci_common.h"
#include "sns_sam_sensor_thresh_v01.h"
#include "sns_sam_amd_v01.h"
#include "sns_sam_ped_v01.h"
#include "qurt.h"
#include "qurt_sclk.h"
#include "sns_smr_util.h"
#include "sns_common.h"
#include "sns_debug_api.h"
//#include "sns_smr_priv.h"
#include "sns_debug_str.h"
#include "sns_init.h"
#include "sns_em.h"

#define QMI_CLNT_WAIT_SIG  0x00010000
#define QMI_CLNT_TIMER_SIG 0x00000001
#define QMI_CLNT_IND_DONE_SIG 0x00000002
#define QMI_CLNT_ASYNC_DONE_SIG 0x00000004
#define SNS_SAM_QMI_UNIT_TEST

#define QMI_PING_CLIENT_STACK_SIZE  (2048)

//#define THRESH
#define AMD
//#define PED

static qurt_thread_attr_t  sam_qmi_ping_client_thread_attr;
static qurt_thread_t       sam_qmi_ping_client_tcb;
static char                sam_qmi_ping_client_stack[QMI_PING_CLIENT_STACK_SIZE];
static qurt_anysignal_t    sam_qmi_ping_client_sig;
static int                 sam_qmi_ping_ind_count=0;
unsigned int               sam_ping_clnt_delay = 100000;
/*=============================================================================
  CALLBACK FUNCTION sam_ping_ind_cb
=============================================================================*/
/*!
@brief
  This callback function is called by the QCCI infrastructure when
  infrastructure receives an indication for this client

@param[in]   user_handle         Opaque handle used by the infrastructure to
                 identify different services.

@param[in]   msg_id              Message ID of the indication

@param[in]  ind_buf              Buffer holding the encoded indication

@param[in]  ind_buf_len          Length of the encoded indication

@param[in]  ind_cb_data          Cookie value supplied by the client during registration

*/
/*=========================================================================*/
void sam_ping_ind_cb
(
 qmi_client_type                user_handle,
 unsigned int                   msg_id,
 void                           *ind_buf,
 unsigned int                   ind_buf_len,
 void                           *ind_cb_data
)
{
  switch (msg_id)
  {
#ifdef THRESH
    case SNS_SAM_SENSOR_THRESH_REPORT_IND_V01:
      {
        qmi_client_error_type err;
        sns_sam_sensor_thresh_report_ind_msg_v01 ind_msg;

        sam_qmi_ping_ind_count++;

        err = qmi_client_message_decode(user_handle,
                                        QMI_IDL_INDICATION,
                                        SNS_SAM_SENSOR_THRESH_REPORT_IND_V01,
                                        ind_buf, ind_buf_len,
                                        &ind_msg, sizeof(sns_sam_sensor_thresh_report_ind_msg_v01));

        qurt_printf("\n SNS THRESH REPORT IND: sample[0]: %d, sample[1]: %d, sample[2]: %d", ind_msg.sample_value[0],
                    ind_msg.sample_value[1],ind_msg.sample_value[2]);
      }
      break;

    case SNS_SAM_SENSOR_THRESH_ERROR_IND_V01:
      {
        sns_sam_sensor_thresh_error_ind_msg_v01 *ind_msg = (sns_sam_sensor_thresh_error_ind_msg_v01*)ind_buf;
        qurt_printf("\n SNS THRESH ERR IND: error: %d", ind_msg->error);
      }
      break;
#endif
#ifdef AMD
    case SNS_SAM_AMD_REPORT_IND_V01:
      {
        qmi_client_error_type err;
        sns_sam_qmd_report_ind_msg_v01 ind_msg;

        sam_qmi_ping_ind_count++;

        err = qmi_client_message_decode(user_handle,
                                        QMI_IDL_INDICATION,
                                        SNS_SAM_AMD_REPORT_IND_V01,
                                        ind_buf, ind_buf_len,
                                        &ind_msg, sizeof(sns_sam_qmd_report_ind_msg_v01));

        qurt_printf("\n AMD REPORT IND: state: %d", ind_msg.state);
      }
      break;

    case SNS_SAM_AMD_ERROR_IND_V01:
      {
        sns_sam_qmd_error_ind_msg_v01 *ind_msg = (sns_sam_qmd_error_ind_msg_v01*) ind_buf;

        qurt_printf("\n AMD ERR IND: error: %d", ind_msg->error);
      }
      break;
#endif
#ifdef PED
    case SNS_SAM_PED_REPORT_IND_V01:
      {
        qmi_client_error_type err;
        sns_sam_ped_report_ind_msg_v01 ind_msg;

        sam_qmi_ping_ind_count++;

        err = qmi_client_message_decode(user_handle,
                                        QMI_IDL_INDICATION,
                                        SNS_SAM_PED_REPORT_IND_V01,
                                        ind_buf, ind_buf_len,
                                        &ind_msg, sizeof(sns_sam_ped_report_ind_msg_v01));

        qurt_printf("\n Pedometer REPORT IND: state: %d", ind_msg.report_data.step_count);
      }
      break;

    case SNS_SAM_PED_ERROR_IND_V01:
      {
        sns_sam_ped_error_ind_msg_v01 *ind_msg = (sns_sam_ped_error_ind_msg_v01*) ind_buf;

        qurt_printf("\n Pedometer ERR IND: error: %d", ind_msg->error);
      }
      break;
#endif
    default:
      break;
  }
}

/*=============================================================================
  CALLBACK FUNCTION sam_ping_rx_cb
=============================================================================*/
/*!
@brief
  This callback function is called by the QCCI infrastructure when
  infrastructure receives an asynchronous response for this client

@param[in]   user_handle         Opaque handle used by the infrastructure to
                 identify different services.

@param[in]   msg_id              Message ID of the response

@param[in]   buf                 Buffer holding the decoded response

@param[in]   len                 Length of the decoded response

@param[in]   resp_cb_data        Cookie value supplied by the client

@param[in]   transp_err          Error value

*/
/*=========================================================================*/
static void sam_ping_rx_cb
(
 qmi_client_type                user_handle,
 unsigned int                   msg_id,
 void                           *buf,
 unsigned int                   len,
 void                           *resp_cb_data,
 qmi_client_error_type          transp_err
 )
{
  /* Print the appropriate message based on the message ID */
  switch (msg_id)
  {
#ifdef THRESH
    case SNS_SAM_SENSOR_THRESH_CANCEL_RESP_V01:
    case SNS_SAM_SENSOR_THRESH_VERSION_RESP_V01:
    case SNS_SAM_SENSOR_THRESH_DISABLE_RESP_V01:
    case SNS_SAM_SENSOR_THRESH_GET_REPORT_RESP_V01:
      qurt_printf("\n RESP: MsgID: %d",msg_id);
      break;
    case SNS_SAM_SENSOR_THRESH_ENABLE_RESP_V01:
    {
      sns_sam_sensor_thresh_enable_resp_msg_v01 *resp_msg = (sns_sam_sensor_thresh_enable_resp_msg_v01*)buf;
      qurt_printf("\n THRESH EN RESP: Result: %d   Err: %d", resp_msg->resp.sns_result_t, resp_msg->resp.sns_err_t);
    }
      break;
#endif
#ifdef AMD
    case SNS_SAM_AMD_CANCEL_RESP_V01:
    case SNS_SAM_AMD_VERSION_RESP_V01:
    case SNS_SAM_AMD_DISABLE_RESP_V01:
    case SNS_SAM_AMD_GET_REPORT_RESP_V01:
      break;

    case SNS_SAM_AMD_ENABLE_RESP_V01:
      {
        sns_sam_qmd_get_report_resp_msg_v01 *resp_msg = (sns_sam_qmd_get_report_resp_msg_v01*)buf;

        qurt_printf("\n AMD EN RESP: Result: %d   Err: %d  State: %d", resp_msg->resp.sns_result_t,
                                     resp_msg->resp.sns_err_t, resp_msg->state);
      }
      break;
#endif
#ifdef PED
    case SNS_SAM_PED_CANCEL_RESP_V01:
    case SNS_SAM_PED_VERSION_RESP_V01:
    case SNS_SAM_PED_DISABLE_RESP_V01:
    case SNS_SAM_PED_GET_REPORT_RESP_V01:
      break;

    case SNS_SAM_PED_ENABLE_RESP_V01:
      {
        sns_sam_ped_enable_resp_msg_v01 *resp_msg = (sns_sam_ped_enable_resp_msg_v01*)buf;

        qurt_printf("\n PED EN RESP: Result: %d   Err: %d  Instance id: %d", resp_msg->resp.sns_result_t,
                                     resp_msg->resp.sns_err_t, resp_msg->instance_id);
      }
      break;
#endif
    default:
      break;
  }
}

/*=============================================================================
  FUNCTION ping_data_test
=============================================================================*/
/*!
@brief
  This function sends a number of data ping messages asynchronously

@param[in]   clnt                Client handle needed to send messages

@param[in]   txn                 Transaction handle

@param[in]   num_pings           Number of data messages to send

@param[in]   msg_size            Size of data messages to send

*/
/*=========================================================================*/
int sam_ping_data_test
(
 qmi_client_type *clnt,
 qmi_txn_handle *txn,
 int num_msgs,
 int msg_size
 )
{
#ifdef THRESH
  sns_sam_sensor_thresh_enable_req_msg_v01 *data_req;
  sns_sam_sensor_thresh_enable_resp_msg_v01 *data_resp;
#endif

#ifdef AMD
  sns_sam_qmd_enable_req_msg_v01 *data_req;
  sns_sam_qmd_enable_resp_msg_v01 *data_resp;
#endif

#ifdef PED
  sns_sam_ped_enable_req_msg_v01 *data_req;
  sns_sam_ped_enable_resp_msg_v01 *data_resp;
#endif

#ifdef THRESH
  {
    int i,rc;

    data_req = (sns_sam_sensor_thresh_enable_req_msg_v01*)MALLOC(sizeof(sns_sam_sensor_thresh_enable_req_msg_v01));
    if(!data_req) {
      return -1;
    }
    data_resp = (sns_sam_sensor_thresh_enable_resp_msg_v01*)MALLOC(sizeof(sns_sam_sensor_thresh_enable_resp_msg_v01));
    if(!data_resp) {
      FREE(data_req);
      return -1;
    }
    memset( data_req, 0, sizeof(sns_sam_sensor_thresh_enable_req_msg_v01) );
    memset( data_resp, 0, sizeof(sns_sam_sensor_thresh_enable_resp_msg_v01) );
    data_req->sensor_id = 40; //SNS_SMGR_ID_PROX_LIGHT_V01;
    data_req->data_type = 1; //SNS_SMGR_DATA_TYPE_SECONDARY;
    data_req->sample_rate = 10; //10Hz in Q16
    data_req->threshold[0] = 0;
    data_req->threshold[1] = 0;
    data_req->threshold[2] = 0;

    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_ASYNC_DONE_SIG);
    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_IND_DONE_SIG);

    for (i=0;i<num_msgs;++i)
    {
        rc = qmi_client_send_msg_async(*clnt, SNS_SAM_SENSOR_THRESH_ENABLE_REQ_V01, data_req, sizeof(sns_sam_sensor_thresh_enable_req_msg_v01),
                                       data_resp, sizeof(sns_sam_sensor_thresh_enable_resp_msg_v01), sam_ping_rx_cb, (void *)2, txn);
        if (rc != 0){
          return -1;
        }
    }
  }
#endif
#ifdef AMD
  {
    int i,rc;

    data_req = (sns_sam_qmd_enable_req_msg_v01*)MALLOC(sizeof(sns_sam_qmd_enable_req_msg_v01));
    if(!data_req) {
      return -1;
    }
    data_resp = (sns_sam_qmd_enable_resp_msg_v01*)MALLOC(sizeof(sns_sam_qmd_enable_resp_msg_v01));
    if(!data_resp) {
      FREE(data_req);
      return -1;
    }
    memset( data_req, 0, sizeof(sns_sam_qmd_enable_req_msg_v01) );
    memset( data_resp, 0, sizeof(sns_sam_qmd_enable_resp_msg_v01) );
    data_req->report_period = 0; // non-zero for periodic, report every second; zero for async
    data_req->config_valid = 0;

    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_ASYNC_DONE_SIG);
    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_IND_DONE_SIG);

    for (i=0;i<num_msgs;++i)
    {
        qurt_printf("\n Enable AMD");
        rc = qmi_client_send_msg_async(*clnt, SNS_SAM_AMD_ENABLE_REQ_V01, data_req, sizeof(sns_sam_qmd_enable_req_msg_v01),
                                       data_resp, sizeof(sns_sam_qmd_enable_resp_msg_v01), sam_ping_rx_cb, (void *)2, txn);
        if (rc != 0){
          return -1;
        }
    }
  }
#endif

#ifdef PED
  {
    int i,rc;

    data_req = (sns_sam_ped_enable_req_msg_v01*)MALLOC(sizeof(sns_sam_ped_enable_req_msg_v01));
    if(!data_req) {
      return -1;
    }
    data_resp = (sns_sam_ped_enable_resp_msg_v01*)MALLOC(sizeof(sns_sam_ped_enable_resp_msg_v01));
    if(!data_resp) {
      FREE(data_req);
      return -1;
    }
    memset( data_req, 0, sizeof(sns_sam_ped_enable_req_msg_v01) );
    memset( data_resp, 0, sizeof(sns_sam_ped_enable_resp_msg_v01) );
    data_req->report_period = 0; // zero for async
    data_req->sample_rate_valid = 0;
    data_req->step_count_threshold_valid = 0;

    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_ASYNC_DONE_SIG);
    qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_IND_DONE_SIG);

    for (i=0;i<num_msgs;++i)
    {
        qurt_printf("\n Enable Pedometer");
        rc = qmi_client_send_msg_async(*clnt, SNS_SAM_PED_ENABLE_REQ_V01, data_req, sizeof(sns_sam_ped_enable_req_msg_v01),
                                       data_resp, sizeof(sns_sam_ped_enable_resp_msg_v01), sam_ping_rx_cb, (void *)2, txn);
        if (rc != 0){
          return -1;
        }
    }
  }
#endif

  /* Wait until all pending async messages have been received */
  qurt_anysignal_wait(&sam_qmi_ping_client_sig, QMI_CLNT_IND_DONE_SIG); //wait forever
  qurt_anysignal_clear(&sam_qmi_ping_client_sig, QMI_CLNT_IND_DONE_SIG);

#if defined(AMD) || defined(PED) || defined(THRESH)
  FREE(data_req);
  FREE(data_resp);
#endif
  return 0;
}

#ifdef SNS_SAM_QMI_UNIT_TEST
static int sam_qmi_ping_test_passed[] = {
0, 0, 0, 0, 0, 0
};
#endif










void sam_qmi_delay(uint32_t usec)
{
  uint64_t  usec_long;
  uint32_t  start_tick, wait_tick;

  /* it takes long time to busy-wait on Virtio */
  if (usec > 1000)
    usec = 1000;

    usec_long = usec;
    start_tick = sns_em_get_timestamp();
    wait_tick = (usec_long * 32768 + (1000000-1)) / 1000000;  /* at least one tick */
    while ( ( sns_em_get_timestamp() - start_tick ) < wait_tick )
    {
      ;
    }
}









void sam_qmi_ping_client_thread(void *unused)
{
  qmi_client_type clnt;
#ifdef SNS_SAM_QMI_UNIT_TEST
  qmi_txn_handle txn;
#endif
  qmi_client_type notifier;
  unsigned int num_services, num_entries=10, i=0, num_services_old=0;
  int rc;
  qmi_cci_os_signal_type os_params;
  qmi_service_info info[10];
#ifdef THRESH
  qmi_idl_service_object_type ping_service_object = sns_smr_get_svc_obj(SNS_SAM_SENSOR_THRESH_SVC_ID_V01);
#endif
#ifdef AMD
  qmi_idl_service_object_type ping_service_object = sns_smr_get_svc_obj(SNS_SAM_AMD_SVC_ID_V01);
#endif
#ifdef PED
  qmi_idl_service_object_type ping_service_object = sns_smr_get_svc_obj(SNS_SAM_PED_SVC_ID_V01);
#endif

  os_params.ext_signal = NULL;
  os_params.sig = QMI_CLNT_WAIT_SIG;
  os_params.timer_sig = QMI_CLNT_TIMER_SIG;

#if defined(AMD) || defined(PED) || defined(THRESH)
  if (!ping_service_object)
  {
    SNS_PRINTF_STRING_ID_ERROR_3(SNS_DBG_MOD_DSPS_SMGR,DBG_SMGR_GENERIC_STRING3,0,0,0);
  }

  //qurt_timer_sleep(sam_ping_clnt_delay); //100ms - let SMGR come up completely

  rc = qmi_client_notifier_init(ping_service_object, &os_params, &notifier);
#endif

  sns_init_done();

  /* Check if the service is up, if not wait on a signal */
  while(1)
  {
    qurt_printf("\n Wait for SAM service to be up");
    QMI_CCI_OS_SIGNAL_WAIT(&os_params, 0);
    QMI_CCI_OS_SIGNAL_CLEAR(&os_params);
    qurt_printf("\n SAM service is up");

   sam_qmi_delay(500);
    /* The server has come up, store the information in info variable */
    num_entries=10;
#if defined(AMD) || defined(PED) || defined(THRESH)
    rc = qmi_client_get_service_list( ping_service_object, info, &num_entries, &num_services);

    if(rc != QMI_NO_ERR || num_services == num_services_old)
      continue;

    num_services_old = num_services;

    for(i = 0; i < num_services; i++)
    {
      rc = qmi_client_init(&info[i], ping_service_object, sam_ping_ind_cb, NULL, &os_params, &clnt);

      qurt_printf("\n Registered test client with SAM service");
#ifdef SNS_SAM_QMI_UNIT_TEST
      rc = sam_ping_data_test(&clnt, &txn, 1, 1024);
      if(rc)
      {
        goto bail;
      }
      sam_qmi_ping_test_passed[2] = 1;
bail:

#endif

      rc = qmi_client_release(clnt);
    }

#endif  /* AMD || PED || THRESH */

  }
}

sns_err_code_e sam_qmi_ping_client_start(void)
{
  sns_err_code_e err_code;

  qurt_anysignal_init(&sam_qmi_ping_client_sig);
  qurt_thread_attr_init(&sam_qmi_ping_client_thread_attr);
  qurt_thread_attr_set_name(&sam_qmi_ping_client_thread_attr, "SAM_QMI_PING_CLNT");
  qurt_thread_attr_set_priority(&sam_qmi_ping_client_thread_attr, 10);
  qurt_thread_attr_set_stack_size(&sam_qmi_ping_client_thread_attr, QMI_PING_CLIENT_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&sam_qmi_ping_client_thread_attr, sam_qmi_ping_client_stack);
  err_code = qurt_thread_create(&sam_qmi_ping_client_tcb, &sam_qmi_ping_client_thread_attr,
      sam_qmi_ping_client_thread, NULL);

  return err_code;
}
