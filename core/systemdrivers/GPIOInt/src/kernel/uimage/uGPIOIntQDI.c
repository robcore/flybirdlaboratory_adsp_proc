/*==============================================================================

  G P I O   I N T E R R U P T   C O N T R O L L E R  Q D I   W R A P P E R  

DESCRIPTION
  This modules contains the Qurt Driver Invocation (QDI) layer that interfaces
  with the driver in the kernel on behalf of the user clients in the user domain.

REFERENCES

       Copyright (c) 2012 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
 
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntQDI.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "uGPIOIntQDI.h"
#include "uGPIOInt.h"
#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"
#include "qurt_futex.h"
#include "qurt_atomic_ops.h"
#include "stdlib.h"
#include "err.h"
#include "uGPIOIntKernel.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Type Declarations.
------------------------------------------------------------------------------*/ 

/* 
 * Any Driver that opens a QDI driver has this structure. 
 */ 
typedef struct{
  qurt_qdi_obj_t       qdiobj;
}uGPIOIntQdiOpenerType;

/* 
 * Any Driver that opens a QDI driver has this structure. 
 */ 
typedef struct  
{
  qurt_qdi_obj_t qdiobj;
}uGPIOIntQdiDrvType;

/* 
 * The QDI driver has one common structure for all user PD clients.
 */ 
typedef struct
{

 uint32                nGpioNumber;
 uint8                 is_initialized;

}uGPIOIntQdiDataType;

static qurt_mutex_t uGPIOIntQDILock = {{0}};
static uGPIOIntQdiDataType *puGPIOIntQdiData = NULL;

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
#define UGPIOINTQDI_VALID_GPIO(x) ((x) < (puGPIOIntQdiData->nGpioNumber) )

/*------------------------------------------------------------------------------
 GPIOInt Function Declarations.
------------------------------------------------------------------------------*/ 
static int uGPIOIntQDI_Invoke(int hClientHandle,qurt_qdi_obj_t *pobj,
                          int method,qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,qurt_qdi_arg_t a9);

void uGPIOIntQDI_Release(qurt_qdi_obj_t *qdiobj);
void uGPIOIntQDI_Init(void);

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * The QDI functionality is implemented in a opener object.
 */
const uGPIOIntQdiOpenerType uGPIOIntQdiOpener = {
  { 
    uGPIOIntQDI_Invoke,
    QDI_REFCNT_PERM,
    uGPIOIntQDI_Release
  }
};




/*===========================================================================
FUNCTION uGPIOIntQDI_Init
 
DESCRIPTION 
  This function is called in RCInit . Its dependent on GPIOInt DAL in Guest OS.
  Only when the Guest OS uGPIOInt_Init is called then can this function be called.
  It registers the GPIOInt QDI wrapper with QDI Framework.
===========================================================================*/
void uGPIOIntQDI_Init(void)
{
  if (puGPIOIntQdiData == NULL) 
  {
    qurt_mutex_init(&uGPIOIntQDILock);
    puGPIOIntQdiData = malloc(sizeof(*puGPIOIntQdiData));
   
    if((puGPIOIntQdiData == NULL) ||
       (qurt_qdi_register_devname(uGPIOIntQdiName, &uGPIOIntQdiOpener) < 0))
    {
      ERR_FATAL("uGPIOIntQDI_Init failed to initialize properly", 0, 0, 0);
    }
    
    /*
     * For the initialization the Max GPIO limit is set at the threshold.
     * It will be changed according to platform usage shortly thereafter.
     */
    puGPIOIntQdiData->nGpioNumber = GPIO_TOTAL_NUMBER;
    puGPIOIntQdiData->is_initialized = 1;
  }
  return;

}


/*===========================================================================
FUNCTION uGPIOIntQDI_release

DESCRIPTION
  uGPIOIntQDI_release
  This releases the qdi object when the user pd driver closes the handle
  to the qdi driver.
===========================================================================*/
void uGPIOIntQDI_Release(qurt_qdi_obj_t *qdiobj)
{
  /* 
   * Typically this driver is active during the entire duration that the
   * target is on. So we may not want to release anything more than the client handle.
   */
  puGPIOIntQdiData->nGpioNumber = 0;
  puGPIOIntQdiData->is_initialized = 0;
  free(qdiobj);

} /* End uGPIOIntQDI_Release */


/*===========================================================================
FUNCTION uGPIOIntQDI_open

DESCRIPTION
  Open the specified driver for subsequent operations.
===========================================================================*/
int uGPIOIntQDI_Open
(
  int hClientHandle,
  qurt_qdi_obj_t *objptr,
  const char *devname,
  int mode
)
{
  uGPIOIntQdiDrvType *puGPIOIntQdiDrv;
  int nResult;
  puGPIOIntQdiDrv = malloc(sizeof(*puGPIOIntQdiDrv));
  if (puGPIOIntQdiDrv == NULL)
  {
    return -1;
  }
  puGPIOIntQdiDrv->qdiobj.invoke = uGPIOIntQDI_Invoke;
  puGPIOIntQdiDrv->qdiobj.refcnt = QDI_REFCNT_INIT;
  puGPIOIntQdiDrv->qdiobj.release = uGPIOIntQDI_Release;

  nResult = qurt_qdi_handle_create_from_obj_t(hClientHandle,&puGPIOIntQdiDrv->qdiobj);

  if (nResult < 0)
  {
    free(puGPIOIntQdiDrv);
  }

  return nResult;

} /* End uGPIOIntQDI_Open */


/*===========================================================================

FUNCTION    uGPIOIntQDI_ConfigureMPMInterrupt

DESCRIPTION
  This api is the QDI window into the Kernel function to configure the wakeup
  interrupt on the MPM. 

DEPENDENCIES
  None.

RETURN VALUE
  UGPIOINT_QDI_ERROR if there was an error returned by the uGPIO Kernel driver.
  UGPIOINT_QDI_SUCCESS if the call to the uGPIOInt Kernel driver is a success.
SIDE EFFECTS
  None

===========================================================================*/
int uGPIOIntQDI_ConfigureMPMInterrupt
(
  int hClientHandle,
  int nGPIO,
  int nTrigger
)
{
  if (!UGPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return UGPIOINT_QDI_ERROR;
  }
  return uGPIOInt_SetMPMTrigger(nGPIO,(uGPIOIntTriggerType)nTrigger);
  
} /* End uGPIOIntQDI_ConfigureMPMInterrupt */


/*===========================================================================

FUNCTION    uGPIOIntQDI_UnConfigureMPMInterrupt

DESCRIPTION
  DESCRIPTION
  This api is a way to unconfigure the MPM wakeup.

DEPENDENCIES
  None.

RETURN VALUE
  UGPIOINT_QDI_SUCCESS if the interrupt is disabled as wakeup.
  UGPIOINT_QDI_ERROR if the interrupt is not disabled as wakeup.
 
SIDE EFFECTS
  None

===========================================================================*/
int uGPIOIntQDI_ClearGPIOIntConfig
(
  int hClientHandle,
  int nGPIO
)
{

  int nResult;

  if (!UGPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return UGPIOINT_QDI_ERROR;
  }
  nResult = uGPIOInt_ClearGPIOIntConfig(nGPIO);

  return nResult;

}/* End uGPIOIntQDI_IsInterruptEnabled */


/*===========================================================================

FUNCTION    uGPIOIntQDI_SetGPIOIntConfig

DESCRIPTION
  This api sets the interrupt configuration in the Kernel.
  If the GPIO is a wakeup GPIO it will set up the MPM config.
  If the GPIO is setup as a direct connect interrupt. It will notify the kernel
  the l2vic interrupt vector its connected to.

DEPENDENCIES
  None.

RETURN VALUE
  Failure in setting the GPIO config returns -1 (UGPIOINT_QDI_ERROR)
  Success in setting the GPIO config returns 0 (UGPIOINT_QDI_SUCCESS)
 
SIDE EFFECTS
  None

===========================================================================*/
int uGPIOIntQDI_SetGPIOIntConfig
(
  int hClientHandle,
  int nGPIO, 
  int nTrigger,
  int nQurtInterruptID
)
{
  int32 nResult;
 
  if (!UGPIOINTQDI_VALID_GPIO(nGPIO)) 
  {
    return UGPIOINT_QDI_ERROR;
  }
  
  nResult = uGPIOInt_SetGPIOIntConfig((uint32)nGPIO,(uGPIOIntTriggerType)nTrigger,
                                      (uint32)nQurtInterruptID);
  return nResult;
 
} /* End uGPIOIntQDI_SetGPIOIntConfig */


/*===========================================================================
FUNCTION uGPIOIntQDI_Invoke

DESCRIPTION : 
  This is the main handler for the QDI driver layer in the kernel. All user
  specified methods are routed by this handler to the specific functionality.
 
===========================================================================*/
static int uGPIOIntQDI_Invoke(int hClientHandle,
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
      return uGPIOIntQDI_Open(hClientHandle, (void *)pobj, a1.ptr, a2.num);

    case UGPIOINT_QDI_SET_GPIO_CONFIG:
      return uGPIOIntQDI_SetGPIOIntConfig(hClientHandle,a1.num,a2.num,a3.num);

    case UGPIOINT_QDI_CLEAR_GPIO_CONFIG:
      return uGPIOIntQDI_ClearGPIOIntConfig(hClientHandle, a1.num);
    case UGPIOINT_QDI_SET_MPM_TRIGGER:
      return uGPIOIntQDI_ConfigureMPMInterrupt(hClientHandle, a1.num, a2.num);
    default:
      return qurt_qdi_method_default(hClientHandle, pobj, method,
                                     a1, a2, a3, a4, a5, a6, a7, a8, a9);	
  }
   return -1;
} /* End uGPIOIntQDI_Invoke */

