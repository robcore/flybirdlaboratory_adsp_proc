/*
==============================================================================

FILE:         HALclkAIFPCMOE.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF PCMOE clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFPCMOEClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/lcc/HALclkAIFPCMOE.c#1 $

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
 *  HAL_clk_mAIFPCMOEClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFPCMOEClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcmoe_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_PCM_DATA_OE_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mAIFPCMOEClkDomain
 *
 * AIF PCMOE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPCMOEClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PCMOE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFPCMOEClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPCMOEClkDomainClks)/sizeof(HAL_clk_mAIFPCMOEClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


