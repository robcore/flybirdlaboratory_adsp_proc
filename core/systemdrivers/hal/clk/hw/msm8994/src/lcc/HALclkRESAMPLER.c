/*
==============================================================================

FILE:         HALclkRESAMPLER.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   RESAMPLER clocks.

   List of clock domains:
     - HAL_clk_mLPASSRESAMPLERClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkRESAMPLER.c#1 $

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


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSBusClockDomainControl;

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
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_RESAMPLER_CORE_CLK
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
  /* .pmControl            = */ &HAL_clk_mLPASSBusClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

