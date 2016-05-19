/*========================================================================*/
/**
@file adsp_asm_stream_commands.h

This file contains ASM stream commands and events structures definitions.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      audio_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
Copyright (c) 2010-2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_asm_stream_commands.h#3 $

when       who     what, where, why
--------   ---      -------------------------------------------------------
09/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                    Doxygen comments/markup for 2.6.
09/06/13   sw      (Tech Pubs) Merged Doxygen comments from 2.0; edited
                    new Doxygen comments for 2.2.
08/06/12   sw      (Tech Pubs) Edited comments for Badger; updated Doxygen markup
                   to Rev D.2 templates; updated legal statements for QTI.
05/30/11   sw/leo  (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
04/22/11    ss     Introducing Audproc API file that would hold all post processing
                   Module IDs, Parameter IDs and Topology IDs
10/12/10   leo     (Tech Pubs) Edited/added Doxygen comments and markup.
04/15/10   rkc      Created file.
========================================================================== */

#ifndef _ADSP_ASM_STREAM_COMMANDS_H_
#define _ADSP_ASM_STREAM_COMMANDS_H_

#include "mmdefs.h"
#include "adsp_audproc_api.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


/** @addtogroup asmstrm_cmd_open_write_v2
@{ */
/** Creates an audio stream for playback. There is one decoder and one
    postprocessor chain, however, there is no decoder for PCM playback.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_WRITE_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_write_v2_t}
    @table{weak__asm__stream__cmd__open__write__v2__t}

  @detdesc
    When creating a stream, the client must specify the group and stream IDs.
    The current release supports up to 15 groups, and each
    group can have up to #ASM_MAX_STREAMS_PER_SESSION streams.
    @par
    This command has only the media format ID to open the decoder. The media
    format block is communicated to the aDSP through the
    #ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2 command before the data is sent.
    @par
    After successfully opening the stream, ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2
    must be sent in the data path to configure the decoder before sending
    any data.
    @par
    @keep{6}
    To achieve gapless playback, the client must open successive streams with
    the same session ID, but different stream IDs. Up to two streams can be
    open at the same time per session in Gapless mode. If the client tries to
    open a stream when two streams are already open in the session, an
    ADSP_EALREADY error code is returned.
    @par
    MIDI and DTMF formats are not supported in gapless playback. Any attempt
    to open streams in these formats in Gapless Playback mode returns the
    ADSP_EUNSUPPORTED error code. For more details on the error codes, refer
    to @xhyperref{Q5,[Q5]}.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client.

  @dependencies
    None.
*/
/* Q3 = Async Packet Router API Interface Spec for MDM9x15 (80-N1463-2)
   Q5 = Hex MM: AV Core Service API Interface Spec for 2.6 (80-NF770-4)
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_WRITE. Since
   ASM_STREAM_CMD_OPEN_WRITE_V2 is more general, ASM_STREAM_CMD_OPEN_WRITE is
   removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_WRITE_V2                                   0x00010D8F

/** Enumeration for a device matrix as an endpoint. */
#define ASM_STREAM_END_POINT_DEVICE_MTX                             0

/** Bitmask for an SR/CM change notification flag. */
#define ASM_BIT_MASK_SR_CM_CHANGE_NOTIFY_FLAG                       (0x00000004UL)

/** Bit shift for an SR/CM change notification flag. */
#define ASM_SHIFT_SR_CM_CHANGE_NOTIFY_FLAG                          2

/** Bitmask for Gapless mode. */
#define ASM_BIT_MASK_GAPLESS_MODE_FLAG                              (0x80000000UL)

/** Bit shift for Gapless mode. */
#define ASM_SHIFT_GAPLESS_MODE_FLAG                                 31

/** @} */ /* end_addtogroup asmstrm_cmd_open_write_v2 */

typedef struct asm_stream_cmd_open_write_v2_t asm_stream_cmd_open_write_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_write_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_WRITE_V2 command, which opens a write
    stream for a given session ID and stream ID. The dst_port field in the
    APR packet contains both the session ID and the stream ID.
*/
struct asm_stream_cmd_open_write_v2_t
{

    uint32_t                    mode_flags;
    /**< Configures the stream to notify the client when it detects an SR/CM
         change at the input to its POPP, and specifies whether the stream is
         to be opened in Gapless mode.

         @note1hang MIDI and DTMF streams cannot be opened in Gapless mode.

         @values{for bit 2}
         - 0 -- SR/CM change notification event is disabled
         - 1 -- SR/CM change notification event is enabled
         - To set/get this bit, use #ASM_BIT_MASK_SR_CM_CHANGE_NOTIFY_FLAG and
           #ASM_SHIFT_SR_CM_CHANGE_NOTIFY_FLAG

         @values{for bit 31}
         - 0 -- Stream to be opened in non-Gapless mode
         - 1 -- Stream to be opened in Gapless mode; successive streams must
           be opened with the same session ID but different stream IDs
         - To set/get this bit, use #ASM_BIT_MASK_GAPLESS_MODE_FLAG and
           #ASM_SHIFT_GAPLESS_MODE_FLAG

         All other bits are reserved; clients must set them to zero. */

    uint16_t                    sink_endpoint_type;
    /**< Sink point type.

         @values
         - 0 -- Device matrix (gateway to the hardware ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by ASM modules.

          @values 16, 24 */

    uint32_t                    postproc_topo_id;
    /**< Specifies the topology (order of processing) of postprocessing
         algorithms. <i>None</i> means no postprocessing.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    dec_fmt_id;
    /**< Configuration ID of the decoder media format.

         @values See Section @xref{dox:MediaFmtDecoderIds} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_write_v2_t */

/** @addtogroup asmstrm_cmd_open_write_v3
@{ */
/** Creates an audio stream for playback. There is one decoder and one
    postprocessor chain, however, there is no decoder for PCM playback.

    Unlike the #ASM_STREAM_CMD_OPEN_WRITE_V2 command, this command includes a
    stream_perf_mode subfield in the mode_flags field. This subfield indicates
    the performance mode in which this playback stream must be opened.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_WRITE_V3
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_write_v3_t}
    @table{weak__asm__stream__cmd__open__write__v3__t}

  @detdesc
    When creating a stream, the client must specify the group and stream IDs.
    The current release supports up to 15 groups, and each
    group can have up to #ASM_MAX_STREAMS_PER_SESSION streams.
    @par
    This command has only the media format ID to open the decoder. The media
    format block is communicated to the aDSP through the
    #ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2 command before the data is sent.
    @par
    After successfully opening the stream, ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2
    must be sent in the data path to configure the decoder before sending
    any data.
    @par
    To achieve gapless playback, the client must open successive streams with
    the same session ID, but different stream IDs. Up to two streams can be
    open at the same time per session in Gapless mode. If the client tries to
    open a stream when two streams are already open in the session, an
    ADSP_EALREADY error code is returned.
    @par
    MIDI and DTMF formats are not supported in gapless playback. Any attempt
    to open streams in these formats in Gapless Playback mode returns the
    ADSP_EUNSUPPORTED error code. (For more details on the error codes, refer
    to @xhyperref{Q5,[Q5]}.)

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client.

  @dependencies
    None.
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_WRITE. Since
   ASM_STREAM_CMD_OPEN_WRITE_V2 is more general, ASM_STREAM_CMD_OPEN_WRITE is
   removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_WRITE_V3                                   0x00010DB3

/** Bitmask for the stream_perf_mode subfield. */
#define ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_WRITE            (0x70000000UL)

/** Bit shift for the stream_perf_mode subfield. */
#define ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_WRITE                     28

/** Identifies a legacy stream session. */
#define ASM_LEGACY_STREAM_SESSION                                      0

/** Identifies a low latency stream session. */
#define ASM_LOW_LATENCY_STREAM_SESSION                                  1

/** Identifies an ultra low latency stream session. */
#define ASM_ULTRA_LOW_LATENCY_STREAM_SESSION                            2

/** @} */ /* end_addtogroup asmstrm_cmd_open_write_v3 */

/* Payload format for a stream open write command. */
typedef struct asm_stream_cmd_open_write_v3_t asm_stream_cmd_open_write_v3_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_write_v3_t
@{ */
/*  Payload of the ASM_STREAM_CMD_OPEN_WRITE_V3 command, which opens a
     write stream for a given session ID and stream ID.The dst_port field in
    the APR packet contains both the session ID and stream ID.
*/
struct asm_stream_cmd_open_write_v3_t
{

    uint32_t                    mode_flags;
    /**< Configures the stream to notify the client when it detects an SR/CM
         change at the input to its POPP, specifies whether the stream is to
         be opened in Gapless mode, and specifies the performance mode in which
         this stream must be opened.

         @note1hang MIDI and DTMF streams cannot be opened in Gapless mode.

         @values{for bit 2}
         - 0 -- SR/CM change notification event is disabled
         - 1 -- SR/CM change notification event is enabled
         - To set/get this bit, use #ASM_BIT_MASK_SR_CM_CHANGE_NOTIFY_FLAG and
           #ASM_SHIFT_SR_CM_CHANGE_NOTIFY_FLAG

         @contcell
         @values{for bits 30 to 28} (stream_perf_mode subfield)
         - #ASM_LEGACY_STREAM_SESSION -- Ensures backward compatibility to the
           original behavior of #ASM_STREAM_CMD_OPEN_WRITE_V2.
         - #ASM_LOW_LATENCY_STREAM_SESSION -- Opens a playback session by using
           shortened buffers in low latency POPP.
           - Recommendation: Do not enable high latency algorithms; they might
             negate the benefits of opening a low latency stream, and they
             might also suffer quality degradation from unexpected jitter.
           - The aDSP data path output latency contributed from the stream side
             can vary from 1 to 3 ms. In a steady state playback, this latency
             is measured as the average sample time difference between the
             sample that is currently being read from shared memory and the
             sample that is currently rendered to the DMA.
         - #ASM_ULTRA_LOW_LATENCY_STREAM_SESSION -- Opens a ULL 
           playback session by using shortened buffers in the decoder. There is
           no POPP processing in the ULL stream session.
           - Recommendation: Send the content whose bits per sample and number
             of channels match with the device to avoid processing in the aDSP.
           - Only PCM, 48 kHz, 16-bit/24-bit, mono/stereo data are supported.
           - The ULL stream session consists of output buffers
             with a duration of 1 ms. The aDSP data path output latency
             contributed by the stream session is 0 ms.
         - To configure this subfield, use
           #ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_WRITE and
           #ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_WRITE.

         @values{for bit 31}
         - 0 -- Stream to be opened in Non-Gapless mode
         - 1 -- Stream to be opened in Gapless mode; successive streams must
           be opened with the same session ID but different stream IDs
         - To set/get this bit, use #ASM_BIT_MASK_GAPLESS_MODE_FLAG and
           #ASM_SHIFT_GAPLESS_MODE_FLAG

         All other bits are reserved; clients must set them to zero. */

    uint16_t                    sink_endpoint_type;
    /**< Sink point type.

         @values 0 (ASM_SINK_MATRIX_STRTR) -- Device matrix (gateway to the
         hardware ports) */

    uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by ASM modules.

          @values 16, 24 */

    uint32_t                    postproc_topo_id;
    /**< Specifies the topology (order of processing) of postprocessing
         algorithms. <i>None</i> means no postprocessing.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    dec_fmt_id;
    /**< Configuration ID of the decoder media format.

         @values See Section @xref{dox:MediaFmtDecoderIds} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_write_v3_t */

/** @addtogroup asmstrm_cmd_open_read_v2
@{ */
/** Creates an audio stream for recording. There is one preprocessing chain and
    one encoder. If the encoder type is PCM playback, it is a pass-through
    encoder.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_READ_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_read_v2_t}
    @table{weak__asm__stream__cmd__open__read__v2__t}

  @detdesc
    This command creates a new record stream. It specifies the media format of
    the encoding to be performed by the aDSP. The encoder configuration block
    must be communicated to the aDSP through the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command before sending data buffers to get
    the encoded data from the aDSP.
    @par
    After successfully opening the stream, ASM_STREAM_CMD_SET_ENCDEC_PARAM
    must be sent in the command path to configure the encoder before encoded
    frames can be sent back to the client.
    @par
    @note1hang Sending multiple ASM_STREAM_CMD_SET_ENCDEC_PARAM commands for
               changing the encoder configuration is not allowed.
    @par
    Twenty-four-bit recording is supported only for the Linear PCM media format.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_READ. Since
   ASM_STREAM_CMD_OPEN_READ_V2 is more general, ASM_STREAM_CMD_OPEN_READ is
   removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_READ_V2                                    0x00010D8C

/** Definition of the metadata information flag bitmask. */
#define ASM_BIT_MASK_META_INFO_FLAG                                 (0x00000010UL)

/** Definition of the metadata information flag shift value. */
#define ASM_SHIFT_META_INFO_FLAG                                    4

/** Definition of the timestamp type flag bitmask. */
#define ASM_BIT_MASK_TIMESTAMP_TYPE_FLAG                            (0x00000020UL)

/** Definition of the timestamp type flag shift value. */
#define ASM_SHIFT_TIMESTAMP_TYPE_FLAG                                    5

/** Relative timestamp is identified by this value. */
#define ASM_RELATIVE_TIMESTAMP                                          0

/** Absolute timestamp is identified by this value. */
#define ASM_ABSOLUTE_TIMESTAMP                                          1

/** @} */ /* end_addtogroup asmstrm_cmd_open_read_v2 */

/* Payload format for a stream open read command. */
typedef struct asm_stream_cmd_open_read_v2_t asm_stream_cmd_open_read_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_read_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_READ_V2 command, which opens a read
    stream for a given session ID and stream ID. The dst_port field in the
    APR packet contains both the session ID and the stream ID.
*/
struct asm_stream_cmd_open_read_v2_t
{
    uint32_t                    mode_flags;
    /**< Indicates whether metadata per encoded frame is to be provided, and
         whether the timestamp is relative or absolute.

         @values{for bit 4}
         - 0 -- Return data buffer contains all encoded frames only; it does
           not contain frame metadata
         - 1 -- Return data buffer contains an array of metadata and encoded
           frames
         - To set this bit, use #ASM_BIT_MASK_META_INFO_FLAG and
           #ASM_SHIFT_META_INFO_FLAG

         @values{for bit 5}
         - #ASM_RELATIVE_TIMESTAMP -- #ASM_DATA_EVENT_READ_DONE_V2 has a
           relative timestamp
         - #ASM_ABSOLUTE_TIMESTAMP -- #ASM_DATA_EVENT_READ_DONE_V2 has an
           absolute timestamp
         - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_TYPE_FLAG and
           #ASM_SHIFT_TIMESTAMP_TYPE_FLAG

         All other bits are reserved; clients must set them to zero. */

    uint32_t                    src_endpoint_type;
    /**< Specifies the endpoint providing the input samples.

         @values
         - 0 -- Device matrix (gateway from the tunneled Tx ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint32_t                    preproc_topo_id;
    /**< Specifies the topology (order of processing) of preprocessing
         algorithms. <i>None</i> means no preprocessing.

         @values
         - #ASM_STREAM_PREPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_PREPROC_TOPO_ID_NONE
       @endif

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    enc_cfg_id;
    /**< Media configuration ID for encoded output.

         @values See Section @xref{dox:MediaFmtEncoderIds} */

     uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by ASM modules.

          @values 16, 24 */

     uint16_t                    reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_read_v2_t */

/** @addtogroup asmstrm_cmd_open_read_v3
@{ */
/** Creates an audio stream for recording. There is one preprocessing chain
    and one encoder. If the encoder type is PCM playback, it is a pass-through
    encoder.

    Unlike the #ASM_STREAM_CMD_OPEN_READ_V2 command, this command includes a
    stream_perf_mode subfield in the mode_flags field. This subfield indicates
    the performance mode in which this recording stream must be opened.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_READ_V3
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_read_v3_t}
    @table{weak__asm__stream__cmd__open__read__v3__t} @newpage

  @detdesc
    This command creates a new record stream. It specifies the media format of
    the encoding to be performed by the aDSP. The encoder configuration block
    must be communicated to the aDSP through the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command before sending data buffers to
    get the encoded data from the aDSP.
    @par
    After successfully opening the stream, ASM_STREAM_CMD_SET_ENCDEC_PARAM
    must be sent in the command path to configure the encoder before encoded
    frames can be sent back to the client.
    @par
    @note1hang Sending multiple ASM_STREAM_CMD_SET_ENCDEC_PARAM commands for
               changing the encoder configuration is not allowed.
    @par
    Twenty-four-bit recording is supported only for the Linear PCM media
    format.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_READ. Since
   ASM_STREAM_CMD_OPEN_READ_V2 is more general, ASM_STREAM_CMD_OPEN_READ is
   removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_READ_V3                                    0x00010DB4

/** Bitmask for the stream_perf_mode subfield. */
#define ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_READ            (0xe0000000UL)

/** Bit shift for the stream_perf_mode subfield. */
#define ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ                     29

/** @} */ /* end_addtogroup asmstrm_cmd_open_read_v3 */

/* Payload format for a stream open read command. */
typedef struct asm_stream_cmd_open_read_v3_t asm_stream_cmd_open_read_v3_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_read_v3_t
@{ */
/* Payload of the #ASM_STREAM_CMD_OPEN_READ_V3 command, which opens a
    read stream for a given session ID and stream ID. The dst_port field in
    the APR packet contains both the session ID and the stream ID.
*/
struct asm_stream_cmd_open_read_v3_t
{
    uint32_t                    mode_flags;
    /**< Indicates whether metadata per encoded frame is to be provided,
         whether the timestamp is relative or absolute, and the Performance
         mode in which this stream was opened.

         @values{for bit 4}
         - 0 -- Return data buffer contains all encoded frames only; it does
           not contain frame metadata
         - 1 -- Return data buffer contains an array of metadata and encoded
           frames
         - To set this bit, use #ASM_BIT_MASK_META_INFO_FLAG and
           #ASM_SHIFT_META_INFO_FLAG

         @values{for bit 5}
         - #ASM_RELATIVE_TIMESTAMP -- #ASM_DATA_EVENT_READ_DONE_V2 has a
           relative timestamp
         - #ASM_ABSOLUTE_TIMESTAMP -- #ASM_DATA_EVENT_READ_DONE_V2 has an
           absolute timestamp
         - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_TYPE_FLAG and
           #ASM_SHIFT_TIMESTAMP_TYPE_FLAG

         @contcell
         @values{for bits 31 to 29} (stream_perf_mode subfield)
         - #ASM_LEGACY_STREAM_SESSION -- Ensures backward compatibility to the
           original behavior of #ASM_STREAM_CMD_OPEN_READ_V2.
         - #ASM_LOW_LATENCY_STREAM_SESSION -- Opens a record session using
           shortened buffers in low latency POPreP.
           - Recommendation: Do not enable high latency algorithms; they might
             negate the benefits of opening a low latency stream, and they
             might also suffer quality degradation from unexpected jitter.
           - The aDSP data path output latency contributed from the stream side
             can vary from 1 to 2 ms. In steady state recording, this latency
             is measured as the average sample time difference between the
             sample that is currently being read from the DMA and the sample
             that is currently written to shared memory.
         - To configure this subfield, use
           #ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_READ and
           #ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_READ.

         All other bits are reserved; clients must set them to zero. */

    uint32_t                    src_endpoint_type;
    /**< Specifies the endpoint providing the input samples.

         @values
         - 0 -- Device matrix (gateway from the tunneled Tx ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint32_t                    preproc_topo_id;
    /**< Specifies the topology (order of processing) of preprocessing
         algorithms. <i>None</i> means no preprocessing.

         @values
         - #ASM_STREAM_PREPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_PREPROC_TOPO_ID_NONE
       @endif

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    enc_cfg_id;
    /**< Media configuration ID for encoded output.

         @values See Section @xref{dox:MediaFmtEncoderIds} */

     uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by ASM modules.

          @values 16, 24 */

     uint16_t                    reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_read_v3_t */

/** @addtogroup asmstrm_cmd_open_readwrite
@{ */
/** Opens a read/write stream with configurable bits per sample.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_READWRITE_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_readwrite_v2_t}
    @table{weak__asm__stream__cmd__open__readwrite__v2__t}

  @detdesc
    A read/write stream is opened for a given session ID and stream ID. The
    dst_port field in the APR packet contains both the session ID and the
    stream ID.
    @par
    After successfully opening the stream, a set_encdec_params command must be
    sent in the command path to configure the encoder before encoded frames
    can be sent back to the client (even if it is a PCM encoder used for NT
    decoding). Also, a media format update command must be sent on the data
    path to configure the decoder before sending any data.
    @par
    This command specifies the media format of the encoding to be performed by
    the Hexagon processor. The encoder configuration block must be
    communicated to the Hexagon processor through the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command before sending data buffers to
    get the encoded data from the Hexagon processor.
    @par
    @note1hang Sending multiple ASM_STREAM_CMD_SET_ENCDEC_PARAM commands for
               changing the encoder configuration is not allowed.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_READWRITE. Since
   ASM_STREAM_CMD_OPEN_READWRITE_V2 is more general,
   ASM_STREAM_CMD_OPEN_READWRITE is removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_READWRITE_V2                                0x00010D8D

/** Enumeration for native sampling rate signaling at the POPP output. */
#define ASM_POPP_OUTPUT_SR_NATIVE_RATE                                  0

/** Enumeration for the maximum sampling rate at the POPP output. */
#define ASM_POPP_OUTPUT_SR_MAX_RATE                                     48000

/** @} */ /* end_addtogroup asmstrm_cmd_open_readwrite */

/* Payload format for a stream open read/write command. */
typedef struct asm_stream_cmd_open_readwrite_v2_t asm_stream_cmd_open_readwrite_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_readwrite_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_READWRITE_V2 command.
*/
struct asm_stream_cmd_open_readwrite_v2_t
{
    uint32_t                    mode_flags;
    /**< Configures the stream to notify the client when it detects a CM/SR
         change at the input to its POPP. This field also specifies whether
         metadata per encoded frame is to be provided.

         @values{for bit 2}
         - 0 -- SR/CM change notification event is disabled
         - 1 -- SR/CM change notification event is enabled
         - To set/get this bit, use #ASM_BIT_MASK_SR_CM_CHANGE_NOTIFY_FLAG and
           #ASM_SHIFT_SR_CM_CHANGE_NOTIFY_FLAG

         @values{for bit 4}
         - 0 -- Return read data buffer contains all encoded frames only; it
           does not contain frame metadata
         - 1 -- Return read data buffer contains an array of metadata and
           encoded frames
         - To set/get this bit, use #ASM_BIT_MASK_META_INFO_FLAG and
           #ASM_SHIFT_META_INFO_FLAG

         All other bits are reserved; clients must set them to zero. */

    uint32_t                    postproc_topo_id;
    /**< Specifies the topology (order of processing) of postprocessing
         algorithms. <i>None</i> means no postprocessing.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    dec_fmt_id;
    /**< Specifies the media type of the input data. PCM indicates that no
         decoding must be performed (for example, this is an NT encoder
         session.

         @values  See Section @xref{dox:MediaFmtDecoderIds} */

    uint32_t                    enc_cfg_id;
    /**< Specifies the media type for the output of the stream. PCM indicates
         that no encoding must be performed (for example, this is an NT decoder
         session.

         @values See Section @xref{dox:MediaFmtEncoderIds} */

     uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by ASM modules.

          @values 16, 24 */

     uint16_t                    reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_readwrite_v2_t */

/** @ingroup asmstrm_cmd_open_loopback
    Opens a loopback stream for a given session ID and stream ID.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_LOOPBACK_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_loopback_v2_t}
    @table{weak__asm__stream__cmd__open__loopback__v2__t}

  @keep{8} @detdesc
    This command sets up the stream portion of the ASM Loopback mode
    topology. This is different from a read stream and a write stream in that
    there are no buffers exchanged between the aDSP and client. The session to
    which this stream belongs cannot have any other streams.
    @par
    The POPP topology ID must be specified. This command sets up the connection
    from the Tx Matrix output port to the POPP input port, and from the POPP
    output port to the Rx Matrix input port.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
/* API_developer_note: A family also had ASM_STREAM_CMD_OPEN_LOOPBACK. Since
   ASM_STREAM_CMD_OPEN_LOOPBACK_V2 is more general,
   ASM_STREAM_CMD_OPEN_LOOPBACK is removed in B family.
*/
#define ASM_STREAM_CMD_OPEN_LOOPBACK_V2                              0x00010D8E

/* Payload format for stream open loopback */
typedef struct asm_stream_cmd_open_loopback_v2_t asm_stream_cmd_open_loopback_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_loopback_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_LOOPBACK_V2 command, which opens a loopback
    stream with configurable bits per sample. The dst_port field in the APR
    packet contains both the session ID and stream ID.
*/
struct asm_stream_cmd_open_loopback_v2_t
{
    uint32_t                    mode_flags;
    /**< All bits are reserved. Clients must set them to zero. */

    uint16_t                    src_endpoint_type;
    /**< Specifies the source endpoint that provides the input samples.

         @values
         - 0 -- Tx device matrix (gateway to the hardware ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint16_t                    sink_endpoint_type;
    /**< Specifies the sink endpoint type.

         @values
         - 0 -- Rx device matrix (gateway to the hardware ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint32_t                    postproc_topo_id;
    /**< Postprocessing topology ID, which specifies the topology (order of
         processing) of postprocessing algorithms.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_PEAKMETER
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

     uint16_t                    bits_per_sample;
      /**< Number of bits per sample processed by the ASM modules.

          @values 16, 24 */

     uint16_t                    reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_loopback_v2_t */

/** @addtogroup asmstrm_cmd_open_tcode_lpbk
@{ */
/** Opens a transcode loopback stream, which routes the stream from a
    device (either compressed or PCM) to another device (compressed or PCM)
    after decoding or encoding, or as is.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_TRANSCODE_LOOPBACK
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_transcode_loopback_t}
    @table{weak__asm__stream__cmd__open__transcode__loopback__t}
  
  @detdesc
    Following are the possible loopbacks:
    - PCM to PCM: \n
      Tx matrix @rarrow POPP @rarrow Rx matrix
    - PCM to compressed: \n
      Tx matrix @rarrow POPP @rarrow Encoder @rarrow Rx stream router
    - @keep{5} Compressed to compressed: \n
      Tx Stream router @rarrow Decoder @rarrow POPP @rarrow Encoder @rarrow
      Rx stream router
      (selected if source and sink non-PCM formats are different, and the
      converter mode = #ASM_CONVERTER_MODE_NONE or
      #ASM_POST_PROCESS_CONVERTER_MODE)
    - Compressed to compressed: \n
      Tx Stream router @rarrow Decoder converter @rarrow Rx stream router
      (selected based on the converter mode)
    - Compressed to compressed: \n
      Tx stream router @rarrow Rx stream router (direct passthrough)
      (selected if source and sink non-PCM formats are the same, and the
      converter mode = ASM_CONVERTER_MODE_NONE)
    - Compressed to PCM: \n
      Tx stream router @rarrow Decoder @rarrow POPP @rarrow Rx matrix

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
#define ASM_STREAM_CMD_OPEN_TRANSCODE_LOOPBACK                         0x00010DBA

/** Bitmask for the stream's Performance mode. */
#define ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_TRANSCODE_LOOPBACK    (0x70000000UL)

/** Bit shift for the stream's Performance mode. */
#define ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_TRANSCODE_LOOPBACK           28

/** Bitmask for the decoder converter enable flag. */
#define ASM_BIT_MASK_DECODER_CONVERTER_FLAG                          (0x00000078UL)

/** Shift value for the decoder converter enable flag. */
#define ASM_SHIFT_DECODER_CONVERTER_FLAG                              3

/** Converter mode is None (Default). */
#define ASM_CONVERTER_MODE_NONE                    0

/** @cond OEM_only */
/** Converter mode is DDP-to-DD. */
#define ASM_DDP_DD_CONVERTER_MODE                                     1
/** @endcond */

/** Identifies a special converter mode where source and sink formats are the
    same but postprocessing must applied. Therefore, Decode @rarrow Re-encode
    is necessary. */
#define ASM_POST_PROCESS_CONVERTER_MODE                                     2

/** @} */ /* end_addtogroup asmstrm_cmd_open_tcode_lpbk */

/* Payload format for stream open loopback */
typedef struct asm_stream_cmd_open_transcode_loopback_t asm_stream_cmd_open_transcode_loopback_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_transcode_loopback_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_TRANSCODE_LOOPBACK command, which opens
    a loopback stream with configurable bits per sample.
*/
struct asm_stream_cmd_open_transcode_loopback_t
{
    uint32_t                    mode_flags;
    /**< Indicates the Performance mode in which this stream is to be opened.

         @values{for bits 30 to 28} (stream_perf_mode flag)
         - #ASM_LEGACY_STREAM_SESSION -- This mode ensures backward
           compatibility to the original behavior of
           ASM_STREAM_CMD_OPEN_TRANSCODE_LOOPBACK
         - #ASM_LOW_LATENCY_STREAM_SESSION -- Opens a loopback session by using
           shortened buffers in low latency POPP
           - Recommendation: Do not enable high latency algorithms; they might
             negate the benefits of opening a low latency stream, and they
             might also suffer quality degradation from unexpected jitter.
           - This Low Latency mode is supported only for PCM In and PCM Out
             loopbacks. An error is returned if Low Latency mode is opened for
             other transcode loopback modes.
         - To configure this subfield, use
           #ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_TRANSCODE_LOOPBACK and
           #ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_TRANSCODE_LOOPBACK.

         @values{for bits 6 to 3} (decoder-converter compatibility)
         - #ASM_CONVERTER_MODE_NONE (0x0) -- Default
       @if OEM_only
         - #ASM_DDP_DD_CONVERTER_MODE (0x1)
       @endif
         - #ASM_POST_PROCESS_CONVERTER_MODE (0x2)
         - 0x3-0xF -- Reserved for future use
         - Use #ASM_BIT_MASK_DECODER_CONVERTER_FLAG and
           #ASM_SHIFT_DECODER_CONVERTER_FLAG to set this bit

         All other bits are reserved; clients must set them to zero. */

    uint32_t                    src_format_id;
    /**< Specifies the media format of the input audio stream.

         @values
         - #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2
         - #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3
       @if OEM_only
         - #ASM_MEDIA_FMT_DTS
         - #ASM_MEDIA_FMT_EAC3_DEC
         - #ASM_MEDIA_FMT_EAC3
         - #ASM_MEDIA_FMT_AC3_DEC
         - #ASM_MEDIA_FMT_AC3
       @endif
         @tablebulletend */

    uint32_t                    sink_format_id;
    /**< Specifies the media format of the output stream.

         @values
         - #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2
         - #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3
       @if OEM_only
         - #ASM_MEDIA_FMT_DTS (not supported in Low Latency mode)
         - #ASM_MEDIA_FMT_EAC3_DEC (not supported in Low Latency mode)
         - #ASM_MEDIA_FMT_EAC3 (not supported in Low Latency mode)
         - #ASM_MEDIA_FMT_AC3_DEC (not supported in Low Latency mode)
         - #ASM_MEDIA_FMT_AC3 (not supported in Low Latency mode)
       @endif
         @tablebulletend */

    uint32_t                    audproc_topo_id;
    /**< Postprocessing topology ID, which specifies the topology (order of
         processing) of postprocessing algorithms.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_PEAKMETER
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES.

         This field is ignored for the Converter mode, in which no
         postprocessing is performed. */

    uint16_t                    src_endpoint_type;
    /**< Specifies the source endpoint that provides the input samples.

         @values
         - 0 -- Tx device matrix or stream router (gateway to the hardware
           ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint16_t                    sink_endpoint_type;
    /**< Specifies the sink endpoint type.

         @values
         - 0 -- Rx device matrix or stream router (gateway to the hardware
           ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

     uint16_t                    bits_per_sample;
     /**< Number of bits per sample processed by the ASM modules.

          @values 16, 24 */

     uint16_t                    reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_transcode_loopback_t */

/** @ingroup asmstrm_cmd_close
    Stops and closes a specified stream.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_CLOSE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The stream must be a valid session stream.
*/
#define ASM_STREAM_CMD_CLOSE                                        0x00010BCD

/** @ingroup asmstrm_cmd_flush
    Flushes a specified stream.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_FLUSH
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The stream's session must be paused; otherwise, an error is returned.
*/
#define ASM_STREAM_CMD_FLUSH                                        0x00010BCE

/** @addtogroup asmstrm_cmd_flush_v2
@{ */
/** Flushes a specified stream. This command differs from ASM_STREAM_CMD_FLUSH
    in that it provides an option of whether to flush a bitstream.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_FLUSH_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    @table{weak__asm__stream__cmd__flush__v2__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The stream's session must be paused; otherwise, an error is returned.
*/
#define ASM_STREAM_CMD_FLUSH_V2                                        0x00010DEB

/** Bitmask for the mode flags. */
#define ASM_BIT_MASK_FLUSH_V2_MODE                                        (0x00000001UL)

/** Bit shift for the mode flag that is used to specify whether to flush the
    bitstream. */
#define ASM_SHIFT_MASK_FLUSH_MODE_NOT_TO_FLUSH_BISTREAM                   0

/** Do not flush the bitstream. */
#define ASM_STREAM_NOT_TO_FLUSH_BITSTREAM                                 1

/** @} */ /* end_addtogroup asmstrm_cmd_flush_v2 */

/* Payload format for flush command v2 */
typedef struct asm_stream_cmd_flush_v2_t asm_stream_cmd_flush_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_flush_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_FLUSH_V2 command, which has option either
    to flush the bitstream or not.
*/
struct asm_stream_cmd_flush_v2_t
{
    uint32_t                    mode_flags;
    /**< Bit 0 specifies whether to flush the bitstream.

         @values
         - 0 = Flush the bistream
         - 1 = Do not flush the bitstream
         - To set this flag, use #ASM_BIT_MASK_FLUSH_V2_MODE @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_flush_v2_t */

/** @ingroup asmstrm_cmd_flush_readbufs
    Flushes a tunneled Tx or non-tunneled stream's output buffers.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_FLUSH_READBUFS
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @detdesc
    This command is used in read and read/write streams to allow the client
    to retrieve all shared memory buffers for size reallocation, without
    flushing any of the data pipelined in the stream. An example is a sample
    rate or channel configuration change in a non-tunneled decoder.
    @par
    The behavior is to deliver first any partially filled output buffers
    with #ASM_DATA_EVENT_READ_DONE_V2, followed by all the queued empty output
    buffers.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The stream must be either a tunneled Tx stream opened by
    #ASM_STREAM_CMD_OPEN_READ_V2 or a non-tunneled stream opened by
    #ASM_STREAM_CMD_OPEN_READWRITE_V2.
*/
#define ASM_STREAM_CMD_FLUSH_READBUFS                               0x00010C09

/** @ingroup asmstrm_cmd_set_pp_params
    Sets one or more ASM stream parameters to a POPP chain. Supported module
    and parameter IDs are provided in Chapter @xref{hdr:AudioPostProcIDs}.

    This command is typically used to apply settings to the POPP or
    Per-Group-Object Pre/postprocessing (PGOPP) chains.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_SET_PP_PARAMS_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_set_pp_params_v2_t}
    If data_payload_addr=NULL, immediately following are a series of
    <b>Parameter data variable payload</b> structures
    (%asm_stream_param_data_v2_t) whose total size is data_payload_size bytes.
    @tablens{weak__asm__stream__cmd__set__pp__params__v2__t} @newpage

  @par Parameter data variable payload (asm_stream_param_data_v2_t)
    @tablens{weak__asm__stream__param__data__v2__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    This command must be applied to a valid stream.
    @par
    A memory map handle must be obtained from the aDSP using the
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.
*/
/* API_developer_note: A family API ASM_STREAM_CMD_SET_PP_PARAMS is replaced
   by ASM_STREAM_CMD_SET_PP_PARAMS_V2.
*/
#define ASM_STREAM_CMD_SET_PP_PARAMS_V2                                0x00010DA1

/* Payload format for a stream Set Parameters command. */
typedef struct asm_stream_cmd_set_pp_params_v2_t asm_stream_cmd_set_pp_params_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_set_pp_params_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_SET_PP_PARAMS_V2 command, which allows
    one or more parameters to be set on a stream. If data_payload_addr=NULL, a
    series of parameter data structures immediately follow, whose
    total size is data_payload_size bytes.
*/
struct asm_stream_cmd_set_pp_params_v2_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the parameter data payload address.  */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the parameter data payload address.

         The 64-bit number formed by data_payload_addr_lsw and
         data_payload_addr_msw must be set to zero for in-band data. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address. This memory map handle is returned
         by the aDSP through the #ASM_CMD_SHARED_MEM_MAP_REGIONS command.

         @values
         - NULL -- Parameter data payloads are within the message payload
           (in-band).
         - Non-NULL -- Parameter data payloads begin at the address specified
           in the data_payload_addr_lsw and data_payload_addr_msw fields
           (out-of-band).

         If the address is sent (non-NULL), the
         <b>Parameter data variable payload</b> begins at the specified data
         payload address. */

    uint32_t                  data_payload_size;
    /**< Actual size of the variable payload accompanying the message, or in
         shared memory. This field is used for parsing the parameter payload.

         @values > 0 bytes */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_set_pp_params_v2_t */

/* Payload format for stream parameter data. */
typedef struct asm_stream_param_data_v2_t asm_stream_param_data_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_param_data_v2_t
@{ */
/* Payload of the stream parameter data of the
    ASM_STREAM_CMD_SET_PP_PARAMS_V2 command. */
/** Immediately following this structure are param_size bytes of parameter
    data, which must be aligned to 32 bytes. The structure and size depend on
    the module_id/param_id pair.
*/
struct asm_stream_param_data_v2_t
{
    uint32_t                  module_id;
    /**< Valid ID of the module to be configured
         (see Chapter @xref{hdr:AudioPostProcIDs}). */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured
         (see Chapter @xref{hdr:AudioPostProcIDs}). */

    uint16_t                  param_size;
    /**< Data size of the param_id/module_id combination. This is a multiple
         of four bytes.

         @values > 0 bytes */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_param_data_v2_t */

/** @ingroup asmstrm_cmd_get_pp_params
    Queries for an audio processing service parameter of a stream.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_GET_PP_PARAMS_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_get_pp_params_v2_t}
    @table{weak__asm__stream__cmd__get__pp__params__v2__t}

  @return
    #ASM_STREAM_CMDRSP_GET_PP_PARAMS_V2

  @dependencies
    This command must be applied to a valid stream.
    @par
    A memory map handle must be obtained from the aDSP using the
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.
*/
#define ASM_STREAM_CMD_GET_PP_PARAMS_V2                                0x00010DA2

/* Payload format for a stream get parameters command. */
typedef struct asm_stream_cmd_get_pp_params_v2_t asm_stream_cmd_get_pp_params_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_get_pp_params_v2_t
@{ */
/* Payload of the ASM_STREAM_CMD_GET_PP_PARAMS_V2 command, which allows
    a query for one pre/postprocessing parameter of a stream.
*/
struct asm_stream_cmd_get_pp_params_v2_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the parameter data payload address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the parameter data payload address.

         The size of the shared memory, if specified, must be large enough to
         contain the entire parameter data payload. For details, see the
         <b>Parameter data variable payload</b> in
         #ASM_STREAM_CMD_SET_PP_PARAMS_V2.

         The 64-bit number formed by data_payload_addr_lsw and
         data_payload_addr_msw must be set to zero for in-band data.

         @tblsubhd{For a 32-bit shared memory address} This field must be set
         to zero.

         @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
         field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command and is used only for
         out-of-band messages. For in-band messages, this field must be set to
         zero.

         @values
         - NULL -- Parameter data payloads in the acknowledgment are within
           the message payload (in-band).
         - Non-NULL -- Parameter data payloads  in the acknowledgment begin at
           the address specified in the data_payload_addr_lsw and
           data_payload_addr_msw fields (out-of-band).

         If the address is sent (non-NULL), the Parameter data variable
         payload (see #ASM_STREAM_CMD_SET_PP_PARAMS_V2) begins at the
         specified address. */

    uint32_t                  module_id;
    /**< Valid ID of the module to be configured
         (see Chapter @xref{hdr:AudioPostProcIDs}). */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured
         (see Chapter @xref{hdr:AudioPostProcIDs}). */

    uint16_t                  param_max_size;
    /**< Maximum data size of the module_id/param_id combination. This is a
         multiple of four bytes.

         @values > 0 bytes */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_get_pp_params_v2_t */


/** @ingroup asmstrm_cmd_get_pp_topo_mod_list
    Queries the ADM service to get a list of modules in a POPP/POPreP
    topology.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_GET_PP_TOPO_MODULE_LIST
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID  1 -- #ASM_MAX_STREAMS_PER_SESSION

  @msgpayload{asm_stream_cmd_get_pp_topo_module_list_t}
    Immediately following this structure is the <b>Parameter data payload</b>
    (audproc_topology_module_id_info_t).
    @tablens{weak__asm__stream__cmd__get__pp__topo__module__list__t}

  @par Parameter data payload (audproc_topology_module_id_info_t)
    @table{weak__audproc__topology__module__id__info__t}

  @return
    #ASM_STREAM_CMDRSP_GET_PP_TOPO_MODULE_LIST

  @dependencies
    This command must be applied to a valid stream.
    @par
    A memory map handle must be obtained from the aDSP using the
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.
*/
#define ASM_STREAM_CMD_GET_PP_TOPO_MODULE_LIST                   0x00012F21

/* Payload format for a stream get topo modules list command. */
typedef struct asm_stream_cmd_get_pp_topo_module_list_t asm_stream_cmd_get_pp_topo_module_list_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_get_pp_topo_module_list_t
@{ */
/* Payload of the ASM_STREAM_CMD_GET_PP_TOPO_MODULE_LIST command, which allows
    a query for one pre/postprocessing parameter of a stream.
*/
struct asm_stream_cmd_get_pp_topo_module_list_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the parameter data payload address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the parameter data payload address.

         The size of the shared memory, if specified, must be large enough to
         contain the entire parameter data payload.

         The 64-bit number formed by data_payload_addr_lsw and
         data_payload_addr_msw must be set to zero for in-band data.

         @subhead{For a 32-bit shared memory address} This field must be set
         to zero.

         @subhead{For a 36-bit shared memory address} Bits 31 to 4 of this
         field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command and is used only for
         out-of-band messages. For in-band messages, this field must be set to
         zero.

         @values
         - NULL -- Parameter data payloads in the acknowledgment are within
           the message payload (in-band).
         - Non-NULL -- Parameter data payloads  in the acknowledgment begin at
           the address specified in the data_payload_addr_lsw and
           data_payload_addr_msw fields (out-of-band).

         If the address is sent (non-NULL), the parameter data payload begins
         at the specified address. */

    uint16_t                  param_max_size;
    /**< Maximum data size of the module_id list. This is a multiple of four
         bytes.

         @values > 0 bytes */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_get_pp_topo_module_list_t */

/** @ingroup asmstrm_cmd_set_encdec_params
    Sets one parameter for the encoder/decoder on a stream. This is typically
    used to change encoder/decoder settings during runtime.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_SET_ENCDEC_PARAM
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_set_encdec_param_t}
    @tablens{weak__asm__stream__cmd__set__encdec__param__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    This command must be applied to a valid stream.
*/
#define ASM_STREAM_CMD_SET_ENCDEC_PARAM                             0x00010C10

/* Payload format for an ASM stream Set Encoder/Decoder Parameter
    command. */
typedef struct asm_stream_cmd_set_encdec_param_t asm_stream_cmd_set_encdec_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_set_encdec_param_t
@{ */
/* Payload of the ASM_STREAM_CMD_SET_ENCDEC_PARAM command. */
/** Immediately following this structure are param_size bytes representing
    the parameter data. The size depends on the param_id/param_size
    combination.
*/
struct asm_stream_cmd_set_encdec_param_t
{
    uint32_t                  param_id;
    /**< Valid ID of the parameter to be configured.

       @if OEM_only
         @values
         - #ASM_PARAM_ID_ENCDEC_BITRATE
         - #ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2
         - #ASM_PARAM_ID_AAC_SBR_PS_FLAG
         - #ASM_PARAM_ID_AAC_DUAL_MONO_MAPPING
         - #ASM_PARAM_ID_AC3_CHANNEL_CONFIG
         - #ASM_PARAM_ID_AC3_LFE_MODE
         - #ASM_PARAM_ID_AC3_NUM_OUTPUT_CHANNELS
         - #ASM_PARAM_ID_AC3_ERROR_CONCEAL
         - #ASM_PARAM_ID_AC3_ERROR_MAX_RPTS
         - #ASM_PARAM_ID_AC3_CNV_ERROR_CONCEAL
         - #ASM_PARAM_ID_AC3_SUBSTREAM_SELECT
         - #ASM_PARAM_ID_AC3_MDCT_BANDLIMITING_MODE
         - #ASM_PARAM_ID_AC3_DRC_SUPPRESSION_MODE
         - #ASM_PARAM_ID_AC3_EXT_BOOST
         - #ASM_PARAM_ID_AC3_KARAOKE_MODE
         - #ASM_PARAM_ID_AC3_DRC_MODE
         - #ASM_PARAM_ID_AC3_DUAL_MONO_MODE
         - #ASM_PARAM_ID_AC3_STEREO_DOWNMIX_MODE
         - #ASM_PARAM_ID_AC3_PCM_SCALEFACTOR
         - #ASM_PARAM_ID_AC3_DRC_BOOST_SCALEFACTOR
         - #ASM_PARAM_ID_AC3_DRC_CUT_SCALEFACTOR @tablebulletend
       @endif
       @if ISV_only
         @values #ASM_PARAM_ID_DEC_OUTPUT_CHAN_MAP ??
       @endif */

    uint32_t                  param_size;
    /**< Data size in bytes of this parameter. The size is a multiple of
         four bytes.

         @values > 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_set_encdec_param_t */

/** @cond OEM_only */
/** @ingroup asmstrm_cmd_set_encdec_params
    ID of the Audio Encoder/Decoder Bitrate parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    @msgpayload{asm_bitrate_param_t}
    @table{weak__asm__bitrate__param__t}
*/
#define ASM_PARAM_ID_ENCDEC_BITRATE                                 0x00010C13

/* Structure for the bitrate parameter. */
typedef struct asm_bitrate_param_t asm_bitrate_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_bitrate_param_t
@{ */
/* Payload of the ASM_PARAM_ID_ENCDEC_BITRATE parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_bitrate_param_t
{
    uint32_t                  bitrate;
    /**< Maximum supported bitrate. Only the AAC encoder is supported.

         @values See @xhyperref{tbl:AACencoderAllowedBitrates,AAC encoder
                 allowed bitrates} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_bitrate_param_t */
/** @endcond */

/** @cond OEM_only */
/** @ingroup asmstrm_cmd_set_encdec_params
    ID of the Immediate Decode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    @msgpayload{asm_enc_cfg_blk_param_v2_t}
    @tablens{weak__asm__enc__cfg__blk__param__v2__t} @newpage
*/
#define ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2                             0x00010DA3

/* Structure for an encoder configuration block. */
typedef struct asm_enc_cfg_blk_param_v2_t asm_enc_cfg_blk_param_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_enc_cfg_blk_param_v2_t
@{ */
/* Payload of the ASM_PARAM_ID_ENCDEC_ENC_CFG_BLK_V2 parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command. */
/** Immediately following this structure is an encoder configuration block
    of size enc_cfg_blk_size bytes (see Section
    @xref{dox:MediaFmtEncoderIds}).
*/
struct asm_enc_cfg_blk_param_v2_t
{
    uint32_t                  frames_per_buf;
    /**< Number of encoded frames to pack into each buffer.

         @values > 0

         @note1hang This is simply guidance information for the aDSP. The
                    number of encoded frames put into each buffer (specified
                    by the client) is less than or equal to this number. */

    uint32_t                  enc_cfg_blk_size;
    /**< Size of the encoder configuration block that follows this member.

         @values @ge 0 bytes */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_enc_cfg_blk_param_v2_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** Parameter ID of the AAC decoder SBR/PS Enable flag in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    @msgpayload{asm_aac_sbr_ps_flag_param_t}
    @table{weak__asm__aac__sbr__ps__flag__param__t}
*/
#define ASM_PARAM_ID_AAC_SBR_PS_FLAG                                0x00010C63

/** Flag to turn off both SBR and PS processing, if they are present in the
    bitstream.
*/
#define ASM_AAC_SBR_OFF_PS_OFF                                      (2)

/** Flag to turn on SBR but turn off PS processing,if they are present in the
    bitstream.
*/
#define ASM_AAC_SBR_ON_PS_OFF                                       (1)

/** Flag to turn on both SBR and PS processing, if they are present in the
    bitstream (default behavior). @newpage
*/
#define ASM_AAC_SBR_ON_PS_ON                                        (0)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */

/* Structure for an AAC SBR PS processing flag. */
typedef struct asm_aac_sbr_ps_flag_param_t asm_aac_sbr_ps_flag_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_aac_sbr_ps_flag_param_t
@{ */
/* Payload of the ASM_PARAM_ID_AAC_SBR_PS_FLAG parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_aac_sbr_ps_flag_param_t
{
    uint32_t                  sbr_ps_flag;
    /**< Control parameter that enables or disables SBR/PS processing in the
         AAC bitstream. Changes are applied to the next decoded frame.

         @values
         - #ASM_AAC_SBR_OFF_PS_OFF
         - #ASM_AAC_SBR_ON_PS_OFF
         - #ASM_AAC_SBR_ON_PS_ON (Default)

         All other values are invalid. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_aac_sbr_ps_flag_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AAC decoder Dual Mono Channel Mapping parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to AAC dual mono bitstream decoding. The
    command can be sent any time after opening a write or read/write stream,
    and the changes take effect from the next decoded frame.

    The same SCE can be routed to both he left and right channels. The
    following table shows the message payload for AAC dual mono channel
    mapping, where all the channels are valid.

    @msgpayload{asm_aac_dual_mono_mapping_param_t}
    @table{weak__asm__aac__dual__mono__mapping__param__t}
*/
#define ASM_PARAM_ID_AAC_DUAL_MONO_MAPPING                      0x00010C64

/** First single channel element in a dual mono bitstream. */
#define ASM_AAC_DUAL_MONO_MAP_SCE_1                                 (1)

/** Second single channel element in a dual mono bitstream. @newpage */
#define ASM_AAC_DUAL_MONO_MAP_SCE_2                                 (2)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */

/* Structure for AAC decoder dual mono channel mapping. */
typedef struct asm_aac_dual_mono_mapping_param_t asm_aac_dual_mono_mapping_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_aac_dual_mono_mapping_param_t
@{ */
/* Payload of the ASM_PARAM_ID_AAC_DUAL_MONO_MAPPING parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_aac_dual_mono_mapping_param_t
{
    uint16_t                  left_channel_sce;
    /**< Specifies which SCE is connected to the left channel.

         @values
         - #ASM_AAC_DUAL_MONO_MAP_SCE_1 (Default)
         - #ASM_AAC_DUAL_MONO_MAP_SCE_2 @tablebulletend */

    uint16_t                  right_channel_sce;
    /**< Specifies which SCE is connected to the right channel.

         @values
         - #ASM_AAC_DUAL_MONO_MAP_SCE_1 (Default)
         - #ASM_AAC_DUAL_MONO_MAP_SCE_2 @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_aac_dual_mono_mapping_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AAC decoder Stereo Mixing parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to AAC bitstream decoding. The
    command is to be sent after opening a write or read/write stream,
    and before actual decoding starts. The parameter is used to select
    the stereo mix coefficients between the ISO/IEC and
    ARIB standards.

    Do not send this command during decoding; such a change might cause
    glitches in the stereo output.

    @msgpayload{asm_aac_stereo_mix_coeff_selection_param_t}
    @table{weak__asm__aac__stereo__mix__coeff__selection__param__t}
*/
#define ASM_PARAM_ID_AAC_STEREO_MIX_COEFF_SELECTION_FLAG           0x00010DD8

/** Use AAC stereo mix coefficients defined in ISO/IEC. */
#define ASM_AAC_STEREO_MIX_COEFF_ISO                                (0)

/** Use AAC stereo mix coefficients defined in ARIB. @newpage */
#define ASM_AAC_STEREO_MIX_COEFF_ARIB                               (1)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */

/* Structure for AAC decoder dual mono channel mapping. */
typedef struct asm_aac_stereo_mix_coeff_selection_param_t asm_aac_stereo_mix_coeff_selection_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_aac_stereo_mix_coeff_selection_param_t
@{ */
/* Payload of the ASM_PARAM_ID_AAC_STEREO_MIX_COEFF_SELECTION_FLAG parameter
    in the ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_aac_stereo_mix_coeff_selection_param_t
{
    uint32_t      aac_stereo_mix_coeff_flag;
    /**< Specifies which standard is used for AAC stereo mix.

         @values
         - #ASM_AAC_STEREO_MIX_COEFF_ISO (Default)
         - #ASM_AAC_STEREO_MIX_COEFF_ARIB @tablebulletend */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_aac_stereo_mix_coeff_selection_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AAC Decoder Dual Mono Channel Mapping parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to the AAC SBR signaling mechanism. The
    command can be sent any time after opening a write or read/write stream,
    and the changes take effect from the next decoded frame.

    @msgpayload{asm_aac_sbr_signalling_param_t}
    @table{weak__asm__aac__sbr__signalling__param__t}
*/
#define ASM_PARAM_ID_AAC_SBR_SIGNALLING                      0x00012F30

/** AAC extension audio object type is Low Complexity (LC). */
#define ASM_AAC_EXTENSION_AOT_LC                               2

/** AAC extension audio object type is SBR. */
#define ASM_AAC_EXTENSION_AOT_SBR                                5

/** AAC extension audio object type is PS. */
#define ASM_AAC_EXTENSION_AOT_PS                                 29

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */

/* Structure for AAC SBR signalling parameters. */
typedef struct asm_aac_sbr_signalling_param_t asm_aac_sbr_signalling_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_aac_sbr_signalling_param_t
@{ */
/* Payload of the ASM_PARAM_ID_AAC_SBR_SIGNALLING parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_aac_sbr_signalling_param_t
{
    uint32_t                  extension_aot;
    /**< Specifies the extension audio object type in a stream.

         @values
         - #ASM_AAC_EXTENSION_AOT_LC (Default)
         - #ASM_AAC_EXTENSION_AOT_SBR
         - #ASM_AAC_EXTENSION_AOT_PS

         If this value is set as ASM_AAC_EXTENSION_AOT_LC, all remaining fields
         are ignored; the decoder operates in implicit signaling mode. */

    uint32_t                  extension_sampling_rate;
    /**< Specifies the extension sampling rate.

         @values
         - Initialized to core sampling rate of decoder (Default)
         - All sampling rates applicable to the core AAC decoder
         @tablebulletend */

    uint32_t                  sbr_present;
    /**< Specifies whether to explicitly assume the presence or absence of the
         SBR payload in the stream.

         @values
         - 0 -- SBR payload is absent (Default)
         - 1 -- SBR payload is present @tablebulletend */

    uint32_t                  ps_present;
    /**< Specifies whether to explicitly assume the presence or absence of the
         PS payload in the stream.

         @values
         - 0 -- PS payload is absent (Default)
         - 1 -- PS payload is present @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_aac_dual_mono_mapping_param_t */
/** @endcond */

/** @ingroup asmstrm_resp_get_pp_topo_mod_list
    Returns a list of POPP/POPreP topology modules in response to an
    #ASM_STREAM_CMD_GET_PP_TOPO_MODULE_LIST command.
    
  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMDRSP_GET_PP_TOPO_MODULE_LIST
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @msgpayload{asm_stream_cmdrsp_get_pp_topo_module_list_t}
    @table{weak__asm__stream__cmdrsp__get__pp__topo__module__list__t}

  @return
    None.

  @dependencies
    This command must be applied to a valid stream.
*/
#define ASM_STREAM_CMDRSP_GET_PP_TOPO_MODULE_LIST                           0x00012F22

/* Payload for an ASM stream get pre/postprocessing parameters ACK event. */
typedef struct asm_stream_cmdrsp_get_pp_topo_module_list_t asm_stream_cmdrsp_get_pp_topo_module_list_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmdrsp_get_pp_topo_module_list_t
@{ */
/* Payload of the ASM_STREAM_CMDRSP_GET_PP_TOPO_MODULE_LIST message, which returns
    module ids in response to an ASM_STREAM_CMD_GET_PP_TOPO_MODULE_LIST command.
*/
struct asm_stream_cmdrsp_get_pp_topo_module_list_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q5,[Q5]} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmdrsp_get_pp_topo_module_list_t */


/** @ingroup asmstrm_resp_get_pp_params
    Returns parameter values in response to an #ASM_STREAM_CMD_SET_PP_PARAMS_V2
    command.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMDRSP_GET_PP_PARAMS_V2
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmdrsp_get_pp_params_v2_t}
    Immediately following this structure is the
    <b>Parameter data variable payload</b> (%asm_stream_param_data_v2_t).
    @tablens{weak__asm__stream__cmdrsp__get__pp__params__v2__t}

  @par Parameter data variable payload (asm_stream_param_data_v2_t)
    @tablens{weak__asm__stream__param__data__v2__t}

  @return
    None.

  @dependencies
    This command must be applied to a valid stream.
*/
#define ASM_STREAM_CMDRSP_GET_PP_PARAMS_V2                             0x00010DA4

/* Payload for an ASM stream get pre/postprocessing parameters ACK event. */
typedef struct asm_stream_cmdrsp_get_pp_params_v2_t asm_stream_cmdrsp_get_pp_params_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmdrsp_get_pp_params_v2_t
@{ */
/* Payload of the ASM_STREAM_CMDRSP_GET_PP_PARAMS_V2 message, which returns
    parameter values in response to an ASM_STREAM_CMD_GET_PP_PARAMS_V2 command.
*/
struct asm_stream_cmdrsp_get_pp_params_v2_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q5,[Q5]} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmdrsp_get_pp_params_v2_t */

/** @cond OEM_only */
/** @ingroup asmstrm_cmd_dtmf_ctl
    Starts or stops an ASM stream DTMF tone. This command is sent to the ASM
    when a DTMF tone is to be generated.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_DTMF_CTL
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_dtmf_ctl_t}
    @table{weak__asm__stream__cmd__dtmf__ctl__t}

  @detdesc
    The client populates the APR token field with a unique value for each
    DTMF APR payload. The aDSP returns that token in the
    #ASM_STREAM_EVENT_DTMF_TONE_ENDED event to the client. The client uses
    the returned token to look up which DTMF tone has just ended.
    @par
    After completion of DTMF tone generation, the aDSP sends the
    ASM_STREAM_EVENT_DTMF_TONE_ENDED to the client. This event is raised:
      - When a finite duration tone is completely played out
      - When an infinite duration tone is stopped
      - When a tone is pre-empted by a new tone while still playing
      - By the destination AFE port when the last sample has been rendered
        like the #ASM_DATA_EVENT_RENDERED_EOS event.
    @par
    @keep{6} If the client sends a new DTMF command before the previous tone
    is fully played out, the new tone will pre-empt the old tone and tone
    generation will continue with the new parameters specified in the payload.
    @par
    To stop the infinite tone, the client must send the
    #ASM_STREAM_CMD_DTMF_CTL with duration=0 in the payload. After
    receiving this command, the DTMF performs proper ramp down of the tone
    to avoid any pops.
    @par
    For finite tones, there is no need to send a stop command. The library
    stops the generation of samples after a finite duration is reached.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    This command must be applied to a valid stream.
*/
#define ASM_STREAM_CMD_DTMF_CTL                     0x00010D69

/* Payload for an ASM stream DTMF command. */
typedef struct asm_stream_cmd_dtmf_ctl_t asm_stream_cmd_dtmf_ctl_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_dtmf_ctl_t
@{ */
/* Payload of the ASM_STREAM_CMD_DTMF_CTL command, which starts/stops
    the DTMF tone.
*/
struct asm_stream_cmd_dtmf_ctl_t
{
    uint16_t                 tone_1;
    /**< Frequency of DTMF tone 1.

         @values 100 to 4000 Hz */

    uint16_t                  tone_2;
    /**< Frequency of DTMF tone 2.

         @values 100 to 4000 Hz */

    uint16_t                  gain;
    /**< DTMF linear gain in Q13 format. */

    int16_t                  duration;
    /**< Duration of the DTMF tone in milliseconds. Duration includes both
         ramp up and ramp down.

         @values
         - -1 -- Infinite tone
         - 0 -- Disable/stop infinite tone
         - >0 -- Finite duration @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_dtmf_ctl_t */
/** @endcond */

/* The following AC3 parameters make use of the generic
 *  structure asm_ac3_generic_param_t
 */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 Karaoke Mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter specifies the vocal channels for Karaoke mode, so it is
    relevant only for karaoke streams, and it applies only to the E-AC3
    decoder.

    The command can be sent any time after opening a write or
    read/write stream, and the change takes effect from the next decoded frame.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - #AC3_KARAOKE_MODE_NO_VOCAL
    - #AC3_KARAOKE_MODE_LEFT_VOCAL
    - #AC3_KARAOKE_MODE_RIGHT_VOCAL
    - #AC3_KARAOKE_MODE_BOTH_VOCAL (Default)
*/
#define ASM_PARAM_ID_AC3_KARAOKE_MODE                               0x00010D73

/** Enumeration for no vocal channels in a karaoke stream. */
#define AC3_KARAOKE_MODE_NO_VOCAL                                   (0)

/** Enumeration for only the left vocal channel in a karaoke stream. */
#define AC3_KARAOKE_MODE_LEFT_VOCAL                                 (1)

/** Enumeration for only the right vocal channel in a karaoke stream. */
#define AC3_KARAOKE_MODE_RIGHT_VOCAL                                (2)

/** Enumeration for both vocal channels in a karaoke stream. (Default) @newpage */
#define AC3_KARAOKE_MODE_BOTH_VOCAL                                 (3)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 DRC Mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to the E-AC3 decoder, and it specifies the
    compression that must be applied. The command can be sent any time after
    opening a write or read/write stream, and the change takes effect from the
    next decoded frame.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - #AC3_DRC_MODE_CUSTOM_ANALOG
    - #AC3_DRC_MODE_CUSTOM_DIGITAL
    - #AC3_DRC_MODE_LINE_OUT (Default)
    - #AC3_DRC_MODE_RF_REMOD
    - #AC3_DRC_PORTABLE_MODE_8
    - #AC3_DRC_PORTABLE_MODE_11
    - #AC3_DRC_PORTABLE_MODE_14
*/
#define ASM_PARAM_ID_AC3_DRC_MODE                                   0x00010D74

/** Enumeration for the Custom Analog mode. This custom mode is applied when
    DRC is to be scaled using the DRC Cut/Boost Scale factor.
*/
#define AC3_DRC_MODE_CUSTOM_ANALOG                                  (0)

/** Enumeration for the Custom Digital mode. This custom mode is applied when
    DRC is to be scaled using the DRC Cut/Boost Scale factor.
*/
#define AC3_DRC_MODE_CUSTOM_DIGITAL                                 (1)

/** Enumeration for the Line Out mode (light compression; default). This mode
    is used for most applications. It applies a normal compression factor
    (dynrng) present in the bitstream.
*/
#define AC3_DRC_MODE_LINE_OUT                                       (2)

/** Enumeration for the RF Remodulation mode. This mode is to be applied if the
    output is used to modulate an RF signal. It applies the heavy compression
    factor (compr) present in the bitstream.
*/
#define AC3_DRC_MODE_RF_REMOD                                       (3)

/** Enumeration for RF Remodulation mode 8, which is to be applied if 8 dB DRC
    suppression is required when modulating an RF signal. This mode applies
    the heavy compression factor (compr) present in the bitstream.
*/
#define AC3_DRC_PORTABLE_MODE_8                                     (4)

/** Enumeration for RF Remodulation mode 11, which is to be applied if 11 dB
    DRC suppression is required when modulating an RF signal. This mode applies
    the heavy compression factor (compr) present in the bitstream.
*/
#define AC3_DRC_PORTABLE_MODE_11                                    (5)

/** Enumeration for RF Remodulation mode 14, which is to be applied if 14 dB
    DRC suppression is required when modulating an RF signal. This mode applies
    the heavy compression factor (compr) present in the bitstream. @newpage
*/
#define AC3_DRC_PORTABLE_MODE_14                                    (6)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 Dual Mono Mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter specifies how the dual mono channels are to be played out.
    It is relevant only for dual mono streams, and it applies only to the E-AC3
    decoder.
    
    The command can be sent any time after opening a write or
    read/write stream, and the change takes effect from the next decoded frame.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - #AC3_DUAL_MONO_MODE_STEREO (Default)
    - #AC3_DUAL_MONO_MODE_LEFT_MONO
    - #AC3_DUAL_MONO_MODE_RIGHT_MONO
    - #AC3_DUAL_MONO_MODE_MIXED_MONO
*/
#define ASM_PARAM_ID_AC3_DUAL_MONO_MODE                             0x00010D75

/** Enumeration for playing dual mono in Stereo mode. (Default) */
#define AC3_DUAL_MONO_MODE_STEREO                                   (0)

/** Enumeration for playing left mono. */
#define AC3_DUAL_MONO_MODE_LEFT_MONO                                (1)

/** Enumeration for playing right mono. */
#define AC3_DUAL_MONO_MODE_RIGHT_MONO                               (2)

/** Enumeration for mixing and playing both dual mono channels. @newpage */
#define AC3_DUAL_MONO_MODE_MIXED_MONO                               (3)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 Stereo Downmix Mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter specifies the type of stereo downmix to be used. This is
    applicable when downmixing to two channels, and it applies only to the
    E-AC3 decoder. The command can be sent any time after opening a write or
    read/write stream, and the change takes effect from the next decoded frame.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - #AC3_STEREO_DOWNMIX_MODE_AUTO_DETECT (Default).
    - #AC3_STEREO_DOWNMIX_MODE_LT_RT -- LT/RT downmix preserves the
      surround information. It is useful if the downmixed audio is played
      out using a Pro-Logic decoder.
    - #AC3_STEREO_DOWNMIX_MODE_LO_RO -- LO/RO is useful if the stereo
      stream is further downmixed to mono.
*/
#define ASM_PARAM_ID_AC3_STEREO_DOWNMIX_MODE                        0x00010D76

/** Enumeration for using the Downmix mode indicated in the bitstream.
    (Default)
*/
#define AC3_STEREO_DOWNMIX_MODE_AUTO_DETECT                         (0)

/** Enumeration for Surround Compatible mode. This mode preserves the surround
    information. It is useful if the downmixed audio is played out using a
    Pro-Logic decoder.
*/
#define AC3_STEREO_DOWNMIX_MODE_LT_RT                               (1)

/** Enumeration for Mono Compatible mode. This mode is useful if the output is
    to be further downmixed to mono. @newpage
*/
#define AC3_STEREO_DOWNMIX_MODE_LO_RO                               (2)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 PCM Scale Factor parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter is a gain setting for the output audio, and it
    applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a gain value (0 to 1) in Q31 format applied to all samples
    in the stream. For the payload format, see asm_ac3_generic_param_t.
    @par
    @values 0 to 100 (Default is 100)
*/
#define ASM_PARAM_ID_AC3_PCM_SCALEFACTOR                            0x00010D78

/** ID of the AC3 DRC Boost Scale Factor parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter is used to scale the DRC boost parameter, which is useful
    in controlling the extent to which DRC is applied.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a gain value (0 to 1) in Q31 format applied to the DRC
    boost scale factor. By setting this to 1, full DRC is applied.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values 0 to 100 (Default is 100)
*/
#define ASM_PARAM_ID_AC3_DRC_BOOST_SCALEFACTOR                      0x00010D79

/** ID of the AC3 DRC Cut Scale Factor parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter is used to scale the DRC cut parameter, which is useful
    in controlling the extent to which DRC is applied.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a gain value (0 to 1) in Q31 format applied to the DRC cut
    scale factor. By setting this to 1, full DRC is applied.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values 0 to 100 (Default is 100) @newpage
*/
#define ASM_PARAM_ID_AC3_DRC_CUT_SCALEFACTOR                        0x00010D7A

/** ID of the AC3 Channel Configuration parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    The client is responsible for setting the appropriate channel
    configuration, depending on the device settings of write streams or the
    required output format of read/write streams.
    Channel configuration decides the type of downmixing that is to be applied
    by the decoder to get the output channels.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values See Sections @xref{hdr:AC3ChannelEnumFirst} through
            @xref{hdr:AC3ChannelEnumLast}
*/
#define ASM_PARAM_ID_AC3_CHANNEL_CONFIG                                0x00010DE0

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/* Enumeration for a AC3 channel configuration Notation
AC3_CHANNEL_CONFIG_<number of front channels>_<number of surround_channels>_<number of extension channels if they exist>_<channel list>
*/
/** @xreflabel{hdr:AC3ChannelEnumFirst}
    Configuration for Raw mode (no downmixing). Play out all channels in the
    bitstream as is without any downmixing.
*/
#define AC3_CHANNEL_CONFIG_RAW                                      (-1)

/** Reserved configuration. */
#define AC3_CHANNEL_CONFIG_RSVD                                     (0)

/** Configuration for one channel (mono).
    - Speaker front center
*/
#define AC3_CHANNEL_CONFIG_1_0_C                                    (1)

/** Configuration for two channels (stereo, default).
    - Speaker front left
    - Speaker front right
*/
#define AC3_CHANNEL_CONFIG_2_0_L_R                                  (2)

/** Configuration for three channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - No surround
    - No extension
*/
#define AC3_CHANNEL_CONFIG_3_0_L_C_R                                (3)

/** Configuration for three channels.
    - Speaker front left
    - Speaker front right
    - Surround mono
    - No extension
*/
#define AC3_CHANNEL_CONFIG_2_1_L_R_l                                (4)

/** Configuration for four channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround mono
    - No extension
*/
#define AC3_CHANNEL_CONFIG_3_1_L_C_R_l                              (5)

/** Configuration for four channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - No extension
*/
#define AC3_CHANNEL_CONFIG_2_2_L_R_l_r                              (6)

/** Configuration for five channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - No extension @newpage
*/
#define AC3_CHANNEL_CONFIG_3_2_L_C_R_l_r                            (7)

/** Configuration for four channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - No surround
    - Extension center vertical height
*/
#define AC3_CHANNEL_CONFIG_3_0_1_L_C_R_Cvh                          (8)

/** Configuration for five channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - Extension top surround
*/
#define AC3_CHANNEL_CONFIG_2_2_1_L_R_l_r_Ts                         (9)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension top surround
*/
#define AC3_CHANNEL_CONFIG_3_2_1_L_C_R_l_r_Ts                       (10)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension center vertical height @newpage
*/
#define AC3_CHANNEL_CONFIG_3_2_1_L_C_R_l_r_Cvh                      (11)

/** Configuration for five channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - No surround
    - Extension left center
    - Extension right center
*/
#define AC3_CHANNEL_CONFIG_3_0_2_L_C_R_Lc_Rc                        (12)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left wide
    - Extension right wide
*/
#define AC3_CHANNEL_CONFIG_2_2_2_L_R_l_r_Lw_Rw                      (13)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left vertical height
    - Extension right vertical height @newpage
*/
#define AC3_CHANNEL_CONFIG_2_2_2_L_R_l_r_Lvh_Rvh                    (14)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left surround direct
    - Extension right surround direct
*/
#define AC3_CHANNEL_CONFIG_2_2_2_L_R_l_r_Lsd_Rsd                    (15)

/** Configuration for six channels.
    - Speaker front left
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left rear surround
    - Extension right rear surround
*/
#define AC3_CHANNEL_CONFIG_2_2_2_L_R_l_r_Lrs_Rrs                    (16)

/** Configuration for seven channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left center
    - Extension right center @newpage
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Lc_Rc                    (17)

/** Configuration for seven channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left wide
    - Extension right wide
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Lw_Rw                    (18)

/** Configuration for seven channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left vertical height
    - Extension right vertical height
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Lvh_Rvh                  (19)

/** Configuration for seven channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left surround direct
    - Extension right surround direct @newpage
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Lsd_Rsd                  (20)

/** Configuration for seven channels. (Default)
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension left rear surround
    - Extension right rear surround
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Lrs_Rrs                  (21)

/** @xreflabel{hdr:AC3ChannelEnumLast}
    Configuration for seven channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Surround left
    - Surround right
    - Extension top surround
    - Extension center vertical height @newpage
*/
#define AC3_CHANNEL_CONFIG_3_2_2_L_C_R_l_r_Ts_Cvh                   (22)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 Low Frequency Effects (LFE) mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    The client is responsible for setting this parameter, depending on the
    device settings of write streams or the required output format of
    read/write streams.

    @msgpayload
    Specifies the number of LFE channels in the output.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - #AC3_LFE_MODE_NONE
    - #AC3_LFE_MODE_1_LFE (Default)
    - #AC3_LFE_MODE_2_LFE @if ISV_only @tablebulletend @endif
  @if OEM_only
    @par
    @note1hang DDP streams can contain up to two LFE channels.
  @endif
*/
#define ASM_PARAM_ID_AC3_LFE_MODE                                    0x00010DE1

/** Enumeration for no LFE in the output. */
#define AC3_LFE_MODE_NONE                                           (0)

/** Enumeration for one LFE channel in the output. (Default) */
#define AC3_LFE_MODE_1_LFE                                          (1)

/** Enumeration for two LFE channels in the output.

    @note1hang Dolby Digital Plus streams can contain up to two LFE
               channels. @newpage
*/
#define AC3_LFE_MODE_2_LFE                                          (2)

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the AC3 Number of Output Channels parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    The client is responsible for setting the appropriate number of output
    channels, depending on the device settings of write streams or the required
    output format of read/write streams.
    - If more channels are specified here than those specified in the channel
      configuration, the additional channels will contain zero samples.
    - If fewer channels are specified, only the initial channels up to the
      number specified will be present in the output buffer. There will not be
      any additional downmixing.

    @msgpayload
    Specifies the number of channels in the output buffer of the decoder.
    The client must set the number of channels to be equal to the number
    of channels in the channel configuration (#ASM_PARAM_ID_AC3_CHANNEL_CONFIG).
    @par
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values 1 to 8 (Default = 8)
*/
#define ASM_PARAM_ID_AC3_NUM_OUTPUT_CHANNELS                        0x00010DE2

/** ID of the AC3 Error Conceal parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    When enabled and if an error occurs, this parameter fills output PCM
    buffers with data repeated from the last block that decoded without error
    until the specified count (#ASM_PARAM_ID_AC3_ERROR_MAX_RPTS) is reached.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value that is applied to the Error Conceal parameter.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Disable error concealment
    - 1 -- Enable error concealment (Default) @newpage
*/
#define ASM_PARAM_ID_AC3_ERROR_CONCEAL                              0x00010DE3

/** ID of the AC3 Error Maximum Repeats parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    If an error occurs, this parameter is used to specify the maximum number
    of consecutive block repeats that are allowed before the output channels
    are automatically muted.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value (in Q31 format) that is applied to the Error Max repeat
    parameter.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Enable mute
    - -1 -- Block repeats continuously for an indefinite period of time
    (Default)
*/
#define ASM_PARAM_ID_AC3_ERROR_MAX_RPTS                             0x00010DE4

/** ID of the AC3 Converter Error Conceal parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    When enabled and if an error occurs, this parameter fills output PCM
    buffers with data repeated from the last block that converted without
    error until the specified count (#ASM_PARAM_ID_AC3_ERROR_MAX_RPTS) is
    reached.

    This parameter applies only to the E-AC3 converter. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value that is applied to the Converter Error Conceal parameter.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Disable converter error concealment
    - 1 -- Enable converter error concealment (Default) @newpage
*/
#define ASM_PARAM_ID_AC3_CNV_ERROR_CONCEAL                          0x00010DE5

/** ID of the AC3 Substream Select parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter selects the type of substream that specifies the
    associated program for decoding.  A substream is a subcomponent of the
    overall bitstream, specific to E-AC3, which can be either dependent or
    independent as specified by the associated semantics.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value that is applied to the Substream Select parameter.
    Setting this to 1, 2, or 3 enables the type substream select.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 1    -- SUBSTREAMID_1
    - 2 -- SUBSTREAMID_2
    - 3 -- SUBSTREAMID_3
*/
#define ASM_PARAM_ID_AC3_SUBSTREAM_SELECT                           0x00010DE6

/** ID of the AC3 Modified Discrete Cosine Transform (MDCT) Band Limiting
    parameter in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    MDCT is the commonly used filter bank in audio coding, used to limit the.
    bandwidth.
    This parameter is used to enable or disable Band Limiting mode.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value that is applied to the MDCT band limiting factor.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Disable band limiting (Default)
    - 1    -- Enable band limiting @newpage
*/
#define ASM_PARAM_ID_AC3_MDCT_BANDLIMITING_MODE                     0x00010DE7

/** ID of the AC3 DRC Suppression mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies whether to suppress DRC.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    Specifies a value that is applied to the DRC Suppression mode.
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Do not suppress DRC (Default)
    - 1 -- Suppress DRC
*/
#define ASM_PARAM_ID_AC3_DRC_SUPPRESSION_MODE                       0x00010DE8

/** ID of the AC3 External Boost parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter specifies the external boost value and supports only a
    GetParam functionality.

    This parameter applies only to the E-AC3 decoder. The command can be sent
    any time after opening a write or read/write stream, and the change takes
    effect from the next decoded frame.

    @msgpayload
    The parameter is an unsigned 32-bit integer and returns the external boost
    value. For the payload format, see asm_ac3_generic_param_t. @newpage
*/
#define ASM_PARAM_ID_AC3_EXT_BOOST                                  0x00010DEA

/** ID of the AC3 Audio Coding Mode Changes parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter is an unsigned 32-bit integer. It provides the state for
    E-AC3 decoder conformance testing, and it applies only to the E-AC3
    decoder. The command can be sent any time after opening a write or
    read/write stream, and the change takes effect from the next decoded frame.

    @msgpayload
    For the payload format, see asm_ac3_generic_param_t.
    @par
    @values
    - 0 -- Enable conformance
    - 1 -- Disable conformance (Default)
*/
#define ASM_PARAM_ID_AC3_ACMOD_CHANGES_STATE                       0x00010DF5

/* Structure for AC3 Generic Parameter. */
typedef struct asm_ac3_generic_param_t asm_ac3_generic_param_t;

#include "adsp_begin_pack.h"

/** Payload of the generic AC3 parameters in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_ac3_generic_param_t
{
    uint32_t                  generic_parameter;
    /**< @if OEM_only
         Generic parameter field used by the following AC3 parameter IDs:

         - #ASM_PARAM_ID_AC3_KARAOKE_MODE
         - #ASM_PARAM_ID_AC3_CHANNEL_CONFIG
         - #ASM_PARAM_ID_AC3_LFE_MODE
         - #ASM_PARAM_ID_AC3_DRC_MODE
         - #ASM_PARAM_ID_AC3_DUAL_MONO_MODE
         - #ASM_PARAM_ID_AC3_STEREO_DOWNMIX_MODE
         - #ASM_PARAM_ID_AC3_PCM_SCALEFACTOR
         - #ASM_PARAM_ID_AC3_DRC_BOOST_SCALEFACTOR
         - #ASM_PARAM_ID_AC3_DRC_CUT_SCALEFACTOR
         - #ASM_PARAM_ID_AC3_NUM_OUTPUT_CHANNELS
         - #ASM_PARAM_ID_AC3_ERROR_CONCEAL
         - #ASM_PARAM_ID_AC3_ERROR_MAX_RPTS
         - #ASM_PARAM_ID_AC3_CNV_ERROR_CONCEAL
         - #ASM_PARAM_ID_AC3_SUBSTREAM_SELECT
         - #ASM_PARAM_ID_AC3_MDCT_BANDLIMITING_MODE
         - #ASM_PARAM_ID_AC3_DRC_SUPPRESSION_MODE
         - #ASM_PARAM_ID_AC3_EXT_BOOST @tablebulletend
     @endif
     @if ISV_only
         Generic parameter field.
     @endif */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/* The following HEAAC parameters make use of the generic
 *  structure asm_heaac_generic_param_t
 */
/** ID of the Dolby Pulse High Efficiency AAC (HEAAC) Number of Output Channels
    parameter in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter applies only to #ASM_MEDIA_FMT_AAC_V2 and
    #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding. The command is to be sent
    after opening a write or read/write stream and before actual decoding
    starts.

    @msgpayload
    Specifies the number of output channels decoded.
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - 0 -- Native (Default)
    - 1 -- Mono
    - 2 -- Stereo
    - 6 -- 5.1 channels
*/
#define ASM_PARAM_ID_HEAAC_NUM_OUTPUT_CHANNELS                    0x00012F20

/** ID of the Dolby Pulse HEAAC Error Conceal parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies whether to enable error concealment.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    Do not send this command during decoding; such a change might introduce a
    blank frame in the middle of playback.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - 0 -- Disable concealment (Default)
    - 1 -- Enable concealment
*/
#define ASM_PARAM_ID_HEAAC_ERROR_CONCEAL                        0x00012F19

/** ID of the Dolby Pulse HEAAC 2-to-1 Resampling parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies whether to enable 2-to-1 resampling.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    Do not send this command during decoding; such a change might introduce
    discontinuities in the middle of playback.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - 0 -- Disable 2-to-1 resampling (Default)
    - 1 -- Enable 2-to-1 resampling
*/
#define ASM_PARAM_ID_HEAAC_2TO1_RESAMPLING                        0x00012F1A

/** ID of the Dolby Pulse HEAAC (10D86:ASM_MEDIA_FMT_DOLBY_AAC) Replay Gain
    parameter in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies whether the Replay Gain value is applied.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    Do not send this command during decoding; such a change might introduce
    discontinuities in the output.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - Range from -72 to 55 (-18.0dB to 13.75dB in steps of 0.25dB)
    - Default value -- 0
*/
#define ASM_PARAM_ID_HEAAC_REPLAY_GAIN                            0x00012F1B

/** ID of the Dolby Pulse HEAAC default Program Reference Level (PRL)
    parameter in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies the Default PRL value to be applied.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    Do not send this command during decoding; such a change might introduce
    discontinuities in the middle of playback.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - Range of 0 to 127 (0dB to -31.75dB in steps of 0.25dB)
    - Default value -- 124 @newpage
*/
#define ASM_PARAM_ID_HEAAC_DEFAULT_PRL                            0x00012F1C

/** ID of the Dolby Pulse HEAAC DRC Type and Mode parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter specifies whether Dynamic Range Control and Leveling is
    enabled and how it is configured.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    The lower 16 bits indicate the DRC mode and the higher 16 bits indicate
    the DRC type.

    @msgpayload
    Specifies a value that is applied to the DRC type and mode.
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values{for Type}
    - 0 -- None
    - 1 -- MPEG-DRC
    - 2 -- DVB-compression
    - 3 -- Prefer DRC
    - 4 -- Prefer compression
    - 5 -- Portable mode

    @values{for Mode} Application of DRC/compression and consideration of PRL
    on the PCM output of the decoder.
    - 0 -- None
    - 1 -- DRC/compression
    - 2 -- PRL
    - 3 -- DRC/compression and PRL

    @values{for Default}
    - 0 -- Type
    - 2 -- Default mode @newpage
*/
#define ASM_PARAM_ID_HEAAC_DRC_TYPE_MODE                        0x00012F1D

/** ID of the Dolby Pulse HEAAC External Boost parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This postprocessing parameter specifies whether to apply external boost
    on the decoded PCM samples.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - 0 -- Do not apply (Default)
    - 1 -- Apply external boost
*/
#define ASM_PARAM_ID_HEAAC_EXT_BOOST                            0x00012F1E

/** ID of the Dolby Pulse HEAAC External Metadata parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This is a post-processing parameter specifies whether or not to apply
    the external metadata on the decoded PCM samples.

    This parameter applies only to #ASM_MEDIA_FMT_DOLBY_AAC bitstream decoding.
    The command is to be sent after opening a write or read/write stream and
    before actual decoding starts.

    @msgpayload
    For the payload format, see asm_heaac_generic_param_t.
    @par
    @values
    - 0 -- Do not apply (Default)
    - 1 -- Apply external metadata
*/
#define ASM_PARAM_ID_HEAAC_EXT_METADATA                            0x00012F1F

/* Structure for HEAAC Generic Parameter. */
typedef struct asm_heaac_generic_param_t asm_heaac_generic_param_t;

#include "adsp_begin_pack.h"

/** Payload of the generic HEAAC parameters in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_heaac_generic_param_t
{
    uint32_t                  generic_parameter;
    /**< Generic parameter field used by the following HEAAC parameter IDs:
         - #ASM_PARAM_ID_HEAAC_NUM_OUTPUT_CHANNELS
         - #ASM_PARAM_ID_HEAAC_ERROR_CONCEAL
         - #ASM_PARAM_ID_HEAAC_2TO1_RESAMPLING
         - #ASM_PARAM_ID_HEAAC_REPLAY_GAIN
         - #ASM_PARAM_ID_HEAAC_DEFAULT_PRL
         - #ASM_PARAM_ID_HEAAC_DRC_TYPE_MODE
         - #ASM_PARAM_ID_HEAAC_EXT_BOOST
         - #ASM_PARAM_ID_HEAAC_EXT_METADATA @tablebulletend @newpagetable */
}
#include "adsp_end_pack.h"
;

/** Enumeration for Raw mode (no downmixing), which specifies that all
    channels in the bitstream are to be played out as is without any
    downmixing. (Default)
*/
#define WMAPRO_CHANNEL_MASK_RAW                                      (-1)

/** Enumeration for setting the channel mask to 0. The 7.1 mode (Home
    Theater) is assigned.
*/
#define WMAPRO_CHANNEL_MASK_ZERO                                     0x0000

/** Speaker layout mask for one channel (Home Theater, mono).
    - Speaker front center
*/
#define WMAPRO_CHANNEL_MASK_1_C                                      0x0004

/** Speaker layout mask for two channels (Home Theater, stereo).
    - Speaker front left
    - Speaker front right
*/
#define WMAPRO_CHANNEL_MASK_2_L_R                                    0x0003

/** Speaker layout mask for three channels (Home Theater).
    - Speaker front left
    - Speaker front center
    - Speaker front right
*/
#define WMAPRO_CHANNEL_MASK_3_L_C_R                                  0x0007

/** Speaker layout mask for two channels (stereo).
    - Speaker back left
    - Speaker back right
*/
#define WMAPRO_CHANNEL_MASK_2_Bl_Br                                  0x0030

/** Speaker layout mask for four channels.
    - Speaker front left
    - Speaker front right
    - Speaker back left
    - Speaker back right
*/
#define WMAPRO_CHANNEL_MASK_4_L_R_Bl_Br                              0x0033

/** Speaker layout mask for four channels (Home Theater).
    - Speaker front left
    - Speaker front right
    - Speaker front center
    - Speaker back center
*/
#define WMAPRO_CHANNEL_MASK_4_L_R_C_Bc_HT                            0x0107

/** Speaker layout mask for five channels.
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
*/
#define WMAPRO_CHANNEL_MASK_5_L_C_R_Bl_Br                            0x0037

/** Speaker layout mask for five channels (5 mode, Home Theater).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
*/
#define WMAPRO_CHANNEL_MASK_5_L_C_R_Sl_Sr_HT                         0x0607

/** Speaker layout mask for six channels (5.1 mode).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
    - Speaker low frequency
*/
#define WMAPRO_CHANNEL_MASK_5DOT1_L_C_R_Bl_Br_SLF                    0x003F

/** Speaker layout mask for six channels (5.1 mode, Home Theater).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
    - Speaker low frequency
*/
#define WMAPRO_CHANNEL_MASK_5DOT1_L_C_R_Sl_Sr_SLF_HT                 0x060F

/** Speaker layout mask for six channels (5.1 mode, no LFE).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
    - Speaker back center
*/
#define WMAPRO_CHANNEL_MASK_5DOT1_L_C_R_Bl_Br_Bc                     0x0137

/** Speaker layout mask for six channels (5.1 mode, Home Theater, no LFE).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
    - Speaker back center
*/
#define WMAPRO_CHANNEL_MASK_5DOT1_L_C_R_Sl_Sr_Bc_HT                  0x0707

/** Speaker layout mask for seven channels (6.1 mode).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
    - Speaker back center
    - Speaker low frequency
*/
#define WMAPRO_CHANNEL_MASK_6DOT1_L_C_R_Bl_Br_Bc_SLF                 0x013F

/** Speaker layout mask for seven channels (6.1 mode, Home Theater).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
    - Speaker back center
    - Speaker low frequency @newpage
*/
#define WMAPRO_CHANNEL_MASK_6DOT1_L_C_R_Sl_Sr_Bc_SLF_HT              0x070F

/** Speaker layout mask for seven channels (6.1 mode, no LFE).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
    - Speaker front left of center
    - Speaker front right of center
*/
#define WMAPRO_CHANNEL_MASK_6DOT1_L_C_R_Bl_Br_SFLOC_SFROC            0x00F7

/** Speaker layout mask for seven channels (6.1 mode, Home Theater, no LFE).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
    - Speaker front left of center
    - Speaker front right of center
*/
#define WMAPRO_CHANNEL_MASK_6DOT1_L_C_R_Sl_Sr_SFLOC_SFROC_HT         0x0637

/** Speaker layout mask for eight channels (7.1 mode).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker back left
    - Speaker back right
    - Speaker low frequency
    - Speaker front left of center
    - Speaker front right of center @newpage
*/
#define WMAPRO_CHANNEL_MASK_7DOT1_L_C_R_Bl_Br_SLF_SFLOC_SFROC        0x00FF

/** Speaker layout mask for eight channels (7.1 mode, Home Theater).
    - Speaker front left
    - Speaker front center
    - Speaker front right
    - Speaker side left
    - Speaker side right
    - Speaker low frequency
    - Speaker front left of center
    - Speaker front right of center
*/
#define WMAPRO_CHANNEL_MASK_7DOT1_L_C_R_Sl_Sr_SLF_SFLOC_SFROC_HT     0x063F

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** Parameter ID for decoder output channel mapping in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    The client can use this command to match the channel mapping at the output
    of the decoder to the channel mapping supported by the rendering device.
    If the same stream is to be routed to multiple rendering devices with
    different supported speaker positions, the client can use this command to
    specify a channel mapping that is a union of the speaker positions
    supported by each of the devices.

    @keep{6} This command is optional. If this command is absent, the decoder
    performs a conversion from its internal channel representation, which might
    be codec specific, to the standard channel representation by preserving as
    many channels as possible.

    In non-tunneled mode playback mode, the client can retain the decoder
    output channel mapping. In this case, the number of channels must be set
    to zero. This option is not valid for tunneled mode.

    This command can be issued multiple times with the last command taking
    precedence.

    @msgpayload{asm_dec_out_chan_map_param_t}
    @table{weak__asm__dec__out__chan__map__param__t}
*/
#define ASM_PARAM_ID_DEC_OUTPUT_CHAN_MAP                   0x00010D82

/** Maximum number of decoder output channels. */
#define MAX_CHAN_MAP_CHANNELS                               16

/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */

/* Structure for decoder output channel mapping. */
typedef struct asm_dec_out_chan_map_param_t asm_dec_out_chan_map_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_dec_out_chan_map_param_t
@{ */
/* Payload of the ASM_PARAM_ID_DEC_OUTPUT_CHAN_MAP parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_dec_out_chan_map_param_t
{
    uint32_t                 num_channels;
    /**< Number of decoder output channels.

         @values 0 to #MAX_CHAN_MAP_CHANNELS

         A value of 0 indicates native channel mapping, which is valid only
         for NT mode. This means the output of the decoder is to be
         preserved as is. */

    uint8_t                  channel_mapping[MAX_CHAN_MAP_CHANNELS];
    /**< Channel array of size num_channels.

         Channel[i] mapping describes channel i inside the decoder output
         buffer. Valid channel mapping values are to be present at the
         beginning of the array.

         @values See Section @xref{dox:PcmChannelDefs} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_dec_out_chan_map_param_t */

/** @addtogroup asmstrm_cmd_open_write_compr
@{ */
/** Opens a playback channel to route compressed audio streams to an external
    receiver after applying the necssary packetization as specified by
    IEC 61937 and IEC 60958 standards.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_WRITE_COMPRESSED
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_write_compressed_t}
    @table{weak__asm__stream__cmd__open__write__compressed__t} @vertspace{-15}

  @keep{4} @detdesc
    For this command, only one stream per session is allowed. Otherwise, an
    error is returned. The client can perform the packetization itself or
    have the aDSP perform packetization.
    @par
    If IEC 61937 packetization is performed by the client, this operation mode
    is called Pass-through mode. The media format block must be
    communicated, if applicable, to the aDSP through the
    #ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2 command before sending the actual data.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client.

  @dependencies
    None.
*/
#define ASM_STREAM_CMD_OPEN_WRITE_COMPRESSED                       0x00010D84

/** Bitmask for the IEC 61937 enable flag. */
#define ASM_BIT_MASK_IEC_61937_STREAM_FLAG                         (0x00000001UL)

/** Shift value for the IEC 61937 enable flag. */
#define ASM_SHIFT_IEC_61937_STREAM_FLAG                             0

/** Bitmask for the IEC 60958 enable flag. */
#define ASM_BIT_MASK_IEC_60958_STREAM_FLAG                          (0x00000002UL)

/** Shift value for the IEC 60958 enable flag. */
#define ASM_SHIFT_IEC_60958_STREAM_FLAG                              1

/** @} */ /* end_addtogroup asmstrm_cmd_open_write_compr */

/* Payload format for open write compressed comand */
typedef struct asm_stream_cmd_open_write_compressed_t asm_stream_cmd_open_write_compressed_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_write_compressed_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_WRITE_COMPRESSED comand,
    which opens a stream for a given session ID and stream ID to be
    rendered in the compressed format.
*/
struct asm_stream_cmd_open_write_compressed_t
{
    uint32_t                    flags;
    /**< Mode flags that configure the stream for a specific format.

         @note1hang Currently, IEC 60958 packetized input streams are not
                    supported.

         @values{for bit 0} (IEC 61937 compatibility)
         - 0 -- Stream is not in IEC 61937 format
         - 1 -- Stream is in IEC 61937 format
         - To set this bit, use #ASM_BIT_MASK_IEC_61937_STREAM_FLAG and
           #ASM_SHIFT_IEC_61937_STREAM_FLAG

         @values{for bit 1} (IEC 60958 compatibility)
         - 0 -- Stream is not in IEC 60958 format
         - 1 -- Stream is in IEC 60958 format
         - To set this bit, use #ASM_BIT_MASK_IEC_60958_STREAM_FLAG and
           #ASM_SHIFT_IEC_60958_STREAM_FLAG

       @if OEMonly
         @values{for bits 6 to 3} (Decoder-Converter compatibility)
         - 0x0 -- Default mode
         - 0x1 -- DDP-to-DD Decoder-Converter mode
         - 0x2-0xF -- Reserved for future use
         - To set this bit, use #ASM_BIT_MASK_DECODER_CONVERTER_FLAG and
           #ASM_SHIFT_DECODER_CONVERTER_FLAG
         - Currently supported value: #ASM_DDP_DD_CONVERTER_MODE
       @endif

         Bit 2 is left, to be consistent with other stream commands.

         Bit 2 and all other bits are reserved; clients must set them to zero.

         For the same stream: bit 0 cannot be set to 0, and bit 1 cannot be set
         to 1. A compressed stream cannot have IEC 60958 packetization applied
         without IEC 61937 packetization. */

    uint32_t                    fmt_id;
    /**< Specifies the media type of the HDMI stream to be opened.

         @note1hang This field must be set to a valid media type even if
                    IEC 61937 packetization is not performed by the aDSP.

       @if OEM_only
         For the formats indicated by *, only IEC 61937 Pass-through mode is
         currently supported.

         @values
         - #ASM_MEDIA_FMT_AC3
         - #ASM_MEDIA_FMT_EAC3
         - #ASM_MEDIA_FMT_DTS
         - #ASM_MEDIA_FMT_ATRAC *
         - #ASM_MEDIA_FMT_MAT *
         - #ASM_MEDIA_FMT_AAC_V2 *
         - #ASM_MEDIA_FMT_MP3 *
         - #ASM_MEDIA_FMT_WMA_V10PRO_V2 * @tablebulletend
       @endif */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_write_compressed_t */


/** @ingroup asmstrm_cmd_open_read_compr
    Opens a stream to receive compressed audio content from an external
    receiver after removing the IEC&nbsp;61937 and IEC&nbsp;60958
    packetization.

    Only one stream per session is allowed for this command. Otherwise, an
    error is returned.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_READ_COMPRESSED
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_read_compressed_t}
    @table{weak__asm__stream__cmd__open__read__compressed__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client.

  @dependencies
    None.
*/
#define ASM_STREAM_CMD_OPEN_READ_COMPRESSED                        0x00010D95

/* Payload format for open read compressed comand */
typedef struct asm_stream_cmd_open_read_compressed_t asm_stream_cmd_open_read_compressed_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_read_compressed_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_READ_COMPRESSED comand, which opens
    a stream for a given session ID and stream ID to be received from an
    external source.
*/
struct asm_stream_cmd_open_read_compressed_t
{
     uint32_t                    mode_flags;
     /**< Indicates whether metadata per encoded frame is to be provided.

          @values{for bit 4}
          - 0 -- Return data buffer contains all encoded frames only; it does
            not contain frame metadata
          - 1 -- Return data buffer contains an array of metadata and encoded
            frames
          - To set the shift value for this bit, use
            #ASM_BIT_MASK_META_INFO_FLAG to set the bitmask and
            #ASM_SHIFT_META_INFO_FLAG

          All other bits are reserved; clients must set them to zero. */

    uint32_t                    frames_per_buf;
    /**< Indicates the number of frames that must be returned per read buffer.

         @values > 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_read_compressed_t */


/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the DTS mix LFE Channel to Front Channels parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    If enabled, this parameter mixes the LFE channel to the front while
    downmixing (if necessary).

    @msgpayload
    For the payload format, see asm_dts_generic_param_t.
    @par
    @values
    - 0 -- Disable (Default)
    - 1 -- Enable
*/
#define ASM_PARAM_ID_DTS_MIX_LFE_TO_FRONT                          0x00010DB6

/** ID of the DTS Enable Parse REV2AUX parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This flag enables parsing of the REV2AUX chunk in the bitstream. This chunk
    contains the broadcast metadata.

    @msgpayload
    For the payload format, see asm_dts_generic_param_t.
    @par
    @values
    - 0 -- Disable (Default)
    - 1 -- Enable
*/
#define ASM_PARAM_ID_DTS_ENABLE_PARSE_REV2AUX                         0x00010DB9

/* Structure for DTS Generic Parameter. */
typedef struct asm_dts_generic_param_t asm_dts_generic_param_t;

#include "adsp_begin_pack.h"

/** Payload of the DTS parameters in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM
    command.
*/
struct asm_dts_generic_param_t
{
    int32_t                  generic_parameter;
    /**< Generic parameter used by the following DTS parameter IDs:
         - #ASM_PARAM_ID_DTS_MIX_LFE_TO_FRONT
         - #ASM_PARAM_ID_DTS_ENABLE_PARSE_REV2AUX @tablebulletend */
}
#include "adsp_end_pack.h"
;

/** ID of the DTS LBR Mix LFE Channel to Front Channels parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    If enabled, this parameter mixes the LFE channel to the front while
    downmixing (if necessary).

    @msgpayload
    For the payload format, see asm_dts_lbr_generic_param_t.
    @par
    @values
    - 0 -- Disable (Default)
    - 1 -- Enable @newpage
*/
#define ASM_PARAM_ID_DTS_LBR_MIX_LFE_TO_FRONT                          0x00010DBC

/** ID of the DTS LBR Enable Parse REV2AUX parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This flag enables parsing of the REV2AUX chunk in the bitstream. This chunk
    contains the broadcast metadata.

    @msgpayload
    For the payload format, see asm_dts_generic_param_t.
    @par
    @values
    - 0 -- Disable (Default)
    - 1 -- Enable
*/
#define ASM_PARAM_ID_DTS_LBR_ENABLE_PARSE_REV2AUX                    0x00010DBD

/* Structure for DTS LBR Generic Parameter. */
typedef struct asm_dts_lbr_generic_param_t asm_dts_lbr_generic_param_t;

#include "adsp_begin_pack.h"

/** Payload of the DTS LBR parameters in the #ASM_STREAM_CMD_SET_ENCDEC_PARAM
    command.
*/
struct asm_dts_lbr_generic_param_t
{
    int32_t                  generic_parameter;
    /**< Generic parameter used by the following DTS LBR parameter IDs:
         - #ASM_PARAM_ID_DTS_LBR_MIX_LFE_TO_FRONT
         - #ASM_PARAM_ID_DTS_LBR_ENABLE_PARSE_REV2AUX @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @addtogroup asmstrm_cmd_open_pull_write
@{ */
/** Creates an audio stream for PCM playback in Pull mode.

    Pull mode differs from regular playback (#ASM_STREAM_CMD_OPEN_WRITE_V2
    and #ASM_STREAM_CMD_OPEN_WRITE_V3) in that no data commands are supported
    in Pull mode. The aDSP continuously reads data from a shared circular
    buffer, assuming the client writes data on time.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_pull_mode_write_t}
    @table{weak__asm__stream__cmd__open__pull__mode__write__t}
    This structure is followed by:
     - %asm_pull_mode_write_position_buffer_t
     - %asm_multi_channel_pcm_fmt_blk_v3_t (if dec_fmt_id is
       #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3)
     - %avs_shared_map_region_payload_t (repeated shared_pos_buf_num_regions
       times -- typically 1)
     - %avs_shared_map_region_payload_t (repeated shared_circ_buf_num_regions
       times)
     - %asm_pull_mode_watermark_level_t (repeated num_water_mark_levels times)
     @newpage

  @par Pull mode write position (asm_pull_mode_write_position_buffer_t
    @table{weak__asm__pull__mode__write__position__buffer__t}

  @par Multichannel PCM (asm_multi_channel_pcm_fmt_blk_v3_t)
    If dec_fmt_id is #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3, the size of this
    region is defined by the media format structure.
    @tablens{weak__asm__multi__channel__pcm__fmt__blk__v3__t}

  @par Memory mapped regions (avs_shared_map_region_payload_t)
    Repeated shared_pos_buf_num_regions times and shared_circ_buf_num_regions
    times.
    @tablens{weak__avs__shared__map__region__payload__t}

  @par Watermark levels (asm_pull_mode_watermark_level_t)
    If num_watermark_levels > 0:
    @tablens{weak__asm__pull__mode__watermark__level__t}

  @detdesc
    When creating a stream, the client must specify the group and stream IDs.
    The current release supports up to 15 groups, and each
    group can have up to #ASM_MAX_STREAMS_PER_SESSION streams.
    @par
    The #ASM_CMD_SHARED_MEM_MAP_REGIONS command assumes that memory is cached.
    This ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE command contains memory mapping
    information because in some cases the memory must be uncached:
     - The position buffer must always be uncached.
     - On the playback path, the circular buffer can be cached in the aDSP
       because the aDSP only reads.
    @par
    Therefore, the position buffer and the circular buffer must be from
    different regions. The mapped memory is unmapped automatically by the aDSP
    during stream close.
    @par
    This command contains media format information (PCM media format ID and the
    media format block) because data path commands are absent.
    Only PCM formats are supported.
    @par
    The shared position buffer is read-only for the clients.
    @par
    Gapless playback is not supported.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client.

  @dependencies
    None.
*/
#define ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE                          0x00010DD9

/** Bitmask for the stream_perf_mode subfield. */
#define ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_PULL_MODE_WRITE            (0xE0000000UL)

/** Bit shift for the stream_perf_mode subfield. */
#define ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_PULL_MODE_WRITE                29

/** @} */ /* end_addtogroup asmstrm_cmd_open_pull_write */

/* position buffer for pull mode write */
typedef struct asm_pull_mode_write_position_buffer_t asm_pull_mode_write_position_buffer_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_pull_mode_write_position_buffer_t
@{ */
/* Position buffer for Pull mode writes in ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE.
*/
struct asm_pull_mode_write_position_buffer_t
{
   volatile uint32_t frame_counter;
   /**< Counter used to handle interprocessor synchronization issues associated
        with reading read_index, wall_clock_us_lsw, and wall_clock_us_msw.
        These are invalid when frame_counter = 0.

        @values @ge 0

        Read the frame_counter value both before and after reading these values
        to make sure the aDSP did not update them while the client was reading
        them. */

   volatile uint32_t read_index;
   /**< Index in bytes from where the aDSP is reading.

        @values 0 to the circular buffer size minus 1 */

   volatile uint32_t wall_clock_us_lsw;
   /**< Lower 32 bits of the 64-bit wall clock time in microseconds when the
        read_index was updated.

        @values @ge 0 */

   volatile uint32_t wall_clock_us_msw;
   /**< Upper 32 bits of the 64-bit wall clock time in microseconds when the
        read_index was updated.

        @values @ge 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_pull_mode_write_position_buffer_t */

typedef struct asm_pull_mode_watermark_level_t asm_pull_mode_watermark_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_pull_mode_watermark_level_t
@{ */
/* Payload of the watermark level structure in
    ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE.
*/
struct asm_pull_mode_watermark_level_t
{
   uint32_t watermark_level_bytes;
   /**< Watermark level in bytes. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_pull_mode_watermark_level_t */

/* Payload format for a stream open write command. */
typedef struct asm_stream_cmd_open_pull_mode_write_t asm_stream_cmd_open_pull_mode_write_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_pull_mode_write_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_PULL_MODE_WRITE command, which opens a
    write stream for a given session ID and stream ID in Pull mode. The
    dst_port field in the APR packet contains both the session ID and the
    stream ID.
    The structure of the payload consists of the following:
     -asm_stream_cmd_open_pull_mode_write_t
     - asm_multi_channel_pcm_fmt_blk_v3_t (if dec_fmt_id is
       ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3)
     - avs_shared_map_region_payload_t (repeated shared_pos_buf_num_regions
       times -- usually 1)
     - avs_shared_map_region_payload_t (repeated shared_circ_buf_num_regions
       times)
     - asm_pull_mode_watermark_level_t (repeated num_water_mark_levels times)
*/
struct asm_stream_cmd_open_pull_mode_write_t
{
    uint32_t                    mode_flags;
    /**< Specifies the performance mode in which this stream must be opened.

         @values{for bits 31 to 29} (stream_perf_mode subfield)
         - #ASM_LEGACY_STREAM_SESSION -- This mode is not supported.
         - #ASM_LOW_LATENCY_STREAM_SESSION -- Opens a playback session by using
           shortened buffers in low latency POPP.
           - Recommendation: Do not enable high latency algorithms; they might
             negate the benefits of opening a low latency stream, and they
             might also suffer quality degradation from unexpected jitter.
           - The aDSP data path output latency contributed from the stream side
             can vary from 1 to 3 ms. In a steady state playback, this latency
             is measured as the average sample time difference between the
             sample that is currently being read from shared memory and the
             sample that is currently rendered to the DMA.

         @contcell
         - #ASM_ULTRA_LOW_LATENCY_STREAM_SESSION -- Opens a ULL playback
           session by using shortened buffers in the decoder. There is no
           POPP processing in the ULL stream session.
           - Recommendation: Send the content whose bits per sample and number
             of channels match with the device to avoid processing in the aDSP.
           - Only PCM, 16-bit/24-bit, mono/stereo data at non-fractional
             sampling rates are supported.
           - The ULL stream sessions consist of output buffers
             with a duration of 1 ms. The stream session contributes 0 ms to
             the aDSP data path output latency. 
         - To configure this subfield, use
           #ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_PULL_MODE_WRITE and
           #ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_PULL_MODE_WRITE.

         All other bits are reserved; clients must set them to zero. */

    uint16_t                    sink_endpoint_type;
    /**< Type of sink endpoint.

         @values
         - 0 -- Device matrix (gateway to the hardware ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */

    uint16_t                    topo_bits_per_sample;
     /**< Number of bits per sample processed by ASM modules. This is different
          from input sample bits per sample.

          @values 16, 24 */

    uint32_t                    postproc_topo_id;
    /**< Specifies the topology (order of processing) of postprocessing
         algorithms. <i>None</i> means no postprocessing.

         @values
         - #ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT
       @if OEM_only
         - #ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL
       @endif
         - #ASM_STREAM_POSTPROC_TOPO_ID_NONE (open to other topology IDs)

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                    dec_fmt_id;
    /**< Configuration ID of the decoder media format.

         @values #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3 */

    uint32_t                   shared_pos_buf_phy_addr_lsw;
    /**< Lower 32 bits of the physical address of the shared position buffer. */

    uint32_t                   shared_pos_buf_phy_addr_msw;
    /**< Upper 32 bits of the physical address of the shared position buffer.

         The 64-bit buffer formed by shared_pos_buf_phy_addr_lsw and
         shared_pos_buf_phy_addr_msw must have enough memory allocated for
         asm_pull_mode_write_position_buffer_t. */

    uint16_t                   shared_pos_buf_mem_pool_id;
    /**< Type of memory on which this memory region is mapped for the shared
         position buffer.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         This ID implicitly defines the characteristics of the memory.
         Characteristics include alignment type, permissions, etc.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, byte addressable, and
         4 KB aligned. */

    uint16_t                    shared_pos_buf_num_regions;
    /**< Number of regions to map for the shared position buffer.

         @values > 0 */

    uint32_t                    shared_pos_buf_property_flag;
    /**< Configures one common property for all regions in the payload for the
         shared position buffer. No two regions can have different properties
         for the shared position buffer.

         @values 0x00000000 to 0x00000001

         Bit 0 is the IsVirtual flag that indicates physical or virtual
         mapping:
           - 0 -- The shared memory address provided in
                  avs_shared_map_regions_payload is a physical address. The
                  shared memory must be mapped (a hardware TLB entry), and a
                  software entry must be added for internal bookkeeping.
           - 1 -- The shared memory address provided in the map
                  payload[usRegions] is a virtual address. The shared memory
                  must not be mapped (because the hardware TLB entry is already
                  available), but a software entry must be added for internal
                  bookkeeping. \n
                  This is useful if two services within the aDSP are
                  communicating via the APR. They can directly communicate via
                  the virtual address instead of the physical address. The
                  virtual regions must be contiguous.

         Bits 31 to 1 are reserved and must be set to zero. */

    uint32_t                   shared_circ_buf_start_phy_addr_lsw;
    /**< Lower 32 bits of the 64-bit physical address of the shared circular
         buffer. */

    uint32_t                   shared_circ_buf_start_phy_addr_msw;
    /**< Upper 32 bits of the 64-bit physical address of the shared circular
         buffer. */

    uint32_t                   shared_circ_buf_size;
    /**< Number of valid bytes available in the shared circular buffer.

         @values > 0

         The value must be an integral multiple of the number of
         (sample word size * number of channels). */

    uint16_t                   shared_circ_buf_mem_pool_id;
    /**< Type of memory on which this memory region is mapped for the shared
         circular buffer.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         The memory ID implicitly defines the characteristics of the memory.
         Characteristics can include alignment type, permissions, etc.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, byte addressable, and
         4 KB aligned. */

    uint16_t                  shared_circ_buf_num_regions;
    /**< Number of regions to map for the shared circular buffer.

         @values > 0 */

    uint32_t                  shared_circ_buf_property_flag;
    /**< Configures one common property for all regions in the payload for the
         shared circular buffer. No two regions can have different properties
         for the shared circular buffer.

         @values 0x00000000 to 0x00000001

         Bit 0 is the IsVirtual flag that indicates physical or virtual
         mapping:
           - 0 -- The shared memory address provided in
                  shared memory map regions payload is a physical address. The
                  shared memory must be mapped (a hardware TLB entry), and a
                  software entry must be added for internal bookkeeping.
           - 1 -- The shared memory address provided in the map
                  payload[usRegions] is a virtual address. The shared memory
                  must not be mapped (because the hardware TLB entry is already
                  available), but a software entry must be added for internal
                  bookkeeping. \n
                  This is useful if two services within the aDSP are
                  communicating via the APR. They can directly communicate via
                  the virtual address instead of the physical address. The
                  virtual regions must be contiguous.

         Bits 31 to 1 are reserved and must be set to zero. */

    uint32_t                 num_watermark_levels;
    /**< Number of watermark-level structures of type
         asm_pull_mode_watermark_level_t following this structure.

         @values @ge 0

         If set to zero, no watermark levels are specified, and hence no
         watermark events are supported. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_pull_mode_write_t */


/** @addtogroup asmstrm_cmd_open_push_read
@{ */
/** Creates an audio stream for recording in Push mode. There is one
    preprocessing chain and one encoder.

    The Push mode differs from regular record (#ASM_STREAM_CMD_OPEN_READ_V2
    and #ASM_STREAM_CMD_OPEN_READ_V2) in that no data commands are supported
    in Push mode. The aDSP continuously writes data to a shared circular
    buffer, assuming the client reads data on time.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_CMD_OPEN_READ_PUSH_MODE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_stream_cmd_open_push_mode_read_t}
    @table{weak__asm__stream__cmd__open__push__mode__read__t}
    This structure is followed by:
     - %asm_push_mode_read_position_buffer_t
     - %asm_multi_channel_pcm_enc_cfg_v3_t (if enc_cfg_id is
       #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3)
     - %avs_shared_map_region_payload_t (repeated shared_pos_buf_num_regions
       times -- typically 1)
     - %avs_shared_map_region_payload_t (repeated shared_circ_buf_num_regions
       times)
     - %asm_push_mode_watermark_level_t (repeated num_watermark_levels times)
     @newpage

  @par Push mode read position (asm_push_mode_read_position_buffer_t)
    @table{weak__asm__push__mode__read__position__buffer__t}

  @par Multichannel PCM (asm_multi_channel_pcm_enc_cfg_v3_t)
    If enc_cfg_id is #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3.
    The size of this regions is defined by the media format structure.
    @tablens{weak__asm__multi__channel__pcm__enc__cfg__v3__t}

  @par Memory mapped regions (avs_shared_map_region_payload_t)
    Repeated shared_pos_buf_num_regions times and shared_circ_buf_num_regions
    times.
    @tablens{weak__avs__shared__map__region__payload__t}
    @newpage

  @par Watermark levels (asm_push_mode_watermark_level_t)
    If num_watermark_levels is > 0 (in asm_stream_cmd_open_push_mode_read_t):
    @tablens{weak__asm__push__mode__watermark__level__t}

  @detdesc
    This command creates a new record stream in Push mode. It specifies the
    media format of the encoding to be performed by the aDSP. The encoder
    configuration block must be communicated in this command because data
    commands indicating sample rate and channel mapping changes are absent.
    Further, Native mode is not supported (sample rate and number of 
    channels cannot be zero).
    @par
    Encoder configuration information is present in this command because data
    path commands indicating an SR_CM event are absent.
    @par
    Memory mapping information is present in this command because in some
    cases this memory must be uncached:
      - The position buffer must always be uncached.
      - On the record path, the circular buffer cannot be cached in the aDSP
        because the aDSP writes in bytes and the byte length cannot match the
        aDSP cache line.
    @par
    @keep{3} Therefore, the position buffer and the circular buffer must be
    from different regions. The mapped memory is unmapped automatically by the
    aDSP during stream close.
    @par
    This command contains media format information (PCM media format ID and the
    media format block) because data path commands are absent.
    Only PCM formats are supported.
    @par
    @note1hang Sending #ASM_STREAM_CMD_SET_ENCDEC_PARAM commands for
               changing the encoder configuration is not allowed.\n
               The #ASM_STREAM_CMD_FLUSH_READBUFS command is not supported.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as an input.

  @dependencies
    None.
*/
#define ASM_STREAM_CMD_OPEN_PUSH_MODE_READ                                    0x00010DDA

/** Bitmask for the stream_perf_mode subfield. */
#define ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_PUSH_MODE_READ            (0xE0000000UL)

/** Bit shift for the stream_perf_mode subfield. */
#define ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_PUSH_MODE_READ                     29

/** @} */ /* end_addtogroup asmstrm_cmd_open_push_read */

/* position buffer for push mode read */
typedef struct asm_push_mode_read_position_buffer_t asm_push_mode_read_position_buffer_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_push_mode_read_position_buffer_t
@{ */
/* Position buffer for Push mode reads in ASM_STREAM_CMD_OPEN_READ_PUSH_MODE.
*/
struct asm_push_mode_read_position_buffer_t
{
   volatile uint32_t frame_counter;
   /**< Counter used to handle interprocessor synchronization issues associated
        with reading write_index, wall_clock_us_lsw, and wall_clock_us_msw.
        These are invalid when frame_counter = 0.

        @values @ge 0

        Read the frame_counter value both before and after reading these values
        to make sure the aDSP did not update them while the client was reading
        them. */

   volatile uint32_t write_index;
   /**< Index in bytes to where the aDSP is writing.

        @values 0 to the circular buffer size minus 1 */

   volatile uint32_t wall_clock_us_lsw;
   /**< Lower 32 bits of the 64-bit wall clock time in microseconds when the
        read_index was updated.

        @values @ge 0 */

   volatile uint32_t wall_clock_us_msw;
   /**< Upper 32 bits of the 64-bit wall clock time in microseconds when the
        read_index was updated.

        @values @ge 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_push_mode_read_position_buffer_t */

typedef struct asm_push_mode_watermark_level_t asm_push_mode_watermark_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_push_mode_watermark_level_t
@{ */
/* used by ASM_STREAM_CMD_OPEN_READ_PUSH_MODE */
struct asm_push_mode_watermark_level_t
{
   uint32_t watermark_level_bytes;
   /**< Watermark level in bytes. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_push_mode_watermark_level_t */

/* Payload format for a stream open push mode read command. */
typedef struct asm_stream_cmd_open_push_mode_read_t asm_stream_cmd_open_push_mode_read_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_stream_cmd_open_push_mode_read_t
@{ */
/* Payload of the ASM_STREAM_CMD_OPEN_PUSH_MODE_READ command, which opens a
    read stream for a given session ID and stream ID. The APR packet contains
    both the session ID and the stream ID.
    The structure of the payload consists of the following:
     -asm_stream_cmd_open_push_mode_read_t
     - asm_multi_channel_pcm_enc_cfg_v3_t (if enc_cfg_id is
       ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3)
     - avs_shared_map_region_payload_t (repeated shared_pos_buf_num_regions
       times -- usually 1)
     - avs_shared_map_region_payload_t (repeated shared_circ_buf_num_regions
       times)
     -asm_push_mode_watermark_level_t (repeated num_watermark_levels times)
*/
struct asm_stream_cmd_open_push_mode_read_t
{
    uint32_t                    mode_flags;
    /**< Specifies whether the session is low latency.

         @values{for bits 31 to 29} (stream_perf_mode subfield)}
         - #ASM_LEGACY_STREAM_SESSION -- Currently not supported.
         - #ASM_LOW_LATENCY_STREAM_SESSION -- Opens a record session using
           shortened buffers in low latency POPreP.
           - Recommendation: Do not enable high latency algorithms; they might
             negate the benefits of opening a low latency stream, and they
             might also suffer quality degradation from unexpected jitter.
           - The aDSP data path output latency contributed from the stream side
             can vary from 1 to 2 ms. In steady state recording, this latency
             is measured as the average sample time difference between the
             sample that is currently being read from the DMA and the sample
             that is currently written to shared memory.
         - To configure this subfield, use
           #ASM_BIT_MASK_STREAM_PERF_MODE_FLAG_IN_OPEN_PUSH_MODE_READ and
           #ASM_SHIFT_STREAM_PERF_MODE_FLAG_IN_OPEN_PUSH_MODE_READ.

         All other bits are reserved; clients must set them to zero. */

    uint16_t                    src_endpoint_type;
    /**< Device matrix endpoint providing the input samples.

         @values
         - 0 -- Device matrix (gateway from the tunneled Tx ports)
         - All other values are reserved

         Clients must set this field to zero. Otherwise, an error is returned. */


    uint16_t                    topo_bits_per_sample;
     /**< Number of bits per sample processed by the ASM modules.
          Note that this is different from output sample bits per sample.

          @values 16, 24 */

    uint32_t                    preproc_topo_id;
    /**< Specifies the topology (order of processing) of preprocessing
         algorithms. <i>None</i> means no preprocessing.

         @values
         - #ASM_STREAM_PREPROC_TOPO_ID_DEFAULT
         - #ASM_STREAM_PREPROC_TOPO_ID_NONE

         This field can also be enabled through SetParams flags.

         Topologies can be added through #ASM_CMD_ADD_TOPOLOGIES. */

    uint32_t                     enc_cfg_id;
    /**< Media configuration ID for the encoded output.
         Native mode is not supported.

         @values #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V3*/

    uint32_t                   shared_pos_buf_phy_addr_lsw;
    /**< Lower 32 bits of the physical address of the shared position buffer. */

    uint32_t                   shared_pos_buf_phy_addr_msw;
    /**< Upper 32 bits of the physical address of the shared position buffer.
         Enough memory must be allocated for
         #asm_push_mode_read_position_buffer_t. */

    uint16_t                  shared_pos_buf_mem_pool_id;
    /**< Type of memory on which this memory region is mapped for the shared
         position buffer.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         The memory ID implicitly defines the characteristics of the memory.
         Characteristics can include alignment type, permissions, etc.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, byte addressable, and
         4 KB aligned. */

    uint16_t                  shared_pos_buf_num_regions;
    /**< Number of regions to map for the shared position buffer.

         @values Any value greater than zero */

    uint32_t                  shared_pos_buf_property_flag;
    /**< Configures one common property for all regions in the payload. No
         two regions can have different properties for the shared position
         buffer.

         @values 0x00000000 to 0x00000001

         Bit 0 is the IsVirtual flag that indicates physical or virtual
         mapping:
           - 0 -- The shared memory address provided in
                  shared memory map regions payload is a physical address. The
                  shared memory must be mapped (a hardware TLB entry), and a
                  software entry must be added for internal bookkeeping.
           - 1 -- The shared memory address provided in the map
                  payload[usRegions] is a virtual address. The shared memory
                  must not be mapped (because the hardware TLB entry is already
                  available), but a software entry must be added for internal
                  bookkeeping. \n
                  This is useful if two services within the aDSP are
                  communicating via the APR. They can directly communicate via
                  the virtual address instead of the physical address. The
                  virtual regions must be contiguous.

         Bits 31 to 1 are reserved and must be set to zero. */

    uint32_t                   shared_circ_buf_start_phy_addr_lsw;
    /**< Lower 32 bits of the 64-bit physical address of the shared circular
         buffer. */

    uint32_t                   shared_circ_buf_start_phy_addr_msw;
    /**< Upper 32 bits of the 64-bit physical address of the shared circular
         buffer. */

    uint32_t                   shared_circ_buf_size;
    /**< Number of valid bytes available in the shared circular buffer.

         @values > 0

         The value must be an integral multiple of the number of
         (sample word size * number of channels). */

    uint16_t                   shared_circ_buf_mem_pool_id;
    /**< Type of memory on which this memory region is mapped for the shared
         circular buffer.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         The memory ID implicitly defines the characteristics of the memory.
         Characteristics can include alignment type, permissions, etc.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, byte addressable, and
         4 KB aligned. */

    uint16_t                  shared_circ_buf_num_regions;
    /**< Number of regions to map for the shared circular buffer.

         @values > 0 */

    uint32_t                  shared_circ_buf_property_flag;
    /**< Configures one common property for all regions in the payload. No
         two regions can have different properties for the shared circular
         buffer.

         @values 0x00000000 to 0x00000001

         Bit 0 is the IsVirtual flag that indicates physical or virtual
         mapping:
           - 0 -- The shared memory address provided in
                  shared memory map regions payload is a physical address. The
                  shared memory must be mapped (a hardware TLB entry), and a
                  software entry must be added for internal bookkeeping.
           - 1 -- The shared memory address provided in the map
                  payload[usRegions] is a virtual address. The shared memory
                  must not be mapped (because the hardware TLB entry is already
                  available), but a software entry must be added for internal
                  bookkeeping. \n
                  This is useful if two services within the aDSP are
                  communicating via the APR. They can directly communicate via
                  the virtual address instead of the physical address. The
                  virtual regions must be contiguous.

         Bits 31 to 1 are reserved and must be set to zero. */

    uint32_t                 num_watermark_levels;
    /**< Number of watermark-level structures of type
         %asm_push_mode_watermark_level_t following this structure.

         @values @ge 0

         If set to zero, no watermark levels are specified, and hence no
         watermark events are supported. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_stream_cmd_open_read_v3_t */


/** @cond OEM_only */
/** @addtogroup asmstrm_cmd_set_encdec_params
@{ */
/** ID of the Data Rate/Bit Rate parameter for the DDP encoder in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    Each acmod has its own data rate. It signals the configuration of main
    audio channels to the decoder.

    @msgpayload
    For the payload format, see asm_ddp_enc_cfg_t.
    @par
    @values
    - For 1/0 acmod -- 192 data rate (Default)
    - For 2/0 acmod -- 192, 256 (Default) data rates
    - For 3/2 acmod -- 384 (Default), 448, 640 data rates
*/
#define ASM_PARAM_ID_DDP_ENC_DATA_RATE    0x00010DF0

/** ID of the DDP LFE Channel Enable parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
    This parameter is available only when the 3/2 Audio Coding mode is selected
    (acmod = 7).

    @msgpayload
    For the payload format, see asm_ddp_enc_cfg_t.
    @par
    @values
    - 0 -- Disable
    - 1 -- Enable
*/
#define ASM_PARAM_ID_DDP_ENC_LFE          0x00010DF1

/** ID of the 90-degree Phase Shift Filter parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter conditions the signals that include surround channels.
    It is available only when the 3/2 Audio Coding mode is selected
    (acmod = 7). In this case, the filter default is ON.

    @msgpayload
    For the payload format, see asm_ddp_enc_cfg_t.
    @par
    @values
    - 1 -- ON
    - 2 -- OFF
*/
#define ASM_PARAM_ID_DDP_ENC_PH90_FILT    0x00010DF2

/** ID of the Global DRC Profile parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    To compress the dynamic range of a program, a DDP decoder can use
    DRC to reduce (cut) the level of the loudest sounds and increase (boost)
    the level of quiet sounds.

    @msgpayload
    For the payload format, see asm_ddp_enc_cfg_t.
    @par
    @values
    - 1 -- Film Standard (Default)
    - 3 -- Music Standard @newpage
*/
#define ASM_PARAM_ID_DDP_ENC_GBL_DRC_PROF 0x00010DF3

/** ID of the Dialogue Normalization (DialNorm) parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter represents a known DialNorm reference level (in dBFS) that
    is embedded in the bitstream as DialNorm metadata to ensure that the
    decoded audio can be played.

    Attenuation = 31 + (DialNorm value)

    Examples:
    - If the DialNorm value is -31, attenuation is zero.
    - If the DialNorm value is -27, encoded PCM is 4 db attenuated compared to
      the original PCM (input).

    @msgpayload
    For the payload format, see asm_ddp_enc_cfg_t.
    @par
    @values -1 to -31 (Default setting is -31)
*/
#define ASM_PARAM_ID_DDP_ENC_DIAL_NORM    0x00010DF4

/* Structure for DDP encoder Generic Parameter. */
typedef struct asm_ddpencoder_generic_param_t asm_ddpencoder_generic_param_t;

#include "adsp_begin_pack.h"

/** Payload of the generic DDP encoder parameters in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_ddpencoder_generic_param_t
{
    uint32_t                  param_val;
    /**< Generic parameter used by the following DDP encoder parameter IDs:
         - #ASM_PARAM_ID_DDP_ENC_DATA_RATE
         - #ASM_PARAM_ID_DDP_ENC_LFE
         - #ASM_PARAM_ID_DDP_ENC_PH90_FILT
         - #ASM_PARAM_ID_DDP_ENC_GBL_DRC_PROF
         - #ASM_PARAM_ID_DDP_ENC_DIAL_NORM @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_addtogroup asmstrm_cmd_set_encdec_params */
/** @endcond */

/** @ingroup asmstrm_cmd_set_encdec_params
    ID of the Register Decoder Error Event parameter in the
    #ASM_STREAM_CMD_SET_ENCDEC_PARAM command.

    This parameter registers or deregisters how many consecutive decoder errors
    occur before an event is raised. The HLOS is notified that either a serious
    decoding error has occurred or that the decoder format is wrong.

    @msgpayload(asm_dec_err_param_t)
    @table{weak__asm__dec__err__param__t} @newpage
*/
#define ASM_PARAM_ID_REG_DEC_ERR_EVENT                                0x00010DF6

/* Structure for an AAC SBR PS processing flag. */
typedef struct asm_dec_err_param_t asm_dec_err_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_dec_err_param_t
@{ */
/* Payload of the ASM_PARAM_ID_REG_DEC_ERR_EVENT parameter in the
    ASM_STREAM_CMD_SET_ENCDEC_PARAM command.
*/
struct asm_dec_err_param_t
{
    uint16_t                 n_dec_err_threshold;
    /**< Specifies how many consecutive decoder errors occur before an event
         is raised.

         @values
         - 0 -- Deregister event raising
         - > 0 @tablebulletend */

    uint16_t                 timeout_ms;
    /**< Specifies how many milliseconds occur before an event is raised
         on consecutive decoder errors before the n_dec_err_threshold is met.

         @values
         - 0 -- No timeout; always wait until the threshold is reached
         - All positive values @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_dec_err_param_t */


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_ASM_STREAM_COMMANDS_H_ */
