/*
==============================================================================

FILE:         HALclkSECONDARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SECONDARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFPCM1ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkSECONDARYPCM.c#1 $

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
 *  HAL_clk_mLPAIFPCM1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFPCM1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm1_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSLPAIFPCM1ClkDomain
 *
 * LPAIFPCM1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PCM1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFPCM1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFPCM1ClkDomainClks)/sizeof(HAL_clk_mLPAIFPCM1ClkDomainClks[0]),
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
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFSECPCMSLVClkDomain
 *
 * AIF SEC PCM SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM1SLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFSECPCMSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFSECPCMSLVClkDomainClks)/sizeof(HAL_clk_mAIFSECPCMSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


