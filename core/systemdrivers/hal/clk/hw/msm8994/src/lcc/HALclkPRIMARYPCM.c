/*
==============================================================================

FILE:         HALclkPRIMARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   PRIMARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFPCM0ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkPRIMARYPCM.c#1 $

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
 *  HAL_clk_mLPAIFPCM0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFPCM0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pcm0_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSLPAIFPCM0ClkDomain
 *
 * LPAIFPCM0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PCM0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFPCM0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFPCM0ClkDomainClks)/sizeof(HAL_clk_mLPAIFPCM0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
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
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFPRIPCMSLVClkDomain
 *
 * AIF PRI PCM SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCM0SLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFPRIPCMSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPRIPCMSLVClkDomainClks)/sizeof(HAL_clk_mAIFPRIPCMSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

