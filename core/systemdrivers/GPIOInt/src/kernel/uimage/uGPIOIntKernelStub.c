/*==============================================================================

FILE:      uGPIOInt.c

DESCRIPTION
  This modules implements the API to utilize the Micro GPIO interrupt controller.
  This Micro GPIO Interrupt Controller module is strictly used in USER Protection
  Domain and in Micro image.The definitions in this module are implemented internally
  and should not be exposed for external client usage directly without using the
  accompanying uGPIOInt.h in the core/api/systemdrivers interface file for this module.

REFERENCES

       Copyright (c) 2014 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntKernelStub.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

// #include "uTimetick.h" so far now not sure about the logging plan.

#include <atomic_ops.h>
#include <qurt.h>
#include "qurt_int.h"
#include "qurt_anysignal.h"
#include "stringl.h"
#include "HALhwio.h"
#include "uGPIOIntKernelHWIO.h"
#include "uGPIOIntKernel.h"



/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*------------------------------------------------------------------------------
 GPIOInt Macro Declarations.
------------------------------------------------------------------------------*/ 

/*------------------------------------------------------------------------------
Following functions are internal functions.
------------------------------------------------------------------------------*/

/*==========================================================================

   FUNCTION      uGPIOInt_Init

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32 uGPIOInt_Init(void)
{

  return UGPIOINT_ERROR;

} /* END uGPIOInt_Init */

/*==========================================================================

   FUNCTION      uGPIOInt_RegisterInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_RegisterInterrupt( uint32 gpio,uGPIOIntTriggerType trigger,
                            uGPIOINTISR isr,uGPIOINTISRCtx param, uint32 nFlags)
{
  
  return UGPIOINT_ERROR;

} /* END uGPIOInt_RegisterInterrupt */


/*==========================================================================

   FUNCTION      uGPIOInt_DeregisterInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_DeregisterInterrupt(uint32  gpio)
{
  return UGPIOINT_ERROR;

} /* END uGPIOInt_DeregisterInterrupt */


/*==========================================================================

   FUNCTION      uGPIOInt_IsInterruptPending

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_IsInterruptPending( uint32  gpio, uint32 *  state)
{

  return UGPIOINT_ERROR;

} /* END uGPIOInt_IsInterruptPending */


/*==========================================================================

   FUNCTION      uGPIOInt_TriggerInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_TriggerInterrupt(uint32 gpio)
{
  return UGPIOINT_ERROR;

} /* END uGPIOInt_TriggerInterrupt */

int32 uGPIOInt_SetGPIOIntConfig
(
  uint32 gpio, 
  uGPIOIntTriggerType trigger,
  uint32 qurt_intr_id
)
{
  return UGPIOINT_ERROR;
}
int32 uGPIOInt_ClearGPIOIntConfig
(
  uint32 gpio
)
{
  return UGPIOINT_ERROR;
}
int32 uGPIOInt_SetMPMTrigger
(
  uint32              gpio,
  uGPIOIntTriggerType trigger
)
{
  return UGPIOINT_ERROR;
}
int32 uGPIOInt_SetDirectConnectGPIOMapping
(
  uint32 gpio,
  uint32 qurt_intr_id
)
{
  return UGPIOINT_ERROR;
}

int32 uGPIOInt_MapMPMInterrupt
(
  
  uint32 gpio,
  uint32 mpm_id
)
{
  return UGPIOINT_ERROR;
}

/*==========================================================================

  FUNCTION      uGPIOInt_ClearDirectConnectGPIOMapping

  DESCRIPTION   This is an internal function to disable GPIO direct connect
                mapping from the Kernel GPIOInt Dal.

==========================================================================*/
int32 uGPIOInt_ClearDirectConnectGPIOMapping
(
  uint32 gpio
)
{
  
  return UGPIOINT_ERROR;

} /* END  uGPIOInt_ClearDirectConnectGPIOMapping */

