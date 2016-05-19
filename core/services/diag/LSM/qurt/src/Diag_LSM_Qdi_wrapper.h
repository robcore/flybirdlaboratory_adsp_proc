#ifndef DIAG_LSM_QDI_WRAPPER_H
#define  DIAG_LSM_QDI_WRAPPER_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                    Diag QDI Wrapper Header

General Description

we need to implement inline wrapper functions for our qdi driver in order to
hide the details of our QDI implementation from the user.

Copyright (c) 2012,2014 Qualcomm Technologies, Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================
                          Edit History 
   
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/24/14   xy      Resolve 8994 Diag warnings with new LLVM 7.0.04 toolchain  
02/12/14   jb      Marked inline functions as extern for LLVM
07/05/12   sg      Created File 
===========================================================================*/
#include "comdef.h"

/*===========================================================================

FUNCTION  diag_lsm_read_data

DESCRIPTION
 This function reads the data from guest os diag driver

RETURN VALUE
  Returns number of bytes read.

===========================================================================*/
int diag_lsm_read_data(byte * buf,int length);

/*===========================================================================

FUNCTION diag_lsm_write_data

DESCRIPTION
  This function writes the data to guest os diag driver


RETURN VALUE
  Returns number of bytes written.

===========================================================================*/
int diag_lsm_write_data(byte * buf,int length);

/*===========================================================================

FUNCTION diag_lsm_ioctl

DESCRIPTION
 This function ioctls into guest os diag driver

RETURN VALUE
  Returns the bytes for the ioctl code.

===========================================================================*/
int diag_lsm_ioctl(int diag_qdi_ioctl,byte * inbuf,dword inbuflen,byte *outbuf,dword outbuflen,dword *  out_buf_actual_bytes_ptr);

/*===========================================================================

FUNCTION diag_lsm_wait_for_event

DESCRIPTION
  This function waits on a set of signals to be set to the Diag LSM.
  Signals are set when there is a mask change or when a command is available for the client

RETURN VALUE
  Indicates which signal is set to LSM.

===========================================================================*/
int diag_lsm_wait_for_event(void);

/*===========================================================================

FUNCTION diag_lsm_send_pkt_read_complete_notify

DESCRIPTION
 This function indicates to the diag in guest os that the LSM client has 
 read the command completely

RETURN VALUE
  None.

===========================================================================*/
int diag_lsm_send_pkt_read_complete_notify(void);

#endif
