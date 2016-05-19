/*===========================================================================

                  capi_v2 APPI Wrapper

  A wrapper that can be used to translate APPI to capi_v2.

  Copyright (C) 2013-2014 by Qualcomm Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/capi_v2_appi_wrapper/src/capi_v2_appi_wrapper.cpp#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2013/11/18 dg      Created file
===========================================================================*/

#include "capi_v2_appi_wrapper.h"
#include "capi_v2_adsp_error_code_converter.h"
#ifdef CAPI_V2_APPI_WRAPPER_TEST
#include "tst_capi_v2_appi_wrapper.h"
#elif defined CAPI_V2_STANDALONE
#include "capi_v2_util.h"
#include "adsp_media_fmt.h"
#include "adsp_audproc_api.h"
#include "adsp_ds1ap_api.h"
#include "adsp_dts_hpx_api.h"
#else
#include "adsp_audproc_api.h"
#include "adsp_ds1ap_api.h"
#include "adsp_dts_hpx_api.h"
#include "qurt_elite.h"
#include "adsp_media_fmt.h"
#include "audio_basic_op_ext.h"
#endif

static capi_v2_err_t capi_v2_appi_wrapper_process(capi_v2_t* obj_ptr,
			capi_v2_stream_data_t* input[],
			capi_v2_stream_data_t* output[]);
static capi_v2_err_t capi_v2_appi_wrapper_end(capi_v2_t* obj_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_set_param(capi_v2_t* obj_ptr,
			uint32_t param_id, const capi_v2_port_info_t *port_info_ptr,
			capi_v2_buf_t *params_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_get_param(capi_v2_t* obj_ptr,
			uint32_t param_id, const capi_v2_port_info_t *port_info_ptr,
			capi_v2_buf_t *params_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_set_properties(capi_v2_t* obj_ptr,
			capi_v2_proplist_t *props_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_get_properties(capi_v2_t* obj_ptr,
			capi_v2_proplist_t *props_ptr);

struct capi_v2_appi_wrapper_media_type
{
	capi_v2_set_get_media_format_t h;
	capi_v2_standard_data_format_t f;
};

struct capi_v2_appi_wrapper_t
{
	const capi_v2_vtbl_t *vtbl_ptr;

	appi_t *appi_ptr;
	capi_v2_event_callback_info_t cb_info;
	bool_t last_process_check;
	uint32_t last_delay;
    uint32_t last_headroom;
	uint32_t delay_in_us;
	bool_t got_media_type;
	uint32_t input_sampling_rate;
    uint32_t module_id;
	capi_v2_appi_wrapper_media_type output_media_type;
    capi_v2_appi_wrapper_media_type input_media_type;

	// Variables for supporting KPPS and bandwidth events.
	// The get param for KPPS is only done if this variable is TRUE. It is initialized
	// to TRUE. It is set to FALSE when a KPPS query fails. This ensures that if a
	// module does not support KPPS queries, it is not repeatedly queried for it.
	bool_t supports_KPPS;
	// This variable stores the current KPPS value. It is checked with the value returned
	// by the module when a get param call is made for KPPS. An event is raised if the
	// two values are different.
	uint32_t KPPS;

	// The get param for KBPS is only done if this variable is TRUE. It is initialized
	// to TRUE. It is set to FALSE when a KBPS query fails. This ensures that if a
	// module does not support KBPS queries, it is not repeatedly queried for it.
	bool_t supports_KBPS;
	// This variable stores the current KBPS value. It is checked with the value returned
	// by the module when a get param call is made for KBPS. An event is raised if the
	// two values are different.
	uint32_t KBPS;
};

const capi_v2_vtbl_t capi_v2_appi_wrapper_vtbl = {
		capi_v2_appi_wrapper_process,
		capi_v2_appi_wrapper_end,
		capi_v2_appi_wrapper_set_param,
		capi_v2_appi_wrapper_get_param,
		capi_v2_appi_wrapper_set_properties,
		capi_v2_appi_wrapper_get_properties,
};

// Property handlers
static capi_v2_err_t capi_v2_appi_wrapper_set_event_callback(capi_v2_appi_wrapper_t *me_ptr, capi_v2_prop_t *prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_set_port_info(capi_v2_appi_wrapper_t *me_ptr, capi_v2_prop_t *prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_set_algorithmic_reset(capi_v2_appi_wrapper_t *me_ptr, capi_v2_prop_t *prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_set_input_media_type(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_get_output_media_format(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_get_output_media_format_size(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr);
static capi_v2_err_t capi_v2_appi_wrapper_get_port_data_threshold(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr);
// End property handlers

// Events
static void capi_v2_appi_wrapper_events_check(capi_v2_appi_wrapper_t *me_ptr);
static void capi_v2_appi_wrapper_process_check(capi_v2_appi_wrapper_t* me_ptr);
static void capi_v2_appi_wrapper_check_delay(capi_v2_appi_wrapper_t* me_ptr);
static void capi_v2_appi_wrapper_check_KPPS(capi_v2_appi_wrapper_t* me_ptr);
static void capi_v2_appi_wrapper_check_KBPS(capi_v2_appi_wrapper_t* me_ptr);
static void capi_v2_appi_wrapper_update_headroom(capi_v2_appi_wrapper_t *me_ptr);
static void capi_v2_appi_wrapper_media_fmt_update(capi_v2_appi_wrapper_t *me_ptr, bool_t delayed_flag);

static bool_t capi_v2_appi_wrapper_is_supported_media_type(const capi_v2_appi_wrapper_media_type *format_ptr);
static void capi_v2_appi_wrapper_output_media_format_event(capi_v2_appi_wrapper_t *me_ptr);
static int64_t s64_sub_s64_u32_sat(int64_t x, uint32_t y);


static bool_t is_compressed(const capi_v2_set_get_media_format_t *format_header_ptr)
{
	if(format_header_ptr->format_header.data_format == CAPI_V2_IEC61937_PACKETIZED)
	{
		return TRUE;
	}

	return FALSE;
}

uint32_t capi_v2_appi_wrapper_getsize(void)
{
	MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: getsize returning %zd", sizeof(capi_v2_appi_wrapper_t));
	return sizeof(capi_v2_appi_wrapper_t);
}

ADSPResult capi_v2_appi_wrapper_init(capi_v2_t *obj_ptr,
		appi_t* module_ptr,
		capi_v2_proplist_t *init_properties,
        const appi_format_t *initial_output_media_format,
        uint32_t module_id)
{
	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Init called.");

	if (NULL == obj_ptr)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: obj_ptr is NULL.");
		return CAPI_V2_EFAILED;
	}

	if (NULL == module_ptr)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: module_ptr is NULL.");
		return CAPI_V2_EFAILED;
	}

	if (NULL == initial_output_media_format)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: initial_output_media_format is NULL.");
		return CAPI_V2_EFAILED;
	}

	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);

	me_ptr->vtbl_ptr = &capi_v2_appi_wrapper_vtbl;
	me_ptr->appi_ptr = module_ptr;
	me_ptr->cb_info.event_cb = NULL;
	me_ptr->cb_info.event_context = NULL;
	me_ptr->last_process_check = TRUE; // By default all algorithms are enabled.
	me_ptr->last_delay = 0; // Default value
	me_ptr->delay_in_us = 0;
	me_ptr->got_media_type = FALSE;
	me_ptr->input_sampling_rate = 0;
	me_ptr->module_id = module_id;
	me_ptr->output_media_type.h.format_header.data_format = CAPI_V2_FIXED_POINT;
	me_ptr->output_media_type.f.bits_per_sample = initial_output_media_format->bits_per_sample;
	me_ptr->output_media_type.f.bitstream_format = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3;
	me_ptr->output_media_type.f.num_channels = initial_output_media_format->num_channels;
	for (uint32_t i = 0; i < initial_output_media_format->num_channels; i++)
	{
		me_ptr->output_media_type.f.channel_type[i] = initial_output_media_format->channel_type[i];
	}
	me_ptr->output_media_type.f.data_interleaving = initial_output_media_format->data_is_interleaved ? CAPI_V2_INTERLEAVED : CAPI_V2_DEINTERLEAVED_UNPACKED;
	me_ptr->output_media_type.f.data_is_signed = initial_output_media_format->data_is_signed;
	me_ptr->output_media_type.f.q_factor = CAPI_V2_DATA_FORMAT_INVALID_VAL;
	switch(initial_output_media_format->bits_per_sample)
	{
	case 16:
		me_ptr->output_media_type.f.q_factor = PCM_16BIT_Q_FORMAT;
		break;
	case 32:
		me_ptr->output_media_type.f.q_factor = ELITE_32BIT_PCM_Q_FORMAT;
		break;
	default:
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Unsupported bits per sample output: %lu. Only 16 and 32 bits supported.", initial_output_media_format->bits_per_sample);
		return CAPI_V2_EUNSUPPORTED;
	}
	me_ptr->output_media_type.f.sampling_rate = initial_output_media_format->sampling_rate;
	me_ptr->last_headroom = 0;
	me_ptr->input_media_type = me_ptr->output_media_type;
	me_ptr->supports_KPPS = TRUE;
	me_ptr->KPPS = UINT32_MAX; // Invalid value. This will be overwritten when the call to get param is made for KPPS.
	me_ptr->supports_KBPS = TRUE;
	me_ptr->KBPS = UINT32_MAX; // Invalid value. This will be overwritten when the call to get param is made for KBPS.

	if (NULL != init_properties)
	{
		for (uint32_t i = 0; i < init_properties->props_num; i++)
		{
			capi_v2_err_t result = CAPI_V2_EOK;
			capi_v2_prop_t *prop_ptr = &init_properties->prop_ptr[i];
			switch(prop_ptr->id)
			{
			case CAPI_V2_EVENT_CALLBACK_INFO:
				result = capi_v2_appi_wrapper_set_event_callback(me_ptr, prop_ptr);
				break;
			case CAPI_V2_PORT_NUM_INFO:
				result = capi_v2_appi_wrapper_set_port_info(me_ptr, prop_ptr);
				break;
			default:
				MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Property id %d unsupported at init. Ignoring.", static_cast<int>(prop_ptr->id));
			}

			if (CAPI_V2_FAILED(result))
			{
				return capi_v2_err_to_adsp_result(result);
			}
		}
	}

	capi_v2_appi_wrapper_events_check(me_ptr);
	capi_v2_appi_wrapper_update_headroom(me_ptr);
	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_set_input_media_type(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr)
{
	if (!prop_ptr->port_info.is_valid)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info invalid; failed in set media type property.");
		return CAPI_V2_EBADPARAM;
	}

	if (!prop_ptr->port_info.is_input_port)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info set to output port; failed in set media type property.");
		return CAPI_V2_EBADPARAM;
	}

	if (0 != prop_ptr->port_info.port_index)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info output port = %lu, only 0 supported; failed in set media type property.", prop_ptr->port_info.port_index);
		return CAPI_V2_EBADPARAM;
	}

	QURT_ELITE_ASSERT(CAPI_V2_INPUT_MEDIA_FORMAT == prop_ptr->id);

	if (sizeof(capi_v2_set_get_media_format_t) > prop_ptr->payload.actual_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Input media type property header has insufficient size %lu. Required size is %zu.", prop_ptr->payload.actual_data_len, sizeof(capi_v2_set_get_media_format_t));
		return CAPI_V2_ENEEDMORE;
	}

	{
		capi_v2_set_get_media_format_t *media_format_header = reinterpret_cast<capi_v2_set_get_media_format_t*>(prop_ptr->payload.data_ptr);

		if ((CAPI_V2_FIXED_POINT != media_format_header->format_header.data_format) && (CAPI_V2_IEC61937_PACKETIZED != media_format_header->format_header.data_format))
		{
			MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Input media type property got data format %lu. Only %lu and %lu supported. Failed.", static_cast<uint32_t>(media_format_header->format_header.data_format), static_cast<uint32_t>(CAPI_V2_FIXED_POINT), static_cast<uint32_t>(CAPI_V2_IEC61937_PACKETIZED));
			return CAPI_V2_EUNSUPPORTED;
		}
	}

	if (sizeof(capi_v2_appi_wrapper_media_type) > prop_ptr->payload.actual_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Input media type property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.actual_data_len, sizeof(capi_v2_standard_data_format_t));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_appi_wrapper_media_type *media_format_ptr = reinterpret_cast<capi_v2_appi_wrapper_media_type*>(prop_ptr->payload.data_ptr);
	me_ptr->input_media_type = *media_format_ptr;

	if (!capi_v2_appi_wrapper_is_supported_media_type(media_format_ptr))
	{
		return CAPI_V2_EUNSUPPORTED;
	}

	ADSPResult result = ADSP_EOK;
	appi_format_t in_format, out_format;
	in_format.bits_per_sample = media_format_ptr->f.bits_per_sample;
	in_format.num_channels = media_format_ptr->f.num_channels;
	for (uint32_t i = 0; i < media_format_ptr->f.num_channels; i++)
	{
		in_format.channel_type[i] = media_format_ptr->f.channel_type[i]; // Converts from 16 bit to 8 bit.
	}

	if (!is_compressed(&media_format_ptr->h))
	{
		in_format.data_is_interleaved = (CAPI_V2_INTERLEAVED == media_format_ptr->f.data_interleaving) ? 1 : 0;
	}
	else
	{
		in_format.data_is_interleaved = 1; // APPIs expect compressed data to be interleaved.
	}
	in_format.data_is_signed = media_format_ptr->f.data_is_signed;
	in_format.sampling_rate = media_format_ptr->f.sampling_rate;

	result = me_ptr->appi_ptr->vtbl_ptr->reinit(me_ptr->appi_ptr, &in_format, &out_format, NULL);

	capi_v2_appi_wrapper_events_check(me_ptr);

	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Reinit returned with error %d.", result);
		return adsp_result_to_capi_v2_err(result);
	}

	me_ptr->input_sampling_rate = in_format.sampling_rate;

	me_ptr->output_media_type.h = media_format_ptr->h;
	me_ptr->output_media_type.f.bitstream_format = media_format_ptr->f.bitstream_format;
	me_ptr->output_media_type.f.num_channels = out_format.num_channels;
	me_ptr->output_media_type.f.bits_per_sample = out_format.bits_per_sample;

	if (!is_compressed(&me_ptr->output_media_type.h))
	{
		switch(out_format.bits_per_sample)
		{
		case 16:
			me_ptr->output_media_type.f.q_factor = PCM_16BIT_Q_FORMAT;
			break;
		case 32:
			me_ptr->output_media_type.f.q_factor = ELITE_32BIT_PCM_Q_FORMAT;
			break;
		default:
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Unsupported bits per sample output: %lu. Only 16 and 32 bits supported.", out_format.bits_per_sample);
			return CAPI_V2_EUNSUPPORTED;
		}
	}
	else
	{
		me_ptr->output_media_type.f.q_factor = media_format_ptr->f.q_factor;
	}
	me_ptr->output_media_type.f.sampling_rate = out_format.sampling_rate;
	me_ptr->output_media_type.f.data_is_signed = out_format.data_is_signed;
	me_ptr->output_media_type.f.data_interleaving = out_format.data_is_interleaved ? CAPI_V2_INTERLEAVED : CAPI_V2_DEINTERLEAVED_UNPACKED;
	for (uint32_t i = 0; i < me_ptr->output_media_type.f.num_channels; i++)
	{
		me_ptr->output_media_type.f.channel_type[i] = out_format.channel_type[i]; // Converts from 8 bit to 16 bit
	}

	capi_v2_appi_wrapper_output_media_format_event(me_ptr);
	capi_v2_appi_wrapper_update_headroom(me_ptr);

	MSG_8(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Media change done, output: bitstream_format %lu, data_format %lu, num_channels %lu, bits_per_sample %lu, q_factor %lu, sampling_rate %lu, data_is_signed %lu, data_interleaving %lu",
			me_ptr->output_media_type.f.bitstream_format,
			static_cast<uint32_t>(me_ptr->output_media_type.h.format_header.data_format),
			me_ptr->output_media_type.f.num_channels,
			me_ptr->output_media_type.f.bits_per_sample,
			me_ptr->output_media_type.f.q_factor,
			me_ptr->output_media_type.f.sampling_rate,
			me_ptr->output_media_type.f.data_is_signed,
			static_cast<uint32_t>(me_ptr->output_media_type.f.data_interleaving));

	if (is_compressed(&me_ptr->output_media_type.h))
	{
		// Send the format ID
		appi_buf_t buf;
		uint32_t format = me_ptr->output_media_type.f.bitstream_format;
		buf.actual_data_len = buf.max_data_len = sizeof(format);
		buf.data_ptr = reinterpret_cast<int8_t*>(&format);

		result = me_ptr->appi_ptr->vtbl_ptr->set_param(me_ptr->appi_ptr, APPI_PARAM_ID_COMPRESSED_FORMAT, &buf);
		if (CAPI_V2_FAILED(result))
		{
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Setting compressed format returned with error %d.", result);
			return adsp_result_to_capi_v2_err(result);
		}

		capi_v2_appi_wrapper_events_check(me_ptr);
	}

	me_ptr->got_media_type = TRUE;

	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_process(capi_v2_t* obj_ptr,
		capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[])
{
	/*
	 * While creating the APPI and setting up the wrapper, the client must know whether
	 * the input and output sizes are always equal for this APPI (regardless of the output
	 * size required). If this is true it can specify that this APPI when wrapper with the CAPIv2
	 * wrapper will not need data buffering. Otherwise, it must specify that it will need buffering.
	 * In this function, we don't need to worry about it since if the APPI needs buffering it will
	 * be done by the upper layer and if it does not then the wrapper need not do it either. So
	 * the wrapper needs no buffering in either case.
	 */

	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);

	if (!me_ptr->got_media_type)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Process called without media type being set. Returning error.");
		return CAPI_V2_EFAILED;
	}

	appi_buflist_t in_buflist, out_buflist;
	appi_buf_t in_buf[APPI_MAX_CHANNELS], out_buf[APPI_MAX_CHANNELS];

	for (uint32_t i = 0; i < input[0]->bufs_num; i++)
	{
		in_buf[i].actual_data_len = input[0]->buf_ptr[i].actual_data_len;
		in_buf[i].max_data_len = input[0]->buf_ptr[i].max_data_len;
		in_buf[i].data_ptr = input[0]->buf_ptr[i].data_ptr;
	}
	in_buflist.bufs_num = input[0]->bufs_num;
	in_buflist.buf_ptr = in_buf;

	for (uint32_t i = 0; i < output[0]->bufs_num; i++)
	{
		out_buf[i].actual_data_len = output[0]->buf_ptr[i].actual_data_len;
		out_buf[i].max_data_len = output[0]->buf_ptr[i].max_data_len;
		out_buf[i].data_ptr = output[0]->buf_ptr[i].data_ptr;
	}
	out_buflist.bufs_num = output[0]->bufs_num;
	out_buflist.buf_ptr = out_buf;

	ADSPResult result = me_ptr->appi_ptr->vtbl_ptr->process(me_ptr->appi_ptr, &in_buflist, &out_buflist, NULL);
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Process returned with error %d.", result);
		return adsp_result_to_capi_v2_err(result);
	}
    if(me_ptr->module_id == AUDPROC_MODULE_ID_VIRTUALIZER)
        capi_v2_appi_wrapper_media_fmt_update(me_ptr, TRUE);

    if(me_ptr->module_id == AUDPROC_MODULE_ID_POPLESS_EQUALIZER)
    {
        capi_v2_appi_wrapper_events_check(me_ptr);
        capi_v2_appi_wrapper_update_headroom(me_ptr);
    }

	for (uint32_t i = 0; i < input[0]->bufs_num; i++)
	{
		input[0]->buf_ptr[i].actual_data_len = in_buf[i].actual_data_len;
	}

	for (uint32_t i = 0; i < output[0]->bufs_num; i++)
	{
		output[0]->buf_ptr[i].actual_data_len = out_buf[i].actual_data_len;
	}

	output[0]->flags = input[0]->flags;
	// Just calculate the output timestamp regardless of whether the timestamp is valid. It's not worth checking for validity.
	output[0]->timestamp = s64_sub_s64_u32_sat(input[0]->timestamp, me_ptr->delay_in_us);

	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_end(capi_v2_t* obj_ptr)
{
	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: End called.");
	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);
	(void) me_ptr->appi_ptr->vtbl_ptr->end(me_ptr->appi_ptr);
	me_ptr->vtbl_ptr = NULL;
	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_set_param(capi_v2_t* obj_ptr,
		uint32_t param_id, const capi_v2_port_info_t *port_info_ptr, capi_v2_buf_t* params_ptr)
{
	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);

	appi_buf_t buf;
	buf.actual_data_len = params_ptr->actual_data_len;
	buf.max_data_len = params_ptr->max_data_len;
	buf.data_ptr = params_ptr->data_ptr;

	ADSPResult result = me_ptr->appi_ptr->vtbl_ptr->set_param(me_ptr->appi_ptr, param_id, &buf);
	capi_v2_appi_wrapper_events_check(me_ptr);
	capi_v2_appi_wrapper_update_headroom(me_ptr);
	if ((me_ptr->module_id == AUDPROC_MODULE_ID_DTS_HPX_PREMIX) ||
		(me_ptr->module_id == AUDPROC_MODULE_ID_DTS_HPX_POSTMIX))
		capi_v2_appi_wrapper_media_fmt_update(me_ptr, FALSE);
	return adsp_result_to_capi_v2_err(result);
}

static capi_v2_err_t capi_v2_appi_wrapper_get_param(capi_v2_t* obj_ptr,
		uint32_t param_id, const capi_v2_port_info_t *port_info_ptr, capi_v2_buf_t* params_ptr)
{
	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);

	appi_buf_t buf;
	buf.actual_data_len = params_ptr->actual_data_len;
	buf.max_data_len = params_ptr->max_data_len;
	buf.data_ptr = params_ptr->data_ptr;

	ADSPResult result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr, param_id, &buf);

	params_ptr->actual_data_len = buf.actual_data_len;

	return adsp_result_to_capi_v2_err(result);
}

static capi_v2_err_t capi_v2_appi_wrapper_set_properties(capi_v2_t* obj_ptr,
		capi_v2_proplist_t* props_ptr)
{
	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);
	capi_v2_err_t result = CAPI_V2_EOK;

	for (uint32_t i = 0; i < props_ptr->props_num; i++)
	{
		capi_v2_prop_t *prop_ptr = &props_ptr->prop_ptr[i];
		switch(prop_ptr->id)
		{
		case CAPI_V2_ALGORITHMIC_RESET:
			result = capi_v2_appi_wrapper_set_algorithmic_reset(me_ptr, prop_ptr);
			break;
		case CAPI_V2_EVENT_CALLBACK_INFO:
			result = capi_v2_appi_wrapper_set_event_callback(me_ptr, prop_ptr);
			break;
		case CAPI_V2_PORT_NUM_INFO:
			result = capi_v2_appi_wrapper_set_port_info(me_ptr, prop_ptr);
			break;
		case CAPI_V2_INPUT_MEDIA_FORMAT:
			result = capi_v2_appi_wrapper_set_input_media_type(me_ptr, prop_ptr);
			break;
		default:
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Property id %d unsupported. Ignoring.", static_cast<int>(prop_ptr->id));
		}

		if (CAPI_V2_FAILED(result))
		{
			break;
		}
	}

	capi_v2_appi_wrapper_events_check(me_ptr);

	return result;
}

static capi_v2_err_t capi_v2_appi_wrapper_get_properties(capi_v2_t* obj_ptr,
		capi_v2_proplist_t* props_ptr)
{
	capi_v2_appi_wrapper_t *me_ptr = reinterpret_cast<capi_v2_appi_wrapper_t*>(obj_ptr);
	capi_v2_err_t result = CAPI_V2_EOK;

	for (uint32_t i = 0; i < props_ptr->props_num; i++)
	{
		capi_v2_prop_t *prop_ptr = &props_ptr->prop_ptr[i];
		switch(prop_ptr->id)
		{
		case CAPI_V2_OUTPUT_MEDIA_FORMAT_SIZE:
			result = capi_v2_appi_wrapper_get_output_media_format_size(me_ptr, prop_ptr);
			break;
		case CAPI_V2_OUTPUT_MEDIA_FORMAT:
			result = capi_v2_appi_wrapper_get_output_media_format(me_ptr, prop_ptr);
			break;
		case CAPI_V2_PORT_DATA_THRESHOLD:
			result = capi_v2_appi_wrapper_get_port_data_threshold(me_ptr, prop_ptr);
			break;
		default:
			MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Property id %d unsupported for get properties.", static_cast<int>(prop_ptr->id));
			prop_ptr->payload.actual_data_len = 0;
			result = CAPI_V2_EUNSUPPORTED;
			break;
		}

		if (CAPI_V2_FAILED(result))
		{
			break;
		}
	}

	return result;
}

static capi_v2_err_t capi_v2_appi_wrapper_set_event_callback(
		capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr)
{
	QURT_ELITE_ASSERT(CAPI_V2_EVENT_CALLBACK_INFO == prop_ptr->id);

	if (sizeof(capi_v2_event_callback_info_t) > prop_ptr->payload.actual_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Event callback info property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.actual_data_len, sizeof(capi_v2_event_callback_info_t));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_event_callback_info_t *cb_info_ptr = reinterpret_cast<capi_v2_event_callback_info_t*>(prop_ptr->payload.data_ptr);
	me_ptr->cb_info = *cb_info_ptr;

	MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Callback pointer set.");
	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_set_port_info(
		capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr) {
	QURT_ELITE_ASSERT(CAPI_V2_PORT_NUM_INFO == prop_ptr->id);

	if (sizeof(capi_v2_port_num_info_t) > prop_ptr->payload.actual_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.actual_data_len, sizeof(capi_v2_port_info_t));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_port_num_info_t *port_info_ptr = reinterpret_cast<capi_v2_port_num_info_t*>(prop_ptr->payload.data_ptr);
	if ((1 != port_info_ptr->num_input_ports)
			|| (1 != port_info_ptr->num_output_ports))
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Exactly 1 input and 1 output is supported. %lu inputs and %lu outputs unsupported.", port_info_ptr->num_input_ports, port_info_ptr->num_output_ports);
		return CAPI_V2_EUNSUPPORTED;
	}

	return CAPI_V2_EOK;
}

static capi_v2_err_t capi_v2_appi_wrapper_set_algorithmic_reset(capi_v2_appi_wrapper_t *me_ptr, capi_v2_prop_t *prop_ptr)
{
	QURT_ELITE_ASSERT(CAPI_V2_ALGORITHMIC_RESET == prop_ptr->id);

	appi_buf_t buf;
	buf.actual_data_len = buf.max_data_len = 0;
	buf.data_ptr = NULL;

	ADSPResult result = me_ptr->appi_ptr->vtbl_ptr->set_param(me_ptr->appi_ptr, APPI_PARAM_ID_ALGORITHMIC_RESET, &buf);

	return adsp_result_to_capi_v2_err(result);
}

static void capi_v2_appi_wrapper_process_check(capi_v2_appi_wrapper_t* me_ptr)
{
   QURT_ELITE_ASSERT(NULL != me_ptr->cb_info.event_cb);

   ADSPResult result = ADSP_EOK;
   appi_buf_t buf;
   uint32_t process_check_u32 = 0;
   buf.actual_data_len = buf.max_data_len = sizeof(process_check_u32);
   buf.data_ptr = reinterpret_cast<int8_t*>(&process_check_u32);
   result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr,
   APPI_PARAM_ID_PROCESS_CHECK, &buf);
   if (ADSP_FAILED(result))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "CAPI_V2 to APPI wrapper: Failed to get process check. Enabling algorithm.");
      process_check_u32 = 1;
   }
   else if (buf.actual_data_len < sizeof(process_check_u32))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "CAPI_V2 to APPI wrapper: Failed to get enough data for process check. Enabling algorithm.");
      process_check_u32 = 1;
   }

   bool_t process_check = (0 == process_check_u32) ? FALSE : TRUE;
   if (process_check != me_ptr->last_process_check)
   {
      // Raise an event
      capi_v2_event_process_state_t event;
      event.is_enabled = process_check;
      capi_v2_event_info_t event_info;
      event_info.port_info.is_valid = false;
      event_info.payload.actual_data_len = event_info.payload.max_data_len =
            sizeof(event);
      event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&event);
      result = me_ptr->cb_info.event_cb(me_ptr->cb_info.event_context,
            CAPI_V2_EVENT_PROCESS_STATE, &event_info);
      if (ADSP_FAILED(result))
      {
         MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
               "CAPI_V2 to APPI wrapper: Failed to send process update event with %d",
               result);
      }
      else
      {
         me_ptr->last_process_check = process_check;
      }
   }
}

static void capi_v2_appi_wrapper_check_delay(capi_v2_appi_wrapper_t* me_ptr)
{
   ADSPResult result = ADSP_EOK;
   appi_buf_t buf;
   uint32_t delay = 0;
   buf.actual_data_len = buf.max_data_len = sizeof(delay);
   buf.data_ptr = reinterpret_cast<int8_t*>(&delay);
   result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr,
   APPI_PARAM_ID_ALGORITHMIC_DELAY, &buf);
   if (ADSP_FAILED(result))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "CAPI_V2 to APPI wrapper: Failed to get delay, setting to zero.");
      delay = 0;
   }
   else if (buf.actual_data_len < sizeof(delay))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "CAPI_V2 to APPI wrapper: Failed to get enough data for delay. Setting to zero.");
      delay = 0;
   }

   if (me_ptr->got_media_type)
   {
      uint64_t delay_in_us_64 = delay * uint64_t(1000000)
            / me_ptr->input_sampling_rate;
      uint32_t delay_in_us_32 =
            (delay_in_us_64 > UINT32_MAX) ? UINT32_MAX : delay_in_us_64;

      if (delay_in_us_32 != me_ptr->last_delay)
      {
         // Raise an event if needed
         if (NULL != me_ptr->cb_info.event_cb)
         {
            capi_v2_event_algorithmic_delay_t event;
            event.delay_in_us = delay_in_us_32;
            capi_v2_event_info_t event_info;
            event_info.port_info.is_valid = false;
            event_info.payload.actual_data_len =
                  event_info.payload.max_data_len = sizeof(event);
            event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&event);
            capi_v2_err_t err_code = me_ptr->cb_info.event_cb(
                  me_ptr->cb_info.event_context,
                  CAPI_V2_EVENT_ALGORITHMIC_DELAY, &event_info);
            if (CAPI_V2_FAILED(err_code))
            {
               MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                     "CAPI_V2 to APPI wrapper: Failed to send delay update event with %d",
                     static_cast<int>(err_code));
            }
            else
            {
               me_ptr->last_delay = delay_in_us_32;
            }
         }

         me_ptr->delay_in_us = delay_in_us_32;
      }
   }
}

static void capi_v2_appi_wrapper_events_check(capi_v2_appi_wrapper_t *me_ptr)
{
	if (NULL != me_ptr->cb_info.event_cb)
	{
      capi_v2_appi_wrapper_process_check(me_ptr);
      capi_v2_appi_wrapper_check_KPPS(me_ptr);
      capi_v2_appi_wrapper_check_KBPS(me_ptr);
	}

	// Delay must be queried always, since it is needed for timestamp updates.
   capi_v2_appi_wrapper_check_delay(me_ptr);
}
static bool_t capi_v2_appi_wrapper_is_supported_media_type(const capi_v2_appi_wrapper_media_type *format_ptr)
{
	QURT_ELITE_ASSERT((format_ptr->h.format_header.data_format == CAPI_V2_FIXED_POINT) || (format_ptr->h.format_header.data_format == CAPI_V2_IEC61937_PACKETIZED));

	if (!is_compressed(&format_ptr->h))
	{
		if ((format_ptr->f.bitstream_format != ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2)
				&& (format_ptr->f.bitstream_format != ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3))
		{
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Only PCM bitstream supported for FIXED_POINT data. Got bitstream format %lx", format_ptr->f.bitstream_format);
			return FALSE;
		}

		if (format_ptr->f.bits_per_sample == 16)
		{
			if (format_ptr->f.q_factor != PCM_16BIT_Q_FORMAT)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: 16 bit PCM data requires Q factor %d, but %lu was set.", PCM_16BIT_Q_FORMAT, format_ptr->f.q_factor);
				return FALSE;
			}
		}
		if (format_ptr->f.bits_per_sample == 32)
		{
			if (format_ptr->f.q_factor != ELITE_32BIT_PCM_Q_FORMAT)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: 32 bit PCM data requires Q factor %d, but %lu was set.", ELITE_32BIT_PCM_Q_FORMAT, format_ptr->f.q_factor);
				return FALSE;
			}
		}
	}

	if ((0 == format_ptr->f.num_channels) || (format_ptr->f.num_channels > APPI_MAX_CHANNELS))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Invalid channel count %lu.", format_ptr->f.num_channels);
		return FALSE;
	}

	return TRUE;
}

static void capi_v2_appi_wrapper_check_KPPS(capi_v2_appi_wrapper_t* me_ptr)
{
   QURT_ELITE_ASSERT(NULL != me_ptr->cb_info.event_cb);

   if (me_ptr->supports_KPPS)
   {
      ADSPResult result = ADSP_EOK;
      appi_buf_t buf;
      uint32_t KPPS = 0;
      buf.actual_data_len = buf.max_data_len = sizeof(KPPS);
      buf.data_ptr = reinterpret_cast<int8_t*>(&KPPS);
      result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr,
            APPI_PARAM_ID_KPPS, &buf);
      if (ADSP_FAILED(result))
      {
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
               "CAPI_V2 to APPI wrapper: Failed to get KPPS. No further queries will be made.");
         me_ptr->supports_KPPS = FALSE;
         return;
      }
      else if (buf.actual_data_len < sizeof(KPPS))
      {
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
               "CAPI_V2 to APPI wrapper: Failed to get enough data for KPPS. No further queries will be made.");
         me_ptr->supports_KPPS = FALSE;
         return;
      }

      if (KPPS != me_ptr->KPPS)
      {
         // Raise an event
         capi_v2_event_KPPS_t event;
         event.KPPS = KPPS;
         capi_v2_event_info_t event_info;
         event_info.port_info.is_valid = false;
         event_info.payload.actual_data_len = event_info.payload.max_data_len =
         sizeof(event);
         event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&event);
         result = me_ptr->cb_info.event_cb(me_ptr->cb_info.event_context,
               CAPI_V2_EVENT_KPPS, &event_info);
         if (ADSP_FAILED(result))
         {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                  "CAPI_V2 to APPI wrapper: Failed to send KPPS update event with %d",
                  result);
         }
         else
         {
            me_ptr->KPPS = KPPS;
         }
      }
   }
}

static uint32_t capi_v2_appi_wrapper_KBPS_to_BPS(uint32_t KBPS)
{
   if (KBPS <= UINT32_MAX / 1000)
   {
      return (KBPS * 1000);
   }
   else
   {
      return UINT32_MAX;
   }
}

static void capi_v2_appi_wrapper_check_KBPS(capi_v2_appi_wrapper_t* me_ptr)
{
   QURT_ELITE_ASSERT(NULL != me_ptr->cb_info.event_cb);

   if (me_ptr->supports_KBPS)
   {
      ADSPResult result = ADSP_EOK;
      appi_buf_t buf;
      uint32_t KBPS = 0;
      buf.actual_data_len = buf.max_data_len = sizeof(KBPS);
      buf.data_ptr = reinterpret_cast<int8_t*>(&KBPS);
      result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr,
      APPI_PARAM_ID_KBPS, &buf);
      if (ADSP_FAILED(result))
      {
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
               "CAPI_V2 to APPI wrapper: Failed to get KBPS. No further queries will be made.");
         me_ptr->supports_KBPS = FALSE;
         return;
      }
      else if (buf.actual_data_len < sizeof(KBPS))
      {
         MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
               "CAPI_V2 to APPI wrapper: Failed to get enough data for KBPS. No further queries will be made.");
         me_ptr->supports_KBPS = FALSE;
         return;
      }

      if (KBPS != me_ptr->KBPS)
      {
         // Raise an event
         capi_v2_event_bandwidth_t event;
         event.code_bandwidth = 0;
         event.data_bandwidth = capi_v2_appi_wrapper_KBPS_to_BPS(KBPS);
         capi_v2_event_info_t event_info;
         event_info.port_info.is_valid = false;
         event_info.payload.actual_data_len = event_info.payload.max_data_len =
               sizeof(event);
         event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&event);
         result = me_ptr->cb_info.event_cb(me_ptr->cb_info.event_context,
               CAPI_V2_EVENT_BANDWIDTH, &event_info);
         if (ADSP_FAILED(result))
         {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                  "CAPI_V2 to APPI wrapper: Failed to send bandwidth update event with %d",
                  result);
         }
         else
         {
            me_ptr->KBPS = KBPS;
         }
      }
   }
}

// Function to subtract an unsigned 32 bit value from a signed 64 bit value with saturation. It returns a signed 64 bit value.
static int64_t s64_sub_s64_u32_sat(int64_t x, uint32_t y)
{
	if (x >= 0)
	{
		return x - y;
	}
	else if((INT64_MIN - x) < -int64_t(y)) // Mathematically same as x - y > INT64_MIN
	{
		return x - y;
	}
	else
	{
		return INT64_MIN;
	}
}

static void capi_v2_appi_wrapper_output_media_format_event(capi_v2_appi_wrapper_t *me_ptr)
{
	if (NULL == me_ptr->cb_info.event_cb)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Event callback is not set. Unable to raise media format event!");
		return;
	}

	// Raise an event
	capi_v2_event_info_t event_info;
	event_info.port_info.is_valid = TRUE;
	event_info.port_info.is_input_port = FALSE;
	event_info.port_info.port_index = 0;
	event_info.payload.actual_data_len = event_info.payload.max_data_len = sizeof(me_ptr->output_media_type);
	event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&me_ptr->output_media_type);
	capi_v2_err_t result = me_ptr->cb_info.event_cb(me_ptr->cb_info.event_context, CAPI_V2_EVENT_OUTPUT_MEDIA_FORMAT_UPDATED, &event_info);
	if (CAPI_V2_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Failed to send output media format updated event with %d", result);
	}
}

static capi_v2_err_t capi_v2_appi_wrapper_get_output_media_format(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr)
{
	QURT_ELITE_ASSERT(CAPI_V2_OUTPUT_MEDIA_FORMAT == prop_ptr->id);

	prop_ptr->payload.actual_data_len = 0;

	if (FALSE == prop_ptr->port_info.is_valid)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format get property has invalid port info. Failed.");
		return CAPI_V2_EBADPARAM;
	}

	if (prop_ptr->port_info.is_input_port)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format get property called for input port. Failed.");
		return CAPI_V2_EBADPARAM;
	}

	if (0 != prop_ptr->port_info.port_index)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info output port = %lu, only 0 supported; failed in getting the output media format.", prop_ptr->port_info.port_index);
		return CAPI_V2_EBADPARAM;
	}

	if (sizeof(capi_v2_appi_wrapper_media_type) > prop_ptr->payload.max_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format get property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.max_data_len, sizeof(capi_v2_appi_wrapper_media_type));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_appi_wrapper_media_type *payload_ptr = reinterpret_cast<capi_v2_appi_wrapper_media_type*>(prop_ptr->payload.data_ptr);
	*payload_ptr = me_ptr->output_media_type;
	prop_ptr->payload.actual_data_len = sizeof(capi_v2_appi_wrapper_media_type);

	return CAPI_V2_EOK;

}

static capi_v2_err_t capi_v2_appi_wrapper_get_output_media_format_size(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr)
{
	QURT_ELITE_ASSERT(CAPI_V2_OUTPUT_MEDIA_FORMAT_SIZE == prop_ptr->id);

	prop_ptr->payload.actual_data_len = 0;

	if (FALSE == prop_ptr->port_info.is_valid)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format size get property has invalid port info. Failed.");
		return CAPI_V2_EBADPARAM;
	}

	if (prop_ptr->port_info.is_input_port)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format size get property called for input port. Failed.");
		return CAPI_V2_EBADPARAM;
	}

	if (0 != prop_ptr->port_info.port_index)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port info output port = %lu, only 0 supported; failed in getting the output media format size.", prop_ptr->port_info.port_index);
		return CAPI_V2_EBADPARAM;
	}

	if (sizeof(capi_v2_output_media_format_size_t) > prop_ptr->payload.max_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Output media format size get property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.max_data_len, sizeof(capi_v2_output_media_format_size_t));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_output_media_format_size_t *payload_ptr = reinterpret_cast<capi_v2_output_media_format_size_t*>(prop_ptr->payload.data_ptr);
	payload_ptr->size_in_bytes = sizeof(capi_v2_standard_data_format_t);
	prop_ptr->payload.actual_data_len = sizeof(payload_ptr->size_in_bytes);

	return CAPI_V2_EOK;
}
static capi_v2_err_t capi_v2_appi_wrapper_get_port_data_threshold(capi_v2_appi_wrapper_t* me_ptr, capi_v2_prop_t* prop_ptr)
{
	QURT_ELITE_ASSERT(CAPI_V2_PORT_DATA_THRESHOLD == prop_ptr->id);

	prop_ptr->payload.actual_data_len = 0;

	if (sizeof(capi_v2_port_data_threshold_t) > prop_ptr->payload.max_data_len)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Port data threshold get property has insufficient size %lu. Required size is %zu.", prop_ptr->payload.max_data_len, sizeof(capi_v2_port_data_threshold_t));
		return CAPI_V2_ENEEDMORE;
	}

	capi_v2_port_data_threshold_t *payload_ptr = reinterpret_cast<capi_v2_port_data_threshold_t*>(prop_ptr->payload.data_ptr);
	payload_ptr->threshold_in_bytes = 1;
	prop_ptr->payload.actual_data_len = sizeof(*payload_ptr);

	return CAPI_V2_EOK;
}

static void capi_v2_appi_wrapper_update_headroom(capi_v2_appi_wrapper_t *me_ptr)
{
    if (NULL != me_ptr->cb_info.event_cb)
    {
        // Head-room update
        if(me_ptr->module_id == AUDPROC_MODULE_ID_POPLESS_EQUALIZER)
        {
            ADSPResult result = ADSP_EOK;
            appi_buf_t buf;
            uint32_t headroom_u32 = 0;
            buf.actual_data_len = buf.max_data_len = sizeof(headroom_u32);
            buf.data_ptr = reinterpret_cast<int8_t*>(&headroom_u32);
            result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr, APPI_PARAM_ID_ALGORITHMIC_HEADROOM, &buf);
            if (ADSP_FAILED(result))
            {
                MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Failed to get Headroom. Defaulting to zero.");
                headroom_u32 = 0;
            }
            else if(buf.actual_data_len < sizeof(headroom_u32))
            {
                MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Failed to get enough data for get Headroom. Defaulting to zero.");
                headroom_u32 = 0;
            }
            uint32_t new_headroom = headroom_u32;
            if (new_headroom != me_ptr->last_headroom)
            {
                // Raise an event
                capi_v2_event_headroom_t event;
                event.headroom_in_millibels = new_headroom;
                capi_v2_event_info_t event_info;
                event_info.port_info.is_valid = false;
                event_info.payload.actual_data_len = event_info.payload.max_data_len = sizeof(event);
                event_info.payload.data_ptr = reinterpret_cast<int8_t*>(&event);
                result = me_ptr->cb_info.event_cb(me_ptr->cb_info.event_context, CAPI_V2_EVENT_HEADROOM, &event_info);
                if (ADSP_FAILED(result))
                {
                    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 to APPI wrapper: Failed to send headroom update event with %d", result);
                }
                else
                {
                    me_ptr->last_headroom = new_headroom;
                }
            }
        }
    }
}

static void capi_v2_appi_wrapper_media_fmt_update(capi_v2_appi_wrapper_t *me_ptr, bool_t delayed_flag)
{
    if (NULL != me_ptr->cb_info.event_cb)
    {
        {
            ADSPResult result = ADSP_EOK;
            appi_buf_t buf;
            uint32_t trigger_reinit = 0;
            buf.actual_data_len = buf.max_data_len = sizeof(trigger_reinit);
            buf.data_ptr = reinterpret_cast<int8_t*>(&trigger_reinit);
			if(!delayed_flag)
				result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr, APPI_PARAM_ID_MEDIA_FORMAT_CHANGE, &buf);
			else
				result = me_ptr->appi_ptr->vtbl_ptr->get_param(me_ptr->appi_ptr, APPI_PARAM_ID_DELAYED_MEDIA_FORMAT_CHANGE, &buf);
            if (ADSP_FAILED(result))
            {
                MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Failed to get trigger reinit flag. Defaulting to zero.");
                trigger_reinit = 0;
            }
            else if(buf.actual_data_len < sizeof(trigger_reinit))
            {
                MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 to APPI wrapper: Failed to get trigger reinit flag. Defaulting to zero.");
                trigger_reinit = 0;
            }

            if (trigger_reinit)
            {
                // Raise an event
                capi_v2_prop_t prop = {
                    CAPI_V2_INPUT_MEDIA_FORMAT,
                    {
                        reinterpret_cast<int8_t*>(&me_ptr->input_media_type),
                        sizeof(capi_v2_appi_wrapper_media_type),
                        sizeof(capi_v2_appi_wrapper_media_type)
                    },
                    {
                        TRUE,
                        TRUE,
                        0
                    }
                };
                capi_v2_appi_wrapper_set_input_media_type(me_ptr,&prop);
            }
        }
    }
}

