/***********************************************************************
 * rfs_rmts.c
 *
 * RFS wrapper for Remote Storage Server.
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * Remote File System wrapper layer on top of Remote Storage server. Maps the
 * RFS APIs and data structres to RMTS APIs data structures and vice versa.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_rmts.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-01-24   dks   Create

===========================================================================*/

#include "rfs_config_i.h"

#ifdef FEATURE_RFS_USE_RMTS

#include "rfs_rmts.h"
#include "rfs_ops.h"
#include "rfs_errno.h"
#include "rfs_osal.h"
#include "comdef.h"
#include "assert.h"
#include <string.h>
#include "remotefs_qmi_server.h"
#include "remotefs_comm_api.h"

struct rfs_rmts_info_type
{
  rfs_osal_crit_sect_type cs;
  int rmts_connect_done;
};

static struct rfs_rmts_info_type rfs_rmts_info;

static remotefs_status_type
rfs_rmts_connect (void)
{
  remotefs_status_type result = RMFS_NO_ERROR;

  rfs_osal_enter_crit_sect (&rfs_rmts_info.cs);

  if (!rfs_rmts_info.rmts_connect_done)
  {
    result = rmtfs_refresh_file_mapping ();
    if (result == RMFS_NO_ERROR)
    {
      rfs_rmts_info.rmts_connect_done = 1;
    }
  }

  rfs_osal_leave_crit_sect (&rfs_rmts_info.cs);

  return result;
}

static int
map_rmts_to_rfs_errno (remotefs_status_type rmts_errno)
{
  switch (rmts_errno)
  {
    case RMFS_NO_ERROR:
      return RFS_ENOERROR;

    case RMFS_ERROR_PARAM:
      return RFS_EINVAL;

    case RMFS_ERROR_BUSY:
      return RFS_EBUSY;

    case RMFS_ERROR_PIPE:
    case RMFS_ERROR_UNINIT:
    case RMFS_ERROR_DEVICE:
      return RFS_ESYSTEM;

    default:
      ASSERT (0);
      return RFS_ESYSTEM;
  }
}

static int32
rfs_rmts_put (const char *path, void *data, uint32 length, int oflag)
{
  int32 result;
  remotefs_status_type rmts_result;
  (void) oflag;

  rmts_result = rfs_rmts_connect ();
  if (rmts_result == RMFS_NO_ERROR)
  {
    rmts_result = rmtfs_write_file (path, data, length);
  }

  if (rmts_result != RMFS_NO_ERROR)
  {
    result = map_rmts_to_rfs_errno (rmts_result);
  }
  else
  {
    result = length;
  }

  return result;
}

static int32
rfs_rmts_get (const char *path, void *data, uint32 length)
{
  int32 result;
  remotefs_status_type rmts_result;

  rmts_result = rfs_rmts_connect ();
  if (rmts_result == RMFS_NO_ERROR)
  {
    rmts_result = rmtfs_read_file (path, data, length);
  }

  if (rmts_result != RMFS_NO_ERROR)
  {
    result = map_rmts_to_rfs_errno (rmts_result);
  }
  else
  {
    result = length;
  }

  return result;
}

static int
rfs_rmts_invalid_open (const char *path, int oflag)
{
  (void) path;
  (void) oflag;
  return RFS_EPERM;
}

static int
rfs_rmts_invalid_close (int filedes)
{
  (void) filedes;
  return RFS_EPERM;
}

static int32
rfs_rmts_invalid_read (int filedes, void *buf, uint32 nbyte)
{
  (void) filedes;
  (void) buf;
  (void) nbyte;
  return RFS_EPERM;
}

static int32
rfs_rmts_invalid_write (int filedes, const void *buf, uint32 nbyte)
{
  (void) filedes;
  (void) buf;
  (void) nbyte;
  return RFS_EPERM;
}

static int
rfs_rmts_invalid_unlink (const char *path)
{
  (void) path;
  return RFS_EPERM;
}

static int32
rfs_rmts_invalid_seek (int filedes, int32 offset, int whence)
{
  (void) filedes;
  (void) offset;
  (void) whence;
  return RFS_EPERM;
}

static int
rfs_rmts_invalid_stat (const char *path, struct rfs_stat_buf *buf)
{
  (void) path;
  (void) buf;
  return RFS_EPERM;
}

int
rfs_rmts_init (void)
{
  struct rfs_ops_type rfs_rmts_ops;

  rfs_rmts_ops.open = rfs_rmts_invalid_open;
  rfs_rmts_ops.close = rfs_rmts_invalid_close;
  rfs_rmts_ops.read = rfs_rmts_invalid_read;
  rfs_rmts_ops.write = rfs_rmts_invalid_write;
  rfs_rmts_ops.unlink = rfs_rmts_invalid_unlink;
  rfs_rmts_ops.seek = rfs_rmts_invalid_seek;
  rfs_rmts_ops.stat = rfs_rmts_invalid_stat;
  rfs_rmts_ops.put = rfs_rmts_put;
  rfs_rmts_ops.get = rfs_rmts_get;

  rfs_ops_register (&rfs_rmts_ops);

  memset (&rfs_rmts_info, 0x0, sizeof (rfs_rmts_info));
  rfs_osal_init_crit_sect (&rfs_rmts_info.cs);

  return 0;
}

#endif /* FEATURE_RFS_USE_EFS */

