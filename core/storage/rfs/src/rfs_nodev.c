/***********************************************************************
 * rfs_nodev.c
 *
 * RFS Nodev Operations.
 * Copyright (C) 2013-2014 QUALCOMM Technologies, Inc.
 *
 * Stub operations which return error for all RFS APIs when there are no
 * Filessytem implementing RFS APIs
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_nodev.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-07-29   dks   Fix error-codes.
2013-11-12   dks   Create

===========================================================================*/

#include "rfs_nodev.h"
#include "rfs_ops.h"
#include "rfs_errno.h"

static int
rfs_nodev_open (const char *path, int oflag)
{
  (void) path;
  (void) oflag;
  return RFS_ECONFIG;
}

static int
rfs_nodev_close (int filedes)
{
  (void) filedes;
  return RFS_ECONFIG;
}

static int32
rfs_nodev_read (int filedes, void *buf, uint32 nbyte)
{
  (void) filedes;
  (void) buf;
  (void) nbyte;
  return RFS_ECONFIG;
}

static int32
rfs_nodev_write (int filedes, const void *buf, uint32 nbyte)
{
  (void) filedes;
  (void) buf;
  (void) nbyte;
  return RFS_ECONFIG;
}

static int
rfs_nodev_unlink (const char *path)
{
  (void) path;
  return RFS_ECONFIG;
}

static int32
rfs_nodev_seek (int filedes, int32 offset, int whence)
{
  (void) filedes;
  (void) offset;
  (void) whence;
  return RFS_ECONFIG;
}

static int
rfs_nodev_stat (const char *path, struct rfs_stat_buf *buf)
{
  (void) path;
  (void) buf;
  return RFS_ECONFIG;
}

static int32
rfs_nodev_put (const char *path, void *data, uint32 length, int oflag)
{
  (void) path;
  (void) data;
  (void) length;
  (void) oflag;
  return RFS_ECONFIG;
}

static int32
rfs_nodev_get (const char *path, void *data, uint32 length)
{
  (void) path;
  (void) data;
  (void) length;
  return RFS_ECONFIG;
}

void
rfs_nodev_init (void)
{
  struct rfs_ops_type rfs_nodev_ops;

  rfs_nodev_ops.open = rfs_nodev_open;
  rfs_nodev_ops.close = rfs_nodev_close;
  rfs_nodev_ops.read = rfs_nodev_read;
  rfs_nodev_ops.write = rfs_nodev_write;
  rfs_nodev_ops.seek = rfs_nodev_seek;
  rfs_nodev_ops.unlink = rfs_nodev_unlink;
  rfs_nodev_ops.stat = rfs_nodev_stat;
  rfs_nodev_ops.put = rfs_nodev_put;
  rfs_nodev_ops.get = rfs_nodev_get;

  rfs_ops_register (&rfs_nodev_ops);
}
