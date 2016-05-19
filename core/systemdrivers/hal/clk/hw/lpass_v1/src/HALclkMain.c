/*
==============================================================================

FILE:         HALclkMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the modem subsystem (LPASS) processor on MSM8974.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/src/HALclkMain.c#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
12/10/11   dcf     Created.

==============================================================================
            Copyright (c) 2011 - 2012 Qualcomm Technologies Incorporated.
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

static HAL_clk_PLLContextType HAL_clk_aPLLContextLPAPLL[] =
{
  {
    HWIO_OFFS(LPASS_LPAAUDIO_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, LPA_PLL)
  },
  {
    HWIO_OFFS(LPASS_LPAQ6_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASSQ6, Q6_PLL)
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

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_LPAPLL0, &HAL_clk_aPLLContextLPAPLL[0], LPASS_LPASS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_LPAPLL1, &HAL_clk_aPLLContextLPAPLL[1], LPASS_LPASS_BASE);

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
       else if(nHWDeviceNumber == 1) { return(HAL_CLK_CHIP_SOC_MDM9x25); }
       else if(nHWDeviceNumber == 2) { return(HAL_CLK_CHIP_SOC_MSM8x26); }
       else if(nHWDeviceNumber == 3) { return(HAL_CLK_CHIP_SOC_APQ8084); }
       /* Use 8x26 for 8926 */
       else if(nHWDeviceNumber == 4) { return(HAL_CLK_CHIP_SOC_MSM8x26); }
       else if(nHWDeviceNumber == 5) { return(HAL_CLK_CHIP_SOC_MSM8962); }
     case 1:
       if(nHWDeviceNumber == 0)      { return(HAL_CLK_CHIP_SOC_MSM8x10); }

     default:
       return(HAL_CLK_CHIP_SOC_MSM8974);
  }
  return( HAL_CLK_CHIP_SOC_MSM8974 );

} /* HAL_clk_GetDeviceNumber */


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
  /* Not supported on this branch. */

} /* END HAL_clk_AdjustSourceFrequency */


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
  /* Not supported on this branch. */

} /* END HAL_clk_SelectClockSourceInternal */

