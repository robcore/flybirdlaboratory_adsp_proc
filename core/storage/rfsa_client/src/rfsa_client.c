/******************************************************************************
 * rfsa_client.c
 *
 * Remote File System Access, client API implementations
 *
 * Copyright (c) 2012-2014
 * Qualcomm Technology Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_client.c#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-08-12   dks     Fix seek behavior for SEEK_END.
2014-04-20   ab      Featurize code compilation.
2014-02-20   nr      Add support for dynamic shared buffer and clean-up.
2013-02-25   rh      Replace strncpy with strlcpy
2013-02-14   rh      Make call to qmi_init non blocking
2012-11-28   rh      Add call to deinit routine to the QMI layer
2012-10-11   rh      Adding opening file with checking on server side
2012-02-22   rh      Initial checkin
=============================================================================*/

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stringl.h>

#include "rfsa_errno.h"
#include "rfsa_log.h"
#include "rfsa_client.h"
#include "rfsa_helper.h"
#include "rfsa_lock.h"
#include "rfsa_config.h"

#include "remote_filesystem_access_v01.h"


/*****************************************************************************
* Defines                                                                   *
****************************************************************************/

#define RFSA_MAX_OPEN_FILES          64
#define RFSA_UINT32_MAX              0xFFFFFFFF
/*****************************************************************************
* Definitions                                                               *
****************************************************************************/

typedef struct rfsa_info_client
{
  char        filename[RFSA_MAX_FILE_PATH_V01];
  int         open;
  uint32      pos;
  int         flags;
} rfsa_info_t;

/*****************************************************************************
* Variables                                                                 *
****************************************************************************/
static uint8_t rfsa_client_init_done = 0;
static rfsa_info_t rfsa_open_files[RFSA_MAX_OPEN_FILES];
static rfsa_mutex_handle rfsa_client_lock;
static rfsa_mutex_handle rfsa_init_lock;

/*****************************************************************************
* Implementations                                                           *
****************************************************************************/

void rfsa_client_rc_init(void)
{
  memset(rfsa_open_files, 0, sizeof(rfsa_open_files));
  (void)rfsa_thread_mutex_init (&rfsa_client_lock);
  (void)rfsa_thread_mutex_init (&rfsa_init_lock);
}

int
rfsa_client_init(void)
{
  int32_t result = 0;

  (void)rfsa_thread_lock (&rfsa_init_lock);

  if(rfsa_client_init_done)
  {
    goto End;
  }

  result = rfsa_init_helper ();
  if (result != 0)
  {
    result = -1;
  }
  else
  {
    rfsa_client_init_done = 1;
  }

End:
  (void)rfsa_thread_unlock (&rfsa_init_lock);
  return result;
}


int
rfsa_client_deinit(void)
{
  rfsa_client_init();
  return 0;
}


#ifndef RFSA_DISABLE

/* Helper functions */
static int32_t
rfsa_get_new_index_file (void)
{
  int32_t i, index = -1;

  (void)rfsa_thread_lock (&rfsa_client_lock);

  for(i = 0; i < RFSA_MAX_OPEN_FILES; i++)
  {
    if (rfsa_open_files[i].open == 0)
    {
      memset (&rfsa_open_files[i], 0, sizeof (rfsa_info_t));
      rfsa_open_files[i].open = 1;
      index = i;
      break;
    }
  }

  (void) rfsa_thread_unlock (&rfsa_client_lock);

  return index;
}

static int32_t
rfsa_check_index_file(int32_t index_file)
{
  if((index_file < 0) || (index_file >= RFSA_MAX_OPEN_FILES))
  {
    LOGE1("Invalid handle: %d", (int)index_file);
    return 0;
  }

  if(rfsa_open_files[index_file].open == 0)
  {
    LOGE1("Invalid handle: %d", (int)index_file);
    return 0;
  }

  return 1;
}

static rfsa_info_t *rfsa_get_index_file (int32_t index_file)
{
  return &(rfsa_open_files[index_file]);
}

int32_t
rfsa_open (const char *filename, int flags)
{
  int32_t index_file;
  int32_t res;
  int32_t fnlen;
  rfsa_info_t *pinfo = NULL;
  struct rfsa_stat stat_buf;

  res = rfsa_client_init ();
  if (0 != res)
    return res;

  if (filename == NULL)
  {
    LOGE("Error on rfsa_client_file_open, filename is NULL!");
    return -1;
  }

  if ((flags & O_ACCMODE) > O_RDWR)
  {
    LOGE ("Open mode not supported!");
    return -1;
  }

  // TODO: Currently the rfs_access server relies on always seeing the O_CREAT
  // flag in the create file QMI message. This is incorrect because the create
  // file QMI message is meant to be a general purpose open() check - for
  // example, if the client opens a file with O_RDONLY, rfsa_open should use
  // the create file QMI message to check if the file exists and can therefore
  // be indeed opened with O_RDONLY.
  // This comment is a reminder to evaluate such scenarios when the server
  // is upgraded to the next revision, where the requirement for FLAG_CREATE is
  // removed
  if ((flags & O_CREAT) || (flags & O_TRUNC))
  {
    uint64_t create_flags = RFSA_ACCESS_FLAG_CREATE_V01;
    if (flags & O_TRUNC)
    {
      create_flags |= RFSA_ACCESS_FLAG_TRUNC_V01;
    }

    LOGD("Calling create_file_helper");
    res = rfsa_create_file_helper (filename, create_flags);
    if (res != RFSA_EOK)
    {
      LOGE("create call failed on the server side!");
      return -1;
    }
  }
  else
  {
    // Only do pending check if the client did not set the O_NO_OPEN_CHK flag
    if (!(flags & O_NO_OPEN_CHK))
    {
      res = rfsa_stat_helper (filename, &stat_buf);

      if (res != RFSA_EOK)
      {
        LOGE("STAT call failed on the server side!");
        return -1;
      }
      if ((stat_buf.flags & RFSA_ACCESS_FLAG_READ_V01) == 0)
      {
        LOGE("File doesn't have read permissions!");
        return -1;
      }
    }
  }

  // No error in the process, get a new file index to pass back to the client
  index_file = rfsa_get_new_index_file ();
  if(index_file == -1)
  {
    LOGE("Too many open files!");
    return -1;
  }

  pinfo = rfsa_get_index_file (index_file);
  fnlen = strlcpy (pinfo->filename, filename, RFSA_MAX_FILE_PATH_V01);
  if (fnlen >= RFSA_MAX_FILE_PATH_V01)
  {
    LOGE ("Filename too long!");
    return -1;
  }
  pinfo->pos = 0;
  pinfo->flags = flags;

  return ++index_file;
}


int32_t
rfsa_close(int32_t handle)
{
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;

  if (!rfsa_check_index_file(index_file))
  {
    return EOF;
  }

  pinfo = rfsa_get_index_file (index_file);
  (void)rfsa_thread_lock (&rfsa_client_lock);
  pinfo->open = 0;
  (void)rfsa_thread_unlock (&rfsa_client_lock);

  return 0;
}


int
rfsa_seek(int32_t handle, int32_t count, int32_t way)
{
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;
  long length;
  int64 new_pos;
  int result;

  if (!rfsa_check_index_file(index_file))
  {
    return -1;
  }

  pinfo = rfsa_get_index_file (index_file);

  switch (way)
  {
    case RFSA_SEEK_SET:
      new_pos = count;
      break;

    case RFSA_SEEK_CUR:
      new_pos = (int)pinfo->pos + count;
      break;

    case RFSA_SEEK_END:
      length = rfsa_plen(pinfo->filename);
      if (length == -1)
      {
        result = -1;
        goto END;
      }
      new_pos = length + count;
      break;

    default:
      result = -1;
      goto END;
    break;
  }

  if (new_pos < 0 || new_pos > RFSA_UINT32_MAX)
  {
    result = -1;
    goto END;
  }

  pinfo->pos = new_pos;
  result = RFSA_EOK;

END:
  return result;
}


long
rfsa_plen (const char *filename)
{
  struct rfsa_stat stat_buf;
  int32_t res;
  res = rfsa_stat_helper (filename, &stat_buf);

  if (res != RFSA_EOK)
  {
    LOGE("STAT call failed on the server side!");
    return -1;
  }
  if (stat_buf.is_file_size_valid == 0)
  {
    LOGE("Invalid file size for stat!");
    return -1;
  }

  return (long)stat_buf.file_size;
}


long
rfsa_ftell (int32_t handle)
{
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;

  if(!rfsa_check_index_file (index_file))
  {
    return (long)-1;
  }

  pinfo = rfsa_get_index_file (index_file);
  return pinfo->pos;
}


long
rfsa_flen(int32_t handle)
{
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;
  int32_t res;

  res = rfsa_client_init ();
  if (0 != res)
    return res;

  if (!rfsa_check_index_file(index_file))
  {
    return (long)-1;
  }

  pinfo = rfsa_get_index_file (index_file);

  return rfsa_plen(pinfo->filename);
}

int32_t
rfsa_read(int32_t handle, char *buffer, int size)
{
  int32_t res, read_size;
  int32_t crt_pos, size_to_read;
  int32_t total_read;
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;

  if (NULL == buffer) {
    LOGD("read: NULL user supplied buffer");
    return -1;
  }

  if (0 == size) {
    LOGD("Nothing to read");
    return 0;
  }

  res = rfsa_client_init ();
  if (0 != res)
    return res;

  if (!rfsa_check_index_file(index_file))
  {
    return 0;
  }

  pinfo = rfsa_get_index_file (index_file);
  if (((pinfo->flags & O_ACCMODE) != O_RDONLY) &&
      ((pinfo->flags & O_ACCMODE) != O_RDWR))
  {
    LOGE("Invalid file permissions. Read not allowed.");
    return -1;
  }

  size_to_read = size;
  crt_pos = pinfo->pos;
  total_read = 0;

  while (size_to_read > 0)
  {
    LOGD1("rfsa_read trying to read %d\n", size_to_read);

    read_size =  rfsa_read_helper (pinfo->filename, crt_pos,
                                  (buffer + total_read), size_to_read);

    LOGD1("rfsa_read returned read_size= %d\n", read_size);
    if(read_size < 0)
    {
      LOGE("rfsa_read failed\n");
      total_read = -1;
      break;
    }
    crt_pos += read_size;
    size_to_read -= read_size;
    total_read += read_size;

    // Read terminates when the read_size is 0
    if (read_size == 0)
    {
      break;
    }
  }
  // Record the last read position
  pinfo->pos = crt_pos;

  return total_read;
}

int32_t
rfsa_write (int32_t handle, char *buffer, int size)
{
  int32_t res, write_size;
  uint32 crt_pos;
  int32_t size_to_write;
  int32_t total_write;
  int32_t index_file = handle - 1;
  rfsa_info_t *pinfo;

  if (NULL == buffer) {
    LOGD("write: NULL user supplied buffer");
    return -1;
  }

  if (0 == size) {
    LOGD("Nothing to write");
    return 0;
  }

  res = rfsa_client_init ();
  if (0 != res)
    return res;

  if (!rfsa_check_index_file(index_file))
  {
    return 0;
  }

  pinfo = rfsa_get_index_file (index_file);
  if (((pinfo->flags & O_ACCMODE) != O_WRONLY) &&
      ((pinfo->flags & O_ACCMODE) != O_RDWR))
  {
    LOGE("Invalid file permissions. Write not allowed.");
    return -1;
  }

  size_to_write = size;
  crt_pos = pinfo->pos;
  total_write = 0;

  while(size_to_write > 0)
  {
    if ((pinfo->flags & O_APPEND) == O_APPEND)
      crt_pos = UINT32_MAX;

    write_size =  rfsa_write_helper (pinfo->filename, crt_pos,
                                    (buffer + total_write), size_to_write);
    if (write_size < 0)
    {
      LOGE("rfsa_write failed\n");
      total_write = -1;
      break;
    }
    crt_pos += write_size;
    size_to_write -= write_size;
    total_write += write_size;

    // write terminates when the write_size is 0
    if (write_size == 0)
    {
      break;
    }
  }
  // Record the last write position
  pinfo->pos = crt_pos;

  return total_write;
}

#else

int32_t
rfsa_open (const char *filename, int flags)
{
  return -1;
}

int32_t
rfsa_close(int32_t handle)
{
  return -1;
}

int
rfsa_seek(int32_t handle, int32_t count, int32_t way)
{
  return -1;
}

long
rfsa_plen (const char *filename)
{
  return -1;
}

long
rfsa_ftell (int32_t handle)
{
  return -1;
}

long
rfsa_flen(int32_t handle)
{
  return -1;
}

int32_t
rfsa_read(int32_t handle, char *buffer, int size)
{
  return -1;
}

int32_t
rfsa_write (int32_t handle, char *buffer, int size)
{
  return -1;
}

#endif

