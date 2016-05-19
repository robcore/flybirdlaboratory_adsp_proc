/*
==============================================================================

FILE:         HALclkATIME.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   ATIME clocks.

   List of clock domains:


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkATIME.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSAudioClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSAudioClockDomainControlRO;

/* ============================================================================
**    Data
** ==========================================================================*/

/*                           
 *  HAL_clk_mEXTMCLK1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAudioCoreAVSyncATimeClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_avsync_atime_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ATIME_CLK_SRC
  },
};


/*
 * HAL_clk_mLPASSEXTMCLK1ClkDomain
 *
 * EXTMCLK1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR),
  /* .pmClocks             = */ HAL_clk_mAudioCoreAVSyncATimeClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAudioCoreAVSyncATimeClkDomainClks)/sizeof(HAL_clk_mAudioCoreAVSyncATimeClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

