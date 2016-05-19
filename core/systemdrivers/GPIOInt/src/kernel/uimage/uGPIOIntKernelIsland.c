/*==============================================================================

FILE:      uGPIOIntKernel.c

DESCRIPTION
  This modules implements the API to utilize the Micro GPIO interrupt controller for the Kernel.
  This Micro GPIO Interrupt Controller module is strictly used in KERNEL or GUEST OS Protection
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

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntKernelIsland.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include <atomic_ops.h>
#include <qurt.h>
#include "qurt_int.h"
#include "HALhwio.h"
#include "uGPIOIntKernelHWIO.h"
#include "uGPIOInt.h"
#include "uGPIOIntKernel.h"
#include "mpmint.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * This is static uGPIOIntKernel state data. It can be accessed for debugging 
 * uGPIO Interrupts to see what is the current registration state of the GPIO.
 */
uGPIOIntKernelCntrlType uGPIOIntKernelData;

/*------------------------------------------------------------------------------
 GPIOInt Macro Declarations.
------------------------------------------------------------------------------*/ 
#define UGPIOINT_PRIORITY 4

#define VALID_UGPIO(x) ((x) < MAX_NUMBER_OF_GPIOS)

/* This macro is used to get the gpio register address */
#define UGPIOINT_GET_ADDRESS(base,nGPIO) (base + 0x10* (nGPIO))


/*==========================================================================

   FUNCTION      uGPIOInt_IsInterruptPending

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_IsInterruptPending( uint32  gpio, uint32 *state)
{
  int32 nResult;
  int nStatus;

  nResult = UGPIOINT_SUCCESS;
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }

  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  if ( uGPIOIntKernelData.state[gpio].qurt_intr_id != UGPIOINT_NONE) 
  { 
    if (QURT_EOK != qurt_interrupt_status(uGPIOIntKernelData.state[gpio].qurt_intr_id, &nStatus))
    {
      *state = 0;
      nResult = UGPIOINT_ERROR;
    }
    else 
    {
      if(nStatus == 1)
      {
        *state = 1;
      }
      else
      {
        *state = 0;
      }
    }
  }
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return nResult;
  

} /* END uGPIOInt_IsInterruptPending */


/*==========================================================================

   FUNCTION      uGPIOInt_TriggerInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_TriggerInterrupt(uint32 gpio)
{
  uint32 nReg;
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }

  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  if ( uGPIOIntKernelData.state[gpio].qurt_intr_id == 
       uGPIOIntKernelData.summary_id )
  {
    /* 
     * If the GPIO is a summary interrupt we need to just
     * write to the status register to force trigger it
     */
    nReg = UGPIOINT_GET_ADDRESS(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(0),gpio);
    outpdw(nReg,0x1);  
  }
  else if ( uGPIOIntKernelData.state[gpio].qurt_intr_id != UGPIOINT_NONE ) 
  { 
    /*
     * If the GPIO is a dir connect interrupt we need to 
     * trigger the interrupt through qurt_interrupt_raise
     */
    qurt_interrupt_raise((unsigned int) uGPIOIntKernelData.state[gpio].qurt_intr_id);  
  }
  else
  {
    qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock);
    return UGPIOINT_ERROR;
  }

  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_TriggerInterrupt */

