/***********************************************************************
 * rfs_efs.h
 *
 * RFS wrapper for EFS
 * Copyright (C) 2013 QUALCOMM Technologies, Inc.
 *
 * APIs to hook up EFS Filesystem under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_efs.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2013-11-14   dks   Create

===========================================================================*/

#ifndef __RFS_EFS_H__
#define __RFS_EFS_H__

#ifdef FEATURE_RFS_USE_EFS

int rfs_efs_init (void);

#endif

#endif /* not __RFS_EFS_H__ */
