#ifndef GLINK_INTERNAL_H
#define GLINK_INTERNAL_H

/*===========================================================================

                    GLink Core Internal Header File


-----------------------------------------------------------------------------
Copyright (c) 2014 QUALCOMM Technologies Incorporated
-----------------------------------------------------------------------------
===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/07/14   bm      Initial version. 
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "smem_list.h"
#include "glink.h"
#include "glink_os.h"
#include "glink_core_if.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
                        FEATURE DEFINITIONS
===========================================================================*/
#define GLINK_VERSION 0
#define GLINK_FEATURE_FLAGS 0

/*===========================================================================
                           MACRO DEFINITIONS
===========================================================================*/
#define GLINK_LOG_EVENT(type, ch_name, xport, remote_ss, param) \
  glink_mem_log(__FUNCTION__, __LINE__, type, ch_name, xport, remote_ss, param);

#define GLINK_MEM_LOG_SIZE 128

/*===========================================================================
                           TYPE DEFINITIONS
===========================================================================*/
typedef enum {
  GLINK_EVENT_INIT,
  GLINK_EVENT_REGISTER_XPORT,
  GLINK_EVENT_CH_OPEN,
  GLINK_EVENT_CH_CLOSE,
  GLINK_EVENT_CH_TX,
  GLINK_EVENT_CH_Q_RX_INTENT,
  GLINK_EVENT_CH_RX_DONE,
  GLINK_EVENT_LINK_UP,
  GLINK_EVENT_RX_CMD_VER,
  GLINK_EVENT_RM_CH_OPEN,
  GLINK_EVENT_CH_OPEN_ACK,
  GLINK_EVENT_CH_CLOSE_ACK,
  GLINK_EVENT_CH_REMOTE_CLOSE,
  GLINK_EVENT_CH_STATE_TRANS,
  GLINK_EVENT_CH_INTENT_PUT,
  GLINK_EVENT_CH_RX_DATA,
  GLINK_EVENT_CH_RX_DATA_FRAG,
  GLINK_EVENT_CH_TX_DONE,
  GLINK_EVENT_XPORT_INTERNAL,
}glink_log_event_type;

typedef struct {
  /* Link needed for use with list APIs.  Must be at the head of the struct */
  smem_list_link_type    link;
  
  void       *data;      /* Pointer to the data buffer to be transmitted */
  const void *pkt_priv;  /* Per packet private data */
  size_t     size;       /* Size of data buffer */
  size_t     used;       /* Actual valid data in *data field */
  size_t     pkt_sz;     /* Size of the packet */
  uint32     iid;        /* Intent ID */
}glink_rx_intent_type;


typedef struct glink_channel_ctx {
  /* Link needed for use with list APIs.  Must be at the head of the struct */
  smem_list_link_type          link;
  
  /* Channel name */
  char                         name[GLINK_CH_NAME_LEN];

  /* Local channel ID */
  uint32                       lcid;

  /* Remote Channel ID */
  uint32                       rcid;

  /* Channel state */
  glink_ch_state_type          state;

  /*Critical section to protest access to intent queues */
  glink_os_cs_type             intent_q_cs;

  /* Linked list of remote Rx intents. Data can be transmitted only when 
   * remote intents are available */
  smem_list_type               remote_intent_q;

  /* Linked list of remote Rx intents which local GLink core has used to 
   * transmit data, and are pending Tx complete */
  smem_list_type               remote_intent_pending_tx_q;

  /* Linked list of local Rx intents. Data can be received only when 
   * local intents are available */
  smem_list_type               local_intent_q;
  
  /* Linked list of remote Rx intents held by the clients */
  smem_list_type               local_intent_client_q;

  /* Read intent being gathered */
  glink_rx_intent_type         *cur_read_intent;
  
  /* Interface pointer with with this channel is registered */
  glink_transport_if_type      *if_ptr; 

  /** Private data for client to maintain context. This data is passed back
   * to client in the notification callbacks */
  const void                   *priv;

  /** Data receive notification callback */
  glink_rx_notification_cb     notify_rx;

  /** Data transmit notification callback */
  glink_tx_notification_cb     notify_tx_done;

  /** GLink channel state notification callback */
  glink_state_notification_cb  notify_state;
  
}glink_channel_ctx_type;


typedef struct _glink_mem_log_entry_type {
  const char *func;
  uint32 line;
  glink_log_event_type type; 
  const char *msg;
  const char *xport;
  const char *remote_ss;
  union {
    glink_err_type status;
    uint32 param;
  };
} glink_mem_log_entry_type;

/*===========================================================================
                              GLOBAL DATA DECLARATIONS
===========================================================================*/
extern void *glink_transport_q_cs;

/*===========================================================================
                    LOCAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/
/*===========================================================================
FUNCTION      glink_link_up

DESCRIPTION   Indicates that transport is now ready to start negotiation 
              using the v0 configuration

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge
                         
RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_link_up
(
  glink_transport_if_type *if_ptr
);

/*===========================================================================
FUNCTION      glink_rx_cmd_version

DESCRIPTION   Receive transport version for remote-initiated version 
              negotiation

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            version  Remote Version

            features Remote Features

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_version
(
  glink_transport_if_type *if_ptr,
  uint32                  version,
  uint32                  features
);

/*===========================================================================
FUNCTION      glink_rx_cmd_version_ack

DESCRIPTION   Receive ACK to previous glink_transport_if::tx_cmd_version 
              command

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            version  Remote Version

            features Remote Features
                         
RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_version_ack
(
  glink_transport_if_type *if_ptr,
  uint32                  version,
  uint32                  features
);

/*===========================================================================
FUNCTION      glink_rx_cmd_ch_remote_open

DESCRIPTION   Receive remote channel open request; Calls 
              glink_transport_if:: tx_cmd_ch_remote_open_ack as a result

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            rcid     Remote Channel ID

            *name    String name for logical channel
                         
RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_ch_remote_open
(
  glink_transport_if_type *if_ptr,
  uint32                  rcid,
  const char              *name
);

/*===========================================================================
FUNCTION      glink_rx_cmd_ch_open_ack

DESCRIPTION   This function is invoked by the transport in response to 
              glink_transport_if:: tx_cmd_ch_open

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            lcid     Local Channel ID

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_ch_open_ack
(
  glink_transport_if_type *if_ptr,
  uint32                  lcid
);

/*===========================================================================
FUNCTION      glink_rx_cmd_ch_close_ack

DESCRIPTION   This function is invoked by the transport in response to 
              glink_transport_if_type:: tx_cmd_ch_close

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            lcid      Local Channel ID

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_ch_close_ack
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  lcid     /* Local channel ID */
);

/*===========================================================================
FUNCTION      glink_rx_cmd_ch_remote_close

DESCRIPTION   Remote channel close request; will result in sending 
              glink_transport_if_type:: tx_cmd_ch_remote_close_ack

ARGUMENTS   *if_ptr   ;Pointer to interface instance; must be unique
                      for each edge

            rcid      Remote Channel ID

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_ch_remote_close
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid     /* Remote channel ID */
);

/*===========================================================================
FUNCTION      glink_ch_state_local_trans

DESCRIPTION   Process local state transition

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge
;
            rcid      Remote Channel ID

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_ch_state_local_trans
(
  glink_transport_if_type  *if_ptr,  /* Pointer to the interface instance */
  uint32                   lcid,     /* Local channel ID */
  glink_ch_state_type      new_state /* New local channel state */
);

/*===========================================================================
FUNCTION      glink_rx_cmd_remote_rx_intent_put

DESCRIPTION   Transport invokes this call on receiving remote RX intent

ARGUMENTS   *if_ptr   Pointer to interface instance; must be unique
                      for each edge

            rcid      Remote Channel ID

            riid      Remote intent ID

            size      Size of 

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_remote_rx_intent_put
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid,    /* Remote channel ID */
  uint32                  riid,    /* Remote intent ID */
  size_t                  size     /* Size of receive intent */
);

/*===========================================================================
FUNCTION      glink_rx_cmd_rx_data

DESCRIPTION   Transport invokes this call on receiving new data packet

ARGUMENTS   *if_ptr    Pointer to interface instance; must be unique
                       for each edge

            rcid       Remote Channel ID

            liid       Local intent ID
 
            total_size Total size of the incoming packet

            *data      Data pointer to the 1st data fragment
            
            size       Size of the current fragment

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_rx_data
(
  glink_transport_if_type *if_ptr,   /* Pointer to the interface instance */
  uint32                  rcid,      /* Remote channel ID */
  uint32                  liid,      /* Local intent ID */
  size_t                  total_size,/* Total size of the incoming packet */
  const void              *data,     /* Data pointer to the 1st data fragment */
  size_t                  size       /* Size of the current fragment */
);

/*===========================================================================
FUNCTION      glink_rx_cmd_rx_data_fragment

DESCRIPTION   Transport invokes this call to inform GLink to gather the 
              remaining data packet fragments. Note that this call should be 
              preceeded by glink_core_if_type:: rx_cmd_rx_data

ARGUMENTS   *if_ptr    Pointer to interface instance; must be unique
                       for each edge

            rcid       Remote Channel ID

            liid       Local intent ID
 
            *data      Data pointer to the data fragment
            
            size       Size of the current fragment

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_rx_data_fragment
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid,    /* Remote channel ID */
  const void              *data,    /* Data pointer to the data fragment */
  size_t                  size     /* Size of the current fragment */
);

/*===========================================================================
FUNCTION      glink_rx_cmd_tx_done

DESCRIPTION   Transport invokes this call to inform GLink that remote side is
              done with previous transmitted packet.

ARGUMENTS   *if_ptr    Pointer to interface instance; must be unique
                       for each edge

            rcid       Remote Channel ID

            riid       Remote intent ID

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_rx_cmd_tx_done
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid,    /* Remote channel ID */
  uint32                  riid     /* Remote intent ID */
);

/*===========================================================================
FUNCTION      glink_tx_resume

DESCRIPTION   If transport was full and could not continue a transmit 
              operation, then it will call this function to notify the core 
              that it is ready to resume transmission.

ARGUMENTS   *if_ptr    Pointer to interface instance; must be unique
                       for each edge

RETURN VALUE  None.

SIDE EFFECTS  None
===========================================================================*/
void glink_tx_resume
(
  glink_transport_if_type *if_ptr /* Pointer to the interface instance */
);
  

/*===========================================================================
                           CHANNEL CONTEXT APIS
===========================================================================*/

/*===========================================================================
FUNCTION      glinki_ch_is_fully_opened

DESCRIPTION   Determine if both the local and remote channel state is fully
              open

ARGUMENTS     *cfg_ptr   - Pointer to channel context

RETURN VALUE  True if fully opened, false otherwise.

SIDE EFFECTS  None
===========================================================================*/
boolean glinki_ch_is_fully_opened
(
  glink_channel_ctx_type *ctx
);


/*===========================================================================
FUNCTION      glinki_ch_push_local_rx_intent

DESCRIPTION   Create and push a local receive intent to internal list

ARGUMENTS     *cfg_ptr   - Pointer to channel context

              *pkt_priv  - Client-provided opaque data

              size       - Size of Receive Intent

RETURN VALUE  Pointer to the new intent

SIDE EFFECTS  None
===========================================================================*/
glink_rx_intent_type* glinki_ch_push_local_rx_intent
(
  glink_channel_ctx_type *ctx,
  const void             *pkt_priv,
  size_t                 size
);

/*===========================================================================
FUNCTION      glinki_ch_get_local_rx_intent

DESCRIPTION   Lookup a local receive intent

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              liid        - Local Receive Intent ID

RETURN VALUE  Pointer to the intent or NULL if not match is found.

SIDE EFFECTS  None
===========================================================================*/
glink_rx_intent_type* glinki_ch_get_local_rx_intent
(
  glink_channel_ctx_type *ctx,
  uint32                 liid
);

/*===========================================================================
FUNCTION      glinki_ch_remove_local_rx_intent

DESCRIPTION   Removes Local Receive Intent ID

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              liid        - Local Receive Intent ID

RETURN VALUE  None

SIDE EFFECTS  None
===========================================================================*/
void glinki_ch_remove_local_rx_intent
(
  glink_channel_ctx_type *ctx,
  uint32                 liid
);

/*===========================================================================
FUNCTION      glinki_ch_set_local_rx_intent_notified

DESCRIPTION   Sets the state of the intent as client-notified

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              *intent_ptr - Pointer to the receive intent

RETURN VALUE  None

SIDE EFFECTS  None
===========================================================================*/
void glinki_ch_set_local_rx_intent_notified
(
  glink_channel_ctx_type *ctx,
  glink_rx_intent_type   *intent_ptr
);

/*===========================================================================
FUNCTION      glinki_ch_get_local_rx_intent_notified

DESCRIPTION   Lookup a Local Receive Intent ID that is in the client-notified 
              state

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              *ptr        - Data pointer of receive buffer from client 
                            (passed in through glink_rx_done)

RETURN VALUE  Pointer to the intent or NULL if not match is found.

SIDE EFFECTS  None
===========================================================================*/
glink_rx_intent_type* glinki_ch_get_local_rx_intent_notified
(
  glink_channel_ctx_type *ctx,
  void                   *ptr
);

/*===========================================================================
FUNCTION      glinki_ch_remove_local_rx_intent_notified

DESCRIPTION   Removes the Local Receive Intent

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              *intent_ptr - Pointer to the receive intent

RETURN VALUE  New channel context or NULL

SIDE EFFECTS  None
===========================================================================*/
glink_channel_ctx_type* glinki_ch_remove_local_rx_intent_notified
(
  glink_channel_ctx_type *ctx,
  glink_rx_intent_type   *intent_ptr
);

/*===========================================================================
FUNCTION      glinki_ch_push_remote_rx_intent

DESCRIPTION   Adds a new Remote Receive Intent

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              size        - Size of the Remote Receive Intent

RETURN VALUE  None

SIDE EFFECTS  None
===========================================================================*/
void glinki_ch_push_remote_rx_intent
(
  glink_channel_ctx_type *ctx,
  size_t                 size
);

/*===========================================================================
FUNCTION      glinki_ch_pop_remote_rx_intent

DESCRIPTION   Removes a Remote Receive Intent

ARGUMENTS     *cfg_ptr    - Pointer to channel context
 
              size        - Size of the Remote Receive Intent

              *riid_ptr   - Pointer to the Remote Receive Intent

RETURN VALUE  Standard GLink Err code.

SIDE EFFECTS  None
===========================================================================*/
glink_err_type glinki_ch_pop_remote_rx_intent
(
  glink_channel_ctx_type *ctx,
  size_t                size,
  uint32                *riid_ptr
);

/*===========================================================================
FUNCTION      glinki_ch_get_tx_pending_remote_done

DESCRIPTION   Lookup packet transmit context for a packet that is waiting for 
              the remote-done notification.

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              riid        - Remote Receive Intent ID

RETURN VALUE  Pointer to the transmit packet context or NULL if not match is 
              found.

SIDE EFFECTS  None
===========================================================================*/
glink_core_tx_pkt_type* glinki_ch_get_tx_pending_remote_done
(
  glink_channel_ctx_type *ctx,
  uint32                 riid
);

/*===========================================================================
FUNCTION      glinki_ch_remove_tx_pending_remote_done

DESCRIPTION   Removes a packet transmit context for a packet that is waiting 
              for the remote-done notification.

ARGUMENTS     *cfg_ptr    - Pointer to channel context

              *tx_pkt     - Pointer to the packet context to remove

RETURN VALUE  None

SIDE EFFECTS  None
===========================================================================*/
void glinki_ch_remove_tx_pending_remote_done
(
  glink_channel_ctx_type       *ctx,
  glink_core_tx_pkt_type       *tx_pkt
);

void glink_mem_log
(
  const char *func, 
  uint32 line,
  glink_log_event_type type, 
  const char *msg, 
  const char *xport, 
  const char *remote_ss, 
  uint32 param
);

#endif /* GLINK_INTERNAL_H */
