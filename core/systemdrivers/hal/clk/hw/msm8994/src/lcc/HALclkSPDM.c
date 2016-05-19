/*
==============================================================================

FILE:         HALclkSPDM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SPDM clocks.

   List of clock domains:
     - HAL_clk_mLPASSQ6SPDMClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/lcc/HALclkSPDM.c#1 $

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
 *  HAL_clk_mQ6SPDMClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQ6SPDMClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6_spdm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6_SPDM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6_SPDM_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSQ6SPDMClkDomain
 *
 * Q6SPDM clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SPDMClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_Q6_SPDM_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQ6SPDMClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQ6SPDMClkDomainClks)/sizeof(HAL_clk_mQ6SPDMClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


