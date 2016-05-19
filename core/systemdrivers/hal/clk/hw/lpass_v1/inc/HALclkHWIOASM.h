#ifndef __HALCLKHWIOASM_H__
#define __HALCLKHWIOASM_H__
/*
===========================================================================
*/
/**
  @file HALclkHWIOASM.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    LPASS_LPASS_CC_REG
    LPASS_QDSP6SS_PUB

  'Include' filters applied: <none>
  'Exclude' filters applied: TSENS ACR RPU RESERVED 
*/
/*
  ===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/inc/HALclkHWIOASM.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*
 * HWIO base definitions
 */
#define LPASS_BASE                 LPASS_BASE_PHYS
#define LPASS_BASE_PHYS            0xFE000000
#define LPASS_LPASS_BASE           LPASS_BASE
#define LPASS_BASE_SIZE            0x00300000
       
#define CORE_TOP_CSR_BASE                                           0xfd480000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00030000


#define TCSR_TCSR_REGS_REG_BASE                                                                (CORE_TOP_CSR_BASE      + 0x00020000)
#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                                     0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN          \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, HWIO_TCSR_SOC_HW_VERSION_RMSK)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                       0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                             0x1c
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                        0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                             0x10
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                           0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                              0x8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                             0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                              0x0


/*----------------------------------------------------------------------------
 * MODULE: LPASS_LPASS_CC_REG
 *--------------------------------------------------------------------------*/

#define LPASS_LPASS_CC_REG_REG_BASE                                                         (LPASS_BASE      + 0x00000000)
#define LPASS_LPASS_CC_REG_REG_BASE_OFFS                                                    0x00000000

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS31_22_BMSK                                 0xffc00000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS31_22_SHFT                                       0x16
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                  0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                      0x15
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                    0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                        0x14
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK                                       0xfc000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT                                           0xe
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_BMSK                                        0x3f00
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_SHFT                                           0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_BMSK                                         0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_SHFT                                          0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_BMSK                                              0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_SHFT                                              0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_BMSK                                              0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_SHFT                                              0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_BMSK                                             0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_SHFT                                             0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_BMSK                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_SHFT                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_RMSK                                                            0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_BMSK                                                        0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_PLL_M_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_M_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_M_RMSK                                                         0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_ADDR, HWIO_LPASS_LPAAUDIO_PLL_M_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_M_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_M_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_M_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_M_VAL_BMSK                                                     0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_VAL_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_PLL_N_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_N_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_N_RMSK                                                         0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_ADDR, HWIO_LPASS_LPAAUDIO_PLL_N_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_N_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_N_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_N_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_N_VAL_BMSK                                                     0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_VAL_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                             0xfe000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                   0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_MN_EN_BMSK                                          0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_MN_EN_SHFT                                               0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                               0xc00000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                   0x16
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_VCO_SEL_BMSK                                         0x300000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_VCO_SEL_SHFT                                             0x14
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                                0xf8000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                                    0xf
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                     0x7000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                        0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                  0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                    0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                     0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                       0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_BMSK                                          0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_SHFT                                           0x7
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_DIFF_90_BMSK                                      0x40
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_DIFF_90_SHFT                                       0x6
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_DIFF_0_BMSK                                       0x20
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_DIFF_0_SHFT                                        0x5
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                      0x10
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                       0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                      0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                      0x3
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                       0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                       0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                        0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                        0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                       0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                             0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_24_BMSK                           0xff000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_24_SHFT                                 0x18
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                     0xc00000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                         0x16
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ICP_DIV_BMSK                                       0x300000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ICP_DIV_SHFT                                           0x14
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IREG_DIV_BMSK                                       0xc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IREG_DIV_SHFT                                          0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS17_16_BMSK                              0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS17_16_SHFT                                 0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_VREF_REF_MODE_BMSK                                   0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_VREF_REF_MODE_SHFT                                      0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_VCO_REF_MODE_BMSK                                    0x4000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_VCO_REF_MODE_SHFT                                       0xe
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CFG_LOCKDET_BMSK                                     0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CFG_LOCKDET_SHFT                                        0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                      0x800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                        0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_COARSE_GM_BMSK                                        0x600
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_COARSE_GM_SHFT                                          0x9
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_LOOP_ZERO_BMSK                                 0x100
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_LOOP_ZERO_SHFT                                   0x8
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_LOOP_MODE_BMSK                                  0x80
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_LOOP_MODE_SHFT                                   0x7
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_RESISTOR_BMSK                                   0x60
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILTER_RESISTOR_SHFT                                    0x5
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_GMC_SLEW_MODE_BMSK                                     0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_GMC_SLEW_MODE_SHFT                                      0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS3_0_BMSK                                    0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS3_0_SHFT                                    0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_21_BMSK                             0xffe00000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_21_SHFT                                   0x15
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NGEN_CFG_BMSK                                        0x1c0000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NGEN_CFG_SHFT                                            0x12
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NGEN_EN_BMSK                                          0x20000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NGEN_EN_SHFT                                             0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NMOSC_FREQ_CTRL_BMSK                                  0x18000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NMOSC_FREQ_CTRL_SHFT                                      0xf
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NMOSC_EN_BMSK                                          0x4000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_NMOSC_EN_SHFT                                             0xe
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_FORCE_PFD_UP_BMSK                                      0x2000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_FORCE_PFD_UP_SHFT                                         0xd
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_FORCE_PFD_DOWN_BMSK                                    0x1000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_FORCE_PFD_DOWN_SHFT                                       0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                       0x800
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                         0xb
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ICP_TST_EN_BMSK                                         0x400
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ICP_TST_EN_SHFT                                           0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ICP_EXT_SEL_BMSK                                        0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ICP_EXT_SEL_SHFT                                          0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                          0x180
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                            0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                         0x40
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                          0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                          0x30
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                           0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_BMSK                                           0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_SHFT                                           0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                            0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                            0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                            0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                    0x3ffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACTIVE_FLAG_BMSK                                    0x20000
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACTIVE_FLAG_SHFT                                       0x11
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_LOCK_DET_BMSK                                       0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_LOCK_DET_SHFT                                          0x10
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_D_BMSK                                               0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_D_SHFT                                                  0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_RMSK                                                   0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_LPAAUDIO_PLL_CLK_SRC_SEL_BMSK                          0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_LPAAUDIO_PLL_CLK_SRC_SEL_SHFT                          0x0

#define HWIO_LPASS_LPAQ6_PLL_MODE_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001000)
#define HWIO_LPASS_LPAQ6_PLL_MODE_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_LPAQ6_PLL_MODE_RMSK                                                      0xffffffff
#define HWIO_LPASS_LPAQ6_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_MODE_ADDR, HWIO_LPASS_LPAQ6_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_MODE_IN)
#define HWIO_LPASS_LPAQ6_PLL_MODE_RESERVE_BITS31_22_BMSK                                    0xffc00000
#define HWIO_LPASS_LPAQ6_PLL_MODE_RESERVE_BITS31_22_SHFT                                          0x16
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                     0x200000
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                         0x15
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                       0x100000
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                           0x14
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_BIAS_COUNT_BMSK                                          0xfc000
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_BIAS_COUNT_SHFT                                              0xe
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_LOCK_COUNT_BMSK                                           0x3f00
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_LOCK_COUNT_SHFT                                              0x8
#define HWIO_LPASS_LPAQ6_PLL_MODE_RESERVE_BITS7_4_BMSK                                            0xf0
#define HWIO_LPASS_LPAQ6_PLL_MODE_RESERVE_BITS7_4_SHFT                                             0x4
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_PLLTEST_BMSK                                                 0x8
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_PLLTEST_SHFT                                                 0x3
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_RESET_N_BMSK                                                 0x4
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_RESET_N_SHFT                                                 0x2
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_BYPASSNL_BMSK                                                0x2
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_BYPASSNL_SHFT                                                0x1
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_OUTCTRL_BMSK                                                 0x1
#define HWIO_LPASS_LPAQ6_PLL_MODE_PLL_OUTCTRL_SHFT                                                 0x0

#define HWIO_LPASS_LPAQ6_PLL_L_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAQ6_PLL_L_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_LPAQ6_PLL_L_RMSK                                                               0xff
#define HWIO_LPASS_LPAQ6_PLL_L_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_L_ADDR, HWIO_LPASS_LPAQ6_PLL_L_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_L_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_L_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_L_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_L_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_L_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_L_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_L_IN)
#define HWIO_LPASS_LPAQ6_PLL_L_VAL_BMSK                                                           0xff
#define HWIO_LPASS_LPAQ6_PLL_L_VAL_SHFT                                                            0x0

#define HWIO_LPASS_LPAQ6_PLL_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAQ6_PLL_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_LPAQ6_PLL_M_RMSK                                                            0x7ffff
#define HWIO_LPASS_LPAQ6_PLL_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_M_ADDR, HWIO_LPASS_LPAQ6_PLL_M_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_M_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_M_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_M_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_M_IN)
#define HWIO_LPASS_LPAQ6_PLL_M_VAL_BMSK                                                        0x7ffff
#define HWIO_LPASS_LPAQ6_PLL_M_VAL_SHFT                                                            0x0

#define HWIO_LPASS_LPAQ6_PLL_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAQ6_PLL_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000100c)
#define HWIO_LPASS_LPAQ6_PLL_N_RMSK                                                            0x7ffff
#define HWIO_LPASS_LPAQ6_PLL_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_N_ADDR, HWIO_LPASS_LPAQ6_PLL_N_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_N_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_N_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_N_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_N_IN)
#define HWIO_LPASS_LPAQ6_PLL_N_VAL_BMSK                                                        0x7ffff
#define HWIO_LPASS_LPAQ6_PLL_N_VAL_SHFT                                                            0x0

#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RMSK                                                  0xffffffff
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAQ6_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                                0xfe000000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                      0x19
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_MN_EN_BMSK                                             0x1000000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_MN_EN_SHFT                                                  0x18
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                                  0xc00000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                      0x16
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_VCO_SEL_BMSK                                            0x300000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_VCO_SEL_SHFT                                                0x14
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                                   0xf8000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                                       0xf
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                        0x7000
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                           0xc
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                     0xc00
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                       0xa
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                        0x300
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                          0x8
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_OUTPUT_INV_BMSK                                             0x80
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_OUTPUT_INV_SHFT                                              0x7
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_DIFF_90_BMSK                                         0x40
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_DIFF_90_SHFT                                          0x6
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_DIFF_0_BMSK                                          0x20
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_DIFF_0_SHFT                                           0x5
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                         0x10
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                          0x4
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                         0x8
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                         0x3
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                          0x4
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                          0x2
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                           0x2
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                           0x1
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                          0x1
#define HWIO_LPASS_LPAQ6_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                          0x0

#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RMSK                                                0xffffffff
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS31_24_BMSK                              0xff000000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS31_24_SHFT                                    0x18
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                        0xc00000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                            0x16
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ICP_DIV_BMSK                                          0x300000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_ICP_DIV_SHFT                                              0x14
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_IREG_DIV_BMSK                                          0xc0000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_IREG_DIV_SHFT                                             0x12
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS17_16_BMSK                                 0x30000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS17_16_SHFT                                    0x10
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_VREF_REF_MODE_BMSK                                      0x8000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_VREF_REF_MODE_SHFT                                         0xf
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_VCO_REF_MODE_BMSK                                       0x4000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_VCO_REF_MODE_SHFT                                          0xe
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_CFG_LOCKDET_BMSK                                        0x3000
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_CFG_LOCKDET_SHFT                                           0xc
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                         0x800
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                           0xb
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_COARSE_GM_BMSK                                           0x600
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_COARSE_GM_SHFT                                             0x9
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_LOOP_ZERO_BMSK                                    0x100
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_LOOP_ZERO_SHFT                                      0x8
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_LOOP_MODE_BMSK                                     0x80
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_LOOP_MODE_SHFT                                      0x7
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_RESISTOR_BMSK                                      0x60
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_FILTER_RESISTOR_SHFT                                       0x5
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_GMC_SLEW_MODE_BMSK                                        0x10
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_GMC_SLEW_MODE_SHFT                                         0x4
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS3_0_BMSK                                       0xf
#define HWIO_LPASS_LPAQ6_PLL_CONFIG_CTL_RESERVE_BITS3_0_SHFT                                       0x0

#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001018)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_RMSK                                                  0xffffffff
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAQ6_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAQ6_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_RESERVE_BITS31_21_BMSK                                0xffe00000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_RESERVE_BITS31_21_SHFT                                      0x15
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NGEN_CFG_BMSK                                           0x1c0000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NGEN_CFG_SHFT                                               0x12
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NGEN_EN_BMSK                                             0x20000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NGEN_EN_SHFT                                                0x11
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NMOSC_FREQ_CTRL_BMSK                                     0x18000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NMOSC_FREQ_CTRL_SHFT                                         0xf
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NMOSC_EN_BMSK                                             0x4000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_NMOSC_EN_SHFT                                                0xe
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_FORCE_PFD_UP_BMSK                                         0x2000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_FORCE_PFD_UP_SHFT                                            0xd
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_FORCE_PFD_DOWN_BMSK                                       0x1000
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_FORCE_PFD_DOWN_SHFT                                          0xc
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                          0x800
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                            0xb
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ICP_TST_EN_BMSK                                            0x400
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ICP_TST_EN_SHFT                                              0xa
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ICP_EXT_SEL_BMSK                                           0x200
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ICP_EXT_SEL_SHFT                                             0x9
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_DTEST_SEL_BMSK                                             0x180
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_DTEST_SEL_SHFT                                               0x7
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                            0x40
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                             0x6
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST1_SEL_BMSK                                             0x30
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST1_SEL_SHFT                                              0x4
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST0_SEL_BMSK                                              0xc
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST0_SEL_SHFT                                              0x2
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST1_EN_BMSK                                               0x2
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST1_EN_SHFT                                               0x1
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST0_EN_BMSK                                               0x1
#define HWIO_LPASS_LPAQ6_PLL_TEST_CTL_ATEST0_EN_SHFT                                               0x0

#define HWIO_LPASS_LPAQ6_PLL_STATUS_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAQ6_PLL_STATUS_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000101c)
#define HWIO_LPASS_LPAQ6_PLL_STATUS_RMSK                                                       0x3ffff
#define HWIO_LPASS_LPAQ6_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_STATUS_ADDR, HWIO_LPASS_LPAQ6_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAQ6_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAQ6_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_ACTIVE_FLAG_BMSK                                       0x20000
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_ACTIVE_FLAG_SHFT                                          0x11
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_LOCK_DET_BMSK                                          0x10000
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_LOCK_DET_SHFT                                             0x10
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_D_BMSK                                                  0xffff
#define HWIO_LPASS_LPAQ6_PLL_STATUS_PLL_D_SHFT                                                     0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00002000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK                                                          0x3
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_APPS_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6_PLL_BMSK                                                   0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6_PLL_SHFT                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPA_PLL_BMSK                                                  0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPA_PLL_SHFT                                                  0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK                                                       0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6_PLL_BMSK                                                0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6_PLL_SHFT                                                0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPA_PLL_BMSK                                               0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPA_PLL_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004000)
#define HWIO_LPASS_AUDIO_CORE_BCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_LPASS_AUDIO_CORE_BCR_RMSK                                                      0x80000007
#define HWIO_LPASS_AUDIO_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_BMSK                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_SHFT                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_BMSK                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_SHFT                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00005000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK                                                   0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_SHFT                                                 0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006000)
#define HWIO_LPASS_Q6SS_BCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_Q6SS_BCR_RMSK                                                            0x80000003
#define HWIO_LPASS_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, HWIO_LPASS_Q6SS_BCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_IN)
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_BMSK                                                 0x80000000
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_SHFT                                                       0x1f
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_BMSK                                                            0x2
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_SHFT                                                            0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_BMSK                                                          0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_SHFT                                                          0x0

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK                                                   0x81ff7ff3
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_DIV_BMSK                                            0x1ff0000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_DIV_SHFT                                                 0x10
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                                     0x4000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                        0xe
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                   0x2000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                      0xd
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                  0x1000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                     0xc
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_WAKEUP_BMSK                                                 0xf00
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_WAKEUP_SHFT                                                   0x8
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_SLEEP_BMSK                                                   0xf0
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_SLEEP_SHFT                                                    0x4
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK                                                    0xf8ffffff
#define HWIO_LPASS_AUDIO_CORE_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_BMSK                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_SHFT                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_BMSK                                         0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_SHFT                                               0x1b
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_BMSK                                         0xf00000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_SHFT                                             0x14
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_BMSK                                           0xf0000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_SHFT                                              0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_BMSK                                           0xf000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_SHFT                                              0xc
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_BMSK                                        0x800
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_SHFT                                          0xb
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_BMSK                                                 0x400
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_SHFT                                                   0xa
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_BMSK                                                    0x200
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_SHFT                                                      0x9
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_BMSK                                                  0x100
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_SHFT                                                    0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_BMSK                                                  0x80
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_SHFT                                                   0x7
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_BMSK                                                   0x40
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_SHFT                                                    0x6
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_BMSK                                                 0x20
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_SHFT                                                  0x5
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_BMSK                                              0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_BMSK                                                   0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_SHFT                                                   0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_BMSK                                               0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_SHFT                                               0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_BMSK                                               0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_MIDI_CMD_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008000)
#define HWIO_LPASS_MIDI_CMD_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_MIDI_CMD_RCGR_RMSK                                                       0x800000f3
#define HWIO_LPASS_MIDI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_MIDI_CMD_RCGR_ADDR, HWIO_LPASS_MIDI_CMD_RCGR_RMSK)
#define HWIO_LPASS_MIDI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_MIDI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_MIDI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_MIDI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_MIDI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_MIDI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_MIDI_CMD_RCGR_IN)
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_D_BMSK                                                     0x80
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_D_SHFT                                                      0x7
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_N_BMSK                                                     0x40
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_N_SHFT                                                      0x6
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_M_BMSK                                                     0x20
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_M_SHFT                                                      0x5
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                              0x10
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                               0x4
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_EN_BMSK                                                      0x2
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_EN_SHFT                                                      0x1
#define HWIO_LPASS_MIDI_CMD_RCGR_UPDATE_BMSK                                                       0x1
#define HWIO_LPASS_MIDI_CMD_RCGR_UPDATE_SHFT                                                       0x0

#define HWIO_LPASS_MIDI_CFG_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008004)
#define HWIO_LPASS_MIDI_CFG_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_MIDI_CFG_RCGR_RMSK                                                           0x371f
#define HWIO_LPASS_MIDI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_MIDI_CFG_RCGR_ADDR, HWIO_LPASS_MIDI_CFG_RCGR_RMSK)
#define HWIO_LPASS_MIDI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_MIDI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_MIDI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_MIDI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_MIDI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_MIDI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_MIDI_CFG_RCGR_IN)
#define HWIO_LPASS_MIDI_CFG_RCGR_MODE_BMSK                                                      0x3000
#define HWIO_LPASS_MIDI_CFG_RCGR_MODE_SHFT                                                         0xc
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_SEL_BMSK                                                    0x700
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_SEL_SHFT                                                      0x8
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_DIV_BMSK                                                     0x1f
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_DIV_SHFT                                                      0x0

#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008014)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008014)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008018)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008018)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK                                                 0x800000f3
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_SHFT                                              0x1f
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_BMSK                                               0x80
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_SHFT                                                0x7
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_BMSK                                               0x40
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_SHFT                                                0x6
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_BMSK                                               0x20
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_SHFT                                                0x5
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                        0x10
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                         0x4
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_BMSK                                                0x2
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_SHFT                                                0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_BMSK                                                 0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK                                                     0x371f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_BMSK                                                0x3000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_SHFT                                                   0xc
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_BMSK                                              0x700
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_SHFT                                                0x8
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_BMSK                                               0x1f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_SPKR_M_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a008)
#define HWIO_LPASS_LPAIF_SPKR_M_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a008)
#define HWIO_LPASS_LPAIF_SPKR_M_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_SPKR_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, HWIO_LPASS_LPAIF_SPKR_M_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_M_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_M_IN)
#define HWIO_LPASS_LPAIF_SPKR_M_M_BMSK                                                            0xff
#define HWIO_LPASS_LPAIF_SPKR_M_M_SHFT                                                             0x0

#define HWIO_LPASS_LPAIF_SPKR_N_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a00c)
#define HWIO_LPASS_LPAIF_SPKR_N_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a00c)
#define HWIO_LPASS_LPAIF_SPKR_N_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_SPKR_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, HWIO_LPASS_LPAIF_SPKR_N_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_N_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_N_IN)
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_BMSK                                                0xff
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_SPKR_D_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a010)
#define HWIO_LPASS_LPAIF_SPKR_D_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a010)
#define HWIO_LPASS_LPAIF_SPKR_D_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_SPKR_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, HWIO_LPASS_LPAIF_SPKR_D_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_D_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_D_IN)
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_BMSK                                                       0xff
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OFFS                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK                                0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_BMSK                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_SHFT                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_DIV_BMSK                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_DIV_SHFT                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                  0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                     0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                   0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK               0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                  0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_WAKEUP_BMSK                              0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_WAKEUP_SHFT                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_SLEEP_BMSK                                0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_SLEEP_SHFT                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_BMSK                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_SHFT                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_BMSK                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_SHFT                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OFFS                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_BMSK                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_SHFT                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_BMSK                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_SHFT                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_WAKEUP_BMSK                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_WAKEUP_SHFT                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_SLEEP_BMSK                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_SLEEP_SHFT                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_BMSK                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_SHFT                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OFFS                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_BMSK                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_SHFT                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_DIV_BMSK                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_DIV_SHFT                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_WAKEUP_BMSK                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_WAKEUP_SHFT                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_SLEEP_BMSK                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_SLEEP_SHFT                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_BMSK                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_SHFT                           0x0

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK                                                  0x800000f3
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_SHFT                                               0x1f
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_BMSK                                                0x80
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_SHFT                                                 0x7
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_BMSK                                                0x40
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_SHFT                                                 0x6
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_BMSK                                                0x20
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_SHFT                                                 0x5
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                         0x10
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                          0x4
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_BMSK                                                 0x2
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_SHFT                                                 0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_BMSK                                                  0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK                                                      0x371f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_BMSK                                                 0x3000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_SHFT                                                    0xc
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_BMSK                                               0x700
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_SHFT                                                 0x8
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_BMSK                                                0x1f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b008)
#define HWIO_LPASS_LPAIF_PRI_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b008)
#define HWIO_LPASS_LPAIF_PRI_M_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_PRI_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, HWIO_LPASS_LPAIF_PRI_M_RMSK)
#define HWIO_LPASS_LPAIF_PRI_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_M_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_M_IN)
#define HWIO_LPASS_LPAIF_PRI_M_M_BMSK                                                             0xff
#define HWIO_LPASS_LPAIF_PRI_M_M_SHFT                                                              0x0

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b00c)
#define HWIO_LPASS_LPAIF_PRI_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b00c)
#define HWIO_LPASS_LPAIF_PRI_N_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_PRI_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, HWIO_LPASS_LPAIF_PRI_N_RMSK)
#define HWIO_LPASS_LPAIF_PRI_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_N_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_N_IN)
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_BMSK                                                 0xff
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b010)
#define HWIO_LPASS_LPAIF_PRI_D_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b010)
#define HWIO_LPASS_LPAIF_PRI_D_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_PRI_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, HWIO_LPASS_LPAIF_PRI_D_RMSK)
#define HWIO_LPASS_LPAIF_PRI_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_D_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_D_IN)
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_BMSK                                                        0xff
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK                                       0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_DIV_BMSK                                0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_DIV_SHFT                                     0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                         0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                            0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                       0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                          0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                      0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                         0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_WAKEUP_BMSK                                     0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_WAKEUP_SHFT                                       0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_SLEEP_BMSK                                       0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_SLEEP_SHFT                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_BMSK                                       0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_SHFT                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK                                                  0x800000f3
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_SHFT                                               0x1f
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_BMSK                                                0x80
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_SHFT                                                 0x7
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_BMSK                                                0x40
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_SHFT                                                 0x6
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_BMSK                                                0x20
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_SHFT                                                 0x5
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                         0x10
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                          0x4
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_BMSK                                                 0x2
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_SHFT                                                 0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_BMSK                                                  0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK                                                      0x371f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_BMSK                                                 0x3000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_SHFT                                                    0xc
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_BMSK                                               0x700
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_SHFT                                                 0x8
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_BMSK                                                0x1f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c008)
#define HWIO_LPASS_LPAIF_SEC_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c008)
#define HWIO_LPASS_LPAIF_SEC_M_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_SEC_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, HWIO_LPASS_LPAIF_SEC_M_RMSK)
#define HWIO_LPASS_LPAIF_SEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_M_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_M_IN)
#define HWIO_LPASS_LPAIF_SEC_M_M_BMSK                                                             0xff
#define HWIO_LPASS_LPAIF_SEC_M_M_SHFT                                                              0x0

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c00c)
#define HWIO_LPASS_LPAIF_SEC_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c00c)
#define HWIO_LPASS_LPAIF_SEC_N_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_SEC_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, HWIO_LPASS_LPAIF_SEC_N_RMSK)
#define HWIO_LPASS_LPAIF_SEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_N_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_N_IN)
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_BMSK                                                 0xff
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c010)
#define HWIO_LPASS_LPAIF_SEC_D_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c010)
#define HWIO_LPASS_LPAIF_SEC_D_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_SEC_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, HWIO_LPASS_LPAIF_SEC_D_RMSK)
#define HWIO_LPASS_LPAIF_SEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_D_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_D_IN)
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_BMSK                                                        0xff
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK                                       0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_DIV_BMSK                                0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_DIV_SHFT                                     0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                         0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                            0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                       0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                          0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                      0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                         0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_WAKEUP_BMSK                                     0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_WAKEUP_SHFT                                       0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_SLEEP_BMSK                                       0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_SLEEP_SHFT                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_BMSK                                       0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_SHFT                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK                                                  0x800000f3
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_SHFT                                               0x1f
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_BMSK                                                0x80
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_SHFT                                                 0x7
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_BMSK                                                0x40
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_SHFT                                                 0x6
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_BMSK                                                0x20
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_SHFT                                                 0x5
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                         0x10
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                          0x4
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_BMSK                                                 0x2
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_SHFT                                                 0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_BMSK                                                  0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK                                                      0x371f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_BMSK                                                 0x3000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_SHFT                                                    0xc
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_BMSK                                               0x700
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_SHFT                                                 0x8
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_BMSK                                                0x1f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d008)
#define HWIO_LPASS_LPAIF_TER_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d008)
#define HWIO_LPASS_LPAIF_TER_M_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_TER_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, HWIO_LPASS_LPAIF_TER_M_RMSK)
#define HWIO_LPASS_LPAIF_TER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_M_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_M_ADDR,m,v,HWIO_LPASS_LPAIF_TER_M_IN)
#define HWIO_LPASS_LPAIF_TER_M_M_BMSK                                                             0xff
#define HWIO_LPASS_LPAIF_TER_M_M_SHFT                                                              0x0

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d00c)
#define HWIO_LPASS_LPAIF_TER_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d00c)
#define HWIO_LPASS_LPAIF_TER_N_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_TER_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, HWIO_LPASS_LPAIF_TER_N_RMSK)
#define HWIO_LPASS_LPAIF_TER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_N_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_N_ADDR,m,v,HWIO_LPASS_LPAIF_TER_N_IN)
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_BMSK                                                 0xff
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d010)
#define HWIO_LPASS_LPAIF_TER_D_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d010)
#define HWIO_LPASS_LPAIF_TER_D_RMSK                                                               0xff
#define HWIO_LPASS_LPAIF_TER_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, HWIO_LPASS_LPAIF_TER_D_RMSK)
#define HWIO_LPASS_LPAIF_TER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_D_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_D_ADDR,m,v,HWIO_LPASS_LPAIF_TER_D_IN)
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_BMSK                                                        0xff
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK                                       0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_DIV_BMSK                                0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_DIV_SHFT                                     0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                         0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                            0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                       0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                          0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                      0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                         0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_WAKEUP_BMSK                                     0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_WAKEUP_SHFT                                       0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_SLEEP_BMSK                                       0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_SLEEP_SHFT                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_BMSK                                       0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_SHFT                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK                                                 0x800000f3
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_SHFT                                              0x1f
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_BMSK                                               0x80
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_SHFT                                                0x7
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_BMSK                                               0x40
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_SHFT                                                0x6
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_BMSK                                               0x20
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_SHFT                                                0x5
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                        0x10
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                         0x4
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_BMSK                                                0x2
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_SHFT                                                0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_BMSK                                                 0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK                                                     0x371f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_BMSK                                                0x3000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_SHFT                                                   0xc
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_BMSK                                              0x700
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_SHFT                                                0x8
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_BMSK                                               0x1f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e008)
#define HWIO_LPASS_LPAIF_QUAD_M_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e008)
#define HWIO_LPASS_LPAIF_QUAD_M_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_QUAD_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, HWIO_LPASS_LPAIF_QUAD_M_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_M_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_M_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_M_IN)
#define HWIO_LPASS_LPAIF_QUAD_M_M_BMSK                                                            0xff
#define HWIO_LPASS_LPAIF_QUAD_M_M_SHFT                                                             0x0

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e00c)
#define HWIO_LPASS_LPAIF_QUAD_N_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e00c)
#define HWIO_LPASS_LPAIF_QUAD_N_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_QUAD_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, HWIO_LPASS_LPAIF_QUAD_N_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_N_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_N_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_N_IN)
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_BMSK                                                0xff
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e010)
#define HWIO_LPASS_LPAIF_QUAD_D_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e010)
#define HWIO_LPASS_LPAIF_QUAD_D_RMSK                                                              0xff
#define HWIO_LPASS_LPAIF_QUAD_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, HWIO_LPASS_LPAIF_QUAD_D_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_D_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_D_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_D_IN)
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_BMSK                                                       0xff
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK                                     0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_BMSK                              0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_SHFT                                   0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                       0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                          0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                     0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                        0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                    0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                       0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_WAKEUP_BMSK                                   0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_WAKEUP_SHFT                                     0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_SLEEP_BMSK                                     0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_SLEEP_SHFT                                      0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK                                     0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_DIV_BMSK                              0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_DIV_SHFT                                   0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                       0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                          0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                     0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                        0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                    0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                       0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_WAKEUP_BMSK                                   0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_WAKEUP_SHFT                                     0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_SLEEP_BMSK                                     0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_SLEEP_SHFT                                      0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f000)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f000)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_RMSK                                                 0x800000f3
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_OFF_SHFT                                              0x1f
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_D_BMSK                                               0x80
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_D_SHFT                                                0x7
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_N_BMSK                                               0x40
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_N_SHFT                                                0x6
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_M_BMSK                                               0x20
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_M_SHFT                                                0x5
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                        0x10
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                         0x4
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_EN_BMSK                                                0x2
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_EN_SHFT                                                0x1
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_UPDATE_BMSK                                                 0x1
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_UPDATE_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f004)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f004)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_RMSK                                                     0x371f
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_MODE_BMSK                                                0x3000
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_MODE_SHFT                                                   0xc
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_SEL_BMSK                                              0x700
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_SEL_SHFT                                                0x8
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_DIV_BMSK                                               0x1f
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_DIV_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_PCM0_M_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f008)
#define HWIO_LPASS_LPAIF_PCM0_M_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f008)
#define HWIO_LPASS_LPAIF_PCM0_M_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM0_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_M_ADDR, HWIO_LPASS_LPAIF_PCM0_M_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_M_IN)
#define HWIO_LPASS_LPAIF_PCM0_M_M_BMSK                                                          0xffff
#define HWIO_LPASS_LPAIF_PCM0_M_M_SHFT                                                             0x0

#define HWIO_LPASS_LPAIF_PCM0_N_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f00c)
#define HWIO_LPASS_LPAIF_PCM0_N_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f00c)
#define HWIO_LPASS_LPAIF_PCM0_N_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM0_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_N_ADDR, HWIO_LPASS_LPAIF_PCM0_N_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_N_IN)
#define HWIO_LPASS_LPAIF_PCM0_N_NOT_N_MINUS_M_BMSK                                              0xffff
#define HWIO_LPASS_LPAIF_PCM0_N_NOT_N_MINUS_M_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_PCM0_D_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f010)
#define HWIO_LPASS_LPAIF_PCM0_D_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f010)
#define HWIO_LPASS_LPAIF_PCM0_D_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM0_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_D_ADDR, HWIO_LPASS_LPAIF_PCM0_D_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_D_IN)
#define HWIO_LPASS_LPAIF_PCM0_D_NOT_2D_BMSK                                                     0xffff
#define HWIO_LPASS_LPAIF_PCM0_D_NOT_2D_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_RMSK                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_RMSK                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010000)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_RMSK                                                 0x800000f3
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_OFF_SHFT                                              0x1f
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_D_BMSK                                               0x80
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_D_SHFT                                                0x7
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_N_BMSK                                               0x40
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_N_SHFT                                                0x6
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_M_BMSK                                               0x20
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_M_SHFT                                                0x5
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                        0x10
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                         0x4
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_EN_BMSK                                                0x2
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_EN_SHFT                                                0x1
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_UPDATE_BMSK                                                 0x1
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_UPDATE_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010004)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_RMSK                                                     0x371f
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_MODE_BMSK                                                0x3000
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_MODE_SHFT                                                   0xc
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_SEL_BMSK                                              0x700
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_SEL_SHFT                                                0x8
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_DIV_BMSK                                               0x1f
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_DIV_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_PCM1_M_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010008)
#define HWIO_LPASS_LPAIF_PCM1_M_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010008)
#define HWIO_LPASS_LPAIF_PCM1_M_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM1_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_M_ADDR, HWIO_LPASS_LPAIF_PCM1_M_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_M_IN)
#define HWIO_LPASS_LPAIF_PCM1_M_M_BMSK                                                          0xffff
#define HWIO_LPASS_LPAIF_PCM1_M_M_SHFT                                                             0x0

#define HWIO_LPASS_LPAIF_PCM1_N_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001000c)
#define HWIO_LPASS_LPAIF_PCM1_N_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001000c)
#define HWIO_LPASS_LPAIF_PCM1_N_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM1_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_N_ADDR, HWIO_LPASS_LPAIF_PCM1_N_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_N_IN)
#define HWIO_LPASS_LPAIF_PCM1_N_NOT_N_MINUS_M_BMSK                                              0xffff
#define HWIO_LPASS_LPAIF_PCM1_N_NOT_N_MINUS_M_SHFT                                                 0x0

#define HWIO_LPASS_LPAIF_PCM1_D_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010010)
#define HWIO_LPASS_LPAIF_PCM1_D_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010010)
#define HWIO_LPASS_LPAIF_PCM1_D_RMSK                                                            0xffff
#define HWIO_LPASS_LPAIF_PCM1_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_D_ADDR, HWIO_LPASS_LPAIF_PCM1_D_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_D_IN)
#define HWIO_LPASS_LPAIF_PCM1_D_NOT_2D_BMSK                                                     0xffff
#define HWIO_LPASS_LPAIF_PCM1_D_NOT_2D_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_RMSK                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_RMSK                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_OFF_BMSK                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_OFF_SHFT                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_HW_CTL_BMSK                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_HW_CTL_SHFT                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK                                                  0x800000f3
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CMD_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_SHFT                                               0x1f
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_BMSK                                                0x80
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_SHFT                                                 0x7
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_BMSK                                                0x40
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_SHFT                                                 0x6
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_BMSK                                                0x20
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_SHFT                                                 0x5
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                         0x10
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                          0x4
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_BMSK                                                 0x2
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_SHFT                                                 0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_BMSK                                                  0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_SHFT                                                  0x0

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK                                                      0x371f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CFG_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_BMSK                                                 0x3000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_SHFT                                                    0xc
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_BMSK                                               0x700
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_SHFT                                                 0x8
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_BMSK                                                0x1f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_SHFT                                                 0x0

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011008)
#define HWIO_LPASS_RESAMPLER_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011008)
#define HWIO_LPASS_RESAMPLER_M_RMSK                                                               0xff
#define HWIO_LPASS_RESAMPLER_M_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, HWIO_LPASS_RESAMPLER_M_RMSK)
#define HWIO_LPASS_RESAMPLER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, m)
#define HWIO_LPASS_RESAMPLER_M_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_M_ADDR,v)
#define HWIO_LPASS_RESAMPLER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_M_ADDR,m,v,HWIO_LPASS_RESAMPLER_M_IN)
#define HWIO_LPASS_RESAMPLER_M_M_BMSK                                                             0xff
#define HWIO_LPASS_RESAMPLER_M_M_SHFT                                                              0x0

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001100c)
#define HWIO_LPASS_RESAMPLER_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001100c)
#define HWIO_LPASS_RESAMPLER_N_RMSK                                                               0xff
#define HWIO_LPASS_RESAMPLER_N_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, HWIO_LPASS_RESAMPLER_N_RMSK)
#define HWIO_LPASS_RESAMPLER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, m)
#define HWIO_LPASS_RESAMPLER_N_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_N_ADDR,v)
#define HWIO_LPASS_RESAMPLER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_N_ADDR,m,v,HWIO_LPASS_RESAMPLER_N_IN)
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_BMSK                                                 0xff
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_SHFT                                                  0x0

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011010)
#define HWIO_LPASS_RESAMPLER_D_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011010)
#define HWIO_LPASS_RESAMPLER_D_RMSK                                                               0xff
#define HWIO_LPASS_RESAMPLER_D_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, HWIO_LPASS_RESAMPLER_D_RMSK)
#define HWIO_LPASS_RESAMPLER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, m)
#define HWIO_LPASS_RESAMPLER_D_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_D_ADDR,v)
#define HWIO_LPASS_RESAMPLER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_D_ADDR,m,v,HWIO_LPASS_RESAMPLER_D_IN)
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_BMSK                                                        0xff
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_RMSK                                    0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_DIV_BMSK                             0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_DIV_SHFT                                  0x10
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                      0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                         0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                    0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                       0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                   0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                      0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_WAKEUP_BMSK                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_WAKEUP_SHFT                                    0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_SLEEP_BMSK                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_SLEEP_SHFT                                     0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_HW_CTL_BMSK                                    0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_HW_CTL_SHFT                                    0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_ENABLE_SHFT                                0x0

#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012000)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_RMSK                                                    0x800000f3
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                  0x80
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                   0x7
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                  0x40
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                   0x6
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                  0x20
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                   0x5
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                           0x10
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                            0x4
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                   0x2
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                   0x1
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                    0x1
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                    0x0

#define HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012004)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_RMSK                                                        0x371f
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_MODE_BMSK                                                   0x3000
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_MODE_SHFT                                                      0xc
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                  0x1f
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                   0x0

#define HWIO_LPASS_SLIMBUS_M_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012008)
#define HWIO_LPASS_SLIMBUS_M_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012008)
#define HWIO_LPASS_SLIMBUS_M_RMSK                                                                 0xff
#define HWIO_LPASS_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_M_ADDR, HWIO_LPASS_SLIMBUS_M_RMSK)
#define HWIO_LPASS_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_SLIMBUS_M_IN)
#define HWIO_LPASS_SLIMBUS_M_M_BMSK                                                               0xff
#define HWIO_LPASS_SLIMBUS_M_M_SHFT                                                                0x0

#define HWIO_LPASS_SLIMBUS_N_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001200c)
#define HWIO_LPASS_SLIMBUS_N_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001200c)
#define HWIO_LPASS_SLIMBUS_N_RMSK                                                                 0xff
#define HWIO_LPASS_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_N_ADDR, HWIO_LPASS_SLIMBUS_N_RMSK)
#define HWIO_LPASS_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_SLIMBUS_N_IN)
#define HWIO_LPASS_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                   0xff
#define HWIO_LPASS_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                    0x0

#define HWIO_LPASS_SLIMBUS_D_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012010)
#define HWIO_LPASS_SLIMBUS_D_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012010)
#define HWIO_LPASS_SLIMBUS_D_RMSK                                                                 0xff
#define HWIO_LPASS_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_D_ADDR, HWIO_LPASS_SLIMBUS_D_RMSK)
#define HWIO_LPASS_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_SLIMBUS_D_IN)
#define HWIO_LPASS_SLIMBUS_D_NOT_2D_BMSK                                                          0xff
#define HWIO_LPASS_SLIMBUS_D_NOT_2D_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK                                                0x800000f3
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_SHFT                                             0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_BMSK                                              0x80
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_SHFT                                               0x7
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_BMSK                                              0x40
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_SHFT                                               0x6
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_BMSK                                              0x20
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_SHFT                                               0x5
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                       0x10
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                        0x4
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_BMSK                                               0x2
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_SHFT                                               0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_BMSK                                                0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK                                                    0x371f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_BMSK                                               0x3000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_SHFT                                                  0xc
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_BMSK                                             0x700
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_SHFT                                               0x8
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_BMSK                                              0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_SHFT                                               0x0

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013008)
#define HWIO_LPASS_LPAIF_PCMOE_M_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013008)
#define HWIO_LPASS_LPAIF_PCMOE_M_RMSK                                                             0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, HWIO_LPASS_LPAIF_PCMOE_M_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_M_IN)
#define HWIO_LPASS_LPAIF_PCMOE_M_M_BMSK                                                           0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_M_SHFT                                                            0x0

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001300c)
#define HWIO_LPASS_LPAIF_PCMOE_N_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001300c)
#define HWIO_LPASS_LPAIF_PCMOE_N_RMSK                                                             0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, HWIO_LPASS_LPAIF_PCMOE_N_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_N_IN)
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_BMSK                                               0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_SHFT                                                0x0

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013010)
#define HWIO_LPASS_LPAIF_PCMOE_D_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013010)
#define HWIO_LPASS_LPAIF_PCMOE_D_RMSK                                                             0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, HWIO_LPASS_LPAIF_PCMOE_D_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_D_IN)
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_BMSK                                                      0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OFFS                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK                                   0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_BMSK                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_SHFT                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_DIV_BMSK                            0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_DIV_SHFT                                 0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_CORE_ON_BMSK                     0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_CORE_ON_SHFT                        0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                   0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                      0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                  0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                     0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_WAKEUP_BMSK                                 0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_WAKEUP_SHFT                                   0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_SLEEP_BMSK                                   0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_SLEEP_SHFT                                    0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_BMSK                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_SHFT                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014000)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_Q6CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR, HWIO_LPASS_Q6CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_Q6CORE_CMD_RCGR_IN)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_Q6CORE_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_Q6CORE_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014004)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_Q6CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR, HWIO_LPASS_Q6CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_Q6CORE_CFG_RCGR_IN)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_Q6CORE_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_Q6CORE_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014008)
#define HWIO_LPASS_Q6CORE_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014008)
#define HWIO_LPASS_Q6CORE_M_RMSK                                                                  0xff
#define HWIO_LPASS_Q6CORE_M_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_M_ADDR, HWIO_LPASS_Q6CORE_M_RMSK)
#define HWIO_LPASS_Q6CORE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_M_ADDR, m)
#define HWIO_LPASS_Q6CORE_M_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_M_ADDR,v)
#define HWIO_LPASS_Q6CORE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_M_ADDR,m,v,HWIO_LPASS_Q6CORE_M_IN)
#define HWIO_LPASS_Q6CORE_M_M_BMSK                                                                0xff
#define HWIO_LPASS_Q6CORE_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_Q6CORE_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001400c)
#define HWIO_LPASS_Q6CORE_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001400c)
#define HWIO_LPASS_Q6CORE_N_RMSK                                                                  0xff
#define HWIO_LPASS_Q6CORE_N_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_N_ADDR, HWIO_LPASS_Q6CORE_N_RMSK)
#define HWIO_LPASS_Q6CORE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_N_ADDR, m)
#define HWIO_LPASS_Q6CORE_N_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_N_ADDR,v)
#define HWIO_LPASS_Q6CORE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_N_ADDR,m,v,HWIO_LPASS_Q6CORE_N_IN)
#define HWIO_LPASS_Q6CORE_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_Q6CORE_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_Q6CORE_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014010)
#define HWIO_LPASS_Q6CORE_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014010)
#define HWIO_LPASS_Q6CORE_D_RMSK                                                                  0xff
#define HWIO_LPASS_Q6CORE_D_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_D_ADDR, HWIO_LPASS_Q6CORE_D_RMSK)
#define HWIO_LPASS_Q6CORE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_D_ADDR, m)
#define HWIO_LPASS_Q6CORE_D_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_D_ADDR,v)
#define HWIO_LPASS_Q6CORE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_D_ADDR,m,v,HWIO_LPASS_Q6CORE_D_IN)
#define HWIO_LPASS_Q6CORE_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_Q6CORE_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_RMSK                                                      0x800000f3
#define HWIO_LPASS_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, HWIO_LPASS_SLEEP_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CMD_RCGR_IN)
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                             0x80000000
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                   0x1f
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                    0x80
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                     0x7
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                    0x40
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                     0x6
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                    0x20
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                     0x5
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                             0x10
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                              0x4
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                     0x2
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                     0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_BMSK                                                      0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_SHFT                                                      0x0

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_RMSK                                                          0x371f
#define HWIO_LPASS_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, HWIO_LPASS_SLEEP_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CFG_RCGR_IN)
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_BMSK                                                     0x3000
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_SHFT                                                        0xc
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                   0x700
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                     0x8
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                    0x1f
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                     0x0

#define HWIO_LPASS_SPDM_CMD_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016000)
#define HWIO_LPASS_SPDM_CMD_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_SPDM_CMD_RCGR_RMSK                                                       0x800000f3
#define HWIO_LPASS_SPDM_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDM_CMD_RCGR_ADDR, HWIO_LPASS_SPDM_CMD_RCGR_RMSK)
#define HWIO_LPASS_SPDM_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDM_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SPDM_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDM_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SPDM_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDM_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SPDM_CMD_RCGR_IN)
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_D_BMSK                                                     0x80
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_D_SHFT                                                      0x7
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_N_BMSK                                                     0x40
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_N_SHFT                                                      0x6
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_M_BMSK                                                     0x20
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_M_SHFT                                                      0x5
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                              0x10
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                               0x4
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_EN_BMSK                                                      0x2
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_EN_SHFT                                                      0x1
#define HWIO_LPASS_SPDM_CMD_RCGR_UPDATE_BMSK                                                       0x1
#define HWIO_LPASS_SPDM_CMD_RCGR_UPDATE_SHFT                                                       0x0

#define HWIO_LPASS_SPDM_CFG_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016004)
#define HWIO_LPASS_SPDM_CFG_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_SPDM_CFG_RCGR_RMSK                                                           0x371f
#define HWIO_LPASS_SPDM_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDM_CFG_RCGR_ADDR, HWIO_LPASS_SPDM_CFG_RCGR_RMSK)
#define HWIO_LPASS_SPDM_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDM_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SPDM_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDM_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SPDM_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDM_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SPDM_CFG_RCGR_IN)
#define HWIO_LPASS_SPDM_CFG_RCGR_MODE_BMSK                                                      0x3000
#define HWIO_LPASS_SPDM_CFG_RCGR_MODE_SHFT                                                         0xc
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_SEL_BMSK                                                    0x700
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_SEL_SHFT                                                      0x8
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_DIV_BMSK                                                     0x1f
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_DIV_SHFT                                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016014)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017000)
#define HWIO_LPASS_XO_CMD_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_XO_CMD_RCGR_RMSK                                                         0x800000f3
#define HWIO_LPASS_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, HWIO_LPASS_XO_CMD_RCGR_RMSK)
#define HWIO_LPASS_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CMD_RCGR_ADDR,m,v,HWIO_LPASS_XO_CMD_RCGR_IN)
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_BMSK                                                       0x80
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_SHFT                                                        0x7
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_BMSK                                                       0x40
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_SHFT                                                        0x6
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_BMSK                                                       0x20
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_SHFT                                                        0x5
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                0x10
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                 0x4
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_BMSK                                                        0x2
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_SHFT                                                        0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_BMSK                                                         0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_SHFT                                                         0x0

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017004)
#define HWIO_LPASS_XO_CFG_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_XO_CFG_RCGR_RMSK                                                             0x371f
#define HWIO_LPASS_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, HWIO_LPASS_XO_CFG_RCGR_RMSK)
#define HWIO_LPASS_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CFG_RCGR_ADDR,m,v,HWIO_LPASS_XO_CFG_RCGR_IN)
#define HWIO_LPASS_XO_CFG_RCGR_MODE_BMSK                                                        0x3000
#define HWIO_LPASS_XO_CFG_RCGR_MODE_SHFT                                                           0xc
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_BMSK                                                      0x700
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_SHFT                                                        0x8
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_BMSK                                                       0x1f
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_SHFT                                                        0x0

#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018000)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_RMSK                                                  0x800000f3
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR, HWIO_LPASS_AHBFABRIC_CMD_RCGR_RMSK)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AHBFABRIC_CMD_RCGR_IN)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_OFF_SHFT                                               0x1f
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_D_BMSK                                                0x80
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_D_SHFT                                                 0x7
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_N_BMSK                                                0x40
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_N_SHFT                                                 0x6
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_M_BMSK                                                0x20
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_M_SHFT                                                 0x5
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                         0x10
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                          0x4
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_EN_BMSK                                                 0x2
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_EN_SHFT                                                 0x1
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_BMSK                                                  0x1
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_SHFT                                                  0x0

#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018004)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_RMSK                                                      0x371f
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR, HWIO_LPASS_AHBFABRIC_CFG_RCGR_RMSK)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AHBFABRIC_CFG_RCGR_IN)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_MODE_BMSK                                                 0x3000
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_MODE_SHFT                                                    0xc
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_BMSK                                               0x700
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_SHFT                                                 0x8
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_BMSK                                                0x1f
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_SHFT                                                 0x0

#define HWIO_LPASS_AHBFABRIC_M_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018008)
#define HWIO_LPASS_AHBFABRIC_M_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018008)
#define HWIO_LPASS_AHBFABRIC_M_RMSK                                                               0xff
#define HWIO_LPASS_AHBFABRIC_M_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_M_ADDR, HWIO_LPASS_AHBFABRIC_M_RMSK)
#define HWIO_LPASS_AHBFABRIC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_M_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_M_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_M_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_M_ADDR,m,v,HWIO_LPASS_AHBFABRIC_M_IN)
#define HWIO_LPASS_AHBFABRIC_M_M_BMSK                                                             0xff
#define HWIO_LPASS_AHBFABRIC_M_M_SHFT                                                              0x0

#define HWIO_LPASS_AHBFABRIC_N_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001800c)
#define HWIO_LPASS_AHBFABRIC_N_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001800c)
#define HWIO_LPASS_AHBFABRIC_N_RMSK                                                               0xff
#define HWIO_LPASS_AHBFABRIC_N_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_N_ADDR, HWIO_LPASS_AHBFABRIC_N_RMSK)
#define HWIO_LPASS_AHBFABRIC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_N_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_N_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_N_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_N_ADDR,m,v,HWIO_LPASS_AHBFABRIC_N_IN)
#define HWIO_LPASS_AHBFABRIC_N_NOT_N_MINUS_M_BMSK                                                 0xff
#define HWIO_LPASS_AHBFABRIC_N_NOT_N_MINUS_M_SHFT                                                  0x0

#define HWIO_LPASS_AHBFABRIC_D_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018010)
#define HWIO_LPASS_AHBFABRIC_D_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018010)
#define HWIO_LPASS_AHBFABRIC_D_RMSK                                                               0xff
#define HWIO_LPASS_AHBFABRIC_D_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_D_ADDR, HWIO_LPASS_AHBFABRIC_D_RMSK)
#define HWIO_LPASS_AHBFABRIC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_D_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_D_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_D_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_D_ADDR,m,v,HWIO_LPASS_AHBFABRIC_D_IN)
#define HWIO_LPASS_AHBFABRIC_D_NOT_2D_BMSK                                                        0xff
#define HWIO_LPASS_AHBFABRIC_D_NOT_2D_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_RMSK                                                 0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_DIV_BMSK                                          0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_DIV_SHFT                                               0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_CORE_ON_BMSK                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_CORE_ON_SHFT                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_WAKEUP_BMSK                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_WAKEUP_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_SLEEP_BMSK                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_SLEEP_SHFT                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001900c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001900c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a00c)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a00c)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_TCM_SLAVE_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_RMSK                                                 0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_DIV_BMSK                                          0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_DIV_SHFT                                               0x10
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                      0xe
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                    0xd
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                0x1000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                   0xc
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_WAKEUP_BMSK                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_WAKEUP_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_SLEEP_BMSK                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_SLEEP_SHFT                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_RMSK                                                 0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_DML_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DML_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_DIV_BMSK                                          0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_DIV_SHFT                                               0x10
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_CORE_ON_BMSK                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_CORE_ON_SHFT                                      0xe
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                    0xd
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                0x1000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                   0xc
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_WAKEUP_BMSK                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_WAKEUP_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_SLEEP_BMSK                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_SLEEP_SHFT                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_RMSK                                              0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_DIV_BMSK                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_DIV_SHFT                                            0x10
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_CORE_ON_BMSK                                0x4000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_CORE_ON_SHFT                                   0xe
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                              0x2000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                 0xd
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                             0x1000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                0xc
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_WAKEUP_BMSK                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_WAKEUP_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_SLEEP_BMSK                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_SLEEP_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f004)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f004)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020000)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020000)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020004)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020004)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_RMSK                                          0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_RMSK                                            0x80000003
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021004)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021004)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022000)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022000)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_RMSK                                                0x81ff7ff3
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR, HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_DIV_BMSK                                         0x1ff0000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_DIV_SHFT                                              0x10
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                                  0x4000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                                     0xe
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                0x2000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                   0xd
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                               0x1000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                  0xc
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_WAKEUP_BMSK                                              0xf00
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_WAKEUP_SHFT                                                0x8
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_SLEEP_BMSK                                                0xf0
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_SLEEP_SHFT                                                 0x4
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022004)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022004)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_RMSK                                                      0x80000003
#define HWIO_LPASS_Q6SS_AHBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBM_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBM_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_Q6SS_AHBM_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_Q6SS_AHBM_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00024000)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00024000)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_RMSK                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_Q6SS_XO_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026000)
#define HWIO_LPASS_Q6SS_XO_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026000)
#define HWIO_LPASS_Q6SS_XO_CBCR_RMSK                                                        0x81ff7ff3
#define HWIO_LPASS_Q6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_XO_CBCR_ADDR, HWIO_LPASS_Q6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_XO_CBCR_IN)
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_DIV_BMSK                                                 0x1ff0000
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_DIV_SHFT                                                      0x10
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                                          0x4000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                             0xe
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                        0x2000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                           0xd
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                       0x1000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                          0xc
#define HWIO_LPASS_Q6SS_XO_CBCR_WAKEUP_BMSK                                                      0xf00
#define HWIO_LPASS_Q6SS_XO_CBCR_WAKEUP_SHFT                                                        0x8
#define HWIO_LPASS_Q6SS_XO_CBCR_SLEEP_BMSK                                                        0xf0
#define HWIO_LPASS_Q6SS_XO_CBCR_SLEEP_SHFT                                                         0x4
#define HWIO_LPASS_Q6SS_XO_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_Q6SS_XO_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_Q6SS_SLP_CBCR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026004)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026004)
#define HWIO_LPASS_Q6SS_SLP_CBCR_RMSK                                                       0x81ff7ff3
#define HWIO_LPASS_Q6SS_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_DIV_BMSK                                                0x1ff0000
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_DIV_SHFT                                                     0x10
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                                         0x4000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                            0xe
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                       0x2000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                          0xd
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                      0x1000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                         0xc
#define HWIO_LPASS_Q6SS_SLP_CBCR_WAKEUP_BMSK                                                     0xf00
#define HWIO_LPASS_Q6SS_SLP_CBCR_WAKEUP_SHFT                                                       0x8
#define HWIO_LPASS_Q6SS_SLP_CBCR_SLEEP_BMSK                                                       0xf0
#define HWIO_LPASS_Q6SS_SLP_CBCR_SLEEP_SHFT                                                        0x4
#define HWIO_LPASS_Q6SS_SLP_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_LPASS_Q6SS_SLP_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_RMSK                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OFFS                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_RMSK                                 0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_BMSK                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_SHFT                               0x1f
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_DIV_BMSK                          0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_DIV_SHFT                               0x10
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                   0x4000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                      0xe
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                 0x2000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                    0xd
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                0x1000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                   0xc
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_WAKEUP_BMSK                               0xf00
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_WAKEUP_SHFT                                 0x8
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_SLEEP_BMSK                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_SLEEP_SHFT                                  0x4
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_HW_CTL_BMSK                                 0x2
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_HW_CTL_SHFT                                 0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_BMSK                             0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_SHFT                             0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OFFS                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_RMSK                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_BMSK                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_SHFT                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_HW_CTL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_HW_CTL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_BMSK                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_SHFT                           0x0

#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028010)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028010)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK                                                0x800000f3
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_SHFT                                             0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_BMSK                                              0x80
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_SHFT                                               0x7
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_BMSK                                              0x40
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_SHFT                                               0x6
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_BMSK                                              0x20
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_SHFT                                               0x5
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                       0x10
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                        0x4
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_BMSK                                               0x2
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_SHFT                                               0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_BMSK                                                0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_SHFT                                                0x0

#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028014)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028014)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_RMSK                                                    0x371f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_BMSK                                               0x3000
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_SHFT                                                  0xc
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_BMSK                                             0x700
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_SHFT                                               0x8
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_BMSK                                              0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_SHFT                                               0x0

#define HWIO_LPASS_SPDIFTX_BMC_M_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028018)
#define HWIO_LPASS_SPDIFTX_BMC_M_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028018)
#define HWIO_LPASS_SPDIFTX_BMC_M_RMSK                                                           0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_M_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_M_M_BMSK                                                         0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_M_SHFT                                                            0x0

#define HWIO_LPASS_SPDIFTX_BMC_N_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002801c)
#define HWIO_LPASS_SPDIFTX_BMC_N_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002801c)
#define HWIO_LPASS_SPDIFTX_BMC_N_RMSK                                                           0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_N_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_BMSK                                             0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_SHFT                                                0x0

#define HWIO_LPASS_SPDIFTX_BMC_D_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028020)
#define HWIO_LPASS_SPDIFTX_BMC_D_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028020)
#define HWIO_LPASS_SPDIFTX_BMC_D_RMSK                                                           0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_D_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_BMSK                                                    0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_SHFT                                                       0x0

#define HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028024)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028024)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_RMSK                                                    0x80000003
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028028)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028028)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_RMSK                                                   0x80000003
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR, HWIO_LPASS_SPDIFTX_AHBS_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_AHBS_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002802c)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002802c)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_RMSK                                                   0x80000003
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR, HWIO_LPASS_SPDIFTX_AHBM_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_AHBM_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_SIF_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028030)
#define HWIO_LPASS_SIF_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028030)
#define HWIO_LPASS_SIF_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_SIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SIF_CBCR_ADDR, HWIO_LPASS_SIF_CBCR_RMSK)
#define HWIO_LPASS_SIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SIF_CBCR_ADDR, m)
#define HWIO_LPASS_SIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SIF_CBCR_ADDR,v)
#define HWIO_LPASS_SIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SIF_CBCR_ADDR,m,v,HWIO_LPASS_SIF_CBCR_IN)
#define HWIO_LPASS_SIF_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_SIF_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_SIF_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_SIF_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_SIF_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_SIF_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_SIF_AHB_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028034)
#define HWIO_LPASS_SIF_AHB_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028034)
#define HWIO_LPASS_SIF_AHB_CBCR_RMSK                                                        0x80000003
#define HWIO_LPASS_SIF_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SIF_AHB_CBCR_ADDR, HWIO_LPASS_SIF_AHB_CBCR_RMSK)
#define HWIO_LPASS_SIF_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SIF_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_SIF_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SIF_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_SIF_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SIF_AHB_CBCR_ADDR,m,v,HWIO_LPASS_SIF_AHB_CBCR_IN)
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_SIF_AHB_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_SIF_AHB_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028040)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028040)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_RMSK                                                     0x80000003
#define HWIO_LPASS_HDMIRX_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR, HWIO_LPASS_HDMIRX_AHB_CBCR_RMSK)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR,m,v,HWIO_LPASS_HDMIRX_AHB_CBCR_IN)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_OFF_BMSK                                             0x80000000
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_OFF_SHFT                                                   0x1f
#define HWIO_LPASS_HDMIRX_AHB_CBCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_HDMIRX_AHB_CBCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028050)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028050)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_RMSK                                                   0x800000f3
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR, HWIO_LPASS_DIGCODEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_DIGCODEC_CMD_RCGR_IN)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_D_BMSK                                                 0x80
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_D_SHFT                                                  0x7
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_N_BMSK                                                 0x40
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_N_SHFT                                                  0x6
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_M_BMSK                                                 0x20
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_M_SHFT                                                  0x5
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028054)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028054)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_RMSK                                                       0x371f
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_MODE_BMSK                                                  0x3000
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_MODE_SHFT                                                     0xc
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_DIV_BMSK                                                 0x1f
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_DIV_SHFT                                                  0x0

#define HWIO_LPASS_DIGCODEC_M_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028058)
#define HWIO_LPASS_DIGCODEC_M_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028058)
#define HWIO_LPASS_DIGCODEC_M_RMSK                                                                0xff
#define HWIO_LPASS_DIGCODEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_M_ADDR,v)
#define HWIO_LPASS_DIGCODEC_M_M_BMSK                                                              0xff
#define HWIO_LPASS_DIGCODEC_M_M_SHFT                                                               0x0

#define HWIO_LPASS_DIGCODEC_N_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002805c)
#define HWIO_LPASS_DIGCODEC_N_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002805c)
#define HWIO_LPASS_DIGCODEC_N_RMSK                                                                0xff
#define HWIO_LPASS_DIGCODEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_N_ADDR,v)
#define HWIO_LPASS_DIGCODEC_N_NOT_N_MINUS_M_BMSK                                                  0xff
#define HWIO_LPASS_DIGCODEC_N_NOT_N_MINUS_M_SHFT                                                   0x0

#define HWIO_LPASS_DIGCODEC_D_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028060)
#define HWIO_LPASS_DIGCODEC_D_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028060)
#define HWIO_LPASS_DIGCODEC_D_RMSK                                                                0xff
#define HWIO_LPASS_DIGCODEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_D_ADDR,v)
#define HWIO_LPASS_DIGCODEC_D_NOT_2D_BMSK                                                         0xff
#define HWIO_LPASS_DIGCODEC_D_NOT_2D_SHFT                                                          0x0

#define HWIO_LPASS_DIGCODEC_CBCR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028064)
#define HWIO_LPASS_DIGCODEC_CBCR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028064)
#define HWIO_LPASS_DIGCODEC_CBCR_RMSK                                                       0x80000003
#define HWIO_LPASS_DIGCODEC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CBCR_ADDR, HWIO_LPASS_DIGCODEC_CBCR_RMSK)
#define HWIO_LPASS_DIGCODEC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CBCR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CBCR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_CBCR_ADDR,m,v,HWIO_LPASS_DIGCODEC_CBCR_IN)
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_LPASS_DIGCODEC_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_LPASS_DIGCODEC_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028068)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028068)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_RMSK                                                   0x80000003
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR, HWIO_LPASS_DIGCODEC_AHB_CBCR_RMSK)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR,m,v,HWIO_LPASS_DIGCODEC_AHB_CBCR_IN)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029000)
#define HWIO_LPASS_DBG_CLK_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029000)
#define HWIO_LPASS_DBG_CLK_RMSK                                                               0x10ffff
#define HWIO_LPASS_DBG_CLK_IN          \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, HWIO_LPASS_DBG_CLK_RMSK)
#define HWIO_LPASS_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, m)
#define HWIO_LPASS_DBG_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_DBG_CLK_ADDR,v)
#define HWIO_LPASS_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DBG_CLK_ADDR,m,v,HWIO_LPASS_DBG_CLK_IN)
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                0x100000
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                    0x14
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                 0xffff
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OFFS                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_RMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_SEL_BMSK                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_SEL_SHFT                                0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002b000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002b000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_RMSK                                           0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_I2S_PCM_SEL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_I2S_PCM_SEL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_SEL_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_SEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_RMSK                                           0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_I2S_PCM_SEL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_I2S_PCM_SEL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_SEL_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_SEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002d000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_RMSK                                           0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_I2S_PCM_SEL_BMSK                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_I2S_PCM_SEL_SHFT                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_SEL_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_SEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OFFS                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_RMSK                                          0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_I2S_PCM_SEL_BMSK                              0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_I2S_PCM_SEL_SHFT                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_SEL_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_SEL_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002f000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OFFS                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002f000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_RMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_SEL_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_SEL_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OFFS                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_RMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_SEL_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_SEL_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031000)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031000)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_RMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_EN_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_EN_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031004)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031004)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_RMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_EN_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_EN_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031008)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031008)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_RMSK                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_EN_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_EN_SHFT                                        0x0

#define HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032000)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032000)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_RMSK                                                           0x1
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR, HWIO_LPASS_Q6SS_RST_EVB_SEL_RMSK)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR, m)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR,v)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR,m,v,HWIO_LPASS_Q6SS_RST_EVB_SEL_IN)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_SEL_BMSK                                                       0x1
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_SEL_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_RST_EVB_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032004)
#define HWIO_LPASS_Q6SS_RST_EVB_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032004)
#define HWIO_LPASS_Q6SS_RST_EVB_RMSK                                                         0xffffff0
#define HWIO_LPASS_Q6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_ADDR, HWIO_LPASS_Q6SS_RST_EVB_RMSK)
#define HWIO_LPASS_Q6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_Q6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_Q6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_Q6SS_RST_EVB_IN)
#define HWIO_LPASS_Q6SS_RST_EVB_EVB_BMSK                                                     0xffffff0
#define HWIO_LPASS_Q6SS_RST_EVB_EVB_SHFT                                                           0x4

#define HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_RMSK                                                            0x7
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR, HWIO_LPASS_VFR_IRQ_MUX_CTL_RMSK)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR, m)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR,v)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR,m,v,HWIO_LPASS_VFR_IRQ_MUX_CTL_IN)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_SEL_BMSK                                                        0x7
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_SEL_SHFT                                                        0x0

#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n)                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034000 + 0x4 * (n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OFFS(n)                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034000 + 0x4 * (n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_RMSK                                         0x80010077
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_MAXn                                                  3
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n), HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_RMSK)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n), mask)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n),val)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n),mask,val,HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INI(n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_BMSK                         0x80000000
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_SHFT                               0x1f
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_BMSK                       0x10000
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_SHFT                          0x10
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_BMSK                               0x70
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_SHFT                                0x4
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_BMSK                                 0x7
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_SHFT                                 0x0

#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n)                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034010 + 0x4 * (n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OFFS(n)                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034010 + 0x4 * (n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_RMSK                                           0x80010077
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_MAXn                                                    3
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n), HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_RMSK)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n), mask)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n),val)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n),mask,val,HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INI(n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_BMSK                           0x80000000
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_SHFT                                 0x1f
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_BMSK                         0x10000
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_SHFT                            0x10
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_BMSK                                 0x70
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_SHFT                                  0x4
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_BMSK                                   0x7
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_SHFT                                   0x0

#define HWIO_LPASS_STM_MUXSEL_n_ADDR(n)                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035000 + 0x4 * (n))
#define HWIO_LPASS_STM_MUXSEL_n_OFFS(n)                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035000 + 0x4 * (n))
#define HWIO_LPASS_STM_MUXSEL_n_RMSK                                                        0x80000007
#define HWIO_LPASS_STM_MUXSEL_n_MAXn                                                                31
#define HWIO_LPASS_STM_MUXSEL_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_STM_MUXSEL_n_ADDR(n), HWIO_LPASS_STM_MUXSEL_n_RMSK)
#define HWIO_LPASS_STM_MUXSEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_STM_MUXSEL_n_ADDR(n), mask)
#define HWIO_LPASS_STM_MUXSEL_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_STM_MUXSEL_n_ADDR(n),val)
#define HWIO_LPASS_STM_MUXSEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_STM_MUXSEL_n_ADDR(n),mask,val,HWIO_LPASS_STM_MUXSEL_n_INI(n))
#define HWIO_LPASS_STM_MUXSEL_n_ENABLE_BMSK                                                 0x80000000
#define HWIO_LPASS_STM_MUXSEL_n_ENABLE_SHFT                                                       0x1f
#define HWIO_LPASS_STM_MUXSEL_n_SEL_BMSK                                                           0x7
#define HWIO_LPASS_STM_MUXSEL_n_SEL_SHFT                                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_PUB_REG_BASE                                      (LPASS_BASE      + 0x00200000)
#define LPASS_QDSP6SS_PUB_REG_BASE_OFFS                                 0x00200000

#define HWIO_LPASS_QDSP6SS_VERSION_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_RMSK                                 0xffffffff
#define HWIO_LPASS_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, HWIO_LPASS_QDSP6SS_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_BMSK                           0xf0000000
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_SHFT                                 0x1c
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_BMSK                            0xfff0000
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_SHFT                                 0x10
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_BMSK                                0xffff
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_RST_EVB_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_RMSK                                  0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, HWIO_LPASS_QDSP6SS_RST_EVB_RMSK)
#define HWIO_LPASS_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_QDSP6SS_RST_EVB_IN)
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_BMSK                              0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_SHFT                                    0x4

#define HWIO_LPASS_QDSP6SS_RESET_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_RMSK                                        0x1f7
#define HWIO_LPASS_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, HWIO_LPASS_QDSP6SS_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_RESET_IN)
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_BMSK                              0x100
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_SHFT                                0x8
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_BMSK                               0x80
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_SHFT                                0x7
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_BMSK                               0x40
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_SHFT                                0x6
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_BMSK                               0x20
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_SHFT                                0x5
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                           0x10
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                            0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                             0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                             0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK                                 0xffff0003
#define HWIO_LPASS_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                      0xff000000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                            0x18
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                         0xff0000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                             0x10
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK                                    0x30f
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                   0x200
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                     0x9
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                 0x100
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                   0x8
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                          0xc
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                          0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK                                  0x1f
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                       0x1e
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                     0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                     0x0

#define HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK                                  0xfff0007
#define HWIO_LPASS_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BG_PU_BMSK                        0x8000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BG_PU_SHFT                             0x1b
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_VREF_SEL_BMSK                     0x4000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_VREF_SEL_SHFT                          0x1a
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                       0x3000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                            0x18
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                           0xc00000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                               0x16
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK                            0x200000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                0x15
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                          0x100000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                              0x14
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                          0x80000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                             0x13
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_BMSK                      0x40000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_SHFT                         0x12
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_BMSK                     0x20000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_SHFT                        0x11
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                   0x10000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                      0x10
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                      0x7
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK                                0x3fff
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                    0x2000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                       0xd
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_BMSK                    0x1000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_SHFT                       0xc
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                     0x800
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                       0xb
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                     0x400
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                       0xa
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                0x300
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                  0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_BMSK                      0x80
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_SHFT                       0x7
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                0x60
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                 0x5
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                 0x10
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                  0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                   0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                   0x3
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                       0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                       0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                      0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                      0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                       0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_NMI_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_RMSK                                            0x3
#define HWIO_LPASS_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_NMI_ADDR,v)
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_BMSK                               0x2
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR                              (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_OFFS                              (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK                                     0x3
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                         0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                         0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK                                 0x7ffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG0_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_BMSK                        0x4000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_SHFT                             0x1a
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_BYP_LDO_EXT_BMSK                     0x2000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_BYP_LDO_EXT_SHFT                          0x19
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_BMSK                         0x1000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_SHFT                              0x18
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL2_BMSK                         0xff0000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL2_SHFT                             0x10
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_BMSK                           0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL0_BMSK                             0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL0_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK                                  0xffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG1_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_RSV2_BMSK                         0xff0000
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_RSV2_SHFT                             0x10
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_RSV1_BMSK                           0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_RSV1_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_BMSK                              0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK                                    0xffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG2_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RDAC_CTL2_BMSK                          0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RDAC_CTL2_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RDAC_CTL1_BMSK                            0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RDAC_CTL1_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK                                0x7f7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_BMSK                       0x7f00
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_SHFT                          0x8
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_BMSK                         0x7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK                                0xffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_TCM_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                      0xffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                           0x12

#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OFFS                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK                           0xfffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                0xfffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                      0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OFFS                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK                           0xfffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                0xfffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                      0xe

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                               0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000114)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000114)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK                                0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_LPASS_QDSP6SS_DCC_CTRL_IN)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_BMSK                           0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR                              (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OFFS                              (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_EXT_PD_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_PD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_FLL_CTL_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001010)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_RMSK                                  0xfffffff
#define HWIO_LPASS_QDSP6SS_FLL_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_FLL_CTL_ADDR, HWIO_LPASS_QDSP6SS_FLL_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_FLL_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_FLL_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_FLL_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_FLL_CTL_IN)
#define HWIO_LPASS_QDSP6SS_FLL_CTL_M_BMSK                                0xfff0000
#define HWIO_LPASS_QDSP6SS_FLL_CTL_M_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_FLL_CTL_N_BMSK                                   0xf800
#define HWIO_LPASS_QDSP6SS_FLL_CTL_N_SHFT                                      0xb
#define HWIO_LPASS_QDSP6SS_FLL_CTL_DCO_INIT_BMSK                             0x7f8
#define HWIO_LPASS_QDSP6SS_FLL_CTL_DCO_INIT_SHFT                               0x3
#define HWIO_LPASS_QDSP6SS_FLL_CTL_CLK_SEL_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_FLL_CTL_CLK_SEL_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_FLL_CTL_RESET_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_FLL_CTL_RESET_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_FLL_CTL_ENA_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_FLL_CTL_ENA_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_FLL_STATUS_ADDR                              (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001014)
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_OFFS                              (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_RMSK                                   0x1ff
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_FLL_STATUS_ADDR, HWIO_LPASS_QDSP6SS_FLL_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_FLL_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_DCO_CURRENT_BMSK                       0x1fe
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_DCO_CURRENT_SHFT                         0x1
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_LOCKED_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_FLL_STATUS_LOCKED_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK                            0xff03ffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                  0xff000000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                        0x18
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                    0x20000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                       0x11
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                            0xffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_OFFS                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OFFS                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR                              (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OFFS                              (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK                                  0x7f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                    0x40
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                     0x6
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                   0x20
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                    0x5
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                      0x1f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_OFFS                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK                           0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_BMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK                                  0x3ffff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_ATEST_IN)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_BMSK                        0x20000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_SHFT                           0x11
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_BMSK                        0xff00
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_SHFT                           0x8
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_BMSK                          0xff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_ADDR                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_OFFS                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_RMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_VALUE_BMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_VALUE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002020)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OFFS                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002020)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK                              0xffffff
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                  0xffffe0
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                       0x5
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                          0x10
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                           0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                   0x8
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                   0x3
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                      0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                      0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                      0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                      0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                    0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                    0x0


#endif /* __HALCLKHWIOASM_H__ */
