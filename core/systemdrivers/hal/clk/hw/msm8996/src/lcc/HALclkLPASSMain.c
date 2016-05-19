/*
==============================================================================

FILE:         HALclkLPASSMain.c

DESCRIPTION:
   The main auto-generated file for LPASS.


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkLPASSMain.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
06/16/2014           Auto-generated.


==============================================================================
            Copyright (c) 2014 QUALCOMM Technologies Incorporated.
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
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAONClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAUDSLIMBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSBCRSLPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREQOSFIXEDLATCOUNTERSRCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSGDSCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCMOEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPRIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFQUADClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSECClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSPKRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SMMUGDSCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQCASLIMBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSFIXEDLATCOUNTERSRCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mQ6ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSResamplerClkDomain;

/*
 * Power domains
 */


/* ============================================================================
**    Data
** ==========================================================================*/


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
  {HAL_CLK_SOURCE_XO,           0},
  {HAL_CLK_SOURCE_LPAPLL1,      1},
  {HAL_CLK_SOURCE_LPAPLL0,      3},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};


static HAL_clk_SourceMapType aLPASSAudioSourceMap[] =
{
  {HAL_CLK_SOURCE_XO,           0},
  {HAL_CLK_SOURCE_LPAPLL1,      5},
  {HAL_CLK_SOURCE_LPAPLL0,      6},
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

HAL_clk_ClockDomainControlType HAL_clk_mLPASSAudioClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aLPASSAudioSourceMap
};




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
 * HAL_clk_mLPASSClockDomainControlRO
 *
 * Read-only functions for LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aLPASSSourceMap
};

HAL_clk_ClockDomainControlType HAL_clk_mLPASSAudioClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aLPASSAudioSourceMap
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
 * HAL_clk_mUSBHSHSICPowerDomain
 *
 * USB HS HSIC power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mLPASSSMMUPowerDomain =
{
  /* .szPowerDomainName       = */ "LPASS_Q6_SMMU",   /* Not sure about the name ? */
  /* .nGDSCRAddr              = */ HWIO_OFFS(LPASS_Q6_SMMU_GDSCR),
  /* .pmControl               = */ &HAL_clk_mAudioCorePowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};


/*
 * HAL_clk_aLPASSPowerDomainDesc
 *
 * List of LPASS power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aLPASSPowerDomainDesc [] =
{
  &HAL_clk_mLPASSAudioCorePowerDomain,
  &HAL_clk_mLPASSSMMUPowerDomain,
  NULL
};


/*
 * HAL_clk_aLPASSClockDomainDesc
 *
 * List of LPASS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aLPASSClockDomainDesc [] =
{
  &HAL_clk_mLPASSAONClkDomain,
  &HAL_clk_mLPASSAUDSLIMBUSClkDomain,
  &HAL_clk_mLPASSBCRSLPClkDomain,
  &HAL_clk_mLPASSCOREClkDomain,
  &HAL_clk_mLPASSCOREQOSFIXEDLATCOUNTERSRCClkDomain,
  &HAL_clk_mLPASSEXTMCLK0ClkDomain,
  &HAL_clk_mLPASSEXTMCLK1ClkDomain,
  &HAL_clk_mLPASSEXTMCLK2ClkDomain,
  &HAL_clk_mLPASSGDSCXOClkDomain,
  &HAL_clk_mLPASSLPAIFPCMOEClkDomain,
  &HAL_clk_mLPASSLPAIFPRIClkDomain,
  &HAL_clk_mLPASSLPAIFQUADClkDomain,
  &HAL_clk_mLPASSLPAIFSECClkDomain,
  &HAL_clk_mLPASSLPAIFSPKRClkDomain,
  &HAL_clk_mLPASSLPAIFTERClkDomain,
  &HAL_clk_mLPASSQ6SMMUGDSCXOClkDomain,
  &HAL_clk_mLPASSQCASLIMBUSClkDomain,
  &HAL_clk_mLPASSQOSFIXEDLATCOUNTERSRCClkDomain,
  &HAL_clk_mLPASSQOSXOClkDomain,
  &HAL_clk_mQ6ClkDomain,
  &HAL_clk_mLPASSResamplerClkDomain,
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
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aLPASSClockDomainDesc, LPASS_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aLPASSPowerDomainDesc, LPASS_BASE);

} /* END HAL_clk_PlatformInitLPASSMain */

