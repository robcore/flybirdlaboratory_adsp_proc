/***********************************************************************
 * rfs_msg.h
 *
 * Message Macros to printf RFS module messages.
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * Message Macros to printf RFS module messages.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_msg.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-08-04   rp    Create

===========================================================================*/

#ifndef __RFS_MSG_H__
#define __RFS_MSG_H__


#include "rfs_config_i.h"
#include "msg.h"

#define RFS_MSG_STRING_1(a,b) \
        MSG_SPRINTF_1(MSG_SSID_RFS_ACCESS,MSG_LEGACY_HIGH,a,b)


#endif /* not __RFS_MSG_H__ */
