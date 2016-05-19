#ifndef __RFSA_MEMORY_H__
#define __RFSA_MEMORY_H__
/******************************************************************************
 * rfsa_memory.h
 *
 * RFSA memory functions
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_memory.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
2014-02-20   nr      Create.
=============================================================================*/
#include "comdef.h"

int32 rfsa_mmap (uint64 physical_addr, uint32 size, void **virtual_addr);

#endif /* __RFSA_MEMORY_H__ */
