/*============================================================================
  @file sns_umemmgr.c

  @brief
  Implements SNS memory manager interfaces expected to run in uImage mode.
 
  The symbols in this file should be places in the uImage section.

  <br><br>


  Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
  ============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. Please
  use ISO format for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/common/util/memmgr/src/sns_u_memmgr.c#1 $
  $DateTime: 2014/12/01 08:57:58 $

  when       who    what, where, why 
  ---------- --- -----------------------------------------------------------
  2014-10-27  hw  Divide BigImage heap to two parts: default heap and memheap. Each
                  will have size of 512K. Also add lowmem callback function support
  2013-08-15  asj Handle uHeap exhaustion failure by allocating memory from
                  DDR heap and restricting uImage entry.
  2013-06-30  asj Initial release

  ============================================================================*/
/*=====================================================================
  INCLUDES
=======================================================================*/
#ifdef SNS_USES_ISLAND

#include "sns_memheap_lite.h"
#include "sns_memmgr.h"
#include "sns_uimg_utils.h"


/*============================================================================
  Global Data Definitions
  ===========================================================================*/

/* Sensors uImage heap. All uImage dynamic allocations are done from here */
uint8 sns_uheap_mem[SNS_UIMAGE_HEAP_SIZE];

/* Data structures used to maintain the heap */
sns_mem_heap_type sns_uheap;
mem_magic_number_struct sns_uheap_magic;

uint32 sns_uheap_magic_num[SNS_MAX_HEAP_INIT] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                             0xFFFFFFFF, 0xFFFFFFFF};
uint16 sns_uheap_magic_num_idx_array[SNS_MAX_HEAP_INIT] = {0,1,2,3,4};
uint16_t sns_uheap_magic_num_index = 0;

/*=========================================================================
  FUNCTION:  sns_memgr_int_u_free
  =======================================================================*/
int sns_memmgr_int_u_free(void *ptr)
{
  if (SNS_OS_IS_UHEAP_PTR(ptr))
  {
    return(sns_mem_free(&sns_uheap, &sns_uheap_magic, ptr));
  }
  else
  {
    return(-1);
  }
}

/*=========================================================================
  FUNCTION:  sns_memgr_int_u_malloc
  =======================================================================*/
void *sns_memmgr_int_u_malloc(uint8_t module, uint32_t size)
{
  void *buffer = NULL;
  buffer = sns_mem_malloc(&sns_uheap, &sns_uheap_magic, size);
  if (buffer != NULL)
     SNS_OS_MEMSET(buffer, 0, size);
  return buffer;
}

/*=========================================================================
  FUNCTION:  sns_memgr_int_any_free
  =======================================================================*/
void sns_memmgr_int_any_free(void *ptr)
{
  if (SNS_OS_IS_UHEAP_PTR(ptr))
  {
    sns_memmgr_int_u_free(ptr);
  }
  else
  {
    sns_memmgr_free_spillover_buffer(ptr);
  }
}

/*=========================================================================
  FUNCTION:  sns_memgr_int_any_free_sam
  =======================================================================*/
void sns_memmgr_sensor_heap_int_any_free(void *ptr)
{
  if (SNS_OS_IS_UHEAP_PTR(ptr))
  {
    sns_memmgr_int_u_free(ptr);
  }
  else
  {
    sns_memmgr_free_sensor_heap_spillover_buffer(ptr);
  }
}

/*=========================================================================
  FUNCTION:  sns_memgr_int_any_malloc
  =======================================================================*/
void * sns_memmgr_int_any_malloc(uint8_t module, uint32_t size)
{
  void *buffer = NULL;
  uint32_t i;
  buffer = sns_memmgr_int_u_malloc(module, size);

  if (NULL == buffer)
  {
	sns_utils_place_uimge_hold(SNS_UIMG_MEMGR);

    /* check if curre_heap usage is beyond the low memory threshold. If it is, call callback function
     * to address the state before really running out of memory */
	if(qurt_elite_globalstate.avs_stats.curr_heap > SNS_DEFAULT_HEAP_LOW_MEM_THRESH)
    {
      UMSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO, "int_any_malloc calling callback function - heap size %d, peak heap %d, callback func num %d",
             qurt_elite_globalstate.avs_stats.curr_heap,
             qurt_elite_globalstate.avs_stats.peak_heap,
             sns_default_heap_lowmem_cb.num_clients);
      for( i = 0; i < sns_default_heap_lowmem_cb.num_clients; i++ )
      {
        if(NULL != sns_default_heap_lowmem_cb.cb_func[i])
        {
          UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO,
                 "default heap int_any_malloc calling callback function i=%d", i );
          (*sns_default_heap_lowmem_cb.cb_func[i])();
        }
      }
    }

    buffer = qurt_elite_memory_malloc(size, sns_heap_id);
      sns_memmgr_add_to_spillover_list(buffer);
  }

  if (buffer != NULL)
  {
     SNS_OS_MEMSET(buffer, 0, size);
  }
  else
  {
  	UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO, "malloc failed - size %d",size);
  }

  return buffer;
}

#endif /* SNS_USES_ISLAND */
