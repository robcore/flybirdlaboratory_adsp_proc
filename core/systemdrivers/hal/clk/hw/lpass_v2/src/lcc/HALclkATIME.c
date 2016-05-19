/*
==============================================================================

FILE:         HALclkATIME.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   ATIME clocks.

   List of clock domains:
   -HAL_clk_mLPASSATIMEClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/lcc/HALclkATIME.c#1 $

when          who     what, where, why
----------    ---     --------------------------------------------------------
05/20/2013            Auto-generated.

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
 *  HAL_clk_mATIMEClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mATIMEClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_avsync_atime_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_CORE_AVSYNC_ATIME_CLK
  },
};


/*
 * HAL_clk_mLPASSATIMEClkDomain
 *
 * ATIME clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSATIMEClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_ATIME_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mATIMEClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mATIMEClkDomainClks)/sizeof(HAL_clk_mATIMEClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


