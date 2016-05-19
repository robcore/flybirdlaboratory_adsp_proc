/*
==============================================================================

FILE:         HALclkBIMC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BIMC clocks.

   List of clock domains:
     - HAL_clk_mGCCBIMCClkDomain


   List of power domains:
     - HAL_clk_mGCCBIMCPowerDomain



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkBIMC.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mBIMCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBIMCClkDomainClks[] =
{
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_bimc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCBIMCClkDomain
 *
 * BIMC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BIMC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBIMCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBIMCClkDomainClks)/sizeof(HAL_clk_mBIMCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mGCCBIMCPowerDomain
 *
 * BIMC power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCBIMCPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_BIMC",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_BIMC_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

