/***********************************************************************
 * rfs_ops.h
 *
 * RFS OPS
 * Copyright (C) 2013-2014 QUALCOMM Technologies, Inc.
 *
 * Remote File System Ops to hook up different filesystem implemenations
 * to RFS APIs.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_ops.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-01-27   dks   Add support for RFS over RMTS APIs.
2013-11-14   dks   Create

===========================================================================*/

#ifndef __RFS_OPS_H__
#define __RFS_OPS_H__

#include "comdef.h"
#include "rfs_types.h"

/* Ops table to map the RFS APIs to appropriate underlying Filesystem APIs */

struct rfs_ops_type
{
  int (*open) (const char *path, int oflag);

  int (*close) (int filedes);

  int32 (*read) (int filedes, void *buf, uint32 nbyte);

  int32 (*write) (int filedes, const void *buf, uint32 nbyte);

  int (*unlink) (const char *path);

  int32 (*seek) (int filedes, int32 offset, int whence);

  int (*stat) (const char *path, struct rfs_stat_buf *buf);

  int32 (*put) (const char *path, void *data, uint32 length,
                      int oflag);

  int32 (*get) (const char *path, void *data, uint32 length);
};

void rfs_ops_register (const struct rfs_ops_type *ops);


#endif /* not __RFS_OPS_H__ */
