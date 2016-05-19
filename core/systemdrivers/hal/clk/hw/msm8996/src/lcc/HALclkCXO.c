/*
==============================================================================

FILE:         HALclkCXO.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CXO clocks.

   List of clock domains:
     - HAL_clk_mLPASSQOSXOClkDomain
     - HAL_clk_mLPASSQ6SMMUGDSCXOClkDomain
     - HAL_clk_mLPASSGDSCXOClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkCXO.c#1 $

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
 *  HAL_clk_mQOSXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQOSXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_qos_xo_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CLK
  },
};


/*
 * HAL_clk_mLPASSQOSXOClkDomain
 *
 * QOSXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQOSXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQOSXOClkDomainClks)/sizeof(HAL_clk_mQOSXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQ6SMMUGDSCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQ6SMMUGDSCXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_q6_smmu_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CLK
  },
};


/*
 * HAL_clk_mLPASSQ6SMMUGDSCXOClkDomain
 *
 * Q6SMMUGDSCXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SMMUGDSCXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQ6SMMUGDSCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQ6SMMUGDSCXOClkDomainClks)/sizeof(HAL_clk_mQ6SMMUGDSCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mGDSCXOClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGDSCXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_GDSC_XO_CLK
  },
  {
    /* .szClockName      = */ "audio_core_avsync_stc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_STC_CBCR ), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_STC_XO_CLK
  },
  {
    /* .szClockName      = */ "q6ss_q6_camss_dsp_streaming_0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR ), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_STC_XO_CLK
  },
  {
    /* .szClockName      = */ "q6ss_q6_camss_dsp_streaming_1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR ), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_AVSYNC_STC_XO_CLK
  },
};


/*
 * HAL_clk_mLPASSGDSCXOClkDomain
 *
 * GDSCXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSGDSCXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mGDSCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGDSCXOClkDomainClks)/sizeof(HAL_clk_mGDSCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

