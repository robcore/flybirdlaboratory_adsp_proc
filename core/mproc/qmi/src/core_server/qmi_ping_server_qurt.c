#include "qmi_ping_server.h"
#include "core_server_platform.h"
/*---------------------------------------------------------------------------
   QMI_PING_SERVER_QURT.C
---------------------------------------------------------------------------*/
/*!
  @file
    qmi_ping_server_qurt.c

  @brief
    This file contains the QuRT implementation of the ping service.

  ---------------------------------------------------------------------------
  Copyright (c) 2012 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/qmi/src/core_server/qmi_ping_server_qurt.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

extern void ping_server_handle_event
(
  ping_server *me,
  void *event
);

void ping_server_event_loop(void  *param)
{
   unsigned int wait_on,sig_received;
   qmi_csi_os_params         *os_params; 

   ping_server     *ping_srv_obj;
   ping_srv_obj =  (ping_server *)param;
   os_params = ping_server_get_os_params(ping_srv_obj);
   wait_on = QMI_PING_SVC_WAIT_SIG;

   while (1) {
       qurt_anysignal_wait(os_params->signal, wait_on);
       sig_received = qurt_anysignal_get(os_params->signal);
       qurt_anysignal_clear(os_params->signal, sig_received);
       ping_server_handle_event(ping_srv_obj,
                                (void *)sig_received);
   }
}



