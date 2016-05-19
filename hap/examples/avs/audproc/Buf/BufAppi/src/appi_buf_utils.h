/* ======================================================================== */
/**
@file appi_buf_utils.h

   Utils header file to implement the Audio Post Processor Interface for 
   locally buffering input signal before sending out
*/

/* =========================================================================
  Copyright (c) 2011 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================= */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   11/04/10   ss      Utils for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files 
 * -----------------------------------------------------------------------*/
#ifndef __APPI_BUF_UTILS_H__
#define __APPI_BUF_UTILS_H__

#include "appi_buf.h"
#include "appi_util.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/
typedef struct
{
   const appi_vtbl_t* vtbl;
   uint32_t           num_channels;
   int16_t            *local_in_buf_ptr;        // Input Data is processed locally in 
                                                // chunks of alg_buffer_size internally 
   uint32_t           samples_in_local_in_buf;  // This number indicates the input number 
                                                // of samples unprocessed (from previous iteration)
   int16_t            *local_out_buf_ptr;       // Output Data is readied locally in 
                                                // chunks of alg_buffer_size internally 
   uint32_t           samples_in_local_out_buf; // This number indicates the output number 
                                                // of samples not yet sent (from previous iteration)
} appi_buf_struct;

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Function declarations
 * -----------------------------------------------------------------------*/

#endif //__APPI_BUF_UTILS_H__
