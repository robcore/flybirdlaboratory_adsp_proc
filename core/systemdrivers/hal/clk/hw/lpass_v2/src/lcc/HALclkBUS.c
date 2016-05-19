/*
==============================================================================

FILE:         HALclkBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BUS clocks.

   List of clock domains:
   -HAL_clk_mLPASSBUSClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/src/lcc/HALclkBUS.c#1 $

when          who     what, where, why
----------    ---     --------------------------------------------------------
05/20/2013            Auto-generated.

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

void HAL_clk_BusConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
);


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSBusClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

#define HAL_CLK_MEM_CORE_ON_BMSK               0x00004000
#define HAL_CLK_MEM_PERIPH_ON_BMSK             0x00002000
#define HAL_CLK_HW_CTL_ON_BMSK                 0x00000002
#define HAL_CLK_CONFIG_LPASS_CORE_CLK_OFF_BMSK 0x80000000

/*
 * HAL_clk_mBusClockControl
 *
 * Functions for controlling common clock functions.
 */
HAL_clk_ClockControlType HAL_clk_mConfigClockControl =
{
  /* .Enable           = */ HAL_clk_GenericEnable,
  /* .Disable          = */ HAL_clk_GenericDisable,
  /* .IsEnabled        = */ HAL_clk_GenericIsEnabled,
  /* .IsOn             = */ HAL_clk_GenericIsOn,
  /* .Reset            = */ HAL_clk_GenericReset,
  /* .IsReset          = */ HAL_clk_GenericIsReset,
  /* .Config           = */ HAL_clk_BusConfig,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ HAL_clk_GenericConfigDivider,
  /* .DetectDivider    = */ HAL_clk_GenericDetectDivider,
  /* .ConfigFootswitch = */ HAL_clk_GenericConfigFootswitch,
};


/*                           
 *  HAL_clk_mBUSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBUSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_ixfabric_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_IXFABRIC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_IXFABRIC_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_ixfabric_spdmtm_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_tcm_slave_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_TCM_SLAVE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_CSR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_dml_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_DML_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_DML_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_dma_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_DMA_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_DMA_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_lpaif_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_CSR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_avsync_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_CSR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_sysnoc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SYSNOC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SYSNOC_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MSM8962
  },
  {
    /* .szClockName      = */ "audio_core_lpm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPM_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_slimbus_lfabif_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SLIMBUS_LFABIF_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_resampler_lfabif_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_RESAMPLER_LFABIF_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_efabric_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_EFABRIC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_EFABRIC_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_security_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SECURITY_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SECURITY_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_security_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SECURITY_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_SECURITY_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_lcc_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_LCC_CSR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_sysnoc_sway_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "q6ss_ahbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_AHBM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_AHBM_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "q6ss_ahb_lfabif_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_AHB_LFABIF_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_AHB_LFABIF_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_smem_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SMEM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_SMEM_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_br_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_BR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_BR_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_timeout_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_TIMEOUT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_TIMEOUT_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_timeout_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_TIMEOUT_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_efabric_spdmtm_csr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CLK,
  },
  {
    /* .szClockName      = */ "spdiftx_ahbs_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_SPDIFTX_AHBS_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_SPDIFTX_AHBS_CLK
  },
  {
    /* .szClockName      = */ "spdiftx_ahbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_SPDIFTX_AHBM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_SPDIFTX_AHBM_CLK
  },
  {
    /* .szClockName      = */ "sif_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_SIF_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_SIF_AHB_CLK
  },
  {
    /* .szClockName      = */ "hdmirx_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_HDMIRX_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_HDMIRX_AHB_CLK
  },
  {
    /* .szClockName      = */ "ahb_spdmtm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AHB_SPDM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AHB_SPDMTM_CLK
  },
  {
    /* .szClockName      = */ "audio_core_bstc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_BSTC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_BSTC_CLK
  },
  {
    /* .szClockName      = */ "core_smmu_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_CORE_SMMU_CFG_CLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_CORE_SMMU_CFG_CLK
  },
  {
    /* .szClockName      = */ "q6_smmu_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6_SMMU_CFG_CLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6_SMMU_CFG_CLK
  },
  {
    /* .szClockName      = */ "audio_core_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AON_CLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_AON_CLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_AON_CLK
  },
  {
    /* .szClockName      = */ "gcc_lpass_sys_noc_mport_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_MIDI_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
};


/*
 * HAL_clk_mLPASSBUSClkDomain
 *
 * BUS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSBUSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_AHBFABRIC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBUSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBUSClkDomainClks)/sizeof(HAL_clk_mBUSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSBusClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

void HAL_clk_BusConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
)
{
  uint32 nAddr = 0;
  uint32 nValue = 0;

  if(NULL != pmClockDesc)
  {
    nAddr = pmClockDesc->mRegisters.nBranchAddr;

    if(nAddr != 0)
    {
      nValue = inpdw(nAddr);

      switch(eConfig)
      {
        case HAL_CLK_CONFIG_LPASS_CORE_MEM_ON:
          nValue |= HAL_CLK_MEM_CORE_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_PERIPH_MEM_ON:
          nValue |= HAL_CLK_MEM_PERIPH_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_CORE_MEM_OFF:
          nValue &= ~HAL_CLK_MEM_CORE_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_PERIPH_MEM_OFF:
          nValue &= ~HAL_CLK_MEM_PERIPH_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_HW_CTL_ON:
          nValue |= HAL_CLK_HW_CTL_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_HW_CTL_OFF:
          nValue &= ~HAL_CLK_HW_CTL_ON_BMSK;
          outpdw(nAddr, nValue);
          break;
 
        default:
          break;
      }
    }
  }

} /* HAL_clk_BusConfig */

