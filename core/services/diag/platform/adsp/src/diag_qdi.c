/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Diag Interface

GENERAL DESCRIPTION
  Contains main implementation of Diagnostic interface driver.

EXTERNALIZED FUNCTIONS
  diag_qdi_read
  diag_qdi_write
  diag_qdi_ioctl
  diag_qdi_release
  diag_qdi_open
  diag_qdi_register

INITIALIZATION AND SEQUENCING REQUIREMENTS


Copyright (c) 2012-2015 Qualcomm Technologies Incorporated.  All Rights Reserved.
Qualcomm Confidential and Proprietary
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/platform/adsp/src/diag_qdi.c#7 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/26/15   rh      Copy other data from userspace to local memory before reading
02/20/15   rh      Copy data from userspace to local memory before reading
02/19/15   rh      Bounds-check parameters sent from userspace.
02/17/15   rh      Use qurt_qdi_copy_to_user() to copy to userspace.
02/11/15   rh      Added client_id to diagpkt_get_delayed_rsp_id_dcm()
01/19/15   rh      QURT QDI hardening
08/20/14   sr      Fixed issue with F3s not coming out 
07/30/14   is      Do cleanup to support PD Restart
07/06/14   ph      Added support for Diag over STM
07/17/14   is      Prevent DIAG_QDI_BLOCK_FOR_NOTIFICATION from blocking PD from exit
05/09/14   rs      Moving delayed response out of diag buffer. 
03/05/14   xy      Fixed KW issue: replaced memcpy() with memscpy()  
06/27/13   sr      Fixed the issue with events not working in Sensor PD   
06/21/13   sr      Fixed the issue with log_status() not returning the 
                   correct status in Sensor PD 
02/10/13   sg      Donot check stream2 mask if DIAG_STREAM_2_MASK_CHECK
                   feature is not defined
10/10/12   sg      Replaced memcpy() with qurt_qdi_copy_to_user(),
                   qurt_qdi_copy_from_user() calls
08/30/12   sg      Fixed Compiler warnings
07/05/12   sg      File Created

===========================================================================*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stringl/stringl.h>
#include "diag.h"
#include "msg.h"
#include "diag_shared_i.h" /* for declaration of event_q_alloc,diag_data etc */
#include "eventi.h"
#include "diagpkt.h"    /* for DIAG_MAX_TX_PKT_SIZ */
#include "diagpkti.h"
#include "diagcomm_v.h" /* for diagcomm_sio_stream() */
#include "diagcomm_ctrl.h" /* For diagcomm_ctrl_send_mult_pkt */
#include "diagi_v.h"   /* for diag_control_sleep_voting, for ENABLE, DISABLE signals*/
#include "diagbuf_v.h" /* for diagbuf_ctrl_tx_sleep_parameters */
#include "diag_cfg.h" /* For DIAG_EVENT_HEAP_SIZE */
#include "diagtune.h" /* For DIAG_DRAIN_TIMER_LEN */
#include "msg_pkt_defs.h"
#include "msgi.h"
#include "msgcfg.h"
#include "diaglogi.h"
#include "msg_arrays_i.h"
#include "osal.h"
#include "diag_stm.h"

#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"
#include "qurt_futex.h"
#include "qurt_atomic_ops.h"
#include "qurt_error.h" /* for QURT_ECANCEL */
#include "osal.h"

#define DIAG_QDI_SUCCESS 0

extern osal_tcb_t diag_tcb;
//mask arrays for mask request functions
extern byte * log_mask[DIAG_MAX_STREAM_ID];
extern unsigned char * diag_event_mask[DIAG_MAX_STREAM_ID];
extern byte g_rx_buffer[MAX_CONCURRENT_REQS*DIAG_MAX_RX_PKT_SIZ] ;
extern unsigned int  g_rx_buffer_len;
static uint32 msg_drop_delta; /* number of dropped messages */
extern uint8 diag_cur_preset_id; /* from diag.c */

extern byte log_status_adv (log_code_type code);

typedef struct diag_qdi_opener_type
{
  qurt_qdi_obj_t qdiobj;
  qurt_signal_t  signal;
  int            qdi_handle;
} diag_qdi_opener;

static int diag_qdi_invoke(int client_handle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9);


/*===========================================================================

FUNCTION    diag_qdi_read

DESCRIPTION
  Handles read call for the driver.

DEPENDENCIES
  None.

RETURN VALUE
  -1 = failure, else number of bytes read

SIDE EFFECTS
  None

===========================================================================*/
dword diag_qdi_read(int client_handle, diag_qdi_opener *ppipe,

  void* rd_buf,
    /* Ptr to buffer where we should write the read data into */
  dword   rd_bytes
    /* Number of bytes to read from the device and copy into rd_buf */
)
{
  int memcpy_ret;
  
  /* What we're doing here is reading out commands to be handled locally in userspace.
     In order to do that, first we're bounds-checking so that we fit the destination size
	 and we read as much as needs to be read, if possible.
  */
  unsigned int read_length = g_rx_buffer_len;
  if ( read_length > rd_bytes )
    read_length = rd_bytes;
  if ( read_length > DIAG_MAX_RX_PKT_SIZ )
    read_length = DIAG_MAX_RX_PKT_SIZ;

  /* Here we actually do the copy and then we wipe the command if it was correctly read. */
  if ( NULL != rd_buf )
  {
    memcpy_ret = qurt_qdi_copy_to_user(client_handle, rd_buf, g_rx_buffer, read_length);
	if ( memcpy_ret < 0 )
	{
	  return memcpy_ret;
	}
	else
    {
      memset(g_rx_buffer, 0, MAX_CONCURRENT_REQS * DIAG_MAX_RX_PKT_SIZ);
    }
	return read_length;
  }
  return (0);
}
/*===========================================================================

FUNCTION    diag_qdi_write

DESCRIPTION
  Handles write call for the driver.

DEPENDENCIES
  None.

RETURN VALUE
  -1 = failure, else number of bytes read

SIDE EFFECTS
  None

===========================================================================*/
static int diag_qdi_write( int client_handle, diag_qdi_opener *ppipe,
                           const void *buf,
                           int buflen )
{
  int res = 0;
  int memcpy_res = 0;

  void* pDiagData = NULL;
  diag_data hdr_data;
  byte *pData = ((byte *)buf + DIAG_REST_OF_DATA_POS);
  
  if ( buf == NULL )
    return -1;
  
  /* check against integer underflow for packet lengths */
  if( buflen < DIAG_REST_OF_DATA_POS )
    return res;

  memcpy_res = qurt_qdi_copy_from_user(client_handle, &hdr_data, buf, sizeof(hdr_data));
  if ( memcpy_res < 0 )
    return -1;

  /* examine diag_data_type to determine if the data is an event, log, 
      F3 or response. */
  switch ( hdr_data.diag_data_type )
  {
  case DIAG_DATA_TYPE_EVENT:
    {

	  /* Check against integer overflow/underflow for events */
	  if( buflen - DIAG_REST_OF_DATA_POS > UINT8_MAX)
	    break;
	  
	  event_store_type *pEventData = (event_store_type*)pData;
      event_store_type *pDiagEventData = NULL;
	  uint8 payload_len = (uint8)buflen - DIAG_REST_OF_DATA_POS;

	  
	  event_store_type eventData;
	  memcpy_res = qurt_qdi_copy_from_user(client_handle, &eventData, pEventData, sizeof(eventData));
	  
      /* Allocate an event for the first stream */
      pDiagEventData = event_q_alloc((event_id_enum_type)eventData.event_id.id,
                                     payload_len, DIAG_STREAM_1);
      if ( pDiagEventData )
      {
        memcpy_res = qurt_qdi_copy_from_user(client_handle,
                                             (pDiagEventData->payload.payload),
                                             pEventData->payload.payload,
                                             payload_len);
        if ( memcpy_res == 0 )
        {
          event_q_put(pDiagEventData, DIAG_STREAM_1);
          res = buflen;
        }
        else
        {
          diag_event_free(pDiagEventData);
        }
      }

    }
    break; /* end case DIAG_DATA_TYPE_EVENT */
      /* Note for use of diagbuf_alloc for DIAG HEALTH
       * Under the current design, DIAG traffic drop at the API layer (LSM) can only occur when
       * the client process runs out of heap-space. As such, it is assumed that the recorded
       * drop counts will be at the DCM level. This code may require an update if the design changes.
       */
   case DIAG_DATA_TYPE_LOG:
      {

         log_header_type temp;
		 memcpy_res = qurt_qdi_copy_from_user(client_handle, &temp, (void*)(pData + LOG_DIAGPKT_OFFSET), sizeof(temp));
         if (memcpy_res < 0)
         {
            return 0;
         }
         /* Check runtime masks again to determine what stream(s) to send on */
         byte stream_id = log_status_adv(temp.code);
         if (stream_id != 0)
         {
            pDiagData = (void *)diagbuf_alloc (0 , buflen - DIAG_REST_OF_DATA_POS, 0, DIAGBUF_ALLOC_REQUEST_LOG);
            if (pDiagData)
            {

               diagbuf_write_stream_id(pDiagData, stream_id);
               diagbuf_set_bit_outbound_pkt_handler(pDiagData);
               //Read message straight into buffer
               memcpy_res = qurt_qdi_copy_from_user(client_handle,pDiagData, (void*) pData, buflen - DIAG_REST_OF_DATA_POS);
               if (memcpy_res < 0)
               {
                 log_free(pDiagData);
                 return 0;
               }

               /*Commit the data to the diagbuf buffer. */
               diagbuf_commit(pDiagData);
               res = buflen;
            }
         }
      }
      break;/* end case DIAG_DATA_TYPE_LOG */

   case DIAG_DATA_TYPE_F3:
      {
         boolean valid_ssid;

		 msg_ext_type temp;
         uint32 rt_mask = 0;
         #ifdef DIAG_STREAM_2_MASK_CHECK
         uint32 rt_mask_ctrl = 0;
         boolean valid_ssid_ctrl;
         #endif
         byte stream_id = 0;
		 
         /* Check the runtime masks to get outgoing streams... */
		 memcpy_res = qurt_qdi_copy_from_user(client_handle, &temp, pData, sizeof(temp));
		 if (memcpy_res < 0)
         {
            return 0;
         }

         valid_ssid = msg_get_ssid_masks_adv (MSG_MASK_RT, temp.desc.ss_id, temp.desc.ss_id, &rt_mask, DIAG_STREAM_1, diag_cur_preset_id);
         if ((valid_ssid && (temp.desc.ss_mask & rt_mask)))
         {
            stream_id |= DIAG_STREAM_1;
         }
         #ifdef DIAG_STREAM_2_MASK_CHECK
         valid_ssid_ctrl = msg_get_ssid_masks_adv (MSG_MASK_RT, temp.desc.ss_id, temp.desc.ss_id, &rt_mask_ctrl, DIAG_STREAM_2, DIAG_DCI_MASK_1);
         if ((valid_ssid_ctrl && (temp.desc.ss_mask & rt_mask_ctrl)))
         {
            stream_id |= DIAG_STREAM_2;
         }
         #endif

         if (stream_id != 0)
         {
            pDiagData = (void *)diagbuf_alloc (0 , buflen - DIAG_REST_OF_DATA_POS, 0, DIAGBUF_ALLOC_REQUEST_MSG);
            if (pDiagData)
            {

               diagbuf_write_stream_id(pDiagData, stream_id);
               diagbuf_set_bit_outbound_pkt_handler(pDiagData);
               temp.hdr.drop_cnt = (unsigned char) ((((temp.hdr.drop_cnt)+msg_drop_delta) > 255) ? 255 : ((temp.hdr.drop_cnt)+msg_drop_delta));
               msg_drop_delta = 0;   /* Reset delta drop count */
               memcpy_res = qurt_qdi_copy_from_user(client_handle, pDiagData, pData, buflen - DIAG_REST_OF_DATA_POS);
               /*Commit the data to the diagbuf buffer. */
               if (memcpy_res < 0)
               {
                 diagbuf_shorten(pDiagData,0);
                 diagbuf_commit(pDiagData);
                 return 0;
               }

               diagbuf_commit(pDiagData);
               res = buflen;
            }
         }
         else
         {
            msg_drop_delta++;
         }
      }
      break;/* end case DIAG_DATA_TYPE_F3 */

   case DIAG_DATA_TYPE_DELAYED_RESPONSE:
       memcpy_res = diagpkt_delay_commit_dcm(client_handle,pData);
       if (!memcpy_res)
          return 0;

         res = buflen;
      break;/* end case DIAG_DATA_TYPE_DELAYED_RESPONSE */
   case DIAG_DATA_TYPE_RESPONSE:

      memcpy_res = diagpkt_commit_dcm(client_handle,pData);
      if (!memcpy_res)
         return 0;

      res = buflen ;
      break;/* end case DIAG_DATA_TYPE_RESPONSE */

   default:


      break;
   }/* end switch */


   return(res);
}

/*===========================================================================
FUNCTION   diag_qdi_ioctl

DESCRIPTION
  Called by other modules to implement IOCTL code responses.

DEPENDENCIES
  None.

RETURN VALUE
  FALSE = failure, else TRUE

SIDE EFFECTS
  None
===========================================================================*/
static int diag_qdi_ioctl(int client_handle, diag_qdi_opener *ppipe,
                 dword   ioctl_code,
    /* IOCTL code */
  byte*   in_buf_ptr,
    /* Ptr to buffer containing input data */
  dword   in_buf_bytes,
    /* Number of bytes of data in the in_buf */
  byte*   out_buf_ptr,
    /* Ptr to buffer containing output data */
  dword   out_buf_max_bytes,
    /* Maximum number of bytes of data allowed in the out_buf */
  dword*  out_buf_actual_bytes_ptr) {
  int tot_out_buf_bytes = 0;

  /* Function return value */
  int fn_ret_val = 0;
  int copy_ret;

  switch ( ioctl_code )
  {
  case DIAG_IOCTL_COMMAND_REG:
  case DIAG_IOCTL_MASK_REG:
    {
	  bindpkt_params_per_process bind_data;
      bindpkt_params_per_process *pbind_data = &bind_data;
      /* make a local copy of the values in the incoming pointer */
      uint32 count;
      int qdi_handle;

      copy_ret = qurt_qdi_copy_from_user(client_handle, pbind_data, in_buf_ptr, sizeof(*pbind_data));
	  if( copy_ret < 0 )
	  {
		fn_ret_val = FALSE;
		return fn_ret_val;
	  }

      pbind_data->signal = &ppipe->signal;
      count = pbind_data->count;
      qdi_handle = ppipe->qdi_handle;
	  /* We don't use pbind_data->signal on the user end, so we don't need to copy things back. */

      if ( count > 0 )
      {
        if ( ioctl_code == DIAG_IOCTL_COMMAND_REG )
        {
          fn_ret_val = diagpkt_tbl_reg_dcm(client_handle, in_buf_ptr, count, pbind_data->signal, qdi_handle);

        }
        else if ( ioctl_code == DIAG_IOCTL_MASK_REG )
        {
          fn_ret_val = diagpkt_mask_tbl_reg(pbind_data->client_id, pbind_data->signal, qdi_handle);
        }
      }
      else
      {
        fn_ret_val = FALSE;
      }
      break; /* end case DIAG_DEVCTL_COMMAND_REG:*/
    }
    
  case DIAG_IOCTL_COMMAND_DEREG:
    {
      if ( in_buf_ptr )
      {
        int qdi_handle = ppipe->qdi_handle;
        fn_ret_val = (boolean)diagpkt_tbl_dereg_dcm(qdi_handle);
      }
      else
      {
        fn_ret_val = FALSE;
      }
      break; /* end case DIAG_DEVCTL_COMMAND_DEREG */
    }
  case DIAG_IOCTL_MASK_DEREG:
    {
      if ( in_buf_ptr && (in_buf_bytes == sizeof(bindpkt_params_per_process)) )
      {
        int qdi_handle = ppipe->qdi_handle;
        fn_ret_val = (boolean)diagpkt_mask_tbl_dereg(qdi_handle);
      }
      else
      {
        fn_ret_val = FALSE;
      }
      break; /* end case DIAG_DEVCTL_MASK_DEREG */
    }

  case DIAG_IOCTL_GETEVENTMASK:
    /* input buffer is same, and same size, as output buffer, so we're using input
     * buffer variable names to hand pointers... */
    fn_ret_val = event_process_LSM_mask_req(client_handle, out_buf_ptr, out_buf_max_bytes, &tot_out_buf_bytes);
    break;

  case DIAG_IOCTL_GETLOGMASK:
    /* input buffer is same, and same size, as output buffer, so we're using input
     * buffer variable names to hand pointers... */
    fn_ret_val = log_process_LSM_mask_req(client_handle, out_buf_ptr, out_buf_max_bytes, &tot_out_buf_bytes);
    break;

  case DIAG_IOCTL_GETMSGMASK:
    /* input buffer is same, and same size, as output buffer, so we're using input
     * buffer variable names to hand pointers... */
    fn_ret_val = msg_process_LSM_mask_req(client_handle, out_buf_ptr, out_buf_max_bytes, &tot_out_buf_bytes);
    break;

  case DIAG_IOCTL_GET_DELAYED_RSP_ID:
    /* input buffer is same, and same size, as output buffer, so we're using input
     * buffer variable names to hand pointers... */
    fn_ret_val = diagpkt_get_delayed_rsp_id_dcm(client_handle, out_buf_ptr, (unsigned long)out_buf_max_bytes, (unsigned long *)&tot_out_buf_bytes);
    break;
        
    case DIAG_IOCTL_GET_STM_MODE:
        /* input buffer is same, and same size, as output buffer, so we're using input
         * buffer variable names to hand pointers... */
#ifdef FEATURE_DIAG_STM
        fn_ret_val = diag_stm_get_mode_dcm(out_buf_ptr, (unsigned long)out_buf_max_bytes,(unsigned long*) &tot_out_buf_bytes );
        break;
#endif

  default:
    fn_ret_val = FALSE;
  }


  /* Indicate the number of bytes and return the message */
  if ( out_buf_actual_bytes_ptr != NULL )
  {
    if(qurt_qdi_copy_to_user(client_handle, out_buf_actual_bytes_ptr, &tot_out_buf_bytes, sizeof(tot_out_buf_bytes)) < 0)
		fn_ret_val = FALSE;
  }

  return(fn_ret_val);
}

/* Why we don't have any close callback? Because the default
 * function, iofunc_close_ocb_default(), does all we need in this
 * case: Free the ocb, update the time stamps etc. - copied from
 * sample code documentation
 * Also, close gets called whenever an fd is closed, whereas ocb_free
 * is only called when a process is actually done with their OCB.
 */

/*===========================================================================

FUNCTION MSG_PROCESS_LSM_MASK_REQ

DESCRIPTION
  Handles requests from LSM to transfer the message mask table.
============================================================================*/

boolean msg_process_LSM_mask_req (int client_handle,unsigned char* mask, int maskLen, int * maskLenReq)
{
  boolean status = TRUE;
  if ( mask && maskLenReq )
  {
    unsigned int i;
    unsigned int byte_count = 0;
    unsigned int temp_size = 0;
    int memcpy_res = 0;
    byte *ptemp_byte = (byte *)mask;
    *maskLenReq = 0;

    for ( i = 0; i < MSG_MASK_TBL_CNT; i++ )
    {
      if ( byte_count >= maskLen )
      {
        status = FALSE;
        break;
      }
	  /* We're copying this in pieces using qurt_qdi_copy_to_user() to guarantee that
	     we are writing to userspace without relying on the structure of the mask table staying in the same order forever. */
	  memcpy_res = qurt_qdi_copy_to_user(client_handle, ptemp_byte, (byte *)&(msg_mask_tbl[i].ssid_first), sizeof(msg_mask_tbl[i].ssid_first));
      if ( memcpy_res < 0 )
        return (FALSE);
      byte_count += sizeof(msg_mask_tbl[i].ssid_first);
      ptemp_byte = (byte *)mask + byte_count;
	  memcpy_res = qurt_qdi_copy_to_user(client_handle, ptemp_byte, (byte *)&(msg_mask_tbl[i].ssid_last), sizeof(msg_mask_tbl[i].ssid_last));
      if ( memcpy_res < 0 )
        return (FALSE);
      byte_count += sizeof(msg_mask_tbl[i].ssid_last);
      ptemp_byte = (byte *)mask + byte_count;
		
      temp_size = sizeof(uint32) * (msg_mask_tbl[i].ssid_last - msg_mask_tbl[i].ssid_first + 1);
      memcpy_res = qurt_qdi_copy_to_user(client_handle, ptemp_byte, (byte *)msg_mask_tbl[i].rt_mask_array[DIAG_STREAM_1 - 1], temp_size);
      if ( memcpy_res < 0 )
        return (FALSE);

      byte_count += temp_size;
      ptemp_byte = (byte *)mask + byte_count;
    }
	
    if ( maskLen == byte_count && status )
    {
      *maskLenReq = byte_count;
    }
    else
    {
      *maskLenReq = byte_count;
      status = FALSE;
    }
  }
  else
  {
    status = FALSE;
  }
  return (status);
} /* msg_process_LSM_mask_req */

/*===========================================================================

FUNCTION LOG_PROCESS_LSM_MASK_REQ


DESCRIPTION
  Handles requests from LSM to transfer the log mask.
============================================================================*/
boolean
log_process_LSM_mask_req (int client_handle,unsigned char* mask, int maskLen, int * maskLenReq)
{
    boolean status = TRUE;
    if(mask && maskLenReq && (maskLen >= LOG_MASK_SIZE))
    {
        int memcpy_res = 0;
        *maskLenReq = 0;
        /* Copy the current log mask in DCM to the buffer passed in.*/
        memcpy_res = qurt_qdi_copy_to_user(client_handle,(void*)mask, (void*)log_mask[0], LOG_MASK_SIZE);
        if(memcpy_res<0)
                  return FALSE;

            int i, j;
            *maskLenReq = LOG_MASK_SIZE;

            /* For the purpose of supporting multiple masks, we will now OR in
             * the values from any secondary masks.
             * On the LSM side, anything which is allowed by at least one mask
             * will be passed down to DCM to be further sorted.
             */
            for(i = 1; i < DIAG_MAX_STREAM_ID; i++) {
                for(j = 0; j < LOG_MASK_SIZE; j++) {
                    mask[j] |= log_mask[i][j];
                }
            }
    }
    else
    {
          status = FALSE;
    }
    return(status);
}

/*===========================================================================

FUNCTION EVENT_PROCESS_LSM_MASK_REQ

DESCRIPTION
  Handles requests from LSM to transfer the event mask.
============================================================================*/

boolean
event_process_LSM_mask_req (int client_handle,unsigned char* mask, int maskLen, int * maskLenReq)
{
    boolean status = TRUE;
    if(mask && maskLenReq)
    {
        int memcpy_res = 0;
        *maskLenReq = 0;

        /* Copy the current event mask in DCM to the buffer passed in.*/
        memcpy_res = qurt_qdi_copy_to_user(client_handle,(void*)mask, (void*)diag_event_mask[0], EVENT_MASK_SIZE);
        if(memcpy_res<0)
          return FALSE;

            if(maskLen == EVENT_MASK_SIZE)
            {
                int i, j;
                *maskLenReq = EVENT_MASK_SIZE;

                /* For the purpose of supporting multiple masks, we will now OR in
                 * the values from any secondary masks.
                 * On the LSM side, anything which is allowed by at least one mask
                 * will be passed down to DCM to be further sorted.
                 */
                for(i = 1; i < DIAG_MAX_STREAM_ID; i++) {
                    for(j = 0; j < EVENT_MASK_SIZE; j++) {
                        mask[j] |= diag_event_mask[i][j];
                    }
                }
            }

    }
    else
    {
        status = FALSE;
    }
    return status;
} /*END event_process_LSM_mask_req()*/

/*===========================================================================
FUNCTION diag_qdi_release

DESCRIPTION
  diag_qdi_release
===========================================================================*/
void diag_qdi_release(qurt_qdi_obj_t *qdiobj)
{
  diag_qdi_opener * qdi_opener = (diag_qdi_opener*)qdiobj;
  
  diagpkt_tbl_dereg_dcm( qdi_opener->qdi_handle );
  diagpkt_mask_tbl_dereg( qdi_opener->qdi_handle );
  
  free(qdiobj);
}

/*===========================================================================
FUNCTION diag_qdi_open

DESCRIPTION
  Open the specified driver for subsequent operations.
===========================================================================*/
int diag_qdi_open(int client_handle, diag_qdi_opener *objptr,
                  const char *devname,
                  int mode)
{
  diag_qdi_opener *popen;

  popen = malloc(sizeof(*popen));
  if(popen == NULL)
  {
    printf("malloc err for %d bytes", sizeof(*popen));
    return -1;
  }
      
  popen->qdiobj.invoke = diag_qdi_invoke;
  popen->qdiobj.refcnt = QDI_REFCNT_INIT;
  popen->qdiobj.release = diag_qdi_release;
  qurt_signal_init(&popen->signal);
  popen->qdi_handle = qurt_qdi_handle_create_from_obj_t(client_handle, &popen->qdiobj);
  return popen->qdi_handle;
     
} /* diag_qdi_open */

/*===========================================================================
FUNCTION diag_qdi_invoke

DESCRIPTION
  Perform a generic driver operation, which (depending on the specified operation) can be
  either be one of the predefined operations  or a driver-specific
  operation
===========================================================================*/
static int diag_qdi_invoke(int client_handle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9)
{
   diag_qdi_opener *me = NULL;
   int sigs = 0;
   unsigned int mask = SYNC_EVENT_DIAG_LSM_PKT_IDX | DIAG_EVENTSVC_MASK_CHANGE| DIAG_MSGSVC_MASK_CHANGE| DIAG_LOGSVC_MASK_CHANGE | DIAG_STM_MODE_CHANGE | DIAG_KILL_RX_THREAD;
   osal_sigs_t return_sigs;
   me = (void *)pobj;

   switch (method) 
   {
     case QDI_OPEN:
      return diag_qdi_open(client_handle, (void *)pobj, a1.ptr, a2.num);

     case DIAG_QDI_READ:
      return diag_qdi_read(client_handle,(void *)pobj, a1.ptr, a2.num);

     case DIAG_QDI_WRITE:
      return diag_qdi_write(client_handle,(void *)pobj, a1.ptr, a2.num);

     case DIAG_QDI_IOCTL:
      return diag_qdi_ioctl(client_handle,(void *)pobj,a1.num,a2.ptr,a3.num,a4.ptr,a5.num,a6.ptr);

     case DIAG_QDI_BLOCK_FOR_NOTIFICATION:
      if( QURT_ECANCEL == qurt_signal_wait_cancellable(&me->signal, mask, QURT_SIGNAL_ATTR_WAIT_ANY, (unsigned int*) &sigs) ) 
        return TRUE;
      qurt_signal_clear(&me->signal, sigs);
      return sigs;

     case DIAG_QDI_SEND_PKT_READ_COMPLETE_NOTIFICATION:
      osal_set_sigs( &diag_tcb, DIAG_CMD_READ_COMPLETE_SIG, &return_sigs );
      return TRUE;

     case DIAG_QDI_KILL_RX_THREAD:
      qurt_signal_set(&me->signal,DIAG_KILL_RX_THREAD);
      return TRUE; 

     default:
       return qurt_qdi_method_default(client_handle, pobj, method,
                                      a1, a2, a3, a4, a5, a6, a7, a8, a9);
   }
   return -1;
   
} /* diag_qdi_invoke */

/*===========================================================================
FUNCTION diag_qdi_register

DESCRIPTION
  Register Diag with QDI Framework
===========================================================================*/
void diag_qdi_register(void)
{
   diag_qdi_opener *p_opener;

   p_opener = malloc(sizeof(*p_opener));
   if (p_opener == NULL)
      return;

   p_opener->qdiobj.invoke = diag_qdi_invoke;
   p_opener->qdiobj.refcnt = QDI_REFCNT_INIT;
   p_opener->qdiobj.release = diag_qdi_release;
   qurt_qdi_register_devname("/dev/diag", p_opener);

}
