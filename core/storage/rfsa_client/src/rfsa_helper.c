/******************************************************************************
 * rfsa_helper.c
 *
 * Helper functions for rfsa client.
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_helper.c#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-06-13   dks     XPU lock RFSA buffer with its own slot.
2014-02-20   nr      Create.
=============================================================================*/

#include "stringl.h"
#include "err.h"
#ifdef FEATURE_RFSA_MPSS_XPU_LOCK
  #include "mba_ac.h"
#endif

#include "rfsa_helper.h"
#include "rfsa_qmi_core.h"
#include "rfsa_errno.h"
#include "rfsa_config.h"
#include "rfsa_log.h"
#include "rfsa_memory.h"
#include "rfsa_lock.h"

#define SERVER_RECONNECT_TIMEOUT_MS 2000

struct rfsa_helper_info
{
  uint8 core_init_complete;
  rfsa_mutex_handle shared_buffer_mutex;
  rfsa_mutex_handle qmi_core_lock;
  qmi_client_type server;
  qmi_client_type kernel;
  uint8 is_server_handle_valid;
  uint8 is_kernel_handle_valid;
  uint64 shared_buffer_physical;
  uint32 shared_buffer_virtual;
  uint32 buffer_size;
  void *shared_buffer;
};

static struct rfsa_helper_info rfsa_info = {0};

static int32
connect_userspace (uint32_t timeout)
{
  int32 result;

  if (1 == rfsa_info.is_server_handle_valid)
    return RFSA_EOK;

  result = rfsa_qmi_core_connect_userspace (&rfsa_info.server, timeout);
  if (result == RFSA_EOK)
  {
    LOGH("Reconnection successful");
    rfsa_info.is_server_handle_valid = 1;
  }
  else
  {
    LOGH("Reconnection unsuccessful");
  }

  return result;
}

static int32
reconnect_userspace (void)
{
  LOGH("Server down. Attempting to reconnect");
  rfsa_info.is_server_handle_valid = 0;
  rfsa_qmi_core_disconnect (&rfsa_info.server);
  return connect_userspace(SERVER_RECONNECT_TIMEOUT_MS);
}

static int32
rfsa_init_qmi_helper (void)
{
  int32 result;

  result = rfsa_qmi_core_connect_userspace (&rfsa_info.server,
                                            RFSA_QMI_WAIT_FOREVER);
  if (result != RFSA_EOK)
  {
    rfsa_info.is_server_handle_valid = 0;
    return result;
  }
  rfsa_info.is_server_handle_valid = 1;

  result = rfsa_qmi_core_connect_kernel (&rfsa_info.kernel);
  if (result == RFSA_EOK)
  {
    rfsa_info.is_kernel_handle_valid = 1;
  }
  else if (result == RFSA_INSTANCE_NOT_FOUND)
  {
    rfsa_info.is_kernel_handle_valid = 0;
    result = RFSA_EOK;
  }

  return result;
}

static void
rfsa_xpu_lock_shared_memory (uint64 start_addr, uint64 end_addr)
{
#ifdef FEATURE_RFSA_MPSS_XPU_LOCK
  if (mba_xpu_lock_region(start_addr, end_addr, MBA_XPU_PARTITION_MODEM_RFSA))
  {
    ERR_FATAL ("xpu lock failed %d %d",
               (uint32) start_addr, (uint32) end_addr, 0);
  }

  LOGH2 ("xpu-lock success %d %d", (uint32)start_addr, (uint32) end_addr);
#endif
}


static int32
rfsa_map_physical_to_virtual (void)
{
  int32 result;
  void *virtual_addr = NULL;

  result = rfsa_mmap (rfsa_info.shared_buffer_physical, rfsa_info.buffer_size,
                      &virtual_addr);
  if (result == RFSA_EOK)
  {
    rfsa_info.shared_buffer = virtual_addr;
    rfsa_info.shared_buffer_virtual = (uint32) virtual_addr;
  }
  return result;
}

static int32
rfsa_setup_shared_buffer (void)
{
  int32 result, remote_error;
  uint64 shared_address_response;
  qmi_client_type *buffer_server;
  rfsa_get_buff_addr_req_msg_v01 get_buff_addr_req;
  rfsa_get_buff_addr_resp_msg_v01 get_buff_addr_resp;
  uint64 end_addr;

  memset (&get_buff_addr_req, 0, sizeof (get_buff_addr_req));
  memset (&get_buff_addr_resp, 0, sizeof (get_buff_addr_resp));

  if (rfsa_info.is_kernel_handle_valid == 1)
  {
    buffer_server = &rfsa_info.kernel;
  }
  else
  {
    buffer_server = &rfsa_info.server;
  }

  get_buff_addr_req.size = RFSA_SHARED_BUFFER_SIZE;
  get_buff_addr_resp.resp.result = QMI_RESULT_FAILURE_V01;

  result = rfsa_core_get_buff_addr (buffer_server, &get_buff_addr_req,
                                    &get_buff_addr_resp);
  if (result != RFSA_EOK)
  {
    return result;
  }
  if ((get_buff_addr_resp.resp.result != QMI_RESULT_SUCCESS_V01) ||
      (get_buff_addr_resp.address_valid != 1))
  {
    remote_error = get_buff_addr_resp.resp.error;
    LOGE1("get_buff_addr_resp.resp.error %d!\n", remote_error);
    return RFSA_GET_SHARED_BUFFER_ERROR;
  }
  shared_address_response = get_buff_addr_resp.address;

  if (shared_address_response == 0)
  {
    return RFSA_SHARED_BUFFER_ERANGE;
  }

  rfsa_info.shared_buffer_physical = shared_address_response;
  rfsa_info.buffer_size = RFSA_SHARED_BUFFER_SIZE;
  end_addr = rfsa_info.shared_buffer_physical + rfsa_info.buffer_size - 1;
  rfsa_xpu_lock_shared_memory (rfsa_info.shared_buffer_physical, end_addr);
  result = rfsa_map_physical_to_virtual ();
  return result;
}

int32
rfsa_init_helper (void)
{
  int32 result, ret_val;

  if (rfsa_info.core_init_complete == 1)
  {
    return RFSA_EOK;
  }

  result = rfsa_thread_mutex_init (&rfsa_info.shared_buffer_mutex);
  if (result != 0)
  {
    LOGE1("rfsa_thread_mutex_init error %d!\n", -result);
    return -result;
  }
  result = rfsa_thread_mutex_init (&rfsa_info.qmi_core_lock);
  if (result != 0)
  {
    LOGE1("rfsa_thread_mutex_init error %d!\n", -result);
    return -result;
  }

  result = rfsa_thread_lock (&rfsa_info.shared_buffer_mutex);
  if (result != 0)
  {
    LOGE1("rfsa_thread_lock error %d!\n", -result);
    return -result;
  }

  result = rfsa_init_qmi_helper ();
  if (result != RFSA_EOK)
  {
    LOGE1("rfsa init error %d!\n", result);
    ret_val = result;
    goto End;
  }

  result = rfsa_setup_shared_buffer ();
  if (result != RFSA_EOK)
  {
    LOGE1("rfsa init error %d!\n", result);
    ret_val = result;
    goto End;
  }

  rfsa_info.core_init_complete = 1;
  ret_val = RFSA_EOK;

End:
  result = rfsa_thread_unlock (&rfsa_info.shared_buffer_mutex);
  if (result != 0)
  {
    LOGE1("rfsa_thread_unlock error %d!\n", -result);
  }
  return ret_val;
}

int32
rfsa_stat_helper (const char *filename, struct rfsa_stat *buf)
{
  int32 result, remote_error;
  rfsa_file_stat_req_msg_v01 file_stat_req;
  rfsa_file_stat_resp_msg_v01 file_stat_resp;

  (void)rfsa_thread_lock (&rfsa_info.qmi_core_lock);

  if ((result = connect_userspace(SERVER_RECONNECT_TIMEOUT_MS)) != RFSA_EOK)
  {
    LOGE("Could not reconnect to server");
    goto End;
  }

  memset (&file_stat_req, 0, sizeof (file_stat_req));
  memset (&file_stat_resp, 0, sizeof (file_stat_resp));

  memset (buf, 0, sizeof (*buf));
  result = strlcpy (file_stat_req.filename, filename, RFSA_MAX_FILE_PATH_V01);
  if (result >= RFSA_MAX_FILE_PATH_V01)
  {
    LOGE("Filename too long!");
    result = RFSA_ENAMETOOLONG;
    goto End;
  }

  file_stat_resp.resp.result = QMI_RESULT_FAILURE_V01;

  result = rfsa_qmi_core_stat (&rfsa_info.server, &file_stat_req,
                               &file_stat_resp);
  if (RFSA_QMI_SERVER_DOWN == result)
  {
    if ((result = reconnect_userspace()) == RFSA_EOK)
    {
      LOGH("Reconnected. Re-sending original request");
      result = rfsa_qmi_core_stat (&rfsa_info.server, &file_stat_req,
                                   &file_stat_resp);
    }
  }

  if (result != RFSA_EOK)
  {
    LOGE1("rfsa_qmi_core_stat error %d!\n", result);
    goto End;
  }

  if (file_stat_resp.resp.result != QMI_RESULT_SUCCESS_V01)
  {
    remote_error = file_stat_resp.resp.error;
    LOGE1("file_stat_resp.resp.error %d!\n", remote_error);
    result = RFSA_GET_SHARED_BUFFER_ERROR;
    goto End;
  }

  buf->flags = file_stat_resp.flags;
  buf->is_file_size_valid = file_stat_resp.size_valid;
  buf->file_size = file_stat_resp.size;
  result = RFSA_EOK;

End:
  (void)rfsa_thread_unlock (&rfsa_info.qmi_core_lock);
  return result;
}


int32
rfsa_create_file_helper (const char *filename, uint64 flags)
{
  int32 result, remote_error;
  rfsa_file_create_req_msg_v01 file_creat_req;
  rfsa_file_create_resp_msg_v01 file_creat_resp;

  (void)rfsa_thread_lock (&rfsa_info.qmi_core_lock);

  if ((result = connect_userspace(SERVER_RECONNECT_TIMEOUT_MS)) != RFSA_EOK)
  {
    LOGE("Could not reconnect to server");
    goto End;
  }

  memset (&file_creat_req, 0, sizeof (file_creat_req));
  memset (&file_creat_resp, 0, sizeof (file_creat_resp));

  result = strlcpy (file_creat_req.filename, filename, RFSA_MAX_FILE_PATH_V01);
  if (result >= RFSA_MAX_FILE_PATH_V01)
  {
    LOGE("Filename too long!");
    result = RFSA_ENAMETOOLONG;
    goto End;
  }
  file_creat_req.flags = flags;

  file_creat_resp.resp.result = QMI_RESULT_FAILURE_V01;
  LOGD("Calling rfsa_qmi_core_fcreate");
  result = rfsa_qmi_core_fcreate (&rfsa_info.server, &file_creat_req,
                                  &file_creat_resp);
  if (RFSA_QMI_SERVER_DOWN == result)
  {
    if ((result = reconnect_userspace()) == RFSA_EOK)
    {
      LOGH("Reconnected. Re-sending original request");
      result = rfsa_qmi_core_fcreate (&rfsa_info.server, &file_creat_req,
                                      &file_creat_resp);
    }
  }

  if (result != RFSA_EOK)
  {
    LOGE1("rfsa_qmi_core_fcreate error %d!\n", result);
    goto End;
  }

  if (file_creat_resp.resp.result != QMI_RESULT_SUCCESS_V01)
  {
    remote_error = file_creat_resp.resp.error;
    LOGE1("file_creat_resp.resp.error %d!\n", remote_error);
    result = RFSA_FILE_CREATE_FAILED;
    goto End;
  }
  result = RFSA_EOK;

End:
  (void)rfsa_thread_unlock (&rfsa_info.qmi_core_lock);
  return result;
}

int32
rfsa_read_helper (const char *filename, uint32 offset, void *buffer,
                  uint32 buf_size)
{
  int32 result, remote_error, read_size, ret_val;
  rfsa_file_read_req_msg_v01  file_read_req;
  rfsa_file_read_resp_msg_v01 file_read_resp;

  (void)rfsa_thread_lock (&rfsa_info.qmi_core_lock);
  (void)rfsa_thread_lock (&rfsa_info.shared_buffer_mutex);

  if ((result = connect_userspace(SERVER_RECONNECT_TIMEOUT_MS)) != RFSA_EOK)
  {
    LOGE("Could not reconnect to server");
    ret_val = result;
    goto End;
  }

  memset (&file_read_req, 0, sizeof (file_read_req));
  memset (&file_read_resp, 0, sizeof (file_read_resp));

  result = strlcpy (file_read_req.filename, filename, RFSA_MAX_FILE_PATH_V01);
  if (result >= RFSA_MAX_FILE_PATH_V01)
  {
    LOGE("Filename too long!");
    ret_val = RFSA_ENAMETOOLONG;
    goto End;
  }
  file_read_req.size = buf_size;

  if (file_read_req.size > rfsa_info.buffer_size)
  {
    file_read_req.size = rfsa_info.buffer_size;
  }
  file_read_req.offset = offset;

  file_read_resp.resp.result = QMI_RESULT_FAILURE_V01;

  ret_val = RFSA_READ_FAILED;

  result = rfsa_qmi_core_read (&rfsa_info.server, &file_read_req,
                               &file_read_resp);
  if (RFSA_QMI_SERVER_DOWN == result)
  {
    if ((result = reconnect_userspace()) == RFSA_EOK)
    {
      LOGH("Reconnected. Re-sending original request");
      result = rfsa_qmi_core_read (&rfsa_info.server, &file_read_req,
                                   &file_read_resp);
    }
  }

  if (result != RFSA_EOK)
  {
    LOGE1("rfsa_qmi_core_read error %d!\n", result);
    ret_val = result;
    goto End;
  }

  if ((file_read_resp.resp.result != QMI_RESULT_SUCCESS_V01) ||
      (file_read_resp.data_valid != 1))
  {
    remote_error = file_read_resp.resp.error;
    LOGE1("file_read_resp.resp.error %d!\n", remote_error);
    LOGE1("file_read_resp.data_valid = %d!\n", file_read_resp.data_valid);
  }
  else
  {
    read_size = file_read_resp.data.count;
    memcpy (buffer, rfsa_info.shared_buffer, read_size);
    ret_val = read_size;
  }

End:
  (void)rfsa_thread_unlock (&rfsa_info.shared_buffer_mutex);
  (void)rfsa_thread_unlock (&rfsa_info.qmi_core_lock);
  return ret_val;
}

int32
rfsa_write_helper (const char *filename, uint32 offset, void *buffer,
                   uint32 buf_size)
{
  int32 result, remote_error, ret_val;
  uint32 write_size;
  rfsa_iovec_file_write_req_msg_v01  write_iovec_req;
  rfsa_iovec_file_write_resp_msg_v01 write_iovec_resp;
  rfsa_iovec_desc_type_v01 *iovec;

  (void)rfsa_thread_lock (&rfsa_info.qmi_core_lock);
  (void)rfsa_thread_lock (&rfsa_info.shared_buffer_mutex);

  if ((result = connect_userspace(SERVER_RECONNECT_TIMEOUT_MS)) != RFSA_EOK)
  {
    LOGE("Could not reconnect to server");
    ret_val = result;
    goto End;
  }

  memset (&write_iovec_req, 0, sizeof (write_iovec_req));
  memset (&write_iovec_resp, 0, sizeof (write_iovec_resp));

  result = strlcpy (write_iovec_req.filename, filename, RFSA_MAX_FILE_PATH_V01);
  if (result >= RFSA_MAX_FILE_PATH_V01)
  {
    LOGE("Filename too long!");
    ret_val = RFSA_ENAMETOOLONG;
    goto End;
  }

  write_iovec_req.iovec_struct_len = 1;
  iovec = &write_iovec_req.iovec_struct[0];

  write_size = buf_size;
  if (write_size > rfsa_info.buffer_size)
  {
    write_size = rfsa_info.buffer_size;
  }

  ret_val = RFSA_WRITE_FAILED;

  memcpy (rfsa_info.shared_buffer, buffer, write_size);

  iovec->file_offset = offset;
  iovec->buff_addr_offset = 0;
  iovec->size = write_size;

  write_iovec_resp.resp.result = QMI_RESULT_FAILURE_V01;
  result = rfsa_core_write_iovec (&rfsa_info.server, &write_iovec_req,
                                  &write_iovec_resp);
  if (RFSA_QMI_SERVER_DOWN == result)
  {
    if ((result = reconnect_userspace()) == RFSA_EOK)
    {
      LOGH("Reconnected. Re-sending original request");
      result = rfsa_core_write_iovec (&rfsa_info.server, &write_iovec_req,
                                      &write_iovec_resp);
    }
  }

  if (result != RFSA_EOK)
  {
    LOGE1("rfsa_core_write_iovec error %d!\n", result);
    ret_val = result;
    goto End;
  }

  if (write_iovec_resp.resp.result != QMI_RESULT_SUCCESS_V01)
  {
    remote_error = write_iovec_resp.resp.error;
    LOGE1("file_read_resp.resp.error %d!\n", remote_error);
    ret_val = RFSA_WRITE_FAILED;
  }
  else
  {
    ret_val = write_size;
  }

End:
  (void)rfsa_thread_unlock (&rfsa_info.shared_buffer_mutex);
  (void)rfsa_thread_unlock (&rfsa_info.qmi_core_lock);
  return ret_val;
}

