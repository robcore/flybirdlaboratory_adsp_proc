/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                         Diagnostics over STM

General Description
This routines in this file are used to send data over STM using the debugtrace
interfaces.
  
Copyright (c) 2013-14 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diag_stm.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/06/14   ph      Added support for Diag over STM
09/20/13   tbg     File creation
===========================================================================*/

#include "comdef.h"
#include "stdlib.h"
#include "tracer.h"

#include "diagdiag_v.h"
#include "diagcmd.h"
#include "diagbuf_v.h"
#include "diagi_v.h"
#include "assert.h"

#include "diag_stm.h"
#include "osal.h"


#ifdef FEATURE_DIAG_STM
/* Safe guard to ensure file is not compiled if feature is not enabled */


/* Local variable declarations */
static boolean diag_stm_initialized = FALSE; // Indicates if diag tracer has been initialized
boolean diag_stm_enabled = FALSE; // Transmit data over STM

boolean diag_pthread_initialized = FALSE; // TLS key initialized for STM. Note: Must be done before diag_stm_enabled can be set to TRUE.
osal_tls_key_t diag_tracer_tls_key; // TLS key for diag tracer handle


/* Local #defines */
#define TRACER_PROTOCOL_DIAG 1 // Protocol ID value; not used by tracer interface. 

/* Defines used for enabling Diag over STM */
#if (defined (DIAG_IMAGE_MODEM_PROC) || defined(DIAG_SINGLE_PROC)) && !defined (DIAG_IMAGE_QDSP6_PROC)
  /* The ARM9 modem and NOT QDSP6 modem */
  #define DIAG_STM_PROC_MASK DIAG_STM_PROC_MASK_MODEM
#elif defined (DIAG_IMAGE_APPS_PROC) && !defined (DIAG_IMAGE_QDSP6_PROC)
  /* Brew apps and WM apps */
  #define DIAG_STM_PROC_MASK DIAG_STM_PROC_MASK_APPS
#elif defined(DIAG_IMAGE_QDSP6_PROC)
  /* QDSP6 modem */
  #define DIAG_STM_PROC_MASK DIAG_STM_PROC_MASK_ADSP
#elif defined(DIAG_IMAGE_RIVA_PROC)
  /* RIVA */
  #define DIAG_STM_PROC_MASK DIAG_STM_PROC_MASK_WCNSS
#endif

#ifdef FEATURE_DIAG_STM
extern void diag_stm_mode_change_notify(int Svc);
#endif
/* Local function prototypes */
#if (defined(DIAG_MP_MASTER)) || (!defined(DIAG_MP_MASTER) && !defined(DIAG_MP))
void* diag_stm_configure_request(void *, uint16);

/* Diag STM Command */
static const diagpkt_user_table_entry_type diag_subsys_tbl_stm[] =
{
  {DIAGDIAG_STM_CONTROL, DIAGDIAG_STM_CONTROL, diag_stm_configure_request}
};
#endif

/*===========================================================================

FUNCTION DIAG_STM_INIT

DESCRIPTION
  Prepares Diag to be able to send traffic over STM. Note this does not enable
  Diag traffic over STM when called, it simply allows Diag to switch it on
  when needed.
 
  Specific init steps taken:
    1. Register any command handlers needed for enabling STM (if applicable)
    2. Create the TLS key used to store tracer handlers
 
  diag_stm_initialized will be set to TRUE only if all steps are successfully
  completed, especially the TLS key creation.
 
PARAMETERS
  None

DEPENDENCIES
  None

===========================================================================*/
void diag_stm_init(void)
{
  int rval;

  if(!diag_stm_initialized)
  {
#if (defined(DIAG_MP_MASTER)) || (!defined(DIAG_MP_MASTER) && !defined(DIAG_MP))
    DIAGPKT_DISPATCH_TABLE_REGISTER_PROC (DIAG_MODEM_PROC, DIAG_SUBSYS_DIAG_SERV, diag_subsys_tbl_stm);
#endif

    /* Create TLS key for storage of Diag tracer client handles.
       This key MUST be created before other Diag calls try to access
       the Diag tracer TLS information.
     */

    rval = osal_pthread_key_create(&diag_tracer_tls_key, NULL);
    
    if(rval == OSAL_SUCCESS) // Success
    {
      diag_stm_initialized = TRUE;
    }
  }
}

#ifdef FEATURE_DIAG_STRESS_PROFILE
uint64 diag_tracer_pcycles_total = 0;
uint32 diag_tracer_byte_total = 0;
#endif /* FEATURE_DIAG_STRESS_PROFILE */

/*===========================================================================

FUNCTION DIAG_STM_WRITE_PKT

DESCRIPTION
  Writes the specified packet to STM using the tracer APIs using the tracer
  handle that exists for this thread in TLS. If a handle does not exist, one
  is created and then stored using TLS.
 
PARAMETERS
  ptr      Pointer to data to be written
  length   Number of bytes to write from ptr
 
DEPENDENCIES
  diag_stm_initliazed is TRUE

===========================================================================*/
void diag_stm_write_pkt(void* ptr, uint32 length)
{
  tracer_return_enum_t rval;
  static tracer_options_t diag_tracer_options = TRACER_OPT_TIMESTAMP;
  static uint32 diag_tracer_reg_error_cnt = 0;
  static uint32 diag_tracer_write_error_cnt = 0;
  tracer_client_handle_t client_handle;
  boolean write_flag = TRUE;
  
  if(( ptr != NULL) && diag_stm_initialized && diag_stm_enabled && (length > 0))
  {
    /* Check if tracer handle has been written into TLS */
    client_handle = osal_pthread_getspecific(diag_tracer_tls_key);
    if(client_handle == NULL)
    {
      write_flag = FALSE;
      /* No handle exists; need to create a handle for this thread */
      rval = tracer_register(&client_handle, TRACER_ENTITY_DIAG, TRACER_PROTOCOL_DIAG);
      if (rval == TRACER_RETURN_SUCCESS)
      {
        ASSERT(osal_pthread_setspecific(diag_tracer_tls_key, (void*)client_handle) == OSAL_SUCCESS)
        write_flag = TRUE;          
      }
      else
      {
        // tracer didn't intiialize -- why?
        // Don't send error MSG, as it may result in an recursive loop
        // Increment debug counter for tracer registration
        diag_tracer_reg_error_cnt++;
      }
    }
    /* Send packet to tracer */
    if(write_flag)
    {
#ifdef FEATURE_DIAG_STRESS_PROFILE
      uint64 pcycle_end, pcycle_start;
      pcycle_start = qurt_get_core_pcycles();
#endif /* FEATURE_DIAG_STRESS_PROFILE */

      rval = tracer_data(client_handle, diag_tracer_options, length, ptr);

      if (rval != TRACER_RETURN_SUCCESS)
      {
        // If write fails, increment debug counter for write failures
        diag_tracer_write_error_cnt++;
      }

#ifdef FEATURE_DIAG_STRESS_PROFILE
      pcycle_end = qurt_get_core_pcycles();
      diag_tracer_pcycles_total += pcycle_end-pcycle_start;
      diag_tracer_byte_total += length;
#endif /* FEATURE_DIAG_STRESS_PROFILE */
    }
  }
}

/*===========================================================================

FUNCTION DIAG_STM_CONTROL_MODE

DESCRIPTION
  Used to enable or disable Diag over STM. Function will only allow it to be
  enabled if diag_stm_initialized is TRUE.
 
PARAMETERS
  mode_info    parameter indicating enable/disable of Diag over STM
               (DIAG_STM_ENABLE or DIAG_STM_DISABLE)
 
DEPENDENCIES
 
RETURN 
  Returns the current state of Diag over STM
    DIAG_STM_DISABLE  Diag STM is currently disabled
    DIAG_STM_ENABLE   Diag STM is currently enabled

===========================================================================*/
uint8 diag_stm_control_mode(uint8 mode_info)
{
  uint8 rval = DIAG_STM_DISABLE;

  if(diag_stm_initialized)
  {
    if (mode_info == DIAG_STM_ENABLE)
    {
      diag_stm_enabled = TRUE;
      rval = DIAG_STM_ENABLE;
#ifdef FEATURE_DIAG_STM
	  diag_stm_mode_change_notify(DIAG_STM_MODE_CHANGE);
#endif
    }
    else if (mode_info == DIAG_STM_DISABLE)
    {
      diag_stm_enabled = FALSE;
      rval = DIAG_STM_DISABLE;
#ifdef FEATURE_DIAG_STM
	  diag_stm_mode_change_notify(DIAG_STM_MODE_CHANGE);
#endif
    }
    else
    {
      MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR, "Invalid paramater receieved in diag_control_stm_mode");
      if (diag_stm_enabled)
      {
        rval = DIAG_STM_ENABLE;
      }
    }
  }
  else
  {
    MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR, "diag_stm_control_mode called but Diag STM is not initialized");
  }
  return rval;
}

#if (defined(DIAG_MP_MASTER)) || (!defined(DIAG_MP_MASTER) && !defined(DIAG_MP))
/*===========================================================================

FUNCTION DIAG_STM_CONFIGURE_REQUEST

DESCRIPTION
  Packet handler for Diag over STM configuration command. For use in modem
  only builds where there is no apps processor.
 
PARAMETERS
  req_pkt     Incoming command packet
  pkt_len     Length of incoming packet
 
DEPENDENCIES
 
RETURN 
  Returns response packet

===========================================================================*/
PACK(void *) diag_stm_configure_request(
  PACK(void *) req_pkt,
  uint16 pkt_len
)
{
  diagpkt_subsys_cmd_code_type cmd_code;
  diag_stm_control_rsp_type *rsp = NULL;
  diag_stm_control_req_type *req = (diag_stm_control_req_type *)req_pkt;
  boolean valid_cmd = TRUE;

  if (pkt_len != sizeof (diag_stm_control_req_type) || req_pkt == NULL)
  {
    return (diagpkt_err_rsp (DIAG_BAD_LEN_F, req_pkt, pkt_len));
  }

  cmd_code = diagpkt_subsys_get_cmd_code (req_pkt);
  rsp = (diag_stm_control_rsp_type *) diagpkt_subsys_alloc(DIAG_SUBSYS_DIAG_SERV, 
           cmd_code, sizeof(diag_stm_control_rsp_type));
  
  if(rsp != NULL)
  {	
    if((req->stm_control > DIAG_STM_ENABLE) || (req->version != DIAG_STM_VER_1))
    {
      /* Mark response field invalid if either parameter is out of range */
      valid_cmd = FALSE;
    }

    rsp->proc_mask = req->proc_mask;
    rsp->version = req->version;
    rsp->proc_mask = req->proc_mask;
    /* In this mode, only DIAG_STM_PROC_MASK is supported */
    rsp->is_support_mask = DIAG_STM_PROC_MASK;

    if(!(req->proc_mask & DIAG_STM_PROC_MASK))
    {
      /* This configuration only supports the default processor */
      /* Any other value will return an invalid flag in the response */
      valid_cmd = FALSE;
    }

    if (valid_cmd)
    {
      rsp->stm_status = diag_stm_control_mode(req->stm_control);
    }
    else
    {
      rsp->stm_status = DIAG_STM_DISABLE;
    }

    rsp->valid_cmd = valid_cmd;
  }
  
  return rsp;
} /* diag_stm_configure_request */
#endif

/*===========================================================================

FUNCTION DIAG_STM_LOG_ALLOC

DESCRIPTION
  Allocates a log packet using malloc, intended to be transmitted using the
  tracer APIs and then freed. Logs allocated using this API are not intended to
  be processed by the diag task.
 
  For consistency in other log handling APIs, the method for allocating the logs
  and the headers used are consistent with the standard diagbuf_alloc function.
 
  The status member of the diagbuf header is set to DIAGBUF_STM_BUFFER_S to
  allow other Diag APIs to know where the buffer was allocated from.
 
PARAMETERS 
  code                 ID of the log to be reported
  length               The specified length is the length of the entire log, 
                       including the log header.  
DEPENDENCIES

===========================================================================*/
PACK(void *) diag_stm_log_alloc (uint8 code, uint16 length)
{
  uint32 alloc_length;
  PACK(void *) ptr = NULL; /* Pointer to return.        */
  diagbuf_header_type *pkt_hdr;
  
  if(length==0)
  {
    /* Return NULL if an empty log packet is being requested */
    return NULL;
  }
  
  alloc_length =
    sizeof(diagbuf_header_type) +  /* Diagbuf header    */
      (uint32)length;     /* Number of bytes requested buffer */
  
  ptr = malloc(alloc_length);
  
  if (ptr)
  {
    /* Set header field of buffer */
    pkt_hdr = ((diagbuf_header_type *) ptr);
    
    pkt_hdr->status = DIAGBUF_STM_BUFFER_S;
    /* Note: pkt_hdr->pad not needed for STM implementation, sicne this allocation is not
       going into diagbuf */
    pkt_hdr->length = length;
    
    /* Set 'ptr' to pkt_hdr +1 = data following pkt_hdr */
    ptr = pkt_hdr + 1;
    
    diagpkt_set_cmd_code (ptr, code);
  }
  
  return ptr;
} /* diag_stm_log_alloc */


/*===========================================================================

FUNCTION DIAG_STM_ALLOC

DESCRIPTION
  Allocates a buffer using malloc, intended to be transmitted using the
  tracer APIs and then freed. Packets allocated using this API are not intended to
  be processed by the diag task.
 
  This is a direct wrapper for malloc (no additional headers added, etc.)
  Intended use case is allocating memory for messages and event reports, where
  diag will be determining the exact size of the final packet.
 
PARAMETERS 
  length      Length of buffer to allocate
 
DEPENDENCIES
 
 
===========================================================================*/
PACK(void *) diag_stm_alloc(uint32 length)
{
  void *ptr = NULL;
  if(length > 0)
  {
    ptr = malloc(length);
  }
  return ptr;
}

/*===========================================================================

FUNCTION DIAG_STM_FREE

DESCRIPTION
  Frees a buffer allocated using diag_stm_alloc
 
PARAMETERS 
  ptr      Pointer to free
 
DEPENDENCIES

===========================================================================*/
void diag_stm_free(void *ptr)
{
  free(ptr);
}

/*===========================================================================

FUNCTION DIAG_STM_LOG_FREE

DESCRIPTION
  Frees a buffer allocated using diag_stm_log_alloc (accounts for diagbuf header)
 
PARAMETERS 
  ptr      Pointer to free 
 
DEPENDENCIES

===========================================================================*/
void diag_stm_log_free(void *ptr)
{
  diagbuf_header_type *pkt_hdr;

  if(ptr)
  {
    pkt_hdr = ((diagbuf_header_type *) ptr) - 1;
    free(pkt_hdr);  
  }
}

/*===========================================================================

FUNCTION DIAG_STM_GET_MODE_DCM 

DESCRIPTION
  Populates the output buffer with the STM mode information and returns TRUE
  if it is able to write the mode.
  
 
PARAMETERS 
  out_buf_ptr      	Pointer to the buffer where STM mode is to be written.
  outbuf_max_bytes 	Maximum bytes that can be written.
  pbytes_written	Pointer to hold the info of number of bytes written.
 
DEPENDENCIES
	None

===========================================================================*/
boolean diag_stm_get_mode_dcm(byte* out_buf_ptr, unsigned long outbuf_max_bytes, unsigned long* pbytes_written) 
{
	boolean success = FALSE;
	if( (out_buf_ptr) && (outbuf_max_bytes == sizeof(diag_stm_enabled) ) && (pbytes_written))
	{
		*((byte*)out_buf_ptr) = diag_stm_enabled;
		*pbytes_written = sizeof(diag_stm_enabled);
		success = TRUE;		
	}
	else
	{
		MSG(MSG_SSID_DIAG,MSG_LEGACY_ERROR, "diag_stm.c error:LSM request for STM failed \n");
	}
	return success;
}

#endif /* FEATURE_DIAG_STM */
