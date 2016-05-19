/*
==============================================================================

FILE:         HALclkSPEAKERI2S.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SPEAKERI2S clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFSPKRClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkSPEAKERI2S.c#1 $

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
 *  HAL_clk_mLPAIFSPKRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFSPKRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_codec_spkr_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CLK
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_codec_spkr_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_codec_spkr_cdiv_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CLK
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_codec_spkr_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFSPKRClkDomain
 *
 * LPAIFSPKR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSPKRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_SPKR_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFSPKRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFSPKRClkDomainClks)/sizeof(HAL_clk_mLPAIFSPKRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

