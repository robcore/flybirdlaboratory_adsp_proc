#ifndef DIAGPKTI_H
#define DIAGPKTI_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                   Diagnostics Packet Processing

General Description
  Diagnostic packet processing internal declarations.

Copyright (c) 2007-2015 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                           Edit History

$Header: //components/rel/core.adsp/2.6.1/services/diag/LSM/qurt/src/diagpkti.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/11/15   rh      Added client_id to diagpkt_get_delayed_rsp_id_dcm()
07/30/14   is      Do cleanup to support PD Restart
05/09/14   rs      Moving delayed response out of diag buffer.
10/10/12   sg      Changed the return type of diag_pkt_commit_dcm()
07/05/12   sg      Changes to bring up Diag MultiPD
04/20/10   sg      Moved diag_client_maskchange() to diag_v.h
07/07/09   mad     Removed inclusion of qw.h, included queue.h
07/07/09   mad     Moved structure definitions here from diagi.h, to 
                   maintain commonality of diagi.h
04/24/09   mad     Added declaration for diagpkt_get_delayed_rsp_id_dcm().
01/15/09   mad     Removed declaration of Mutex that protects global Rx buffer
12/02/08   mad     Introduced some function declarations etc.
                   which are shared between different C files.
===========================================================================*/
#include "comdef.h"
#include "diagi.h"
#include "diag.h"
#include "queue.h" /* for q_link_type */
#include "qurt_signal.h"

typedef struct
{
  diag_cmd_rsp rsp_func; /* If !NULL, this is called in lieu of comm layer */
  void *rsp_func_param;

  diagpkt_rsp_type rsp; /* see diagi.h */
}
diagpkt_lsm_rsp_type;

typedef struct
{
  unsigned int pattern;     /*!< Pattern to check validity of committed pointers. */
  unsigned int length;      /*!< Size of packet */
  byte pkt[1024];  
}
diagpkt_lsm_delay_rsp_type;

typedef struct
{
   boolean pending;
   diag_cmd_rsp rsp_func;
   void *rsp_func_param;
} diagpkt_rsp_func_store_type;

typedef struct
{ 
  uint32 client_id;
  int qdi_handle;
  qurt_signal_t *LSM_obj;
} diagpkt_mask_client_tbl_type;

typedef struct
{
  q_link_type link;
  diagpkt_mask_client_tbl_type mask_client;
} diagpkt_mask_client_q_type;

q_type diagpkt_mask_client_list_q;

typedef struct
{ 
  uint16 cmd_code;
  word subsysid;
  uint16 proc_id;
  word count;
  word cmd_code_lo;
  word cmd_code_hi;
  qurt_signal_t * LSM_obj;
  uint32 client_id;
  int qdi_handle;
} diagpkt_dcm_master_table_type;

typedef struct
{
  q_link_type link;
  diagpkt_dcm_master_table_type* master_tbl_entry;
  uint16 fwd_status;
}diagpkt_master_table_q_type;

q_type diagpkt_master_table_q;


void diagpkt_table_q_init(void);



boolean diagpkt_rx_buffer_cs_init(void);
void diagpkt_master_tbl_cs_init(void);
void diagpkt_mask_tbl_cs_init(void);

void diagpkt_delayrspid_mutex_init(void);

/* Functions used by windiag. */
int diagpkt_commit_dcm (int client_id,PACKED byte *ptr);
int diagpkt_delay_commit_dcm (int client_handle,PACKED byte * pkt);
boolean diagpkt_get_delayed_rsp_id_dcm(int client_handle, byte* out_buf_ptr, unsigned long outbuf_max_bytes, unsigned long* pbytes_written);

#endif /* DIAGPKTI_H */
