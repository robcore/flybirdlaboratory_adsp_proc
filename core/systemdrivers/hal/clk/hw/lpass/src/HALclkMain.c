/*
==============================================================================

FILE:         HALclkMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the Low Power Audio Subsystem (LPASS) processor.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/HALclkMain.c#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
12/10/11   dcf     Created.

==============================================================================
            Copyright (c) 2011 - 2013 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include "HALclkInternal.h"
#include "HALclkGeneric.h"
#include "HALclkGenericPLL.h"
#include "HALhwio.h"
#include "HALclkHWIO.h"


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_PlatformInitSources(void);


/* ============================================================================
**    Externs
** ==========================================================================*/

extern void HAL_clk_PlatformInitGCCMain(void);
extern void HAL_clk_PlatformInitLPASSMain(void);


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_aInitFuncs
 *
 * Declare array of module initialization functions.
 */
static HAL_clk_InitFuncType HAL_clk_afInitFuncs[] =
{
  /*
   * Sources
   */
  HAL_clk_PlatformInitSources,
  
  /*
   *
   */
  HAL_clk_PlatformInitGCCMain,
  HAL_clk_PlatformInitLPASSMain,

  NULL
};


/*
 * Declare the base pointers for HWIO access.
 */
uint32 HAL_clk_nHWIOBaseTop;
uint32 HAL_clk_nHWIOBaseLPASS;
uint32 HAL_clk_nHWIOBaseTCSR;


/*
 * HAL_clk_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_clk_HWIOBaseType HAL_clk_aHWIOBases[] =
{
  { CLK_CTL_BASE_PHYS,      CLK_CTL_BASE_SIZE,      &HAL_clk_nHWIOBaseTop },
  { LPASS_BASE_PHYS,        LPASS_BASE_SIZE,        &HAL_clk_nHWIOBaseLPASS },
  { CORE_TOP_CSR_BASE_PHYS, CORE_TOP_CSR_BASE_SIZE, &HAL_clk_nHWIOBaseTCSR },
  { 0, 0, NULL }
};


/*
 * HAL_clk_Platform;
 * Platform data.
 */
HAL_clk_PlatformType HAL_clk_Platform =
{
  HAL_clk_afInitFuncs,
  HAL_clk_aHWIOBases
};


/*
 * GPLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextGPLL[] =
{
  {
    HWIO_OFFS(GCC_GPLL0_MODE),
    HAL_CLK_FMSK(GCC_LPASS_DSP_GPLL_ENA_VOTE, GPLL0),
    HAL_CLK_PLL_SR
  }
};


/*
 * LPASS PLL contexts - voting is support.
 */

static HAL_clk_PLLContextType HAL_clk_aPLLContextLPAPLL_8974[] =
{
  {
    HWIO_OFFS(LPASS_LPAAUDIO_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL),
    HAL_CLK_PLL_SR,
    { 0, 0 }
  },
  {
    HWIO_OFFS(LPASS_LPAQ6_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL),
    HAL_CLK_PLL_SR,
    { 0,0 }
  }
};


/*
 * LPASS PLL contexts - voting is support.
 */

static HAL_clk_PLLContextType HAL_clk_aPLLContextLPAPLL[] =
{
  {
    HWIO_OFFS(LPASS_LPAAUDIO_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL),
    HAL_CLK_PLL_SR,
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASS_HW, LPA_PLL)
  },
  {
    HWIO_OFFS(LPASS_LPAQ6_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL),
    HAL_CLK_PLL_SR,
    { 0,0 }
  }
};


/* ============================================================================
**    Functions
** ==========================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitSources
**
** ======================================================================== */

void HAL_clk_PlatformInitSources (void)
{
  /*
   * Install PLL handlers.
   */
  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL0, &HAL_clk_aPLLContextGPLL[0], CLK_CTL_BASE);

  /*
   * Install the LPASS PLL handlers.
   */

  if(HAL_clk_GetDeviceNumber() == HAL_CLK_CHIP_SOC_APQ8084)
  {
    HAL_clk_InstallPLL(
        HAL_CLK_SOURCE_LPAPLL0, &HAL_clk_aPLLContextLPAPLL[0], LPASS_LPASS_BASE);

    HAL_clk_InstallPLL(
        HAL_CLK_SOURCE_LPAPLL1, &HAL_clk_aPLLContextLPAPLL[1], LPASS_LPASS_BASE);
  }
  else
  {
    HAL_clk_InstallPLL(
        HAL_CLK_SOURCE_LPAPLL0, &HAL_clk_aPLLContextLPAPLL_8974[0], LPASS_LPASS_BASE);

    HAL_clk_InstallPLL(
        HAL_CLK_SOURCE_LPAPLL1, &HAL_clk_aPLLContextLPAPLL_8974[1], LPASS_LPASS_BASE);

  }
} /* END HAL_clk_PlatformInitSources */


/* ===========================================================================
**  HAL_clk_GetDeviceNumber
**
** ======================================================================== */

uint32 HAL_clk_GetDeviceNumber( void )
{
  static uint32 nHWDeviceNumber = 0xFFFFFFFF;
  static uint32 nHWFamilyNumber = 0xFFFFFFFF;
  if(0xFFFFFFFF == nHWDeviceNumber)
  {
    nHWFamilyNumber = HWIO_INF(TCSR_SOC_HW_VERSION, FAMILY_NUMBER);
    nHWDeviceNumber = HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_NUMBER);
  }
  switch(nHWFamilyNumber)
  {
     case 0:
       if(nHWDeviceNumber == 0)      { return(HAL_CLK_CHIP_SOC_MSM8974); }
       else if(nHWDeviceNumber == 2) { return(HAL_CLK_CHIP_SOC_MSM8x26); }
       if(nHWDeviceNumber == 3)      { return(HAL_CLK_CHIP_SOC_APQ8084); }
       else if(nHWDeviceNumber == 5) { return(HAL_CLK_CHIP_SOC_MSM8962); }
       else if(nHWDeviceNumber == 6) { return(HAL_CLK_CHIP_SOC_MPQ8092); }
     case 1:
       if(nHWDeviceNumber == 0)      { return(HAL_CLK_CHIP_SOC_MSM8x10); }

     default:
       return(HAL_CLK_CHIP_SOC_MSM8974);
  }
  return( HAL_CLK_CHIP_SOC_MSM8974 );

} /* HAL_clk_GetDeviceNumber */




/* ===========================================================================
**  HAL_clk_AdjustSourceFrequency
**
** ======================================================================== */

void HAL_clk_AdjustSourceFrequencyInternal
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  HAL_clk_PLLContextType *pCtxt = NULL;

  /*
   * Configure the source if possible.
   */
  if (pSource != NULL && pConfig != NULL && pSource->pContext != NULL)
  {
     pCtxt = (HAL_clk_PLLContextType*)pSource->pContext;

     if(pCtxt->ePLLType == HAL_CLK_PLL_SR)
     {
       switch (pSource->eSource)
       {
         /*
          * Update the delta values to the LMN _DELTA registers and 
          * send the request. 
          */
         case HAL_CLK_SOURCE_LPAPLL0:
           HWIO_OUT(LPASS_LPAAUDIO_PLL_L_Q6_DELTA, pConfig->nL);
           HWIO_OUT(LPASS_LPAAUDIO_PLL_M_Q6_DELTA, pConfig->nM);
           HWIO_OUT(LPASS_LPAAUDIO_PLL_N_Q6_DELTA, pConfig->nN);

           HWIO_OUTF(LPASS_LPAAUDIO_PLL_MODE_Q6_CTL, REQ_UPDATE_LMN, 0x1);
           HAL_clk_BusyWait(5);
           HWIO_OUTF(LPASS_LPAAUDIO_PLL_MODE_Q6_CTL, REQ_UPDATE_LMN, 0x0);
           break;

         case HAL_CLK_SOURCE_LPAPLL1:
           HWIO_OUT(LPASS_LPAQ6_PLL_L_DELTA, pConfig->nL);
           HWIO_OUT(LPASS_LPAQ6_PLL_M_DELTA, pConfig->nM);
           HWIO_OUT(LPASS_LPAQ6_PLL_N_DELTA, pConfig->nN);

           HWIO_OUTF(LPASS_LPAQ6_PLL_MODE_CTL, REQ_UPDATE_LMN, 0x1);
           HAL_clk_BusyWait(5);
           HWIO_OUTF(LPASS_LPAQ6_PLL_MODE_CTL, REQ_UPDATE_LMN, 0x0);
           break;
      
         default:
           break;
       }
     }
  }

} /* END HAL_clk_AdjustSourceFrequency */


void HAL_clk_GetSourceDeltaInternal
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  HAL_clk_PLLContextType *pCtxt = NULL;

  /*
   * Get the delta readback information.
   */
  if (pSource != NULL && pConfig != NULL && pSource->pContext != NULL)
  {
     pCtxt = (HAL_clk_PLLContextType*)pSource->pContext;

     if(pCtxt->ePLLType == HAL_CLK_PLL_SR)
     {
       switch (pSource->eSource)
       {
         /*
          * Update the delta values to the LMN _DELTA registers and 
          * send the request. 
          */
         case HAL_CLK_SOURCE_LPAPLL0:
           pConfig->nL = HWIO_IN(LPASS_LPAAUDIO_PLL_L_Q6_READBACK);
           pConfig->nM = HWIO_IN(LPASS_LPAAUDIO_PLL_M_Q6_READBACK);
           pConfig->nN = HWIO_IN(LPASS_LPAAUDIO_PLL_N_Q6_READBACK);
           break;

         case HAL_CLK_SOURCE_LPAPLL1:
           pConfig->nL = HWIO_IN(LPASS_LPAQ6_PLL_L_READBACK);
           pConfig->nM = HWIO_IN(LPASS_LPAQ6_PLL_M_READBACK);
           pConfig->nN = HWIO_IN(LPASS_LPAQ6_PLL_N_READBACK);
           break;
      
         default:
           pConfig->nL = 0;
           pConfig->nM = 0;
           pConfig->nN = 0;
           break;
       }
     }
  }
}


/* ===========================================================================
**  HAL_clk_SelectClockSourceInternal
**
** ======================================================================== */

void HAL_clk_SelectClockSourceInternal
(
   HAL_clk_ClockDomainDescType *pmClockDomainDesc,
   HAL_clk_SourceDescType      *pSource
)
{
  HAL_clk_ClockMuxConfigType NewConfig;
  boolean bQ6PLLWasOff = FALSE;
  boolean bLPAPLLWasOff = FALSE;

  NewConfig.eSource = pSource->eSource;
  NewConfig.nM = NewConfig.nN = NewConfig.n2D = 0;
  NewConfig.nDiv2x = 0;

  /*
   * Check if the previous souce was on or not.  We need both 
   * sources running in order to make the switch.  This assumes 
   * the original source is not XO, but this does not matter. 
   */
  if (pSource->eSource == HAL_CLK_SOURCE_LPAPLL0)
  {
    if (HWIO_INF(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL) == 0)
    {
      bQ6PLLWasOff = TRUE;
      HWIO_OUTF(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL, 0x1);
      while (HWIO_INF(LPASS_LPAQ6_PLL_STATUS, PLL_ACTIVE_FLAG) != 1)
      {
        HAL_clk_BusyWait(10);
      }
    }
  }
  else if (pSource->eSource == HAL_CLK_SOURCE_LPAPLL1)
  {
    if (HWIO_INF(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL) == 0)
    {
      bLPAPLLWasOff = TRUE;
      HWIO_OUTF(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL, 0x1);
      while (HWIO_INF(LPASS_LPAAUDIO_PLL_STATUS, PLL_ACTIVE_FLAG) != 1)
      {
        HAL_clk_BusyWait(10);
      }
    }
  }

  HAL_clk_GenericConfigMux( pmClockDomainDesc, (const HAL_clk_ClockMuxConfigType*)&NewConfig);

  /*
   * Shut off any PLLs that were off before configuring the source.
   */
  if (bQ6PLLWasOff == TRUE)
  {
    HWIO_OUTF(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL, 0x0);
  }
  else if (bLPAPLLWasOff == TRUE)
  {
    HWIO_OUTF(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL, 0x1);
  }

} /* HAL_clk_SelectClockSourceInternal */


/* ===========================================================================
**  HAL_clk_Save
**
** ======================================================================== */

void HAL_clk_Save (void)
{
  /*
   * Nothing to save.
   */

} /* END HAL_clk_Save */


/* ===========================================================================
**  HAL_clk_Restore
**
** ======================================================================== */

void HAL_clk_Restore (void)
{
  /*
   * Nothing to restore.
   */
  
} /* END HAL_clk_Restore */

