/* ======================================================================== */
/**
@file appi_gain_ctrl.c

   Source file to implement the Audio Post Processor Interface for
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
   06/12/12	  DS	  Updated to support 24 bit processing
   11/03/11	  DS	  Media format checking added in init and reinit
   11/04/10   ss      Source for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files
 * -----------------------------------------------------------------------*/
#include "appi_gain_ctrl.h"
#include "appi_gain_ctrl_utils.h"
#include "adsp_media_fmt.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/
//#define GAIN_FLOAT_ALGO

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_reinit(
      appi_t*               _pif,
      const appi_format_t*  in_format_ptr,
      appi_format_t*        out_format_ptr,
      appi_buf_t*           info_ptr);

static ADSPResult appi_gain_ctrl_process(
      appi_t*               _pif,
      const appi_buflist_t* input,
      appi_buflist_t*       output,
      appi_buf_t*           info_ptr);

static ADSPResult appi_gain_ctrl_end(
      appi_t*               _pif);

static ADSPResult appi_gain_ctrl_set_param(
      appi_t*               _pif,
      uint32_t              param_id,
      const appi_buf_t*     params_ptr);

static ADSPResult appi_gain_ctrl_get_param(
      appi_t*               _pif,
      uint32_t              param_id,
      appi_buf_t*           params_ptr);

static ADSPResult appi_gain_ctrl_get_input_req(
      appi_t*               _pif,
      const uint32_t        output_size,
      uint32_t*             input_size_ptr);

static const appi_vtbl_t vtbl =
{
   appi_gain_ctrl_reinit,
   appi_gain_ctrl_process,
   appi_gain_ctrl_end,
   appi_gain_ctrl_set_param,
   appi_gain_ctrl_get_param,
   appi_gain_ctrl_get_input_req
};

static bool_t is_supported_media_type(const appi_format_t *format_ptr);

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_getsize
  Returns the memory required by this associated structure/algorithm.
 * -----------------------------------------------------------------------*/
ADSPResult appi_gain_ctrl_getsize(
      const appi_buf_t* params_ptr,
      uint32_t* size_ptr)
{
   if (NULL == size_ptr)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Getsize received bad pointer, 0x%lx",
            (uint32_t)size_ptr);
      return ADSP_EUNEXPECTED;
   }

   // Each block must begin with 8-byte aligned memory. Here we have 3 blocks
   *size_ptr = align_to_8_byte(sizeof(appi_gain_ctrl_struct));

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Getsize done, requires %lu bytes",*size_ptr);
   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_init
  Initialize the APPI library. This function can allocate memory.
 * -----------------------------------------------------------------------*/
ADSPResult appi_gain_ctrl_init(
      appi_t*               _pif,
      bool_t*               is_inplace_ptr,
      const appi_format_t*  in_format_ptr,
      appi_format_t*        out_format_ptr,
      appi_buf_t*           info_ptr)
{
   if (NULL == _pif
         || NULL == is_inplace_ptr 
         || NULL == in_format_ptr
         || NULL == out_format_ptr)
   {
      MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Init received bad pointer, 0x%lx, 0x%lx, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)is_inplace_ptr, (uint32_t)in_format_ptr, (uint32_t)out_format_ptr);
      return ADSP_EUNEXPECTED;
   }

   // Check for support
   if (!is_supported_media_type(in_format_ptr))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Init, Data format unsupported");
      return ADSP_EUNSUPPORTED;
   }
   // Based on what has been requested by getsize function, memory has been
   // allocated for
   //   - appi_gain_ctrl_struct
   //   - coeffs
   int8_t* ptr = (int8_t*)_pif;
   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)ptr;

   me_ptr->vtbl = &vtbl;

   // Set default output data format (determined by internal algorithm)
   out_format_ptr->num_channels        = in_format_ptr->num_channels;
   out_format_ptr->bits_per_sample     = in_format_ptr->bits_per_sample;
   out_format_ptr->sampling_rate       = in_format_ptr->sampling_rate;
   out_format_ptr->data_is_signed      = in_format_ptr->data_is_signed;
   out_format_ptr->data_is_interleaved = in_format_ptr->data_is_interleaved;
   memcpy (out_format_ptr->channel_type, in_format_ptr->channel_type, out_format_ptr->num_channels * sizeof(out_format_ptr->channel_type[0]));

   // Copy format to internal structure
   me_ptr->num_channels                = in_format_ptr->num_channels;

   // Assign bitspersample
   me_ptr->bitspersample = in_format_ptr->bits_per_sample;

   // Set default Gain in Q13
   me_ptr->gain = 8192;
   // Set default floating point gain in 32 bit
   me_ptr->gain_float = 0x3F800000;

   // Report if in-place is supported by this algorithm
   // If it is supported, the same buffer may be sent down
   // for optimal performance
   *is_inplace_ptr = FALSE;

   MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Init done with outformat %lu,%lu,%lu,%lu,%lu",
         out_format_ptr->num_channels,
         out_format_ptr->bits_per_sample,
         out_format_ptr->sampling_rate,
         out_format_ptr->data_is_signed,
         out_format_ptr->data_is_interleaved);

   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_reinit
  Reinitialize the APPI library. This function can optionally allocate
  memory. The state is dependent on the media type information, such as the
  sampling rate.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_reinit(
      appi_t*               _pif,
      const appi_format_t*  in_format_ptr,
      appi_format_t*        out_format_ptr,
      appi_buf_t*           info_ptr)
{
   if (NULL == _pif
         || NULL == in_format_ptr
         || NULL == out_format_ptr)
   {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Reinit received bad pointer, 0x%lx, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)in_format_ptr, (uint32_t)out_format_ptr);
      return ADSP_EUNEXPECTED;
   }

   // Check for support
   if (!is_supported_media_type(in_format_ptr))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Reinit, Data format unsupported");
      return ADSP_EUNSUPPORTED;
   }

   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)(_pif);

   // Set output data format (determined by internal algorithm)
   out_format_ptr->num_channels        = in_format_ptr->num_channels;
   out_format_ptr->bits_per_sample     = in_format_ptr->bits_per_sample;
   out_format_ptr->sampling_rate       = in_format_ptr->sampling_rate;
   out_format_ptr->data_is_signed      = in_format_ptr->data_is_signed;
   out_format_ptr->data_is_interleaved = in_format_ptr->data_is_interleaved;
   memcpy (out_format_ptr->channel_type, in_format_ptr->channel_type, out_format_ptr->num_channels * sizeof(out_format_ptr->channel_type[0]));

   // Copy format to internal structure
   me_ptr->num_channels                = in_format_ptr->num_channels;

   // Assign bitspersample
   me_ptr->bitspersample = in_format_ptr->bits_per_sample;

   MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Reinit done with outformat %lu,%lu,%lu,%lu,%lu",
         out_format_ptr->num_channels,
         out_format_ptr->bits_per_sample,
         out_format_ptr->sampling_rate,
         out_format_ptr->data_is_signed,
         out_format_ptr->data_is_interleaved);

   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_process
  Processes an input buffer and generates an output buffer.
  Assumes Stereo, for this example
  Notes;
  - No steady state debug messages (prints) allowed in this function
  - Supports only 16-bit and 24-bit processing
  - Supports only mono and stereo channel
  - Supports only signed de-interleaved data processing
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_process(
      appi_t*               _pif,
      const appi_buflist_t* input,
      appi_buflist_t*       output,
      appi_buf_t*           info_ptr)
{
   ADSPResult result = ADSP_EOK;
   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)(_pif);
   uint32_t in_samples_present = input->buf_ptr[0].actual_data_len / sizeof(int16_t); // Sample count from one channel should be sufficient

   // First verify that all pointers sent in are good.
   // The macro used does this only on simulation and not
   // on target, to not affect performance
   QURT_ELITE_ASSERT(me_ptr);
   QURT_ELITE_ASSERT(input);
   QURT_ELITE_ASSERT(output);
   QURT_ELITE_ASSERT(me_ptr->num_channels <= input->bufs_num);
   QURT_ELITE_ASSERT(me_ptr->num_channels <= output->bufs_num);


   if(me_ptr->bitspersample == 16)
   {
	   // Sample count from one channel should be sufficient
	   uint32_t num_samples = s32_min_s32_s32(
	         input->buf_ptr[0].actual_data_len>>1,
	         output->buf_ptr[0].max_data_len>>1); //bytes per sample is 2 for 16-bit processing

	   // Data pointers and sizes
	   int16_t* lin_ptr16=NULL;
	   int16_t* rin_ptr16=NULL;
	   int16_t* lout_ptr16=NULL;
	   int16_t* rout_ptr16=NULL;

	   lin_ptr16  = (int16_t*)input->buf_ptr[0].data_ptr;
	   lout_ptr16 = (int16_t*)output->buf_ptr[0].data_ptr;
	   if (2 == me_ptr->num_channels)
	   {
		  rin_ptr16  = (int16_t*)input->buf_ptr[1].data_ptr;
		  rout_ptr16 = (int16_t*)output->buf_ptr[1].data_ptr;
	   }

	   // Primary processing
#ifndef GAIN_FLOAT_ALGO
	   gain_16bits(lin_ptr16,
			 rin_ptr16,
			 lout_ptr16,
			 rout_ptr16,
			 me_ptr->gain,
			 me_ptr->num_channels,
			 num_samples);
#else
	   gain_float(lin_ptr16,
			rin_ptr16,
			lout_ptr16,
			rout_ptr16,
			me_ptr->gain_float,
			me_ptr->num_channels,
			num_samples);
#endif
	   in_samples_present -= num_samples; // Update the number of samples still present in th input buffer

	   // Book keeping variables
	   // Update the actual_data_len for both input and output buffers.
	   // actual_data_len of input buffer is to determine the number of samples consumed by the process method
	   // actual_data_len of output buffer is to determine the number of sample generated by the process method.
	   input->buf_ptr[0].actual_data_len -= in_samples_present<<1;
	   output->buf_ptr[0].actual_data_len = num_samples<<1;
	   if (2 == output->bufs_num)
	   {
		  input->buf_ptr[1].actual_data_len -= in_samples_present<<1;
		  output->buf_ptr[1].actual_data_len = num_samples<<1;
	   }
   }
   else //if(me_ptr->bitspersample != 16) /*24-bit process in 32-bit data width */
   {
	   // Sample count from one channel should be sufficient
	   uint32_t num_samples = s32_min_s32_s32(
	         input->buf_ptr[0].actual_data_len>>2,
	         output->buf_ptr[0].max_data_len>>2); //bytes per sample is 4 for 24-bit & 32-bit processing

	   // Data pointers and sizes
	   int32_t* lin_ptr32=NULL;
	   int32_t* rin_ptr32=NULL;
	   int32_t* lout_ptr32=NULL;
	   int32_t* rout_ptr32=NULL;

	   lin_ptr32  = (int32_t*)input->buf_ptr[0].data_ptr;
	   lout_ptr32 = (int32_t*)output->buf_ptr[0].data_ptr;
	   if (2 == me_ptr->num_channels)
	   {
		  rin_ptr32  = (int32_t*)input->buf_ptr[1].data_ptr;
		  rout_ptr32 = (int32_t*)output->buf_ptr[1].data_ptr;
	   }

	   // Primary processing
	   gain_32bits(lin_ptr32,
			 rin_ptr32,
			 lout_ptr32,
			 rout_ptr32,
			 me_ptr->gain,
			 me_ptr->num_channels,
			 num_samples);

	   in_samples_present -= num_samples; // Update the number of samples still present in th input buffer

	   // Book keeping variables
	   // Update the actual_data_len for both input and output buffers.
	   // actual_data_len of input buffer is to determine the number of samples consumed by the process method
	   // actual_data_len of output buffer is to determine the number of sample generated by the process method.
	   input->buf_ptr[0].actual_data_len -= in_samples_present<<2;
	   output->buf_ptr[0].actual_data_len = num_samples<<2;
	   if (2 == output->bufs_num)
	   {
		  input->buf_ptr[1].actual_data_len -= in_samples_present<<2;
		  output->buf_ptr[1].actual_data_len = num_samples<<2;
	   }
   }

   return result;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_end
  Returns the library to the uninitialized state and frees the memory that
  was allocated by Init(). This function also frees the virtual function
  table.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_end(appi_t* _pif)
{
   if (NULL == _pif)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain End received bad pointer, 0x%lx",(uint32_t)_pif);
      return ADSP_EUNEXPECTED;
   }
   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)(_pif);

   me_ptr->vtbl = NULL;

   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain End done");
   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_set_param
  Sets either a parameter value or a parameter structure containing multiple
  parameters. In the event of a failure, the appropriate error code is
  returned.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_set_param(
      appi_t*               _pif,
      uint32_t              param_id,
      const appi_buf_t*     params_ptr)
{
   if (NULL == _pif)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Set param received bad pointer, 0x%lx",
            (uint32_t)_pif);
      return ADSP_EUNEXPECTED;
   }

   ADSPResult result = ADSP_EOK;
   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)(_pif);

   switch (param_id)
   {
      case APPI_PARAM_ID_ALGORITHMIC_RESET:
         {
            MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Reset");
         }
         break;
      case PARAM_ID_GAIN_CTRL_MASTER_GAIN:
         {
            if (params_ptr->actual_data_len >= sizeof(gain_ctrl_master_gain_t))
            {
               gain_ctrl_master_gain_t *pkt_ptr = (gain_ctrl_master_gain_t*)(params_ptr->data_ptr);
               // set  the fixed point gain value in Q13
               me_ptr->gain= pkt_ptr->master_gain;
               MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Set Gain %ld",me_ptr->gain);
               result = ADSP_EOK;
            }
            else
            {
			   MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Set: Insufficient size, actual_data_len = %lu",params_ptr->actual_data_len);
               result = ADSP_ENEEDMORE;
            }
         }
         break;
      case PARAM_ID_GAIN_CTRL_MASTER_GAIN_FLOAT:
      {
         if (params_ptr->actual_data_len >= sizeof(gain_ctrl_float_master_gain_t))
         {
        	gain_ctrl_float_master_gain_t *pkt_ptr = (gain_ctrl_float_master_gain_t*)(params_ptr->data_ptr);
        	// set the floating point gain value in 32 bits
            me_ptr->gain_float= pkt_ptr->master_gain_float;
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Set Gain %ld",me_ptr->gain_float);
            result = ADSP_EOK;
         }
         else
         {
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Set: Insufficient size, actual_data_len = %lu",params_ptr->actual_data_len);
            result = ADSP_ENEEDMORE;
         }
      }
    	  break;

      default:
         {
			 MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Set: unsupported param ID 0x%lx",param_id);
            result = ADSP_EUNSUPPORTED;
         }
         break;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Set param for 0x%lx done",param_id);
   return result;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_get_param
  Gets either a parameter value or a parameter structure containing multiple
  parameters. In the event of a failure, the appropriate error code is
  returned.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_get_param(
      appi_t*               _pif,
      uint32_t              param_id,
      appi_buf_t*           params_ptr)
{
   if (NULL == _pif
         || NULL == params_ptr)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Get param received bad pointer, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)params_ptr);
      return ADSP_EUNEXPECTED;
   }

   ADSPResult result = ADSP_EOK;
   appi_gain_ctrl_struct* me_ptr = (appi_gain_ctrl_struct*)(_pif);

   uint32_t delay=0;     // Delay in number of samples, depending on internal states of the library.

   switch (param_id)
   {
      case APPI_PARAM_ID_ALGORITHMIC_DELAY:
         {
            uint32_t* delay_ptr = (uint32_t*)(params_ptr->data_ptr);
            *delay_ptr = delay;
			params_ptr->actual_data_len = sizeof(uint32_t);
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Delay Get %ld",delay);
         }
         break;

      case PARAM_ID_GAIN_CTRL_MASTER_GAIN:
         {
            if (params_ptr->max_data_len >= sizeof(gain_ctrl_master_gain_t))
            {
               gain_ctrl_master_gain_t *pkt_ptr = (gain_ctrl_master_gain_t*)(params_ptr->data_ptr);
               pkt_ptr->master_gain = me_ptr->gain;
               params_ptr->actual_data_len = sizeof(gain_ctrl_master_gain_t);
               MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Get %ld",me_ptr->gain);
               result = ADSP_EOK;
            }
            else
            {
				MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Get: Insufficient size, max_data_len = %lu",params_ptr->max_data_len);
               result = ADSP_ENEEDMORE;
            }
         }
         break;

      case PARAM_ID_GAIN_CTRL_MASTER_GAIN_FLOAT:
         {
            if (params_ptr->max_data_len >= sizeof(gain_ctrl_float_master_gain_t))
            {
            	gain_ctrl_float_master_gain_t *pkt_ptr = (gain_ctrl_float_master_gain_t*)(params_ptr->data_ptr);
               pkt_ptr->master_gain_float = (uint64_t)me_ptr->gain_float;
               params_ptr->actual_data_len = sizeof(gain_ctrl_float_master_gain_t);
               MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Get %ld",me_ptr->gain_float);
               result = ADSP_EOK;
            }
            else
            {
				MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Get: Insufficient size, max_data_len = %lu",params_ptr->max_data_len);
               result = ADSP_ENEEDMORE;
            }
         }
         break;

      case APPI_PARAM_ID_PROCESS_CHECK:
         if (params_ptr->max_data_len >= sizeof(uint32_t))
         {
            uint32_t *process_check_ptr = (uint32_t*)(params_ptr->data_ptr);
            *process_check_ptr = 1;
#ifndef GAIN_FLOAT_ALGO
            // No need to do processing for unity gain (in Q13)
            if (8192 == me_ptr->gain)
            {
               *process_check_ptr = 0;
            }
#else
            // No need to do processing for unity floating point gain (1.0)
            if (0x3F800000 == me_ptr->gain_float)
            {
               *process_check_ptr = 0;
            }
#endif
            params_ptr->actual_data_len = sizeof(uint32_t);
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Process check, %lu",*process_check_ptr);
         }
         else
         {
			 MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Process check: Insufficient size, max_data_len =  %lu",params_ptr->max_data_len);
            result = ADSP_ENEEDMORE;
         }
         break;

      default:
         {
			 MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Gain Get: unsupported param ID 0x%lx",param_id);
            result = ADSP_EUNSUPPORTED;
         }
         break;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Gain Get param for 0x%lx done",param_id);
   return result;
}

/*------------------------------------------------------------------------
  Function name: appi_gain_ctrl_get_input_req
  Gets the number of input samples needed to produce a certain number of
  output samples. If the library has internal buffering, it can take into
  account the state of its buffers and return the appropriate size.
  Notes;
  - No steady state debug messages (prints) allowed in this function
 * -----------------------------------------------------------------------*/
static ADSPResult appi_gain_ctrl_get_input_req(
      appi_t*               _pif,
      const uint32_t        output_size,
      uint32_t*             input_size_ptr)
{
   QURT_ELITE_ASSERT(_pif);
   QURT_ELITE_ASSERT(input_size_ptr);

   // This algorithm does not need any buffering
   *input_size_ptr = output_size;

   return ADSP_EOK;
}

static bool_t is_supported_media_type(const appi_format_t *format_ptr)
{
   if (format_ptr->bits_per_sample != 16 && format_ptr->bits_per_sample != 32)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Only 16 or 32 bit data supported. Received %lu.", format_ptr->bits_per_sample);
      return FALSE;
   }

   if (format_ptr->data_is_interleaved)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Interleaved data not supported.");
      return FALSE;
   }

   if (!format_ptr->data_is_signed)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Unsigned data not supported.");
      return FALSE;
   }

   switch(format_ptr->num_channels)
   {
   case 0:
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Zero channels passed.");
      return FALSE;
   case 1:
      if (PCM_CHANNEL_C != format_ptr->channel_type[0])
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Unsupported channel mapping.");
         return FALSE;
      }
      break;
   case 2:
      if ((PCM_CHANNEL_L != format_ptr->channel_type[0]) || (PCM_CHANNEL_R != format_ptr->channel_type[1]))
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Unsupported channel mapping.");
         return FALSE;
      }
      break;
   default:
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE GAIN: Only upto 2 channels supported. Received %lu.", format_ptr->num_channels);
      return FALSE;
   }

   return TRUE;
}
