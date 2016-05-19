/*
==============================================================================

FILE:         HALclkSYSTEMNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SYSTEMNOC clocks.

   List of clock domains:
     - HAL_clk_mGCCSYSTEMNOCClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkSYSTEMNOC.c#1 $

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
 *  HAL_clk_mSYSTEMNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSYSTEMNOCClkDomainClks[] =
{
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre0_snoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE0_SNOC_AXI_CBCR), HWIO_OFFS(GCC_AGGRE0_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE0_SNOC_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre1_snoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE1_SNOC_AXI_CBCR), HWIO_OFFS(GCC_AGGRE1_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE1_SNOC_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre2_snoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_SNOC_AXI_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_SNOC_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_bimc_nius_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_NIUS_AXI_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_NIUS_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_bimc_sysnoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_SYSNOC_AXI_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_SYSNOC_AXI_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_ce1_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_AXI_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_AXI_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_imem_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IMEM_AXI_CBCR), HWIO_OFFS(GCC_IMEM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IMEM_AXI_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_lpass_sway_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_SWAY_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_SWAY_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_mmss_sys_noc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_SYS_NOC_AXI_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_SYS_NOC_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_0_mstr_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_0_MSTR_AXI_CBCR), HWIO_OFFS(GCC_PCIE_0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_0_MSTR_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_0_slv_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_0_SLV_AXI_CBCR), HWIO_OFFS(GCC_PCIE_0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_0_SLV_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_1_mstr_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_1_MSTR_AXI_CBCR), HWIO_OFFS(GCC_PCIE_1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_1_MSTR_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_1_slv_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_1_SLV_AXI_CBCR), HWIO_OFFS(GCC_PCIE_1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_1_SLV_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_2_mstr_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_2_MSTR_AXI_CBCR), HWIO_OFFS(GCC_PCIE_2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_2_MSTR_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_2_slv_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_2_SLV_AXI_CBCR), HWIO_OFFS(GCC_PCIE_2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_2_SLV_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_qdss_etr_usb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_ETR_USB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_ETR_USB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre0_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE0_AXI_CBCR), HWIO_OFFS(GCC_AGGRE0_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE0_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre1_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE1_AXI_CBCR), HWIO_OFFS(GCC_AGGRE1_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE1_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre2_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE2_AXI_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE2_AXI_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_snoc_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_BUS_TIMEOUT1_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_snoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_SNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_BUS_TIMEOUT3_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_ssc_snoc_ahbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SSC_SNOC_AHBM_CBCR), HWIO_OFFS(GCC_SSC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SSC_SNOC_AHBM_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_sys_noc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_AXI_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_AXI_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sys_noc_ssc_q6_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_SSC_Q6_AXI_CBCR), HWIO_OFFS(GCC_SSC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_SSC_Q6_AXI_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCSYSTEMNOCClkDomain
 *
 * SYSTEMNOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* read only for lpass */
  /* .pmClocks             = */ HAL_clk_mSYSTEMNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSYSTEMNOCClkDomainClks)/sizeof(HAL_clk_mSYSTEMNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

