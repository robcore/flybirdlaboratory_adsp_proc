/*========================================================================
Copyright (c) 2010-2011, 2013-2014 Qualcomm Technologies, Inc. All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
========================================================================== */
/**
@file qurt_elite_thread.h

@brief This file contains utilities for threads. Threads must be joined to
avoid memory leaks. This file provides functions to create and destroy threads,
and to change thread priorities.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      qurt_elite_mainpage.dox file.
===========================================================================*/
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/inc/qurt_elite_thread.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/08/14    sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                     Doxygen comments/markup for 2.6.
03/25/13    sw      (Tech Pubs) Edited Doxygen comments/markup for 2.0.
05/03/11    leo     (Tech Pubs) Edited doxygen comments and markup.
03/08/10    brs      Edited for doxygen-to-latex process.
02/04/10    mwc      Created file.
========================================================================== */

#ifndef QURT_ELITE_THREAD_H
#define QURT_ELITE_THREAD_H

#include "qurt_elite_memory.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */

/** @addtogroup qurt_elite_thread
@{ */

/* -----------------------------------------------------------------------
** Global definitions/forward declarations
** ----------------------------------------------------------------------- */

/** @name Maximum number of hardware and software threads available on the platform
@{ */

//Support Q6v3 (variable HW threads) & Q6v4, Q6v5 (3 HW threads) & Q6v55, Q6v56 (4 HW threads). 
//For others issue error until supported.
//TBD: Hard-coding because 8994 build is still using v5 but need to use v55.
//Need to be modified once build migrates to v55.

/** Maximum number of hardware threads. */
#define QURT_ELITE_MAX_HW_THREADS       4 

/** Maximum number of software threads. */
#define QURT_ELITE_MAX_SW_THREADS       MAX_THREADS

/** Generic thread mask. */
#define QURT_ELITE_GENERIC_THREAD_MASK  0xFF

/** @} */ /* end_namegroup Maximum Number of Hardware and Software Threads */

/** @name Thread stack fill pattern and spacing
@{ */

/** Stack fill word. */
#define QURT_ELITE_STACK_FILL_WORD             0xF8F8F8F8L

/** Stack fill spacing. */
#define QURT_ELITE_STACK_FILL_SPACING          16

/** @} */ /* end_namegroup Thread Stack Fill Pattern and Spacing */

/** Handle to a thread. */
typedef int qurt_elite_thread_t;

/**	Valid low power optimization feature flags. */
typedef enum
{
   QURT_ELITE_LP_TCB_OPT=1,  /**< Thread context buffer optimization. @newpage */
}  QURT_ELITE_LP_OPT_FLAGS;


/****************************************************************************
** Threads
*****************************************************************************/

/**
  Creates and launches a thread.

  @datatypes
  #qurt_elite_thread_t \n
  #QURT_ELITE_HEAP_ID

  @param[out] pTid           Pointer to the thread ID.
  @param[in]  pzThreadName   Pointer to the thread name.
  @param[in]  pStack         Pointer to the location of the preallocated stack
                             (NULL causes a new allocation). \n
                             pStack must point to the lowest address in the
                             stack.
  @param[in]  nStackSize     Size of the thread stack.
  @param[in]  nPriority      Thread priority, where 0 is the lowest and 255 is
                             the highest.
  @param[in]  pfStartRoutine Pointer to the entry function of the thread.
  @param[in]  arg            Pointer to the arguments passed to the entry
                             function. An argument can be to any pointer type.
  @param[in]  heap_id        ID of the heap to which the thread stack is
                             allocated.

  @detdesc
  The thread stack can be passed in as the pStack argument, or pStack=NULL
  indicates that QuRT_Elite allocates the stack internally. If the caller
  provides the stack, the caller is responsible for freeing the stack memory
  after joining the thread.
  @par
  Preallocated stacks must be freed after the dying thread is joined. The
  caller must specify the heap in which the thread stack is to be allocated.

  @return
  An indication of success (0) or failure (nonzero).

  @dependencies
  None. @newpage
*/
ADSPResult qurt_elite_thread_launch(qurt_elite_thread_t *pTid, char *pzThreadName, char* pStack,
   size_t nStackSize, int nPriority, int (*pfStartRoutine)(void *), void* arg, QURT_ELITE_HEAP_ID heap_id);

/**
  Creates and launches a thread for Low Power Audio (LPA). 

  @datatypes
  #qurt_elite_thread_t \n
  #QURT_ELITE_HEAP_ID

  @param[out] pTid           Thread ID.
  @param[in]  pzThreadName   Thread name.
  @param[in]  pStack         Location of a preallocated stack (NULL causes a
                             new allocation). \n
                             pStack must point to the lowest address in the
                             stack.
  @param[in]  nStackSize     Size (in bytes) of the thread stack.
  @param[in]  nPriority      Thread priority, where 0 is the lowest and 255 is
                             the highest.
  @param[in]  pfStartRoutine Entry function of the thread.
  @param[in]  arg            Passed to the entry function and can be a case to
                             any pointer type.
  @param[in]  heap_id        Specifies the thread stack allocated in the heap.
                             If the specified heap is full, the thread stack
                             is allocated in the default heap.  
  @param[in]  lp_opt_flags   Flags that indicate the power optimization
                             features. Each bit represents different
                             optimization.
                             - Bit 0 = 1 -- Thread TCB must be created in the
                               small TCB buffer. 
                             - Bit 0 = 0 -- Thread TCB must be created in the
                               normal TCB buffer.
                             - Bits 1 to 31 -- Reserved. @tablebulletend

  @detdesc
  All services can use this function by passing #QURT_ELITE_HEAP_DEFAULT as
  the heap_id if no specific heap ID is required.
  @par
  The TCB is allocated in the small TCB buffer (which can be OCMEM or LPI). If
  the small TCB buffer is full, the thread context buffer (TCB) is allocated
  in the normal TCB buffer.

  @return
  An indication of success (0) or failure (nonzero).

  @dependencies
   None.
*/
ADSPResult qurt_elite_thread_launch_lowpower(qurt_elite_thread_t *pTid, char *pzThreadName, char* pStack,
   size_t nStackSize, int nPriority, int (*pfStartRoutine)(void *), void* arg, QURT_ELITE_HEAP_ID heap_id,
   uint32_t lp_opt_flags);   
   
/**
  Waits for a specified thread to exit and collects its exit status.

  @datatypes
  #qurt_elite_thread_t

  @param[in]  nTid     Thread ID to wait on.
  @param[out] nStatus  Pointer to the value returned by pfStartRoutine
                       called in qurt_elite_thread_launch().

  @return
  None.

  @dependencies
  The object must have been created and initialized before calling this
  function.
*/
void qurt_elite_thread_join(qurt_elite_thread_t nTid, int* nStatus);

/**
  Intializes the thread context structure.

  @return
  None.

  @dependencies
  None.
*/
void qurt_elite_thread_list_init(void);

/**
  Queries the caller's thread priority.

  @return
  The caller's thread priority, where 255 is the highest and 0 is the lowest.

  @dependencies
  The object must have been created and initialized before calling this
  function. @newpage
*/
static inline int qurt_elite_thread_prio_get(void)
{
   return 255 - qurt_thread_get_priority(qurt_thread_get_id());
}

/**
  Changes the caller's thread priority.

  @param[in] nPrio  New priority, where 255 is the highest and 0 is the lowest.

  @return
  None.

  @dependencies
  The object must have been created and initialized before calling this
  function.
*/
static inline void qurt_elite_thread_set_prio(int nPrio)
{
   (void) qurt_thread_set_priority(qurt_thread_get_id(), 255 - nPrio);
}

/** @} */ /* end_addtogroup qurt_elite_thread */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef QURT_ELITE_THREAD_H

