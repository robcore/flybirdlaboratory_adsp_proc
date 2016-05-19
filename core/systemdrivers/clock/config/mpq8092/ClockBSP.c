/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/config/mpq8092/ClockBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/19/13   dcf     Created. 

==============================================================================
            Copyright (c) 2013 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "ClockLPASSCPU.h"

/*=========================================================================
      Data Declarations
==========================================================================*/

/*
 *  SourceFreqConfig_XO
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_XO[] =
{
  {
    .nFreqHz    = 19200 * 1000,
    .HALConfig  = { HAL_CLK_SOURCE_NULL },
    .eVRegLevel = CLOCK_VREG_LEVEL_HIGH,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL0[] =
{
  {
    .nFreqHz    = 600000 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO1,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 31,
      .nM             = 1,
      .nN             = 4,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_HIGH,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL0[] =
{
  {
    .nFreqHz    = 903168 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 47,
      .nM             = 1,
      .nN             = 25,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_HIGH,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_LPAPLL1 (Q6PLL)
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL1[] =
{
  {
    .nFreqHz    = 663552 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 34,
      .nM             = 14,
      .nN             = 25,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_HIGH,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
};


/*
 *  ClockSourcesToInit
 *
 *  Array of sources and settings to initialize at runtime.
 */
const ClockSourceInitType ClockSourcesToInit[] =
{
   { HAL_CLK_SOURCE_LPAPLL1, 663552 * 1000 },
   { HAL_CLK_SOURCE_NULL,    NULL}
};



/*
 * Clock source configuration data.
 */
const ClockSourceConfigType SourceConfig[] =
{
  {
    SOURCE_NAME(XO),

    .nConfigMask            = 0,
    .pSourceFreqConfig      = SourceFreqConfig_XO,
  },
  {
    SOURCE_NAME(GPLL0),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_GPLL0,
  },
  {
    SOURCE_NAME(LPAPLL0),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_LPAPLL0,
  },
  {
    SOURCE_NAME(LPAPLL1),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_LPAPLL1,
  },

  /* last entry */
  { SOURCE_NAME(NULL) }
};



/* 
 * Supported pulled source mappings and their configurations.
 */
static ClockPulledSourceType Clock_PulledSourceConfig[] =
{
   {
     .eSource = CLOCK_SOURCE_PRIMARY,
     .HALConfig = 
     {
       .eSource        = HAL_CLK_SOURCE_LPAPLL0,
       .eVCO           = HAL_CLK_PLL_VCO3,
       .nPreDiv        = 1,
       .nPostDiv       = 2,
       .nL             = 47,
       .nM             = 1310,
       .nN             = 32768,
       .nVCOMultiplier = 0,
       .nAlpha         = 0,
       .nAlphaU        = 0,
     }
   },

    /*
     * Last entry.
     */
    { 0 }
};

/* =========================================================================
**    nFreqHz       { eSource, nDiv2x, nM, nN, n2D },      eVRegLevel         
** =========================================================================*/


/*
 * QUP I2C clock configuration.
 */
const ClockMuxConfigType  QUPI2CClockConfig[] =
{
  {  19200000,     { HAL_CLK_SOURCE_NULL,     2,    0,      0,     0 }, CLOCK_VREG_LEVEL_HIGH },
  { 0 }
};

/*
 * QUP SPI clock configurations.
 */
const ClockMuxConfigType  QUPSPIClockConfig[] =
{
  {    960000,     { HAL_CLK_SOURCE_XO,    20,  1,   2,   2 }, CLOCK_VREG_LEVEL_HIGH},
  {   4800000,     { HAL_CLK_SOURCE_XO,     8,  0,   0,   0 }, CLOCK_VREG_LEVEL_HIGH},
  {   9600000,     { HAL_CLK_SOURCE_XO,     4,  0,   0,   0 }, CLOCK_VREG_LEVEL_HIGH },
  {  15000000,     { HAL_CLK_SOURCE_GPLL0, 20,  1,   4,   4 }, CLOCK_VREG_LEVEL_HIGH },
  {  19200000,     { HAL_CLK_SOURCE_XO,     2,  0,   0,   0 }, CLOCK_VREG_LEVEL_HIGH },
  {  25000000,     { HAL_CLK_SOURCE_GPLL0, 24,  1,   2,   2 }, CLOCK_VREG_LEVEL_HIGH },
  {  50000000,     { HAL_CLK_SOURCE_GPLL0, 24,  0,   0,   0 }, CLOCK_VREG_LEVEL_HIGH },
  { 0 }
};


/*
 * LPASS AHB clock configurations.
 */
const ClockMuxConfigType  AHBClockConfig[] =
{
  {   3200 * 1000, { HAL_CLK_SOURCE_XO,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {   6400 * 1000, { HAL_CLK_SOURCE_XO,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {   9600 * 1000, { HAL_CLK_SOURCE_XO,       4, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {  28224 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 32, 1, 2, 2 }, CLOCK_VREG_LEVEL_HIGH },
  {  37632 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 24, 1, 2, 2 }, CLOCK_VREG_LEVEL_HIGH },
  {  56448 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 32, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {  69474 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 26, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  {  82106 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 22, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  { 100352 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 18, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  { 112896 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  { 129024 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 14, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  { 138949 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 13, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH },
  { 0 }
};


/*=========================================================================================*/
/*                   Audio Clocks on Primary Clock Source                                  */
/*=========================================================================================*/

/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFOSRClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 240, 240 }, CLOCK_VREG_LEVEL_HIGH},
  {    256 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 162, 162 }, CLOCK_VREG_LEVEL_HIGH},
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 108, 108 }, CLOCK_VREG_LEVEL_HIGH},
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1,  54,  54 }, CLOCK_VREG_LEVEL_HIGH},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  16, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   8, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  16, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   4, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   8, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   6, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {  12288 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   4, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFPCMClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 240, 240 }, CLOCK_VREG_LEVEL_HIGH},
  {    256 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 162, 162 }, CLOCK_VREG_LEVEL_HIGH},
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1, 108, 108 }, CLOCK_VREG_LEVEL_HIGH},
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1,  54,  54 }, CLOCK_VREG_LEVEL_HIGH},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  16, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  32, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   8, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL1,  16, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   4, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   8, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   2, 1,  81,  81 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};

const ClockMuxConfigType LPAIFSPDIFClockConfig[] =
{
  {  12288 * 1000, { HAL_CLK_SOURCE_LPAPLL1,   4, 1,  27,  27 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};


/*
 * Resampler clock configurations.
 */
const ClockMuxConfigType ResamplerClockConfig[] =
{
  {   3200 * 1000, { HAL_CLK_SOURCE_XO,      12, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {   6400 * 1000, { HAL_CLK_SOURCE_XO,       6, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {   9600 * 1000, { HAL_CLK_SOURCE_XO,       4, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {  28224 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 32, 1,  2,  2 }, CLOCK_VREG_LEVEL_HIGH },
  {  37632 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 24, 1,  2,  2 }, CLOCK_VREG_LEVEL_HIGH },
  {  56448 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 32, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {  64512 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 28, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  {  75264 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 24, 1,  2,  2 }, CLOCK_VREG_LEVEL_HIGH },
  { 100352 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 18, 1,  2,  2 }, CLOCK_VREG_LEVEL_HIGH },
  { 112896 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 16, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  { 129024 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 14, 0,  0,  0 }, CLOCK_VREG_LEVEL_HIGH },
  { 1389489 * 100, { HAL_CLK_SOURCE_LPAPLL0, 1,  2, 13, 13 }, CLOCK_VREG_LEVEL_HIGH },
  { 0 }
};


/*
 * Slimbus clock configurations. 
 *  
 * Note:  Slimbus requires nominal voltage, but is making requests
 *        directly to the PMIC driver so set the vote here for low. 
 */
const ClockMuxConfigType SlimbusClockConfig[] =
{
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL1, 1, 1, 27, 27 }, CLOCK_VREG_LEVEL_HIGH },
  { 0 }
};



/*=========================================================================================*/
/*                   Audio Clocks on Secondary (Pulled) Clock Source                       */
/*=========================================================================================*/

/*
 * Low Power Audio Interface (LPAIF) clocks
 */

static const ClockMuxConfigType LPAIFOSRClockConfigPulled[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 240, 240 }, CLOCK_VREG_LEVEL_HIGH},
  {    256 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  16, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {    384 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   8, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  16, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   4, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   8, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   4, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 2, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {  112896 * 100, { HAL_CLK_SOURCE_LPAPLL0,   2, 1,  80,  80 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};


static const ClockMuxConfigType LPAIFPCMClockConfigPulled[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 240, 240 }, CLOCK_VREG_LEVEL_HIGH},
  {    256 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  16, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {    3528 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 160, 160 }, CLOCK_VREG_LEVEL_HIGH}, /* New in Pulling */
  {    384 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   8, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {    7056 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  80,  80 }, CLOCK_VREG_LEVEL_HIGH}, /* New in Pulling */
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  16, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   4, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   14112 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  40,  40 }, CLOCK_VREG_LEVEL_HIGH}, /* New in Pulling */
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   8, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   28224 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  20,  20 }, CLOCK_VREG_LEVEL_HIGH}, /* New in Pulling */
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   4, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 2, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   56448 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  10,  10 }, CLOCK_VREG_LEVEL_HIGH}, /* New in Pulling */
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};


const ClockMuxConfigType LPAIFSPDIFClockConfigPulled[] =
{
  {   28224 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  20,  20 }, CLOCK_VREG_LEVEL_HIGH},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   4, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 2, 441, 441 }, CLOCK_VREG_LEVEL_HIGH},
  {   56448 * 100, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  10,  10 }, CLOCK_VREG_LEVEL_HIGH},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1, 147, 147 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};


const ClockMuxConfigType ATIMEClockConfig[] =
{
  {  28224 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1,  32,  32 }, CLOCK_VREG_LEVEL_HIGH},
  { 0 }
};

/* 
 * Array of Clock source config mappings - Non-pulled to pulled.
 */
ClockSourceSelectConfigType ClockSourceSelects[] =
{
   {
      (ClockMuxConfigType*)LPAIFOSRClockConfig,
      (ClockMuxConfigType*)LPAIFOSRClockConfigPulled,
   },
   {
      (ClockMuxConfigType*)LPAIFPCMClockConfig,
      (ClockMuxConfigType*)LPAIFPCMClockConfigPulled,
   },
   {
      (ClockMuxConfigType*)LPAIFSPDIFClockConfig,
      (ClockMuxConfigType*)LPAIFSPDIFClockConfigPulled,
   },
   { 0 }
};

/* 
 * Main data structure for clock source selections.
 */
ClockSourceSelectMapType ClockSourceMaps =
{
   {
      CLOCK_SOURCE_PRIMARY,
      HAL_CLK_SOURCE_LPAPLL1,
   },
   {
      CLOCK_SOURCE_SECONDARY,
      HAL_CLK_SOURCE_LPAPLL0,
   },
   {
      CLOCK_SOURCE_NONE,
      HAL_CLK_SOURCE_NULL
   },

   ClockSourceSelects
};


/*
 * Clock Log Default Configuration.
 *
 * NOTE: A .nGlobalLogFlags value of 0x12 will log only clock frequency
 *       changes and source state changes by default.
 */
const ClockLogType ClockLogDefaultConfig[] =
{
  {
    /* .nLogSize        = */ 4096,
    /* .nGlobalLogFlags = */ 0x12
  }
};


/*
 * Clock Flag Init Config.
 */
const ClockFlagInitType ClockFlagInitConfig[] =
{
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_q6core",                    CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_timeout_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_timeout_clk",          CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_ixfabric_clk",         CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"q6ss_ahbm_clk",                   CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_resampler_lfabif_clk", CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_dml_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpaif_dma_clk",        CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpaif_csr_clk",        CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_slimbus_lfabif_clk",   CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_midi_lfabif_clk",      CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_avsync_csr_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpm_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_smem_clk",          CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_lcc_csr_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_efabric_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_csr_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_security_clk",         CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_security_clk",      CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_br_clk",            CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_sysnoc_mport_clk",  CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"gcc_lpass_sys_noc_mport_clk",     CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_aon_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_NONE,         (void*)0,                                 0                       } 
};

/*
 * Resources that need to be published to domains outside GuestOS.
 */
static const char *ClockPubResource[] =
{
   CLOCK_NPA_RESOURCE_QDSS
};

ClockNPAResourcePubType ClockResourcePub = 
{
   SENSOR_PD,
   ClockPubResource,
   1
};





/*=========================================================================
      Macros
==========================================================================*/

/*
 * Q6 PMIC (LDO o/p) Voltage (in uV)
 */
#define CLOCK_CPU_VREG_LEVEL_LOW_UV      812500
#define CLOCK_CPU_VREG_LEVEL_NOMINAL_UV  900000
#define CLOCK_CPU_VREG_LEVEL_HIGH_UV    1050000


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of CPU configurations.
 */
enum
{
  CLOCK_CPU_CONFIG_9P6_MHZ_XO,
  CLOCK_CPU_CONFIG_19P2_MHZ_XO,
  CLOCK_CPU_CONFIG_56P448_MHZ_PLL8,
  CLOCK_CPU_CONFIG_75P264_MHZ_PLL8,
  CLOCK_CPU_CONFIG_90P317_MHZ_PLL8,
  CLOCK_CPU_CONFIG_112P896_MHZ_PLL8,
  CLOCK_CPU_CONFIG_150P528_MHZ_PLL8,
  CLOCK_CPU_CONFIG_180P634_MHZ_PLL8,
  CLOCK_CPU_CONFIG_225P792_MHZ_PLL8,
  CLOCK_CPU_CONFIG_301P056_MHZ_PLL9,
  CLOCK_CPU_CONFIG_451P584_MHZ_PLL8,
  CLOCK_CPU_CONFIG_663P552_MHZ_PLL9,

  CLOCK_CPU_CONFIG_TOTAL
};


/*=========================================================================
      Data Declarations
==========================================================================*/
/*
 * Mux configuration for different CPU frequencies. 
 */
static ClockCPUConfigType Clock_QDSP6Config [] =
{
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   9600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_XO, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_XO[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   19200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_XO, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_XO[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   56448 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 32, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   75264 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 24, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   90317 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 20, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   112896 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 16, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   150528 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 12, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   180634 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 10, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   225792 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 8, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   301056 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 6, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   451584 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   663552 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  }
};


/*
 * Enumeration of CPU performance levels.
 */
enum
{
  CLOCK_CPU_PERF_LEVEL_0,
  CLOCK_CPU_PERF_LEVEL_1,
  CLOCK_CPU_PERF_LEVEL_2,
  CLOCK_CPU_PERF_LEVEL_3,
  CLOCK_CPU_PERF_LEVEL_4,
  CLOCK_CPU_PERF_LEVEL_5,
  CLOCK_CPU_PERF_LEVEL_6,
  CLOCK_CPU_PERF_LEVEL_7,
  CLOCK_CPU_PERF_LEVEL_8,
  CLOCK_CPU_PERF_LEVEL_9,
  CLOCK_CPU_PERF_LEVEL_10,
  CLOCK_CPU_PERF_LEVEL_11,

  CLOCK_CPU_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of generic CPU performance levels.
 */
static const uint32 QDSP6PerfList[] =
{
  CLOCK_CPU_CONFIG_19P2_MHZ_XO,
  CLOCK_CPU_CONFIG_56P448_MHZ_PLL8,
  CLOCK_CPU_CONFIG_75P264_MHZ_PLL8,
  CLOCK_CPU_CONFIG_90P317_MHZ_PLL8,
  CLOCK_CPU_CONFIG_112P896_MHZ_PLL8,
  CLOCK_CPU_CONFIG_150P528_MHZ_PLL8,
  CLOCK_CPU_CONFIG_180P634_MHZ_PLL8,
  CLOCK_CPU_CONFIG_225P792_MHZ_PLL8,
  CLOCK_CPU_CONFIG_301P056_MHZ_PLL9,
  CLOCK_CPU_CONFIG_451P584_MHZ_PLL8,
  CLOCK_CPU_CONFIG_663P552_MHZ_PLL9
};


/*
 * Performance level configuration data for the Q6LPASS (CPU).
 */
static const ClockCPUPerfConfigType Clock_QDSP6LPASSPerfConfig[] =
{
  {
    /*
     * Define performance levels.
     */

    /*
     * min level
     */
    CLOCK_CPU_PERF_LEVEL_0,

    /*
     * max level
     */
    CLOCK_CPU_PERF_LEVEL_10,

    /*
     * Init performance level
     */
    CLOCK_CPU_PERF_LEVEL_8,

    /*
     * Total number of CPU configurations.
     */
    sizeof(Clock_QDSP6Config)/sizeof(ClockCPUConfigType),

    /*
     * Pointer to the performance levels.
     */
    (uint32*)QDSP6PerfList
  }
};


/*
 * Main Image data structure.
 */
const ClockImageConfigType Clock_ImageConfig =
{
  /*
   * Pointer to the CPU frequency plan settings.
   */
   (ClockCPUConfigType*)Clock_QDSP6Config,

  /*
   * Pointer to the performance level configurations.
   */
   (ClockCPUPerfConfigType*)Clock_QDSP6LPASSPerfConfig,

  /*
   * Global enable for the eLDO feature.
   */
   FALSE,

  /*
   * Fusion variant.
   */
   FALSE,

   (ClockPulledSourceType*)Clock_PulledSourceConfig,

};


/*
 * OCMEM is used on this chipset.
 */
const ClockNPARemoteNodeSupportType ClockNPARemoteNodeSupport = 
{
   /* bOCMEM  = */ TRUE,
};


/*
 * Clock LDO Configuration Data.
 */
const ClockLDODataType ClockLDODataConfig[] =
{
  {
    /* nLDOCFG0 */           0x01004000,
    /* nLDOCFG1 */           0x00000050,
    /* nLDOCFG2 */           0x00000048,
    /* nRetentionVoltage */  500 * 1000,
    /* nOperatingVoltage */  775 * 1000
  }
};


const HAL_clk_HWIOBaseType ClockLDOHWIOBases = 
{
   /* nPhysAddress */ 0xfe000000,
   /* nSize        */ 0x00300000
};


const HAL_clk_HWIOBaseType ClockSECHWIOBases = 
{
   /* nPhysAddress */ 0xfc4b8000,
   /* nSize        */ 0x00008000
};


