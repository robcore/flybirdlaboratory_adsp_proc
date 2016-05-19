#ifndef IPC_ROUTER_OS_H
#define IPC_ROUTER_OS_H

/*===========================================================================

                    I P C    R O U T E R   O S   R E X

   This file describes the QURT interface to the IPC Router.
   This file must be compatible with all operating systems on which the 
   router will be used.

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/ipc_router/inc/ipc_router_os.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/04/09   ap      Klockwork fixes
07/01/09   ap      Changed IPC_ROUTER_OS_MESSAGE macro to directly call MSG_* 
05/07/09   sa      Removed flow control ioctl, switched to ping mechanism
02/03/09   sa      Moved in network order macros from DS header
10/16/08   sa      Added ipc_router_get_fc_status function
04/08/08   sa      Switched back to using IPC_ROUTER_OS_MESSAGE macro
03/20/08   sa      Switched to using ipc_router_os_message function
                   and added smem logging 
10/31/07   rr      Fix signals so we only use ONCIPC_REPLY_SIG
08/24/07   bfc     Increased the size of the IPC_ROUTER_CLIENT_QUEUE_SIZE.
04/10/07   rr      Initial Draft
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "customer.h"
#include "comdef.h"
#include "stdlib.h"
#include "string.h" 
#include "qurt.h"
#include "err.h"
#include "msg.h"
#ifdef FEATURE_SMEM_LOG
  #include "smem_log.h"
#endif

#ifdef FEATURE_WINCE
  #define inline __inline
#endif

/*===========================================================================
                CONSTANT / MACRO DACLARATIONS
===========================================================================*/

/***************************************************************************
 * Define each message level to point to appropiate message handles. 
 ***************************************************************************/
#define IPC_ROUTER_MSG_EMERG(msg,param1,param2,param3)   \
	    ERR_FATAL(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_CRIT(msg,param1,param2,param3)    \
	    ERR_FATAL(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_ERR(msg,param1,param2,param3)     \
	    MSG_ERROR(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_ALERT(msg,param1,param2,param3)   \
	    MSG_ERROR(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_NOTICE(msg,param1,param2,param3)  \
	    MSG_MED(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_WARNING(msg,param1,param2,param3) \
	    MSG_MED(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_DEBUG(msg,param1,param2,param3)   \
	    MSG_LOW(msg, param1, param2, param3)
#define IPC_ROUTER_MSG_INFO(msg,param1,param2,param3)    \
	    MSG_LOW(msg, param1, param2, param3)
#ifdef FEATURE_SMEM_LOG
  #define IPC_ROUTER_MSG_SMEM_LOG(msg,param1,param2,param3) \
            SMEM_LOG_EVENT((param1 | SMEM_LOG_IPC_ROUTER_EVENT_BASE), \
                           param2, param3, (uint32)qurt_thread_get_id())
#else
  #define IPC_ROUTER_MSG_SMEM_LOG(msg,param1,param2,param3) 
#endif

/***************************************************************************
 * IPC_ROUTER_OS_MESSAGE redirects calls based on level.
 ***************************************************************************/
#define IPC_ROUTER_OS_MESSAGE(level, msg, param1,param2,param3) \
	    level (msg,param1,param2,param3)


/*===========================================================================
                      TYPE DECLARATIONS                     
===========================================================================*/

/*===========================================================================
                         MACRO DACLARATIONS
===========================================================================*/
#define ipc_router_os_sem qurt_mutex_t

#define ipc_router_os_malloc(size)  \
            malloc(size)

#define ipc_router_os_free(ptr)  \
            free(ptr)

#define ipc_router_os_calloc(num,size)  \
            calloc(num,size)

#define ipc_router_os_mem_set(ptr,value,size)\
            memset(ptr,value,size)

#define ipc_router_os_sem_init(sem) qurt_mutex_init(sem)
#define ipc_router_os_sem_lock(sem) qurt_mutex_lock(sem)
#define ipc_router_os_sem_unlock(sem) qurt_mutex_unlock(sem)
#define ipc_router_os_sem_deinit(sem) qurt_mutex_destroy(sem)

/*=============================================================================
  MACRO  ipc_router_os_mem_copy
=============================================================================*/
/*!
@brief
  Copy over from source buffer to destination buffer.

@param[in]  dst     Pointer to the destination buffer
@param[in]  d_len   Size in bytes of the destination buffer
@param[in]  src     Pointer to the source buffer
@param[in]  c_len   Size in bytes to copy from source to destination

@retval   Total number of bytes which were copied from source to destination
*/
/*=========================================================================*/
static __inline size_t ipc_router_os_mem_copy
(
  void *dest,
  size_t dest_len,
  void *src,
  size_t copy_len
)
{
  if(dest_len < copy_len)
  {
    copy_len = dest_len;
  }
  memcpy(dest, src, copy_len);
  return copy_len;
}

#endif /* IPC_ROUTER_OS_H */

