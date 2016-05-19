/*
==============================================================================

FILE:         HALclkMIDI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MIDI clocks.

   List of clock domains:
   -HAL_clk_mLPASSMIDIClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkMIDI.c#1 $

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
 *  HAL_clk_mMIDIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMIDIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_midi_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_MIDI_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_MIDI_CORE_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8974
  },
};


/*
 * HAL_clk_mLPASSMIDIClkDomain
 *
 * MIDI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSMIDIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_MIDI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMIDIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMIDIClkDomainClks)/sizeof(HAL_clk_mMIDIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


