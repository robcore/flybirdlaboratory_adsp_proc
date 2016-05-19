/* ======================================================================== *
 * Copyright (c) 2012 QUALCOMM Technologies Incorporated.                                *
 * All Rights Reserved.                                                     *
 * Qualcomm Confidential and Proprietary.                                   *
 * ======================================================================== */

/* ========================================================================
   Sample decoder library wrapper source file
  
   *//** @file CSampleDecoderLib.cpp
   This file contains constructor, destructor and audio decoder methods 
   definition that are internal to Sample decoder CAPI.
   The functions in this file are called by decoder service to interact with 
   Sample core decoder
 * ======================================================================== */

/* ======================================================================== *
 *                          INCLUDE FILES									*
 * ======================================================================== */
#include <string.h>
#include <stdlib.h>
#include "test_util.h"
#include "SampleDecoderLib.h"
#include "CSampleDecoderLib.h"
#include "CSampleDecoderLib_Struct.h"

/* ======================================================================== *
 *                              DEFINITIONS 								*
 * ======================================================================== */
#define BYTES_TO_COPY_TWO 2


/* =======================================================================  *
 *                          Function Definitions							*
 * =======================================================================  */

  /*************************************************************************
   ** Constructors/destructor                                              *
   *************************************************************************/
   CSampleDecoderLib::CSampleDecoderLib( )
   {
       //default constructor
   }

   //Constructor that creates instance of Sample Decoder Library
   CSampleDecoderLib::CSampleDecoderLib( ADSPResult &nRes )

   {
	   //Allocate memory for decoder state(CAPI Structure)
       m_pDecState = qurt_elite_memory_malloc(sizeof(CSampleDecState_t), QURT_ELITE_HEAP_DEFAULT);
       if(!m_pDecState)
       {
          nRes = DEC_NOMEMORY_FAILURE ;
          return ;
       }

       CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;
       // Create an instance of Sample Decoder Library
       qurt_elite_memory_new(pDecState->m_pSampleDecoder, SampleDecoderLib, QURT_ELITE_HEAP_DEFAULT);

	  /* To create an instance of Sample Decoder Library, the size of instance to be created can  */
	  /* also be fetched from functional library based on the requirement of functional library	  */
	  
	  
       if ( NULL == pDecState->m_pSampleDecoder )
       {
           nRes = DEC_NOMEMORY_FAILURE ;
           return ;
       }
       nRes = DEC_SUCCESS;
   }

/* ************************************************************************ *
 * Destructor																*
 * ************************************************************************ */
   CSampleDecoderLib::~CSampleDecoderLib( )
   {
       CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;
       //Destroy core decoder
       if(pDecState)
       {
          if(pDecState->m_pSampleDecoder)
          {
             qurt_elite_memory_delete(pDecState->m_pSampleDecoder, SampleDecoderLib);
		  }

          //now destroy decoder state
          qurt_elite_memory_free(m_pDecState);
       }
   }




   /* --------------------------------------------------------------------- *
    *                Sample decoder initialization.							*
    * --------------------------------------------------------------------- */
   int CSampleDecoderLib::Init ( CAPI_Buf_t* /*pParams*/ )
   {

      CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;
       // create instance of the Sample decoder library

        //return fail if not able to create one
        if ( (NULL == pDecState->m_pSampleDecoder) || (NULL == pDecState)) {
            return DEC_FAILURE;
        }

      // Initialize the internal state of the Sample Decoder
      (pDecState->m_pSampleDecoder)->Init((uint16_t) pDecState->m_sNumberOfChannels);

      return DEC_SUCCESS;
   }

/* ------------------------------------------------------------------------ *
 *          Sample decoder re-initialization routine						*
 * ------------------------------------------------------------------------ */

int CSampleDecoderLib::ReInit ( CAPI_Buf_t* /*pParams*/ )
{
   CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;
   // Initialize the internal state of the Sample Decoder
   (pDecState->m_pSampleDecoder)->Init((uint16_t) pDecState->m_sNumberOfChannels);

   return DEC_SUCCESS;
}


   /* --------------------------------------------------------------------- *
   * Sample decoder END routine, de-allocate memory allocated in the Init   *
   * ---------------------------------------------------------------------  */
int CSampleDecoderLib::End ( void )
{

   CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;

   // Destroy core decoder. m_pSampleDecoder is NULL initialized and safe to delete.
   if(NULL !=pDecState->m_pSampleDecoder)
   qurt_elite_memory_delete(pDecState->m_pSampleDecoder,SampleDecoderLib);
   pDecState->m_pSampleDecoder = NULL;

   // now destroy the decoder state
   if(NULL !=m_pDecState)
   qurt_elite_memory_free(m_pDecState);
   m_pDecState = NULL;

   return DEC_SUCCESS;
}


/* -----------------------------------------------------------------------  *
 *               Sample decoder GetParam routine							*
 * -----------------------------------------------------------------------  */
 int CSampleDecoderLib::GetParam ( int nParamIdx, int *pnParamVal )
{

     CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;

     switch ( nParamIdx )
     {
     case eIcapiNumChannels :
         *pnParamVal = (int) pDecState->m_sNumberOfChannels;
         break;

     case eIcapiSamplingRate :
         *pnParamVal = (int) pDecState->m_lSamplingRate;
         break;

     case eIcapiInputBufferSize :
         *pnParamVal = (int) SAMPLEDEC_INP_BUF_SIZE;
         break;
	 
     case eIcapiOutputBufferSize :
         *pnParamVal = (int) SAMPLEDEC_OUT_BUF_SIZE;
         break;

     case eIcapiThreadStackSize :
         *pnParamVal = (int) SAMPLEDEC_THREAD_STACK_SIZE;
         break;

     case eIcapiWaitForFormatBlock :
         *pnParamVal = (int) SAMPLEDEC_FORMAT_BLOCK_REQ;
         break;

     case eIcapiBitsPerSample:
         *pnParamVal = 16;
         break;

     case eIcapiKCPSRequired:
         *pnParamVal = SAMPLEDEC_KIPS;
         break;

     case eSampleNumBlockSize :
         *pnParamVal = (int) pDecState->m_lNumBlockSize;
          break;


     case eSampleDec_output_bytes_per_sample :
          *pnParamVal = (int)(&pDecState->m_lDec_output_bytes_per_sample);
          break;
	
     case eSampleDec_input_bytes_per_sample :
    	 *pnParamVal = (int)(&pDecState->m_lDec_input_bytes_per_sample);
          break;
	 

	 case eSampleDec_EndOfFrame :
              *pnParamVal = (int) pDecState->m_lDec_EndOfFrame;
              break;
     
	 case eIcapiOutputChanMap:

		 pDecState->out_chan_map.nChannels =
	 			(unsigned int) pDecState->m_sNumberOfChannels;

	 		if(1 == pDecState->out_chan_map.nChannels)
	 		{
	 			pDecState->out_chan_map.nChannelMap[0] = eIcapiCentre;
	 		}
	 		else if(2 == pDecState->out_chan_map.nChannels)
	 		{
	 			pDecState->out_chan_map.nChannelMap[0] = eIcapiLeft;
	 			pDecState->out_chan_map.nChannelMap[1] = eIcapiRight;
	 		}
	 		*pnParamVal = (int)(&pDecState->out_chan_map);

	 		break;
	 
     default:
         return ( DEC_BADPARAM_FAILURE );
     }
     return DEC_SUCCESS;
}

/* ------------------------------------------------------------------------ *
 *               Sample decoder SetParam routine							*
 * ------------------------------------------------------------------------ */

int CSampleDecoderLib::SetParam (  int lParamIdx, int lParamVal )
   {

        CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;

        switch ( lParamIdx ) {
        case eSampleFormatTag:
            pDecState->m_lFormatTag = ( uint32_t ) lParamVal;
            break;

        case eIcapiNumChannels :
            pDecState->m_sNumberOfChannels = ( uint16_t ) lParamVal;
            break;

        case eIcapiSamplingRate :
            pDecState->m_lSamplingRate = ( uint32_t ) lParamVal;
            break;

        case eSampleIsSigned :
            pDecState->m_lIsSigned = ( uint32_t ) lParamVal;
            break;

        case eSampleIsInterleaved :
            pDecState->m_lIsInterleaved = ( uint32_t ) lParamVal;
            break;

        case eSampleNumBlockSize :
            pDecState->m_lNumBlockSize = ( uint32_t ) lParamVal;
            break;

        case eIcapiBitsPerSample:
        	pDecState->m_sBitsPerSample = ( uint32_t ) lParamVal; 
            break;

        case eSampleDec_output_bytes_per_sample :
            pDecState->m_lDec_output_bytes_per_sample = ( uint32_t ) lParamVal;
            break;


        case eSampleDec_input_bytes_per_sample :
            pDecState->m_lDec_input_bytes_per_sample = ( uint32_t ) lParamVal;
            break;


        case eSampleDec_EndOfFrame :
			 pDecState->m_lDec_EndOfFrame = ( uint32_t ) lParamVal;
			 break;

        case eSampleDec_samples_to_copy :
             pDecState->m_lDec_SamplesToCopy = ( uint32_t ) lParamVal;
             break;

        default:
            return DEC_BADPARAM_FAILURE;
        }

        return DEC_SUCCESS;
  }


/* ------------------------------------------------------------------------ *
 *                Sample decoder Process									*
 * ------------------------------------------------------------------------ */
int CSampleDecoderLib::Process(const CAPI_BufList_t* pBitStream,
        				CAPI_BufList_t*       pPcmData,
        				CAPI_Buf_t*      /*pParams*/)
	{
	CSampleDecState_t *pDecState = (CSampleDecState_t *)m_pDecState;
	int32_t nRes=0;
	int32_t in_bytes_to_copy = pDecState->m_lDec_input_bytes_per_sample; 				// pDecState->m_lDec_input_bytes_per_sample is set by SetParam Routine. It should be set to 2
	int32_t out_bytes_to_copy = pDecState->m_lDec_output_bytes_per_sample;				// pDecState->m_lDec_output_bytes_per_sample is set by SetParam Routine. It should be set to 2
	int32_t num_channels = pDecState->m_sNumberOfChannels;								// pDecState->m_sNumberOfChannels is set by SetParam Routine. It supports Mono and Stereo files
	uint32_t samples_to_copy = pDecState->m_lDec_SamplesToCopy;							// pDecState->m_lDec_SamplesToCopy is set by SetParam Routine.
	int8_t *poutput_buffer;															    // Pointer to output buffer
	int8_t *pinput_buffer;																// Pointer to input buffer
	int nInpSize;
	uint32_t nOutputSize=0;


	/*Make sure the input buffer contains some valid data
	 if(pBitStream->pBuf[0].nActualDataLen <= DEC_FRAME_SIZE)
	     nRes = SAMPLE_NEED_MORE;


	//Checking if Output buffer is too small and cannot hold a frame.
	if( (pPcmData->pBuf[0].nMaxDataLen - pPcmData->pBuf[0].nActualDataLen) < pBitStream->pBuf[0].nActualDataLen )
		nRes = SAMPLE_BUFFERTOOSMALL_FAILURE;
	*/


	if (pBitStream->pBuf[0].nActualDataLen > pPcmData->pBuf[0].nMaxDataLen )
		nInpSize = pPcmData->pBuf[0].nMaxDataLen;
	else
		nInpSize = pBitStream->pBuf[0].nActualDataLen;

	pBitStream->pBuf[0].nActualDataLen -= nInpSize;



	pinput_buffer = (int8_t *)pBitStream->pBuf[0].Data;
	poutput_buffer = (int8_t *)pPcmData->pBuf[0].Data;


	//Calling the Functional Library
	if(nRes != SAMPLE_BUFFERTOOSMALL_FAILURE && nRes != SAMPLE_NEED_MORE)
	nRes = (pDecState->m_pSampleDecoder->DecodeFrame) (samples_to_copy,
													   num_channels,
													   in_bytes_to_copy,
												       out_bytes_to_copy,
												       nInpSize,
												       &nOutputSize,
												       pinput_buffer,
												       poutput_buffer);

	pPcmData->pBuf[0].nActualDataLen += nOutputSize;

	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Reached end of process function Sample Decoder CAPI");
	 switch (nRes)
	     {
	     	 case SAMPLE_SUCCESS :
	     		 return DEC_SUCCESS;
	     		 break;

	     	case SAMPLE_NEED_MORE :
	     		 return DEC_NEED_MORE;
	     		 break;

	     	case SAMPLE_BUFFERTOOSMALL_FAILURE :
	     		 return DEC_BUFFERTOOSMALL_FAILURE;
	     	     break;

	     	default:
	     		 return DEC_FAILURE;
          		 break;

	     }
	}
