/***********************************************************************
 * rfs_fcntl.h
 *
 * Posix File control options for RFS APIs
 * Copyright (C) 2013 QUALCOMM Technologies, Inc.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/api/storage/rfs_fcntl.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2013-11-07   dks   Create

===========================================================================*/

#ifndef __RFS_FCNTL_H__
#define __RFS_FCNTL_H__

#define RFS_O_RDONLY       0001
#define RFS_O_WRONLY       0002
#define RFS_O_RDWR         0004
#define RFS_O_CREAT        0010
#define RFS_O_TRUNC        0020
#define RFS_O_APPEND       0040
#define RFS_O_ENCRYPT      0100
#define RFS_O_COMPRESS     0200

#define RFS_SEEK_SET          0       /**< Seek from beginning of file.  */
#define RFS_SEEK_CUR          1       /**< Seek from current position.  */
#define RFS_SEEK_END          2       /**< Seek from end of file.  */

#endif /* not __RFS_FCNTL_H__ */
