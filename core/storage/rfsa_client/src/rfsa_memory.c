/******************************************************************************
 * rfsa_memory.c
 *
 * RFSA memory functions
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_memory.c#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-02-20   nr      Create.
=============================================================================*/
#include "comdef.h"
#include "rfsa_errno.h"
#include "rfsa_log.h"


#include <sys/mman.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef RFSA_ANDROID

int32
rfsa_mmap (uint32 physical_addr, uint32 size, void **virtual_addr)
{
  int mem_fd;
  int32 ret_val;

  ret_val = RFSA_MMAP_FAILED;
  /* Use /dev/mem to read the physical address provided */
  mem_fd = open ("/dev/mem", O_RDWR);
  if(mem_fd < 0)
  {
    LOGE ("/dev/mem open failed\n");
    return ret_val;
  }

  *virtual_addr = mmap(NULL, size, PROT_READ | PROT_WRITE,
							         MAP_SHARED, mem_fd, physical_addr);

  if (*virtual_addr != MAP_FAILED)
  {
    LOGE ("mmap failed with errno %d\n", errno);
    ret_val = RFSA_EOK;
  }
  else
  {
    LOGE ("mmap success!! %d\n");
  }
  return ret_val;
}

#else

#include "DALSys.h"
#include "DALSysTypes.h"

#define RFSA_UINT32_MAX 0x00000000FFFFFFFF

int32
rfsa_mmap (uint64 physical_addr, uint32 size, void **virtual_addr)
{
  int32 ret_val;
  DALSYSMemHandle handle;
  DALSYSMemInfo mem_info;
  DALResult result;
  uint32 mem_attr = (DALSYS_MEM_PROPS_UNCACHED | DALSYS_MEM_PROPS_PHYS_CONT);

  *virtual_addr = NULL;
  ret_val = RFSA_MMAP_FAILED;

  if (physical_addr >= RFSA_UINT32_MAX)
  {
    LOGE("Physical address exceeds 32-bit max");
    return ret_val;
  }

  result = DALSYS_MemRegionAlloc (mem_attr, DALSYS_MEM_ADDR_NOT_SPECIFIED,
                                  (DALSYSMemAddr) physical_addr, size,
                                  &handle, NULL);
  if (DAL_SUCCESS == result)
  {
    result = DALSYS_MemInfo (handle, &mem_info);
    if (result == DAL_SUCCESS)
    {
      *virtual_addr = (void *)(mem_info.VirtualAddr);
      if (*virtual_addr != NULL)
      {
        //LOGD("mmap successful");
        ret_val = RFSA_EOK;
      }
      else
      {
        LOGE("Invalid (NULL) virtual address");
      }
    }
    else
    {
      LOGE("Failed to retrieve memory object handle");
    }
  }
  else
  {
    LOGE("Failed to map physical address to virtual");
  }
  return ret_val;
}

/*
int32
rfsa_mmap (uint64 physical_addr, uint32 size, void **virtual_addr)
{
  int32 ret_val;
  DALSYSMemHandle handle;
  DALSYSMemInfoEx mem_info;
  DALSYS_MEM_REQ_OBJECT(mem_req);
  DALResult result;

  *virtual_addr = NULL;
  ret_val = RFSA_MMAP_FAILED;

  mem_req.memInfo.physicalAddr = (DALSYSPhyAddr) physical_addr;
  mem_req.memInfo.virtualAddr = DALSYS_MEM_ADDR_NOT_SPECIFIED;
  mem_req.memInfo.size = (DALSYSMemAddr) size;
  mem_req.memInfo.cacheType = DALSYS_MEM_CACHE_NONE;

  result = DALSYS_MemRegionAllocEx (&handle, &mem_req, &mem_info);
  if (DAL_SUCCESS == result)
  {
    *virtual_addr = (void *)(mem_info.virtualAddr);
    if (*virtual_addr != NULL)
    {
      ret_val = RFSA_EOK;
    }
  }
  return ret_val;
}

int32
rfsa_mmap (uint64 physical_addr, uint32 size, void **virtual_addr)
{
  int32 ret_val;
  DALSYSMemHandle handle;
  DALSYSMemInfoEx mem_info;
  DALResult result;

  *virtual_addr = NULL;
  ret_val = RFSA_MMAP_FAILED;

  mem_info.PhysicalAddr = (DALSYSMemAddr64) physical_addr;
  mem_info.VirtualAddr = DALSYS_MEM_ADDR_NOT_SPECIFIED;
  mem_info.dwLen = size;
  mem_info.dwProps = (DALSYS_MEM_PROPS_UNCACHED |
                         DALSYS_MEM_PROPS_PHYS_CONT);

  result = DALSYS_MemRegionAllocEx (&mem_info, &handle, NULL);
  if (DAL_SUCCESS == result)
  {
    *virtual_addr = (void *)(mem_info.VirtualAddr);
    if (*virtual_addr != NULL)
    {
      ret_val = RFSA_EOK;
    }
  }
  return ret_val;
}

*/

#endif

