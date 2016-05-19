/*======================================================================== */
/**
@file adsp_asm_service_commands.h

This file contains ASM service commands and events structures definitions.
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

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_asm_service_commands.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                    Doxygen comments/markup for 2.6 ??.
09/06/13   sw      (Tech Pubs) Merged Doxygen comments/markup from 2.0.
08/06/12   sw      (Tech Pubs) Edited comments; updated Doxygen markup to
                   Rev D.2 templates; updated legal statements for QTI.
05/30/11   sw/leo  (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
10/12/10   leo     (Tech Pubs) Edited/added Doxygen comments and markup.
04/15/10   rkc      Created file.
========================================================================== */

#ifndef _ADSP_ASM_SERVICE_COMMANDS_H_
#define _ADSP_ASM_SERVICE_COMMANDS_H_

#include "mmdefs.h"
#include "adsp_audio_memmap_api.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/** @ingroup asmsvc_cmd_get_strm_handles
    Queries for a list of currently active stream handles. This is used by the
    calibration software.

  @apr_hdr_fields
    Opcode -- ASM_SVC_CMD_GET_STREAM_HANDLES

  @apr_msgpayload
    None.

  @return
    #ASM_SVC_CMDRSP_GET_STREAM_HANDLES

  @dependencies
    None.
*/
#define ASM_SVC_CMD_GET_STREAM_HANDLES                          0x00010C0B

/** @addtogroup asmsvc_resp_get_strm_handles
@{ */
/** Returns a list of stream handles that are currently active.

  @apr_hdr_fields
    Opcode -- ASM_SVC_CMDRSP_GET_STREAM_HANDLES
    @par
    Src_port -- Session ID 0, Stream ID 0

  @apr_msgpayload{asm_svc_cmdrsp_get_stream_handles_t}
    @table{weak__asm__svc__cmdrsp__get__stream__handles__t}
    Immediately following this structure are num_handles of uint32 stream
    handles, which are used in APR addresses. Set the bits for a stream handle
    as follows:
    - Bits 0 to 7 -- Stream ID. To set these bits, use #ASM_BIT_MASK_STREAM_ID
      and #ASM_SHIFT_STREAM_ID.
    - Bits 8 to 15 -- Session ID. To set these bits, use
      #ASM_BIT_MASK_SESSION_ID and #ASM_SHIFT_SESSION_ID.
    - Bits 16 to 23 -- Service ID (= ASM). To set these bits, use
      #ASM_BIT_MASK_SERVICE_ID and #ASM_SHIFT_SERVICE_ID.
    - Bits 24 to 31 -- Domain ID (= aDSP). To set these bits, use
      #ASM_BIT_MASK_DOMAIN_ID and #ASM_SHIFT_DOMAIN_ID.

  @return
    None.

  @dependencies
    None.
*/
#define ASM_SVC_CMDRSP_GET_STREAM_HANDLES                       0x00010C1B

/** Definition of the stream ID bitmask. */
#define ASM_BIT_MASK_STREAM_ID                                  (0x000000FFUL)

/** Definition of the stream ID shift value. */
#define ASM_SHIFT_STREAM_ID                                     0

/** Definition of the session ID bitmask. */
#define ASM_BIT_MASK_SESSION_ID                                 (0x0000FF00UL)

/** Definition of the session ID shift value. */
#define ASM_SHIFT_SESSION_ID                                    8

/** Definition of the service ID bitmask. */
#define ASM_BIT_MASK_SERVICE_ID                                 (0x00FF0000UL)

/** Definition of the service ID shift value. */
#define ASM_SHIFT_SERVICE_ID                                    16

/** Definition of the domain ID bitmask. */
#define ASM_BIT_MASK_DOMAIN_ID                                 (0xFF000000UL)

/** Definition of the domain ID shift value. */
#define ASM_SHIFT_DOMAIN_ID                                     24

/** @} */ /* end_addtogroup asmsvc_resp_get_strm_handles */

/* Payload structure for a get stream handles ACK. */
typedef struct asm_svc_cmdrsp_get_stream_handles_t asm_svc_cmdrsp_get_stream_handles_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_svc_cmdrsp_get_stream_handles_t
@{ */
/* Payload of the ASM_SVC_CMDRSP_GET_STREAM_HANDLES message, which
    returns a list of currently active stream handles.
*/
struct asm_svc_cmdrsp_get_stream_handles_t
{
    uint32_t                  num_handles;
    /**< Number of active stream handles. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_svc_cmdrsp_get_stream_handles_t */

/** @ingroup asmsvc_cmd_mem_map
    Commands the ASM to map multiple shared memory regions.
    All the mapped regions must be from the same memory pool.

  @apr_hdr_fields
    Opcode -- ASM_CMD_SHARED_MEM_MAP_REGIONS
    @par
    Dst_port -- 0000 (Session ID/Stream ID = 0/0)

  @apr_msgpayload{avs_cmd_shared_mem_map_regions_t}
    Immediately following this structure are num_regions of the
    <b>Map payload</b> (%avs_shared_map_region_payload_t).
    @tablens{weak__avs__cmd__shared__mem__map__regions__t}

  @mappayload{avs_shared_map_region_payload_t}
    @table{weak__avs__shared__map__region__payload__t}

  @return
    #ASM_CMDRSP_SHARED_MEM_MAP_REGIONS.

  @dependencies
    None.
*/
/* API_developer_note: A family APIs ASM_CMD_MEMORY_MAP, ASM_CMD_MEMORY_UNMAP,
   ASM_CMD_MEMORY_MAP_REGIONS, ASM_CMD_MEMORY_UNMAP_REGIONS are replaced by
   ASM_CMD_SHARED_MEM_MAP_REGIONS & ASM_CMD_SHARED_MEM_UNMAP_REGIONS in
   B family.
   Also, ASM_CMDRSP_SHARED_MEM_MAP_REGIONS is introduced to return the mmhandle
   to the clients. 
*/
#define ASM_CMD_SHARED_MEM_MAP_REGIONS               0x00010D92

/* ASM memory map regions command structure is the same as the
    AVS memory map regions command structure. */
typedef struct  avs_cmd_shared_mem_map_regions_t asm_cmd_shared_mem_map_regions_t;

/** @ingroup asmsvc_resp_mem_map
    Returns the memory map handle in response to an
    #ASM_CMD_SHARED_MEM_MAP_REGIONS command.

   @apr_hdr_fields
    Opcode -- ASM_CMD_SHARED_MEM_UNMAP_REGIONS
    @par
    Dst_port -- 0000 (Session ID/Stream ID = 0/0)

  @apr_msgpayload{avs_cmdrsp_shared_mem_map_regions_t}
    @table{weak__avs__cmdrsp__shared__mem__map__regions__t}

  @return
    None.

  @dependencies
    An #ASM_CMD_SHARED_MEM_MAP_REGIONS command must have been issued.
*/
#define ASM_CMDRSP_SHARED_MEM_MAP_REGIONS     0x00010D93

/* ASM memory map regions response payload is same as AVS memory map regions payload. */
typedef struct avs_cmdrsp_shared_mem_map_regions_t asm_cmdrsp_shared_mem_map_regions_t;

/** @ingroup asmsvc_cmd_mem_unmap
    Commands the ASM to unmap multiple shared memory regions that were
    previously mapped via #ASM_CMD_SHARED_MEM_MAP_REGIONS.

  @apr_hdr_fields
    Opcode -- ASM_CMD_SHARED_MEM_UNMAP_REGIONS
    @par
    Dst_port -- 0000 (Session ID/Stream ID = 0/0)

  @apr_msgpayload{avs_cmd_shared_mem_unmap_regions_t}
    @table{weak__avs__cmd__shared__mem__unmap__regions__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #ASM_CMD_SHARED_MEM_MAP_REGIONS command must have been
    issued.
*/
/* Q3 = Async Packet Router API Interface Spec for MDM9x15 (80-N1463-2) */
#define ASM_CMD_SHARED_MEM_UNMAP_REGIONS              0x00010D94

/* ASM memory unmap regions command structure is the same as the
    AVS memory unmap regions command structure. */
typedef struct avs_cmd_shared_mem_unmap_regions_t asm_cmd_shared_mem_unmap_regions_t;

/** @ingroup asmsvc_cmd_add_topos
    Defines custom topologies in the aDSP for use in POPP and POPreP. These
    topologies are created by specifying the topology IDs in the
    #ASM_STREAM_CMD_OPEN_READ_V2 command.

  @apr_hdr_fields
    Opcode -- ASM_CMD_ADD_TOPOLOGIES
    @par
    Dst_port -- 0

  @apr_msgpayload{asm_cmd_add_topologies_t}
    @table{weak__asm__cmd__add__topologies__t}

  @par Buffer format (audproc_custom_topologies_t)
    Immediately following this structure are num_topologies of the
    <b>Topology definitions</b> (%audproc_topology_definition_t) that are to
    be added to the aDSP.
    @tablens{weak__audproc__custom__topologies__t}
    Calculation of the buffer size:
    - Size of the module information structure = 4 + 4 + 16 = 24 bytes
    - Size of the topology definition structure = 4 + 4 + 16 * (size of the
      module information structure) = 392 bytes
    - Size of the buffer = 4 + num_topologies * 392 @newpage

  @par Topology definition (audproc_topology_definition_t)
    Immediately following this structure are num_modules of the Module
    information structure (%audproc_module_info_t).
    @tablens{weak__audproc__topology__definition__t}

  @par Module information (audproc_module_info_t)
    @table{weak__audproc__module__info__t}

  @detdesc 
    Custom topology definitions are stored internally by the aDSP. The
    definitions sent to the ASM are available for only the POPP and POPreP.
    @par
    This command must be sent before opening a session with the custom
    topologies. It can be sent multiple times to add new topologies; the ASM
    supports up to a total of 128 custom topologies. If a subsequent command
    redefines a previously defined topology ID, the previous topology
    definition is replaced with the new one. However, the changes take effect
    only when the next session is created. @newpage

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as input.

  @dependencies
    None.
*/
#define ASM_CMD_ADD_TOPOLOGIES                                0x00010DBE

/* The payload for the ASM_CMD_ADD_TOPOLOGIES command */
typedef struct asm_cmd_add_topologies_t asm_cmd_add_topologies_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_cmd_add_topologies_t
@{ */
/* Payload of the ASM_CMD_ADD_TOPOLOGIES command.
*/
struct asm_cmd_add_topologies_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit topology buffer address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit topology buffer address. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #ASM_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buffer_size;
    /**< Size in bytes of the valid data in the topology buffer. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_cmd_add_topologies_t */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* ADSP_ASM_SERVICE_COMMANDS_H_ */
