/******************************************************************************
 * rfsa_qmi_core.c
 *
 * QMI core interface functions for Remote File System Access
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_qmi_core.c#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-02-20   nr      Create.
=============================================================================*/
#include "rfsa_config.h"
#include "rfsa_qmi_core.h"
#include "rfsa_log.h"
#include "rfsa_errno.h"

#include "qmi_cci_target_ext.h"

static void
rfsa_indicator (qmi_client_type user_handle, unsigned int msg_id,
                void *ind_buf, unsigned int ind_buf_len, void *ind_cb_data)
{
  LOGH1("RFSA Indicator Called, MSGID=%d\n", msg_id);
}

static void
rfsa_indicator_kernel (qmi_client_type user_handle, unsigned int msg_id,
                       void *ind_buf, unsigned int ind_buf_len,
                       void *ind_cb_data)
{
  LOGH1("RFSA Kernel Indicator Called, MSGID=%d\n", msg_id);
}

void
rfsa_setup_os_params (qmi_cci_os_signal_type *os_params)
{
  os_params->timed_out = 0;

#ifdef RFSA_ANDROID
  os_params->sig_set = RFSA_QMI_WAIT_SIGNAL;
#elif defined RFSA_ADSP
  os_params->sig = RFSA_QMI_WAIT_SIGNAL;
  os_params->timer_sig = RFSA_QMI_TIMER_SIGNAL;
#elif defined RFSA_MPSS
  os_params->sig = RFSA_QMI_WAIT_SIGNAL;
  os_params->timer_sig = RFSA_QMI_TIMER_SIGNAL;
  os_params->tcb = rex_self();
#else
  #error "Compiling for unknown processor"
#endif
}

int32
rfsa_qmi_core_connect_userspace (qmi_client_type *handle, uint32_t timeout)
{
  qmi_client_error_type qmi_ret;
  qmi_cci_os_signal_type os_params;
  qmi_idl_service_object_type service_object;

  service_object = rfsa_get_service_object_v01();
  if (!service_object)
  {
    LOGE("rfsa_get_service_object_v01 error!\n");
    return RFSA_SERVER_OBJECT_NOT_FOUND;
  }

  rfsa_setup_os_params (&os_params);

  qmi_ret = qmi_client_init_instance (service_object, RFSA_USERSPACE_INSTANCE,
	                                    rfsa_indicator, NULL, &os_params,
                                      timeout, handle);
  if(qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa qmi_client_init_instance (userspace) error = %d!\n", qmi_ret);
    return RFSA_INIT_FAILED;
  }

  return RFSA_EOK;
}

int32
rfsa_qmi_core_connect_kernel (qmi_client_type *handle)
{
  qmi_client_error_type qmi_ret;
  qmi_service_info service_info;
  qmi_cci_os_signal_type os_params;
  qmi_idl_service_object_type service_object;

  service_object = rfsa_get_service_object_v01();
  if (!service_object)
  {
    LOGE("rfsa_get_service_object_v01 error!\n");
    return RFSA_SERVER_OBJECT_NOT_FOUND;
  }

  rfsa_setup_os_params (&os_params);

  qmi_ret = qmi_client_get_service_instance (service_object,
                                             RFSA_KERNEL_INSTANCE,
                                             &service_info);
  if(qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa qmi_client_get_service_instance error = %d!\n", qmi_ret);
    return RFSA_INSTANCE_NOT_FOUND;
  }

  qmi_ret = qmi_client_init(&service_info, service_object,
                            rfsa_indicator_kernel, NULL, &os_params, handle);
  if(qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa qmi_client_init (kernel) error = %d!\n", qmi_ret);
    return RFSA_INIT_FAILED;
  }

  return RFSA_EOK;
}

void
rfsa_qmi_core_disconnect (qmi_client_type *handle)
{
  (void)qmi_client_release (*handle);
}

static int32
rfsa_qmi_core_get_rfsa_error (qmi_client_error_type qmi_ret)
{
  int32 rfsa_error = RFSA_EOK;

  switch (qmi_ret)
  {
    case QMI_NO_ERR:
      rfsa_error = RFSA_EOK;
      break;

    case QMI_SERVICE_ERR:
      rfsa_error = RFSA_QMI_SERVER_DOWN;
      break;

    default:
      rfsa_error = RFSA_QMI_SEND_MSG_FAILED;
      break;
  }
  return rfsa_error;
}

int32
rfsa_qmi_core_stat (qmi_client_type *handle,
                    rfsa_file_stat_req_msg_v01 *file_stat_req,
                    rfsa_file_stat_resp_msg_v01 *file_stat_resp)
{
  qmi_client_error_type qmi_ret;

  qmi_ret = qmi_client_send_msg_sync (*handle, QMI_RFSA_FILE_STAT_REQ_MSG_V01,
                                      file_stat_req,
                                      sizeof(rfsa_file_stat_req_msg_v01),
                                      file_stat_resp,
                                      sizeof(rfsa_file_stat_resp_msg_v01),
                                      RFSA_QMI_WAIT_FOREVER);
  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa Stat qmi Failed: qmi_error:%d\n", qmi_ret);
  }

  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}


int32
rfsa_qmi_core_fcreate (qmi_client_type *handle,
                       rfsa_file_create_req_msg_v01 *file_create_req,
                       rfsa_file_create_resp_msg_v01 *file_create_resp)
{
  qmi_client_error_type qmi_ret;

  qmi_ret = qmi_client_send_msg_sync(*handle, QMI_RFSA_FILE_CREATE_REQ_MSG_V01,
                                      file_create_req,
                                      sizeof(rfsa_file_create_req_msg_v01),
                                      file_create_resp,
                                      sizeof(rfsa_file_create_resp_msg_v01),
                                      RFSA_QMI_WAIT_FOREVER);
  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa File Create qmi Failed: qmi_error:%d\n", qmi_ret);
  }

  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}


int32
rfsa_qmi_core_read (qmi_client_type *handle,
                    rfsa_file_read_req_msg_v01 *file_read_req,
                    rfsa_file_read_resp_msg_v01 *file_read_resp)
{
  qmi_client_error_type qmi_ret;

  file_read_req->client_id = RFSA_CLIENT_ID;

  qmi_ret = qmi_client_send_msg_sync (*handle, QMI_RFSA_FILE_READ_REQ_MSG_V01,
                                      file_read_req,
                                      sizeof(rfsa_file_read_req_msg_v01),
                                      file_read_resp,
                                      sizeof(rfsa_file_read_resp_msg_v01),
                                      RFSA_QMI_WAIT_FOREVER);
  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa Read (non iovec) qmi Failed: qmi_error:%d\n", qmi_ret);
  }
  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}



int32
rfsa_core_get_buff_addr (qmi_client_type *handle,
                         rfsa_get_buff_addr_req_msg_v01 *get_buff_req,
                         rfsa_get_buff_addr_resp_msg_v01 *get_buff_resp)
{
  qmi_client_error_type qmi_ret;

  get_buff_req->client_id = RFSA_CLIENT_ID;
  qmi_ret = qmi_client_send_msg_sync (*handle,
                                      QMI_RFSA_GET_BUFF_ADDR_REQ_MSG_V01,
                                      get_buff_req,
                                      sizeof(rfsa_get_buff_addr_req_msg_v01),
                                      get_buff_resp,
                                      sizeof(rfsa_get_buff_addr_resp_msg_v01),
                                      RFSA_QMI_WAIT_FOREVER);
  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa get_buffer qmi Failed: qmi_error:%d\n", qmi_ret);
  }

  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}


int32
rfsa_core_read_iovec (qmi_client_type *handle,
                      rfsa_iovec_file_read_req_msg_v01 *read_iovec_req,
                      rfsa_iovec_file_read_resp_msg_v01 *read_iovec_resp)
{
  qmi_client_error_type qmi_ret;

  read_iovec_req->client_id = RFSA_CLIENT_ID;
  qmi_ret = qmi_client_send_msg_sync(*handle,
                                     QMI_RFSA_IOVEC_FILE_READ_REQ_MSG_V01,
                                     read_iovec_req,
                                     sizeof(rfsa_iovec_file_read_req_msg_v01),
                                     read_iovec_resp,
                                     sizeof(rfsa_iovec_file_read_resp_msg_v01),
                                     RFSA_QMI_WAIT_FOREVER);
  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa read iovec qmi Failed: qmi_error:%d\n", qmi_ret);
  }

  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}


int32
rfsa_core_write_iovec (qmi_client_type *handle,
                       rfsa_iovec_file_write_req_msg_v01 *iovec_write_req,
                       rfsa_iovec_file_write_resp_msg_v01 *iovec_write_resp)
{
  qmi_client_error_type qmi_ret;

  iovec_write_req->client_id = RFSA_CLIENT_ID;
  qmi_ret = qmi_client_send_msg_sync(*handle,
                                     QMI_RFSA_IOVEC_FILE_WRITE_REQ_MSG_V01,
                                     iovec_write_req,
                                     sizeof(rfsa_iovec_file_write_req_msg_v01),
                                     iovec_write_resp,
                                     sizeof(rfsa_iovec_file_write_resp_msg_v01),
                                     RFSA_QMI_WAIT_FOREVER);

  if (qmi_ret != QMI_NO_ERR)
  {
    LOGE1("rfsa write iovec qmi Failed: qmi_error:%d\n", qmi_ret);
  }

  return rfsa_qmi_core_get_rfsa_error (qmi_ret);
}
