/*==============================================================================
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All rights reserved.
  Proprietary and Confidential - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S.
  Government. Diversion contrary to U.S. law prohibited. 
==============================================================================*/
#ifndef ELITE_CAPI_NEW_H
#define ELITE_CAPI_NEW_H

/* ========================================================================*/
/**
@file Elite_CAPI_new.h
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Elite_CAPI_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   10/17/14   sw      (Tech Pubs) Edited Doxgen markup and comments for 2.6.
========================================================================= */

#include "mmdefs.h"
#include "adsp_error_codes.h"
#include "Elite_CAPI.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/** @addtogroup capi_c_wrappers
@{ */
/**
  Gets the memory requirement of the library.
  Optional input parameters can be sent to the CAPI wrapper to calculate
  worst case memory requirements.

  @param[in]  format    Format of the input buffer.
  @param[in]  bps       Bytes per sample.
  @param[out] size_ptr  Pointer to the number of bytes of memory being
                        requested.

  @return
  Indication of success or failure.

  @dependencies
  None.
*/
typedef ADSPResult(* capi_getsize_f)(int32_t format, uint32_t bps,
                                     uint32_t* size_ptr);

/**
  Called to instantiate the library to set up the virtual function table, and
  also to allocate any memory required by the library. States within the
  library must be initialized at the same time.
  If the algorithm does not support a specific data format, an error code is
  to be returned. 

  Input parameters are sent to the APPI wrapper.

  @param[in]  capi_ptr  Pointer to the library object.
  @param[in]  format    ID of the media format.
  @param[out] bps       Bytes per sample.

  @return
  Indication of success or failure.

  @dependencies
  The appi_getsize_f() function (refer to @xhyperref{Q3,[Q3]}) must have been
  executed, and any memory requested must have been allocated.
*/
typedef ADSPResult(* capi_ctor_f)(ICAPI* capi_ptr, uint32_t format,
                                  uint32_t bps);

/** @} */ /* end_addtogroup capi_c_wrappers */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ELITE_CAPI_NEW_H
