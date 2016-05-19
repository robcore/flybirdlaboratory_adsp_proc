/* ========================================================================= */
/**
@file Voice_CustomFilter.cpp

   Source file to implement the Voice Post Processor Interface for 
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
   06/28/13   DS	  Updated to support different parameter IDs
   ========================================================================= */
/* -------------------------------------------------------------------------
                        INCLUDE FILES FOR MODULE
   ------------------------------------------------------------------------- */
#include "Voice_CustomFilter.h"
#include "Voice_CustomFilter_Util.h"
#include "adsp_vparams_api.h"

/* -------------------------------------------------------------------------
   Constant / Define Declarations
   ------------------------------------------------------------------------- */
// KPPS value
static const uint32_t CUSTOM_FILTER_EXAMPLE_KPPS = 500; //Rough Value

/* -------------------------------------------------------------------------
                          Function Definitions
   ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------
   Function name: voice_customfilter_init
   Initialize the voice module parameters.
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_init(voice_customfilter_t *customfilter_struct_ptr)
{
	ADSPResult result = ADSP_EOK;
	customfilter_struct_ptr->enable = FALSE;                             // default : disable this module
	customfilter_struct_ptr->shift_factor = 0;                           // bit to be shifted
	customfilter_struct_ptr->shift_mark = 0;                             // 0: right shift
	customfilter_struct_ptr->pre_sample = 0;                             // set to be 0
	return result;
}

/* ------------------------------------------------------------------------
   Function name: voice_customfilter_process
   Applies filtering process on input samples and generates the output samples.
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_process(voice_customfilter_t *customfilter_struct_ptr, int16_t *pLocalBufDes, int16_t *pLocalBufSrc, uint32_t num_samples)
{
	ADSPResult nResult = ADSP_EOK;
	int16_t *pBufDes=(int16_t *)pLocalBufDes;
	int16_t *pBufSrc=(int16_t *)pLocalBufSrc;   
	int16_t temp=0;
	uint32_t i;

	if(TRUE == customfilter_struct_ptr->enable)                          // if this module is enabled
	{
		if(0 == (customfilter_struct_ptr->shift_mark) )                   // 0 for right shift condition
		{
			for(i = 0; i < num_samples; i++)
			{
				temp = ((customfilter_struct_ptr->pre_sample + pBufSrc[i]) >> (customfilter_struct_ptr->shift_factor));
				customfilter_struct_ptr->pre_sample = pBufSrc[i];           // note: update the value in pBufDes[i] after store the value of previous sample
				// for inplace process, original data will be replaced, should backup first       
				pBufDes[i] = temp; 
			}
		}
		else if(1 == (customfilter_struct_ptr->shift_mark) )              // 1 for left shift condition
		{
			for(i = 0; i < num_samples; i++)
			{
				temp = ((customfilter_struct_ptr->pre_sample + pBufSrc[i]) << (customfilter_struct_ptr->shift_factor));            
				customfilter_struct_ptr->pre_sample = pBufSrc[i];           // note: update the value in pBufDes[i] after store the value of previous sample
				// for inplace process, original data will be replaced, should backup first       
				pBufDes[i] = temp; 
			}  
		}
		MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "VPRX CUSTOM FILTER PROCESS Enabled");
	}
	return nResult;
}

/* ------------------------------------------------------------------------
   Function name: voice_customfilter_set_param
   Sets either a parameter value or a parameter structure containing multiple
   parameters. In the event of a failure, the appropriate error code is
   returned.
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_set_param(voice_customfilter_t *customfilter_struct_ptr,
                                       uint8_t *params_buffer_ptr, 
                                       uint32_t param_id, 
                                       uint16_t param_size)
{
	ADSPResult result = ADSP_EOK;
	uint16_t *param_ptr = (uint16_t *)params_buffer_ptr;                 // unint16_t in case user give negative value parameter

	switch(param_id)
	{
	case VOICE_PARAM_MOD_ENABLE:
		if(sizeof(voice_customfilter_enable_t) <= param_size)
		{
			voice_customfilter_enable_t *enable_ptr = (voice_customfilter_enable_t *)params_buffer_ptr;
			customfilter_struct_ptr->enable = enable_ptr->enable;
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_set_param enable=%d", customfilter_struct_ptr->enable);
			result = ADSP_EOK;
		}
		else
		{
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_set_param (VOICE_PARAM_RX_CUSTOMFILTER_ENABLE) Bad Param Size=%lu", param_size);
			result = ADSP_EBADPARAM;
			return result;
		}
		break;
	case VOICE_PARAM_RX_CUSTOMFILTER_SHIFT:
		if(sizeof(voice_customfilter_shift_t) <= param_size)
		{
			voice_customfilter_shift_t *shift_ptr = (voice_customfilter_shift_t *) params_buffer_ptr;
			customfilter_struct_ptr->shift_factor = shift_ptr->shift_factor;
			customfilter_struct_ptr->shift_mark = shift_ptr->shift_mark;
			MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_set_param shift_factor=%d, shift_mark=%d", customfilter_struct_ptr->shift_factor, customfilter_struct_ptr->shift_mark);
			result = ADSP_EOK;
		}
		else
		{
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_set_param (VOICE_PARAM_RX_CUSTOMFILTER_SHIFT) Bad Param Size=%lu", param_size);
			result = ADSP_EBADPARAM;
			return result;
		}
		break;
	default:
		result = ADSP_EUNSUPPORTED;
		MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "voice_customfilter_set_param: Unsupported Parameter ID");
		break;
	}


	return result;
}

/* ------------------------------------------------------------------------
   Function name: voice_customfilter_get_param
   Gets either a parameter value or a parameter structure containing multiple
   parameters. In the event of a failure, the appropriate error code is
   returned.
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_get_param(voice_customfilter_t *customfilter_struct_ptr,
                                       uint8_t *params_buffer_ptr,
                                       uint32_t param_id,
                                       int32_t inp_param_buf_size,                 
                                       uint16_t *param_size_ptr)
{
	ADSPResult result = ADSP_EOK;
	uint16_t *param_ptr = (uint16_t *)params_buffer_ptr;

	switch(param_id)
	{
	case VOICE_PARAM_MOD_ENABLE:
		if(sizeof(voice_customfilter_enable_t) <= inp_param_buf_size)
		{
			voice_customfilter_enable_t *enable_ptr = (voice_customfilter_enable_t *)params_buffer_ptr;
			enable_ptr->enable = customfilter_struct_ptr->enable;
			*param_size_ptr = sizeof(voice_customfilter_enable_t);
			result = ADSP_EOK;
		}
		else
		{
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_get_param (VOICE_PARAM_RX_CUSTOMFILTER_ENABLE) Bad Param Size=%lu", inp_param_buf_size);
			result = ADSP_EBADPARAM;
			return result;
		}
		break;
	case VOICE_PARAM_RX_CUSTOMFILTER_SHIFT:
		if(sizeof(voice_customfilter_shift_t) <= inp_param_buf_size)
		{
			voice_customfilter_shift_t *shift_ptr = (voice_customfilter_shift_t *) params_buffer_ptr;
			shift_ptr->shift_factor = customfilter_struct_ptr->shift_factor;
			shift_ptr->shift_mark = customfilter_struct_ptr->shift_mark;
			*param_size_ptr = sizeof(voice_customfilter_shift_t);
			result = ADSP_EOK;
		}
		else
		{
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"voice_custom_filter_get_param (VOICE_PARAM_RX_CUSTOMFILTER_SHIFT) Bad Param Size=%lu", inp_param_buf_size);
			result = ADSP_EBADPARAM;
			return result;
		}
		break;
	default:
		result = ADSP_EUNSUPPORTED;
		MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "voice_customfilter_get_param: Unsupported Parameter ID");
		break;
	}

	return result;
}

/* ------------------------------------------------------------------------
   Function name: voice_customfilter_get_kpps
   Sets the voice custom filter module KPPS
   ------------------------------------------------------------------------- */
ADSPResult voice_customfilter_get_kpps(voice_customfilter_t *customfilter_struct_ptr, uint32_t *kpps_ptr)
{
	if(NULL == customfilter_struct_ptr || NULL == kpps_ptr)
	{
		return ADSP_EBADPARAM;
	}
	customfilter_struct_ptr->kpps = CUSTOM_FILTER_EXAMPLE_KPPS;
	*kpps_ptr = customfilter_struct_ptr->kpps;

	return ADSP_EOK;
}
