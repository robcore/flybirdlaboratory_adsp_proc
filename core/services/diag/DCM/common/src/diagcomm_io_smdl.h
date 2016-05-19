#ifndef DIAGCOMM_IO_SMDL_H 
#define DIAGCOMM_IO_SMDL_H
/*==========================================================================

              Diag I/O Wrapper APIs for Interprocessor Communication and I/O 

General Description
  
Copyright (c) 2011-2014 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diagcomm_io_smdl.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/10/14   sr      Support for peripheral buffering mode  
09/27/13   xy      Removed code under FEATURE_WINCE  
07/06/11   hvm     Added new api declaration for T-put improv
03/04/11   is      Support for Diag over SMD-Lite

===========================================================================*/

  #include "customer.h"


#ifdef DIAG_SMDL_SUPPORT 

#include "diagcomm_io.h"         /* For diagcomm_io_conn_type */

void diagcomm_smdl_open_init( diagcomm_io_conn_type * conn );
void diagcomm_io_smdl_send ( diagcomm_io_conn_type * conn, boolean is_cmd_rsp_type );

#endif /* DIAG_SMDL_SUPPORT */

#endif //DIAGCOMM_IO_SMDL_H


