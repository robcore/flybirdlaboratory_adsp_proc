/******************************************************************************
 * rfsa_qmi_core.h
 *
 * QMI core interface functions for Remote File System Access
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_qmi_core.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-02-20   nr      Create.
=============================================================================*/

#ifndef __RFSA_QMI_CORE_H__
#define __RFSA_QMI_CORE_H__

#include "comdef.h"
#include "remote_filesystem_access_v01.h"
#include "qmi_client.h"

#define RFSA_QMI_WAIT_FOREVER 0

int32 rfsa_qmi_core_connect_userspace (qmi_client_type *handle,
                                       uint32_t timeout);

int32 rfsa_qmi_core_connect_kernel (qmi_client_type *handle);

void rfsa_qmi_core_disconnect (qmi_client_type *handle);

int32 rfsa_qmi_core_stat (qmi_client_type *handle,
                          rfsa_file_stat_req_msg_v01 *file_stat_req,
                          rfsa_file_stat_resp_msg_v01 *file_stat_resp);

int32 rfsa_qmi_core_fcreate (qmi_client_type *handle,
                             rfsa_file_create_req_msg_v01 *file_create_req,
                             rfsa_file_create_resp_msg_v01 *file_create_resp);

int32 rfsa_qmi_core_read (qmi_client_type *handle,
                          rfsa_file_read_req_msg_v01 *file_read_req,
                          rfsa_file_read_resp_msg_v01 *file_read_resp);

int32 rfsa_core_get_buff_addr (qmi_client_type *handle,
                               rfsa_get_buff_addr_req_msg_v01 *get_buff_req,
                               rfsa_get_buff_addr_resp_msg_v01 *get_buff_resp);

int32 rfsa_core_read_iovec (qmi_client_type *handle,
                           rfsa_iovec_file_read_req_msg_v01 *read_iovec_req,
                           rfsa_iovec_file_read_resp_msg_v01 *read_iovec_resp);

int32 rfsa_core_write_iovec (qmi_client_type *handle,
                         rfsa_iovec_file_write_req_msg_v01 *iovec_write_req,
                         rfsa_iovec_file_write_resp_msg_v01 *iovec_write_resp);

#endif /* __RFSA_QMI_CORE_H__ */

