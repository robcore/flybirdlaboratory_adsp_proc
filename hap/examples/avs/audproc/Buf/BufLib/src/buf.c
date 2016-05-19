/* ======================================================================== */
/**
@file buf.c

   Source file to implement the Audio Post Processor Interface for 
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
#include "buf.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
  Function name: buffer_process
  This function processes a buffer of a specific size alg_process_size.
 * -----------------------------------------------------------------------*/
void buffer_process(int16_t* lin_ptr, 
      int16_t* rin_ptr,
      int16_t* lout_ptr,
      int16_t* rout_ptr,
      uint32_t num_channels)
{
   memcpy(lout_ptr, lin_ptr, alg_process_size*sizeof(int16_t));

   if (2 == num_channels)
   {
      memcpy(rout_ptr, rin_ptr, alg_process_size*sizeof(int16_t));
   }
}

