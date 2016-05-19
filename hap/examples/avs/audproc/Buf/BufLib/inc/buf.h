/* ======================================================================== */
/**
@file buf.h

   Header file to implement the Audio Post Processor Interface for 
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
#ifndef __BUF_H__
#define __BUF_H__

#include "appi_util.h"

static const uint32_t alg_process_size=80;       // In samples, process size of algorithm per channel
static const uint32_t alg_buffer_size=320;       // In bytes, internal buffer storage size 
                                                // alg_process_size * (2 channels) * (2 bytes per sample)

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Function declarations
 * -----------------------------------------------------------------------*/
void buffer_process(int16_t* lin_ptr, 
      int16_t* rin_ptr,
      int16_t* lout_ptr,
      int16_t* rout_ptr,
      uint32_t num_channels);

#endif //__BUF_H__
