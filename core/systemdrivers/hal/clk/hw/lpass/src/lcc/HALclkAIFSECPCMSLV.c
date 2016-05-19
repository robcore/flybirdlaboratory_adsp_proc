/*
==============================================================================

FILE:         HALclkAIFSECPCMSLV.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF SEC PCM SLV clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFSECPCMMSTRClkDomain
   -HAL_clk_mLPASSAIFSECPCMSLVClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkAIFSECPCMSLV.c#1 $

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
 *  HAL_clk_mAIFSECPCMMSTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFSECPCMMSTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm1_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFSECPCMMSTRClkDomain
 *
 * AIF SEC PCM MSTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECPCMMSTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PCM1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFSECPCMMSTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFSECPCMMSTRClkDomainClks)/sizeof(HAL_clk_mAIFSECPCMMSTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


                                    
/*                           
 *  HAL_clk_mAIFSECPCMSLVClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFSECPCMSLVClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm1_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFSECPCMSLVClkDomain
 *
 * AIF SEC PCM SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECPCMSLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFSECPCMSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFSECPCMSLVClkDomainClks)/sizeof(HAL_clk_mAIFSECPCMSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


