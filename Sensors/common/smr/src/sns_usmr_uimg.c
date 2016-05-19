/*============================================================================
  @file sns_usmr_uimg.c

  @brief Contains the implementation of the usmr interface on non ADSP
  platforms.

  The symbols defined in this file should be placed in microImage sections.

  @note QMI Error: See qmi_csi_error in qmi_csi.h

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/
#include "sns_usmr_priv.h"
#include "sns_uimg_utils.h"
#include "sns_profiling.h"
#include "sns_debug_api.h"

/*===========================================================================
  MACROS
  ===========================================================================*/

#ifdef SNS_USES_ISLAND
  #define SMR_LEAVE_ISLAND() \
    sns_utils_place_uimge_hold(SNS_UIMG_SMR)
  #define SMR_ENTER_ISLAND() \
    sns_utils_remove_uimage_hold(SNS_UIMG_SMR)
#else
  #define SMR_LEAVE_ISLAND()
  #define SMR_ENTER_ISLAND()
#endif

#define SNS_SMR_CONN_BUSY_MSG_Q_MAX 50 // 50 was arbitrarily chosen

/*===========================================================================
  GLOBAL VARIABLES
  ===========================================================================*/
smr_services_info_s smr_services;
bool sns_usmr_drop_indications = FALSE;

/**
 * Mutex protecting client_q and all entries within. Only needs to be held when:
 * - Adding, removing, or searching through the client_q
 * - Accessing or modifying client objects that do not use QMI
 *   Inversely, client objects associated with a QMI connection do not require
 *   holding this mutex.
 */
OS_EVENT *client_mutex;

/*===========================================================================
  STATIC VARIABLES
  ===========================================================================*/

/* List of all active SMR client connections. */
static struct smr_client_hndl_s *client_q = NULL;
/* Identifier to be used on the next client handle to be added to client_q */
static uint32_t next_client_id = 1;

/*===========================================================================
  STATIC FUNCTIONS
  ===========================================================================*/

/**
 * Add a new indication message intended for a busy client to the
 * sns_smr_conn_busy_msg_buf_q list.  May also involve creating and adding an
 * entry to the sns_smr_busy_clients_q list.
 *
 * @param[i] client Busy client
 * @param[i] msg_id See smr_service_send_ind
 * @param[i] ind_c_struct See smr_service_send_ind
 * @param[i] ind_c_struct_len See smr_service_send_ind
 *
 * @return SMR_CONN_BUSY_ERR Insertion successful
 *         SMR_OUT_OF_MEMORY No memory is available to store the indication
 *         SMR_XPORT_ERR No memory is available to note that the client is busy
 */
static smr_err smr_add_busy_ind(struct smr_client_hndl_s *client,
      unsigned int msg_id, void *ind_c_struct, unsigned int ind_c_struct_len)
{
  smr_err rv = SMR_CONN_BUSY_ERR;
  smr_buffered_ind_s *buffered_ind;
  void *buffered_ind_msg;
  smr_busy_client_s* busy_client;
  uint8_t os_err;

  // PEND: Consider placing this block into a function, then placing that
  //       function where it'll be protected by the
  //       sns_smr_conn_busy_msg_buf_q mutex

  busy_client = smr_find_busy_client(client->qmi_client_conn_handle);
  if (NULL == busy_client)
  {
    SNS_COMMON_MSG_1(HIGH, "Adding a newly busy-client 0x%x to the queue.",
        client->qmi_client_conn_handle);

    busy_client = SNS_OS_MALLOC(0, sizeof(smr_busy_client_s));
    if (NULL == busy_client)
    {
      SNS_COMMON_MSG_1(ERROR,
          "NO MEMORY to add the busy-client 0x%x to the queue!",
          client->qmi_client_conn_handle);
      rv = SMR_OUT_OF_MEMORY;
    }
    else
    {
      sns_q_link(busy_client, &busy_client->q_link);
      busy_client->qmi_client_conn_handle = client->qmi_client_conn_handle;

      sns_os_mutex_pend(sns_smr_busy_clients_q.mutex_ptr, 0, &os_err );
      sns_q_put(&sns_smr_busy_clients_q.protected_q, &busy_client->q_link);
      sns_os_mutex_post(sns_smr_busy_clients_q.mutex_ptr);
    }
  }
  else
  {
    buffered_ind = SNS_OS_MALLOC(0, sizeof(smr_buffered_ind_s));
    buffered_ind_msg = SNS_OS_MALLOC(0, ind_c_struct_len);
    if (NULL == buffered_ind || NULL == buffered_ind_msg)
    {
      SNS_COMMON_MSG_2(ERROR,
          "NO MEMORY to buffer message buf_ind 0x%x, buf_ind_msg 0x%x",
          buffered_ind, buffered_ind_msg);

      SNS_OS_FREE(buffered_ind);
      SNS_OS_FREE(buffered_ind_msg);
      rv = SMR_OUT_OF_MEMORY;
    }
    else
    {
      sns_q_link(buffered_ind, &buffered_ind->q_link);

      SNS_OS_MEMSCPY(buffered_ind_msg, ind_c_struct_len,
          ind_c_struct, ind_c_struct_len);

      buffered_ind->qmi_client_conn_handle = client->qmi_client_conn_handle;
      buffered_ind->msg_id = msg_id;
      buffered_ind->ind_c_struct = buffered_ind_msg;
      buffered_ind->ind_c_struct_len = ind_c_struct_len;

      sns_os_mutex_pend(sns_smr_conn_busy_msg_buf_q.mutex_ptr, 0, &os_err );
      sns_q_put(&sns_smr_conn_busy_msg_buf_q.protected_q, &buffered_ind->q_link);
      sns_os_mutex_post(sns_smr_conn_busy_msg_buf_q.mutex_ptr);
    }
  }

  return rv;
}

/*===========================================================================
  PUBLIC FUNCTIONS
  ===========================================================================*/

bool smr_is_valid_service(int8_t service_idx)
{
  if (service_idx < 0 || service_idx > SMR_MAX_SERVICES - 1 ||
      !smr_services.services[ service_idx ])
  {
    return false;
  }
  else
  {
    return true;
  }
}

struct smr_client_hndl_s *smr_find_client(uint32_t client_id)
{
  struct smr_client_hndl_s *curr;

  for(curr = client_q; NULL != curr; curr = curr->next)
  {
    if(curr->client_id == client_id)
    {
      return curr;
    }
  }

  return NULL;
}

void smr_remove_client(uint32_t client_id)
{
  struct smr_client_hndl_s *curr, *prev;

  for(curr = client_q, prev = NULL; NULL != curr; prev = curr, curr = curr->next)
  {
    if(curr->client_id == client_id)
    {
      if(NULL == prev)
      {
        client_q = curr->next;
      }
      else
      {
        prev->next = curr->next;
      }
      break;
    }
  }
}

void smr_add_client(struct smr_client_hndl_s *client)
{
  client->client_id = next_client_id++;
  client->next = client_q;
  client_q = client;
}

void smr_remove_service(const uint32_t smr_idx)
{
  struct smr_client_hndl_s *client, *curr_client;

  for(client = client_q; NULL != client; )
  {
    curr_client = client;
    client = client->next;

    if(smr_idx == curr_client->smr_idx)
    {
      // PEND: Remove outstanding requests for this client
      smr_remove_client(curr_client->client_id);
      // PEND: Send error callback (need to save err_cb in smr_client_hndl_s)
      SNS_OS_ANY_FREE(curr_client);
    }
  }
}

smr_err smr_service_send_ind(smr_qmi_client_handle client_id,
                             unsigned int msg_id,
                             void *ind_c_struct,
                             unsigned int ind_c_struct_len)
{
  qmi_client_error_type qmi_err = QMI_NO_ERR;
  smr_err err = SMR_NO_ERR;
  struct smr_client_hndl_s *client;

  sns_os_mutex_pend(client_mutex, 0, NULL);
  client = smr_find_client((uint32_t)client_id);

  if (NULL != client)
  {
    if (smr_is_valid_service(client->smr_idx))
    {
      client->cb_ptr(client, msg_id, ind_c_struct,
          ind_c_struct_len, client->cb_data);
    }
    else if (!sns_usmr_drop_indications)
    {
      SMR_LEAVE_ISLAND();
      sns_profiling_log_qdss(SNS_USMR_EXT_IND_SEND, 2, msg_id, ind_c_struct_len);

      if (NULL != smr_find_busy_client(client->qmi_client_conn_handle))
      {
        SNS_COMMON_MSG_1(HIGH, "Client 0x%x is already busy!",
            client->qmi_client_conn_handle);
        qmi_err = QMI_CSI_CONN_BUSY;
      }
      else
      {
        qmi_client_handle qmi_handle = client->qmi_client_conn_handle;
        sns_os_mutex_post(client_mutex);
        qmi_err = qmi_csi_send_ind(qmi_handle,
            msg_id, ind_c_struct, ind_c_struct_len);
         sns_os_mutex_pend(client_mutex, 0, NULL);
         client = smr_find_client((uint32_t)client_id);
      }

      if (QMI_CSI_CONN_BUSY == qmi_err && NULL != client)
      {
        SNS_COMMON_MSG_3(HIGH,
            "CONN_BUSY client_handle %d, msg_id %d, msg_size %d",
            client, msg_id, ind_c_struct_len);

        /* If the conn_busy_msg_q's size is too big, then do not buffer the
          indication. Instead, allow the indication to drop.

          Note: The sns_q_cnt call is not protected here because it is only
                reading the count. It could result in the queue adding slightly
                more indications than allowed, SNS_SMR_CONN_BUSY_MSG_Q_MAX, but
                would not be a fatal issue. */
        if ( sns_q_cnt(&sns_smr_conn_busy_msg_buf_q.protected_q) >=
            SNS_SMR_CONN_BUSY_MSG_Q_MAX )
        {
          SNS_COMMON_MSG_1(ERROR,
                    "Dropping indication! conn_busy_msg_buf_cnt %d",
                    sns_q_cnt(&sns_smr_conn_busy_msg_buf_q.protected_q));
          err = SMR_OUT_OF_MEMORY;
        }
        else
        {
          err = smr_add_busy_ind(client, msg_id, ind_c_struct, ind_c_struct_len);
        }
      }
      else if (QMI_NO_ERR != qmi_err)
      {
        SNS_COMMON_MSG_3(ERROR, "Send IND handle %d, msg_id %d, err %d",
            client, msg_id, qmi_err);
        err = SMR_XPORT_ERR;
      }
      SMR_ENTER_ISLAND();
    }
  }
  sns_os_mutex_post(client_mutex);

  return err;
}
