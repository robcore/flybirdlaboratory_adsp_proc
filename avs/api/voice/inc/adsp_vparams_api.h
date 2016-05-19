#ifndef __ADSP_VPARAMS_API_H__
#define __ADSP_VPARAMS_API_H__

/**
  @file adsp_vparams_api.h
  @brief This file contains module and parameter IDs for calibration purposes.
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
10/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited for 2.6.
04/28/14   sw      (Tech Pubs) Updated Doxygen for 2.4.
02/25/13   sw      (Tech Pubs) Updated Doxygen for 2.0 internal draft.
02/27/12   sw      (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
10/11/10   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
===========================================================================*/


/** @ingroup cal_param_ids
    Parameter used to enable or disable a module.

    @inputtable{Cal_ID_0x00010E00.tex}
*/
#define VOICE_PARAM_MOD_ENABLE             (0x00010E00)

/** @cond OEM_only */
/** @ingroup group cal_module_ids
    Module that identifies the Limiter algorithm in the voice stream
    on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_TX_STREAM_LIMITER
*/
#define VOICE_MODULE_TX_STREAM_LIMITER (0x00010F15)

/** @ingroup cal_param_ids
    ID of the Limiter parameter used to control the dynamic range of signals.

    The maximum array size for this parameter is:
    - Version 0 -- 16 bytes

    @inputtable{Cal_ID_0x00010E33.tex}
*/
#define VOICE_PARAM_TX_STREAM_LIMITER (0x00010E33)

/** @ingroup group cal_module_ids
    Module that identifies the Comfort Noise Generation algorithm in the
    voice stream on the Tx path.

    This module supports the #VOICE_PARAM_MOD_ENABLE parameter ID.
*/
#define VOICE_MODULE_ENC_CNG                (0x00010F13)
/** @endcond */

/** @addtogroup cal_param_ids
@{ */
/** @cond OEM_only */
/** ID of the Single-mic ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 92 bytes

    @note1hang Single-mic ECNS also supports a versioned command,
               #VOICE_PARAM_SMECNS_EXT.

    @inputtable{Cal_ID_0x00010E01.tex} @newpage
*/
#define VOICE_PARAM_SMECNS                 (0x00010E01)

/** ID of the SMECNS Preset parameter that contains preset coefficients for
    single-mic ECNS.

    The maximum array size for this parameter is:
    - Version 0 -- 1604 bytes

    @inputtable{Cal_ID_0x00010E02.tex}
*/
#define VOICE_PARAM_SMECNS_PRESET          (0x00010E02)

/** ID of the VP3 parameter, which contains VP3 data for all voice processing
    modules.

    The #VOICE_PARAM_VP3_SIZE parameter provides the size, which can be
    different for each software device ID (each device ID can correspond to a
    different topology ID for voice Tx processing).

    This parameter must be saved before destruction or reinitialization of the
    voice processing session, and it must be restored before the voice
    processing session is started.

    @inputtable{Cal_ID_0x00010E03.tex}
*/
#define VOICE_PARAM_VP3                    (0x00010E03)
/** @endcond */

/** @cond OEM_only */
/** ID of the Wide Voice algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 44 bytes

    @inputtable{Cal_ID_0x00010E04.tex}
*/
#define VOICE_PARAM_WV                     (0x00010E04)

/** ID of the Wide Voice V2 algorithm parameter, which supports all
    types of NB vocoders and WB vocoders running in NB mode of operation.

    The fixed size for this parameter is:
    - Version 0 -- 64 bytes

    @inputtable{Cal_ID_0x00010E42.tex}
*/
#define VOICE_PARAM_WV_V2                  (0x00010E42)

/** ID of the Slow Talk parameter for the voice activity detection and
    expansion algorithm.

    The fixed size for this parameter is:
    - Version 0 -- 60 bytes

    @inputtable{Cal_ID_0x00010E05.tex}
*/
#define VOICE_PARAM_ST                     (0x00010E05)

/** ID of the Slow Talk Expansion algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 4 bytes

    @inputtable{Cal_ID_0x00010E16.tex} @newpage
*/
#define VOICE_PARAM_ST_EXP                 (0x00010E16)

/** ID of the AVC/RVE algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 148 bytes

    @inputtable{Cal_ID_0x00010E06.tex} @newpage
*/
#define VOICE_PARAM_AVC_RVE                (0x00010E06)

/** ID of the AVC/RVE V2 algorithm parameter, which upgrades the
    single-mic noise estimate method to the Minimum Statistics method.

    The fixed size for this parameter is:
    - Version 0 -- 164 bytes

    @inputtable{Cal_ID_0x00010E41.tex}
*/
#define VOICE_PARAM_AVC_RVE_V2                (0x00010E41)

/** ID of the parameter used to enable the AVC/RVE algorithms.

    The fixed size for this parameter is:
    - Version 0 -- 4 bytes

    @inputtable{Cal_ID_0x00010E15.tex}
*/
#define VOICE_PARAM_AVC_RVE_ENABLE         (0x00010E15)
/** @endcond */

/** @cond OEM_only */
/** ID of the PBE algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 56 bytes, followed by a variable size IIR filter structure

    The filter sizes are defined by configurable parameters. The maximum size
    for voice applications is 236 bytes. The filter order is assumed to be 3
    for high, low, and band-pass filters.

    @inputtable{Cal_ID_0x00010E07.tex}
*/
#define VOICE_PARAM_PBE                    (0x00010E07)

/** ID of the Multiband Adaptive Dynamic Range Control (MADRC) algorithm
    parameter.

    The fixed size for this parameter is:
    - Version 0 -- 12 bytes, followed by variable size DRC and FIR filter
      structures

    The filter sizes are defined by configurable parameters. The maximum size
    for voice applications is 472 bytes. For voice, the maximum number of
    bands is assumed to be 3.

    @inputtable{Cal_ID_0x00010E08.tex}
*/
#define VOICE_PARAM_MBDRC                  (0x00010E08)

/** ID of the IIR Tuning Filter algorithm parameter for voice.

    The fixed size for this parameter is:
    - Version 0 -- 2 bytes, followed by variable-sized IIR filter structures

    The filter sizes are defined by configurable parameters. The maximum size
    for voice applications is 224 bytes. For voice, the maximum number of
    filter stages is assumed to be 10. If the number of stages is an odd
    number, two bytes of padding must be added at the end of the payload.

    @inputtable{Cal_ID_0x00010E09.tex}
*/
#define VOICE_PARAM_IIR                    (0x00010E09)
/** @endcond */

/** @cond OEM_only */
/** ID of the FIR tuning filter algorithm parameter for voice.

    This parameter contains a field that indicates the number of filter taps,
    followed by an FIR filter coefficient structure. The supported Q-factor is
    Q14.

    The maximum number of FIR taps for voice applications is 128 taps.
    The maximum size for this parameter is:
    - Version 0 -- 260 bytes

    @inputtable{Cal_ID_0x00010E0A.tex} @newpage
*/
#define VOICE_PARAM_FIR                    (0x00010E0A)

/** ID of the FNS algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 76 bytes

    @inputtable{Cal_ID_0x00010E0B.tex}
*/
#define VOICE_PARAM_FNS                    (0x00010E0B)

/** ID of the FNS V2 algorithm parameter, which incorporates a comfort
    noise injection module.

    The maximum array size for this parameter is:
    - Version 0 -- 84 bytes

    @inputtable{Cal_ID_0x00010E43.tex}
*/
#define VOICE_PARAM_FNS_V2                    (0x00010E43)
/** @endcond */
/** @} */ /* end_addtogroup cal_param_ids */

/** @cond OEM_only */
/** @ingroup cal_module_ids
    Module that identifies the Time Warp algorithm in the voice postprocessor
    on the Rx path.

    This module supports the #VOICE_PARAM_MOD_ENABLE parameter ID.
*/
#define VOICE_MODULE_TIMEWARP        (0x00010F0B)
/** @endcond */

/** @addtogroup cal_param_ids
@{ */
/** @cond OEM_only */
/** ID of the DTMF Detection algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 36 bytes

    @inputtable{Cal_ID_0x00010E0C.tex} @newpage
*/
#define VOICE_PARAM_DTMF_DETECTION         (0x00010E0C)

/** ID of the Echo Canceller Rx algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 20 bytes

    @inputtable{Cal_ID_0x00010E0D.tex}
*/
#define VOICE_PARAM_ECRX                   (0x00010E0D)

/** ID of the Dynamic Range Control (DRC) algorithm parameter.

    The fixed size for this parameter is:
    - Version 0 -- 56 bytes

    @inputtable{Cal_ID_0x00010E0E.tex}
*/
#define VOICE_PARAM_DRC                    (0x00010E0E)

/** ID of the Dual-mic ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 448 bytes

    @inputtable{Cal_ID_0x00010E11.tex}
*/
#define VOICE_PARAM_DMECNS                 (0x00010E11)

/** ID of the Fluence Dual-mic and Tri-mic ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 468 bytes

    @inputtable{Cal_ID_0x00010E20.tex}
*/
#define VOICE_PARAM_FLECNS                 (0x00010E20)
/** @endcond */

/** @cond OEM_only */
/** ID of the Fluence Dual-mic and Tri-mic ECNS with versioning parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 92 bytes

    @inputtable{Cal_ID_0x00010E1F.tex}
*/
#define VOICE_PARAM_FLECNS_EXT               (0x00010E1F)

/** ID of the Fluence Pro (quad-mic) and Fluence V5 (single and dual mic) ECNS
    parameter.

    The maximum array size for this parameter is:
     - Version 0 -- 904 bytes
     - Version 1 -- 908 bytes
     - Version 2 -- 920 bytes
     - Version 3 -- 932 bytes
     - Version 4 -- 976 bytes 

      @inputtable{Cal_ID_0x00010E1C.tex}

    For version 1, the parameter is extended as follows.

      @inputtable{Cal_ID_0x00010E1C_V1_ext.tex}

    For version 2, the parameter is extended as follows.

      @inputtable{Cal_ID_0x00010E1C_V2_ext.tex}

    For version 3, the parameter is extended as follows.

      @inputtable{Cal_ID_0x00010E1C_V3_ext.tex}

    For version 4, the parameter is extended as follows.
  
      @inputtable{Cal_ID_0x00010E1C_V4_ext.tex}
*/
#define VOICE_PARAM_FPECNS                 (0x00010E1C)
/** @endcond */

/** @cond OEM_only */
/** ID of the Fluence V5 ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 904 bytes
    - Version 1 -- 908 bytes
    - Version 2 -- 912 bytes
    - Version 3 -- 1108 bytes
    - Version 4 -- 5380 bytes

      @inputtable{Cal_ID_0x00010E26.tex}

    For version 1, the parameter is extended as follows.

      @inputtable{Cal_ID_0x00010E26_V1_ext.tex}

    @keep{8} For version 2, the parameter is extended as follows.

      @inputtable{Cal_ID_0x00010E26_V2_ext.tex}

    For version 3, the parameter is extended as follows:

      @inputtable{Cal_ID_0x00010E26_V3_ext.tex}

    For version 4, the parameter is extended as follows:

      @inputtable{Cal_ID_0x00010E26_V4_ext.tex}
*/
#define VOICE_PARAM_FV5ECNS                (0x00010E26)

/** ID of the Fluence V5 Broadside and Pro V2 ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 716 bytes

    @inputtable{Cal_ID_0x00010E35.tex}
*/
#define VOICE_PARAM_FLUENCE_EC                (0x00010E35)
/** @endcond */

/** @cond OEM_only */
/** ID of the Fluence V5 Broadside and Pro V2 ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 1064 bytes

    @inputtable{Cal_ID_0x00010E36.tex}
*/
#define VOICE_PARAM_FLUENCE_NS_SPK            (0x00010E36)

/** ID of the Single-mic ECNS with versioning parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 96 bytes
    - Version 1 -- 112 bytes

    @inputtable{Cal_ID_0x00010E27.tex}

    For version 1, the parameter is extended as follows.

    @inputtable{Cal_ID_0x00010E27_V1_ext.tex} @newpage
*/
#define VOICE_PARAM_SMECNS_EXT			   (0x00010E27)

/** ID of the read-only parameter structure for Fluence dual-mic and Fluence
    ANC (tri-mic) ECNS.

    The maximum array size for this parameter is:
    - Version 0 -- 240 bytes

    @inputtable{Cal_ID_0x00010E1D.tex} @newpage
*/
#define VOICE_PARAM_FL_STATE               (0x00010E1D)

/** ID of the read-only parameter structure for internal status monitoring of
    Fluence Pro/V5 single-mic, dual-mic, and quad-mic ECNS.

    The maximum array size for this parameter is:
    - Version 0 -- 860 bytes

    @inputtable{Cal_ID_0x00010E30.tex} @newpage
*/
#define VOICE_PARAM_FP_STATE               (0x00010E30)
/** @endcond */

/** @cond OEM_only */
/** ID of the read-only parameter structure for internal status monitoring of
    Fluence V5 single-mic, dual-mic ECNS.

    The maximum array size for this parameter is:
    - Version 0 -- 116 bytes
    - Version 1 -- 180 bytes 

    @inputtable{Cal_ID_0x00010E31.tex} @newpage

    For version 1, the parameter is extended as follows.

    @inputtable{Cal_ID_0x00010E31_V1_ext.tex}
*/
#define VOICE_PARAM_FV5_STATE              (0x00010E31)

/** ID of the read-only parameter structure for Fluence V5 spatial filter
    coefficients (internal status monitoring of single-mic and dual-mic
    ECNS).

    The maximum array size for this parameter is:
    - Version 0 -- 4100 bytes

    @inputtable{Cal_ID_0x00010E2D.tex} @newpage
*/
#define VOICE_PARAM_FV5_SPF_COEFF              (0x00010E2D)

/** For the Fluence V5 Dual-Mic Broadside and Fluence Pro v2 Quad-Mic
    Speakerphone modes, ID of the read-only parameter structure for the noise
    suppressor's internal status monitoring.

    The maximum array size for this parameter is:
    - Version 0 -- 980 bytes

    @inputtable{Cal_ID_0x00010E40.tex} @newpage
*/
#define VOICE_PARAM_FLUENCE_NS_SPK_STATE    (0x00010E40)
/** @endcond */

/** @cond OEM_only */
/** ID of the parameter for Fixed Echo Path Delay in the firmware. The delay
    is in multiples of 8 kHz samples.

    The maximum array size for this parameter is:
    - Version 0 -- 4 bytes

    @inputtable{Cal_ID_0x00010E1E.tex}
*/
#define VOICE_PARAM_ECHO_PATH_DELAY        (0x00010E1E)
/** @endcond */

/** ID of the Volume Control algorithm parameter on the Tx and Rx paths.
    The fixed size for this parameter is:

    - Version 0 -- 4 bytes

    @inputtable{Cal_ID_0x00010E12.tex}
*/
#define VOICE_PARAM_VOL                    (0x00010E12)

/** @cond OEM_only */
/** ID of the Gain parameter.

The fixed size for this parameter is:
    - Version 0 -- 4 bytes

    @inputtable{Cal_ID_0x00010E13.tex}
*/
#define VOICE_PARAM_GAIN                   (0x00010E13)

/** ID of the Adaptive Input Gain (AIG) algorithm parameter on the Tx and Rx
    paths.

    The fixed size for this parameter is:
    - Version 0 -- 36 bytes

    @inputtable{Cal_ID_0x00010E17.tex}
*/
#define VOICE_PARAM_AIG                    (0x00010E17)
/** @endcond */

/** @cond OEM_only */
/** ID of the read-only parameter used to return the Adaptive Filter (AF)
    coefficients of the currently configured echo canceller.

    @inputtable{Cal_ID_0x00010E19.tex}

    AFCoeffData is defined in the following topology AF data structure tables
    and is based on the voice processing topology. The structure length is
    variable based on the number of taps used by the module at the time of the
    query.

    @subhead{AF data structure for the VPM\_TX\_SM\_ECNS topology}
    @inputtable{Cal_ID_0x00010E19_topo_VPM_TX_SM_ECNS.tex} @newpage

    @subhead{AF data structure for the VPM\_TX\_DM\_FLUENCE topology}
    @inputtable{Cal_ID_0x00010E19_topo_VPM_TX_DM_FLUENCE.tex} @vertspace{-6}

    @subhead{AF data structure for the VPM\_TX\_TM\_FLUENCE topology}
    @inputtable{Cal_ID_0x00010E19_topo_VPM_TX_TM_FLUENCE.tex} @vertspace{-6}

    @subhead{AF data structure for the VPM\_TX\_QM\_FLUENCE\_PRO\,
    VPM\_TX\_SM\_FLUENCEV5\, and VPM\_TX\_DM\_FLUENCEV5 topologies}
    @inputtable{Cal_ID_0x00010E19_topo_VPM_TX_QM_FLUENCE_pro.tex} @newpage

    For the VPM_TX_QM_FLUENCE_PRO, VPM_TX_DM_FLUENCEV5, VPM_TX_SM_FLUENCEV5,
    VPM_TX_QM_FLUENCE_PROV2, and VPM_TX_DM_FLUENCEV5_BROADSIDE
    topologies, each AecPathStruct is defined by the following variable length
    payload. AFLen need not be the same across all AecPaths.

    The total number of taps over all filters for both Fg and Bg arrays must
    not exceed 2000. Fg and Bg filters for a particular filter index i use the
    same length AFLen[i]. This means the sum of AFLen[i] over i from 0 to
    (NumAfFilter-1) must not exceed (2000 / 2) = 1000. The maximum size is
    4024&nbsp;bytes.

    BASE represents the byte offset of the current AecPath i, which has filter
    length AFLen[i]. The next AecPathStruct for index (i+1) starts at offset
    BASE+4+4*AFLen[i].

    @subhead{AecPathStruct variable length payload}
    @inputtable{Cal_ID_0x00010E19_topo_VPM_TX_QM_FLUENCE_PRO_payload.tex}
    @vertspace{-6}

    @subhead{Maximum size of VOICE\_PARAM\_AF\_COEFFS}
    The memory allocated to get the AF coefficents must be large enough to
    accommodate the maximum size of the VOICE_PARAM_AF_COEFFS structure. The
    maximum size depends on the maximum number of AF taps allowed for the
    current topology configuration.

    The following table lists the maximum size according to topology.

    @inputtable{Cal_ID_0x00010E19_maximum_size.tex} @newpage
*/
#define VOICE_PARAM_AF_COEFFS              (0x00010E19)

/** ID of the read-only parameter used to read the size of VP3 data. This
    parameter is a multiple of 4 bytes, which is defined by the voice
    processor Tx to maintain parameter alignment.

    @inputtable{Cal_ID_0x00010E1A.tex}
*/
#define VOICE_PARAM_VP3_SIZE               (0x00010E1A)

/** @endcond */

/** ID of the Soft-stepping Volume Control algorithm parameter on Tx and Rx
    paths. This parameter is used to change the volume linearly over ramp
    duration.

    This is a read-only parameter with a total size of:
    - Version 0 -- 8 bytes

    @inputtable{Cal_ID_0x00010E21.tex}
*/
#define VOICE_PARAM_SOFT_VOL               (0x00010E21)

/** @cond OEM_only */
/** ID of the Voice Plus Dual-mic ECNS parameter.

    The maximum array size for this parameter is:
    - Version 0 -- 80 bytes

    @inputtable{Cal_ID_0x00010E34.tex}
*/
#define VOICE_PARAM_VPECNS                 (0x00010E34)
/** @endcond */

/** @} */ /* end_addtogroup cal_param_ids */

/** @addtogroup cal_module_ids
@{ */
/** @cond OEM_only */
/** Module that identifies Single-mic ECNS in the voice processor on the
    Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_SMECNS (supported only for backward compatibility)
    - #VOICE_PARAM_SMECNS_PRESET
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_FNS
    - #VOICE_PARAM_SMECNS_EXT @newpage
*/
#define VOICE_MODULE_SMECNS                (0x00010EE0)

/** Module that identifies Dual-mic ECNS in the voice processor on the
    Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_DMECNS (supported only for backward compatability)
    - #VOICE_PARAM_FLECNS
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_FL_STATE
    - #VOICE_PARAM_FLECNS_EXT
*/
#define VOICE_MODULE_DMECNS                (0x00010EE1)

/** Module that identifies Tri-mic Fluence ECNS in the voice processor on the
    Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FLECNS
    - #VOICE_PARAM_AF_COEFFS
*/
#define VOICE_MODULE_TMECNS                (0x00010F02)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies Fluence Pro Quad-mic ECNS in the voice processor on
    the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FPECNS
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_ECHO_PATH_DELAY
*/
#define VOICE_MODULE_FPECNS_QM             (0x00010F08)

/** Module that identifies Fluence Pro V2 Quad-mic ECNS in the voice
    processor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_ECHO_PATH_DELAY
    - #VOICE_PARAM_FLUENCE_EC
    - #VOICE_PARAM_FLUENCE_NS_SPK
    - #VOICE_PARAM_FP_STATE
    - #VOICE_PARAM_FLUENCE_NS_SPK_STATE @newpage
*/
#define VOICE_MODULE_FLUENCE_PROV2 (0x00010F17)

/** Module that identifies Dual-mic Fluence V5 ECNS in the voice processor on
    the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FPECNS
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_ECHO_PATH_DELAY
    - #VOICE_PARAM_FV5ECNS
    - #VOICE_PARAM_FP_STATE
    - #VOICE_PARAM_FV5_STATE
    - #VOICE_PARAM_FV5_SPF_COEFF
*/
#define VOICE_MODULE_FV5ECNS_DM            (0x00010F0A)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies Dual-mic Fluence V5 Broadside ECNS in the voice
    processor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_ECHO_PATH_DELAY
    - #VOICE_PARAM_FLUENCE_EC
    - #VOICE_PARAM_FLUENCE_NS_SPK
    - #VOICE_PARAM_FP_STATE
    - #VOICE_PARAM_FLUENCE_NS_SPK_STATE
*/
#define VOICE_MODULE_FLUENCEV5_BROADSIDE (0x00010F18)

/** Module that identifies Single-mic Fluence V5 ECNS in the voice processor
    on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FPECNS
    - #VOICE_PARAM_AF_COEFFS
    - #VOICE_PARAM_ECHO_PATH_DELAY
    - #VOICE_PARAM_FV5ECNS
    - #VOICE_PARAM_FP_STATE
    - #VOICE_PARAM_FV5_STATE
    - #VOICE_PARAM_FV5_SPF_COEFF @newpage
*/
#define VOICE_MODULE_FV5ECNS_SM            (0x00010F09)

/** Module that identifies the Wide Voice algorithm in the voice decoder
    postprocessor.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_WV
*/
#define VOICE_MODULE_WV                    (0x00010EE2)

/** Module that identifies the Wide Voice V2 algorithm in the voice decoder
    postprocessor.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_WV_V2
*/
#define VOICE_MODULE_WV_V2                 (0x00010F1A)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies the Slow Talk algorithm in the voice decoder
    postprocessor.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_ST
    - #VOICE_PARAM_ST_EXP
*/
#define VOICE_MODULE_ST                    (0x00010EE3)

/** Module that identifies the AVC/RVE algorithm in the voice preprocessor on
    the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_AVC_RVE_ENABLE
    - #VOICE_PARAM_AVC_RVE
*/
#define VOICE_MODULE_TX_AVC                (0x00010EE4)

/** Module that identifies the PBE algorithm in the voice processor on the
    Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_PBE
*/
#define VOICE_MODULE_PBE                   (0x00010EE5)

/** Module that identifies the Multiband Dynamic Range Control (MDRC)
    algorithm in the voice processor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_MBDRC
*/
#define VOICE_MODULE_MBDRC                 (0x00010EE6)

/** Module that identifies the IIR algorithm in the voice processor on the
    Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_TX_IIR                (0x00010EE7)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies the IIR algorithm in the voice processor on the
    Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_RX_IIR                (0x00010EE8)

/** Module that identifies the FIR algorithm in the voice processor on the
    Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FIR
 */
#define VOICE_MODULE_TX_FIR                (0x00010EE9)

/** Module that identifies the FIR algorithm in the voice processor on the
    Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FIR
*/
#define VOICE_MODULE_RX_FIR                (0x00010EEA)

/** Module that identifies the FNS algorithm in the voice postprocessor on the
    Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_FNS
*/
#define VOICE_MODULE_FNS                   (0x00010EEB)

/** Module that identifies the DTMF detection algorithm in the voice
    postprocessor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_DTMF_DETECTION
*/
#define VOICE_MODULE_DTMF_DETECTION        (0x00010EEC)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies the DTMF detection algorithm in the voice
    postprocessor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_DTMF_DETECTION
*/
#define VOICE_MODULE_TX_DTMF_DETECTION     (0x00010F01)

/** Module that identifies the echo canceller Rx algorithm in the voice
    postprocessor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_ECRX
*/
#define VOICE_MODULE_RX_EC                 (0x00010EED)

/** Module that identifies the IIR algorithm in the voice processor on the
    Tx mic1 input path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_IIR_MIC1              (0x00010EF0)

/** Module that identifies the IIR algorithm in the voice processor on the
    Tx mic2 input path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_IIR_MIC2              (0x00010EF1)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies the IIR algorithm in the voice processor on the
    Tx mic3 input path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_IIR_MIC3              (0x00010F03)

/** Module that identifies the IIR algorithm in the voice processor on the
    Tx mic4 input path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_IIR_MIC4              (0x00010F04)

/** Module that identifies the Dynamic Range Control algorithm in the voice
    preprocessor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_DRC
*/
#define VOICE_MODULE_RX_DRC                (0x00010EF2)

/** Module that identifies the Dynamic Range Control algorithm in the voice
    preprocessor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_DRC
*/
#define VOICE_MODULE_TX_DRC                (0x00010EF3)
/** @endcond */

/** Module that identifies the Volume Control algorithm in the voice
    preprocessor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_VOL
    - #VOICE_PARAM_SOFT_VOL
*/
#define VOICE_MODULE_TX_VOL                (0x00010EF4)

/** Module that identifies the Volume Control algorithm in the voice
    preprocessor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_VOL
    - #VOICE_PARAM_SOFT_VOL
*/
#define VOICE_MODULE_RX_VOL                (0x00010EF5)

/** Module that identifies supported generic parameters that are not tied to
    a specific algorithm module in the voice preprocessor on the Tx path.
    This module ID is also used as the default identifier for the host PCM.

  @if OEM_only
    This module supports the following parameter IDs:
    - #VOICE_PARAM_VP3
    - #VOICE_PARAM_VP3_SIZE (read only)
  @endif
*/
#define VOICEPROC_MODULE_TX          (0x00010EF6)

/** Module that identifies supported generic parameters that are not tied to
    a specific algorithm module in the voice preprocessor on the Rx path.
    This module ID is also used as the default identifier for the host PCM.
*/
#define VOICEPROC_MODULE_RX          (0x00010F06)

/** Module that identifies supported generic parameters that are not tied to
    a specific algorithm module in the voice Tx stream.
*/
#define VOICESTREAM_MODULE_TX              (0x00010F07)

/** Module that identifies supported generic parameters that are not tied to
    an algorithm module in the voice Rx stream.
*/
#define VOICESTREAM_MODULE_RX              (0x00010F14)

/** Module that identifies the Voice Mic Gain in the voice preprocessor on
    the Tx path.

  @if OEM_only
    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_GAIN
  @endif
  @if ISV_only
    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
  @endif
*/
#define VOICE_MODULE_TX_MIC_GAIN           (0x00010EF7)

/** Module that identifies the voice encoder gain in the voice preprocessor on
    the Tx path.

  @if OEM_only
    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_GAIN
  @endif
  @if ISV_only
    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
  @endif
*/
#define VOICE_MODULE_TX_ENC_GAIN           (0x00010EF8)

/** Module that identifies the Voice Speaker Gain in the voice preprocessor on
    the Tx path.

  @if OEM_only
    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_GAIN
  @endif
  @if ISV_only
    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
  @endif
*/
#define VOICE_MODULE_RX_SPKR_GAIN          (0x00010EF9)

/** Module that identifies the Voice Decoder Gain in the voice preprocessor on
    the Rx path.

    @if OEM_only
    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_GAIN
  @endif
  @if ISV_only
    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
  @endif
*/
#define VOICE_MODULE_RX_DEC_GAIN           (0x00010EFA)

/** @cond OEM_only */
/** Module that identifies the HPF 12 IIR algorithm in the voice processor on
    the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_TX_HPF                (0x00010F11)

/** Module that identifies the Fixed Elliptical Filter in the voice
    preprocessor on the Tx path.

    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
*/
#define VOICE_MODULE_TX_ELLIPTICAL_FILTER  (0x00010EFD)

/** Module that identifies the Fixed Slope Filter in the voice preprocessor on
    the Tx path.

    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
*/
#define VOICE_MODULE_TX_SLOPE_FILTER       (0x00010EFE)

/** Module that identifies the HPF 12 IIR algorithm in the voice processor on
    the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_IIR
*/
#define VOICE_MODULE_RX_HPF                (0x00010F12)

/** Module that identifies the Automatic Gain Control algorithm in the voice
    preprocessor on the Rx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_AIG
*/
#define VOICE_MODULE_RX_AIG                (0x00010EFF)
/** @endcond */

/** @cond OEM_only */
/** Module that identifies the Automatic Gain Control algorithm in the voice
    preprocessor on the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_AIG
*/
#define VOICE_MODULE_TX_AIG                (0x00010F00)

/** Module that identifies Dual-mic Voice Plus ECNS in the voice processor on
    the Tx path.

    This module supports the following parameter IDs:
    - #VOICE_PARAM_MOD_ENABLE
    - #VOICE_PARAM_VPECNS
*/
#define VOICE_MODULE_VPECNS                (0x00010F16)

/** Module that identifies the Blind Bandwidth extension for eAMR and AMR-NB
    vocoders on the Rx path.

    This module supports the following parameter ID:
    - #VOICE_PARAM_MOD_ENABLE
*/
#define VOICE_MODULE_BEAMR                    (0x00010F19)
/** @endcond */

/** @} */ /* end_addtogroup cal_module_ids */

#endif /* __ADSP_VPARAMS_API_H__ */
