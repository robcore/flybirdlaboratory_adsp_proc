/*
==============================================================================

FILE:         HALclkATIME2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   ATIME2 clocks.

   List of clock domains:
   -HAL_clk_mLPASSATIME2ClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkATIME2.c#1 $

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
 *  HAL_clk_mATIME2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mATIME2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_avsync_atime2_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_ATIME2_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_CORE_AVSYNC_ATIME2_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MPQ8092
  },
};


/*
 * HAL_clk_mLPASSATIME2ClkDomain
 *
 * ATIME2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSATIME2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_ATIME2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mATIME2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mATIME2ClkDomainClks)/sizeof(HAL_clk_mATIME2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


