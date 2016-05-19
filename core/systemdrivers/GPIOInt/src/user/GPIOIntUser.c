/*==============================================================================

FILE:      DalGPIOInt.c

DESCRIPTION
  This modules implements the API to utilize the Dal GPIO interrupt controller.
  This GPIO Interrupt Controller module is strictly used in USER Protection Domain.
  The definitions in this module are implemented internally and should not be 
  exposed for external client usage directly without using the accompanying DDI
  interface file for this module.

REFERENCES

       Copyright (c) 2012 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/user/GPIOIntUser.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "com_dtypes.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "DDITimetick.h"
#include "DDITlmm.h"
#include "busywait.h"
#include "GPIOIntQDI.h"
#include "DALGlbCtxt.h"
#include "GPIOIntUser.h"
#include <atomic_ops.h>
#include "qurt_int.h"
#include "qurt_anysignal.h"
#include "stringl.h"
#include "uGPIOIntUser.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 
/*
 * This is static GPIOInt state data. It can be accessed for debugging 
 * GPIOInterrupts to see what is the current registration state of the GPIO.
 */
static GPIOIntCntrlType GPIOIntData;

#define MEDIAN_GPIOINT_PRIORITY 4

#define VALID_GPIO(x) ((x) < GPIOIntData.gpio_number)

/* 
 * For each interrupt handler thread a Default IST stack size is declared.
 */
#define GPIOINT_IST_STACK_SIZE  2048


#define GPIOINT_USAGE_MODE 0x3
/*------------------------------------------------------------------------------
Following functions are internal MAO related functions that are turned off in 
WM until we have api support.
------------------------------------------------------------------------------*/

static DALResult GPIOInt_ConfigureDynamicIST(GPIOIntDevCtxt * device,uint32 nGPIO, char* pISTName);
static void GPIOInt_ISTMain(void * ISTParam);

/*------------------------------------------------------------------------------
Following functions are for DALDriver specific functionality
------------------------------------------------------------------------------*/
DALResult 
GPIOIntr_DriverInit(GPIOIntDrvCtxt *pCtxt)
{
	return DAL_SUCCESS;
}

DALResult 
GPIOIntr_DriverDeInit(GPIOIntDrvCtxt *pCtxt)
{
	return DAL_SUCCESS;
}

/*------------------------------------------------------------------------------
Following functions are declared in DalDevice Interface. 
------------------------------------------------------------------------------*/

/*==========================================================================

  FUNCTION      GPIOIntr_DeviceInit

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_DeviceInit
(
  GPIOIntClientCtxt *pCtxt
)
{
  GPIOIntDevCtxt* device;
  DALResult result;
  int nQDIResult;

  device = pCtxt->pGPIOIntDevCtxt;
  device->gpioint_cntrl = &GPIOIntData;
  GPIOIntData.pGPIOIntDevCtxt = pCtxt->pGPIOIntDevCtxt;
  result = DAL_SUCCESS;
 
  if(!pCtxt->is_initialized)
  {
  
    /* Each processor has its own internal synchronization object to access 
     * data that it owns */
    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
             &(device->gpioint_synchronization), &(device->GPIOIntSyncObject)))
    {
      DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
      "GPIO Interrupt Controller: Device could not create a sync object");
      return DAL_ERROR;
    }
   
    /*
     * Initialize the GPIOInt Platform Data
     */
    (void)DALSYS_SyncEnter(device->gpioint_synchronization);
    if(DAL_SUCCESS != GPIOIntr_GetTargetData(pCtxt))
    {  
      (void)DALSYS_SyncLeave(device->gpioint_synchronization);
      return DAL_ERROR;
    }

    device->gpioint_qdi = qurt_qdi_open(GPIOIntQdiName);
    if (device->gpioint_qdi < 0)
    {
      result = DAL_ERROR;
    }
    else
    {
      nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_SET_MAX_GPIOS,
                                        device->gpioint_cntrl->gpio_number);
      if (nQDIResult < 0)
      {
        result = DAL_ERROR;
      }
    }
    (void)DALSYS_SyncLeave(device->gpioint_synchronization);
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    result = uGPIOInt_Init();
  }

  if(result == DAL_SUCCESS)
  {
    /*
     * flags indicating that the driver as initialised.
     */
    pCtxt->is_initialized = 1;
    GPIOIntData.pGPIOIntDevCtxt->is_initialized = 1;
  }
  else
  {
    pCtxt->is_initialized = 0;
    GPIOIntData.pGPIOIntDevCtxt->is_initialized = 0;
  }
  return result;

} /* END GPIOIntr_DeviceInit */


/*==========================================================================

  FUNCTION      GPIOIntr_GetTargetData

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_GetTargetData
(
  GPIOIntClientCtxt *pCtxt
)
{
  DALResult result;
  GPIOIntDevCtxt *device;

  /* 
   * structure which holds properties for dal.
   */
  DALSYSPropertyVar system_property_var;  
 
  /* 
   * declare property handle variable.
   */
  DALSYS_PROPERTY_HANDLE_DECLARE(interrupt_property); 

  /* Get the property handle */
  DALSYS_GetDALPropertyHandle(DALDEVICEID_GPIOINT,interrupt_property);

  result = DAL_SUCCESS;
  device = pCtxt->pGPIOIntDevCtxt;
  
  result = DALSYS_GetPropertyValue(interrupt_property,
  "MAX_GPIOS",0,&system_property_var); 
  if(result == DAL_SUCCESS)
  {
    device->gpioint_cntrl->gpio_number = 
        system_property_var.Val.dwVal;
  }
  else
  {
    device->gpioint_cntrl->gpio_number = 0;
    DALSYS_LogEvent(pCtxt->pGPIOIntDevCtxt->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIO Interrupt Controller: Invalid Config Data ");
    return DAL_ERROR;
  }

  result = DALSYS_GetPropertyValue(interrupt_property,
  "UGPIOINT_DRIVER",0,&system_property_var); 
  if(result == DAL_SUCCESS)
  {
    device->gpioint_cntrl->ugpioint_driver = 
        system_property_var.Val.dwVal;
  }
  else
  {
    /*
     * we do not support the ugpioint  driver.
     */
    device->gpioint_cntrl->ugpioint_driver = 0;
  }


  return result;

} /* END GPIOIntr_GetTargetData */


/*==========================================================================

  FUNCTION      GPIOIntr_Save (No implementation perceived as of now.)

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_Save
( 
  GPIOIntClientCtxt * pCtxt
)
{
    return DAL_ERROR;
}

DALResult 
GPIOIntr_DeviceDeInit(GPIOIntClientCtxt *pCtxt)
{
    return DAL_SUCCESS;
}

DALResult 
GPIOIntr_PowerEvent(GPIOIntClientCtxt *pCtxt, DalPowerCmd PowerCmd, 
                    DalPowerDomain PowerDomain)
{
    return DAL_SUCCESS;
}

DALResult 
GPIOIntr_Open(GPIOIntClientCtxt *pCtxt, uint32 dwaccessMode )
{
    return DAL_SUCCESS;
}

DALResult 
GPIOIntr_Close(GPIOIntClientCtxt *pCtxt)
{
    return DAL_SUCCESS;
}

DALResult 
GPIOIntr_Info(GPIOIntClientCtxt *pCtxt,DalDeviceInfo *pdeviceInfo, uint32 dwSize)
{
    return DAL_SUCCESS;
}

/*------------------------------------------------------------------------------
Following functions are extended in DalGPIOInt Interface. 
------------------------------------------------------------------------------*/
/*==========================================================================

  FUNCTION      GPIOIntr_SetTrigger

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_SetTrigger
( 
  GPIOIntClientCtxt * pCtxt, 
  uint32  gpio, 
  GPIOIntTriggerType  trigger
) 
{
  GPIOIntDevCtxt *device;
  DALResult nResult;
  int nQDIResult;

  device = pCtxt->pGPIOIntDevCtxt;
  nResult = DAL_SUCCESS;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_SetTrigger : This GPIO is invalid");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      return DAL_ERROR;
    }
  }
  /*
   * get the synchronization object.
   */
  (void)DALSYS_SyncEnter(device->gpioint_synchronization);
   
  nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_SET_TRIGGER,gpio,trigger);

  if (nQDIResult < 0 ) 
  {
    nResult = DAL_ERROR;
  }

  /*
   * Update static GPIOInt map with Trigger 
   */ 
  device->gpioint_cntrl->state[gpio].intr_trigger = trigger;
  (void)DALSYS_SyncLeave(device->gpioint_synchronization);
  return nResult;

} /* END GPIOIntr_SetTrigger */


/*==========================================================================

  FUNCTION      GPIOIntr_RegisterIsr

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_RegisterIsr
(
  GPIOIntClientCtxt * pCtxt, 
  uint32  gpio, 
  GPIOIntTriggerType trigger, 
  GPIOINTISR isr,
  GPIOINTISRCtx param
) 
{
  return GPIOIntr_RegisterIsrEx(pCtxt, gpio, trigger, isr, param,0);
} /* END GPIOIntr_RegisterIsr */


/*==========================================================================

  FUNCTION      GPIOIntr_RegisterInterrupt

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_RegisterIsrEx
(
  GPIOIntClientCtxt * pCtxt, 
  uint32  gpio, 
  GPIOIntTriggerType trigger, 
  GPIOINTISR isr,
  GPIOINTISRCtx param,
  uint32 nFlags
) 
{
  DALResult result;
  GPIOIntDevCtxt *device;
  
  device = pCtxt->pGPIOIntDevCtxt;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_RegisterIsr : This GPIO is not supported");
    return DAL_ERROR;
  }
  if (trigger > GPIOINT_TRIGGER_DUAL_EDGE)
  {
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if ((nFlags & GPIOINT_USAGE_MODE)== GPIOINT_ISLAND_MODE)
    {
      device->gpioint_cntrl->state[gpio].gpio_intr_flags |= GPIOINTF_UGPIOINT_CONFIG;
      return uGPIOInt_RegisterInterrupt( gpio,(uGPIOIntTriggerType) trigger,
                                (uGPIOINTISR) isr,(uGPIOINTISRCtx) param, nFlags);
    }
  }

  (void)DALSYS_SyncEnter(device->gpioint_synchronization);
  if(((device->gpioint_cntrl->state[gpio].isr != NULL) &&
     (device->gpioint_cntrl->state[gpio].isr != isr)) ||
    (device->gpioint_cntrl->state[gpio].event != NULL))
  {
    /*
     * Restore interrupts and return an error.
     */
    (void)DALSYS_SyncLeave(device->gpioint_synchronization);
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_RegisterIsr:This GPIO is already assigned");
    return DAL_ERROR;
  }
  device->gpioint_cntrl->state[gpio].isr = isr;
  device->gpioint_cntrl->state[gpio].isr_param = param; 
   
  /*
   * Update static GPIOInt map with Trigger 
   */ 
  device->gpioint_cntrl->state[gpio].intr_trigger = trigger;
  device->gpioint_cntrl->state[gpio].gpio_intr_flags |= GPIOINTF_REGISTERED;

  if(device->gpioint_cntrl->state[gpio].pISTStack != NULL)
  {
    (void)DALSYS_SyncLeave(device->gpioint_synchronization);
    /* 
     * An IST thread is already created.
     * It will only be restarted on a re registration.
     */
    qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_SET_SIGNAL,gpio,GPIOINT_QDI_TASK_START);

    return DAL_SUCCESS;
  }
  else
  {
    result = GPIOInt_ConfigureDynamicIST(device,gpio,NULL);
  }

  (void)DALSYS_SyncLeave(device->gpioint_synchronization);
  return result;

} /* END GPIOIntr_RegisterInterrupt */


/*==========================================================================

  FUNCTION      GPIOIntr_DeregisterIsr

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_DeregisterIsr
( 
  GPIOIntClientCtxt * pCtxt, 
  uint32  gpio, 
  GPIOINTISR isr
) 
{
  GPIOIntDevCtxt *device;
  
  device = pCtxt->pGPIOIntDevCtxt;

  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_DeregisterIsr : invalid GPIO");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      device->gpioint_cntrl->state[gpio].gpio_intr_flags &= ~GPIOINTF_UGPIOINT_CONFIG;
      uGPIOInt_DeregisterInterrupt( gpio);
      return DAL_SUCCESS;
    }
  }

  /*
   * Disable interrupts by accessing the processor's internal sync variable
   */
  (void)DALSYS_SyncEnter(device->gpioint_synchronization);

  /*
   * Check that the ISR is correct
   */
  if (device->gpioint_cntrl->state[gpio].isr != isr)
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIO Interrupt Controller: : invalid GPIO");
    /*
     * Restore interrupts
     */
    (void)DALSYS_SyncLeave(
    device->gpioint_synchronization);
    return DAL_ERROR;
  }

  /*
   * Clear out the handler and remove the event. Here the direct connect 
   * interrupt handler is just saved for error checking purposes as it is 
   * largely handled by the Main GPIO interrupt controller.
   */
  device->gpioint_cntrl->state[gpio].isr = NULL;
  device->gpioint_cntrl->state[gpio].event = NULL;
  device->gpioint_cntrl->state[gpio].isr_param = 0;
  device->gpioint_cntrl->state[gpio].intr_trigger = 0;
  
  qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_DEREGISTER,gpio);
  device->gpioint_cntrl->state[gpio].gpio_intr_flags &= ~GPIOINTF_REGISTERED;

  /*
   * Restore interrupts
   */
 (void)DALSYS_SyncLeave(device->gpioint_synchronization);

 return DAL_SUCCESS;

} /* END GPIOIntr_DeregisterIsr */


/*==========================================================================

  FUNCTION      GPIOIntr_IsInterruptEnabled

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_IsInterruptEnabled
(
  GPIOIntClientCtxt *pCtxt, 
  uint32  gpio, 
  uint32 *state
) 
{
  int nQDIResult;
  GPIOIntDevCtxt *device;

  device = pCtxt->pGPIOIntDevCtxt;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, 
      DALSYS_LOGEVENT_WARNING, 
      "GPIOIntr_IsInterruptEnabled : invalid GPIO");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      return DAL_ERROR;
    }
  }
  nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, 
                                      GPIOINT_QDI_IS_INTERRUPT_ENABLED,
                                      gpio);

  if(nQDIResult < 0) 
  {
    return DAL_ERROR;
  }
  else
  {
    if (nQDIResult == GPIOINT_QDI_FALSE) 
    {
      *state = 0;
    }
    else
    {
      *state = 1;
    }
  }
 
  return DAL_SUCCESS;

} /* GPIOIntr_IsInterruptEnabled */


/*==========================================================================

  FUNCTION      GPIOIntr_IsInterruptPending

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_IsInterruptPending
( 
  GPIOIntClientCtxt *pCtxt, 
  uint32            gpio, 
  uint32            *state 
) 
{  
  GPIOIntDevCtxt *device;
  int nQDIResult;
  device = pCtxt->pGPIOIntDevCtxt;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_IsInterruptPending : invalid GPIO");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      return uGPIOInt_IsInterruptPending(gpio, state); 
    }
  }
  nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, 
                                      GPIOINT_QDI_IS_INTERRUPT_PENDING,
                                      gpio);

  if(nQDIResult < 0) 
  {
    return DAL_ERROR;
  }
  else
  {
    if (nQDIResult == GPIOINT_QDI_FALSE) 
    {
      *state = 0;
    }
    else
    {
      *state = 1;
    }
  }
 
  return DAL_SUCCESS;
 
} /* END GPIOIntr_IsInterruptPending */


/*==========================================================================

  FUNCTION      GPIOIntr_IsInterruptSet

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_IsInterruptSet
( 
  GPIOIntClientCtxt *pCtxt, 
  uint32            gpio, 
  uint32            *state 
) 
{  
  int nQDIResult;
  GPIOIntDevCtxt *device;

  device = pCtxt->pGPIOIntDevCtxt;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_IsInterruptPending : invalid GPIO");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      return DAL_ERROR;
    } 
  }
  nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, 
                                      GPIOINT_QDI_IS_INTERRUPT_SET,
                                      gpio);
 
  if(nQDIResult < 0) 
  {
    return DAL_ERROR;
  }
  else
  {
    if (nQDIResult == GPIOINT_QDI_FALSE) 
    {
      *state = 0;
    }
    else
    {
      *state = 1;
    }
  }
 
  return DAL_SUCCESS;

} /* END GPIOIntr_IsInterruptSet */

/*==========================================================================

  FUNCTION      GPIOIntr_LogEvent

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

void 
GPIOIntr_LogEvent
(
  GPIOIntDevCtxt *device,
  uint32 gpio
)
{
  #ifdef GPIOINT_USERPDLOG
  uint32 index;
  GPIOIntCntrlType *gpioint_cntrl = device->gpioint_cntrl;
  
  DALSYS_SyncEnter(device->gpioint_synchronization); 
  index = gpioint_cntrl->log.index;
  gpioint_cntrl->log.entries[index].gpio = gpio;
  //DalTimetick_Get(device->timetick_handle, &gpioint_cntrl->log.entries[index].timestamp);

  gpioint_cntrl->state[gpio].last =
  gpioint_cntrl->log.entries[index].timestamp;
  gpioint_cntrl->state[gpio].cnt++;

  if (++gpioint_cntrl->log.index >= MAX_INTERRUPT_LOG_ENTRIES)
  {
    gpioint_cntrl->log.index = 0;
  }
  (void)DALSYS_SyncLeave(device->gpioint_synchronization);
  #endif
} /* END GPIOIntr_log_event */


/*==========================================================================

  FUNCTION      GPIOIntr_DefaultIsr

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

void 
GPIOIntr_DefaultIsr
(
  GPIOIntDevCtxt *device,
  uint32 gpio
)
{
  DALSYS_SyncEnter(device->gpioint_synchronization); 
  device->gpioint_cntrl->state[gpio].unhandled++ ;
  qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_DEREGISTER,gpio);
  (void)DALSYS_SyncLeave(device->gpioint_synchronization);

} /* END GPIOIntdefault_isr */


/*==========================================================================

  FUNCTION      GPIOIntr_Restore

  DESCRIPTION   See GPIOInt.h

==========================================================================*/
DALResult GPIOIntr_Restore
( 
  GPIOIntClientCtxt * pCtxt
)
{
    return DAL_SUCCESS;
}


/*==========================================================================

  FUNCTION      GPIOIntr_DisableInterrupt

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_DisableInterrupt
( 
  GPIOIntClientCtxt * pCtxt, 
  uint32 gpio
)
{
  return DAL_ERROR;
} /* END GPIOIntr_DisableInterrupt */


/*==========================================================================

  FUNCTION      GPIOIntr_EnableInterrupt

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_EnableInterrupt
(
  GPIOIntClientCtxt * pCtxt, 
  uint32 gpio
)
{
  return DAL_ERROR;

} /* END GPIOIntr_EnableInterrupt */

/*==========================================================================

   FUNCTION      GPIOIntr_ClearInterrupt

   DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_ClearInterrupt
(
  GPIOIntClientCtxt * pCtxt, 
  uint32 gpio
)
{
  return DAL_ERROR;

} /* END GPIOIntr_ClearInterrupt */


/*==========================================================================

   FUNCTION      GPIOIntr_TriggerInterrupt

   DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_TriggerInterrupt
(
  GPIOIntClientCtxt * pCtxt, 
  uint32  gpio
)
{
  int nQDIResult;
  GPIOIntDevCtxt *device;

  device = pCtxt->pGPIOIntDevCtxt;

  /*
   * Validate the given GPIO interrupt
   */
  if (!VALID_GPIO(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_TriggerInterrupt : invalid GPIO");
    return DAL_ERROR;
  }
  if (device->gpioint_cntrl->ugpioint_driver != 0) 
  {
    if (device->gpioint_cntrl->state[gpio].gpio_intr_flags & GPIOINTF_UGPIOINT_CONFIG)
    {
      return uGPIOInt_TriggerInterrupt(gpio);
    }
  }

  nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, 
                                      GPIOINT_QDI_TRIGGER_INTERRUPT,
                                      gpio);
 
  if(nQDIResult < 0) 
  {
    return DAL_ERROR;
  }
  else
  {
    return DAL_SUCCESS;
  }
 
  
                                        
} /* END GPIOIntr_TriggerInterrupt */


/*==========================================================================

   FUNCTION      GPIOInt_Init

   DESCRIPTION   See DDIGPIOInt.h

==========================================================================*/
void GPIOInt_Init(void)
{

  /* 
   * For user PD we do not need this function.The primary reason to have                                                                               .
   * this in Kernel was to allocate the cxo resource node.
   * This needed t be done asap on power up and before mpm interraction.                                                                               .
   */
  return; 

} /* END GPIOInt_Init */


/*===========================================================================

  FUNCTION      GPIOInt_ConfigureDynamicIST

  DESCRIPTION   This function spawns a single IST thread for handling
                each GPIO interrupt.

  PARAMETERS
  GPIOIntDevCtxt *device : Device context of the GPIOInt driver.
  nGPIO : The GPIO pin number.
  char* pISTName : This is a future provision in case clients
               want to name their own ISTs

  DEPENDENCIES  None.

  RETURN VALUE  DALResult
  DAL_SUCCESS : If the IST was spawned successfully.
  DAL_ERROR : If the IST Spawning encountered an error.

  SIDE EFFECTS  None.


==========================================================================*/
static DALResult GPIOInt_ConfigureDynamicIST
(
  GPIOIntDevCtxt *device,
  uint32         nGPIO, 
  char*          pISTName
)
{
  int nResult;
  unsigned int StackSize;
  unsigned char * StackAddr;

  if(DALSYS_Malloc(
  (sizeof(unsigned char))*GPIOINT_IST_STACK_SIZE,
  (void **)&device->gpioint_cntrl->state[nGPIO].pISTStack) == DAL_ERROR)
  {
    return DAL_ERROR;
  }

  /*
   * Get the signal object from QDI GPIOInt driver.
   */
  nResult = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_CREATE_SIGNAL,nGPIO,
                                   &device->gpioint_cntrl->state[nGPIO].pISTSignal);
 
  if(nResult < 0)
  {
    return DAL_ERROR;
  }

  /*
   * Allways initialize malloced data to 0.
   */
  DALSYS_memset(device->gpioint_cntrl->state[nGPIO].pISTStack, 0,
  ((sizeof(unsigned char))* GPIOINT_IST_STACK_SIZE));

  /*
   * Allways initialize malloced data to 0.
   */
  DALSYS_memset(device->gpioint_cntrl->state[nGPIO].aISTName, 0, 
      (sizeof(char))*GPIOIST_TASKNAME_SIZE);

  device->gpioint_cntrl->state[nGPIO].nISTStackSize = GPIOINT_IST_STACK_SIZE;
  /*
   * Set the IST name to GPIOIST<GpioNumber>
   */
  snprintf(device->gpioint_cntrl->state[nGPIO].aISTName, 
          (sizeof(unsigned char)*GPIOIST_TASKNAME_SIZE), "GPIOIST%d",(int)nGPIO);

  if(pISTName !=NULL)
  {
    strlcat((char *)device->gpioint_cntrl->state[nGPIO].aISTName,pISTName,GPIOIST_TASKNAME_SIZE);
  }

  /*
   *  Initialize any thread attribute objects needed by the interrupt service thread.
   */
  qurt_thread_attr_init (&device->gpioint_cntrl->state[nGPIO].ThreadAttr);

  /*
   * 64 bit alignment of the stack ptr.
   */
  StackAddr = (unsigned char *)
              (((unsigned long)device->gpioint_cntrl->state[nGPIO].pISTStack -1) & (~0x7)) + 0x8;

  StackSize = (unsigned int)( device->gpioint_cntrl->state[nGPIO].nISTStackSize - 
              ((unsigned long)StackAddr - 
              (unsigned long)device->gpioint_cntrl->state[nGPIO].pISTStack) );

  /* 
   * To ensure that the entire stack (start to end) is 64-bit aligned
   * so the last odd bytes are dropped off.
   */
  StackSize &= ~(0x7);

  device->gpioint_cntrl->state[nGPIO].nGPIO = nGPIO;
  qurt_thread_attr_set_stack_size(&device->gpioint_cntrl->state[nGPIO].ThreadAttr, 
                                  StackSize);
  qurt_thread_attr_set_stack_addr (&device->gpioint_cntrl->state[nGPIO].ThreadAttr, 
                                   (void *)StackAddr);
  qurt_thread_attr_set_priority (&device->gpioint_cntrl->state[nGPIO].ThreadAttr, 
                                (unsigned short)MEDIAN_GPIOINT_PRIORITY);
  qurt_thread_attr_set_name(&device->gpioint_cntrl->state[nGPIO].ThreadAttr, 
                            device->gpioint_cntrl->state[nGPIO].aISTName);
   
  nResult = qurt_thread_create((qurt_thread_t *)&device->gpioint_cntrl->state[nGPIO].nThreadID, 
                               &device->gpioint_cntrl->state[nGPIO].ThreadAttr,
                               GPIOInt_ISTMain,(void *)&device->gpioint_cntrl->state[nGPIO].nGPIO);
   
  if (nResult == QURT_EFATAL) 
  {
    /*
     * Destroy the signal object from QDI GPIOInt driver.
     */
    (void)qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_DESTROY_SIGNAL,nGPIO);
    device->gpioint_cntrl->state[nGPIO].pISTSignal = NULL;
    DALSYS_Free((void *)device->gpioint_cntrl->state[nGPIO].pISTStack);
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

} /* END GPIOInt_ConfigureDynamicIST */

/*=============================================================================

  FUNCTION      GPIOInt_ISTMain

  DESCRIPTION   This is the main Interrupt service thread function that 
  processes incoming GPIO interrupts from QURT.

  PARAMETERS
  void * ISTParam  this the pointer actual GPIO interrupt number passed in.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.


==========================================================================*/
static void GPIOInt_ISTMain
(
  void * ISTParam
)
{
  GPIOIntDevCtxt *device; 
  int nStatus;
  uint32 gpio;
  int nQDIResult;

  gpio = *((uint32 *)ISTParam);
  device = GPIOIntData.pGPIOIntDevCtxt; 

  device->gpioint_cntrl->state[gpio].nThreadID = qurt_thread_get_id();

  /*
   * Main loop.  Process an interrupt IPC, then wait for another.
   */
  while(1)
  {

   /*
    * check if interrupt registration flag is set and only register if its still set.
    */
    DALSYS_SyncEnter(device->gpioint_synchronization); 
    if(!(device->gpioint_cntrl->state[gpio].gpio_intr_flags  & GPIOINTF_REGISTERED))
    {
      DALSYS_SyncLeave(device->gpioint_synchronization);
      goto WaitForTaskStart;
    }

    /*
     * Register with QURT using the interrupt vector
     */
    nStatus = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_REGISTER,gpio,
                                   device->gpioint_cntrl->state[gpio].intr_trigger,
                                   &device->gpioint_cntrl->state[gpio].pISTSignal);
   DALSYS_SyncLeave(device->gpioint_synchronization);

   if (nStatus < 0)
   {
     DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
      "Interrupt Controller: failed to register the interrupt"); 
   }
   
   while (1)
   {

      nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_INTERRUPT_RECEIVE,gpio);

      if (GPIOINT_QDI_TASK_STOP & nQDIResult)
      {
        /*
         * Clear task stop signal.
         */
        qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_CLEAR_SIGNAL,gpio,GPIOINT_QDI_TASK_STOP);
        break;
      }

      /*
       * If its not a task stop due to deregistration or an error due to qdi
       * we should error fatal if we still do not get the interrupt registration signal.
       */
      if ( !(GPIOINT_QDI_INTERRUPT_SIGNAL & nQDIResult) )
      {
        DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
          "Interrupt Controller: invalid interrupt signal");
        break;
      }

      /*
       * Log the GPIO that fired
       */
      GPIOIntr_LogEvent(device,gpio);
      
      /*
       * Get the client registered ISR and run it.
       */
      if((device->gpioint_cntrl->state[gpio].event == NULL)&&(device->gpioint_cntrl->state[gpio].isr == NULL))
      {
        GPIOIntr_DefaultIsr(device,gpio);
      }
      else if(device->gpioint_cntrl->state[gpio].event)
      {
        
        DALSYS_EventCtrl(device->gpioint_cntrl->state[gpio].event, DALSYS_EVENT_CTRL_TRIGGER);
      }
      else 
      {
        /*
         * Call the registered client callback.
         */
        device->gpioint_cntrl->state[gpio].isr(device->gpioint_cntrl->state[gpio].isr_param);
      }
      
      qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_CLEAR_INTERRUPT,gpio);

      /*
       * Clear signal and reactivate interrupt.
       */
       qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_CLEAR_SIGNAL,gpio,(GPIOINT_QDI_INTERRUPT_SIGNAL | SIG_INT_ABORT | GPIOINT_QDI_TASK_STOP));
      
    }

    WaitForTaskStart:

    nQDIResult = qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_SIGNAL_RECEIVE,gpio);

    /*
     * Wait for the next time this interrupt is registered with QURT.
     */
    if (GPIOINT_QDI_TASK_START & nQDIResult)
    {
      qurt_qdi_handle_invoke(device->gpioint_qdi, GPIOINT_QDI_CLEAR_SIGNAL,gpio,(GPIOINT_QDI_TASK_START | GPIOINT_QDI_INTERRUPT_SIGNAL | SIG_INT_ABORT));
    }  
  }
} /* END GPIOInt_ISTMain */

/*==========================================================================

  FUNCTION      GPIOIntr_MapMPMInterrupts

  DESCRIPTION   See GPIOInt.h

==========================================================================*/

DALResult 
GPIOIntr_MapMPMInterrupt
(
  GPIOIntClientCtxt * pCtxt,
  uint32 gpio, 
  uint32 mpm_interrupt_id
) 
{
  /* GPIOIntDevCtxt *device;
   device = (GPIOIntDevCtxt *)pCtxt->pGPIOIntDevCtxt;

  
  if (!HAL_gpioint_IsSupported(gpio))
  {
    DALSYS_LogEvent(device->DevId, DALSYS_LOGEVENT_WARNING, 
    "GPIOIntr_MapMPMInterrupts: This GPIO is not supported");
     return DAL_ERROR;
  }
  else
  {
    (void)DALSYS_SyncEnter(device->gpioint_synchronization);
    device->gpioint_cntrl->state[gpio].mpm_intr_id = mpm_interrupt_id;                      
    device->gpioint_cntrl->state[gpio].gpio_intr_flags  |= GPIOINTF_MPMINT;     
    if(device->gpioint_cntrl->state[gpio].gpio_intr_flags  & GPIOINTF_REGISTERED)
    {
      #ifdef GPIOINT_USE_MPM
      GPIOIntr_ConfigMPMWakeup(pCtxt,gpio,(GPIOIntProcessorType)device->gpioint_cntrl->processor);
      #ifdef GPIOINT_USE_NPA
      device->gpioint_cntrl->non_mpm_interrupts --;
      GPIOIntr_UpdateNPARequest(device);
      #endif 
      #endif 
    }
    (void)DALSYS_SyncLeave(device->gpioint_synchronization);
  }         */                   
  return DAL_SUCCESS;
} /* END GPIOIntr_MapMPMInterrupts */

