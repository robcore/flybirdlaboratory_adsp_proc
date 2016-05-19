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

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntKernel.c#2 $

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
extern uGPIOIntKernelCntrlType uGPIOIntKernelData;

/*------------------------------------------------------------------------------
 GPIOInt Macro Declarations.
------------------------------------------------------------------------------*/ 
#define UGPIOINT_PRIORITY 4

#define VALID_UGPIO(x) ((x) < MAX_NUMBER_OF_GPIOS)

/* This macro is used to get the gpio register address */
#define UGPIOINT_GET_ADDRESS(base,nGPIO) (base + 0x10* (nGPIO))

/*------------------------------------------------------------------------------
 GPIOInt Function Declarations.
------------------------------------------------------------------------------*/ 
static void uGPIOInt_ConfigureMPMInterrupt(uint32 gpio,uGPIOIntTriggerType trigger);

/*==========================================================================

   FUNCTION      uGPIOInt_Init

   DESCRIPTION   See uGPIOIntKernel.h

==========================================================================*/
int32 uGPIOInt_Init(uint32 summary_id)
{
  uint32 index;
 
  index = 0;

  /*
   * Initialize the uGPIO state table.
   */
  qurt_mutex_init(&uGPIOIntKernelData.uGPIOIntKernelLock);
  for(index =0;index < MAX_NUMBER_OF_GPIOS; index++)
  {
    uGPIOIntKernelData.state[index].qurt_intr_id = UGPIOINT_NONE;
    uGPIOIntKernelData.state[index].MPMId = UGPIOINT_NONE;  
  }

  uGPIOIntKernelData.summary_id = summary_id;

  return UGPIOINT_SUCCESS;
     
} /* END uGPIOInt_Init */



/*==========================================================================

   FUNCTION      uGPIOIntKernel_RegisterInterrupt

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

  FUNCTION      uGPIOInt_ConfigureMPMInterrupt

  DESCRIPTION   This is an internal function to configure MPM interrupt.

==========================================================================*/
static void uGPIOInt_ConfigureMPMInterrupt
(
  uint32              gpio,
  uGPIOIntTriggerType trigger
)
{
  mpmint_processor_type    mpm_proc;
  mpmint_detect_type       mao_int_detect;
  mpmint_polarity_type     mao_int_polarity;
  
  mpm_proc = MPMINT_MODEM;
  if (uGPIOIntKernelData.state[gpio].MPMId != UGPIOINT_NONE) 
  {
    /*
     * Determine the MAO interrupt configuration
     */
    switch (trigger)
    {

      case UGPIOINT_TRIGGER_HIGH:
        mao_int_detect = MPMINT_LEVEL_DETECT;
        mao_int_polarity = MPMINT_ACTIVE_HIGH;
        break;

      case UGPIOINT_TRIGGER_LOW:
        mao_int_detect = MPMINT_LEVEL_DETECT;
        mao_int_polarity = MPMINT_ACTIVE_LOW;
        break;

      case UGPIOINT_TRIGGER_RISING:
        mao_int_detect = MPMINT_EDGE_DETECT;
        mao_int_polarity = MPMINT_ACTIVE_HIGH;
        break;

      case UGPIOINT_TRIGGER_FALLING:
        mao_int_detect = MPMINT_EDGE_DETECT;
        mao_int_polarity = MPMINT_ACTIVE_LOW;
        break;

      default:
        mao_int_detect = MPMINT_LEVEL_DETECT;
        mao_int_polarity = MPMINT_ACTIVE_HIGH;
        break;
    }
  
    /*
     * Inform MAO the GPIO interrupt is enabled
     */
    mpmint_config_gpio_wakeup(gpio, mao_int_detect,mao_int_polarity, mpm_proc);
  }
  return;

} /* END uGPIOInt_ConfigureMPMInterrupt */


/*==========================================================================

  FUNCTION      uGPIOInt_SetMPMTrigger

  DESCRIPTION   See uGPIOIntKernel.h

==========================================================================*/
int32 uGPIOInt_SetMPMTrigger
(
  uint32              gpio,
  uGPIOIntTriggerType trigger
)
{
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  
  if (uGPIOIntKernelData.state[gpio].MPMId != UGPIOINT_NONE) 
  {
    uGPIOInt_ConfigureMPMInterrupt(gpio,trigger);
  }
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 

  return UGPIOINT_SUCCESS;

}/* END uGPIOInt_SetMPMTrigger */



/*==========================================================================

  FUNCTION      uGPIOInt_UnConfigureMPMInterrupt

  DESCRIPTION   This is an internal function to disable MPM interrupt.

==========================================================================*/
void uGPIOInt_UnConfigureMPMInterrupt
(
  uint32 gpio
)
{
  if (uGPIOIntKernelData.state[gpio].MPMId != UGPIOINT_NONE) 
  {
    mpmint_disable_gpio_wakeup(gpio);
  }
  return;

} /* END uGPIOInt_UnConfigureMPMInterrupt */


int32 uGPIOInt_MapMPMInterrupt
(
  
  uint32 gpio,
  uint32 mpm_id
)
{
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  uGPIOIntKernelData.state[gpio].MPMId = mpm_id;
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 

  return UGPIOINT_SUCCESS;

}/* END uGPIOInt_MapMPMInterrupt */

/*===========================================================================

FUNCTION    uGPIOInt_SetGPIOIntConfig

DESCRIPTION
  This api sets the interrupt configuration in the Kernel.

DEPENDENCIES
  None.

RETURN VALUE
  Failure in setting the GPIO interrupt config returns -1 (UGPIOINT_QDI_ERROR)
  Success in setting the GPIO interrupt config returns 0 (UGPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int32 uGPIOInt_SetGPIOIntConfig
(
  uint32 gpio, 
  uGPIOIntTriggerType trigger,
  uint32 qurt_intr_id
)
{
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  uGPIOIntKernelData.state[gpio].qurt_intr_id = qurt_intr_id;
  uGPIOInt_ConfigureMPMInterrupt(gpio, (uGPIOIntTriggerType)trigger);
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return UGPIOINT_SUCCESS;

} /* END  uGPIOInt_SetGPIOIntConfig */


/*===========================================================================

FUNCTION    uGPIOInt_ClearGPIOIntConfig

DESCRIPTION
  This api clears the interrupt configuration in the Kernel GPIOInt DAL

DEPENDENCIES
  None.

RETURN VALUE
  Failure in setting the trigger returns -1 (UGPIOINT_QDI_ERROR)
  Success in setting the interrupt trigger returns 0 (UGPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int32 uGPIOInt_ClearGPIOIntConfig
(
  uint32 gpio
)
{
  
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  uGPIOIntKernelData.state[gpio].qurt_intr_id = UGPIOINT_NONE;
  uGPIOInt_UnConfigureMPMInterrupt(gpio);
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return UGPIOINT_SUCCESS;

} /* END  uGPIOInt_ClearGPIOIntConfig */


/*==========================================================================

  FUNCTION      uGPIOInt_ClearDirectConnectGPIOMapping

  DESCRIPTION   This is an internal function to disable GPIO direct connect
                mapping from the Kernel GPIOInt Dal.

==========================================================================*/
int32 uGPIOInt_SetDirectConnectGPIOMapping
(
  uint32 gpio,
  uint32 qurt_intr_id
)
{
  
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  uGPIOIntKernelData.state[gpio].qurt_intr_id = qurt_intr_id;
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return UGPIOINT_SUCCESS;

} /* END  uGPIOInt_SetDirectConnectGPIOMapping */


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
  
  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntKernelData.uGPIOIntKernelLock);
  uGPIOIntKernelData.state[gpio].qurt_intr_id = UGPIOINT_NONE;
  qurt_mutex_unlock(&uGPIOIntKernelData.uGPIOIntKernelLock); 
  return UGPIOINT_SUCCESS;

} /* END  uGPIOInt_ClearDirectConnectGPIOMapping */

