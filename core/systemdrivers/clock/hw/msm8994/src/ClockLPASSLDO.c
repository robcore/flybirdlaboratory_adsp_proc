/*
===========================================================================
*/
/**
  @file ClockLPASSLDO.c 
  
  The file contains the resource definitions for LDO voltage scaling on
  supported chipsets of the Low Power Audio Subsystem processor.
*/
/*  
  ====================================================================

  Copyright (c) 2012 - 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8994/src/ClockLPASSLDO.c#2 $
  $DateTime: 2014/11/23 10:17:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/12/12   dcf     Created for LPASS on 8974.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include "ClockLPASS.h"
#include "ClockLPASSLDO.h"
#include "ClockLPASSLDOHWIO.h"
#include "busywait.h"
#include "kvp.h"
#include "rpmclient.h"
#include "npa_transaction.h"
#include "DDIChipInfo.h"


/*=========================================================================
      Function Prototypes
==========================================================================*/


/*=========================================================================
      Internal type definitions 
==========================================================================*/

typedef struct
{
  const uint32 nSVS2;
  const uint32 nSVS;
  uint32 nLDOVoltageUV;
  uint32 nHeadroom;
  boolean bIsSufficient;
  boolean bInitialized;
}ClockLDOStateType;
   

/*=========================================================================
      Global Variables
==========================================================================*/

static boolean bLDOInited = FALSE;
uint32 Clock_nHWIOBaseLPASS;
uint32 Clock_nHWIOBaseSecurity;
static npa_transaction_handle ghNPATransaction = NULL;
static uint32 gnCurrentvoltage = 0;
static uint32 gnSVSTarget = 0;

ClockLDOStateType ClockLDOState = 
{
  /* .nSVS2         = */ 725 * 1000,
  /* .nSVS          = */ 800 * 1000,
  /* .nLDOVoltageUV = */ 0,
  /* .nHeadroom     = */ 20 * 1000,
  /* .bIsSufficient = */ FALSE,
  /* .bInitialize   = */ FALSE
};


/*=========================================================================
      Macros
==========================================================================*/

/*
 * Min/Max voltage values for the LDO operation range.
 * These voltages need to be converted to LDO reg format when programmed.
 */
#define CLOCK_LDO_VREF_MIN_UV  345 * 1000
#define CLOCK_LDO_VREF_MAX_UV  980 * 1000

/*
 * LDO voltage delta.
 */
#define CLOCK_LDO_DELTA(val1, val2)                                            \
  ((val1)>(val2)?(val1)-(val2):(val2)-(val1))

/*
 * LDO range checker.
 */
#define CLOCK_LDO_IN_RANGE(x)                                                  \
  ( ((x) >=CLOCK_LDO_VREF_MIN_UV) && ((x) <= CLOCK_LDO_VREF_MAX_UV) )

/*
 * LDO uV to LDO_REF register format.
 */
#define CLOCK_LDO_UV_MAP_TO_HW(x)                                              \
  ( ( ( (x) - CLOCK_LDO_VREF_MIN_UV ) / 1000 ) / 5 ) + 1

/*
 * Set wait time to the equivalent of 5 us per 10 mV.
 * This value is expected to change when data becomes available.
 */
#define CLOCK_LDO_SETTLE_DELAY(start, end)                                     \
  DALSYS_BusyWait(5 * ( ( ( CLOCK_LDO_DELTA(start, end) + (10000 - 1) ) / 10000) ) )


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_DetectEFuseSetting
** =========================================================================*/
/**
  Read LDO Trimmed Info

  This function will read an efuse field to detect whether the LDO has
  been trimmed and is safe to enable the LDO output.

  @return
  None.

  @dependencies
  None.
*/
static void Clock_DetectLDOEFuse
(
  ClockDrvCtxt  *pDrvCtxt
)
{
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Read EFuse to determine whether LDO should be enabled or not.         */
  /*-----------------------------------------------------------------------*/
  if(HWIO_INF(QFPROM_RAW_CALIB_ROW1_MSB, Q6SS1_LDO_ENABLE) != 0)
  {
    if((ClockLDOState.bInitialized == TRUE) && (ClockLDOState.bIsSufficient == FALSE))
    {
      pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;
    }
    else if((ClockLDOState.bInitialized == TRUE) && (ClockLDOState.bIsSufficient == TRUE))
    {
      pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = TRUE;
    }
    else
    {
      /*
       * If LDO initialization has not taken place, get the value from EFUSE and
       * store the SVS2 value accordingly.
       */
      if(ClockLDOState.bInitialized == FALSE)
      {
        gnSVSTarget = HWIO_INF(QFPROM_RAW_SPARE_REG28_ROW1_LSB, CPR0_TARG_VOLT_SVS);
        ClockLDOState.bInitialized = TRUE;

        if((gnSVSTarget & 0xF) != 0)
        {
          ClockLDOState.nLDOVoltageUV =
            (ClockLDOState.nSVS  - (((gnSVSTarget & 0xF) * 10000) + ClockLDOState.nHeadroom));
        }
        else
        {
          ClockLDOState.bIsSufficient = FALSE;
          pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;
          return;
        }

        if(ClockLDOState.nLDOVoltageUV < ClockLDOState.nSVS)
        {
          ClockLDOState.bIsSufficient = TRUE;
          pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = TRUE;
        }
        else
        {
          ClockLDOState.bIsSufficient = FALSE;
          pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;
        }
      }
    }
  }
  else
  {
    pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;
  }

} /* Clock_DetectLDOEFuse */


/* =========================================================================
**  Function : Clock_IsBHSMode
** =========================================================================*/
/**
  Specifies if the Q6 is currently running in BHS mode.
 
  This function is used to determine if the state of the Q6 is running under
  BHS mode.

  @return
  TRUE  - The Q6 is in BHS mode.
  FALSE - The Q6 is in LDO mode.

  @dependencies
  None.
*/ 
boolean Clock_IsBHSMode(void)
{
    if(HWIO_IN(LPASS_QDSP6SS_PWR_CTL) & HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK)
    {
      return(TRUE);
    }

  return(FALSE);

} /* Clock_IsBHSMode */


/* =========================================================================
**  Function : Clock_SendCPRNotification
** =========================================================================*/
/**
  Issues a notification to CPR that we are entering BHS or LDO mode.
 
  This function sends an asynchronous notification to the RPM that the
  Q6SS is entering BHS or LDO mode in order to enable/disable the associated
  CPR sensor.
 
  @param bEnterLDO -- TRUE if we're entering LDO mode, FALSE for BHS.

  @return
  NULL

  @dependencies
  None.
*/ 
void Clock_SendCPRNotification
(
   boolean bEnterLDO,
   boolean bBarrier
)
{
  unsigned nDisableSensor = 0;
  unsigned nLastMessageId = 0;

  /* 
   * Initialize the kvp request object.
   */
  kvp_t *pActiveRequest = kvp_create(0);

  if(TRUE == bEnterLDO)
  {
    nDisableSensor = 1;
  }
  
  /* 
   * Make the request to enable/disable the sensor.
   */
  kvp_put(pActiveRequest, 0, sizeof(unsigned), &nDisableSensor);
  
  /* 
   * Post the request to the RPM.
   */
  nLastMessageId = rpm_post_request(RPM_ACTIVE_SET, RPM_RBCPR_REQ, 0, pActiveRequest);

  /*
   * Only barrier if the CPR request is the only outgoing request.
   */
  if(TRUE == bBarrier)
  {
    rpm_barrier(nLastMessageId);
  }

  /*
   * Release the active request resource.
   */
  kvp_destroy(pActiveRequest);

} /* Clock_SendCPRNotification */


/* =========================================================================
**  Function : Clock_SendRPMNotification
** =========================================================================*/
/**
  Handles RPM transactions when switching between voltage corners and
  issuing CPR notifications.
 
  This function handles all necessary transactions to the RPM when switching
  to the LDO or to BHS.
 
  @param pDrvCtxt     -- The Driver Context.
  @param pConfig      -- The new clock config which will be programmed.
  @param bSwitchToLDO -- TRUE if we're entering LDO mode, FALSE for BHS.

  @return
  None.

  @dependencies
  Assumes the NPA transaction handle has been initialized in order to function.
*/ 
static void Clock_SendRPMNotification
(
   ClockDrvCtxt         *pDrvCtxt,
   ClockCPUConfigType   *pConfig,
   ClockVRegRequestType *pVRegRequest,
   boolean              bSwitchToLDO
)
{
  boolean bRequiresCornerVote = FALSE;
  ClockLPASSCtxtType *pLPASSQ6Config = (ClockLPASSCtxtType*)pDrvCtxt->pImageCtxt;
  ClockNodeType *pClock = pLPASSQ6Config->QDSP6Ctxt.pQDSP6Clock;

  if(pLPASSQ6Config->QDSP6Ctxt.QDSP6SavedConfig.pCPUConfig->Mux.eVRegLevel != 
       pConfig->Mux.eVRegLevel)
  {
    bRequiresCornerVote = TRUE;
  }

  if(TRUE == bRequiresCornerVote)
  {
    if(ghNPATransaction != NULL)
    {
      /*
       * Issue a start transfer to NPA.
       */
      npa_begin_transaction( ghNPATransaction );
      
      if(bSwitchToLDO == Clock_IsBHSMode())
      {
        Clock_SendCPRNotification(bSwitchToLDO, FALSE);
      }

      Clock_VoltageRequest(pDrvCtxt, &pClock->pDomain->VRegRequest, pVRegRequest);

      npa_end_transaction( ghNPATransaction );
    }
  }
  else
  {
    if(bSwitchToLDO == Clock_IsBHSMode())
    {
      Clock_SendCPRNotification(bSwitchToLDO, TRUE);
    }
  }

} /* Clock_SendRPMNotification */


/* =========================================================================
**  Function : Clock_SwitchToBHS
** =========================================================================*/
/**
  Switches to using BHS mode.
 
  This function is used to switch to BHS mode.

  @return
  None.

  @dependencies
  Assumes the subsystem is in LDO mode.
*/ 
static void Clock_SwitchToBHS(ClockDrvCtxt *pDrvCtxt)
{

  uint32 nQ6PowerCtl = HWIO_IN(LPASS_QDSP6SS_PWR_CTL);

  /*
   * Turn on BHS from LDO mode.
   */
   
  nQ6PowerCtl |= HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK;
  HWIO_OUT(LPASS_QDSP6SS_PWR_CTL, nQ6PowerCtl);
  busywait(5);  

  /*
   * Put LDO in bypass.
   */

  nQ6PowerCtl |= HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK;
  HWIO_OUT(LPASS_QDSP6SS_PWR_CTL, nQ6PowerCtl);

  /*
   * Turn off LDO.  Leave BG_UP enabled to allow fast switching.
   * Estimated power leakage is 150 uA in BHS mode.
   */

  nQ6PowerCtl &= ~HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK;
  HWIO_OUT(LPASS_QDSP6SS_PWR_CTL, nQ6PowerCtl);


  if(pDrvCtxt->hClockLog)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockLog,
                          "Clock LDO Enablement:  Switched to BHS mode.");
  }

} /* Clock_SwitchToBHS */


/* =========================================================================
**  Function : Clock_SwitchToLDO
** =========================================================================*/
/**
  Switches to using LDO mode.
 
  This function is used to switch to LDO mode.

  @return
  None.

  @dependencies
  None.
*/
static void Clock_SwitchToLDO(ClockDrvCtxt *pDrvCtxt)
{
  uint32 nQ6PowerCtl = HWIO_IN(LPASS_QDSP6SS_PWR_CTL);
  uint32 nLDOCTL1Val;

  /*
   * Set the mode bit before switching to LDO mode from BHS.
   */

  nLDOCTL1Val = 
    ((HWIO_IN(LPASS_QDSP6SS_LDO_CFG0) & HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_BMSK) >> \
              HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_SHFT);
  nLDOCTL1Val |= 0x80;
  HWIO_OUTF(LPASS_QDSP6SS_LDO_CFG0, LDO_CTL1, nLDOCTL1Val);

  /*
   * Turn on LDO by setting LDO_BG_UP and LDO_PWR_UP.  Wait for a few us. 
   * LDO_BG_UP will be left on to allow fast switching between LDO and BHS. 
   */

  nQ6PowerCtl &= ~HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK;

  nQ6PowerCtl |= (0x1 << HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT);

  HWIO_OUT(LPASS_QDSP6SS_PWR_CTL, nQ6PowerCtl);

  DALSYS_BusyWait(10);

  /*
   * Turn off BHS and LDO Bypass.
   */

  nQ6PowerCtl &= ~(HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK | \
      HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK);

  HWIO_OUT(LPASS_QDSP6SS_PWR_CTL, nQ6PowerCtl);

  /*
   * Clear the mode bit after switching to LDO mode from BHS.
   */

  nLDOCTL1Val &= ~0x80;
  HWIO_OUTF(LPASS_QDSP6SS_LDO_CFG0, LDO_CTL1, nLDOCTL1Val);

  if(pDrvCtxt->hClockLog)
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                          "Clock LDO Enablement:  Switched to LDO mode.  Voltage: %d uv.", gnCurrentvoltage);
  }

} /* Clock_SwitchToLDO */


/* =========================================================================
**  Function : Clock_InitLDOVoltage
** =========================================================================*/
/*
  See ClockLPASSLDO.h
*/ 
DALResult Clock_InitLDOVoltage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  ClockPropertyValueType PropVal = NULL;
  ClockLDODataType *pLDOData = NULL;
  HAL_clk_HWIOBaseType *pHWIOBases = NULL;
  ClockLPASSCtxtType *pLPASSCtxt = (ClockLPASSCtxtType *)pDrvCtxt->pImageCtxt;
  const char *paNPAResources[] = { CLOCK_PMIC_RESOURCE_VDD_DIG }; 

  if(FALSE == bLDOInited)
  {
    /* 
     * Get a pointer to the LPASS_BASE address.
     */
    if(Clock_nHWIOBaseLPASS == 0)
    {
      eResult = Clock_GetPropertyValue("ClockLDOBase", &PropVal);

      if (eResult != DAL_SUCCESS)
      {
        return(eResult);
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

    /* 
     * Attempt to get a pointer to the SECURITY_CONTROL_BASE address. 
     * If not supported or unavailable, eLDO will not be allowed to operate. 
     */
    eResult = Clock_GetPropertyValue("ClockSecBase", &PropVal);

    pHWIOBases = (HAL_clk_HWIOBaseType*)PropVal;

    if (pHWIOBases != NULL)
    {
      Clock_MapHWIORegion(
        pHWIOBases->nPhysAddr, pHWIOBases->nSize, &Clock_nHWIOBaseSecurity);

      /*
       * If we are unable to map a virtual address, assume the physical one.
       */
      if(Clock_nHWIOBaseSecurity == NULL)
      {
        Clock_nHWIOBaseSecurity = pHWIOBases->nPhysAddr;
      }

      /*
       * Read the EFuse to determine whether LDO output should be allowed.
       */
      Clock_DetectLDOEFuse(pDrvCtxt);
    }
    else
    {
      /*
       * We were unable to get the SECURITY_CONTROL base address so 
       * assume EFUSE is not available.
       */
      pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;
    }

    /* 
     * Get a pointer to the LDO BSP data.
     */
    eResult = Clock_GetPropertyValue("ClockLDOData", &PropVal);

    if (eResult != DAL_SUCCESS)
    {
      return(eResult);
    }

    pLDOData = (ClockLDODataType*)PropVal;

    /*
     * Ensure we're in BHS mode before setting up the LDO config.
     */
    if(FALSE == Clock_IsBHSMode())
    {
      Clock_SwitchToBHS(pDrvCtxt);
    }

    /*
     * Program the LDO_CFG registers per recommendation from HW.
     */
    HWIO_OUT(LPASS_QDSP6SS_LDO_CFG0, pLDOData->nLDOCFG0);
    HWIO_OUT(LPASS_QDSP6SS_LDO_CFG1, pLDOData->nLDOCFG1);
    HWIO_OUT(LPASS_QDSP6SS_LDO_CFG2, pLDOData->nLDOCFG2);

    /*
     * Program the OSC_CTL to configure LDO fast loop strength.
     */
    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_TEST_CFG, OSC_CTL, 0x60);

    /*
     * Program the retention voltage and operating voltage based on the BSP.
    */
    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_SET, VREF_RET, 
              CLOCK_LDO_UV_MAP_TO_HW(pLDOData->nRetentionVoltage));

    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_SET, VREF_LDO, 
              CLOCK_LDO_UV_MAP_TO_HW(pLDOData->nOperatingVoltage));

    bLDOInited = TRUE;
  }

  /*
   * Initialize the NPA Transaction handle.
   */
   ghNPATransaction = npa_define_transaction(
                              "ClockLDOTransactions",
                              NPA_TRANSACTION_LAZY_LOCKING,
                              1,
                              paNPAResources );

   if(ghNPATransaction == NULL)
   {
     return(DAL_ERROR);
   }

  return(DAL_SUCCESS);

} /* Clock_InitLDOVoltage */


/* =========================================================================
**  Function : Clock_SetLDOVoltage
** =========================================================================*/
/*
  See ClockLPASSLDO.h
*/ 
DALResult Clock_SetLDOVoltage
(
  ClockDrvCtxt         *pDrvCtxt,
  ClockCPUConfigType   *pConfig,
  ClockVRegRequestType *pVRegRequest
)
{
  DALResult eResult = DAL_ERROR;
  uint32 nLDOVddData = 0;
  ClockLPASSCtxtType *pLPASSQ6Config = (ClockLPASSCtxtType*)pDrvCtxt->pImageCtxt;
  boolean bInBHSMode = Clock_IsBHSMode();
  ClockNodeType *pClock = pLPASSQ6Config->QDSP6Ctxt.pQDSP6Clock;

  if(pConfig == NULL)
  {
     return(DAL_ERROR);
  }

  /*
   * If the requested voltage is not supported, switch to BHS and make the 
   * voltage request accordingly. 
   */
  if((pConfig->nLDOQ6UV == 0) ||
     (FALSE == pLPASSQ6Config->pImageConfig->bLDOSupportedByEFuse))
  {
    if(FALSE == bInBHSMode)
    {
      /* 
       * Issue a notification to CPR that we are switching to BHS mode.
       */
      Clock_SendRPMNotification(pDrvCtxt, pConfig, pVRegRequest, FALSE);

      /*
       * Switch to BHS mode.
       */
      Clock_SwitchToBHS(pDrvCtxt);
    }
    else
    {
      Clock_VoltageRequest(pDrvCtxt, &pClock->pDomain->VRegRequest, pVRegRequest);
    }

    return DAL_SUCCESS;
  }

  /*
   * Here we can assume that the caller has enabled the LDO feature before 
   * requesting an LDO update, so ensure that the NPA node and the feature 
   * have been initialized. 
   */
  if(TRUE == bLDOInited)
  {
    Clock_SendRPMNotification(pDrvCtxt, pConfig, pVRegRequest, TRUE);

    gnCurrentvoltage = ClockLDOState.nLDOVoltageUV;
    /*
     * Program the new voltage data to the LDO VREF register and
     * switch to LDO mode. 
     */
    nLDOVddData = CLOCK_LDO_UV_MAP_TO_HW(ClockLDOState.nLDOVoltageUV);

    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_SET, VREF_LDO, nLDOVddData);

    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_SET, LDO_VREF_SEL, 0x0);

    HWIO_OUTF(LPASS_QDSP6SS_LDO_VREF_SET, LDO_VREF_SEL_RST, 0x0);

    HWIO_OUT(LPASS_QDSP6SS_LDO_VREF_CMD, 0x1);

    if(TRUE == bInBHSMode)
    {
      Clock_SwitchToLDO(pDrvCtxt);
    }

    /*
     * Wait for voltage to settle.
     */
    CLOCK_LDO_SETTLE_DELAY(ClockLDOState.nLDOVoltageUV, pLPASSQ6Config->QDSP6Ctxt.pCPUConfig->nVDDCPU);

    if(pDrvCtxt->hClockLog)
    {
      ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
          "  Clock LDO:  Set eLDO voltage to %d, based on data read of %x:  LDO mode operating now.",
          ClockLDOState.nLDOVoltageUV, gnSVSTarget);
    }

    eResult = DAL_SUCCESS;

    return(eResult);
  }
  else
  {
    return(DAL_ERROR);
  }

} /* Clock_SetLDOVoltage */


/* =========================================================================
**  Function : Clock_EnableLDO
** =========================================================================*/
/*
  See ClockLPASSLDO.h
*/ 
void Clock_EnableLDO
(
   ClockDrvCtxt* pDrvCtxt
)
{
  ClockLPASSCtxtType * pLPASSCtxt = (ClockLPASSCtxtType*)pDrvCtxt->pImageCtxt;

  if(FALSE == pLPASSCtxt->pImageConfig->bGlobalLDOEnable)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt); 

  /*
   * Re-initialize the enable flag based on eFuse setting.
   */
  Clock_DetectLDOEFuse(pDrvCtxt);

  /*
   * Set back the LDO configuration if necessary, sending RPM notification 
   * as required.
   */
  Clock_SetLDOVoltage(pDrvCtxt, 
                      pLPASSCtxt->QDSP6Ctxt.pCPUConfig, 
                      &pLPASSCtxt->QDSP6Ctxt.pQDSP6Clock->pDomain->VRegRequest);

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_FREE(pDrvCtxt); 


}/* Clock_EnableLDO */


/* =========================================================================
**  Function : Clock_DisableLDO
** =========================================================================*/
/*
  See ClockLPASSLDO.h
*/
void Clock_DisableLDO
(
   ClockDrvCtxt* pDrvCtxt
)
{
  boolean bIsInBHS = TRUE;
  ClockLPASSCtxtType * pLPASSCtxt = (ClockLPASSCtxtType*)pDrvCtxt->pImageCtxt;
  ClockNodeType *pClock = pLPASSCtxt->QDSP6Ctxt.pQDSP6Clock;

  if(FALSE == pLPASSCtxt->pImageConfig->bGlobalLDOEnable)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt); 

  bIsInBHS = Clock_IsBHSMode();

  /*
   * Disable the functionality to use the LDO.
   */
  pLPASSCtxt->pImageConfig->bLDOSupportedByEFuse = FALSE;

  /*
   * If we're currently in LDO mode, switch to BHS and send an RPM notification.
   */
  if(FALSE == bIsInBHS)
  {
    Clock_SwitchToBHS(pDrvCtxt);

    Clock_SendRPMNotification(pDrvCtxt, 
                              pLPASSCtxt->QDSP6Ctxt.pCPUConfig, 
                              &pClock->pDomain->VRegRequest, 
                              FALSE);
  }

  /*-----------------------------------------------------------------------*/
  /* Thread safety.                                                        */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_FREE(pDrvCtxt); 

}/* Clock_DisableLDO */

