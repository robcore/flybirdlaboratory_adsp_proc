/*========================================================================

*//** @file qurt_elite_globalstate.cpp
This file contains the global state structure for the qurt_elite environment.
This state includes system-wide information such as number of active
threads, malloc counters, etc..

Copyright (c) 2010 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/src/qurt_elite_globalstate.cpp#4 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
02/04/10   mwc     Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_elite.h"

#include "lpm_prop.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include "DALPropDef.h"
#include "DDIChipInfo.h"

/*--------------------------------------------------------------*/
/* Macro definitions                                            */
/* -------------------------------------------------------------*/

/* -----------------------------------------------------------------------
** Constant / Define Declarations
** ----------------------------------------------------------------------- */

/* =======================================================================
**                          Function Definitions
** ======================================================================= */

//***************************************************************************
// Global state structure for resource monitoring & debugging
//***************************************************************************
qurt_elite_globalstate_t qurt_elite_globalstate;

/* Static variable declarations */
static qurt_mem_region_t lpm_reg;

void qurt_elite_globalstate_init(void)
{
   qurt_elite_memory_stats_init();

   // set all fields to 0.
   qurt_elite_globalstate.nSimulatedMallocFailCount = -1;
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMsgQs, 0);
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMemRegions, 0);
   qurt_elite_globalstate.pMemoryMapClientList = NULL;
   qurt_elite_mutex_init(&qurt_elite_globalstate.mutex);
   qurt_elite_mutex_init(&qurt_elite_globalstate.lpmMutex);

   // by default, do not log queues.
   qurt_elite_globalstate.bEnableQLogging = 0;

   // clear the frequency measurements
   qurt_elite_globalstate.uQ6ClockKHz = 0;
   qurt_elite_globalstate.uAhbClockKHz = 0;
   qurt_elite_globalstate.uSysFabricClockKHz = 0;

   // Initialise the static svc cmd Q with NULL
   qurt_elite_globalstate.pAdmStatSvcCmdQ = NULL;
   qurt_elite_globalstate.pAfeStatSvcCmdQ = NULL;
   qurt_elite_globalstate.pVoiceTimerCmdQ = NULL;
   for (uint32_t i=0; i < ASM_NUM_QUEUES; i++)
   {
      qurt_elite_globalstate.pAsmSessionCmdQ[i] = NULL;   
   }
   qurt_elite_globalstate.uSvcUpStatus = 0;

   qurt_elite_globalstate.ddr_lpa_heap =  NULL;

   //clear the thread context structures
   qurt_elite_thread_list_init();

   // initialize qurt_elite heap manager heap table entries
   qurt_elite_heap_table_init();
}

void qurt_elite_globalstate_deinit(void)
{
   // clean up all resources.

   qurt_elite_mutex_lock(&qurt_elite_globalstate.mutex);

   qurt_elite_memorymap_client_t *pClientNode = qurt_elite_globalstate.pMemoryMapClientList;
   qurt_elite_memorymap_node_t *pMemoryMapNode;

   //loop through all clients
   while (pClientNode) {
      qurt_elite_globalstate.pMemoryMapClientList = pClientNode->pNext;

      //loop through all memory regions of a client
      qurt_elite_mutex_lock(&(pClientNode->mClientMutex));
      pMemoryMapNode = pClientNode->pMemMapListNode;
      while (pMemoryMapNode) {
         pClientNode->pMemMapListNode = pMemoryMapNode->pNext;
         qurt_elite_memory_aligned_free(pMemoryMapNode);
         pMemoryMapNode = pClientNode->pMemMapListNode;
      }
      qurt_elite_mutex_unlock(&(pClientNode->mClientMutex));

      qurt_elite_memory_free(pClientNode);
      pClientNode = qurt_elite_globalstate.pMemoryMapClientList;
   }
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMemRegions, 0);
   qurt_elite_mutex_unlock(&qurt_elite_globalstate.mutex);
   qurt_elite_mutex_destroy(&qurt_elite_globalstate.mutex);

   qurt_elite_memory_stats_deinit();


}

ADSPResult lpm_init(void)
{
   DALSYSPropertyVar prop_value;
   DALSYS_PROPERTY_HANDLE_DECLARE(handle);
   const lpm_prop_struct_t *lpm_prop_ptr = NULL;
   const char *dev_id="LPM";
  
   /* Get handle to the device */
   if(DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(dev_id, handle))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "DALSYS_GetDALPropertyHandleStr failed, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   if(DAL_SUCCESS != DALSYS_GetPropertyValue(handle,"LPMPropStructPtr", 0, &prop_value))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "DALSYS_GetPropertyValue failed, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   lpm_prop_ptr = (const lpm_prop_struct_t*)(prop_value.Val.pStruct);

   uint32_t phy_addr_lsw = (uint32_t) (lpm_prop_ptr->base_phy_addr & 0xffffffff);
   uint32_t phy_addr_msw = (uint32_t) ((lpm_prop_ptr->base_phy_addr >> 32) & 0xffffffff) ;
   MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM base physical address MSW = 0x%lx, LSW = 0x%lx. Size = %lu", 
         phy_addr_msw, phy_addr_lsw, lpm_prop_ptr->size);

   //check the size
   if (0 == lpm_prop_ptr->size || 0 == lpm_prop_ptr->base_phy_addr)
   {
       //LPM not present, nothing to do
       return ADSP_EOK;
   }

   //Query the LPM memory pool. This needs to go away once
   //we define a generic LPASS driver pool
   qurt_mem_pool_t pool = 0;
   
   char pool_name[]="ADSP_DRIVER_POOL";
   int res = qurt_mem_pool_attach(pool_name, &pool);

   if (QURT_EOK != res)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to attach to memory pool, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   //initialize region attributes
   qurt_mem_region_attr_t reg_attr;
   qurt_mem_region_attr_init(&reg_attr);

   qurt_mem_region_attr_set_cache_mode(&reg_attr, QURT_MEM_CACHE_WRITEBACK_NONL2CACHEABLE);
   qurt_mem_region_attr_set_mapping(&reg_attr, QURT_MEM_MAPPING_PHYS_CONTIGUOUS);
   qurt_mem_region_attr_set_physaddr(&reg_attr, (qurt_addr_t) phy_addr_lsw);
   qurt_mem_region_attr_set_type(&reg_attr, QURT_MEM_REGION_LOCAL);
   
   //create the region
   res = qurt_mem_region_create(&lpm_reg, lpm_prop_ptr->size, pool, &reg_attr);

   if (QURT_EOK != res)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to create memory region, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   //get updated attributes
   res = qurt_mem_region_attr_get(lpm_reg, &reg_attr);

   if (QURT_EOK != res)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to get memory region attributes, LPM cannot be used!");
      lpm_deinit();
      return ADSP_EFAILED;
   }

   uint32_t virt_addr = 0;
   qurt_mem_region_attr_get_virtaddr(&reg_attr, (unsigned int *) (&virt_addr));

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM virtual address = 0x%lx", virt_addr);

   //fill up the buffer details
   qurt_elite_globalstate_t *glob_state = &qurt_elite_globalstate;
   uint64_t phy_addr = lpm_prop_ptr->base_phy_addr;

   //store base addr and size in global state
   glob_state->lpm_virt_addr = virt_addr;
   glob_state->lpm_size = lpm_prop_ptr->size;
   
   //Create the LPA heap from DDR
   glob_state->size_lpa_heap_from_ddr = lpm_prop_ptr->size_lpa_heap_from_ddr;
   if(0 != glob_state->size_lpa_heap_from_ddr)
   {
      /* 4KB address alignment so that it can be placed in OCMEM */ 
      glob_state->ddr_lpa_heap = (uint32_t*)qurt_elite_memory_aligned_malloc(glob_state->size_lpa_heap_from_ddr, 4096, QURT_ELITE_HEAP_DEFAULT);
      if(NULL == glob_state->ddr_lpa_heap)
      {
	     MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO," Failure in mallocing the LPA stream heap from DDR!! Exiting..");
	     lpm_deinit();
	     return ADSP_EFAILED;
      }
   }   
   
   if (lpm_prop_ptr->size_audio_bitstrm_buf != 0)
   {
       glob_state->lpm_aud_bitstrm_buf.phy_addr = phy_addr;
       glob_state->lpm_aud_bitstrm_buf.virt_addr = virt_addr;
       glob_state->lpm_aud_bitstrm_buf.size = lpm_prop_ptr->size_audio_bitstrm_buf;

       phy_addr += lpm_prop_ptr->size_audio_bitstrm_buf;
       virt_addr += lpm_prop_ptr->size_audio_bitstrm_buf;
   }

   if (lpm_prop_ptr->size_afe_dma_buf != 0)
   {
       glob_state->lpm_afe_dma_buf.phy_addr = phy_addr;
       glob_state->lpm_afe_dma_buf.virt_addr = virt_addr;
       glob_state->lpm_afe_dma_buf.size = lpm_prop_ptr->size_afe_dma_buf;

       phy_addr += lpm_prop_ptr->size_afe_dma_buf;
       virt_addr += lpm_prop_ptr->size_afe_dma_buf;
   }

   if (lpm_prop_ptr->size_voice_buf != 0)
   {
       glob_state->lpm_voice_buf.phy_addr = phy_addr;
       glob_state->lpm_voice_buf.virt_addr = virt_addr;
       glob_state->lpm_voice_buf.size = lpm_prop_ptr->size_voice_buf;

       phy_addr += lpm_prop_ptr->size_voice_buf;
       virt_addr += lpm_prop_ptr->size_voice_buf;
   }

   if (lpm_prop_ptr->size_lpa_heap_from_lpm != 0)
   {
       glob_state->lpm_lpa_heap.phy_addr = phy_addr;
       glob_state->lpm_lpa_heap.virt_addr = virt_addr;
       glob_state->lpm_lpa_heap.size = lpm_prop_ptr->size_lpa_heap_from_lpm;

       phy_addr += lpm_prop_ptr->size_lpa_heap_from_lpm;
       virt_addr += lpm_prop_ptr->size_lpa_heap_from_lpm;
   }
   
   return ADSP_EOK;
}

void lpm_deinit(void)
{
    if (0 != lpm_reg)
    {
        qurt_mem_region_delete(lpm_reg);
        lpm_reg = 0;
    }
    if(NULL != qurt_elite_globalstate.ddr_lpa_heap)
	{
		qurt_elite_memory_aligned_free(qurt_elite_globalstate.ddr_lpa_heap);
		qurt_elite_globalstate.ddr_lpa_heap = NULL;
	}
}
