#ifndef PM_NPA_PAM_TYPES_H
#define PM_NPA_PAM_TYPES_H
/*===========================================================================


                  P M    NPA   H E A D E R    F I L E

DESCRIPTION
  This file contains prototype definitions to support interaction
  with the QUALCOMM Power Management ICs.

Copyright (c) 2010 - 2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/npa/inc/pm_npa_pam_types.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/03/10   umr     Created.
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
  void *rail_data; /* Type of client to create */
  pm_npa_resouce_type rail_type;
}pm_npa_pam_client_cfg_type;

/*===========================================================================

                        DEFINITIONS

===========================================================================*/

/*===========================================================================

                        GENERIC FUNCTION PROTOTYPES

===========================================================================*/

#endif /* PM_NPA_PAM_TYPES_H */

