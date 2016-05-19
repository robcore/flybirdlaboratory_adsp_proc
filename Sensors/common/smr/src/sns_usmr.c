/*============================================================================
  @file sns_usmr.c

  @brief Contains the implementation of the usmr interface on non ADSP
  platforms.

  @note QMI Error: See qmi_csi_error in qmi_csi.h

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ============================================================================*/
#include "sns_usmr.h"
#include "sns_usmr_priv.h"
#include "sns_em.h"
#include "sns_debug_str.h"
#include "sns_init.h"
#include "sns_debug_api.h"
#include "sns_uimg_utils.h"

/*===========================================================================
  MACROS
  ===========================================================================*/

/* The number of maximum services supported is currently restricted by the
   number of signal bits, each service requires a unique signal bit. We are
   reserving 24 bits for services, leaving 8 for SMR + expansion.
   The lowest order bits shall be used for services
*/
#define SMR_QMI_CLIENT_SIG       0x80000000
#define SMR_SVC_CHECK_RESULT_SIG 0x40000000
#define SMR_ALL_SIGS             0xFFFFFFFF

/*===========================================================================
  TYPE DEFINITIONS
  ===========================================================================*/
typedef struct
{
  sns_q_link_s q_link;
  smr_client_init_cb cb_func;
  qmi_idl_service_object_type serviceObj;
  qmi_service_instance instanceID;
  qmi_client_type qmi_notifier_handle;
  sns_em_timer_obj_t timer;
  qmi_client_os_params os_params;
  bool addedToQueue;
} sns_smr_service_check_cb_data;

/*===========================================================================
  STATIC VARIABLES
  ===========================================================================*/

/* Queue holding service_check_cb_data from timer_cb or notifier_cb
   to be processed in SMR context */
static sns_smr_protected_q_s smr_svc_check_cb_data_q;

/*===========================================================================
  GLOBAL VARIABLES
  ===========================================================================*/

/* Queue buffering messages for busy connections. Once the client becomes
 * available, the SMR will resume sending that client's indications from this
 * buffer.
 * Elements in this queue are of type smr_buffered_ind_s. */
sns_smr_protected_q_s sns_smr_conn_busy_msg_buf_q;

/* Queue containing all of the busy clients. As soon as a client becomes busy,
 * the client handle must be added to this queue. Once that client's messages
 * are flushed, the client must be removed from this queue.
 * Elements in this queue are of type smr_busy_client_s. */
sns_smr_protected_q_s sns_smr_busy_clients_q;

/*===========================================================================
  STATIC FUNCTIONS
  ===========================================================================*/

/**
 * @brief
 * Initializes the SMR task data structures
 */
static void sns_smr_task_init(void)
{
  uint8_t err;

  SNS_OS_MEMSET(&smr_services, 0, sizeof(smr_services));

  sns_q_init(&smr_svc_check_cb_data_q.protected_q);
  smr_svc_check_cb_data_q.mutex_ptr = sns_os_mutex_create(SNS_SMR_QUE_MUTEX, &err);
  SNS_ASSERT(err == OS_ERR_NONE);

  sns_q_init(&sns_smr_conn_busy_msg_buf_q.protected_q);
  sns_smr_conn_busy_msg_buf_q.mutex_ptr = sns_os_mutex_create(SNS_SMR_QUE_MUTEX, &err);
  SNS_ASSERT(err == OS_ERR_NONE);

  sns_q_init(&sns_smr_busy_clients_q.protected_q);
  sns_smr_busy_clients_q.mutex_ptr = sns_os_mutex_create(SNS_SMR_QUE_MUTEX, &err);
  SNS_ASSERT(err == OS_ERR_NONE);

  client_mutex = sns_os_mutex_create_uimg(SNS_SMR_QUE_MUTEX, &err);
  SNS_ASSERT(err == OS_ERR_NONE);
}

/**
 * @brief
 * This callback function is invoked by the QCCI infrastructure when
 * infrastructure processes a client release for this service
 */
static void
sns_smr_svc_check_release_cb( void *data )
{
  sns_smr_service_check_cb_data* cb_data = (sns_smr_service_check_cb_data *)data;

  if (NULL != cb_data)
  {
    SNS_OS_FREE( cb_data );
  }
}

/**
 * @brief
 * Processes SMR_CLIENT_SIG dispatched from timer callback or notifier callback.
 */
static void sns_smr_process_svc_check_result_sig(void)
{
  uint8_t os_err;
  sns_smr_service_check_cb_data* cb_data;

  do
  {
    sns_os_mutex_pend(smr_svc_check_cb_data_q.mutex_ptr, 0, &os_err );
    cb_data =
      (sns_smr_service_check_cb_data*)sns_q_get(&smr_svc_check_cb_data_q.protected_q);
    (void) sns_os_mutex_post(smr_svc_check_cb_data_q.mutex_ptr);

    if (cb_data != NULL)
    {
      qmi_client_error_type qmi_err = QMI_NO_ERR;
      qmi_service_info service_info;

      qmi_err = qmi_client_get_service_instance(cb_data->serviceObj,
                                                cb_data->instanceID,
                                                &service_info);
      SNS_COMMON_MSG_3(MED, "process_client_sig - service_obj=%d cb_data=%d err=%d",
                       cb_data->serviceObj, cb_data, qmi_err);

      (*(cb_data->cb_func))(cb_data->serviceObj,
                            cb_data->instanceID,
                            (qmi_err != QMI_NO_ERR) ? true : false);

      qmi_client_release_async(cb_data->qmi_notifier_handle,
          sns_smr_svc_check_release_cb, (void*)cb_data);
    }
  } while (cb_data != NULL);
}

/**
 * @brief
 * Dispatches service check result to SMR task.
 */
static
void sns_smr_dispatch_service_check_result(sns_smr_service_check_cb_data *cb_data)
{
  uint8_t os_err;

  sns_os_mutex_pend(smr_svc_check_cb_data_q.mutex_ptr, 0, &os_err );
  /* Add the cb_data to the queue if its not already on it. This is done since
     a QMI notifier cb can get called twice with the same cb_data - once from the
     IPCRouter Transport and once from the Loopback transport */
  if(!cb_data->addedToQueue)
  {
    uint32_t svc_id = 0;

    // Set the flag so that the item does not get added to the queue again
    cb_data->addedToQueue = true;

    qmi_idl_get_service_id(cb_data->serviceObj, &svc_id);
    SNS_COMMON_MSG_1(MED, "dispatch_svc_check_result - svc_id=%d", svc_id);

    if( NULL != cb_data->timer )
    {
      sns_em_cancel_timer(cb_data->timer);
    }

    sns_q_put(&smr_svc_check_cb_data_q.protected_q, &cb_data->q_link);

    sns_os_sigs_post(smr_services.smr_flag_grp, SMR_SVC_CHECK_RESULT_SIG,
                     OS_FLAG_SET, &os_err);
  }
  sns_os_mutex_post(smr_svc_check_cb_data_q.mutex_ptr);
}

/**
 * @brief
 * Timer callback for this module to check for the existence of
 * a service with a specific instance ID.
 */
static void sns_smr_service_check_timer_cb(void *args)
{
  if (NULL != args)
  {
    SNS_COMMON_MSG_1(MED, "svc_check_timer_cb - callback args %d", args);
    sns_smr_dispatch_service_check_result((sns_smr_service_check_cb_data*)args);
  }
}

/**
 * @brief
 * QMI notifier callback for this module to check for the
 * existence of a service with a specific instance ID.
 */
static
void sns_smr_service_check_notifier_cb(qmi_client_type user_handle,
                                       qmi_idl_service_object_type    service_obj,
                                       qmi_client_notify_event_type   service_event,
                                       void                           *data)
{
  SNS_COMMON_MSG_3(MED, "svc_check_notifier_cb - service_obj %d data %d event %d",
      service_obj, data, service_event);
  if (NULL != data && QMI_CLIENT_SERVICE_COUNT_INC == service_event )
  {
    sns_smr_dispatch_service_check_result((sns_smr_service_check_cb_data*)data);
  }
}


/**
 * @brief
 * Allocates a signal bit for a new service.
 */
static int8_t  sns_smr_get_new_service_sig(smr_service_hndl smr_service)
{
  int8_t i;
  int8_t ret_val = -1;

  for (i = 0; i < SMR_MAX_SERVICES; i++)
  {
    if (NULL == smr_services.services[i])
    {
      smr_services.services[i] = smr_service;
      ret_val = i;
      break;
    }
  }

  SNS_COMMON_MSG_1(MED, "smr_get_new_service sig - returning bit %d", ret_val);
  return ret_val;
}

/**
 * @brief
 * Finds an SMR service of the specified description.
 */
static int8_t smr_find_service(qmi_idl_service_object_type service_obj,
                     qmi_service_instance instance_id)
{
  uint32_t i;
  for (i = 0; i < SMR_MAX_SERVICES; i++)
  {
    if (smr_services.services[i] &&
        smr_services.services[i]->service_obj == service_obj &&
        (instance_id == SMR_CLIENT_INSTANCE_ANY ||
        smr_services.services[i]->instance_id == instance_id))
    {
      return i;
    }
  }

  return -1;
}

/**
 * @brief
 * Free up a signal bit
 */
static void sns_smr_free_service_sig(int8_t sig_num)
{
  SNS_COMMON_MSG_1(MED, "Freeing bit %d", sig_num);
  if (sig_num < 0 || sig_num > SMR_MAX_SERVICES - 1)
  {
    return;
  }

  smr_services.services[sig_num] = NULL;
}

/**
 * @brief
 * Compares a qmi_client_handle against a queued smr_busy_client_s item.
 *
 * @param[i] item_ptr Pointer to the queued item (of type smr_busy_client_s)
 * @param[i] compare_val Pointer to the client-handle to be compared against
 *                       (of type qmi_client_handle).
 *
 * @return 0 If the item_ptr and compare_val are not equivalent
 *         1 Otherwise
 */
static int smr_compare_client_handles(void* item_ptr, void* compare_val)
{
  smr_busy_client_s *busy_client_ptr;
  qmi_client_handle *compare_client_handle_ptr;

  if (NULL == compare_val)
  {
    return 0;
  }

  busy_client_ptr = (smr_busy_client_s*)item_ptr;
  compare_client_handle_ptr = (qmi_client_handle*)compare_val;

  return (busy_client_ptr->qmi_client_conn_handle == *compare_client_handle_ptr) ?
      1 : 0;
}

/**
 * @brief
 * Common connect callback for all services
 */
static
qmi_csi_cb_error smr_csi_connect_cb(qmi_client_handle qmi_handle,
                                    void *service_cookie,
                                    void **connection_handle)
{
  struct smr_client_hndl_s  *smr_qmi_client_handle;

  smr_service_hndl service_data = (smr_service_hndl)service_cookie;
  SNS_COMMON_MSG_2(MED, "csi_connect_cb - qmi_handle %d, cookie ptr %d",
      qmi_handle, service_cookie);

  if (NULL != service_data->connect_cb)
  {
    /* We are here implies that this is a connection request from a client that*
    *  is not registered with the SMR. Allocate a wrapperfor the qmi_handle    */
    smr_qmi_client_handle  = SNS_OS_ANY_MALLOC(0, sizeof(struct smr_client_hndl_s));
    if (NULL == smr_qmi_client_handle || NULL == connection_handle)
    {
      return QMI_CSI_CB_INTERNAL_ERR;
    }

    memset(smr_qmi_client_handle, 0, sizeof(*smr_qmi_client_handle));
    smr_qmi_client_handle->smr_idx = -1;
    smr_qmi_client_handle->qmi_client_conn_handle = qmi_handle;
    smr_qmi_client_handle->qmi_client = NULL;
    smr_qmi_client_handle->req_q = NULL;

    sns_os_mutex_pend(client_mutex, 0, NULL);
    smr_add_client(smr_qmi_client_handle);
    sns_os_mutex_post(client_mutex);

    *connection_handle = smr_qmi_client_handle;

    return service_data->connect_cb((smr_client_hndl)smr_qmi_client_handle->client_id,
        service_data->service_cookie, &(smr_qmi_client_handle->connection_handle));
  }

  return QMI_NO_ERR;
}

/**
 * @brief
 * Handles to disconnect callback from QMI
 */
static
void smr_csi_disconnect_cb (void *connection_handle,
                            void *service_cookie)
{
  struct smr_client_hndl_s  *smr_qmi_client_handle;
  smr_service_hndl service_data;

  SNS_COMMON_MSG_2(MED, "csi_disconnect_cb - conn_handle %d, cookie ptr %d",
      connection_handle, service_cookie);

  if (NULL == connection_handle || NULL == service_cookie)
  {
    return;
  }

  smr_qmi_client_handle = (struct smr_client_hndl_s *)connection_handle;
  service_data = (smr_service_hndl)service_cookie;

  sns_os_mutex_pend(client_mutex, 0, NULL);
  smr_remove_client(smr_qmi_client_handle->client_id);
  sns_os_mutex_post(client_mutex);

  if (NULL != service_data->disconnect_cb)
  {
    service_data->disconnect_cb(smr_qmi_client_handle->connection_handle,
        service_data->service_cookie);
  }

  SNS_OS_ANY_FREE(smr_qmi_client_handle);
}

/**
 * @brief
 * Handles request callback from QMI
 */
static qmi_csi_cb_error smr_csi_process_req_cb(void *connection_handle,
                                        qmi_req_handle req_handle,
                                        unsigned int msg_id,
                                        void  *req_c_struct,
                                        unsigned int req_c_struct_len,
                                        void *service_cookie)
{
  smr_service_hndl service_data = (smr_service_hndl)service_cookie;
  smr_req_handle wrap_req_handle = SNS_OS_MALLOC(0, sizeof(struct smr_req_handle_s));
  struct smr_client_hndl_s *client = (struct smr_client_hndl_s*)connection_handle;

  SNS_COMMON_MSG_3(MED, "csi_process_req_cb - conn_handle %d, req_handle %d, msgId %d",
      connection_handle, req_handle, msg_id);

  if (NULL == wrap_req_handle || NULL == client)
  {
    SNS_OS_FREE(wrap_req_handle);
    return QMI_CSI_CB_INTERNAL_ERR;
  }

  wrap_req_handle->req_handle = req_handle;
  wrap_req_handle->smr_idx = -1;

  if (NULL != service_data->process_req_cb)
  {
    smr_cb_err err;
    err = service_data->process_req_cb(client->connection_handle, wrap_req_handle,
        msg_id, req_c_struct, req_c_struct_len, service_data->service_cookie);

    if(SMR_CB_NO_ERR != err)
    {
      SNS_COMMON_MSG_1(MED, "Error processing req %d", err);
      SNS_OS_FREE(wrap_req_handle);
    }

    return err;
  }
  else
  {
    SNS_OS_FREE(wrap_req_handle);
    return QMI_NO_ERR;
  }
}

/**
 * @brief
 * Handles "resume ind" callback from QMI
 *
 * This callback function (if provided) is called by the framework
 * when a previously busy client becomes available for more indications.
 * (See QMI_CSI_OPTIONS_SET_RESUME_CB)
 *
 * @param[in]   client_handle       Handle used by the infrastructure to
 *                                  identify different services.
 * @param[out]  connection_handle   Services return this handle as a token to
 * @param[in]   service_cookie      Service specific data. Service cookie is
 *                                  registered with the infrastructure during
 *                                  service registration(qmi_csi_register).
 *                                  represent this client connection
 *                                  to the service.
 */
static void smr_csi_resume_ind_cb(qmi_client_handle client_handle,
                                  void *connection_handle,
                                  void *service_cookie)
{
  // PEND: check to see if the service has an smr_resume_ind cb registered with the SMR
  //       if yes, then use that cb
  //       if no, then flush that service's buffered messages from the SMR's bigImage heap

  UNREFERENCED_PARAMETER(service_cookie); //  smr_service_hndl service_data = (smr_service_hndl)service_cookie;
//  struct smr_client_hndl_s  *smr_qmi_client_handle = (struct smr_client_hndl_s *) connection_handle;
  smr_buffered_ind_s *buf_ind;
  uint8_t os_err;
  qmi_csi_error qmi_err = QMI_NO_ERR;
  smr_buffered_ind_s* delete_buf_ind = NULL;
  bool is_client_still_busy = false;

// PEND?
//  if (service_data->resume_ind_cb)
//  {
//    (*service_data->resume_ind_cb)(service_data,
//                                   smr_qmi_client_handle->connection_handle,
//                                   service_data->service_cookie);
//  }

  /* Protect the entire function with both mutexes. This will block all services
     from sending indications while the SMR is flushing its indication queue.
     If the indication queue becomes immensely large, then this could block the
     other services for a substantial amount of time (5 ms. or so). */
  sns_os_mutex_pend(sns_smr_conn_busy_msg_buf_q.mutex_ptr, 0, &os_err );
  sns_os_mutex_pend(sns_smr_busy_clients_q.mutex_ptr, 0, &os_err );

  SNS_COMMON_MSG_3(HIGH,
                   "smr_csi_resume_ind_cb - conn_handle 0x%x, client_handle 0x%x, buffer_cnt %d",
                   connection_handle,
                   client_handle,
                   sns_q_cnt(&sns_smr_conn_busy_msg_buf_q.protected_q));

  /* Iterate through the SMR's buffered indication queue and send out the
   * indications that were meant for the previously-busy client. */
  buf_ind = sns_q_check(&sns_smr_conn_busy_msg_buf_q.protected_q);

  while ( buf_ind != NULL )
  {
    // If the client handle matches, send the indication and delete the q item
    if ( buf_ind->qmi_client_conn_handle == client_handle )
    {
      qmi_err = qmi_csi_send_ind(buf_ind->qmi_client_conn_handle,
                                 buf_ind->msg_id,
                                 buf_ind->ind_c_struct,
                                 buf_ind->ind_c_struct_len);
      if ( qmi_err != QMI_NO_ERR )
      {
        SNS_COMMON_MSG_3(FATAL,
                         "smr_csi_resume_ind_cb - client 0x%x, msg %d, qmi_err %d",
                         buf_ind->qmi_client_conn_handle,
                         buf_ind->msg_id,
                         qmi_err);
        // If we see an error here, then something is probably horribly wrong

        if ( qmi_err == QMI_CSI_CONN_BUSY )
        {
          is_client_still_busy = true;
        }
        break;
      }

      // Flag the indication for deletion from the queue
      delete_buf_ind = buf_ind;
    }

    buf_ind = (smr_buffered_ind_s*)sns_q_next(&sns_smr_conn_busy_msg_buf_q.protected_q,
                                              &buf_ind->q_link);
    // Delete and free the sent indication from the queue
    if ( delete_buf_ind != NULL )
    {
      sns_q_delete(&delete_buf_ind->q_link);
      // Free the indication message and the buffered indication message struct
      SNS_OS_FREE(delete_buf_ind->ind_c_struct);
      SNS_OS_FREE(delete_buf_ind);

      // Reset the delete_buf_ind flag
      delete_buf_ind = NULL;
    }
  }

  SNS_COMMON_MSG_1(HIGH,
                   "%d inds left in the conn_busy queue",
                   sns_q_cnt(&sns_smr_conn_busy_msg_buf_q.protected_q));

  if ( !is_client_still_busy )
  {
    // Remove the previously-busy client from the sns_smr_busy_client_q and free it
    smr_busy_client_s* busy_client = smr_find_busy_client(client_handle);
    if ( busy_client != NULL )
    {
      sns_q_delete(&busy_client->q_link);
      SNS_COMMON_MSG_2(HIGH,
                       "Removed busy client_handle 0x%x, %d busy clients remaining",
                       client_handle,
                       sns_q_cnt(&sns_smr_busy_clients_q.protected_q));
      SNS_OS_FREE(busy_client);
    }
  }

  sns_os_mutex_post(sns_smr_busy_clients_q.mutex_ptr);
  sns_os_mutex_post(sns_smr_conn_busy_msg_buf_q.mutex_ptr);
}

/**
 * @brief
 * Handles indication callback from QMI
 */
static
void smr_cci_ind_cb (qmi_client_type user_handle,
                     unsigned int msg_id,
                     void *ind_buf,
                     unsigned int ind_buf_len,
                     void *ind_cb_data)
{
  smr_client_hndl client_handle;
  qmi_client_error_type qmi_err = QMI_NO_ERR;
  uint32_t decoded_size;
  uint8_t* smr_ind_msg;
  /* SNS_COMMON_MSG_3(MED,
                   "cci_ind_cb client %d, msgId %d, msgLen %d",
                   user_handle,
                   msg_id,
                   ind_buf_len); */

  if (ind_cb_data)
  {
    client_handle = (smr_client_hndl)(ind_cb_data);

    qmi_err = qmi_idl_get_message_c_struct_len(client_handle->service_obj,
                                               QMI_IDL_INDICATION,
                                               (uint16_t)msg_id,
                                               &decoded_size);
    if( QMI_NO_ERR != qmi_err )
    {
      SNS_COMMON_MSG_1(ERROR, "Error getting struct len %d", qmi_err);
      return;
    }

    smr_ind_msg = SNS_OS_MALLOC(0, decoded_size);
    if (smr_ind_msg == NULL)
    {
      SNS_COMMON_MSG_1(ERROR, "cci_ind_cb - cannot allocate memory of %d bytes",
                       decoded_size);
      return;
    }

    qmi_err = qmi_client_message_decode(user_handle,
                                         QMI_IDL_INDICATION,
                                         msg_id,
                                         ind_buf,
                                         ind_buf_len,
                                         smr_ind_msg,
                                         decoded_size );
    if( QMI_NO_ERR != qmi_err )
    {
      SNS_COMMON_MSG_1(ERROR, "Error decoding msg %d", qmi_err);
      SNS_OS_FREE(smr_ind_msg);
      return ;
    }

    if (client_handle->cb_ptr)
    {
      client_handle->cb_ptr(client_handle, msg_id, smr_ind_msg,
          decoded_size, client_handle->cb_data);
    }
    else
    {
      SNS_COMMON_MSG_0(ERROR, "No callback installed");
    }

    SNS_OS_FREE(smr_ind_msg);
  }
}

/*===========================================================================
  STATIC FUNCTIONS - CLIENT
  ===========================================================================*/
static void smr_client_recv_msg_async_cb (qmi_client_type        user_handle,
                                   unsigned int           msg_id,
                                   void                   *resp_c_struct,
                                   unsigned int           resp_c_struct_len,
                                   void                   *resp_cb_data,
                                   qmi_client_error_type  transp_err)
{
  smr_req_handle wrap_req_handle = resp_cb_data;
  struct smr_client_hndl_s *client;

  sns_os_mutex_pend(client_mutex, 0, NULL);
  client = smr_find_client((uint32_t)wrap_req_handle->client_id);
  sns_os_mutex_post(client_mutex);

  if(NULL != client)
  {
    wrap_req_handle->resp_cb(client, msg_id, resp_c_struct, resp_c_struct_len,
        wrap_req_handle->resp_cb_data, transp_err);
  }
}

static void
sns_smr_client_release_cb(void *data)
{
  smr_client_hndl client_handle = (smr_client_hndl)data;

  sns_os_mutex_pend(client_mutex, 0, NULL);
  if(NULL != client_handle &&
     NULL != client_handle->release_cb)
  {
    client_handle->release_cb(client_handle->release_cb_data);
    smr_remove_client(client_handle->client_id);
  }
  sns_os_mutex_post(client_mutex);
  SNS_OS_ANY_FREE(client_handle);
}

/**
 * Remove a specific request handle from a SMR client.  Presumably this will be
 * called when a response message is received.
 *
 * @param[io] client Client to be modified
 * @param[i] req_handle Request to search for
 *
 * @return true if request found; false otherwise
 */
static bool smr_remove_req_hndl(struct smr_client_hndl_s *client, struct smr_req_handle_s const *req_handle)
{
  struct smr_req_handle_s *prev_req, *curr_req;

  for(prev_req = NULL, curr_req = client->req_q;
      NULL != curr_req;
      prev_req = curr_req, curr_req = curr_req->next)
  {
    if(curr_req == req_handle)
    {
      if(NULL == prev_req)
      {
        client->req_q = curr_req->next;
      }
      else
      {
        prev_req->next = curr_req->next;
      }
      return true;
    }
  }

  return false;
}

/*===========================================================================
  PUBLIC FUNCTIONS - CLIENT
  ===========================================================================*/
/**
 * @brief
 * Helper blocking function to lookup and initialize a connection with a
 * service with a specific instance ID.
 */
smr_err smr_client_init(qmi_idl_service_object_type service_obj,
                        qmi_service_instance instance_id,
                        smr_client_ind_cb ind_cb,
                        void *ind_cb_data,
                        uint32_t timeout,
                        smr_client_error_cb err_cb,
                        void *err_cb_data,
                        smr_client_hndl *client_handle)
{
  qmi_client_error_type qmi_err = QMI_NO_ERR;
  smr_client_hndl smr_client_p;

  SNS_COMMON_MSG_3(HIGH, "init client - service %d, instance %d, tmo %d",
      service_obj, instance_id, timeout);

  SNS_COMMON_MSG_3(HIGH, "Callbacks ind_cb %d, ind_cb_data %d, err_cb %d",
      ind_cb, ind_cb_data, err_cb);

  smr_client_p = SNS_OS_ANY_MALLOC(0, sizeof(struct smr_client_hndl_s));
  if (NULL == smr_client_p)
  {
    SNS_COMMON_MSG_0(ERROR, "Cannot allocate memory for smr_client");
    return SMR_OUT_OF_MEMORY;
  }

  smr_client_p->cb_data = ind_cb_data;
  smr_client_p->cb_ptr = ind_cb;
  smr_client_p->service_obj = service_obj;
  smr_client_p->req_q = NULL;

  /* If this is a service that is registered with SMR, tag info */
  smr_client_p->smr_idx = smr_find_service(service_obj, instance_id);

  sns_os_mutex_pend(client_mutex, 0, NULL);
  smr_add_client( smr_client_p );
  sns_os_mutex_post(client_mutex);

  *client_handle = (smr_client_hndl)smr_client_p->client_id;

  if (smr_client_p->smr_idx < 0)
  {
    qmi_err = qmi_client_init_instance(service_obj,
        (qmi_service_instance)instance_id, smr_cci_ind_cb, smr_client_p,
        &smr_client_p->os_params, timeout, &(smr_client_p->qmi_client));

    if (QMI_NO_ERR == qmi_err )
    {
      qmi_err =  qmi_client_register_error_cb(smr_client_p->qmi_client,
          (qmi_client_error_cb) err_cb, err_cb_data);
    }
  }
  else
  {
    // PEND: We are missing out on the error callbacks
    struct smr_service_hndl_s *svc_hndl = smr_services.services[ smr_client_p->smr_idx ];

    svc_hndl->connect_cb((smr_client_hndl)smr_client_p->client_id,
        svc_hndl->service_cookie, &smr_client_p->connection_handle);
  }

  SNS_COMMON_MSG_2(HIGH, "Client Inited : qmi_err %d, local idx",
      qmi_err, smr_client_p->smr_idx);
  return qmi_err == QMI_NO_ERR ? SMR_NO_ERR : SMR_XPORT_ERR;
}

/**
 * @brief
 * Releases the connection to a service and return immediately without blocking.
 * the provided callback is called when the connection is fully released and
 * it is safe for the caller to release any associated resources.
 */
smr_err smr_client_release(smr_client_hndl client_id,
                           smr_client_release_cb release_cb,
                           void *release_cb_data)
{
  qmi_client_error_type qmi_err = QMI_NO_ERR;
  struct smr_client_hndl_s *client;

  SNS_COMMON_MSG_3(HIGH, "Releasing client %d, rel_cb %d, cb_data %d",
      client_id, release_cb, release_cb_data);

  sns_os_mutex_pend(client_mutex, 0, NULL);
  client = smr_find_client((uint32_t)client_id);
  if(NULL != client)
  {
    client->release_cb_data = release_cb_data;
    client->release_cb = release_cb;

    if(smr_is_valid_service(client->smr_idx))
    {
      if(NULL == client->req_q)
      {
        struct smr_service_hndl_s *svc_h = smr_services.services[client->smr_idx];
        smr_remove_client(client->client_id);
        svc_h->disconnect_cb(client->connection_handle, svc_h->service_cookie);
        client->release_cb(client->release_cb_data);
        SNS_OS_ANY_FREE(client);
      }
      sns_os_mutex_post(client_mutex);
    }
    else
    {
      sns_os_mutex_post(client_mutex);
      qmi_err = qmi_client_release_async(client->qmi_client,
          sns_smr_client_release_cb, client);

      if(QMI_NO_ERR != qmi_err)
      {
        SNS_COMMON_MSG_1(ERROR, "SMR Client Release QMI Error : %d", qmi_err);
      }
    }
  }
  else
  {
    sns_os_mutex_post(client_mutex);
    SNS_COMMON_MSG_1(ERROR, "SMR Client not found: %d", client_id);
  }

  return QMI_NO_ERR;
}

/**
 * @brief
 * Sends an asynchronous message on the specified connection.
 * The callback function is expected to decode the message before sending it
 * through this function.
 */
smr_err smr_client_send_req(smr_client_hndl client_id,
                            unsigned int msg_id,
                            void *req_c_struct,
                            unsigned int req_c_struct_len,
                            void *resp_c_struct,
                            unsigned int resp_c_struct_len,
                            smr_client_resp_cb resp_cb,
                            void *resp_cb_data,
                            smr_txn_handle *txn_handle)
{
  qmi_client_error_type qmi_err = QMI_NO_ERR;
  smr_req_handle wrap_req_handle = SNS_OS_MALLOC(0, sizeof(struct smr_req_handle_s));
  struct smr_client_hndl_s *client;
  smr_err rv = QMI_NO_ERR;
  uint8_t smr_idx;
  qmi_client_type qmi_client;

  sns_os_mutex_pend(client_mutex, 0, NULL);
  client = smr_find_client((uint32_t)client_id);

  if (NULL == wrap_req_handle)
  {
    rv = SMR_OUT_OF_MEMORY;
    sns_os_mutex_post(client_mutex);
  }
  else if (NULL == client)
  {
    rv = SMR_INVALID_PARAMS;
    sns_os_mutex_post(client_mutex);
  }
  else
  {
    smr_idx = client->smr_idx;
    qmi_client = client->qmi_client;

    wrap_req_handle->client_id = (uint32_t)client_id;
    wrap_req_handle->resp_cb = resp_cb;
    wrap_req_handle->resp_cb_data = resp_cb_data;
    wrap_req_handle->resp_c_struct = resp_c_struct;
    wrap_req_handle->resp_c_struct_len = resp_c_struct_len;
    wrap_req_handle->next = client->req_q;

    if (smr_is_valid_service(smr_idx))
    {
      struct smr_service_hndl_s *svc_h;
      smr_cb_err err;

      wrap_req_handle->smr_idx = smr_idx;
      svc_h = smr_services.services[smr_idx];
      client->req_q = wrap_req_handle;

      err = svc_h->process_req_cb(client->connection_handle, wrap_req_handle,
          msg_id, req_c_struct, req_c_struct_len, svc_h->service_cookie);

      if(SMR_CB_NO_ERR != err)
      {
        SNS_COMMON_MSG_1(MED, "Error processing req %d", err);
        smr_remove_req_hndl(client, wrap_req_handle);
        SNS_OS_FREE(wrap_req_handle);
      }
    }

    sns_os_mutex_post(client_mutex);

    if (!smr_is_valid_service(smr_idx))
    {
      wrap_req_handle->smr_idx = -1;

      qmi_err = qmi_client_send_msg_async(qmi_client,
          msg_id, req_c_struct, req_c_struct_len, resp_c_struct,
          resp_c_struct_len, smr_client_recv_msg_async_cb, wrap_req_handle,
          (qmi_txn_handle*) txn_handle);
      rv = qmi_err == QMI_NO_ERR ? SMR_NO_ERR: SMR_XPORT_ERR;
    }

    SNS_COMMON_MSG_3(MED, "send_req for client %d, msgId %d, err %d",
        client, msg_id, qmi_err);
  }

  return rv;
}

/*===========================================================================
  PUBLIC FUNCTIONS - SERVICE
  ===========================================================================*/

/**
 * @brief
 * Register a service with the SMR infrastructure.
 */
smr_err smr_service_register(qmi_idl_service_object_type service_obj,
                             qmi_service_instance instance_id,
                             smr_service_connect service_connect,
                             smr_service_disconnect service_disconnect,
                             smr_process_req service_process_req,
                             // PEND: smr_resume_ind service_resume_ind,
                             void *service_cookie,
                             smr_service_hndl *smr_handle)
{
  qmi_client_error_type  qmi_err = QMI_NO_ERR;
  qmi_csi_options   qmi_options;
  uint8_t osa_err;
  smr_service_hndl smr_service = NULL;
  int8_t sig_num;
  uint32_t svc_id = 0;
  qmi_idl_get_service_id(service_obj, &svc_id);

  SNS_COMMON_MSG_3(HIGH, "register svc_id %d, instance %d, cookie %d",
      svc_id, instance_id, service_cookie);

  SNS_COMMON_MSG_3(HIGH, "Callbacks connect %d, disconnect %d, process_req %d",
      service_connect, service_disconnect, service_process_req);

  if (NULL == smr_handle)
  {
    SNS_COMMON_MSG_0(ERROR, "NULL smr handle");
    return SMR_INVALID_PARAMS;
  }

  smr_service = SNS_OS_MALLOC(0, sizeof(struct smr_service_hndl_s));
  if (NULL == smr_service)
  {
    SNS_COMMON_MSG_0(ERROR, "Could not allocate memory");
    return SMR_OUT_OF_MEMORY;
  }

  smr_service->service_obj    = service_obj;
  smr_service->instance_id    = instance_id;
  smr_service->service_cookie = service_cookie;
  smr_service->connect_cb     = service_connect;
  smr_service->disconnect_cb  = service_disconnect;
  smr_service->process_req_cb = service_process_req;

  *smr_handle = smr_service;

  QMI_CSI_OPTIONS_INIT(qmi_options);
  QMI_CSI_OPTIONS_SET_INSTANCE_ID(qmi_options, instance_id);
  // Set the "resume ind" callback
  QMI_CSI_OPTIONS_SET_RESUME_IND_CB(qmi_options, smr_csi_resume_ind_cb);
  // todo: consider QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS (default is 30)
//  QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS(qmi_options, 12); // REMOVE THIS!!!!!!!!! FOR DEBUG ONLY!

  sig_num = sns_smr_get_new_service_sig(smr_service);
  if (sig_num < 0)
  {
    SNS_COMMON_MSG_0(ERROR, "Could not allocate signal for service");
    SNS_OS_FREE(smr_service);
    return SMR_OUT_OF_MEMORY;
  }
  smr_service->smr_idx = sig_num;

  sns_os_set_qmi_csi_params(smr_services.smr_flag_grp, 1 << sig_num,
      &(smr_service->os_params), &osa_err);

  if (OS_ERR_NONE != osa_err)
  {
    sns_smr_free_service_sig(sig_num);
    SNS_OS_FREE(smr_service);
    SNS_COMMON_MSG_1(ERROR, "OSA error %d", osa_err);
    return SMR_OS_ERR;
  }

  qmi_err = qmi_csi_register_with_options(service_obj, smr_csi_connect_cb,
      smr_csi_disconnect_cb, smr_csi_process_req_cb, smr_service,
      &(smr_service->os_params), &qmi_options, &(smr_service->service_provider));

  if (QMI_NO_ERR != qmi_err )
  {
     sns_smr_free_service_sig(sig_num);
     SNS_OS_FREE(smr_service);
     SNS_COMMON_MSG_1(ERROR, "QMI error %d", qmi_err);
     return SMR_XPORT_ERR;
  }

  return SMR_NO_ERR;
}

/**
 * @brief
 * Unregisters a service.
 */
smr_err smr_service_unregister(smr_service_hndl service_provider )
{
  qmi_client_error_type qmi_err = QMI_NO_ERR;

  qmi_err = qmi_csi_unregister(service_provider->service_provider);
  sns_smr_free_service_sig(service_provider->smr_idx);
  smr_remove_service(service_provider->smr_idx);
  SNS_COMMON_MSG_2(HIGH, "Unregister service %d, err %d", service_provider, qmi_err);

  return qmi_err == QMI_NO_ERR ? SMR_NO_ERR: SMR_XPORT_ERR;
}

/**
 * @brief
 * Sends a response to the client.  Response must always be sent, as the
 * client will likely not free it's pre-allocated response buffer until
 * it receives one.
 */
smr_err smr_service_send_resp(smr_req_handle req_handle,
                              unsigned int msg_id,
                              void *resp_c_struct,
                              unsigned int resp_c_struct_len)
{
  qmi_client_error_type  qmi_err = QMI_NO_ERR;

  if (smr_is_valid_service(req_handle->smr_idx))
  {
    struct smr_client_hndl_s *client;

    sns_os_mutex_pend(client_mutex, 0, NULL);
    client = smr_find_client((uint32_t)req_handle->client_id);
    if (NULL != client && smr_remove_req_hndl(client, req_handle))
    {
      memcpy(req_handle->resp_c_struct, resp_c_struct, resp_c_struct_len);
      req_handle->resp_cb(client, msg_id,
          req_handle->resp_c_struct, resp_c_struct_len,
          req_handle->resp_cb_data, SMR_NO_ERR);
      SNS_OS_FREE(req_handle);

      if(NULL == client->req_q && NULL != client->release_cb)
      {
        struct smr_service_hndl_s *svc_h = smr_services.services[client->smr_idx];
        smr_remove_client(client->client_id);
        svc_h->disconnect_cb(client->connection_handle, svc_h->service_cookie);
        client->release_cb(client->release_cb_data);
        SNS_OS_ANY_FREE(client);
      }
    }
    else
    {
      SNS_COMMON_MSG_0(HIGH, "Dropping response due to stale client or req");
    }
    sns_os_mutex_post(client_mutex);
  }
  else
  {
    qmi_err = qmi_csi_send_resp(req_handle->req_handle, msg_id,
        resp_c_struct, resp_c_struct_len);

    SNS_OS_FREE(req_handle);
  }

  SNS_COMMON_MSG_3(HIGH, "Send resp handle %d, msg_id %d, err %d",
        req_handle, msg_id, qmi_err);

  return qmi_err == QMI_NO_ERR ? SMR_NO_ERR: SMR_XPORT_ERR;
}

/**
 * @brief
 * Sends a broadcast indication to all registered clients.
 *
 * @param[i] service_provider Handle used by SMR infrastructure to identify
 *                            the service that intends to send a broadcast message.
 * @param[i] msg_id Message ID for this particular message.
 * @param[i] ind_c_struct C data structure for this broadcast indication.
 * @param[i] ind_c_struct_len Size of the broadcast indication.
 *
 * @return SMR_NO_ERR if function is successful, error code otherwise.
 */
smr_err smr_service_broadcast_ind(smr_service_hndl *service_provider,
                                  unsigned int msg_id,
                                  void *ind_c_struct,
                                  unsigned int ind_c_struct_len)
{
  qmi_client_error_type  qmi_err = QMI_NO_ERR;

  qmi_err = qmi_csi_send_broadcast_ind((qmi_csi_service_handle)service_provider,
                                            msg_id,
                                            ind_c_struct,
                                            ind_c_struct_len);
  SNS_COMMON_MSG_3(HIGH, "Send broadcast ind service %d, msg_id %d, err %d",
      service_provider, msg_id, qmi_err);
  return qmi_err == QMI_NO_ERR ? SMR_NO_ERR: SMR_XPORT_ERR;
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
smr_err  smr_client_check(qmi_idl_service_object_type serviceObj,
                          qmi_service_instance instanceID,
                          unsigned int timeout,
                          smr_client_init_cb cb_func)
{
  qmi_client_error_type qmi_err  = QMI_NO_ERR;
  qmi_service_info service_info;
  sns_smr_service_check_cb_data *smr_cb_data;
  sns_err_code_e sns_err;
  uint32_t svc_id = 0;
  qmi_idl_get_service_id(serviceObj, &svc_id);

  SNS_COMMON_MSG_3(HIGH, "client_check - svc_id %d instance %d, tmo %d",
      svc_id, instanceID, timeout);

  /* probe for the service */
  qmi_err = qmi_client_get_service_instance(serviceObj, instanceID, &service_info);
  if (QMI_NO_ERR != qmi_err)
  {
    smr_cb_data = SNS_OS_MALLOC(SNS_USMR, sizeof(sns_smr_service_check_cb_data));
    if (NULL == smr_cb_data)
    {
      SNS_COMMON_MSG_0(ERROR, "client_check - Cannot allocate memory");
      return SMR_OUT_OF_MEMORY;
    }

    sns_q_link(smr_cb_data, &smr_cb_data->q_link);
    smr_cb_data->addedToQueue =  FALSE;
    smr_cb_data->serviceObj = serviceObj;
    smr_cb_data->instanceID = instanceID;
    smr_cb_data->qmi_notifier_handle = NULL; // We break abstraction here - find a cleaner method
    smr_cb_data->timer = NULL;
    smr_cb_data->cb_func = cb_func;

    smr_cb_data->os_params.ext_signal = NULL;
    smr_cb_data->os_params.sig = SMR_QMI_CLIENT_SIG;
    smr_cb_data->os_params.timer_sig = 0x0;

    qmi_err = qmi_client_notifier_init(serviceObj,
        &smr_cb_data->os_params, &smr_cb_data->qmi_notifier_handle);
    if (QMI_NO_ERR != qmi_err)
    {
      SNS_COMMON_MSG_1(ERROR, "client_check - QMI error", qmi_err);
      SNS_OS_FREE(smr_cb_data);
      return SMR_XPORT_ERR;
    }

    if( 0 != timeout )
    {
      /* Start the timer - we start the timer first, as qmi notification callback
        can fire in the callback itself */
      sns_err = sns_em_create_timer_obj(sns_smr_service_check_timer_cb,
          smr_cb_data, SNS_EM_TIMER_TYPE_ONESHOT, &smr_cb_data->timer);
      if (SNS_SUCCESS != sns_err)
      {
        SNS_COMMON_MSG_1(ERROR, "Cannot Create timer - err %d", sns_err);
        SNS_OS_FREE(smr_cb_data);
        return SMR_OUT_OF_MEMORY;
      }

      sns_err = sns_em_register_timer(smr_cb_data->timer,
          sns_em_convert_usec_to_localtick(timeout));
      if (SNS_SUCCESS != sns_err)
      {
        SNS_COMMON_MSG_1(ERROR, "Cannot Register timer - err %d", sns_err);
        SNS_OS_FREE(smr_cb_data);
        return SMR_OUT_OF_MEMORY;
      }
    }

    qmi_err = qmi_client_register_notify_cb(smr_cb_data->qmi_notifier_handle,
          sns_smr_service_check_notifier_cb, smr_cb_data);
    if (QMI_NO_ERR != qmi_err)
    {
      SNS_COMMON_MSG_1(ERROR, "Cannot register for notify  err %d", qmi_err);
      return SMR_XPORT_ERR;
      /* At timeout, we shall clean up anyways*/
    }
  }
  else
  {
    /* Call the call back immediately*/
    SNS_COMMON_MSG_0(HIGH, "client_check - service exists, calling callback");
    cb_func(serviceObj, instanceID, FALSE);
  }

  return SMR_NO_ERR;
}

smr_busy_client_s* smr_find_busy_client(qmi_client_handle client)
{
  uint8_t os_err;
  smr_busy_client_s* busy_client;
  qmi_client_handle client_to_find = client;

  // Search through the sns_smr_busy_clients_q queue for the client
  sns_os_mutex_pend(sns_smr_busy_clients_q.mutex_ptr, 0, &os_err );
  busy_client = (smr_busy_client_s*) sns_q_linear_search(&sns_smr_busy_clients_q.protected_q,
                                                         smr_compare_client_handles,
                                                         (void*) &client_to_find);
  sns_os_mutex_post(sns_smr_busy_clients_q.mutex_ptr);

  return busy_client;
}

/**
* @brief
* Cleanup any state before closing the service
*/
sns_err_code_e sns_smr_close (void)
{
  SNS_COMMON_MSG_0(HIGH, "SMR close");
  return SNS_SUCCESS;
}

/**
* @brief
* Main SMR task loop
*/
void sns_smr_task(void* p_arg)
{
  uint8_t   err;
  uint8_t   i;
  OS_FLAGS  sig_flags;
  OS_FLAGS  smr_all_sigs = SMR_ALL_SIGS;
  qmi_csi_error qmi_err;

  sns_smr_task_init();
  /* This is a tricky call - and requires hidden knowledge - plan to change
     The uimg utils should not be initialized until the memory manager is
     initilized && the Power manager is initalized. This can probably be movied
     to sns_init - but keeping it here for now.
  */
  sns_uimg_utils_init();

  smr_services.smr_flag_grp = sns_os_sigs_create(0, &err);
  SNS_ASSERT(NULL != smr_services.smr_flag_grp);

  sns_os_sigs_add(smr_services.smr_flag_grp, SMR_ALL_SERVICES_SIGS);

  sns_init_done();

/* ========================= MAIN TASK LOOP ===============================*/
  while (1)
  {
    sig_flags = sns_os_sigs_pend(smr_services.smr_flag_grp,
                                 smr_all_sigs,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                 0,
                                 &err);
    if (sig_flags & SMR_SVC_CHECK_RESULT_SIG)
    {
      sig_flags &= ~SMR_SVC_CHECK_RESULT_SIG;
      sns_smr_process_svc_check_result_sig();
    }
    for (i = 0; i < SMR_MAX_SERVICES && sig_flags != 0; i++)
    {
      if (sig_flags & (1<<i))
      {
        /* Handle service */
        SNS_COMMON_MSG_1(LOW, "Signal set for service %d", i);
        if (smr_services.services[i])
        {
          qmi_err = qmi_csi_handle_event(smr_services.services[i]->service_provider,
                                         &smr_services.services[i]->os_params);
          if ( qmi_err != QMI_NO_ERR )
          {
            SNS_COMMON_MSG_2(ERROR, "handle_event error %d, service %d", qmi_err, i);
          }
        }
        else
        {
          SNS_COMMON_MSG_1(ERROR, "Service %d not registered", i);
        }
        sig_flags &=  ~(1<<i);
      }
    }
  } /* while */
}


/**
* @brief
* Entry point to SMR
*/
sns_err_code_e sns_smr_init (void)
{
  SNS_COMMON_MSG_0(HIGH, "SMR Init");
  sns_os_task_create_ext(sns_smr_task,
                         NULL,
                         NULL,
                         SNS_MODULE_PRI_DSPS_SMR,
                         SNS_MODULE_PRI_DSPS_SMR,
                         NULL,
                         SNS_MODULE_STK_SIZE_DSPS_SMR,
                         (void *)0,
                         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR,
                         (uint8_t *)"SNS_SMR");

  return SNS_SUCCESS;
}

void sns_usmr_set_disable_ext_ind(bool drop_ind)
{
  sns_usmr_drop_indications = drop_ind;
}
