#ifndef __UGPIOIntKernel_H
#define __UGPIOIntKernel_H
/*===========================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This modules contains enumeration definitions to support the Kernel uGPIO 
  interrupt controller. The definitions in this module are used internally 
  in the dal GPIO interrupt controller or the QDI interface and are not to be
  exposed to the clients or the user PD uGPIO driver directly . These Apis
  support the maintainance of GPIOInt state across all protection domains.

REFERENCES

       Copyright (c) 2014 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntKernel.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "com_dtypes.h"
#include "qurt.h"
#include "uGPIOInt.h"
/*------------------------------------------------------------------------------
Declaring uGPIOInt Driver data
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 GPIO interrupt controller constant declarations.
------------------------------------------------------------------------------*/


/*
 * As an Upper limit we keep the maximum number of GPIOs as 200.
 * This number needs to be updated if the GPIO number exceeds 200.
 */

#define MAX_NUMBER_OF_GPIOS         200


/*=========================================================================

                           DATA TYPE DEFINITIONS

===========================================================================*/

/*
 * GPIOIntdata_type
 * Structure storing the GPIO interrupt configuration map across all uGPIOInterrupt
 * configuration modules in all Protection domains.
 * it matches with the DAL GPIOInt driver as well.
 * uint32          gpio;         GPIO pin number
 * uint32          MPMId;        Corresponding interrupt id on the always on interrupt domain.  
 * uint32          qurt_interrupt_id; l1 main interrupt line for direct connects.
 */
typedef struct
{
  uint32                                 MPMId;
  uint32                                 qurt_intr_id;
} uGPIOIntKernelDataType;
 

/*
 * GPIOIntCntrlType
 *
 * Container for all local data.
 *
 * initialized: Indicates if the driver has been started or not.  Needed
 *              mostly because some compilers complain about empty structs.
 * table:       Table of registered GPIO_INT mapping data.
 */
typedef struct
{
  /* GPIOInt Dev state can be added by developers here */

  /* Flag to Initialize GPIOInt_Init is called first 
   * before anything else can attach 
   */
  uint8                          uGPIOIntKernel_Init;

  /* Summary Interrupt ID for retriggering interrupts
   */
  uint32                         summary_id;

  /* 
   * Interrupt_state Table of registered GPIO interrupts mapped as either
   * direct connects or sumary type.
   */
  uGPIOIntKernelDataType         state[MAX_NUMBER_OF_GPIOS];
  qurt_mutex_t                   uGPIOIntKernelLock;
        
} uGPIOIntKernelCntrlType;


/*=========================================================================

        FUNCTIONS TO BE USED BY THE QDI LAYER or THE KERNEL DAL.

  FUNCTION      uGPIOInt_SetGPIOIntConfig

  DESCRIPTION   
  This function sets the GPIO interrupt trigger configuration to the mpm interrupt
  driver . It also marks the direct connect line to the main interrupt controller
  to which the GPIO is connected as an interrupt.

  PARAMETERS   
  
  uint32 gpio :                     The GPIO pin whose interrupt state needs to
                                    be cleared.
  uGPIOIntTriggerType trigger : The TLMM trigger configuration of the GPIO interrupt.

  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt trigger is successfully
  communicated to the mpm driver and the GPIO interrupt was mapped to the correct direct line
  to the main interrupt controller.
  UGPIOINT_ERROR : this result is returned when the driver failed to set the interrupt trigger
  to the MPM driver or its configuration was not marked as a direct connect interrupt.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_SetGPIOIntConfig
(
  uint32 gpio, 
  uGPIOIntTriggerType trigger,
  uint32 qurt_intr_id
);

/*=============================================================================

  FUNCTION      uGPIOInt_ClearGPIOIntConfig

  DESCRIPTION   
  This function clears the GPIO interrupt mapping to direct connect line of the
  main interrupt controller and disables the mpm trigger.

  PARAMETERS   
  
  uint32 gpio :                     The GPIO pin whose interrupt state needs to
                                    be cleared.

  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio state is successfully
  cleared.
  UGPIOINT_ERROR : this result is returned when the driver failed to clear
  the GPIO state.

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_ClearGPIOIntConfig
(
  uint32 gpio
);


/*=============================================================================

  FUNCTION      uGPIOInt_SetMPMTrigger

  DESCRIPTION   
  This function sends the GPIO interrupt trigger configuration to the mpm interrupt
  driver .

  PARAMETERS   
  
  uint32 gpio :                     The GPIO pin whose interrupt state needs to
                                    be cleared.
  uGPIOIntTriggerType trigger : The TLMM trigger configuration of the GPIO interrupt.

  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt trigger
  is successfully communicated to the mpm driver.
  UGPIOINT_ERROR : this result is returned when the driver failed to set
  the interrupt trigger.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_SetMPMTrigger
(
  uint32              gpio,
  uGPIOIntTriggerType trigger
);


/*=============================================================================

  FUNCTION      uGPIOInt_SetDirectConnectGPIOMapping

  DESCRIPTION   
  This function is used by the GPIOInt Dal driver to log the direct connect
  interrupts in DDR for Guest OS. This is so that in uimage the micro
  interrupt controller can trigger these interrupts quickly.

  PARAMETERS   
  
  uint32 gpio :         The GPIO pin whose interrupt state needs to be logged.
  uint32 qurt_intr_id : The QURT direct connect line to which the GPIO interrupt
                        is configured to.

  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt mapping
  is successfully communicated to the uGPIOInt driver.
  UGPIOINT_ERROR : this result is returned when the driver failed to set
  the interrupt mapping for uGPIOInt driver.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_SetDirectConnectGPIOMapping
(
  uint32 gpio,
  uint32 qurt_intr_id
);

/*=============================================================================

  FUNCTION      uGPIOInt_ClearDirectConnectGPIOMapping

  DESCRIPTION   
  This function is used by the GPIOInt Dal driver clear the GPIO to main
  direct connect interrupt vector id.

  PARAMETERS   
  
  uint32 gpio :         The GPIO pin whose interrupt state needs to be cleared.
  
  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt mapping
  is successfully cleared from the uGPIOInt driver.
  UGPIOINT_ERROR : this result is returned when the driver failed to clear
  the interrupt mapping for uGPIOInt driver.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_ClearDirectConnectGPIOMapping
(
  uint32 gpio
);

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
  uint32 summary_id
);

#endif /* __UGPIOIntKernel_H */
