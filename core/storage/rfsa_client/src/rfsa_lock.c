/******************************************************************************
 * rfsa_lock.c
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

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_lock.c#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
2014-02-20   nr      Create.
=============================================================================*/
#include "rfsa_lock.h"

uint32
rfsa_thread_mutex_init (rfsa_mutex_handle *hdl_ptr)
{
  uint32 result = 0;
  result = pthread_mutex_init (hdl_ptr, NULL);

  return result;
}

uint32
rfsa_thread_lock (rfsa_mutex_handle *hdl_ptr)
{
  uint32 result = 0;
  result = pthread_mutex_lock (hdl_ptr);

  return result;
}

uint32
rfsa_thread_unlock (rfsa_mutex_handle *hdl_ptr)
{
  uint32 result = 0;
  result = pthread_mutex_unlock (hdl_ptr);

  return result;
}

