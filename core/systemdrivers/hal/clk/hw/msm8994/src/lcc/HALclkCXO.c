/*
==============================================================================

FILE:         HALclkCXO.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CXO clocks.

   List of clock domains:
     - HAL_clk_mLPASSQ6XOClkDomain
     - HAL_clk_mLPASSGDSCXOClkDomain
     - HAL_clk_mLPASSSTMXOClkDomain
     - HAL_clk_mLPASSAVTIMERXOClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkCXO.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
12/03/2013           auto-generated.


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
extern HAL_clk_ClockControlType HAL_clk_mConfigClockControl;
/* ============================================================================
**    Data
** ==========================================================================*/


/*
 *  HAL_clk_mQ6XOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQ6XOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSQ6XOClkDomain
 *
 * Q6XO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6XOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQ6XOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQ6XOClkDomainClks)/sizeof(HAL_clk_mQ6XOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


/*                           
 *  HAL_clk_mGDSCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGDSCXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_GDSC_XO_CLK
  },
};


/*
 * HAL_clk_mLPASSGDSCXOClkDomain
 *
 * GDSCXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSGDSCXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mGDSCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGDSCXOClkDomainClks)/sizeof(HAL_clk_mGDSCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


/*                           
 *  HAL_clk_mSTMXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSTMXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_stm_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_STM_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSTMXOClkDomain
 *
 * STMXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSTMXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mSTMXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSTMXOClkDomainClks)/sizeof(HAL_clk_mSTMXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

                                    
/*                           
 *  HAL_clk_mCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_avsync_avtimer_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVTIMER_XO_CLK
  },
};


/*
 * HAL_clk_mLPASSAVTIMERXOClkDomain
 *
 * CXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAVTIMERXOClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCXOClkDomainClks)/sizeof(HAL_clk_mCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};

