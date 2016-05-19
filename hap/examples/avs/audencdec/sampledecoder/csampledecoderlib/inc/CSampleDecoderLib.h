#ifndef C_CAPI_SAMPLE_DECODER_LIB_H
#define C_CAPI_SAMPLE_DECODER_LIB_H

/* ======================================================================== *
 * Copyright (c) 2012 QUALCOMM Technologies Incorporated.                                *
 * All Rights Reserved.                                                     *
 * Qualcomm Confidential and Proprietary.                                   *
 * ======================================================================== */

/* ========================================================================
   Sample decoder library wrapper header file
  
   *//** @file CSampleDecoderLib.h
   This file contains class definition and audio processing methods that are 
   internal to Sample decoder CAPI.
 * ======================================================================== */

/* ======================================================================== *
 *                          INCLUDE FILES									*
 * ======================================================================== */
#include "Elite_CAPI.h"



/* ======================================================================== *
 *                       DEFINITIONS AND DECLARATIONS						*
 * ======================================================================== */

/* Enums used by SetParam/GetParam Subroutines helpful in setting		*
 * parameters from Elite Framework  									*/
enum eSampleDecoder
{
	eSampleNumBlockSize = eIcapiMaxParamIndex,      // Decoder specific Enum variables starting at eIcapiMaxParamIndex
	eSampleFormatTag,
	eSampleIsSigned,
	eSampleIsInterleaved,
	eSampleDec_input_bytes_per_sample,
	eSampleDec_output_bytes_per_sample,
	eSampleDec_EndOfFrame,
	eSampleDec_samples_to_copy
};

class CSampleDecoderLib : public ICAPI
   {
	   
	   
	   
   private:

       void *m_pDecState;											//Points to Decoder specific parameters in CAPI
       
   public:




      /* =======================================================================
       *                          Public Function Declarations
       * ======================================================================= */

      /**
       * Default Constructor of CSampleDecoderLib
       */
      CSampleDecoderLib ( );

      /**
       * Constructor of CSampleDecoderLib that creats an instance of decoder lib
       */
      CSampleDecoderLib ( ADSPResult    &nRes );

      virtual ~CSampleDecoderLib ( );

         /*************************************************************************
          * CSampleDecoder Methods
          *************************************************************************/

         /**
          * Initialize the core decoder library
          *
          * @return     success/failure is returned
          */
         virtual int Init ( CAPI_Buf_t* pParams );

         /**
          * Re initialize the core decoder library in the case of repositioning or
          * when full initialization is not required
          *
          * @return     success/failure is returned
          */
         virtual int ReInit ( CAPI_Buf_t* pParams );

         /**
          * Gracefully exit the core decoder library
          *
          * @return     success/failure is returned
          */
         virtual int End ( void );

         /**
          * Get the value of the Sample decoder parameters
          *
          * @param[in]   nParamIdx      Enum value of the parameter of interest
          * @param[out]  pnParamVal      Desired value of the parameter of interest
          *
          * @return  Success/fail
          */
         virtual int GetParam ( int nParamIdx, int *pParamVal );

         /**
          * Set the value of the Sample decoder parameters
          *
          * @param[in]   nParamIdx      Enum value of the parameter of interest
          * @param[out]  nParamVal      Desired value of the parameter of interest
          *
          * @return  Success/fail
          */
         virtual int SetParam ( int nParamIdx, int nParamVal );

         /**
          * Decode audio bitstream and produce one frame worth of samples
          *
          * @param[in]   pIndata      Pointer to input bit stream
          * @param[out]  pOutData     Pointer to output samples
          * @param[out]  pOutParams   Pointer to output parameters
          *
          * @return     Success/failure
          */
         virtual int Process ( const CAPI_BufList_t* pIndata,
                                     CAPI_BufList_t*       pOutData,
                                     CAPI_Buf_t*       pOutParams );
      };

  #endif /* C_CAPI_SAMPLE_DECODER_LIB_H */
