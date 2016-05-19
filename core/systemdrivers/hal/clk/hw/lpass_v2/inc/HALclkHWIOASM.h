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
    CORE_TOP_CSR

  'Include' filters applied: <none>
  'Exclude' filters applied: TSENS ACR RPU RESERVED 
*/
/*
  ===========================================================================

  Copyright (c) 2013 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v2/inc/HALclkHWIOASM.h#1 $
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
#define CORE_TOP_CSR_BASE          0x0xfd480000

/*----------------------------------------------------------------------------
 * MODULE: LPASS_LPASS_CC_REG
 *--------------------------------------------------------------------------*/

#define LPASS_LPASS_CC_REG_REG_BASE                                                            (LPASS_BASE      + 0x00000000)
#define LPASS_LPASS_CC_REG_REG_BASE_OFFS                                                       0x00000000

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_BMSK                                         0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_SHFT                                               0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                      0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                            0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                        0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                              0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_BMSK                                    0x1f000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_SHFT                                          0x18
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                             0x800000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                 0x17
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_BMSK                                             0x400000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_SHFT                                                 0x16
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                     0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                         0x15
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                       0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                           0x14
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK                                          0xfc000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT                                              0xe
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_BMSK                                           0x3f00
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_SHFT                                              0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_BMSK                                            0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_SHFT                                             0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_BMSK                                                 0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_SHFT                                                 0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_BMSK                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_SHFT                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                 0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                 0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_BMSK                                   0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_SHFT                                          0x8
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_BMSK                                                     0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_SHFT                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK                                                 0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                         0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK                                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                             0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                     0xff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                                0xfe000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                      0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_BMSK                                          0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_SHFT                                               0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_BMSK                                  0xffc000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_SHFT                                       0xe
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_BMSK                                            0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_SHFT                                               0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                     0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                       0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                                           0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                                             0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_BMSK                                             0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_SHFT                                              0x7
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                        0x60
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                         0x5
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                         0x10
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                          0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                         0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                         0x3
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                          0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                           0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                           0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                          0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                          0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK                                                0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_BMSK                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_SHFT                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                                0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_BMSK                              0xfffc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_SHFT                                    0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_BMSK                                        0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_SHFT                                           0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_BMSK                                            0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_SHFT                                               0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_BMSK                                          0x6000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_SHFT                                             0xd
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                          0x1800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                             0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                         0x400
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                           0xa
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_BMSK                                              0x200
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_SHFT                                                0x9
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_BMSK                                             0x1c0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_SHFT                                               0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_BMSK                                         0x30
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_SHFT                                          0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_BMSK                                          0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_SHFT                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_BMSK                                           0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_SHFT                                           0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_BMSK                                0xff800000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_SHFT                                      0x17
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_BMSK                                                 0x700000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_SHFT                                                     0x14
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_BMSK                                                 0x80000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_SHFT                                                    0x13
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_BMSK                                                 0x60000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_SHFT                                                    0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                        0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                           0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_BMSK                                    0xfc00
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_SHFT                                       0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_BMSK                                              0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_SHFT                                                0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                             0x180
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                               0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                            0x40
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                             0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                             0x30
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                              0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_BMSK                                              0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_SHFT                                              0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                               0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                               0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                               0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                               0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK                                                0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_BMSK                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_SHFT                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                        0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_BMSK                                       0xfffc
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_SHFT                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_BMSK                                             0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_SHFT                                             0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_BMSK                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_SHFT                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_RMSK                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_LPAAUDIO_PLL_CLK_SRC_SEL_BMSK                             0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_SRC_SEL_LPAAUDIO_PLL_CLK_SRC_SEL_SHFT                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK                                                       0x7fff
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK                                          0x7000
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_SHFT                                             0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_BMSK                                            0xff8
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_SHFT                                              0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                             0x7
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                             0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_RMSK                                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_RESERVE_BITS_31_16_BMSK                            0xffff0000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_RESERVE_BITS_31_16_SHFT                                  0x10
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_PLL_L_BMSK                                             0xffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_PLL_L_SHFT                                                0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_RMSK                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                   0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_RMSK                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                       0xffffff00
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                              0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                               0xff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RMSK                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                          0xf0000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                0x1c
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                            0x8000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                                 0x1b
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                           0x6000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                                0x19
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ALPHA_EN_BMSK                                    0x1000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ALPHA_EN_SHFT                                         0x18
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                            0xc00000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                0x16
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_VCO_SEL_BMSK                                      0x300000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_VCO_SEL_SHFT                                          0x14
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                             0xf8000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                                 0xf
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                  0x7000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                     0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                  0xf00
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                    0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_OUTPUT_INV_BMSK                                       0x80
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_OUTPUT_INV_SHFT                                        0x7
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                  0x60
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                   0x5
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                   0x10
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                    0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                   0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                   0x3
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                    0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                    0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                     0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                     0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                    0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                    0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_RMSK                                          0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_RESERVE_BITS31_12_BMSK                        0xfffff000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_RESERVE_BITS31_12_SHFT                               0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                        0x800
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                          0xb
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                               0x700
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                 0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_DSM_BMSK                                            0x80
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_DSM_SHFT                                             0x7
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_WRITE_STATE_BMSK                                    0x40
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_WRITE_STATE_SHFT                                     0x6
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_TARGET_CTL_BMSK                                     0x38
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_TARGET_CTL_SHFT                                      0x3
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_LOCK_DET_BMSK                                        0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_LOCK_DET_SHFT                                        0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                      0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                      0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                      0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                      0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_RMSK                                          0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK                  0x80000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                        0x1f
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                       0x40000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                             0x1e
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK                  0x3c000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                        0x1a
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                      0x3800000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                           0x17
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                          0x700000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                              0x14
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                          0xff000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                              0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                          0xf00
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                            0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_RESERVE_BITS7_6_BMSK                                0xc0
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_RESERVE_BITS7_6_SHFT                                 0x6
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                      0x30
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                       0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_KFN_BMSK                                             0xf
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CONFIG_CTL_KFN_SHFT                                             0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_RMSK                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                              0xe0000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                                    0x1d
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DCO_BMSK                                        0x10000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DCO_SHFT                                              0x1c
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_PROCESS_CALB_BMSK                                0xc000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_PROCESS_CALB_SHFT                                     0x1a
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                       0x2000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                            0x19
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_FINE_FCW_BMSK                                    0x1f00000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_FINE_FCW_SHFT                                         0x14
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                             0x80000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                0x13
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_COARSE_FCW_BMSK                                    0x7e000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_COARSE_FCW_SHFT                                        0xd
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                                0x1000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                                   0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                    0x800
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                      0xb
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DTEST_SEL_BMSK                                       0x700
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DTEST_SEL_SHFT                                         0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DTEST_EN_BMSK                                         0x80
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_DTEST_EN_SHFT                                          0x7
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                      0x40
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                       0x6
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                       0x30
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                        0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                        0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                        0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST1_EN_BMSK                                         0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST1_EN_SHFT                                         0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST0_EN_BMSK                                         0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_ATEST0_EN_SHFT                                         0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_RMSK                                          0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_RESERVE_BITS31_14_BMSK                        0xffffc000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_RESERVE_BITS31_14_SHFT                               0xe
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                        0x2000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                           0xd
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                               0x1800
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                                  0xb
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                   0x600
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                     0x9
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NMO_EN_BMSK                                        0x100
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NMO_EN_SHFT                                          0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                      0xe0
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                       0x5
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                      0x10
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                       0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                    0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                    0x3
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                0x6
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                                 0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                                 0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RMSK                                                0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_DET_BMSK                                   0x80000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_DET_SHFT                                         0x1f
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                0x40000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                      0x1e
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACK_LATCH_BMSK                                  0x20000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACK_LATCH_SHFT                                        0x1d
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RESERVE_BITS28_24_BMSK                              0x1f000000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RESERVE_BITS28_24_SHFT                                    0x18
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                       0x800000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                           0x17
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_UPDATE_BMSK                                       0x400000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_UPDATE_SHFT                                           0x16
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                               0x200000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                   0x15
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                 0x100000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                     0x14
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_BMSK                                    0xfc000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                        0xe
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_BMSK                                     0x3f00
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                        0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RESERVE_BITS7_4_BMSK                                      0xf0
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_RESERVE_BITS7_4_SHFT                                       0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_PLLTEST_BMSK                                           0x8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_PLLTEST_SHFT                                           0x3
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_RESET_N_BMSK                                           0x4
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_RESET_N_SHFT                                           0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BYPASSNL_BMSK                                          0x2
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BYPASSNL_SHFT                                          0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_OUTCTRL_BMSK                                           0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_OUTCTRL_SHFT                                           0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_RMSK                                              0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_STATUS_31_0_BMSK                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_STATUS_STATUS_31_0_SHFT                                         0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_RMSK                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_RMSK                                                0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_BMSK                 0x1
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_LPAAUDIO_PRIUS_PLL_CLK_SRC_SEL_SHFT                 0x0

#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_RMSK                                                 0x7fff
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK                                    0x7000
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_AUX2_DIV_SHFT                                       0xc
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_AUX_DIV_BMSK                                      0xff8
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_AUX_DIV_SHFT                                        0x3
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                       0x7
#define HWIO_LPASS_LPAAUDIO_PRIUS_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                       0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00002000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK                                                             0x7
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_APPS_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6SS_PLL_BMSK                                                    0x4
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6SS_PLL_SHFT                                                    0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6_PLL_BMSK                                                      0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_Q6_PLL_SHFT                                                      0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPA_PLL_BMSK                                                     0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPA_PLL_SHFT                                                     0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK                                                          0x7
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6SS_PLL_BMSK                                                 0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6SS_PLL_SHFT                                                 0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6_PLL_BMSK                                                   0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_Q6_PLL_SHFT                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPA_PLL_BMSK                                                  0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPA_PLL_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004000)
#define HWIO_LPASS_AUDIO_CORE_BCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_LPASS_AUDIO_CORE_BCR_RMSK                                                         0x80000007
#define HWIO_LPASS_AUDIO_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_BMSK                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_SHFT                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_BMSK                                                    0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_SHFT                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK                                                0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_DIV_BMSK                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_DIV_SHFT                                              0x10
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                                  0x4000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                     0xe
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                0x2000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                   0xd
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                               0x1000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                  0xc
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_WAKEUP_BMSK                                              0xf00
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_WAKEUP_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_SLEEP_BMSK                                                0xf0
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_SLEEP_SHFT                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00005000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK                                                      0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_BMSK                                                      0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_SHFT                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_SHFT                                                    0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006000)
#define HWIO_LPASS_Q6SS_BCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_Q6SS_BCR_RMSK                                                               0x80000003
#define HWIO_LPASS_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, HWIO_LPASS_Q6SS_BCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_IN)
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_BMSK                                                    0x80000000
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_SHFT                                                          0x1f
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_BMSK                                                               0x2
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_SHFT                                                               0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_BMSK                                                             0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_SHFT                                                             0x0

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK                                                      0x81ff7ff3
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_DIV_BMSK                                               0x1ff0000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_DIV_SHFT                                                    0x10
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                                        0x4000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                           0xe
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                      0x2000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                         0xd
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                     0x1000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                        0xc
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_WAKEUP_BMSK                                                    0xf00
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_WAKEUP_SHFT                                                      0x8
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_SLEEP_BMSK                                                      0xf0
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_SLEEP_SHFT                                                       0x4
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006008)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006008)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_RMSK                                                          0x1
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_ADDR, HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_IN)
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_Q6SS_PLL_CLK_SRC_SEL_BMSK                                     0x1
#define HWIO_LPASS_Q6SS_PLL_CLK_SRC_SEL_Q6SS_PLL_CLK_SRC_SEL_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK                                                       0xf8ffffff
#define HWIO_LPASS_AUDIO_CORE_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_BMSK                                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_SHFT                                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_BMSK                                            0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_SHFT                                                  0x1b
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_BMSK                                            0xf00000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_SHFT                                                0x14
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_BMSK                                              0xf0000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_SHFT                                                 0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_BMSK                                              0xf000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_SHFT                                                 0xc
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_BMSK                                           0x800
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_SHFT                                             0xb
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_BMSK                                                    0x400
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_SHFT                                                      0xa
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_BMSK                                                       0x200
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_SHFT                                                         0x9
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_BMSK                                                     0x100
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_SHFT                                                       0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_BMSK                                                     0x80
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_SHFT                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_BMSK                                                      0x40
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_SHFT                                                       0x6
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_BMSK                                                    0x20
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_SHFT                                                     0x5
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_BMSK                                                 0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_SHFT                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_BMSK                                                      0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_SHFT                                                      0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_BMSK                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_SHFT                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_MIDI_CMD_RCGR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008000)
#define HWIO_LPASS_MIDI_CMD_RCGR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_MIDI_CMD_RCGR_RMSK                                                          0x800000f3
#define HWIO_LPASS_MIDI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_MIDI_CMD_RCGR_ADDR, HWIO_LPASS_MIDI_CMD_RCGR_RMSK)
#define HWIO_LPASS_MIDI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_MIDI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_MIDI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_MIDI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_MIDI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_MIDI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_MIDI_CMD_RCGR_IN)
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_D_BMSK                                                        0x80
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_D_SHFT                                                         0x7
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_N_BMSK                                                        0x40
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_N_SHFT                                                         0x6
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_M_BMSK                                                        0x20
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_M_SHFT                                                         0x5
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                 0x10
#define HWIO_LPASS_MIDI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                  0x4
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_EN_BMSK                                                         0x2
#define HWIO_LPASS_MIDI_CMD_RCGR_ROOT_EN_SHFT                                                         0x1
#define HWIO_LPASS_MIDI_CMD_RCGR_UPDATE_BMSK                                                          0x1
#define HWIO_LPASS_MIDI_CMD_RCGR_UPDATE_SHFT                                                          0x0

#define HWIO_LPASS_MIDI_CFG_RCGR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008004)
#define HWIO_LPASS_MIDI_CFG_RCGR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_MIDI_CFG_RCGR_RMSK                                                              0x371f
#define HWIO_LPASS_MIDI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_MIDI_CFG_RCGR_ADDR, HWIO_LPASS_MIDI_CFG_RCGR_RMSK)
#define HWIO_LPASS_MIDI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_MIDI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_MIDI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_MIDI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_MIDI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_MIDI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_MIDI_CFG_RCGR_IN)
#define HWIO_LPASS_MIDI_CFG_RCGR_MODE_BMSK                                                         0x3000
#define HWIO_LPASS_MIDI_CFG_RCGR_MODE_SHFT                                                            0xc
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_SEL_BMSK                                                       0x700
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_SEL_SHFT                                                         0x8
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_MIDI_CFG_RCGR_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008014)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008014)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_RMSK                                              0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_DIV_BMSK                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_DIV_SHFT                                            0x10
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                0x4000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                   0xe
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                              0x2000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                 0xd
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                             0x1000
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                0xc
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_WAKEUP_BMSK                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_WAKEUP_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_SLEEP_BMSK                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_SLEEP_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_CORE_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008018)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008018)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_MIDI_LFABIF_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_RMSK                                              0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_DIV_BMSK                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_DIV_SHFT                                            0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_CORE_ON_BMSK                                0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_CORE_ON_SHFT                                   0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_ON_BMSK                              0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                 0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                             0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_WAKEUP_BMSK                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_WAKEUP_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_SLEEP_BMSK                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_SLEEP_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_DMA_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_RMSK                                              0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_DIV_BMSK                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_DIV_SHFT                                            0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                                0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                   0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                              0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                 0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                             0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_WAKEUP_BMSK                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_WAKEUP_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_SLEEP_BMSK                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_SLEEP_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK                                                    0x800000f3
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_BMSK                                                  0x80
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_SHFT                                                   0x7
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_BMSK                                                  0x40
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_SHFT                                                   0x6
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_BMSK                                                  0x20
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_SHFT                                                   0x5
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                           0x10
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                            0x4
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_BMSK                                                   0x2
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_SHFT                                                   0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_BMSK                                                    0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK                                                        0x371f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_BMSK                                                   0x3000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_SHFT                                                      0xc
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_BMSK                                                  0x1f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_SPKR_M_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a008)
#define HWIO_LPASS_LPAIF_SPKR_M_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a008)
#define HWIO_LPASS_LPAIF_SPKR_M_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_SPKR_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, HWIO_LPASS_LPAIF_SPKR_M_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_M_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_M_IN)
#define HWIO_LPASS_LPAIF_SPKR_M_M_BMSK                                                               0xff
#define HWIO_LPASS_LPAIF_SPKR_M_M_SHFT                                                                0x0

#define HWIO_LPASS_LPAIF_SPKR_N_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a00c)
#define HWIO_LPASS_LPAIF_SPKR_N_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a00c)
#define HWIO_LPASS_LPAIF_SPKR_N_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_SPKR_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, HWIO_LPASS_LPAIF_SPKR_N_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_N_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_N_IN)
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_BMSK                                                   0xff
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_SPKR_D_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a010)
#define HWIO_LPASS_LPAIF_SPKR_D_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a010)
#define HWIO_LPASS_LPAIF_SPKR_D_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_SPKR_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, HWIO_LPASS_LPAIF_SPKR_D_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_D_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_D_IN)
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_BMSK                                                          0xff
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OFFS                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK                                   0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_BMSK                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_SHFT                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_DIV_BMSK                            0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_DIV_SHFT                                 0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                     0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                        0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                   0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                      0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                  0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                     0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_WAKEUP_BMSK                                 0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_WAKEUP_SHFT                                   0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_SLEEP_BMSK                                   0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_SLEEP_SHFT                                    0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_BMSK                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_SHFT                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OFFS                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK                                  0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_BMSK                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_SHFT                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_BMSK                           0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_SHFT                                0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                    0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                       0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                  0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                     0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                 0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                    0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_WAKEUP_BMSK                                0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_WAKEUP_SHFT                                  0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_SLEEP_BMSK                                  0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_SLEEP_SHFT                                   0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_BMSK                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_SHFT                              0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OFFS                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK                                  0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_BMSK                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_SHFT                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_DIV_BMSK                           0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_DIV_SHFT                                0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                    0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                       0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                  0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                     0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                 0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                    0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_WAKEUP_BMSK                                0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_WAKEUP_SHFT                                  0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_SLEEP_BMSK                                  0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_SLEEP_SHFT                                   0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_BMSK                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_SHFT                              0x0

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b008)
#define HWIO_LPASS_LPAIF_PRI_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b008)
#define HWIO_LPASS_LPAIF_PRI_M_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_PRI_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, HWIO_LPASS_LPAIF_PRI_M_RMSK)
#define HWIO_LPASS_LPAIF_PRI_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_M_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_M_IN)
#define HWIO_LPASS_LPAIF_PRI_M_M_BMSK                                                                0xff
#define HWIO_LPASS_LPAIF_PRI_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b00c)
#define HWIO_LPASS_LPAIF_PRI_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b00c)
#define HWIO_LPASS_LPAIF_PRI_N_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_PRI_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, HWIO_LPASS_LPAIF_PRI_N_RMSK)
#define HWIO_LPASS_LPAIF_PRI_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_N_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_N_IN)
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b010)
#define HWIO_LPASS_LPAIF_PRI_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b010)
#define HWIO_LPASS_LPAIF_PRI_D_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_PRI_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, HWIO_LPASS_LPAIF_PRI_D_RMSK)
#define HWIO_LPASS_LPAIF_PRI_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_D_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_D_IN)
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c008)
#define HWIO_LPASS_LPAIF_SEC_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c008)
#define HWIO_LPASS_LPAIF_SEC_M_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_SEC_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, HWIO_LPASS_LPAIF_SEC_M_RMSK)
#define HWIO_LPASS_LPAIF_SEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_M_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_M_IN)
#define HWIO_LPASS_LPAIF_SEC_M_M_BMSK                                                                0xff
#define HWIO_LPASS_LPAIF_SEC_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c00c)
#define HWIO_LPASS_LPAIF_SEC_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c00c)
#define HWIO_LPASS_LPAIF_SEC_N_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_SEC_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, HWIO_LPASS_LPAIF_SEC_N_RMSK)
#define HWIO_LPASS_LPAIF_SEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_N_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_N_IN)
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c010)
#define HWIO_LPASS_LPAIF_SEC_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c010)
#define HWIO_LPASS_LPAIF_SEC_D_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_SEC_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, HWIO_LPASS_LPAIF_SEC_D_RMSK)
#define HWIO_LPASS_LPAIF_SEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_D_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_D_IN)
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d008)
#define HWIO_LPASS_LPAIF_TER_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d008)
#define HWIO_LPASS_LPAIF_TER_M_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_TER_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, HWIO_LPASS_LPAIF_TER_M_RMSK)
#define HWIO_LPASS_LPAIF_TER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_M_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_M_ADDR,m,v,HWIO_LPASS_LPAIF_TER_M_IN)
#define HWIO_LPASS_LPAIF_TER_M_M_BMSK                                                                0xff
#define HWIO_LPASS_LPAIF_TER_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d00c)
#define HWIO_LPASS_LPAIF_TER_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d00c)
#define HWIO_LPASS_LPAIF_TER_N_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_TER_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, HWIO_LPASS_LPAIF_TER_N_RMSK)
#define HWIO_LPASS_LPAIF_TER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_N_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_N_ADDR,m,v,HWIO_LPASS_LPAIF_TER_N_IN)
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d010)
#define HWIO_LPASS_LPAIF_TER_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d010)
#define HWIO_LPASS_LPAIF_TER_D_RMSK                                                                  0xff
#define HWIO_LPASS_LPAIF_TER_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, HWIO_LPASS_LPAIF_TER_D_RMSK)
#define HWIO_LPASS_LPAIF_TER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_D_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_D_ADDR,m,v,HWIO_LPASS_LPAIF_TER_D_IN)
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK                                          0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_DIV_BMSK                                   0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_DIV_SHFT                                        0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                            0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                               0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                          0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                             0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                         0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                            0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_WAKEUP_BMSK                                        0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_WAKEUP_SHFT                                          0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_SLEEP_BMSK                                          0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_SLEEP_SHFT                                           0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK                                                    0x800000f3
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_BMSK                                                  0x80
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_SHFT                                                   0x7
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_BMSK                                                  0x40
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_SHFT                                                   0x6
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_BMSK                                                  0x20
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_SHFT                                                   0x5
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                           0x10
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                            0x4
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_BMSK                                                   0x2
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_SHFT                                                   0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_BMSK                                                    0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK                                                        0x371f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_BMSK                                                   0x3000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_SHFT                                                      0xc
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_BMSK                                                  0x1f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e008)
#define HWIO_LPASS_LPAIF_QUAD_M_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e008)
#define HWIO_LPASS_LPAIF_QUAD_M_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_QUAD_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, HWIO_LPASS_LPAIF_QUAD_M_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_M_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_M_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_M_IN)
#define HWIO_LPASS_LPAIF_QUAD_M_M_BMSK                                                               0xff
#define HWIO_LPASS_LPAIF_QUAD_M_M_SHFT                                                                0x0

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e00c)
#define HWIO_LPASS_LPAIF_QUAD_N_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e00c)
#define HWIO_LPASS_LPAIF_QUAD_N_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_QUAD_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, HWIO_LPASS_LPAIF_QUAD_N_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_N_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_N_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_N_IN)
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_BMSK                                                   0xff
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e010)
#define HWIO_LPASS_LPAIF_QUAD_D_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e010)
#define HWIO_LPASS_LPAIF_QUAD_D_RMSK                                                                 0xff
#define HWIO_LPASS_LPAIF_QUAD_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, HWIO_LPASS_LPAIF_QUAD_D_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_D_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_D_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_D_IN)
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_BMSK                                                          0xff
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f000)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f000)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_RMSK                                                    0x800000f3
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_D_BMSK                                                  0x80
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_D_SHFT                                                   0x7
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_N_BMSK                                                  0x40
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_N_SHFT                                                   0x6
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_M_BMSK                                                  0x20
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_M_SHFT                                                   0x5
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                           0x10
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                            0x4
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_EN_BMSK                                                   0x2
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_ROOT_EN_SHFT                                                   0x1
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_UPDATE_BMSK                                                    0x1
#define HWIO_LPASS_LPAIF_PCM0_CMD_RCGR_UPDATE_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f004)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f004)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_RMSK                                                        0x371f
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_MODE_BMSK                                                   0x3000
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_MODE_SHFT                                                      0xc
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_DIV_BMSK                                                  0x1f
#define HWIO_LPASS_LPAIF_PCM0_CFG_RCGR_SRC_DIV_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_PCM0_M_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f008)
#define HWIO_LPASS_LPAIF_PCM0_M_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f008)
#define HWIO_LPASS_LPAIF_PCM0_M_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM0_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_M_ADDR, HWIO_LPASS_LPAIF_PCM0_M_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_M_IN)
#define HWIO_LPASS_LPAIF_PCM0_M_M_BMSK                                                             0xffff
#define HWIO_LPASS_LPAIF_PCM0_M_M_SHFT                                                                0x0

#define HWIO_LPASS_LPAIF_PCM0_N_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f00c)
#define HWIO_LPASS_LPAIF_PCM0_N_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f00c)
#define HWIO_LPASS_LPAIF_PCM0_N_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM0_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_N_ADDR, HWIO_LPASS_LPAIF_PCM0_N_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_N_IN)
#define HWIO_LPASS_LPAIF_PCM0_N_NOT_N_MINUS_M_BMSK                                                 0xffff
#define HWIO_LPASS_LPAIF_PCM0_N_NOT_N_MINUS_M_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PCM0_D_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f010)
#define HWIO_LPASS_LPAIF_PCM0_D_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f010)
#define HWIO_LPASS_LPAIF_PCM0_D_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM0_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_D_ADDR, HWIO_LPASS_LPAIF_PCM0_D_RMSK)
#define HWIO_LPASS_LPAIF_PCM0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM0_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM0_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM0_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM0_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCM0_D_IN)
#define HWIO_LPASS_LPAIF_PCM0_D_NOT_2D_BMSK                                                        0xffff
#define HWIO_LPASS_LPAIF_PCM0_D_NOT_2D_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_RMSK                                        0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_IBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_RMSK                                        0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_EBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010000)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_RMSK                                                    0x800000f3
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_D_BMSK                                                  0x80
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_D_SHFT                                                   0x7
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_N_BMSK                                                  0x40
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_N_SHFT                                                   0x6
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_M_BMSK                                                  0x20
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_M_SHFT                                                   0x5
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                           0x10
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                            0x4
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_EN_BMSK                                                   0x2
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_ROOT_EN_SHFT                                                   0x1
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_UPDATE_BMSK                                                    0x1
#define HWIO_LPASS_LPAIF_PCM1_CMD_RCGR_UPDATE_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010004)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_RMSK                                                        0x371f
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_MODE_BMSK                                                   0x3000
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_MODE_SHFT                                                      0xc
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_DIV_BMSK                                                  0x1f
#define HWIO_LPASS_LPAIF_PCM1_CFG_RCGR_SRC_DIV_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_PCM1_M_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010008)
#define HWIO_LPASS_LPAIF_PCM1_M_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010008)
#define HWIO_LPASS_LPAIF_PCM1_M_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM1_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_M_ADDR, HWIO_LPASS_LPAIF_PCM1_M_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_M_IN)
#define HWIO_LPASS_LPAIF_PCM1_M_M_BMSK                                                             0xffff
#define HWIO_LPASS_LPAIF_PCM1_M_M_SHFT                                                                0x0

#define HWIO_LPASS_LPAIF_PCM1_N_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001000c)
#define HWIO_LPASS_LPAIF_PCM1_N_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001000c)
#define HWIO_LPASS_LPAIF_PCM1_N_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM1_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_N_ADDR, HWIO_LPASS_LPAIF_PCM1_N_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_N_IN)
#define HWIO_LPASS_LPAIF_PCM1_N_NOT_N_MINUS_M_BMSK                                                 0xffff
#define HWIO_LPASS_LPAIF_PCM1_N_NOT_N_MINUS_M_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PCM1_D_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010010)
#define HWIO_LPASS_LPAIF_PCM1_D_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010010)
#define HWIO_LPASS_LPAIF_PCM1_D_RMSK                                                               0xffff
#define HWIO_LPASS_LPAIF_PCM1_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_D_ADDR, HWIO_LPASS_LPAIF_PCM1_D_RMSK)
#define HWIO_LPASS_LPAIF_PCM1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCM1_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCM1_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCM1_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCM1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCM1_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCM1_D_IN)
#define HWIO_LPASS_LPAIF_PCM1_D_NOT_2D_BMSK                                                        0xffff
#define HWIO_LPASS_LPAIF_PCM1_D_NOT_2D_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_RMSK                                        0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_IBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_RMSK                                        0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_EBIT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CMD_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CFG_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011008)
#define HWIO_LPASS_RESAMPLER_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011008)
#define HWIO_LPASS_RESAMPLER_M_RMSK                                                                  0xff
#define HWIO_LPASS_RESAMPLER_M_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, HWIO_LPASS_RESAMPLER_M_RMSK)
#define HWIO_LPASS_RESAMPLER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, m)
#define HWIO_LPASS_RESAMPLER_M_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_M_ADDR,v)
#define HWIO_LPASS_RESAMPLER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_M_ADDR,m,v,HWIO_LPASS_RESAMPLER_M_IN)
#define HWIO_LPASS_RESAMPLER_M_M_BMSK                                                                0xff
#define HWIO_LPASS_RESAMPLER_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001100c)
#define HWIO_LPASS_RESAMPLER_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001100c)
#define HWIO_LPASS_RESAMPLER_N_RMSK                                                                  0xff
#define HWIO_LPASS_RESAMPLER_N_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, HWIO_LPASS_RESAMPLER_N_RMSK)
#define HWIO_LPASS_RESAMPLER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, m)
#define HWIO_LPASS_RESAMPLER_N_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_N_ADDR,v)
#define HWIO_LPASS_RESAMPLER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_N_ADDR,m,v,HWIO_LPASS_RESAMPLER_N_IN)
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011010)
#define HWIO_LPASS_RESAMPLER_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011010)
#define HWIO_LPASS_RESAMPLER_D_RMSK                                                                  0xff
#define HWIO_LPASS_RESAMPLER_D_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, HWIO_LPASS_RESAMPLER_D_RMSK)
#define HWIO_LPASS_RESAMPLER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, m)
#define HWIO_LPASS_RESAMPLER_D_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_D_ADDR,v)
#define HWIO_LPASS_RESAMPLER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_D_ADDR,m,v,HWIO_LPASS_RESAMPLER_D_IN)
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_RMSK                                       0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_OFF_BMSK                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_OFF_SHFT                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_DIV_BMSK                                0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_DIV_SHFT                                     0x10
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                         0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                            0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                       0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                          0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                      0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                         0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_WAKEUP_BMSK                                     0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_WAKEUP_SHFT                                       0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_SLEEP_BMSK                                       0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_SLEEP_SHFT                                        0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_HW_CTL_BMSK                                       0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_HW_CTL_SHFT                                       0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_ENABLE_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_LFABIF_CBCR_CLK_ENABLE_SHFT                                   0x0

#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012000)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_RMSK                                                       0x800000f3
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                     0x80
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                      0x7
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                     0x40
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                      0x6
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                     0x20
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                      0x5
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                              0x10
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                               0x4
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                      0x2
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                      0x1
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                       0x1
#define HWIO_LPASS_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                       0x0

#define HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012004)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_RMSK                                                           0x371f
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_MODE_BMSK                                                      0x3000
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_MODE_SHFT                                                         0xc
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                    0x700
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                      0x8
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                     0x1f
#define HWIO_LPASS_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                      0x0

#define HWIO_LPASS_SLIMBUS_M_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012008)
#define HWIO_LPASS_SLIMBUS_M_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012008)
#define HWIO_LPASS_SLIMBUS_M_RMSK                                                                    0xff
#define HWIO_LPASS_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_M_ADDR, HWIO_LPASS_SLIMBUS_M_RMSK)
#define HWIO_LPASS_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_SLIMBUS_M_IN)
#define HWIO_LPASS_SLIMBUS_M_M_BMSK                                                                  0xff
#define HWIO_LPASS_SLIMBUS_M_M_SHFT                                                                   0x0

#define HWIO_LPASS_SLIMBUS_N_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001200c)
#define HWIO_LPASS_SLIMBUS_N_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001200c)
#define HWIO_LPASS_SLIMBUS_N_RMSK                                                                    0xff
#define HWIO_LPASS_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_N_ADDR, HWIO_LPASS_SLIMBUS_N_RMSK)
#define HWIO_LPASS_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_SLIMBUS_N_IN)
#define HWIO_LPASS_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                      0xff
#define HWIO_LPASS_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                       0x0

#define HWIO_LPASS_SLIMBUS_D_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012010)
#define HWIO_LPASS_SLIMBUS_D_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012010)
#define HWIO_LPASS_SLIMBUS_D_RMSK                                                                    0xff
#define HWIO_LPASS_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_SLIMBUS_D_ADDR, HWIO_LPASS_SLIMBUS_D_RMSK)
#define HWIO_LPASS_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_SLIMBUS_D_IN)
#define HWIO_LPASS_SLIMBUS_D_NOT_2D_BMSK                                                             0xff
#define HWIO_LPASS_SLIMBUS_D_NOT_2D_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_CORE_SLIMBUS_LFABIF_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK                                                   0x800000f3
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_BMSK                                                 0x80
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_SHFT                                                  0x7
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_BMSK                                                 0x40
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_SHFT                                                  0x6
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_BMSK                                                 0x20
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_SHFT                                                  0x5
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK                                                       0x371f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_BMSK                                                  0x3000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_SHFT                                                     0xc
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_BMSK                                                 0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_SHFT                                                  0x0

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013008)
#define HWIO_LPASS_LPAIF_PCMOE_M_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013008)
#define HWIO_LPASS_LPAIF_PCMOE_M_RMSK                                                                0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, HWIO_LPASS_LPAIF_PCMOE_M_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_M_IN)
#define HWIO_LPASS_LPAIF_PCMOE_M_M_BMSK                                                              0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_M_SHFT                                                               0x0

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001300c)
#define HWIO_LPASS_LPAIF_PCMOE_N_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001300c)
#define HWIO_LPASS_LPAIF_PCMOE_N_RMSK                                                                0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, HWIO_LPASS_LPAIF_PCMOE_N_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_N_IN)
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_BMSK                                                  0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013010)
#define HWIO_LPASS_LPAIF_PCMOE_D_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013010)
#define HWIO_LPASS_LPAIF_PCMOE_D_RMSK                                                                0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, HWIO_LPASS_LPAIF_PCMOE_D_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_D_IN)
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_BMSK                                                         0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014000)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_RMSK                                                        0x800000f3
#define HWIO_LPASS_Q6CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR, HWIO_LPASS_Q6CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_Q6CORE_CMD_RCGR_IN)
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_OFF_BMSK                                               0x80000000
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_OFF_SHFT                                                     0x1f
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_D_BMSK                                                      0x80
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_D_SHFT                                                       0x7
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_N_BMSK                                                      0x40
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_N_SHFT                                                       0x6
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_M_BMSK                                                      0x20
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_M_SHFT                                                       0x5
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                               0x10
#define HWIO_LPASS_Q6CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                0x4
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_EN_BMSK                                                       0x2
#define HWIO_LPASS_Q6CORE_CMD_RCGR_ROOT_EN_SHFT                                                       0x1
#define HWIO_LPASS_Q6CORE_CMD_RCGR_UPDATE_BMSK                                                        0x1
#define HWIO_LPASS_Q6CORE_CMD_RCGR_UPDATE_SHFT                                                        0x0

#define HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014004)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_RMSK                                                            0x371f
#define HWIO_LPASS_Q6CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR, HWIO_LPASS_Q6CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_Q6CORE_CFG_RCGR_IN)
#define HWIO_LPASS_Q6CORE_CFG_RCGR_MODE_BMSK                                                       0x3000
#define HWIO_LPASS_Q6CORE_CFG_RCGR_MODE_SHFT                                                          0xc
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_SEL_BMSK                                                     0x700
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_SEL_SHFT                                                       0x8
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_DIV_BMSK                                                      0x1f
#define HWIO_LPASS_Q6CORE_CFG_RCGR_SRC_DIV_SHFT                                                       0x0

#define HWIO_LPASS_Q6CORE_M_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014008)
#define HWIO_LPASS_Q6CORE_M_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014008)
#define HWIO_LPASS_Q6CORE_M_RMSK                                                                     0xff
#define HWIO_LPASS_Q6CORE_M_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_M_ADDR, HWIO_LPASS_Q6CORE_M_RMSK)
#define HWIO_LPASS_Q6CORE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_M_ADDR, m)
#define HWIO_LPASS_Q6CORE_M_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_M_ADDR,v)
#define HWIO_LPASS_Q6CORE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_M_ADDR,m,v,HWIO_LPASS_Q6CORE_M_IN)
#define HWIO_LPASS_Q6CORE_M_M_BMSK                                                                   0xff
#define HWIO_LPASS_Q6CORE_M_M_SHFT                                                                    0x0

#define HWIO_LPASS_Q6CORE_N_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001400c)
#define HWIO_LPASS_Q6CORE_N_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001400c)
#define HWIO_LPASS_Q6CORE_N_RMSK                                                                     0xff
#define HWIO_LPASS_Q6CORE_N_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_N_ADDR, HWIO_LPASS_Q6CORE_N_RMSK)
#define HWIO_LPASS_Q6CORE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_N_ADDR, m)
#define HWIO_LPASS_Q6CORE_N_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_N_ADDR,v)
#define HWIO_LPASS_Q6CORE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_N_ADDR,m,v,HWIO_LPASS_Q6CORE_N_IN)
#define HWIO_LPASS_Q6CORE_N_NOT_N_MINUS_M_BMSK                                                       0xff
#define HWIO_LPASS_Q6CORE_N_NOT_N_MINUS_M_SHFT                                                        0x0

#define HWIO_LPASS_Q6CORE_D_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014010)
#define HWIO_LPASS_Q6CORE_D_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014010)
#define HWIO_LPASS_Q6CORE_D_RMSK                                                                     0xff
#define HWIO_LPASS_Q6CORE_D_IN          \
        in_dword_masked(HWIO_LPASS_Q6CORE_D_ADDR, HWIO_LPASS_Q6CORE_D_RMSK)
#define HWIO_LPASS_Q6CORE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6CORE_D_ADDR, m)
#define HWIO_LPASS_Q6CORE_D_OUT(v)      \
        out_dword(HWIO_LPASS_Q6CORE_D_ADDR,v)
#define HWIO_LPASS_Q6CORE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6CORE_D_ADDR,m,v,HWIO_LPASS_Q6CORE_D_IN)
#define HWIO_LPASS_Q6CORE_D_NOT_2D_BMSK                                                              0xff
#define HWIO_LPASS_Q6CORE_D_NOT_2D_SHFT                                                               0x0

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_RMSK                                                         0x800000f3
#define HWIO_LPASS_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, HWIO_LPASS_SLEEP_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CMD_RCGR_IN)
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                       0x80
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                        0x7
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                       0x40
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                        0x6
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                       0x20
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                        0x5
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                0x10
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                 0x4
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                        0x2
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                        0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_BMSK                                                         0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_SHFT                                                         0x0

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_RMSK                                                             0x371f
#define HWIO_LPASS_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, HWIO_LPASS_SLEEP_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CFG_RCGR_IN)
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_BMSK                                                        0x3000
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_SHFT                                                           0xc
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                      0x700
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                        0x8
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                       0x1f
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                        0x0

#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016000)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_RMSK                                                       0x800000f3
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CMD_RCGR_ADDR, HWIO_LPASS_Q6_SPDM_CMD_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPDM_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPDM_CMD_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPDM_CMD_RCGR_IN)
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_ROOT_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_ROOT_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_D_BMSK                                                     0x80
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_D_SHFT                                                      0x7
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_N_BMSK                                                     0x40
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_N_SHFT                                                      0x6
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_M_BMSK                                                     0x20
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_M_SHFT                                                      0x5
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                              0x10
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                               0x4
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_ROOT_EN_BMSK                                                      0x2
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_ROOT_EN_SHFT                                                      0x1
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_UPDATE_BMSK                                                       0x1
#define HWIO_LPASS_Q6_SPDM_CMD_RCGR_UPDATE_SHFT                                                       0x0

#define HWIO_LPASS_SPDM_CMD_RCGR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016000)
#define HWIO_LPASS_SPDM_CMD_RCGR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_SPDM_CMD_RCGR_RMSK                                                          0x800000f3
#define HWIO_LPASS_SPDM_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDM_CMD_RCGR_ADDR, HWIO_LPASS_SPDM_CMD_RCGR_RMSK)
#define HWIO_LPASS_SPDM_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDM_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SPDM_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDM_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SPDM_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDM_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SPDM_CMD_RCGR_IN)
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_D_BMSK                                                        0x80
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_D_SHFT                                                         0x7
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_N_BMSK                                                        0x40
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_N_SHFT                                                         0x6
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_M_BMSK                                                        0x20
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_M_SHFT                                                         0x5
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                 0x10
#define HWIO_LPASS_SPDM_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                  0x4
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_EN_BMSK                                                         0x2
#define HWIO_LPASS_SPDM_CMD_RCGR_ROOT_EN_SHFT                                                         0x1
#define HWIO_LPASS_SPDM_CMD_RCGR_UPDATE_BMSK                                                          0x1
#define HWIO_LPASS_SPDM_CMD_RCGR_UPDATE_SHFT                                                          0x0

#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016004)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_RMSK                                                           0x371f
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CFG_RCGR_ADDR, HWIO_LPASS_Q6_SPDM_CFG_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPDM_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPDM_CFG_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPDM_CFG_RCGR_IN)
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_MODE_BMSK                                                      0x3000
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_MODE_SHFT                                                         0xc
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_SRC_SEL_BMSK                                                    0x700
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_SRC_SEL_SHFT                                                      0x8
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_SRC_DIV_BMSK                                                     0x1f
#define HWIO_LPASS_Q6_SPDM_CFG_RCGR_SRC_DIV_SHFT                                                      0x0

#define HWIO_LPASS_SPDM_CFG_RCGR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016004)
#define HWIO_LPASS_SPDM_CFG_RCGR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_SPDM_CFG_RCGR_RMSK                                                              0x371f
#define HWIO_LPASS_SPDM_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDM_CFG_RCGR_ADDR, HWIO_LPASS_SPDM_CFG_RCGR_RMSK)
#define HWIO_LPASS_SPDM_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDM_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SPDM_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDM_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SPDM_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDM_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SPDM_CFG_RCGR_IN)
#define HWIO_LPASS_SPDM_CFG_RCGR_MODE_BMSK                                                         0x3000
#define HWIO_LPASS_SPDM_CFG_RCGR_MODE_SHFT                                                            0xc
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_SEL_BMSK                                                       0x700
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_SEL_SHFT                                                         0x8
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_SPDM_CFG_RCGR_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_Q6_SPDM_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016014)
#define HWIO_LPASS_Q6_SPDM_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_Q6_SPDM_CBCR_RMSK                                                           0x81ff7ff3
#define HWIO_LPASS_Q6_SPDM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CBCR_ADDR, HWIO_LPASS_Q6_SPDM_CBCR_RMSK)
#define HWIO_LPASS_Q6_SPDM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPDM_CBCR_ADDR, m)
#define HWIO_LPASS_Q6_SPDM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPDM_CBCR_ADDR,v)
#define HWIO_LPASS_Q6_SPDM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPDM_CBCR_ADDR,m,v,HWIO_LPASS_Q6_SPDM_CBCR_IN)
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_DIV_BMSK                                                    0x1ff0000
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_DIV_SHFT                                                         0x10
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_CORE_ON_BMSK                                             0x4000
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_CORE_ON_SHFT                                                0xe
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                           0x2000
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                              0xd
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                          0x1000
#define HWIO_LPASS_Q6_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                             0xc
#define HWIO_LPASS_Q6_SPDM_CBCR_WAKEUP_BMSK                                                         0xf00
#define HWIO_LPASS_Q6_SPDM_CBCR_WAKEUP_SHFT                                                           0x8
#define HWIO_LPASS_Q6_SPDM_CBCR_SLEEP_BMSK                                                           0xf0
#define HWIO_LPASS_Q6_SPDM_CBCR_SLEEP_SHFT                                                            0x4
#define HWIO_LPASS_Q6_SPDM_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_Q6_SPDM_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_Q6_SPDM_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016014)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_RMSK                                                0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_DIV_BMSK                                         0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_DIV_SHFT                                              0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_CORE_ON_BMSK                                  0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_CORE_ON_SHFT                                     0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                   0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                               0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                  0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_WAKEUP_BMSK                                              0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_WAKEUP_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_SLEEP_BMSK                                                0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_SLEEP_SHFT                                                 0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SPDM_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AHB_SPDM_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016018)
#define HWIO_LPASS_AHB_SPDM_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016018)
#define HWIO_LPASS_AHB_SPDM_CBCR_RMSK                                                          0x81ff7ff3
#define HWIO_LPASS_AHB_SPDM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AHB_SPDM_CBCR_ADDR, HWIO_LPASS_AHB_SPDM_CBCR_RMSK)
#define HWIO_LPASS_AHB_SPDM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHB_SPDM_CBCR_ADDR, m)
#define HWIO_LPASS_AHB_SPDM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AHB_SPDM_CBCR_ADDR,v)
#define HWIO_LPASS_AHB_SPDM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHB_SPDM_CBCR_ADDR,m,v,HWIO_LPASS_AHB_SPDM_CBCR_IN)
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_DIV_BMSK                                                   0x1ff0000
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_DIV_SHFT                                                        0x10
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_CORE_ON_BMSK                                            0x4000
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_CORE_ON_SHFT                                               0xe
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                          0x2000
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                             0xd
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                         0x1000
#define HWIO_LPASS_AHB_SPDM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                            0xc
#define HWIO_LPASS_AHB_SPDM_CBCR_WAKEUP_BMSK                                                        0xf00
#define HWIO_LPASS_AHB_SPDM_CBCR_WAKEUP_SHFT                                                          0x8
#define HWIO_LPASS_AHB_SPDM_CBCR_SLEEP_BMSK                                                          0xf0
#define HWIO_LPASS_AHB_SPDM_CBCR_SLEEP_SHFT                                                           0x4
#define HWIO_LPASS_AHB_SPDM_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_AHB_SPDM_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AHB_SPDM_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017000)
#define HWIO_LPASS_XO_CMD_RCGR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_XO_CMD_RCGR_RMSK                                                            0x800000f3
#define HWIO_LPASS_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, HWIO_LPASS_XO_CMD_RCGR_RMSK)
#define HWIO_LPASS_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CMD_RCGR_ADDR,m,v,HWIO_LPASS_XO_CMD_RCGR_IN)
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_BMSK                                                          0x80
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_SHFT                                                           0x7
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_BMSK                                                          0x40
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_SHFT                                                           0x6
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_BMSK                                                          0x20
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_SHFT                                                           0x5
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                   0x10
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                    0x4
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_BMSK                                                           0x2
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_SHFT                                                           0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_BMSK                                                            0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_SHFT                                                            0x0

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017004)
#define HWIO_LPASS_XO_CFG_RCGR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_XO_CFG_RCGR_RMSK                                                                0x371f
#define HWIO_LPASS_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, HWIO_LPASS_XO_CFG_RCGR_RMSK)
#define HWIO_LPASS_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CFG_RCGR_ADDR,m,v,HWIO_LPASS_XO_CFG_RCGR_IN)
#define HWIO_LPASS_XO_CFG_RCGR_MODE_BMSK                                                           0x3000
#define HWIO_LPASS_XO_CFG_RCGR_MODE_SHFT                                                              0xc
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_BMSK                                                         0x700
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_SHFT                                                           0x8
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_BMSK                                                          0x1f
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_SHFT                                                           0x0

#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018000)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_RMSK                                                     0x800000f3
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR, HWIO_LPASS_AHBFABRIC_CMD_RCGR_RMSK)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AHBFABRIC_CMD_RCGR_IN)
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_D_BMSK                                                   0x80
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_D_SHFT                                                    0x7
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_N_BMSK                                                   0x40
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_N_SHFT                                                    0x6
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_M_BMSK                                                   0x20
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_M_SHFT                                                    0x5
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                            0x10
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                             0x4
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_EN_BMSK                                                    0x2
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_ROOT_EN_SHFT                                                    0x1
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_BMSK                                                     0x1
#define HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_SHFT                                                     0x0

#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018004)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_RMSK                                                         0x371f
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR, HWIO_LPASS_AHBFABRIC_CFG_RCGR_RMSK)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AHBFABRIC_CFG_RCGR_IN)
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_MODE_BMSK                                                    0x3000
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_MODE_SHFT                                                       0xc
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_BMSK                                                   0x1f
#define HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_SHFT                                                    0x0

#define HWIO_LPASS_AHBFABRIC_M_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018008)
#define HWIO_LPASS_AHBFABRIC_M_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018008)
#define HWIO_LPASS_AHBFABRIC_M_RMSK                                                                  0xff
#define HWIO_LPASS_AHBFABRIC_M_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_M_ADDR, HWIO_LPASS_AHBFABRIC_M_RMSK)
#define HWIO_LPASS_AHBFABRIC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_M_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_M_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_M_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_M_ADDR,m,v,HWIO_LPASS_AHBFABRIC_M_IN)
#define HWIO_LPASS_AHBFABRIC_M_M_BMSK                                                                0xff
#define HWIO_LPASS_AHBFABRIC_M_M_SHFT                                                                 0x0

#define HWIO_LPASS_AHBFABRIC_N_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001800c)
#define HWIO_LPASS_AHBFABRIC_N_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001800c)
#define HWIO_LPASS_AHBFABRIC_N_RMSK                                                                  0xff
#define HWIO_LPASS_AHBFABRIC_N_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_N_ADDR, HWIO_LPASS_AHBFABRIC_N_RMSK)
#define HWIO_LPASS_AHBFABRIC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_N_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_N_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_N_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_N_ADDR,m,v,HWIO_LPASS_AHBFABRIC_N_IN)
#define HWIO_LPASS_AHBFABRIC_N_NOT_N_MINUS_M_BMSK                                                    0xff
#define HWIO_LPASS_AHBFABRIC_N_NOT_N_MINUS_M_SHFT                                                     0x0

#define HWIO_LPASS_AHBFABRIC_D_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018010)
#define HWIO_LPASS_AHBFABRIC_D_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018010)
#define HWIO_LPASS_AHBFABRIC_D_RMSK                                                                  0xff
#define HWIO_LPASS_AHBFABRIC_D_IN          \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_D_ADDR, HWIO_LPASS_AHBFABRIC_D_RMSK)
#define HWIO_LPASS_AHBFABRIC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBFABRIC_D_ADDR, m)
#define HWIO_LPASS_AHBFABRIC_D_OUT(v)      \
        out_dword(HWIO_LPASS_AHBFABRIC_D_ADDR,v)
#define HWIO_LPASS_AHBFABRIC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBFABRIC_D_ADDR,m,v,HWIO_LPASS_AHBFABRIC_D_IN)
#define HWIO_LPASS_AHBFABRIC_D_NOT_2D_BMSK                                                           0xff
#define HWIO_LPASS_AHBFABRIC_D_NOT_2D_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_RMSK                                                    0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_DIV_BMSK                                             0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_DIV_SHFT                                                  0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_CORE_ON_BMSK                                      0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_CORE_ON_SHFT                                         0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                    0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                       0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                   0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                      0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_WAKEUP_BMSK                                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_WAKEUP_SHFT                                                    0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_SLEEP_BMSK                                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_SLEEP_SHFT                                                     0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_RMSK                                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_DIV_BMSK                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_DIV_SHFT                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_RMSK                                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_DIV_BMSK                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_DIV_SHFT                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001900c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001900c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_RMSK                                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_DIV_BMSK                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_DIV_SHFT                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_RMSK                                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_DIV_BMSK                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_DIV_SHFT                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CSR_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_RMSK                                                   0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_DIV_BMSK                                            0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_DIV_SHFT                                                 0x10
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_CORE_ON_BMSK                                     0x4000
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_CORE_ON_SHFT                                        0xe
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                   0x2000
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                      0xd
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                  0x1000
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                     0xc
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_WAKEUP_BMSK                                                 0xf00
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_WAKEUP_SHFT                                                   0x8
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_SLEEP_BMSK                                                   0xf0
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_SLEEP_SHFT                                                    0x4
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_AUDIO_CORE_BSTC_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_RMSK                                              0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_DIV_BMSK                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_DIV_SHFT                                            0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                                0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                   0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                              0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                 0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                             0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_WAKEUP_BMSK                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_WAKEUP_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_SLEEP_BMSK                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_SLEEP_SHFT                                               0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_XO_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a00c)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a00c)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_BT_XO_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a010)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a010)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_RMSK                                           0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_DIV_BMSK                                    0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_FM_XO_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_RMSK                                      0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_DIV_BMSK                               0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_DIV_SHFT                                    0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                        0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                           0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                      0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                         0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                     0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                        0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_WAKEUP_BMSK                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_WAKEUP_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_SLEEP_BMSK                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_SLEEP_SHFT                                       0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_HW_CTL_BMSK                                      0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_HW_CTL_SHFT                                      0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_AVTIMER_XO_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_RMSK                                               0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_DIV_BMSK                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_DIV_SHFT                                             0x10
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_RMSK                                                    0x81ff7ff3
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_ADDR, HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_IN)
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_DIV_BMSK                                             0x1ff0000
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_DIV_SHFT                                                  0x10
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_CORE_ON_BMSK                                      0x4000
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_CORE_ON_SHFT                                         0xe
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                    0x2000
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                       0xd
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                   0x1000
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                      0xc
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_WAKEUP_BMSK                                                  0xf00
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_WAKEUP_SHFT                                                    0x8
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_SLEEP_BMSK                                                    0xf0
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_SLEEP_SHFT                                                     0x4
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_Q6SS_TCM_SLAVE_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_RMSK                                                    0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_DIV_BMSK                                             0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_DIV_SHFT                                                  0x10
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                                      0x4000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                         0xe
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                    0x2000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                       0xd
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                   0x1000
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                      0xc
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_WAKEUP_BMSK                                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_WAKEUP_SHFT                                                    0x8
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_SLEEP_BMSK                                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_SLEEP_SHFT                                                     0x4
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_AUDIO_CORE_CSR_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_RMSK                                                    0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_DML_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DML_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DML_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_DIV_BMSK                                             0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_DIV_SHFT                                                  0x10
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_CORE_ON_BMSK                                      0x4000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_CORE_ON_SHFT                                         0xe
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                    0x2000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                       0xd
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                   0x1000
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                      0xc
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_WAKEUP_BMSK                                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_WAKEUP_SHFT                                                    0x8
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_SLEEP_BMSK                                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_SLEEP_SHFT                                                     0x4
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_RMSK                                                 0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_DIV_BMSK                                          0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_DIV_SHFT                                               0x10
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_CORE_ON_BMSK                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_CORE_ON_SHFT                                      0xe
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                    0xd
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                0x1000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                   0xc
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_WAKEUP_BMSK                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_WAKEUP_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_SLEEP_BMSK                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_SLEEP_SHFT                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_MPORT_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f004)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OFFS                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f004)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_RMSK                                         0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_DIV_BMSK                                  0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_DIV_SHFT                                       0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_CORE_ON_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_CORE_ON_SHFT                              0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_ON_BMSK                         0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_ON_SHFT                            0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                        0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                           0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_WAKEUP_BMSK                                       0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_WAKEUP_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_SLEEP_BMSK                                         0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_SLEEP_SHFT                                          0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_HW_CTL_BMSK                                         0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_HW_CTL_SHFT                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020000)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020000)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_TIMEOUT_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020004)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020004)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_TIMEOUT_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_RMSK                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_SECURITY_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021004)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021004)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_RMSK                                            0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_DIV_BMSK                                     0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_DIV_SHFT                                          0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_CORE_ON_BMSK                              0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_CORE_ON_SHFT                                 0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_ON_BMSK                            0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_ON_SHFT                               0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                           0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                              0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_WAKEUP_BMSK                                          0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_WAKEUP_SHFT                                            0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_SLEEP_BMSK                                            0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_SLEEP_SHFT                                             0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SECURITY_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022000)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022000)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_RMSK                                                   0x81ff7ff3
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR, HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_DIV_BMSK                                            0x1ff0000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_DIV_SHFT                                                 0x10
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_CORE_ON_BMSK                                     0x4000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_CORE_ON_SHFT                                        0xe
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                   0x2000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                      0xd
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                  0x1000
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                     0xc
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_WAKEUP_BMSK                                                 0xf00
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_WAKEUP_SHFT                                                   0x8
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_SLEEP_BMSK                                                   0xf0
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_SLEEP_SHFT                                                    0x4
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_Q6SS_AHB_LFABIF_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022004)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022004)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_RMSK                                                         0x80000003
#define HWIO_LPASS_Q6SS_AHBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBM_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBM_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBM_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_Q6SS_AHBM_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_Q6SS_AHBM_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_Q6SS_AHBM_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_RMSK                                             0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_DIV_BMSK                                      0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_DIV_SHFT                                           0x10
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_LCC_CSR_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00024000)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00024000)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_RMSK                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_OFF_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_OFF_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_HW_CTL_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_HW_CTL_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BR_CBCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_RMSK                                                0x81ff7ff3
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_DIV_BMSK                                         0x1ff0000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_DIV_SHFT                                              0x10
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_CORE_ON_BMSK                                  0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_CORE_ON_SHFT                                     0xe
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                   0xd
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                               0x1000
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                  0xc
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_WAKEUP_BMSK                                              0xf00
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_WAKEUP_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_SLEEP_BMSK                                                0xf0
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_SLEEP_SHFT                                                 0x4
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMEM_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_Q6SS_XO_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026000)
#define HWIO_LPASS_Q6SS_XO_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026000)
#define HWIO_LPASS_Q6SS_XO_CBCR_RMSK                                                           0x81ff7ff3
#define HWIO_LPASS_Q6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_XO_CBCR_ADDR, HWIO_LPASS_Q6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_XO_CBCR_IN)
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_DIV_BMSK                                                    0x1ff0000
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_DIV_SHFT                                                         0x10
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                                             0x4000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                                                0xe
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                           0x2000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                              0xd
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                          0x1000
#define HWIO_LPASS_Q6SS_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                             0xc
#define HWIO_LPASS_Q6SS_XO_CBCR_WAKEUP_BMSK                                                         0xf00
#define HWIO_LPASS_Q6SS_XO_CBCR_WAKEUP_SHFT                                                           0x8
#define HWIO_LPASS_Q6SS_XO_CBCR_SLEEP_BMSK                                                           0xf0
#define HWIO_LPASS_Q6SS_XO_CBCR_SLEEP_SHFT                                                            0x4
#define HWIO_LPASS_Q6SS_XO_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_Q6SS_XO_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_Q6SS_XO_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_SLP_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026004)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026004)
#define HWIO_LPASS_Q6SS_SLP_CBCR_RMSK                                                          0x81ff7ff3
#define HWIO_LPASS_Q6SS_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_DIV_BMSK                                                   0x1ff0000
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_DIV_SHFT                                                        0x10
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_CORE_ON_BMSK                                            0x4000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_CORE_ON_SHFT                                               0xe
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                          0x2000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                             0xd
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                         0x1000
#define HWIO_LPASS_Q6SS_SLP_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                            0xc
#define HWIO_LPASS_Q6SS_SLP_CBCR_WAKEUP_BMSK                                                        0xf00
#define HWIO_LPASS_Q6SS_SLP_CBCR_WAKEUP_SHFT                                                          0x8
#define HWIO_LPASS_Q6SS_SLP_CBCR_SLEEP_BMSK                                                          0xf0
#define HWIO_LPASS_Q6SS_SLP_CBCR_SLEEP_SHFT                                                           0x4
#define HWIO_LPASS_Q6SS_SLP_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_Q6SS_SLP_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_Q6SS_SLP_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_RMSK                                              0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OFFS                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_RMSK                                    0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_DIV_BMSK                             0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_DIV_SHFT                                  0x10
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_CORE_ON_BMSK                      0x4000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_CORE_ON_SHFT                         0xe
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_ON_BMSK                    0x2000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_ON_SHFT                       0xd
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                   0x1000
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                      0xc
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_WAKEUP_BMSK                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_WAKEUP_SHFT                                    0x8
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_SLEEP_BMSK                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_SLEEP_SHFT                                     0x4
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_HW_CTL_BMSK                                    0x2
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_HW_CTL_SHFT                                    0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_LPASS_AUDIO_CORE_IXFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_SHFT                                0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OFFS                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028004)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_RMSK                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_BMSK                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_OFF_SHFT                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_HW_CTL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_HW_CTL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_BMSK                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CSR_CBCR_CLK_ENABLE_SHFT                              0x0

#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029000)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029000)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK                                                   0x800000f3
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_BMSK                                                 0x80
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_SHFT                                                  0x7
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_BMSK                                                 0x40
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_SHFT                                                  0x6
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_BMSK                                                 0x20
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_SHFT                                                  0x5
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029004)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029004)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_RMSK                                                       0x371f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_BMSK                                                  0x3000
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_SHFT                                                     0xc
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_BMSK                                                 0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_SHFT                                                  0x0

#define HWIO_LPASS_SPDIFTX_BMC_M_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029008)
#define HWIO_LPASS_SPDIFTX_BMC_M_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029008)
#define HWIO_LPASS_SPDIFTX_BMC_M_RMSK                                                              0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_M_ADDR, HWIO_LPASS_SPDIFTX_BMC_M_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_M_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_M_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_M_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_M_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_M_IN)
#define HWIO_LPASS_SPDIFTX_BMC_M_M_BMSK                                                            0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_M_SHFT                                                               0x0

#define HWIO_LPASS_SPDIFTX_BMC_N_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002900c)
#define HWIO_LPASS_SPDIFTX_BMC_N_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002900c)
#define HWIO_LPASS_SPDIFTX_BMC_N_RMSK                                                              0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_N_ADDR, HWIO_LPASS_SPDIFTX_BMC_N_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_N_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_N_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_N_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_N_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_N_IN)
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_BMSK                                                0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_SHFT                                                   0x0

#define HWIO_LPASS_SPDIFTX_BMC_D_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029010)
#define HWIO_LPASS_SPDIFTX_BMC_D_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029010)
#define HWIO_LPASS_SPDIFTX_BMC_D_RMSK                                                              0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_D_ADDR, HWIO_LPASS_SPDIFTX_BMC_D_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_D_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_D_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_D_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_D_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_D_IN)
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_BMSK                                                       0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_SHFT                                                          0x0

#define HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029014)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029014)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_RMSK                                                       0x80000003
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_SPDIFTX_BMC_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029018)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029018)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_RMSK                                                      0x80000003
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR, HWIO_LPASS_SPDIFTX_AHBS_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_AHBS_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_AHBS_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_SPDIFTX_AHBS_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002901c)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002901c)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_RMSK                                                      0x80000003
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR, HWIO_LPASS_SPDIFTX_AHBM_CBCR_RMSK)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_AHBM_CBCR_ADDR,m,v,HWIO_LPASS_SPDIFTX_AHBM_CBCR_IN)
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_SPDIFTX_AHBM_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_SIF_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a000)
#define HWIO_LPASS_SIF_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a000)
#define HWIO_LPASS_SIF_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_SIF_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SIF_CBCR_ADDR, HWIO_LPASS_SIF_CBCR_RMSK)
#define HWIO_LPASS_SIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SIF_CBCR_ADDR, m)
#define HWIO_LPASS_SIF_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SIF_CBCR_ADDR,v)
#define HWIO_LPASS_SIF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SIF_CBCR_ADDR,m,v,HWIO_LPASS_SIF_CBCR_IN)
#define HWIO_LPASS_SIF_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_SIF_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_SIF_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_SIF_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_SIF_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_SIF_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_SIF_AHB_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a004)
#define HWIO_LPASS_SIF_AHB_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a004)
#define HWIO_LPASS_SIF_AHB_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_SIF_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_SIF_AHB_CBCR_ADDR, HWIO_LPASS_SIF_AHB_CBCR_RMSK)
#define HWIO_LPASS_SIF_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SIF_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_SIF_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_SIF_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_SIF_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SIF_AHB_CBCR_ADDR,m,v,HWIO_LPASS_SIF_AHB_CBCR_IN)
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_SIF_AHB_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_SIF_AHB_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_SIF_AHB_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002b000)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002b000)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_RMSK                                                        0x80000003
#define HWIO_LPASS_HDMIRX_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR, HWIO_LPASS_HDMIRX_AHB_CBCR_RMSK)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_HDMIRX_AHB_CBCR_ADDR,m,v,HWIO_LPASS_HDMIRX_AHB_CBCR_IN)
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_HDMIRX_AHB_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_HDMIRX_AHB_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_HDMIRX_AHB_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c000)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c000)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_RMSK                                                      0x800000f3
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR, HWIO_LPASS_DIGCODEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_DIGCODEC_CMD_RCGR_IN)
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_OFF_BMSK                                             0x80000000
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_OFF_SHFT                                                   0x1f
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_D_BMSK                                                    0x80
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_D_SHFT                                                     0x7
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_N_BMSK                                                    0x40
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_N_SHFT                                                     0x6
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_M_BMSK                                                    0x20
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_M_SHFT                                                     0x5
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                             0x10
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                              0x4
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_EN_BMSK                                                     0x2
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_ROOT_EN_SHFT                                                     0x1
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_UPDATE_BMSK                                                      0x1
#define HWIO_LPASS_DIGCODEC_CMD_RCGR_UPDATE_SHFT                                                      0x0

#define HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c004)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c004)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_RMSK                                                          0x371f
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR, HWIO_LPASS_DIGCODEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_DIGCODEC_CFG_RCGR_IN)
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_MODE_BMSK                                                     0x3000
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_MODE_SHFT                                                        0xc
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_SEL_BMSK                                                   0x700
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_SEL_SHFT                                                     0x8
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_DIV_BMSK                                                    0x1f
#define HWIO_LPASS_DIGCODEC_CFG_RCGR_SRC_DIV_SHFT                                                     0x0

#define HWIO_LPASS_DIGCODEC_M_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c008)
#define HWIO_LPASS_DIGCODEC_M_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c008)
#define HWIO_LPASS_DIGCODEC_M_RMSK                                                                   0xff
#define HWIO_LPASS_DIGCODEC_M_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_M_ADDR, HWIO_LPASS_DIGCODEC_M_RMSK)
#define HWIO_LPASS_DIGCODEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_M_ADDR, m)
#define HWIO_LPASS_DIGCODEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_M_ADDR,v)
#define HWIO_LPASS_DIGCODEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_M_ADDR,m,v,HWIO_LPASS_DIGCODEC_M_IN)
#define HWIO_LPASS_DIGCODEC_M_M_BMSK                                                                 0xff
#define HWIO_LPASS_DIGCODEC_M_M_SHFT                                                                  0x0

#define HWIO_LPASS_DIGCODEC_N_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c00c)
#define HWIO_LPASS_DIGCODEC_N_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c00c)
#define HWIO_LPASS_DIGCODEC_N_RMSK                                                                   0xff
#define HWIO_LPASS_DIGCODEC_N_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_N_ADDR, HWIO_LPASS_DIGCODEC_N_RMSK)
#define HWIO_LPASS_DIGCODEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_N_ADDR, m)
#define HWIO_LPASS_DIGCODEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_N_ADDR,v)
#define HWIO_LPASS_DIGCODEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_N_ADDR,m,v,HWIO_LPASS_DIGCODEC_N_IN)
#define HWIO_LPASS_DIGCODEC_N_NOT_N_MINUS_M_BMSK                                                     0xff
#define HWIO_LPASS_DIGCODEC_N_NOT_N_MINUS_M_SHFT                                                      0x0

#define HWIO_LPASS_DIGCODEC_D_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c010)
#define HWIO_LPASS_DIGCODEC_D_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c010)
#define HWIO_LPASS_DIGCODEC_D_RMSK                                                                   0xff
#define HWIO_LPASS_DIGCODEC_D_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_D_ADDR, HWIO_LPASS_DIGCODEC_D_RMSK)
#define HWIO_LPASS_DIGCODEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_D_ADDR, m)
#define HWIO_LPASS_DIGCODEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_D_ADDR,v)
#define HWIO_LPASS_DIGCODEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_D_ADDR,m,v,HWIO_LPASS_DIGCODEC_D_IN)
#define HWIO_LPASS_DIGCODEC_D_NOT_2D_BMSK                                                            0xff
#define HWIO_LPASS_DIGCODEC_D_NOT_2D_SHFT                                                             0x0

#define HWIO_LPASS_DIGCODEC_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c014)
#define HWIO_LPASS_DIGCODEC_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c014)
#define HWIO_LPASS_DIGCODEC_CBCR_RMSK                                                          0x80000003
#define HWIO_LPASS_DIGCODEC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CBCR_ADDR, HWIO_LPASS_DIGCODEC_CBCR_RMSK)
#define HWIO_LPASS_DIGCODEC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_CBCR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_CBCR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_CBCR_ADDR,m,v,HWIO_LPASS_DIGCODEC_CBCR_IN)
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_DIGCODEC_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_DIGCODEC_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_DIGCODEC_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c018)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c018)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_RMSK                                                      0x80000003
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR, HWIO_LPASS_DIGCODEC_AHB_CBCR_RMSK)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR, m)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR,v)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DIGCODEC_AHB_CBCR_ADDR,m,v,HWIO_LPASS_DIGCODEC_AHB_CBCR_IN)
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_DIGCODEC_AHB_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002d000)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_RMSK                                                 0x80000003
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_ADDR, HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_RMSK)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_ADDR, m)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_ADDR,v)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_ADDR,m,v,HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_IN)
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_LPASS_CORE_SMMU_CFG_CLK_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002d004)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002d004)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_RMSK                                                   0x80000003
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_ADDR, HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_RMSK)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_ADDR,m,v,HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_IN)
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_Q6_SMMU_CFG_CLK_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_ATIME_CMD_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_ATIME_CMD_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e000)
#define HWIO_LPASS_ATIME_CMD_RCGR_RMSK                                                         0x800000f3
#define HWIO_LPASS_ATIME_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, HWIO_LPASS_ATIME_CMD_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CMD_RCGR_IN)
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_BMSK                                                       0x80
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_SHFT                                                        0x7
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_BMSK                                                       0x40
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_SHFT                                                        0x6
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_BMSK                                                       0x20
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_SHFT                                                        0x5
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                0x10
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                 0x4
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_BMSK                                                        0x2
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_SHFT                                                        0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_BMSK                                                         0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_SHFT                                                         0x0

#define HWIO_LPASS_ATIME_CFG_RCGR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e004)
#define HWIO_LPASS_ATIME_CFG_RCGR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e004)
#define HWIO_LPASS_ATIME_CFG_RCGR_RMSK                                                             0x371f
#define HWIO_LPASS_ATIME_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, HWIO_LPASS_ATIME_CFG_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CFG_RCGR_IN)
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_BMSK                                                        0x3000
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_SHFT                                                           0xc
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_BMSK                                                      0x700
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_SHFT                                                        0x8
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_BMSK                                                       0x1f
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_SHFT                                                        0x0

#define HWIO_LPASS_ATIME_M_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e008)
#define HWIO_LPASS_ATIME_M_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e008)
#define HWIO_LPASS_ATIME_M_RMSK                                                                      0xff
#define HWIO_LPASS_ATIME_M_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, HWIO_LPASS_ATIME_M_RMSK)
#define HWIO_LPASS_ATIME_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, m)
#define HWIO_LPASS_ATIME_M_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_M_ADDR,v)
#define HWIO_LPASS_ATIME_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_M_ADDR,m,v,HWIO_LPASS_ATIME_M_IN)
#define HWIO_LPASS_ATIME_M_M_BMSK                                                                    0xff
#define HWIO_LPASS_ATIME_M_M_SHFT                                                                     0x0

#define HWIO_LPASS_ATIME_N_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e00c)
#define HWIO_LPASS_ATIME_N_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e00c)
#define HWIO_LPASS_ATIME_N_RMSK                                                                      0xff
#define HWIO_LPASS_ATIME_N_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, HWIO_LPASS_ATIME_N_RMSK)
#define HWIO_LPASS_ATIME_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, m)
#define HWIO_LPASS_ATIME_N_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_N_ADDR,v)
#define HWIO_LPASS_ATIME_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_N_ADDR,m,v,HWIO_LPASS_ATIME_N_IN)
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_BMSK                                                        0xff
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_SHFT                                                         0x0

#define HWIO_LPASS_ATIME_D_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e010)
#define HWIO_LPASS_ATIME_D_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e010)
#define HWIO_LPASS_ATIME_D_RMSK                                                                      0xff
#define HWIO_LPASS_ATIME_D_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, HWIO_LPASS_ATIME_D_RMSK)
#define HWIO_LPASS_ATIME_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, m)
#define HWIO_LPASS_ATIME_D_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_D_ADDR,v)
#define HWIO_LPASS_ATIME_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_D_ADDR,m,v,HWIO_LPASS_ATIME_D_IN)
#define HWIO_LPASS_ATIME_D_NOT_2D_BMSK                                                               0xff
#define HWIO_LPASS_ATIME_D_NOT_2D_SHFT                                                                0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_ADDR                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_OFFS                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_RMSK                                        0x81ff7ff3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_DIV_BMSK                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_CORE_ON_BMSK                          0x4000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_CORE_ON_SHFT                             0xe
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_PERIPH_ON_BMSK                        0x2000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_PERIPH_ON_SHFT                           0xd
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                       0x1000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                          0xc
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_WAKEUP_BMSK                                      0xf00
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_WAKEUP_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_SLEEP_BMSK                                        0xf0
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_SLEEP_SHFT                                         0x4
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_HW_CTL_BMSK                                        0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_HW_CTL_SHFT                                        0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_XO_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002f000)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002f000)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_AON_CLK_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002f004)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002f004)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CLK_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_RMSK                                                      0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ACK_UPDATE_LMN_BMSK                                       0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_ACK_UPDATE_LMN_SHFT                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_REQ_UPDATE_LMN_BMSK                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_Q6_CTL_REQ_UPDATE_LMN_SHFT                                       0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_RMSK                                                      0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_VAL_BMSK                                                  0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_DELTA_VAL_SHFT                                                   0x0

#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030008)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030008)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_RMSK                                                   0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_ADDR, HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_VAL_BMSK                                               0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_DELTA_VAL_SHFT                                                   0x0

#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003000c)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003000c)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_RMSK                                                   0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_ADDR, HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_VAL_BMSK                                               0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_DELTA_VAL_SHFT                                                   0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030010)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030010)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_RMSK                                                   0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_VAL_BMSK                                               0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_Q6_READBACK_VAL_SHFT                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030014)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030014)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_RMSK                                                0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_ADDR, HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_VAL_BMSK                                            0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_M_Q6_READBACK_VAL_SHFT                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030018)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030018)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_RMSK                                                0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_ADDR, HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_VAL_BMSK                                            0x7ffff
#define HWIO_LPASS_LPAAUDIO_PLL_N_Q6_READBACK_VAL_SHFT                                                0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK                                                         0x7
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_Q6SS_PLL_BMSK                                                0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_Q6SS_PLL_SHFT                                                0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_Q6_PLL_BMSK                                                  0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_Q6_PLL_SHFT                                                  0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPA_PLL_BMSK                                                 0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPA_PLL_SHFT                                                 0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032000)
#define HWIO_LPASS_DBG_CLK_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032000)
#define HWIO_LPASS_DBG_CLK_RMSK                                                                0xfff0ffff
#define HWIO_LPASS_DBG_CLK_IN          \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, HWIO_LPASS_DBG_CLK_RMSK)
#define HWIO_LPASS_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, m)
#define HWIO_LPASS_DBG_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_DBG_CLK_ADDR,v)
#define HWIO_LPASS_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DBG_CLK_ADDR,m,v,HWIO_LPASS_DBG_CLK_IN)
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_BMSK                                                 0xe0000000
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_SHFT                                                       0x1d
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_BMSK                                               0x1c000000
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_SHFT                                                     0x1a
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_BMSK                                               0x3e00000
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_SHFT                                                    0x15
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                   0x100000
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                       0x14
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                    0xffff
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OFFS                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_RMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_SEL_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_MODE_MUXSEL_SEL_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_RMSK                                              0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_I2S_PCM_SEL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_I2S_PCM_SEL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_SEL_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_MODE_MUXSEL_SEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_RMSK                                              0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_I2S_PCM_SEL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_I2S_PCM_SEL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_SEL_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_MODE_MUXSEL_SEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_RMSK                                              0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_I2S_PCM_SEL_BMSK                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_I2S_PCM_SEL_SHFT                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_SEL_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_MODE_MUXSEL_SEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_RMSK                                             0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_I2S_PCM_SEL_BMSK                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_I2S_PCM_SEL_SHFT                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_SEL_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_MODE_MUXSEL_SEL_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00038000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00038000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_RMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_SEL_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM0_MODE_MUXSEL_SEL_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00039000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00039000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_RMSK                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_SEL_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM1_MODE_MUXSEL_SEL_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003a000)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003a000)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_RMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_EN_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_XFABRIC_SPDMTM_CGC_EN_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003a004)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OFFS                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003a004)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_RMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_EN_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_IFABRIC_SPDMTM_CGC_EN_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003a008)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OFFS                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003a008)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_RMSK                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_EN_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EFABRIC_SPDMTM_CGC_EN_SHFT                                           0x0

#define HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003b000)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003b000)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_RMSK                                                              0x1
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR, HWIO_LPASS_Q6SS_RST_EVB_SEL_RMSK)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR, m)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR,v)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_RST_EVB_SEL_ADDR,m,v,HWIO_LPASS_Q6SS_RST_EVB_SEL_IN)
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_SEL_BMSK                                                          0x1
#define HWIO_LPASS_Q6SS_RST_EVB_SEL_SEL_SHFT                                                          0x0

#define HWIO_LPASS_Q6SS_RST_EVB_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003b004)
#define HWIO_LPASS_Q6SS_RST_EVB_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003b004)
#define HWIO_LPASS_Q6SS_RST_EVB_RMSK                                                            0xffffff0
#define HWIO_LPASS_Q6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_ADDR, HWIO_LPASS_Q6SS_RST_EVB_RMSK)
#define HWIO_LPASS_Q6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_Q6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_Q6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_Q6SS_RST_EVB_IN)
#define HWIO_LPASS_Q6SS_RST_EVB_EVB_BMSK                                                        0xffffff0
#define HWIO_LPASS_Q6SS_RST_EVB_EVB_SHFT                                                              0x4

#define HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003c000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003c000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_RMSK                                                             0x11f
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR, HWIO_LPASS_VFR_IRQ_MUX_CTL_RMSK)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR, m)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR,v)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_VFR_IRQ_MUX_CTL_ADDR,m,v,HWIO_LPASS_VFR_IRQ_MUX_CTL_IN)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_VFR_BMSK                                                         0x100
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_VFR_SHFT                                                           0x8
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_SEL_BMSK                                                          0x1f
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_SEL_SHFT                                                           0x0

#define HWIO_LPASS_VFR_STC_MSB_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003c004)
#define HWIO_LPASS_VFR_STC_MSB_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003c004)
#define HWIO_LPASS_VFR_STC_MSB_RMSK                                                              0xffffff
#define HWIO_LPASS_VFR_STC_MSB_IN          \
        in_dword_masked(HWIO_LPASS_VFR_STC_MSB_ADDR, HWIO_LPASS_VFR_STC_MSB_RMSK)
#define HWIO_LPASS_VFR_STC_MSB_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_STC_MSB_ADDR, m)
#define HWIO_LPASS_VFR_STC_MSB_MSB_BMSK                                                          0xffffff
#define HWIO_LPASS_VFR_STC_MSB_MSB_SHFT                                                               0x0

#define HWIO_LPASS_VFR_STC_LSB_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003c008)
#define HWIO_LPASS_VFR_STC_LSB_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003c008)
#define HWIO_LPASS_VFR_STC_LSB_RMSK                                                            0xffffffff
#define HWIO_LPASS_VFR_STC_LSB_IN          \
        in_dword_masked(HWIO_LPASS_VFR_STC_LSB_ADDR, HWIO_LPASS_VFR_STC_LSB_RMSK)
#define HWIO_LPASS_VFR_STC_LSB_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_STC_LSB_ADDR, m)
#define HWIO_LPASS_VFR_STC_LSB_LSB_BMSK                                                        0xffffffff
#define HWIO_LPASS_VFR_STC_LSB_LSB_SHFT                                                               0x0

#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n)                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003d000 + 0x4 * (n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OFFS(n)                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003d000 + 0x4 * (n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_RMSK                                            0x80010077
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_MAXn                                                     3
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n), HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_RMSK)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n), mask)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n),val)
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ADDR(n),mask,val,HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_INI(n))
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_BMSK                            0x80000000
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_SHFT                                  0x1f
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_BMSK                          0x10000
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_SHFT                             0x10
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_BMSK                                  0x70
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_SHFT                                   0x4
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_BMSK                                    0x7
#define HWIO_LPASS_SYSNOC_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_SHFT                                    0x0

#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n)                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003d020 + 0x4 * (n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OFFS(n)                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003d020 + 0x4 * (n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_RMSK                                              0x80010077
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_MAXn                                                       3
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n), HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_RMSK)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n), mask)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n),val)
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ADDR(n),mask,val,HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_INI(n))
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_BMSK                              0x80000000
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_DISABLE_CLK_GRP_SHFT                                    0x1f
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_BMSK                            0x10000
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYST_DISABLE_SHFT                               0x10
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_BMSK                                    0x70
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_STARTUP_HYSTSEL_SHFT                                     0x4
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_BMSK                                      0x7
#define HWIO_LPASS_Q6SS_HYSTERESIS_CLK_GRP_n_ACTIVE_HYSTSEL_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003d100)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003d100)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_RMSK                                                       0xff
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_ADDR, HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_IN)
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_LPASS_CORE_CLAMP_ZERO_DELAY_BMSK                           0xff
#define HWIO_LPASS_AUDIO_CORE_CLAMP_DELAY_LPASS_CORE_CLAMP_ZERO_DELAY_SHFT                            0x0

#define HWIO_LPASS_STM_MUXSEL_n_ADDR(n)                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e000 + 0x4 * (n))
#define HWIO_LPASS_STM_MUXSEL_n_OFFS(n)                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e000 + 0x4 * (n))
#define HWIO_LPASS_STM_MUXSEL_n_RMSK                                                           0x80000007
#define HWIO_LPASS_STM_MUXSEL_n_MAXn                                                                   31
#define HWIO_LPASS_STM_MUXSEL_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_STM_MUXSEL_n_ADDR(n), HWIO_LPASS_STM_MUXSEL_n_RMSK)
#define HWIO_LPASS_STM_MUXSEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_STM_MUXSEL_n_ADDR(n), mask)
#define HWIO_LPASS_STM_MUXSEL_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_STM_MUXSEL_n_ADDR(n),val)
#define HWIO_LPASS_STM_MUXSEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_STM_MUXSEL_n_ADDR(n),mask,val,HWIO_LPASS_STM_MUXSEL_n_INI(n))
#define HWIO_LPASS_STM_MUXSEL_n_ENABLE_BMSK                                                    0x80000000
#define HWIO_LPASS_STM_MUXSEL_n_ENABLE_SHFT                                                          0x1f
#define HWIO_LPASS_STM_MUXSEL_n_SEL_BMSK                                                              0x7
#define HWIO_LPASS_STM_MUXSEL_n_SEL_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003f000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003f000)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_RMSK                                                     0x3
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_LPASS_Q6_AXI_BYPASS_ENABLE_BMSK                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_LPASS_Q6_AXI_BYPASS_ENABLE_SHFT                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_LPASS_CORE_AXI_BYPASS_ENABLE_BMSK                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SMMU_BYPASS_LPASS_CORE_AXI_BYPASS_ENABLE_SHFT                        0x0

#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003f004)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_OFFS                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003f004)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_RMSK                                                  0x3
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR, HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_IN)
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_DIG_CDC_CLK_SEL_BMSK                                  0x3
#define HWIO_LPASS_AUDIO_CORE_DIG_CODEC_CLK_SEL_DIG_CDC_CLK_SEL_SHFT                                  0x0

#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00040000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00040000)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_RMSK                                                           0x11f
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_IN          \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_1_ADDR, HWIO_LPASS_VFR_IRQ_MUX_CTL_1_RMSK)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_IRQ_MUX_CTL_1_ADDR, m)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_OUT(v)      \
        out_dword(HWIO_LPASS_VFR_IRQ_MUX_CTL_1_ADDR,v)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_VFR_IRQ_MUX_CTL_1_ADDR,m,v,HWIO_LPASS_VFR_IRQ_MUX_CTL_1_IN)
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_VFR_BMSK                                                       0x100
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_VFR_SHFT                                                         0x8
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_SEL_BMSK                                                        0x1f
#define HWIO_LPASS_VFR_IRQ_MUX_CTL_1_SEL_SHFT                                                         0x0

#define HWIO_LPASS_VFR_STC_MSB_1_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00040004)
#define HWIO_LPASS_VFR_STC_MSB_1_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00040004)
#define HWIO_LPASS_VFR_STC_MSB_1_RMSK                                                            0xffffff
#define HWIO_LPASS_VFR_STC_MSB_1_IN          \
        in_dword_masked(HWIO_LPASS_VFR_STC_MSB_1_ADDR, HWIO_LPASS_VFR_STC_MSB_1_RMSK)
#define HWIO_LPASS_VFR_STC_MSB_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_STC_MSB_1_ADDR, m)
#define HWIO_LPASS_VFR_STC_MSB_1_MSB_BMSK                                                        0xffffff
#define HWIO_LPASS_VFR_STC_MSB_1_MSB_SHFT                                                             0x0

#define HWIO_LPASS_VFR_STC_LSB_1_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00040008)
#define HWIO_LPASS_VFR_STC_LSB_1_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00040008)
#define HWIO_LPASS_VFR_STC_LSB_1_RMSK                                                          0xffffffff
#define HWIO_LPASS_VFR_STC_LSB_1_IN          \
        in_dword_masked(HWIO_LPASS_VFR_STC_LSB_1_ADDR, HWIO_LPASS_VFR_STC_LSB_1_RMSK)
#define HWIO_LPASS_VFR_STC_LSB_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_VFR_STC_LSB_1_ADDR, m)
#define HWIO_LPASS_VFR_STC_LSB_1_LSB_BMSK                                                      0xffffffff
#define HWIO_LPASS_VFR_STC_LSB_1_LSB_SHFT                                                             0x0

#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00041000)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00041000)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_RMSK                                                       0x1ff
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_ADDR, HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_RMSK)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_ADDR, m)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_ADDR,v)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_ADDR,m,v,HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_IN)
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_VFR_BMSK                                                   0x100
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_VFR_SHFT                                                     0x8
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_SEL_BMSK                                                    0xff
#define HWIO_LPASS_SENSOR_IRQ_TS_MUX_CTL_SEL_SHFT                                                     0x0

#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00041004)
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00041004)
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_RMSK                                                       0xffffff
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_IN          \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_STC_MSB_ADDR, HWIO_LPASS_SENSOR_IRQ_STC_MSB_RMSK)
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_INM(m)      \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_STC_MSB_ADDR, m)
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_MSB_BMSK                                                   0xffffff
#define HWIO_LPASS_SENSOR_IRQ_STC_MSB_MSB_SHFT                                                        0x0

#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00041008)
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00041008)
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_RMSK                                                     0xffffffff
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_IN          \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_STC_LSB_ADDR, HWIO_LPASS_SENSOR_IRQ_STC_LSB_RMSK)
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_INM(m)      \
        in_dword_masked(HWIO_LPASS_SENSOR_IRQ_STC_LSB_ADDR, m)
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_LSB_BMSK                                                 0xffffffff
#define HWIO_LPASS_SENSOR_IRQ_STC_LSB_LSB_SHFT                                                        0x0

#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00042000)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00042000)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_RMSK                                                         0x1ff
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_ADDR, HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_RMSK)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_ADDR, m)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_OUT(v)      \
        out_dword(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_ADDR,v)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_ADDR,m,v,HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_IN)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_VFR_BMSK                                                     0x100
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_VFR_SHFT                                                       0x8
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_SEL_BMSK                                                      0xff
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_0_SEL_SHFT                                                       0x0

#define HWIO_LPASS_GP_IRQ_STC_MSB_0_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00042004)
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00042004)
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_RMSK                                                         0xffffff
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_MSB_0_ADDR, HWIO_LPASS_GP_IRQ_STC_MSB_0_RMSK)
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_MSB_0_ADDR, m)
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_MSB_BMSK                                                     0xffffff
#define HWIO_LPASS_GP_IRQ_STC_MSB_0_MSB_SHFT                                                          0x0

#define HWIO_LPASS_GP_IRQ_STC_LSB_0_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00042008)
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00042008)
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_RMSK                                                       0xffffffff
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_LSB_0_ADDR, HWIO_LPASS_GP_IRQ_STC_LSB_0_RMSK)
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_LSB_0_ADDR, m)
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_LSB_BMSK                                                   0xffffffff
#define HWIO_LPASS_GP_IRQ_STC_LSB_0_LSB_SHFT                                                          0x0

#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00043000)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00043000)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_RMSK                                                         0x1ff
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_ADDR, HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_RMSK)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_ADDR, m)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_OUT(v)      \
        out_dword(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_ADDR,v)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_ADDR,m,v,HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_IN)
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_VFR_BMSK                                                     0x100
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_VFR_SHFT                                                       0x8
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_SEL_BMSK                                                      0xff
#define HWIO_LPASS_GP_IRQ_TS_MUX_CTL_1_SEL_SHFT                                                       0x0

#define HWIO_LPASS_GP_IRQ_STC_MSB_1_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00043004)
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00043004)
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_RMSK                                                         0xffffff
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_MSB_1_ADDR, HWIO_LPASS_GP_IRQ_STC_MSB_1_RMSK)
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_MSB_1_ADDR, m)
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_MSB_BMSK                                                     0xffffff
#define HWIO_LPASS_GP_IRQ_STC_MSB_1_MSB_SHFT                                                          0x0

#define HWIO_LPASS_GP_IRQ_STC_LSB_1_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00043008)
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00043008)
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_RMSK                                                       0xffffffff
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_IN          \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_LSB_1_ADDR, HWIO_LPASS_GP_IRQ_STC_LSB_1_RMSK)
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_GP_IRQ_STC_LSB_1_ADDR, m)
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_LSB_BMSK                                                   0xffffffff
#define HWIO_LPASS_GP_IRQ_STC_LSB_1_LSB_SHFT                                                          0x0

#define HWIO_LPASS_SB_VFR_IRQ_CTL_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00044000)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00044000)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_RMSK                                                           0xffffff
#define HWIO_LPASS_SB_VFR_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SB_VFR_IRQ_CTL_ADDR, HWIO_LPASS_SB_VFR_IRQ_CTL_RMSK)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SB_VFR_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SB_VFR_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SB_VFR_IRQ_CTL_ADDR,m,v,HWIO_LPASS_SB_VFR_IRQ_CTL_IN)
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_23_BMSK                                     0x800000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_23_SHFT                                         0x17
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_22_BMSK                                     0x400000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_22_SHFT                                         0x16
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_21_BMSK                                     0x200000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_21_SHFT                                         0x15
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_20_BMSK                                     0x100000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_20_SHFT                                         0x14
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_19_BMSK                                      0x80000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_19_SHFT                                         0x13
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_18_BMSK                                      0x40000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_18_SHFT                                         0x12
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_17_BMSK                                      0x20000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_17_SHFT                                         0x11
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_16_BMSK                                      0x10000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_16_SHFT                                         0x10
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_15_BMSK                                       0x8000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_15_SHFT                                          0xf
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_14_BMSK                                       0x4000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_14_SHFT                                          0xe
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_13_BMSK                                       0x2000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_13_SHFT                                          0xd
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_12_BMSK                                       0x1000
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_12_SHFT                                          0xc
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_11_BMSK                                        0x800
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_11_SHFT                                          0xb
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_10_BMSK                                        0x400
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_10_SHFT                                          0xa
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_9_BMSK                                         0x200
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_9_SHFT                                           0x9
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_8_BMSK                                         0x100
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_8_SHFT                                           0x8
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_7_BMSK                                          0x80
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_7_SHFT                                           0x7
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_6_BMSK                                          0x40
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_6_SHFT                                           0x6
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_5_BMSK                                          0x20
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_5_SHFT                                           0x5
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_4_BMSK                                          0x10
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_4_SHFT                                           0x4
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_3_BMSK                                           0x8
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_3_SHFT                                           0x3
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_2_BMSK                                           0x4
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_2_SHFT                                           0x2
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_1_BMSK                                           0x2
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_1_SHFT                                           0x1
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_0_BMSK                                           0x1
#define HWIO_LPASS_SB_VFR_IRQ_CTL_SB_VFR_IRQ_CTL_SEL_0_SHFT                                           0x0

#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00044004)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00044004)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_RMSK                                                           0x1ff
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_VFR_IRQ_CTL_ADDR, HWIO_LPASS_LPAIF_VFR_IRQ_CTL_RMSK)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_VFR_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_VFR_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_VFR_IRQ_CTL_ADDR,m,v,HWIO_LPASS_LPAIF_VFR_IRQ_CTL_IN)
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_3_BMSK                             0x100
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_3_SHFT                               0x8
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_2_BMSK                              0x80
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_2_SHFT                               0x7
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_1_BMSK                              0x40
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_1_SHFT                               0x6
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_0_BMSK                              0x20
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RWDMA_SEL_0_SHFT                               0x5
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_4_BMSK                               0x10
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_4_SHFT                                0x4
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_3_BMSK                                0x8
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_3_SHFT                                0x3
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_2_BMSK                                0x4
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_2_SHFT                                0x2
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_1_BMSK                                0x2
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_1_SHFT                                0x1
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_0_BMSK                                0x1
#define HWIO_LPASS_LPAIF_VFR_IRQ_CTL_LPAIF_VFR_IRQ_CTL_RDMA_SEL_0_SHFT                                0x0

#define HWIO_LPASS_WCN_VFR_IRQ_CTL_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00044008)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00044008)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_RMSK                                                               0x1
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_WCN_VFR_IRQ_CTL_ADDR, HWIO_LPASS_WCN_VFR_IRQ_CTL_RMSK)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_WCN_VFR_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_WCN_VFR_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_WCN_VFR_IRQ_CTL_ADDR,m,v,HWIO_LPASS_WCN_VFR_IRQ_CTL_IN)
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_SEL_BMSK                                                           0x1
#define HWIO_LPASS_WCN_VFR_IRQ_CTL_SEL_SHFT                                                           0x0

#define HWIO_LPASS_AVT_VFR_IRQ_CTL_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0004400c)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0004400c)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_RMSK                                                               0x1
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AVT_VFR_IRQ_CTL_ADDR, HWIO_LPASS_AVT_VFR_IRQ_CTL_RMSK)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AVT_VFR_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AVT_VFR_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AVT_VFR_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AVT_VFR_IRQ_CTL_IN)
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_SEL_BMSK                                                           0x1
#define HWIO_LPASS_AVT_VFR_IRQ_CTL_SEL_SHFT                                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_PUB_REG_BASE                                              (LPASS_BASE      + 0x00200000)
#define LPASS_QDSP6SS_PUB_REG_BASE_OFFS                                         0x00200000

#define HWIO_LPASS_QDSP6SS_VERSION_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, HWIO_LPASS_QDSP6SS_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_BMSK                                   0xf0000000
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_SHFT                                         0x1c
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_BMSK                                    0xfff0000
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_SHFT                                         0x10
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_BMSK                                        0xffff
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_RST_EVB_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_RMSK                                          0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, HWIO_LPASS_QDSP6SS_RST_EVB_RMSK)
#define HWIO_LPASS_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_QDSP6SS_RST_EVB_IN)
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_BMSK                                      0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_SHFT                                            0x4

#define HWIO_LPASS_QDSP6SS_RESET_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_RMSK                                               0x1ff7
#define HWIO_LPASS_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, HWIO_LPASS_QDSP6SS_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_RESET_IN)
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                0x1000
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                   0xc
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                               0x800
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                 0xb
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                  0x400
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                    0xa
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_BMSK                                     0x200
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_SHFT                                       0x9
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_BMSK                                      0x100
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_SHFT                                        0x8
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_BMSK                                       0x80
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_SHFT                                        0x7
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_BMSK                                       0x40
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_SHFT                                        0x6
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_BMSK                                       0x20
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_SHFT                                        0x5
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                   0x10
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                    0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK                                         0xffff0003
#define HWIO_LPASS_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                              0xff000000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                    0x18
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                 0xff0000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_RET_CFG_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_RMSK                                                0x3
#define HWIO_LPASS_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, HWIO_LPASS_QDSP6SS_RET_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_RET_CFG_IN)
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK                                            0x30f
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                           0x200
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                             0x9
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                         0x100
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                           0x8
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                  0xc
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                      0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                      0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK                                          0x1f
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                               0x1e
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK                                   0x80000013
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                          0x80000000
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                          0x10
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                           0x4
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK                                        0x71f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                0x700
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                 0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK                                          0x77fe0ff
#define HWIO_LPASS_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                               0x4000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                    0x1a
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                  0x2000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                       0x19
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                   0x1000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                        0x18
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                             0x400000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                 0x16
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                  0x200000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                      0x15
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                  0x100000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                      0x14
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                  0x80000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                     0x13
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_BMSK                              0x40000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_SHFT                                 0x12
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_BMSK                             0x20000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_SHFT                                0x11
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                           0x10000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                              0x10
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1IU_SLP_NRET_N_BMSK                             0x8000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1IU_SLP_NRET_N_SHFT                                0xf
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1DU_SLP_NRET_N_BMSK                             0x4000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1DU_SLP_NRET_N_SHFT                                0xe
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                           0x2000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                              0xd
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                             0xff
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK                                        0xffff
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP_CLK_EN_BMSK                              0x8000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP_CLK_EN_SHFT                                 0xf
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM2_CLK_EN_BMSK                           0x4000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM2_CLK_EN_SHFT                              0xe
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                            0x2000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                               0xd
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_BMSK                            0x1000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_SHFT                               0xc
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                             0x800
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                               0xb
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                             0x400
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                               0xa
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                        0x300
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                          0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_BMSK                              0x80
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_SHFT                               0x7
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                        0x60
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                         0x5
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                         0x10
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                          0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                           0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                           0x3
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                               0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                               0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK                                         0x80000001
#define HWIO_LPASS_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_XO_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                  0x80000000
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                        0x1f
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK                                      0x80000001
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                               0x80000000
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                     0x1f
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_NMI_ADDR                                             (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_OFFS                                             (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_RMSK                                                    0x3
#define HWIO_LPASS_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_NMI_ADDR,v)
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                       0x2
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                       0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK                                             0x3
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK                                         0x500ff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG0_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_BMSK                                0x4000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_SHFT                                     0x1a
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_BMSK                                 0x1000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_SHFT                                      0x18
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_BMSK                                   0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_SHFT                                      0x8

#define HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK                                            0x3fff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG1_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SEL_BMSK                          0x2000
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SEL_SHFT                             0xd
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SW_BMSK                           0x1f00
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SW_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_BMSK                                      0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK                                            0xffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG2_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_REF_CTL_BMSK                                    0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_REF_CTL_SHFT                                       0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IDAC_CTL1_BMSK                                    0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IDAC_CTL1_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK                                       0x37f7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_BMSK                          0x20000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_SHFT                             0x11
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_BMSK                      0x10000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_SHFT                         0x10
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_BMSK                               0x7f00
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_BMSK                                 0x7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_RMSK                                 0xffffff
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_MSB_BMSK                          0xff0000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_MSB_SHFT                              0x10
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_LSB_BMSK                            0xff00
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_LSB_SHFT                               0x8
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OSC_CTL_BMSK                             0xff
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OSC_CTL_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_RMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_BMSK                       0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000068)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000068)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK                                            0x3
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK                                       0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_TCM_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                             0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                   0x12

#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                                       0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000114)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000114)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK                                   0x800000ff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SEL_BMSK                 0x80000000
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SEL_SHFT                       0x1f
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                           0xff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_LPASS_QDSP6SS_DCC_CTRL_IN)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_BMSK                                   0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                     0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                            0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                     0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                            0xe

#define HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_MODE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                           0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                 0x1f
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                        0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                              0x1e
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                          0x20000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                0x1d
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_BMSK                      0x1f000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_SHFT                            0x18
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK               0x800000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                   0x17
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                               0x400000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                   0x16
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                       0x200000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                           0x15
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                         0x100000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                             0x14
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                            0xfc000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                0xe
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                             0x3f00
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_BMSK                              0xf0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_SHFT                               0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                   0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                   0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK                                           0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                     0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK                                   0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK                                       0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                       0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                  0xf0000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                        0x1c
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                    0x8000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                         0x1b
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                   0x6000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                        0x19
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_BMSK                            0x1000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_SHFT                                 0x18
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                    0xc00000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                        0x16
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_BMSK                              0x300000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT                                  0x14
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                     0xf8000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                         0xf
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                          0x7000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                             0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_BMSK                          0xf00
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT                            0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_BMSK                               0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_SHFT                                0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                          0x60
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                           0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                           0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                            0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                           0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                           0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                             0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                             0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_12_BMSK                0xfffff000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_12_SHFT                       0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                0x800
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                  0xb
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                       0x700
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                         0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_BMSK                                    0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_SHFT                                     0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_BMSK                            0x40
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_SHFT                             0x6
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_BMSK                             0x38
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK          0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                0x1f
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK               0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                     0x1e
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK          0x3c000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                0x1a
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK              0x3800000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                   0x17
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                  0x700000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                      0x14
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                  0xff000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                      0xc
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                  0xf00
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                    0x8
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RESERVE_BITS7_6_BMSK                        0xc0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RESERVE_BITS7_6_SHFT                         0x6
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_BMSK                              0x30
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_SHFT                               0x4
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_BMSK                                     0xf
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                      0xe0000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                            0x1d
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_BMSK                                0x10000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_SHFT                                      0x1c
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_BMSK                        0xc000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_SHFT                             0x1a
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK               0x2000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                    0x19
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                            0x1e00000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                 0x15
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                    0x100000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                        0x14
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                            0xfe000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                        0x1000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                           0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                            0x800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                              0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_BMSK                               0x700
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_SHFT                                 0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_BMSK                                 0x80
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_SHFT                                  0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_SHFT                               0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                               0x30
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                 0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_BMSK                0xffffc000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_SHFT                       0xe
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                0x2000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                   0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                       0x1800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                          0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                           0x600
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                             0x9
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_BMSK                                0x100
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                              0xe0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                               0x5
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_BMSK                              0x10
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_SHFT                               0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                            0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                            0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                        0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                         0x0

#define HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_RMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_EXT_PD_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_RMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_PD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK                                    0xff03ffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                          0xff000000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                0x18
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                            0x20000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                               0x11
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                0x10000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                   0x10
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                    0xffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                            0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                            0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK                                          0x7f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                            0x40
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                             0x6
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                           0x20
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                            0x5
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                              0x1f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK                                   0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_BMSK                            0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK                                      0xffffff
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                          0xffffe0
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                               0x5
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                  0x10
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                   0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                           0x8
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                           0x3
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK                                          0x3ffff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_ATEST_IN)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_BMSK                                0x20000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_SHFT                                   0x11
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_BMSK                                0x10000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_SHFT                                   0x10
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_BMSK                                0xff00
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_SHFT                                   0x8
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_BMSK                                  0xff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR                              (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002020)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_OFFS                              (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002020)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_RMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR, HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_VALUE_BMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_VALUE_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR                             (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002024)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_OFFS                             (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002024)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_RMSK                             0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR, HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_VALUE_BMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_VALUE_SHFT                              0x0


#endif /* __HALCLKHWIOASM_H__ */
