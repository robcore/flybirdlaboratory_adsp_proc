/*
==============================================================================

FILE:         HALclkQUATERNARYTDM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QUATERNARYTDM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFQUADClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkQUATERNARYTDM.c#1 $

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
 *  HAL_clk_mLPAIFQUADClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFQUADClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_QUAD_IBIT_CLK
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  }
};


/*
 * HAL_clk_mLPASSLPAIFQUADClkDomain
 *
 * LPAIFQUAD clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFQUADClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_QUAD_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFQUADClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFQUADClkDomainClks)/sizeof(HAL_clk_mLPAIFQUADClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

