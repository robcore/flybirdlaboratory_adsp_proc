#ifndef __RFSA_LOCK_H__
#define __RFSA_LOCK_H__
/******************************************************************************
 * rfsa_lock.h
 *
 * Implement platform dependent critical sections
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_lock.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
2014-02-20   nr      Create.
=============================================================================*/
#include "comdef.h"
#include <pthread.h>

typedef pthread_mutex_t rfsa_mutex_handle;

uint32 rfsa_thread_mutex_init (rfsa_mutex_handle *hdl_ptr);

uint32 rfsa_thread_lock (rfsa_mutex_handle *hdl_ptr);

uint32 rfsa_thread_unlock (rfsa_mutex_handle *hdl_ptr);

#endif /* __RFSA_LOCK_H__ */

