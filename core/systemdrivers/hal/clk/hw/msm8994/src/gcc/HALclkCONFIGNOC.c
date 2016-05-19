/*
==============================================================================

FILE:         HALclkConfigNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Config NOC clocks.

   List of clock domains:
   -HAL_clk_mGCCCONFNOCClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/gcc/HALclkCONFIGNOC.c#1 $

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
 *  HAL_clk_mCONFNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCONFNOCClkDomainClks[] =
{
#if 0
  {
    /* .szClockName      = */ "gcc_snoc_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SNOC_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SNOC_CNOC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_lpss_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPSS_SMMU_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPSS_SMMU_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_copss_smmu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_COPSS_SMMU_AHB_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_COPSS_SMMU_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_periph_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PERIPH_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_PERIPH_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PERIPH_NOC_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_noc_conf_xpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_NOC_CONF_XPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_NOC_CONF_XPU_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_imem_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IMEM_CFG_AHB_CBCR), HWIO_OFFS(GCC_IMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IMEM_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_ocmem_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_OCMEM_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_OCMEM_NOC_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ (HAL_CLK_CHIPSET_MSM8974)
  },
  {
    /* .szClockName      = */ "gcc_mmss_noc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_NOC_CFG_AHB_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_NOC_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_mss_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_CFG_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_qdss_rbcpr_xpu_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_RBCPR_XPU_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_RBCPR_XPU_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_qdss_dap_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_DAP_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_DAP_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_qdss_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_CFG_AHB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_tcsr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TCSR_AHB_CBCR), HWIO_OFFS(GCC_TCSR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TCSR_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_boot_rom_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BOOT_ROM_AHB_CBCR), HWIO_OFFS(GCC_BOOT_ROM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BOOT_ROM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BOOT_ROM_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_msg_ram_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSG_RAM_AHB_CBCR), HWIO_OFFS(GCC_MSG_RAM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSG_RAM_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_tlmm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_AHB_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_tlmm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TLMM_CBCR), HWIO_OFFS(GCC_TLMM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, TLMM_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TLMM_CLK
  },
  {
    /* .szClockName      = */ "gcc_mpm_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MPM_AHB_CBCR), HWIO_OFFS(GCC_MPM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, MPM_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MPM_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_sec_ctrl_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_AHB_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sec_ctrl_boot_rom_patch_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_BOOT_ROM_PATCH_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_BOOT_ROM_PATCH_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_spmi_cnoc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPMI_CNOC_AHB_CBCR), HWIO_OFFS(GCC_SPMI_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, SPMI_CNOC_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPMI_CNOC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_spdm_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_CFG_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_spdm_mstr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_MSTR_AHB_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_MSTR_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_ce1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_AHB_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_ce2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE2_AHB_CBCR), HWIO_OFFS(GCC_CE2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE2_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE2_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8974
  },
  {
    /* .szClockName      = */ "gcc_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_bimc_cfg_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_CFG_AHB_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_CFG_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout0_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT0_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout1_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT1_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT1_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout2_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT2_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout3_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT3_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout4_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT4_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_dehr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DEHR_CBCR), HWIO_OFFS(GCC_DEHR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DEHR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_rbcpr_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RBCPR_AHB_CBCR), HWIO_OFFS(GCC_RBCPR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RBCPR_AHB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
};


/*
 * HAL_clk_mGCCCONFNOCClkDomain
 *
 * CONF NOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFNOCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_CONFIG_NOC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCONFNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCONFNOCClkDomainClks)/sizeof(HAL_clk_mCONFNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


