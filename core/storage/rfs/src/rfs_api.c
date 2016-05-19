/***********************************************************************
 * rfs_api.c
 *
 * RFS API implementations.
 * Copyright (C) 2013-2014 QUALCOMM Technologies, Inc.
 *
 * Implementation of the Remote File System Module APIs
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_api.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-08-06   dks   Return error for open with encrypt and compress oflags.
2014-07-18   rp    tftp and ipc-router integration changes from target.
2014-15-04   dks   Add support for RFS over RFSA APIs.
2014-01-27   dks   Add support for RFS over RMTS APIs.
2013-12-26   rp    Add tftp-client module.
2013-11-07   dks   Create

===========================================================================*/


#include "rfs_config_i.h"
#include "rfs_api.h"
#include "rfs_errno.h"
#include "rfs_ops.h"
#include "rfs_tftp.h"
#include "rfs_efs.h"
#include "rfs_nodev.h"
#include "rfs_rmts.h"
#include "rfs_rfsa.h"

#include <string.h>

static struct rfs_ops_type rfs_ops;

static int
rfs_validate_path (const char *path)
{
  if (path == NULL || path[0] == '\0')
    return RFS_EINVAL;

  if (strlen (path) > RFS_PATH_MAX)
    return RFS_ENAMETOOLONG;

  return RFS_ENOERROR;
}

int
rfs_open (const char *path, int oflag, int mode)
{
  int result;

  (void) mode;

  result = rfs_validate_path (path);
  if (result != RFS_ENOERROR)
    goto end;

  if ((oflag & RFS_O_ENCRYPT) || (oflag & RFS_O_COMPRESS))
  {
    result = RFS_ENOTSUPPORTED;
    goto end;
  }

  result = rfs_ops.open (path, oflag);

end:
  return result;
}

int
rfs_close (int fd)
{
  return rfs_ops.close (fd);
}

int32
rfs_read (int fd, void *buf, uint32 nbyte)
{
  if (buf == NULL)
    return RFS_EINVAL;

  return rfs_ops.read (fd, buf, nbyte);
}

int32
rfs_write (int fd, const void *buf, uint32 nbyte)
{
  if (buf == NULL)
    return RFS_EINVAL;

  return rfs_ops.write (fd, buf, nbyte);
}

int32
rfs_seek (int fd, int32 offset, int whence)
{
  return rfs_ops.seek (fd, offset, whence);
}

int
rfs_unlink (const char *path)
{
  int result;

  result = rfs_validate_path (path);
  if (result != RFS_ENOERROR)
    goto end;

  result = rfs_ops.unlink (path);

end:
  return result;
}

int
rfs_stat (const char *path, struct rfs_stat_buf *buf)
{
  int result;

  result = rfs_validate_path (path);
  if (result != RFS_ENOERROR)
    goto end;

  if (buf == NULL)
  {
    result = RFS_EINVAL;
    goto end;
  }

  result = rfs_ops.stat (path, buf);

end:
  return result;
}

int32
rfs_put (const char *path, void *data, uint32 length, int oflag, int mode)
{
  int result;

  (void) mode;

  result = rfs_validate_path (path);
  if (result != RFS_ENOERROR)
    goto end;

  if (data == NULL)
  {
    result = RFS_EINVAL;
    goto end;
  }

  if ((oflag & RFS_O_ENCRYPT) || (oflag & RFS_O_COMPRESS))
  {
    result = RFS_ENOTSUPPORTED;
    goto end;
  }

  result = rfs_ops.put (path, data, length, oflag);

end:
  return result;
}

int32
rfs_get (const char *path, void *data, uint32 length)
{
  int result;

  result = rfs_validate_path (path);
  if (result != RFS_ENOERROR)
    goto end;

  if (data == NULL)
  {
    result = RFS_EINVAL;
    goto end;
  }

  result = rfs_ops.get (path, data, length);

 end:
  return result;
}

void
rfs_ops_register (const struct rfs_ops_type *ops)
{
  memset (&rfs_ops, 0x0, sizeof (struct rfs_ops_type));
  memcpy (&rfs_ops, ops, sizeof (struct rfs_ops_type));
}

void
rfs_init (void)
{
  int result = -1;

#if defined (FEATURE_RFS_USE_TFTP)
  result = rfs_tftp_init ();
#elif defined (FEATURE_RFS_USE_RMTS)
  result = rfs_rmts_init ();
#elif defined (FEATURE_RFS_USE_RFSA)
  result = rfs_rfsa_init ();
#elif defined (FEATURE_RFS_USE_EFS)
  result = rfs_efs_init ();
#endif

  if (result != 0)
  {
    rfs_nodev_init ();
  }
}
