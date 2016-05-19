/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                   Diag I/O Wrapper APIs for Interprocessor Communication and I/O 

General Description

Copyright (c) 2011-2014 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diagcomm_io_smdl.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/10/14   sr      Support for peripheral buffering mode  
03/05/14   xy      Fixed KW ASSERTs issue 
09/27/13   xy      Removed code under FEATURE_WINCE  
07/24/13   sr      Changed SMDL_READ_SIG to internal signal and reduced the 
                   priority over CTRl_MSG_SIG  
02/11/13   sr      Mainling Diag central routing  
07/06/12   hvm     Added support for t-put improvements with SMDL
07/05/12   sg      Changes to bring up diag Multi PD
09/28/11   is      Check if there's more data to read in diagcomm_smdl_buffer_read()
09/12/11   is      Master Diag forwards "set mask" requests via CTRL msgs
08/08/11   wjg     Modified to bring smdl_read into diag context 
03/04/11   is      Support for Diag over SMD-Lite

===========================================================================*/

  #include "customer.h"


#ifdef DIAG_SMDL_SUPPORT 

#include "diagcomm_io_smdl.h"
#include "diagcomm_io.h"         /* For diagcomm_io_conn_type */
#include "smd_lite.h"
#include "osal.h"
#include "diag.h"  
#include "diagpkt.h"             /* For DIAG_MAX_TX_PKT_SIZ */
#include "diagdsm_v.h"           /* For DSM_DIAG_SIO_RX_ITEM_POOL, etc */
#include "diagi_v.h"             /* For DIAG_SMDL_READ_SIG */
#include "diag_fwd_v.h"          /* For diag_fwd_task_tcb */
#include "assert.h"              /* For ASSERT() */
#include "diagdiag_v.h"          /* For diag_debug_log()*/
#include "diag_mode_v.h"

#if defined (DIAG_C_STRING)
#include <stringl/stringl.h>
#endif

#define DIAG_EDGE_APPS_RIVA_DATA     "APPS_RIVA_DATA"
#define DIAG_EDGE_APPS_RIVA_CTRL     "APPS_RIVA_CTRL"
#define DIAG_EDGE_APPS_QDSP_DATA     "DIAG"
#define DIAG_EDGE_APPS_QDSP_CTRL     "DIAG_CNTL"

extern diag_tx_mode_type diag_tx_mode[DIAG_MAX_STREAM_ID];

extern osal_tcb_t diag_tcb;
extern dsm_watermark_type diagcomm_smd_rx_wmq[NUM_SMD_PORTS];  /* From diagcomm_smd.c */
extern dsm_watermark_type diagcomm_smd_tx_wmq[NUM_SMD_PORTS];  /* From diagcomm_smd.c */

extern dsm_watermark_type diagcomm_ctrl_rx_wmq[NUM_SMD_PORT_TYPES][NUM_SMD_PORTS]; /* From diagcomm_ctrl.c */
extern dsm_watermark_type diagcomm_ctrl_tx_wmq[NUM_SMD_PORT_TYPES][NUM_SMD_PORTS]; /* From diagcomm_ctrl.c */

extern dsm_watermark_type diagcomm_sio_rx_wmq;  /* From diagcomm_sio.c */
extern dsm_watermark_type diagcomm_sio_tx_wmq;  /* From diagcomm_sio.c */
extern dsm_watermark_type diagcomm_sio_cmd_tx_wmq;  /* From diagcomm_sio.c */

extern diagcomm_io_conn_type diagcomm_io_conn[NUM_SMD_PORT_TYPES][NUM_SMD_PORTS]; /* From diagcomm_io.c */
extern diagcomm_io_conn_type diagcomm_io_ctrl_conn[NUM_SMD_PORT_TYPES][NUM_SMD_PORTS]; /* From diagcomm_io.c */

char diag_smdl_read_buf[SMD_STANDARD_FIFO];

uint32 diag_tx_pkt_conn_data[DIAG_TX_MAX_CHAIN_SIZ/4]; /* i.e. DIAG_MAX_TX_PKT_SIZ(0x1820)*2 to support 6k log pkts */
uint32 diag_tx_pkt_conn_ctrl[DIAG_TX_MAX_CHAIN_SIZ/4];
void diagcomm_smdl_buffer_read(void);
      
/*===========================================================================
FUNCTION DIAGCOMM_IO_SMDL_NOTIFY

DESCRIPTION

PARAMETERS
  
RETURN VALUE
  None
  
===========================================================================*/
static void diagcomm_io_smdl_notify_cb( smdl_handle_type port,
                                        smdl_event_type event,
                                        void *data )
{
  diagcomm_io_conn_type * conn = (diagcomm_io_conn_type *)data;
   
  switch( event )
  {
    case SMDL_EVENT_OPEN:
    {
      /* Received when the remote processor opens the port */
      conn->channel_connected = TRUE;
      diagcomm_io_conn_changed( conn, conn->channel_connected );
      break;
    }
    
    case SMDL_EVENT_CLOSE:
    {
      /* Received when the remote processor closes the port */
      conn->channel_connected = FALSE;
      diagcomm_io_conn_changed( conn, conn->channel_connected );
      /* Nothing happens to the local end of the connection. */
      break;
    }
    
    case SMDL_EVENT_READ:
    {
      /* Received when data is available to be read from the FIFO */
      /* Check if previous data not read */
      if( conn->data_pending == FALSE )
      {
        /* Set data pending flag for connection */
        conn->data_pending = TRUE;
        
        /* Set signal to read smdl buffer */ 
        diag_set_internal_sigs( DIAG_SMDL_READ_SIG);
      }
      else
      {
        // Did not read last message
      }
      
      break;
    }
    
    case SMDL_EVENT_WRITE:
    {
      /* Received when previous smdl_write() failed and SMDL is ready to write again.
         Reason for failure may have been pkt to be written is > than outgoing FIFO size,
         and needs to be continued */
      osal_sigs_t return_sigs;
      int return_val = 0;
      
        /* Check if previous pkt not sent completely */
        /* Set signal to write the remaining pkt */ 
        return_val = osal_set_sigs(&diag_tcb, DIAG_SMDL_WRITE_SIG, &return_sigs);
        ASSERT(OSAL_SUCCESS == return_val);
      break;
    }
    
    default:
      break;
  } /* end switch */
  
} /* diagcomm_io_smdl_notify_cb */


/*===========================================================================
FUNCTION DIAGCOMM_SMDL_OPEN_INIT

DESCRIPTION

PARAMETERS
  conn - Diag I/O connection handle
  
RETURN VALUE
  None
  
===========================================================================*/
void diagcomm_smdl_open_init( diagcomm_io_conn_type * conn )
{
  uint8 stream_index;
  
  if( conn == NULL )
    return;
  
  if( conn->port_num > DIAGCOMM_PORT_NUM_LAST )
  {
    MSG_1(MSG_SSID_DIAG, MSG_LEGACY_ERROR, "diagcomm_smdl_open_init - Invalid port_num %d", conn->port_num);
    return;
  }
  
  stream_index = DIAG_PORT_TO_INDEX(conn->port_num);

/*
  struct
  {
    const char       *name;
    smd_channel_type  edge;
    uint32            flags;
    uint32            fifo_size;
    smdl_callback_t   notify;
    void             *cb_data;
    dsm_watermark_type       *rx_queue;
    dsm_watermark_type       *tx_queue;
    dsm_mempool_id_enum_type  dsm_mempool_id;
  } smdl_params;
  
  typedef enum
  {
    SMD_CHANNEL_TYPE_FIRST,
    SMD_APPS_MODEM = SMD_CHANNEL_TYPE_FIRST,
    SMD_APPS_QDSP,
    SMD_MODEM_QDSP,
    SMD_APPS_DSPS,
    SMD_MODEM_DSPS,
    SMD_QDSP_DSPS,
    SMD_APPS_RIVA,
    SMD_MODEM_RIVA,
    SMD_QDSP_RIVA,
    SMD_DSPS_RIVA,
    SMD_CHANNEL_TYPE_LAST,
    SMD_INVALID_CHANNEL_TYPE
  } smd_channel_type;
*/
  
  conn->open_params.smdl_params.flags = SMDL_OPEN_FLAGS_NONE;
  conn->open_params.smdl_params.fifo_size = SMD_STANDARD_FIFO;
  conn->open_params.smdl_params.notify = diagcomm_io_smdl_notify_cb;
  conn->open_params.smdl_params.cb_data = conn;
  
  /* Set edge ID */
#if defined(DIAG_QDSP6_APPS_PROC)
  conn->open_params.smdl_params.edge =  SMD_APPS_QDSP;
#elif defined (DIAG_IMAGE_RIVA_PROC)
 conn->open_params.smdl_params.edge = SMD_APPS_RIVA;
#endif
  /* Set watermark queues */
  if( DIAGCOMM_IO_DATA == conn->channel_type )
  {
    #if defined(DIAG_QDSP6_APPS_PROC)
    (void)snprintf( conn->open_params.smdl_params.name,
                          DIAG_SMDL_CHANNEL_NAME_SIZE_MAX,
                          DIAG_EDGE_APPS_QDSP_DATA );
    #elif defined (DIAG_IMAGE_RIVA_PROC)
    (void)snprintf( conn->open_params.smdl_params.name,
                          DIAG_SMDL_CHANNEL_NAME_SIZE_MAX,
                          DIAG_EDGE_APPS_RIVA_DATA );
    #endif
    if( DIAGCOMM_PORT_SMD == conn->port_type )
    {
      conn->open_params.smdl_params.rx_queue = &diagcomm_smd_rx_wmq[conn->port_num];
      conn->open_params.smdl_params.tx_queue = &diagcomm_smd_tx_wmq[conn->port_num];
    }
    else
    {
      conn->open_params.smdl_params.rx_queue = &diagcomm_sio_rx_wmq;
      conn->open_params.smdl_params.tx_queue = &diagcomm_sio_tx_wmq;
      conn->open_params.smdl_params.cmd_tx_queue = &diagcomm_sio_cmd_tx_wmq;
    }
  }
  else if( DIAGCOMM_IO_CTRL == conn->channel_type )
  {
    #if defined(DIAG_QDSP6_APPS_PROC)
    (void)snprintf( conn->open_params.smdl_params.name,
                          DIAG_SMDL_CHANNEL_NAME_SIZE_MAX,
                          DIAG_EDGE_APPS_QDSP_CTRL );
    #elif defined (DIAG_IMAGE_RIVA_PROC)
                          
      (void)snprintf( conn->open_params.smdl_params.name,
                          DIAG_SMDL_CHANNEL_NAME_SIZE_MAX,
                          DIAG_EDGE_APPS_RIVA_CTRL );
    #endif                    
    conn->open_params.smdl_params.rx_queue = &(diagcomm_ctrl_rx_wmq[conn->port_type][conn->port_num]);
    conn->open_params.smdl_params.tx_queue = &(diagcomm_ctrl_tx_wmq[conn->port_type][conn->port_num]);
  }
  
  /* Set DSM pool ID */
  if( DIAGCOMM_PORT_SIO == conn->port_type )
  {
    conn->open_params.smdl_params.dsm_mempool_id = DSM_DIAG_SIO_RX_ITEM_POOL;  
  }
  else
  {
#if defined (DIAG_MP_MASTER)
	conn->open_params.smdl_params.dsm_mempool_id = DSM_DIAG_SMD_TX_ITEM_POOL;
#else
	conn->open_params.smdl_params.dsm_mempool_id = diag_tx_mode[stream_index].pool_info.pool_id;
#endif
  }

} /* diagcomm_smdl_open_init */


/*===========================================================================

FUNCTION DIAG_SMDL_BUFFER_READ

DESCRIPTION
  This function reads data from a smdl connection. It is called when data 
  is available to be read from a smdl FIFO.

PARAMETERS
  None
  
RETURN VALUE
  None
  
===========================================================================*/
void
diagcomm_smdl_buffer_read(void)
{
  diagcomm_io_conn_type * conn = NULL;
  int32 read_len = 0;
  dsm_item_type *dsm_item_ptr = NULL;
  osal_sigs_t return_sigs;
  int return_val = 0;
  int i, j;
  
  for (i = 0; i < NUM_SMD_PORT_TYPES; i++)
  {
    for (j = 0; j < NUM_SMD_PORTS; j++)
    {
      conn = &diagcomm_io_conn[i][j];
      if( conn->io_type == DIAGCOMM_IO_TYPE_SMDL )
      {
        /* Check for data to be read */
        if (conn->data_pending == TRUE)
        {
          read_len = smdl_read( conn->handle.smdl_handle, SMD_STANDARD_FIFO, &diag_smdl_read_buf, SMDL_READ_FLAGS_NONE );
          if( read_len > 0 )
          {
            if( dsm_pushdown_tail(&dsm_item_ptr, &diag_smdl_read_buf, read_len, 
                                  conn->open_params.smdl_params.dsm_mempool_id) == read_len )
            { 
              dsm_enqueue( conn->open_params.smdl_params.rx_queue, &dsm_item_ptr );
              if( DIAGCOMM_IO_CTRL == conn->channel_type )
              {
                /* Set signal to diag task to process ctrl traffic from slave */
                 diag_set_internal_sigs( DIAG_CTRL_MSG_SIG);
              }
              else if( (DIAGCOMM_IO_DATA == conn->channel_type) && (DIAGCOMM_PORT_SMD == conn->port_type) )
              {
                /* Set signal to diag task to process traffic from slave */
                return_val = osal_set_sigs( &diag_fwd_task_tcb, DIAG_TX_SLAVE_SIG, &return_sigs );
                ASSERT(OSAL_SUCCESS == return_val);
              }
              else if( (DIAGCOMM_IO_DATA == conn->channel_type) && (DIAGCOMM_PORT_SIO == conn->port_type) )
              {
                //diag_rx_notify();
                return_val = osal_set_sigs( &diag_tcb, DIAG_RX_SIG, &return_sigs );
                ASSERT(OSAL_SUCCESS == return_val);
              }
            }
            else
            {
              dsm_free_packet( &dsm_item_ptr );
            }
          }
    
          /* Check if there's more data to be read */
          if( smdl_rx_peek(conn->handle.smdl_handle) > 0 )
          {
             diag_set_internal_sigs( DIAG_SMDL_READ_SIG);
          }
          else
          {
            conn->data_pending = FALSE;
          }
        }
      }

      conn = &diagcomm_io_ctrl_conn[i][j];
      if( conn->io_type == DIAGCOMM_IO_TYPE_SMDL )
      {
        /* Check for ctrl data to be read */
        if (conn->data_pending == TRUE)
        {
          read_len = smdl_read( conn->handle.smdl_handle, SMD_STANDARD_FIFO, &diag_smdl_read_buf, SMDL_READ_FLAGS_NONE );
          if( read_len > 0 )
          {
            if( dsm_pushdown_tail(&dsm_item_ptr, &diag_smdl_read_buf, read_len, 
                                  conn->open_params.smdl_params.dsm_mempool_id) == read_len )
            { 
              dsm_enqueue( conn->open_params.smdl_params.rx_queue, &dsm_item_ptr );
              if( DIAGCOMM_IO_CTRL == conn->channel_type )
              {
                /* Set signal to diag task to process ctrl traffic from slave */
                diag_set_internal_sigs( DIAG_CTRL_MSG_SIG);
              }
              else if( (DIAGCOMM_IO_DATA == conn->channel_type) && (DIAGCOMM_PORT_SMD == conn->port_type) )
              {
                /* Set signal to diag task to process traffic from slave */
                return_val = osal_set_sigs( &diag_fwd_task_tcb, DIAG_TX_SLAVE_SIG, &return_sigs );
                ASSERT(OSAL_SUCCESS == return_val);
              }
              else if( (DIAGCOMM_IO_DATA == conn->channel_type) && (DIAGCOMM_PORT_SIO == conn->port_type) )
              {
                //diag_rx_notify();
                return_val = osal_set_sigs( &diag_tcb, DIAG_RX_SIG, &return_sigs );
                ASSERT(OSAL_SUCCESS == return_val);
              }
            }
            else
            {
              dsm_free_packet( &dsm_item_ptr );
            }
          }
    
          /* Check if there's more data to be read */
          if( smdl_rx_peek(conn->handle.smdl_handle) > 0 )
          {
            diag_set_internal_sigs( DIAG_SMDL_READ_SIG);
            ASSERT(OSAL_SUCCESS == return_val);
          }
          else
          {
            conn->data_pending = FALSE;
          }
        }
      }
    } /* END for NUM_SMD_PORTS */
  } /* END for NUM_SMD_PORT_TYPES */
  
} /* diagcomm_smdl_buffer_read */


/*===========================================================================

FUNCTION DIAGCOMM_IO_SMDL_SEND

DESCRIPTION
  This function writes data to a smdl connection. It is called when data 
  is already enqueued in the Tx WMQ of the data/ctrl channel.

PARAMETERS
  conn - Diag I/O connection handle
  
RETURN VALUE
  None
  
===========================================================================*/
void diagcomm_io_smdl_send ( diagcomm_io_conn_type * conn, boolean is_cmd_rsp_type )
{
  uint32 total_pkt_length = 0;
  int32 smdl_writev_ret=0;  
  dsm_item_type * diag_tx_dsm_ptr = NULL;

  /* Sanity check for conn */
  if( conn == NULL )
    return;

  if( conn->channel_connected == 0)
  {
    return;
  }

  if( is_cmd_rsp_type )
  {
    // Check if Tx WMQ is empty & prev tx was complete
    if( (dsm_is_wm_empty(conn->open_params.smdl_params.cmd_tx_queue) && !conn->diag_prev_tx_pending) )
    {
      return;
    }
  }
  else
  {
    if( (dsm_is_wm_empty(conn->open_params.smdl_params.tx_queue) && !conn->diag_prev_tx_pending ))
    {
      return;
    }
  }

  /* dequeue new dsm item and update iovec_ptr only when previous Tx was complete */
  if( ! conn->diag_prev_tx_pending )
  {  
    diag_tx_dsm_ptr = diagcomm_io_dequeue_tx_wmq(conn, is_cmd_rsp_type);
    ASSERT ( diag_tx_dsm_ptr != NULL );
    /* dsm_length_packet() provides length of entire packet if DSMs are chained */
    total_pkt_length = dsm_length_packet(diag_tx_dsm_ptr);

    conn->diag_tx_iovec.length = total_pkt_length;
    conn->diag_tx_iovec.next = NULL;

    if (conn->channel_type == DIAGCOMM_IO_DATA )
    {
      /* Check if pkt fits into the diag_tx_pkt before dsm_pullup_tail() */
      ASSERT( total_pkt_length <= sizeof(diag_tx_pkt_conn_data));
      dsm_pullup_tail(&diag_tx_dsm_ptr, &diag_tx_pkt_conn_data, total_pkt_length);
      conn->diag_tx_iovec.buffer = &diag_tx_pkt_conn_data;
    }
    if (conn->channel_type == DIAGCOMM_IO_CTRL )
    {
      /* Check if pkt fits into the diag_tx_pkt before dsm_pullup_tail() */
      ASSERT( total_pkt_length <= sizeof(diag_tx_pkt_conn_ctrl));
      dsm_pullup_tail(&diag_tx_dsm_ptr, &diag_tx_pkt_conn_ctrl, total_pkt_length);
      conn->diag_tx_iovec.buffer = &diag_tx_pkt_conn_ctrl;
    }
    
    /* free incoming dsm_ptr since it is already queued */
    (void)dsm_free_packet( &(diag_tx_dsm_ptr) );
  }

  /* call smdl_writev() */
  /* for log_pkt_len > smd fifo_sz, wait for SMDL_EVENT_WRITE cb to call us again with same iovec ptr */
  smdl_writev_ret = smdl_writev( conn->handle.smdl_handle, &(conn->diag_tx_iovec), SMDL_WRITE_FLAG_LONG );
  if( smdl_writev_ret == conn->diag_tx_iovec.length )
    conn->diag_prev_tx_pending = FALSE; /* Packet successfully sent */
  else if( smdl_writev_ret == SMDL_CONTINUE || smdl_writev_ret == 0 )
    conn->diag_prev_tx_pending = TRUE;  /* FIFO is full; come back later */
  else
    conn->diag_prev_tx_pending = FALSE; /* If we get here, something has gone wrong. */
    
}

#endif /* DIAG_SMDL_SUPPORT */

