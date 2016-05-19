#ifndef PM_NPA_DEVICE_NCP__H
#define PM_NPA_DEVICE_NCP__H
/*===========================================================================


P M    N P A   N C P   D E V I C E    H E A D E R    F I L E

DESCRIPTION
This file contains prototype definitions npa device layer

Copyright (c) 2012 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/npa/inc/pm_npa_device_ncp.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/12/12   wra     KVP based device setting initial file 
===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/

#include "pm_npa_device.h"


/*===========================================================================

TYPE DEFINITIONS

===========================================================================*/
typedef struct  
{
    // [Disable, Enable] — max aggregation (left to right)
    unsigned sw_enable_key; // PM_NPA_KEY_SOFTWARE_ENABLE
    unsigned sw_enable_size; // 4
    unsigned sw_enable_value;

    //	- Vote when low [Off, LPM] and high [Off, LPM, NPM]
    unsigned pin_ctrl_enable_key; // PM_NPA_KEY_PIN_CTRL_ENABLE
    unsigned pin_ctrl_enable_size; // 4
    unsigned pin_ctrl_enable_value;

    // [X uV] — max aggregation
    unsigned uv_key; // PM_NPA_KEY_MICRO_VOLT
    unsigned uv_size; // 4
    unsigned uv_value;

    // [xx MHz] — max within a priority group
    // — Allows one execution environments vote to be higher or lower priority relative to another execution environment
    unsigned frequency_key; // PM_NPA_KEY_FREQUENCY
    unsigned frequency_size; // 4
    unsigned frequency_value;

    //Frequency_Reason — Optional	[xx] — Distinct indicators per execution environment
    //    One execution environment will not be allowed to use the indicators of another
    //    - Allows interspersed prioritization between execution environments for
    //    frequency aggregation
    //    — Ex: Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority
    unsigned frequency_reason_key; // PM_NPA_KEY_FREQUENCY_REASON
    unsigned frequency_reason_size; // 4
    unsigned frequency_reason_value;
}pm_npa_ncp_kvps;

npa_resource_plugin *pm_npa_get_ncp_kvps_plugin(void);


#endif // PM_NPA_DEVICE_NCP__H

