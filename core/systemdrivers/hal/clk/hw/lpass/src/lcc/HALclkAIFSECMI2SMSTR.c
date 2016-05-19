/*
==============================================================================

FILE:         HALclkAIFSECMI2SMSTR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AIF SEC MI2S MSTR clocks.

   List of clock domains:
   -HAL_clk_mLPASSAIFSECMI2SMSTRClkDomain
   -HAL_clk_mLPASSAIFSECMI2SSLVClkDomain
   -HAL_clk_mLPASSSECMCLKClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkAIFSECMI2SMSTR.c#1 $

when          who     what, where, why
----------    ---     --------------------------------------------------------
08/14/2013            Auto-generated.

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
 *  HAL_clk_mAIFSECMI2SSLVClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFSECMI2SSLVClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFSECMI2SSLVClkDomain
 *
 * AIF SEC MI2S SLV clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECMI2SSLVClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mAIFSECMI2SSLVClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFSECMI2SSLVClkDomainClks)/sizeof(HAL_clk_mAIFSECMI2SSLVClkDomainClks[0]),
  /* .pmControl            = */ NULL,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


                                    
/*                           
 *  HAL_clk_mAIFSECMI2SMSTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAIFSECMI2SMSTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPAIF_SEC_CLK_SRC,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_cdiv_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ HAL_CLK_CHIP_FLAG_MSM8974
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_sec_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSAIFSECMI2SMSTRClkDomain
 *
 * AIF SEC MI2S MSTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAIFSECMI2SMSTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_SEC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAIFSECMI2SMSTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAIFSECMI2SMSTRClkDomainClks)/sizeof(HAL_clk_mAIFSECMI2SMSTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

                                    
/*                           
 *  HAL_clk_mSECMCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSECMCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_sec_mclk_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SEC_MCLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0, /* HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_SEC_MCLK_CLK */
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MPQ8092
  },
};


/*
 * HAL_clk_mLPASSSECMCLKClkDomain
 *
 * SEC MCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSECMCLKClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SEC_MCLK_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSECMCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSECMCLKClkDomainClks)/sizeof(HAL_clk_mSECMCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


