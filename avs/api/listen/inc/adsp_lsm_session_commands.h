/**
@file adsp_lsm_session_commands.h

@brief This file contains LSM session commands and events structures
definitions.
*/

/*==============================================================================
NOTE: The @brief description above does not appear in the PDF.
      Any descriptions that display in the PDF are located in the
      LSM_mainpage.dox file. Contact Tech Pubs for assistance.
==============================================================================*/

/*==============================================================================
Copyright (c) 2012, 2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.6.1/api/listen/inc/adsp_lsm_session_commands.h#3 $

  when         who      what, where, why
  --------     ---      -------------------------------------------------------
  12/09/2014   sw       (Tech Pubs) Edited Doxygen comments for 2.6.
  07/17/2014   Unni     Added LSM_SESSION_CMD_OPEN_TX_V2 working on topology_id
  05/12/2014   sw       (Tech Pubs) Edited Doxygen comments/markup for 2.4.
  11/07/2012   Sudhir   Initial version
==============================================================================*/

#ifndef _ADSP_LSM_SESSION_COMMANDS_H_
#define _ADSP_LSM_SESSION_COMMANDS_H_

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#include "mmdefs.h"

/** @addtogroup lsmsess_datatypes
@{ */

/** Maximum number of possible session IDs. IDs start from 1; 0 is reserved. */
#define LSM_MAX_SESSION_ID                        (8)

/** Maximum number of LSM sessions. */
#define LSM_MAX_NUM_SESSIONS                      LSM_MAX_SESSION_ID

/** @} */ /* end_addtogroup lsmsess_datatypes */

/** @addtogroup lsmsess_cmd_sh_mem_map_reg
@{ */
/** Commands the LSM session to map multiple shared memory regions. All the
    mapped regions must be from the same memory pool.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID

  @apr_msgpayload{lsm_session_cmd_shared_mem_map_regions_t}
    @tablens{weak__lsm__session__cmd__shared__mem__map__regions__t}

  @mappayload{lsm_session_shared_map_region_payload_t}
    @table{weak__lsm__session__shared__map__region__payload__t}

  @return
    #LSM_SESSION_CMDRSP_SHARED_MEM_MAP_REGIONS if successful.
    @par
    Error code for a failure (refer to @xhyperref{Q4,[Q4]}).

  @dependencies
    None.
*/
#define LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS    0x00012A7F

/** Enumeration for the shared memory, 8 byte addressable, 4 KB aligned
    pool ID. */
#define ADSP_MEMORY_MAP_SHMEM8_4K_POOL            3

/** @} */ /* end_addtogroup lsmsess_cmd_sh_mem_map_reg */

/* LSM Session shared memory map regions structure  */
typedef struct  lsm_session_cmd_shared_mem_map_regions_t
                lsm_session_cmd_shared_mem_map_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_shared_mem_map_regions_t
@{ */
/* Memory map regions command payload used by the
    LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS. 
    This structure allows clients to map multiple shared memory regions in a
    single command. */
/** Following this structure are num_regions of
    lsm_session_shared_map_region_payload_t.
*/
struct lsm_session_cmd_shared_mem_map_regions_t
{
    uint16_t                  mem_pool_id;
    /**< Type of memory on which this memory region is mapped.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         The memory pool ID implicitly defines the characteristics of the
         memory.
         Characteristics may include alignment type, permissions, etc.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, 8 byte addressable,
         and 4 KB aligned. */

    uint16_t                  num_regions;
    /**< Number of regions to map. 

         @values Any value greater than zero */

    uint32_t                  property_flag;
    /**< Configures one common property for all the regions in the payload. 

         @values 0x00000000 to 0x00000001

         Bit 0 indicates physical or virtual mapping:
         - 0 -- The shared memory address provided in
           lsm_session_shared_map_region_payload_t is a physical address.
           The shared memory must be mapped (hardware TLB entry), and a
           software entry must be added for internal bookkeeping.
         - 1 -- The shared memory address provided in
           lsm_session_shared_map_region_payload_t is a virtual address.
           The shared memory must not be mapped (because the hardware TLB entry
           is already available), but a software entry must be added for
           internal bookkeeping. \n @vertspace{2}
           This is useful if two services within the aDSP are communicating
           via the APR. They can directly communicate via the virtual
           address instead of the physical address. The virtual regions must
           be contiguous. In this case, num_regions must be 1.

         Bits 31 to 1 are reserved and must be set to zero. */
} 
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_shared_mem_map_regions_t */

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_shared_map_region_payload_t
@{ */
/* Map region payload used by the lsm_session_cmd_shared_mem_map_regions_t structure.
*/
struct lsm_session_shared_map_region_payload_t
{
    uint32_t                  shm_addr_lsw;
    /**< Lower 32 bits of the shared memory address of the memory region to
         map. The address must be 4 KB aligned.

         @values Any valid 32-bit address */

    uint32_t                  shm_addr_msw;
    /**< Upper 32 bits of the shared memory address of the memory region to
         map.

         The 64-bit number formed by shm_addr_lsw and shm_addr_msw word must be
         contiguous memory, and it must be 4 KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value.
         @tablebulletend */

    uint32_t                  mem_size_bytes;
    /**< Number of bytes in the region. 

         @values Multiples of 4 KB

         The aDSP always maps the regions as virtual contiguous memory, but
         the memory size must be in multiples of 4 KB to avoid gaps in the
         virtually contiguous mapped memory. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_shared_map_region_payload_t */

/** @ingroup lsmsess_rsp_sh_mem_map_reg
    Sent by the LSM session to the client processor in response to the
    successful processing of #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMDRSP_SHARED_MEM_MAP_REGIONS

  @apr_msgpayload{lsm_session_cmdrsp_shared_mem_map_regions_t}
    @table{weak__lsm__session__cmdrsp__shared__mem__map__regions__t}
      
  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS command must have
    been sent to receive this response from the LSM session.
*/
#define LSM_SESSION_CMDRSP_SHARED_MEM_MAP_REGIONS         0x00012A80

/* LSM Session shared memory map regions response structure  */
typedef struct  lsm_session_cmdrsp_shared_mem_map_regions_t
                lsm_session_cmdrsp_shared_mem_map_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmdrsp_shared_mem_map_regions_t
@{ */
/* Memory map command response payload used by the
    LSM_SESSION_CMDRSP_SHARED_MEM_MAP_REGIONS commands.

    This structure is  response to the memory mapping
    regions command. mem_map_handle must later be used by the
    client to unmap regions that are previously mapped.
*/
struct lsm_session_cmdrsp_shared_mem_map_regions_t
{
    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value

         The aDSP returns the memory map handle through
         #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS. This handle can be used as
         an abstract representation of the shared memory regions that are
         being mapped. If the command fails, a generic APR error response is
         returned to the client.
       
         The aDSP uses this handle to retrieve the shared memory attributes.

         #LSM_SESSION_CMD_SHARED_MEM_UNMAP_REGIONS uses this handle to unmap
         the mapped memory. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmdrsp_shared_mem_map_regions_t */

/** @ingroup lsmsess_cmd_sh_mem_unmap_reg
    Commands the LSM to unmap multiple shared memory regions
    that were previously mapped.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_SHARED_MEM_UNMAP_REGIONS
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID

  @apr_msgpayload{lsm_session_cmd_shared_mem_unmap_regions_t}
    @table{weak__lsm__session__cmd__shared__mem__unmap__regions__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS command must have
    been successfully processed.
*/
#define LSM_SESSION_CMD_SHARED_MEM_UNMAP_REGIONS          0x00012A81

/* LSM session shared memory unmap regions command structure */
typedef struct lsm_session_cmd_shared_mem_unmap_regions_t
               lsm_session_cmd_shared_mem_unmap_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_shared_mem_unmap_regions_t
@{ */
/* Memory unmap regions command payload used by the
    #LSM_SESSION_CMD_SHARED_MEM_UNMAP_REGIONS
    This structure allows clients to unmap multiple shared memory regions in
    a single command. 
*/
struct lsm_session_cmd_shared_mem_unmap_regions_t
{
    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value
       
         The aDSP returns this memory map handle through
         #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS.
       
         The aDSP uses this handle to retrieve the associated shared
         memory regions and unmap them. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_shared_mem_unmap_regions_t */

/** @ingroup lsmdepr_command
    Deprecated. Use #LSM_SESSION_CMD_OPEN_TX_V2.

    This command creates a dynamic LSM session for a listen application. The
    type of application depends on the application ID specified in the payload.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_OPEN_TX
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)
    
  @apr_msgpayload{lsm_session_cmd_open_tx_t}
    @table{weak__lsm__session__cmd__open__tx__t}

  @detdesc
    When creating an LSM session, the client processor must specify the session
    ID. Currently, up to #LSM_MAX_SESSION_ID groups are supported.
    @par
    After receiving this command, the LSM creates a dynamic service that
    handles the voice wakeup algorithm.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/ /* Q3 = Asynchronous Packet Router API (for MDM9x15 and Newer Devices)
           Interface Spec (80-N1463-2) */
#define LSM_SESSION_CMD_OPEN_TX               0x00012A82

/** @addtogroup lsmdepr_app_ids
@{ */
/** Deprecated. Use #LSM_MODULE_VOICE_WAKEUP_V1.

    Voice wakeup application ID.
*/
#define LSM_VOICE_WAKEUP_APP                  0x1

/** Deprecated. Use #LSM_MODULE_VOICE_WAKEUP_V2.

    Voice wakeup application ID for detecting multiple keywords and multiple
    users.
*/
#define LSM_VOICE_WAKEUP_APP_V2               0x2

/** Deprecated.

    Size of the range of application IDs for Hexagon customer algorithms and
    third party algorithms.
*/
#define LSM_APP_ID_RANGE_FOR_OPEN_DSP         0x10

/** Deprecated.

    Start of the range of application IDs for Hexagon customer algorithms and
    third party algorithms.  
*/
#define LSM_APP_ID_START_FOR_OPEN_DSP         0x1000

/** Deprecated.

    End of the range of application IDs for Hexagon Multimedia and
    third-party algorithms. @hideinitializer
*/
#define LSM_APP_ID_END_FOR_OPEN_DSP      ( LSM_APP_ID_START_FOR_OPEN_DSP + \
                                           LSM_APP_ID_RANGE_FOR_OPEN_DSP - 1 )

/** @} */ /* end_addtogroup lsmdepr_app_ids */

/* Deprecated. Use lsm_session_cmd_open_tx_v2_t instead.
   Payload format for an LSM open session command.
*/
typedef struct lsm_session_cmd_open_tx_t lsm_session_cmd_open_tx_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_open_tx_t
@{ */
/* Deprecated. Use lsm_session_cmd_open_tx_v2_t instead.    
   Payload of the command LSM_SESSION_CMD_OPEN_TX,
           which is used for opening LSM session.
*/
struct lsm_session_cmd_open_tx_t
{
    uint16_t app_id;
    /**< ID of the application the LSM is to create/open.
          
         @values
         - #LSM_VOICE_WAKEUP_APP
         - #LSM_VOICE_WAKEUP_APP_V2
         - Range of #LSM_APP_ID_START_FOR_OPEN_DSP to
           #LSM_APP_ID_END_FOR_OPEN_DSP (for Hexagon customers who want to use
           new IDs instead of an existing application ID). @tablebulletend */

    uint16_t reserved;
    /**< This field must be set to zero. */

    uint32_t sample_rate;
    /**< Sampling rate at which the voice wakeup application or target sound
         detection application runs.
     
         @values 16000 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_open_tx_t */

/** @addtogroup lsmsess_cmd_open_tx2
@{ */
/** Creates dynamic sessions in the Listen server.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_OPEN_TX_V2
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload{lsm_session_cmd_open_tx_v2_t}
    @table{weak__lsm__session__cmd__open__tx__v2__t}

  @description
    The session type depends on the collection of modules (graph) specified
    in the payload.
    @par
    When creating a session, the client processor must specify the session IDs.
    Currently, up to #LSM_MAX_SESSION_ID groups are supported.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/
#define LSM_SESSION_CMD_OPEN_TX_V2        0x00012A8B

/** Enumeration for setting the maximum number of modules in an open
    LSM session.
*/
#define LSM_MAX_MODULES_PER_GRAPH         8

/** @} */ /* end_addtogroup lsmsess_cmd_open_tx2 */

/* Payload format for an LSM open session command (v2). */
typedef struct lsm_session_cmd_open_tx_v2_t lsm_session_cmd_open_tx_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_open_tx_v2_t
@{ */
/*  payload of the command LSM_SESSION_CMD_OPEN_TX_V2,
           which is used for opening LSM session.
*/
struct lsm_session_cmd_open_tx_v2_t
{
    uint32_t topology_id;
    /**< Topology to use in this LSM session.

         @values See Chapter @xref{dox:ModParamIds} */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_addtogroup lsmsess_session_cmd_open_tx_v2 */

/** @ingroup lsmsess_cmd_set_params
    Sets one or more parameters in the LSM session. For supported module
    and parameter IDs, see Section&nbsp;@xref{dox:ModParamIds}.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_SET_PARAMS
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID

  @apr_msgpayload{lsm_session_cmd_set_params_t}
    @tablens{weak__lsm__session__cmd__set__params__t}

  @return
      APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    This command is accepted only after #LSM_SESSION_CMD_OPEN_TX_V2 is
    processed succesfully.
*/
#define LSM_SESSION_CMD_SET_PARAMS        0x00012A83

/* Payload format for a  Set Parameters command. */
typedef struct lsm_session_cmd_set_params_t lsm_session_cmd_set_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_set_params_t
@{ */
/* Payload of the LSM_SESSION_CMD_SET_PARAMS command, which allows
    one or more parameters to set on an open session. */
/** If the 64-bit data_payload_addr=NULL, a series of lsm_session_param_data_t
    structures immediately follow, whose total size is data_payload_size bytes.
*/
struct lsm_session_cmd_set_params_t
{

    uint32_t                  data_payload_size;
   /**< Actual size (in bytes) of the variable payload accompanying the message
        or in shared memory. This is used for parsing the parameter payload.

        @values > 0 */

    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the payload physical address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the payload physical address.

         The 64-bit number formed by data_payload_addr_lsw and
         data_payload_addr_msw must be aligned to a 32-byte boundary, be 4 KB
         aligned, and be in contiguous memory.

         @values
         - For in-band data, this field must be set to zero.
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 of this field must
           be set to zero. @tablebulletend */

    uint32_t                  mem_map_handle;
   /**< Unique identifier for an address.

        @values
        - NULL -- The message is in the payload (in-band).
        - Non-NULL -- The parameter data payload begins at the address
          specified by a pointer to the payload's physical address in shared
          memory (out-of-band).

        The aDSP returns this memory map handle through
        #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS.

        An optional field is available if parameter data is in-band:
        %lsm_session_param_data_t param_data[...].
        For detailed payload content, see <b>Parameter data variable
        payload</b> on the next page. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_set_params_t */

/* Payload format for  parameter data. */
typedef struct lsm_session_param_data_t lsm_session_param_data_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_param_data_t
@{ */
/* Payload of the session parameter data of the
    LSM_SESSION_CMD_SET_PARAMS command.*/
/** Immediately following this structure is the actual calibration data for the
    module_id/param_id pair.
*/
struct lsm_session_param_data_t
{
    uint32_t                  module_id;
   /**< ID of the module to configure.

        @values Valid module ID (See Section&nbsp;@xref{dox:ModParamIds}) */

    uint32_t                  param_id;
   /**< ID of a parameter that is supported by the module ID.

        @values Valid parameter ID (See Section&nbsp;@xref{dox:ModParamIds}) */

    uint16_t                  param_size;
   /**< Actual size of the data for the module_id/param_id pair. The size is a
        multiple of four bytes.

        @values > 0 */

    uint16_t                  reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_param_data_t */

/** @ingroup lsmsess_cmd_get_params
    Gets a configuration parameter from an LSM module.

    For in-band messages, the requested value is populated in the command
    response. For out-of-band messages the requested value is present in the
    shared memory location pointed to by the data payload address field.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_GET_PARAMS
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID

  @apr_msgpayload{lsm_session_cmd_get_params_t}
    @table{weak__lsm__session__cmd__get__params__t}

  @par Parameter data variable payload (lsm_session_param_data_t)
    @tablens{weak__lsm__session__param__data__t}

  @return
    #LSM_SESSION_CMDRSP_GET_PARAMS

  @dependencies
    This command is accepted only after #LSM_SESSION_CMD_OPEN_TX_V2 is
    processed successfully.
*/
#define LSM_SESSION_CMD_GET_PARAMS        0x00012A8D

/* Payload format for a  Get Parameter command. */
typedef struct lsm_session_cmd_get_params_t lsm_session_cmd_get_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_get_params_t
@{ */
/* Payload of the LSM_SESSION_CMD_GET_PARAMS command, which allows
   a single parameter to be queried form the module.
*/
struct lsm_session_cmd_get_params_t
{

    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the payload physical address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the payload physical address.

         The 64-bit number formed by data_payload_addr_lsw and
         data_payload_addr_msw must be aligned to a 32-byte boundary, be 4 KB
         aligned, and be contiguous in the aDSP's virtual memory space.

         @values
         - For in-band data, both the data_payload_addr_lsw and
           data_payload_addr_msw are set to zero.
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 of this field must
           be set to zero. @tablebulletend */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         @values
         - NULL -- The message is in the payload (in-band).
         - Non-NULL -- The parameter data payload begins at the address
           specified by a pointer to the payload's physical address in shared
           memory (out-of-band).

         The aDSP returns this memory map handle through
         #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS. */

    uint32_t                  module_id;
    /**< Valid ID of the module to query.
    
         @values See Section @xref{dox:ModParamIds} */

    uint32_t                  param_id;
    /**< Valid ID of the parameter to query.
    
         @values See Section @xref{dox:ModParamIds} */

    uint32_t                  param_max_size;
    /**< Maximum data size of the payload content. This value is a
         multiple of four bytes.

         @values > 0 bytes */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_get_params_t */


/** @ingroup lsmsess_rsp_get_params
    Returns parameter values in response to an #LSM_SESSION_CMD_GET_PARAMS
    command.

    For in-band messages, the lsm_session_param_data_t structure and actual
    content being queried follow the status field. For out-of-band messages,
    the actual payload is returned in the allocated out-of-band memory.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMDRSP_GET_PARAMS
    @par
    Src_port -- 1 to #LSM_MAX_SESSION_ID

  @apr_msgpayload{lsm_session_cmdrsp_get_params_t}
    Immediately following this structure is the <b>Acknowledgment parameter
    data variable payload</b>.
    @tablens{weak__lsm__session__cmdrsp__get__params__t}

  @par Acknowledgment parameter data variable payload (lsm_session_param_data_t)
    @tablens{weak__lsm__session__param__data__t}

  @return
    None.

  @dependencies
    None.
*/
#define LSM_SESSION_CMDRSP_GET_PARAMS                             0x00012A8E

/* Payload for LSM_SESSION_CMDRSP_GET_PARAMS. */
typedef struct lsm_session_cmdrsp_get_params_t lsm_session_cmdrsp_get_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmdrsp_get_params_t
@{ */
/* Payload of the LSM_SESSION_CMDRSP_GET_PARAMS message, which returns
    parameter values in response to an LSM_SESSION_CMD_GET_PARAMS command.
*/
struct lsm_session_cmdrsp_get_params_t
{
    uint32_t                  status;
    /**< Status message (error code).

         @values Refer to @xhyperref{Q4,[Q4]} */
    /* Q4 = Hexagon MM: Audio Voice Core Service API Interface Spec for 2.6
       (80-NF770-8) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmdrsp_get_params_t */

/** @ingroup lsmdepr_module
    Deprecated. 
    - Use #LSM_MODULE_VOICE_WAKEUP_V1 to replace LSM_MODULE_VOICE_WAKEUP plus
      #LSM_VOICE_WAKEUP_APP, which is also deprecated.
    - Use #LSM_MODULE_VOICE_WAKEUP_V2 to replace LSM_MODULE_VOICE_WAKEUP plus
      #LSM_VOICE_WAKEUP_APP_V2, which is also deprecated.

    This module sets the calibration data for the Voice Wakeup module.
    This module supports the following parameter IDs:
    - #LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD
    - #LSM_PARAM_ID_OPERATION_MODE
    - #LSM_PARAM_ID_GAIN
    - #LSM_PARAM_ID_CONNECT_TO_PORT
    - #LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY
    - #LSM_PARAM_ID_USER_DETECT_SENSITIVITY
    - #LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS
 
    To set the parameters, the client processor must:
    -# Send #LSM_SESSION_CMD_SET_PARAMS to the LSM session.
    -# Fill the module_id field with LSM_MODULE_VOICE_WAKEUP.
    -# Fill the param_id field with the respective parameter IDs as listed
       above.
 
    @note1hang LSM_SESSION_CMD_SET_PARAMS is accepted only after a valid dynamic
               session is created.

    @apr_hdr_fields
    Opcode -- LSM_MODULE_VOICE_WAKEUP
*/
#define LSM_MODULE_VOICE_WAKEUP           0x00012C00

/** @ingroup lsmmodule_voice_wakeup1
    ID of the Voice Wakeup V1 module, which configures single keyword and single
    user calibration data.
    
    This module supports the following parameter IDs:
    - #LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD
    - #LSM_PARAM_ID_OPERATION_MODE
    - #LSM_PARAM_ID_GAIN
    - #LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY
    - #LSM_PARAM_ID_USER_DETECT_SENSITIVITY

    This module supports the #LSM_SESSION_EVENT_DETECTION_STATUS event.
*/
#define LSM_MODULE_VOICE_WAKEUP_V1        0x00012C0C

/** @ingroup lsmmodule_voice_wakeup2
    ID of the Voice Wakeup V2 module, which configures multiple
    keyword and multiple user calibration data.

    This module supports the following parameter IDs:
    - #LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD
    - #LSM_PARAM_ID_OPERATION_MODE
    - #LSM_PARAM_ID_GAIN
    - #LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS

    This module supports the #LSM_SESSION_EVENT_DETECTION_STATUS_V2 event.
*/
#define LSM_MODULE_VOICE_WAKEUP_V2        0x00012C0D

/** @ingroup lsmmodule_framework
    ID of the Framework module, which configures calibration data for an AFE
    port.

    This module supports the following parameter ID:
    - #LSM_PARAM_ID_CONNECT_TO_PORT

    This module supports the #LSM_SESSION_EVENT_DETECTION_STATUS_V2 event.
*/
#define LSM_MODULE_FRAMEWORK             0x00012C0E

/** @addtogroup lsmmodule_common_params
@{ */
/** ID of the parameter used to set the beginning-of-speech and end-of-speech
    thresholds.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD
    
    @msgpayload{lsm_param_id_epd_threshold_t}
    @table{weak__lsm__param__id__epd__threshold__t}
*/
#define LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD      0x00012C01

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility).
 */
#define LSM_API_VERSION_EPD_THRESHOLD               0x1

/** @} */ /* end_addtogroup lsmmodule_common_params */

/* Payload of the LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD command. */
typedef struct lsm_param_id_epd_threshold_t lsm_param_id_epd_threshold_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_epd_threshold_t
@{ */
/* Payload of the LSM_PARAM_ID_ENDPOINT_DETECT_THRESHOLD parameter, which
    sets the beginning of speech and end of speech thresholds .
*/
struct lsm_param_id_epd_threshold_t
{
    uint32_t minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_EPD_THRESHOLD */

    int32_t epd_begin_threshold;
    /**< Threshold for the beginning of speech.

         @values
         - Range of values (in Q20 format)
         - Default -- 0x02710000 @tablebulletend */

    int32_t epd_end_threshold;
    /**< Threshold for the end of speech.

         @values
         - Range of values (in Q20 format)
         - Default -- 0xFA9B62B7 @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_epd_threshold_t */

/** @addtogroup lsmmodule_common_params
@{ */
/** ID of the parameter used to set different operation modes for the Voice
    Wakeup module.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_OPERATION_MODE

    @msgpayload{lsm_param_id_operation_mode_t}
    @table{weak__lsm__param__id__operation__mode__t}
*/
#define LSM_PARAM_ID_OPERATION_MODE                0x00012C02

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility). @newpage
 */
#define LSM_API_VERSION_OPERATION_MODE             0x1

/** @} */ /* end_addtogroup lsmmodule_common_params */

/* Payload of the LSM_PARAM_ID_OPERATION_MODE command. */
typedef struct lsm_param_id_operation_mode_t lsm_param_id_operation_mode_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_operation_mode_t
@{ */
/* Payload of the LSM_PARAM_ID_OPERATION_MODE parameter, which sets the
    different types of operation mode of voice wakeup block
*/
struct lsm_param_id_operation_mode_t
{
    uint32_t                  minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_OPERATION_MODE */

    uint16_t mode;
    /**< Flags that configure the Voice Wakeup module to run in different
         modes.

         @values{for bit 0}
         - 0 -- Keyword Detection mode is disabled
         - 1 -- Keyword Detection mode is enabled (Default)
    
         @values{for bit 1}
         This bit is applicable only if bit 0 is set to 1. Otherwise this
         value is ignored.    
         - 0 -- User Verification mode is disabled
         - 1 -- User Verification mode is enabled
    
        @values{for bit 2}
        - 0 -- Events are sent to the HLOS only when detection is
          successful
        - 1 -- Events are sent to the HLOS regardless of success or failure
        @tablebulletend */

    uint16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_operation_mode_t */

/** @addtogroup lsmmodule_common_params
@{ */
/** ID of the parameter used to set the gain that is applied to the data
    coming from the software Microphone Activity Detection (MAD) thread.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_GAIN
    
    @msgpayload{lsm_param_id_gain_t}
    @table{weak__lsm__param__id__gain__t}
*/
#define LSM_PARAM_ID_GAIN                     0x00012C03

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility). @newpage
 */
#define LSM_API_VERSION_GAIN                  0x1

/** @} */ /* end_addtogroup lsmmodule_common_params */

/* Payload of the LSM_PARAM_ID_GAIN command. */
typedef struct lsm_param_id_gain_t lsm_param_id_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_gain_t
@{ */
/* Payload of the LSM_PARAM_ID_GAIN parameter.
*/
struct lsm_param_id_gain_t
{
    uint32_t                  minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_GAIN  */

    int16_t gain;
    /**< Gain applied to the data.

         @values
         - Range of values (in Q8 format)
         - Default -- 0x100 (unity gain) @tablebulletend */

    uint16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_gain_t */

/** @addtogroup lsmmodule_framework
@{ */
/** ID of the parameter used by #LSM_MODULE_FRAMEWORK to connect the LSM
    session to the AFE port.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_CONNECT_TO_PORT

    @msgpayload{lsm_param_id_connect_port_t}
    @table{weak__lsm__param__id__connect__port__t}
*/
#define LSM_PARAM_ID_CONNECT_TO_PORT          0x00012C04

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility). @newpage
 */
#define LSM_API_VERSION_CONNECT_TO_PORT       0x1

/** @} */ /* end_addtogroup lsmmodule_framework */

/* Payload of the LSM_PARAM_ID_CONNECT_TO_PORT command. */
typedef struct lsm_param_id_connect_port_t lsm_param_id_connect_port_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_connect_port_t
@{ */
/* Payload of the LSM_PARAM_ID_CONNECT_TO_PORT parameter.
*/
struct lsm_param_id_connect_port_t
{
    uint32_t                  minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_CONNECT_TO_PORT */

    uint16_t port_id;
    /**< ID of the AFE port from which the Voice Wakeup module receives the
         data.

         @values Refer to @xhyperref{Q5,[Q5]} */
    /* Q3 = Hexagon Multimedia: AFE API Interface Spec for 2.6 (80-NF770-3) */

    uint16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_connect_port_t */

/** @addtogroup lsmmodule_voice_wakeup1
@{ */
/** ID of the parameter used by #LSM_MODULE_VOICE_WAKEUP_V1 to set the keyword
    sensitivity.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY

    @msgpayload{lsm_param_id_keyword_det_sensitivity_t}
    @table{weak__lsm__param__id__keyword__det__sensitivity__t}
*/
#define LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY             0x00012C05

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility).
 */
#define LSM_API_VERSION_KEYWORD_DETECT_SENSITIVITY          0x1

/** @} */ /* end_addtogroup lsmmodule_voice_wakeup1 */

/* Payload of the LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY command. */
typedef struct lsm_param_id_keyword_det_sensitivity_t 
               lsm_param_id_keyword_det_sensitivity_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_keyword_det_sensitivity_t
@{ */
/* Payload of the LSM_PARAM_ID_KEYWORD_DETECT_SENSITIVITY parameter
 */
struct lsm_param_id_keyword_det_sensitivity_t
{
    uint32_t                  minor_version;
    /**< Minor version used for tracking the version of this parameter ID. 
     
         @values #LSM_API_VERSION_KEYWORD_DETECT_SENSITIVITY */

    int16_t keyword_sensitivity;
    /**< Scale factor used to change the keyword confidence thresholds.
     
         @values 0 to 100 percent
         - If the value is small, the application provides a low miss rate
           and more false alarms.
         - If the value is high, the application provides a high miss rate
           and fewer false alarms. @tablebulletend */

    uint16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_keyword_det_sensitivity_t */

/** @addtogroup lsmmodule_voice_wakeup1
@{ */
/** ID of the parameter used by #LSM_MODULE_VOICE_WAKEUP_V1 to set the user
    sensitivity.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_USER_DETECT_SENSITIVITY

    @msgpayload{lsm_param_id_user_det_sensitivity_t}
    @table{weak__lsm__param__id__user__det__sensitivity__t}
*/ 
#define LSM_PARAM_ID_USER_DETECT_SENSITIVITY              0x00012C06

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility). @newpage
 */
#define LSM_API_VERSION_USER_DETECT_SENSITIVITY           0x1

/** @} */ /* end_addtogroup lsmmodule_voice_wakeup1 */

/* Payload of the LSM_PARAM_ID_USER_DETECT_SENSITIVITY command. */
typedef struct lsm_param_id_user_det_sensitivity_t lsm_param_id_user_det_sensitivity_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_user_det_sensitivity_t
@{ */
/* Payload of the LSM_PARAM_ID_USER_DETECT_SENSITIVITY parameter
*/
struct lsm_param_id_user_det_sensitivity_t
{
    uint32_t                  minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_USER_DETECT_SENSITIVITY */

    int16_t user_sensitivity;
    /**< Scale factor used to change the user confidence thresholds.

         @values 0 to 100 percent
         - If the value is small, the application provides a low miss rate
           and more false alarms.
         - If the value is high, the application provides a high miss rate
           and fewer false alarms. @tablebulletend */

    uint16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_user_det_sensitivity_t */

/** @ingroup lsmmodule_voice_wakeup2
    ID of the parameter used by #LSM_MODULE_VOICE_WAKEUP_V2 to set the minimum
    confidence levels for registered keyword models and active user models.

    @par Prerequisite
    The LSM session must be in the Init state.
   
    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS

    @msgpayload{lsm_param_id_min_confidence_levels_t}
    @tablens{weak__lsm__param__id__min__confidence__levels__t}
*/ 
#define LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS                0x00012C07

/* Payload of the LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS command. */
typedef struct lsm_param_id_min_confidence_levels_t
               lsm_param_id_min_confidence_levels_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_min_confidence_levels_t
@{ */
/* Payload of the LSM_PARAM_ID_MIN_CONFIDENCE_LEVELS parameter */
/** Immediately following this structure are num_active_models bytes of data.
    The HLOS must ensure that enough padding bytes are added while sending
    this payload. The entire payload size must be a multiple of four bytes.
*/
struct lsm_param_id_min_confidence_levels_t
{
    uint8_t                  num_active_models;
    /**< Sum of all keyword models plus the active user models. The active
         user models are the users registered for each target keyword.

         @values 1 to 20
         - If the value is 1, there is one uint8 sensitivity value
         - If the value is 2, there are two uint8 sensitivity values
         - And so on @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_min_confidence_levels_t */

/** @addtogroup lsmmodule_common_params
@{ */
/** ID of the parameter used to register the sound model with a Voice
    Wakeup module.

    A sound model is interpreted by a module that supports this parameter.
    The sound model contains the unique sound characteristics or signatures
    used by the algorithm hosted in the module. 
    
    This parameter does not have a payload. The #LSM_SESSION_CMD_SET_PARAMS
    command specifies the following:
    - When the sound model is in-band, the model follows the param_id field
      in the payload, and the data is 32-bit aligned.
    - When the sound model is sent as an out-of-band payload, the model is
      in the out-of-band payload pointed to by #LSM_SESSION_CMD_SET_PARAMS, and
      the data is 32-byte aligned.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_REGISTER_SOUND_MODEL
*/
#define LSM_PARAM_ID_REGISTER_SOUND_MODEL                0x00012C14

/** ID of the parameter used to deregister the sound model from the
    Voice Wakeup module.

    This parameter is useful if the client processor wants to replace an already
    registered sound model or free resources without closing a session.

    @note1hang If the client closes a session, all registered models and other
               resources claimed by the module are freed implicitly.

    @par Prerequisite
    The LSM session must be in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_DEREGISTER_SOUND_MODEL @newpage
*/
#define LSM_PARAM_ID_DEREGISTER_SOUND_MODEL              0x00012C15

/** @} */ /* end_addtogroup lsmmodule_common_params */

/** @ingroup lsmsess_cmd_reg_sound_model
    Registers sound model data with a Voice Wakeup module in the LSM session.
    
  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_REGISTER_SOUND_MODEL
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload{lsm_session_cmd_register_sound_model_t}
    @table{weak__lsm__session__cmd__register__sound__model__t}

  @detdesc
    This command is accepted only when the LSM session is in the Init state.
    @par
    When creating a session, the client processor must specify the session IDs.
    Currently, up to #LSM_MAX_SESSION_ID groups are supported.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}). @newpage

  @dependencies
    This command can only be sent after #LSM_SESSION_CMD_OPEN_TX_V2 has been
    processed succesfully.
    @par
    Before sending this command, sound model memory must be mapped using
    #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS.
*/
#define LSM_SESSION_CMD_REGISTER_SOUND_MODEL              0x00012A84

/* Payload format for an LSM register sound model command. */
typedef struct lsm_session_cmd_register_sound_model_t
               lsm_session_cmd_register_sound_model_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_cmd_register_sound_model_t
@{ */
/* Payload of LSM_SESSION_CMD_REGISTER_SOUND_MODEL command
*/
struct lsm_session_cmd_register_sound_model_t
{
    uint32_t model_size;
    /**< Size (in bytes) of the registering sound model. */

    uint32_t model_addr_lsw;
    /**< Lower 32 bits of the 64-bit parameter data payload address. */

    uint32_t model_addr_msw;
    /**< Upper 32 bits of the 64-bit parameter data payload address. 
    
         The 64-bit number formed by model_addr_lsw and model_addr_msw word
         must be contiguous memory, and it must be 4 KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value.
         @tablebulletend */

    uint32_t mem_map_handle; 
    /**< Unique identifier for an address.

         @values Any 32-bit value

         The aDSP returns this memory map handle through
         #LSM_SESSION_CMD_SHARED_MEM_MAP_REGIONS. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_cmd_register_sound_model_t */

/** @ingroup lsmsess_cmd_dereg_sound_model
    Deregisters sound model data from the LSM session.
   
  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_DEREGISTER_SOUND_MODEL
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload
    None.

  @detdesc
    This command is accepted only when the LSM session is in the Init state.
    If the session is in the Active state, it must be transitioned to the Init
    state before sending this deregister command.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session ID must be for a valid opened session.
    @par
    The sound model must have been registered with the session.
*/
#define LSM_SESSION_CMD_DEREGISTER_SOUND_MODEL            0x00012A85

/** @ingroup lsmsess_cmd_start
    Starts a specified LSM session.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_START
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload
    None.

  @detdesc
    This command is accepted ony when the session is in the Init state.
    After processing this command suucesfully, the session transitions to the
    Active state.
    @par
    The LSM session processes data only after receiving this command.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session ID must be for a valid opened session.
*/
#define LSM_SESSION_CMD_START                             0x00012A86

/** @ingroup lsmsess_cmd_stop
    Stops a specified LSM session.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_STOP
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload
    None.

  @detdesc
    The session sends this command to the voice wakeup thread and disables
    data processing. 
    After processing this command, the session transitions from the Stop state
    to the Init state.
    @par
    This command is helpful if the application processor stops voice wakeup
    processing due to concurrency restrictions. To resume voice wakeup
    processing, the client processor resends #LSM_SESSION_CMD_START.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session ID must be for a valid opened session.
*/
#define LSM_SESSION_CMD_STOP                              0x00012A87

/** @ingroup lsmsess_cmd_close
    Stops and closes a specified LSM session, tearing down all dynamic threads
    that were created through #LSM_SESSION_CMD_OPEN_TX_V2.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_CLOSE
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session ID must be for a valid opened LSM session.
*/
#define LSM_SESSION_CMD_CLOSE                             0x00012A88

/** @ingroup lsmsess_cmd_eob
    Stops look ahead buffering in a specified LSM session. Any data buffers
    held by the aDSP are returned to the client.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_CMD_EOB
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)
     
  @apr_msgpayload
    None.
     
  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The session ID must be a valid active session.
*/
#define LSM_SESSION_CMD_EOB                               0x00012A89

/** @addtogroup lsmsess_evt_detect_status
@{ */
/** Event sent by the aDSP to the HLOS when a registered keyword is detected.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_EVENT_DETECTION_STATUS
    @par
    Dst_port -- 1 to #LSM_MAX_SESSION_ID (0 is reserved)

  @apr_msgpayload{lsm_session_event_detection_status_t}
    @tablens{weak__lsm__session__event__detection__status__t}
    
  @detdesc
    The listen application sends the event to the client processor after
    processing the data.
    @par
    The aDSP sends the detection_status in the APR payload of this event.
    @par
    If bit 2 of the mode field is set to 1 in #LSM_PARAM_ID_OPERATION_MODE,
    events are sent to the HLOS regardless of success or failure.

  @return
    None.

  @dependencies
    None.
*/
#define LSM_SESSION_EVENT_DETECTION_STATUS                0x00012B00

/** @cond OEM_only */
/* Status (None) when a Voice Wakeup module is processing data, is
    initialized, or is reinitialised. This status definition is internal and
    is not sent to the client. */
#define LSM_VOICE_WAKEUP_STATUS_NONE                      0x0

/* Status (Running) when a Voice Wakeup module is processing data. */
#define LSM_VOICE_WAKEUP_STATUS_RUNNING                   0x1

/** Status (Detected) when a Voice Wakeup module detects a keyword or user. */
#define LSM_VOICE_WAKEUP_STATUS_DETECTED                  0x2

/* Status (End Speech) when a Voice Wakeup module detects end of speech. */
#define LSM_VOICE_WAKEUP_STATUS_END_SPEECH                0x3

/** Status (Rejected) when a Voice Wakeup module rejects a keyword or user. */
#define LSM_VOICE_WAKEUP_STATUS_REJECTED                  0x4

/** Status (Discovery) when a Voice Wakeup module is doing keyword end
    discovery. This status definition is internal and is not sent to the
    client. */
#define LSM_VOICE_WAKEUP_STATUS_DISCOVERY                 0x5
/** @endcond */

/** Status (Detected) when a Voice Wakeup module detects an event. */
#define LSM_DETECTION_STATUS_DETECTED       LSM_VOICE_WAKEUP_STATUS_DETECTED

/** Status (Rejected) when a Voice Wakeup module rejects an event. */
#define LSM_DETECTION_STATUS_REJECTED       LSM_VOICE_WAKEUP_STATUS_REJECTED

/** @cond OEM_only */
/** Status (Discovery) when a Voice Wakeup module is in Discovery mode.
    This status definition is internal and is not sent to the client. */
#define LSM_DETECTION_STATUS_DISCOVERY      LSM_VOICE_WAKEUP_STATUS_DISCOVERY
/** @endcond */

/** @} */ /* end_addtogroup lsmsess_evt_detect_status */

/* Payload format for an LSM session event detection. */
typedef struct lsm_session_event_detection_status_t
               lsm_session_event_detection_status_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_event_detection_status_t
@{ */
/* payload of LSM_SESSION_EVENT_DETECTION_STATUS command. */
/** Following this structure is a parameter data payload of size payload_size.
*/
struct lsm_session_event_detection_status_t
{
    uint16_t  detection_status;
    /**< Status sent by the Voice Wakeup module to the client.
     
         @values
         - #LSM_DETECTION_STATUS_DETECTED
         - #LSM_DETECTION_STATUS_REJECTED @tablebulletend */

    uint16_t  payload_size;
    /**< Actual size (in bytes) of the parameter data payload that follows
         this structure. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_event_detection_status_t */

/** @ingroup lsmsess_evt_detect_status2
    Event sent by the aDSP to the HLOS processor when a registered keyword
    is detected.

  @apr_hdr_fields
    Opcode -- LSM_SESSION_EVENT_DETECTION_STATUS_V2

  @apr_msgpayload{lsm_session_event_detection_status_v2_t}
    @tablens{weak__lsm__session__event__detection__status__v2__t}

  @detdesc
    The listen application sends the event to the client processor after
    processing the data.
    @par
    The aDSP sends the detection_status in the APR payload of this event.
    @par
    If bit 2 of the mode field is set to 1 in #LSM_PARAM_ID_OPERATION_MODE,
    events are sent to the HLOS regardless of success or failure.

  @return
    None.

  @dependencies
    None. @newpage
*/
#define LSM_SESSION_EVENT_DETECTION_STATUS_V2             0x00012B01

/* Payload format for an LSM session event detection. */
typedef struct lsm_session_event_detection_status_v2_t
               lsm_session_event_detection_status_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_session_event_detection_status_v2_t
@{ */
/* payload of LSM_SESSION_EVENT_DETECTION_STATUS_V2 command. */
/** Following this structure is a parameter data payload of size payload_size.
*/
struct lsm_session_event_detection_status_v2_t
{
    uint8_t  detection_status;
    /**< Status sent by the Voice Wakeup module to the client.
     
         @values
         - #LSM_DETECTION_STATUS_DETECTED
         - #LSM_DETECTION_STATUS_REJECTED

         @note1hang LSM_VOICE_WAKEUP_STATUS_END_SPEECH is a legacy status used
         in VOICE_WAKEUP_V1. It is not used from VOICE_WAKEUP_V2 on. */

    uint8_t  payload_size;
    /**< Actual size (in bytes) of the parameter data payload that follows
         this structure. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_session_event_detection_status_v2_t */

/** @ingroup lsmmodule_lab
    ID of the Look Ahead Buffering (LAB) module, which configures LAB
    parameters. 
    This module supports the following parameter IDs:
    - #LSM_PARAM_ID_ENABLE
    - #LSM_PARAM_ID_LAB_CONFIG
    
    To set the parameters, the client processor must send
    #LSM_SESSION_CMD_SET_PARAMS to the session and fill the module_id field
    with LSM_MODULE_LAB, and the param_id field with the respective parameter
    IDs.
 
    The LSM_SESSION_CMD_SET_PARAMS command is accepted only when the session is
    in the Init state.

    @apr_hdr_fields
    Opcode -- LSM_MODULE_LAB
*/
#define LSM_MODULE_LAB                          0x00012C08

/** @ingroup lsmmodule_lab
    ID of the parameter used to enable or disable the LAB module in the LSM
    session.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_ENABLE

    @msgpayload{lsm_param_id_enable_t}
    @table{weak__lsm__param__id__enable__t}
*/ 
#define LSM_PARAM_ID_ENABLE                    0x00012C09

/* Payload of the LSM_PARAM_ID_ENABLE command. */
typedef struct lsm_param_id_enable_t lsm_param_id_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_enable_t
@{ */
/* Payload of the LSM_PARAM_ID_ENABLE parameter
*/
struct lsm_param_id_enable_t
{
    uint16_t   enable;
   /**< Specifies whether a module is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

    uint16_t   reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_enable_t */

/** @addtogroup lsmmodule_lab
@{ */
/** ID of the parameter used by #LSM_MODULE_LAB to set look ahead buffering
    properties to determine the size of an internal circular buffer based on
    the application response time.

    @apr_hdr_fields
    Opcode -- LSM_PARAM_ID_LAB_CONFIG

    @msgpayload{lsm_param_id_lab_config_v1_t}
    @table{weak__lsm__param__id__lab__config__v1__t}
*/ 
#define LSM_PARAM_ID_LAB_CONFIG                  0x00012C0A

/** Version information used to handle future additions to the configuration
    interface (for backward compatibility).
 */
#define LSM_API_VERSION_LAB_CONFIG                                  0x1

/** @} */ /* end_addtogroup lsmmodule_lab */

/* Payload of the LSM_PARAM_ID_LAB_CONFIG command. */
typedef struct lsm_param_id_lab_config_v1_t lsm_param_id_lab_config_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_lsm_param_id_lab_config_v1_t
@{ */
/* Payload of the LSM_PARAM_ID_LAB_CONFIG parameter
*/
struct lsm_param_id_lab_config_v1_t
{
    uint32_t   minor_version;
    /**< Minor version used for tracking the version of this parameter ID.

         @values #LSM_API_VERSION_LAB_CONFIG */

    uint32_t  wake_up_latency_ms;
    /**< Time (in milliseconds) taken by the client processor to respond to a
         keyword detection event and set up the data path for look ahead
         buffering.

         @values > 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_lsm_param_id_lab_config_v1_t */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_LSM_SESSION_COMMANDS_H_ */
