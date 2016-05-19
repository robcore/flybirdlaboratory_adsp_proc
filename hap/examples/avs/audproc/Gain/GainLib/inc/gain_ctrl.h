/* ======================================================================== */
/**
@file gain_ctrl.h

   Header file to implement the Audio Post Processor Interface for 
   applying gain to input signal
*/

/* =========================================================================
  Copyright (c) 2012 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================= */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   06/12/13   DS	  Updated to support floating point processing
   06/12/12	  DS	  Updated to support both 16-bit and 24-bit (in 32-bit 
					  data width)processing
   11/04/10   ss      Utils for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files 
 * -----------------------------------------------------------------------*/
#ifndef __GAIN_CTRL_H__
#define __GAIN_CTRL_H__

#include "appi_util.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Function declarations
 * -----------------------------------------------------------------------*/
void gain_16bits(int16_t* lin_ptr16,
      int16_t* rin_ptr16,
      int16_t* lout_ptr16,
      int16_t* rout_ptr16,
      uint32_t gain,
      uint32_t num_channels,
      uint32_t num_samples);

void gain_32bits(int32_t* lin_ptr32,
      int32_t* rin_ptr32,
      int32_t* lout_ptr32,
      int32_t* rout_ptr32,
      uint32_t gain,
      uint32_t num_channels,
      uint32_t num_samples);

void gain_float(int16_t* lin,
	  int16_t* rin,
	  int16_t* lout,
	  int16_t* rout,
	  float float_gain,
	  uint32_t num_channels,
	  uint32_t num_samples);

#endif //__GAIN_CTRL_H__
