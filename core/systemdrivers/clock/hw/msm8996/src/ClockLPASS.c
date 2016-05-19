/*
===========================================================================
*/
/**
  @file ClockLPASS.c 
  
  Main entry point for the MSM8996 LPASS clock driver.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8996/src/ClockLPASS.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  09/07/11   dcf     Created.
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "ClockLPASS.h"
#include "busywait.h"
#include "ClockSWEVT.h"
#include "ClockLPASSCPU.h"
#include "ClockLPASSHWIO.h"

/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/

extern void Clock_EnableSPMCTL(void);
extern void Clock_DisableSPMCTL(void);
uint32 Clock_nHWIOBaseLPASS;

/*=========================================================================
      Data
==========================================================================*/

static ClockLPASSCtxtType Clock_LPASSCtxt;
static ClockImageConfigType Clock_ImageConfig;

/* =========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_DetectQDSP6Config
** =========================================================================*/
/**
  Detects current configuration of QDSP6 clock
 
  This function is invoked at driver initialization to detect the current
  QDSP6 configuration.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.

  @return
  DAL_ERROR if configuration was not valid, other DAL_SUCCESS.

  @dependencies
  None.
*/ 

static DALResult Clock_DetectQDSP6Config
(
  ClockDrvCtxt    *pDrvCtxt
)
{
  uint32 nCfg;
  uint32 nDiv2x;
  uint32 nSrcIdx;
  ClockCPUConfigType *pCfg;
  ClockCPUConfigType **pClockCfg;
  HAL_clk_ClockMuxConfigType MuxCfg; 
  ClockNodeType *pClock;
  boolean bPerfFound = FALSE;

  /*-----------------------------------------------------------------------*/
  /* Get proper clock and configuration data                               */
  /*-----------------------------------------------------------------------*/

  pClock    = Clock_LPASSCtxt.QDSP6Ctxt.pQDSP6Clock;
  pClockCfg = &Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig;

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);  

  /*-----------------------------------------------------------------------*/
  /* Get the current hardware configuration.                               */
  /*-----------------------------------------------------------------------*/

  HAL_clk_DetectClockMuxConfig(pClock->pDomain->HALHandle, &MuxCfg);
  
  /*
   * If we got back divider of 0, set to 2 for comparison.
   */
  if ((MuxCfg.nDiv2x == 1) || (MuxCfg.nDiv2x == 0))
  {
    MuxCfg.nDiv2x = 2;
  }

  /*-----------------------------------------------------------------------*/
  /* Go through config array to find a matching configuration.             */
  /*-----------------------------------------------------------------------*/

  for (nCfg = 0; nCfg < Clock_LPASSCtxt.pImageConfig->nTotalSupportedConfigs; nCfg++)
  {
    pCfg = &Clock_LPASSCtxt.pImageConfig->pCPUConfig[nCfg];
    nDiv2x = pCfg->Mux.HALConfig.nDiv2x;
    if ((nDiv2x == 1) || (nDiv2x == 0))
    {    
        nDiv2x = 2;
    }

    if (MuxCfg.eSource  == pCfg->Mux.HALConfig.eSource &&
        MuxCfg.nDiv2x == nDiv2x)
    {
      bPerfFound = TRUE;
      break;
    }
  }

  if (FALSE == bPerfFound)
  {
    DALCLOCK_FREE(pDrvCtxt);  
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Update the clock node with the matched configuration.                 */
  /*-----------------------------------------------------------------------*/

  *pClockCfg = pCfg;

  pClock->pDomain->pActiveMuxConfig = &pCfg->Mux;

  nSrcIdx = pDrvCtxt->anSourceIndex[pCfg->Mux.HALConfig.eSource];

  if (nSrcIdx != 0xFF)
  {
    pClock->pDomain->pSource = &pDrvCtxt->aSources[nSrcIdx];
  }

  /*-----------------------------------------------------------------------*/
  /* Free.                                                                 */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_FREE(pDrvCtxt);  

  return DAL_SUCCESS;

}/* END Clock_DetectQDSP6Config */


/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_InitImage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult eRes;
  uint32 nMaxPL, nMaxQDSP6Config, nIdx, nSupportedIdx;
  ClockPropertyValueType PropVal = NULL;
  ClockImageConfigType *pImageCfg = NULL;
  ClockSourceInitType* pInitSources = NULL;
  HAL_clk_HWIOBaseType *pHWIOBases = NULL;
  uint32 anSourceIndex;

  /*-----------------------------------------------------------------------*/
  /* Get the CPU Configurations.                                           */
  /*-----------------------------------------------------------------------*/

  if(DAL_SUCCESS != Clock_GetPropertyValue("ClockImageConfig", &PropVal))
  {
    return(DAL_ERROR);
  }

  pImageCfg = (ClockImageConfigType*)PropVal;
  nSupportedIdx = 0;

  if (pImageCfg != NULL)
  {
    /* 
     * Get the number of supported configs on this chipset.
     */
    for (nIdx = 0; nIdx < pImageCfg->pCPUPerfConfig->nTotalConfigs; nIdx++)
    {
      if (Clock_IsBSPSupported(&pImageCfg->pCPUConfig[nIdx].Mux.HWVersion))
      {
        nSupportedIdx++;
      }
    }

    if (nSupportedIdx == 0)
    {
      return(DAL_ERROR);
    }

    Clock_LPASSCtxt.pImageConfig = &Clock_ImageConfig;

    eRes = DALSYS_Malloc(sizeof(ClockCPUConfigType)*nSupportedIdx, (void **)&Clock_LPASSCtxt.pImageConfig->pCPUConfig);

    if (eRes != DAL_SUCCESS) 
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate pImageConfig buffer for Q6 clock controller.");
      return eRes;
    }
    memset(Clock_LPASSCtxt.pImageConfig->pCPUConfig, 0, sizeof(ClockCPUConfigType)*nSupportedIdx);

    nSupportedIdx = 0;

    /* 
     * Add each supported configuration into the new CPU configuration array.
     */
    for (nIdx=0; nIdx < pImageCfg->pCPUPerfConfig->nTotalConfigs; nIdx++)
    {
      if (Clock_IsBSPSupported(&pImageCfg->pCPUConfig[nIdx].Mux.HWVersion))
      {
        Clock_LPASSCtxt.pImageConfig->pCPUConfig[nSupportedIdx] = pImageCfg->pCPUConfig[nIdx];
        nSupportedIdx++;
      }
    }
  }
  else
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to get QDSP6 Image Configuration information from the BSP!.");
    return(DAL_ERROR);
  }

  /* 
   * Fill in remaining fields from the BSP here.
   */
  Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig = pImageCfg->pCPUPerfConfig;
  Clock_LPASSCtxt.pImageConfig->nTotalSupportedConfigs  = nSupportedIdx;
  Clock_LPASSCtxt.pImageConfig->bGlobalLDOEnable = pImageCfg->bGlobalLDOEnable;
  Clock_LPASSCtxt.pImageConfig->bIsFusionMDM = pImageCfg->bIsFusionMDM;
  Clock_LPASSCtxt.pImageConfig->pIntermediateCPUConfig = pImageCfg->pIntermediateCPUConfig;


  /*-----------------------------------------------------------------------*/
  /* Initialize the Q6SS HWIO Base address.                                */
  /*-----------------------------------------------------------------------*/

  if(Clock_nHWIOBaseLPASS == 0)
  {
    eRes = Clock_GetPropertyValue("ClockLDOBase", &PropVal);

    if (eRes != DAL_SUCCESS)
    {
      return(eRes);
    }

    pHWIOBases = (HAL_clk_HWIOBaseType*)PropVal;

    if (pHWIOBases != NULL)
    {
      Clock_MapHWIORegion(
        pHWIOBases->nPhysAddr, pHWIOBases->nSize, &Clock_nHWIOBaseLPASS);

      /*
       * If we are unable to map a virtual address, assume the physical one.
       */
      if(Clock_nHWIOBaseLPASS == NULL)
      {
        Clock_nHWIOBaseLPASS = pHWIOBases->nPhysAddr;
      }
    }
    else
    {
      /*
       * We were unable to get the base address.
       */
      return(DAL_ERROR);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get QDSP6 core/cpu clock ID.                                          */
  /*-----------------------------------------------------------------------*/

  eRes =
    Clock_GetClockId(
      pDrvCtxt, "lpass_q6core",
      (ClockIdType *)&Clock_LPASSCtxt.QDSP6Ctxt.pQDSP6Clock);

  if (eRes != DAL_SUCCESS) 
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to get Q6LPASS core clock ID.");
    return eRes;

  }

  /*
   * Increase the reference count on the LPAPLL2 to ensure Q6 clock 
   * switching does not disable the PLL that the bus is currently on. 
   */
  anSourceIndex = pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_LPAPLL2];
  pDrvCtxt->aSources[anSourceIndex].nReferenceCountSuppressible++;

  pDrvCtxt->pImageCtxt = &Clock_LPASSCtxt;

  /*-----------------------------------------------------------------------*/
  /* Detect initial QDSP6 core clock frequency configuration.              */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_DetectQDSP6Config(pDrvCtxt);

  if (eRes != DAL_SUCCESS) 
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to detect Q6LPASS core clock configuration.");
    return eRes;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the Q6PLL if applicable to this chipset.                   */
  /*-----------------------------------------------------------------------*/

  if(DAL_SUCCESS == Clock_GetPropertyValue("ClockSourcesToInit", &PropVal))
  {
    pInitSources = (ClockSourceInitType*)PropVal;

    if (pInitSources != NULL)
    {
      nIdx = 0;
      while (pInitSources[nIdx].eSource != HAL_CLK_SOURCE_NULL)
      {
        Clock_InitSource(pDrvCtxt,
                         pInitSources[nIdx].eSource,
                         pInitSources[nIdx].nFreqHz);
        nIdx++;
      }
    }
  }

  nIdx = pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_LPAPLL2];
  pDrvCtxt->aSources[nIdx].pActiveFreqConfig = 
    pDrvCtxt->aSources[nIdx].pBSPConfig->pSourceFreqConfig;


  /*-----------------------------------------------------------------------*/
  /* Ensure that the Q6LPASS clock/domain/source reference counts are '1'. */
  /*-----------------------------------------------------------------------*/

  Clock_EnableClock(pDrvCtxt, 
    (ClockIdType)Clock_LPASSCtxt.QDSP6Ctxt.pQDSP6Clock);


  /*-----------------------------------------------------------------------*/
  /* Run QDSP6 at max performance level - if DCVS is enable then we'll     */
  /* go to lower performance level later.                                  */
  /*-----------------------------------------------------------------------*/

  nMaxPL = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->nInitPerfLevel;

  /* 
   * Configure the PLL to one less than max for low power initialization.
   */

  nMaxQDSP6Config = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->panPerfLevel[nMaxPL];
 

  if (Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig != 
        &Clock_LPASSCtxt.pImageConfig->pCPUConfig[nMaxQDSP6Config])
  {
    Clock_SetQDSP6Config(
      pDrvCtxt, &Clock_LPASSCtxt.pImageConfig->pCPUConfig[nMaxQDSP6Config]);
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the DCVS module.                                           */
  /*-----------------------------------------------------------------------*/

  Clock_InitDCVS(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Initialize the XO module.                                             */
  /*-----------------------------------------------------------------------*/

  Clock_InitXO(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Now that NPA is initialized, allow Q6 scaling by the power manager.   */
  /*-----------------------------------------------------------------------*/

  Clock_EnableDCVS(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Initialize the NPA Voltage NPA node.                                  */
  /*-----------------------------------------------------------------------*/

  Clock_InitVdd(pDrvCtxt);

  /*
   * Decrease the reference count on the LPAPLL2 to ensure Q6 clock 
   * switching does not disable the PLL that the bus is currently on. 
   */
  anSourceIndex = pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_LPAPLL2];
  pDrvCtxt->aSources[anSourceIndex].nReferenceCountSuppressible--;

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitImage */


/* =========================================================================
**  Function : Clock_ProcessorSleep
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ProcessorSleep
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockSleepModeType  eMode,
  uint32              nFlags
)
{

  return DAL_SUCCESS;

} /* END Clock_ProcessorSleep */


/* =========================================================================
**  Function : Clock_ProcessorRestore
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ProcessorRestore
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockSleepModeType  eMode,
  uint32              nFlags
) 
{

  /*
   * Nothing to do here. HW_VOTE does SPMCTL override handling.
  */

  return DAL_SUCCESS;

} /* END Clock_ProcessorRestore */


/* =========================================================================
**  Function : Clock_SetCPUMaxFrequencyAtCurrentVoltage
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetCPUMaxFrequencyAtCurrentVoltage
(
  ClockDrvCtxt *pDrvCtxt,
  boolean      bRequired,
  uint32       *pnResultFreqHz
)
{
  DALResult            eRes;
  uint32               nMinPL, nMaxPL, nPL, nCfg;
  ClockVRegLevelType   eVReg;
  ClockCPUConfigType *pQDSP6Config = Clock_LPASSCtxt.pImageConfig->pCPUConfig;
  HAL_clk_SourceType eSource;

  nMinPL = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->nMinPerfLevel;
  nMaxPL = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->nMaxPerfLevel;

  if (TRUE == bRequired)
  {
    /*
     * Find the highest frequency configuration supported by the clock driver's
     * current vote (suppressible and non-suppressible) on the power rail.
     */

    eVReg = Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig->Mux.eVRegLevel;
    eSource = Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig->Mux.HALConfig.eSource;

    /*
     * Start with the max PL and move down from there to find a match 
     * with the voltage and source. 
     */
    for (nPL = nMaxPL; nPL > nMinPL; nPL--)
    {
      nCfg = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->panPerfLevel[nPL];

      if ((pQDSP6Config[nCfg].Mux.eVRegLevel == eVReg) &&
          (pQDSP6Config[nCfg].Mux.HALConfig.eSource == eSource))
      {
        break;
      }
    }

    /*
     * No frequency was found.  Return the current frequency.
     */
    if (nPL == nMinPL)
    {
      if(pnResultFreqHz != NULL)
      {
        *pnResultFreqHz = Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig->Mux.nFreqHz;
      }
      return(DAL_SUCCESS);
    }

    nCfg = Clock_LPASSCtxt.pImageConfig->pCPUPerfConfig->panPerfLevel[nPL];

    /*
     * Configure the Q6 to the desired performance level if different
     * from current configuration.
     */
    if (Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig != &pQDSP6Config[nCfg])
    {
      Clock_SetQDSP6Config(pDrvCtxt, &pQDSP6Config[nCfg]);

      /*
       * Overwrite the active state of the NPA node.
       */
      eRes = Clock_NPACPUResourceOverwriteActiveState(
        (npa_resource_state)pQDSP6Config[nCfg].Mux.nFreqHz/1000);

      if (eRes != DAL_SUCCESS)
      {
        if (pnResultFreqHz != NULL)
        {
          *pnResultFreqHz = Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig->Mux.nFreqHz;
        }

        return DAL_ERROR_INTERNAL;
      }
    }

    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = Clock_LPASSCtxt.QDSP6Ctxt.pCPUConfig->Mux.nFreqHz;
    }
    
    return DAL_SUCCESS;
  }
  else
  {
    /*
     * The max CPU at current voltage level is no longer required.  We can 
     * request that NPA re-aggregate the CPU requests. 
     */
    if (Clock_LPASSCtxt.QDSP6Ctxt.NPAImpulseHandle != NULL)
    {
      npa_issue_impulse_request( Clock_LPASSCtxt.QDSP6Ctxt.NPAImpulseHandle );
    }
  }

  return DAL_SUCCESS;

} /* END Clock_SetCPUMaxFrequencyAtCurrentVoltage */


/* =========================================================================
**  Function : Clock_AdjustSourceFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/
DALResult Clock_AdjustSourceFrequency
(
   ClockDrvCtxt    *pDrvCtxt,
   ClockSourceType eSource,
   int32           nDeltaLAlpha
)
{
  return(DAL_ERROR);

} /* Clock_AdjustSourceFrequency */


DALResult Clock_SelectClockSource
(
   ClockDrvCtxt    *pDrvCtxt,
   ClockIdType     nClock,
   ClockSourceType eSource
)
{

  if(eSource == CLOCK_SOURCE_PRIMARY)
  {
    return(DAL_SUCCESS);
  }
  return(DAL_ERROR);

} /* Clock_SelectClockSource */


/* =========================================================================
**  Function : Clock_GetImageCtxt
** =========================================================================*/
/*
  See ClockLPASS.h
*/

ClockLPASSCtxtType* Clock_GetImageCtxt(void)
{
  return(&Clock_LPASSCtxt);
}

/*
 * Unused APIs are stubbed out here.
 */

DALResult Clock_ImageBIST
(
  ClockDrvCtxt  *pDrvCtxt,
  boolean       *bBISTPassed,
  uint32        *nFailedTests
)
{
  return(DAL_ERROR);
}

DALResult Clock_LoadNV
(
  ClockDrvCtxt  *pDrvCtxt
)
{
  return(DAL_ERROR_NOT_SUPPORTED);
}


