/*
==============================================================================

FILE:         HALclkPriusPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Prius/Tesla PLL control.
  These PLLs are of the Prius and Tesla PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/v1/HALclkPriusPLL.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
05/30/13   frv     Created

==============================================================================
            Copyright (c) 2013 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkPriusPLL.h"
#include "HALclkGenericPLL.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/


/*
 * HAL_CLK_PLL_MODE_*
 *
 * Definitions for configuring the PLLn_MODE register.
 */
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_OUTCTRL)  | \
   HWIO_FMSK(PLL_MODE, PLL_BYPASSNL) | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * Definitions for configuring the PLL in FSM Mode
 */
#define HAL_CLK_PLL_BIAS_COUNT_VAL   (0x1 << HWIO_SHFT(PLL_MODE, PLL_BIAS_COUNT))
#define HAL_CLK_PLL_LOCK_COUNT_VAL   (0x0 << HWIO_SHFT(PLL_MODE, PLL_LOCK_COUNT))

/*
 * HAL_CLK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define HAL_CLK_PLL_INIT_TIME_US 5

/*
 * HAL_CLK_PLL_WARMUP_TIME_US
 *
 * Warm-up time in microseconds after turning on the PLL.
 */
#define HAL_CLK_PLL_WARMUP_TIME_US 50


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_PriusPLLControl
 *
 * Control function array for the Prius/Tesla PLLs.
 */
HAL_clk_SourceControlType HAL_clk_PriusPLLControl =
{
  /* .Enable              = */ HAL_clk_PriusPLLEnable,
  /* .Disable             = */ HAL_clk_PriusPLLDisable,
  /* .IsEnabled           = */ HAL_clk_PriusPLLIsEnabled,
  /* .Config              = */ HAL_clk_PriusPLLConfig,
  /* .ConfigPLL           = */ HAL_clk_PriusPLLConfigPLL,
  /* .DetectPLLConfig     = */ HAL_clk_PriusPLLDetectPLLConfig,
  /* .EnableVote          = */ HAL_clk_PriusPLLEnableVote,
  /* .DisableVote         = */ HAL_clk_PriusPLLDisableVote,
  /* .IsVoteEnabled       = */ HAL_clk_PriusPLLIsVoteEnabled,
  /* .SlewConfigPLL       = */ HAL_clk_PriusPLLSlewConfigPLL,
  /* .EnableVoteOverride  = */ HAL_clk_PriusPLLEnableVoteOverride,
  /* .DisableVoteOverride = */ HAL_clk_PriusPLLDisableVoteOverride,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_PriusPLLEnableVoteOverride
**
** ======================================================================== */

static void HAL_clk_PriusPLLEnableVoteOverride
(
  HAL_clk_SourceDescType      *pSource,
  HAL_clk_ClockDomainDescType *pmClkDomainDesc
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  if (pmClkDomainDesc->bSPMHWVoter == TRUE)
  {
    if (pCtxt->SPMHWVoteRegister.nAddr != 0)
    {
      nVal = inpdw(pCtxt->SPMHWVoteRegister.nAddr) &~ pCtxt->SPMHWVoteRegister.nMask;
      outpdw(pCtxt->SPMHWVoteRegister.nAddr, nVal);
    }
  }

} /* END HAL_clk_PriusPLLEnableVoteOverride */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableVoteOverride
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableVoteOverride
(
  HAL_clk_SourceDescType      *pSource,
  HAL_clk_ClockDomainDescType *pmClkDomainDesc
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  if (pmClkDomainDesc->bSPMHWVoter == TRUE)
  {
    if (pCtxt->SPMHWVoteRegister.nAddr != 0)
    {
      nVal = inpdw(pCtxt->SPMHWVoteRegister.nAddr) | pCtxt->SPMHWVoteRegister.nMask;
      outpdw(pCtxt->SPMHWVoteRegister.nAddr, nVal);
    }
  }

} /* END HAL_clk_PriusPLLDisableVoteOverride */


/* ===========================================================================
**  HAL_clk_PriusPLLEnableVote
**
** ======================================================================== */

static void HAL_clk_PriusPLLEnableVote
(
  HAL_clk_SourceDescType   *pSource,
  boolean                  bAsync
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Set the appropriate bit.
   */
  nVal = inpdw(pCtxt->VoterRegister.nAddr) | pCtxt->VoterRegister.nMask;
  outpdw(pCtxt->VoterRegister.nAddr, nVal);

  if (FALSE == bAsync)
  {
    /*
     * Wait for the PLL to go active.
     */
    while (HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_ACTIVE_FLAG) != 1)
    {
      HAL_clk_BusyWait(10);
    }
  }

} /* END HAL_clk_PriusPLLEnableVote */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableVote
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear the appropriate bit.
   */
  nVal = inpdw(pCtxt->VoterRegister.nAddr) & ~pCtxt->VoterRegister.nMask;
  outpdw(pCtxt->VoterRegister.nAddr, nVal);

} /* END HAL_clk_PriusPLLDisableVote */


/* ===========================================================================
**  HAL_clk_PriusPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clk_PriusPLLIsVoteEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check the appropriate bit.
   */
  if (inpdw(pCtxt->VoterRegister.nAddr) & pCtxt->VoterRegister.nMask)
  {
    return TRUE;
  }

  return FALSE;

} /* END HAL_clk_PriusPLLIsVoteEnabled */


/* ===========================================================================
**  HAL_clk_PriusPLLEnable
**
** ======================================================================== */

static void HAL_clk_PriusPLLEnable
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32 nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_PriusPLLIsEnabled(pSource))
  {
    return;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert PLL bypass.
   * This latches L, Alpha, and AlphaU values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL init time
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_INIT_TIME_US);

  /*
   * De-assert PLL reset.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for the PLL warm-up time.
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_WARMUP_TIME_US);

  /*
   * Wait for lock.
   */
  while (HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_LOCK_DET) == 0)
  {
    HAL_clk_BusyWait(10);
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_PriusPLLEnable */


/* ===========================================================================
**  HAL_clk_PriusPLLDisable
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisable
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Put the PLL in reset mode
   */
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_BYPASSNL) |
                HWIO_FMSK(PLL_MODE, PLL_OUTCTRL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_PriusPLLDisable */


/* ===========================================================================
**  HAL_clk_PriusPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_PriusPLLIsEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32 nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Check whether the PLL is enabled.
   */
  return ((nModeVal & HAL_CLK_PLL_MODE_ACTIVE) == HAL_CLK_PLL_MODE_ACTIVE);

} /* END HAL_clk_PriusPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_PriusPLLConfig
**
** ======================================================================== */

static void HAL_clk_PriusPLLConfig
(
  HAL_clk_SourceDescType   *pSource,
  HAL_clk_SourceConfigType  eConfig
)
{
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Take action.
   */
  switch (eConfig)
  {
    case HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA, 1);
      break;

    case HAL_CLK_CONFIG_PLL_FSM_MODE_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX, 1);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX2, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX2, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_EARLY, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_EARLY, 0);
      break;

    case HAL_CLK_CONFIG_PLL_SRC_SEL_AUD_REF_CLK:
      HAL_CLK_PLL_HWIO_OUTF(PLL_CLK_SRC_SEL, pCtxt, PLL_CLK_SRC_SEL, 0x1);
      break;

    default:
      break;
  }

} /* END HAL_clk_PriusPLLConfig */


/* ===========================================================================
**  HAL_clk_PriusPLLConfigPLL
**
** ======================================================================== */

static void HAL_clk_PriusPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32  nModeVal, nUserVal;
  uint32  nPLLInFSMMode = 0;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  nPLLInFSMMode = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt) &
    HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
  bPLLEnabled = HAL_clk_PriusPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PriusPLLDisable(pSource);
  }

  /*
   * Read the PLLx_Mode value
   */
  nModeVal  = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Disable FSM Mode
   */
  if (nPLLInFSMMode != 0)
  {
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);
  }

  /*
   * Program L/Alpha/AlphaU values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pCtxt, pConfig->nAlpha);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_U_VAL, pCtxt, pConfig->nAlphaU);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, ALPHA_EN) |
                HWIO_FMSK(PLL_USER_CTL, VCO_SEL) |
                HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO));

  /*
   * Find the VCO 
   */
  switch (pConfig->eVCO)
  {
    case HAL_CLK_PLL_VCO3:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 2);
      break;

    case HAL_CLK_PLL_VCO2:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 1);
      break;

    default:
      break;
  }

  /*
   * Program the pre-div value (div-1 to div-8).
   */
  if (pConfig->nPreDiv <= 8 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, PRE_DIV_RATIO, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div value (div-1,2,4,8 and 16 are supported)
   */
  if ((pConfig->nPostDiv == 2) || (pConfig->nPostDiv == 4) ||
      (pConfig->nPostDiv == 8) || (pConfig->nPostDiv == 16))
  {
    nUserVal |=
      ((pConfig->nPostDiv - 1) << HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO));
  }

  /*
   *  Check fractional output or integer output.
   */
  if ((pConfig->nAlpha != 0) || (pConfig->nAlphaU != 0))
  {
    nUserVal |= HWIO_FMSK(PLL_USER_CTL, ALPHA_EN);
  }

  /*
   * Enable MAIN_OUT_ENA bit. 
   */
  nUserVal |= HWIO_FMSK(PLL_USER_CTL, PLLOUT_LV_MAIN);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pCtxt, nUserVal);

  /*
   * If there is an address for a voting register, then the PLL is in
   * FSM voteable mode. In this case, the enable sequence is handled in
   * hardware, guided by the BIAS and LOCK counts.
   */
  if (nPLLInFSMMode)
  {
    /*
     * Put the FSM in reset.
     */
    nModeVal |= HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_RESET);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

    /*
     * Program the FSM portion of the mode register.
     */
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_BIAS_COUNT);
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_LOCK_COUNT);

    nModeVal |= HAL_CLK_PLL_BIAS_COUNT_VAL;
    nModeVal |= HAL_CLK_PLL_LOCK_COUNT_VAL;

    nModeVal |= HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
    /*
     * Finally program the Mode register.
     */
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

    /*
     * Take the FSM out of reset.
     */
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_RESET);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);
  }

  /*
   * Enable the PLL if it was on before and not in FSM mode (in FSM
   * mode this function is not used).
   */
  if (bPLLEnabled && nPLLInFSMMode == 0)
  {
    HAL_clk_PriusPLLEnable(pSource);
  }

} /* END HAL_clk_PriusPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_PriusPLLSlewConfigPLL
**
** ======================================================================== */

static void HAL_clk_PriusPLLSlewConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports dynamic programming.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    return;
  }

  /*
   * Read the PLLx_Mode value
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Program L/Alpha/AlphaU values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pCtxt, pConfig->nAlpha);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_U_VAL, pCtxt, pConfig->nAlphaU);

  /*
   * Toggle the update bit to latch the new configuration values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_UPDATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL_UPDATE to be cleared by the HW.
   */
  while (HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_UPDATE) != 0)
  {
    HAL_clk_BusyWait(10);
  }

  /*
   * Wait for 11 or more PLL clk_ref ticks for PLL_LOCK_DET to transition to 0.
   * When using a reference clock of XO, the wait requirement is 570 ns.
   */
  HAL_clk_BusyWait(1);

  /*
   * Wait for lock.
   */
  while (HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_LOCK_DET) == 0)
  {
    HAL_clk_BusyWait(10);
  }

} /* END HAL_clk_PriusPLLSlewConfigPLL */


/* ===========================================================================
**  HAL_clk_PriusPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_PriusPLLDetectPLLConfig
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  uint32 nConfigVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear all config values not modified in this function.
   */
  pConfig->nM = 0;
  pConfig->nN = 0;
  pConfig->nVCOMultiplier = 0;

  /*
   * Read current L, Alpha, and AlphaU values.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pCtxt);
  pConfig->nAlpha = HAL_CLK_PLL_HWIO_IN(PLL_ALPHA_VAL, pCtxt);
  pConfig->nAlphaU = HAL_CLK_PLL_HWIO_IN(PLL_ALPHA_U_VAL, pCtxt);

  /*
   * Determine the oscillator source.
   */
  pConfig->eSource = HAL_CLK_SOURCE_XO;

  /*
   * Get the VCO 
   */
  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  pConfig->eVCO =
    (HAL_clk_PLLVCOType)((nConfigVal & HWIO_FMSK(PLL_USER_CTL, VCO_SEL))
                            >> HWIO_SHFT(PLL_USER_CTL, VCO_SEL));

  /*
   * Get the pre and post dividers.
   */
  pConfig->nPreDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO))
                         >> (HWIO_SHFT(PLL_USER_CTL, PRE_DIV_RATIO))) + 1;
  pConfig->nPostDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO))
                >> HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO)) + 1;

} /* END HAL_clk_PriusPLLDetectPLLConfig */

