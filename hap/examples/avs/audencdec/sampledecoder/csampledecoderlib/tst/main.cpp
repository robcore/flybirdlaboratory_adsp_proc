/*
 * test_SampleDecoder.cpp : Defines the entry point for the CSim implementation of
 * SAMPLE decoder.
 */

/**
 * Includes
 */
#include <stdlib.h>
#include "test_CSampleDecoder.h"
#include "CSampleDecoderLib.h"
#include "test_util.h"
/**
 * Definitions
 */

#ifdef PROFILE_SAMPLE_DECODER
#ifdef __qdsp6__
#include <q6sim_timer.h>
#endif
#endif

int main(int argc, char **argv)
{


    Arg_t   args;

    FILE    *in_file, *out_file;   												//File pointers to input and output files

    int32_t   lResult = SAMPLE_SUCCESS;
    int32_t   in_bytes_per_samples = 2, out_bytes_per_samples = 2; 				//16 Bit support exists for bytes bytes per sample in input and output file
    int32_t   nChannels = 1;														//Unit level testing of Sample Decoder CAPI supports Mono. For Mono Case data gets copied from
    																			//input to output without any modifications in input data unlike stereo which has L and R channels.
    int32_t   samples_to_copy=BUFFER_SIZE/in_bytes_per_samples;
    int32_t   lInBufSize, lOutBufSize;
    int8_t   output_buffer[OPBUF_SIZE];
    int8_t   input_buffer[BUFFER_SIZE];
	int8_t *poutput_buffer = output_buffer;
	int8_t *pinput_buffer = input_buffer;

	//Creating an instance of Decoder dynamic Services
    AudioDecSvc_Struct *pMe = (AudioDecSvc_Struct*) qurt_elite_memory_malloc(sizeof(AudioDecSvc_Struct), QURT_ELITE_HEAP_DEFAULT);

    get_eargs(argc, argv, &args);
#ifdef _WIN32
    fopen_s(&in_file, args.in_fileName, "rb");
#else
    in_file = fopen(args.in_fileName, "rb");
#endif

    if ( NULL == in_file )
   {
       printf("Could not read input file \n");
       exit(1);
    }
    
#ifdef _WIN32
    fopen_s(&out_file, args.out_fileName, "w+b");
#else
    out_file = fopen(args.out_fileName, "w+b");
#endif
    
    if ( NULL == out_file )
    {
       printf ("Could not create output file\n");
       exit(1);
    }


       ADSPResult result = ADSP_EFAILED;
       CAPI_Buf_t *bitstream_buffer = (CAPI_Buf_t* )qurt_elite_memory_malloc(sizeof(CAPI_Buf_t), QURT_ELITE_HEAP_DEFAULT);
       CAPI_Buf_t *pcmdata_buffer = (CAPI_Buf_t* )qurt_elite_memory_malloc(sizeof(CAPI_Buf_t), QURT_ELITE_HEAP_DEFAULT);

       //Creating an instance of CSampleDecoderLib and associating it with pMe->pDecoderLib
       qurt_elite_memory_new(pMe->pDecoderLib, CSampleDecoderLib, QURT_ELITE_HEAP_DEFAULT, result);

       pMe->BitStream.pBuf = bitstream_buffer;
       pMe->PcmData.pBuf   = pcmdata_buffer;

       //Calling the SetParam routine to set parameters required by CSampleDecoderLib :: Process function
       pMe->pDecoderLib->SetParam(eSampleDec_output_bytes_per_sample, out_bytes_per_samples);
       pMe->pDecoderLib->SetParam(eSampleDec_input_bytes_per_sample, in_bytes_per_samples);
	   pMe->pDecoderLib->SetParam(eIcapiNumChannels, nChannels);
	   pMe->pDecoderLib->SetParam(eSampleDec_samples_to_copy, samples_to_copy);

       int i=0;
       while(!feof(in_file))
       {

    	   printf("Decoding Buffer No. %d \n",i++);
    	   lInBufSize = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, in_file);
		   lOutBufSize = lInBufSize;
		   pMe->BitStream.pBuf[0].Data = (char *)pinput_buffer;
		   pMe->PcmData.pBuf[0].Data = (char *)poutput_buffer;

		   //Actual length of buffers for input(BitStream) and output(PcmData)
		   pMe->BitStream.pBuf[0].nActualDataLen = lInBufSize;
		   pMe->PcmData.pBuf[0].nActualDataLen = 0;

		   //Maximum length of buffers for input(BitStream) and output(PcmData)
		   pMe->BitStream.pBuf[0].nMaxDataLen = SAMPLEDEC_INP_BUFFER_SIZE;
		   pMe->PcmData.pBuf[0].nMaxDataLen = SAMPLEDEC_OUT_BUFFER_SIZE;
		   //Calling the CAPI Process
		   if(pMe->BitStream.pBuf[0].nActualDataLen > DECODER_FRAME_SIZE)
		   lResult = pMe->pDecoderLib->Process(&pMe->BitStream,  &pMe->PcmData,  NULL);

		   fwrite(output_buffer, sizeof(uint8_t), pMe->PcmData.pBuf[0].nActualDataLen , out_file);

       }
     fclose(in_file);
     fclose(out_file);

     qurt_elite_memory_free(bitstream_buffer);
     qurt_elite_memory_free(pcmdata_buffer);

     switch (lResult)
     {
     	 case DEC_SUCCESS :
     		 printf("Decoding Successful. Bitmatch the output.raw file with input.raw to confirm.\n");
     		 break;

     	case DEC_NEED_MORE :
     		printf("Size of input buffer is less than frame size. More data needed in input  \n");
     		break;

     	case DEC_BUFFERTOOSMALL_FAILURE :
     	    printf("Size of output buffer is not sufficient to hold input data. \n");
     	    break;

     	default:
     		printf("Decoding Unsuccessful");
     		break;

     }
     return 0;
}

