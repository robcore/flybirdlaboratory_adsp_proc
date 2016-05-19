/*
==============================================================================

FILE:         HALclkResampler.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Resampler clocks.

   List of clock domains:
   -HAL_clk_mLPASSRESAMPLERClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/src/lcc/HALclkRESAMPLER.c#1 $

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
extern HAL_clk_ClockControlType HAL_clk_mConfigClockControl;

/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mRESAMPLERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mRESAMPLERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_resampler_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_RESAMPLER_CORE_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8974
  },
};


/*
 * HAL_clk_mLPASSRESAMPLERClkDomain
 *
 * RESAMPLER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSRESAMPLERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_RESAMPLER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mRESAMPLERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mRESAMPLERClkDomainClks)/sizeof(HAL_clk_mRESAMPLERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


