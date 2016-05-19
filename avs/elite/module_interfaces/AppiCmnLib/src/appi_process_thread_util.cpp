/*===========================================================================

  A library to provide a separate processing thread for APPI modules that
  process in fixed sized frames. This library will provide double buffering
  between the main thread used by the post proc service and a processing
  thread in which one frame of data is processed.

  Copyright (C) 2013 by Qualcomm Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/AppiCmnLib/src/appi_process_thread_util.cpp#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2013/09/13 dg      Created file
===========================================================================*/

#include "appi_process_thread_util.h"

#ifndef TST_PROCESS_UTIL
#include "qurt_elite.h"
#include <stringl/stringl.h>
#include "EliteThread_Priority.h"
#endif

#define SIZE_OF_ARRAY(a) (sizeof(a)/sizeof((a)[0]))

//---- Thread object API ----

struct appi_pu_thread_t
{
	qurt_elite_signal_t exit_signal;
	qurt_elite_signal_t process_signal;
	qurt_elite_channel_t process_channel;

	qurt_elite_signal_t done_signal;
	qurt_elite_channel_t done_channel;

	qurt_elite_thread_t thread;
	void (*fn)(void*);
	void *state;
};

static ADSPResult appi_pu_thread_init(appi_pu_thread_t *obj_ptr, void (*fn)(void*), void *state_ptr, uint32_t stack_size);
static void appi_pu_thread_deinit(appi_pu_thread_t *obj_ptr);
static void appi_pu_thread_wait_for_task_done(appi_pu_thread_t *obj_ptr);
static void appi_pu_thread_start_task(appi_pu_thread_t *obj_ptr);

//---- Thread object API end ----

struct _appi_pu_t
{
	appi_t *module_ptr;
	appi_pu_process_fn_t fn;

	uint32_t frame_size_in_bytes;
	uint32_t num_input_buffers;
	uint8_t input_channel_map[APPI_MAX_CHANNELS];
	uint32_t num_output_buffers;
	uint8_t output_channel_map[APPI_MAX_CHANNELS];

	uint32_t buf_offset;
	uint8_t *in_buf_main_thread_ptr[APPI_MAX_CHANNELS];
	uint8_t *out_buf_main_thread_ptr[APPI_MAX_CHANNELS];
	uint8_t *in_buf_proc_thread_ptr[APPI_MAX_CHANNELS];
	uint8_t *out_buf_proc_thread_ptr[APPI_MAX_CHANNELS];

	appi_pu_thread_t th;
};

static void appi_pu_delete_buffers(uint8_t *buf_array[], uint32_t num_elements);
static ADSPResult appi_pu_create_buffers(uint8_t *buf_array[], uint32_t num_elements, uint32_t size);
static void appi_pu_fill_buffers(appi_pu_t *obj_ptr, const appi_buflist_t *input, appi_buflist_t *output, uint32_t *num_bytes_to_fill_ptr, uint32_t total_bytes_to_fill);
static void appi_pu_start_process_frame(appi_pu_t *obj_ptr);
static void appi_pu_th_process(void *state_ptr);
static bool_t appi_pu_is_supported_media_type(uint32_t frame_size_in_bytes,
		uint32_t num_input_buffers,
		const uint8_t input_channel_map[],
		uint32_t num_output_buffers,
		const uint8_t output_channel_map[]);
static bool_t appi_pu_is_buffer_info_same(uint32_t num_bufs1,
		const uint8_t channel_map1[],
		uint32_t num_bufs2,
		const uint8_t channel_map2[]);

static uint32_t appi_pu_calc_proc_size(uint32_t input_size, uint32_t output_size)
{
	return (input_size > output_size) ? output_size : input_size;
}

ADSPResult appi_pu_process(appi_pu_t *obj_ptr,
		const appi_buflist_t* input,
		appi_buflist_t* output)
{
	QURT_ELITE_ASSERT(obj_ptr->num_input_buffers <= input->bufs_num);
	QURT_ELITE_ASSERT(obj_ptr->num_output_buffers <= output->bufs_num);

	uint32_t num_bytes_to_process = appi_pu_calc_proc_size(input->buf_ptr[0].actual_data_len, output->buf_ptr[0].max_data_len);
	uint32_t num_bytes_left = num_bytes_to_process;

	while (num_bytes_left > 0)
	{
		if (obj_ptr->buf_offset == obj_ptr->frame_size_in_bytes)
		{
			appi_pu_start_process_frame(obj_ptr);
		}

		// Fill up as much as possible
		appi_pu_fill_buffers(obj_ptr, input, output, &num_bytes_left, num_bytes_to_process);
	}

	for (uint32_t i = 0; i < obj_ptr->num_input_buffers; i++)
	{
		input->buf_ptr[i].actual_data_len = num_bytes_to_process;
	}

	for (uint32_t i = 0; i < obj_ptr->num_output_buffers; i++)
	{
		output->buf_ptr[i].actual_data_len = num_bytes_to_process;
	}

	return ADSP_EOK;
}

void appi_pu_set_process_function(appi_pu_t *obj_ptr, appi_t *module_ptr, appi_pu_process_fn_t fn)
{
	obj_ptr->module_ptr = module_ptr;
	obj_ptr->fn = fn;
}

static bool_t appi_pu_is_supported_media_type(uint32_t frame_size_in_bytes,
		uint32_t num_input_buffers,
		const uint8_t input_channel_map[],
		uint32_t num_output_buffers,
		const uint8_t output_channel_map[])
{
	if (0 == frame_size_in_bytes)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util unsupported frame size = 0");
		return FALSE;
	}

	if (num_input_buffers > APPI_MAX_CHANNELS)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util unsupported num input buffers = %lu. Max supported = %d", num_input_buffers, APPI_MAX_CHANNELS);
		return FALSE;
	}

	if (num_output_buffers > APPI_MAX_CHANNELS)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util unsupported num output buffers = %lu. Max supported = %d", num_output_buffers, APPI_MAX_CHANNELS);
		return FALSE;
	}

	return TRUE;
}

static bool_t appi_pu_is_buffer_info_same(uint32_t num_bufs1,
		const uint8_t channel_map1[],
		uint32_t num_bufs2,
		const uint8_t channel_map2[])
{
	if (num_bufs1 != num_bufs2)
	{
		return FALSE;
	}

	if (0 != memcmp(channel_map1, channel_map2, num_bufs1 * sizeof(channel_map1[0])))
	{
		return FALSE;
	}

	return TRUE;
}

ADSPResult appi_pu_set_media_type(appi_pu_t *obj_ptr,
		uint32_t frame_size_in_bytes,
		uint32_t num_input_buffers,
		const uint8_t input_channel_map[],
		uint32_t num_output_buffers,
		const uint8_t output_channel_map[])
{
	if (!appi_pu_is_supported_media_type(frame_size_in_bytes,
		num_input_buffers,
		input_channel_map,
		num_output_buffers,
		output_channel_map))
	{
		return ADSP_EUNSUPPORTED;
	}

	if ((obj_ptr->frame_size_in_bytes != frame_size_in_bytes)
			|| !appi_pu_is_buffer_info_same(num_output_buffers, output_channel_map, obj_ptr->num_output_buffers, obj_ptr->output_channel_map))
	{
		appi_pu_wait_for_processing_done(obj_ptr);

		// Delete old buffers
		appi_pu_delete_buffers(obj_ptr->in_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_proc_thread_ptr));
		appi_pu_delete_buffers(obj_ptr->out_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->out_buf_proc_thread_ptr));
		appi_pu_delete_buffers(obj_ptr->in_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_main_thread_ptr));
		appi_pu_delete_buffers(obj_ptr->out_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->out_buf_main_thread_ptr));
		obj_ptr->frame_size_in_bytes = 0;
		obj_ptr->num_input_buffers = 0;
		obj_ptr->num_output_buffers = 0;

		// Create new buffers
		ADSPResult result;
		result = appi_pu_create_buffers(obj_ptr->in_buf_proc_thread_ptr, num_input_buffers, frame_size_in_bytes);
		if (ADSP_FAILED(result))
		{
			MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to allocate input buffers for the proc thread.");
			return result;
		}
		result = appi_pu_create_buffers(obj_ptr->in_buf_main_thread_ptr, num_input_buffers, frame_size_in_bytes);
		if (ADSP_FAILED(result))
		{
			MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to allocate input buffers for the main thread.");
			return result;
		}
		obj_ptr->num_input_buffers = num_input_buffers;
		memscpy(obj_ptr->input_channel_map, sizeof(obj_ptr->input_channel_map), input_channel_map, num_input_buffers * sizeof(input_channel_map[0]));

		result = appi_pu_create_buffers(obj_ptr->out_buf_proc_thread_ptr, num_output_buffers, frame_size_in_bytes);
		if (ADSP_FAILED(result))
		{
			MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to allocate output buffers for the proc thread.");
			return result;
		}
		result = appi_pu_create_buffers(obj_ptr->out_buf_main_thread_ptr, num_output_buffers, frame_size_in_bytes);
		if (ADSP_FAILED(result))
		{
			MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to allocate output buffers for the main thread.");
			return result;
		}
		obj_ptr->num_output_buffers = num_output_buffers;
		memscpy(obj_ptr->output_channel_map, sizeof(obj_ptr->output_channel_map), output_channel_map, num_output_buffers * sizeof(output_channel_map[0]));
		obj_ptr->frame_size_in_bytes = frame_size_in_bytes;

		// Reset the buffers
		appi_pu_reset(obj_ptr);
	}
	else if(!appi_pu_is_buffer_info_same(num_input_buffers, input_channel_map, obj_ptr->num_input_buffers, obj_ptr->input_channel_map))
	{
		// Only the input media type changed. We can retain the output buffers.
		appi_pu_wait_for_processing_done(obj_ptr);

		uint32_t num_input_buffers_old;
		uint8_t input_channel_map_old[APPI_MAX_CHANNELS];
		uint8_t *in_buf_main_thread_ptrs_old[APPI_MAX_CHANNELS];
		uint8_t *in_buf_proc_thread_ptrs_old[APPI_MAX_CHANNELS];

		num_input_buffers_old = obj_ptr->num_input_buffers;
		memscpy(input_channel_map_old, sizeof(input_channel_map_old), obj_ptr->input_channel_map, sizeof(obj_ptr->input_channel_map));
		memscpy(in_buf_main_thread_ptrs_old, sizeof(in_buf_main_thread_ptrs_old), obj_ptr->in_buf_main_thread_ptr, sizeof(obj_ptr->in_buf_main_thread_ptr));
		memset(obj_ptr->in_buf_main_thread_ptr, 0, sizeof(obj_ptr->in_buf_main_thread_ptr));
		memscpy(in_buf_proc_thread_ptrs_old, sizeof(in_buf_proc_thread_ptrs_old), obj_ptr->in_buf_proc_thread_ptr, sizeof(obj_ptr->in_buf_proc_thread_ptr));
		memset(obj_ptr->in_buf_proc_thread_ptr, 0, sizeof(obj_ptr->in_buf_proc_thread_ptr));

		for (uint32_t i = 0; i < num_input_buffers; i++)
		{
			uint32_t old_buffer_index = 0;
			bool_t found = FALSE;
			for (uint32_t j = 0; j < num_input_buffers_old; j++)
			{
				if (input_channel_map[i] == input_channel_map_old[j])
				{
					old_buffer_index = j;
					found = TRUE;
					break;
				}
			}

			if (found)
			{
				obj_ptr->in_buf_main_thread_ptr[i] = in_buf_main_thread_ptrs_old[old_buffer_index];
				in_buf_main_thread_ptrs_old[old_buffer_index] = NULL;
				obj_ptr->in_buf_proc_thread_ptr[i] = in_buf_proc_thread_ptrs_old[old_buffer_index];
				in_buf_proc_thread_ptrs_old[old_buffer_index] = NULL;
			}
			else
			{
				ADSPResult result;
				result = appi_pu_create_buffers(&obj_ptr->in_buf_main_thread_ptr[i], 1, frame_size_in_bytes);
				if (ADSP_FAILED(result))
				{
					appi_pu_delete_buffers(obj_ptr->in_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_proc_thread_ptr));
					appi_pu_delete_buffers(obj_ptr->in_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_main_thread_ptr));
					appi_pu_delete_buffers(in_buf_main_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_main_thread_ptrs_old));
					appi_pu_delete_buffers(in_buf_proc_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_proc_thread_ptrs_old));
					obj_ptr->num_input_buffers = 0;
					return result;
				}
				memset(obj_ptr->in_buf_main_thread_ptr[i], 0, obj_ptr->buf_offset);

				result = appi_pu_create_buffers(&obj_ptr->in_buf_proc_thread_ptr[i], 1, frame_size_in_bytes);
				if (ADSP_FAILED(result))
				{
					appi_pu_delete_buffers(obj_ptr->in_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_proc_thread_ptr));
					appi_pu_delete_buffers(obj_ptr->in_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_main_thread_ptr));
					appi_pu_delete_buffers(in_buf_main_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_main_thread_ptrs_old));
					appi_pu_delete_buffers(in_buf_proc_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_proc_thread_ptrs_old));
					obj_ptr->num_input_buffers = 0;
					return result;
				}
				memset(obj_ptr->in_buf_proc_thread_ptr[i], 0, obj_ptr->buf_offset);
			}

			obj_ptr->input_channel_map[i] = input_channel_map[i];
		}

		obj_ptr->num_input_buffers = num_input_buffers;

		// Delete old buffers
		appi_pu_delete_buffers(in_buf_main_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_main_thread_ptrs_old));
		appi_pu_delete_buffers(in_buf_proc_thread_ptrs_old, SIZE_OF_ARRAY(in_buf_proc_thread_ptrs_old));
	}


	return ADSP_EOK;
}

void appi_pu_reset(appi_pu_t *obj_ptr)
{
	appi_pu_wait_for_processing_done(obj_ptr);

	obj_ptr->buf_offset = 0;
	for (uint32_t i = 0; i < obj_ptr->num_output_buffers; i++)
	{
		memset(obj_ptr->out_buf_main_thread_ptr[i], 0, obj_ptr->frame_size_in_bytes);
		memset(obj_ptr->out_buf_proc_thread_ptr[i], 0, obj_ptr->frame_size_in_bytes);
	}
}

void appi_pu_wait_for_processing_done(appi_pu_t *obj_ptr)
{
	appi_pu_thread_wait_for_task_done(&obj_ptr->th);
}

appi_pu_t *appi_pu_create(uint32_t stack_size)
{
	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "APPI process thread util creating instance structure.");

	appi_pu_t *obj_ptr = (appi_pu_t*)qurt_elite_memory_malloc(sizeof(appi_pu_t), QURT_ELITE_HEAP_DEFAULT);
	if (NULL == obj_ptr)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to allocate memory for the instance structure.");
		return NULL;
	}

	obj_ptr->module_ptr = NULL;
	obj_ptr->fn = NULL;
	obj_ptr->frame_size_in_bytes = 0;
	obj_ptr->num_input_buffers = 0;
	obj_ptr->num_output_buffers = 0;
	obj_ptr->buf_offset = 0;

	for (uint32_t i = 0; i < SIZE_OF_ARRAY(obj_ptr->in_buf_proc_thread_ptr); i++)
	{
		obj_ptr->in_buf_proc_thread_ptr[i] = NULL;
	}

	for (uint32_t i = 0; i < SIZE_OF_ARRAY(obj_ptr->out_buf_proc_thread_ptr); i++)
	{
		obj_ptr->out_buf_proc_thread_ptr[i] = NULL;
	}

	for (uint32_t i = 0; i < SIZE_OF_ARRAY(obj_ptr->in_buf_main_thread_ptr); i++)
	{
		obj_ptr->in_buf_main_thread_ptr[i] = NULL;
	}

	for (uint32_t i = 0; i < SIZE_OF_ARRAY(obj_ptr->out_buf_main_thread_ptr); i++)
	{
		obj_ptr->out_buf_main_thread_ptr[i] = NULL;
	}

	ADSPResult result = appi_pu_thread_init(&obj_ptr->th, appi_pu_th_process, obj_ptr, stack_size);
	if (ADSP_FAILED(result))
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed initialization");
		qurt_elite_memory_free(obj_ptr);
		return NULL;
	}

	return obj_ptr;
}

void appi_pu_destroy(appi_pu_t *obj_ptr)
{
	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "APPI process thread util destroying instance structure.");

	appi_pu_thread_deinit(&obj_ptr->th);

	appi_pu_delete_buffers(obj_ptr->in_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_proc_thread_ptr));
	appi_pu_delete_buffers(obj_ptr->out_buf_proc_thread_ptr, SIZE_OF_ARRAY(obj_ptr->out_buf_proc_thread_ptr));
	appi_pu_delete_buffers(obj_ptr->in_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->in_buf_main_thread_ptr));
	appi_pu_delete_buffers(obj_ptr->out_buf_main_thread_ptr, SIZE_OF_ARRAY(obj_ptr->out_buf_main_thread_ptr));

	obj_ptr->module_ptr = NULL;
	obj_ptr->fn = NULL;
	obj_ptr->frame_size_in_bytes = 0;
	obj_ptr->num_input_buffers = 0;
	obj_ptr->num_output_buffers = 0;
	obj_ptr->buf_offset = 0;

	qurt_elite_memory_free(obj_ptr);
}

static void appi_pu_delete_buffers(uint8_t *buf_array[], uint32_t num_elements)
{
	for (uint32_t i = 0; i < num_elements; i++)
	{
		if (buf_array[i] != NULL)
		{
			qurt_elite_memory_free(buf_array[i]);
		}
		buf_array[i] = NULL;
	}
}

static ADSPResult appi_pu_create_buffers(uint8_t *buf_array[], uint32_t num_elements, uint32_t size)
{
	for (uint32_t i = 0; i < num_elements; i++)
	{
		QURT_ELITE_ASSERT(NULL == buf_array[i]);

		buf_array[i] = (uint8_t*)qurt_elite_memory_malloc(size, QURT_ELITE_HEAP_DEFAULT);
		if (NULL == buf_array[i])
		{
			appi_pu_delete_buffers(buf_array, i);
			return ADSP_ENOMEMORY;
		}
	}

	return ADSP_EOK;
}

static void appi_pu_fill_buffers(appi_pu_t *obj_ptr, const appi_buflist_t *input, appi_buflist_t *output, uint32_t *num_bytes_to_fill_ptr, uint32_t total_bytes_to_fill)
{
	uint32_t copy_size = 0;
	uint32_t external_buf_offset = total_bytes_to_fill - *num_bytes_to_fill_ptr;

	for (uint32_t i = 0; i < obj_ptr->num_input_buffers; i++)
	{
		copy_size = memscpy(obj_ptr->in_buf_main_thread_ptr[i] + obj_ptr->buf_offset,
				obj_ptr->frame_size_in_bytes - obj_ptr->buf_offset,
				input->buf_ptr[i].data_ptr + external_buf_offset,
				*num_bytes_to_fill_ptr);
	}

	for (uint32_t i = 0; i < obj_ptr->num_output_buffers; i++)
	{
		copy_size = memscpy(output->buf_ptr[i].data_ptr + external_buf_offset,
				*num_bytes_to_fill_ptr,
				obj_ptr->out_buf_main_thread_ptr[i] + obj_ptr->buf_offset,
				obj_ptr->frame_size_in_bytes - obj_ptr->buf_offset);
	}

	obj_ptr->buf_offset += copy_size;
	*num_bytes_to_fill_ptr -= copy_size;
}

static void exchange_pointers(uint8_t **p1_ptr, uint8_t **p2_ptr)
{
	uint8_t *tmp_ptr = *p1_ptr;
	*p1_ptr = *p2_ptr;
	*p2_ptr = tmp_ptr;
}

static void appi_pu_start_process_frame(appi_pu_t *obj_ptr)
{
	QURT_ELITE_ASSERT(obj_ptr->frame_size_in_bytes == obj_ptr->buf_offset);

	appi_pu_wait_for_processing_done(obj_ptr);

	for(uint32_t i = 0; i < obj_ptr->num_input_buffers; i++)
	{
		exchange_pointers(&obj_ptr->in_buf_main_thread_ptr[i], &obj_ptr->in_buf_proc_thread_ptr[i]);
	}

	for(uint32_t i = 0; i < obj_ptr->num_output_buffers; i++)
	{
		exchange_pointers(&obj_ptr->out_buf_main_thread_ptr[i], &obj_ptr->out_buf_proc_thread_ptr[i]);
	}

	appi_pu_thread_start_task(&obj_ptr->th);

	obj_ptr->buf_offset = 0;
}

static void appi_pu_th_process(void *state_ptr)
{
	appi_buf_t in_bufs[APPI_MAX_CHANNELS], out_bufs[APPI_MAX_CHANNELS];
	appi_buflist_t in, out;
	appi_pu_t *obj_ptr = reinterpret_cast<appi_pu_t*>(state_ptr);

	in.bufs_num = obj_ptr->num_input_buffers;
	out.bufs_num = obj_ptr->num_output_buffers;
	in.buf_ptr = in_bufs;
	out.buf_ptr = out_bufs;
	for (uint32_t i = 0; i < obj_ptr->num_input_buffers; i++)
	{
		in.buf_ptr[i].actual_data_len = in.buf_ptr[i].max_data_len = obj_ptr->frame_size_in_bytes;
		in.buf_ptr[i].data_ptr = (int8_t*)(obj_ptr->in_buf_proc_thread_ptr[i]);
	}

	for (uint32_t i = 0; i < obj_ptr->num_output_buffers; i++)
	{
		out.buf_ptr[i].actual_data_len = 0;
		out.buf_ptr[i].max_data_len = obj_ptr->frame_size_in_bytes;
		out.buf_ptr[i].data_ptr = (int8_t*)(obj_ptr->out_buf_proc_thread_ptr[i]);
	}

	obj_ptr->fn(obj_ptr->module_ptr, &in, &out);
}

static int appi_pu_thread_task(void *ptr)
{
	appi_pu_thread_t *obj_ptr = reinterpret_cast<appi_pu_thread_t*>(ptr);

	uint32_t exit_mask = qurt_elite_signal_get_channel_bit(&obj_ptr->exit_signal);
	uint32_t process_mask = qurt_elite_signal_get_channel_bit(&obj_ptr->process_signal);
	uint32_t wait_mask = exit_mask | process_mask;

	while (1)
	{
		uint32_t signals = qurt_elite_channel_wait(&obj_ptr->process_channel, wait_mask);
		if (signals & exit_mask)
		{
			MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "APPI process thread util process thread exiting.");
			break;
		}

		if (signals & process_mask)
		{
			obj_ptr->fn(obj_ptr->state);
			qurt_elite_signal_clear(&obj_ptr->process_signal);
			qurt_elite_signal_send(&obj_ptr->done_signal);
		}
	}

	return ADSP_EOK;
}

static ADSPResult appi_pu_thread_init(appi_pu_thread_t *obj_ptr, void (*fn)(void*), void *state_ptr, uint32_t stack_size)
{
	obj_ptr->fn = fn;
	obj_ptr->state = state_ptr;

	ADSPResult result;
	result = qurt_elite_signal_init(&obj_ptr->process_signal);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to create process signal with error %d.", result);
		goto cleanup1;
	}

	result = qurt_elite_signal_init(&obj_ptr->done_signal);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to create process done signal with error %d.", result);
		goto cleanup2;
	}

	result = qurt_elite_signal_init(&obj_ptr->exit_signal);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to create exit signal with error %d.", result);
		goto cleanup3;
	}

	qurt_elite_channel_init(&obj_ptr->process_channel);
	qurt_elite_channel_init(&obj_ptr->done_channel);

	result = qurt_elite_channel_add_signal(&obj_ptr->process_channel, &obj_ptr->process_signal, 0);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to add process signal to channel with error %d.", result);
		goto cleanup4;
	}

	result = qurt_elite_channel_add_signal(&obj_ptr->done_channel, &obj_ptr->done_signal, 0);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to add process done signal to channel with error %d.", result);
		goto cleanup4;
	}

	result = qurt_elite_channel_add_signal(&obj_ptr->process_channel, &obj_ptr->exit_signal, 0);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to add exit signal to channel with error %d.", result);
		goto cleanup4;
	}

	{
		char thread_name[] = "APPI thread";
		const uint32_t stack_size_for_util_fns = 128;
		uint32_t stack_allocation_size = stack_size + stack_size_for_util_fns;
		result = qurt_elite_thread_launch(&obj_ptr->thread, thread_name, NULL, stack_allocation_size, ELITETHREAD_DYNA_PP_SVC_PRIO, appi_pu_thread_task, obj_ptr, QURT_ELITE_HEAP_DEFAULT);
		if (ADSP_FAILED(result))
		{
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPI process thread util failed to launch thread with error %d", result);
			goto cleanup4;
		}
	}

	// Set this signal in the beginning so that the object is in a state of having finished processing.
	qurt_elite_signal_send(&obj_ptr->done_signal);

	return ADSP_EOK;

cleanup4:
	qurt_elite_channel_destroy(&obj_ptr->done_channel);
	qurt_elite_channel_destroy(&obj_ptr->process_channel);
	qurt_elite_signal_deinit(&obj_ptr->exit_signal);
cleanup3:
	qurt_elite_signal_deinit(&obj_ptr->done_signal);
cleanup2:
	qurt_elite_signal_deinit(&obj_ptr->process_signal);
cleanup1:
	return result;
}

static void appi_pu_thread_deinit(appi_pu_thread_t *obj_ptr)
{
	appi_pu_thread_wait_for_task_done(obj_ptr);
	qurt_elite_signal_send(&obj_ptr->exit_signal);

	int status;
	qurt_elite_thread_join(obj_ptr->thread, &status);

	qurt_elite_channel_destroy(&obj_ptr->done_channel);
	qurt_elite_channel_destroy(&obj_ptr->process_channel);
	qurt_elite_signal_deinit(&obj_ptr->exit_signal);
	qurt_elite_signal_deinit(&obj_ptr->done_signal);
	qurt_elite_signal_deinit(&obj_ptr->process_signal);
}

static void appi_pu_thread_wait_for_task_done(appi_pu_thread_t *obj_ptr)
{
	(void) qurt_elite_channel_wait(&obj_ptr->done_channel, qurt_elite_signal_get_channel_bit(&obj_ptr->done_signal));
}

static void appi_pu_thread_start_task(appi_pu_thread_t *obj_ptr)
{
	appi_pu_thread_wait_for_task_done(obj_ptr);
	qurt_elite_signal_clear(&obj_ptr->done_signal);
	qurt_elite_signal_send(&obj_ptr->process_signal);
}
