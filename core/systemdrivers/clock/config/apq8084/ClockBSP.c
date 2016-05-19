/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/config/apq8084/ClockBSP.c#1 $

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
    .nFreqHz    = 49152 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 2,
      .nL             = 51,
      .nM             = 1,
      .nN             = 5,
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
    .nFreqHz    = 800000 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 41,
      .nM             = 2,
      .nN             = 3,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_NOMINAL,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },

  /* last entry */
  { 0 }
};


/*
 *  ClockSourcesToInit
 *
 *  Array of sources and settings to initialize at runtime.
 */
const ClockSourceInitType ClockSourcesToInit[] =
{
   { HAL_CLK_SOURCE_LPAPLL1, 800000 * 1000 },
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
       .nL             = 51,
       .nM             = 6554,
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
  {  19200000,     { HAL_CLK_SOURCE_NULL,     2,    0,      0,     0 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};

/*
 * QUP SPI clock configurations.
 */
const ClockMuxConfigType  QUPSPIClockConfig[] =
{
  {    960000,     { HAL_CLK_SOURCE_XO,    20,  1,   2,   2 }, CLOCK_VREG_LEVEL_LOW},
  {   4800000,     { HAL_CLK_SOURCE_XO,     8,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW},
  {   9600000,     { HAL_CLK_SOURCE_XO,     4,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW },
  {  15000000,     { HAL_CLK_SOURCE_GPLL0, 20,  1,   4,   4 }, CLOCK_VREG_LEVEL_LOW },
  {  19200000,     { HAL_CLK_SOURCE_XO,     2,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW },
  {  25000000,     { HAL_CLK_SOURCE_GPLL0, 24,  1,   2,   2 }, CLOCK_VREG_LEVEL_LOW },
  {  50000000,     { HAL_CLK_SOURCE_GPLL0, 24,  0,   0,   0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * UART Configs.
 */
const ClockMuxConfigType UARTClockConfig[] =
{
  {       3686400, { HAL_CLK_SOURCE_GPLL0,  2,     96,  15625,  15625 }, CLOCK_VREG_LEVEL_LOW     },
  {       7372800, { HAL_CLK_SOURCE_GPLL0,  2,    192,  15625,  15625 }, CLOCK_VREG_LEVEL_LOW     },
  {      14745600, { HAL_CLK_SOURCE_GPLL0,  2,    384,  15625,  15625 }, CLOCK_VREG_LEVEL_LOW     },
  {  16000 * 1000, { HAL_CLK_SOURCE_GPLL0, 10,      2,     15,     15 }, CLOCK_VREG_LEVEL_LOW     },
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,     2,      0,      0,      0 }, CLOCK_VREG_LEVEL_LOW     },
  {  24000 * 1000, { HAL_CLK_SOURCE_GPLL0, 10,      1,      5,      5 }, CLOCK_VREG_LEVEL_LOW     },
  {  32000 * 1000, { HAL_CLK_SOURCE_GPLL0,  2,      4,     75,     75 }, CLOCK_VREG_LEVEL_LOW     },
  {  40000 * 1000, { HAL_CLK_SOURCE_GPLL0, 30,      0,      0,      0 }, CLOCK_VREG_LEVEL_LOW     },
  {  46400 * 1000, { HAL_CLK_SOURCE_GPLL0,  2,     29,    375,    375 }, CLOCK_VREG_LEVEL_LOW     },
  {  48000 * 1000, { HAL_CLK_SOURCE_GPLL0, 25,      0,      0,      0 }, CLOCK_VREG_LEVEL_LOW     },
  {  51200 * 1000, { HAL_CLK_SOURCE_GPLL0,  2,     32,    375,    375 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  56000 * 1000, { HAL_CLK_SOURCE_GPLL0,  2,      7,     75,     75 }, CLOCK_VREG_LEVEL_NOMINAL },
  {      58982400, { HAL_CLK_SOURCE_GPLL0,  2,   1536,  15625,  15625 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  60000 * 1000, { HAL_CLK_SOURCE_GPLL0, 20,      0,      0,      0 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  63160 * 1000, { HAL_CLK_SOURCE_GPLL0, 19,      0,      0,      0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * LPASS AHB clock configurations.
 */
const ClockMuxConfigType  AHBClockConfig[] =
{
  {   3200 * 1000, { HAL_CLK_SOURCE_XO,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {   6400 * 1000, { HAL_CLK_SOURCE_XO,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {   9600 * 1000, { HAL_CLK_SOURCE_XO,       4, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 10, 1, 4, 4 }, CLOCK_VREG_LEVEL_LOW },
  {  30720 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 32, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  40960 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 24, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  61440 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  70217 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 14, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  81920 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  98304 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 10, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 122880 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 140434 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  7, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFOSRClockConfig[] =
{
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 60, 60 }, CLOCK_VREG_LEVEL_LOW},
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 40, 40 }, CLOCK_VREG_LEVEL_LOW},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 30, 30 }, CLOCK_VREG_LEVEL_LOW},
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 20, 20 }, CLOCK_VREG_LEVEL_LOW},
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 15, 15 }, CLOCK_VREG_LEVEL_LOW},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 10, 10 }, CLOCK_VREG_LEVEL_LOW},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  30, 1,  8,  8 }, CLOCK_VREG_LEVEL_LOW},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  20, 1,  8,  8 }, CLOCK_VREG_LEVEL_LOW},
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  30, 1,  4,  4 }, CLOCK_VREG_LEVEL_LOW},
  {  12288 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  20, 1,  4,  4 }, CLOCK_VREG_LEVEL_LOW},
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFPCMClockConfig[] =
{
  {    128 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1, 240, 240 }, CLOCK_VREG_LEVEL_LOW},
  {    512 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  60,  60 }, CLOCK_VREG_LEVEL_LOW},
  {    768 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  40,  40 }, CLOCK_VREG_LEVEL_LOW},
  {   1024 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  30,  30 }, CLOCK_VREG_LEVEL_LOW},
  {   1536 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  20,  20 }, CLOCK_VREG_LEVEL_LOW},
  {   2048 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  15,  15 }, CLOCK_VREG_LEVEL_LOW},
  {   3072 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  32, 1,  10,  10 }, CLOCK_VREG_LEVEL_LOW},
  {   4096 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  30, 1,   8,   8 }, CLOCK_VREG_LEVEL_LOW},
  {   6144 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  20, 1,   8,   8 }, CLOCK_VREG_LEVEL_LOW},
  {   8192 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  30, 1,   4,   4 }, CLOCK_VREG_LEVEL_LOW},
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
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 20, 1, 2, 2 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * ATIME cloock frequency.
 */
const ClockMuxConfigType ATIMEClockConfig[] =
{
  {  28224 * 1000, { HAL_CLK_SOURCE_LPAPLL0,   2, 1,  32,  32 }, CLOCK_VREG_LEVEL_LOW},
  { 0 }
};


/*
 * Resampler clock configurations.
 */
const ClockMuxConfigType ResamplerClockConfig[] =
{
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  61440 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  {  81920 * 1000, { HAL_CLK_SOURCE_LPAPLL0, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 122880 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 140434 * 1000, { HAL_CLK_SOURCE_LPAPLL0,  7, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
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
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"core_smmu_cfg_clk",               CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"q6_smmu_cfg_clk",                 CLOCK_FLAG_SUPPRESSIBLE },
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


/*
 * Initial CX voltage level.
 */
const ClockVRegLevelType CXVRegInitLevelConfig[] =
{
  CLOCK_VREG_LEVEL_LOW
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
  CLOCK_CPU_CONFIG_49P152_MHZ_PLL8,
  CLOCK_CPU_CONFIG_61P440_MHZ_PLL8,
  CLOCK_CPU_CONFIG_81P920_MHZ_PLL8,
  CLOCK_CPU_CONFIG_122P880_MHZ_PLL8,
  CLOCK_CPU_CONFIG_163P840_MHZ_PLL8,
  CLOCK_CPU_CONFIG_196P608_MHZ_PLL8,
  CLOCK_CPU_CONFIG_245P760_MHZ_PLL8,
  CLOCK_CPU_CONFIG_491P520_MHZ_PLL8,
  CLOCK_CPU_CONFIG_800P000_MHZ_PLL9,

  CLOCK_CPU_CONFIG_TOTAL
};


/*=========================================================================
      Data Declarations
==========================================================================*/


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
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
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
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   49152 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 20, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   61440 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 16, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   81920 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 12, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   122880 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 8, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   163840 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 6, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   196608 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 5, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   245760 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   491520 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL0, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL0[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_NOMINAL_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
    /* .Mux               */ {
    /* .nFreq             */   800000 * 1000,
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

  CLOCK_CPU_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of generic CPU performance levels.
 */
static const uint32 QDSP6PerfList[] =
{
    CLOCK_CPU_CONFIG_19P2_MHZ_XO,
    CLOCK_CPU_CONFIG_49P152_MHZ_PLL8,
    CLOCK_CPU_CONFIG_61P440_MHZ_PLL8,
    CLOCK_CPU_CONFIG_81P920_MHZ_PLL8,
    CLOCK_CPU_CONFIG_122P880_MHZ_PLL8,
    CLOCK_CPU_CONFIG_163P840_MHZ_PLL8,
    CLOCK_CPU_CONFIG_196P608_MHZ_PLL8,
    CLOCK_CPU_CONFIG_245P760_MHZ_PLL8,
    CLOCK_CPU_CONFIG_491P520_MHZ_PLL8,
    CLOCK_CPU_CONFIG_800P000_MHZ_PLL9,
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
    CLOCK_CPU_PERF_LEVEL_9,

    /*
     * Init performance level
     */
    CLOCK_CPU_PERF_LEVEL_7,

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
   * Intermedate CPU configuration, where applicable.
   */
  NULL,

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



