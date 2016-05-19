
#ifndef _ADSP_DOLBY_AUDIO_KERNEL_API_H_
#define _ADSP_DOLBY_AUDIO_KERNEL_API_H_

/**
@file adsp_dolby_audio_kernel_api.h

@brief This file contains the structure definitions for the 
commands related with Dolby Audio Kernel. 
*/

/*===========================================================================
  Copyright (c) 2010 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/

/*========================================================================
Edit History
when       who     what, where, why
--------   ---     -------------------------------------------------------
11/05/10   DC      Created file.

========================================================================== */

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/** Dolby Audio Kernel Topology ID. The client shall only route one ASM session to this COPP. */ 
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DAK  0x000106ca   
    

/**  Module ID for TDAS bundle feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_BUNDLE           0x000106cb

/**  Module ID for Mono To Stereo Creator feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_M2S              0x000106d7

/**  Module ID for sound space expander feature in Dolby Audio Kernel.
            This feature shall be used for speaker only*/
#define ADM_DAK_MODULE_ID_SSE              0x000106dc

/**  Module ID for Sound level control feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_SLC              0x000106e5

/**  Module ID for volume control feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_VOL              0x000106ef

/**  Module ID for Natural bass feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_NAT_BASS         0x000106fb

/**  Module ID for Graphic EQ feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_GEQ              0x000106e9

/**  Module ID for Mobile Surround feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_MSR              0x000106e0

/**  Module ID for High Frequency Enhancer feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_HFE              0x000106d9

/**  Module ID for Fade processing feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_FADE             0x00010700

/**  Module ID for Speaker EQ feature in Dolby Audio Kernel */
#define ADM_DAK_MODULE_ID_SEQ              0x000106f6


/***************************************************************/
/*  PARAMETERS IN THE BUNDLE MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/
/**   Parameter ID  for input matrix mapping parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_IN_MATRIX                 0x000106cd

#define	ADM_DAK_PARAM_IN_MATRIX_STEREO                  0 /**< left and right input channels are treated normally*/
#define	ADM_DAK_PARAM_IN_MATRIX_LEFT                    1 /**< right channel is replaced by left input channel internally*/
#define ADM_DAK_PARAM_IN_MATRIX_RIGHT                   2 /**< left channel is replaced by the right input channel internally*/
#define ADM_DAK_PARAM_IN_MATRIX_DUALMONO	             3 /**< both channels are summed and replicated to both channels internally. */
#define	ADM_DAK_PARAM_IN_MATRIX_PL2                     4 /**< left and right channels are treated as Pro-Logic II encoded. */

/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_IN_MATRIX */
typedef struct adm_dak_param_in_matrix_t adm_dak_param_in_matrix_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_IN_MATRIX */
struct adm_dak_param_in_matrix_t
{
    int32_t                  in_matrix; /**< specifies how the two channel input 
    is mixed to form the two channel samples that are processed by DAK.  
    This parameter is only relevant when the input signal is stereo. 
    See ADM_DAK_PARAM_IN_MATRIX_XXX macros for supported values. 
    */
}
#include "adsp_end_pack.h"
;

/**   Parameter ID  for LFE mix level parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_LFE_MIX_LEVEL             0x000106cc

/** Minimum LFE mix level */
#define ADM_DAK_PARAM_TDAS_LFE_MIX_MIN				31
/** Maximum LFE mix level */
#define ADM_DAK_PARAM_TDAS_LFE_MIX_MAX				0


/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_LFE_MIX_LEVEL */
typedef struct adm_dak_param_lfe_mix_level_t adm_dak_param_lfe_mix_level_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_LFE_MIX_LEVEL */
struct adm_dak_param_lfe_mix_level_t
{
    int32_t                  mix_level; 
    /**< Supports from ADM_DAK_PARAM_TDAS_LFE_MIX_MAX to ADM_DAK_PARAM_TDAS_LFE_MIX_MIN. 
    Default is 10. Determines the level at which the LFE channel is mixed into the
    output audio. The effective mix level gain in (dB) = 5.5 – this value.
    */
}
#include "adsp_end_pack.h"
;

/**   Parameter ID  for Mobile surround max profile parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_MSR_MAX_PROFILE           0x000106cf

#define ADM_DAK_PARAM_MSR_MAX_PROFILE_STEREO  0    /**< Rendering up to 2 virtual channels */
#define ADM_DAK_PARAM_MSR_MAX_PROFILE_FOUR    1    /**< Rendering up to 4 virtual channels */
#define ADM_DAK_PARAM_MSR_MAX_PROFILE_FIVE    2    /**< Rendering up to 5 virtual channels */
#define ADM_DAK_PARAM_MSR_MAX_PROFILE_SEVEN   3    /**< Rendering up to 7 virtual channels */

/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_MSR_MAX_PROFILE */
typedef struct adm_dak_param_msr_max_profile_t adm_dak_param_msr_max_profile_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_MSR_MAX_PROFILE */
struct adm_dak_param_msr_max_profile_t
{
    int32_t                  profile; 
    /**< Controls the maximum number of virtual rendering channels in Mobile
    Surround. When the value is zero, mobile surround upmixer is disabled. See
    ADM_DAK_PARAM_MSR_MAX_PROFILE_XXX macros for supported values. 
    */
}
#include "adsp_end_pack.h"
;

/**   Parameter ID  for portable mode enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE              0x000106d2

/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE */
typedef struct adm_dak_param_portable_mode_t adm_dak_param_portable_mode_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE */
struct adm_dak_param_portable_mode_t
{
    int32_t                  enable; 
    /**< 1 for enable Portable mode feature. 0 for disable.*/
}
#include "adsp_end_pack.h"
;


/**   Parameter ID  for portable mode gain parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_GAIN         0x000106d3 

/* The minimum portable mode gain which correspond to -11dB*/
#define ADM_DAK_PARAM_TDAS_PORTABLEMODE_GAIN_MIN     -44   
/* The maximum portable mode gain which correspond to 40dB*/
#define ADM_DAK_PARAM_TDAS_PORTABLEMODE_GAIN_MAX     160  


/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_GAIN */
typedef struct adm_dak_param_portable_mode_gain_t adm_dak_param_portable_mode_gain_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_GAIN */
struct adm_dak_param_portable_mode_gain_t
{
    int32_t                  gain; 
    /**< Index of gain applied to modify the loudness of the signal 
         to reach –11 dB. Supports ADM_DAK_PARAM_TDAS_PORTABLEMODE_GAIN_MIN
          to ADM_DAK_PARAM_TDAS_PORTABLEMODE_GAIN_MAX which corresponds to -11dB and 40dB. 
         0.25dB increment in between. */
}
#include "adsp_end_pack.h"
;

/**   Parameter ID  for portable mode output reference level parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_ORL          0x000106d4

#define ADM_DAK_PARAM_PORTABLEMODE_ORL_8DB      0     /**< -8dB Portable Mode ORL */
#define ADM_DAK_PARAM_PORTABLEMODE_ORL_11DB     1     /**< Default, -11dB Portable Mode ORL */
#define ADM_DAK_PARAM_PORTABLEMODE_ORL_14DB     2     /**< -14dB Portable Mode ORL */

/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_ORL */
typedef struct adm_dak_param_portable_mode_orl_t adm_dak_param_portable_mode_orl_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PORTABLEMODE_ORL */
struct adm_dak_param_portable_mode_orl_t
{
    int32_t                  out_ref_level; 
    /**< determine the output reference level in portable mode.
        See ADM_DAK_PARAM_PORTABLEMODE_ORL_XXX for supported values. */
}
#include "adsp_end_pack.h"
;


/**   Parameter ID  for Pulse downmix enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX              0x000106d5


/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX */
typedef struct adm_dak_param_pulse_downmix_t adm_dak_param_pulse_downmix_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX */
struct adm_dak_param_pulse_downmix_t
{
    int32_t                  enable; 
    /**< 1 for notify the pulse decoder downmixing is enabled. 0 for disable.*/
}
#include "adsp_end_pack.h"
;

/**  Parameter ID  for Pulse downmix attenuation level parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX_ATTEN        0x000106d6

/**  The maximum Pulse Downmixer attenuation */
#define ADM_DAK_PARAM_TDAS_PULSEDOWNMIX_ATTEN_MAX    -40   
/**  The minimum Pulse Downmixer attenuation */
#define ADM_DAK_PARAM_TDAS_PULSEDOWNMIX_ATTEN_MIN    0   


/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX_ATTEN */
typedef struct adm_dak_param_pulse_downmix_atten_t adm_dak_param_pulse_downmix_atten_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_TDAS_PULSEDOWNMIX_ATTEN */
struct adm_dak_param_pulse_downmix_atten_t
{
    int32_t                  atten; 
    /**< attenuation applied by the Dolby Pulse downmixer. 
    Supports value range from ADM_DAK_PARAM_TDAS_PULSEDOWNMIX_ATTEN_MAX to 
    ADM_DAK_PARAM_TDAS_PULSEDOWNMIX_ATTEN_MIN
    (-10dB and 0dB correspondingly with 0.25dB increament in between)*/
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Mono To Stereo MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Mono To Stereo Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_M2S_ENABLE			0x000106d8	

/** @brief Param structure for ADM_DAK_PARAM_ID_M2S_ENABLE */
typedef struct adm_dak_param_m2s_enable_t adm_dak_param_m2s_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_M2S_ENABLE */
struct adm_dak_param_m2s_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable Mono To Stereo creator. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Sound Space Expander MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Sound Space Expander Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SSE_ENABLE			0x000106dd	

/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_ENABLE */
typedef struct adm_dak_param_sse_enable_t adm_dak_param_sse_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_ENABLE */
struct adm_dak_param_sse_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable Sound space expander. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Sound Space Expander Width parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SSE_WIDTH			0x000106de	

#define ADM_DAK_PARAM_SSE_WIDTH_HALF		0 /**< moderate amount of stereo widening*/
#define ADM_DAK_PARAM_SSE_WIDTH_FULL		1 /**< maximum amount of stereo widening.*/

/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_WIDTH */
typedef struct adm_dak_param_sse_width_t adm_dak_param_sse_width_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_WIDTH */
struct adm_dak_param_sse_width_t
{
    int32_t                  width; 
    /**<  Determines the amount of stereo widening. 
        See ADM_DAK_PARAM_SEE_WIDTH_XXX macro for supported values */
}
#include "adsp_end_pack.h"
;


/**  Parameter ID for Sound Space Expander Speaker Mode parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SSE_SPK_MODE			0x000106df	

#define ADM_DAK_PARAM_SSE_SPK_NORMAL       0  /**< for devices that have a greater distance between the two speakers
than that between speakers on a portable or mobile device */
#define ADM_DAK_PARAM_SSE_SPK_NARROW	    1  /**< for closely spaced speakers */
#define ADM_DAK_PARAM_SSE_SPK_BINAURAL     2  /**< intended for
    processing audio that has been specifically preencoded for Mobile
    Surround processing, allowing such audio to be rendered via speakers */

/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_SPK_MODE */
typedef struct adm_dak_param_sse_spk_mode_t adm_dak_param_sse_spk_mode_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SSE_SPK_MODE */
struct adm_dak_param_sse_spk_mode_t
{
    int32_t                  speaker; 
    /**<  Specifies the speaker setting for Sound space expander. 
           See ADM_DAK_PARAM_SSE_SPK_XXX macros for supported values. */
}
#include "adsp_end_pack.h"
;


/***************************************************************/
/*  PARAMETERS IN THE Sound Level Controller MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Sound Level Controller Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SLC_ENABLE			0x000106e6	

/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_ENABLE */
typedef struct adm_dak_param_slc_enable_t adm_dak_param_slc_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_ENABLE */
struct adm_dak_param_slc_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable Sound Level Controller. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Sound Level Controller Level parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SLC_LEVEL			0x000106e7	

/** Minimum SLC level value */
#define ADM_DAK_PARAM_SLC_LEVEL_MIN		0	
/** Maximum SLC level value */
#define ADM_DAK_PARAM_SLC_LEVEL_MAX		6
	
/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_LEVEL */
typedef struct adm_dak_param_slc_level_t adm_dak_param_slc_level_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_LEVEL */
struct adm_dak_param_slc_level_t
{
    int32_t                  level; 
    /**<  Specifies the RMS level of input audio. 
          Supports ADM_DAK_PARAM_SLC_LEVEL_MIN to ADM_DAK_PARAM_SLC_LEVEL_MAX.  
          ADM_DAK_PARAM_SLC_LEVEL_MIN is for very loud, heavily Range compressed music 
          and ADM_DAK_PARAM_SLC_LEVEL_MAX is for quiet film tracks with large dynamic ranges. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Sound Level Controller Depth parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SLC_DEPTH			0x000106e8	

/** Minimum sound level control depth */
#define ADM_DAK_PARAM_SLC_DEPTH_MIN			0	
/** Minimum sound level control depth */
#define ADM_DAK_PARAM_SLC_DEPTH_MAX			2	

/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_DEPTH */
typedef struct adm_dak_param_slc_depth_t adm_dak_param_slc_depth_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SLC_DEPTH */
struct adm_dak_param_slc_depth_t
{
    int32_t                  depth; 
    /**<  Specifies the effect of dynmic range control. Supports 
         ADM_DAK_PARAM_SLC_DEPTH_MIN to ADM_DAK_PARAM_SLC_DEPTH_MAX. 
        ADM_DAK_PARAM_SLC_DEPTH_MIN for having the minimum effect 
        and ADM_DAK_PARAM_SLC_DEPTH_MAX for having the strongest effect.  */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Volume control MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for VOLUME CONTROL Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_ENABLE			0x000106f0	

/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_ENABLE */
typedef struct adm_dak_param_vol_enable_t adm_dak_param_vol_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_ENABLE */
struct adm_dak_param_vol_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable volume control. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for VOLUME CONTROL internal gain parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_GAIN_INTERNAL			0x000106f2	
/**  Parameter ID for VOLUME CONTROL external gain parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_GAIN_EXTERNAL			0x000106f3	

/** Minimum Volume control gain value*/
#define ADM_DAK_PARAM_VOL_GAIN_MIN			0
/** Maximum Volume control gain value*/
#define ADM_DAK_PARAM_VOL_GAIN_MAX			255

/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_GAIN_INTERNAL and  ADM_DAK_PARAM_ID_VOL_GAIN_EXTERNAL*/
typedef struct adm_dak_param_vol_gain_t adm_dak_param_vol_gain_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_GAIN_INTERNAL and  ADM_DAK_PARAM_ID_VOL_GAIN_EXTERNAL*/
struct adm_dak_param_vol_gain_t
{
    int32_t                  gain; 
    /**<  Specifies the volume gain that DAK is going to apply to signals. 
           Supports 0 to 255. 
           For linear gain type, 0: 1.0 (volume is unchanged) and 255: 1/256 with -1/256 increments in between. 
           For logarithmic gain type, 0: 0dB and -0.25dB increments from 0 to 255. 
        */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for VOLUME CONTROL gain type parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_GAIN_TYPE			0x000106f1	

#define ADM_DAK_PARAM_VOL_LINEAR              0    /**< Linear gain type*/
#define ADM_DAK_PARAM_VOL_LOGARITHMIC         1    /**< Logarithmic gain type*/

/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_GAIN_TYPE*/
typedef struct adm_dak_param_vol_gain_type_t adm_dak_param_vol_gain_type_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_GAIN_TYPE*/
struct adm_dak_param_vol_gain_type_t
{
    int32_t                  gain_type; 
    /**<  specifies the unit by which the volume level is specified.
          supports ADM_DAK_PARAM_VOL_LINEAR and ADM_DAK_PARAM_VOL_LOGARITHMIC
          types. The gain type applies to all subsequent volume control gain commands 
          in adm_dak_param_vol_xxx until gain type is sent again. 
        */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for VOLUME CONTROL balance parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_BALANCE			0x000106f4	

/** The minimum volume balance value*/
#define ADM_DAK_PARAM_VOL_BALANCE_MIN		(-127)
/** The maximum volume balance value*/
#define ADM_DAK_PARAM_VOL_BALANCE_MAX		(127)


/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_BALANCE*/
typedef struct adm_dak_param_vol_balance_t adm_dak_param_vol_balance_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_BALANCE*/
struct adm_dak_param_vol_balance_t
{
    int32_t                  balance; 
    /**<  specifies the balance between left and right channel volume.
          Supports from ADM_DAK_PARAM_VOL_BALANCE_MIN to ADM_DAK_PARAM_VOL_BALANCE_MAX.
          The attenuation applied to right channel increases as this setting changes from –1 to –127, 
          while the attenuation applied to left channel increases as this setting changes from 1 to 127. 
          There is no additional attenuation on either left or right channel for zero.  
          For linear gain type, decreases in -1/128 increments. 
          For logarithmic gain type, decreases in -0.25dB. 
        */
}
#include "adsp_end_pack.h"
;
	
/**  Parameter ID for VOLUME CONTROL mute parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_VOL_MUTE			0x000106f5	

/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_MUTE*/
typedef struct adm_dak_param_vol_mute_t adm_dak_param_vol_mute_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_VOL_MUTE*/
struct adm_dak_param_vol_mute_t
{
    int32_t                  mute; 
    /**<  1 for mute the audio. 0 for unmute. */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Natural Bass MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Natural Bass Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_NAT_BASS_ENABLE			0x000106fc	

/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_ENABLE */
typedef struct adm_dak_param_nat_bass_enable_t adm_dak_param_nat_bass_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_ENABLE */
struct adm_dak_param_nat_bass_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable natural bass. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Natural Bass cut-off parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_NAT_BASS_CUTOFF			0x000106fd	

/** The minimum natural bass cut-off value */
#define ADM_DAK_PARAM_NAT_BASS_CUTOFF_MIN			0	
/** The maximum natural bass cut-off value */
#define ADM_DAK_PARAM_NAT_BASS_CUTOFF_MAX			23


/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_CUTOFF */
typedef struct adm_dak_param_nat_bass_cutoff_t adm_dak_param_nat_bass_cutoff_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_CUTOFF */
struct adm_dak_param_nat_bass_cutoff_t
{
    int32_t                  cutoff; 
    /**<   This specifies cut-off frequency used in Natural Bass. 
            Supports from ADM_DAK_PARAM_NAT_BASS_CUTOFF_MIN to ADM_DAK_PARAM_NAT_BASS_CUTOFF_MAX. 
            See Table 3.38 of the ISOD appendix on Dolby Audio Kernel feature 
            for the mapping between the parameter value and the cut-off frequency 
            for natural bass. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Natural Bass boost parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_NAT_BASS_BOOST			0x000106fe	

/** The minimum natural bass boost level */
#define ADM_DAK_PARAM_NAT_BASS_BOOST_MIN			0	
/** The maximum natural bass boost level */
#define ADM_DAK_PARAM_NAT_BASS_BOOST_MAX			6	


/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_BOOST */
typedef struct adm_dak_param_nat_bass_boost_t adm_dak_param_nat_bass_boost_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_BOOST */
struct adm_dak_param_nat_bass_boost_t
{
    int32_t                  boost; 
    /**<   	This specifies the effect of natural bass. 
            Supports from ADM_DAK_PARAM_NAT_BASS_BOOST_MIN to ADM_DAK_PARAM_NAT_BASS_BOOST_MAX. 
            ADM_DAK_PARAM_NAT_BASS_BOOST_MIN have weakest effect. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Natural Bass level parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_NAT_BASS_LEVEL			0x000106ff	

/**  The minimum natural bass level */
#define ADM_DAK_PARAM_NAT_BASS_LEVEL_MIN			0	
/**  The maximum natural bass level */
#define ADM_DAK_PARAM_NAT_BASS_LEVEL_MAX			6	


/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_LEVEL */
typedef struct adm_dak_param_nat_bass_level_t adm_dak_param_nat_bass_level_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_NAT_BASS_LEVEL */
struct adm_dak_param_nat_bass_level_t
{
    int32_t                  level; 
    /**<   	specifies the output capability of the device.
            Supports ADM_DAK_PARAM_NAT_BASS_LEVEL_MIN to ADM_DAK_PARAM_NAT_BASS_LEVEL_MAX. 
            ADM_DAK_PARAM_NAT_BASS_LEVEL_MIN have the highest output capability.  */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Graphic EQ MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Graphic EQ Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_GEQ_ENABLE			0x000106ea	

/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_ENABLE */
typedef struct adm_dak_param_geq_enable_t adm_dak_param_geq_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_ENABLE */
struct adm_dak_param_geq_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable graphic EQ. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Graphic EQ Number of Frequency Bands parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_GEQ_NBANDS			0x000106eb	

/** The minimum number of bands in Graphic EQ */
#define ADM_DAK_PARAM_GEQ_NBANDS_MIN	   2
/** The max number of bands in Graphic EQ */
#define ADM_DAK_PARAM_GEQ_NBANDS_MAX      7
	

/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_NBANDS */
typedef struct adm_dak_param_geq_nbands_t adm_dak_param_geq_nbands_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_NBANDS */
struct adm_dak_param_geq_nbands_t
{
    int32_t                  nbands; 
    /**<  Number of frequency bands for graphic equalizer.
           Supports ADM_DAK_PARAM_GEQ_NBANDS_MIN to ADM_DAK_PARAM_GEQ_NBANDS_MAX. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Graphic EQ PreAmp parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_GEQ_PREAMP			0x000106ec	

/** The minimum of Graphic EQ PreAmp */
#define ADM_DAK_PARAM_GEQ_PREAMP_MIN		-48	
/** The maximum of Graphic EQ PreAmp */
#define ADM_DAK_PARAM_GEQ_PREAMP_MAX		0	

/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_PREAMP */
typedef struct adm_dak_param_geq_preamp_t adm_dak_param_geq_preamp_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_PREAMP */
struct adm_dak_param_geq_preamp_t
{
    int32_t                  preamp; 
    /**<  specifies the amount of attenuation applied  by Graphic EQ uniformly across the spectrum. 
        Supports from ADM_DAK_PARAM_GEQ_PREAMP_MIN to ADM_DAK_PARAM_GEQ_PREAMP_MAX. 
        ADM_DAK_PARAM_GEQ_PREAMP_MAX correspond to no attenuation. 
        ADM_DAK_PARAM_GEQ_PREAMP_MIN correspond to -12dB. 
        Between ADM_DAK_PARAM_GEQ_PREAMP_MIN and ADM_DAK_PARAM_GEQ_PREAMP_MAX, -0.25dB increment */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Graphic EQ Max Boost parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_GEQ_MAX_BOOST			0x000106ed	

/** The minimum of allowable Graphic EQ max-boost */
#define ADM_DAK_PARAM_GEQ_MAX_BOOST_MIN			0	
/** The maximum of allowable Graphic EQ max-boost */
#define ADM_DAK_PARAM_GEQ_MAX_BOOST_MAX			48	

/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_MAX_BOOST */
typedef struct adm_dak_param_geq_max_boost_t adm_dak_param_geq_max_boost_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_MAX_BOOST */
struct adm_dak_param_geq_max_boost_t
{
    int32_t                  max_boost; 
    /**<  specifies the maxium amount of boost applied on any frequency band in 
          increments of 0.25 dB, ranging from 
          ADM_DAK_PARAM_GEQ_MAX_BOOST_MIN (no boost) to 
          ADM_DAK_PARAM_GEQ_MAX_BOOST_MAX (12 dB, maximum boost). */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Graphic EQ Band Attenuation parameter in Dolby Audio Kernel. */
#define ADM_DAK_PARAM_ID_GEQ_BAND_ATTN			0x000106ee	

/** Minimum Graphic EQ band attenuation */
#define ADM_DAK_PARAM_GEQ_BAND_ATTN_MIN		(-48)	
/** Maximum Graphic EQ band attenuation  */
#define ADM_DAK_PARAM_GEQ_BAND_ATTN_MAX		(48)	

/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_MAX_BOOST */
typedef struct adm_dak_param_geq_band_attn_t adm_dak_param_geq_band_attn_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_GEQ_MAX_BOOST */
struct adm_dak_param_geq_band_attn_t
{
    int32_t     num_bands_to_config; /**< number of frequency bands that are to be configured by this command.
    The value shall be no larger than the maximum number of bands that is specified in ADM_DAK_PARAM_ID_GEQ_NBANDS*/
    int32_t     band_idx;          /**< To which band the next field shall applies. 
     band index starts from 1. */
    int32_t     band_attn;         /**< Boost or attenuation level applied on the above specified band. 
    The control is increment of 0.25dB from -12 dB(ADM_DAK_PARAM_GEQ_BAND_ATTN_MIN) 
    to +12 dB(ADM_DAK_PARAM_GEQ_BAND_ATTN_MAX).     */
    /** More band_idx and band_attn pairs might follow depends 
    on the num_bands_to_config*/
}
#include "adsp_end_pack.h"
;


/***************************************************************/
/*  PARAMETERS IN THE Mobile Surround MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Mobile Surround Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_MSR_ENABLE			0x000106e2	

/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_ENABLE */
typedef struct adm_dak_param_msr_enable_t adm_dak_param_msr_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_ENABLE */
struct adm_dak_param_msr_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable mobile surround. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Mobile Surround Room parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_MSR_ROOM			0x000106e3	

/** The mimimum MSR room */
#define ADM_DAK_PARAM_MSR_ROOM_MIN			0	
/** The maximum MSR room */
#define ADM_DAK_PARAM_MSR_ROOM_MAX			2	


/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_ROOM */
typedef struct adm_dak_param_msr_room_t adm_dak_param_msr_room_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_ROOM */
struct adm_dak_param_msr_room_t
{
    int32_t                  room; 
    /**<  This parameter controls the perceived size of a room and the sense of environment 
          Supports from ADM_DAK_PARAM_MSR_ROOM_MIN to 
          ADM_DAK_PARAM_MSR_ROOM_MAX.
          ADM_DAK_PARAM_MSR_ROOM_MIN: the narrowest room;
          ADM_DAK_PARAM_MSR_ROOM_MAX: the largest room.  */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Mobile Surround Bright parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_MSR_BRIGHT			0x000106e4	

/** The minimum MSR bright value*/
#define ADM_DAK_PARAM_MSR_BRIGHT_MIN			0	
/** The maximum MSR bright value*/
#define ADM_DAK_PARAM_MSR_BRIGHT_MAX			2	


/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_BRIGHT */
typedef struct adm_dak_param_msr_bright_t adm_dak_param_msr_bright_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_MSR_BRIGHT */
struct adm_dak_param_msr_bright_t
{
    int32_t                  bright; 
    /**<  controls the perceived brightness. 
        Supports from ADM_DAK_PARAM_MSR_BRIGHT_MIN to ADM_DAK_PARAM_MSR_BRIGHT_MAX. 
        ADM_DAK_PARAM_MSR_BRIGHT_MIN: warm (least high frequency); 
        ADM_DAK_PARAM_MSR_BRIGHT_MAX: bright (have most high frequency).   
        */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Hight Frequency Enhancer MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for High Frequency Enhancer Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_HFE_ENABLE			0x000106da	

/** @brief Param structure for ADM_DAK_PARAM_ID_HFE_ENABLE */
typedef struct adm_dak_param_hfe_enable_t adm_dak_param_hfe_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_HFE_ENABLE */
struct adm_dak_param_hfe_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable high frequency enhancer. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for High Frequency Enhancer Depth parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_HFE_DEPTH			0x000106db	

/** The minimum HFE depth */
#define ADM_DAK_PARAM_HFE_DEPTH_MIN			0	
/** The maximum HFE depth */
#define ADM_DAK_PARAM_HFE_DEPTH_MAX			6	


/** @brief Param structure for ADM_DAK_PARAM_ID_HFE_DEPTH */
typedef struct adm_dak_param_hfe_depth_t adm_dak_param_hfe_depth_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_HFE_DEPTH */
struct adm_dak_param_hfe_depth_t
{
    int32_t                  depth; 
    /**<  specifies the level of high frequency components that are to be added to original signals. 
         Supports ADM_DAK_PARAM_HFE_DEPTH_MIN (least depth of effect) 
         to ADM_DAK_PARAM_HFE_DEPTH_MAX (greatest depth of effect)*/
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Fade processing MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/

/**  Parameter ID for Fade Processing Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_FADE_ENABLE			0x00010701	

/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_ENABLE */
typedef struct adm_dak_param_fade_enable_t adm_dak_param_fade_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_ENABLE */
struct adm_dak_param_fade_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable fade processing feature. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Fade Processing TARGET parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_FADE_TARGET			0x00010702	

/**  The minimum fade target level */
#define ADM_DAK_PARAM_FADE_TARGET_MIN			0	
/**  The maximum fade target level */
#define ADM_DAK_PARAM_FADE_TARGET_MAX			255	


/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_TARGET */
typedef struct adm_dak_param_fade_target_t adm_dak_param_fade_target_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_TARGET */
struct adm_dak_param_fade_target_t
{
    int32_t                  target; 
    /**<  specifies the target attenuation level applied to audio when fading is over.
          Supports from ADM_DAK_PARAM_FADE_TARGET_MIN (no fade) 
          to ADM_DAK_PARAM_FADE_TARGET_MAX (the maximum attenuation level)
          with -1/256 increment inbetween. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Fade Processing Time during parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_FADE_TIME			0x00010703	

/**  The minimum fading time in milliseconds */
#define ADM_DAK_PARAM_FADE_TIME_MIN			32
/**  The maximum fading time in milliseconds */
#define ADM_DAK_PARAM_FADE_TIME_MAX			3968
	


/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_TIME */
typedef struct adm_dak_param_fade_time_t adm_dak_param_fade_time_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_FADE_TIME */
struct adm_dak_param_fade_time_t
{
    int32_t                  time; 
    /**<  Specifiestotal fading time in milliseconds. Supports from 
    ADM_DAK_PARAM_FADE_TIME_MIN to ADM_DAK_PARAM_FADE_TIME_MAX */
}
#include "adsp_end_pack.h"
;

/***************************************************************/
/*  PARAMETERS IN THE Speaker EQ MODULE OF DOLBY AUDIO KERNEL */ 
/***************************************************************/
/**  Parameter ID for Speaker EQ Enable parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SEQ_ENABLE			0x000106f7	

/** @brief Param structure for ADM_DAK_PARAM_ID_SEQ_ENABLE */
typedef struct adm_dak_param_seq_enable_t adm_dak_param_seq_enable_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SEQ_ENABLE */
struct adm_dak_param_seq_enable_t
{
    int32_t                  enable; 
    /**<  1 for enable Speaker EQ feature. 0 for otherwise. */
}
#include "adsp_end_pack.h"
;

/**  Parameter ID for Speaker EQ Left Channel Gain parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SEQ_GAIN_L			0x000106f8	
/**  Parameter ID for Speaker EQ Right Channel Gain parameter in Dolby Audio Kernel */
#define ADM_DAK_PARAM_ID_SEQ_GAIN_R			0x000106f9	

/**  The minimum gain value for speaker EQ */
#define ADM_DAK_PARAM_SEQ_GAIN_MIN			-24	
/**  The maximum gain value for speaker EQ */
#define ADM_DAK_PARAM_SEQ_GAIN_MAX			24	


/** @brief Param structure for ADM_DAK_PARAM_ID_SEQ_GAIN_L and ADM_DAK_PARAM_ID_SEQ_GAIN_R */
typedef struct adm_dak_param_seq_gain_t adm_dak_param_seq_gain_t;

#include "adsp_begin_pack.h"
/** @brief Param structure for ADM_DAK_PARAM_ID_SEQ_GAIN_L and ADM_DAK_PARAM_ID_SEQ_GAIN_R */
struct adm_dak_param_seq_gain_t
{
    int32_t                  gain; 
    /**< specifies additional gain on left or right channel depends on param ID.  
         Supports from ADM_DAK_PARAM_SEQ_GAIN_MIN (–6 dB) to 
         ADM_DAK_PARAM_SEQ_GAIN_MAX  (+6 dB) with 0.25dB increments in between */
}
#include "adsp_end_pack.h"
;

/** Parameter ID  to set Speaker EQ coefficients for 48kHz */
#define ADM_DAK_PARAM_ID_SEQ_COEF_48K   0x000106fa

/** The maximum number of filter per channel for speake EQ */
#define ADM_DAK_PARAM_SEQ_NUM_FILTER_MAX   4

/** @brief Param structure for ADM_DAK_PARAM_ID_SEQ_COEF_48K */
typedef struct adm_dak_param_seq_coef_t adm_dak_param_seq_coef_t;

#include "adsp_begin_pack.h"
/** @brief Payload Structure for ADM_DAK_PARAM_ID_SEQ_COEF_48K parameters */
struct adm_dak_param_seq_coef_t
{
   uint16_t    num_filter_per_chan; /**< Number of filters per channel. Supports up to 4 */
   uint16_t    request_headroom;    /**< Request head room 0.25 dB units */
   /** The rest of payload specifies the filter coefficients and scaling factors.  
        The size depends on num_filter_per_chan. See Audio ISOD appendix on 
        Dolby Audio Kernel for more descritioins */ 
}  
#include "adsp_end_pack.h"
;


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif // #ifdef _ADSP_DOLBY_AUDIO_KERNEL_API_H_
