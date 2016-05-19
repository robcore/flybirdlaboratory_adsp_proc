/*
==============================================================================

FILE:         HALclkCXO.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CXO clocks.

   List of clock domains:
   -HAL_clk_mLPASSCXOClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkCXO.c#1 $

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


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockControlType HAL_clk_mConfigClockControl;
/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_avsync_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_XO_V1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_XO_CLK,
    /* .nChipsetFlag     = */ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "audio_core_avsync_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "audio_core_avsync_bt_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_BT_XO_V1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_BT_XO_CLK,
    /* .nChipsetFlag     = */ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "audio_core_avsync_bt_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_BT_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "audio_core_avsync_fm_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_FM_XO_V1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_FM_XO_CLK,
    /* .nChipsetFlag     = */ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "audio_core_avsync_fm_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_FM_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  },
  {
    /* .szClockName      = */ "q6ss_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_Q6SS_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_GDSC_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_wrapper_stm_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_STM_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "audio_core_avsync_avtimer_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVTIMER_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL &~ (HAL_CLK_CHIP_FLAG_MSM8974 | HAL_CLK_CHIP_FLAG_MSM8x26 | HAL_CLK_CHIP_FLAG_MSM8x10)
  }
};


/*
 * HAL_clk_mLPASSCXOClkDomain
 *
 * CXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCXOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_XO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mXOClkDomainClks)/sizeof(HAL_clk_mXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL,
  /* .bSPMHWVoter          = */ TRUE
};


