/*
==============================================================================

FILE:         HALclkUFS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   UFS clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mGCCUFSPowerDomain



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkUFS.c#1 $

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
 * HAL_clk_mGCCUFSPowerDomain
 *
 * UFS power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCUFSPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_UFS",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_UFS_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

