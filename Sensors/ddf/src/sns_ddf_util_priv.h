/** 
 * @file sns_ddf_util_priv.h 
 * @brief private header for DDF util.
 *  
 * Copyright (c) 2014 by Qualcomm Technologies, Inc. 
 * All Rights Reserved Qualcomm Technologies Proprietary and 
 * Confidential 
 *
 */

/*==============================================================================
  Edit History

  This section contains comments describing changes made to the module. Notice
  that changes are listed in reverse chronological order. Please use ISO format
  for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/ddf/src/sns_ddf_util_priv.h#1 $
  $DateTime: 2014/12/12 18:16:56 $

  when       who  what, where, why 
  ---------- ---  -----------------------------------------------------------
  2014-01-12 MW   Initial revision
==============================================================================*/

#ifndef SNS_DDF_UTIL_PRIV_H
#define SNS_DDF_UTIL_PRIV_H

#include "sns_ddf_util.h"
#include "sns_ddf_common.h"
#include "sns_ddf_driver_if.h"
#include "sns_em.h"
#include "sns_ddf_smgr_if.h"
#include "sns_memmgr.h"
#include "sns_debug_api.h"
#include "sns_profiling.h"
#if !defined(SNS_PCSIM) && !defined(QDSP6)
#include "DALSys.h"
#endif

typedef struct sns_ddf_timer_obj_s
{
    sns_ddf_driver_if_s*  dd_interface; /**< Functions of the calling driver. */
    sns_ddf_handle_t      dd_handle;    /**< Instance of the calling driver. */
    void*                 arg;          /**< Argument for the handler fn. */
    sns_em_timer_obj_t    em_timer;     /**< Timer service object. */
    bool                  is_uimg_refac;
} sns_ddf_timer_obj_s;


#endif //SNS_DDF_UTIL_PRIV_H
