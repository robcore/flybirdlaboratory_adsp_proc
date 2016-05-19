/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        M A I N   M O D U L E

GENERAL DESCRIPTION
  This module contains the AMSS exception handler

EXTERNALIZED FUNCTIONS
  None

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright(c) 2014 by Qualcomm Technologies, Incorporated. All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/uerr_exception_handler.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/31/14   din     Made some changes to support Error on User PD.
07/24/14   din     Changed Diag Macro to use uImage Diag Macro.
07/02/14   din     Accomodate Qurt argument change to complete ERR_FATAL call flow.
06/13/14   din     Moved uErr task to TCM using qurt apis.
04/01/14   din     Initial verion (pulled code from exception_handler.c)
===========================================================================*/

#include <stdio.h>
#include "erri.h"
#include "msg.h"
#include "qurt_event.h"
#include "qurt.h"
#include "uSleep.h"
#include "dog_hal.h"

/*===========================================================================
FUNCTION uerr_exception_handler

DESCRIPTION
  1. It is suppossed to run in ADSP island low power mode.
  2. Brings system out of island mode when recoverable exception occurs.
  3. Brings system out of island mode when non fatal or user exception occurs 
     and raises non fatal exception to the kernel.

===========================================================================*/
void uerr_exception_handler
(
  /* Unused parameter - required to match rex_task_func_type prototype */
  void *                           ignored    /*lint -esym(715,ignored) */
)
{
  unsigned int     tid, ip, sp, badva, cause;
   
  for (;;)
  {
    /* Register self as uException_Handler. */
    tid = qurt_island_exception_wait(&ip, &sp, &badva, &cause);

    if (-1==tid)
    {
      UMSG_1(MSG_SSID_LEGACY, MSG_LEGACY_ERROR, "Failed to register with qurt_reg_error_handler: tid=%x", tid );
      continue;
    }

    if (USLEEP_SUCCESS != uSleep_exit())
    {
      HAL_dogForceBite();
    }

    if (QURT_EXCEPT_INVALID_INT == cause)
    {
      continue;
    }

    if (QURT_EXCEPT_EXIT == cause )
    {
      qurt_exception_raise_nonfatal( badva );
    }
    else
    {
      qurt_exception_raise_nonfatal( ERR_RAISE_EXCEPTION_ARG(ERR_TYPE_NON_RECOVERABLE_EXCEPTION) );
    }
  } 
} /* end of uerr_exception_handler */



