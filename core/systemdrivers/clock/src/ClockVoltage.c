/*
===========================================================================
*/
/**
  @file ClockVoltage.c 
  
  Digital voltage management interface implementation for the clock
  device driver.
*/
/*  
  ====================================================================

  Copyright (c) 2010 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header $
  $DateTime $
  $Author $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include "ClockSWEVT.h"


/*=========================================================================
      Constants and Macros 
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_UpdateVoltageRequests
** =========================================================================*/
/**
  Updates the current voltage request.
 
  This function updates the current voltage request for a particular voltage
  regulator configuration.
 
  @param *pDrvCtxt [in] -- Context pointer, the driver context in this case.
  @param pVRegConfig -- The voltage regulator configuration to update.
  @param eNewLevel -- New voltage level to configure.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR   -- Request failed.

  @dependencies
  None.
*/ 

static DALResult Clock_UpdateVoltageRequests
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockVRegConfigType *pVRegConfig,
  ClockVRegLevelType   eNewLevel
)
{
  ClockVRegLevelType eMinLevel;

  /*-----------------------------------------------------------------------*/
  /* Check if new min has changed.                                         */
  /*-----------------------------------------------------------------------*/

  if (eNewLevel > pVRegConfig->eMinLevel)
  {
    eMinLevel = eNewLevel;
  }
  else
  {
    for (eMinLevel = pVRegConfig->eMinLevel;
         eMinLevel > eNewLevel; eMinLevel--)
    {
      if (pVRegConfig->nClientCount[eMinLevel] > 0)
      {
        break;
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update request if minimum level is different.                         */
  /*-----------------------------------------------------------------------*/

  if (eMinLevel != pVRegConfig->eMinLevel)
  {
    if ((pVRegConfig->NPAHandle != NULL) && (!pDrvCtxt->bSuspendVoltageRequest))
    {
      /*
       * Set Fire and Forget attribute for the NPA request if we are
       * requesting for a lower voltage. This attribute is only valid for
       * one request and gets cleared as soon as the NPA receives it.
       */
      if (eMinLevel < pVRegConfig->eMinLevel)
      {
        npa_set_request_attribute(pVRegConfig->NPAHandle,
          NPA_REQUEST_FIRE_AND_FORGET);
      }

      npa_issue_scalar_request(pVRegConfig->NPAHandle, eMinLevel);
    }
    
    pVRegConfig->eMinLevel = eMinLevel;
  }
 
  return DAL_SUCCESS;

} /* END Clock_UpdateVoltageRequests */


/* =========================================================================
**  Function : Clock_VoltageRequest
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_VoltageRequest
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockVRegRequestType  *pCurrentRequest,
  ClockVRegRequestType  *pNewRequest
)
{
  ClockVRegConfigType *pCurrentVRegConfig, *pNewVRegConfig;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments are usable.                                        */
  /*-----------------------------------------------------------------------*/

  if ((pCurrentRequest == NULL)                              || 
	  (pNewRequest == NULL)                                  ||
	  (pCurrentRequest->eVRegLevel >= CLOCK_VREG_NUM_LEVELS) ||
	  (pNewRequest->eVRegLevel >= CLOCK_VREG_NUM_LEVELS))
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Find new minimum level.                                               */
  /*-----------------------------------------------------------------------*/

  if (pCurrentRequest->eVRegLevel == pNewRequest->eVRegLevel && 
      pCurrentRequest->bSuppressible == pNewRequest->bSuppressible)
  {
    return DAL_SUCCESS;
  }

  if (pCurrentRequest->bSuppressible)
  {
    pCurrentVRegConfig = &pDrvCtxt->VRegConfigSuppressible;
  }
  else
  {
    pCurrentVRegConfig = &pDrvCtxt->VRegConfig;
  }

  if (pNewRequest->bSuppressible)
  {
    pNewVRegConfig = &pDrvCtxt->VRegConfigSuppressible;
  }
  else
  {
    pNewVRegConfig = &pDrvCtxt->VRegConfig;
  }

  /*-----------------------------------------------------------------------*/
  /* Note:                                                                 */
  /*   PMIC defaults to NOMINAL at boot-up.                                */
  /*                                                                       */
  /* Note:                                                                 */
  /*   Once the PMIC NPA node is available we get callback                 */
  /*   notification that allows us to vote immediately.                    */
  /*                                                                       */
  /* Note:                                                                 */
  /*   We ERROR_FATAL if the request is greater than the driver context's  */
  /*   initial vreg level prior to us being able to communicate that       */
  /*   requirement over to RPM.                                            */
  /*-----------------------------------------------------------------------*/

  if ((pNewVRegConfig->NPAHandle == NULL) &&
      (pNewRequest->eVRegLevel > pNewVRegConfig->eInitLevel))
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_VoltageRequest received [%d] prior to communication with RPM",
      pNewRequest->eVRegLevel);

    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* All domains default to OFF at init, but the ClientCount for OFF will  */
  /* not reflect this.  So we cannot track clients for the OFF voltage     */
  /* level, but this is ok since it is the "do not care" level.            */
  /*-----------------------------------------------------------------------*/

  if (pCurrentRequest->eVRegLevel != CLOCK_VREG_LEVEL_OFF &&
      pCurrentVRegConfig->nClientCount[pCurrentRequest->eVRegLevel] > 0)
  {
    pCurrentVRegConfig->nClientCount[pCurrentRequest->eVRegLevel]--;
  }

  if (pNewRequest->eVRegLevel != CLOCK_VREG_LEVEL_OFF)
  {
    pNewVRegConfig->nClientCount[pNewRequest->eVRegLevel]++;
  }

  pCurrentRequest->eVRegLevel = pNewRequest->eVRegLevel;
  pCurrentRequest->bSuppressible = pNewRequest->bSuppressible;

  /*-----------------------------------------------------------------------*/
  /* Update voltage requests.                                              */
  /*-----------------------------------------------------------------------*/

  Clock_UpdateVoltageRequests(pDrvCtxt, pNewVRegConfig, pNewRequest->eVRegLevel);
  Clock_UpdateVoltageRequests(pDrvCtxt, pCurrentVRegConfig, CLOCK_VREG_LEVEL_OFF);

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_VoltageRequest */


/* =========================================================================
**  Function : Clock_VoltageNodeReadyCallback
** =========================================================================*/
/**
  Callback when the PMIC NPA node is ready.
 
  This function is invoked by the NPA framework when the PMIC NPA node
  is ready to be used.  It will create a client and enter the current
  driver minimum voltage request.
 
  @param *pContext [in] -- Context pointer, the driver context in this case.

  @return
  NULL

  @dependencies
  None.
*/ 

void Clock_VoltageNodeReadyCallback
(
  void *pContext
)
{
  ClockDrvCtxt *pDrvCtxt = (ClockDrvCtxt *)pContext;

  /*-----------------------------------------------------------------------*/
  /* Ensure atomicity                                                      */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Create NPA client handle for VDD dig core if it hasn't been created.  */
  /*-----------------------------------------------------------------------*/
  
  if (pDrvCtxt->VRegConfig.NPAHandle == NULL)
  {
    pDrvCtxt->VRegConfig.NPAHandle = 
      npa_create_sync_client(
        CLOCK_PMIC_RESOURCE_VDD_DIG,
        CLOCK_PMIC_RESOURCE_VDD_DIG_CLIENT, 
        NPA_CLIENT_REQUIRED);
  }

  if (pDrvCtxt->VRegConfigSuppressible.NPAHandle == NULL)
  {
    pDrvCtxt->VRegConfigSuppressible.NPAHandle = 
      npa_create_sync_client(
        CLOCK_PMIC_RESOURCE_VDD_DIG,
        CLOCK_PMIC_RESOURCE_VDD_DIG_CLIENT, 
        NPA_CLIENT_SUPPRESSIBLE);
  }

  /*-----------------------------------------------------------------------*/
  /* Make a request for the currently required voltage.                    */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->VRegConfig.NPAHandle)
  {
    npa_issue_scalar_request(pDrvCtxt->VRegConfig.NPAHandle,
      pDrvCtxt->VRegConfig.eMinLevel);
  }

  if (pDrvCtxt->VRegConfigSuppressible.NPAHandle)
  {
    npa_issue_scalar_request(pDrvCtxt->VRegConfigSuppressible.NPAHandle,
      pDrvCtxt->VRegConfigSuppressible.eMinLevel);
  }

  /*-----------------------------------------------------------------------*/
  /* Log CX Voltage Event.                                                 */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(CLOCK_EVENT_CX_VOLTAGE, 1, pDrvCtxt->VRegConfig.eMinLevel);

  /*-----------------------------------------------------------------------*/
  /* Free mutex.                                                           */
  /*-----------------------------------------------------------------------*/
 
  DALCLOCK_FREE(pDrvCtxt);  

} /* END Clock_VoltageNodeReadyCallback */


/* =========================================================================
**  Function : Clock_VoltageSuspend
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_VoltageSuspend
(
  ClockDrvCtxt *pDrvCtxt
)
{
  pDrvCtxt->bSuspendVoltageRequest = TRUE;
  return DAL_SUCCESS;

} /* END Clock_VoltageSuspend */


/* =========================================================================
**  Function : Clock_VoltageResume
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_VoltageResume
(
  ClockDrvCtxt  *pDrvCtxt,
  boolean        bUpdate
)
{
  pDrvCtxt->bSuspendVoltageRequest = FALSE;

  /*-----------------------------------------------------------------------*/
  /* Make a voltage request when resuming from suspension.                 */
  /*-----------------------------------------------------------------------*/

  if (bUpdate)
  {
    if (pDrvCtxt->VRegConfig.NPAHandle != NULL)
    {
      npa_issue_scalar_request(pDrvCtxt->VRegConfig.NPAHandle, 
        pDrvCtxt->VRegConfig.eMinLevel);

      /*
       * Log CX Voltage Event.
       */
      Clock_SWEvent(CLOCK_EVENT_CX_VOLTAGE, 1, pDrvCtxt->VRegConfig.eMinLevel);
    }

    if (pDrvCtxt->VRegConfigSuppressible.NPAHandle != NULL)
    {
      npa_issue_scalar_request(pDrvCtxt->VRegConfigSuppressible.NPAHandle,
        pDrvCtxt->VRegConfigSuppressible.eMinLevel);

      /*
       * Log CX Voltage Event.
       */
      Clock_SWEvent(CLOCK_EVENT_CX_VOLTAGE, 1, pDrvCtxt->VRegConfig.eMinLevel);
    }
  }

  return DAL_SUCCESS;

} /* END Clock_VoltageResume */


/* =========================================================================
**  Function : Clock_InitVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_InitVoltage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult               eResult;
  ClockPropertyValueType  PropVal;
  ClockVRegLevelType     *pCXVRegInit;

  /*-----------------------------------------------------------------------*/
  /* Get initial CX voltage level from BSP.                                */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("CXVRegInitLevel", &PropVal);

  if (eResult != DAL_SUCCESS)
  {
    pDrvCtxt->VRegConfig.eMinLevel =
    pDrvCtxt->VRegConfig.eInitLevel =
    pDrvCtxt->VRegConfigSuppressible.eInitLevel = CLOCK_VREG_LEVEL_LOW;
  }
  else
  {
    pCXVRegInit = (ClockVRegLevelType *)PropVal;

    if ((pCXVRegInit == NULL)                  ||
        (*pCXVRegInit == CLOCK_VREG_LEVEL_OFF) ||
        (*pCXVRegInit >= CLOCK_VREG_NUM_LEVELS) )
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
        "Invalid initial CX corner value in BSP. Setting to LOW.");

      pDrvCtxt->VRegConfig.eMinLevel =
      pDrvCtxt->VRegConfig.eInitLevel =
      pDrvCtxt->VRegConfigSuppressible.eInitLevel = CLOCK_VREG_LEVEL_LOW;
    }
    else
    {
      pDrvCtxt->VRegConfig.eMinLevel =
      pDrvCtxt->VRegConfig.eInitLevel =
      pDrvCtxt->VRegConfigSuppressible.eInitLevel = *pCXVRegInit;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Create callback event to initialize the remote node client.           */
  /*-----------------------------------------------------------------------*/

  eResult =
    Clock_RegisterResourceCallback(
      pDrvCtxt,
      CLOCK_PMIC_RESOURCE_VDD_DIG,
      Clock_VoltageNodeReadyCallback,
      pDrvCtxt);

  return eResult;

} /* END Clock_InitVoltage */



