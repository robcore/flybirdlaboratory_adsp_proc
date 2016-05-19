/*============================================================================
 *                       INCLUDE FILES FOR MODULE
 *==========================================================================*/
#include "Voice_Delay.h"
#include "adsp_vparams_api.h"

/* -------------------------------------------------------------*/
/* Macro definitions   Constant / Define Declarations           */
/* -------------------------------------------------------------*/
#define ROUNDTO8(x) ((((uint32_t)(x) + 7) >> 3) << 3)
#define MAX_DELAY_TIME 20000                                //measured by microsecond
#define NB_SAMPLING_RATE 8000                               //measured by Hz
#define WB_SAMPLING_RATE 16000                              //measured by Hz

#define NB_FRAME_SAMPLES NB_SAMPLING_RATE/100               //NB samples for 10ms framesize
#define WB_FRAME_SAMPLES WB_SAMPLING_RATE/100               //WB samples for 10ms framesize

#define SHIFT_QFACTOR 15                                    //16Q15 data format,  data multiplied by 2^15
#define NB_TIME_TO_SAMP_CONV_FACTOR 262                     //This macro value represent 0.008 in Q15. i.e. number of samples per micro second which is 0.008 = (8000 * 10^-6) for NB. 
#define NB_SAMP_TO_TIME_CONV_FACTOR 125                     //This macro value represent how many microsecond for 1 sample
#define NB_ROUND_OFFSET 124                                 //(time+124us) for round purpose, NB case 

#define CONVERT_TIME_TO_NBSAMPLES(time)  (int32_t)((NB_TIME_TO_SAMP_CONV_FACTOR)*(time+NB_ROUND_OFFSET)>>(SHIFT_QFACTOR))     //the function to convert time to number of samples for NB

static const uint32_t MOD_DELAY_ENABLE_PARAM_SIZE=sizeof(uint32_t);     // 1 16bit for enable/disable mark; 1 16bit for Reserve          
static const uint32_t DELAY_PARAM_SIZE=6*sizeof(int16_t);  	            // 1 16bit for number of channels; 4 16bit for 4 channel delay time; 1 16bit for Reserve

static const uint32_t VOICE_DELAY_EXAMPLE_KPPS = 500; //Rough Value

/* -----------------------------------------------------------------------
** Function prototypes
** ----------------------------------------------------------------------- */
void voice_delay_default(voice_delay_t *delay_struct_ptr);
ADSPResult voice_delay_reinit(voice_delay_t *delay_struct_ptr);

/* =======================================================================
**                          Function Definitions
** ======================================================================= */
//-----------configure the sampling rate, number of channels etc. in delay module
void voice_delay_config(voice_delay_t *delay_struct_ptr, 
                        int32_t sampling_rate, 
                        int32_t num_channels, 
                        int32_t bits_per_channel)
{
   delay_struct_ptr->sampling_rate = sampling_rate;
   delay_struct_ptr->num_channels = num_channels;
   delay_struct_ptr->bits_per_channel = bits_per_channel;

   delay_struct_ptr->num_buf_samples = (int16_t)(NB_FRAME_SAMPLES + CONVERT_TIME_TO_NBSAMPLES(MAX_DELAY_TIME));          // Maximum num of samples possible for delay
   if(WB_SAMPLING_RATE==delay_struct_ptr->sampling_rate)                    // for WB, num multiplied by 2                                                    
   {
      delay_struct_ptr->num_buf_samples <<= 1;
   }                                                                     
   // 16bits/sample,   multiply by 2 to convert to size of bytes;   buf_samples need to be round to 8 
   delay_struct_ptr->buf_size   = ((delay_struct_ptr->num_channels)*ROUNDTO8(delay_struct_ptr->num_buf_samples)) << 1;     
} 

//----------default value: the Delay factor(delay time, then convert to number of delay samples)
void voice_delay_default(voice_delay_t *delay_struct_ptr)
{
   int16_t i=0;
   int16_t delay_time[MAX_DELAY_CIRCBUF_CHS]={ 0, 0, 0, 0};                // measured by mircosecond 
   //measured by mircosecond, NO LARGER than MAX_DELAY_TIME,  
   //in principle, should no less than 62.5 mircosecond for WB; 
   //                     no less than 125  mircosecond for NB;     
   //delay_time may result in a fractional value for samples, the code will do the rounding to make the num_delay_samples integer 

   for(i = 0; i < MAX_DELAY_CIRCBUF_CHS; i++)
   {
      delay_struct_ptr->num_delay_samples[i] = (int16_t)(CONVERT_TIME_TO_NBSAMPLES(delay_time[i])); 
      if(WB_SAMPLING_RATE==delay_struct_ptr->sampling_rate)                 // for WB, multiply the number of samples by 2    
      {
         delay_struct_ptr->num_delay_samples[i] <<= 1; 
      }
   }
}

//-----------initialize the Delay structure------
ADSPResult voice_delay_init(voice_delay_t *delay_struct_ptr)
{
   ADSPResult result = ADSP_EOK;
   circbuf_status_enum  result_buf = CIRCBUF_SUCCESS;
   int16_t i=0;

   int16_t zero_buf[(NB_FRAME_SAMPLES + CONVERT_TIME_TO_NBSAMPLES(MAX_DELAY_TIME))<<1];
   memset(zero_buf, 0, sizeof(zero_buf));                                    // buffer with zeros, as the src buffer for writing zero to delay samples

   if (MAX_DELAY_CIRCBUF_CHS >= delay_struct_ptr->num_channels)
   {
      delay_struct_ptr->enable = FALSE;                                      // defualt value FALSE, disabled
      voice_delay_default( delay_struct_ptr );

      printf("Initial: Delay structure number of channels: %d\n",delay_struct_ptr->num_channels);
      //-------initialize the circular buffer
      for (i = 0; i < delay_struct_ptr->num_channels; i++)
      {
         if(NULL==&(delay_struct_ptr->circ_buf[i]))
         {
            result = ADSP_EFAILED;
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module Delay circular buffer pointer is NULL, for channel: %d", i);
            break;
         }

         result_buf = voice_circbuf_init((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]),
                                     (int8_t *)(delay_struct_ptr->buf_ptr[i]), 
                                     delay_struct_ptr->num_buf_samples, 
                                     MONO_VOICE,
                                     delay_struct_ptr->bits_per_channel);
         if (CIRCBUF_SUCCESS != result_buf)
         {
            result = ADSP_EFAILED;
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module circ buf init failed, for channel: %d", i);
            break;
         }
         // write zero to the delay samples
         MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Delay samples for channel [%d] is %d", i,  delay_struct_ptr->num_delay_samples[i]);
         printf("Initial: Delay samples for channel [%d] is %d\n", i,  delay_struct_ptr->num_delay_samples[i]);       
         result_buf = voice_circbuf_write((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]), 
                                       (int8_t *)(&zero_buf[0]), delay_struct_ptr->num_delay_samples[i]);         
         if (CIRCBUF_SUCCESS != result_buf)
         {
            result = ADSP_EFAILED;
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module write(set) delay samples to be Zero failed, for channel: %d", i);
            break;
         }
      }
   }
   else
   {
      delay_struct_ptr->num_channels = 0;
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module number of channels larger than maximum");
      result=ADSP_EFAILED;
   }

   return result;
}

//------Process inclue circular buffer write and read
ADSPResult voice_delay_process(voice_delay_t *delay_struct_ptr,
      int8_t *(*src_data_ptr)[MAX_DELAY_CIRCBUF_CHS], 
      int8_t *(*des_data_ptr)[MAX_DELAY_CIRCBUF_CHS], 
      int32_t num_samples_per_ch)
{
   int16_t i;
   ADSPResult result = ADSP_EOK;
   circbuf_status_enum  result_buf = CIRCBUF_SUCCESS;

   if ( TRUE == delay_struct_ptr->enable)
   {
      printf("Process: Delay structure number of channels: %d\n",delay_struct_ptr->num_channels);
      for (i = 0; i <delay_struct_ptr->num_channels; i++)
      {
         if(0 != delay_struct_ptr->num_delay_samples[i])                      // if delay sample not Zero       
         {
            printf("Process: Delay samples for channel [%d] is %d\n", i,  delay_struct_ptr->num_delay_samples[i]);   
            //----Write from Data buffer(Src) to Delay buffer(Des)
            //----Data buffer is normal buffer, Delay buffer is circular buffer
            result_buf = voice_circbuf_write((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]), 
                  (int8_t *)(*src_data_ptr)[i], num_samples_per_ch);          // SrcData is int16_t, convert the data type
            if (CIRCBUF_SUCCESS != result_buf)
            {
               MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module Write error, for channel: %d, num_samples_per_ch:%d", i, num_samples_per_ch);
               result=ADSP_EFAILED;
               break;
            }
            //----Read from Delay buffer(Src) to Data buffer(Des)
            //----Data buffer is normal buffer, Delay buffer is circular buffer
            result_buf = voice_circbuf_read((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]),
                  (int8_t *)(*des_data_ptr)[i], num_samples_per_ch);
            if (CIRCBUF_SUCCESS != result_buf)
            {
               MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module Read error, for channel: %d, num_samples_per_ch: %d", i, num_samples_per_ch);
               result=ADSP_EFAILED;
               break;
            }
         }
         else                                                                          // if delay sample is Zero
         {
            if( ((int8_t *)(*src_data_ptr)[i]) != ((int8_t *)(*des_data_ptr)[i]) )     // if src and dest address not the same: memcpy ;  else do nothing 
            {
               memcpy((*des_data_ptr)[i], (*src_data_ptr)[i], (num_samples_per_ch<<1));
            }
         }
      }
      printf("**************Voice TX Delay Module is enabled**************************\n");
   }
   return result;
}

uint32_t voice_delay_get_size(voice_delay_t *delay_struct_ptr)
{
   return (uint32_t)delay_struct_ptr->buf_size;
}

ADSPResult voice_delay_set_mem(voice_delay_t *delay_struct_ptr, int8_t *mem_addr_ptr, uint32_t mem_size)
{
   int16_t i=0;
   ADSPResult result = ADSP_EOK;

   if(delay_struct_ptr->buf_size <= mem_size)
   {
      for(i=0; i<(delay_struct_ptr->num_channels); i++)      
      {
         delay_struct_ptr->buf_ptr[i] = mem_addr_ptr;
         mem_addr_ptr+= delay_struct_ptr->num_buf_samples<<1;      
      }
   }
   else
   {
      result = ADSP_EFAILED;
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay Module Set Memory Failed: Size error\n");
   }

   return result;
}

ADSPResult voice_delay_reinit(voice_delay_t *delay_struct_ptr)
{
   ADSPResult result = ADSP_EOK;
   circbuf_status_enum  result_buf = CIRCBUF_SUCCESS;
   int16_t i=0;

   int16_t zero_buf[(NB_FRAME_SAMPLES + CONVERT_TIME_TO_NBSAMPLES(MAX_DELAY_TIME))<<1];
   memset(zero_buf, 0, sizeof(zero_buf));

   for ( i = 0; i < delay_struct_ptr->num_channels; i++)
   {
      //----reset the circular buffer, ignore the previous unread data
      result_buf = voice_circbuf_reset((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]));
      if (CIRCBUF_SUCCESS != result_buf)
      {
         result = ADSP_EFAILED;
         MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module SET PARAM Reset failed, for channel: %d", i);
         break;
      }
      //----Write from Zero_buffer to Delay buffer, make all delay samples to be 0
      result_buf = voice_circbuf_write((circbuf_struct *)&(delay_struct_ptr->circ_buf[i]), 
                                    (int8_t *)(&zero_buf[0]), delay_struct_ptr->num_delay_samples[i]);         
      if (CIRCBUF_SUCCESS != result_buf)
      {
         result = ADSP_EFAILED;
         MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module SET PARAM set delay samples to be Zero failed, for channel: %d", i);
         break;
      }
   }
   return result;
}


ADSPResult voice_delay_set_param(voice_delay_t *delay_struct_ptr,
                                 int8_t *params_buffer_ptr, 
                                 uint32_t param_id, 
                                 uint16_t param_size )
{
   ADSPResult result = ADSP_EOK;
   uint16_t *param_ptr = (uint16_t *)params_buffer_ptr;        // unint16_t in case user give negative value parameter
   int16_t i=0;
   uint16_t delaytime=0;

   if ( VOICE_PARAM_MOD_ENABLE == param_id )                   // Set the Enable/Disable status of this module
   {
      if (MOD_DELAY_ENABLE_PARAM_SIZE != param_size)
      {
         result = ADSP_EBADPARAM;
         return result;
      }
      delay_struct_ptr->enable = *param_ptr;
   }
   else if ( VOICE_PARAM_DELAY == param_id )                   // Set the parameter for calibrated Delay time/Delay samples
   {
      if ( DELAY_PARAM_SIZE < param_size )                     // if the calibration parameter size is larger than the maximum parameter size possible, return
      {
         result = ADSP_EBADPARAM;
         return result;
      }

      delay_struct_ptr->num_channels = *param_ptr++;            // 1st parameter is number of channel
      printf("Set Param: Delay structure number of channels: %d\n",delay_struct_ptr->num_channels);
      for(i = 0; i < (delay_struct_ptr->num_channels); i++)   
      {
         delaytime = *param_ptr++;                             // 2nd-5th parameter is delay time for each channel
         printf("Set Param: Delay time for channel[%d]: %d\n", i,delaytime);
         if(delaytime > MAX_DELAY_TIME)
         {
            result = ADSP_EBADPARAM;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "vptx Delay module error: Delay time for ch %d larger for maximum possible %d",i,MAX_DELAY_TIME);
         }
         else
         {
            delay_struct_ptr->num_delay_samples[i] = (int16_t)(CONVERT_TIME_TO_NBSAMPLES(delaytime));
            if(WB_SAMPLING_RATE==delay_struct_ptr->sampling_rate)
            {
               delay_struct_ptr->num_delay_samples[i] <<= 1; 
            }
            printf("Set Param: Delay samples for channel[%d]: %d\n", i, delay_struct_ptr->num_delay_samples[i] );
         }
      }
   }
   else
   {
      result = ADSP_EBADPARAM;
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Voice_Delay_set_param: Bad Parameter");
   }

   if ((ADSP_EOK == result ) && ( TRUE == delay_struct_ptr->enable))
   {
      voice_delay_reinit(delay_struct_ptr);
   }

   return result;
}

ADSPResult voice_delay_get_param(voice_delay_t *delay_struct_ptr,
                                 int8_t *params_buffer_ptr,
                                 uint32_t param_id,
                                 int32_t inp_param_buf_size,                 
                                 uint16_t *param_size_ptr )
{
   ADSPResult result = ADSP_EOK;
   uint16_t *param_ptr = (uint16_t *)params_buffer_ptr;
   int16_t i=0;
   int16_t delaytime=0;

   if( VOICE_PARAM_MOD_ENABLE == param_id)
   {
      if(MOD_DELAY_ENABLE_PARAM_SIZE <= inp_param_buf_size)
      {
         *param_ptr = delay_struct_ptr->enable;
         *param_size_ptr = MOD_DELAY_ENABLE_PARAM_SIZE;
      }
      else
      {
         result = ADSP_EBADPARAM;
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Voice_Delay_get_param: Insufficient BufLength");
      }
   }
   else if( VOICE_PARAM_DELAY == param_id)
   {
      if(DELAY_PARAM_SIZE <= inp_param_buf_size)                   
      {
         *param_ptr++ = delay_struct_ptr->num_channels;                 //give the number of channels to the parameter buffer
         for(i=0; i<(delay_struct_ptr->num_channels); i++)
         {
            delaytime = (int32_t)((delay_struct_ptr->num_delay_samples[i])*NB_SAMP_TO_TIME_CONV_FACTOR);  //125=1/0.008  :  ((delay_sample)<<15)/(0.008*2^15)
            if(WB_SAMPLING_RATE==delay_struct_ptr->sampling_rate)    //for WB, divid the delaytime by 2
            {
               delaytime >>= 1; 
            }
            *param_ptr++ = delaytime;
         }
         *param_size_ptr = DELAY_PARAM_SIZE;
      }
      else
      {
         result = ADSP_EBADPARAM;
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Voice_Delay_get_param: Insufficient BufLength");
      }
   }
   else
   {
      result = ADSP_EBADPARAM;
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Voice_Delay_get_param: Bad Parameter");
   }

   return result;
}

ADSPResult voice_delay_get_kpps(voice_delay_t *delay_struct_ptr, uint32_t *kpps_ptr)
{
	   if(NULL == delay_struct_ptr || NULL == kpps_ptr)
	   {
	      return ADSP_EBADPARAM;
	   }
	   delay_struct_ptr->kpps = VOICE_DELAY_EXAMPLE_KPPS;
	   *kpps_ptr = delay_struct_ptr->kpps;

	   return ADSP_EOK;
}
