#ifndef C_CAPI_SAMPLE_DECODER_LIB_STRUCT_H
#define C_CAPI_SAMPLE_DECODER_LIB_STRUCT_H

/* ======================================================================== *
 * Copyright (c) 2012 QUALCOMM Technologies Incorporated.                                *
 * All Rights Reserved.                                                     *
 * Qualcomm Confidential and Proprietary.                                   *
 * ======================================================================== */

/* ========================================================================
   Sample decoder library wrapper header file
  
   *//** @file CSampleDecoderLib_Structs.h
   This file contains structure definitions that are internal to Sample
   decoder CAPI.
 * ======================================================================== */

/* ======================================================================== *
 *                          INCLUDE FILES									*
 * ======================================================================== */
class SampleDecoderLib;

/* ======================================================================== *
 *                       DEFINITIONS AND DECLARATIONS					    *
 * ======================================================================== */
static const uint32_t SAMPLEDEC_INP_BUF_SIZE      = 4096*2;  //Maximum buffer size for input. This corresponds to enum variable eSampleDec_input_bytes_per_sample used by Elite Framework.
static const uint32_t SAMPLEDEC_OUT_BUF_SIZE      = 8192*2;  //Maximum buffer size for input. This corresponds to enum variable eSampleDec_output_bytes_per_sample used by Elite Framework.
static const uint32_t SAMPLEDEC_THREAD_STACK_SIZE = 2048;	 //Corresponds to enum variable eIcapiThreadStackSize used by Elite Framework to get thread stack size value from CAPI.Based on Decoder Requirement the stack size can be changed.
static const uint32_t SAMPLEDEC_FORMAT_BLOCK_REQ  = 1;		 //Corresponds to enum variable eIcapiWaitForFormatBlock used by Elite Framework to get format block value from CAPI(Useful in Update Media Format Function).
															 //If the decoder service is ready to be initialized without any SetParam, then this value can be set to 0.
static const uint32_t SAMPLEDEC_KIPS              = 20000;	 //Corresponds to enum variable eIcapiKCPSRequired used by Elite Framework to get KCPS value from CAPI.
static const uint32_t DEC_FRAME_SIZE			  = 1000;	 //Corresponds to the minimum bytes required by functional lib for processing

typedef struct
{
         // Sample core decoder instance used by the SampleDecoderLib
        SampleDecoderLib *m_pSampleDecoder;

        int32_t             m_lFormatTag;						// Media Format Tag
        int16_t             m_sNumberOfChannels;			    // Number of granules
        int16_t             m_sBitsPerSample;				    // Bits Per Sample
        int32_t             m_lSamplingRate;					// Sampling Rate
        int32_t             m_lIsSigned;						// Signed or Unsigned
        int32_t             m_lIsInterleaved;					// Interleaved or de-interleaved
        int32_t             m_lNumBlockSize;					// Number of SAMPLE Block Size
        int32_t             m_lrSampleUsed;					// Number of bytes of input used
        int32_t             m_lrSamplesWritten;				// Number of samples outputted
        int32_t			  m_lDec_output_bytes_per_sample;   // Output Bytes per Sample
        int32_t			  m_lDec_input_bytes_per_sample;    // Input Bytes per Sample
        int32_t			  m_lDec_EndOfFrame;				// End of one frame
        int32_t 			  m_lDec_SamplesToCopy;				// Samples to copy from input to output
        
        CAPI_ChannelMap_t out_chan_map;                 // output channel map
} CSampleDecState_t;

#endif /*#ifndef C_CAPI_SAMPLE_DECODER_LIB_STRUCT_H*/
