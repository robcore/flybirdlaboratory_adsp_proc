/*
==============================================================================

FILE:         HALclkPERIPHNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   PERIPHNOC clocks.

   List of clock domains:
     - HAL_clk_mGCCPERIPHNOCClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkPERIPHNOC.c#1 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mPERIPHNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPERIPHNOCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_aggre1_pnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE1_PNOC_AHB_CBCR), HWIO_OFFS(GCC_AGGRE1_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE1_PNOC_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_blsp1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_AHB_CBCR), HWIO_OFFS(GCC_BLSP1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_blsp2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_AHB_CBCR), HWIO_OFFS(GCC_BLSP2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_AHB_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pdm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PDM_AHB_CBCR), HWIO_OFFS(GCC_PDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PDM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_periph_noc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_AHB_CBCR), HWIO_OFFS(GCC_PERIPH_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_AHB_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_periph_noc_mpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_MPU_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_MPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT1_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT2_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT3_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT4_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sdcc1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_AHB_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sdcc2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC2_AHB_CBCR), HWIO_OFFS(GCC_SDCC2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC2_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sdcc3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC3_AHB_CBCR), HWIO_OFFS(GCC_SDCC3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC3_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sdcc4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC4_AHB_CBCR), HWIO_OFFS(GCC_SDCC4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC4_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_snoc_pnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_PNOC_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_PNOC_AHB_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_tsif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TSIF_AHB_CBCR), HWIO_OFFS(GCC_TSIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TSIF_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_usb_phy_cfg_ahb2phy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_PHY_CFG_AHB2PHY_CBCR), HWIO_OFFS(GCC_USB_PHY_CFG_AHB2PHY_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_PHY_CFG_AHB2PHY_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCPERIPHNOCClkDomain
 *
 * PERIPHNOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCPERIPHNOCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* read only for lpass */
  /* .pmClocks             = */ HAL_clk_mPERIPHNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPERIPHNOCClkDomainClks)/sizeof(HAL_clk_mPERIPHNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

