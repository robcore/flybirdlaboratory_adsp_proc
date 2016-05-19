#ifndef DIAGCOMM_IO_SIO_H 
#define DIAGCOMM_IO_SIO_H
/*==========================================================================

              Diag I/O Wrapper APIs for Interprocessor Communication and I/O 

General Description
  
Copyright (c) 2011 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diagcomm_io_sio.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/27/13   xy      Removed code under FEATURE_WINCE  
03/04/11   is      Support for Diag over SMD-Lite

===========================================================================*/

  #include "customer.h"


#ifdef DIAG_SIO_SUPPORT

#include "comdef.h"
#include "diagcomm_io.h"   /* For diagcomm_io_conn_type */
#include "sio.h"           /* For sio_bitrate_type */


/* For smd channel */
void diagcomm_smd_sio_set_port( diagcomm_io_conn_type * conn );

/* For sio channel */
void diag_dtr_enable( diagcomm_io_conn_type * conn );
void diag_dtr_changed_cb( void * cb_data );
void diagcomm_sio_open_cb( sio_port_id_type port_id );
void diagcomm_sio_set_port( diagcomm_io_conn_type * conn );

/* For ctrl channel */
void diagcomm_ctrl_sio_set_port( diagcomm_io_conn_type * conn );
void diagcomm_ctrl_open_cb( sio_port_id_type port_id );

#endif /* DIAG_SIO_SUPPORT */

#endif /* DIAGCOMM_IO_SIO_H */
