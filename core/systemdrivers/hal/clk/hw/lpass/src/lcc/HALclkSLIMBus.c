/*
==============================================================================

FILE:         HALclkSLIMbus.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SLIMbus clocks.

   List of clock domains:
   -HAL_clk_mLPASSSLIMBUSIFMClkDomain
   -HAL_clk_mLPASSSLIMBUSIFMSYNTHClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkSLIMBus.c#1 $

when          who     what, where, why
--------      ---     ----------------------------------------------------------- 
10/31/2012            Auto-generated.

==============================================================================
            Copyright (c) 2013 Qualcomm Technologies Incorporated.
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
 *  HAL_clk_mSLIMBUSIFMClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLIMBUSIFMClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SLIMBUS_CORE_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSSLIMBUSIFMClkDomain
 *
 * SLIMBUS IFM clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUSIFMClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLIMBUS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLIMBUSIFMClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLIMBUSIFMClkDomainClks)/sizeof(HAL_clk_mSLIMBUSIFMClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


                                    
/*                           
 *  HAL_clk_mSLIMBUSIFMSYNTHClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLIMBUSIFMSYNTHClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SLIMBUS_CORE_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8x10
  },
};


/*
 * HAL_clk_mLPASSSLIMBUSIFMSYNTHClkDomain
 *
 * SLIMBUS IFMSYNTH clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUSIFMSYNTHClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLIMBUS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLIMBUSIFMSYNTHClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLIMBUSIFMSYNTHClkDomainClks)/sizeof(HAL_clk_mSLIMBUSIFMSYNTHClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


