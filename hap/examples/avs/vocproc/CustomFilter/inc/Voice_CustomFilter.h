#ifndef __VOICE_CUSTOMFILTER__
#define __VOICE_CUSTOMFILTER__
/* ========================================================================= */
/**
@file Voice_CustomFilter.h

   Header file to implement the Voice Post Processor Interface for 
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
   11/04/10   ss      APPI wrapper
   06/28/13   DS	  Updated to support integration with B-family chipsets and
					  parameter structures
   ========================================================================= */

/* -------------------------------------------------------------------------
                     INCLUDE FILES FOR MODULE
   ------------------------------------------------------------------------- */
#include "Elite.h"
#include "Voice_CustomFilter_Util.h"

/* -------------------------------------------------------------------------
                        DATA DECLARATIONS
   ------------------------------------------------------------------------- */
/* \brief enable parameter structure of custom filter module */
typedef struct {
   int16_t enable;               // TRUE: enable ; FALSE: disable
   int16_t reserevd;			 // reserved
} voice_customfilter_enable_t;

/* \brief shift parameters structure of custom filter module */
typedef struct {
   int16_t shift_factor;         // how many bits to shift
   int16_t shift_mark;           // 0: right shift; 1: left shift
} voice_customfilter_shift_t;

/* -------------------------------------------------------------------------
                           Function Declarations
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_init(voice_customfilter_t *customfilter_struct_ptr);

ADSPResult voice_customfilter_process(voice_customfilter_t *customfilter_struct_ptr, 
                                       int16_t *pLocalBufDes, 
                                       int16_t *pLocalBufSrc, 
                                       uint32_t num_samples);

ADSPResult voice_customfilter_set_param(voice_customfilter_t *customfilter_struct_ptr,
                                       uint8_t *params_buffer_ptr, 
                                       uint32_t param_id, 
                                       uint16_t param_size);

ADSPResult voice_customfilter_get_param(voice_customfilter_t *customfilter_struct_ptr,
                                       uint8_t *params_buffer_ptr,
                                       uint32_t param_id,
                                       int32_t inp_param_buf_size,                 
                                       uint16_t *param_size_ptr);

ADSPResult voice_customfilter_get_kpps(voice_customfilter_t *customfilter_struct_ptr,
                                       uint32_t *kpps_ptr);


#endif	//#ifndef __VOICE_CUSTOMFILTER__
