/*========================================================================*/
/**
@file adsp_asm_data_commands.h

This file contains ASM data commands and events structures definitions.
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

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_asm_data_commands.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                    Doxygen comments/markup for 2.6.
09/06/13   sw      (Tech Pubs) Merged Doxygen comments/markup from 2.0.
08/06/12   sw      (Tech Pubs) Edited comments; updated Doxygen markup to
                   Rev D.2 templates; updated legal statements for QTI.
05/30/11   sw/leo  (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
10/12/10   leo     (Tech Pubs) Edited/added Doxygen comments and markup.
04/15/10   rkc      Created file.
========================================================================== */

#ifndef _ADSP_ASM_DATA_COMMANDS_H_
#define _ADSP_ASM_DATA_COMMANDS_H_

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/** @addtogroup asmdata_cmd_write_data
@{ */
/** Delivers a data buffer to the ASM.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_WRITE_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_write_v2_t}
    @table{weak__asm__data__cmd__write__v2__t}

  @keep{8} @detdesc
    If the client wants the aDSP to use valid timestamps in this command and
    the data being sent through this command is in RAW format, the last data
    byte must constitute an end of frame. The end-of-frame flag (bit&nbsp;4
    of the flags field) must be set to 1. Otherwise, the aDSP will not
    be able to handle the timestamps correctly, which might result in gaps
    during audio playback.
    @par
    When the buffer delivers uncompressed PCM data (i.e.,
    #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2 format), the buffer must contain the
    same number of PCM samples for all channels. If not, the aDSP discards the
    buffer and generates an #ASM_DATA_EVENT_WRITE_DONE_V2 event with the
    ADSP_EBADPARAM error code. (For more details on the error code, refer to
    @xhyperref{Q5,[Q5]}.)

  @return
    #ASM_DATA_EVENT_WRITE_DONE_V2 is raised when the buffer is fully consumed.

  @dependencies
    The session/stream must be a valid and opened write or read/write 
    session/stream.
*/
/* Q5 = Hex MM: AV Core Service API Interface Spec for 2.6 (80-NF770-4) */
#define ASM_DATA_CMD_WRITE_V2                                          0x00010DAB

/* Payload for an ASM Data Write command. */
typedef struct asm_data_cmd_write_v2_t asm_data_cmd_write_v2_t;

/** Definition of a timestamp valid flag bitmask. */
#define ASM_BIT_MASK_TIMESTAMP_VALID_FLAG                           (0x80000000UL)

/** Definition of a timestamp valid flag shift value. */
#define ASM_SHIFT_TIMESTAMP_VALID_FLAG                               31

/** Definition of the last buffer flag bitmask. The last buffer flag is part
    of the flags word in the ASM_DATA_CMD_WRITE_V2 command.
*/
#define ASM_BIT_MASK_LAST_BUFFER_FLAG                               (0x40000000UL)

/** Definition of the last buffer flag shift value. The last buffer flag is
    part of the flags word in the ASM_DATA_CMD_WRITE_V2 command.
*/
#define ASM_SHIFT_LAST_BUFFER_FLAG                                   30

/** Definition of the shift value for the timestamp continue flag.
    The timestamp continue flag is part of the flags field in the
    asm_data_cmd_write_v2_t structure.
*/
#define ASM_BIT_MASK_TS_CONTINUE_FLAG                               (0x20000000UL)

/** Definition of the shift value for the timestamp continue flag.
    The timestamp continue flag is part of the flags field in the
    asm_data_cmd_write_v2_t structure.
*/
#define ASM_SHIFT_TS_CONTINUE_FLAG                                   29

/** Definition of an End of Frame (EOF) flag bitmask. */
#define ASM_BIT_MASK_EOF_FLAG                                       (0x00000010UL)

/** Definition of an EOF flag shift value. */
#define ASM_SHIFT_EOF_FLAG                                           4

/** @} */ /* end_addtogroup asmdata_cmd_write_data */

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_write_v2_t
@{ */
/* Payload of the ASM_DATA_CMD_WRITE_V2 command, which delivers a data
    buffer to the ASM for decoding.
*/
struct asm_data_cmd_write_v2_t
{
    uint32_t                  buf_addr_lsw;
    /**< Lower 32 bits of the address of the buffer containing the data to be
         decoded. */

    uint32_t                  buf_addr_msw;
    /**< Upper 32 bits of the address of the buffer containing the data to be
         decoded.

         Each frame's buffer address must be a valid, mapped, physical address
         that has been mapped via #ASM_CMD_SHARED_MEM_MAP_REGIONS.
         The 64-bit number formed by buf_addr_lsw and buf_addr_msw must be
         aligned to a 32-byte boundary.

         @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw field
         must be set to zero.

         @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
         buf_addr_msw field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buf_size;
    /**< Number of valid bytes available in the buffer for decoding. The
         first byte starts at the buffer address.

         @values > 0

         For PCM data, the buf_size must be a multiple of 
         (number of channels * bytes per sample). Bytes per sample is 2 for
         16-bit data and 4 for 24-bit data.

         If the buffer size is greater than or equal to 32 KB, DM-lite
         (Data Mover) can be used for the transfer. This is useful for Low
         Power Audio (LPA). */

    uint32_t                  seq_id;
    /**< Optional buffer sequence ID. */

    uint32_t                  timestamp_lsw;
    /**< Lower 32 bits of the 64-bit session time in microseconds of the
         first buffer sample. */

    uint32_t                  timestamp_msw;
    /**< Upper 32 bits of the 64-bit session time in microseconds of the
         first buffer sample. */

    uint32_t                  flags;
    /**< Bitfield of flags.

         @values{for bit 31}
         - 1 -- Valid timestamp
         - 0 -- Invalid timestamp
         - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_VALID_FLAG and
           #ASM_SHIFT_TIMESTAMP_VALID_FLAG

         @values{for bit 30}
         - 1 -- Last buffer
         - 0 -- Not the last buffer
         - To set this bit, use #ASM_BIT_MASK_LAST_BUFFER_FLAG and
           #ASM_SHIFT_LAST_BUFFER_FLAG

         @values{for bit 29}
         - 1 -- Continue the timestamp from the previous buffer
         - 0 -- Timestamp of the current buffer is not related to the timestamp
                of the previous buffer
         - To set this bit, use #ASM_BIT_MASK_TS_CONTINUE_FLAG and
           #ASM_SHIFT_TS_CONTINUE_FLAG
  
         @values{for bit 4 (end-of-frame flag)}
         - 1 -- End of the frame
         - 0 -- Not the end of frame, or this information is not known
         - To set this bit, use #ASM_BIT_MASK_EOF_FLAG as the bitmask and
           #ASM_SHIFT_EOF_FLAG

         All other bits are reserved; clients must set them to zero.

         @tblsubhd{If bit 31=0 and bit 29=1}
         The timestamp of the first sample in this buffer continues from the
         timestamp of the last sample in the previous buffer. If there is no
         previous buffer (i.e., this is the first buffer sent after opening
         the stream or after a flush operation), or if the previous buffer
         does not have a valid timestamp, the samples in the current buffer
         also do not have a valid timestamp. They are played out as soon as
         possible.

         @tblsubhd{If bit 31=0 and bit 29=0}
         No timestamp is associated with the first sample in this buffer. The
         samples are played out as soon as possible.

         @tblsubhd{If bit 31=1 and bit 29 is ignored}
         The timestamp specified in this payload is honored.

         @tblsubhd{If bit 30=0}
         This is not the last buffer in the stream. This is useful in
         removing trailing samples.

         @tblsubhd{For bit 4}
         The client can set this end-of-frame flag for every buffer sent in
         which the last byte is the end of a frame. If this flag is set, the
         buffer can contain data from multiple frames, but it must always end
         at a frame boundary. Restrictions allow the aDSP to detect an end of
         frame without requiring additional processing. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_write_v2_t */

/** @ingroup asmdata_cmd_read
    Delivers an empty data buffer to be filled by the ASM.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_READ_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_read_v2_t}
    @tablens{weak__asm__data__cmd__read__v2__t} @newpage

  @return
    #ASM_DATA_EVENT_READ_DONE_V2 is raised when the buffer is consumed.

  @dependencies
    The session/stream must be a valid and opened write or read/write
    session/stream.
    @par
    A memory map handle must be obtained from the aDSP using the
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.
*/
#define ASM_DATA_CMD_READ_V2                                         0x00010DAC

/* Payload for an ASM Data Read command. */
typedef struct asm_data_cmd_read_v2_t asm_data_cmd_read_v2_t;

#include "adsp_begin_pack.h"
                      
/** @weakgroup weak_asm_data_cmd_read_v2_t
@{ */
/* Payload of the ASM_DATA_CMD_READ_V2 command, which delivers a data
    buffer to the ASM for encoded data. */
/** Each frame's buffer address must be a physical address that has
    been mapped via #ASM_CMD_SHARED_MEM_MAP_REGIONS.
*/
struct asm_data_cmd_read_v2_t
{
    uint32_t                  buf_addr_lsw;
    /**< Lower 32 bits of the address of the buffer where the aDSP puts the
         encoded data. */

    uint32_t                  buf_addr_msw;
    /**< Upper 32 bits of the address of the buffer where the aDSP puts the
         encoded data.

         Each frame's buffer address must be a valid, mapped, physical address
         that has been mapped via #ASM_CMD_SHARED_MEM_MAP_REGIONS. The address
         can be at an offset specified in the offset field of
         #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2.

         The 64-bit number formed by buf_addr_lsw and buf_addr_msw must be
         aligned to a 32-byte boundary.

         @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw
         field must be set to zero.

         @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
         buf_addr_msw field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buf_size;
    /**< Number of bytes available for the aDSP to write. The aDSP starts
         writing from the buffer address.

         @values > 0  */

    uint32_t                  seq_id;
    /**< Optional buffer sequence ID. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_read_v2_t */

/** @ingroup asmdata_cmd_read_compressed
    Delivers an empty data buffer to be filled by the ASM in Compressed Read
    mode.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_READ_COMPRESSED_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_read_compressed_v2_t}
    @table{weak__asm__data__cmd__read__compressed__v2__t}

  @return
    #ASM_DATA_EVENT_READ_DONE_V2 is raised when the buffer is consumed, or if
    #ASM_STREAM_CMD_FLUSH is issued.

  @dependencies
    This command must be applied to a valid session opened using the
    #ASM_STREAM_CMD_OPEN_READ_COMPRESSED command.
    @par
    The memory map handle must be obtained from the aDSP using the
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.
*/
#define ASM_DATA_CMD_READ_COMPRESSED_V2                                0x00010DC1

/* Payload for an ASM Data Read Compressed command. */
typedef struct asm_data_cmd_read_compressed_v2_t asm_data_cmd_read_compressed_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_read_compressed_v2_t
@{ */
/* Payload of the ASM_DATA_CMD_READ_COMPRESSED_V2 command, which delivers
    a data buffer to the ASM for encoded data.
*/
struct asm_data_cmd_read_compressed_v2_t
{
    uint32_t                  buf_addr_lsw;
    /**< Lower 32 bits of the address of the buffer where the aDSP puts the
         encoded data. */

    uint32_t                  buf_addr_msw;
    /**< Upper 32 bits of the address of the buffer where the aDSP puts the
         encoded data.
         
         Each frame's buffer address must be a valid, mapped, physical address
         that has been mapped via #ASM_CMD_SHARED_MEM_MAP_REGIONS. The address
         can be at an offset specified in the offset field of
         #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2.

         The 64-bit number formed by buf_addr_lsw and buf_addr_msw must be
         aligned to a 32-byte boundary.

         @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw
         field must be set to zero.

         @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
         buf_addr_msw field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buf_size;
    /**< Number of bytes available for the aDSP to write. The aDSP starts
         writing from the buffer address.

         @values > 0  */

    uint32_t                  seq_id;
      /**< Optional buffer sequence ID. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_read_compressed_v2_t */

/** @ingroup asmdata_cmd_eos
    Communicates an End of Stream (EOS) marker, which indicates that the last
    buffer in a stream has been delivered. For two or more streams routed to
    the same AFE port, the client sends unique token IDs in the APR header of
    the EOS command.

    Because the AFE generates #ASM_DATA_EVENT_RENDERED_EOS with the same token
    ID, the client can correlate the events with the EOS commands it sent for
    each stream.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_EOS
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @return
    #ASM_DATA_EVENT_RENDERED_EOS is raised when the final sample before the
    EOS has been rendered.

  @dependencies
    The session/stream must be a valid and opened write or read/write
    session/stream.
*/
#define ASM_DATA_CMD_EOS                                            0x00010BDB

/** @ingroup asmdata_cmd_mark_buffer
    Communicates a marked buffer containing a token for identification.
    When the marked buffer has been lost or processed, the relevant service
    raises an event (#ASM_DATA_EVENT_MARK_BUFFER_V2) using the token.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_MARK_BUFFER_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @msgpayload{asm_data_cmd_mark_buffer_v2_t}
    @tablens{weak__asm__data__cmd__mark__buffer__v2__t}

  @return
    None

  @dependencies
    The session/stream must be a valid and opened write, read/write, or
    compressed write session/stream.
*/
#define ASM_DATA_CMD_MARK_BUFFER_V2                                      0x00012F15
/* Structure for a Mark Buffer command. */
typedef struct asm_data_cmd_mark_buffer_v2_t asm_data_cmd_mark_buffer_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_mark_buffer_v2_t
@{ */
/* Payload of the #ASM_DATA_CMD_MARK_BUFFER_V2 command, which indicates an
   update to the media format that applies to future buffers written to this
   stream.
*/
struct asm_data_cmd_mark_buffer_v2_t
{
    uint32_t                    token_lsw;
    /**< Lower 32 bits of the token value. The aDSP does not care about the
         value. */

    uint32_t                    token_msw;
    /**< Upper 32 bits of the token value. The aDSP does not care about the
         value. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_mark_buffer_v2_t */

/** @addtogroup asmdata_event_mark_buffer
@{ */
/** Defines the event for a marked buffer that is either processed or lost.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_MARK_BUFFER_V2
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @msgpayload{asm_data_event_mark_buffer_v2_t}
    @tablens{weak__asm__data__event__mark__buffer__v2__t}

  @return
    None

  @dependencies
    The session/stream must be a valid and opened write or read/write
    session/stream.
*/
#define ASM_DATA_EVENT_MARK_BUFFER_V2                                      0x00012F16

/* Structure for a Mark Buffer event. */
typedef struct asm_data_event_mark_buffer_v2_t asm_data_event_mark_buffer_v2_t;

/** Indicates that a marked buffer has been processed. */
#define ASM_DATA_EVENT_MARK_BUFFER_PROCESSED                              0

/** Indicates that a marked buffer has been discarded. */
#define ASM_DATA_EVENT_MARK_BUFFER_DISCARDED                              1

/** @} */ /* end_addtogroup asmdata_event_mark_buffer */

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_mark_buffer_v2_t
@{ */
/* Payload of the #ASM_DATA_EVENT_MARK_BUFFER_V2 command, which indicates an event
 * regarding an adsp marked buffer is either processed or lost
*/
struct asm_data_event_mark_buffer_v2_t
{
    uint32_t                    token_lsw;
    /**< Lower 32 bits of the token value. The aDSP does not care about the
         value. */

    uint32_t                    token_msw;
    /**< Upper 32 bits of the token value. The aDSP does not care about the
         value. */

    uint32_t                    result;
    /**< Result of the marked buffer.

         @values
         - #ASM_DATA_EVENT_MARK_BUFFER_PROCESSED
         - #ASM_DATA_EVENT_MARK_BUFFER_DISCARDED @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_mark_buffer_v2_t */

/** @ingroup asmdata_cmd_media_format_update
    Indicates an update to the media format, which applies to future buffers
    written to this stream.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_media_fmt_update_t}
    @tablens{weak__asm__data__cmd__media__fmt__update__t}

  @detdesc
    This message must be properly sequenced with corresponding
    #ASM_DATA_CMD_WRITE_V2 messages, i.e., it must be sent on the data path.
    @par
    This command is also sent by the client after opening a write stream or
    read/write stream and before sending any #ASM_DATA_CMD_WRITE_V2 commands.
    This is required to configure the decoder properly. If ASM_DATA_CMD_WRITE_V2
    commands arrive before this command, the data buffers are discarded and 
    #ASM_DATA_EVENT_WRITE_DONE_V2 events are raised with an error status for
    these commands.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session/stream must be a valid and opened write or read/write
    session/stream.
*/
/* Q3 = Async Packet Router API Interface Spec for MDM9x15 (80-N1463-2) */
#define ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2                            0x00010D98

/* Structure for a Media Format Update command. */
typedef struct asm_data_cmd_media_fmt_update_v2_t asm_data_cmd_media_fmt_update_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_media_fmt_update_t
@{ */
/* Payload of the #ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2 command, which indicates an
   update to the media format that applies to future buffers written to this
   stream. */
/** Immediately following this structure is a media format block of size
    fmt_blk_size.
*/
struct asm_data_cmd_media_fmt_update_v2_t
{
    uint32_t                    fmt_blk_size;
    /**< Media format block size in bytes. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_media_fmt_update_t */

/** @cond OEM_only */
/** @ingroup asmstrm_evt_dtmf_tone_end
    Indicates that an ASM stream event for DTMF tone has ended. This is raised
    by the AFE for write streams.

  @apr_hdr_fields
    Opcode -- ASM_STREAM_EVENT_DTMF_TONE_ENDED
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @detdesc
    After completion of DTMF tone generation, the aDSP sends this
    event to the client under the following conditions:
      - When a finite duration tone is completely played out
      - When an infinite duration tone is stopped
      - When a tone is pre-empted by a new tone while still playing
      - By the destination AFE port when the last sample has been rendered,
        like the #ASM_DATA_EVENT_RENDERED_EOS event.
    @par
    The destination port in this event is same as the source port sent in
    the #ASM_STREAM_CMD_DTMF_CTL command.
    @par
    This event cannot be raised when the client sends a flush command
    immediately after sending the tone end command. The client is responsible
    for tagging each DTMF command (such as using a counter value in the APR
    token field) so it can safely ignore the ASM_DATA_EVENT_RENDERED_EOS
    event that has been flushed.

  @return
    None.

  @dependencies
    None.
*/
#define ASM_STREAM_EVENT_DTMF_TONE_ENDED                           0x00010C1E
/** @endcond */

/** @ingroup asmdata_event_rendered_eos
    Indicates that the last sample in the write or read/write stream has been
    successfully rendered after an EOS data command is received, and that no
    more samples will be rendered.

    This event is raised by the AFE for tunneled playback streams, or by the
    encoder service for non-tunneled streams.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_RENDERED_EOS
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

    @apr_msgpayload
    None.

  @return
    None.

  @dependencies
    The stream must be open for write.
*/
#define ASM_DATA_EVENT_RENDERED_EOS                                 0x00010C1C

/** @ingroup asmdata_event_eos
    Indicates that data is being read from a read or read/write stream that
    has reached the EOS.

    @note1hang Do not confuse this event with the acknowledgment to
    #ASM_DATA_CMD_EOS received on a write stream. This ASM_DATA_EVENT_EOS is
    an independent event generated toward the client.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_EOS
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload
    None.

  @return
    None.

  @dependencies
    The stream must be open for read or read/write.
*/
#define ASM_DATA_EVENT_EOS                                          0x00010BDD

/** @ingroup asmdata_event_write_done
    Indicates that the referenced buffer has been fully consumed and is again
    available to the client.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_WRITE_DONE_V2
    @par
    Token  -- Matches the token in the #ASM_DATA_CMD_WRITE_V2 command for
              which this event is being raised
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_write_done_v2_t}
    @table{weak__asm__data__event__write__done__v2__t}

  @return
    None.

  @dependencies
    The session/stream must be a valid and open write or read/write
    session/stream.
    @par
    A corresponding #ASM_DATA_CMD_WRITE_V2 command must have been received and
    processed.
*/
#define ASM_DATA_EVENT_WRITE_DONE_V2                                   0x00010D99

/* Structure for a data write done event payload. */
typedef struct asm_data_event_write_done_v2_t asm_data_event_write_done_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_write_done_v2_t
@{ */
/* Payload of the ASM_DATA_EVENT_WRITE_DONE_V2 event, which indicates
    that the referenced buffer has been fully consumed and is again available
    to the client.    
*/
struct asm_data_event_write_done_v2_t
{
    uint32_t                  buf_addr_lsw;
    /**< Lower 32 bits of the address of the buffer being returned. */

    uint32_t                  buf_addr_msw;
    /**< Upper 32 bits of the address of the buffer being returned.
         
         The valid, mapped, 64-bit physical address is the same address that
         is provided by the client in #ASM_DATA_CMD_WRITE_V2. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_DATA_CMD_WRITE_V2 command. */

    uint32_t                  status;
    /**< Status message (error code) that indicates whether the referenced
         buffer has been successfully consumed.

         @values Refer to @xhyperref{Q5,[Q5]} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_write_done_v2_t */

/** @addtogroup asmdata_event_read_done
@{ */
/** Indicates that the referenced buffer has been filled and is available to
    the client.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_READ_DONE_V2
    @par
    Token  -- Matches the token in the #ASM_DATA_CMD_READ_V2 command for which
              this event is being raised
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_read_done_v2_t}
    @table{weak__asm__data__event__read__done__v2__t}

  @detdesc
    The referenced buffer contains an optional array of metadata if the client
    requested it in an open command. This is followed by a variable amount of
    empty space, assuming metadata is present, followed by an integer number
    of encoded frames. Metadata presence is indicated by bit 30 of the flags
    field in the APR message payload structure.

  @par Frame metadata (asm_data_read_buf_metadata_v2_t)
    @xreflabel{hdr:FrameMetadataRead}
    Information for each encoded frame is inside the buffer. If bit 30 of the
    flags field is set to 1, this metadata structure is present in the buffer
    when ASM_DATA_EVENT_READ_DONE_V2 is issued. Following this metadata
    structure is the resulting buffer from the read event (see
    <b>Buffer format</b> on the next page).
    @tablens{weak__asm__data__read__buf__metadata__v2__t}
    
  @par Buffer format
    A multiframe buffer becomes an array of Hexagon frame metadata
    information structures, and then an array of audio frames. Encoded
    frames start with <i>offset</i>.
    @verbatim
       MetaData 0 (optional)
       MetaData 1 (optional)
          . . .
       MetaData n (optional)
       Extra space determined by the Hexagon processor (optional)
       Frame 0 Payload (this always starts at an offset from buf_addr)
       Frame 1 Payload
          . . .
       Frame n Payload

    @endverbatim
    Resulting buffer from a read event:
    @inputtable{Frame_metadata_buffer_content.tex}

  @return
    None.

  @dependencies
    The session/stream must be a valid and open write or read/write
    session/stream.
    @par
    A corresponding #ASM_DATA_CMD_READ_V2 command must have been received and
    processed.
*/
#define ASM_DATA_EVENT_READ_DONE_V2                                    0x00010D9A

/** Definition of the frame metadata flag bitmask. */
#define ASM_BIT_MASK_FRAME_METADATA_FLAG                            (0x40000000UL)

/** Definition of the frame metadata flag shift value. */
#define ASM_SHIFT_FRAME_METADATA_FLAG                               30

/** @} */ /* end_addtogroup asmdata_event_read_done */

/* Structure for the data read done event payload. */
typedef struct asm_data_event_read_done_v2_t asm_data_event_read_done_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_read_done_v2_t
@{ */
/* Payload of the ASM_DATA_EVENT_READ_DONE_V2 event, which indicates
    that the referenced buffer has been filled and is available to the client.
*/
struct asm_data_event_read_done_v2_t
{
   uint32_t                  status;
   /**< Status message (error code).

        @values Refer to @xhyperref{Q5,[Q5]} */
   /* Q5 = Async Packet Router API (for MDM9x15 and Newer) IS (80-N1463-2) */

   uint32_t                  buf_addr_lsw;
   /**< Lower 32 bits of the valid, mapped address of the buffer containing
        the decoded data. */

   uint32_t                  buf_addr_msw;
   /**< Upper 32 bits of the valid, mapped address of the buffer containing
        the decoded data. 

        The 64-bit number formed by buf_addr_lsw and buf_addr_msw must be
        aligned to a 32-byte boundary. This is the same address that is
        provided by the client in #ASM_DATA_CMD_READ_V2.

        @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw field
        must be set to zero.

        @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
        buf_addr_msw field must be set to zero. */

   uint32_t                  mem_map_handle;
   /**< Unique identifier for an address.

        This memory map handle is returned by the aDSP through the
        #ASM_DATA_CMD_READ_V2 command. */

   uint32_t                  enc_frames_total_size;
   /**< Total size of the encoded frames in bytes.

        @values @ge 0  */

   uint32_t                  offset;
   /**< Offset from the buffer address to the first byte of the first encoded
        frame. All encoded frames are consecutive, starting from this offset.
          
        @values > 0 */

   uint32_t                  timestamp_lsw;
   /**< Lower 32 bits of the 64-bit session time in microseconds of the
        first sample in the buffer. */

   uint32_t                  timestamp_msw;
   /**< Upper 32 bits of the 64-bit session time in microseconds of the
        first sample in the buffer.

        If bit 5 of the mode_flags field of #ASM_STREAM_CMD_OPEN_READ_V2 is set
        to 1, the 64-bit timestamp is an absolute capture time. Otherwise, it
        is a relative session time. The absolute timestamp does not reset
        unless the system is reset. */

   uint32_t                  flags;
   /**< Bit field of flags.

        @values{for bit 31}
        - 1 -- Timestamp is valid
        - 0 -- Timestamp is invalid
        - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_VALID_FLAG and
          #ASM_SHIFT_TIMESTAMP_VALID_FLAG

        @values{for bit 30}
        - 1 -- Frame metadata is present
        - 0 -- Frame metadata is absent
        - To set this bit, use #ASM_BIT_MASK_FRAME_METADATA_FLAG and
          #ASM_SHIFT_FRAME_METADATA_FLAG

        All other bits are reserved; the aDSP sets them to 0.
        
        If bit 30 is set to 1, num_frames of consecutive instances of
        %asm_data_read_buf_metadata_v2_t start at the buffer address
        (see <b>Buffer format</b>). */

   uint32_t                  num_frames;
   /**< Number of encoded frames in the buffer. */

   uint32_t                  seq_id;
   /**< Optional buffer sequence ID. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_read_done_v2_t */

/* Structure for metadata that can be put in the data read buffer. */
typedef struct asm_data_read_buf_metadata_v2_t asm_data_read_buf_metadata_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_read_buf_metadata_v2_t
@{ */
/* Payload of the metadata that can be put in the data read buffer.
*/
struct asm_data_read_buf_metadata_v2_t
{
   uint32_t          offset;
   /**< Offset from the buffer address in %asm_data_event_read_done_v2_t to
        the frame associated with the metadata.
          
        @values > 0 */

   uint32_t          frm_size;
   /**< Size of the encoded frame in bytes.

        @values > 0 */

   uint32_t          num_encoded_pcm_samples;
   /**< Number of encoded PCM samples (per channel) in the frame 
        associated with the metadata.
          
        @values > 0 */

   uint32_t          timestamp_lsw;
   /**< Lower 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame. */

   uint32_t          timestamp_msw;
   /**< Upper 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame.

        If bit 5 of the mode_flags field of #ASM_STREAM_CMD_OPEN_READ_V2 is set
        to 1, the 64-bit timestamp is an absolute capture time. Otherwise, it
        is a relative session time. The absolute timestamp does not reset
        unless the system is reset. */

   uint32_t          flags;
   /**< Frame flags.

        @values{for bit 31}
        - 1 -- Timestamp is valid
        - 0 -- Timestamp is not valid
        - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_VALID_FLAG and
          #ASM_SHIFT_TIMESTAMP_VALID_FLAG

        All other bits are reserved; the aDSP sets them to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_read_buf_metadata_v2_t */

/** @ingroup asmdata_event_read_compr_done
    Indicates that the referenced buffer has been filled and is available to
    the client.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2
    @par
    Token  -- Matches the token in the #ASM_DATA_CMD_READ_COMPRESSED_V2 command
              for which this event is being raised
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_read_compressed_done_v2_t}
    If bit 30 of the flags field is set to 1, frame metadata is present in
    the buffer (i.e., the number of frames indicated in the event payload is
    greater than zero). In this case, num_frames consecutive instances of
    <b>Frame metadata</b> start at the buffer address.
    @tablens{weak__asm__data__event__read__compressed__done__v2__t}

  @par Frame metadata (asm_data_read_buf_metadata_compressed_v2_t)
    Information for each encoded frame is inside the buffer. If bit 30 of the
    flags field is set to 1, this metadata structure is present in the buffer
    when #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 is issued. Following this
    metadata structure is the resulting buffer from the read event (see
    (see <b>Buffer format</b>).
    @tablens{weak__asm__data__read__buf__metadata__compressed__v2__t} @newpage
    
  @par Buffer format
    A multiframe buffer becomes an array of Hexagon frame metadata
    information structures, and then an array of audio frames. Encoded
    frames start with <i>offset</i>.
    @verbatim
       MetaData 0 (optional)
       MetaData 1 (optional)
          . . .
       MetaData n (optional)
       Extra space determined by the Hexagon processor (optional)
       Frame 0 Payload (this always starts at an offset from buf_addr)
       Frame 1 Payload
          . . .
       Frame n Payload

    @endverbatim
    Resulting buffer from a read event:
    @inputtable{Frame_metadata_buffer_content.tex}

  @detdesc            
    The #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 event is raised when the
    specified number of frames are filled in the buffer. The client can force
    this event by issuing #ASM_STREAM_CMD_FLUSH.
    @par
    The referenced buffer contains an optional array of metadata if the client
    requested it in an open command. This is followed by a variable amount of
    empty space, assuming metadata is present, followed by an integer number
    of encoded frames. Metadata presence is indicated by bit 30 of the flags
    field in the APR message payload structure.

  @return
    None. @newpage

  @dependencies
    This command must be applied to a valid stream opened using the
    #ASM_STREAM_CMD_OPEN_READ_COMPRESSED command.
    @par
    A corresponding #ASM_DATA_CMD_READ_COMPRESSED_V2 command must have been
    received and processed.
*/
#define ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2                        0x00010DC2

/* Structure for the data read done event payload. */
typedef struct asm_data_event_read_compressed_done_v2_t asm_data_event_read_compressed_done_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_read_compressed_done_v2_t
@{ */
/* Payload of the ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 event, which
    indicates that the referenced buffer has been filled and is available to
    the client.
*/
struct asm_data_event_read_compressed_done_v2_t
{
   uint32_t                  status;
   /**< Status message (error code).

        @values Refer to @xhyperref{Q5,[Q5]} */

   uint32_t                  buf_addr_lsw;
   /**< Lower 32 bits of the address of the buffer where the aDSP put the
        encoded data. */

   uint32_t                  buf_addr_msw;
   /**< Upper 32 bits of the address of the buffer where the aDSP put the
        encoded data.

        This is the address provided by the client in
        #ASM_DATA_CMD_READ_COMPRESSED_V2. The 64-bit number formed by
        buf_addr_lsw and buf_addr_msw must be aligned to a 32-byte boundary.

        @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw field
        must be set to zero.

        @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
        buf_addr_msw field must be set to zero. */

   uint32_t                  mem_map_handle;
   /**< Unique identifier for an address.

        This memory map handle is returned by the aDSP through the
        #ASM_DATA_CMD_READ_COMPRESSED_V2 command. */

   uint32_t                  enc_frames_total_size;
   /**< Total size of the encoded frames. This field is set to 0 if no frames
        are present in the buffer.

        @values @ge 0  bytes */

   uint32_t                  offset;
   /**< Offset from the buffer address to the first byte of the first encoded
        frame. All encoded frames are consecutive, starting from this offset.

        @values > 0 */

   uint32_t                  timestamp_lsw;
   /**< Lower 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame. */

   uint32_t                  timestamp_msw;
   /**< Upper 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame.

        The timestamp is valid only if there is at least one valid frame.

        If bit 5 of the mode_flags field of #ASM_DATA_CMD_READ_COMPRESSED_V2
        is set to 1, the 64-bit timestamp is an absolute capture time.
        Otherwise, it is a relative session time. The absolute timestamp does
        not reset unless the system is reset. */

   uint32_t                  flags;
   /**< Bit field of flags.
    
        @values{for bit 31}
        - 1 -- Timestamp is valid
        - 0 -- Timestamp is invalid
        - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_VALID_FLAG and
          #ASM_SHIFT_TIMESTAMP_VALID_FLAG

        @values{for bit 30}
        - 1 -- Frame metadata is present
        - 0 -- Frame metadata is absent
        - To set this bit, use #ASM_BIT_MASK_FRAME_METADATA_FLAG and
          #ASM_SHIFT_FRAME_METADATA_FLAG

        All other bits are reserved; the aDSP sets them to zero. */

   uint32_t                  num_frames;
   /**< Number of encoded frames in the buffer. */

   uint32_t                  seq_id;
   /**< Optional buffer sequence ID. This is the same ID provided in
        #ASM_DATA_CMD_READ_COMPRESSED_V2.*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_read_compressed_done_v2_t */

/* Structure for metadata that can be put in the data read compressed buffer. */
typedef struct asm_data_read_buf_metadata_compressed_v2_t asm_data_read_buf_metadata_compressed_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_read_buf_metadata_compressed_v2_t
@{ */
/* Payload of the metadata that can be put in the data read buffer when
    ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 is issued. 
*/
struct asm_data_read_buf_metadata_compressed_v2_t
{
    uint32_t          bitstream_id;
   /**< If multiple audio bitstreams are transferred over the same IEC 61937
        data streams, this is the sequence ID of the stream to which the frame
        belongs. */

   uint32_t          format_id;
   /**< Indicates the format of the incoming stream captured from the HDMI or
        SPDIF interface.

        @values Any valid format ID */

   uint32_t          data_offset;
   /**< Offset from the buffer address in the
        #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 payload to the frame associated
        with the metadata.

        @values > 0 bytes */

   uint32_t          data_size;
   /**< Size of the encoded frame.

        @values > 0 bytes */

   uint32_t          command_offset;
   /**< Offset from the buffer address in the
        #ASM_DATA_EVENT_READ_COMPRESSED_DONE_V2 payload to the command
        associated with the encoded frame.

        @values > 0 bytes

        This command offset is valid only if the command size is greater than
        zero. Commands are present only for DTS Type 4 streams received through
        HDMI input. */

   uint32_t          command_size;
   /**< Size of the command associated with the encoded frame.

        @values 0 bytes (no command is present)

        Currently, the aDSP does not support commands that are present for DTS
        Type 4 streams received through HDMI input, and this field is set to
        zero. */

   uint32_t          num_encoded_pcm_samples;
   /**< Number of encoded PCM samples per channel in the frame
        associated with the metadata.

        @values > 0 */

   uint32_t          timestamp_lsw;
   /**< Lower 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame. */

   uint32_t          timestamp_msw;
   /**< Upper 32 bits of the 64-bit session time in microseconds of the
        first sample in the frame.
        
        If bit 5 of the mode_flags field of #ASM_STREAM_CMD_OPEN_READ_V2 is
        set to 1, the 64-bit timestamp is an absolute capture time.
        Otherwise, it is a relative session time. The absolute timestamp does
        not reset unless the system is reset. */

   uint32_t          flags;
   /**< Frame flags.

        @values{for bit 31}
        - 1 -- Timestamp is valid
        - 0 -- Timestamp is not valid
        - To set this bit, use #ASM_BIT_MASK_TIMESTAMP_VALID_FLAG and
          #ASM_SHIFT_TIMESTAMP_VALID_FLAG

        All other bits are reserved; the aDSP sets them to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_read_buf_metadata_compressed_v2_t */

/** @ingroup asmdata_event_dec_sr_cm_update
    Notifies the client of a change in the data sampling rate or Channel mode.
    This event is raised by the decoder service.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_SR_CM_CHANGE_NOTIFY
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_sr_cm_change_notify_t}
    @table{weak__asm__data__event__sr__cm__change__notify__t}

  @detdesc
    This event is raised when both of these conditions are true:
    - The event is enabled through the mode flags of
      #ASM_STREAM_CMD_OPEN_WRITE_V2 or #ASM_STREAM_CMD_OPEN_READWRITE_V2.
    - The decoder detects a change in the output sampling frequency or the
      number/positioning of output channels, or if it is the first frame
      decoded.
    @par
    @note1hang This event is not be raised for MIDI (even if it is enabled)
               because there is no concept of sampling frequency or number of
               channels in a MIDI file.
    @par
    The new sampling frequency or the new channel configuration is
    communicated back to the client asynchronously. Channel configuration
    consists of the number of channels and the positioning of each channel.
    The event is helpful for clients to update the user interface upon
    changes in decoded bitstream parameters. @newpage

  @return
    None.

  @dependencies
    The stream must be in the Open state.
    @par
    At least one complete frame of encoded data must be available to the
    decoder.
*/
#define ASM_DATA_EVENT_SR_CM_CHANGE_NOTIFY                        0x00010C65

/* Payload for decoder sampling rate or channel mode change event. */
typedef struct asm_data_event_sr_cm_change_notify_t asm_data_event_sr_cm_change_notify_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_sr_cm_change_notify_t
@{ */
/* Payload of the ASM_DATA_EVENT_SR_CM_CHANGE_NOTIFY event.
*/
struct asm_data_event_sr_cm_change_notify_t
{
    uint32_t                  sample_rate;
    /**< New sampling rate after detecting a change in the bitstream.

         @values 2000 to 48000 Hz */
    
    uint16_t                  num_channels;
    /**< New number of channels after detecting a change in the bitstream.

         @values 1 to 8 */
    
    uint16_t                  reserved;
    /**< This field must be set to zero. */
    
    uint8_t                   channel_mapping[8];
    /**< Mapping for each of the channels. Channel[i] mapping describes the
         position of channel i, where 0 @le num_channels. Each entry in the
         array can have the following values.
    
         @values See Section @xref{dox:PcmChannelDefs} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_sr_cm_change_notify_t */

/** @ingroup asmdata_event_enc_sr_cm_update
    Notifies the client of a data sampling rate or channel mode change. This
    event is raised by the encoder service.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_ENC_SR_CM_CHANGE_NOTIFY
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_enc_sr_cm_change_notify_t}
    @table{weak__asm__data__event__enc__sr__cm__change__notify__t}
    
  @detdesc
    This event is raised when all of the following conditions are true:
     - The stream is opened through #ASM_STREAM_CMD_OPEN_READWRITE_V2 or
       #ASM_STREAM_CMD_OPEN_READ_V2.
     - The encoding format is #ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2.
     - Native mode encoding was requested in the encoder configuration (i.e.,
       the channel number was 0), the sample rate was 0, or both were 0.
     - The input data frame at the encoder is the first one, or the sampling
       rate/channel mode is different from the previous input data frame.
    @par
    Immediately after this event is raised, the encoder service stops
    processing input data and waits for the client to issue
    #ASM_STREAM_CMD_FLUSH_READBUFS. Data processing resumes after successfully
    handling #ASM_STREAM_CMD_FLUSH_READBUFS.

  @return
    None.

  @dependencies
    The stream must have been opened by #ASM_STREAM_CMD_OPEN_READWRITE_V2 or
    #ASM_STREAM_CMD_OPEN_READ_V2.
*/
#define ASM_DATA_EVENT_ENC_SR_CM_CHANGE_NOTIFY                    0x00010BDE

/* Payload for encoder sampling rate, channel mode change event. */
typedef struct asm_data_event_enc_sr_cm_change_notify_t asm_data_event_enc_sr_cm_change_notify_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_enc_sr_cm_change_notify_t
@{ */
/* Payload of the ASM_DATA_EVENT_ENC_SR_CM_CHANGE_NOTIFY event.
 */
struct asm_data_event_enc_sr_cm_change_notify_t
{
    uint32_t                  sample_rate;
    /**< New sampling rate after detecting a change in the input data.

         @values 2000 to 48000 Hz */
    
    uint16_t                  num_channels;
    /**< New number of channels after detecting a change in the input data.

         @values 1 to 8 */
    
    uint16_t                  bits_per_sample;
    /**< New bits per sample after detecting a change in the input data.

         @values 16, 24 */
    
    uint8_t                   channel_mapping[8];
    /**< New channel mapping. Channel[i] mapping describes the position of
         channel i, where 0 @le i < num_channels. Each entry in the array
         can have the following values.

         @values See Section @xref{dox:PcmChannelDefs} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_enc_sr_cm_change_notify_t */

/** @cond OEM_only */
/** @ingroup asmdata_cmd_write_spa_data
    Delivers an empty data buffer to the ASM for filling with spectrum
    analyzer data.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_SPA_V2
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_spa_v2_t}
    @table{weak__asm__data__cmd__spa__v2__t}

  @return
    #ASM_DATA_EVENT_SPA_DONE_V2 is raised when the buffer is filled.

  @dependencies
    The session/stream must be a valid and opened session/stream.
    @par
    The spectrum analyzer feature must be enabled using
    #ASM_STREAM_CMD_SET_PP_PARAMS_V2.
*/
#define ASM_DATA_CMD_SPA_V2                                          0x00010D9B

/* Payload for a Spectrum Analyzer Data command. */
typedef struct asm_data_cmd_spa_v2_t asm_data_cmd_spa_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_spa_v2_t
@{ */
/* Payload of the ASM_DATA_CMD_SPA_V2 command, which delivers a data
    buffer to the Spectrum Analyzer module to be filled with spectrum data.
*/
struct asm_data_cmd_spa_v2_t
{
    uint32_t                  buf_addr_lsw;
    /**< Lower 32 bits of the address where the aDSP puts the spectrum
         analyzer data. */

    uint32_t                  buf_addr_msw;
    /**< Upper 32 bits of the address where the aDSP puts the spectrum
         analyzer data.

         The valid, mapped, 64-bit address is the same address that is
         provided by the client in #ASM_CMD_SHARED_MEM_MAP_REGIONS.

         @tblsubhd{For a 32-bit shared memory address} This buf_addr_msw field
         must be set to zero.

         @tblsubhd{For a 36-bit shared memory address} Bits 31 to 4 of this
         buf_addr_msw field must be set to zero. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buf_size;
    /**< Number of valid bytes available in the buffer for decoding. The first
         byte starts at the buffer address.

         @values > 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_spa_v2_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup asmdata_event_spa_done
@{ */
/** Sends a spectrum analyzer done event, which indicates that the referenced
    buffer has been filled with spectrum analyzer data and is available to the
    client.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_SPA_DONE_V2
    @par
    Token  -- Matches the token in the original #ASM_DATA_CMD_SPA_V2 buffer
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_spa_done_v2_t}
    @table{weak__asm__data__event__spa__done__v2__t}

  @par Filled buffer format
    The filled buffer contains the spectral coefficients and, optionally, the
    PCM data that was used to calculate these coefficients (described in the
    tables below). Following is the format of the spectrum analyzer buffer.
    @par
    Beginning of the buffer:
    - Coefficient header
    - Coefficient data
    @par
    Next 32-bit-aligned position:
    - PCM header 
    - PCM data

  @par Spectral coefficients (asm_data_spa_spectrum_data_header_t)
    This structure is immediately followed by num_coeffs of coefficients.
    @tablens{weak__asm__data__spa__spectrum__data__header__t} @newpage

  @par Optional PCM data (asm_data_spa_pcm_data_header_t)
    This structure is immediately followed by num_samples of PCM samples.
    @tablens{weak__asm__data__spa__pcm__data__header__t}

  @return
    None.

  @dependencies
    The session/stream must be a valid, open session/stream.
    @par
    A corresponding #ASM_DATA_CMD_SPA_V2 command must have been received and
    processed.
*/
#define ASM_DATA_EVENT_SPA_DONE_V2                                    0x00010D9C

/** Definition of the spectrum analyzer timestamp valid flag mask. */
#define ASM_BIT_MASK_SPA_TIMESTAMP_VALID_FLAG                      (0x80000000UL)

/** Definition of the spectrum analyzer timestamp valid flag shift value. */
#define ASM_SHIFT_SPA_TIMESTAMP_VALID_FLAG                               31

/** Definition of the spectrum analyzer PCM data flag bitmask. */
#define ASM_BIT_MASK_SPA_PCM_DATA_FLAG                             (0x40000000UL)

/** Definition of the spectrum analyzer PCM data flag shift value. */
#define ASM_SHIFT_SPA_PCM_DATA_FLAG                                      30

/** @} */ /* end_addtogroup asmdata_event_spa_done */

/* Payload for a spectrum analyzer done event. */
typedef struct asm_data_event_spa_done_v2_t asm_data_event_spa_done_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_spa_done_v2_t
@{ */
/*f Payload of the #ASM_DATA_EVENT_SPA_DONE_V2 event, which indicates that
    the spectrum analyzer buffer has been filled and is available to the client.
*/
struct asm_data_event_spa_done_v2_t
{
   uint32_t                  status;
   /**< Status message (error code).

        @values
        - ADSP_EOK -- Success 
        - ADSP_EUNEXPECTED -- Spectrum analyzer is disabled
        - Other aDSP error codes -- Memory mapping failure or general
          failure
            
        For more details, refer to @xhyperref{Q5,[Q5]}. */

   uint32_t                  flags;
   /**< Bit field of flags.

        @values{for bit 31} (which indicates whether the timestamp_msw and
        timestamp_lsw fields are valid)
        - 1 -- Timestamp is valid
        - 0 -- Timestamp is not valid
        - To set/get this bit, use #ASM_BIT_MASK_SPA_TIMESTAMP_VALID_FLAG and
          #ASM_SHIFT_SPA_TIMESTAMP_VALID_FLAG

        @values{for bit 30} (which indicates whether the PCM data header and
        PCM data are present in the returned buffer)
        - 1 -- PCM data is present along with spectrum coefficients
        - 0 -- PCM data is absent
        - To set/get this bit, use  #ASM_BIT_MASK_SPA_PCM_DATA_FLAG and
          #ASM_SHIFT_SPA_PCM_DATA_FLAG

        All other bits are reserved; the aDSP sets them to zero. */

   uint32_t                  buf_addr_lsw;
   /**< Lower 32 bits of the address containing the spectrum analyzer data. */

   uint32_t                  buf_addr_msw;
   /**< Upper 32 bits of the address containing the spectrum analyzer data.
        
        This is the valid, mapped, 64-bit physical address provided by the
        client in #ASM_DATA_CMD_SPA_V2. */

   uint32_t                  mem_map_handle;
   /**< Unique identifier for an address.

        This memory map handle is returned by the aDSP through the
        #ASM_DATA_CMD_SPA_V2 command. */

   uint32_t                  actual_size;
   /**< Total size of the valid data in the buffer. This size includes the
        sizes of all headers and data, and any padding.

        @values @ge 0 bytes */

   uint32_t                  timestamp_lsw;
   /**< Lower 32 bits of the 64-bit session time in microseconds of the
        first sample in the buffer. */

   uint32_t                  timestamp_msw;
   /**< Upper 32 bits of the 64-bit session time in microseconds of the
        first sample in the buffer.

        The timestamp is valid only if bit 31 of the flags field is set to 1. */

   uint32_t                  sample_rate;
   /**< Sampling rate in Hertz of the audio stream. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_spa_done_v2_t */

/* Structure for the coefficient header in the spectrum analyzer buffer. */
typedef struct asm_data_spa_spectrum_data_header_t asm_data_spa_spectrum_data_header_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_spa_spectrum_data_header_t
@{ */
/* Payload of the coefficient header in the buffer of the
    ASM_DATA_EVENT_SPA_DONE_V2 event.
*/
struct asm_data_spa_spectrum_data_header_t
{
   uint32_t                  coeff_size;
   /**< Size in bits of each spectral coefficient. The 32-bit index is 0. */

   uint32_t                  num_coeffs;
   /**< Number of spectral coefficients. The 32-bit index is 6. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_spa_spectrum_data_header_t */

/* Structure for the PCM header in the spectrum analyzer buffer. */
typedef struct asm_data_spa_pcm_data_header_t asm_data_spa_pcm_data_header_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_spa_pcm_data_header_t
@{ */
/* Payload of the PCM header in the buffer of the ASM_DATA_EVENT_SPA_DONE_V2
    event.
*/
struct asm_data_spa_pcm_data_header_t
{
   uint32_t                  sample_size;
   /**< Size in bits of each PCM sample. The 32-bit index is 6 * (uNum
        Frames - 1).

        This parameter is present only if the flags field in the APR message
        payload (asm_data_event_spa_done_t) indicates PCM data is present. */

   uint32_t                  num_samples;
   /**< Number of samples.  The 32-bit index is of variable size.

        This parameter is present only if the flags field in the APR message
        payload (asm_data_event_spa_done_t) indicates PCM data is present. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_spa_pcm_data_header_t */
/** @endcond */

/** @ingroup asmdata_cmd_remove_init_silence
    Indicates the number of samples per channel to be removed from the
    beginning of the stream.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_REMOVE_INITIAL_SILENCE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_remove_initial_silence_t}
    @table{weak__asm__data__cmd__remove__initial__silence__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session/stream must be valid.
    @par
    This command must be sent before the first data buffer. If it is sent
    after the first frame, the ADSP_EFAILED error code is returned, and
    samples to be returned are not updated. (For more details on the error
    code, refer to @xhyperref{Q5,[Q5]}.)
    @par
    If this message is sent multiple times before the first data buffer,
    only the last value sent is considered.
*/
#define ASM_DATA_CMD_REMOVE_INITIAL_SILENCE                             0x00010D67

/* Structure for the number of silence samples to be removed from the
    beginning of the track. */
typedef struct asm_data_cmd_remove_initial_silence_t asm_data_cmd_remove_initial_silence_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_remove_initial_silence_t
@{ */
/* Payload of the ASM_DATA_CMD_REMOVE_INITIAL_SILENCE command, which removes
    a specified number of silence samples from the beginning of the track.
*/
struct asm_data_cmd_remove_initial_silence_t
{
   uint32_t                  num_samples_to_remove;
   /**< Number of samples per channel to be removed.

        @values 0 to 2^31 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_remove_initial_silence_t */

/** @ingroup asmdata_cmd_remove_trail_silence
    Indicates the number of samples per channel to be removed from
    the end of the stream.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_REMOVE_TRAILING_SILENCE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_remove_trailing_silence_t}
    @table{weak__asm__data__cmd__remove__trailing__silence__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session/stream must be valid.
    @par
    This command must be sent before the last data buffer is sent to the
    aDSP. Also, the last buffer flag must be set for the last data buffer. If
    this command is sent after the last buffer is sent down, the error code
    ADSP_EFAILED is returned, and samples to be removed are not updated. (For
    more details on the error code, refer to @xhyperref{Q5,[Q5]}.)
    @par
    If this message is sent multiple times before the last buffer, only the
    last value sent is considered.
*/
#define ASM_DATA_CMD_REMOVE_TRAILING_SILENCE                            0x00010D68

/* Structure for the number of silence samples to be removed from the
    end of a track. */
typedef struct asm_data_cmd_remove_trailing_silence_t asm_data_cmd_remove_trailing_silence_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_remove_trailing_silence_t
@{ */
/* Payload of the ASM_DATA_CMD_REMOVE_TRAILING_SILENCE command, which
    removes a specified number of silence samples from end the of the track.
*/
struct asm_data_cmd_remove_trailing_silence_t
{
   uint32_t                  num_samples_to_remove;
   /**< Number of samples per channel to be removed.

        @values 0 to 2^31 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_remove_trailing_silence_t */

/** @cond OEM_only */
/** @ingroup asmdata_cmd_iec60958_fr_rate
    Indicates the IEC 60958 frame rate of the IEC 61937 packetized audio
    stream.
    This command is used when the aDSP is operating in Pass-through mode for
    compressed audio playback.

    Currently, sampling rate changes midstream are not supported, and the
    client is not expected to issue this command in the middle of playback.

  @apr_hdr_fields
    Opcode -- ASM_DATA_CMD_IEC_60958_FRAME_RATE
    @par
    Dst_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_cmd_iec_60958_frame_rate}
    @table{weak__asm__data__cmd__iec__60958__frame__rate}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session must be valid, and it must be opened for compressed audio
    playback in Pass-through mode.
    @par
    This command must be sent before the first data buffer. Any data buffers
    received in Pass-through mode before this message will not be processed.
    If this message is sent multiple times before the first data buffer, the
    latest value will take effect.
*/
#define ASM_DATA_CMD_IEC_60958_FRAME_RATE                            0x00010D87

/* Structure for the number of silence samples to be removed from the
    end of a track. */
typedef struct asm_data_cmd_iec_60958_frame_rate asm_data_cmd_iec_60958_frame_rate;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_cmd_iec_60958_frame_rate
@{ */
/* Payload of the ASM_DATA_CMD_IEC_60958_FRAME_RATE command, which is used to
    indicate the IEC 60958 frame rate of a given packetized audio stream.
*/
struct asm_data_cmd_iec_60958_frame_rate
{
   uint32_t                  frame_rate;
   /**< IEC 60958 frame rate of the incoming IEC 61937 packetized stream.

        @values Any valid frame rate */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_cmd_iec_60958_frame_rate */
/** @endcond */

/** @ingroup asmdata_event_watermark
   Indicates that a preconfigured watermark has been hit during Pull mode
   playback or Push mode record. The client can use this event to write more
   data or consume existing data in the buffer.

   This event is sent to the same client that opens the stream
   (to the same APR address).

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_WATERMARK
    @par
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_watermark_t}
    @table{weak__asm__data__event__watermark__t}

  @return
    None.

  @dependencies
    The session/stream must be a valid and open Pull mode write or Push mode
    read session/stream.
*/
#define ASM_DATA_EVENT_WATERMARK                                   0x00010DDB

/* Structure for a data water mark event payload. */
typedef struct asm_data_event_watermark_t asm_data_event_watermark_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_data_event_watermark_t
@{ */
/*  Payload of the ASM_DATA_EVENT_WATERMARK event, which indicates the
    approximate position of the aDSP and triggers the client to supply
    more data (playback) or consume existing data (record).
*/
struct asm_data_event_watermark_t
{
   uint32_t    watermark_level_bytes;
   /**< Watermark level that is reached.

        For Pull mode playback, this means the read pointer on the aDSP has
        reached this number of bytes from the start of the buffer.

        For Push mode record, this means that the write pointer on the aDSP
        has reached this number of bytes from the start of the buffer.

        @values 0 to circular buffer size minus 1

        This value is for information only, and the actual read or write index
        must be read using #asm_push_mode_read_position_buffer_t or
        #asm_pull_mode_write_position_buffer_t. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_data_event_watermark_t */

/** @ingroup asmdata_event_dec_error_notify
    Notifies the client of consecutive errors that reach a preset threshold.

  @apr_hdr_fields
    Opcode -- ASM_DATA_EVENT_DEC_ERR_NOTIFY \n
    Src_port:
            - Session ID 1 -- 15 (0 is reserved)
            - Stream ID 1 -- #ASM_MAX_STREAMS_PER_SESSION (0 is reserved)

  @apr_msgpayload{asm_data_event_dec_err_t}
    None.

  @detdesc
    The decoder service raises this event when all of the following conditions
    are true:
      - Functionality has been enabled by an
        #ASM_STREAM_CMD_SET_ENCDEC_PARAM command where the preset number is
        specified (denoted as N) and the preset timeout is also specified
        (denoted as T).
      - One of the following errors has occurred:
          - N consecutive decoder errors have occurred.
          - >1 consecutive decoder error has occurred and T milliseconds have
            passed.
    @par
    After this event is raised, the decoder continues processing and waits for
    instructions from the client.

  @return
    None.

  @dependencies
    None.
*/
#define ASM_DATA_EVENT_DEC_ERR_NOTIFY                        0x00010DF7


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_ASM_DATA_COMMANDS_H_ */
