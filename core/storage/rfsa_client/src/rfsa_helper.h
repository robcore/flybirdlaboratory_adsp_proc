/******************************************************************************
 * rfsa_helper.h
 *
 * Helper functions for rfsa client.
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_helper.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-02-20   nr      Create.
=============================================================================*/

#ifndef __RFSA_HELPER_H__
#define __RFSA_HELPER_H__

#include "comdef.h"

struct rfsa_stat
{
  uint64 flags;
  uint8 is_file_size_valid;
  uint32 file_size;
};

int32 rfsa_init_helper (void);

int32 rfsa_stat_helper (const char *filename, struct rfsa_stat *buf);

int32 rfsa_create_file_helper (const char *filename, uint64 flags);

int32 rfsa_read_helper (const char *filename, uint32 offset, void *buffer,
                        uint32 buf_size);

int32 rfsa_write_helper (const char *filename, uint32 offset, void *buffer,
                         uint32 buf_size);

#endif /* __RFSA_HELPER_H__ */

