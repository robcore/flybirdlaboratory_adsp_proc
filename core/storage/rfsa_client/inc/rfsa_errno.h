/******************************************************************************
 * rfs_errno.h
 *
 * ERROR CODES for remote file system access
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/inc/rfsa_errno.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
2014-02-20   nr      Create.
=============================================================================*/

#ifndef __RFSA_ERRNO_H__
#define __RFSA_ERRNO_H__

#include <errno.h>

#define RFSA_EOK                        0

#define RFSA_SERVER_OBJECT_NOT_FOUND   (-2001)

#define RFSA_INIT_FAILED               (-2002)

#define RFSA_INSTANCE_NOT_FOUND        (-2003)

#define RFSA_QMI_SEND_MSG_FAILED       (-2004)

#define RFSA_QMI_SERVER_DOWN           (-2005)

#define RFSA_GET_SHARED_BUFFER_ERROR   (-2006)

#define RFSA_SHARED_BUFFER_ERANGE      (-2007)

#define RFSA_MMAP_FAILED               (-2008)

#define RFSA_STAT_FAILED               (-2009)

#define RFSA_FILE_CREATE_FAILED        (-2010)

#define RFSA_READ_FAILED               (-2011)

#define RFSA_WRITE_FAILED              (-2012)


#define RFSA_ENAMETOOLONG              (-3001)


#define RFSA_EFAILED                   (-4001)

#endif /* __RFSA_ERRNO_H__ */
