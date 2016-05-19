/*
==============================================================================

FILE:         HALclkQOSFIXEDMONITOR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QOSFIXEDMONITOR clocks.

   List of clock domains:
     - HAL_clk_mLPASSCOREQOSFIXEDLATCOUNTERSRCClkDomain
     - HAL_clk_mLPASSQOSFIXEDLATCOUNTERSRCClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/lcc/HALclkQOSFIXEDMONITOR.c#1 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSAudioClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSAudioClockDomainControlRO;

/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCOREQOSFIXEDLATCOUNTERSRCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCOREQOSFIXEDLATCOUNTERSRCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_qos_dmonitor_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CLK
  },
};


/*
 * HAL_clk_mLPASSCOREQOSFIXEDLATCOUNTERSRCClkDomain
 *
 * COREQOSFIXEDLATCOUNTERSRC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREQOSFIXEDLATCOUNTERSRCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCOREQOSFIXEDLATCOUNTERSRCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCOREQOSFIXEDLATCOUNTERSRCClkDomainClks)/sizeof(HAL_clk_mCOREQOSFIXEDLATCOUNTERSRCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_qos_danger_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CLK
  },
  {
    /* .szClockName      = */ "audio_wrapper_qos_dmonitor_fixed_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CLK
  },
};


/*
 * HAL_clk_mLPASSQOSFIXEDLATCOUNTERSRCClkDomain
 *
 * QOSFIXEDLATCOUNTERSRC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSFIXEDLATCOUNTERSRCClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks)/sizeof(HAL_clk_mQOSFIXEDLATCOUNTERSRCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSAudioClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

