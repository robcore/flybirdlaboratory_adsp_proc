/* ======================================================================== */
/**
@file gain_ctrl.c

   Source file to implement the Audio Post Processor Interface for 
   applying gain to input signal
*/

/* =========================================================================
  Copyright (c) 2013 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================= */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   06/12/13   DS	  Updated to support floating point processing
   06/12/12	  DS	  Updated to support both 16-bit and 24-bit(in 32-bit 
					  data width) processing
   11/04/10   ss      Utils for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files 
 * -----------------------------------------------------------------------*/
#include "gain_ctrl.h"
#include <hexagon_types.h>

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/


/*------------------------------------------------------------------------
  Function name: gain_16bits
  This function applies gain on 16 bit input data and generates the
  16 bit output data.
 * -----------------------------------------------------------------------*/
void gain_16bits(int16_t* lin_ptr16,
      int16_t* rin_ptr16,
      int16_t* lout_ptr16,
      int16_t* rout_ptr16,
      uint32_t gain,
      uint32_t num_channels,
      uint32_t num_samples)
{
   uint32_t i, lout_tmp32, rout_tmp32;

   if (num_channels == 2)
   {
	   // Processing for stereo channel
	   for (i=0 ; i<num_samples ; i++)
	   {
		   lout_tmp32 = Q6_R_mpy_RlRl(lin_ptr16[i], gain);
		   rout_tmp32 = Q6_R_mpy_RlRl(rin_ptr16[i], gain);
		   // gain is in Q13 format, to maintain the Q format for 
		   // right shifting by 13 bits
		   lout_ptr16[i] = lout_tmp32 >> 13; 
		   rout_ptr16[i] = rout_tmp32 >> 13;
	   }
   }
   else
   {
	   // Processing for mono channel
	   for (i=0 ; i<num_samples ; i++)
	   {
		   lout_tmp32 = Q6_R_mpy_RlRl(lin_ptr16[i], gain);
		   // gain is in Q13 format, to maintain the Q format for 
		   // right shifting by 13 bits
		   lout_ptr16[i] = lout_tmp32 >> 13; 
	   }
   }
}

/*------------------------------------------------------------------------
  Function name: gain_32bits
  This function applies gain on 32 bit input data and generates the
  32 bit output data.
 * -----------------------------------------------------------------------*/
void gain_32bits(int32_t* lin_ptr32,
      int32_t* rin_ptr32,
      int32_t* lout_ptr32,
      int32_t* rout_ptr32,
      uint32_t gain,
      uint32_t num_channels,
      uint32_t num_samples)
{
   uint32_t i;
   uint32_t gainQ28 = gain << 15; // Expects gain in Q13 format

   if (num_channels == 2)
   {
	   // Processing for stereo channel
	   for (i=0 ; i<num_samples ; i++)
	   {
		   lout_ptr32[i] = Q6_R_mpysu_RR(lin_ptr32[i], gainQ28);
		   rout_ptr32[i] = Q6_R_mpysu_RR(rin_ptr32[i], gainQ28);
		   // Q6_R_mpysu_RR right shift the o/p by 32 bits to maintain the Q format
		   // o/p need to be left shift by 4 (gainQ28 is in Q 28 format)
		   lout_ptr32[i] <<= 4; 
		   rout_ptr32[i] <<= 4;
	   }
   }
   else
   {
	   // Processing for mono channel
	   for (i=0 ; i<num_samples ; i++)
	   {
		   lout_ptr32[i] = Q6_R_mpysu_RR(lin_ptr32[i], gainQ28);
		   // Q6_R_mpysu_RR right shift the o/p by 32 bits to maintain the Q format
		   // o/p need to be left shift by 4 (gainQ28 is in Q 28 format)
		   lout_ptr32[i] <<= 4;
	   }
   }
}

/*------------------------------------------------------------------------
  Function name: gain_float
  This function applies floating point gain on coming input data and
  generates the output data.
 * -----------------------------------------------------------------------*/
void gain_float(int16_t* lin,
      int16_t* rin,
      int16_t* lout,
      int16_t* rout,
      float float_gain,
      uint32_t num_channels,
      uint32_t num_samples)
{
	  uint32_t i;

	  // Apply float_gain on input data
      if (num_channels == 2)
      {
    	  // Processing for stereo channel
    	  for (i=0 ; i<num_samples; i++)
    	  {
    		  lout[i] = float_gain*lin[i];
    		  rout[i] = float_gain*rin[i];
    	  }
	  }
      else
      {
    	  // Processing for mono channel
    	  for (i=0 ; i<num_samples; i++)
    	  {
    		  lout[i] = float_gain*lin[i];
    	  }
      }
}


