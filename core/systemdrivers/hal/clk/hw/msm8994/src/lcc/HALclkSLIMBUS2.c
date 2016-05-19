/*
==============================================================================

FILE:         HALclkSLIMBUS2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SLIMBUS2 clocks.

   List of clock domains:
     - HAL_clk_mLPASSSLIMBUS2ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkSLIMBUS2.c#1 $

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


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSLIMBUS2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLIMBUS2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_slimbus2_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SLIMBUS2_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SLIMBUS2_CORE_CLK
  },
};


/*
 * HAL_clk_mLPASSSLIMBUS2ClkDomain
 *
 * SLIMBUS2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLIMBUS2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLIMBUS2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLIMBUS2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLIMBUS2ClkDomainClks)/sizeof(HAL_clk_mSLIMBUS2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

