/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/gcc/HALclkGCCMain.c#1 $

when          who     what, where, why
--------      ---     ----------------------------------------------------------- 
10/31/2012            Auto-generated.

==============================================================================
            Copyright (c) 2012 Qualcomm Technologies Incorporated.
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


/* ============================================================================
**    Externs
** ==========================================================================*/


/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP5SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6SPIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCPERIPHNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSLEEPCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMIAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMISERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCXOClkDomain;


/*
 * Power domains
 */


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGCCSourceMapping
 *
 * GCC HW source mapping
 * 
 * NOTES:
 * - HAL_clk_SourceMappingType is a fixed size (HAL_CLK_MAX_MAPPED_SOURCES)
 *   array of mapped sources - see HALclkInternal.h.
 * 
 * - If source index is reserved/not used in a clock diagram, please tie that 
 *   to HAL_CLK_SOURCE_GROUND.
 *
 * - If you do not define a valid source for a given array index, the default
 *   value for that index will be HAL_CLK_SOURCE_NULL.
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap[] =
{
  {HAL_CLK_SOURCE_XO,          0},
  {HAL_CLK_SOURCE_GPLL0,       1},
  {HAL_CLK_SOURCE_GPLL2,       2},
  {HAL_CLK_SOURCE_GPLL3,       3},
  {HAL_CLK_SOURCE_GPLL1,       4},
  {HAL_CLK_SOURCE_GROUND,      5},
  {HAL_CLK_SOURCE_SLEEPCLK,    6},
  {HAL_CLK_SOURCE_PLLTEST,     7},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
};


/*
 * HAL_clk_mGCCClockDomainControl
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap
};


/*
 * HAL_clk_aGCCClockDomainDesc
 *
 * List of GCC clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aGCCClockDomainDesc [] =
{
  &HAL_clk_mGCCBLSP1QUP1SPIClkDomain,
  &HAL_clk_mGCCBLSP1QUP2SPIClkDomain,
  &HAL_clk_mGCCBLSP1QUP3SPIClkDomain,
  &HAL_clk_mGCCBLSP1QUP4SPIClkDomain,
  &HAL_clk_mGCCBLSP1QUP5SPIClkDomain,
  &HAL_clk_mGCCBLSP1QUP6SPIClkDomain,
  &HAL_clk_mGCCCONFNOCClkDomain,
  &HAL_clk_mGCCPERIPHNOCClkDomain,
  &HAL_clk_mGCCSLEEPCLKClkDomain,
  &HAL_clk_mGCCSPMIAHBClkDomain,
  &HAL_clk_mGCCSPMISERClkDomain,
  &HAL_clk_mGCCSYSNOCClkDomain,
  &HAL_clk_mGCCXOClkDomain,
  NULL
};


/*
 * HAL_clk_aGCCPowerDomainDesc
 *
 * List of GCC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGCCPowerDomainDesc [] =
{
  NULL
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitGCCMain
**
** ======================================================================== */

void HAL_clk_PlatformInitGCCMain (void)
{
  /*
   * Filter out unsupported clock in each domain.
   */
  HAL_clk_FilterClockDomains(HAL_clk_aGCCClockDomainDesc);

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aGCCClockDomainDesc, CLK_CTL_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aGCCPowerDomainDesc, CLK_CTL_BASE);

} /* END HAL_clk_PlatformInitGCCMain */

