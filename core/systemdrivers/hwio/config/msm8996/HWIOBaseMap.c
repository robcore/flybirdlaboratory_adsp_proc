
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

  Copyright (c) 2014 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hwio/config/msm8996/HWIOBaseMap.c#1 $
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

static HWIOModuleType HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SECURITY_CONTROL[] =
{
  { "SECURITY_CONTROL_CORE",                       0x00000000, 0x00007000 },
  { "SECURE_CHANNEL",                              0x00008000, 0x00004200 },
  { "KEY_CTRL",                                    0x00008000, 0x00004000 },
  { "CRI_CM",                                      0x0000c000, 0x00000100 },
  { "CRI_CM_EXT",                                  0x0000c100, 0x00000100 },
  { "SEC_CTRL_APU_APU1132_37",                     0x0000e000, 0x00001480 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM[] =
{
  { "RPM_DEC",                                     0x00080000, 0x00002000 },
  { "RPM_QTMR_AC",                                 0x00082000, 0x00001000 },
  { "RPM_F0_QTMR_V1_F0",                           0x00083000, 0x00001000 },
  { "RPM_F1_QTMR_V1_F1",                           0x00084000, 0x00001000 },
  { "RPM_MSTR_MPU",                                0x00089000, 0x00000c00 },
  { "RPM_VMIDMT",                                  0x00088000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CLK_CTL[] =
{
  { "GCC_CLK_CTL_REG",                             0x00000000, 0x00090000 },
  { "GCC_RPU_RPU0032_144_L12",                     0x00090000, 0x00004a00 },
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

static HWIOModuleType HWIOModules_CONFIG_NOC[] =
{
  { "CONFIG_NOC",                                  0x00000000, 0x00000080 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SYSTEM_NOC[] =
{
  { "SYSTEM_NOC",                                  0x00000000, 0x00009100 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CORE_TOP_CSR[] =
{
  { "TCSR_MUTEX_RPU1132_64_L12",                   0x00000000, 0x00002200 },
  { "TCSR_TCSR_MUTEX",                             0x00040000, 0x00040000 },
  { "TCSR_REGS_RPU1132_24_L12",                    0x00080000, 0x00000e00 },
  { "TCSR_TCSR_REGS",                              0x000a0000, 0x00018000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_TLMM[] =
{
  { "TLMM_APU1032_175",                            0x00000000, 0x00005980 },
  { "TLMM_CSR",                                    0x00010000, 0x00300000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_QDSS_QDSS_CHIP[] =
{
  { "QDSS_APB",                                    0x00000000, 0x00030000 },
  { "QDSS_DAPROM",                                 0x00000000, 0x00001000 },
  { "QDSS_QDSSCSR",                                0x00001000, 0x00001000 },
  { "QDSS_CXSTM_8_32_32_TRUE",                     0x00002000, 0x00001000 },
  { "QDSS_TPDA_TPDA_TPDA_S8_W64_D8_M64_CSF9D1CB23", 0x00003000, 0x00001000 },
  { "QDSS_TPDM_TPDM_TPDM_ATB64_ATCLK_DSB256_CS319DD72A", 0x00004000, 0x00001000 },
  { "QDSS_CTI0_CTI0_CSCTI",                        0x00010000, 0x00001000 },
  { "QDSS_CTI1_CTI1_CSCTI",                        0x00011000, 0x00001000 },
  { "QDSS_CTI2_CTI2_CSCTI",                        0x00012000, 0x00001000 },
  { "QDSS_CTI3_CTI3_CSCTI",                        0x00013000, 0x00001000 },
  { "QDSS_CTI4_CTI4_CSCTI",                        0x00014000, 0x00001000 },
  { "QDSS_CTI5_CTI5_CSCTI",                        0x00015000, 0x00001000 },
  { "QDSS_CTI6_CTI6_CSCTI",                        0x00016000, 0x00001000 },
  { "QDSS_CTI7_CTI7_CSCTI",                        0x00017000, 0x00001000 },
  { "QDSS_CTI8_CTI8_CSCTI",                        0x00018000, 0x00001000 },
  { "QDSS_CTI9_CTI9_CSCTI",                        0x00019000, 0x00001000 },
  { "QDSS_CTI10_CTI10_CSCTI",                      0x0001a000, 0x00001000 },
  { "QDSS_CTI11_CTI11_CSCTI",                      0x0001b000, 0x00001000 },
  { "QDSS_CTI12_CTI12_CSCTI",                      0x0001c000, 0x00001000 },
  { "QDSS_CTI13_CTI13_CSCTI",                      0x0001d000, 0x00001000 },
  { "QDSS_CTI14_CTI14_CSCTI",                      0x0001e000, 0x00001000 },
  { "QDSS_CSTPIU_CSTPIU_CSTPIU",                   0x00020000, 0x00001000 },
  { "QDSS_IN_FUN0_IN_FUN0_CXATBFUNNEL_128W8SP",    0x00021000, 0x00001000 },
  { "QDSS_IN_FUN1_IN_FUN1_CXATBFUNNEL_128W8SP",    0x00022000, 0x00001000 },
  { "QDSS_MERG_FUN_MERG_FUN_CXATBFUNNEL_128W2SP",  0x00023000, 0x00001000 },
  { "QDSS_REPL64_REPL64_CXATBREPLICATOR_64WP",     0x00024000, 0x00001000 },
  { "QDSS_ETFETB_ETFETB_CXTMC_F128W64K",           0x00025000, 0x00001000 },
  { "QDSS_ETR_ETR_CXTMC_R64W32D",                  0x00026000, 0x00001000 },
  { "QDSS_SSC_CTI_0_SSC_CTI_0_CSCTI",              0x00030000, 0x00001000 },
  { "QDSS_SSC_CTI_1_SSC_CTI_1_CSCTI",              0x00031000, 0x00001000 },
  { "QDSS_SSC_STM_SSC_STM_CXSTM_8_32_32_TRUE",     0x00033000, 0x00001000 },
  { "QDSS_SSC_FUN0_SSC_FUN0_CXATBFUNNEL_128W8SP",  0x00034000, 0x00001000 },
  { "QDSS_SSC_ETFETB_SSC_ETFETB_CXTMC_F128W64K",   0x00035000, 0x00001000 },
  { "QDSS_VSENSE_CONTROLLER",                      0x00038000, 0x00001000 },
  { "QDSS_QDSP6_CTI_QDSP6_CTI_CSCTI",              0x00044000, 0x00001000 },
  { "QDSS_RPM_M3_CTI_RPM_M3_CTI_CSCTI",            0x00048000, 0x00001000 },
  { "QDSS_PRNG_TPDM_PRNG_TPDM_TPDM_ATB32_APCLK_CMB32_CS5CFE4153", 0x0004c000, 0x00001000 },
  { "QDSS_PIMEM_TPDM_PIMEM_TPDM_TPDM_ATB64_APCLK_GPRCLK_BC8_TC2_CMB64_DSB64_CS4528A7E6", 0x00050000, 0x00001000 },
  { "QDSS_DCC_TPDM_DCC_TPDM_TPDM_ATB8_ATCLK_CMB32_CSDED7E5A1", 0x00054000, 0x00001000 },
  { "QDSS_ISTARI_APB2JTAG",                        0x00058000, 0x00004000 },
  { "QDSS_VMIDDAP_VMIDDAP_VMIDMT_IDX_2_SSD1",      0x00076000, 0x00001000 },
  { "QDSS_VMIDETR_VMIDETR_VMIDMT_IDX_2_SSD1",      0x00077000, 0x00001000 },
  { "QDSS_NDPBAM_NDPBAM_BAM_NDP_TOP_AUTO_SCALE_V2_0", 0x00080000, 0x00019000 },
  { "QDSS_NDPBAM_BAM",                             0x00084000, 0x00015000 },
  { "QDSS_ISDB_CTI_ISDB_CTI_CSCTI",                0x00141000, 0x00001000 },
  { "QDSS_GPMU_CTI_GPMU_CTI_CSCTI",                0x00142000, 0x00001000 },
  { "QDSS_ARM9_CTI_ARM9_CTI_CSCTI",                0x00180000, 0x00001000 },
  { "QDSS_VENUS_ARM9_ETM_VENUS_ARM9_ETM_A9ETM",    0x00181000, 0x00001000 },
  { "QDSS_MMSS_FUNNEL_MMSS_FUNNEL_CXATBFUNNEL_64W8SP", 0x00184000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PMIC_ARB[] =
{
  { "SPMI_CFG_TOP",                                0x00000000, 0x0000d000 },
  { "SPMI_GENI_CFG",                               0x0000a000, 0x00000700 },
  { "SPMI_CFG",                                    0x0000a700, 0x00001a00 },
  { "SPMI_PIC",                                    0x01800000, 0x00200000 },
  { "PMIC_ARB_MPU1132_18_M25L12_AHB",              0x0000e000, 0x00000b00 },
  { "PMIC_ARB_CORE",                               0x0000f000, 0x00001000 },
  { "PMIC_ARB_CORE_REGISTERS",                     0x00400000, 0x00800000 },
  { "PMIC_ARB_CORE_REGISTERS_OBS",                 0x00c00000, 0x00800000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS[] =
{
  { "PERIPH_SS_PDM_PERPH_WEB",                     0x00000000, 0x00004000 },
  { "PERIPH_SS_PDM_WEB_TCXO4",                     0x00000000, 0x00004000 },
  { "PERIPH_SS_BUS_TIMEOUT_0_BUS_TIMEOUT",         0x00004000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_1_BUS_TIMEOUT",         0x00005000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_2_BUS_TIMEOUT",         0x00006000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_3_BUS_TIMEOUT",         0x00007000, 0x00001000 },
  { "PERIPH_SS_BUS_TIMEOUT_4_BUS_TIMEOUT",         0x00008000, 0x00001000 },
  { "PERIPH_SS_MPU_MPU1132A_4_M15L7_AHB",          0x0000f000, 0x00000400 },
  { "PERIPH_SS_USB_PHYS_AHB2PHY",                  0x00010000, 0x00008000 },
  { "PERIPH_SS_AHB2PHY_BROADCAST_SWMAN",           0x00017000, 0x00000400 },
  { "PERIPH_SS_AHB2PHY_SWMAN",                     0x00016000, 0x00000400 },
  { "PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_SEC_CM_QUSB2_LQ_1EX", 0x00012000, 0x00000180 },
  { "PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PRIM_CM_QUSB2_LQ_1EX", 0x00011000, 0x00000180 },
  { "PERIPH_SS_USB3PHY_USB3PHY_CM_USB3_SW",        0x00010000, 0x00000800 },
  { "PERIPH_SS_USB3PHY_QSERDES_COM_QSERDES_COM_USB3_QSRV_COM", 0x00010000, 0x000001c4 },
  { "PERIPH_SS_USB3PHY_QSERDES_TX_QSERDES_TX_USB3_TX_MPHY", 0x00010200, 0x00000130 },
  { "PERIPH_SS_USB3PHY_QSERDES_RX_QSERDES_RX_USB3_RX_MPHY", 0x00010400, 0x00000200 },
  { "PERIPH_SS_USB3PHY_USB3_PHY_USB3_PHY_USB3_PCS", 0x00010600, 0x000001a8 },
  { "PERIPH_SS_SDC1_SDCC5_TOP",                    0x00040000, 0x00026800 },
  { "PERIPH_SS_SDC1_SDCC_XPU2",                    0x00042000, 0x00000300 },
  { "PERIPH_SS_SDC1_SDCC_SDCC5",                   0x00064000, 0x00000800 },
  { "PERIPH_SS_SDC1_SDCC_SDCC5_HC",                0x00064900, 0x00000500 },
  { "PERIPH_SS_SDC1_SDCC_SDCC5_HC_CMDQ",           0x00064e00, 0x00000200 },
  { "PERIPH_SS_SDC1_SDCC_SDCC5_HC_SCM",            0x00065000, 0x00000100 },
  { "PERIPH_SS_SDC1_SDCC_SCM",                     0x00066000, 0x00000800 },
  { "PERIPH_SS_SDC2_SDCC5_TOP",                    0x00080000, 0x00026800 },
  { "PERIPH_SS_SDC2_SDCC_XPU2",                    0x00082000, 0x00000300 },
  { "PERIPH_SS_SDC2_SDCC_SDCC5",                   0x000a4000, 0x00000800 },
  { "PERIPH_SS_SDC2_SDCC_SDCC5_HC",                0x000a4900, 0x00000500 },
  { "PERIPH_SS_SDC2_SDCC_SDCC5_HC_SCM",            0x000a5000, 0x00000100 },
  { "PERIPH_SS_SDC2_SDCC_SCM",                     0x000a6000, 0x00000800 },
  { "PERIPH_SS_SDC4_SDCC5_TOP",                    0x00100000, 0x00026800 },
  { "PERIPH_SS_SDC4_SDCC_SDCC5",                   0x00124000, 0x00000800 },
  { "PERIPH_SS_SDC4_SDCC_SDCC5_HC",                0x00124900, 0x00000500 },
  { "PERIPH_SS_SDC4_SDCC_SDCC5_HC_SCM",            0x00125000, 0x00000100 },
  { "PERIPH_SS_BLSP1_BLSP",                        0x00140000, 0x00040000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM",                    0x00144000, 0x0002b000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_XPU2",               0x00142000, 0x00002000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_VMIDMT",             0x00140000, 0x00001000 },
  { "PERIPH_SS_BLSP1_BLSP_UART0_UART0_DM",         0x0016f000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART1_UART1_DM",         0x00170000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART2_UART2_DM",         0x00171000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART3_UART3_DM",         0x00172000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART4_UART4_DM",         0x00173000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART5_UART5_DM",         0x00174000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_QUP0",                   0x00175000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP1",                   0x00176000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP2",                   0x00177000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP3",                   0x00178000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP4",                   0x00179000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP5",                   0x0017a000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP",                        0x00180000, 0x00040000 },
  { "PERIPH_SS_BLSP2_BLSP_BAM",                    0x00184000, 0x0002b000 },
  { "PERIPH_SS_BLSP2_BLSP_BAM_XPU2",               0x00182000, 0x00002000 },
  { "PERIPH_SS_BLSP2_BLSP_BAM_VMIDMT",             0x00180000, 0x00001000 },
  { "PERIPH_SS_BLSP2_BLSP_UART0_UART0_DM",         0x001af000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART1_UART1_DM",         0x001b0000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART2_UART2_DM",         0x001b1000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART3_UART3_DM",         0x001b2000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART4_UART4_DM",         0x001b3000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART5_UART5_DM",         0x001b4000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_QUP0",                   0x001b5000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP1",                   0x001b6000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP2",                   0x001b7000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP3",                   0x001b8000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP4",                   0x001b9000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP5",                   0x001ba000, 0x00000600 },
  { "PERIPH_SS_TSIF_TSIF_12SEG_WRAPPER",           0x001c0000, 0x00040000 },
  { "PERIPH_SS_TSIF_TSIF_TSIF_BAM_LITE_TOP_AUTO_SCALE_V2_0", 0x001c0000, 0x00027000 },
  { "PERIPH_SS_TSIF_TSIF_BAM",                     0x001c4000, 0x00023000 },
  { "PERIPH_SS_TSIF_TSIF_0_TSIF_0_TSIF",           0x001e7000, 0x00000200 },
  { "PERIPH_SS_TSIF_TSIF_1_TSIF_1_TSIF",           0x001e8000, 0x00000200 },
  { "PERIPH_SS_TSIF_TSIF_TSIF_TSPP",               0x001e9000, 0x00001000 },
  { "PERIPH_SS_USB1_HS_USB20S",                    0x00200000, 0x00200000 },
  { "PERIPH_SS_USB1_HS_DWC_USB3",                  0x00200000, 0x0000cd00 },
  { "PERIPH_SS_USB1_HS_USB30_QSCRATCH",            0x002f8800, 0x00000400 },
  { "PERIPH_SS_USB1_HS_USB30_QSRAM_REGS",          0x002fc000, 0x00000100 },
  { "PERIPH_SS_USB1_HS_USB30_DBM_REGFILE",         0x002f8000, 0x00000400 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS[] =
{
  { "LPASS_LPASS_CC_REG",                          0x00000000, 0x0003c000 },
  { "LPASS_LPASS_TCSR",                            0x00080000, 0x0001e000 },
  { "LPASS_LPASS_QOS",                             0x000a0000, 0x00004000 },
  { "LPASS_QOS_QOS_GENERIC",                       0x000a0000, 0x00000100 },
  { "LPASS_QOS_QOS_DEBUG",                         0x000a0100, 0x00000200 },
  { "LPASS_QOS_QOS_DANGER",                        0x000a0300, 0x00000200 },
  { "LPASS_QOS_QOS_INTERRUPTS",                    0x000a1000, 0x00002000 },
  { "LPASS_QOS_QOS_THROTTLE",                      0x000a3000, 0x00001000 },
  { "LPASS_AHBE_TIME",                             0x000b7000, 0x00001000 },
  { "LPASS_Q6SS_MPU",                              0x000b8000, 0x00001600 },
  { "LPASS_LPASS_CSR",                             0x000c0000, 0x0001c000 },
  { "LPASS_AHBI_TIME",                             0x000f6000, 0x00001000 },
  { "LPASS_LPASS_SYNC_WRAPPER",                    0x000f7000, 0x00000ffd },
  { "LPASS_AVTIMER",                               0x000f7000, 0x00000100 },
  { "LPASS_LPASS_HDMITX",                          0x000f8000, 0x00007000 },
  { "LPASS_ATIMER",                                0x000ff000, 0x00000100 },
  { "LPASS_LPA_IF",                                0x00100000, 0x0001fffd },
  { "LPASS_LPASS_LPM",                             0x00120000, 0x00010000 },
  { "LPASS_TLB_PL",                                0x00130000, 0x00005000 },
  { "LPASS_RESAMPLER",                             0x00138000, 0x00008000 },
  { "LPASS_CORE_LPASS_CORE_QOS",                   0x00140000, 0x00003000 },
  { "LPASS_CORE_QOS_QOS_GENERIC",                  0x00140000, 0x00000100 },
  { "LPASS_CORE_QOS_QOS_DEBUG",                    0x00140100, 0x00000200 },
  { "LPASS_CORE_QOS_QOS_INTERRUPTS",               0x00141000, 0x00002000 },
  { "LPASS_AUD_SBMASTER0_BASE",                    0x00180000, 0x00080000 },
  { "LPASS_AUD_SB_SLIMBUS_BAM_LITE",               0x00180000, 0x00036000 },
  { "LPASS_AUD_SB_BAM",                            0x00184000, 0x00032000 },
  { "LPASS_AUD_SLIMBUS",                           0x001c0000, 0x0002c000 },
  { "LPASS_QCA_SBMASTER0_BASE",                    0x00200000, 0x00080000 },
  { "LPASS_QCA_SB_SLIMBUS_BAM_LITE",               0x00200000, 0x0002a000 },
  { "LPASS_QCA_SB_BAM",                            0x00204000, 0x00026000 },
  { "LPASS_QCA_SLIMBUS",                           0x00240000, 0x0002c000 },
  { "LPASS_QDSP6SS_PUBLIC",                        0x00300000, 0x00080000 },
  { "LPASS_QDSP6SS_PUB",                           0x00300000, 0x00004040 },
  { "LPASS_QDSP6SS_PRIVATE",                       0x00380000, 0x00080000 },
  { "LPASS_QDSP6SS_CSR",                           0x00380000, 0x00008028 },
  { "LPASS_QDSP6SS_L2VIC",                         0x00390000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_QTMR_AC",               0x003a0000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F0_0",                     0x003a1000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F1_1",                     0x003a2000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F2_2",                     0x003a3000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_SAW3",                  0x003b0000, 0x00001000 },
  { NULL, 0, 0 }
};

HWIOPhysRegionType HWIOBaseMap[] =
{
  {
    "SPDM_WRAPPER_TOP",
    (DALSYSMemAddr)0x00048000,
    0x00006000,
    (DALSYSMemAddr)SPDM_WRAPPER_TOP_BASE,
    HWIOModules_SPDM_WRAPPER_TOP
  },
  {
    "RPM_SS_MSG_RAM_START_ADDRESS",
    (DALSYSMemAddr)0x00068000,
    0x00004000,
    (DALSYSMemAddr)RPM_SS_MSG_RAM_START_ADDRESS_BASE,
    HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS
  },
  {
    "SECURITY_CONTROL",
    (DALSYSMemAddr)0x00070000,
    0x00010000,
    (DALSYSMemAddr)SECURITY_CONTROL_BASE,
    HWIOModules_SECURITY_CONTROL
  },
  {
    "RPM",
    (DALSYSMemAddr)0x00200000,
    0x00090000,
    (DALSYSMemAddr)RPM_BASE,
    HWIOModules_RPM
  },
  {
    "CLK_CTL",
    (DALSYSMemAddr)0x00300000,
    0x000a0000,
    (DALSYSMemAddr)CLK_CTL_BASE,
    HWIOModules_CLK_CTL
  },
  {
    "MPM2_MPM",
    (DALSYSMemAddr)0x004a0000,
    0x0000c000,
    (DALSYSMemAddr)MPM2_MPM_BASE,
    HWIOModules_MPM2_MPM
  },
  {
    "CONFIG_NOC",
    (DALSYSMemAddr)0x00500000,
    0x00001000,
    (DALSYSMemAddr)CONFIG_NOC_BASE,
    HWIOModules_CONFIG_NOC
  },
  {
    "SYSTEM_NOC",
    (DALSYSMemAddr)0x00520000,
    0x00009100,
    (DALSYSMemAddr)SYSTEM_NOC_BASE,
    HWIOModules_SYSTEM_NOC
  },
  {
    "CORE_TOP_CSR",
    (DALSYSMemAddr)0x00700000,
    0x000c0000,
    (DALSYSMemAddr)CORE_TOP_CSR_BASE,
    HWIOModules_CORE_TOP_CSR
  },
  {
    "TLMM",
    (DALSYSMemAddr)0x01000000,
    0x00300000,
    (DALSYSMemAddr)TLMM_BASE,
    HWIOModules_TLMM
  },
  {
    "QDSS_QDSS_CHIP",
    (DALSYSMemAddr)0x03000000,
    0x00800000,
    (DALSYSMemAddr)QDSS_QDSS_CHIP_BASE,
    HWIOModules_QDSS_QDSS_CHIP
  },
  {
    "PMIC_ARB",
    (DALSYSMemAddr)0x04000000,
    0x02000000,
    (DALSYSMemAddr)PMIC_ARB_BASE,
    HWIOModules_PMIC_ARB
  },
  {
    "PERIPH_SS",
    (DALSYSMemAddr)0x07400000,
    0x00400000,
    (DALSYSMemAddr)PERIPH_SS_BASE,
    HWIOModules_PERIPH_SS
  },
  {
    "LPASS",
    (DALSYSMemAddr)0x09000000,
    0x00400000,
    (DALSYSMemAddr)LPASS_BASE,
    HWIOModules_LPASS
  },
  { NULL, 0, 0, 0, NULL }
};

