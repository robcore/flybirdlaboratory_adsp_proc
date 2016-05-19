/***********************************************************************
 * rfs_rfsa.h
 *
 * RFS wrapper for RFS_ACCESS
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * APIs to hook up RFS_ACCESS APIs under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_rfsa.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-04-02   dks   Create

===========================================================================*/

#ifndef __RFS_RFSA_H__
#define __RFS_RFSA_H__

#ifdef FEATURE_RFS_USE_RFSA

int rfs_rfsa_init (void);

#endif

#endif /* not __RFS_RFSA_H__ */
