#ifndef _SNS_USMR_PRIV_H
#define _SNS_USMR_PRIV_H
/*============================================================================
  @file sns_usmr_priv.h

  @brief Contains type definitions and function declarations that are only used
  internally by the uImage SMR.

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/
#include "sns_usmr.h"
#include "sns_queue.h"
#include "sns_memmgr.h"

/*===========================================================================
  MACROS
  ===========================================================================*/

/* Maximum number of services that may be registered with SMR */
#define SMR_MAX_SERVICES 24
#define SMR_ALL_SERVICES_SIGS    0x00FFFFFF

/*===========================================================================
  TYPE DEFINITIONS
  ===========================================================================*/

/**
 * Represents a particular client-service connection.  To be used by clients
 * to send requests over an open connection, and for services to send
 * indication messages.  Every connection, regardless of whether it uses QMI,
 * will have an associated client handle object.  Each client handle will be
 * included on the client_q list.
 */
struct smr_client_hndl_s
{
  /* Next client on the client_q; or NULL if last */
  struct smr_client_hndl_s    *next;
  /* Unique identifier of this client */
  uint32_t                    client_id;

  qmi_idl_service_object_type service_obj;
  qmi_client_type             qmi_client;
  qmi_client_handle           qmi_client_conn_handle;
  smr_client_ind_cb           cb_ptr;
  void                        *cb_data;
  qmi_client_os_params        os_params;
  int8_t                      smr_idx;
  void                        *connection_handle;
  void                        *release_cb_data;
  smr_client_release_cb       release_cb;
  /* Outstanding request messages; only used for SMR-bypass clients */
  struct smr_req_handle_s     *req_q;
};

/**
 * An outstanding request, received by a service.  This handle shall be
 * used by the service to send the appropriate response message.  Note that
 * the response message will not be sent to the client, if the client has
 * already disconnected.
 */
struct smr_req_handle_s
{
  struct smr_req_handle_s *next;
  int8_t                  smr_idx;
  smr_client_resp_cb      resp_cb;
  void                    *resp_cb_data;
  uint32_t                client_id;
  qmi_req_handle          req_handle;
  void                    *resp_c_struct;
  unsigned int            resp_c_struct_len;
};

/**
 * A particular service registered with SMR.
 */
struct smr_service_hndl_s
{
  qmi_idl_service_object_type service_obj;
  qmi_service_instance        instance_id;
  qmi_csi_service_handle      service_provider;
  qmi_csi_os_params           os_params;
  smr_service_connect         connect_cb;
  smr_service_disconnect      disconnect_cb;
  smr_process_req             process_req_cb;
  smr_resume_ind              resume_ind_cb;
  void                        *service_cookie;
  int8_t                      smr_idx;
};

typedef struct
{
   //OS signals
   OS_FLAG_GRP      *smr_flag_grp;
   OS_FLAGS         smr_flags;

   //Services already used
   smr_service_hndl services[ SMR_MAX_SERVICES ];
}smr_services_info_s;

typedef struct
{
  sns_q_s   protected_q;
  OS_EVENT* mutex_ptr;
} sns_smr_protected_q_s;

typedef struct
{
  sns_q_link_s        q_link;
  qmi_client_handle   qmi_client_conn_handle;
  unsigned int        msg_id;
  /* Note: The ind_c_struct must be malloc'ed and freed in addition to this
   *       entire structure! */
  void                *ind_c_struct;
  unsigned int        ind_c_struct_len;
} smr_buffered_ind_s;

typedef struct
{
  sns_q_link_s        q_link;
  qmi_client_handle   qmi_client_conn_handle;
} smr_busy_client_s;

/*===========================================================================
  PUBLIC VARIABLE DECLARATIONS
  ===========================================================================*/

/* List of all services registered on SMR.  Note that other services may still
 * be available via QCSI. */
extern smr_services_info_s smr_services;
/* List of messages which have not been sent due to a busy and/or unresponsive
 * client.  Messages may be dropped if length exceeds
 * SNS_SMR_CONN_BUSY_MSG_Q_MAX */
extern sns_smr_protected_q_s sns_smr_conn_busy_msg_buf_q;
/* List of clients that have have too many unprocessed indication messages.
 * All indication messages to these clients are blocked until they process
 * their outstanding message queue. */
extern sns_smr_protected_q_s sns_smr_busy_clients_q;
/* Whether to drop indications destined for outside of the SSC.  This option is
 * only enabled for debugging purposes. */
extern bool sns_usmr_drop_indications;
/* Mutex protecting the client_q list, as well as all client objects.  This
 * must be held whenever a client handle is being accessed or modified. */
extern OS_EVENT *client_mutex;

/*===========================================================================
  PUBLIC FUNCTION DECLARATIONS
  ===========================================================================*/

/**
 * Determine whether the service at the given index is currently valid.
 *
 * PEND: Race condition is possible if service is unregistered.
 *
 * @param[i] service_idx Index into smr_services.services
 *
 * @return frue if value, false otherwise
 */
bool smr_is_valid_service(int8_t service_idx);

/**
 * @brief
 * Performs a linear search through the busy-clients queue to look for the
 * desired client.
 *
 * @dependencies
 * Requires the sns_smr_busy_clients_q mutex to be free in order to succeed.
 *
 * @param[i] client The QMI client handle that is being queried to see if it is
 *                  busy
 *
 * @return Pointer to the busy_client item if the client is currently busy.
 *         NULL if the client is not busy.
 */
smr_busy_client_s* smr_find_busy_client(qmi_client_handle client);

/**
 * Find the client object in client_q that has the specified ID.
 *
 * @note Must hold client_mutex.
 *
 * @param[i] client_id Globally and perpetually unique identifier
 *
 * @return Client handle if matching client_id found; NULL otherwise
 */
struct smr_client_hndl_s *smr_find_client(uint32_t client_id);

/**
 * Add a new client to the global client_q list.  No checking is performed
 * whether this client already exists.
 *
 * @note Must hold client_mutex.
 *
 * @param[i] client Client handle already initialized and ready to be added
 */
void smr_add_client(struct smr_client_hndl_s *client);

/**
 * Remove a client from the client_q list.  This should be done immediately
 * prior to freeing the client handle memory, and around the same time as
 * the release and disconnect callbacks are invoked.
 *
 * @note Must hold client_mutex.
 *
 * @param[i] client_id Globally and perpetually unique identifier
 */
void smr_remove_client(uint32_t client_id);

/**
 * Remove a service from the list of available SMR services.  Close all
 * active client connections, and void all outstanding requests.
 *
 * @param[i] smr_idx Service index as provided by sns_smr_get_new_service_sig()
 */
void smr_remove_service(const uint32_t smr_idx);

#endif
