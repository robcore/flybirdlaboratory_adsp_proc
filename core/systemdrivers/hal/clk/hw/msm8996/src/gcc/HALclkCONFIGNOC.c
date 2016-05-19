/*
==============================================================================

FILE:         HALclkCONFIGNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CONFIGNOC clocks.

   List of clock domains:
     - HAL_clk_mGCCCONFIGNOCClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkCONFIGNOC.c#1 $

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
 *  HAL_clk_mCONFIGNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCONFIGNOCClkDomainClks[] =
{
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre0_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE0_CNOC_AHB_CBCR), HWIO_OFFS(GCC_AGGRE0_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE0_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre0_noc_mpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE0_NOC_MPU_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE0_NOC_MPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre1_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE1_CNOC_AHB_CBCR), HWIO_OFFS(GCC_AGGRE1_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE1_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre1_noc_mpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE1_NOC_MPU_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE1_NOC_MPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre2_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_CNOC_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_aggre2_noc_mpu_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_MPU_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_MPU_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_bimc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_CFG_AHB_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_bimc_nius_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_NIUS_CFG_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_NIUS_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_boot_rom_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BOOT_ROM_AHB_CBCR), HWIO_OFFS(GCC_BOOT_ROM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BOOT_ROM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BOOT_ROM_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_ce1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_AHB_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_AHB_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT0_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT1_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT2_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT3_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT4_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout6_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT6_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT6_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout7_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT7_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT7_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT7_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout8_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT8_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT8_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT8_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout9_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT9_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT9_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT9_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_cnoc_mst_rpm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_MST_RPM_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_MST_RPM_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_dcc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DCC_AHB_CBCR), HWIO_OFFS(GCC_DCC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DCC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_imem_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IMEM_CFG_AHB_CBCR), HWIO_OFFS(GCC_IMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IMEM_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_lpass_core_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_CORE_SMMU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_CORE_SMMU_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_lpass_q6_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_Q6_SMMU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_Q6_SMMU_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_lpass_smmu_aon_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_SMMU_AON_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_SMMU_AON_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_mmss_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_NOC_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_mpm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MPM_AHB_CBCR), HWIO_OFFS(GCC_MPM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MPM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MPM_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_msg_ram_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSG_RAM_AHB_CBCR), HWIO_OFFS(GCC_MSG_RAM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSG_RAM_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_noc_conf_xpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_NOC_CONF_XPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NOC_CONF_XPU_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_0_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_0_CFG_AHB_CBCR), HWIO_OFFS(GCC_PCIE_0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_0_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_1_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_1_CFG_AHB_CBCR), HWIO_OFFS(GCC_PCIE_1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_1_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_2_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_2_CFG_AHB_CBCR), HWIO_OFFS(GCC_PCIE_2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_2_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pcie_phy_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PCIE_PHY_CFG_AHB_CBCR), HWIO_OFFS(GCC_PCIE_PHY_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PCIE_PHY_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_periph_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_PERIPH_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_pimem_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PIMEM_AHB_CBCR), HWIO_OFFS(GCC_PIMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PIMEM_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_prng_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PRNG_AHB_CBCR), HWIO_OFFS(GCC_PRNG_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, PRNG_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PRNG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_qdss_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_CFG_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_qdss_dap_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_DAP_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_DAP_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_qdss_mpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_MPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_MPU_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_rbcpr_cx_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_CX_AHB_CBCR), HWIO_OFFS(GCC_RBCPR_CX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_CX_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_rbcpr_mx_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_MX_AHB_CBCR), HWIO_OFFS(GCC_RBCPR_MX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_MX_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_rbcpr_xpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_XPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_XPU_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_rpm_mst_m2_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_MST_M2_CNOC_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_MST_M2_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_AHB_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_boot_rom_patch_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_BOOT_ROM_PATCH_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_BOOT_ROM_PATCH_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE0_AHB_CBCR), HWIO_OFFS(GCC_AGGRE0_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE0_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE1_AHB_CBCR), HWIO_OFFS(GCC_AGGRE1_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE1_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_smmu_aggre2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SMMU_AGGRE2_AHB_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SMMU_AGGRE2_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_snoc_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_CNOC_AHB_CLK
  },
#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_spdm_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_CFG_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_CFG_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_spdm_mstr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_MSTR_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_MSTR_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_spmi_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPMI_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SPMI_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, SPMI_CNOC_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPMI_CNOC_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_ssc_cnoc_ahbs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SSC_CNOC_AHBS_CBCR), HWIO_OFFS(GCC_SSC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SSC_CNOC_AHBS_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_ssc_cnoc_mpu_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SSC_CNOC_MPU_CBCR), HWIO_OFFS(GCC_SSC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SSC_CNOC_MPU_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_tcsr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TCSR_AHB_CBCR), HWIO_OFFS(GCC_TCSR_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TCSR_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TCSR_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_tlmm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_AHB_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_AHB_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_tlmm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_CLK
  },
#endif

#if 0 /* not present on lpass */

  {
    /* .szClockName      = */ "gcc_ufs_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_AHB_CBCR), HWIO_OFFS(GCC_UFS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_UFS_AHB_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCCONFIGNOCClkDomain
 *
 * CONFIGNOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* read only for lpass */
  /* .pmClocks             = */ HAL_clk_mCONFIGNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCONFIGNOCClkDomainClks)/sizeof(HAL_clk_mCONFIGNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

