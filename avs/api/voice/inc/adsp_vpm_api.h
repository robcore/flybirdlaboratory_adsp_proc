#ifndef __ADSP_VPM_API_H__
#define __ADSP_VPM_API_H__

/**
  @file adsp_vpm_api.h
  @brief This file contains API definitions for the Voice Processing Manager 
  (VPM).
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Voice_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
  Copyright (c) 2010, 2012-2014 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/
/*===========================================================================
                        EDIT HISTORY FOR MODULE
  
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4.
02/25/13   sw      (Tech Pubs) Updated Doxygen for 2.0 internal draft.
02/27/12   sw      (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
10/11/10   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
12/09/10    dp     Update VPM version, since VFR API changed (common VSM/VPM) 
===========================================================================*/

#include "mmdefs.h"
#include "adsp_vcmn_api.h"

/** @ingroup vpm_version
    Version of the aDPS VPM module.
*/
#define ADSP_VPM_VERSION    0x00070005


/*============================================================================
   VPM 8x60 ISOD commands
============================================================================*/

/** @ingroup vpm_cmd_start_session
    Starts any existing Tx/Rx path on a specified device session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_START_SESSION
    @par
    Dst_port -- Handle to the session

  @msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created.
*/
/* Q3 = Async Packet Router API (MDM9x15 and Newer Devices) Interface Spec
        (80-N1463-2)*/
#define VPM_CMD_START_SESSION ( 0x00011002 )

/** @ingroup vpm_cmd_stop_session
    Stops any existing Tx/Rx path on a specified device session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_STOP_SESSION
    @par
    Dst_port -- Handle to the session

  @msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created.
*/
#define VPM_CMD_STOP_SESSION ( 0x00011003 )

/** @ingroup vpm_cmd_destroy_session
    Destroys any existing Tx/Rx paths on a specified device session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_DESTROY_SESSION
    @par
    Dst_port -- Handle to the session

  @msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created, and it must be in the Stop state.
*/
#define VPM_CMD_DESTROY_SESSION ( 0x00011004 )

/** @cond OEM_only */
/** @addtogroup vpm_cmd_config_tx_dtmf
@{ */
/** Configures DTMF detection in the Tx direction.

  @apr_hdr_fields
    Opcode -- VPM_CMD_SET_TX_DTMF_DETECTION
    @par
    Dst_port -- Handle of the client that enabled DTMF detection

  @apr_msgpayload{vpm_set_tx_dtmf_detection_t}
    @table{weak__vpm__set__tx__dtmf__detection__t}

  @description
    The DTMF status is sent to the client that requested detection via
    #VPM_EVT_TX_DTMF_DETECTED. Only one client can request Tx DTMF detection on
    a given stream at a given time. If another client requests Tx DTMF
    detection while the previous client's Tx DTMF detection is still active,
    the request fails.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created.
*/
#define VPM_CMD_SET_TX_DTMF_DETECTION  ( 0x00011033 )

/** Valid values for configuring DTMF detection on the Tx path.
*/
typedef enum
{
   VPM_TX_DTMF_DETECTION_DISABLE = 0, /**< Tx DTMF detection is disabled. */
   VPM_TX_DTMF_DETECTION_ENABLE       /**< Tx DTMF detection is enabled. */
}vpm_set_tx_dtmf_detection_mode_t;

/** @} */ /* end_addtogroup vpm_cmd_config_tx_dtmf */

/* Used by the structure that allows the client to enable or disable 
  DTMF detection. */
typedef struct vpm_set_tx_dtmf_detection_t vpm_set_tx_dtmf_detection_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_set_tx_dtmf_detection_t
@{ */
/* Payload of the VPM_CMD_SET_TX_DTMF_DETECTION command, which allows
    the client to enable DTMF detection on the Tx path.
*/
struct vpm_set_tx_dtmf_detection_t
{
   uint32_t enable;
   /**< Specifies whether Tx DTMF detection is enabled.

        @values
        - #VPM_TX_DTMF_DETECTION_DISABLE
        - #VPM_TX_DTMF_DETECTION_ENABLE @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_set_tx_dtmf_detection_t */
/** @endcond */

/** @cond OEM_only */
/** @ingroup vpm_evt_tx_dtmf_detected
    Event sent by the stream to the client that enabled Tx DTMF detection
    whenever DTMF has been detected on the Tx path.

  @apr_hdr_fields
    Opcode -- VPM_EVT_TX_DTMF_DETECTED
    @par
    Dst_port -- Handle of the client that enabled it

  @apr_msgpayload{vpm_tx_dtmf_detected_t}
    @table{weak__vpm__tx__dtmf__detected__t}

  @description
    The DTMF detection feature can only be used to detect DTMF frequencies as
    listed in ITU-T Recommendation Q.23, Section 6 (refer to
    @xhyperref{S1,[S1]}) and not to arbitrary frequencies. Therefore, the
    possible values for low and high frequencies are listed in
    %vpm_tx_dtmf_detected_t.

  @return
    None.

  @dependencies
    A valid session must have been created.
    @par
    Tx DTMF detection must be enabled for these events to be generated.
 */
#define VPM_EVT_TX_DTMF_DETECTED ( 0x00011034 )

/* Used by the structure that sends a DTMF detection tone status to the 
  client that enabled it. */
typedef struct vpm_tx_dtmf_detected_t vpm_tx_dtmf_detected_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_tx_dtmf_detected_t
@{ */
/* Payload of the VPM_EVT_TX_DTMF_DETECTED event, which sends a DTMF
    detection tone status to the client that enabled it.
*/
struct vpm_tx_dtmf_detected_t
{
   uint16_t low_freq;
   /**< Low frequency detected in the DTMF tone.

        @values 697, 770, 852, 941 Hz */

   uint16_t high_freq;
   /**< High frequency detected in the DTMF tone.

        @values 1209, 1336, 1477, 1633 Hz */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_tx_dtmf_detected_t */
/** @endcond */

/** @addtogroup vpm_cmd_create_session
@{ */
/** Creates a paired Tx/Rx device leg of a voice call.

  @apr_hdr_fields
    Opcode -- VPM_CMD_CREATE_SESSION_V2

  @apr_msgpayload{vpm_create_session_v2_t}
    @table{weak__vpm__create__session__v2__t}

  @description
    A voice processing session is a paired Tx/Rx session with postprocessing
    blocks. If the Tx or Rx port is set to NO_INTERFACE, the corresponding
    module is not created.

  @return
    @keep{3} APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    - Includes the handle to the paired Tx and Rx
    - Is NULL if there is an error

  @dependencies
    This is the first command before starting a voice processing session.
*/
#define VPM_CMD_CREATE_SESSION_V2 ( 0x00011037 )

/** Topology ID for Tx pass through. */
#define VPM_TX_NONE       ( 0x00010F70 )

/** @cond OEM_only */
/** @xreflabel{hdr:ParamVpmTxSmEcnsTopo}
    Topology ID for Tx single-mic ECNS.	@newpage */
#define VPM_TX_SM_ECNS    ( 0x00010F71 )

/** @xreflabel{hdr:ParamVpmTxDmFluenceTopo}
    Topology ID for Tx dual-mic Fluence@tm. */
#define VPM_TX_DM_FLUENCE ( 0x00010F72 )

/** @xreflabel{hdr:ParamVpmTxSmFluenceV5Topo}
    Topology ID for Tx single-mic Fluence V5. */
#define VPM_TX_SM_FLUENCEV5 ( 0x00010F73 )

/** @xreflabel{hdr:ParamVpmTxDmFluenceV5Topo}
    Topology ID for Tx dual-mic Fluence V5. */
#define VPM_TX_DM_FLUENCEV5 ( 0x00010F74 )

/** @xreflabel{hdr:ParamVpmTxQmFluenceProV2Topo}
    Topology ID for Tx quad-mic Fluence Pro V2. */
#define VPM_TX_QM_FLUENCE_PROV2 ( 0x00010F87 )

/** @xreflabel{hdr:ParamVpmTxDmFluenceV5BroadsideTopo}
    Topology ID for Tx dual-mic Fluence V5 broadside speakerphone. */
#define VPM_TX_DM_FLUENCEV5_BROADSIDE ( 0x00010F88 )

/** @xreflabel{hdr:ParamVpmTxTmFluenceTopo}
    Topology ID for Tx tri-mic Fluence. */
#define VPM_TX_TM_FLUENCE ( 0x00010F80 )

/** @xreflabel{hdr:ParamVpmTxQmFluenceProTopo}
    Topology ID for Tx quad-mic Fluence Pro. */
#define VPM_TX_QM_FLUENCE_PRO ( 0x00010F75 )

/** @xreflabel{hdr:ParamVpmTxDmVpecnsTopo}
    Topology ID for Tx dual-mic Snapdragon@tm Voice Plus ECNS. */
#define VPM_TX_DM_VPECNS ( 0x00010F86 )
/** @endcond */

/** Topology ID for utilizing dynamically loadable voice modules in the shared
    object, voiceproc_tx.so. This topology must be used by modules that operate
    on the uplink device path.

    The supported media type is defined by the following:
    - The input and output of this topology must be signed 16-bit mono.
    - The reference signal is signed 16-bit mono.
    - Both near and far-end inputs use the same sampling rate.
*/
#define VPM_TX_SINGLE_MIC_DYNAMIC_TOPOLOGY (0x00010F83)

/** Topology ID for utilizing dynamically loadable voice modules in the shared
    object, voiceproc_tx.so. This topology must be used by modules that operate
    on the uplink device path.

    The media type supported is defined by the following:
    - The input and output of this topology must be signed 16-bit. 
    - The supported input number of channels is stereo (2), and the output
      must be mono.
    - The reference signal is signed 16-bit mono.
    - Both near and far-end inputs use the same sampling rate.
  */
#define VPM_TX_DUAL_MIC_DYNAMIC_TOPOLOGY (0x00010F84)

/** Topology ID for utilizing dynamically loadable voice modules in the shared
    object voiceproc_tx.so. This topology must be used by modules that operate
    on the uplink device path.

    The media type supported is defined by the following:
    - The input and output of this topology must be signed 16-bit. 
    - The input number of channels supported is quad (4), and the output
      must be mono.
    - The reference signal is signed 16-bit mono.
    - Both near and far-end inputs use the same sampling rate.
*/
#define VPM_TX_QUAD_MIC_DYNAMIC_TOPOLOGY (0x00010F85)

/** Topology ID for Rx pass through. */
#define VPM_RX_NONE       ( 0x00010F70 )

/** Topology ID for Rx processing with all available algorithms. */
#define VPM_RX_DEFAULT    ( 0x00010F77 )

/** Topology ID for utilizing dynamically loadable voice modules in the shared
    object voiceproc_rx.so. This topology must be used by modules that operate
    on the downlink device path.

    The media type supported is defined by the following:
    - The input and output of this topology must be signed 16-bit mono. 
    - The sampling rate of this topology is defined by the
      #VPM_CMD_CREATE_SESSION_V2 command. 
*/
#define VPM_RX_DYNAMIC_TOPOLOGY (0x00010F82)

/** @cond OEM_only */
/** Indicates that the far-end reference for echo cancellation is composed by
    mixing audio and voice inside the aDSP.
*/
#define	VPM_TX_INT_MIX_MODE       ( 0x00010F7C )

/** Indicates that the far-end reference for echo cancellation is composed by
    mixing audio and voice outside the aDSP.
*/
#define	VPM_TX_EXT_MIX_MODE       ( 0x00010F7D )
/** @endcond */

/** @} */ /* end_addtogroup vpm_cmd_create_session */

/* Used by the structure that creates a paired Tx/Rx device leg of
  the voice call. */
typedef struct vpm_create_session_v2_t vpm_create_session_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_create_session_v2_t
@{ */
/* Payload of the VPM_CMD_CREATE_SESSION_V2 command, which creates a
    paired Tx/Rx device leg of a voice call. It is also used by the
    VPM_CMD_REINIT_SESSION_V2 command, which reconfigures an existing device
    session.
*/
struct vpm_create_session_v2_t
{
   uint16_t tx_port;
   /**< AFE port ID for voice Tx. This port ID is expected by the AFE that
        connects to voice Tx device processing.

        @values Refer to @xhyperref{Q6,[Q6]} */
   /* Q6 = Hex Multimedia: Audio API Interface Spec for 2.4 (80-NF769-3) */

   uint16_t tx_sampling_rate;
   /**< Tx sampling rate.

        @values 8000, 16000, 48000 Hz */

   uint32_t tx_topology_id;
   /**< Identifies the predefined algorithms required for the session.

   @if OEM_only
        @values
        - #VPM_TX_NONE
        - #VPM_TX_SM_ECNS
        - #VPM_TX_DM_FLUENCE
        - #VPM_TX_SM_FLUENCEV5
        - #VPM_TX_DM_FLUENCEV5
        - #VPM_TX_TM_FLUENCE 
        - #VPM_TX_QM_FLUENCE_PRO 
        - #VPM_TX_DM_FLUENCEV5_BROADSIDE 
        - #VPM_TX_QM_FLUENCE_PROV2
        - #VPM_TX_DM_VPECNS @tablebulletend
    @endif
    @if ISV_only
        @values #VPM_TX_NONE
    @endif */

   uint16_t rx_port;
   /**< AFE port ID for voice Rx. This is the port ID expected by the AFE that
        connects to voice Rx device processing.

        @values Refer to @xhyperref{Q6,[Q6]} */

   uint16_t rx_sampling_rate;
   /**< Rx sampling rate.
   
        @values 8000, 16000, 48000 Hz */

   uint32_t rx_topology_id;
   /**< Identifies the predefined algorithms required for the session.

        @values
        - #VPM_RX_NONE
        - #VPM_RX_DEFAULT @tablebulletend */

   /** @cond OEM_only */
   uint32_t ec_mode;
   /**<	Echo Cancellation mode.

        @values
          - #VPM_TX_INT_MIX_MODE
          - #VPM_TX_EXT_MIX_MODE
        
        The far-end reference signal contains both audio and voice in the In
        Call Audio feature.

        Echo cancellation supports both Synchronous and Asynchronous mode. 
        - In Synchronous mode, echo cancellation expects an audio-plus-voice
          mixed signal as the echo reference.
        - In Asynchronous mode, echo cancellation expects audio and voice as
          different echo references.
        
        Audio and voice can be mixed within the aDSP or outside the aDSP. This
        mode word indicates where the mixing is happening. */
   /** @endcond */

   uint16_t audio_ref_port;
   /**< AFE port ID for an external audio signal. This is the port ID expected
        by the AFE that connects to the voice Tx device processing.

        @values Refer to @xhyperref{Q6,[Q6]}
        
        If this field is set to 0xFFFF, audio and voice are assumed to be
        mixed internally; otherwise, they are mixed externally. */

   uint16_t reserved;
   /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_create_session_v2_t */

/** @ingroup vpm_cmd_reconfig_session
    Reconfigures an existing device session with new parameters if the
    parameters of the existing session change. Use this command if
    #VPM_CMD_CREATE_SESSION_V2 was used to create the session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_REINIT_SESSION_V2
    @par
    Dst_port -- Handle to the session

  @msgpayload
    This command uses the same APR message payload as
    #VPM_CMD_CREATE_SESSION_V2.

  @description
    A voice processing session is a paired Tx/Rx session with postprocessing
    blocks. If the Tx or Rx port is set to NO_INTERFACE, the corresponding
    module is not created. If, in the original handle, the Tx port was set to
    NO_INTERFACE but it is now a valid interface, a corresponding module is
    created.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created, and it must be in the Stop state.
    @par
    Typically, a new set of calibration data is sent after this
    reinitialization and before the session is restarted.
*/
#define VPM_CMD_REINIT_SESSION_V2  ( 0x0001103A )

/** @cond OEM_only */
/** @ingroup vpm_cmd_set_timing_params
    Sets the Vocoder Frame Reference (VFR) mode and timing offsets in a
    voice stream session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_SET_TIMING_PARAMS
    @par
    Dst_port -- Handle to the session

  @apr_msgpayload{vpm_set_timing_params_t}
    @table{weak__vpm__set__timing__params__t}

  @detdesc
    This command is used to provide timing information for a packet exchange
    to the aDSP services. All circuit-switched calls must use either the
    internal or external #VFR_HARD mode. All packet-switched calls with time
    warping enabled or disabled, and other applications, must use #VFR_NONE
    mode.

  @dependencies
    A valid session must have been created.
    @par
    This command can only be issued in the Stop state.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
*/
#define VPM_CMD_SET_TIMING_PARAMS ( 0x0001105A )

/* Payload used to provide timing information for a packet exchange
  to the voice services. */
typedef struct vpm_set_timing_params_t vpm_set_timing_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_set_timing_params_t
@{ */
/* Payload of the VPM_CMD_SET_TIMING_PARAMS command, which sets the
    VFR mode and timing offsets in a session.
*/
struct vpm_set_timing_params_t
{
   uint16_t mode;
   /**< Sets the stream VFR mode. The decoder derives timing based on its
        output length.
    
        @values
        - #VFR_NONE -- No periodic tick is used
        - #VFR_HARD -- Internal modem generates a 20 ms periodic tick
        - #VFR_HARD_EXT -- External modem generates a 20 ms periodic tick 
		@tablebulletend */

   uint16_t vptx_start_offset;
   /**< Offset from the VFR for the voice device uplink to synchronize to
        incoming data from the AFE.

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is reverse calculated from the encoder offset, leaving room
		for encoder and voice device uplink processing times. Clock settings
		and system load are factors considered for this calculation. */

   uint16_t vptx_delivery_offset;
   /**< Offset from the VFR for the voice device uplink to deliver processed
        data to the encoder.

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is reverse calculated from the encoder offset, leaving room
		for encoder processing times. Clock settings and system load are
		factors considered for this calculation. */

   uint16_t vprx_delivery_offset;
   /**< Offset from the VFR for the voice device downlink to deliver processed
        data to the AFE. 

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is forward calculated from the decode begin offset,
		considering room for the decoder, voice stream downlink, and voice
		device downlink processing times. Clock settings and system load are
		factors considered for this calculation. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_set_timing_params_t */
/** @endcond */

/** @ingroup vpm_cmd_get_kpps
    Queries the VPM for required Kilo Packets per Second (KPPS) by aggregating
	the KPPS of all modules independently on the Tx and Rx paths.

  @apr_hdr_fields
    Opcode -- VPM_CMD_GET_KPPS
    @par
    Dst_port -- Handle to the session

  @msgpayload
    None.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}) .
	@par
    #VPM_RSP_GET_KPPS_ACK in response to this command. 
    In the event of a failure, this acknowledgment is not returned.

  @dependencies
    A valid session must have been created.
*/
#define VPM_CMD_GET_KPPS ( 0x00011056 )

/** @ingroup vpm_resp_get_kpps_ack
    Response to the #VPM_CMD_GET_KPPS command.

  @apr_hdr_fields
    Opcode -- VPM_RSP_GET_KPPS_ACK
    @par
    Dst_port -- Client handle
    @par
    Src_port -- Handle to the stream session

  @apr_msgpayload{vpm_get_kpps_ack_t}
    @table{weak__vpm__get__kpps__ack__t}

  @return
    None.

  @dependencies
    A valid session must have been created.
*/
#define VPM_RSP_GET_KPPS_ACK ( 0x00011058 )

/* Used by the structure that responds to the Get KPPS command. */
typedef struct vpm_get_kpps_ack_t vpm_get_kpps_ack_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_get_kpps_ack_t
@{ */
/* Payload of the VPM_RSP_GET_KPPS_ACK event, which acknowledges
    the VPM_CMD_GET_KPPS command.
*/
struct vpm_get_kpps_ack_t
{
   uint32_t vptx_kpps;
   /**< Specifies the KPPS consumed by the voice device Tx processing thread.
   
        @values Any uint32 value */

   uint32_t vprx_kpps;
   /**< Specifies the KPPS consumed by the voice device Rx processing thread.
   
        @values Any uint32 value */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_get_kpps_ack_t */

/** @cond OEM_only */
/** @ingroup vpm_cmd_set_timing_params_2
    Sets the timing mode, Voice System ID (VSID), and timing offsets in a voice
    stream session.

  @apr_hdr_fields
    Opcode -- VPM_CMD_SET_TIMING_PARAMS_V2
    @par
    Dst_port -- Handle to the stream session

  @apr_msgpayload{vpm_set_timing_params_v2_t}
    @table{weak__vpm__set__timing__params__v2__t}

  @detdesc
    This command is used to provide timing information for a packet exchange
    to the aDSP services. Clients who intend to drive timing must set the mode 
    to VFR_HARD and send the appropriate VSID. Clients who do not intend to
    drive the timing must set the mode to VFR_NONE, where internal timing is
    used.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A valid session must have been created.
    @par
    This command is allowed only in the Stop state.
*/
#define VPM_CMD_SET_TIMING_PARAMS_V2 ( 0x0001105C )

/* Payload used to provide timing information for a packet exchange
  to the voice services. */
typedef struct vpm_set_timing_params_v2_t vpm_set_timing_params_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_set_timing_params_v2_t
@{ */
/* Payload of the VPM_CMD_SET_TIMING_PARAMS_V2 command, which sets the
    timing mode, VSID and timing offsets in a session.
*/
struct vpm_set_timing_params_v2_t
{
   uint16_t mode;
   /**< Sets the timing mode.
    
        @values
        - #VFR_NONE -- Internal timing is used and the VSID is ignored
        - #VFR_HARD -- Timing is driven by the client (for more information,
                       refer to @xhyperref{Q9,[Q9]}) @tablebulletend */

   /* Q9 = Voice System ID (VSID) Definition And Use Cases (80-NF711-1) */
        
   uint32_t vsid;
   /**< Voice System ID, which has information on how VFR_HARD timing is to be
        used by the session.
        
        @values Refer to @xhyperref{Q9,[Q9]}

        Bits[21:18] represent the VFR ID, which is used by the AFE for
        direct mapping of mux input in the LPAIF hardware. Mux input lines
        are hardwired to different modems. */

   uint16_t vptx_start_offset;
   /**< Offset from the VFR for the voice device uplink to synchronize to
        incoming data from the AFE.

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is reverse calculated from the encoder offset, leaving room
        for encoder and voice device uplink processing times. The calculation
        considers clock settings and system load factors. */

   uint16_t vptx_delivery_offset;
   /**< Offset from the VFR for the voice device uplink to deliver processed
        data to the encoder.

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is reverse calculated from the encoder offset, leaving room
        for encoder processing times. The calculation considers clock settings
        and system load factors. */

   uint16_t vprx_delivery_offset;
   /**< Offset from the VFR for the voice device downlink to deliver processed
        data to the AFE. 

        @values 0 to 20000 microseconds with 1-microsecond granularity

        The offset is forward calculated from the decode begin offset, and it
        considers room for decoder, voice stream downlink, and voice device
        downlink processing times. The calculation considers clock settings
        and system load factors. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_set_timing_params_v2_t */
/** @endcond */

/** @ingroup vpm_cmd_get_delay
    Queries the VPM for the total delay added by aggregating
    the delays of all modules independently on the Tx and Rx paths,
    including delay added by the AFE.

    Valid AFE delay can be provided only if the delay is queried when the
    session is in the Run state and the AFE ports being used are already
    calibrated and running.

  @apr_hdr_fields
    Opcode -- VPM_CMD_GET_DELAY
    @par
    Dst_port -- Handle to the session

  @msgpayload
    None.

  @return
    #VPM_RSP_GET_DELAY_ACK.
	@par
    An acknowledgment is sent back in response to this command. 
    @par
    In the event of a failure, the error is reported back.

  @dependencies
    A valid session must have been created.
*/
#define VPM_CMD_GET_DELAY ( 0x00011062 )

/** @ingroup vpm_resp_get_delay_ack
    Response to the #VPM_CMD_GET_DELAY command.

  @apr_hdr_fields
    Opcode -- VPM_RSP_GET_DELAY_ACK
    @par
    Dst_port -- Client handle
    @par
    Src_port -- Handle to the stream session

  @apr_msgpayload{vpm_get_delay_ack_t}
    @table{weak__vpm__get__delay__ack__t}

  @return
    None.

  @dependencies
    A valid session must have been created.
*/
#define VPM_RSP_GET_DELAY_ACK ( 0x00011063 )

/* Used by the structure that responds to the Get Delay command. */
typedef struct vpm_get_delay_ack_t vpm_get_delay_ack_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_vpm_get_delay_ack_t
@{ */
/* Payload of the VPM_RSP_GET_DELAY_ACK event, which acknowledges
    the VPM_CMD_GET_DELAY command.
*/
struct vpm_get_delay_ack_t
{
   uint32_t vptx_delay;
   /**< Specifies the total delay (in microseconds) on the Tx device path,
        including algorithmic and buffering delay added by the voice device Tx
        processing thread and group delay added by the AFE Tx port.
   
        @values Any uint32 value */

   uint32_t vprx_delay;
   /**< Specifies the total delay (in microseconds) on the Rx device path,
        including algortithmic and buffering delay added by the voice device
        Rx processing thread and group delay added by the AFE Rx port.
   
        @values Any uint32 value */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_vpm_get_delay_ack_t */


#endif /* __ADSP_VPM_API_H__ */

