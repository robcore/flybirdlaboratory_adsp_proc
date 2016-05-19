#ifndef __UGPIOInt_H
#define __UGPIOInt_H
/*===========================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This modules contains enumeration definitions to support the Dal GPIO 
  interrupt controller. The definitions in this module are used internally 
  in the GPIO interrupt controller and are not to be exposed to the clients.

REFERENCES

       Copyright (c) 2014 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/user/uimage/uGPIOIntUser.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

#include "qurt.h"
#include "uGPIOInt.h"
/*------------------------------------------------------------------------------
Declaring uGPIOInt Driver data
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 GPIO interrupt controller constant declarations.
------------------------------------------------------------------------------*/

#define UGPIOIST_TASKNAME_SIZE 16
/*
 * As an Upper limit we keep the maximum number of GPIOs as 200.
 * This number needs to be updated if the GPIO number exceeds 200.
 * Also the number of GPIOs supported in Uimage is 10 is a direct 1 to 1 relation to the number of direct connects currently available in Sensors.
 */
#define MAX_NUMBER_OF_UGPIOS         10
#define MAX_NUMBER_OF_GPIOS         200
#define UGPIOINTF_MPMINT            0x0002
#define UGPIOINTF_WAKEUP            0x0004
#define UGPIOINTF_REGISTERED        0x0008
#define UGPIOINT_IST_STACK_SIZE     2048

/*
 * These are signals to the TASK
 * Esstentially the Task can wait on Interrupt signals from the Kernel and signals from the registration thread.
 */
#define UGPIOINT_TASK_START      0x00008000
#define UGPIOINT_TASK_STOP       0x00010000 
#define UGPIOINT_TASK_INT0       0x00020000 /* Direct connect 0 registration signal to the IST. */
#define UGPIOINT_TASK_INT1       0x00040000 /* Direct connect 1 registration signal to the IST. */
#define UGPIOINT_TASK_INT2       0x00080000 /* Direct connect 2 registration signal to the IST. */
#define UGPIOINT_TASK_INT3       0x00100000 /* Direct connect 3 registration signal to the IST. */
#define UGPIOINT_TASK_INT4       0x00200000 /* Direct connect 4 registration signal to the IST. */
#define UGPIOINT_TASK_INT5       0x00400000 /* Direct connect 5 registration signal to the IST. */
#define UGPIOINT_TASK_INT6       0x00800000 /* Direct connect 6 registration signal to the IST. */
#define UGPIOINT_TASK_INT7       0x01000000 /* Direct connect 7 registration signal to the IST. */
#define UGPIOINT_TASK_INT8       0x02000000 /* Direct connect 8 registration signal to the IST. */
#define UGPIOINT_TASK_INT9       0x04000000 /* Direct connect 9 registration signal to the IST. */


#define UGPIOINT_TASK_INTMASK   0xFFFE0000


 




/* #define SIG_INT_ABORT 0x80000000 */


/*=========================================================================

                           DATA TYPE DEFINITIONS

===========================================================================*/

/*
 * GPIOIntdata_type
 * Structure storing the details for a SUMMARY group interrupt
 */
typedef struct
{
  uGPIOINTISR                    isr;
  uGPIOINTISRCtx                 isr_param;
  qurt_anysignal_t *             pISTSignal;
  uint8                          intr_trigger;
  uint32                         qurt_intr_id;
  uint8                          gpio_intr_flags;
  uint32                         nGPIO;
  uint32                         nInterruptMask;
  uint32                         nIntRegMask;

} uGPIOIntDataType;
 

/*
 * uGPIOIntConfigMapType
 * Structure storing the interrupt data map accross all processors.
 * it matches with the DAL GPIOInt driver.
 * uint32          gpio;         GPIO pin number
 * uint32          interrupt_id; l1 main interrupt line for direct connects.
 * uint32          polarity;     polarity of the interrupt.
 */
typedef struct
{
  uint32                                 gpio;
  uint32                                 DirConnIntId;
  uint32                                 qurt_interrupt_id;
  uint32                                 flags;
} uGPIOIntConfigMapType;

/*
 * GPIOIntCntrlType
 *
 * Container for all local data.
 *
 * initialized: Indicates if the driver has been started or not.  Needed
 *              mostly because some compilers complain about empty structs.
 * table:       Table of registered GPIO_INT handler functions.
 * wakeup_isr:  ISR to invoke when a monitored GPIO interrupt triggers.
 */
typedef struct
{
  /* GPIOInt Dev state can be added by developers here */

  /* Flag to Initialize GPIOInt_Init is called first 
   * before anything else can attach 
   */
  uint8                          uGPIOInt_Init;

  /* interrupt_state Table of registered GPIO_INT handler functions */
  uGPIOIntDataType               state[MAX_NUMBER_OF_UGPIOS];
  uint32                         aGPIOLUT[MAX_NUMBER_OF_GPIOS];
  qurt_thread_t                  nThreadID;
  uint8                          aISTStack[UGPIOINT_IST_STACK_SIZE];
  char                           aISTName[UGPIOIST_TASKNAME_SIZE];
  qurt_anysignal_t               ISTSignal;
  qurt_thread_attr_t             ThreadAttr;
  uint32                         nPriority;
  uint32                         nGPIOIntMask;
  uint32                         nGPIOIntRegistrationMask;
  uint32                         nISTStackSize;
  qurt_mutex_t                   uGPIOIntLock;
  int32                          ugpioint_qdi;
  
  /* Configuration map for direct connect interrupts.*/
  uGPIOIntConfigMapType          *puGPIOIntConfigMap;

  /* 
   * Number of direct connect interrupts.
   */
  uint32                        direct_intr_number;
      
} uGPIOIntCntrlType;


/*=========================================================================

                      INTERNAL FUNCTION DEFINITIONS

===========================================================================*/


/*============================================================================= 
 
  FUNCTION      uGPIOInt_Init

  This is the main driver initialization function that is called in the
  GPIOInt DAL. \n

  DEPENDENCIES  None.
  @return
  UGPIOINT_SUCCESS -- Is returned if the uGPIOInt driver was correctly initialized. \n
  UGPIOINT_ERROR --  Is returned if the uGPIOInt initialization failed. \n
  @dependencies
  None.
 
=============================================================================*/
int32 uGPIOInt_Init
(
  void
);


#endif /*__UGPIOInt_H */
