/*
==============================================================================

FILE:         HALclkBLSP2QUP6.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP2QUP6 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain
     - HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/gcc/HALclkBLSP2QUP6.c#1 $

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
 *  HAL_clk_mBLSP2QUP6SPIAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP2QUP6SPIAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp2_qup6_spi_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP6_SPI_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP6_SPI_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain
 *
 * BLSP2QUP6SPIAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP2_QUP6_SPI_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP2QUP6SPIAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP2QUP6SPIAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP2QUP6SPIAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBLSP2QUP6I2CAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP2QUP6I2CAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp2_qup6_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP6_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP6_I2C_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain
 *
 * BLSP2QUP6I2CAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP2_QUP6_I2C_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP2QUP6I2CAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP2QUP6I2CAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP2QUP6I2CAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

