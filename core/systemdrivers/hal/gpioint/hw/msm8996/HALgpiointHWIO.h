#ifndef __HALGPIOINTHWIO_H__
#define __HALGPIOINTHWIO_H__
/*
===========================================================================
*/
/**
  @file HALgpiointHWIO.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    TLMM_CSR

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
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

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/gpioint/hw/msm8996/HALgpiointHWIO.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

extern uint32 nGPIOIntBaseAddress;
extern uint32 nGPIOIntBaseAddressPhys;

#define TLMM_BASE nGPIOIntBaseAddress
#define TLMM_BASE_PHYS nGPIOIntBaseAddressPhys


/*----------------------------------------------------------------------------
 * MODULE: TLMM_CSR
 *--------------------------------------------------------------------------*/

#define TLMM_CSR_REG_BASE                                                  (TLMM_BASE      + 0x00010000)
#define TLMM_CSR_REG_BASE_PHYS                                             (TLMM_BASE_PHYS + 0x00010000)
#define TLMM_CSR_REG_BASE_OFFS                                             0x00010000

#define HWIO_TLMM_GPIO_CFGn_ADDR(n)                                        (TLMM_CSR_REG_BASE      + 0x00000000 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_CFGn_PHYS(n)                                        (TLMM_CSR_REG_BASE_PHYS + 0x00000000 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_CFGn_OFFS(n)                                        (TLMM_CSR_REG_BASE_OFFS + 0x00000000 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_CFGn_RMSK                                                0x7ff
#define HWIO_TLMM_GPIO_CFGn_MAXn                                                  149
#define HWIO_TLMM_GPIO_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), HWIO_TLMM_GPIO_CFGn_RMSK)
#define HWIO_TLMM_GPIO_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_CFGn_INI(n))
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_BMSK                                  0x400
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_SHFT                                    0xa
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK                                        0x200
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT                                          0x9
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK                                   0x1c0
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT                                     0x6
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_2_MA_FVAL                            0x0
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_4_MA_FVAL                            0x1
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_6_MA_FVAL                            0x2
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_8_MA_FVAL                            0x3
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_10_MA_FVAL                           0x4
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_12_MA_FVAL                           0x5
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_14_MA_FVAL                           0x6
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_16_MA_FVAL                           0x7
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK                                        0x3c
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT                                         0x2
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK                                        0x3
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT                                        0x0
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_NO_PULL_FVAL                                0x0
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_PULL_DOWN_FVAL                              0x1
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_KEEPER_FVAL                                 0x2
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_PULL_UP_FVAL                                0x3

#define HWIO_TLMM_GPIO_IN_OUTn_ADDR(n)                                     (TLMM_CSR_REG_BASE      + 0x00000004 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_PHYS(n)                                     (TLMM_CSR_REG_BASE_PHYS + 0x00000004 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_OFFS(n)                                     (TLMM_CSR_REG_BASE_OFFS + 0x00000004 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_RMSK                                               0x3
#define HWIO_TLMM_GPIO_IN_OUTn_MAXn                                               149
#define HWIO_TLMM_GPIO_IN_OUTn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), HWIO_TLMM_GPIO_IN_OUTn_RMSK)
#define HWIO_TLMM_GPIO_IN_OUTn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),val)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),mask,val,HWIO_TLMM_GPIO_IN_OUTn_INI(n))
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK                                      0x2
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT                                      0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_BMSK                                       0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_SHFT                                       0x0

#define HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n)                                   (TLMM_CSR_REG_BASE      + 0x00000008 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_PHYS(n)                                   (TLMM_CSR_REG_BASE_PHYS + 0x00000008 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_OFFS(n)                                   (TLMM_CSR_REG_BASE_OFFS + 0x00000008 + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_RMSK                                           0x1ff
#define HWIO_TLMM_GPIO_INTR_CFGn_MAXn                                             149
#define HWIO_TLMM_GPIO_INTR_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), HWIO_TLMM_GPIO_INTR_CFGn_RMSK)
#define HWIO_TLMM_GPIO_INTR_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_CFGn_INI(n))
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_BMSK                               0x100
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_SHFT                                 0x8
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_DISABLE_FVAL                         0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_ENABLE_FVAL                          0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_BMSK                                0xe0
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SHFT                                 0x5
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SENSORS_FVAL                         0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_LPA_DSP_FVAL                         0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_RPM_FVAL                             0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_HMSS_FVAL                            0x3
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_GSS_FVAL                             0x4
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_TZ_FVAL                              0x5
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_NONE_FVAL                            0x7
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_BMSK                         0x10
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_SHFT                          0x4
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_DISABLE_FVAL                  0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_ENABLE_FVAL                   0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_BMSK                               0xc
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_SHFT                               0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_LEVEL_FVAL                         0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_POS_EDGE_FVAL                      0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_NEG_EDGE_FVAL                      0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_DUAL_EDGE_FVAL                     0x3
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_BMSK                                0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_SHFT                                0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_POLARITY_0_FVAL                     0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_POLARITY_1_FVAL                     0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_BMSK                                 0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_SHFT                                 0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_DISABLE_FVAL                         0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_ENABLE_FVAL                          0x1

#define HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n)                                (TLMM_CSR_REG_BASE      + 0x0000000c + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_PHYS(n)                                (TLMM_CSR_REG_BASE_PHYS + 0x0000000c + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_OFFS(n)                                (TLMM_CSR_REG_BASE_OFFS + 0x0000000c + 0x1000 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_RMSK                                          0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_MAXn                                          149
#define HWIO_TLMM_GPIO_INTR_STATUSn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), HWIO_TLMM_GPIO_INTR_STATUSn_RMSK)
#define HWIO_TLMM_GPIO_INTR_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_STATUSn_INI(n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK                              0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT                              0x0

#define HWIO_TLMM_CLK_GATE_EN_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00116000)
#define HWIO_TLMM_CLK_GATE_EN_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00116000)
#define HWIO_TLMM_CLK_GATE_EN_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00116000)
#define HWIO_TLMM_CLK_GATE_EN_RMSK                                                0x7
#define HWIO_TLMM_CLK_GATE_EN_IN          \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, HWIO_TLMM_CLK_GATE_EN_RMSK)
#define HWIO_TLMM_CLK_GATE_EN_INM(m)      \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, m)
#define HWIO_TLMM_CLK_GATE_EN_OUT(v)      \
        out_dword(HWIO_TLMM_CLK_GATE_EN_ADDR,v)
#define HWIO_TLMM_CLK_GATE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_CLK_GATE_EN_ADDR,m,v,HWIO_TLMM_CLK_GATE_EN_IN)
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_BMSK                                    0x4
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_SHFT                                    0x2
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_DISABLE_FVAL                            0x0
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_ENABLE_FVAL                             0x1
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_BMSK                                0x2
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_SHFT                                0x1
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_DISABLE_FVAL                        0x0
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_ENABLE_FVAL                         0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_BMSK                                   0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_SHFT                                   0x0
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_DISABLE_FVAL                           0x0
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_ENABLE_FVAL                            0x1

#define HWIO_TLMM_IE_CTRL_DISABLE_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00116004)
#define HWIO_TLMM_IE_CTRL_DISABLE_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00116004)
#define HWIO_TLMM_IE_CTRL_DISABLE_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00116004)
#define HWIO_TLMM_IE_CTRL_DISABLE_RMSK                                            0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IN          \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, HWIO_TLMM_IE_CTRL_DISABLE_RMSK)
#define HWIO_TLMM_IE_CTRL_DISABLE_INM(m)      \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, m)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUT(v)      \
        out_dword(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,v)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,m,v,HWIO_TLMM_IE_CTRL_DISABLE_IN)
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_BMSK                            0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_SHFT                            0x0
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_ENABLE_FVAL                     0x0
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_DISABLE_FVAL                    0x1

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR                                 (TLMM_CSR_REG_BASE      + 0x00116008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_PHYS                                 (TLMM_CSR_REG_BASE_PHYS + 0x00116008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x00116008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK                                 0xffffffff
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_BMSK                         0x80000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_SHFT                               0x1f
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_78_BMSK                         0x40000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_78_SHFT                               0x1e
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_78_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_78_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_BMSK                         0x20000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_SHFT                               0x1d
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_BMSK                         0x10000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_SHFT                               0x1c
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_BMSK                          0x8000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_SHFT                               0x1b
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_BMSK                          0x4000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_SHFT                               0x1a
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_BMSK                          0x2000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_SHFT                               0x19
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_63_BMSK                          0x1000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_63_SHFT                               0x18
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_63_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_63_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_BMSK                           0x800000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_SHFT                               0x17
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_BMSK                           0x400000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_SHFT                               0x16
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_BMSK                           0x200000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_SHFT                               0x15
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_60_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_BMSK                           0x100000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_SHFT                               0x14
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_BMSK                            0x80000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_SHFT                               0x13
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_58_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_57_BMSK                            0x40000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_57_SHFT                               0x12
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_57_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_57_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_BMSK                            0x20000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_SHFT                               0x11
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_56_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_BMSK                            0x10000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_SHFT                               0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_53_BMSK                             0x8000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_53_SHFT                                0xf
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_53_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_53_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_BMSK                             0x4000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_SHFT                                0xe
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_BMSK                             0x2000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_SHFT                                0xd
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_BMSK                             0x1000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_SHFT                                0xc
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_40_BMSK                              0x800
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_40_SHFT                                0xb
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_40_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_40_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_38_BMSK                              0x400
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_38_SHFT                                0xa
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_38_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_38_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_BMSK                              0x200
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_SHFT                                0x9
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_36_BMSK                              0x100
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_36_SHFT                                0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_36_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_36_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_BMSK                               0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_SHFT                                0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_26_BMSK                               0x40
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_26_SHFT                                0x6
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_26_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_26_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_BMSK                               0x20
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_SHFT                                0x5
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_22_BMSK                               0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_22_SHFT                                0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_22_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_22_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_11_BMSK                                0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_11_SHFT                                0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_11_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_11_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_BMSK                                 0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_SHFT                                 0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_DISABLE_FVAL                         0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_ENABLE_FVAL                          0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_BMSK                                 0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_SHFT                                 0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_DISABLE_FVAL                         0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_ENABLE_FVAL                          0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_BMSK                                 0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_SHFT                                 0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_DISABLE_FVAL                         0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_ENABLE_FVAL                          0x1

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR                                 (TLMM_CSR_REG_BASE      + 0x0011600c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_PHYS                                 (TLMM_CSR_REG_BASE_PHYS + 0x0011600c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x0011600c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_RMSK                                 0xffffffff
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_1_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_1_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_145_BMSK                        0x80000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_145_SHFT                              0x1f
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_145_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_145_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_133_BMSK                        0x40000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_133_SHFT                              0x1e
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_133_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_133_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_132_BMSK                        0x20000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_132_SHFT                              0x1d
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_132_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_132_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_131_BMSK                        0x10000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_131_SHFT                              0x1c
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_131_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_131_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_129_BMSK                         0x8000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_129_SHFT                              0x1b
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_129_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_129_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_127_BMSK                         0x4000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_127_SHFT                              0x1a
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_127_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_127_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_126_BMSK                         0x2000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_126_SHFT                              0x19
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_126_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_126_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_125_BMSK                         0x1000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_125_SHFT                              0x18
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_125_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_125_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_124_BMSK                          0x800000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_124_SHFT                              0x17
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_124_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_124_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_123_BMSK                          0x400000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_123_SHFT                              0x16
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_123_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_123_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_122_BMSK                          0x200000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_122_SHFT                              0x15
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_122_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_122_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_121_BMSK                          0x100000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_121_SHFT                              0x14
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_121_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_121_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_120_BMSK                           0x80000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_120_SHFT                              0x13
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_120_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_120_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_119_BMSK                           0x40000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_119_SHFT                              0x12
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_119_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_119_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_118_BMSK                           0x20000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_118_SHFT                              0x11
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_118_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_118_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_117_BMSK                           0x10000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_117_SHFT                              0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_117_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_117_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_116_BMSK                            0x8000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_116_SHFT                               0xf
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_116_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_116_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_115_BMSK                            0x4000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_115_SHFT                               0xe
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_115_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_115_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_113_BMSK                            0x2000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_113_SHFT                               0xd
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_113_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_113_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_112_BMSK                            0x1000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_112_SHFT                               0xc
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_112_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_112_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_110_BMSK                             0x800
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_110_SHFT                               0xb
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_110_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_110_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_108_BMSK                             0x400
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_108_SHFT                               0xa
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_108_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_108_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_106_BMSK                             0x200
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_106_SHFT                               0x9
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_106_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_106_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_104_BMSK                             0x100
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_104_SHFT                               0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_104_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_104_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_101_BMSK                              0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_101_SHFT                               0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_101_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_101_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_97_BMSK                               0x40
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_97_SHFT                                0x6
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_97_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_97_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_BMSK                               0x20
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_SHFT                                0x5
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_BMSK                               0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_SHFT                                0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_91_BMSK                                0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_91_SHFT                                0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_91_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_91_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_BMSK                                0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_SHFT                                0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_BMSK                                0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_SHFT                                0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_ENABLE_FVAL                         0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_80_BMSK                                0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_80_SHFT                                0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_80_DISABLE_FVAL                        0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_80_ENABLE_FVAL                         0x1

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_ADDR                                 (TLMM_CSR_REG_BASE      + 0x00116010)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_PHYS                                 (TLMM_CSR_REG_BASE_PHYS + 0x00116010)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_OFFS                                 (TLMM_CSR_REG_BASE_OFFS + 0x00116010)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_RMSK                                       0x9f
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_2_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_2_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_2_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_2_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_2_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_2_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SRST_N_BMSK                                0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SRST_N_SHFT                                 0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SRST_N_DISABLE_FVAL                         0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SRST_N_ENABLE_FVAL                          0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_CMD_BMSK                              0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_CMD_SHFT                               0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_CMD_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_CMD_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_3_BMSK                            0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_3_SHFT                            0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_3_DISABLE_FVAL                    0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_3_ENABLE_FVAL                     0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_1_BMSK                            0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_1_SHFT                            0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_1_DISABLE_FVAL                    0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC2_DATA_1_ENABLE_FVAL                     0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_3_BMSK                            0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_3_SHFT                            0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_3_DISABLE_FVAL                    0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_3_ENABLE_FVAL                     0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_1_BMSK                            0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_1_SHFT                            0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_1_DISABLE_FVAL                    0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_2_SDC1_DATA_1_ENABLE_FVAL                     0x1

#define HWIO_TLMM_INT_JTAG_CTL_ADDR                                        (TLMM_CSR_REG_BASE      + 0x00141000)
#define HWIO_TLMM_INT_JTAG_CTL_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x00141000)
#define HWIO_TLMM_INT_JTAG_CTL_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x00141000)
#define HWIO_TLMM_INT_JTAG_CTL_RMSK                                               0xf
#define HWIO_TLMM_INT_JTAG_CTL_IN          \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, HWIO_TLMM_INT_JTAG_CTL_RMSK)
#define HWIO_TLMM_INT_JTAG_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, m)
#define HWIO_TLMM_INT_JTAG_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_INT_JTAG_CTL_ADDR,v)
#define HWIO_TLMM_INT_JTAG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_INT_JTAG_CTL_ADDR,m,v,HWIO_TLMM_INT_JTAG_CTL_IN)
#define HWIO_TLMM_INT_JTAG_CTL_HMSS_TAP_ENA_BMSK                                  0x8
#define HWIO_TLMM_INT_JTAG_CTL_HMSS_TAP_ENA_SHFT                                  0x3
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_BMSK                                  0x4
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_SHFT                                  0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_BMSK                                   0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_SHFT                                   0x1
#define HWIO_TLMM_INT_JTAG_CTL_MSM_TAP_ENA_BMSK                                   0x1
#define HWIO_TLMM_INT_JTAG_CTL_MSM_TAP_ENA_SHFT                                   0x0

#define HWIO_TLMM_ETM_MODE_ADDR                                            (TLMM_CSR_REG_BASE      + 0x00141004)
#define HWIO_TLMM_ETM_MODE_PHYS                                            (TLMM_CSR_REG_BASE_PHYS + 0x00141004)
#define HWIO_TLMM_ETM_MODE_OFFS                                            (TLMM_CSR_REG_BASE_OFFS + 0x00141004)
#define HWIO_TLMM_ETM_MODE_RMSK                                                   0x3
#define HWIO_TLMM_ETM_MODE_IN          \
        in_dword_masked(HWIO_TLMM_ETM_MODE_ADDR, HWIO_TLMM_ETM_MODE_RMSK)
#define HWIO_TLMM_ETM_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_ETM_MODE_ADDR, m)
#define HWIO_TLMM_ETM_MODE_OUT(v)      \
        out_dword(HWIO_TLMM_ETM_MODE_ADDR,v)
#define HWIO_TLMM_ETM_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_ETM_MODE_ADDR,m,v,HWIO_TLMM_ETM_MODE_IN)
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_BMSK                                   0x3
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_SHFT                                   0x0
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_MODE0_FVAL                             0x0
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_MODE1_FVAL                             0x1
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_MODE2_FVAL                             0x2
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_MODE3_FVAL                             0x3

#define HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00141008)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00141008)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00141008)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK                                            0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_IN          \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_INM(m)      \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, m)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUT(v)      \
        out_dword(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,v)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,m,v,HWIO_TLMM_DBG_BUS_OUT_SEL_IN)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_BMSK                                   0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_SHFT                                   0x0
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_A_FVAL                            0x0
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_B_FVAL                            0x1
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_C_FVAL                            0x2
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_D_FVAL                            0x3

#define HWIO_TLMM_CHIP_MODE_ADDR                                           (TLMM_CSR_REG_BASE      + 0x0014100c)
#define HWIO_TLMM_CHIP_MODE_PHYS                                           (TLMM_CSR_REG_BASE_PHYS + 0x0014100c)
#define HWIO_TLMM_CHIP_MODE_OFFS                                           (TLMM_CSR_REG_BASE_OFFS + 0x0014100c)
#define HWIO_TLMM_CHIP_MODE_RMSK                                                  0x3
#define HWIO_TLMM_CHIP_MODE_IN          \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, HWIO_TLMM_CHIP_MODE_RMSK)
#define HWIO_TLMM_CHIP_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, m)
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_BMSK                                        0x2
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_SHFT                                        0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_BMSK                                        0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_SHFT                                        0x0

#define HWIO_TLMM_HW_REVISION_NUMBER_ADDR                                  (TLMM_CSR_REG_BASE      + 0x00141010)
#define HWIO_TLMM_HW_REVISION_NUMBER_PHYS                                  (TLMM_CSR_REG_BASE_PHYS + 0x00141010)
#define HWIO_TLMM_HW_REVISION_NUMBER_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x00141010)
#define HWIO_TLMM_HW_REVISION_NUMBER_RMSK                                  0xffffffff
#define HWIO_TLMM_HW_REVISION_NUMBER_IN          \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, HWIO_TLMM_HW_REVISION_NUMBER_RMSK)
#define HWIO_TLMM_HW_REVISION_NUMBER_INM(m)      \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_BMSK                       0xf0000000
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_SHFT                             0x1c
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_FIRST_TAPE_OUT_FVAL               0x0
#define HWIO_TLMM_HW_REVISION_NUMBER_PRODUCT_DEVICE_ID_BMSK                 0xffff000
#define HWIO_TLMM_HW_REVISION_NUMBER_PRODUCT_DEVICE_ID_SHFT                       0xc
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_BMSK                       0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_SHFT                         0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_BMSK                               0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_SHFT                               0x0

#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR                               (TLMM_CSR_REG_BASE      + 0x00141014)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_PHYS                               (TLMM_CSR_REG_BASE_PHYS + 0x00141014)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x00141014)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_RMSK                                      0x1
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_IN          \
        in_dword_masked(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR, HWIO_TLMM_PERIPH_CHAR_TEST_MODE_RMSK)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR, m)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OUT(v)      \
        out_dword(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR,v)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PERIPH_CHAR_TEST_MODE_ADDR,m,v,HWIO_TLMM_PERIPH_CHAR_TEST_MODE_IN)
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_BMSK                       0x1
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_SHFT                       0x0
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_DISABLE_FVAL               0x0
#define HWIO_TLMM_PERIPH_CHAR_TEST_MODE_CHAR_TEST_MODE_ENABLE_FVAL                0x1

#define HWIO_TLMM_MODE_PULL_CTL_ADDR                                       (TLMM_CSR_REG_BASE      + 0x0012b000)
#define HWIO_TLMM_MODE_PULL_CTL_PHYS                                       (TLMM_CSR_REG_BASE_PHYS + 0x0012b000)
#define HWIO_TLMM_MODE_PULL_CTL_OFFS                                       (TLMM_CSR_REG_BASE_OFFS + 0x0012b000)
#define HWIO_TLMM_MODE_PULL_CTL_RMSK                                              0xf
#define HWIO_TLMM_MODE_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, HWIO_TLMM_MODE_PULL_CTL_RMSK)
#define HWIO_TLMM_MODE_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, m)
#define HWIO_TLMM_MODE_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_MODE_PULL_CTL_ADDR,v)
#define HWIO_TLMM_MODE_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MODE_PULL_CTL_ADDR,m,v,HWIO_TLMM_MODE_PULL_CTL_IN)
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_BMSK                                  0xc
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_SHFT                                  0x2
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_BMSK                                  0x3
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_SHFT                                  0x0

#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR                                  (TLMM_CSR_REG_BASE      + 0x0012c000)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_PHYS                                  (TLMM_CSR_REG_BASE_PHYS + 0x0012c000)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x0012c000)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_RMSK                                     0x1ffff
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR, HWIO_TLMM_SDC1_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_SDC1_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_RCLK_PULL_BMSK                      0x18000
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_RCLK_PULL_SHFT                          0xf
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_PULL_BMSK                        0x6000
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_PULL_SHFT                           0xd
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_PULL_BMSK                        0x1800
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_PULL_SHFT                           0xb
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_PULL_BMSK                        0x600
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_PULL_SHFT                          0x9
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_HDRV_BMSK                         0x1c0
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_HDRV_SHFT                           0x6
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_HDRV_BMSK                          0x38
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_HDRV_SHFT                           0x3
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_HDRV_BMSK                          0x7
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_HDRV_SHFT                          0x0

#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR                                  (TLMM_CSR_REG_BASE      + 0x0012d000)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_PHYS                                  (TLMM_CSR_REG_BASE_PHYS + 0x0012d000)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x0012d000)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_RMSK                                      0xffff
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, HWIO_TLMM_SDC2_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_SDC2_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_PULL_BMSK                        0xc000
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_PULL_SHFT                           0xe
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_BMSK                         0x2000
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_SHFT                            0xd
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_DISABLE_FVAL                    0x0
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_ENABLE_FVAL                     0x1
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_PULL_BMSK                        0x1800
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_PULL_SHFT                           0xb
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_PULL_BMSK                        0x600
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_PULL_SHFT                          0x9
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_HDRV_BMSK                         0x1c0
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_HDRV_SHFT                           0x6
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_HDRV_BMSK                          0x38
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_HDRV_SHFT                           0x3
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_HDRV_BMSK                          0x7
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_HDRV_SHFT                          0x0

#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_ADDR                               (TLMM_CSR_REG_BASE      + 0x0012e000)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_PHYS                               (TLMM_CSR_REG_BASE_PHYS + 0x0012e000)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x0012e000)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RMSK                                   0xffff
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_RESERVE_HDRV_PULL_CTL_ADDR, HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_RESERVE_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_RESERVE_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_RESERVE_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_RESERVE_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CLK_PULL_BMSK                  0xc000
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CLK_PULL_SHFT                     0xe
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_HYS_CTL_BMSK                   0x2000
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_HYS_CTL_SHFT                      0xd
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_HYS_CTL_DISABLE_FVAL              0x0
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_HYS_CTL_ENABLE_FVAL               0x1
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CMD_PULL_BMSK                  0x1800
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CMD_PULL_SHFT                     0xb
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_DATA_PULL_BMSK                  0x600
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_DATA_PULL_SHFT                    0x9
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CLK_HDRV_BMSK                   0x1c0
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CLK_HDRV_SHFT                     0x6
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CMD_HDRV_BMSK                    0x38
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_CMD_HDRV_SHFT                     0x3
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_DATA_HDRV_BMSK                    0x7
#define HWIO_TLMM_RESERVE_HDRV_PULL_CTL_RESERVE_DATA_HDRV_SHFT                    0x0

#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR                                  (TLMM_CSR_REG_BASE      + 0x0012f000)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PHYS                                  (TLMM_CSR_REG_BASE_PHYS + 0x0012f000)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x0012f000)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_RMSK                                    0xffffff
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR, HWIO_TLMM_PMIC_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_PMIC_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_HIHYS_EN_DATA_BMSK            0x800000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_HIHYS_EN_DATA_SHFT                0x17
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_HIHYS_EN_CLK_BMSK             0x400000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_HIHYS_EN_CLK_SHFT                 0x16
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_BMSK              0x300000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_SHFT                  0x14
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_GPIO_MODE_FVAL         0x0
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_RFFE_MODE_FVAL         0x1
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_SLIMBUS_MODE_FVAL        0x2
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SR_CTL_SPMI_MODE_FVAL         0x3
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_BMSK                0xc0000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_SHFT                   0x12
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_GPIO_MODE_FVAL          0x0
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_RFFE_MODE_FVAL          0x1
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_SLIMBUS_MODE_FVAL        0x2
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SR_CTL_SPMI_MODE_FVAL          0x3
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SEN_EN_BMSK               0x20000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SEN_EN_SHFT                  0x11
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SEN_EN_BMSK                0x10000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SEN_EN_SHFT                   0x10
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_PULL_BMSK                  0xc000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_PULL_SHFT                     0xe
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_PULL_BMSK                   0x3000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_PULL_SHFT                      0xc
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PSHOLD_HDRV_BMSK                           0xe00
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PSHOLD_HDRV_SHFT                             0x9
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_CXO_EN_HDRV_BMSK                           0x1c0
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_CXO_EN_HDRV_SHFT                             0x6
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_HDRV_BMSK                    0x38
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_HDRV_SHFT                     0x3
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_HDRV_BMSK                      0x7
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_HDRV_SHFT                      0x0

#define HWIO_TLMM_JTAG_HDRV_CTL_ADDR                                       (TLMM_CSR_REG_BASE      + 0x00130000)
#define HWIO_TLMM_JTAG_HDRV_CTL_PHYS                                       (TLMM_CSR_REG_BASE_PHYS + 0x00130000)
#define HWIO_TLMM_JTAG_HDRV_CTL_OFFS                                       (TLMM_CSR_REG_BASE_OFFS + 0x00130000)
#define HWIO_TLMM_JTAG_HDRV_CTL_RMSK                                            0x3ff
#define HWIO_TLMM_JTAG_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, HWIO_TLMM_JTAG_HDRV_CTL_RMSK)
#define HWIO_TLMM_JTAG_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,m,v,HWIO_TLMM_JTAG_HDRV_CTL_IN)
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_BMSK                                   0x300
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_SHFT                                     0x8
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_BMSK                                    0xc0
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_SHFT                                     0x6
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_BMSK                                    0x38
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_SHFT                                     0x3
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_BMSK                                     0x7
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_SHFT                                     0x0

#define HWIO_TLMM_RESOUT_HDRV_CTL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00131000)
#define HWIO_TLMM_RESOUT_HDRV_CTL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00131000)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00131000)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RMSK                                            0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, HWIO_TLMM_RESOUT_HDRV_CTL_RMSK)
#define HWIO_TLMM_RESOUT_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,m,v,HWIO_TLMM_RESOUT_HDRV_CTL_IN)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_BMSK                              0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_SHFT                              0x0

#define HWIO_TLMM_GPIO_GS_I2C_CTL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00132000)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00132000)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00132000)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_RMSK                                            0x3
#define HWIO_TLMM_GPIO_GS_I2C_CTL_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_GS_I2C_CTL_ADDR, HWIO_TLMM_GPIO_GS_I2C_CTL_RMSK)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_GS_I2C_CTL_ADDR, m)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_GS_I2C_CTL_ADDR,v)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_GS_I2C_CTL_ADDR,m,v,HWIO_TLMM_GPIO_GS_I2C_CTL_IN)
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_BMSK                                       0x3
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_SHFT                                       0x0
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_GPIO_MODE_FVAL                             0x0
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_GS_I2C_MODE_FVAL                           0x1
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_FS_I2C_MODE_FVAL                           0x2
#define HWIO_TLMM_GPIO_GS_I2C_CTL_MODE_GS_I2C_HIGH_LOAD_MODE_FVAL                 0x3

#define HWIO_TLMM_CCI_GS_I2C_CTL_ADDR                                      (TLMM_CSR_REG_BASE      + 0x00133000)
#define HWIO_TLMM_CCI_GS_I2C_CTL_PHYS                                      (TLMM_CSR_REG_BASE_PHYS + 0x00133000)
#define HWIO_TLMM_CCI_GS_I2C_CTL_OFFS                                      (TLMM_CSR_REG_BASE_OFFS + 0x00133000)
#define HWIO_TLMM_CCI_GS_I2C_CTL_RMSK                                             0xf
#define HWIO_TLMM_CCI_GS_I2C_CTL_IN          \
        in_dword_masked(HWIO_TLMM_CCI_GS_I2C_CTL_ADDR, HWIO_TLMM_CCI_GS_I2C_CTL_RMSK)
#define HWIO_TLMM_CCI_GS_I2C_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_CCI_GS_I2C_CTL_ADDR, m)
#define HWIO_TLMM_CCI_GS_I2C_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_CCI_GS_I2C_CTL_ADDR,v)
#define HWIO_TLMM_CCI_GS_I2C_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_CCI_GS_I2C_CTL_ADDR,m,v,HWIO_TLMM_CCI_GS_I2C_CTL_IN)
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_BMSK                                   0xc
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_SHFT                                   0x2
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_GPIO_MODE_FVAL                         0x0
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_GS_I2C_MODE_FVAL                       0x1
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_FS_I2C_MODE_FVAL                       0x2
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI1_MODE_GS_I2C_HIGH_LOAD_MODE_FVAL             0x3
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_BMSK                                   0x3
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_SHFT                                   0x0
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_GPIO_MODE_FVAL                         0x0
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_GS_I2C_MODE_FVAL                       0x1
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_FS_I2C_MODE_FVAL                       0x2
#define HWIO_TLMM_CCI_GS_I2C_CTL_CCI0_MODE_GS_I2C_HIGH_LOAD_MODE_FVAL             0x3

#define HWIO_TLMM_LPASS_SLIMBUS_CTL_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00134000)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_PHYS                                   (TLMM_CSR_REG_BASE_PHYS + 0x00134000)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00134000)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_RMSK                                          0x7
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_IN          \
        in_dword_masked(HWIO_TLMM_LPASS_SLIMBUS_CTL_ADDR, HWIO_TLMM_LPASS_SLIMBUS_CTL_RMSK)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_LPASS_SLIMBUS_CTL_ADDR, m)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_LPASS_SLIMBUS_CTL_ADDR,v)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_LPASS_SLIMBUS_CTL_ADDR,m,v,HWIO_TLMM_LPASS_SLIMBUS_CTL_IN)
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_SR_SEN_EN_BMSK                                0x4
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_SR_SEN_EN_SHFT                                0x2
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_SR_CTL_EN_BMSK                                0x3
#define HWIO_TLMM_LPASS_SLIMBUS_CTL_SR_CTL_EN_SHFT                                0x0

#define HWIO_TLMM_BTFM_SLIMBUS_CTL_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00135000)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00135000)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00135000)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_RMSK                                           0x3
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_IN          \
        in_dword_masked(HWIO_TLMM_BTFM_SLIMBUS_CTL_ADDR, HWIO_TLMM_BTFM_SLIMBUS_CTL_RMSK)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_BTFM_SLIMBUS_CTL_ADDR, m)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_BTFM_SLIMBUS_CTL_ADDR,v)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_BTFM_SLIMBUS_CTL_ADDR,m,v,HWIO_TLMM_BTFM_SLIMBUS_CTL_IN)
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_SR_CTL_EN_BMSK                                 0x3
#define HWIO_TLMM_BTFM_SLIMBUS_CTL_SR_CTL_EN_SHFT                                 0x0

#define HWIO_TLMM_UFS_REF_CLK_CTL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00136000)
#define HWIO_TLMM_UFS_REF_CLK_CTL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00136000)
#define HWIO_TLMM_UFS_REF_CLK_CTL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00136000)
#define HWIO_TLMM_UFS_REF_CLK_CTL_RMSK                                           0x3f
#define HWIO_TLMM_UFS_REF_CLK_CTL_IN          \
        in_dword_masked(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR, HWIO_TLMM_UFS_REF_CLK_CTL_RMSK)
#define HWIO_TLMM_UFS_REF_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR, m)
#define HWIO_TLMM_UFS_REF_CLK_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR,v)
#define HWIO_TLMM_UFS_REF_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR,m,v,HWIO_TLMM_UFS_REF_CLK_CTL_IN)
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_EN_BMSK                            0x20
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_EN_SHFT                             0x5
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_PULL_BMSK                          0x18
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_PULL_SHFT                           0x3
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_HDRV_BMSK                           0x7
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_HDRV_SHFT                           0x0

#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_ADDR                           (TLMM_CSR_REG_BASE      + 0x00137000)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_PHYS                           (TLMM_CSR_REG_BASE_PHYS + 0x00137000)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_OFFS                           (TLMM_CSR_REG_BASE_OFFS + 0x00137000)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_RMSK                                  0x7
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_ADDR, HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_DDR_RESET_N_HDRV_BMSK                 0x7
#define HWIO_TLMM_DDR_RESET_N_HDRV_PULL_CTL_DDR_RESET_N_HDRV_SHFT                 0x0

#define HWIO_TLMM_UFS_RESET_CTL_ADDR                                       (TLMM_CSR_REG_BASE      + 0x00138000)
#define HWIO_TLMM_UFS_RESET_CTL_PHYS                                       (TLMM_CSR_REG_BASE_PHYS + 0x00138000)
#define HWIO_TLMM_UFS_RESET_CTL_OFFS                                       (TLMM_CSR_REG_BASE_OFFS + 0x00138000)
#define HWIO_TLMM_UFS_RESET_CTL_RMSK                                             0x3f
#define HWIO_TLMM_UFS_RESET_CTL_IN          \
        in_dword_masked(HWIO_TLMM_UFS_RESET_CTL_ADDR, HWIO_TLMM_UFS_RESET_CTL_RMSK)
#define HWIO_TLMM_UFS_RESET_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_UFS_RESET_CTL_ADDR, m)
#define HWIO_TLMM_UFS_RESET_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_UFS_RESET_CTL_ADDR,v)
#define HWIO_TLMM_UFS_RESET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_UFS_RESET_CTL_ADDR,m,v,HWIO_TLMM_UFS_RESET_CTL_IN)
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_EN_BMSK                                0x20
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_EN_SHFT                                 0x5
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_BMSK                              0x18
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_SHFT                               0x3
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_BMSK                               0x7
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_SHFT                               0x0

#define HWIO_TLMM_SPARE_ADDR                                               (TLMM_CSR_REG_BASE      + 0x00139000)
#define HWIO_TLMM_SPARE_PHYS                                               (TLMM_CSR_REG_BASE_PHYS + 0x00139000)
#define HWIO_TLMM_SPARE_OFFS                                               (TLMM_CSR_REG_BASE_OFFS + 0x00139000)
#define HWIO_TLMM_SPARE_RMSK                                               0xffffffff
#define HWIO_TLMM_SPARE_IN          \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, HWIO_TLMM_SPARE_RMSK)
#define HWIO_TLMM_SPARE_INM(m)      \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, m)
#define HWIO_TLMM_SPARE_OUT(v)      \
        out_dword(HWIO_TLMM_SPARE_ADDR,v)
#define HWIO_TLMM_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SPARE_ADDR,m,v,HWIO_TLMM_SPARE_IN)
#define HWIO_TLMM_SPARE_SPARE_BMSK                                         0xffffff00
#define HWIO_TLMM_SPARE_SPARE_SHFT                                                0x8
#define HWIO_TLMM_SPARE_MISC_BMSK                                                0xff
#define HWIO_TLMM_SPARE_MISC_SHFT                                                 0x0

#define HWIO_TLMM_SPARE1_ADDR                                              (TLMM_CSR_REG_BASE      + 0x0013a000)
#define HWIO_TLMM_SPARE1_PHYS                                              (TLMM_CSR_REG_BASE_PHYS + 0x0013a000)
#define HWIO_TLMM_SPARE1_OFFS                                              (TLMM_CSR_REG_BASE_OFFS + 0x0013a000)
#define HWIO_TLMM_SPARE1_RMSK                                              0xffffffff
#define HWIO_TLMM_SPARE1_IN          \
        in_dword_masked(HWIO_TLMM_SPARE1_ADDR, HWIO_TLMM_SPARE1_RMSK)
#define HWIO_TLMM_SPARE1_INM(m)      \
        in_dword_masked(HWIO_TLMM_SPARE1_ADDR, m)
#define HWIO_TLMM_SPARE1_OUT(v)      \
        out_dword(HWIO_TLMM_SPARE1_ADDR,v)
#define HWIO_TLMM_SPARE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SPARE1_ADDR,m,v,HWIO_TLMM_SPARE1_IN)
#define HWIO_TLMM_SPARE1_SPARE_BMSK                                        0xffffff00
#define HWIO_TLMM_SPARE1_SPARE_SHFT                                               0x8
#define HWIO_TLMM_SPARE1_MISC_BMSK                                               0xff
#define HWIO_TLMM_SPARE1_MISC_SHFT                                                0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n)                       (TLMM_CSR_REG_BASE      + 0x00123000 + 0x3E8 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_PHYS(n)                       (TLMM_CSR_REG_BASE_PHYS + 0x00123000 + 0x3E8 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OFFS(n)                       (TLMM_CSR_REG_BASE_OFFS + 0x00123000 + 0x3E8 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_RMSK                               0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_MAXn                                   1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_BMSK                      0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_SHFT                        0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_POLARITY_0_FVAL             0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_POLARITY_1_FVAL             0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_BMSK                       0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_SHFT                        0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n)                       (TLMM_CSR_REG_BASE      + 0x00122000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_PHYS(n)                       (TLMM_CSR_REG_BASE_PHYS + 0x00122000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OFFS(n)                       (TLMM_CSR_REG_BASE_OFFS + 0x00122000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_RMSK                               0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_MAXn                                   5
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_BMSK                      0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_SHFT                        0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_POLARITY_0_FVAL             0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_POLARITY_1_FVAL             0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_GPIO_SEL_BMSK                       0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_GPIO_SEL_SHFT                        0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n)                           (TLMM_CSR_REG_BASE      + 0x00121000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_PHYS(n)                           (TLMM_CSR_REG_BASE_PHYS + 0x00121000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OFFS(n)                           (TLMM_CSR_REG_BASE_OFFS + 0x00121000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_RMSK                                   0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_MAXn                                       0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_BMSK                          0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_SHFT                            0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_POLARITY_0_FVAL                 0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_POLARITY_1_FVAL                 0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_GPIO_SEL_BMSK                           0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_GPIO_SEL_SHFT                            0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n)                          (TLMM_CSR_REG_BASE      + 0x00120000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_PHYS(n)                          (TLMM_CSR_REG_BASE_PHYS + 0x00120000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OFFS(n)                          (TLMM_CSR_REG_BASE_OFFS + 0x00120000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_RMSK                                  0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_MAXn                                      7
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_BMSK                         0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_SHFT                           0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_POLARITY_0_FVAL                0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_POLARITY_POLARITY_1_FVAL                0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_BMSK                          0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_HMSS_GPIO_SEL_SHFT                           0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_ADDR(n)                           (TLMM_CSR_REG_BASE      + 0x0011f000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_PHYS(n)                           (TLMM_CSR_REG_BASE_PHYS + 0x0011f000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_OFFS(n)                           (TLMM_CSR_REG_BASE_OFFS + 0x0011f000 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_RMSK                                   0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_MAXn                                       1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_POLARITY_BMSK                          0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_POLARITY_SHFT                            0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_POLARITY_POLARITY_0_FVAL                 0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_POLARITY_POLARITY_1_FVAL                 0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_GPIO_SEL_BMSK                           0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_GSS_GPIO_SEL_SHFT                            0x0


#endif /* __HALGPIOINTHWIO_H__ */
