/*
==============================================================================

FILE:         HALclkCDC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CDC clocks.

   List of clock domains:
   -HAL_clk_mLPASSCDCClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass/src/lcc/HALclkCDC.c#1 $

when          who     what, where, why
----------    ---     --------------------------------------------------------
01/30/2013            Auto-generated.

==============================================================================
            Copyright (c) 2013 Qualcomm Technologies Incorporated.
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

#define HAL_CLK_CONFIG_LPASS_CORE_CLK_OFF_BMSK 0x80000000

/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_DigCodecConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
);

/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

/*
 * HAL_clk_mDigCodecConfigClockControl
 *
 * Customize the ConfigClock for Digital Codec.
 */
HAL_clk_ClockControlType HAL_clk_mDigCodecConfigClockControl =
{
  /* .Enable           = */ HAL_clk_GenericEnable,
  /* .Disable          = */ HAL_clk_GenericDisable,
  /* .IsEnabled        = */ HAL_clk_GenericIsEnabled,
  /* .IsOn             = */ HAL_clk_GenericIsOn,
  /* .Reset            = */ HAL_clk_GenericReset,
  /* .IsReset          = */ HAL_clk_GenericIsReset,
  /* .Config           = */ HAL_clk_DigCodecConfig,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ HAL_clk_GenericConfigDivider,
  /* .DetectDivider    = */ HAL_clk_GenericDetectDivider,
  /* .ConfigFootswitch = */ HAL_clk_GenericConfigFootswitch,
};

                                    
/*                           
 *  HAL_clk_mCDCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCDCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "digcodec_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_DIGCODEC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mDigCodecConfigClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_DIGCODEC_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_MSM8x10
  },
};


/*
 * HAL_clk_mLPASSCDCClkDomain
 *
 * CDC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCDCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_DIGCODEC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCDCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCDCClkDomainClks)/sizeof(HAL_clk_mCDCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};



/*
 * Digital codec clock config source selection API.
 */
void HAL_clk_DigCodecConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
)
{
  uint32 nAddr = 0;

  if((eConfig < HAL_CLK_CONFIG_DIG_CODEC_SRC_SEL_DIG_CODEC) ||
     (eConfig > HAL_CLK_CONFIG_DEG_CODEC_SRC_SEL_SEC_MI2S))
  {
    return;
  }

  if(NULL != pmClockDesc)
  {
    nAddr = pmClockDesc->mRegisters.nBranchAddr;

    if(nAddr != 0)
    {
      switch(eConfig)
      {
         case HAL_CLK_CONFIG_DIG_CODEC_SRC_SEL_DIG_CODEC:
           outpdw(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR, 0x0);
           break;
     
         case HAL_CLK_CONFIG_DEG_CODEC_SRC_SEL_PRI_MI2S:
           outpdw(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR, 0x1);
           break;
     
         case HAL_CLK_CONFIG_DEG_CODEC_SRC_SEL_SEC_MI2S:
           outpdw(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR, 0x2);
           break;
     
         default:
           break;
      }
    }
  }
} /* HAL_clk_DigCodecConfig */

