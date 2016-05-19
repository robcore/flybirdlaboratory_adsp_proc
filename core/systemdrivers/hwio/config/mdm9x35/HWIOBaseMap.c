
/*
===========================================================================
*/
/**
  @file HWIOBaseMap.c
  @brief Auto-generated HWIO Device Configuration base file.

  DESCRIPTION:
    This file contains Device Configuration data structures for mapping
    physical and virtual memory for HWIO blocks.
*/
/*
  ===========================================================================

  Copyright (c) 2013 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hwio/config/mdm9x35/HWIOBaseMap.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "DalHWIO.h"
#include "msmhwiobase.h"


/*=========================================================================
      Data Definitions
==========================================================================*/

static HWIOModuleType HWIOModules_PERIPH_SS[] =
{
  { "PERIPH_SS_SDC2_SDCC4_TOP",                    0x00080000, 0x00024b00 },
  { "PERIPH_SS_SDC2_SDCC_SDCC4",                   0x000a4000, 0x00000800 },
  { "PERIPH_SS_SDC2_SDCC_DML",                     0x000a4800, 0x00000100 },
  { "PERIPH_SS_SDC2_SDCC_SDCC4_HC",                0x000a4900, 0x00000200 },
  { "PERIPH_SS_SDC2_SDCC_SDCC4_BAM",               0x00080000, 0x00024000 },
  { "PERIPH_SS_SDC2_SDCC_BAM",                     0x00084000, 0x00007000 },
  { "PERIPH_SS_SDC2_SDCC_XPU2",                    0x00082000, 0x00002000 },
  { "PERIPH_SS_SDC2_SDCC_VMIDMT",                  0x00080000, 0x00001000 },
  { "PERIPH_SS_BLSP1_BLSP",                        0x00100000, 0x00029000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM",                    0x00104000, 0x00019000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_XPU2",               0x00102000, 0x00002000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_VMIDMT",             0x00100000, 0x00001000 },
  { "PERIPH_SS_BLSP1_BLSP_UART0_UART0_DM",         0x0011d000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_UART1_UART1_DM",         0x0011e000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_UART2_UART2_DM",         0x0011f000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_UART3_UART3_DM",         0x00120000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_UART4_UART4_DM",         0x00121000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_UART5_UART5_DM",         0x00122000, 0x000001c0 },
  { "PERIPH_SS_BLSP1_BLSP_QUP0",                   0x00123000, 0x00000500 },
  { "PERIPH_SS_BLSP1_BLSP_QUP1",                   0x00124000, 0x00000500 },
  { "PERIPH_SS_BLSP1_BLSP_QUP2",                   0x00125000, 0x00000500 },
  { "PERIPH_SS_BLSP1_BLSP_QUP3",                   0x00126000, 0x00000500 },
  { "PERIPH_SS_BLSP1_BLSP_QUP4",                   0x00127000, 0x00000500 },
  { "PERIPH_SS_BLSP1_BLSP_QUP5",                   0x00128000, 0x00000500 },
  { "PERIPH_SS_BAM_DMA_BAM_DMA_TOP_AUTO_SCALEV1_7", 0x00180000, 0x00024000 },
  { "PERIPH_SS_BAM_DMA_BAM",                       0x00184000, 0x00015000 },
  { "PERIPH_SS_BAM_DMA_XPU2",                      0x00182000, 0x00002000 },
  { "PERIPH_SS_BAM_DMA_VMIDMT",                    0x00180000, 0x00001000 },
  { "PERIPH_SS_BAM_DMA",                           0x00199000, 0x0000b000 },
  { "PERIPH_SS_USB2_HSIC_USB_OTG_HS_HSIC_BAM_LPM_TOP", 0x00200000, 0x00016000 },
  { "PERIPH_SS_USB2_HSIC_USB_OTG_HS_BASE",         0x00215000, 0x00001000 },
  { "PERIPH_SS_USB2_HSIC_USB_OTG_HS_BAM",          0x00200000, 0x00015000 },
  { "PERIPH_SS_USB2_HSIC_BAM",                     0x00204000, 0x00011000 },
  { "PERIPH_SS_USB2_HSIC_XPU2",                    0x00202000, 0x00002000 },
  { "PERIPH_SS_USB2_HSIC_VMIDMT",                  0x00200000, 0x00001000 },
  { "PERIPH_SS_USB1_HS_USB_OTG_HS_BAM_LPM_TOP",    0x00240000, 0x00016000 },
  { "PERIPH_SS_USB1_HS_USB_OTG_HS_BASE",           0x00255000, 0x00001000 },
  { "PERIPH_SS_USB1_HS_USB_OTG_HS_BAM",            0x00240000, 0x00015000 },
  { "PERIPH_SS_USB1_HS_BAM",                       0x00244000, 0x00011000 },
  { "PERIPH_SS_USB1_HS_XPU2",                      0x00242000, 0x00002000 },
  { "PERIPH_SS_USB1_HS_VMIDMT",                    0x00240000, 0x00001000 },
  { "PERIPH_SS_QPIC_QPIC",                         0x002c0000, 0x00040000 },
  { "PERIPH_SS_QPIC_QPIC_BAM_LITE_TOP_QPIC",       0x002c0000, 0x0000c000 },
  { "PERIPH_SS_QPIC_QPIC_BAM",                     0x002c4000, 0x00008000 },
  { "PERIPH_SS_QPIC_QPIC_XPU2",                    0x002c2000, 0x00002000 },
  { "PERIPH_SS_QPIC_QPIC_VMIDMT",                  0x002c0000, 0x00001000 },
  { "PERIPH_SS_QPIC_EBI2CR",                       0x002e0000, 0x00008000 },
  { "PERIPH_SS_QPIC_EBI2ND",                       0x002f0000, 0x00001000 },
  { "PERIPH_SS_QPIC_QPIC_MPU_MPU1132_8_M39L16_AHB_40", 0x002f1000, 0x00000600 },
  { "PERIPH_SS_PDM_PERPH_WEB",                     0x00310000, 0x00004000 },
  { "PERIPH_SS_PDM_WEB_TCXO4",                     0x00310000, 0x00004000 },
  { "PERIPH_SS_USB3PHY_AHB2PHY",                   0x00338000, 0x00008000 },
  { "PERIPH_SS_USB3PHY_USB3PHY_CM_PCIE_USB3_SW",   0x00338000, 0x00000800 },
  { "PERIPH_SS_USB3PHY_QSERDES_COM_QSERDES_COM_PCIE_USB3_COMMON", 0x00338000, 0x0000016c },
  { "PERIPH_SS_USB3PHY_QSERDES_TX_QSERDES_TX_PCIE_USB3_TX", 0x00338200, 0x000000e4 },
  { "PERIPH_SS_USB3PHY_QSERDES_RX_QSERDES_RX_PCIE_USB3_RX", 0x00338400, 0x000001f0 },
  { "PERIPH_SS_USB3PHY_PCIE_USB3_PCS",             0x00338600, 0x0000016c },
  { "PERIPH_SS_AHB2PHY_SWMAN",                     0x0033e000, 0x00000400 },
  { "PERIPH_SS_AHB2PHY_BROADCAST_SWMAN",           0x0033f000, 0x00000400 },
  { "PERIPH_SS_BUS_TIMEOUT_0_BUS_TIMEOUT",         0x003f7000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_1_BUS_TIMEOUT",         0x003f8000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_2_BUS_TIMEOUT",         0x003f9000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_3_BUS_TIMEOUT",         0x003fa000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_4_BUS_TIMEOUT",         0x003fb000, 0x00001000 },
  { "PERIPH_SS_MPU_MPU1132A_4_M15L7_AHB",          0x003fc000, 0x00000400 },
  { "PERIPH_SS_APU_APU0132_4",                     0x003fd000, 0x00000400 },
  { "PERIPH_SS_PRNG_PRNG",                         0x003ff000, 0x00000140 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM[] =
{
  { "RPM_DEC",                                     0x00080000, 0x00002000 },
  { "RPM_QTMR_AC",                                 0x00082000, 0x00001000 },
  { "RPM_F0_QTMR_V1_F0",                           0x00083000, 0x00001000 },
  { "RPM_F1_QTMR_V1_F1",                           0x00084000, 0x00001000 },
  { "RPM_MPU",                                     0x00086000, 0x00000500 },
  { "RPM_APU",                                     0x00087000, 0x00000280 },
  { "RPM_VMIDMT",                                  0x00088000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_QDSS_QDSS[] =
{
  { "QDSS_APB",                                    0x00000000, 0x00030000 },
  { "QDSS_DAPROM",                                 0x00000000, 0x00001000 },
  { "QDSS_QDSSCSR",                                0x00001000, 0x00001000 },
  { "QDSS_CXSTM_2_32_32_TRUE",                     0x00002000, 0x00001000 },
  { "QDSS_CTI0_CTI0_CSCTI",                        0x00010000, 0x00001000 },
  { "QDSS_CTI1_CTI1_CSCTI",                        0x00011000, 0x00001000 },
  { "QDSS_CTI2_CTI2_CSCTI",                        0x00012000, 0x00001000 },
  { "QDSS_CTI3_CTI3_CSCTI",                        0x00013000, 0x00001000 },
  { "QDSS_CTI4_CTI4_CSCTI",                        0x00014000, 0x00001000 },
  { "QDSS_CTI5_CTI5_CSCTI",                        0x00015000, 0x00001000 },
  { "QDSS_CTI6_CTI6_CSCTI",                        0x00016000, 0x00001000 },
  { "QDSS_CTI7_CTI7_CSCTI",                        0x00017000, 0x00001000 },
  { "QDSS_CTI8_CTI8_CSCTI",                        0x00018000, 0x00001000 },
  { "QDSS_CSTPIU_CSTPIU_CSTPIU",                   0x00020000, 0x00001000 },
  { "QDSS_IN_FUN0_IN_FUN0_CXATBFUNNEL_128W8SP",    0x00021000, 0x00001000 },
  { "QDSS_IN_FUN1_IN_FUN1_CXATBFUNNEL_128W8SP",    0x00022000, 0x00001000 },
  { "QDSS_MERG_FUN_MERG_FUN_CXATBFUNNEL_128W2SP",  0x00023000, 0x00001000 },
  { "QDSS_REPL64_REPL64_CXATBREPLICATOR_64WP",     0x00024000, 0x00001000 },
  { "QDSS_ETFETB_ETFETB_CXTMC_F128W64K",           0x00025000, 0x00001000 },
  { "QDSS_ETR_ETR_CXTMC_R64W32D",                  0x00026000, 0x00001000 },
  { "QDSS_AHB",                                    0x00070000, 0x00010000 },
  { "QDSS_VMIDDAP_VMIDDAP_VMIDMT_IDX_2_SSD1",      0x00076000, 0x00001000 },
  { "QDSS_VMIDETR_VMIDETR_VMIDMT_IDX_2_SSD1",      0x00077000, 0x00001000 },
  { "QDSS_NDPBAM_NDPBAM_BAM_NDP_TOP_AUTO_SCALEV1_7", 0x00078000, 0x00007000 },
  { "QDSS_NDPBAM_BAM",                             0x0007c000, 0x00003000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CLK_CTL[] =
{
  { "GCC_CLK_CTL_REG",                             0x00000000, 0x00010000 },
  { "GCC_RPU_RPU0032_128_L6",                      0x00010000, 0x00004200 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SYSTEM_NOC[] =
{
  { "SYSTEM_NOC",                                  0x00000000, 0x00003600 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CONFIG_NOC[] =
{
  { "CONFIG_NOC",                                  0x00000000, 0x00000080 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MPM2_MPM[] =
{
  { "MPM2_MPM",                                    0x00000000, 0x00001000 },
  { "MPM2_G_CTRL_CNTR",                            0x00001000, 0x00001000 },
  { "MPM2_G_RD_CNTR",                              0x00002000, 0x00001000 },
  { "MPM2_SLP_CNTR",                               0x00003000, 0x00001000 },
  { "MPM2_QTIMR_AC",                               0x00004000, 0x00001000 },
  { "MPM2_QTIMR_V1",                               0x00005000, 0x00001000 },
  { "MPM2_TSYNC",                                  0x00006000, 0x00001000 },
  { "MPM2_APU",                                    0x00007000, 0x00000780 },
  { "MPM2_TSENS",                                  0x00008000, 0x00001000 },
  { "MPM2_TSENS_TM",                               0x00009000, 0x00001000 },
  { "MPM2_WDOG",                                   0x0000a000, 0x00000020 },
  { "MPM2_PSHOLD",                                 0x0000b000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SPDM_WRAPPER_TOP[] =
{
  { "SPDM_SPDM_CREG",                              0x00000000, 0x00000120 },
  { "SPDM_SPDM_OLEM",                              0x00001000, 0x0000015c },
  { "SPDM_SPDM_RTEM",                              0x00002000, 0x00000318 },
  { "SPDM_APU0132_1",                              0x00003000, 0x00000280 },
  { "SPDM_SPDM_SREG",                              0x00004000, 0x00000120 },
  { "SPDM_VMIDMT_IDX_1_SSD0",                      0x00005000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SECURITY_CONTROL[] =
{
  { "SECURITY_CONTROL_CORE",                       0x00000000, 0x00007000 },
  { "SEC_CTRL_APU_APU1132_3",                      0x00007000, 0x00000380 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PMIC_ARB[] =
{
  { "PMIC_ARB_SPMI_CFG_TOP",                       0x00000000, 0x0000b000 },
  { "PMIC_ARB_SPMI_SPMI_GENI_CFG",                 0x0000a000, 0x00000700 },
  { "PMIC_ARB_SPMI_CFG",                           0x0000a700, 0x00000900 },
  { "PMIC_ARB_SPMI_SPMI_XPU2",                     0x00000000, 0x0000a000 },
  { "PMIC_ARB_SPMI_PIC",                           0x0000b000, 0x00000e00 },
  { "PMIC_ARB_XPU2",                               0x0000e000, 0x00001000 },
  { "PMIC_ARB_CORE",                               0x0000f000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CORE_TOP_CSR[] =
{
  { "TCSR_MUTEX_RPU1132_64_L7",                    0x00000000, 0x00002200 },
  { "TCSR_TCSR_MUTEX",                             0x00004000, 0x00002000 },
  { "TCSR_REGS_RPU1132_16_L12",                    0x00018000, 0x00000a00 },
  { "TCSR_TCSR_REGS",                              0x00020000, 0x00010000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_TLMM[] =
{
  { "TLMM_APU1032_111",                            0x00000000, 0x00003980 },
  { "TLMM_CSR",                                    0x00010000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS[] =
{
  { "LPASS_LPASS_CC_REG",                          0x00000000, 0x00045000 },
  { "LPASS_LPASS_TCSR",                            0x0004f000, 0x00000100 },
  { "LPASS_LPASS_AHBE",                            0x0004f100, 0x0000002d },
  { "LPASS_AHBE_CSR",                              0x0004f100, 0x0000002d },
  { "LPASS_AHBE_TIME",                             0x00071000, 0x00001000 },
  { "LPASS_Q6AHB_VMT",                             0x00072000, 0x00001000 },
  { "LPASS_Q6AXI_VMT",                             0x00073000, 0x00001000 },
  { "LPASS_LCC_XPU",                               0x00084000, 0x00004000 },
  { "LPASS_TOP_XPU",                               0x00088000, 0x00001000 },
  { "LPASS_SENSOR",                                0x000a0000, 0x00000800 },
  { "LPASS_LPASS_CSR",                             0x000b0000, 0x00009000 },
  { "LPASS_SPDM",                                  0x000c7000, 0x00000138 },
  { "LPASS_AHBI_TIME",                             0x000c8000, 0x00001000 },
  { "LPASS_LPASS_SYNC_WRAPPER",                    0x000c9000, 0x00000ffd },
  { "LPASS_AVTIMER",                               0x000c9000, 0x00000100 },
  { "LPASS_AUDSYNC_WRAPPER",                       0x000c9200, 0x000001fd },
  { "LPASS_DM_VMT",                                0x000cc000, 0x00001000 },
  { "LPASS_LPAIF_VMT",                             0x000cd000, 0x00001000 },
  { "LPASS_LPM_XPU",                               0x000db000, 0x00001000 },
  { "LPASS_CSR_XPU",                               0x000dc000, 0x00001000 },
  { "LPASS_CMN_XPU",                               0x000dd000, 0x00001000 },
  { "LPASS_LPAIF_XPU",                             0x000ec000, 0x00002000 },
  { "LPASS_LPASS_LPM",                             0x00100000, 0x00004000 },
  { "LPASS_LPA_IF",                                0x00140000, 0x0001fffd },
  { "LPASS_SBMASTER0_BASE",                        0x00180000, 0x00080000 },
  { "LPASS_SB_SLIMBUS_BAM_LITE",                   0x00180000, 0x00024000 },
  { "LPASS_SB_BAM",                                0x00184000, 0x00014000 },
  { "LPASS_SB_XPU2",                               0x00182000, 0x00002000 },
  { "LPASS_SB_VMIDMT",                             0x00180000, 0x00001000 },
  { "LPASS_SLIMBUS",                               0x001af000, 0x0002c000 },
  { "LPASS_QDSP6SS_PUBLIC",                        0x00200000, 0x00080000 },
  { "LPASS_QDSP6SS_PUB",                           0x00200000, 0x00004040 },
  { "LPASS_QDSP6SS_QDSP6SS_APU0132_2",             0x00270000, 0x00000300 },
  { "LPASS_QDSP6SS_PRIVATE",                       0x00280000, 0x00080000 },
  { "LPASS_QDSP6SS_CSR",                           0x00280000, 0x00008028 },
  { "LPASS_QDSP6SS_L2VIC",                         0x00290000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_QTMR_AC",               0x002a0000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F0_0",                     0x002a1000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F1_1",                     0x002a2000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F2_2",                     0x002a3000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_SAW2",                  0x002b0000, 0x00000ff0 },
  { NULL, 0, 0 }
};

HWIOPhysRegionType HWIOBaseMap[] =
{
  {
    "PERIPH_SS",
    (DALSYSMemAddr)0xf9800000,
    0x00400000,
    (DALSYSMemAddr)PERIPH_SS_BASE,
    HWIOModules_PERIPH_SS
  },
  {
    "RPM",
    (DALSYSMemAddr)0xfc100000,
    0x00090000,
    (DALSYSMemAddr)RPM_BASE,
    HWIOModules_RPM
  },
  {
    "QDSS_QDSS",
    (DALSYSMemAddr)0xfc300000,
    0x00080000,
    (DALSYSMemAddr)QDSS_QDSS_BASE,
    HWIOModules_QDSS_QDSS
  },
  {
    "CLK_CTL",
    (DALSYSMemAddr)0xfc400000,
    0x00020000,
    (DALSYSMemAddr)CLK_CTL_BASE,
    HWIOModules_CLK_CTL
  },
  {
    "RPM_SS_MSG_RAM_START_ADDRESS",
    (DALSYSMemAddr)0xfc428000,
    0x00004000,
    (DALSYSMemAddr)RPM_SS_MSG_RAM_START_ADDRESS_BASE,
    HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS
  },
  {
    "SYSTEM_NOC",
    (DALSYSMemAddr)0xfc460000,
    0x00004000,
    (DALSYSMemAddr)SYSTEM_NOC_BASE,
    HWIOModules_SYSTEM_NOC
  },
  {
    "CONFIG_NOC",
    (DALSYSMemAddr)0xfc480000,
    0x00001000,
    (DALSYSMemAddr)CONFIG_NOC_BASE,
    HWIOModules_CONFIG_NOC
  },
  {
    "MPM2_MPM",
    (DALSYSMemAddr)0xfc4a0000,
    0x0000c000,
    (DALSYSMemAddr)MPM2_MPM_BASE,
    HWIOModules_MPM2_MPM
  },
  {
    "SPDM_WRAPPER_TOP",
    (DALSYSMemAddr)0xfc4b0000,
    0x00006000,
    (DALSYSMemAddr)SPDM_WRAPPER_TOP_BASE,
    HWIOModules_SPDM_WRAPPER_TOP
  },
  {
    "SECURITY_CONTROL",
    (DALSYSMemAddr)0xfc4b8000,
    0x00008000,
    (DALSYSMemAddr)SECURITY_CONTROL_BASE,
    HWIOModules_SECURITY_CONTROL
  },
  {
    "PMIC_ARB",
    (DALSYSMemAddr)0xfc4c0000,
    0x00010000,
    (DALSYSMemAddr)PMIC_ARB_BASE,
    HWIOModules_PMIC_ARB
  },
  {
    "CORE_TOP_CSR",
    (DALSYSMemAddr)0xfd480000,
    0x00030000,
    (DALSYSMemAddr)CORE_TOP_CSR_BASE,
    HWIOModules_CORE_TOP_CSR
  },
  {
    "TLMM",
    (DALSYSMemAddr)0xfd500000,
    0x00020000,
    (DALSYSMemAddr)TLMM_BASE,
    HWIOModules_TLMM
  },
  {
    "LPASS",
    (DALSYSMemAddr)0xfe000000,
    0x00300000,
    (DALSYSMemAddr)LPASS_BASE,
    HWIOModules_LPASS
  },
  { NULL, 0, 0, 0, NULL }
};

