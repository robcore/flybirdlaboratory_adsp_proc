/*
==============================================================================

FILE:         HALclkLPASSMain.c

DESCRIPTION:
   The main auto-generated file for LPASS.


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkLPASSMain.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
11/20/2013           auto-generated.


==============================================================================
            Copyright (c) 2013 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_AudioCorePowerDomainEnable(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
void HAL_clk_AudioCorePowerDomainDisable(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);

/* ============================================================================
**    Externs
** ==========================================================================*/


/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mQ6ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAHBFABRICClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAVTIMERXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSGDSCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM0SLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM1SLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCMOEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPRIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFQUADClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSECClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSPKRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSPRIMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SPDMClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SSBCRSLPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6XOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQUADMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSRESAMPLERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSECMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUS2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSTMXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSTERMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFTERMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSPKRI2SSLVClkDomain;

/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_mAudioCorePowerDomainControl
 *
 * Functions for controlling common power domain functions.
 */
HAL_clk_PowerDomainControlType HAL_clk_mAudioCorePowerDomainControl =
{
   /* .Enable     = */ HAL_clk_AudioCorePowerDomainEnable,
   /* .Disable    = */ HAL_clk_AudioCorePowerDomainDisable,
   /* .IsEnabled  = */ HAL_clk_GenericPowerDomainIsEnabled
};


/*
 * HAL_clk_mUSBHSHSICPowerDomain
 *
 * USB HS HSIC power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mLPASSAudioCorePowerDomain =
{
  /* .szPowerDomainName       = */ "LPASS_AUDIO_CORE",   /* Not sure about the name ? */
  /* .nGDSCRAddr              = */ HWIO_OFFS(LPASS_AUDIO_CORE_GDSCR),
  /* .pmControl               = */ &HAL_clk_mAudioCorePowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};


/*
 * aLPASSSourceMap
 *
 * LPASS HW source mapping
 * 
 * NOTES:
 * - HAL_clk_SourceMapType is an array of mapped sources
 *   - see HALclkInternal.h.
 *
 * - If source index is reserved/not used in a clock diagram, please tie that
 *   to HAL_CLK_SOURCE_GROUND.
 *
 * - {HAL_CLK_SOURCE_NULL, HAL_CLK_SOURCE_INDEX_INVALID} is used to indicate
 *   the end of the mapping array. If we reach this element during our lookup,
 *   we'll know we could not find the matching source enum for the register
 *   value, or vice versa.
 * 
 */
static HAL_clk_SourceMapType aLPASSSourceMap[] =
{
  {HAL_CLK_SOURCE_XO,          0},
  {HAL_CLK_SOURCE_LPAPLL0,     1},
  {HAL_CLK_SOURCE_LPAPLL2,     2},
  {HAL_CLK_SOURCE_AUD_REF_CLK, 3},
  {HAL_CLK_SOURCE_LPAPLL1,     6},
  {HAL_CLK_SOURCE_PLLTEST,     7},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};


/*
 * HAL_clk_mLPASSClockDomainControl
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aLPASSSourceMap
};


/*
 * Bus clocks use the MAIN output on the LPAPLLs, so they require 
 * a different LPAPLL source mapping. 
*/
static HAL_clk_SourceMapType aLPASSSBusSourceMap[] =
{
  {HAL_CLK_SOURCE_XO,          0},
  {HAL_CLK_SOURCE_LPAPLL0,     4},
  {HAL_CLK_SOURCE_LPAPLL2,     5},
  {HAL_CLK_SOURCE_AUD_REF_CLK, 3},
  {HAL_CLK_SOURCE_LPAPLL1,     6},
  {HAL_CLK_SOURCE_PLLTEST,     7},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};


/*
 * HAL_clk_mLPASSBusClockDomainControl
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSBusClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aLPASSSBusSourceMap
};


/*
 * HAL_clk_aLPASSClockDomainDesc
 *
 * List of LPASS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aLPASSClockDomainDesc [] =
{
  &HAL_clk_mQ6ClkDomain,
  &HAL_clk_mLPASSAHBFABRICClkDomain,
  &HAL_clk_mLPASSAVTIMERXOClkDomain,
  &HAL_clk_mLPASSGDSCXOClkDomain,
  &HAL_clk_mLPASSLPAIFPCM0ClkDomain,
  &HAL_clk_mLPASSLPAIFPCM1ClkDomain,
  &HAL_clk_mLPASSLPAIFPCMOEClkDomain,
  &HAL_clk_mLPASSLPAIFPRIClkDomain,
  &HAL_clk_mLPASSLPAIFQUADClkDomain,
  &HAL_clk_mLPASSLPAIFSECClkDomain,
  &HAL_clk_mLPASSLPAIFSPKRClkDomain,
  &HAL_clk_mLPASSLPAIFTERClkDomain,
  &HAL_clk_mLPASSPRIMCLKClkDomain,
  &HAL_clk_mLPASSQ6SPDMClkDomain,
  &HAL_clk_mLPASSQ6SSBCRSLPClkDomain,
  &HAL_clk_mLPASSQ6XOClkDomain,
  &HAL_clk_mLPASSQUADMCLKClkDomain,
  &HAL_clk_mLPASSRESAMPLERClkDomain,
  &HAL_clk_mLPASSSECMCLKClkDomain,
  &HAL_clk_mLPASSSLEEPClkDomain,
  &HAL_clk_mLPASSSLIMBUSClkDomain,
  &HAL_clk_mLPASSSLIMBUS2ClkDomain,
  &HAL_clk_mLPASSSTMXOClkDomain,
  &HAL_clk_mLPASSTERMCLKClkDomain,
  &HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFSECMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFTERMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFSPKRI2SSLVClkDomain,
  &HAL_clk_mLPASSLPAIFPCM0SLVClkDomain,
  &HAL_clk_mLPASSLPAIFPCM1SLVClkDomain,
  NULL
};

/*
 * HAL_clk_aLPASSPowerDomainDesc
 *
 * List of LPASS power domains
*/
static HAL_clk_PowerDomainDescType * HAL_clk_aLPASSPowerDomainDesc [] = 
{
   &HAL_clk_mLPASSAudioCorePowerDomain,
   NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_AudioCorePowerDomainEnable
**
** ======================================================================== */

void HAL_clk_AudioCorePowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr,nVal;
  nAddr = pmPowerDomainDesc->nGDSCRAddr;

  /*
   * Sanity check
   */
  if(nAddr != 0)
  {
    nVal  = inpdw(nAddr);
   
    /*
     * Clear the SW PD collapse bit
     */
    nVal &= ~HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);
   
    /*
     * Wait for PD ON
     */
    while(!(inpdw(nAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));

    /*
     * Ensure the reset is cleared.
     */
    HWIO_OUTF(LPASS_AUDIO_CORE_BCR, BLK_ARES, 0x0);
    HAL_clk_BusyWait(2);
  }

} /* HAL_clk_AudioCorePowerDomainEnable */


/* ===========================================================================
**  HAL_clk_AudioCorePowerDomainDisable
**
** ======================================================================== */

void HAL_clk_AudioCorePowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr = pmPowerDomainDesc->nGDSCRAddr;
  uint32 nVal;

  if(nAddr != 0)
  {
    nVal = inpdw(nAddr);

    /*
     * Before disabling the GDS, put the core in reset to ensure that any 
     * bus transactions are gracefully aborted. 
     */
    HWIO_OUTF(LPASS_AUDIO_CORE_BCR, BLK_ARES, 0x1);
  
    while(HWIO_IN(LPASS_AUDIO_CORE_BCR) &~ HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK);

    /*
     * Set the SW PD collapse bit
     */
    nVal |= HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);
  }

} /* HAL_clk_AudioCorePowerDomainDisable */


/* ===========================================================================
**  HAL_clk_PlatformInitLPASSMain
**
** ======================================================================== */

void HAL_clk_PlatformInitLPASSMain (void)
{
  /*
   * Filter out clocks not supported on the current chipset.
   */
  HAL_clk_FilterClockDomains(HAL_clk_aLPASSClockDomainDesc);

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aLPASSClockDomainDesc, LPASS_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aLPASSPowerDomainDesc, LPASS_BASE);


} /* END HAL_clk_PlatformInitLPASSMain */

