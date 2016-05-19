#ifndef __VOICE_CUSTOMFILTER_UTIL__
#define __VOICE_CUSTOMFILTER_UTIL__
/* ========================================================================= */
/**
@file Voice_CustomFilter_Util.h

   Util header file to implement the Voice Post Processor Interface for 
   applying custom filter on input signal
*/

/* =========================================================================
  Copyright (c) 2013 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================== */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   06/28/13   DS	  Updated to support parameter structure
   ========================================================================= */
#include "Voice_CustomFilter.h"

/* -------------------------------------------------------------------------
                        DATA DECLARATIONS
   ------------------------------------------------------------------------- */
/* \brief internal structure for custom filter module */
typedef struct {
   int16_t shift_factor;         // how many bits to shift
   int16_t shift_mark;           // 0: right shift; 1: left shift
   int16_t pre_sample;           // store the value of previous sample
   int16_t enable;               // TRUE: enable ; FALSE: disable
   uint32_t kpps;				 // KPPS value
} voice_customfilter_t;


#endif	//#ifndef __VOICE_CUSTOMFILTER_UTIL__
