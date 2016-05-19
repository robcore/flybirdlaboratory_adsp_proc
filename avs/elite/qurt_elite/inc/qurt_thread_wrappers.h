/*========================================================================
Copyright (c) 2011, 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
====================================================================== */
/**
@file qurt_thread_wrappers.h

This file contains wrapper functions for QuRT thread APIs
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      qurt_elite_mainpage.dox file.
===========================================================================*/
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/inc/qurt_thread_wrappers.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/08/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4.
03/25/13   sw      (Tech Pubs) Edited Doxygen comments/markup for 2.0.
11/14/11   rkc      Created file.
========================================================================== */

#ifndef __QURT_THREAD_WRAPPERS_H__
#define __QURT_THREAD_WRAPPERS_H__

#include "qurt_elite.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/** @addtogroup qurt_elite_thread_wrappers
@{ */

/**
  Real (unwrapped) qurt_thread_create function.

  @param [out] tid         Pointer to the thread ID.
  @param [in] attr         Pointer to the thread attributes.
  @param [in] entry_func   Pointer to the entry functions for the thread.
  @param [in] arg          Pointer to the arguments to pass to the entry
                           function.

  @return
  None.

  @dependencies
  None. @newpage
*/
int __real_qurt_thread_create (qurt_thread_t *tid, 
                                    qurt_thread_attr_t *attr, 
                                    void (*entry_func) (void *), 
                                    void *arg);

/**
  Real (unwrapped) qurt_thread_stop function.

  @return
  None.

  @dependencies
  None.
*/
void __real_qurt_thread_stop(void);

/**
  Real (unwrapped) qurt_thread_resume function.

  @param[in] tid   Thread ID.

  @return
  None.

  @dependencies
  None. @newpage
*/
int __real_qurt_thread_resume(unsigned int tid);

/**
  Real (unwrapped) qurt_thread_exit function.

  @param[in] status   User-defined thread exit status value. 

  @return
  None.

  @dependencies
  None.
*/
void __real_qurt_thread_exit(int status);

/**
  Real (unwrapped) qurt_thread_join function.

  @param[in]  tid     Thread identifier.
  @param[out] status  Pointer to the destination variable for the thread exit
                      status. This returns an application-defined value
                      indicating the termination status of the specified
                      thread. 

  @return
  None.

  @dependencies
  None. @newpage
*/
int __real_qurt_thread_join(unsigned int tid, int *status); 

/** Stores the statistics of a software thread.
*/
typedef struct {
   qurt_thread_t     tid;           /**< Thread ID. */
   char               name[QURT_THREAD_ATTR_NAME_MAXLEN]; /**< Thread name. */
   void               (*entry_func)(void *); /**< Function pointer to the
                                                  thread entry function. */
   void               *arg;         /**< Pointer to the thread arguments. */
   int                thread_state; /**< Thread state. */
   unsigned int       stack_size;   /**< Size in bytes of the thread stack. */

} thread_stats_t;

/** List of software thread statistics.
*/
typedef struct
{
   thread_stats_t stats_list[QURT_ELITE_MAX_SW_THREADS]; /**< List of thread
                                                              statistics. */
   qurt_elite_mutex_t lock; /**< Mutex to protect access to the list. */

} thread_stats_list_t;

/** List of non-Elite thread statistics. */
extern thread_stats_list_t thread_wrap_stats_list;

/**
  Resets thread Pcycles in a given list.

  @datatypes
  thread_stats_list_t

  @param[in] stats   Pointer to the list of thread statistics.

  @return
  None.

  @dependencies
  None.
*/
void thread_wrap_reset_pcycles(thread_stats_list_t *stats);

/** @} */ /* end_addtogroup qurt_elite_thread_wrappers */

#ifdef __cplusplus
}
#endif //__cplusplus
       
#endif //__QURT_THREAD_WRAPPERS_H__
