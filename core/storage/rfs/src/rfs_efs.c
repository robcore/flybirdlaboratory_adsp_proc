/***********************************************************************
 * rfs_efs.c
 *
 * RFS wrapper for EFS.
 * Copyright (C) 2013-2014 QUALCOMM Technologies, Inc.
 *
 * Remote File System wrapper layer on top of EFS. Maps the RFS APIs and
 * data structres to EFS APIs data structures and vice versa.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_efs.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-01-27   dks   Add support for RFS over RMTS APIs.
2013-11-14   dks   Create

===========================================================================*/

#include "rfs_config_i.h"

#ifdef FEATURE_RFS_USE_EFS

#include "rfs_efs.h"
#include "rfs_ops.h"
#include "rfs_errno.h"
#include "fs_public.h"
#include "fs_lib.h"
#include "fs_errno.h"
#include "comdef.h"

static int
map_efs_to_rfs_errno (int errno)
{
  switch (errno)
  {
    case ENOENT:
      return RFS_ENOENT;
    case EACCES:
      return RFS_EACCESS;
    case ENOMEM:
      return RFS_ENOMEM;
    case EPERM:
      return RFS_EPERM;
    case EBADF:
      return RFS_EBADF;
    case EEXIST:
      return RFS_EEXISTS;
    case ENODEV:
      return RFS_ENODEV;
    case EINVAL:
      return RFS_EINVAL;
    case EMFILE:
      return RFS_EMFILE;
    case ENOSPC:
      return RFS_ENOSPC;
    case ENAMETOOLONG:
      return RFS_ENAMETOOLONG;
    default:
      return RFS_ESYSTEM;
  }
}

static int
map_rfs_to_efs_oflag (int oflag)
{
  int efs_oflag;

  if (oflag & RFS_O_RDONLY == RFS_O_RDONLY)
    efs_oflag |= O_RDONLY;

  if (oflag & RFS_O_WRONLY == RFS_O_WRONLY)
    efs_oflag |= O_WRONLY;

  if (oflag & RFS_O_RDWR == RFS_O_RDWR)
    efs_oflag |= O_RDWR;

  if (oflag & RFS_O_CREAT == RFS_O_CREAT)
    efs_oflag |= O_CREAT;

  if (oflag & RFS_O_TRUNC == RFS_O_TRUNC)
    efs_oflag |= O_TRUNC;

  if (oflag & RFS_O_APPEND == RFS_O_APPEND)
    efs_oflag |= O_APPEND;

  return efs_oflag;
}


static int
rfs_efs_open (const char *path, int oflag)
{
  int fd;
  int efs_oflag;

  /* TODO: handle encrypt and compression flags */

  efs_oflag = map_rfs_to_efs_oflag (oflag);
  fd = efs_open (path, efs_oflag);
  if (fd < 0)
  {
    fd = map_efs_to_rfs_errno (efs_errno);
  }

  return fd;
}

static int
rfs_efs_close (int filedes)
{
  int result;

  result = efs_close (fildes);
  if (result != 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
  }

  return result;
}

static int32
rfs_efs_read (int filedes, void *buf, uint32 nbyte)
{
  int32 result = 0;
  uint32 bytes_to_read = nbyte;
  uint32 bytes_read = 0;

  while (bytes_to_read > 0)
  {
    result = efs_read (filedes, buf, bytes_to_read);

    if (result < 0)
    {
      result = map_efs_to_rfs_errno (efs_errno);
      return result;
    }

    if(result == 0)
    {
      break;
    }

    bytes_read += result;
    bytes_to_read = nbyte - bytes_read;
  }

  return bytes_read;
}

static int32
rfs_efs_write (int filedes, const void *buf, uint32 nbyte)
{
  int32 result = 0;
  uint32 bytes_to_write = nbyte;
  uint32 bytes_written = 0;

  while(bytes_to_write > 0)
  {
    result = efs_write (filedes, buf, bytes_to_write);

    if (result < 0)
    {
      result = map_efs_to_rfs_errno (efs_errno);
      return result;
    }

    if (result == 0)
    {
      break;
    }

    bytes_written += result;
    bytes_to_write = nbyte - bytes_written;
  }

  return bytes_written;
}

static int
rfs_efs_unlink (const char *path)
{
  int result;

  result = efs_unlink (path);
  if (result != 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
  }

  return result;
}

static int32
rfs_efs_seek (int filedes, int32 offset, int whence)
{
  int result;

  switch (whence)
  {
    case RFS_SEEK_CUR:
      efs_whence = SEEK_CUR;
      break;

    case RFS_SEEK_END:
      efs_whence = SEEK_END;
      break;

    case RFS_SEEK_SET:
      efs_whence = SEEK_SET;
      break;

    default:
      return RFS_EINVAL;
  }

  result = efs_lseek (filedes, offset, efs_whence);
  if (result < 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
  }

  return result;
}

static int
rfs_efs_stat (const char *path, struct rfs_stat_buf *buf)
{
  int result;
  struct fs_stat fs_buff;

  result = efs_stat (path, &fs_buff);
  if (result != 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
    return result;
  }

  buf->st_mode = fs_buff.st_mode;
  buf->st_size = fs_buff.st_size;

  return result;
}

static int32
rfs_efs_put (const char *path, void *data, uint32 length, int oflag)
{
  int32 result;
  int efs_oflag;

  efs_oflag = map_rfs_to_efs_oflag (oflag);

  result = efs_put (path, data, length, efs_oflag, 0666);
  if (result != 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
    return result;
  }

  return (int32) length;
}

static int32
rfs_efs_get (const char *path, void *data, uint32 length)
{
  int result;

  result = efs_get (path, data, length);
  if (result < 0)
  {
    result = map_efs_to_rfs_errno (efs_errno);
    return result;
  }

  return (int32) length;
}

int
rfs_efs_init (void)
{
  struct rfs_ops_type rfs_efs_ops;

  rfs_efs_ops.open = rfs_efs_open;
  rfs_efs_ops.close = rfs_efs_close;
  rfs_efs_ops.read = rfs_efs_read;
  rfs_efs_ops.write = rfs_efs_write;
  rfs_efs_ops.unlink = rfs_efs_unlink;
  rfs_efs_ops.seek = rfs_efs_seek;
  rfs_efs_ops.stat = rfs_efs_stat;
  rfs_efs_ops.put = rfs_efs_put;
  rfs_efs_ops.get = rfs_efs_get;

  rfs_ops_register (&rfs_efs_ops);

  return 0;
}

#endif /* FEATURE_RFS_USE_EFS */

