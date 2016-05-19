#ifndef GLINK_TRANSPORT_IF_H
#define GLINK_TRANSPORT_IF_H

/**
 * @file glink_transport_if.h
 *
 * Public API for the GLink Core to transport interface
 */
/*=============================================================================
     Copyright (c) 2014 QUALCOMM Technologies Incorporated.
     All rights reserved.
     Qualcomm Confidential and Proprietary
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/glink/core/inc/glink_transport_if.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/22/14   bm      Initial release of GLink Core to transport interface.
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include "comdef.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/

/*===========================================================================
                      TYPE DECLARATIONS
===========================================================================*/
/* forward declaration */
struct glink_transport_if;
typedef struct glink_transport_if   glink_transport_if_type;

struct glink_core_xport_ctx;
typedef struct glink_core_xport_ctx glink_core_xport_ctx_type;

struct glink_core_if;
typedef struct glink_core_if        glink_core_if_type;


/** Glink core -> Xport pkt type definition */
typedef struct {
  void       *data;      /* Pointer to the data buffer to be transmitted */
  const void *pkt_priv;  /* Per packet private data */
  uint32     iid;        /* Remote intent ID being used to transmit data */
  size_t     size;       /* Size of data buffer */
  size_t     size_remaining; /* Size left to transmit */
}glink_core_tx_pkt_type;
  
/** Transmit a version command for local negotiation. The transport would call
 *  glink_transport_if_type::rx_cmd_version_ack callback as a result */
typedef void (*tx_cmd_version_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  version, /* Version */
  uint32                  features /* Features */
);

/** Transmit a version ack for remote nogotiation */
typedef void (*tx_cmd_version_ack_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  version, /* Version */
  uint32                  features /* Features */
);

/** Signals the negotiation is complete and transport can now do version
 *  specific initialization */
typedef void (*set_version_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  version, /* Version */
  uint32                  features /* Features */
);

/** Sends OPEN command to transport for transport to do whatever it deems 
 *  necessary to open a GLink logical channel.
 *  GLink Core expects glink_transport_if_type::rx_cmd_ch_open_ack to be called
 *  as a result of channel opening. */
typedef glink_err_type (*tx_cmd_ch_open_fn)
(
  glink_transport_if_type *if_ptr,/* Pointer to the interface instance */
  uint32                  lcid,   /* Local channel ID */
  const char              *name   /* String name for the logical channel */
);

/** Sends CLOSE command to transport for transport to do whatever it deems 
 *  necessary to close the specified GLink logical channel.
 *  GLink Core expects glink_transport_if_type::rx_cmd_ch_close_ack to be 
 *  called as a result of channel closing. */
typedef glink_err_type (*tx_cmd_ch_close_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                     lcid  /* Local channel ID */
);

/** Sends the remote open ACK command in response to receiving
 *  glink_core_if_type::rx_cmd_ch_remote_open */
typedef void (*tx_cmd_ch_remote_open_ack_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid     /* Remote channel ID */
);

/** Sends the remote close ACK command in response to receiving
 *  glink_core_if_type::rx_cmd_ch_remote_close */
typedef void (*tx_cmd_ch_remote_close_ack_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  rcid     /* Remote channel ID */
);

/** Send receive intent ID for a given channel */
typedef glink_err_type (*tx_cmd_local_rx_intent_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  lcid,    /* Local channel ID */
  size_t                  size,    /* Size of Rx intent */
  uint32                  liid     /* Local indent ID */
); 

/** Send receive done command for an intent for the specified channel */
typedef void (*tx_cmd_local_rx_done_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  lcid,    /* Local channel ID */
  uint32                  liid     /* Local indent ID */
);

/** Send a data packet to the transport to be transmitted over the specified
 *  channel */
typedef glink_err_type (*tx_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  uint32                  lcid,    /* Local channel ID */
  glink_core_tx_pkt_type  *pctx    /* Packet to be transmitted */
);


/**
 * Data Structure for GLink Core to call into transport API
 *
 * This structure is used by the GLink core to operate transport
 * This set of function pointers to to be filled in by the transport
 * abstraction layer.
 */
struct glink_transport_if {
  /* Link needed for use with list APIs.  Must be at the head of the struct */
  smem_list_link_type    link;
  
  /** Transmit a version command for local negotiation. The transport would 
   * call glink_transport_if_type::rx_cmd_version_ack callback as a result */
  tx_cmd_version_fn              tx_cmd_version;

  /** Transmit a version ack for remote nogotiation */
  tx_cmd_version_ack_fn          tx_cmd_version_ack;

  /** Signals the negotiation is complete and transport can now do version
   *  specific initialization */
  set_version_fn                 set_version;


  /** Sends OPEN command to transport for transport to do whatever it deems 
   *  necessary to open a GLink logical channel.
   *  GLink Core expects glink_transport_if_type::rx_cmd_ch_open_ack to be 
   *  called as a result of channel opening. */
  tx_cmd_ch_open_fn              tx_cmd_ch_open;


  /** Sends CLOSE command to transport for transport to do whatever it deems 
   *  necessary to close the specified GLink logical channel.
   *  GLink Core expects glink_transport_if_type::rx_cmd_ch_close_ack to be 
   *  called as a result of channel closing. */
  tx_cmd_ch_close_fn             tx_cmd_ch_close;


  /** Sends the remote open ACK command in response to receiving
   *  glink_core_if_type::rx_cmd_ch_remote_open */
  tx_cmd_ch_remote_open_ack_fn   tx_cmd_ch_remote_open_ack;

  /** Sends the remote close ACK command in response to receiving
   *  glink_core_if_type::rx_cmd_ch_remote_close */
  tx_cmd_ch_remote_close_ack_fn  tx_cmd_ch_remote_close_ack;


  /** Send receive intent ID for a given channel */
  tx_cmd_local_rx_intent_fn      tx_cmd_local_rx_intent;


  /** Send receive done command for an intent for the specified channel */
  tx_cmd_local_rx_done_fn        tx_cmd_local_rx_done;


  /** Send a data packet to the transport to be transmitted over the specified
   *  channel */
  tx_fn                          tx;

  /** Transport specific data pointer that transport may choose fill in
   * with some data */
  glink_core_xport_ctx_type      *glink_core_priv;

  /** GLINK core interface pointer associated with this transport interface */
  glink_core_if_type             *glink_core_if_ptr;
};

#endif //GLINK_TRANSPORT_IF_H

