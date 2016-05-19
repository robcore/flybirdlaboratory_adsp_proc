/*
==============================================================================

FILE:         HALclkQUATERNARYMI2S.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QUATERNARYMI2S clocks.

   List of clock domains:
     - HAL_clk_mLPASSQUADMCLKClkDomain
     - HAL_clk_mLPASSLPAIFQUADClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkQUATERNARYMI2S.c#1 $

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
 *  HAL_clk_mAIFQUAMI2SSLVClkDomainClks
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
 * AIF QUA MI2S SLV clock domain.
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


/*                           
 *  HAL_clk_mQUADMCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQUADMCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_quad_mclk_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QUAD_MCLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_QUAD_MCLK_CLK
  },
};


/*
 * HAL_clk_mLPASSQUADMCLKClkDomain
 *
 * QUADMCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQUADMCLKClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_QUAD_MCLK_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQUADMCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQUADMCLKClkDomainClks)/sizeof(HAL_clk_mQUADMCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


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
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_cdiv_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
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
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

