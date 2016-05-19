/*========================================================================*/
/**
@file adsp_audproc_api.h

This file contains the structure definitions for Audio Post Processing
Topology IDs, Module IDs, Parameter IDs.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is maintained in the
      audio_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
Copyright (c) 2010-2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_audproc_api.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/10/14   sw      (Tech Pubs) Merged Doxygen comments from 2.4; edited
                    Doxygen comments/markup for 2.6.
09/06/13   sw      (Tech Pubs) Merged Doxygen comments/markup from 2.0; edited
                   new Doxygen comments for 2.2.
08/03/12   sw      (Tech Pubs) Edited Doxygen comments for 2.0 updates;
                   updated Doxygen markup to Dox 1.7.6.1.
02/08/12   sw      (Tech Pubs) Updated Doxygen comments based on 06.110 branch.
05/30/11   sw      (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
04/22/11    ss     Introducing Audproc API file that would hold all post processing
                   Module IDs, Parameter IDs and Topology IDs
========================================================================== */

#ifndef _ADSP_AUDPROC_API_H_
#define _ADSP_AUDPROC_API_H_

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*
 * Include file to add New PP topology and PP module. This file is present at adsp_proc\hap\integration\audproc
 * To include this file, set OEM_ROOT from command prompt
 */
#if defined(OEM_ROOT)
#include "custom_adsp_audproc_api.h"
#endif
/** @addtogroup audiopp_topos_asm
@{ */
/** ID of the default audio postprocessing stream topology.

  @if OEM_only
    @inputfig{1,topo_id_asm_0x00010BE4_postproc.png}

    - Downmixer                         (#AUDPROC_MODULE_ID_DOWNMIX)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA) @newpage
  @endif
  @if ISV_only
    @inputfig{1,topo_id_asm_0x00010BE4_postproc_subset.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
*/
#define ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT                         0x00010BE4

/** @cond OEM_only */
/** ID of the default postprocessing topology with peak meter.

    @inputfig{1,topo_id_asm_0x00010D83.png}

    - Downmixer                         (#AUDPROC_MODULE_ID_DOWNMIX)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Peak Meter                        (#AUDPROC_MODULE_ID_PEAK_METER)
*/
#define ASM_STREAM_POSTPROC_TOPO_ID_PEAKMETER                       0x00010D83
/** @endcond */

/** ID of the no-default audio postprocessing topology. The resampler
    is the only module present in this topology.

  @if OEM_only
    @inputfig{1,topo_id_asm_0x00010C68_postproc.png}

    - Downmixer                         (#AUDPROC_MODULE_ID_DOWNMIX)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
  @if ISV_only
    @inputfig{1,topo_id_asm_0x00010C68_postproc_subset.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL) @newpage
  @endif
*/
#define ASM_STREAM_POSTPROC_TOPO_ID_NONE                            0x00010C68

/** @cond OEM_only */
/** ID of the audo postprocessing topology with multichannel resampler, peak
    meter, and volume control.

    @inputfig{1,topo_id_asm_0x00010D8B.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Peak Meter                        (#AUDPROC_MODULE_ID_PEAK_METER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    @newpage
*/
#define ASM_STREAM_POSTPROC_TOPO_ID_MCH_PEAK_VOL                     0x00010D8B
/** @endcond */

/** ID of the default audio preprocessing stream topology.

  @if OEM_only
    @inputfig{1,topo_id_asm_0x00010BE4_preproc.png}

    - Downmixer                         (#AUDPROC_MODULE_ID_DOWNMIX)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
  @if ISV_only
    @inputfig{1,topo_id_asm_0x00010BE4_preproc_subset.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
*/
#define ASM_STREAM_PREPROC_TOPO_ID_DEFAULT   ASM_STREAM_POSTPROC_TOPO_ID_DEFAULT

/** ID of the no-default audio preprocessing topology. The resampler is
    the only module present in this topology.

  @if OEM_only
    @inputfig{1,topo_id_asm_0x00010C68_preproc.png}
    - Downmixer                         (#AUDPROC_MODULE_ID_DOWNMIX)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
  @if ISV_only
    @inputfig{1,topo_id_asm_0x00010C68_preproc_subset.png}
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
*/
#define ASM_STREAM_PREPROC_TOPO_ID_NONE      ASM_STREAM_POSTPROC_TOPO_ID_NONE

/** @cond OEM_only */
/** ID of the DTS audio postprocessing topology.

    @inputfig{1,topo_id_audproc_0x0001071F.png}

    - DTS Dynamic Range Control         (#AUDPROC_MODULE_ID_DTS_DRC)
    - DTS DialNorm                      (#AUDPROC_MODULE_ID_DTS_DIALNORM)
*/
#define AUDPROC_POPP_TOPOLOGY_ID_DTS_AUDIO   0x0001071F

/** @endcond */
/** @} */ /* end_addtogroup audiopp_topos_asm */

/** @addtogroup audiopp_topos_adm
@{ */
/** ID of the no-default COPP audio postprocessing device topology
    (indicates None).

    @inputfig{1,topo_id_adm_0x00010312.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_NONE_AUDIO_COPP              0x00010312

/** @cond OEM_only */
/** ID of SPEAKER_MONO in the COPP audio postprocessing device topology.

@inputfig{1,topo_id_adm_0x00010313.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
    @newpage
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MONO_AUDIO_COPP        0x00010313

/** ID of SPEAKER_STEREO in the COPP audio postprocessing device topology.

@inputfig{1,topo_id_adm_0x00010314.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_AUDIO_COPP      0x00010314

/** ID of SPEAKER_STEREO_IIR ID in the COPP audio postprocessing device
    topology.

@inputfig{1,topo_id_adm_0x00010704.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter Left       (#AUDPROC_MODULE_ID_LEFT_IIR_TUNING_FILTER)
    - IIR Tuning Filter Right      (#AUDPROC_MODULE_ID_RIGHT_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
     @newpage
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_IIR_AUDIO_COPP  0x00010704

/** ID of the COPP topology of SPEAKER_MONO for MBDRC Version 2.

@inputfig{1,topo_id_adm_0x0001070D.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRCV2)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MONO_AUDIO_COPP_MBDRCV2 0x0001070D

/** IID of the COPP topology of SPEAKER_STEREO for MBDRC Version 2.

@inputfig{1,topo_id_adm_0x0001070E.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRCV2)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
    @newpage
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_AUDIO_COPP_MBDRCV2 0x0001070E

/** ID of the COPP topology of STEREO_IIR for MBDRC Version 2.

@inputfig{1,topo_id_adm_0x0001070F.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter Left      (#AUDPROC_MODULE_ID_LEFT_IIR_TUNING_FILTER)
    - IIR Tuning Filter Right     (#AUDPROC_MODULE_ID_RIGHT_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRCV2)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_STEREO_IIR_AUDIO_COPP_MBDRCV2 0x0001070F

/** ID of the COPP topology with multichannel peak meter and volume control.

    @inputfig{1,topo_id_adm_0x0001031B.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Peak Meter                        (#AUDPROC_MODULE_ID_PEAK_METER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL) @newpage
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SPEAKER_MCH_PEAK_VOL          0x0001031B

/** ID of Tx MIC_MONO in the COPP audio postprocessing device topology.

@inputfig{1,topo_id_adm_0x00010315.png}

    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Tx Mic Gain                       (#AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL)
    - High Pass Filter                  (#AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER)
    - Enhanced Audio Noise Suppression  (#AUDPROC_MODULE_ID_EANS)
    - Tx IIR Tuning Filter              (#AUDPROC_MODULE_ID_TX_IIR_FILTER)
    - Adaptive Input Gain               (#AUDPROC_MODULE_ID_AIG)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_MIC_MONO_AUDIO_COPP           0x00010315

/** ID of Tx MIC_STEREO in the COPP audio postprocessing device topology.

@inputfig{1,topo_id_adm_0x00010316.png}

    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Tx Mic Gain                       (#AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL)
    - High Pass Filter                  (#AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER)
    - Enhanced Audio Noise Suppression  (#AUDPROC_MODULE_ID_EANS)
    - Tx IIR Tuning Filter              (#AUDPROC_MODULE_ID_TX_IIR_FILTER)
    - Adaptive Input Gain               (#AUDPROC_MODULE_ID_AIG)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER) @newpage
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_MIC_STEREO_AUDIO_COPP         0x00010316

/** ID of Tx Multichannel IIR in the COPP audio postprocessing
    device topology.

    @inputfig{1,topo_id_audproc_0x00010715.png}

    - Tx Multichannel IIR Tuning Filter
      (#AUDPROC_MODULE_ID_MCHAN_IIR_TUNING_FILTER)
*/
#define AUDPROC_COPP_TOPOLOGY_ID_MCHAN_IIR_AUDIO                    0x00010715
/** @endcond */

/** ID of the default COPP audio postprocessing device topology.

  @if OEM_only
    @inputfig{1,topo_id_adm_0x00010BE3.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
    @newpage
  @endif
  @if ISV_only
    @inputfig{1,topo_id_adm_0x00010BE3_subset.png}

    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
  @endif
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DEFAULT_AUDIO_COPP           0x00010BE3

/** @cond OEM_only */
/** ID of the default COPP open topology with peak meter.

    @inputfig{1,topo_id_adm_0x00010317.png}

    - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
    - Peak Meter                        (#AUDPROC_MODULE_ID_PEAK_METER)
    - Soft Volume Control               (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Equalizer                         (#AUDPROC_MODULE_ID_EQUALIZER)
    - Psychoacoustic Bass Enhancement   (#AUDPROC_MODULE_ID_PBE)
    - IIR Tuning Filter                 (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER)
    - Multiband Dynamic Range Control   (#AUDPROC_MODULE_ID_MBDRC)
    - Spectrum Analyzer                 (#AUDPROC_MODULE_ID_SPA)
    - Rx Codec Gain                     (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_PEAKMETER_AUDIO_COPP          0x00010317

/** ID of the default COPP open topology for compressed data.

    @inputfig{1,topo_id_audproc_0x0001076B.png}

    - Mute (compressed)            (#AUDPROC_MODULE_ID_COMPRESSED_MUTE)
    - Latency (compressed)         (#AUDPROC_MODULE_ID_COMPRESSED_LATENCY)
*/
#define AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT                      0x0001076B

/** ID of the topology containing no modules for compressed data. @newpage */
#define AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE                         0x00010774

/** @endcond */
/** @} */ /* end_addtogroup audiopp_topos_adm */

/** @cond OEM_only */
/** @addtogroup audiopp_module_aig
@{ */
/** ID of the audio Adaptive Input Gain (AIG) module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_AIG_ENABLE
    - #AUDPROC_PARAM_ID_AIG_CONFIG
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_AIG                         0x00010716

/** ID of the AIG Enable parameter used by AUDPROC_MODULE_ID_AIG.

    @msgpayload{Audio_AigEnable_t}
    @table{weak__audio__aigenable__t}
*/
#define AUDPROC_PARAM_ID_AIG_ENABLE                   0x00010717

/** @} */ /* end_addtogroup audiopp_module_aig */

/* Structure for enabling the configuration parameter for
    AUDIO AIG enable. */
typedef struct Audio_AigEnable_t Audio_AigEnable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audio_aigenable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_AIG_ENABLE parameter in the AIG
 module.
*/
struct Audio_AigEnable_t
{

    uint32_t                  enable;
    /**< Specifies whether AIG is enabled.

         @values
         - 0 -- Disable (Default)
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audio_aigenable_t */

/** @ingroup audiopp_module_aig
    ID of the AIG Tunable parameters used by AUDPROC_MODULE_ID_AIG.

    @msgpayload{Audio_AigParam_t}
    @table{weak__audio__aigparam__t}
*/
#define AUDPROC_PARAM_ID_AIG_CONFIG                   0x00010718

/* Structure for Audio Aig configuration parameters */
typedef struct Audio_AigParam_t Audio_AigParam_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audio_aigparam_t
@{ */
/* Payload of the AUDIO_PARAM_AIG parameters in the AIG module.
*/
struct Audio_AigParam_t
{

    uint16_t                           mode;
    /**< Mode word for enabling AIG/SIG mode .

         @values
         - 0 -- Static Input Gain (SIG)
         - 1 -- Adaptive Input Gain (AIG)

         Byte offset: 0 */

    int16_t                           staticGainL16Q12;
    /**< Static input gain when the mode field is set to 1.

         Byte offset: 2 */

    int16_t                           initialGainDBL16Q7;
    /**< Initial value from which the adaptive gain update starts (decibels in
         Q7 format).

         Byte offset: 4 */

    int16_t                           idealRMSDBL16Q7;
    /**< Average RMS level that the AIG tries to achieve (in Q8.7 format).

         Byte offset: 6 */

    int32_t                           noiseGateL32;
    /**< Threshold below which a signal is considered as noise and AIG is not
         applied.

         Byte offset: 8 */

    int32_t                           minGainL32Q15;
    /**< Minimum gain that can be provided by the AIG (in Q16.15 format).

         Byte offset: 12 */

    int32_t                           maxGainL32Q15;
    /**< Maximum gain that can be provided by the AIG (in Q16.15 format).

         Byte offset: 16 */

    uint32_t                          gainAtRtUL32Q31;
    /**< Attack/release time for the AIG update (in Q1.31 format).

         Byte offset: 20 */

    uint32_t                          longGainAtRtUL32Q31;
    /**< Long attack/release time while updating gain for noise/silence
         (in Q1.31 format).

         Byte offset: 24 */

    uint32_t                          rmsTavUL32Q32;
    /**< RMS smoothing time constant used for long-term RMS estimate (in
         Q0.32 format).

         Byte offset: 28 */

    uint32_t                          gainUpdateStartTimMsUL32Q0;
    /**< Waiting time before which the AIG applies the adaptive gain update
         (in Q32.0 format).

         Byte offset: 32 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audio_aigparam_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_eans
@{ */
/** ID of the Enhanced Audio Noise Suppression (EANS) I module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_EANS_ENABLE
    - #AUDPROC_PARAM_ID_EANS_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_EANS                            0x00010C4A

/** ID of the EANS Enable parameter used by AUDPROC_MODULE_ID_EANS.

    @msgpayload{audproc_eans_enable_t}
    @table{weak__audproc__eans__enable__t}
*/
#define AUDPROC_PARAM_ID_EANS_ENABLE                      0x00010C4B

/** ID of the EANS Configuration parameters used by AUDPROC_MODULE_ID_EANS.

    @msgpayload{audproc_eans_params_t}
    @table{weak__audproc__eans__params__t} @newpage
*/
#define AUDPROC_PARAM_ID_EANS_PARAMS                      0x00010C4C

/** @} */ /* end_addtogroup audiopp_module_eans */

/* Structure for enabling the configuration parameter for
    spectrum analyzer enable. */
typedef struct audproc_eans_enable_t audproc_eans_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eans_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EANS_ENABLE parameter in the EANS module.
*/
struct audproc_eans_enable_t
{

    uint32_t                  enable_flag;
    /**< Specifies whether EANS is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable 

         This is supported only for sampling rates of 8, 12, 16, 24, 32, and
         48&nbsp;kHz. It is not supported for sampling rates of 11.025, 22.05,
         or 44.1&nbsp;kHz. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eans_enable_t */

/* Structure for EANS configuration parameters. */
typedef struct audproc_eans_params_t audproc_eans_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eans_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EANS_ENABLE parameters in the EANS module.
*/
struct audproc_eans_params_t
{
    int16_t                         eans_mode;
    /**< Mode word for enabling/disabling submodules.

         Byte offset: 0 */

    int16_t                         eans_input_gain;
    /**< Input gain to the EANS module (in Q2.13 format).

         Byte offset: 2 */

    int16_t                         eans_output_gain;
    /**< Output gain to the EANS module (in Q2.13 format).

         Byte offset: 4 */

    int16_t                         eans_target_ns;
    /**< Target noise suppression level in dB.

         Byte offset: 6 */

    int16_t                         eans_s_alpha;
    /**< Over-subtraction factor for stationary noise suppression (in Q3.12
         format).

         Byte offset: 8 */

    int16_t                         eans_n_alpha;
    /**< Over-subtraction factor for nonstationary noise suppression (in Q3.12
         format).

         Byte offset: 10 */

    int16_t                         eans_n_alphamax;
    /**< Maximum over-subtraction factor for nonstationary noise suppression
         (in Q3.12 format).

         Byte offset: 12 */

    int16_t                         eans_e_alpha;
    /**< Scaling factor for excess noise suppression (in Q15 format).

         Byte offset: 14 */

    int16_t                         eans_ns_snrmax;
    /**< Upper boundary in dB for SNR estimation.

         Byte offset: 16 */

    int16_t                         eans_sns_block;
    /**< Quarter block size for stationary noise suppression.

         Byte offset: 18  */

    int16_t                         eans_ns_i;
    /**< Initialization block size for noise suppression.

         Byte offset: 20 */

    int16_t                         eans_np_scale;
    /**< Power scale factor for nonstationary noise update.

         Byte offset: 22 */

    int16_t                         eans_n_lambda;
    /**< Smoothing factor for higher level nonstationary noise update.

         Byte offset: 24 */

    int16_t                         eans_n_lambdaf;
    /**< Medium averaging factor for noise update.

         Byte offset: 26 */

    int16_t                         eans_gs_bias;
    /**< Bias factor in dB for gain calculation.

         Byte offset: 28 */

    int16_t                         eans_gs_max;
    /**< SNR lower boundary in dB for aggressive gain calculation.

         Byte offset: 30 */

    int16_t                         eans_s_alpha_hb;
    /**< Over-subtraction factor for high-band stationary noise suppression
         (in Q3.12 format).

         Byte offset: 32 */

    int16_t                         eans_n_alphamax_hb;
    /**< Maximum over-subtraction factor for high-band nonstationary noise
         suppression (in Q3.12 format).

         Byte offset: 34 */

    int16_t                         eans_e_alpha_hb;
    /**< Scaling factor for high-band excess noise suppression (in Q15 format).

         Byte offset: 36 */

    int16_t                         eans_n_lambda0;
    /**< Smoothing factor for nonstationary noise update during speech activity.

         Byte offset: 38 */

    int16_t                         thresh;
    /**< Threshold for generating a binary VAD decision.

         Byte offset: 40 */

    int16_t                         pwr_scale;
    /**< Indirect lower boundary of the noise level estimate.

         Byte offset: 42 */

    int16_t                         hangover_max;
    /**< Avoids mid-speech clipping and reliably detects weak speech bursts at
         the end of speech activity.

         Byte offset: 44 */

    int16_t                         alpha_snr;
    /**< Controls responsiveness of the VAD.

         Byte offset: 46 */

    int16_t                         snr_diff_max;
    /**< Maximum SNR difference.

         Decreasing this parameter value can help in making correct decisions
         during abrupt changes; however, decreasing too much might increase
         false alarms during long pauses/silences.

         Byte offset: 48 */

    int16_t                         snr_diff_min;
    /**< Minimum SNR difference.

         Decreasing this parameter value can help in making correct decisions
         during abrupt changes; however, decreasing too much might increase
         false alarms during long pauses/silences.

         Byte offset: 50 */

    int16_t                         init_length;
    /**< Defines the number of frames for which a noise level estimate is set
         to a fixed value.

         Byte offset: 52 */

    int16_t                         max_val;
    /**< Defines the upper limit of the noise level.

         Byte offset: 54 */

    int16_t                         init_bound;
    /**< Defines the initial bounding value for the noise level estimate. This
         is used during the initial segment defined by the init_length
         parameter.

         Byte offset: 56 */

    int16_t                         reset_bound;
    /**< Reset boundary for noise tracking.

         Byte offset: 58  */

    int16_t                         avar_scale;
    /**< Defines the bias factor in noise estimation.

         Byte offset: 60 */

    int16_t                         sub_nc;
    /**< Defines the window length for noise estimation.

         Byte offset: 62 */

    int16_t                         spow_min;
    /**< Defines the minimum signal power required to update the boundaries
         for the noise floor estimate.

         Byte offset: 64 */

    int16_t                         eans_gs_fast;
    /**< Fast smoothing factor for postprocessor gain.

         Byte offset: 66 */

    int16_t                         eans_gs_med;
    /**< Medium smoothing factor for postprocessor gain.

         Byte offset: 68 */

    int16_t                         eans_gs_slow;
    /**< Slow smoothing factor for postprocessor gain.

         Byte offset: 70 */

    int16_t                         eans_swb_salpha;
    /**< Super wideband aggressiveness factor for stationary noise suppression
         (in Q3.12 format).

         Byte offset: 72 */

    int16_t                         eans_swb_nalpha;
    /**< Super wideband aggressiveness factor for nonstationary noise
         suppression (in Q3.12 format).

         Byte offset: 74 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eans_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_tx_mic_gain
@{ */
/** ID of the Tx Mic Gain Control module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_TX_MIC_GAIN
    - #AUDPROC_PARAM_ID_ENABLE
   */
#define AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL                          0x00010C35

/** ID of the Tx Mic Gain Control parameter used by
    AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL.

    @msgpayload{audproc_tx_mic_gain_t}
    @table{weak__audproc__tx__mic__gain__t}
*/
#define AUDPROC_PARAM_ID_TX_MIC_GAIN                                0x00010C36

/** @} */ /* end_addtogroup audiopp_module_tx_mic_gain */

/* Structure for a Tx mic gain parameter for the mic gain
    control module. */
typedef struct audproc_tx_mic_gain_t audproc_tx_mic_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_tx_mic_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_TX_MIC_GAIN parameter in the
    Tx Mic Gain Control module.
*/
struct audproc_tx_mic_gain_t
{
    uint16_t                  tx_mic_gain;
    /**< Linear gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_tx_mic_gain_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_rx_codec_gain
@{ */
/** ID of the Rx Codec Gain Control module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_RX_CODEC_GAIN
    - #AUDPROC_PARAM_ID_ENABLE
    */
#define AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL                        0x00010C37

/** ID of the Rx Codec Gain Control parameter used by
    AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL.

    @msgpayload{audproc_rx_codec_gain_t}
    @table{weak__audproc__rx__codec__gain__t}
*/
#define AUDPROC_PARAM_ID_RX_CODEC_GAIN                              0x00010C38

/** @} */ /* end_addtogroup audiopp_module_rx_codec_gain */

/* Structure for the Rx common codec gain control module. */
typedef struct audproc_rx_codec_gain_t audproc_rx_codec_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_rx_codec_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_RX_CODEC_GAIN parameter in the
    Rx Codec Gain Control module.
*/
struct audproc_rx_codec_gain_t
{
    uint16_t                  rx_codec_gain;
    /**< Linear gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_rx_codec_gain_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_tx_hpf_iir_tun_filter
@{ */
/** ID of the HPF IIR Tuning Filter module on the Tx path.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_ENABLE_CONFIG
    - #AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_PRE_GAIN
    - #AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_CONFIG_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER                         0x00010C3D

/** ID of the Tx HPF IIR Filter Enable parameter used by
    AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER.

    @msgpayload{audproc_hpf_tx_iir_filter_enable_cfg_t}
    @table{weak__audproc__hpf__tx__iir__filter__enable__cfg__t}
*/
#define AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_ENABLE_CONFIG            0x00010C3E

/** ID of the Tx HPF IIR Filter Pregain parameter used by
    AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER.

    @msgpayload{audproc_hpf_tx_iir_filter_pre_gain_t}
    @table{weak__audproc__hpf__tx__iir__filter__pre__gain__t} @newpage
*/
#define AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_PRE_GAIN                 0x00010C3F

/** ID of the Tx HPF IIR Filter Configuration parameters used by
    #AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER.

    @msgpayload{audproc_hpf_tx_iir_filter_cfg_params_t}
    @table{weak__audproc__hpf__tx__iir__filter__cfg__params__t}
    This structure is followed by the HPF IIR filter coefficients
    on the Tx path as follows:
    - Sequence of int32 ulFilterCoeffs -- Each band has five coefficients, each
      in int32 format in the order of b0, b1, b2, a1, a2.
    - Sequence of int16 sNumShiftFactor -- One int16 per band. The numerator
      shift factor is related to the Q factor of the filter coefficients.
    - Sequence of uint16 usPanSetting -- One uint16 for each band to indicate
      if the filter is applied to left (0), center (1), and right (2) channels.
*/
#define AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_CONFIG_PARAMS            0x00010C40

/** @} */ /* end_addtogroup audiopp_module_tx_hpf_iir_tun_filter */

/* Structure for enabling a configuration parameter for
    the HPF IIR tuning filter module on the Tx path. */
typedef struct audproc_hpf_tx_iir_filter_enable_cfg_t audproc_hpf_tx_iir_filter_enable_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_hpf_tx_iir_filter_enable_cfg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_ENABLE_CONFIG
    parameter in the Tx path HPF Tuning Filter module.
*/
struct audproc_hpf_tx_iir_filter_enable_cfg_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the HPF tuning filter is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_hpf_tx_iir_filter_enable_cfg_t */

/* Structure for the pregain parameter for the HPF
    IIR tuning filter module on the Tx path. */
typedef struct audproc_hpf_tx_iir_filter_pre_gain_t audproc_hpf_tx_iir_filter_pre_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_hpf_tx_iir_filter_pre_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_PRE_GAIN parameter
    in the Tx path HPF Tuning Filter module.
*/
struct audproc_hpf_tx_iir_filter_pre_gain_t
{
    uint16_t                  pre_gain;
    /**< Linear gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_hpf_tx_iir_filter_pre_gain_t */

/* Structure for the configuration parameter for the
    HPF IIR tuning filter module on the Tx path. */
typedef struct audproc_hpf_tx_iir_filter_cfg_params_t audproc_hpf_tx_iir_filter_cfg_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_hpf_tx_iir_filter_cfg_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_CONFIG_PARAMS
    parameters on the Tx path HPF Tuning Filter module.
*/
struct audproc_hpf_tx_iir_filter_cfg_params_t
{
    uint16_t                  num_biquad_stages;
    /**< Number of bands.

         @values 0 to 20 */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_hpf_tx_iir_filter_cfg_params_t */
/** @endcond */

/** @cond OEM_only */
/** @ingroup audiopp_module_tx_iir_tun_filter
    ID of the IIR Tuning Filter module on the Tx path.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_TX_IIR_FILTER_ENABLE_CONFIG
    - #AUDPROC_PARAM_ID_TX_IIR_FILTER_PRE_GAIN
    - #AUDPROC_PARAM_ID_TX_IIR_FILTER_CONFIG_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_TX_IIR_FILTER                             0x00010C41
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_rx_iir_tun_filter
@{ */
/** ID of the IIR Tuning Filter module on the Rx path for the left channel.

    The parameter IDs of the IIR tuning filter module
    (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER) are used for the left IIR Rx tuning
    filter.

    Pan parameters are not required for this per-channel IIR filter, and they
    are ignored by this module.
*/
#define AUDPROC_MODULE_ID_LEFT_IIR_TUNING_FILTER                     0x00010705

/** ID of the IIR Tuning Filter module on the Rx path for the right channel.

    The parameter IDs of the IIR tuning filter module
    (#AUDPROC_MODULE_ID_IIR_TUNING_FILTER) are used for the right IIR Rx tuning
    filter.

    Pan parameters are not required for this per-channel IIR filter, and they
    are ignored by this module.
*/
#define AUDPROC_MODULE_ID_RIGHT_IIR_TUNING_FILTER                    0x00010706

/** @} */ /* end_addtogroup audiopp_module_rx_iir_tun_filter */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_tx_iir_tun_filter
@{ */
/** ID of the Tx IIR Filter Enable parameter used by
    AUDPROC_MODULE_ID_TX_IIR_FILTER.

    @msgpayload{audproc_tx_iir_filter_enable_cfg_t}
    @table{weak__audproc__tx__iir__filter__enable__cfg__t}
*/
#define AUDPROC_PARAM_ID_TX_IIR_FILTER_ENABLE_CONFIG                0x00010C42

/** ID of the Tx IIR Filter Pregain parameter used by
    AUDPROC_MODULE_ID_TX_IIR_FILTER.

    @msgpayload{audproc_tx_iir_filter_pre_gain_t}
    @table{weak__audproc__tx__iir__filter__pre__gain__t} @newpage
*/
#define AUDPROC_PARAM_ID_TX_IIR_FILTER_PRE_GAIN                     0x00010C43

/** ID of the Tx IIR Filter Configuration parameters used by
    AUDPROC_MODULE_ID_TX_IIR_FILTER.

    @msgpayload{audproc_tx_iir_filter_cfg_params_t}
    @table{weak__audproc__tx__iir__filter__cfg__params__t}
    This structure is followed by the IIR filter coefficients on
    the Tx path as follows:
    - Sequence of int32 ulFilterCoeffs -- Each band has five coefficients, each
      in int32 format in the order of b0, b1, b2, a1, a2.
    - Sequence of int16 sNumShiftFactor -- One int16 per band. The numerator
      shift factor is related to the Q factor of the filter coefficients.
    - Sequence of uint16 usPanSetting -- One uint16 for each band to indicate
      if the filter is applied to left (0), center (1), and right (2) channels.
*/
#define AUDPROC_PARAM_ID_TX_IIR_FILTER_CONFIG_PARAMS                0x00010C44

/** @} */ /* end_addtogroup audiopp_module_tx_iir_tun_filter */

/* Structure for enabling the configuration parameter for the
    IIR filter module on the Tx path. */
typedef struct audproc_tx_iir_filter_enable_cfg_t audproc_tx_iir_filter_enable_cfg_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_tx_iir_filter_enable_cfg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_TX_IIR_FILTER_ENABLE_CONFIG parameter
    in the Tx Path IIR Tuning Filter module.
*/
struct audproc_tx_iir_filter_enable_cfg_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the IIR tuning filter is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_tx_iir_filter_enable_cfg_t */

/* Structure for the pregain parameter for the
    IIR filter module on the Tx path. */
typedef struct audproc_tx_iir_filter_pre_gain_t audproc_tx_iir_filter_pre_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_tx_iir_filter_pre_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_TX_IIR_FILTER_PRE_GAIN parameter
    in the Tx Path IIR Tuning Filter module.
*/
struct audproc_tx_iir_filter_pre_gain_t
{
    uint16_t                  pre_gain;
    /**< Linear gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_tx_iir_filter_pre_gain_t */

/* Structure for the configuration parameter for the
    IIR filter module on the Tx path. */
typedef struct audproc_tx_iir_filter_cfg_params_t audproc_tx_iir_filter_cfg_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_tx_iir_filter_cfg_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_TX_IIR_FILTER_CONFIG_PARAMS parameter
    in the Tx Path IIR Tuning Filter module.
*/
struct audproc_tx_iir_filter_cfg_params_t
{
    uint16_t                  num_biquad_stages;
    /**< Number of bands.

         @values 0 to 20 */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_tx_iir_filter_cfg_params_t */
/** @endcond */

/** @addtogroup audiopp_module_mono2stereo_upmix
*/
/*  ID for Upmixer from mono to stereo
    To be used with custom topology in tunnel mode.
	The module converts the stream to stereo if the
	the channel is mono or else by passes the stream.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_MONO2STEREO_UPMIX_ENABLE
*/
#define AUDPROC_MODULE_ID_MONO2STEREO_UPMIX                                  0x000108d6

/** ID of the MonotoStereoUpmix Enable parameter used by
    AUDPROC_MODULE_ID_MONO2STEREO_UPMIX.

    @msgpayload{audproc_mono2stereo_upmix_enable_t}
    @table{weak__audproc__mono2stereo__upmix__enable__t}
*/

#define AUDPROC_PARAM_ID_MONO2STEREO_UPMIX_ENABLE                      0x000108d7

#include "adsp_begin_pack.h"

/** @weakgroup weak__audproc__mono2stereo__upmix__enable__t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MONO2STEREO_UPMIX_ENABLE parameter used by the
    Mono2Stereo_upmix module.
*/

typedef struct audproc_mono2stereo_upmix_enable_t audproc_mono2stereo_upmix_enable_t;

struct audproc_mono2stereo_upmix_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the mono2stereo upmix is disabled (0) or enabled (1). */

}

#include "adsp_end_pack.h"
;

/** @addtogroup audiopp_module_volume_control_2
@{ */
/** ID of the Volume Control module pre/postprocessing block, instance 2.
    Use this module together with #AUDPROC_MODULE_ID_VOL_CTRL to have two
    volume controls in a pre/postprocessing chain.
    
    This module supports the same parameter IDs that are supported by
    AUDPROC_MODULE_ID_VOL_CTRL.
  */
#define AUDPROC_MODULE_ID_VOL_CTRL_INSTANCE_2         0x00010910
/** @} */ /* end_addtogroup audiopp_module_volume_control_instance_2 */


/** @addtogroup audiopp_module_volume_control
@{ */
/** ID of the Volume Control module pre/postprocessing block.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_VOL_CTRL_MASTER_GAIN
    - #AUDPROC_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN
    - #AUDPROC_PARAM_ID_VOL_CTRL_MUTE_CONFIG
    - #AUDPROC_PARAM_ID_SOFT_VOL_STEPPING_PARAMETERS
    - #AUDPROC_PARAM_ID_SOFT_PAUSE_PARAMETERS
  @if OEM_only
    - #AUDPROC_PARAM_ID_MULTICHANNEL_GAIN
    - #AUDPROC_PARAM_ID_MULTICHANNEL_MUTE
  @endif
*/
#define AUDPROC_MODULE_ID_VOL_CTRL                                  0x00010BFE

/** ID of the Master Gain parameter used by AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_volume_ctrl_master_gain_t}
    @table{weak__audproc__volume__ctrl__master__gain__t}
*/
#define AUDPROC_PARAM_ID_VOL_CTRL_MASTER_GAIN                       0x00010BFF

/** ID of the Left/Right Channel Gain parameter used by
    AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_volume_ctrl_lr_chan_gain_t}
    @table{weak__audproc__volume__ctrl__lr__chan__gain__t}
*/
#define AUDPROC_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN                   0x00010C00

/** ID of the mute Configuration parameter used by
    #AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_volume_ctrl_mute_config_t}
    @table{weak__audproc__volume__ctrl__mute__config__t}
*/
#define AUDPROC_PARAM_ID_VOL_CTRL_MUTE_CONFIG                       0x00010C01

/** ID of the Soft Stepping Volume parameters used by
    #AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_soft_step_volume_params_t}
    @table{weak__audproc__soft__step__volume__params__t}
*/
#define AUDPROC_PARAM_ID_SOFT_VOL_STEPPING_PARAMETERS               0x00010C29

/** Supported parameters for a soft stepping linear ramping curve. */
#define AUDPROC_PARAM_SVC_RAMPINGCURVE_LINEAR                               0

/** Exponential ramping curve. */
#define AUDPROC_PARAM_SVC_RAMPINGCURVE_EXP                                  1

/** Logarithmic ramping curve.  */
#define AUDPROC_PARAM_SVC_RAMPINGCURVE_LOG                                  2

/** Fractional exponent ramping curve. */
#define AUDPROC_PARAM_SVC_RAMPINGCURVE_FRAC_EXP                             3

/** ID of the Soft Pause parameters used by #AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_soft_pause_params_t}
    @table{weak__audproc__soft__pause__params__t} @if OEM_only @newpage @endif 
*/
#define AUDPROC_PARAM_ID_SOFT_PAUSE_PARAMETERS                      0x00010D6A

/** @cond OEM_only */
/** ID of the Multichannel Volume Control parameters used by
    #AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_volume_ctrl_multichannel_gain_t}
    @table{weak__audproc__volume__ctrl__multichannel__gain__t}

    @par Payload format of the channel type/gain pairs (audproc_volume_ctrl_channel_type_gain_pair_t)
    @table{weak__audproc__volume__ctrl__channel__type__gain__pair__t}
*/
#define AUDPROC_PARAM_ID_MULTICHANNEL_GAIN                          0x00010713

/** Maximum number of channels. @newpage */
#define VOLUME_CONTROL_MAX_CHANNELS                       8

/** ID of the Multichannel Mute Configuration parameters used by
    #AUDPROC_MODULE_ID_VOL_CTRL.

    @msgpayload{audproc_volume_ctrl_multichannel_mute_t}
    @table{weak__audproc__volume__ctrl__multichannel__mute__t}

    @par Payload format of the channel type/mute setting pairs (audproc_volume_ctrl_channel_type_mute_pair_t)
    @table{weak__audproc__volume__ctrl__channel__type__mute__pair__t} @newpage
*/
#define AUDPROC_PARAM_ID_MULTICHANNEL_MUTE                          0x00010714

/** @endcond */
/** @} */ /* end_addtogroup audiopp_module_volume_control */

/* Structure for the master gain parameter for a volume control module. */
typedef struct audproc_volume_ctrl_master_gain_t audproc_volume_ctrl_master_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_master_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VOL_CTRL_MASTER_GAIN parameter used
    by the Volume Control module.
*/
struct audproc_volume_ctrl_master_gain_t
{
    uint16_t                  master_gain;
    /**< Linear master gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_master_gain_t */

/* Structure for the left/right channel gain parameter for a
    volume control module. */
typedef struct audproc_volume_ctrl_lr_chan_gain_t audproc_volume_ctrl_lr_chan_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_lr_chan_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN parameters
    used by the Volume Control module.
*/
struct audproc_volume_ctrl_lr_chan_gain_t
{
    uint16_t                  l_chan_gain;
    /**< Linear gain (in Q13 format) for the left channel. */

    uint16_t                  r_chan_gain;
    /**< Linear gain (in Q13 format) for the right channel. @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_lr_chan_gain_t */

/* Structure for the mute configuration parameter for a
    volume control module. */
typedef struct audproc_volume_ctrl_mute_config_t audproc_volume_ctrl_mute_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_mute_config_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VOL_CTRL_MUTE_CONFIG parameter used
    by the Volume Control module.
*/
struct audproc_volume_ctrl_mute_config_t
{
    uint32_t                  mute_flag;
    /**< Specifies whether mute is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_mute_config_t */

/* Structure for holding soft stepping volume parameters. */
typedef struct audproc_soft_step_volume_params_t audproc_soft_step_volume_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_soft_step_volume_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_SOFT_VOL_STEPPING_PARAMETERS
    parameters used by the Volume Control module.
*/
struct audproc_soft_step_volume_params_t
{
    uint32_t                  period;
    /**< Period in milliseconds.

         @values 0 to 15000 */

    uint32_t                  step;
    /**< Step in microseconds.

         @values 0 to 15000000 */

    uint32_t                  ramping_curve;
    /**< Ramping curve type.

         @values
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_LINEAR
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_EXP
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_LOG
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_FRAC_EXP @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_soft_step_volume_params_t */

/* Structure for holding soft pause parameters. */
typedef struct audproc_soft_pause_params_t audproc_soft_pause_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_soft_pause_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_SOFT_PAUSE_PARAMETERS parameters used
    by the Volume Control module.
*/
struct audproc_soft_pause_params_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether soft pause is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */

    uint32_t                  period;
    /**< Period in milliseconds.

         @values 0 to 15000 */

    uint32_t                  step;
    /**< Step in microseconds.

         @values 0 to 15000000 */

    uint32_t                  ramping_curve;
    /**< Ramping curve.

         @values
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_LINEAR
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_EXP
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_LOG
         - #AUDPROC_PARAM_SVC_RAMPINGCURVE_FRAC_EXP @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_soft_pause_params_t */

/* Structure for holding one channel type - gain pair. */
typedef struct audproc_volume_ctrl_channel_type_gain_pair_t audproc_volume_ctrl_channel_type_gain_pair_t;

#include "adsp_begin_pack.h"

/** @cond OEM_only */
/** @weakgroup weak_audproc_volume_ctrl_channel_type_gain_pair_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MULTICHANNEL_GAIN channel type/gain
    pairs used by the Volume Control module.
    This structure immediately follows the
    audproc_volume_ctrl_multichannel_gain_t structure.
*/
struct audproc_volume_ctrl_channel_type_gain_pair_t
{
    uint8_t                   channel_type;
    /**< Channel type for which the gain setting is to be applied.

         @values See Section @xref{dox:PcmChannelDefs} */

    uint8_t                   reserved1;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved2;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved3;
    /**< Clients must set this field to zero. */

    uint32_t                  gain;
    /**< Gain value for this channel in Q28 format. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_channel_type_gain_pair_t */

/* Structure for the multichannel gain command */
typedef struct audproc_volume_ctrl_multichannel_gain_t audproc_volume_ctrl_multichannel_gain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_multichannel_gain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MULTICHANNEL_GAIN parameters used by
    the Volume Control module.
*/
struct audproc_volume_ctrl_multichannel_gain_t
{
    uint32_t                  num_channels;
    /**< Number of channels for which gain values are provided. Any channels
         present in the data for which gain is not provided are set to unity
         gain.

         @values 1 to #VOLUME_CONTROL_MAX_CHANNELS */

    audproc_volume_ctrl_channel_type_gain_pair_t     gain_data[VOLUME_CONTROL_MAX_CHANNELS];
    /**< Array of channel type/gain pairs.

         @values See the <b>Payload format</b> table below */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_multichannel_gain_t */

/* Structure for holding one channel type - mute pair. */
typedef struct audproc_volume_ctrl_channel_type_mute_pair_t audproc_volume_ctrl_channel_type_mute_pair_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_channel_type_mute_pair_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MULTICHANNEL_MUTE channel type/mute
    setting pairs used by the Volume Control module.
    This structure immediately follows the
    audproc_volume_ctrl_multichannel_mute_t structure.
*/
struct audproc_volume_ctrl_channel_type_mute_pair_t
{
    uint8_t                   channel_type;
    /**< Channel type for which the mute setting is to be applied.

         @values See Section @xref{dox:PcmChannelDefs} */

    uint8_t                   reserved1;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved2;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved3;
    /**< Clients must set this field to zero. */

    uint32_t                  mute;
    /**< Specifies whether this channel is set to mute.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_channel_type_mute_pair_t */

/* Structure for the multichannel mute command */
typedef struct audproc_volume_ctrl_multichannel_mute_t audproc_volume_ctrl_multichannel_mute_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_volume_ctrl_multichannel_mute_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MULTICHANNEL_MUTE parameters used by
    the Volume Control module.
*/
struct audproc_volume_ctrl_multichannel_mute_t
{
    uint32_t                  num_channels;
    /**< Number of channels for which mute configuration is provided. Any
         channels present in the data for which mute configuration is not
         provided are set to unmute.

         @values 1 to #VOLUME_CONTROL_MAX_CHANNELS */

    audproc_volume_ctrl_channel_type_mute_pair_t    mute_data[VOLUME_CONTROL_MAX_CHANNELS];
    /**< Array of channel type/mute setting pairs.

         @values See the <b>Payload format</b> table below */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_volume_ctrl_multichannel_mute_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_iir_tuning_filter
@{ */
/** ID of the IIR Tuning Filter module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_IIR_TUNING_FILTER_ENABLE_CONFIG
    - #AUDPROC_PARAM_ID_IIR_TUNING_FILTER_PRE_GAIN
    - #AUDPROC_PARAM_ID_IIR_TUNING_FILTER_CONFIG_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_IIR_TUNING_FILTER                         0x00010C02

/** ID of the IIR Tuning Filter Enable parameter used by
    AUDPROC_MODULE_ID_IIR_TUNING_FILTER.

    @msgpayload{audproc_iir_tuning_filter_enable_t}
    @table{weak__audproc__iir__tuning__filter__enable__t}
*/
#define AUDPROC_PARAM_ID_IIR_TUNING_FILTER_ENABLE_CONFIG            0x00010C03

/** ID of the IIR Tuning Filter Pregain parameter used by
    AUDPROC_MODULE_ID_IIR_TUNING_FILTER.

    @msgpayload{audproc_iir_tuning_filter_pregain_t}
    @table{weak__audproc__iir__tuning__filter__pregain__t}
*/
#define AUDPROC_PARAM_ID_IIR_TUNING_FILTER_PRE_GAIN                 0x00010C04

/** ID of the IIR Tuning Filter Configuration parameters used by
    #AUDPROC_MODULE_ID_IIR_TUNING_FILTER.

    @msgpayload{audproc_iir_filter_config_params_t}
    @table{weak__audproc__iir__filter__config__params__t}
    This structure is followed by the IIR filter coefficients on
    the Tx path as follows:
    - Sequence of int32 ulFilterCoeffs -- Each band has five coefficients, each
      in int32 format in the order of b0, b1, b2, a1, a2.
    - Sequence of int16 sNumShiftFactor -- One int16 per band. The numerator
      shift factor is related to the Q factor of the filter coefficients.
    - Sequence of uint16 usPanSetting -- One uint16 for each band to indicate
      if the filter is applied to left (0), center (1), and right (2) channels.
*/
#define AUDPROC_PARAM_ID_IIR_TUNING_FILTER_CONFIG_PARAMS            0x00010C05

/** @} */ /* end_addtogroup audiopp_module_iir_tuning_filter */

/* Structure for an enable configuration parameter for an
    IIR tuning filter module. */
typedef struct audproc_iir_tuning_filter_enable_t audproc_iir_tuning_filter_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_iir_tuning_filter_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_IIR_TUNING_FILTER_ENABLE_CONFIG
    parameter used by the IIR Tuning Filter module.
*/
struct audproc_iir_tuning_filter_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the IIR tuning filter is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_iir_tuning_filter_enable_t */

/* Structure for the pregain parameter for an IIR tuning filter module. */
typedef struct audproc_iir_tuning_filter_pregain_t audproc_iir_tuning_filter_pregain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_iir_tuning_filter_pregain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_IIR_TUNING_FILTER_PRE_GAIN
    parameters used by the IIR Tuning Filter module.
*/
struct audproc_iir_tuning_filter_pregain_t
{
    uint16_t                  pregain;
    /**< Linear gain (in Q13 format). */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_iir_tuning_filter_pregain_t */

/* Structure for the configuration parameter for an IIR tuning filter module. */
typedef struct audproc_iir_filter_config_params_t audproc_iir_filter_config_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_iir_filter_config_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_IIR_TUNING_FILTER_CONFIG_PARAMS
    parameters used by the IIR Tuning Filter module.
*/
struct audproc_iir_filter_config_params_t
{
    uint16_t                  num_biquad_stages;
    /**< Number of bands.

         @values 0 to 20 */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_iir_filter_config_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_mbdrc
@{ */
/** ID of the Multiband Dynamic Range Control (MBDRC) module on the Tx/Rx
    paths.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_MBDRC_ENABLE
    - #AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_MBDRC                                    0x00010C06

/** ID of the MBDRC Enable parameter used by AUDPROC_MODULE_ID_MBDRC.

    @msgpayload{audproc_mbdrc_enable_t}
    @table{weak__audproc__mbdrc__enable__t}
*/
#define AUDPROC_PARAM_ID_MBDRC_ENABLE                              0x00010C07

/** ID of the MBDRC Configuration parameter used by AUDPROC_MODULE_ID_MBDRC.

    @msgpayload{audproc_mbdrc_config_params_t}
    Following this structure is the subband payload,
    %audproc_subband_drc_config_params_t (see <b>Subband DRC configuration
    parameters</b>).
    This subband structure must be repeated for each band.
    @tablens{weak__audproc__mbdrc__config__params__t}
    After this DRC structure is configured for valid bands, the next MBDRC
    setparams expects the sequence of subband MBDRC filter coefficients (the
    length depends on the number of bands) plus the mute flag for that band
    plus uint16 padding.
    @par
    The filter coefficient and mute flag are of type int16:
    - FIR coefficient = int16 firFilter
    - Mute flag = int16 fMuteFlag
    @par
    @keep{6} The sequence is as follows:
    - 1 band = 0 FIR coefficient + 1 mute flag + uint16 padding
    - 2 bands = 97 FIR coefficients + 2 mute flags + uint16 padding
    - 3 bands = 97+33 FIR coefficients + 3 mute flags + uint16 padding
    - 4 bands = 97+33+33 FIR coefficients + 4 mute flags + uint16 padding
    - 5 bands = 97+33+33+33 FIR coefficients + 5 mute flags + uint16 padding
    @par
    @keep{6} For improved filterbank, the sequence is as follows:
    - 1 band = 0 FIR coefficient + 1 mute flag + uint16 padding
    - 2 bands = 141 FIR coefficients + 2 mute flags + uint16 padding
    - 3 bands = 141+81 FIR coefficients + 3 mute flags + uint16 padding
    - 4 bands = 141+81+61 FIR coefficients + 4 mute flags + uint16 padding
    - 5 bands = 141+81+61+61 FIR coefficients + 5 mute flags + uint16 padding

    @par Subband DRC configuration parameters (audproc_subband_drc_config_params_t)
    @table{weak__audproc__subband__drc__config__params__t} @newpage
    To obtain legacy ADRC from MBDRC, use the calibration tool to:
    - Enable MBDRC (EnableFlag = TRUE)
    - Set number of bands to 1 (uiNumBands = 1)
    - Enable the first MBDRC band (DrcMode[0] = DRC_ENABLED = 1)
    - Clear the first band mute flag (MuteFlag[0] = 0)
    - Set the first band makeup gain to unity (compMakeUpGain[0] = 0x2000)
    - Use the legacy ADRC parameters to calibrate the rest of the MBDRC
      parameters. @newpage
*/
#define AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS                         0x00010C08

/** @} */ /* end_addtogroup audiopp_module_mbdrc */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_mbdrcv2
@{ */
/** ID of the MBDRC version 2 module pre/postprocessing block.

    This MBDRCV2 module differs from the original MBDRC
    (#AUDPROC_MODULE_ID_MBDRC) in the length of the filters used in each
    subband.

    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_MBDRCV2                                0x0001070B

/** ID of the Configuration parameter used by AUDPROC_MODULE_ID_MBDRCV2 for the
    improved filter structure of the MBDRC v2 pre/postprocessing block.

    The update to this configuration structure from the original MBDRC is the
    number of filter coefficients in the filter structure. The sequence
    is as follows:

    - 1 band = 0 FIR coefficient + 1 mute flag + uint16 padding
    - 2 bands = 141 FIR coefficients + 2 mute flags + uint16 padding
    - 3 bands = 141+81 FIR coefficients + 3 mute flags + uint16 padding
    - 4 bands = 141+81+61 FIR coefficients + 4 mute flags + uint16 padding
    - 5 bands = 141+81+61+61 FIR coefficients + 5 mute flags + uint16 padding

    @msgpayload
    This block uses the same parameter structure as
    #AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS.
*/
#define AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_IMPROVED_FILTBANK_V2  0x0001070C

/** @} */ /* end_addtogroup audiopp_module_mbdrcv2 */

/* Structure for the enable parameter for an MBDRC module. */
typedef struct audproc_mbdrc_enable_t audproc_mbdrc_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mbdrc_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MBDRC_ENABLE parameter used by the
    MBDRC module.
*/
struct audproc_mbdrc_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether MBDRC is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mbdrc_enable_t */

/* Structure for the configuration parameters for an MBDRC module. */
typedef struct audproc_mbdrc_config_params_t audproc_mbdrc_config_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mbdrc_config_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS parameters used
    by the MBDRC module.

    Following this structure is the payload for subband DRC configuration
    parameters (audproc_subband_drc_config_params_t). This subband structure
    must be repeated for each band.
*/
struct audproc_mbdrc_config_params_t
{
    uint16_t                  num_bands;
    /**< Number of bands.

         @values 1 to 5 */

    int16_t                   limiter_threshold;
    /**< Threshold in decibels for the limiter output.

         @values -72 to 18 \n
         Recommended value: 3994 (-0.22 db in Q3.12 format) */

    int16_t                   limiter_makeup_gain;
    /**< Makeup gain in decibels for the limiter output.

         @values -42 to 42 \n
         Recommended value: 256 (0 dB in Q7.8 format) */

    int16_t                   limiter_gc;
    /**< Limiter gain recovery coefficient.

         @values 0.5 to 0.99 \n
         Recommended value: 32440 (0.99 in Q15 format) */

    int16_t                   limiter_delay;
    /**< Limiter delay in samples.

         @values 0 to 10 \n
         Recommended value: 262 (0.008 samples in Q15 format) */

    int16_t                   limiter_max_wait;
    /**< Maximum limiter waiting time in samples.

         @values 0 to 10 \n
         Recommended value: 262 (0.008 samples in Q15 format) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mbdrc_config_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_mbdrcv3
@{ */
/** ID of the Multiband Dynamic Range Control (MBDRC24Bit) module on the Tx
    and Rx paths. This parameter supports both 16-bit and 24-bit data.

    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_MBDRC_ENABLE
    - #AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_V3
    - #AUDPROC_PARAM_ID_ENABLE
    - #AUDPROC_PARAM_ID_MBDRC_FILTER_XOVER_FREQS
*/
#define AUDPROC_MODULE_ID_MBDRCV3                              0x0001090B

/** ID of the MBDRC Configuration parameter used by AUDPROC_MODULE_ID_MBDRCV3.

    @msgpayload{audproc_mbdrc_config_params_v3_t}
    Following this structure is the <b>Payload for sub-band DRC configuration
    parameters</b>. This sub-band structure must be repeated for each band.
    @tablens{weak__audproc__mbdrc__config__params__v3__t}
    After this DRC structure is configured for valid bands, the next MBDRC
    setparams expects the sequence of sub-band MBDRC filter coefficients (the
    length depends on the number of bands) plus the mute flag for that band
    plus uint16 padding.
    @par
    The filter coefficient and mute flag are of type int16:
    - FIR coefficient = int16 firFilter
    - Mute flag = int16 fMuteFlag
    @par
    The sequence is as follows:
    - 1 band = 0 FIR coefficient + 1 mute flag + uint16 padding
    - 2 bands = 97 FIR coefficients + 2 mute flags + uint16 padding
    - 3 bands = 97+33 FIR coefficients + 3 mute flags + uint16 padding
    - 4 bands = 97+33+33 FIR coefficients + 4 mute flags + uint16 padding
    - 5 bands = 97+33+33+33 FIR coefficients + 5 mute flags + uint16 padding
    @par
    For improved filterbank, the sequence is as follows:
    - 1 band = 0 FIR coefficient + 1 mute flag + uint16 padding
    - 2 bands = 141 FIR coefficients + 2 mute flags + uint16 padding
    - 3 bands = 141+81 FIR coefficients + 3 mute flags + uint16 padding
    - 4 bands = 141+81+61 FIR coefficients + 4 mute flags + uint16 padding
    - 5 bands = 141+81+61+61 FIR coefficients + 5 mute flags + uint16 padding
    @newpage

    @par Sub-band DRC configuration parameters (audproc_subband_drc_config_params_t)
    @table{weak__audproc__subband__drc__config__params__t}
    To obtain legacy ADRC from MBDRC, use the calibration tool to:
    - Enable MBDRC (EnableFlag = TRUE)
    - Set number of bands to 1 (uiNumBands = 1)
    - Enable the first MBDRC band (DrcMode[0] = DRC_ENABLED = 1)
    - Clear the first band mute flag (MuteFlag[0] = 0)
    - Set the first band makeup gain to unity (compMakeUpGain[0] = 0x2000)
    - Use the legacy ADRC parameters to calibrate the rest of the MBDRC
      parameters.
*/
#define AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_V3               0x0001090C

/* Structure for the configuration parameters for an MBDRC_V3 module. */
typedef struct audproc_mbdrc_config_params_v3_t audproc_mbdrc_config_params_v3_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mbdrc_config_params_v3_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_V3 parameters used
    by the MBDRC_V3 module.

    Following this structure is the payload for sub-band DRC configuration
    parameters (audproc_subband_drc_config_params_t). This sub-band structure
    must be repeated for each band.
*/
struct audproc_mbdrc_config_params_v3_t
{
    uint16_t                  num_bands;
    /**< Number of bands.

         @values 1 to 5 */

    int16_t                   limiter_threshold;
    /**< Threshold in decibels for the limiter output.

         @values -72 to 18 \n
         Recommended value: 3994 (-0.22 db in Q3.12 format) */

    int16_t                   limiter_makeup_gain;
    /**< Makeup gain in decibels for the limiter output.

         @values -42 to 42 \n
         Recommended value: 256 (0 dB in Q7.8 format) */

    int16_t                   limiter_gc;
    /**< Limiter gain recovery coefficient.

         @values 0.5 to 0.99 \n
         Recommended value: 32440 (0.99 in Q15 format) */

    int16_t                   limiter_delay;
    /**< Limiter delay in samples.

         @values 0 to 10 \n
         Recommended value: 262 (0.008 samples in Q15 format) */

    int16_t                   limiter_max_wait;
    /**< Maximum limiter waiting time in samples.

         @values 0 to 10 \n
         Recommended value: 262 (0.008 samples in Q15 format) */

    uint16_t                  fir_filter_length;
    /**< MBDRC_V3 FIR split filter length.

         @values
         - For device sampling frequencies < 32 kHz:
             - 1 band -- 0
             - 2 bands -- 97
             - 3 bands -- 130
             - 4 bands -- 163
             - 5 bands -- 196 
         - For device sampling frequencies >= 32 kHz:
             - 1 band -- 0
             - 2 bands -- 141
             - 3 bands -- 222
             - 4 bands -- 283
             - 5 bands -- 344 @tablebulletend */

    uint16_t                  reserved;
    /**< Must be set to 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mbdrc_config_params_v3_t */

/** ID of the MBDRC Configuration parameter used by #AUDPROC_MODULE_ID_MBDRCV3.

    @msgpayload{audproc_mbdrc_filter_xover_freqs_t}
    @table{weak__audproc__mbdrc__filter__xover__freqs__t}
*/
#define AUDPROC_PARAM_ID_MBDRC_FILTER_XOVER_FREQS             0x0001090D

/** @} */ /* end_addtogroup audiopp_module_mbdrc_v3 */

/** Maximum number of bands. */
#define MBDRC_MAX_BANDS                                            5

/* Structure for the MBDRC filter cross over frequencies parameter
 * for an MBDRC_V3 module. */
typedef struct audproc_mbdrc_filter_xover_freqs_t audproc_mbdrc_filter_xover_freqs_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mbdrc_filter_xover_freqs_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MBDRC_FILTER_XOVER_FREQS parameter used
    by the MBDRC_V3 module.
*/
struct audproc_mbdrc_filter_xover_freqs_t
{
    uint32_t                  filter_xover_freqs[MBDRC_MAX_BANDS-1];
    /**< Array of filter crossover frequencies.

         Band 1 -- filter_xover_freqs[MBDRC_MAX_BANDS-1] are ignored.

         Band 2 -- filter_xover_freqs[MBDRC_MAX_BANDS-1] has one crossover
         frequency and the rest are ignored.

         Band 3 -- filter_xover_freqs[MBDRC_MAX_BANDS-1] has two crossover
         frequencies and the rest are ignored.

         Band 4 -- filter_xover_freqs[MBDRC_MAX_BANDS-1] has three crossover
         frequencies and the rest are ignored.

         Band 5 -- filter_xover_freqs[MBDRC_MAX_BANDS-1] has all four crossover
         frequencies. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mbdrc_filter_xover_freqs_t */
/** @endcond */

/* DRC configuration structure for each sub-band of an MBDRC module. */
typedef struct audproc_subband_drc_config_params_t audproc_subband_drc_config_params_t;

#include "adsp_begin_pack.h"

/** @cond OEM_only */
/** @weakgroup weak_audproc_subband_drc_config_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS DRC configuration
    parameters for each sub-band in the MBDRC module.
    (See also audproc_mbdrc_config_params_t.)
*/
struct audproc_subband_drc_config_params_t
{
    int16_t                   drc_stereo_linked_flag;
    /**< Specifies whether all stereo channels have the same applied dynamics
         or if they process their dynamics independently.

         @values
         - 0 -- Not linked; channels process the dynamics independently
         - 1 -- Linked; channels have the same applied dynamics
         @tablebulletend */

    int16_t                   drc_mode;
    /**< Specifies whether DRC mode is bypassed for subbands.

         @values
         - 0 -- Disabled
         - 1 -- Enabled @tablebulletend */

    int16_t                   drc_down_sample_level;
    /**< DRC down sample level.

         @values @ge 1 */

    int16_t                   drc_delay;
    /**< DRC delay in samples.

         @values 0 to 1200 */

    uint16_t                  drc_rms_time_avg_const;
    /**< RMS signal energy time-averaging constant.

         @values 0 to 2^16-1 */

    uint16_t                  drc_makeup_gain;
    /**< DRC makeup gain in decibels.

         @values 258 to 64917 */

    /* Down expander settings */

    int16_t                   down_expdr_threshold;
    /**< Down expander threshold.

         @values 1320 to up_cmpsr_threshold (in Q7 format) */

    int16_t                   down_expdr_slope;
    /**< Down expander slope.

         @values -32768 to 0 (in Q8 format) */

    uint32_t                  down_expdr_attack;
    /**< Down expander attack constant.

         @values 196844 to 2^31 (in Q31 format) */

    uint32_t                  down_expdr_release;
    /**< Down expander release constant.

         @values 19685 to 2^31 (in Q31 format) */

    uint16_t                  down_expdr_hysteresis;
    /**< Down expander hysteresis constant.

         @values 1 to 32690 (in Q14 format) */

    uint16_t                  reserved;
    /**< Clients must set this field to zero. */

    int32_t                   down_expdr_min_gain_db;
    /**< Down expander minimum gain.

         @values -805306368 to 0.  (in Q23 format)*/

    /* Up compressor settings */

    int16_t                   up_cmpsr_threshold;
    /**< Up compressor threshold.

         @values down_expdr_threshold to down_cmpsr_threshold (in Q7 format) */

    uint16_t                  up_cmpsr_slope;
    /**< Up compressor slope.

         @values 0 to 64881  (in Q16 format)*/

    uint32_t                  up_cmpsr_attack;
    /**< Up compressor attack constant.

         @values 196844 to 2^31  (in Q31 format)*/

    uint32_t                  up_cmpsr_release;
    /**< Up compressor release constant.

         @values 19685 to 2^31  (in Q31 format)*/

    uint16_t                  up_cmpsr_hysteresis;
    /**< Up compressor hysteresis constant.

         @values 1 to 32690 (in Q14 format) */

    /* Down compressor settings */

    int16_t                   down_cmpsr_threshold;
    /**< Down compressor threshold.

         @values up_cmpsr_threshold to 11560 (in Q7 format) */

    uint16_t                  down_cmpsr_slope;
    /**< Down compressor slope.

         @values 0 to 64881 (in Q16 format) */

    uint16_t                  reserved1;
    /**< Clients must set this field to zero. */

    uint32_t                  down_cmpsr_attack;
    /**< Down compressor attack constant.

         @values 196844 to 2^31 (in Q31 format) */

    uint32_t                  down_cmpsr_release;
    /**< Down compressor release constant.

         @values 19685 to 2^31 (in Q31 format) */

    uint16_t                  down_cmpsr_hysteresis;
    /**< Down compressor hysteresis constant.

         @values 1 to 32690 (in Q14 format) */

    uint16_t                  reserved2;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_subband_drc_config_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_equalizer
@{ */
/** ID of the Equalizer module postprocessing block.
    This module supports the following parameter ID.
    
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_EQUALIZER_PARAMETERS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_EQUALIZER                                 0x00010C27

/** ID of the Equalizer Configuration parameter used by
    AUDPROC_MODULE_ID_EQUALIZER.

    @msgpayload{audproc_eq_params_t}
    Following this structure are num_bands of %audproc_eq_per_band_params_t
    (see <b>Per-band equalizer parameters</b>).
    The length is dependent on the num_bands value.
    @tablens{weak__audproc__eq__params__t}

    @par Per-band equalizer parameters (audproc_eq_per_band_params_t)
    @table{weak__audproc__eq__per__band__params__t}
*/
#define AUDPROC_PARAM_ID_EQUALIZER_PARAMETERS                       0x00010C28

/** @} */ /* end_addtogroup audiopp_module_equalizer */

/* Structure for equalizer module parameters. */
typedef struct audproc_eq_params_t audproc_eq_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQUALIZER_PARAMETERS parameters used
    by the Equalizer module.
   Following this structure is a sequence of <b>Per-band equalizer
    parameters</b>. The length is dependent on the num_bands value.
*/
struct audproc_eq_params_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the equalizer module is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */

    uint32_t                  num_bands;
    /**< Number of bands.

         @values 1 to 12 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_params_t */

/** @addtogroup audiopp_module_equalizer
@{ */
/** No equalizer effect. */
#define AUDPROC_PARAM_EQ_TYPE_NONE                                       0

/** Bass boost equalizer effect. */
#define AUDPROC_PARAM_EQ_BASS_BOOST                                      1

/** Bass cut equalizer effect. */
#define AUDPROC_PARAM_EQ_BASS_CUT                                        2

/** Treble boost equalizer effect. */
#define AUDPROC_PARAM_EQ_TREBLE_BOOST                                    3

/** Treble cut equalizer effect. */
#define AUDPROC_PARAM_EQ_TREBLE_CUT                                      4

/** Band boost equalizer effect. */
#define AUDPROC_PARAM_EQ_BAND_BOOST                                      5

/** Band cut equalizer effect. @newpage */
#define AUDPROC_PARAM_EQ_BAND_CUT                                        6

/** @} */ /* end_addtogroup audiopp_module_equalizer */

/* Structure for per-band parameters for the equalizer module. */
typedef struct audproc_eq_per_band_params_t audproc_eq_per_band_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_per_band_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQUALIZER_PARAMETERS per-band
    parameters used by the Equalizer module. (See also audproc_eq_params_t.)
*/
struct audproc_eq_per_band_params_t
{
    uint32_t                  band_idx;
    /**< Band index.

         @values 0 to 11 */

    uint32_t                  filter_type;
    /**< Type of filter.

         @values
         - #AUDPROC_PARAM_EQ_TYPE_NONE
         - #AUDPROC_PARAM_EQ_BASS_BOOST
         - #AUDPROC_PARAM_EQ_BASS_CUT
         - #AUDPROC_PARAM_EQ_TREBLE_BOOST
         - #AUDPROC_PARAM_EQ_TREBLE_CUT
         - #AUDPROC_PARAM_EQ_BAND_BOOST
         - #AUDPROC_PARAM_EQ_BAND_CUT @tablebulletend */

    uint32_t                  center_freq_hz;
    /**< Filter band center frequency in Hertz. */

    int32_t                   filter_gain;
    /**< Filter band initial gain.

         @values +12 to -12 dB in 1 dB increments */

    int32_t                   q_factor;
    /**< Filter band quality factor expressed as a Q8 number (a
         fixed-point number with q factor of 8). For example, 3000/(2^8). */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_per_band_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_pbe
@{ */
/** ID of the Psychoacoustic Bass Enhancement (PBE) module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_PBE_ENABLE
    - #AUDPROC_PARAM_ID_PBE_PARAMS_CONFIG
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_PBE                              0x00010C2A

/** ID of the PBE Enable Configuration parameter used by AUDPROC_MODULE_ID_PBE.

    @msgpayload{audproc_pbe_enable_t}
    @table{weak__audproc__pbe__enable__t}
*/
#define AUDPROC_PARAM_ID_PBE_ENABLE                       0x00010C2B

/** ID of the PBE Configuration parameter used by AUDPROC_MODULE_ID_PBE.

    @msgpayload{audproc_pbe_params_t}
    @table{weak__audproc__pbe__params__t}
    This structure is followed by the filter coefficients. The length is
    dependent on the number of bands:
    - Sequence of int32 p1LowpassCoeffsLQ30 -- Low pass filter coefficients if
      uiXoverFltOrder = 3 {length = 5 * 2}. Else, {length = 5}.
    - Sequence of int32 p1HighpassCoeffsQ30 -- High pass filter coefficients
      if uiXoverFltOrder = 3 {length = 5 * 2}. Else, {length = 5}.
    - Sequence of int32 p1BandpassCoeffsQ30 -- Band pass filter coefficients
      if length is 5 * uiBandpassFltOrder. Each band has five coefficients,
      and each coefficient is in int32 format in the order of b0, b1, b2, a1,
      a2.
    - Sequence of int32 p1BassShelfCoeffsQ30 -- Bass shelf filter coefficients
      of length 5. Each coefficient is in int32 format in the order of b0, b1,
      b2, a1, a2.
    - Sequence of int32 p1TrebleShelfCoeffsQ30 -- Treble shelf filter
      coefficients of length 5. Each coefficient is in int32 format in the
      order of b0, b1, b2, a1, a2.
*/
#define AUDPROC_PARAM_ID_PBE_PARAMS_CONFIG                0x00010C49

/** @} */ /* end_addtogroup audiopp_module_pbe */

/* Structure for the enable configuration parameter for PBE enable. */
typedef struct audproc_pbe_enable_t audproc_pbe_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_pbe_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_PBE_ENABLE parameter used by the PBE module.
*/
struct audproc_pbe_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the PBE module is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_pbe_enable_t */

/* Structure for PBE configuration parameters. */
typedef struct audproc_pbe_params_t audproc_pbe_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_pbe_params_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_PBE_PARAMS_CONFIG parameters used by
    the PBE module.
*/
struct audproc_pbe_params_t
{
    int16_t                   real_bass_mix_q15;
    /**< Mix amount of real bass harmonics and virtual bass harmonics.

         @values 0.0 (all virtual) to 1.0 (all real) \n
         Default: 0.4 */

    int16_t                   bass_color_ctrl_q15;
    /**< Color control of virtual bass.

         @values 0.0 (more even harmonics) to 1.0 (more odd harmonics) \n
         Default: 0.3 */

    uint16_t                  main_chain_delay;
    /**< Sample delay in the non-bass path to compensate an algorithm delay in
         the bass path.

         @values 0 to 32 \n
         Default: 15 */

    uint16_t                  xover_filter_order;
    /**< Low-pass and HPF order.

         @values 1 to 3
         - 1 -- 6 dB/oct
         - 2 -- 12 dB/oct (Default)
         - 3 -- 18 dB/oct @tablebulletend */

    uint16_t                  bpass_filter_order;
    /**< Band pass filter order.

         @values 1 to 3
         - 1 -- 6 dB/oct
         - 2 -- 12 dB/oct (Default)
         - 3 -- 18 dB/oct @tablebulletend */

    int16_t                   drc_delay;
    /**< Delay on the signal path to which to apply DRC gain.

         @values 0.0 to 3.0 \n
         Delay: 2.0 */

    uint16_t                  rms_time_avg_ul16q16;
    /**< Short-term root mean square energy estimation time.

         @values 0.0 to 3.0 \n
         Delay: 2.0 */

    int16_t                   expdr_threshold_l16q8;
    /**< Downward expansion threshold.

         @values -80.0 to cmpsr_threashold_l16q7 \n
         Default: -35.0 */

    uint16_t                  expdr_slope_l16q8;
    /**< Downward expansion ratio.

         @values 0.0 to 1.0 \n
         Default: 0.6 */

    int16_t                   cmpsr_threashold_l16q7;
    /**< Downward compression threshold.

         @values expdr_threshold_l16q8 to 0.0 \n
         Default: -20.0 */

    uint16_t                  cmpsr_slope_ul16q16;
    /**< Downward compression ratio.

         @values 1.0 to 30.0 \n
         Default: 10.0 */

    uint16_t                  makeup_gain_ul16q12;
    /**< Makeup gain.

         @values -18.0 to 18.0 \n
         Default: 6.0 */

    uint32_t                  cmpsr_attack_ul32q31;
    /**< Downward compression gain smooth attack time.

         @values 0.0 to 500.0 \n
         Default: 10.0 */

    uint32_t                  cmpsr_release_ul32q31;
    /**< Downward compression gain smooth release time.

         @values 0.0 to 5000.0 \n
         Default: 100.0 */

    uint32_t                  expdr_attack_ul32q31;
    /**< Downward expansion gain smooth attack time.

         @values 0.0 to 500.0 \n
         Default: 50.0 */

    uint32_t                  expdr_release_ul32q31;
    /**< Downward expansion gain smooth release time.

         @values 0.0 to 5000.0 \n
         Default: 50.0 */

    int16_t                   limiter_bass_threshold_q12;
    /**< Output level of bass content.

         @values 0.0 to 48.0 \n
         Default: 27.0 */

    int16_t                   limiter_high_threshold_q12;
    /**< Output level of non-bass content.

         @values 0.0 to 48.0 \n
         Default: 6.0 */

    int16_t                   limiter_bass_makeup_gain_q8;
    /**< Extra boost gain for bass content.

         @values 0.0 to 1.0 \n
         Default: 0.99 */

    int16_t                   limiter_high_makeup_gain_q8;
    /**< Extra boost gain for non-bass content.

         @values 0.0 to 1.0 \n
         Default: 0.99 */

    int16_t                   limiter_bass_grc_q15;
    /**< Limiter gain recovery constant for bass content.

         @values 0.0 to 1.0 \n
         Default: 0.99 */

    int16_t                   limiter_high_grc_q15;
    /**< Limiter gain recovery constant for non-bass content.

         @values 0.0 to 1.0 \n
         Default: 0.99 */

    int16_t                   limiter_delay_q15;
    /**< Limiter delay and maximum waiting time.

         @values 0.0 to 10.0 \n
         Default: 10.0 */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_pbe_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_spa
@{ */
/** ID of the Spectrum Analyzer (SPA) module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_SPA_ENABLE
    - #AUDPROC_PARAM_ID_SPA_PARAMS_CONFIG
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_SPA                             0x00010C39

/** ID of the SPA Enable parameter used by AUDPROC_MODULE_ID_SPA.

    @msgpayload{audproc_spa_enable_t}
    @table{weak__audproc__spa__enable__t}
*/
#define AUDPROC_PARAM_ID_SPA_ENABLE                       0x00010C3A

/** ID of the SPA Configuration parameter used by AUDPROC_MODULE_ID_SPA.

    @msgpayload{audproc_spa_param_t}
    @table{weak__audproc__spa__param__t}
*/
#define AUDPROC_PARAM_ID_SPA_PARAMS_CONFIG                0x00010C3B

/** @} */ /* end_addtogroup audiopp_module_spa */

/* Structure for the enable configuration parameter for spectrum analyzer enable. */
typedef struct audproc_spa_enable_t audproc_spa_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_spa_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_SPA_ENABLE parameter used by the
    Spectrum Analyzer module.
*/
struct audproc_spa_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the spectrum analyzer is enabled.

         @values
         - 0 -- Disable
         - Nonzero -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_spa_enable_t */

/* Structure for the configuration parameters for the spectrum analyzer
    module. */
typedef struct audproc_spa_param_t audproc_spa_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_spa_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_SPA_PARAMS_CONFIG parameters used by the
    Spectrum Analyzer module.
*/
struct audproc_spa_param_t
{
    uint32_t                  sample_interval;
    /**< Sample interval.

         @values @ge 512 */

    uint16_t                  sample_points;
    /**< Supported Fast Fourier Transform (FFT) size.

         @values 32, 64, 128, 256 */

    uint16_t                  reserved;
    /**< This field must be set to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_spa_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_peakmeter
@{ */
/** ID of the Peak Meter module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_PEAK_INTERVAL
    - #AUDPROC_PARAM_ID_PEAK_VALUES
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_PEAK_METER            0x00010712

/** ID of the Peak Meter Configuration parameter used by
    AUDPROC_MODULE_ID_PEAK_METER. This parameter indicates the update
    interval of the peak meter.

    @msgpayload{audproc_peakmeter_interval_t}
    @table{weak__audproc__peakmeter__interval__t}
*/
#define AUDPROC_PARAM_ID_PEAK_INTERVAL                  0x00010711

/** ID of the Peak Meter Values parameters used by
    #AUDPROC_MODULE_ID_PEAK_METER. The peak meter values are returned
    by the aDSP.

    @msgpayload{audproc_peakmeter_values_t}
    @table{weak__audproc__peakmeter__values__t}
*/
#define AUDPROC_PARAM_ID_PEAK_VALUES                    0x00010710

/** Maximum number of channels that supports peak meter measurement. */
#define PEAKMETER_MAX_NUM_CHANNELS                  8

/** @} */ /* end_addtogroup audiopp_module_peakmeter */

typedef struct audproc_peakmeter_interval_t audproc_peakmeter_interval_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_peakmeter_interval_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_PEAK_INTERVAL parameter used by
    the Peak Meter module.
*/
struct audproc_peakmeter_interval_t
{
    uint32_t            sample_interval;
    /**<  Update time interval in milliseconds of the peak meter.

          @values 0 to 0xFFFFFFFF

          A value of zero disables the peak meter. In this case, the aDSP will
          not report valid peak meter values.

          A nonzero value indicates the peak meter log/reset frequency. For
          example, a value of 20 indicates an interval of 20 ms. This means
          a peak value is updated every 20 ms, and the newly calculated peak
          value replaces the existing value once every 20 ms.

          @note1hang The recommended sample interval is a multiple of 10 ms. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_peakmeter_interval_t */

typedef struct audproc_peakmeter_values_t audproc_peakmeter_values_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_peakmeter_values_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_PEAK_VALUES parameters used by the
    Peak Meter module.
*/
struct audproc_peakmeter_values_t
{
    uint32_t            num_supported_channels;
    /**<  Number of channels for which the peak value was calculated. A value
          of zero indicates that the peak meter is disabled.

          @values 0 to #PEAKMETER_MAX_NUM_CHANNELS */

    int16_t             peak_values[PEAKMETER_MAX_NUM_CHANNELS];
    /**<  Array of peak values for each channel in the most recent window.

          @values 0 to 32767 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_peakmeter_values_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_mchan_iir_tun_filter
@{ */
/** ID of the Multiple Channel IIR Tuning Filter module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_ENABLE
    - #AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_PREGAIN
    - #AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_CONFIG_PARAMS
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_MCHAN_IIR_TUNING_FILTER              0x0001031F

/** ID of the Multichannel IIR Tuning Filter Enable parameters used by
    AUDPROC_MODULE_ID_MCHAN_IIR_TUNING_FILTER.

    @msgpayload{audproc_mchan_iir_enable_t}
    @table{weak__audproc__mchan__iir__enable__t}

    @par Payload format of channel type / IIR enable flag pairs 
    @table{weak__audproc__channel__type__iir__enable__pair__t}
*/
#define AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_ENABLE        0x0001031C

/** Maximum number of channels for the multichannel IIR tuning filter. */
#define IIR_TUNING_FILTER_MAX_CHANNELS                 8

/** @} */ /* end_addtogroup audiopp_module_mchan_iir_tun_filter */

/* Structure for holding one channel type - IIR enable pair. */
typedef struct audproc_channel_type_iir_enable_pair_t audproc_channel_type_iir_enable_pair_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_channel_type_iir_enable_pair_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_ENABLE
    channel type/IIR enable pairs used by the Multiple Channel IIR Tuning
    Filter module.

    This structure immediately follows the audproc_mchan_iir_enable_t
    structure.
*/
struct audproc_channel_type_iir_enable_pair_t
{
    uint8_t                   channel_type;
    /**< Channel type for which the IIR enable is to be applied.

         @values See Section @xref{dox:PcmChannelDefs} */

    uint8_t                   reserved1;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved2;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved3;
    /**< Clients must set this field to zero. */

    uint32_t                  enable_flag;
    /**< Specifies whether the channel IIR is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_channel_type_iir_enable_pair_t */

/* Structure for the multichannel IIR enable command */
typedef struct audproc_mchan_iir_enable_t audproc_mchan_iir_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mchan_iir_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_ENABLE
    parameters used by the Multiple Channel IIR Tuning Filter module.
*/
struct audproc_mchan_iir_enable_t
{
    uint32_t                  num_channels;
    /**< Number of channels for which enable flags are provided.

         @values 0 to #IIR_TUNING_FILTER_MAX_CHANNELS */

    audproc_channel_type_iir_enable_pair_t     enable_flag_settings[IIR_TUNING_FILTER_MAX_CHANNELS];
    /**< Channel type/enable_flag value pairs.

         @values See the <b>Payload format</b> table below */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mchan_iir_enable_t */

/** @ingroup audiopp_module_mchan_iir_tun_filter
    ID of the Multiple Channel IIR Tuning Filter Pregain parameters used by
    #AUDPROC_MODULE_ID_MCHAN_IIR_TUNING_FILTER.

    @msgpayload{audproc_mchan_iir_pregain_t}
    @table{weak__audproc__mchan__iir__pregain__t}

    @par Payload format of channel type/IIR pregain pairs (audproc_channel_type_iir_pregain_pair_t)
    @table{weak__audproc__channel__type__iir__pregain__pair__t}
*/
#define AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_PREGAIN        0x0001031D

/* Structure for holding one channel type - IIR pregain pair. */
typedef struct audproc_channel_type_iir_pregain_pair_t audproc_channel_type_iir_pregain_pair_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_channel_type_iir_pregain_pair_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_PREGAIN
    channel type/IIR pregain pairs used by the Multiple Channel IIR Tuning
    Filter module.
    This structure immediately follows the audproc_mchan_iir_pregain_t
    structure.
*/
struct audproc_channel_type_iir_pregain_pair_t
{
    uint8_t                   channel_type;
    /**< Channel type for which the IIR pregain is to be applied.

         @values See Section @xref{dox:PcmChannelDefs} */

    uint8_t                   reserved1;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved2;
    /**< Clients must set this field to zero. */

    uint8_t                   reserved3;
    /**< Clients must set this field to zero. */

    int32_t                   preGain;
    /**< Pregain of IIR for this channel (in Q27 format). @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_channel_type_iir_pregain_pair_t */

/* Structure for the multichannel IIR preGain command */
typedef struct audproc_mchan_iir_pregain_t audproc_mchan_iir_pregain_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mchan_iir_pregain_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_PREGAIN
    parameters used by the Multiple Channel IIR Tuning Filter module.
*/
struct audproc_mchan_iir_pregain_t
{
    uint32_t                  num_channels;
    /**< Number of channels for which pregains are provided.

         @values 0 to #IIR_TUNING_FILTER_MAX_CHANNELS */

    audproc_channel_type_iir_pregain_pair_t     preGain_settings[IIR_TUNING_FILTER_MAX_CHANNELS];
    /**< Channel type/pregain value pairs.

         @values See the <b>Payload format</b> table below */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mchan_iir_pregain_t */

/** @ingroup audiopp_module_mchan_iir_tun_filter
    ID of the Multiple Channel IIR Tuning Filter Configuration parameters used
    by #AUDPROC_MODULE_ID_MCHAN_IIR_TUNING_FILTER.

    @msgpayload{audproc_mchan_iir_config_t}
    @table{weak__audproc__mchan__iir__config__t}
    This structure is followed by the multichannel IIR filter
    coefficients as follows:
    - Channel type/configuration pairs -- See the <b>Payload format</b> table
      below.
    - Sequence of int32 ulFilterCoeffs -- Five coefficients for each band, each
      in int32 format in the order of b0, b1, b2, a1, a2.
    - Sequence of int16 sNumShiftFactor -- One int16 per band. The numerator
      shift factor is related to the Q factor of the filter coefficients b0,
      b1, b2.
    @par
    There must be one data sequence per channel.
    @par
    If the number of bands is odd, there must be an extra 16-bit padding by
    the end of the numerator shift factors. This extra 16-bit padding makes
    the entire structure 32-bit aligned. The padding bits must be all zeros.

    @par Payload format of channel type/configuration pairs (audproc_channel_type_iir_config_pair_t)
    @table{weak__audproc__channel__type__iir__config__pair__t}
*/
#define AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_CONFIG_PARAMS     0x0001031E

/* Structure for the configuration parameter for multichannel IIR tuning filter module. */
typedef struct audproc_channel_type_iir_config_pair_t audproc_channel_type_iir_config_pair_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_channel_type_iir_config_pair_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_CONFIG_PARAMS
    channel type/configuration pairs used by the Multichannel IIR Tuning Filter
    module.
*/
struct audproc_channel_type_iir_config_pair_t
{
    uint8_t                   channel_type;
    /**< Channel type for which the IIR configuration is to be applied.

         @values See Section @xref{dox:PcmChannelDefs} */

    uint8_t                   reserved;
    /**< Clients must set this field to zero. */

    uint16_t                  num_biquad_stages;
    /**< Number of biquad-IIR bands.

         @values 0 to 20 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_channel_type_iir_config_pair_t */

/* Structure for the multichannel IIR config params */
typedef struct audproc_mchan_iir_config_t audproc_mchan_iir_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mchan_iir_config_t
@{ */
/* Payload of the #AUDPROC_PARAM_ID_MCHAN_IIR_TUNING_FILTER_CONFIG_PARAMS
    parameters used by the Multichannel IIR Tuning Filter module.
*/
struct audproc_mchan_iir_config_t
{
    uint32_t                  num_channels;
    /**< Number of channels for which enable flags are provided.

         @values 0 to #IIR_TUNING_FILTER_MAX_CHANNELS */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_mchan_iir_config_t */
/** @endcond */

/** @cond OEM_only */
/** @ingroup audiopp_topos_adm
    ID of the COPP topology for the SRS TruMedia module.

    @inputfig{1,topo_id_adm_0x00010D90.png}

    - Resampler                       (#AUDPROC_MODULE_ID_RESAMPLER)
    - SRS TruMedia                    (#APPI_SRS_TRUMEDIA_MODULE_ID)
    - Peak Meter                      (#AUDPROC_MODULE_ID_PEAK_METER)
    - Soft Volume Control             (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Rx Codec Gain                   (#AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_SRS_TRUMEDIA_TOPOLOGY          0x00010D90

/** @addtogroup audiopp_module_srs_trumedia
@{ */
/** ID of the SRS TruMedia@tm module.
    This module supports the following parameter IDs:
    - #APPI_SRS_TRUMEDIA_PARAMS
    - #APPI_SRS_TRUMEDIA_WOWHD_PARAMS
    - #APPI_SRS_TRUMEDIA_CSHP_PARAMS
    - #APPI_SRS_TRUMEDIA_HPF_PARAMS
    - #APPI_SRS_TRUMEDIA_AEQ_PARAMS
    - #APPI_SRS_TRUMEDIA_HL_PARAMS
    - #APPI_SRS_TRUMEDIA_GEQ_PARAMS
*/
#define APPI_SRS_TRUMEDIA_MODULE_ID                   0x10005010

/** ID of the SRS TruMedia enable parameters used by
    APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_params_t}
    @table{weak__srs__trumedia__params__t}
*/
#define APPI_SRS_TRUMEDIA_PARAMS                      0x10005011

/* The following are bit fields for the  Enable_Flags
 * field in srs_TruMedia_params_t structure defined below*/

/** Any SRS processing can occur. This bit must be set if any of the
    other enable macros are to be used.
*/
#define SRS_ENABLE_GLOBAL    0x00000001

/** SRS WOW HD@tm processing stage is active. */
#define SRS_ENABLE_WOWHD     0x00000002

/** CS Headphone@tm (CSHP) processing stage is active. */
#define SRS_ENABLE_CSHP      0x00000004

/** High Pass Filter stage is active. */
#define SRS_ENABLE_HPF       0x00000008

/** Adaptive Equalizer stage is active. */
#define SRS_ENABLE_AEQ       0x00000010

/** Hard Limiter stage is active. */
#define SRS_ENABLE_HL        0x00000020

/** Graphic Equalizer stage is active. @newpage */
#define SRS_ENABLE_GEQ       0x00000040

/** @} */ /* end_addtogroup audiopp_module_srs_trumedia */

typedef struct srs_TruMedia_params_t srs_TruMedia_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_PARAMS parameters used by the SRS
    TruMedia module.
*/
struct srs_TruMedia_params_t {
   uint8_t                  Enable_Flags;
   /**< Bitfield of macros used to enable SRS TruMedia.

        @values
        - #SRS_ENABLE_GLOBAL
        - #SRS_ENABLE_WOWHD
        - #SRS_ENABLE_CSHP
        - #SRS_ENABLE_HPF
        - #SRS_ENABLE_AEQ
        - #SRS_ENABLE_HL
        - #SRS_ENABLE_GEQ

        The values are a bitwise OR of any of these macros. When a bit
        corresponding to a particular macro is set, the processing block
        associated with that macro is enabled.

        The bit corresponding to SRS_ENABLE_GLOBAL must be set if any of the
        other bits in the bit field are to be set. */

   uint8_t                  Reserved;
   /**< This field must be set to zero. */

   uint8_t                  I_0;
   /**< SRS licensing payload used to verify the SRS Licensing scheme with the
        aDSP module. */

   uint8_t                  V_0;
   /**< SRS licensing payload. */

   uint8_t                  I_1;
   /**< SRS licensing payload. */

   uint8_t                  V_1;
   /**< SRS licensing payload. */

   uint8_t                  I_2;
   /**< SRS licensing payload. */

    uint8_t                  V_2;
   /**< SRS licensing payload. */

   uint16_t                 IGain;
   /**< Input gain. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_params_t */

/** @addtogroup audiopp_module_srs_trumedia
@{ */
/** ID of the WOW HD configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_wowhd_params_t}
    @table{weak__srs__trumedia__wowhd__params__t}
*/
#define APPI_SRS_TRUMEDIA_WOWHD_PARAMS                0x10005012

/* The following are bit fields for the EnableFlags field in
 * srs_TruMedia_wowhd_params_t defined below*/

/** DTS limiter is enabled and is specific to the WOW HD feature. */
#define SRS_TRUMEDIA_WOWHD_DOLIMIT          0x0001

/** DTS SRS 3D is enabled and is specific to the WOW HD feature. */
#define SRS_TRUMEDIA_WOWHD_DOSRS3D          0x0002

/** DTS TruBass is enabled and is specific to the WOW HD feature. */
#define SRS_TRUMEDIA_WOWHD_DOTB             0x0004

/** DTS TruBass Split Analysis is enabled and is specific to the WOW HD
    feature. */
#define SRS_TRUMEDIA_WOWHD_DOSATB           0x0008

/** DTS Focus is enabled and is specific to the WOW HD feature. */
#define SRS_TRUMEDIA_WOWHD_DOFOCUS          0x0010

/** DTS Definition is enabled and is specific to the WOW HD feature. */
#define SRS_TRUMEDIA_WOWHD_DODEF            0x0020

/** TruBass is stereo when set and mono when not set. */
#define SRS_TRUMEDIA_WOWHD_TBMODE           0x0040

/** Headphone mode for SRS 3D is active. */
#define SRS_TRUMEDIA_WOWHD_SRSTYPE          0x0080

/** Bitmask to use when defining SRS_TRUMEDIA_WOWHD_SRSMODE values.*/
#define SRS_TRUMEDIA_WOWHD_SRSMODE_MASK     0x0F00

/** SRS 3D mode is SRSSrs3dMono. */
#define SRS_TRUMEDIA_WOWHD_SRSMODE_MONO     0x0100

/** SRS 3D mode is SRSSrs3dSingleSpeaker. */
#define SRS_TRUMEDIA_WOWHD_SRSMODE_SINGLE   0x0200

/** SRS 3D mode is SRSSrs3dStereo. */
#define SRS_TRUMEDIA_WOWHD_SRSMODE_STEREO   0x0300

/** SRS 3D mode is SRSSrs3dExtreme. */
#define SRS_TRUMEDIA_WOWHD_SRSMODE_XTREME   0x0400

/** DTS High Pass Filter is enabled and is specific to the WOW HDX feature. */
#define SRS_TRUMEDIA_WOWHDX_DOHPF           0x1000

/** DTS Crossover is enabled and is specific to the WOW HDX feature. */
#define SRS_TRUMEDIA_WOWHDX_DOXOVER         0x2000

/** DTS SRS WideSurround is enabled and is specific to the WOW HDX
    feature. @newpage */
#define SRS_TRUMEDIA_WOWHDX_DOWDSRD         0x4000

/** @} */ /* end_addtogroup audiopp_module_srs_trumedia */

typedef struct srs_TruMedia_wowhd_params_t srs_TruMedia_wowhd_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_wowhd_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_WOWHD_PARAMS used by the SRS TruMedia
    module.
*/
struct srs_TruMedia_wowhd_params_t {
    uint32_t                EnableFlags;
   /**< Bitfield of macros used to enable the SRS TruMedia WOW HD
        parameters.

        @values
        - #SRS_TRUMEDIA_WOWHD_DOLIMIT
        - #SRS_TRUMEDIA_WOWHD_DOSRS3D
        - #SRS_TRUMEDIA_WOWHD_DOTB
        - #SRS_TRUMEDIA_WOWHD_DOSATB
        - #SRS_TRUMEDIA_WOWHD_DOFOCUS
        - #SRS_TRUMEDIA_WOWHD_DODEF
        - #SRS_TRUMEDIA_WOWHD_TBMODE
        - #SRS_TRUMEDIA_WOWHD_SRSMODE_MASK
        - #SRS_TRUMEDIA_WOWHD_SRSMODE_MONO
        - #SRS_TRUMEDIA_WOWHD_SRSMODE_SINGLE
        - #SRS_TRUMEDIA_WOWHD_SRSMODE_STEREO
        - #SRS_TRUMEDIA_WOWHD_SRSMODE_XTREME
        - #SRS_TRUMEDIA_WOWHDX_DOHPF
        - #SRS_TRUMEDIA_WOWHDX_DOXOVER
        - #SRS_TRUMEDIA_WOWHDX_DOWDSRD

        The values are a bitwise OR of any of these macros. When a bit
        corresponding to a particular macro is set, the processing block
        associated with that macro is enabled. */

   uint16_t             Gain_Input;
   /**< Gain (in Q15 format) applied to the signal before processing. */

   uint16_t             Gain_Output;
   /**< Gain (in Q15 format) applied to the signal after processing. */

   uint16_t             Gain_Bypass;
   /**< Currently not used. */

   uint16_t             Focus_Level;
   /**< Level of focus effect (in Q15 format). */

   uint16_t             Def_Level;
   /**< Level of definition effect (in Q15 format). */

   uint16_t             Center_Level;
   /**< SRS 3D Center control (in Q15 format). */

   uint16_t             Space_Level;
   /**< SRS 3D Space control (in Q15 format). */

   uint16_t             Reserved;
   /**< This field must be set to zero. */

   uint32_t             Limit_Level;
   /**< Level of the limiter (in Q30 format). */

   uint16_t             TruBass_Level;
   /**< Level of the TruBass effect (in Q15 format). */

   uint16_t             TruBass_Compress;
   /**< Level of the TruBass compressor (in Q15 format). */

   uint32_t             TruBass_Coefs[16];
   /**< Array of TruBass coefficients. */

   uint32_t                Xhp_Coefs[16];
   /**< Array of crossover high pass filter coefficients. */

   uint32_t                Xlp_Coefs[16];
   /**< Array of crossover low pass filter coefficients. */

   uint32_t                Tbhp_Coefs[16];
   /**< Array of TruBass high pass filter coefficients. */

   uint32_t                Tbhp_order;
   /**< TruBass high pass filter order. */

   uint16_t                Wdsrd_Center_Gain;
   /**< WideSurround center gain.  */

   uint16_t                Wdsrd_Spk_Sep_Level;
   /**< WideSurround speaker separation level. */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_wowhd_params_t */

/** @addtogroup audiopp_module_srs_trumedia
@{ */
/** ID of the CS Headphone configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_cshp_params_t}
    @table{weak__srs__trumedia__cshp__params__t}
*/
#define APPI_SRS_TRUMEDIA_CSHP_PARAMS                 0x10005013

/* The following are bit fields for the EnableFlags field in
 * srs_TruMedia_cshp_params_t defined below*/

/** Limiter is enabled. */
#define SRS_TRUMEDIA_CSHP_DOLIMIT       0x0001

/** Dialog enhancement is enabled. */
#define SRS_TRUMEDIA_CSHP_DODIALOG      0x0002

/** TruBass is enabled. */
#define SRS_TRUMEDIA_CSHP_DOTB          0x0004

/** TruBass Split Analysis is active. */
#define SRS_TRUMEDIA_CSHP_DOSATB        0x0008

/** Circle Surround<sup>&reg;</sup> (CS) decoder is enabled. */
#define SRS_TRUMEDIA_CSHP_DODECODE      0x0010

/** CS decoding is active when set; passive matrix decoding when not set. */
#define SRS_TRUMEDIA_CSHP_DECODEMODE    0x0020

/** Definition is enabled. */
#define SRS_TRUMEDIA_CSHP_DODEF         0x0040

/** TruBass is stereo when set, and mono when not set. */
#define SRS_TRUMEDIA_CSHP_TBMODE        0x0080

/** @} */ /* end_addtogroup audiopp_module_srs_trumedia */

typedef struct srs_TruMedia_cshp_params_t srs_TruMedia_cshp_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_cshp_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_CSHP_PARAMS parameters used by
    the SRS TruMedia module.
*/
struct srs_TruMedia_cshp_params_t {
    uint32_t                EnableFlags;
   /**< Bitfield of macros used to specify how SRS TruMedia CSHP is
        enabled.

        @values
        - #SRS_TRUMEDIA_CSHP_DOLIMIT
        - #SRS_TRUMEDIA_CSHP_DODIALOG
        - #SRS_TRUMEDIA_CSHP_DOTB
        - #SRS_TRUMEDIA_CSHP_DOSATB
        - #SRS_TRUMEDIA_CSHP_DODECODE
        - #SRS_TRUMEDIA_CSHP_DECODEMODE
        - #SRS_TRUMEDIA_CSHP_DODEF
        - #SRS_TRUMEDIA_CSHP_TBMODE

        The values are a bitwise OR of any of these macros. When a bit
        corresponding to a particular macro is set, the processing block
        associated with that macro is enabled. */

   uint16_t             Gain_Input;
   /**< Specifies the gain (in Q15 format) applied to the signal before
        processing. */

   uint16_t             Gain_Output;
   /**< Specifies the gain (in Q15 format) applied to the signal after
        processing. */

   uint16_t             Gain_Bypass;
   /**< Currently not used. */

   uint16_t             Dialog_Level;
   /**< Specifies the level of dialog enhancement (in Q15 format). */

   uint16_t             Def_Level;
   /**< Specifies the level of definition effect (in Q15 format). */

   uint16_t             Reserved;
   /**< This field must be set to zero. */

   uint32_t             Limit_Level;
   /**< Specifies the limiter's limit (in Q30 format). */

   uint16_t             TruBass_Level;
   /**< Specifies the level of TruBass effect (in Q15 format). */

   uint16_t             TruBass_Compress;
   /**< Specifies the TruBass compressor's level (in Q15 format). */

   uint32_t             TruBass_Coefs[16];
   /**< TruBass coefficients. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_cshp_params_t */

/** @ingroup audiopp_module_srs_trumedia
    ID of the high pass filter configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_hpf_params_t}
    @table{weak__srs__trumedia__hpf__params__t} @newpage
*/
#define APPI_SRS_TRUMEDIA_HPF_PARAMS                  0x10005014

typedef struct srs_TruMedia_hpf_params_t srs_TruMedia_hpf_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_hpf_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_HPF_PARAMS parameters used by the
    SRS TruMedia module.
*/
struct srs_TruMedia_hpf_params_t {
    uint32_t                Order;
   /**< Order of the filter. */

   uint32_t             Coefs[26];
   /**< High pass filter coefficients. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_hpf_params_t */

/** @addtogroup audiopp_module_srs_trumedia
@{ */
/** ID of the Adaptive Equalizer (AEQ) configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_aeq_params_t}
    @table{weak__srs__trumedia__aeq__params__t}
*/
#define APPI_SRS_TRUMEDIA_AEQ_PARAMS                  0x10005015

/* The following are bit fields for the EnableFlags field in
 * srs_TruMedia_aeq_params_t defined below*/

/** Left/right link channel is enabled. Regardless of the right channel
    values, the left channel values are copied to the right channel. */
#define SRS_TRUMEDIA_AEQ_LR_LINK  0x00000001

/** Left channel is enabled (Do Left == Enable left). */
#define SRS_TRUMEDIA_AEQ_DOL      0x00000002

/** Right channel is enabled (Do Right == Enable right). */
#define SRS_TRUMEDIA_AEQ_DOR      0x00000004

/** Left channel (band 0) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB0      0x00000010

/** Left channel (band 1) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB1      0x00000020

/** Left channel (band 2) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB2      0x00000040

/** Left channel (band 3) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB3      0x00000080

/** Left channel (band 4) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB4      0x00000100

/** Left channel (band 5) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB5      0x00000200

/** Left channel (band 6) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB6      0x00000400

/** Left channel (band 7) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB7      0x00000800

/** Left channel (band 8) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB8      0x00001000

/** Left channel (band 9) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB9      0x00002000

/** Left channel (band 10) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB10     0x00004000

/** Left channel (band 11) is enabled. */
#define SRS_TRUMEDIA_AEQ_LB11     0x00008000

/** Right channel (band 0) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB0      0x00010000

/** Right channel (band 1) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB1      0x00020000

/** Right channel (band 2) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB2      0x00040000

/** Right channel (band 3) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB3      0x00080000

/** Right channel (band 4) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB4      0x00100000

/** Right channel (band 5) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB5      0x00200000

/** Right channel (band 6) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB6      0x00400000

/** Right channel (band 7) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB7      0x00800000

/** Right channel (band 8) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB8      0x01000000

/** Right channel (band 9) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB9      0x02000000

/** Right channel (band 10) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB10     0x04000000

/** Right channel (band 11) is enabled. */
#define SRS_TRUMEDIA_AEQ_RB11     0x08000000

/** Dolby FIR filter is enabled. */
#define SRS_TRUMEDIA_AEQ_DOFIR      0x10000000

/** Select between inbuilt (the table in the code) or a coefficient read from
    a file. */
#define SRS_TRUMEDIA_AEQ_FIR_SELECT 0x20000000

/** @} */ /* end_addtogroup audiopp_module_srs_trumedia */

typedef struct srs_TruMedia_aeq_params_t srs_TruMedia_aeq_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_aeq_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_AEQ_PARAMS parameters used by the
    SRS TruMedia module.
*/
struct srs_TruMedia_aeq_params_t {
   uint32_t             EnableFlags;
   /**< Bitfield of macros used to enable the SRS TruMedia AEQ parameters.

        @values
        - #SRS_TRUMEDIA_AEQ_LR_LINK
        - #SRS_TRUMEDIA_AEQ_DOL
        - #SRS_TRUMEDIA_AEQ_DOR
        - #SRS_TRUMEDIA_AEQ_LB0 through #SRS_TRUMEDIA_AEQ_LB11
        - #SRS_TRUMEDIA_AEQ_RB0 through #SRS_TRUMEDIA_AEQ_RB11
        - #SRS_TRUMEDIA_AEQ_DOFIR
        - #SRS_TRUMEDIA_AEQ_FIR_SELECT

        The values are a bitwise OR of any of these macros. When a bit that
        corresponds to a particular macro is set, the processing block
        associated with that macro is enabled. */

   uint16_t             Gain_Input;
   /**< Specifies the gain (in Q12 format) applied to the signal before
        processing. */

   uint16_t             Gain_Output;
   /**< Specifies the gain (in Q12 format) applied to the signal after
        processing. */

   uint16_t             Gain_Bypass;
   /**< Currently not used. */

   uint16_t             Reserved;
   /**< This field must be set to zero. */

   uint32_t              L_Coefs[74];
   /**< Left-channel AEQ coefficients (6*(nBands)+2) -- DO NOT MODIFY. */

   uint32_t              R_Coefs[74];
   /**< Right-channel AEQ coefficients (6*(nBands)+2) -- DO NOT MODIFY. */

   uint16_t              FIR_Coefs[2048];
   /**< FIR AEQ coefficients -- DO NOT MODIFY.
   
        FIR filters are used by the headphone equalizer. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_aeq_params_t */

/** @ingroup audiopp_module_srs_trumedia
    ID of the hard limiter configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_hl_params_t}
    @table{weak__srs__trumedia__hl__params__t}
*/
#define APPI_SRS_TRUMEDIA_HL_PARAMS                   0x10005016

typedef struct srs_TruMedia_hl_params_t srs_TruMedia_hl_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_hl_params_t
@{ */
/* Payload of the APPI_SRS_TRUMEDIA_HL_PARAMS parameters used by the
    SRS TruMedia module.
*/
struct srs_TruMedia_hl_params_t {
   uint16_t                Gain_Input;
   /**< Specifies the gain (in Q13 format) applied to the signal before
        processing. */

   uint16_t             Gain_Output;
   /**< Specifies the gain (in Q13 format) applied to the signal after
        processing. */

   uint16_t             Gain_Bypass;
   /**< Currently not used. */

   uint16_t             Reserved_1;
   /**< This field must be set to zero. */

   int32_t              Delay_Len;
   /**< Number of samples in the delay buffer. */

   uint32_t             Boost;
   /**< Specifies the gain (in Q23 format) applied to the signal before
        limiting. */

   uint16_t             Limit;
   /**< Specifies the limiter's limit (in Q15 format). */

   uint16_t             Reserved_2;
   /**< This field must be set to zero. */

   uint32_t             DecaySmooth;
   /**< When nonzero, decay smoothing is enabled. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_hl_params_t */

/** @ingroup audiopp_module_srs_trumedia
    ID of the Graphic Equalizer configuration parameters used by
    #APPI_SRS_TRUMEDIA_MODULE_ID.

    @msgpayload{srs_TruMedia_geq_params_t}
    Do not fill this structure directly. An SRS Library at the operating system
    level generates this structure.
    @tablens{weak__srs__trumedia__geq__params__t}
*/
#define APPI_SRS_TRUMEDIA_GEQ_PARAMS                  0x10005017

typedef struct srs_TruMedia_geq_params_t srs_TruMedia_geq_params_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_srs_trumedia_geq_params_t
@{ */
struct srs_TruMedia_geq_params_t{

    int16_t                UserGains[10];
    /**< Gain for the left channel -- DO NOT MODIFY. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_srs_trumedia_geq_params_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_dts_dialnorm
@{ */
/** ID of the DTS Dialogue Normalization (DialNorm) module.
    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_DTS_DIALNORM    0x0001071B

/** ID of the DTS DialNorm Enable parameter used by
    AUDPROC_MODULE_ID_DTS_DIALNORM.

    @msgpayload{audproc_dts_dialnorm_enable_t}
    @table{weak__audproc__dts__dialnorm__enable__t}
*/
#define AUDPROC_PARAM_ID_DTS_DIALNORM_ENABLE    0x0001071C

/** @} */ /* end_addtogroup audiopp_module_dts_dialnorm */

typedef struct audproc_dts_dialnorm_enable_t audproc_dts_dialnorm_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_dts_dialnorm_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DTS_DIALNORM_ENABLE enable_flag parameter
    used by the DialNorm module.
*/
struct audproc_dts_dialnorm_enable_t
{

    uint32_t                  enable_flag;
    /**< Specifies whether DTS DialNorm is enabled.

         @values
         - 0 -- Disable (Default)
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_dts_dialnorm_enable_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_dts_drc
@{ */
/** ID of the DTS Dynamic Range Control (DRC) module.
    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_DTS_DRC    0x0001071D

/** ID of the DTS DRC Ratio parameter used by AUDPROC_MODULE_ID_DTS_DRC.

    @msgpayload{audproc_dts_drc_param_t}
    @table{weak__audproc__dts__drc__param__t}
*/
#define AUDPROC_PARAM_ID_DTS_DRC_RATIO    0x0001071E

/** @} */ /* end_addtogroup audiopp_module_dts_drc */

typedef struct audproc_dts_drc_param_t audproc_dts_drc_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_dts_drc_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DTS_DRC_RATIO parameter used by the
    DRC module.
*/
struct audproc_dts_drc_param_t
{

    uint32_t                  drc_ratio;
    /**< Specifies the DTS DRC_ratio used by the DRC.

         @values 0  to 100

         If this value is greater than 4, the DRC is enabled; otherwise, it is
         bypassed. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_dts_drc_param_t */
/** @endcond */

/** @addtogroup audiopp_module_resampler
@{ */
/** ID of the Resampler module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DYNAMIC_RESAMPLER_MODE_CONFIG
    - #AUDPROC_PARAM_ID_ENABLE_HIGH_THD_RESAMPLER
 */
#define AUDPROC_MODULE_ID_RESAMPLER   0x00010719

/** ID of the Dynamic Resampler Mode Configuration parameter used by
    AUDPROC_MODULE_ID_RESAMPLER.

    @msgpayload{audproc_dynamic_resampler_mode_config_t}
    @table{weak__audproc__dynamic__resampler__mode__config__t} @newpage
*/
#define AUDPROC_PARAM_ID_DYNAMIC_RESAMPLER_MODE_CONFIG   0x00010911

/** ID of the Enable Low Degradation Resampler parameter used by
    #AUDPROC_MODULE_ID_RESAMPLER.

    @note1hang Although the parameter ID indicates HIGH_THD, it is actually
               defining the low threshold.

    @msgpayload{audproc_high_thd_resamp_enable_t}
    @table{weak__audproc__high__thd__resamp__enable__t}
*/
#define AUDPROC_PARAM_ID_ENABLE_HIGH_THD_RESAMPLER 0x0001071A

/** @} */ /* end_addtogroup audiopp_module_resampler */

/* Structure for setting the dynamic mode configuration for the Resampler. */
typedef struct audproc_dynamic_resampler_mode_config_t audproc_dynamic_resampler_mode_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_dynamic_resampler_mode_config_t
@{ */
/* Payload of the AUDPROC_MODULE_ID_RESAMPLER dynamic mode configuration parameter used by
    the Resampler module.
*/
struct audproc_dynamic_resampler_mode_config_t
{
    uint8_t  dynamic_mode;
    /**< Specifies the mode of operation for the dynamic re-sampler.

         @values
         - 0 -- Generic resampling (Default)
         - 1 -- Dynamic resampling @tablebulletend */

    uint8_t delay_type;
    /**< Specifies the delay type for the Dynamic Resampling mode.

         @values
         - 0 -- High delay with smooth transition (Default)
         - 1 -- Low delay with visible transitional phase distortion

         This delay_type value has significance only if the dynamic_mode value
         is set to 1. */

    uint16_t reserved;
    /**< Clients must set this field to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_dynamic_resampler_mode_config_t  */


/* Structure for enabling the configuration parameter for high thd resampler. */
typedef struct audproc_high_thd_resamp_enable_t audproc_high_thd_resamp_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_high_thd_resamp_enable_t
@{ */
/* Payload of the AUDPROC_MODULE_ID_RESAMPLER enable_flag parameter used by
    the Resampler module.
*/
struct audproc_high_thd_resamp_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the resampler is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable

         This resampler is applicable only for the input sampling rate of
         44.1 kHz and output sampling rate of 48 kHz. It is not supported for
         the other sampling rates.

         If this resampler is enabled and input sampling and output sampling
         rates are not 44.1 kHz and 48 kHz respectively, the generic resampler
         is used.

         If this resampler is disabled, the generic resampler is used for all
         sampling rate conversions. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_high_thd_resamp_enable_t  */

/** @cond OEM_only */
/** @addtogroup audiopp_module_downmixer
@{ */
/** ID for the Downmixer module. This module does not have any
    parameters.
*/
#define AUDPROC_MODULE_ID_DOWNMIX     0x00010721

/** ID for the Sample Slipping/stuffing module. This module does
    not have any parameters.
*/
#define AUDPROC_MODULE_ID_SAMPLESLIP  0x00010722

/** @} */ /* end_addtogroup audiopp_module_downmixer */
/** @endcond */

typedef struct audproc_module_info_t audproc_module_info_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_module_info_t
@{ */
/* Defines the modules used by the ASM_CMD_ADD_TOPOLOGIES and
    ADM_CMD_ADD_TOPOLOGIES_V5 commands.
*/
struct audproc_module_info_t
{
   uint32_t module_id;
   /**< ID of the module to be created.

        @values Any valid module ID */

   uint32_t use_lpm;
   /**< Specifies whether to put this module in low power memory.

        @values
        - 0 -- Do not put this module in low power memory
        - 1 -- Put this module in low power memory

        If there is insufficient low power memory, this module is placed in
        the default memory pool.*/

   uint8_t  init_params[16];
   /**< Array of initialization parameters passed to the module when it is
        created.

        This array of 16 bytes is sent to the getsize() and init() methods of
        the module. The interpretation of this information is module specific. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_module_info_t */

typedef struct audproc_topology_definition_t audproc_topology_definition_t;

#include "adsp_begin_pack.h"

/** @ingroup asmsvc_cmd_add_topos
    Maximum number of modules supported in a custom topology.
*/
#define AUDPROC_MAX_MODULES_PER_TOPOLOGY 16

/** @weakgroup weak_audproc_topology_definition_t
@{ */
/* Defines a custom topology that is to be added to the aDSP. This structure
    is followed by num_modules of audproc_module_info_t.
*/
struct audproc_topology_definition_t
{
   uint32_t topology_id;
   /**< ID of this custom topology.

        @values 0x10000000-0x1FFFFFFF */

   uint32_t num_modules;
   /**< Number of modules in this topology.

        @values 0 to #AUDPROC_MAX_MODULES_PER_TOPOLOGY */

   audproc_module_info_t module_info[AUDPROC_MAX_MODULES_PER_TOPOLOGY];
   /**< Array of module information structures with 16 elements.

        The order of the elements in this array specify the order in which the
        modules will be connected in the topology, from source to sink.

        Only the first num_modules elements of this array are required.
        The rest of the elements are ignored. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_topology_definition_t */

typedef struct audproc_custom_topologies_t audproc_custom_topologies_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_custom_topologies_t
@{ */
/* Header structure for the custom topologies command buffer. This structure
    is followed by num_topologies of audproc_topology_definition_t.
*/
struct audproc_custom_topologies_t
{
   uint32_t num_topologies;
   /**< Specifies the number of topologies in this command.

        @values Any nonzero number */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_custom_topologies_t */

/** @cond OEM_only */
/** @addtogroup audiopp_module_compr_latency
@{ */
/** ID of the Compressed Latency module.

    This module introduces non-negative delays in the compressed data path,
    achieved by introducing IEC61937 pause bursts for the specified delay.
    When the delay is decreased, data is dropped.

    Because the minimum pause burst duration that is possible depends on the
    format of the compressed data, the minimum delay possible also varies
    according to the format. For AC3/EAC3, the minimum is three samples
    duration.

    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_COMPRESSED_LATENCY            0x0001076E

/** ID of the Delay parameter used by AUDPROC_MODULE_ID_COMPRESSED_LATENCY.

    @msgpayload{audproc_comp_latency_param_t}
    @table{weak__audproc__comp__latency__param__t}
*/
#define AUDPROC_PARAM_ID_COMPRESSED_LATENCY             0x0001076F

/** @} */ /* end_addtogroup audiopp_module_compr_latency */

/* Structure for latency parameter in compressed data paths. */
typedef struct audproc_compressed_latency_param_t audproc_compressed_latency_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_comp_latency_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_COMPRESSED_LATENCY parameter used by
    AUDPROC_MODULE_ID_COMPRESSED_LATENCY.
*/
struct audproc_compressed_latency_param_t
{
    uint32_t                  delay_us;
    /**< Delay in microseconds.

         @values 0 to 100000

         This value is the amount of delay introduced by the Latency module.
         It must be greater than zero. If the value is zero, this module is
         disabled.

         The actual resolution of the delay value depends on the compressed
         data format. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_comp_latency_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_compr_mute
@{ */
/** ID of the Compressed Mute module.
    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_COMPRESSED_MUTE    0x00010770

/** ID of the Compressed Mute parameter used by
    AUDPROC_MODULE_ID_COMPRESSED_MUTE.

    @msgpayload{audproc_compressed_mute_param_t}
    @table{weak__audproc__compressed__mute__param__t}
*/
#define AUDPROC_PARAM_ID_COMPRESSED_MUTE     0x00010771

/** @} */ /* end_addtogroup audiopp_module_compr_mute */

/* Structure for Compressed Mute parameter muteFlag. */
typedef struct audproc_compressed_mute_param_t audproc_compressed_mute_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_compressed_mute_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_COMPRESSED_MUTE muteFlag parameter used by
    AUDPROC_MODULE_ID_COMPRESSED_MUTE.
*/
struct audproc_compressed_mute_param_t
{
    uint32_t                  mute_flag;
    /**< Specifies whether compressed mute is enabled.

         @values 0 to 4294967295
         - 0 -- Disable (Default)
         - Any nonzero value -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak__audproc_compressed_mute_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_delay_latency
@{ */
/** ID of the Delay/Latency module on the LPCM data path.

    This module introduces the specified amount of delay in the audio path.
    If the delay is increased, silence is inserted. If the delay is decreased,
    data is dropped.

    There are no smooth transitions. The resolution of the delay applied is
    limited by the period of a single sample. Qualcomm recommends muting the
    device path when the delay is changed (to avoid glitches).

    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_DELAY                    0x00010772

/** ID of the Delay parameter used by AUDPROC_MODULE_ID_DELAY.

    @msgpayload{audproc_delay_param_t}
    @table{weak__audproc__delay__param__t}
*/
#define AUDPROC_PARAM_ID_DELAY                     0x00010773

/** @} */ /* end_addtogroup audiopp_module_delay_latency */

/* Structure for delay parameter in LPCM data paths. */
typedef struct audproc_delay_param_t audproc_delay_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_delay_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DELAY parameter used by
    AUDPROC_MODULE_ID_DELAY.
*/
struct audproc_delay_param_t
{
    uint32_t                  delay_us;
    /**< Delay in microseconds.

         @values 0 to 100000

         The amount of delay must be greater than zero.  If the value is
         zero, this module is disabled.

         The actual resolution of the delay is limited by the period of a
         single audio sample. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_delay_param_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_bass_boost
@{ */
/** ID of the Bass Boost module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_BASS_BOOST_ENABLE
    - #AUDPROC_PARAM_ID_BASS_BOOST_MODE
    - #AUDPROC_PARAM_ID_BASS_BOOST_STRENGTH
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_BASS_BOOST                             0x000108A1

/** ID of the Bass Boost Enable parameter used by
    AUDPROC_MODULE_ID_BASS_BOOST.

    @msgpayload{audproc_bass_boost_enable_t}
    @table{weak__audproc__bass__boost__enable__t}
*/
#define AUDPROC_PARAM_ID_BASS_BOOST_ENABLE                       0x000108A2

/** ID of the Bass Boost Mode parameter used by
    AUDPROC_MODULE_ID_BASS_BOOST.

    @msgpayload{audproc_bass_boost_mode_t}
    @table{weak__audproc__bass__boost__mode__t} @newpage
*/
#define AUDPROC_PARAM_ID_BASS_BOOST_MODE                         0x000108A3

/** ID of the Bass Boost Strength parameter used by
    #AUDPROC_MODULE_ID_BASS_BOOST.

    @msgpayload{audproc_bass_boost_strength_t}
    @table{weak__audproc__bass__boost__strength__t}
*/
#define AUDPROC_PARAM_ID_BASS_BOOST_STRENGTH                     0x000108A4

/** @} */ /* end_addtogroup audiopp_module_bass_boost */

/* Structure for the enable parameter of Bass Boost module. */
typedef struct audproc_bass_boost_enable_t audproc_bass_boost_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_bass_boost_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_BASS_BOOST_ENABLE parameter used by the
    Bass Boost module.
*/
struct audproc_bass_boost_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether bass boost is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_bass_boost_enable_t */

/* Structure for the mode parameter of Bass Boost module. */
typedef struct audproc_bass_boost_mode_t audproc_bass_boost_mode_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_bass_boost_mode_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_BASS_BOOST_MODE parameter used by the
    Bass Boost module.
*/
struct audproc_bass_boost_mode_t
{
    uint32_t                  bass_boost_mode;
    /**< Specifies the bass boost mode. This parameter is device dependent.

         @values
         - 0 -- Physical boost; used by the headphone
         - 1 -- Virtual boost; used by small speakers

         Physical boost enhances the low frequency contents. Virtual boost
         creates harmonics of the low frequency contents (PBE).
         
         Currently, only Physical Boost mode is supported. Virtual Boost mode
         is not supported; it is reserved for future use. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_bass_boost_mode_t */

/* Structure for the strength parameter of Bass Boost module. */
typedef struct audproc_bass_boost_strength_t audproc_bass_boost_strength_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_bass_boost_strength_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_BASS_BOOST_STRENGTH parameter used by the
    Bass Boost module.
*/
struct audproc_bass_boost_strength_t
{
    uint32_t                  strength;
    /**< Specifies the effects of bass boost. This parameter affects the audio
         stream and is device independent.

         @values
         - 0 -- No effects
         - 1000 -- Maximum effects @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_bass_boost_strength_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_virtualizer
@{ */
/** ID of the Virtualizer module. This module supports the
    following parameter IDs:
    - #AUDPROC_PARAM_ID_VIRTUALIZER_ENABLE
    - #AUDPROC_PARAM_ID_VIRTUALIZER_STRENGTH
    - #AUDPROC_PARAM_ID_VIRTUALIZER_OUT_TYPE
    - #AUDPROC_PARAM_ID_VIRTUALIZER_GAIN_ADJUST
    - #AUDPROC_PARAM_ID_ENABLE 
*/
#define AUDPROC_MODULE_ID_VIRTUALIZER                            0x000108A5

/** ID of the Virtualizer Enable parameter used by
    AUDPROC_MODULE_ID_VIRTUALIZER.

    @msgpayload{audproc_virtualizer_enable_t}
    @table{weak__audproc__virtualizer__enable__t}
*/
#define AUDPROC_PARAM_ID_VIRTUALIZER_ENABLE                      0x000108A6

/** ID of the Virtualizer Strength parameter used by
    AUDPROC_MODULE_ID_VIRTUALIZER.

    @msgpayload{audproc_virtualizer_strength_t}
    @table{weak__audproc__virtualizer__strength__t} @newpage
*/
#define AUDPROC_PARAM_ID_VIRTUALIZER_STRENGTH                    0x000108A7

/** ID of the Virtualizer Out Type parameter used by
    #AUDPROC_MODULE_ID_VIRTUALIZER.

    @msgpayload{audproc_virtualizer_out_type_t}
    @table{weak__audproc__virtualizer__out__type__t}
*/
#define AUDPROC_PARAM_ID_VIRTUALIZER_OUT_TYPE                    0x000108A8

/** ID of the Virtualizer Gain Adjust parameter used by
    #AUDPROC_MODULE_ID_VIRTUALIZER.

    @msgpayload{audproc_virtualizer_gain_adjust_t}
    @table{weak__audproc__virtualizer__gain__adjust__t}
*/
#define AUDPROC_PARAM_ID_VIRTUALIZER_GAIN_ADJUST                 0x000108A9

/** @} */ /* end_addtogroup audiopp_module_virtualizer */

/* Structure for the enable parameter of Virtualizer module. */
typedef struct audproc_virtualizer_enable_t audproc_virtualizer_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_virtualizer_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VIRTUALIZER_ENABLE parameter used by the
    Virtualizer module.
*/
struct audproc_virtualizer_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the virtualizer is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_virtualizer_enable_t */

/* Structure for the strength parameter of VIRTUALIZER module. */
typedef struct audproc_virtualizer_strength_t audproc_virtualizer_strength_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_virtualizer_strength_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VIRTUALIZER_STRENGTH parameter used by the
    Virtualizer module.
*/
struct audproc_virtualizer_strength_t
{
    uint32_t                  strength;
    /**< Specifies the effects of the virtualizer. This parameter affects the
         audio stream and is device independent.

         @values 0 to 1000, where:
         - 0 -- No effects
         - 1000 -- Maximum effects @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_virtualizer_strength_t */

/* Structure for the strength parameter of VIRTUALIZER module. */
typedef struct audproc_virtualizer_out_type_t audproc_virtualizer_out_type_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_virtualizer_out_type_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VIRTUALIZER_OUT_TYPE parameter used by the
    Virtualizer module.
*/
struct audproc_virtualizer_out_type_t
{
    uint32_t                  out_type;
    /**< Specifies the output device type of the virtualizer. This parameter is
         it is device dependent.

         @values
         - 0 -- Headphone
         - 1 -- Desktop speakers @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_virtualizer_out_type_t */

/* Structure for the strength parameter of VIRTUALIZER module. */
typedef struct audproc_virtualizer_gain_adjust_t audproc_virtualizer_gain_adjust_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_virtualizer_gain_adjust_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VIRTUALIZER_GAIN_ADJUST parameter used by the
    Virtualizer module.
*/
struct audproc_virtualizer_gain_adjust_t
{
    int32_t                  gain_adjust;
    /**< Specifies the overall gain adjustment of virtualizer outputs. This
         parameter is device dependent.

         @values -600 to +600 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_virtualizer_gain_adjust_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_reverb
@{ */
/** ID of the Reverberation module. This module supports the following
    parameter IDs:
    - #AUDPROC_PARAM_ID_REVERB_ENABLE
    - #AUDPROC_PARAM_ID_REVERB_MODE
    - #AUDPROC_PARAM_ID_REVERB_PRESET
    - #AUDPROC_PARAM_ID_REVERB_WET_MIX
    - #AUDPROC_PARAM_ID_REVERB_GAIN_ADJUST
    - #AUDPROC_PARAM_ID_REVERB_ROOM_LEVEL
    - #AUDPROC_PARAM_ID_REVERB_ROOM_HF_LEVEL
    - #AUDPROC_PARAM_ID_REVERB_DECAY_TIME
    - #AUDPROC_PARAM_ID_REVERB_DECAY_HF_RATIO
    - #AUDPROC_PARAM_ID_REVERB_REFLECTIONS_LEVEL
    - #AUDPROC_PARAM_ID_REVERB_REFLECTIONS_DELAY
    - #AUDPROC_PARAM_ID_REVERB_LEVEL
    - #AUDPROC_PARAM_ID_REVERB_DELAY
    - #AUDPROC_PARAM_ID_REVERB_DIFFUSION
    - #AUDPROC_PARAM_ID_REVERB_DENSITY
    - #AUDPROC_PARAM_ID_ENABLE 

    All parameter IDs are device independent.
*/
#define AUDPROC_MODULE_ID_REVERB                          0x000108AA

/** ID of the Reverberation Enable parameter used by AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_enable_t}
    @table{weak__audproc__reverb__enable__t} @newpage
*/
#define AUDPROC_PARAM_ID_REVERB_ENABLE                    0x000108AB

/** ID of the Reverberation Mode parameter used by #AUDPROC_MODULE_ID_REVERB.

    This parameter must be initialized once when the library is created.
    The mode cannot be changed after initialization. Hence, this parameter
    ID is used for Get Parameter calls only.

    @msgpayload{audproc_reverb_mode_t}
    @table{weak__audproc__reverb__mode__t}

    @par Insert effects
    One source is in and one source is out. The input/output channels match so
    the reverberation output is a mixture of original (dry) sound and
    reverberation (wet) sound. For example, applying reverberation to a music
    stream.

    @par Auxiliary effects
    Multiple input sources and one global reverberation engine. Each input
    source makes a copy of itself with its own (Q15) reverberation send gain
    applied. The copies are mixed internally inside the reverberation library.
    @par
    The sound sources can have different numbers of channels, and they do not
    need to match the reverberation output numbers of channels.
    @par
    After mixing all inputs, reverberation generates dense echoes (wet sound).
    The reverberation (wet) output must be mixed somewhere outside the
    reverberation library with the direct (dry) sound. For example, applying
    one global reverberation for gaming or multi-track MIDI. @newpage
*/
#define AUDPROC_PARAM_ID_REVERB_MODE                      0x000108AC

/** ID of the Reverberation Preset parameter used by #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_preset_t}
    @table{weak__audproc__reverb__preset__t}

    The following table maps the OpenSL presets to the Qualcomm Hexagon
    Multimedia presets.
    @inputtable{Reverb_preset_mapping.tex}
*/
#define AUDPROC_PARAM_ID_REVERB_PRESET                    0x000108AD

/** ID of the Reverberation Wet Mix parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_wet_mix_t}
    @table{weak__audproc__reverb__wet__mix__t} @newpage
*/
#define AUDPROC_PARAM_ID_REVERB_WET_MIX                   0x000108AE

/** ID of the Reverberation Gain Adjust parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_gain_adjust_t}
    @table{weak__audproc__reverb__gain__adjust__t}
*/
#define AUDPROC_PARAM_ID_REVERB_GAIN_ADJUST               0x000108AF

/** ID of the Reverberation Room Level parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_room_level_t}
    @table{weak__audproc__reverb__room__level__t}
*/
#define AUDPROC_PARAM_ID_REVERB_ROOM_LEVEL                0x000108B0

/** ID of the Reverberation Room High Frequency Level parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_room_hf_level_t}
    @table{weak__audproc__reverb__room__hf__level__t}
*/
#define AUDPROC_PARAM_ID_REVERB_ROOM_HF_LEVEL             0x000108B1

/** ID of the Reverberation Decay Time parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_decay_time_t}
    @table{weak__audproc__reverb__decay__time__t} @newpage
*/
#define AUDPROC_PARAM_ID_REVERB_DECAY_TIME                0x000108B2

/** ID of the Reverberation Decay High Frequency Ratio parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_decay_hf_ratio_t}
    @table{weak__audproc__reverb__decay__hf__ratio__t}
*/
#define AUDPROC_PARAM_ID_REVERB_DECAY_HF_RATIO            0x000108B3

/** ID of the Reverberation Reflections Level parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_reflections_level_t}
    @table{weak__audproc__reverb__reflections__level__t}
*/
#define AUDPROC_PARAM_ID_REVERB_REFLECTIONS_LEVEL         0x000108B4

/** ID of the Reverberation Reflections Delay parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_reflections_delay_t}
    @table{weak__audproc__reverb__reflections__delay__t}
*/
#define AUDPROC_PARAM_ID_REVERB_REFLECTIONS_DELAY         0x000108B5

/** ID of the Reverberation Level parameter used by #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_level_t}
    @table{weak__audproc__reverb__level__t} @newpage
*/
#define AUDPROC_PARAM_ID_REVERB_LEVEL                      0x000108B6

/** ID of the Reverberation Delay parameter used by #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_delay_t}
    @table{weak__audproc__reverb__delay__t}
*/
#define AUDPROC_PARAM_ID_REVERB_DELAY                      0x000108B7

/** ID of the Reverberation Diffusion parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_diffusion_t}
    @table{weak__audproc__reverb__diffusion__t}
*/
#define AUDPROC_PARAM_ID_REVERB_DIFFUSION                  0x000108B8

/** ID of the Reverberation Density parameter used by
    #AUDPROC_MODULE_ID_REVERB.

    @msgpayload{audproc_reverb_density_t}
    @table{weak__audproc__reverb__density__t}
*/
#define AUDPROC_PARAM_ID_REVERB_DENSITY                    0x000108B9

/** @} */ /* end_addtogroup audiopp_module_reverb */

/* Structure for the enable parameter of Reverb module. */
typedef struct audproc_reverb_enable_t audproc_reverb_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_ENABLE parameter used by the
    Reverb module.
*/
struct audproc_reverb_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether reverberation is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_enable_t */

/* Structure for the mode parameter of Reverb module. */
typedef struct audproc_reverb_mode_t audproc_reverb_mode_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_mode_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_MODE parameter used by the
    Reverb module.
*/
struct audproc_reverb_mode_t
{
    uint32_t                  reverb_mode;
    /**< Specifies the reverberation topology mode.

         @values
         0 -- Insert Effects mode. Reverberation is cascaded with other audio
              processing modules.
         1 -- Auxiliary Effects mode. Reverberation runs in parallel to other
              processing modules.

         The #AUDPROC_COPP_TOPOLOGY_ID_AUDIO_PLUS_HEADPHONE and
         #AUDPROC_COPP_TOPOLOGY_ID_AUDIO_PLUS_SPEAKER topologies support only
         Insert Effects mode.
         For Auxiliary Effect mode, a custom topology must be defined. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_mode_t */

/** @addtogroup audiopp_module_reverb
@{ */
/** User-customized preset (with environmental reverberation parameters
    specified individually).
*/
#define  AUDPROC_REVERB_PRESET_CUSTOM            0

/** Simulates an environment in a room. */
#define  AUDPROC_REVERB_PRESET_ROOM              1

/** Simulates an environment in a bathroom. */
#define  AUDPROC_REVERB_PRESET_BATHROOM          2

/** Simulates an environment in a concert hall. */
#define  AUDPROC_REVERB_PRESET_CONCERTHALL       3

/** Simulates an environment in a cave. */
#define  AUDPROC_REVERB_PRESET_CAVE              4

/** Simulates an environment in an arena. */
#define  AUDPROC_REVERB_PRESET_ARENA             5

/** Simulates an environment in a forest. */
#define  AUDPROC_REVERB_PRESET_FOREST            6

/** Simulates an environment in a city. */
#define  AUDPROC_REVERB_PRESET_CITY              7

/** Simulates an environment in the mountains (open air). */
#define  AUDPROC_REVERB_PRESET_MOUNTAINS         8

/** Simulates an environment under the water. */
#define  AUDPROC_REVERB_PRESET_UNDERWATER        9

/** Simulates an environment in an auditorium. */
#define  AUDPROC_REVERB_PRESET_AUDITORIUM        10

/** Simulates an environment in an alley. */
#define  AUDPROC_REVERB_PRESET_ALLEY             11

/** Simulates an environment in a hallway. */
#define  AUDPROC_REVERB_PRESET_HALLWAY           12

/** Simulates an environment in a hangar. */
#define  AUDPROC_REVERB_PRESET_HANGAR            13

/** Simulates an environment in a living room. */
#define  AUDPROC_REVERB_PRESET_LIVINGROOM        14

/** Simulates an environment in a small room. */
#define  AUDPROC_REVERB_PRESET_SMALLROOM         15

/** Simulates an environment in a medium-sized room. */
#define  AUDPROC_REVERB_PRESET_MEDIUMROOM        16

/** Simulates an environment in a large room. */
#define  AUDPROC_REVERB_PRESET_LARGEROOM         17

/** Simulates an environment in a medium-sized hall. */
#define  AUDPROC_REVERB_PRESET_MEDIUMHALL        18

/** Simulates an environment in a large hall. */
#define  AUDPROC_REVERB_PRESET_LARGEHALL         19

/** Simulates sound being sent to a metal plate, which vibrates back and forth.
    These vibrations are transformed into an audio signal.
*/
#define  AUDPROC_REVERB_PRESET_PLATE             20

/** Simulates a generic reverberation effect. */
#define  AUDPROC_REVERB_PRESET_GENERIC           21

/** Simulates an environment in a padded cell. */
#define  AUDPROC_REVERB_PRESET_PADDEDCELL        22

/** Simulates an environment in a stone room. */
#define  AUDPROC_REVERB_PRESET_STONEROOM         23

/** Simulates an environment in a carpeted hallway. */
#define  AUDPROC_REVERB_PRESET_CARPETEDHALLWAY   24

/** Simulates an environment in a stone corridor. */
#define  AUDPROC_REVERB_PRESET_STONECORRIDOR     25

/** Simulates an environment in a quarry. */
#define  AUDPROC_REVERB_PRESET_QUARRY            26

/** Simulates an environment on an open plain. */
#define  AUDPROC_REVERB_PRESET_PLAIN             27

/** Simulates an environment in a parking lot. */
#define  AUDPROC_REVERB_PRESET_PARKINGLOT        28

/** Simulates an environment in a sewer pipe. */
#define  AUDPROC_REVERB_PRESET_SEWERPIPE         29

/** Synthetic environment preset: drugged. */
#define  AUDPROC_REVERB_PRESET_DRUGGED           30

/** Synthetic environment preset: dizzy. */
#define  AUDPROC_REVERB_PRESET_DIZZY             31

/** Synthetic environment preset: psychotic. */
#define  AUDPROC_REVERB_PRESET_PSYCHOTIC         32

/** @} */ /* end_addtogroup audiopp_module_reverb */

/* Structure for the preset parameter of Reverb module. */
typedef struct audproc_reverb_preset_t audproc_reverb_preset_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_preset_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_PRESET parameter used by the
    Reverb module.
*/
struct audproc_reverb_preset_t
{
    uint32_t                  reverb_preset;
    /**< Specifies one of the reverberation presets that create special
         environmental audio effects.

         @values 0 to 32 (#AUDPROC_REVERB_PRESET_CUSTOM to
                 #AUDPROC_REVERB_PRESET_PSYCHOTIC) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_preset_t */

/* Structure for the wet mix parameter of Reverb module. */
typedef struct audproc_reverb_wet_mix_t audproc_reverb_wet_mix_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_wet_mix_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_WET_MIX parameter used by the
    Reverb module.
*/
struct audproc_reverb_wet_mix_t
{
    uint32_t                  reverb_wet_mix;
    /**< Specifies the reverberation wet/dry mix ratio for Insert Effects mode.

         @values 0 to 1000

         This parameter has no effect if the Reverberation mode is set to
         Auxiliary Effects. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_wet_mix_t */

/* Structure for the gain adjust parameter of Reverb module. */
typedef struct audproc_reverb_gain_adjust_t audproc_reverb_gain_adjust_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_gain_adjust_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_GAIN_ADJUST parameter used by the
    Reverb module.
*/
struct audproc_reverb_gain_adjust_t
{
    int32_t                  gain_adjust;
    /**< Specifies the overall gain adjustment of reverberation outputs.

         @values -600 to +600 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_gain_adjust_t */

/* Structure for the room level parameter of Reverb module. */
typedef struct audproc_reverb_room_level_t audproc_reverb_room_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_room_level_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_ROOM_LEVEL parameter used by the
    Reverb module.
*/
struct audproc_reverb_room_level_t
{
    int32_t                  room_level;
    /**< Specifies the master volume level of the environment reverberation
         effect.

         @values -9600 to 0 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_room_level_t */

/* Structure for the room hf level parameter of Reverb module. */
typedef struct audproc_reverb_room_hf_level_t audproc_reverb_room_hf_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_room_hf_level_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_ROOM_HF_LEVEL parameter used by the
    Reverb module.
*/
struct audproc_reverb_room_hf_level_t
{
    int32_t                  room_hf_level;
    /**< Specifies the volume level at 5 kHz relative to the volume level at
         low frequencies of the overall reverberation effect.

         @values -9600 to 0 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_room_hf_level_t */

/* Structure for the decay time parameter of Reverb module. */
typedef struct audproc_reverb_decay_time_t audproc_reverb_decay_time_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_decay_time_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_DECAY_TIME parameter used by the
    Reverb module.
*/
struct audproc_reverb_decay_time_t
{
    uint32_t                  decay_time;
    /**< Specifies the time for the level of reverberation to decay by 60 dB.

         @values 100 to 20000 milliseconds */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_decay_time_t */

/* Structure for the decay hf ratio parameter of Reverb module. */
typedef struct audproc_reverb_decay_hf_ratio_t audproc_reverb_decay_hf_ratio_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_decay_hf_ratio_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_DECAY_HF_RATIO parameter used by the
    Reverb module.
*/
struct audproc_reverb_decay_hf_ratio_t
{
    uint32_t                  decay_hf_ratio;
    /**< Specifies the ratio of high frequency decay time (at 5 kHz) relative
         to the decay time at low frequencies.

         @values 100 to 2000 milliseconds */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_decay_hf_ratio_t */

/* Structure for the reverb level parameter of Reverb module. */
typedef struct audproc_reverb_level_t audproc_reverb_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_level_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_LEVEL parameter used by the
    Reverb module.
*/
struct audproc_reverb_level_t
{
    int32_t                  reverb_level;
    /**< Specifies the volume level of the late reverberation.

         @values -9600 to 2000 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_level_t */

/* Structure for the reverb delay parameter of Reverb module. */
typedef struct audproc_reverb_delay_t audproc_reverb_delay_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_delay_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_DELAY parameter used by the
    Reverb module.
*/
struct audproc_reverb_delay_t
{
    uint32_t                  reverb_delay;
    /**< Specifies the time between the first reflection and the late
         reverberation.

         @values 0 to 100 milliseconds */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_delay_t */

/* Structure for the reverb reflections level parameter of Reverb module. */
typedef struct audproc_reverb_reflections_level_t audproc_reverb_reflections_level_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_reflections_level_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_REFLECTIONS_LEVEL parameter used by the
    Reverb module.
*/
struct audproc_reverb_reflections_level_t
{
    int32_t                  reflections_level;
    /**< Specifies the volume level of the early reflections.

         @values -9600 to +1000 millibels */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_reflections_level_t */

/* Structure for the reverb reflections delay parameter of Reverb module. */
typedef struct audproc_reverb_reflections_delay_t audproc_reverb_reflections_delay_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_reflections_delay_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_REFLECTIONS_DELAY parameter used by the
    Reverb module.
*/
struct audproc_reverb_reflections_delay_t
{
    uint32_t                  reflections_delay;
    /**< Specifies the time between the first reflection and the late
         reverberation.

         @values 0 to +300 milliseconds */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_reflections_delay_t */

/* Structure for the reverb diffusion parameter of Reverb module. */
typedef struct audproc_reverb_diffusion_t audproc_reverb_diffusion_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_diffusion_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_DIFFUSION parameter used by the
    Reverb module.
*/
struct audproc_reverb_diffusion_t
{
    uint32_t                  diffusion;
    /**< Specifies the echo density in the late reverberation decay.

         @values 0 to +1000 per mille */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_diffusion_t */

/* Structure for the reverb density parameter of Reverb module. */
typedef struct audproc_reverb_density_t audproc_reverb_density_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_reverb_density_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_REVERB_DENSITY parameter used by the
    Reverb module.
*/
struct audproc_reverb_density_t
{
    uint32_t                  density;
    /**< Specifies the modal density of the late reverberation decay.

         @values 0 to +1000 per mille */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_reverb_density_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_popless_equalizer
@{ */
/** ID of the Popless Equalizer module. This module supports the
    following parameter IDs:
    - #AUDPROC_PARAM_ID_EQ_ENABLE
    - #AUDPROC_PARAM_ID_EQ_CONFIG
    - #AUDPROC_PARAM_ID_EQ_NUM_BANDS
    - #AUDPROC_PARAM_ID_EQ_BAND_LEVELS
    - #AUDPROC_PARAM_ID_EQ_BAND_LEVEL_RANGE
    - #AUDPROC_PARAM_ID_EQ_BAND_FREQS
    - #AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ_RANGE
    - #AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ
    - #AUDPROC_PARAM_ID_EQ_BAND_INDEX
    - #AUDPROC_PARAM_ID_EQ_PRESET_ID
    - #AUDPROC_PARAM_ID_EQ_NUM_PRESETS
    - #AUDPROC_PARAM_ID_EQ_PRESET_NAME
    - #AUDPROC_PARAM_ID_ENABLE 
*/
#define AUDPROC_MODULE_ID_POPLESS_EQUALIZER                    0x000108BA

/** ID of the Popless Equalizer Enable parameter used by
    AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    @msgpayload{audproc_eq_enable_t}
    @table{weak__audproc__eq__enable__t} @newpage
*/
#define AUDPROC_PARAM_ID_EQ_ENABLE                             0x000108BB

/** ID of the Popless Equalizer Configuration parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER. This parameter is for Set Parameter
    calls only.

    @msgpayload{audproc_eq_config_t}
    Following this structure are num_bands of %audproc_eq_per_band_params_t
    (see <b>Per-band equalizer parameters</b>).
    The length is dependent on the num_bands value.
    @par
    For predefined Qualcomm and predefined OpenSL equalizers, the sequence of
    per-band parameters is not required, and num_bands must be set to zero.
    @tablens{weak__audproc__eq__config__t}

    @par Per-band equalizer parameters (audproc_eq_per_band_params_t)
    @table{weak__audproc__eq__per__band__params__t}
*/
#define AUDPROC_PARAM_ID_EQ_CONFIG                             0x000108BC

/** ID of the Popless Equalizer Number of Bands parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_num_bands_t}
    @table{weak__audproc__eq__num__bands__t}
*/
#define AUDPROC_PARAM_ID_EQ_NUM_BANDS                          0x000108BD

/** ID of the Popless Equalizer Band Levels parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_band_levels_t}
    @table{weak__audproc__eq__band__levels__t} @newpage
*/
#define AUDPROC_PARAM_ID_EQ_BAND_LEVELS                        0x000108BE

/** ID of the Popless Equalizer Band Level Range parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_band_level_range_t}
    @table{weak__audproc__eq__band__level__range__t}
*/
#define AUDPROC_PARAM_ID_EQ_BAND_LEVEL_RANGE                   0x000108BF

/** ID of the Popless Equalizer Band Frequencies parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_band_freqs_t}
    @table{weak__audproc__eq__band__freqs__t} @newpage
*/
#define AUDPROC_PARAM_ID_EQ_BAND_FREQS                         0x000108C0

/** ID of the Popless Equalizer Single Band Frequency range parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_single_band_freq_range_t}
    @table{weak__audproc__eq__single__band__freq__range__t}
*/
#define AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ_RANGE             0x000108C1

/** ID of the Popless Equalizer Single Band Frequency parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Set Parameter calls only.

    @msgpayload{audproc_eq_single_band_freq_t}
    @table{weak__audproc__eq__single__band__freq__t} @newpage
*/
#define AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ                   0x000108C2

/** ID of the Popless Equalizer Band Index parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER. It is used for both Set and Get
    Parameter calls.

    @msgpayload{audproc_eq_band_index_t}
    @table{weak__audproc__eq__band__index__t}
*/
#define AUDPROC_PARAM_ID_EQ_BAND_INDEX                         0x000108C3

/** ID of the Popless Equalizer Preset ID parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_preset_id_t}
    @table{weak__audproc__eq__preset__id__t} @newpage
*/
#define AUDPROC_PARAM_ID_EQ_PRESET_ID                          0x000108C4

/** ID of the Popless Equalizer Number of Presets parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_num_presets_t}
    @table{weak__audproc__eq__num__presets__t}
*/
#define AUDPROC_PARAM_ID_EQ_NUM_PRESETS                        0x000108C5

/** ID of the Popless Equalizer Preset Name parameter used by
    #AUDPROC_MODULE_ID_POPLESS_EQUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It is used for Get Parameter calls only.

    @msgpayload{audproc_eq_preset_name_t}
    @table{weak__audproc__eq__preset__name__t}
*/
#define AUDPROC_PARAM_ID_EQ_PRESET_NAME                        0x000108C6

/** @} */ /* end_addtogroup audiopp_module_popless_equalizer */

/* Structure for the enable parameter of Popless Equalizer module. */
typedef struct audproc_eq_enable_t audproc_eq_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_ENABLE parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the popless equalizer is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_enable_t */

/** @addtogroup audiopp_module_popless_equalizer
@{ */
/* Presets -1 to 16 are for Qualcomm, and 18 to 28 are for OpenSL. */
/** User-customized equalizer preset (with audio effects specified
    individually). */
#define  AUDPROC_EQ_PRESET_USER_CUSTOM     (-1)

/** Equalizer preset for no audio effects. */
#define  AUDPROC_EQ_PRESET_BLANK           0

/** Equalizer preset for audio effects like a club. @newpage */
#define  AUDPROC_EQ_PRESET_CLUB            1

/** Equalizer preset for audio effects like a dance. */
#define  AUDPROC_EQ_PRESET_DANCE           2

/** Qualcomm equalizer preset for full bass audio effects. */
#define  AUDPROC_EQ_PRESET_FULLBASS        3

/** Equalizer preset for bass and treble audio effects. */
#define  AUDPROC_EQ_PRESET_BASSTREBLE      4

/** Equalizer preset for full treble audio effects. */
#define  AUDPROC_EQ_PRESET_FULLTREBLE      5

/** Equalizer preset for audio effects that are suitable for playback through
    laptop/phone speakers.
*/
#define  AUDPROC_EQ_PRESET_LAPTOP          6

/** Equalizer preset for audio effects that sound like a large hall. */
#define  AUDPROC_EQ_PRESET_LHALL           7

/** Equalizer preset for audio effects that sound like a live performance. */
#define  AUDPROC_EQ_PRESET_LIVE            8

/** Equalizer preset for audio effects that sound like a party. */
#define  AUDPROC_EQ_PRESET_PARTY           9

/** Equalizer preset for pop audio effects. */
#define  AUDPROC_EQ_PRESET_POP             10

/** Equalizer preset for reggae audio effects. */
#define  AUDPROC_EQ_PRESET_REGGAE          11

/** Equalizer preset for rock audio effects. */
#define  AUDPROC_EQ_PRESET_ROCK            12

/** Equalizer preset for Ska audio effects. */
#define  AUDPROC_EQ_PRESET_SKA             13

/** Equalizer preset for soft pop audio effects. */
#define  AUDPROC_EQ_PRESET_SOFT            14

/** Equalizer preset for soft rock audio effects. */
#define  AUDPROC_EQ_PRESET_SOFTROCK        15

/** Equalizer preset for techno audio effects. */
#define  AUDPROC_EQ_PRESET_TECHNO          16

/** User-customized equalizer preset (with audio effects specified
    individually) (OpenSL).
*/
#define  AUDPROC_EQ_PRESET_USER_CUSTOM_AUDIO_FX    18

/** Equalizer preset for normal (generic) audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_NORMAL_AUDIO_FX         19

/** Equalizer preset for classical audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_CLASSICAL_AUDIO_FX      20

/** Equalizer preset for dance audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_DANCE_AUDIO_FX          21

/** Equalizer preset for no audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_FLAT_AUDIO_FX           22

/** Equalizer preset for folk audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_FOLK_AUDIO_FX           23

/** Equalizer preset for heavy metal audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_HEAVYMETAL_AUDIO_FX     24

/** Equalizer preset for hip hop audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_HIPHOP_AUDIO_FX         25

/** Equalizer preset for jazz audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_JAZZ_AUDIO_FX           26

/** Equalizer preset for pop audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_POP_AUDIO_FX            27

/** Equalizer preset for rock audio effects (OpenSL). */
#define  AUDPROC_EQ_PRESET_ROCK_AUDIO_FX           28

/** @} */ /* end_addtogroup audiopp_module_popless_equalizer */

/* Structure for the config parameter of Popless Equalizer module. */
typedef struct audproc_eq_config_t audproc_eq_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_config_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_CONFIG parameter used by the
    Popless Equalizer module.
   Following this structure are num_bands of audproc_eq_per_band_params_t. The length is
    dependent on the num_bands value.
    For predefined Qualcomm and predefined OpenSL equalizers, the sequence of
    per-band parameters is not required, and num_bands must be set to zero.
*/
struct audproc_eq_config_t
{
    int32_t                  eq_pregain;
    /**< Gain in Q27 before any equalization processing. */

    int32_t                  preset_id;
    /**< Specifies either the user-customized equalizers or two sets of
         equalizers predefined by Qualcomm and OpenSL, respectively.

         @values
         - -1 -- Custom equalizer that meets Qualcomm requirements
         - 0 to 16 -- Equalizers that are predefined by Qualcomm
         - 18 -- Custom equalizer that meets OpenSL requirements
         - 19 to 28 -- Equalizers that are predefined by OpenSL
         @tablebulletend */

    uint32_t                  num_bands;
    /**< Number of subbands for equalization when a custom preset ID is
         selected in the preset_id field.

         @values{if preset\_id = -1} 1 to 12

         @values{if preset\_id = 18} 5

         @values{all other preset\_id settings} 0 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_config_t */

/* Structure for per-band parameters for the Popless Equalizer module. */
typedef struct audproc_eq_per_band_config_t audproc_eq_per_band_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_per_band_config_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_CONFIG per-band config
    parameters used by the Popless Equalizer module. (See also audproc_eq_config_t.)
*/
struct audproc_eq_per_band_config_t
{
    uint32_t                  filter_type;
    /**< Type of equalizer filter in the subband.

         @values
         - #AUDPROC_PARAM_EQ_TYPE_NONE
         - #AUDPROC_PARAM_EQ_BASS_BOOST
         - #AUDPROC_PARAM_EQ_BASS_CUT
         - #AUDPROC_PARAM_EQ_TREBLE_BOOST
         - #AUDPROC_PARAM_EQ_TREBLE_CUT
         - #AUDPROC_PARAM_EQ_BAND_BOOST
         - #AUDPROC_PARAM_EQ_BAND_CUT @tablebulletend */

    uint32_t                  freq_millihertz;
    /**< Center or cutoff frequency of the subband filter in Millihertz.

         @values 0 to fs/2 (Nyquist rate), depending on the sampling rate of
                 the input audio signal */

    int32_t                   gain_millibels;
    /**< Initial gain of the subband filter.

         @values +1500 to -1500 mdB in 100 mdB increments */

    uint32_t                  quality_factor;
    /**< Subband filter quality factor expressed as a Q8 number (a
         fixed-point number with a quality factor of 8).
         For example, 3000/(2^8). */

    uint32_t                  band_idx;
    /**< Index of the subband filter.

         @values 0 to num_bands - 1 (num_bands is specified in
                 audproc_eq_config_t) */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_per_band_config_t */

/* Structure for the num bands parameter of Popless Equalizer module. */
typedef struct audproc_eq_num_bands_t audproc_eq_num_bands_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_num_bands_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_NUM_BANDS parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_num_bands_t
{
    uint32_t                  num_bands;
    /**< Number of subbands in the current equalizer filter.
         For Get Parameter calls only, the library returns the value.

         @values
         - 1 to 12 -- Equalizers are compliant to or predefined by Qualcomm
         - 5 -- Equalizers are compliant to or predefined by OpenSL
           @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_num_bands_t */

/* Structure for the band levels parameter of Popless Equalizer module. */
typedef struct audproc_eq_band_levels_t audproc_eq_band_levels_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_band_levels_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_BAND_LEVELS parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_band_levels_t
{
    uint32_t                  num_bands;
    /**< Number of subbands in the current equalizer filter.
         For Get Parameter calls only, the library returns the value.

         @values
         - 1 to 12 -- Equalizers are compliant to or predefined by Qualcomm
         - 5 -- Equalizers are compliant to or predefined by OpenSL
           @tablebulletend */

    int32_t                   band_levels[12];
    /**< Array of gains (in millibels) of each subband filter.
         For Get Parameter calls only, the library returns the values.

         The meaningful contents in the array depend on num_bands.
         In other words, the following contains valid values returned by the
         library:
         
         @indent band_levels[0] - band_levels[num_bands-1] */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_band_levels_t */

/* Structure for the band level range parameter of Popless Equalizer module. */
typedef struct audproc_eq_band_level_range_t audproc_eq_band_level_range_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_band_level_range_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_BAND_LEVEL_RANGE parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_band_level_range_t
{
    int32_t                  min_level_millibels;
    /**< Minimum gain of subband equalizer filters in the current equalizer
         configuration. For Get Parameter calls only, the library returns
         the value.

         @values Always -1500 */

    int32_t                  max_level_millibels;
    /**< Maximum gain of subband equalizer filters in the current equalizer
         configuration. For Get Parameter calls only, the library returns
         the value.

         @values Always +1500 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_band_level_range_t */

/* Structure for the band frequency parameter of Popless Equalizer module. */
typedef struct audproc_eq_band_freqs_t audproc_eq_band_freqs_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_band_freqs_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_BAND_FREQS parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_band_freqs_t
{
    uint32_t                  num_bands;
    /**< Number of subband equalizer filters in the current equalizer
         configuration. For Get Parameter calls only, the library returns
         the value.

         @values
         - 1 to 12 -- Equalizers are compliant to or predefined by Qualcomm
         - 5 -- Equalizers are compliant to or predefined by OpenSL
           @tablebulletend */

    uint32_t                   band_freqs[12];
    /**< Array of center or cutoff frequencies of each subband filter, in
         millihertz.
         For Get parameter calls only, the library returns the values.

         The meaningful contents in the array depend on num_bands.
         In other words, the following contains valid values returned by the
         library:
         
         @indent band_freqs[0] - band_freqs[num_bands-1] */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_band_freqs_t */

/* Structure for the band frequency range parameter of Popless Equalizer module. */
typedef struct audproc_eq_single_band_freq_range_t audproc_eq_single_band_freq_range_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_single_band_freq_range_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ_RANGE parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_single_band_freq_range_t
{
    uint32_t                  min_freq_millihertz;
    /**< Lower frequency boundary of the subband equalizer filter with the
         band_index provided by a previous Set Parameter call with
         #AUDPROC_PARAM_ID_EQ_BAND_INDEX.

         For Get Parameter calls only, the library returns the value.

         @values Any value in the range of 0 to sample_rate/2

         If the band index is not provided by a previous Set Parameter call,
         the parameters of the first subband with band_index = 0 are returned. */

    uint32_t                  max_freq_millihertz;
    /**< Upper frequency boundary of the subband equalizer filter with the
         band_index provided by a previous Set Parameter call with
         #AUDPROC_PARAM_ID_EQ_BAND_INDEX.

         For Get Parameter calls only, the library returns the value.

         @values Any value in the range of 0 to sample_rate/2

         If the band index is not provided by a previous Set Parameter call,
         the parameters of the first subband with band_index = 0 are returned. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_single_band_freq_range_t */

/* Structure for the band frequency parameter of Popless Equalizer module. */
typedef struct audproc_eq_single_band_freq_t audproc_eq_single_band_freq_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_single_band_freq_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_single_band_freq_t
{
    uint32_t                  freq_millihertz;
    /**< For Set Parameter calls only, center or cutoff frequency of the
         subband equalizer filter for which the band_index is requested in a
         subsequent Get Parameter call via #AUDPROC_PARAM_ID_EQ_BAND_INDEX.

         @values Any value in the range of 0 to sample_rate/2 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_single_band_freq_t */

/* Structure for the band index parameter of Popless Equalizer module. */
typedef struct audproc_eq_band_index_t audproc_eq_band_index_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_band_index_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_BAND_INDEX parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_band_index_t
{
    uint32_t                  band_index;
    /**< Index of each band.

         @values
         - 0 to 11 -- Equalizers are compliant to or predefined by Qualcomm
         - 0 to 4 -- Equalizers are compliant to or predefined by OpenSL

         If AUDPROC_PARAM_ID_EQ_BAND_INDEX is used in a Set Parameter call,
         this band_index is used to get the subband frequency range in the next
         Get Parameter call with #AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ_RANGE.

         If this parameter ID is used in a Get Parameter call, the band_index
         with the center or cutoff frequency set by the Set parameter of
         #AUDPROC_PARAM_ID_EQ_SINGLE_BAND_FREQ is returned.

         If the center/cutoff frequency of the requested subband is not set
         before a Get Parameter call via #AUDPROC_PARAM_ID_EQ_BAND_INDEX, the
         default band_index of zero is returned. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_band_index_t */

/* Structure for the preset id parameter of Popless Equalizer module. */
typedef struct audproc_eq_preset_id_t audproc_eq_preset_id_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_preset_id_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_PRESET_ID parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_preset_id_t
{
    int32_t                  preset_id;
    /**< Preset ID of the current equalizer configuration.
         For Get Parameter calls only, the library returns the value.

         @values
         - -1 to 16 -- Equalizers are compliant to or predefined by Qualcomm 
         - 18 to 28 -- Equalizers are compliant to or predefined by OpenSL
           @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_preset_id_t */

/* Structure for the num presets parameter of Popless Equalizer module. */
typedef struct audproc_eq_num_presets_t audproc_eq_num_presets_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_num_presets_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_NUM_PRESETS parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_num_presets_t
{
    uint32_t                 num_presets;
    /**< Total number of supported presets in the current equalizer
         configuration.
         For Get Parameter calls only, the library returns the value.

         @values
         - 17 -- Equalizers are compliant to or predefined by Qualcomm
         - 10 -- Equalizers are compliant to or predefined by OpenSL
           @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_num_presets_t */

/* Structure for the preset name parameter of Popless Equalizer module. */
typedef struct audproc_eq_preset_name_t audproc_eq_preset_name_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_eq_preset_name_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_EQ_PRESET_NAME parameter used by the
    Popless Equalizer module.
*/
struct audproc_eq_preset_name_t
{
    uint8_t                 preset_name[32];
    /**< Name of the current equalizer preset (in ASCII characters).
         For Get Parameter calls only, the library returns the value. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_eq_preset_name_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_module_visualizer
@{ */
/** ID of the Visualizer module. This module supports the
    following parameter IDs:
    - #AUDPROC_PARAM_ID_VISUALIZER_ENABLE
    - #AUDPROC_PARAM_ID_VISUALIZER_CONFIG
    - #AUDPROC_PARAM_ID_VISUALIZER_CAPTURE_SIZE
    - #AUDPROC_PARAM_ID_VISUALIZER_SCALING_MODE
    - #AUDPROC_PARAM_ID_VISUALIZER_PCM_DATA
    - #AUDPROC_PARAM_ID_VISUALIZER_FFT_DATA
    - #AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT_MODE
    - #AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT
    - #AUDPROC_PARAM_ID_ENABLE
*/
#define AUDPROC_MODULE_ID_VISUALIZER                            0x000108C9

/** ID of the Visualizer Enable parameter used by
    AUDPROC_MODULE_ID_VISUALIZER.

    @msgpayload{audproc_visualizer_enable_t}
    @table{weak__audproc__visualizer__enable__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_ENABLE                 0x000108CA

/** ID of the Visualizer Configuration parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    @msgpayload{audproc_visualizer_config_t}
    @table{weak__audproc__visualizer__config__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_CONFIG                 0x000108CB

/** ID of the Visualizer Capture Size parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    @msgpayload{audproc_visualizer_capture_size_t}
    @table{weak__audproc__visualizer__capture__size__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_CAPTURE_SIZE           0x000108CC

/** ID of the Visualizer Scaling Mode parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    @msgpayload{audproc_visualizer_scaling_mode_t}
    @table{weak__audproc__visualizer__scaling__mode__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_SCALING_MODE           0x000108CD

/** ID of the Visualizer PCM Data parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It gets parameters only when the module
    is enabled (#AUDPROC_PARAM_ID_VISUALIZER_ENABLE).
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_PCM_DATA               0x000108CE

/** ID of the Visualizer FFT Data parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It gets parameters only when the module
    is enabled (#AUDPROC_PARAM_ID_VISUALIZER_ENABLE). 
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_FFT_DATA               0x000108CF

/** ID of the Visualizer RMS Measurement Mode parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    @msgpayload{audproc_visualizer_measurement_mode_t}
    @table{weak__audproc__visualizer__measurement__mode__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT_MODE       0x000108D0

/** ID of the Visualizer Measurement Data parameter used by
    #AUDPROC_MODULE_ID_VISUALIZER.

    This is a read-only parameter used by #ADM_CMD_GET_PP_PARAMS_V5 and
    #ASM_STREAM_CMD_GET_PP_PARAMS_V2. It gets parameters only when the module
    is enabled (#AUDPROC_PARAM_ID_VISUALIZER_ENABLE) and measurement mode is 1.

    @msgpayload{audproc_visualizer_measurement_t}
    @table{weak__audproc__visualizer__measurement__t}
*/
#define   AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT            0x000108D1

/** @} */ /* end_addtogroup audiopp_module_visualizer */

/* Structure for the visualzier enable parameter */
typedef struct audproc_visualizer_enable_t audproc_visualizer_enable_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_enable_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_ENABLE parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_enable_t
{
    uint32_t                  enable_flag;
    /**< Specifies whether the visualizer is enabled.

         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_enable_t */

/* Structure for the visualzier configuration parameter */
typedef struct audproc_visualizer_config_t audproc_visualizer_config_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_config_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_CONFIG parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_config_t
{
   uint32_t   latency_ms;
   /**< Specifies the latency of the visualizer in milliseconds.

        The latency is greater or equal to zero. The maximum allowed value of
        latency is dependent on the capture size and audio sampling rate as
        follows:

        @indent ((8192 - capture_size) / sampling_rate) x 1000

        The capture size is set by #AUDPROC_PARAM_ID_VISUALIZER_CAPTURE_SIZE. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_config_t */

/* Structure for the visualzier capture size parameter */
typedef struct audproc_visualizer_capture_size_t  audproc_visualizer_capture_size_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_capture_size_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_CAPTURE_SIZE parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_capture_size_t
{
    uint32_t                  capture_size;
    /**< Specifies the visualizer input data capture window length for FFT
         analysis. The size must be a power of 2.

         @values 128, 256, 512, 1024, 2048, 4096

         Set the parameter before audio playback starts.
         Get the parameter only after playback starts. @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_capture_size_t */

/* Structure for the visualzier scaling mode parameter */
typedef struct audproc_visualizer_scaling_mode_t  audproc_visualizer_scaling_mode_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_scaling_mode_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_SCALING_MODE parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_scaling_mode_t
{
    uint32_t                  scaling_mode;
    /**< Specifies the visualizer Scaling mode.

         @values
         - 0 -- NORMALIZED \n
                Input PCM samples are normalized frame-by-frame and saved in
                8-bit resolution.
         - 1 -- AS_PLAYED \n
                Input PCM samples are simply right-shifted and saved in
                8-bit resolution. @tablebulletend */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_scaling_mode_t */

/* Structure for the visualzier measurement mode parameter */
typedef struct audproc_visualizer_measurement_mode_t  audproc_visualizer_measurement_mode_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_measurement_mode_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT_MODE parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_measurement_mode_t
{
    uint32_t                  measurement_mode;
    /**< Specifies whether the visualizer RMS Measurement mode is enabled.

       @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_measurement_mode_t */

/* Structure for the visualzier RMS measurement data parameter */
typedef struct audproc_visualizer_measurement_t  audproc_visualizer_measurement_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_visualizer_measurement_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_VISUALIZER_MEASUREMENT parameter used by the
    Visualizer module.
*/
struct audproc_visualizer_measurement_t
{
    int32_t                  peak_value_db;
    /**< Specifies the peak absolute amplitude of input PCM data in decibels. */

    int32_t                  rms_power_db;
    /**< Specifies the average RMS power of input PCM data in decibels. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_visualizer_measurement_t */
/** @endcond */

/** @cond OEM_only */
/** @addtogroup audiopp_topos_adm
@{ */
/** ID of the COPP audio postprocessing headphone topology that includes
    AudioPlus.

    @inputfig{1,topo_id_audproc_0x0001089E.png}

    - Virtualizer     (#AUDPROC_MODULE_ID_VIRTUALIZER)
    - Reverberation   (#AUDPROC_MODULE_ID_REVERB)
    - Bass Boost      (#AUDPROC_MODULE_ID_BASS_BOOST)
    - Visualizer      (#AUDPROC_MODULE_ID_VISUALIZER)
*/
#define AUDPROC_COPP_TOPOLOGY_ID_AUDIO_PLUS_HEADPHONE           0x0001089E

/** ID of the COPP audio postprocessing speaker topology that includes
    AudioPlus.

    @inputfig{1,topo_id_audproc_0x0001089F.png}

    - Virtualizer        (#AUDPROC_MODULE_ID_VIRTUALIZER)
    - Reverberation      (#AUDPROC_MODULE_ID_REVERB)
    - PBE                (#AUDPROC_MODULE_ID_PBE)
    - Visualizer         (#AUDPROC_MODULE_ID_VISUALIZER)@newpage
*/
#define AUDPROC_COPP_TOPOLOGY_ID_AUDIO_PLUS_SPEAKER             0x0001089F

/** ID of the POPP audio postprocessing topology that includes AudioPlus.

    @inputfig{1,topo_id_audproc_0x000108A0.png}

    - Resampler                (#AUDPROC_MODULE_ID_RESAMPLER)
    - Soft Volume Control      (#AUDPROC_MODULE_ID_VOL_CTRL)
    - Popless Equalizer        (#AUDPROC_MODULE_ID_POPLESS_EQUALIZER)
*/
#define AUDPROC_POPP_TOPOLOGY_ID_AUDIO_PLUS                      0x000108A0

/** @} */ /* end_addtogroup audiopp_topos_adm */
/** @endcond */

/** @ingroup audiopp_common_params
    ID of the Enable parameter used by any audio processing module.

    This is a generic/common parameter used to configure or determine the
    state of any audio processing module.

    @msgpayload{audproc_enable_param_t}
    @table{weak__audproc__enable__param__t}
*/
#define AUDPROC_PARAM_ID_ENABLE                                   0x00010904

/* Structure for Enable parameter for any Audio processing modules. */
typedef struct audproc_enable_param_t audproc_enable_param_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_enable_param_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_ENABLE parameter used by
    any Audio Processing module
*/
struct audproc_enable_param_t
{
    uint32_t                  enable;
    /**< Specifies whether the audio processing module is enabled.
 
         @values
         - 0 -- Disable
         - 1 -- Enable @tablebulletend */

}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak__audproc_enable_param_t */

/** @cond OEM_only */
/** @addtogroup audiopp_module_channel_mixer
@{ */
/** ID of the Channel Mixer module, which is used to configure
    channel-mixer related parameters.

    This module supports the following parameter ID.
*/
#define AUDPROC_MODULE_ID_CHMIXER                                  MTMX_MODULE_ID_DEFAULT_CHMIXER

/* Structure payload for: AUDPROC_CHMIXER_PARAM_ID_COEFF*/
/** ID of the Coefficient parameter used by AUDPROC_MODULE_ID_CHMIXER to
    configure the channel mixer weighting coefficients.

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
    - The Set parameters are per-stream, per-device, or per-stream-per-device.
    - The Set parameters values are lost when the stream/device is closed.
      @newpage
    - For a given stream/device, the aDSP can cache up to eight Set
      parameters. \n
      \n
      For example, this means the client can configure eight Set parameters as
      follows:
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
    - If multiple rows contain duplicate entries, the higher index rule (which
      is supposedly set later) is chosen and applied, if applicable.
    - The aDSP reverts to default coefficients (built-in coefficients) if the
      rule is not explicitly provided by the client (for example, if the input
      or output media types do not match the Set parameter rule provided.
    - The Set parameter must be called after stream, device, and routing is
      established. For the Set parameter to take effect correctly, Qualcomm
      recommends calling the Set parameter before the Run command.
*/
#define AUDPROC_CHMIXER_PARAM_ID_COEFF                                    DEFAULT_CHMIXER_PARAM_ID_COEFF

/** @} */ /* end_addtogroup audproc_chmixer */
/** @endcond */

typedef struct default_chmixer_param_id_coeff audproc_chmixer_param_id_coeff_t;

/* Payload format for pp topology module id info data. */
typedef struct audproc_topology_module_id_info_t audproc_topology_module_id_info_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_topology_module_id_info_t
@{ */
/* Payload of the ADM_CMD_GET_PP_TOPO_MODULE_LIST and ASM_CMD_GET_PP_TOPO_MODULE_LIST
    command.
*/
struct  audproc_topology_module_id_info_t
{
    uint32_t                  num_modules;
    /**< Number of modules in the topology. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_topology_module_id_info_t */


/** @cond OEM_only */
/** @addtogroup audiopp_module_mfc
@{ */
/** ID of the Media Format Converter (MFC) module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_MFC_OUTPUT_MEDIA_FORMAT
    - #AUDPROC_CHMIXER_PARAM_ID_COEFF
*/
#define AUDPROC_MODULE_ID_MFC                               0x00010912

/** ID of the Output Media Format parameters used by AUDPROC_MODULE_ID_MFC.

    @msgpayload{audproc_mfc_output_media_fmt_t}
    @table{weak__audproc__mfc__output__media__fmt__t}
*/
#define AUDPROC_PARAM_ID_MFC_OUTPUT_MEDIA_FORMAT            0x00010913

/** @} */ /* end_addtogroup audiopp_module_mfc */

/* Structure for the output media format parameter used by the Media
   Format Converter module. */
typedef struct audproc_mfc_output_media_fmt_t audproc_mfc_output_media_fmt_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_audproc_mfc_output_media_fmt_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_MFC_OUTPUT_MEDIA_FORMAT parameter in the
   Media Format Converter Module.
*/
struct audproc_mfc_output_media_fmt_t
{
   uint32_t sampling_rate;
   /**< Sampling rate in samples per second.

        @values 0 < sampling rate @le 192000 */

   uint16_t bits_per_sample;
   /**< Number of bits used to store each sample.

        @values
        - 16 = 16 bits per sample
        - 24 = 24 bits per sample @tablebulletend */

   uint16_t num_channels;
   /**< Number of channels.

        @values 1 to 8 channels */

   uint16_t channel_type[8];
   /**< Channel mapping array. Specify a channel mapping for each output
        channel.

        @values See Chapter @xref{dox:AsmStreamMediaFormats}

        If the number of channels is not a multiple of four, zero padding must
        be added to the channel type array to align the packet to a multiple of
        32 bits. */
};
#include "adsp_end_pack.h"

/** @} */ /* end_weakgroup weak_audproc_mfc_output_media_fmt_t */
/** @endcond */

/** @cond OEM_only */
// The following names have been deprecated. Please use the new names.
/** @addtogroup asm_audpp_deprecated
@{ */
/** @name EANS module
@{ */
#define ADM_MODULE_ID_EANS AUDPROC_MODULE_ID_EANS
#define ADM_PARAM_ID_EANS_ENABLE AUDPROC_PARAM_ID_EANS_ENABLE
#define ADM_PARAM_ID_EANS_PARAMS AUDPROC_PARAM_ID_EANS_PARAMS
typedef audproc_eans_enable_t adm_eans_enable_t;
typedef audproc_eans_params_t adm_eans_params_t;
/** @} */ /* end_name EANS module */

/** @name Tx Mic Gain Control module
@{ */
#define ADM_MODULE_ID_TX_MIC_GAIN_CTRL AUDPROC_MODULE_ID_TX_MIC_GAIN_CTRL
#define ADM_PARAM_ID_TX_MIC_GAIN AUDPROC_PARAM_ID_TX_MIC_GAIN
typedef audproc_tx_mic_gain_t adm_tx_mic_gain_t;
/** @} */ /* end_name Tx Mic Gain Control module */

/** @name Rx Codec Gain Control module
@{ */
#define ADM_MODULE_ID_RX_CODEC_GAIN_CTRL AUDPROC_MODULE_ID_RX_CODEC_GAIN_CTRL
#define ADM_PARAM_ID_RX_CODEC_GAIN AUDPROC_PARAM_ID_RX_CODEC_GAIN
typedef audproc_rx_codec_gain_t adm_rx_codec_gain_t;
/** @} */ /* end_name Rx Codec Gain Control module */

/** @name IIR Tuning Filter module
@{ */
#define ASM_MODULE_ID_IIR_TUNING_FILTER AUDPROC_MODULE_ID_IIR_TUNING_FILTER
#define ASM_PARAM_ID_IIR_TUNING_FILTER_ENABLE_CONFIG AUDPROC_PARAM_ID_IIR_TUNING_FILTER_ENABLE_CONFIG
#define ASM_PARAM_ID_IIR_TUNING_FILTER_PRE_GAIN AUDPROC_PARAM_ID_IIR_TUNING_FILTER_PRE_GAIN
#define ASM_PARAM_ID_IIR_TUNING_FILTER_CONFIG_PARAMS AUDPROC_PARAM_ID_IIR_TUNING_FILTER_CONFIG_PARAMS
typedef audproc_iir_tuning_filter_enable_t asm_iir_tuning_filter_enable_t;
typedef audproc_iir_tuning_filter_pregain_t asm_iir_tuning_filter_pregain_t;
typedef audproc_iir_filter_config_params_t asm_iir_filter_config_params_t;
/** @} */ /* end_name IIR Tuning Filter module */

/** @name Tx IIR Tuning Filter module
@{ */
#define ADM_MODULE_ID_TX_IIR_FILTER AUDPROC_MODULE_ID_TX_IIR_FILTER
#define ADM_PARAM_ID_TX_IIR_FILTER_ENABLE_CONFIG AUDPROC_PARAM_ID_TX_IIR_FILTER_ENABLE_CONFIG
#define ADM_PARAM_ID_TX_IIR_FILTER_PRE_GAIN AUDPROC_PARAM_ID_TX_IIR_FILTER_PRE_GAIN
#define ADM_PARAM_ID_TX_IIR_FILTER_CONFIG_PARAMS AUDPROC_PARAM_ID_TX_IIR_FILTER_CONFIG_PARAMS
typedef audproc_tx_iir_filter_enable_cfg_t adm_tx_iir_filter_enable_cfg_t;
typedef audproc_tx_iir_filter_pre_gain_t adm_tx_iir_filter_pre_gain_t;
typedef audproc_tx_iir_filter_cfg_params_t adm_tx_iir_filter_cfg_params_t;
/** @} */ /* end_name Tx IIR Tuning Filter module */

/** @name Tx HPF IIR Tuning Filter module
@{ */
#define ADM_MODULE_ID_HPF_IIR_TX_FILTER AUDPROC_MODULE_ID_HPF_IIR_TX_FILTER
#define ADM_PARAM_ID_HPF_IIR_TX_FILTER_ENABLE_CONFIG AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_ENABLE_CONFIG
#define ADM_PARAM_ID_HPF_IIR_TX_FILTER_PRE_GAIN AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_PRE_GAIN
#define ADM_PARAM_ID_HPF_IIR_TX_FILTER_CONFIG_PARAMS AUDPROC_PARAM_ID_HPF_IIR_TX_FILTER_CONFIG_PARAMS
typedef audproc_hpf_tx_iir_filter_enable_cfg_t adm_hpf_tx_iir_filter_enable_cfg_t;
typedef audproc_hpf_tx_iir_filter_pre_gain_t adm_hpf_tx_iir_filter_pre_gain_t;
typedef audproc_hpf_tx_iir_filter_cfg_params_t adm_hpf_tx_iir_filter_cfg_params_t;
/** @} */ /* end_name Tx HPF IIR Tuning Filter module */

/** @name Rx Path IIR Tuning Filter modules
@{ */
#define ADM_MODULE_ID_LEFT_IIR_TUNING_FILTER AUDPROC_MODULE_ID_LEFT_IIR_TUNING_FILTER
#define ADM_MODULE_ID_RIGHT_IIR_TUNING_FILTER AUDPROC_MODULE_ID_RIGHT_IIR_TUNING_FILTER
/** @} */ /* end_name Rx Path IIR Tuning Filter modules */

/** @name Volume Control module
@{ */
#define ASM_MODULE_ID_VOL_CTRL AUDPROC_MODULE_ID_VOL_CTRL
#define ASM_PARAM_ID_VOL_CTRL_MASTER_GAIN AUDPROC_PARAM_ID_VOL_CTRL_MASTER_GAIN
#define ASM_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN AUDPROC_PARAM_ID_VOL_CTRL_LR_CHANNEL_GAIN
#define ASM_PARAM_ID_VOL_CTRL_MUTE_CONFIG AUDPROC_PARAM_ID_VOL_CTRL_MUTE_CONFIG
#define ASM_PARAM_ID_SOFT_VOL_STEPPING_PARAMETERS AUDPROC_PARAM_ID_SOFT_VOL_STEPPING_PARAMETERS
#define ASM_PARAM_ID_SOFT_PAUSE_PARAMETERS AUDPROC_PARAM_ID_SOFT_PAUSE_PARAMETERS
#define ASM_PARAM_ID_MULTICHANNEL_GAIN AUDPROC_PARAM_ID_MULTICHANNEL_GAIN
#define ASM_PARAM_ID_MULTICHANNEL_MUTE AUDPROC_PARAM_ID_MULTICHANNEL_MUTE
#define ASM_PARAM_SVC_RAMPINGCURVE_LINEAR AUDPROC_PARAM_SVC_RAMPINGCURVE_LINEAR
#define ASM_PARAM_SVC_RAMPINGCURVE_EXP AUDPROC_PARAM_SVC_RAMPINGCURVE_EXP
#define ASM_PARAM_SVC_RAMPINGCURVE_LOG AUDPROC_PARAM_SVC_RAMPINGCURVE_LOG
#define ASM_PARAM_SVC_RAMPINGCURVE_FRAC_EXP  AUDPROC_PARAM_SVC_RAMPINGCURVE_FRAC_EXP
typedef audproc_volume_ctrl_master_gain_t asm_volume_ctrl_master_gain_t;
typedef audproc_volume_ctrl_lr_chan_gain_t asm_volume_ctrl_lr_chan_gain_t;
typedef audproc_volume_ctrl_mute_config_t asm_volume_ctrl_mute_config_t;
typedef audproc_soft_step_volume_params_t asm_soft_step_volume_params_t;
typedef audproc_soft_pause_params_t asm_soft_pause_params_t;
typedef audproc_volume_ctrl_channel_type_gain_pair_t asm_volume_ctrl_channel_type_gain_pair_t;
typedef audproc_volume_ctrl_multichannel_gain_t asm_volume_ctrl_multichannel_gain_t;
typedef audproc_volume_ctrl_channel_type_mute_pair_t asm_volume_ctrl_channel_type_mute_pair_t;
typedef audproc_volume_ctrl_multichannel_mute_t asm_volume_ctrl_multichannel_mute_t;
/** @} */ /* end_name Volume Control module */

/** @name MBDRC, MBDRCV2, and MBDRCV3 modules
@{ */
#define ASM_MODULE_ID_MBDRC AUDPROC_MODULE_ID_MBDRC
#define ASM_PARAM_ID_MBDRC_ENABLE AUDPROC_PARAM_ID_MBDRC_ENABLE
#define ASM_PARAM_ID_MBDRC_CONFIG_PARAMS AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS
#define ASM_MODULE_ID_MBDRCV2 AUDPROC_MODULE_ID_MBDRCV2
#define ASM_PARAM_ID_MBDRC_CONFIG_PARAMS_IMPROVED_FILTBANK_V2 AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_IMPROVED_FILTBANK_V2
#define ASM_MODULE_ID_MBDRCV3 AUDPROC_MODULE_ID_MBDRCV3
#define ASM_PARAM_ID_MBDRC_CONFIG_PARAMS_V3 AUDPROC_PARAM_ID_MBDRC_CONFIG_PARAMS_V3
typedef audproc_mbdrc_enable_t asm_mbdrc_enable_t;
typedef audproc_mbdrc_config_params_t asm_mbdrc_config_params_t;
typedef audproc_subband_drc_config_params_t asm_subband_drc_config_params_t;
typedef audproc_mbdrc_filter_xover_freqs_t asm_mbdrc_filter_xover_freqs_t;
typedef audproc_mbdrc_config_params_v3_t asm_mbdrc_config_params_v3_t;
/** @} */ /* end_name MBDRC and MBDRCV2 modules */

/** @name Equalizer module
@{ */
#define ASM_MODULE_ID_EQUALIZER AUDPROC_MODULE_ID_EQUALIZER
#define ASM_PARAM_ID_EQUALIZER_PARAMETERS AUDPROC_PARAM_ID_EQUALIZER_PARAMETERS
#define ASM_PARAM_EQ_TYPE_NONE AUDPROC_PARAM_EQ_TYPE_NONE
#define ASM_PARAM_EQ_BASS_BOOST AUDPROC_PARAM_EQ_BASS_BOOST
#define ASM_PARAM_EQ_BASS_CUT AUDPROC_PARAM_EQ_BASS_CUT
#define ASM_PARAM_EQ_TREBLE_BOOST AUDPROC_PARAM_EQ_TREBLE_BOOST
#define ASM_PARAM_EQ_TREBLE_CUT AUDPROC_PARAM_EQ_TREBLE_CUT
#define ASM_PARAM_EQ_BAND_BOOST AUDPROC_PARAM_EQ_BAND_BOOST
#define ASM_PARAM_EQ_BAND_CUT AUDPROC_PARAM_EQ_BAND_CUT
typedef audproc_eq_params_t asm_eq_params_t;
typedef audproc_eq_per_band_params_t asm_eq_per_band_params_t;
/** @} */ /* end_name Equalizer modules */

/** @name PBE module
@{ */
#define ASM_PARAM_ID_PBE AUDPROC_MODULE_ID_PBE
#define ASM_PARAM_ID_PBE_ENABLE AUDPROC_PARAM_ID_PBE_ENABLE
#define ASM_PARAM_ID_PBE_PARAMS_CONFIG AUDPROC_PARAM_ID_PBE_PARAMS_CONFIG
typedef audproc_pbe_enable_t asm_pbe_enable_t;
typedef audproc_pbe_params_t asm_pbe_params_t;
/** @} */ /* end_name PBE modules */

/** @name SPA module
@{ */
#define ASM_MODULE_ID_SPA AUDPROC_MODULE_ID_SPA
#define ASM_PARAM_ID_SPA_ENABLE AUDPROC_PARAM_ID_SPA_ENABLE
#define ASM_PARAM_ID_SPA_PARAMS_CONFIG AUDPROC_PARAM_ID_SPA_PARAMS_CONFIG
typedef audproc_spa_enable_t asm_spa_enable_t;
typedef audproc_spa_param_t asm_spa_param_t;
/** @} */ /* end_name SPA modules */

/** @} */ /* end_addtogroup asm_audpp_deprecated */
/** @endcond */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_AUDPROC_API_H_ */
