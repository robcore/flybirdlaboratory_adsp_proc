/*==================================================================================================

FILE: tal_interrupt.c

DESCRIPTION: This module defines the "stock" implementation of the interrupt APIs for the
             Target Abstraction Layer.  This implementation simply forwards requests
             to the DAL interrupt functions.

                              Copyright (c) 2012 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*==================================================================================================

$Header: //components/rel/core.adsp/2.6.1/buses/uart/tal/src/tal_interrupt.c#1 $

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   tal_interrupt_close
   tal_interrupt_done
   tal_interrupt_open
   tal_interrupt_register
   tal_interrupt_trigger
   tal_interrupt_unregister

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/

#if ( defined(_WIN32) && !defined(_WIN32_WCE) )
#include "dal.h"
#else
#include "comdef.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DDIGPIOInt.h"
#include "DDIInterruptController.h"
#endif

#include "tal.h"

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

typedef struct tal_interrupt_context
{
   DALDEVICEID          client_id;       // DALDEVICEID
   DalDeviceHandle      *daldev_intc;    // handle to DAL device for interrupt controller
   DalDeviceHandle      *daldev_gpio;    // handle to DAL device for GPIO controller
} TAL_INTERRUPT_CONTEXT;

/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static uint32             tal_trigger_to_dal_irq_trigger(TAL_INTERRUPT_TRIGGER trigger);
static GPIOIntTriggerType tal_trigger_to_gpio_trigger(TAL_INTERRUPT_TRIGGER trigger);

/*==================================================================================================
                                          LOCAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: tal_trigger_to_dal_irq_trigger

DESCRIPTION:

==================================================================================================*/
static uint32 tal_trigger_to_dal_irq_trigger(TAL_INTERRUPT_TRIGGER trigger)
{
   switch (trigger)
   {
      case TAL_INTERRUPT_TRIGGER_HIGH:    return DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER;
      case TAL_INTERRUPT_TRIGGER_LOW:     return DALINTRCTRL_ENABLE_LEVEL_LOW_TRIGGER;
      case TAL_INTERRUPT_TRIGGER_RISING:  return DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER;
      case TAL_INTERRUPT_TRIGGER_FALLING: return DALINTRCTRL_ENABLE_FALLING_EDGE_TRIGGER;
      default:                            return DALINTRCTRL_ENABLE_DEFAULT_SETTINGS;
   }
}

/*==================================================================================================

FUNCTION: tal_trigger_to_gpio_trigger

DESCRIPTION:

==================================================================================================*/
static GPIOIntTriggerType tal_trigger_to_gpio_trigger(TAL_INTERRUPT_TRIGGER trigger)
{
   switch (trigger)
   {
      case TAL_INTERRUPT_TRIGGER_HIGH:    return GPIOINT_TRIGGER_HIGH;
      case TAL_INTERRUPT_TRIGGER_LOW:     return GPIOINT_TRIGGER_LOW;
      case TAL_INTERRUPT_TRIGGER_RISING:  return GPIOINT_TRIGGER_RISING;
      case TAL_INTERRUPT_TRIGGER_FALLING: return GPIOINT_TRIGGER_FALLING;
      default:                            return GPIOINT_TRIGGER_HIGH;
   }
}
 
/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: tal_interrupt_close

DESCRIPTION:

==================================================================================================*/
void tal_interrupt_close(TAL_INTERRUPT_HANDLE handle)
{
   DalDevice_Close(handle->daldev_intc);
   DAL_DeviceDetach(handle->daldev_intc);
   DalDevice_Close(handle->daldev_gpio);
   DAL_DeviceDetach(handle->daldev_gpio);
   DALSYS_Free(handle);
}

/*==================================================================================================

FUNCTION: tal_interrupt_done

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_interrupt_done(TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id)
{
   DALResult result = DAL_ERROR;

   switch (tal_int_id->type)
   {
      case TAL_INTERRUPT_TYPE_IRQ:
         result = DalInterruptController_InterruptDone(handle->daldev_intc,
                                                       (DALInterruptID)tal_int_id->u.irq_num);
         break;
      case TAL_INTERRUPT_TYPE_GPIO:
         // There is no GPIOInt_DoneInterrupt
         break;
      default:
         break;
   }

   return (result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}

/*==================================================================================================

FUNCTION: tal_interrupt_open

DESCRIPTION:
   Opens and attaches to both the DAL interrupt controller and the GPIO controller

==================================================================================================*/
TAL_RESULT tal_interrupt_open(TAL_INTERRUPT_HANDLE *phandle, uint32 client_id)
{
   TAL_INTERRUPT_CONTEXT *tal_interrupt_ctxt = NULL;
   DalDeviceHandle *interrupt_dal = NULL;
   DalDeviceHandle *gpioint_dal = NULL;
   DALResult result;
   boolean intc_opened = FALSE;

   result = DALSYS_Malloc(sizeof(TAL_INTERRUPT_CONTEXT), (void **)(&tal_interrupt_ctxt));
   if (result != DAL_SUCCESS) 
   { 
      goto error;
   }

   result = DAL_DeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER, &interrupt_dal);
   if (result != DAL_SUCCESS) 
   { 
      goto error;
   }

   result = DalDevice_Open(interrupt_dal, DAL_OPEN_SHARED);
   if (result != DAL_SUCCESS) 
   { 
      goto error;
   }
   intc_opened = TRUE;

   result = DAL_DeviceAttach(DALDEVICEID_GPIOINT, &gpioint_dal);
   if (result != DAL_SUCCESS) 
   { 
      goto error;
   }

   result = DalDevice_Open(gpioint_dal, DAL_OPEN_SHARED);
   if (result != DAL_SUCCESS) 
   { 
      goto error;
   }

   tal_interrupt_ctxt->daldev_intc = interrupt_dal;
   tal_interrupt_ctxt->daldev_gpio = gpioint_dal;
   tal_interrupt_ctxt->client_id   = client_id;
   *phandle = tal_interrupt_ctxt;
   return TAL_SUCCESS;

error:
   if (intc_opened)        { DalDevice_Close(interrupt_dal); }
   if (interrupt_dal)      { DAL_DeviceDetach(interrupt_dal); }
   if (gpioint_dal)        { DAL_DeviceDetach(gpioint_dal); }
   if (tal_interrupt_ctxt) { DALSYS_Free(tal_interrupt_ctxt); }
   *phandle = NULL;
   return TAL_ERROR;
}

/*==================================================================================================

FUNCTION: tal_interrupt_register

DESCRIPTION:
   Registers a tal_interrupt

==================================================================================================*/
TAL_RESULT tal_interrupt_register(TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id,
                                  TAL_INTERRUPT_TRIGGER trigger, TAL_INTERRUPT_ISR isr, 
                                  void *context)
{
   DALResult dal_result = DAL_ERROR;
   uint32 dal_irq_trigger;
   GPIOIntTriggerType gpio_trigger;

   switch (tal_int_id->type)
   {
      case TAL_INTERRUPT_TYPE_IRQ:
         dal_irq_trigger = tal_trigger_to_dal_irq_trigger(trigger);
         dal_result = DalInterruptController_RegisterISR(handle->daldev_intc, 
                                                         (DALInterruptID)tal_int_id->u.irq_num,
                                                         isr, context,
                                                         dal_irq_trigger);
         break;
      case TAL_INTERRUPT_TYPE_GPIO:
         gpio_trigger = tal_trigger_to_gpio_trigger(trigger);
         dal_result = GPIOInt_RegisterIsr(handle->daldev_gpio, 
                                          tal_int_id->u.gpio_num, 
                                          gpio_trigger,
                                          (GPIOINTISR) isr, (GPIOINTISRCtx) context);
         break;
      default:
         break;
   }

   return (dal_result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}

/*==================================================================================================

FUNCTION: tal_interrupt_trigger

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_interrupt_trigger(TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id)
{
   DALResult result = DAL_ERROR;

   switch (tal_int_id->type)
   {
      case TAL_INTERRUPT_TYPE_IRQ:
         result = DalInterruptController_InterruptTrigger(handle->daldev_intc,
                                                          (DALInterruptID)tal_int_id->u.irq_num);
         break;
      case TAL_INTERRUPT_TYPE_GPIO:
         result = GPIOInt_TriggerInterrupt(handle->daldev_gpio, tal_int_id->u.gpio_num);
         break;
      default:
         break;
   }

   return (result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}

/*==================================================================================================

FUNCTION: tal_interrupt_unregister

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_interrupt_unregister(TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id,
                                    TAL_INTERRUPT_ISR isr)
{
   DALResult result = DAL_ERROR;

   switch (tal_int_id->type)
   {
      case TAL_INTERRUPT_TYPE_IRQ:
         result = DalInterruptController_Unregister(handle->daldev_intc,
                                                    (DALInterruptID)tal_int_id->u.irq_num);
         break;
      case TAL_INTERRUPT_TYPE_GPIO:
         result = GPIOInt_DeregisterIsr(handle->daldev_gpio, tal_int_id->u.gpio_num,
                                        (GPIOINTISR)isr);
         break;
      default:
         break;
   }

   return (result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}
