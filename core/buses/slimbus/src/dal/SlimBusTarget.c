/*
===========================================================================

FILE:         SlimBusTarget.c

DESCRIPTION:  This file implements the SLIMbus core driver target-specific
              functionality.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/src/dal/SlimBusTarget.c#3 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
02/04/15   MJS     Remove sleep latency vote.
12/19/14   MJS     Add sleep latency vote to prevent entering uImage mode.
09/03/14   MJS     Fix for race condition while checking external framer
                   satellite.
03/26/14   MJS     Purge satellite channels for non-responsive satellite.
03/19/14   MJS     Enhanced support for MDM restart.
12/12/13   MJS     Add support for TLMM write value.
11/07/13   MJS     Support for MDM restart when master is inactive framer.
11/06/13   MJS     Vote for DDR bandwidth to ensure MPORT clock will be on.
07/31/13   MJS     Use DALSYS busywait instead of QuRT.
03/21/13   MJS     Support for standalone satellite hardware configuration.
03/11/13   MJS     Update NPA voting value for nominal voltage.
03/04/13   MJS     Configure HAL platform environment.
02/15/13   MJS     Add parameter for voltage voting clock gear.
02/01/13   MJS     Configurable NPA name for SVS voting.
11/29/12   MJS     Error if ADSPPM handle initialization fails.
10/25/12   MJS     Support for voltage control and role reversal.
09/19/12   MJS     Restructure for binary compatibility.
04/19/12   MJS     Update for latest FLAT file.
05/25/11   MJS     Add pause clock support.
05/24/11   MJS     Add GPIO config, make no port disconnection int the norm.
05/10/11   MJS     Add port disconnection workwaround flag.
04/14/11   MJS     Added name field to BSP.
04/08/11   MJS     Implement workarounds for Waverider v1 and v2.
06/21/10   MJS     Initial revision.

===========================================================================
             Copyright (c) 2011, 2012, 2013, 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include "DALSys.h"
#include "DALDeviceId.h"
#include "SlimBus.h"
#include "SlimBusTarget.h"
#include "SlimBusDal.h"
#include "SlimBusSat.h"
#include "SlimBusMaster.h"
#include "SlimBusLists.h"
#include "HALhwio.h"
#include "DDITlmm.h"
#include "mmpm.h"
#include "npa.h"
#include "pmapp_npa.h"

/*------------------------------------------------------------------------------
Driver functions
------------------------------------------------------------------------------*/
DALResult
SlimBus_DeviceAttach(const char *, DALDEVICEID,DalDeviceHandle **);


/*------------------------------------------------------------------------------
Info file
------------------------------------------------------------------------------*/
static DALDEVICEID DalSlimBus_DeviceId[SLIMBUS_TARGET_NUM_DEVICES] = {DALDEVICEID_SLIMBUS_1};

const DALREG_DriverInfo
DALSlimBus_DriverInfo = { SlimBus_DeviceAttach, SLIMBUS_TARGET_NUM_DEVICES, DalSlimBus_DeviceId };

#define NUM_MMPM_REQS 4

static uint32 hMMPM = 0;
static MmpmRscExtParamType RscExtParam;
static MmpmRscParamType ReqArray[NUM_MMPM_REQS];
static MMPM_STATUS StsArray[NUM_MMPM_REQS];
static MmpmClkReqType ClkReq;
static MmpmClkValType ClkArray[1];
static MmpmGenBwReqType BwReq;
static MmpmGenBwValType BwVal;
static npa_client_handle hSVS;

/**
 * @brief Switch the master mode for the driver
 *
 * This function switches the role of the Slimbus driver between 
 * master and satellite mode. 
 * 
 * @param[in] h  Handle to the Slimbus driver
 * @param[in] bMaster  TRUE for master mode, FALSE for satellite 
 *       mode
 * 
 * @return TRUE on success, FALSE if an error occurred
 */
uint32 SlimBus_SwitchMasterMode(SlimBusHandle h, uint32 bMaster)
{
  SlimBusClientCtxt *pClientCtxt = SB_GET_PCLIENTCTXT(h);
  SlimBusDevCtxt *pDevCtxt = SB_GET_PDEVCTXT(pClientCtxt->hDevCtxt);
  SBResult result = SB_ERROR;
  
  SlimBus_LockDevice(pDevCtxt);
  
  if ( SB_MASTER_DRIVER == pDevCtxt->eDrvType &&
       FALSE != bMaster )
  {
    result = SB_SUCCESS;
  }
  else if ( SB_SATELLITE_DRIVER == pDevCtxt->eDrvType &&
            FALSE == bMaster )
  {
    result = SB_SUCCESS;
  }
  else if ( !pDevCtxt->bEverOpened )
  {
    pDevCtxt->bEverOpened = TRUE;
    if ( FALSE == bMaster )
    {
      pDevCtxt->eDrvType = SB_SATELLITE_DRIVER;
    }
    else
    {
      pDevCtxt->eDrvType = SB_MASTER_DRIVER;
    }
    
    SB_LOG_INFO_1("Switching driver mode (master: %d)",
                  (pDevCtxt->eDrvType == SB_MASTER_DRIVER));
    
    /* Do master or satellite specific initialization */
    if ( SB_MASTER_DRIVER == pDevCtxt->eDrvType )
    {
      if ( !SlimBus_IsMasterSupported() )
      {
        result = SB_ERROR;
      }
      else
      {
        result = SlimBus_DeviceInitMaster(pDevCtxt);
      }
    }
    else
    {
      if ( !SlimBus_IsSatSupported() )
      {
        result = SB_ERROR;
      }
      else
      {
        result = SlimBus_DeviceInitSat(pDevCtxt);
      }
    }
  }
  else
  {
    SB_LOG_ERR_0("Failed to switch driver mode due to device already opened");
  }

  SlimBus_UnlockDevice(pDevCtxt);
  
  return (SB_SUCCESS == result);
}

/**
 * @brief Check the external framer state
 *
 * This function checks the framer state and performs recovery
 * if the external framer is expected to be active but the clock
 * is not detected. 
 * 
 * @param[in] h  Handle to the Slimbus driver
 */
void SlimBus_CheckFramerState(SlimBusHandle h)
{
  SlimBusClientCtxt *pClientCtxt = SB_GET_PCLIENTCTXT(h);
  SlimBusDevCtxt *pDevCtxt = SB_GET_PDEVCTXT(pClientCtxt->hDevCtxt);
  SlimBusDeviceType *pNgdDevice;
  SBResult result;

  if (NULL == pDevCtxt->pSched)
  {
    return;
  }
  
  SlimBus_LockDevice(pDevCtxt);
  
  pNgdDevice = pDevCtxt->pDevices[pDevCtxt->pSched->FrmHandNgdLA&SB_LA_IDX_MASK];
  
  SB_LOG_WARN_0("Got request to check external framer state");

  SlimBus_CheckFramerStateInternal(pDevCtxt);
  
  if ( !pDevCtxt->bActiveFramer )
  {
    if ( (NULL != pNgdDevice) &&
         (pDevCtxt->pSched->FrmHandNgdLA == pNgdDevice->LA) &&
         (SB_FRM_HANDOVER_IDLE == pDevCtxt->pSched->eFrmHandState) )
    {
      pNgdDevice->eState = SB_ENUM_RESERVED;
      pDevCtxt->pSched->eFrmHandState = SB_FRM_HANDOVER_PREPARE;

      SB_LOG_INFO_0("Forcing framer back to APQ due to pending external framer restart");
      result = pDevCtxt->leaveLowPowerFcn(pDevCtxt);
  
      if (SB_SUCCESS == result)
      {
        result = SlimBus_DeviceInitHardware(pDevCtxt);
      }

      if (SB_SUCCESS == result)
      {
        SlimBus_SignalNextReconfig(pDevCtxt);
      }
    }
  }
  else
  {
    if ( NULL != pNgdDevice &&
         pDevCtxt->pSched->FrmHandNgdLA == pNgdDevice->LA &&
         NULL != pNgdDevice->pSat &&
         SlimBus_AreSatChannelsActive(pNgdDevice->pSat->paClientCtxt, pNgdDevice->pSat->numClientSlots) )
    {
      result = pDevCtxt->leaveLowPowerFcn(pDevCtxt);
      
      if (SB_SUCCESS == result)
      {
        pDevCtxt->pSched->bCheckFrmHandSat = TRUE;
        SlimBus_EventTrigger(pDevCtxt->hMasterWorkLoopEvent);
      }
    }
  }

  SlimBus_UnlockDevice(pDevCtxt);
}

/**
 * @brief Perform target-specific initialization for Slimbus
 *
 * This function performs target-specific initialization for 
 * Slimbus 
 * 
 * @param pDevCtxt  Pointer to the device context
 * 
 * @return SB_SUCCESS
 */
SBResult SlimBus_DeviceInitTarget(SlimBusDevCtxt *pDevCtxt)
{
  DALSYSPropertyVar PropVar;
  DALResult result;
  MmpmRegParamType RegParam;
  HAL_sb_EnvType sb_env = { DALSYS_BusyWait };
  
  if (NULL != pDevCtxt->pBSP)
  {
    return SB_SUCCESS;
  }
  
  result = DALSYS_GetPropertyValue(pDevCtxt->Base.hProp, "bsp_data", 0, &PropVar);
  if (result != DAL_SUCCESS)
  {
    return SB_ERROR;
  }
  pDevCtxt->pBSP = (SlimBusBSPType *)PropVar.Val.pdwVal;

  result = DALSYS_GetPropertyValue(pDevCtxt->Base.hProp, "svs_npa", 0, &PropVar);
  if (DAL_SUCCESS == result &&
      DALSYS_PROP_TYPE_STR_PTR == PropVar.dwType )
  {
    hSVS = npa_create_sync_client(PropVar.Val.pszVal, "slimbus", NPA_CLIENT_REQUIRED);
  }
  
  result = DALSYS_GetPropertyValue(pDevCtxt->Base.hProp, "tlmm_name", 0, &PropVar);
  if (DAL_SUCCESS == result &&
      DALSYS_PROP_TYPE_STR_PTR == PropVar.dwType )
  {
    DALSYSPropertyVar OffsetProp, ValProp;
    DalDeviceHandle *hHWIO;
    uint8 *TLMM_BASE_PTR = 0;

    result = DALSYS_GetPropertyValue( pDevCtxt->Base.hProp, "tlmm_offset", 0, &OffsetProp );
    if ( DAL_SUCCESS == result &&
         DALSYS_PROP_TYPE_UINT32 == OffsetProp.dwType &&
         DAL_SUCCESS == DAL_HWIODeviceAttach(DALDEVICEID_HWIO, &hHWIO) )
    {
      DalDevice_Open(hHWIO, DAL_OPEN_SHARED);
      if ( DAL_SUCCESS == DalHWIO_MapRegion(hHWIO, PropVar.Val.pszVal, &TLMM_BASE_PTR) )
      {
        uint32 uVal = 0x1;

        result = DALSYS_GetPropertyValue( pDevCtxt->Base.hProp, "tlmm_val", 0, &ValProp );
        if ( DAL_SUCCESS == result &&
             DALSYS_PROP_TYPE_UINT32 == ValProp.dwType )
        {
          uVal = ValProp.Val.dwVal;
        }

        /* Write to SLIMBUS_CTL */
        out_dword((TLMM_BASE_PTR+OffsetProp.Val.dwVal),uVal);
      }
      DalDevice_Close(hHWIO);
      DAL_DeviceDetach(hHWIO);
    }
    else
    {
      return SB_ERROR;
    }
  }

  RegParam.rev = MMPM_REVISION;
  RegParam.coreId = MMPM_CORE_ID_LPASS_SLIMBUS;
  RegParam.instanceId = MMPM_CORE_INSTANCE_0;
  RegParam.pClientName = "slimbus";
  RegParam.pwrCtrlFlag = PWR_CTRL_NONE;
  RegParam.callBackFlag = CALLBACK_NONE;
  RegParam.MMPM_Callback = NULL;
  RegParam.cbFcnStackSize = 0;
  
  hMMPM = MMPM_Register_Ext(&RegParam);
  if (NULL == hMMPM)
  {
    return SB_ERROR;
  }
  
  /* Setup the resource request data */
  ClkArray[0].clkId.clkIdLpass = MMPM_CLK_ID_LPASS_SLIMBUS_CORE;
  ClkArray[0].clkFreqHz = 24576000;
  ClkArray[0].freqMatch = MMPM_FREQ_EXACT;
  ClkReq.numOfClk = 1;
  ClkReq.pClkArray = ClkArray;

  BwVal.busRoute.masterPort = MMPM_BW_PORT_ID_SLIMBUS_MASTER;
  BwVal.busRoute.slavePort = MMPM_BW_PORT_ID_DDR_SLAVE;
  BwVal.bwValue.busBwValue.bwBytePerSec = 1024; /* just a minimum to keep clock on */
  BwVal.bwValue.busBwValue.usagePercentage = 1;
  BwVal.bwValue.busBwValue.usageType = MMPM_BW_USAGE_LPASS_DMA;
  BwReq.numOfBw = 1;
  BwReq.pBandWidthArray = &BwVal;

  ReqArray[0].rscId = MMPM_RSC_ID_POWER;
  //ReqArray[0].rscParam = 0; /* parameter is ignored for power request */
  ReqArray[1].rscId = MMPM_RSC_ID_REG_PROG;
  ReqArray[1].rscParam.regProgMatch = MMPM_REG_PROG_NORM;
  ReqArray[2].rscId = MMPM_RSC_ID_CORE_CLK;
  ReqArray[2].rscParam.pCoreClk = &ClkReq;
  ReqArray[3].rscId = MMPM_RSC_ID_GENERIC_BW;
  ReqArray[3].rscParam.pGenBwReq = &BwReq;

  RscExtParam.apiType = MMPM_API_TYPE_SYNC;
  RscExtParam.numOfReq = NUM_MMPM_REQS;
  RscExtParam.pReqArray = ReqArray;
  RscExtParam.pStsArray = StsArray;
  RscExtParam.reqTag = 0;
  RscExtParam.pExt = NULL;
  
  HAL_sb_ConfigEnv(&sb_env);

  return SB_SUCCESS;
}

/**
 * @brief Register callback for Subsystem Restart(SSR)
 *
 * This function registers callbacks for Subsystem Restart (SSR)
 * 
 * @param[in] h Client handle to the device
 * 
 * @return SB_SUCCESS 
 */
SBResult SlimBus_RegisterSSRcb(SlimBusDevCtxt *pDevCtxt)
{
  return SB_SUCCESS;
}

/**
 * @brief Control the voltage rail for Slimbus
 *
 * This function controls the voltage rail for Slimbus 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * @param[in] uReqClkGear  Requested clock gear
 * 
 * @return SB_SUCCESS on success, error code on error
 */
SBResult SlimBus_VoltageControl(SlimBusDevCtxt *pDevCtxt, uint32 uReqClkGear)
{
  if ( pDevCtxt->bIsHwOwner )
  {
    if (!pDevCtxt->bClockIsOn)
    {
      uReqClkGear = 0;
    }

    if ( uReqClkGear != pDevCtxt->uPowerClkGear )
    {
      if ( NULL != hSVS )
      {
        if ( SB_MAX_CLK_GEAR == uReqClkGear )
        {
          SB_LOG_INFO_0("Issuing request for nominal voltage");
          npa_issue_required_request(hSVS, PMIC_NPA_MODE_ID_CORE_RAIL_NOMINAL);
        }
        else if ( SB_MAX_CLK_GEAR == pDevCtxt->uPowerClkGear )
        {
          SB_LOG_INFO_0("Cancelling request for nominal voltage");
          npa_cancel_request(hSVS);
        }
      }
      else
      {
        SB_LOG_WARN_0("Skipping Slimbus voltage control due to NULL NPA handle");
      }
    }
    pDevCtxt->uPowerClkGear = uReqClkGear;
  }

  return SB_SUCCESS;
}


/**
 * @brief Turn on the Slimbus clock
 *
 * This function turns on the Slimbus clock
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * 
 * @return SB_SUCCESS on success, error code on error
 */
SBResult SlimBus_ClockOn(SlimBusDevCtxt *pDevCtxt)
{
  pDevCtxt->bClockIsOn = TRUE;
  
  if ( pDevCtxt->bIsHwOwner )
  {
    SlimBus_VoltageControl(pDevCtxt, pDevCtxt->uFrmClkGear);
    
    if (NULL != hMMPM)
    {
      MMPM_STATUS status = MMPM_Request_Ext(hMMPM, &RscExtParam);
      
      if (MMPM_STATUS_SUCCESS != status)
      {
        SB_LOG_ERR_1("Error during MMPM request (rc: %d)", status);
      }
    }
  }
  
  return SB_SUCCESS;
}

/**
 * @brief Turn off the Slimbus clock
 *
 * This function turns off the Slimbus clock
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * 
 * @return SB_SUCCESS on success, error code on error
 */
SBResult SlimBus_ClockOff(SlimBusDevCtxt *pDevCtxt)
{
  pDevCtxt->bClockIsOn = FALSE;
  
  if ( pDevCtxt->bIsHwOwner )
  {
    if (NULL != hMMPM)
    {
      MMPM_Release_Ext(hMMPM, &RscExtParam);
    }

    SlimBus_VoltageControl(pDevCtxt, pDevCtxt->uFrmClkGear);
  }
  
  return SB_SUCCESS;
}

