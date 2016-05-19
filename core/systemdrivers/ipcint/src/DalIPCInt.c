/*============================================================================

FILE:      DalIPCInt.c

DESCRIPTION:
  This file implements the portion of the ChipInfo DAL that reads information
  from the hardware.

PUBLIC CLASSES:
  IPCInt_DriverInit
  IPCInt_DriverDeInit
  IPCInt_Trigger
  IPCInt_IsSupported
  IPCInt_TriggerBySource
  IPCInt_IsSupportedBySource

============================================================================
        Copyright (c) 2009 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
============================================================================
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/ipcint/src/DalIPCInt.c#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $
============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DalIPCInt.h"
#include "DALStdDef.h"
#include "DDIHWIO.h"
#include "DDIInterruptController.h"

#ifdef IPCINT_RECEIVE_TEST
uint8 InterruptsToRegister[32];
uint32 Interruptlog[200];
 DalDeviceHandle  *pIPCHandle;
 
#endif /* IPCINT_RECEIVE_TEST */
/*=========================================================================
      Implementation
==========================================================================*/

DalDeviceHandle *pHWIOHandler;
/*==========================================================================

  FUNCTION      IPCInt_DriverInit

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_DriverInit
(
  IPCIntDrvCtxt *pCtxt
)
{
  return DAL_SUCCESS;

} /* IPCInt_DriverInit */


/*==========================================================================

  FUNCTION      IPCInt_DriverDeInit

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_DriverDeInit
(
  IPCIntDrvCtxt *pCtxt
)
{
	return DAL_SUCCESS;

} /* IPCInt_DriverDeInit */


/*==========================================================================

  FUNCTION      IPCInt_Trigger

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_Trigger
(
  IPCIntClientCtxt       *pCtxt,
  DalIPCIntProcessorType  eTarget,
  DalIPCIntInterruptType  eInterrupt
) 
{
  return IPCInt_TriggerBySource(
    pCtxt, pCtxt->pIPCIntDevCtxt->pIPCIntDrvCtxt->eSourceProcessor,
    eTarget, eInterrupt);

} /* IPCInt_Trigger */


/*==========================================================================

  FUNCTION      IPCInt_TriggerBySource

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_TriggerBySource
(
  IPCIntClientCtxt       *pCtxt,
  DalIPCIntProcessorType  eSource,
  DalIPCIntProcessorType  eTarget,
  DalIPCIntInterruptType  eInterrupt
) 
{
  uint32 int_mask = 1;
  uint32 reg_addr = 0;
  DALResult result = DAL_SUCCESS;

  if (eTarget == pCtxt->pIPCIntDevCtxt->pIPCIntDrvCtxt->eSourceProcessor)
  {
    return DAL_ERROR; //source and target cannot be the same!
  }

  switch(eTarget)
  {
    case DALIPCINT_PROC_WCN:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
          int_mask <<= WCN_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= WCN_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= WCN_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= WCN_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_MDSPSW:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
          int_mask <<= MPSS_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= MPSS_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= MPSS_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= MPSS_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_ADSP:       //ADSP and LPASS are the same for MPSS 2.0
    case DALIPCINT_PROC_LPASS:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
          int_mask <<= ADSP_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= ADSP_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= ADSP_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= ADSP_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_ACPU:
      switch (eInterrupt)
      {
        // APCS_HLOS
        case DALIPCINT_GP_0:
          int_mask <<= APCS_HLOS_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= APCS_HLOS_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= APCS_HLOS_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= APCS_HLOS_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
       }
      break;
    case DALIPCINT_PROC_TZ:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
          int_mask <<= APCS_TZ_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= APCS_TZ_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= APCS_TZ_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= APCS_TZ_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;
    case DALIPCINT_PROC_RPM:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
          int_mask <<= RPM_IPC_GP_0_IRQ;
          break;
        case DALIPCINT_GP_1:
          int_mask <<= RPM_IPC_GP_1_IRQ;
          break;
        case DALIPCINT_GP_2:
          int_mask <<= RPM_IPC_GP_2_IRQ;
          break;
        case DALIPCINT_GP_3:
          int_mask <<= RPM_IPC_GP_3_IRQ;
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    default: // catch all cases in the enums NOT cited here. Causes Q6 only compiler error
      result = DAL_ERROR;
      break;
  }

  if (result == DAL_SUCCESS)
  {
    reg_addr = (uint32) pCtxt->pIPCIntDevCtxt->ipcint_cntrl.nIPCIntBase; // fetch IPCInt register address
    outpdw(reg_addr, int_mask);     
  
  }
      
  return result;

} /* IPCInt_TriggerBySource */


/*==========================================================================

  FUNCTION      IPCInt_IsSupported

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_IsSupported
(
  IPCIntClientCtxt       *pCtxt,
  DalIPCIntProcessorType  eTarget,
  DalIPCIntInterruptType  eInterrupt
) 
{
  return IPCInt_IsSupportedBySource(
    pCtxt, pCtxt->pIPCIntDevCtxt->pIPCIntDrvCtxt->eSourceProcessor,
    eTarget, eInterrupt);

} /* IPCInt_IsSupported */


/*==========================================================================

  FUNCTION      IPCInt_IsSupportedBySource

  DESCRIPTION   See DDIIPCInt.h

==========================================================================*/

DALResult IPCInt_IsSupportedBySource
(
  IPCIntClientCtxt       *pCtxt,
  DalIPCIntProcessorType  eSource,
  DalIPCIntProcessorType  eTarget,
  DalIPCIntInterruptType  eInterrupt
) 
{
  DALResult result = DAL_SUCCESS;

  if (eSource  != pCtxt->pIPCIntDevCtxt->pIPCIntDrvCtxt->eSourceProcessor)
  {
    return DAL_ERROR; // Is this source on the supported list?
  }

  switch(eTarget)
  {
    case DALIPCINT_PROC_WCN:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_MDSPSW:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_ADSP:       //ADSP and LPASS are the same for MPSS 2.0
    case DALIPCINT_PROC_LPASS:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_ACPU:
      switch (eInterrupt)
      {
        // APCS_HLOS
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
          break;
        default:
          result = DAL_ERROR;
          break;
      }
    break;
    case DALIPCINT_PROC_TZ:
      switch (eInterrupt)
	  {
        // APCS_TZ
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
          break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    case DALIPCINT_PROC_RPM:
      switch (eInterrupt)
      {
        case DALIPCINT_GP_0:
        case DALIPCINT_GP_1:
        case DALIPCINT_GP_2:
        case DALIPCINT_GP_3:
           break;
        default:
          result = DAL_ERROR;
          break;
      }
      break;

    default: // catch all cases in the enums NOT cited here. Causes Q6 only compiler error
      result = DAL_ERROR;
      break;
  }

  return result;

} /* IPCInt_IsSupported */

DALResult IPCInt_GetTargetData(IPCIntClientCtxt *pCtxt)
{
  IPCIntDevCtxt *pDevice;
  DALSYS_PROPERTY_HANDLE_DECLARE(IPCInt_property);
  DALSYSPropertyVar system_property;

  pDevice = pCtxt->pIPCIntDevCtxt; // point to the associated device context.  
  
  if( DAL_SUCCESS != DALSYS_GetDALPropertyHandle(DALDEVICEID_IPCINT, IPCInt_property))
  {
    return DAL_ERROR;
  }

  if( DAL_SUCCESS != DALSYS_GetPropertyValue(IPCInt_property, "SourceProc", 0, &system_property))
  {
    DALSYS_LogEvent(pDevice->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
                      "IPCInt_GetTargetData: Device could not get SourceProc");
    return DAL_ERROR;
    
  }
    
  pCtxt->pIPCIntDevCtxt->pIPCIntDrvCtxt->eSourceProcessor = (DalIPCIntProcessorType)system_property.Val.dwVal;

  // get the IPCInt physical base address
  if( DAL_SUCCESS != DALSYS_GetPropertyValue(IPCInt_property, "IPCINT_PHYSICAL_ADDRESS", 0, &system_property))
  {
    DALSYS_LogEvent(pDevice->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
                      "IPCInt_GetTargetData: Device could not get IPCINT_PHYSICAL_ADDRESS");
    return DAL_ERROR;
  }
 
  pDevice->ipcint_cntrl.nIPCIntBasePhys = (uint32 *)system_property.Val.dwVal;

  // get the IPCInt offset
  if( DAL_SUCCESS != DALSYS_GetPropertyValue(IPCInt_property, "IPCINT_OFFSET", 0, &system_property))
  {
    DALSYS_LogEvent(pDevice->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
                      "IPCInt_GetTargetData: Device could not get IPCINT_OFFSET");
    return DAL_ERROR;
  }
  
  pDevice->ipcint_cntrl.nIPCIntOffset = (uint32)system_property.Val.dwVal;
  // pDevice->ipcint_cntrl.nIPCIntOffset = 0x105000;

  if(DAL_DeviceAttach(DALDEVICEID_HWIO,&pHWIOHandler) == DAL_SUCCESS)
  {
    if (DalHWIO_MapRegionByAddress(pHWIOHandler, (uint8 *)pDevice->ipcint_cntrl.nIPCIntBasePhys, 
                                  (uint8**)&(pDevice->ipcint_cntrl.nIPCIntBaseVirt) )!= DAL_SUCCESS)
    {
      DALSYS_LogEvent(pDevice->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
                      "IPCInt_GetTargetData: could not get the virtual address");
      return DAL_ERROR; 
    }    
    pDevice->ipcint_cntrl.nIPCIntBase = (uint32) pDevice->ipcint_cntrl.nIPCIntBaseVirt ;
    pDevice->ipcint_cntrl.nIPCIntBase += pDevice->ipcint_cntrl.nIPCIntOffset; 
   
  }
  else
  {
    pDevice->ipcint_cntrl.nIPCIntBase =  (uint32) pDevice->ipcint_cntrl.nIPCIntBasePhys;
    pDevice->ipcint_cntrl.nIPCIntBase += pDevice->ipcint_cntrl.nIPCIntOffset; 
  }
  return DAL_SUCCESS;

}

/*------------------------------------------------------------------------------
Following functions are declared in DalDevice Interface. 
------------------------------------------------------------------------------*/

DALResult 
IPCInt_DeviceInit(IPCIntClientCtxt *pCtxt)
{

  IPCIntDevCtxt *pDevice;
  pDevice = pCtxt->pIPCIntDevCtxt; // point to the associated device context

  if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_NO_PREEMPTION,
                                      &(pDevice->IPCInt_synchronization),
                                      &(pDevice->IPCIntSyncObject)))
  {
    DALSYS_LogEvent(pDevice->DevId, DALSYS_LOGEVENT_FATAL_ERROR, 
                      "IPCInt_DeviceInit: Device could not create a sync object");
    return DAL_ERROR;
  }

  if(IPCInt_GetTargetData(pCtxt) != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/
  return DAL_SUCCESS;
}

DALResult 
IPCInt_DeviceDeInit(IPCIntClientCtxt *pCtxt)
{
    return DAL_SUCCESS;
}

DALResult 
IPCInt_PowerEvent(IPCIntClientCtxt *pCtxt, DalPowerCmd PowerCmd, 
                    DalPowerDomain PowerDomain)
{
    return DAL_SUCCESS;
}

DALResult 
IPCInt_Open(IPCIntClientCtxt *pCtxt, uint32 dwaccessMode )
{
    return DAL_SUCCESS;
}

DALResult 
IPCInt_Close(IPCIntClientCtxt *pCtxt)
{
    return DAL_SUCCESS;
}

DALResult 
IPCInt_Info(IPCIntClientCtxt *pCtxt,DalDeviceInfo *pdeviceInfo, uint32 dwSize)
{
    return DAL_SUCCESS;
}

#ifdef IPCINT_RECEIVE_TEST
void IPCInt_TestIsr
(
  void *param
)
{
 
  uint8 Interrupt;
  uint32 interrupt_count, mycount;

  Interrupt = *(uint32 *)param;
  interrupt_count = Interruptlog[Interrupt];
  Interruptlog[Interrupt] = interrupt_count +1;
  mycount = 1;
  while(mycount)
  {
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_0))
    {
      return;
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_1))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_2))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_3))
    {
      return;    
    }

    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_0))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_1))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_2))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_3))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_0))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_1))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_2))
    {
      return;    
    }
    if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_3))
    {
      return;    
    }
    mycount --;
  }
}
#endif /* IPCINT_RECEIVE_TEST*/
void IPCInt_Test(void)
{

  #ifdef IPCINT_RECEIVE_TEST
  DalDeviceHandle * intr_handle;
  uint32 mycount,index;
  mycount= 10;
  if(DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_IPCINT, &pIPCHandle))
  {
    return;
  }
  /* attach to the Main Interrupt Controller dal*/
  if(DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER, 
                                     &intr_handle))
  {
    return;
  }

  /* Incoming interrupts from MPSS */
  InterruptsToRegister[0] = 92;
  InterruptsToRegister[1] = 93;
  InterruptsToRegister[2] = 94;
  InterruptsToRegister[3] = 95;

  /* Incoming interrupts from APPS */
  InterruptsToRegister[4] = 13;
  InterruptsToRegister[5] = 14;
  InterruptsToRegister[6] = 15;
  InterruptsToRegister[7] = 16;
  
  /* Incoming interrupts from Pronto */
  InterruptsToRegister[8]  = 15;
  InterruptsToRegister[9]  = 52;
  InterruptsToRegister[10] = 21;
  InterruptsToRegister[11] = 35;
  
  for(index=0;index< 12;index++)
  {
    if (DAL_SUCCESS != DalInterruptController_RegisterISR(intr_handle, 
                     InterruptsToRegister[index] ,(DALISR)IPCInt_TestIsr, (DALISRCtx)&InterruptsToRegister[index], 
                     DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER))
    {
      return;
    }
  }
#endif
#ifdef IPCINT_SEND_TEST
  while(mycount)
{
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_0))
  {
    return;
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_1))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_2))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_MDSPSW, DALIPCINT_GP_3))
  {
    return;    
  }

  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_0))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_1))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_2))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_ACPU, DALIPCINT_GP_3))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_0))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_1))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_2))
  {
    return;    
  }
  if (DAL_SUCCESS != DalIPCInt_Trigger(pIPCHandle, DALIPCINT_PROC_WCN, DALIPCINT_GP_3))
  {
    return;    
  }
  mycount --;
}
  #endif /* IPCINT_SEND_TEST */
}

