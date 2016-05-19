/*
==============================================================================

FILE:         HALclkAIFQUADMI2SMSTR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF QUAD MI2S MSTR clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFQUADMI2SMSTRClkDomain
   -HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/lcc/HALclkAIFQUADMI2SMSTR.c#1 $

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
 *  HAL_clk_mAIFQUADMI2SMSTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFQUADMI2SMSTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_cdiv_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFQUADMI2SMSTRClkDomain
 *
 * AIF QUAD MI2S MSTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFQUADMI2SMSTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_QUAD_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFQUADMI2SMSTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFQUADMI2SMSTRClkDomainClks)/sizeof(HAL_clk_mAIFQUADMI2SMSTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


                                    
/*                           
 *  HAL_clk_mAIFQUADMI2SSLVClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFQUADMI2SSLVClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain
 *
 * AIF QUAD MI2S SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFQUADMI2SSLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFQUADMI2SSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFQUADMI2SSLVClkDomainClks)/sizeof(HAL_clk_mAIFQUADMI2SSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


