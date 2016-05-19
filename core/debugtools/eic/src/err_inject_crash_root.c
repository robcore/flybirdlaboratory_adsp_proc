/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      ERR service crash simulator
                
GENERAL DESCRIPTION
  Command handler for injecting various types of crashes for testing

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Diag must be initialized

Copyright (c) 2013 -2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.adsp/2.6.1/debugtools/eic/src/err_inject_crash_root.c#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------

===========================================================================*/

#ifndef ERR_INJECT_CRASH
  #error Required definition is missing, check configuration
#endif //ERR_INJECT_CRASH

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "msg.h"
#include "dog_hal.h"

void err_dog_force_bite(void)
{
    MSG(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Calling HAL_dogForceBite from CORE ROOT PD");
    HAL_dogForceBite();
}
