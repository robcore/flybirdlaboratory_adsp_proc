#ifndef _ADSP_AFE_SERVICE_COMMANDS_H_
#define _ADSP_AFE_SERVICE_COMMANDS_H_

/*========================================================================*/
/**
@file adsp_afe_service_commands.h

This file contains AFE service commands and events structures definitions.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      Any descriptions that display in the PDF are located in the
      AFE_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
Copyright (c) 2012, 2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================ */
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/afe/inc/adsp_afe_service_commands.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
10/20/14    sw     (Tech Pubs) Edited Doxygen comments/markup for 2.6.
03/01/14    sw     (Tech Pubs) Edited Doxygen comments/markup for 2.4.
11/16/12    sw     (Tech Pubs) Edited comments and applied latest Doxygen markup.
03/27/12   mspk    Non backward compatible API changes for next generation
========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/** @ingroup afe_version
    Version of the aDSP AFE module.
*/
#define ADSP_AFE_VERSION    0x00260000

/** @addtogroup afe_port_id_ranges
@{ */

/** Size of the range of port IDs for the audio interface. */
#define  AFE_PORT_ID_AUDIO_IF_PORT_RANGE_SIZE                       0x16

/** Size of the range of port IDs for internal BT-FM ports. */
#define AFE_PORT_ID_INTERNAL_BT_FM_RANGE_SIZE                       0x6

/** Size of the range of port IDs for SLIMbus multichannel ports. */
#define AFE_PORT_ID_SLIMBUS_RANGE_SIZE                              0x12

/** Size of the range of port IDs for real-time proxy ports. */
#define  AFE_PORT_ID_RT_PROXY_PORT_RANGE_SIZE                       0x6

/** Size of the range of port IDs for pseudoports. */
#define AFE_PORT_ID_PSEUDOPORT_RANGE_SIZE                           0x5

/** Size of the range of port IDs for HDMI input. */
#define AFE_PORT_ID_HDMI_INPUT_RANGE_SIZE                           0x1

/** Start of the range of port IDs for the audio interface. */
#define  AFE_PORT_ID_AUDIO_IF_PORT_RANGE_START                      0x1000

/** End of the range of port IDs for the audio interface. */
#define  AFE_PORT_ID_AUDIO_IF_PORT_RANGE_END                        (AFE_PORT_ID_AUDIO_IF_PORT_RANGE_START+AFE_PORT_ID_AUDIO_IF_PORT_RANGE_SIZE-1)

/** Start of the range of port IDs for real-time proxy ports. */
#define  AFE_PORT_ID_RT_PROXY_PORT_RANGE_START                      0x2000

/** End of the range of port IDs for real-time proxy ports. */
#define  AFE_PORT_ID_RT_PROXY_PORT_RANGE_END                        (AFE_PORT_ID_RT_PROXY_PORT_RANGE_START+AFE_PORT_ID_RT_PROXY_PORT_RANGE_SIZE-1)

/** Start of the range of port IDs for internal BT-FM devices. */
#define AFE_PORT_ID_INTERNAL_BT_FM_RANGE_START                      0x3000

/** End of the range of port IDs for internal BT-FM devices. */
#define AFE_PORT_ID_INTERNAL_BT_FM_RANGE_END                        (AFE_PORT_ID_INTERNAL_BT_FM_RANGE_START+AFE_PORT_ID_INTERNAL_BT_FM_RANGE_SIZE-1)

/** Start of the range of port IDs for SLIMbus devices. */
#define AFE_PORT_ID_SLIMBUS_RANGE_START                             0x4000

/** End of the range of port IDs for SLIMbus devices. */
#define AFE_PORT_ID_SLIMBUS_RANGE_END                               (AFE_PORT_ID_SLIMBUS_RANGE_START+AFE_PORT_ID_SLIMBUS_RANGE_SIZE-1)

/** Start of the range of port IDs for pseudoports. */
#define AFE_PORT_ID_PSEUDOPORT_RANGE_START                          0x8001

/** End of the range of port IDs for pseudoports. */
#define AFE_PORT_ID_PSEUDOPORT_RANGE_END                            (AFE_PORT_ID_PSEUDOPORT_RANGE_START+AFE_PORT_ID_PSEUDOPORT_RANGE_SIZE-1)

/** Start of the range of port IDs for HDMI input. */
#define AFE_PORT_ID_HDMI_INPUT_RANGE_START                          0x6001

/** End of the range of port IDs for HDMI input. */
#define AFE_PORT_ID_HDMI_INPUT_RANGE_END                            (AFE_PORT_ID_HDMI_INPUT_RANGE_START+AFE_PORT_ID_HDMI_INPUT_RANGE_SIZE-1)

/** @} */ /* end_addtogroup afe_port_id_ranges */

/** @addtogroup afe_defined_port_ids
@{ */
/** ID of the primary MI2S Rx port. */
#define AFE_PORT_ID_PRIMARY_MI2S_RX                                 0x1000

/** ID of the primary MI2S Tx port. */
#define AFE_PORT_ID_PRIMARY_MI2S_TX                                 0x1001

/** ID of the secondary MI2S Rx port. */
#define AFE_PORT_ID_SECONDARY_MI2S_RX                               0x1002

/** ID of the secondary MI2S Tx port. */
#define AFE_PORT_ID_SECONDARY_MI2S_TX                               0x1003

/** ID of the tertiary MI2S Rx port. */
#define AFE_PORT_ID_TERTIARY_MI2S_RX                                0x1004

/** ID of the tertiary MI2S Tx port. */
#define AFE_PORT_ID_TERTIARY_MI2S_TX                                0x1005

/** ID of the quaternary MI2S Rx port. */
#define AFE_PORT_ID_QUATERNARY_MI2S_RX                              0x1006

/** ID of the quaternary MI2S Tx port. */
#define AFE_PORT_ID_QUATERNARY_MI2S_TX                              0x1007

/** ID of the I2S Rx port. This macro is for backward compatability.
    For naming consistency, use #AFE_PORT_ID_I2S_RX instead.
*/
#define AUDIO_PORT_ID_I2S_RX                                        0x1008

/** ID of the I2S Rx port. */
#define AFE_PORT_ID_I2S_RX                                          AUDIO_PORT_ID_I2S_RX

/** ID of the digital microphone Tx port. */
#define AFE_PORT_ID_DIGITAL_MIC_TX                                  0x1009

/** ID of the primary auxiliary PCM Rx port. */
#define AFE_PORT_ID_PRIMARY_PCM_RX                                  0x100A

/** ID of the primary auxiliary PCM Tx port. */
#define AFE_PORT_ID_PRIMARY_PCM_TX                                  0x100B

/** ID of the secondary auxiliary PCM Rx port. */
#define AFE_PORT_ID_SECONDARY_PCM_RX                                0x100C

/** ID of the secondary auxiliary PCM Tx port. */
#define AFE_PORT_ID_SECONDARY_PCM_TX                                0x100D

/** ID of the multichannel HDMI Rx port. */
#define AFE_PORT_ID_MULTICHAN_HDMI_RX                               0x100E

/** ID of secondary MI2S Rx port 2. */
#define AFE_PORT_ID_SECONDARY_MI2S_RX_2                             0x1010

/** ID of the tertiary auxiliary PCM Rx port. */
#define AFE_PORT_ID_TERTIARY_PCM_RX                                 0x1012

/** ID of the tertiary auxiliary PCM Tx port. */
#define AFE_PORT_ID_TERTIARY_PCM_TX                                 0x1013

/** ID of the quaternary auxiliary PCM Rx port. */
#define AFE_PORT_ID_QUATERNARY_PCM_RX                               0x1014

/** ID of the quaternary auxiliary PCM Tx port. */
#define AFE_PORT_ID_QUATERNARY_PCM_TX                               0x1015

/** ID of real-time Rx proxy port 1.

    When this port is opened, the real-time port driver reads data
    from the AFE service and sends it to the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_001_RX                           0x2000

/** ID of real-time Tx proxy port 1.

    When this port is opened, the real-time port driver writes data
    to the AFE service from the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_001_TX                           0x2001

/** ID of real-time Rx proxy port 2.

    When this port is opened, the real-time port driver reads data
    from the AFE service and sends it to the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_002_RX                           0x2002

/** ID of real-time Tx proxy port 2.

    When this port is opened, the real-time port driver writes data
    to the AFE service from the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_002_TX                           0x2003

/** ID of real-time Rx proxy port 3.

    When this port is opened, the real-time port driver reads data
    from the AFE service and sends it to the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_003_RX                           0x2004

/** ID of real-time Tx proxy port 3.

    When this port is opened, the real-time port driver writes data
    to the AFE service from the real-time device.
*/
#define  AFE_PORT_ID_RT_PROXY_PORT_003_TX                           0x2005

/** ID of the internal Bluetooth@regns Rx port. */
#define AFE_PORT_ID_INTERNAL_BT_SCO_RX                              0x3000

/** ID of the internal Bluetooth Tx port. */
#define AFE_PORT_ID_INTERNAL_BT_SCO_TX                              0x3001

/** ID of the internal A2DP Rx port. */
#define AFE_PORT_ID_INTERNAL_BT_A2DP_RX                             0x3002

/** ID of the internal FM audio Rx port. */
#define AFE_PORT_ID_INTERNAL_FM_RX                                  0x3004

/** ID of the internal FM audio Tx porID. */
#define AFE_PORT_ID_INTERNAL_FM_TX                                  0x3005

/** ID of SLIMbus Rx multichannel port 0. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_RX                         0x4000

/** ID of SLIMbus Tx multichannel port 0. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_TX                         0x4001

/** ID of SLIMbus Rx multichannel port 1. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_RX                         0x4002

/** ID of SLIMbus Tx multichannel port 1. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_TX                         0x4003

/** ID of SLIMbus Rx multichannel port 2. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_RX                         0x4004

/** ID of SLIMbus Tx multichannel port 2. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_TX                         0x4005

/** ID of SLIMbus Rx multichannel port 3. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_RX                         0x4006

/** ID of SLIMbus Tx multichannel port 3. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_TX                         0x4007

/** ID of SLIMbus Rx multichannel port 4. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_RX                         0x4008

/** ID of SLIMbus Tx multichannel port 4. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_TX                         0x4009

/** ID of SLIMbus Rx multichannel port 5. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_RX                         0x400A

/** ID of SLIMbus Tx multichannel port 5. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_TX                         0x400B

/** ID of SLIMbus Rx multichannel port 6. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_RX                         0x400C

/** ID of SLIMbus Tx multichannel port 6. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_TX                         0x400D

/** ID of SLIMbus Rx multichannel port 7. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_7_RX                         0x400E

/** ID of SLIMbus Tx multichannel port 7. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_7_TX                         0x400F

/** ID of SLIMbus Rx multichannel port 8. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_8_RX                         0x4010

/** ID of SLIMbus Tx multichannel port 8. */
#define AFE_PORT_ID_SLIMBUS_MULTI_CHAN_8_TX                         0x4011

/** ID of the SPDIF Rx port. */
#define AFE_PORT_ID_SPDIF_RX                                        0x5000

/** ID of the HDMI Tx port. */
#define AFE_PORT_ID_HDMI_TX                                         0x6001

/** ID of the Signaling Information Field (SIF) Tx port. */
#define AFE_PORT_ID_SIF_TX                                          0x7001

/** ID of generic pseudoport 1. */
#define AFE_PORT_ID_PSEUDOPORT_01                                   0x8001

/** ID of generic pseudoport 2. */
#define AFE_PORT_ID_PSEUDOPORT_02                                   0x8002

/** ID of the pseudoport that corresponds to the voice Rx path.

    For recording, the voice Rx path samples are written to this port and
    consumed by the audio path.
*/
#define AFE_PORT_ID_VOICE_RECORD_RX                                 0x8003

/** ID of the pseudoport that corresponds to the voice Tx path.

    For recording, the voice Tx path samples are written to this port and
    consumed by the audio path.
*/
#define AFE_PORT_ID_VOICE_RECORD_TX                                 0x8004

/** ID of the pseudoport that corresponds to in-call voice delivery samples.

    During in-call audio delivery, the audio path delivers samples to this port
    from where the voice path delivers them on the Rx path.
*/
#define AFE_PORT_ID_VOICE_PLAYBACK_TX                               0x8005

/** Invalid port ID. */
#define AFE_PORT_ID_INVALID                                         0xFFFF

/** @} */ /* end_addtogroup afe_defined_port_ids */

/** @ingroup afe_defined_group_device_ids
    Secondary MI2S group device ID.
*/
#define AFE_GROUP_DEVICE_ID_SECONDARY_MI2S_RX                        (AFE_PORT_ID_SECONDARY_MI2S_RX + 0x100)

/** @ingroup afe_cmd_start_dtmf
    Starts DTMF on any port, including a pseudoport.

  @apr_hdr_fields
    Opcode -- AFE_PORTS_CMD_DTMF_CTL

  @apr_msgpayload{afe_ports_cmd_dtmf_ctl_t}
    @table{weak__afe__ports__cmd__dtmf__ctl__t}
    Following this structure in memory are num_ports number of port_ids. If
    num_ports is greater than one, the reserved field is one of the port_ids;
    otherwise, the reserved field must be set to zero.
    @par
    When multiple ports are involved, the acknowledgment indicates the status:
    - SUCCESS -- DTMF is initiated on all ports
    - FAILURE -- DTMF failed on one or more ports (may not be all ports)

  @detdesc
    When enabling DTMF on more than one port, specify num_ports with the number
    of ports where DTMF is to be enabled. The port ID of each port is to follow
    the port ID field in the command structure.
    @par
    For multiple ports, the command's return value indicates if there was a
    failure, i.e., DTMF might be successful on some ports and fail on others.
    If a return status is important, the command is to be sent to each port
    individually.
    @par
    This command is accepted only on ports with sampling rates of:
    - #AFE_PORT_SAMPLE_RATE_8K
    - #AFE_PORT_SAMPLE_RATE_16K
    - #AFE_PORT_SAMPLE_RATE_48K

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The port must be active. If the port is inactive and a DTMF command is
    received, DTMF is not played. If the port is activated, a new command
    must be received to play DTMF later.
*/ /* Q3 = Asynchronous Packet Router API (for MDM9x15 and Newer Devices)
      Interface Spec (80-N1463-2) */
#define AFE_PORTS_CMD_DTMF_CTL                                   0x00010102

/* Structure for the AFE_PORTS_CMD_DTMF_CTL command. */
typedef struct afe_ports_cmd_dtmf_ctl_t afe_ports_cmd_dtmf_ctl_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_ports_cmd_dtmf_ctl_t
@{ */
/* Payload of the AFE_PORTS_CMD_DTMF_CTL command, which starts DTMF on
    any port.
 */
struct afe_ports_cmd_dtmf_ctl_t
{
    int64_t                   dtmf_duration_in_ms;
    /**< Duration in milliseconds of the DTMF tone.

         @values
         - -1 -- Continuous DTMF of infinite duration
         - 0 -- Disable; this also stops a continuous DTMF if it was started

         Any other valid value indicates the duration in milliseconds. */

    uint16_t                  dtmf_high_freq;
    /**< DTMF high tone frequency.

         @values 1209, 1336, 1477, 1633 Hz */

    uint16_t                  dtmf_low_freq;
    /**< DTMF low tone frequency.

         @values 697, 770, 852, 941 Hz */

    uint16_t                  dtmf_gain;
    /**< Gain applied to a DTMF tone.

         @values Any number (in Q13 format) */

    uint16_t                  num_ports;
    /**< Number of ports following this structure in memory.

         @values @ge 1 */

    uint16_t                  port_ids;
    /**< Destination ports (array). For DTMF on multiple ports, port_ids is
         populated num_ports times, and they follow this element. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_ports_cmd_dtmf_ctl_t */

/** @ingroup afe_module_sidetone_iir_filter
    ID of the Sidetone IIR module, which sets or gets the calibration data of
    the sidetone filter for a requested AFE Rx port.
    This module supports the following parameter IDs:
    - #AFE_PARAM_ID_SIDETONE_IIR_FILTER_CONFIG
    - #AFE_PARAM_ID_ENABLE

    This module is effective only when the sidetone path is enabled and active.

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SIDETONE_IIR_FILTER
*/
#define AFE_MODULE_SIDETONE_IIR_FILTER                              0x00010202

/** @ingroup afe_common_params
    ID of the parameter used to enable/disable the following modules:
    - #AFE_MODULE_SIDETONE_IIR_FILTER
    - #AFE_MODULE_RMC
    - #AFE_MODULE_SPEAKER_PROTECTION
    - #AFE_MODULE_AANC
    - #AFE_MODULE_FB_SPKR_PROT_RX
    - #AFE_MODULE_FB_SPKR_PROT_VI_PROC
    - #AFE_MODULE_ID_SW_MAD
    - #AFE_MODULE_SW_DUTY_CYCLE
  @if OEM_only
    - #AFE_MODULE_SPEAKER_PROTECTION_V2_RX
  @endif

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_ENABLE

    @apr_msgpayload{afe_mod_enable_param_t}
    @tablens{weak__afe__mod__enable__param__t}
*/
#define AFE_PARAM_ID_ENABLE                                          0x00010203

typedef struct afe_mod_enable_param_t afe_mod_enable_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_mod_enable_param_t
@{ */
/* Payload of the AFE_PARAM_ID_ENABLE parameter, which enables or
    disables any module. */
/** The fixed size of this structure is four bytes.
*/
struct afe_mod_enable_param_t
{
    uint16_t                  enable;
    /**< Specifies whether the module is enabled (1) or disabled (0). */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_mod_enable_param_t */

/** @ingroup afe_module_sidetone_iir_filter
    ID of the parameter used by #AFE_MODULE_SIDETONE_IIR_FILTER to configure
    the sidetone IIR filter. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

  @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIDETONE_IIR_FILTER_CONFIG

  @apr_msgpayload{afe_sidetone_iir_filter_config_params_t}
    @table{weak__afe__sidetone__iir__filter__config__params__t}
    This structure is followed by the IIR filter coefficients:
    - Sequence of int32 ulFilterCoeffs \n
      Each band has five coefficients, each in int32 format in the order of b0,
      b1, b2, a1, a2. The total sequence length depends on the number of bands.
        - bx -- Numerator coefficients
        - ax -- Denominator coefficients
    - Sequence of int16 sNumShiftFactor \n
      One int16 per band; a numerator shift factor related to the Q factor of
      the filter coefficients. If the number of bands is odd, pad an extra value
      for alignment.

  @detdesc
    This structure has a field indicating the number of stages for filter and
    pregain, followed by variable-sized IIR filter structures. The size of these
    structures is defined by configurable parameters.
    @par
    Set the filter parameters before enabling the module so there will not be
    any audio quality issues because of a change in pregain from default to
    required values.
    @par
    The maximum size for a sidetone filter is 224 bytes. The maximum number of
    filter stages is assumed to be 10 (the original requirement was 5 stages).
    For an odd number of stages, 2 bytes of padding are required at the end of
    the payload.
*/
#define AFE_PARAM_ID_SIDETONE_IIR_FILTER_CONFIG                      0x00010204

typedef struct afe_sidetone_iir_filter_config_params_t afe_sidetone_iir_filter_config_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sidetone_iir_filter_config_params_t
@{ */
/* Payload of the AFE_PARAM_ID_SIDETONE_IIR_FILTER_CONFIG parameter,
    which configures the sidetone IIR tuning filter module.
*/
struct afe_sidetone_iir_filter_config_params_t
{
    uint16_t                  num_biquad_stages;
    /**< Number of stages.

         @values Minimum of 5 and maximum of 10 */

    uint16_t                  pregain;
    /**< Pregain for the compensating filter response.

         @values Any number (in Q13 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sidetone_iir_filter_config_params_t */

/** @addtogroup afe_module_loopback
@{ */
/** ID of the Loopback module, which is used to set up the loopback between AFE
    ports.
    This module supports the following parameter IDs:
    - #AFE_PARAM_ID_LOOPBACK_GAIN_PER_PATH
    - #AFE_PARAM_ID_LOOPBACK_CONFIG

    @apr_hdr_fields
    Opcode -- AFE_MODULE_LOOPBACK
*/
#define AFE_MODULE_LOOPBACK                                           0x00010205

/** ID of the parameter used by #AFE_MODULE_LOOPBACK to get/set the loopback
    gain on a specified path.

    When multiple loopbacks are enabled, this parameter ID controls the gain
    of the loopback from the source port ID in #AFE_PORT_CMD_SET_PARAM_V2
    to the destination port ID. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_LOOPBACK_GAIN_PER_PATH

    @apr_msgpayload{afe_loopback_gain_per_path_param_t}
    @tablens{weak__afe__loopback__gain__per__path__param__t} @newpage
*/
#define AFE_PARAM_ID_LOOPBACK_GAIN_PER_PATH                         0x00010206

/** @} */ /* end_addtogroup afe_module_loopback */

typedef struct afe_loopback_gain_per_path_param_t afe_loopback_gain_per_path_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_loopback_gain_per_path_param_t
@{ */
/* Payload of the AFE_PARAM_ID_LOOPBACK_GAIN_PER_PATH parameter,
    which gets/sets loopback gain of a port to a Rx port. */
/** The Tx port ID of the loopback is part of #AFE_PORT_CMD_SET_PARAM_V2.
*/
struct afe_loopback_gain_per_path_param_t
{
   uint16_t                  rx_port_id;
   /**< Rx port of the loopback. */

   uint16_t                  gain;
   /**< Loopback gain per path of the port.

        @values Any number (in Q13 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_loopback_gain_per_path_param_t */

/** @addtogroup afe_module_loopback
@{ */
/** ID of the parameter used by #AFE_MODULE_LOOPBACK to configure and
    enable/disable the loopback path.

    This parameter ID allows an Rx port to be configured as a source port on
    the loopback path. The port_id field in #AFE_PORT_CMD_SET_PARAM_V2 is the
    source port that can be designated as a Tx or Rx port. Both
    #AFE_PORT_CMD_SET_PARAM_V2 and #AFE_PORT_CMD_GET_PARAM_V2 can use this
    parameter ID.

    Also, this parameter ID can be used to configure the type of
    routing mode, which is useful for handling different use cases.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_LOOPBACK_CONFIG

    @apr_msgpayload{afe_loopback_cfg_v1_t}
    @table{weak__afe__loopback__cfg__v1__t}
*/
#define AFE_PARAM_ID_LOOPBACK_CONFIG                                 0x0001020B

/** Version information used to handle future additions to
    AFE_PARAM_ID_LOOPBACK_CONFIG configuration (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_LOOPBACK_CONFIG                                0x1

/** Data path type of the loopback routing mode.
*/
typedef enum afe_loopback_routing_mode_t
{
    LB_MODE_DEFAULT = 1,
    /**< Regular loopback from the source port to the destination port. */

    LB_MODE_SIDETONE,
    /**< Sidetone feed from the source port to the destination port.
         This field is supported only on the Tx port. */

    LB_MODE_EC_REF_VOICE_AUDIO,
    /**< Echo canceller reference: voice + audio + DTMF. This field is
         supported only on the Rx port. */

    LB_MODE_EC_REF_VOICE
    /**< Echo canceller reference: voice alone. Currently, this field is not
         supported. */

}/** @cond */ afe_loopback_routing_mode_t /** @endcond */ ;

/** @} */ /* end_addtogroup afe_module_loopback */

/* Structure for the AFE_PARAM_ID_LOOPBACK_CONFIG param. */
typedef struct afe_loopback_cfg_v1_t afe_loopback_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_loopback_cfg_v1_t
@{ */
/* Payload of the AFE_PARAM_ID_LOOPBACK_CONFIG parameter, which
    enables/disables one AFE loopback.
*/
struct afe_loopback_cfg_v1_t
{
    uint32_t                  loopback_cfg_minor_version;
    /**< Minor version used to track loopback module configuration.

         @values #AFE_API_VERSION_LOOPBACK_CONFIG */

    uint16_t                  dst_port_id;
    /**< Destination port ID.

         @values See <i>Supported Hardware Ports</i> for the applicable
                 chipset in Chapter @xref{chp:portIDs} */

    uint16_t                  routing_mode;
    /**< Specifies the data path type from the source to the destination port.

         @values
         - #LB_MODE_DEFAULT
         - #LB_MODE_SIDETONE
         - #LB_MODE_EC_REF_VOICE_AUDIO
         - #LB_MODE_EC_REF_VOICE @tablebulletend */

    uint16_t                  enable;
    /**< Specifies whether to enable (1) or disable (0) an AFE loopback. */

     uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_loopback_cfg_v1_t */

/** @addtogroup afe_module_rmc
@{ */
/** ID of the Remove Click Noise (RMC) module, which supports the following
    parameter IDs:
    - #AFE_PARAM_ID_RMC_CONFIG
    - #AFE_PARAM_ID_ENABLE

    @apr_hdr_fields
    Opcode -- AFE_MODULE_RMC

    @detdesc
    RMC module configuration and enabling is recommended when the AFE port is
    in the Configuration state (i.e, after configuring the AFE port only).
    The module must be disabled only when the port is in the Stop state
    (after a port stop command only) to avoid errors or problems.
*/
#define AFE_MODULE_RMC                                               0x00010207

/** ID of the parameter used by #AFE_MODULE_RMC to set or get RMC configuration
    parameters. Both #AFE_PORT_CMD_SET_PARAM_V2 and #AFE_PORT_CMD_GET_PARAM_V2
    can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_RMC_CONFIG

    @apr_msgpayload{afe_rmc_cfg_param_v1_t}
    @table{weak__afe__rmc__cfg__param__v1__t}
*/
#define AFE_PARAM_ID_RMC_CONFIG                                       0x00010208

/** Version information used to handle future additions to
    AFE_PARAM_ID_RMC_CONFIG configuration (for backward compatibility).
*/
#define AFE_API_VERSION_RMC_CONFIG                                     0x1

/** @} */ /* end_addtogroup afe_module_rmc */

typedef struct afe_rmc_cfg_param_v1_t afe_rmc_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_rmc_cfg_param_v1_t
@{ */
/* Payload of the AFE_PARAM_ID_RMC_CONFIG parameter, which gets/sets
    RMC configuration parameters.
*/
struct afe_rmc_cfg_param_v1_t
{
   uint32_t                 rmc_minor_version;
   /**< Minor version used to track RMC module configuration.

        @values #AFE_API_VERSION_RMC_CONFIG */

   int16_t                  rmc_neg_on_set_detect_thresh;
   /**< Threshold used to trigger the start of negative spike tracking.

        @values 0 to 32767 */

   int16_t                  rmc_pos_on_set_detect_thresh;
   /**< Threshold used to trigger the start of positive spike tracking.

        @values 0 to 32767 */

   int16_t                  rmc_on_set_slope;
   /**< Ratio between x(n) and x(n-2) used to trigger the start of spike
        tracking.

        @values 1 to 32767 */

   int16_t                  rmc_neg_peak_detect_thresh;
   /**< Threshold used to determine the negative peak.

        @values 0 to 32767 */

   int16_t                  rmc_pos_peak_detect_thresh;
   /**< Threshold used to determine the positive peak.

        @values 0 to 32767 */

   int16_t                  rmc_neg_click_tail_thresh;
   /**< Threshold used to track the long smooth tail after the negative peak.

        @values 0 to 32767 */

   int16_t                  rmc_pos_click_tail_thresh;
   /**< Threshold used to track the long smooth tail after the positive peak.

        @values 0 to 32767 */

   uint16_t                 rmc_ramp_upDn_length;
   /**< Length of the gain ramping up/down.

        @values 2 to 48000 */

   uint16_t                 rmc_delay_length;
   /**< Delay buffer size used for look-ahead.

        @values 0 to 48000 */

   int16_t                  rmc_next_pos_on_set_thresh;
   /**< When still in negative spike detection and a positive spike arrives:
        threshold used to switch to positive spike detection.

        @values 0 to 32767 */

   int16_t                  rmc_next_pos_on_set_slope;
   /**< When still in negative spike detection and a positive spike arrives:
        ratio between x(n) and x(n-2) used to switch to positive spike
        detection.

        @values 1 to 32767 */

   int16_t                  rmc_gain_step_dB;
   /**< Gain step size used for gain ramping up/down.

        @values -11520 to 0 */

   uint32_t                 rmc_peak_length;
   /**< Length of the negative/positive peaks.

        @values 2 to 48000 */

   uint32_t                 rmc_click_tail_length;
   /**< Length of the negative/positive tail after peaks.

        @values 3 to 480000 */

   uint32_t                 rmc_total_neg_mute_length;
   /**< Length of the total muting time for a negative spike.

        @values 5 to 480000 */

   uint32_t                 rmc_total_pos_mute_length;
   /**< Length of the total muting time for a positive spike.

        @values 5 to 480000 */

   uint32_t                 rmc_next_pos_decay_length;
   /**< When still in negative spike detection and a positive spike arrives:
        length of the muting time that must be extended.

        @values 0 to 480000 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_rmc_cfg_param_v1_t */

/** @addtogroup afe_module_speaker_prot
@{ */
/** ID of the feedforward Speaker Protection module, which supports the
    following parameter IDs:
     - #AFE_PARAM_ID_SPKR_PROT_CONFIG
     - #AFE_PARAM_ID_ENABLE

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SPEAKER_PROTECTION

    @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the Speaker Protection module using
       #AFE_PORT_CMD_SET_PARAM_V2 with #AFE_MODULE_SPEAKER_PROTECTION,
       including both parameters, #AFE_PARAM_ID_SPKR_PROT_CONFIG and
       #AFE_PARAM_ID_ENABLE.
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port when necessary using #AFE_PORT_CMD_DEVICE_STOP (the
       AFE destroys all speaker protection-related information).
    @par
    This module is accepted only in the Configuration state of the port (i.e.,
    after AFE_MODULE_AUDIO_DEV_INTERFACE and before AFE_PORT_CMD_DEVICE_START.
    @par
    The Speaker Protection module is supported only on a 16-bit mono or stereo
    Rx port running at a sampling rate of 48000 Hz. @newpage
*/
#define AFE_MODULE_SPEAKER_PROTECTION                               0x00010209

/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION to configure
    for the feedforward speaker protection algorithm. Both
    #AFE_PORT_CMD_SET_PARAM_V2 and #AFE_PORT_CMD_GET_PARAM_V2 can use this
    parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SPKR_PROT_CONFIG

    @apr_msgpayload{afe_spkr_prot_cfg_param_v1_t}
    @table{weak__afe__spkr__prot__cfg__param__v1__t} @newpage
*/
#define AFE_PARAM_ID_SPKR_PROT_CONFIG                                 0x0001020a

/** Version information used to handle future additions to
    AFE_PARAM_ID_SPKR_PROT_CONFIG configuration (for backward compatibility).
*/
#define AFE_API_VERSION_SPKR_PROT_CONFIG                            0x1

/** Length of the excursion transfer function. */
#define AFE_SPKR_PROT_EXCURSION_TF_LEN                                512

/** @} */ /* end_addtogroup afe_module_speaker_prot */

typedef struct afe_spkr_prot_cfg_param_v1_t afe_spkr_prot_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_spkr_prot_cfg_param_v1_t
@{ */
/* Configuration structure for the AFE_MODULE_SPEAKER_PROTECTION
    module (version 1).
*/
struct afe_spkr_prot_cfg_param_v1_t
{
   uint32_t       spkr_prot_minor_version;
   /**< Minor version used to track speaker protection module
        configuration.

        @values #AFE_API_VERSION_SPKR_PROT_CONFIG */

   int16_t        win_size;
   /**< Analysis and synthesis window size (nWinSize).

        @values 1024, 512, 256 samples */

   int16_t        margin;
   /**< Allowable margin for excursion prediction (in L16Q15 format). This is a
        control parameter to allow for overestimation of peak excursion. */

   int16_t        spkr_exc_limit;
   /**< Speaker excursion limit (in L16Q15 format). */

   int16_t        spkr_resonance_freq;
   /**< Resonance frequency of the speaker; used to define a frequency range
        for signal modification.

        @values 0 to 2000 Hz */

   int16_t        lim_thresh;
   /**< Threshold of the hard limiter; used to prevent overshooting beyond a
        signal level that was set by the limiter prior to speaker protection.

        @values 0 to 32767 */

   int16_t        hpf_cut_off_freq;
   /**< High pass filter cutoff frequency.

        @values 100, 200, 300 Hz */

   int16_t        hpf_enable;
   /**< Specifies whether the high pass filter is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int16_t        reserved;
   /**< This field must be set to zero. */

   int32_t        amp_gain;
   /**< Amplifier gain (in L32Q15 format). This is the RMS voltage at the
        loudspeaker when a 0 dBFS tone is played in the digital domain. */

   int16_t        excursion_tf[AFE_SPKR_PROT_EXCURSION_TF_LEN];
   /**< Array for the excursion transfer function. The peak excursion of the
        loudspeaker diaphragm is measured in millimeters for 1 Vrms sine tone
        at all FFT bin frequencies.

        @values Q15 format */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_spkr_prot_cfg_param_v1_t */

/** @addtogroup afe_module_aanc
@{ */
/** ID of the Adaptive ANC (AANC) module, which supports the following
    parameter IDs:
    @if OEM_only
     - #AFE_PARAM_ID_AANC_PORT_CONFIG
     - #AFE_PARAM_ID_AANC_CFG1
     - #AFE_PARAM_ID_AANC_CFG2
     - #AFE_PARAM_ID_AANC_PROXIMITY_DETECTION
     - #AFE_PARAM_ID_AANC_STATS
     - #AFE_PARAM_ID_SB_CODEC_REG_CFG
     - #AFE_PARAM_ID_ENABLE
    @endif
    @if ISV_only
     - #AFE_PARAM_ID_AANC_PORT_CONFIG
     - #AFE_PARAM_ID_AANC_CFG1
     - #AFE_PARAM_ID_AANC_CFG2
     - #AFE_PARAM_ID_SB_CODEC_REG_CFG
     - #AFE_PARAM_ID_ENABLE
    @endif

    @apr_hdr_fields
    Opcode -- AFE_MODULE_AANC

    @detdesc
    The commands sent to this module are used to configure and enable the
    AANC algorithm in the aDSP. The algorithm is not enabled until all of
    the above parameters are passed via #AFE_PORT_CMD_SET_PARAM_V2.
    @par
    After the algorithm is enabled, only one of the following parameter IDs
    is allowed to be sent:
    - #AFE_PARAM_ID_AANC_CFG2
    - #AFE_PARAM_ID_ENABLE (includes disable) @newpage
*/
#define AFE_MODULE_AANC                   0x00010214

/** ID of the parameter used by #AFE_MODULE_AANC to configure the port for the
    Adaptive ANC algorithm. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this
    parameter ID.

    @apr_msgpayload{afe_aanc_port_cfg_param_v1_t}
    @table{weak__afe__aanc__port__cfg__param__v1__t}
*/
#define AFE_PARAM_ID_AANC_PORT_CONFIG   0x00010215

/** Version information used to handle future additions to
    AFE_PARAM_ID_AANC_PORT_CONFIG configuration (for backward compatibility).
*/
#define AFE_API_VERSION_AANC_PORT_CONFIG 0x1

/** Enumeration for indicating if a channel is unused. */
#define AANC_TX_MIC_UNUSED              0

/** Enumeration for indicating if a channel contains voice samples. */
#define AANC_TX_VOICE_MIC               1

/** Enumeration for indicating if a channel contains error mic samples. */
#define AANC_TX_ERROR_MIC               2

/** Enumeration for indicating if a channel contains noise mic samples. */
#define AANC_TX_NOISE_MIC               3

/** Enumeration for setting the maximum number of channels per device.
    @newpage */
#define AFE_PORT_MAX_CHANNEL_CNT        0x8

/** @} */ /* end_addtogroup afe_module_aanc */

typedef struct afe_aanc_port_cfg_param_v1_t afe_aanc_port_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_port_cfg_param_v1_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_PORT_CONFIG parameter of
    AFE_MODULE_AANC.
*/
struct afe_aanc_port_cfg_param_v1_t
{
   uint32_t       aanc_port_cfg_minor_version;
   /**< Minor version used to track AANC module source port configuration.

        @values #AFE_API_VERSION_AANC_PORT_CONFIG */

   uint32_t       tx_port_sample_rate;
   /**< Sampling rate of the source Tx port.

        @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */

   uint8_t        tx_port_channel_map[AFE_PORT_MAX_CHANNEL_CNT];
   /**< Array of channel mapping for the Tx port signal carrying Noise (X),
        Error (E), and Voice (V) signals.

        @values
        - #AANC_TX_MIC_UNUSED
        - #AANC_TX_VOICE_MIC
        - #AANC_TX_ERROR_MIC
        - #AANC_TX_NOISE_MIC @tablebulletend */

   uint16_t       tx_port_num_channels;
   /**< Number of channels on the source Tx port. 

         @values - 1 to AFE_PORT_MAX_CHANNEL_CNT */

   uint16_t       rx_path_ref_port_id;
   /**< Port ID of the Rx path reference signal.
   
        @values See <i>Supported Hardware Ports</i> for the applicable
                Chapter @xref{chp:portIDs} */

   uint32_t       ref_port_sample_rate;
   /**< Sampling rate of the reference port.

        @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_port_cfg_param_v1_t */

/** @addtogroup afe_module_aanc
@{ */
/** ID of the parameter used by #AFE_MODULE_AANC to configure static
    configuration parameters for the Adaptive ANC algorithm. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

  @if OEM_only
    There are two versions of the payload. Version 2 includes version 1 plus
    feedback gates on the feedback path and static path.
  @endif

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_AANC_CFG1

    @apr_msgpayload{afe_aanc_cfg1_param_v1_t}
    @table{weak__afe__aanc__cfg1__param__v1__t}

  @if OEM_only
    @apr_msgpayload{afe_aanc_cfg1_param_v2_t}
    @table{weak__afe__aanc__cfg1__param__v2__t} @newpage
  @endif
*/
#define AFE_PARAM_ID_AANC_CFG1   0x00010216

/** Version information used to handle future additions to
    AFE_PARAM_ID_AANC_CFG1 processing (for backward compatibility).
*/
#define AFE_API_VERSION_AANC_CFG1 0x2

/** Enumeration for indicating the maximum length of the IIR filter. */
#define ADAP_ANC_IIR_MAX_FILT_LEN         24

/** Enumeration for indicating the maximum length of the prefilter. @newpage */
#define ADAP_ANC_PREFILT_MAX_FILT_LEN     5

/** @} */ /* end_addtogroup afe_module_aanc */

typedef struct afe_aanc_cfg1_param_v2_t afe_aanc_cfg1_param_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_cfg1_param_v2_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_CFG1 parameter of
    AFE_MODULE_AANC. New features added in the ver 2 are as follows:

    1) Feedback gate (Feedback path)
    2) Feedback gate (Static path)
*/
struct afe_aanc_cfg1_param_v2_t
{
   uint32_t       aanc_cfg1_minor_version;
   /**< Minor version used to track AANC module static configuration.

        @values #AFE_API_VERSION_AANC_CFG1 */

   uint32_t       frame_size;
   /**< Input frame size for the voice, error, noise, and Rx path signal.

        @values 80, 160 ,240 */

   int32_t        ad_gain_default;
   /**< Default adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   uint16_t       ad_skip_k;
   /**< Skip K samples from the start of the frame.

        @values 0 to 240 */

   uint16_t       vad_gate_hist_len;
   /**< Length of the energy estimate history buffer (for minimum statistics).

        @values 1 to 1024 */

   int32_t        vad_gate_hist_init_val;
   /**< Initial value for the energy history buffer.

        @values 0 to 32767 */

   uint16_t       prefilt_biquad_iir_num_len;
   /**< Prefilter biquad IIR filter; length of the numerator coefficient.

        @values 1 to 5 */

   uint16_t       prefilt_biquad_iir_deno_len;
   /**< Prefilter biquad IIR filter; length of the denominator coefficient.

        @values 1 to 5 */

   int32_t        prefilt_biquad_iir_num[ADAP_ANC_PREFILT_MAX_FILT_LEN];
   /**< Prefilter biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        prefilt_biquad_iir_deno[ADAP_ANC_PREFILT_MAX_FILT_LEN];
   /**< Prefilter biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint16_t       spath_biquad_iir_num_len;
   /**< Speaker transfer function biquad IIR filter; length of the numerator
        coefficient.

        @values 1 to 24 */

   uint16_t       spath_biquad_iir_deno_len;
   /**< Speaker transfer function biquad IIR filter; length of the denominator
        coefficient.

        @values 1 to 24 */

   int32_t        spath_biquad_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker transfer function biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */


   int32_t        spath_biquad_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker transfer function biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint16_t       wfilt_biquad_iir_num_len;
   /**< Adaptive Least Mean Square (LMS) biquad IIR filter; length of the
        numerator coefficient.

        @values 1 to 24 */

   uint16_t       wfilt_biquad_iir_deno_len;
   /**< Adaptive LMS biquad IIR filter; length of the denominator coefficient.

        @values 1 to 24 */

   int32_t        wfilt_biquad_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Adaptive LMS biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        wfilt_biquad_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Adaptive LMS biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint32_t       fb_gate_static_enable;
   /**< Specifies whether to enable the feedback gate on the static path.

        @values
        - 0 -- Disabled
        - 1 -- Enabled

        If disabled, this field completely frees memory and bypasses
        computation. */

   uint32_t       fb_gate_sample_frequency;
   /**< Sample frequency of the feedback gate. This frequency is static; it is
        related to memory requirements.

        @values 8000, 16000 Hz */

   uint16_t       fb_gate_fpath_iir_num_len;
   /**< Feedback path IIR filter for the feedback gate; length of the
        numerator coefficient.

        @values 1 to 24 */

   uint16_t       fb_gate_fpath_iir_deno_len;
   /**< Feedback path IIR filter for the feedback gate; length of the
        denominator coefficient.

        @values 1 to 24 */

   int32_t        fb_gate_fpath_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Feedback Path IIR filter for the feedback gate; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        fb_gate_fpath_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Feedback Path IIR filter for the feedback gate; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint16_t       fb_gate_spath_iir_num_len;
   /**< Speaker path IIR filter for the feedback gate; length of the numerator
        coefficient.

        @values 1 to 24 */

   uint16_t       fb_gate_spath_iir_deno_len;
   /**< Speaker path IIR filter for the feedback gate; length of the
        denominator coefficient.

        @values 1 to 24 */

   int32_t        fb_gate_spath_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker path IIR filter for the feedback gate; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        fb_gate_spath_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker path IIR filter for the feedback gate; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg1_param_v2_t */

typedef struct afe_aanc_cfg1_param_v1_t afe_aanc_cfg1_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_cfg1_param_v1_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_CFG1 parameter of
    AFE_MODULE_AANC.
*/
struct afe_aanc_cfg1_param_v1_t
{
   uint32_t       aanc_cfg1_minor_version;
   /**< Minor version used to track AANC module static configuration.

        @values #AFE_API_VERSION_AANC_CFG1 */

   uint32_t       frame_size;
   /**< Input frame size for the voice, error, noise, and Rx path signal.

        @values 80, 160, 240 */

   int32_t        ad_gain_default;
   /**< Default adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   uint16_t       ad_skip_k;
   /**< Skip K samples from the start of the frame.

        @values 0 to 240 */

   uint16_t       vad_gate_hist_len;
   /**< Length of the energy estimate history buffer (for minimum statistics).

        @values 1 to 1024 */

   int32_t        vad_gate_hist_init_val;
   /**< Initial value for the energy history buffer.

        @values 0 to 32767 */

   uint16_t       prefilt_biquad_iir_num_len;
   /**< Prefilter biquad IIR filter; length of the numerator coefficient.

        @values 1 to 5 */

   uint16_t       prefilt_biquad_iir_deno_len;
   /**< Prefilter biquad IIR filter; length of the denominator coefficient.

        @values 1 to 5 */

   int32_t        prefilt_biquad_iir_num[ADAP_ANC_PREFILT_MAX_FILT_LEN];
   /**< Prefilter biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        prefilt_biquad_iir_deno[ADAP_ANC_PREFILT_MAX_FILT_LEN];
   /**< Prefilter biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint16_t       spath_biquad_iir_num_len;
   /**< Speaker transfer function biquad IIR filter; length of the numerator
        coefficient.

        @values 1 to 24 */

   uint16_t       spath_biquad_iir_deno_len;
   /**< Speaker transfer function biquad IIR filter; length of the denominator
        coefficient.

        @values 1 to 24 */

   int32_t        spath_biquad_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker transfer function biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */


   int32_t        spath_biquad_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Speaker transfer function biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   uint16_t       wfilt_biquad_iir_num_len;
   /**< Adaptive Least Mean Square (LMS) biquad IIR filter; length of the
        numerator coefficient.

        @values 1 to 24 */

   uint16_t       wfilt_biquad_iir_deno_len;
   /**< Adaptive LMS biquad IIR filter; length of the denominator coefficient.

        @values 1 to 24 */

   int32_t        wfilt_biquad_iir_num[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Adaptive LMS biquad IIR filter; numerator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        wfilt_biquad_iir_deno[ADAP_ANC_IIR_MAX_FILT_LEN];
   /**< Adaptive LMS biquad IIR filter; denominator coefficient.

        @values -32768 to 32767 (in Q2.14 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg1_param_v1_t */

/** @addtogroup afe_module_aanc
@{ */
/** ID of the parameter used by #AFE_MODULE_AANC to set dynamic configuration
    parameters for the Adaptive ANC algorithm. Only #AFE_PORT_CMD_SET_PARAM_V2
    can use this parameter ID.

  @if OEM_only
    There are three versions of the payload. In addition to version 1:
    - Version 2 provides a block gate.
    - Version 3 provides features such as maximum noise gate, wind gate,
      and saturation gate. This version also includes improvements in the noise
      gate and block gate parameters.
    - Version 4 provides feedback gates on the feedback and static paths.
  @endif

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_AANC_CFG2

    @apr_msgpayload{afe_aanc_cfg1_param_v2_t}
    @table{weak__afe__aanc__cfg1__param__v2__t}

  @if OEM_only
    @apr_msgpayload{afe_aanc_cfg2_param_v2_t}
    Version 2 includes version 1 plus the block gate parameters.
    @tablens{weak__afe__aanc__cfg2__param__v2__t}

    @apr_msgpayload{afe_aanc_cfg2_param_v3_t}
    Version 3 includes the following enhancements:
    @par
    Updated features:
      -  Noise gate
      -  Block gate
    @par
    New features:
      -  Maximum noise gate
      -  Saturation gate
      -  Proximity detector
      -  Wind gate
    
    @tablens{weak__afe__aanc__cfg2__param__v3__t}

    @apr_msgpayload{afe_aanc_cfg2_param_v4_t}
    Version 4 includes feedback gate parameters.
    @tablens{weak__afe__aanc__cfg2__param__v4__t}
  @endif
*/
#define AFE_PARAM_ID_AANC_CFG2   0x00010217

/** Version information used to handle future additions to
    AFE_PARAM_ID_AANC_CFG2 processing (for backward compatibility). @newpage
*/
#define AFE_API_VERSION_AANC_CFG2 0x4

/** Algorithm feature for wind gate, corresponding to bit 0 in the features
    word in wnd_gate_enable of afe_aanc_cfg2_param_v3_t.
 */
#define ADANC_WND_GATE     (1 << 0)

/** Algorithm feature for wind detection, corresponding to bit 1 in the
    features word in wnd_gate_enable of afe_aanc_cfg2_param_v3_t. @newpage
*/
#define ADANC_WND_DETECT   (1 << 1)

/** @} */ /* end_addtogroup afe_module_aanc */

typedef struct afe_aanc_cfg2_param_v4_t afe_aanc_cfg2_param_v4_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_cfg2_param_v4_t
@{ */
struct afe_aanc_cfg2_param_v4_t
{
   uint32_t       aanc_cfg2_minor_version;
   /**< Minor version used to track AANC module dynamic configuration.

        @values #AFE_API_VERSION_AANC_CFG2 */

   uint16_t       adapt_anc_enable;
   /**< Specifies whether adaptive AANC is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       alc_enable;
   /**< Specifies whether the adaptive level controller is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       pre_filt_enable;
   /**< Specifies whether the prefilter is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       rx_factor_enable;
   /**< Specifies whether the Rx energy factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       vad_factor_enable;
   /**< Specifies whether the voice activity detection factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       noise_gate_enable;
   /**< Specifies whether the noise gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        ad_alpha;
   /**< Learning rate.

        @values -32768 to 32767 (in Q8.8 format) */

   int32_t        ad_delta_g2_bound;
   /**< Absolute maximum of delta G2.

        @values 0 to 32767 (in Q2.14 format) */

   int32_t        ad_gain_bound[2];
   /**< Minimum and maximum values for the adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        alc_cfg_sm_beta;
   /**< Adaptive level controller smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_ftarget;
   /**< Adaptive level controller gain curve target).

        @values 0 to 32767 (in Q1.15 format */

   int32_t        alc_cfg_fthresh;
   /**< Adaptive level controller gain curve threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_sm_beta;
   /**< Rx gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh1;
   /**< Rx gate curve threshold 1.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh2;
   /**< Rx gate curve threshold 2.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        vad_gate_cfg_fthresh1;
   /**< Voice activity detection gate curve threshold 1.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        vad_gate_cfg_fthresh2;
   /**< Voice activity detection gate curve threshold 2.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        noise_gate_cfg_thresh;
   /**< Noise gate threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_trstep;
   /**< Noise gate transition step.

        @values 0 to 32767 (in Q1.15 format) */

   uint16_t       block_gate_enable;
   /**< Specifies whether the block gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       block_offset_enable;
   /**< Specifies whether the block offset is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        block_gate_cfg_sm_beta;
   /**< Block gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_discount_factor;
   /**< Block gate discount factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_weight_factor;
   /**< Block gate weighting factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_vad_threshold;
   /**< Block gate Rx VAD threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_offset_factor;
   /**< Factor for generating an offset.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_thresh2;
   /**< Noise gate threshold.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_thresh2targetgain;
   /**< Safe target gain.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_discount_gain_threshold;
   /**< Threshold on ANC gain that determines the dynamic discount factor.

        @values -32768 to 32767 (in Q13 format) */

   int32_t        block_gate_cfg_err_limit_factor;
   /**< Block gate safe target gain.

        @values -32768 to 32767 (in Q13 format) */

   int32_t        wnd_gate_enable;
   /**< Wind noise detection feature.
   
        Bit 0 is used to enable the gate, and bit 1 is used to enable
        detection.

        @values
        - 0 -- No wind detection computation and no wind gain adjustment
        - #ADANC_WND_GATE (1) -- Both wind gate gain adjustment and wind
          detection computation are enabled
        - #ADANC_WND_DETECT (2) -- Only wind detection computation is enabled
        - (ADANC_WND_GATE | ADANC_WND_DETECT) (3) -- Both wind gate gain
          adjustment and wind detection computation are enabled
          @tablebulletend */

   int32_t        wnd_tran_step;
   /**< Wind noise transition step.

        @values -32768 to 32767 (in Q2.14 format) */

   int32_t        wnd_min_gain;
   /**< Minimum gain when WND is detected.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        wnd_hangover;
   /**< Hangover before declaring no wind after a detection.

        @values 0 to 2147483647 */

   int32_t        wnd_sec_mic;
   /**< Choice of secondary mic for wind noise detection.

        @values 0 to 2 */

   int32_t        wnd_cov_eps;
   /**< Small initialization constant for the covariance, per sample.

        @values 0 to 2147483647 */

   int32_t        wnd_det_th[2];
   /**< Lower and upper thresholds for wind measurement.

        @values 0 to 2147483647 */

   int32_t        wnd_detect_thresh_l32q31;
   /**< Wind detection threshold.

        @values 0 to 2147483647 */

   int32_t        wnd_silent_thresh_l32q0;
   /**< Wind silence threshold.

        @values 0 to 2147483647 */

   int16_t        wnd_c_alph;
   /**< Smoothing alpha of the covariance statistics.

        @values 0 to 32767 */

   int16_t        wnd_cov_bit_shf;
   /**< Right bit shift for correction before converting to int32.

        @values -32 to 62 */

   int16_t        wnd_ws_alph_inc;
   /**< Smoothing alpha of the wind score when wind increases.

        @values 0 to 32767 */

   int16_t        wnd_ws_alph_dec;
   /**< Smoothing alpha of the wind score when wind decreases.

        @values 0 to 32767 */

   int16_t        wnd_boost_s16q10;
   /**< Boosting self standard deviation for wind determination.

        @values 0 to 32767 */

   int16_t        wnd_fact_s16q15;
   /**< Percentage of low frequency standard deviation in wind discrimination.

        @values 0 to 32767 */

   int32_t        sat_gate_enable;
   /**< Specifies whether the saturation gate is enabled.

        @values
        - 0 -- Off
        - 1 -- On @tablebulletend */

   int32_t        sat_gate_cfg_pcm_thresh;
   /**< Threshold for a PCM sample before saturation (typically 2^15-1).

        @values 0 to 65535 */

   int32_t        sat_gate_cfg_count_thresh;
   /**< Threshold count to determine if saturation occurs.

        @values 0 to 2147483647 */

   int32_t        sat_gate_cfg_gain_thresh;
   /**< Threshold on gain to determine if saturation occurs.

        @values 0 to 32767 */

   int32_t        sat_gate_cfg_hangover_len;
   /**< Length of hangover frames when saturation is detected.

        @values 0 to 2147483647 */

   int32_t        sat_gate_cfg_trans_step;
   /**< Gain reduction delta when saturation is detected.

        @values 0 to 2147483647 (in Q2.14 format) */

   int32_t        sat_gate_cfg_min_gain;
   /**< Lower limit for the gain transition target when saturation is detected.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        prox_gate_enable;
   /**< Flag used to enable the proximity detector feature.

        @values
        - 0 -- False == Off
        - 1 -- True == On @tablebulletend */

   int32_t        prox_gate_trans_step;
   /**< Gain reduction delta when proximity is not detected.

        @values 0 to 2147483647 (in Q2.14 format) */

   int32_t        prox_gate_min_gain;
   /**< Lower limit for gain reduction.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        prox_gate_trigger_hangover;
   /**< Hangover before the proximity detector flag is accepted.

        @values 0 to 2147483647 */

   int32_t        fb_gate_dynamic_enable;
   /**< Specifies whether the feedback gate can be dynamically enabled
        (turned on or off while AANC is running).

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        fb_gate_criteria_type;
   /**< Type of normalization criteria for the feedback gate correlation
        method.

        @values
        - 0 -- Fully normalized with error and noise
        - 1 -- Half normalized with error
        - 2 -- Half normalized with noise
        - 3 -- Correlation @tablebulletend */

   int32_t        fb_gate_threshold;
   /**< Threshold to compare against the feedback criteria.

        @values 0 to 2147483648 (in Q24.8 format) */

   int32_t        fb_gate_sm_beta1;
   /**< Smoothing beta to smooth the XX, XE, and EE energies.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        fb_gate_sm_beta2;
   /**< Smoothing beta to smooth XE/sqrt(XX*EE).

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        fb_gate_rx_discount_factor;
   /**< Factor multiplied with the Rx power for subtraction from
        correlation.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        fb_gate_hangover;
   /**< Hangover frames when feedback is detected.

        @values 0 to 32768 (in Q16 format) */

   int32_t        fb_gate_trans_step;
   /**< Gain reduction delta when feedback is detected.

        @values 0 to 32768 (in Q2.14 format) */

   int32_t        fb_gate_min_gain;
   /**< Lower limit for the gain transition target when feedback is detected.

        @values 0 to 32767 (in Q3.13 format) */

   int32_t        static_gate_enable;
   /**< Specifies whether the output gain is increased each frame incrementally
        to the default gain.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        static_gate_trans_step;
   /**< Transition-up step in static ANC mode.

        @values 0 to 32768 (in Q2.14 format) */

   int32_t        noise_gate_cfg_min_gain;
   /**< Noise gate minimum gain.

        @values 0 to 32767 (in Q3.13 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg2_param_v4_t */

typedef struct afe_aanc_cfg2_param_v3_t afe_aanc_cfg2_param_v3_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_cfg2_param_v3_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_CFG2 parameter of AFE_MODULE_AANC. */
/* Version 3 comprises the following updated and new features.
        Updated features:
      -  Noise gate
      -  Block gate
    New features:
      -  Maximum noise gate
      -  Saturation gate
      -  Proximity detector
      -  Wind gate
*/
struct afe_aanc_cfg2_param_v3_t
{
   uint32_t       aanc_cfg2_minor_version;
   /**< Minor version used to track AANC module dynamic configuration.

        @values #AFE_API_VERSION_AANC_CFG2 */

   uint16_t       adapt_anc_enable;
   /**< Specifies whether Adaptive AANC is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       alc_enable;
   /**< Specifies whether the adaptive level controller is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       pre_filt_enable;
   /**< Specifies whether the prefilter is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       rx_factor_enable;
   /**< Specifies whether the Rx energy factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       vad_factor_enable;
   /**< Specifies whether the voice activity detection factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       noise_gate_enable;
   /**< Specifies whether the noise gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        ad_alpha;
   /**< Learning rate.

        @values -32768 to 32767 (in Q8.8 format) */

   int32_t        ad_delta_g2_bound;
   /**< Absolute maximum of delta G2.

        @values 0 to 32767 (in Q2.14 format) */

   int32_t        ad_gain_bound[2];
   /**< Minimum and maximum values for the adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        alc_cfg_sm_beta;
   /**< Adaptive level controller smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_ftarget;
   /**< Adaptive level controller gain curve target.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_fthresh;
   /**< Adaptive level controller gain curve threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_sm_beta;
   /**< Rx gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh1;
   /**< Rx gate curve threshold 1.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh2;
   /**< Rx gate curve threshold 2.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        vad_gate_cfg_fthresh1;
   /**< Voice activity detection gate curve threshold 1.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        vad_gate_cfg_fthresh2;
   /**< Voice activity detection gate curve threshold 2.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        noise_gate_cfg_thresh;
   /**< Noise gate threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_trstep;
   /**< Noise gate transition step.

        @values 0 to 32767 (in Q1.15 format) */

   uint16_t       block_gate_enable;
   /**< Specifies whether the block gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       block_offset_enable;
   /**< Specifies whether the block offset is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        block_gate_cfg_sm_beta;
   /**< Block gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_discount_factor;
   /**< Block gate discount factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_weight_factor;
   /**< Block gate weighting factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_vad_threshold;
   /**< Block gate Rx VAD threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_offset_factor;
   /**< Factor for generating an offset.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_thresh2;
   /**< Noise gate threshold.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_thresh2targetgain;
   /**< Safe target gain.

        @values -32768 to 32767 (in Q1.13 format) */

   int32_t        block_gate_cfg_discount_gain_threshold;
   /**< Threshold on ANC gain that determines the dynamic discount factor.

        @values -32768 to 32767 (in Q1.13 format) */

   int32_t        block_gate_cfg_err_limit_factor;
   /**< Block gate safe target gain.

        @values -32768 to 32767 (in Q1.13 format) */

   int32_t        wnd_gate_enable;
   /**< Wind noise detection feature.

        Bit 0 is used to enable the gate, and bit 1 is used to enable
        detection.

        @values
        - 0 -- No wind detection computation and no wind gain adjustment
        - #ADANC_WND_GATE (1) -- Both wind gate gain adjustment and wind
          detection computation are enabled
        - #ADANC_WND_DETECT (2) -- Only wind detection computation is enabled
        - (ADANC_WND_GATE | ADANC_WND_DETECT) (3) -- Both wind gate gain
          adjustment and wind detection computation are enabled
          @tablebulletend */

   int32_t        wnd_tran_step;
   /**< Wind noise transition step.

        @values -32768 to 32767 (in Q2.14 format)*/

   int32_t        wnd_min_gain;
   /**< Minimum gain when wind is detected.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        wnd_hangover;
   /**< Hangover before declaring no wind after a detection.

        @values 0 to 2147483647 */

   int32_t        wnd_sec_mic;
   /**< Choice of a secondary mic for wind noise detection.

        @values 0 to 2 */

   int32_t        wnd_cov_eps;
   /**< Small initialization constant for the co-variance, per sample.

        @values 0 to 2147483647 */

   int32_t        wnd_det_th[2];
   /**< Lower and upper thresholds for wind measurement.

        @values 0 to 2147483647 */

   int32_t        wnd_detect_thresh_l32q31;
   /**< Wind detection threshold.

        @values 0 to 2147483647 */

   int32_t        wnd_silent_thresh_l32q0;
   /**< Wind silence threshold.

        @values 0 to 2147483647 */

   int16_t        wnd_c_alph;
   /**< Smoothing of the covariance statistics.

        @values 0 to 32767 */

   int16_t        wnd_cov_bit_shf;
   /**< Right bit shift for correction before converting to int32.

        @values -32 to 62 */

   int16_t        wnd_ws_alph_inc;
   /**< Smoothing of the wind score when wind increases.

        @values 0 to 32767 */

   int16_t        wnd_ws_alph_dec;
   /**< Smoothing of the wind score when wind decreases.

        @values 0 to 32767 */

   int16_t        wnd_boost_s16q10;
   /**< Boosting self-standard deviation for wind determination.

        @values 0 to 32767 */

   int16_t        wnd_fact_s16q15;
   /**< Percentage of low frequency standard deviation in wind discrimination.

        @values 0 to 32767 */

   int32_t        sat_gate_enable;
   /**< Specifies whether the saturation gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        sat_gate_cfg_pcm_thresh;
   /**< Threshold for a PCM sample before saturation (typically 2^15-1).

        @values 0 to 65535 */

   int32_t        sat_gate_cfg_count_thresh;
   /**< Threshold count to determine if saturation occurs.

        @values 0 to 2147483647 */

   int32_t        sat_gate_cfg_gain_thresh;
   /**< Threshold on gain to determine if saturation occurs.

        @values 0 to 32767 */

   int32_t        sat_gate_cfg_hangover_len;
   /**< Length of hangover frames when saturation is detected.

        @values 0 to 2147483647 */

   int32_t        sat_gate_cfg_trans_step;
   /**< Gain reduction delta when saturation is detected.

        @values 0 to 2147483647 (in Q2.14 format) */

   int32_t        sat_gate_cfg_min_gain;
   /**< Lower limit for the gain transition target when saturation is
        detected.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        prox_gate_enable;
   /**< Flag used to enable the proximity detector feature.

        @values
        - 0 -- FALSE == Off
        - 1 -- TRUE == On @tablebulletend */

   int32_t        prox_gate_trans_step;
   /**< Gain reduction delta when proximity is not detected.

        @values 0 to 2147483647 (in Q2.14 format) */

   int32_t        prox_gate_min_gain;
   /**< Lower limit for gain reduction.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        prox_gate_trigger_hangover;
   /**< Hangover before the proximity detector flag is accepted.

        @values 0 to 2147483647 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg2_param_v3_t */

typedef struct afe_aanc_cfg2_param_v2_t afe_aanc_cfg2_param_v2_t;

#include "adsp_begin_pack.h"

/** @cond OEM_only */
/** @weakgroup weak_afe_aanc_cfg2_param_v2_t
@{ */
/* Structure for the Adaptive ANC dynamic configuration parameters. */
/* Version 2 comprises version 1 plus the block gate parameters.
*/
struct afe_aanc_cfg2_param_v2_t
{
   uint32_t       aanc_cfg2_minor_version;
   /**< Minor version used to track AANC module dynamic
        configuration (CFG2).

        @values #AFE_API_VERSION_AANC_CFG2 */

   uint16_t       adapt_anc_enable;
   /**< Specifies whether Adaptive AANC is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       alc_enable;
   /**< Specifies whether the adaptive level controller is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       pre_filt_enable;
   /**< Specifies whether prefilter is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       rx_factor_enable;
   /**< Specifies whether the Rx energy factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       vad_factor_enable;
   /**< Specifies whether the voice activity detection factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       noise_gate_enable;
   /**< Specifies whether the noise gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        ad_alpha;
   /**< Learning rate.

        @values -32768 to 32767 (in Q8.8 format) */

   int32_t        ad_delta_g2_bound;
   /**< Absolute maximum of delta G2.

        @values 0 to 32767 (in Q2.14 format) */

   int32_t        ad_gain_bound[2];
   /**< Minimum and maximum values for the adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        alc_cfg_sm_beta;
   /**< Adaptive level controller smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_ftarget;
   /**< Adaptive level controller gain curve target.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_fthresh;
   /**< Adaptive level controller gain curve threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_sm_beta;
   /**< Rx gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh1;
   /**< Rx gate curve threshold 1.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh2;
   /**< Rx gate curve threshold 2.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        vad_gate_cfg_fthresh1;
   /**< Voice activity detection gate curve threshold 1.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        vad_gate_cfg_fthresh2;
   /**< Voice activity detection gate curve threshold 2.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        noise_gate_cfg_thresh;
   /**< Noise gate threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_trstep;
   /**< Noise gate transition step.

        @values 0 to 32767 (in Q1.15 format) */

   uint16_t       block_gate_enable;
   /**< Specifies whether the block gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       block_offset_enable;
   /**< Specifies whether the block offset is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        block_gate_cfg_sm_beta;
   /**< Block gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_discount_factor;
   /**< Block gate discount factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_weight_factor;
   /**< Block gate weighting factor.

        @values -32768 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_vad_threshold;
   /**< Block gate Rx VAD threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        block_gate_cfg_rx_offset_factor;
   /**< Factor for generating an offset.

        @values -32768 to 32767 (in Q1.15 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg2_param_v2_t */
/** @endcond */

typedef struct afe_aanc_cfg2_param_v1_t afe_aanc_cfg2_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_cfg2_param_v1_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_CFG2 parameter of
    AFE_MODULE_AANC.
*/
struct afe_aanc_cfg2_param_v1_t
{
   uint32_t       aanc_cfg2_minor_version;
   /**< Minor version used to track AANC module dynamic
        configuration (CFG2).

        @values #AFE_API_VERSION_AANC_CFG2 */

   uint16_t       adapt_anc_enable;
   /**< Specifies whether Adaptive AANC is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       alc_enable;
   /**< Specifies whether the adaptive level controller is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       pre_filt_enable;
   /**< Specifies whether the prefilter is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       rx_factor_enable;
   /**< Specifies whether the Rx energy factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       vad_factor_enable;
   /**< Specifies whether the voice activity detection factor is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t       noise_gate_enable;
   /**< Specifies whether the noise gate is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t        ad_alpha;
   /**< Learning rate.

        @values -32768 to 32767 (in Q8.8 format) */

   int32_t        ad_delta_g2_bound;
   /**< Absolute maximum of delta G2.

        @values 0 to 32767 (in Q2.14 format) */

   int32_t        ad_gain_bound[2];
   /**< Minimum and maximum values for the adaptive gain.

        @values -32768 to 32767 (in Q3.13 format) */

   int32_t        alc_cfg_sm_beta;
   /**< Adaptive level controller smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_ftarget;
   /**< Adaptive level controller gain curve target.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        alc_cfg_fthresh;
   /**< Adaptive level controller gain curve threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_sm_beta;
   /**< Rx gate smoothing beta.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh1;
   /**< Rx gate curve threshold 1.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        rx_gate_cfg_fthresh2;
   /**< Rx gate curve threshold 2.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        vad_gate_cfg_fthresh1;
   /**< Voice activity detection gate curve threshold 1.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        vad_gate_cfg_fthresh2;
   /**< Voice activity detection gate curve threshold 2.

        @values 0 to 32767 (in Q8.8 format) */

   int32_t        noise_gate_cfg_thresh;
   /**< Noise gate threshold.

        @values 0 to 32767 (in Q1.15 format) */

   int32_t        noise_gate_cfg_trstep;
   /**< Noise gate transition step.

        @values 0 to 32767 (in Q1.15 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_cfg2_param_v1_t */

/** @cond OEM_only */
/** @addtogroup afe_module_aanc
@{ */
/** ID of the parameter used by #AFE_MODULE_AANC to configure proximity
    sensor information at runtime. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this
    parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_AANC_PROXIMITY_DETECTION

    @apr_msgpayload{afe_aanc_proxy_det_cfg_param_v1_t }
    @tablens{weak__afe__aanc__proxy__det__cfg__param__v1__t}
*/
#define AFE_PARAM_ID_AANC_PROXIMITY_DETECTION   0x00010247

/** Version information used to handle future additions to
    AFE_PARAM_ID_AANC_PROXIMITY_DETECTION processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_AANC_PROXIMITY_DETECTION   0x1

/** @} */ /* end_addtogroup afe_module_aanc */

/* Structure for the adap ANC proximity dynamic config parameters. */
typedef struct afe_aanc_proxy_det_cfg_param_v1_t afe_aanc_proxy_det_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_proxy_det_cfg_param_v1_t
@{ */
/* Structure for the AFE_PARAM_ID_AANC_PROXIMITY_DETECTION parameter of
   AFE_MODULE_AANC. */
/** Provides information to the AANC algorithm regarding the
    proximity sensor status.
*/
struct afe_aanc_proxy_det_cfg_param_v1_t
{
   uint32_t    aanc_prox_det_minor_version;
   /**< Minor version used to track AANC module proximity detector
        configuration.

        @values #AFE_API_VERSION_AANC_PROXIMITY_DETECTION */

   int32_t     prox_detect_flag;
   /**< Specifies whether the proximity detector flag is enabled.

        @values
        - 0 -- Disabled; the device is next to the ear
        - 1 -- Enabled; prox_gate_enable (in afe_aanc_cfg2_param_v3_t) is set
               to TRUE @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_proxy_det_cfg_param_v1_t */
/** @endcond */

/** @weakgroup weakb_afe_cmd_remcore_hw_vote_req_values
@{ */
//lpass_core_hw_block_id define
/** Hardware block ID is invalid. */
#define AFE_LPASS_CORE_HW_BLOCK_ID_NONE                        0

/** Hardware block is a BSTC manager. */
#define AFE_LPASS_CORE_HW_BLOCK_ID_BSTC_MGR                    1

/** Hardware block is an audio-video timer. */
#define AFE_LPASS_CORE_HW_BLOCK_ID_AVTIMER                     2

/** @} */ /* end_weakgroup weak_weakb_afe_cmd_remcore_hw_vote_req_values */

/** @ingroup afe_cmd_remcore_hw_vote_req
    Handles audio-video timer (avtimer) and BTSC vote requests from
    clients.

  @apr_hdr_fields
    Opcode -- AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST

  @apr_msgpayload{afe_cmd_remote_lpass_core_hw_vote_request}
    @table{weak__afe__cmd__remote__lpass__core__hw__vote__request}

  @description
    Clients can use this command to request the LPASS core hardware module be
    enabled. Remote clients can access the LPASS core hardware module only
    after this vote request.
    @par
    The AFE returns a handle to the LPASS core hardware module in response to
    this command.
    @par
    A client must ensure that it votes the LPASS core hardware module only
    once. If the client sends multiple vote commands, the same LPASS core
    hardware module handle is sent in response.
    @par
    After processing finishes, the client must issue
    #AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST to release the LPASS core
    hardware module.

  @return
    #AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST

  @dependencies
    None. @newpage

  @inputfile{group__weakb__afe__cmd__remcore__hw__vote__req__values.tex}
*/
#define AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST            0x000100f4

typedef struct afe_cmd_remote_lpass_core_hw_vote_request afe_cmd_remote_lpass_core_hw_vote_request;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cmd_remote_lpass_core_hw_vote_request
@{ */
/* Payload of the AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST command.
*/
struct afe_cmd_remote_lpass_core_hw_vote_request
{
   uint32_t  hw_block_id;
   /**< ID of the hardware block.

        @values
        - #AFE_LPASS_CORE_HW_BLOCK_ID_NONE
        - #AFE_LPASS_CORE_HW_BLOCK_ID_BSTC_MGR
        - #AFE_LPASS_CORE_HW_BLOCK_ID_AVTIMER @tablebulletend */

   char client_name[8];
   /**< Name of the client.

        @values Valid string with a maximum of 8 characters */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cmd_remote_lpass_core_hw_vote_request */


/** @ingroup afe_rsp_remcore_hw_vote_req
    In response to the #AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST command, the
    AFE sends a handle to the LPASS core hardware module.

  @apr_hdr_fields
   Opcode -- AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST

  @apr_msgpayload{afe_cmd_rsp_remote_lpass_core_hw_vote_request}
    @table{weak__afe__cmd__rsp__remote__lpass__core__hw__vote__request}

  @description
    After processing finishes, the client must issue
    #AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST to release the LPASS core
    hardware module.

  @return
    None.

  @dependencies
    #AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST must have been sent by the
    client.
*/
#define AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST        0x000100f5

typedef struct afe_cmd_rsp_remote_lpass_core_hw_vote_request afe_cmd_rsp_remote_lpass_core_hw_vote_request;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cmd_rsp_remote_lpass_core_hw_vote_request
@{ */
/* Payload of the AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST command.
*/
struct afe_cmd_rsp_remote_lpass_core_hw_vote_request
{
   uint32_t client_handle;
   /**< Handle of the client.

        @values Valid uint32 number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cmd_rsp_remote_lpass_core_hw_vote_request */


/** @ingroup afe_rsp_remcore_hw_devote_req
  Handles client requests to disable the LPASS core hardware module.
  The client must send a valid LPASS core hardware module handle.

  @apr_hdr_fields
   Opcode -- AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST

  @apr_msgpayload{afe_cmd_remote_lpass_core_hw_devote_request}
    @table{weak__afe__cmd__remote__lpass__core__hw__devote__request}

  @return
    None.

  @dependencies
    The #AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST must have been sent by the
    client.
*/
#define AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST            0x000100f6

typedef struct afe_cmd_remote_lpass_core_hw_devote_request afe_cmd_remote_lpass_core_hw_devote_request;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cmd_remote_lpass_core_hw_devote_request
@{ */
/* Payload of the AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST command.
*/
struct afe_cmd_remote_lpass_core_hw_devote_request
{
   uint32_t  hw_block_id;
   /**< ID of the hardware block.

        @values
        - #AFE_LPASS_CORE_HW_BLOCK_ID_NONE
        - #AFE_LPASS_CORE_HW_BLOCK_ID_BSTC_MGR
        - #AFE_LPASS_CORE_HW_BLOCK_ID_AVTIMER @tablebulletend */

   uint32_t client_handle;
   /**< Handle of the client.

        @values Valid uint32 number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cmd_remote_lpass_core_hw_devote_request */


/** @cond OEM_only */
/** @addtogroup afe_module_aanc
@{ */
/** ID of the parameter used by #AFE_MODULE_AANC to log AANC algorithm
    tuning variables.
    This parameter ID is currently used for logging the algorithm internal
    variables.

    There are two versions of this parameter ID. Version 2 includes feedback
    gate information.

    @apr_msgpayload{afe_aanc_stats_v1_t}
    @table{weak__afe__aanc__stats__v1__t}

    @apr_msgpayload{afe_aanc_stats_v2_t}
    @table{weak__afe__aanc__stats__v2__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_AANC_STATS                        0x0001024A

/** Version information used to handle future additions to
    AFE_PARAM_ID_AANC_STATS processing (for backward compatibility).
*/
#define AFE_API_VERSION_AANC_STATS                           0x2

/** Maximum number of wind channels allowed for wind detection
    calculation. @newpage */
#define AFE_AANC_WND_MAX_CHANNELS                            2

/** @} */ /* end_addtogroup afe_module_aanc */

typedef struct afe_aanc_stats_v2_t afe_aanc_stats_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_stats_v2_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_AANC_STATS parameter (version 2).
    New features:
    - Feedback gate information.
*/
struct afe_aanc_stats_v2_t
{
      uint32_t       aanc_stats_minor_version;
      /**< Minor version used to track AANC statistics. Currently, the
           supported version is 2.

           @values #AFE_API_VERSION_AANC_STATS */

      uint32_t        frame_duration_in_ms;
      /**< Frame duration in milliseconds for AANC variables.

           @values Valid uint32 number */

      uint32_t        frame_num;
      /**< Frame number of the AANC variables.

           @values Valid uint32 number

           This field is reset to zero after crossing the maximum limit for
           uint32 variables. */

      int32_t        ad_gain;
      /**< Adaptive gain value.

           @values Valid int32 number (in Q3.13 format) */

      int32_t        delta_g;
      /**< Delta G from the adaptive algorithm.

           @values Valid int32 number (in Q3.13 format) */

      int32_t        out_gain;
      /**< Output gain, which is computed as adaptive gain * noise gate factor.

           @values Valid int32 number (in Q3.13 format) */

      int32_t        alc_data_sm_peak_x;
      /**< ALC smoothed signal peak.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        alc_data_gain_x;
      /**< ALC gain.

           @values Valid uint32 number */

      int32_t        rx_gate_data_sm_peak_x;
      /**< Rx gate-smoothed signal peak.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        rx_gate_data_factor;
      /**< Rx power estimate learning rate gate factor.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        vad_gate_data_detect_ratio;
      /**< Voice detection ratio.

           @values Valid int32 number (in Q8.8 format) */

      int32_t        vad_gate_data_factor;
      /**< Learning rate gate factor.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        vad_gate_data_min_eng;
      /**< Minimum energy for noise estimation.

           @values Valid int32 number */

      int32_t        vad_gate_data_cur_eng;
      /**< Current energy for noise estimation.

           @values Valid int32 number */

      int32_t        noise_gate_data_nng_state;
      /**< State of the noise gate.

           @values Valid int32 number */

      int32_t        noise_gate_data_nng_factor;
      /**< Factor multiplied with ANC gain to generate the final gain.

           @values Valid int32 number (in Q3.13 format) */

      int32_t        block_gate_data_est_x;
      /**< Peak estimate on X.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        block_gate_data_est_e;
      /**< Peak estimate on E.

           @values Valid int32 number (in Q1.15 format) */

      int32_t        block_gate_data_sm_est_x;
      /**< Smoothed peak estimate on X.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        block_gate_data_sm_est_e;
      /**< Smoothed peak estimate on E.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        block_gate_data_gate_delta;
      /**< Delta factor to be added to the filtered LMS.

           @values Valid int32 number (in Q14 format) */

      int32_t        block_gate_data_gate_offset;
      /**< Offset that is proportional to the estimate X and ratio.

           @values Valid int32 number (in Q14 format) */

      int32_t        sat_gate_data_nsg_sat_count;
      /**< Number of saturations in the current frame.

           @values Valid int32 number */

      int32_t        sat_gate_data_nsg_sat_hangover;
      /**< Hangover counter, which is positive if the saturation gate is
           active.

           @values Valid int32 number */

      int32_t        wnd_gate_data_wnd_state;
      /**< State of the wind gate.

           @values Valid int32 number */

      int32_t        prox_gate_cfg_prox_detect_flag;
      /**< Proximity detector flag.

           @values Valid int32 number */

      int32_t        prox_gate_data_prox_state;
      /**< Proximity state.

           @values Valid int32 number */

      int32_t        prox_gate_data_prox_hangover_count;
      /**< Proximity gate hangover count.

           @values Valid int32 number */

      int32_t        std[AFE_AANC_WND_MAX_CHANNELS];
      /**< Standard deviation of the low-pass data.

           @values Valid int32 number */

      int32_t        var_f[AFE_AANC_WND_MAX_CHANNELS];
      /**< Non-low-pass variance.

           @values Valid int32 number */

      int32_t        std_f[AFE_AANC_WND_MAX_CHANNELS];
      /**< Non-low-pass standard deviation.

           @values Valid int32 number */

      int32_t        std_o[AFE_AANC_WND_MAX_CHANNELS];
      /**< Lowest standard deviation of the other channel (low pass).

           @values Valid int32 number */

      int32_t        wind_meas[AFE_AANC_WND_MAX_CHANNELS];
      /**< Measure of the raw wind strength.

           @values Valid int32 number */

      int32_t        wind_sc_q30[AFE_AANC_WND_MAX_CHANNELS];
      /**< Indicates the wind score (the probability of wind detection).
           A higher number means there is more probability.

           @values Valid int32 number (in Q30 format) */

      int16_t        pri_wind_1q14[AFE_AANC_WND_MAX_CHANNELS];
      /**< Probability that wind is present in the primary channel(criteria 1).

           @values Valid uint16 number (in Q14 format) */

      int16_t        pri_wind_2q14[AFE_AANC_WND_MAX_CHANNELS];
      /**< Probability that wind is present in the primary channel(criteria 2).

           @values Valid int16 number (in Q14 format) */

      int16_t        pri_wind_q15[AFE_AANC_WND_MAX_CHANNELS];
      /**< Probability that wind is present in the channel.

           @values Valid int16 number (in Q15 format) */

      int32_t        wind_sc_adj_q30[AFE_AANC_WND_MAX_CHANNELS];
      /**< Wind score, adjusted for all bad correlations.

           @values Valid int16 number (in Q30 format) */

      int32_t        wind_sc_adj_sm_q30[AFE_AANC_WND_MAX_CHANNELS];
      /**< Wind score, adjusted for all bad correlations and smoothed.

           @values Valid int32 number (in Q30 format)*/

      int16_t        wnd_gate_data_wind_detect_flag;
      /**< Wind detection flag.

           @values Valid int16 number */

      int16_t        wnd_channels;
      /**< Number of wind channels.

           @values Valid int16 number */

      int32_t        fb_gate_corr_xe;
      /**< Correlation score for XE.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_var_xx;
      /**< Variance of XX to normalize XY.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_var_ee;
      /**< Variance of EE to normalize XY.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_corr_sm_xe;
      /**< Smooth correlation score for XE.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_var_sm_xx;
      /**< Smooth variance for XX.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_var_sm_ee;
      /**< Smooth variance for EE.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_criteria;
      /**< Final criteria computed from smooth score and variance.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_hangover_counts;
      /**< Frame counts to turn off ANC when feedback is detected.

           @values Valid int32 number (in Q1.30 format) */

      int32_t        fb_gate_rx_eng;
      /**< Rx mean square energy.

           @values Valid int32 number (in Q1.30 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_stats_v2_t */

typedef struct afe_aanc_stats_v1_t afe_aanc_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_aanc_stats_v1_t
@{ */
/*     Configuration structure for the
    AFE_PARAM_ID_AANC_STATS parameter (version 1).
*/
struct afe_aanc_stats_v1_t
{
       uint32_t       aanc_stats_minor_version;
       /**< Minor version used to track AANC statistics. Currently, the
            supported version is 1.

            @values #AFE_API_VERSION_AANC_STATS */

       uint32_t        frame_duration_in_ms;
       /**< Frame duration in milliseconds for AANC variables.

            @values Valid uint32 number */

       uint32_t        frame_num;
       /**< Frame number of the AANC variables. This field is reset to zero
            after crossing the maximum limit for uint32 variables.

            @values Valid uint32 number */

       int32_t        ad_gain;
       /**< Adaptive gain value.

            @values Valid int32 number (in Q3.13 format) */

       int32_t        delta_g;
       /**< Delta G from the adaptive algorithm.

            @values Valid int32 number (in Q3.13 format) */

       int32_t        out_gain;
       /**< Output gain, which is computed as adaptive gain * noise gate
            factor.

            @values Valid int32 number (in Q3.13 format) */

       int32_t        alc_data_sm_peak_x;
       /**< ALC smoothed signal peak. 

            @values Valid int32 number (in Q1.15 format) */

       int32_t        alc_data_gain_x;
       /**< ALC gain.

            @values Valid uint32 number */

       int32_t        rx_gate_data_sm_peak_x;
       /**< Rx gate-smoothed signal peak.

            @values Valid int32 number (in Q1.15 format) */

       int32_t        rx_gate_data_factor;
       /**< Rx power estimate learning rate gate factor.

            @values Valid int32 number (in Q1.15 format) */

       int32_t        vad_gate_data_detect_ratio;
       /**< Voice detection ratio.

            @values Valid int32 number (in Q8.8 format) */

       int32_t        vad_gate_data_factor;
       /**< Learning rate gate factor.

            @values Valid int32 number (in Q1.15 format) */

       int32_t        vad_gate_data_min_eng;
       /**< Minimum energy for noise estimation.

            @values Valid int32 number */

       int32_t        vad_gate_data_cur_eng;
       /**< Current energy for noise estimation.

            @values Valid int32 number */

       int32_t        noise_gate_data_nng_state;
       /**< State of the noise gate.

            @values Valid int32 number */

       int32_t        noise_gate_data_nng_factor;
       /**< Factor multiplied with ANC gain to generate the final gain.

            @values Valid int32 number (in Q3.13 format) */

       int32_t        block_gate_data_est_x;
       /**< Peak estimate on X.

            @values Valid int32 number (in Q1.15 format) */

       int32_t        block_gate_data_est_e;
       /**< Peak estimate on E.

            @values Valid int32 number (in Q1.15 format) */

       int32_t        block_gate_data_sm_est_x;
       /**< Smoothed peak estimate on X.

            @values Valid int32 number (in Q1.30 format) */

       int32_t        block_gate_data_sm_est_e;
       /**< Smoothed peak estimate on E.

            @values Valid int32 number (in Q1.30 format) */

       int32_t        block_gate_data_gate_delta;
       /**< Delta factor to be added to the filtered LMS.

            @values Valid int32 number (in Q14 format) */

       int32_t        block_gate_data_gate_offset;
       /**< Offset that is proportional to the X estimate and ratio.

            @values Valid int32 number (in Q14 format) */

       int32_t        sat_gate_data_nsg_sat_count;
       /**< Number of saturations in the current frame.

            @values Valid int32 number */

       int32_t        sat_gate_data_nsg_sat_hangover;
       /**< Hangover counter, which is positive if the saturation gate is
            active.

            @values Valid int32 number */

       int32_t        wnd_gate_data_wnd_state;
       /**< State of the wind gate.

            @values Valid int32 number */

       int32_t        prox_gate_cfg_prox_detect_flag;
       /**< Proximity detector flag.

            @values Valid int32 number */

       int32_t        prox_gate_data_prox_state;
       /**< Proximity state.

            @values Valid int32 number */

       int32_t        prox_gate_data_prox_hangover_count;
       /**< Proximity gate hangover count.

            @values Valid int32 number */

       int32_t        std[AFE_AANC_WND_MAX_CHANNELS];
       /**< Standard deviation of the low-pass data.

            @values Valid int32 number */

       int32_t        var_f[AFE_AANC_WND_MAX_CHANNELS];
       /**< Non-low-pass variance.

            @values Valid int32 number */

       int32_t        std_f[AFE_AANC_WND_MAX_CHANNELS];
       /**< Non-low-pass standard deviation.

            @values Valid int32 number */

       int32_t        std_o[AFE_AANC_WND_MAX_CHANNELS];
       /**< Lowest standard deviation of the other channel (low pass).

            @values Valid int32 number */

       int32_t        wind_meas[AFE_AANC_WND_MAX_CHANNELS];
       /**< Measure of the raw wind strength.

            @values Valid int32 number */

       int32_t        wind_sc_q30[AFE_AANC_WND_MAX_CHANNELS];
       /**< Indicates the wind score (the probability of wind detection).
            A higher number means there is more probability.

            @values Valid int32 number (in Q30 format) */

       int16_t        pri_wind_1q14[AFE_AANC_WND_MAX_CHANNELS];
       /**< Probability that wind is present in the primary channel.

            @values Valid uint16 number (in Q14 format) */

       int16_t        pri_wind_2q14[AFE_AANC_WND_MAX_CHANNELS];
       /**< Probability that wind is present in the secondary channel.

            @values Valid int16 number (in Q14 format) */

       int16_t        pri_wind_q15[AFE_AANC_WND_MAX_CHANNELS];
       /**< Probability that wind is present in the channel.

            @values Valid int16 number (in Q15 format) */

       int32_t        wind_sc_adj_q30[AFE_AANC_WND_MAX_CHANNELS];
       /**< Wind score, adjusted for all bad correlations.

            @values Valid int16 number (in Q30 format) */

       int32_t        wind_sc_adj_sm_q30[AFE_AANC_WND_MAX_CHANNELS];
       /**< Wind score, adjusted for all bad correlations and smoothed.

            @values Valid int32 number (in Q30 format) */

       int16_t        wnd_gate_data_wind_detect_flag;
       /**< Wind detection flag.

            @values Valid int16 number */

       int16_t        wnd_channels;
       /**< Number of wind channels.

            @values Valid int16 number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_aanc_stats_v1_t */
/** @endcond */


/** @addtogroup afe_module_aanc
@{ */
/** ID of the parameter used by #AFE_MODULE_AANC to configure codec registers
    through the SLIMbus interface. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this
    parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SB_CODEC_REG_CFG

    @apr_msgpayload{afe_sb_codec_reg_cfg_v1_t}
    @table{weak__afe__sb__codec__reg__cfg__v1__t}
*/
#define AFE_PARAM_ID_SB_CODEC_REG_CFG   0x00010218

/** Version information used to handle future additions to
    AFE_PARAM_ID_SB_CODEC_REG_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_SB_CODEC_REG_CFG 0x1

/** Enumeration for the AANC_REG_LPF_FF_FB (CDC_ANCn_LPF_B1_CTL) register. */
#define AANC_REG_LPF_FF_FB               0x1

/** Enumeration for the AANC_REG_LPF_COEFF_MSB (CDC_ANCn_LPF_B2_CTL) register. */
#define AANC_REG_LPF_COEFF_MSB           0x2

/** Enumeration for the AANC_REG_LPF_COEFF_LSB (CDC_ANCn_LPF_B3_CTL) register. */
#define AANC_REG_LPF_COEFF_LSB           0x3

typedef struct afe_sb_codec_reg_cfg_v1_t afe_sb_codec_reg_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sb_codec_reg_cfg_v1_t
@{ */
/* Structure for AFE_PARAM_ID_SB_CODEC_REG_CFG parameter through SLIMbus
    interface; used by AFE_MODULE_AANC.
*/
struct afe_sb_codec_reg_cfg_v1_t
{
   uint32_t sb_ve_cfg_minor_version;
   /**< Minor version used to track SLIMbus codec register configuration.

        @values #AFE_API_VERSION_SB_CODEC_REG_CFG */

   uint32_t device_enum_addr_lsw;
   /**< Lower 32 bits of the SLIMbus slave device's 48-bit enumeration
        address. */

   uint32_t device_enum_addr_msw;
   /**< Upper 16 bits of the SLIMbus slave device's 48-bit enumeration
        address.

        @values
        - Bits 15 to 0 contain device_enum_addr_msw.
        - Bits 31 to 16 must be set to zero. @tablebulletend */

   uint32_t reg_logical_addr;
   /**< Logical address of the codec register to/from which the aDSP will
        write/read. */

   uint32_t reg_field_type;
   /**< Type of register field that points to this codec register read/write
        operation.

        @values
        - #AANC_REG_LPF_FF_FB
        - #AANC_REG_LPF_COEFF_MSB
        - #AANC_REG_LPF_COEFF_LSB @tablebulletend */

   uint32_t reg_field_bit_mask;
   /**< Register bitmask to specify the bitfields that must be accessed from
        the aDSP through this read/write operation. */

   uint16_t reg_bit_width;
   /**< Bit width of the register.

        @values 8, 16, 32 */

   uint16_t reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sb_codec_reg_cfg_v1_t */
/** @} */ /* end_addtogroup afe_module_aanc */


/** @ingroup afe_cmd_register_rt_port_dr
    Registers a real-time port driver with the AFE service for a given port.

  @apr_hdr_fields
    Opcode -- AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER

  @apr_msgpayload{afe_service_cmd_register_rt_port_driver_t}
    @table{weak__afe__service__cmd__register__rt__port__driver__t}

  @detdesc
    The APR destination address and port number are obtained from the header of
    this packet and are used for sending different events.
    @par
    By registering, the customer applications receive
    #AFE_EVENT_RT_PROXY_PORT_STATUS events indicating when to start and stop
    the PCM exchange flow.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/
#define AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER                     0x000100E0

/* Structure for the AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER command. */
typedef struct afe_service_cmd_register_rt_port_driver_t    afe_service_cmd_register_rt_port_driver_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_cmd_register_rt_port_driver_t
@{ */
/* Payload of the AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER command,
    which registers a real-time port driver with the AFE service.
*/
struct afe_service_cmd_register_rt_port_driver_t
{
    uint16_t                  port_id;
    /**< Port ID with which the real-time driver exchanges data (registers for
         events).

         @values #AFE_PORT_ID_RT_PROXY_PORT_RANGE_START to
                 #AFE_PORT_ID_RT_PROXY_PORT_RANGE_END */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_cmd_register_rt_port_driver_t */

/** @ingroup afe_cmd_unregister_rt_port_dr
    Unregisters a real-time port driver from the AFE service for a given port.

  @apr_hdr_fields
    Opcode -- AFE_SERVICE_CMD_UNREGISTER_RT_PORT_DRIVER

  @apr_msgpayload{afe_service_cmd_unregister_rt_port_driver_t}
    @table{weak__afe__service__cmd__unregister__rt__port__driver__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    #AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER must have been successfully
    processed.
*/
#define AFE_SERVICE_CMD_UNREGISTER_RT_PORT_DRIVER                      0x000100E1

/* Structure for the AFE_SERVICE_CMD_UNREGISTER_RT_PORT_DRIVER command. */
typedef struct afe_service_cmd_unregister_rt_port_driver_t    afe_service_cmd_unregister_rt_port_driver_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_cmd_unregister_rt_port_driver_t
@{ */
/* Payload of the AFE_SERVICE_CMD_UNREGISTER_RT_PORT_DRIVER command,
    which unregisters a real-time port driver from the AFE service.
*/
struct afe_service_cmd_unregister_rt_port_driver_t
{
    uint16_t                  port_id;
    /**< Port ID from which the real-time driver unregisters for events.

         @values #AFE_PORT_ID_RT_PROXY_PORT_RANGE_START to
                 #AFE_PORT_ID_RT_PROXY_PORT_RANGE_END */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_cmd_unregister_rt_port_driver_t */

/** @addtogroup afe_evt_rt_proxy_port_status
@{ */
/** Sent when an event is reported from the AFE service to a real-time driver.

  @apr_hdr_fields
    Opcode -- AFE_EVENT_RT_PROXY_PORT_STATUS

  @apr_msgpayload{afe_event_rt_proxy_port_status_t}
    @table{weak__afe__event__rt__proxy__port__status__t}

  @detdesc
    This event communicates information about the real-time proxy port to the
    client. A Start or Stop event indicates that data transfer begins or stops.
    For a client to receive this notification, it must register using
    #AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER.
    @par
    For a Start/Stop event, and depending on the value of port_id, the client
    starts/stops sending either filled buffers when the port_id is set for the
    mic path or empty buffers when the port_id is set for the speaker path.
    After acknowledging the Port Stop command, all buffers are returned by the
    AFE service.
    @par
    Low and high watermark events are sent based on the values of the
    corresponding thresholds configured using the using the
    #AFE_PARAM_ID_RT_PROXY_CONFIG parameter ID in
    #AFE_MODULE_AUDIO_DEV_INTERFACE.
    - In the source path, a low/high watermark event is sent when the application
      is too slow/fast in sending data.
    - In the sink path, a low watermark event indicates the application is
      consuming data at a faster rate than the AFE is getting from the Rx path,
      and a high watermark event indicates that the application is consuming
      slowly.
    @par
    @keep{4}
    Although these events can be used to adjust the rate at which applications
    produce or consume data, that is not the goal. These events are added for
    debugging, and they should not be used for non-real-time applications.

  @return
    None.

  @dependencies
    #AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER.
*/
#define AFE_EVENT_RT_PROXY_PORT_STATUS                              0x00010105

/** Type of event sent when a real-time proxy port is started. */
#define AFE_EVENT_TYPE_RT_PROXY_PORT_START                           0

/** Type of event sent when a real-time proxy port is stopped. */
#define AFE_EVENT_TYPE_RT_PROXY_PORT_STOP                            1

/** Type of event sent when a low watermark is reached. */
#define AFE_EVENT_TYPE_RT_PROXY_PORT_LOW_WATER_MARK                  2

/** Type of event sent when a high watermark is reached. */
#define AFE_EVENT_TYPE_RT_PROXY_PORT_HIGH_WATER_MARK                 3

/** Invalid event. */
#define AFE_EVENT_TYPE_RT_PROXY_PORT_INVALID                         0xFFFF

/** @} */ /* end_addtogroup afe_evt_rt_proxy_port_status */

/* Structure for the AFE_EVENT_RT_PROXY_PORT_STATUS event. */
typedef struct afe_event_rt_proxy_port_status_t  afe_event_rt_proxy_port_status_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_event_rt_proxy_port_status_t
@{ */
/* Payload of the AFE_EVENT_RT_PROXY_PORT_STATUS message, which sends
    an event from the AFE service to a registered client.
*/
struct afe_event_rt_proxy_port_status_t
{
    uint16_t                  port_id;
    /**< Port ID to which the event is sent.

         @values #AFE_PORT_ID_RT_PROXY_PORT_RANGE_START to
                 #AFE_PORT_ID_RT_PROXY_PORT_RANGE_END */

    uint16_t                  event_type;
    /**< Type of event.

         @values
         - #AFE_EVENT_TYPE_RT_PROXY_PORT_START
         - #AFE_EVENT_TYPE_RT_PROXY_PORT_STOP
         - #AFE_EVENT_TYPE_RT_PROXY_PORT_LOW_WATER_MARK
         - #AFE_EVENT_TYPE_RT_PROXY_PORT_HIGH_WATER_MARK @vertspace{-28} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_event_rt_proxy_port_status_t */

/** @ingroup afe_cmd_rt_proxy_port_write
    Delivers a data buffer to the AFE service from a real-time device.

  @apr_hdr_fields
    Opcode -- AFE_PORT_DATA_CMD_RT_PROXY_PORT_WRITE_V2

  @apr_msgpayload{afe_port_data_cmd_rt_proxy_port_write_v2_t}
    @table{weak__afe__port__data__cmd__rt__proxy__port__write__v2__t}

  @detdesc
    This command is used by the client for sending the data obtained from the
    source device to the AFE. An acknowledgment is sent immediately after
    copying the data to the circular buffer.
    @par
    If incoming data does not fit in the circular buffer due to overflow, it
    overwrites a portion of the data in the existing buffer, and that data is
    lost.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    #AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER -- The following commands are to be
    sent with the port_id set as a source (Tx) real-time proxy port ID:
    - #AFE_PARAM_ID_RT_PROXY_CONFIG through #AFE_MODULE_AUDIO_DEV_INTERFACE
    - #AFE_PORT_CMD_DEVICE_START
    @par
    The physical buffer must be fully contained in a memory region that has
    been mapped to the AFE service via #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.
*/
#define AFE_PORT_DATA_CMD_RT_PROXY_PORT_WRITE_V2                    0x000100ED

/* Structure for the AFE_PORT_DATA_CMD_RT_PROXY_PORT_WRITE_V2 command. */
typedef struct afe_port_data_cmd_rt_proxy_port_write_v2_t  afe_port_data_cmd_rt_proxy_port_write_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_data_cmd_rt_proxy_port_write_v2_t
@{ */
/* Payload of the AFE_PORT_DATA_CMD_RT_PROXY_PORT_WRITE_V2 command, which
    delivers a filled buffer to the AFE service.
*/
struct afe_port_data_cmd_rt_proxy_port_write_v2_t
{
    uint16_t                  port_id;
    /**< Tx (mic) proxy port ID with which the real-time driver exchanges data.

         @values #AFE_PORT_ID_RT_PROXY_PORT_RANGE_START to
                 #AFE_PORT_ID_RT_PROXY_PORT_RANGE_END */

    uint16_t                  reserved;
    /**< This field must be set to zero. */

    uint32_t                  buffer_address_lsw;
    /**< Lower 32 bits of the 64-bit address buffer containing the data from
         the real-time source device on a client. */

    uint32_t                  buffer_address_msw;
    /**< Upper 32 bits of the 64-bit address buffer containing the data from
         the real-time source device on a client. */

    uint32_t                   mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value

         This memory map handle is returned by the aDSP through
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS. */

    uint32_t                  available_bytes;
    /**< Number of valid bytes available in the buffer (including all
         channels: number of bytes per channel = availableBytes/numChannels).

         @values > 0

         This field must be equal to the frame size specified in the
         #AFE_MODULE_AUDIO_DEV_INTERFACE command that was sent to configure this
         port. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup afe_port_data_cmd_rt_proxy_port_write_v2_t */

/** @ingroup afe_cmd_rt_proxy_port_read
    Delivers an empty data buffer to the AFE service to be filled and sent to a
    real-time device.

  @apr_hdr_fields
    Opcode -- AFE_PORT_DATA_CMD_RT_PROXY_PORT_READ

  @apr_msgpayload{afe_port_data_cmd_rt_proxy_port_read_v2_t}
    @table{weak__afe__port__data__cmd__rt__proxy__port__read__v2__t}

  @detdesc
    This command is used by the client for receiving data (from the AFE service)
    to be written to the sink device. If sufficient data is available in the
    circular buffer, data is immediately copied and an acknowledgment is sent.
    @par
    If the circular buffer does not have enough data to fill in the circular
    buffer, an underrun is detected, partial data is copied, the rest of the
    buffer is filled with zeros, and an acknowledgment is sent. @newpage

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    #AFE_SERVICE_CMD_REGISTER_RT_PORT_DRIVER -- The following commands are to be
    sent with the port_id set as a sink (Rx) real-time proxy port ID:
    - #AFE_PARAM_ID_RT_PROXY_CONFIG through #AFE_MODULE_AUDIO_DEV_INTERFACE
    - #AFE_PORT_CMD_DEVICE_START
    @par
    The physical buffer must be fully contained in a memory region that has
    been mapped to the AFE service via #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.
*/
#define AFE_PORT_DATA_CMD_RT_PROXY_PORT_READ_V2                        0x000100EE

/* Structure for the AFE_PORT_DATA_CMD_RT_PROXY_PORT_READ_V2 command. */
typedef struct afe_port_data_cmd_rt_proxy_port_read_v2_t  afe_port_data_cmd_rt_proxy_port_read_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_data_cmd_rt_proxy_port_read_v2_t
@{ */
/* Payload of the AFE_PORT_DATA_CMD_RT_PROXY_PORT_READ_V2 command, which
    delivers an empty buffer to the AFE service. On acknowledgment, data is
    filled in the buffer.
*/
struct afe_port_data_cmd_rt_proxy_port_read_v2_t
{
    uint16_t                  port_id;
    /**< Rx proxy port ID with which the real-time driver exchanges data.

         @values #AFE_PORT_ID_RT_PROXY_PORT_RANGE_START to
                 #AFE_PORT_ID_RT_PROXY_PORT_RANGE_END

         This must be an Rx (speaker) port. */

    uint16_t                  reserved;
    /**< This field must be set to zero. */

    uint32_t                  buffer_address_lsw;
    /**< Lower 32 bits of the 64-bit address containing the data sent from the
         AFE service to a real-time sink device on the client. */

    uint32_t                  buffer_address_msw;
    /**< Upper 32 bits of the 64-bit address containing the data sent from the
         AFE service to a real-time sink device on the client. */

    uint32_t                   mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value

         This memory map handle is returned by the aDSP through
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS. */

    uint32_t                  available_bytes;
    /**< Number of valid bytes available in the buffer (including all
         channels).

         @values > 0 bytes

         This field must be equal to the frame size specified in the
         #AFE_MODULE_AUDIO_DEV_INTERFACE command that was sent to configure this
         port. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup afe_port_data_cmd_rt_proxy_port_read_v2_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the Audio Device Interface module, which configures devices such as
    I2S, PCM, HDMI, SLIMbus.
    This module supports following parameter IDs:
     - #AFE_PARAM_ID_I2S_CONFIG
     - #AFE_PARAM_ID_PCM_CONFIG
     - #AFE_PARAM_ID_DIGI_MIC_CONFIG
     - #AFE_PARAM_ID_HDMI_CONFIG
     - #AFE_PARAM_ID_SPDIF_CONFIG
  @if OEM_only
     - #AFE_PARAM_ID_SIF_CONFIG
     - #AFE_PARAM_ID_SIF_MODE_CONFIG
     - #AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG
     - #AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG
  @endif
     - #AFE_PARAM_ID_CH_STATUS_CONFIG
     - #AFE_PARAM_ID_HDMI_INPUT_CONFIG
     - #AFE_PARAM_ID_INTERNAL_BT_FM_CONFIG
     - #AFE_PARAM_ID_SLIMBUS_CONFIG
     - #AFE_PARAM_ID_RT_PROXY_CONFIG
     - #AFE_PARAM_ID_PSEUDO_PORT_CONFIG
     - #AFE_PARAM_ID_AHB_CLOCK_CONFIG
     - #AFE_PARAM_ID_DEVICE_HW_DELAY
     - #AFE_PARAM_ID_LPAIF_CLK_CONFIG
     - #AFE_PARAM_ID_SPDIF_CLK_CONFIG
     - #AFE_PARAM_ID_INTERNAL_DIGIATL_CDC_CLK_CONFIG
     - #AFE_PARAM_ID_TOPO_ID

    To configure the AFE port, the client must set the port via the
    #AFE_PORT_CMD_SET_PARAM_V2 command, and fill the module ID with the
    respective parameter IDs as listed above. The client must ensure the
    codec configuration and SLIMbus interface configuration (for a SLIMbus
    device) before sending this command to the AFE.

    @apr_hdr_fields
    Opcode -- AFE_MODULE_AUDIO_DEV_INTERFACE @newpage
*/
#define AFE_MODULE_AUDIO_DEV_INTERFACE                                0x0001020C

/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the I2S interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_I2S_CONFIG

    @apr_msgpayload{afe_param_id_i2s_cfg_t}
    @table{weak__afe__param__id__i2s__cfg__t}
*/
#define AFE_PARAM_ID_I2S_CONFIG                                      0x0001020D

/** Version information used to handle future additions to
    AFE_PARAM_ID_I2S_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_I2S_CONFIG                                     0x1

/** Sample rate is 8000 Hz. */
#define AFE_PORT_SAMPLE_RATE_8K                                     8000

/** Sample rate is 16000 Hz. */
#define AFE_PORT_SAMPLE_RATE_16K                                    16000

/** Sample rate is 22050 Hz. */
#define AFE_PORT_SAMPLE_RATE_22_05K                                 22050

/** Sample rate is 24000 Hz. */
#define AFE_PORT_SAMPLE_RATE_24K                                    24000

/** Sample rate is 32000 Hz. */
#define AFE_PORT_SAMPLE_RATE_32K                                    32000

/** Sample rate is 44100 Hz. */
#define AFE_PORT_SAMPLE_RATE_44_1K                                  44100

/** Sample rate is 88200 Hz. */
#define AFE_PORT_SAMPLE_RATE_88_2K                                  88200

/** Sample rate is 48000 Hz. */
#define AFE_PORT_SAMPLE_RATE_48K                                    48000

/** Sample rate is 96000 Hz. */
#define AFE_PORT_SAMPLE_RATE_96K                                    96000

/** Sample rate is 176400 Hz.*/
#define AFE_PORT_SAMPLE_RATE_176_4K                                 176400

/** Sample rate is 192000 Hz. */
#define AFE_PORT_SAMPLE_RATE_192K                                   192000

/** Enumeration for setting the data format to PCM when PCM data is
    transmitted/received over I2S lines.
*/
#define AFE_LINEAR_PCM_DATA                                         0x0

/** Enumeration for setting the data format to Non-Linear (compressed) when
    non-linear (compressed) data is transmited/received over I2S lines.
*/
#define AFE_NON_LINEAR_DATA                                          0x1

/** Enumeration for setting the data format when PCM data packed in a 60958
    container is transmited/received over I2S lines.
*/
#define AFE_LINEAR_PCM_DATA_PACKED_60958                             0x2

/** Enumeration for setting the data format when non-linear data packed in a
    60958 container is transmited/received over I2S lines.
*/
#define AFE_NON_LINEAR_DATA_PACKED_60958                             0x3

/** Enumeration for setting the data format when PCM data is packed in the
    custom parallel audio interface format.
*/
#define AFE_LINEAR_PCM_DATA_PACKED_CUSTOM_PAO                        0x4

/** Enumeration for setting the data format when non-linear data is packed in
    the custom parallel audio interface format.
*/
#define AFE_NON_LINEAR_DATA_PACKED_CUSTOM_PAO                        0x5

/** Enumeration for setting the I2S configuration channel_mode parameter to
    serial data wire number 0 (SD0).
*/
#define AFE_PORT_I2S_SD0                                            0x1

/** Enumeration for setting the I2S configuration channel_mode parameter to
    serial data wire number 1 (SD1).
*/
#define AFE_PORT_I2S_SD1                                            0x2

/** Enumeration for setting the I2S configuration channel_mode parameter to
    serial data wire number 2 (SD2).
*/
#define AFE_PORT_I2S_SD2                                            0x3

/** Enumeration for setting the I2S configuration channel_mode parameter to
    serial data wire number 3 (SD3).
*/
#define AFE_PORT_I2S_SD3                                            0x4

/** Enumeration for setting the I2S configuration channel_mode parameter to
    SD0 and SD1.
*/
#define AFE_PORT_I2S_QUAD01                                         0x5

/** Enumeration for setting the I2S configuration channel_mode parameter to
    SD2 and SD3.
*/
#define AFE_PORT_I2S_QUAD23                                         0x6

/** Enumeration for setting the I2S configuration channel_mode parameter to
    six channels.
*/
#define AFE_PORT_I2S_6CHS                                           0x7

/** Enumeration for setting the I2S configuration channel_mode parameter to
    8 channels.
*/
#define AFE_PORT_I2S_8CHS                                           0x8

/** Enumeration for setting the I2S configuration mono_stereo parameter to
    mono.
*/
#define AFE_PORT_I2S_MONO                                           0x0

/** Enumeration for setting the I2S configuration mono_stereo parameter to
    stereo.
*/
#define AFE_PORT_I2S_STEREO                                         0x1

/** Enumeration for setting the I2S configuration ws_src parameter to
    external.
*/
#define AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL                         0x0

/** Enumeration for setting the I2S configuration ws_src parameter to
    internal. @newpage
*/
#define AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL                         0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_i2s_cfg_t afe_param_id_i2s_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_i2s_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_I2S_CONFIG parameter ID used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_i2s_cfg_t
{
    uint32_t                  i2s_cfg_minor_version;
   /**< Minor version used to track I2S configuration.

        @values #AFE_API_VERSION_I2S_CONFIG */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24, 32

         Currently, a 32-bit value is supported on the AFE Tx (mic) path only.
         The AFE acts as a pass-through module in 32-bit configuration, and no
         features or algorithms are to be enabled in this mode. Current
         algorithms do not support 32-bit format directly; therefore, this can
         be disabled or return an error when the port is running at 32-bit and
         an attempt is made to enable algorithms. */

    uint16_t                  channel_mode;
    /**< I2S lines and multichannel operation.

         @values
         - #AFE_PORT_I2S_SD0
         - #AFE_PORT_I2S_SD1
         - #AFE_PORT_I2S_SD2
         - #AFE_PORT_I2S_SD3
         - #AFE_PORT_I2S_QUAD01
         - #AFE_PORT_I2S_QUAD23
         - #AFE_PORT_I2S_6CHS
         - #AFE_PORT_I2S_8CHS @tablebulletend */

    uint16_t                  mono_stereo;
    /**< Specifies mono or stereo. This applies only when a single I2S line is
         used.

         @values
         - #AFE_PORT_I2S_MONO
         - #AFE_PORT_I2S_STEREO @tablebulletend */

    uint16_t                  ws_src;
    /**< Word select source: internal or external.

         @values
         - #AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL
         - #AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL @tablebulletend */

    uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_22_05K
         - #AFE_PORT_SAMPLE_RATE_24K
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_44_1K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_88_2K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_176_4K
         - #AFE_PORT_SAMPLE_RATE_192K

         At 44100 Hz, the I2S interface supports both PCM and compressed data
         in both the Tx direction and Rx direction.

         There is no concurrent support of a voice call when the port operates
         at 44100 Hz because of Round Trip Delay (RTD) requirements.

         The AFE and ADM must be running with same sampling rate.
         All AFE clients must be at same sampling rate (44.1 kHz) on the same
         device. This applies to other sampling rates that are either
         multiples or divisors of 44.1 kHz (e.g., 22.05 kHz, 88.2 kHz, 176.4 kHz).

         @note1hang Sampling rates of 24 kHz and 32 kHz are typically used
                    for compressed data. */

    uint16_t                   data_format;
    /**< Data format supported by the I2S interface.

         @values
         - #AFE_LINEAR_PCM_DATA
         - #AFE_NON_LINEAR_DATA
         - #AFE_LINEAR_PCM_DATA_PACKED_60958
         - #AFE_NON_LINEAR_DATA_PACKED_60958 @tablebulletend */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_i2s_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the PCM interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    Because of restrictions from the hardware, the AUX PCM interface must be
    enabled for both Rx and Tx at the same time. Rx or Tx cannot be used alone.
    For example, the primary AUX Tx PCM port must be enabled with the primary
    AUX Rx PCM port.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_PCM_CONFIG

    @apr_msgpayload{afe_param_id_pcm_cfg_t}
    @table{weak__afe__param__id__pcm__cfg__t}
*/
#define AFE_PARAM_ID_PCM_CONFIG                                      0x0001020E

/** Version information used to handle future additions to
    AFE_PARAM_ID_PCM_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_PCM_CONFIG                                     0x1

/** Enumeration for the auxiliary PCM synchronization signal provided by an
    external source.
*/
#define AFE_PORT_PCM_SYNC_SRC_EXTERNAL                              0x0

/** Enumeration for the auxiliary PCM synchronization signal provided by an
    internal source.
*/
#define AFE_PORT_PCM_SYNC_SRC_INTERNAL                              0x1

/** Enumeration for the PCM configuration aux_mode parameter, which configures
    the auxiliary PCM interface to use short synchronization.
*/
#define AFE_PORT_PCM_AUX_MODE_PCM                                   0x0

/** Enumeration for the PCM configuration aux_mode parameter, which configures
    the auxiliary PCM interface to use long synchronization.
*/
#define AFE_PORT_PCM_AUX_MODE_AUX                                   0x1

/** Enumeration for setting the PCM configuration frame to 8. */
#define AFE_PORT_PCM_BITS_PER_FRAME_8                               0x0

/** Enumeration for setting the PCM configuration frame to 16. */
#define AFE_PORT_PCM_BITS_PER_FRAME_16                              0x1

/** Enumeration for setting the PCM configuration frame to 32. */
#define AFE_PORT_PCM_BITS_PER_FRAME_32                              0x2

/** Enumeration for setting the PCM configuration frame to 64. */
#define AFE_PORT_PCM_BITS_PER_FRAME_64                              0x3

/** Enumeration for setting the PCM configuration frame to 128. */
#define AFE_PORT_PCM_BITS_PER_FRAME_128                             0x4

/** Enumeration for setting the PCM configuration frame to 256. */
#define AFE_PORT_PCM_BITS_PER_FRAME_256                             0x5

/** Enumeration for setting the PCM configuration quant_type parameter to
    A-law with no padding.
*/
#define AFE_PORT_PCM_ALAW_NOPADDING                                 0x0

/** Enumeration for setting the PCM configuration quant_type parameter to
    mu-law with no padding.
*/
#define AFE_PORT_PCM_MULAW_NOPADDING                                0x1

/** Enumeration for setting the PCM configuration quant_type parameter to
    linear with no padding.
*/
#define AFE_PORT_PCM_LINEAR_NOPADDING                               0x2

/** Enumeration for setting the PCM configuration quant_type parameter to
    A-law with padding.
*/
#define AFE_PORT_PCM_ALAW_PADDING                                   0x3

/** Enumeration for setting the PCM configuration quant_type parameter to
    mu-law with padding.
*/
#define AFE_PORT_PCM_MULAW_PADDING                                  0x4

/** Enumeration for setting the PCM configuration quant_type parameter to
    linear with padding.
*/
#define AFE_PORT_PCM_LINEAR_PADDING                                 0x5

/** Enumeration for disabling the PCM configuration ctrl_data_out_enable
    parameter. The PCM block is the only master.
*/
#define AFE_PORT_PCM_CTRL_DATA_OE_DISABLE                           0x0

/** Enumeration for enabling the PCM configuration ctrl_data_out_enable
    parameter. The PCM block shares the signal with other masters. @newpage
*/
#define AFE_PORT_PCM_CTRL_DATA_OE_ENABLE                            0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_pcm_cfg_t afe_param_id_pcm_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_pcm_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_PCM_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_pcm_cfg_t
{
    uint32_t                  pcm_cfg_minor_version;
   /**< Minor version used to track AUX PCM configuration.

        @values #AFE_API_VERSION_PCM_CONFIG */

    uint16_t                  aux_mode;
    /**< PCM synchronization setting.

         @values
         - #AFE_PORT_PCM_AUX_MODE_PCM
         - #AFE_PORT_PCM_AUX_MODE_AUX @tablebulletend */

    uint16_t                  sync_src;
    /**< Synchronization source.

         @values
         - #AFE_PORT_PCM_SYNC_SRC_EXTERNAL
         - #AFE_PORT_PCM_SYNC_SRC_INTERNAL @tablebulletend */

    uint16_t                  frame_setting;
    /**< Number of bits per frame.

         @values
         - #AFE_PORT_PCM_BITS_PER_FRAME_8
         - #AFE_PORT_PCM_BITS_PER_FRAME_16
         - #AFE_PORT_PCM_BITS_PER_FRAME_32
         - #AFE_PORT_PCM_BITS_PER_FRAME_64
         - #AFE_PORT_PCM_BITS_PER_FRAME_128
         - #AFE_PORT_PCM_BITS_PER_FRAME_256 @tablebulletend */

    uint16_t                  quant_type;
    /**< PCM quantization type.

         @values
         - #AFE_PORT_PCM_ALAW_NOPADDING
         - #AFE_PORT_PCM_MULAW_NOPADDING
         - #AFE_PORT_PCM_LINEAR_NOPADDING
         - #AFE_PORT_PCM_ALAW_PADDING
         - #AFE_PORT_PCM_MULAW_PADDING
         - #AFE_PORT_PCM_LINEAR_PADDING @tablebulletend */

    uint16_t                  ctrl_data_out_enable;
    /**< Specifies whether the PCM block shares the data-out signal to the
         drive with other masters.

         @values
         - #AFE_PORT_PCM_CTRL_DATA_OE_DISABLE
         - #AFE_PORT_PCM_CTRL_DATA_OE_ENABLE @tablebulletend */

    uint16_t                  reserved;
    /**< This field must be set to zero. */

    uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K @tablebulletend */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16 */

    uint16_t                  num_channels;
    /**< Number of channels.

         @values 1 to 4 */

    uint16_t                  slot_number_mapping[4];
    /**< Array that specifies the slot number for each channel in a
         multichannel scenario.

         @values 1 to 32

         To transfer the data at higher sample rate, use more slots.
         For example, 16 kHz data can be transferred using 8 kHz samples in
         two slots.

         The valid slot value setting must always be placed in form index 0.
         For example, use slot_number_mapping[0] for one slot, and use
         slot_number_mapping[0] and slot_number_mapping[1] for two slots.

         Unused slot_number_mapping[] must be cleared to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_pcm_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the DIGI MIC interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_DIGI_MIC_CONFIG

    @apr_msgpayload{afe_param_id_digi_mic_cfg_t}
    @table{weak__afe__param__id__digi__mic__cfg__t}
*/
#define AFE_PARAM_ID_DIGI_MIC_CONFIG                                  0x0001020F

/** Version information used to handle future additions to
    AFE_PARAM_ID_DIGI_MIC_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_DIGI_MIC_CONFIG                             0x1

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to left 0.
*/
#define AFE_PORT_DIGI_MIC_MODE_LEFT0                                0x1

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to right 0.
*/
#define AFE_PORT_DIGI_MIC_MODE_RIGHT0                               0x2

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to left 1.
*/
#define AFE_PORT_DIGI_MIC_MODE_LEFT1                                0x3

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to right 1.
*/
#define AFE_PORT_DIGI_MIC_MODE_RIGHT1                               0x4

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to stereo 0.
*/
#define AFE_PORT_DIGI_MIC_MODE_STEREO0                              0x5

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to stereo 1.
*/
#define AFE_PORT_DIGI_MIC_MODE_STEREO1                              0x6

/** Enumeration for setting the digital mic configuration channel_mode
    parameter to quad. @newpage
*/
#define AFE_PORT_DIGI_MIC_MODE_QUAD                                 0x7

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_digi_mic_cfg_t afe_param_id_digi_mic_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_digi_mic_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_DIGI_MIC_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_digi_mic_cfg_t
{
    uint32_t                  digi_mic_cfg_minor_version;
   /**< Minor version used to track DIGI MIC configuration.

        @values #AFE_API_VERSION_DIGI_MIC_CONFIG */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16 */

    uint16_t                  channel_mode;
    /**< Digital mic and multichannel operation.

         @values
         - #AFE_PORT_DIGI_MIC_MODE_LEFT0
         - #AFE_PORT_DIGI_MIC_MODE_RIGHT0
         - #AFE_PORT_DIGI_MIC_MODE_LEFT1
         - #AFE_PORT_DIGI_MIC_MODE_RIGHT1
         - #AFE_PORT_DIGI_MIC_MODE_STEREO0
         - #AFE_PORT_DIGI_MIC_MODE_STEREO1
         - #AFE_PORT_DIGI_MIC_MODE_QUAD @tablebulletend */

     uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_48K @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_digi_mic_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the HDMI interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_HDMI_CONFIG

    @apr_msgpayload{afe_param_id_hdmi_multi_chan_audio_cfg_t}
    @table{weak__afe__param__id__hdmi__multi__chan__audio__cfg__t}
*/
#define AFE_PARAM_ID_HDMI_CONFIG                                      0x00010210

/** Version information used to handle future additions to
    AFE_PARAM_ID_HDMI_CONFIG processing (for backward compatibility). @newpage
*/
#define AFE_API_VERSION_HDMI_CONFIG                                 0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_hdmi_multi_chan_audio_cfg_t afe_param_id_hdmi_multi_chan_audio_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_hdmi_multi_chan_audio_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_HDMI_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_hdmi_multi_chan_audio_cfg_t
{
   uint32_t                  hdmi_cfg_minor_version;
   /**< Minor version used to track HDMI module configuration.

        @values #AFE_API_VERSION_HDMI_CONFIG */

   uint16_t                  data_type;
    /**< Valid data type.

         @values
         - #AFE_LINEAR_PCM_DATA
         - #AFE_NON_LINEAR_DATA
         - #AFE_LINEAR_PCM_DATA_PACKED_60958
         - #AFE_NON_LINEAR_DATA_PACKED_60958 @tablebulletend */

   uint16_t                  channel_allocation;
   /**< HDMI channel allocation information for programming an HDMI frame.
        The default is 0 (Stereo).

        This information is defined in the HDMI standard, CEA 861-D
        (refer to @xhyperref{S1,[S1]}). The number of channels is also inferred
        from this parameter. */

   uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_22_05K
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_44_1K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_176_4K
         - #AFE_PORT_SAMPLE_RATE_192K

         For the HDMI interface, sampling rates 22050, 44100, and 176400 Hz
         are applicable only for compressed data (non-PCM). */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_hdmi_multi_chan_audio_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the SPDIF interface.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SPDIF_CONFIG

    @apr_msgpayload{afe_param_id_spdif_audio_cfg_t}
    @table{weak__afe__param__id__spdif__audio__cfg__t}
*/
#define AFE_PARAM_ID_SPDIF_CONFIG                                    0x00010244

/** Version information used to handle future additions to
    AFE_PARAM_ID_SPDIF_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_SPDIF_CONFIG                                 0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_spdif_audio_cfg_t afe_param_id_spdif_audio_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_spdif_audio_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SPDIF_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_spdif_audio_cfg_t
{
   uint32_t                  spdif_cfg_minor_version;
   /**< Minor version used to track SPDIF module configuration.

        @values #AFE_API_VERSION_SPDIF_CONFIG */

   uint32_t                  sample_rate;
   /**< Sampling rate of the port.

        @values
         - #AFE_PORT_SAMPLE_RATE_22_05K; for compressed use case only
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_44_1K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_88_2K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_176_4K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */

   uint16_t                  data_format;
   /**< Data format supported by the SPDIF interface.

        @values
         - #AFE_LINEAR_PCM_DATA
         - #AFE_NON_LINEAR_DATA @tablebulletend */

   uint16_t                  num_channels;
   /**< Number of channels.

        @values 1 to 2 */

   uint16_t                  bit_width;
   /**< Bit width of the sample.

        @values 16, 24 */

   uint16_t                  reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_spdif_audio_cfg_t */

/** @cond OEM_only */
/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the SIF interface.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIF_CONFIG

    @apr_msgpayload{afe_param_id_sif_cfg_t}
    @table{weak__afe__param__id__sif__cfg__t}
*/
#define AFE_PARAM_ID_SIF_CONFIG                                      0x00010250

/** Version information used to handle future additions to
    AFE_PARAM_ID_SIF_CONFIG processing (for backward compatibility). @newpage
*/
#define AFE_API_VERSION_SIF_CONFIG                                   0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_sif_cfg_t afe_param_id_sif_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_sif_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SIF_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_sif_cfg_t
{
   uint32_t                  sif_cfg_minor_version;
   /**< Minor version used to track SIF interface configuration.

        @values #AFE_API_VERSION_SIF_CONFIG */

   uint32_t                  sample_rate;
   /**< Sampling rate of the port.

        @values #AFE_PORT_SAMPLE_RATE_48K */

   uint16_t                  data_format;
   /**< Supported data type.

        @values #AFE_LINEAR_PCM_DATA */

   uint16_t                  num_channels;
   /**< Number of channels.
   
        @values 2 */

   uint16_t                  bit_width;
   /**< Bit width of the sample.

        @values 16*/

   uint16_t                  reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sif_cfg_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the SIF interface mode.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIF_MODE_CONFIG

    @apr_msgpayload{afe_param_id_sif_mode_cfg_t}
    @table{weak__afe__param__id__sif__mode__cfg__t}
*/
#define AFE_PARAM_ID_SIF_MODE_CONFIG                                  0x0001024C

/** Version information used to handle future additions to
    AFE_PARAM_ID_SIF_MODE_CONFIG processing (for backward compatibility). 
*/
#define AFE_API_VERSION_SIF_MODE_CONFIG                                   0x1

/** SIF broadcast standard is invalid. */
#define AFE_SIF_BROADCAST_STD_NONE            0

/** SIF broadcast standard is A2 (two-channel audio/sound). */
#define AFE_SIF_BROADCAST_STD_A2              1

/** SIF broadcast standard is AM. */
#define AFE_SIF_BROADCAST_STD_AM              2

/** SIF broadcast standard is BTSC. */
#define AFE_SIF_BROADCAST_STD_BTSC            3

/** SIF broadcast standard is EIAJ. */
#define AFE_SIF_BROADCAST_STD_EIAJ            4

/** SIF broadcast standard is FM mono. */
#define AFE_SIF_BROADCAST_STD_FM_MONO         5

/** SIF broadcast standard is FM radio. */
#define AFE_SIF_BROADCAST_STD_FM_RADIO        6

/** SIF broadcast standard is NICAM. */
#define AFE_SIF_BROADCAST_STD_NICAM           7

/** SIF broadcast standard is NICAM fallback. */
#define AFE_SIF_BROADCAST_STD_NICAM_FALLBACK  8

/** SIF Broadcast mode is invalid. */
#define AFE_SIF_BROADCAST_MODE_NONE           0

/** SIF Broadcast mode is mono. */
#define AFE_SIF_BROADCAST_MODE_MONO           1

/** SIF Broadcast mode is stereo. */
#define AFE_SIF_BROADCAST_MODE_STEREO         2

/** SIF Broadcast mode is dual channel A and B. */
#define AFE_SIF_BROADCAST_MODE_DUAL_CHAN_A_CHAN_B    3

/** SIF User mode is invalid. */
#define AFE_SIF_USER_MODE_NONE                0

/** SIF User mode is mono. */
#define AFE_SIF_USER_MODE_MONO                1

/** SIF User mode is stereo. */
#define AFE_SIF_USER_MODE_STEREO              2

/** SIF User mode is dual channel A. */
#define AFE_SIF_USER_MODE_DUAL_CHAN_A         3

/** SIF User mode is dual channel B. */
#define AFE_SIF_USER_MODE_DUAL_CHAN_B         4

/** SIF User mode is dual channel A and B. */
#define AFE_SIF_USER_MODE_DUAL_CHAN_A_CHAN_B  5

/** SIF User mode is Second Audio Program (SAP). @newpage*/
#define AFE_SIF_USER_MODE_SAP                 6

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_sif_mode_cfg_t afe_param_id_sif_mode_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_sif_mode_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SIF_MODE_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_sif_mode_cfg_t
{
   uint32_t                  sif_mode_cfg_minor_version;
   /**< Minor version used to track SIF mode configuration.

        @values #AFE_API_VERSION_SIF_MODE_CONFIG */

   uint16_t                  broadcast_std;
   /**< SIF broadcast standard.

        @values
         - #AFE_SIF_BROADCAST_STD_NONE
         - #AFE_SIF_BROADCAST_STD_A2
         - #AFE_SIF_BROADCAST_STD_AM
         - #AFE_SIF_BROADCAST_STD_BTSC
         - #AFE_SIF_BROADCAST_STD_EIAJ
         - #AFE_SIF_BROADCAST_STD_FM_MONO
         - #AFE_SIF_BROADCAST_STD_FM_RADIO 
         - #AFE_SIF_BROADCAST_STD_NICAM
         - #AFE_SIF_BROADCAST_STD_NICAM_FALLBACK @tablebulletend */

   uint16_t                  broadcast_mode;
   /**< SIF Broadcast mode.

        @values
         - #AFE_SIF_BROADCAST_MODE_NONE
         - #AFE_SIF_BROADCAST_MODE_MONO
         - #AFE_SIF_BROADCAST_MODE_STEREO
         - #AFE_SIF_BROADCAST_MODE_DUAL_CHAN_A_CHAN_B @tablebulletend */

   uint16_t                  user_mode;
   /**< SIF User mode.
   
        @values 
         - #AFE_SIF_USER_MODE_NONE 
         - #AFE_SIF_USER_MODE_MONO
         - #AFE_SIF_USER_MODE_STEREO
         - #AFE_SIF_USER_MODE_DUAL_CHAN_A
         - #AFE_SIF_USER_MODE_DUAL_CHAN_B
         - #AFE_SIF_USER_MODE_DUAL_CHAN_A_CHAN_B
         - #AFE_SIF_USER_MODE_SAP @tablebulletend */

   uint16_t                  reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sif_mode_cfg_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE and
    #AFE_MODULE_CUSTOM_EVENTS to configure carrier lost detection for the SIF
    interface.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG

    @apr_msgpayload{afe_param_id_sif_carrier_lost_cfg_t}
    @table{weak__afe__param__id__sif__carrier__lost__cfg__t}
*/
#define AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG                        0x0001024D

/** Version information used to handle future additions to
    AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG (for backward
    compatibility). 
*/
#define AFE_API_VERSION_SIF_CARRIER_LOST_DETECTION_CONFIG            0x1

/** SIF carrier lost detection is disabled. */
#define AFE_SIF_CARRIER_LOST_DETECTION_DISABLE        0

/** SIF carrier lost detection is enabled. @newpage */
#define AFE_SIF_CARRIER_LOST_DETECTION_ENABLE         1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_sif_carrier_lost_cfg_t afe_param_id_sif_carrier_lost_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_sif_carrier_lost_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_sif_carrier_lost_cfg_t
{
   uint32_t                  sif_carrier_lost_cfg_minor_version;
   /**< Minor version used to track SIF carrier lost configuration.

        @values #AFE_API_VERSION_SIF_CARRIER_LOST_DETECTION_CONFIG */

   uint16_t                  enable;
   /**< Specifies whether carrier lost detection is enabled for a SIF port.

        @values
         - #AFE_SIF_CARRIER_LOST_DETECTION_DISABLE
         - #AFE_SIF_CARRIER_LOST_DETECTION_ENABLE @tablebulletend */

   uint16_t                  amp_drop_rate;
   /**< Percentage of an amplitude drop.
   
        @values 1 to 100% */

   uint16_t                  time_window_ms;
   /**< Monitoring time window used to determine that a carrier is lost.
   
        @values 1 to 1000 ms */

   uint16_t                  amp_min_value;
   /**< Minimum value of amplitude used to determine that a carrier is lost.

        @values 0 to 65536 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sif_carrier_lost_cfg_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE and
    #AFE_MODULE_CUSTOM_EVENTS to configure clip detection for the SIF interface.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG

    @apr_msgpayload{afe_param_id_sif_clip_cfg_t}
    @table{weak__afe__param__id__sif__clip__cfg__t}
*/
#define AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG                        0x0001024E

/** Version information used to handle future additions to
    AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG processing (for backward
    compatibility). 
*/
#define AFE_API_VERSION_SIF_CLIP_DETECTION_CONFIG            0x1

/** SIF clip detection is disabled. */
#define AFE_SIF_CLIP_DETECTION_DISABLE        0

/** SIF clip detection is enabled. @newpage */
#define AFE_SIF_CLIP_DETECTION_ENABLE            1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_sif_clip_cfg_t afe_param_id_sif_clip_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_sif_clip_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_sif_clip_cfg_t
{
   uint32_t                  sif_clip_cfg_minor_version;
   /**< Minor version used to track SIF clip detection configuration.

        @values #AFE_API_VERSION_SIF_CLIP_DETECTION_CONFIG */

   uint16_t                  enable;
   /**< Specifies whether clip detection is enabled for a SIF port.

        @values
         - #AFE_SIF_CLIP_DETECTION_DISABLE
         - #AFE_SIF_CLIP_DETECTION_ENABLE @tablebulletend */

   uint16_t                  threshold;
   /**< Threshold value used to determine clipping.
   
        @values 1 to 100% */

   uint16_t                  num_clip_samples;
   /**< Number of samples out of the threshold value.
   
        @values 1 to 48000 (48*time_window_ms) */

   uint16_t                  time_window_ms;
   /**< Monitoring time window used to determine overmodulation.

        @values 0 to 1000 ms */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sif_clip_cfg_t */
/** @endcond */


/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to
    configure the channel status bits. Only #AFE_PORT_ID_SPDIF_RX can use this
    parameter ID.

    Channel status bits must be called after #AFE_PORT_CMD_SET_PARAM_V2
    is issued to configure the port parameter.

    This parameter ID can support dynamic updates only on the copyright bit
    (bit 2), depending on the hardware version:
    - 0 -- Software for which a copyright is asserted
    - 1 -- Software for which no copyright is asserted
    - For more details, refer to @xhyperref{S4,[S4]}

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_CHSTATUS_CONFIG

    @apr_msgpayload{afe_param_id_chstatus_cfg_t}
    @table{weak__afe__param__id__chstatus__cfg__t}
*/
#define AFE_PARAM_ID_CH_STATUS_CONFIG                           0x00010245

/** Version information used to handle future additions to
    AFE_PARAM_ID_CH_STATUS_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_CH_STATUS_CONFIG                        0x1

/* Enumeration for channel type */

/** Channel status bits for channel A. */
#define AFE_CH_STATUS_A                                         0x1

/** Channel status bits for channel B. */
#define AFE_CH_STATUS_B                                         0x2

/** Enumeration for the channel status byte size. @newpage */
#define AFE_CH_STATUS_BYTE_SIZE                                 24

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_chstatus_cfg_t afe_param_id_chstatus_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_chstatus_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_CHSTATUS_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_chstatus_cfg_t
{
   uint32_t                  ch_status_cfg_minor_version;
   /**< Minor version used to track channel status configuration.

        @values #AFE_API_VERSION_CH_STATUS_CONFIG */

   uint32_t                  ch_status_type;
   /**< Indicates whether the channel status is for channel A or B.

        @values
        - #AFE_CH_STATUS_A
        - #AFE_CH_STATUS_B @tablebulletend */

   uint8_t   ch_stat_buf[AFE_CH_STATUS_BYTE_SIZE];
   /**< 192 channel status bits for the channel.

        @values The byte ordering is the same as the ordering defined in
                IEC60958-3 (refer to @xhyperref{S4,[S4]}). */

   uint8_t   ch_stat_mask[AFE_CH_STATUS_BYTE_SIZE];
   /**< 192 channel status bitmasks for the channel.

        @values The byte ordering is the same as the ordering defined in
                IEC60958-3 (refer to @xhyperref{S4,[S4]}). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_chstatus_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to
    configure the HDMI input interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_HDMI_CONFIG

    @apr_msgpayload{afe_param_id_hdmi_input_cfg_t}
    @table{weak__afe__param__id__hdmi__input__cfg__t}
*/
#define AFE_PARAM_ID_HDMI_INPUT_CONFIG                              0x00010248

/** Version information used to handle future additions to
    AFE_PARAM_ID_HDMI_INPUT_CONFIG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_HDMI_INPUT_CONFIG                           0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_hdmi_input_cfg_t afe_param_id_hdmi_input_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_hdmi_input_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_HDMI_INPUT_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_hdmi_input_cfg_t
{
   uint32_t                  hdmi_input_cfg_minor_version;
   /**< Minor version used to track HDMI module configuration.

        @values #AFE_API_VERSION_HDMI_INPUT_CONFIG */

   uint16_t                  data_type;
    /**< Valid data type.

         @values
         - #AFE_LINEAR_PCM_DATA_PACKED_CUSTOM_PAO
         - #AFE_NON_LINEAR_DATA_PACKED_CUSTOM_PAO @tablebulletend */

   uint16_t                  num_channels;
   /**< Number of channels.

        @values 1 to 8 */

   uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_44_1K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_176_4K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_hdmi_input_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the BT or FM (RIVA) interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_INTERNAL_BT_FM_CONFIG

    @apr_msgpayload{afe_param_id_internal_bt_fm_cfg_t}
    @table{weak__afe__param__id__internal__bt__fm__cfg__t}
*/
#define AFE_PARAM_ID_INTERNAL_BT_FM_CONFIG                          0x00010211

/** Version information used to handle future additions to
    AFE_PARAM_ID_INTERNAL_BT_FM_CONFIG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_INTERNAL_BT_FM_CONFIG                         0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_internal_bt_fm_cfg_t afe_param_id_internal_bt_fm_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_internal_bt_fm_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_INTERNAL_BT_FM_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_internal_bt_fm_cfg_t
{
    uint32_t                  bt_fm_cfg_minor_version;
   /**< Minor version used to track BT and FM configuration.

        @values #AFE_API_VERSION_INTERNAL_BT_FM_CONFIG */

    uint16_t                  num_channels;
    /**< Number of channels.

         @values
         - 1 (only for BTSCO)
         - 2 (only for FM and A2DP) @tablebulletend */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16 */

    uint32_t                  sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K (only for BTSCO)
         - #AFE_PORT_SAMPLE_RATE_16K (only for BTSCO)
         - #AFE_PORT_SAMPLE_RATE_48K (FM and A2DP) @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_internal_bt_fm_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the SLIMbus interface using a shared channel approach. Both
    #AFE_PORT_CMD_SET_PARAM_V2 and #AFE_PORT_CMD_GET_PARAM_V2 can use this
    parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SLIMBUS_CONFIG

    @apr_msgpayload{afe_port_cmd_slimbus_cfg_t}
    @table{weak__afe__port__cmd__slimbus__cfg__t}
 */
#define AFE_PARAM_ID_SLIMBUS_CONFIG                                   0x00010212

/** Version information used to handle future additions to
    AFE_PARAM_ID_SLIMBUS_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_SLIMBUS_CONFIG                                 0x1

/** Enumeration for setting SLIMbus device ID 1. */
#define AFE_SLIMBUS_DEVICE_1                                         0x0

/** Enumeration for setting SLIMbus device ID 2. */
#define AFE_SLIMBUS_DEVICE_2                                         0x1

/** Enumeration for setting the SLIMbus data formats. */
#define AFE_SB_DATA_FORMAT_NOT_INDICATED                             0x0

/** Enumeration for setting the maximum number of streams per device. @newpage */
#define AFE_PORT_MAX_AUDIO_CHAN_CNT                                   0x8

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_slimbus_cfg_t afe_param_id_slimbus_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_slimbus_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SLIMBUS_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_slimbus_cfg_t
{
    uint32_t                  sb_cfg_minor_version;
    /**< Minor version used to track SLIMbus device configuration.

         @values #AFE_API_VERSION_SLIMBUS_CONFIG */

    uint16_t                  slimbus_dev_id;
    /**< SLIMbus hardware device ID, which is required to handle multiple
         SLIMbus hardware blocks.

         @values
         - #AFE_SLIMBUS_DEVICE_1
         - #AFE_SLIMBUS_DEVICE_2 @tablebulletend */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  data_format;
    /**< Data format supported by the SLIMbus hardware. The default is 0
         (#AFE_SB_DATA_FORMAT_NOT_INDICATED), which indicates the hardware
         does not perform any format conversions before the data transfer. */

    uint16_t                  num_channels;
    /**< Number of channels.

         @values 1 to #AFE_PORT_MAX_AUDIO_CHAN_CNT */

    uint8_t                  shared_channel_mapping[AFE_PORT_MAX_AUDIO_CHAN_CNT];
    /**< Array of shared channel IDs (128 to 255) to which the master port
         is to be connected.

         Shared_channel_mapping[i] represents the shared channel assigned for
         audio channel i in multichannel audio data. */

    uint32_t              sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_24K
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_slimbus_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the Real-time Proxy interface. Both #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_hdr_fields
    Opcode --AFE_PARAM_ID_RT_PROXY_CONFIG

    @apr_msgpayload{afe_param_id_rt_proxy_port_cfg_t}
    @table{weak__afe__param__id__rt__proxy__port__cfg__t}
*/
#define AFE_PARAM_ID_RT_PROXY_CONFIG                                  0x00010213

/** Version information used to handle future additions to
    AFE_PARAM_ID_RT_PROXY_CONFIG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_RT_PROXY_CONFIG                             0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_rt_proxy_port_cfg_t afe_param_id_rt_proxy_port_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_rt_proxy_port_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_RT_PROXY_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_rt_proxy_port_cfg_t
{
    uint32_t                  rt_proxy_cfg_minor_version;
    /**< Minor version used to track real-time proxy configuration.

         @values #AFE_API_VERSION_RT_PROXY_CONFIG */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  interleaved;
    /**< Specifies whether the data exchanged between the AFE interface and
         real-time port is interleaved.

         @values
         - 0 -- Non-interleaved (samples from each channel are contiguous in the
                buffer)
         - 1 -- Interleaved (corresponding samples from each input channel are
                interleaved within the buffer) @tablebulletend */

    uint16_t                  frame_size;
    /**< Size of the frames that are used for PCM exchanges with this port.

         @values > 0, in bytes

         For example, 5 ms buffers of 16 bits and 16 kHz stereo samples
         is 5 ms * 16 samples/ms * 2 bytes/sample * 2 channels = 320 bytes. */

    uint16_t                  jitter_allowance;
    /**< Configures the amount of jitter that the port will allow.

         @values > 0

         For example, if +/-10 ms of jitter is anticipated in the
         timing of sending frames to the port, and the configuration is 16 kHz
         mono with 16-bit samples, this field is 10 ms * 16 samples/ms * 2
         bytes/sample = 320. */

    uint16_t                  low_water_mark;
    /**< Low watermark in bytes (including all channels).

         @values
         - 0 -- Do not send any low watermark events
         - > 0 -- Low watermark for triggering an event

         If the number of bytes in an internal circular buffer is lower than
         this low_water_mark parameter, a LOW_WATER_MARK event is sent to
         applications (via #AFE_EVENT_RT_PROXY_PORT_STATUS).

         The use of watermark events is optional for debugging purposes. */

    uint16_t                  high_water_mark;
    /**< High watermark in bytes (including all channels).

         @values
         - 0 -- Do not send any high watermark events
         - > 0 -- High watermark for triggering an event

         If the number of bytes in an internal circular buffer exceeds
         TOTAL_CIRC_BUF_SIZE minus high_water_mark, a high watermark event is
         sent to applications (via #AFE_EVENT_RT_PROXY_PORT_STATUS).

         The use of watermark events is optional and for debugging purposes. */

    uint32_t                    sample_rate;
    /**< Sampling rate of the port.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_48K @tablebulletend*/

    uint16_t                  num_channels;
    /**< Number of channels.

         @values 1 to #AFE_PORT_MAX_AUDIO_CHAN_CNT */

    uint16_t                  reserved;
     /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_rt_proxy_port_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the Pseudoport interface. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this
    parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_PSEUDO_PORT_CONFIG @vertspace{-3}

    @apr_msgpayload{afe_param_id_pseudo_port_cfg_t}
    @table{weak__afe__param__id__pseudo__port__cfg__t}
*/
#define AFE_PARAM_ID_PSEUDO_PORT_CONFIG                             0x00010219

/** Version information used to handle future additions to
    AFE_PARAM_ID_PSEUDO_PORT_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_PSEUDO_PORT_CONFIG                          0x1

/** Enumeration for setting the timing_mode parameter to faster than real
    time.
*/
#define AFE_PSEUDOPORT_TIMING_MODE_FTRT                             0x0

/** Enumeration for setting the timing_mode parameter to real time using
    timers. @newpage
*/
#define AFE_PSEUDOPORT_TIMING_MODE_TIMER                            0x1

/** Enumeration for setting the pseudoport to act as real-time port.
   */
#define AFE_PSEUDOPORT_TIMING_MODE_REALTIME                         0x2

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_pseudo_port_cfg_t afe_param_id_pseudo_port_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_pseudo_port_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_PSEUDO_PORT_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_pseudo_port_cfg_t
{
    uint32_t                  pseud_port_cfg_minor_version;
    /**< Minor version used to track pseudoport configuration.

         @values #AFE_API_VERSION_PSEUDO_PORT_CONFIG */

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  num_channels;
    /**< Number of channels.

         @values 1 to 8 */

    uint16_t                  data_format;
    /**< Non-linear data format supported by the pseudoport (for future use).

         @values #AFE_LINEAR_PCM_DATA */

    uint16_t                  timing_mode;
    /**< Indicates whether the pseudoport synchronizes to the clock or
         operates faster than real time.

         @values
         - #AFE_PSEUDOPORT_TIMING_MODE_FTRT
         - #AFE_PSEUDOPORT_TIMING_MODE_TIMER @tablebulletend */

    uint32_t                  sample_rate;
    /**< Sample rate at which the pseudoport will run.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_32K
         - #AFE_PORT_SAMPLE_RATE_48K
         - #AFE_PORT_SAMPLE_RATE_96K
         - #AFE_PORT_SAMPLE_RATE_192K @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_pseudo_port_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to
    configure the AHB clock for register access to specific hardware.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this ID.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_AHB_CLOCK_CONFIG @vertspace{-3}

    @apr_msgpayload{afe_param_id_ahb_clock_cfg_t}
    @table{weak__afe__param__id__ahb__clock__cfg__t}
*/
#define AFE_PARAM_ID_AHB_CLOCK_CONFIG                           0x00010249

/** Version information used to handle future additions to
    AFE_PARAM_ID_AHB_CLOCK_CONFIG processing (for backward compatibility).
*/
#define AFE_API_VERSION_AHB_CLOCK_CONFIG                         0x1

/** Enumeration for disabling the AHB clock for register access. */
#define AFE_AHB_CLK_DISABLE                                      0x0

/** Enumeration for enabling the AHB clock for register access. @newpage */
#define AFE_AHB_CLK_ENABLE                                       0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_ahb_clock_cfg_t afe_param_id_ahb_clock_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_ahb_clock_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_AHB_CLOCK_CONFIG parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_ahb_clock_cfg_t
{
    uint32_t                  ahb_clock_cfg_minor_version;
     /**< Minor version used for AHB clock configuration.

         @values #AFE_API_VERSION_AHB_CLOCK_CONFIG */

    uint32_t                  ahb_clk_enable;
    /**< Specifies whether the AHB clock is enabled for register access.

         @values
         - #AFE_AHB_CLK_DISABLE
         - #AFE_AHB_CLK_ENABLE @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_ahb_clock_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to provide
    the device hardware delay.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_DEVICE_HW_DELAY

    @apr_msgpayload{afe_param_id_device_hw_delay_t}
    @table{weak__afe__param__id__device__hw__delay__t}
*/
#define AFE_PARAM_ID_DEVICE_HW_DELAY                             0x00010243

/** Version information used to handle future additions to
    AFE_PARAM_ID_DEVICE_HW_DELAY processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_DEVICE_HW_DELAY                          0x1

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_device_hw_delay_t afe_param_id_device_hw_delay_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_device_hw_delay_t
@{ */
/* Payload of the AFE_PARAM_ID_DEVICE_HW_DELAY parameter used by
    AFE_MODULE_AUDIO_DEV_INTERFACE.
*/
struct afe_param_id_device_hw_delay_t
{
    uint32_t                  device_hw_delay_minor_version;
    /**< Minor version used to track hardware device delay configuration.

         @values 1 */

    uint32_t                  delay_in_us;
    /**< Device hardware delay in microseconds.

         @values Valid uint32 number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_device_hw_delay_t */

/** @ingroup afe_cmd_device_start
    Starts the AFE interface specified by the port_id field.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMD_DEVICE_START

  @apr_msgpayload{afe_port_cmd_device_start_t}
    @table{weak__afe__port__cmd__device__start__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    The port must be configured before sending this command; otherwise, it
    returns an error.
*/
#define AFE_PORT_CMD_DEVICE_START                                      0x000100E5

/* Structure for the AFE_PORT_CMD_DEVICE_START command. */
typedef struct afe_port_cmd_device_start_t afe_port_cmd_device_start_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_device_start_t
@{ */
/* Payload of the AFE_PORT_CMD_DEVICE_START command.
*/
struct afe_port_cmd_device_start_t
{
    uint16_t                  port_id;
    /**< Port interface and direction (Rx or Tx) to start. An even number
         represents the Rx direction, and an odd number represents the Tx
         direction.

         @values See <i>Supported Hardware Ports</i> for the applicable
                 chipset in Chapter @xref{chp:portIDs} */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_device_start_t */

/** @ingroup afe_cmd_devices_restart
    Restarts the AFE interface specified by the port_id field.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMD_DEVICES_RESTART

  @apr_msgpayload{afe_port_cmd_devices_restart_t}
    @table{weak__afe__port__cmd__devices__restart__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}). @vertspace{-6}

  @dependencies
    @vertspace{-3} The I2S port must be started before sending this command;
    otherwise, an error is returned.
    @par
    The sampling rate can be changed only for the 48 kHz family group (8 kHz,
    16 kHz, and 48 kHz sampling rates) because it cannot change the root clock
    for the I2S interface.
    @par
    The OSR cannot be changed. For example, if the OSR is 12288000, it stays as
    12288000.
    If the OSR (mclk) is to be changed, it must send the clock configuration,
    and then stop and restart the command.
    @par
    The root clocks must be in Master mode. If they are in Slave mode, this
    command must not be used.
    @par
    If the Rx and Tx ports usE different interfaces (such as the Primary
    Rx port and Secondary Tx port), the Primary Tx Port and Secondary Rx port
    must not be used.
    @par
    The number of channels for this command can be supported only for the mono
    channel.
*/
#define AFE_PORT_CMD_DEVICES_RESTART                                      0x000100F7

/* Structure for the AFE_PORT_CMD_DEVICE_START command. */
typedef struct afe_port_cmd_devices_restart_t afe_port_cmd_devices_restart_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_devices_restart_t
@{ */
/* Payload of the AFE_PORT_CMD_DEVICES_RESTART command.
*/
struct afe_port_cmd_devices_restart_t
{
    uint16_t                  rx_port_id;
    /**< I2S Rx port interface to restart. 
    
         @values
         - See the I2S/MI2S ports for the applicable chipset in
           Chapter @xref{chp:portIDs}
         - If an Rx port is not used -- #AFE_PORT_ID_INVALID
         
         If only one Rx port is to be restarted, you can specify the Tx port
         parameter as invalid. */

    uint16_t                  tx_port_id;
    /**<I2S Tx port interface to restart. 

         @values
         - See the I2S/MI2S ports for the applicable chipset in
           Chapter @xref{chp:portIDs}
         - If an Tx port is not used -- #AFE_PORT_ID_INVALID @tablebulletend */

    uint32_t                  sample_rate;
    /**< Sample rate at which the port will rerun.

         @values
         - #AFE_PORT_SAMPLE_RATE_8K
         - #AFE_PORT_SAMPLE_RATE_16K
         - #AFE_PORT_SAMPLE_RATE_48K @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_devices_restart_t */


/** @ingroup afe_cmd_device_stop
    Stops the AFE interface specified by the port_id field.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMD_DEVICE_STOP

  @apr_msgpayload{afe_port_cmd_device_stop_t}
    @table{weak__afe__port__cmd__device__stop__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/
#define AFE_PORT_CMD_DEVICE_STOP                                      0x000100E6

/* Payload structure of the AFE_PORT_CMD_DEVICE_STOP command. */
typedef struct afe_port_cmd_device_stop_t afe_port_cmd_device_stop_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_device_stop_t
@{ */
/* Payload of the AFE_PORT_CMD_DEVICE_STOP command.
*/
struct afe_port_cmd_device_stop_t
{
    uint16_t                  port_id;
    /**< Port interface and direction (Rx or Tx) to stop. An even number
         represents the Rx direction, and an odd number represents the Tx
         direction.

         @values See <i>Supported Hardware Ports</i> for the applicable
                 chipset in Chapter @xref{chp:portIDs} */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_device_stop_t */

/** @addtogroup afe_cmd_mem_map
@{ */
/** Commands the AFE service to map multiple shared memory regions.
    All regions to be mapped must be from the same memory pool.

  @apr_hdr_fields
    Opcode -- AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS

  @apr_msgpayload{afe_service_cmd_shared_mem_map_regions_t}
    @tablens{weak__afe__service__cmd__shared__mem__map__regions__t}

  @mappayload{afe_service_shared_map_region_payload_t}
    @table{weak__afe__service__shared__map__region__payload__t}

  @return
    #AFE_SERVICE_CMDRSP_SHARED_MEM_MAP_REGIONS

  @dependencies
    None.
*/
#define AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS                       0x000100EA

/** Enumeration for the shared memory, 8 byte addressable, 4 KB aligned
    pool ID. */
#define ADSP_MEMORY_MAP_SHMEM8_4K_POOL      3

/** @} */ /* end_addtogroup afe_cmd_mem_map */

/* AFE_SERVICE shared memory map regions structure */
typedef struct  afe_service_cmd_shared_mem_map_regions_t afe_service_cmd_shared_mem_map_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_cmd_shared_mem_map_regions_t
@{ */
/* Memory map regions command payload used by the
    AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS command that allows clients to map
    multiple shared memory regions in a single command. */
/** Immediately following this structure are num_regions of the
    <b>Map payload</b> (%afe_service_shared_map_region_payload_t).
*/
struct afe_service_cmd_shared_mem_map_regions_t
{
    uint16_t                  mem_pool_id;
    /**< Type of memory on which this memory region is mapped.

         @values
         - #ADSP_MEMORY_MAP_SHMEM8_4K_POOL
         - Other values are reserved

         The memory pool ID implicitly defines the characteristics of the memory.
         Characteristics can include alignment type, permissions, and so on.

         ADSP_MEMORY_MAP_SHMEM8_4K_POOL is shared memory, 8 byte addressable,
         and 4 KB aligned. */

    uint16_t                  num_regions;
    /**< Number of regions to map.

         @values Any value greater than zero */

    uint32_t                  property_flag;
    /**< Configures one common property for all regions in the payload.

         @values 0x00000000 to 0x00000001

         Bit 0 indicates physical or virtual mapping:
         - 0 -- The shared memory address provided in
           %afe_service_shared_map_region_payload_t is a physical address.
           The shared memory must be mapped (hardware TLB entry), and a
           software entry must be added for internal bookkeeping.
         - 1 -- The shared memory address provided in
           %afe_service_shared_map_region_payload_t is a virtual address.
           The shared memory must not be mapped (because the hardware TLB entry
           is already available), but a software entry must be added for
           internal bookkeeping. \n
           This is useful if two services within the aDSP are communicating
           via the APR. They can directly communicate via the virtual
           address instead of the physical address. The virtual regions must
           be contiguous. In this case, num_regions must be 1.

         Bits 31 to 1 are reserved and must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_cmd_shared_mem_map_regions_t */

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_shared_map_region_payload_t
@{ */
/* Payload of the map region; used by the
    afe_service_cmd_shared_mem_map_regions_t structure.
*/
struct afe_service_shared_map_region_payload_t
{
    uint32_t                  shm_addr_lsw;
    /**< Lower 32 bits of the shared memory address of the memory region to
         map. */

    uint32_t                  shm_addr_msw;
    /**< Upper 32 bits of the shared memory address of the memory region to
         map.

         The 64-bit number formed by shm_addr_lsw and shm_addr_msw word must be
         contiguous memory, and it must be 4 KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value. @tablebulletend */

    uint32_t                  mem_size_bytes;
    /**< Number of bytes in the region.

         @values Multiples of 4 KB

         The aDSP always maps the regions as virtual contiguous memory, but
         the memory size must be in multiples of 4 KB to avoid gaps in the
         virtually contiguous mapped memory. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_shared_map_region_payload_t */

/** @ingroup afe_resp_mem_map
    Response sent by the AFE service to the client in response to the
    successful processing of #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

  @apr_hdr_fields
    Opcode -- AFE_SERVICE_CMDRSP_SHARED_MEM_MAP_REGIONS \n

  @apr_msgpayload{afe_service_cmdrsp_shared_mem_map_regions_t}
    @table{weak__afe__service__cmdrsp__shared__mem__map__regions__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS command must have
    been sent to receive this response from the AFE service.
*/
#define AFE_SERVICE_CMDRSP_SHARED_MEM_MAP_REGIONS                   0x000100EB

/* AFE_SERVICE shared memory map regions response structure */
typedef struct  afe_service_cmdrsp_shared_mem_map_regions_t afe_service_cmdrsp_shared_mem_map_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_cmdrsp_shared_mem_map_regions_t
@{ */
/* Payload of the memory map command response used by the
    AFE_SERVICE_CMDRSP_SHARED_MEM_MAP_REGIONS command.
*/
struct afe_service_cmdrsp_shared_mem_map_regions_t
{
    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value

         This memory map handle is returned by the aDSP through
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS. This handle can be
         used as an abstract representation of the shared memory regions that
         are being mapped.

         The aDSP uses this handle to retrieve the shared memory attributes.
         AFE_SERVICE_CMD_SHARED_MEM_UNMAP_REGIONS uses this handle
         to unmap the mapped memory. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_cmdrsp_shared_mem_map_regions_t */

/** @ingroup afe_cmd_mem_unmap
    Commands the AFE service to unmap multiple shared memory regions that were
    previously mapped.

  @apr_hdr_fields
    Opcode -- AFE_SERVICE_CMD_SHARED_MEM_UNMAP_REGIONS \n

  @apr_msgpayload{afe_service_cmd_shared_mem_unmap_regions_t}
    @table{weak__afe__service__cmd__shared__mem__unmap__regions__t}

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    A corresponding #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS command must have
    been successfully processed.
*/
#define AFE_SERVICE_CMD_SHARED_MEM_UNMAP_REGIONS                      0x000100EC

/* AFE_SERVICE shared memory unmap regions command structure */
typedef struct afe_service_cmd_shared_mem_unmap_regions_t afe_service_cmd_shared_mem_unmap_regions_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_service_cmd_shared_mem_unmap_regions_t
@{ */
/* Payload of the memory map command response used by
    AFE_SERVICE_CMD_SHARED_MEM_UNMAP_REGIONS, which allows clients to unmap
    multiple shared memory regions in a single command.
*/
struct afe_service_cmd_shared_mem_unmap_regions_t
{
    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         @values Any 32-bit value

         This memory map handle is returned by the aDSP through
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

         The aDSP uses this handle to retrieve the associated shared
         memory regions and unmap them. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_service_cmd_shared_mem_unmap_regions_t */

/** @ingroup afe_cmd_port_set_params
    Configures one or more parameters on an AFE port. This command is
    typically used to apply calibration data to the modules.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMD_SET_PARAM_V2

  @apr_msgpayload{afe_port_cmd_set_param_v2_t}
    @table{weak__afe__port__cmd__set__param__v2__t}

  @par Parameter data variable payload (afe_port_param_data_v2_t)
    @tablens{weak__afe__port__param__data__v2__t}

  @detdesc
    This command is sent from the client to the aDSP to set the parameters of
    a port. A single command can be used to set multiple parameters, each
    belonging to multiple modules.
    @par
    Messages can be either in-band or out-of-band via shared memory. The modes
    are:
    - In-band set parameter -- In this mode, the physical address is set to
      NULL. The rest of the payload contains the parameters as shown in the
      parameter data variable payload (%afe_port_param_data_v2_t).
    - Shared memory set parameter -- In this mode, both the physical address to
      the parameter data and the data payload size are sent. The rest of the
      message is inside the shared memory in the parameter data variable
      payload format. The memory content is the same as the in-band payload
      structure (%afe_port_param_data_v2_t).

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/
#define AFE_PORT_CMD_SET_PARAM_V2                                      0x000100EF

/* Structure for the AFE parameter data. */
typedef struct afe_port_param_data_v2_t afe_port_param_data_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_param_data_v2_t
@{ */
/* Payload of the AFE parameter data used by
    AFE_PORT_CMD_SET_PARAM_V2, AFE_PORT_CMD_GET_PARAM_V2, and
    AFE_PORT_CMDRSP_GET_PARAM_V2. */
/** Immediately following this structure is the actual calibration data for the
    module_id/param_id pair.
*/
struct afe_port_param_data_v2_t
{
   uint32_t module_id;
   /**< ID of the module.

        @values Valid module ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint32_t param_id;
   /**< ID of a parameter that is supported by the module ID.

        @values Valid parameter ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint16_t param_size;
   /**< Actual size of the data for the module_id/param_id pair. The size is a
        multiple of four bytes.

        @values > 0 */

   uint16_t reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_param_data_v2_t */

/* Structure for configuration/calibration settings for the AFE port. */
typedef struct afe_port_cmd_set_param_v2_t afe_port_cmd_set_param_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_set_param_v2_t
@{ */
/* Payload of the AFE_PORT_CMD_SET_PARAM_V2 command's
    configuration/calibration settings for the AFE port.
*/
struct afe_port_cmd_set_param_v2_t
{
   uint16_t port_id;
   /**< Port interface and direction (Rx or Tx) to configure. An even number
        represents the Rx direction, and an odd number represents the Tx
        direction.

        @values See <i>Supported Hardware Ports</i> for the applicable
                chipset in Chapter @xref{chp:portIDs} */

   uint16_t payload_size;
   /**< Actual size of the payload in bytes. This is used for parsing the
        parameter payload.

        @values > 0 */

   uint32_t payload_address_lsw;
    /**< Lower 32 bits of the payload address. */

   uint32_t payload_address_msw;
    /**< Upper 32 bits of the payload address.

         The 64-bit number formed by payload_address_lsw and
         payload_address_msw must be aligned to a 32-byte boundary, be \n
         4 KB aligned, and be in contiguous memory.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 of this field must
           be set to zero. @tablebulletend */

   uint32_t mem_map_handle;
   /**< Unique identifier for an address.

        @values
        - NULL -- The message is in the payload (in-band).
        - Non-NULL -- The parameter data payload begins at the address
          specified by a pointer to the payload's physical address in shared
          memory (out-of-band).

        This memory map handle is returned by the aDSP through
        #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

        An optional field is available if parameter data is in-band:
        %afe_port_param_data_v2_t param_data[...].
        See <b>Parameter data variable payload</b> on the next page.
        @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_set_param_v2_t */

/** @ingroup afe_cmd_get_params
    Queries for the parameters of an AFE port.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMD_GET_PARAM_V2

  @apr_msgpayload{afe_port_cmd_get_param_v2_t}
    @table{weak__afe__port__cmd__get__param__v2__t}

  @par Parameter data variable payload (afe_port_param_data_v2_t)
    @tablens{weak__afe__port__param__data__v2__t}

  @detdesc
    This command is sent from the client to the aDSP to query the parameters of
    the requested port. If the payload_address is NULL (in-band), the aDSP
    sends the data in the APR payload of #AFE_PORT_CMDRSP_GET_PARAM_V2.
    If the payload_address is non-NULL (out-of-band), data is stored at the
    address specified in the payload_address variable.
    @par
    The client receives a response from the aDSP with the values of the
    requested parameters in AFE_PORT_CMDRSP_GET_PARAM_V2.

  @return
    An #AFE_PORT_CMDRSP_GET_PARAM_V2 message.

  @dependencies
    None.
*/
#define  AFE_PORT_CMD_GET_PARAM_V2                                    0x000100F0

/* Payload structure of the AFE_PORT_CMD_GET_PARAM_V2 command. */
typedef struct afe_port_cmd_get_param_v2_t afe_port_cmd_get_param_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmd_get_param_v2_t
@{ */
/* Payload of the AFE_PORT_CMD_GET_PARAM_V2 command, which queries for one
    post/preprocessing parameter of a stream.
*/
struct afe_port_cmd_get_param_v2_t
{
    uint16_t                  port_id;
    /**< Port interface and direction (Rx or Tx) to query. An even number
         represents the Rx direction, and an odd number represents the Tx
         direction.

         @values See <i>Supported Hardware Ports</i> for the applicable
                 chipset in Chapter @xref{chp:portIDs} */

    uint16_t                  payload_size;
    /**< Maximum data size of the parameter ID/module ID combination. This is
         a multiple of four bytes.

         @values > 0 bytes */

    uint32_t payload_address_lsw;
    /**< Lower 32 bits of the payload address. */

    uint32_t payload_address_msw;
    /**< Upper 32 bits of the payload address.

         The 64-bit number formed by payload_address_lsw and
         payload_address_msw must be aligned to a 32-byte boundary, be \n
         4 KB aligned, and be in contiguous memory.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 of this field must
           be set to zero. @tablebulletend */

    uint32_t mem_map_handle;
    /**< Unique identifier for an address.

         @values
         - NULL -- The message is in the payload (in-band).
         - Non-NULL -- The parameter data payload begins at the address
           specified by a pointer to the payload's physical address in shared
           memory (out-of-band).

         This memory map handle is returned by the aDSP through
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

         An optional field is available if parameter data is in-band:
         %afe_port_param_data_v2_t param_data[...].
         See <b>Parameter data variable payload</b> on the next page. */

    uint32_t                  module_id;
    /**< ID of the module to be queried.

         @values Valid module ID (See Chapter @xref{hdr:CalibrationIDs}) */

    uint32_t                  param_id;
    /**< ID of the parameter to be queried.

         @values Valid parameter ID (See Chapter @xref{hdr:CalibrationIDs}) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmd_get_param_v2_t */

/** @ingroup afe_resp_get_params
    Provides an acknowledgment response to an #AFE_PORT_CMD_GET_PARAM_V2
    command.
    This event supports shared memory if an address is sent with
    AFE_PORT_CMD_GET_PARAM_V2.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CMDRSP_GET_PARAM_V2

  @apr_msgpayload{afe_port_cmdrsp_get_param_v2_t}
    Immediately following this structure is the acknowledgment
    <b>Parameter data variable payload</b> (%afe_port_param_data_v2_t).
    This payload is included for an in-band scenario. For an address/shared
    memory-based set parameter, this payload is not required.
    @tablens{weak__afe__port__cmdrsp__get__param__v2__t}

  @par Parameter data variable payload (afe_port_param_data_v2_t)
    @tablens{weak__afe__port__param__data__v2__t} @newpage

  @detdesc
    This command is sent from the aDSP to the client with the parameter values
    requested in response to #AFE_PORT_CMD_GET_PARAM_V2.
    @par
    For in-band parameters, the acknowledgment response contains the status,
    followed by the parameter data variable payload.
    @par
    For out-of-band parameters, the response contains only the status, and the
    requested parameters are stored in the address specified in the
    AFE_PORT_CMD_GET_PARAM_V2. Data is stored in the form of the acknowledgment
    parameter data variable payload.
    @par
    The choice of in-band or out-of-band depends on the values of
    payload_address present in %AFE_PORT_CMD_GET_PARAM_V2.

  @return
    None.

  @dependencies
    #AFE_PORT_CMD_GET_PARAM_V2 must have been sent before this response.
*/
#define AFE_PORT_CMDRSP_GET_PARAM_V2                                   0x00010106

/* Payload structure of the AFE_PORT_CMDRSP_GET_PARAM_V2 event. */
typedef struct afe_port_cmdrsp_get_param_v2_t afe_port_cmdrsp_get_param_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_cmdrsp_get_param_v2_t
@{ */
/* Payload of the AFE_PORT_CMDRSP_GET_PARAM_V2 message,
    which responds to an #AFE_PORT_CMD_GET_PARAM_V2 command.
*/
struct afe_port_cmdrsp_get_param_v2_t
{
    uint32_t                  status;
    /**< Status message or error code. For more information, refer to
         @xhyperref{Q3,[Q3]}.

         @values
          - APR_EOK -- Success
          - APR_EBADPARAM -- Failure @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_cmdrsp_get_param_v2_t */

#include "adsp_begin_pack.h"

/** @cond OEM_only */
/** @weakgroup weak_afe_algo_log_header_t
@{ */
/* Payload of the AFE algo log data used by
    Modules AFE_MODULE_FB_SPKR_PROT_RX and AFE_MODULE_FB_SPKR_PROT_VI_PROC
    for logging AFE_PARAM_ID_FBSP_TH_RX_STATS, AFE_PARAM_ID_FBSP_EX_RX_STATS,
    AFE_PARAM_ID_FBSP_CLIP_INT_STATS, AFE_PARAM_ID_FBSP_TH_VI_STATS
    and AFE_PARAM_ID_FBSP_EX_VI_STATS*/
/** Header structure for logging algorithm data. Immediately following this
    structure is the actual algorithm logging data for the module_id/param_id
    pair.
*/
struct afe_algo_log_header_t
{
   uint32_t module_id;
   /**< ID of the module to be configured.

        @values Valid module ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint32_t param_id;
   /**< ID of the parameter corresponding to the supported parameters
        for the module ID.

        @values Valid parameter ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint16_t param_size;
   /**< Actual size of the data for the module_id/param_id pair. The size is a
        multiple of four bytes.

        @values > 0 */

   uint16_t reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_algo_log_header_t */
/** @endcond */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** @ingroup afe_module_feedback_spkr_rx
    ID of the Feedback Speaker Protection Rx module, which is used to process
    the PCM data to protect the speaker.
    
    This module supports the following parameter IDs:
     - #AFE_PARAM_ID_FBSP_MODE_RX_CFG
     - #AFE_PARAM_ID_FB_SPKR_PROT_FEAT_RX_CFG
     - #AFE_PARAM_ID_FBSP_IIR_RX_CFG
     - #AFE_PARAM_ID_SPKR_COIL_TX_RX_CFG
     - #AFE_PARAM_ID_FBSP_SPKR_COIL_RX_CFG
     - #AFE_PARAM_ID_FB_THERM_PROT_RX_CFG
     - #AFE_PARAM_ID_FB_EXCUR_CNTL_RX_CFG
     - #AFE_PARAM_ID_FBSP_ACM_RX_CFG
     - #AFE_PARAM_ID_FBSP_ACM_CDC_RX_CFG
     - #AFE_PARAM_ID_FBSP_EX_PARAM_RX_CFG
     - #AFE_PARAM_ID_FBSP_TH_RX_STATS
     - #AFE_PARAM_ID_FBSP_EX_RX_STATS
     - #AFE_PARAM_ID_FBSP_CLIP_INT_STATS
     - #AFE_PARAM_ID_ENABLE

  @apr_hdr_fields
    Opcode -- AFE_MODULE_FB_SPKR_PROT_RX

  @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the feedback Speaker Protection module using
       #AFE_PORT_CMD_SET_PARAM_V2 with #AFE_MODULE_FB_SPKR_PROT_RX,
       including the above mentioned parameters.
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port when needed using #AFE_PORT_CMD_DEVICE_STOP (the AFE
       destroys all speaker protection-related information).
    @par
    Except for AFE_PARAM_ID_ENABLE, all other configurations for this module
    are accepted only in the Configuration state of the port (after
    #AFE_MODULE_AUDIO_DEV_INTERFACE and before #AFE_PORT_CMD_DEVICE_START).
    @par
    AFE_PARAM_ID_ENABLE can also be enabled for this module when the AFE
    port is in the Run state. This allows disabling/enabling this feature at
    runtime.
    @par
    However, there will be a glitch in the audio output when the feature is
    disabled and enabled, and vice versa, during runtime. Qualcomm recommends
    that avoid disabling/enabling this feature during runtime.
    @par
    The Enable parameter ID must be sent first to enable the feature when the
    port is in the Configuration state.
    @par
    This module supports only 1 channel (mono speaker), 16 or 24 bits, and
    8K, 16K, or 48K sampling rates.
*/
#define AFE_MODULE_FB_SPKR_PROT_RX                             0x0001021C

/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX
    @if OEM_only and #AFE_MODULE_SPEAKER_PROTECTION_V2_RX @endif
    to configure the mode of feedback speaker protection Rx processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_mode_rx_cfg_v1_t}
    @table{weak__afe__fbsp__mode__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FBSP_MODE_RX_CFG                          0x0001021D

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_MODE_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_MODE_RX_CFG                            0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_mode_rx_cfg_v1_t afe_fbsp_mode_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_mode_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_MODE_RX_CFG parameter (version 1).
*/
struct afe_fbsp_mode_rx_cfg_v1_t
{
   uint32_t       fbsp_mode_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection
        Rx processing configuration.

        @values #AFE_API_VERSION_FBSP_MODE_RX_CFG */

   uint32_t        mode;
   /**< Mode of feedback speaker protection Rx processing.

        @values
        - 0 -- Normal processing
        - 1 -- Thermal calibration @tablebulletend*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_mode_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure
    feedback speaker protection features Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_feat_rx_cfg_v1_t}
    @table{weak__afe__fbsp__feat__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FB_SPKR_PROT_FEAT_RX_CFG                           0x0001021E

/** Version information used to handle future additions to
    AFE_PARAM_ID_FB_SPKR_PROT_FEAT_RX_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_FBSP_FEAT_RX_CFG                              0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_feat_rx_cfg_v1_t afe_fbsp_feat_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_feat_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FB_SPKR_PROT_FEAT_RX_CFG parameter (version 1).
*/
struct afe_fbsp_feat_rx_cfg_v1_t
{
   uint32_t       fbsp_feat_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        protection Rx feature configuration.

        @values #AFE_API_VERSION_FBSP_FEAT_RX_CFG */

   uint32_t        feature;
   /**< Feature flag for the AFE_PARAM_ID_FB_SPKR_PROT_FEAT_RX_CFG parameter.

        @values
        - Bit 0 -- Notch high pass filter
        - Bit 1 -- Thermal protection
        - Bit 2 -- Excursion control
        - Bit 3 -- Analog clip manager
        - Bits 31-4 -- Reserved; must be set to zero @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_feat_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure the
    IIR filter for feedback speaker protection Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_iir_rx_cfg_v1_t}
    @table{weak__afe__fbsp__iir__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FBSP_IIR_RX_CFG                                 0x0001021F

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_IIR_RX_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_FBSP_IIR_RX_CFG                              0x1

/** Maximum number of stages in the IIR filter. @newpage */
#define AFE_FBSP_IIR_FILT_MAX_STAGES                        5

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_iir_rx_cfg_v1_t afe_fbsp_iir_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_iir_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_IIR_RX_CFG parameter (version 1).
*/
struct afe_fbsp_iir_rx_cfg_v1_t
{
   uint32_t       fbsp_iir_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection Rx IIR
        filter feedback speaker configuration.

        @values #AFE_API_VERSION_FBSP_IIR_RX_CFG */

   int32_t        iir_nch_c_num[AFE_FBSP_IIR_FILT_MAX_STAGES * 3];
   /**< IIR notch filter numerator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

    int32_t       iir_nch_c_den[AFE_FBSP_IIR_FILT_MAX_STAGES * 2];
   /**< IIR notch filter denominator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

    int32_t       iir_nch_c_num_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
    /**< IIR notch filter numerator Q factors.
         Unused filter factors must be set to zero.

        @values -32 to 32 */

    int32_t       iir_nch_c_den_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
    /**< IIR notch filter denominator Q factors.
         Unused filter coeffs must be set to zero.

        @values -32 to 32 */

    int16_t       iir_nch_c_stages;
    /**< Number of stages in the IIR filter.

        @values 0 to #AFE_FBSP_IIR_FILT_MAX_STAGES */

    int16_t       reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_iir_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX and
    #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure speaker coil Tx/Rx
    for feedback speaker protection Rx and Vsens/Isens (VI) processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_spkr_coil_tx_rx_cfg_v1_t}
    @table{weak__afe__fbsp__spkr__coil__tx__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_SPKR_COIL_TX_RX_CFG                           0x00010220

/** Version information used to handle future additions to
    AFE_PARAM_ID_SPKR_COIL_TX_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SPKR_COIL_TX_RX_CFG                          0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_spkr_coil_tx_rx_cfg_v1_t afe_fbsp_spkr_coil_tx_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_spkr_coil_tx_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SPKR_COIL_TX_RX_CFG parameter (version 1).
*/
struct afe_fbsp_spkr_coil_tx_rx_cfg_v1_t
{
   uint32_t       spkr_coil_tx_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker coil Tx/Rx configuration.

        @values #AFE_API_VERSION_SPKR_COIL_TX_RX_CFG */

   int32_t        mt_l32_q24;
   /**< Enclosure-independent parameter: MMD + MM1, where MMD is moving
        mass of diaphragm and MM1 is air mass load.

        @values
        - Minimum -- 1677 (0.0001 gram in Q24 format)
        - Maximum -- 1677721600 (100 gram in Q24 format) @tablebulletend */

   int32_t        re_l32_q24;
   /**< DC resistance of the speaker.

        @values
        - Minimum -- 167772 (0.01 Ohm in Q24 format)
        - Maximum -- 160054640 (100 Ohms in Q24 format) @tablebulletend */

   int32_t        le_l32_q24;
   /**< Inductance of the speaker.

        @values 0 to 160054640 (100 mH in Q24 format) */

   int32_t        bl_l32_q24;
   /**< Force factor.

        @values
        - Minimum -- 1677 (0.0001 in Q24 format)
        - Maximum -- 160054640 (100 in Q24 format) @tablebulletend */

   int32_t        fct_l32_q20;
   /**< Resonance frequency.

        @values
        - Minimum -- 1048576 (1 Hz in Q20 format)
        - Maximum -- 2147483647 (2047.99 Hz in Q20) @tablebulletend */

   int32_t        q_mct_l32_q24;
   /**< Mechanical Q factor (no unit).

        @values
        - Minimum -- 167772 (0.01 in Q24 format)
        - Maximum -- 160054640 (100 in Q24 format) @tablebulletend */

   int32_t        rect_l32_q24;
   /**< Resistance due to mechanical losses.

        @values
        - Minimum -- 167772 (0.01 Ohm in Q24 format)
        - Maximum -- 2147483647 (127.99 Ohms in Q24 format) @tablebulletend */

   int16_t        tolerance_re_l16;
   /**< Tolerance for DC resistance of the speaker.

        @values 1 to 100% */

   int16_t        tolerance_le_l16;
   /**< Tolerance for inductance of the speaker.

        @values 1 to 100% */

   int16_t        tolerance_bl_l16;
   /**< Tolerance for the force factor.

        @values 1 to 100% */

   int16_t        tolerance_fct_l16;
   /**< Tolerance for the resonance frequency.

        @values 1 to 100% */

   int16_t        tolerance_qmct_l16;
   /**< Tolerance for the Mechanical Q factor

        @values 1 to 100% */

   int16_t        tolerance_rect_l16;
   /**< Tolerance for resistance due to mechanical losses.

        @values 1 to 100% */

   uint16_t        temp_coef_inv_u16;
   /**< Resistivity coefficient. This is a speaker-dependent
        parameter.

        @values 10 to 65535 (1/degrees C) */

   int16_t        reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_spkr_coil_tx_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure
    speaker coil parameters used in Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_spkr_coil_rx_cfg_v1_t}
    @table{weak__afe__fbsp__spkr__coil__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FBSP_SPKR_COIL_RX_CFG                             0x00010221

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_SPKR_COIL_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_SPKR_COIL_RX_CFG                        0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_spkr_coil_rx_cfg_v1_t afe_fbsp_spkr_coil_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_spkr_coil_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_SPKR_COIL_RX_CFG parameter (version 1).
*/
struct afe_fbsp_spkr_coil_rx_cfg_v1_t
{
   uint32_t       fbsp_spkr_coil_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection speaker
        coil Rx configuration.

        @values #AFE_API_VERSION_FBSP_SPKR_COIL_RX_CFG */

   int16_t        r_spk_coil_q8;
   /**< Electrical resistance of the speaker coil.

        @values
        - Minimum -- 512 (2 Ohms in Q8 format)
        - Maximum -- 16384 (64 Ohms in Q8 format) @tablebulletend */

   int16_t        v_full_sc_q10;
   /**< Speaker voltage for the digitally full-scale signal.

        @values
        - Minimum -- 512 (0.5 volt in Q10 format)
        - Maximum -- 10240 (10 volts in Q10 format) @tablebulletend */

   int16_t        thermal_resistance_q6;
   /**< Voice coil thermal resistance).

        @values 0 to 32767 (511.9 degrees C/Watt in Q6 format) */

   int16_t        thermal_resistance_tot_q6;
   /**< Total thermal resistance (voice coil + magnet, and so on.).

        @values 0 to 32767 (511.9 degrees C/Watt in Q6 format) */

   int16_t        thermal_tau_q10[2];
   /**< Estimate of the voice coil thermal time constant:
        - thermal_tau_q10[0] -- Low estimate
        - thermal_tau_q10[1] -- High estimate

        @values
        - Minimum -- 51 (0.049 seconds in Q10 format)
        - Maximum -- 32767 (31.9 seconds in Q10 format) @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_spkr_coil_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure
    feedback thermal protection Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fb_therm_prot_rx_cfg_v1_t}
    Version 1 of the configuration structure.
    @tablens{weak__afe__fb__therm__prot__rx__cfg__v1__t}

    @apr_msgpayload{afe_fb_therm_prot_rx_cfg_v2_t}
    Version 2 of the configuration structure. It includes support for the
    loudness boost feature (loudness_temp_margin_q6).
    @tablens{weak__afe__fb__therm__prot__rx__cfg__v2__t}
*/
#define AFE_PARAM_ID_FB_THERM_PROT_RX_CFG                               0x00010222

/** Version information used to handle future additions to
    AFE_PARAM_ID_FB_THERM_PROT_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FB_THERM_PROT_RX_CFG                          0x2

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fb_therm_prot_rx_cfg_v2_t afe_fb_therm_prot_rx_cfg_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fb_therm_prot_rx_cfg_v2_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FB_THERM_PROT_RX_CFG parameter (version 2).
    It comprises of new feature such as loudness boost.

    Following are the new feature additions:
    - loudnessTempMarginQ6
*/
struct afe_fb_therm_prot_rx_cfg_v2_t
{
   uint32_t       fb_therm_prot_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        thermal protection Rx configuration.

        @values #AFE_API_VERSION_FB_THERM_PROT_RX_CFG */

   int16_t        cntl_input;
   /**< Type of control input for temperature feed.

        @values
        - 0 -- Use the feedback temperature only
        - 1 -- Use the feedback temperature with the low pass filter
        - 2 -- Feed a forward estimated temperature @tablebulletend */

   int16_t        temp_loop_dly_ms;
   /**< Delay of predicted temperature feeding back to the Thermal Control
        module.

        @values 0 to 1000 ms */

   int16_t        pow_est_smooth;
   /**< Smoothing IIR filter flag for power estimation.

        @values
        - 0 -- Disable smoothing IIR filter
        - 1 -- Enable smoothing IIR filter @tablebulletend */

   int16_t        temp_tgt_q6;
   /**< Target control temperature.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_nominal_q6;
   /**< Initial voice coil temperature.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_min_q6;
   /**< Minimum reasonable measured temperature.

        A temperature lower than this setting is ignored.
        The temperature must not be higher than temp_nominal_q6 or temp_tgt_q6.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_max_q6;
   /**< Maximum reasonable measured temperature.

        A temperature higher than this setting is ignored.
        The temperature must not be lower than temp_nominal_q6 or temp_tgt_q6.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_max_chg_sec_q6;
   /**< Maximum temperature change per second.
        A new temperature is ignored if it is outside this range.

        @values
        - 0 to 32767 (511.9 degrees C in Q6 format)
        - > 32767 -- Disable this feature @tablebulletend */

   int32_t        iir_tdc_c_num[AFE_FBSP_IIR_FILT_MAX_STAGES * 3];
   /**< Temperature smoothing IIR filter numerator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_den[AFE_FBSP_IIR_FILT_MAX_STAGES * 2];
   /**< Temperature smoothing IIR filter denominator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_num_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
   /**< Integer part of the Q factor of the temperature smoothing IIR filter
        numerator coefficient.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_den_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
   /**< Integer part of the Q factor of the temperature smoothing IIR filter
        denominator coefficient.

        @values -32 to 32 */

   int16_t        iir_tdc_c_stages;
   /**< Number of stages in the temperature smoothing IIR filter.

        @values 0 to 5 */

   int16_t        prop_x_q12;
   /**< Proportional term in Proportional and Integral (PI) control.

        @values 0 to 32767 (7.9 in Q12 format) */

   int16_t        intg_x_q12;
   /**< Integral term in PI control.

        @values 0 to 32767 (7.9 in Q12 format) */

   int16_t        min_gain_db_q7;
   /**< Minimum temperature control gain,

        @values -7680 to 0 (-60 dB in Q7 format) */

   int16_t        gain_alph_q15[2];
   /**< Smoothing of gain, attack (gain decreasing), and release (relaxing
        back to 0 dB).

        @values
        - Minimum -- 328 (0.01 dB in Q15 format)
        - Maximum -- 32767 (0.99 dB in Q15 format) @tablebulletend */

   int16_t        dead_zone_q6;
   /**< Dead zone (region near the target temperature) for a reduced
        proportional term.

        @values
        - Minimum -- 2 (0.03125 degrees C in Q6 format)
        - Maximum -- 2048 (32 degrees C in Q6 format) @tablebulletend */

   int16_t        dead_zone_sc_q15;
   /**< Scaling factor to modify the proportional term when inside a dead zone.

        @values
        - Minimum -- 328 (0.01 in Q15 format)
        - Maximum -- 32767 (0.99 in Q15 format) @tablebulletend */

   uint16_t        rx_scale_u16_q16;
   /**< Factor for scaling down the signal such that adding a pilot tone
        does not cause clipping.

        @values
        - Minimum -- 32768 (0.5 in Q16 format)
        - Maximum -- 65535 (0.99 in Q16 format) @tablebulletend */

   uint16_t        pi_scale_u16_q18;
   /**< Scale factor for the pilot tone relative to 0 dBFs
        (for example, -40 dB from the full scale).

        @values 0 to 65535 (0.249 in Q18 format) */

   int32_t        clip_time_out_ms;
   /**< Clip interrupt timeout. A value greater than zero means the clip
        interrupt support feature is enabled with this timeout.

        @values 0 to 4000 ms */

   int32_t        vbat_time_out_ms;
   /**< VBAT timeouts. A value greater than zero means the VBAT interrupt
        support feature is enabled with this timeout.

        @values 0 to 1000000 ms */

   int16_t        loudness_temp_margin_q6;
   /**< Temperature prediction error window due to corrupt Isen samples.

        @values
        - Minimum -- 0 (0 degrees C in Q6 format)
        - Maximum -- 1280 (20 degrees C in Q6 format) @tablebulletend */

   uint16_t       reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fb_therm_prot_rx_cfg_v2_t */

typedef struct afe_fb_therm_prot_rx_cfg_v1_t afe_fb_therm_prot_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fb_therm_prot_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FB_THERM_PROT_RX_CFG parameter (version 1).
*/
struct afe_fb_therm_prot_rx_cfg_v1_t
{
   uint32_t       fb_therm_prot_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        thermal protection Rx configuration.

        @values #AFE_API_VERSION_FB_THERM_PROT_RX_CFG */

   int16_t        cntl_input;
   /**< Type of control input for temperature feed.

        @values
        - 0 -- Use the feedback temperature only
        - 1 -- Use the feedback temperature with the low pass filter
        - 2 -- Feed the forward estimated temperature @tablebulletend */

   int16_t        temp_loop_dly_ms;
   /**< Delay of predicted temperature feeding back to the Thermal Control
        module.

        @values 0 to 1000 ms */

   int16_t        pow_est_smooth;
   /**< Smoothing IIR filter flag for power estimation.

        @values
        - 0 -- Disable smoothing IIR filter
        - 1 -- Enable smoothing IIR filter @tablebulletend */

   int16_t        temp_tgt_q6;
   /**< Target control temperature.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_nominal_q6;
   /**< Initial voice coil temperature.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_min_q6;
   /**< Minimum reasonable measured temperature.

        A temperature lower than this setting is ignored.
        The temperature must not be higher than temp_nominal_q6 or temp_tgt_q6.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_max_q6;
   /**< Maximum reasonable measured temperature.

        A temperature higher than this setting is ignored.
        The temperature must not be lower than temp_nominal_q6 or temp_tgt_q6.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 12800 (200 degrees C in Q6 format) @tablebulletend */

   int16_t        temp_max_chg_sec_q6;
   /**< Maximum temperature change per second.
        A new temperature is ignored if it is outside this range.

        @values
        - 0 to 32767 (511.9 degrees C in Q6 format)
        - > 32767 -- Disable this feature @tablebulletend */

   int32_t        iir_tdc_c_num[AFE_FBSP_IIR_FILT_MAX_STAGES * 3];
   /**< Temperature smoothing IIR filter numerator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_den[AFE_FBSP_IIR_FILT_MAX_STAGES * 2];
   /**< Temperature smoothing IIR filter denominator coefficients.
        Unused filter coefficients must be set to zero.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_num_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
   /**< Integer part of the Q factor of the temperature smoothing IIR filter
        numerator coefficient.

        @values -2147483648 to 2147483647 */

   int32_t        iir_tdc_c_den_q[AFE_FBSP_IIR_FILT_MAX_STAGES];
   /**< Integer part of the Q factor of the temperature smoothing IIR filter
        denominator coefficient.

        @values -32 to 32 */

   int16_t        iir_tdc_c_stages;
   /**< Number of stages in the temperature smoothing IIR filter.

        @values 0 to 5 */

   int16_t        prop_x_q12;
   /**< Proportional term in Proportional and Integral (PI) control.

        @values 0 to 32767 (7.9 in Q12 format) */

   int16_t        intg_x_q12;
   /**< Integral term in PI control.

        @values 0 to 32767 (7.9 in Q12 format) */

   int16_t        min_gain_db_q7;
   /**< Minimum temperature control gain,

        @values -7680 to 0 (-60 dB in Q7 format) */

   int16_t        gain_alph_q15[2];
   /**< Smoothing of gain, attack (gain decreasing), and release (relaxing
        back to 0 dB).

        @values
        - Minimum -- 328 (0.01 dB in Q15 format)
        - Maximum -- 32767 (0.99 dB in Q15 format) @tablebulletend */

   int16_t        dead_zone_q6;
   /**< Dead zone (region near the target temperature) for a reduced
        proportional term.

        @values
        - Minimum -- 2 (0.03125 degrees C in Q6 format)
        - Maximum -- 2048 (32 degrees C in Q6 format) @tablebulletend */

   int16_t        dead_zone_sc_q15;
   /**< Scaling factor to modify the proportional term when inside a dead zone.

        @values
        - Minimum -- 328 (0.01 in Q15 format)
        - Maximum -- 32767 (0.99 in Q15 format) @tablebulletend */

   uint16_t        rx_scale_u16_q16;
   /**< Factor for scaling down the signal such that adding a pilot tone
        does not cause clipping.

        @values
        - Minimum -- 32768 (0.5 in Q16 format)
        - Maximum -- 65535 (0.99 in Q16 format) @tablebulletend */

   uint16_t        pi_scale_u16_q18;
   /**< Scale factor for the pilot tone relative to 0 dBFs
        (for example, -40 dB from the full scale).

        @values 0 to 65535 (0.249 in Q18 format) */

   int32_t        clip_time_out_ms;
   /**< Clip interrupt timeout. A value greater than zero means the clip
        interrupt support feature is enabled with this timeout.

        @values 0 to 4000 ms */

   int32_t        vbat_time_out_ms;
   /**< Battery Voltage (VBAT) timeouts. A value greater than zero means the
        VBAT interrupt support feature is enabled with this timeout.

        @values 0 to 1000000 ms */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fb_therm_prot_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure
    feedback excursion control Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fb_excur_cntl_rx_cfg_v1_t}
    @table{weak__afe__fb__excur__cntl__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FB_EXCUR_CNTL_RX_CFG                               0x00010223

/** Version information used to handle future additions to
    AFE_PARAM_ID_FB_EXCUR_CNTL_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FB_EXCUR_CNTL_RX_CFG                          0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fb_excur_cntl_rx_cfg_v1_t afe_fb_excur_cntl_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fb_excur_cntl_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FB_EXCUR_CNTL_RX_CFG parameter (version 1).
*/
struct afe_fb_excur_cntl_rx_cfg_v1_t
{
   uint32_t       excur_cntl_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        excursion control Rx configuration.

        @values #AFE_API_VERSION_FB_EXCUR_CNTL_RX_CFG */

   int16_t        f_limiter_only;
   /**< Specifies how the limiter is enabled.

        @values
        - 0 -- Limiter + excursion control
        - 1 -- Limiter only @tablebulletend */

   int16_t        cutoff_freq;
   /**< Cutoff frequency for signal modification.

        @values 1000 to 4000 Hz */

   int32_t        amp_gain_l32_q24;
   /**< Constant gain representing the flat frequency response from the \n
        DAC to the speaker driver.
        This is the RMS voltage at the loudspeaker when 0 dB full-scale tone
        at 1 kHz is played in the digital domain.

        This setting allows for a negative value for phase inversion.

        @values
        - Minimum -- -2147483648 (-128 in Q24 format)
        - Maximum -- 2147483647 (127.99 in Q24 format) @tablebulletend */

   int32_t        margin_l32_q24;
   /**< Control parameter to allow for overestimation of peak excursion.

        @values
        - Minimum -- 8388608 (0.5 in Q24 format)
        - Maximum -- 33554432 (2 in Q24 format) @tablebulletend */

   int32_t        x_max_l32_q24;
   /**< Speaker excursion limit.

        @values
        - Minimum -- 167772 (0.01 mm in Q24 format)
        - Maximum -- 167772160 (10 mm in Q24 format) @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fb_excur_cntl_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure the
    Audio Clip Manager (ACM) for feedback speaker protection Rx processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_acm_rx_cfg_v1_t}
    Version 1 of the configuration structure.
    @tablens{weak__afe__fbsp__acm__rx__cfg__v1__t}

    @apr_msgpayload{afe_fbsp_acm_rx_cfg_v2_t}
    Version 2 of the configuration structure. It includes support for
    the loudness boost feature (loudnessBoostEn and loudnessThresholdQ27).
    @tablens{weak__afe__fbsp__acm__rx__cfg__v2__t}
*/
#define AFE_PARAM_ID_FBSP_ACM_RX_CFG                                    0x00010224

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_ACM_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_ACM_RX_CFG                               0x2

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_acm_rx_cfg_v2_t afe_fbsp_acm_rx_cfg_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_acm_rx_cfg_v2_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_ACM_RX_CFG parameter (version 2).
    Loudness boost support is added. The following variables are added:
    - loudnessBoostEn
    - loudnessThresholdQ27
*/
struct afe_fbsp_acm_rx_cfg_v2_t
{
   uint32_t       fbsp_acm_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        protection ACM configuration.

        @values #AFE_API_VERSION_FBSP_ACM_RX_CFG */

   int16_t        lim_to_clip_thr_ratio_q15;
   /**< Limiter threshold to clip the level ratio.

        @values
        - Minimum -- 16384 (0.5 in Q15 format)
        - Maximum -- 32767 (0.99 in Q15 format) @tablebulletend */

   int16_t        lowest_acc_clip_level_q15;
   /**< Lowest acceptable clip level. Any clipping detecting below this level
        is ignored.

        @values 0 to 26214 (0.799 in Q15 format) */

   int16_t        thr_inc_step_in_db_q15;
   /**< Limiter threshold increment per step_size_in_msec.

        @values 0 to 32767 (0.99 dB in Q15 format) */

   uint16_t        step_size_in_msec;
   /**< Step size for the limiter threshold increment.

        @values 1 to 10000 ms */

   uint32_t        spk_prot_acm_clip_lvl_det_mthd;
   /**< Methods for clip-level detection.

        In the Codec Maximum Value and Codec History buffer methods, the
        clip-level detection is performed in the codec.

        In the Library History buffer, the clip-level detection is performed
        in the aDSP. Do not use this method because it requires more processing
        and has lower quality than the Codec Maximum Value or Codec History
        buffer methods.

        @values
        - 0 -- Codec Maximum Value
        - 1 -- Codec History buffer
        - 2 -- Library History buffer @tablebulletend */

   int32_t           loudness_threshold_q27;
   /**< Maximum limiter threshold in loudness boost mode. This parameter is
        considered only when loudness_boost is enabled (in dBFS).

        @values
        - Minimum -- 67108864   (-6 in Q27 format)
        - Maximum -- 134217727  (0 in Q27 format) @tablebulletend */

   uint16_t          loudness_boost_en;
   /**< Loudness boost mode enable/disable flag.

        @values
        - 0 -- Disable
        - 1 -- Enable  @tablebulletend */

   uint16_t          reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_acm_rx_cfg_v2_t */

typedef struct afe_fbsp_acm_rx_cfg_v1_t afe_fbsp_acm_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_acm_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_ACM_RX_CFG parameter (version 1).
*/
struct afe_fbsp_acm_rx_cfg_v1_t
{
   uint32_t       fbsp_acm_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker
        protection ACM configuration.

        @values #AFE_API_VERSION_FBSP_ACM_RX_CFG */

   int16_t        lim_to_clip_thr_ratio_q15;
   /**< Limiter threshold to clip the level ratio.

        @values
        - Minimum -- 16384 (0.5 in Q15 format)
        - Maximum -- 32767 (0.99 in Q15 format) @tablebulletend */

   int16_t        lowest_acc_clip_level_q15;
   /**< Lowest acceptable clip level. Any clipping detecting below this level
        is ignored.

        @values 0 to 26214 (0.799 in Q15 format) */

   int16_t        thr_inc_step_in_db_q15;
   /**< Limiter threshold increment per step_size_in_msec.

        @values 0 to 32767 (0.99 dB in Q15 format) */

   uint16_t        step_size_in_msec;
   /**< Step size for the limiter threshold increment.

        @values 1 to 10000 ms */

   uint32_t        spk_prot_acm_clip_lvl_det_mthd;
   /**< Methods for clip-level detection.

        In the Codec Maximum Value and Codec History buffer methods, the
        clip-level detection is performed in the codec.

        In the Library History buffer, the clip-level detection is performed
        in the aDSP. Do not use this method because it requires more processing
        and has lower quality than the Codec Maximum Value or Codec History
        buffer methods.

        @values
        - 0 -- Codec Maximum Value
        - 1 -- Codec History buffer
        - 2 -- Library History buffer @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_acm_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure the
    ACM Codec mode for feedback speaker protection Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_acm_cdc_rx_cfg_v1_t}
    @table{weak__afe__fbsp__acm__cdc__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FBSP_ACM_CDC_RX_CFG                                0x00010225

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_ACM_CDC_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_ACM_CDC_RX_CFG                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_acm_cdc_rx_cfg_v1_t afe_fbsp_acm_cdc_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_acm_cdc_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_ACM_CDC_RX_CFG parameter (version 1).
*/
struct afe_fbsp_acm_cdc_rx_cfg_v1_t
{
   uint32_t       fbsp_acm_cdc_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection ACM codec
        Rx mode configuration.

        @values #AFE_API_VERSION_FBSP_ACM_CDC_RX_CFG */

   uint16_t        cdc_clip_det_trigger_thr;
   /**< Number of triggers the codec waits for before asserting the clip
        interrupt.

        @values 1 to 12 */

   uint16_t        num_cdc_fifos;
   /**< Depth of the trigger FIFO queue in the codec.

        @values 1 to 12 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_acm_cdc_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to configure
    excursion parameters for feedback speaker protection Rx processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_ex_param_rx_cfg_v1_t}
    @table{weak__afe__fbsp__ex__param__rx__cfg__v1__t}
*/
#define AFE_PARAM_ID_FBSP_EX_PARAM_RX_CFG                                0x0001023b

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_EX_PARAM_RX_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_EX_PARAM_RX_CFG                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_ex_param_rx_cfg_v1_t afe_fbsp_ex_param_rx_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_ex_param_rx_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_EX_PARAM_RX_CFG parameter (version 1).
*/
struct afe_fbsp_ex_param_rx_cfg_v1_t
{
   uint32_t       fbsp_ex_param_rx_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection
        excursion parameter Rx processing configuration.
        Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_EX_PARAM_RX_CFG */

   uint32_t        cx_data_size_in_bytes;
   /**< Size of the excursion control data in bytes.

        @values All valid sizes */

   uint32_t        cx_data_addr_lsw;
   /**< Lower 32 bits of the 64-bit payload address. */

   uint32_t        cx_data_addr_msw;
   /**< Upper 32 bits of the 64-bit payload address.

         The 64-bit number formed by cx_data_addr_lsw and cx_data_addr_msw
         word must be contiguous memory, and it must be 4 KB aligned.

        @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value. @tablebulletend */

   uint32_t        mem_map_handle;
   /**< Unique identifier for an address.

        @values
        - NULL -- The message is in the payload (in-band).
        - Non-NULL -- The parameter data payload begins at the address
          specified by a pointer to the payload's physical address in shared
          memory (out-of-band).

        This memory map handle is returned by the aDSP through
        #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

        An optional field is available if parameter data is in-band:
        %afe_port_param_data_v2_t param_data[...].
        For detailed payload content, see afe_port_param_data_v2_t. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_ex_param_rx_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to log thermal
    Rx processing statistics for feedback speaker protection.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_fbsp_th_rx_stats_v1_t}
    @table{weak__afe__fbsp__th__rx__stats__v1__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_FBSP_TH_RX_STATS                                0x0001023c

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_TH_RX_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_TH_RX_STATS                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_th_rx_stats_v1_t afe_fbsp_th_rx_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_th_rx_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_TH_RX_STATS parameter (version 1).
*/
struct afe_fbsp_th_rx_stats_v1_t
{
   uint32_t       fbsp_th_rx_stats_minor_version;
   /**< Minor version used to track feedback speaker protection thermal
        Rx processing statistics. Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_TH_RX_STATS */

   uint32_t        frame_duration_in_ms;
   /**< Frame duration in milliseconds for thermal variables.

        @values Valid uint32 number */

   uint32_t        frame_num;
   /**< Frame number of the thermal variables. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

   int32_t        th_gain_dB_q23;
   /**< Thermal gain in dB.

        @values Valid int32 number (in Q23 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_th_rx_stats_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to log excursion
    tuning Rx processing statistics for feedback speaker protection.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_fbsp_ex_rx_stats_v1_t}
    @table{weak__afe__fbsp__ex__rx__stats__v1__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_FBSP_EX_RX_STATS                                0x0001023d

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_EX_RX_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_EX_RX_STATS                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_ex_rx_stats_v1_t afe_fbsp_ex_rx_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_ex_rx_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_EX_RX_STATS parameter (version 1).
*/
struct afe_fbsp_ex_rx_stats_v1_t
{
   uint32_t       fbsp_ex_rx_stats_minor_version;
   /**< Minor version used to track feedback speaker protection log
        excursion Rx tuning statistics. Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_EX_RX_STATS */

   uint32_t        frame_duration_in_ms;
   /**< Frame duration in milliseconds for excursion variables.

        @values Valid uint32 number */

   uint32_t        frame_num;
   /**< Frame number of the excursion variables. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

   int16_t        max_exc;
   /**< Peak excursion (in millimeters).

        @values Valid int16 number (in Q15 format) */

   int16_t                 reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_ex_rx_stats_v1_t */

/** @addtogroup afe_module_feedback_spkr_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_RX to log audio clip
    interrupt statistics for feedback speaker protection.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_fbsp_clip_int_stats_v1_t}
    @table{weak__afe__fbsp__clip__int__stats__v1__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_FBSP_CLIP_INT_STATS                               0x0001023e

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_CLIP_INT_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_CLIP_INT_STATS                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_rx */

typedef struct afe_fbsp_clip_int_stats_v1_t afe_fbsp_clip_int_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_clip_int_stats_v1_t
@{ */
/* Configuration structure for the
    #AFE_PARAM_ID_FBSP_CLIP_INT_STATS parameter (version 1).
*/
struct afe_fbsp_clip_int_stats_v1_t
{
   uint32_t       fbsp_clip_int_stats_minor_version;
   /**< Minor version used to track feedback speaker protection clip
        interrupt statistics. Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_CLIP_INT_STATS */

   uint32_t        frame_duration_in_ms;
   /**< Frame duration in milliseconds for the clip interrupt.

        @values Valid uint32 number */

   uint32_t        frame_num;
   /**< Frame number of the clip interrupt variables. This field is reset to
        zero after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

   uint32_t        clip_interrupt;
   /**< Audio clip interrupt.

        @values Valid uint32 number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_clip_int_stats_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the Feedback Speaker Protection Vsens/Isens (VI) processing module,
    which supports the following parameter IDs:
     - #AFE_PARAM_ID_MODE_VI_PROC_CFG
     - #AFE_PARAM_ID_THERMAL_VI_PROC_CFG
     - #AFE_PARAM_ID_EXCURSION_VI_PROC_CFG
     - #AFE_PARAM_ID_SPKR_CALIB_VI_PROC_CFG
     - #AFE_PARAM_ID_CALIB_RES_CFG
     - #AFE_PARAM_ID_FEEDBACK_PATH_CFG
     - #AFE_PARAM_ID_TUNING_VI_PROC_CFG
     - #AFE_PARAM_ID_FBSP_EX_VI_STATS
     - #AFE_PARAM_ID_SPKR_COIL_TX_RX_CFG
     - #AFE_PARAM_ID_ENABLE

    @apr_hdr_fields
    Opcode -- AFE_MODULE_FB_SPKR_PROT_VI_PROC

    @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the Speaker Protection module using
       #AFE_PORT_CMD_SET_PARAM_V2 and #AFE_MODULE_SPEAKER_PROTECTION,
       .including both parameters, #AFE_PARAM_ID_SPKR_PROT_CONFIG and
       #AFE_PARAM_ID_ENABLE.
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port when needed using #AFE_PORT_CMD_DEVICE_STOP (the AFE
       destroys all speaker protection-related information).
    @par
    This module is accepted only in the Configuration state of the port
    (after AFE_MODULE_AUDIO_DEV_INTERFACE and before
    AFE_PORT_CMD_DEVICE_START.
    @par
    The feedback speaker protection VI processing module is supported only on
    a 16-bit stereo Tx port running at a sampling rate of 48000 Hz. @newpage

    @inputfile{group__weakb__afe__fbsp__feedback__path__cfg__v1__t.tex}
*/
#define AFE_MODULE_FB_SPKR_PROT_VI_PROC                               0x00010226

/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    the mode of feedback speaker protection VI processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_mode_vi_proc_cfg_v1_t}
    @table{weak__afe__fbsp__mode__vi__proc__cfg__v1__t}
*/
#define AFE_PARAM_ID_MODE_VI_PROC_CFG                                 0x00010227

/** Version information used to handle future additions to
    AFE_PARAM_ID_MODE_VI_PROC_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_MODE_VI_PROC_CFG                            0x1

/** Calibration mode is disabled. */
#define AFE_FBSP_CALIB_MODE_DISABLE     0

/** Calibration mode is enabled. @newpage */
#define AFE_FBSP_CALIB_MODE_ENABLE         1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_mode_vi_proc_cfg_v1_t afe_fbsp_mode_vi_proc_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_mode_vi_proc_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_MODE_VI_PROC_CFG parameter (version 1).
*/
struct afe_fbsp_mode_vi_proc_cfg_v1_t
{
   uint32_t       mode_vi_proc_cfg_minor_version;
   /**< Minor version used to track speaker protection VI Processing mode
        configuration.

        @values #AFE_API_VERSION_MODE_VI_PROC_CFG */

   uint32_t        cali_mode;
   /**< Specifies whether the Calibration mode is enabled.

        @values
        - #AFE_FBSP_CALIB_MODE_DISABLE
        - #AFE_FBSP_CALIB_MODE_ENABLE @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_mode_vi_proc_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    thermal VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_thermal_vi_proc_cfg_v1_t}
    @table{weak__afe__fbsp__thermal__vi__proc__cfg__v1__t}
*/
#define AFE_PARAM_ID_THERMAL_VI_PROC_CFG                                0x00010228

/** Version information used to handle future additions to
    AFE_PARAM_ID_THERMAL_VI_PROC_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_THERMAL_VI_PROC_CFG                            0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_thermal_vi_proc_cfg_v1_t afe_fbsp_thermal_vi_proc_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_thermal_vi_proc_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_THERMAL_VI_PROC_CFG parameter (version 1).
*/
struct afe_fbsp_thermal_vi_proc_cfg_v1_t
{
   uint32_t       therm_vi_proc_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection thermal
        VI processing configuration.

        @values #AFE_API_VERSION_THERMAL_VI_PROC_CFG */

   int32_t        v_meas_bias_q26;
   /**< Biased value of voltage measured to avoid division by 0.

        @values
        - Minimum -- 537 (0.000008 volt in Q26 format)
        - Maximum -- 536871 (0.008 volt in Q26 format) @tablebulletend */

   int32_t        i_meas_bias_q26;
   /**< Biased value of current measured to avoid division by zero.

        @values
        - Minimum -- 67 (0.000001 amp in Q26 format)
        - Maximum -- 67109 (0.001 amp in Q26 format) @tablebulletend */

   int32_t        r0_safe_q24;
   /**< Default calibration point resistance when per-device calibration is
        not available.

        @values
        - Minimum -- 33554432 (2 Ohms in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   int16_t        t0_safe_q6;
   /**< Default calibration point temperature when per-device
        calibration is not available.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 5120 ( 80 degrees C in Q6 format) @tablebulletend */

   int16_t        pow_sup_freq;
   /**< Power supply frequency.

        @values
        - 50 or 60 Hz
        - 0 -- Disabled @tablebulletend */

   uint16_t        vsen_2_v_u16_q12;
   /**< Conversion factor for Vsens digital to volts.

        @values 0 to 65535 (15.99 in Q12 format) */

   uint16_t        isen_2_a_u16_q12;
   /**< Conversion factor for Isens digital to amps.

        @values 0 to 65535 (15.99 in Q12 format) */

   int32_t        r0_short_q24;
   /**< Resistance below this speaker is considered a shorted circuit.

        @values
        - Minimum -- 8388608 (0.5 Ohm in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   int32_t        r0_open_q24;
   /**< Resistance above this speaker is considered an open circuit.

        @values
        - Minimum -- 16777216 (1 Ohm in Q24 format)
        - Maximum -- 2147483647 (127.99 Ohms in Q24 format) @tablebulletend */

   int32_t        wait_time_ms;
   /**< Wait time for initial settling before collecting statistics during
        calibration.

        @values 100 to 5000 ms */

   int32_t        cali_time_ms;
   /**< Calibration time.

        @values 500 to 30000 ms */

   int32_t        r0_min_q24;
   /**< Minimum expected resistance from calibration.

        @values
        - Minimum -- 33554432 (2 Ohms in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   int32_t        r0_max_q24;
   /**< Maximum expected resistance from calibration.

        @values
        - Minimum -- 33554432 (2 Ohms in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   int16_t        t0_min_q6;
   /**< Minimum expected temperature from calibration.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 5120 (80 degrees C in Q6 format) @tablebulletend */

   int16_t        t0_max_q6;
   /**< Maximum expected temperature from calibration.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 5120 (80 degrees C in Q6 format) @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_thermal_vi_proc_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    excursion parameters for feedback speaker protection VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_excursion_vi_proc_cfg_v1_t}
    @table{weak__afe__fbsp__excursion__vi__proc__cfg__v1__t}
*/
#define AFE_PARAM_ID_EXCURSION_VI_PROC_CFG                            0x00010229

/** Version information used to handle future additions to
    AFE_PARAM_ID_EXCURSION_VI_PROC_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_EXCURSION_VI_PROC_CFG                        0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_excursion_vi_proc_cfg_v1_t afe_fbsp_excursion_vi_proc_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_excursion_vi_proc_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_EXCURSION_VI_PROC_CFG parameter (version 1).
*/
struct afe_fbsp_excursion_vi_proc_cfg_v1_t
{
   uint32_t       excursion_vi_proc_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection excursion
        VI Processing mode configuration.

        @values #AFE_API_VERSION_EXCURSION_VI_PROC_CFG */

   int32_t        v_scale_l32_q24;
   /**< Scaling factor for Vsens. To allow for phase inversion, set this
        field to a negative value.

        @values
        - Minimum -- -2147483648 (-128 in Q24 format)
        - Maximum -- 2147483647 (127.99 in Q24 format) @tablebulletend */

   int32_t        i_scale_l32_q24;
   /**< Scaling factor for Isens. To allow for phase inversion, set this
        field to a negative value.

        @values
        - Minimum -- -2147483648 (-128 in Q24 format)
        - Maximum -- 2147483647 (127.99 in Q24 format) @tablebulletend */

   int16_t        f_param_adaptation;
   /**< Enables (1) or disables (0) speaker parameter adaptation. */

   int16_t        rx_cutoff_freq;
   /**< Cutoff frequency for signal processing.

        @values 1000 to 4000 Hz */

   int32_t        rx_amp_gain_l32_q24;
   /**< Amplifier gain in the codec.

        @values
        - Minimum -- -2147483648 (-128 in Q24 format)
        - Maximum -- 2147483647 (127.99 in Q24 format) @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_excursion_vi_proc_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    calibration for feedback speaker VI calibration processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_spkr_calib_vi_proc_cfg_v1_t}
    @table{weak__afe__fbsp__spkr__calib__vi__proc__cfg__v1__t}
*/
#define AFE_PARAM_ID_SPKR_CALIB_VI_PROC_CFG                            0x0001022A

/** Version information used to handle future additions to
    AFE_PARAM_ID_SPKR_CALIB_VI_PROC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SPKR_CALIB_VI_PROC_CFG                       0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_spkr_calib_vi_proc_cfg_v1_t afe_fbsp_spkr_calib_vi_proc_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_spkr_calib_vi_proc_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SPKR_CALIB_VI_PROC_CFG parameter (version 1).
*/
struct afe_fbsp_spkr_calib_vi_proc_cfg_v1_t
{
   uint32_t       spkr_calib_vi_proc_cfg_minor_version;
   /**< Minor version used to track feedback speaker VI calibration processing.

        @values #AFE_API_VERSION_SPKR_CALIB_VI_PROC_CFG */

   int32_t        r0_cali_q24;
   /**< Caliberation point resistance per device.

        @values
        - Minimum -- 33554432 (2 Ohms in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   int16_t        t0_cali_q6;
   /**< Caliberation point temperature per device. A valid value
        must be supplied both in Calibration mode and Processing mode.

        @values
        - Minimum -- -1920 (-30 degrees C in Q6 format)
        - Maximum -- 5120 (80 degrees C in Q6 format) @tablebulletend */

   int16_t        reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_spkr_calib_vi_proc_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to get the
    calibrated resistance value from the feedback speaker VI processing module.
    Only #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_calib_res_cfg_v1_t}
    @table{weak__afe__fbsp__calib__res__cfg__v1__t}
*/
#define AFE_PARAM_ID_CALIB_RES_CFG                                     0x0001022B

/** Version information used to handle future additions to
    AFE_PARAM_ID_CALIB_RES_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_CALIB_RES_CFG                               0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_calib_res_cfg_v1_t afe_fbsp_calib_res_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_calib_res_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_CALIB_RES_CFG parameter (version 1).
*/
struct afe_fbsp_calib_res_cfg_v1_t
{
   uint32_t       spkr_calib_res_tx_cfg_minor_version;
   /**< Minor version used to track feedback speaker VI processing
        calibrated resistance configuration.

        @values #AFE_API_VERSION_CALIB_RES_CFG */

   int32_t        r0_cali_q24;
   /**< Calibrated resistance per device.

        @values
        - Minimum -- 33554432 (2 Ohms in Q24 format)
        - Maximum -- 1073741824 (64 Ohms in Q24 format) @tablebulletend */

   uint32_t        th_vi_ca_state;
   /**< Specifies the calibration state.

        @values
        - 0 -- Reserved
        - 1 -- Calibration is in progress
        - 2 -- Calibration was successful
        - 3 -- Calibration has failed @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_calib_res_cfg_v1_t */

/** @weakgroup weakb_afe_fbsp_feedback_path_cfg_v1_t
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    a feedback connection between speaker protection Tx and Rx processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_fbsp_feedback_path_cfg_v1_t}
    @table{weak__afe__fbsp__feedback__path__cfg__v1__t}
*/
#define AFE_PARAM_ID_FEEDBACK_PATH_CFG                         0x0001022C

/** Version information used to handle future additions to
    AFE_PARAM_ID_FEEDBACK_PATH_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_FEEDBACK_PATH_CFG                      0x1

/** Vsens comes from the left speaker. */
#define AFE_FBSP_VSENS_LEFT_CHAN                1

/** Isens comes from the left speaker. */
#define AFE_FBSP_ISENS_LEFT_CHAN                2

/** Vsens comes from the right speaker. */
#define AFE_FBSP_VSENS_RIGHT_CHAN                3

/** Isens comes from the right speaker. */
#define AFE_FBSP_ISENS_RIGHT_CHAN                4

/** Maximum number of VI channels supported. @newpage */
#define AFE_FBSP_VI_CHAN_MAX                    4

/** @} */ /* end_weakgroup weakb_afe_fbsp_feedback_path_cfg_v1_t */

typedef struct afe_fbsp_feedback_path_cfg_v1_t afe_fbsp_feedback_path_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_feedback_path_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FEEDBACK_PATH_CFG parameter (version 1).
*/
struct afe_fbsp_feedback_path_cfg_v1_t
{
   uint32_t       feedback_path_cfg_minor_version;
   /**< Minor version used to track feedback speaker protection Tx and Rx
        processing configuration.

        @values #AFE_API_VERSION_FEEDBACK_PATH_CFG */

   int32_t        dst_portid;
   /**< Destination Rx port ID. It must be the same Rx port ID for
        which feedback speaker protection is configured.

        @values See <i>Supported Hardware Ports</i> for the applicable
                chipset in Chapter @xref{chp:portIDs} */

   int32_t        num_channels;
   /**< Number of Tx port channels. Each Vsens and Isens is considered an
        individual channel.

        @values
        - 2 -- Mono speaker
        - 4 -- Stereo speakers @tablebulletend */

   int32_t        chan_info[AFE_FBSP_VI_CHAN_MAX];
   /**< Channel mapping array that provides information on the order in
        which the Vsens and Isens of different speakers come into a Tx port.

        @values
        - #AFE_FBSP_VSENS_LEFT_CHAN
        - #AFE_FBSP_ISENS_LEFT_CHAN
        - #AFE_FBSP_VSENS_RIGHT_CHAN
        - #AFE_FBSP_ISENS_RIGHT_CHAN 

        All channels must be unique. The order is not important as long as the
        channels are valid.

        If only two channels are sent (Vsens and Isens), they must be the
        first two channels. For example, (4,3,0,0) or (1,2,0,0). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_feedback_path_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to configure
    the Tuning mode for feedback speaker VI processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_tuning_vi_proc_cfg_v1_t}
    @table{weak__afe__tuning__vi__proc__cfg__v1__t}
*/
#define AFE_PARAM_ID_TUNING_VI_PROC_CFG                                     0x0001023f

/** Version information used to handle future additions to
    AFE_PARAM_ID_TUNING_VI_PROC_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_TUNING_VI_PROC_CFG                               0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_tuning_vi_proc_cfg_v1_t afe_tuning_vi_proc_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_tuning_vi_proc_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_TUNING_VI_PROC_CFG parameter (version 1).
*/
struct afe_tuning_vi_proc_cfg_v1_t
{
   uint32_t       tuning_vi_proc_cfg_minor_version;
   /**< Minor version used to track feedback speaker VI processing Tuning
        mode configuration. Currently, the supported version is 1.

        @values #AFE_API_VERSION_TUNING_VI_PROC_CFG */

   int32_t        ex_tuning_mode;
   /**< Specifies whether the Tuning mode for excursion VI processing is
        enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_tuning_vi_proc_cfg_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to log thermal
    statistics for feedback speaker protection thermal VI processing.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_fbsp_th_vi_stats_v1_t}
    @table{weak__afe__fbsp__th__vi__stats__v1__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_FBSP_TH_VI_STATS                                0x00010240

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_TH_VI_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_TH_VI_STATS                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_th_vi_stats_v1_t afe_fbsp_th_vi_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_th_vi_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_TH_VI_STATS parameter (version 1).
*/
struct afe_fbsp_th_vi_stats_v1_t
{
   uint32_t       fbsp_th_vi_stats_minor_version;
   /**< Minor version used to track feedback speaker protection thermal
        VI processing statistics. Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_TH_VI_STATS */

   uint32_t        frame_duration_in_ms;
   /**< Frame duration in milliseconds for thermal VI processing variables.

        @values Valid uint32 number */

   uint32_t        frame_num;
   /**< Frame number of the thermal variables. This field is reset to zero
        after crossing the maximum limit for a uint32 variable.

        @values Valid uint32 number */

   int32_t        x_r_q24;
   /**< Speaker coil resistance (in Ohms).

        @values Valid int32 number (in Q24 format) */

   int32_t        x_t_q22;
   /**< Speaker coil temperature (degrees C).

        @values Valid int32 number (in Q22 format) */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_th_vi_stats_v1_t */

/** @addtogroup afe_module_feedback_spkr_vi
@{ */
/** ID of the parameter used by #AFE_MODULE_FB_SPKR_PROT_VI_PROC to log
    excursion tuning statistics for feedback speaker VI processing.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_fbsp_ex_vi_stats_v1_t}
    @table{weak__afe__fbsp__ex__vi__stats__v1__t}

  @if OEM_only
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_FBSP_EX_VI_STATS                                0x00010241

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_EX_VI_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_FBSP_EX_VI_STATS                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_fbsp_ex_vi_stats_v1_t afe_fbsp_ex_vi_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_fbsp_ex_vi_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_FBSP_EX_VI_STATS parameter (version 1).
*/
struct afe_fbsp_ex_vi_stats_v1_t
{
   uint32_t       fbsp_ex_vi_stats_minor_version;
   /**< Minor version used to track feedback speaker protection excursion
        VI processing statistics. Currently, the supported version is 1.

        @values #AFE_API_VERSION_FBSP_EX_VI_STATS */

   uint32_t        frame_duration_in_ms;
   /**< Frame duration in milliseconds for excursion variables.

        @values Valid uint32 number */

   uint32_t        frame_num;
   /**< Frame number of the excursion variables. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

   int32_t        re_l32_q24;
   /**< Voice coil resistance (in Ohms).

        @values Valid int32 number (in Q24 format) */

   int32_t        le_l32_q24;
   /**< Voice coil inductance (in mH).

        @values Valid int32 number (in Q24 format) */

   int32_t        bl_l32_q24;
   /**< Force factor.

        @values Valid int32 number (in Q24 format) */

   int32_t        fct_l32_q20;
   /**< Resonance frequency (in Hertz).

        @values Valid int32 number (in Q20 format) */

   int32_t        q_mct_l32_q24;
   /**< Mechanical Q factor.

        @values Valid int32 number (in Q24 format) */

   int32_t        rect_l32_q24;
   /**< Mechanical resistance (in Ohms).

        @values Valid int32 number (in Q24 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_fbsp_ex_vi_stats_v1_t */

/** @ingroup afe_cmd_svc_set_params
    Configures one or more parameters to the AFE service.

  @apr_hdr_fields
    Opcode -- AFE_SVC_CMD_SET_PARAM

  @apr_msgpayload{afe_svc_cmd_set_param_t}
    @table{weak__afe__svc__cmd__set__param__t} @newpage

  @par Parameter data variable payload (afe_svc_param_data_t)
    @tablens{weak__afe__svc__param__data__t}

  @description
    This command is sent from the client to the aDSP to set the parameters of
    AFE service. Typically, this command is used to apply global calibration
    data. A single command can be used to set multiple parameters, each
    belonging to multiple modules.
    @par
    Messages can be either in-band or out-of-band via shared memory. The modes
    are:
    - In-band set parameter -- In this mode, the physical address is set to
      NULL. The rest of the payload contains the parameters as shown in the
      parameter data variable payload structure (%afe_svc_param_data_t).
    - Shared memory set parameter -- In this mode, both the physical address to
      the parameter data and the data payload size are sent. The rest of the
      message is inside the shared memory in the parameter data variable
      payload format. The memory content is the same as the in-band payload
      structure (%afe_svc_param_data_t).

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).

  @dependencies
    None.
*/
#define AFE_SVC_CMD_SET_PARAM                                      0x000100f3

/* Payload of the AFE parameter data. */
typedef struct afe_svc_param_data_t afe_svc_param_data_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_svc_param_data_t
@{ */
/* Payload of the AFE parameter data used by AFE_SVC_CMD_SET_PARAM. */
/** Immediately following this structure is the actual calibration data for the
    module_id/param_id pair.
*/
struct afe_svc_param_data_t
{
   uint32_t module_id;
   /**< ID of the module to be configured.

        @values Valid module ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint32_t param_id;
   /**< ID of the parameter corresponding to the supported parameters
        for the module ID.

        @values Valid parameter ID (See Chapter @xref{hdr:CalibrationIDs}) */

   uint16_t param_size;
   /**< Actual size of the data for the module_id/param_id pair. The size is a
        multiple of four bytes.

        @values > 0 */

   uint16_t reserved;
   /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_svc_param_data_t */

/* Payload of configuration/calibration settings for the AFE Service. */
typedef struct afe_svc_cmd_set_param_t afe_svc_cmd_set_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_svc_cmd_set_param_t
@{ */
/* Payload of the AFE_SVC_CMD_SET_PARAM command's
    configuration/calibration settings for the AFE service.
*/
struct afe_svc_cmd_set_param_t
{
   uint32_t payload_size;
   /**< Actual size of the payload in bytes. This is used for parsing the
        parameter payload.

        @values > 0 */

   uint32_t payload_address_lsw;
   /**< Lower 32 bits of the 64-bit payload address. */

   uint32_t payload_address_msw;
   /**< Upper 32 bits of the 64-bit payload address.

        The 64-bit number formed by payload_address_lsw and payload_address_msw
        word must be contiguous memory, and it must be 4 KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value. @tablebulletend */

   uint32_t mem_map_handle;
   /**< Unique identifier for an address.

        @values
        - NULL -- The message is in the payload (in-band).
        - Non-NULL -- The parameter data payload begins at the address
          specified by a pointer to the payload's physical address in shared
          memory (out-of-band).

        This memory map handle is returned by the aDSP through
        #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

        An optional field is available if parameter data is in-band:
        %afe_port_param_data_v2_t param_data[...].
        For detailed payload content, see afe_port_param_data_v2_t. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_svc_cmd_set_param_t */

/** @addtogroup afe_module_sw_mad
@{ */
/** ID of the Software Microphone Activity Detection (MAD) module, which
    supports the following parameter IDs:
    - #AFE_PARAM_ID_SW_MAD_CFG
    - #AFE_PARAM_ID_SVM_MODEL
    - #AFE_PARAM_ID_ENABLE

    @apr_hdr_fields
    Opcode -- AFE_MODULE_ID_SW_MAD
 */
#define AFE_MODULE_ID_SW_MAD                                       0x0001022D

/** ID of the parameter used by #AFE_MODULE_ID_SW_MAD to configure information for
    the software MAD algorithm. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this
    parameter ID.

    @apr_msgpayload{afe_sw_mad_cfg_param_v1_t}
    @table{weak__afe__sw__mad__cfg__param__v1__t}
 */
#define AFE_PARAM_ID_SW_MAD_CFG                                  0x0001022E

/** Version information used to handle future additions to
    AFE_PARAM_ID_FBSP_EX_VI_STATS processing (for backward compatibility).
    @newpage
 */
#define AFE_API_VERSION_SW_MAD_CONFIG                            0x1

/** @} */ /* end_addtogroup afe_module_sw_mad */

typedef struct afe_sw_mad_cfg_param_v1_t afe_sw_mad_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sw_mad_cfg_param_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_SW_MAD_CFG
 module (version 1).
 */
struct afe_sw_mad_cfg_param_v1_t
{
    uint32_t sw_mad_minor_version;
    /**< Minor version used to track software MAD configuration.

        @values #AFE_API_VERSION_SW_MAD_CONFIG */

    int32_t sw_mad_threshQ23;
    /**< Score threshold for the binary classifier.

        @values
         - Minimum -- -2147483648 (-256 in Q23 format)
         - Maximum -- 2139095040  (255 in Q23 format)
         - Default -- -511573 @tablebulletend */

    int16_t sw_mad_gain_Q8;
    /**< Gain value to multiply to input samples.

        @values
         - Minimum -- 32786 (-128 in Q8 format)
         - Maximum -- 32767 (127 in Q8 format)
         - Default -- 256 @tablebulletend */

    int16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sw_mad_cfg_param_v1_t */

/** @addtogroup afe_module_sw_mad
@{ */
/** ID of the Sound Vector Model (SVM) parameter used by #AFE_MODULE_ID_SW_MAD
    to configure information for the software MAD algorithm. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_svm_model_param_v1_t}
    @table{weak__afe__svm__model__param__v1__t}
 */
#define AFE_PARAM_ID_SVM_MODEL                                     0x0001022F

/** Version information used to handle future additions to
    AFE_PARAM_ID_SVM_MODEL processing (for backward compatibility). @newpage
 */
#define AFE_API_VERSION_SVM_MODEL                               0x1

/** @} */ /* end_addtogroup afe_module_sw_mad */

typedef struct afe_svm_model_param_v1_t afe_svm_model_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_svm_model_param_v1_t
@{ */
/* Configuration structure for the #AFE_PARAM_ID_SVM_MODEL
 module (version 1).
 */
struct afe_svm_model_param_v1_t
{
    uint32_t svm_model_minor_version;
    /**< Minor version used to track the SVM configuration interface.

        @values #AFE_API_VERSION_SVM_MODEL */

    uint32_t model_size_in_bytes;
    /**< Size in bytes of the SVM.

        @values All valid sizes*/

    uint32_t svm_model_addr_lsw;
    /**< Lower 32 bits of the 64-bit payload address for the SVM. */

    uint32_t svm_model_addr_msw;
    /**< Upper 32 bits of the 64-bit payload address for the SVM.

         The 64-bit number formed by svm_model_addr_lsw and svm_model_addr_msw
         word must be contiguous memory, and it must be 4 KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to zero.
         - For a 36-bit shared memory address, bits 31 to 4 must be set to zero.
         - For a 64-bit shared memory address, any 32-bit value. @tablebulletend */

    uint32_t mem_map_handle;
   /**< Unique identifier for an address.

        @values
        - NULL -- The message is in the payload (in-band).
        - Non-NULL -- The parameter data payload begins at the address
          specified by a pointer to the payload's physical address in shared
          memory (out-of-band).

        This memory map handle is returned by the aDSP through
        #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS.

        An optional field is available if parameter data is in-band:
        %afe_port_param_data_v2_t param_data[...].
        For detailed payload content, see afe_port_param_data_v2_t. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_svm_model_param_v1_t */

/** @addtogroup afe_module_hw_mad
@{ */
/** ID of the hardware MAD module, which supports the following parameter IDs:
    - #AFE_PARAM_ID_HW_MAD_CFG
    - #AFE_PARAM_ID_HW_MAD_CTRL
    - #AFE_PARAM_ID_SLIMBUS_SLAVE_PORT_CFG

    @apr_hdr_fields
    Opcode -- AFE_MODULE_HW_MAD
 */
#define AFE_MODULE_HW_MAD                                           0x00010230

/** ID of the parameter used by #AFE_MODULE_HW_MAD for hardware MAD
    configuration. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_hw_mad_cfg_param_v1_t}
    @table{weak__afe__hw__mad__cfg__param__v1__t}
 */
#define AFE_PARAM_ID_HW_MAD_CFG                                 0x00010231

/** Version information used to handle future additions to
    AFE_PARAM_ID_HW_MAD_CFG processing (for backward compatibility). @newpage
 */
#define AFE_API_VERSION_HW_MAD_CONFIG                            0x1

/** @} */ /* end_addtogroup afe_module_hw_mad */

typedef struct afe_hw_mad_cfg_param_v1_t afe_hw_mad_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_hw_mad_cfg_param_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_HW_MAD_CFG
 parameter (version 1).
 */
struct afe_hw_mad_cfg_param_v1_t
{
    uint32_t hw_mad_minor_version;
    /**< Minor version used to track hardware MAD configuration.

        @values #AFE_API_VERSION_HW_MAD_CONFIG */

    uint16_t audio_sleep_time_ms;
    /**< Sleep time for the MAD audio hardware.

         @values 0 to 60000 ms */

    uint16_t beacon_sleep_time_ms;
    /**< Sleep time for the MAD beacon hardware.

         @values 0 to 60000 ms */

    uint16_t us_sleep_time_ms;
    /**< Sleep time for the MAD ultrasound hardware.

         @values 0 to 60000 ms */

    int16_t reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_hw_mad_cfg_param_v1_t */

/** @addtogroup afe_module_hw_mad
@{ */
/** ID of the parameter used by #AFE_MODULE_HW_MAD to configure hardware MAD
    controls. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_hw_mad_ctrl_param_v1_t}
    @table{weak__afe__hw__mad__ctrl__param__v1__t}
*/
#define AFE_PARAM_ID_HW_MAD_CTRL                                 0x00010232

/** Version information used to handle future additions to
    AFE_PARAM_ID_HW_MAD_CTRL processing (for backward compatibility).
 */
#define AFE_API_VERSION_HW_MAD_CTRL                            0x1

/** Bit to enable/disable hardware MAD audio. */
#define AFE_HW_MAD_AUDIO_BIT            0x0

/** Bit to enable/disable MAD beacon. */
#define AFE_HW_MAD_BEACON_BIT           0x1

/** Bit to enable/disable MAD ultrasound. @newpage */
#define AFE_HW_MAD_ULT_BIT              0x2

/** @} */ /* end_addtogroup afe_module_hw_mad */

typedef struct afe_hw_mad_ctrl_param_v1_t afe_hw_mad_ctrl_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_hw_mad_ctrl_param_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_HW_MAD_CTRL
 parameter (version 1).
 */
struct afe_hw_mad_ctrl_param_v1_t
{
    uint32_t minor_version;
    /**< Minor version used to track hardware MAD control configuration.

        @values #AFE_API_VERSION_HW_MAD_CTRL */

    uint16_t mad_type;
    /**< Type of the MAD hardware block.
         Multiple paths can be enabled (1) or disabled (0) by setting the
         respective bits:
         - Set bit 0 to 1 for #AFE_HW_MAD_AUDIO_BIT
         - Set bit 1 to 1 for #AFE_HW_MAD_BEACON_BIT
         - Set bit 2 to 1 for #AFE_HW_MAD_ULT_BIT @tablebulletend */

    uint16_t mad_enable;
    /**< Enable (TRUE) or disable (FALSE) the MAD hardware paths for audio,
         ultrasound, and beacon. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_hw_mad_ctrl_param_v1_t */

/** @addtogroup afe_module_hw_mad
@{ */
/** ID of the parameter used by #AFE_MODULE_HW_MAD to configure a SLIMbus
    slave port. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_slimbus_slave_port_cfg_param_v1_t}
    @table{weak__afe__slimbus__slave__port__cfg__param__v1__t}
*/
#define AFE_PARAM_ID_SLIMBUS_SLAVE_PORT_CFG                             0x00010233

/** Version information used to handle future additions to
    AFE_PARAM_ID_SLIMBUS_SLAVE_PORT_CFG processing (for backward
    compatibility). @newpage
 */
#define AFE_API_VERSION_SLIMBUS_SLAVE_PORT_CFG                            0x1

/** @} */ /* end_addtogroup afe_module_hw_mad */

typedef struct afe_slimbus_slave_port_cfg_param_v1_t afe_slimbus_slave_port_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_slimbus_slave_port_cfg_param_v1_t
@{ */
/* AFE SLIMbus slave port configuration structure used by the
    AFE_PARAM_ID_SLIMBUS_SLAVE_PORT_CFG parameter (version 1).
 */
struct afe_slimbus_slave_port_cfg_param_v1_t
{
    uint32_t minor_version;
    /**< Minor version used to track SLIMbus slave port configuration.

        @values #AFE_API_VERSION_SLIMBUS_SLAVE_PORT_CFG */

    uint16_t slimbus_dev_id;
    /**< Type of the MAD hardware block.
         Multiple paths can be enabled (1) or disabled (0) by setting the
         respective bits in mad_type.

         @values
         - #AFE_SLIMBUS_DEVICE_1
         - #AFE_SLIMBUS_DEVICE_2 @tablebulletend*/

    uint16_t slave_dev_pgd_la;
    /**< Ported generic device's 8-bit logical address of the slave port.

        @values 0 to 255*/

    uint16_t slave_dev_intfdev_la;
    /**< Interface device's 8-bit logical address of the slave interface.

        @values 0 to 255*/

    uint16_t                  bit_width;
    /**< Bit width of the sample.

         @values 16, 24 */

    uint16_t                  data_format;
    /**< Data format supported by the SLIMbus hardware. The default indicates
         the hardware does not perform any format conversions before the data
         transfer.

         @values #AFE_SB_DATA_FORMAT_NOT_INDICATED (Default) */

    uint16_t num_chnnels;
    /**< Number of channels.

        @values 1 to #AFE_PORT_MAX_AUDIO_CHAN_CNT */

    uint16_t slave_port_mapping[AFE_PORT_MAX_AUDIO_CHAN_CNT];
    /**< Mapping of slave port IDs to which the master port is to be
         connected.

        @values 0 to 24*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_slimbus_slave_port_cfg_param_v1_t */

/** @addtogroup afe_module_cdc_device
@{ */
/** ID of the hardware Codec Device Configuration module, which supports the
    following parameter IDs:
    - #AFE_PARAM_ID_CDC_SLIMBUS_SLAVE_CFG
    - #AFE_PARAM_ID_CDC_REG_CFG
    - #AFE_PARAM_ID_CDC_AANC_VERSION
    - #AFE_PARAM_ID_CLIP_BANK_SEL_CFG
    - #AFE_PARAM_ID_CDC_REG_CFG_INIT

    @apr_hdr_fields
    Opcode -- AFE_MODULE_CDC_DEV_CFG
 */
#define AFE_MODULE_CDC_DEV_CFG                                     0x00010234

/** ID of the parameter used by #AFE_MODULE_CDC_DEV_CFG to configure a codec
    SLIMbus slave device. Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    @apr_msgpayload{afe_cdc_slimbus_slave_cfg_param_v1_t}
    @table{weak__afe__cdc__slimbus__slave__cfg__param__v1__t}
 */
#define AFE_PARAM_ID_CDC_SLIMBUS_SLAVE_CFG                        0x00010235

/** Version information used to handle future additions to
    AFE_PARAM_ID_CDC_SLIMBUS_SLAVE_CFG processing (for backward compatibility).
 */
#define AFE_API_VERSION_CDC_SLIMBUS_SLAVE_CFG                            0x1

/** @} */ /* end_addtogroup afe_module_cdc_device */

typedef struct afe_cdc_slimbus_slave_cfg_param_v1_t afe_cdc_slimbus_slave_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cdc_slimbus_slave_cfg_param_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_CDC_SLIMBUS_SLAVE_CFG
 module (version 1).
 */
struct afe_cdc_slimbus_slave_cfg_param_v1_t
{
    uint32_t slave_dev_minor_version;
    /**< Minor version used to track codec SLIMbus device configuration.

         @values #AFE_API_VERSION_CDC_SLIMBUS_SLAVE_CFG */

    uint32_t device_enum_addr_lsw;
    /**< Lower 16 bits of the SLIMbus slave device 48-bit enumeration address.
         The lower half comes first to be consistent with little endian
         architecture. */

    uint32_t device_enum_addr_msw;
    /**< Upper 16 bits of the SLIMbus slave device 48-bit enumeration address.

         @values
         - Bits 15 to 0 contain the upper 16 bits of the address
         - Bits 31 to 16 must be set to zero @tablebulletend */

    uint16_t tx_slave_port_offset;
    /**< Offset value that can be used for Tx slave ports.

         @values Valid offset value based on the hardware design
                 (refer to the applicable hardware interface specification) */

    uint16_t rx_slave_port_offset;
    /**< Offset value that can be used for Rx slave ports.

         @values Valid offset value based on the hardware design
                 (refer to the applicable hardware interface specification) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cdc_slimbus_slave_cfg_param_v1_t */

/** @addtogroup afe_module_cdc_device
@{ */
/** ID of the parameter used by #AFE_MODULE_CDC_DEV_CFG to configure the
    codec register. Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    @apr_msgpayload{afe_cdc_reg_cfg_param_v1_t}
    @table{weak__afe__cdc__reg__cfg__param__v1__t}
 */
#define AFE_PARAM_ID_CDC_REG_CFG                             0x00010236

/** Version information used to handle future additions to
    AFE_PARAM_ID_CDC_REG_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_CDC_REG_CFG                                    0x1

/** @xreflabel{First}
    AANC_REG_LPF_FF_FB (CDC_ANCn_LPF_B1_CTL) register. */
#define AFE_CRC_AANC_LPF_FF_FB                                        0x1

/** AANC_REG_LPF_COEFF_MSB (CDC_ANCn_LPF_B2_CTL) register. */
#define AFE_CRC_AANC_LPF_COEFF_MSB                                  0x2

/** AANC_REG_LPF_COEFF_LSB (CDC_ANCn_LPF_B3_CTL) register. */
#define AFE_CRC_AANC_LPF_COEFF_LSB                                     0x3

/** Hardware register field used to enable MAD audio detection. */
#define AFE_CRC_HW_MAD_AUDIO_ENABLE                                  0x4

/** Hardware register field used to enable MAD ultrasound detection. */
#define AFE_CRC_HW_MAD_ULTR_ENABLE                                    0x5

/** Hardware register field used to enable MAD beacon detection. */
#define AFE_CRC_HW_MAD_BEACON_ENABLE                                  0x6

/** Hardware register field used to configure MAD audio sleep time. */
#define AFE_CRC_HW_MAD_AUDIO_SLEEP_TIME                                0x7

/** Hardware register field used to configure MAD ultrasound sleep time. */
#define AFE_CRC_HW_MAD_ULTR_SLEEP_TIME                              0x8

/** Hardware register field used to configure MAD beacon sleep time. */
#define AFE_CRC_HW_MAD_BEACON_SLEEP_TIME                            0x9

/** Hardware register field used to switch off the MAD Tx audio path after
    detection. */
#define AFE_CRC_HW_MAD_TX_AUDIO_SWITCH_OFF                            0xA

/** Hardware register field used to switch off the MAD Tx ultrasound path after
    detection. */
#define AFE_CRC_HW_MAD_TX_ULTR_SWITCH_OFF                            0xB

/** Hardware register field used to switch off the MAD Tx beacon path after
    detection. */
#define AFE_CRC_HW_MAD_TX_BEACON_SWITCH_OFF                            0xC

/** Hardware register field used to route the MAD audio interrupt. */
#define AFE_CRC_MAD_AUDIO_INT_DEST_SELECT_REG                        0xD

/** Hardware register field used to route the MAD ultrasound interrupt. */
#define AFE_CRC_MAD_ULT_INT_DEST_SELECT_REG                            0xE

/** Hardware register field used to route the MAD beacon interrupt. */
#define AFE_CRC_MAD_BEACON_INT_DEST_SELECT_REG                        0xF

/** Hardware register field used to route the audio clip interrupt
    of speaker 1. */
#define AFE_CRC_CLIP_INT_DEST_SELECT_REG                            0x10

/** More meaningful macro for AFE_CRC_CLIP_INT_DEST_SELECT_REG.
    This macro helps distinguish between two speakers that are generating
    clip interrupts. */
#define AFE_CRC_SPKR_CLIP_INT_DEST_SELECT_REG                        AFE_CRC_CLIP_INT_DEST_SELECT_REG

/** Hardware register field used to route the VBAT attack interrupt. */
#define AFE_CRC_VBAT_INT_DEST_SELECT_REG                            0x11

/** More meaningful macro for AFE_CRC_VBAT_INT_DEST_SELECT_REG.
    This macro helps distinguish between ATTACK and RELEASE interrupts. */
#define AFE_CRC_VBAT_ATTACK_INT_DEST_SELECT_REG                        AFE_CRC_VBAT_INT_DEST_SELECT_REG

/** Hardware register field used to specify the MAD audio interrupt mask
    field. */
#define AFE_CRC_MAD_AUDIO_INT_MASK_REG                                0x12

/** Hardware register field used to specify the MAD ultrasound interrupt mask
    field. */
#define AFE_CRC_MAD_ULT_INT_MASK_REG                                0x13

/** Hardware register field used to specify the MAD beacon interrupt mask
    field. */
#define AFE_CRC_MAD_BEACON_INT_MASK_REG                                0x14

/** Hardware register field used to specify the audio clip interrupt
    mask field of speaker 1. */
#define AFE_CRC_CLIP_INT_MASK_REG                                    0x15

/** More meaningful macro for AFE_CRC_CLIP_INT_MASK_REG. This macro helps
    distinguish between two speakers that are generating clip interrupts. */
#define AFE_CRC_SPKR_CLIP_INT_MASK_REG                                AFE_CRC_CLIP_INT_MASK_REG

/** Hardware register field used to specify the VBAT attack interrupt mask
    field. */
#define AFE_CRC_VBAT_INT_MASK_REG                                    0x16

/** More meaningful macro for AFE_CRC_VBAT_INT_MASK_REG.
    This macro helps distinguish between ATTACK and RELEASE interrupts. */
#define AFE_CRC_VBAT_ATTACK_INT_MASK_REG                            AFE_CRC_VBAT_INT_MASK_REG

/** Hardware register field used to specify the MAD audio interrupt status
    field. */
#define AFE_CRC_MAD_AUDIO_INT_STATUS_REG                            0x17

/** Hardware register field used to specify the MAD ultrasound interrupt
    status field. */
#define AFE_CRC_MAD_ULT_INT_STATUS_REG                                0x18

/** Hardware register field used to specify the MAD beacon interrupt status
    field. */
#define AFE_CRC_MAD_BEACON_INT_STATUS_REG                            0x19

/** Hardware register field used to specify the audio clip interrupt
    status field of speaker 1. */
#define AFE_CRC_CLIP_INT_STATUS_REG                                    0x1A

/** More meaningful macro for AFE_CRC_SPKR_CLIP_INT_STATUS_REG.
    This macro helps distinguish between two speakers that are generating
    clip interrupts. */
#define AFE_CRC_SPKR_CLIP_INT_STATUS_REG                            AFE_CRC_CLIP_INT_STATUS_REG

/** Hardware register field used to specify the VBAT attack interrupt
    status field. */
#define AFE_CRC_VBAT_INT_STATUS_REG                                    0x1B

/** More meaningful macro for AFE_CRC_VBAT_INT_STATUS_REG.
    This macro helps distinguish between ATTACK and RELEASE interrupts. */
#define AFE_CRC_VBAT_ATTACK_INT_STATUS_REG                            AFE_CRC_VBAT_INT_STATUS_REG

/** Hardware register field used to specify the MAD audio interrupt clear
    field. */
#define AFE_CRC_MAD_AUDIO_INT_CLEAR_REG                                0x1C

/** Hardware register field used to specify the MAD ultrasound interrupt clear
    field. */
#define AFE_CRC_MAD_ULT_INT_CLEAR_REG                                0x1D

/** Hardware register field used to specify the MAD beacon interrupt clear
    field. */
#define AFE_CRC_MAD_BEACON_INT_CLEAR_REG                            0x1E

/** Hardware register field used to specify the audio clip interrupt
    clear field of speaker 1. */
#define AFE_CRC_CLIP_INT_CLEAR_REG                                    0x1F

/** More meaningful macro for AFE_CRC_CLIP_INT_CLEAR_REG. This macro helps
    distinguish between two speakers that are generating clip interrupts. */
#define AFE_CRC_SPKR_CLIP_INT_CLEAR_REG                                AFE_CRC_CLIP_INT_CLEAR_REG

/** Hardware register field used to specify the VBAT attack interrupt clear
    field. */
#define AFE_CRC_VBAT_INT_CLEAR_REG                                    0x20

/** More meaningful macro for AFE_CRC_VBAT_INT_CLEAR_REG.
    This macro helps distinguish between ATTACK and RELEASE interrupts. */
#define AFE_CRC_VBAT_ATTACK_INT_CLEAR_REG                            AFE_CRC_VBAT_INT_CLEAR_REG

/** Hardware register field used to specify the SLIMbus slave port (Tx)
    watermark configuration field. */
#define AFE_CRC_SB_PGD_PORT_TX_WATERMARK_n                            0x21

/** Hardware register field used to specify the SLIMbus slave port (Tx)
    enable/disable configuration field. */
#define AFE_CRC_SB_PGD_PORT_TX_ENABLE_n                                0x22

/** Hardware register field used to specify the SLIMbus slave port (Rx)
    watermark configuration field. */
#define AFE_CRC_SB_PGD_PORT_RX_WATERMARK_n                            0x23

/** Hardware register field used to specify the SLIMbus slave port (Rx)
    enable/disable configuration field. */
#define AFE_CRC_SB_PGD_PORT_RX_ENABLE_n                                0x24

/** Hardware register field used to enable SLIMbus multichannel 0 (Tx) for
    the given slave port. */
#define AFE_CRC_SB_PGD_TX_PORTn_MULTI_CHNL_0 0x25

/** Hardware register field used to enable SLIMbus multichannel 1 (Tx) for
    the given slave port. */
#define AFE_CRC_SB_PGD_TX_PORTn_MULTI_CHNL_1 0x26

/** Hardware register field used to enable SLIMbus multichannel 0 (Rx) for
    the given slave port. */
#define AFE_CRC_SB_PGD_RX_PORTn_MULTI_CHNL_0 0x27

/** Hardware register field used to enable SLIMbus multichannel 1 (Rx) for
    the given slave port. */
#define AFE_CRC_SB_PGD_RX_PORTn_MULTI_CHNL_1 0x28

/** Hardware register field used to enable the double banking, FFGAIN_ADAPTIVE
    bit (CDC_ANCn_IIR_B1_CTL). */
#define AFE_CRC_AANC_FF_GAIN_ADAPTIVE          0x29

/** Hardware register field used to copy AANC gain from the foreground to the
    background register (CDC_ANCn_IIR_B1_CTL). */
#define AFE_CRC_AANC_FFGAIN_ADAPTIVE_EN  0x2A

/** Hardware register field used to update AANC gain (CDC_ANCn_GAIN_CTL). */
#define AFE_CRC_AANC_GAIN_CONTROL            0x2B

/** Hardware register field used to update the clip PCM-level bank
    selection of speaker 1 (CDC_SPKR_CLIPDET_B1_CTL). */
#define AFE_CRC_CLIP_PIPE_BANK_SEL                0x2C

/** More meaningful macro for AFE_CRC_CLIP_PIPE_BANK_SEL.
    This macro helps distinguish between two speakers that are generating clip
    interrupts. */
#define AFE_CRC_SPKR_CLIP_PIPE_BANK_SEL            AFE_CRC_CLIP_PIPE_BANK_SEL

/** Hardware register field used to update clip PCM-level
    register 0 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL0            0x2D

/** Hardware register field used to update clip PCM-level
    register 1 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL1            0x2E

/** Hardware register field used to update clip PCM-level
    register 2 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL2            0x2F

/** Hardware register field used to update clip PCM-level
    register 3 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL3            0x30

/** Hardware register field used to update clip PCM-level
    register 4 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL4            0x31

/** Hardware register field used to update clip PCM-level
    register 5 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL5            0x32

/** Hardware register field used to update clip PCM-level
    register 6 of speaker 1.*/
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL6            0x33

/** Hardware register field used to update clip PCM-level
    register 7 of speaker 1. */
#define AFE_CRC_CDC_SPKR_CLIPDET_VAL7            0x34

/** Hardware register field used to route the VBAT release interrupt. */
#define AFE_CRC_VBAT_RELEASE_INT_DEST_SELECT_REG                            0x35

/** Hardware register field used to specify the VBAT release interrupt
    mask field. */
#define AFE_CRC_VBAT_RELEASE_INT_MASK_REG                                   0x36

/** Hardware register field used to specify the VBAT release interrupt
    status field. */
#define AFE_CRC_VBAT_RELEASE_INT_STATUS_REG                                 0x37

/** Hardware register field used to specify the VBAT release interrupt clear
    field. */
#define AFE_CRC_VBAT_RELEASE_INT_CLEAR_REG                                  0x38

/** Hardware register field used to route the audio clip
    interrupt of speaker 2. */
#define AFE_CRC_SPKR2_CLIP_INT_DEST_SELECT_REG                              0x39

/** Hardware register field used to specify the audio clip
    interrupt mask field of speaker 2. */
#define AFE_CRC_SPKR2_CLIP_INT_MASK_REG                                     0x3A

/** Hardware register field used to specify the audio clip
    interrupt status field of speaker 2. */
#define AFE_CRC_SPKR2_CLIP_INT_STATUS_REG                                   0x3B

/** Hardware register field used to specify the audio clip
    interrupt clear field of speaker 2. */
#define AFE_CRC_SPKR2_CLIP_INT_CLEAR_REG                                    0x3C

/** Hardware register field used to update the clip PCM-level bank
    selection of speaker 2 (CDC_SPKR_CLIPDET_B1_CTL). */
#define AFE_CRC_SPKR2_CLIP_PIPE_BANK_SEL                                    0x3D

/** Hardware register field used to update clip PCM-level
    register 0 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL0                                      0x3E

/** Hardware register field used to update clip PCM-level
    register 1 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL1                                      0x3F

/** Hardware register field used to update clip PCM-level
    register 2 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL2                                      0x40

/** Hardware register field used to update clip PCM-level
    register 3 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL3                                      0x41

/** Hardware register field used to update clip PCM-level
    register 4 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL4                                      0x42

/** Hardware register field used to update clip PCM-level
    register 5 of speaker 2. */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL5                                      0x43

/** Hardware register field used to update clip PCM-level
    register 6 of speaker 2.*/
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL6                                      0x44

/** @xreflabel{Last}
    Hardware register field used to update clip PCM-level
    register 7 of speaker 2. @newpage */
#define AFE_CRC_CDC_SPKR2_CLIPDET_VAL7                                      0x45

/** @} */ /* end_addtogroup afe_module_cdc_device */

typedef struct afe_cdc_reg_cfg_param_v1_t afe_cdc_reg_cfg_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cdc_reg_cfg_param_v1_t
@{ */
/* Hardware codec register configuration structure used by the
    AFE_PARAM_ID_CDC_REG_CFG parameter (version 1).
 */
struct afe_cdc_reg_cfg_param_v1_t
{
    uint32_t cdc_reg_cfg_minor_version;
    /**< Minor version used to track codec register configuration.

        @values #AFE_API_VERSION_CDC_REG_CFG */

    uint32_t reg_logical_addr;
    /**< Logical address of the value element mapped to the SLIMbus codec
         register to which read/write access is required.

        @values 32-bit logical address of the register to be accessed */

    uint32_t reg_field_type;
    /**< Enumeration for the register field to be updated.

         If more than one field in the register is to be updated, the same
         command must be sent for each field.

        @values
         - 0 is reserved
         - See Sections @xref{First} through @xref{Last} @tablebulletend */

   uint32_t reg_field_bit_mask;
   /**< Register bitmask to which the ANC algorithm writes.

        @values Valid register bitmask */

   uint16_t reg_bit_width;
   /**< Bit width of the register.

        @values Valid register bit width */

   uint16_t reg_offset_scale;
   /**< Offset scale factor for codec registers.
        For example, 0x400+1*n, where 1 is reg_offset_scale.

        @values Valid register offset scale, if any (Default = 0) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cdc_reg_cfg_param_v1_t */

/** @addtogroup afe_module_cdc_device
@{ */
/** ID of the parameter used by #AFE_MODULE_CDC_DEV_CFG to configure codec AANC.
    Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    @apr_msgpayload{afe_cdc_aanc_version_param_v1_t}
    @table{weak__afe__cdc__aanc__version__param__v1__t}
 */
#define AFE_PARAM_ID_CDC_AANC_VERSION                        0x0001023A

/** Version information used to handle future additions to
    AFE_PARAM_ID_CDC_AANC_VERSION processing (for backward compatibility).
 */
#define AFE_API_VERSION_CDC_AANC_VERSION                            0x1

/** AANC hardware block version 1.

    This version must be selected by applications when the
    #AFE_CRC_AANC_LPF_FF_FB, #AFE_CRC_AANC_LPF_COEFF_MSB, and
    #AFE_CRC_AANC_LPF_COEFF_LSB registers are used for gain updates.
    For example, for the Tabla codec.
 */
#define AFE_AANC_HW_BLOCK_VERSION_1                                 0x1

/** AANC hardware block version 2.

    This version must be selected by applications when the
    #AFE_CRC_AANC_FF_GAIN_ADAPTIVE, #AFE_CRC_AANC_FFGAIN_ADAPTIVE_EN,
    and #AFE_CRC_AANC_GAIN_CONTROL registers are used for gain updates.
    For example, for the Taiko codec. @newpage
 */
#define AFE_AANC_HW_BLOCK_VERSION_2                                 0x2

/** @} */ /* end_addtogroup afe_module_cdc_device */

typedef struct afe_cdc_aanc_version_param_v1_t afe_cdc_aanc_version_param_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cdc_aanc_version_param_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_CDC_AANC_VERSION parameter
  (version 1).
 */
struct afe_cdc_aanc_version_param_v1_t
{
    uint32_t cdc_aanc_minor_version;
    /**< Minor version used to track codec AANC configuration.

         @values #AFE_API_VERSION_CDC_AANC_VERSION */

    uint32_t aanc_hw_version;
    /**< Type of AANC hardware version present in the codec.

         @values
         - #AFE_AANC_HW_BLOCK_VERSION_1
         - #AFE_AANC_HW_BLOCK_VERSION_2 @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cdc_aanc_version_param_v1_t */

/** @addtogroup afe_module_cdc_device
@{ */
/** ID of the parameter used by #AFE_MODULE_CDC_DEV_CFG to configure
    clip bank select. Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    @apr_msgpayload{afe_clip_bank_sel_cfg_v1_t}
    @table{weak__afe__clip__bank__sel__cfg__v1__t}
 */
#define AFE_PARAM_ID_CLIP_BANK_SEL_CFG                        0x00010242

/** Version information used to handle future additions to
    AFE_PARAM_ID_CLIP_BANK_SEL_CFG processing (for backward compatibility).
 */
#define AFE_API_VERSION_CLIP_BANK_SEL_CFG                            0x1

/** Maximum number of banks allowed for reading the PCM levels in the event of
    a clip interrupt.
 */
#define AFE_CLIP_MAX_BANKS                                             0x4

/** @} */ /* end_addtogroup afe_module_cdc_device */

typedef struct afe_clip_bank_sel_cfg_v1_t afe_clip_bank_sel_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_clip_bank_sel_cfg_v1_t
@{ */
/* Configuration structure for the
  AFE_PARAM_ID_CLIP_BANK_SEL_CFG parameter (version 1).
 */
struct afe_clip_bank_sel_cfg_v1_t
{
    uint32_t clip_bank_sel_cfg_minor_version;
    /**< Minor version used to track clip bank selection configuration.

      @values #AFE_API_VERSION_CLIP_BANK_SEL_CFG */

    uint32_t num_banks;
    /**< Number of banks to be read.

         @values 2 or 4 */

    uint32_t bank_map[AFE_CLIP_MAX_BANKS];
    /**< Bank number to be read.

         If the number of banks is 2, the bank map must be
         [1, 3, DC, DC] or [0, 2, DC, DC], where DC means ``do not care.''

         @values 0 to 3 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_clip_bank_sel_cfg_v1_t */

/** @ingroup afe_module_cdc_device
    ID of the parameter used by #AFE_MODULE_CDC_DEV_CFG to initialize codec
    device configuration.

    This parameter must be sent to the aDSP after sending all device
    configuration parameters so that initialization takes affect in all
    configurations. Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    This parameter does not contain an explict payload and must be sent with
    the AFE_MODULE_CDC_DEV_CFG module.
 */
#define AFE_PARAM_ID_CDC_REG_CFG_INIT                            0x00010237

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    a Low Power Audio Interface (LPAIF) clock (I2S/PCM bit clock and OSR).
    - An LPAIF clock must be enabled before #AFE_PORT_CMD_DEVICE_START
      is issued.
    - An LPAIF clock must be disabled after #AFE_PORT_CMD_DEVICE_STOP
      is issued.

    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.
    @apr_msgpayload{afe_param_id_lpaif_clk_cfg_t}
    The payload for this parameter must be sent with
    #AFE_MODULE_AUDIO_DEV_INTERFACE.
    @tablens{weak__afe__param__id__lpaif__clk__cfg__t}
 */
#define AFE_PARAM_ID_LPAIF_CLK_CONFIG                0x00010238

/** Version information used to handle future additions to
    AFE_PARAM_ID_LPAIF_CLK_CONFIG processing (for backward compatibility).
 */
#define AFE_API_VERSION_LPAIF_CLK_CONFIG               0x1

/* Enumeration for setting LPAIF clock source clk_src. */

/** LPAIF clock source is external. */
#define AFE_PORT_LPACLK_CLK_SRC_EXTERNAL                                     0x0

/** LPAIF clock source is internal. */
#define AFE_PORT_LPACLK_CLK_SRC_INTERNAL                                     0x1

/* Enumeration for setting LPAIF clock root clk_root. */

/** LPAIF clock is sourced from the audio PLL. */
#define AFE_PORT_LPACLK_CLK_ROOT_DEFAULT                                     0x0

/** LPAIF clock is sourced from the PXO. */
#define AFE_PORT_LPACLK_CLK_ROOT_PXO                                         0x1

/** LPAIF clock is sourced from the CXO. */
#define AFE_PORT_LPACLK_CLK_ROOT_CXO                                         0x2

/** LPAIF clock is sourced from the LPA PLL. */
#define AFE_PORT_LPACLK_CLK_ROOT_LPAPLL                                      0x3

/** LPAIF clock is sourced from the second PLL. */
#define AFE_PORT_LPACLK_CLK_ROOT_SECPLL                                      0x4

/** LPAIF clock is sourced from the LPA QDSP6 PLL. */
#define AFE_PORT_LPACLK_CLK_ROOT_LPAQ6PLL                                    0x5

/** LPAIF clock is sourced from pullable PLL 1. */
#define AFE_PORT_LPACLK_CLK_ROOT_PULLABLEPLL1                                0x6

/** LPAIF clock is sourced from pullable PLL 2. */
#define AFE_PORT_LPACLK_CLK_ROOT_PULLABLEPLL2                                0x7

/* Enumeration for specifying value1 and value2 valid setting via clk_set_mode.*/

/** Both clk_value1 and clk_value2 in afe_param_id_lpaif_clk_cfg_t are invalid. */
#define AFE_PORT_LPACLK_CLK_VALUE_INVALID                                    0x0

/** Only clk_value1 in afe_param_id_lpaif_clk_cfg_t is valid. */
#define AFE_PORT_LPACLK_CLK_VALUE1_VALID_ONLY                                0x1

/** Only clk_value2 in afe_param_id_lpaif_clk_cfg_t is valid. */
#define AFE_PORT_LPACLK_CLK_VALUE2_VALID_ONLY                                0x2

/** Both clk_value1 and clk_value2 in afe_param_id_lpaif_clk_cfg_t are valid. @newpage */
#define AFE_PORT_LPACLK_CLK_VALUE1_VALUE2_BOTH_VALID                         0x3

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_lpaif_clk_cfg_t afe_param_id_lpaif_clk_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_lpaif_clk_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_LPAIF_CLK_CONFIG parameter.
*/
struct afe_param_id_lpaif_clk_cfg_t
{
    uint32_t                  lpaif_cfg_minor_version;
    /**< Minor version used to track LPAIF clock configuration.

         @values #AFE_API_VERSION_LPAIF_CLK_CONFIG */

    uint32_t                 clk_value1;
    /**< Clock frequency value 1 (in Hertz) to be set.

         @values
         - I2S bit clock for an MI2S port, or PCM bit clock for a PCM port
         - 0 to disable the clock @tablebulletend */

    uint32_t                 clk_value2;
    /**< Clock frequency value 2 (in Hertz) to be set.

         @values
         - I2S OSR for an MI2S port
         - 0 to disable the clock @tablebulletend */

    uint16_t                 clk_src;
    /**< Specifies I2S WS or PCM SYNC as the clock source.

         @values
         - #AFE_PORT_LPACLK_CLK_SRC_EXTERNAL
         - #AFE_PORT_LPACLK_CLK_SRC_INTERNAL @tablebulletend */

    uint16_t                 clk_root;
    /**< Specifies I2S or PCM as the root clock source.
         Currently, only AFE_PORT_LPACLK_CLK_ROOT_DEFAULT is valid.

         @values
         - #AFE_PORT_LPACLK_CLK_ROOT_DEFAULT
         - #AFE_PORT_LPACLK_CLK_ROOT_PXO
         - #AFE_PORT_LPACLK_CLK_ROOT_CXO
         - #AFE_PORT_LPACLK_CLK_ROOT_LPAPLL
         - #AFE_PORT_LPACLK_CLK_ROOT_SECPLL
         - #AFE_PORT_LPACLK_CLK_ROOT_LPAQ6PLL
         - #AFE_PORT_LPACLK_CLK_ROOT_PULLABLEPLL1
         - #AFE_PORT_LPACLK_CLK_ROOT_PULLABLEPLL2 @tablebulletend */

    uint16_t                 clk_set_mode;
      /**< Valid setting for clk_value1 and clk_value2 fields.

           @values
           - #AFE_PORT_LPACLK_CLK_VALUE_INVALID
           - #AFE_PORT_LPACLK_CLK_VALUE1_VALID_ONLY
           - #AFE_PORT_LPACLK_CLK_VALUE2_VALID_ONLY
           - #AFE_PORT_LPACLK_CLK_VALUE1_VALUE2_BOTH_VALID @vertspace{-28} */

    uint16_t                 reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_lpaif_clk_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    an SPDIF clock.
    - An SPDIF clock must be enabled before #AFE_PORT_CMD_DEVICE_START
      is issued.
    - An SPDIF clock must be disabled after #AFE_PORT_CMD_DEVICE_STOP
      is issued.

    @apr_msgpayload{afe_param_id_spdif_clk_cfg_t}
    The payload for this parameter must be sent with
    #AFE_MODULE_AUDIO_DEV_INTERFACE.
    @tablens{weak__afe__param__id__spdif__clk__cfg__t}
 */
#define AFE_PARAM_ID_SPDIF_CLK_CONFIG                0x00010246

/** Version information used to handle future additions to
    AFE_PARAM_ID_SPDIF_CLK_CONFIG processing (for backward compatibility).
 */
#define AFE_API_VERSION_SPDIF_CLK_CONFIG               0x1

/* Enumeration for setting clock root clk_root. */

/** Clock is sourced from the PXO. */
#define AFE_PORT_CLK_ROOT_PXO                                         0x1

/** Clock is sourced from the CXO. */
#define AFE_PORT_CLK_ROOT_CXO                                         0x2

/** Clock is sourced from the LPA PLL. */
#define AFE_PORT_CLK_ROOT_LPAPLL                                      0x3

/** Clock is sourced from the LPA QDSP6 PLL. */
#define AFE_PORT_CLK_ROOT_LPAQ6PLL                                    0x4

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_spdif_clk_cfg_t afe_param_id_spdif_clk_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_spdif_clk_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_SPDIF_CLK_CONFIG parameter.
*/
struct afe_param_id_spdif_clk_cfg_t
{
    uint32_t                  spdif_clk_cfg_minor_version;
    /**< Minor version used to track SPDIF clock configuration.

         @values #AFE_API_VERSION_SPDIF_CLK_CONFIG */

    uint32_t                 clk_value;
    /**< Clock frequency value 1 (in Hertz) to be set as twice the bitrate.

         - 2 (biphase) * 32 (60958 subframe size) * sampling rate * 2 
            (channels A and B)
         - 0 to disable the clock @tablebulletend */

    uint32_t                 clk_root;
    /**< Specifies I2S or PCM as the root clock source.

         @values
         - #AFE_PORT_CLK_ROOT_LPAPLL
         - #AFE_PORT_CLK_ROOT_LPAQ6PLL  @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_spdif_clk_cfg_t */

/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the internal digital codec core clock.

    The call sequence for this clock is:
    -# Enable the MI2S OSR clock if the client selects MI2S OSR as the
       internal digital core clock source.
    -# Enable the internal digital core clock.
    -# The clock is running.
    -# Disable the internal digital core clock.
    -# Disable the MI2S OSR clock if the client selects MI2S OSR as the
       internal digital core clock source.

    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_param_id_internal_digital_cdc_clk_cfg_t}
    The payload must be sent with #AFE_MODULE_AUDIO_DEV_INTERFACE.
    @tablens{weak__afe__param__id__internal__digital__cdc__clk__cfg__t}
 */
#define AFE_PARAM_ID_INTERNAL_DIGIATL_CDC_CLK_CONFIG                0x00010239

/** Version information used to handle future additions to
    AFE_PARAM_ID_INTERNAL_DIGIATL_CDC_CLK_CONFIG processing (for backward
    compatibility).
 */
#define AFE_API_VERSION_INTERNAL_DIGIATL_CDC_CLK_CONFIG               0x1

/* Enumerations for setting digital codec core clock root. */

/** Digital codec core clock root is invalid. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_INVALID                  0x0

/** Digital codec core clock root is Primary I2S OSR. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_PRII2SOSR                0x1

/** Digital codec core clock root is Secondary I2S OSR. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_SECI2SOSR                0x2

/** Digital codec core clock root is Tertiary I2S OSR. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_TERI2SOSR                0x3

/** Digital codec core clock root is Quaternary I2S OSR. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_QUAI2SOSR                0x4

/** Digital codec core clock root is Codec. */
#define AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_CODEC                    0x5

/** @} */ /* end_addtogroup afe_module_audio_device */

typedef struct afe_param_id_internal_digital_cdc_clk_cfg_t afe_param_id_internal_digital_cdc_clk_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_internal_digital_cdc_clk_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_INTERNAL_DIGIATL_CDC_CLK_CONFIG command's
    internal digital codec core clock configuration parameter.
*/
struct afe_param_id_internal_digital_cdc_clk_cfg_t
{
    uint32_t                  cdc_clk_cfg_minor_version;
    /**< Minor version used to track the internal digital
         codec core clock configuration.

         @values #AFE_API_VERSION_INTERNAL_DIGIATL_CDC_CLK_CONFIG */

    uint32_t                 clk_value;
    /**< Digital codec core clock frequency in Hertz. */

    uint16_t                 clk_root;
    /**< Source of the digital codec core clock.

         @values
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_INVALID
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_PRII2SOSR
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_SECI2SOSR
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_TERI2SOSR
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_QUAI2SOSR
         - #AFE_PORT_INTERNAL_DIGIATL_CDC_CLK_ROOT_CODEC @vertspace{-28} */

    uint16_t                 reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_internal_digital_cdc_clk_cfg_t */


/** @ingroup afe_module_custom_evts
    ID of the Custom Events module, which registers or deregisters an
    event on a specified port or service.
    @if OEM_only This module ID supports the following parameter IDs:
    - #AFE_PARAM_ID_SIF_CLIP_DETECTION_CONFIG
    - #AFE_PARAM_ID_SIF_CARRIER_LOST_DETECTION_CONFIG
    @endif

    @apr_hdr_fields
    Opcode -- AFE_MODULE_CUSTOM_EVENTS

    @detdesc
    #AFE_PORT_CMD_SET_PARAM_V2 uses this module ID for destination ports, and
    #AFE_SVC_CMD_SET_PARAM uses this module ID for destination sevices.
    @par
    The APR destination address and port number are obtained from the header of
    this packet and are used for sending different events.
    @par
    By registering, the customer applications will receive
    #AFE_PORT_CUSTOM_EVENT events, depending on the destination.
*/
#define AFE_MODULE_CUSTOM_EVENTS                                    0x00010251

/** @weakgroup weakb_afe_param_id_sif_events_cfg_input
@{ */
/** Enumeration used to unregister an event. */
#define AFE_CUSTOM_EVENT_UNREGISTER                                 0x0

/** Enumeration used to register an event. */
#define AFE_CUSTOM_EVENT_REGISTER                                   0x1

/** @} */ /* end_weakgroup weakb_afe_param_id_sif_events_cfg_input */

/** @addtogroup afe_module_custom_evts
@{ */
/** ID of the parameter used by #AFE_MODULE_CUSTOM_EVENTS to register/unregister
    a carrier lost detection event.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SIF_EVENTS_CFG

    @apr_msgpayload{afe_param_id_sif_events_cfg_t}
    @table{weak__afe__param__id__sif__events__cfg__t}

    @inputfile{group__weakb__afe__param__id__sif__events__cfg__input.tex}
*/
#define AFE_PARAM_ID_SIF_EVENTS_CFG                                   0x00010252

/** Version information used to handle future additions to carrier lost
    detection event registration (for backward compatibility). */
#define AFE_EVENT_VERSION_SIF_EVENTS_CFG                                 0x1

/** SIF carrier lost detection event for channel A. */
#define AFE_SIF_EVENT_TYPE_CARRIER_LOST_CHA_DETECTION                    0x1

/** SIF carrier lost detection event for channel B. */
#define AFE_SIF_EVENT_TYPE_CARRIER_LOST_CHB_DETECTION                    0x2

/** SIF clip detection event. */
#define AFE_SIF_EVENT_TYPE_CLIP_DETECTION                                0x3

/** @} */ /* end_addtogroup afe_module_custom_evts */

typedef struct afe_param_id_sif_events_cfg_t afe_param_id_sif_events_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_sif_events_cfg_t
@{ */
/* Payload of the AFE_PARAM_IDCARRIER_LOST_DETECTION_CFG  parameter used by
    AFE_MODULE_CUSTOM_EVENTS.
*/
struct afe_param_id_sif_events_cfg_t
{
   uint32_t                  sif_events_cfg_minor_version;
   /**< Minor version used to track carrier lost detection configuration.

        @values #AFE_EVENT_VERSION_SIF_EVENTS_CFG */

   uint16_t                  register_flag;
   /**< Specifies whether events are to be registered for carrier lost
        detection.

        @values
         - #AFE_CUSTOM_EVENT_UNREGISTER 
         - #AFE_CUSTOM_EVENT_REGISTER @tablebulletend */

   uint16_t                  event_type;
   /**< Supported event type.

        @values
         - #AFE_SIF_EVENT_TYPE_CARRIER_LOST_CHA_DETECTION
         - #AFE_SIF_EVENT_TYPE_CARRIER_LOST_CHB_DETECTION
         - #AFE_SIF_EVENT_TYPE_CLIP_DETECTION @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sif_events_cfg_t */


/** @ingroup afe_evt_port_custom_event
    Sent when the AFE port reports an event to a client.

  @apr_hdr_fields
    Opcode -- AFE_PORT_CUSTOM_EVENT

  @apr_msgpayload{afe_port_custom_event_t}
    @table{weak__afe__port__custom__event__t}

  @detdesc
    This event communicates information about the AFE port event for which the 
    client registered.
    @par
    For a client to receive this notification, it must register using
    #AFE_PORT_CMD_SET_PARAM_V2, #AFE_MODULE_CUSTOM_EVENTS, and a
    corresponding parameter ID.

  @return
    None.

  @dependencies
    #AFE_PORT_CMD_SET_PARAM_V2
*/
#define AFE_PORT_CUSTOM_EVENT                                         0x00010107

/* Structure for the AFE_PORT_CUSTOM_EVENT event. */
typedef struct afe_port_custom_event_t  afe_port_custom_event_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_port_custom_event_t
@{ */
/* Payload of the AFE_PORT_CUSTOM_EVENT message, which sends
    an event from the AFE port to a registered client.
*/
struct afe_port_custom_event_t
{
   uint32_t                  port_id;
   /**< ID of the AFE port from which the event is generated.

        @values Valid AFE port ID */

   uint32_t                  module_id;
   /**< Module ID of the event being notified.

        @values #AFE_MODULE_CUSTOM_EVENTS */

   uint32_t                  param_id;
   /**< Parameter ID of the event being notfied. */

   uint16_t event_type;
   /**< Valid event type corresponding to the param_id value. */

   uint16_t payload_size;
   /**< Size of the event payload.

        @values
        - Any valid payload size
        - 0 -- There is no payload @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_port_event_t */


/** @ingroup afe_module_feedback
    ID of the Feedback module, which is used to set up the feedback path
    between modules on different AFE ports for communicating custom data.
    To use this framework, these modules must support custom data
    communication. 

    This module supports the following parameter ID:
    - #AFE_PARAM_ID_FEEDBACK_PATH_CFG
 
    @apr_hdr_fields
    Opcode -- AFE_MODULE_FEEDBACK
*/
#define AFE_MODULE_FEEDBACK                                     0x00010257


/** @addtogroup afe_module_device_group
@{ */
/** ID of the Group Device module, which groups AFE ports that are in the
    same physical device interface (for example, Secondary MI2S Rx).
 
    This module supports following parameter IDs:
     - #AFE_PARAM_ID_GROUP_DEVICE_CONFIG
     - #AFE_PARAM_ID_GROUP_DEVICE_ENABLE

    To configure the group device (a single device that operates like multiple
    devices), use the #AFE_SVC_CMD_SET_PARAM command and fill the module ID
    with the respective parameter ID.

    @apr_hdr_fields
    Opcode -- AFE_MODULE_GROUP_DEVICE
*/
#define AFE_MODULE_GROUP_DEVICE                                      0x00010254

/** ID of the parameter used by #AFE_MODULE_GROUP_DEVICE to configure the
    group device. #AFE_SVC_CMD_SET_PARAM can use this parameter ID.

    Requirements:
    - Configure the group before the member ports in the group are configured
      and started.
    - Enable the group only after it is configured.
    - Stop all member ports in the group before disabling the group.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_GROUP_DEVICE_CONFIG

    @apr_msgpayload{afe_param_id_group_device_cfg_t}
    @table{weak__afe__param__id__group__device__cfg__t}
*/
#define AFE_PARAM_ID_GROUP_DEVICE_CONFIG                              0x00010255

/** Version information used to handle future additions to
    AFE_PARAM_ID_GROUP_DEVICE_CONFIG processing (for backward compatibility).
 */
#define AFE_API_VERSION_GROUP_DEVICE_CONFIG                           0x1

/** Number of AFE ports in the group device. */
#define AFE_GROUP_DEVICE_NUM_PORTS                                    8

typedef struct afe_param_id_group_device_cfg_t afe_param_id_group_device_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_group_device_cfg_t
@{ */
/* Payload of the AFE_PARAM_ID_GROUP_DEVICE_CONFIG parameter ID
    used by AFE_MODULE_GROUP_DEVICE.
*/
struct afe_param_id_group_device_cfg_t
{
    uint32_t                  group_device_cfg_minor_version;
   /**< Minor version used to track group device configuration.

        @values #AFE_API_VERSION_GROUP_DEVICE_CONFIG */

    uint16_t                  group_id;
   /**< ID for the group device.

        @values #AFE_GROUP_DEVICE_ID_SECONDARY_MI2S_RX */

    uint16_t                  num_channel;
   /**< Number of channels for the group device.

        @values 1 to 32 */

    uint16_t                  port_id[AFE_GROUP_DEVICE_NUM_PORTS];
    /**< Array of member port IDs of this group.

         @values
         - #AFE_PORT_ID_SECONDARY_MI2S_RX
         - #AFE_PORT_ID_SECONDARY_MI2S_RX_2 @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_group_device_cfg_t */

/** ID of the parameter used by #AFE_MODULE_GROUP_DEVICE to enable and disable
    the group device. Only #AFE_SVC_CMD_SET_PARAM can use this parameter ID.
 
    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_GROUP_DEVICE_ENABLE

    @apr_msgpayload{afe_param_id_group_device_enable_t}
    @table{weak__afe__param__id__group__device__enable__t}
*/
#define AFE_PARAM_ID_GROUP_DEVICE_ENABLE                           0x00010256

typedef struct afe_param_id_group_device_enable_t afe_param_id_group_device_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_param_id_group_device_enable_t
@{ */
/* Payload of the AFE_PARAM_ID_GROUP_DEVICE_ENABLE parameter ID used by
    AFE_MODULE_GROUP_DEVICE.
*/
struct afe_param_id_group_device_enable_t
{
    uint16_t                  group_id;
   /**< ID of the group device.

        @values #AFE_GROUP_DEVICE_ID_SECONDARY_MI2S_RX */

    uint16_t                  enable;
   /**< Specifies whether the group device is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_afe_param_id_group_device_enable_t */
/** @} */ /* end_addtogroup afe_module_device_group */


/** @ingroup afe_cmd_add_topos 
    Defines custom topologies in the aDSP for use in an AFE session.
    These topologies are created by specifying the topology IDs in the
    #AFE_PARAM_ID_TOPO_ID parameter.

  @apr_hdr_fields
    Opcode -- AFE_CMD_ADD_TOPOLOGIES 

  @apr_msgpayload{afe_cmd_add_topologies_t}
    @table{weak__afe__cmd__add__topologies__t}

  @par Buffer format (afe_custom_topologies_t)
    Immediately following this structure are num_topologies of the
    definitions to be added to the aDSP (see
    @xhyperref{hdr:AfeTopoDefinition,Topology definition}).
    @tablens{weak__afe__custom__topologies__t}
    @par
    Calculation of the buffer size:
    - Size of the module information structure = 4 + 4 + 16 = 24 bytes
    - Size of the topology definition structure = 4 + 4 + 16 * (size of the
      module information structure) = 392 bytes
    - Size of the buffer = 4 + num_topologies * 392 @newpage

  @par Topology definition (afe_topology_definition_t)
    @xreflabel{hdr:AfeTopoDefinition}
    Immediately following this structure are num_modules of
    @xhyperref{hdr:AfeModuleInfo,Module information}.
    @tablens{weak__afe__topology__definition__t}

  @par Module information (afe_module_info_t)
    @xreflabel{hdr:AfeModuleInfo}
    @table{weak__afe__module__info__t}

  @detdesc 
    Custom topology definitions are stored internally by the aDSP. Only the
    definitions sent to the AFE are available for AFE sessions.
    @par
    This command must be sent before opening an AFE session with the custom
    topologies. It can be sent multiple times to add new topologies.
    If a subsequent command redefines a previously defined topology ID,
    the previous topology definition is replaced with the new definition.
    However, the changes take effect only when the next AFE session is created.

  @return
    APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q3,[Q3]}).
    The handle is defined by the client as input.

  @dependencies
    None.
*/
#define AFE_CMD_ADD_TOPOLOGIES                                0x000100f8

/* The payload for the AFE_CMD_ADD_TOPOLOGIES command */
typedef struct afe_cmd_add_topologies_t afe_cmd_add_topologies_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_cmd_add_topologies_t
@{ */
/* Payload of the AFE_CMD_ADD_TOPOLOGIES command.
*/
struct afe_cmd_add_topologies_t
{
    uint32_t                  data_payload_addr_lsw;
    /**< Lower 32 bits of the 64-bit topology buffer address. */

    uint32_t                  data_payload_addr_msw;
    /**< Upper 32 bits of the 64-bit topology buffer address. */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for an address.

         This memory map handle is returned by the aDSP through the
         #AFE_SERVICE_CMD_SHARED_MEM_MAP_REGIONS command. */

    uint32_t                  buffer_size;
    /**< Size in bytes of the valid data in the topology buffer. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_cmd_add_topologies_t */

typedef struct afe_module_info_t afe_module_info_t;

#include "adsp_begin_pack.h"

#define AFE_TOPO_MODULE_MAX_INIT_PARAMS  16

/** @weakgroup weak_afe_module_info_t
@{ */
/* Defines the modules used by the AFE_CMD_ADD_TOPOLOGIES command.
*/
struct afe_module_info_t
{
   uint32_t module_id;
   /**< ID of the module to be created.

        @values Any valid module ID (see Chapter @xref{hdr:CalibrationIDs}) */

   uint32_t use_lpm;
   /**< Specifies whether to put this module in low power memory.

        @values
        - 0 -- Do not put this module in low power memory
        - 1 -- Put this module in low power memory

        If there is insufficient low power memory, this module is placed in
        the default memory pool. */

   uint8_t  init_params[AFE_TOPO_MODULE_MAX_INIT_PARAMS];
   /**< Array of initialization parameters passed to the module when it is
        created.

        This array of 16 bytes is sent to the getsize() and init() methods of
        the module. The interpretation of this information is module
        specific. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_module_info_t */

typedef struct afe_topology_definition_t afe_topology_definition_t;

#include "adsp_begin_pack.h"

/** @ingroup afe_cmd_add_topos
    Maximum number of modules supported in an AFE custom topology. */
#define AFE_MAX_MODULES_PER_TOPOLOGY 16

/** @weakgroup weak_afe_topology_definition_t
@{ */
/* Defines a custom topology that is to be added to the aDSP. This structure
    is followed by num_modules of afe_module_info_t.
*/
struct afe_topology_definition_t
{
   uint32_t topology_id;
   /**< ID of this custom topology.

        @values 0x10000000 to 0x1FFFFFFF */

   uint32_t num_modules;
   /**< Number of modules in this topology.

        @values 0 to #AFE_MAX_MODULES_PER_TOPOLOGY */

   afe_module_info_t module_info[AFE_MAX_MODULES_PER_TOPOLOGY];
   /**< Array of module information structures with 16 elements.

        The order of the elements in this array specifies the order in which
        the modules are connected in the topology, from source to sink. Only
        the first num_modules elements of this array are required. The rest of
        the elements are ignored. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_topology_definition_t */

typedef struct afe_custom_topologies_t afe_custom_topologies_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_custom_topologies_t
@{ */
/* Header structure for the custom topologies command buffer. This structure
    is followed by num_topologies of afe_topology_definition_t.
*/
struct afe_custom_topologies_t
{
   uint32_t num_topologies;
   /**< Specifies the number of topologies in this command.

        @values Any nonzero number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_custom_topologies_t */


/** @addtogroup afe_module_audio_device
@{ */
/** ID of the parameter used by #AFE_MODULE_AUDIO_DEV_INTERFACE to configure
    the topology ID of the AFE session. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_topo_id_v1_t}
    @table{weak__afe__topo__id__v1__t}
*/
#define AFE_PARAM_ID_TOPO_ID                                         0x0001025A

/** Version information used to handle future additions to
    AFE_PARAM_ID_TOPO_ID processing (for backward compatibility).
*/
#define AFE_API_VERSION_TOPO_ID                                0x1

/* Structure for the AFE_PARAM_ID_TOPO_ID. */
typedef struct afe_topo_id_v1_t  afe_topo_id_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_topo_id_v1_t
@{ */
/* Configuration structure for the AFE_PARAM_ID_TOPO_ID parameter.
*/
struct afe_topo_id_v1_t
{
   uint32_t                  topo_def_minor_version;
   /**< Minor version used to track AFE topology ID configuration.

        @values #AFE_API_VERSION_TOPO_ID */

   uint32_t                  topology_id;
   /**< ID of the topology for the AFE session.

        @values See Section @xhyperref{hdr:TopoIDs,AFE Topology IDs} */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_topo_id_v1_t */
/** @} */ /* end_addtogroup afe_module_audio_device */

/** @addtogroup afe_topo_ids
@{ */
/** ID of the AFE Tx topology with no modules. */
#define AFE_TX_TOPOLOGY_ID_NONE                       0x000112FB

/** @cond OEM_only */
/** ID of the AFE Tx topology with RMC.

    - Remove Click Noise (#AFE_MODULE_RMC)
*/
#define AFE_TX_TOPOLOGY_ID_RMC                       0x000112F9

/** ID of the no-default AFE Rx topology. */
#define AFE_RX_TOPOLOGY_ID_NONE                        0x000112FC

/** ID of the AFE Rx topology with feedforward speaker protection.

    - Feedforward Speaker Protection (#AFE_MODULE_SPEAKER_PROTECTION)
   */      
#define AFE_RX_TOPOLOGY_ID_FFSP_RX_V1_PROC              0x000112FA

/** ID of the AFE Tx topology with feedback speaker protection VI processing.

    - Feedback Speaker Protection VI processing
      (#AFE_MODULE_FB_SPKR_PROT_VI_PROC)
   */
#define AFE_TX_TOPOLOGY_ID_FBSP_VI_V1_PROC                    0x00012E17

/** ID of the AFE Tx topology with feedback speaker protection Rx processing.

    - Feedback Speaker Protection Rx processing (#AFE_MODULE_FB_SPKR_PROT_RX)
   */
#define AFE_RX_TOPOLOGY_ID_FBSP_RX_V1_PROC                    0x00012E16

/** ID of the AFE Tx topology with software microphone activity detection in
    Low Power mode.

    - Software Microphone Activity Detection (#AFE_MODULE_ID_SW_MAD)
*/
#define AFE_TX_TOPOLOGY_ID_SWMAD_HWMAD                       0x00012E19

/** ID of the AFE Tx topology with software microphone activity detection in
    High Power mode.

    - Software Microphone Activity Detection (#AFE_MODULE_ID_SW_MAD)
*/
#define AFE_TX_TOPOLOGY_ID_SWMAD                       0x00012E18

/** ID of the AFE Tx topology with adaptive active noise control.

    - Adaptive ANC (#AFE_MODULE_AANC)
*/
#define AFE_TX_TOPOLOGY_ID_AANC                       0x0001025B

/** ID of the AFE Tx topology with Speaker Protection V2 in Feedback mode.

    - Feedback Speaker Protection V2 TH VI
      (#AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI)
    - Feedback Speaker Protection V2 EX VI
      (#AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI)
*/
#define AFE_TX_TOPOLOGY_ID_FBSP_VI_V2_PROC             0x0001025C

/** ID of the AFE Rx topology with Speaker Protection V2 in Feedback mode.

    - Feedback Speaker Protection V2 Rx (#AFE_MODULE_SPEAKER_PROTECTION_V2_RX)
*/
#define AFE_RX_TOPOLOGY_ID_FBSP_RX_V2_PROC             0x0001025D

/** ID of the AFE Rx topology with Speaker Protection V2 in Feedforward mode.

    - Feedback Speaker Protection V2 Rx (#AFE_MODULE_SPEAKER_PROTECTION_V2_RX)
*/
#define AFE_RX_TOPOLOGY_ID_FFSP_RX_V2_PROC             0x0001025E

/** @endcond */
/** @} */ /* end_addtogroup afe_topo_ids */


/** @addtogroup afe_module_sw_duty_cycle
@{ */
/** ID of the Software Duty Cycle module, which is used to configure the
    duty cycle of the AFE software.

    This module supports the following parameter IDs:
     - #AFE_PARAM_ID_SW_DUTY_CYCLE_CFG
     - #AFE_PARAM_ID_ENABLE

    To configure the duty cycle, use the #AFE_PORT_CMD_SET_PARAM_V2 command and
    fill the module ID with the parameter IDs.

    The AFE_PARAM_ID_SW_DUTY_CYCLE_CFG and AFE_PARAM_ID_ENABLE (enable=1)
    parameters must be sent before the AFE port starts.

    After receiving AFE_PARAM_ID_ENABLE (enable=0), there is no data exchange
    between the codec and AFE.

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SW_DUTYCYCLE
 */
#define AFE_MODULE_SW_DUTY_CYCLE                                   0x00010258

/** ID of the parameter used by #AFE_MODULE_SW_DUTY_CYCLE to configure the duty
    cycle parameters. 

    AFE_PARAM_ID_SW_DUTY_CYCLE_CFG must be sent before the AFE port starts.
    This parameter is not accepted if the port is in the Run state.

    @apr_hdr_fields
    Opcode -- AFE_PARAM_ID_SW_DUTY_CYCLE_CFG

    @apr_msgpayload{afe_param_id_sw_duty_cycle_cfg_v1_t}
    @table{weak__afe__param__id__sw__duty__cycle__cfg__v1__t}
 */
#define AFE_PARAM_ID_SW_DUTY_CYCLE_CFG                            0x00010259

/** Version information used to handle future additions to
    AFE_PARAM_ID_SW_DUTY_CYCLE_CFG processing (for backward compatibility).
*/
#define AFE_API_VERSION_SW_DUTY_CYCLE_CFG                         0x1

/** @} */ /* end_addtogroup afe_module_sw_duty_cycle */

typedef struct afe_param_id_sw_duty_cycle_cfg_v1_t afe_param_id_sw_duty_cycle_cfg_v1_t;

#include "adsp_begin_pack.h"

  /** @weakgroup weak_afe_param_id_sw_duty_cycle_cfg_v1_t
@{ */
/* Payload of the AFE_PARAM_ID_SW_DUTY_CYCLE_CFG  parameter used by
    AFE_MODULE_SW_DUTY_CYCLE.
*/
struct afe_param_id_sw_duty_cycle_cfg_v1_t
{
    uint32_t                  minor_version;
    /**< Minor version used to track the duty cycle. 

         @values #AFE_API_VERSION_SW_DUTY_CYCLE_CFG */

    uint32_t                  sleep_time_ms;
    /**< The amount of time when the AFE does not process any data.

         @values
         - > 0 milliseconds
         - Default value is 200 milliseconds @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_param_id_sw_duty_cycle_cfg_v1_t */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the Speaker Protection V2 Rx module, which is used to process
    the PCM data to protect up to two speakers.

    This module supports the following parameter IDs:
    - #AFE_PARAM_ID_FBSP_MODE_RX_CFG
    - #AFE_PARAM_ID_SP_V2_RX_PTONE_RAMP_DN_CFG
    - #AFE_PARAM_ID_SP_V2_RX_STATIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_DYNAMIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_NOTCH_DYNAMIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_EX_DYNAMIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_TH_DYNAMIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_ACM_DYNAMIC_CFG
    - #AFE_PARAM_ID_SP_V2_RX_TH_STATS
    - #AFE_PARAM_ID_SP_V2_RX_EX_STATS
    - #AFE_PARAM_ID_SP_V2_RX_ACM_STATS
    - #AFE_PARAM_ID_ENABLE

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SPEAKER_PROTECTION_V2_RX

    @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the Speaker Protection V2 module using
       #AFE_PORT_CMD_SET_PARAM_V2 with #AFE_MODULE_SPEAKER_PROTECTION_V2_RX,
       including the supported parameters.
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port using #AFE_PORT_CMD_DEVICE_STOP (the AFE destroys all
       speaker protection-related information).
    @par
    All configurations except #AFE_PARAM_ID_SP_V2_RX_STATIC_CFG are
    accepted either in the Configurations state of the port or during runtime
    (after #AFE_MODULE_AUDIO_DEV_INTERFACE).
    AFE_PARAM_ID_SP_V2_RX_STATIC_CFG is expected only in the configuration
    state of the port (after AFE_MODULE_AUDIO_DEV_INTERFACE and before
    #AFE_PORT_CMD_DEVICE_START). @newpage
    @par
    The Enable parameter ID for this module can also be enabled when the AFE
    port is in the Run state, which allows this feature to be disabled/enabled
    at runtime.
    However, there will be a glitch in the audio output when the feature is
    disabled and enabled, and vice versa, during runtime. Qualcomm recommends
    that this feature not be disabled/enabled during runtime.
    @par
    This module supports only 1 channel (mono speaker) or 2 channels (stereo
    speakers), 16 or 24 bits, and 8K, 16K, or 48K sampling rates.
    @par Common defines
    Sections @xref{hdr:afeModSpkrProtV2RxCommonStart} through
    @xref{hdr:afeModSpkrProtV2RxCommonEnd} are common defines used in the
    parameters supported by this module.
*/
#define AFE_MODULE_SPEAKER_PROTECTION_V2_RX                        0x0001025F

/** @xreflabel{hdr:afeModSpkrProtV2RxCommonStart}
    Maximum number of stages in the notch filter. */
#define SP_V2_NCH_FILT_STAGES_MAX 5

/** Maximum number of taps in the FIR filter. */
#define SP_V2_MAX_FIR_TAP 48

/** Maximum number of speakers supported in Speaker Protection V2 Rx
    processing. */
#define SP_V2_NUM_MAX_SPKRS 2

/** Number of plotting samples in one thermal Rx output packet. */
#define SP_V2_TH_RX_DEMO_SMPL_PER_PKT 10

/** Number of plotting samples in one excursion Rx output packet. */
#define SP_V2_EX_RX_DEMO_SMPL_PER_PKT  10

/** Number of plotting samples in one audio clip manager Rx output
    packet. */
#define SP_V2_ACM_SMPL_PER_DEMO_PKT 10

/** Number of FFT bins in Real-Time Monitoring (RTM) statistics. */
#define SP_V2_NUM_FFT_BINS 256

/** Maximum number of stages in the IIR filter. */
#define SP_V2_IIR_TDF2_STAGES_MAX 5

/** Number of numerators per stage in the IIR filter. */
#define SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE 3

/** @xreflabel{hdr:afeModSpkrProtV2RxCommonEnd}
    Number of denominators per stage in the IIR filter. */
#define SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE 2

/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    the pilot tone Ramp Down mode of speaker protection Rx processing.
    This parameter must be sent at least 15 ms before a port stop.

    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.
 */
#define AFE_PARAM_ID_SP_V2_RX_PTONE_RAMP_DN_CFG                       0x00010260

/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    the static configuration of Speaker Protection V2 Rx processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_static_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__static__cfg__v1__t}
 */
#define AFE_PARAM_ID_SP_V2_RX_STATIC_CFG                     0x00010261

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_STATIC_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_STATIC_CFG                  0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_static_cfg_v1_t afe_sp_v2_rx_static_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_rx_static_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_STATIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_static_cfg_v1_t
{
   uint32_t       sp_v2_rx_static_cfg_minor_version;
   /**< Minor version used to track speaker protection V2 Rx static
        configuration.

        @values #AFE_API_VERSION_SP_V2_RX_STATIC_CFG */

   uint32_t        features;
   /**< Features enabled in the speaker protection algorithm.

        @values
          - Bit 0 -- Notch high-pass filter
          - Bit 1 -- Thermal protection
          - Bit 2 -- Feedback excursion control
          - Bit 3 -- Analog clip manager
          - Bit 4 -- Feedforward excursion control
          - Bits 31-5 -- Reserved; must be set to zero @tablebulletend */

   uint32_t        tuning_mode_en_flag;
   /**< Specifies whether RTM tuning mode is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint32_t        ctrl_rate;
   /**< Thermal control rate.

        @values
        - 1000 Hz @tablebulletend */

   uint32_t num_nch_filter_stages;
   /**< Number of notch filter stages.

        @values 0 to #SP_V2_NCH_FILT_STAGES_MAX */

   int16_t temp_loop_dly_ms;
   /**< Loop delay from the predicted temperature to the temperature
        information coming back.

        @values 0 to 1000 */

   int16_t pow_est_smooth_flag;
   /**< Specifies whether to use IIR filtering to smooth the power estimation.

        @values
        - 0 -- Do not use IIR filtering
        - 1 -- Use IIR filtering @tablebulletend */

   int16_t num_bs_filter_stages;
   /**< Number of stages for band split LPF and HPF.

        @values 1 to 10 */

   int16_t num_ex_filter_taps;
   /**< Number of taps for the FIR excursion prediction filter.

        @values
        - 24
        - 32
        - 40
        - 48 @tablebulletend */

   uint16_t pt_lvl_switch_en;
   /**< Specifies whether to enable the dynamic pilot tone level switch.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t pt_masking_delay_ms;
   /**< Delay in ramping down the pilot tone.

        @values 0 to 1000 ms */

   int32_t pt_masking_thr_q27;
   /**< Specifies the input level threshold below which the pilot tone is
        disabled.

        @values 0 to 134217727 (in Q27 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_static_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    dynamic parameters for Speaker Protection V2 Rx module processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_RX_DYNAMIC_CFG                    0x00010262

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_STATIC_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_DYNAMIC_CFG                  0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_dynamic_cfg_v1_t afe_sp_v2_rx_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_rx_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_dynamic_cfg_v1_t
{
   uint32_t  sp_v2_rx_dynamic_minor_version;
   /**< Minor version used to track speaker protection V2 Rx dynamic
        configuration.

        @values #AFE_API_VERSION_SP_V2_RX_DYNAMIC_CFG */

   uint32_t  speakers_link_mode;
   /**< Specifies whether the gains applied to the two speakers are linked.

        @values
        - 0 -- Unlinked
        - 1 -- Linked @tablebulletend */

   uint32_t  left_pi_scale_u16q18;
   /**< Left speaker: scale down a full scale 40 Hz pilot tone by this
        value.

        @values 0 to 65535 (in Q18 format) */

   uint32_t  left_rx_scale_u16q16;
   /**< Left speaker: scale down the outgoing signal by this value so
        when the pilot tone is added, the signal does not exceed full scale.

        @values 32768 to 65535 */

   uint32_t  right_pi_scale_u16q18;
   /**< Right speaker: scale down a full scale 40 Hz pilot tone by this
        value. 

        @values 0 to 65535 (in Q18 format) */

   uint32_t  right_rx_scale_u16q16;
   /**< Right speaker: scale down the outgoing signal by this value so
        when the pilot tone is added, the signal does not exceed full scale.

        @values 32768 to 65535 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    notch dynamic parameters for Feedback Speaker Protection V2 Rx module processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_notch_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__notch__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_RX_NOTCH_DYNAMIC_CFG                             0x00010263

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_NOTCH_DYNAMIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_NOTCH_DYNAMIC_CFG                          0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkr_vi */

typedef struct afe_sp_v2_rx_notch_dynamic_cfg_v1_t afe_sp_v2_rx_notch_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_rx_notch_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_NOTCH_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_notch_dynamic_cfg_v1_t
{
   uint32_t sp_v2_rx_notch_dynamic_cfg_minor_version;
   /**< Minor version used to track speaker protection V2 Rx
        notch dynamic configuration.

        @values #AFE_API_VERSION_SP_V2_RX_NOTCH_DYNAMIC_CFG */

   int32_t num[SP_V2_NCH_FILT_STAGES_MAX * SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE];
   /**< Numerator coefficients for notch filter configuration.

        @values 0x80000000 to 0x7FFFFFFF */

    int32_t den[SP_V2_NCH_FILT_STAGES_MAX * SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE];
   /**< Denominator coefficients for notch filter configuration.

        @values 0x80000000 to 0x7FFFFFFF */

   int16_t num_q[SP_V2_NCH_FILT_STAGES_MAX];
   /**< Q factor of numerator coefficients for notch filter configuration.

        @values -32 to 32 */

   int16_t den_q[SP_V2_NCH_FILT_STAGES_MAX];
   /**< Q factor of denominator coefficients for notch filter configuration.

        @values -32 to 32 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_notch_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    dynamic parameters for Feedback Speaker Protection V2 Rx module processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_ex_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__ex__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_RX_EX_DYNAMIC_CFG                         0x00010264

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_EX_DYNAMIC_CFG processing (for backward
    compatibility).
*/
#define AFE_API_VERSION_SP_V2_RX_EX_DYNAMIC_CFG                      0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_ex_dynamic_cfg_v1_t afe_sp_v2_rx_ex_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_ex_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_EX_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_ex_dynamic_cfg_v1_t
{
   uint32_t sp_v2_rx_ex_dynamic_minor_version;
   /**< Minor version used to track speaker protection V2 Rx excursion dynamic
        configuration.

        @values #AFE_API_VERSION_SP_V2_RX_EX_DYNAMIC_CFG */

   int32_t excursion_gain_recovery_constant_q31;
   /**< Excursion gain release constant.

        @values 0 to 2147483647 (in Q31 format) */

   int32_t limiter_gain_recovery_constant_q31;
   /**< Limiter gain release constant.

        @values 0 to 2147483647 (in Q31 format) */

   int32_t left_amp_gain_q24;
   /**< Left speaker: amplifier gain used when scaling the Tx vsense signal to
        an Rx signal.

        @values 0 to 2147483647 (in Q24 format) */

   uint32_t left_ptone_excursion_q16;
   /**< Left speaker: excursion for the pilot tone. This excursion is added to
        the computed peak excursion.

        @values 0 to 32767 mm (in Q16 format) */

   int32_t left_xmax_q24;
   /**< Left speaker: maximum excursion value.

        @values 0 to 2147483647 (in Q24 format) */

   int16_t left_fir_taps;
   /**< Left FIR: Number of taps.

        @values
        - 24
        - 32
        - 40
        - 48 @tablebulletend */

   int16_t left_fir_coeffq;
   /**< Left FIR: Q factor of coefficients. 

        @values 0x8000 to 0x7FFF */

   int32_t left_fir_coeffs[SP_V2_MAX_FIR_TAP];
   /**< Left FIR: coefficients.

        @values 0x80000000 to 0x7FFFFFFF */

   int16_t left_lpf_num_ch;
   /**< Left LPF: number of channels. 

        @values  1 to 2 */

   int16_t left_lpf_stages;
   /**< Left LPF: number of stages. 

        @values  1 to 10 */

   int32_t left_lpf_num[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE];
   /**< Left LPF: numerator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int32_t left_lpf_den[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE];
   /**< Left LPF: denominator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int16_t left_lpf_num_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Left LPF: Q factor of numerator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t left_lpf_den_q[ SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Left LPF: Q factor of denominator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t left_hpf_num_ch;
   /**< Left HPF: number of channels. 

        @values  1 to 2 */

   int16_t left_hpf_stages;
   /**< Left HPF: number of stages. 

        @values  1 to 10 */

   int32_t left_hpf_num[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE];
   /**< Left HPF: numerator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int32_t left_hpf_den[ SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE];
   /**< Left HPF: denominator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int16_t left_hpf_num_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Left HPF: Q factor of numerator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t left_hpf_den_q[ SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Left HPF: Q factor of denominator coefficients. 

        @values  0x8000 to 0x7FFF */

   int32_t left_xmax_margin_q24;
   /**< Left speaker: margin used to modify the overall limiter gain.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_lim_thr_q27;
   /**< Left speaker: limiter threshold.

        @values 0 to 2147483647 (in Q27 format) */

   int32_t right_amp_gain_q24;
   /**< Right speaker: amplifier gain used to scale the Tx vsense signal to the
        Rx signal.

        @values 0 to 2147483647 (in Q24 format) */

   uint32_t right_ptone_excursion_q16;
   /**< Right speaker: excursion for the pilot tone. This excursion is added to
        the computed peak excursion.

        @values 0 to 32767 mm (in Q16 format) */

   int32_t right_xmax_q24;
   /**< Right speaker: xmax value.

        @values 0 to 2147483647 (in Q24 format) */

   int16_t right_fir_taps;
   /**< Right FIR: Number of taps in the right FIR.

        @values
        - 24
        - 32
        - 40
        - 48 @tablebulletend */

   int16_t right_fir_coeffq;
   /**< Right FIR: Q factor of coefficients. 

        @values 0x8000 to 0x7FFF */

   int32_t right_fir_coeffs[SP_V2_MAX_FIR_TAP];
   /**< Right FIR: coefficients.

        @values 0x80000000 to 0x7FFFFFFF */

   int16_t right_lpf_num_ch;
   /**< Right LPF: number of channels. 

        @values  1 to 2 */

   int16_t right_lpf_stages;
   /**< Right LPF: number of stages. 

        @values  1 to 10 */

   int32_t right_lpf_num[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE];
   /**< Right LPF: numerator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int32_t right_lpf_den[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE];
   /**< Right LPF: denominator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int16_t right_lpf_num_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Right LPF: Q factor of numerator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t right_lpf_den_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Right LPF: Q factor of denominator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t right_hpf_num_ch;
   /**< Right HPF: number of channels. 

        @values  1 to 2 */

   int16_t right_hpf_stages;
   /**< Right HPF: number of stages. 

        @values  1 to 10 */

   int32_t right_hpf_num[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_NUM_PER_STAGE];
   /**< Right HPF: numerator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int32_t right_hpf_den[SP_V2_IIR_TDF2_STAGES_MAX* SP_V2_IIR_TDF2_NUM_DEN_PER_STAGE];
   /**< Right HPF: denominator. 

        @values  0x80000000 to 0x7FFFFFFF */

   int16_t right_hpf_num_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Right HPF: Q factor of numerator coefficients. 

        @values  0x8000 to 0x7FFF */

   int16_t right_hpf_den_q[SP_V2_IIR_TDF2_STAGES_MAX];
   /**< Right HPF: Q factor of denominator coefficients. 

        @values  0x8000 to 0x7FFF */

   int32_t right_xmax_margin_q24;
   /**< Right HPF: margin used to modify overall limiter gain.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_lim_thr_q27;
   /**< Right speaker: limiter threshold.

        @values 0 to 2147483647 (in Q27 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_ex_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    dynamic parameters for Feedback Speaker Protection V2 Rx module processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_th_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__th__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_RX_TH_DYNAMIC_CFG                              0x00010265

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_TH_DYNAMIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_TH_DYNAMIC_CFG                           0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_th_dynamic_cfg_v1_t afe_sp_v2_rx_th_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_th_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_TH_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_th_dynamic_cfg_v1_t
{
   uint32_t sp_v2_rx_th_dynamic_minor_version;
   /**< Minor version used to track speaker protection V2 Rx thermal dynamic
        configuration.

        @values #AFE_API_VERSION_SP_V2_RX_TH_DYNAMIC_CFG */

   uint32_t temp_control_mthd;
   /**< Temperature control method.

        @values
        - 0 -- Use feedback tempperature only
        - 1 -- Feedback with lowpass
        - 2 -- Use feedforward estimated temperature @tablebulletend */

   int32_t temp_nominal_q6;
   /**< Assumed voice coil temperature at startup.

        @values -1920 to 12800 degrees C (in Q6 format) */

   int32_t temp_min_q6;
   /**< Minimum reasonable measured temperature. A temperature lower
        than this value is ignored.

        @values -1920 to 12800 degrees C (in Q6 format) */

   int32_t temp_max_q6;
   /**< Maximum reasonable measured temperature. A temperature higher
        than this value is ignored.

        @values -1920 to 12800 degrees C (in Q6 format) */

   int32_t temp_max_chg_sec_q6;
   /**< Maximum temperature change per second. A new temperature is ignored
        if it falls outside this range.

        @values
        - 0 to 32767 degrees C (in Q6 format)
        - 0 disables this feature @tablebulletend*/

   int32_t temp_smoothing_factor_q31;
   /**< Smoothing of the temperature to compute the gain.

        @values 0x80000000 to 0x7FFFFFFF (in Q31 format) */

   int32_t max_attenuation_db_q7;
   /**< Minimum temperature control gain.

        @values -7680 to 0 dB (in Q7 format) */

   int32_t attack_gain_smoothing_factor;
   /**< Smoothing factor for adjusting gain during the attack phase
        (current gain < previous gain).

        @values 328 to 32767 */

   int32_t release_gain_smoothing_factor;
   /**< Smoothing factor for adjusting gain during the release phase
        (current gain > previous gain).

        @values 328- 32767 */

   int32_t temp_dead_zone_q6;
   /**< Dead zone (region near the target temperature) for a reduced
        proportional term.

        @values 2 to 2048 degrees C (in Q6 format) */

   int32_t dead_zone_scaling_q15;
   /**< Scaling factor to modify the proportional term.

        @values 328 to 32767 (in Q15 format) */

   int32_t clip_time_out_ms;
   /**< Timeout used for processing a clip interrupt.

        @values
        - 0 to 4000 milliseconds
        - > 0 enables the clip interrupt timeout @tablebulletend*/

   int32_t vbat_time_out_ms;
   /**< Timeout used to process a VBAT interrupt.

        @values
        - 0 to 1000000 milliseconds
        - > 0 enables the VBAT interrupt timeout @tablebulletend */

   int32_t left_r_spk_coil_q8;
   /**< Left speaker: typical resistance.

        @values 512 to 16384 (in Q8 format) */

   int32_t left_v_full_scale_q10;
   /**< Left speaker: voltage for a digitally full scale signal.

        @values 512 to 15360 (in Q10 format) */

   int32_t left_thermal_resistance_q6;
   /**< Left speaker: total thermal resistance (such as voice coil + magnet).

        @values 0 to 32767 (in Q6 format) */

   int32_t left_thermal_time_constant_low_q10;
   /**< Left speaker: low estimate of the voice coil thermal time constant.

        @values 51 to 32767 seconds (in Q10 format) */

   int32_t left_thermal_time_constant_high_q10;
   /**< Left speaker: high estimate of voice coil thermal time constant.

        @values 51 to 32767 seconds (in Q10 format) */

   int32_t left_temp_tgt_q6;
   /**< Left speaker: target temperature.

        @values -1920 to 12800 degrees C (in Q6 format) */

   int32_t left_pi_ctrl_prop_value_q12;
   /**< Left speaker: value of the proportional term in the PI controller.

        @values 0 to 32767 (in Q12 format) */

   int32_t left_pi_ctrl_intg_value_q12;
   /**< Left speaker: value of the integral term in the PI controller.

        @values 0 to 32767 (in Q12 format) */

   int32_t right_r_spk_coil_q8;
   /**< Right speaker: typical resistance.

        @values 512 to 16384 (in Q8 format) */

   int32_t right_v_full_scale_q10;
   /**< Right speaker: speaker voltage for digitally full scale signal.

        @values 512 to 15360 (in Q10 format) */

   int32_t right_thermal_resistance_q6;
   /**< Right speaker: total thermal resistance (such as voice coil + magnet).

        @values 0 to 32767 (in Q6 format) */

   int32_t right_thermal_time_constant_low_q10;
   /**< Right speaker: low estimate of the voice coil thermal time constant.

        @values 51 to 32767 seconds (in Q10 format) */

   int32_t right_thermal_time_constant_high_q10;
   /**< Right speaker: high estimate of the voice coil thermal time constant.

        @values 51 to 32767 (in Q10 format) */

   int32_t right_temp_tgt_q6;
   /**< Right speaker: target temperature.

        @values -1920 to 12800 degrees C (in Q6 format) */

   int32_t right_pi_ctrl_prop_value_q12;
   /**< Right speaker: value of the proportional term in the PI controller.

        @values 0 to 32767 (in Q12 format) */

   int32_t right_pi_ctrl_intg_value_q12;
   /**< Right speaker: value of the integral term in the PI controller.

        @values 0 to 32767 (in Q12 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_th_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to configure
    dynamic parameters for Feedback Speaker Protection V2 Rx module processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_rx_acm_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__rx__acm__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_RX_ACM_DYNAMIC_CFG                       0x00010266

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_ACM_DYNAMIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_ACM_DYNAMIC_CFG                    0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_acm_dynamic_cfg_v1_t afe_sp_v2_rx_acm_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_acm_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_ACM_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_rx_acm_dynamic_cfg_v1_t
{
   uint32_t sp_v2_rx_acm_dynamic_cfg_minor_version;
   /**< Minor version used to track speaker protection v2
        Rx ACM dynamic configuration.

        @values #AFE_API_VERSION_SP_V2_RX_ACM_DYNAMIC_CFG */

   uint32_t cdc_buf_q_format;
   /**< Q-format of the clip PCM values returned by the codec.

        @values 1 to 15 */

   uint32_t clip_pcm_buf_len;
   /**< Length of buffer containing clip PCM values.

        @values 1 to 16 */

   int32_t lim_thr_to_clip_level_ratio_q15;
   /**< Limiter threshold = lim_thr_to_clip_level_ratio_q15 * clip PCM value.

        @values 16384 to 32767 (in Q15 format) */

   int32_t lowest_acc_clip_level_Q15;
   /**< Lowest acceptable clip level. Any clipping detecting below this level
        is ignored.

        @values 0 to 23281 (in Q15 format) */

   int32_t thr_inc_step_in_db_Q15;
   /**< Limiter threshold increment per step_size_in_msec.

        @values 0 to 32767 (0.99 dB in Q15 format) */

   uint32_t thr_inc_period_in_msec;
   /**< Step size for the limiter threshold increment.

        @values 1 to 10000 ms */

   uint32_t loudness_boost_en;
   /**< Enable/disable loudness boost mode.

        @values
          - 0 -- Disabled
          - 1 -- Enabled @tablebulletend */

    int32_t loudness_threshold_q27;
    /**< Maximum limiter threshold in Loudness Boost mode.

         @values 0 to 134217727 */

   int32_t loudness_temp_margin_q6;
   /**< Temperature prediction error window, due to corrupt Isen samples.

        @values 0 to 1280 (in Q6 format) */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_acm_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to log
    Rx TH tuning statistics.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_sp_v2_rx_th_stats_v1_t}
    @table{weak__afe__sp__v2__rx__th__stats__v1__t}

  @if OEM_only
    @newpage
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_SP_V2_RX_TH_STATS                       0x00010267

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_TH_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_TH_STATS                    0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_th_stats_v1_t afe_sp_v2_rx_th_stats_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_th_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_TH_STATS parameter (version 1).
*/
struct afe_sp_v2_rx_th_stats_v1_t
{
   uint32_t sp_v2_rx_th_stats_minor_version;
   /**< Minor version used to track speaker protection V2 Rx thermal
        statistics.

        @values #AFE_API_VERSION_SP_V2_RX_TH_STATS */

    uint32_t frame_duration_in_ms;
    /**< Frame duration in milliseconds for Thermal Rx statistics.

       @values Valid uint32 number */

    uint32_t frame_num;
    /**< Frame number of the Thermal Rx statistics. This field is reset to zero
       after crossing the maximum limit for uint32 variables.

       @values Valid uint32 number */

   int32_t vc_resis_q24[SP_V2_NUM_MAX_SPKRS][SP_V2_TH_RX_DEMO_SMPL_PER_PKT];
   /**< Voice coil resistance array (in Ohms in Q24 format). */

   int32_t vc_temp_q22[SP_V2_NUM_MAX_SPKRS][SP_V2_TH_RX_DEMO_SMPL_PER_PKT];
   /**< Voice coil temperature array (in degrees C in Q22 format). */

   int32_t th_gain_lnk_db_q23[SP_V2_NUM_MAX_SPKRS][SP_V2_TH_RX_DEMO_SMPL_PER_PKT];
   /**< Gain control array (in deciBels in Q23 format). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_th_stats_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to log
    rx ex tuning statistics.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_sp_v2_rx_ex_stats_v1_t}
    @table{weak__afe__sp__v2__rx__ex__stats__v1__t}

  @if OEM_only
    @newpage
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_SP_V2_RX_EX_STATS                       0x00010268

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_EX_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_EX_STATS                    0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_ex_stats_v1_t afe_sp_v2_rx_ex_stats_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_ex_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_EX_STATS parameter (version 1).
*/
struct afe_sp_v2_rx_ex_stats_v1_t
{
   uint32_t sp_v2_rx_ex_stats_minor_version;
   /**< Minor version used to track speaker protection V2
        Rx excursion statistics.

        @values #AFE_API_VERSION_SP_V2_RX_EX_STATS */

    uint32_t frame_duration_in_ms;
    /**< Frame duration in milliseconds for Excursion Rx statistics.

        @values Valid uint32 number */

    uint32_t frame_num;
    /**< Frame number of the Excursion Rx statistics. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

         @values Valid uint32 number */

   int32_t xmax_q14[SP_V2_NUM_MAX_SPKRS ];
   /**< Maximum excursion limit (in Q14 format). */

   int32_t total_gain_q31[SP_V2_NUM_MAX_SPKRS ][SP_V2_EX_RX_DEMO_SMPL_PER_PKT];
   /**< Excursion control gain (in Q31 format). */

   uint16_t pred_peak_exc_q14[SP_V2_NUM_MAX_SPKRS ][SP_V2_EX_RX_DEMO_SMPL_PER_PKT];
   /**< Predicted excursion (in Q14 format). */

   uint16_t ctrl_peak_exc_q14[SP_V2_NUM_MAX_SPKRS ][SP_V2_EX_RX_DEMO_SMPL_PER_PKT];
   /**< Controlled excursion (in Q14 format). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_ex_stats_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to log
    rx acm tuning statistics.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_sp_v2_rx_acm_stats_v1_t}
    @table{weak__afe__sp__v2__rx__acm__stats__v1__t}

  @if OEM_only
    @newpage
    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
  @endif
*/
#define AFE_PARAM_ID_SP_V2_RX_ACM_STATS                       0x00010269

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_RX_ACM_STATS processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_RX_ACM_STATS                    0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

typedef struct afe_sp_v2_rx_acm_stats_v1_t afe_sp_v2_rx_acm_stats_v1_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_afe_sp_v2_rx_acm_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_ACM_STATS parameter (version 1).
*/
struct afe_sp_v2_rx_acm_stats_v1_t
{
   uint32_t sp_v2_rx_acm_stats_minor_version;
   /**< Minor version used to track speaker protection V2
        Rx ACM statistics.

        @values #AFE_API_VERSION_SP_V2_RX_ACM_STATS */

    uint32_t frame_duration_in_ms;
    /**< Frame duration in milliseconds for ACM statistics.

        @values Valid uint32 number */

    uint32_t frame_num;
    /**< Frame number of the ACM statistics. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

         @values Valid uint32 number */

   int32_t clip_intr_status[SP_V2_NUM_MAX_SPKRS][SP_V2_ACM_SMPL_PER_DEMO_PKT];
   /**< Clip interrupt status (high or low). */

    uint16_t clip_level_q15[SP_V2_NUM_MAX_SPKRS][SP_V2_ACM_SMPL_PER_DEMO_PKT];
   /**< Clip level (in Q15 format). */

   int32_t lim_threshold_q27[SP_V2_NUM_MAX_SPKRS][SP_V2_ACM_SMPL_PER_DEMO_PKT];
   /**< Limiter threshold (in Q27 format). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_rx_acm_stats_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_module_feedback_spkrv2_rx
@{ */
  /** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_RX to log
    Rx tuning statistics.

    This parameter ID is currently used for logging the algorithm internal
    variables. It is not supported by #AFE_PORT_CMD_SET_PARAM_V2 and
    #AFE_PORT_CMD_GET_PARAM_V2.

    @apr_msgpayload{afe_sp_v2_rx_stats_v1_t}
    @table{weak__afe__sp__v2__rx__stats__v1__t}

    @par Algorithm logging data (afe_algo_log_header_t)
    @tablens{weak__afe__algo__log__header__t}
   */
#define AFE_PARAM_ID_SP_V2_RX_STATS                       0x00010284

/** Version information used to handle future additions to
    #AFE_PARAM_ID_SP_V2_RX_STATS processing (for backward compatibility).
   */
#define AFE_API_VERSION_SP_V2_RX_STATS                    0x1

/** @} */ /* end_addtogroup afe_module_feedback_spkrv2_rx */

  typedef struct afe_sp_v2_rx_stats_v1_t afe_sp_v2_rx_stats_v1_t;

#include "adsp_begin_pack.h"

  /** @weakgroup weak_afe_sp_v2_rx_stats_v1_t
@{ */
  /* Configuration structure for the
    AFE_PARAM_ID_SP_V2_RX_STATS parameter (version 1).
   */
  struct afe_sp_v2_rx_stats_v1_t
  {
    uint32_t sp_v2_rx_stats_minor_version;
   /**< Minor version used for tracking speaker protection v2 Rx statistics.

        @values #AFE_API_VERSION_SP_V2_RX_STATS */

    uint32_t frame_duration_in_ms;
    /**< Frame duration in milliseconds for Rx statistics.

        @values Valid uint32 number */

    uint32_t frame_num;
    /**< Frame number of the Rx statistics. This field is reset to zero
        after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

    uint32_t num_speakers;
    /**< Number of speakers. 

      @values Valid uint32 number */

    uint32_t features;
    /**< Features enabled in the speaker protection algorithm.

          @values
          - Bit 0 -- Notch High pass filter
          - Bit 1 -- Thermal protection
          - Bit 2 -- Feedback Excursion control
          - Bit 3 -- Analog clip manager
          - Bit 4 -- Feedforward Excursion control
          - Bits 31-5 -- Reserved; must be set to zero @tablebulletend */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_afe_sp_v2_rx_stats_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_thvi
@{ */
/** ID of the Speaker Protection V2 Thermal VI module, which is used to
    process Vsens and Isens data for extracting the speaker temperature.

    This module supports the following parameter IDs:
     - #AFE_PARAM_ID_SP_V2_TH_VI_MODE_CFG
     - #AFE_PARAM_ID_SP_V2_TH_VI_STATIC_CFG
     - #AFE_PARAM_ID_SP_V2_TH_VI_DYNAMIC_CFG
     - #AFE_PARAM_ID_SP_V2_TH_VI_CALIB_RES_CFG

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI

    @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the Speaker Protection V2 module using
       #AFE_PORT_CMD_SET_PARAM_V2 with #AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI,
       including its other parameters (optional).
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port when needed using #AFE_PORT_CMD_DEVICE_STOP (the AFE
       destroys all speaker protection-related information).
    @par
    All configurations except the #AFE_PARAM_ID_SP_V2_TH_VI_STATIC_CFG and
    #AFE_API_VERSION_SP_V2_TH_VI_MODE_CFG, are
    accepted either in configurations state of the port or during runtime
    (after #AFE_MODULE_AUDIO_DEV_INTERFACE).
    While the beforementioned two params is expected only in the configuration
    state of the port  (i.e., after #AFE_MODULE_AUDIO_DEV_INTERFACE and before
    #AFE_PORT_CMD_DEVICE_START).
    @par
    This module supports only 2 channels (mono speaker VI) or 4 channels (stereo
    speaker VI), 16 bits, and 8K or 48K sampling rates. @newpage
*/
#define AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI                         0x0001026A

/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI to configure
    the mode of feedback speaker protection thermal VI processing. Only
    #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_th_vi_mode_cfg_v1_t}
    @table{weak__afe__sp__v2__th__vi__mode__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_TH_VI_MODE_CFG                          0x0001026B

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_TH_VI_MODE_CFG processing (for backward compatibility).
    @newpage
*/
#define AFE_API_VERSION_SP_V2_TH_VI_MODE_CFG                        0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_thvi */

typedef struct afe_sp_v2_th_vi_mode_cfg_v1_t afe_sp_v2_th_vi_mode_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_th_vi_mode_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_TH_VI_MODE_CFG parameter (version 1).
*/
struct afe_sp_v2_th_vi_mode_cfg_v1_t
{
   uint32_t sp_v2_th_vi_mode_cfg_minor_version;
   /**< Minor version used to track speaker protection V2
        thermal VI mode configuration.

        @values #AFE_API_VERSION_SP_V2_TH_VI_MODE_CFG */

   uint32_t operation_mode;
   /**< Operation mode of thermal VI module.

        @values
           - 0 -- Normal Running mode
           - 1 -- Calibration mode @tablebulletend */

   uint32_t r0t0_selection_flag[SP_V2_NUM_MAX_SPKRS];
   /**< Specifies which set of R0, T0 values the algorithm will use. This field
        is valid only in Normal mode (operation_mode = 0).
 
        @values
          - 0 -- Use calibrated R0, T0 value
          - 1 -- Use safe R0, T0 value @tablebulletend */

   int32_t r0_cali_q24[SP_V2_NUM_MAX_SPKRS];
   /**< Calibration point resistance per device. This field is valid only
        in Normal mode (operation_mode = 0).

        @values 33554432 to 1073741824 Ohms (in Q24 format) */

   int16_t t0_cali_q6[SP_V2_NUM_MAX_SPKRS];
   /**< Calibration point temperature per device. This field is valid
        in both Normal mode and Calibration mode.

        @values -1920 to 5120 degrees C (in Q6 format) */

   uint32_t quick_calib_flag;
   /**< Indicates whether calibration is to be done in quick mode or not.
        This field is valid only in Calibration mode (operation_mode = 1).

        @values
          - 0 -- Disabled
          - 1 -- Enabled @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_th_vi_mode_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_thvi
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI to
    configure static parameters of thermal VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_th_vi_static_cfg_v1_t}
    @table{weak__afe__sp__v2__th__vi__static__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_TH_VI_STATIC_CFG                       0x0001026C

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_TH_VI_STATIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_TH_VI_STATIC_CFG                         0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_thvi */

typedef struct afe_sp_v2_th_vi_static_cfg_v1_t afe_sp_v2_th_vi_static_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_th_vi_static_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_TH_VI_STATIC_CFG parameter (version 1).
*/
struct afe_sp_v2_th_vi_static_cfg_v1_t
{
   uint32_t sp_v2_th_vi_static_cfg_minor_version;
   /**< Minor version used to track speaker protection V2
        thermal VI static configuration.

        @values #AFE_API_VERSION_SP_V2_TH_VI_STATIC_CFG */

   uint32_t ctrl_rate;
   /**< Thermal control rate.

        @values
          - 500 Hz
          - 1000 Hz @tablebulletend */

   int32_t pow_supply_freq;
   /**< Specifies the power supply frequency.

        @values
          - 0 -- Disabled
          - 50 -- 50 Hz
          - 60 -- 60 Hz @tablebulletend */

   uint16_t pt_lvl_switch_en;
   /**< Specifies whether to enable the dynamic pilot tone level switch.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t pt_masking_delay_ms;
   /**< Delay in ramping down the pilot tone.

        @values 0 to 1000 ms */

   int32_t pt_masking_thr_q27;
   /**< Specifies the input level threshold below which the pilot tone is
        disabled.

        @values 0 to 134217727 (in Q27 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_th_vi_static_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_thvi
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI to
    configure dynamic thermal parameters for feedback speaker protection
    VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_th_vi_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__th__vi__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_TH_VI_DYNAMIC_CFG                     0x0001026D

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_TH_VI_DYNAMIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_TH_VI_DYNAMIC_CFG                  0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_thvi */

typedef struct afe_sp_v2_th_vi_dynamic_cfg_v1_t afe_sp_v2_th_vi_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_th_vi_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_TH_VI_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_th_vi_dynamic_cfg_v1_t
{
   uint32_t sp_v2_th_vi_dynamic_cfg_minor_version;
   /**< Minor version used to track speaker protection V2
        thermal VI dynamic configuration.

        @values #AFE_API_VERSION_SP_V2_TH_VI_DYNAMIC_CFG */

   uint32_t left_pilot_tone_scale_u16q18;
   /**< Left speaker: scale of pilot tone relative to 0 dBFs
        (for example, -40 dB from the full scale).

        @values 0 to 65535 (in Q18 format) */

   int32_t left_wait_time_ms;
   /**< Left speaker: wait time for initial settling before collecting
        statistics.

        @values 100 to 5000 ms */

   int32_t left_cali_time_ms;
   /**< Left speaker: calibration time.

        @values 500 to 30000 ms */

   int32_t left_r0_safe_q24;
   /**< Left speaker: backup calibration point resistance when per-device
        calibration is not available.

        @values 33554432 to 1073741824 Ohms (in Q24 format) */

   int16_t left_t0_safe_q6;
   /**< Left speaker: backup calibration point temperature when per-device
        calibration is not available.

        @values -1920 to 5120 degrees C (in Q6 format) */

   int16_t left_r_spk_coil_typ_q8;
   /**< Typical resistance of the left speaker.

        @values 512 to 32767 Ohms (in Q8 format) */

   int16_t left_r_spk_coil_factor_q10;
   /**< Left speaker: factor used to determine the threshold for speaker coil
        resistance (threshold for speaker coil resistance = factor * speaker
        coil resistance). After this threshold, the speaker is considered open.

        @values -32768 to 32767 (in Q10 format) */

   int16_t left_v_full_sc_q10;
   /**< Left speaker: voltage for digitally full scale signal.

        @values 0 to 32767 (in Q10 format) */

   uint16_t left_spk_resistivity_coeff_u16q7;
   /**< Left speaker: resistivity coefficient (1/degree C).

        @values 0 to 65535 degrees C */

   uint16_t left_vsen_2_v_u16q11;
   /**< Left speaker: conversion factor from Vsens digital to volts.

        @values 0 to 65535 (in Q11 format) */

   uint16_t left_isen_2_a_u16q11;
   /**< Left speaker: conversion factor from Isens digital to amps.

        @values 0 to 65535 (in Q11 format) */

   uint16_t left_v_pilot_thsd_u16q16;
   /**< Left speaker: fraction of the expected pilot tone. Below this value, the
        resistance update is unreliable.

        @values 0 to 65535 */

   uint16_t left_r0_und_est_fac_q16;
   /**< Left speaker: underestimate R0 if it is quick calibration.

        @values 0 to 65535 (in Q16 format) */

   int16_t left_r0_rng_fac_q10;
   /**< Left speaker: factor used to determine the threshold for calculated
        calibrated resistance (threshold for calibrated resistance = factor
        * calibrated resistance). After this threshold, calibrated resistance
        is considered as failed. 

        @values -32768 to 32767 (in Q10 format) */

   int16_t left_t0_min_q6;
   /**< Left speaker: minimum expected temperature from calibration.

        @values -1920 to 5120 degrees C (in Q6 format) */

   int16_t left_t0_max_q6;
   /**< Left speaker: maximum expected temperature from calibration.

        @values -1920 to 5120 degrees C (in Q6 format) */

   uint32_t right_pilot_tone_scale_u16q18;
   /**< Right speaker: scale of the pilot tone relative to 0 dBFs
        (for example, -40 dB from the full scale).

        @values 0 to 65535 (in Q18 format) */

   int32_t right_wait_time_ms;
   /**< Right speaker: wait time for initial settling before collecting
        statistics.

        @values 100 to 5000 ms */

   int32_t right_cali_time_ms;
   /**< Right speaker: calibration time.

        @values 500 to 30000 ms */

   int32_t right_r0_safe_q24;
   /**< Right speaker: backup calibration point resistance when per-device
        calibration is not available.

        @values 33554432 to 1073741824 Ohms (in Q24 format) */

   int16_t right_t0_safe_q6;
   /**< Right speaker: backup calibration point temperature when per-device
        calibration is not available.

        @values -1920 to 5120 degrees C (in Q6 format) */

   int16_t right_r_spk_coil_typ_q8;
   /**< Right speaker: typical resistance of the speaker.

        @values 512 to 32767 Ohms (in Q8 format) */

   int16_t right_r_spk_coil_factor_q10;
   /**< Right speaker: factor used to determine the threshold for speaker coil
        resistance (threshold for speaker coil resistance = factor * speaker
        coil resistance). After this threshold, the speaker is considered open.

        @values -32768 to 32767 (in Q10 format) */

   int16_t right_v_full_sc_q10;
   /**< Right speaker: speaker voltage for a digitally full-scale signal.

        @values 0 to 32767 (in Q10 format) */

   uint16_t right_spk_resistivity_coeff_u16q7;
   /**< Right speaker: resistivity coefficient (1/degree C).

        @values 0 to 65535 degrees C */

   uint16_t right_vsen_2_v_u16q11;
   /**< Right speaker: conversion factor from Vsens digital to volts.

        @values 0 to 65535 (in Q11 format) */

   uint16_t right_isen_2_a_u16q11;
   /**< Right speaker: conversion factor from Isens digital to amps.

        @values 0 to 65535 (in Q11 format) */

   uint16_t right_v_pilot_thsd_u16q16;
   /**< Right speaker: fraction of the expected pilot tone. Below this value,
        the resistance update is unreliable.

        @values 0 to 65535 (in Q16 format) */

   uint16_t right_r0_und_est_fac_q16;
   /**< Right speaker: underestimate R0 if it is quick calibration.

        @values 0 to 65535 (in Q16 format) */

   int16_t right_r0_rng_fac_q10;
   /**< Right speaker: factor used to determine the threshold for calculated
        calibrated resistance (threshold for calibrated resistance = factor
        * calibrated resistance). After this threshold, calibrated resistance
        is considered as failed.

        @values -32768 to 32767 (in Q10 format) */

   int16_t right_t0_min_q6;
   /**< Right speaker: minimum expected temperature from calibration.

        @values -1920 to 5120 degrees C (in Q6 format) */

   int16_t right_t0_max_q6;
   /**< Right speaker: maximum expected temperature from calibration.

        @values -1920 to 5120 degrees C (in Q6 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_th_vi_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_thvi
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_TH_VI to
    get the calibrated resistance value from the feedback speaker VI processing module.

    Only #AFE_PORT_CMD_GET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_th_vi_calib_res_cfg_v1_t}
    @table{weak__afe__sp__v2__th__vi__calib__res__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_TH_VI_CALIB_RES_CFG                    0x0001026E

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_TH_VI_CALIB_RES_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_TH_VI_CALIB_RES_CFG                  0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_thvi */

typedef struct afe_sp_v2_th_vi_calib_res_cfg_v1_t afe_sp_v2_th_vi_calib_res_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_th_vi_calib_res_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_TH_VI_CALIB_RES_CFG parameter (version 1).
*/
struct afe_sp_v2_th_vi_calib_res_cfg_v1_t
{
   uint32_t sp_v2_th_vi_calib_res_cfg_minor_version;
   /**< Minor version used to track speaker protection V2
        thermal VI calibration resistance configuration.

        @values #AFE_API_VERSION_SP_V2_TH_VI_CALIB_RES_CFG */

   int32_t r0_cali_q24[SP_V2_NUM_MAX_SPKRS];
   /**< Calibration point resistance per device. In Calibration mode, this
        resistance is not valid.

        @values 33554432 to 1073741824 Ohms (in Q24 format) */

   uint32_t th_vi_ca_state;
   /**< Represents the calibration state for both speakers.
        The state of each speaker is tied together.

        @values
         - 0 -- Incorrect operation mode is returned if
           AFE_PARAM_ID_SP_V2_TH_VI_CALIB_RES_CFG is called when operation_mode
           is normal processing.
         - 1 -- Inactive mode -- When a port is not started, this value is
           returned.
         - 2 -- Wait state (left_wait_time_ms + right_wait_time_ms) -- The
           wait time for initial settling before collecting statistics (in
           milliseconds).
         - 3 -- In the Calibration state.
         - 4 -- Success.
         - 5 -- Failed. @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_th_vi_calib_res_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_exvi
@{ */
/** ID of the Speaker Protection V2 Excursion VI module, which is used to
    process Vsens and Isens data for extracting speaker excursion information.

    This module supports the following parameter IDs:
     - #AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG
     - #AFE_PARAM_ID_SP_V2_EX_VI_DYNAMIC_CFG
     - #AFE_PARAM_ID_SP_V2_EX_VI_STATS

    @apr_hdr_fields
    Opcode -- AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI

    @detdesc
    The AFE does not cache the configuration information when stopping the
    port. Following is the expected sequence:
    -# Configure the port using #AFE_MODULE_AUDIO_DEV_INTERFACE.
    -# Configure and enable the Speaker Protection V2 module using
       #AFE_PORT_CMD_SET_PARAM_V2 with #AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI,
       including its other parameters (optional).
    -# Start the port using #AFE_PORT_CMD_DEVICE_START.
    -# Stop the port when needed using #AFE_PORT_CMD_DEVICE_STOP (the AFE
       destroys all speaker protection-related information).
    @par
    All configurations except #AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG are
    accepted either in the Configuration state of the port or during runtime
    (after #AFE_MODULE_AUDIO_DEV_INTERFACE).
    AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG and
    AFE_PARAM_ID_SP_V2_EX_VI_DYNAMIC_CFG are expected only in the Configuration
    state of the port (after AFE_MODULE_AUDIO_DEV_INTERFACE and before
    #AFE_PORT_CMD_DEVICE_START).
    @par
    This module supports only 2 channels (mono speaker VI) or 4 channels (stereo
    speaker VI), 16 bits, and 8K or 48K sampling rates. @newpage
*/
#define AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI                         0x0001026F

/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI to
    configure the static parameters of feedback Speaker Protection Excursion VI
    processing. Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_ex_vi_static_cfg_v1_t}
    @table{weak__afe__sp__v2__ex__vi__static__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG                          0x00010270

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_EX_VI_STATIC_CFG                       0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_exvi */

typedef struct afe_sp_v2_ex_vi_static_cfg_v1_t afe_sp_v2_ex_vi_static_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_ex_vi_static_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_EX_VI_STATIC_CFG parameter (version 1).
*/
struct afe_sp_v2_ex_vi_static_cfg_v1_t
{
   uint32_t sp_v2_ex_vi_static_cfg_minor_version;
   /**< Minor version used to track speaker protection V2 excursion VI static
        configuration.

        @values #AFE_API_VERSION_SP_V2_EX_VI_STATIC_CFG */

   uint32_t ex_filter_taps;
   /**< Number of taps in the excursion prediction.

        @values
        - 24
        - 32
        - 40
        - 48 @tablebulletend */

   uint32_t exc_fine_tune_en_flag;
   /**< Specifies whether the Tuning mode is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint32_t tuning_mode_en_flag;
   /**< Specifies whether RTM tuning mode is enabled.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t pt_lvl_switch_en;
   /**< Specifies whether to enable the dynamic pilot tone level switch.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   uint16_t pt_masking_delay_ms;
   /**< Delay in ramping down the pilot tone.

        @values 0 to 1000 ms */

   int32_t pt_masking_thr_q27;
   /**< Specifies the input level threshold below which the pilot tone is
        disabled.

        @values 0 to 134217727 (in Q27 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_ex_vi_static_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_exvi
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI
    to configure the dynamic parameters of excursion VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_ex_vi_dynamic_cfg_v1_t}
    @table{weak__afe__sp__v2__ex__vi__dynamic__cfg__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_EX_VI_DYNAMIC_CFG                       0x00010271

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_EX_VI_DYNAMIC_CFG processing (for backward
    compatibility). @newpage
*/
#define AFE_API_VERSION_SP_V2_EX_VI_DYNAMIC_CFG                         0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_exvi */

typedef struct afe_sp_v2_ex_vi_dynamic_cfg_v1_t afe_sp_v2_ex_vi_dynamic_cfg_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_ex_vi_dynamic_cfg_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_EX_VI_DYNAMIC_CFG parameter (version 1).
*/
struct afe_sp_v2_ex_vi_dynamic_cfg_v1_t
{
   uint32_t sp_v2_ex_vi_dynamic_cfg_minor_version;
   /**< Minor version used to track speaker protection V2 excursion VI dynamic
        configuration.

        @values #AFE_API_VERSION_SP_V2_EX_VI_DYNAMIC_CFG */

   int32_t impedance_convergence_level_thr_q15;
   /**< Impedance convergence level threshold.

        @values 16384 to 32767 (in Q15 format) */

   int32_t ex_filter_stable_level_thr_q31;
   /**< Excursion prediction filter stability threshold.

        @values 1073741824 to 2147483647 (in Q31 format) */

   int32_t ex_filter_energy_level_thr_q31;
   /**< Excursion prediction filter energy threshold as compared to the shape
        of the reference filter.

        @values 1073741824 to 2147483647 (in Q31 format) */

   int32_t impedance_convergence_speed_ctrl_cnst_q31;
   /**< Impedance convergence speed control parameter.
        The higher the value, the faster the convergence, but with more noise.

        @values 0 to 1073741824 (in Q31 format) */

   int32_t left_re_typ_q24;
   /**< Left speaker: typical resistance of the speaker.

        @values 0 to 2147483647 Ohms (in Q24 format) */

   int32_t left_vsen_2_v_q24;
   /**< Left speaker: Vsens scaling constant.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_isen_2_a_q24;
   /**< Left speaker: Isens scaling constant.

        @values -2147483648 to 2147483647 (in Q24 format) */

   int32_t left_amp_gain_q24;
   /**< Left speaker: amplifier gain used when scaling a Tx Vsens signal to an
        Rx signal.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_re_q24;
   /**< Left speaker: dc resistance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_le_q24;
   /**< Left speaker: inductance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_bl_q24;
   /**< Left speaker: force factor parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_fct_q20;
   /**< Left speaker: resonance frequency parameter.

        @values 0 to 2147483647 (in Q20 format) */

   int32_t left_qmct_q24;
   /**< Left speaker: Q factor parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_rect_q24;
   /**< Left speaker: mechanical resistance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t left_pi_scale_q31;
   /**< Left speaker: scale of the pilot tone relative to 0 dBFs
        (for example, -40 dB from the full scale).

        @values 0 to 2147483647 (in Q31 format) */

   int32_t left_tol_range_q15;
   /**< Left speaker: tolerance range for speaker parameters
        (for example, 20%).

        @values 0 to 32767 (in Q15 format) */

   int32_t right_re_typ_q24;
   /**< Right speaker: typical resistance of the speaker.

        @values 0 to 2147483647 Ohms (in Q24 format) */

   int32_t right_vsen_2_v_q24;
   /**< Right speaker: Vsens scaling constant.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_isen_2_a_q24;
   /**< Right speaker: Isens scaling constant.

        @values -2147483648 to 2147483647 (in Q24 format) */

   int32_t right_amp_gain_q24;
   /**< Right speaker: amplifier gain used when scaling a Tx Vsens signal
        to an Rx signal.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_re_q24;
   /**< Right speaker: dc resistance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_le_q24;
   /**< Right speaker: inductance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_bl_q24;
   /**< Right speaker: force factor parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_fct_q20;
   /**< Right speaker: resonance frequency parameter.

        @values 0 to 2147483647 (in Q20 format) */

   int32_t right_qmct_q24;
   /**< Right speaker: Q factor parameters.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_rect_q24;
   /**< Right speaker: mechanical resistance parameter.

        @values 0 to 2147483647 (in Q24 format) */

   int32_t right_pi_scale_q31;
   /**< Right speaker: scale of the pilot tone relative to 0 dBFs
        (for example, for -40 dB.

        @values 0 to 2147483647 (in Q31 format) */

   int32_t right_tol_range_q15;
   /**< Right speaker: tolerance range for speaker parameters
        (for example, 20%).

        @values 0- 32767 (in Q15 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_ex_vi_dynamic_cfg_v1_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup afe_mod_feedback_spkrv2_exvi
@{ */
/** ID of the parameter used by #AFE_MODULE_SPEAKER_PROTECTION_V2_EX_VI to configure
    excursion parameters for feedback Speaker Protection VI processing.
    Only #AFE_PORT_CMD_SET_PARAM_V2 can use this parameter ID.

    @apr_msgpayload{afe_sp_v2_ex_vi_stats_v1_t}
    @table{weak__afe__sp__v2__ex__vi__stats__v1__t}
*/
#define AFE_PARAM_ID_SP_V2_EX_VI_STATS                     0x00010272

/** Version information used to handle future additions to
    AFE_PARAM_ID_SP_V2_EX_VI_STATS processing (for backward compatibility).
*/
#define AFE_API_VERSION_SP_V2_EX_VI_STATS                  0x1

/** @} */ /* end_addtogroup afe_mod_feedback_spkrv2_exvi */

typedef struct afe_sp_v2_ex_vi_stats_v1_t afe_sp_v2_ex_vi_stats_v1_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_afe_sp_v2_ex_vi_stats_v1_t
@{ */
/* Configuration structure for the
    AFE_PARAM_ID_SP_V2_EX_VI_STATS parameter (version 1).
*/
struct afe_sp_v2_ex_vi_stats_v1_t
{
   uint32_t sp_v2_ex_vi_stats_minor_version;
   /**< Minor version used to track speaker protection V2 excursion VI
        statistics.

        @values #AFE_API_VERSION_SP_V2_EX_VI_STATS */

    uint32_t frame_duration_in_ms;
    /**< Frame duration in milliseconds for Excursion VI statistics.

        @values Valid uint32 number */

    uint32_t frame_num;
    /**< Frame number of the Excursion VI statistics. This field is reset to
         zero after crossing the maximum limit for uint32 variables.

        @values Valid uint32 number */

    uint32_t exc_fine_tune_en_flag;
    /**< Specifies whether fine tuning is enabled for Excursion statistics.

        @values
        - 0 -- Disabled
        - 1 -- Enabled @tablebulletend */

   int32_t impedance_mag_response[SP_V2_NUM_MAX_SPKRS][SP_V2_NUM_FFT_BINS];
   /**< Impedance magnitude response. */

   int32_t excursion_mag_response[SP_V2_NUM_MAX_SPKRS][SP_V2_NUM_FFT_BINS];
   /**< Excursion magnitude response. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_afe_sp_v2_ex_vi_stats_v1_t */
/** @endcond */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* ADSP_AFE_SERVICE_COMMANDS_H_ */
