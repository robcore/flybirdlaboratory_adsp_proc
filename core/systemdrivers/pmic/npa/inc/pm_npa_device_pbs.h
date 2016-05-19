#ifndef PM_NPA_DEVICE_PBS__H
#define PM_NPA_DEVICE_PBS__H
/*===========================================================================


P M    N P A   L D O   D E V I C E    H E A D E R    F I L E

DESCRIPTION
This file contains prototype definitions npa device layer

Copyright (c) 2012 - 2013 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/npa/inc/pm_npa_device_pbs.h#1 $

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
    // [Disable (default), Enable] — max aggregation (left to right)
    unsigned sw_enable_key; // PM_NPA_KEY_SOFTWARE_ENABLE
    unsigned sw_enable_size; // 4
    unsigned sw_enable_value;

	// Starting Address of PBS sequence
    unsigned pbs_start_address_key; // Address
    unsigned pbs_start_address_size; // 4
    unsigned pbs_start_address_value;
}pm_npa_pbs_kvps;

npa_resource_plugin *pm_npa_get_pbs_kvps_plugin(void);

#endif // PM_NPA_DEVICE_PBS__H

