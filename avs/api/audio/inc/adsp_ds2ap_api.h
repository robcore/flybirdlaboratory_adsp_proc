#ifndef _ADSP_DS2APv2_API_H_
#define _ADSP_DS2APv2_API_H_

/**
 @file adsp_ds2ap_api.h

 @brief This file contains the structure definitions for the
 commands related with Dolby Surround2 Audio Processing.
 */

/*===========================================================================
 Copyright (c) 2013 Qualcomm Technologies, Inc. All rights reserved.
 Qualcomm Technologies Proprietary and Confidential.
 ===========================================================================*/

/*========================================================================
 Edit History
 when       who     what, where, why
 --------   ---     -------------------------------------------------------
 12/12/13   bvodapal      API file for DS2AP

 ========================================================================== */

#include "mmdefs.h"

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/      

   /** Dolby Surround II  COPP Topology ID. The client can route multiple ASM session to this COPP with Matrix operating in Native mode. */

   /** @addtogroup audio_pp_topos_adm
    @{ */
   /** @cond OEM_only */
   /** ID of the COPP topology of DS2AP, for the Dolby Surround II Feature

    @inputfig{1,ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DS2AP_topology.png}
    
    - DS2AP                             (#AUDPROC_MODULE_ID_DS2AP)
    */
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DS2AP 				0x00010348

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_topos_adm */

   /** @addtogroup audiopp_topos_asm
    @{ */
   /** @cond OEM_only */
   /** ID of the Dolby Surround II audio post-processing stream topology.


    @inputfig{1,AUDPROC_POPP_TOPOLOGY_ID_DS2AP_topology.png}

    - DS2AP                             (#AUDPROC_MODULE_ID_DS2AP)

    */
#define ASM_STREAM_POSTPROC_TOPO_ID_DS2AP             0x00012f17

   /** @endcond */
   /** @} *//* end_addtogroup audiopp_topos_asm */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap
    @{ */
   /** ID of the module Dolby Surround II. All the module parameters are generic parameters of the Dolby Surround II module.
    * This ID can be used to create custom topology. All the configuration  must be defined under this module id if it is to be
    *  used as custom topology
    This module supports the following parameter IDs:
	 - #AUDPROC_PARAM_ID_DS2AP_DESIGN_MODE
	 - #AUDPROC_PARAM_ID_DS2AP_MODE
	 - #AUDPROC_PARAM_ID_DS2AP_MI_ENABLE
    - #AUDPROC_PARAM_ID_DS2AP_MIXED_STEREO_ENABLE
    */

#define AUDPROC_MODULE_ID_DS2AP                       	    0x000108DA


   /** ID to set the design mode of Dolby Surround II used by AUDPROC_MODULE_ID_DS2AP.

    @msgpayload{audproc_param_id_ds2ap_design_mode_t}
    @table{weak__audproc__param__id__ds2ap__design__mode__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DESIGN_MODE                   0x000108DB

   /** ID to set the DS2AP MODE configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP.

    @msgpayload{audproc_param_id_ds2ap_mode_t}
    @table{weak__audproc__param__id__ds2ap__mode__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_MODE                          0x000108DC

   /** ID to set the DS2AP Media Intelligence configuration parameter of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP.

     @msgpayload{audproc_param_id_ds2ap_mi_enable_t}
     @table{weak__audproc__param__id__ds2ap__mi__enable__t}
     */
 #define AUDPROC_PARAM_ID_DS2AP_MI_ENABLE                     0x000108DD


   /** ID to Set the Mixed Stereo Enable parameter for Dolby Surround II used by AUDPROC_MODULE_ID_DS2AP.

    @msgpayload{audproc_param_id_ds2ap_mixed_stereo_t}
    @table{weak__audproc__param__id__ds2ap__mixed__stereo__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_MIXED_STEREO_ENABLE           0x000108DE

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap */

   /* Structure for the ds2ap design mode parameter for a DS2AP module. */
   typedef struct audproc_param_id_ds2ap_design_mode_t audproc_param_id_ds2ap_design_mode_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_design_mode_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DESIGN_MODE parameter used by the DS2AP module.
    */
   struct audproc_param_id_ds2ap_design_mode_t
   {
      uint32_t design_mode;
      /**< Supported Values:
       1 : Complete DS2AP Processing chain implemented in POPP
       2 : Complete DS2AP Processing chain implemented in COPP
       3 : Content processing of audio is implemented in POPP and
       the Device processing and Virtualization implemented in COPP
       default: 3
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_design_mode_t */

   /* Structure for the ds2ap mode  parameters for a DS2AP module. */
   typedef struct audproc_param_id_ds2ap_mode_t audproc_param_id_ds2ap_mode_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_mode_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_MODE parameter used by the DS2AP module.
    */
   struct audproc_param_id_ds2ap_mode_t
   {

      int32_t mode;
      /**<
       Supported Values :
       For COPP Topology :
       DS2AP_MODE_NO_DUAL_VIRTUALIZER (1)
       For POPP Topology :
       DS2AP_MODE_NO_DEVICE_PROCESSING (2)
       DS2AP_MODE_DV_DE_ONLY (3)
       Default :
       For POPP topology : DS2AP_MODE_NO_DEVICE_PROCESSING (2)
       For COPP topology : DS2AP_MODE_NO_DUAL_VIRTUALIZER (1)
       Parameter Type : User Configurable.
       The mode determines the ds2ap core processing modules that will be available in the chain of audio processing.
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_mode_t */

   /* Structure for the ds2ap MI Enable configuration parameter for a DS2AP module. */
   typedef struct audproc_param_id_ds2ap_mi_enable_t audproc_param_id_ds2ap_mi_enable_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_mi_enable_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_MI_ENABLE parameter used by the DS2AP module.
    */
   struct audproc_param_id_ds2ap_mi_enable_t
   {
      uint32_t enable;
      /**< Supported Values:
       0 : Disable
       1 : Enable
       default: 1
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_mi_enable_t */


   /* Structure for the mixed stereo enable parameter for a DS2AP module. */
   typedef struct audproc_param_id_ds2ap_mixed_streo_enable_t audproc_param_id_ds2ap_mixed_streo_enable_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_mixed_stereo_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_MIXED_STEREO_ENABLE parameter used by the DS2AP module.
    */
   struct audproc_param_id_ds2ap_mixed_streo_enable_t
   {
      uint32_t enable;
      /**< Supported Values:
       0 - L and R channels will be unmodified.
       any other value – L and R will be mixed to provide (L+R)/2 on both channels
       Default : 0
       Parameter Type : Factory Configurable.
       Enables or disables the mixed stereo mode. The mixed stereo mode only
       takes effect when the output has L and R channels only.
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_mixed_stereo_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_bundle
    @{ */
   /** ID of the Bundle module of Dolby Surround II. All these module parameters correspond to the generic parameters of the
    * Dolby Surround II core audio processing chain of module .
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_BUNDLE_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_DOWNMIXER_CONFIG
    */

#define AUDPROC_MODULE_ID_DS2AP_BUNDLE                      0x000108DF

   /** ID to set the Generic configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_BUNDLE.

    @msgpayload{audproc_param_id_ds2ap_bundle_config_t}
    @table{weak__audproc__param__id__ds2ap__bundle__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_BUNDLE_CONFIG                0x000108E0

   /** ID to set the DS2AP downmixer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_BUNDLE.

    @msgpayload{audproc_param_id_ds2ap_downmixer_config_t}
    @table{weak__audproc__param__id__ds2ap__downmixer__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DOWNMIXER_CONFIG             0x000108E1

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_bundle */


   /* Structure for the ds2ap bundle configuration for a DS2AP Bundle module. */
   typedef struct audproc_param_id_ds2ap_bundle_config_t audproc_param_id_ds2ap_bundle_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_bundle_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_BUNDLE_CONFIG parameter used by the DS2AP Bundle module.
    */
   struct audproc_param_id_ds2ap_bundle_config_t
   {
      int32_t output_mode;
      /**< Supported Values:
       0 : DS2AP_OUTPUT_1 - Output channel count is 1(mono)
       1 : DS2AP_OUTPUT_2 - Output channel count is 2 with order L, R
       2 : DS2AP_OUTPUT_2_LTRT - Output channel count is 2 with order L, R.  If a channel 8 to 2 or channel 6 to 2 down-mixing is required,
       a PLII LtRt compatible down-mixing will be carried out.
       3 : DS2AP_OUTPUT_6 - Output channel count is 6 with order L, R, C, LFE, Ls, Rs
       4 : DS2AP_OUTPUT_6_PLIIZ_COMPATIBLE - Output channel count is 6 with order L, R, C, LFE, Ls, Rs. If a channel 8 to 6 down-mixing is required,
       a PLIIz decode compatible down-mixing of Lrs and Rrs into Ls and Rs will be carried out
       5 : DS2AP_OUTPUT_8 - Output channel count is 8 with order L, R, C, LFE, Ls, Rs, Lrs, Rrs
       6 : DS2AP_OUTPUT_2_HEADPHONE - Output channel count is 2 with order L, R, Headphone Virtualizer enabled as virtualizer
       7 : DS2AP_OUTPUT_2_SPEAKER - Output channel count is 2 with order L, R, Speaker Virtualizer enabled as virtualizer
       8 : DS2AP_OUTPUT_2DOT1_SPEAKER - Output channel count is 3 with order L, R, LFE Speaker Virtualizer enabled as virtualizer
       Default : 1 (DS2AP_OUTPUT_2)
       Parameter Type : User Configurable.
       Specifies the output mode of the ds2ap signal chain.
       */

      int32_t pre_gain;
      /**<
       Numeric range : [-2080,480]
       Default : 0
       Parameter Type : User Configurable.
       The amount of gain applied to the signal prior to entering the DS2AP processing. If the input audio is known to have amplified or attenuated,
       this value should be set to reflect how much gain has been applied.
       DS2AP_PREGAIN_MIN -130dB
       DS2AP_PREGAIN_MAX 30dB
       DS2AP_PREGAIN_DEFAULT 0dB
       */

      int32_t post_gain;
      /**<
       Numeric range : [-2080,480]
       Default : 0
       Parameter Type : User Configurable.
       The amount of gain which will be applied after DS2AP processing. For example: by an analog volume control.
       DS2AP_POSTGAIN_MIN -130dB
       DS2AP_POSTGAIN_MAX 30dB
       DS2AP_POSTGAIN_DEFAULT 0dB
       */

      int32_t system_gain;
      /**<
       Numeric range : [-2080,480]
       Default : 0
       Parameter Type : User Configurable.
       The amount of gain which the user would like to be applied to the signal.
       DS2AP_SYSTEM_GAIN_MIN -130dB
       DS2AP_SYSTEM_GAIN_MAX 30dB
       DS2AP_SYSTEM_GAIN_DEFAULT 0dB
       */

      int32_t calibration_gain;
      /**<
       Numeric range : [0, 192]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the boost gain to be applied to the signal. It gives the ability to give the different presets a different boost level,
       that is independent of the volume control (if it were used as the main volume control). This gain will be processed together with
       the volume maximizer boost gain as part of the system gain.
       DS2AP_CALIBRATION_GAIN_MIN 0dB
       DS2AP_CALIBRATION_GAIN_MAX 12dB
       DS2AP_CALIBRATION_GAIN_DEFAULT 0dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_bundle_config_t */

   /* Structure for the ds2ap downmixer configuration parameters for a DS2AP Bundle module. */
   typedef struct audproc_param_id_ds2ap_downmixer_config_t audproc_param_id_ds2ap_downmixer_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_downmixer_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DOWNMIXER_CONFIG parameter used by the DS2AP Bundle module.
    */
   struct audproc_param_id_ds2ap_downmixer_config_t
   {

      int32_t cmixlev;
      /**<
       Numeric range : [0, 23134]
       Default : 11583
       Parameter Type : User Configurable.
       The cmixlev parameter specifies how much the center channel should be mixed into the left and right channels.
       These settings only have an effect when the input and output configuration of DS2AP meets one of the following conditions:
       The output mode is DS2AP_OUTPUT_1 with 6 or 8 channels of input
       The output mode is DS2AP_OUTPUT_2 with 6 or 8 channels of input
       DS2AP_CMIXLEV_MIN   0.0
       DS2AP_CMIXLEV_MAX   1.412
       DS2AP_CMIXLEV_DEFAULT 0.707

       */

      int32_t surmixlev;
      /**<
       Numeric range : [0, 16384]
       Default : 16384
       Parameter Type : User Configurable.
       The surmixlev parameter specifies how much the left surround/back channels should be mixed into the left channel and
       how much the right surround/back channels should be mixed into the right channel.
       These settings only have an effect when the input and output configuration of DS2AP meets one of the following conditions:
       The output mode is DS2AP_OUTPUT_1 with 6 or 8 channels of input
       The output mode is DS2AP_OUTPUT_2 with 6 or 8 channels of input
       DS2AP_SURMIXLEV_MIN   0.0
       DS2AP_SURMIXLEV_MAX   1.0
       DS2AP_SURMIXLEV_DEFAULT 1.0
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_downmixer_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_sd
    @{ */
   /** ID of the Surround Decoder module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_SD_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_SD                          0x000108E2

   /** ID to set the Surround Decoder configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_SD.

    @msgpayload{audproc_param_id_ds2ap_sd_config_t}
    @table{weak__audproc__param__id__ds2ap__sd__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_SD_CONFIG                    0x000108E3

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_sd */

   /* Structure for the ds2ap surround decoder configuration for the DS2AP Surround Decoder module. */
   typedef struct audproc_param_id_ds2ap_sd_config_t audproc_param_id_ds2ap_sd_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_sd_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_SD_CONFIG parameter used by the Surround Decoder module.
    */
   struct audproc_param_id_ds2ap_sd_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 1
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the surround decoder module
       ENABLE 1
       DISABLE 0
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_sd_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_de
    @{ */
   /** ID of the Dialogue Enhancer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_DE_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_DE                          0x000108E4

   /** ID to set the Dialogue Enhancer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_DE.

    @msgpayload{audproc_param_id_ds2ap_de_config_t}
    @table{weak__audproc__param__id__ds2ap__de__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DE_CONFIG                    0x000108E5

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_de */

   /* Structure for the ds2ap dialogue enhancer configuration parameters for the DS2AP Dialogue Enhancer module. */
   typedef struct audproc_param_id_ds2ap_de_config_t audproc_param_id_ds2ap_de_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_de_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DE_CONFIG parameter used by the dialogue enhancer module.
    */
   struct audproc_param_id_ds2ap_de_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the dialogue enhancer module
       ENABLE  1
       DISABLE 0
       */
      int32_t amount;
      /**<
       Numeric range : [0,16]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the strength of the dialog enhancer effect
       DS2AP_DE_AMOUNT_MIN   0.0
       DS2AP_DE_AMOUNT_MAX   1.0
       DS2AP_DE_AMOUNT_DEFAULT   0.0
       */
      int32_t ducking;
      /**<
       Numeric range : [0,16]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the degree of suppression of channels that don't contain dialog.
       DS2AP_DE_DUCKING_MIN   0.0
       DS2AP_DE_DUCKING_MAX   1.0
       DS2AP_DE_DUCKING_DEFAULT   0.0
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_de_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_dv
    @{ */
   /** ID of the Dolby Volume module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_DV_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_DV                          0x000108E6

   /** ID to set the Dolby Volume configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_DV.

    @msgpayload{audproc_param_id_ds2ap_dv_config_t}
    @table{weak__audproc__param__id__ds2ap__dv__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DV_CONFIG                    0x000108E7

   /** ID to set the Dolby Volume Leveler Input Target parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_DV.

    @msgpayload{audproc_param_id_ds2ap_dv_lit_t}
    @table{weak__audproc__param__id__ds2ap__dv__lit__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DV_LIT                    0x000108D2

   /** ID to set the Dolby Volume Leveler Output Target parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_DV.

    @msgpayload{audproc_param_id_ds2ap_dv_lot_t}
    @table{weak__audproc__param__id__ds2ap__dv__lot__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DV_LOT                    0x000108D3

   /** ID to set the Dolby Volume Maximizer Boost parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_DV.

    @msgpayload{audproc_param_id_ds2ap_dv_mb_t}
    @table{weak__audproc__param__id__ds2ap__dv__mb__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_DV_MB                    0x000108D4

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_dv */

   /* Structure for the ds2ap dolby volume configuration parameters for the Dolby Volume module. */
   typedef struct audproc_param_id_ds2ap_dv_config_t audproc_param_id_ds2ap_dv_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_dv_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DV_CONFIG parameter used by the Dolby Volume module.
    */
   struct audproc_param_id_ds2ap_dv_config_t
   {

      int32_t leveller_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Dolby Volume leveller
       ENABLE  1
       DISABLE 0
       */
      int32_t leveller_amount;
      /**<
       Numeric range : [0,10]
       Default : 7
       Parameter Type : User Configurable.
       Specifies how much the dolby volume leveler adjusts the loudness to normalize different
       audio content
       DS2AP_VOLUME_LEVELER_AMOUNT_MIN        0
       DS2AP_VOLUME_LEVELER_AMOUNT_MAX       10
       DS2AP_VOLUME_LEVELER_AMOUNT_DEFAULT    7
       */
      int32_t modeler_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Dolby Volume modeler
       ENABLE  1
       DISABLE 0
       */
      int32_t modeler_calibration;
      /**<
       Numeric range : [-320,320]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the Dolby Volume modeler calibration. It is used to fine-tune the manufacturer
       calibrated reference level to the listening environment. This input parameter allows the
       listener to adjust for variables such as listening positions or differing speaker sensitivities.
       For example, the end user of an A/V receiver (AVR) with Dolby Volume can recalibrate an AVR
       to optimize the reference level for the user's actual listening position.
       DS2AP_VOLUME_MODELER_CALIBRATION_MIN     -20 dB
       DS2AP_VOLUME_MODELER_CALIBRATION_MAX      20 dB
       DS2AP_VOLUME_MODELER_CALIBRATION_DEFAULT   0 dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_dv_config_t */

   /* Structure for the ds2ap dolby volume Leveler Input Target parameters for the Dolby Volume module. */
   typedef struct audproc_param_id_ds2ap_dv_lit_t audproc_param_id_ds2ap_dv_lit_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_dv_lit_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DV_LIT parameter used by the Dolby Volume module.
    */
   struct audproc_param_id_ds2ap_dv_lit_t
   {

      int32_t leveller_input_target;
      /**<
       Numeric range : [-640,0]
       Default : -320
       Parameter Type : User Configurable.
       Specifies the target average loudness level of the Dolby volume leveler.
       DS2AP_VOLUME_LEVELER_IN_TARGET_MIN     -40 dBFS
       DS2AP_VOLUME_LEVELER_IN_TARGET_MAX       0 dBFS
       DS2AP_VOLUME_LEVELER_IN_TARGET_DEFAULT -20 dBFS
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_dv_lit_t */

   /* Structure for the ds2ap dolby volume leveler output target parameters for the Dolby Volume module. */
   typedef struct audproc_param_id_ds2ap_dv_lot_t audproc_param_id_ds2ap_dv_lot_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_dv_lot_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DV_LOT parameter used by the Dolby Volume module.
    */
   struct audproc_param_id_ds2ap_dv_lot_t
   {

      int32_t leveller_output_target;
      /**<
       Numeric range : [-640,0]
       Default : -320
       Parameter Type : User Configurable.
       Specifies the Dolby Volume leveler output target. The Leveler Output Target is set by a
       system designer in order to calibrate the system to the proper reference playback SPL.
       To compensate for the difference between mastering and playback levels, Dolby Volume
       applies an unshaped digital gain of leveler output target minus leveler input target
       so that zero digital and analog volume produces reference loudness levels.
       DS2AP_VOLUME_LEVELER_OUT_TARGET_MIN     -40 dBFS
       DS2AP_VOLUME_LEVELER_OUT_TARGET_MAX       0 dBFS
       DS2AP_VOLUME_LEVELER_OUT_TARGET_DEFAULT -20 dBFS
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_dv_lot_t */

   /* Structure for the ds2ap dolby volume maximizer boost parameters for the Dolby Volume module. */
   typedef struct audproc_param_id_ds2ap_dv_mb_t audproc_param_id_ds2ap_dv_mb_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_dv_mb_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_DV_MB parameter used by the Dolby Volume module.
    */
   struct audproc_param_id_ds2ap_dv_mb_t
   {
      int32_t volume_maximizer_boost;
      /**<
       Numeric range : [0,192]
       Default : 144
       Parameter Type : User Configurable.
       Boost control for the Volume Maximizer. The amount of signal boost to be applied by the
       Volume Maximizer. Volume maximization will be performed only if Volume Leveler is enabled.
       DS2AP_VOLMAX_BOOST_MIN       0 dB
       DS2AP_VOLMAX_BOOST_MAX      12 dB
       DS2AP_VOLMAX_BOOST_DEFAULT   9 dB
       */

   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_dv_mb_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_ieq
    @{ */
   /** ID of the Intelligent Equalizer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_IEQ_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_IEQ_BAND_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_IEQ                         0x000108E8

   /** ID to set the Intelligent Equalizer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_IEQ.

    @msgpayload{audproc_param_id_ds2ap_ieq_config_t}
    @table{weak__audproc__param__id__ds2ap__ieq__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_IEQ_CONFIG                   0x000108E9

   /** ID to set the Intelligent Equalizer band configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_IEQ.

    @msgpayload{audproc_param_id_ds2ap_ieq_band_config_t}
    @table{weak__audproc__param__id__ds2ap__ieq__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_IEQ_BAND_CONFIG              0x000108EA

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_ieq */

   /* Structure for the Intelligent Equalizer configuration parameters for the Intelligent Equalizer module . */
   typedef struct audproc_param_id_ds2ap_ieq_config_t audproc_param_id_ds2ap_ieq_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ieq_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_IEQ_CONFIG parameter used by the Intelligent Equalizer module.
    */
   struct audproc_param_id_ds2ap_ieq_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Intelligent Equalizer module. IEQ dynamically adjusts the audio to meet the spectral preferences.
       ENABLE  1
       DISABLE 0
       */
      int32_t amount;
      /**<
       Numeric range : [0,16]
       Default : 10
       Parameter Type : User Configurable.
       Specifies the strength of the Intelligent Equalizer effect to apply.
       DS2AP_IEQ_AMOUNT_MIN        0.0
       DS2AP_IEQ_AMOUNT_MAX        1.0
       DS2AP_IEQ_AMOUNT_DEFAULT    0.625
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ieq_config_t */

   /* Structure for the Intelligent Equalizer band configuration parameters for the Intelligent Equalizer module. */
   typedef struct audproc_param_id_ds2ap_ieq_band_config_t audproc_param_id_ds2ap_ieq_band_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ieq_band_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_IEQ_BAND_CONFIG parameter used by the Intelligent Equalizer module.
    */
   struct audproc_param_id_ds2ap_ieq_band_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [1,20]
       Default : 10
       Parameter Type : User Configurable.
       Specifies the number of band for the Intelligent Equalizer.
       DS2AP_IEQ_MIN_BANDS_NUM   1
       DS2AP_IEQ_MAX_BANDS_NUM   20
       DS2AP_IEQ_DEFAULT_BANDS_NUM   10
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20, 20000] for each band
       Default : {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000}
       Parameter Type : User Configurable.
       Specifies the band center frequencies for the Intelligent Equalizer. The frequency values must increase through the array,
       if not, the invalid setting will be ignored by the core library and current band setting will be kept.
       DS2AP_IEQ_MIN_BANDS_FREQS   20 Hz
       DS2AP_IEQ_MAX_BANDS_FREQS   20000 Hz
       DS2AP_IEQ_DEFAULT_BAND_FREQUENCIES   {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000} Hz
       */
      int32_t band_target[20];
      /**<
       Numeric range : [-480,480] for each band
       Default : {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
       Parameter Type : User Configurable.
       Specifies the band target levels for the Intelligent Equalizer.
       DS2AP_IEQ_MIN_BANDS_TARGETS   -30 dB
       DS2AP_IEQ_MAX_BANDS_TARGETS    30 dB
       DS2AP_IEQ_DEFAULT_BAND_TARGETS   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ieq_band_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_geq
    @{ */
   /** ID of the Graphic Equalizer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_GEQ_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_GEQ_BAND_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_GEQ                         0x000108EB

   /** ID to set the Graphic Equalizer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_GEQ.

    @msgpayload{audproc_param_id_ds2ap_geq_config_t}
    @table{weak__audproc__param__id__ds2ap__geq__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_GEQ_CONFIG                   0x000108EC

   /** ID to set the Graphic Equalizer band configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_GEQ.

    @msgpayload{audproc_param_id_ds2ap_geq_band_config_t}
    @table{weak__audproc__param__id__ds2ap__geq__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_GEQ_BAND_CONFIG              0x000108ED

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_geq */

   /* Structure for the Graphic Equalizer configuration parameters for the Graphic Equalizer module. */
   typedef struct audproc_param_id_ds2ap_geq_config_t audproc_param_id_ds2ap_geq_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_qeq_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_GEQ_CONFIG parameter used by the Graphic Equalizer module.
    */
   struct audproc_param_id_ds2ap_geq_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Graphic Equalizer module. Graphic Equalizer feature is a traditional equalizer,
       with configurable number of bands and center frequencies. The same equalization gains will be applied to all channels.
       ENABLE  1
       DISABLE 0
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_geq_config_t */

   /* Structure for the Graphic Equalizer band configuration parameters for the Graphic Equalizer module. */
   typedef struct audproc_param_id_ds2ap_geq_band_config_t audproc_param_id_ds2ap_geq_band_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_geq_band_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_GEQ_BAND_CONFIG parameter used by the Graphic Equalizer module.
    */
   struct audproc_param_id_ds2ap_geq_band_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [1,20]
       Default : 10
       Parameter Type : User Configurable.
       Specifies the number of band for the Graphic Equalizer.
       DS2AP_GEQ_MIN_BANDS_NUM   1
       DS2AP_GEQ_MAX_BANDS_NUM   20
       DS2AP_GEQ_DEFAULT_BANDS_NUM   10
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20, 20000] for each band
       Default : {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000}
       Parameter Type : User Configurable.
       Specifies the band center frequencies for the Graphic Equalizer. The frequency values must increase through the array,
       if not, the invalid setting will be ignored by the core library and current band setting will be kept.
       DS2AP_GEQ_MIN_BANDS_FREQS   20 Hz
       DS2AP_GEQ_MAX_BANDS_FREQS   20000 Hz
       DS2AP_GEQ_DEFAULT_BAND_FREQUENCIES   {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000} Hz
       */
      int32_t band_target[20];
      /**<
       Numeric range : [-480,480] for each band
       Default : {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
       Parameter Type : User Configurable.
       Specifies the band target levels for the Graphic Equalizer.
       DS2AP_GEQ_MIN_BANDS_TARGETS   -30 dB
       DS2AP_GEQ_MAX_BANDS_TARGETS    30 dB
       DS2AP_GEQ_DEFAULT_BAND_TARGETS   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_geq_band_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_sv
    @{ */
   /** ID of the Surround Virtualizer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_SV_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_SV                          0x000108EE

   /** ID to set the Surround Virtualizer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_SV.

    @msgpayload{audproc_param_id_ds2ap_sv_config_t}
    @table{weak__audproc__param__id__ds2ap__sv__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_SV_CONFIG                    0x000108EF

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_sv */

   /* Structure for the ds2ap surround virtualizer configuration for the Surround Virtualizer module. */
   typedef struct audproc_param_id_ds2ap_sv_config_t audproc_param_id_ds2ap_sv_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_sv_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_SV_CONFIG parameter used by the DS2AP Surround Virtualizer module.
    */
   struct audproc_param_id_ds2ap_sv_config_t
   {

      int32_t headphone_reverb_gain;
      /**<
       Numeric range : [-2080,192]
       Default : 0
       Parameter Type : User Configurable.
       Amount of reverberation that is added to the signal if Dolby Headphone is being used as
       the surround virtualizer.
       DS2AP_HEADPHONE_VIRTUALIZER_REVERB_MIN      -130 dB
       DS2AP_HEADPHONE_VIRTUALIZER_REVERB_MAX       12 dB
       DS2AP_HEADPHONE_VIRTUALIZER_REVERB_DEFAULT   0 dB
       */
      uint32_t speaker_angle;
      /**<
       Numeric range : [5, 30]. Tuned in steps of 5 only
       Default : 10
       Parameter Type : User Configurable.
       Specifies the horizontal angle of each loudspeaker from the central listening position to the
       Speaker Virtualizer
       DS2AP_SPEAKER_VIRTUALIZER_ANGLE_MIN      5  degrees
       DS2AP_SPEAKER_VIRTUALIZER_ANGLE_MAX      30 degrees
       DS2AP_SPEAKER_VIRTUALIZER_ANGLE_DEFAULT  10 degrees
       */
      uint32_t start_frequency;
      /**<
       Numeric range : [20, 20000]
       Default : 20
       Parameter Type : User Configurable.
       Specifies the start frequency to be virtualized in Speaker Virtualizer. Frequencies below
       this value will not get virtualized. This is useful for improving bass response.
       DS2AP_SPEAKER_VIRTUALIZER_START_FREQ_MIN      20 Hz
       DS2AP_SPEAKER_VIRTUALIZER_START_FREQ_MAX      20 KHz
       DS2AP_SPEAKER_VIRTUALIZER_START_FREQ_DEFAULT  20 Hz
       */
      int32_t surround_boost_level;
      /**<
       Numeric range : [0,96]
       Default : 96
       Parameter Type : User Configurable.
       Specifies the amount of boost applied to the surround channels
       DS2AP_SURROUND_BOOST_MIN      0
       DS2AP_SURROUND_BOOST_MAX      6 dB
       DS2AP_SURROUND_BOOST_DEFAULT  6 dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_sv_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_be
    @{ */
   /** ID of the Bass Enhancer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_BE_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_BE                          0x000108F0

   /** ID to set the Bass Enhancer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_BE.

    @msgpayload{audproc_param_id_ds2ap_be_config_t}
    @table{weak__audproc__param__id__ds2ap__be__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_BE_CONFIG                    0x000108F1

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_be */

   /* Structure for the bass enhancer configuration parameters for the Bass Enhancer module. */
   typedef struct audproc_param_id_ds2ap_be_config_t audproc_param_id_ds2ap_be_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_be_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_BE_CONFIG parameter used by the bass enhancer module.
    */
   struct audproc_param_id_ds2ap_be_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Bass Enhancer module. Bass Enhancer enhances the bass response of a speaker
       by adding a low frequency shelf. In conjunction with the audio regulator in distortion protection mode, Bass Enhancer
       gives signal dependent enhancement without distortion
       ENABLE  1
       DISABLE 0
       */
      int32_t boost;
      /**<
       Numeric range : [0,384]
       Default : 192
       Parameter Type : User Configurable.
       Specifies the amount of bass enhancement boost applied by Bass Enhancer
       DS2AP_BASS_ENHANCER_BOOST_MIN   0 dB
       DS2AP_BASS_ENHANCER_BOOST_MAX   24 dB
       DS2AP_BASS_ENHANCER_BOOST_DEFAULT   12 dB
       */
      uint32_t cutoff_frequency;
      /**<
       Numeric range : [20,2000]
       Default : 200
       Parameter Type : User Configurable.
       Specifies the bass enhancement cutoff frequency used by Bass Enhancer
       DS2AP_BASS_ENHANCER_CUTOFF_MIN   20 Hz
       DS2AP_BASS_ENHANCER_CUTOFF_MAX   2000 Hz
       DS2AP_BASS_ENHANCER_CUTOFF_DEFAULT   200 Hz
       */
      int32_t width;
      /**<
       Numeric range : [2,64]
       Default : 16
       Parameter Type : User Configurable.
       Specifies the width of the bass enhancement boost curve used by Bass Enhancer, in units of octaves below the cutoff frequency
       DS2AP_BASS_ENHANCER_WIDTH_MIN   0.125 octaves
       DS2AP_BASS_ENHANCER_WIDTH_MAX   4.0 octave
       DS2AP_BASS_ENHANCER_WIDTH_DEFAULT   1.0 octaves
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_be_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_ao
    @{ */
   /** ID of the Audio Optimizer module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_AO_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_AO_BAND_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_AO                          0x000108F2

   /** ID to set the Audio Optimizer configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_AO.

    @msgpayload{audproc_param_id_ds2ap_ao_config_t}
    @table{weak__audproc__param__id__ds2ap__ao__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_AO_CONFIG                   0x000108F3

   /** ID to set the Audio Optimizer band configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_AO.

    @msgpayload{audproc_param_id_ds2ap_ao_band_config_t}
    @table{weak__audproc__param__id__ds2ap__ao__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_AO_BAND_CONFIG                   0x000108F4

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_ao */

   /* Structure for the Audio Optimizer configuration parameters for the Audio Optimizer module. */
   typedef struct audproc_param_id_ds2ap_ao_config_t audproc_param_id_ds2ap_ao_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ao_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_AO_CONFIG parameter used by the Audio Optimizer module.
    */
   struct audproc_param_id_ds2ap_ao_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Audio Optimizer module. Audio Optimizer provides a static equalization
       curve with a configurable number of bands and center frequencies. This curve may be different for different
       channels. The curves are typically produced by a tuning tool to compensate for imperfections in the speakers
       internal to a device.
       ENABLE  1
       DISABLE 0
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ao_config_t */

   /* Structure for the Audio Optimizer band configuration parameters for the Audio Optimizer module.. */
   typedef struct audproc_param_id_ds2ap_ao_band_config_t audproc_param_id_ds2ap_ao_band_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ao_band_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_AO_BAND_CONFIG parameter used by the Audio Optimizer module.
    */
   struct audproc_param_id_ds2ap_ao_band_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [1,20]
       Default : 10
       Parameter Type : User Configurable.
       Specifies the number of band for the Audio Optimizer.
       DS2AP_AUDIO_OPTIMIZER_MIN_BANDS_NUM   1
       DS2AP_AUDIO_OPTIMIZER_MAX_BANDS_NUM   20
       DS2AP_AUDIO_OPTIMIZER_DEFAULT_BANDS_NUM   10
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20, 20000] for each band
       Default : {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000}
       Parameter Type : User Configurable.
       Specifies the band center frequencies for the Audio Optimizer. The frequency values must increase through the array,
       if not, the invalid setting will be ignored by the core library and current band setting will be kept.
       DS2AP_AUDIO_OPTIMIZER_MIN_BANDS_FREQS   20 Hz
       DS2AP_AUDIO_OPTIMIZER_MAX_BANDS_FREQS   20000 Hz
       DS2AP_AUDIO_OPTIMIZER_DEFAULT_BAND_FREQUENCIES   {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000} Hz
       */
      int32_t gains[8][20];
      /**<
       Numeric range : [-480,480] for each band of each channel
       Default : {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
       Parameter Type : User Configurable.
       Specifies the band target levels for the Graphic Equalizer.
       DS2AP_AUDIO_OPTIMIZER_MIN_BANDS_TARGETS   -30 dB
       DS2AP_AUDIO_OPTIMIZER_MAX_BANDS_TARGETS    30 dB
       DS2AP_AUDIO_OPTIMIZER_DEFAULT_BAND_TARGETS   {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}} dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ao_band_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_ar
    @{ */
   /** ID of the Audio Regulator module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_AR_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_AR_TUNING_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_AR_GAIN_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_AR                          0x000108F5

   /** ID to set the Audio Regulator configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_AR.

    @msgpayload{audproc_param_id_ds2ap_ar_config_t}
    @table{weak__audproc__param__id__ds2ap__ar__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_AR_CONFIG                    0x000108F6

   /** ID to set the Audio Regulator band configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_AR.

    @msgpayload{audproc_param_id_ds2ap_ar_band_config_t}
    @table{weak__audproc__param__id__ds2ap__ar__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_AR_TUNING_CONFIG                   0x000108F7

   /** ID to get the Audio Regulator gain/tuning information parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_AR.

    @msgpayload{audproc_param_id_ds2ap_ar_gain_config_t}
    @table{weak__audproc__param__id__ds2ap__ar__gain__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_AR_GAIN_CONFIG                   0x000108F8

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_ar */

   /* Structure for the Audio Regulator configuration parameters for the Audio Regulator module. */
   typedef struct audproc_param_id_ds2ap_ar_config_t audproc_param_id_ds2ap_ar_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ar_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_AR_CONFIG parameter used by the Audio Regulator module.
    */
   struct audproc_param_id_ds2ap_ar_config_t
   {

      int32_t enable;
      /**<
       Numeric range : [0,1]
       Default : 1
       Parameter Type : User Configurable.
       Define the state (enable/disable) of the Audio Regulator module.
       ENABLE  1
       DISABLE 0
       */
      int32_t operating_mode;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the operating mode of the Audio Regulator. There are two valid modes which the Audio Regulator can operate in:
       Peak Protection mode (0): The tuning configuration supplied by regulator tuning configuration and regulator overdrive
       is ignored and the audio regulator has the same operating characteristics for each band.
       Speaker Distortion mode (1): The tuning configuration supplied by regulator tuning configuration and regulator overdrive
       is used to give the audio regulator per-band operating characteristics.
       */
      int32_t distortion_relaxation_amount;
      /**<
       Numeric range : [0,144]
       Default : 96
       Parameter Type : User Configurable.
       Defines the audio regulator distortion relaxation amount. This parameter specifies the maximum amount that the distortion
       masking algorithm can relax (increase) the regulator threshold.
       DS2AP_AUDIO_REGULATOR_RELAXATION_AMOUNT_MIN   0 dB
       DS2AP_AUDIO_REGULATOR_RELAXATION_AMOUNT_MAX   9 dB
       DS2AP_AUDIO_REGULATOR_RELAXATION_AMOUNT_DEFAULT   6dB
       */
      int32_t timber_preservation_amount;
      /**<
       Numeric range : [0,16]
       Default : 16
       Parameter Type : User Configurable.
       Defines the timbre preservation amount for the Audio Regulator. This is a dimensionless quantity which specifies a trade-off
       between maximum output loudness and preserving the spectral shape of the incoming signal. Values close to zero maximize loudness
       and values close to one maximize the preservation of signal tonality. This value is used in both the speaker distortion and peak
       protection operating modes of the Audio Regulator.
       DS2AP_AUDIO_REGULATOR_TP_AMOUNT_MIN   0
       DS2AP_AUDIO_REGULATOR_TP_AMOUNT_MAX   1.0
       DS2AP_AUDIO_REGULATOR_TP_AMOUNT_DEFAULT   10
       */
      int32_t over_drive;
      /**<
       Numeric range : [0,192]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the boost which will be applied to all of the tuned low and high thresholds. This permits the Audio Regulator to increase
       the maximum output at the expense of increasing the maximum output distortion. This value only has an effect when the Audio Regulator
       is operating in speaker distortion mode
       DS2AP_AUDIO_REGULATOR_OVERDRIVE_MIN   0 dB
       DS2AP_AUDIO_REGULATOR_OVERDRIVE_MAX   12 dB
       DS2AP_AUDIO_REGULATOR_OVERDRIVE_DEFAULT  0 dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ar_config_t */

   /* Structure for the Audio Regulator tuning configuration parameters for the Audio Regulator module. */
   typedef struct audproc_param_id_ds2ap_ar_tuning_config_t audproc_param_id_ds2ap_ar_tuning_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ar_tuning_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_AR_TUNING_CONFIG parameter used by the Audio Regulator module.
    */
   struct audproc_param_id_ds2ap_ar_tuning_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [1,20]
       Default : 2
       Parameter Type : User Configurable.
       Specifies the number of bands for the Audio Regulator.
       DS2AP_AUDIO_REGULATOR_MIN_BANDS_NUM   1
       DS2AP_AUDIO_REGULATOR_MAX_BANDS_NUM   20
       DS2AP_AUDIO_REGULATOR_DEFAULT_BANDS_NUM   2
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20, 20000] for each band
       Default : {20, 20000}
       Parameter Type : User Configurable.
       Specifies the band center frequencies for the Audio Regulator. The frequency values must increase through the array,
       if not, the invalid setting will be ignored by the core library and current band setting will be kept.
       DS2AP_AUDIO_REGULATOR_MIN_BANDS_FREQS   20 Hz
       DS2AP_AUDIO_REGULATOR_MAX_BANDS_FREQS   20000 Hz
       DS2AP_AUDIO_REGULATOR_DEFAULT_BAND_FREQUENCIES   {20, 20000} Hz
       */
      int32_t low_thresholds[20];
      /**<
       Numeric range : [-2080,0]
       Default :{ -192,-192}
       Parameter Type : User Configurable.
       Specifies the lower excitation thresholds which when exceeded will cause the Audio Regulator to begin attenuating.
       DS2AP_AUDIO_REGULATOR_TUNING_LOW_THRESHOLD_MIN     -130 dB
       DS2AP_AUDIO_REGULATOR_TUNING_LOW_THRESHOLD_MAX        0 dB
       DS2AP_AUDIO_REGULATOR_TUNING_LOW_THRESHOLD_DEFAULT  {-12,-12} dB
       */
      int32_t high_thresholds[20];
      /**<
       Numeric range : [-2080,0]
       Default :{0,0}
       Parameter Type : User Configurable.
       Specifies the upper excitation thresholds which will not be permitted to be exceeded.
       DS2AP_AUDIO_REGULATOR_TUNING_HIGH_THRESHOLD_MIN     -130 dB
       DS2AP_AUDIO_REGULATOR_TUNING_HIGH_THRESHOLD_MAX        0 dB
       DS2AP_AUDIO_REGULATOR_TUNING_HIGH_THRESHOLD_DEFAULT  {0,0} dB
       */
      int32_t isolate_bands[20];
      /**<
       Numeric range : [0,1]
       Default :{0,0}
       Parameter Type : User Configurable.
       Specifies whether the band is isolated from the gain-frequency smoothing. Non-zero value indicates that the band is
       isolated and surrounding bands will not be affected by the amount of regulation being applied to it.
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ar_tuning_config_t */

   /* Structure to get Audio Regulator parameters of Gain Configuration for the Audio Regulator module. */
   typedef struct audproc_param_id_ds2ap_ar_gain_config_t audproc_param_id_ds2ap_ar_gain_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_ar_gain_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_AR_GAIN_CONFIG parameter used by the Audio Regulator module.
    */
   struct audproc_param_id_ds2ap_ar_gain_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [19,20]
       Parameter Type : Read Only.
       Provides the band count of the Audio Regulator.
       */
      int32_t band_gain[20];
      /**<
       Numeric range : [-2080,0]
       Parameter Type : Read Only.
       Provides the band gains seen by the Audio Regulator.
       */
      int32_t band_excitations[20];
      /**<
       Numeric range : [-2080,0]
       Parameter Type : Read Only.
       Provides the band excitations seen by the Audio Regulator.
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_ar_gain_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_vis
    @{ */
   /** ID of the Visualization module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_VIS_BAND_CONFIG
    - #AUDPROC_PARAM_ID_DS2AP_VIS_CUSTOM_BAND_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_VIS                         0x000108F9

   /** ID to get the Visualization parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_VIS.

    @msgpayload{audproc_param_id_ds2ap_vis_band_config_t}
    @table{weak__audproc__param__id__ds2ap__vis__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_VIS_BAND_CONFIG              0x000108FA

   /** ID to set/get the Visualization parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_VIS.

    @msgpayload{audproc_param_id_ds2ap_vis_custom_band_config_t}
    @table{weak__audproc__param__id__ds2ap__vis__custom__band__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_VIS_CUSTOM_BAND_CONFIG       0x000108FB

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_ar */

   /* Structure to get Visualization band parameters for the Visualizer module. */
   typedef struct audproc_param_id_ds2ap_vis_band_config_t audproc_param_id_ds2ap_vis_band_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_vis_band_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_VIS_BAND_CONFIG parameter used by the Visualizer module.
    */
   struct audproc_param_id_ds2ap_vis_band_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [19,20]
       Parameter Type : Read Only.
       Provides the band count of the Visualizer.
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20,20000] in Hz
       Parameter Type : Read Only.
       Provides the band center frequency of the Visualizer.
       */
      int32_t band_gain[20];
      /**<
       Numeric range : [-192,576]
       Parameter Type : Read Only.
       Provides the band gains seen by the Visualizer.
       DS2AP__VIS_GAIN_MIN   -12 dB
       DS2AP__VIS_GAIN_MAX    36 dB
       */
      int32_t band_excitations[20];
      /**<
       Numeric range : [-192,576]
       Parameter Type : Read Only.
       Provides the band excitations seen by the Visualizer.
       DS2AP__VIS_EXCITATION_MIN   -12 dB
       DS2AP__VIS_EXCITATION_MAX    36 dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_vis_band_config_t */

   /* Structure to set/get Visualization custom band parameters for the Visualizer module. */
   typedef struct audproc_param_id_ds2ap_vis_custom_band_config_t audproc_param_id_ds2ap_vis_custom_band_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_vis_custom_band_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_VIS_CUSTOM_BAND_CONFIG parameter used by the Visualizer module.
    */
   struct audproc_param_id_ds2ap_vis_custom_band_config_t
   {

      uint32_t band_count;
      /**<
       Numeric range : [19,20]
       Parameter Type : User Configurable.
       Specifies the band count for the Visualizer.
       */
      uint32_t band_center_frequency[20];
      /**<
       Numeric range : [20,20000] in Hz
       Parameter Type : User Configurable.
       Specifies the band center frequency for the Visualizer.
       */
      int32_t band_gain[20];
      /**<
       Numeric range : [-192,576]
       Parameter Type : Read Only.
       Provides the custom band gains seen by the Visualizer.
       DS2AP__VIS_GAIN_MIN   -12 dB
       DS2AP__VIS_GAIN_MAX    36 dB
       */
      int32_t band_excitations[20];
      /**<
       Numeric range : [-192,576]
       Parameter Type : Read Only.
       Provides the custom band excitations seen by the Visualizer.
       DS2AP__VIS_EXCITATION_MIN   -12 dB
       DS2AP__VIS_EXCITATION_MAX    36 dB
       */
   }
#include "adsp_end_pack.h"
   ;
   /** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_vis_custom_band_config_t */

   /** @cond OEM_only */
   /** @addtogroup audio_pp_module_ds2ap_mi
    @{ */
   /** ID of the Media Intelligence module of Dolby Surround II.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS2AP_MI_CONFIG
    */
#define AUDPROC_MODULE_ID_DS2AP_MI                          0x000108FC

   /** ID to set the Media Intelligence configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_MI.

    @msgpayload{audproc_param_id_ds2ap_mi_config_t}
    @table{weak__audproc__param__id__ds2ap__mi__config__t}
    */
#define AUDPROC_PARAM_ID_DS2AP_MI_CONFIG                    0x000108FD

   /** ID to set the Media Intelligence Meta-data configuration parameters of Dolby Surround II package used by AUDPROC_MODULE_ID_DS2AP_MI.

    @msgpayload{audproc_param_id_ds2ap_mi_metadata_input_config_t}
    @table{weak__audproc__param__id__ds2ap__mi__metadata__input__config__t}
    */

#define AUDPROC_PARAM_ID_DS2AP_MI_METADATA_INPUT_CONFIG    0x000108FE

   /** @endcond */
   /** @} *//* end_addtogroup audio_pp_module_ds2ap_mi */

   /* Structure for the ds2ap media intelligence configuration parameters for the MI module. */
   typedef struct audproc_param_id_ds2ap_mi_config_t audproc_param_id_ds2ap_mi_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_mi_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_MI_CONFIG parameter used by the Media Intelligence module.
    */
   struct audproc_param_id_ds2ap_mi_config_t
   {

      int32_t mi2ieq_steering_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of  Media Intelligence to Intelligent Equalizer steering.
       If this parameter is enabled, Intelligent Equalizer will use information from MI to improve
       the quality of the processing it does. If Intelligent Equalizer is disabled, then this
       parameter will not have any effect. If MI processing is disabled then this parameter will not have any
       effect.
       ENABLE  1
       DISABLE 0
       */
      int32_t mi2dv_leveler_steering_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of  Media Intelligence to Volume Leveler steering. If
       this parameter is enabled, Volume Leveler will use information from MI to improve the
       quality of processing it does. If Volume Leveler is disabled, then this parameter will
       not have any effect. If MI processing is disabled then this parameter will not have any
       effect.
       ENABLE  1
       DISABLE 0
       */
      int32_t mi2dialog_enhancer_steering_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of Media Intelligence to Dialog Enhancer steering. If
       this parameter is enabled, Dialog Enhancer will use information from MI to improve the
       quality of processing it does. If Dialog Enhancer is disabled, then this parameter will
       not have any effect. If MI processing is disabled then this parameter will not have any
       effect.
       ENABLE  1
       DISABLE 0
       */
      int32_t mi2surround_compressor_steering_enable;
      /**<
       Numeric range : [0,1]
       Default : 0
       Parameter Type : User Configurable.
       Define the state (enable/disable) of  Media Intelligence to Surround Compressor steering.
       The Surround Compressor is only used when the headphone or speaker virtualizer is enabled.
       If this parameter is enabled, then Surround Compressor will use information from MI to
       improve the quality of the processing it does. If the output mode doesn't require
       virtualization, then this parameter will not have any effect. If MI processing is disabled
       then this parameter will not have any effect.
       ENABLE  1
       DISABLE 0
       */
   }
#include "adsp_end_pack.h"
   ;
/** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_mi_config_t */

   /* Structure for the ds2ap media intelligence metadata configuration parameters for the MI module. */
   typedef struct audproc_param_id_ds2ap_mi_metadata_input_config_t audproc_param_id_ds2ap_mi_metadata_input_config_t;

#include "adsp_begin_pack.h"
   /** @weakgroup weak_audproc_param_id_ds2ap_mi_metadata_input_config_t
    @{ */
   /* Payload of the AUDPROC_PARAM_ID_DS2AP_MI_METADATA_INPUT_CONFIG parameter used by the Media Intelligence module.
    */
   struct audproc_param_id_ds2ap_mi_metadata_input_config_t
   {

      int32_t volume_leveler_weight;
      /**<
       Numeric range : [0,2147483647]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the weighting for volume leveler.
       */
      int32_t intelligent_equalizer_weight;
      /**<
       Numeric range : [0,2147483647]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the weighting for intelligent_equalizer.
       */
      int32_t dialog_enhancer_speech_confidence;
      /**<
       Numeric range : [0,2147483647]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the speech confidence value for dialog_enhancer.
       */
      int32_t surround_compressor_music_confidence;
      /**<
       Numeric range : [0,2147483647]
       Default : 0
       Parameter Type : User Configurable.
       Specifies the music confidence value for surround_compressor.
       */
   }
#include "adsp_end_pack.h"
   ;
/** @} *//* end_weakgroup weak_audproc_param_id_ds2ap_mi_metadata_input_config_t */



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif // #ifdef _ADSP_DS2APv2_API_H_
