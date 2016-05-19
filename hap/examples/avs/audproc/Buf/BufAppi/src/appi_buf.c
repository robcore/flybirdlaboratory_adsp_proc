/* ======================================================================== */
/**
@file appi_buf.c

   Source file to implement the Audio Post Processor Interface for
   locally buffering input signal before sending out
*/

/* =========================================================================
  Copyright (c) 2011 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================= */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   11/03/11	  SD	  Media format checking added in init and reinit
   11/04/10   ss      Source for APPI wrapper
   ======================================================================== */

/*------------------------------------------------------------------------
 * Include files
 * -----------------------------------------------------------------------*/
#include "appi_buf.h"
#include "appi_buf_utils.h"
#include "adsp_media_fmt.h"

/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_reinit(
      appi_t*               _pif,
      const appi_format_t*  in_format_ptr,
      appi_format_t*        out_format_ptr,
      appi_buf_t*           info_ptr);

static ADSPResult appi_buf_process(
      appi_t*               _pif,
      const appi_buflist_t* input,
      appi_buflist_t*       output,
      appi_buf_t*           info_ptr);

static ADSPResult appi_buf_end(
      appi_t*               _pif);

static ADSPResult appi_buf_set_param(
      appi_t*               _pif,
      uint32_t              param_id,
      const appi_buf_t*     params_ptr);

static ADSPResult appi_buf_get_param(
      appi_t*               _pif,
      uint32_t              param_id,
      appi_buf_t*           params_ptr);

static ADSPResult appi_buf_get_input_req(
      appi_t*               _pif,
      const uint32_t        output_size,
      uint32_t*             input_size_ptr);

static const appi_vtbl_t vtbl =
{
   appi_buf_reinit,
   appi_buf_process,
   appi_buf_end,
   appi_buf_set_param,
   appi_buf_get_param,
   appi_buf_get_input_req
};

static bool_t is_supported_media_type(const appi_format_t *format_ptr);

/*------------------------------------------------------------------------
  Function name: appi_buf_getsize
  Returns the memory required by this associated structure/algorithm.
 * -----------------------------------------------------------------------*/
ADSPResult appi_buf_getsize(
      const appi_buf_t* params_ptr,
      uint32_t* size_ptr)
{
   if (NULL == size_ptr)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Getsize received bad pointer, 0x%lx",
            (uint32_t)size_ptr);
      return ADSP_EUNEXPECTED;
   }

   // Each block must begin with 8-byte aligned memory. Here we have 3 blocks
   *size_ptr = align_to_8_byte(sizeof(appi_buf_struct))
      + align_to_8_byte(alg_buffer_size)
      + align_to_8_byte(alg_buffer_size);

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Getsize done, requires %lu bytes",*size_ptr);
   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_init
  Initialize the APPI library. This function can allocate memory.
 * -----------------------------------------------------------------------*/
ADSPResult appi_buf_init(
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
      MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Init received bad pointer, 0x%lx, 0x%lx, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)is_inplace_ptr, (uint32_t)in_format_ptr, (uint32_t)out_format_ptr);
      return ADSP_EUNEXPECTED;
   }

   if (!is_supported_media_type(in_format_ptr))
   {
      return ADSP_EUNSUPPORTED;
   }

   // Based on what has been requested by getsize function, memory has been
   // allocated for
   //   - appi_buf_struct
   //   - coeffs
   int8_t* ptr = (int8_t*)_pif;
   appi_buf_struct* me_ptr = (appi_buf_struct*)ptr;

   ptr += align_to_8_byte(sizeof(appi_buf_struct));
   me_ptr->local_in_buf_ptr = (int16_t*)ptr;

   ptr += align_to_8_byte(alg_buffer_size);
   me_ptr->local_out_buf_ptr = (int16_t*)ptr;

   me_ptr->vtbl = &vtbl;

   me_ptr->samples_in_local_in_buf = 0;
   me_ptr->samples_in_local_out_buf = 0;

   // Set default output data format (determined by internal algorithm)
   out_format_ptr->num_channels        = in_format_ptr->num_channels;
   out_format_ptr->bits_per_sample     = in_format_ptr->bits_per_sample;
   out_format_ptr->sampling_rate       = in_format_ptr->sampling_rate;
   out_format_ptr->data_is_signed      = in_format_ptr->data_is_signed;
   out_format_ptr->data_is_interleaved = in_format_ptr->data_is_interleaved;

   // Copy format to internal structure
   me_ptr->num_channels                = in_format_ptr->num_channels;

   // Check for support
   if (1 == in_format_ptr->data_is_interleaved
         || 2 < in_format_ptr->num_channels)
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Reinit, Data format unsupported");
      return ADSP_EUNSUPPORTED;
   }

   // Report if in-place is supported by this algorithm
   // If it is supported, the same buffer may be sent down
   // for optimal performance
   *is_inplace_ptr = FALSE;

   MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Init done with outformat %lu,%lu,%lu,%lu,%lu",
         out_format_ptr->num_channels,
         out_format_ptr->bits_per_sample,
         out_format_ptr->sampling_rate,
         out_format_ptr->data_is_signed,
         out_format_ptr->data_is_interleaved);

   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_reinit
  Reinitialize the APPI library. This function can optionally allocate
  memory. The state is dependent on the media type information, such as the
  sampling rate.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_reinit(
      appi_t*               _pif,
      const appi_format_t*  in_format_ptr,
      appi_format_t*        out_format_ptr,
      appi_buf_t*           info_ptr)
{
   if (NULL == _pif
         || NULL == in_format_ptr
         || NULL == out_format_ptr)
   {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Reinit received bad pointer, 0x%lx, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)in_format_ptr, (uint32_t)out_format_ptr);
      return ADSP_EUNEXPECTED;
   }

   if (!is_supported_media_type(in_format_ptr))
   {
      return ADSP_EUNSUPPORTED;
   }

   appi_buf_struct* me_ptr = (appi_buf_struct*)(_pif);

   // Set output data format (determined by internal algorithm)
   out_format_ptr->num_channels        = in_format_ptr->num_channels;
   out_format_ptr->bits_per_sample     = in_format_ptr->bits_per_sample;
   out_format_ptr->sampling_rate       = in_format_ptr->sampling_rate;
   out_format_ptr->data_is_signed      = in_format_ptr->data_is_signed;
   out_format_ptr->data_is_interleaved = in_format_ptr->data_is_interleaved;

   // Copy format to internal structure
   me_ptr->num_channels                = in_format_ptr->num_channels;

   // Check for support
   if (1 == in_format_ptr->data_is_interleaved
         || 2 < in_format_ptr->num_channels)
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Reinit, Data format unsupported");
      return ADSP_EUNSUPPORTED;
   }

   MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Reinit done with outformat %lu,%lu,%lu,%lu,%lu",
         out_format_ptr->num_channels,
         out_format_ptr->bits_per_sample,
         out_format_ptr->sampling_rate,
         out_format_ptr->data_is_signed,
         out_format_ptr->data_is_interleaved);

   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_process
  Processes an input buffer and generates an output buffer.
  Assumes Stereo, for this example
  Notes;
  - No steady state debug messages (prints) allowed in this function
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_process(
      appi_t*               _pif,
      const appi_buflist_t* input,
      appi_buflist_t*       output,
      appi_buf_t*           info_ptr)
{
   ADSPResult result = ADSP_EOK;
   appi_buf_struct* me_ptr = (appi_buf_struct*)(_pif);

   // First verify that all pointers sent in are good.
   // The macro used does this only on simulation and not
   // on target, to not affect performance
   QURT_ELITE_ASSERT(me_ptr);
   QURT_ELITE_ASSERT(input);
   QURT_ELITE_ASSERT(output);
   QURT_ELITE_ASSERT(me_ptr->num_channels <= input->bufs_num);
   QURT_ELITE_ASSERT(me_ptr->num_channels <= output->bufs_num);

   // Data pointers
   // Sample count from one channel should be sufficient
   int16_t* lin_ptr =NULL;
   int16_t* rin_ptr =NULL;
   int16_t* lout_ptr =NULL;
   int16_t* rout_ptr =NULL;

   lin_ptr  = (int16_t*)input->buf_ptr[0].data_ptr;
   lout_ptr = (int16_t*)output->buf_ptr[0].data_ptr;
   if (2 == me_ptr->num_channels)
   {
      rin_ptr  = (int16_t*)input->buf_ptr[1].data_ptr;
      rout_ptr = (int16_t*)output->buf_ptr[1].data_ptr;
   }

   uint32_t in_samples_present = input->buf_ptr[0].actual_data_len / sizeof(int16_t); // Sample count from one channel should be sufficient
   uint32_t out_samples_needed = output->buf_ptr[0].max_data_len / sizeof(int16_t); // Sample count from one channel should be sufficient

   // If the input or output buffers are larger than the process size, 
   // then it is possible to process in iterations until the input buffer 
   // is consumed or the output buffer is full (and leftover data is stored 
   // in the internal buffers).
   // In the comments below - 
   // APPI Input buffer means the input buffer to the APPI process function
   // APPI Output buffer means the output buffer to the APPI process function
   // Local Input buffer means the locally held input buffer
   // Local Output buffer means the locally held output buffer
   do
   {
      // Empty as much of the local output buffer as possible
      {
         uint32_t copy_size;
         if (me_ptr->samples_in_local_out_buf >= out_samples_needed)
         {
            // If space left in APPI Output buffer is smaller than or 
            // equal to local output buffer
            copy_size = out_samples_needed;  
         }
         else
         {
            // If APPI Output buffer is larger than Local temp Output buffer
            copy_size = me_ptr->samples_in_local_out_buf;
         }

         // This indicates how much space is left in the local out-buffer for a refill, copy accordingly
         uint32_t local_out_buf_offset = alg_process_size - me_ptr->samples_in_local_out_buf;
         memcpy(lout_ptr, me_ptr->local_out_buf_ptr + local_out_buf_offset, copy_size * sizeof(int16_t));
         lout_ptr += copy_size;
         if (2 == me_ptr->num_channels)
         {
            memcpy(rout_ptr, me_ptr->local_out_buf_ptr + local_out_buf_offset + alg_process_size, copy_size * sizeof(int16_t));
            rout_ptr += copy_size;
         }

         // Subract the amount copied from the APPI output buffer
         out_samples_needed -= copy_size;
         // Update the local output buffer filled up mark (in the buffer, until this mark - there is data)
         me_ptr->samples_in_local_out_buf -= copy_size;
      }

      // Fill as much of the local input buffer as possible
      {
         uint32_t copy_size;
         uint32_t space_in_local_in_buf = alg_process_size - me_ptr->samples_in_local_in_buf;

         if (space_in_local_in_buf >= in_samples_present)
         {
            // If APPI Input buffer is smaller than or equal to Local temp Input buffer
            copy_size = in_samples_present;
         }
         else
         {
            // If APPI Input buffer is larger than Local temp Input buffer
            copy_size = space_in_local_in_buf;
         }

         // Copy input data into temporary input buffer, remember that previous input
         // would already be present here - so copy from that point.
         memcpy(me_ptr->local_in_buf_ptr + me_ptr->samples_in_local_in_buf, lin_ptr, copy_size * sizeof(int16_t));
         lin_ptr += copy_size;
         if (2 == me_ptr->num_channels)
         {
            memcpy(me_ptr->local_in_buf_ptr + me_ptr->samples_in_local_in_buf + alg_process_size, rin_ptr, copy_size * sizeof(int16_t));
            rin_ptr += copy_size;
         }
         // Subract the amount copied from the APPI input buffer
         in_samples_present -= copy_size;
         // Update the local input buffer filled up mark (in the buffer, until this mark - there is data)
         me_ptr->samples_in_local_in_buf += copy_size;
      }

      if ((me_ptr->samples_in_local_in_buf >= alg_process_size) && (me_ptr->samples_in_local_out_buf == 0))
      {
         // ---------------------------------------------------
         // Dear customer: Call your processing function here
         //                instead of "buffer_process" function
         // ---------------------------------------------------
         buffer_process(me_ptr->local_in_buf_ptr,
               me_ptr->local_in_buf_ptr + alg_process_size,
               me_ptr->local_out_buf_ptr,
               me_ptr->local_out_buf_ptr + alg_process_size,
               me_ptr->num_channels);

         // Set state variables accordingly - this basically means
         // alg_process_size amount of output has now been generated
         // in the local output buffer and the local input buffer 
         // needs a refill before further processing
         me_ptr->samples_in_local_in_buf = 0;
         me_ptr->samples_in_local_out_buf = alg_process_size;
      }
      else
      {
         // No processing can be done in either of the two below conditions:
         //     - If number of samples in local input buffer is less than the algorithm processing size requirement 
         //     - The local output buffer is not "completely" available for processing
         break;
      }
   } while (1);

   // Bookkeeping
   input->buf_ptr[0].actual_data_len  -= in_samples_present * sizeof(int16_t);
   output->buf_ptr[0].actual_data_len = output->buf_ptr[0].max_data_len - (out_samples_needed * sizeof(int16_t));
   if (2 == me_ptr->num_channels)
   {
      input->buf_ptr[1].actual_data_len  -= in_samples_present * sizeof(int16_t);
      output->buf_ptr[1].actual_data_len = output->buf_ptr[1].max_data_len - (out_samples_needed * sizeof(int16_t));
   }

   return result;
}
/*------------------------------------------------------------------------
  Function name: appi_buf_end
  Returns the library to the uninitialized state and frees the memory that
  was allocated by Init(). This function also frees the virtual function
  table.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_end(appi_t* _pif)
{
   if (NULL == _pif)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf End received bad pointer, 0x%lx",(uint32_t)_pif);
      return ADSP_EUNEXPECTED;
   }
   appi_buf_struct* me_ptr = (appi_buf_struct*)(_pif);

   me_ptr->vtbl = NULL;

   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf End done");
   return ADSP_EOK;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_set_param
  Sets either a parameter value or a parameter structure containing multiple
  parameters. In the event of a failure, the appropriate error code is
  returned.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_set_param(
      appi_t*               _pif,
      uint32_t              param_id,
      const appi_buf_t*     params_ptr)
{
   if (NULL == _pif
         || NULL == params_ptr)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Set param received bad pointer, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)params_ptr);
      return ADSP_EUNEXPECTED;
   }

   ADSPResult result = ADSP_EOK;

   switch (param_id)
   {
      case APPI_PARAM_ID_ALGORITHMIC_RESET:
         {
            MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Reset");
         }
         break;

      default:
         {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Set, unsupported param ID 0x%lx",param_id);
            result = ADSP_EUNSUPPORTED;
         }
         break;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Set param for 0x%lx done",param_id);
   return result;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_get_param
  Gets either a parameter value or a parameter structure containing multiple
  parameters. In the event of a failure, the appropriate error code is
  returned.
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_get_param(
      appi_t*               _pif,
      uint32_t              param_id,
      appi_buf_t*           params_ptr)
{
   if (NULL == _pif
         || NULL == params_ptr)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Get param received bad pointer, 0x%lx, 0x%lx",
            (uint32_t)_pif, (uint32_t)params_ptr);
      return ADSP_EUNEXPECTED;
   }

   ADSPResult result = ADSP_EOK;

   uint32_t delay=0;     // Delay in number of samples, depending on internal states of the library.

   switch (param_id)
   {
      case APPI_PARAM_ID_ALGORITHMIC_DELAY:
         {
            uint32_t* delay_ptr = (uint32_t*)(params_ptr->data_ptr);
            *delay_ptr = delay;
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Delay Get %ld",delay);
         }
         break;

      case APPI_PARAM_ID_PROCESS_CHECK:
         if (params_ptr->max_data_len >= sizeof(uint32_t))
         {
            uint32_t *process_check_ptr = (uint32_t*)(params_ptr->data_ptr);
            *process_check_ptr = 1;
            params_ptr->actual_data_len = sizeof(uint32_t);
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Process check, %lu",*process_check_ptr);
         }
         else
         {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Process check, Bad param size %lu",params_ptr->max_data_len);
            result = ADSP_ENEEDMORE;
         }
         break;

      default:
         {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"APPI Example Buf Get, unsupported param ID 0x%lx",param_id);
            result = ADSP_EUNSUPPORTED;
         }
         break;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"APPI Example Buf Get param for 0x%lx done",param_id);
   return result;
}

/*------------------------------------------------------------------------
  Function name: appi_buf_get_input_req
  Gets the number of input samples needed to produce a certain number of
  output samples. If the library has internal buffering, it can take into
  account the state of its buffers and return the appropriate size.
  Notes;
  - No steady state debug messages (prints) allowed in this function
 * -----------------------------------------------------------------------*/
static ADSPResult appi_buf_get_input_req(
      appi_t*               _pif,
      const uint32_t        output_size,
      uint32_t*             input_size_ptr)
{
   QURT_ELITE_ASSERT(_pif);
   QURT_ELITE_ASSERT(input_size_ptr);

   appi_buf_struct* me_ptr = (appi_buf_struct*)(_pif);

   // Account for the samples present in the local output buffer
   if (me_ptr->samples_in_local_out_buf >= output_size)
   {
      // Enough samples are present in the output buffer. Let service know that
      // there is no requirement of any input in order to produce the desired 
      // output, as it can already be generated with the available data in the 
      // local output buffer.
      *input_size_ptr = 0;
   }
   else
   {
      // If there is data already present in the local output buffer, then
      // keep track of that during this calculation.
      uint32_t samples_to_be_generated;
      samples_to_be_generated = output_size - me_ptr->samples_in_local_out_buf;

      // Round up to the next multiple of the algorithm's processing size 
      // Note that the processing could be iterated in the process function if 
      // the APPI input/output buffers are larger than the algorithm's
      // processing size.
      uint32_t samples_needed;
      uint32_t remainder = samples_to_be_generated % alg_process_size;
      if (0 == remainder)
      {
         samples_needed = samples_to_be_generated;
      }
      else
      {
         samples_needed = samples_to_be_generated + (alg_process_size - remainder);
      }

      // Account for the samples present in the local input buffer
      // If there is data already present in the local input buffer, and it is
      // greater than what is needed, then just request nothing from the service.
      if (me_ptr->samples_in_local_in_buf >= samples_needed)
      {
         *input_size_ptr = 0;
      }
      else
      {
         *input_size_ptr = samples_needed - me_ptr->samples_in_local_in_buf;
      }
   }

   return ADSP_EOK;
}

static bool_t is_supported_media_type(const appi_format_t *format_ptr)
{
   if (format_ptr->bits_per_sample != 16)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Only 16 bit data supported. Received %lu.", format_ptr->bits_per_sample);
      return FALSE;
   }

   if (format_ptr->data_is_interleaved)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Interleaved data not supported.");
      return FALSE;
   }

   if (!format_ptr->data_is_signed)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Unsigned data not supported.");
      return FALSE;
   }

   switch(format_ptr->num_channels)
   {
   case 0:
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Zero channels passed.");
      return FALSE;
   case 1:
      if (PCM_CHANNEL_C != format_ptr->channel_type[0])
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Unsupported channel mapping.");
         return FALSE;
      }
      break;
   case 2:
      if ((PCM_CHANNEL_L != format_ptr->channel_type[0]) || (PCM_CHANNEL_R != format_ptr->channel_type[1]))
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Unsupported channel mapping.");
         return FALSE;
      }
      break;
   default:
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI EXAMPLE BUF: Only upto 2 channels supported. Received %lu.", format_ptr->num_channels);
      return FALSE;
   }

   return TRUE;
}
