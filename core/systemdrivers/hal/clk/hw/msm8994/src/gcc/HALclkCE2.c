/*
==============================================================================

FILE:         HALclkCE2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CE2 clocks.

   List of clock domains:
     - HAL_clk_mGCCCE2ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/gcc/HALclkCE2.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
11/01/2013           auto-generated.


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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCE2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCE2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ce2_clk",
    /* .mRegisters       = */ { HWIO_OFF(GCC_CE2_CBCR), HWIO_OFFS(GCC_CE2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE2_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE2_CLK
  },
};


/*
 * HAL_clk_mGCCCE2ClkDomain
 *
 * CE2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCE2ClkDomain =
{
  /* .nCGRAddr             = */ 0, /* read only for lpass */
  /* .pmClocks             = */ HAL_clk_mCE2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCE2ClkDomainClks)/sizeof(HAL_clk_mCE2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

