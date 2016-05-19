/*! \file  pm_config_lpass_npa_pam.c
 *  
 *  \brief  This file contains PAM information for NPA
 *  \details This file contains PAM information for NPA for all NPA Clients and Modes
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation NPA Client Version: VU.PMA8084.MPQ8092.11192013v1a - Approved
 *    PMIC code generation NPA Device Setting Value Version: VU.PMA8084.MPQ8092.11192013v1a - Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2013 Qualcomm Technologies, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/config/mpq8092/pm8084/pm_lpass_proc_pam.c#1 $ 

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
11/19/2013	NA\orlandos	VU.PMA8084.MPQ8092.11192013v1a - Approved 
Comments: 1.Version Notes:  Removed HFPLL1 because is never used by LPASS.  On Cx
client made the corner voltage to KVP not generated because it was 
causing issues with compiler.  
	
2.Applicability:
	
3.Release Priority(Urgent/Medium/Low/Not for release):
	
4.Verification(How/Who will test):
	

10/11/2013	NA\orlandos	VU.PMA8084.MPQ8092.10022013v1a - Approved 
Comments: 1.Version Notes:  Locking initial PAM table for RPM in MPQ8092.
	
2.Applicability:
	
3.Release Priority(Urgent/Medium/Low/Not for release):
	
4.Verification(How/Who will test):
	

10/2/2013	NA\orlandos	VU.PMA8084.MPQ8092.10022013v1 - Approved 
Comments: 1.Version Notes:
	
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
#include "npa_remote_resource.h"

#include "pm_npa_device_clk_buff.h"
#include "pm_npa_device_ldo.h"
#include "pm_npa_device_smps.h"
#include "pm_npa_device_ncp.h"
#include "pm_npa_device_vs.h"

#include "pm_lpass_proc_npa.h"
#include "pm_lpass_proc_npa_device.h"

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/
/* RAIL_CX Client */
static pm_npa_smps_kvps
pm_pam_rail_cx_a_smps8 [] =
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
    // Comments: 	Do not use
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
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__2,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW
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
pm_pam_rail_cx_rails_info []=
{
   {
      (void*)pm_pam_rail_cx_a_smps8,
      PM_NPA_VREG_SMPS
   },
};
/* RAIL_MX Client */
static pm_npa_smps_kvps
pm_pam_rail_mx_a_smps8 [] =
{
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 670000,  /**< [X uV] -> max aggregation */
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
      PM_NPA_KEY_MICRO_VOLT, 4, 670000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW_MINUS
    // Comments: 	Do not use
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 950000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_LOW
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 950000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__AUTO,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 950000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL_PLUS
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__NPM,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1050000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
    // Mode: 		PMIC_NPA_MODE_ID_CORE_RAIL_TURBO
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_SMPS_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_SMPS__NPM,  /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1050000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_FREQUENCY, 4, PM_SWITCHING_FREQ_FREQ_NONE,  /**< [xx MHz] -> max within a priority group */
      PM_NPA_KEY_FREQUENCY_REASON, 4, PM_NPA_FREQ_REASON_NONE,  /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority) */
      PM_NPA_KEY_FOLLOW_QUIET_MODE, 4, PM_NPA_QUIET_MODE__DISABLE,  /**< [None, Quiet, Super Quiet] -> max aggregation (left to right)  */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
   },
};

static pm_npa_pam_client_cfg_type
pm_pam_rail_mx_rails_info []=
{
   {
      (void*)pm_pam_rail_mx_a_smps8,
      PM_NPA_VREG_SMPS
   },
};
/* SENSOR_VDD Client */
static pm_npa_ldo_kvps
pm_pam_sensor_vdd_a_ldo15 [] =
{
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 2700000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
   },
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 2700000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 11,  /**< [X mA] -> max aggregation */
      PM_NPA_KEY_HEAD_ROOM, 4, 0, /**< head_room_voltage_value */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
   },
};

static pm_npa_pam_client_cfg_type
pm_pam_sensor_vdd_rails_info []=
{
   {
      (void*)pm_pam_sensor_vdd_a_ldo15,
      PM_NPA_VREG_LDO
   },
};
/* SENSOR_VDDIO Client */
static pm_npa_vs_kvps
pm_pam_sensor_vddio_a_vs2 [] =
{
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> max aggregation */
   },
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> max aggregation */
   },
    // Mode: 		PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right) */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> max aggregation */
   },
};

static pm_npa_pam_client_cfg_type
pm_pam_sensor_vddio_rails_info []=
{
   {
      (void*)pm_pam_sensor_vddio_a_vs2,
      PM_NPA_VREG_VS
   },
};





/*===========================================================================

                RESOURCE VARIABLES DEFINITIONS

===========================================================================*/
#define PMIC_NPA_CLIENT_NODE_RAIL_CX   "/node/pmic/client/rail_cx"
#define PMIC_NPA_CLIENT_NODE_RAIL_MX   "/node/pmic/client/rail_mx"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDD   "/node/pmic/client/sensor_vdd"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO   "/node/pmic/client/sensor_vddio"

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/



/* RAIL_CX Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_rail_cx [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, smps, 8 ),
};

/* RAIL_MX Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_rail_mx [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, smps, 8 ),
};

/* SENSOR_VDD Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_sensor_vdd [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 15 ),
};

/* SENSOR_VDDIO Client */
static npa_node_dependency 
pm_lpass_proc_client_dev_deps_sensor_vddio [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, vs, 2 ),
};

/*PMIC NPA Node Resource Info */
pm_npa_node_resource_info
pm_npa_lpass_pam_node_rsrcs[] =
{
   {
      PMIC_NPA_GROUP_ID_RAIL_CX,                                  // Resource Name
      PMIC_NPA_MODE_ID_CORE_RAIL_MAX - 1,                         // Maximum value
      NPA_RESOURCE_DEFAULT,                                       // Resource Attributes
      (void*) pm_pam_rail_cx_rails_info,                          // Resource User Data
      PMIC_NPA_CLIENT_NODE_RAIL_CX,                               // Node Name
      NPA_NODE_DEFAULT,                                           // Node Attributes
      NULL,
      pm_lpass_proc_client_dev_deps_rail_cx,                      // Node Dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_rail_cx),      // deps count & Deps Node Dependency count
      PM_NPA_PLUGIN_TYPE_MAX                                      // Type of NPA plugin to use
   },
   {
      PMIC_NPA_GROUP_ID_RAIL_MX,                                  // Resource Name
      PMIC_NPA_MODE_ID_CORE_RAIL_MAX - 1,                         // Maximum value
      NPA_RESOURCE_DEFAULT,                                       // Resource Attributes
      (void*) pm_pam_rail_mx_rails_info,                          // Resource User Data
      PMIC_NPA_CLIENT_NODE_RAIL_MX,                               // Node Name
      NPA_NODE_DEFAULT,                                           // Node Attributes
      NULL,
      pm_lpass_proc_client_dev_deps_rail_mx,                      // Node Dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_rail_mx),      // deps count & Deps Node Dependency count
      PM_NPA_PLUGIN_TYPE_MAX                                      // Type of NPA plugin to use
   },
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDD,                               // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1,                            // Maximum value
      NPA_RESOURCE_SINGLE_CLIENT,                                 // Resource Attributes
      (void*) pm_pam_sensor_vdd_rails_info,                       // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDD,                            // Node Name
      NPA_NODE_DEFAULT,                                           // Node Attributes
      NULL,
      pm_lpass_proc_client_dev_deps_sensor_vdd,                   // Node Dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_sensor_vdd),   // deps count & Deps Node Dependency count
      PM_NPA_PLUGIN_TYPE_IDENTITY                                 // Use Identity here.
   },
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDDIO,                             // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1,                            // Maximum value
      NPA_RESOURCE_SINGLE_CLIENT,                                 // Resource Attributes
      (void*) pm_pam_sensor_vddio_rails_info,                     // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO,                          // Node Name
      NPA_NODE_DEFAULT,                                           // Node Attributes
      NULL,
      pm_lpass_proc_client_dev_deps_sensor_vddio,                 // Node Dependencies
      NPA_ARRAY_SIZE(pm_lpass_proc_client_dev_deps_sensor_vddio), // deps count & Deps Node Dependency count
      PM_NPA_PLUGIN_TYPE_IDENTITY                                 // Use Identity here.
   },
};

uint32 num_of_pm_lpass_nodes[] = { NPA_ARRAY_SIZE(pm_npa_lpass_pam_node_rsrcs) };



static pm_npa_remote_name_type
pmic_npa_smps_remote_resources [] = 
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, smps, 8), "smpa\x08\x00\x00\x00" },
};

pm_npa_remote_resource_type
pmic_npa_remote_smps [1] =
{
   {
   pmic_npa_smps_remote_resources,
   1
   }
};

static pm_npa_remote_name_type
pmic_npa_ldo_remote_resources [] = 
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 15), "ldoa\x0F\x00\x00\x00" },
};

pm_npa_remote_resource_type
pmic_npa_remote_ldo [1] =
{
   {
   pmic_npa_ldo_remote_resources,
   1
   }
};

static pm_npa_remote_name_type
pmic_npa_vs_remote_resources [] = 
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, vs, 2), "vsa\x00\x02\x00\x00\x00" },
};

pm_npa_remote_resource_type
pmic_npa_remote_vs [1] =
{
   {
   pmic_npa_vs_remote_resources,
   1
   }
};



static char *pmic_publish_resources[] =
{
   PMIC_NPA_GROUP_ID_SENSOR_VDD,
   PMIC_NPA_GROUP_ID_SENSOR_VDDIO
};

pm_npa_resource_publish_type pmic_npa_pub_type = 
{
   SENSOR_PD,
   pmic_publish_resources,
   2
};

