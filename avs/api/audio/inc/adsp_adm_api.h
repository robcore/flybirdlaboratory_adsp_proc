/*========================================================================*/
/**
@file adsp_adm_api.h

This file contains the structure definitions for Audio Device Manager (ADM) 
commands used in client-ADM communications.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      audio_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
Copyright (c) 2012-2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_adm_api.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                    Doxygen comments/markup for 2.6.
09/06/13   sw      (Tech Pubs) Merged Doxygen comments from 2.0; edited 
                    new Doxygen comments for 2.2.
08/06/12   sw      (Tech Pubs) Edited comments; updated Doxygen markup to
                   Rev D.2 templates; updated legal statements for QTI.
02/15/12   KR      Non-backward compatible API changes for Badger.
02/07/12   KK      Memory map changes for Badger.
02/06/12   KK      Branched to dev/avs2.0 for API development.
========================================================================== */

#ifndef _ADSP_ADM_API_H_
#define _ADSP_ADM_API_H_

#include "mmdefs.h"
#include "adsp_audio_memmap_api.h"
#include "adsp_audproc_api.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


/** @ingroup admsvc_version
    Hexagon ADM version ID.
*/
#define ADSP_ADM_VERSION    0x00070000

/** @ingroup admsvc_cmd_map_shared_mem
    Commands the ADM to map multiple shared memory regions. All mapped regions
    must be from the same memory pool.

  @apr_hdr_fields
    Opcode -- ADM_CMD_SHARED_MEM_MAP_REGIONS
    @par
    Dst_port -- 0000 (Session ID/Stream ID = 0/0)

  @apr_msgpayload{avs_cmd_shared_mem_map_regions_t}
    Immediately following this structure are num_regions of
    %avs_shared_map_region_payload_t (see <b>Map payload</b>).
    @tablens{weak__avs__cmd__shared__mem__map__regions__t}

  @mappayload{avs_shared_map_region_payload_t}
    @table{weak__avs__shared__map__region__payload__t}

  @return
    #ADM_CMDRSP_SHARED_MEM_MAP_REGIONS.

  @dependencies
    None.
*/
#define ADM_CMD_SHARED_MEM_MAP_REGIONS               0x00010322

/* ADM memory map regions command structure is the same as the
    avs memory map regions command structure. */
typedef struct  avs_cmd_shared_mem_map_regions_t adm_cmd_shared_mem_map_regions_t;

/** @ingroup admsvc_resp_map_shared_mem
    Returns the memory map handle in response to the
    #ADM_CMD_SHARED_MEM_MAP_REGIONS command.

  @apr_hdr_fields
    Opcode -- ADM_CMDRSP_SHARED_MEM_MAP_REGIONS
    @par
    Dst_port -- Ignored

  @apr_msgpayload{avs_cmdrsp_shared_mem_map_regions_t}
    @table{weak__avs__cmdrsp__shared__mem__map__regions__t}

  @return
    None.

  @dependencies
    An #ADM_CMD_SHARED_MEM_MAP_REGIONS command must have been issued.
*/
#define ADM_CMDRSP_SHARED_MEM_MAP_REGIONS               0x00010323

/* ADM memory map regions response structure is the same as the
    avs memory map regions response structure. */
typedef struct  avs_cmdrsp_shared_mem_map_regions_t adm_cmdrsp_shared_mem_map_regions_t;

/** @ingroup admsvc_cmd_unmap_shared_mem
    Commands the ADM to unmap multiple shared memory regions that were
    previously mapped.

  @apr_hdr_fields
    Opcode -- ADM_CMD_SHARED_MEM_UNMAP_REGIONS
    @par
    Dst_port -- 0000 (Session ID/Stream ID = 0/0)

  @apr_msgpayload{avs_cmd_shared_mem_unmap_regions_t}
    @table{weak__avs__cmd__shared__mem__unmap__regions__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #ADM_CMD_SHARED_MEM_MAP_REGIONS command must have been
    issued.
*/
/* Q3 = Async Packet Router API Interface Spec for MDM9x15 (80-N1463-2) */
#define ADM_CMD_SHARED_MEM_UNMAP_REGIONS              0x00010324

/* ADM memory unmap regions command structure is the same as the
    avs memory unmap regions command structure. */
typedef struct avs_cmd_shared_mem_unmap_regions_t adm_cmd_shared_mem_unmap_regions_t;

/** @addtogroup admsvc_cmd_update_matrix_map
@{ */
/** Provides updates to the matrix mapping between session IDs and COPP IDs.
    All specified session and COPP IDs must be valid and connected to the
    targeted matrix.

  @apr_hdr_fields
    Opcode -- ADM_CMD_MATRIX_MAP_ROUTINGS_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_matrix_map_routings_v5_t}
    Immediately following this structure are num_sessions of
    %adm_session_map_node_v5_t (see <b>Session map node payload</b>).
    @tablens{weak__adm__cmd__matrix__map__routings__v5__t}

  @par Session map node payload (adm_session_map_node_v5_t)
    @tablens{weak__adm__session__map__node__v5__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    All specified session and COPP IDs must be valid and connected to the
    targeted matrix.
*/
#define ADM_CMD_MATRIX_MAP_ROUTINGS_V5                                 0x00010325

/** Enumeration for an audio Rx matrix ID. */
#define ADM_MATRIX_ID_AUDIO_RX              0

/** Enumeration for an audio Tx matrix ID. */
#define ADM_MATRIX_ID_AUDIO_TX              1

/** @} */ /* end_addtogroup admsvc_cmd_update_matrix_map */

/* Payload of an ADM_CMD_MATRIX_MAP_ROUTINGS_V5 command. */
typedef struct adm_cmd_matrix_map_routings_v5_t adm_cmd_matrix_map_routings_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_matrix_map_routings_v5_t
@{ */
/* Payload of the ADM_CMD_MATRIX_MAP_ROUTINGS_V5 command, which allows a client
    to provide updates to the matrix mapping between session IDs and COPP IDs. 
    Immediately following this structure are num_sessions of
    adm_session_map_node_v5_t.
*/
struct adm_cmd_matrix_map_routings_v5_t
{
    uint32_t                  matrix_id;
    /**< Specifies whether the matrix ID is Audio Rx (0) or Audio Tx (1). 

         @values
         - #ADM_MATRIX_ID_AUDIO_RX
         - #ADM_MATRIX_ID_AUDIO_TX @tablebulletend */

    uint32_t                  num_sessions;
    /**< Number of sessions being updated by this command (optional).

         @values 1 to 8 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_matrix_map_routings_v5_t */

/* Session map node structure. */
typedef struct adm_session_map_node_v5_t adm_session_map_node_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_session_map_node_v5_t
@{ */
/* Payload of the session map node used by ADM_CMD_MATRIX_MAP_ROUTINGS_V5. */
/** Immediately following this structure are num_copps entries of COPP IDs.
    The COPP IDs are 16 bits, so there is another 16-bit field for padding if
    num_copps is an odd number.
*/
struct adm_session_map_node_v5_t
{
    uint16_t                  session_id;
    /**< Handle of the ASM session to be routed.
    
         @values 1 to 8 */

    uint16_t                  num_copps;
    /**< Number of COPPs to which this session is to be routed. 

         @values 0 < num_copps @le ADM_MAX_COPPS */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_session_map_node_v5_t */

/** @addtogroup admsvc_cmd_open_device
@{ */
/** Opens a COPP/voice processing Tx module and sets up the device
    session.
 
    The following configurations are supported (based on the mode_of_operation
    value):
    - Opens an Audio COPP and sets up the device session: 
      Rx matrix @rarrow COPP @rarrow AFE
    - Opens an Audio COPP and sets up the device session: 
      AFE @rarrow COPreP @rarrow Tx matrix (Live mode)
    - Opens an Audio COPP and sets up the device session: 
      AFE @rarrow COPreP @rarrow Tx matrix (Non-live mode)
    - Opens an Audio COPP and sets up the device session: 
      Rx matrix @rarrow COPP @rarrow Tx matrix
    - Sets up the device session: Rx stream router @rarrow AFE
    - Sets up the device session: AFE @rarrow Tx stream router

  @apr_hdr_fields
    Opcode -- ADM_CMD_DEVICE_OPEN_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_device_open_v5_t}
    @table{weak__adm__cmd__device__open__v5__t}

  @keep{5} @return
    #ADM_CMDRSP_DEVICE_OPEN_V5 with the resulting status and COPP ID.

  @dependencies
    None.
*/
#define ADM_CMD_DEVICE_OPEN_V5                          0x00010326

/** Indicates that endpoint_id_1 is to be ignored. */
#define ADM_CMD_COPP_OPEN_END_POINT_ID_1_IGNORE                     0xFFFF

/** Indicates that endpoint_id_2 is to be ignored. */
#define ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE                     0xFFFF

/** Indicates an Rx path COPP. */
#define ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP             1

/** Indicates a Tx path live COPreP.
    @if OEM_only
    Following is the default topology for Tx path COPreP:
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Tx Mic Gain                       (#AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL)
    - High Pass Filter                  (#AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER)
    - Enhanced Audio Noise Suppression  (#AUDPROC_MODULE_ID_EANS)
    - Tx IIR Tuning Filter              (#AUDPROC_MODULE_ID_TX_IIR_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    @endif
*/
#define ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP        2

/** Indicates a Tx path nonlive COPP. */
#define ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP    3

/** Indicates a loopback COPP. */
#define ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP    4

/** Indicates Rx Compressed mode (compressed output). */
#define ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX    5

/** Indicates Tx Compressed mode (compressed input). */
#define ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX    6

/** Indicates that an audio COPP is to send/receive a mono PCM stream to/from
    endpoint_id_1.
*/
#define ADM_CMD_COPP_OPEN_CHANNEL_CONFIG_MONO                        1

/** Indicates that an audio COPP is to send/receive a stereo PCM stream to/from
    endpoint_id_1.
*/
#define ADM_CMD_COPP_OPEN_CHANNEL_CONFIG_STEREO                      2

/** Sample rate is 8000 Hz. */
#define ADM_CMD_COPP_OPEN_SAMPLE_RATE_8K                             8000

/** Sample rate is 16000 Hz. */
#define ADM_CMD_COPP_OPEN_SAMPLE_RATE_16K                            16000

/** Sample rate is 48000 Hz. */
#define ADM_CMD_COPP_OPEN_SAMPLE_RATE_48K                            48000

/** Definition for a COPP live input flag bitmask. */
#define ADM_BIT_MASK_COPP_LIVE_INPUT_FLAG                            (0x0001U)

/** Definition for a COPP live shift value bitmask. */
#define ADM_SHIFT_COPP_LIVE_INPUT_FLAG                               0

/** Definition for the COPP ID bitmask. */
#define ADM_BIT_MASK_COPP_ID                                        (0x0000FFFFUL)

/** Definition for the COPP ID shift value. */
#define ADM_SHIFT_COPP_ID                                           0

/** Definition for the service ID bitmask. */
#define ADM_BIT_MASK_SERVICE_ID                                     (0x00FF0000UL)

/** Definition for the service ID shift value. */
#define ADM_SHIFT_SERVICE_ID                                        16

/** Definition for the domain ID bitmask. */
#define ADM_BIT_MASK_DOMAIN_ID                                      (0xFF000000UL)

/** Definition for the domain ID shift value. */
#define ADM_SHIFT_DOMAIN_ID                                          24

/** Definition for the Device Performance mode bitmask. */
#define ADM_BIT_MASK_DEVICE_PERF_MODE_FLAG                          (0x0000e000UL)

/** Definition for the Device Performance mode bit shift value. */
#define ADM_BIT_SHIFT_DEVICE_PERF_MODE_FLAG                           13

/** Definition for a legacy device session. */
#define ADM_LEGACY_DEVICE_SESSION                                      0

/** Definition for a low latency stream session. */
#define ADM_LOW_LATENCY_DEVICE_SESSION                                 1

/** Identifies an ultra low latency stream session. */
#define ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION                           2

/** @} */ /* end_addtogroup admsvc_cmd_open_device */

/* ADM device open command payload. */
typedef struct adm_cmd_device_open_v5_t adm_cmd_device_open_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_device_open_v5_t
@{ */
/* Payload of the ADM_CMD_DEVICE_OPEN_V5 command.
*/
struct adm_cmd_device_open_v5_t
{
    uint16_t                  flags;
    /**< Used to configure the device session based on the bitmasks.

         The device_perf_mode flag (bits 15 to 13) indicates the performance
         mode in which this device session must be opened.

         @values{for bits 15 to 13}
         - #ADM_LEGACY_DEVICE_SESSION -- Opens a legacy device session using
           default buffer sizes.
         - #ADM_LOW_LATENCY_DEVICE_SESSION -- Opens a low latency device session
           by using shortened buffers in the matrix and COPP.
           See the notes below.
         - #ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION -- Opens a ULL
           COPP session. There is no COPP or Matrix processing involved.
           See the notes below.
         - To configure this subfield, use #ADM_BIT_MASK_DEVICE_PERF_MODE_FLAG
           and #ADM_BIT_SHIFT_DEVICE_PERF_MODE_FLAG.
 
         All other bits are reserved; clients must set them to zero.

         @contcell
         @tblsubhd{Notes for low latency:}
         Recommendation: Do not enable high latency algorithms; they might
         negate the benefits of opening a low latency device, and they
         might also suffer quality degradation from unexpected jitter.

         The aDSP data path input latency contributed from the device side
         only can vary from 1 to 2 ms. The aDSP data path output latency
         contributed from the device side only can vary from 2 to 4 ms.
         In a steady state playback, latency is measured as the average
         sample time difference between the sample that is currently being
         read from shared memory and the sample that is currently rendered
         to the DMA.

         @tblsubhd{Notes for ultra low latency:}
         Recommendation: Open the COPP whose bits per sample and number of
         channels match the device to avoid processing in the aDSP.

         Only PCM, 48 kHz, 16-bit/24-bit, mono/stereo data is supported.

         The aDSP data path output latency contributed from the COPP session 
         is 0 ms. The end-to-end aDSP data path output latency is 2 ms,
         which is the AFE contribution. */

    uint16_t                  mode_of_operation;
    /**< Specifies whether the COPP is opened on the Tx or Rx path.

         @values
         - #ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP
         - #ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP
         - #ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP
         - #ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP
         - #ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX
         - #ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX

         Live connections cause sample discarding in the Tx device matrix if
         the destination output ports do not pull them fast enough. Non-live
         connections queue the samples indefinitely. */

    uint16_t                  endpoint_id_1;
    /**< Logical and physical endpoint ID of the audio path. If the ID is a
         voice processor Tx block, it receives near samples.
         
         @values Any pseudoport, AFE Rx port, or AFE Tx port (for a list of
                 valid IDs, refer to @xhyperref{Q6,[Q6]})
                 
         This value is ignored for mode_of_operation = 4 (loopback use case). */
    /* Q6 = Hex MM: AFE API Interface Spec for 2.6 (80-NF770-3) */

    uint16_t                  endpoint_id_2;
    /**< Second logical and physical endpoint ID for a voice processor Tx
         block. This is not applicable to audio COPP.
         
         @values
         - AFE Rx port (for a list of valid IDs, refer to @xhyperref{Q6,[Q6]})
         - 0xFFFF -- Endpoint 2 is unavailable and the voice processor Tx
           block ignores this endpoint
           
         When the voice processor Tx block is created on the audio record path,
         it can receive far-end samples from an AFE Rx port if the voice call
         is active. The ID of the AFE port is provided in this field.

         This value is ignored for:
         - mode_of_operation = 4 (loopback use case)
         - mode_of_operation = 5 and 6 (compressed use cases) @tablebulletend */

    uint32_t                  topology_id;
    /**< Audio COPP or voice processor Tx topology ID.

       @if OEM_only
         @values
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DEFAULT_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_NONE_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MONO_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_MIC_MONO_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_MIC_STEREO_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_IIR_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MCH_PEAK_VOL
         - #AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MONO_AUDIO_COPP_MBDRCV2
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_AUDIO_COPP_MBDRCV2
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_IIR_AUDIO_COPP_MBDRCV2
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_PEAKMETER_AUDIO_COPP
         - #ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SRS_TRUMEDIA_TOPOLOGY
       @endif

         For a complete list of audio topology IDs, see
         Chapter @xref{hdr:AudioPostProcTopos}. For a complete list of voice
         topology IDs, refer to @xhyperref{Q7,[Q7]}.

         Topologies can be added through #ADM_CMD_ADD_TOPOLOGIES_V5.
           
       @if OEM_only
         @contcell
         The SPEAKER_STEREO_IIR topology is the same as the SPEAKER_STEREO
         topology, except in the SPEAKER_STEREO_IIR, the IIR filter module is
         replaced by two independent per-channel IIR tuning filter modules.
         This topology is to be used on the Rx path only.

         For compressed use cases (mode_of_operation = 5 and 6), the client
         must set this field to #AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT.
       @endif

         Tx voice processing topology IDs are not supported in loopback mode
         (mode_of_operation = 4).

         AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT is not supported in any mode
         other than compressed audio input and compressed audio output. */
      /* Q7 = Hex MM: Voice API Interface Spec for 2.6 (80-NF770-2) */

    uint16_t                  dev_num_channel;
    /**< Number of channels in the data.

         @values
         - For voice processing Tx block (topology_id) -- 1, 2, 4
         - For audio COPP (topology_id) -- 1 to 8
         - For compressed use case (mode_of_operation) -- 2, 8 @tablebulletend */

     uint16_t                  bit_width;
     /**< Bit width of the data.

         @values
         - For voice processing Tx block (topology_id) -- 16 bits
         - For audio COPP (topology_id) -- 16 bits or 24 bits
         - For compressed use case (mode_of_operation) -- 16 bits
         @tablebulletend */

    uint32_t                  sample_rate;
    /**<  Sampling rate in Hertz of the data.

         @values
         - For voice processing Tx block (topology_id) -- 8K, 16K and 48K
         - For audio COPP (topology_id) -- > 0 and @le 192K
         - For compressed use case (mode_of_operation) -- 32K, 44.1K, 48K, 88.2K,
           96K, 176.4K, and 192K @tablebulletend */

    uint8_t                   dev_channel_mapping[8];
    /**< Channel mapping array of buffers that the audio COPP sends to the
         endpoint. Channel[i] mapping describes channel i inside the buffer,
         where 0 @le i < dev_num_channel.

         @values See Section @xref{dox:PcmChannelDefs}

         This value is relevent only for an audio COPP.

         For compressed use cases (mode_of_operation = 5 and 6), the client
         must set this field to zero.
         This value is ignored if the Device Performance mode is 
         #ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_device_open_v5_t */

/** @ingroup admsvc_cmd_close_device
    Closes a COPP (optional) and disconnects the device session.

  @apr_hdr_fields
    Opcode -- ADM_CMD_DEVICE_CLOSE_V5
    @par
    Dst_port -- COPP ID/Device ID

  @apr_msgpayload
    None.

  @detdesc
    The client must set the COPP ID for the Linear Pulse Code Modulation (LPCM)
    use case, and the device ID for the compressed use case.
    @par
    In the LPCM use case (mode_of_operation = 1 to 4), this command closes the
    COPP and disconnects the device session.
    @par
    In the Compressed use case (mode_of_operation = 5 to 6), this command
    disconnects the device session.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    #ADM_CMD_DEVICE_OPEN_V5 must have been used to open the COPP ID/device ID.
*/
#define ADM_CMD_DEVICE_CLOSE_V5                                        0x00010327

/** @ingroup admsvc_cmd_set_pp_params
    Sets one or more parameters for a COPP.

  @apr_hdr_fields
    Opcode -- ADM_CMD_SET_PP_PARAMS_V5
    @par
    Dst_port -- COPP ID

  @apr_msgpayload{adm_cmd_set_pp_params_v5_t}
    If the data payload address is NULL, this structure is immediately
    followed by a series of structures (%adm_param_data_v5_t) containing the
    pre/postprocessing parameter data (see
    <b>Parameter data variale payload</b>).
    @tablens{weak__adm__cmd__set__pp__params__v5__t}

  @par Parameter data variable payload (adm_param_data_v5_t)
    @tablens{weak__adm__param__data__v5__t} @newpage

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    This command must be applied to a valid COPP ID.
*/
#define ADM_CMD_SET_PP_PARAMS_V5                                     0x00010328

/* Payload of an ADM_CMD_SET_PP_PARAMS_V5 command. */
typedef struct adm_cmd_set_pp_params_v5_t adm_cmd_set_pp_params_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_set_pp_params_v5_t
@{ */
/* Payload of the ADM_CMD_SET_PP_PARAMS_V5 command.
    If the data payload addrress is NULL, this structure is immediately
    followed by a series of structures (adm_param_data_v5_t) containing the
    pre/postprocessing parameter data.
*/
struct adm_cmd_set_pp_params_v5_t
{

    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit parameter data payload address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit parameter data payload address. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ADM_CMD_SHARED_MEM_MAP_REGIONS command.

         @values
         - Non-NULL -- The parameter data payload begins at the specified
           address (out-of-band)
         - NULL -- The message is in the payload (in-band) @tablebulletend */

    uint32_t                  data_payload_size;
    /**< Size in bytes of the variable payload accompanying this message or
         in shared memory. This is used for parsing the parameter payload. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_set_pp_params_v5_t */

/* Payload of COPP parameter data. */
typedef struct adm_param_data_v5_t adm_param_data_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_param_data_v5_t
@{ */
/* Payload of the COPP parameter data of the ADM_CMD_SET_PP_PARAMS_V5
    command. */
/** Immediately following this structure are param_size bytes of the
    parameter data.
*/
struct adm_param_data_v5_t
{
    uint32_t                  module_id;
    /**< Valid ID of the module to be configured (see
         Chapter @xref{hdr:AudioPostProcIDs}). */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured (see
         Chapter @xref{hdr:AudioPostProcIDs}). */

    uint16_t                  param_size;
    /**< Data size of the param_id/module_id combination. This value is a
         multiple of 4 bytes. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */ 
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_param_data_v5_t */

/** @ingroup admsvc_resp_get_device_status
    Returns the status and COPP ID/device ID to an #ADM_CMD_DEVICE_OPEN_V5 command.

  @apr_hdr_fields
    Opcode -- ADM_CMDRSP_DEVICE_OPEN_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_rsp_device_open_v5_t}
    @table{weak__adm__cmd__rsp__device__open__v5__t}

  @return
    None.

  @dependencies
    None.
*/
#define ADM_CMDRSP_DEVICE_OPEN_V5                                     0x00010329

/* ADM command response to a Device open command. */
typedef struct adm_cmd_rsp_device_open_v5_t adm_cmd_rsp_device_open_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_rsp_device_open_v5_t
@{ */
/* Payload of the ADM_CMDRSP_DEVICE_OPEN_V5 message, which returns the
    status and COPP ID to an ADM_CMD_DEVICE_OPEN_V5 command.
*/
struct adm_cmd_rsp_device_open_v5_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q3,[Q3]} */
    /* Q3 = Async Packet Router API Interface Spec for MDM9x15 (80-N1463-2) */

    uint16_t                  copp_id;
    /**< Handle for the created COPP.

         @values
         - If mode_of_operation = 1 to 4 (LPCM use cases) -- \n
           0 @le copp_id < 25
         - If mode_of_operation = 5 and 6 (Compressed use cases) -- \n
           100 @le copp_id @le 113

         If mode_of_operation = 5 and 6, the COPP ID is to be interpreted as
         the device ID. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_rsp_device_open_v5_t */

/** @ingroup admsvc_cmd_get_pp_params
    Queries the ADM to get one COPP parameter.

  @apr_hdr_fields
    Opcode -- ADM_CMD_GET_PP_PARAMS_V5
    @par
    Dst_port -- COPP ID

  @apr_msgpayload{adm_cmd_get_pp_params_v5_t}
    @table{weak__adm__cmd__get__pp__params__v5__t}

  @return
    #ADM_CMDRSP_GET_PP_PARAMS_V5.

  @dependencies
    This command must be applied to a valid COPP ID.
*/
#define ADM_CMD_GET_PP_PARAMS_V5                                0x0001032A

/* Payload format for the Get Parameters command. */
typedef struct adm_cmd_get_pp_params_v5_t adm_cmd_get_pp_params_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_get_pp_params_v5_t
@{ */
/* Payload of the ADM_CMD_GET_PP_PARAMS_V5 command.
*/
struct adm_cmd_get_pp_params_v5_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit parameter data payload address. */
    
    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit parameter data payload address.

         The size of the shared memory, if specified, must be large enough to
         contain the entire parameter data payload, including the module ID,
         parameter ID, parameter size, and parameter values. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ADM_CMD_SHARED_MEM_MAP_REGIONS command.

         @values
         - Non-NULL -- On acknowledgment, the parameter data payloads begin at
           the address specified (out-of-band)
         - NULL -- The acknowledgment's payload contains the parameter data
           (in-band) @tablebulletend */

    uint32_t                  module_id;
    /**< Valid ID of the module to be configured (see
         Chapter @xref{hdr:AudioPostProcIDs}). */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured (see
         Chapter @xref{hdr:AudioPostProcIDs}). */

    uint16_t                  param_max_size;
    /**< Maximum data size of the parameter ID/module ID combination. This
         field is a multiple of 4 bytes. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_get_pp_params_v5_t */

/** @ingroup admsvc_resp_get_pp_param_vals
    Returns parameter values in response to an #ADM_CMD_GET_PP_PARAMS_V5
    command.

  @apr_hdr_fields
    Opcode -- ADM_CMDRSP_GET_PP_PARAMS_V5
    @par
    Dst_port -- COPP ID

  @apr_msgpayload{adm_cmd_rsp_get_pp_params_v5_t}
    Immediately following this structure is %adm_param_data_v5_t, which
    contains the pre/postprocessing parameter data (see
    <b>Parameter data variable payload</b>).
    @par
    For an in-band scenario, the variable payload depends on the size
    of the parameter.
    @tablens{weak__adm__cmd__rsp__get__pp__params__v5__t}

  @par Parameter data variable payload (adm_param_data_v5_t}
    @tablens{weak__adm__param__data__v5__t}

  @return
    None.

  @dependencies
    #ADM_CMD_GET_PP_PARAMS_V5 must have been applied to a valid COPP.
*/
#define ADM_CMDRSP_GET_PP_PARAMS_V5                             0x0001032B

/* Payload for an ADM get pre/postprocessing parameters ACK event. */
typedef struct adm_cmd_rsp_get_pp_params_v5_t adm_cmd_rsp_get_pp_params_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_rsp_get_pp_params_v5_t
@{ */
/* Payload of the ADM_CMDRSP_GET_PP_PARAMS_V5 message, which returns
    parameter values in response to an ADM_CMD_GET_PP_PARAMS_V5 command.
    Immediately following this structure is adm_param_data_v5_t, which
    contains the pre/postprocessing parameter data.
    For an in-band scenario, the variable payload depends on the size
    of the parameter.
*/
struct adm_cmd_rsp_get_pp_params_v5_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q5,[Q5]} */
    /* Q5 = Hex MM: AV Core Service API Interface Spec for 2.6 (80-NF770-4) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_rsp_get_pp_params_v5_t */

/** @ingroup admsvc_cmd_get_pp_topo_mods
    Queries the ADM service to get list of modules in a COPP/COPreP
    topology.

  @apr_hdr_fields
    Opcode -- ADM_CMD_GET_PP_TOPO_MODULE_LIST
    @par
    Dst_port -- COPP ID

  @msgpayload{adm_cmd_get_pp_topo_module_list_t}
    @table{weak__adm__cmd__get__pp__topo__module__list__t}

  @par Parameter data payload (audproc_topology_module_id_info_t)
    @table{weak__audproc__topology__module__id__info__t}

  @return
    #ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST.

  @dependencies
    This command must be applied to a valid COPP ID.
*/
#define ADM_CMD_GET_PP_TOPO_MODULE_LIST                                0x00010349

/* Payload format for the Get Parameters command. */
typedef struct adm_cmd_get_pp_topo_module_list_t adm_cmd_get_pp_topo_module_list_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_get_pp_topo_module_list_t
@{ */
/* Payload of the ADM_CMD_GET_PP_TOPO_MODULE_LIST command.
*/
struct adm_cmd_get_pp_topo_module_list_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit parameter data payload address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit parameter data payload address.

         The size of the shared memory, if specified, must be large enough to
         contain the entire parameter data payload, including the module ID,
         parameter ID, parameter size, and parameter values. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ADM_CMD_SHARED_MEM_MAP_REGIONS command.

         @values
         - Non-NULL -- On acknowledgment, the parameter data payloads begin at
           the address specified (out-of-band)
         - NULL -- The acknowledgment's payload contains the <b>Parameter data
           payload</b> (in-band) @tablebulletend */

    uint16_t                  param_max_size;
    /**< Maximum data size of the list of modules. This
         field is a multiple of 4 bytes. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_get_pp_topo_module_list_t */

/** @ingroup admsvc_resp_get_pp_topo_mods
    Returns a list of COPP/COPreP topology modules in response to an
    #ADM_CMD_GET_PP_TOPO_MODULE_LIST command.

  @apr_hdr_fields
    Opcode -- ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST
    @par
    Dst_port -- COPP ID

  @msgpayload{adm_cmd_rsp_get_pp_topo_module_list_t}
    @tablens{weak__adm__cmd__resp__get__pp__topo__module__info__t}

  @return
    None.

  @dependencies
    #ADM_CMD_GET_PP_TOPO_MODULE_LIST must have been applied to a valid COPP.
*/
#define ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST                             0x00010350

/* Payload for an ADM get pre/postprocessing parameters ACK event. */
typedef struct adm_cmd_rsp_get_pp_topo_module_list_t adm_cmd_rsp_get_pp_topo_module_list_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_resp_get_pp_topo_module_info_t
@{ */
/* Payload of the ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST message, which returns
   module ids in response to an ADM_CMD_GET_PP_TOPO_MODULE_LIST command.
*/
struct adm_cmd_rsp_get_pp_topo_module_list_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q5,[Q5]} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_rsp_get_pp_topo_module_info_t */

/** @addtogroup admsvc_cmd_gain_control
@{ */
/** Allows a client to control the gains on various session-to-COPP paths.
    All specified session and COPP IDs must be valid and connected to the
    targeted matrix.

  @apr_hdr_fields
    Opcode -- ADM_CMD_MATRIX_RAMP_GAINS_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_matrix_ramp_gains_v5_t}
    Immediately following this structure are num_gains of
    %adm_session_copp_gain_v5_t (see <b>Session COPP gain type</b>).
    @tablens{weak__adm__cmd__matrix__ramp__gains__v5__t}

  @par Session COPP gain type (adm_session_copp_gain_v5_t)
    This structure specifies the target gain (per channel) that must be applied
    to a particular session-to-COPP path in the audio matrix. The structure can
    also be used to apply the gain globally to all session-to-COPP paths that
    exist for the given session.
    @par
    The aDSP uses device channel mapping to determine which channel gains to
    use from this command. For example, if the device is configured as stereo,
    the aDSP uses only target_gain_ch_1 and target_gain_ch_2, and it ignores
    the others.
    @tablens{weak__adm__session__copp__gain__v5__t}

  @detdesc
    For every session-to-COPP path, the specified gains are channel specific
    and can be applied immediately or over a period of time in
    ramping fashion. The latter helps avoid a pop when the gain is changed.
    The client can specify the ramp curve, ramp duration, and step duration
    to indicate the kind of ramping required to achieve the target gain.
    @par
    The clients can specify gain ramps for multiple session-to-COPP paths at
    one time, improving synchronization. The client can also apply the gain
    ramp globally to all session-to-COPP paths that exist for the specified
    session.
    @par
    This command takes effect immediately upon receipt. It can be used for:
      - Controlling per-stream-per-device volume
      - Supporting multichannel (up to 7.1) gain settings
      - Soft-stepping during a stream's volume changes
    @par
    It is the client's responsibility to maintain a history of gain values
    for every channel in each session-to-COPP path because this command
    does not allow a client to specify new gain values for only some channels
    in a stream. The client must specify new gain values for all the channels.
    @par
    If the client wants to selectively change the gains of only some
    channels in an audio stream, it must still send this command with all the
    required target gains. For the channels on which the client does not want
    to change the gains, the client must specify its current gain as the
    target gain. @newpage
    @par
    The aDSP applies gain on a stream after reformatting, if required, to
    match the COPP's channel mapping. Therefore, the aDSP uses the COPP channel
    mapping information (from ADM_CMD_MULTICHANNEL_COPP_OPEN) to determine
    which gains to use from this command. Therefore, it is the client's
    responsibility to send this command with gain values set for exactly those
    channels on which the device is operating. For example:
      - If the audio stream is multichannel, the user sets a multichannel
        volume, and the device (and COPP) are configured to operate in Stereo
        mode -- the client converts the multichannel gain to stereo gain and
        sets gains for only two channels in this command. The aDSP ignores the
        remaining gain values.
      - If the audio stream is stereo, the user sets a stereo volume, and the
        device (and COPP) are configured to operate in 5.1 Multichannel mode --
        the client must convert the stereo gain to 5.1 gain and set gains for
        all six channels in this command.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    All specified session IDs and COPP IDs must be valid and connected to the
    targeted matrix.
*/
#define ADM_CMD_MATRIX_RAMP_GAINS_V5                                 0x0001032C

/** Indicates that the target gain in the current adm_session_copp_gain_v5_t
    structure is to be applied to all the session-to-COPP paths that exist for
    the specified session.
*/
#define ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS     0xFFFF

/** Indicates that the target gain is to be immediately applied to the
    specified session-to-COPP path, without a ramping fashion.
*/
#define ADM_CMD_MATRIX_RAMP_GAINS_RAMP_DURATION_IMMEDIATE         0x0000

/** Enumeration for a linear ramping curve. */
#define ADM_CMD_MATRIX_RAMP_GAINS_RAMP_CURVE_LINEAR               0x0000

/** @} */ /* end_addtogroup admsvc_cmd_gain_control */

/* Payload format for the ADM Matrix Ramp Gains command. */
typedef struct adm_cmd_matrix_ramp_gains_v5_t adm_cmd_matrix_ramp_gains_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_matrix_ramp_gains_v5_t
@{ */
/* Payload of the ADM_CMD_MATRIX_RAMP_GAINS_V5 command, which allows a client
    to specify gain ramps to apply to PCM samples on multiple session-to-COPP
    paths. Immediately following this structure are num_gains of
    adm_session_copp_gain_v5_t. 
*/
struct adm_cmd_matrix_ramp_gains_v5_t
{
    uint32_t                  matrix_id;
    /**< ID of the audio matrix on the Tx path or Rx path.

         @values
         - #ADM_MATRIX_ID_AUDIO_RX
         - #ADM_MATRIX_ID_AUDIO_TX @tablebulletend */

    uint16_t                  num_gains;
    /**< Number of gain settings being applied.

         @values > 0*/

    uint16_t                  reserved_for_align;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_matrix_ramp_gains_v5_t */

/* Session-to-COPP path gain structure. */
typedef struct adm_session_copp_gain_v5_t adm_session_copp_gain_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_session_copp_gain_v5_t
@{ */
/* Payload of the session-to-COPP path gain used by the
    ADM_CMD_MATRIX_RAMP_GAINS_V5 command.
*/
struct adm_session_copp_gain_v5_t
{
    uint16_t                  session_id;
    /**< Handle of the ASM session to be routed.

         @values 1 to 8 */

    uint16_t                  copp_id;
    /**< Handle of the COPP. The path from the session handle to the COPP
         handle has the gain applied. Gain must be applied to all COPPs
         connected to the current session_id.

         @values
         - #ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS
         - Other values -- Valid COPP ID @tablebulletend */

    uint16_t                  ramp_duration;
    /**< Duration (in milliseconds) of the ramp over which target gains are
         to be applied.

         @values
         - 0 (Default) to 0xFFFF
         - Or, use #ADM_CMD_MATRIX_RAMP_GAINS_RAMP_DURATION_IMMEDIATE
           to indicate that gain must be applied immediately @tablebulletend */

    uint16_t                  step_duration;
    /**< Duration (in milliseconds) of each step in the ramp. This parameter
         is ignored if ramp_duration=0.

         @values 1 */

    uint16_t                  ramp_curve;
    /**< Type of ramping curve.  

         @values #ADM_CMD_MATRIX_RAMP_GAINS_RAMP_CURVE_LINEAR */

    uint16_t                  reserved_for_align;
    /**< This field must be set to zero. */

    uint16_t                  target_gain_ch_1;
    /**< Target linear gain for channel 1. For a stereo stream, the gain is
         applied to the left channel.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_2;
    /**< Target linear gain for channel 2. For a stereo stream, the gain is
         applied to the right channel.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_3;
    /**< Target linear gain for channel 3.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_4;
    /**< Target linear gain for channel 4.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_5;
    /**< Target linear gain for channel 5.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_6;
    /**< Target linear gain for channel 6.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_7;
    /**< Target linear gain for channel 7.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */

    uint16_t                  target_gain_ch_8;
    /**< Target linear gain for channel 8.

         @values unsigned Q13 number
         - 0 -- Mute
         - 0x2000 -- Unity @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_session_copp_gain_v5_t */

/** @addtogroup admsvc_cmd_matrix_mute
@{ */
/** Allows a client to set mute/unmute on various session-to-COPP paths.

  @apr_hdr_fields
    Opcode -- ADM_CMD_MATRIX_MUTE_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_matrix_mute_v5_t}
    @table{weak__adm__cmd__matrix__mute__v5__t}

  @detdesc
    The client can apply mute/unmute globally to all session-to-COPP paths that
    exist for the specified session. The aDSP uses device channel mapping to
    determine which device channel mute/unmute to use from the command. For
    example, if the device is configured as stereo, the aDSP uses only
    mute_flag_ch_1 and mute_flag_ch_2 and ignores the others. For every
    session-to-COPP path (stream-device interconnection), mute/unmute can be
    set individually on the output channels.
    @par
    The ADM_CMD_MATRIX_MUTE_V5 command:
      - Can be used for controlling per-stream-per-device mute/unmute
      - Supports multichannel mute settings (up to 8 channels)
      - Overrides any #ADM_CMD_MATRIX_RAMP_GAINS_V5 that might be called
    @par
    Example 1: Ramp_gain > Mute > Unmute sequence
      -# Mute is applied immediately.
      -# All ramps are canceled.
      -# On unmute, the target setting provided in the ramp_gain field is
        applied immediately. @newpage
    @par
    Example 2: Mute > Ramp_gain > Unmute sequence
      -# Mute is applied immediately.
      -# Ramps are not serviced.
      -# On unmute, the target setting provided in the ramp_gain field is
        applied immediately.
    @par
    On the playback path:
    - If the client wants to use this command as a stream mute command, it can
      set the #ADM_CMD_MATRIX_MUTE_COPP_ID_ALL_CONNECTED_COPPS for the copp_id.
      This will mute all interconnections emanating from this stream. 
    - If the client wants to use this as a device (n) mute command, it must
      provide the mute command to individual (stream 1, device n), (stream 2,
      device n) combinations. In this example, stream 1 and stream 2 mix into
      device n.
    @par
    The aDSP applies mute/unmute on a stream after reformatting, if required,
    to match the COPP's channel mapping. The aDSP uses the COPP channel
    mapping information (from ADM_CMD_MULTICHANNEL_COPP_OPEN) to determine
    which channels will be muted/unmuted from this command. Therefore, it is
    the client's responsibility to send this command to mute/unmute exactly
    those channels on which the device is operating.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    All specified session IDs and COPP IDs must be valid and connected to the
    targeted matrix.
*/
#define ADM_CMD_MATRIX_MUTE_V5                                0x0001032D

/** Indicates that mute/unmute in the current adm_session_copp_mute_v5_t structure
    is to be applied to all the session-to-COPP paths that exist for the
    specified session.
*/
#define ADM_CMD_MATRIX_MUTE_COPP_ID_ALL_CONNECTED_COPPS     0xFFFF

/** @} */ /* end_addtogroup admsvc_cmd_matrix_mute */

/* Payload format for the ADM Matrix mute command. */
typedef struct adm_cmd_matrix_mute_v5_t adm_cmd_matrix_mute_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_matrix_mute_v5_t
@{ */
/* Payload of the ADM_CMD_MATRIX_MUTE_V5 command, which allows clients to
    apply mute/unmute to PCM samples on multiple session-to-COPP paths.
*/
struct adm_cmd_matrix_mute_v5_t
{
    uint32_t                  matrix_id;
    /**< Specifies whether the command is intended for the audio matrix on the
         Tx path or Rx path.

         @values
         - #ADM_MATRIX_ID_AUDIO_RX
         - #ADM_MATRIX_ID_AUDIO_TX @tablebulletend */

    uint16_t                  session_id;
    /**< Handle of the ASM session to be routed.
    
         @values 1 to 8 */

    uint16_t                  copp_id;
    /**< Handle of the COPP. Mute/unmute must be applied to all the COPPs
         connected to session_id. 
         
         @values
         - #ADM_CMD_MATRIX_MUTE_COPP_ID_ALL_CONNECTED_COPPS
         - Other values -- Valid COPP ID @tablebulletend */

    uint8_t                  mute_flag_ch_1;
    /**< Specifies whether channel 1 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_2;
    /**< Specifies whether channel 2 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_3;
    /**< Specifies whether channel 3 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_4;
    /**< Specifies whether channel 4 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_5;
    /**< Specifies whether channel 5 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_6;
    /**< Specifies whether channel 6 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_7;
    /**< Specifies whether channel 7 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint8_t                  mute_flag_ch_8;
    /**< Specifies whether channel 8 is set to mute.

         @values
         - 0 -- Unmute
         - 1 -- Mute @tablebulletend */

    uint16_t                 ramp_duration;
    /**< Period (in milliseconds) over which the soft mute/unmute will be
         applied. The default of 0 means mute/unmute will be applied
         immediately.
             
         @values 0 (Default) to 0xFFFF */

    uint16_t                 reserved_for_align;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_matrix_mute_v5_t */

/** @addtogroup admsvc_cmd_connect_afe_port
@{ */
/** Allows a client to connect a specified stream to a specified AFE port
    through the stream router.

  @apr_hdr_fields
    Opcode -- ADM_CMD_CONNECT_AFE_PORT_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_connect_afe_port_v5_t}
    @table{weak__adm__cmd__connect__afe__port__v5__t}

  @detdesc
    This command is used only for compressed streams that are opened using
    the #ASM_STREAM_CMD_OPEN_WRITE_COMPRESSED or
    #ASM_STREAM_CMD_OPEN_READ_COMPRESSED command.
    @par
    This command assumes an implicit device sampling rate of 48 kHz and
    two device channels.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @keep{6} @dependencies
    The session ID and AFE port ID must be valid.
    @par
    #ASM_STREAM_CMD_OPEN_WRITE_COMPRESSED or
    #ASM_STREAM_CMD_OPEN_READ_COMPRESSED must have been called in this session.
*/
#define ADM_CMD_CONNECT_AFE_PORT_V5                           0x0001032E

/** Enumeration for the Rx stream router ID. */
#define ADM_STRTR_ID_RX                    0

/** Enumeration for the Tx stream router ID. */
#define ADM_STRTR_ID_TX                    1

/** @} */ /* end_addtogroup admsvc_cmd_connect_afe_port */

/* Payload format for the ADM Connect AFE port command. */
typedef struct adm_cmd_connect_afe_port_v5_t adm_cmd_connect_afe_port_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_connect_afe_port_v5_t
@{ */
/* Payload of the ADM_CMD_CONNECT_AFE_PORT_V5 command, which allows a client to
    connect a specified session to a specified AFE port in Compressed Bitstream
    mode.
*/
struct adm_cmd_connect_afe_port_v5_t
{
    uint8_t                  mode;
    /**< ID of the stream router.

         @values
         - #ADM_STRTR_ID_RX 
         - #ADM_STRTR_ID_TX @tablebulletend */

    uint8_t                  session_id;
    /**< ID of the AFE session to be routed.

         @values 1 to 8 */

    uint16_t                 afe_port_id;
    /**< ID of the AFE port to which this stream is to connect.

         @values Refer to @xhyperref{Q6,[Q6]} */
    /* Q6 = Hex MM: AFE API Interface Spec for 2.6 (80-NF770-3) */

    uint32_t                 num_channels;
    /**< Number of device channels.

         @values
         - 2 -- Audio sample packet (data is transmitted over a single I2S line
         - 8 -- High bitrate audio stream sample packet (data is transmitted
           over four I2S lines (HBR_Audio for compressed HDMI) @tablebulletend */

    uint32_t                 sampling_rate;
    /**< Device sampling rate in Hertz. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_connect_afe_port_v5_t */

/** @ingroup admsvc_cmd_disconnect_afe_port
    Allows a client to disconnect the stream router from a specified AFE port.

  @apr_hdr_fields
    Opcode -- ADM_CMD_DISCONNECT_AFE_PORT_V5
    @par
    Dst_port -- AFE Port ID

  @apr_msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The #ADM_CMD_CONNECT_AFE_PORT_V5 command must have been used to connect
    this AFE port to the stream router.
*/
#define ADM_CMD_DISCONNECT_AFE_PORT_V5                           0x0001032F

/** @cond OEM_only */
/** @ingroup admsvc_cmd_get_spa_data
    Indicates a data buffer to be filled with spectrum analyzer data.

  @apr_hdr_fields
    Opcode -- ADM_DATA_CMD_SPA_V5
    @par
    Dst_port -- COPP ID

  @apr_msgpayload
    See #ASM_DATA_CMD_SPA_V2.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The spectrum analyzer must have been enabled using
    #ADM_CMD_SET_PP_PARAMS_V5.
    @par
    This command must be applied to a valid COPP ID.
*/
#define ADM_DATA_CMD_SPA_V5                                          0x00010330

/** @ingroup admsvc_event_spa_done_resp
    Indicates that the referenced buffer has been filled with spectrum analyzer
    data and is available to the client.

  @apr_hdr_fields
    Opcode -- ADM_DATA_EVENT_SPA_V5_DONE
    @par
    Dst_port -- COPP ID

  @apr_msgpayload
    See #ASM_DATA_EVENT_SPA_DONE_V2.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #ADM_DATA_CMD_SPA_V5 on a valid COPP ID must have been
    received and processed.
*/
#define ADM_DATA_EVENT_SPA_V5_DONE                                    0x00010331

/** @endcond */

/** @ingroup admsvc_cmd_add_topos
    Defines custom topologies in the aDSP for use in COPP and COPreP. These
    topologies can be created by specifying their topology IDs in the
    COPP open command (#ADM_CMD_DEVICE_OPEN_V5).
    
  @apr_hdr_fields
    Opcode -- ADM_CMD_ADD_TOPOLOGIES_V5
    @par
    Dst_port -- 0

  @apr_msgpayload{adm_cmd_add_topologies_v5_t}
    @table{weak__adm__cmd__add__topologies__v5__t}

  @par Buffer format (audproc_custom_topologies_t)
    Immediately following this structure are num_topologies of
    %audproc_topology_definition_t, which are to be added to the aDSP
    (see <b>Topology definition</b>).
    @tablens{weak__audproc__custom__topologies__t}
    Calculation of the buffer size:
    - Size of the module information structure = 4 + 4 + 16 = 24 bytes
    - Size of the topology definition structure = 4 + 4 + 16 * (size of the
      module information structure) = 392 bytes
    - Size of the buffer = 4 + num_topologies * 392 @newpage

  @par Topology definition (audproc_topology_definition_t)
    Immediately following this structure are num_modules of
    %audproc_module_info_t (see <b>Module information</b>).
    @tablens{weak__audproc__topology__definition__t}

  @par Module information (audproc_module_info_t)
    @table{weak__audproc__module__info__t} @vertspace{-12}

  @detdesc 
    Custom topology definitions are stored internally by the aDSP. The
    definitions sent to the ADM are available for only the COPP and COPreP.
    @par
    This command must be sent before opening a COPP with the custom
    topologies. This command can be sent multiple times to add new topologies;
    the ADM supports up to a total of 128 custom topologies.
    @par
    If a subsequent command redefines a previously defined topology ID, the
    previous topology definition is replaced with the new one. However, the
    changes take effect only on the next session creation. @newpage

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as input.

  @dependencies
    None.
*/
#define ADM_CMD_ADD_TOPOLOGIES_V5                                0x00010335

/* The payload for the ADM_CMD_ADD_TOPOLOGIES_V5 command */
typedef struct adm_cmd_add_topologies_v5_t adm_cmd_add_topologies_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_add_topologies_v5_t
@{ */
/* Payload of the ADM_CMD_ADD_TOPOLOGIES_V5 message.
*/
struct adm_cmd_add_topologies_v5_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the topology buffer address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the topology buffer address. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ADM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buffer_size;
    /**< Size in bytes of the valid data in the topology buffer. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_add_topologies_v5_t */

/** @addtogroup admsvc_cmd_strm_dev_map_rout
@{ */
/** Provides updates to the matrix/stream router mapping between session IDs
    and device IDs.
    All specified session and device IDs must be valid and connected to the
    targeted matrix.

  @apr_hdr_fields
    Opcode -- ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_stream_device_map_routings_v5_t}
    Immediately following this structure are num_sessions of
    %adm_stream_device_map_node_v5_t (see <b>Map node payload</b>).
    @tablens{weak__adm__cmd__stream__device__map__routings__v5__t}

  @par Map node payload (adm_stream_device_map_node_v5_t)
    @tablens{weak__adm__stream__device__map__node__v5__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    All specified session and device IDs must be valid and connected to the
    targeted matrix/stream router.
*/
#define ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5                                 0x0001033D

/** Enumeration for LPCM audio output. */
#define ADM_LPCM_AUDIO_OUT              0

/** Enumeration for LPCM audio input. */
#define ADM_LPCM_AUDIO_IN               1

/** Enumeration for compressed audio output. */
#define ADM_COMPRESSED_AUDIO_OUT        2

/** Enumeration for compressed audio input. */
#define ADM_COMPRESSED_AUDIO_IN         3

/** @} */ /* end_addtogroup admsvc_cmd_strm_dev_map_rout */

/* Payload of an ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5 command. */
typedef struct adm_cmd_stream_device_map_routings_v5_t adm_cmd_stream_device_map_routings_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_stream_device_map_routings_v5_t
@{ */
/* Payload of the ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5 command, which allows a client
    to provide updates to the mapping between session IDs and device end point IDs.
    Immediately following this structure are num_sessions of
    adm_stream_device_map_node_v5_t.
*/
struct adm_cmd_stream_device_map_routings_v5_t
{
    uint32_t                  mode;
    /**< Specifies the operation mode of a session.

         @values
         - #ADM_LPCM_AUDIO_OUT
         - #ADM_LPCM_AUDIO_IN
         - #ADM_COMPRESSED_AUDIO_OUT
         - #ADM_COMPRESSED_AUDIO_IN @tablebulletend */

    uint32_t                  num_sessions;
    /**< Number of sessions being updated by this command.

         @values 1 to 8 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_stream_device_map_routings_v5_t */

/* Session map node structure. */
typedef struct adm_stream_device_map_node_v5_t adm_stream_device_map_node_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_stream_device_map_node_v5_t
@{ */
/* Payload of the session map node used by ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5. */
/** Immediately following this structure are num_device_end_points entries of
    device endpoint IDs. These IDs are 16 bits, so there is another 16-bit
    field for padding if num_device_end_points is an odd number. For PCM
    devices, this is the COPP ID.

    For compressed audio devices, this ID was
    returned in #ADM_CMDRSP_DEVICE_OPEN_V5.
*/
struct adm_stream_device_map_node_v5_t
{
    uint16_t                  session_id;
    /**< Handle of the ASM session to be routed.

         @values 1 to 8 */

    uint16_t                  num_device_end_points;
    /**< Number of devices to which this session is to be routed.

         @values 0 < num_device_end_points @le 25 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_stream_device_map_node_v5_t */

/** @ingroup admsvc_cmd_strm_dev_unmap_rout
    Informs the stream router to unmap the connection between the given stream
    and device ports.

  @apr_hdr_fields
    Opcode -- ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_stream_device_unmap_routings_v5_t}
    Immediately following this structure are num_sessions of
    %adm_stream_device_unmap_node_v5_t (see <b>Unmap node payload</b>).
    @tablens{weak__adm__cmd__stream__device__unmap__routings__v5__t}

  @par Unmap node payload (adm_stream_device_unmap_node_v5_t)
    @tablens{weak__adm__stream__device__unmap__node__v5__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    All specified session and device IDs must be valid and connected to the
    targeted matrix/stream router.
*/
#define ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5                                 0x0001033E

/* Payload of an ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5 command. */
typedef struct adm_cmd_stream_device_unmap_routings_v5_t adm_cmd_stream_device_unmap_routings_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_stream_device_unmap_routings_v5_t
@{ */
/* Payload of the ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5 command, which allows a client
    to specify the session ID that needs to be unmapped from the corresponding device ID
    Immediately following this structure are num_sessions of
    adm_stream_device_unmap_node_v5_t).
*/
struct adm_cmd_stream_device_unmap_routings_v5_t
{
    uint32_t                  mode;
    /**< Specifies the operation mode of a session.

         @values
         - #ADM_LPCM_AUDIO_OUT
         - #ADM_LPCM_AUDIO_IN
         - #ADM_COMPRESSED_AUDIO_OUT
         - #ADM_COMPRESSED_AUDIO_IN @tablebulletend */

    uint32_t                  num_sessions;
    /**< Number of sessions being updated by this command.

         @values 1 to 8 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_stream_device_unmap_routings_v5_t */

/* stream device unmap node structure. */
typedef struct adm_stream_device_unmap_node_v5_t adm_stream_device_unmap_node_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_stream_device_unmap_node_v5_t
@{ */
/* Payload of the stream/device unmap node used by ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5. */
/** Immediately following this structure are num_device_end_points entries of
    device endpoint IDs. These IDs are 16 bits, so there is another 16-bit
    field for padding if num_device_end_points is an odd number. For PCM
    devices, this is the COPP ID.

    For compressed audio devices, this ID was
    returned in #ADM_CMDRSP_DEVICE_OPEN_V5.
*/
struct adm_stream_device_unmap_node_v5_t
{
    uint16_t                  session_id;
    /**< Handle of the ASM session to be unmapped.

         @values 1 to 8 */

    uint16_t                  num_device_end_points;
    /**< Number of devices to which this session is to be routed.

         @values 0 < num_device_end_points @le 25 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_stream_device_unmap_node_v5_t */

/** @cond OEM_only */
/** @ingroup admsvc_cmd_set_pspd_params
    Sets one or more parameters on a matrix mixer or stream router on the
    per-stream, per-device path.

  @apr_hdr_fields
    Opcode -- ADM_CMD_SET_PSPD_MTMX_STRTR_PARAM_V5
    @par
    Dst_port -- Ignored

  @apr_msgpayload{adm_cmd_set_pspd_mtmx_strtr_params_v5_t}
    @table{weak__adm__cmd__set__pspd__mtmx__strtr__params__v5__t}

  @par Parameter data variable payload (adm_pspd_param_data_t)
    @tablens{weak__adm__pspd__param__data__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    Both the session and device must be open and valid. They also must be
    connected using the #ADM_CMD_MATRIX_MAP_ROUTINGS_V5 command.
*/
#define ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V5                   0x00010344

/* Structure for a set param command on matrix or stream router on the per-stream, per-device pathway. */
typedef struct adm_cmd_set_pspd_mtmx_strtr_params_v5_t adm_cmd_set_pspd_mtmx_strtr_params_v5_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_cmd_set_pspd_mtmx_strtr_params_v5_t
@{ */
/* Payload of the ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V5 command, which allows
    one or more parameters to be set on a matrix or stream router on the per-strean, per-device pathway.
*/
struct adm_cmd_set_pspd_mtmx_strtr_params_v5_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit parameter data payload address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit parameter data payload address. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the address.

         This memory map handle is returned by the aDSP through the
         #ADM_CMD_SHARED_MEM_MAP_REGIONS command.

         @values
         - Non-NULL -- The parameter data payload begins at the specified
           address (out-of-band)
         - NULL -- The message is in the payload (in-band)

         If mem_map_handle = non-NULL, the parameter data variable
         payload begins at the specified address.
         The total size is data_payload_size bytes.
         
         If mem_map_handle = NULL, a series of %adm_pspd_param_data_t
         structures immediately follow, whose total size is data_payload_size
         bytes (see <b>Parameter data variable payload</b>). */

    uint32_t                  data_payload_size;
    /**< Actual size of the variable payload accompanying the message, or in
         shared memory.

         This field is used for parsing the parameter payload.

         @values > 0 bytes */

    uint16_t                  direction;
    /**< The direction of the entity on which parameter is to be set.

         @values
         - 0 -- Rx 
         - 1 -- Tx @tablebulletend */

    uint16_t                  session_id;
    /**< ID of the ASM session for this command.

         @values 1 to 15 */

    uint16_t                  device_id;
    /**< ID of the device for this command.

         @values
         - For LPCM -- COPP ID
         - For compressed -- Device ID @tablebulletend */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_cmd_set_pspd_mtmx_strtr_params_v5_t */

/* Structure for session parameter data. */
typedef struct adm_pspd_param_data_t adm_pspd_param_data_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_pspd_param_data_t
@{ */
/* Payload of the per-session, per-device parameter data of the
    #ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V5 command. */
/** Immediately following this structure are param_size bytes of parameter
    data. The structure and size depend on the module_id/param_id pair.
*/
struct adm_pspd_param_data_t
{
    uint32_t                  module_id;
    /**< Valid ID of the module to be configured (see
         Section @xref{hdr:AudioMatrixRouterModule}). */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured (see
         Section @xref{hdr:AudioMatrixRouterModule}). */

    uint16_t                  param_size;
    /**< Data size of the param_id/module_id combination. This is a multiple
         of four bytes.

         @values > 0 bytes */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_pspd_param_data_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asm_audpp_deprecated
@{ */
/** @name Channel Mixer module
@{ */
/** Deprecated. Use #AUDPROC_MODULE_ID_CHMIXER.

    Used for default channel-mixer related parameters.
    This module supports the following parameter ID:
       - #DEFAULT_CHMIXER_PARAM_ID_COEFF
*/
#define MTMX_MODULE_ID_DEFAULT_CHMIXER                                  0x00010341

/* Structure payload for: DEFAULT_CHMIXER_PARAM_ID_COEFF*/
/** Deprecated. Use #AUDPROC_CHMIXER_PARAM_ID_COEFF.

    Used by MTMX_MODULE_ID_DEFAULT_CHMIXER to configure the channel mixer
    weighting coefficients.

  @msgpayload{default_chmixer_param_id_coeff}
    @table{weak__default__chmixer__param__id__coeff}

    Immediately following this structure are these variable-sized arrays in
    sequence:
    -# num_output_channels entries of output channel mapping.
       (Permitted values: 1 to 34)
    -# num_input_channels entries of input channel mapping.
       (Permitted values: 1 to 34)
    -# num_output_channels (rows) x num_input_channels (columns) entries of
       channel mixer weighting coefficients in Q14 format.
       (Permitted values: 0 to 16384)
       \n
       For example:
       @verbatim
       Unity (1)       -> 0x4000 -> 16384
       -3 dB (0.707)   -> 0x2D44 -> 11588
       -6 dB (0.5)     -> 0x2000 -> 8192
       0               -> 0x0    -> 0
       @endverbatim
    -# Optional 16-bit zero padding if the entire combination of 1, 2, and 3
       above is not a multiple of 32 bits. This is required so the entire
       payload is aligned to 32 bits. (Permitted value: 0)

  @par Rules for using Set parameters
    - The Set parameters are per-stream, per-device.
    - The Set parameters values are lost once the stream/device is closed.
    - For a given stream/device, the aDSP can cache up to 8 Set parameters. \n
      \n
      For example, this means the client can set 8 Set parameters as follows: \n
      @verbatim
      Input -- 2, FL, FR
      Output -- 2, FL, FR
      Coefficients set #0 on index #0
      
      Input -- 5.1, FL, FR, FC, LS, RS, LFE 
      Output -- 2, FL, FR
      Coefficients set #1 on index #1
      ..
      ..
      Input -- 2, FL, C
      Output: FL, FR
      Coefficients set #7 on index #7

      @endverbatim
      \n
      The client can overwrite any of the mapping rules by providing the index
      number.
    - If there are multiple rows containing duplicate entries, the higher index
      rule (which is supposedly set later) is chosen and applied, if
      applicable.
    - The aDSP reverts to default coefficients (built-in coefficients) if the
      rule is not explicitly provided by the client (for example, if the input
      or output media types do not match the Set parameter rule provided.
    - The Set parameter must be called after stream, device, and routing is
      established. For the Set parameter to take effect correctly, Qualcomm
      recommends calling the Set parameter before the Run command.
*/
#define DEFAULT_CHMIXER_PARAM_ID_COEFF                                    0x00010342

/** @} */ /* end_name Channel Mixer module */
/** @} */ /* end_addtogroup asm_audpp_deprecated */
/** @endcond */

typedef struct default_chmixer_param_id_coeff default_chmixer_param_id_coeff;

#include "adsp_begin_pack.h"

/** @weakgroup weak_default_chmixer_param_id_coeff
@{ */
struct default_chmixer_param_id_coeff
{
    uint32_t                  index;
    /**< Index of the mapping rule the client is providing.

         @values 0 to 7 */

    uint16_t                  num_output_channels;
    /**< Number of output channels for this rule.

         @values 1 to 8 */

    uint16_t                  num_input_channels;
    /**< Number of input channels for this rule.

         @values 1 to 8 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_addtogroup weak_default_chmixer_param_id_coeff */

/** @ingroup admsvc_cmd_reg_iec61937_fmt
    Registers or deregisters for a 61937 media format change event to be raised
    for the stream router on a per-device basis. This command is valid only for
    Tx compressed devices.

  @apr_hdr_fields
    Opcode -- ADM_CMD_REGISTER_61937_FMT_UPDATE \n
    Dst_port -- DEVICE_ID

  @apr_msgpayload{adm_iec_61937_media_fmt_reg_t}
    @table{weak__adm__iec__61937__media__fmt__reg__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The device must have been opened through the
    #ADM_CMD_DEVICE_OPEN_V5 command.
*/
#define ADM_CMD_REGISTER_IEC_61937_FMT_UPDATE 0x00010345

typedef struct adm_iec_61937_media_fmt_reg_t adm_iec_61937_media_fmt_reg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_adm_iec_61937_media_fmt_reg_t
@{ */
struct adm_iec_61937_media_fmt_reg_t
{
   uint16_t device_id;
   /**< Index of the device ID.

        @values All values supported by the ADM */

   uint16_t enable;
   /**< Specifies whether media format events are to be raised (enabled).

        @values
        - 0 -- Disable
        - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_iec_61937_media_fmt_reg_t */

/** @ingroup admsvc_evt_reg_iec61937_fmt
   Indicates a change in the incoming Tx compressed format.

   @apr_hdr_fields
    Opcode -- ADM_IEC_61937_MEDIA_FMT_EVENT \n
    Src_port -- DEVICE_ID

  @apr_msgpayload{adm_iec_61937_media_fmt_event_t}
    @table{weak__adm__iec__61937__media__fmt__event__t}

  @detdesc
    This event occurrs under the following conditions:
     - This event has been registered.
     - After registration, the incoming compressed data format is different
       from what the stream router remembers in the last incoming format.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies 
    The device must have been opened through #ADM_CMD_DEVICE_OPEN_V5.
    @par
    #ADM_CMD_REGISTER_IEC_61937_FMT_UPDATE must have been issued to the relevant
    device ID.
*/
#define ADM_IEC_61937_MEDIA_FMT_EVENT  0x00010346

typedef struct adm_iec_61937_media_fmt_event_t adm_iec_61937_media_fmt_event_t;

#include "adsp_begin_pack.h" 

/** @weakgroup weak_adm_iec_61937_media_fmt_event_t
@{ */
struct adm_iec_61937_media_fmt_event_t
{
   uint16_t  device_id;
   /**< Index of the device ID.

        @values All values supported by the ADM */

   uint16_t  reserved;
    /**< Clients must set this field to zero. */

   uint32_t  new_format_id;
   /**< Incoming format ID.

        @values All supported values per the IEC 61937 standard (refer to
        @xhyperref{S1,[S1]}) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_adm_iec_61937_media_fmt_event_t */


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_ADM_API_H_ */
