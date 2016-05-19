/*! \file
 *  
 *  \brief  pm_lpass_proc_pam.c ----This file contains PAM information for NPA
 *  \details This file contains PAM information for NPA for all NPA Clients and Modes
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation NPA Client Version: MSM8x10_PM8110_NPA_2012_12_14 - Approved
 *    PMIC code generation NPA Device Setting Value Version: MSM8x10_PM8110_NPA_2012_12_14 - Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2012 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/config/msm8x10/pm_lpass_proc_pam.c#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

/* =======================================================================
 For more information regarding these settings please see document: 
Qualcomm PMIC NPA (QPN) Node
System Software Specification
80-VN657-xxx
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when        who      what, where, why
--------    ---      ----------------------------------------------------------
6/6/2013    akt      Fixed the node dependancy size for handling suppresible (CR-555420)
12/14/2012	NA\hcorleto	MSM8x10_PM8110_NPA_2012_12_14 - Approved 
Comments: 1.Version Notes:
Initial version for SW development (with errors fixed)

2.Applicability:
	
3.Release Priority(Urgent/Medium/Low/Not for release):
	
4.Verification(How/Who will test):
	

========================================================================== */
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "pm_npa.h"
#include "pmapp_npa.h"
#include "pm_lpass_proc_npa.h"
#include "pm_npa_device.h"
#include "pm_npa_device_clk_buff.h"
#include "pm_npa_device_ldo.h"
#include "pm_npa_device_smps.h"
#include "pm_npa_device_ncp.h"
#include "pm_npa_device_vs.h"
#include "npa_remote_resource.h"

#include "pm_lpass_proc_npa.h"
#include "pm_lpass_proc_npa_device.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                LOCAL FUNCTION PROTOTYPES

===========================================================================*/

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/

static pm_npa_smps_kvps
pm_pam_rail_cx_a_smps1[] =
{
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_RETENTION
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__1,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW_MINUS
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW
    // Comments: 	AKA SVS
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__3,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__4,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL_PLUS
    // Comments: 	AKA Turbo
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__5,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_TURBO
    // Comments: 	AKA Super Turbo
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__6,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
};

static pm_npa_pam_client_cfg_type
pm_pam_rail_cx_rails_info[] =
{
   {
      (void*)pm_pam_rail_cx_a_smps1,
      PM_NPA_VREG_SMPS
   },
};
/* RAIL_MX Client */
static pm_npa_ldo_kvps
pm_pam_rail_mx_a_ldo3[] =
{
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_RETENTION
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 800000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 25, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW_MINUS
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW
    // Comments: 	AKA SVS
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1150000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 600,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 50, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1150000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 600,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 50, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL_PLUS
    // Comments: 	AKA Turbo
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1275000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 600,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 50, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_TURBO
    // Comments: 	AKA Super Turbo
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1275000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 600,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 50, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
};

static pm_npa_pam_client_cfg_type
pm_pam_rail_mx_rails_info[] =
{
   {
      (void*)pm_pam_rail_mx_a_ldo3,
      PM_NPA_VREG_LDO
   },
};


/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_RAIL_CX   "/node/pmic/client/rail_cx"
#define PMIC_NPA_CLIENT_NODE_RAIL_MX   "/node/pmic/client/rail_mx"


/* RAIL_CX Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_rail_cx [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, smps, 1 )
};

/* RAIL_MX Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_rail_mx [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 3 )
};


pm_npa_node_resource_info pmic_npa_lpass_node_resources[] =
{
   {
      PMIC_NPA_GROUP_ID_RAIL_CX,                      // Resource Name
      PMIC_NPA_MODE_ID_CORE_RAIL_MAX - 1,             // Maximum value
      NPA_RESOURCE_DEFAULT,                           // Resource Attributes
      (void*) pm_pam_rail_cx_rails_info,              // Resource User Data
      PMIC_NPA_CLIENT_NODE_RAIL_CX,                   // Node Name
      NPA_NODE_DEFAULT,                               // Node Attributes
      NULL,                                           // Node User Data
      pm_lpass_proc_client_dev_deps_rail_cx,          // Node dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_rail_cx),    // Node dependency count
      PM_NPA_PLUGIN_TYPE_MAX                          // Type of NPA plugin to use
   },
   {
      PMIC_NPA_GROUP_ID_RAIL_MX,                      // Resource Name
      PMIC_NPA_MODE_ID_CORE_RAIL_MAX - 1,             // Maximum value
      NPA_RESOURCE_DEFAULT,                           // Resource Attributes
      (void*) pm_pam_rail_mx_rails_info,              // Resource User Data
      PMIC_NPA_CLIENT_NODE_RAIL_MX,                   // Node Name
      NPA_NODE_DEFAULT,                               // Node Attributes
      NULL,                                           // Node User Data
      pm_lpass_proc_client_dev_deps_rail_mx,          // Node dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_rail_mx),    // Node dependency count
      PM_NPA_PLUGIN_TYPE_MAX                          // Type of NPA plugin to use
   },
};

unsigned num_of_pmic_lpass_nodes[] = { 2 };


// Remote resource definitions.
static pm_npa_remote_name_type pmic_npa_ldo_remote_resources [] =
{  
   {
     PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 3),
     "ldoa\x03\x00\x00\x00",
   },
};


pm_npa_remote_resource_type pmic_npa_remote_ldo =
{
   pmic_npa_ldo_remote_resources,
   1
};


static pm_npa_remote_name_type pmic_npa_vs_remote_resources [] =
{  
   {NULL}
};

pm_npa_remote_resource_type pmic_npa_remote_vs =
{
   pmic_npa_vs_remote_resources,
   0
};

static pm_npa_remote_name_type pmic_npa_smps_remote_resources [] =
{  
   {
     PMIC_DEV_RSRC_NAME_VEC_IN( A, smps, 1),
     "smpa\x01\x00\x00\x00",
   }
};

pm_npa_remote_resource_type pmic_npa_remote_smps =
{
   pmic_npa_smps_remote_resources,
   1
};

