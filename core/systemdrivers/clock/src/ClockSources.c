/*
===========================================================================
*/
/**
  @file ClockSources.c

  Interface implementation file for the sources management of the
  clock device driver.
*/
/*
  ====================================================================

  Copyright (c) 2010 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/src/ClockSources.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "HALclk.h"

#include "ClockSWEVT.h"

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_InitSources
** =========================================================================*/
/*
  See DalClock.h
*/

DALResult Clock_InitSources
(
  ClockDrvCtxt *pDrvCtxt
)
{
  ClockPropertyValueType      PropVal;
  ClockSourceConfigType      *pClockSourceFirstBSPData, *pClockSourceBSPData;
  uint32                      nSourceIndex, nSubSourceIndex;
  DALResult                   eResult;
  uint32                      nSize;
  ClockSourceNodeType        *pSource;
  ClockSourceFreqConfigType  *pSourceFreqConfig;
  HAL_clk_PLLConfigType       DetectedConfig;
  HAL_clk_SourceType          eSubSource;

  /*-----------------------------------------------------------------------*/
  /* Get the list of clock sources from the BSP/XML                        */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockSources", &PropVal);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_GetPropertyValue failed.");
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Count the number of clock sources present in the BSP/XML              */
  /*-----------------------------------------------------------------------*/

  /*
   * Get the pointer to the clock sources data
   */
  pClockSourceFirstBSPData = (ClockSourceConfigType *)PropVal;
  pClockSourceBSPData = pClockSourceFirstBSPData;

  /*
   * Go through all sources until we hit the end marker and increment
   * the source count.
   */
  while (pClockSourceBSPData->eSource != HAL_CLK_SOURCE_NULL)
  {
    pDrvCtxt->nNumSources++;
    pClockSourceBSPData++;
  }

  /*
   * Make sure we found at least one source.
   */
  if (pDrvCtxt->nNumSources == 0)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitSources found 0 sources.");
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Allocate memory for the source nodes                                  */
  /*-----------------------------------------------------------------------*/

  nSize = pDrvCtxt->nNumSources * sizeof (*pDrvCtxt->aSources);

  eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aSources);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to allocate %d bytes for %d sources.",
      nSize, pDrvCtxt->nNumSources);
    return eResult;
  }

  memset((void *)pDrvCtxt->aSources, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Initialize the source nodes                                           */
  /*-----------------------------------------------------------------------*/

  /*
   * Invalidate the look-up array
   */
  for (nSourceIndex = 0; nSourceIndex < HAL_CLK_NUM_OF_SOURCES; nSourceIndex++)
  {
    pDrvCtxt->anSourceIndex[nSourceIndex] = 0xFF;
  }

  pClockSourceBSPData = pClockSourceFirstBSPData;
  for (nSourceIndex = 0; nSourceIndex < pDrvCtxt->nNumSources; nSourceIndex++)
  {
    /*
     * Store the index of this source in the look-up array
     */
    pDrvCtxt->anSourceIndex[pClockSourceBSPData->eSource] = (uint8)nSourceIndex;

    /*
     * Link the source node to its BSP/XML configuration data
     */
    pDrvCtxt->aSources[nSourceIndex].pBSPConfig = pClockSourceBSPData;
    pDrvCtxt->aSources[nSourceIndex].eSource = pClockSourceBSPData->eSource;

    /*
     * Store the source name
     */
    pDrvCtxt->aSources[nSourceIndex].szName = pClockSourceBSPData->szName;

    // TODO: This is where we can do any other source init steps.  For example,
    // if a source needs to be initialized (.init_src), then we can do that here.

    /*
     * Move to the next source
     */
    pClockSourceBSPData++;
  }

  /*-----------------------------------------------------------------------*/
  /* Connect up sources that have sub-sources, like PLLs->XO               */
  /*-----------------------------------------------------------------------*/

  for (nSourceIndex = 0; nSourceIndex < pDrvCtxt->nNumSources; nSourceIndex++)
  {
    pSource = &pDrvCtxt->aSources[nSourceIndex];

    /*
     * Use the first config for XO
     */
    if (pSource->eSource == HAL_CLK_SOURCE_XO)
    {
      pSource->pActiveFreqConfig = pSource->pBSPConfig->pSourceFreqConfig;
      continue;
    }

    /*
     * Detect the current configuration of this source.
     */
    HAL_clk_DetectPLLConfig(pSource->eSource, &DetectedConfig);

    /*
     * Try to match the detected source config against the BSP data.
     */
    if (DetectedConfig.eSource != HAL_CLK_SOURCE_NULL)
    {
      pSourceFreqConfig = pSource->pBSPConfig->pSourceFreqConfig;

      /*
       * Iterate over source freq configs until we reach the end marker.
       */
      while(pSourceFreqConfig->nFreqHz != 0)
      {
        /*
         * Compare the detected config to this config.
         */
        if (DetectedConfig.eSource  == pSourceFreqConfig->HALConfig.eSource  &&
            DetectedConfig.nL       == pSourceFreqConfig->HALConfig.nL       &&
            DetectedConfig.nM       == pSourceFreqConfig->HALConfig.nM       &&
            DetectedConfig.nN       == pSourceFreqConfig->HALConfig.nN       &&
            DetectedConfig.nAlpha   == pSourceFreqConfig->HALConfig.nAlpha   &&
            DetectedConfig.nAlphaU  == pSourceFreqConfig->HALConfig.nAlphaU  &&
            DetectedConfig.nPostDiv == pSourceFreqConfig->HALConfig.nPostDiv &&
            DetectedConfig.nPreDiv  == pSourceFreqConfig->HALConfig.nPreDiv)
        {
          /*
           * Store the detected frequency configuration.
           */
          pSource->pActiveFreqConfig = pSourceFreqConfig;

          /*
           * Exit this search loop.
           */
          break;
        }

        /*
         * Move to the next frequency config for this source.
         */
        pSourceFreqConfig++;
      }
    }

    /*
     * Hookup the sub-source pointer.
     */
    if (pSource->pActiveFreqConfig != NULL)
    {
      eSubSource = pSource->pActiveFreqConfig->HALConfig.eSource;
      if (eSubSource < HAL_CLK_NUM_OF_SOURCES)
      {
        nSubSourceIndex = pDrvCtxt->anSourceIndex[eSubSource];
        if (nSubSourceIndex != 0xFF)
        {
          pSource->pSource = &pDrvCtxt->aSources[nSubSourceIndex];
        }
      }
    }

    /*
     * Log a warning if we were unable to detect the active config.
     */
    else
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
        "Clock_InitSources could not find matching freq config for source[%s].",
        pSource->szName);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Source initialization complete                                        */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitSources */


/* =========================================================================
**  Function : Clock_SourceOn
** =========================================================================*/
/**
  Enables a source.

  This function performs the final operations required to turn on a
  clock source.  It handles deciding whether to use an NPA client request,
  a HAL source vote, or a direct HAL source enable call.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pSource [in] -- Pointer to a source node.
  @param nNPAState [in] -- State value to use in any NPA request.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.

  @return
  None.
*/

static void Clock_SourceOn
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  uint32               nNPAState,
  boolean              bSuppressibleRequest
)
{
  ClockVRegRequestType        VRegRequest;
  ClockSourceFreqConfigType  *pActiveFreqConfig = pSource->pActiveFreqConfig;

  /*-----------------------------------------------------------------------*/
  /* Assert the voltage requirement.                                       */
  /*-----------------------------------------------------------------------*/

    if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
    {
      VRegRequest.eVRegLevel = pActiveFreqConfig->eVRegLevel;
      VRegRequest.bSuppressible = bSuppressibleRequest;
      Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
    }

  /*-----------------------------------------------------------------------*/
  /* Enable the source using an NPA client if it exists, or HAL call       */
  /* otherwise.                                                            */
  /*-----------------------------------------------------------------------*/

  if (pSource->NPAHandle != NULL)
  {
    npa_issue_scalar_request(pSource->NPAHandle, nNPAState);
  }
  else if (pSource->pBSPConfig->nConfigMask & CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
  {
    HAL_clk_EnableSourceVote(pSource->eSource, FALSE);
  }
  else
  {
    HAL_clk_EnableSource(pSource->eSource);
  }

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pSource, LOG_STATE_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_STATE_CHANGE))
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                      "%s (Enabled: 1)", pSource->szName);
  }

  /*-----------------------------------------------------------------------*/
  /* Log source enable.                                                    */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(CLOCK_EVENT_SOURCE_STATUS, 2, pSource->eSource, 1);

} /* END Clock_SourceOn */


/* =========================================================================
**  Function : Clock_SourceOff
** =========================================================================*/
/**
  Disables a source.

  This function performs the final operations required to turn off a
  clock source.  It handles deciding whether to use an NPA client request,
  a HAL source vote, or a direct HAL source disable call.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pSource [in] -- Pointer to a source node.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.

  @return
  None.
*/

static void Clock_SourceOff
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  boolean              bSuppressibleRequest
)
{
  ClockVRegRequestType VRegRequest;

  /*-----------------------------------------------------------------------*/
  /* Disable the source using an NPA client if it exists, or HAL call      */
  /* otherwise.                                                            */
  /*-----------------------------------------------------------------------*/

  if (pSource->NPAHandle != NULL)
  {
    npa_issue_scalar_request(pSource->NPAHandle, CLOCK_SOURCE_NOT_REQUIRED);
  }
  else if (pSource->pBSPConfig->nConfigMask &
             CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
  {
    HAL_clk_DisableSourceVote(pSource->eSource);
  }
  else
  {
    HAL_clk_DisableSource(pSource->eSource);
  }

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pSource, LOG_STATE_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_STATE_CHANGE))
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                      "%s (Enabled: 0)", pSource->szName);
  }

  /*-----------------------------------------------------------------------*/
  /* Deassert the voltage requirement.                                     */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    VRegRequest.eVRegLevel = CLOCK_VREG_LEVEL_OFF;
    VRegRequest.bSuppressible = bSuppressibleRequest;
    Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
  }

  /*-----------------------------------------------------------------------*/
  /* Log source disable.                                                   */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(CLOCK_EVENT_SOURCE_STATUS, 2, pSource->eSource, 0);
} /* END Clock_SourceOff */


/* =========================================================================
**  Function : Clock_EnableSourceInternal
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_EnableSourceInternal
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  boolean              bSuppressibleRequest
)
{
  ClockVRegRequestType VRegRequest; 
  
  DALResult eResult;

  /*-----------------------------------------------------------------------*/
  /* Make sure the source handle is valid.                                 */
  /*-----------------------------------------------------------------------*/

  if (pSource == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Process insuppressible requests.                                      */
  /*-----------------------------------------------------------------------*/

  if (!bSuppressibleRequest)
  {
    if (pSource->nReferenceCount == 0)
    {
      /*
       * If the source has a source, then recursively enable that.
       * If the current state is enabled for a insuppressible clock, then we
       * need to release the previously registered vote.
       */
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
          (pSource->pSource != NULL))
      {
        eResult = Clock_EnableSourceInternal(pDrvCtxt, pSource->pSource, FALSE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * Turn on the source if it is not already on.  If there is already
       * a suppressible reference count we just need to update the NPA state
       * and voltage request with the insuppressible requirements.
       */
      if (pSource->nReferenceCountSuppressible == 0)
      {
        Clock_SourceOn(pDrvCtxt, pSource, CLOCK_SOURCE_REQUIRED, FALSE);
      }
      else
      {
        if (pSource->NPAHandle != NULL)
        {
          npa_issue_scalar_request(pSource->NPAHandle, CLOCK_SOURCE_REQUIRED);
        }

        if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
        {
          VRegRequest.eVRegLevel = pSource->pActiveFreqConfig->eVRegLevel;
          VRegRequest.bSuppressible = FALSE;
          Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
        }
      }
    }

    /*
     * Increment the reference count.
     */
    pSource->nReferenceCount++;
  }

  /*-----------------------------------------------------------------------*/
  /* Process suppressible request.                                         */
  /*-----------------------------------------------------------------------*/

  else
  {
    if (pSource->nReferenceCountSuppressible == 0)
    {
      /*
       * If the source has a source, then recursively enable that.
       */
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
          (pSource->pSource != NULL))
      {
        eResult = Clock_EnableSourceInternal(pDrvCtxt, pSource->pSource, TRUE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * If the source is not already enabled by an insuppressible request
       * then enable it.  Use "0" for any NPA request to indicate
       * suppressible-based and that the source is not required. If there is
       * already an insuppressible reference count, then just update the voltage
       * request with the suppressible requirement.
       */
      if (pSource->nReferenceCount == 0)
      {
        Clock_SourceOn(
          pDrvCtxt, pSource, CLOCK_SOURCE_NOT_REQUIRED, TRUE);
      }
    }

    /*
     * Increment the reference count.
     */
    pSource->nReferenceCountSuppressible++;
  }

  return DAL_SUCCESS;

} /* END Clock_EnableSourceInternal */


/* =========================================================================
**  Function : Clock_DisableSourceInternal
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_DisableSourceInternal
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  boolean              bSuppressibleRequest,
  boolean              bDoNotDisable
)
{
  ClockVRegRequestType VRegRequest;
  DALResult eResult;

  /*-----------------------------------------------------------------------*/
  /* Make sure the source handle is valid.                                 */
  /*-----------------------------------------------------------------------*/

  if (pSource == NULL)
  {
    return DAL_ERROR;
  }

  bDoNotDisable = 
    bDoNotDisable || 
    CLOCK_FLAG_IS_SET(pSource, DO_NOT_DISABLE) ||
    CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_SOURCES);

  /*-----------------------------------------------------------------------*/
  /* Process insuppressible requests.                                      */
  /*-----------------------------------------------------------------------*/

  if (!bSuppressibleRequest)
  {
    /*
     * Decrement insuppressible reference count.
     */
    if (pSource->nReferenceCount > 0)
    {
      pSource->nReferenceCount--;
    }

    /*
     * If the count is zero and the DO_NOT_DISABLE bits aren't set, we can
     * disable the source.
     */
    if (pSource->nReferenceCount == 0)
    {
      if (!bDoNotDisable)
      {
        /*
         * If there is no suppressible reference count then disable the source.
         * If there are suppressible requests on this source then we just remove
         * the insuppressible requirement from the NPA state and voltage request.
         */
        if (pSource->nReferenceCountSuppressible == 0)
        {
          Clock_SourceOff(pDrvCtxt, pSource, FALSE);
        }
        else
        {
          if (pSource->NPAHandle != NULL)
          {
            npa_issue_scalar_request(
              pSource->NPAHandle, CLOCK_SOURCE_NOT_REQUIRED);
          }

          if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
          {
            VRegRequest.eVRegLevel = pSource->pActiveFreqConfig->eVRegLevel;
            VRegRequest.bSuppressible = TRUE;
            Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
          }
        }
      }

      /*
       * If the source has a source, then recursively disable that.
       */
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
          (pSource->pSource != NULL))
      {
        eResult = Clock_DisableSourceInternal(pDrvCtxt, pSource->pSource, FALSE, bDoNotDisable);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Process suppressible request.                                         */
  /*-----------------------------------------------------------------------*/

  else
  {
    if (pSource->nReferenceCountSuppressible > 0)
    {
      pSource->nReferenceCountSuppressible--;
    }

    if (pSource->nReferenceCountSuppressible == 0)
    {
      if (!bDoNotDisable)
      {
        /*
         * Disable the source if there aren't any insuppressible references. If
         * there is an insuppressible reference count, then just remove the 
         * suppressible voltage request.
         */
        if (pSource->nReferenceCount == 0)
        {
          Clock_SourceOff(pDrvCtxt, pSource, TRUE);
        }
      }

      /*
       * If the source has a source, then recursively remove the
       * suppressible request.
       */
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
          (pSource->pSource != NULL))
      {
        eResult = Clock_DisableSourceInternal(pDrvCtxt, pSource->pSource, TRUE, bDoNotDisable);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }
    }
  }

  return DAL_SUCCESS;

} /* END Clock_DisableSourceInternal */


/* =========================================================================
**  Function : Clock_ConfigSource
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_ConfigSource
(
  ClockDrvCtxt               *pDrvCtxt,
  ClockSourceNodeType        *pSource,
  ClockSourceFreqConfigType  *pConfig
)
{
  HAL_clk_SourceType         eSubSource;
  uint32                     nSubSourceIndex;
  ClockSourceFreqConfigType *pActiveFreqConfig;
  ClockVRegRequestType       VRegRequest;

  /*-----------------------------------------------------------------------*/
  /* Make sure the source handle is valid.                                 */
  /*-----------------------------------------------------------------------*/

  if (pSource == NULL || pConfig == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if this config is already active.                       */
  /*-----------------------------------------------------------------------*/

  if (pConfig == pSource->pActiveFreqConfig)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Make sure the new config contents are valid.                          */
  /*-----------------------------------------------------------------------*/

  eSubSource = pConfig->HALConfig.eSource;
  if (eSubSource >= HAL_CLK_NUM_OF_SOURCES)
  {
    return DAL_ERROR;
  }

  nSubSourceIndex = pDrvCtxt->anSourceIndex[eSubSource];
  if (nSubSourceIndex == 0xFF)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Check if this source supports slewing (dynamic configuration).        */
  /*-----------------------------------------------------------------------*/

  if ((pSource->nReferenceCount == 0) &&
      (pSource->nReferenceCountSuppressible == 0))
  {
    /*
     * Configure the PLL.
     */
    HAL_clk_ConfigPLL(pSource->eSource, &pConfig->HALConfig);
  }
  else
  {
    /*
     * We cannot configure a source while in use that doesn't support slewing.
     */
    if ((pSource->nFlags & CLOCK_FLAG_SUPPORTS_SLEWING) == 0)
    {
      return DAL_ERROR;
    }

    /*
     * We cannot slew between VCO's as this requires switch to away from source.
     */
    pActiveFreqConfig = pSource->pActiveFreqConfig;
    if (pConfig->HALConfig.eVCO != pSource->pActiveFreqConfig->HALConfig.eVCO)
    {
      return DAL_ERROR;
    }

    /*
     * Increase the voltage vote if the new config has a higher requirement.
     *
     * Do not make a voltage request if we've marked the source as having all
     * of its requirements managed by an outside agent.
     * We assume the source's voltage requirement is always satisfied.
     */
    if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
        (pConfig->eVRegLevel > pActiveFreqConfig->eVRegLevel))
    {
      VRegRequest.eVRegLevel = pConfig->eVRegLevel;
      VRegRequest.bSuppressible = pSource->VRegRequest.bSuppressible;
      Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
    }

    /*
     * Slew the PLL.
     */
    HAL_clk_SlewConfigPLL(pSource->eSource, &pConfig->HALConfig);
    
    /*
     * Decrease the voltage vote if the new config has a lower requirement.
     *
     * Do not make a voltage request if we've marked the source as having all
     * of its requirements managed by an outside agent.
     * We assume the source's voltage requirement is always satisfied.
     */
    if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES) &&
        (pConfig->eVRegLevel < pActiveFreqConfig->eVRegLevel))
    {
      VRegRequest.eVRegLevel = pConfig->eVRegLevel;
      VRegRequest.bSuppressible = pSource->VRegRequest.bSuppressible;
      Clock_VoltageRequest(pDrvCtxt, &pSource->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update state.                                                         */
  /*-----------------------------------------------------------------------*/

  pSource->pSource = &pDrvCtxt->aSources[nSubSourceIndex];
  pSource->pActiveFreqConfig = pConfig;

  /*-----------------------------------------------------------------------*/
  /* Log source config change.                                             */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pSource, LOG_FREQ_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_FREQ_CHANGE))
  {
    ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
                      "%s (Freq: %lu)",
                      pSource->szName, pConfig->nFreqHz);
  }

  return DAL_SUCCESS;

} /* END Clock_ConfigSource */



/* =========================================================================
**  Function : Clock_InitSource
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_InitSource
(
  ClockDrvCtxt       *pDrvCtxt,
  HAL_clk_SourceType  eSource,
  uint32              nFreqHz
)
{
  DALResult                   eResult;
  uint8                       nIndex;
  ClockSourceNodeType        *pSource;
  ClockSourceFreqConfigType  *pNewActiveConfig;

  /*-----------------------------------------------------------------------*/
  /* Verify configuration.                                                 */
  /*-----------------------------------------------------------------------*/

  if (eSource >= HAL_CLK_NUM_OF_SOURCES)
  {
    return DAL_ERROR;
  }

  nIndex = pDrvCtxt->anSourceIndex[eSource];

  if (nIndex == 0xFF)
  {
    return DAL_ERROR;
  }

  pSource = &pDrvCtxt->aSources[nIndex];

  if (pSource == NULL || pSource->pBSPConfig == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Use the first config in the BSP if the client didn't provide one.     */
  /*-----------------------------------------------------------------------*/

  if (nFreqHz == 0)
  {
    pNewActiveConfig = pSource->pBSPConfig->pSourceFreqConfig;
  }
  else
  {
    eResult =
      Clock_FindSourceConfig(
        pSource->pBSPConfig->pSourceFreqConfig,
        nFreqHz,
        CLOCK_FREQUENCY_HZ_EXACT,
        &pNewActiveConfig);

    if ((eResult != DAL_SUCCESS) || (pNewActiveConfig == NULL))
    {
      return DAL_ERROR;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Apply the new active source config.                                   */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_ConfigSource(pDrvCtxt, pSource, pNewActiveConfig);

  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure PLL parameters as well.                                     */
  /*-----------------------------------------------------------------------*/

  if (pSource->pBSPConfig->nConfigMask & CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
  {
    HAL_clk_ConfigSource(eSource, HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE);
  }

  if (pSource->pBSPConfig->nConfigMask & CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(eSource, HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE);
  }

  if (pSource->pBSPConfig->nConfigMask & CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(eSource, HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE);
  }

  if (pSource->pBSPConfig->nConfigMask & CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(eSource, HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE);
  }

  /*-----------------------------------------------------------------------*/
  /* Done.                                                                 */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitSource */


/* =========================================================================
**  Function : Clock_FindSourceConfig
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_FindSourceConfig
(
  ClockSourceFreqConfigType   *pBSPConfig,
  uint32                       nFreqHz,
  ClockFrequencyType           eMatch,
  ClockSourceFreqConfigType  **pMatchingConfig
)
{
  uint32                     nAtLeastFrequency = 0xFFFFFFFF;
  ClockSourceFreqConfigType *pAtLeastConfig = NULL;
  uint32                     nAtMostFrequency = 0;
  ClockSourceFreqConfigType *pAtMostConfig = NULL;

  /* Make sure the list of configurations isn't empty */
  if (pBSPConfig == NULL || pMatchingConfig == NULL)
  {
    return DAL_ERROR;
  }

  /* Loop over all configurations */
  while(pBSPConfig->nFreqHz != 0)
  {
    /* Stop if we find an exact match */
    if (pBSPConfig->nFreqHz == nFreqHz)
    {
      *pMatchingConfig = pBSPConfig;
      return DAL_SUCCESS;
    }

    /* Look for the lowest at-least frequency */
    if ((pBSPConfig->nFreqHz > nFreqHz) &&
        (pBSPConfig->nFreqHz < nAtLeastFrequency))
    {
      nAtLeastFrequency = pBSPConfig->nFreqHz;
      pAtLeastConfig = pBSPConfig;
    }
    /* Look for the highest at-most frequency */
    else if ((pBSPConfig->nFreqHz < nFreqHz) &&
             (pBSPConfig->nFreqHz > nAtMostFrequency))
    {
      nAtMostFrequency = pBSPConfig->nFreqHz;
      pAtMostConfig = pBSPConfig;
    }

    /* Move to the next configuration */
    pBSPConfig++;
  }

  /* Select a config based on the match criteria */
  switch (eMatch)
  {
    case CLOCK_FREQUENCY_HZ_AT_LEAST:
      if (pAtLeastConfig != NULL)
      {
        *pMatchingConfig = pAtLeastConfig;
        return DAL_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_AT_MOST:
      if (pAtMostConfig != NULL)
      {
        *pMatchingConfig = pAtMostConfig;
        return DAL_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_CLOSEST:
      if ((pAtLeastConfig != NULL) && (pAtMostConfig == NULL))
      {
        *pMatchingConfig = pAtLeastConfig;
        return DAL_SUCCESS;
      }
      else if ((pAtMostConfig != NULL) && (pAtLeastConfig == NULL))
      {
        *pMatchingConfig = pAtMostConfig;
        return DAL_SUCCESS;
      }
      else if ((pAtLeastConfig != NULL) && (pAtMostConfig != NULL))
      {
        /* Select the closest match, select the lowest in case of a tie */
        if ((nAtLeastFrequency - nFreqHz) < (nFreqHz - nAtMostFrequency))
        {
          *pMatchingConfig = pAtLeastConfig;
          return DAL_SUCCESS;
        }
        else
        {
          *pMatchingConfig = pAtMostConfig;
          return DAL_SUCCESS;
        }
      }
      break;

    default:
      break;
  }

  /* No match was found */
  *pMatchingConfig = NULL;

  return DAL_ERROR;

} /* END Clock_FindSourceConfig */

