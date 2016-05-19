/***********************************************************************
 * rfs_config_i.h
 *
 * Remote File System - Internal Configuration file.
 * Copyright (C) 2013 QUALCOMM Technologies, Inc.
 *
 * Internal Configuration file for the Remote File System module.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/inc/rfs_config_i.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2013-11-14   rp    Create

===========================================================================*/

#ifndef __RFS_CONFIG_I_H__
#define __RFS_CONFIG_I_H__

#include "rfs_config.h"

/**
  Maximum number of files that can be kept open simultaneously. Targets can
  override this value but bear in mind that the descriptor is a heavy
  data structure and based on RFS_PATH_MAX can increase RAM usage heavily.
*/
#ifndef RFS_MAX_FILE_DESCRIPTORS
  #define RFS_MAX_FILE_DESCRIPTORS (128)
#endif

#endif /* not __RFS_CONFIG_I_H__ */
