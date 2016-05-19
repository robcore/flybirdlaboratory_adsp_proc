/* ======================================================================== */
/**
@file appi_buf.h

   Header file to implement the Audio Post Processor Interface for 
   locally buffering input signal before sending out
*/

/* =========================================================================
  Copyright (c) 2010 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================== */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   11/04/10   ss      APPI wrapper
   ========================================================================= */

/*------------------------------------------------------------------------
 * Include files
 * -----------------------------------------------------------------------*/
#ifndef __APPI_BUF_H__
#define __APPI_BUF_H__

#include "Elite_APPI.h"
#include "buf.h"

#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

// No associated tuning parameters for this module, This module once included
// is always assumed to be enabled

/*------------------------------------------------------------------------
 * Function declarations
 * -----------------------------------------------------------------------*/
ADSPResult appi_buf_getsize(
      const appi_buf_t* params_ptr,
      uint32_t* size_ptr);

ADSPResult appi_buf_init( 
      appi_t*              _pif,
      bool_t*              is_inplace_ptr,
      const appi_format_t* in_format_ptr,
      appi_format_t*       out_format_ptr,
      appi_buf_t*          info_ptr);

#ifdef __cplusplus
}
#endif

#endif //__APPI_BUF_H__

