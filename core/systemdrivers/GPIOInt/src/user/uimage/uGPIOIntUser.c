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

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/user/uimage/uGPIOIntUser.c#2 $

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
#include "uGPIOIntHWIO.h"
#include "uGPIOIntUser.h"
#include "uGPIOIntQDI.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * This is static uGPIOInt state data. It can be accessed for debugging 
 * uGPIO Interrupts to see what is the current registration state of the GPIO.
 */
extern uGPIOIntCntrlType uGPIOIntData;
extern uGPIOIntConfigMapType uGPIOIntConfigMap;

/*------------------------------------------------------------------------------
 GPIOInt Macro Declarations.
------------------------------------------------------------------------------*/ 
#define UGPIOINT_PRIORITY 4

#define VALID_UGPIO(x) ((x) < MAX_NUMBER_OF_GPIOS)
#define VALID_UGPIO_IDX(x) (uGPIOIntData.aGPIOLUT[x] != UGPIOINT_NONE)
#define UGPIOINT_IDX(x) (uGPIOIntData.aGPIOLUT[x])

/* This macro is used to get the gpio register address */
#define UGPIOINT_GET_ADDRESS(base,nGPIO) (base + 0x10* (nGPIO))
#define UGPIOINT_GET_DIR_CONN_ADDRESS(base,nGPIO) (base + 0x4 * (nGPIO))

/* 
 * For each interrupt handler thread a Default IST stack size is declared.
 */
#define GPIOINT_IST_STACK_SIZE  2048

/*------------------------------------------------------------------------------
Following functions are internal functions.
------------------------------------------------------------------------------*/

extern void uGPIOInt_ISTMain(void * ISTParam);
static int32 uGPIOInt_ConfigureIST(void);
static void uGPIOInt_SetDirConnIntrPolarity(uGPIOIntTriggerType  eTrigger,uint32 nGPIO,uint32 DirConnIntrIdx);

/*==========================================================================

  FUNCTION      uGPIOInt_AssignInterruptIndex

  DESCRIPTION   See uGPIOIntUser.h

==========================================================================*/

int32
uGPIOInt_AssignInterruptIndex(uint32 nGPIO)
{
  uint32 index;

  if (uGPIOIntData.aGPIOLUT[nGPIO] == UGPIOINT_NONE) 
  {
    for(index =0;index < MAX_NUMBER_OF_UGPIOS; index++)
    {
      if (uGPIOIntData.state[index].nGPIO == UGPIOINT_NONE) 
      {
        uGPIOIntData.state[index].nGPIO = nGPIO;
        uGPIOIntData.aGPIOLUT[nGPIO] = index;
        break;
      }   
    }
    if (index >= MAX_NUMBER_OF_UGPIOS) 
    {
      return UGPIOINT_ERROR;
    }
    else
    {
      return UGPIOINT_SUCCESS;
    }
  }
  else
  {
    return UGPIOINT_SUCCESS;
  }
 
}

/* ===========================================================================
**  UGPIOInt_SetDirConnInterrupt
**
** ======================================================================== */
void uGPIOInt_SetDirConnIntr
(
  uint32                   nGPIO,
  uint32                   DirConnIntrIdx
)
{
  uint32 nReg,nMask,nVal,nRegBase;
  nMask = HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_BMSK;
  nRegBase = HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(0);

  /* We need to Set the Direct connect CFG register Gpio select bits*/
  nReg = 
    UGPIOINT_GET_DIR_CONN_ADDRESS(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(0),DirConnIntrIdx);
  nVal  = inpdw(nReg);

  /* Clear the Gpio Sel bits first*/
  nVal &= ~(nMask);
  nVal |= ((nGPIO) << HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_SHFT);
    
  outpdw(nReg, nVal);
    
  /* We need to enable the direct connect 
   * interrupt from the Summary CFG register */
  nRegBase = HWIO_TLMM_GPIO_INTR_CFGn_ADDR(0);
  nReg = UGPIOINT_GET_ADDRESS(nRegBase,nGPIO);
  nMask = HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_BMSK;
  nVal  = inpdw(nReg);
  nVal |= nMask;
  outpdw(nReg, nVal);
  
}

/* ===========================================================================
**  UGPIOInt_DisableDirConnIntr
**
** ======================================================================== */
void uGPIOInt_DisableDirConnIntr
(
  uint32    nGPIO,  
  uint32    DirConnIntrIdx
)
{
  uint32 nReg, nMask,nVal,nRegBase;
  nMask = HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_BMSK;
  nRegBase = HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(0);

  /* 
   * We need to clear the Direct connect register Gpio select bits.
   */
  nReg = 
  UGPIOINT_GET_DIR_CONN_ADDRESS(nRegBase,DirConnIntrIdx);
  nVal  = inpdw(nReg);

  /* 
   * Clear the Gpio Sel bits first.
   */
  nVal &= ~(nMask);
  outpdw(nReg, nVal);

  /* 
   * We need to clear the direct connect 
   * interrupt from the Summary register* 
   */
  nRegBase = HWIO_TLMM_GPIO_INTR_CFGn_ADDR(0);
  nReg = 
  UGPIOINT_GET_ADDRESS(nRegBase,nGPIO);
  nMask = HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_BMSK;
  nVal  = inpdw(nReg);
  nVal &= ~(nMask);
  outpdw(nReg, nVal);
}

/* ===========================================================================
**  UGPIOInt_SetDirConnIntrPolarity
**
** ======================================================================== */
static void uGPIOInt_SetDirConnIntrPolarity
(
  uGPIOIntTriggerType   eTrigger,
  uint32                nGPIO,
  uint32                DirConnIntrIdx
)
{
  uint32 nPolarityMask,nVal,nReg;
  

  nPolarityMask = HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_BMSK;
  nReg  = UGPIOINT_GET_DIR_CONN_ADDRESS(
            HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(0),
            DirConnIntrIdx);

  nVal  = inpdw(nReg);
  /*
   * Configure the polarity
   */
  if (eTrigger == UGPIOINT_TRIGGER_HIGH ||
    eTrigger == UGPIOINT_TRIGGER_RISING)
  {
    nVal |= nPolarityMask;
  }
  else
  {
    nVal &= ~nPolarityMask;
  }
  outpdw(nReg, nVal);
 
} /* END UGPIOInt_SetDirConnPolarity */

/*==========================================================================

   FUNCTION      uGPIOInt_SetQURTTriggerConfig

  DESCRIPTION   This function sets the trigger for the interrupt vector
                using the QURT OS apis.

  PARAMETERS    
  uint32 nInterrupt  : The interrupt vector number.
  uint32 nTrigger : The interrupt trigger type.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

==========================================================================*/
static int32 uGPIOInt_SetQURTTriggerConfig
(
  
  uint32 nInterruptVector,
  uGPIOIntTriggerType eTrigger
)
{
  uint32 nDetectType,nPolarity;

  switch (eTrigger)
  {
    case UGPIOINT_TRIGGER_FALLING:
    case UGPIOINT_TRIGGER_RISING:
      nDetectType = 1;
      nPolarity = 0;
      break;
  
    case UGPIOINT_TRIGGER_HIGH:
    case UGPIOINT_TRIGGER_LOW:
      nDetectType = 0;
      nPolarity = 0;
      break;
    default:
       return UGPIOINT_ERROR;    
  }

  /*
   * Change the interrupt trigger only when the interrupt is not registered.
   */
  if (QURT_EOK != qurt_interrupt_set_config(nInterruptVector, nDetectType, nPolarity))
  {
    /* Throw an error. */
    return UGPIOINT_ERROR;
  } 
  return UGPIOINT_SUCCESS;

} /* SetQURTTriggerConfig */


/*==========================================================================

  FUNCTION      uGPIOInt_UnConfigureDirectConnectInterrupt

  DESCRIPTION   This function configures the given GPIO pin to the
                direct connect line on the main interrupt controller

==========================================================================*/
int32 
uGPIOInt_UnConfigureDirectConnectInterrupt
(
  uint32 gpio
) 
{
  /* The index position in the state table is the Direct connect index */
  uGPIOInt_DisableDirConnIntr(gpio, UGPIOINT_IDX(gpio));
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].gpio_intr_flags &= ~UGPIOINTF_REGISTERED;
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].nGPIO = UGPIOINT_NONE; 
  uGPIOIntData.aGPIOLUT[gpio] = UGPIOINT_NONE;
  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_UnConfigureDirectConnectInterrupt */


/*==========================================================================

  FUNCTION      uGPIOInt_ConfigureDirectConnectInterrupt

  DESCRIPTION   This function configures the given GPIO pin to the
                direct connect line on the main interrupt controller

==========================================================================*/
int32 
uGPIOInt_ConfigureDirectConnectInterrupt
(
  uint32 gpio,
  uGPIOIntTriggerType trigger
) 
{
  uGPIOInt_SetDirConnIntr(gpio, UGPIOINT_IDX(gpio));
  uGPIOInt_SetDirConnIntrPolarity(trigger , gpio, UGPIOINT_IDX(gpio));
  uGPIOInt_SetQURTTriggerConfig(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id,trigger);
  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_ConfigureDirectConnectInterrupt */


/*==========================================================================

   FUNCTION      uGPIOInt_Init

   DESCRIPTION   See uGPIOIntUser.h

==========================================================================*/
int32 uGPIOInt_Init(void)
{
  uint32 index;
  uint32 BaseOffset;
  int32 nResult;
  BaseOffset = 0x11;
  
  if(uGPIOIntData.uGPIOInt_Init != 1)
  {
    /* 
     * We get the mapping of all supported direct connect interrupts from DALGPIOInt.                                                                            .
     * This is done at power up.                                                                                             .
     */
    qurt_mutex_init(&uGPIOIntData.uGPIOIntLock);
    uGPIOIntData.puGPIOIntConfigMap = &uGPIOIntConfigMap;
    index = 0;
    uGPIOIntData.direct_intr_number = 0;
    while (uGPIOIntData.puGPIOIntConfigMap[index].qurt_interrupt_id !=0) 
    {
      uGPIOIntData.direct_intr_number ++;
      index ++;
    }
    if (uGPIOIntData.direct_intr_number < MAX_NUMBER_OF_UGPIOS) 
    {
      /*
       * The number of supported UGPIO Interrupts should never exceed
       * the number of Direct Connect GPIO interrupts available.
       */
      return UGPIOINT_ERROR;
    }


    /*
     * Initialize the uGPIO state table.
     * The interrupt configuration is fixed for the 10 configurations possible in hw for 10 direct connects.
     */
    for(index =0;index < uGPIOIntData.direct_intr_number; index++)
    {
      uGPIOIntData.state[index].qurt_intr_id = uGPIOIntData.puGPIOIntConfigMap[index].qurt_interrupt_id;
      uGPIOIntData.state[index].nInterruptMask = (1<< index);
      uGPIOIntData.nGPIOIntMask |= uGPIOIntData.state[index].nInterruptMask;
      uGPIOIntData.state[index].nGPIO = UGPIOINT_NONE;  
      uGPIOIntData.state[index].nIntRegMask = 1<< (index + BaseOffset);
    }

    /*
     * Initialize the uGPIO LUT table. this the full size of 200 GPIOs
     */
    for(index =0;index < MAX_NUMBER_OF_GPIOS; index++)
    {
      uGPIOIntData.aGPIOLUT[index] = UGPIOINT_NONE;  
    }

    uGPIOIntData.nThreadID = 0;
    uGPIOIntData.nGPIOIntRegistrationMask = UGPIOINT_TASK_INTMASK;

    /*
     * Spawn the IST here in init so it can wait for registration commands when the client registers.
     */
    nResult =  uGPIOInt_ConfigureIST();
    uGPIOIntData.ugpioint_qdi = qurt_qdi_open(uGPIOIntQdiName);

    if (uGPIOIntData.ugpioint_qdi < 0)
    {
      nResult = UGPIOINT_ERROR;
    }

    if (nResult == UGPIOINT_SUCCESS) 
    {
      uGPIOIntData.uGPIOInt_Init = 1;
    }
    return nResult;
  }

  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_Init */


/*===========================================================================

  FUNCTION      uGPIOInt_ConfigureIST

  DESCRIPTION   This function spawns a single IST thread for handling
                each GPIO interrupt.

  PARAMETERS
  Parameters : None. 

  DEPENDENCIES  None.

  RETURN VALUE  DALResult
  UGPIOINT_SUCCESS : If the IST was spawned successfully.
  UGPIOINT_ERROR : If the IST Spawning encountered an error.

  SIDE EFFECTS  None.


==========================================================================*/
static int32 uGPIOInt_ConfigureIST(void)
{
  int nResult;
  unsigned int StackSize;
  unsigned char * StackAddr;
 
  nResult = 0;

  /*
   * Set the IST name to UGPIOIST
   */
  snprintf(uGPIOIntData.aISTName, 
          (sizeof(unsigned char)*UGPIOIST_TASKNAME_SIZE), "UGPIOIST");

  /*
   *  Initialize any thread attribute objects needed by the interrupt service thread.
   */
  qurt_thread_attr_init (&uGPIOIntData.ThreadAttr);

  /*
   *  Initialize any thread attribute and signal objects needed by
   *  the interrupt service thread.
   */
  qurt_anysignal_init(&uGPIOIntData.ISTSignal);

  /*
   * 64 bit alignment of the stack ptr.
   */
  StackAddr = (unsigned char *)
              (((unsigned long)uGPIOIntData.aISTStack -1) & (~0x7)) + 0x8;

  StackSize = (unsigned int)( UGPIOINT_IST_STACK_SIZE - 
              ((unsigned long)StackAddr - 
              (unsigned long)uGPIOIntData.aISTStack) );

  /* 
   * To ensure that the entire stack (start to end) is 64-bit aligned
   * so the last odd bytes are dropped off.
   */
  StackSize &= ~(0x7);

  
  qurt_thread_attr_set_stack_size(&uGPIOIntData.ThreadAttr, 
                                  StackSize);
  qurt_thread_attr_set_stack_addr (&uGPIOIntData.ThreadAttr, 
                                   (void *)StackAddr);
  qurt_thread_attr_set_priority (&uGPIOIntData.ThreadAttr, 
                                (unsigned short)UGPIOINT_PRIORITY);

  qurt_thread_attr_set_tcb_partition(&uGPIOIntData.ThreadAttr,1); // This task should reside in TCM Memory for UGPIOInt Delivery.

  qurt_thread_attr_set_name(&uGPIOIntData.ThreadAttr, 
                            uGPIOIntData.aISTName);
   
  nResult = qurt_thread_create((qurt_thread_t *)&uGPIOIntData.nThreadID, 
                               &uGPIOIntData.ThreadAttr,
                               uGPIOInt_ISTMain,NULL);
   
  if (nResult == QURT_EFATAL) 
  {
    return UGPIOINT_ERROR;
  }

  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_ConfigureIST */


/*==========================================================================

   FUNCTION      uGPIOInt_RegisterInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_RegisterInterrupt( uint32 gpio,uGPIOIntTriggerType trigger,
                            uGPIOINTISR isr,uGPIOINTISRCtx param, uint32 nFlags)
{
  int nQDIResult;

  if (!VALID_UGPIO(gpio))
  {
    return UGPIOINT_ERROR;
  }
  if (trigger > UGPIOINT_TRIGGER_FALLING)
  {
    return UGPIOINT_ERROR;
  }

  qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);
  
  if (uGPIOInt_AssignInterruptIndex(gpio) == UGPIOINT_ERROR) 
  {
    qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 
    return UGPIOINT_ERROR;
  }
  if((uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr != NULL) &&
     (uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr != isr))
  {
    /*
     * Restore interrupts and return an error.
     */
    qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 
    return UGPIOINT_ERROR;
  }
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr = isr;
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr_param = param; 

  /*
   * Update static GPIOInt map with Trigger 
   */ 
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].intr_trigger = (uint8)trigger;
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].gpio_intr_flags |= UGPIOINTF_REGISTERED;

  uGPIOInt_ConfigureDirectConnectInterrupt(gpio,trigger);

  /* 
   * An IST thread is already created.
   * It will only be restarted on a re registration.
   */
  qurt_anysignal_set(&uGPIOIntData.ISTSignal,
                     uGPIOIntData.state[UGPIOINT_IDX(gpio)].nIntRegMask);
  
  nQDIResult = qurt_qdi_handle_invoke(uGPIOIntData.ugpioint_qdi, 
                                      UGPIOINT_QDI_SET_GPIO_CONFIG,
                                      (uint32)gpio,(uint32)trigger,
                                      (uint32)uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id);

  qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 
  if (nQDIResult != UGPIOINT_QDI_SUCCESS)
  {
    return UGPIOINT_ERROR;
  }
  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_RegisterInterrupt */


/*==========================================================================

   FUNCTION      uGPIOInt_DeregisterInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_DeregisterInterrupt(uint32  gpio)
{
  int nStatus;
  int nQDIResult;
  /*
   * if the GPIO is not configured by UGPIO module then we will
   * not have any valid index etc. Hence its better to abandon
   * any invalid accesses from  this point.
   */
  if ((!VALID_UGPIO(gpio))||(!VALID_UGPIO_IDX(gpio)))
  {
    return UGPIOINT_ERROR;
  }

  qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);
  
  /*
   * Clear out the handler and remove the event. Here the direct connect 
   * interrupt handler is just saved for error checking purposes as it is 
   * largely handled by the Main GPIO interrupt controller.
   */
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr = NULL;
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr_param = 0;
  uGPIOIntData.state[UGPIOINT_IDX(gpio)].intr_trigger = 0;
  
  /* 
   * Deregister IST from QURT so it can stop waiting for an interrupt.
   */
  nStatus = qurt_interrupt_deregister(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id); 

  if (QURT_EOK != nStatus) 
  { 
    qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock);
    return UGPIOINT_ERROR;
  } 

  uGPIOInt_UnConfigureDirectConnectInterrupt(gpio);
  nQDIResult = qurt_qdi_handle_invoke(uGPIOIntData.ugpioint_qdi, 
                                      UGPIOINT_QDI_CLEAR_GPIO_CONFIG,
                                     (uint32)gpio);
  /*
   * Restore interrupts
   */
  qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 
  if (nQDIResult != UGPIOINT_QDI_SUCCESS) 
  {
    return UGPIOINT_ERROR;
  }
  else
  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_DeregisterInterrupt */


int32 uGPIOInt_MapMPMInterrupt
(
  uint32 gpio,
  uint32 mpm_id
)
{
  return UGPIOINT_ERROR;

} /* END uGPIOInt_MapMPMInterrupt */


