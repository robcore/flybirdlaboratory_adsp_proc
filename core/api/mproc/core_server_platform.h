#ifndef  _CORE_SERVER_PLATFORM_H_
#define  _CORE_SERVER_PLATFORM_H_
/*---------------------------------------------------------------------------
   CORE_SERVER_PLATFORM.H
---------------------------------------------------------------------------*/
/*!
  @file
    core_server_platform.h

  @brief
    This file contains the platform specific definitions for the core
    server framework

  ---------------------------------------------------------------------------
  Copyright (c) 2012 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$$

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

#include <stdlib.h>

#include "qurt.h"
#include "qurt_timer.h"
#include "msg.h"
#include "err.h"
#include "comdef.h"
#include "stringl/stringl.h"

#define ALLOCATOR( _SIZE_IN_BYTES_ )     calloc(1, _SIZE_IN_BYTES_ )
#define DEALLOCATE( _PTR_ )              free( _PTR_ ) 


#define DEBUG MSG_HIGH
#define CLASS_NAME_MAX 16
#define TASK_NAME_MAX 16

//Qurt based implementation of task
typedef struct _qurt_task_impl {
    qurt_thread_t       thread;
    qurt_thread_attr_t  thread_attr;
    qurt_anysignal_t    signal;
    unsigned int        sigs;
    unsigned int        prio;
    unsigned int        stack_size;
    void                *stack_addr;
}task_impl;


typedef struct _qurt_lock_impl {
    qurt_mutex_t        crit_sec;
}lock_impl;


typedef struct _qurt_timer_impl {
   qurt_timer_t        timer_type;
   unsigned int        time_msecs;
}timer_impl_type;

/* Platform specific locking macros */
#define LOCK_DATA(_LOCK_VARIABLE_) \
           qurt_mutex_lock(&((_LOCK_VARIABLE_).crit_sec))

#define UNLOCK_DATA(_LOCK_VARIABLE_)\
           qurt_mutex_unlock(&((_LOCK_VARIABLE_).crit_sec))

#define LOCK_INIT_DATA(_LOCK_VARIABLE_,_LOCK_ATTR_) \
           qurt_mutex_init(&((_LOCK_VARIABLE_).crit_sec))

#define LOCK_DEINIT_DATA(_LOCK_VARIABLE_,_LOCK_ATTR_) \
           qurt_mutex_destroy(&((_LOCK_VARIABLE_).crit_sec))

#endif 
