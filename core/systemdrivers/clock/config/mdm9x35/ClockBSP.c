/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/config/mdm9x35/ClockBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/19/11   dcf     Created. 

==============================================================================
            Copyright (c) 2012 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "ClockLPASSCPU.h"
#include "DDITlmm.h"

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
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW,
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
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 31,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0x40,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW,
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
    .nFreqHz    = 614400 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 32,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_LPAPLL1
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL1[] =
{
  {
    .nFreqHz    = 403200 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 2,
      .nL             = 42,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  {
    .nFreqHz    = 537600 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 28,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL2[] =
{
  {
    .nFreqHz    = 614400 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 32,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW, /* This PLL is powered by VDD_CX */
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 * Clock source frequency configuration data for the Audio Reference Clock functionality.
 * Input source will be 9.6 MHz.
 */
static ClockSourceFreqConfigType SourceFreqConfigARC[] =
{
  {
    .nFreqHz    = 614400 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 64,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW, /* This PLL is powered by VDD_CX */
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 * Clock source configuration data for the Audio Reference Clock functionality.
 */
const ClockSourceConfigType SourceConfigARC[] =
{
  {
    SOURCE_NAME(LPAPLL2),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE | CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfigARC,
  },
    /* last entry */
  { SOURCE_NAME(NULL) }
};

/*
 *  ClockSourcesToInit
 *
 *  Array of sources and settings to initialize at runtime.
 */
const ClockSourceInitType ClockSourcesToInit[] =
{
   { HAL_CLK_SOURCE_LPAPLL0, 614400 * 1000 },
   { HAL_CLK_SOURCE_LPAPLL1, 537600 * 1000 },
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

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE | CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_LPAPLL0,
  },
  {
    SOURCE_NAME(LPAPLL1),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE | CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_LPAPLL1,
  },
  {
    SOURCE_NAME(LPAPLL2),

    .nConfigMask            = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE | CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE | CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
    .pSourceFreqConfig      = SourceFreqConfig_LPAPLL2,
  },

  /* last entry */
  { SOURCE_NAME(NULL) }

};


/* =========================================================================
**    nFreqHz       { eSource, nDiv2x, nM, nN, n2D },      eVRegLevel         
** =========================================================================*/


/*
 * QUP I2C clock configuration.
 */
const ClockMuxConfigType  QUPI2CClockConfig[] =
{
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,     2,    0,      0,     0 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * LPASS AHB clock configurations.
 */
const ClockMuxConfigType  AHBClockConfig[] =
{
  {   3200 * 1000, { HAL_CLK_SOURCE_XO,      12, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {   6400 * 1000, { HAL_CLK_SOURCE_XO,       6, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {   9600 * 1000, { HAL_CLK_SOURCE_XO,       4, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  2, 3, 25, 25 }, CLOCK_VREG_LEVEL_LOW },
  {  34133 * 1000, { HAL_CLK_SOURCE_LPAPLL2, 12, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  40960 * 1000, { HAL_CLK_SOURCE_LPAPLL2, 10, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  51200 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  8, 0,  0,  0 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  68267 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  6, 0 , 0,  0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 136533 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  3, 0,  0,  0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFOSRClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1, 384, 384 }, CLOCK_VREG_LEVEL_LOW },
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  48,  48 }, CLOCK_VREG_LEVEL_LOW },
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  32,  32 }, CLOCK_VREG_LEVEL_LOW },
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  24,  24 }, CLOCK_VREG_LEVEL_LOW },
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  16,  16 }, CLOCK_VREG_LEVEL_LOW },
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  12,  12 }, CLOCK_VREG_LEVEL_LOW },
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   8,   8 }, CLOCK_VREG_LEVEL_LOW },
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   6,   6 }, CLOCK_VREG_LEVEL_LOW },
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   4,   4 }, CLOCK_VREG_LEVEL_LOW },
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   3,   3 }, CLOCK_VREG_LEVEL_LOW },
  {  12288 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   2,   2 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};

/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFPCMOEClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1, 384, 384 }, CLOCK_VREG_LEVEL_LOW },
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  48,  48 }, CLOCK_VREG_LEVEL_LOW },
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  32,  32 }, CLOCK_VREG_LEVEL_LOW },
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  24,  24 }, CLOCK_VREG_LEVEL_LOW },
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  16,  16 }, CLOCK_VREG_LEVEL_LOW },
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  12,  12 }, CLOCK_VREG_LEVEL_LOW },
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   8,   8 }, CLOCK_VREG_LEVEL_LOW },
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   6,   6 }, CLOCK_VREG_LEVEL_LOW },
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   4,   4 }, CLOCK_VREG_LEVEL_LOW },
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   3,   3 }, CLOCK_VREG_LEVEL_LOW },
  {  12288 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   2,   2 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks 
 *  
 * Note:  LPAAUDIO PRIUS PLL output from AUX1 has a CDIV-5 on the PLL output which sources 
 *        the RCG with a 122.88 MHz frequency, requiring a different RCG divider.
 */
const ClockMuxConfigType LPAIFPCMClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1, 384, 384 }, CLOCK_VREG_LEVEL_LOW },
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  48,  48 }, CLOCK_VREG_LEVEL_LOW },
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  32,  32 }, CLOCK_VREG_LEVEL_LOW },
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  24,  24 }, CLOCK_VREG_LEVEL_LOW },
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  16,  16 }, CLOCK_VREG_LEVEL_LOW },
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,  12,  12 }, CLOCK_VREG_LEVEL_LOW },
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   8,   8 }, CLOCK_VREG_LEVEL_LOW },
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   6,   6 }, CLOCK_VREG_LEVEL_LOW },
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   4,   4 }, CLOCK_VREG_LEVEL_LOW },
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  10, 1,   3,   3 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * Slimbus clock configurations. 
 *  
 * Note:  Slimbus requires nominal voltage, but is making requests
 *        directly to the PMIC driver so set the vote here for low.
 *  
 * Note:  There is a CDIV-5 on the output of the LPAAUDIO PRIUS PLL 
 *        AUX2 selection which results in a 122.88 MHz frequency to
 *        supply the Slimbus core clock.  Further division reflects
 *        the proper frequency.
 */
const ClockMuxConfigType SlimbusClockConfig[] =
{
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL2, 1, 1, 5, 5 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * Clock Log Default Configuration.
 *
 * NOTE: An .nGlobalLogFlags value of 0x12 will log only clock frequency
 *       changes and source state changes by default.
 */
const ClockLogType ClockLogDefaultConfig[] =
{
  {
    /* .nLogSize        = */ 4096,
    /* .nGlobalLogFlags = */ 0x12
  }
};


const uint32 ClockARCGPIOs [] = 
{
   DAL_GPIO_CFG(71, 2, DAL_GPIO_INPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA),
   DAL_GPIO_CFG_OUT(16, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA, DAL_GPIO_HIGH_VALUE),
   0xFFFFFFFF
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
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_dml_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpaif_dma_clk",        CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpaif_csr_clk",        CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_slimbus_lfabif_clk",   CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_avsync_csr_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpm_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_smem_clk",          CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_lcc_csr_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_efabric_clk",       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_csr_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_security_clk",         CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_security_clk",      CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_br_clk",            CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"gcc_lpass_sys_noc_mport_clk",     CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_sysnoc_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_aon_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_NONE,         (void*)0,                                 0                       } 
};


/*
 * Initial CX voltage level.
 */
const ClockVRegLevelType CXVRegInitLevelConfig[] =
{
  CLOCK_VREG_LEVEL_LOW
};






/*=========================================================================
      Type Definitions and Macros
==========================================================================*/

/*
 * Q6 Voltage levels in uv.
 */
#define CLOCK_CPU_VREG_LEVEL_LOW_UV      812500
#define CLOCK_CPU_VREG_LEVEL_NOMINAL_UV  900000
#define CLOCK_CPU_VREG_LEVEL_HIGH_UV    1050000


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of QDSP6 configurations.
 */
enum
{
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_0,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_1,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_2,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_3,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_4,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_5,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_6,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_7,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_8,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_9,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_10,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_11,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_12,

  CLOCK_CPU_CONFIG_TOTAL
};



/*=========================================================================
      Data Declarations
==========================================================================*/


/*
 * Mux configuration for different CPU frequencies. 
 *  
 * Note:  LPAPLL2_AUX2 has a CDIV=2 coming out of the PLL output so the source 
 *        source coming into the RCG is 614.4/2 = 307.2 MHz.
 */
static ClockCPUConfigType Clock_QDSP6Config [] =
{
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   9600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_XO, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_XO[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   19200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_XO, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_XO[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   38400 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 16, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   51200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 12, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   61440 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 10, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   76800 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 8, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   102400 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 6, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   122880 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 5, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   153600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   268800 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[1]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   307200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_NOMINAL_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   403600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_NOMINAL_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   537600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[1]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_NOMINAL_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  }
};

/*
 * Enumeration of CPU performance levels.  More performance 
 * levels exist here than are actually implemented.
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
  CLOCK_CPU_PERF_LEVEL_12,

  CLOCK_CPU_PERF_LEVEL_TOTAL
};

/*
 * Enumeration of generic CPU performance levels.  More performance 
 * levels exist here than are actually implemented.
 */
static const uint32 QDSP6PerfList[] =
{
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_1,  /* Start at XO */
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_2,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_3,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_4,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_5,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_6,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_7,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_8,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_9,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_10,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_11,
  CLOCK_QDSP6_CONFIG_TABLE_INDEX_12,
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
    CLOCK_CPU_PERF_LEVEL_11,
   
    /*
     * Init performance level
     */
    CLOCK_CPU_PERF_LEVEL_8,
   
    /*
     * Total number of CPU configurations.
     */
    sizeof(Clock_QDSP6Config)/sizeof(ClockCPUConfigType),
   
    /*
     * Pointer to an array of supported performance level indices.
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
    * Global enable flag for eLDO.
    */
   FALSE,

   /*
    * Intermediate CPU configuration (if necessary).
    */
   NULL,
   
   /*
    * Global flag for MDMs.
    */
   TRUE

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


/*
 * OCMEM is not used on this chipset.  Add additional flags to this as needed.
 */
const ClockNPARemoteNodeSupportType ClockNPARemoteNodeSupport = 
{
   /* bOCMEM  = */ FALSE,
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


const boolean ClockLDOVersion[] =
{
   1
};

