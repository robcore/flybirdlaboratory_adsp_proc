/*========================================================================

  Copyright (c) 2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.
  ====================================================================== */
#ifndef FASTRPC_INVOKE_H
#define FASTRPC_INVOKE_H

#include "remote64.h"
#include "qurt_types.h"
#include "AEEStdDef.h"
#include "fastrpc_port.h"
#include "fastrpc_internal.h"
#include "HAP_farf.h"
#include "verify.h"

#define PAGE_SIZE  0x1000
#define PAGE_MASK  ~(PAGE_SIZE-1)
static __inline void* uint64_to_ptr(uint64 pv) {
   void* rv = (void*)(uintptr_t)pv;
   if((uint64)(uintptr_t)rv != pv) {
      FARF(MEDIUM, "uint64 to void* conversion error");
   }
   return rv;
}
static __inline uint32 uint64_to_uint32(uint64 pv) {
   uint32 rv = (uint32)pv;
   if((uint64)rv != pv) {
      FARF(MEDIUM, "uint64 to uint32 conversion error");
   }
   return rv;
}
static __inline uintptr_t uint64_to_uintptr(uint64 pv) {
   uintptr_t rv = (uintptr_t)pv;
   if((uint64)rv != pv) {
      FARF(MEDIUM, "uint64 to uintptr_t conversion error");
   }
   return rv;
}
static __inline int uint64_to_int(uint64 pv) {
   int rv = (int)pv;
   if((uint64)rv != pv) {
      FARF(MEDIUM, "uint64 to int conversion error");
   }
   return rv;
}
static __inline int int64_to_int(int64 pv) {
   int rv = (int)pv;
   if((int64)rv != pv) {
      FARF(MEDIUM, "int64 to int conversion error");
   }
   return rv;
}
static __inline qurt_addr_t uint64_to_qurt_addr(uint64 pv) {
   qurt_addr_t rv = (qurt_addr_t)pv;
   if((uint64)rv != pv) {
      FARF(MEDIUM, "64 to qurt_addr_t conversion error");
   }
   return rv;
}
static __inline qurt_addr_t ptr_to_qurt_addr(void* pv) {
   qurt_addr_t rv = (qurt_addr_t)pv;
   if((void*)rv != pv) {
      FARF(MEDIUM, "ptr to qurt_addr_t conversion error");
   }
   return rv;
}
static __inline uint64 ptr_to_uint64(void* pv) {
   C_ASSERT(sizeof(uint64) >= sizeof(void*));
   return (uint64)(uintptr_t)pv;
}

static __inline uint64 buf_page_start(uint64 buf) {
   uint64 start = buf & PAGE_MASK;
   return start;
}
static __inline uint64 buf_page_start_ptr(void* pv) {
   return buf_page_start((uintptr_t)pv);
}

static __inline uint64 buf_page_offset(uint64 buf) {
   uint64 offset = buf & (PAGE_SIZE-1);
   return offset;
}
static __inline uint64 buf_page_offset_ptr(void* pv) {
   return buf_page_offset((uintptr_t)pv);
}


static __inline uint64 buf_page_size(uint32 size) {
   uint64 sz = (size + (PAGE_SIZE - 1)) & PAGE_MASK;
   return sz;
}

static __inline uint64 buf_page_aligned_size(uint64 buf, int64 size) {
   uint64 end = buf + size + (PAGE_SIZE-1);
   uint64 sz = buf_page_start(end) - buf_page_start(buf);
   return sz;
}

static __inline uint64 buf_page_aligned_size_ptr(void *buf, uint32 size) {
   return buf_page_aligned_size(ptr_to_uint64(buf), size);
}

struct fastrpc_invoke_process;

struct fastrpc_invoke_thread {
   struct fastrpc_invoke_process* pinfo;
   qurt_mem_region_t iregion;
   uint32 inval;
   void* buf;
   int bufSize;
   uint32 sc;
   remote_arg* lpra;
   remote_arg64* rpra;
   int nStaticMaps;
   void (*rsp_fn)(void* ctx, int ret);
   void* rsp_ctx;
};

int fastrpc_get_cache_attr(struct fastrpc_invoke_process* pinfo, boolean bInBuf, qurt_mem_cache_mode_t* pattr);
int fastrpc_set_cache_attr(struct fastrpc_invoke_process* pinfo, boolean bInBuf, qurt_mem_cache_mode_t attr);

int fastrpc_invoke_thread_init(struct fastrpc_invoke_process* pinfo, 
                               struct fastrpc_invoke_thread* tn,
                               void (*rsp_fn)(void* ctx, int ret),
                               void* ctx);

void fastrpc_invoke_thread_deinit(struct fastrpc_invoke_thread* me);

void fastrpc_invoke_dispatch(struct fastrpc_invoke_thread* tn,
                             struct fastrpc_port_msg* msg);

int fastrpc_invoke_mmap_create32(struct fastrpc_invoke_process* pinfo,
                                 uint32 flags, uint32 virt, struct smq_phy_page32 *pgstart,
                                 int numPages, uint32* vaddrout);
int fastrpc_invoke_mmap_create(struct fastrpc_invoke_process* pinfo,
                               uint32 flags, uint64 virt, struct smq_phy_page *pgstart,
                               int numPages, uint64* vaddrout);
int fastrpc_invoke_mmap_addref(struct fastrpc_invoke_process* pinfo,
                               void* buf, int bufLen, uint32 flags);
int fastrpc_invoke_mmap_release(struct fastrpc_invoke_process* pinfo,
                                void* buf, int bufLen);
int fastrpc_invoke_mmap_destroy(struct fastrpc_invoke_process* pinfo,
                                void* buf, int bufLen);

int fastrpc_invoke_process_create(struct fastrpc_invoke_process **po);
void fastrpc_invoke_process_destroy(struct fastrpc_invoke_process *po);

int fastrpc_mapping_create(qurt_addr_t vaddr, qurt_addr_t paddr, qurt_size_t size, qurt_mem_cache_mode_t cache, qurt_perm_t perm);
int fastrpc_mapping_remove(qurt_addr_t vaddr, qurt_addr_t paddr, qurt_size_t size);

#endif
