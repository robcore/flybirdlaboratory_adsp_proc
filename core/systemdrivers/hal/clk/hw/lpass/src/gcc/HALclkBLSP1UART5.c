/*
==============================================================================

FILE:         HALclkBLSP1UART5.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP1 UART5 clocks.

   List of clock domains:
   -HAL_clk_mGCCBLSP1UART5ClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/gcc/HALclkBLSP1UART5.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mBLSP1UART5ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1UART5ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_uart5_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_UART5_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_UART5_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_UART5_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1UART5ClkDomain
 *
 * BLSP1 UART5 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART5ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_UART5_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1UART5ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1UART5ClkDomainClks)/sizeof(HAL_clk_mBLSP1UART5ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


