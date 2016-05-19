/*
==============================================================================

FILE:         HALclkSleep.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Sleep clocks.

   List of clock domains:
   -HAL_clk_mLPASSSLEEPClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkSLEEP.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mSLEEPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_SLP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "q6ss_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_BCR_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_BCR_SLP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSSLEEPClkDomain
 *
 * SLEEP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLPClkDomainClks)/sizeof(HAL_clk_mSLPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


