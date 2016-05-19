/***********************************************************************
 * rfs_utils.c
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

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_utils.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-08-26   rp    Bring in changes from target-unit-testing.
2014-08-04   rp    Create

===========================================================================*/

#include "rfs_utils.h"
#include "rfs_api.h"
#include "assert.h"
#include "rfs_msg.h"
#include "stringl/stringl.h"

#include <stdlib.h>
#include <string.h>

static void
rfs_util_fill_buf (uint8 *buf, uint32 buf_size, const char *filename,
                   uint32 block_no, uint32 id)
{
  char temp_buf[100];
  uint32 cur_buf_size, temp_buf_size, ctr;

  memset (buf, 0, buf_size);

  cur_buf_size = ctr = 0;
  while (cur_buf_size < buf_size)
  {
    memset (temp_buf, 0, sizeof (temp_buf));
    snprintf (temp_buf, sizeof (temp_buf),
              "%s-%d-%d-%d\n", filename, (int)block_no,
              (int)id, (int)ctr++);
    strlcat ((char *)buf, temp_buf, buf_size);
    temp_buf_size = strlen (temp_buf);
    cur_buf_size += temp_buf_size;
  }
}

int
rfs_util_verify_file_in_chunks (const char *filename, const uint8 *file_buf,
                                uint32 file_size, uint32 read_size,
                                uint32 read_size_incr)
{
  int fd = -1, result = -1;
  uint8 *cur_buf, *verify_buf = NULL;
  uint32 cur_file_size, cur_read_size, remaining_size;
  struct rfs_stat_buf stat_buf;

  verify_buf = malloc (file_size);
  if (verify_buf == NULL)
  {
    RFS_MSG_STRING_1 ("%d, malloc failed", (int)file_size);
    goto Error;
  }

  result = rfs_stat (filename, &stat_buf);
  ASSERT (result == 0);
  ASSERT ((int32)stat_buf.st_size == file_size);

  memset (verify_buf, 0, file_size);

  fd = rfs_open (filename, RFS_O_RDONLY, 0644);
  if (fd < 0)
  {
    goto End;
  }

  cur_file_size = 0;
  cur_read_size = read_size;
  while (cur_file_size < file_size)
  {
    remaining_size = file_size - cur_file_size;
    cur_read_size += read_size_incr;
    if (cur_read_size > remaining_size)
    {
      cur_read_size = remaining_size;
    }

    cur_buf = &verify_buf[cur_file_size];
    result = rfs_read (fd, cur_buf, cur_read_size);
    if (result != cur_read_size)
    {
      RFS_MSG_STRING_1 ("%d, rfs_read failed", result);
      goto Error;
    }

    cur_file_size += cur_read_size;

    result = memcmp (file_buf, verify_buf, cur_file_size);
    ASSERT (result == 0);
  }

  result = memcmp (file_buf, verify_buf, file_size);
  ASSERT (result == 0);
  result = 0;
  goto End;

Error:
    result = -1;

End:
  if (verify_buf != NULL)
  {
    free (verify_buf);
  }

  if (fd >= 0)
  {
    (void) rfs_close (fd);
  }

  return result;
}

int
rfs_util_verify_file (const char *filename, const uint8 *file_buf,
                      uint32 file_size)
{
  int result;

  result = rfs_util_verify_file_in_chunks (filename, file_buf,
                                    file_size, file_size, 0);
  ASSERT (result == 0);
  return result;
}


int
rfs_util_create_file (const char *filename, uint32 file_size,
                      uint32 write_size, uint32 write_size_incr,
                      uint32 buf_seed,
                      int verify_file_after_each_write)
{
  uint32 cur_file_size, cur_write_size, remaining_size, block_no;
  uint8 *file_buf = NULL, *cur_buf;
  int fd = -1, result = -1;

  file_buf = malloc (file_size);
  if (file_buf == NULL)
  {
    RFS_MSG_STRING_1 ("%d, malloc failed", (int)file_size);
    goto Error;
  }

  memset (file_buf, 0, file_size);

  fd = rfs_open (filename, RFS_O_CREAT | RFS_O_WRONLY | RFS_O_TRUNC, 0644);
  if (fd < 0)
  {
    RFS_MSG_STRING_1 ("%d, rfs_open failed", fd);
    goto Error;
  }

  RFS_MSG_STRING_1 ("%d, rfs_open success", fd);

  cur_file_size = block_no = 0;
  cur_write_size = write_size;
  while (cur_file_size < file_size)
  {
    remaining_size = file_size - cur_file_size;
    cur_write_size += write_size_incr;
    if (cur_write_size > remaining_size)
    {
      cur_write_size = remaining_size;
    }

    cur_buf = &file_buf[cur_file_size];
    rfs_util_fill_buf (cur_buf, cur_write_size, filename, ++block_no, buf_seed);
    result = rfs_write (fd, cur_buf, cur_write_size);
    if (result != cur_write_size)
    {
      RFS_MSG_STRING_1 ("%d, rfs_write failed", result);
      goto Error;
    }

    cur_file_size += cur_write_size;

    if (verify_file_after_each_write)
    {
      result = rfs_util_verify_file_in_chunks (filename, file_buf,
                      cur_file_size, write_size, write_size_incr);
      if (result != 0)
      {
        RFS_MSG_STRING_1 ("file verification failed. file=%s", filename);
        RFS_MSG_STRING_1 ("file verification failed. size=%d", cur_file_size);
        goto Error;
      }
    }
  }

  result = 0;
  goto End;

Error:
result = -1;

End:
  if (file_buf != NULL)
  {
    free (file_buf);
  }

  if (fd >= 0)
  {
    (void) rfs_close (fd);
  }

  return result;
}

int
rfs_util_create_file_from_buf (const char *filename, uint8 *file_buf,
                               uint32 file_size, uint32 write_size,
                               uint32 write_size_incr)
{
  uint32 cur_file_size, cur_write_size, remaining_size;
  uint8 *cur_buf;
  int fd = -1, result = -1;

  fd = rfs_open (filename, RFS_O_CREAT | RFS_O_WRONLY | RFS_O_TRUNC, 0644);
  if (fd < 0)
  {
    RFS_MSG_STRING_1 ("%d, rfs_open failed", fd);
    goto Error;
  }

  cur_file_size = 0;
  cur_write_size = write_size;
  while (cur_file_size < file_size)
  {
    remaining_size = file_size - cur_file_size;
    cur_write_size += write_size_incr;
    if (cur_write_size > remaining_size)
    {
      cur_write_size = remaining_size;
    }

    cur_buf = &file_buf[cur_file_size];
    result = rfs_write (fd, cur_buf, cur_write_size);
    if (result != cur_write_size)
    {
      RFS_MSG_STRING_1 ("%d, rfs_write failed", result);
      goto Error;
    }

    cur_file_size += cur_write_size;
  }

  result = 0;
  goto End;

Error:
result = -1;

End:
  if (fd >= 0)
  {
    (void) rfs_close (fd);
  }

  return result;
}
