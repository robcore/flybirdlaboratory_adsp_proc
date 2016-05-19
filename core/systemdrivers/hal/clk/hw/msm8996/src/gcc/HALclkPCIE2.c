/*
==============================================================================

FILE:         HALclkPCIE2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   PCIE2 clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mGCCPCIE2PowerDomain



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkPCIE2.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
06/16/2014           Auto-generated.


==============================================================================
            Copyright (c) 2014 QUALCOMM Technologies Incorporated.
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
 * HAL_clk_mGCCPCIE2PowerDomain
 *
 * PCIE_2 power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCPCIE2PowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_PCIE_2",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_PCIE_2_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

