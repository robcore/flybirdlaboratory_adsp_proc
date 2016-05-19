/***********************************************************************
 * rfs_rmts.h
 *
 * RFS wrapper for Remote Storage Server
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * APIs to hook up Remote Storage Server APIs under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_rmts.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-01-24   dks   Create

===========================================================================*/

#ifndef __RFS_RMTS_H__
#define __RFS_RMTS_H__

#ifdef FEATURE_RFS_USE_RMTS

int rfs_rmts_init (void);

#endif

#endif /* not __RFS_RMTS_H__ */
