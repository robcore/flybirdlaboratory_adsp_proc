/*
==============================================================================

FILE:         HALclkSystemNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   System NOC clocks.

   List of clock domains:
   -HAL_clk_mGCCSYSNOCClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/gcc/HALclkSystemNOC.c#1 $

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
 *  HAL_clk_mSYSNOCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSYSNOCClkDomainClks[] =
{
#if 0
  {
    /* .szClockName      = */ "gcc_sys_noc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_AXI_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_imem_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IMEM_AXI_CBCR), HWIO_OFFS(GCC_IMEM_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, IMEM_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IMEM_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_ocmem_sys_noc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_OCMEM_SYS_NOC_AXI_CBCR), HWIO_OFFS(GCC_MMSS_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, OCMEM_SYS_NOC_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_OCMEM_SYS_NOC_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_qdss_etr_usb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QDSS_ETR_USB_CBCR), HWIO_OFFS(GCC_QDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QDSS_ETR_USB_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_spdm_snoc_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_SNOC_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_SNOC_CY_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_ce1_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_AXI_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_ce2_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE2_AXI_CBCR), HWIO_OFFS(GCC_CE2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE2_AXI_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE2_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_bimc_sysnoc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_SYSNOC_AXI_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_SYSNOC_AXI_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_lpass_q6_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_LPASS_CORE_AXIM_VOTE_LPASSQ6), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_Q6_AXI_CLK,
  },
#endif
  {
    /* .szClockName      = */ "gcc_lpass_sys_noc_sway_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_LPASS_SYS_NOC_SWAY_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_LPASS_SYS_NOC_SWAY_CLK
  },
};


/*
 * HAL_clk_mGCCSYSNOCClkDomain
 *
 * SYS NOC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSNOCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* HWIO_OFFS(GCC_SYSTEM_NOC_CMD_RCGR), */
  /* .pmClocks             = */ HAL_clk_mSYSNOCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSYSNOCClkDomainClks)/sizeof(HAL_clk_mSYSNOCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


