#ifndef __VSS_IAVSYNC_PUBLIC_IF_H__
#define __VSS_IAVSYNC_PUBLIC_IF_H__

/**
  @file vss_iavsync_public_if.h
  @brief This file contains the APR API definitions for CVD audio-video
  synchonization information.
*/

/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      The CVD_mainpage.dox file contains all file/group descriptions 
      that are in the output PDF generated using Doxygen and Latex. To edit or 
      update any of the file/group text in the PDF, edit the 
      CVD_mainpage.dox file or contact Tech Pubs.

      The above description for this file is part of the vss_iavsync_public_if 
      group description in the CVD_mainpage.dox file. 
=============================================================================*/
/*===========================================================================
Copyright (C) 2015 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

  $Header: //components/rel/avs.adsp/2.6.1/api/cvd/vss_iavsync_public_if.h#5 $
  $Author: pwbldsvc $

===========================================================================*/


#include "apr_comdef.h"

/** @addtogroup vss_iavsync_public_if
@{ */

/****************************************************************************
 * AV SYNC APIS                                                             *
 ****************************************************************************/

/**
  RX voice path audio-video syncrhonization event class. The events that
  comprise this class are:

    #VSS_IAVSYNC_EVT_RX_PATH_DELAY
*/
#define VSS_IAVSYNC_EVENT_CLASS_RX ( 0x00012EE1 )


/**
  Notifies the client of changes in the value of the RX voice path delay.
 
  @par Payload
  #vss_iavsync_evt_rx_path_delay_t

  @return
  None.

  @dependencies
  In order to receive this event, the client must first register to listen for
  the #VSS_IAVSYNC_EVENT_CLASS_RX event class with the appropriate module via the
  #VSS_INOTIFY_CMD_LISTEN_FOR_EVENT_CLASS command. In order to stop receiving this
  event the client must cancel the #VSS_IAVSYNC_EVENT_CLASS_RX event class via
  the #VSS_INOTIFY_CMD_CANCEL_EVENT_CLASS command.

  @comments
  This event is sent to the client under the following circumstances:
    -- once every time the module with which the client is registered for this
       event is started.
    -- immediately after registration, if the module is already running.
    -- subsequently whenever the value of the RX path delay changes.
*/
#define VSS_IAVSYNC_EVT_RX_PATH_DELAY ( 0x00012EE2 )

/** @brief Type definition for
 *         #vss_iavsync_evt_rx_path_delay_t.
*/
typedef struct vss_iavsync_evt_rx_path_delay_t vss_iavsync_evt_rx_path_delay_t;

#include "apr_pack_begin.h"

/** @brief Payload structure for the #VSS_IAVSYNC_EVT_RX_PATH_DELAY event.
*/
struct vss_iavsync_evt_rx_path_delay_t
{
   uint32_t delay_us;
     /**< RX voice path delay in microseconds. */
}
#include "apr_pack_end.h"
;

/****************************************************************************
 * AV SYNC TX APIS                                                          *
 ****************************************************************************/

/** @ingroup cvd_avsync_evt_class_tx
  Tx voice path audio-video syncrhonization event class. This class
  comprises one event: #VSS_IAVSYNC_EVT_TX_TIMESTAMP
*/
#define VSS_IAVSYNC_EVENT_CLASS_TX ( 0x00012EE5 )


/** @ingroup cvd_avsync_evt_tx_timestamp
  Notifies the client of AVTimer Timestamp (total TX path delay)
 
  @apr_msgpayload{vss_iavsync_evt_tx_timestamp_t}
  @wktable{weakst__vss__iavsync__evt__tx__time__stamp__t}

  @detdesc
  This event is sent to the client under the following circumstances:
    - Before sending every Tx Vocoder Packet Event.

  @return
  None.

  @dependencies
  To receive this event, the client must first register to listen for the
  #VSS_IAVSYNC_EVENT_CLASS_TX event class with the appropriate module via the
  #VSS_INOTIFY_CMD_LISTEN_FOR_EVENT_CLASS command.
  @par
  To stop receiving this event, the client must cancel the
  VSS_IAVSYNC_EVENT_CLASS_TX event class via the
  #VSS_INOTIFY_CMD_CANCEL_EVENT_CLASS command.
*/
#define VSS_IAVSYNC_EVT_TX_TIMESTAMP ( 0x00012EE6 )

/* Type definition for vss_iavsync_evt_tx_timestamp_t. */
typedef struct vss_iavsync_evt_tx_timestamp_t vss_iavsync_evt_tx_timestamp_t;

#include "apr_pack_begin.h"

/** @weakgroup vss_iavsync_evt_tx_timestamp_t
@{ */
/* Payload structure for the #VSS_IAVSYNC_EVT_TX_TIMESTAMP event.
*/
struct vss_iavsync_evt_tx_timestamp_t
{
   uint64_t timestamp_us;     /**< TX path timestamp at MIC in micrseconds. */
}
#include "apr_pack_end.h"
;

/** @} */ /* end_addtogroup vss_iavsync_public_if */

#endif /* __VSS_IAVSYNC_PUBLIC_IF_H__ */
