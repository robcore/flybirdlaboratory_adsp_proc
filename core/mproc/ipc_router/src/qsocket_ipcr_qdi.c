/*===========================================================================

                 Q S O C K E T   I P C R   Q D I

   This file provides the qsocket stubs to access the IPC Router QDI Driver

  ---------------------------------------------------------------------------
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/ipc_router/src/qsocket_ipcr_qdi.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/01/14   aep     Initial Creation
==========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include <stddef.h>
#include "qsocket_ipcr.h"
#include "ipc_router_qdi_driver.h"
#include "qurt_qdi_driver.h"
#include "ipc_router_core.h"
#include "stdint.h"
#include "timer.h"

/*===========================================================================
                      MACROS AND DEFINES
===========================================================================*/
typedef struct qsockaddr_ipcr ipcr_addr_t;

#define IPCR_ADDR_VALID(aptr, alen) ((aptr) && ((alen) >= sizeof(ipcr_addr_t)) && ((aptr)->sa_family == AF_IPC_ROUTER))

/* Each FD opened by the user to IPC Router's QDI driver, may have
 * multiple addressable handles (Port on IPC Router). Even though it
 * is allowed, Qsockets will open on one handle per FD. Thus, to simplify
 * (use the FD as the handle handed out to the user on socket()),
 * we take advantage of the knowledge that the first handle will always
 * be 0x1. */
#define IPC_ROUTER_QDI_EXP_HANDLE 0x1

/*===========================================================================
                      PRIVATE METHODS
===========================================================================*/
static int err_ipcr_to_sock(int ipcr_err)
{
  int ret;
  switch(ipcr_err)
  {
    case IPC_ROUTER_STATUS_SUCCESS:
      ret = 0;
      break;
    case IPC_ROUTER_STATUS_NO_MEM:
    case IPC_ROUTER_QDI_NO_MEM_ERR:
      ret = QENOMEM;
      break;
    case IPC_ROUTER_STATUS_BUSY:
      ret = QEAGAIN;
      break;
    case IPC_ROUTER_QDI_HUNGUP_ERR:
    case IPC_ROUTER_STATUS_INVALID_ENDPOINT:
      ret = QECONNRESET;
      break;
    case IPC_ROUTER_QDI_PARAM_ERR:
      ret = QEINVAL;
      break;
    case IPC_ROUTER_QDI_NO_SPACE_ERR:
      ret = QEMSGSIZE;
      break;
    case IPC_ROUTER_QDI_PERM_ERR:
      ret = QEFAULT;
    case IPC_ROUTER_QDI_NOT_SUPP_ERR:
      ret = QEOPNOTSUPP;
      break;
    case IPC_ROUTER_QDI_BADF_ERR:
      ret = QEBADF;
      break;
    case IPC_ROUTER_QDI_TIMEOUT_ERR:
      ret = QEAGAIN;
      break;
    default:
      ret = QEFAULT;
      break;
  }
  return ret;
}

/*===========================================================================
  FUNCTION  qsocket
===========================================================================*/
int qsocket(int domain, int type, int protocol)
{
  int fd, rc, handle = 0;

  if(domain != AF_IPC_ROUTER)
  {
    return QEAFNOTSUPP;
  }

  if(type != QSOCK_DGRAM && type != QSOCK_STREAM)
  {
    return QEOPNOTSUPP;
  }

  fd = qurt_qdi_open(IPC_ROUTER_QDI_DEV_NAME, NULL, NULL, NULL);
  if(fd < 0)
  {
    /* QENODEV? */
    return QEFAULT;
  }

  /* each fd can have multiple sub-handles. This is used by ipc_router_qdi_user
   * but for sockets, we will have just 1 sub handle for each fd. So, we 
   * are expecting the returned handle to be 1 */
  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_OPEN, &handle, 0, NULL, NULL);
  if(rc < 0 || handle != IPC_ROUTER_QDI_EXP_HANDLE)
  {
    qurt_qdi_close(fd);
    if(rc < 0)
      rc = err_ipcr_to_sock(rc);
    else
      rc = QEFAULT;
    return rc;
  }

  return fd;
}

/*===========================================================================
  FUNCTION  qconnect
===========================================================================*/
int qconnect(int fd, struct qsockaddr *addr, qsocklen_t addrlen)
{
  ipcr_addr_t *dest;
  ipc_router_address_type ipc_addr;
  int rc;

  if(!IPCR_ADDR_VALID(addr, addrlen))
  {
    return QEINVAL;
  }
  dest = (ipcr_addr_t *)addr;

  if(dest->address.addrtype != IPCR_ADDR_PORT)
  {
    return QEINVAL;
  }
  ipc_addr.processor_id = (uint32)dest->address.addr.port_addr.node_id;
  ipc_addr.port_id = (uint32)dest->address.addr.port_addr.port_id;

  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_CONNECT, 
                                IPC_ROUTER_QDI_EXP_HANDLE, &ipc_addr);
  
  return err_ipcr_to_sock(rc);
}

/*===========================================================================
  FUNCTION  qclose
===========================================================================*/
int qclose(int fd)
{
  int rc;
  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_CLOSE, 
                                IPC_ROUTER_QDI_EXP_HANDLE);
  if(rc != 0)
  {
    return err_ipcr_to_sock(rc);
  }
  rc = qurt_qdi_close(fd);
  return rc == 0 ? 0 : QEBADF;
}

/*===========================================================================
  FUNCTION  qshutdown
===========================================================================*/
int qshutdown(int fd, int how)
{
  /* Currently all forms of 'how' ends up being QSHUT_RDWR */
  return qclose(fd);
}

/*===========================================================================
  FUNCTION  qbind
===========================================================================*/
int qbind(int fd, struct qsockaddr *_addr, qsocklen_t addrlen)
{
  ipcr_addr_t *addr;
  ipc_router_service_type service;
  int rc;

  if(!IPCR_ADDR_VALID(_addr, addrlen))
  {
    return QEINVAL;
  }
  addr = (ipcr_addr_t *)_addr;

  if(addr->address.addrtype != IPCR_ADDR_NAME)
  {
    return QENOTSUPP;
  }

  service.type = addr->address.addr.port_name.service;
  service.instance = addr->address.addr.port_name.instance;

  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_REGISTER_SERVER, 
                              IPC_ROUTER_QDI_EXP_HANDLE, &service);
  return err_ipcr_to_sock(rc);
}


/*===========================================================================
  FUNCTION  ipcr_find_name
===========================================================================*/
int ipcr_find_name(int fd, ipcr_name_t *name, struct qsockaddr_ipcr *addrs, 
                    unsigned int *instances, unsigned int *io_num_entries, 
                    unsigned int flags)
{
  int rc;
  uint32_t mask = (flags & IPCR_FLAGS_ANY_INSTANCE) ? 0 : 0xffffffff;
  ipc_router_service_type service;
  uint32_t num_entries, num_servers, i;
  ipc_router_server_type *servers = NULL;

  if(!name || !addrs || !io_num_entries || !*io_num_entries)
  {
    return QEINVAL;
  }

  service.type = (uint32)name->service;
  service.instance = (uint32)name->instance;

  num_entries = (unsigned int)*io_num_entries;
  servers = ipc_router_os_malloc(num_entries * sizeof(*servers));
  if(!servers)
  {
    return QENOMEM;
  }

  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_FIND_ALL_SERVERS, IPC_ROUTER_QDI_EXP_HANDLE,
                              &service, servers, &num_entries, &num_servers, mask);
  if(rc == 0)
  {
    rc = (int)num_servers;
    *io_num_entries = (unsigned int)num_entries;
    for(i = 0; i < num_entries; i++)
    {
      addrs[i].sa_family = AF_IPC_ROUTER;
      addrs[i].address.addrtype = IPCR_ADDR_PORT;
      addrs[i].address.addr.port_addr.node_id = (uint32_t)servers[i].addr.processor_id;
      addrs[i].address.addr.port_addr.port_id = (uint32_t)servers[i].addr.port_id;
      if(instances)
        instances[i] = servers[i].service.instance;
    }
  }
  else
  {
    rc = 0;
  }
  ipc_router_os_free(servers);

  return rc;
}


int qgetsockopt(int fd, int level, int optname, 
                  void *optval, qsocklen_t *optlen)
{
  return QEOPNOTSUPP;
}



int qsetsockopt(int fd, int level, int optname, 
                 void *optval, qsocklen_t optlen)
{
  ipc_router_qdi_port_options options = {0};
  int rc = 0;

  switch(level)
  {
    case QSOL_SOCKET:
      switch(optname)
      {
        case QSO_SNDTIMEO:
          if(!optval || optlen < sizeof(int))
          {
            rc = QEINVAL;
            break;
          }
          options.sendtimeo_valid = 1;
          options.sendtimeo = *((uint32_t *)optval);
          rc = 0;
          break;
        case QSO_RCVTIMEO:
          if(!optval || optlen < sizeof(int))
          {
            rc = QEINVAL;
            break;
          }
          options.rcvtimeo_valid = 1;
          options.rcvtimeo = *((uint32_t *)optval);
          rc = 0;
          break;
        default:
          rc = QEOPNOTSUPP;
          break;
      }
      break;
    case QSOL_IPC_ROUTER:
      switch(optname)
      {
        case QSO_IPCR_SET_CONTROL_PORT:
          options.ctrl_port_valid = 1;
          options.allowed_valid = 1;
          options.allowed_flag = EVENT_ALLOWED;
          rc = 0;
          break;
        case QSO_IPCR_SET_SERVICE_PREF:
          options.type_pref_valid = 1;
          options.type_pref = *((uint32_t *)optval);
          rc = 0;
          break;
        default:
          rc = QEOPNOTSUPP;
          break;
      }
      break;
    default:
      rc = QEOPNOTSUPP;
      break;
  }
  if(rc != 0)
    return rc;
  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_SET_PORT_OPTIONS, 
                                IPC_ROUTER_QDI_EXP_HANDLE, &options);
  return err_ipcr_to_sock(rc);
}


/*===========================================================================
  FUNCTION  qsendto
===========================================================================*/
int qsendto(int fd, void *buf, size_t len, int flags, 
              struct qsockaddr *_addr, qsocklen_t addrlen)
{
  ipcr_addr_t *addr;
  ipc_router_address_type iaddr;
  int rc;
  uint32 drv_flags = 0;

  if(!buf || !len ||
      (_addr && !IPCR_ADDR_VALID(_addr, addrlen)))
  {
    return QEINVAL;
  }

  addr = (ipcr_addr_t *)_addr;

  if(addr && addr->address.addrtype == IPCR_ADDR_NAME)
  {
    ipc_router_service_type service;

    service.type = (uint32)addr->address.addr.port_name.service;
    service.instance = (uint32)addr->address.addr.port_name.instance;

    rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_SEND_TO_NAME, 
                        IPC_ROUTER_QDI_EXP_HANDLE, &service, buf, len);
    return rc == IPC_ROUTER_STATUS_SUCCESS ? (int)len : err_ipcr_to_sock(rc);
  }

  if(addr && addr->address.addrtype != IPCR_ADDR_PORT)
  {
    return QEINVAL;
  }

  if(addr)
  {
    iaddr.processor_id = (uint32)addr->address.addr.port_addr.node_id;
    iaddr.port_id = (uint32)addr->address.addr.port_addr.port_id;
  }

  if(flags & QMSG_DONTWAIT)
  {
    drv_flags |= IPC_ROUTER_QDI_WRFLAG_DONTWAIT;
  }

  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_SEND, IPC_ROUTER_QDI_EXP_HANDLE,
                              addr ? &iaddr : NULL, buf, len, drv_flags);

  return rc == IPC_ROUTER_STATUS_SUCCESS ? (int)len : err_ipcr_to_sock(rc);
}

/*===========================================================================
  FUNCTION  qsend
===========================================================================*/
int qsend(int fd, void *buf, size_t len, int flags)
{
  return qsendto(fd, buf, len, flags, NULL, 0);
}

/*===========================================================================
  FUNCTION  qrecvfrom
===========================================================================*/
int qrecvfrom(int fd, void *buffer, size_t len, int flags, 
               struct qsockaddr *_addr, qsocklen_t *addrlen)
{
  ipcr_addr_t *addr;
  ipc_router_address_type src_addr;
  int rc;
  uint32_t drv_flags = 0;

  if((len > 0 && !buffer) ||
     (_addr && !addrlen) ||
     (_addr && *addrlen < sizeof(ipcr_addr_t)))
  {
    return QEINVAL;
  }
  addr = (ipcr_addr_t *)_addr;

  if(flags & QMSG_PEEK)
  {
    drv_flags |= IPC_ROUTER_QDI_RDFLAG_MSGPEEK;
  }
  if(flags & QMSG_DONTWAIT)
  {
    drv_flags |= IPC_ROUTER_QDI_RDFLAG_DONTWAIT;
  }
  if(flags & QMSG_TRUNC)
  {
    drv_flags |= IPC_ROUTER_QDI_RDFLAG_TRUNC;
  }

  rc = qurt_qdi_handle_invoke(fd, IPC_ROUTER_QDI_READ, buffer, len, 
                              addr ? &src_addr : NULL, NULL, &len, NULL, drv_flags);
  if(addr)
  {
    *addrlen = sizeof(ipcr_addr_t);
    addr->sa_family = AF_IPC_ROUTER;
    if(rc == IPC_ROUTER_STATUS_SUCCESS)
    {
      addr->address.addrtype = IPCR_ADDR_PORT;
      addr->address.addr.port_addr.node_id = (uint32_t)src_addr.processor_id;
      addr->address.addr.port_addr.port_id = (uint32_t)src_addr.port_id;
    }
  }
  return rc == IPC_ROUTER_STATUS_SUCCESS ? (int)len : err_ipcr_to_sock(rc);
}

/*===========================================================================
  FUNCTION  qrecv
===========================================================================*/
int qrecv(int fd, void *buf, size_t len, int flags)
{
  return qrecvfrom(fd, buf, len, flags, NULL, NULL);
}


/*===========================================================================
  FUNCTION  qpoll
===========================================================================*/
int qpoll(struct qpollfd *pfd, qnfds_t num, int timeout_ms)
{
  int rc;

  if(!pfd || !num)
  {
    return QEINVAL;
  }

  /* Use the first FD to get to IPC Router's QDI Driver */
  rc = qurt_qdi_handle_invoke(pfd[0].fd, IPC_ROUTER_QDI_POLL, pfd, num, timeout_ms);

  return rc < 0 ? err_ipcr_to_sock(rc) : rc;
}

void qsocket_init(void)
{
  /* Dummy function, nothing to do */
}

