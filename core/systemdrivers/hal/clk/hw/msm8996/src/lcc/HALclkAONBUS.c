/*
==============================================================================

FILE:         HALclkAONBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AONBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSAONClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkAONBUS.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mAONClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAONClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_qdsp_sway_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_QDSP_SWAY_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_bus_timeout_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_mpu_cfg_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_MPU_CFG_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_q6_ahbm_mpu_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_qos_ahbs_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_QOS_AHBS_AON_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_sysnoc_sway_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CLK
  },
  {
    /* .szClockName      = */ "q6ss_ahbm_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_AHBM_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_AHBM_AON_CLK
  },
  {
    /* .szClockName      = */ "q6ss_ahbs_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_AHBS_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_AHBS_AON_CLK
  },
};


/*
 * HAL_clk_mLPASSAONClkDomain
 *
 * AON clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAONClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_AON_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAONClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAONClkDomainClks)/sizeof(HAL_clk_mAONClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

