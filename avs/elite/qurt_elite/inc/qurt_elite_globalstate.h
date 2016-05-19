/*========================================================================
Copyright (c) 2010, 2013-2014 Qualcomm Technologies, Inc. All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
========================================================================= */
/**
@file qurt_elite_globalstate.h

@brief This file contains the global state structure for the qurt_elite environment.
This state includes system-wide information such as the number
of active threads and malloc counters.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      qurt_elite_mainpage.dox file.
===========================================================================*/
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/inc/qurt_elite_globalstate.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/05/14    sw     (Tech Pubs) Merged Doxygen comments from 2.4; edited
                   Doxygen comments/markup for 2.6.
03/25/13    sw     (Tech Pubs) Edited Doxygen comments/markup for 2.0.
02/04/10    mwc      Created file.
03/09/10    brs      Edited for doxygen-to-latex process.
========================================================================== */

#ifndef QURT_ELITE_GLOBALSTATE_H
#define QURT_ELITE_GLOBALSTATE_H

/*=======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */

#include "qurt_elite_atomic.h"
#include "qurt_elite_thread.h"
#include "qurt_elite_mutex.h"
#include "qurt_elite_queue.h"
#include "qurt_elite_memorymap.h"
#include "qurt_elite_memory.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/** @addtogroup qurt_elite_globalstate
@{ */

/** Number of ASM queues. User session IDs are from 1 to 15.
    Reserved session ID 0 is +1.
*/
#define ASM_NUM_QUEUES (15+1)

/** Maximum length of the thread name, including the NULL terminator.
*/
#define QURT_ELITE_THREAD_NAME_MAX_LENGTH (16)

/* Forward declaration. */
typedef struct qurt_elite_globalstate_t qurt_elite_globalstate_t;

/* Forward declaration. */
typedef struct qurt_elite_thread_list_t qurt_elite_thread_list_t;

/* Forward declaration. */
typedef struct qurt_elite_memorymap_node_t qurt_elite_memorymap_node_t;

/* Forward declaration. */
typedef struct qurt_elite_memorymap_client_t qurt_elite_memorymap_client_t;

/** Valid thread states.
*/
typedef enum {
   QURT_ELITE_THREAD_NONE  =    0,  /**< No thread. */
   QURT_ELITE_THREAD_LAUNCHING  ,   /**< Thread is launching. */
   QURT_ELITE_THREAD_RUNNING    ,   /**< Thread is running. */
   QURT_ELITE_THREAD_EXITING        /**< Thread is exiting. @newpage */
} QURT_ELITE_THREAD_STATES;

/** Node of a thread in the array of threads in the global state structure.
*/
struct qurt_elite_thread_list_t {
   qurt_elite_thread_t     tid;      /**< Thread ID. */
   int                nExitStatus;   /**< Thread exit status. */
   char*              pStack;        /**< Thread stack buffer. */
   int                nStackSize;    /**< Thread stack size. */
   char               name[QURT_ELITE_THREAD_NAME_MAX_LENGTH];
                                     /**< Thread name. */
   int                (*pfStartRoutine)(void *);
                                     /**< Function pointer to the thread entry
                                          function. */
   void               *arg;          /**< Pointer to the thread arguments. */
   int                nThreadState;  /**< Thread state. */
   bool_t             fPreAllocatedStack;
                                     /**< Indicates whether the thread stack
                                          is assigned by the user. */

};

/**	Physical and virtual address information about a memory segment.
 */
typedef struct {
    uint64_t phy_addr;   /**< Starting physical address. */
    uint32_t virt_addr;  /**< Starting virtual address. */
    uint32_t size;       /**< Size in bytes. */
} qurt_elite_mem_seg_t;

/**	Memory usage statistics obtained during a test case run.
*/
typedef struct {
   qurt_elite_mutex_t   lock;
   /**< Mutex lock for this data structure. */

   uint32_t             num_mallocs;
   /**< Total number of mallocs up to the current point in the test. */

   uint32_t             num_frees;
   /**< Total number of times memory is freed up to the current point in the
        test. */

   uint32_t             curr_heap;
   /**< Current heap usage at the current point in the test. */

   uint32_t             peak_heap;
   /**< Peak heap usage up to the current point in the test. */

} qurt_elite_mem_stats_t;

//***************************************************************************
// Global State
//***************************************************************************

/** Global structure used to track resources, such as threads and queues. This
  structure is intended for use in such tasks as debugging and checking for
  leaks.
*/
struct qurt_elite_globalstate_t
{
   qurt_elite_mem_stats_t avs_stats; 
   /**< Heap statistics for AVS threads. */

   qurt_elite_mem_stats_t non_avs_stats;
   /**< Heap statistics for non-AVS threads. */
   
   volatile int32_t        nSimulatedMallocFailCount;
   /**< If the failure count > 0, counts mallocs down to zero and then
        simulates out-of-memory. This is used for testing. */

   qurt_elite_atomic_word_t      nMsgQs;
   /**< Counter of queues to help generate unique names. */

   qurt_elite_atomic_word_t      nMemRegions;
   /**< Counter of the number of memory regions in a system. */

   qurt_elite_mutex_t            mutex;
   /**< Mutex for thread safety of this structure. */

   qurt_elite_mutex_t            lpmMutex;
   /**< Mutex to lock usage of Low Power Memory (LPM). */

   qurt_elite_thread_list_t      aThreadContextBuf[QURT_ELITE_MAX_SW_THREADS];
   /**< Linked list of threads in the system. */

   qurt_elite_memorymap_client_t *pMemoryMapClientList;
   /**< Linked list of memory map clients in the system. */

   volatile uint32_t        bEnableQLogging;
   /**< Logs the commands going into and coming out of queues. */

   volatile uint32_t        uQ6ClockKHz;
   /**< Tracks the Hexagon core clock frequency. */

   volatile uint32_t        uAhbClockKHz;
   /**< Tracks the Hexagon AHB frequency. */

   volatile uint32_t        uSysFabricClockKHz;
   /**< Tracks the system FABRIC frequency. */

   qurt_elite_queue_t            *pAdmStatSvcCmdQ;
   /**< Pointer to the ADM static service command queue. */

   qurt_elite_queue_t *pAfeStatSvcCmdQ;
   /**< Pointer to the AFE static service command queue. */

   qurt_elite_queue_t *pVoiceTimerCmdQ;
   /**< Pointer to the ASM static service session command queues.

        i@sup{th} element @rarrow i@sup{th} session @rarrow
        (i-1)@sup{th} ASM internal session ID */

   qurt_elite_queue_t *pAsmSessionCmdQ[ASM_NUM_QUEUES];   
   /**< Specifies whether all static services are up and ready. */

   volatile uint32_t uSvcUpStatus;
   /**< Specifies whether the aDSP static services are up and ready. */

   uint64_t lpm_virt_addr;
   /**< Base virtual address of the LPM. */
   
   uint32_t lpm_size;
   /**< Size of the LPM in bytes. */
   
   qurt_elite_mem_seg_t lpm_aud_bitstrm_buf;
   /**< LPM bitstream buffer used by the audio decoder service. */

   qurt_elite_mem_seg_t lpm_afe_dma_buf;
   /**< AFE DMA buffers placed in LPM. */

   qurt_elite_mem_seg_t lpm_voice_buf;
   /**< Voice buffer placed in LPM for low power. */

   qurt_elite_mem_seg_t lpm_lpa_heap;
   /**< LPA heap buffer placed in LPM for low power.*/
   
   volatile uint32_t size_lpa_heap_from_ddr;
   /**< LPA heap size. */

    uint32_t *ddr_lpa_heap;
    /**< Address in the heap where LPA dynamic buffers are allocated. */
};


/** Linked list of memory regions.
 */
struct qurt_elite_memorymap_node_t
{

    qurt_mem_pool_t     MemPool;
    /**< Memory pool from which the memory region is created. */

    uint16_t        unNumContPhysReg;
	/**< Number of physical memory regions in this node. */

    int16_t         ref_count;
	/**< Reference count that the client can increment to lock this memory map
         handle.

         Unmapping can only be performed if ref_count reaches zero.

         The client must decrement ref_count when it does not use this memory
         map handle. */

    uint32_t        mapping_mode;
	/**< Specifies whether the mapping is physical or virtual, or if it is a
         physical offset. */

    qurt_elite_memorymap_node_t *pNext;
	/**< Pointer to the next node in the linked list.

         @tblsubhd{If unNumContPhysReg is greater than 1}
         In addition to the number of qurt_elite_memorymap_region_record_t
         structures following this structure, one more ContPhysReg follows to
         represent the master region for all ContPhysRegs (called the <i>
         virtual memory region</i> in QuRT).

         When freeing the regions, all of the following space is also freed. */
};


/** Maintains a linked list of clients registered with qurt_elite_memorymap.
 */
struct qurt_elite_memorymap_client_t
{

    qurt_elite_memorymap_node_t   *pMemMapListNode;
    /**< List of memory map nodes for this client.*/

    qurt_elite_mutex_t             mClientMutex;
    /**< Mutex to access the list. */

    qurt_elite_memorymap_client_t *pNext;
    /**< Next entry in the client list. */

};


/** Instance of the global state structure. */
extern qurt_elite_globalstate_t qurt_elite_globalstate;

/**
  Initializes the global state structure. This function must be
  called once at bootup.

  @return
  None.

  @dependencies
  None.
*/
void qurt_elite_globalstate_init(void);

/**
  Deinitializes the global state structure. This function must be
  called before exiting to do a final cleanup.

  @return
  None.

  @dependencies
  The object must have been created and initialized before calling this
  function.
*/
void qurt_elite_globalstate_deinit(void);

/** 
  Initializes LPM. This function must be called before using LPM.

  @return
  ADSP_EOK -- Initialization is successful. \n
  ADSP_EFAILED -- Otherwise.
  @par
  For more information, refer to @xhyperref{Q2,[Q2]}.

  @dependencies
  None.
*/ /* Q2 = Hex Multimedia: Elite API Interface Spec for 2.4 (80-NF770-13) */
ADSPResult lpm_init(void);

/**
  Deinitializes LPM. 

  @return
  None.

  @dependencies
  Must be called after all usage of LPM ends.
*/
void lpm_deinit(void);

/** @} */ /* end_addtogroup qurt_elite_globalstate */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef QURT_ELITE_GLOBALSTATE_H

