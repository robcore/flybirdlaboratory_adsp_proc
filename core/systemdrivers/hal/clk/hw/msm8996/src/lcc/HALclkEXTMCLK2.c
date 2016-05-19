/*
==============================================================================

FILE:         HALclkEXTMCLK2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   EXTMCLK2 clocks.

   List of clock domains:
     - HAL_clk_mLPASSEXTMCLK2ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkEXTMCLK2.c#1 $

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
 *  HAL_clk_mEXTMCLK2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mEXTMCLK2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_ext_mclk2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_EXT_MCLK2_CLK
  },
};


/*
 * HAL_clk_mLPASSEXTMCLK2ClkDomain
 *
 * EXTMCLK2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_EXT_MCLK2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mEXTMCLK2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mEXTMCLK2ClkDomainClks)/sizeof(HAL_clk_mEXTMCLK2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

