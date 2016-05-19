/*
==============================================================================

FILE:         HALclkSPDIFTXBMC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SPDIFTX BMC clocks.

   List of clock domains:
   -HAL_clk_mLPASSSPDIFTXBMCClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkSPDIFTXBMC.c#1 $

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


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mSPDIFTXBMCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSPDIFTXBMCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "spdiftx_bmc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_SPDIFTX_BMC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_SPDIFTX_BMC_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26)
  },
  {
    /* .szClockName      = */ "spdiftx_bmc_npl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_SPDIFTX_BMC_NPL_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_SPDIFTX_BMC_NPL_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26)
  },
};


/*
 * HAL_clk_mLPASSSPDIFTXBMCClkDomain
 *
 * SPDIFTX BMC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSPDIFTXBMCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SPDIFTX_BMC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSPDIFTXBMCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSPDIFTXBMCClkDomainClks)/sizeof(HAL_clk_mSPDIFTXBMCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


