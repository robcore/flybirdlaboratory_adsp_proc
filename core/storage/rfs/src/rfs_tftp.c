/***********************************************************************
 * rfs_tftp.c
 *
 * RFS wrapper on top of TFTP.
 * Copyright (C) 2013-2014 QUALCOMM Technologies, Inc.
 *
 * RFS implementation on top of TFTP. This maps the RFS APIs and data
 * structres to TFTP APIs and data structures and vice versa.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_tftp.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-07-29   dks   Fix locks for accessing fds
2014-07-18   rp    tftp and ipc-router integration changes from target.
2014-06-11   rp    Renamed DEBUG_ASSERT as TFTP_DEBUG_ASSERT
2014-01-20   dks   Fix compilation on windows builds.
2014-01-13   dks   Add wrappers for rex critical section APIs.
2013-12-26   rp    Add tftp-client module.
2013-11-24   rp    Support TFTP extension options.
2013-11-12   dks   Create

===========================================================================*/

#include "rfs_config_i.h"

#ifdef FEATURE_RFS_USE_TFTP

#include "rfs_tftp.h"
#include "rfs_ops.h"
#include "rfs_fcntl.h"
#include "rfs_types.h"
#include "rfs_errno.h"
#include "tftp_client.h"
#include "rfs_osal.h"
#include "err.h"
#include "assert.h"
#include <stringl/stringl.h>

#include <string.h>

struct rfs_file_desc
{
  int used;
  char filename [RFS_PATH_MAX];
  uint32 offset;
  int oflag;
};

static struct rfs_file_desc rfs_fd [RFS_MAX_FILE_DESCRIPTORS];

static struct rfs_ops_type rfs_tftp_ops;

/* Critical section for accessing the FD table */
static rfs_osal_mutex_handle rfs_tftp_cs;

static void
rfs_tftp_lock_init (void)
{
  memset (&rfs_tftp_cs, 0, sizeof (rfs_tftp_cs));
  rfs_osal_mutex_init (&rfs_tftp_cs);
}

static void
rfs_tftp_lock (void)
{
  rfs_osal_mutex_lock (&rfs_tftp_cs);
}

static void
rfs_tftp_unlock (void)
{
  rfs_osal_mutex_unlock (&rfs_tftp_cs);
}

static int
rfs_tftp_allocate_fd (void)
{
  int i;

  rfs_tftp_lock ();

  for (i = 0; i < RFS_MAX_FILE_DESCRIPTORS; i++)
  {
    if (rfs_fd[i].used == 0)
    {
      rfs_fd[i].used = 1;
      break;
    }
  }

  rfs_tftp_unlock ();

  if (i == RFS_MAX_FILE_DESCRIPTORS)
  {
    i = -1;
  }

  return i;
}

static int
rfs_tftp_check_valid_fd (int fd)
{
  int result = 0;

  rfs_tftp_lock ();

  if (fd < 0 || fd >= RFS_MAX_FILE_DESCRIPTORS ||
      rfs_fd[fd].used == 0)
  {
    goto End;
  }

  result = 1;

End:
  rfs_tftp_unlock ();
  return result;
}

static int
rfs_tftp_free_fd (int fd)
{
  ASSERT ((fd >= 0) && (fd < RFS_MAX_FILE_DESCRIPTORS));

  rfs_tftp_lock ();

  ASSERT (rfs_fd[fd].used == 1);

  memset (&rfs_fd[fd], 0x0, sizeof (rfs_fd[fd]));

  rfs_tftp_unlock ();

  return 0;
}

static int
rfs_tftp_is_path_valid (const char *path)
{
  if (path == NULL)
    return 0;

  if (path[0] == '\0')
    return 0;

  return 1;
}

static int
rfs_tftp_map_tftp_to_rfs_error (enum tftp_client_result_type client_res)
{
  switch (client_res)
  {
    case TFTP_CLIENT_RESULT_SUCCESS:
      return RFS_ENOERROR;

    case TFTP_CLIENT_RESULT_TOO_MANY_REQUESTS:
      return RFS_EBUSY;

    case TFTP_CLIENT_RESULT_ENOMEM:
      return RFS_ENOMEM;

    case TFTP_CLIENT_RESULT_ENOENT:
      return RFS_ENOENT;

    case TFTP_CLIENT_RESULT_EPERM:
      return RFS_EPERM;

    case TFTP_CLIENT_RESULT_ENOSPC:
      return RFS_ENOSPC;

    case TFTP_CLIENT_RESULT_EEXIST:
      return RFS_EEXISTS;

    case TFTP_CLIENT_RESULT_TIME_OUT:
      return RFS_ETIMEOUT;

    case TFTP_CLIENT_RESULT_ENODEV:
    case TFTP_CLIENT_RESULT_NO_SERVER:
      return RFS_ENODEV;

    default:
      return RFS_ESYSTEM;
  }
}

int
rfs_tftp_open (const char *path, int oflag)
{
  int fd_index = -1, result, create_empty_file = 0;
  struct rfs_file_desc *fd;
  uint32 out_buf_size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_is_path_valid (path))
  {
    return RFS_EINVAL;
  }

  client_res = tftp_stat (path, &out_buf_size);
  if (client_res == TFTP_CLIENT_RESULT_ENOENT)
  {
    if (oflag & RFS_O_CREAT)
    {
      create_empty_file = 1;
      client_res = TFTP_CLIENT_RESULT_SUCCESS;
    }
  }

  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    result = rfs_tftp_map_tftp_to_rfs_error (client_res);
    return result;
  }

  if (oflag & RFS_O_TRUNC)
  {
    create_empty_file = 1;
  }

  fd_index = rfs_tftp_allocate_fd ();
  if (fd_index < 0)
  {
    return RFS_EMFILE;
  }

  if (create_empty_file)
  {
    /* Create file */
    client_res = tftp_put (path, "", 0, &out_buf_size);
    if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
    {
      result = rfs_tftp_map_tftp_to_rfs_error (client_res);
      goto ERROR;
    }
  }

  ASSERT (rfs_fd[fd_index].used == 1);
  fd = &rfs_fd[fd_index];
  (void) strlcpy (fd->filename, path, sizeof (fd->filename));
  fd->oflag = oflag;
  fd->offset = 0;
  goto END;

ERROR:
  if (fd_index >= 0)
  {
    rfs_tftp_free_fd (fd_index);
  }
  fd_index = result;

END:
  return fd_index;
}

int
rfs_tftp_close (int fd)
{
  if (!rfs_tftp_check_valid_fd (fd))
  {
    return RFS_EBADF;
  }
  return rfs_tftp_free_fd (fd);
}

int32
rfs_tftp_read (int filedes, void *buf, uint32 nbyte)
{
  struct rfs_file_desc *fd;
  int32 read_size;
  uint32 out_buf_size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_check_valid_fd (filedes))
  {
    return RFS_EBADF;
  }

  fd = &rfs_fd[filedes];
  if ( ((fd->oflag & RFS_O_RDONLY) == 0) &&
       ((fd->oflag & RFS_O_RDWR) == 0))
  {
    return RFS_EBADF;
  }

  if (buf == NULL)
  {
    return RFS_EINVAL;
  }

  if (nbyte == 0)
  {
    return 0;
  }

  /* TODO: Handle encrpytion and compression */

  client_res = tftp_read (fd->filename, fd->offset, buf, nbyte, &out_buf_size);
  if (client_res !=  TFTP_CLIENT_RESULT_SUCCESS)
  {
    read_size = rfs_tftp_map_tftp_to_rfs_error (client_res);
  }
  else
  {
    read_size = (int32)out_buf_size;
    fd->offset += read_size;
  }

  return read_size;
}

int32
rfs_tftp_write (int filedes, const void *buf, uint32 nbyte)
{
  struct rfs_file_desc *fd;
  int32 wrote_size;
  uint32 out_buf_size;
  int append_mode = 0;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_check_valid_fd (filedes))
  {
    return RFS_EBADF;
  }

  fd = &rfs_fd[filedes];
  if ( ((fd->oflag & RFS_O_WRONLY) == 0) &&
       ((fd->oflag & RFS_O_RDWR) == 0))
  {
    return RFS_EBADF;
  }

  if (buf == NULL)
  {
    return RFS_EINVAL;
  }

  if (nbyte == 0)
  {
    return 0;
  }

  if ((fd->oflag & RFS_O_APPEND) != 0)
  {
    append_mode = 1;
  }
  else
  {
    append_mode = 0;
  }

  /* TODO: Handle encrpytion and compression */

  client_res = tftp_write (fd->filename, fd->offset, append_mode, buf, nbyte,
                           &out_buf_size);
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    wrote_size = rfs_tftp_map_tftp_to_rfs_error (client_res);
  }
  else
  {
    wrote_size = (int32)out_buf_size;
    fd->offset += wrote_size;
  }

  return wrote_size;
}

int32
rfs_tftp_seek (int filedes, int32 offset, int whence)
{
  int32 new_offset;
  uint32 file_size;
  struct rfs_file_desc *fd;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_check_valid_fd (filedes))
  {
    return RFS_EBADF;
  }

  fd = &rfs_fd[filedes];

  switch (whence)
  {
    case RFS_SEEK_CUR:
      new_offset = fd->offset + offset;
      break;

    case RFS_SEEK_END:
      client_res = tftp_stat (fd->filename, &file_size);
      if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
      {
        ERR_FATAL ("%d, Filesystem corrupted. Open file deleted%d%d\n",
                    client_res, 0, 0);
      }
      new_offset = file_size + offset;
      break;

    case RFS_SEEK_SET:
      new_offset = 0 + offset;
      break;

    default:
      return RFS_EINVAL;
  }


  if (new_offset < 0)
  {
    return RFS_EPERM;
  }

  fd->offset = new_offset;

  return new_offset;
}

int
rfs_tftp_unlink (const char *path)
{
  int result = 0;
  uint32 file_size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_is_path_valid (path))
  {
    return RFS_EINVAL;
  }

  client_res = tftp_stat (path, &file_size);
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    result = rfs_tftp_map_tftp_to_rfs_error (client_res);
    goto End;
  }

  client_res = tftp_unlink (path);
  result = rfs_tftp_map_tftp_to_rfs_error (client_res);

End:
  if(result == RFS_ENOENT)
  {
    result = RFS_ENOERROR;
  }
  return result;
}


int
rfs_tftp_stat (const char *path, struct rfs_stat_buf *buf)
{
  int result;
  uint32 size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_is_path_valid (path))
  {
    return RFS_EINVAL;
  }

  if (buf == NULL)
  {
    return RFS_EINVAL;
  }

  client_res = tftp_stat (path, &size);
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    result = rfs_tftp_map_tftp_to_rfs_error (client_res);
    return result;
  }

  memset (buf, 0x0, sizeof (struct rfs_stat_buf));
  buf->st_size = size;

  return 0;
}

int32
rfs_tftp_put (const char *path, void *buf, uint32 length, int oflag)
{
  int32 result;
  uint32 out_buf_size, file_size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_is_path_valid (path))
  {
    return RFS_EINVAL;
  }

  if (buf == NULL)
  {
    return RFS_EINVAL;
  }

  if ((oflag & RFS_O_RDONLY) != 0)
  {
    return RFS_EINVAL;
  }


  client_res = tftp_stat (path, &file_size);
  if (client_res == TFTP_CLIENT_RESULT_ENOENT)
  {
    if ((oflag & RFS_O_CREAT) == 0)
	  {
	    return RFS_ENOENT;
	  }
  }

  /* TODO: Handle encrpytion and compression */

  client_res = tftp_put (path, buf, length, &out_buf_size);
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    result = rfs_tftp_map_tftp_to_rfs_error (client_res);
    return result;
  }

  return (int32)out_buf_size;
}

int32
rfs_tftp_get (const char *path, void *buf, uint32 length)
{
  int32 result;
  uint32 out_buf_size;
  enum tftp_client_result_type client_res;

  if (!rfs_tftp_is_path_valid (path))
  {
    return RFS_EINVAL;
  }

  if (buf == NULL)
  {
    return RFS_EINVAL;
  }

  if (length == 0)
  {
    return 0;
  }
  /* TODO: Handle encrpytion and compression */

  client_res = tftp_get (path, buf, length, &out_buf_size);
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    result = rfs_tftp_map_tftp_to_rfs_error (client_res);
    return result;
  }

  return (int32)out_buf_size;
}


int
rfs_tftp_init (void)
{
  int result = -1;
  enum tftp_client_result_type client_res;

  rfs_tftp_lock_init ();
  rfs_tftp_lock ();

  client_res = tftp_client_init ();
  if (client_res != TFTP_CLIENT_RESULT_SUCCESS)
  {
    goto End;
  }

  memset (rfs_fd, 0x0, sizeof (rfs_fd));
  memset (&rfs_tftp_ops, 0x0, sizeof (rfs_tftp_ops));

  rfs_tftp_ops.open = rfs_tftp_open;
  rfs_tftp_ops.close = rfs_tftp_close;
  rfs_tftp_ops.read = rfs_tftp_read;
  rfs_tftp_ops.write = rfs_tftp_write;
  rfs_tftp_ops.seek = rfs_tftp_seek;
  rfs_tftp_ops.unlink = rfs_tftp_unlink;
  rfs_tftp_ops.stat = rfs_tftp_stat;
  rfs_tftp_ops.put = rfs_tftp_put;
  rfs_tftp_ops.get = rfs_tftp_get;

  rfs_ops_register (&rfs_tftp_ops);
  result = 0;

End:
  rfs_tftp_unlock ();
  return result;
}

#endif /* FEATURE_RFS_USE_TFTP */
