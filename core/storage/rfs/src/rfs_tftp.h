/***********************************************************************
 * rfs_tftp.h
 *
 * RFS wrapper on top of TFTP.
 * Copyright (C) 2013 QUALCOMM Technologies, Inc.
 *
 * APIs to hook up TFTP APIs under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_tftp.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2013-11-12   dks   Create

===========================================================================*/

#ifndef __RFS_TFTP_H__
#define __RFS_TFTP_H__

#ifdef FEATURE_RFS_USE_TFTP

int rfs_tftp_init (void);

#endif

#endif /* not __RFS_TFTP_H__ */
