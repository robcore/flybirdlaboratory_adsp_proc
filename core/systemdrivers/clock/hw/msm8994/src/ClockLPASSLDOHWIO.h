#ifndef __CLOCKLPASSLDOHWIO_H__
#define __CLOCKLPASSLDOHWIO_H__
/*
===========================================================================
*/
/**
  @file ClockLPASSLDOHWIO.h 
  
  The file contains the resource definitions for LDO voltage scaling on
  the Low Power Audio Subsystem processor for 9x25.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8994/src/ClockLPASSLDOHWIO.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/12/12   dcf     Created for LPASS on 8974.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include <HALhwio.h>

/*=========================================================================
      Type Definitions
==========================================================================*/

extern uint32                      Clock_nHWIOBaseLPASS;
#define LPASS_BASE                 Clock_nHWIOBaseLPASS

extern uint32                      Clock_nHWIOBaseSecurity;
#define SECURITY_CONTROL_BASE      Clock_nHWIOBaseSecurity


/*=========================================================================
      Macros
==========================================================================*/


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

#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR                                       (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_OFFS                                       (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK                                       0xfff03fff
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                         0xfff00000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                               0x14
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_ON_VDDCX_BMSK                             0x2000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_ON_VDDCX_SHFT                                0xd
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_APU_PRESENT_BMSK                               0x1000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_APU_PRESENT_SHFT                                  0xc
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                0x800
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                  0xb
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                0x400
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                  0xa
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                   0x200
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                     0x9
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                0x100
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                   0xf0
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                    0x4
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                      0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                      0x0

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

#define HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR                                    (LPASS_QDSP6SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OFFS                                    (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK                                           0xf
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STATERET_CTL_IN)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                 0x8
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                 0x3
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_SHFT                                      0x0

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

#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR                                (LPASS_QDSP6SS_PUB_REG_BASE      + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_OFFS                                (LPASS_QDSP6SS_PUB_REG_BASE_OFFS + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK                                      0x3f
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_BMSK                        0x3e
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_SHFT                         0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_SHFT                                0x0

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

/*----------------------------------------------------------------------------
 * MODULE: SECURITY_CONTROL_CORE
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_CORE_REG_BASE                                                                             (SECURITY_CONTROL_BASE      + 0x00000000)
#define SECURITY_CONTROL_CORE_REG_BASE_OFFS                                                                        0x00000000

#define HWIO_QFPROM_RAW_ACC_PRIVATEn_ADDR(n)                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_OFFS(n)                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_RMSK                                                                          0xffffffff
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_MAXn                                                                                  39
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_ACC_PRIVATEn_ADDR(n), HWIO_QFPROM_RAW_ACC_PRIVATEn_RMSK)
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_ACC_PRIVATEn_ADDR(n), mask)
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_ACC_PRIVATE_BMSK                                                              0xffffffff
#define HWIO_QFPROM_RAW_ACC_PRIVATEn_ACC_PRIVATE_SHFT                                                                     0x0

#define HWIO_QFPROM_RAW_JTAG_ID_LSB_ADDR                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000a0)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_OFFS                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000a0)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_RMSK                                                                            0xfffffff
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_JTAG_ID_LSB_ADDR, HWIO_QFPROM_RAW_JTAG_ID_LSB_RMSK)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_JTAG_ID_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_JTAG_ID_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_JTAG_ID_LSB_ADDR,m,v,HWIO_QFPROM_RAW_JTAG_ID_LSB_IN)
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_FEATURE_ID_BMSK                                                                 0xff00000
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_FEATURE_ID_SHFT                                                                      0x14
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_JTAG_ID_BMSK                                                                      0xfffff
#define HWIO_QFPROM_RAW_JTAG_ID_LSB_JTAG_ID_SHFT                                                                          0x0

#define HWIO_QFPROM_RAW_JTAG_ID_MSB_ADDR                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000a4)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_OFFS                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000a4)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_JTAG_ID_MSB_ADDR, HWIO_QFPROM_RAW_JTAG_ID_MSB_RMSK)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_JTAG_ID_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_JTAG_ID_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_JTAG_ID_MSB_ADDR,m,v,HWIO_QFPROM_RAW_JTAG_ID_MSB_IN)
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_QFPROM_RAW_JTAG_ID_MSB_BMSK                                                    0xffffffff
#define HWIO_QFPROM_RAW_JTAG_ID_MSB_QFPROM_RAW_JTAG_ID_MSB_SHFT                                                           0x0

#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000a8)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000a8)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ADDR, HWIO_QFPROM_RAW_RD_WR_PERM_LSB_RMSK)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ADDR,m,v,HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IN)
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_PRIV_KEY1_BMSK                                                         0x80000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_PRIV_KEY1_SHFT                                                               0x1f
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_PRIV_KEY0_BMSK                                                         0x40000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_PRIV_KEY0_SHFT                                                               0x1e
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_HDCP_KEY_BMSK                                                               0x20000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_HDCP_KEY_SHFT                                                                     0x1d
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE28_BMSK                                                                0x10000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE28_SHFT                                                                      0x1c
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE27_BMSK                                                                 0x8000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE27_SHFT                                                                      0x1b
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_USB_VID_PID_BMSK                                                             0x4000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_USB_VID_PID_SHFT                                                                  0x1a
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_QC_SEC_BOOT_BMSK                                                             0x2000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_QC_SEC_BOOT_SHFT                                                                  0x19
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_SEC_BOOT_BMSK                                                            0x1000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_SEC_BOOT_SHFT                                                                 0x18
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_PK_HASH_BMSK                                                              0x800000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_PK_HASH_SHFT                                                                  0x17
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                                   0x400000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                                       0x16
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                                   0x200000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                                       0x15
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_BOOT_ROM_PATCH_BMSK                                                           0x100000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_BOOT_ROM_PATCH_SHFT                                                               0x14
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE19_BMSK                                                                   0x80000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SPARE19_SHFT                                                                      0x13
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SERIAL_NUM_BMSK                                                                0x40000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_SERIAL_NUM_SHFT                                                                   0x12
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_KEY_BMSK                                                                  0x20000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CUST_KEY_SHFT                                                                     0x11
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_INTAGLIO_GLUEBIT_BMSK                                                          0x10000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_INTAGLIO_GLUEBIT_SHFT                                                             0x10
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_FEC_EN_BMSK                                                                     0x8000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_FEC_EN_SHFT                                                                        0xf
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CALIB_BMSK                                                                      0x4000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_CALIB_SHFT                                                                         0xe
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MEM_ACCEL_BMSK                                                                  0x2000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MEM_ACCEL_SHFT                                                                     0xd
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_DEBUG_KEY_BMSK                                                                  0x1000
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_DEBUG_KEY_SHFT                                                                     0xc
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MEM_REDUN_BMSK                                                                   0x800
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MEM_REDUN_SHFT                                                                     0xb
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_FEAT_CONFIG_BMSK                                                                 0x400
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_FEAT_CONFIG_SHFT                                                                   0xa
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_CONFIG_BMSK                                                                  0x200
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_OEM_CONFIG_SHFT                                                                    0x9
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN2_BMSK                                                                   0x100
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN2_SHFT                                                                     0x8
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN1_BMSK                                                                    0x80
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN1_SHFT                                                                     0x7
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN0_BMSK                                                                    0x40
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_IMEI_ESN0_SHFT                                                                     0x6
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MSA_ANTI_ROLLBACK_BMSK                                                            0x20
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_MSA_ANTI_ROLLBACK_SHFT                                                             0x5
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_AP_ANTI_ROLLBACK_BMSK                                                             0x10
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_AP_ANTI_ROLLBACK_SHFT                                                              0x4
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_PTE_BMSK                                                                           0x8
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_PTE_SHFT                                                                           0x3
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_RD_WR_PERM_BMSK                                                                    0x4
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_RD_WR_PERM_SHFT                                                                    0x2
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_JTAG_ID_BMSK                                                                       0x2
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_JTAG_ID_SHFT                                                                       0x1
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ACC_PRIVATE_BMSK                                                                   0x1
#define HWIO_QFPROM_RAW_RD_WR_PERM_LSB_ACC_PRIVATE_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000ac)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000ac)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ADDR, HWIO_QFPROM_RAW_RD_WR_PERM_MSB_RMSK)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ADDR,m,v,HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IN)
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_PRIV_KEY1_BMSK                                                         0x80000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_PRIV_KEY1_SHFT                                                               0x1f
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_PRIV_KEY0_BMSK                                                         0x40000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_PRIV_KEY0_SHFT                                                               0x1e
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_HDCP_KEY_BMSK                                                               0x20000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_HDCP_KEY_SHFT                                                                     0x1d
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE28_BMSK                                                                0x10000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE28_SHFT                                                                      0x1c
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE27_BMSK                                                                 0x8000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE27_SHFT                                                                      0x1b
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_USB_VID_PID_BMSK                                                             0x4000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_USB_VID_PID_SHFT                                                                  0x1a
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_QC_SEC_BOOT_BMSK                                                             0x2000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_QC_SEC_BOOT_SHFT                                                                  0x19
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_SEC_BOOT_BMSK                                                            0x1000000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_SEC_BOOT_SHFT                                                                 0x18
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_PK_HASH_BMSK                                                              0x800000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_PK_HASH_SHFT                                                                  0x17
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SEC_KEY_DERIVATION_KEY_BMSK                                                   0x400000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SEC_KEY_DERIVATION_KEY_SHFT                                                       0x16
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_PRI_KEY_DERIVATION_KEY_BMSK                                                   0x200000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_PRI_KEY_DERIVATION_KEY_SHFT                                                       0x15
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_BOOT_ROM_PATCH_BMSK                                                           0x100000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_BOOT_ROM_PATCH_SHFT                                                               0x14
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE19_BMSK                                                                   0x80000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SPARE19_SHFT                                                                      0x13
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SERIAL_NUM_BMSK                                                                0x40000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_SERIAL_NUM_SHFT                                                                   0x12
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_KEY_BMSK                                                                  0x20000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CUST_KEY_SHFT                                                                     0x11
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_INTAGLIO_GLUEBIT_BMSK                                                          0x10000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_INTAGLIO_GLUEBIT_SHFT                                                             0x10
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_FEC_EN_BMSK                                                                     0x8000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_FEC_EN_SHFT                                                                        0xf
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CALIB_BMSK                                                                      0x4000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_CALIB_SHFT                                                                         0xe
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MEM_ACCEL_BMSK                                                                  0x2000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MEM_ACCEL_SHFT                                                                     0xd
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_DEBUG_KEY_BMSK                                                                  0x1000
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_DEBUG_KEY_SHFT                                                                     0xc
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MEM_REDUN_BMSK                                                                   0x800
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MEM_REDUN_SHFT                                                                     0xb
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_FEAT_CONFIG_BMSK                                                                 0x400
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_FEAT_CONFIG_SHFT                                                                   0xa
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_CONFIG_BMSK                                                                  0x200
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_OEM_CONFIG_SHFT                                                                    0x9
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN2_BMSK                                                                   0x100
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN2_SHFT                                                                     0x8
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN1_BMSK                                                                    0x80
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN1_SHFT                                                                     0x7
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN0_BMSK                                                                    0x40
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_IMEI_ESN0_SHFT                                                                     0x6
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MSA_ANTI_ROLLBACK_BMSK                                                            0x20
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_MSA_ANTI_ROLLBACK_SHFT                                                             0x5
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_AP_ANTI_ROLLBACK_BMSK                                                             0x10
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_AP_ANTI_ROLLBACK_SHFT                                                              0x4
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_PTE_BMSK                                                                           0x8
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_PTE_SHFT                                                                           0x3
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_RD_WR_PERM_BMSK                                                                    0x4
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_RD_WR_PERM_SHFT                                                                    0x2
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_JTAG_ID_BMSK                                                                       0x2
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_JTAG_ID_SHFT                                                                       0x1
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ACC_PRIVATE_BMSK                                                                   0x1
#define HWIO_QFPROM_RAW_RD_WR_PERM_MSB_ACC_PRIVATE_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_PTE_LSB_ADDR                                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000b0)
#define HWIO_QFPROM_RAW_PTE_LSB_OFFS                                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000b0)
#define HWIO_QFPROM_RAW_PTE_LSB_RMSK                                                                               0xffffffff
#define HWIO_QFPROM_RAW_PTE_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_LSB_ADDR, HWIO_QFPROM_RAW_PTE_LSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_LSB_IN)
#define HWIO_QFPROM_RAW_PTE_LSB_PTE_DATA0_BMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_PTE_LSB_PTE_DATA0_SHFT                                                                            0x0

#define HWIO_QFPROM_RAW_PTE_MSB_ADDR                                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000b4)
#define HWIO_QFPROM_RAW_PTE_MSB_OFFS                                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000b4)
#define HWIO_QFPROM_RAW_PTE_MSB_RMSK                                                                               0xffffffff
#define HWIO_QFPROM_RAW_PTE_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_MSB_ADDR, HWIO_QFPROM_RAW_PTE_MSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_MSB_IN)
#define HWIO_QFPROM_RAW_PTE_MSB_PTE_DATA1_BMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_PTE_MSB_PTE_DATA1_SHFT                                                                            0x0

#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000b8)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000b8)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_RMSK                                                             0xffffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_TZ_BMSK                                                          0xffff0000
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_TZ_SHFT                                                                0x10
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_SBL1_BMSK                                                            0xffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_LSB_SBL1_SHFT                                                               0x0

#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000bc)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000bc)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_RMSK                                                             0xffffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_PIL_SUBSYSTEM_31_0_BMSK                                          0xffffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW0_MSB_PIL_SUBSYSTEM_31_0_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000c0)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000c0)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_RMSK                                                             0xffffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_APPSBL0_BMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_LSB_APPSBL0_SHFT                                                            0x0

#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000c4)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000c4)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_RMSK                                                              0x3ffffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_RPM_BMSK                                                          0x3fc0000
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_RPM_SHFT                                                               0x12
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_APPSBL1_BMSK                                                        0x3ffff
#define HWIO_QFPROM_RAW_AP_ANTI_ROLLBACK_ROW1_MSB_APPSBL1_SHFT                                                            0x0

#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000c8)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000c8)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_ADDR, HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_RMSK)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_ADDR,m,v,HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_IN)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_MSS_BMSK                                                             0xffff0000
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_MSS_SHFT                                                                   0x10
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_MBA_BMSK                                                                 0xffff
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_LSB_MBA_SHFT                                                                    0x0

#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000cc)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000cc)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_ADDR, HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_RMSK)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_ADDR,m,v,HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_IN)
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_BMSK                                0xffffffff
#define HWIO_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_QFPROM_RAW_MSA_ANTI_ROLLBACK_MSB_SHFT                                       0x0

#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000d0)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000d0)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN0_LSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN0_LSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN0_LSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS2_OFFSET_BMSK                                                           0xf0000000
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS2_OFFSET_SHFT                                                                 0x1c
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS1_OFFSET_BMSK                                                            0xf000000
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS1_OFFSET_SHFT                                                                 0x18
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS0_OFFSET_BMSK                                                             0xf00000
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS0_OFFSET_SHFT                                                                 0x14
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS_BASE1_BMSK                                                                0xffc00
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS_BASE1_SHFT                                                                    0xa
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS_BASE0_BMSK                                                                  0x3ff
#define HWIO_QFPROM_RAW_IMEI_ESN0_LSB_TSENS_BASE0_SHFT                                                                    0x0

#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000d4)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000d4)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN0_MSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN0_MSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN0_MSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS10_OFFSET_BMSK                                                          0xf0000000
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS10_OFFSET_SHFT                                                                0x1c
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS9_OFFSET_BMSK                                                            0xf000000
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS9_OFFSET_SHFT                                                                 0x18
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS8_OFFSET_BMSK                                                             0xf00000
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS8_OFFSET_SHFT                                                                 0x14
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS7_OFFSET_BMSK                                                              0xf0000
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS7_OFFSET_SHFT                                                                 0x10
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS6_OFFSET_BMSK                                                               0xf000
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS6_OFFSET_SHFT                                                                  0xc
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS5_OFFSET_BMSK                                                                0xf00
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS5_OFFSET_SHFT                                                                  0x8
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS4_OFFSET_BMSK                                                                 0xf0
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS4_OFFSET_SHFT                                                                  0x4
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS3_OFFSET_BMSK                                                                  0xf
#define HWIO_QFPROM_RAW_IMEI_ESN0_MSB_TSENS3_OFFSET_SHFT                                                                  0x0

#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000d8)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000d8)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN1_LSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN1_LSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN1_LSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TXDAC1_CAL_0_BMSK                                                            0x80000000
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TXDAC1_CAL_0_SHFT                                                                  0x1f
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TXDAC0_CAL_BMSK                                                              0x7f800000
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TXDAC0_CAL_SHFT                                                                    0x17
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS_CAL_SEL_BMSK                                                             0x700000
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS_CAL_SEL_SHFT                                                                 0x14
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS15_OFFSET_BMSK                                                             0xf0000
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS15_OFFSET_SHFT                                                                0x10
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS14_OFFSET_BMSK                                                              0xf000
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS14_OFFSET_SHFT                                                                 0xc
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS13_OFFSET_BMSK                                                               0xf00
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS13_OFFSET_SHFT                                                                 0x8
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS12_OFFSET_BMSK                                                                0xf0
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS12_OFFSET_SHFT                                                                 0x4
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS11_OFFSET_BMSK                                                                 0xf
#define HWIO_QFPROM_RAW_IMEI_ESN1_LSB_TSENS11_OFFSET_SHFT                                                                 0x0

#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000dc)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000dc)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN1_MSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN1_MSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN1_MSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_SPARE0_BMSK                                                                  0xfffc0000
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_SPARE0_SHFT                                                                        0x12
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_VCM_BMSK                                                               0x30000
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_VCM_SHFT                                                                  0x10
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_LDO_BMSK                                                                0xc000
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_LDO_SHFT                                                                   0xe
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_VREF_BMSK                                                               0x3000
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_GNSS_ADC_VREF_SHFT                                                                  0xc
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_AVG_ERR_BMSK                                                           0x800
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_AVG_ERR_SHFT                                                             0xb
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC0_CAL_AVG_ERR_BMSK                                                           0x400
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC0_CAL_AVG_ERR_SHFT                                                             0xa
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC_0_1_FLAG_BMSK                                                               0x200
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC_0_1_FLAG_SHFT                                                                 0x9
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_OVFLOW_BMSK                                                            0x100
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_OVFLOW_SHFT                                                              0x8
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC0_CAL_OVFLOW_BMSK                                                             0x80
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC0_CAL_OVFLOW_SHFT                                                              0x7
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_7_1_BMSK                                                                0x7f
#define HWIO_QFPROM_RAW_IMEI_ESN1_MSB_TXDAC1_CAL_7_1_SHFT                                                                 0x0

#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000e0)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000e0)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN2_LSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN2_LSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN2_LSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B1M1_BMSK                                                                 0xe0000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B1M1_SHFT                                                                       0x1d
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B1M0_BMSK                                                                 0x1c000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B1M0_SHFT                                                                       0x1a
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_G_B1_BMSK                                                                     0x3800000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_G_B1_SHFT                                                                          0x17
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_SAR_B1_BMSK                                                                    0x600000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_SAR_B1_SHFT                                                                        0x15
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_CLK_B0_BMSK                                                                    0x180000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_CLK_B0_SHFT                                                                        0x13
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_VREF_B0_BMSK                                                                    0x60000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_VREF_B0_SHFT                                                                       0x11
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M3_BMSK                                                                    0x1c000
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M3_SHFT                                                                        0xe
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M2_BMSK                                                                     0x3800
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M2_SHFT                                                                        0xb
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M1_BMSK                                                                      0x700
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M1_SHFT                                                                        0x8
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M0_BMSK                                                                       0xe0
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_PH_B0M0_SHFT                                                                        0x5
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_G_B0_BMSK                                                                          0x1c
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_G_B0_SHFT                                                                           0x2
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_SAR_B0_BMSK                                                                         0x3
#define HWIO_QFPROM_RAW_IMEI_ESN2_LSB_SAR_B0_SHFT                                                                         0x0

#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000e4)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000e4)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_RMSK                                                                         0xffff7fff
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN2_MSB_ADDR, HWIO_QFPROM_RAW_IMEI_ESN2_MSB_RMSK)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMEI_ESN2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMEI_ESN2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMEI_ESN2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_IMEI_ESN2_MSB_IN)
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_SPARE0_BMSK                                                                  0x80000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_SPARE0_SHFT                                                                        0x1f
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_CLK_B2_BMSK                                                                  0x60000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_CLK_B2_SHFT                                                                        0x1d
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_VREF_B2_BMSK                                                                 0x18000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_VREF_B2_SHFT                                                                       0x1b
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M3_BMSK                                                                  0x7000000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M3_SHFT                                                                       0x18
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M2_BMSK                                                                   0xe00000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M2_SHFT                                                                       0x15
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M1_BMSK                                                                   0x1c0000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M1_SHFT                                                                       0x12
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M0_BMSK                                                                    0x30000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B2M0_SHFT                                                                       0x10
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_G_B2_BMSK                                                                        0x7000
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_G_B2_SHFT                                                                           0xc
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_SAR_B2_BMSK                                                                       0xc00
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_SAR_B2_SHFT                                                                         0xa
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_CLK_B1_BMSK                                                                       0x300
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_CLK_B1_SHFT                                                                         0x8
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_VREF_B1_BMSK                                                                       0xc0
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_VREF_B1_SHFT                                                                        0x6
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B1M3_BMSK                                                                       0x38
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B1M3_SHFT                                                                        0x3
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B1M2_BMSK                                                                        0x7
#define HWIO_QFPROM_RAW_IMEI_ESN2_MSB_PH_B1M2_SHFT                                                                        0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000e8)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000e8)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_DISABLE_BMSK                                                    0x80000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_DISABLE_SHFT                                                          0x1f
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE0_DISABLE_BMSK                                                    0x40000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE0_DISABLE_SHFT                                                          0x1e
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_VENUS_0_DBGEN_DISABLE_BMSK                                             0x20000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_VENUS_0_DBGEN_DISABLE_SHFT                                                   0x1d
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_DAPEN_DISABLE_BMSK                                                 0x10000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_DAPEN_DISABLE_SHFT                                                       0x1c
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                       0x8000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                            0x1b
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_DBGEN_DISABLE_BMSK                                                  0x4000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RPM_DBGEN_DISABLE_SHFT                                                       0x1a
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_WCSS_DBGEN_DISABLE_BMSK                                                 0x2000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_WCSS_DBGEN_DISABLE_SHFT                                                      0x19
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_LPASS_DBGEN_DISABLE_BMSK                                                0x1000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_LPASS_DBGEN_DISABLE_SHFT                                                     0x18
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_NIDEN_DISABLE_BMSK                                                   0x800000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_NIDEN_DISABLE_SHFT                                                       0x17
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_DBGEN_DISABLE_BMSK                                                   0x400000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_DBGEN_DISABLE_SHFT                                                       0x16
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_BMSK                                                   0x200000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_SHFT                                                       0x15
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_BMSK                                                              0x180000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_SHFT                                                                  0x13
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_BMSK                                              0x40000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_SHFT                                                 0x12
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALT_SD_PORT_FOR_BOOT_BMSK                                                 0x20000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALT_SD_PORT_FOR_BOOT_SHFT                                                    0x11
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_GPIO_DISABLE_BMSK                                        0x10000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_GPIO_DISABLE_SHFT                                           0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_EN_BMSK                                                   0x8000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_EN_SHFT                                                      0xf
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FAST_BOOT_BMSK                                                             0x7c00
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FAST_BOOT_SHFT                                                                0xa
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDP_ENUM_SKIP_BMSK                                                          0x200
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDP_ENUM_SKIP_SHFT                                                            0x9
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_BMSK                                                    0x100
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_SHFT                                                      0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_PBL_BOOT_SPEED_BMSK                                                     0xc0
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_PBL_BOOT_SPEED_SHFT                                                      0x6
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_BMSK                                                  0x20
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_SHFT                                                   0x5
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE0_BMSK                                                                  0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE0_SHFT                                                                   0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_PMIC_POWER_DOWN_MSM_BMSK                                                  0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_PMIC_POWER_DOWN_MSM_SHFT                                                  0x3
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_USB_ENUM_TIMEOUT_BMSK                                                         0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_USB_ENUM_TIMEOUT_SHFT                                                         0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DLOAD_TIMEOUT_BMSK                                                            0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DLOAD_TIMEOUT_SHFT                                                            0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_BMSK                                                          0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_SHFT                                                          0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000ec)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000ec)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WDOG_EN_BMSK                                                           0x80000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WDOG_EN_SHFT                                                                 0x1f
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE2_BMSK                                                            0x40000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE2_SHFT                                                                  0x1e
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SCM_M1_RD_PERM_BMSK                                                    0x20000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SCM_M1_RD_PERM_SHFT                                                          0x1d
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_UFS_SCM_FORCE_EFUSE_KEY_BMSK                                           0x10000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_UFS_SCM_FORCE_EFUSE_KEY_SHFT                                                 0x1c
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SDC2_SCM_FORCE_EFUSE_KEY_BMSK                                           0x8000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SDC2_SCM_FORCE_EFUSE_KEY_SHFT                                                0x1b
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPDM_SECURE_MODE_BMSK                                                   0x4000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPDM_SECURE_MODE_SHFT                                                        0x1a
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IMEI_ESN_SELECT_BMSK                                                    0x3000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IMEI_ESN_SELECT_SHFT                                                         0x18
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE1_BMSK                                                              0xc00000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE1_SHFT                                                                  0x16
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_CUST_PRIV_KEY_SELECT_BMSK                                                0x200000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_CUST_PRIV_KEY_SELECT_SHFT                                                    0x15
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SW_FUSE_PROG_DISABLE_BMSK                                                0x100000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SW_FUSE_PROG_DISABLE_SHFT                                                    0x14
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE0_BMSK                                                               0xfe000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE0_SHFT                                                                   0xd
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_SPNIDEN_DISABLE_BMSK                                                 0x1000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_SPNIDEN_DISABLE_SHFT                                                    0xc
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_SPIDEN_DISABLE_BMSK                                                   0x800
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_SPIDEN_DISABLE_SHFT                                                     0xb
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_NIDEN_DISABLE_BMSK                                                    0x400
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_NIDEN_DISABLE_SHFT                                                      0xa
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_DBGEN_DISABLE_BMSK                                                    0x200
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS1_DBGEN_DISABLE_SHFT                                                      0x9
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_BMSK                                                   0x100
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_SHFT                                                     0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_BMSK                                                     0x80
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_SHFT                                                      0x7
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_BMSK                                                      0x40
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_SHFT                                                       0x6
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_BMSK                                                       0x20
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_SHFT                                                        0x5
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_BMSK                                                       0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_SHFT                                                        0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_SPNIDEN_DISABLE_BMSK                                                    0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_SPNIDEN_DISABLE_SHFT                                                    0x3
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_SPIDEN_DISABLE_BMSK                                                     0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_SPIDEN_DISABLE_SHFT                                                     0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_NIDEN_DISABLE_BMSK                                                      0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_NIDEN_DISABLE_SHFT                                                      0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_DBGEN_DISABLE_BMSK                                                      0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS0_DBGEN_DISABLE_SHFT                                                      0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000f0)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000f0)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_HW_ID_BMSK                                                         0xffff0000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_HW_ID_SHFT                                                               0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ANTI_ROLLBACK_FEATURE_EN_BMSK                                              0xff00
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ANTI_ROLLBACK_FEATURE_EN_SHFT                                                 0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_SPARE0_BMSK                                                                  0xf0
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_SPARE0_SHFT                                                                   0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ROOT_CERT_TOTAL_NUM_BMSK                                                      0xf
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ROOT_CERT_TOTAL_NUM_SHFT                                                      0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000f4)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000f4)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_SPARE0_BMSK                                                            0xffff0000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_SPARE0_SHFT                                                                  0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_BMSK                                                        0xffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_SHFT                                                           0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000f8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000f8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                                     0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                                           0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_0_DISABLE_BMSK                                                    0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_0_DISABLE_SHFT                                                          0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                                    0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                                          0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                                    0x10000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                                          0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                                               0x8000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                                                    0x1b
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                                               0x4000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                                                    0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                                    0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                                         0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                                    0x1000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                                         0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_SPARE_DISABLE_BMSK                                                0xe00000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_SPARE_DISABLE_SHFT                                                    0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_UL_CA_DISABLE_BMSK                                            0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_UL_CA_DISABLE_SHFT                                                0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX3_DISABLE_BMSK                                                 0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX3_DISABLE_SHFT                                                    0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX2_DISABLE_BMSK                                                 0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX2_DISABLE_SHFT                                                    0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_GLOBAL_DISABLE_BMSK                                                0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_GLOBAL_DISABLE_SHFT                                                   0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DC_DISABLE_0_BMSK                                             0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DC_DISABLE_0_SHFT                                                0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_MIMO_DISABLE_0_BMSK                                            0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_MIMO_DISABLE_0_SHFT                                               0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT2_DISABLE_0_BMSK                                       0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT2_DISABLE_0_SHFT                                          0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT1_DISABLE_0_BMSK                                       0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT1_DISABLE_0_SHFT                                          0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_TDSCDMA_DISABLE_0_BMSK                                              0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_TDSCDMA_DISABLE_0_SHFT                                                 0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DISABLE_0_BMSK                                                  0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DISABLE_0_SHFT                                                    0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_DISABLE_0_BMSK                                                   0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_DISABLE_0_SHFT                                                     0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_WCDMA_DISABLE_0_BMSK                                                 0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_WCDMA_DISABLE_0_SHFT                                                   0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_DO_DISABLE_0_BMSK                                                    0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_DO_DISABLE_0_SHFT                                                      0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_1X_DISABLE_0_BMSK                                                     0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MODEM_1X_DISABLE_0_SHFT                                                      0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_NAV_DISABLE_BMSK                                                            0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_NAV_DISABLE_SHFT                                                             0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_GERAN_DISABLE_0_BMSK                                                        0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_GERAN_DISABLE_0_SHFT                                                         0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_SPI_SLAVE_DISABLE_BMSK                                                      0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_SPI_SLAVE_DISABLE_SHFT                                                       0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_APPS_ACG_DISABLE_BMSK                                                        0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_APPS_ACG_DISABLE_SHFT                                                        0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                                                  0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000fc)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000000fc)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENDOR_LOCK_BMSK                                                      0xf0000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENDOR_LOCK_SHFT                                                            0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_SDC_EMMC_MODE1P2_FORCE_GPIO_BMSK                                       0x8000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_SDC_EMMC_MODE1P2_FORCE_GPIO_SHFT                                            0x1b
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_DSDA_DISABLE_BMSK                                                0x4000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_DSDA_DISABLE_SHFT                                                     0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_60_MHZ_DISABLE_BMSK                                          0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_60_MHZ_DISABLE_SHFT                                               0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_40_MHZ_DISABLE_BMSK                                          0x1000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_40_MHZ_DISABLE_SHFT                                               0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DC_DISABLE_1_BMSK                                            0x800000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DC_DISABLE_1_SHFT                                                0x17
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_MIMO_DISABLE_1_BMSK                                          0x400000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_MIMO_DISABLE_1_SHFT                                              0x16
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT2_DISABLE_1_BMSK                                     0x200000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT2_DISABLE_1_SHFT                                         0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT1_DISABLE_1_BMSK                                     0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT1_DISABLE_1_SHFT                                         0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_TDSCDMA_DISABLE_1_BMSK                                             0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_TDSCDMA_DISABLE_1_SHFT                                                0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DISABLE_1_BMSK                                                0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DISABLE_1_SHFT                                                   0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_DISABLE_1_BMSK                                                 0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_DISABLE_1_SHFT                                                    0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_WCDMA_DISABLE_1_BMSK                                               0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_WCDMA_DISABLE_1_SHFT                                                  0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_DO_DISABLE_1_BMSK                                                   0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_DO_DISABLE_1_SHFT                                                      0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_1X_DISABLE_1_BMSK                                                   0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MODEM_1X_DISABLE_1_SHFT                                                      0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GERAN_DISABLE_1_BMSK                                                      0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GERAN_DISABLE_1_SHFT                                                         0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_UFS_SW_CONTROL_DISABLE_BMSK                                               0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_UFS_SW_CONTROL_DISABLE_SHFT                                                  0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PCIE_1_DISABLE_BMSK                                                        0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PCIE_1_DISABLE_SHFT                                                          0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PCIE_0_DISABLE_BMSK                                                        0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PCIE_0_DISABLE_SHFT                                                          0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_SATA_DISABLE_BMSK                                                          0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_SATA_DISABLE_SHFT                                                            0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ACC_DISABLE_BMSK                                                           0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ACC_DISABLE_SHFT                                                             0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL1_BMSK                                                       0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL1_SHFT                                                        0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL0_BMSK                                                       0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL0_SHFT                                                        0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_DISABLE_BMSK                                                    0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_DISABLE_SHFT                                                     0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_DECODE_DISABLE_BMSK                                              0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_DECODE_DISABLE_SHFT                                               0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                                               0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                                               0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_4K_DISABLE_BMSK                                                        0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VENUS_4K_DISABLE_SHFT                                                        0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MDP_APICAL_LTC_DISABLE_BMSK                                                  0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MDP_APICAL_LTC_DISABLE_SHFT                                                  0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_HDMI_DISABLE_BMSK                                                            0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_HDMI_DISABLE_SHFT                                                            0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000100)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000100)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SCM_DISABLE_BMSK                                                      0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SCM_DISABLE_SHFT                                                            0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY1_BMSK                                                0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY1_SHFT                                                      0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY0_BMSK                                                0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY0_SHFT                                                      0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_DISABLE_BMSK                                                      0x10000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ICE_DISABLE_SHFT                                                            0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_CSID_DPCM_14_DISABLE_BMSK                                              0x8000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_CSID_DPCM_14_DISABLE_SHFT                                                   0x1b
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_FD_DISABLE_BMSK                                                        0x4000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_FD_DISABLE_SHFT                                                             0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPNIDEN_DISABLE_BMSK                                          0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPNIDEN_DISABLE_SHFT                                               0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPIDEN_DISABLE_BMSK                                           0x1000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPIDEN_DISABLE_SHFT                                                0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_NIDEN_DISABLE_BMSK                                             0x800000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_NIDEN_DISABLE_SHFT                                                 0x17
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_DBGEN_DISABLE_BMSK                                             0x400000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS1_DBGEN_DISABLE_SHFT                                                 0x16
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                                            0x200000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                                                0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPNIDEN_DISABLE_BMSK                                             0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPNIDEN_DISABLE_SHFT                                                 0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPIDEN_DISABLE_BMSK                                               0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPIDEN_DISABLE_SHFT                                                  0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_NIDEN_DISABLE_BMSK                                                0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_NIDEN_DISABLE_SHFT                                                   0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_DBGEN_DISABLE_BMSK                                                0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_DAP_DBGEN_DISABLE_SHFT                                                   0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPNIDEN_DISABLE_BMSK                                            0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPNIDEN_DISABLE_SHFT                                               0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPIDEN_DISABLE_BMSK                                              0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPIDEN_DISABLE_SHFT                                                 0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_NIDEN_DISABLE_BMSK                                               0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_NIDEN_DISABLE_SHFT                                                  0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_DBGEN_DISABLE_BMSK                                               0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_APPS0_DBGEN_DISABLE_SHFT                                                  0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_SPARE1_DISABLE_BMSK                                                    0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_SPARE1_DISABLE_SHFT                                                       0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_SPARE0_DISABLE_BMSK                                                     0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_SPARE0_DISABLE_SHFT                                                       0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                                              0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                                                0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_DAPEN_DISABLE_BMSK                                                  0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_DAPEN_DISABLE_SHFT                                                    0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                       0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                         0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_DBGEN_DISABLE_BMSK                                                   0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_RPM_DBGEN_DISABLE_SHFT                                                    0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                                                  0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                                                   0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_LPASS_DBGEN_DISABLE_BMSK                                                 0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_LPASS_DBGEN_DISABLE_SHFT                                                  0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_MSS_NIDEN_DISABLE_BMSK                                                   0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_MSS_NIDEN_DISABLE_SHFT                                                    0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_MSS_DBGEN_DISABLE_BMSK                                                    0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_QC_MSS_DBGEN_DISABLE_SHFT                                                    0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MOCHA_PART_BMSK                                                              0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MOCHA_PART_SHFT                                                              0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SM_BIST_DISABLE_BMSK                                                         0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SM_BIST_DISABLE_SHFT                                                         0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_TIC_DISABLE_BMSK                                                             0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_TIC_DISABLE_SHFT                                                             0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000104)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000104)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SEC_TAP_ACCESS_DISABLE_BMSK                                           0xfffc0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SEC_TAP_ACCESS_DISABLE_SHFT                                                 0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_TAP_CJI_CORE_SEL_DISABLE_BMSK                                            0x3c000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_TAP_CJI_CORE_SEL_DISABLE_SHFT                                                0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_TAP_INSTR_DISABLE_BMSK                                                    0x3fff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_TAP_INSTR_DISABLE_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000108)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000108)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TAP_GEN_SPARE_INSTR_DISABLE_BMSK                                      0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TAP_GEN_SPARE_INSTR_DISABLE_SHFT                                             0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000010c)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000010c)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SW_EXPANSION_FUSES_BMSK                                               0xff000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SW_EXPANSION_FUSES_SHFT                                                     0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CFGCPUPRESENT_N_BMSK                                               0xff0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CFGCPUPRESENT_N_SHFT                                                   0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION3_BMSK                                                  0xf000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION3_SHFT                                                     0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION2_BMSK                                                   0xf00
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION2_SHFT                                                     0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION1_BMSK                                                    0xf0
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION1_SHFT                                                     0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION0_BMSK                                                     0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION0_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000110)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000110)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_MDSP_FW_DISABLE_BMSK                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_MDSP_FW_DISABLE_SHFT                                                         0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000114)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000114)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS1_CLOCKCFG_BMSK                                                   0xc0000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS1_CLOCKCFG_SHFT                                                         0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS0_CLOCKCFG_BMSK                                                   0x30000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS0_CLOCKCFG_SHFT                                                         0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS_ARCH64_DISABLE_BMSK                                               0xc000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS_ARCH64_DISABLE_SHFT                                                    0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RICA_DISABLE_BMSK                                                      0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RICA_DISABLE_SHFT                                                           0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_SPARE0_BMSK                                                            0x1ff0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_SPARE0_SHFT                                                                 0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RPM_PBL_BOOT_SPEED_BMSK                                                   0xc000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RPM_PBL_BOOT_SPEED_SHFT                                                      0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RPM_BOOT_FROM_ROM_BMSK                                                    0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RPM_BOOT_FROM_ROM_SHFT                                                       0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS_BOOT_FROM_ROM_BMSK                                                   0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_APPS_BOOT_FROM_ROM_SHFT                                                      0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_MSA_ENA_BMSK                                                               0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_MSA_ENA_SHFT                                                                 0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_FORCE_MSA_AUTH_EN_BMSK                                                     0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_FORCE_MSA_AUTH_EN_SHFT                                                       0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_FLCB_SKIP_BMSK                                                             0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_FLCB_SKIP_SHFT                                                               0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_QCOM_PMIC_FEATURE_ENABLE_BMSK                                              0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_QCOM_PMIC_FEATURE_ENABLE_SHFT                                                0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_BOOT_ROM_CFG_BMSK                                                           0xe0
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_BOOT_ROM_CFG_SHFT                                                            0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_STACKED_MEMORY_ID_BMSK                                                      0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_STACKED_MEMORY_ID_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_MEM_REDUNn_ADDR(n)                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000118 + 0x4 * (n))
#define HWIO_QFPROM_RAW_MEM_REDUNn_OFFS(n)                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000118 + 0x4 * (n))
#define HWIO_QFPROM_RAW_MEM_REDUNn_RMSK                                                                            0xffffffff
#define HWIO_QFPROM_RAW_MEM_REDUNn_MAXn                                                                                    35
#define HWIO_QFPROM_RAW_MEM_REDUNn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_REDUNn_ADDR(n), HWIO_QFPROM_RAW_MEM_REDUNn_RMSK)
#define HWIO_QFPROM_RAW_MEM_REDUNn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_REDUNn_ADDR(n), mask)
#define HWIO_QFPROM_RAW_MEM_REDUNn_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_MEM_REDUNn_ADDR(n),val)
#define HWIO_QFPROM_RAW_MEM_REDUNn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_REDUNn_ADDR(n),mask,val,HWIO_QFPROM_RAW_MEM_REDUNn_INI(n))
#define HWIO_QFPROM_RAW_MEM_REDUNn_REDUN_DATA_BMSK                                                                 0xffffffff
#define HWIO_QFPROM_RAW_MEM_REDUNn_REDUN_DATA_SHFT                                                                        0x0

#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001a8)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001a8)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_DEBUG_KEY_LSB_ADDR, HWIO_QFPROM_RAW_DEBUG_KEY_LSB_RMSK)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_DEBUG_KEY_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_DEBUG_KEY_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_DEBUG_KEY_LSB_ADDR,m,v,HWIO_QFPROM_RAW_DEBUG_KEY_LSB_IN)
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B4M1_BMSK                                                                 0xe0000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B4M1_SHFT                                                                       0x1d
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B4M0_BMSK                                                                 0x1c000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B4M0_SHFT                                                                       0x1a
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_G_B4_BMSK                                                                     0x3800000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_G_B4_SHFT                                                                          0x17
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_SAR_B1_BMSK                                                                    0x600000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_SAR_B1_SHFT                                                                        0x15
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_CLK_B3_BMSK                                                                    0x180000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_CLK_B3_SHFT                                                                        0x13
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_VREF_B3_BMSK                                                                    0x60000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_VREF_B3_SHFT                                                                       0x11
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M3_BMSK                                                                    0x1c000
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M3_SHFT                                                                        0xe
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M2_BMSK                                                                     0x3800
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M2_SHFT                                                                        0xb
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M1_BMSK                                                                      0x700
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M1_SHFT                                                                        0x8
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M0_BMSK                                                                       0xe0
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_PH_B3M0_SHFT                                                                        0x5
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_G_B3_BMSK                                                                          0x1c
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_G_B3_SHFT                                                                           0x2
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_SAR_B3_BMSK                                                                         0x3
#define HWIO_QFPROM_RAW_DEBUG_KEY_LSB_SAR_B3_SHFT                                                                         0x0

#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001ac)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001ac)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_RMSK                                                                         0xffff7fff
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_DEBUG_KEY_MSB_ADDR, HWIO_QFPROM_RAW_DEBUG_KEY_MSB_RMSK)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_DEBUG_KEY_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_DEBUG_KEY_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_DEBUG_KEY_MSB_ADDR,m,v,HWIO_QFPROM_RAW_DEBUG_KEY_MSB_IN)
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_SPARE0_BMSK                                                                  0x80000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_SPARE0_SHFT                                                                        0x1f
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_CLK_B5_BMSK                                                                  0x60000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_CLK_B5_SHFT                                                                        0x1d
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_VREF_B5_BMSK                                                                 0x18000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_VREF_B5_SHFT                                                                       0x1b
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M3_BMSK                                                                  0x7000000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M3_SHFT                                                                       0x18
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M2_BMSK                                                                   0xe00000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M2_SHFT                                                                       0x15
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M1_BMSK                                                                   0x1c0000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M1_SHFT                                                                       0x12
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M0_BMSK                                                                    0x30000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B5M0_SHFT                                                                       0x10
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_G_B5_BMSK                                                                        0x7000
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_G_B5_SHFT                                                                           0xc
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_SAR_B5_BMSK                                                                       0xc00
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_SAR_B5_SHFT                                                                         0xa
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_CLK_B4_BMSK                                                                       0x300
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_CLK_B4_SHFT                                                                         0x8
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_VREF_B4_BMSK                                                                       0xc0
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_VREF_B4_SHFT                                                                        0x6
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B4M3_BMSK                                                                       0x38
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B4M3_SHFT                                                                        0x3
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B4M2_BMSK                                                                        0x7
#define HWIO_QFPROM_RAW_DEBUG_KEY_MSB_PH_B4M2_SHFT                                                                        0x0

#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b0)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b0)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_MEM_ACCEL_BMSK                                                          0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_LSB_MEM_ACCEL_SHFT                                                                 0x0

#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b4)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b4)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_MEM_ACCEL_BMSK                                                          0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW0_MSB_MEM_ACCEL_SHFT                                                                 0x0

#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b8)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b8)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_RMSK                                                                        0x3fff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_MEM_ACCEL_BMSK                                                              0x3fff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_LSB_MEM_ACCEL_SHFT                                                                 0x0

#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001bc)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001bc)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_BMSK                                      0xffffffff
#define HWIO_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_QFPROM_RAW_MEM_ACCEL_ROW1_MSB_SHFT                                             0x0

#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c0)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c0)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_SW_CAL_REDUN_10_0_BMSK                                                      0xffe00000
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_SW_CAL_REDUN_10_0_SHFT                                                            0x15
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_CLK_B6_BMSK                                                                   0x180000
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_CLK_B6_SHFT                                                                       0x13
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_VREF_B6_BMSK                                                                   0x60000
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_VREF_B6_SHFT                                                                      0x11
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M3_BMSK                                                                   0x1c000
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M3_SHFT                                                                       0xe
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M2_BMSK                                                                    0x3800
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M2_SHFT                                                                       0xb
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M1_BMSK                                                                     0x700
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M1_SHFT                                                                       0x8
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M0_BMSK                                                                      0xe0
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_PH_B6M0_SHFT                                                                       0x5
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_G_B6_BMSK                                                                         0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_G_B6_SHFT                                                                          0x2
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_SAR_B6_BMSK                                                                        0x3
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_SAR_B6_SHFT                                                                        0x0

#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c4)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c4)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_SW_CAL_REDUN_42_11_BMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_SW_CAL_REDUN_42_11_SHFT                                                            0x0

#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c8)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c8)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_SPARE0_BMSK                                                                 0xfff00000
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_SPARE0_SHFT                                                                       0x14
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS3_LDO_VREF_TRIM_BMSK                                                       0xf8000
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS3_LDO_VREF_TRIM_SHFT                                                           0xf
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS2_LDO_VREF_TRIM_BMSK                                                        0x7c00
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS2_LDO_VREF_TRIM_SHFT                                                           0xa
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS1_LDO_VREF_TRIM_BMSK                                                         0x3e0
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS1_LDO_VREF_TRIM_SHFT                                                           0x5
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS0_LDO_VREF_TRIM_BMSK                                                          0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_APPS0_LDO_VREF_TRIM_SHFT                                                           0x0

#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001cc)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001cc)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_APPS_APCSLMEAS_ACC_TRIM_BMSK                                                0xf8000000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_APPS_APCSLMEAS_ACC_TRIM_SHFT                                                      0x1b
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SW_CAL_REDUN_46_43_BMSK                                                      0x7800000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SW_CAL_REDUN_46_43_SHFT                                                           0x17
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SPARE0_BMSK                                                                   0x7f0000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SPARE0_SHFT                                                                       0x10
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_GP_HW_CALIB_BMSK                                                                0xf000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_GP_HW_CALIB_SHFT                                                                   0xc
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS1_LDO_VREF_TRIM_BMSK                                                         0xf80
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS1_LDO_VREF_TRIM_SHFT                                                           0x7
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS1_LDO_ENABLE_BMSK                                                             0x40
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS1_LDO_ENABLE_SHFT                                                              0x6
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS0_LDO_VREF_TRIM_BMSK                                                          0x3e
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS0_LDO_VREF_TRIM_SHFT                                                           0x1
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS0_LDO_ENABLE_BMSK                                                              0x1
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_Q6SS0_LDO_ENABLE_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR                                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001d0)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OFFS                                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001d0)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_RMSK                                                                            0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR, HWIO_QFPROM_RAW_FEC_EN_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEC_EN_LSB_IN)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION31_FEC_EN_BMSK                                                            0x80000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION31_FEC_EN_SHFT                                                                  0x1f
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION30_FEC_EN_BMSK                                                            0x40000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION30_FEC_EN_SHFT                                                                  0x1e
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION29_FEC_EN_BMSK                                                            0x20000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION29_FEC_EN_SHFT                                                                  0x1d
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION28_FEC_EN_BMSK                                                            0x10000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION28_FEC_EN_SHFT                                                                  0x1c
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION27_FEC_EN_BMSK                                                             0x8000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION27_FEC_EN_SHFT                                                                  0x1b
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION26_FEC_EN_BMSK                                                             0x4000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION26_FEC_EN_SHFT                                                                  0x1a
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION25_FEC_EN_BMSK                                                             0x2000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION25_FEC_EN_SHFT                                                                  0x19
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION24_FEC_EN_BMSK                                                             0x1000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION24_FEC_EN_SHFT                                                                  0x18
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION23_FEC_EN_BMSK                                                              0x800000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION23_FEC_EN_SHFT                                                                  0x17
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION22_FEC_EN_BMSK                                                              0x400000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION22_FEC_EN_SHFT                                                                  0x16
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION21_FEC_EN_BMSK                                                              0x200000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION21_FEC_EN_SHFT                                                                  0x15
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION20_FEC_EN_BMSK                                                              0x100000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION20_FEC_EN_SHFT                                                                  0x14
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION19_FEC_EN_BMSK                                                               0x80000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION19_FEC_EN_SHFT                                                                  0x13
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION18_FEC_EN_BMSK                                                               0x40000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION18_FEC_EN_SHFT                                                                  0x12
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION17_FEC_EN_BMSK                                                               0x20000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION17_FEC_EN_SHFT                                                                  0x11
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION16_FEC_EN_BMSK                                                               0x10000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION16_FEC_EN_SHFT                                                                  0x10
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION15_FEC_EN_BMSK                                                                0x8000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION15_FEC_EN_SHFT                                                                   0xf
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION14_FEC_EN_BMSK                                                                0x4000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION14_FEC_EN_SHFT                                                                   0xe
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION13_FEC_EN_BMSK                                                                0x2000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION13_FEC_EN_SHFT                                                                   0xd
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION12_FEC_EN_BMSK                                                                0x1000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION12_FEC_EN_SHFT                                                                   0xc
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION11_FEC_EN_BMSK                                                                 0x800
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION11_FEC_EN_SHFT                                                                   0xb
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION10_FEC_EN_BMSK                                                                 0x400
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION10_FEC_EN_SHFT                                                                   0xa
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION9_FEC_EN_BMSK                                                                  0x200
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION9_FEC_EN_SHFT                                                                    0x9
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION8_FEC_EN_BMSK                                                                  0x100
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION8_FEC_EN_SHFT                                                                    0x8
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION7_FEC_EN_BMSK                                                                   0x80
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION7_FEC_EN_SHFT                                                                    0x7
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION6_FEC_EN_BMSK                                                                   0x40
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION6_FEC_EN_SHFT                                                                    0x6
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION5_FEC_EN_BMSK                                                                   0x20
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION5_FEC_EN_SHFT                                                                    0x5
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION4_FEC_EN_BMSK                                                                   0x10
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION4_FEC_EN_SHFT                                                                    0x4
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION3_FEC_EN_BMSK                                                                    0x8
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION3_FEC_EN_SHFT                                                                    0x3
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION2_FEC_EN_BMSK                                                                    0x4
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION2_FEC_EN_SHFT                                                                    0x2
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION1_FEC_EN_BMSK                                                                    0x2
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION1_FEC_EN_SHFT                                                                    0x1
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION0_FEC_EN_BMSK                                                                    0x1
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION0_FEC_EN_SHFT                                                                    0x0

#define HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR                                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001d4)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OFFS                                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001d4)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_RMSK                                                                            0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR, HWIO_QFPROM_RAW_FEC_EN_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEC_EN_MSB_IN)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_QFPROM_RAW_FEC_EN_MSB_BMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_MSB_QFPROM_RAW_FEC_EN_MSB_SHFT                                                             0x0

#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001d8)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001d8)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_RMSK                                                                  0xff000000
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ADDR, HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_RMSK)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ADDR,m,v,HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_IN)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ROOT_CERT_PK_HASH_INDEX_BMSK                                          0xff000000
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_LSB_ROOT_CERT_PK_HASH_INDEX_SHFT                                                0x18

#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001dc)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001dc)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_ADDR, HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_RMSK)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_ADDR,m,v,HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_IN)
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_BMSK                                  0xffffffff
#define HWIO_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_QFPROM_RAW_INTAGLIO_GLUEBIT_MSB_SHFT                                         0x0

#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_ADDR(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001e0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_OFFS(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001e0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_RMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_MAXn                                                                              1
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_KEY_DATA_BMSK                                                            0xffffffff
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_LSB_KEY_DATA_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_ADDR(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001e4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_OFFS(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001e4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_RMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_MAXn                                                                              1
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_KEY_DATA_BMSK                                                            0xffffffff
#define HWIO_QFPROM_RAW_CUST_KEY_ROWn_MSB_KEY_DATA_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f0)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f0)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SERIAL_NUM_LSB_ADDR, HWIO_QFPROM_RAW_SERIAL_NUM_LSB_RMSK)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SERIAL_NUM_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SERIAL_NUM_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SERIAL_NUM_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SERIAL_NUM_LSB_IN)
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_SERIAL_NUM_BMSK                                                             0xffffffff
#define HWIO_QFPROM_RAW_SERIAL_NUM_LSB_SERIAL_NUM_SHFT                                                                    0x0

#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f4)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f4)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_RMSK                                                                            0xffff
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SERIAL_NUM_MSB_ADDR, HWIO_QFPROM_RAW_SERIAL_NUM_MSB_RMSK)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SERIAL_NUM_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SERIAL_NUM_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SERIAL_NUM_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SERIAL_NUM_MSB_IN)
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_CHIP_ID_BMSK                                                                    0xffff
#define HWIO_QFPROM_RAW_SERIAL_NUM_MSB_CHIP_ID_SHFT                                                                       0x0

#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f8)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f8)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG19_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG19_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG19_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG19_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG19_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG19_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_ROOT_CERT_PK_HASH_INDEX_BMSK                                               0xff000000
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_ROOT_CERT_PK_HASH_INDEX_SHFT                                                     0x18
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_SPARE0_BMSK                                                                  0xff0000
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_SPARE0_SHFT                                                                      0x10
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_PIL_SUBSYSTEM_47_32_BMSK                                                       0xffff
#define HWIO_QFPROM_RAW_SPARE_REG19_LSB_PIL_SUBSYSTEM_47_32_SHFT                                                          0x0

#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001fc)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001fc)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG19_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG19_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG19_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG19_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG19_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG19_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_TQS_HASH_ACTIVE_BMSK                                                       0xf8000000
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_TQS_HASH_ACTIVE_SHFT                                                             0x1b
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_RPMB_KEY_PROVISIONED_BMSK                                                   0x4000000
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_RPMB_KEY_PROVISIONED_SHFT                                                        0x1a
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_SPARE_BMSK                                                                  0x3ffffff
#define HWIO_QFPROM_RAW_SPARE_REG19_MSB_SPARE_SHFT                                                                        0x0

#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000200 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000200 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_MAXn                                                                            47
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA0_BMSK                                                        0xffff0000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA0_SHFT                                                              0x10
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_ADDR_BMSK                                                             0xffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_ADDR_SHFT                                                                0x0

#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000204 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000204 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RMSK                                                                    0x7f01ffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_MAXn                                                                            47
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_FEC_VALUE_BMSK                                                          0x7f000000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_FEC_VALUE_SHFT                                                                0x18
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_BMSK                                                              0x10000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_SHFT                                                                 0x10
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_DATA1_BMSK                                                            0xffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_DATA1_SHFT                                                               0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000380 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000380 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                                                3
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000384 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000384 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                                       0x7fffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                                                3
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_BMSK                                             0x7f000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_SHFT                                                   0x18
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                                               0xffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003a0)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003a0)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003a4)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003a4)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                                       0x7f000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_BMSK                                             0x7f000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_SHFT                                                   0x18

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003a8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003a8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                                                3
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003ac + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003ac + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                                       0x7fffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                                                3
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_BMSK                                             0x7f000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_SHFT                                                   0x18
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                                               0xffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003c8)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003c8)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003cc)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003cc)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                                       0x7f000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_BMSK                                             0x7f000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_SHFT                                                   0x18

#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_ADDR(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003d0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_OFFS(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003d0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_MAXn                                                                           3
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_HASH_DATA0_BMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_LSB_HASH_DATA0_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_ADDR(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003d4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_OFFS(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003d4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_RMSK                                                                  0x7fffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_MAXn                                                                           3
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_FEC_VALUE_BMSK                                                        0x7f000000
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_FEC_VALUE_SHFT                                                              0x18
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_HASH_DATA1_BMSK                                                         0xffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROWn_MSB_HASH_DATA1_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003f0)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003f0)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_HASH_DATA0_BMSK                                                       0xffffffff
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_LSB_HASH_DATA0_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003f4)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003f4)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_RMSK                                                                  0x7f000000
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_FEC_VALUE_BMSK                                                        0x7f000000
#define HWIO_QFPROM_RAW_OEM_PK_HASH_ROW4_MSB_FEC_VALUE_SHFT                                                              0x18

#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003f8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003f8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_MAXn                                                                          3
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                                       0xff000000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                                             0x18
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                                         0xff0000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                                             0x10
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                                           0xff00
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                                              0x8
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                                             0xff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003fc + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003fc + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RMSK                                                                 0x7fffffff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_MAXn                                                                          3
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_FEC_VALUE_BMSK                                                       0x7f000000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_FEC_VALUE_SHFT                                                             0x18
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                                         0xff0000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                                             0x10
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                                           0xff00
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                                              0x8
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                                             0xff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                                              0x0

#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_ADDR(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000418 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_OFFS(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000418 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_MAXn                                                                           3
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                                        0xff000000
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                                              0x18
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                                          0xff0000
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                                              0x10
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                                            0xff00
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                                               0x8
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                                              0xff
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                                               0x0

#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_ADDR(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000041c + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_OFFS(n)                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000041c + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_RMSK                                                                  0x7fffffff
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_MAXn                                                                           3
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_FEC_VALUE_BMSK                                                        0x7f000000
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_FEC_VALUE_SHFT                                                              0x18
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                                          0xff0000
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                                              0x10
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                                            0xff00
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                                               0x8
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                                              0xff
#define HWIO_QFPROM_RAW_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                                               0x0

#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000438)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000438)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_USB_VID_PID_LSB_ADDR, HWIO_QFPROM_RAW_USB_VID_PID_LSB_RMSK)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_USB_VID_PID_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_USB_VID_PID_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_USB_VID_PID_LSB_ADDR,m,v,HWIO_QFPROM_RAW_USB_VID_PID_LSB_IN)
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_PID1_BMSK                                                                  0xffff0000
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_PID1_SHFT                                                                        0x10
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_PID0_BMSK                                                                      0xffff
#define HWIO_QFPROM_RAW_USB_VID_PID_LSB_PID0_SHFT                                                                         0x0

#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000043c)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000043c)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_RMSK                                                                       0x7f00ffff
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_USB_VID_PID_MSB_ADDR, HWIO_QFPROM_RAW_USB_VID_PID_MSB_RMSK)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_USB_VID_PID_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_USB_VID_PID_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_USB_VID_PID_MSB_ADDR,m,v,HWIO_QFPROM_RAW_USB_VID_PID_MSB_IN)
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_FEC_VALUE_BMSK                                                             0x7f000000
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_FEC_VALUE_SHFT                                                                   0x18
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_VID_BMSK                                                                       0xffff
#define HWIO_QFPROM_RAW_USB_VID_PID_MSB_VID_SHFT                                                                          0x0

#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000440)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000440)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_SW_CAL_REDUN_83_52_BMSK                                               0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_LSB_SW_CAL_REDUN_83_52_SHFT                                                      0x0

#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000444)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000444)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_SW_CAL_REDUN_115_84_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW0_MSB_SW_CAL_REDUN_115_84_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000448)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000448)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_CPR5_SVS2_QUOT_VMIN_0_BMSK                                            0x80000000
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_CPR5_SVS2_QUOT_VMIN_0_SHFT                                                  0x1f
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_SW_CAL_REDUN_146_116_BMSK                                             0x7fffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_LSB_SW_CAL_REDUN_146_116_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000044c)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000044c)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_UNUSED_BMSK                                                      0x80000000
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_UNUSED_SHFT                                                            0x1f
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_TURBO_QUOT_VMIN_BMSK                                             0x7f800000
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_TURBO_QUOT_VMIN_SHFT                                                   0x17
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_NOMINAL_QUOT_VMIN_BMSK                                             0x7f8000
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_NOMINAL_QUOT_VMIN_SHFT                                                  0xf
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_SVS_QUOT_VMIN_BMSK                                                   0x7f80
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_SVS_QUOT_VMIN_SHFT                                                      0x7
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_SVS2_QUOT_VMIN_7_1_BMSK                                                0x7f
#define HWIO_QFPROM_RAW_SPARE_REG27_ROW1_MSB_CPR5_SVS2_QUOT_VMIN_7_1_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000450)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000450)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR6_SVS_QUOT_VMIN_2_0_BMSK                                           0xe0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR6_SVS_QUOT_VMIN_2_0_SHFT                                                 0x1d
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR6_SVS2_QUOT_VMIN_BMSK                                              0x1fe00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR6_SVS2_QUOT_VMIN_SHFT                                                    0x15
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TURBO_ROSEL_BMSK                                                   0x1c0000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TURBO_ROSEL_SHFT                                                       0x12
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_TUR_BMSK                                                  0x3f000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_TUR_SHFT                                                      0xc
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_NOM_BMSK                                                    0xfc0
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_NOM_SHFT                                                      0x6
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_SVS_BMSK                                                     0x3f
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_SVS_SHFT                                                      0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000454)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000454)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_NOM_3_0_BMSK                                           0xf0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_NOM_3_0_SHFT                                                 0x1c
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_SVS_BMSK                                                0xfc00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_SVS_SHFT                                                     0x16
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_UNUSED_BMSK                                                        0x200000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_UNUSED_SHFT                                                            0x15
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TURBO_QUOT_VMIN_BMSK                                               0x1fe000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_TURBO_QUOT_VMIN_SHFT                                                    0xd
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_NOMINAL_QUOT_VMIN_BMSK                                               0x1fe0
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_NOMINAL_QUOT_VMIN_SHFT                                                  0x5
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_SVS_QUOT_VMIN_7_3_BMSK                                                 0x1f
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW0_MSB_CPR6_SVS_QUOT_VMIN_7_3_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000458)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000458)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_NOM_1_0_BMSK                                    0xc0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                          0x1e
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                        0x3c000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                              0x1a
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_TUR_BMSK                                                0x3e00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_TUR_SHFT                                                     0x15
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_NOM_BMSK                                                 0x1f0000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_NOM_SHFT                                                     0x10
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_SVS_BMSK                                                   0xf800
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_SVS_SHFT                                                      0xb
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TURBO_ROSEL_BMSK                                                      0x700
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TURBO_ROSEL_SHFT                                                        0x8
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_TUR_BMSK                                                     0xfc
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_TUR_SHFT                                                      0x2
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_NOM_5_4_BMSK                                                  0x3
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_NOM_5_4_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000045c)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000045c)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_SVS_2_0_BMSK                                    0xe0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_SVS_2_0_SHFT                                          0x1d
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                        0x1e000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                              0x19
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                                         0x1e00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                              0x15
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_TUR_BMSK                                                 0x1f0000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_TUR_SHFT                                                     0x10
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_NOM_BMSK                                                   0xf800
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_NOM_SHFT                                                      0xb
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_SVS_BMSK                                                    0x7c0
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_SVS_SHFT                                                      0x6
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                              0x3c
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                               0x2
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_NOM_3_2_BMSK                                           0x3
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_NOM_3_2_SHFT                                           0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000460)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000460)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR3_TARG_VOLT_SVS_3_0_BMSK                                           0xf0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR3_TARG_VOLT_SVS_3_0_SHFT                                                 0x1c
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                         0xf000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                              0x18
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                          0xf00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                              0x14
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                           0xf0000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                              0x10
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_TUR_BMSK                                                   0xf800
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_TUR_SHFT                                                      0xb
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_NOM_BMSK                                                    0x7c0
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_NOM_SHFT                                                      0x6
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_SVS_BMSK                                                     0x3e
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_SVS_SHFT                                                      0x1
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR1_TARG_VOLT_OFFSET_SVS_3_BMSK                                             0x1
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_LSB_CPR1_TARG_VOLT_OFFSET_SVS_3_SHFT                                             0x0

#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000464)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000464)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_SW_CAL_REDUN_SEL_BMSK                                                 0xe0000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_SW_CAL_REDUN_SEL_SHFT                                                       0x1d
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                        0x1e000000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                              0x19
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                         0x1e00000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                              0x15
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_TUR_BMSK                                                 0x1f0000
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_TUR_SHFT                                                     0x10
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_NOM_BMSK                                                   0xf800
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_NOM_SHFT                                                      0xb
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_TUR_BMSK                                                    0x7c0
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_TUR_SHFT                                                      0x6
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_NOM_BMSK                                                     0x3e
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_NOM_SHFT                                                      0x1
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_SVS_4_BMSK                                                    0x1
#define HWIO_QFPROM_RAW_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_SVS_4_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_ADDR                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000468)
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_OFFS                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000468)
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_RMSK                                                                          0xffffffff
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KSV_LSB_ADDR, HWIO_QFPROM_RAW_HDCP_KSV_LSB_RMSK)
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KSV_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_KSV0_BMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_HDCP_KSV_LSB_KSV0_SHFT                                                                            0x0

#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_ADDR                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000046c)
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_OFFS                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000046c)
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_RMSK                                                                          0x7f0000ff
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KSV_MSB_ADDR, HWIO_QFPROM_RAW_HDCP_KSV_MSB_RMSK)
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KSV_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_FEC_VALUE_BMSK                                                                0x7f000000
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_FEC_VALUE_SHFT                                                                      0x18
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_KSV1_BMSK                                                                           0xff
#define HWIO_QFPROM_RAW_HDCP_KSV_MSB_KSV1_SHFT                                                                            0x0

#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_ADDR(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000468 + 0x8 * (n))
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_OFFS(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000468 + 0x8 * (n))
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_RMSK                                                                     0xffffffff
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_MAXn                                                                             40
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_KEY_DATA_BMSK                                                            0xffffffff
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_LSB_KEY_DATA_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_ADDR(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000046c + 0x8 * (n))
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_OFFS(n)                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000046c + 0x8 * (n))
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_RMSK                                                                     0x7fffffff
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_MAXn                                                                             40
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_FEC_VALUE_BMSK                                                           0x7f000000
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_FEC_VALUE_SHFT                                                                 0x18
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_KEY_DATA_BMSK                                                              0xffffff
#define HWIO_QFPROM_RAW_HDCP_KEY_ROWn_MSB_KEY_DATA_SHFT                                                                   0x0

#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000005b0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_OFFS(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000005b0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_RMSK                                                               0xffffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_MAXn                                                                       36
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_KEY_DATA_BMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_LSB_KEY_DATA_SHFT                                                             0x0

#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000005b4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_OFFS(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000005b4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_RMSK                                                               0x7fffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_MAXn                                                                       36
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_FEC_VALUE_BMSK                                                     0x7f000000
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_FEC_VALUE_SHFT                                                           0x18
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_KEY_DATA_BMSK                                                        0xffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY0_ROWn_MSB_KEY_DATA_SHFT                                                             0x0

#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000006d8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_OFFS(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000006d8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_RMSK                                                               0xffffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_MAXn                                                                       36
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_KEY_DATA_BMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_LSB_KEY_DATA_SHFT                                                             0x0

#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000006dc + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_OFFS(n)                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000006dc + 0x8 * (n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_RMSK                                                               0x7fffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_MAXn                                                                       36
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_FEC_VALUE_BMSK                                                     0x7f000000
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_FEC_VALUE_SHFT                                                           0x18
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_KEY_DATA_BMSK                                                        0xffffff
#define HWIO_QFPROM_RAW_CUST_PRIV_KEY1_ROWn_MSB_KEY_DATA_SHFT                                                             0x0

#define HWIO_ACC_IR_ADDR                                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002000)
#define HWIO_ACC_IR_OFFS                                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002000)
#define HWIO_ACC_IR_RMSK                                                                                                 0x1f
#define HWIO_ACC_IR_OUT(v)      \
        out_dword(HWIO_ACC_IR_ADDR,v)
#define HWIO_ACC_IR_INSTRUCTION_BMSK                                                                                     0x1f
#define HWIO_ACC_IR_INSTRUCTION_SHFT                                                                                      0x0

#define HWIO_ACC_DR_ADDR                                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002004)
#define HWIO_ACC_DR_OFFS                                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002004)
#define HWIO_ACC_DR_RMSK                                                                                           0xffffffff
#define HWIO_ACC_DR_IN          \
        in_dword_masked(HWIO_ACC_DR_ADDR, HWIO_ACC_DR_RMSK)
#define HWIO_ACC_DR_INM(m)      \
        in_dword_masked(HWIO_ACC_DR_ADDR, m)
#define HWIO_ACC_DR_OUT(v)      \
        out_dword(HWIO_ACC_DR_ADDR,v)
#define HWIO_ACC_DR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACC_DR_ADDR,m,v,HWIO_ACC_DR_IN)
#define HWIO_ACC_DR_DR_BMSK                                                                                        0xffffffff
#define HWIO_ACC_DR_DR_SHFT                                                                                               0x0

#define HWIO_ACC_VERID_ADDR                                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002008)
#define HWIO_ACC_VERID_OFFS                                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002008)
#define HWIO_ACC_VERID_RMSK                                                                                            0xffff
#define HWIO_ACC_VERID_IN          \
        in_dword_masked(HWIO_ACC_VERID_ADDR, HWIO_ACC_VERID_RMSK)
#define HWIO_ACC_VERID_INM(m)      \
        in_dword_masked(HWIO_ACC_VERID_ADDR, m)
#define HWIO_ACC_VERID_FWVERID_BMSK                                                                                    0xff00
#define HWIO_ACC_VERID_FWVERID_SHFT                                                                                       0x8
#define HWIO_ACC_VERID_HWVERID_BMSK                                                                                      0xff
#define HWIO_ACC_VERID_HWVERID_SHFT                                                                                       0x0

#define HWIO_ACC_FEATSETn_ADDR(n)                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002010 + 0x4 * (n))
#define HWIO_ACC_FEATSETn_OFFS(n)                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002010 + 0x4 * (n))
#define HWIO_ACC_FEATSETn_RMSK                                                                                     0xffffffff
#define HWIO_ACC_FEATSETn_MAXn                                                                                              7
#define HWIO_ACC_FEATSETn_INI(n)        \
        in_dword_masked(HWIO_ACC_FEATSETn_ADDR(n), HWIO_ACC_FEATSETn_RMSK)
#define HWIO_ACC_FEATSETn_INMI(n,mask)    \
        in_dword_masked(HWIO_ACC_FEATSETn_ADDR(n), mask)
#define HWIO_ACC_FEATSETn_FEAT_BMSK                                                                                0xffffffff
#define HWIO_ACC_FEATSETn_FEAT_SHFT                                                                                       0x0

#define HWIO_QFPROM_BLOW_TIMER_ADDR                                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002038)
#define HWIO_QFPROM_BLOW_TIMER_OFFS                                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002038)
#define HWIO_QFPROM_BLOW_TIMER_RMSK                                                                                     0xfff
#define HWIO_QFPROM_BLOW_TIMER_IN          \
        in_dword_masked(HWIO_QFPROM_BLOW_TIMER_ADDR, HWIO_QFPROM_BLOW_TIMER_RMSK)
#define HWIO_QFPROM_BLOW_TIMER_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BLOW_TIMER_ADDR, m)
#define HWIO_QFPROM_BLOW_TIMER_OUT(v)      \
        out_dword(HWIO_QFPROM_BLOW_TIMER_ADDR,v)
#define HWIO_QFPROM_BLOW_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_BLOW_TIMER_ADDR,m,v,HWIO_QFPROM_BLOW_TIMER_IN)
#define HWIO_QFPROM_BLOW_TIMER_BLOW_TIMER_BMSK                                                                          0xfff
#define HWIO_QFPROM_BLOW_TIMER_BLOW_TIMER_SHFT                                                                            0x0

#define HWIO_QFPROM_TEST_CTRL_ADDR                                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000203c)
#define HWIO_QFPROM_TEST_CTRL_OFFS                                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000203c)
#define HWIO_QFPROM_TEST_CTRL_RMSK                                                                                        0xf
#define HWIO_QFPROM_TEST_CTRL_IN          \
        in_dword_masked(HWIO_QFPROM_TEST_CTRL_ADDR, HWIO_QFPROM_TEST_CTRL_RMSK)
#define HWIO_QFPROM_TEST_CTRL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_TEST_CTRL_ADDR, m)
#define HWIO_QFPROM_TEST_CTRL_OUT(v)      \
        out_dword(HWIO_QFPROM_TEST_CTRL_ADDR,v)
#define HWIO_QFPROM_TEST_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_TEST_CTRL_ADDR,m,v,HWIO_QFPROM_TEST_CTRL_IN)
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_BMSK                                                                            0x8
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_SHFT                                                                            0x3
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_BMSK                                                                             0x4
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_SHFT                                                                             0x2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_BMSK                                                                             0x2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_SHFT                                                                             0x1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_BMSK                                                                       0x1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_SHFT                                                                       0x0

#define HWIO_QFPROM_ACCEL_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002040)
#define HWIO_QFPROM_ACCEL_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002040)
#define HWIO_QFPROM_ACCEL_RMSK                                                                                          0xfff
#define HWIO_QFPROM_ACCEL_IN          \
        in_dword_masked(HWIO_QFPROM_ACCEL_ADDR, HWIO_QFPROM_ACCEL_RMSK)
#define HWIO_QFPROM_ACCEL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_ACCEL_ADDR, m)
#define HWIO_QFPROM_ACCEL_OUT(v)      \
        out_dword(HWIO_QFPROM_ACCEL_ADDR,v)
#define HWIO_QFPROM_ACCEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_ACCEL_ADDR,m,v,HWIO_QFPROM_ACCEL_IN)
#define HWIO_QFPROM_ACCEL_QFPROM_GATELAST_BMSK                                                                          0x800
#define HWIO_QFPROM_ACCEL_QFPROM_GATELAST_SHFT                                                                            0xb
#define HWIO_QFPROM_ACCEL_QFPROM_TRIPPT_SEL_BMSK                                                                        0x700
#define HWIO_QFPROM_ACCEL_QFPROM_TRIPPT_SEL_SHFT                                                                          0x8
#define HWIO_QFPROM_ACCEL_QFPROM_ACCEL_BMSK                                                                              0xff
#define HWIO_QFPROM_ACCEL_QFPROM_ACCEL_SHFT                                                                               0x0

#define HWIO_ACC_STATE_ADDR                                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002044)
#define HWIO_ACC_STATE_OFFS                                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002044)
#define HWIO_ACC_STATE_RMSK                                                                                               0x7
#define HWIO_ACC_STATE_IN          \
        in_dword_masked(HWIO_ACC_STATE_ADDR, HWIO_ACC_STATE_RMSK)
#define HWIO_ACC_STATE_INM(m)      \
        in_dword_masked(HWIO_ACC_STATE_ADDR, m)
#define HWIO_ACC_STATE_ACC_READY_BMSK                                                                                     0x4
#define HWIO_ACC_STATE_ACC_READY_SHFT                                                                                     0x2
#define HWIO_ACC_STATE_ACC_LOCKED_BMSK                                                                                    0x2
#define HWIO_ACC_STATE_ACC_LOCKED_SHFT                                                                                    0x1
#define HWIO_ACC_STATE_ACC_STOP_BMSK                                                                                      0x1
#define HWIO_ACC_STATE_ACC_STOP_SHFT                                                                                      0x0

#define HWIO_QFPROM_BLOW_STATUS_ADDR                                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002048)
#define HWIO_QFPROM_BLOW_STATUS_OFFS                                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002048)
#define HWIO_QFPROM_BLOW_STATUS_RMSK                                                                                      0x3
#define HWIO_QFPROM_BLOW_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM_BLOW_STATUS_ADDR, HWIO_QFPROM_BLOW_STATUS_RMSK)
#define HWIO_QFPROM_BLOW_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BLOW_STATUS_ADDR, m)
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_BMSK                                                                        0x2
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_SHFT                                                                        0x1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_BMSK                                                                          0x1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_SHFT                                                                          0x0

#define HWIO_HW_KEY_STATUS_ADDR                                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000204c)
#define HWIO_HW_KEY_STATUS_OFFS                                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000204c)
#define HWIO_HW_KEY_STATUS_RMSK                                                                                          0x1f
#define HWIO_HW_KEY_STATUS_IN          \
        in_dword_masked(HWIO_HW_KEY_STATUS_ADDR, HWIO_HW_KEY_STATUS_RMSK)
#define HWIO_HW_KEY_STATUS_INM(m)      \
        in_dword_masked(HWIO_HW_KEY_STATUS_ADDR, m)
#define HWIO_HW_KEY_STATUS_KDF_DONE_BMSK                                                                                 0x10
#define HWIO_HW_KEY_STATUS_KDF_DONE_SHFT                                                                                  0x4
#define HWIO_HW_KEY_STATUS_MSA_KEYS_BLOCKED_BMSK                                                                          0x8
#define HWIO_HW_KEY_STATUS_MSA_KEYS_BLOCKED_SHFT                                                                          0x3
#define HWIO_HW_KEY_STATUS_APPS_KEYS_BLOCKED_BMSK                                                                         0x4
#define HWIO_HW_KEY_STATUS_APPS_KEYS_BLOCKED_SHFT                                                                         0x2
#define HWIO_HW_KEY_STATUS_SEC_KEY_DERIVATION_KEY_BLOWN_BMSK                                                              0x2
#define HWIO_HW_KEY_STATUS_SEC_KEY_DERIVATION_KEY_BLOWN_SHFT                                                              0x1
#define HWIO_HW_KEY_STATUS_PRI_KEY_DERIVATION_KEY_BLOWN_BMSK                                                              0x1
#define HWIO_HW_KEY_STATUS_PRI_KEY_DERIVATION_KEY_BLOWN_SHFT                                                              0x0

#define HWIO_QFPROM_BIST_CTRL_ADDR                                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002050)
#define HWIO_QFPROM_BIST_CTRL_OFFS                                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002050)
#define HWIO_QFPROM_BIST_CTRL_RMSK                                                                                       0x7f
#define HWIO_QFPROM_BIST_CTRL_IN          \
        in_dword_masked(HWIO_QFPROM_BIST_CTRL_ADDR, HWIO_QFPROM_BIST_CTRL_RMSK)
#define HWIO_QFPROM_BIST_CTRL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BIST_CTRL_ADDR, m)
#define HWIO_QFPROM_BIST_CTRL_OUT(v)      \
        out_dword(HWIO_QFPROM_BIST_CTRL_ADDR,v)
#define HWIO_QFPROM_BIST_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_BIST_CTRL_ADDR,m,v,HWIO_QFPROM_BIST_CTRL_IN)
#define HWIO_QFPROM_BIST_CTRL_AUTH_REGION_BMSK                                                                           0x7c
#define HWIO_QFPROM_BIST_CTRL_AUTH_REGION_SHFT                                                                            0x2
#define HWIO_QFPROM_BIST_CTRL_SHA_ENABLE_BMSK                                                                             0x2
#define HWIO_QFPROM_BIST_CTRL_SHA_ENABLE_SHFT                                                                             0x1
#define HWIO_QFPROM_BIST_CTRL_START_BMSK                                                                                  0x1
#define HWIO_QFPROM_BIST_CTRL_START_SHFT                                                                                  0x0

#define HWIO_QFPROM_BIST_ERROR_ADDR                                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002054)
#define HWIO_QFPROM_BIST_ERROR_OFFS                                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002054)
#define HWIO_QFPROM_BIST_ERROR_RMSK                                                                                0xffffffff
#define HWIO_QFPROM_BIST_ERROR_IN          \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR_ADDR, HWIO_QFPROM_BIST_ERROR_RMSK)
#define HWIO_QFPROM_BIST_ERROR_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR_ADDR, m)
#define HWIO_QFPROM_BIST_ERROR_ERROR_BMSK                                                                          0xffffffff
#define HWIO_QFPROM_BIST_ERROR_ERROR_SHFT                                                                                 0x0

#define HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n)                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002060 + 0x4 * (n))
#define HWIO_QFPROM_HASH_SIGNATUREn_OFFS(n)                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002060 + 0x4 * (n))
#define HWIO_QFPROM_HASH_SIGNATUREn_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_HASH_SIGNATUREn_MAXn                                                                                    7
#define HWIO_QFPROM_HASH_SIGNATUREn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n), HWIO_QFPROM_HASH_SIGNATUREn_RMSK)
#define HWIO_QFPROM_HASH_SIGNATUREn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n), mask)
#define HWIO_QFPROM_HASH_SIGNATUREn_HASH_VALUE_BMSK                                                                0xffffffff
#define HWIO_QFPROM_HASH_SIGNATUREn_HASH_VALUE_SHFT                                                                       0x0

#define HWIO_FEC_ESR_ADDR                                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002080)
#define HWIO_FEC_ESR_OFFS                                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002080)
#define HWIO_FEC_ESR_RMSK                                                                                               0xfff
#define HWIO_FEC_ESR_IN          \
        in_dword_masked(HWIO_FEC_ESR_ADDR, HWIO_FEC_ESR_RMSK)
#define HWIO_FEC_ESR_INM(m)      \
        in_dword_masked(HWIO_FEC_ESR_ADDR, m)
#define HWIO_FEC_ESR_OUT(v)      \
        out_dword(HWIO_FEC_ESR_ADDR,v)
#define HWIO_FEC_ESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FEC_ESR_ADDR,m,v,HWIO_FEC_ESR_IN)
#define HWIO_FEC_ESR_CORR_SW_ACC_BMSK                                                                                   0x800
#define HWIO_FEC_ESR_CORR_SW_ACC_SHFT                                                                                     0xb
#define HWIO_FEC_ESR_CORR_HDCP_BMSK                                                                                     0x400
#define HWIO_FEC_ESR_CORR_HDCP_SHFT                                                                                       0xa
#define HWIO_FEC_ESR_CORR_BOOT_ROM_BMSK                                                                                 0x200
#define HWIO_FEC_ESR_CORR_BOOT_ROM_SHFT                                                                                   0x9
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_BMSK                                                                               0x100
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_SHFT                                                                                 0x8
#define HWIO_FEC_ESR_CORR_MULT_BMSK                                                                                      0x80
#define HWIO_FEC_ESR_CORR_MULT_SHFT                                                                                       0x7
#define HWIO_FEC_ESR_CORR_SEEN_BMSK                                                                                      0x40
#define HWIO_FEC_ESR_CORR_SEEN_SHFT                                                                                       0x6
#define HWIO_FEC_ESR_ERR_SW_ACC_BMSK                                                                                     0x20
#define HWIO_FEC_ESR_ERR_SW_ACC_SHFT                                                                                      0x5
#define HWIO_FEC_ESR_ERR_HDCP_BMSK                                                                                       0x10
#define HWIO_FEC_ESR_ERR_HDCP_SHFT                                                                                        0x4
#define HWIO_FEC_ESR_ERR_BOOT_ROM_BMSK                                                                                    0x8
#define HWIO_FEC_ESR_ERR_BOOT_ROM_SHFT                                                                                    0x3
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_BMSK                                                                                  0x4
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_SHFT                                                                                  0x2
#define HWIO_FEC_ESR_ERR_MULT_BMSK                                                                                        0x2
#define HWIO_FEC_ESR_ERR_MULT_SHFT                                                                                        0x1
#define HWIO_FEC_ESR_ERR_SEEN_BMSK                                                                                        0x1
#define HWIO_FEC_ESR_ERR_SEEN_SHFT                                                                                        0x0

#define HWIO_FEC_EAR_ADDR                                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002084)
#define HWIO_FEC_EAR_OFFS                                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002084)
#define HWIO_FEC_EAR_RMSK                                                                                          0xffffffff
#define HWIO_FEC_EAR_IN          \
        in_dword_masked(HWIO_FEC_EAR_ADDR, HWIO_FEC_EAR_RMSK)
#define HWIO_FEC_EAR_INM(m)      \
        in_dword_masked(HWIO_FEC_EAR_ADDR, m)
#define HWIO_FEC_EAR_CORR_ADDR_BMSK                                                                                0xffff0000
#define HWIO_FEC_EAR_CORR_ADDR_SHFT                                                                                      0x10
#define HWIO_FEC_EAR_ERR_ADDR_BMSK                                                                                     0xffff
#define HWIO_FEC_EAR_ERR_ADDR_SHFT                                                                                        0x0

#define HWIO_RESET_JDR_STATUS_ADDR                                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002088)
#define HWIO_RESET_JDR_STATUS_OFFS                                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002088)
#define HWIO_RESET_JDR_STATUS_RMSK                                                                                        0x3
#define HWIO_RESET_JDR_STATUS_IN          \
        in_dword_masked(HWIO_RESET_JDR_STATUS_ADDR, HWIO_RESET_JDR_STATUS_RMSK)
#define HWIO_RESET_JDR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RESET_JDR_STATUS_ADDR, m)
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_BMSK                                                                            0x2
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_SHFT                                                                            0x1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_BMSK                                                                   0x1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_SHFT                                                                   0x0

#define HWIO_QFPROM_ROM_ERROR_ADDR                                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002090)
#define HWIO_QFPROM_ROM_ERROR_OFFS                                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002090)
#define HWIO_QFPROM_ROM_ERROR_RMSK                                                                                        0x1
#define HWIO_QFPROM_ROM_ERROR_IN          \
        in_dword_masked(HWIO_QFPROM_ROM_ERROR_ADDR, HWIO_QFPROM_ROM_ERROR_RMSK)
#define HWIO_QFPROM_ROM_ERROR_INM(m)      \
        in_dword_masked(HWIO_QFPROM_ROM_ERROR_ADDR, m)
#define HWIO_QFPROM_ROM_ERROR_ERROR_BMSK                                                                                  0x1
#define HWIO_QFPROM_ROM_ERROR_ERROR_SHFT                                                                                  0x0

#define HWIO_QFPROM0_MATCH_STATUS_ADDR                                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002094)
#define HWIO_QFPROM0_MATCH_STATUS_OFFS                                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002094)
#define HWIO_QFPROM0_MATCH_STATUS_RMSK                                                                             0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM0_MATCH_STATUS_ADDR, HWIO_QFPROM0_MATCH_STATUS_RMSK)
#define HWIO_QFPROM0_MATCH_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM0_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_BMSK                                                                        0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_SHFT                                                                               0x0

#define HWIO_QFPROM1_MATCH_STATUS_ADDR                                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002098)
#define HWIO_QFPROM1_MATCH_STATUS_OFFS                                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002098)
#define HWIO_QFPROM1_MATCH_STATUS_RMSK                                                                             0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM1_MATCH_STATUS_ADDR, HWIO_QFPROM1_MATCH_STATUS_RMSK)
#define HWIO_QFPROM1_MATCH_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM1_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_BMSK                                                                        0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_SHFT                                                                               0x0

#define HWIO_QFPROM_CORR_ACC_PRIVATEn_ADDR(n)                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004000 + 0x4 * (n))
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_OFFS(n)                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004000 + 0x4 * (n))
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_MAXn                                                                                 39
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_ACC_PRIVATEn_ADDR(n), HWIO_QFPROM_CORR_ACC_PRIVATEn_RMSK)
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_ACC_PRIVATEn_ADDR(n), mask)
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_ACC_PRIVATE_BMSK                                                             0xffffffff
#define HWIO_QFPROM_CORR_ACC_PRIVATEn_ACC_PRIVATE_SHFT                                                                    0x0

#define HWIO_QFPROM_CORR_JTAG_ID_LSB_ADDR                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040a0)
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_OFFS                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040a0)
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_RMSK                                                                           0xfffffff
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_JTAG_ID_LSB_ADDR, HWIO_QFPROM_CORR_JTAG_ID_LSB_RMSK)
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_JTAG_ID_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_FEATURE_ID_BMSK                                                                0xff00000
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_FEATURE_ID_SHFT                                                                     0x14
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_JTAG_ID_BMSK                                                                     0xfffff
#define HWIO_QFPROM_CORR_JTAG_ID_LSB_JTAG_ID_SHFT                                                                         0x0

#define HWIO_QFPROM_CORR_JTAG_ID_MSB_ADDR                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040a4)
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_OFFS                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040a4)
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_RMSK                                                                          0xffffffff
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_JTAG_ID_MSB_ADDR, HWIO_QFPROM_CORR_JTAG_ID_MSB_RMSK)
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_JTAG_ID_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_QFPROM_CORR_JTAG_ID_MSB_BMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_JTAG_ID_MSB_QFPROM_CORR_JTAG_ID_MSB_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040a8)
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040a8)
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_RD_WR_PERM_LSB_ADDR, HWIO_QFPROM_CORR_RD_WR_PERM_LSB_RMSK)
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_RD_WR_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_PRIV_KEY1_BMSK                                                        0x80000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_PRIV_KEY1_SHFT                                                              0x1f
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_PRIV_KEY0_BMSK                                                        0x40000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_PRIV_KEY0_SHFT                                                              0x1e
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_HDCP_KEY_BMSK                                                              0x20000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_HDCP_KEY_SHFT                                                                    0x1d
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE28_BMSK                                                               0x10000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE28_SHFT                                                                     0x1c
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE27_BMSK                                                                0x8000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE27_SHFT                                                                     0x1b
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_USB_VID_PID_BMSK                                                            0x4000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_USB_VID_PID_SHFT                                                                 0x1a
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_QC_SEC_BOOT_BMSK                                                            0x2000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_QC_SEC_BOOT_SHFT                                                                 0x19
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_SEC_BOOT_BMSK                                                           0x1000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_SEC_BOOT_SHFT                                                                0x18
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_PK_HASH_BMSK                                                             0x800000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_PK_HASH_SHFT                                                                 0x17
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                                  0x400000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                                      0x16
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                                  0x200000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                                      0x15
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_BOOT_ROM_PATCH_BMSK                                                          0x100000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_BOOT_ROM_PATCH_SHFT                                                              0x14
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE19_BMSK                                                                  0x80000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SPARE19_SHFT                                                                     0x13
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SERIAL_NUM_BMSK                                                               0x40000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_SERIAL_NUM_SHFT                                                                  0x12
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_KEY_BMSK                                                                 0x20000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CUST_KEY_SHFT                                                                    0x11
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_INTAGLIO_GLUEBIT_BMSK                                                         0x10000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_INTAGLIO_GLUEBIT_SHFT                                                            0x10
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_FEC_EN_BMSK                                                                    0x8000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_FEC_EN_SHFT                                                                       0xf
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CALIB_BMSK                                                                     0x4000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_CALIB_SHFT                                                                        0xe
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MEM_ACCEL_BMSK                                                                 0x2000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MEM_ACCEL_SHFT                                                                    0xd
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_DEBUG_KEY_BMSK                                                                 0x1000
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_DEBUG_KEY_SHFT                                                                    0xc
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MEM_REDUN_BMSK                                                                  0x800
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MEM_REDUN_SHFT                                                                    0xb
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_FEAT_CONFIG_BMSK                                                                0x400
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_FEAT_CONFIG_SHFT                                                                  0xa
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_CONFIG_BMSK                                                                 0x200
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_OEM_CONFIG_SHFT                                                                   0x9
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN2_BMSK                                                                  0x100
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN2_SHFT                                                                    0x8
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN1_BMSK                                                                   0x80
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN1_SHFT                                                                    0x7
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN0_BMSK                                                                   0x40
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IMEI_ESN0_SHFT                                                                    0x6
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MSA_ANTI_ROLLBACK_BMSK                                                           0x20
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_MSA_ANTI_ROLLBACK_SHFT                                                            0x5
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_AP_ANTI_ROLLBACK_BMSK                                                            0x10
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_AP_ANTI_ROLLBACK_SHFT                                                             0x4
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_PTE_BMSK                                                                          0x8
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_PTE_SHFT                                                                          0x3
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_RD_WR_PERM_BMSK                                                                   0x4
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_RD_WR_PERM_SHFT                                                                   0x2
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_JTAG_ID_BMSK                                                                      0x2
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_JTAG_ID_SHFT                                                                      0x1
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_ACC_PRIVATE_BMSK                                                                  0x1
#define HWIO_QFPROM_CORR_RD_WR_PERM_LSB_ACC_PRIVATE_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040ac)
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040ac)
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_RD_WR_PERM_MSB_ADDR, HWIO_QFPROM_CORR_RD_WR_PERM_MSB_RMSK)
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_RD_WR_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_PRIV_KEY1_BMSK                                                        0x80000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_PRIV_KEY1_SHFT                                                              0x1f
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_PRIV_KEY0_BMSK                                                        0x40000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_PRIV_KEY0_SHFT                                                              0x1e
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_HDCP_KEY_BMSK                                                              0x20000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_HDCP_KEY_SHFT                                                                    0x1d
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE28_BMSK                                                               0x10000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE28_SHFT                                                                     0x1c
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE27_BMSK                                                                0x8000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE27_SHFT                                                                     0x1b
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_USB_VID_PID_BMSK                                                            0x4000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_USB_VID_PID_SHFT                                                                 0x1a
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_QC_SEC_BOOT_BMSK                                                            0x2000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_QC_SEC_BOOT_SHFT                                                                 0x19
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_SEC_BOOT_BMSK                                                           0x1000000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_SEC_BOOT_SHFT                                                                0x18
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_PK_HASH_BMSK                                                             0x800000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_PK_HASH_SHFT                                                                 0x17
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SEC_KEY_DERIVATION_KEY_BMSK                                                  0x400000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SEC_KEY_DERIVATION_KEY_SHFT                                                      0x16
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_PRI_KEY_DERIVATION_KEY_BMSK                                                  0x200000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_PRI_KEY_DERIVATION_KEY_SHFT                                                      0x15
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_BOOT_ROM_PATCH_BMSK                                                          0x100000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_BOOT_ROM_PATCH_SHFT                                                              0x14
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE19_BMSK                                                                  0x80000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SPARE19_SHFT                                                                     0x13
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SERIAL_NUM_BMSK                                                               0x40000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_SERIAL_NUM_SHFT                                                                  0x12
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_KEY_BMSK                                                                 0x20000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CUST_KEY_SHFT                                                                    0x11
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_INTAGLIO_GLUEBIT_BMSK                                                         0x10000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_INTAGLIO_GLUEBIT_SHFT                                                            0x10
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_FEC_EN_BMSK                                                                    0x8000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_FEC_EN_SHFT                                                                       0xf
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CALIB_BMSK                                                                     0x4000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_CALIB_SHFT                                                                        0xe
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MEM_ACCEL_BMSK                                                                 0x2000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MEM_ACCEL_SHFT                                                                    0xd
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_DEBUG_KEY_BMSK                                                                 0x1000
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_DEBUG_KEY_SHFT                                                                    0xc
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MEM_REDUN_BMSK                                                                  0x800
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MEM_REDUN_SHFT                                                                    0xb
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_FEAT_CONFIG_BMSK                                                                0x400
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_FEAT_CONFIG_SHFT                                                                  0xa
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_CONFIG_BMSK                                                                 0x200
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_OEM_CONFIG_SHFT                                                                   0x9
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN2_BMSK                                                                  0x100
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN2_SHFT                                                                    0x8
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN1_BMSK                                                                   0x80
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN1_SHFT                                                                    0x7
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN0_BMSK                                                                   0x40
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IMEI_ESN0_SHFT                                                                    0x6
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MSA_ANTI_ROLLBACK_BMSK                                                           0x20
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_MSA_ANTI_ROLLBACK_SHFT                                                            0x5
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_AP_ANTI_ROLLBACK_BMSK                                                            0x10
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_AP_ANTI_ROLLBACK_SHFT                                                             0x4
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_PTE_BMSK                                                                          0x8
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_PTE_SHFT                                                                          0x3
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_RD_WR_PERM_BMSK                                                                   0x4
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_RD_WR_PERM_SHFT                                                                   0x2
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_JTAG_ID_BMSK                                                                      0x2
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_JTAG_ID_SHFT                                                                      0x1
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_ACC_PRIVATE_BMSK                                                                  0x1
#define HWIO_QFPROM_CORR_RD_WR_PERM_MSB_ACC_PRIVATE_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_PTE_LSB_ADDR                                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040b0)
#define HWIO_QFPROM_CORR_PTE_LSB_OFFS                                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040b0)
#define HWIO_QFPROM_CORR_PTE_LSB_RMSK                                                                              0xffffffff
#define HWIO_QFPROM_CORR_PTE_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_LSB_ADDR, HWIO_QFPROM_CORR_PTE_LSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_LSB_PTE_DATA0_BMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_PTE_LSB_PTE_DATA0_SHFT                                                                           0x0

#define HWIO_QFPROM_CORR_PTE_MSB_ADDR                                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040b4)
#define HWIO_QFPROM_CORR_PTE_MSB_OFFS                                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040b4)
#define HWIO_QFPROM_CORR_PTE_MSB_RMSK                                                                              0xffffffff
#define HWIO_QFPROM_CORR_PTE_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_MSB_ADDR, HWIO_QFPROM_CORR_PTE_MSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_MSB_PTE_DATA1_BMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_PTE_MSB_PTE_DATA1_SHFT                                                                           0x0

#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040b8)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_OFFS                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040b8)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_RMSK                                                            0xffffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_TZ_BMSK                                                         0xffff0000
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_TZ_SHFT                                                               0x10
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_SBL1_BMSK                                                           0xffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_LSB_SBL1_SHFT                                                              0x0

#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040bc)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_OFFS                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040bc)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_RMSK                                                            0xffffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_PIL_SUBSYSTEM_31_0_BMSK                                         0xffffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW0_MSB_PIL_SUBSYSTEM_31_0_SHFT                                                0x0

#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040c0)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_OFFS                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040c0)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_RMSK                                                            0xffffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_APPSBL0_BMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_LSB_APPSBL0_SHFT                                                           0x0

#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040c4)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_OFFS                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040c4)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_RMSK                                                             0x3ffffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_RPM_BMSK                                                         0x3fc0000
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_RPM_SHFT                                                              0x12
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_APPSBL1_BMSK                                                       0x3ffff
#define HWIO_QFPROM_CORR_AP_ANTI_ROLLBACK_ROW1_MSB_APPSBL1_SHFT                                                           0x0

#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040c8)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040c8)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_RMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_ADDR, HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_RMSK)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_MSS_BMSK                                                            0xffff0000
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_MSS_SHFT                                                                  0x10
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_MBA_BMSK                                                                0xffff
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_LSB_MBA_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040cc)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040cc)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_RMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_ADDR, HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_RMSK)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_BMSK                              0xffffffff
#define HWIO_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_QFPROM_CORR_MSA_ANTI_ROLLBACK_MSB_SHFT                                     0x0

#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040d0)
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040d0)
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN0_LSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN0_LSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS2_OFFSET_BMSK                                                          0xf0000000
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS2_OFFSET_SHFT                                                                0x1c
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS1_OFFSET_BMSK                                                           0xf000000
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS1_OFFSET_SHFT                                                                0x18
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS0_OFFSET_BMSK                                                            0xf00000
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS0_OFFSET_SHFT                                                                0x14
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS_BASE1_BMSK                                                               0xffc00
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS_BASE1_SHFT                                                                   0xa
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS_BASE0_BMSK                                                                 0x3ff
#define HWIO_QFPROM_CORR_IMEI_ESN0_LSB_TSENS_BASE0_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040d4)
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040d4)
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN0_MSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN0_MSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS10_OFFSET_BMSK                                                         0xf0000000
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS10_OFFSET_SHFT                                                               0x1c
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS9_OFFSET_BMSK                                                           0xf000000
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS9_OFFSET_SHFT                                                                0x18
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS8_OFFSET_BMSK                                                            0xf00000
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS8_OFFSET_SHFT                                                                0x14
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS7_OFFSET_BMSK                                                             0xf0000
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS7_OFFSET_SHFT                                                                0x10
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS6_OFFSET_BMSK                                                              0xf000
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS6_OFFSET_SHFT                                                                 0xc
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS5_OFFSET_BMSK                                                               0xf00
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS5_OFFSET_SHFT                                                                 0x8
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS4_OFFSET_BMSK                                                                0xf0
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS4_OFFSET_SHFT                                                                 0x4
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS3_OFFSET_BMSK                                                                 0xf
#define HWIO_QFPROM_CORR_IMEI_ESN0_MSB_TSENS3_OFFSET_SHFT                                                                 0x0

#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040d8)
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040d8)
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN1_LSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN1_LSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TXDAC1_CAL_0_BMSK                                                           0x80000000
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TXDAC1_CAL_0_SHFT                                                                 0x1f
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TXDAC0_CAL_BMSK                                                             0x7f800000
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TXDAC0_CAL_SHFT                                                                   0x17
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS_CAL_SEL_BMSK                                                            0x700000
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS_CAL_SEL_SHFT                                                                0x14
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS15_OFFSET_BMSK                                                            0xf0000
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS15_OFFSET_SHFT                                                               0x10
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS14_OFFSET_BMSK                                                             0xf000
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS14_OFFSET_SHFT                                                                0xc
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS13_OFFSET_BMSK                                                              0xf00
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS13_OFFSET_SHFT                                                                0x8
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS12_OFFSET_BMSK                                                               0xf0
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS12_OFFSET_SHFT                                                                0x4
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS11_OFFSET_BMSK                                                                0xf
#define HWIO_QFPROM_CORR_IMEI_ESN1_LSB_TSENS11_OFFSET_SHFT                                                                0x0

#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040dc)
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040dc)
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN1_MSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN1_MSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_SPARE0_BMSK                                                                 0xfffc0000
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_SPARE0_SHFT                                                                       0x12
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_VCM_BMSK                                                              0x30000
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_VCM_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_LDO_BMSK                                                               0xc000
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_LDO_SHFT                                                                  0xe
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_VREF_BMSK                                                              0x3000
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_GNSS_ADC_VREF_SHFT                                                                 0xc
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_AVG_ERR_BMSK                                                          0x800
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_AVG_ERR_SHFT                                                            0xb
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC0_CAL_AVG_ERR_BMSK                                                          0x400
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC0_CAL_AVG_ERR_SHFT                                                            0xa
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC_0_1_FLAG_BMSK                                                              0x200
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC_0_1_FLAG_SHFT                                                                0x9
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_OVFLOW_BMSK                                                           0x100
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_OVFLOW_SHFT                                                             0x8
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC0_CAL_OVFLOW_BMSK                                                            0x80
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC0_CAL_OVFLOW_SHFT                                                             0x7
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_7_1_BMSK                                                               0x7f
#define HWIO_QFPROM_CORR_IMEI_ESN1_MSB_TXDAC1_CAL_7_1_SHFT                                                                0x0

#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040e0)
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040e0)
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN2_LSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN2_LSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B1M1_BMSK                                                                0xe0000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B1M1_SHFT                                                                      0x1d
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B1M0_BMSK                                                                0x1c000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B1M0_SHFT                                                                      0x1a
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_G_B1_BMSK                                                                    0x3800000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_G_B1_SHFT                                                                         0x17
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_SAR_B1_BMSK                                                                   0x600000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_SAR_B1_SHFT                                                                       0x15
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_CLK_B0_BMSK                                                                   0x180000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_CLK_B0_SHFT                                                                       0x13
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_VREF_B0_BMSK                                                                   0x60000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_VREF_B0_SHFT                                                                      0x11
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M3_BMSK                                                                   0x1c000
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M3_SHFT                                                                       0xe
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M2_BMSK                                                                    0x3800
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M2_SHFT                                                                       0xb
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M1_BMSK                                                                     0x700
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M1_SHFT                                                                       0x8
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M0_BMSK                                                                      0xe0
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_PH_B0M0_SHFT                                                                       0x5
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_G_B0_BMSK                                                                         0x1c
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_G_B0_SHFT                                                                          0x2
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_SAR_B0_BMSK                                                                        0x3
#define HWIO_QFPROM_CORR_IMEI_ESN2_LSB_SAR_B0_SHFT                                                                        0x0

#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040e4)
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040e4)
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_RMSK                                                                        0xffff7fff
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN2_MSB_ADDR, HWIO_QFPROM_CORR_IMEI_ESN2_MSB_RMSK)
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMEI_ESN2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_SPARE0_BMSK                                                                 0x80000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_SPARE0_SHFT                                                                       0x1f
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_CLK_B2_BMSK                                                                 0x60000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_CLK_B2_SHFT                                                                       0x1d
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_VREF_B2_BMSK                                                                0x18000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_VREF_B2_SHFT                                                                      0x1b
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M3_BMSK                                                                 0x7000000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M3_SHFT                                                                      0x18
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M2_BMSK                                                                  0xe00000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M2_SHFT                                                                      0x15
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M1_BMSK                                                                  0x1c0000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M1_SHFT                                                                      0x12
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M0_BMSK                                                                   0x30000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B2M0_SHFT                                                                      0x10
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_G_B2_BMSK                                                                       0x7000
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_G_B2_SHFT                                                                          0xc
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_SAR_B2_BMSK                                                                      0xc00
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_SAR_B2_SHFT                                                                        0xa
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_CLK_B1_BMSK                                                                      0x300
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_CLK_B1_SHFT                                                                        0x8
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_VREF_B1_BMSK                                                                      0xc0
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_VREF_B1_SHFT                                                                       0x6
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B1M3_BMSK                                                                      0x38
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B1M3_SHFT                                                                       0x3
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B1M2_BMSK                                                                       0x7
#define HWIO_QFPROM_CORR_IMEI_ESN2_MSB_PH_B1M2_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040e8)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040e8)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_DISABLE_BMSK                                                   0x80000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_DISABLE_SHFT                                                         0x1f
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE0_DISABLE_BMSK                                                   0x40000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE0_DISABLE_SHFT                                                         0x1e
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_VENUS_0_DBGEN_DISABLE_BMSK                                            0x20000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_VENUS_0_DBGEN_DISABLE_SHFT                                                  0x1d
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_DAPEN_DISABLE_BMSK                                                0x10000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_DAPEN_DISABLE_SHFT                                                      0x1c
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                      0x8000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                           0x1b
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_DBGEN_DISABLE_BMSK                                                 0x4000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RPM_DBGEN_DISABLE_SHFT                                                      0x1a
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_WCSS_DBGEN_DISABLE_BMSK                                                0x2000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_WCSS_DBGEN_DISABLE_SHFT                                                     0x19
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_LPASS_DBGEN_DISABLE_BMSK                                               0x1000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_LPASS_DBGEN_DISABLE_SHFT                                                    0x18
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_NIDEN_DISABLE_BMSK                                                  0x800000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_NIDEN_DISABLE_SHFT                                                      0x17
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_DBGEN_DISABLE_BMSK                                                  0x400000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_DBGEN_DISABLE_SHFT                                                      0x16
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_BMSK                                                  0x200000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_SHFT                                                      0x15
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_BMSK                                                             0x180000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_SHFT                                                                 0x13
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_BMSK                                             0x40000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_SHFT                                                0x12
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALT_SD_PORT_FOR_BOOT_BMSK                                                0x20000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALT_SD_PORT_FOR_BOOT_SHFT                                                   0x11
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_GPIO_DISABLE_BMSK                                       0x10000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_GPIO_DISABLE_SHFT                                          0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_EN_BMSK                                                  0x8000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDC_EMMC_MODE1P2_EN_SHFT                                                     0xf
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FAST_BOOT_BMSK                                                            0x7c00
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FAST_BOOT_SHFT                                                               0xa
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDP_ENUM_SKIP_BMSK                                                         0x200
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDP_ENUM_SKIP_SHFT                                                           0x9
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_BMSK                                                   0x100
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_SHFT                                                     0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_PBL_BOOT_SPEED_BMSK                                                    0xc0
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_PBL_BOOT_SPEED_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_BMSK                                                 0x20
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_SHFT                                                  0x5
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE0_BMSK                                                                 0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE0_SHFT                                                                  0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_PMIC_POWER_DOWN_MSM_BMSK                                                 0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_PMIC_POWER_DOWN_MSM_SHFT                                                 0x3
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_USB_ENUM_TIMEOUT_BMSK                                                        0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_USB_ENUM_TIMEOUT_SHFT                                                        0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DLOAD_TIMEOUT_BMSK                                                           0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DLOAD_TIMEOUT_SHFT                                                           0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_BMSK                                                         0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040ec)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040ec)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WDOG_EN_BMSK                                                          0x80000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WDOG_EN_SHFT                                                                0x1f
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE2_BMSK                                                           0x40000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE2_SHFT                                                                 0x1e
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SCM_M1_RD_PERM_BMSK                                                   0x20000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SCM_M1_RD_PERM_SHFT                                                         0x1d
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_UFS_SCM_FORCE_EFUSE_KEY_BMSK                                          0x10000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_UFS_SCM_FORCE_EFUSE_KEY_SHFT                                                0x1c
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SDC2_SCM_FORCE_EFUSE_KEY_BMSK                                          0x8000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SDC2_SCM_FORCE_EFUSE_KEY_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPDM_SECURE_MODE_BMSK                                                  0x4000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPDM_SECURE_MODE_SHFT                                                       0x1a
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_IMEI_ESN_SELECT_BMSK                                                   0x3000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_IMEI_ESN_SELECT_SHFT                                                        0x18
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE1_BMSK                                                             0xc00000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE1_SHFT                                                                 0x16
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_CUST_PRIV_KEY_SELECT_BMSK                                               0x200000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_CUST_PRIV_KEY_SELECT_SHFT                                                   0x15
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SW_FUSE_PROG_DISABLE_BMSK                                               0x100000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SW_FUSE_PROG_DISABLE_SHFT                                                   0x14
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE0_BMSK                                                              0xfe000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE0_SHFT                                                                  0xd
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_SPNIDEN_DISABLE_BMSK                                                0x1000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_SPNIDEN_DISABLE_SHFT                                                   0xc
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_SPIDEN_DISABLE_BMSK                                                  0x800
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_SPIDEN_DISABLE_SHFT                                                    0xb
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_NIDEN_DISABLE_BMSK                                                   0x400
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_NIDEN_DISABLE_SHFT                                                     0xa
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_DBGEN_DISABLE_BMSK                                                   0x200
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS1_DBGEN_DISABLE_SHFT                                                     0x9
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_BMSK                                                  0x100
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_SHFT                                                    0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_BMSK                                                    0x80
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_SHFT                                                     0x7
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_BMSK                                                     0x40
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_SHFT                                                      0x6
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_BMSK                                                      0x20
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_SHFT                                                       0x5
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_BMSK                                                      0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_SHFT                                                       0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_SPNIDEN_DISABLE_BMSK                                                   0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_SPNIDEN_DISABLE_SHFT                                                   0x3
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_SPIDEN_DISABLE_BMSK                                                    0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_SPIDEN_DISABLE_SHFT                                                    0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_NIDEN_DISABLE_BMSK                                                     0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_NIDEN_DISABLE_SHFT                                                     0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_DBGEN_DISABLE_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS0_DBGEN_DISABLE_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040f0)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040f0)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_HW_ID_BMSK                                                        0xffff0000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_HW_ID_SHFT                                                              0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ANTI_ROLLBACK_FEATURE_EN_BMSK                                             0xff00
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ANTI_ROLLBACK_FEATURE_EN_SHFT                                                0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_SPARE0_BMSK                                                                 0xf0
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_SPARE0_SHFT                                                                  0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ROOT_CERT_TOTAL_NUM_BMSK                                                     0xf
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ROOT_CERT_TOTAL_NUM_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040f4)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040f4)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_SPARE0_BMSK                                                           0xffff0000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_SPARE0_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_BMSK                                                       0xffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040f8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040f8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                                    0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                                          0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_0_DISABLE_BMSK                                                   0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_0_DISABLE_SHFT                                                         0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                                   0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                                         0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                                   0x10000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                                         0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                                              0x8000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                                                   0x1b
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                                              0x4000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                                                   0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                                   0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                                        0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                                   0x1000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                                        0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_SPARE_DISABLE_BMSK                                               0xe00000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_SPARE_DISABLE_SHFT                                                   0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_UL_CA_DISABLE_BMSK                                           0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_UL_CA_DISABLE_SHFT                                               0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX3_DISABLE_BMSK                                                0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX3_DISABLE_SHFT                                                   0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX2_DISABLE_BMSK                                                0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_BBRX2_DISABLE_SHFT                                                   0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_GLOBAL_DISABLE_BMSK                                               0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_GLOBAL_DISABLE_SHFT                                                  0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DC_DISABLE_0_BMSK                                            0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DC_DISABLE_0_SHFT                                               0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_MIMO_DISABLE_0_BMSK                                           0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_MIMO_DISABLE_0_SHFT                                              0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT2_DISABLE_0_BMSK                                      0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT2_DISABLE_0_SHFT                                         0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT1_DISABLE_0_BMSK                                      0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_ABOVE_CAT1_DISABLE_0_SHFT                                         0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_TDSCDMA_DISABLE_0_BMSK                                             0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_TDSCDMA_DISABLE_0_SHFT                                                0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DISABLE_0_BMSK                                                 0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_HSPA_DISABLE_0_SHFT                                                   0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_DISABLE_0_BMSK                                                  0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_LTE_DISABLE_0_SHFT                                                    0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_WCDMA_DISABLE_0_BMSK                                                0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_WCDMA_DISABLE_0_SHFT                                                  0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_DO_DISABLE_0_BMSK                                                   0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_DO_DISABLE_0_SHFT                                                     0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_1X_DISABLE_0_BMSK                                                    0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MODEM_1X_DISABLE_0_SHFT                                                     0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_NAV_DISABLE_BMSK                                                           0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_NAV_DISABLE_SHFT                                                            0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_GERAN_DISABLE_0_BMSK                                                       0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_GERAN_DISABLE_0_SHFT                                                        0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_SPI_SLAVE_DISABLE_BMSK                                                     0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_SPI_SLAVE_DISABLE_SHFT                                                      0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_APPS_ACG_DISABLE_BMSK                                                       0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_APPS_ACG_DISABLE_SHFT                                                       0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040fc)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040fc)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENDOR_LOCK_BMSK                                                     0xf0000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENDOR_LOCK_SHFT                                                           0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_SDC_EMMC_MODE1P2_FORCE_GPIO_BMSK                                      0x8000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_SDC_EMMC_MODE1P2_FORCE_GPIO_SHFT                                           0x1b
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_DSDA_DISABLE_BMSK                                               0x4000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_DSDA_DISABLE_SHFT                                                    0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_60_MHZ_DISABLE_BMSK                                         0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_60_MHZ_DISABLE_SHFT                                              0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_40_MHZ_DISABLE_BMSK                                         0x1000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_40_MHZ_DISABLE_SHFT                                              0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DC_DISABLE_1_BMSK                                           0x800000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DC_DISABLE_1_SHFT                                               0x17
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_MIMO_DISABLE_1_BMSK                                         0x400000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_MIMO_DISABLE_1_SHFT                                             0x16
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT2_DISABLE_1_BMSK                                    0x200000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT2_DISABLE_1_SHFT                                        0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT1_DISABLE_1_BMSK                                    0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_ABOVE_CAT1_DISABLE_1_SHFT                                        0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_TDSCDMA_DISABLE_1_BMSK                                            0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_TDSCDMA_DISABLE_1_SHFT                                               0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DISABLE_1_BMSK                                               0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_HSPA_DISABLE_1_SHFT                                                  0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_DISABLE_1_BMSK                                                0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_LTE_DISABLE_1_SHFT                                                   0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_WCDMA_DISABLE_1_BMSK                                              0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_WCDMA_DISABLE_1_SHFT                                                 0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_DO_DISABLE_1_BMSK                                                  0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_DO_DISABLE_1_SHFT                                                     0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_1X_DISABLE_1_BMSK                                                  0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MODEM_1X_DISABLE_1_SHFT                                                     0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GERAN_DISABLE_1_BMSK                                                     0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GERAN_DISABLE_1_SHFT                                                        0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_UFS_SW_CONTROL_DISABLE_BMSK                                              0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_UFS_SW_CONTROL_DISABLE_SHFT                                                 0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PCIE_1_DISABLE_BMSK                                                       0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PCIE_1_DISABLE_SHFT                                                         0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PCIE_0_DISABLE_BMSK                                                       0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PCIE_0_DISABLE_SHFT                                                         0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_SATA_DISABLE_BMSK                                                         0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_SATA_DISABLE_SHFT                                                           0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ACC_DISABLE_BMSK                                                          0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ACC_DISABLE_SHFT                                                            0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL1_BMSK                                                      0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL1_SHFT                                                       0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL0_BMSK                                                      0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_SEL0_SHFT                                                       0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_DISABLE_BMSK                                                   0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GFX3D_TURBO_DISABLE_SHFT                                                    0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_DECODE_DISABLE_BMSK                                             0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_DECODE_DISABLE_SHFT                                              0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                                              0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                                              0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_4K_DISABLE_BMSK                                                       0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VENUS_4K_DISABLE_SHFT                                                       0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MDP_APICAL_LTC_DISABLE_BMSK                                                 0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MDP_APICAL_LTC_DISABLE_SHFT                                                 0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_HDMI_DISABLE_BMSK                                                           0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_HDMI_DISABLE_SHFT                                                           0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004100)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004100)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SCM_DISABLE_BMSK                                                     0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SCM_DISABLE_SHFT                                                           0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY1_BMSK                                               0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY1_SHFT                                                     0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY0_BMSK                                               0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_FORCE_HW_KEY0_SHFT                                                     0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_DISABLE_BMSK                                                     0x10000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ICE_DISABLE_SHFT                                                           0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_CSID_DPCM_14_DISABLE_BMSK                                             0x8000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_CSID_DPCM_14_DISABLE_SHFT                                                  0x1b
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_FD_DISABLE_BMSK                                                       0x4000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_FD_DISABLE_SHFT                                                            0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPNIDEN_DISABLE_BMSK                                         0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPNIDEN_DISABLE_SHFT                                              0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPIDEN_DISABLE_BMSK                                          0x1000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_SPIDEN_DISABLE_SHFT                                               0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_NIDEN_DISABLE_BMSK                                            0x800000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_NIDEN_DISABLE_SHFT                                                0x17
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_DBGEN_DISABLE_BMSK                                            0x400000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS1_DBGEN_DISABLE_SHFT                                                0x16
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                                           0x200000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                                               0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPNIDEN_DISABLE_BMSK                                            0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPNIDEN_DISABLE_SHFT                                                0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPIDEN_DISABLE_BMSK                                              0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_SPIDEN_DISABLE_SHFT                                                 0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_NIDEN_DISABLE_BMSK                                               0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_NIDEN_DISABLE_SHFT                                                  0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_DBGEN_DISABLE_BMSK                                               0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_DAP_DBGEN_DISABLE_SHFT                                                  0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPNIDEN_DISABLE_BMSK                                           0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPNIDEN_DISABLE_SHFT                                              0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPIDEN_DISABLE_BMSK                                             0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_SPIDEN_DISABLE_SHFT                                                0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_NIDEN_DISABLE_BMSK                                              0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_NIDEN_DISABLE_SHFT                                                 0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_DBGEN_DISABLE_BMSK                                              0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_APPS0_DBGEN_DISABLE_SHFT                                                 0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_SPARE1_DISABLE_BMSK                                                   0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_SPARE1_DISABLE_SHFT                                                      0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_SPARE0_DISABLE_BMSK                                                    0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_SPARE0_DISABLE_SHFT                                                      0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                                             0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                                               0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_DAPEN_DISABLE_BMSK                                                 0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_DAPEN_DISABLE_SHFT                                                   0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                      0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                        0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_DBGEN_DISABLE_BMSK                                                  0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_RPM_DBGEN_DISABLE_SHFT                                                   0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                                                 0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                                                  0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_LPASS_DBGEN_DISABLE_BMSK                                                0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_LPASS_DBGEN_DISABLE_SHFT                                                 0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_MSS_NIDEN_DISABLE_BMSK                                                  0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_MSS_NIDEN_DISABLE_SHFT                                                   0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_MSS_DBGEN_DISABLE_BMSK                                                   0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_QC_MSS_DBGEN_DISABLE_SHFT                                                   0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MOCHA_PART_BMSK                                                             0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MOCHA_PART_SHFT                                                             0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SM_BIST_DISABLE_BMSK                                                        0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SM_BIST_DISABLE_SHFT                                                        0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_TIC_DISABLE_BMSK                                                            0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_TIC_DISABLE_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004104)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004104)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SEC_TAP_ACCESS_DISABLE_BMSK                                          0xfffc0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SEC_TAP_ACCESS_DISABLE_SHFT                                                0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_TAP_CJI_CORE_SEL_DISABLE_BMSK                                           0x3c000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_TAP_CJI_CORE_SEL_DISABLE_SHFT                                               0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_TAP_INSTR_DISABLE_BMSK                                                   0x3fff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_TAP_INSTR_DISABLE_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004108)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004108)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TAP_GEN_SPARE_INSTR_DISABLE_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TAP_GEN_SPARE_INSTR_DISABLE_SHFT                                            0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000410c)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000410c)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SW_EXPANSION_FUSES_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SW_EXPANSION_FUSES_SHFT                                                    0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CFGCPUPRESENT_N_BMSK                                              0xff0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CFGCPUPRESENT_N_SHFT                                                  0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION3_BMSK                                                 0xf000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION3_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION2_BMSK                                                  0xf00
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION2_SHFT                                                    0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION1_BMSK                                                   0xf0
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION1_SHFT                                                    0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION0_BMSK                                                    0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_CONFIGURATION0_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004110)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004110)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_MDSP_FW_DISABLE_BMSK                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_MDSP_FW_DISABLE_SHFT                                                        0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004114)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004114)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS1_CLOCKCFG_BMSK                                                  0xc0000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS1_CLOCKCFG_SHFT                                                        0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS0_CLOCKCFG_BMSK                                                  0x30000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS0_CLOCKCFG_SHFT                                                        0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS_ARCH64_DISABLE_BMSK                                              0xc000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS_ARCH64_DISABLE_SHFT                                                   0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RICA_DISABLE_BMSK                                                     0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RICA_DISABLE_SHFT                                                          0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_SPARE0_BMSK                                                           0x1ff0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_SPARE0_SHFT                                                                0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RPM_PBL_BOOT_SPEED_BMSK                                                  0xc000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RPM_PBL_BOOT_SPEED_SHFT                                                     0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RPM_BOOT_FROM_ROM_BMSK                                                   0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RPM_BOOT_FROM_ROM_SHFT                                                      0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS_BOOT_FROM_ROM_BMSK                                                  0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_APPS_BOOT_FROM_ROM_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_MSA_ENA_BMSK                                                              0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_MSA_ENA_SHFT                                                                0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_FORCE_MSA_AUTH_EN_BMSK                                                    0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_FORCE_MSA_AUTH_EN_SHFT                                                      0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_FLCB_SKIP_BMSK                                                            0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_FLCB_SKIP_SHFT                                                              0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_QCOM_PMIC_FEATURE_ENABLE_BMSK                                             0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_QCOM_PMIC_FEATURE_ENABLE_SHFT                                               0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_BOOT_ROM_CFG_BMSK                                                          0xe0
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_BOOT_ROM_CFG_SHFT                                                           0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_STACKED_MEMORY_ID_BMSK                                                     0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_STACKED_MEMORY_ID_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_MEM_REDUNn_ADDR(n)                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004118 + 0x4 * (n))
#define HWIO_QFPROM_CORR_MEM_REDUNn_OFFS(n)                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004118 + 0x4 * (n))
#define HWIO_QFPROM_CORR_MEM_REDUNn_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_MEM_REDUNn_MAXn                                                                                   35
#define HWIO_QFPROM_CORR_MEM_REDUNn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_REDUNn_ADDR(n), HWIO_QFPROM_CORR_MEM_REDUNn_RMSK)
#define HWIO_QFPROM_CORR_MEM_REDUNn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_REDUNn_ADDR(n), mask)
#define HWIO_QFPROM_CORR_MEM_REDUNn_REDUN_DATA_BMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_MEM_REDUNn_REDUN_DATA_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041a8)
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041a8)
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_RMSK                                                                        0xffffffff
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_DEBUG_KEY_LSB_ADDR, HWIO_QFPROM_CORR_DEBUG_KEY_LSB_RMSK)
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_DEBUG_KEY_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B4M1_BMSK                                                                0xe0000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B4M1_SHFT                                                                      0x1d
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B4M0_BMSK                                                                0x1c000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B4M0_SHFT                                                                      0x1a
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_G_B4_BMSK                                                                    0x3800000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_G_B4_SHFT                                                                         0x17
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_SAR_B1_BMSK                                                                   0x600000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_SAR_B1_SHFT                                                                       0x15
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_CLK_B3_BMSK                                                                   0x180000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_CLK_B3_SHFT                                                                       0x13
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_VREF_B3_BMSK                                                                   0x60000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_VREF_B3_SHFT                                                                      0x11
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M3_BMSK                                                                   0x1c000
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M3_SHFT                                                                       0xe
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M2_BMSK                                                                    0x3800
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M2_SHFT                                                                       0xb
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M1_BMSK                                                                     0x700
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M1_SHFT                                                                       0x8
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M0_BMSK                                                                      0xe0
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_PH_B3M0_SHFT                                                                       0x5
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_G_B3_BMSK                                                                         0x1c
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_G_B3_SHFT                                                                          0x2
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_SAR_B3_BMSK                                                                        0x3
#define HWIO_QFPROM_CORR_DEBUG_KEY_LSB_SAR_B3_SHFT                                                                        0x0

#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041ac)
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041ac)
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_RMSK                                                                        0xffff7fff
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_DEBUG_KEY_MSB_ADDR, HWIO_QFPROM_CORR_DEBUG_KEY_MSB_RMSK)
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_DEBUG_KEY_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_SPARE0_BMSK                                                                 0x80000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_SPARE0_SHFT                                                                       0x1f
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_CLK_B5_BMSK                                                                 0x60000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_CLK_B5_SHFT                                                                       0x1d
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_VREF_B5_BMSK                                                                0x18000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_VREF_B5_SHFT                                                                      0x1b
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M3_BMSK                                                                 0x7000000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M3_SHFT                                                                      0x18
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M2_BMSK                                                                  0xe00000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M2_SHFT                                                                      0x15
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M1_BMSK                                                                  0x1c0000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M1_SHFT                                                                      0x12
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M0_BMSK                                                                   0x30000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B5M0_SHFT                                                                      0x10
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_G_B5_BMSK                                                                       0x7000
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_G_B5_SHFT                                                                          0xc
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_SAR_B5_BMSK                                                                      0xc00
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_SAR_B5_SHFT                                                                        0xa
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_CLK_B4_BMSK                                                                      0x300
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_CLK_B4_SHFT                                                                        0x8
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_VREF_B4_BMSK                                                                      0xc0
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_VREF_B4_SHFT                                                                       0x6
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B4M3_BMSK                                                                      0x38
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B4M3_SHFT                                                                       0x3
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B4M2_BMSK                                                                       0x7
#define HWIO_QFPROM_CORR_DEBUG_KEY_MSB_PH_B4M2_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b0)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b0)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_MEM_ACCEL_BMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_MEM_ACCEL_SHFT                                                                0x0

#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b4)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b4)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_MEM_ACCEL_BMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_MSB_MEM_ACCEL_SHFT                                                                0x0

#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b8)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b8)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_RMSK                                                                       0x3fff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_MEM_ACCEL_BMSK                                                             0x3fff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_LSB_MEM_ACCEL_SHFT                                                                0x0

#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041bc)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041bc)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_BMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_QFPROM_CORR_MEM_ACCEL_ROW1_MSB_SHFT                                           0x0

#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c0)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c0)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_SW_CAL_REDUN_10_0_BMSK                                                     0xffe00000
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_SW_CAL_REDUN_10_0_SHFT                                                           0x15
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_CLK_B6_BMSK                                                                  0x180000
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_CLK_B6_SHFT                                                                      0x13
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_VREF_B6_BMSK                                                                  0x60000
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_VREF_B6_SHFT                                                                     0x11
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M3_BMSK                                                                  0x1c000
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M3_SHFT                                                                      0xe
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M2_BMSK                                                                   0x3800
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M2_SHFT                                                                      0xb
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M1_BMSK                                                                    0x700
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M1_SHFT                                                                      0x8
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M0_BMSK                                                                     0xe0
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_PH_B6M0_SHFT                                                                      0x5
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_G_B6_BMSK                                                                        0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_G_B6_SHFT                                                                         0x2
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_SAR_B6_BMSK                                                                       0x3
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_SAR_B6_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c4)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c4)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_SW_CAL_REDUN_42_11_BMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_SW_CAL_REDUN_42_11_SHFT                                                           0x0

#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c8)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c8)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_SPARE0_BMSK                                                                0xfff00000
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_SPARE0_SHFT                                                                      0x14
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS3_LDO_VREF_TRIM_BMSK                                                      0xf8000
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS3_LDO_VREF_TRIM_SHFT                                                          0xf
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS2_LDO_VREF_TRIM_BMSK                                                       0x7c00
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS2_LDO_VREF_TRIM_SHFT                                                          0xa
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS1_LDO_VREF_TRIM_BMSK                                                        0x3e0
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS1_LDO_VREF_TRIM_SHFT                                                          0x5
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS0_LDO_VREF_TRIM_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_APPS0_LDO_VREF_TRIM_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041cc)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041cc)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_APPS_APCSLMEAS_ACC_TRIM_BMSK                                               0xf8000000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_APPS_APCSLMEAS_ACC_TRIM_SHFT                                                     0x1b
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SW_CAL_REDUN_46_43_BMSK                                                     0x7800000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SW_CAL_REDUN_46_43_SHFT                                                          0x17
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SPARE0_BMSK                                                                  0x7f0000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SPARE0_SHFT                                                                      0x10
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_GP_HW_CALIB_BMSK                                                               0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_GP_HW_CALIB_SHFT                                                                  0xc
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS1_LDO_VREF_TRIM_BMSK                                                        0xf80
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS1_LDO_VREF_TRIM_SHFT                                                          0x7
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS1_LDO_ENABLE_BMSK                                                            0x40
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS1_LDO_ENABLE_SHFT                                                             0x6
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS0_LDO_VREF_TRIM_BMSK                                                         0x3e
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS0_LDO_VREF_TRIM_SHFT                                                          0x1
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS0_LDO_ENABLE_BMSK                                                             0x1
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_Q6SS0_LDO_ENABLE_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041d0)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_OFFS                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041d0)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR, HWIO_QFPROM_CORR_FEC_EN_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION31_FEC_EN_BMSK                                                           0x80000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION31_FEC_EN_SHFT                                                                 0x1f
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION30_FEC_EN_BMSK                                                           0x40000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION30_FEC_EN_SHFT                                                                 0x1e
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION29_FEC_EN_BMSK                                                           0x20000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION29_FEC_EN_SHFT                                                                 0x1d
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION28_FEC_EN_BMSK                                                           0x10000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION28_FEC_EN_SHFT                                                                 0x1c
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION27_FEC_EN_BMSK                                                            0x8000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION27_FEC_EN_SHFT                                                                 0x1b
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION26_FEC_EN_BMSK                                                            0x4000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION26_FEC_EN_SHFT                                                                 0x1a
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION25_FEC_EN_BMSK                                                            0x2000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION25_FEC_EN_SHFT                                                                 0x19
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION24_FEC_EN_BMSK                                                            0x1000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION24_FEC_EN_SHFT                                                                 0x18
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION23_FEC_EN_BMSK                                                             0x800000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION23_FEC_EN_SHFT                                                                 0x17
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION22_FEC_EN_BMSK                                                             0x400000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION22_FEC_EN_SHFT                                                                 0x16
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION21_FEC_EN_BMSK                                                             0x200000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION21_FEC_EN_SHFT                                                                 0x15
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION20_FEC_EN_BMSK                                                             0x100000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION20_FEC_EN_SHFT                                                                 0x14
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION19_FEC_EN_BMSK                                                              0x80000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION19_FEC_EN_SHFT                                                                 0x13
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION18_FEC_EN_BMSK                                                              0x40000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION18_FEC_EN_SHFT                                                                 0x12
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION17_FEC_EN_BMSK                                                              0x20000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION17_FEC_EN_SHFT                                                                 0x11
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION16_FEC_EN_BMSK                                                              0x10000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION16_FEC_EN_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION15_FEC_EN_BMSK                                                               0x8000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION15_FEC_EN_SHFT                                                                  0xf
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION14_FEC_EN_BMSK                                                               0x4000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION14_FEC_EN_SHFT                                                                  0xe
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION13_FEC_EN_BMSK                                                               0x2000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION13_FEC_EN_SHFT                                                                  0xd
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION12_FEC_EN_BMSK                                                               0x1000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION12_FEC_EN_SHFT                                                                  0xc
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION11_FEC_EN_BMSK                                                                0x800
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION11_FEC_EN_SHFT                                                                  0xb
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION10_FEC_EN_BMSK                                                                0x400
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION10_FEC_EN_SHFT                                                                  0xa
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION9_FEC_EN_BMSK                                                                 0x200
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION9_FEC_EN_SHFT                                                                   0x9
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION8_FEC_EN_BMSK                                                                 0x100
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION8_FEC_EN_SHFT                                                                   0x8
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION7_FEC_EN_BMSK                                                                  0x80
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION7_FEC_EN_SHFT                                                                   0x7
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION6_FEC_EN_BMSK                                                                  0x40
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION6_FEC_EN_SHFT                                                                   0x6
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION5_FEC_EN_BMSK                                                                  0x20
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION5_FEC_EN_SHFT                                                                   0x5
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION4_FEC_EN_BMSK                                                                  0x10
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION4_FEC_EN_SHFT                                                                   0x4
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION3_FEC_EN_BMSK                                                                   0x8
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION3_FEC_EN_SHFT                                                                   0x3
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION2_FEC_EN_BMSK                                                                   0x4
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION2_FEC_EN_SHFT                                                                   0x2
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION1_FEC_EN_BMSK                                                                   0x2
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION1_FEC_EN_SHFT                                                                   0x1
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION0_FEC_EN_BMSK                                                                   0x1
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION0_FEC_EN_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041d4)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_OFFS                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041d4)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR, HWIO_QFPROM_CORR_FEC_EN_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_QFPROM_CORR_FEC_EN_MSB_BMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_MSB_QFPROM_CORR_FEC_EN_MSB_SHFT                                                           0x0

#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041d8)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041d8)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_RMSK                                                                 0xff000000
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_ADDR, HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_RMSK)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_ROOT_CERT_PK_HASH_INDEX_BMSK                                         0xff000000
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_LSB_ROOT_CERT_PK_HASH_INDEX_SHFT                                               0x18

#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041dc)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041dc)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_ADDR, HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_RMSK)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_BMSK                                0xffffffff
#define HWIO_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_QFPROM_CORR_INTAGLIO_GLUEBIT_MSB_SHFT                                       0x0

#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041e0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041e0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_MAXn                                                                             1
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_KEY_DATA_BMSK                                                           0xffffffff
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_LSB_KEY_DATA_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041e4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041e4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_MAXn                                                                             1
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_KEY_DATA_BMSK                                                           0xffffffff
#define HWIO_QFPROM_CORR_CUST_KEY_ROWn_MSB_KEY_DATA_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f0)
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f0)
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_RMSK                                                                       0xffffffff
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SERIAL_NUM_LSB_ADDR, HWIO_QFPROM_CORR_SERIAL_NUM_LSB_RMSK)
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SERIAL_NUM_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_SERIAL_NUM_BMSK                                                            0xffffffff
#define HWIO_QFPROM_CORR_SERIAL_NUM_LSB_SERIAL_NUM_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_ADDR                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f4)
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_OFFS                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f4)
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_RMSK                                                                           0xffff
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SERIAL_NUM_MSB_ADDR, HWIO_QFPROM_CORR_SERIAL_NUM_MSB_RMSK)
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SERIAL_NUM_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_CHIP_ID_BMSK                                                                   0xffff
#define HWIO_QFPROM_CORR_SERIAL_NUM_MSB_CHIP_ID_SHFT                                                                      0x0

#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_ADDR                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f8)
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_OFFS                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f8)
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_RMSK                                                                      0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG19_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG19_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_ROOT_CERT_PK_HASH_INDEX_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_ROOT_CERT_PK_HASH_INDEX_SHFT                                                    0x18
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_SPARE0_BMSK                                                                 0xff0000
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_SPARE0_SHFT                                                                     0x10
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_PIL_SUBSYSTEM_47_32_BMSK                                                      0xffff
#define HWIO_QFPROM_CORR_SPARE_REG19_LSB_PIL_SUBSYSTEM_47_32_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_ADDR                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041fc)
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_OFFS                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041fc)
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_RMSK                                                                      0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG19_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG19_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_TQS_HASH_ACTIVE_BMSK                                                      0xf8000000
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_TQS_HASH_ACTIVE_SHFT                                                            0x1b
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_RPMB_KEY_PROVISIONED_BMSK                                                  0x4000000
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_RPMB_KEY_PROVISIONED_SHFT                                                       0x1a
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_SPARE_BMSK                                                                 0x3ffffff
#define HWIO_QFPROM_CORR_SPARE_REG19_MSB_SPARE_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004200 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_OFFS(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004200 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_MAXn                                                                           47
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_DATA0_BMSK                                                       0xffff0000
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_DATA0_SHFT                                                             0x10
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_ADDR_BMSK                                                            0xffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_ADDR_SHFT                                                               0x0

#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004204 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_OFFS(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004204 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RMSK                                                                      0x1ffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_MAXn                                                                           47
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_EN_BMSK                                                             0x10000
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_EN_SHFT                                                                0x10
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_DATA1_BMSK                                                           0xffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_DATA1_SHFT                                                              0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004380 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004380 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                                               3
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004384 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004384 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                                        0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                                               3
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                                              0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043a0)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043a0)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043a4)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043a4)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_BMSK          0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_SHFT                 0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043a8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043a8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                                               3
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043ac + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043ac + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                                        0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                                               3
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                                              0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043c8)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043c8)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043cc)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043cc)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_BMSK          0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_SHFT                 0x0

#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043d0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043d0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_MAXn                                                                          3
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_HASH_DATA0_BMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_HASH_DATA0_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043d4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043d4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_RMSK                                                                   0xffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_MAXn                                                                          3
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_HASH_DATA1_BMSK                                                        0xffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_MSB_HASH_DATA1_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043f0)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043f0)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_HASH_DATA0_BMSK                                                      0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_LSB_HASH_DATA0_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043f4)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043f4)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_BMSK                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_QFPROM_CORR_OEM_PK_HASH_ROW4_MSB_SHFT                                       0x0

#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n)                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043f8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_OFFS(n)                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043f8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_RMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_MAXn                                                                         3
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                                      0xff000000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                                            0x18
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                                        0xff0000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                                            0x10
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                                          0xff00
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                                             0x8
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                                            0xff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n)                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043fc + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_OFFS(n)                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043fc + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_RMSK                                                                  0xffffff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_MAXn                                                                         3
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                                        0xff0000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                                            0x10
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                                          0xff00
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                                             0x8
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                                            0xff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004418 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004418 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_MAXn                                                                          3
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                                       0xff000000
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                                             0x18
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                                         0xff0000
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                                             0x10
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                                           0xff00
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                                              0x8
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                                             0xff
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                                              0x0

#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000441c + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000441c + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_RMSK                                                                   0xffffff
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_MAXn                                                                          3
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                                         0xff0000
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                                             0x10
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                                           0xff00
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                                              0x8
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                                             0xff
#define HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                                              0x0

#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_ADDR                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004438)
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_OFFS                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004438)
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_RMSK                                                                      0xffffffff
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_USB_VID_PID_LSB_ADDR, HWIO_QFPROM_CORR_USB_VID_PID_LSB_RMSK)
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_USB_VID_PID_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID1_BMSK                                                                 0xffff0000
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID1_SHFT                                                                       0x10
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID0_BMSK                                                                     0xffff
#define HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID0_SHFT                                                                        0x0

#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_ADDR                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000443c)
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_OFFS                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000443c)
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_RMSK                                                                          0xffff
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_USB_VID_PID_MSB_ADDR, HWIO_QFPROM_CORR_USB_VID_PID_MSB_RMSK)
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_USB_VID_PID_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_VID_BMSK                                                                      0xffff
#define HWIO_QFPROM_CORR_USB_VID_PID_MSB_VID_SHFT                                                                         0x0

#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004440)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004440)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_SW_CAL_REDUN_83_52_BMSK                                              0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_SW_CAL_REDUN_83_52_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004444)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004444)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_SW_CAL_REDUN_115_84_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW0_MSB_SW_CAL_REDUN_115_84_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004448)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004448)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_CPR5_SVS2_QUOT_VMIN_0_BMSK                                           0x80000000
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_CPR5_SVS2_QUOT_VMIN_0_SHFT                                                 0x1f
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_SW_CAL_REDUN_146_116_BMSK                                            0x7fffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_LSB_SW_CAL_REDUN_146_116_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000444c)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000444c)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_UNUSED_BMSK                                                     0x80000000
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_UNUSED_SHFT                                                           0x1f
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_TURBO_QUOT_VMIN_BMSK                                            0x7f800000
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_TURBO_QUOT_VMIN_SHFT                                                  0x17
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_NOMINAL_QUOT_VMIN_BMSK                                            0x7f8000
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_NOMINAL_QUOT_VMIN_SHFT                                                 0xf
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_SVS_QUOT_VMIN_BMSK                                                  0x7f80
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_SVS_QUOT_VMIN_SHFT                                                     0x7
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_SVS2_QUOT_VMIN_7_1_BMSK                                               0x7f
#define HWIO_QFPROM_CORR_SPARE_REG27_ROW1_MSB_CPR5_SVS2_QUOT_VMIN_7_1_SHFT                                                0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004450)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004450)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR6_SVS_QUOT_VMIN_2_0_BMSK                                          0xe0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR6_SVS_QUOT_VMIN_2_0_SHFT                                                0x1d
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR6_SVS2_QUOT_VMIN_BMSK                                             0x1fe00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR6_SVS2_QUOT_VMIN_SHFT                                                   0x15
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TURBO_ROSEL_BMSK                                                  0x1c0000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TURBO_ROSEL_SHFT                                                      0x12
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_TUR_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_TUR_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_NOM_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_SVS_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_LSB_CPR5_TARG_VOLT_SVS_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004454)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004454)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_NOM_3_0_BMSK                                          0xf0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_NOM_3_0_SHFT                                                0x1c
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_SVS_BMSK                                               0xfc00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TARG_VOLT_SVS_SHFT                                                    0x16
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_UNUSED_BMSK                                                       0x200000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_UNUSED_SHFT                                                           0x15
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TURBO_QUOT_VMIN_BMSK                                              0x1fe000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_TURBO_QUOT_VMIN_SHFT                                                   0xd
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_NOMINAL_QUOT_VMIN_BMSK                                              0x1fe0
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_NOMINAL_QUOT_VMIN_SHFT                                                 0x5
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_SVS_QUOT_VMIN_7_3_BMSK                                                0x1f
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW0_MSB_CPR6_SVS_QUOT_VMIN_7_3_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004458)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004458)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_NOM_1_0_BMSK                                   0xc0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                         0x1e
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                       0x3c000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                             0x1a
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_TUR_BMSK                                               0x3e00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_TUR_SHFT                                                    0x15
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_NOM_BMSK                                                0x1f0000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_NOM_SHFT                                                    0x10
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_SVS_BMSK                                                  0xf800
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR0_TARG_VOLT_SVS_SHFT                                                     0xb
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TURBO_ROSEL_BMSK                                                     0x700
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TURBO_ROSEL_SHFT                                                       0x8
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_TUR_BMSK                                                    0xfc
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_TUR_SHFT                                                     0x2
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_NOM_5_4_BMSK                                                 0x3
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_LSB_CPR6_TARG_VOLT_NOM_5_4_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000445c)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000445c)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_SVS_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_SVS_2_0_SHFT                                         0x1d
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                       0x1e000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                             0x19
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                                        0x1e00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                             0x15
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_TUR_BMSK                                                0x1f0000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_TUR_SHFT                                                    0x10
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_NOM_BMSK                                                  0xf800
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_NOM_SHFT                                                     0xb
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_SVS_BMSK                                                   0x7c0
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR1_TARG_VOLT_SVS_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                             0x3c
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                              0x2
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_NOM_3_2_BMSK                                          0x3
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW1_MSB_CPR0_TARG_VOLT_OFFSET_NOM_3_2_SHFT                                          0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004460)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004460)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR3_TARG_VOLT_SVS_3_0_BMSK                                          0xf0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR3_TARG_VOLT_SVS_3_0_SHFT                                                0x1c
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                        0xf000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                             0x18
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                         0xf00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                             0x14
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                          0xf0000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                             0x10
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_TUR_BMSK                                                  0xf800
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_TUR_SHFT                                                     0xb
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_NOM_BMSK                                                   0x7c0
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_NOM_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_SVS_BMSK                                                    0x3e
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR2_TARG_VOLT_SVS_SHFT                                                     0x1
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR1_TARG_VOLT_OFFSET_SVS_3_BMSK                                            0x1
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_LSB_CPR1_TARG_VOLT_OFFSET_SVS_3_SHFT                                            0x0

#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004464)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004464)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_RMSK                                                                 0xffffffff
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_SW_CAL_REDUN_SEL_BMSK                                                0xe0000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_SW_CAL_REDUN_SEL_SHFT                                                      0x1d
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                       0x1e000000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                             0x19
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                        0x1e00000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                             0x15
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_TUR_BMSK                                                0x1f0000
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_TUR_SHFT                                                    0x10
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_NOM_BMSK                                                  0xf800
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR4_TARG_VOLT_NOM_SHFT                                                     0xb
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_TUR_BMSK                                                   0x7c0
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_TUR_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_NOM_BMSK                                                    0x3e
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_NOM_SHFT                                                     0x1
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_SVS_4_BMSK                                                   0x1
#define HWIO_QFPROM_CORR_SPARE_REG28_ROW2_MSB_CPR3_TARG_VOLT_SVS_4_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004468)
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004468)
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_RMSK                                                                         0xffffffff
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KSV_LSB_ADDR, HWIO_QFPROM_CORR_HDCP_KSV_LSB_RMSK)
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KSV_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_KSV0_BMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_HDCP_KSV_LSB_KSV0_SHFT                                                                           0x0

#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000446c)
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000446c)
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_RMSK                                                                               0xff
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KSV_MSB_ADDR, HWIO_QFPROM_CORR_HDCP_KSV_MSB_RMSK)
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KSV_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_KSV1_BMSK                                                                          0xff
#define HWIO_QFPROM_CORR_HDCP_KSV_MSB_KSV1_SHFT                                                                           0x0

#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004468 + 0x8 * (n))
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004468 + 0x8 * (n))
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_MAXn                                                                            40
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_KEY_DATA_BMSK                                                           0xffffffff
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_LSB_KEY_DATA_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_ADDR(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000446c + 0x8 * (n))
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_OFFS(n)                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000446c + 0x8 * (n))
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_RMSK                                                                      0xffffff
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_MAXn                                                                            40
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_KEY_DATA_BMSK                                                             0xffffff
#define HWIO_QFPROM_CORR_HDCP_KEY_ROWn_MSB_KEY_DATA_SHFT                                                                  0x0

#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000045b0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_OFFS(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000045b0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_RMSK                                                              0xffffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_MAXn                                                                      36
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_KEY_DATA_BMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_LSB_KEY_DATA_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000045b4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_OFFS(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000045b4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_RMSK                                                                0xffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_MAXn                                                                      36
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_KEY_DATA_BMSK                                                       0xffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY0_ROWn_MSB_KEY_DATA_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000046d8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_OFFS(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000046d8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_RMSK                                                              0xffffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_MAXn                                                                      36
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_KEY_DATA_BMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_LSB_KEY_DATA_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000046dc + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_OFFS(n)                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000046dc + 0x8 * (n))
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_RMSK                                                                0xffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_MAXn                                                                      36
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_KEY_DATA_BMSK                                                       0xffffff
#define HWIO_QFPROM_CORR_CUST_PRIV_KEY1_ROWn_MSB_KEY_DATA_SHFT                                                            0x0

#define HWIO_SEC_CTRL_HW_VERSION_ADDR                                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006000)
#define HWIO_SEC_CTRL_HW_VERSION_OFFS                                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006000)
#define HWIO_SEC_CTRL_HW_VERSION_RMSK                                                                              0xffffffff
#define HWIO_SEC_CTRL_HW_VERSION_IN          \
        in_dword_masked(HWIO_SEC_CTRL_HW_VERSION_ADDR, HWIO_SEC_CTRL_HW_VERSION_RMSK)
#define HWIO_SEC_CTRL_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_SEC_CTRL_HW_VERSION_ADDR, m)
#define HWIO_SEC_CTRL_HW_VERSION_MAJOR_BMSK                                                                        0xf0000000
#define HWIO_SEC_CTRL_HW_VERSION_MAJOR_SHFT                                                                              0x1c
#define HWIO_SEC_CTRL_HW_VERSION_MINOR_BMSK                                                                         0xfff0000
#define HWIO_SEC_CTRL_HW_VERSION_MINOR_SHFT                                                                              0x10
#define HWIO_SEC_CTRL_HW_VERSION_STEP_BMSK                                                                             0xffff
#define HWIO_SEC_CTRL_HW_VERSION_STEP_SHFT                                                                                0x0

#define HWIO_FEATURE_CONFIG0_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006004)
#define HWIO_FEATURE_CONFIG0_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006004)
#define HWIO_FEATURE_CONFIG0_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG0_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG0_ADDR, HWIO_FEATURE_CONFIG0_RMSK)
#define HWIO_FEATURE_CONFIG0_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG0_ADDR, m)
#define HWIO_FEATURE_CONFIG0_HDCP_DISABLE_BMSK                                                                     0x80000000
#define HWIO_FEATURE_CONFIG0_HDCP_DISABLE_SHFT                                                                           0x1f
#define HWIO_FEATURE_CONFIG0_DSI_0_DISABLE_BMSK                                                                    0x40000000
#define HWIO_FEATURE_CONFIG0_DSI_0_DISABLE_SHFT                                                                          0x1e
#define HWIO_FEATURE_CONFIG0_DSI_1_DISABLE_BMSK                                                                    0x20000000
#define HWIO_FEATURE_CONFIG0_DSI_1_DISABLE_SHFT                                                                          0x1d
#define HWIO_FEATURE_CONFIG0_ISP_1_DISABLE_BMSK                                                                    0x10000000
#define HWIO_FEATURE_CONFIG0_ISP_1_DISABLE_SHFT                                                                          0x1c
#define HWIO_FEATURE_CONFIG0_VP8_DECODER_DISABLE_BMSK                                                               0x8000000
#define HWIO_FEATURE_CONFIG0_VP8_DECODER_DISABLE_SHFT                                                                    0x1b
#define HWIO_FEATURE_CONFIG0_VP8_ENCODER_DISABLE_BMSK                                                               0x4000000
#define HWIO_FEATURE_CONFIG0_VP8_ENCODER_DISABLE_SHFT                                                                    0x1a
#define HWIO_FEATURE_CONFIG0_CSID_3_DISABLE_BMSK                                                                    0x2000000
#define HWIO_FEATURE_CONFIG0_CSID_3_DISABLE_SHFT                                                                         0x19
#define HWIO_FEATURE_CONFIG0_CSID_2_DISABLE_BMSK                                                                    0x1000000
#define HWIO_FEATURE_CONFIG0_CSID_2_DISABLE_SHFT                                                                         0x18
#define HWIO_FEATURE_CONFIG0_MODEM_SPARE_DISABLE_BMSK                                                                0xe00000
#define HWIO_FEATURE_CONFIG0_MODEM_SPARE_DISABLE_SHFT                                                                    0x15
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_UL_CA_DISABLE_BMSK                                                            0x100000
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_UL_CA_DISABLE_SHFT                                                                0x14
#define HWIO_FEATURE_CONFIG0_MODEM_BBRX3_DISABLE_BMSK                                                                 0x80000
#define HWIO_FEATURE_CONFIG0_MODEM_BBRX3_DISABLE_SHFT                                                                    0x13
#define HWIO_FEATURE_CONFIG0_MODEM_BBRX2_DISABLE_BMSK                                                                 0x40000
#define HWIO_FEATURE_CONFIG0_MODEM_BBRX2_DISABLE_SHFT                                                                    0x12
#define HWIO_FEATURE_CONFIG0_MODEM_GLOBAL_DISABLE_BMSK                                                                0x20000
#define HWIO_FEATURE_CONFIG0_MODEM_GLOBAL_DISABLE_SHFT                                                                   0x11
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_DC_DISABLE_0_BMSK                                                             0x10000
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_DC_DISABLE_0_SHFT                                                                0x10
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_MIMO_DISABLE_0_BMSK                                                            0x8000
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_MIMO_DISABLE_0_SHFT                                                               0xf
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_ABOVE_CAT2_DISABLE_0_BMSK                                                       0x4000
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_ABOVE_CAT2_DISABLE_0_SHFT                                                          0xe
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_ABOVE_CAT1_DISABLE_0_BMSK                                                       0x2000
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_ABOVE_CAT1_DISABLE_0_SHFT                                                          0xd
#define HWIO_FEATURE_CONFIG0_MODEM_TDSCDMA_DISABLE_0_BMSK                                                              0x1000
#define HWIO_FEATURE_CONFIG0_MODEM_TDSCDMA_DISABLE_0_SHFT                                                                 0xc
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_DISABLE_0_BMSK                                                                  0x800
#define HWIO_FEATURE_CONFIG0_MODEM_HSPA_DISABLE_0_SHFT                                                                    0xb
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_DISABLE_0_BMSK                                                                   0x400
#define HWIO_FEATURE_CONFIG0_MODEM_LTE_DISABLE_0_SHFT                                                                     0xa
#define HWIO_FEATURE_CONFIG0_MODEM_WCDMA_DISABLE_0_BMSK                                                                 0x200
#define HWIO_FEATURE_CONFIG0_MODEM_WCDMA_DISABLE_0_SHFT                                                                   0x9
#define HWIO_FEATURE_CONFIG0_MODEM_DO_DISABLE_0_BMSK                                                                    0x100
#define HWIO_FEATURE_CONFIG0_MODEM_DO_DISABLE_0_SHFT                                                                      0x8
#define HWIO_FEATURE_CONFIG0_MODEM_1X_DISABLE_0_BMSK                                                                     0x80
#define HWIO_FEATURE_CONFIG0_MODEM_1X_DISABLE_0_SHFT                                                                      0x7
#define HWIO_FEATURE_CONFIG0_NAV_DISABLE_BMSK                                                                            0x40
#define HWIO_FEATURE_CONFIG0_NAV_DISABLE_SHFT                                                                             0x6
#define HWIO_FEATURE_CONFIG0_GERAN_DISABLE_0_BMSK                                                                        0x20
#define HWIO_FEATURE_CONFIG0_GERAN_DISABLE_0_SHFT                                                                         0x5
#define HWIO_FEATURE_CONFIG0_SPI_SLAVE_DISABLE_BMSK                                                                      0x10
#define HWIO_FEATURE_CONFIG0_SPI_SLAVE_DISABLE_SHFT                                                                       0x4
#define HWIO_FEATURE_CONFIG0_APPS_ACG_DISABLE_BMSK                                                                        0x8
#define HWIO_FEATURE_CONFIG0_APPS_ACG_DISABLE_SHFT                                                                        0x3
#define HWIO_FEATURE_CONFIG0_BOOT_ROM_PATCH_DISABLE_BMSK                                                                  0x7
#define HWIO_FEATURE_CONFIG0_BOOT_ROM_PATCH_DISABLE_SHFT                                                                  0x0

#define HWIO_FEATURE_CONFIG1_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006008)
#define HWIO_FEATURE_CONFIG1_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006008)
#define HWIO_FEATURE_CONFIG1_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG1_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG1_ADDR, HWIO_FEATURE_CONFIG1_RMSK)
#define HWIO_FEATURE_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG1_ADDR, m)
#define HWIO_FEATURE_CONFIG1_VENDOR_LOCK_BMSK                                                                      0xf0000000
#define HWIO_FEATURE_CONFIG1_VENDOR_LOCK_SHFT                                                                            0x1c
#define HWIO_FEATURE_CONFIG1_SDC_EMMC_MODE1P2_FORCE_GPIO_BMSK                                                       0x8000000
#define HWIO_FEATURE_CONFIG1_SDC_EMMC_MODE1P2_FORCE_GPIO_SHFT                                                            0x1b
#define HWIO_FEATURE_CONFIG1_MODEM_DSDA_DISABLE_BMSK                                                                0x4000000
#define HWIO_FEATURE_CONFIG1_MODEM_DSDA_DISABLE_SHFT                                                                     0x1a
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_60_MHZ_DISABLE_BMSK                                                          0x2000000
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_60_MHZ_DISABLE_SHFT                                                               0x19
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_40_MHZ_DISABLE_BMSK                                                          0x1000000
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_40_MHZ_DISABLE_SHFT                                                               0x18
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_DC_DISABLE_1_BMSK                                                            0x800000
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_DC_DISABLE_1_SHFT                                                                0x17
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_MIMO_DISABLE_1_BMSK                                                          0x400000
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_MIMO_DISABLE_1_SHFT                                                              0x16
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_ABOVE_CAT2_DISABLE_1_BMSK                                                     0x200000
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_ABOVE_CAT2_DISABLE_1_SHFT                                                         0x15
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_ABOVE_CAT1_DISABLE_1_BMSK                                                     0x100000
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_ABOVE_CAT1_DISABLE_1_SHFT                                                         0x14
#define HWIO_FEATURE_CONFIG1_MODEM_TDSCDMA_DISABLE_1_BMSK                                                             0x80000
#define HWIO_FEATURE_CONFIG1_MODEM_TDSCDMA_DISABLE_1_SHFT                                                                0x13
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_DISABLE_1_BMSK                                                                0x40000
#define HWIO_FEATURE_CONFIG1_MODEM_HSPA_DISABLE_1_SHFT                                                                   0x12
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_DISABLE_1_BMSK                                                                 0x20000
#define HWIO_FEATURE_CONFIG1_MODEM_LTE_DISABLE_1_SHFT                                                                    0x11
#define HWIO_FEATURE_CONFIG1_MODEM_WCDMA_DISABLE_1_BMSK                                                               0x10000
#define HWIO_FEATURE_CONFIG1_MODEM_WCDMA_DISABLE_1_SHFT                                                                  0x10
#define HWIO_FEATURE_CONFIG1_MODEM_DO_DISABLE_1_BMSK                                                                   0x8000
#define HWIO_FEATURE_CONFIG1_MODEM_DO_DISABLE_1_SHFT                                                                      0xf
#define HWIO_FEATURE_CONFIG1_MODEM_1X_DISABLE_1_BMSK                                                                   0x4000
#define HWIO_FEATURE_CONFIG1_MODEM_1X_DISABLE_1_SHFT                                                                      0xe
#define HWIO_FEATURE_CONFIG1_GERAN_DISABLE_1_BMSK                                                                      0x2000
#define HWIO_FEATURE_CONFIG1_GERAN_DISABLE_1_SHFT                                                                         0xd
#define HWIO_FEATURE_CONFIG1_UFS_SW_CONTROL_DISABLE_BMSK                                                               0x1000
#define HWIO_FEATURE_CONFIG1_UFS_SW_CONTROL_DISABLE_SHFT                                                                  0xc
#define HWIO_FEATURE_CONFIG1_PCIE_1_DISABLE_BMSK                                                                        0x800
#define HWIO_FEATURE_CONFIG1_PCIE_1_DISABLE_SHFT                                                                          0xb
#define HWIO_FEATURE_CONFIG1_PCIE_0_DISABLE_BMSK                                                                        0x400
#define HWIO_FEATURE_CONFIG1_PCIE_0_DISABLE_SHFT                                                                          0xa
#define HWIO_FEATURE_CONFIG1_SATA_DISABLE_BMSK                                                                          0x200
#define HWIO_FEATURE_CONFIG1_SATA_DISABLE_SHFT                                                                            0x9
#define HWIO_FEATURE_CONFIG1_ACC_DISABLE_BMSK                                                                           0x100
#define HWIO_FEATURE_CONFIG1_ACC_DISABLE_SHFT                                                                             0x8
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_SEL1_BMSK                                                                       0x80
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_SEL1_SHFT                                                                        0x7
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_SEL0_BMSK                                                                       0x40
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_SEL0_SHFT                                                                        0x6
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_DISABLE_BMSK                                                                    0x20
#define HWIO_FEATURE_CONFIG1_GFX3D_TURBO_DISABLE_SHFT                                                                     0x5
#define HWIO_FEATURE_CONFIG1_VENUS_HEVC_DECODE_DISABLE_BMSK                                                              0x10
#define HWIO_FEATURE_CONFIG1_VENUS_HEVC_DECODE_DISABLE_SHFT                                                               0x4
#define HWIO_FEATURE_CONFIG1_VENUS_HEVC_ENCODE_DISABLE_BMSK                                                               0x8
#define HWIO_FEATURE_CONFIG1_VENUS_HEVC_ENCODE_DISABLE_SHFT                                                               0x3
#define HWIO_FEATURE_CONFIG1_VENUS_4K_DISABLE_BMSK                                                                        0x4
#define HWIO_FEATURE_CONFIG1_VENUS_4K_DISABLE_SHFT                                                                        0x2
#define HWIO_FEATURE_CONFIG1_MDP_APICAL_LTC_DISABLE_BMSK                                                                  0x2
#define HWIO_FEATURE_CONFIG1_MDP_APICAL_LTC_DISABLE_SHFT                                                                  0x1
#define HWIO_FEATURE_CONFIG1_HDMI_DISABLE_BMSK                                                                            0x1
#define HWIO_FEATURE_CONFIG1_HDMI_DISABLE_SHFT                                                                            0x0

#define HWIO_FEATURE_CONFIG2_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000600c)
#define HWIO_FEATURE_CONFIG2_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000600c)
#define HWIO_FEATURE_CONFIG2_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG2_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG2_ADDR, HWIO_FEATURE_CONFIG2_RMSK)
#define HWIO_FEATURE_CONFIG2_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG2_ADDR, m)
#define HWIO_FEATURE_CONFIG2_SCM_DISABLE_BMSK                                                                      0x80000000
#define HWIO_FEATURE_CONFIG2_SCM_DISABLE_SHFT                                                                            0x1f
#define HWIO_FEATURE_CONFIG2_ICE_FORCE_HW_KEY1_BMSK                                                                0x40000000
#define HWIO_FEATURE_CONFIG2_ICE_FORCE_HW_KEY1_SHFT                                                                      0x1e
#define HWIO_FEATURE_CONFIG2_ICE_FORCE_HW_KEY0_BMSK                                                                0x20000000
#define HWIO_FEATURE_CONFIG2_ICE_FORCE_HW_KEY0_SHFT                                                                      0x1d
#define HWIO_FEATURE_CONFIG2_ICE_DISABLE_BMSK                                                                      0x10000000
#define HWIO_FEATURE_CONFIG2_ICE_DISABLE_SHFT                                                                            0x1c
#define HWIO_FEATURE_CONFIG2_CSID_DPCM_14_DISABLE_BMSK                                                              0x8000000
#define HWIO_FEATURE_CONFIG2_CSID_DPCM_14_DISABLE_SHFT                                                                   0x1b
#define HWIO_FEATURE_CONFIG2_FD_DISABLE_BMSK                                                                        0x4000000
#define HWIO_FEATURE_CONFIG2_FD_DISABLE_SHFT                                                                             0x1a
#define HWIO_FEATURE_CONFIG2_QC_APPS1_SPNIDEN_DISABLE_BMSK                                                          0x2000000
#define HWIO_FEATURE_CONFIG2_QC_APPS1_SPNIDEN_DISABLE_SHFT                                                               0x19
#define HWIO_FEATURE_CONFIG2_QC_APPS1_SPIDEN_DISABLE_BMSK                                                           0x1000000
#define HWIO_FEATURE_CONFIG2_QC_APPS1_SPIDEN_DISABLE_SHFT                                                                0x18
#define HWIO_FEATURE_CONFIG2_QC_APPS1_NIDEN_DISABLE_BMSK                                                             0x800000
#define HWIO_FEATURE_CONFIG2_QC_APPS1_NIDEN_DISABLE_SHFT                                                                 0x17
#define HWIO_FEATURE_CONFIG2_QC_APPS1_DBGEN_DISABLE_BMSK                                                             0x400000
#define HWIO_FEATURE_CONFIG2_QC_APPS1_DBGEN_DISABLE_SHFT                                                                 0x16
#define HWIO_FEATURE_CONFIG2_QC_DAP_DEVICEEN_DISABLE_BMSK                                                            0x200000
#define HWIO_FEATURE_CONFIG2_QC_DAP_DEVICEEN_DISABLE_SHFT                                                                0x15
#define HWIO_FEATURE_CONFIG2_QC_DAP_SPNIDEN_DISABLE_BMSK                                                             0x100000
#define HWIO_FEATURE_CONFIG2_QC_DAP_SPNIDEN_DISABLE_SHFT                                                                 0x14
#define HWIO_FEATURE_CONFIG2_QC_DAP_SPIDEN_DISABLE_BMSK                                                               0x80000
#define HWIO_FEATURE_CONFIG2_QC_DAP_SPIDEN_DISABLE_SHFT                                                                  0x13
#define HWIO_FEATURE_CONFIG2_QC_DAP_NIDEN_DISABLE_BMSK                                                                0x40000
#define HWIO_FEATURE_CONFIG2_QC_DAP_NIDEN_DISABLE_SHFT                                                                   0x12
#define HWIO_FEATURE_CONFIG2_QC_DAP_DBGEN_DISABLE_BMSK                                                                0x20000
#define HWIO_FEATURE_CONFIG2_QC_DAP_DBGEN_DISABLE_SHFT                                                                   0x11
#define HWIO_FEATURE_CONFIG2_QC_APPS0_SPNIDEN_DISABLE_BMSK                                                            0x10000
#define HWIO_FEATURE_CONFIG2_QC_APPS0_SPNIDEN_DISABLE_SHFT                                                               0x10
#define HWIO_FEATURE_CONFIG2_QC_APPS0_SPIDEN_DISABLE_BMSK                                                              0x8000
#define HWIO_FEATURE_CONFIG2_QC_APPS0_SPIDEN_DISABLE_SHFT                                                                 0xf
#define HWIO_FEATURE_CONFIG2_QC_APPS0_NIDEN_DISABLE_BMSK                                                               0x4000
#define HWIO_FEATURE_CONFIG2_QC_APPS0_NIDEN_DISABLE_SHFT                                                                  0xe
#define HWIO_FEATURE_CONFIG2_QC_APPS0_DBGEN_DISABLE_BMSK                                                               0x2000
#define HWIO_FEATURE_CONFIG2_QC_APPS0_DBGEN_DISABLE_SHFT                                                                  0xd
#define HWIO_FEATURE_CONFIG2_QC_SPARE1_DISABLE_BMSK                                                                    0x1000
#define HWIO_FEATURE_CONFIG2_QC_SPARE1_DISABLE_SHFT                                                                       0xc
#define HWIO_FEATURE_CONFIG2_QC_SPARE0_DISABLE_BMSK                                                                     0x800
#define HWIO_FEATURE_CONFIG2_QC_SPARE0_DISABLE_SHFT                                                                       0xb
#define HWIO_FEATURE_CONFIG2_QC_VENUS_0_DBGEN_DISABLE_BMSK                                                              0x400
#define HWIO_FEATURE_CONFIG2_QC_VENUS_0_DBGEN_DISABLE_SHFT                                                                0xa
#define HWIO_FEATURE_CONFIG2_QC_RPM_DAPEN_DISABLE_BMSK                                                                  0x200
#define HWIO_FEATURE_CONFIG2_QC_RPM_DAPEN_DISABLE_SHFT                                                                    0x9
#define HWIO_FEATURE_CONFIG2_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                                       0x100
#define HWIO_FEATURE_CONFIG2_QC_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                                         0x8
#define HWIO_FEATURE_CONFIG2_QC_RPM_DBGEN_DISABLE_BMSK                                                                   0x80
#define HWIO_FEATURE_CONFIG2_QC_RPM_DBGEN_DISABLE_SHFT                                                                    0x7
#define HWIO_FEATURE_CONFIG2_QC_WCSS_DBGEN_DISABLE_BMSK                                                                  0x40
#define HWIO_FEATURE_CONFIG2_QC_WCSS_DBGEN_DISABLE_SHFT                                                                   0x6
#define HWIO_FEATURE_CONFIG2_QC_LPASS_DBGEN_DISABLE_BMSK                                                                 0x20
#define HWIO_FEATURE_CONFIG2_QC_LPASS_DBGEN_DISABLE_SHFT                                                                  0x5
#define HWIO_FEATURE_CONFIG2_QC_MSS_NIDEN_DISABLE_BMSK                                                                   0x10
#define HWIO_FEATURE_CONFIG2_QC_MSS_NIDEN_DISABLE_SHFT                                                                    0x4
#define HWIO_FEATURE_CONFIG2_QC_MSS_DBGEN_DISABLE_BMSK                                                                    0x8
#define HWIO_FEATURE_CONFIG2_QC_MSS_DBGEN_DISABLE_SHFT                                                                    0x3
#define HWIO_FEATURE_CONFIG2_MOCHA_PART_BMSK                                                                              0x4
#define HWIO_FEATURE_CONFIG2_MOCHA_PART_SHFT                                                                              0x2
#define HWIO_FEATURE_CONFIG2_SM_BIST_DISABLE_BMSK                                                                         0x2
#define HWIO_FEATURE_CONFIG2_SM_BIST_DISABLE_SHFT                                                                         0x1
#define HWIO_FEATURE_CONFIG2_TIC_DISABLE_BMSK                                                                             0x1
#define HWIO_FEATURE_CONFIG2_TIC_DISABLE_SHFT                                                                             0x0

#define HWIO_FEATURE_CONFIG3_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006010)
#define HWIO_FEATURE_CONFIG3_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006010)
#define HWIO_FEATURE_CONFIG3_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG3_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG3_ADDR, HWIO_FEATURE_CONFIG3_RMSK)
#define HWIO_FEATURE_CONFIG3_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG3_ADDR, m)
#define HWIO_FEATURE_CONFIG3_SEC_TAP_ACCESS_DISABLE_BMSK                                                           0xfffc0000
#define HWIO_FEATURE_CONFIG3_SEC_TAP_ACCESS_DISABLE_SHFT                                                                 0x12
#define HWIO_FEATURE_CONFIG3_TAP_CJI_CORE_SEL_DISABLE_BMSK                                                            0x3c000
#define HWIO_FEATURE_CONFIG3_TAP_CJI_CORE_SEL_DISABLE_SHFT                                                                0xe
#define HWIO_FEATURE_CONFIG3_TAP_INSTR_DISABLE_BMSK                                                                    0x3fff
#define HWIO_FEATURE_CONFIG3_TAP_INSTR_DISABLE_SHFT                                                                       0x0

#define HWIO_FEATURE_CONFIG4_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006014)
#define HWIO_FEATURE_CONFIG4_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006014)
#define HWIO_FEATURE_CONFIG4_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG4_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG4_ADDR, HWIO_FEATURE_CONFIG4_RMSK)
#define HWIO_FEATURE_CONFIG4_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG4_ADDR, m)
#define HWIO_FEATURE_CONFIG4_TAP_GEN_SPARE_INSTR_DISABLE_BMSK                                                      0xffffffff
#define HWIO_FEATURE_CONFIG4_TAP_GEN_SPARE_INSTR_DISABLE_SHFT                                                             0x0

#define HWIO_FEATURE_CONFIG5_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006018)
#define HWIO_FEATURE_CONFIG5_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006018)
#define HWIO_FEATURE_CONFIG5_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG5_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG5_ADDR, HWIO_FEATURE_CONFIG5_RMSK)
#define HWIO_FEATURE_CONFIG5_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG5_ADDR, m)
#define HWIO_FEATURE_CONFIG5_SW_EXPANSION_FUSES_BMSK                                                               0xff000000
#define HWIO_FEATURE_CONFIG5_SW_EXPANSION_FUSES_SHFT                                                                     0x18
#define HWIO_FEATURE_CONFIG5_APPS_CFGCPUPRESENT_N_BMSK                                                               0xff0000
#define HWIO_FEATURE_CONFIG5_APPS_CFGCPUPRESENT_N_SHFT                                                                   0x10
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION3_BMSK                                                                  0xf000
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION3_SHFT                                                                     0xc
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION2_BMSK                                                                   0xf00
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION2_SHFT                                                                     0x8
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION1_BMSK                                                                    0xf0
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION1_SHFT                                                                     0x4
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION0_BMSK                                                                     0xf
#define HWIO_FEATURE_CONFIG5_APPS_CONFIGURATION0_SHFT                                                                     0x0

#define HWIO_FEATURE_CONFIG6_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000601c)
#define HWIO_FEATURE_CONFIG6_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000601c)
#define HWIO_FEATURE_CONFIG6_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG6_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG6_ADDR, HWIO_FEATURE_CONFIG6_RMSK)
#define HWIO_FEATURE_CONFIG6_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG6_ADDR, m)
#define HWIO_FEATURE_CONFIG6_MDSP_FW_DISABLE_BMSK                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG6_MDSP_FW_DISABLE_SHFT                                                                         0x0

#define HWIO_FEATURE_CONFIG7_ADDR                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006020)
#define HWIO_FEATURE_CONFIG7_OFFS                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006020)
#define HWIO_FEATURE_CONFIG7_RMSK                                                                                  0xffffffff
#define HWIO_FEATURE_CONFIG7_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG7_ADDR, HWIO_FEATURE_CONFIG7_RMSK)
#define HWIO_FEATURE_CONFIG7_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG7_ADDR, m)
#define HWIO_FEATURE_CONFIG7_APPS1_CLOCKCFG_BMSK                                                                   0xc0000000
#define HWIO_FEATURE_CONFIG7_APPS1_CLOCKCFG_SHFT                                                                         0x1e
#define HWIO_FEATURE_CONFIG7_APPS0_CLOCKCFG_BMSK                                                                   0x30000000
#define HWIO_FEATURE_CONFIG7_APPS0_CLOCKCFG_SHFT                                                                         0x1c
#define HWIO_FEATURE_CONFIG7_APPS_ARCH64_DISABLE_BMSK                                                               0xc000000
#define HWIO_FEATURE_CONFIG7_APPS_ARCH64_DISABLE_SHFT                                                                    0x1a
#define HWIO_FEATURE_CONFIG7_RICA_DISABLE_BMSK                                                                      0x2000000
#define HWIO_FEATURE_CONFIG7_RICA_DISABLE_SHFT                                                                           0x19
#define HWIO_FEATURE_CONFIG7_SPARE0_BMSK                                                                            0x1ff0000
#define HWIO_FEATURE_CONFIG7_SPARE0_SHFT                                                                                 0x10
#define HWIO_FEATURE_CONFIG7_RPM_PBL_BOOT_SPEED_BMSK                                                                   0xc000
#define HWIO_FEATURE_CONFIG7_RPM_PBL_BOOT_SPEED_SHFT                                                                      0xe
#define HWIO_FEATURE_CONFIG7_RPM_BOOT_FROM_ROM_BMSK                                                                    0x2000
#define HWIO_FEATURE_CONFIG7_RPM_BOOT_FROM_ROM_SHFT                                                                       0xd
#define HWIO_FEATURE_CONFIG7_APPS_BOOT_FROM_ROM_BMSK                                                                   0x1000
#define HWIO_FEATURE_CONFIG7_APPS_BOOT_FROM_ROM_SHFT                                                                      0xc
#define HWIO_FEATURE_CONFIG7_MSA_ENA_BMSK                                                                               0x800
#define HWIO_FEATURE_CONFIG7_MSA_ENA_SHFT                                                                                 0xb
#define HWIO_FEATURE_CONFIG7_FORCE_MSA_AUTH_EN_BMSK                                                                     0x400
#define HWIO_FEATURE_CONFIG7_FORCE_MSA_AUTH_EN_SHFT                                                                       0xa
#define HWIO_FEATURE_CONFIG7_FLCB_SKIP_BMSK                                                                             0x200
#define HWIO_FEATURE_CONFIG7_FLCB_SKIP_SHFT                                                                               0x9
#define HWIO_FEATURE_CONFIG7_QCOM_PMIC_FEATURE_ENABLE_BMSK                                                              0x100
#define HWIO_FEATURE_CONFIG7_QCOM_PMIC_FEATURE_ENABLE_SHFT                                                                0x8
#define HWIO_FEATURE_CONFIG7_BOOT_ROM_CFG_BMSK                                                                           0xe0
#define HWIO_FEATURE_CONFIG7_BOOT_ROM_CFG_SHFT                                                                            0x5
#define HWIO_FEATURE_CONFIG7_STACKED_MEMORY_ID_BMSK                                                                      0x1f
#define HWIO_FEATURE_CONFIG7_STACKED_MEMORY_ID_SHFT                                                                       0x0

#define HWIO_OEM_CONFIG0_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006024)
#define HWIO_OEM_CONFIG0_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006024)
#define HWIO_OEM_CONFIG0_RMSK                                                                                      0xffffffff
#define HWIO_OEM_CONFIG0_IN          \
        in_dword_masked(HWIO_OEM_CONFIG0_ADDR, HWIO_OEM_CONFIG0_RMSK)
#define HWIO_OEM_CONFIG0_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG0_ADDR, m)
#define HWIO_OEM_CONFIG0_SPARE1_DISABLE_BMSK                                                                       0x80000000
#define HWIO_OEM_CONFIG0_SPARE1_DISABLE_SHFT                                                                             0x1f
#define HWIO_OEM_CONFIG0_SPARE0_DISABLE_BMSK                                                                       0x40000000
#define HWIO_OEM_CONFIG0_SPARE0_DISABLE_SHFT                                                                             0x1e
#define HWIO_OEM_CONFIG0_VENUS_0_DBGEN_DISABLE_BMSK                                                                0x20000000
#define HWIO_OEM_CONFIG0_VENUS_0_DBGEN_DISABLE_SHFT                                                                      0x1d
#define HWIO_OEM_CONFIG0_RPM_DAPEN_DISABLE_BMSK                                                                    0x10000000
#define HWIO_OEM_CONFIG0_RPM_DAPEN_DISABLE_SHFT                                                                          0x1c
#define HWIO_OEM_CONFIG0_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                                          0x8000000
#define HWIO_OEM_CONFIG0_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                                               0x1b
#define HWIO_OEM_CONFIG0_RPM_DBGEN_DISABLE_BMSK                                                                     0x4000000
#define HWIO_OEM_CONFIG0_RPM_DBGEN_DISABLE_SHFT                                                                          0x1a
#define HWIO_OEM_CONFIG0_WCSS_DBGEN_DISABLE_BMSK                                                                    0x2000000
#define HWIO_OEM_CONFIG0_WCSS_DBGEN_DISABLE_SHFT                                                                         0x19
#define HWIO_OEM_CONFIG0_LPASS_DBGEN_DISABLE_BMSK                                                                   0x1000000
#define HWIO_OEM_CONFIG0_LPASS_DBGEN_DISABLE_SHFT                                                                        0x18
#define HWIO_OEM_CONFIG0_MSS_NIDEN_DISABLE_BMSK                                                                      0x800000
#define HWIO_OEM_CONFIG0_MSS_NIDEN_DISABLE_SHFT                                                                          0x17
#define HWIO_OEM_CONFIG0_MSS_DBGEN_DISABLE_BMSK                                                                      0x400000
#define HWIO_OEM_CONFIG0_MSS_DBGEN_DISABLE_SHFT                                                                          0x16
#define HWIO_OEM_CONFIG0_ALL_DEBUG_DISABLE_BMSK                                                                      0x200000
#define HWIO_OEM_CONFIG0_ALL_DEBUG_DISABLE_SHFT                                                                          0x15
#define HWIO_OEM_CONFIG0_SPARE1_BMSK                                                                                 0x180000
#define HWIO_OEM_CONFIG0_SPARE1_SHFT                                                                                     0x13
#define HWIO_OEM_CONFIG0_IMAGE_ENCRYPTION_ENABLE_BMSK                                                                 0x40000
#define HWIO_OEM_CONFIG0_IMAGE_ENCRYPTION_ENABLE_SHFT                                                                    0x12
#define HWIO_OEM_CONFIG0_ALT_SD_PORT_FOR_BOOT_BMSK                                                                    0x20000
#define HWIO_OEM_CONFIG0_ALT_SD_PORT_FOR_BOOT_SHFT                                                                       0x11
#define HWIO_OEM_CONFIG0_SDC_EMMC_MODE1P2_GPIO_DISABLE_BMSK                                                           0x10000
#define HWIO_OEM_CONFIG0_SDC_EMMC_MODE1P2_GPIO_DISABLE_SHFT                                                              0x10
#define HWIO_OEM_CONFIG0_SDC_EMMC_MODE1P2_EN_BMSK                                                                      0x8000
#define HWIO_OEM_CONFIG0_SDC_EMMC_MODE1P2_EN_SHFT                                                                         0xf
#define HWIO_OEM_CONFIG0_FAST_BOOT_BMSK                                                                                0x7c00
#define HWIO_OEM_CONFIG0_FAST_BOOT_SHFT                                                                                   0xa
#define HWIO_OEM_CONFIG0_SDP_ENUM_SKIP_BMSK                                                                             0x200
#define HWIO_OEM_CONFIG0_SDP_ENUM_SKIP_SHFT                                                                               0x9
#define HWIO_OEM_CONFIG0_SDCC_MCLK_BOOT_FREQ_BMSK                                                                       0x100
#define HWIO_OEM_CONFIG0_SDCC_MCLK_BOOT_FREQ_SHFT                                                                         0x8
#define HWIO_OEM_CONFIG0_APPS_PBL_BOOT_SPEED_BMSK                                                                        0xc0
#define HWIO_OEM_CONFIG0_APPS_PBL_BOOT_SPEED_SHFT                                                                         0x6
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_DISABLE_BMSK                                                                     0x20
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_DISABLE_SHFT                                                                      0x5
#define HWIO_OEM_CONFIG0_SPARE0_BMSK                                                                                     0x10
#define HWIO_OEM_CONFIG0_SPARE0_SHFT                                                                                      0x4
#define HWIO_OEM_CONFIG0_PBL_PMIC_POWER_DOWN_MSM_BMSK                                                                     0x8
#define HWIO_OEM_CONFIG0_PBL_PMIC_POWER_DOWN_MSM_SHFT                                                                     0x3
#define HWIO_OEM_CONFIG0_USB_ENUM_TIMEOUT_BMSK                                                                            0x4
#define HWIO_OEM_CONFIG0_USB_ENUM_TIMEOUT_SHFT                                                                            0x2
#define HWIO_OEM_CONFIG0_DLOAD_TIMEOUT_BMSK                                                                               0x2
#define HWIO_OEM_CONFIG0_DLOAD_TIMEOUT_SHFT                                                                               0x1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_BMSK                                                                             0x1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_SHFT                                                                             0x0

#define HWIO_OEM_CONFIG1_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006028)
#define HWIO_OEM_CONFIG1_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006028)
#define HWIO_OEM_CONFIG1_RMSK                                                                                      0xffffffff
#define HWIO_OEM_CONFIG1_IN          \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, HWIO_OEM_CONFIG1_RMSK)
#define HWIO_OEM_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, m)
#define HWIO_OEM_CONFIG1_WDOG_EN_BMSK                                                                              0x80000000
#define HWIO_OEM_CONFIG1_WDOG_EN_SHFT                                                                                    0x1f
#define HWIO_OEM_CONFIG1_SPARE2_BMSK                                                                               0x40000000
#define HWIO_OEM_CONFIG1_SPARE2_SHFT                                                                                     0x1e
#define HWIO_OEM_CONFIG1_SCM_M1_RD_PERM_BMSK                                                                       0x20000000
#define HWIO_OEM_CONFIG1_SCM_M1_RD_PERM_SHFT                                                                             0x1d
#define HWIO_OEM_CONFIG1_UFS_SCM_FORCE_EFUSE_KEY_BMSK                                                              0x10000000
#define HWIO_OEM_CONFIG1_UFS_SCM_FORCE_EFUSE_KEY_SHFT                                                                    0x1c
#define HWIO_OEM_CONFIG1_SDC2_SCM_FORCE_EFUSE_KEY_BMSK                                                              0x8000000
#define HWIO_OEM_CONFIG1_SDC2_SCM_FORCE_EFUSE_KEY_SHFT                                                                   0x1b
#define HWIO_OEM_CONFIG1_SPDM_SECURE_MODE_BMSK                                                                      0x4000000
#define HWIO_OEM_CONFIG1_SPDM_SECURE_MODE_SHFT                                                                           0x1a
#define HWIO_OEM_CONFIG1_IMEI_ESN_SELECT_BMSK                                                                       0x3000000
#define HWIO_OEM_CONFIG1_IMEI_ESN_SELECT_SHFT                                                                            0x18
#define HWIO_OEM_CONFIG1_SPARE1_BMSK                                                                                 0xc00000
#define HWIO_OEM_CONFIG1_SPARE1_SHFT                                                                                     0x16
#define HWIO_OEM_CONFIG1_CUST_PRIV_KEY_SELECT_BMSK                                                                   0x200000
#define HWIO_OEM_CONFIG1_CUST_PRIV_KEY_SELECT_SHFT                                                                       0x15
#define HWIO_OEM_CONFIG1_SW_FUSE_PROG_DISABLE_BMSK                                                                   0x100000
#define HWIO_OEM_CONFIG1_SW_FUSE_PROG_DISABLE_SHFT                                                                       0x14
#define HWIO_OEM_CONFIG1_SPARE0_BMSK                                                                                  0xfe000
#define HWIO_OEM_CONFIG1_SPARE0_SHFT                                                                                      0xd
#define HWIO_OEM_CONFIG1_APPS1_SPNIDEN_DISABLE_BMSK                                                                    0x1000
#define HWIO_OEM_CONFIG1_APPS1_SPNIDEN_DISABLE_SHFT                                                                       0xc
#define HWIO_OEM_CONFIG1_APPS1_SPIDEN_DISABLE_BMSK                                                                      0x800
#define HWIO_OEM_CONFIG1_APPS1_SPIDEN_DISABLE_SHFT                                                                        0xb
#define HWIO_OEM_CONFIG1_APPS1_NIDEN_DISABLE_BMSK                                                                       0x400
#define HWIO_OEM_CONFIG1_APPS1_NIDEN_DISABLE_SHFT                                                                         0xa
#define HWIO_OEM_CONFIG1_APPS1_DBGEN_DISABLE_BMSK                                                                       0x200
#define HWIO_OEM_CONFIG1_APPS1_DBGEN_DISABLE_SHFT                                                                         0x9
#define HWIO_OEM_CONFIG1_DAP_DEVICEEN_DISABLE_BMSK                                                                      0x100
#define HWIO_OEM_CONFIG1_DAP_DEVICEEN_DISABLE_SHFT                                                                        0x8
#define HWIO_OEM_CONFIG1_DAP_SPNIDEN_DISABLE_BMSK                                                                        0x80
#define HWIO_OEM_CONFIG1_DAP_SPNIDEN_DISABLE_SHFT                                                                         0x7
#define HWIO_OEM_CONFIG1_DAP_SPIDEN_DISABLE_BMSK                                                                         0x40
#define HWIO_OEM_CONFIG1_DAP_SPIDEN_DISABLE_SHFT                                                                          0x6
#define HWIO_OEM_CONFIG1_DAP_NIDEN_DISABLE_BMSK                                                                          0x20
#define HWIO_OEM_CONFIG1_DAP_NIDEN_DISABLE_SHFT                                                                           0x5
#define HWIO_OEM_CONFIG1_DAP_DBGEN_DISABLE_BMSK                                                                          0x10
#define HWIO_OEM_CONFIG1_DAP_DBGEN_DISABLE_SHFT                                                                           0x4
#define HWIO_OEM_CONFIG1_APPS0_SPNIDEN_DISABLE_BMSK                                                                       0x8
#define HWIO_OEM_CONFIG1_APPS0_SPNIDEN_DISABLE_SHFT                                                                       0x3
#define HWIO_OEM_CONFIG1_APPS0_SPIDEN_DISABLE_BMSK                                                                        0x4
#define HWIO_OEM_CONFIG1_APPS0_SPIDEN_DISABLE_SHFT                                                                        0x2
#define HWIO_OEM_CONFIG1_APPS0_NIDEN_DISABLE_BMSK                                                                         0x2
#define HWIO_OEM_CONFIG1_APPS0_NIDEN_DISABLE_SHFT                                                                         0x1
#define HWIO_OEM_CONFIG1_APPS0_DBGEN_DISABLE_BMSK                                                                         0x1
#define HWIO_OEM_CONFIG1_APPS0_DBGEN_DISABLE_SHFT                                                                         0x0

#define HWIO_OEM_CONFIG2_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000602c)
#define HWIO_OEM_CONFIG2_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000602c)
#define HWIO_OEM_CONFIG2_RMSK                                                                                      0xffffffff
#define HWIO_OEM_CONFIG2_IN          \
        in_dword_masked(HWIO_OEM_CONFIG2_ADDR, HWIO_OEM_CONFIG2_RMSK)
#define HWIO_OEM_CONFIG2_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG2_ADDR, m)
#define HWIO_OEM_CONFIG2_OEM_HW_ID_BMSK                                                                            0xffff0000
#define HWIO_OEM_CONFIG2_OEM_HW_ID_SHFT                                                                                  0x10
#define HWIO_OEM_CONFIG2_ANTI_ROLLBACK_FEATURE_EN_BMSK                                                                 0xff00
#define HWIO_OEM_CONFIG2_ANTI_ROLLBACK_FEATURE_EN_SHFT                                                                    0x8
#define HWIO_OEM_CONFIG2_SPARE0_BMSK                                                                                     0xf0
#define HWIO_OEM_CONFIG2_SPARE0_SHFT                                                                                      0x4
#define HWIO_OEM_CONFIG2_ROOT_CERT_TOTAL_NUM_BMSK                                                                         0xf
#define HWIO_OEM_CONFIG2_ROOT_CERT_TOTAL_NUM_SHFT                                                                         0x0

#define HWIO_OEM_CONFIG3_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006030)
#define HWIO_OEM_CONFIG3_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006030)
#define HWIO_OEM_CONFIG3_RMSK                                                                                      0xffffffff
#define HWIO_OEM_CONFIG3_IN          \
        in_dword_masked(HWIO_OEM_CONFIG3_ADDR, HWIO_OEM_CONFIG3_RMSK)
#define HWIO_OEM_CONFIG3_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG3_ADDR, m)
#define HWIO_OEM_CONFIG3_SPARE0_BMSK                                                                               0xffff0000
#define HWIO_OEM_CONFIG3_SPARE0_SHFT                                                                                     0x10
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_BMSK                                                                           0xffff
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_SHFT                                                                              0x0

#define HWIO_BOOT_CONFIG_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006034)
#define HWIO_BOOT_CONFIG_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006034)
#define HWIO_BOOT_CONFIG_RMSK                                                                                           0x7ff
#define HWIO_BOOT_CONFIG_IN          \
        in_dword_masked(HWIO_BOOT_CONFIG_ADDR, HWIO_BOOT_CONFIG_RMSK)
#define HWIO_BOOT_CONFIG_INM(m)      \
        in_dword_masked(HWIO_BOOT_CONFIG_ADDR, m)
#define HWIO_BOOT_CONFIG_FORCE_MSA_AUTH_EN_BMSK                                                                         0x400
#define HWIO_BOOT_CONFIG_FORCE_MSA_AUTH_EN_SHFT                                                                           0xa
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_BMSK                                                                       0x300
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_SHFT                                                                         0x8
#define HWIO_BOOT_CONFIG_RPM_BOOT_FROM_ROM_BMSK                                                                          0x80
#define HWIO_BOOT_CONFIG_RPM_BOOT_FROM_ROM_SHFT                                                                           0x7
#define HWIO_BOOT_CONFIG_APPS_BOOT_FROM_ROM_BMSK                                                                         0x40
#define HWIO_BOOT_CONFIG_APPS_BOOT_FROM_ROM_SHFT                                                                          0x6
#define HWIO_BOOT_CONFIG_FAST_BOOT_BMSK                                                                                  0x3e
#define HWIO_BOOT_CONFIG_FAST_BOOT_SHFT                                                                                   0x1
#define HWIO_BOOT_CONFIG_WDOG_EN_BMSK                                                                                     0x1
#define HWIO_BOOT_CONFIG_WDOG_EN_SHFT                                                                                     0x0

#define HWIO_SECURE_BOOTn_ADDR(n)                                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006038 + 0x4 * (n))
#define HWIO_SECURE_BOOTn_OFFS(n)                                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006038 + 0x4 * (n))
#define HWIO_SECURE_BOOTn_RMSK                                                                                          0x17f
#define HWIO_SECURE_BOOTn_MAXn                                                                                             28
#define HWIO_SECURE_BOOTn_INI(n)        \
        in_dword_masked(HWIO_SECURE_BOOTn_ADDR(n), HWIO_SECURE_BOOTn_RMSK)
#define HWIO_SECURE_BOOTn_INMI(n,mask)    \
        in_dword_masked(HWIO_SECURE_BOOTn_ADDR(n), mask)
#define HWIO_SECURE_BOOTn_FUSE_SRC_BMSK                                                                                 0x100
#define HWIO_SECURE_BOOTn_FUSE_SRC_SHFT                                                                                   0x8
#define HWIO_SECURE_BOOTn_USE_SERIAL_NUM_BMSK                                                                            0x40
#define HWIO_SECURE_BOOTn_USE_SERIAL_NUM_SHFT                                                                             0x6
#define HWIO_SECURE_BOOTn_AUTH_EN_BMSK                                                                                   0x20
#define HWIO_SECURE_BOOTn_AUTH_EN_SHFT                                                                                    0x5
#define HWIO_SECURE_BOOTn_PK_HASH_IN_FUSE_BMSK                                                                           0x10
#define HWIO_SECURE_BOOTn_PK_HASH_IN_FUSE_SHFT                                                                            0x4
#define HWIO_SECURE_BOOTn_ROM_PK_HASH_INDEX_BMSK                                                                          0xf
#define HWIO_SECURE_BOOTn_ROM_PK_HASH_INDEX_SHFT                                                                          0x0

#define HWIO_OVERRIDE_0_ADDR                                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060b0)
#define HWIO_OVERRIDE_0_OFFS                                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060b0)
#define HWIO_OVERRIDE_0_RMSK                                                                                       0x10000003
#define HWIO_OVERRIDE_0_IN          \
        in_dword_masked(HWIO_OVERRIDE_0_ADDR, HWIO_OVERRIDE_0_RMSK)
#define HWIO_OVERRIDE_0_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_0_ADDR, m)
#define HWIO_OVERRIDE_0_OUT(v)      \
        out_dword(HWIO_OVERRIDE_0_ADDR,v)
#define HWIO_OVERRIDE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_0_ADDR,m,v,HWIO_OVERRIDE_0_IN)
#define HWIO_OVERRIDE_0_TX_DISABLE_BMSK                                                                            0x10000000
#define HWIO_OVERRIDE_0_TX_DISABLE_SHFT                                                                                  0x1c
#define HWIO_OVERRIDE_0_SDC_EMMC_MODE1P2_EN_BMSK                                                                          0x2
#define HWIO_OVERRIDE_0_SDC_EMMC_MODE1P2_EN_SHFT                                                                          0x1
#define HWIO_OVERRIDE_0_SDC_EMMC_MODE1P2_OVERRIDE_BMSK                                                                    0x1
#define HWIO_OVERRIDE_0_SDC_EMMC_MODE1P2_OVERRIDE_SHFT                                                                    0x0

#define HWIO_OVERRIDE_1_ADDR                                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060b4)
#define HWIO_OVERRIDE_1_OFFS                                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060b4)
#define HWIO_OVERRIDE_1_RMSK                                                                                       0xffffffff
#define HWIO_OVERRIDE_1_IN          \
        in_dword_masked(HWIO_OVERRIDE_1_ADDR, HWIO_OVERRIDE_1_RMSK)
#define HWIO_OVERRIDE_1_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_1_ADDR, m)
#define HWIO_OVERRIDE_1_OUT(v)      \
        out_dword(HWIO_OVERRIDE_1_ADDR,v)
#define HWIO_OVERRIDE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_1_ADDR,m,v,HWIO_OVERRIDE_1_IN)
#define HWIO_OVERRIDE_1_OVERRIDE_1_BMSK                                                                            0xffffffff
#define HWIO_OVERRIDE_1_OVERRIDE_1_SHFT                                                                                   0x0

#define HWIO_OVERRIDE_2_ADDR                                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060b8)
#define HWIO_OVERRIDE_2_OFFS                                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060b8)
#define HWIO_OVERRIDE_2_RMSK                                                                                        0x1fffc00
#define HWIO_OVERRIDE_2_IN          \
        in_dword_masked(HWIO_OVERRIDE_2_ADDR, HWIO_OVERRIDE_2_RMSK)
#define HWIO_OVERRIDE_2_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_2_ADDR, m)
#define HWIO_OVERRIDE_2_OUT(v)      \
        out_dword(HWIO_OVERRIDE_2_ADDR,v)
#define HWIO_OVERRIDE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_2_ADDR,m,v,HWIO_OVERRIDE_2_IN)
#define HWIO_OVERRIDE_2_OVRID_APPS1_NIDEN_DISABLE_BMSK                                                              0x1000000
#define HWIO_OVERRIDE_2_OVRID_APPS1_NIDEN_DISABLE_SHFT                                                                   0x18
#define HWIO_OVERRIDE_2_OVRID_APPS1_DBGEN_DISABLE_BMSK                                                               0x800000
#define HWIO_OVERRIDE_2_OVRID_APPS1_DBGEN_DISABLE_SHFT                                                                   0x17
#define HWIO_OVERRIDE_2_OVRID_DAP_DEVICEEN_DISABLE_BMSK                                                              0x400000
#define HWIO_OVERRIDE_2_OVRID_DAP_DEVICEEN_DISABLE_SHFT                                                                  0x16
#define HWIO_OVERRIDE_2_OVRID_DAP_NIDEN_DISABLE_BMSK                                                                 0x200000
#define HWIO_OVERRIDE_2_OVRID_DAP_NIDEN_DISABLE_SHFT                                                                     0x15
#define HWIO_OVERRIDE_2_OVRID_DAP_DBGEN_DISABLE_BMSK                                                                 0x100000
#define HWIO_OVERRIDE_2_OVRID_DAP_DBGEN_DISABLE_SHFT                                                                     0x14
#define HWIO_OVERRIDE_2_OVRID_APPS0_NIDEN_DISABLE_BMSK                                                                0x80000
#define HWIO_OVERRIDE_2_OVRID_APPS0_NIDEN_DISABLE_SHFT                                                                   0x13
#define HWIO_OVERRIDE_2_OVRID_APPS0_DBGEN_DISABLE_BMSK                                                                0x40000
#define HWIO_OVERRIDE_2_OVRID_APPS0_DBGEN_DISABLE_SHFT                                                                   0x12
#define HWIO_OVERRIDE_2_OVRID_SPARE1_DISABLE_BMSK                                                                     0x20000
#define HWIO_OVERRIDE_2_OVRID_SPARE1_DISABLE_SHFT                                                                        0x11
#define HWIO_OVERRIDE_2_OVRID_SPARE0_DISABLE_BMSK                                                                     0x10000
#define HWIO_OVERRIDE_2_OVRID_SPARE0_DISABLE_SHFT                                                                        0x10
#define HWIO_OVERRIDE_2_OVRID_VENUS_0_DBGEN_DISABLE_BMSK                                                               0x8000
#define HWIO_OVERRIDE_2_OVRID_VENUS_0_DBGEN_DISABLE_SHFT                                                                  0xf
#define HWIO_OVERRIDE_2_OVRID_RPM_DAPEN_DISABLE_BMSK                                                                   0x4000
#define HWIO_OVERRIDE_2_OVRID_RPM_DAPEN_DISABLE_SHFT                                                                      0xe
#define HWIO_OVERRIDE_2_OVRID_RPM_LPASS_WCSS_NIDEN_DISABLE_BMSK                                                        0x2000
#define HWIO_OVERRIDE_2_OVRID_RPM_LPASS_WCSS_NIDEN_DISABLE_SHFT                                                           0xd
#define HWIO_OVERRIDE_2_OVRID_RPM_DBGEN_DISABLE_BMSK                                                                   0x1000
#define HWIO_OVERRIDE_2_OVRID_RPM_DBGEN_DISABLE_SHFT                                                                      0xc
#define HWIO_OVERRIDE_2_OVRID_WCSS_DBGEN_DISABLE_BMSK                                                                   0x800
#define HWIO_OVERRIDE_2_OVRID_WCSS_DBGEN_DISABLE_SHFT                                                                     0xb
#define HWIO_OVERRIDE_2_OVRID_LPASS_DBGEN_DISABLE_BMSK                                                                  0x400
#define HWIO_OVERRIDE_2_OVRID_LPASS_DBGEN_DISABLE_SHFT                                                                    0xa

#define HWIO_OVERRIDE_3_ADDR                                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060bc)
#define HWIO_OVERRIDE_3_OFFS                                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060bc)
#define HWIO_OVERRIDE_3_RMSK                                                                                             0x7f
#define HWIO_OVERRIDE_3_IN          \
        in_dword_masked(HWIO_OVERRIDE_3_ADDR, HWIO_OVERRIDE_3_RMSK)
#define HWIO_OVERRIDE_3_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_3_ADDR, m)
#define HWIO_OVERRIDE_3_OUT(v)      \
        out_dword(HWIO_OVERRIDE_3_ADDR,v)
#define HWIO_OVERRIDE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_3_ADDR,m,v,HWIO_OVERRIDE_3_IN)
#define HWIO_OVERRIDE_3_OVRID_APPS1_SPNIDEN_DISABLE_BMSK                                                                 0x40
#define HWIO_OVERRIDE_3_OVRID_APPS1_SPNIDEN_DISABLE_SHFT                                                                  0x6
#define HWIO_OVERRIDE_3_OVRID_APPS1_SPIDEN_DISABLE_BMSK                                                                  0x20
#define HWIO_OVERRIDE_3_OVRID_APPS1_SPIDEN_DISABLE_SHFT                                                                   0x5
#define HWIO_OVERRIDE_3_OVRID_DAP_SPNIDEN_DISABLE_BMSK                                                                   0x10
#define HWIO_OVERRIDE_3_OVRID_DAP_SPNIDEN_DISABLE_SHFT                                                                    0x4
#define HWIO_OVERRIDE_3_OVRID_DAP_SPIDEN_DISABLE_BMSK                                                                     0x8
#define HWIO_OVERRIDE_3_OVRID_DAP_SPIDEN_DISABLE_SHFT                                                                     0x3
#define HWIO_OVERRIDE_3_OVRID_APPS0_SPNIDEN_DISABLE_BMSK                                                                  0x4
#define HWIO_OVERRIDE_3_OVRID_APPS0_SPNIDEN_DISABLE_SHFT                                                                  0x2
#define HWIO_OVERRIDE_3_OVRID_APPS0_SPIDEN_DISABLE_BMSK                                                                   0x2
#define HWIO_OVERRIDE_3_OVRID_APPS0_SPIDEN_DISABLE_SHFT                                                                   0x1
#define HWIO_OVERRIDE_3_OVRID_SPDM_SECURE_MODE_BMSK                                                                       0x1
#define HWIO_OVERRIDE_3_OVRID_SPDM_SECURE_MODE_SHFT                                                                       0x0

#define HWIO_OVERRIDE_4_ADDR                                                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c0)
#define HWIO_OVERRIDE_4_OFFS                                                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c0)
#define HWIO_OVERRIDE_4_RMSK                                                                                              0x3
#define HWIO_OVERRIDE_4_IN          \
        in_dword_masked(HWIO_OVERRIDE_4_ADDR, HWIO_OVERRIDE_4_RMSK)
#define HWIO_OVERRIDE_4_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_4_ADDR, m)
#define HWIO_OVERRIDE_4_OUT(v)      \
        out_dword(HWIO_OVERRIDE_4_ADDR,v)
#define HWIO_OVERRIDE_4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_4_ADDR,m,v,HWIO_OVERRIDE_4_IN)
#define HWIO_OVERRIDE_4_OVRID_MSS_NIDEN_DISABLE_BMSK                                                                      0x2
#define HWIO_OVERRIDE_4_OVRID_MSS_NIDEN_DISABLE_SHFT                                                                      0x1
#define HWIO_OVERRIDE_4_OVRID_MSS_DBGEN_DISABLE_BMSK                                                                      0x1
#define HWIO_OVERRIDE_4_OVRID_MSS_DBGEN_DISABLE_SHFT                                                                      0x0

#define HWIO_CAPT_SEC_GPIO_ADDR                                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c4)
#define HWIO_CAPT_SEC_GPIO_OFFS                                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c4)
#define HWIO_CAPT_SEC_GPIO_RMSK                                                                                       0x3ffff
#define HWIO_CAPT_SEC_GPIO_IN          \
        in_dword_masked(HWIO_CAPT_SEC_GPIO_ADDR, HWIO_CAPT_SEC_GPIO_RMSK)
#define HWIO_CAPT_SEC_GPIO_INM(m)      \
        in_dword_masked(HWIO_CAPT_SEC_GPIO_ADDR, m)
#define HWIO_CAPT_SEC_GPIO_OUT(v)      \
        out_dword(HWIO_CAPT_SEC_GPIO_ADDR,v)
#define HWIO_CAPT_SEC_GPIO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_CAPT_SEC_GPIO_ADDR,m,v,HWIO_CAPT_SEC_GPIO_IN)
#define HWIO_CAPT_SEC_GPIO_SDC_EMMC_MODE1P2_EN_BMSK                                                                   0x20000
#define HWIO_CAPT_SEC_GPIO_SDC_EMMC_MODE1P2_EN_SHFT                                                                      0x11
#define HWIO_CAPT_SEC_GPIO_FORCE_USB_BOOT_GPIO_BMSK                                                                   0x10000
#define HWIO_CAPT_SEC_GPIO_FORCE_USB_BOOT_GPIO_SHFT                                                                      0x10
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_BMSK                                                                       0xffff
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_SHFT                                                                          0x0

#define HWIO_APP_PROC_CFG_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c8)
#define HWIO_APP_PROC_CFG_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c8)
#define HWIO_APP_PROC_CFG_RMSK                                                                                     0x1fffffff
#define HWIO_APP_PROC_CFG_IN          \
        in_dword_masked(HWIO_APP_PROC_CFG_ADDR, HWIO_APP_PROC_CFG_RMSK)
#define HWIO_APP_PROC_CFG_INM(m)      \
        in_dword_masked(HWIO_APP_PROC_CFG_ADDR, m)
#define HWIO_APP_PROC_CFG_OUT(v)      \
        out_dword(HWIO_APP_PROC_CFG_ADDR,v)
#define HWIO_APP_PROC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APP_PROC_CFG_ADDR,m,v,HWIO_APP_PROC_CFG_IN)
#define HWIO_APP_PROC_CFG_WCSS_DBG_NIDEN_BMSK                                                                      0x10000000
#define HWIO_APP_PROC_CFG_WCSS_DBG_NIDEN_SHFT                                                                            0x1c
#define HWIO_APP_PROC_CFG_LPASS_DBG_NIDEN_BMSK                                                                      0x8000000
#define HWIO_APP_PROC_CFG_LPASS_DBG_NIDEN_SHFT                                                                           0x1b
#define HWIO_APP_PROC_CFG_RPM_DBG_NIDEN_BMSK                                                                        0x4000000
#define HWIO_APP_PROC_CFG_RPM_DBG_NIDEN_SHFT                                                                             0x1a
#define HWIO_APP_PROC_CFG_DAP_DBG_NIDEN_BMSK                                                                        0x2000000
#define HWIO_APP_PROC_CFG_DAP_DBG_NIDEN_SHFT                                                                             0x19
#define HWIO_APP_PROC_CFG_DAP_DBG_SPNIDEN_BMSK                                                                      0x1000000
#define HWIO_APP_PROC_CFG_DAP_DBG_SPNIDEN_SHFT                                                                           0x18
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC3_BMSK                                                                        0xf00000
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC3_SHFT                                                                            0x14
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC2_BMSK                                                                         0xf0000
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC2_SHFT                                                                            0x10
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC1_BMSK                                                                          0xf000
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC1_SHFT                                                                             0xc
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC0_BMSK                                                                           0xf00
#define HWIO_APP_PROC_CFG_APPS_CFG_MISC0_SHFT                                                                             0x8
#define HWIO_APP_PROC_CFG_APPS_DBG_NIDEN_BMSK                                                                            0xc0
#define HWIO_APP_PROC_CFG_APPS_DBG_NIDEN_SHFT                                                                             0x6
#define HWIO_APP_PROC_CFG_APPS_DBG_SPNIDEN_BMSK                                                                          0x30
#define HWIO_APP_PROC_CFG_APPS_DBG_SPNIDEN_SHFT                                                                           0x4
#define HWIO_APP_PROC_CFG_APPS_CP15_DISABLE_BMSK                                                                          0xc
#define HWIO_APP_PROC_CFG_APPS_CP15_DISABLE_SHFT                                                                          0x2
#define HWIO_APP_PROC_CFG_APPS_CFG_NMFI_BMSK                                                                              0x3
#define HWIO_APP_PROC_CFG_APPS_CFG_NMFI_SHFT                                                                              0x0

#define HWIO_MSS_PROC_CFG_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060cc)
#define HWIO_MSS_PROC_CFG_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060cc)
#define HWIO_MSS_PROC_CFG_RMSK                                                                                            0x1
#define HWIO_MSS_PROC_CFG_IN          \
        in_dword_masked(HWIO_MSS_PROC_CFG_ADDR, HWIO_MSS_PROC_CFG_RMSK)
#define HWIO_MSS_PROC_CFG_INM(m)      \
        in_dword_masked(HWIO_MSS_PROC_CFG_ADDR, m)
#define HWIO_MSS_PROC_CFG_OUT(v)      \
        out_dword(HWIO_MSS_PROC_CFG_ADDR,v)
#define HWIO_MSS_PROC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSS_PROC_CFG_ADDR,m,v,HWIO_MSS_PROC_CFG_IN)
#define HWIO_MSS_PROC_CFG_MSS_DBG_NIDEN_BMSK                                                                              0x1
#define HWIO_MSS_PROC_CFG_MSS_DBG_NIDEN_SHFT                                                                              0x0

#define HWIO_KDF_CFG_ADDR                                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d0)
#define HWIO_KDF_CFG_OFFS                                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d0)
#define HWIO_KDF_CFG_RMSK                                                                                                 0x1
#define HWIO_KDF_CFG_IN          \
        in_dword_masked(HWIO_KDF_CFG_ADDR, HWIO_KDF_CFG_RMSK)
#define HWIO_KDF_CFG_INM(m)      \
        in_dword_masked(HWIO_KDF_CFG_ADDR, m)
#define HWIO_KDF_CFG_OUT(v)      \
        out_dword(HWIO_KDF_CFG_ADDR,v)
#define HWIO_KDF_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_KDF_CFG_ADDR,m,v,HWIO_KDF_CFG_IN)
#define HWIO_KDF_CFG_CE1_CE2_SAME_HW_KEY_BMSK                                                                             0x1
#define HWIO_KDF_CFG_CE1_CE2_SAME_HW_KEY_SHFT                                                                             0x0

#define HWIO_QFPROM_CLK_CTL_ADDR                                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d4)
#define HWIO_QFPROM_CLK_CTL_OFFS                                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d4)
#define HWIO_QFPROM_CLK_CTL_RMSK                                                                                          0x1
#define HWIO_QFPROM_CLK_CTL_IN          \
        in_dword_masked(HWIO_QFPROM_CLK_CTL_ADDR, HWIO_QFPROM_CLK_CTL_RMSK)
#define HWIO_QFPROM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CLK_CTL_ADDR, m)
#define HWIO_QFPROM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_QFPROM_CLK_CTL_ADDR,v)
#define HWIO_QFPROM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_CLK_CTL_ADDR,m,v,HWIO_QFPROM_CLK_CTL_IN)
#define HWIO_QFPROM_CLK_CTL_CLK_HALT_BMSK                                                                                 0x1
#define HWIO_QFPROM_CLK_CTL_CLK_HALT_SHFT                                                                                 0x0

#define HWIO_HDCP_KSV_LSB_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d8)
#define HWIO_HDCP_KSV_LSB_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d8)
#define HWIO_HDCP_KSV_LSB_RMSK                                                                                     0xffffffff
#define HWIO_HDCP_KSV_LSB_IN          \
        in_dword_masked(HWIO_HDCP_KSV_LSB_ADDR, HWIO_HDCP_KSV_LSB_RMSK)
#define HWIO_HDCP_KSV_LSB_INM(m)      \
        in_dword_masked(HWIO_HDCP_KSV_LSB_ADDR, m)
#define HWIO_HDCP_KSV_LSB_KSV_LSB_BMSK                                                                             0xffffffff
#define HWIO_HDCP_KSV_LSB_KSV_LSB_SHFT                                                                                    0x0

#define HWIO_HDCP_KSV_MSB_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060dc)
#define HWIO_HDCP_KSV_MSB_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060dc)
#define HWIO_HDCP_KSV_MSB_RMSK                                                                                           0xff
#define HWIO_HDCP_KSV_MSB_IN          \
        in_dword_masked(HWIO_HDCP_KSV_MSB_ADDR, HWIO_HDCP_KSV_MSB_RMSK)
#define HWIO_HDCP_KSV_MSB_INM(m)      \
        in_dword_masked(HWIO_HDCP_KSV_MSB_ADDR, m)
#define HWIO_HDCP_KSV_MSB_KSV_MSB_BMSK                                                                                   0xff
#define HWIO_HDCP_KSV_MSB_KSV_MSB_SHFT                                                                                    0x0

#define HWIO_JTAG_ID_ADDR                                                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060e0)
#define HWIO_JTAG_ID_OFFS                                                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060e0)
#define HWIO_JTAG_ID_RMSK                                                                                          0xffffffff
#define HWIO_JTAG_ID_IN          \
        in_dword_masked(HWIO_JTAG_ID_ADDR, HWIO_JTAG_ID_RMSK)
#define HWIO_JTAG_ID_INM(m)      \
        in_dword_masked(HWIO_JTAG_ID_ADDR, m)
#define HWIO_JTAG_ID_JTAG_ID_BMSK                                                                                  0xffffffff
#define HWIO_JTAG_ID_JTAG_ID_SHFT                                                                                         0x0

#define HWIO_OEM_ID_ADDR                                                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060e4)
#define HWIO_OEM_ID_OFFS                                                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060e4)
#define HWIO_OEM_ID_RMSK                                                                                           0xffffffff
#define HWIO_OEM_ID_IN          \
        in_dword_masked(HWIO_OEM_ID_ADDR, HWIO_OEM_ID_RMSK)
#define HWIO_OEM_ID_INM(m)      \
        in_dword_masked(HWIO_OEM_ID_ADDR, m)
#define HWIO_OEM_ID_OEM_ID_BMSK                                                                                    0xffff0000
#define HWIO_OEM_ID_OEM_ID_SHFT                                                                                          0x10
#define HWIO_OEM_ID_OEM_PRODUCT_ID_BMSK                                                                                0xffff
#define HWIO_OEM_ID_OEM_PRODUCT_ID_SHFT                                                                                   0x0

#define HWIO_TEST_BUS_SEL_ADDR                                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060e8)
#define HWIO_TEST_BUS_SEL_OFFS                                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060e8)
#define HWIO_TEST_BUS_SEL_RMSK                                                                                            0x7
#define HWIO_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_TEST_BUS_SEL_ADDR, HWIO_TEST_BUS_SEL_RMSK)
#define HWIO_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TEST_BUS_SEL_ADDR, m)
#define HWIO_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TEST_BUS_SEL_ADDR,v)
#define HWIO_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TEST_BUS_SEL_ADDR,m,v,HWIO_TEST_BUS_SEL_IN)
#define HWIO_TEST_BUS_SEL_TEST_EN_BMSK                                                                                    0x4
#define HWIO_TEST_BUS_SEL_TEST_EN_SHFT                                                                                    0x2
#define HWIO_TEST_BUS_SEL_TEST_SELECT_BMSK                                                                                0x3
#define HWIO_TEST_BUS_SEL_TEST_SELECT_SHFT                                                                                0x0

#define HWIO_SPDM_DYN_SECURE_MODE_ADDR                                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060ec)
#define HWIO_SPDM_DYN_SECURE_MODE_OFFS                                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060ec)
#define HWIO_SPDM_DYN_SECURE_MODE_RMSK                                                                                    0x1
#define HWIO_SPDM_DYN_SECURE_MODE_IN          \
        in_dword_masked(HWIO_SPDM_DYN_SECURE_MODE_ADDR, HWIO_SPDM_DYN_SECURE_MODE_RMSK)
#define HWIO_SPDM_DYN_SECURE_MODE_INM(m)      \
        in_dword_masked(HWIO_SPDM_DYN_SECURE_MODE_ADDR, m)
#define HWIO_SPDM_DYN_SECURE_MODE_OUT(v)      \
        out_dword(HWIO_SPDM_DYN_SECURE_MODE_ADDR,v)
#define HWIO_SPDM_DYN_SECURE_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SPDM_DYN_SECURE_MODE_ADDR,m,v,HWIO_SPDM_DYN_SECURE_MODE_IN)
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_BMSK                                                                        0x1
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_SHFT                                                                        0x0

#define HWIO_BOOT_PARTITION_SELECT_ADDR                                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060f0)
#define HWIO_BOOT_PARTITION_SELECT_OFFS                                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060f0)
#define HWIO_BOOT_PARTITION_SELECT_RMSK                                                                            0xffffffff
#define HWIO_BOOT_PARTITION_SELECT_IN          \
        in_dword_masked(HWIO_BOOT_PARTITION_SELECT_ADDR, HWIO_BOOT_PARTITION_SELECT_RMSK)
#define HWIO_BOOT_PARTITION_SELECT_INM(m)      \
        in_dword_masked(HWIO_BOOT_PARTITION_SELECT_ADDR, m)
#define HWIO_BOOT_PARTITION_SELECT_OUT(v)      \
        out_dword(HWIO_BOOT_PARTITION_SELECT_ADDR,v)
#define HWIO_BOOT_PARTITION_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BOOT_PARTITION_SELECT_ADDR,m,v,HWIO_BOOT_PARTITION_SELECT_IN)
#define HWIO_BOOT_PARTITION_SELECT_PARTITION_BMSK                                                                  0xffffffff
#define HWIO_BOOT_PARTITION_SELECT_PARTITION_SHFT                                                                         0x0


#endif /* __CLOCKLPASSLDOHWIO_H__ */
