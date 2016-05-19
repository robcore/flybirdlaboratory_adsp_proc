/*
==============================================================================

FILE:         HALclkAIFPRIMI2SMSTR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF PRI MI2S MSTR clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFPRIMI2SMSTRClkDomain
   -HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/lcc/HALclkAIFPRIMI2SMSTR.c#1 $

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
 *  HAL_clk_mAIFPRIMI2SMSTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFPRIMI2SMSTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pri_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_pri_cdiv_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_pri_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFPRIMI2SMSTRClkDomain
 *
 * AIF PRI MI2S MSTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIMI2SMSTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PRI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFPRIMI2SMSTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPRIMI2SMSTRClkDomainClks)/sizeof(HAL_clk_mAIFPRIMI2SMSTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


                                    
/*                           
 *  HAL_clk_mAIFPRIMI2SSLVClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFPRIMI2SSLVClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_pri_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain
 *
 * AIF PRI MI2S SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFPRIMI2SSLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFPRIMI2SSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFPRIMI2SSLVClkDomainClks)/sizeof(HAL_clk_mAIFPRIMI2SSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


