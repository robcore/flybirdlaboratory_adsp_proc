#ifndef GLINK_H
#define GLINK_H

/**
 * @file glink.h
 *
 * Public API for the GLink
 */

/** \defgroup glink GLink
 * \ingroup SMD
 *
 * GLink reliable, in-order, datagram-based interprocessor communication
 * over a set of supported transport (Shared Memory, UART, BAM, HSIC)
 *
 * All ports preserve message boundaries across the interprocessor channel; one
 * write into the port exactly matches one read from the port.
 */
/*@{*/

/*==============================================================================
     Copyright (c) 2014 QUALCOMM Technologies Incorporated.
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/mproc/glink.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/22/14   bm      Initial release of GLink API
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "comdef.h"
#include "stddef.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/
/** GLink status/return codes */
typedef enum {
  GLINK_STATUS_SUCCESS = 0,
  GLINK_STATUS_FAILURE,
  GLINK_STATUS_INVALID_PARAM,
  GLINK_STATUS_NOT_INIT,
  GLINK_STATUS_OUT_OF_RESOURCES,
  GLINK_STATUS_NO_TRANSPORT  
}glink_err_type;

/** List of possible suvsystems */
/**
  "apss"   Application Processor Subsystem
  "dsps"   Sensors Processor
  "lpass"  LPASS (Low Power Audio Subsystem)
  "mpss"   Modem subsystem
  "rpm"    Power processor
  "wcnss"  Wireless Connectivity Subsystem
*/

/** Max allowed channel name length */
#define GLINK_CH_NAME_LEN 32

/*===========================================================================
                      TYPE DECLARATIONS
===========================================================================*/

/** 
 * Opaque handle returned by glink_open. Client uses this handle to call into
 * GLink API for any further activity related to the channel,
 *
 * Client must to modify or try to interpret this value 
 */
typedef struct glink_channel_ctx * glink_handle_type;

/** GLink logical link state notifications */
typedef enum {
  /** Channel is fully opened. Both local and remote end have
      opened channel from their respective ends, and data communication
      can now take place */
  GLINK_CONNECTED = 0,

  /** Local side has called glink_close() and remote side has acknowledged
      this end's close. Client may call glink_open() after this point */
  GLINK_L_DISCONNECTED,

  /** Remote side has called glink_close() to close the channel */
  GLINK_R_DISCONNECTED
}glink_channel_event_type;

/** Data receive notification callback type*/  
typedef void (*glink_rx_notification_cb)
(
  glink_handle_type handle,     /* handle for the glink channel */
  const void        *priv,      /* priv client data passed in glink_open */
  const void        *pkt_priv,  /* private client data assiciated with the
                                   rx intent that client queued earlier */
  const void        *ptr,       /* pointer to the received buffer */
  size_t            size        /* size of the packet */
);

/** Data transmit notification callback type*/  
typedef void (*glink_tx_notification_cb)
(
  glink_handle_type handle,    /* handle for the glink channel */
  const void        *priv,     /* priv client data passed in glink_open */
  const void        *pkt_priv, /* private client data assiciated with the
                                  tx pkt that client queued earlier */
  const void        *ptr,      /* pointer to the transmitted buffer */
  size_t            size       /* size of the packet */
);

/** GLink channel state change notification callback type*/  
typedef void (*glink_state_notification_cb)
(
  glink_handle_type         handle, /* handle for the glink channel */
  const void                *priv,  /* priv client data passed in glink_open */
  glink_channel_event_type  event   /* Notification event */
);

/**
 * Data Structure for GLink logical channel open configuration
 *
 * This structure is used by the clients to open a GLink logical channel
 * when calling glink_open()
 */
typedef struct {
  /** string name for the transport to use (Optional)*/
  const char                   *transport;

  /** string name for the remote subsystem to which the user wants to 
      connect */
  const char                   *remote_ss;

  /** string name for the channel */
  const char                   *name;

  /** Private data for client to maintain context. This data is passed back
      to client in the notification callbacks */
  const void                   *priv;

  /** Data receive notification callback */
  glink_rx_notification_cb     notify_rx;

  /** Data transmit notification callback */
  glink_tx_notification_cb     notify_tx_done;

  /** GLink channel state notification callback */
  glink_state_notification_cb  notify_state;

}glink_open_config_type;

/*===========================================================================
                      GLINK PUBLIC API
===========================================================================*/
/** 
 * Opens a logical GLink based on the specified config params
 *
 * @param[in]    cfg_ptr  Pointer to the configuration structure for the
 *                        GLink. See glink.h
 * @param[out]   handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Allocates channel resources and informs remote host about
 *               channel open.
 */
glink_err_type glink_open
(
  glink_open_config_type *cfg_ptr,
  glink_handle_type      *handle
);

/** 
 * Closes the GLink logical channel specified by the handle.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Closes local end of the channel and informs remote host
 */
glink_err_type glink_close
(
  glink_handle_type handle
);

/** 
 * Transmit the provided buffer over GLink.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv Per packet private data
 *
 * @param[in]   *data     Pointer to the data buffer to be transmitted
 *
 * @param[in]   size      Size of buffer
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Causes remote host to wake-up and process rx pkt
 */
glink_err_type glink_tx
(
  glink_handle_type handle,
  const void        *pkt_priv,
  const void        *data,
  size_t            size
);

/** 
 * Queue one or more Rx intent for the logical GPIC Link channel.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv Per packet private data
 *
 * @param[in]   size      Size of buffer
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  GLink XAL allocates rx buffers for receiving packets
 */
glink_err_type glink_queue_rx_intent
(
  glink_handle_type handle,
  const void        *pkt_priv,
  size_t            size
);

/** 
 * Client uses this to signal to GLink layer that it is done with the received 
 * data buffer. This API should be called to free up the receive buffer, which,
 * in zero-copy mode is actually remote-side's transmit buffer.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @param[in]   *ptr      Pointer to the received buffer
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  GLink XAL frees the Rx buffer
 */
glink_err_type glink_rx_done
(
  glink_handle_type handle,
  const void        *ptr
);

#endif //GLINK_H
