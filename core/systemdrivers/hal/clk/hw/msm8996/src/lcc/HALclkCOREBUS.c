/*
==============================================================================

FILE:         HALclkCOREBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   COREBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSCOREClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkCOREBUS.c#1 $

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
 *  HAL_clk_mCOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_aud_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AUD_SLIMBUS_CORE_CLK
  },
  {
    /* .szClockName      = */ "audio_core_qca_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_QCA_SLIMBUS_CORE_CLK
  },
  {
    /* .szClockName      = */ "audio_core_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_CORE_CLK
  },
  {
    /* .szClockName      = */ "audio_core_lpm_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPM_CORE_CLK
  },
  {
    /* .szClockName      = */ "audio_core_peripheral_smmu_client_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CLK
  },
  {
    /* .szClockName      = */ "audio_core_sysnoc_mport_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_SYSNOC_MPORT_CORE_CLK
  },
};


/*
 * HAL_clk_mLPASSCOREClkDomain
 *
 * CORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCOREClkDomainClks)/sizeof(HAL_clk_mCOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

