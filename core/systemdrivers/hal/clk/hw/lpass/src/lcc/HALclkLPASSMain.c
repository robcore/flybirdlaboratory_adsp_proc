/*
==============================================================================

FILE:         HALclkLPASSMain.c

DESCRIPTION:
   The main auto-generated file for LPASS.


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkLPASSMain.c#1 $

when          who     what, where, why
----------    ---     --------------------------------------------------------
08/14/2013            Auto-generated.

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
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPCMOEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIMI2SMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIPCMMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIPCMSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFQUADMI2SMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECMI2SMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECPCMMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECPCMSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSPKRI2SMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSPKRI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFTERMI2SMSTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFTERMI2SSLVClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSATIME2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSATIMEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSPRIMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQUADMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSMIDIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSRESAMPLERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSECMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSIFClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUSIFMClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUSIFMSYNTHClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSPDIFTXBMCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSPDMClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSTERMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCDCClkDomain;

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
  {HAL_CLK_SOURCE_LPAPLL1,     2},
  {HAL_CLK_SOURCE_GROUND,      3},
  {HAL_CLK_SOURCE_GROUND,      4},
  {HAL_CLK_SOURCE_GROUND,      5},
  {HAL_CLK_SOURCE_GROUND,      6},
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
 * HAL_clk_aLPASSClockDomainDesc
 *
 * List of LPASS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aLPASSClockDomainDesc [] =
{
  &HAL_clk_mQ6ClkDomain,
  &HAL_clk_mLPASSAIFPCMOEClkDomain,
  &HAL_clk_mLPASSAIFPRIMI2SMSTRClkDomain,
  &HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFPRIPCMMSTRClkDomain,
  &HAL_clk_mLPASSAIFPRIPCMSLVClkDomain,
  &HAL_clk_mLPASSAIFQUADMI2SMSTRClkDomain,
  &HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFSECMI2SMSTRClkDomain,
  &HAL_clk_mLPASSAIFSECMI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFSECPCMMSTRClkDomain,
  &HAL_clk_mLPASSAIFSECPCMSLVClkDomain,
  &HAL_clk_mLPASSAIFSPKRI2SMSTRClkDomain,
  &HAL_clk_mLPASSAIFSPKRI2SSLVClkDomain,
  &HAL_clk_mLPASSAIFTERMI2SMSTRClkDomain,
  &HAL_clk_mLPASSAIFTERMI2SSLVClkDomain,
  &HAL_clk_mLPASSATIME2ClkDomain,
  &HAL_clk_mLPASSATIMEClkDomain,
  &HAL_clk_mLPASSBUSClkDomain,
  &HAL_clk_mLPASSCXOClkDomain,
  &HAL_clk_mLPASSPRIMCLKClkDomain,
  &HAL_clk_mLPASSQUADMCLKClkDomain,
  &HAL_clk_mLPASSMIDIClkDomain,
  &HAL_clk_mLPASSRESAMPLERClkDomain,
  &HAL_clk_mLPASSSECMCLKClkDomain,
  &HAL_clk_mLPASSSIFClkDomain,
  &HAL_clk_mLPASSSLEEPClkDomain,
  &HAL_clk_mLPASSSLIMBUSIFMClkDomain,
  &HAL_clk_mLPASSSLIMBUSIFMSYNTHClkDomain,
  &HAL_clk_mLPASSSPDIFTXBMCClkDomain,
  &HAL_clk_mLPASSSPDMClkDomain,
  &HAL_clk_mLPASSTERMCLKClkDomain,
  &HAL_clk_mLPASSCDCClkDomain,
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


  /*
   *  SW workaround for HW issue that fails to default the sleep and wake POR
   *  values for LPM to max.  Set values to max (0xF) here.
   */
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM0_CBCR, WAKEUP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM0_CBCR, SLEEP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM1_CBCR, WAKEUP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM1_CBCR, SLEEP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM2_CBCR, WAKEUP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM2_CBCR, SLEEP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM3_CBCR, WAKEUP, 0xF);
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_MEM3_CBCR, SLEEP, 0xF);


  /*
   * Need to modify the AUDIO_CORE_GDSC register defaults to allow enough 
   * time for the clock to propagate before deasserting the clamp. 
   */
  HWIO_OUTF(LPASS_AUDIO_CORE_GDSCR, EN_REST_WAIT, 0x2);
  HWIO_OUTF(LPASS_AUDIO_CORE_GDSCR, EN_FEW_WAIT, 0x2);
  HWIO_OUTF(LPASS_AUDIO_CORE_GDSCR, CLK_DIS_WAIT, 0x2);

} /* END HAL_clk_PlatformInitLPASSMain */

