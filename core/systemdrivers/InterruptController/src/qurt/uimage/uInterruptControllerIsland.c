/*==============================================================================

FILE:      uInterruptController.c

DESCRIPTION
  This modules implements the API to utilize the Micro interrupt controller.
  This Micro Interrupt Controller module is strictly used in Kernel Protection
  Domain and in Micro image.The definitions in this module are implemented internally
  and should not be exposed for external client usage directly without using the
  accompanying uInterruptController.h in the core/api/systemdrivers interface file for this module.

REFERENCES

       Copyright (c) 2014 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/InterruptController/src/qurt/uimage/uInterruptControllerIsland.c#1 $

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
#include "uInterruptController.h"
#include "uInterruptControllerInternal.h"



/*------------------------------------------------------------------------------
 uInterrupt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * This is static uInterrupt state data. It can be accessed for debugging 
 * uInterrupts to see what is the current registration state of the uInterrupt.
 */
uIntCntrlType uIntData;

/*------------------------------------------------------------------------------
 uInterrupt Macro Declarations.
------------------------------------------------------------------------------*/ 
#define UINT_PRIORITY 4

#define VALID_UINT(x) ((x) < MAX_NUMBER_OF_INTS)
#define VALID_UINT_IDX(x) (uIntData.auIntLUT[x] != UINT_NONE)
#define UINT_IDX(x) (uIntData.auIntLUT[x])



/*------------------------------------------------------------------------------
Following functions are internal functions.
------------------------------------------------------------------------------*/

void uInterruptController_ISTMain(void * ISTParam);

/*==========================================================================

  FUNCTION      GetInterruptFromSignalMask
 
  DESCRIPTION   This function returns the interrupt to be registered by the IST
  that matches the given signal mask.
  
==========================================================================*/

static uint32 GetInterruptFromSignalMask
(
  uint32 nSignalMask
 
)
{
  uint32 nIdx;
  for (nIdx = 0;nIdx < MAX_NUMBER_OF_UINTS ; nIdx ++) 
  {
    if (uIntData.state[nIdx].nIntRegMask & nSignalMask) 
    {
      qurt_anysignal_clear(&uIntData.ISTSignal,uIntData.state[nIdx].nIntRegMask);
      return uIntData.state[nIdx].qurt_intr_id;
    }
  }
  return UINT_NONE;
} /* END GetInterruptFromSignalMask */


/*=============================================================================

  FUNCTION      uInterruptController_ISTMain

  DESCRIPTION   This is the main Micro Interrupt service thread function that 
  processes incoming L2VIC interrupts from QURT.

  PARAMETERS
  void * ISTParam  this parameter for now is ignored.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.


==========================================================================*/
void uInterruptController_ISTMain
(
  void * ISTParam
)
{
  int                            nStatus;
  uint32                         nIdx;
  uint32                         nInterruptID;
  uIRQ                           ClientIsr;
  uIRQCtx                        ClientIsrParam;
  unsigned int                   nSignalValue;
  
  nInterruptID = UINT_NONE;
  uIntData.nThreadID = qurt_thread_get_id();

  /*
   * Main loop.  Process an interrupt IPC, then wait for another.
   */
  while(1)
  {

    while (1)
    {
      unsigned int nSignalValue;
      
      nSignalValue = qurt_anysignal_wait( &uIntData.ISTSignal, 
                                          uIntData.nIntRegistrationMask | uIntData.nIntMask | SIG_INT_ABORT | UINT_TASK_STOP);
      
      if (SIG_INT_ABORT & nSignalValue)
      {
        /*
         * Clear task stop signal.
         */
        qurt_anysignal_clear(&uIntData.ISTSignal,SIG_INT_ABORT);
        break;
      }
      if (UINT_TASK_STOP & nSignalValue)
      {
        /*
         * Clear task stop signal.
         */
        qurt_anysignal_clear(&uIntData.ISTSignal,UINT_TASK_STOP);
        break;
      }
      qurt_mutex_lock(&uIntData.uIntLock);
      if (nSignalValue & uIntData.nIntRegistrationMask)
      {
        /*
         * we get the QURT Interrupt and clear the interrupt registration mask that was set.
         */
        nInterruptID = GetInterruptFromSignalMask(nSignalValue & uIntData.nIntRegistrationMask);
        if (nInterruptID == UINT_NONE) 
        {
          // Ideally throw an error here .
          qurt_mutex_unlock(&uIntData.uIntLock);
          continue;
        }
         /* 
          * Register with QURT using the interrupt vector
          */
        nStatus = qurt_interrupt_register(nInterruptID,&uIntData.ISTSignal,
                                    uIntData.state[UINT_IDX(nInterruptID)].nInterruptMask);

        qurt_mutex_unlock(&uIntData.uIntLock); 
        if (nStatus != QURT_EOK) 
        {
          /* throw an error  */
          break;
        }
        continue;     
      }
      qurt_mutex_unlock(&uIntData.uIntLock); 
      /*
       * If its not a task stop due to deregistration or an error due to qdi
       * we should error fatal if we still do not get the interrupt registration signal.
       */
      if ( !(uIntData.nIntMask  & nSignalValue) )
      {
        /* Ideally throw an error in Uimage*/
        break;
      }

      qurt_mutex_lock(&uIntData.uIntLock);

      /*
       * find the interrupt that fired.
       */
      for (nIdx=0;nIdx < MAX_NUMBER_OF_UINTS;nIdx++) 
      {
        if (uIntData.state[nIdx].nInterruptMask & nSignalValue) 
        {
          nInterruptID = uIntData.state[nIdx].qurt_intr_id;
          break;
        }
      }
 
      ClientIsr = uIntData.state[UINT_IDX(nInterruptID)].isr;
      ClientIsrParam = uIntData.state[UINT_IDX(nInterruptID)].isr_param;

      qurt_mutex_unlock(&uIntData.uIntLock); 

      if (ClientIsr == NULL) 
      {
        uInterruptController_UnRegister(nInterruptID);
      }
      else 
      {
        ClientIsr(ClientIsrParam);
      }
      
      /*
       * Clear signal and reactivate interrupt.
       */
      qurt_anysignal_clear(&uIntData.ISTSignal,(uIntData.state[UINT_IDX(nInterruptID)].nInterruptMask | SIG_INT_ABORT | UINT_TASK_STOP));
      nStatus = qurt_interrupt_acknowledge(uIntData.state[UINT_IDX(nInterruptID)].qurt_intr_id);
      if (QURT_EOK != nStatus)
      {
        /* Ideally throw an error*/
        break;
      }
    }

    nSignalValue = qurt_anysignal_wait(&uIntData.ISTSignal,
                                     (UINT_TASK_START | SIG_INT_ABORT | UINT_TASK_STOP));
    /*
     * Wait for the next time this interrupt is registered with QURT.
     */
    if (UINT_TASK_START & nSignalValue)
    {
      /*
       * Clear signal and reactivate interrupt.
       */
      qurt_anysignal_clear(&uIntData.ISTSignal,(UINT_TASK_START | SIG_INT_ABORT | UINT_TASK_STOP));
    }  
  }
} /* END uInterruptController_ISTMain */

/*==========================================================================

   FUNCTION      uInterruptController_IsInterruptPending

   DESCRIPTION   See uInterruptController.h

==========================================================================*/
int32
uInterruptController_IsInterruptPending( uint32 nInterruptID, uint32 *  state)
{
  int nStatus;
  int32 nResult;
  nResult = UINTERRUPT_SUCCESS;
  if (!VALID_UINT(nInterruptID))
  {
    return UINTERRUPT_ERROR;
  }
  qurt_mutex_lock(&uIntData.uIntLock);
  if (QURT_EOK != qurt_interrupt_status(nInterruptID, &nStatus))
  {
    *state = 0;

    nResult = UINTERRUPT_ERROR;
  }
  else 
  {
    if((nStatus == 1)&&(uIntData.state[UINT_IDX(nInterruptID)].intr_flags & UINTF_REGISTERED))
    {
      *state = 1;
    }
    else
    {
      *state = 0;
    }
  }
 
  qurt_mutex_unlock(&uIntData.uIntLock); 

  return nResult;


} /* END uInterruptController_IsInterruptPending */



/*==========================================================================

   FUNCTION      uInterruptController_TriggerInterrupt

   DESCRIPTION   See uInterruptController.h

==========================================================================*/
int32
uInterruptController_TriggerInterrupt(uint32 nInterruptID)
{
  if (!VALID_UINT(nInterruptID))
  {
    return UINTERRUPT_ERROR;
  }
  qurt_mutex_lock(&uIntData.uIntLock);
  qurt_interrupt_raise((unsigned int) nInterruptID); 
  qurt_mutex_unlock(&uIntData.uIntLock); 

  return UINTERRUPT_SUCCESS;

} /* END uInterruptController_TriggerInterrupt */


