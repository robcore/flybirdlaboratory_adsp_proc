/* ======================================================================== */
/**
@file appi_gain_ctrl_utils.h

   Utils header file to implement the Audio Post Processor Interface for 
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
   06/12/13   DS	  Added floating point gain parameter
   06/12/12	  DS	  Added bitspersample variable to call process function 
					  for 16bit and 32bit
   11/04/10   ss      Utils for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files 
 * -----------------------------------------------------------------------*/
#ifndef __APPI_GAIN_CTRL_UTILS_H__
#define __APPI_GAIN_CTRL_UTILS_H__

#include "appi_gain_ctrl.h"
#include "appi_util.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/
typedef struct
{
   const appi_vtbl_t* vtbl;			// pointer to virtual table
   uint32_t           num_channels;	// number of channels
   uint32_t           gain;			// fixed point gain value
   uint32_t           bitspersample;// bits per sample
   float			  gain_float;	// floating point gain value
} appi_gain_ctrl_struct;

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/

#endif //__APPI_GAIN_CTRL_UTILS_H__
