/*
==============================================================================

FILE:         HALclkBLSP2UART6.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP2 UART6 clocks.

   List of clock domains:
   -HAL_clk_mGCCBLSP2UART6ClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/gcc/HALclkBLSP2UART6.c#1 $

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
 *  HAL_clk_mBLSP2UART6ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP2UART6ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp2_uart6_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_UART6_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_UART6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_UART6_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP2UART6ClkDomain
 *
 * BLSP2 UART6 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART6ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP2_UART6_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP2UART6ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP2UART6ClkDomainClks)/sizeof(HAL_clk_mBLSP2UART6ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


