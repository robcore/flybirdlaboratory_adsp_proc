#ifndef __CVD_VFR_API_H__
#define __CVD_VFR_API_H__

/*
   Copyright (C) 2014 QUALCOMM Technologies Incorporated.
   All rights reserved.
   Qualcomm Confidential and Proprietary

   $Header: //components/rel/avs.adsp/2.6.1/vsd/inc/private/cvd_vfr_api.h#3 $
   $Author: svutukur $
*/

#include "apr_comdef.h"
#include "drv_api.h"

APR_EXTERNAL int32_t cvd_vfr_call (
  uint32_t cmd_id,
  void* params,
  uint32_t size
);

#endif /* __CVD_VFR_API_H__ */

