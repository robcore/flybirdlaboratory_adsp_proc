/***********************************************************************
 * rfs_utils.h
 *
 * Utility functions to create and verify files using RFS APIs.
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * Utility functions to create and verify files using RFS APIs.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/inc/rfs_utils.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-08-04   rp    Create

===========================================================================*/

#ifndef __RFS_UTILS_H__
#define __RFS_UTILS_H__

#include "comdef.h"

int rfs_util_create_file (const char *filename, uint32 file_size,
                          uint32 write_size, uint32 write_size_incr,
                          uint32 buf_seed,
                          int verify_file_after_each_write);

int rfs_util_create_file_from_buf (const char *filename, uint8 *file_buf,
            uint32 file_size, uint32 write_size, uint32 write_size_incr);

int rfs_util_verify_file_in_chunks (const char *filename, const uint8 *file_buf,
                                    uint32 file_size, uint32 read_size,
                                    uint32 read_size_incr);

int rfs_util_verify_file (const char *filename, const uint8 *file_buf,
                          uint32 file_size);



#endif /* not __RFS_UTILS_H__ */
