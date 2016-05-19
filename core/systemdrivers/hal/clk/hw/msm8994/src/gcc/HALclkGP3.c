/*
==============================================================================

FILE:         HALclkGP3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GP3 clocks.

   List of clock domains:
     - HAL_clk_mGCCGP3ClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/gcc/HALclkGP3.c#1 $

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
 *  HAL_clk_mGP3ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGP3ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_gp3_clk",
    /* .mRegisters       = */ { HWIO_OFF(GCC_GP3_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mGCCGP3ClkDomain
 *
 * GP3 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCGP3ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GP3_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mGP3ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGP3ClkDomainClks)/sizeof(HAL_clk_mGP3ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

