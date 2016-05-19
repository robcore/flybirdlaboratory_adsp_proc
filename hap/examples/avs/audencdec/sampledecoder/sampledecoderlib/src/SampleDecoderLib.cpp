/* ======================================================================== *
 * Copyright (c) 2012 QUALCOMM Technologies Incorporated.                                *
 * All Rights Reserved.                                                     *
 * Qualcomm Confidential and Proprietary.                                   *
 * ======================================================================== */

/* ========================================================================
   Sample decoder library wrapper source file
  
   *//** @file SampleDecoderLib.cpp
   This file contains the core decoder functions definitions
 * ======================================================================== */

/* ======================================================================== *
 *                          INCLUDE FILES									*
 * ======================================================================== */
#include <stdio.h>
#include <string.h>
#include "SampleDecoderLib.h"
#ifdef __qdsp6__
#include "q6protos.h"
#endif

/* ======================================================================== *
 *                       DEFINITIONS AND DECLARATIONS						*
 * ======================================================================== */

#define BYTES_PER_SAMPLE_TWO 2



/*==========================================================================*/
/* FUNCTION: Init                                                           */
/*                                                                          */
/* DESCRIPTION: Initialize the Sample decoder: set the number of channels   */
/*                                                                          */
/* INPUTS: nNoOfChannels: number of channels for decoding                   */
/* OUTPUTS:                                                                 */
/*==========================================================================*/
void SampleDecoderLib::Init (int16_t nNoOfChannels)
{
    m_nNoOfChannels = nNoOfChannels;

}


/*==========================================================================  */
/* FUNCTION: DecoderFrame                                                     */
/*                                                                            */
/* DESCRIPTION: Processes the PCM data for Mono or Stereo File                */
/*                                                                            */
/* INPUTS: samples_to_copy: This indicates the number of samples to be copied */
/* 	       num_channels: Number of Channels(Supports mono and stereo 		  */
/*         bytes_per_sample_in: This indicates the number of bytes from the   */
/*         PCM input buffer to be decoded.                                    */
/*	       bytes_per_sample_out: This indicates the number of bytes per sample*/
/*         for output.                                                        */
/*         nInpSize: This indicates the size of input frame.	              */
/*         nOutputSize: This is an ouput parameter to indicate how many bytes */
/*	       of input is decoded successfully.	              				  */
/*         src_ptr: This points to the input buffer.   				          */
/*         dest_ptr: This points to the output buffer.					      */
/* OUTPUTS: return SAMPLE_SUCCESS if Pcm data copied from input buffer to     */
/*          output buffer.		                                              */
/*============================================================================*/

ADSPResult SampleDecoderLib::DecodeFrame (uint32_t samples_to_copy,
										uint32_t num_channels,
								        uint32_t bytes_per_sample_in,
										uint32_t bytes_per_sample_out,
										uint32_t nInpSize,
										uint32_t *nOutputSize,
										int8_t  *src_ptr,
										int8_t  *dest_ptr
										)

{
	uint32_t num_samples_per_chan = (samples_to_copy / num_channels);
	uint32_t num_out_bytes_per_chan = (num_samples_per_chan * bytes_per_sample_out);
	int8_t *out_buf;
	int8_t *out_ptr[PCM_FORMAT_MAX_NUM_CHANNEL];

	if(num_channels == 1)
	{
		memcpy(dest_ptr,src_ptr, nInpSize);
	}
	else  
	{
		//For Stereo file, L channel and R channel are created
		for(uint32_t i = 0; i < num_channels; i++)
		{
			out_ptr[i] = dest_ptr + (i * num_out_bytes_per_chan);
		}
		
		if(BYTES_PER_SAMPLE_TWO == bytes_per_sample_out)   /*2 Bytes per sample*/
		{
			DeInterleave_Multichannel_16((int16_t *)src_ptr, (int16_t **)out_ptr, num_channels, num_samples_per_chan);
		}
		else /* 4 bytes per sample */
		{
			DeInterleave_Multichannel_32((int32_t *)src_ptr, (int32_t **)out_ptr, num_channels, num_samples_per_chan);
		}
	}
	*nOutputSize = nInpSize;
	return SAMPLE_SUCCESS;
}

ADSPResult DeInterleave_Multichannel_16(int16_t *inBuf,
                                 int16_t *outBuf[],
                                 uint32_t numChannels,
                                 uint32_t numSamplesToDeInterleave)
{
   if(2 == numChannels)
   {
      uint32_t i = 0;
   if(!inBuf || !outBuf[0] || !outBuf[1])
   {
       return SAMPLE_FAILURE;
   }
	for(i = 0; i < numSamplesToDeInterleave; i++)
   {
      outBuf[0][i] = inBuf[2*i];
      outBuf[1][i] = inBuf[2*i+1];
   }
   return SAMPLE_SUCCESS;
   }

    __DEINTERLEAVE_MULTICH__(inBuf, outBuf, numChannels, numSamplesToDeInterleave);
}


ADSPResult DeInterleave_Multichannel_32(int32_t *inBuf,
                                 int32_t *outBuf[],
                                 uint32_t numChannels,
                                 uint32_t numSamplesToDeInterleave)
{
   if(2 == numChannels)
   {
      uint32_t i = 0;
   if(!inBuf || !outBuf[0] || !outBuf[1])
   {
       return SAMPLE_FAILURE;
   }
	for(i = 0; i < numSamplesToDeInterleave; i++)
   {
      outBuf[0][i] = inBuf[2*i];
      outBuf[1][i] = inBuf[2*i+1];
   }
   return SAMPLE_SUCCESS;
   }

    __DEINTERLEAVE_MULTICH__(inBuf, outBuf, numChannels, numSamplesToDeInterleave);
}
