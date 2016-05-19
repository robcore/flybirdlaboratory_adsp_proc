/*=========================================================================
                       QDSS e-fuse check

GENERAL DESCRIPTION
   The interface to check efuses associated with the QDSS for accessing its
   trace functionality is implemented. The fuses that are checked include
   DBGEN, SPIDEN, NIDEN and SPNIDEN. The functionality controlled by the fuses
   are as follows. DBGEN controls non-secure invasive debugging, SPIDEN controls
   secured invasive debugging, NIDEN controls non-secure non-invasive debugging
   and SPNIDEN controls secure non-invasive debugging.

   According to the ARM Coresight architecture, in all cases, the fuse
   setting for invasive debugging overrides settings for non-invasive debugging.

EXTERNALIZED FUNCTIONS
   qdss_fuse_trace_access

INITIALIZATION AND SEQUENCING REQUIREMENTS
   Requires System FPB clock to access the efuse registers.

==========================================================================*/
/*=============================================================================
  Copyright (c) 2012-2014 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*==========================================================================
 $Header: //components/rel/core.adsp/2.6.1/debugtrace/common/src/qdss_fuse_check_dal.c#1 $
==========================================================================*/

/*---------------------------------------------------------------------------
 * Include Files
 * ------------------------------------------------------------------------*/

#include "qdss_fuse_check.h"
#include "halhwio_qdss.h"
#include "qdss_fuse_regs.h"
#include "DALSys.h"

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ------------------------------------------------------------------------*/

#define HWIO_PAGE_SIZE 0x1000  // Page size for HWIO regions - 4K.

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * ------------------------------------------------------------------------*/

static volatile uint32 SECURITY_CONTROL_BASE_PTR = NULL;

/*---------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ------------------------------------------------------------------------*/

/* Define macro to get the page base and offset given an address. */
#define HWIO_PAGE_BASE(nAddr)   ((nAddr) & ~(HWIO_PAGE_SIZE - 1))
#define HWIO_PAGE_OFFSET(nAddr) ((nAddr) & (HWIO_PAGE_SIZE - 1))


static DALResult qdss_efuse_memmap(uint32 physAddr,
                                  uint32 size,
                                  DALSYSMemHandle *phMem,
                                  DALSYSMemInfo *pMemInfo)
{
   uint32 offset;

   offset = HWIO_PAGE_OFFSET(physAddr);

   if (DAL_SUCCESS != DALSYS_MemRegionAlloc(DALSYS_MEM_PROPS_UNCACHED,
                                  DALSYS_MEM_ADDR_NOT_SPECIFIED,
                                  HWIO_PAGE_BASE(physAddr),
                                  size, phMem, NULL ))
   {
      return DAL_ERROR;
   }

   DALSYS_MemInfo(*phMem, pMemInfo);
   pMemInfo->VirtualAddr  += offset;
   pMemInfo->PhysicalAddr += offset;
   pMemInfo->dwLen        -= offset;

   return DAL_SUCCESS;
}


/*---------------------------------------------------------------------------
 * Externalized Function Definitions
 * ------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
int qdss_fuse_trace_access(void)
{
   int status = 0;

   DALSYSMemHandle hMem;
   DALSYSMemInfo MemInfo;

   if (NULL == SECURITY_CONTROL_BASE_PTR)
   {
      if (DAL_SUCCESS != qdss_efuse_memmap(SECURITY_CONTROL_BASE_PHYS,
                     SECURITY_CONTROL_BASE_SIZE,
                     &hMem,
                     &MemInfo
                     ))
      {
         return QDSS_TRACE_ACCESS_DENIED;
      }
      if (SECURITY_CONTROL_BASE_SIZE == MemInfo.dwMappedLen)
      {
         SECURITY_CONTROL_BASE_PTR = MemInfo.VirtualAddr;
      }
      else
      {
         return QDSS_TRACE_ACCESS_DENIED;
      }
   }

   status =           !(HWIO_INF(OEM_CONFIG1,DAP_SPNIDEN_DISABLE));
   status = status && !(HWIO_INF(OEM_CONFIG1,DAP_SPIDEN_DISABLE));
   status = status && !(HWIO_INF(OEM_CONFIG1,DAP_NIDEN_DISABLE));
   status = status && !(HWIO_INF(OEM_CONFIG1,DAP_DBGEN_DISABLE));
   status = status && !(HWIO_INF(OEM_CONFIG1,DAP_DEVICEEN_DISABLE));
   status = status && !(HWIO_INF(OEM_CONFIG0,ALL_DEBUG_DISABLE));

   return (status ? QDSS_TRACE_ACCESS_ALLOWED : QDSS_TRACE_ACCESS_DENIED);
}
