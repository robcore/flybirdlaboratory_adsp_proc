/*
==============================================================================

FILE:         HALclkAIFPRIPCMSLV.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF PRI PCM SLV clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFPRIPCMMSTRClkDomain
   -HAL_clk_mLPASSAIFPRIPCMSLVClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/src/lcc/HALclkAIFPRIPCMSLV.c#1 $

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
 *  HAL_clk_mAIFPRIPCMMSTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFPRIPCMMSTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm0_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFPRIPCMMSTRClkDomain
 *
 * AIF PRI PCM MSTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIPCMMSTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PCM0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFPRIPCMMSTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPRIPCMMSTRClkDomainClks)/sizeof(HAL_clk_mAIFPRIPCMMSTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


                                    
/*                           
 *  HAL_clk_mAIFPRIPCMSLVClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFPRIPCMSLVClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm0_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFPRIPCMSLVClkDomain
 *
 * AIF PRI PCM SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIPCMSLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFPRIPCMSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPRIPCMSLVClkDomainClks)/sizeof(HAL_clk_mAIFPRIPCMSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL
};


