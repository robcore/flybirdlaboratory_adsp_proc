/*
==============================================================================

FILE:         HALclkPeriphNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Periph NOC clocks.

   List of clock domains:
   -HAL_clk_mGCCPERIPHNOCClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/gcc/HALclkPeriphNOC.c#1 $

when          who     what, where, why
--------      ---     ----------------------------------------------------------- 
10/31/2012            Auto-generated.

==============================================================================
            Copyright (c) 2012 Qualcomm Technologies Incorporated.
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
 *  HAL_clk_mPERIPHNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPERIPHNOCClkDomainClks[] =
{
#if 0
  {
    /* .szClockName      = */ "gcc_snoc_pnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_PNOC_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_PNOC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_periph_noc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_AHB_CBCR), HWIO_OFFS(GCC_PERIPH_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb_hsic_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_HSIC_AHB_CBCR), HWIO_OFFS(GCC_USB_HS_HSIC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_HSIC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb_hs_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_HS_AHB_CBCR), HWIO_OFFS(GCC_USB_HS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_HS_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_AHB_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC2_AHB_CBCR), HWIO_OFFS(GCC_SDCC2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC2_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC3_AHB_CBCR), HWIO_OFFS(GCC_SDCC3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC3_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC4_AHB_CBCR), HWIO_OFFS(GCC_SDCC4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC4_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_blsp1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_AHB_CBCR), HWIO_OFFS(GCC_BLSP1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_blsp2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_AHB_CBCR), HWIO_OFFS(GCC_BLSP2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8974
  },
  {
    /* .szClockName      = */ "gcc_periph_xpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_XPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_XPU_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_periph_noc_mpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_MPU_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_MPU_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pdm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PDM_AHB_CBCR), HWIO_OFFS(GCC_PDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PDM_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_prng_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PRNG_AHB_CBCR), HWIO_OFFS(GCC_PRNG_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, PRNG_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PRNG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_bam_dma_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BAM_DMA_AHB_CBCR), HWIO_OFFS(GCC_BAM_DMA_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BAM_DMA_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BAM_DMA_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_tsif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TSIF_AHB_CBCR), HWIO_OFFS(GCC_TSIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TSIF_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_spdm_pnoc_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_PNOC_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_PNOC_CY_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT0_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT0_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT1_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT2_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT3_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_pnoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_PNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PNOC_BUS_TIMEOUT4_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
};


/*
 * HAL_clk_mGCCPERIPHNOCClkDomain
 *
 * PERIPH NOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCPERIPHNOCClkDomain =
{
  /* .nCGRAddr             = */ 0, /*HWIO_OFFS(GCC_PERIPH_NOC_CMD_RCGR),*/
  /* .pmClocks             = */ HAL_clk_mPERIPHNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPERIPHNOCClkDomainClks)/sizeof(HAL_clk_mPERIPHNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


