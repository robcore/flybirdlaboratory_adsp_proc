/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkGCCMain.c#1 $

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


/* ============================================================================
**    Externs
** ==========================================================================*/



/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCHMSSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP5I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP5SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART3APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART4APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART5APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART6APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP5I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP5SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART3APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART4APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART5APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART6APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP3ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSRBCPRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCPERIPHNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain;

/*
 * Power domains
 */
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCAGGRE0NOCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCAGGRE1NOCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCAGGRE2NOCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCBIMCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCPCIE0PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCPCIE1PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCPCIE2PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCUFSPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCUSB30PowerDomain;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGCCSourceMap
 *
 * GCC HW source mapping
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
static HAL_clk_SourceMapType aGCCSourceMap[] =
{
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
 * HAL_clk_mGCCClockDomainControlRO
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
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
  &HAL_clk_mGCCBIMCClkDomain,
  &HAL_clk_mGCCBIMCHMSSAXIClkDomain,
  &HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP5I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP5SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART2APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART3APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART4APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART5APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART6APPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP5I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP5SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART2APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART3APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART4APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART5APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART6APPSClkDomain,
  &HAL_clk_mGCCCE1ClkDomain,
  &HAL_clk_mGCCCONFIGNOCClkDomain,
  &HAL_clk_mGCCGP1ClkDomain,
  &HAL_clk_mGCCGP2ClkDomain,
  &HAL_clk_mGCCGP3ClkDomain,
  &HAL_clk_mGCCHMSSAHBClkDomain,
  &HAL_clk_mGCCHMSSRBCPRClkDomain,
  &HAL_clk_mGCCPERIPHNOCClkDomain,
  &HAL_clk_mGCCSYSTEMNOCClkDomain,
  NULL
};


/*
 * HAL_clk_aGCCPowerDomainDesc
 *
 * List of GCC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGCCPowerDomainDesc [] =
{
  &HAL_clk_mGCCAGGRE0NOCPowerDomain,
  &HAL_clk_mGCCAGGRE1NOCPowerDomain,
  &HAL_clk_mGCCAGGRE2NOCPowerDomain,
  &HAL_clk_mGCCBIMCPowerDomain,
  &HAL_clk_mGCCPCIE0PowerDomain,
  &HAL_clk_mGCCPCIE1PowerDomain,
  &HAL_clk_mGCCPCIE2PowerDomain,
  &HAL_clk_mGCCUFSPowerDomain,
  &HAL_clk_mGCCUSB30PowerDomain,
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
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aGCCClockDomainDesc, CLK_CTL_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aGCCPowerDomainDesc, CLK_CTL_BASE);

} /* END HAL_clk_PlatformInitGCCMain */

