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
    LPASS_QDSP6SS_PUBLIC
    TCSR_TCSR_REGS

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

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/inc/HALclkHWIOASM.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*
 * HWIO base definitions
 */
#define LPASS_BASE                 LPASS_BASE_PHYS
#define LPASS_BASE_PHYS            0x09000000
#define LPASS_LPASS_BASE           LPASS_BASE
#define LPASS_BASE_SIZE            0x00400000
#define CORE_TOP_CSR_BASE          0x00700000


/*----------------------------------------------------------------------------
 * MODULE: LPASS_LPASS_CC_REG
 *--------------------------------------------------------------------------*/

#define LPASS_LPASS_CC_REG_REG_BASE                                                                                  (LPASS_BASE      + 0x00000000)
#define LPASS_LPASS_CC_REG_REG_BASE_OFFS                                                                             0x00000000

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK                                                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                               0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                                     0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                            0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                                  0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                                              0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                    0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_BMSK                                                          0x1f000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                0x18
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                   0x800000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                       0x17
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_BMSK                                                                   0x400000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_SHFT                                                                       0x16
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                           0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                               0x15
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                             0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                                 0x14
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                                0xfc000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                    0xe
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                                 0x3f00
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_BMSK                                                                  0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                   0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_BMSK                                                                       0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_SHFT                                                                       0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_BMSK                                                                       0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_SHFT                                                                       0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                                      0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                                       0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK                                                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_BMSK                                                         0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_SHFT                                                                0x8
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_BMSK                                                                           0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_SHFT                                                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                               0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                   0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                          0x8
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                           0xff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                                                      0xfe000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                                            0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_BMSK                                                                0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_SHFT                                                                     0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_BMSK                                                        0xffc000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_SHFT                                                             0xe
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_BMSK                                                                  0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_SHFT                                                                     0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                                           0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                                             0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                                                                 0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                                                                   0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                   0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                    0x7
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                              0x60
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                               0x5
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                               0x10
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                               0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                               0x3
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                                0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                                0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                                0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_BMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_BMSK                                                    0xfffc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_SHFT                                                          0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_BMSK                                                              0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_SHFT                                                                 0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_BMSK                                                                  0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_SHFT                                                                     0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_BMSK                                                                0x6000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_SHFT                                                                   0xd
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                                                0x1800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                                                   0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                                               0x400
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                                                 0xa
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_BMSK                                                                    0x200
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_SHFT                                                                      0x9
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_BMSK                                                                   0x1c0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_SHFT                                                                     0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_BMSK                                                               0x30
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_BMSK                                                                0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_SHFT                                                                0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_BMSK                                                                 0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_BMSK                                                      0xff800000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_SHFT                                                            0x17
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_BMSK                                                                       0x700000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_SHFT                                                                           0x14
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_BMSK                                                                       0x80000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_SHFT                                                                          0x13
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_BMSK                                                                       0x60000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_SHFT                                                                          0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                                              0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                                                 0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_BMSK                                                          0xfc00
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_SHFT                                                             0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_BMSK                                                                    0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_SHFT                                                                      0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                   0x180
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                     0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                                  0x40
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                   0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                   0x30
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                    0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                     0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                     0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                     0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_BMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                                              0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_BMSK                                                             0xfffc
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_SHFT                                                                0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_BMSK                                                                   0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_SHFT                                                                   0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK                                                                             0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX2_CGC_EN_BMSK                                                             0x8
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX2_CGC_EN_SHFT                                                             0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                              0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                              0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_BMSK                                                         0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_SHFT                                                         0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                             0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK                                                                            0x3f03f
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_EARLY_DIV_BMSK                                                              0x38000
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_EARLY_DIV_SHFT                                                                  0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK                                                                0x7000
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_SHFT                                                                   0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_BMSK                                                                   0x38
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_SHFT                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                   0x7
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                   0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_BMSK                                                    0xffff0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_SHFT                                                          0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_BMSK                                                                     0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_SHFT                                                                        0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                           0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK                                                                 0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                               0xffffff00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                      0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                       0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                        0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK                                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                  0xf0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                        0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                                                    0x8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                                                         0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                                                   0x6000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                                                        0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_BMSK                                                            0x1000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_SHFT                                                                 0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                                                    0xc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                                        0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_BMSK                                                              0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_SHFT                                                                  0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_BMSK                                                     0xc0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_SHFT                                                        0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_BMSK                                                    0x38000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_SHFT                                                        0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                          0x7000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                             0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                          0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                            0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_BMSK                                                               0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                          0x60
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                           0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                           0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                            0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                           0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                           0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                            0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                            0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                             0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                             0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                            0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_BMSK                                                0xfffff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_SHFT                                                       0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                  0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                       0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                         0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_BMSK                                                                    0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_SHFT                                                                     0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                            0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                             0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_BMSK                                                             0x38
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_SHFT                                                              0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_BMSK                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_SHFT                                                                0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                                              0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                                              0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                                              0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                                              0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK                                          0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                                                0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                                               0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                                                     0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK                                          0x3c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                                                0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                                              0x3800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                                                   0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                                                  0x700000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                                                      0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                                                  0xff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                                                      0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                                                  0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                                                    0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                   0xc0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                    0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                                              0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                                               0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_BMSK                                                                     0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK                                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                                                      0xe0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                                                            0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_BMSK                                                       0x1c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_SHFT                                                             0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                                               0x2000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                                                    0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_BMSK                                                            0x1f00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_SHFT                                                                 0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                                                     0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                                        0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_BMSK                                                            0x7e000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                                                        0x1000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                                                           0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                            0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                              0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_BMSK                                                               0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                 0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_BMSK                                                                 0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_SHFT                                                                  0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                              0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                               0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                               0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_BMSK                                                0xffc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_SHFT                                                      0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_BMSK                                               0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_SHFT                                                   0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_BMSK                                               0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_SHFT                                                  0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_BMSK                                                    0x60000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_SHFT                                                       0x11
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_BMSK                                                          0x18000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_SHFT                                                              0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_BMSK                                                        0x4000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_SHFT                                                           0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                                                0x2000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                                                   0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                                                       0x1800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                                                          0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                           0x600
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                             0x9
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_BMSK                                                          0x100
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_SHFT                                                            0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                                              0xe0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                                               0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                                              0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                                               0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                                            0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                                            0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                                        0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                                        0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                                                         0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_BMSK                                                           0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_SHFT                                                                 0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                        0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                              0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_BMSK                                                          0x20000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_BMSK                                                      0x1f000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_SHFT                                                            0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                               0x800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                   0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_BMSK                                                               0x400000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_SHFT                                                                   0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                       0x200000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                           0x15
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                         0x100000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                             0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                            0xfc000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                             0x3f00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_BMSK                                                              0xf0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_SHFT                                                               0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_BMSK                                                                   0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_SHFT                                                                   0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_BMSK                                                                   0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_SHFT                                                                   0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_BMSK                                                                   0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_SHFT                                                                   0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_BMSK                                                          0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK                                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                 0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                        0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK                                                                         0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                          0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                          0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                         0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                         0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_BMSK                                                    0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_SHFT                                                    0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_BMSK                                                        0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_SHFT                                                        0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK                                                                        0x3f03f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_EARLY_DIV_BMSK                                                          0x38000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_EARLY_DIV_SHFT                                                              0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK                                                            0x7000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_AUX2_DIV_SHFT                                                               0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_AUX_DIV_BMSK                                                               0x38
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_AUX_DIV_SHFT                                                                0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                               0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                               0x0

#define HWIO_LPASS_REF_CLK_SRC_SEL_ADDR                                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00002000)
#define HWIO_LPASS_REF_CLK_SRC_SEL_OFFS                                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_REF_CLK_SRC_SEL_RMSK                                                                                     0x1
#define HWIO_LPASS_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                                     0x1
#define HWIO_LPASS_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                                     0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK                                                                                  0xff
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_APPS_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_BMSK                                                                  0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_SHFT                                                                   0x3
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_BMSK                                                                       0x4
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_SHFT                                                                       0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_BMSK                                                                  0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_SHFT                                                                  0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_BMSK                                                                      0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_SHFT                                                                      0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK                                                                               0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_BMSK                                                                    0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_SHFT                                                                    0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_BMSK                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_SHFT                                                                   0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK                                                                              0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_BMSK                                                              0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_SHFT                                                               0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_BMSK                                                                   0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_SHFT                                                                   0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_BMSK                                                              0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_SHFT                                                              0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_BMSK                                                                  0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006000)
#define HWIO_LPASS_AUDIO_CORE_BCR_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_AUDIO_CORE_BCR_RMSK                                                                               0x80000007
#define HWIO_LPASS_AUDIO_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_BMSK                                                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_SHFT                                                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_BMSK                                                                          0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_SHFT                                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_BMSK                                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_SHFT                                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK                                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_SHFT                                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK                                                                      0x80000003
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_BMSK                                                                 0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_SHFT                                                                       0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_BMSK                                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_SHFT                                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008000)
#define HWIO_LPASS_Q6SS_BCR_OFFS                                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_Q6SS_BCR_RMSK                                                                                     0x80000003
#define HWIO_LPASS_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, HWIO_LPASS_Q6SS_BCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_IN)
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_BMSK                                                                          0x80000000
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_SHFT                                                                                0x1f
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_BMSK                                                                                     0x2
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_SHFT                                                                                     0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_BMSK                                                                                   0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_SHFT                                                                                   0x0

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK                                                                             0xf8ffffff
#define HWIO_LPASS_AUDIO_CORE_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_BMSK                                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_SHFT                                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_BMSK                                                                  0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_SHFT                                                                        0x1b
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_BMSK                                                                  0xf00000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_SHFT                                                                      0x14
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_BMSK                                                                    0xf0000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_SHFT                                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_BMSK                                                                    0xf000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_SHFT                                                                       0xc
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                 0x800
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                   0xb
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_BMSK                                                                          0x400
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_SHFT                                                                            0xa
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_BMSK                                                                             0x200
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_SHFT                                                                               0x9
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_BMSK                                                                           0x100
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_SHFT                                                                             0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_BMSK                                                                           0x80
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_SHFT                                                                            0x7
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_BMSK                                                                            0x40
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_SHFT                                                                             0x6
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_BMSK                                                                          0x20
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_SHFT                                                                           0x5
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_BMSK                                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_SHFT                                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_BMSK                                                                            0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_SHFT                                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_BMSK                                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_SHFT                                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_BMSK                                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_SHFT                                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_BMSK                                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_SHFT                                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK                                                                      0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_BMSK                                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_SHFT                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                             0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                                   0x1b
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                                0x7800000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                                     0x17
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                               0x780000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                                   0x13
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                                  0x78000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                                      0xf
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                              0x4000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                                 0xe
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                            0x2000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                               0xd
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                                         0x1fe0
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                            0x5
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                                0x1e
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK                                                                               0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                              0x0

#define HWIO_LPASS_Q6_SMMU_GDSCR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_RMSK                                                                                0xf8ffffff
#define HWIO_LPASS_Q6_SMMU_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR, HWIO_LPASS_Q6_SMMU_GDSCR_RMSK)
#define HWIO_LPASS_Q6_SMMU_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR,m,v,HWIO_LPASS_Q6_SMMU_GDSCR_IN)
#define HWIO_LPASS_Q6_SMMU_GDSCR_PWR_ON_BMSK                                                                         0x80000000
#define HWIO_LPASS_Q6_SMMU_GDSCR_PWR_ON_SHFT                                                                               0x1f
#define HWIO_LPASS_Q6_SMMU_GDSCR_GDSC_STATE_BMSK                                                                     0x78000000
#define HWIO_LPASS_Q6_SMMU_GDSCR_GDSC_STATE_SHFT                                                                           0x1b
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_WAIT_BMSK                                                                     0xf00000
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_WAIT_SHFT                                                                         0x14
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_WAIT_BMSK                                                                       0xf0000
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_WAIT_SHFT                                                                          0x10
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DIS_WAIT_BMSK                                                                       0xf000
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DIS_WAIT_SHFT                                                                          0xc
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                    0x800
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                      0xb
#define HWIO_LPASS_Q6_SMMU_GDSCR_RESTORE_BMSK                                                                             0x400
#define HWIO_LPASS_Q6_SMMU_GDSCR_RESTORE_SHFT                                                                               0xa
#define HWIO_LPASS_Q6_SMMU_GDSCR_SAVE_BMSK                                                                                0x200
#define HWIO_LPASS_Q6_SMMU_GDSCR_SAVE_SHFT                                                                                  0x9
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_BMSK                                                                              0x100
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_SHFT                                                                                0x8
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_BMSK                                                                              0x80
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_SHFT                                                                               0x7
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_BMSK                                                                               0x40
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_SHFT                                                                                0x6
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLAMP_IO_BMSK                                                                             0x20
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLAMP_IO_SHFT                                                                              0x5
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DISABLE_BMSK                                                                          0x10
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DISABLE_SHFT                                                                           0x4
#define HWIO_LPASS_Q6_SMMU_GDSCR_PD_ARES_BMSK                                                                               0x8
#define HWIO_LPASS_Q6_SMMU_GDSCR_PD_ARES_SHFT                                                                               0x3
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_OVERRIDE_BMSK                                                                           0x4
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_OVERRIDE_SHFT                                                                           0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_HW_CONTROL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_HW_CONTROL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_COLLAPSE_BMSK                                                                           0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_COLLAPSE_SHFT                                                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b008)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b008)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK                                                            0xffffffff
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                            0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                  0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                  0x78000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                        0x1b
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                     0x7800000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                          0x17
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                    0x780000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                        0x13
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                       0x78000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                           0xf
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                              0x1fe0
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                 0x5
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                     0x1e
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                       0x0

#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RMSK                                                                                  0x3
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR, HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RMSK)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR,m,v,HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_IN)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                            0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                            0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                                 0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                                 0x0

#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_SPKR_M_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d008)
#define HWIO_LPASS_LPAIF_SPKR_M_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d008)
#define HWIO_LPASS_LPAIF_SPKR_M_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_SPKR_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, HWIO_LPASS_LPAIF_SPKR_M_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_M_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_M_IN)
#define HWIO_LPASS_LPAIF_SPKR_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_LPAIF_SPKR_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_LPAIF_SPKR_N_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d00c)
#define HWIO_LPASS_LPAIF_SPKR_N_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d00c)
#define HWIO_LPASS_LPAIF_SPKR_N_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_SPKR_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, HWIO_LPASS_LPAIF_SPKR_N_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_N_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_N_IN)
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_SPKR_D_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d010)
#define HWIO_LPASS_LPAIF_SPKR_D_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d010)
#define HWIO_LPASS_LPAIF_SPKR_D_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_SPKR_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, HWIO_LPASS_LPAIF_SPKR_D_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_D_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_D_IN)
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK                                                         0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK                                                        0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_BMSK                                                 0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_SHFT                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK                                                        0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_RMSK                                                   0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                     0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                        0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                               0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_EN_BMSK                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_EN_SHFT                                                   0x0

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e008)
#define HWIO_LPASS_LPAIF_PRI_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e008)
#define HWIO_LPASS_LPAIF_PRI_M_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_PRI_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, HWIO_LPASS_LPAIF_PRI_M_RMSK)
#define HWIO_LPASS_LPAIF_PRI_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_M_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_M_IN)
#define HWIO_LPASS_LPAIF_PRI_M_M_BMSK                                                                                    0xffff
#define HWIO_LPASS_LPAIF_PRI_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e00c)
#define HWIO_LPASS_LPAIF_PRI_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e00c)
#define HWIO_LPASS_LPAIF_PRI_N_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_PRI_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, HWIO_LPASS_LPAIF_PRI_N_RMSK)
#define HWIO_LPASS_LPAIF_PRI_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_N_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_N_IN)
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_BMSK                                                                        0xffff
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e010)
#define HWIO_LPASS_LPAIF_PRI_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e010)
#define HWIO_LPASS_LPAIF_PRI_D_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_PRI_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, HWIO_LPASS_LPAIF_PRI_D_RMSK)
#define HWIO_LPASS_LPAIF_PRI_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_D_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_D_IN)
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_BMSK                                                                               0xffff
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK                                                               0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_BMSK                                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_SHFT                                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK                                                                        0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f008)
#define HWIO_LPASS_LPAIF_SEC_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f008)
#define HWIO_LPASS_LPAIF_SEC_M_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_SEC_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, HWIO_LPASS_LPAIF_SEC_M_RMSK)
#define HWIO_LPASS_LPAIF_SEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_M_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_M_IN)
#define HWIO_LPASS_LPAIF_SEC_M_M_BMSK                                                                                    0xffff
#define HWIO_LPASS_LPAIF_SEC_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f00c)
#define HWIO_LPASS_LPAIF_SEC_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f00c)
#define HWIO_LPASS_LPAIF_SEC_N_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_SEC_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, HWIO_LPASS_LPAIF_SEC_N_RMSK)
#define HWIO_LPASS_LPAIF_SEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_N_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_N_IN)
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_BMSK                                                                        0xffff
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f010)
#define HWIO_LPASS_LPAIF_SEC_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f010)
#define HWIO_LPASS_LPAIF_SEC_D_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_SEC_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, HWIO_LPASS_LPAIF_SEC_D_RMSK)
#define HWIO_LPASS_LPAIF_SEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_D_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_D_IN)
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_BMSK                                                                               0xffff
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK                                                               0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_BMSK                                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_SHFT                                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK                                                                        0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010008)
#define HWIO_LPASS_LPAIF_TER_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010008)
#define HWIO_LPASS_LPAIF_TER_M_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_TER_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, HWIO_LPASS_LPAIF_TER_M_RMSK)
#define HWIO_LPASS_LPAIF_TER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_M_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_M_ADDR,m,v,HWIO_LPASS_LPAIF_TER_M_IN)
#define HWIO_LPASS_LPAIF_TER_M_M_BMSK                                                                                    0xffff
#define HWIO_LPASS_LPAIF_TER_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001000c)
#define HWIO_LPASS_LPAIF_TER_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001000c)
#define HWIO_LPASS_LPAIF_TER_N_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_TER_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, HWIO_LPASS_LPAIF_TER_N_RMSK)
#define HWIO_LPASS_LPAIF_TER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_N_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_N_ADDR,m,v,HWIO_LPASS_LPAIF_TER_N_IN)
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_BMSK                                                                        0xffff
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010010)
#define HWIO_LPASS_LPAIF_TER_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010010)
#define HWIO_LPASS_LPAIF_TER_D_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_TER_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, HWIO_LPASS_LPAIF_TER_D_RMSK)
#define HWIO_LPASS_LPAIF_TER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_D_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_D_ADDR,m,v,HWIO_LPASS_LPAIF_TER_D_IN)
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_BMSK                                                                               0xffff
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK                                                               0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_BMSK                                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_SHFT                                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK                                                                        0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011008)
#define HWIO_LPASS_LPAIF_QUAD_M_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011008)
#define HWIO_LPASS_LPAIF_QUAD_M_RMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, HWIO_LPASS_LPAIF_QUAD_M_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_M_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_M_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_M_IN)
#define HWIO_LPASS_LPAIF_QUAD_M_M_BMSK                                                                                   0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001100c)
#define HWIO_LPASS_LPAIF_QUAD_N_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001100c)
#define HWIO_LPASS_LPAIF_QUAD_N_RMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, HWIO_LPASS_LPAIF_QUAD_N_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_N_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_N_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_N_IN)
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_BMSK                                                                       0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011010)
#define HWIO_LPASS_LPAIF_QUAD_D_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011010)
#define HWIO_LPASS_LPAIF_QUAD_D_RMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, HWIO_LPASS_LPAIF_QUAD_D_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_D_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_D_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_D_IN)
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_BMSK                                                                              0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK                                                              0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_BMSK                                                       0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_SHFT                                                            0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK                                                              0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK                                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK                                                         0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                           0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                              0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                     0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                      0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_SHFT                                                         0x0

#define HWIO_LPASS_AON_CMD_RCGR_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012000)
#define HWIO_LPASS_AON_CMD_RCGR_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_AON_CMD_RCGR_RMSK                                                                                 0x800000f3
#define HWIO_LPASS_AON_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, HWIO_LPASS_AON_CMD_RCGR_RMSK)
#define HWIO_LPASS_AON_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AON_CMD_RCGR_IN)
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_BMSK                                                                        0x80000000
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_SHFT                                                                              0x1f
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_BMSK                                                                               0x80
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_SHFT                                                                                0x7
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_BMSK                                                                               0x40
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_SHFT                                                                                0x6
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_BMSK                                                                               0x20
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_SHFT                                                                                0x5
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                        0x10
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                         0x4
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_BMSK                                                                                0x2
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_SHFT                                                                                0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_BMSK                                                                                 0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_SHFT                                                                                 0x0

#define HWIO_LPASS_AON_CFG_RCGR_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012004)
#define HWIO_LPASS_AON_CFG_RCGR_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_AON_CFG_RCGR_RMSK                                                                                     0x771f
#define HWIO_LPASS_AON_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, HWIO_LPASS_AON_CFG_RCGR_RMSK)
#define HWIO_LPASS_AON_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AON_CFG_RCGR_IN)
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                         0x4000
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                            0xe
#define HWIO_LPASS_AON_CFG_RCGR_MODE_BMSK                                                                                0x3000
#define HWIO_LPASS_AON_CFG_RCGR_MODE_SHFT                                                                                   0xc
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_BMSK                                                                              0x700
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_SHFT                                                                                0x8
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_BMSK                                                                               0x1f
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_SHFT                                                                                0x0

#define HWIO_LPASS_AON_M_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012008)
#define HWIO_LPASS_AON_M_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012008)
#define HWIO_LPASS_AON_M_RMSK                                                                                              0xff
#define HWIO_LPASS_AON_M_IN          \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, HWIO_LPASS_AON_M_RMSK)
#define HWIO_LPASS_AON_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, m)
#define HWIO_LPASS_AON_M_OUT(v)      \
        out_dword(HWIO_LPASS_AON_M_ADDR,v)
#define HWIO_LPASS_AON_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_M_ADDR,m,v,HWIO_LPASS_AON_M_IN)
#define HWIO_LPASS_AON_M_M_BMSK                                                                                            0xff
#define HWIO_LPASS_AON_M_M_SHFT                                                                                             0x0

#define HWIO_LPASS_AON_N_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001200c)
#define HWIO_LPASS_AON_N_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001200c)
#define HWIO_LPASS_AON_N_RMSK                                                                                              0xff
#define HWIO_LPASS_AON_N_IN          \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, HWIO_LPASS_AON_N_RMSK)
#define HWIO_LPASS_AON_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, m)
#define HWIO_LPASS_AON_N_OUT(v)      \
        out_dword(HWIO_LPASS_AON_N_ADDR,v)
#define HWIO_LPASS_AON_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_N_ADDR,m,v,HWIO_LPASS_AON_N_IN)
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_BMSK                                                                                0xff
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_SHFT                                                                                 0x0

#define HWIO_LPASS_AON_D_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012010)
#define HWIO_LPASS_AON_D_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012010)
#define HWIO_LPASS_AON_D_RMSK                                                                                              0xff
#define HWIO_LPASS_AON_D_IN          \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, HWIO_LPASS_AON_D_RMSK)
#define HWIO_LPASS_AON_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, m)
#define HWIO_LPASS_AON_D_OUT(v)      \
        out_dword(HWIO_LPASS_AON_D_ADDR,v)
#define HWIO_LPASS_AON_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_D_ADDR,m,v,HWIO_LPASS_AON_D_IN)
#define HWIO_LPASS_AON_D_NOT_2D_BMSK                                                                                       0xff
#define HWIO_LPASS_AON_D_NOT_2D_SHFT                                                                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK                                                                       0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_ATIME_CMD_RCGR_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013000)
#define HWIO_LPASS_ATIME_CMD_RCGR_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_ATIME_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_ATIME_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, HWIO_LPASS_ATIME_CMD_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CMD_RCGR_IN)
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_ATIME_CFG_RCGR_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013004)
#define HWIO_LPASS_ATIME_CFG_RCGR_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_ATIME_CFG_RCGR_RMSK                                                                                   0x771f
#define HWIO_LPASS_ATIME_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, HWIO_LPASS_ATIME_CFG_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CFG_RCGR_IN)
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                       0x4000
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                          0xe
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_ATIME_M_ADDR                                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013008)
#define HWIO_LPASS_ATIME_M_OFFS                                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013008)
#define HWIO_LPASS_ATIME_M_RMSK                                                                                            0xff
#define HWIO_LPASS_ATIME_M_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, HWIO_LPASS_ATIME_M_RMSK)
#define HWIO_LPASS_ATIME_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, m)
#define HWIO_LPASS_ATIME_M_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_M_ADDR,v)
#define HWIO_LPASS_ATIME_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_M_ADDR,m,v,HWIO_LPASS_ATIME_M_IN)
#define HWIO_LPASS_ATIME_M_M_BMSK                                                                                          0xff
#define HWIO_LPASS_ATIME_M_M_SHFT                                                                                           0x0

#define HWIO_LPASS_ATIME_N_ADDR                                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001300c)
#define HWIO_LPASS_ATIME_N_OFFS                                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001300c)
#define HWIO_LPASS_ATIME_N_RMSK                                                                                            0xff
#define HWIO_LPASS_ATIME_N_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, HWIO_LPASS_ATIME_N_RMSK)
#define HWIO_LPASS_ATIME_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, m)
#define HWIO_LPASS_ATIME_N_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_N_ADDR,v)
#define HWIO_LPASS_ATIME_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_N_ADDR,m,v,HWIO_LPASS_ATIME_N_IN)
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_BMSK                                                                              0xff
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_SHFT                                                                               0x0

#define HWIO_LPASS_ATIME_D_ADDR                                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013010)
#define HWIO_LPASS_ATIME_D_OFFS                                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013010)
#define HWIO_LPASS_ATIME_D_RMSK                                                                                            0xff
#define HWIO_LPASS_ATIME_D_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, HWIO_LPASS_ATIME_D_RMSK)
#define HWIO_LPASS_ATIME_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, m)
#define HWIO_LPASS_ATIME_D_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_D_ADDR,v)
#define HWIO_LPASS_ATIME_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_D_ADDR,m,v,HWIO_LPASS_ATIME_D_IN)
#define HWIO_LPASS_ATIME_D_NOT_2D_BMSK                                                                                     0xff
#define HWIO_LPASS_ATIME_D_NOT_2D_SHFT                                                                                      0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CMD_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CFG_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014008)
#define HWIO_LPASS_RESAMPLER_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014008)
#define HWIO_LPASS_RESAMPLER_M_RMSK                                                                                        0xff
#define HWIO_LPASS_RESAMPLER_M_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, HWIO_LPASS_RESAMPLER_M_RMSK)
#define HWIO_LPASS_RESAMPLER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, m)
#define HWIO_LPASS_RESAMPLER_M_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_M_ADDR,v)
#define HWIO_LPASS_RESAMPLER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_M_ADDR,m,v,HWIO_LPASS_RESAMPLER_M_IN)
#define HWIO_LPASS_RESAMPLER_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_RESAMPLER_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001400c)
#define HWIO_LPASS_RESAMPLER_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001400c)
#define HWIO_LPASS_RESAMPLER_N_RMSK                                                                                        0xff
#define HWIO_LPASS_RESAMPLER_N_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, HWIO_LPASS_RESAMPLER_N_RMSK)
#define HWIO_LPASS_RESAMPLER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, m)
#define HWIO_LPASS_RESAMPLER_N_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_N_ADDR,v)
#define HWIO_LPASS_RESAMPLER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_N_ADDR,m,v,HWIO_LPASS_RESAMPLER_N_IN)
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014010)
#define HWIO_LPASS_RESAMPLER_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014010)
#define HWIO_LPASS_RESAMPLER_D_RMSK                                                                                        0xff
#define HWIO_LPASS_RESAMPLER_D_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, HWIO_LPASS_RESAMPLER_D_RMSK)
#define HWIO_LPASS_RESAMPLER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, m)
#define HWIO_LPASS_RESAMPLER_D_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_D_ADDR,v)
#define HWIO_LPASS_RESAMPLER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_D_ADDR,m,v,HWIO_LPASS_RESAMPLER_D_IN)
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK                                                                    0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_BMSK                                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_SHFT                                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_BMSK                                                      0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_SHFT                                                         0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                    0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                       0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                   0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                      0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_BMSK                                                                  0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_SHFT                                                                    0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_BMSK                                                                    0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_SHFT                                                                     0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_BMSK                                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_SHFT                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_BMSK                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_SHFT                                                                0x0

#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK                                                                             0x771f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                 0x4000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                    0xe
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                        0x3000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                           0xc
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_AUD_SLIMBUS_M_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015008)
#define HWIO_LPASS_AUD_SLIMBUS_M_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015008)
#define HWIO_LPASS_AUD_SLIMBUS_M_RMSK                                                                                      0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, HWIO_LPASS_AUD_SLIMBUS_M_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_M_IN)
#define HWIO_LPASS_AUD_SLIMBUS_M_M_BMSK                                                                                    0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_M_SHFT                                                                                     0x0

#define HWIO_LPASS_AUD_SLIMBUS_N_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001500c)
#define HWIO_LPASS_AUD_SLIMBUS_N_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001500c)
#define HWIO_LPASS_AUD_SLIMBUS_N_RMSK                                                                                      0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, HWIO_LPASS_AUD_SLIMBUS_N_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_N_IN)
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                        0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                         0x0

#define HWIO_LPASS_AUD_SLIMBUS_D_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015010)
#define HWIO_LPASS_AUD_SLIMBUS_D_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015010)
#define HWIO_LPASS_AUD_SLIMBUS_D_RMSK                                                                                      0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, HWIO_LPASS_AUD_SLIMBUS_D_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_D_IN)
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_BMSK                                                                               0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_SHFT                                                                                0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK                                                             0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                               0x4000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                  0xe
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                             0x2000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                0xd
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                            0x1000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                               0xc
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                           0xf00
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                             0x8
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                             0xf0
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                              0x4
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK                                                                             0x771f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                 0x4000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                    0xe
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                        0x3000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                           0xc
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_QCA_SLIMBUS_M_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016008)
#define HWIO_LPASS_QCA_SLIMBUS_M_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016008)
#define HWIO_LPASS_QCA_SLIMBUS_M_RMSK                                                                                      0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, HWIO_LPASS_QCA_SLIMBUS_M_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_M_IN)
#define HWIO_LPASS_QCA_SLIMBUS_M_M_BMSK                                                                                    0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_M_SHFT                                                                                     0x0

#define HWIO_LPASS_QCA_SLIMBUS_N_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001600c)
#define HWIO_LPASS_QCA_SLIMBUS_N_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001600c)
#define HWIO_LPASS_QCA_SLIMBUS_N_RMSK                                                                                      0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, HWIO_LPASS_QCA_SLIMBUS_N_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_N_IN)
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                        0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                         0x0

#define HWIO_LPASS_QCA_SLIMBUS_D_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016010)
#define HWIO_LPASS_QCA_SLIMBUS_D_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016010)
#define HWIO_LPASS_QCA_SLIMBUS_D_RMSK                                                                                      0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, HWIO_LPASS_QCA_SLIMBUS_D_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_D_IN)
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_BMSK                                                                               0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_SHFT                                                                                0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK                                                             0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                               0x4000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                  0xe
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                             0x2000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                0xd
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                            0x1000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                               0xc
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                           0xf00
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                             0x8
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                             0xf0
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                              0x4
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK                                                                             0x771f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                 0x4000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                    0xe
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_BMSK                                                                        0x3000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_SHFT                                                                           0xc
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017008)
#define HWIO_LPASS_LPAIF_PCMOE_M_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017008)
#define HWIO_LPASS_LPAIF_PCMOE_M_RMSK                                                                                      0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, HWIO_LPASS_LPAIF_PCMOE_M_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_M_IN)
#define HWIO_LPASS_LPAIF_PCMOE_M_M_BMSK                                                                                    0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_M_SHFT                                                                                     0x0

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001700c)
#define HWIO_LPASS_LPAIF_PCMOE_N_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001700c)
#define HWIO_LPASS_LPAIF_PCMOE_N_RMSK                                                                                      0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, HWIO_LPASS_LPAIF_PCMOE_N_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_N_IN)
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_BMSK                                                                        0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017010)
#define HWIO_LPASS_LPAIF_PCMOE_D_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017010)
#define HWIO_LPASS_LPAIF_PCMOE_D_RMSK                                                                                      0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, HWIO_LPASS_LPAIF_PCMOE_D_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_D_IN)
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_BMSK                                                                               0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_SHFT                                                                                0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, HWIO_LPASS_SLEEP_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CMD_RCGR_IN)
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_RMSK                                                                                   0x371f
#define HWIO_LPASS_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, HWIO_LPASS_SLEEP_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CFG_RCGR_IN)
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019000)
#define HWIO_LPASS_XO_CMD_RCGR_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_XO_CMD_RCGR_RMSK                                                                                  0x800000f3
#define HWIO_LPASS_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, HWIO_LPASS_XO_CMD_RCGR_RMSK)
#define HWIO_LPASS_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CMD_RCGR_ADDR,m,v,HWIO_LPASS_XO_CMD_RCGR_IN)
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_BMSK                                                                         0x80000000
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_SHFT                                                                               0x1f
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_BMSK                                                                                0x80
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_SHFT                                                                                 0x7
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_BMSK                                                                                0x40
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_SHFT                                                                                 0x6
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_BMSK                                                                                0x20
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_SHFT                                                                                 0x5
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                         0x10
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                          0x4
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_BMSK                                                                                 0x2
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_SHFT                                                                                 0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_BMSK                                                                                  0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_SHFT                                                                                  0x0

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019004)
#define HWIO_LPASS_XO_CFG_RCGR_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_XO_CFG_RCGR_RMSK                                                                                      0x771f
#define HWIO_LPASS_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, HWIO_LPASS_XO_CFG_RCGR_RMSK)
#define HWIO_LPASS_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CFG_RCGR_ADDR,m,v,HWIO_LPASS_XO_CFG_RCGR_IN)
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                          0x4000
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                             0xe
#define HWIO_LPASS_XO_CFG_RCGR_MODE_BMSK                                                                                 0x3000
#define HWIO_LPASS_XO_CFG_RCGR_MODE_SHFT                                                                                    0xc
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_BMSK                                                                               0x700
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_SHFT                                                                                 0x8
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_BMSK                                                                                0x1f
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK                                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_BMSK                                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_SHFT                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_CORE_CMD_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_CORE_CMD_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_CORE_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_LPASS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_LPASS_CORE_CFG_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b004)
#define HWIO_LPASS_CORE_CFG_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b004)
#define HWIO_LPASS_CORE_CFG_RCGR_RMSK                                                                                    0x771f
#define HWIO_LPASS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                        0x4000
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                           0xe
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_LPASS_CORE_M_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b008)
#define HWIO_LPASS_CORE_M_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b008)
#define HWIO_LPASS_CORE_M_RMSK                                                                                             0xff
#define HWIO_LPASS_CORE_M_IN          \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, HWIO_LPASS_CORE_M_RMSK)
#define HWIO_LPASS_CORE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, m)
#define HWIO_LPASS_CORE_M_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_M_ADDR,v)
#define HWIO_LPASS_CORE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_M_ADDR,m,v,HWIO_LPASS_CORE_M_IN)
#define HWIO_LPASS_CORE_M_M_BMSK                                                                                           0xff
#define HWIO_LPASS_CORE_M_M_SHFT                                                                                            0x0

#define HWIO_LPASS_CORE_N_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b00c)
#define HWIO_LPASS_CORE_N_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b00c)
#define HWIO_LPASS_CORE_N_RMSK                                                                                             0xff
#define HWIO_LPASS_CORE_N_IN          \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, HWIO_LPASS_CORE_N_RMSK)
#define HWIO_LPASS_CORE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, m)
#define HWIO_LPASS_CORE_N_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_N_ADDR,v)
#define HWIO_LPASS_CORE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_N_ADDR,m,v,HWIO_LPASS_CORE_N_IN)
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_BMSK                                                                               0xff
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_SHFT                                                                                0x0

#define HWIO_LPASS_CORE_D_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b010)
#define HWIO_LPASS_CORE_D_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b010)
#define HWIO_LPASS_CORE_D_RMSK                                                                                             0xff
#define HWIO_LPASS_CORE_D_IN          \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, HWIO_LPASS_CORE_D_RMSK)
#define HWIO_LPASS_CORE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, m)
#define HWIO_LPASS_CORE_D_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_D_ADDR,v)
#define HWIO_LPASS_CORE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_D_ADDR,m,v,HWIO_LPASS_CORE_D_IN)
#define HWIO_LPASS_CORE_D_NOT_2D_BMSK                                                                                      0xff
#define HWIO_LPASS_CORE_D_NOT_2D_SHFT                                                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK                                                                     0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_BMSK                                                                   0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_SHFT                                                                     0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_BMSK                                                                     0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_SHFT                                                                      0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK                                                                         0x80000003
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_BMSK                                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_SHFT                                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_BMSK                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_SHFT                                                                     0x0

#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_EXT_MCLK0_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e008)
#define HWIO_LPASS_EXT_MCLK0_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e008)
#define HWIO_LPASS_EXT_MCLK0_M_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK0_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, HWIO_LPASS_EXT_MCLK0_M_RMSK)
#define HWIO_LPASS_EXT_MCLK0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_M_IN)
#define HWIO_LPASS_EXT_MCLK0_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_EXT_MCLK0_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_EXT_MCLK0_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e00c)
#define HWIO_LPASS_EXT_MCLK0_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e00c)
#define HWIO_LPASS_EXT_MCLK0_N_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK0_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, HWIO_LPASS_EXT_MCLK0_N_RMSK)
#define HWIO_LPASS_EXT_MCLK0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_N_IN)
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK0_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e010)
#define HWIO_LPASS_EXT_MCLK0_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e010)
#define HWIO_LPASS_EXT_MCLK0_D_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK0_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, HWIO_LPASS_EXT_MCLK0_D_RMSK)
#define HWIO_LPASS_EXT_MCLK0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_D_IN)
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_EXT_MCLK1_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f008)
#define HWIO_LPASS_EXT_MCLK1_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f008)
#define HWIO_LPASS_EXT_MCLK1_M_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK1_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, HWIO_LPASS_EXT_MCLK1_M_RMSK)
#define HWIO_LPASS_EXT_MCLK1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_M_IN)
#define HWIO_LPASS_EXT_MCLK1_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_EXT_MCLK1_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_EXT_MCLK1_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f00c)
#define HWIO_LPASS_EXT_MCLK1_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f00c)
#define HWIO_LPASS_EXT_MCLK1_N_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK1_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, HWIO_LPASS_EXT_MCLK1_N_RMSK)
#define HWIO_LPASS_EXT_MCLK1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_N_IN)
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK1_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f010)
#define HWIO_LPASS_EXT_MCLK1_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f010)
#define HWIO_LPASS_EXT_MCLK1_D_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK1_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, HWIO_LPASS_EXT_MCLK1_D_RMSK)
#define HWIO_LPASS_EXT_MCLK1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_D_IN)
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_EXT_MCLK2_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020008)
#define HWIO_LPASS_EXT_MCLK2_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020008)
#define HWIO_LPASS_EXT_MCLK2_M_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK2_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, HWIO_LPASS_EXT_MCLK2_M_RMSK)
#define HWIO_LPASS_EXT_MCLK2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_M_IN)
#define HWIO_LPASS_EXT_MCLK2_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_EXT_MCLK2_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_EXT_MCLK2_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK2_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK2_N_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK2_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, HWIO_LPASS_EXT_MCLK2_N_RMSK)
#define HWIO_LPASS_EXT_MCLK2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_N_IN)
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK2_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020010)
#define HWIO_LPASS_EXT_MCLK2_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020010)
#define HWIO_LPASS_EXT_MCLK2_D_RMSK                                                                                        0xff
#define HWIO_LPASS_EXT_MCLK2_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, HWIO_LPASS_EXT_MCLK2_D_RMSK)
#define HWIO_LPASS_EXT_MCLK2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_D_IN)
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_RMSK                                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00023000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00024000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00024000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK                                                                           0x80000003
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_BMSK                                                                           0x2
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_SHFT                                                                           0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                                       0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00025000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00025000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_RMSK                                                  0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_OFF_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_OFF_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                    0x4000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                       0xe
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                  0x2000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                     0xd
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                 0x1000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                    0xc
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_WAKEUP_BMSK                                                0xf00
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_WAKEUP_SHFT                                                  0x8
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_SLEEP_BMSK                                                  0xf0
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_SLEEP_SHFT                                                   0x4
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_HW_CTL_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_HW_CTL_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00027000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK                                                          0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_RMSK                                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_OFF_BMSK                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_OFF_SHFT                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK                                                          0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a000)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a000)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_SPDIFTX_BMC_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a004)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a004)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_RMSK                                                                             0x771f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR, HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_IN)
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                 0x4000
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                    0xe
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_BMSK                                                                        0x3000
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_MODE_SHFT                                                                           0xc
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_SPDIFTX_BMC_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_SPDIFTX_BMC_M_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a008)
#define HWIO_LPASS_SPDIFTX_BMC_M_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a008)
#define HWIO_LPASS_SPDIFTX_BMC_M_RMSK                                                                                    0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_M_ADDR, HWIO_LPASS_SPDIFTX_BMC_M_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_M_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_M_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_M_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_M_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_M_IN)
#define HWIO_LPASS_SPDIFTX_BMC_M_M_BMSK                                                                                  0xffff
#define HWIO_LPASS_SPDIFTX_BMC_M_M_SHFT                                                                                     0x0

#define HWIO_LPASS_SPDIFTX_BMC_N_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a00c)
#define HWIO_LPASS_SPDIFTX_BMC_N_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a00c)
#define HWIO_LPASS_SPDIFTX_BMC_N_RMSK                                                                                    0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_N_ADDR, HWIO_LPASS_SPDIFTX_BMC_N_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_N_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_N_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_N_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_N_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_N_IN)
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_BMSK                                                                      0xffff
#define HWIO_LPASS_SPDIFTX_BMC_N_NOT_N_MINUS_M_SHFT                                                                         0x0

#define HWIO_LPASS_SPDIFTX_BMC_D_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a010)
#define HWIO_LPASS_SPDIFTX_BMC_D_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a010)
#define HWIO_LPASS_SPDIFTX_BMC_D_RMSK                                                                                    0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_D_ADDR, HWIO_LPASS_SPDIFTX_BMC_D_RMSK)
#define HWIO_LPASS_SPDIFTX_BMC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_BMC_D_ADDR, m)
#define HWIO_LPASS_SPDIFTX_BMC_D_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_BMC_D_ADDR,v)
#define HWIO_LPASS_SPDIFTX_BMC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_BMC_D_ADDR,m,v,HWIO_LPASS_SPDIFTX_BMC_D_IN)
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_BMSK                                                                             0xffff
#define HWIO_LPASS_SPDIFTX_BMC_D_NOT_2D_SHFT                                                                                0x0

#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a014)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a014)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_BMC_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002b000)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002b000)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002c004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002c004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_BMSK                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_SHFT                                                0x0

#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002d000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002f000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002f000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK                                                                           0x80000003
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_BMSK                                                                           0x2
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_SHFT                                                                           0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                                       0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                                       0x0

#define HWIO_LPASS_DFS_HW_CTL_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032000)
#define HWIO_LPASS_DFS_HW_CTL_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032000)
#define HWIO_LPASS_DFS_HW_CTL_RMSK                                                                                   0x70000071
#define HWIO_LPASS_DFS_HW_CTL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, HWIO_LPASS_DFS_HW_CTL_RMSK)
#define HWIO_LPASS_DFS_HW_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, m)
#define HWIO_LPASS_DFS_HW_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_HW_CTL_ADDR,v)
#define HWIO_LPASS_DFS_HW_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_HW_CTL_ADDR,m,v,HWIO_LPASS_DFS_HW_CTL_IN)
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_BMSK                                                                0x70000000
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_SHFT                                                                      0x1c
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_BMSK                                                                          0x70
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_SHFT                                                                           0x4
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_BMSK                                                                            0x1
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_SHFT                                                                            0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003200c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003200c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003201c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003201c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK                                                                             0x777
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_BMSK                                                 0x700
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_SHFT                                                   0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_BMSK                                                       0x70
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_SHFT                                                        0x4
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_BMSK                                                         0x7
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003202c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003202c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003203c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003203c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK                                                                          0x1f1f1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_BMSK                                              0x1f0000
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_SHFT                                                  0x10
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_BMSK                                                     0x1f00
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_SHFT                                                        0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_BMSK                                                        0x1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_SHFT                                                         0x0

#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK                                                                                0x7
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN          \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, m)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,v)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,m,v,HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_BMSK                                                     0x4
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_SHFT                                                     0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_BMSK                                                          0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_SHFT                                                          0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_BMSK                                                           0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_SHFT                                                           0x0

#define HWIO_LPASS_DFS_PERF0_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032048)
#define HWIO_LPASS_DFS_PERF0_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032048)
#define HWIO_LPASS_DFS_PERF0_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF0_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, HWIO_LPASS_DFS_PERF0_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_CDIV_IN)
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF1_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003204c)
#define HWIO_LPASS_DFS_PERF1_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003204c)
#define HWIO_LPASS_DFS_PERF1_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF1_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, HWIO_LPASS_DFS_PERF1_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_CDIV_IN)
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF2_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032050)
#define HWIO_LPASS_DFS_PERF2_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032050)
#define HWIO_LPASS_DFS_PERF2_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF2_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, HWIO_LPASS_DFS_PERF2_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_CDIV_IN)
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF3_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032054)
#define HWIO_LPASS_DFS_PERF3_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032054)
#define HWIO_LPASS_DFS_PERF3_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF3_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, HWIO_LPASS_DFS_PERF3_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_CDIV_IN)
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF4_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032058)
#define HWIO_LPASS_DFS_PERF4_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032058)
#define HWIO_LPASS_DFS_PERF4_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF4_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, HWIO_LPASS_DFS_PERF4_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_CDIV_IN)
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF5_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003205c)
#define HWIO_LPASS_DFS_PERF5_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003205c)
#define HWIO_LPASS_DFS_PERF5_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF5_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, HWIO_LPASS_DFS_PERF5_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_CDIV_IN)
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF6_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032060)
#define HWIO_LPASS_DFS_PERF6_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032060)
#define HWIO_LPASS_DFS_PERF6_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF6_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, HWIO_LPASS_DFS_PERF6_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_CDIV_IN)
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_DFS_PERF7_CDIV_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032064)
#define HWIO_LPASS_DFS_PERF7_CDIV_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032064)
#define HWIO_LPASS_DFS_PERF7_CDIV_RMSK                                                                                     0x77
#define HWIO_LPASS_DFS_PERF7_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, HWIO_LPASS_DFS_PERF7_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_CDIV_IN)
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                    0x70
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                     0x4
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                0x7
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK                                                               0x800000f3
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_BMSK                                                             0x80
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_SHFT                                                              0x7
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_BMSK                                                             0x40
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_SHFT                                                              0x6
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_BMSK                                                             0x20
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_SHFT                                                              0x5
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                      0x10
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                       0x4
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_BMSK                                                              0x2
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_SHFT                                                              0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_BMSK                                                               0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_SHFT                                                               0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK                                                                   0x771f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                       0x4000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                          0xe
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_BMSK                                                              0x3000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_SHFT                                                                 0xc
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_BMSK                                                            0x700
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_SHFT                                                              0x8
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_BMSK                                                             0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_SHFT                                                              0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK                                                                            0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_BMSK                                                                          0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_SHFT                                                                           0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003300c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003300c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK                                                                            0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_BMSK                                                              0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_SHFT                                                               0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK                                                                            0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_BMSK                                                                     0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_SHFT                                                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK                                                              0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OFFS                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK                                                        0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003301c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003301c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OFFS                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK                                              0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                            0x2
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                            0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                              0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00036000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00036000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                     0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                      0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                            0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                 0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                   0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00037000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00037000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK                                                      0x80000001
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00039000)
#define HWIO_LPASS_DBG_CLK_OFFS                                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00039000)
#define HWIO_LPASS_DBG_CLK_RMSK                                                                                      0xfff0ffff
#define HWIO_LPASS_DBG_CLK_IN          \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, HWIO_LPASS_DBG_CLK_RMSK)
#define HWIO_LPASS_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, m)
#define HWIO_LPASS_DBG_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_DBG_CLK_ADDR,v)
#define HWIO_LPASS_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DBG_CLK_ADDR,m,v,HWIO_LPASS_DBG_CLK_IN)
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_BMSK                                                                       0xe0000000
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_SHFT                                                                             0x1d
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_BMSK                                                                     0x1c000000
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_SHFT                                                                           0x1a
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_BMSK                                                                     0x3e00000
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_SHFT                                                                          0x15
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                                         0x100000
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                                             0x14
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                                          0xffff
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                                             0x0

#define HWIO_LPASS_TEST_BUS_SEL_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00039004)
#define HWIO_LPASS_TEST_BUS_SEL_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00039004)
#define HWIO_LPASS_TEST_BUS_SEL_RMSK                                                                                        0x1
#define HWIO_LPASS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, HWIO_LPASS_TEST_BUS_SEL_RMSK)
#define HWIO_LPASS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, m)
#define HWIO_LPASS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_TEST_BUS_SEL_ADDR,v)
#define HWIO_LPASS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TEST_BUS_SEL_ADDR,m,v,HWIO_LPASS_TEST_BUS_SEL_IN)
#define HWIO_LPASS_TEST_BUS_SEL_SEL_BMSK                                                                                    0x1
#define HWIO_LPASS_TEST_BUS_SEL_SEL_SHFT                                                                                    0x0

#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003a000)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003a000)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK                                                                                  0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN          \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, m)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,v)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,m,v,HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_BMSK                                                                              0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_SHFT                                                                              0x0

#define HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003b000)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003b000)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK                                                                           0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_IN          \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, m)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUT(v)      \
        out_dword(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,v)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,m,v,HWIO_LPASS_LPASS_CC_SPARE_REG_IN)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_BMSK                                                                     0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_SHFT                                                                            0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_PUB_REG_BASE                                                (LPASS_BASE      + 0x00300000)
#define LPASS_QDSP6SS_PUB_REG_BASE_OFFS                                           0x00300000

#define HWIO_LPASS_QDSP6SS_VERSION_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_RMSK                                           0xffffffff
#define HWIO_LPASS_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, HWIO_LPASS_QDSP6SS_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_BMSK                                     0xf0000000
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_SHFT                                           0x1c
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_BMSK                                      0xfff0000
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_SHFT                                           0x10
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_BMSK                                          0xffff
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK                                         0xfff1ffff
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                           0xfff00000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                                 0x14
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_BMSK                              0x10000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_SHFT                                 0x10
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_BMSK                             0x8000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_SHFT                                0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SSC_BMSK                                      0x4000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SSC_SHFT                                         0xe
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_ON_VDDCX_BMSK                               0x2000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_ON_VDDCX_SHFT                                  0xd
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_APU_PRESENT_BMSK                                 0x1000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_APU_PRESENT_SHFT                                    0xc
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                  0x800
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                    0xb
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                  0x400
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                    0xa
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                     0x200
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                       0x9
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                  0x100
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                     0xf0
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                        0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_RST_EVB_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_RMSK                                            0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, HWIO_LPASS_QDSP6SS_RST_EVB_RMSK)
#define HWIO_LPASS_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_QDSP6SS_RST_EVB_IN)
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_BMSK                                        0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_SHFT                                              0x4

#define HWIO_LPASS_QDSP6SS_RESET_ADDR                                             (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_OFFS                                             (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_RMSK                                                 0x7ff7
#define HWIO_LPASS_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, HWIO_LPASS_QDSP6SS_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_RESET_IN)
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_BMSK                                       0x4000
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_SHFT                                          0xe
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_BMSK                                       0x2000
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_SHFT                                          0xd
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                  0x1000
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                     0xc
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                                 0x800
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                   0xb
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                    0x400
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                      0xa
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_BMSK                                       0x200
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_SHFT                                         0x9
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_BMSK                                        0x100
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_SHFT                                          0x8
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_BMSK                                         0x80
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_SHFT                                          0x7
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_BMSK                                         0x40
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_SHFT                                          0x6
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_BMSK                                         0x20
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_SHFT                                          0x5
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                     0x10
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_BMSK                                          0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_SHFT                                          0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK                                           0xffff0003
#define HWIO_LPASS_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                                0xff000000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                      0x18
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                   0xff0000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                       0x10
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_RET_CFG_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_RMSK                                                  0x3
#define HWIO_LPASS_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, HWIO_LPASS_QDSP6SS_RET_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_RET_CFG_IN)
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK                                              0x30f
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                             0x200
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                               0x9
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                           0x100
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                    0xc
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK                                            0x1f
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                                 0x1e
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK                                          0x71f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK                                            0x77fffff
#define HWIO_LPASS_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                                 0x4000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                      0x1a
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                    0x2000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                         0x19
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                     0x1000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                          0x18
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                               0x400000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                   0x16
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                    0x200000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                        0x15
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                    0x100000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                        0x14
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                    0x80000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                       0x13
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_BMSK                                0x40000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_STBY_N_SHFT                                   0x12
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_BMSK                               0x20000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ETB_SLP_NRET_N_SHFT                                  0x11
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1IU_SLP_NRET_N_BMSK                              0x18000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1IU_SLP_NRET_N_SHFT                                  0xf
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1DU_SLP_NRET_N_BMSK                               0x6000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L1DU_SLP_NRET_N_SHFT                                  0xd
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                             0x1000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                                0xc
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                               0xf00
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                                 0x8
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                               0xff
#define HWIO_LPASS_QDSP6SS_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK                                         0x6ffff
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CSI1_CLK_EN_BMSK                             0x40000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CSI1_CLK_EN_SHFT                                0x12
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CSI0_CLK_EN_BMSK                             0x20000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CSI0_CLK_EN_SHFT                                0x11
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_BMSK                               0x8000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_SHFT                                  0xf
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM2_CLK_EN_BMSK                             0x4000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM2_CLK_EN_SHFT                                0xe
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                              0x2000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                                 0xd
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_BMSK                              0x1000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIM_CLK_EN_SHFT                                 0xc
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                               0x800
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                                 0xb
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                               0x400
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                                 0xa
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                          0x300
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                            0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_BMSK                                0x80
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TCXO_CLK_EN_SHFT                                 0x7
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                          0x60
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                           0x5
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                           0x10
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                            0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK                                           0x80000001
#define HWIO_LPASS_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_XO_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                    0x80000000
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                          0x1f
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK                                        0x80000001
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                                 0x80000000
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                       0x1f
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_NMI_ADDR                                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_OFFS                                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_RMSK                                                      0x3
#define HWIO_LPASS_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_NMI_ADDR,v)
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_BMSK                                              0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK                                               0x3
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK                                             0xf
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STATERET_CTL_IN)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK                                           0x500ff7f
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG0_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_BMSK                                  0x4000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_TEST_SHFT                                       0x1a
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_BMSK                                   0x1000000
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IDAC_EN_SHFT                                        0x18
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_BMSK                                     0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_LDO_CTL1_SHFT                                        0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_SYS_CTL_BMSK                                        0x7e
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_SYS_CTL_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_SYSTEM_LOAD_EN_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_SYSTEM_LOAD_EN_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK                                              0x3fff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG1_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SEL_BMSK                            0x2000
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SEL_SHFT                               0xd
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SW_BMSK                             0x1f00
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_LDO_VREF_TRIM_SW_SHFT                                0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_BMSK                                        0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DIG_CTL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK                                              0xffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG2_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_REF_CTL_BMSK                                      0xff00
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_REF_CTL_SHFT                                         0x8
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IDAC_CTL_BMSK                                       0xff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IDAC_CTL_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK                                         0x37f7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_BMSK                            0x20000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_SHFT                               0x11
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_BMSK                                 0x7f00
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_RET_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_BMSK                                   0x7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR                                 (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OFFS                                 (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_RMSK                                   0xffffff
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_TEST_BMSK                           0xff0000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_LD_TEST_SHFT                               0x10
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_DTEST_CTL_BMSK                           0xff00
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_DTEST_CTL_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OSC_CTL_BMSK                               0xff
#define HWIO_LPASS_QDSP6SS_LDO_VREF_TEST_CFG_OSC_CTL_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_RMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_BMSK                         0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_SHFT                         0x0

#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000068)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000068)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_RMSK                                       0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_LD_DATA_ADDR, HWIO_LPASS_QDSP6SS_LDO_LD_DATA_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_LD_DATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_LD_DATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_LD_DATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_LD_DATA_IN)
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_LD_DATA2_BMSK                              0xffff0000
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_LD_DATA2_SHFT                                    0x10
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_LD_DATA1_BMSK                                  0xffff
#define HWIO_LPASS_QDSP6SS_LDO_LD_DATA_LD_DATA1_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_STATUS_BMSK                                 0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_STATUS_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK                                        0x3f
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_BMSK                          0x3e
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_BHS_CTL_ADDR                                           (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000074)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_OFFS                                           (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000074)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_RMSK                                                  0xf
#define HWIO_LPASS_QDSP6SS_BHS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_CTL_ADDR, HWIO_LPASS_QDSP6SS_BHS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_BHS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_BHS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_BHS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_BHS_CTL_DRIVE_SEL_BMSK                                        0xf
#define HWIO_LPASS_QDSP6SS_BHS_CTL_DRIVE_SEL_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000078)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000078)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000007c)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000007c)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK                                              0x3
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000080)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000080)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_RMSK                                              0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_BMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000084)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000084)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_BMSK                                     0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000088)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000088)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK                                             0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000008c)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000008c)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK                                             0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000090)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000090)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_RMSK                                            0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_BMSK                              0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_BMSK                               0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000094)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000094)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_RMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_BMSK                            0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_SHFT                            0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_BMSK                             0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_SHFT                             0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000098)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000098)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK                                         0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_BMSK                           0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_SHFT                           0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_BMSK                           0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_SHFT                           0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x000000a0)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x000000a0)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK                                          0x3
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x000000f0)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x000000f0)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK                                         0x17800ff
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CP0_BHS_ON_BMSK                              0x1000000
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CP0_BHS_ON_SHFT                                   0x18
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_QMC_MEM_BMSK                            0x400000
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_QMC_MEM_SHFT                                0x16
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_WL_BMSK                                 0x200000
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_WL_SHFT                                     0x15
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_BMSK                                 0x100000
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_SHFT                                     0x14
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SLP_RET_N_BMSK                                 0x80000
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SLP_RET_N_SHFT                                    0x13
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_L1S_SLP_NRET_N_BMSK                               0xff
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_L1S_SLP_NRET_N_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x000000f4)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x000000f4)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK                                            0x3
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_CP0_ENF_ACK_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_CP0_ENF_ACK_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_CP0_ENR_ACK_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_CP0_ENR_ACK_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_CP_RESET_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x000000f8)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x000000f8)
#define HWIO_LPASS_QDSP6SS_CP_RESET_RMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, HWIO_LPASS_QDSP6SS_CP_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_RESET_IN)
#define HWIO_LPASS_QDSP6SS_CP_RESET_CP0_ARES_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_CP0_ARES_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x000000fc)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x000000fc)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CP0_CLK_ENA_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CP0_CLK_ENA_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK                                         0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_TCM_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                               0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                     0x12

#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK                                    0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                         0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                                0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK                                    0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                         0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                                0xe

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000114)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000114)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK                                     0x800000ff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SEL_BMSK                   0x80000000
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SEL_SHFT                         0x1f
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                             0xff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_LPASS_QDSP6SS_DCC_CTRL_IN)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_BMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                  (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OFFS                                  (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR                                          (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OFFS                                          (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_MODE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                             0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                   0x1f
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                          0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                0x1e
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                            0x20000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                  0x1d
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_BMSK                        0x1f000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_SHFT                              0x18
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                 0x800000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                     0x17
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                                 0x400000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                     0x16
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                         0x200000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                             0x15
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                           0x100000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                               0x14
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                              0xfc000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                  0xe
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                               0x3f00
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_BMSK                                0xf0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_BMSK                                     0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_SHFT                                     0x3
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK                                             0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                       0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR                                   (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OFFS                                   (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK                                         0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                         0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                    0xf0000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                          0x1c
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                      0x8000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                           0x1b
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                     0x6000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                          0x19
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_BMSK                              0x1000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_SHFT                                   0x18
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                      0xc00000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                          0x16
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_BMSK                                0x300000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT                                    0x14
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                       0xf8000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                           0xf
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                            0x7000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                               0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_BMSK                            0xf00
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_BMSK                                 0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_SHFT                                  0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                            0x60
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                             0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                             0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                              0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                               0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_BMSK                      0xffff0000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_SHFT                            0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_BMSK                      0xf000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_SHFT                         0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                  0x800
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                    0xb
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                         0x700
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                           0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_BMSK                                      0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_SHFT                                       0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_SHFT                               0x6
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_BMSK                               0x38
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_SHFT                                0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK            0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                  0x1f
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                 0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                       0x1e
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK            0x3c000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                  0x1a
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                0x3800000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                     0x17
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                    0x700000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                        0x14
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                    0xff000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                        0xc
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                    0xf00
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                      0x8
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_BMSK                         0xc0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_SHFT                          0x6
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                0x30
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_BMSK                                       0xf
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                        0xe0000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                              0x1d
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_BMSK                                  0x10000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_SHFT                                        0x1c
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_BMSK                          0xc000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_SHFT                               0x1a
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                 0x2000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                      0x19
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                              0x1e00000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                   0x15
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                      0x100000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                          0x14
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                              0xfe000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                  0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                          0x1000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                             0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                              0x800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_BMSK                                 0x700
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_SHFT                                   0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_BMSK                                   0x80
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_SHFT                                    0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                0x40
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                 0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                 0x30
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                  0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                  0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_BMSK                  0xffffc000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_SHFT                         0xe
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                  0x2000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                     0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                         0x1800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                            0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                             0x600
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                               0x9
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_BMSK                                  0x100
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                0xe0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                0x10
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                              0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                          0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                            0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                   0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000240)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000240)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK                                       0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_BMSK                        0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_BMSK                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR                             (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000244)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OFFS                             (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000244)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK                                   0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_BMSK                       0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000248)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000248)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_RMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR                             (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000023c)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_OFFS                             (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000023c)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK                                    0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_BMSK                 0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_SHFT                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_BMSK                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_SHFT                 0x0

#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_WAKEUP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_EXT_WAKEUP_CMD_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_EXT_PD_ADDR                                            (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_OFFS                                            (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_QDSP6SS_EXT_PD_RMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_EXT_PD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_BMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_EXT_PD_CMD_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK                                      0xff03ffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                            0xff000000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                  0x18
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                              0x20000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                                 0x11
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                  0x10000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                      0xffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR                                        (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OFFS                                        (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK                                            0x7f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                               0x6
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                             0x20
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                              0x5
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                                0x1f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR                                     (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_OFFS                                     (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002014)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_BMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_PWRDBG_STATUS_STATUS_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR                                      (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OFFS                                      (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK                                        0xffffff
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                            0xffffe0
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                    0x10
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                     0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR                                         (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OFFS                                         (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK                                            0x3ffff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, HWIO_LPASS_QDSP6SS_LDO_ATEST_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_ATEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_ATEST_IN)
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_BMSK                                  0x20000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_EN_SHFT                                     0x11
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_BMSK                                  0x10000
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_EN_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_BMSK                                  0xff00
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST1_SEL_SHFT                                     0x8
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_BMSK                                    0xff
#define HWIO_LPASS_QDSP6SS_LDO_ATEST_ATEST0_SEL_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002020)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002020)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_RMSK                                0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR, HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_VALUE_BMSK                          0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_LOW_VALUE_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR                               (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002024)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_OFFS                               (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002024)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_RMSK                               0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR, HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_VALUE_BMSK                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_DAC_STATUS_HIGH_VALUE_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00002028)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00002028)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK                                              0x7
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_PUBLIC
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_PUBLIC_REG_BASE (LPASS_BASE      + 0x00300000)
#define LPASS_QDSP6SS_PUBLIC_REG_BASE_OFFS 0x00300000

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                       (CORE_TOP_CSR_BASE      + 0x000a0000)
#define TCSR_TCSR_REGS_REG_BASE_OFFS                                                                                                                  0x000a0000

#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR                                                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00000800)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OFFS                                                                                                           (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00000800)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK                                                                                                                  0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_BMSK                                                                                             0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_SHFT                                                                                             0x0

#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00000804)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00000804)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK                                                                                                                   0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_BMSK                                                                                               0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_SHFT                                                                                               0x0

#define HWIO_TCSR_XPU_NSEN_STATUS_ADDR                                                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x00000820)
#define HWIO_TCSR_XPU_NSEN_STATUS_OFFS                                                                                                                (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00000820)
#define HWIO_TCSR_XPU_NSEN_STATUS_RMSK                                                                                                                       0x3
#define HWIO_TCSR_XPU_NSEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_NSEN_STATUS_ADDR, HWIO_TCSR_XPU_NSEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_NSEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_NSEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_NSEN_STATUS_REGS_XPU2_NSEN_STATUS_BMSK                                                                                                 0x2
#define HWIO_TCSR_XPU_NSEN_STATUS_REGS_XPU2_NSEN_STATUS_SHFT                                                                                                 0x1
#define HWIO_TCSR_XPU_NSEN_STATUS_MUTEX_XPU2_NSEN_STATUS_BMSK                                                                                                0x1
#define HWIO_TCSR_XPU_NSEN_STATUS_MUTEX_XPU2_NSEN_STATUS_SHFT                                                                                                0x0

#define HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00000824)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00000824)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_RMSK                                                                                                                     0x3
#define HWIO_TCSR_XPU_VMIDEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR, HWIO_TCSR_XPU_VMIDEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_REGS_XPU2_VMIDEN_STATUS_BMSK                                                                                             0x2
#define HWIO_TCSR_XPU_VMIDEN_STATUS_REGS_XPU2_VMIDEN_STATUS_SHFT                                                                                             0x1
#define HWIO_TCSR_XPU_VMIDEN_STATUS_MUTEX_XPU2_VMIDEN_STATUS_BMSK                                                                                            0x1
#define HWIO_TCSR_XPU_VMIDEN_STATUS_MUTEX_XPU2_VMIDEN_STATUS_SHFT                                                                                            0x0

#define HWIO_TCSR_XPU_MSAEN_STATUS_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00000828)
#define HWIO_TCSR_XPU_MSAEN_STATUS_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00000828)
#define HWIO_TCSR_XPU_MSAEN_STATUS_RMSK                                                                                                                      0x3
#define HWIO_TCSR_XPU_MSAEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_MSAEN_STATUS_ADDR, HWIO_TCSR_XPU_MSAEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_MSAEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_MSAEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_MSAEN_STATUS_REGS_XPU2_MSAEN_STATUS_BMSK                                                                                               0x2
#define HWIO_TCSR_XPU_MSAEN_STATUS_REGS_XPU2_MSAEN_STATUS_SHFT                                                                                               0x1
#define HWIO_TCSR_XPU_MSAEN_STATUS_MUTEX_XPU2_MSAEN_STATUS_BMSK                                                                                              0x1
#define HWIO_TCSR_XPU_MSAEN_STATUS_MUTEX_XPU2_MSAEN_STATUS_SHFT                                                                                              0x0

#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00002000)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002000)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_RMSK                                                                                                          0xfffffffe
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ADDR, HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_QDSS_MPU_APU_XPU2_NON_SEC_INTR_BMSK                                                                           0x80000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_QDSS_MPU_APU_XPU2_NON_SEC_INTR_SHFT                                                                                 0x1f
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BOOT_ROM_XPU2_NON_SEC_INTR_BMSK                                                                               0x40000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BOOT_ROM_XPU2_NON_SEC_INTR_SHFT                                                                                     0x1e
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_NOC_CFG_XPU2_NON_SEC_INTR_BMSK                                                                                0x20000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_NOC_CFG_XPU2_NON_SEC_INTR_SHFT                                                                                      0x1d
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_LPASS_IRQ_OUT_SECURITY_1_BMSK                                                                                 0x10000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_LPASS_IRQ_OUT_SECURITY_1_SHFT                                                                                       0x1c
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_TLMM_XPU_XPU2_NON_SEC_INTR_BMSK                                                                                0x8000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_TLMM_XPU_XPU2_NON_SEC_INTR_SHFT                                                                                     0x1b
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SPDM_XPU_XPU2_NON_SEC_INTR_BMSK                                                                                0x4000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SPDM_XPU_XPU2_NON_SEC_INTR_SHFT                                                                                     0x1a
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PMIC_ARB_XPU2_NON_SEC_INTR_BMSK                                                                                0x2000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PMIC_ARB_XPU2_NON_SEC_INTR_SHFT                                                                                     0x19
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_UFS_ICE_XPU2_NON_SEC_INTR_BMSK                                                                                 0x1000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_UFS_ICE_XPU2_NON_SEC_INTR_SHFT                                                                                      0x18
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_VENUS_WRAPPER_XPU2_NON_SEC_INTERRUPT_BMSK                                                                       0x800000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_VENUS_WRAPPER_XPU2_NON_SEC_INTERRUPT_SHFT                                                                           0x17
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CH1_XPU2_NON_SEC_INTERRUPT_BMSK                                                                            0x400000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CH1_XPU2_NON_SEC_INTERRUPT_SHFT                                                                                0x16
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CH0_XPU2_NON_SEC_INTERRUPT_BMSK                                                                            0x200000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CH0_XPU2_NON_SEC_INTERRUPT_SHFT                                                                                0x15
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CFG_XPU2_NON_SEC_INTERRUPT_BMSK                                                                            0x100000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_BIMC_CFG_XPU2_NON_SEC_INTERRUPT_SHFT                                                                                0x14
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_GCC_XPU_NON_SEC_INTR_BMSK                                                                                        0x80000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_GCC_XPU_NON_SEC_INTR_SHFT                                                                                           0x13
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_UFS_XPU_NON_SEC_INTR_BMSK                                                                                        0x40000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_UFS_XPU_NON_SEC_INTR_SHFT                                                                                           0x12
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A2NOC_MPU_CFG_XPU2_NON_SEC_INTR_BMSK                                                                             0x20000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A2NOC_MPU_CFG_XPU2_NON_SEC_INTR_SHFT                                                                                0x11
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A1NOC_MPU_CFG_XPU2_NON_SEC_INTR_BMSK                                                                             0x10000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A1NOC_MPU_CFG_XPU2_NON_SEC_INTR_SHFT                                                                                0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A0NOC_MPU_CFG_XPU2_NON_SEC_INTR_BMSK                                                                              0x8000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_A0NOC_MPU_CFG_XPU2_NON_SEC_INTR_SHFT                                                                                 0xf
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PIMEM_MPU_XPU2_NON_SEC_IRQ_BMSK                                                                                   0x4000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PIMEM_MPU_XPU2_NON_SEC_IRQ_SHFT                                                                                      0xe
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PIMEM_APU_XPU2_NON_SEC_IRQ_BMSK                                                                                   0x2000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_PIMEM_APU_XPU2_NON_SEC_IRQ_SHFT                                                                                      0xd
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_1_BMSK                                                                                           0x1000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_1_SHFT                                                                                              0xc
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_9_BMSK                                                                                            0x800
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_9_SHFT                                                                                              0xb
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_4_BMSK                                                                                            0x400
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SSC_XPU_IRQ_APPS_4_SHFT                                                                                              0xa
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SEC_CTRL_XPU2_NON_SEC_INTR_BMSK                                                                                    0x200
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_SEC_CTRL_XPU2_NON_SEC_INTR_SHFT                                                                                      0x9
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_DCC_XPU2_NON_SEC_INTR_BMSK                                                                                         0x100
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_DCC_XPU2_NON_SEC_INTR_SHFT                                                                                           0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_OCIMEM_RPU_XPU2_NON_SEC_INTR_BMSK                                                                                   0x80
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_OCIMEM_RPU_XPU2_NON_SEC_INTR_SHFT                                                                                    0x7
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_CRYPTO0_BAM_XPU2_NON_SEC_INTR_BMSK                                                                                  0x40
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_CRYPTO0_BAM_XPU2_NON_SEC_INTR_SHFT                                                                                   0x6
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_O_TCSR_MUTEX_XPU2_NON_SEC_INTR_BMSK                                                                                 0x20
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_O_TCSR_MUTEX_XPU2_NON_SEC_INTR_SHFT                                                                                  0x5
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_COPSS_XPU2_NON_SEC_IRQ_BMSK                                                                                         0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_COPSS_XPU2_NON_SEC_IRQ_SHFT                                                                                          0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_O_TCSR_REGS_XPU2_NON_SEC_INTR_BMSK                                                                                   0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_O_TCSR_REGS_XPU2_NON_SEC_INTR_SHFT                                                                                   0x3
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_MMSS_NOC_XPU2_NON_SEC_INTR_BMSK                                                                                      0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_MMSS_NOC_XPU2_NON_SEC_INTR_SHFT                                                                                      0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_DSA_XPU2_NON_SEC_INTR_BMSK                                                                                           0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_DSA_XPU2_NON_SEC_INTR_SHFT                                                                                           0x1

#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00002004)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002004)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RMSK                                                                                                               0x3ff
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ADDR, HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RPM_MPU_XPU2_NON_SEC_INTR_BMSK                                                                                     0x200
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RPM_MPU_XPU2_NON_SEC_INTR_SHFT                                                                                       0x9
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURIT_9_BMSK                                                                                       0x100
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURIT_9_SHFT                                                                                         0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_MDSS_XPU2_NON_SEC_INTR_BMSK                                                                                         0x80
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_MDSS_XPU2_NON_SEC_INTR_SHFT                                                                                          0x7
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_QDSS_BAM_XPU2_NON_SEC_INTR_BMSK                                                                                     0x40
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_QDSS_BAM_XPU2_NON_SEC_INTR_SHFT                                                                                      0x6
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_MPM_XPU2_NON_SEC_INTR_BMSK                                                                                          0x20
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_MPM_XPU2_NON_SEC_INTR_SHFT                                                                                           0x5
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_SDCC2_XPU2_NON_SEC_ERROR_INTR_BMSK                                                                                  0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_SDCC2_XPU2_NON_SEC_ERROR_INTR_SHFT                                                                                   0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RBCPR_APU_XPU2_NON_SEC_INTR_BMSK                                                                                     0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_RBCPR_APU_XPU2_NON_SEC_INTR_SHFT                                                                                     0x3
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_BLSP2_XPU2_NON_SEC_INTR_BMSK                                                                                         0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_BLSP2_XPU2_NON_SEC_INTR_SHFT                                                                                         0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_BLSP1_XPU2_NON_SEC_INTR_BMSK                                                                                         0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_BLSP1_XPU2_NON_SEC_INTR_SHFT                                                                                         0x1
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_OCIMEM_MPU_XPU2_NON_SEC_INTR_BMSK                                                                                    0x1
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_OCIMEM_MPU_XPU2_NON_SEC_INTR_SHFT                                                                                    0x0

#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_ADDR                                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00002040)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_OFFS                                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002040)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_RMSK                                                                                                   0xfffffffe
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_QDSS_MPU_APU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                             0x80000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_QDSS_MPU_APU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                   0x1f
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BOOT_ROM_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                 0x40000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BOOT_ROM_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x1e
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_NOC_CFG_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                  0x20000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_NOC_CFG_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                        0x1d
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_1_INTR_ENABLE_BMSK                                                              0x10000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_1_INTR_ENABLE_SHFT                                                                    0x1c
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_TLMM_XPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                  0x8000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_TLMM_XPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x1b
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SPDM_XPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                  0x4000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SPDM_XPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x1a
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PMIC_ARB_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                  0x2000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PMIC_ARB_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x19
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_UFS_ICE_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                   0x1000000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_UFS_ICE_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                        0x18
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_VENUS_WRAPPER_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                              0x800000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_VENUS_WRAPPER_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                  0x17
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CH1_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                   0x400000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CH1_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x16
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CH0_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                   0x200000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CH0_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x15
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CFG_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                   0x100000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_BIMC_CFG_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x14
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_GCC_XPU_NON_SEC_INTR_ENABLE_BMSK                                                                          0x80000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_GCC_XPU_NON_SEC_INTR_ENABLE_SHFT                                                                             0x13
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_UFS_XPU_NON_SEC_INTR_ENABLE_BMSK                                                                          0x40000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_UFS_XPU_NON_SEC_INTR_ENABLE_SHFT                                                                             0x12
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                               0x20000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                  0x11
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                               0x10000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                  0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                0x8000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                   0xf
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PIMEM_MPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                    0x4000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PIMEM_MPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0xe
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PIMEM_APU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                    0x2000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_PIMEM_APU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0xd
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_1_INTR_ENABLE_BMSK                                                                        0x1000
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_1_INTR_ENABLE_SHFT                                                                           0xc
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_9_INTR_ENABLE_BMSK                                                                         0x800
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_9_INTR_ENABLE_SHFT                                                                           0xb
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_4_INTR_ENABLE_BMSK                                                                         0x400
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_4_INTR_ENABLE_SHFT                                                                           0xa
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SEC_CTRL_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                      0x200
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_SEC_CTRL_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                        0x9
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_DCC_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                           0x100
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_DCC_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                             0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                     0x80
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                      0x7
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                    0x40
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                     0x6
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                   0x20
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                    0x5
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_COPSS_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                          0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_COPSS_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                           0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                     0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                     0x3
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_MMSS_NOC_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                        0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_MMSS_NOC_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                        0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_DSA_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                             0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR0_ENABLE_DSA_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                             0x1

#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_ADDR                                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00002044)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_OFFS                                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002044)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RMSK                                                                                                        0x3ff
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RPM_MPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                       0x200
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RPM_MPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                         0x9
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_9_INTR_ENABLE_BMSK                                                                    0x100
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_9_INTR_ENABLE_SHFT                                                                      0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_MDSS_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                           0x80
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_MDSS_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                            0x7
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_QDSS_BAM_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                       0x40
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_QDSS_BAM_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                        0x6
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_MPM_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                            0x20
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_MPM_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                             0x5
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_SDCC2_XPU2_NON_SEC_ERROR_INTR_ENABLE_BMSK                                                                    0x10
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_SDCC2_XPU2_NON_SEC_ERROR_INTR_ENABLE_SHFT                                                                     0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RBCPR_APU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                       0x8
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_RBCPR_APU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                       0x3
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_BLSP2_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                           0x4
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_BLSP2_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                           0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_BLSP1_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                           0x2
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_BLSP1_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                           0x1
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_OCIMEM_MPU_XPU2_NON_SEC_INTR_ENABLE_BMSK                                                                      0x1
#define HWIO_TCSR_SS_XPU2_NON_SEC_INTR1_ENABLE_OCIMEM_MPU_XPU2_NON_SEC_INTR_ENABLE_SHFT                                                                      0x0

#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00004000)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004000)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_RMSK                                                                                                              0xfffffffe
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR0_ADDR, HWIO_TCSR_SS_XPU2_SEC_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_QDSS_MPU_APU_XPU2_SEC_INTR_BMSK                                                                                   0x80000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_QDSS_MPU_APU_XPU2_SEC_INTR_SHFT                                                                                         0x1f
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BOOT_ROM_XPU2_SEC_INTR_BMSK                                                                                       0x40000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BOOT_ROM_XPU2_SEC_INTR_SHFT                                                                                             0x1e
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_NOC_CFG_XPU2_SEC_INTR_BMSK                                                                                        0x20000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_NOC_CFG_XPU2_SEC_INTR_SHFT                                                                                              0x1d
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_LPASS_IRQ_OUT_SECURITY_0_BMSK                                                                                     0x10000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_LPASS_IRQ_OUT_SECURITY_0_SHFT                                                                                           0x1c
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_TLMM_XPU_XPU2_SEC_INTR_BMSK                                                                                        0x8000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_TLMM_XPU_XPU2_SEC_INTR_SHFT                                                                                             0x1b
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SPDM_XPU_XPU2_SEC_INTR_BMSK                                                                                        0x4000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SPDM_XPU_XPU2_SEC_INTR_SHFT                                                                                             0x1a
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PMIC_ARB_XPU2_SEC_INTR_BMSK                                                                                        0x2000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PMIC_ARB_XPU2_SEC_INTR_SHFT                                                                                             0x19
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_UFS_ICE_XPU2_SEC_INTR_BMSK                                                                                         0x1000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_UFS_ICE_XPU2_SEC_INTR_SHFT                                                                                              0x18
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_VENUS_WRAPPER_XPU2_SEC_INTERRUPT_BMSK                                                                               0x800000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_VENUS_WRAPPER_XPU2_SEC_INTERRUPT_SHFT                                                                                   0x17
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CH1_XPU2_SEC_INTERRUPT_BMSK                                                                                    0x400000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CH1_XPU2_SEC_INTERRUPT_SHFT                                                                                        0x16
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CH0_XPU2_SEC_INTERRUPT_BMSK                                                                                    0x200000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CH0_XPU2_SEC_INTERRUPT_SHFT                                                                                        0x15
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CFG_XPU2_SEC_INTERRUPT_BMSK                                                                                    0x100000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_BIMC_CFG_XPU2_SEC_INTERRUPT_SHFT                                                                                        0x14
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_GCC_XPU_SEC_INTR_BMSK                                                                                                0x80000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_GCC_XPU_SEC_INTR_SHFT                                                                                                   0x13
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_UFS_XPU_SEC_INTR_BMSK                                                                                                0x40000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_UFS_XPU_SEC_INTR_SHFT                                                                                                   0x12
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A2NOC_MPU_CFG_XPU2_SEC_INTR_BMSK                                                                                     0x20000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A2NOC_MPU_CFG_XPU2_SEC_INTR_SHFT                                                                                        0x11
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A1NOC_MPU_CFG_XPU2_SEC_INTR_BMSK                                                                                     0x10000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A1NOC_MPU_CFG_XPU2_SEC_INTR_SHFT                                                                                        0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A0NOC_MPU_CFG_XPU2_SEC_INTR_BMSK                                                                                      0x8000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_A0NOC_MPU_CFG_XPU2_SEC_INTR_SHFT                                                                                         0xf
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PIMEM_MPU_XPU2_SEC_IRQ_BMSK                                                                                           0x4000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PIMEM_MPU_XPU2_SEC_IRQ_SHFT                                                                                              0xe
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PIMEM_APU_XPU2_SEC_IRQ_BMSK                                                                                           0x2000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_PIMEM_APU_XPU2_SEC_IRQ_SHFT                                                                                              0xd
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_2_BMSK                                                                                               0x1000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_2_SHFT                                                                                                  0xc
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_8_BMSK                                                                                                0x800
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_8_SHFT                                                                                                  0xb
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_5_BMSK                                                                                                0x400
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SSC_XPU_IRQ_APPS_5_SHFT                                                                                                  0xa
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SEC_CTRL_XPU2_SEC_INTR_BMSK                                                                                            0x200
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_SEC_CTRL_XPU2_SEC_INTR_SHFT                                                                                              0x9
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_DCC_XPU2_SEC_INTR_BMSK                                                                                                 0x100
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_DCC_XPU2_SEC_INTR_SHFT                                                                                                   0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_OCIMEM_RPU_XPU2_SEC_INTR_BMSK                                                                                           0x80
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_OCIMEM_RPU_XPU2_SEC_INTR_SHFT                                                                                            0x7
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_CRYPTO0_BAM_XPU2_SEC_INTR_BMSK                                                                                          0x40
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_CRYPTO0_BAM_XPU2_SEC_INTR_SHFT                                                                                           0x6
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_O_TCSR_MUTEX_XPU2_SEC_INTR_BMSK                                                                                         0x20
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_O_TCSR_MUTEX_XPU2_SEC_INTR_SHFT                                                                                          0x5
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_COPSS_XPU2_SEC_IRQ_BMSK                                                                                                 0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_COPSS_XPU2_SEC_IRQ_SHFT                                                                                                  0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_O_TCSR_REGS_XPU2_SEC_INTR_BMSK                                                                                           0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_O_TCSR_REGS_XPU2_SEC_INTR_SHFT                                                                                           0x3
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_MMSS_NOC_XPU2_SEC_INTR_BMSK                                                                                              0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_MMSS_NOC_XPU2_SEC_INTR_SHFT                                                                                              0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_DSA_XPU2_SEC_INTR_BMSK                                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_DSA_XPU2_SEC_INTR_SHFT                                                                                                   0x1

#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00004004)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004004)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_RMSK                                                                                                                   0x3ff
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR1_ADDR, HWIO_TCSR_SS_XPU2_SEC_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_RPM_MPU_XPU2_SEC_INTR_BMSK                                                                                             0x200
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_RPM_MPU_XPU2_SEC_INTR_SHFT                                                                                               0x9
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_LPASS_IRQ_OUT_SECURIT_8_BMSK                                                                                           0x100
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_LPASS_IRQ_OUT_SECURIT_8_SHFT                                                                                             0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_MDSS_XPU2_SEC_INTR_BMSK                                                                                                 0x80
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_MDSS_XPU2_SEC_INTR_SHFT                                                                                                  0x7
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_QDSS_BAM_XPU2_SEC_INTR_BMSK                                                                                             0x40
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_QDSS_BAM_XPU2_SEC_INTR_SHFT                                                                                              0x6
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_MPM_XPU2_SEC_INTR_BMSK                                                                                                  0x20
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_MPM_XPU2_SEC_INTR_SHFT                                                                                                   0x5
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_SDCC2_XPU2_SEC_ERROR_INTR_BMSK                                                                                          0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_SDCC2_XPU2_SEC_ERROR_INTR_SHFT                                                                                           0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_RBCPR_APU_XPU2_SEC_INTR_BMSK                                                                                             0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_RBCPR_APU_XPU2_SEC_INTR_SHFT                                                                                             0x3
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_BLSP2_XPU2_SEC_INTR_BMSK                                                                                                 0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_BLSP2_XPU2_SEC_INTR_SHFT                                                                                                 0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_BLSP1_XPU2_SEC_INTR_BMSK                                                                                                 0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_BLSP1_XPU2_SEC_INTR_SHFT                                                                                                 0x1
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_OCIMEM_MPU_XPU2_SEC_INTR_BMSK                                                                                            0x1
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_OCIMEM_MPU_XPU2_SEC_INTR_SHFT                                                                                            0x0

#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_ADDR                                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00004040)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_OFFS                                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004040)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_RMSK                                                                                                       0xfffffffe
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_QDSS_MPU_APU_XPU2_SEC_INTR_ENABLE_BMSK                                                                     0x80000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_QDSS_MPU_APU_XPU2_SEC_INTR_ENABLE_SHFT                                                                           0x1f
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BOOT_ROM_XPU2_SEC_INTR_ENABLE_BMSK                                                                         0x40000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BOOT_ROM_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x1e
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_NOC_CFG_XPU2_SEC_INTR_ENABLE_BMSK                                                                          0x20000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_NOC_CFG_XPU2_SEC_INTR_ENABLE_SHFT                                                                                0x1d
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_0_INTR_ENABLE_BMSK                                                                  0x10000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_0_INTR_ENABLE_SHFT                                                                        0x1c
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_TLMM_XPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                          0x8000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_TLMM_XPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x1b
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SPDM_XPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                          0x4000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SPDM_XPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x1a
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PMIC_ARB_XPU2_SEC_INTR_ENABLE_BMSK                                                                          0x2000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PMIC_ARB_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x19
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_UFS_ICE_XPU2_SEC_INTR_ENABLE_BMSK                                                                           0x1000000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_UFS_ICE_XPU2_SEC_INTR_ENABLE_SHFT                                                                                0x18
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_VENUS_WRAPPER_XPU2_SEC_INTR_ENABLE_BMSK                                                                      0x800000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_VENUS_WRAPPER_XPU2_SEC_INTR_ENABLE_SHFT                                                                          0x17
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CH1_XPU2_SEC_INTR_ENABLE_BMSK                                                                           0x400000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CH1_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x16
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CH0_XPU2_SEC_INTR_ENABLE_BMSK                                                                           0x200000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CH0_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x15
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CFG_XPU2_SEC_INTR_ENABLE_BMSK                                                                           0x100000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_BIMC_CFG_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x14
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_GCC_XPU_SEC_INTR_ENABLE_BMSK                                                                                  0x80000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_GCC_XPU_SEC_INTR_ENABLE_SHFT                                                                                     0x13
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_UFS_XPU_SEC_INTR_ENABLE_BMSK                                                                                  0x40000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_UFS_XPU_SEC_INTR_ENABLE_SHFT                                                                                     0x12
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_BMSK                                                                       0x20000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_SHFT                                                                          0x11
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_BMSK                                                                       0x10000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_SHFT                                                                          0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_BMSK                                                                        0x8000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_SEC_INTR_ENABLE_SHFT                                                                           0xf
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PIMEM_MPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                            0x4000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PIMEM_MPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0xe
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PIMEM_APU_XPU2_SEC_INTR_ENABLE_BMSK                                                                            0x2000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_PIMEM_APU_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0xd
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_2_INTR_ENABLE_BMSK                                                                            0x1000
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_2_INTR_ENABLE_SHFT                                                                               0xc
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_8_INTR_ENABLE_BMSK                                                                             0x800
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_8_INTR_ENABLE_SHFT                                                                               0xb
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_5_INTR_ENABLE_BMSK                                                                             0x400
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SSC_XPU_IRQ_APPS_5_INTR_ENABLE_SHFT                                                                               0xa
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SEC_CTRL_XPU2_SEC_INTR_ENABLE_BMSK                                                                              0x200
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_SEC_CTRL_XPU2_SEC_INTR_ENABLE_SHFT                                                                                0x9
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_DCC_XPU2_SEC_INTR_ENABLE_BMSK                                                                                   0x100
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_DCC_XPU2_SEC_INTR_ENABLE_SHFT                                                                                     0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                             0x80
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                              0x7
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU2_SEC_INTR_ENABLE_BMSK                                                                            0x40
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU2_SEC_INTR_ENABLE_SHFT                                                                             0x6
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU2_SEC_INTR_ENABLE_BMSK                                                                           0x20
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU2_SEC_INTR_ENABLE_SHFT                                                                            0x5
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_COPSS_XPU2_SEC_INTR_ENABLE_BMSK                                                                                  0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_COPSS_XPU2_SEC_INTR_ENABLE_SHFT                                                                                   0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU2_SEC_INTR_ENABLE_BMSK                                                                             0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU2_SEC_INTR_ENABLE_SHFT                                                                             0x3
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_MMSS_NOC_XPU2_SEC_INTR_ENABLE_BMSK                                                                                0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_MMSS_NOC_XPU2_SEC_INTR_ENABLE_SHFT                                                                                0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_DSA_XPU2_SEC_INTR_ENABLE_BMSK                                                                                     0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR0_ENABLE_DSA_XPU2_SEC_INTR_ENABLE_SHFT                                                                                     0x1

#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_ADDR                                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00004044)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_OFFS                                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004044)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RMSK                                                                                                            0x3ff
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RPM_MPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                               0x200
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RPM_MPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                                 0x9
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_8_INTR_ENABLE_BMSK                                                                        0x100
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_8_INTR_ENABLE_SHFT                                                                          0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_MDSS_XPU2_SEC_INTR_ENABLE_BMSK                                                                                   0x80
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_MDSS_XPU2_SEC_INTR_ENABLE_SHFT                                                                                    0x7
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_QDSS_BAM_XPU2_SEC_INTR_ENABLE_BMSK                                                                               0x40
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_QDSS_BAM_XPU2_SEC_INTR_ENABLE_SHFT                                                                                0x6
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_MPM_XPU2_SEC_INTR_ENABLE_BMSK                                                                                    0x20
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_MPM_XPU2_SEC_INTR_ENABLE_SHFT                                                                                     0x5
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_SDCC2_XPU2_SEC_ERROR_INTR_ENABLE_BMSK                                                                            0x10
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_SDCC2_XPU2_SEC_ERROR_INTR_ENABLE_SHFT                                                                             0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RBCPR_APU_XPU2_SEC_INTR_ENABLE_BMSK                                                                               0x8
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_RBCPR_APU_XPU2_SEC_INTR_ENABLE_SHFT                                                                               0x3
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_BLSP2_XPU2_SEC_INTR_ENABLE_BMSK                                                                                   0x4
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_BLSP2_XPU2_SEC_INTR_ENABLE_SHFT                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_BLSP1_XPU2_SEC_INTR_ENABLE_BMSK                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_BLSP1_XPU2_SEC_INTR_ENABLE_SHFT                                                                                   0x1
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_OCIMEM_MPU_XPU2_SEC_INTR_ENABLE_BMSK                                                                              0x1
#define HWIO_TCSR_SS_XPU2_SEC_INTR1_ENABLE_OCIMEM_MPU_XPU2_SEC_INTR_ENABLE_SHFT                                                                              0x0

#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00002010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_OFFS                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RMSK                                                                                                      0x3dff
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_PIMEM_VMIDMT_NSGIRPT_BMSK                                                                                 0x2000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_PIMEM_VMIDMT_NSGIRPT_SHFT                                                                                    0xd
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SPDM_VMID_NSGIRPT_BMSK                                                                                    0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SPDM_VMID_NSGIRPT_SHFT                                                                                       0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGIRPT_BMSK                                                                               0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGIRPT_SHFT                                                                                 0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGIRPT_BMSK                                                                             0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGIRPT_SHFT                                                                               0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP2_VMIDMT_NSGIRPT_BMSK                                                                                  0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP2_VMIDMT_NSGIRPT_SHFT                                                                                    0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP1_VMIDMT_NSGIRPT_BMSK                                                                                   0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP1_VMIDMT_NSGIRPT_SHFT                                                                                    0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_BMSK                                                                                  0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_SHFT                                                                                   0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGIRPT_BMSK                                                                                0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGIRPT_SHFT                                                                                 0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_UFS_VMIDMT_NSGIRPT_BMSK                                                                                     0x10
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_UFS_VMIDMT_NSGIRPT_SHFT                                                                                      0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_VENUS1_VBIF_VMIDMT_NSGIRPT_BMSK                                                                              0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_VENUS1_VBIF_VMIDMT_NSGIRPT_SHFT                                                                              0x3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_VENUS0_VBIF_VMIDMT_NSGIRPT_BMSK                                                                              0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_VENUS0_VBIF_VMIDMT_NSGIRPT_SHFT                                                                              0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                                                  0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                                                  0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGIRPT_BMSK                                                                                  0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGIRPT_SHFT                                                                                  0x0

#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00002014)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_OFFS                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002014)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_RMSK                                                                                                         0x1ffe
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_5_IRQ_OUT_SECURITY_BMSK                                                                                0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_5_IRQ_OUT_SECURITY_SHFT                                                                                   0xc
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_13_IRQ_OUT_SECURITY_BMSK                                                                                0x800
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_13_IRQ_OUT_SECURITY_SHFT                                                                                  0xb
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGIRPT_BMSK                                                                               0x400
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGIRPT_SHFT                                                                                 0xa
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGIRPT_BMSK                                                                               0x200
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGIRPT_SHFT                                                                                 0x9
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR0_NOC_SMMU_MMU_NSGIRPT_BMSK                                                                               0x100
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR0_NOC_SMMU_MMU_NSGIRPT_SHFT                                                                                 0x8
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MDSS_DMA_MMU_NSGIRPT_BMSK                                                                                      0x80
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MDSS_DMA_MMU_NSGIRPT_SHFT                                                                                       0x7
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_OGPU_MMU_NSGIRPT_BMSK                                                                                          0x40
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_OGPU_MMU_NSGIRPT_SHFT                                                                                           0x6
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MDSS_MMU_NSGIRPT_BMSK                                                                                          0x20
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MDSS_MMU_NSGIRPT_SHFT                                                                                           0x5
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_JPEG_MMU_NSGIRPT_BMSK                                                                                    0x10
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_JPEG_MMU_NSGIRPT_SHFT                                                                                     0x4
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_VFE_MMU_NSGIRPT_BMSK                                                                                      0x8
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_VFE_MMU_NSGIRPT_SHFT                                                                                      0x3
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_CPP_MMU_NSGIRPT_BMSK                                                                                      0x4
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_CAMSS_CPP_MMU_NSGIRPT_SHFT                                                                                      0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_VENUS0_MMU_NSGIRPT_BMSK                                                                                         0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_VENUS0_MMU_NSGIRPT_SHFT                                                                                         0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR                                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00002050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_OFFS                                                                                           (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RMSK                                                                                               0x3ff7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_PIMEM_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                   0x2000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_PIMEM_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                      0xd
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGIRPT_ENABLE_BMSK                                                                      0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGIRPT_ENABLE_SHFT                                                                         0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                 0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                   0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGIRPT_ENABLE_BMSK                                                               0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                 0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                    0x200
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                      0x9
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                    0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                      0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SSC_VMIDMT_1_APPS_IRQ_ENABLE_BMSK                                                                    0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SSC_VMIDMT_1_APPS_IRQ_ENABLE_SHFT                                                                     0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                  0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                   0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_UFS_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                       0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_UFS_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                        0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_NSGIRPT_ENABLE_BMSK                                                               0x10
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGIRPT_ENABLE_BMSK                                                                 0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGIRPT_ENABLE_SHFT                                                                 0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGIRPT_ENABLE_BMSK                                                                    0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGIRPT_ENABLE_SHFT                                                                    0x0

#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00002054)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OFFS                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00002054)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_RMSK                                                                                                  0x1ffe
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_5_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                             0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_5_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                0xc
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_13_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                             0x800
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_13_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                               0xb
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGIRPT_ENABLE_BMSK                                                                 0x400
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGIRPT_ENABLE_SHFT                                                                   0xa
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGIRPT_ENABLE_BMSK                                                                 0x200
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGIRPT_ENABLE_SHFT                                                                   0x9
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_NSGIRPT_ENABLE_BMSK                                                                 0x100
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_NSGIRPT_ENABLE_SHFT                                                                   0x8
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MDSS_DMA_MMU_NSGIRPT_ENABLE_BMSK                                                                        0x80
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MDSS_DMA_MMU_NSGIRPT_ENABLE_SHFT                                                                         0x7
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGIRPT_ENABLE_BMSK                                                                            0x40
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGIRPT_ENABLE_SHFT                                                                             0x6
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MDSS_MMU_NSGIRPT_ENABLE_BMSK                                                                            0x20
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MDSS_MMU_NSGIRPT_ENABLE_SHFT                                                                             0x5
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_NSGIRPT_ENABLE_BMSK                                                                      0x10
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_NSGIRPT_ENABLE_SHFT                                                                       0x4
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_VFE_MMU_NSGIRPT_ENABLE_BMSK                                                                        0x8
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_VFE_MMU_NSGIRPT_ENABLE_SHFT                                                                        0x3
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_CPP_MMU_NSGIRPT_ENABLE_BMSK                                                                        0x4
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_CAMSS_CPP_MMU_NSGIRPT_ENABLE_SHFT                                                                        0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_VENUS0_MMU_NSGIRPT_ENABLE_BMSK                                                                           0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_VENUS0_MMU_NSGIRPT_ENABLE_SHFT                                                                           0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00003000)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_OFFS                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00003000)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RMSK                                                                                                         0x3dff
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_PIMEM_VMIDMT_NSGCFGIRPT_BMSK                                                                                 0x2000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_PIMEM_VMIDMT_NSGCFGIRPT_SHFT                                                                                    0xd
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SPDM_VMID_NSGCFGIRPT_BMSK                                                                                    0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SPDM_VMID_NSGCFGIRPT_SHFT                                                                                       0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGCFGIRPT_BMSK                                                                               0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGCFGIRPT_SHFT                                                                                 0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGCFGIRPT_BMSK                                                                             0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGCFGIRPT_SHFT                                                                               0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP2_VMIDMT_NSGCFGIRPT_BMSK                                                                                  0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP2_VMIDMT_NSGCFGIRPT_SHFT                                                                                    0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP1_VMIDMT_NSGCFGIRPT_BMSK                                                                                   0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP1_VMIDMT_NSGCFGIRPT_SHFT                                                                                    0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_BMSK                                                                                     0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_SHFT                                                                                      0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGCFGIRPT_BMSK                                                                                0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGCFGIRPT_SHFT                                                                                 0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_UFS_VMIDMT_NSGCFGIRPT_BMSK                                                                                     0x10
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_UFS_VMIDMT_NSGCFGIRPT_SHFT                                                                                      0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_VENUS1_VBIF_VMIDMT_NSGCFGIRPT_BMSK                                                                              0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_VENUS1_VBIF_VMIDMT_NSGCFGIRPT_SHFT                                                                              0x3
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_VENUS0_VBIF_VMIDMT_NSGCFGIRPT_BMSK                                                                              0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_VENUS0_VBIF_VMIDMT_NSGCFGIRPT_SHFT                                                                              0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                                                     0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                                                     0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGCFGIRPT_BMSK                                                                                  0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGCFGIRPT_SHFT                                                                                  0x0

#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00003004)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OFFS                                                                                                        (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00003004)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_RMSK                                                                                                            0x1ffe
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_4_IRQ_OUT_SECURITY_BMSK                                                                                   0x1000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_4_IRQ_OUT_SECURITY_SHFT                                                                                      0xc
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_12_IRQ_OUT_SECURITY_BMSK                                                                                   0x800
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_12_IRQ_OUT_SECURITY_SHFT                                                                                     0xb
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_BMSK                                                                               0x400
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_SHFT                                                                                 0xa
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_BMSK                                                                               0x200
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_SHFT                                                                                 0x9
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR0_NOC_SMMU_MMU_NSGCFGIRPT_BMSK                                                                               0x100
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR0_NOC_SMMU_MMU_NSGCFGIRPT_SHFT                                                                                 0x8
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MDSS_DMA_MMU_NSGCFGIRPT_BMSK                                                                                      0x80
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MDSS_DMA_MMU_NSGCFGIRPT_SHFT                                                                                       0x7
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OGPU_MMU_NSGCFGIRPT_BMSK                                                                                          0x40
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OGPU_MMU_NSGCFGIRPT_SHFT                                                                                           0x6
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MDSS_MMU_NSGCFGIRPT_BMSK                                                                                          0x20
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MDSS_MMU_NSGCFGIRPT_SHFT                                                                                           0x5
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_JPEG_MMU_NSGCFGIRPT_BMSK                                                                                    0x10
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_JPEG_MMU_NSGCFGIRPT_SHFT                                                                                     0x4
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_VFE_MMU_NSGCFGIRPT_BMSK                                                                                      0x8
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_VFE_MMU_NSGCFGIRPT_SHFT                                                                                      0x3
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_CPP_MMU_NSGCFGIRPT_BMSK                                                                                      0x4
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_CAMSS_CPP_MMU_NSGCFGIRPT_SHFT                                                                                      0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_VENUS0_MMU_NSGCFGIRPT_BMSK                                                                                         0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_VENUS0_MMU_NSGCFGIRPT_SHFT                                                                                         0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00003040)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_OFFS                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00003040)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RMSK                                                                                                  0x3dff
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_PIMEM_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                   0x2000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_PIMEM_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                      0xd
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGCFGIRPT_ENABLE_BMSK                                                                      0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGCFGIRPT_ENABLE_SHFT                                                                         0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                 0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                   0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                               0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                 0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                    0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                      0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                     0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                      0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_BMSK                                                                       0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_SHFT                                                                        0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                  0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                   0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_UFS_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                       0x10
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_UFS_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                        0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                0x3
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGCFGIRPT_ENABLE_BMSK                                                                 0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGCFGIRPT_ENABLE_SHFT                                                                 0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                                                    0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                                                    0x0

#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00003044)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OFFS                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00003044)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_RMSK                                                                                                     0x1ffe
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_4_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                0x1000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_4_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                   0xc
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_12_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                0x800
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_12_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                  0xb
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                 0x400
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                   0xa
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                 0x200
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                   0x9
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                 0x100
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                   0x8
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MDSS_DMA_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                        0x80
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MDSS_DMA_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                         0x7
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                            0x40
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                             0x6
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MDSS_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                            0x20
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MDSS_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                             0x5
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                      0x10
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                       0x4
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_VFE_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                        0x8
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_VFE_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                        0x3
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_CPP_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                        0x4
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_CAMSS_CPP_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                        0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_VENUS0_MMU_NSGCFGIRPT_ENABLE_BMSK                                                                           0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_VENUS0_MMU_NSGCFGIRPT_ENABLE_SHFT                                                                           0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00004010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_OFFS                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RMSK                                                                                                          0x3dff
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_PIMEM_VMIDMT_GIRPT_BMSK                                                                                       0x2000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_PIMEM_VMIDMT_GIRPT_SHFT                                                                                          0xd
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SPDM_VMID_GIRPT_BMSK                                                                                          0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SPDM_VMID_GIRPT_SHFT                                                                                             0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_DAP_VMIDMT_GIRPT_BMSK                                                                                     0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_DAP_VMIDMT_GIRPT_SHFT                                                                                       0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_TRACE_VMIDMT_GIRPT_BMSK                                                                                   0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_TRACE_VMIDMT_GIRPT_SHFT                                                                                     0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP2_VMIDMT_GIRPT_BMSK                                                                                        0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP2_VMIDMT_GIRPT_SHFT                                                                                          0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP1_VMIDMT_GIRPT_BMSK                                                                                         0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP1_VMIDMT_GIRPT_SHFT                                                                                          0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_BMSK                                                                                      0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_SHFT                                                                                       0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_BAM_VMIDMT_GIRPT_BMSK                                                                                      0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_BAM_VMIDMT_GIRPT_SHFT                                                                                       0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_UFS_VMIDMT_GIRPT_BMSK                                                                                           0x10
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_UFS_VMIDMT_GIRPT_SHFT                                                                                            0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_VENUS1_VBIF_VMIDMT_GIRPT_BMSK                                                                                    0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_VENUS1_VBIF_VMIDMT_GIRPT_SHFT                                                                                    0x3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_VENUS0_VBIF_VMIDMT_GIRPT_BMSK                                                                                    0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_VENUS0_VBIF_VMIDMT_GIRPT_SHFT                                                                                    0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                                                      0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                                                      0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_CRYPTO0_VMIDMT_GIRPT_BMSK                                                                                        0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_CRYPTO0_VMIDMT_GIRPT_SHFT                                                                                        0x0

#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00004014)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004014)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_RMSK                                                                                                             0x1ffe
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_7_IRQ_OUT_SECURITY_BMSK                                                                                    0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_7_IRQ_OUT_SECURITY_SHFT                                                                                       0xc
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_15_IRQ_OUT_SECURITY_BMSK                                                                                    0x800
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_15_IRQ_OUT_SECURITY_SHFT                                                                                      0xb
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR2_NOC_SMMU_MMU_GIRPT_BMSK                                                                                     0x400
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR2_NOC_SMMU_MMU_GIRPT_SHFT                                                                                       0xa
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR1_NOC_SMMU_MMU_GIRPT_BMSK                                                                                     0x200
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR1_NOC_SMMU_MMU_GIRPT_SHFT                                                                                       0x9
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR0_NOC_SMMU_MMU_GIRPT_BMSK                                                                                     0x100
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR0_NOC_SMMU_MMU_GIRPT_SHFT                                                                                       0x8
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MDSS_DMA_MMU_GIRPT_BMSK                                                                                            0x80
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MDSS_DMA_MMU_GIRPT_SHFT                                                                                             0x7
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_OGPU_MMU_GIRPT_BMSK                                                                                                0x40
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_OGPU_MMU_GIRPT_SHFT                                                                                                 0x6
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MDSS_MMU_GIRPT_BMSK                                                                                                0x20
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MDSS_MMU_GIRPT_SHFT                                                                                                 0x5
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_JPEG_MMU_GIRPT_BMSK                                                                                          0x10
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_JPEG_MMU_GIRPT_SHFT                                                                                           0x4
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_VFE_MMU_GIRPT_BMSK                                                                                            0x8
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_VFE_MMU_GIRPT_SHFT                                                                                            0x3
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_CPP_MMU_GIRPT_BMSK                                                                                            0x4
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_CAMSS_CPP_MMU_GIRPT_SHFT                                                                                            0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_VENUS0_MMU_GIRPT_BMSK                                                                                               0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_VENUS0_MMU_GIRPT_SHFT                                                                                               0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00004050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_OFFS                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RMSK                                                                                                   0x3dff
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_PIMEM_VMIDMT_GIRPT_ENABLE_BMSK                                                                         0x2000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_PIMEM_VMIDMT_GIRPT_ENABLE_SHFT                                                                            0xd
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SPDM_VMID_GIRPT_ENABLE_BMSK                                                                            0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SPDM_VMID_GIRPT_ENABLE_SHFT                                                                               0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GIRPT_ENABLE_BMSK                                                                       0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GIRPT_ENABLE_SHFT                                                                         0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GIRPT_ENABLE_BMSK                                                                     0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GIRPT_ENABLE_SHFT                                                                       0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP2_VMIDMT_GIRPT_ENABLE_BMSK                                                                          0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP2_VMIDMT_GIRPT_ENABLE_SHFT                                                                            0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP1_VMIDMT_GIRPT_ENABLE_BMSK                                                                           0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP1_VMIDMT_GIRPT_ENABLE_SHFT                                                                            0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_BMSK                                                                        0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_SHFT                                                                         0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GIRPT_ENABLE_BMSK                                                                        0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GIRPT_ENABLE_SHFT                                                                         0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_UFS_VMIDMT_GIRPT_ENABLE_BMSK                                                                             0x10
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_UFS_VMIDMT_GIRPT_ENABLE_SHFT                                                                              0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_GIRPT_ENABLE_BMSK                                                                      0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_GIRPT_ENABLE_SHFT                                                                      0x3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_GIRPT_ENABLE_BMSK                                                                      0x4
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_GIRPT_ENABLE_SHFT                                                                      0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GIRPT_ENABLE_BMSK                                                                       0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GIRPT_ENABLE_SHFT                                                                       0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GIRPT_ENABLE_BMSK                                                                          0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GIRPT_ENABLE_SHFT                                                                          0x0

#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00004054)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OFFS                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00004054)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_RMSK                                                                                                      0x1ffe
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_7_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                 0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_7_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                    0xc
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_15_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                 0x800
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_15_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                   0xb
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GIRPT_ENABLE_BMSK                                                                       0x400
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GIRPT_ENABLE_SHFT                                                                         0xa
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GIRPT_ENABLE_BMSK                                                                       0x200
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GIRPT_ENABLE_SHFT                                                                         0x9
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_GIRPT_ENABLE_BMSK                                                                       0x100
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_GIRPT_ENABLE_SHFT                                                                         0x8
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MDSS_DMA_MMU_GIRPT_ENABLE_BMSK                                                                              0x80
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MDSS_DMA_MMU_GIRPT_ENABLE_SHFT                                                                               0x7
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OGPU_MMU_GIRPT_ENABLE_BMSK                                                                                  0x40
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OGPU_MMU_GIRPT_ENABLE_SHFT                                                                                   0x6
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MDSS_MMU_GIRPT_ENABLE_BMSK                                                                                  0x20
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MDSS_MMU_GIRPT_ENABLE_SHFT                                                                                   0x5
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_GIRPT_ENABLE_BMSK                                                                            0x10
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_GIRPT_ENABLE_SHFT                                                                             0x4
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_VFE_MMU_GIRPT_ENABLE_BMSK                                                                              0x8
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_VFE_MMU_GIRPT_ENABLE_SHFT                                                                              0x3
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_CPP_MMU_GIRPT_ENABLE_BMSK                                                                              0x4
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_CAMSS_CPP_MMU_GIRPT_ENABLE_SHFT                                                                              0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_VENUS0_MMU_GIRPT_ENABLE_BMSK                                                                                 0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_VENUS0_MMU_GIRPT_ENABLE_SHFT                                                                                 0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00005000)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00005000)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RMSK                                                                                                             0x7bfb
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_PIMEM_VMIDMT_GCFGIRPT_BMSK                                                                                       0x4000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_PIMEM_VMIDMT_GCFGIRPT_SHFT                                                                                          0xe
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SPDM_VMID_GCFGIRPT_BMSK                                                                                          0x2000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SPDM_VMID_GCFGIRPT_SHFT                                                                                             0xd
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_DAP_VMIDMT_GCFGIRPT_BMSK                                                                                    0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_DAP_VMIDMT_GCFGIRPT_SHFT                                                                                       0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_TRACE_VMIDMT_GCFGIRPT_BMSK                                                                                   0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_TRACE_VMIDMT_GCFGIRPT_SHFT                                                                                     0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP2_VMIDMT_GCFGIRPT_BMSK                                                                                        0x200
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP2_VMIDMT_GCFGIRPT_SHFT                                                                                          0x9
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP1_VMIDMT_GCFGIRPT_BMSK                                                                                        0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP1_VMIDMT_GCFGIRPT_SHFT                                                                                          0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_BMSK                                                                                         0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SSC_VMIDMT_1_APPS_IRQ_SHFT                                                                                          0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_BAM_VMIDMT_GCFGIRPT_BMSK                                                                                      0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_BAM_VMIDMT_GCFGIRPT_SHFT                                                                                       0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_UFS_VMIDMT_GCFGIRPT_BMSK                                                                                           0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_UFS_VMIDMT_GCFGIRPT_SHFT                                                                                            0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_VENUS1_VBIF_VMIDMT_GCFGIRPT_BMSK                                                                                   0x10
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_VENUS1_VBIF_VMIDMT_GCFGIRPT_SHFT                                                                                    0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_VENUS0_VBIF_VMIDMT_GCFGIRPT_BMSK                                                                                    0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_VENUS0_VBIF_VMIDMT_GCFGIRPT_SHFT                                                                                    0x3
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                                                         0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                                                         0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_CRYPTO0_VMIDMT_GCFGIRPT_BMSK                                                                                        0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_CRYPTO0_VMIDMT_GCFGIRPT_SHFT                                                                                        0x0

#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00005004)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00005004)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_RMSK                                                                                                                0x1ffe
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CFG_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_6_IRQ_OUT_SECURITY_BMSK                                                                                       0x1000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_6_IRQ_OUT_SECURITY_SHFT                                                                                          0xc
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_14_IRQ_OUT_SECURITY_BMSK                                                                                       0x800
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_14_IRQ_OUT_SECURITY_SHFT                                                                                         0xb
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR2_NOC_SMMU_MMU_GCFGIRPT_BMSK                                                                                     0x400
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR2_NOC_SMMU_MMU_GCFGIRPT_SHFT                                                                                       0xa
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR1_NOC_SMMU_MMU_GCFGIRPT_BMSK                                                                                     0x200
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR1_NOC_SMMU_MMU_GCFGIRPT_SHFT                                                                                       0x9
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR0_NOC_SMMU_MMU_GCFGIRPT_BMSK                                                                                     0x100
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR0_NOC_SMMU_MMU_GCFGIRPT_SHFT                                                                                       0x8
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MDSS_DMA_MMU_GCFGIRPT_BMSK                                                                                            0x80
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MDSS_DMA_MMU_GCFGIRPT_SHFT                                                                                             0x7
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OGPU_MMU_GCFGIRPT_BMSK                                                                                                0x40
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OGPU_MMU_GCFGIRPT_SHFT                                                                                                 0x6
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MDSS_MMU_GCFGIRPT_BMSK                                                                                                0x20
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MDSS_MMU_GCFGIRPT_SHFT                                                                                                 0x5
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_JPEG_MMU_GCFGIRPT_BMSK                                                                                          0x10
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_JPEG_MMU_GCFGIRPT_SHFT                                                                                           0x4
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_VFE_MMU_GCFGIRPT_BMSK                                                                                            0x8
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_VFE_MMU_GCFGIRPT_SHFT                                                                                            0x3
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_CPP_MMU_GCFGIRPT_BMSK                                                                                            0x4
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_CAMSS_CPP_MMU_GCFGIRPT_SHFT                                                                                            0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_VENUS0_MMU_GCFGIRPT_BMSK                                                                                               0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_VENUS0_MMU_GCFGIRPT_SHFT                                                                                               0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00005040)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_OFFS                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00005040)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RMSK                                                                                                      0x3dff
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_PIMEM_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                         0x2000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_PIMEM_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                            0xd
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SPDM_VMID_GCFGIRPT_ENABLE_BMSK                                                                            0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SPDM_VMID_GCFGIRPT_ENABLE_SHFT                                                                               0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                       0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                         0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                     0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                       0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP2_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                          0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP2_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                            0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP1_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                           0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP1_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                            0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_BMSK                                                                           0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SSC_VMIDMT_0_APPS_IRQ_ENABLE_SHFT                                                                            0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                        0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                         0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_UFS_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                             0x10
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_UFS_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                              0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                      0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_VENUS1_VBIF_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                      0x3
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                      0x4
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_VENUS0_VBIF_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                      0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GCFGIRPT_ENABLE_BMSK                                                                       0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GCFGIRPT_ENABLE_SHFT                                                                       0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GCFGIRPT_ENABLE_BMSK                                                                          0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GCFGIRPT_ENABLE_SHFT                                                                          0x0

#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00005044)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OFFS                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00005044)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_RMSK                                                                                                         0x1ffe
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_6_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                    0x1000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_6_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                       0xc
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_14_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                                                    0x800
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_14_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                                                      0xb
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GCFGIRPT_ENABLE_BMSK                                                                       0x400
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GCFGIRPT_ENABLE_SHFT                                                                         0xa
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GCFGIRPT_ENABLE_BMSK                                                                       0x200
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GCFGIRPT_ENABLE_SHFT                                                                         0x9
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_GCFGIRPT_ENABLE_BMSK                                                                       0x100
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR0_NOC_SMMU_MMU_GCFGIRPT_ENABLE_SHFT                                                                         0x8
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MDSS_DMA_MMU_GCFGIRPT_ENABLE_BMSK                                                                              0x80
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MDSS_DMA_MMU_GCFGIRPT_ENABLE_SHFT                                                                               0x7
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OGPU_MMU_GCFGIRPT_ENABLE_BMSK                                                                                  0x40
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OGPU_MMU_GCFGIRPT_ENABLE_SHFT                                                                                   0x6
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MDSS_MMU_GCFGIRPT_ENABLE_BMSK                                                                                  0x20
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MDSS_MMU_GCFGIRPT_ENABLE_SHFT                                                                                   0x5
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_GCFGIRPT_ENABLE_BMSK                                                                            0x10
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_JPEG_MMU_GCFGIRPT_ENABLE_SHFT                                                                             0x4
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_VFE_MMU_GCFGIRPT_ENABLE_BMSK                                                                              0x8
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_VFE_MMU_GCFGIRPT_ENABLE_SHFT                                                                              0x3
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_CPP_MMU_GCFGIRPT_ENABLE_BMSK                                                                              0x4
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_CAMSS_CPP_MMU_GCFGIRPT_ENABLE_SHFT                                                                              0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_VENUS0_MMU_GCFGIRPT_ENABLE_BMSK                                                                                 0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_VENUS0_MMU_GCFGIRPT_ENABLE_SHFT                                                                                 0x1

#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00006000)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00006000)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_RMSK                                                                                                              0xfffffffe
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR0_ADDR, HWIO_TCSR_SS_XPU2_MSA_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_QDSS_MPU_CFG_XPU2_MSA_INTR_BMSK                                                                                   0x80000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_QDSS_MPU_CFG_XPU2_MSA_INTR_SHFT                                                                                         0x1f
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BOOT_ROM_MSA_INTR_BMSK                                                                                            0x40000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BOOT_ROM_MSA_INTR_SHFT                                                                                                  0x1e
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_NOC_CFG_XPU2_MSA_INTR_BMSK                                                                                        0x20000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_NOC_CFG_XPU2_MSA_INTR_SHFT                                                                                              0x1d
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_LPASS_IRQ_OUT_SECURITY_2_BMSK                                                                                     0x10000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_LPASS_IRQ_OUT_SECURITY_2_SHFT                                                                                           0x1c
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_TLMM_XPU_MSA_INTR_BMSK                                                                                             0x8000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_TLMM_XPU_MSA_INTR_SHFT                                                                                                  0x1b
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SPDM_XPU_MSA_INTR_BMSK                                                                                             0x4000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SPDM_XPU_MSA_INTR_SHFT                                                                                                  0x1a
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PMIC_ARB_XPU2_MSA_INTR_BMSK                                                                                        0x2000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PMIC_ARB_XPU2_MSA_INTR_SHFT                                                                                             0x19
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_UFS_ICE_XPU2_MSA_INTR_BMSK                                                                                         0x1000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_UFS_ICE_XPU2_MSA_INTR_SHFT                                                                                              0x18
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_VENUS_WRAPPER_XPU2_MSA_INTERRUPT_BMSK                                                                               0x800000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_VENUS_WRAPPER_XPU2_MSA_INTERRUPT_SHFT                                                                                   0x17
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CH1_XPU2_MSA_INTERRUPT_BMSK                                                                                    0x400000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CH1_XPU2_MSA_INTERRUPT_SHFT                                                                                        0x16
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CH0_XPU2_MSA_INTERRUPT_BMSK                                                                                    0x200000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CH0_XPU2_MSA_INTERRUPT_SHFT                                                                                        0x15
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CFG_XPU2_MSA_INTERRUPT_BMSK                                                                                    0x100000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_BIMC_CFG_XPU2_MSA_INTERRUPT_SHFT                                                                                        0x14
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_GCC_XPU_MSA_INTR_BMSK                                                                                                0x80000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_GCC_XPU_MSA_INTR_SHFT                                                                                                   0x13
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_UFS_XPU_MSA_INTR_BMSK                                                                                                0x40000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_UFS_XPU_MSA_INTR_SHFT                                                                                                   0x12
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A2NOC_MPU_CFG_XPU2_MSA_INTR_BMSK                                                                                     0x20000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A2NOC_MPU_CFG_XPU2_MSA_INTR_SHFT                                                                                        0x11
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A1NOC_MPU_CFG_XPU2_MSA_INTR_BMSK                                                                                     0x10000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A1NOC_MPU_CFG_XPU2_MSA_INTR_SHFT                                                                                        0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A0NOC_MPU_CFG_XPU2_MSA_INTR_BMSK                                                                                      0x8000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_A0NOC_MPU_CFG_XPU2_MSA_INTR_SHFT                                                                                         0xf
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PIMEM_MPU_MSA_IRQ_BMSK                                                                                                0x4000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PIMEM_MPU_MSA_IRQ_SHFT                                                                                                   0xe
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PIMEM_APU_MSA_IRQ_BMSK                                                                                                0x2000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_PIMEM_APU_MSA_IRQ_SHFT                                                                                                   0xd
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_0_BMSK                                                                                               0x1000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_0_SHFT                                                                                                  0xc
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_10_BMSK                                                                                               0x800
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_10_SHFT                                                                                                 0xb
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_3_BMSK                                                                                                0x400
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SSC_XPU_IRQ_APPS_3_SHFT                                                                                                  0xa
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SEC_CTRL_XPU2_MSA_INTR_BMSK                                                                                            0x200
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_SEC_CTRL_XPU2_MSA_INTR_SHFT                                                                                              0x9
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_DCC_XPU2_MSA_INTR_BMSK                                                                                                 0x100
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_DCC_XPU2_MSA_INTR_SHFT                                                                                                   0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_OCIMEM_RPU_MSA_INTR_BMSK                                                                                                0x80
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_OCIMEM_RPU_MSA_INTR_SHFT                                                                                                 0x7
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_CRYPTO0_BAM_XPU2_MSA_INTR_BMSK                                                                                          0x40
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_CRYPTO0_BAM_XPU2_MSA_INTR_SHFT                                                                                           0x6
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_O_TCSR_MUTEX_MSA_INTR_BMSK                                                                                              0x20
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_O_TCSR_MUTEX_MSA_INTR_SHFT                                                                                               0x5
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_COPSS_MSA_IRQ_BMSK                                                                                                      0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_COPSS_MSA_IRQ_SHFT                                                                                                       0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_O_TCSR_REGS_MSA_INTR_BMSK                                                                                                0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_O_TCSR_REGS_MSA_INTR_SHFT                                                                                                0x3
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_MMSS_NOC_XPU2_MSA_INTR_BMSK                                                                                              0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_MMSS_NOC_XPU2_MSA_INTR_SHFT                                                                                              0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_DSA_XPU2_MSA_INTR_BMSK                                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_DSA_XPU2_MSA_INTR_SHFT                                                                                                   0x1

#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00006004)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00006004)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_RMSK                                                                                                                   0x3ff
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR1_ADDR, HWIO_TCSR_SS_XPU2_MSA_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_RPM_MPU_MSA_INTR_BMSK                                                                                                  0x200
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_RPM_MPU_MSA_INTR_SHFT                                                                                                    0x9
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_LPASS_IRQ_OUT_SECURIT_10_BMSK                                                                                          0x100
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_LPASS_IRQ_OUT_SECURIT_10_SHFT                                                                                            0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_MDSS_XPU2_MSA_INTR_BMSK                                                                                                 0x80
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_MDSS_XPU2_MSA_INTR_SHFT                                                                                                  0x7
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_QDSS_BAM_XPU2_MSA_INTR_BMSK                                                                                             0x40
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_QDSS_BAM_XPU2_MSA_INTR_SHFT                                                                                              0x6
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_MPM_XPU2_MSA_INTR_BMSK                                                                                                  0x20
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_MPM_XPU2_MSA_INTR_SHFT                                                                                                   0x5
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_SDCC2_XPU2_MSA_INTR_BMSK                                                                                                0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_SDCC2_XPU2_MSA_INTR_SHFT                                                                                                 0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_RBCPR_APU_XPU2_MSA_INTR_BMSK                                                                                             0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_RBCPR_APU_XPU2_MSA_INTR_SHFT                                                                                             0x3
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_BLSP2_XPU2_MSA_INTR_BMSK                                                                                                 0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_BLSP2_XPU2_MSA_INTR_SHFT                                                                                                 0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_BLSP1_XPU2_MSA_INTR_BMSK                                                                                                 0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_BLSP1_XPU2_MSA_INTR_SHFT                                                                                                 0x1
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_OCIMEM_RPU_MSA_INTR_BMSK                                                                                                 0x1
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_OCIMEM_RPU_MSA_INTR_SHFT                                                                                                 0x0

#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_ADDR                                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00006040)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_OFFS                                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00006040)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_RMSK                                                                                                       0xfffffffe
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_QDSS_MPU_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                     0x80000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_QDSS_MPU_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                           0x1f
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BOOT_ROM_MSA_INTR_ENABLE_BMSK                                                                              0x40000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BOOT_ROM_MSA_INTR_ENABLE_SHFT                                                                                    0x1e
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_NOC_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                          0x20000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_NOC_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                                0x1d
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_2_INTR_ENABLE_BMSK                                                                  0x10000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_LPASS_IRQ_OUT_SECURITY_2_INTR_ENABLE_SHFT                                                                        0x1c
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_TLMM_XPU_MSA_INTR_ENABLE_BMSK                                                                               0x8000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_TLMM_XPU_MSA_INTR_ENABLE_SHFT                                                                                    0x1b
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SPDM_XPU_MSA_INTR_ENABLE_BMSK                                                                               0x4000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SPDM_XPU_MSA_INTR_ENABLE_SHFT                                                                                    0x1a
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PMIC_ARB_XPU2_MSA_INTR_ENABLE_BMSK                                                                          0x2000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PMIC_ARB_XPU2_MSA_INTR_ENABLE_SHFT                                                                               0x19
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_UFS_ICE_XPU2_MSA_INTR_ENABLE_BMSK                                                                           0x1000000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_UFS_ICE_XPU2_MSA_INTR_ENABLE_SHFT                                                                                0x18
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_VENUS_WRAPPER_XPU2_MSA_INTR_ENABLE_BMSK                                                                      0x800000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_VENUS_WRAPPER_XPU2_MSA_INTR_ENABLE_SHFT                                                                          0x17
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CH1_XPU2_MSA_INTR_ENABLE_BMSK                                                                           0x400000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CH1_XPU2_MSA_INTR_ENABLE_SHFT                                                                               0x16
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CH0_XPU2_MSA_INTR_ENABLE_BMSK                                                                           0x200000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CH0_XPU2_MSA_INTR_ENABLE_SHFT                                                                               0x15
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                           0x100000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_BIMC_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                               0x14
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_GCC_XPU_MSA_INTR_ENABLE_BMSK                                                                                  0x80000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_GCC_XPU_MSA_INTR_ENABLE_SHFT                                                                                     0x13
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_UFS_XPU_MSA_INTR_ENABLE_BMSK                                                                                  0x40000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_UFS_XPU_MSA_INTR_ENABLE_SHFT                                                                                     0x12
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                       0x20000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A2NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                          0x11
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                       0x10000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A1NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                          0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_BMSK                                                                        0x8000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_A0NOC_MPU_CFG_XPU2_MSA_INTR_ENABLE_SHFT                                                                           0xf
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PIMEM_MPU_MSA_INTR_ENABLE_BMSK                                                                                 0x4000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PIMEM_MPU_MSA_INTR_ENABLE_SHFT                                                                                    0xe
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PIMEM_APU_MSA_INTR_ENABLE_BMSK                                                                                 0x2000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_PIMEM_APU_MSA_INTR_ENABLE_SHFT                                                                                    0xd
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_0_INTR_ENABLE_BMSK                                                                            0x1000
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_0_INTR_ENABLE_SHFT                                                                               0xc
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_10_INTR_ENABLE_BMSK                                                                            0x800
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_10_INTR_ENABLE_SHFT                                                                              0xb
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_3_INTR_ENABLE_BMSK                                                                             0x400
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SSC_XPU_IRQ_APPS_3_INTR_ENABLE_SHFT                                                                               0xa
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SEC_CTRL_XPU2_MSA_INTR_ENABLE_BMSK                                                                              0x200
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_SEC_CTRL_XPU2_MSA_INTR_ENABLE_SHFT                                                                                0x9
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_DCC_XPU2_MSA_INTR_ENABLE_BMSK                                                                                   0x100
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_DCC_XPU2_MSA_INTR_ENABLE_SHFT                                                                                     0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_BMSK                                                                                  0x80
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_SHFT                                                                                   0x7
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_CRYPTO0_BAM_XPU2_MSA_INTR_ENABLE_BMSK                                                                            0x40
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_CRYPTO0_BAM_XPU2_MSA_INTR_ENABLE_SHFT                                                                             0x6
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_O_TCSR_MUTEX_MSA_INTR_ENABLE_BMSK                                                                                0x20
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_O_TCSR_MUTEX_MSA_INTR_ENABLE_SHFT                                                                                 0x5
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_COPSS_MSA_IRQ_ENABLE_BMSK                                                                                        0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_COPSS_MSA_IRQ_ENABLE_SHFT                                                                                         0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_O_TCSR_REGS_MSA_INTR_ENABLE_BMSK                                                                                  0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_O_TCSR_REGS_MSA_INTR_ENABLE_SHFT                                                                                  0x3
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_MMSS_NOC_XPU2_MSA_INTR_EN_BMSK                                                                                    0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_MMSS_NOC_XPU2_MSA_INTR_EN_SHFT                                                                                    0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_DSA_XPU2_MSA_INTR_EN_BMSK                                                                                         0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR0_ENABLE_DSA_XPU2_MSA_INTR_EN_SHFT                                                                                         0x1

#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_ADDR                                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00006044)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_OFFS                                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00006044)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RMSK                                                                                                            0x3ff
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RPM_MPU_MSA_INTR_ENABLE_BMSK                                                                                    0x200
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RPM_MPU_MSA_INTR_ENABLE_SHFT                                                                                      0x9
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_10_INTR_ENABLE_BMSK                                                                       0x100
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURIT_10_INTR_ENABLE_SHFT                                                                         0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_MDSS_XPU2_MSA_INTR_ENABLE_BMSK                                                                                   0x80
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_MDSS_XPU2_MSA_INTR_ENABLE_SHFT                                                                                    0x7
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_QDSS_BAM_XPU2_MSA_INTR_ENABLE_BMSK                                                                               0x40
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_QDSS_BAM_XPU2_MSA_INTR_ENABLE_SHFT                                                                                0x6
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_MPM_XPU2_MSA_INTR_ENABLE_BMSK                                                                                    0x20
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_MPM_XPU2_MSA_INTR_ENABLE_SHFT                                                                                     0x5
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_SDCC2_XPU2_MSA_INTR_ENABLE_BMSK                                                                                  0x10
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_SDCC2_XPU2_MSA_INTR_ENABLE_SHFT                                                                                   0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RBCPR_APU_XPU2_MSA_INTR_ENABLE_BMSK                                                                               0x8
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_RBCPR_APU_XPU2_MSA_INTR_ENABLE_SHFT                                                                               0x3
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_BLSP2_XPU2_MSA_INTR_ENABLE_BMSK                                                                                   0x4
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_BLSP2_XPU2_MSA_INTR_ENABLE_SHFT                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_BLSP1_XPU2_MSA_INTR_ENABLE_BMSK                                                                                   0x2
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_BLSP1_XPU2_MSA_INTR_ENABLE_SHFT                                                                                   0x1
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_BMSK                                                                                   0x1
#define HWIO_TCSR_SS_XPU2_MSA_INTR1_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_SHFT                                                                                   0x0

#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00007000)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007000)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_RMSK                                                                                                                  0xffff
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR, HWIO_TCSR_SPDM_CNT_CLK_CTRL_RMSK)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR, m)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR,v)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR,m,v,HWIO_TCSR_SPDM_CNT_CLK_CTRL_IN)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_SPDM_CNT_CLK_MUX_SEL_BMSK                                                                                             0xffff
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_SPDM_CNT_CLK_MUX_SEL_SHFT                                                                                                0x0

#define HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00007004)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007004)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_RMSK                                                                                                               0xffffffff
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR, HWIO_TCSR_SPDM_DLY_FIFO_EN_RMSK)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR, m)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR,v)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR,m,v,HWIO_TCSR_SPDM_DLY_FIFO_EN_IN)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_SPDM_DLY_FIFO_EN_BMSK                                                                                              0xffffffff
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_SPDM_DLY_FIFO_EN_SHFT                                                                                                     0x0

#define HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00007008)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007008)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_RMSK                                                                                                                  0xffff
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG1_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG1_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_SPDM_STG1_MUX_SEL_BMSK                                                                                                0xffff
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_SPDM_STG1_MUX_SEL_SHFT                                                                                                   0x0

#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000700c)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000700c)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_RMSK                                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG2_A_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG2_A_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_SPDM_STG2_A_MUX_SEL_BMSK                                                                                        0xffffffff
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_SPDM_STG2_A_MUX_SEL_SHFT                                                                                               0x0

#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00007010)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007010)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_RMSK                                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG2_B_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG2_B_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_SPDM_STG2_B_MUX_SEL_BMSK                                                                                        0xffffffff
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_SPDM_STG2_B_MUX_SEL_SHFT                                                                                               0x0

#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00007014)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007014)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_RMSK                                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG3_A_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG3_A_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_SPDM_STG3_A_MUX_SEL_BMSK                                                                                        0xffffffff
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_SPDM_STG3_A_MUX_SEL_SHFT                                                                                               0x0

#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00007018)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007018)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_RMSK                                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG3_B_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG3_B_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_SPDM_STG3_B_MUX_SEL_BMSK                                                                                        0xffffffff
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_SPDM_STG3_B_MUX_SEL_SHFT                                                                                               0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000701c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000701c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_SPDM_WRP_RT_INTF_CTL0_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_SPDM_WRP_RT_INTF_CTL0_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007020)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007020)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_SPDM_WRP_RT_INTF_CTL1_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_SPDM_WRP_RT_INTF_CTL1_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007024)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007024)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_SPDM_WRP_RT_INTF_CTL2_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_SPDM_WRP_RT_INTF_CTL2_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007028)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007028)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_SPDM_WRP_RT_INTF_CTL3_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_SPDM_WRP_RT_INTF_CTL3_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000702c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000702c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_SPDM_WRP_RT_INTF_CTL4_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_SPDM_WRP_RT_INTF_CTL4_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007030)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007030)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_SPDM_WRP_RT_INTF_CTL5_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_SPDM_WRP_RT_INTF_CTL5_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007034)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007034)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_SPDM_WRP_RT_INTF_CTL6_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_SPDM_WRP_RT_INTF_CTL6_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007038)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007038)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_SPDM_WRP_RT_INTF_CTL7_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_SPDM_WRP_RT_INTF_CTL7_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000703c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000703c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_SPDM_WRP_RT_INTF_CTL8_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_SPDM_WRP_RT_INTF_CTL8_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00007040)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007040)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_SPDM_WRP_RT_INTF_CTL9_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_SPDM_WRP_RT_INTF_CTL9_SHFT                                                                                           0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007044)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007044)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_SPDM_WRP_RT_INTF_CTL10_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_SPDM_WRP_RT_INTF_CTL10_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007048)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007048)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_SPDM_WRP_RT_INTF_CTL11_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_SPDM_WRP_RT_INTF_CTL11_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000704c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000704c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_SPDM_WRP_RT_INTF_CTL12_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_SPDM_WRP_RT_INTF_CTL12_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007050)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007050)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_SPDM_WRP_RT_INTF_CTL13_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_SPDM_WRP_RT_INTF_CTL13_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007054)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007054)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_SPDM_WRP_RT_INTF_CTL14_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_SPDM_WRP_RT_INTF_CTL14_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007058)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007058)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_SPDM_WRP_RT_INTF_CTL15_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_SPDM_WRP_RT_INTF_CTL15_SHFT                                                                                         0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000705c)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000705c)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_RMSK                                                                                                              0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL0_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL0_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_SPDM_WRP_CTI_CTL0_BMSK                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_SPDM_WRP_CTI_CTL0_SHFT                                                                                                   0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00007060)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007060)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_RMSK                                                                                                              0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL1_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL1_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_SPDM_WRP_CTI_CTL1_BMSK                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_SPDM_WRP_CTI_CTL1_SHFT                                                                                                   0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00007064)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007064)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_RMSK                                                                                                              0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL2_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL2_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_SPDM_WRP_CTI_CTL2_BMSK                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_SPDM_WRP_CTI_CTL2_SHFT                                                                                                   0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00007068)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007068)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_RMSK                                                                                                              0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL3_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL3_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_SPDM_WRP_CTI_CTL3_BMSK                                                                                            0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_SPDM_WRP_CTI_CTL3_SHFT                                                                                                   0x0

#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000706c)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000706c)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR, HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_IN)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_SPDM_WRP_CTL_COMMON_BMSK                                                                                     0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_SPDM_WRP_CTL_COMMON_SHFT                                                                                            0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00007070)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00007070)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_RMSK                                                                                                                      0x7
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_SPDM_WRP_CTI_CTL_BMSK                                                                                                     0x7
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_SPDM_WRP_CTI_CTL_SHFT                                                                                                     0x0

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00008000)
#define HWIO_TCSR_SOC_HW_VERSION_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                                                                 0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN          \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, HWIO_TCSR_SOC_HW_VERSION_RMSK)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                                                   0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                                                         0x1c
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                                                    0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                                                         0x10
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                                                       0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                                                          0x8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                                                         0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                                                          0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00008020)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008020)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK                                                                                                            0x1f6ffbff
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S9_IRQ_BMSK                                                                                    0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S9_IRQ_SHFT                                                                                          0x1c
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S8_IRQ_BMSK                                                                                     0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S8_IRQ_SHFT                                                                                          0x1b
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S1_IRQ_BMSK                                                                                     0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S1_IRQ_SHFT                                                                                          0x1a
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_BMSK                                                                                   0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_SHFT                                                                                        0x19
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS4_BUS_TIMEOUT_IRQ_BMSK                                                                                   0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS4_BUS_TIMEOUT_IRQ_SHFT                                                                                        0x18
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_BMSK                                                                                   0x400000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_SHFT                                                                                       0x16
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_BMSK                                                                                   0x200000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_SHFT                                                                                       0x15
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_BMSK                                                                                     0x80000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_SHFT                                                                                        0x13
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_BMSK                                                                                     0x40000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_SHFT                                                                                        0x12
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_BMSK                                                                                      0x20000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_SHFT                                                                                         0x11
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S7_IRQ_BMSK                                                                                       0x10000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S7_IRQ_SHFT                                                                                          0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_4_IRQ_BMSK                                                                                        0x8000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_4_IRQ_SHFT                                                                                           0xf
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_3_IRQ_BMSK                                                                                        0x4000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_3_IRQ_SHFT                                                                                           0xe
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_2_IRQ_BMSK                                                                                        0x2000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_2_IRQ_SHFT                                                                                           0xd
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_1_IRQ_BMSK                                                                                        0x1000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_1_IRQ_SHFT                                                                                           0xc
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_0_IRQ_BMSK                                                                                         0x800
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_COPSS_BUS_TIMEOUT_0_IRQ_SHFT                                                                                           0xb
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_SSC_IRQ_OUT_AHB_TIMEOUT_0_BMSK                                                                                       0x200
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_SSC_IRQ_OUT_AHB_TIMEOUT_0_SHFT                                                                                         0x9
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S2_IRQ_BMSK                                                                                         0x100
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S2_IRQ_SHFT                                                                                           0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_SSC_IRQ_OUT_AHB_TIMEOUT_1_BMSK                                                                                        0x80
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_SSC_IRQ_OUT_AHB_TIMEOUT_1_SHFT                                                                                         0x7
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S6_IRQ_BMSK                                                                                          0x40
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S6_IRQ_SHFT                                                                                           0x6
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S5_IRQ_BMSK                                                                                          0x20
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S5_IRQ_SHFT                                                                                           0x5
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S4_IRQ_BMSK                                                                                          0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S4_IRQ_SHFT                                                                                           0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S3_IRQ_BMSK                                                                                           0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S3_IRQ_SHFT                                                                                           0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S2_IRQ_BMSK                                                                                           0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S2_IRQ_SHFT                                                                                           0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S1_IRQ_BMSK                                                                                           0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S1_IRQ_SHFT                                                                                           0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S0_IRQ_BMSK                                                                                           0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_S0_IRQ_SHFT                                                                                           0x0

#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00008030)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_OFFS                                                                                                        (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008030)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_RMSK                                                                                                        0x1f6ffbff
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_BMSK                                                                         0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_SHFT                                                                               0x1c
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_BMSK                                                                          0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_SHFT                                                                               0x1b
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_BMSK                                                                          0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_SHFT                                                                               0x1a
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x19
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x18
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_BMSK                                                                        0x400000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_SHFT                                                                            0x16
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_BMSK                                                                        0x200000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_SHFT                                                                            0x15
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                          0x80000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x13
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                          0x40000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x12
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                           0x20000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                              0x11
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_BMSK                                                                            0x10000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_SHFT                                                                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_BMSK                                                                             0x8000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_SHFT                                                                                0xf
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_BMSK                                                                             0x4000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_SHFT                                                                                0xe
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_BMSK                                                                             0x2000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_SHFT                                                                                0xd
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_BMSK                                                                             0x1000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_SHFT                                                                                0xc
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_BMSK                                                                              0x800
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_SHFT                                                                                0xb
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                                                     0x200
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                                                       0x9
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_BMSK                                                                              0x100
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_SHFT                                                                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                                                      0x80
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                                                       0x7
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_BMSK                                                                               0x40
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_SHFT                                                                                0x6
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_BMSK                                                                               0x20
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_SHFT                                                                                0x5
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_BMSK                                                                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_SHFT                                                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_BMSK                                                                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_SHFT                                                                                0x3
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_BMSK                                                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_SHFT                                                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_BMSK                                                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_SHFT                                                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_BMSK                                                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_SHFT                                                                                0x0

#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR                                                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00008040)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OFFS                                                                                                       (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008040)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK                                                                                                       0x1f6ffbff
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_BMSK                                                                        0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_SHFT                                                                              0x1c
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_BMSK                                                                         0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_SHFT                                                                              0x1b
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_BMSK                                                                         0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_SHFT                                                                              0x1a
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                       0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                            0x19
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                       0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                            0x18
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_BMSK                                                                       0x400000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_SHFT                                                                           0x16
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_BMSK                                                                       0x200000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_SHFT                                                                           0x15
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                         0x80000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                            0x13
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                         0x40000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                            0x12
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                          0x20000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x11
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_BMSK                                                                           0x10000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_SHFT                                                                              0x10
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_BMSK                                                                            0x8000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_SHFT                                                                               0xf
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_BMSK                                                                            0x4000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_SHFT                                                                               0xe
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_BMSK                                                                            0x2000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_SHFT                                                                               0xd
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_BMSK                                                                            0x1000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_SHFT                                                                               0xc
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_BMSK                                                                             0x800
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_SHFT                                                                               0xb
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                                                    0x200
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                                                      0x9
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_BMSK                                                                             0x100
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_SHFT                                                                               0x8
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                                                     0x80
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                                                      0x7
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_BMSK                                                                              0x40
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_SHFT                                                                               0x6
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_BMSK                                                                              0x20
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_SHFT                                                                               0x5
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_BMSK                                                                              0x10
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_SHFT                                                                               0x4
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_BMSK                                                                               0x8
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_SHFT                                                                               0x3
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_BMSK                                                                               0x4
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_SHFT                                                                               0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_BMSK                                                                               0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_SHFT                                                                               0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_BMSK                                                                               0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_SHFT                                                                               0x0

#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00008050)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OFFS                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008050)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK                                                                                                      0x1f6ffbff
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_BMSK                                                                       0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_SHFT                                                                             0x1c
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_BMSK                                                                        0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_SHFT                                                                             0x1b
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_BMSK                                                                        0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_SHFT                                                                             0x1a
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                      0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                           0x19
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                      0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                           0x18
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_BMSK                                                                      0x400000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_SHFT                                                                          0x16
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_BMSK                                                                      0x200000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_SHFT                                                                          0x15
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x80000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                           0x13
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x40000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                           0x12
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                         0x20000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                            0x11
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_BMSK                                                                          0x10000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_SHFT                                                                             0x10
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_BMSK                                                                           0x8000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_SHFT                                                                              0xf
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_BMSK                                                                           0x4000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_SHFT                                                                              0xe
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_BMSK                                                                           0x2000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_SHFT                                                                              0xd
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_BMSK                                                                           0x1000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_SHFT                                                                              0xc
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_BMSK                                                                            0x800
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_SHFT                                                                              0xb
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                                                   0x200
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                                                     0x9
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_BMSK                                                                            0x100
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_SHFT                                                                              0x8
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                                                    0x80
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                                                     0x7
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_BMSK                                                                             0x40
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_SHFT                                                                              0x6
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_BMSK                                                                             0x20
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_SHFT                                                                              0x5
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_BMSK                                                                             0x10
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_SHFT                                                                              0x4
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_BMSK                                                                              0x8
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_SHFT                                                                              0x3
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_BMSK                                                                              0x4
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_SHFT                                                                              0x2
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_BMSK                                                                              0x2
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_SHFT                                                                              0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_BMSK                                                                              0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_SHFT                                                                              0x0

#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00008060)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_OFFS                                                                                                        (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00008060)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_RMSK                                                                                                        0x1f6ffbff
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_BMSK                                                                         0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S9_IRQ_ENABLE_SHFT                                                                               0x1c
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_BMSK                                                                          0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S8_IRQ_ENABLE_SHFT                                                                               0x1b
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_BMSK                                                                          0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S1_IRQ_ENABLE_SHFT                                                                               0x1a
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x19
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                        0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS4_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x18
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_BMSK                                                                        0x400000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT1_SHFT                                                                            0x16
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_BMSK                                                                        0x200000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_ENABLE_OUT_AHB_TIMEOUT0_SHFT                                                                            0x15
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                          0x80000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x13
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                          0x40000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                             0x12
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                                                           0x20000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                                                              0x11
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_BMSK                                                                            0x10000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S7_IRQ_ENABLE_SHFT                                                                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_BMSK                                                                             0x8000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_4_IRQ_ENABLE_SHFT                                                                                0xf
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_BMSK                                                                             0x4000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_3_IRQ_ENABLE_SHFT                                                                                0xe
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_BMSK                                                                             0x2000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_2_IRQ_ENABLE_SHFT                                                                                0xd
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_BMSK                                                                             0x1000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_1_IRQ_ENABLE_SHFT                                                                                0xc
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_BMSK                                                                              0x800
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_COPSS_BUS_TIMEOUT_0_IRQ_ENABLE_SHFT                                                                                0xb
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                                                     0x200
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                                                       0x9
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_BMSK                                                                              0x100
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S2_IRQ_ENABLE_SHFT                                                                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                                                      0x80
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_SSC_IRQ_ENABLE_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                                                       0x7
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_BMSK                                                                               0x40
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S6_IRQ_ENABLE_SHFT                                                                                0x6
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_BMSK                                                                               0x20
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S5_IRQ_ENABLE_SHFT                                                                                0x5
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_BMSK                                                                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S4_IRQ_ENABLE_SHFT                                                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_BMSK                                                                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S3_IRQ_ENABLE_SHFT                                                                                0x3
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_BMSK                                                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S2_IRQ_ENABLE_SHFT                                                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_BMSK                                                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S1_IRQ_ENABLE_SHFT                                                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_BMSK                                                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_S0_IRQ_ENABLE_SHFT                                                                                0x0

#define HWIO_TCSR_TCSR_CLK_EN_ADDR                                                                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0000907c)
#define HWIO_TCSR_TCSR_CLK_EN_OFFS                                                                                                                    (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000907c)
#define HWIO_TCSR_TCSR_CLK_EN_RMSK                                                                                                                           0x1
#define HWIO_TCSR_TCSR_CLK_EN_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_CLK_EN_ADDR, HWIO_TCSR_TCSR_CLK_EN_RMSK)
#define HWIO_TCSR_TCSR_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_CLK_EN_ADDR, m)
#define HWIO_TCSR_TCSR_CLK_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_CLK_EN_ADDR,v)
#define HWIO_TCSR_TCSR_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_CLK_EN_ADDR,m,v,HWIO_TCSR_TCSR_CLK_EN_IN)
#define HWIO_TCSR_TCSR_CLK_EN_TCSR_CLK_EN_BMSK                                                                                                               0x1
#define HWIO_TCSR_TCSR_CLK_EN_TCSR_CLK_EN_SHFT                                                                                                               0x0

#define HWIO_TCSR_SYS_POWER_CTRL_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000a000)
#define HWIO_TCSR_SYS_POWER_CTRL_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a000)
#define HWIO_TCSR_SYS_POWER_CTRL_RMSK                                                                                                                     0xffff
#define HWIO_TCSR_SYS_POWER_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_SYS_POWER_CTRL_ADDR, HWIO_TCSR_SYS_POWER_CTRL_RMSK)
#define HWIO_TCSR_SYS_POWER_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SYS_POWER_CTRL_ADDR, m)
#define HWIO_TCSR_SYS_POWER_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_SYS_POWER_CTRL_ADDR,v)
#define HWIO_TCSR_SYS_POWER_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SYS_POWER_CTRL_ADDR,m,v,HWIO_TCSR_SYS_POWER_CTRL_IN)
#define HWIO_TCSR_SYS_POWER_CTRL_SYS_POWER_CTRL_BMSK                                                                                                      0xffff
#define HWIO_TCSR_SYS_POWER_CTRL_SYS_POWER_CTRL_SHFT                                                                                                         0x0

#define HWIO_TCSR_USB_CORE_ID_ADDR                                                                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0000a004)
#define HWIO_TCSR_USB_CORE_ID_OFFS                                                                                                                    (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a004)
#define HWIO_TCSR_USB_CORE_ID_RMSK                                                                                                                           0x3
#define HWIO_TCSR_USB_CORE_ID_IN          \
        in_dword_masked(HWIO_TCSR_USB_CORE_ID_ADDR, HWIO_TCSR_USB_CORE_ID_RMSK)
#define HWIO_TCSR_USB_CORE_ID_INM(m)      \
        in_dword_masked(HWIO_TCSR_USB_CORE_ID_ADDR, m)
#define HWIO_TCSR_USB_CORE_ID_OUT(v)      \
        out_dword(HWIO_TCSR_USB_CORE_ID_ADDR,v)
#define HWIO_TCSR_USB_CORE_ID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_USB_CORE_ID_ADDR,m,v,HWIO_TCSR_USB_CORE_ID_IN)
#define HWIO_TCSR_USB_CORE_ID_USB_CORE_ID_BMSK                                                                                                               0x3
#define HWIO_TCSR_USB_CORE_ID_USB_CORE_ID_SHFT                                                                                                               0x0

#define HWIO_TCSR_SPARE_REG0_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a044)
#define HWIO_TCSR_SPARE_REG0_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a044)
#define HWIO_TCSR_SPARE_REG0_RMSK                                                                                                                     0xffffffff
#define HWIO_TCSR_SPARE_REG0_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG0_ADDR, HWIO_TCSR_SPARE_REG0_RMSK)
#define HWIO_TCSR_SPARE_REG0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG0_ADDR, m)
#define HWIO_TCSR_SPARE_REG0_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG0_ADDR,v)
#define HWIO_TCSR_SPARE_REG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG0_ADDR,m,v,HWIO_TCSR_SPARE_REG0_IN)
#define HWIO_TCSR_SPARE_REG0_SPARE_REG0_BMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPARE_REG0_SPARE_REG0_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_REG1_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a048)
#define HWIO_TCSR_SPARE_REG1_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a048)
#define HWIO_TCSR_SPARE_REG1_RMSK                                                                                                                     0xffffffff
#define HWIO_TCSR_SPARE_REG1_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG1_ADDR, HWIO_TCSR_SPARE_REG1_RMSK)
#define HWIO_TCSR_SPARE_REG1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG1_ADDR, m)
#define HWIO_TCSR_SPARE_REG1_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG1_ADDR,v)
#define HWIO_TCSR_SPARE_REG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG1_ADDR,m,v,HWIO_TCSR_SPARE_REG1_IN)
#define HWIO_TCSR_SPARE_REG1_SPARE_REG1_BMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPARE_REG1_SPARE_REG1_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_REG2_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a04c)
#define HWIO_TCSR_SPARE_REG2_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a04c)
#define HWIO_TCSR_SPARE_REG2_RMSK                                                                                                                           0xff
#define HWIO_TCSR_SPARE_REG2_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG2_ADDR, HWIO_TCSR_SPARE_REG2_RMSK)
#define HWIO_TCSR_SPARE_REG2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG2_ADDR, m)
#define HWIO_TCSR_SPARE_REG2_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG2_ADDR,v)
#define HWIO_TCSR_SPARE_REG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG2_ADDR,m,v,HWIO_TCSR_SPARE_REG2_IN)
#define HWIO_TCSR_SPARE_REG2_SPARE_REG2_BMSK                                                                                                                0xff
#define HWIO_TCSR_SPARE_REG2_SPARE_REG2_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_REG3_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a050)
#define HWIO_TCSR_SPARE_REG3_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a050)
#define HWIO_TCSR_SPARE_REG3_RMSK                                                                                                                           0xff
#define HWIO_TCSR_SPARE_REG3_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG3_ADDR, HWIO_TCSR_SPARE_REG3_RMSK)
#define HWIO_TCSR_SPARE_REG3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG3_ADDR, m)
#define HWIO_TCSR_SPARE_REG3_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG3_ADDR,v)
#define HWIO_TCSR_SPARE_REG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG3_ADDR,m,v,HWIO_TCSR_SPARE_REG3_IN)
#define HWIO_TCSR_SPARE_REG3_SPARE_REG3_BMSK                                                                                                                0xff
#define HWIO_TCSR_SPARE_REG3_SPARE_REG3_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_REG4_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a054)
#define HWIO_TCSR_SPARE_REG4_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a054)
#define HWIO_TCSR_SPARE_REG4_RMSK                                                                                                                           0xff
#define HWIO_TCSR_SPARE_REG4_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG4_ADDR, HWIO_TCSR_SPARE_REG4_RMSK)
#define HWIO_TCSR_SPARE_REG4_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG4_ADDR, m)
#define HWIO_TCSR_SPARE_REG4_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG4_ADDR,v)
#define HWIO_TCSR_SPARE_REG4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG4_ADDR,m,v,HWIO_TCSR_SPARE_REG4_IN)
#define HWIO_TCSR_SPARE_REG4_SPARE_REG4_BMSK                                                                                                                0xff
#define HWIO_TCSR_SPARE_REG4_SPARE_REG4_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_REG5_ADDR                                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000a058)
#define HWIO_TCSR_SPARE_REG5_OFFS                                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a058)
#define HWIO_TCSR_SPARE_REG5_RMSK                                                                                                                           0xff
#define HWIO_TCSR_SPARE_REG5_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG5_ADDR, HWIO_TCSR_SPARE_REG5_RMSK)
#define HWIO_TCSR_SPARE_REG5_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG5_ADDR, m)
#define HWIO_TCSR_SPARE_REG5_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG5_ADDR,v)
#define HWIO_TCSR_SPARE_REG5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG5_ADDR,m,v,HWIO_TCSR_SPARE_REG5_IN)
#define HWIO_TCSR_SPARE_REG5_SPARE_REG5_BMSK                                                                                                                0xff
#define HWIO_TCSR_SPARE_REG5_SPARE_REG5_SHFT                                                                                                                 0x0

#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000a05c)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a05c)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR, HWIO_TCSR_SPARE_QGIC_INTERRUPTS_RMSK)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR, m)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR,v)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR,m,v,HWIO_TCSR_SPARE_QGIC_INTERRUPTS_IN)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_SPARE_QGIC_INTERRUPTS_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_SPARE_QGIC_INTERRUPTS_SHFT                                                                                           0x0

#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000a070)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a070)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_RMSK                                                                                                                     0x1
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_UFS_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_UFS_SCM_FAULT_IRQ_BMSK                                                                                                   0x1
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_UFS_SCM_FAULT_IRQ_SHFT                                                                                                   0x0

#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000a074)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a074)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_RMSK                                                                                                                   0x1
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_SDCC5_SCM_FAULT_IRQ_BMSK                                                                                               0x1
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_SDCC5_SCM_FAULT_IRQ_SHFT                                                                                               0x0

#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000a078)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_OFFS                                                                                                            (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000a078)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_RMSK                                                                                                                   0x1
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_SDCC1_SCM_FAULT_IRQ_BMSK                                                                                               0x1
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_SDCC1_SCM_FAULT_IRQ_SHFT                                                                                               0x0

#define HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000b008)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b008)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_RMSK                                                                                                                     0x3
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR, HWIO_TCSR_PHSS_TEST_BUS_SEL_RMSK)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR, m)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR,v)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR,m,v,HWIO_TCSR_PHSS_TEST_BUS_SEL_IN)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_PHSS_TEST_BUS_SEL_BMSK                                                                                                   0x3
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_PHSS_TEST_BUS_SEL_SHFT                                                                                                   0x0

#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n)                                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000b040 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_OFFS(n)                                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b040 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_RMSK                                                                                                           0xfff
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_MAXn                                                                                                               1
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_6_IRQ_ENABLE_BMSK                                                                             0x800
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_6_IRQ_ENABLE_SHFT                                                                               0xb
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_5_IRQ_ENABLE_BMSK                                                                             0x400
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_5_IRQ_ENABLE_SHFT                                                                               0xa
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_4_IRQ_ENABLE_BMSK                                                                             0x200
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_4_IRQ_ENABLE_SHFT                                                                               0x9
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_3_IRQ_ENABLE_BMSK                                                                             0x100
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_3_IRQ_ENABLE_SHFT                                                                               0x8
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_2_IRQ_ENABLE_BMSK                                                                              0x80
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_2_IRQ_ENABLE_SHFT                                                                               0x7
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_1_IRQ_ENABLE_BMSK                                                                              0x40
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP2_UART_1_IRQ_ENABLE_SHFT                                                                               0x6
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_6_IRQ_ENABLE_BMSK                                                                              0x20
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_6_IRQ_ENABLE_SHFT                                                                               0x5
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_5_IRQ_ENABLE_BMSK                                                                              0x10
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_5_IRQ_ENABLE_SHFT                                                                               0x4
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_4_IRQ_ENABLE_BMSK                                                                               0x8
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_4_IRQ_ENABLE_SHFT                                                                               0x3
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_3_IRQ_ENABLE_BMSK                                                                               0x4
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_3_IRQ_ENABLE_SHFT                                                                               0x2
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_2_IRQ_ENABLE_BMSK                                                                               0x2
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_2_IRQ_ENABLE_SHFT                                                                               0x1
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_1_IRQ_ENABLE_BMSK                                                                               0x1
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP1_UART_1_IRQ_ENABLE_SHFT                                                                               0x0

#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_ADDR(n)                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000b080 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_OFFS(n)                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b080 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_RMSK                                                                                                             0xfff
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_MAXn                                                                                                                 1
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_6_IRQ_ENABLE_BMSK                                                                                 0x800
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_6_IRQ_ENABLE_SHFT                                                                                   0xb
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_5_IRQ_ENABLE_BMSK                                                                                 0x400
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_5_IRQ_ENABLE_SHFT                                                                                   0xa
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_4_IRQ_ENABLE_BMSK                                                                                 0x200
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_4_IRQ_ENABLE_SHFT                                                                                   0x9
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_3_IRQ_ENABLE_BMSK                                                                                 0x100
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_3_IRQ_ENABLE_SHFT                                                                                   0x8
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_2_IRQ_ENABLE_BMSK                                                                                  0x80
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_2_IRQ_ENABLE_SHFT                                                                                   0x7
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_1_IRQ_ENABLE_BMSK                                                                                  0x40
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP2_UART_1_IRQ_ENABLE_SHFT                                                                                   0x6
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_6_IRQ_ENABLE_BMSK                                                                                  0x20
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_6_IRQ_ENABLE_SHFT                                                                                   0x5
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_5_IRQ_ENABLE_BMSK                                                                                  0x10
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_5_IRQ_ENABLE_SHFT                                                                                   0x4
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_4_IRQ_ENABLE_BMSK                                                                                   0x8
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_4_IRQ_ENABLE_SHFT                                                                                   0x3
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_3_IRQ_ENABLE_BMSK                                                                                   0x4
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_3_IRQ_ENABLE_SHFT                                                                                   0x2
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_2_IRQ_ENABLE_BMSK                                                                                   0x2
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_2_IRQ_ENABLE_SHFT                                                                                   0x1
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_1_IRQ_ENABLE_BMSK                                                                                   0x1
#define HWIO_TCSR_PHSS_UART_SSC_INT_SEL_n_SSC_BLSP1_UART_1_IRQ_ENABLE_SHFT                                                                                   0x0

#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_ADDR(n)                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000b100 + 0x10 * (n))
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_OFFS(n)                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b100 + 0x10 * (n))
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_RMSK                                                                                                              0xfff
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_MAXn                                                                                                                  1
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_6_IRQ_ENABLE_BMSK                                                                                   0x800
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_6_IRQ_ENABLE_SHFT                                                                                     0xb
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_5_IRQ_ENABLE_BMSK                                                                                   0x400
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_5_IRQ_ENABLE_SHFT                                                                                     0xa
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_4_IRQ_ENABLE_BMSK                                                                                   0x200
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_4_IRQ_ENABLE_SHFT                                                                                     0x9
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_3_IRQ_ENABLE_BMSK                                                                                   0x100
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_3_IRQ_ENABLE_SHFT                                                                                     0x8
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_2_IRQ_ENABLE_BMSK                                                                                    0x80
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_2_IRQ_ENABLE_SHFT                                                                                     0x7
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_1_IRQ_ENABLE_BMSK                                                                                    0x40
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP2_QUP_1_IRQ_ENABLE_SHFT                                                                                     0x6
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_6_IRQ_ENABLE_BMSK                                                                                    0x20
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_6_IRQ_ENABLE_SHFT                                                                                     0x5
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_5_IRQ_ENABLE_BMSK                                                                                    0x10
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_5_IRQ_ENABLE_SHFT                                                                                     0x4
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_4_IRQ_ENABLE_BMSK                                                                                     0x8
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_4_IRQ_ENABLE_SHFT                                                                                     0x3
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_3_IRQ_ENABLE_BMSK                                                                                     0x4
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_3_IRQ_ENABLE_SHFT                                                                                     0x2
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_2_IRQ_ENABLE_BMSK                                                                                     0x2
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_2_IRQ_ENABLE_SHFT                                                                                     0x1
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_1_IRQ_ENABLE_BMSK                                                                                     0x1
#define HWIO_TCSR_PHSS_QUP_SSC_INT_SEL_n_SSC_BLSP1_QUP_1_IRQ_ENABLE_SHFT                                                                                     0x0

#define HWIO_TCSR_SSC_QUP_INT_SEL_ADDR                                                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000b800)
#define HWIO_TCSR_SSC_QUP_INT_SEL_OFFS                                                                                                                (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b800)
#define HWIO_TCSR_SSC_QUP_INT_SEL_RMSK                                                                                                                       0x7
#define HWIO_TCSR_SSC_QUP_INT_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SSC_QUP_INT_SEL_ADDR, HWIO_TCSR_SSC_QUP_INT_SEL_RMSK)
#define HWIO_TCSR_SSC_QUP_INT_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SSC_QUP_INT_SEL_ADDR, m)
#define HWIO_TCSR_SSC_QUP_INT_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SSC_QUP_INT_SEL_ADDR,v)
#define HWIO_TCSR_SSC_QUP_INT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SSC_QUP_INT_SEL_ADDR,m,v,HWIO_TCSR_SSC_QUP_INT_SEL_IN)
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_3_INT_ENABLE_BMSK                                                                                                  0x4
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_3_INT_ENABLE_SHFT                                                                                                  0x2
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_2_INT_ENABLE_BMSK                                                                                                  0x2
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_2_INT_ENABLE_SHFT                                                                                                  0x1
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_1_INT_ENABLE_BMSK                                                                                                  0x1
#define HWIO_TCSR_SSC_QUP_INT_SEL_SSC_QUP_1_INT_ENABLE_SHFT                                                                                                  0x0

#define HWIO_TCSR_SSC_UART_INT_SEL_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000bc00)
#define HWIO_TCSR_SSC_UART_INT_SEL_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000bc00)
#define HWIO_TCSR_SSC_UART_INT_SEL_RMSK                                                                                                                      0x7
#define HWIO_TCSR_SSC_UART_INT_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SSC_UART_INT_SEL_ADDR, HWIO_TCSR_SSC_UART_INT_SEL_RMSK)
#define HWIO_TCSR_SSC_UART_INT_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SSC_UART_INT_SEL_ADDR, m)
#define HWIO_TCSR_SSC_UART_INT_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SSC_UART_INT_SEL_ADDR,v)
#define HWIO_TCSR_SSC_UART_INT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SSC_UART_INT_SEL_ADDR,m,v,HWIO_TCSR_SSC_UART_INT_SEL_IN)
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_3_INT_ENABLE_BMSK                                                                                                0x4
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_3_INT_ENABLE_SHFT                                                                                                0x2
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_2_INT_ENABLE_BMSK                                                                                                0x2
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_2_INT_ENABLE_SHFT                                                                                                0x1
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_1_INT_ENABLE_BMSK                                                                                                0x1
#define HWIO_TCSR_SSC_UART_INT_SEL_SSC_UART_1_INT_ENABLE_SHFT                                                                                                0x0

#define HWIO_TCSR_TCSR_LDO_MISC_ADDR                                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000b22c)
#define HWIO_TCSR_TCSR_LDO_MISC_OFFS                                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b22c)
#define HWIO_TCSR_TCSR_LDO_MISC_RMSK                                                                                                                  0xffffffff
#define HWIO_TCSR_TCSR_LDO_MISC_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_LDO_MISC_ADDR, HWIO_TCSR_TCSR_LDO_MISC_RMSK)
#define HWIO_TCSR_TCSR_LDO_MISC_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_LDO_MISC_ADDR, m)
#define HWIO_TCSR_TCSR_LDO_MISC_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_LDO_MISC_ADDR,v)
#define HWIO_TCSR_TCSR_LDO_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_LDO_MISC_ADDR,m,v,HWIO_TCSR_TCSR_LDO_MISC_IN)
#define HWIO_TCSR_TCSR_LDO_MISC_TCSR_LDO_MISC_BMSK                                                                                                    0xffffffff
#define HWIO_TCSR_TCSR_LDO_MISC_TCSR_LDO_MISC_SHFT                                                                                                           0x0

#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000b244)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_OFFS                                                                                                         (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b244)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_RMSK                                                                                                         0xffffffff
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR, HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_RMSK)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR, m)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR,v)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR,m,v,HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_IN)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_TCSR_USB_PHY_VLS_CLAMP_BMSK                                                                                  0xffffffff
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_TCSR_USB_PHY_VLS_CLAMP_SHFT                                                                                         0x0

#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR                                                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000b204)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_OFFS                                                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b204)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_RMSK                                                                                                     0xffffffff
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_IN          \
        in_dword_masked(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR, HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_RMSK)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_INM(m)      \
        in_dword_masked(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR, m)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_OUT(v)      \
        out_dword(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR,v)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR,m,v,HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_IN)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_COPSS_USB_CONTROL_WITH_JDR_BMSK                                                                          0xffffffff
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_COPSS_USB_CONTROL_WITH_JDR_SHFT                                                                                 0x0

#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000b20c)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_OFFS                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b20c)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_RMSK                                                                                                             0x1
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_IN          \
        in_dword_masked(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR, HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_RMSK)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_INM(m)      \
        in_dword_masked(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR, m)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_OUT(v)      \
        out_dword(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR,v)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR,m,v,HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_IN)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_UFS_SATA_CTRL_SEL_BMSK                                                                                           0x1
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_UFS_SATA_CTRL_SEL_SHFT                                                                                           0x0

#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000b160 + 0x4 * (n))
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_OFFS(n)                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b160 + 0x4 * (n))
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_RMSK                                                                                                     0x8000007f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                                                             31
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_EN_BMSK                                                                              0x80000000
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_EN_SHFT                                                                                    0x1f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_SEL_BMSK                                                                                   0x7f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_SEL_SHFT                                                                                    0x0

#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000b360 + 0x4 * (n))
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_OFFS(n)                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b360 + 0x4 * (n))
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_RMSK                                                                                                 0x80000007
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                                                         31
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_EN_BMSK                                                                      0x80000000
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_EN_SHFT                                                                            0x1f
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_SEL_BMSK                                                                            0x7
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_SEL_SHFT                                                                            0x0

#define HWIO_TCSR_QPDI_DISABLE_CFG_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00001000)
#define HWIO_TCSR_QPDI_DISABLE_CFG_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00001000)
#define HWIO_TCSR_QPDI_DISABLE_CFG_RMSK                                                                                                                    0x303
#define HWIO_TCSR_QPDI_DISABLE_CFG_IN          \
        in_dword_masked(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR, HWIO_TCSR_QPDI_DISABLE_CFG_RMSK)
#define HWIO_TCSR_QPDI_DISABLE_CFG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR, m)
#define HWIO_TCSR_QPDI_DISABLE_CFG_OUT(v)      \
        out_dword(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR,v)
#define HWIO_TCSR_QPDI_DISABLE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR,m,v,HWIO_TCSR_QPDI_DISABLE_CFG_IN)
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_ACK_BMSK                                                                                                  0x200
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_ACK_SHFT                                                                                                    0x9
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_REQ_BMSK                                                                                                  0x100
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_REQ_SHFT                                                                                                    0x8
#define HWIO_TCSR_QPDI_DISABLE_CFG_SPMI_HANDSHAKE_DISABLE_BMSK                                                                                               0x2
#define HWIO_TCSR_QPDI_DISABLE_CFG_SPMI_HANDSHAKE_DISABLE_SHFT                                                                                               0x1
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_DISABLE_CFG_BMSK                                                                                                     0x1
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_DISABLE_CFG_SHFT                                                                                                     0x0

#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_ADDR                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00016000)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_OFFS                                                                                                        (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00016000)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_RMSK                                                                                                               0x3
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_IN          \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_ADDR, HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_RMSK)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_INM(m)      \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_ADDR, m)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_OUT(v)      \
        out_dword(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_ADDR,v)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_ADDR,m,v,HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_IN)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_TEST_EN_BMSK                                                                                                       0x2
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_TEST_EN_SHFT                                                                                                       0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_TEST_DATA_BMSK                                                                                                     0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_TEST_DATA_SHFT                                                                                                     0x0

#define HWIO_TCSR_LDO_SLEEP_CTRL_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000c000)
#define HWIO_TCSR_LDO_SLEEP_CTRL_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c000)
#define HWIO_TCSR_LDO_SLEEP_CTRL_RMSK                                                                                                                        0x1
#define HWIO_TCSR_LDO_SLEEP_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR, HWIO_TCSR_LDO_SLEEP_CTRL_RMSK)
#define HWIO_TCSR_LDO_SLEEP_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_SLEEP_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_SLEEP_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR,m,v,HWIO_TCSR_LDO_SLEEP_CTRL_IN)
#define HWIO_TCSR_LDO_SLEEP_CTRL_LDO_SLEEP_BMSK                                                                                                              0x1
#define HWIO_TCSR_LDO_SLEEP_CTRL_LDO_SLEEP_SHFT                                                                                                              0x0

#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000c004)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c004)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_RMSK                                                                                                                 0x1
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR, HWIO_TCSR_LDO_UPDATE_STATE_CTRL_RMSK)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR,m,v,HWIO_TCSR_LDO_UPDATE_STATE_CTRL_IN)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_LDO_UPDATE_STATE_BMSK                                                                                                0x1
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_LDO_UPDATE_STATE_SHFT                                                                                                0x0

#define HWIO_TCSR_LDO_OBIAS_CTRL_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000c008)
#define HWIO_TCSR_LDO_OBIAS_CTRL_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c008)
#define HWIO_TCSR_LDO_OBIAS_CTRL_RMSK                                                                                                                        0x1
#define HWIO_TCSR_LDO_OBIAS_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR, HWIO_TCSR_LDO_OBIAS_CTRL_RMSK)
#define HWIO_TCSR_LDO_OBIAS_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_OBIAS_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_OBIAS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR,m,v,HWIO_TCSR_LDO_OBIAS_CTRL_IN)
#define HWIO_TCSR_LDO_OBIAS_CTRL_LDO_OBIAS_ON_BMSK                                                                                                           0x1
#define HWIO_TCSR_LDO_OBIAS_CTRL_LDO_OBIAS_ON_SHFT                                                                                                           0x0

#define HWIO_TCSR_LDO_VREF_CONFIG_ADDR                                                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000c00c)
#define HWIO_TCSR_LDO_VREF_CONFIG_OFFS                                                                                                                (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c00c)
#define HWIO_TCSR_LDO_VREF_CONFIG_RMSK                                                                                                                       0xf
#define HWIO_TCSR_LDO_VREF_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CONFIG_ADDR, HWIO_TCSR_LDO_VREF_CONFIG_RMSK)
#define HWIO_TCSR_LDO_VREF_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_VREF_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_VREF_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_VREF_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_VREF_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_VREF_CONFIG_IN)
#define HWIO_TCSR_LDO_VREF_CONFIG_LDO_VREF_CONFIG_BMSK                                                                                                       0xf
#define HWIO_TCSR_LDO_VREF_CONFIG_LDO_VREF_CONFIG_SHFT                                                                                                       0x0

#define HWIO_TCSR_LDO_IB_CONFIG_ADDR                                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000c010)
#define HWIO_TCSR_LDO_IB_CONFIG_OFFS                                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c010)
#define HWIO_TCSR_LDO_IB_CONFIG_RMSK                                                                                                                         0x7
#define HWIO_TCSR_LDO_IB_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_IB_CONFIG_ADDR, HWIO_TCSR_LDO_IB_CONFIG_RMSK)
#define HWIO_TCSR_LDO_IB_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_IB_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_IB_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_IB_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_IB_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_IB_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_IB_CONFIG_IN)
#define HWIO_TCSR_LDO_IB_CONFIG_LDO_IB_CONFIG_BMSK                                                                                                           0x7
#define HWIO_TCSR_LDO_IB_CONFIG_LDO_IB_CONFIG_SHFT                                                                                                           0x0

#define HWIO_TCSR_LDO_BGC_CONFIG_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000c014)
#define HWIO_TCSR_LDO_BGC_CONFIG_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c014)
#define HWIO_TCSR_LDO_BGC_CONFIG_RMSK                                                                                                                        0x7
#define HWIO_TCSR_LDO_BGC_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_BGC_CONFIG_ADDR, HWIO_TCSR_LDO_BGC_CONFIG_RMSK)
#define HWIO_TCSR_LDO_BGC_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_BGC_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_BGC_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_BGC_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_BGC_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_BGC_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_BGC_CONFIG_IN)
#define HWIO_TCSR_LDO_BGC_CONFIG_LDO_BGC_BMSK                                                                                                                0x7
#define HWIO_TCSR_LDO_BGC_CONFIG_LDO_BGC_SHFT                                                                                                                0x0

#define HWIO_TCSR_LDO_VREF_CTRL_ADDR                                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000c018)
#define HWIO_TCSR_LDO_VREF_CTRL_OFFS                                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c018)
#define HWIO_TCSR_LDO_VREF_CTRL_RMSK                                                                                                                     0x10001
#define HWIO_TCSR_LDO_VREF_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CTRL_ADDR, HWIO_TCSR_LDO_VREF_CTRL_RMSK)
#define HWIO_TCSR_LDO_VREF_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_VREF_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_VREF_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_VREF_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_VREF_CTRL_ADDR,m,v,HWIO_TCSR_LDO_VREF_CTRL_IN)
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_OVR_BMSK                                                                                                    0x10000
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_OVR_SHFT                                                                                                       0x10
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_SW_BMSK                                                                                                         0x1
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_SW_SHFT                                                                                                         0x0

#define HWIO_TCSR_LDO_LD_EN_ADDR                                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000c01c)
#define HWIO_TCSR_LDO_LD_EN_OFFS                                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c01c)
#define HWIO_TCSR_LDO_LD_EN_RMSK                                                                                                                      0x80000000
#define HWIO_TCSR_LDO_LD_EN_IN          \
        in_dword_masked(HWIO_TCSR_LDO_LD_EN_ADDR, HWIO_TCSR_LDO_LD_EN_RMSK)
#define HWIO_TCSR_LDO_LD_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_LD_EN_ADDR, m)
#define HWIO_TCSR_LDO_LD_EN_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_LD_EN_ADDR,v)
#define HWIO_TCSR_LDO_LD_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_LD_EN_ADDR,m,v,HWIO_TCSR_LDO_LD_EN_IN)
#define HWIO_TCSR_LDO_LD_EN_LDO_LD_EN_BMSK                                                                                                            0x80000000
#define HWIO_TCSR_LDO_LD_EN_LDO_LD_EN_SHFT                                                                                                                  0x1f

#define HWIO_TCSR_LDO_LD_CTRL_ADDR                                                                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0000c020)
#define HWIO_TCSR_LDO_LD_CTRL_OFFS                                                                                                                    (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c020)
#define HWIO_TCSR_LDO_LD_CTRL_RMSK                                                                                                                      0xff00ff
#define HWIO_TCSR_LDO_LD_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_LD_CTRL_ADDR, HWIO_TCSR_LDO_LD_CTRL_RMSK)
#define HWIO_TCSR_LDO_LD_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_LD_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_LD_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_LD_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_LD_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_LD_CTRL_ADDR,m,v,HWIO_TCSR_LDO_LD_CTRL_IN)
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_MSB_BMSK                                                                                                           0xff0000
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_MSB_SHFT                                                                                                               0x10
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_LSB_BMSK                                                                                                               0xff
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_LSB_SHFT                                                                                                                0x0

#define HWIO_TCSR_LDO_OSC_RESETB_ADDR                                                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000c024)
#define HWIO_TCSR_LDO_OSC_RESETB_OFFS                                                                                                                 (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c024)
#define HWIO_TCSR_LDO_OSC_RESETB_RMSK                                                                                                                 0x80000000
#define HWIO_TCSR_LDO_OSC_RESETB_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OSC_RESETB_ADDR, HWIO_TCSR_LDO_OSC_RESETB_RMSK)
#define HWIO_TCSR_LDO_OSC_RESETB_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OSC_RESETB_ADDR, m)
#define HWIO_TCSR_LDO_OSC_RESETB_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OSC_RESETB_ADDR,v)
#define HWIO_TCSR_LDO_OSC_RESETB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OSC_RESETB_ADDR,m,v,HWIO_TCSR_LDO_OSC_RESETB_IN)
#define HWIO_TCSR_LDO_OSC_RESETB_LDO_OSC_RESETB_BMSK                                                                                                  0x80000000
#define HWIO_TCSR_LDO_OSC_RESETB_LDO_OSC_RESETB_SHFT                                                                                                        0x1f

#define HWIO_TCSR_LDO_OSC_CTRL_ADDR                                                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000c028)
#define HWIO_TCSR_LDO_OSC_CTRL_OFFS                                                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c028)
#define HWIO_TCSR_LDO_OSC_CTRL_RMSK                                                                                                                          0x3
#define HWIO_TCSR_LDO_OSC_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OSC_CTRL_ADDR, HWIO_TCSR_LDO_OSC_CTRL_RMSK)
#define HWIO_TCSR_LDO_OSC_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OSC_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_OSC_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OSC_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_OSC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OSC_CTRL_ADDR,m,v,HWIO_TCSR_LDO_OSC_CTRL_IN)
#define HWIO_TCSR_LDO_OSC_CTRL_LDO_OSC_CTRL_BMSK                                                                                                             0x3
#define HWIO_TCSR_LDO_OSC_CTRL_LDO_OSC_CTRL_SHFT                                                                                                             0x0

#define HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR                                                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000c02c)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_OFFS                                                                                                                (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c02c)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_RMSK                                                                                                                0x80000000
#define HWIO_TCSR_LDO_DFT_EN_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR, HWIO_TCSR_LDO_DFT_EN_CTRL_RMSK)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR,m,v,HWIO_TCSR_LDO_DFT_EN_CTRL_IN)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_LDO_DFT_EN_BMSK                                                                                                     0x80000000
#define HWIO_TCSR_LDO_DFT_EN_CTRL_LDO_DFT_EN_SHFT                                                                                                           0x1f

#define HWIO_TCSR_LDO_DFT_CTRL_ADDR                                                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000c030)
#define HWIO_TCSR_LDO_DFT_CTRL_OFFS                                                                                                                   (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000c030)
#define HWIO_TCSR_LDO_DFT_CTRL_RMSK                                                                                                                          0x7
#define HWIO_TCSR_LDO_DFT_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_DFT_CTRL_ADDR, HWIO_TCSR_LDO_DFT_CTRL_RMSK)
#define HWIO_TCSR_LDO_DFT_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_DFT_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_DFT_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_DFT_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_DFT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_DFT_CTRL_ADDR,m,v,HWIO_TCSR_LDO_DFT_CTRL_IN)
#define HWIO_TCSR_LDO_DFT_CTRL_LDO_DFT_CONFIG_BMSK                                                                                                           0x7
#define HWIO_TCSR_LDO_DFT_CTRL_LDO_DFT_CONFIG_SHFT                                                                                                           0x0

#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000d000)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d000)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDSSC_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDSSC_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDSSC_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_COMPILER_VDDSSC_ACC_0_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_0_COMPILER_VDDSSC_ACC_0_SHFT                                                                                           0x0

#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000d004)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d004)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDSSC_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDSSC_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDSSC_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_COMPILER_VDDSSC_ACC_1_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_COMPILER_VDDSSC_ACC_1_COMPILER_VDDSSC_ACC_1_SHFT                                                                                           0x0

#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR                                                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000d080)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_OFFS                                                                                                           (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d080)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_RMSK                                                                                                           0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDCX_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_COMPILER_VDDCX_ACC_0_BMSK                                                                                      0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_COMPILER_VDDCX_ACC_0_SHFT                                                                                             0x0

#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR                                                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000d084)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_OFFS                                                                                                           (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d084)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_RMSK                                                                                                           0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDCX_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_COMPILER_VDDCX_ACC_1_BMSK                                                                                      0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_COMPILER_VDDCX_ACC_1_SHFT                                                                                             0x0

#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000d100)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d100)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDGFX_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_COMPILER_VDDGFX_ACC_0_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_COMPILER_VDDGFX_ACC_0_SHFT                                                                                           0x0

#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000d104)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d104)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDGFX_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_COMPILER_VDDGFX_ACC_1_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_COMPILER_VDDGFX_ACC_1_SHFT                                                                                           0x0

#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000d110)
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_OFFS                                                                     (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d110)
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_RMSK                                                                           0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_ADDR, HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_BMSK                0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_CUSTOM_ACC_QCRF6421_162RBYNGDB00_256X128_1_CUSTOM6P_VDDGFX_SHFT                 0x0

#define HWIO_TCSR_MEM_ARRY_STBY_ADDR                                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000d180)
#define HWIO_TCSR_MEM_ARRY_STBY_OFFS                                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000d180)
#define HWIO_TCSR_MEM_ARRY_STBY_RMSK                                                                                                                         0x1
#define HWIO_TCSR_MEM_ARRY_STBY_IN          \
        in_dword_masked(HWIO_TCSR_MEM_ARRY_STBY_ADDR, HWIO_TCSR_MEM_ARRY_STBY_RMSK)
#define HWIO_TCSR_MEM_ARRY_STBY_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_ARRY_STBY_ADDR, m)
#define HWIO_TCSR_MEM_ARRY_STBY_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_ARRY_STBY_ADDR,v)
#define HWIO_TCSR_MEM_ARRY_STBY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_ARRY_STBY_ADDR,m,v,HWIO_TCSR_MEM_ARRY_STBY_IN)
#define HWIO_TCSR_MEM_ARRY_STBY_MEM_ARRY_STBY_N_BMSK                                                                                                         0x1
#define HWIO_TCSR_MEM_ARRY_STBY_MEM_ARRY_STBY_N_SHFT                                                                                                         0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR                                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000e004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_OFFS                                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000e004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_RMSK                                                                                                                     0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDCX_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDCX_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_MEM_SVS_SEL_VDDCX_BMSK                                                                                                   0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_MEM_SVS_SEL_VDDCX_SHFT                                                                                                   0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR                                                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0000f004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_OFFS                                                                                                             (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000f004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_RMSK                                                                                                                    0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDGFX_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDGFX_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_MEM_SVS_SEL_VDDGFX_BMSK                                                                                                 0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_MEM_SVS_SEL_VDDGFX_SHFT                                                                                                 0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_ADDR                                                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00010000)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_OFFS                                                                                                             (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00010000)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_RMSK                                                                                                                    0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDSSC_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDSSC_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDSSC_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDSSC_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDSSC_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDSSC_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_MEM_SVS_SEL_VDDSSC_BMSK                                                                                                 0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDSSC_MEM_SVS_SEL_VDDSSC_SHFT                                                                                                 0x0

#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR                                                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000b220)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_OFFS                                                                                                           (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b220)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_RMSK                                                                                                                 0x1f
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_IN          \
        in_dword_masked(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR, HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_RMSK)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR,m,v,HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_IN)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_DDR_SS_DEBUG_BUS_SEL_BMSK                                                                                            0x1f
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_DDR_SS_DEBUG_BUS_SEL_SHFT                                                                                             0x0

#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR                                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00011000)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_OFFS                                                                                              (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00011000)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_RMSK                                                                                                     0x1
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_IN          \
        in_dword_masked(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR, HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_RMSK)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_INM(m)      \
        in_dword_masked(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR, m)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_OUT(v)      \
        out_dword(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR,v)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR,m,v,HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_IN)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_VSENSE_CONTROLLER_ENABLE_REGISTER_BMSK                                                                   0x1
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_VSENSE_CONTROLLER_ENABLE_REGISTER_SHFT                                                                   0x0

#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR                                                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00012000)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_OFFS                                                                                                      (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00012000)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_RMSK                                                                                                      0xffffffff
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR, HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_RMSK)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR, m)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR,v)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR,m,v,HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_IN)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_TCSR_RESET_DEBUG_SW_ENTRY_BMSK                                                                            0xffffffff
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_TCSR_RESET_DEBUG_SW_ENTRY_SHFT                                                                                   0x0

#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR                                                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00013000)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OFFS                                                                                                          (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00013000)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_RMSK                                                                                                          0xffffffff
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR, HWIO_TCSR_TCSR_BOOT_MISC_DETECT_RMSK)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR, m)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR,v)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR,m,v,HWIO_TCSR_TCSR_BOOT_MISC_DETECT_IN)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_TCSR_BOOT_MISC_DETECT_BMSK                                                                                    0xffffffff
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_TCSR_BOOT_MISC_DETECT_SHFT                                                                                           0x0

#define HWIO_TCSR_TZ_WONCE_n_ADDR(n)                                                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00014000 + 0x4 * (n))
#define HWIO_TCSR_TZ_WONCE_n_OFFS(n)                                                                                                                  (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00014000 + 0x4 * (n))
#define HWIO_TCSR_TZ_WONCE_n_RMSK                                                                                                                     0xffffffff
#define HWIO_TCSR_TZ_WONCE_n_MAXn                                                                                                                             15
#define HWIO_TCSR_TZ_WONCE_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TZ_WONCE_n_ADDR(n), HWIO_TCSR_TZ_WONCE_n_RMSK)
#define HWIO_TCSR_TZ_WONCE_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TZ_WONCE_n_ADDR(n), mask)
#define HWIO_TCSR_TZ_WONCE_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TZ_WONCE_n_ADDR(n),val)
#define HWIO_TCSR_TZ_WONCE_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TZ_WONCE_n_ADDR(n),mask,val,HWIO_TCSR_TZ_WONCE_n_INI(n))
#define HWIO_TCSR_TZ_WONCE_n_TZ_WONCE_ADDRESS_BMSK                                                                                                    0xffffffff
#define HWIO_TCSR_TZ_WONCE_n_TZ_WONCE_ADDRESS_SHFT                                                                                                           0x0

#define HWIO_TCSR_QREFS_RPT_CONFIG_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00015000)
#define HWIO_TCSR_QREFS_RPT_CONFIG_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00015000)
#define HWIO_TCSR_QREFS_RPT_CONFIG_RMSK                                                                                                                   0xffff
#define HWIO_TCSR_QREFS_RPT_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR, HWIO_TCSR_QREFS_RPT_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_RPT_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_RPT_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_RPT_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_RPT_CONFIG_IN)
#define HWIO_TCSR_QREFS_RPT_CONFIG_QREFS_RPT_CONFIG_BUS_SELECT_BMSK                                                                                       0xffff
#define HWIO_TCSR_QREFS_RPT_CONFIG_QREFS_RPT_CONFIG_BUS_SELECT_SHFT                                                                                          0x0

#define HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR                                                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00015004)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_OFFS                                                                                                             (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x00015004)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_RMSK                                                                                                                 0xffff
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR, HWIO_TCSR_QREFS_TXVBG_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_TXVBG_CONFIG_IN)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_QREFS_TXVBG_CONFIG_BMSK                                                                                              0xffff
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_QREFS_TXVBG_CONFIG_SHFT                                                                                                 0x0

#define HWIO_TCSR_TIC_CNOC_NS_ADDR                                                                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e0)
#define HWIO_TCSR_TIC_CNOC_NS_OFFS                                                                                                                    (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b3e0)
#define HWIO_TCSR_TIC_CNOC_NS_RMSK                                                                                                                           0x1
#define HWIO_TCSR_TIC_CNOC_NS_IN          \
        in_dword_masked(HWIO_TCSR_TIC_CNOC_NS_ADDR, HWIO_TCSR_TIC_CNOC_NS_RMSK)
#define HWIO_TCSR_TIC_CNOC_NS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIC_CNOC_NS_ADDR, m)
#define HWIO_TCSR_TIC_CNOC_NS_OUT(v)      \
        out_dword(HWIO_TCSR_TIC_CNOC_NS_ADDR,v)
#define HWIO_TCSR_TIC_CNOC_NS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIC_CNOC_NS_ADDR,m,v,HWIO_TCSR_TIC_CNOC_NS_IN)
#define HWIO_TCSR_TIC_CNOC_NS_TIC_CNOC_NS_BMSK                                                                                                               0x1
#define HWIO_TCSR_TIC_CNOC_NS_TIC_CNOC_NS_SHFT                                                                                                               0x0

#define HWIO_TCSR_CONN_BOX_SPARE_0_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e4)
#define HWIO_TCSR_CONN_BOX_SPARE_0_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b3e4)
#define HWIO_TCSR_CONN_BOX_SPARE_0_RMSK                                                                                                               0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_0_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR, HWIO_TCSR_CONN_BOX_SPARE_0_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_0_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_0_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_0_CONN_BOX_SPARE_0_BMSK                                                                                              0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_0_CONN_BOX_SPARE_0_SHFT                                                                                                     0x0

#define HWIO_TCSR_CONN_BOX_SPARE_1_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e8)
#define HWIO_TCSR_CONN_BOX_SPARE_1_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b3e8)
#define HWIO_TCSR_CONN_BOX_SPARE_1_RMSK                                                                                                               0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_1_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR, HWIO_TCSR_CONN_BOX_SPARE_1_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_1_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_1_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_1_CONN_BOX_SPARE_1_BMSK                                                                                              0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_1_CONN_BOX_SPARE_1_SHFT                                                                                                     0x0

#define HWIO_TCSR_CONN_BOX_SPARE_2_ADDR                                                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3ec)
#define HWIO_TCSR_CONN_BOX_SPARE_2_OFFS                                                                                                               (TCSR_TCSR_REGS_REG_BASE_OFFS + 0x0000b3ec)
#define HWIO_TCSR_CONN_BOX_SPARE_2_RMSK                                                                                                               0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_2_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR, HWIO_TCSR_CONN_BOX_SPARE_2_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_2_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_2_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_2_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_2_CONN_BOX_SPARE_2_BMSK                                                                                              0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_2_CONN_BOX_SPARE_2_SHFT                                                                                                     0x0


#endif /* __HALCLKHWIOASM_H__ */
