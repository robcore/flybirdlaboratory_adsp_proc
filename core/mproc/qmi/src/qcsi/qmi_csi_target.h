#ifndef QMI_CSI_TARGET_H
#define QMI_CSI_TARGET_H
/******************************************************************************
  @file    qmi_csi_target.h
  @brief   QuRT OS Specific routines internal to QCSI.

  DESCRIPTION
  This header provides an OS (QuRT) abstraction to QCSI.

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "qurt.h"
#include "smem_log.h"
#include "err.h"
#include "assert.h"
#include "qmi_common.h"
#include "qmi_idl_lib_internal.h"

typedef  qurt_mutex_t qmi_csi_lock_type;

#define LOCK(ptr)        qurt_mutex_lock(ptr)
#define UNLOCK(ptr)      qurt_mutex_unlock(ptr)
#define LOCK_INIT(ptr)   qurt_mutex_init(ptr)
#define LOCK_DEINIT(ptr) qurt_mutex_destroy(ptr)

#define MALLOC(size)      malloc(size)
#define CALLOC(num, size) calloc(num, size)
#define FREE(ptr)         free(ptr)
#define REALLOC(ptr,size) realloc(ptr, size)

#define QMI_CSI_OS_SIGNAL_SET(s) qurt_anysignal_set((s)->signal, (s)->sig)
#define QMI_CSI_OS_SIGNAL_WAIT(s) qurt_anysignal_wait((s)->signal, (s)->sig)
#define QMI_CSI_OS_SIGNAL_CLEAR(s) qurt_anysignal_clear((s)->signal, (s)->sig)

#define QMI_CSI_LOG_EVENT_TX            (SMEM_LOG_QMI_CSI_EVENT_BASE + 0x00)
#define QMI_CSI_LOG_EVENT_TX_EXT        (SMEM_LOG_QMI_CSI_EVENT_BASE + 0x04)
#define QMI_CSI_LOG_EVENT_RX            (SMEM_LOG_QMI_CSI_EVENT_BASE + 0x01)
#define QMI_CSI_LOG_EVENT_RX_EXT        (SMEM_LOG_QMI_CSI_EVENT_BASE + 0x05)
#define QMI_CSI_LOG_EVENT_ERROR         (SMEM_LOG_QMI_CSI_EVENT_BASE + 0x03)

#ifdef FEATURE_QMI_SMEM_LOG

#define QMI_CSI_OS_LOG_TX(header) \
  do { \
    uint8_t cntl_flag; \
    uint16_t txn_id, msg_id, msg_len; \
    decode_header(header, &cntl_flag, &txn_id, &msg_id, &msg_len); \
    SMEM_LOG_EVENT(QMI_CSI_LOG_EVENT_TX, cntl_flag << 16 | txn_id, msg_id << 16 | msg_len, 0); \
  } while(0)

#define QMI_CSI_OS_LOG_RX(header) \
  do { \
    uint8_t cntl_flag; \
    uint16_t txn_id, msg_id, msg_len; \
    decode_header(header, &cntl_flag, &txn_id, &msg_id, &msg_len); \
    SMEM_LOG_EVENT(QMI_CSI_LOG_EVENT_RX, cntl_flag << 16 | txn_id, msg_id << 16 | msg_len, 0); \
  } while(0)

#define QMI_CSI_OS_LOG_TX_EXT(header, svc_id, addr, addr_len) \
  do { \
    uint8_t cntl_flag; \
    uint16_t txn_id, msg_id, msg_len; \
    uint32_t __addr[MAX_ADDR_LEN/4] = {0};\
    memcpy(__addr, addr, addr_len); \
    decode_header(header, &cntl_flag, &txn_id, &msg_id, &msg_len); \
    SMEM_LOG_EVENT6(QMI_CSI_LOG_EVENT_TX_EXT, cntl_flag << 16 | txn_id, msg_id << 16 | msg_len, svc_id, __addr[0], __addr[1], __addr[2]); \
  } while(0)

#define QMI_CSI_OS_LOG_RX_EXT(header, svc_id, addr, addr_len) \
  do { \
    uint8_t cntl_flag; \
    uint16_t txn_id, msg_id, msg_len; \
    uint32_t __addr[MAX_ADDR_LEN/4] = {0};\
    memcpy(__addr, addr, addr_len); \
    decode_header(header, &cntl_flag, &txn_id, &msg_id, &msg_len); \
    SMEM_LOG_EVENT6(QMI_CSI_LOG_EVENT_RX_EXT, cntl_flag << 16 | txn_id, msg_id << 16 | msg_len, svc_id, __addr[0], __addr[1], __addr[2]); \
  } while(0)

#else
#define QMI_CSI_OS_LOG_TX(header) 
#define QMI_CSI_OS_LOG_RX(header) 

#endif

#define QMI_CSI_OS_LOG_ERROR() qcsi_log_error(__FILE__, __LINE__)

size_t strlcpy(char *dst, const char *src, size_t siz);
static __inline void qcsi_log_error(char *filename, unsigned int line)
{
  uint32 name[5];
  char *last;
  last = strrchr(filename, '/');
  if(!last)
    last = strrchr(filename, '\\');
  last = last ? (last+1) : filename;
  strlcpy((char *)name, last, sizeof(name));
#ifdef FEATURE_QMI_SMEM_LOG
  SMEM_LOG_EVENT6(QMI_CSI_LOG_EVENT_ERROR, name[0], name[1], name[2], name[3], 
      name[4], line);
#endif
#ifdef FEATURE_QMI_MSG
  MSG_ERROR("Runtime error. File 0x%s, Line: %d", filename, line, 0);
#endif
}
#endif
