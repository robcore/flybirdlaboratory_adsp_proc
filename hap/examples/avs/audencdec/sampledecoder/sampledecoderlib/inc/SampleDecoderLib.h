/*===========================================================================*]
[* Copyright (c) 2012 QUALCOMM Technologies Incorporated.                                 *]
[* All Rights Reserved.                                                      *]
[* Qualcomm Confidential and Proprietary.                                    *]
[*===========================================================================*]
[*===========================================================================*]*/

/*****************************************************************************
 *  Global Macro Definitions                                                 *
 *****************************************************************************/
#ifdef __cplusplus
 #define EXTERN_C extern "C"
#else
 #define EXTERN_C extern
#endif


#ifndef NULL
 #ifdef __cplusplus
  #define NULL    0
#else
  #define NULL    ( ( void * ) 0 )
 #endif
#endif

/*****************************************************************************
 *  Global Type Definitions                                                  *
 *****************************************************************************/

#ifndef uint16
#define uint16  unsigned short int
#endif
typedef unsigned long long uint64_t;  /* Unsigned 64 bit value */
typedef unsigned long int  uint32_t;  /* Unsigned 32 bit value */
typedef unsigned short     uint16_t;  /* Unsigned 16 bit value */
typedef unsigned char      uint8_t;   /* Unsigned 8  bit value */

typedef signed long long   int64_t;   /* Signed 64 bit value */
typedef signed long int    int32_t;   /* Signed 32 bit value */
typedef signed short       int16_t;   /* Signed 16 bit value */
typedef signed char        int8_t;    /* Signed 8  bit value */

typedef int ADSPResult;

/*============================================================================
  Constants and Macros
============================================================================*/
#define SAMPLE_SUCCESS                     0
#define SAMPLE_FAILURE					   1
#define SAMPLE_BUFFERTOOSMALL_FAILURE      2
#define SAMPLE_NEED_MORE		           3

#define __DEINTERLEAVE_MULTICH__(inBuf, outBuf, numChannels, numSamplesToDeInterleave) \
{                                                                   \
    uint32_t i = 0;                                                 \
    uint32_t j = 0;                                                 \
                                                                    \
    if(!inBuf || !outBuf || !numChannels)                           \
    {                                                               \
        return SAMPLE_FAILURE;                                      \
    }                                                               \
                                                                    \
    for(i = 0; i < numChannels; i++)                                \
    {                                                               \
        if(!outBuf[i])                                              \
        {                                                           \
            return SAMPLE_FAILURE;                                  \
        }                                                           \
    }                                                               \
                                                                    \
    for(i = 0; i < numSamplesToDeInterleave; i++)                   \
    {                                                               \
        for(j = 0; j < numChannels; j++)                            \
        {                                                           \
            outBuf[j][i] = inBuf[(numChannels * i) + j];            \
        }                                                           \
    }                                                               \
                                                                    \
    return SAMPLE_SUCCESS;                                                \
}

#define  PCM_FORMAT_MAX_NUM_CHANNEL  8

ADSPResult DeInterleave_Multichannel_16(int16_t *inBuf,
                                 int16_t *outBuf[],
                                 uint32_t numChannels,
                                 uint32_t numSamplesToDeInterleave);

ADSPResult DeInterleave_Multichannel_32(int32_t *inBuf,
                                 int32_t *outBuf[],
                                 uint32_t numChannels,
                                 uint32_t numSamplesToDeInterleave);



class SampleDecoderLib {
	
private:
    int16_t m_nNoOfChannels;     /* number of channels */
    
public:

    /*==========================================================================*/
    /* FUNCTION: Init                                                           */
    /*                                                                          */
    /* DESCRIPTION: Initialize the Sample decoder: set the number of channels   */
    /*                                                                          */
    /* INPUTS: nNoOfChannels: number of channels for decoding                   */
    /* OUTPUTS:                                                                 */
    /*==========================================================================*/
    void Init (int16_t nNoOfChannels);
    
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
	/*         for output file.                                                   */
	/*         nInpSize: This indicates the size of input frame.	              */
	/*         nOutputSize: This is an ouput parameter to indicate how many bytes */
	/*	       of input is decoded successfully.	              				  */
	/*         src_ptr: This points to the input buffer.   				          */
	/*         dest_ptr: This points to the output buffer.					      */
	/* OUTPUTS: return SAMPLE_SUCCESS if Pcm data copied from input buffer to     */
	/*          output buffer.		                                              */
	/*============================================================================*/
    
    ADSPResult DecodeFrame (uint32_t samples_to_copy,
    					uint32_t num_channels,
    					uint32_t bytes_per_sample_in,
    					uint32_t bytes_per_sample_out,
    					uint32_t nInpSize,
    					uint32_t *nOutputSize,
    					int8_t  *src_ptr,
    					int8_t  *dest_ptr
    					);

    
};

