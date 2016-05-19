/******************************************************************************
  @file    qmi_fw_init.c
  @brief   QMI framework init

  DESCRIPTION
  QMI framework init module
   
  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include "qmi_idl_lib.h"
#include "qmi_csi.h"
#include "qmi_csi_target.h"
#include "qmi_csi_common.h"
#include "qmi_client.h"
#include "qmi_cci_target.h"
#include "qmi_cci_common.h"
#ifdef FEATURE_QMI_NATIVE_IPC_ROUTER
#include "ipc_router_core.h"
#endif

extern qmi_csi_xport_ops_type qcsi_ipc_ops;
extern qmi_cci_xport_ops_type qcci_ipc_ops;

/* Loopback */
extern qmi_csi_xport_ops_type qcsi_loopback_ops;
extern qmi_cci_xport_ops_type qcci_loopback_ops;
extern void qmi_loopback_xport_init(void);

extern void qmi_ping_service_start(void);
extern void qmi_ping_client_start(void);
extern void qmi_si_init(void);
static int qmi_fw_inited = 0;

#ifdef FEATURE_QMI_NATIVE_IPC_ROUTER
static void *tx_buf;
static uint32 tx_len;

static void rx_cb
(
 ipc_router_client_type     *client,
 void                       *cb_data,
 ipc_router_packet_type     *msg,
 ipc_router_address_type    *src_addr,
 uint32                      len,
 boolean                     confirm_rx
 )
{
  ipc_router_service_type service = {0x101, 0x101};
  ipc_router_address_type addr;
  void *buf;

  if(confirm_rx)
  {
    ipc_router_core_send_conf(client, src_addr);
  }

  if(tx_buf)
  {
    free(tx_buf);
    tx_buf = NULL;
  }

  buf = malloc(len);

  if(!buf)
  {
    ipc_router_packet_free(&msg);
    return;
  }

  ipc_router_packet_read(&msg, buf, len);

  if(ipc_router_core_find_server(client, &service, &addr, NULL, NULL) ==
      IPC_ROUTER_STATUS_SUCCESS)
  {
    ipc_router_core_send(client, &addr, buf, len);
  }

  if(ipc_router_core_send(client, src_addr, buf, len) == IPC_ROUTER_STATUS_BUSY)
  {
    tx_buf = buf;
    tx_len = len;
  }
  else
  {
    free(buf);
  }

  ipc_router_packet_free(&msg);
}

static void event_cb
(
 ipc_router_client_type *client,
 void *data,
 ipc_router_event_type event,
 ipc_router_event_info_type *info
 )
{
  if(event == IPC_ROUTER_EVENT_RESUME_TX && tx_buf)
  {
    ipc_router_core_send(client, &info->client, tx_buf, tx_len);
    free(tx_buf);
    tx_buf = NULL;
  }
}

static void start_echo_service(void)
{
  ipc_router_client_type *cl;

  /* Create an echo server */
  if(ipc_router_core_open(&cl, 0, rx_cb, NULL, event_cb, NULL) ==
      IPC_ROUTER_STATUS_SUCCESS)
  {
    ipc_router_service_type service = {0x100, 0x100};
    ipc_router_core_reg_server(cl, &service);
  }
}

#endif

void qmi_fw_init(void)
{
  if(qmi_fw_inited)
    return;
  qmi_fw_inited = 1;

  /* TODO Enable when there are users */
//  qmi_si_init();

  qmi_cci_common_init();

#ifdef FEATURE_QMI_NATIVE_IPC_ROUTER
  start_echo_service();
#endif

#ifdef FEATURE_QMI_LOOPBACK_TRANSPORT
  /* Add the loopback transport only to User PD */
  qmi_loopback_xport_init();
  qmi_csi_xport_start(&qcsi_loopback_ops, NULL);
  qmi_cci_xport_start(&qcci_loopback_ops, NULL);
#endif

  /* IPC Router transport with QCSI & QCCI */
  qmi_csi_xport_start(&qcsi_ipc_ops, NULL);
  qmi_cci_xport_start(&qcci_ipc_ops, NULL);

#ifdef FEATURE_QMI_TEST_SERVICE_COMPONENTS
  qmi_ping_service_start();

/* Ping client enabled only for bringup testing eng builds */
//  qmi_ping_client_start();
#endif
}

