/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/config/msm8996/ClockBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/19/11   dcf     Created. 

==============================================================================
            Copyright (c) 2014 QUALCOMM Technologies Incorporated.
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
    .nFreqHz    = 326400 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 2,
      .nL             = 34,
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
    .nFreqHz    = 499200 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 2,
      .nL             = 52,
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
    .nFreqHz    = 748800 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 39,
      .nM             = 0,
      .nN             = 0,
      .nVCOMultiplier = 0,
      .nAlpha         = 0,
      .nAlphaU        = 0,
    },
    .eVRegLevel = CLOCK_VREG_LEVEL_NOMINAL,
    .HWVersion  = { {0, 0}, {0xFF, 0xFF} },
  },
  {
    .nFreqHz    = 902400 * 1000,
    .HALConfig  =
    {
      .eSource        = HAL_CLK_SOURCE_XO,
      .eVCO           = HAL_CLK_PLL_VCO3,
      .nPreDiv        = 1,
      .nPostDiv       = 1,
      .nL             = 47,
      .nM             = 0,
      .nN             = 0,
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
    .eVRegLevel = CLOCK_VREG_LEVEL_LOW, /* This PLL is powered by VDD_MX */
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
   { HAL_CLK_SOURCE_LPAPLL0, 614400 * 1000 },
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
 * BLSP1UART1APPS clock configurations
 */
const ClockMuxConfigType BLSP1UART1APPSClockConfig[] =
{
  {    3686400, { HAL_CLK_SOURCE_GPLL0,          2,      96,     15625,  15625   }, CLOCK_VREG_LEVEL_LOW },
  {    7372800, { HAL_CLK_SOURCE_GPLL0,          2,      192,    15625,  15625   }, CLOCK_VREG_LEVEL_LOW },
  {   14745600, { HAL_CLK_SOURCE_GPLL0,          2,      384,    15625,  15625   }, CLOCK_VREG_LEVEL_LOW },
  {   16000000, { HAL_CLK_SOURCE_GPLL0,          10,     2,      15,     15      }, CLOCK_VREG_LEVEL_LOW },
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW },
  {   24000000, { HAL_CLK_SOURCE_GPLL0,          10,     1,      5,      5       }, CLOCK_VREG_LEVEL_LOW },
  {   32000000, { HAL_CLK_SOURCE_GPLL0,          2,      4,      75,     75      }, CLOCK_VREG_LEVEL_NOMINAL },
  {   40000000, { HAL_CLK_SOURCE_GPLL0,          30,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   46400000, { HAL_CLK_SOURCE_GPLL0,          2,      29,     375,    375     }, CLOCK_VREG_LEVEL_NOMINAL },
  {   48000000, { HAL_CLK_SOURCE_GPLL0,          25,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   51200000, { HAL_CLK_SOURCE_GPLL0,          2,      32,     375,    375     }, CLOCK_VREG_LEVEL_NOMINAL },
  {   56000000, { HAL_CLK_SOURCE_GPLL0,          2,      7,      75,     75      }, CLOCK_VREG_LEVEL_NOMINAL },
  {   58982400, { HAL_CLK_SOURCE_GPLL0,          2,      1536,   15625,  15625   }, CLOCK_VREG_LEVEL_NOMINAL },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   63160000, { HAL_CLK_SOURCE_GPLL0,          19,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * LPASS AHB clock configurations.  Source output is 614.4/2 = 307.2.
 */
const ClockMuxConfigType  AHBClockConfig[] =
{
  {  19200 * 1000, { HAL_CLK_SOURCE_XO,       2, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  38400 * 1000, { HAL_CLK_SOURCE_LPAPLL2, 16, 0,  0,  0 }, CLOCK_VREG_LEVEL_LOW },
  {  76800 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  8, 0 , 0,  0 }, CLOCK_VREG_LEVEL_LOW },
  { 153600 * 1000, { HAL_CLK_SOURCE_LPAPLL2,  4, 0,  0,  0 }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};


/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFOSRClockConfig[] =
{
  {     128000, { HAL_CLK_SOURCE_LPAPLL2, 10,     1,    192,    192       }, CLOCK_VREG_LEVEL_LOW },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2, 30,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2, 20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  { 0 }
};

/*
 * Low Power Audio Interface (LPAIF) clocks
 */
const ClockMuxConfigType LPAIFPCMOEClockConfig[] =
{
  {     128000, { HAL_CLK_SOURCE_LPAPLL2, 10,     1,    192,    192       }, CLOCK_VREG_LEVEL_LOW },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2, 30,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2, 20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
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
  {     128000, { HAL_CLK_SOURCE_LPAPLL2, 10,     1,    192,    192       }, CLOCK_VREG_LEVEL_LOW },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,     16,     16       }, CLOCK_VREG_LEVEL_LOW },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      8,      8       }, CLOCK_VREG_LEVEL_LOW },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2, 30,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2, 20,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2, 30,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2, 20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL },
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
  {  24576 * 1000, { HAL_CLK_SOURCE_LPAPLL2, 10, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW },
  { 0 }
};


/*
 * Resampler clock configurations.
 */
const ClockMuxConfigType ResamplerClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,      2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW },
  {   68267000, { HAL_CLK_SOURCE_LPAPLL2, 6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW },
  {  136530000, { HAL_CLK_SOURCE_LPAPLL2, 3,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};


/*
 * QUP SPI clock configurations.
 */
const ClockMuxConfigType  QUPSPIClockConfig[] =
{
  {    960000,     { HAL_CLK_SOURCE_XO,    20,  1,   2,   2 }, CLOCK_VREG_LEVEL_LOW },
  {   4800000,     { HAL_CLK_SOURCE_XO,     8,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW },
  {   9600000,     { HAL_CLK_SOURCE_XO,     4,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW },
  {  15000000,     { HAL_CLK_SOURCE_GPLL0, 20,  1,   4,   4 }, CLOCK_VREG_LEVEL_LOW },
  {  19200000,     { HAL_CLK_SOURCE_XO,     2,  0,   0,   0 }, CLOCK_VREG_LEVEL_LOW },
  {  25000000,     { HAL_CLK_SOURCE_GPLL0, 24,  1,   2,   2 }, CLOCK_VREG_LEVEL_LOW },
  {  48000000,     { HAL_CLK_SOURCE_GPLL0, 25,  0,   0,   0 }, CLOCK_VREG_LEVEL_NOMINAL },
  {  50000000,     { HAL_CLK_SOURCE_GPLL0, 24,  0,   0,   0 }, CLOCK_VREG_LEVEL_NOMINAL },
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


/*
 * Clock Flag Init Config.
 */
const ClockFlagInitType ClockFlagInitConfig[] =
{
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_q6core",                                CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_qdsp_sway_aon_clk",                CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_aon_clk",                       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_bus_timeout_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_mpu_cfg_aon_clk",               CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_q6_ahbm_mpu_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_qos_ahbs_aon_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_wrapper_sysnoc_sway_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"q6ss_ahbm_aon_clk",                           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"q6ss_ahbs_aon_clk",                           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_peripheral_smmu_client_core_clk",  CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_core_clk",                         CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_aud_slimbus_core_clk",             CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_qca_slimbus_core_clk",             CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_lpm_core_clk",                     CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"audio_core_sysnoc_mport_core_clk",            CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_NONE,         (void*)0,                                             0                       } 
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
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
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
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   124800 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 8, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[1]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   163200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   249600 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[1]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   326400 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[0]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 700 * 1000,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   499200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[1]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   748800 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[2]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_NOMINAL_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   902400 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_HIGH,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL1[3]
                             },
    /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_HIGH_UV,
    /* .nLDOQ6UV          */ 0,
    /* .nStrapACCVal      */ 0x00000020
  },
};


static ClockCPUConfigType IntermediateCPUConfig =
{
  /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC,
  /* .Mux               */ {
    /* .nFreq             */   307200 * 1000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_LPAPLL2, 2, 0, 0, 0 },
    /* .eVRegLevel        */   CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_LPAPLL2[0]
  },
  /* .nVDDCPU           */ CLOCK_CPU_VREG_LEVEL_LOW_UV,
  /* .nLDOQ6UV          */ 0,
  /* .nStrapACCVal      */ 0x00000020
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

  CLOCK_CPU_PERF_LEVEL_TOTAL
};

/*
 * Enumeration of generic CPU performance levels.  More performance 
 * levels exist here than are actually implemented.
 */
static const uint32 QDSP6PerfList[] =
{
  CLOCK_CPU_PERF_LEVEL_0,  /*  19.2 MHz */
  CLOCK_CPU_PERF_LEVEL_1,  /* 124.8 MHz */
  CLOCK_CPU_PERF_LEVEL_2,  /* 163.2 MHz */
  CLOCK_CPU_PERF_LEVEL_3,  /* 249.6 MHz */
  CLOCK_CPU_PERF_LEVEL_4,  /* 326.4 MHz */
  CLOCK_CPU_PERF_LEVEL_5,  /* 499.2 MHz */
  CLOCK_CPU_PERF_LEVEL_6,  /* 748.8 MHz */
  CLOCK_CPU_PERF_LEVEL_7,  /* 902.4 MHz */
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
    CLOCK_CPU_PERF_LEVEL_7,
   
    /*
     * Init performance level
     */
    CLOCK_CPU_PERF_LEVEL_4,
   
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

   (ClockCPUConfigType*)&IntermediateCPUConfig

};


/*
 * Clock LDO Configuration Data.
 */
const ClockLDODataType ClockLDODataConfig[] =
{
  {
    /* nLDOCFG0 */           0x01004000,
    /* nLDOCFG1 */           0x00000050,
    /* nLDOCFG2 */           0x0000B068,
    /* nRetentionVoltage */  500 * 1000,
    /* nOperatingVoltage */  700 * 1000
  }
};


/*
 * OCMEM is not used on this chipset.  Add additional flags to this as needed.
 */
const ClockNPARemoteNodeSupportType ClockNPARemoteNodeSupport = 
{
   /* bOCMEM  = */ TRUE,
};


const HAL_clk_HWIOBaseType ClockLDOHWIOBases = 
{
   /* nPhysAddress */ 0x09000000,
   /* nSize        */ 0x00400000
};



const HAL_clk_HWIOBaseType ClockSECHWIOBases = 
{
   /* nPhysAddress */ 0x00070000,
   /* nSize        */ 0x00010000
};


const boolean ClockLDOVersion[] =
{
   1
};

