/*
==============================================================================

FILE:         HALclkBLSP2UART3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP2UART3 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP2UART3APPSClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/gcc/HALclkBLSP2UART3.c#1 $

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
 *  HAL_clk_mBLSP2UART3APPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP2UART3APPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp2_uart3_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_UART3_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_UART3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_UART3_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP2UART3APPSClkDomain
 *
 * BLSP2UART3APPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART3APPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP2_UART3_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP2UART3APPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP2UART3APPSClkDomainClks)/sizeof(HAL_clk_mBLSP2UART3APPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

