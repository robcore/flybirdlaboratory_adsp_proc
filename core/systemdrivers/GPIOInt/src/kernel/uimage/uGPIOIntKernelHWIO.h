#ifndef __UGPIOINTHWIO_H__
#define __UGPIOINTHWIO_H__
/*
===========================================================================
*/
/**
  @file HALgpiointHWIO.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    TLMM
    TLMM_TLMM

  'Include' filters applied: GPIO_INTR DIR_CONN 
  'Exclude' filters applied: ACR 
*/
/*
  ===========================================================================

  Copyright (c) 2011 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/src/kernel/uimage/uGPIOIntKernelHWIO.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: TLMM_TLMM
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * MODULE: TLMM_CSR
 *--------------------------------------------------------------------------*/

#define TLMM_CSR_REG_BASE                                                (TLMM_BASE      + 0x00010000)
#define TLMM_CSR_REG_BASE_PHYS                                           (TLMM_BASE_PHYS + 0x00010000)
#define TLMM_CSR_REG_BASE_OFFS                                           0x00010000

#define HWIO_TLMM_GPIO_CFGn_ADDR(n)                                      (TLMM_CSR_REG_BASE      + 0x00001000 + 0x10 * (n))
#define HWIO_TLMM_GPIO_CFGn_PHYS(n)                                      (TLMM_CSR_REG_BASE_PHYS + 0x00001000 + 0x10 * (n))
#define HWIO_TLMM_GPIO_CFGn_OFFS(n)                                      (TLMM_CSR_REG_BASE_OFFS + 0x00001000 + 0x10 * (n))
#define HWIO_TLMM_GPIO_CFGn_RMSK                                              0x7ff
#define HWIO_TLMM_GPIO_CFGn_MAXn                                                145
#define HWIO_TLMM_GPIO_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), HWIO_TLMM_GPIO_CFGn_RMSK)
#define HWIO_TLMM_GPIO_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_CFGn_INI(n))
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_BMSK                                0x400
#define HWIO_TLMM_GPIO_CFGn_GPIO_HIHYS_EN_SHFT                                  0xa
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_BMSK                                      0x200
#define HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT                                        0x9
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_BMSK                                 0x1c0
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT                                   0x6
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_2_MA_FVAL                          0x0
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_4_MA_FVAL                          0x1
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_6_MA_FVAL                          0x2
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_8_MA_FVAL                          0x3
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_10_MA_FVAL                         0x4
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_12_MA_FVAL                         0x5
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_14_MA_FVAL                         0x6
#define HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_DRV_16_MA_FVAL                         0x7
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_BMSK                                      0x3c
#define HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT                                       0x2
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_BMSK                                      0x3
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT                                      0x0
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_NO_PULL_FVAL                              0x0
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_PULL_DOWN_FVAL                            0x1
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_KEEPER_FVAL                               0x2
#define HWIO_TLMM_GPIO_CFGn_GPIO_PULL_PULL_UP_FVAL                              0x3

#define HWIO_TLMM_GPIO_IN_OUTn_ADDR(n)                                   (TLMM_CSR_REG_BASE      + 0x00001004 + 0x10 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_PHYS(n)                                   (TLMM_CSR_REG_BASE_PHYS + 0x00001004 + 0x10 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_OFFS(n)                                   (TLMM_CSR_REG_BASE_OFFS + 0x00001004 + 0x10 * (n))
#define HWIO_TLMM_GPIO_IN_OUTn_RMSK                                             0x3
#define HWIO_TLMM_GPIO_IN_OUTn_MAXn                                             145
#define HWIO_TLMM_GPIO_IN_OUTn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), HWIO_TLMM_GPIO_IN_OUTn_RMSK)
#define HWIO_TLMM_GPIO_IN_OUTn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),val)
#define HWIO_TLMM_GPIO_IN_OUTn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_IN_OUTn_ADDR(n),mask,val,HWIO_TLMM_GPIO_IN_OUTn_INI(n))
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK                                    0x2
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT                                    0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_BMSK                                     0x1
#define HWIO_TLMM_GPIO_IN_OUTn_GPIO_IN_SHFT                                     0x0

#define HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n)                                 (TLMM_CSR_REG_BASE      + 0x00001008 + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_PHYS(n)                                 (TLMM_CSR_REG_BASE_PHYS + 0x00001008 + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_OFFS(n)                                 (TLMM_CSR_REG_BASE_OFFS + 0x00001008 + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_CFGn_RMSK                                         0x1ff
#define HWIO_TLMM_GPIO_INTR_CFGn_MAXn                                           145
#define HWIO_TLMM_GPIO_INTR_CFGn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), HWIO_TLMM_GPIO_INTR_CFGn_RMSK)
#define HWIO_TLMM_GPIO_INTR_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_CFGn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_CFGn_INI(n))
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_BMSK                             0x100
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_SHFT                               0x8
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_DISABLE_FVAL                       0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_DIR_CONN_EN_ENABLE_FVAL                        0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_BMSK                              0xe0
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SHFT                               0x5
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_WCSS_FVAL                          0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_SENSORS_FVAL                       0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_LPA_DSP_FVAL                       0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_RPM_FVAL                           0x3
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_KPSS_FVAL                          0x4
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_MSS_FVAL                           0x5
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_TZ_FVAL                            0x6
#define HWIO_TLMM_GPIO_INTR_CFGn_TARGET_PROC_NONE_FVAL                          0x7
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_BMSK                       0x10
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_SHFT                        0x4
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_DISABLE_FVAL                0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_RAW_STATUS_EN_ENABLE_FVAL                 0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_BMSK                             0xc
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_SHFT                             0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_LEVEL_FVAL                       0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_POS_EDGE_FVAL                    0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_NEG_EDGE_FVAL                    0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_DECT_CTL_DUAL_EDGE_FVAL                   0x3
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_BMSK                              0x2
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_SHFT                              0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_POLARITY_0_FVAL                   0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_POL_CTL_POLARITY_1_FVAL                   0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_BMSK                               0x1
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_SHFT                               0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_DISABLE_FVAL                       0x0
#define HWIO_TLMM_GPIO_INTR_CFGn_INTR_ENABLE_ENABLE_FVAL                        0x1

#define HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n)                              (TLMM_CSR_REG_BASE      + 0x0000100c + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_PHYS(n)                              (TLMM_CSR_REG_BASE_PHYS + 0x0000100c + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_OFFS(n)                              (TLMM_CSR_REG_BASE_OFFS + 0x0000100c + 0x10 * (n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_RMSK                                        0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_MAXn                                        145
#define HWIO_TLMM_GPIO_INTR_STATUSn_INI(n)        \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), HWIO_TLMM_GPIO_INTR_STATUSn_RMSK)
#define HWIO_TLMM_GPIO_INTR_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n), mask)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTI(n,val)    \
        out_dword(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),val)
#define HWIO_TLMM_GPIO_INTR_STATUSn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_INTR_STATUSn_ADDR(n),mask,val,HWIO_TLMM_GPIO_INTR_STATUSn_INI(n))
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_BMSK                            0x1
#define HWIO_TLMM_GPIO_INTR_STATUSn_INTR_STATUS_SHFT                            0x0

#define HWIO_TLMM_CLK_GATE_EN_ADDR                                       (TLMM_CSR_REG_BASE      + 0x00002000)
#define HWIO_TLMM_CLK_GATE_EN_PHYS                                       (TLMM_CSR_REG_BASE_PHYS + 0x00002000)
#define HWIO_TLMM_CLK_GATE_EN_OFFS                                       (TLMM_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_TLMM_CLK_GATE_EN_RMSK                                              0x7
#define HWIO_TLMM_CLK_GATE_EN_IN          \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, HWIO_TLMM_CLK_GATE_EN_RMSK)
#define HWIO_TLMM_CLK_GATE_EN_INM(m)      \
        in_dword_masked(HWIO_TLMM_CLK_GATE_EN_ADDR, m)
#define HWIO_TLMM_CLK_GATE_EN_OUT(v)      \
        out_dword(HWIO_TLMM_CLK_GATE_EN_ADDR,v)
#define HWIO_TLMM_CLK_GATE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_CLK_GATE_EN_ADDR,m,v,HWIO_TLMM_CLK_GATE_EN_IN)
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_BMSK                                  0x4
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_SHFT                                  0x2
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_DISABLE_FVAL                          0x0
#define HWIO_TLMM_CLK_GATE_EN_AHB_HCLK_EN_ENABLE_FVAL                           0x1
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_BMSK                              0x2
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_SHFT                              0x1
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_DISABLE_FVAL                      0x0
#define HWIO_TLMM_CLK_GATE_EN_SUMMARY_INTR_EN_ENABLE_FVAL                       0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_BMSK                                 0x1
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_SHFT                                 0x0
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_DISABLE_FVAL                         0x0
#define HWIO_TLMM_CLK_GATE_EN_CRIF_READ_EN_ENABLE_FVAL                          0x1

#define HWIO_TLMM_IE_CTRL_DISABLE_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00002004)
#define HWIO_TLMM_IE_CTRL_DISABLE_PHYS                                   (TLMM_CSR_REG_BASE_PHYS + 0x00002004)
#define HWIO_TLMM_IE_CTRL_DISABLE_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00002004)
#define HWIO_TLMM_IE_CTRL_DISABLE_RMSK                                          0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IN          \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, HWIO_TLMM_IE_CTRL_DISABLE_RMSK)
#define HWIO_TLMM_IE_CTRL_DISABLE_INM(m)      \
        in_dword_masked(HWIO_TLMM_IE_CTRL_DISABLE_ADDR, m)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUT(v)      \
        out_dword(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,v)
#define HWIO_TLMM_IE_CTRL_DISABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_IE_CTRL_DISABLE_ADDR,m,v,HWIO_TLMM_IE_CTRL_DISABLE_IN)
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_BMSK                          0x1
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_SHFT                          0x0
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_ENABLE_FVAL                   0x0
#define HWIO_TLMM_IE_CTRL_DISABLE_IE_CTRL_DISABLE_DISABLE_FVAL                  0x1

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR                               (TLMM_CSR_REG_BASE      + 0x00002008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_PHYS                               (TLMM_CSR_REG_BASE_PHYS + 0x00002008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x00002008)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK                               0xffffffff
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_0_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_0_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_0_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_80_BMSK                       0x80000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_80_SHFT                             0x1f
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_80_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_80_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_BMSK                       0x40000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_SHFT                             0x1e
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_79_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_BMSK                       0x20000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_SHFT                             0x1d
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_77_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_75_BMSK                       0x10000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_75_SHFT                             0x1c
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_75_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_75_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_74_BMSK                        0x8000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_74_SHFT                             0x1b
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_74_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_74_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_BMSK                        0x4000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_SHFT                             0x1a
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_73_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_BMSK                        0x2000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_SHFT                             0x19
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_72_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_BMSK                        0x1000000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_SHFT                             0x18
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_71_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_BMSK                         0x800000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_SHFT                             0x17
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_68_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_67_BMSK                         0x400000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_67_SHFT                             0x16
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_67_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_67_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_BMSK                         0x200000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_SHFT                             0x15
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_66_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_65_BMSK                         0x100000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_65_SHFT                             0x14
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_65_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_65_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_BMSK                          0x80000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_SHFT                             0x13
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_64_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_BMSK                          0x40000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_SHFT                             0x12
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_62_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_BMSK                          0x20000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_SHFT                             0x11
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_61_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_BMSK                          0x10000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_SHFT                             0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_59_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_BMSK                           0x8000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_SHFT                              0xf
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_54_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_BMSK                           0x4000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_SHFT                              0xe
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_50_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_BMSK                           0x2000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_SHFT                              0xd
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_46_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_44_BMSK                           0x1000
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_44_SHFT                              0xc
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_44_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_44_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_BMSK                            0x800
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_SHFT                              0xb
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_42_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_BMSK                            0x400
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_SHFT                              0xa
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_37_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_35_BMSK                            0x200
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_35_SHFT                              0x9
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_35_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_35_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_BMSK                            0x100
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_SHFT                              0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_34_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_28_BMSK                             0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_28_SHFT                              0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_28_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_28_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_27_BMSK                             0x40
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_27_SHFT                              0x6
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_27_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_27_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_BMSK                             0x20
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_SHFT                              0x5
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_24_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_20_BMSK                             0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_20_SHFT                              0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_20_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_20_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_18_BMSK                              0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_18_SHFT                              0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_18_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_18_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_BMSK                               0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_SHFT                               0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_9_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_BMSK                               0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_SHFT                               0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_5_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_BMSK                               0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_SHFT                               0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_0_GPIO_1_ENABLE_FVAL                        0x1

#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR                               (TLMM_CSR_REG_BASE      + 0x0000200c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_PHYS                               (TLMM_CSR_REG_BASE_PHYS + 0x0000200c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OFFS                               (TLMM_CSR_REG_BASE_OFFS + 0x0000200c)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_RMSK                                    0xfff
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_IN          \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR, HWIO_TLMM_MPM_WAKEUP_INT_EN_1_RMSK)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_INM(m)      \
        in_dword_masked(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR, m)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OUT(v)      \
        out_dword(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR,v)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MPM_WAKEUP_INT_EN_1_ADDR,m,v,HWIO_TLMM_MPM_WAKEUP_INT_EN_1_IN)
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_3_BMSK                        0x800
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_3_SHFT                          0xb
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_3_DISABLE_FVAL                  0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_3_ENABLE_FVAL                   0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_1_BMSK                        0x400
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_1_SHFT                          0xa
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_1_DISABLE_FVAL                  0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC2_DATA_1_ENABLE_FVAL                   0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_3_BMSK                        0x200
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_3_SHFT                          0x9
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_3_DISABLE_FVAL                  0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_3_ENABLE_FVAL                   0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_1_BMSK                        0x100
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_1_SHFT                          0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_1_DISABLE_FVAL                  0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SDC1_DATA_1_ENABLE_FVAL                   0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SRST_N_BMSK                              0x80
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SRST_N_SHFT                               0x7
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SRST_N_DISABLE_FVAL                       0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_SRST_N_ENABLE_FVAL                        0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_144_BMSK                            0x40
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_144_SHFT                             0x6
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_144_DISABLE_FVAL                     0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_144_ENABLE_FVAL                      0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_102_BMSK                            0x20
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_102_SHFT                             0x5
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_102_DISABLE_FVAL                     0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_102_ENABLE_FVAL                      0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_BMSK                             0x10
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_SHFT                              0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_95_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_93_BMSK                              0x8
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_93_SHFT                              0x3
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_93_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_93_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_BMSK                              0x4
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_SHFT                              0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_92_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_BMSK                              0x2
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_SHFT                              0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_86_ENABLE_FVAL                       0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_BMSK                              0x1
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_SHFT                              0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_DISABLE_FVAL                      0x0
#define HWIO_TLMM_MPM_WAKEUP_INT_EN_1_GPIO_82_ENABLE_FVAL                       0x1

#define HWIO_TLMM_INT_JTAG_CTL_ADDR                                      (TLMM_CSR_REG_BASE      + 0x00002010)
#define HWIO_TLMM_INT_JTAG_CTL_PHYS                                      (TLMM_CSR_REG_BASE_PHYS + 0x00002010)
#define HWIO_TLMM_INT_JTAG_CTL_OFFS                                      (TLMM_CSR_REG_BASE_OFFS + 0x00002010)
#define HWIO_TLMM_INT_JTAG_CTL_RMSK                                            0x1f
#define HWIO_TLMM_INT_JTAG_CTL_IN          \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, HWIO_TLMM_INT_JTAG_CTL_RMSK)
#define HWIO_TLMM_INT_JTAG_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_INT_JTAG_CTL_ADDR, m)
#define HWIO_TLMM_INT_JTAG_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_INT_JTAG_CTL_ADDR,v)
#define HWIO_TLMM_INT_JTAG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_INT_JTAG_CTL_ADDR,m,v,HWIO_TLMM_INT_JTAG_CTL_IN)
#define HWIO_TLMM_INT_JTAG_CTL_USB3_PHY_TAP_ENA_BMSK                           0x10
#define HWIO_TLMM_INT_JTAG_CTL_USB3_PHY_TAP_ENA_SHFT                            0x4
#define HWIO_TLMM_INT_JTAG_CTL_KPSS_TAP_ENA_BMSK                                0x8
#define HWIO_TLMM_INT_JTAG_CTL_KPSS_TAP_ENA_SHFT                                0x3
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_BMSK                                0x4
#define HWIO_TLMM_INT_JTAG_CTL_QDSS_TAP_ENA_SHFT                                0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_BMSK                                 0x2
#define HWIO_TLMM_INT_JTAG_CTL_ACC_TAP_ENA_SHFT                                 0x1
#define HWIO_TLMM_INT_JTAG_CTL_MSM_TAP_ENA_BMSK                                 0x1
#define HWIO_TLMM_INT_JTAG_CTL_MSM_TAP_ENA_SHFT                                 0x0

#define HWIO_TLMM_ETM_MODE_ADDR                                          (TLMM_CSR_REG_BASE      + 0x00002014)
#define HWIO_TLMM_ETM_MODE_PHYS                                          (TLMM_CSR_REG_BASE_PHYS + 0x00002014)
#define HWIO_TLMM_ETM_MODE_OFFS                                          (TLMM_CSR_REG_BASE_OFFS + 0x00002014)
#define HWIO_TLMM_ETM_MODE_RMSK                                                 0x1
#define HWIO_TLMM_ETM_MODE_IN          \
        in_dword_masked(HWIO_TLMM_ETM_MODE_ADDR, HWIO_TLMM_ETM_MODE_RMSK)
#define HWIO_TLMM_ETM_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_ETM_MODE_ADDR, m)
#define HWIO_TLMM_ETM_MODE_OUT(v)      \
        out_dword(HWIO_TLMM_ETM_MODE_ADDR,v)
#define HWIO_TLMM_ETM_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_ETM_MODE_ADDR,m,v,HWIO_TLMM_ETM_MODE_IN)
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_BMSK                                 0x1
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_SHFT                                 0x0
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_DISABLE_FVAL                         0x0
#define HWIO_TLMM_ETM_MODE_TRACE_OVER_SDC2_ENABLE_FVAL                          0x1

#define HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00002018)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_PHYS                                   (TLMM_CSR_REG_BASE_PHYS + 0x00002018)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK                                          0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_IN          \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, HWIO_TLMM_DBG_BUS_OUT_SEL_RMSK)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_INM(m)      \
        in_dword_masked(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR, m)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUT(v)      \
        out_dword(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,v)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_DBG_BUS_OUT_SEL_ADDR,m,v,HWIO_TLMM_DBG_BUS_OUT_SEL_IN)
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_BMSK                                 0x3
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_SHFT                                 0x0
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_A_FVAL                          0x0
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_B_FVAL                          0x1
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_C_FVAL                          0x2
#define HWIO_TLMM_DBG_BUS_OUT_SEL_COPY_SEL_COPY_D_FVAL                          0x3

#define HWIO_TLMM_CHIP_MODE_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00002020)
#define HWIO_TLMM_CHIP_MODE_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00002020)
#define HWIO_TLMM_CHIP_MODE_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00002020)
#define HWIO_TLMM_CHIP_MODE_RMSK                                                0x3
#define HWIO_TLMM_CHIP_MODE_IN          \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, HWIO_TLMM_CHIP_MODE_RMSK)
#define HWIO_TLMM_CHIP_MODE_INM(m)      \
        in_dword_masked(HWIO_TLMM_CHIP_MODE_ADDR, m)
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_BMSK                                      0x2
#define HWIO_TLMM_CHIP_MODE_MODE1_PIN_SHFT                                      0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_BMSK                                      0x1
#define HWIO_TLMM_CHIP_MODE_MODE0_PIN_SHFT                                      0x0

#define HWIO_TLMM_SPARE_ADDR                                             (TLMM_CSR_REG_BASE      + 0x00002024)
#define HWIO_TLMM_SPARE_PHYS                                             (TLMM_CSR_REG_BASE_PHYS + 0x00002024)
#define HWIO_TLMM_SPARE_OFFS                                             (TLMM_CSR_REG_BASE_OFFS + 0x00002024)
#define HWIO_TLMM_SPARE_RMSK                                                   0xff
#define HWIO_TLMM_SPARE_IN          \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, HWIO_TLMM_SPARE_RMSK)
#define HWIO_TLMM_SPARE_INM(m)      \
        in_dword_masked(HWIO_TLMM_SPARE_ADDR, m)
#define HWIO_TLMM_SPARE_OUT(v)      \
        out_dword(HWIO_TLMM_SPARE_ADDR,v)
#define HWIO_TLMM_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SPARE_ADDR,m,v,HWIO_TLMM_SPARE_IN)
#define HWIO_TLMM_SPARE_MISC_BMSK                                              0xff
#define HWIO_TLMM_SPARE_MISC_SHFT                                               0x0

#define HWIO_TLMM_HW_REVISION_NUMBER_ADDR                                (TLMM_CSR_REG_BASE      + 0x00002028)
#define HWIO_TLMM_HW_REVISION_NUMBER_PHYS                                (TLMM_CSR_REG_BASE_PHYS + 0x00002028)
#define HWIO_TLMM_HW_REVISION_NUMBER_OFFS                                (TLMM_CSR_REG_BASE_OFFS + 0x00002028)
#define HWIO_TLMM_HW_REVISION_NUMBER_RMSK                                0xffffffff
#define HWIO_TLMM_HW_REVISION_NUMBER_IN          \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, HWIO_TLMM_HW_REVISION_NUMBER_RMSK)
#define HWIO_TLMM_HW_REVISION_NUMBER_INM(m)      \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_BMSK                     0xf0000000
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_SHFT                           0x1c
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_FIRST_TAPE_OUT_FVAL             0x0
#define HWIO_TLMM_HW_REVISION_NUMBER_PARTNUM_BMSK                         0xffff000
#define HWIO_TLMM_HW_REVISION_NUMBER_PARTNUM_SHFT                               0xc
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_BMSK                     0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_SHFT                       0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_BMSK                             0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_SHFT                             0x0

#define HWIO_TLMM_SLIMBUS_CTL_ADDR                                       (TLMM_CSR_REG_BASE      + 0x00002030)
#define HWIO_TLMM_SLIMBUS_CTL_PHYS                                       (TLMM_CSR_REG_BASE_PHYS + 0x00002030)
#define HWIO_TLMM_SLIMBUS_CTL_OFFS                                       (TLMM_CSR_REG_BASE_OFFS + 0x00002030)
#define HWIO_TLMM_SLIMBUS_CTL_RMSK                                              0x3
#define HWIO_TLMM_SLIMBUS_CTL_IN          \
        in_dword_masked(HWIO_TLMM_SLIMBUS_CTL_ADDR, HWIO_TLMM_SLIMBUS_CTL_RMSK)
#define HWIO_TLMM_SLIMBUS_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_SLIMBUS_CTL_ADDR, m)
#define HWIO_TLMM_SLIMBUS_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_SLIMBUS_CTL_ADDR,v)
#define HWIO_TLMM_SLIMBUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SLIMBUS_CTL_ADDR,m,v,HWIO_TLMM_SLIMBUS_CTL_IN)
#define HWIO_TLMM_SLIMBUS_CTL_SEN_EN_BMSK                                       0x2
#define HWIO_TLMM_SLIMBUS_CTL_SEN_EN_SHFT                                       0x1
#define HWIO_TLMM_SLIMBUS_CTL_SEN_EN_DISABLE_FVAL                               0x0
#define HWIO_TLMM_SLIMBUS_CTL_SEN_EN_ENABLE_FVAL                                0x1
#define HWIO_TLMM_SLIMBUS_CTL_SR_CTL_EN_BMSK                                    0x1
#define HWIO_TLMM_SLIMBUS_CTL_SR_CTL_EN_SHFT                                    0x0
#define HWIO_TLMM_SLIMBUS_CTL_SR_CTL_EN_DISABLE_FVAL                            0x0
#define HWIO_TLMM_SLIMBUS_CTL_SR_CTL_EN_ENABLE_FVAL                             0x1

#define HWIO_TLMM_RFFE_CTL_ADDR                                          (TLMM_CSR_REG_BASE      + 0x00002034)
#define HWIO_TLMM_RFFE_CTL_PHYS                                          (TLMM_CSR_REG_BASE_PHYS + 0x00002034)
#define HWIO_TLMM_RFFE_CTL_OFFS                                          (TLMM_CSR_REG_BASE_OFFS + 0x00002034)
#define HWIO_TLMM_RFFE_CTL_RMSK                                               0xfff
#define HWIO_TLMM_RFFE_CTL_IN          \
        in_dword_masked(HWIO_TLMM_RFFE_CTL_ADDR, HWIO_TLMM_RFFE_CTL_RMSK)
#define HWIO_TLMM_RFFE_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_RFFE_CTL_ADDR, m)
#define HWIO_TLMM_RFFE_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_RFFE_CTL_ADDR,v)
#define HWIO_TLMM_RFFE_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_RFFE_CTL_ADDR,m,v,HWIO_TLMM_RFFE_CTL_IN)
#define HWIO_TLMM_RFFE_CTL_RFFE2_DATA_SEN_EN_BMSK                             0x800
#define HWIO_TLMM_RFFE_CTL_RFFE2_DATA_SEN_EN_SHFT                               0xb
#define HWIO_TLMM_RFFE_CTL_RFFE2_DATA_SR_CTL_EN_BMSK                          0x600
#define HWIO_TLMM_RFFE_CTL_RFFE2_DATA_SR_CTL_EN_SHFT                            0x9
#define HWIO_TLMM_RFFE_CTL_RFFE2_CLK_SEN_EN_BMSK                              0x100
#define HWIO_TLMM_RFFE_CTL_RFFE2_CLK_SEN_EN_SHFT                                0x8
#define HWIO_TLMM_RFFE_CTL_RFFE2_CLK_SR_CTL_EN_BMSK                            0xc0
#define HWIO_TLMM_RFFE_CTL_RFFE2_CLK_SR_CTL_EN_SHFT                             0x6
#define HWIO_TLMM_RFFE_CTL_RFFE1_DATA_SEN_EN_BMSK                              0x20
#define HWIO_TLMM_RFFE_CTL_RFFE1_DATA_SEN_EN_SHFT                               0x5
#define HWIO_TLMM_RFFE_CTL_RFFE1_DATA_SR_CTL_EN_BMSK                           0x18
#define HWIO_TLMM_RFFE_CTL_RFFE1_DATA_SR_CTL_EN_SHFT                            0x3
#define HWIO_TLMM_RFFE_CTL_RFFE1_CLK_SEN_EN_BMSK                                0x4
#define HWIO_TLMM_RFFE_CTL_RFFE1_CLK_SEN_EN_SHFT                                0x2
#define HWIO_TLMM_RFFE_CTL_RFFE1_CLK_SR_CTL_EN_BMSK                             0x3
#define HWIO_TLMM_RFFE_CTL_RFFE1_CLK_SR_CTL_EN_SHFT                             0x0

#define HWIO_TLMM_RESOUT_HDRV_CTL_ADDR                                   (TLMM_CSR_REG_BASE      + 0x00002038)
#define HWIO_TLMM_RESOUT_HDRV_CTL_PHYS                                   (TLMM_CSR_REG_BASE_PHYS + 0x00002038)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OFFS                                   (TLMM_CSR_REG_BASE_OFFS + 0x00002038)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RMSK                                          0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, HWIO_TLMM_RESOUT_HDRV_CTL_RMSK)
#define HWIO_TLMM_RESOUT_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_RESOUT_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_RESOUT_HDRV_CTL_ADDR,m,v,HWIO_TLMM_RESOUT_HDRV_CTL_IN)
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_BMSK                            0x7
#define HWIO_TLMM_RESOUT_HDRV_CTL_RESOUT_N_HDRV_SHFT                            0x0

#define HWIO_TLMM_JTAG_HDRV_CTL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x0000203c)
#define HWIO_TLMM_JTAG_HDRV_CTL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x0000203c)
#define HWIO_TLMM_JTAG_HDRV_CTL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x0000203c)
#define HWIO_TLMM_JTAG_HDRV_CTL_RMSK                                          0x3ff
#define HWIO_TLMM_JTAG_HDRV_CTL_IN          \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, HWIO_TLMM_JTAG_HDRV_CTL_RMSK)
#define HWIO_TLMM_JTAG_HDRV_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_JTAG_HDRV_CTL_ADDR, m)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,v)
#define HWIO_TLMM_JTAG_HDRV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_JTAG_HDRV_CTL_ADDR,m,v,HWIO_TLMM_JTAG_HDRV_CTL_IN)
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_BMSK                                 0x300
#define HWIO_TLMM_JTAG_HDRV_CTL_TDI_PULL_SHFT                                   0x8
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_BMSK                                  0xc0
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_PULL_SHFT                                   0x6
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_BMSK                                  0x38
#define HWIO_TLMM_JTAG_HDRV_CTL_TMS_HDRV_SHFT                                   0x3
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_BMSK                                   0x7
#define HWIO_TLMM_JTAG_HDRV_CTL_TDO_HDRV_SHFT                                   0x0

#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR                                (TLMM_CSR_REG_BASE      + 0x00002040)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PHYS                                (TLMM_CSR_REG_BASE_PHYS + 0x00002040)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OFFS                                (TLMM_CSR_REG_BASE_OFFS + 0x00002040)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_RMSK                                   0x3ffff
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR, HWIO_TLMM_PMIC_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_PMIC_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_PMIC_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SEN_EN_BMSK             0x20000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_SEN_EN_SHFT                0x11
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SEN_EN_BMSK              0x10000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_SEN_EN_SHFT                 0x10
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_PULL_BMSK                0xc000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_PULL_SHFT                   0xe
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_PULL_BMSK                 0x3000
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_PULL_SHFT                    0xc
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PSHOLD_HDRV_BMSK                         0xe00
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PSHOLD_HDRV_SHFT                           0x9
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_CXO_EN_HDRV_BMSK                         0x1c0
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_CXO_EN_HDRV_SHFT                           0x6
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_HDRV_BMSK                  0x38
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_DATA_HDRV_SHFT                   0x3
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_HDRV_BMSK                    0x7
#define HWIO_TLMM_PMIC_HDRV_PULL_CTL_PMIC_SPMI_CLK_HDRV_SHFT                    0x0

#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR                                (TLMM_CSR_REG_BASE      + 0x00002044)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_PHYS                                (TLMM_CSR_REG_BASE_PHYS + 0x00002044)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OFFS                                (TLMM_CSR_REG_BASE_OFFS + 0x00002044)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_RMSK                                    0x7fff
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR, HWIO_TLMM_SDC1_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SDC1_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_SDC1_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_PULL_BMSK                      0x6000
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_PULL_SHFT                         0xd
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_PULL_BMSK                      0x1800
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_PULL_SHFT                         0xb
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_PULL_BMSK                      0x600
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_PULL_SHFT                        0x9
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_HDRV_BMSK                       0x1c0
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CLK_HDRV_SHFT                         0x6
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_HDRV_BMSK                        0x38
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_CMD_HDRV_SHFT                         0x3
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_HDRV_BMSK                        0x7
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_SDC1_DATA_HDRV_SHFT                        0x0

#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR                                (TLMM_CSR_REG_BASE      + 0x00002048)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_PHYS                                (TLMM_CSR_REG_BASE_PHYS + 0x00002048)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OFFS                                (TLMM_CSR_REG_BASE_OFFS + 0x00002048)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_RMSK                                    0xffff
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, HWIO_TLMM_SDC2_HDRV_PULL_CTL_RMSK)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, m)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR,v)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR,m,v,HWIO_TLMM_SDC2_HDRV_PULL_CTL_IN)
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_PULL_BMSK                      0xc000
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_PULL_SHFT                         0xe
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_BMSK                       0x2000
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_SHFT                          0xd
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_DISABLE_FVAL                  0x0
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_HYS_CTL_ENABLE_FVAL                   0x1
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_PULL_BMSK                      0x1800
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_PULL_SHFT                         0xb
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_PULL_BMSK                      0x600
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_PULL_SHFT                        0x9
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_HDRV_BMSK                       0x1c0
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CLK_HDRV_SHFT                         0x6
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_HDRV_BMSK                        0x38
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_CMD_HDRV_SHFT                         0x3
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_HDRV_BMSK                        0x7
#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_SDC2_DATA_HDRV_SHFT                        0x0

#define HWIO_TLMM_MODE_PULL_CTL_ADDR                                     (TLMM_CSR_REG_BASE      + 0x0000204c)
#define HWIO_TLMM_MODE_PULL_CTL_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x0000204c)
#define HWIO_TLMM_MODE_PULL_CTL_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x0000204c)
#define HWIO_TLMM_MODE_PULL_CTL_RMSK                                            0xf
#define HWIO_TLMM_MODE_PULL_CTL_IN          \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, HWIO_TLMM_MODE_PULL_CTL_RMSK)
#define HWIO_TLMM_MODE_PULL_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_MODE_PULL_CTL_ADDR, m)
#define HWIO_TLMM_MODE_PULL_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_MODE_PULL_CTL_ADDR,v)
#define HWIO_TLMM_MODE_PULL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_MODE_PULL_CTL_ADDR,m,v,HWIO_TLMM_MODE_PULL_CTL_IN)
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_BMSK                                0xc
#define HWIO_TLMM_MODE_PULL_CTL_MODE_1_PULL_SHFT                                0x2
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_BMSK                                0x3
#define HWIO_TLMM_MODE_PULL_CTL_MODE_0_PULL_SHFT                                0x0

#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ADDR                          (TLMM_CSR_REG_BASE      + 0x00002050)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PHYS                          (TLMM_CSR_REG_BASE_PHYS + 0x00002050)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_OFFS                          (TLMM_CSR_REG_BASE_OFFS + 0x00002050)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_RMSK                           0x3ffffff
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ADDR, HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_RMSK)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ADDR, m)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ADDR,v)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ADDR,m,v,HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_IN)
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_CORE_CTL_EN_BMSK               0x2000000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_CORE_CTL_EN_SHFT                    0x19
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_VM_SHIFT_EN_BMSK               0x1000000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_VM_SHIFT_EN_SHFT                    0x18
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ODT_EN_BMSK                     0x800000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ODT_EN_SHFT                         0x17
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ODT_BMSK                        0x600000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_ODT_SHFT                            0x15
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_DCC_BMSK                        0x1c0000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_DCC_SHFT                            0x12
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NRXDEL_BMSK                      0x30000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NRXDEL_SHFT                         0x10
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PRXDEL_BMSK                       0xc000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PRXDEL_SHFT                          0xe
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NSLEW_BMSK                        0x3000
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NSLEW_SHFT                           0xc
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PSLEW_BMSK                         0xc00
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PSLEW_SHFT                           0xa
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NCNT_BMSK                          0x3e0
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_NCNT_SHFT                            0x5
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PCNT_BMSK                           0x1f
#define HWIO_TLMM_GPIO_HSIC_STROBE_PAD_CTL_PCNT_SHFT                            0x0

#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ADDR                            (TLMM_CSR_REG_BASE      + 0x00002054)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PHYS                            (TLMM_CSR_REG_BASE_PHYS + 0x00002054)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_OFFS                            (TLMM_CSR_REG_BASE_OFFS + 0x00002054)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_RMSK                             0x3ffffff
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ADDR, HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_RMSK)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ADDR, m)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ADDR,v)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ADDR,m,v,HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_IN)
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_CORE_CTL_EN_BMSK                 0x2000000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_CORE_CTL_EN_SHFT                      0x19
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_VM_SHIFT_EN_BMSK                 0x1000000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_VM_SHIFT_EN_SHFT                      0x18
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ODT_EN_BMSK                       0x800000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ODT_EN_SHFT                           0x17
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ODT_BMSK                          0x600000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_ODT_SHFT                              0x15
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_DCC_BMSK                          0x1c0000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_DCC_SHFT                              0x12
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NRXDEL_BMSK                        0x30000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NRXDEL_SHFT                           0x10
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PRXDEL_BMSK                         0xc000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PRXDEL_SHFT                            0xe
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NSLEW_BMSK                          0x3000
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NSLEW_SHFT                             0xc
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PSLEW_BMSK                           0xc00
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PSLEW_SHFT                             0xa
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NCNT_BMSK                            0x3e0
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_NCNT_SHFT                              0x5
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PCNT_BMSK                             0x1f
#define HWIO_TLMM_GPIO_HSIC_DATA_PAD_CTL_PCNT_SHFT                              0x0

#define HWIO_TLMM_HSIC_CAL_PAD_CTL_ADDR                                  (TLMM_CSR_REG_BASE      + 0x00002058)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_PHYS                                  (TLMM_CSR_REG_BASE_PHYS + 0x00002058)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_OFFS                                  (TLMM_CSR_REG_BASE_OFFS + 0x00002058)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_RMSK                                         0x3
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_IN          \
        in_dword_masked(HWIO_TLMM_HSIC_CAL_PAD_CTL_ADDR, HWIO_TLMM_HSIC_CAL_PAD_CTL_RMSK)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_HSIC_CAL_PAD_CTL_ADDR, m)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_HSIC_CAL_PAD_CTL_ADDR,v)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_HSIC_CAL_PAD_CTL_ADDR,m,v,HWIO_TLMM_HSIC_CAL_PAD_CTL_IN)
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_IMP_SEL_BMSK                                 0x3
#define HWIO_TLMM_HSIC_CAL_PAD_CTL_IMP_SEL_SHFT                                 0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_ADDR(n)                        (TLMM_CSR_REG_BASE      + 0x00002100 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_PHYS(n)                        (TLMM_CSR_REG_BASE_PHYS + 0x00002100 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_OFFS(n)                        (TLMM_CSR_REG_BASE_OFFS + 0x00002100 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_RMSK                                0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_MAXn                                    1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_POLARITY_BMSK                       0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_POLARITY_SHFT                         0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_POLARITY_POLARITY_0_FVAL              0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_POLARITY_POLARITY_1_FVAL              0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_GPIO_SEL_BMSK                        0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_WCSS_GPIO_SEL_SHFT                         0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n)                     (TLMM_CSR_REG_BASE      + 0x00002200 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_PHYS(n)                     (TLMM_CSR_REG_BASE_PHYS + 0x00002200 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OFFS(n)                     (TLMM_CSR_REG_BASE_OFFS + 0x00002200 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_RMSK                             0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_MAXn                                 9
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_BMSK                    0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_SHFT                      0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_POLARITY_0_FVAL           0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_POLARITY_POLARITY_1_FVAL           0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_BMSK                     0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_SENSORS_GPIO_SEL_SHFT                      0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n)                     (TLMM_CSR_REG_BASE      + 0x00002500 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_PHYS(n)                     (TLMM_CSR_REG_BASE_PHYS + 0x00002500 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OFFS(n)                     (TLMM_CSR_REG_BASE_OFFS + 0x00002500 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_RMSK                             0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_MAXn                                 5
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_BMSK                    0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_SHFT                      0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_POLARITY_0_FVAL           0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_POLARITY_POLARITY_1_FVAL           0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_GPIO_SEL_BMSK                     0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_LPA_DSP_GPIO_SEL_SHFT                      0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n)                         (TLMM_CSR_REG_BASE      + 0x00002700 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_PHYS(n)                         (TLMM_CSR_REG_BASE_PHYS + 0x00002700 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OFFS(n)                         (TLMM_CSR_REG_BASE_OFFS + 0x00002700 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_RMSK                                 0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_MAXn                                     0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_BMSK                        0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_SHFT                          0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_POLARITY_0_FVAL               0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_POLARITY_POLARITY_1_FVAL               0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_GPIO_SEL_BMSK                         0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_RPM_GPIO_SEL_SHFT                          0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_ADDR(n)                        (TLMM_CSR_REG_BASE      + 0x00002800 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_PHYS(n)                        (TLMM_CSR_REG_BASE_PHYS + 0x00002800 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_OFFS(n)                        (TLMM_CSR_REG_BASE_OFFS + 0x00002800 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_RMSK                                0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_MAXn                                    7
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_POLARITY_BMSK                       0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_POLARITY_SHFT                         0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_POLARITY_POLARITY_0_FVAL              0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_POLARITY_POLARITY_1_FVAL              0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_GPIO_SEL_BMSK                        0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_KPSS_GPIO_SEL_SHFT                         0x0

#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_ADDR(n)                         (TLMM_CSR_REG_BASE      + 0x00002a00 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_PHYS(n)                         (TLMM_CSR_REG_BASE_PHYS + 0x00002a00 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_OFFS(n)                         (TLMM_CSR_REG_BASE_OFFS + 0x00002a00 + 0x4 * (n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_RMSK                                 0x1ff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_MAXn                                     1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_INI(n)        \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_ADDR(n), HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_RMSK)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_INMI(n,mask)    \
        in_dword_masked(HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_ADDR(n), mask)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_OUTI(n,val)    \
        out_dword(HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_ADDR(n),val)
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_ADDR(n),mask,val,HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_INI(n))
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_POLARITY_BMSK                        0x100
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_POLARITY_SHFT                          0x8
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_POLARITY_POLARITY_0_FVAL               0x0
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_POLARITY_POLARITY_1_FVAL               0x1
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_GPIO_SEL_BMSK                         0xff
#define HWIO_TLMM_DIR_CONN_INTRn_CFG_MSS_GPIO_SEL_SHFT                          0x0

#define HWIO_TLMM_GPIO_OUT_0_ADDR                                        (TLMM_CSR_REG_BASE      + 0x00003000)
#define HWIO_TLMM_GPIO_OUT_0_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x00003000)
#define HWIO_TLMM_GPIO_OUT_0_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x00003000)
#define HWIO_TLMM_GPIO_OUT_0_RMSK                                        0xffffffff
#define HWIO_TLMM_GPIO_OUT_0_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_0_ADDR, HWIO_TLMM_GPIO_OUT_0_RMSK)
#define HWIO_TLMM_GPIO_OUT_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_0_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_0_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_0_ADDR,m,v,HWIO_TLMM_GPIO_OUT_0_IN)
#define HWIO_TLMM_GPIO_OUT_0_GPIO_OUT_BMSK                               0xffffffff
#define HWIO_TLMM_GPIO_OUT_0_GPIO_OUT_SHFT                                      0x0

#define HWIO_TLMM_GPIO_OUT_1_ADDR                                        (TLMM_CSR_REG_BASE      + 0x00003004)
#define HWIO_TLMM_GPIO_OUT_1_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x00003004)
#define HWIO_TLMM_GPIO_OUT_1_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x00003004)
#define HWIO_TLMM_GPIO_OUT_1_RMSK                                        0xffffffff
#define HWIO_TLMM_GPIO_OUT_1_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_1_ADDR, HWIO_TLMM_GPIO_OUT_1_RMSK)
#define HWIO_TLMM_GPIO_OUT_1_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_1_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_1_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_1_ADDR,m,v,HWIO_TLMM_GPIO_OUT_1_IN)
#define HWIO_TLMM_GPIO_OUT_1_GPIO_OUT_BMSK                               0xffffffff
#define HWIO_TLMM_GPIO_OUT_1_GPIO_OUT_SHFT                                      0x0

#define HWIO_TLMM_GPIO_OUT_2_ADDR                                        (TLMM_CSR_REG_BASE      + 0x00003008)
#define HWIO_TLMM_GPIO_OUT_2_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x00003008)
#define HWIO_TLMM_GPIO_OUT_2_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x00003008)
#define HWIO_TLMM_GPIO_OUT_2_RMSK                                        0xffffffff
#define HWIO_TLMM_GPIO_OUT_2_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_2_ADDR, HWIO_TLMM_GPIO_OUT_2_RMSK)
#define HWIO_TLMM_GPIO_OUT_2_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_2_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_2_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_2_ADDR,m,v,HWIO_TLMM_GPIO_OUT_2_IN)
#define HWIO_TLMM_GPIO_OUT_2_GPIO_OUT_BMSK                               0xffffffff
#define HWIO_TLMM_GPIO_OUT_2_GPIO_OUT_SHFT                                      0x0

#define HWIO_TLMM_GPIO_OUT_3_ADDR                                        (TLMM_CSR_REG_BASE      + 0x0000300c)
#define HWIO_TLMM_GPIO_OUT_3_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x0000300c)
#define HWIO_TLMM_GPIO_OUT_3_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x0000300c)
#define HWIO_TLMM_GPIO_OUT_3_RMSK                                        0xffffffff
#define HWIO_TLMM_GPIO_OUT_3_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_3_ADDR, HWIO_TLMM_GPIO_OUT_3_RMSK)
#define HWIO_TLMM_GPIO_OUT_3_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_3_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_3_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_3_ADDR,m,v,HWIO_TLMM_GPIO_OUT_3_IN)
#define HWIO_TLMM_GPIO_OUT_3_GPIO_OUT_BMSK                               0xffffffff
#define HWIO_TLMM_GPIO_OUT_3_GPIO_OUT_SHFT                                      0x0

#define HWIO_TLMM_GPIO_OUT_4_ADDR                                        (TLMM_CSR_REG_BASE      + 0x00003010)
#define HWIO_TLMM_GPIO_OUT_4_PHYS                                        (TLMM_CSR_REG_BASE_PHYS + 0x00003010)
#define HWIO_TLMM_GPIO_OUT_4_OFFS                                        (TLMM_CSR_REG_BASE_OFFS + 0x00003010)
#define HWIO_TLMM_GPIO_OUT_4_RMSK                                           0x3ffff
#define HWIO_TLMM_GPIO_OUT_4_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_4_ADDR, HWIO_TLMM_GPIO_OUT_4_RMSK)
#define HWIO_TLMM_GPIO_OUT_4_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_4_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_4_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_4_ADDR,m,v,HWIO_TLMM_GPIO_OUT_4_IN)
#define HWIO_TLMM_GPIO_OUT_4_GPIO_OUT_BMSK                                  0x3ffff
#define HWIO_TLMM_GPIO_OUT_4_GPIO_OUT_SHFT                                      0x0

#define HWIO_TLMM_GPIO_OUT_CLR_0_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003020)
#define HWIO_TLMM_GPIO_OUT_CLR_0_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003020)
#define HWIO_TLMM_GPIO_OUT_CLR_0_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003020)
#define HWIO_TLMM_GPIO_OUT_CLR_0_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_CLR_0_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_CLR_0_GPIO_OUT_CLR_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_0_GPIO_OUT_CLR_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_CLR_1_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003024)
#define HWIO_TLMM_GPIO_OUT_CLR_1_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003024)
#define HWIO_TLMM_GPIO_OUT_CLR_1_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003024)
#define HWIO_TLMM_GPIO_OUT_CLR_1_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_CLR_1_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_CLR_1_GPIO_OUT_CLR_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_1_GPIO_OUT_CLR_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_CLR_2_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003028)
#define HWIO_TLMM_GPIO_OUT_CLR_2_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003028)
#define HWIO_TLMM_GPIO_OUT_CLR_2_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003028)
#define HWIO_TLMM_GPIO_OUT_CLR_2_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_CLR_2_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_CLR_2_GPIO_OUT_CLR_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_2_GPIO_OUT_CLR_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_CLR_3_ADDR                                    (TLMM_CSR_REG_BASE      + 0x0000302c)
#define HWIO_TLMM_GPIO_OUT_CLR_3_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x0000302c)
#define HWIO_TLMM_GPIO_OUT_CLR_3_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x0000302c)
#define HWIO_TLMM_GPIO_OUT_CLR_3_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_CLR_3_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_CLR_3_GPIO_OUT_CLR_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_CLR_3_GPIO_OUT_CLR_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_CLR_4_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003030)
#define HWIO_TLMM_GPIO_OUT_CLR_4_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003030)
#define HWIO_TLMM_GPIO_OUT_CLR_4_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003030)
#define HWIO_TLMM_GPIO_OUT_CLR_4_RMSK                                       0x3ffff
#define HWIO_TLMM_GPIO_OUT_CLR_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_CLR_4_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_CLR_4_GPIO_OUT_CLR_BMSK                          0x3ffff
#define HWIO_TLMM_GPIO_OUT_CLR_4_GPIO_OUT_CLR_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_SET_0_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003040)
#define HWIO_TLMM_GPIO_OUT_SET_0_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003040)
#define HWIO_TLMM_GPIO_OUT_SET_0_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003040)
#define HWIO_TLMM_GPIO_OUT_SET_0_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_SET_0_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_SET_0_GPIO_OUT_SET_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_0_GPIO_OUT_SET_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_SET_1_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003044)
#define HWIO_TLMM_GPIO_OUT_SET_1_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003044)
#define HWIO_TLMM_GPIO_OUT_SET_1_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003044)
#define HWIO_TLMM_GPIO_OUT_SET_1_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_SET_1_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_SET_1_GPIO_OUT_SET_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_1_GPIO_OUT_SET_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_SET_2_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003048)
#define HWIO_TLMM_GPIO_OUT_SET_2_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003048)
#define HWIO_TLMM_GPIO_OUT_SET_2_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003048)
#define HWIO_TLMM_GPIO_OUT_SET_2_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_SET_2_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_SET_2_GPIO_OUT_SET_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_2_GPIO_OUT_SET_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_SET_3_ADDR                                    (TLMM_CSR_REG_BASE      + 0x0000304c)
#define HWIO_TLMM_GPIO_OUT_SET_3_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x0000304c)
#define HWIO_TLMM_GPIO_OUT_SET_3_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x0000304c)
#define HWIO_TLMM_GPIO_OUT_SET_3_RMSK                                    0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_SET_3_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_SET_3_GPIO_OUT_SET_BMSK                       0xffffffff
#define HWIO_TLMM_GPIO_OUT_SET_3_GPIO_OUT_SET_SHFT                              0x0

#define HWIO_TLMM_GPIO_OUT_SET_4_ADDR                                    (TLMM_CSR_REG_BASE      + 0x00003050)
#define HWIO_TLMM_GPIO_OUT_SET_4_PHYS                                    (TLMM_CSR_REG_BASE_PHYS + 0x00003050)
#define HWIO_TLMM_GPIO_OUT_SET_4_OFFS                                    (TLMM_CSR_REG_BASE_OFFS + 0x00003050)
#define HWIO_TLMM_GPIO_OUT_SET_4_RMSK                                       0x3ffff
#define HWIO_TLMM_GPIO_OUT_SET_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_SET_4_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_SET_4_GPIO_OUT_SET_BMSK                          0x3ffff
#define HWIO_TLMM_GPIO_OUT_SET_4_GPIO_OUT_SET_SHFT                              0x0

#define HWIO_TLMM_GPIO_IN_0_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003060)
#define HWIO_TLMM_GPIO_IN_0_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003060)
#define HWIO_TLMM_GPIO_IN_0_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003060)
#define HWIO_TLMM_GPIO_IN_0_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_IN_0_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_IN_0_ADDR, HWIO_TLMM_GPIO_IN_0_RMSK)
#define HWIO_TLMM_GPIO_IN_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_0_ADDR, m)
#define HWIO_TLMM_GPIO_IN_0_GPIO_IN_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_IN_0_GPIO_IN_SHFT                                        0x0

#define HWIO_TLMM_GPIO_IN_1_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003064)
#define HWIO_TLMM_GPIO_IN_1_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003064)
#define HWIO_TLMM_GPIO_IN_1_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003064)
#define HWIO_TLMM_GPIO_IN_1_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_IN_1_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_IN_1_ADDR, HWIO_TLMM_GPIO_IN_1_RMSK)
#define HWIO_TLMM_GPIO_IN_1_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_1_ADDR, m)
#define HWIO_TLMM_GPIO_IN_1_GPIO_IN_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_IN_1_GPIO_IN_SHFT                                        0x0

#define HWIO_TLMM_GPIO_IN_2_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003068)
#define HWIO_TLMM_GPIO_IN_2_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003068)
#define HWIO_TLMM_GPIO_IN_2_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003068)
#define HWIO_TLMM_GPIO_IN_2_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_IN_2_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_IN_2_ADDR, HWIO_TLMM_GPIO_IN_2_RMSK)
#define HWIO_TLMM_GPIO_IN_2_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_2_ADDR, m)
#define HWIO_TLMM_GPIO_IN_2_GPIO_IN_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_IN_2_GPIO_IN_SHFT                                        0x0

#define HWIO_TLMM_GPIO_IN_3_ADDR                                         (TLMM_CSR_REG_BASE      + 0x0000306c)
#define HWIO_TLMM_GPIO_IN_3_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x0000306c)
#define HWIO_TLMM_GPIO_IN_3_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x0000306c)
#define HWIO_TLMM_GPIO_IN_3_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_IN_3_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_IN_3_ADDR, HWIO_TLMM_GPIO_IN_3_RMSK)
#define HWIO_TLMM_GPIO_IN_3_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_3_ADDR, m)
#define HWIO_TLMM_GPIO_IN_3_GPIO_IN_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_IN_3_GPIO_IN_SHFT                                        0x0

#define HWIO_TLMM_GPIO_IN_4_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003070)
#define HWIO_TLMM_GPIO_IN_4_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003070)
#define HWIO_TLMM_GPIO_IN_4_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003070)
#define HWIO_TLMM_GPIO_IN_4_RMSK                                            0x3ffff
#define HWIO_TLMM_GPIO_IN_4_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_IN_4_ADDR, HWIO_TLMM_GPIO_IN_4_RMSK)
#define HWIO_TLMM_GPIO_IN_4_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_4_ADDR, m)
#define HWIO_TLMM_GPIO_IN_4_GPIO_IN_BMSK                                    0x3ffff
#define HWIO_TLMM_GPIO_IN_4_GPIO_IN_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_0_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003080)
#define HWIO_TLMM_GPIO_OE_0_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003080)
#define HWIO_TLMM_GPIO_OE_0_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003080)
#define HWIO_TLMM_GPIO_OE_0_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_OE_0_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OE_0_ADDR, HWIO_TLMM_GPIO_OE_0_RMSK)
#define HWIO_TLMM_GPIO_OE_0_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_0_ADDR, m)
#define HWIO_TLMM_GPIO_OE_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_0_ADDR,v)
#define HWIO_TLMM_GPIO_OE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_0_ADDR,m,v,HWIO_TLMM_GPIO_OE_0_IN)
#define HWIO_TLMM_GPIO_OE_0_GPIO_OE_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_OE_0_GPIO_OE_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_1_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003084)
#define HWIO_TLMM_GPIO_OE_1_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003084)
#define HWIO_TLMM_GPIO_OE_1_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003084)
#define HWIO_TLMM_GPIO_OE_1_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_OE_1_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OE_1_ADDR, HWIO_TLMM_GPIO_OE_1_RMSK)
#define HWIO_TLMM_GPIO_OE_1_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_1_ADDR, m)
#define HWIO_TLMM_GPIO_OE_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_1_ADDR,v)
#define HWIO_TLMM_GPIO_OE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_1_ADDR,m,v,HWIO_TLMM_GPIO_OE_1_IN)
#define HWIO_TLMM_GPIO_OE_1_GPIO_OE_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_OE_1_GPIO_OE_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_2_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003088)
#define HWIO_TLMM_GPIO_OE_2_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003088)
#define HWIO_TLMM_GPIO_OE_2_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003088)
#define HWIO_TLMM_GPIO_OE_2_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_OE_2_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OE_2_ADDR, HWIO_TLMM_GPIO_OE_2_RMSK)
#define HWIO_TLMM_GPIO_OE_2_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_2_ADDR, m)
#define HWIO_TLMM_GPIO_OE_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_2_ADDR,v)
#define HWIO_TLMM_GPIO_OE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_2_ADDR,m,v,HWIO_TLMM_GPIO_OE_2_IN)
#define HWIO_TLMM_GPIO_OE_2_GPIO_OE_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_OE_2_GPIO_OE_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_3_ADDR                                         (TLMM_CSR_REG_BASE      + 0x0000308c)
#define HWIO_TLMM_GPIO_OE_3_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x0000308c)
#define HWIO_TLMM_GPIO_OE_3_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x0000308c)
#define HWIO_TLMM_GPIO_OE_3_RMSK                                         0xffffffff
#define HWIO_TLMM_GPIO_OE_3_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OE_3_ADDR, HWIO_TLMM_GPIO_OE_3_RMSK)
#define HWIO_TLMM_GPIO_OE_3_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_3_ADDR, m)
#define HWIO_TLMM_GPIO_OE_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_3_ADDR,v)
#define HWIO_TLMM_GPIO_OE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_3_ADDR,m,v,HWIO_TLMM_GPIO_OE_3_IN)
#define HWIO_TLMM_GPIO_OE_3_GPIO_OE_BMSK                                 0xffffffff
#define HWIO_TLMM_GPIO_OE_3_GPIO_OE_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_4_ADDR                                         (TLMM_CSR_REG_BASE      + 0x00003090)
#define HWIO_TLMM_GPIO_OE_4_PHYS                                         (TLMM_CSR_REG_BASE_PHYS + 0x00003090)
#define HWIO_TLMM_GPIO_OE_4_OFFS                                         (TLMM_CSR_REG_BASE_OFFS + 0x00003090)
#define HWIO_TLMM_GPIO_OE_4_RMSK                                            0x3ffff
#define HWIO_TLMM_GPIO_OE_4_IN          \
        in_dword_masked(HWIO_TLMM_GPIO_OE_4_ADDR, HWIO_TLMM_GPIO_OE_4_RMSK)
#define HWIO_TLMM_GPIO_OE_4_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_4_ADDR, m)
#define HWIO_TLMM_GPIO_OE_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_4_ADDR,v)
#define HWIO_TLMM_GPIO_OE_4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_4_ADDR,m,v,HWIO_TLMM_GPIO_OE_4_IN)
#define HWIO_TLMM_GPIO_OE_4_GPIO_OE_BMSK                                    0x3ffff
#define HWIO_TLMM_GPIO_OE_4_GPIO_OE_SHFT                                        0x0

#define HWIO_TLMM_GPIO_OE_CLR_0_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003100)
#define HWIO_TLMM_GPIO_OE_CLR_0_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003100)
#define HWIO_TLMM_GPIO_OE_CLR_0_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003100)
#define HWIO_TLMM_GPIO_OE_CLR_0_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_CLR_0_ADDR,v)
#define HWIO_TLMM_GPIO_OE_CLR_0_GPIO_OE_CLR_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_0_GPIO_OE_CLR_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_CLR_1_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003104)
#define HWIO_TLMM_GPIO_OE_CLR_1_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003104)
#define HWIO_TLMM_GPIO_OE_CLR_1_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003104)
#define HWIO_TLMM_GPIO_OE_CLR_1_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_CLR_1_ADDR,v)
#define HWIO_TLMM_GPIO_OE_CLR_1_GPIO_OE_CLR_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_1_GPIO_OE_CLR_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_CLR_2_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003108)
#define HWIO_TLMM_GPIO_OE_CLR_2_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003108)
#define HWIO_TLMM_GPIO_OE_CLR_2_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003108)
#define HWIO_TLMM_GPIO_OE_CLR_2_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_CLR_2_ADDR,v)
#define HWIO_TLMM_GPIO_OE_CLR_2_GPIO_OE_CLR_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_2_GPIO_OE_CLR_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_CLR_3_ADDR                                     (TLMM_CSR_REG_BASE      + 0x0000310c)
#define HWIO_TLMM_GPIO_OE_CLR_3_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x0000310c)
#define HWIO_TLMM_GPIO_OE_CLR_3_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x0000310c)
#define HWIO_TLMM_GPIO_OE_CLR_3_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_CLR_3_ADDR,v)
#define HWIO_TLMM_GPIO_OE_CLR_3_GPIO_OE_CLR_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_CLR_3_GPIO_OE_CLR_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_CLR_4_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003110)
#define HWIO_TLMM_GPIO_OE_CLR_4_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003110)
#define HWIO_TLMM_GPIO_OE_CLR_4_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003110)
#define HWIO_TLMM_GPIO_OE_CLR_4_RMSK                                        0x3ffff
#define HWIO_TLMM_GPIO_OE_CLR_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_CLR_4_ADDR,v)
#define HWIO_TLMM_GPIO_OE_CLR_4_GPIO_OE_CLR_BMSK                            0x3ffff
#define HWIO_TLMM_GPIO_OE_CLR_4_GPIO_OE_CLR_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_SET_0_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003120)
#define HWIO_TLMM_GPIO_OE_SET_0_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003120)
#define HWIO_TLMM_GPIO_OE_SET_0_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003120)
#define HWIO_TLMM_GPIO_OE_SET_0_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_0_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_SET_0_ADDR,v)
#define HWIO_TLMM_GPIO_OE_SET_0_GPIO_OE_SET_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_0_GPIO_OE_SET_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_SET_1_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003124)
#define HWIO_TLMM_GPIO_OE_SET_1_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003124)
#define HWIO_TLMM_GPIO_OE_SET_1_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003124)
#define HWIO_TLMM_GPIO_OE_SET_1_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_1_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_SET_1_ADDR,v)
#define HWIO_TLMM_GPIO_OE_SET_1_GPIO_OE_SET_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_1_GPIO_OE_SET_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_SET_2_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003128)
#define HWIO_TLMM_GPIO_OE_SET_2_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003128)
#define HWIO_TLMM_GPIO_OE_SET_2_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003128)
#define HWIO_TLMM_GPIO_OE_SET_2_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_2_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_SET_2_ADDR,v)
#define HWIO_TLMM_GPIO_OE_SET_2_GPIO_OE_SET_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_2_GPIO_OE_SET_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_SET_3_ADDR                                     (TLMM_CSR_REG_BASE      + 0x0000312c)
#define HWIO_TLMM_GPIO_OE_SET_3_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x0000312c)
#define HWIO_TLMM_GPIO_OE_SET_3_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x0000312c)
#define HWIO_TLMM_GPIO_OE_SET_3_RMSK                                     0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_3_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_SET_3_ADDR,v)
#define HWIO_TLMM_GPIO_OE_SET_3_GPIO_OE_SET_BMSK                         0xffffffff
#define HWIO_TLMM_GPIO_OE_SET_3_GPIO_OE_SET_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_SET_4_ADDR                                     (TLMM_CSR_REG_BASE      + 0x00003130)
#define HWIO_TLMM_GPIO_OE_SET_4_PHYS                                     (TLMM_CSR_REG_BASE_PHYS + 0x00003130)
#define HWIO_TLMM_GPIO_OE_SET_4_OFFS                                     (TLMM_CSR_REG_BASE_OFFS + 0x00003130)
#define HWIO_TLMM_GPIO_OE_SET_4_RMSK                                        0x3ffff
#define HWIO_TLMM_GPIO_OE_SET_4_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_SET_4_ADDR,v)
#define HWIO_TLMM_GPIO_OE_SET_4_GPIO_OE_SET_BMSK                            0x3ffff
#define HWIO_TLMM_GPIO_OE_SET_4_GPIO_OE_SET_SHFT                                0x0


#endif /* __HALGPIOINTHWIO_H__ */
