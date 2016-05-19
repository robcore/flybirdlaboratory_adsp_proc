/*========================================================================
qurt_thread_wrappers.cpp

This file contains wrapper functions for QuRT thread APIs

Copyright (c) 2011 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/src/qurt_thread_wrappers.cpp#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
11/14/11   rkc      Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_thread_wrappers.h"

extern "C" {

/* Static function declarations */
static void thread_wrap_init_stats(thread_stats_list_t *stats);
static void thread_wrap_stub(void *arg);

/* Static and global variable definitions */
static uint32_t thread_stats_init = 0;
thread_stats_list_t thread_wrap_stats_list;

/*
 *Function Name:__wrap_qurt_thread_create
 *
 *Parameters: qurt_thread_t *tid: ID of the thread if created 
 *            qurt_thread_attr_t *attr: thread creation attributes
 *            void (*entry_func) (void *): thread entry function
 *            void *arg: arguments to the thread entry function
 *
 *Description: Wrapper for qurt_thread_create function 
 *             to maintain the list of all SW threads and their
 *             states.
 *
 *Returns: QURT_EOK if thread is created successfully 
 *         QURT_EFAILED if thread creation fails. 
 *
 */

int __wrap_qurt_thread_create (qurt_thread_t *tid, 
                              qurt_thread_attr_t *attr, 
                              void (*entry_func) (void *), 
                              void *arg)
{
   if(!thread_stats_init)
   {
      thread_wrap_init_stats(&thread_wrap_stats_list);
      thread_stats_init = 1;
   }

   thread_stats_list_t *stats = &thread_wrap_stats_list;
   uint32_t num_list_elem = sizeof(stats->stats_list) / sizeof(stats->stats_list[0]);

   // scan all the structures to find which one is free
   qurt_elite_mutex_lock(&stats->lock);

   thread_stats_t *thread_info_ptr = NULL;
   for (uint32_t count=0; count < num_list_elem; count++)
   {
      if(QURT_ELITE_THREAD_NONE == stats->stats_list[count].thread_state)
      {
         thread_info_ptr = &stats->stats_list[count];
         thread_info_ptr->thread_state = QURT_ELITE_THREAD_LAUNCHING;
         break;
      }
   }

   qurt_elite_mutex_unlock(&stats->lock);

   if(NULL == thread_info_ptr)
   {
      return QURT_EFAILED;
   }

   qurt_elite_strl_cpy((char_t *)(thread_info_ptr->name), 
                       (char_t *)(attr->name), 
                       QURT_THREAD_ATTR_NAME_MAXLEN);
   thread_info_ptr->entry_func = entry_func;
   thread_info_ptr->arg = arg;
   thread_info_ptr->stack_size = attr->stack_size;
   
   int ret_val = __real_qurt_thread_create(tid, 
                                           attr, 
                                           thread_wrap_stub, 
                                           (void*)thread_info_ptr);

   if(QURT_EOK != ret_val)
   {
      qurt_elite_mutex_lock(&stats->lock);
      //0 will set thread state to QURT_ELITE_THREAD_NONE
      memset(thread_info_ptr, 0, sizeof(*thread_info_ptr)); 
      qurt_elite_mutex_unlock(&stats->lock);
   }

   return ret_val;
}

/*
 *Function Name:__wrap_qurt_thread_exit
 *
 *Parameters: int status: status of the exiting thread
 *
 *Description: Wrapper for qurt_thread_exit function 
 *             to maintain the list of all SW threads and their
 *             states.
 *
 *Returns: None.
 *
 */

void __wrap_qurt_thread_exit(int status)
{
   thread_stats_list_t *stats = &thread_wrap_stats_list;
   uint32_t num_list_elem = sizeof(stats->stats_list) / sizeof(stats->stats_list[0]);

   qurt_thread_t tid = qurt_thread_get_id();

   qurt_elite_mutex_lock(&stats->lock);

   for (uint32_t count=0; count < num_list_elem; count++)
   {
      if(tid == stats->stats_list[count].tid)
      {
         stats->stats_list[count].thread_state = QURT_ELITE_THREAD_EXITING;
         break;
      }
   }

   qurt_elite_mutex_unlock(&stats->lock);

   __real_qurt_thread_exit(status);
}

/*
 *Function Name:__wrap_qurt_thread_join
 *
 *Parameters: unsigned int tid: ID of the thread to be joined.
 *
 *Description: Wrapper for qurt_thread_join function 
 *             to maintain the list of all SW threads and their
 *             states.
 *
 *Returns: QURT_EOK: if thread is successfully joined 
 *         QURT_ENO_THREAD: if thread has already exited. 
 *
 */

int __wrap_qurt_thread_join(unsigned int tid, int *status)
{
   int ret_val = __real_qurt_thread_join(tid, status);

   thread_stats_list_t *stats = &thread_wrap_stats_list;
   uint32_t num_list_elem = sizeof(stats->stats_list) / sizeof(stats->stats_list[0]);

   qurt_elite_mutex_lock(&stats->lock);

   for (uint32_t count=0; count < num_list_elem; count++)
   {
      if((tid == stats->stats_list[count].tid) && 
         (QURT_ELITE_THREAD_EXITING == stats->stats_list[count].thread_state))
      {
         memset(&stats->stats_list[count], 0, sizeof(stats->stats_list[count]));
         break;
      }
   }

   qurt_elite_mutex_unlock(&stats->lock);

   return ret_val;
}

/*
 *Function Name:__wrap_qurt_thread_stop
 *
 *Parameters: None
 *
 *Description: Wrapper for qurt_thread_stop function 
 *             to maintain the list of all SW threads and their
 *             states.
 *
 *Returns: None
 *
 */

void __wrap_qurt_thread_stop(void)
{
   // it looks like qurt_thread_stop internally calls 
   // qurt_thread_exit with 0. 
   __wrap_qurt_thread_exit(0);
}

/*
 *Function Name:__wrap_qurt_thread_resume
 *
 *Parameters: unsigned int tid: ID of the thread to resume.
 *
 *Description: Wrapper for qurt_thread_resume function 
 *             to maintain the list of all SW threads and their
 *             states.
 *
 *Returns: QURT_EOK: if thread is successfully resumed 
 *         QURT_EFATAL: resume operation failed. 
 *
 */

int __wrap_qurt_thread_resume(unsigned int tid)
{
   // currently resume can only be called by the kernel;
   // for now, not doing anything special here.
   return __real_qurt_thread_resume(tid);
}

/*
 *Function Name:thread_wrap_reset_pcycles
 *
 *Parameters: thread_stats_list_t *stats: list of thread statistics
 *
 *Description: Resets the pcycles for each of the running threads 
 *             in the given list.
 *
 *Returns: None
 *
 */

void thread_wrap_reset_pcycles(thread_stats_list_t *stats)
{
   uint32_t num_list_elem = sizeof(stats->stats_list) / sizeof(stats->stats_list[0]);

   /* reset PCycle counters for each running SW thread */
   qurt_elite_mutex_lock(&stats->lock);

   for (uint32_t index=0; index < num_list_elem; index++)
   {
      if( QURT_ELITE_THREAD_RUNNING == stats->stats_list[index].thread_state )
      {
         qurt_profile_reset_threadid_pcycles (stats->stats_list[index].tid);
      }
   }

   // release the mutex.
   qurt_elite_mutex_unlock(&stats->lock);
}

/*
 *Function Name:thread_wrap_stub
 *
 *Parameters: void *arg: arguments to the actual thread entry function.
 *
 *Description: Stub entry function that calls the real entry function 
 *             and also maintains the thread state before and after
 *             the entry function is called.
 *
 *Returns: None
 *
 */

static void thread_wrap_stub(void *arg)
{
   thread_stats_t *thread_info_ptr = (thread_stats_t *) arg;
   thread_stats_list_t *stats = &thread_wrap_stats_list;
   
   qurt_elite_mutex_lock(&stats->lock);

   // record tid for thread joiner to lookup.
   thread_info_ptr->tid = qurt_thread_get_id();
   // set thread state to running before calling entry function
   thread_info_ptr->thread_state = QURT_ELITE_THREAD_RUNNING;

   qurt_elite_mutex_unlock(&stats->lock);

   thread_info_ptr->entry_func(thread_info_ptr->arg);
   
   qurt_elite_mutex_lock(&stats->lock);

   // update thread state to exiting before exit thread 
   thread_info_ptr->thread_state = QURT_ELITE_THREAD_EXITING;
   
   qurt_elite_mutex_unlock(&stats->lock);

   __real_qurt_thread_exit(QURT_EOK);
}

/*
 *Function Name:thread_wrap_init_stats
 *
 *Parameters: thread_stats_list_t *stats: list of thread statistics
 *
 *Description: Initializes the thread statistics list.
 *
 *Returns: None.
 *
 */

static void thread_wrap_init_stats(thread_stats_list_t *stats)
{
   qurt_elite_mutex_init(&stats->lock);
   memset(stats->stats_list, 0, sizeof(stats->stats_list));
}

#ifndef THREAD_WRAP

int __real_qurt_thread_create (qurt_thread_t *tid, 
                                    qurt_thread_attr_t *attr, 
                                    void (*entry_func) (void *), 
                                    void *arg)
{
   return qurt_thread_create(tid, attr, entry_func, arg);
}

void __real_qurt_thread_stop(void)
{
   qurt_thread_stop();
}

int __real_qurt_thread_resume(unsigned int tid)
{
   return qurt_thread_resume(tid);
}

void __real_qurt_thread_exit(int status)
{
   qurt_thread_exit(status);
}

int __real_qurt_thread_join(unsigned int tid, int *status) 
{
   return qurt_thread_join(tid, status);
}

#endif //THREAD_WRAP

} //extern "C"
