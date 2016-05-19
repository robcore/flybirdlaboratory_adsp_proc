/*=============================================================================

                Qurt_Timer_Sleep.c

GENERAL DESCRIPTION
      This file is to have wrapper to qurt_timer_sleep mapping into ATS timer_sleep api

EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

      Copyright (c) 2009 - 2014
      by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/services/time/src/qurt_timer_sleep.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/05/14   ab      Added file
=============================================================================*/

/*****************************************************************************/
/*                           INCLUDE FILES                                   */
/*****************************************************************************/
#include "timer.h"
#include "qurt.h"

int qurt_timer_sleep( qurt_timer_duration_t duration )
{
   timer_sleep(duration, T_USEC, FALSE);
   return QURT_EOK;
}