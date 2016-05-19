/*==============================================================================

  G P I O   I N T E R R U P T   C O N T R O L L E R  Q D I   W R A P P E R  

DESCRIPTION
  This modules contains the Qurt Driver Invocation (QDI) layer that interfaces
  with the driver in the kernel on behalf of the user clients in the user domain.

REFERENCES

       Copyright (c) 2012 - 2014 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
 
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/GPIOIntQDI.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "DALGlbCtxt.h"
#include "GPIOIntQDI.h"
#include "DDIGPIOInt.h"
#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"
#include "qurt_futex.h"
#include "qurt_atomic_ops.h"
#include "stdlib.h"
#include "err.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Type Declarations.
------------------------------------------------------------------------------*/ 

/* 
 * Any Driver that opens a QDI driver has this structure. 
 */ 
typedef struct{
  qurt_qdi_obj_t       qdiobj;
}GPIOIntQdiOpenerType;

/* 
 * Any Driver that opens a QDI driver has this structure. 
 */ 
typedef struct  
{
  qurt_qdi_obj_t qdiobj;
}GPIOIntQdiDrvType;

/* 
 * The QDI driver sets signals on the User threads using this object.
 */ 
typedef struct
{
  qurt_anysignal_t*    pISTSignal;
  qurt_qdi_obj_t*      pQDIObj;
}GPIOIntQdiStateType;

/* 
 * The QDI driver has one common structure for all user PD clients.
 */ 
typedef struct
{
 GPIOIntQdiStateType   *pState;
 uint32                nGpioNumber;
 DalDeviceHandle *     pGPIOIntHdl;
 uint8                 is_initialized;

}GPIOIntQdiDataType;


static DalDeviceHandle *  pGPIOInt_Hdl = NULL;
static qurt_mutex_t GPIOIntQDILock = {{0}};
static GPIOIntQdiDataType *pGPIOIntQdiData = NULL;

/*------------------------------------------------------------------------------
 GPIOInt Constants.
------------------------------------------------------------------------------*/ 

/*
 * This is the maximum number of GPIOs allowed to be used in the system.
 */
#define GPIO_TOTAL_NUMBER 200

/*
 * This macro does a limit check on the GPIO number passed in.
 */
#define GPIOINTQDI_VALID_GPIO(x) ((x) < (pGPIOIntQdiData->nGpioNumber) )

/*------------------------------------------------------------------------------
 GPIOInt Function Declarations.
------------------------------------------------------------------------------*/ 
static int GPIOIntQDI_Invoke(int hClientHandle,qurt_qdi_obj_t *pobj,
                          int method,qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,qurt_qdi_arg_t a9);

void GPIOIntQDI_Release(qurt_qdi_obj_t *qdiobj);
void GPIOIntQDI_Init(void);

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * The QDI functionality is implemented in a opener object.
 */
const GPIOIntQdiOpenerType GPIOIntQdiOpener = {
  { 
    GPIOIntQDI_Invoke,
    QDI_REFCNT_PERM,
    GPIOIntQDI_Release
  }
};




/*===========================================================================
FUNCTION GPIOIntQDI_Init
 
DESCRIPTION 
  This function is called in RCInit . Its dependent on GPIOInt DAL in Guest OS.
  Only when the Guest OS GPIOInt_Init is called then can this function be called.
  It registers the GPIOInt QDI wrapper with QDI Framework.
===========================================================================*/
void GPIOIntQDI_Init(void)
{

  DALResult nResult;

  nResult = DAL_SUCCESS;
  if (pGPIOIntQdiData == NULL) 
  {
    qurt_mutex_init(&GPIOIntQDILock);
    pGPIOIntQdiData = malloc(sizeof(*pGPIOIntQdiData));
    if (pGPIOIntQdiData != NULL)
    {
    
      pGPIOIntQdiData->pState = malloc((sizeof(GPIOIntQdiStateType)*GPIO_TOTAL_NUMBER));
      if (pGPIOIntQdiData->pState == NULL)
      {
        ERR_FATAL("GPIOIntQDI_Init failed to initialize properly", 0, 0, 0);
      }

      /*
       * Allways initialize malloced data to 0.
       */
      memset(pGPIOIntQdiData->pState, 0, (sizeof(GPIOIntQdiStateType)*GPIO_TOTAL_NUMBER));
    }
    else
    {
      ERR_FATAL("GPIOIntQDI_Init failed to initialize properly", 0, 0, 0);
    }
  
    nResult = DAL_DeviceAttach(DALDEVICEID_GPIOINT, &pGPIOInt_Hdl);
    if(nResult == DAL_SUCCESS)
    {
      pGPIOIntQdiData->pGPIOIntHdl = pGPIOInt_Hdl ;
      if(qurt_qdi_register_devname(GPIOIntQdiName, &GPIOIntQdiOpener) < 0)
      {
        nResult = DAL_ERROR;
      }
    }
    if (nResult == DAL_ERROR) 
    {
      ERR_FATAL("GPIOIntQDI_Init failed to initialize properly", 0, 0, 0);
    }
 
    /*
     * For the initialization the Max GPIO limit is set at the threshold.
     * It will be changed according to platform usage shortly thereafter.
     */
    pGPIOIntQdiData->nGpioNumber = GPIO_TOTAL_NUMBER;
    pGPIOIntQdiData->is_initialized = 1;
  }
  return;

}


/*===========================================================================
FUNCTION GPIOIntQDI_release

DESCRIPTION
  GPIOIntQDI_release
  This releases the qdi object when the user pd driver closes the handle
  to the qdi driver.
===========================================================================*/
void GPIOIntQDI_Release(qurt_qdi_obj_t *qdiobj)
{
  uint32 nIdx;

  /* 
   * Typically this driver is active during the entire duration that the
   * target is on. So we may not want to release anything more than the client handle,
   * but if the Protection domain itself is resetting we want to go and reset all the invalid
   * signal pointers belonging to that particualr domain.
   */
  for (nIdx = 0;nIdx< GPIO_TOTAL_NUMBER; nIdx++ ) 
  {
    if (pGPIOIntQdiData->pState[nIdx].pQDIObj == qdiobj) 
    {
       pGPIOIntQdiData->pState[nIdx].pISTSignal = NULL;
    }
  }

  free(qdiobj);

} /* End GPIOIntQDI_Release */


/*===========================================================================
FUNCTION GPIOIntQDI_open

DESCRIPTION
  Open the specified driver for subsequent operations.
===========================================================================*/
int GPIOIntQDI_Open
(
  int hClientHandle,
  qurt_qdi_obj_t *objptr,
  const char *devname,
  int mode
)
{
  GPIOIntQdiDrvType *pGPIOIntQdiDrv;
  int nResult;
  pGPIOIntQdiDrv = malloc(sizeof(*pGPIOIntQdiDrv));
  if (pGPIOIntQdiDrv == NULL)
  {
    return -1;
  }
  pGPIOIntQdiDrv->qdiobj.invoke = GPIOIntQDI_Invoke;
  pGPIOIntQdiDrv->qdiobj.refcnt = QDI_REFCNT_INIT;
  pGPIOIntQdiDrv->qdiobj.release = GPIOIntQDI_Release;

  nResult = qurt_qdi_handle_create_from_obj_t(hClientHandle,&pGPIOIntQdiDrv->qdiobj);

  if (nResult < 0)
  {
    free(pGPIOIntQdiDrv);
  }

  return nResult;

} /* End GPIOIntQDI_Open */


/*===========================================================================

FUNCTION    GPIOIntQDI_CreateSignal

DESCRIPTION
  This api creates the IST signal for the USER PD gpio interrupt thread.
  The signal that is created for the USER PD GPIO Interrupt thread is
  used by it to wait on for notifications from the QDI driver that a GPIO
  Interrupt has fired.
 
DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_ERROR if there was an error creating the signal.
  GPIOINT_QDI_SUCCESS if the signal was successfully created.
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_CreateSignal
(
  int   hClientHandle,
  int   nGPIO,
  void  *pSignal
)
{
  
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  if (pGPIOIntQdiData->pState[nGPIO].pISTSignal == NULL) 
  {
    pGPIOIntQdiData->pState[nGPIO].pISTSignal = 
      qurt_qdi_user_malloc(hClientHandle,sizeof(qurt_anysignal_t));

    if (pGPIOIntQdiData->pState[nGPIO].pISTSignal == NULL) 
    {
      return GPIOINT_QDI_ERROR;
    }

    /*
     *  Initialize any thread attribute and signal objects needed by
     *  the interrupt service thread.
     */
    qurt_anysignal_init(pGPIOIntQdiData->pState[nGPIO].pISTSignal);

    return qurt_qdi_copy_to_user(hClientHandle, pSignal,   
                                 (void *)&pGPIOIntQdiData->pState[nGPIO].pISTSignal, 
                                 sizeof(qurt_anysignal_t *));
  }
  return GPIOINT_QDI_SUCCESS;

} /* End GPIOIntQDI_CreateSignal */


/*===========================================================================

FUNCTION    GPIOIntQDI_DestroySignal

DESCRIPTION
  This api destroys the IST signal for the USER PD gpio interrupt thread.
  The signal that is created for the USER PD GPIO Interrupt thread is destroyed
  so it can no longer wait on for notifications from the QDI driver that a GPIO
  Interrupt has fired.
 
DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_ERROR if there was an error Destrying the signal.
  GPIOINT_QDI_SUCCESS if the signal was successfully destroyed.
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_DestroySignal
(
  int   hClientHandle,
  int   nGPIO
)
{
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  if (pGPIOIntQdiData->pState[nGPIO].pISTSignal == NULL) 
  {
    /*
     * The signal is already destroyed. Nothing to do.
     */
    return GPIOINT_QDI_SUCCESS;
  }

  (void)qurt_qdi_user_free(hClientHandle,(void *)(pGPIOIntQdiData->pState[nGPIO].pISTSignal));
  pGPIOIntQdiData->pState[nGPIO].pISTSignal = NULL;
  

  return GPIOINT_QDI_SUCCESS;

} /* End GPIOIntQDI_DestroySignal */


/*===========================================================================

FUNCTION    GPIOIntQDI_ClearInterrupt

DESCRIPTION
  This api clears the interrupt on behalf of the USER PD
  Client.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_ERROR if there was an error returned by the GPIO DALdriver.
  GPIOINT_QDI_SUCCESS if the call to the GPIOInt Dal driver was successful.
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_ClearInterrupt
(
  int hClientHandle,
  int nGPIO
)
{
  DALResult nResult;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  nResult = GPIOInt_ClearInterrupt(pGPIOIntQdiData->pGPIOIntHdl, (uint32)nGPIO);
  if (nResult == DAL_ERROR) 
  {
    return GPIOINT_QDI_ERROR;
  }
  else
  {
    return GPIOINT_QDI_SUCCESS;
  }
} /* End GPIOIntQDI_ClearInterrupt */


/*===========================================================================

FUNCTION    GPIOIntQDI_IsInterruptEnabled

DESCRIPTION
  DESCRIPTION
  This api finds out if the interrupt is enabled on behalf of the USER PD
  Client.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_TRUE if the interrupt is enabled.
  GPIOINT_QDI_FALSE if the interrupt is not enabled.
  GPIOINT_QDI_ERROR if there was an error returned by the GPIO DALdriver.
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_IsInterruptEnabled
(
  int hClientHandle,
  int nGPIO
)
{

  DALResult nResult;
  uint32 nState;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  nResult = GPIOInt_IsInterruptEnabled(pGPIOIntQdiData->pGPIOIntHdl, 
                                  (uint32)nGPIO, &nState);
  if (nResult == DAL_ERROR) 
  {
    return GPIOINT_QDI_ERROR;
  }
  if (nState == 1)
  {
    return GPIOINT_QDI_TRUE;
  }
  else
  {
    return GPIOINT_QDI_FALSE;
  }

}/* End GPIOIntQDI_IsInterruptEnabled */


/*===========================================================================

FUNCTION    GPIOIntQDI_SetInterruptTrigger

DESCRIPTION
  This api sets the trigger of the interrupt on behalf of the USER PD Client.

DEPENDENCIES
  None.

RETURN VALUE
  Failure in setting the trigger returns -1 (GPIOINT_QDI_ERROR)
  Success in setting the interrupt trigger returns 0 (GPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_SetInterruptTrigger
(
  int hClientHandle,
  int nGPIO, 
  int nTrigger
)
{
  DALResult nResult;
 
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  
  nResult = GPIOInt_SetTrigger(pGPIOIntQdiData->pGPIOIntHdl, 
                              (uint32)nGPIO, (GPIOIntTriggerType)nTrigger);
  if (nResult == DAL_ERROR) 
  {
    return GPIOINT_QDI_ERROR;
  }
  else
  {
    return GPIOINT_QDI_SUCCESS;
  }
 
} /* End GPIOIntQDI_SetInterruptTrigger */


/*===========================================================================

FUNCTION    GPIOIntQDI_IsInterruptSet

DESCRIPTION
  DESCRIPTION
  This api finds out if the interrupt is set on behalf of the USER PD
  Client.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_TRUE if the interrupt is set.
  GPIOINT_QDI_FALSE if the interrupt is not set.
  GPIOINT_QDI_ERROR if there was an error returned by the GPIO DALdriver.
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_IsInterruptSet
(
  int hClientHandle,
  int nGPIO
)
{
 
  DALResult nResult;
  uint32 nState;
  
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  
  nResult = GPIOInt_IsInterruptSet(pGPIOIntQdiData->pGPIOIntHdl, 
                                  (uint32)nGPIO, &nState);
  if (nResult == DAL_ERROR) 
  {
    return GPIOINT_QDI_ERROR;
  }
  if (nState == 1)
  {
    return GPIOINT_QDI_TRUE;
  }
  else
  {
    return GPIOINT_QDI_FALSE;
  }

} /* End GPIOIntQDI_IsInterruptSet */


/*===========================================================================

FUNCTION    GPIOIntQDI_IsInterruptPending

DESCRIPTION
  This api finds out if the interrupt is pending on behalf of the USER PD
  Client.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_TRUE if the interrupt is pending.
  GPIOINT_QDI_FALSE if the interrupt is not pending.
  GPIOINT_QDI_ERROR if there was an error returned by the GPIO DALdriver.
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_IsInterruptPending
(
  int hClientHandle,
  int nGPIO
)
{
  DALResult nResult;
  uint32 nState;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  nResult = GPIOInt_IsInterruptPending(pGPIOIntQdiData->pGPIOIntHdl, 
                                      (uint32)nGPIO, &nState);

  if (nResult == DAL_ERROR) 
  {
    return GPIOINT_QDI_ERROR;
  }
  if (nState == 1)
  {
    return GPIOINT_QDI_TRUE;
  }
  else
  {
    return GPIOINT_QDI_FALSE;
  }

} /* End GPIOIntQDI_IsInterruptPending */


/*===========================================================================

FUNCTION    GPIOIntQDI_TriggerInterrupt

DESCRIPTION
  This api triggers the specific GPIO interrupt in hardware on behalf
  of the USER PD.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_ERROR if there was an error generating the GPIO interrupt.
  GPIOINT_QDI_SUCCESS if the GPIO interrupt was successfully triggered.
 
SIDE EFFECTS
  None

===========================================================================*/

int GPIOIntQDI_TriggerInterrupt
(  
  int   hClientHandle,
  int   nGPIO
)
{
  DALResult nResult;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  
  /*
   * We only trigger a GPIO interrupt when we have registered for the interrupt.
   */
  if (pGPIOIntQdiData->pState[nGPIO].pISTSignal != NULL) 
  {
    nResult = GPIOInt_TriggerInterrupt(pGPIOIntQdiData->pGPIOIntHdl, (uint32)nGPIO);
    if (nResult == DAL_ERROR) 
    {
      return GPIOINT_QDI_ERROR;
    }
    else
    {
      return GPIOINT_QDI_SUCCESS;
    }
  }
  else
  {
    return GPIOINT_QDI_ERROR;
  }

}/* End GPIOIntQDI_TriggerInterrupt */


/*===========================================================================

FUNCTION    GPIOIntQDI_SetMaxGPIOs

DESCRIPTION
  This api sets the maximum GPIOs that are present on the platform.
  It is used for limit check to avoid driver instability issues.

DEPENDENCIES
  None.

RETURN VALUE
  GPIOINT_QDI_ERROR if there was an error setting the max GPIO limit.
  GPIOINT_QDI_SUCCESS if the GPIOs max limit was successfully set.
 
SIDE EFFECTS
  None

===========================================================================*/

int GPIOIntQDI_SetMaxGPIOs
(  
  int   hClientHandle,
  int   nGPIONum
)
{

  if (nGPIONum > GPIO_TOTAL_NUMBER) 
  {
    return GPIOINT_QDI_ERROR;
  }
  pGPIOIntQdiData->nGpioNumber = nGPIONum;

  return GPIOINT_QDI_SUCCESS;

}/* End GPIOIntQDI_SetMaxGPIOs */


/*===========================================================================

FUNCTION    GPIOIntQDI_ISR

DESCRIPTION
  This the default callback handler for any user PD GPIO Interrupt.
  It serves as a proxy interrupt handler that signals the user PD thread waiting
  on a particular GPIO interrupt.

DEPENDENCIES
  None.

RETURN VALUE
 None.
 
SIDE EFFECTS
  None

===========================================================================*/
void GPIOIntQDI_ISR
(
  uint32 nParam
)
{
  uint32 nGPIO;
  nGPIO = nParam;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return;
  }
  GPIOInt_ClearInterrupt(pGPIOIntQdiData->pGPIOIntHdl, nGPIO);
  GPIOInt_DisableGPIOInterrupt(pGPIOIntQdiData->pGPIOIntHdl, nGPIO);
  

  if (pGPIOIntQdiData->pState[nGPIO].pISTSignal != NULL)
  {
  /* 
   * An IST thread is already created.
   * It will only be restarted on a re registration.
   */
    qurt_anysignal_set(pGPIOIntQdiData->pState[nGPIO].pISTSignal,
                       GPIOINT_QDI_INTERRUPT_SIGNAL);
  }

  return;

} /* End GPIOIntQDI_ISR */


/*===========================================================================

FUNCTION    GPIOIntQDI_RegisterInterrupt

DESCRIPTION
  This api registers the interrupt on behalf of the USER PD Client.

DEPENDENCIES
  None.

RETURN VALUE
  Failure to register return -1 (GPIOINT_QDI_ERROR)
  Success in registering returns 0 (GPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_RegisterInterrupt
(
  int               hClientHandle,
  qurt_qdi_obj_t    *pobj,
  int               nGPIO, 
  int               nTrigger, 
  void*             ClientSignal)
{
  DALResult nResult;

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }

  qurt_mutex_lock(&GPIOIntQDILock);
  GPIOIntQDI_CreateSignal(hClientHandle,nGPIO,ClientSignal);
  
  /* 
   * Register an ISR for the GPIO.
   */
  nResult = GPIOInt_RegisterIsr(pGPIOIntQdiData->pGPIOIntHdl,nGPIO, 
                     (GPIOIntTriggerType)nTrigger, (GPIOINTISR)GPIOIntQDI_ISR, nGPIO);

  pGPIOIntQdiData->pState[nGPIO].pQDIObj = pobj;
  qurt_mutex_unlock(&GPIOIntQDILock); 
  if (nResult == DAL_SUCCESS) 
  {
    return GPIOINT_QDI_SUCCESS;
  }
  else
  {
    return GPIOINT_QDI_ERROR;
  }

} /* End GPIOIntQDI_RegisterInterrupt */


/*===========================================================================

FUNCTION    GPIOIntQDI_DeregisterInterrupt

DESCRIPTION
  This api deregisters the interrupt on behalf of the USER PD Client.

DEPENDENCIES
  None.

RETURN VALUE
  Failure to deregister return -1 (GPIOINT_QDI_ERROR)
  Success in deregistering returns 0 (GPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_DeregisterInterrupt
(
  int               hClientHandle,
  int               nGPIO
)
{
  int nQdiResult;
  
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  nQdiResult = GPIOINT_QDI_SUCCESS;

  qurt_mutex_lock(&GPIOIntQDILock);
  /* 
   * Deregister an ISR for the GPIO Interrupt with the dal.
   */
  if(GPIOInt_DeregisterIsr(pGPIOIntQdiData->pGPIOIntHdl,nGPIO, 
                           (GPIOINTISR)GPIOIntQDI_ISR) != DAL_SUCCESS)
  {
    nQdiResult = GPIOINT_QDI_ERROR;
  }
  if (pGPIOIntQdiData->pState[nGPIO].pISTSignal != NULL) 
  {
    qurt_anysignal_set(pGPIOIntQdiData->pState[nGPIO].pISTSignal,GPIOINT_QDI_TASK_STOP);
  }
  pGPIOIntQdiData->pState[nGPIO].pQDIObj = NULL;
  qurt_mutex_unlock(&GPIOIntQDILock); 
  return nQdiResult;

} /* End GPIOIntQDI_DeregisterInterrupt */


/*===========================================================================

FUNCTION    GPIOIntQDI_InterruptReceive

DESCRIPTION
  This api receives the interrupt on behalf of the USER PD Client thread.
  The User PD GPIO interrupt thread calls this api to wait on the interrupt signaled by
  the GPIOIntQDI_ISR

DEPENDENCIES
  None.

RETURN VALUE
  This returns the following signal Value :
  GPIOINT_QDI_INTERRUPT_SIGNAL
  GPIOINT_QDI_TASK_STOP
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_InterruptReceive
(
  int               hClientHandle,
  int               nGPIO
)
{
  int nSignalValue, bState;
  
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  
  qurt_mutex_lock(&GPIOIntQDILock);
  nSignalValue = qurt_anysignal_get(pGPIOIntQdiData->pState[nGPIO].pISTSignal);
  GPIOInt_IsInterruptRegistered(pGPIOIntQdiData->pGPIOIntHdl,(uint32)nGPIO,(uint32*)&bState);
  if((bState != 1)||(nSignalValue & SIG_INT_ABORT)||(nSignalValue & GPIOINT_QDI_TASK_STOP))
  {
   qurt_mutex_unlock(&GPIOIntQDILock); 
   return GPIOINT_QDI_TASK_STOP;
  }
  GPIOInt_ClearInterrupt(pGPIOIntQdiData->pGPIOIntHdl, (uint32)nGPIO);
  GPIOInt_EnableGPIOInterrupt(pGPIOIntQdiData->pGPIOIntHdl, (uint32)nGPIO);
  qurt_mutex_unlock(&GPIOIntQDILock); 
  nSignalValue = qurt_anysignal_wait(pGPIOIntQdiData->pState[nGPIO].pISTSignal,
                                     (GPIOINT_QDI_INTERRUPT_SIGNAL | SIG_INT_ABORT | GPIOINT_QDI_TASK_STOP));

  return nSignalValue;

} /* End GPIOIntQDI_InterruptReceive */


/*===========================================================================

FUNCTION    GPIOIntQDI_SignalReceive

DESCRIPTION
  This api receives the task start , stop signal and the abort on behalf of
  the USER PD Client thread.

DEPENDENCIES
  None.

RETURN VALUE
  This returns the following signal Value :
  GPIOINT_QDI_TASK_START
  GPIOINT_QDI_TASK_STOP
  SIG_INT_ABORT
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_SignalReceive
(
  int               hClientHandle,
  int               nGPIO
)
{
  int nSignalValue;
  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }

  nSignalValue = qurt_anysignal_wait(pGPIOIntQdiData->pState[nGPIO].pISTSignal,
                                     GPIOINT_QDI_TASK_START | SIG_INT_ABORT | GPIOINT_QDI_TASK_STOP);

  return nSignalValue;

} /* End GPIOIntQDI_SignalReceive */

/*===========================================================================

FUNCTION    GPIOIntQDI_ClearSignal

DESCRIPTION
  This api clears the IST thread signal on behalf of the user PD .

DEPENDENCIES
  None.

RETURN VALUE
  This returns the following signal Value :
  GPIOINT_QDI_SUCCESS if signal was cleared successfully.
  GPIOINT_QDI_ERROR if signal could not be cleared.
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_ClearSignal
(
  int               hClientHandle,
  int               nGPIO,
  int               nSignalMask
)
{

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  qurt_anysignal_clear(pGPIOIntQdiData->pState[nGPIO].pISTSignal,nSignalMask);

  return GPIOINT_QDI_SUCCESS;

} /* End GPIOIntQDI_ClearSignal */



/*===========================================================================

FUNCTION    GPIOIntQDI_SetSignal

DESCRIPTION
 This api sets the IST thread signal on behalf of the user PD .

DEPENDENCIES
  None.

RETURN VALUE
  This returns the following signal Value :
  GPIOINT_QDI_SUCCESS if signal was set successfully.
  GPIOINT_QDI_ERROR if signal could not be set.
 
SIDE EFFECTS
  None

===========================================================================*/
int GPIOIntQDI_SetSignal
(
  int               hClientHandle,
  int               nGPIO,
  int               nSignalMask
)
{

  if (!GPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return GPIOINT_QDI_ERROR;
  }
  qurt_anysignal_set(pGPIOIntQdiData->pState[nGPIO].pISTSignal,nSignalMask);
  
  return GPIOINT_QDI_SUCCESS;

} /* End GPIOIntQDI_SetSignal */


/*===========================================================================
FUNCTION GPIOIntQDI_Invoke

DESCRIPTION : 
  This is the main handler for the QDI driver layer in the kernel. All user
  specified methods are routed by this handler to the specific functionality.
 
===========================================================================*/
static int GPIOIntQDI_Invoke(int hClientHandle,
						  qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9)
{
  switch (method) 
  {
    case QDI_OPEN:
      return GPIOIntQDI_Open(hClientHandle, (void *)pobj, a1.ptr, a2.num);

    case GPIOINT_QDI_REGISTER:
      return GPIOIntQDI_RegisterInterrupt(hClientHandle,pobj,a1.num,a2.num, a3.ptr);

    case GPIOINT_QDI_DEREGISTER:
      return GPIOIntQDI_DeregisterInterrupt(hClientHandle, a1.num);

    case GPIOINT_QDI_INTERRUPT_RECEIVE:
	  return GPIOIntQDI_InterruptReceive(hClientHandle,a1.num);

    case GPIOINT_QDI_SIGNAL_RECEIVE:
	  return GPIOIntQDI_SignalReceive(hClientHandle,a1.num);

    case GPIOINT_QDI_SET_TRIGGER:
	  return GPIOIntQDI_SetInterruptTrigger(hClientHandle,a1.num,a2.num);

    case GPIOINT_QDI_IS_INTERRUPT_SET:
	  return GPIOIntQDI_IsInterruptSet(hClientHandle,a1.num);

    case GPIOINT_QDI_IS_INTERRUPT_PENDING:
	  return GPIOIntQDI_IsInterruptPending(hClientHandle,a1.num);

    case GPIOINT_QDI_IS_INTERRUPT_ENABLED:
	  return GPIOIntQDI_IsInterruptEnabled(hClientHandle,a1.num);

    case GPIOINT_QDI_CLEAR_INTERRUPT:
	  return GPIOIntQDI_ClearInterrupt(hClientHandle,a1.num);

    case GPIOINT_QDI_CREATE_SIGNAL:
      return GPIOIntQDI_CreateSignal(hClientHandle,a1.num,a2.ptr);

    case GPIOINT_QDI_DESTROY_SIGNAL:
      return GPIOIntQDI_DestroySignal(hClientHandle,a1.num);

    case GPIOINT_QDI_TRIGGER_INTERRUPT:
      return GPIOIntQDI_TriggerInterrupt(hClientHandle,a1.num);

    case GPIOINT_QDI_SET_MAX_GPIOS:
      return GPIOIntQDI_SetMaxGPIOs(hClientHandle,a1.num);

    case GPIOINT_QDI_CLEAR_SIGNAL:
      return GPIOIntQDI_ClearSignal(hClientHandle,a1.num,a2.num);

    case GPIOINT_QDI_SET_SIGNAL:
      return GPIOIntQDI_SetSignal(hClientHandle,a1.num,a2.num);

    default:
      return qurt_qdi_method_default(hClientHandle, pobj, method,
                                     a1, a2, a3, a4, a5, a6, a7, a8, a9);	
  }
   return -1;
} /* End GPIOIntQDI_Invoke */

