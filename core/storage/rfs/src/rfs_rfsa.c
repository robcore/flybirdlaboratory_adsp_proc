/***********************************************************************
 * rfs_rfsa.c
 *
 * RFS wrapper for RFS_ACCESS
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * APIs to hook up RFS_ACCESS APIs under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_rfsa.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-05-29   dks   Fix RFSA path creation logic
2014-04-02   dks   Create

===========================================================================*/

#include "rfs_config_i.h"

#ifdef FEATURE_RFS_USE_RFSA

#include "rfs_rfsa.h"
#include "rfs_fcntl.h"
#include "rfs_ops.h"
#include "rfs_errno.h"
#include "rfs_osal.h"
#include "comdef.h"
#include "assert.h"
#include <string.h>
#include "rfsa_client.h"
#include <stdio.h>
#include <stdlib.h>

#if defined (FEATURE_RFSA_ON_ADSP)
  #define RFSA_ROOT_DIR "ADSP://"
#elif defined (FEATURE_RFSA_ON_MPSS)
  #define RFSA_ROOT_DIR "MPSS://"
#else
  #error "To compile RFSA turn on FEATURE_RFSA_ON_ADSP or FEATURE_RFSA_ON_MPSS"
#endif

static int rfs_rfsa_open (const char *path, int oflag);
static int32 rfs_rfsa_write (int filedes, const void *buf, uint32 nbyte);
static int32 rfs_rfsa_read (int filedes, void *buf, uint32 nbyte);
static int rfs_rfsa_close (int filedes);

static int
map_rfsa_to_rfs_errno (int rfsa_errno)
{
  switch (rfsa_errno)
  {
    case -1:
      return RFS_ESYSTEM;

    default:
      ASSERT (0);
      return RFS_ESYSTEM;
  }
}

static int
map_rfs_to_rfsa_oflag (int oflag)
{
  int rfsa_oflag = 0;

  if ((oflag & RFS_O_RDONLY) == RFS_O_RDONLY)
    rfsa_oflag |= O_RDONLY;

  if ((oflag & RFS_O_WRONLY) == RFS_O_WRONLY)
    rfsa_oflag |= O_WRONLY;

  if ((oflag & RFS_O_RDWR) == RFS_O_RDWR)
    rfsa_oflag |= O_RDWR;

  if ((oflag & RFS_O_CREAT) == RFS_O_CREAT)
    rfsa_oflag |= O_CREAT;

  if ((oflag & RFS_O_TRUNC) == RFS_O_TRUNC)
    rfsa_oflag |= O_TRUNC;

  if ((oflag & RFS_O_APPEND) == RFS_O_APPEND)
    rfsa_oflag |= O_APPEND;

  return rfsa_oflag;
}

static char *
allocate_rfsa_path (const char *path)
{
  uint32 path_len;
  char *real_path, *rfsa_path;

  real_path = (char *) path;
  while (*real_path != 0 && *real_path == '/')
  {
    real_path++;
  }

  path_len = strlen (real_path) + strlen (RFSA_ROOT_DIR) + 1;
  rfsa_path = (char *) malloc (path_len);
  if (rfsa_path == NULL)
    return rfsa_path;

  (void) snprintf (rfsa_path, path_len, "%s%s", RFSA_ROOT_DIR, real_path);
  return rfsa_path;
}

static void
free_rfsa_path (char *path)
{
  free (path);
}


static int32
rfs_rfsa_put (const char *path, void *data, uint32 length, int oflag)
{
  int32 result, fd;

  fd = rfs_rfsa_open (path, oflag);
  result = fd;

  if (fd < 0)
  {
    goto end;
  }

  result = rfs_rfsa_write (fd, data, length);

end:

  if (fd >= 0)
  {
    (void) rfs_rfsa_close (fd);
  }

  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int32
rfs_rfsa_get (const char *path, void *data, uint32 length)
{
  int32 result, fd;

  fd = rfs_rfsa_open (path, O_RDONLY);
  result = fd;

  if (fd < 0)
  {
    goto end;
  }

  result = rfs_rfsa_read (fd, data, length);

end:

  if (fd >= 0)
  {
    (void) rfs_rfsa_close (fd);
  }

  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int
rfs_rfsa_open (const char *path, int oflag)
{
  int32 result;
  int rfsa_oflag;
  char *rfsa_path;

  rfsa_path = allocate_rfsa_path (path);
  if (rfsa_path == NULL)
  {
    result = RFS_ENOMEM;
    goto end;
  }

  rfsa_oflag = map_rfs_to_rfsa_oflag (oflag);

  result = rfsa_open (rfsa_path, rfsa_oflag);

end:
  if (rfsa_path != NULL)
  {
    free_rfsa_path (rfsa_path);
  }

  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int
rfs_rfsa_close (int filedes)
{
  int32 result;

  result = rfsa_close (filedes);
  if (result != 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  result = RFS_ENOERROR;
  return result;
}

static int32
rfs_rfsa_read (int filedes, void *buf, uint32 nbyte)
{
  int32 result;

  if (nbyte == 0)
    return 0;

  result = rfsa_read (filedes, buf, nbyte);
  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int32
rfs_rfsa_write (int filedes, const void *buf, uint32 nbyte)
{
  int32 result;

  if (nbyte == 0)
    return 0;

  result = rfsa_write (filedes, (char *)buf, nbyte);
  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int32
rfs_rfsa_seek (int filedes, int32 offset, int whence)
{
  int32 result;
  int32 seek_direction;

  switch (whence)
  {
    case RFS_SEEK_SET:
      seek_direction = RFSA_SEEK_SET;
      break;
    case RFS_SEEK_CUR:
      seek_direction = RFSA_SEEK_CUR;
      break;
    case RFS_SEEK_END:
      seek_direction = RFSA_SEEK_END;
      break;
    default:
      return RFS_EINVAL;
  }

  result = rfsa_seek (filedes, offset, seek_direction);
  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  result = rfsa_ftell (filedes);
  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  return result;
}

static int
rfs_rfsa_stat (const char *path, struct rfs_stat_buf *buf)
{
  int32 result;
  char *rfsa_path;

  rfsa_path = allocate_rfsa_path (path);
  if (rfsa_path == NULL)
  {
    result = RFS_ENOMEM;
    goto end;
  }

  result = rfsa_plen (rfsa_path);

end:
  if (rfsa_path != NULL)
  {
    free_rfsa_path (rfsa_path);
  }

  if (result < 0)
  {
    return map_rfsa_to_rfs_errno (result);
  }

  memset (buf, 0x0, sizeof (struct rfs_stat_buf));
  buf->st_size = result;
  return RFS_ENOERROR;
}

static int
rfs_rfsa_invalid_unlink (const char *path)
{
  (void) path;
  return RFS_EPERM;
}

int
rfs_rfsa_init (void)
{
  struct rfs_ops_type rfs_rfsa_ops;

  rfs_rfsa_ops.open = rfs_rfsa_open;
  rfs_rfsa_ops.close = rfs_rfsa_close;
  rfs_rfsa_ops.read = rfs_rfsa_read;
  rfs_rfsa_ops.write = rfs_rfsa_write;
  rfs_rfsa_ops.unlink = rfs_rfsa_invalid_unlink;
  rfs_rfsa_ops.seek = rfs_rfsa_seek;
  rfs_rfsa_ops.stat = rfs_rfsa_stat;
  rfs_rfsa_ops.put = rfs_rfsa_put;
  rfs_rfsa_ops.get = rfs_rfsa_get;

  rfs_ops_register (&rfs_rfsa_ops);

  return 0;
}

#endif /* FEATURE_RFS_USE_RFSA */

