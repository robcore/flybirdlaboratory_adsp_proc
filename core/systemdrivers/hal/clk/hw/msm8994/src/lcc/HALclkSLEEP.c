/*
==============================================================================

FILE:         HALclkSLEEP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SLEEP clocks.

   List of clock domains:
     - HAL_clk_mLPASSSLEEPClkDomain
     - HAL_clk_mLPASSQ6SSBCRSLPClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkSLEEP.c#1 $

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


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mSLEEPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLEEPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSLEEPClkDomain
 *
 * SLEEP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLEEPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLEEPClkDomainClks)/sizeof(HAL_clk_mSLEEPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


/*                           
 *  HAL_clk_mQ6SSBCRSLPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQ6SSBCRSLPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_BCR_SLP_CLK
  },
  {
    /* .szClockName      = */ "q6ss_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_BCR_SLP_CLK
  },
};


/*
 * HAL_clk_mLPASSQ6SSBCRSLPClkDomain
 *
 * Q6SSBCRSLP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SSBCRSLPClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQ6SSBCRSLPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQ6SSBCRSLPClkDomainClks)/sizeof(HAL_clk_mQ6SSBCRSLPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

