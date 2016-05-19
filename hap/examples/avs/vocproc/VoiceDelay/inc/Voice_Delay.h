#ifndef __VOICE_DELAY__
#define __VOICE_DELAY__

#include "VoiceCmnUtils.h"

#define MAX_DELAY_CIRCBUF_CHS 4

typedef struct {
   circbuf_struct circ_buf[MAX_DELAY_CIRCBUF_CHS]; 
   int8_t *buf_ptr[MAX_DELAY_CIRCBUF_CHS];
   int16_t num_delay_samples[MAX_DELAY_CIRCBUF_CHS];        //16 bit could support 4.096 second delay for WB & 8.192s delay for NB
   int32_t sampling_rate;
   int32_t num_channels;
   int32_t num_buf_samples;                                 //number of samples in the buffer (frame samples+delay samples)
   int32_t buf_size;                                        //size of the buffer (measured by bytes)
   int32_t bits_per_channel;              
   int16_t enable;                                          //module enable mark
   uint32_t kpps;											// KPPS value
} voice_delay_t;

void voice_delay_config(voice_delay_t *delay_struct_ptr, 
                        int32_t sampling_rate, 
                        int32_t num_channels, 
                        int32_t bits_per_channel);

ADSPResult voice_delay_init(voice_delay_t *delay_struct_ptr);

ADSPResult voice_delay_process(voice_delay_t *delay_struct_ptr,
                                          int8_t *(*src_data_ptr)[MAX_DELAY_CIRCBUF_CHS], 
                                          int8_t *(*des_data_ptr)[MAX_DELAY_CIRCBUF_CHS], 
                                          int32_t num_Samples_per_ch);

uint32_t voice_delay_get_size(voice_delay_t *delay_struct_ptr);

ADSPResult voice_delay_set_mem(voice_delay_t *delay_struct_ptr, 
                              int8_t *mem_addr_ptr, 
                              uint32_t mem_size);

ADSPResult voice_delay_set_param(voice_delay_t *delay_struct_ptr,
                                 int8_t *params_buffer_ptr, 
                                 uint32_t param_id, 
                                 uint16_t param_size );

ADSPResult voice_delay_get_param(voice_delay_t *delay_struct_ptr,
                                 int8_t *params_buffer_ptr,
                                 uint32_t param_id,
                                 int32_t inp_param_buf_size,
                                 uint16_t *param_size_ptr );

ADSPResult voice_delay_get_kpps(voice_delay_t *delay_struct_ptr, uint32_t *kpps_ptr);

#endif//#ifndef __VOICE_DELAY__
