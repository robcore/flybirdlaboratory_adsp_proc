#ifndef _ADSP_DS1AP_API_H_
#define _ADSP_DS1AP_API_H_

/**
@file adsp_ds1ap_api.h

@brief This file contains the structure definitions for the 
commands related with Dolby Surround1 Audio Processing. 
*/

/*===========================================================================
  Copyright (c) 2013 Qualcomm Technologies, Inc. All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*========================================================================
Edit History
when       who     what, where, why
--------   ---     -------------------------------------------------------
01/25/13   bvodapal      API file for DS1AP

========================================================================== */

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/      

/* Dolby Surround1 Module License ID. This ID is used as an identifier for DS1 license via ADSP generic license mechanism.
 * Please refer AVCS_CMD_SET_LICENSE for more details
*/
#define DOLBY_DS1_LICENSE_ID                                 0x00000001

/* Dolby Surround1 Module ID. This ID can be used to create custom topology. All the params must be defined
 * under this module id if it is to be used as custom topology
*/
#define AUDPROC_MODULE_ID_DS1AP      0x00010775

/** Dolby Surround1  COPP Topology ID. The client can route multiple ASM session to this COPP with Matrix operating in Native mode. */
/** @addtogroup audio_pp_topos_adm
@{ */
/** @cond OEM_only */
/** ID of the COPP topology of DS1AP, the Dolby Surround1 Feature

@inputfig{1,ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DS1AP_topology.png}
    
     - Resampler                         (#AUDPROC_MODULE_ID_RESAMPLER)
	 - DS1AP                             (#AUDPROC_MODULE_ID_DS1AP_MODULE_ID)
     - Resampler                         (#AUDPROC_MODULE_ID_DS1AP_RESAMPLER)
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DS1AP 				0x0001033B

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_topos_adm */


/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_bundle
@{ */
/** ID of the bundle module of Dolby Surround1. All these module paramters configure the root node in the Dolby Surround1 package. 
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_BVER
    - #AUDPROC_PARAM_ID_DS1AP_BNDL
	- #AUDPROC_PARAM_ID_DS1AP_VER
	- #AUDPROC_PARAM_ID_DS1AP_INIT_ENDP
	- #AUDPROC_PARAM_ID_DS1AP_PREG
	- #AUDPROC_PARAM_ID_DS1AP_PSTG
	- #AUDPROC_PARAM_ID_DS1AP_VOL
*/
#define AUDPROC_MODULE_ID_DS1AP_BUNDLE	                    0x00010723

/** ID to get the Bundle Version of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_bver_t}
    @table{weak__audproc__param__id__ds1ap__bver__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_BVER  						0x00010724

/** ID to get the Bundle ID of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_bndl_t}
    @table{weak__audproc__param__id__ds1ap__bndl__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_BNDL 						0x00010725


/** ID to get the Bundle ID of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_ver_t}
    @table{weak__audproc__param__id__ds1ap__ver__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VER 						    0x00010726

/** ID of the Endpoint of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_init_endp_t}
    @table{weak__audproc__param__id__ds1ap__init__endp__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_INIT_ENDP   					0x00010727

/** ID of the Pregain applied to Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_preg_t}
    @table{weak__audproc__param__id__ds1ap__preg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_PREG   						0x00010728

/** ID of the Postgain applied on Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_pstg_t}
    @table{weak__audproc__param__id__ds1ap__pstg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_PSTG   						0x00010729

/** ID of the Bundle volume applied on Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_BUNDLE. 

    @msgpayload{audproc_param_id_ds1ap_vol_t}
    @table{weak__audproc__param__id__ds1ap__vol__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VOL   						0x0001072A

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_bundle */

/* Structure for the bundle version parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_bver_t audproc_param_id_ds1ap_bver_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_bver_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_BVER parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_bver_t
{
    int32_t                  bundle_version[5]; 
    /**< Numeric range : [-32768,32767]  
		 Default : 3,36,6,0,0 
		 Parameter Type : READ_ONLY
		 Identifies the version of the bundle as a combination of versions of all objects. This parameter is automatically calculated as the sum of the versions
		 of all objects in the bundle and is intended as a way to uniquely identify the bundle, in conjunction with the AUDPROC_PARAM_ID_DS1AP_BNDL parameter. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_bver_t */		


/* Structure for the bundle ID parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_bndl_t audproc_param_id_ds1ap_bndl_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_bndl_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_BNDL parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_bndl_t
{
    int32_t                  bundle_id[2]; 
    /**< Numeric range : [-32768,32767]  
		 Default : 21316,49 
		 Parameter Type : READ_ONLY
		 This Parameter is used get to Identify the bundle. This can be interpreted as a four character ASCII name identifying the Bundle ID.
 */
}
#include "adsp_end_pack.h"
;	
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_bndl_t */	


/* Structure to get the object version parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_ver_t audproc_param_id_ds1ap_ver_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ver_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VER parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_ver_t
{
    int32_t                  version[4]; 
    /**< Numeric range : [-32768,32767]  
		 Default : 1,8,3,0 
		 Parameter Type : READ_ONLY
		 This Parameter is used get the Version number of an object.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_bndl_t */	


/* Structure for the endpoint parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_init_endp_t audproc_param_id_ds1ap_init_endp_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_init_endp_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_INIT_ENDP parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_init_endp_t
{
    uint32_t                 endpoint; 
    /**< Supported Values : 
			0 - DS1_ENDP_INT_SPEAKERS
			1 - DS1_ENDP_EXT_SPEAKERS
			2 - DS1_ENDP_HEADPHONES
			3 - DS1_ENDP_HDMI
			4 - DS1_ENDP_SPDIF
			5 - DS1_ENDP_DLNA
			6 - DS1_ENDP_ANALOG
		 Default : 0
		 Parameter Type : User Configurable
		 Specifies the Endpoint of the signal chain .i.e., Device to which it is connected.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_init_endp_t */	


/* Structure for the bundle pregain parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_preg_t audproc_param_id_ds1ap_preg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_preg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_PREG parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_preg_t
{
    int32_t                 bundle_pregain; 
    /**< Numeric range  : [-2080,480] (which maps to [-130.00,30.00] dB)] with 4 fractional bits			
		 Default : 0.00 dB 
		 Parameter Type : Factory Configurable
		 The amount of gain applied to the signal prior to entering the bundle. If the audio entering the DS1 bundle is known to have been boosted or attenuated, 
		 this value should be set to reflect how much boosting has been applied.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_preg_t */	


/* Structure for the bundle postgain parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_pstg_t audproc_param_id_ds1ap_pstg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_pstg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_PSTG parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_pstg_t
{
    int32_t                 bundle_postgain; 
    /**< Numeric range  : [-2080,480] (which maps to [-130.00,30.00] dB)] with 4 fractional bits			
		 Default : 0.00 dB 
		 Parameter Type : Factory Configurable
		 The amount of gain which will be applied after leaving the bundle. For example: by an analog volume control.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_pstg_t */


/* Structure for the bundle volume parameter for a DS1AP Bundle module. */
typedef struct audproc_param_id_ds1ap_vol_t audproc_param_id_ds1ap_vol_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vol_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VOL parameter used by the DS1AP Bundle module.
*/
struct audproc_param_id_ds1ap_vol_t
{
    int32_t                 bundle_volume; 
    /**< Numeric range  : [-2080,480] (which maps to [-130.00,30.00] dB)] with 4 fractional bits			
		 Default : 0.00 dB 
		 Parameter Type : Factory Configurable
		 The amount of gain which the user would like to be applied to the signal.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vol_t */


/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_vis
@{ */
/** ID of the Visualizer module in Dolby Surround1.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_VNNB
    - #AUDPROC_PARAM_ID_DS1AP_VNBF
	- #AUDPROC_PARAM_ID_DS1AP_VNBG
	- #AUDPROC_PARAM_ID_DS1AP_VNBE
	- #AUDPROC_PARAM_ID_DS1AP_VCBG
	- #AUDPROC_PARAM_ID_DS1AP_VCBG
	- #AUDPROC_PARAM_ID_DS1AP_VEN
	- #AUDPROC_PARAM_ID_DS1AP_VCNB
*/
#define AUDPROC_MODULE_ID_DS1AP_VIS    							0x0001072B

/** ID to get the Visualizer Band Count of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS module. 

    @msgpayload{audproc_param_id_ds1ap_vnnb_t}
    @table{weak__audproc__param__id__ds1ap__vnnb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VNNB   							0x0001072C


/** ID to get the Visualizer Band Center Frequencies of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS module. 

    @msgpayload{audproc_param_id_ds1ap_vnbf_t}
    @table{weak__audproc__param__id__ds1ap__vnbf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VNBF   							0x0001072D


/** ID to get the Visualizer Band Gains of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS module. 

    @msgpayload{audproc_param_id_ds1ap_vnbg_t}
    @table{weak__audproc__param__id__ds1ap__vnbg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VNBG   							0x0001072E


/** ID to get the Visualizer Band Excitations of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS module. 

    @msgpayload{audproc_param_id_ds1ap_vnbe_t}
    @table{weak__audproc__param__id__ds1ap__vnbe__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VNBE   							0x0001072F


/** ID to get the Visualizer Custom Band Gains of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS Module. 
    @msgpayload{audproc_param_id_ds1ap_vcbg_t}
    @table{weak__audproc__param__id__ds1ap__vcbg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VCBG   							0x00010730

/** ID to get the Visualizer Custom Band Excitations of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS module. 

    @msgpayload{audproc_param_id_ds1ap_vcbe_t}
    @table{weak__audproc__param__id__ds1ap__vcbe__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VCBE   							0x00010731


/** ID for the Visualizer Enable of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS Module. 

    @msgpayload{audproc_param_id_ds1ap_ven_t}
    @table{weak__audproc__param__id__ds1ap__ven__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VEN    							0x00010732

/** ID for the Visualizer Custom Band Count of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS Module. 

    @msgpayload{audproc_param_id_ds1ap_vcnb_t}
    @table{weak__audproc__param__id__ds1ap__vcnb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VCNB     						0x00010733

/** ID for the Visualizer Custom Band Center Frequencies of Dolby Surround1 used by AUDPROC_MODULE_ID_DS1AP_VIS Module.

    @msgpayload{audproc_param_id_ds1ap_vcbf_t}
    @table{weak__audproc__param__id__ds1ap__vcbf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VCBF      						0x00010734

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_vis */


/* Structure for the Visualizer Band Count parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vnnb_t audproc_param_id_ds1ap_vnnb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vnnb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VNNB parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vnnb_t
{
    uint32_t                  vis_band_count; 
    /**< Numeric range : [1,20]  
		 Default : 0 
		 Parameter Type : READ_ONLY
		 Returns the number of excitations and gains that can be natively exported from the signal chain.This value is dependent on the sample rate. 
		 It is always accessible regardless of whether the ‘AUDPROC_PARAM_ID_DS1AP_VEN’ parameter is on or off.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vnnb_t */


/* Structure for the Visualizer Band Center Frequency parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vnbf_t audproc_param_id_ds1ap_vnbf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vnbf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VNBF parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vnbf_t
{
    uint32_t                  vis_band_freq[20]; 
    /**< Numeric range : [20,20000]  
		 Default : 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 Hertz 
		 Parameter Type : READ_ONLY
		 Contains the center frequencies of the native visualizer bands.These center frequencies are dependent on the sample rate. They are always 
		 accessible regardless of whether the ‘AUDPROC_PARAM_ID_DS1AP_VEN’ parameter is on or off. The range of these centre frequencies is from 
		 20 to 20000 and are unscaled.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vnbf_t */	



/* Structure for the Visualizer Band Gains parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vnbg_t audproc_param_id_ds1ap_vnbg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vnbg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VNBG parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vnbg_t
{
    int32_t                  vis_band_gain[20]; 
    /**< Numeric range : [-32768,32767] 
		 Default : 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 dB 
		 Parameter Type : READ_ONLY
		 The ‘AUDPROC_PARAM_ID_DS1AP_VEN’ parameter must be 'Enabled' to read this value. The gains are scaled by 16. i.e., 16 = 1 dB.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vnbg_t */



/* Structure for the Visualizer Band Excitations parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vnbe_t audproc_param_id_ds1ap_vnbe_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vnbe_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VNBE parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vnbe_t
{
    int32_t                  vis_band_excitation[20]; 
    /**< Numeric range : [-32768,32767] 
		 Default : 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 dB 
		 Parameter Type : READ_ONLY
		 Contains the excitation data for the native visualizer bands. The ‘AUDPROC_PARAM_ID_DS1AP_VEN’ parameter must be 'on' 
		 to read this value. The excitations are scaled by 16. i.e. 16 = 1 dB.

 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vnbe_t */


/* Structure for the Visualizer Custom Band Gains parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vcbg_t audproc_param_id_ds1ap_vcbg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vcbg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VCBG parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vcbg_t
{
    int32_t                 vis_custom_band_gain[20]; 
    /**< Numeric range : [-32768,32767] 
		 Default : 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 dB 
		 Parameter Type : READ_ONLY
		 Contains the visualizer gains for the custom visualizer bands. The AUDPROC_PARAM_ID_DS1AP_VEN parameter must be 'on' to read this value.

 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vcbg_t */



/* Structure for the Visualizer Custom Band Excitations parameter for a DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vcbe_t audproc_param_id_ds1ap_vcbe_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vcbe_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VCBE parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vcbe_t
{
    int32_t                 vis_custom_band_excitation[20]; 
    /**< Numeric range : [-32768,32767] 
		 Default : 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 dB 
		 Parameter Type : READ_ONLY
		 Contains the excitation data for the custom visualizer bands. The AUDPROC_PARAM_ID_DS1AP_VEN parameter must be 'on' to read this value.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vcbe_t */


/* Structure for the Visualizer Enable parameter for the DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_ven_t audproc_param_id_ds1ap_ven_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ven_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VEN parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_ven_t
{
    int32_t               vis_enable; 
	/**< Supported Values: 
		 0 - disable
		 1 - enable
		 Default : 0
		 Parameter Type : Factory Configurable.		
		 Toggles support for visualization
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_ven_t */


/* Structure for the Visualizer Custom Band Count parameter for the DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vcnb_t audproc_param_id_ds1ap_vcnb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vcnb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VCNB parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vcnb_t
{
    uint32_t               vis_custom_band_count; 
	/**< Numerical Range: [1,20]
		 Default : 10
		 Parameter Type : Factory Configurable.		
		 The number of custom visualizer frequency bands to which the native bands will be mapped to. This parameter specifies the number
		 of center frequencies which will be supplied by the user. After this parameter is changed, the AUDPROC_PARAM_ID_DS1AP_VCBF parameter
		 must be updated. Changes to this parameter will not take effect until AUDPROC_PARAM_ID_DS1AP_VEN is 'on'.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vcnb_t */


/* Structure for the Visualizer Custom Band Center Frequencies parameter for the DS1AP Visualizer module. */
typedef struct audproc_param_id_ds1ap_vcbf_t audproc_param_id_ds1ap_vcbf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vcbf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VCBF parameter used by the DS1AP Visualizer module.
*/
struct audproc_param_id_ds1ap_vcbf_t
{
    uint32_t               vis_custom_band_freq[20]; 
	/**< Numerical Range: [20,20000] for each band in Hertz
		 Default : : 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 Hertz 
		 Parameter Type : Factory Configurable.		
		 The center frequencies of each custom visualizer band which the native band data will be interpolated onto. Changes to this parameter
		 will not take effect until AUDPROC_PARAM_ID_DS1AP_VEN is 'on'.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vcbf_t */


/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_ngs
@{ */

/** ID of the Next Generation Surround(NGS) module in Dolby Surround1.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_NGON
*/
#define AUDPROC_MODULE_ID_DS1AP_NGS   						0x00010735

/** ID of the Next Generation Surround(NGS) Enable used by AUDPROC_MODULE_ID_DS1AP_NGS.

    @msgpayload{audproc_param_id_ds1ap_ngon_t}
    @table{weak__audproc__param__id__ds1ap__ngon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_NGON   						0x00010736

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_ngs */


/* Structure for the Next Generation Surround(NGS) Enable parameter for a DS1AP NGS module. */
typedef struct audproc_param_id_ds1ap_ngon_t audproc_param_id_ds1ap_ngon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ngon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_NGON parameter used by the DS1AP NGS module.
*/
struct audproc_param_id_ds1ap_ngon_t
{
    uint32_t                 ngs_enable; 
    /**< Supported Values: 
			0 - Disable
			1 - Enable
			2 - Auto ;  Enable if either Dolby Headphone or Dolby Virtual Speaker is enabled
		 Default : 2 
		 Parameter Type : User Configurable.
		 Specifies the state of Next Generation Surround (NGS) module.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_ngon_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_ngs
@{ */

/** ID for the AUDPROC_MODULE_ID_DS1AP_DE module.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_DEON
	- #AUDPROC_PARAM_ID_DS1AP_DEA
	- #AUDPROC_PARAM_ID_DS1AP_DED
*/
#define AUDPROC_MODULE_ID_DS1AP_DE   							0x00010737

/** ID of the Dialog Enhancer(DE) Enable used by AUDPROC_MODULE_ID_DS1AP_DE.

    @msgpayload{audproc_param_id_ds1ap_deon_t}
    @table{weak__audproc__param__id__ds1ap__deon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DEON   							0x00010738

/** ID of the Dialog Enhancer Amount used by AUDPROC_MODULE_ID_DS1AP_DE.

    @msgpayload{audproc_param_id_ds1ap_dea_t}
    @table{weak__audproc__param__id__ds1ap__dea__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DEA  				 			0x00010739


/** ID of the Dialog Enhancer Ducking factor used by AUDPROC_MODULE_ID_DS1AP_DE.

    @msgpayload{audproc_param_id_ds1ap_ded_t}
    @table{weak__audproc__param__id__ds1ap__ded__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DED   							0x0001073A

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_ngs */


/* Structure for the Dialog Enhancer(DE) Enable parameter for a DS1AP DE module. */
typedef struct audproc_param_id_ds1ap_deon_t audproc_param_id_ds1ap_deon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_deon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DEON parameter used by the DS1AP DE module.
*/
struct audproc_param_id_ds1ap_deon_t
{
    uint32_t                 de_enable; 
    /**< Supported Values: 
			0 - Disable
			1 - Enable
		 Default : 0 
		 Parameter Type : User Configurable.
		 Specifies the state of Dialog Enhancement(DE) module.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_deon_t */


/* Structure for the Dialog Enhancer Amount parameter for a DS1AP DE module. */
typedef struct audproc_param_id_ds1ap_dea_t audproc_param_id_ds1ap_dea_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dea_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DEA parameter used by the DS1AP DE module.
*/
struct audproc_param_id_ds1ap_dea_t
{
    uint32_t                 de_amount; 
    /**< Numerical Range:  [0,16] (which maps to [0.00,1.00] ) with 4 fractional bits.
		 Default : 0.00
		 Parameter Type : User Configurable.
		 Controls the amount of dialog boosting.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dea_t */
 


/* Structure for the Dialog Enhancer Ducking parameter for a DS1AP DE module. */
typedef struct audproc_param_id_ds1ap_ded_t audproc_param_id_ds1ap_ded_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ded_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DED parameter used by the DS1AP DE module.
*/
struct audproc_param_id_ds1ap_ded_t
{
    uint32_t                 de_ducking; 
    /**< Numerical Range:  [0,16] (which maps to [0.00,1.00] ) with 4 fractional bits.
		 Default : 0.00
		 Parameter Type : User Configurable.
		 Controls the degree of suppresion of channels that do not have dialog content.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_ded_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_dv
@{ */

/** ID for the Dolby Volume Module in the Dolby Surround1.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_DVLE
	- #AUDPROC_PARAM_ID_DS1AP_DVLA
	- #AUDPROC_PARAM_ID_DS1AP_DVLI
	- #AUDPROC_PARAM_ID_DS1AP_DVLO
	- #AUDPROC_PARAM_ID_DS1AP_DVME
	- #AUDPROC_PARAM_ID_DS1AP_DVMC
*/
#define AUDPROC_MODULE_ID_DS1AP_DV   								0x0001073B

/** ID of the Dolby Volume Leveller Enable used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvle_t}
    @table{weak__audproc__param__id__ds1ap__dvle__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVLE  								0x0001073C


/** ID of the Dolby Volume Leveller Amount used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvla_t}
    @table{weak__audproc__param__id__ds1ap__dvla__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVLA  								0x0001073D


/** ID of the Dolby Volume Leveller Input Target used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvli_t}
    @table{weak__audproc__param__id__ds1ap__dvli__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVLI  								0x0001073E

/** ID of the Dolby Volume Leveller Output Target used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvlo_t}
    @table{weak__audproc__param__id__ds1ap__dvlo__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVLO									0x0001073F

/** ID of the Dolby Volume Modeller Enable used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvme_t}
    @table{weak__audproc__param__id__ds1ap__dvme__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVME  								0x00010740

/** ID of the Dolby Volume Modeller Calibration used by AUDPROC_MODULE_ID_DS1AP_DV.

    @msgpayload{audproc_param_id_ds1ap_dvmc_t}
    @table{weak__audproc__param__id__ds1ap__dvmc__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DVMC  								0x00010741

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_dv */


/* Structure for the Dolby Volume Leveller Enable parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvle_t audproc_param_id_ds1ap_dvle_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvle_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVLE parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvle_t
{
    uint32_t                 dvle_enable; 
   /**< Supported Values: 
			0 - Disable
			1 - Enable
		 Default : 1 
		 Parameter Type : User Configurable.
		 Specifies the state of Dolby Volume Leveler(DVLE) in the Dolby Volume module. 
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvle_t */


/* Structure for the Dolby Volume Leveller Amount parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvla_t audproc_param_id_ds1ap_dvla_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvla_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVLA parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvla_t
{
    uint32_t                 dvle_amount; 
	/**< Numerical Range:  [0,10] 
		 Default : 7
		 Parameter Type : User Configurable.
		 Defines how much the leveler can adjust the loudness to normalize different audio content.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvla_t */


/* Structure for the Dolby Volume Leveller Input Target parameter for the DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvli_t audproc_param_id_ds1ap_dvli_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvli_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVLI parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvli_t
{
    int32_t                 dvle_in_target; 
	/**< Numerical Range: [-640,0] (which maps to [-40.00,0.00] dB LKFS) with 4 fractional bits
		 Default : -20.00 dB LKFS
		 Parameter Type : Factory Configurable.
		 Sets the target average loudness level. Dolby Volume will level the audio to the average loudness level specified by the Leveler Input Target. 
		 The level is specified according to a K loudness weighting.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvli_t */



/* Structure for the Dolby Volume Leveller Target Output parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvlo_t audproc_param_id_ds1ap_dvlo_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvlo_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVLO parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvlo_t
{
    int32_t                 dvle_out_target; 
	/**< Numerical Range: [-640,0] (which maps to [-40.00,0.00] dB) with 4 fractional bits
		 Default : -20.00 dB 
		 Parameter Type : Factory Configurable.
		 The Leveler Output Target is set by a system designer in order to calibrate the system to the proper playback Sound Pressure Level[SPL].To compensate for the 
		 difference between mastering and playback levels, Dolby Volume applies an un-shaped digital gain of Leveler Output Target minus Leveler Input Target,
		 so that zero digital and analog volume produces reference loudness levels.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvlo_t */



/* Structure for the Dolby Volume Modeller Enable parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvme_t audproc_param_id_ds1ap_dvme_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvme_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVME parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvme_t
{
    uint32_t                 dvm_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
		 Default : 0
		 Parameter Type : User Configurable.
		 Specifies the state of Dolby Volume Modeler (DVM) module. 
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvme_t */


/* Structure for the Dolby Volume Modeller Calibration parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_dvmc_t audproc_param_id_ds1ap_dvmc_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dvmc_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DVMC parameter used by the DS1AP DV module.
*/
struct audproc_param_id_ds1ap_dvmc_t
{
    int32_t                 dvm_calibration; 
	/**< Numerical Range: [-320,320] (which maps to [-20.00,20.00] dB) with 4 fractional bits
		 Default : 0.00 dB 
		 Parameter Type : Factory Configurable.
		 The calibration offset provides the ability to fine-tune the actual playback-level after the Leveler Output Target has been set 
		 by the system manufacturer. This input parameter allows end users to adjust for variables such as listening positions or differing 
		 speaker sensitivities. For example, the end user of an A/V receiver (AVR) with Dolby Volume can recalibrate an AVR to optimize the
		 reference level for the user's actual listening position.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dvmc_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_ieq
@{ */

/** ID for the Intelligent Equalizer(IEQ) Module in the Dolby Surround1.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_IEON
	- #AUDPROC_PARAM_ID_DS1AP_IENB
	- #AUDPROC_PARAM_ID_DS1AP_IEBF
	- #AUDPROC_PARAM_ID_DS1AP_IEBT
	- #AUDPROC_PARAM_ID_DS1AP_IEA
*/
#define AUDPROC_MODULE_ID_DS1AP_IEQ   									0x00010742

/** ID of the Intelligent Equalizer Enable used by AUDPROC_MODULE_ID_DS1AP_IEQ.

    @msgpayload{audproc_param_id_ds1ap_ieon_t}
    @table{weak__audproc__param__id__ds1ap__ieon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_IEON   									0x00010743

/** ID of the Intelligent Equalizer Band Count used by AUDPROC_MODULE_ID_DS1AP_IEQ.

    @msgpayload{audproc_param_id_ds1ap_ienb_t}
    @table{weak__audproc__param__id__ds1ap__ienb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_IENB   									0x00010744

/** ID of the Intelligent Equalizer Band Center frequencies used by AUDPROC_MODULE_ID_DS1AP_IEQ.

    @msgpayload{audproc_param_id_ds1ap_iebf_t}
    @table{weak__audproc__param__id__ds1ap__iebf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_IEBF   								    0x00010745


/** ID of the Intelligent Equalizer Band Targets used by AUDPROC_MODULE_ID_DS1AP_IEQ.

    @msgpayload{audproc_param_id_ds1ap_iebt_t}
    @table{weak__audproc__param__id__ds1ap__iebt__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_IEBT   									0x00010746

/** ID of the Intelligent Equalizer Amount used by AUDPROC_MODULE_ID_DS1AP_IEQ.

    @msgpayload{audproc_param_id_ds1ap_iea_t}
    @table{weak__audproc__param__id__ds1ap__iea__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_IEA   									0x0001076A

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_ieq */


/* Structure for the Intelligent Equalizer Enable parameter for a DS1AP IEQ module. */
typedef struct audproc_param_id_ds1ap_ieon_t audproc_param_id_ds1ap_ieon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ieon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_IEON parameter used by the DS1AP IEQ module.
*/
struct audproc_param_id_ds1ap_ieon_t
{
    uint32_t                 ieq_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
		 Default : 0
		 Parameter Type : User Configurable.
		 Specifies the state of Intelligent Equalizer (IEQ) module. 
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_ieon_t */


/* Structure for the Intelligent Equalizer Band Count parameter for a DS1AP IEQ module. */
typedef struct audproc_param_id_ds1ap_ienb_t audproc_param_id_ds1ap_ienb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_ienb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_IENB parameter used by the DS1AP IEQ module.
*/
struct audproc_param_id_ds1ap_ienb_t
{
    uint32_t                 ieq_band_count; 
	/**< Numerical Range: [1,40]
		 Default : 10 
		 Parameter Type : Factory Configurable.
		 Specifies the number of Frequency bands Intelligent Equalizer operate in. Similar number of target band gains and center frequencies will need to be provided to the Intelligent Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_ienb_t */


/* Structure for the Intelligent Equalizer Band Center frequencies parameter for a DS1AP IEQ module. */
typedef struct audproc_param_id_ds1ap_iebf_t audproc_param_id_ds1ap_iebf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_iebf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_IEBF parameter used by the DS1AP IEQ module.
*/
struct audproc_param_id_ds1ap_iebf_t
{
    uint32_t                 ieq_band_freq[40]; 
	/**< Numerical Range: [20,20000] in hertz for each band.
		 Default : 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ... Hertz 
		 Parameter Type : Factory Configurable.
		 Specifies the band center frequencies for the Intelligent Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_iebf_t */


/* Structure for the Intelligent Equalizer Band Target parameter for a DS1AP IEQ module. */
typedef struct audproc_param_id_ds1ap_iebt_t audproc_param_id_ds1ap_iebt_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_iebt_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_IEBT parameter used by the DS1AP IEQ module.
*/
struct audproc_param_id_ds1ap_iebt_t
{
    int32_t                 ieq_band_target[40]; 
	/**< Numerical Range: [-480,480] (which maps to [-30.00,30.00] dBFS) with 4 fractional bits.
		 Default : 0.00, 0.00, 0.00, 0.00, ... dBFS
		 Parameter Type : Factory Configurable.
		 Specifies the band target levels for the Intelligent Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_iebt_t */


/* Structure for the Intelligent Equalizer Amount parameter for a DS1AP IEQ module. */
typedef struct audproc_param_id_ds1ap_iea_t audproc_param_id_ds1ap_iea_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_iea_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_IEA parameter used by the DS1AP IEQ module.
*/
struct audproc_param_id_ds1ap_iea_t
{
    int32_t                 ieq_amount; 
	/**< Numerical Range: [0,16] (which means [0.00,1.00] ) with 4 fractional bits.
		 Default : 0.63
		 Parameter Type : Factory Configurable.
		 Specifies the strength of the Intelligent Equalizer effect to apply.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_iea_t */


/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_geq
@{ */

/** ID for the Graphic Equalizer(GEQ) Module in the Dolby Surround1.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_GEON
	- #AUDPROC_PARAM_ID_DS1AP_GENB
	- #AUDPROC_PARAM_ID_DS1AP_GEBF
	- #AUDPROC_PARAM_ID_DS1AP_GEBG
*/
#define AUDPROC_MODULE_ID_DS1AP_GEQ						0x00010747

/** ID of the Graphic Equalizer Enable used by AUDPROC_MODULE_ID_DS1AP_GEQ.

    @msgpayload{audproc_param_id_ds1ap_geon_t}
    @table{weak__audproc__param__id__ds1ap__geon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_GEON   					0x00010748

/** ID of the Graphic Equalizer Band Count used by AUDPROC_MODULE_ID_DS1AP_GEQ.

    @msgpayload{audproc_param_id_ds1ap_genb_t}
    @table{weak__audproc__param__id__ds1ap__genb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_GENB   					0x00010749


/** ID of the Graphic Equalizer Band Center Frequencies used by AUDPROC_MODULE_ID_DS1AP_GEQ.

    @msgpayload{audproc_param_id_ds1ap_gebf_t}
    @table{weak__audproc__param__id__ds1ap__gebf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_GEBF   					0x0001074A

/** ID of the Graphic Equalizer Band Gains used by AUDPROC_MODULE_ID_DS1AP_GEQ.

    @msgpayload{audproc_param_id_ds1ap_gebg_t}
    @table{weak__audproc__param__id__ds1ap__gebg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_GEBG   					0x0001074B
/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_geq */


/* Structure for the Graphic Equalizer Enable parameter for a DS1AP GEQ module. */
typedef struct audproc_param_id_ds1ap_geon_t audproc_param_id_ds1ap_geon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_geon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_GEON parameter used by the DS1AP GEQ module.
*/
struct audproc_param_id_ds1ap_geon_t
{
    uint32_t                 geq_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
		 Default : 0
		 Parameter Type : User Configurable.
		 Specifies the state of Graphic Equalizer (GEQ) module. 
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_geon_t */


/* Structure for the Graphic Equalizer Band Count parameter for a DS1AP GEQ module. */
typedef struct audproc_param_id_ds1ap_genb_t audproc_param_id_ds1ap_genb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_genb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_GENB parameter used by the DS1AP GEQ module.
*/
struct audproc_param_id_ds1ap_genb_t
{
    uint32_t                 geq_band_count; 
	/**< Numerical Range: [1,40] 
		 Default : 10
		 Parameter Type : Factory Configurable.
		 Specifies the number of Frequency bands Graphic Equalizer operate in. Similar number of target band gains and center frequencies will need to be provided to the Intelligent Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_genb_t */


/* Structure for the Graphic Equalizer Band Center Frequency parameter for a DS1AP GEQ module. */
typedef struct audproc_param_id_ds1ap_gebf_t audproc_param_id_ds1ap_gebf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_gebf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_GEBF parameter used by the DS1AP GEQ module.
*/
struct audproc_param_id_ds1ap_gebf_t
{
    uint32_t                 geq_band_freq[40]; 
	/**< Numerical Range: [20,20000] in hertz for each band.
		 Default : 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ... Hertz
		 Parameter Type : Factory Configurable.
		 Specifies the band center frequencies for the Graphic Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_gebf_t */


/* Structure for the  Graphic Equalizer Band Gains parameter for a DS1AP DV module. */
typedef struct audproc_param_id_ds1ap_gebg_t audproc_param_id_ds1ap_gebg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_gebg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_GEBG parameter used by the DS1AP GEQ module.
*/
struct audproc_param_id_ds1ap_gebg_t
{
    int32_t                 geq_band_gain[40]; 
	/**< Numerical Range: [-576,576] (which maps to [-36.00,36.00] dB) with 4 fractional bits
		 Default : 0.00, 0.00, 0.00, 0.00, ... dB
		 Parameter Type : User Configurable
		 Specifies the band gains for the Graphic Equalizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_gebg_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_virtualizer
@{ */

/** ID for the Dolby Virtualizer Module in the Dolby Surround1. Virtualizer can be used in Dolby Headphone or Dolby Virtual Speaker mode.
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_VDHE
	- #AUDPROC_PARAM_ID_DS1AP_DHSB
	- #AUDPROC_PARAM_ID_DS1AP_DHRG
	- #AUDPROC_PARAM_ID_DS1AP_VSPE
	- #AUDPROC_PARAM_ID_DS1AP_DSSB
	- #AUDPROC_PARAM_ID_DS1AP_DSSA
	- #AUDPROC_PARAM_ID_DS1AP_DSSF	
	- #AUDPROC_PARAM_ID_DS1AP_SCPE
*/
#define AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER  						0x0001074C

/** ID of the Dolby Headphone(DH) Enable used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER. 

    @msgpayload{audproc_param_id_ds1ap_vdhe_t}
    @table{weak__audproc__param__id__ds1ap__vdhe__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VDHE    								0x0001074D


/** ID of the Dolby Headphone(DH) Surround Boost used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER. 

    @msgpayload{audproc_param_id_ds1ap_dhsb_t}
    @table{weak__audproc__param__id__ds1ap__dhsb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DHSB    								0x0001074E

/** ID of the Dolby Headphone(DH) Reverb Gain used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER. 

    @msgpayload{audproc_param_id_ds1ap_dhrg_t}
    @table{weak__audproc__param__id__ds1ap__dhrg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DHRG									0x0001074F


/** ID of the Dolby Virtual Speaker(DVS) Enable used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER. 

    @msgpayload{audproc_param_id_ds1ap_vspe_t}
    @table{weak__audproc__param__id__ds1ap__vspe__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VSPE      							0x00010750

/** ID of the Dolby Virtual Speaker(DVS) Surround Boost used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER.

    @msgpayload{audproc_param_id_ds1ap_dssb_t}
    @table{weak__audproc__param__id__ds1ap__dssb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DSSB      							0x00010751

/** ID of the Dolby Virtual Speaker(DVS) Speaker Angle used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER.

    @msgpayload{audproc_param_id_ds1ap_dssa_t}
    @table{weak__audproc__param__id__ds1ap__dssa__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DSSA        							0x00010752

/** ID of the Dolby Virtual Speaker(DVS) Start Frequency used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER.

    @msgpayload{audproc_param_id_ds1ap_dssf_t}
    @table{weak__audproc__param__id__ds1ap__dssf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_DSSF      							0x00010753

/** ID of the Dolby Virtual Surround Compressor Enable used by AUDPROC_MODULE_ID_DS1AP_VIRTUALIZER.

    @msgpayload{audproc_param_id_ds1ap_scpe_t}
    @table{weak__audproc__param__id__ds1ap__scpe__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_SCPE									0x00010754

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_virtualizer */


/* Structure for the Dolby Headphone(DH) Enable parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_vdhe_t audproc_param_id_ds1ap_vdhe_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vdhe_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VDHE parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_vdhe_t
{
    uint32_t                 dh_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
			2 – Auto ; Enable if no other virtualizer is enabled and endpoint is headphones.
		 Default : 0
		 Parameter Type : User Configurable.
		 Specifies the state of Dolby Headphone(DH).
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vdhe_t */


/* Structure for the Dolby Headphone(DH) Surround Boost parameter for the DS1AP Dolby Virtualizer module.*/
typedef struct audproc_param_id_ds1ap_dhsb_t audproc_param_id_ds1ap_dhsb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dhsb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DHSB parameter used by the DS1AP Dolby Virtualizer module..
*/
struct audproc_param_id_ds1ap_dhsb_t
{
    uint32_t                 dh_surr_boost; 
	/**< Numerical Range: [0,96] (which maps to [0.00,6.00] dB) with 4bits fractional value
		 Default : 6.00 dB
		 Parameter Type : User Configurable
		 Specifies the amount of boost applied to the surround channels when Dolby Headphone is enabled as the Virtualizer
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dhsb_t */



/* Structure for the Dolby Headphone(DH) Reverb Gain parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_dhrg_t audproc_param_id_ds1ap_dhrg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dhrg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DHRG parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_dhrg_t
{
    int32_t                 dh_reverb_gain; 
	/**< Numerical Range: [-2080,192] (which maps to [-130.00,12.00] dB) with 4bits fractional value.
		 Default : 6.00 dB
		 Parameter Type : User Configurable
		 Specifies the Amount of reverberation to add to the signal when Dolby Headphone is enabled as the virtualizer
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dhrg_t */



/* Structure for the Dolby Virtual Speaker(DVS) Enable parameter for the DS1AP Dolby Virtualizer module.*/
typedef struct audproc_param_id_ds1ap_vspe_t audproc_param_id_ds1ap_vspe_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vspe_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VSPE parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_vspe_t
{
    uint32_t                 vsp_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
			2 – Auto ; Enable if no other virtualizer is enabled and endpoint is internal speakers.
		 Default : 0
		 Parameter Type : User Configurable.
		 Specifies the state of Virtual Speaker(DVSQ).
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vspe_t */



/* Structure for the Dolby Virtual Speaker(DVS) Surround Boost parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_dssb_t audproc_param_id_ds1ap_dssb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dssb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DSSB parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_dssb_t
{
    uint32_t                 vsp_surr_boost; 
	/**< Numerical Range: [0,96] (which maps to [0.00,6.00] dB) with 4bits fractional value
		 Default : 6.00 dB
		 Parameter Type : User Configurable
		 Specifies the Amount of boost to the surround channels when Dolby Virtual Speaker is enabled as the virtualizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dssb_t */


/* Structure for the Dolby Virtual Speaker(DVS) Speaker Angle parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_dssa_t audproc_param_id_ds1ap_dssa_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dssa_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DSSA parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_dssa_t
{
    uint32_t                 vsp_spkr_angle; 
	/**< Numerical Range: [5,30] in degrees
		 Default : 10 degrees
		 Parameter Type : User Configurable
		 Informs Dolby Virtual speaker module, the physical angular separations of the loudspeakers.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dssa_t */


/* Structure for the Dolby Virtual Speaker(DVS) Start Frequency parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_dssf_t audproc_param_id_ds1ap_dssf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_dssf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_DSSF parameter used by the DS1AP Dolby Virtualizer module. 
*/
struct audproc_param_id_ds1ap_dssf_t
{
    uint32_t                 start_freq; 
	/**< Numerical Range: [20, 20000] in hertz.
		 Default : 20 Hertz
		 Parameter Type : User Configurable
		 Specifies the frequency below which, the signal will not get virtualized. This is useful for improving bass response.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_dssf_t */


/* Structure for the Dolby Virtual Surround Compressor Enable parameter for the DS1AP Dolby Virtualizer module. */
typedef struct audproc_param_id_ds1ap_scpe_t audproc_param_id_ds1ap_scpe_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_scpe_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_SCPE parameter used by the DS1AP Dolby Virtualizer module.
*/
struct audproc_param_id_ds1ap_scpe_t
{
    uint32_t                 scpe_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
			2 – Auto ; Enabled whenever Dolby virtual speaker or Dolby headphone are enabled.
		 Default : 2
		 Parameter Type : User Configurable.
		 Specifies the state of Virtual Surround Compressor.
		 Surround Compressor provides up to 6dB of boost to the surround channels. 
		 The amount of boost is given by the Dolby Virtual Speaker Surround Boost parameter when
		 Dolby Virtual Speaker is enabled and the Dolby Headphone Surround Boost parameter otherwise.
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_scpe_t */




/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_vm
@{ */

/** ID for the Volume Maximizer in the Dolby Surround1. 
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_VMON
	- #AUDPROC_PARAM_ID_DS1AP_VMB
*/
#define AUDPROC_MODULE_ID_DS1AP_VM  					0x00010755


/** ID of the Volume Maximizer Enable used by the AUDPROC_MODULE_ID_DS1AP_VM .

    @msgpayload{audproc_param_id_ds1ap_vmon_t}
    @table{weak__audproc__param__id__ds1ap__vmon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VMON        				0x00010756

/** ID of the Volume Maximizer Boost used by the AUDPROC_MODULE_ID_DS1AP_VM.

    @msgpayload{audproc_param_id_ds1ap_vmb_t}
    @table{weak__audproc__param__id__ds1ap__vmb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_VMB        				0x00010757

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_vm */



/* Structure for the Volume Maximizer Enable parameter for the DS1AP Volume Maximizer module. */
typedef struct audproc_param_id_ds1ap_vmon_t audproc_param_id_ds1ap_vmon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vmon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VMON parameter used by the DS1AP Volume Maximizer module.
*/
struct audproc_param_id_ds1ap_vmon_t
{
    uint32_t                 vm_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
			2 – Auto ; Enabled if Dolby Volume Leveler is enabled.
		 Default : 2
		 Parameter Type : User Configurable.
		 Specifies the state of Volume Maximizer.
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vmon_t */


/* Structure for the Volume Maximizer Boost parameter for the DS1AP Volume Maximizer module. */
typedef struct audproc_param_id_ds1ap_vmb_t audproc_param_id_ds1ap_vmb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_vmb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_VMB parameter used by the DS1AP Volume Maximizer module.
*/
struct audproc_param_id_ds1ap_vmb_t
{
    uint32_t                 vm_boost; 
	/**< Numerical Range: [0,240] (which maps to [0.00,15.00] dB) with 4 fractional bits.
		 Default : 9.00 dB
		 Parameter Type : User Configurable
		 Specifies the amount of signal boost to be applied by the Volume Maximizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_vmb_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_ao
@{ */

/** ID for the Audio Optimizer in the Dolby Surround1. 
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_AOON
	- #AUDPROC_PARAM_ID_DS1AP_AOCC
	- #AUDPROC_PARAM_ID_DS1AP_AONB
	- #AUDPROC_PARAM_ID_DS1AP_AOBF
	- #AUDPROC_PARAM_ID_DS1AP_AOBG
*/
#define AUDPROC_MODULE_ID_DS1AP_AO  						0x00010758

/** ID of the Audio Optimizer Enable used by AUDPROC_MODULE_ID_DS1AP_AO.

    @msgpayload{audproc_param_id_ds1ap_aoon_t}
    @table{weak__audproc__param__id__ds1ap__aoon__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AOON       					0x00010759

/** ID of the Audio Optimizer Channel Count used by AUDPROC_MODULE_ID_DS1AP_AO.

    @msgpayload{audproc_param_id_ds1ap_aocc_t}
    @table{weak__audproc__param__id__ds1ap__aocc__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AOCC       					0x0001075A


/** ID of the Audio Optimizer Band Count used by AUDPROC_MODULE_ID_DS1AP_AO.

    @msgpayload{audproc_param_id_ds1ap_aonb_t}
    @table{weak__audproc__param__id__ds1ap__aonb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AONB        					0x0001075B

/** ID of the Audio Optimizer Band Center frequencies used by AUDPROC_MODULE_ID_DS1AP_AO.

    @msgpayload{audproc_param_id_ds1ap_aobf_t}
    @table{weak__audproc__param__id__ds1ap__aobf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AOBF         				0x0001075C

/** ID of the Audio Optimizer Band Gains for each channel used by AUDPROC_MODULE_ID_DS1AP_AO.

    @msgpayload{audproc_param_id_ds1ap_aobg_t}
    @table{weak__audproc__param__id__ds1ap__aobg__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AOBG        					0x0001075D

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_ao */

/* Structure for the Audio Optimizer Enable parameter for the Audio Optimizer module. */
typedef struct audproc_param_id_ds1ap_aoon_t audproc_param_id_ds1ap_aoon_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_aoon_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AOON parameter used by the Audio Optimizer module.
*/
struct audproc_param_id_ds1ap_aoon_t
{
    uint32_t                 ao_enable; 
	/**< Supported Values: 
			0 - Disable
			1 - Enable
			2 – Auto ; Enable if endpoint is set as internal speakers.
		 Default : 2
		 Parameter Type : Factory Configurable.
		 Specifies the state of the Audio Optimizer.
*/
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_aoon_t */


/* Structure for the Audio Optimizer Channel Count parameter for the Audio Optimizer module. */
typedef struct audproc_param_id_ds1ap_aocc_t audproc_param_id_ds1ap_aocc_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_aocc_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AOCC parameter used by the Audio Optimizer module.
*/
struct audproc_param_id_ds1ap_aocc_t
{
    uint32_t                 ao_ch_count; 
	/**< Numerical Range: [0,8]
		 Default : 1
		 Parameter Type : Factory Configurable.
		 The maximum number of channel data, which will be provided to the Audio Optimizer.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_aocc_t */


/* Structure for the Audio Optimizer Band Count parameter for the Audio Optimizer module. */
typedef struct audproc_param_id_ds1ap_aonb_t audproc_param_id_ds1ap_aonb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_aonb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AONB parameter used by the Audio Optimizer module.
*/
struct audproc_param_id_ds1ap_aonb_t
{
    uint32_t                 ao_band_count; 
	/**< Numerical Range: [1,40]
		 Default : 10
		 Parameter Type : Factory Configurable.
		 Specifies the number of frequency bands per channel, in which Audio Optimizer will be operating in.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_aonb_t */


/* Structure for the Audio Optimizer Band Center frequency parameter for Audio Optimizer module. */
typedef struct audproc_param_id_ds1ap_aobf_t audproc_param_id_ds1ap_aobf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_aobf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AOBF parameter used by the Audio Optimizer module.
*/
struct audproc_param_id_ds1ap_aobf_t
{
    uint32_t                ao_band_freq[40]; 
	/**< Numerical Range: [20,20000] in hertz for each band.
		 Default : 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ... Hertz
		 Parameter Type : Factory Configurable.
		 Specifies the center frequencies of each band of Audio Optimizer.
 */
}
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_aobf_t */


/* Structure for the Audio Optimizer Band Gains parameter of each channel for the Audio Optimizer module. */
typedef struct audproc_param_id_ds1ap_aobg_t audproc_param_id_ds1ap_aobg_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_aobg_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AOBG parameter used by the Audio Optimizer module.
*/
struct audproc_param_id_ds1ap_aobg_t
{
    int32_t                ao_band_gain[329]; 
	/**< Numerical Range: [-480,480] (which maps to [-30.00,30.00] dB)
		 Default : 2, 0.00, 0.00, 0.00 ... dB
		 Parameter Type : Factory Configurable.
		 Specifies the gains for each band corresponding to each channel in the Audio Optimizer.
		 NOTE:	This data is stored channel by channel. Each data set is preceeded by a channel identifier for that particular set of gains. 
		 The data array will stop searching when either 'AUDPROC_PARAM_ID_DS1AP_AOCC' number of channels worth of data has been read or the 
		 channel ID AK_CHAN_EMPTY is encountered. All other channels (if applicable) will be set to have a gain of 0 dB.
		 Enumerated values of channel identifiers as mentioned above are given below:
		 AK_CHAN_EMPTY    (0)
		 AK_CHAN_L        (2)
		 AK_CHAN_R        (3)
		 AK_CHAN_C        (4)
		 AK_CHAN_LFE      (5)
		 AK_CHAN_Ls       (7)
		 AK_CHAN_Rs       (8)
		 AK_CHAN_Lb       (9)
		 AK_CHAN_Rb      (10)		 
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_aobg_t */


/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_are
@{ */

/** ID for the Audio Regulator in the Dolby Surround1. 
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_ARNB
	- #AUDPROC_PARAM_ID_DS1AP_ARBF
	- #AUDPROC_PARAM_ID_DS1AP_ARBI
	- #AUDPROC_PARAM_ID_DS1AP_ARBL
	- #AUDPROC_PARAM_ID_DS1AP_ARBH
	- #AUDPROC_PARAM_ID_DS1AP_AROD
	- #AUDPROC_PARAM_ID_DS1AP_ARTP
*/
#define AUDPROC_MODULE_ID_DS1AP_ARE                         0x0001075E

/** ID of the Audio Regulator Band Count used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arnb_t}
    @table{weak__audproc__param__id__ds1ap__arnb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARNB         			    0x0001075F

/** ID of the Audio Regulator Band Center Frequencies used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arbf_t}
    @table{weak__audproc__param__id__ds1ap__arbf__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARBF          				0x00010760

/** ID of the Audio Regulator Band Isolate used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arbi_t}
    @table{weak__audproc__param__id__ds1ap__arbi__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARBI          				0x00010761

/** ID of the Audio Regulator Band Thresholds Lower used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arbl_t}
    @table{weak__audproc__param__id__ds1ap__arbl__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARBL           				0x00010762

/** ID of the Audio Regulator Band Thresholds Higher used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arbh_t}
    @table{weak__audproc__param__id__ds1ap__arbh__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARBH       					0x00010763

/** ID of the Audio Regulator Overdrive used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_arod_t}
    @table{weak__audproc__param__id__ds1ap__arod__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_AROD      					0x00010764

/** ID of the Audio Regulator Timbre Preservation used by AUDPROC_MODULE_ID_DS1AP_ARE.

    @msgpayload{audproc_param_id_ds1ap_artp_t}
    @table{weak__audproc__param__id__ds1ap__artp__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_ARTP    						0x00010765

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_are */

/* Structure for the Audio Regulator Band Count parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arnb_t audproc_param_id_ds1ap_arnb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arnb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARNB parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arnb_t
{
    uint32_t                ar_band_count; 
	/**< Numerical Range: [1,40]
		 Default : 10
		 Parameter Type : Factory Configurable.
		 Specifies the number of frequency bands which will be supplied to the Audio Regulator.
		 When this value changes, the Band Frequencies(AUDPROC_PARAM_ID_DS1AP_ARBF), Isolates(AUDPROC_PARAM_ID_DS1AP_ARBI), 
		 the Higher Thresholds(AUDPROC_PARAM_ID_DS1AP_ARBH) and Lower Thresholds(AUDPROC_PARAM_ID_DS1AP_ARBL) must all be re-written. 
		 The Audio Regulator will not be permitted to enter speaker distortion limiting mode until valid data has been supplied.		 
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arnb_t */


/* Structure for the Audio Regulator Band Center Frequencies parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arbf_t audproc_param_id_ds1ap_arbf_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arbf_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARBF parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arbf_t
{
    uint32_t                ar_band_freq[40]; 
	/**< Numerical Range: [20,20000] in hertz for each band.
		 Default : 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ... Hertz
		 Parameter Type : Factory Configurable.
		 An array of specifying the center frequencies of the bands the Audio Regulator will operate on.
		 These values must increment from lowest to highest. Invalid data will cause the Audio Regulator to not be permitted to enter 
		 speaker distortion limiting mode. The 'AUDPROC_PARAM_ID_DS1AP_ARBI', 'AUDPROC_PARAM_ID_DS1AP_ARBL' and 'AUDPROC_PARAM_ID_DS1AP_ARBH' 
		 parameters must be updated after modifying this parameter.	 
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arbf_t */


/* Structure for the Audio Regulator Band Isolate parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arbi_t audproc_param_id_ds1ap_arbi_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arbi_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARBI parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arbi_t
{
    uint32_t                ar_band_islolates[40]; 
	/**< Supported Values: 
			0 - Regulated
			1 - Isolated			
		 Default : 0,0,0,0,0,0,0,…0,0,0
		 Parameter Type : Factory Configurable.
		 Specifies whether to operate bands in isolated or regulated mode. No Timbre Preservation will be applied to isolated bands.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arbi_t */


/* Structure for the Audio Regulator Band Low Thresholds parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arbl_t audproc_param_id_ds1ap_arbl_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arbl_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARBL parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arbl_t
{
    int32_t               ar_band_lt[40]; 
	/**< Numerical Range: [-2080,0] (which maps to[-130.00,0.00] dBFS) with 4 fractional bits.
		 Default : -12.00, -12.00, -12.00, -12.00, -12.00, -12.00, -12.00, -12.00, -12.00 ...., -12.00 dBFS
		 Parameter Type : Factory Configurable.		
		 Specifies the low onset point of the compression curve.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arbl_t */


/* Structure for the Audio Regulator Band High Thresholds  parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arbh_t audproc_param_id_ds1ap_arbh_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arbh_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARBH parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arbh_t
{
    int32_t               ar_band_ht[40]; 
	/**< Numerical Range: [-2080,0] (which maps to [-130.00,0.00] dBFS) with 4 fractional bits.
		 Default : 0.00, 0.00, 0.00, 0.00, 0.00 , 0.00, 0.00, 0.00,...., 0.00 dBFS
		 Parameter Type : Factory Configurable.		
		 Specifies the higher limiting point of the compression curve.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arbh_t */


/* Structure for the Audio Regulator Overdrive parameter for the DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_arod_t audproc_param_id_ds1ap_arod_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_arod_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_AROD parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_arod_t
{
    uint32_t               ar_overdrive; 
	/**< Numerical Range: [0,192] (which maps to[0.00,12.00] dB) with 4 fractional bits.
		 Default : 0.00 dB
		 Parameter Type : Factory Configurable.		
		 Specifies the amount,the signal is allowed to push past the distortion thresholds.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_arod_t */


/* Structure for the Audio Regulator Timbre Preservation for a DS1AP Audio Regulator module. */
typedef struct audproc_param_id_ds1ap_artp_t audproc_param_id_ds1ap_artp_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_artp_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_ARTP parameter used by the DS1AP Audio Regulator module.
*/
struct audproc_param_id_ds1ap_artp_t
{
    uint32_t               ar_tp_amount; 
	/**< Numerical Range: [0,16] (which maps to [0.00,1.00] ) with 4 fractional bits.
		 Default : 1.00
		 Parameter Type : Factory Configurable.		
		 Controls the compromise between loudness and timbre preservation at high volume levels.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_artp_t */



/** @cond OEM_only */
/** @addtogroup audio_pp_module_ds1ap_plim
@{ */

/** ID for the Peak Limiter in the Dolby Surround1. 
    This module supports the following parameter IDs:
    - #AUDPROC_PARAM_ID_DS1AP_PLMD
	- #AUDPROC_PARAM_ID_DS1AP_PLB
	- #AUDPROC_PARAM_ID_DS1AP_TEST
*/
#define AUDPROC_MODULE_ID_DS1AP_PLIM   					0x00010766

/** ID of the Peak Limiting and Protection Mode used by AUDPROC_MODULE_ID_DS1AP_PLIM.

    @msgpayload{audproc_param_id_ds1ap_plmd_t}
    @table{weak__audproc__param__id__ds1ap__plmd__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_PLMD    					0x00010767

/** ID of the Peak Limiter Boost used by AUDPROC_MODULE_ID_DS1AP_PLIM.

    @msgpayload{audproc_param_id_ds1ap_plb_t}
    @table{weak__audproc__param__id__ds1ap__plb__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_PLB     					0x00010768

/** ID of the Peak Limiter Test Mode Enable used by AUDPROC_MODULE_ID_DS1AP_PLIM.

    @msgpayload{audproc_param_id_ds1ap_test_t}
    @table{weak__audproc__param__id__ds1ap__test__t}
*/
#define AUDPROC_PARAM_ID_DS1AP_TEST      				0x00010769

/** @endcond */
/** @} */ /* end_addtogroup audio_pp_module_ds1ap_plim */



/* Structure for the Peak Limiting and Protection Mode parameter for the DS1AP Peak Limiter module. */
typedef struct audproc_param_id_ds1ap_plmd_t audproc_param_id_ds1ap_plmd_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_plmd_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_PLMD parameter used by the DS1AP Peak Limiter module.
*/
struct audproc_param_id_ds1ap_plmd_t
{
    uint32_t               plim_mode; 
	/**< Supported Values: 
		 0 - DS1_PLMD_DISABLE_ALL
		 1 - DS1_PLMD_PEAK_ONLY
		 2 - DS1_PLMD_REGULATED_PEAK
		 3 - DS1_PLMD_REGULATED_DISTORTION
		 4 - DS1_PLMD_AUTO
		 Default : 4
		 Parameter Type : Factory Configurable.		
		 Specifies or controls the state of the Peak Limiter and Audio Regulator
		 •	DS1_PLMD_DISABLE_ALL - Audio Regulator and Peak Limiter will be disabled.
		 •	DS1_PLMD_PEAK_ONLY - Peak Limiter will be enabled and Audio Regulator will be disabled.
		 •	DS1_PLMD_REGULATED_PEAK - Peak Limiter will be enabled and the Audio Regulator will be enabled in a 'peak limiting only' mode.
		 •	DS1_PLMD_REGULATED_DISTORTION - Peak Limiter will be enabled and the Audio Regulator will be enabled in 'speaker distortion limiting' mode.
		 •	DS1_PLMD_AUTO - The Peak Limiter and Audio Regulator are always enabled. The Audio Regulator will be operating in peak limiting only mode unless 
			the endpoint is ‘internal speakers’, in which case the Audio Regulator will operate in speaker distortion limiting mode.
			NOTE:	The Audio Regulator will not be enabled if the Peak Limiter is disabled.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_plmd_t */



/* Structure for the Peak Limiter Boost parameter for the DS1AP Peak Limiter module. */
typedef struct audproc_param_id_ds1ap_plb_t audproc_param_id_ds1ap_plb_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_plb_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_PLB parameter used by the DS1AP Peak Limiter module.
*/
struct audproc_param_id_ds1ap_plb_t
{
    uint32_t               plim_boost; 
	/**< Numerical Range: [0,192] (which means [0.00,12.00] dB) with 4 fractional bits.
		 Default : 0.00 dB
		 Parameter Type : Factory Configurable.		
		 Specifies the gain in dB by which the signal will be boosted. The limiter will apply this maximum gain if the resulting signal is less than the allowed peak level.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_plb_t */


/* Structure for the Peak Limiter Test Mode Enable parameter for the DS1AP Peak limiter Module. */
typedef struct audproc_param_id_ds1ap_test_t audproc_param_id_ds1ap_test_t;

#include "adsp_begin_pack.h"
/** @weakgroup weak_audproc_param_id_ds1ap_test_t
@{ */
/* Payload of the AUDPROC_PARAM_ID_DS1AP_TEST parameter used by the DS1AP Peak limiter Module.
*/
struct audproc_param_id_ds1ap_test_t
{
    uint32_t               plim_test_mode; 
	/**< Supported Values: 
		 0 - Peak Limiter will behave normally
		 1 – Peak Limiter will be in test mode. In this mode, peak limiter performs a hard clip to limit the output signal.
		 Default : 0
		 Parameter Type : Factory Configurable.		
		 Toggles test mode in the peak limiter.
 */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_audproc_param_id_ds1ap_test_t */

#define AUDPROC_PARAM_ID_DS1AP_MIXED_STEREO_ENABLE    0x108c7

typedef struct audproc_param_id_ds1ap_mixed_streo_enable_t audproc_param_id_ds1ap_mixed_streo_enable_t;

#include "adsp_begin_pack.h"
struct audproc_param_id_ds1ap_mixed_streo_enable_t
{
    uint32_t               enable;
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

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif // #ifdef _ADSP_DS1AP_API_H_
          
