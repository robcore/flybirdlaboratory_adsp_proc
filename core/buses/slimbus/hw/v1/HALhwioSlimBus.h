#ifndef __HAL_HALHWIOSLIMBUS_H__
#define __HAL_HALHWIOSLIMBUS_H__
/* ===========================================================================

              H W I O   I N T E R F A C E   D E F I N I T I O N S

==============================================================================

 Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved

==============================================================================
 $Header: //components/rel/core.adsp/2.6.1/buses/slimbus/hw/v1/HALhwioSlimBus.h#1 $
=========================================================================== */

/*------------------------------------------------------------------------------
 * MODULE: slimbus
 *------------------------------------------------------------------------------*/

#define SLIMBUS_REG_BASE                                                                          0x00000000
#define SLIMBUS_REG_BASE_PHYS                                                                     0x00000000

#define HWIO_SB_COMP_CFG_ADDR                                                                     (SLIMBUS_REG_BASE      + 00000000)
#define HWIO_SB_COMP_CFG_PHYS                                                                     (SLIMBUS_REG_BASE_PHYS + 00000000)
#define HWIO_SB_COMP_CFG_RMSK                                                                            0x1
#define HWIO_SB_COMP_CFG_SHFT                                                                              0
#define HWIO_SB_COMP_CFG_IN                                                                       \
        in_dword_masked(HWIO_SB_COMP_CFG_ADDR, HWIO_SB_COMP_CFG_RMSK)
#define HWIO_SB_COMP_CFG_INM(m)                                                                   \
        in_dword_masked(HWIO_SB_COMP_CFG_ADDR, m)
#define HWIO_SB_COMP_CFG_OUT(v)                                                                   \
        out_dword(HWIO_SB_COMP_CFG_ADDR,v)
#define HWIO_SB_COMP_CFG_OUTM(m,v)                                                                \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_COMP_CFG_ADDR,m,v,HWIO_SB_COMP_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_COMP_CFG_ENABLE_BMSK                                                                     0x1
#define HWIO_SB_COMP_CFG_ENABLE_SHFT                                                                       0

#define HWIO_SB_SW_RESET_ADDR                                                                     (SLIMBUS_REG_BASE      + 0x00000004)
#define HWIO_SB_SW_RESET_PHYS                                                                     (SLIMBUS_REG_BASE_PHYS + 0x00000004)
#define HWIO_SB_SW_RESET_RMSK                                                                     0xffffffff
#define HWIO_SB_SW_RESET_SHFT                                                                              0
#define HWIO_SB_SW_RESET_OUT(v)                                                                   \
        out_dword(HWIO_SB_SW_RESET_ADDR,v)
#define HWIO_SB_SW_RESET_OUTM(m,v)                                                                \
        out_dword_masked(HWIO_SB_SW_RESET_ADDR,m,v,HWIO_SB_SW_RESET_shadow)

#define HWIO_SB_COMP_STATUS_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000008)
#define HWIO_SB_COMP_STATUS_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000008)
#define HWIO_SB_COMP_STATUS_RMSK                                                                           0
#define HWIO_SB_COMP_STATUS_SHFT                                                                           0
#define HWIO_SB_COMP_STATUS_IN                                                                    \
        in_dword_masked(HWIO_SB_COMP_STATUS_ADDR, HWIO_SB_COMP_STATUS_RMSK)
#define HWIO_SB_COMP_STATUS_INM(m)                                                                \
        in_dword_masked(HWIO_SB_COMP_STATUS_ADDR, m)

#define HWIO_SB_COMP_TEST_ADDR                                                                    (SLIMBUS_REG_BASE      + 0x0000000c)
#define HWIO_SB_COMP_TEST_PHYS                                                                    (SLIMBUS_REG_BASE_PHYS + 0x0000000c)
#define HWIO_SB_COMP_TEST_RMSK                                                                          0x7f
#define HWIO_SB_COMP_TEST_SHFT                                                                             0
#define HWIO_SB_COMP_TEST_IN                                                                      \
        in_dword_masked(HWIO_SB_COMP_TEST_ADDR, HWIO_SB_COMP_TEST_RMSK)
#define HWIO_SB_COMP_TEST_INM(m)                                                                  \
        in_dword_masked(HWIO_SB_COMP_TEST_ADDR, m)
#define HWIO_SB_COMP_TEST_OUT(v)                                                                  \
        out_dword(HWIO_SB_COMP_TEST_ADDR,v)
#define HWIO_SB_COMP_TEST_OUTM(m,v)                                                               \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_COMP_TEST_ADDR,m,v,HWIO_SB_COMP_TEST_IN); \
        HWIO_INTFREE()
#define HWIO_SB_COMP_TEST_INT_EE0_BMSK                                                                   0x1
#define HWIO_SB_COMP_TEST_INT_EE0_SHFT                                                                     0
#define HWIO_SB_COMP_TEST_INT_EE1_BMSK                                                                   0x2
#define HWIO_SB_COMP_TEST_INT_EE1_SHFT                                                                   0x1
#define HWIO_SB_COMP_TEST_INT_EE2_BMSK                                                                   0x4
#define HWIO_SB_COMP_TEST_INT_EE2_SHFT                                                                   0x2
#define HWIO_SB_COMP_TEST_SB_TESTBUS_EN_BMSK                                                             0x8
#define HWIO_SB_COMP_TEST_SB_TESTBUS_EN_SHFT                                                             0x3
#define HWIO_SB_COMP_TEST_SB_TESTBUS_SEL_BMSK                                                           0x70
#define HWIO_SB_COMP_TEST_SB_TESTBUS_SEL_SHFT                                                            0x4

#define HWIO_SB_COMP_DEBUG_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00000010)
#define HWIO_SB_COMP_DEBUG_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00000010)
#define HWIO_SB_COMP_DEBUG_RMSK                                                                          0x1
#define HWIO_SB_COMP_DEBUG_SHFT                                                                            0
#define HWIO_SB_COMP_DEBUG_IN                                                                     \
        in_dword_masked(HWIO_SB_COMP_DEBUG_ADDR, HWIO_SB_COMP_DEBUG_RMSK)
#define HWIO_SB_COMP_DEBUG_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_COMP_DEBUG_ADDR, m)
#define HWIO_SB_COMP_DEBUG_TBD_BMSK                                                                      0x1
#define HWIO_SB_COMP_DEBUG_TBD_SHFT                                                                        0

#define HWIO_SB_COMP_TRUST_CFG_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000014)
#define HWIO_SB_COMP_TRUST_CFG_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000014)
#define HWIO_SB_COMP_TRUST_CFG_RMSK                                                                    0xfff
#define HWIO_SB_COMP_TRUST_CFG_SHFT                                                                        0
#define HWIO_SB_COMP_TRUST_CFG_IN                                                                 \
        in_dword_masked(HWIO_SB_COMP_TRUST_CFG_ADDR, HWIO_SB_COMP_TRUST_CFG_RMSK)
#define HWIO_SB_COMP_TRUST_CFG_INM(m)                                                             \
        in_dword_masked(HWIO_SB_COMP_TRUST_CFG_ADDR, m)
#define HWIO_SB_COMP_TRUST_CFG_OUT(v)                                                             \
        out_dword(HWIO_SB_COMP_TRUST_CFG_ADDR,v)
#define HWIO_SB_COMP_TRUST_CFG_OUTM(m,v)                                                          \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_COMP_TRUST_CFG_ADDR,m,v,HWIO_SB_COMP_TRUST_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_COMP_TRUST_CFG_HALT_RECONFIG_BMSK                                                        0x1
#define HWIO_SB_COMP_TRUST_CFG_HALT_RECONFIG_SHFT                                                          0
#define HWIO_SB_COMP_TRUST_CFG_HALT_SW_RESET_BMSK                                                        0x2
#define HWIO_SB_COMP_TRUST_CFG_HALT_SW_RESET_SHFT                                                        0x1
#define HWIO_SB_COMP_TRUST_CFG_HALT_EN_CHANGE_BMSK                                                       0x4
#define HWIO_SB_COMP_TRUST_CFG_HALT_EN_CHANGE_SHFT                                                       0x2
#define HWIO_SB_COMP_TRUST_CFG_HALT_NGD1_MSG_TX_BMSK                                                     0x8
#define HWIO_SB_COMP_TRUST_CFG_HALT_NGD1_MSG_TX_SHFT                                                     0x3
#define HWIO_SB_COMP_TRUST_CFG_HALT_NGD2_MSG_TX_BMSK                                                    0x10
#define HWIO_SB_COMP_TRUST_CFG_HALT_NGD2_MSG_TX_SHFT                                                     0x4
#define HWIO_SB_COMP_TRUST_CFG_HALD_MGR_MSG_TX_BMSK                                                     0x20
#define HWIO_SB_COMP_TRUST_CFG_HALD_MGR_MSG_TX_SHFT                                                      0x5
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_NGD2_BMSK                                                         0xc0
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_NGD2_SHFT                                                          0x6
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_NGD1_BMSK                                                        0x300
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_NGD1_SHFT                                                          0x8
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_MGR_RSRC_GRP_BMSK                                                0xc00
#define HWIO_SB_COMP_TRUST_CFG_EE_FOR_MGR_RSRC_GRP_SHFT                                                  0xa

#define HWIO_SB_COMP_TRUST_DEV1_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000018)
#define HWIO_SB_COMP_TRUST_DEV1_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000018)
#define HWIO_SB_COMP_TRUST_DEV1_RMSK                                                              0xffffff01
#define HWIO_SB_COMP_TRUST_DEV1_SHFT                                                                       0
#define HWIO_SB_COMP_TRUST_DEV1_IN                                                                \
        in_dword_masked(HWIO_SB_COMP_TRUST_DEV1_ADDR, HWIO_SB_COMP_TRUST_DEV1_RMSK)
#define HWIO_SB_COMP_TRUST_DEV1_INM(m)                                                            \
        in_dword_masked(HWIO_SB_COMP_TRUST_DEV1_ADDR, m)
#define HWIO_SB_COMP_TRUST_DEV1_OUT(v)                                                            \
        out_dword(HWIO_SB_COMP_TRUST_DEV1_ADDR,v)
#define HWIO_SB_COMP_TRUST_DEV1_OUTM(m,v)                                                         \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_COMP_TRUST_DEV1_ADDR,m,v,HWIO_SB_COMP_TRUST_DEV1_IN); \
        HWIO_INTFREE()
#define HWIO_SB_COMP_TRUST_DEV1_TRUST_DEV_EN_BMSK                                                        0x1
#define HWIO_SB_COMP_TRUST_DEV1_TRUST_DEV_EN_SHFT                                                          0
#define HWIO_SB_COMP_TRUST_DEV1_TRUSTED_LA_BMSK                                                       0xff00
#define HWIO_SB_COMP_TRUST_DEV1_TRUSTED_LA_SHFT                                                          0x8
#define HWIO_SB_COMP_TRUST_DEV1_TRUSTED_EA_MSB_BMSK                                               0xffff0000
#define HWIO_SB_COMP_TRUST_DEV1_TRUSTED_EA_MSB_SHFT                                                     0x10

#define HWIO_SB_COMP_TRUST_DEV2_ADDR                                                              (SLIMBUS_REG_BASE      + 0x0000001c)
#define HWIO_SB_COMP_TRUST_DEV2_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x0000001c)
#define HWIO_SB_COMP_TRUST_DEV2_RMSK                                                              0xffffffff
#define HWIO_SB_COMP_TRUST_DEV2_SHFT                                                                       0
#define HWIO_SB_COMP_TRUST_DEV2_IN                                                                \
        in_dword_masked(HWIO_SB_COMP_TRUST_DEV2_ADDR, HWIO_SB_COMP_TRUST_DEV2_RMSK)
#define HWIO_SB_COMP_TRUST_DEV2_INM(m)                                                            \
        in_dword_masked(HWIO_SB_COMP_TRUST_DEV2_ADDR, m)
#define HWIO_SB_COMP_TRUST_DEV2_OUT(v)                                                            \
        out_dword(HWIO_SB_COMP_TRUST_DEV2_ADDR,v)
#define HWIO_SB_COMP_TRUST_DEV2_OUTM(m,v)                                                         \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_COMP_TRUST_DEV2_ADDR,m,v,HWIO_SB_COMP_TRUST_DEV2_IN); \
        HWIO_INTFREE()
#define HWIO_SB_COMP_TRUST_DEV2_TRUSTED_EA_LSB_BMSK                                               0xffffffff
#define HWIO_SB_COMP_TRUST_DEV2_TRUSTED_EA_LSB_SHFT                                                        0

#define HWIO_SB_MGR_CFG_ADDR                                                                      (SLIMBUS_REG_BASE      + 0x00000200)
#define HWIO_SB_MGR_CFG_PHYS                                                                      (SLIMBUS_REG_BASE_PHYS + 0x00000200)
#define HWIO_SB_MGR_CFG_RMSK                                                                             0xf
#define HWIO_SB_MGR_CFG_SHFT                                                                               0
#define HWIO_SB_MGR_CFG_IN                                                                        \
        in_dword_masked(HWIO_SB_MGR_CFG_ADDR, HWIO_SB_MGR_CFG_RMSK)
#define HWIO_SB_MGR_CFG_INM(m)                                                                    \
        in_dword_masked(HWIO_SB_MGR_CFG_ADDR, m)
#define HWIO_SB_MGR_CFG_OUT(v)                                                                    \
        out_dword(HWIO_SB_MGR_CFG_ADDR,v)
#define HWIO_SB_MGR_CFG_OUTM(m,v)                                                                 \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_MGR_CFG_ADDR,m,v,HWIO_SB_MGR_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_MGR_CFG_ENABLE_BMSK                                                                      0x1
#define HWIO_SB_MGR_CFG_ENABLE_SHFT                                                                        0
#define HWIO_SB_MGR_CFG_RX_MSGQ_EN_BMSK                                                                  0x2
#define HWIO_SB_MGR_CFG_RX_MSGQ_EN_SHFT                                                                  0x1
#define HWIO_SB_MGR_CFG_TX_MSGQ_EN_HIGH_BMSK                                                             0x4
#define HWIO_SB_MGR_CFG_TX_MSGQ_EN_HIGH_SHFT                                                             0x2
#define HWIO_SB_MGR_CFG_TX_MSGQ_EN_LOW_BMSK                                                              0x8
#define HWIO_SB_MGR_CFG_TX_MSGQ_EN_LOW_SHFT                                                              0x3

#define HWIO_SB_MGR_STATUS_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00000204)
#define HWIO_SB_MGR_STATUS_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00000204)
#define HWIO_SB_MGR_STATUS_RMSK                                                                     0xffffff
#define HWIO_SB_MGR_STATUS_SHFT                                                                            0
#define HWIO_SB_MGR_STATUS_IN                                                                     \
        in_dword_masked(HWIO_SB_MGR_STATUS_ADDR, HWIO_SB_MGR_STATUS_RMSK)
#define HWIO_SB_MGR_STATUS_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_MGR_STATUS_ADDR, m)
#define HWIO_SB_MGR_STATUS_TX_MSG_BUFFER_BUSY_BMSK                                                       0x1
#define HWIO_SB_MGR_STATUS_TX_MSG_BUFFER_BUSY_SHFT                                                         0
#define HWIO_SB_MGR_STATUS_ENUMERATED_BMSK                                                               0x2
#define HWIO_SB_MGR_STATUS_ENUMERATED_SHFT                                                               0x1
#define HWIO_SB_MGR_STATUS_PIPE_NUM_OFFSET_BMSK                                                         0xfc
#define HWIO_SB_MGR_STATUS_PIPE_NUM_OFFSET_SHFT                                                          0x2
#define HWIO_SB_MGR_STATUS_ERROR_BMSK                                                                  0x300
#define HWIO_SB_MGR_STATUS_ERROR_SHFT                                                                    0x8
#define HWIO_SB_MGR_STATUS_ACKED_TX_MSG_MC_BMSK                                                      0x1fc00
#define HWIO_SB_MGR_STATUS_ACKED_TX_MSG_MC_SHFT                                                          0xa
#define HWIO_SB_MGR_STATUS_NACKED_TX_MSG_MC_BMSK                                                    0xfe0000
#define HWIO_SB_MGR_STATUS_NACKED_TX_MSG_MC_SHFT                                                        0x11

#define HWIO_SB_MGR_RX_MSGQ_CFG_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000208)
#define HWIO_SB_MGR_RX_MSGQ_CFG_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000208)
#define HWIO_SB_MGR_RX_MSGQ_CFG_RMSK                                                              0xffffffff
#define HWIO_SB_MGR_RX_MSGQ_CFG_SHFT                                                                       0
#define HWIO_SB_MGR_RX_MSGQ_CFG_IN                                                                \
        in_dword_masked(HWIO_SB_MGR_RX_MSGQ_CFG_ADDR, HWIO_SB_MGR_RX_MSGQ_CFG_RMSK)
#define HWIO_SB_MGR_RX_MSGQ_CFG_INM(m)                                                            \
        in_dword_masked(HWIO_SB_MGR_RX_MSGQ_CFG_ADDR, m)
#define HWIO_SB_MGR_RX_MSGQ_CFG_OUT(v)                                                            \
        out_dword(HWIO_SB_MGR_RX_MSGQ_CFG_ADDR,v)
#define HWIO_SB_MGR_RX_MSGQ_CFG_OUTM(m,v)                                                         \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_MGR_RX_MSGQ_CFG_ADDR,m,v,HWIO_SB_MGR_RX_MSGQ_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_MGR_RX_MSGQ_CFG_BLOCK_SIZE_BMSK                                                         0xff
#define HWIO_SB_MGR_RX_MSGQ_CFG_BLOCK_SIZE_SHFT                                                            0
#define HWIO_SB_MGR_RX_MSGQ_CFG_TRANS_SIZE_BMSK                                                       0xff00
#define HWIO_SB_MGR_RX_MSGQ_CFG_TRANS_SIZE_SHFT                                                          0x8
#define HWIO_SB_MGR_RX_MSGQ_CFG_TIME_OUT_VAL_BMSK                                                 0xffff0000
#define HWIO_SB_MGR_RX_MSGQ_CFG_TIME_OUT_VAL_SHFT                                                       0x10

#define HWIO_SB_MGR_INT_EN_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00000210)
#define HWIO_SB_MGR_INT_EN_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00000210)
#define HWIO_SB_MGR_INT_EN_RMSK                                                                   0xff000000
#define HWIO_SB_MGR_INT_EN_SHFT                                                                            0
#define HWIO_SB_MGR_INT_EN_IN                                                                     \
        in_dword_masked(HWIO_SB_MGR_INT_EN_ADDR, HWIO_SB_MGR_INT_EN_RMSK)
#define HWIO_SB_MGR_INT_EN_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_MGR_INT_EN_ADDR, m)
#define HWIO_SB_MGR_INT_EN_OUT(v)                                                                 \
        out_dword(HWIO_SB_MGR_INT_EN_ADDR,v)
#define HWIO_SB_MGR_INT_EN_OUTM(m,v)                                                              \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_MGR_INT_EN_ADDR,m,v,HWIO_SB_MGR_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_MGR_INT_EN_TX_MSG_SENT_BMSK                                                       0x80000000
#define HWIO_SB_MGR_INT_EN_TX_MSG_SENT_SHFT                                                             0x1f
#define HWIO_SB_MGR_INT_EN_RX_MSG_RCVD_BMSK                                                       0x40000000
#define HWIO_SB_MGR_INT_EN_RX_MSG_RCVD_SHFT                                                             0x1e
#define HWIO_SB_MGR_INT_EN_DEV_ERR_BMSK                                                           0x20000000
#define HWIO_SB_MGR_INT_EN_DEV_ERR_SHFT                                                                 0x1d
#define HWIO_SB_MGR_INT_EN_IE_VE_CHANGE_BMSK                                                      0x10000000
#define HWIO_SB_MGR_INT_EN_IE_VE_CHANGE_SHFT                                                            0x1c
#define HWIO_SB_MGR_INT_EN_INVALID_TX_MSG_BMSK                                                     0x8000000
#define HWIO_SB_MGR_INT_EN_INVALID_TX_MSG_SHFT                                                          0x1b
#define HWIO_SB_MGR_INT_EN_TX_MSG_BUF_CONTENTION_BMSK                                              0x4000000
#define HWIO_SB_MGR_INT_EN_TX_MSG_BUF_CONTENTION_SHFT                                                   0x1a
#define HWIO_SB_MGR_INT_EN_TX_MSG_NACKED_TWICE_BMSK                                                0x2000000
#define HWIO_SB_MGR_INT_EN_TX_MSG_NACKED_TWICE_SHFT                                                     0x19
#define HWIO_SB_MGR_INT_EN_RECONFIG_DONE_BMSK                                                      0x1000000
#define HWIO_SB_MGR_INT_EN_RECONFIG_DONE_SHFT                                                           0x18

#define HWIO_SB_MGR_INT_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000214)
#define HWIO_SB_MGR_INT_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000214)
#define HWIO_SB_MGR_INT_STATUS_RMSK                                                               0xff000000
#define HWIO_SB_MGR_INT_STATUS_SHFT                                                                        0
#define HWIO_SB_MGR_INT_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_MGR_INT_STATUS_ADDR, HWIO_SB_MGR_INT_STATUS_RMSK)
#define HWIO_SB_MGR_INT_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_MGR_INT_STATUS_ADDR, m)
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_SENT_BMSK                                                   0x80000000
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_SENT_SHFT                                                         0x1f
#define HWIO_SB_MGR_INT_STATUS_RX_MSG_RCVD_BMSK                                                   0x40000000
#define HWIO_SB_MGR_INT_STATUS_RX_MSG_RCVD_SHFT                                                         0x1e
#define HWIO_SB_MGR_INT_STATUS_DEV_ERR_BMSK                                                       0x20000000
#define HWIO_SB_MGR_INT_STATUS_DEV_ERR_SHFT                                                             0x1d
#define HWIO_SB_MGR_INT_STATUS_IE_VE_CHANGE_BMSK                                                  0x10000000
#define HWIO_SB_MGR_INT_STATUS_IE_VE_CHANGE_SHFT                                                        0x1c
#define HWIO_SB_MGR_INT_STATUS_INVALID_TX_MSG_BMSK                                                 0x8000000
#define HWIO_SB_MGR_INT_STATUS_INVALID_TX_MSG_SHFT                                                      0x1b
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_BUF_CONTENTION_BMSK                                          0x4000000
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_BUF_CONTENTION_SHFT                                               0x1a
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_NACKED_TWICE_BMSK                                            0x2000000
#define HWIO_SB_MGR_INT_STATUS_TX_MSG_NACKED_TWICE_SHFT                                                 0x19
#define HWIO_SB_MGR_INT_STATUS_RECONFIG_DONE_BMSK                                                  0x1000000
#define HWIO_SB_MGR_INT_STATUS_RECONFIG_DONE_SHFT                                                       0x18

#define HWIO_SB_MGR_INT_CLR_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000218)
#define HWIO_SB_MGR_INT_CLR_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000218)
#define HWIO_SB_MGR_INT_CLR_RMSK                                                                  0xff000000
#define HWIO_SB_MGR_INT_CLR_SHFT                                                                           0
#define HWIO_SB_MGR_INT_CLR_OUT(v)                                                                \
        out_dword(HWIO_SB_MGR_INT_CLR_ADDR,v)
#define HWIO_SB_MGR_INT_CLR_OUTM(m,v)                                                             \
        out_dword_masked(HWIO_SB_MGR_INT_CLR_ADDR,m,v,HWIO_SB_MGR_INT_CLR_shadow)
#define HWIO_SB_MGR_INT_CLR_TX_MSG_SENT_BMSK                                                      0x80000000
#define HWIO_SB_MGR_INT_CLR_TX_MSG_SENT_SHFT                                                            0x1f
#define HWIO_SB_MGR_INT_CLR_RX_MSG_RCVD_BMSK                                                      0x40000000
#define HWIO_SB_MGR_INT_CLR_RX_MSG_RCVD_SHFT                                                            0x1e
#define HWIO_SB_MGR_INT_CLR_DEV_ERR_BMSK                                                          0x20000000
#define HWIO_SB_MGR_INT_CLR_DEV_ERR_SHFT                                                                0x1d
#define HWIO_SB_MGR_INT_CLR_IE_VE_CHANGE_BMSK                                                     0x10000000
#define HWIO_SB_MGR_INT_CLR_IE_VE_CHANGE_SHFT                                                           0x1c
#define HWIO_SB_MGR_INT_CLR_INVALID_TX_MSG_BMSK                                                    0x8000000
#define HWIO_SB_MGR_INT_CLR_INVALID_TX_MSG_SHFT                                                         0x1b
#define HWIO_SB_MGR_INT_CLR_TX_MSG_BUF_CONTENTION_BMSK                                             0x4000000
#define HWIO_SB_MGR_INT_CLR_TX_MSG_BUF_CONTENTION_SHFT                                                  0x1a
#define HWIO_SB_MGR_INT_CLR_TX_MSG_NACKED_TWICE_BMSK                                               0x2000000
#define HWIO_SB_MGR_INT_CLR_TX_MSG_NACKED_TWICE_SHFT                                                    0x19
#define HWIO_SB_MGR_INT_CLR_RECONFIG_DONE_BMSK                                                     0x1000000
#define HWIO_SB_MGR_INT_CLR_RECONFIG_DONE_SHFT                                                          0x18

#define HWIO_SB_MGR_TX_MSGn_ADDR(n)                                                               (SLIMBUS_REG_BASE      + 0x00000230 + 4 * (n))
#define HWIO_SB_MGR_TX_MSGn_PHYS(n)                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000230 + 4 * (n))
#define HWIO_SB_MGR_TX_MSGn_RMSK                                                                  0xffffffff
#define HWIO_SB_MGR_TX_MSGn_SHFT                                                                           0
#define HWIO_SB_MGR_TX_MSGn_MAXn                                                                         0x9
#define HWIO_SB_MGR_TX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_MGR_TX_MSGn_ADDR(n),val)
#define HWIO_SB_MGR_TX_MSGn_OUTMI(n,mask,val) \
        out_dword_masked(HWIO_SB_MGR_TX_MSGn_ADDR(n),mask,val,HWIO_SB_MGR_TX_MSGn_shadow[n])
#define HWIO_SB_MGR_TX_MSGn_MSGVAL_BMSK                                                           0xffffffff
#define HWIO_SB_MGR_TX_MSGn_MSGVAL_SHFT                                                                    0

#define HWIO_SB_MGR_RX_MSGn_ADDR(n)                                                               (SLIMBUS_REG_BASE      + 0x00000270 + 4 * (n))
#define HWIO_SB_MGR_RX_MSGn_PHYS(n)                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000270 + 4 * (n))
#define HWIO_SB_MGR_RX_MSGn_RMSK                                                                  0xffffffff
#define HWIO_SB_MGR_RX_MSGn_SHFT                                                                           0
#define HWIO_SB_MGR_RX_MSGn_MAXn                                                                         0x9
#define HWIO_SB_MGR_RX_MSGn_INI(n) \
        in_dword(HWIO_SB_MGR_RX_MSGn_ADDR(n))
#define HWIO_SB_MGR_RX_MSGn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_MGR_RX_MSGn_ADDR(n), mask)
#define HWIO_SB_MGR_RX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_MGR_RX_MSGn_ADDR(n),val)
#define HWIO_SB_MGR_RX_MSGn_MSGVAL_BMSK                                                           0xffffffff
#define HWIO_SB_MGR_RX_MSGn_MSGVAL_SHFT                                                                    0

#define HWIO_SB_MGR_IE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x000002f0)
#define HWIO_SB_MGR_IE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x000002f0)
#define HWIO_SB_MGR_IE_STATUS_RMSK                                                                0xfffffffd
#define HWIO_SB_MGR_IE_STATUS_SHFT                                                                         0
#define HWIO_SB_MGR_IE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_MGR_IE_STATUS_ADDR, HWIO_SB_MGR_IE_STATUS_RMSK)
#define HWIO_SB_MGR_IE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_MGR_IE_STATUS_ADDR, m)
#define HWIO_SB_MGR_IE_STATUS_UNSPRTD_MSG_BMSK                                                           0x1
#define HWIO_SB_MGR_IE_STATUS_UNSPRTD_MSG_SHFT                                                             0
#define HWIO_SB_MGR_IE_STATUS_RECONFIG_OBJ_BMSK                                                          0x4
#define HWIO_SB_MGR_IE_STATUS_RECONFIG_OBJ_SHFT                                                          0x2
#define HWIO_SB_MGR_IE_STATUS_EX_ERROR_BMSK                                                              0x8
#define HWIO_SB_MGR_IE_STATUS_EX_ERROR_SHFT                                                              0x3
#define HWIO_SB_MGR_IE_STATUS_DEV_CLASS_VER_BMSK                                                    0xff0000
#define HWIO_SB_MGR_IE_STATUS_DEV_CLASS_VER_SHFT                                                        0x10
#define HWIO_SB_MGR_IE_STATUS_DEV_CLASS_CODE_BMSK                                                 0xff000000
#define HWIO_SB_MGR_IE_STATUS_DEV_CLASS_CODE_SHFT                                                       0x18

#define HWIO_SB_MGR_VE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x00000300)
#define HWIO_SB_MGR_VE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x00000300)
#define HWIO_SB_MGR_VE_STATUS_RMSK                                                                0xffffffff
#define HWIO_SB_MGR_VE_STATUS_SHFT                                                                         0
#define HWIO_SB_MGR_VE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_MGR_VE_STATUS_ADDR, HWIO_SB_MGR_VE_STATUS_RMSK)
#define HWIO_SB_MGR_VE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_MGR_VE_STATUS_ADDR, m)
#define HWIO_SB_MGR_VE_STATUS_VE_VAL_BMSK                                                         0xffffffff
#define HWIO_SB_MGR_VE_STATUS_VE_VAL_SHFT                                                                  0

#define HWIO_SB_FRM_CFG_ADDR                                                                      (SLIMBUS_REG_BASE      + 0x00000400)
#define HWIO_SB_FRM_CFG_PHYS                                                                      (SLIMBUS_REG_BASE_PHYS + 0x00000400)
#define HWIO_SB_FRM_CFG_RMSK                                                                       0x3ffffff
#define HWIO_SB_FRM_CFG_SHFT                                                                               0
#define HWIO_SB_FRM_CFG_IN                                                                        \
        in_dword_masked(HWIO_SB_FRM_CFG_ADDR, HWIO_SB_FRM_CFG_RMSK)
#define HWIO_SB_FRM_CFG_INM(m)                                                                    \
        in_dword_masked(HWIO_SB_FRM_CFG_ADDR, m)
#define HWIO_SB_FRM_CFG_OUT(v)                                                                    \
        out_dword(HWIO_SB_FRM_CFG_ADDR,v)
#define HWIO_SB_FRM_CFG_OUTM(m,v)                                                                 \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_FRM_CFG_ADDR,m,v,HWIO_SB_FRM_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_FRM_CFG_SEL_INTFB_CAPTURE_CLK_BMSK                                                 0x2000000
#define HWIO_SB_FRM_CFG_SEL_INTFB_CAPTURE_CLK_SHFT                                                      0x19
#define HWIO_SB_FRM_CFG_CDL_TIMEOUT_BMSK                                                           0x1c00000
#define HWIO_SB_FRM_CFG_CDL_TIMEOUT_SHFT                                                                0x16
#define HWIO_SB_FRM_CFG_CLK_QUALITY_BMSK                                                            0x300000
#define HWIO_SB_FRM_CFG_CLK_QUALITY_SHFT                                                                0x14
#define HWIO_SB_FRM_CFG_INTERNAL_WAKEUP_EN_BMSK                                                      0x80000
#define HWIO_SB_FRM_CFG_INTERNAL_WAKEUP_EN_SHFT                                                         0x13
#define HWIO_SB_FRM_CFG_REFERENCE_CLK_CG_BMSK                                                        0x78000
#define HWIO_SB_FRM_CFG_REFERENCE_CLK_CG_SHFT                                                            0xf
#define HWIO_SB_FRM_CFG_BOOT_ROOT_FREQ_BMSK                                                           0x7800
#define HWIO_SB_FRM_CFG_BOOT_ROOT_FREQ_SHFT                                                              0xb
#define HWIO_SB_FRM_CFG_BOOT_CLOCK_GEAR_BMSK                                                           0x780
#define HWIO_SB_FRM_CFG_BOOT_CLOCK_GEAR_SHFT                                                             0x7
#define HWIO_SB_FRM_CFG_BOOT_SUBFRAME_MODE_BMSK                                                         0x7c
#define HWIO_SB_FRM_CFG_BOOT_SUBFRAME_MODE_SHFT                                                          0x2
#define HWIO_SB_FRM_CFG_BOOT_AS_ACTIVE_FRAMER_BMSK                                                       0x2
#define HWIO_SB_FRM_CFG_BOOT_AS_ACTIVE_FRAMER_SHFT                                                       0x1
#define HWIO_SB_FRM_CFG_ENABLE_BMSK                                                                      0x1
#define HWIO_SB_FRM_CFG_ENABLE_SHFT                                                                        0

#define HWIO_SB_FRM_STATUS_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00000404)
#define HWIO_SB_FRM_STATUS_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00000404)
#define HWIO_SB_FRM_STATUS_RMSK                                                                    0x7ffffff
#define HWIO_SB_FRM_STATUS_SHFT                                                                            0
#define HWIO_SB_FRM_STATUS_IN                                                                     \
        in_dword_masked(HWIO_SB_FRM_STATUS_ADDR, HWIO_SB_FRM_STATUS_RMSK)
#define HWIO_SB_FRM_STATUS_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_FRM_STATUS_ADDR, m)
#define HWIO_SB_FRM_STATUS_FRAMER_BOOTED_BMSK                                                            0x1
#define HWIO_SB_FRM_STATUS_FRAMER_BOOTED_SHFT                                                              0
#define HWIO_SB_FRM_STATUS_CUR_SUBFRAME_MODE_BMSK                                                       0x3e
#define HWIO_SB_FRM_STATUS_CUR_SUBFRAME_MODE_SHFT                                                        0x1
#define HWIO_SB_FRM_STATUS_ERROR_BMSK                                                                   0xc0
#define HWIO_SB_FRM_STATUS_ERROR_SHFT                                                                    0x6
#define HWIO_SB_FRM_STATUS_CUR_CLOCK_GEAR_BMSK                                                         0xf00
#define HWIO_SB_FRM_STATUS_CUR_CLOCK_GEAR_SHFT                                                           0x8
#define HWIO_SB_FRM_STATUS_CUR_ROOT_FREQUENCY_BMSK                                                    0xf000
#define HWIO_SB_FRM_STATUS_CUR_ROOT_FREQUENCY_SHFT                                                       0xc
#define HWIO_SB_FRM_STATUS_ACTIVE_FRAMER_BMSK                                                        0x10000
#define HWIO_SB_FRM_STATUS_ACTIVE_FRAMER_SHFT                                                           0x10
#define HWIO_SB_FRM_STATUS_IDLE_MODE_BMSK                                                            0x20000
#define HWIO_SB_FRM_STATUS_IDLE_MODE_SHFT                                                               0x11
#define HWIO_SB_FRM_STATUS_ENUMERATED_BMSK                                                           0x40000
#define HWIO_SB_FRM_STATUS_ENUMERATED_SHFT                                                              0x12
#define HWIO_SB_FRM_STATUS_DEV_LA_BMSK                                                             0x7f80000
#define HWIO_SB_FRM_STATUS_DEV_LA_SHFT                                                                  0x13

#define HWIO_SB_FRM_INT_EN_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00000410)
#define HWIO_SB_FRM_INT_EN_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00000410)
#define HWIO_SB_FRM_INT_EN_RMSK                                                                         0x1f
#define HWIO_SB_FRM_INT_EN_SHFT                                                                            0
#define HWIO_SB_FRM_INT_EN_IN                                                                     \
        in_dword_masked(HWIO_SB_FRM_INT_EN_ADDR, HWIO_SB_FRM_INT_EN_RMSK)
#define HWIO_SB_FRM_INT_EN_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_FRM_INT_EN_ADDR, m)
#define HWIO_SB_FRM_INT_EN_OUT(v)                                                                 \
        out_dword(HWIO_SB_FRM_INT_EN_ADDR,v)
#define HWIO_SB_FRM_INT_EN_OUTM(m,v)                                                              \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_FRM_INT_EN_ADDR,m,v,HWIO_SB_FRM_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_FRM_INT_EN_DEV_ERR_BMSK                                                                  0x1
#define HWIO_SB_FRM_INT_EN_DEV_ERR_SHFT                                                                    0
#define HWIO_SB_FRM_INT_EN_IE_VE_CHANGE_BMSK                                                             0x2
#define HWIO_SB_FRM_INT_EN_IE_VE_CHANGE_SHFT                                                             0x1
#define HWIO_SB_FRM_INT_EN_FRAMER_BOOT_COMPLETE_BMSK                                                     0x4
#define HWIO_SB_FRM_INT_EN_FRAMER_BOOT_COMPLETE_SHFT                                                     0x2
#define HWIO_SB_FRM_INT_EN_IDLE_MODE_EXITED_BMSK                                                         0x8
#define HWIO_SB_FRM_INT_EN_IDLE_MODE_EXITED_SHFT                                                         0x3
#define HWIO_SB_FRM_INT_EN_CDL_TIMEDOUT_BMSK                                                            0x10
#define HWIO_SB_FRM_INT_EN_CDL_TIMEDOUT_SHFT                                                             0x4

#define HWIO_SB_FRM_INT_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000414)
#define HWIO_SB_FRM_INT_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000414)
#define HWIO_SB_FRM_INT_STATUS_RMSK                                                                     0x1f
#define HWIO_SB_FRM_INT_STATUS_SHFT                                                                        0
#define HWIO_SB_FRM_INT_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_FRM_INT_STATUS_ADDR, HWIO_SB_FRM_INT_STATUS_RMSK)
#define HWIO_SB_FRM_INT_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_FRM_INT_STATUS_ADDR, m)
#define HWIO_SB_FRM_INT_STATUS_DEV_ERR_BMSK                                                              0x1
#define HWIO_SB_FRM_INT_STATUS_DEV_ERR_SHFT                                                                0
#define HWIO_SB_FRM_INT_STATUS_IE_VE_CHANGE_BMSK                                                         0x2
#define HWIO_SB_FRM_INT_STATUS_IE_VE_CHANGE_SHFT                                                         0x1
#define HWIO_SB_FRM_INT_STATUS_FRAMER_BOOT_COMPLETE_BMSK                                                 0x4
#define HWIO_SB_FRM_INT_STATUS_FRAMER_BOOT_COMPLETE_SHFT                                                 0x2
#define HWIO_SB_FRM_INT_STATUS_IDLE_MODE_EXITED_BMSK                                                     0x8
#define HWIO_SB_FRM_INT_STATUS_IDLE_MODE_EXITED_SHFT                                                     0x3
#define HWIO_SB_FRM_INT_STATUS_CDL_TIMEDOUT_BMSK                                                        0x10
#define HWIO_SB_FRM_INT_STATUS_CDL_TIMEDOUT_SHFT                                                         0x4

#define HWIO_SB_FRM_INT_CLR_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000418)
#define HWIO_SB_FRM_INT_CLR_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000418)
#define HWIO_SB_FRM_INT_CLR_RMSK                                                                        0x1f
#define HWIO_SB_FRM_INT_CLR_SHFT                                                                           0
#define HWIO_SB_FRM_INT_CLR_OUT(v)                                                                \
        out_dword(HWIO_SB_FRM_INT_CLR_ADDR,v)
#define HWIO_SB_FRM_INT_CLR_OUTM(m,v)                                                             \
        out_dword_masked(HWIO_SB_FRM_INT_CLR_ADDR,m,v,HWIO_SB_FRM_INT_CLR_shadow)
#define HWIO_SB_FRM_INT_CLR_DEV_ERR_BMSK                                                                 0x1
#define HWIO_SB_FRM_INT_CLR_DEV_ERR_SHFT                                                                   0
#define HWIO_SB_FRM_INT_CLR_IE_VE_CHANGE_BMSK                                                            0x2
#define HWIO_SB_FRM_INT_CLR_IE_VE_CHANGE_SHFT                                                            0x1
#define HWIO_SB_FRM_INT_CLR_FRAMER_BOOT_COMPLETE_BMSK                                                    0x4
#define HWIO_SB_FRM_INT_CLR_FRAMER_BOOT_COMPLETE_SHFT                                                    0x2
#define HWIO_SB_FRM_INT_CLR_IDLE_MODE_EXITED_BMSK                                                        0x8
#define HWIO_SB_FRM_INT_CLR_IDLE_MODE_EXITED_SHFT                                                        0x3
#define HWIO_SB_FRM_INT_CLR_CDL_TIMEDOUT_BMSK                                                           0x10
#define HWIO_SB_FRM_INT_CLR_CDL_TIMEDOUT_SHFT                                                            0x4

#define HWIO_SB_FRM_WAKEUP_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x0000041c)
#define HWIO_SB_FRM_WAKEUP_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x0000041c)
#define HWIO_SB_FRM_WAKEUP_RMSK                                                                          0x1
#define HWIO_SB_FRM_WAKEUP_SHFT                                                                            0
#define HWIO_SB_FRM_WAKEUP_OUT(v)                                                                 \
        out_dword(HWIO_SB_FRM_WAKEUP_ADDR,v)
#define HWIO_SB_FRM_WAKEUP_OUTM(m,v)                                                              \
        out_dword_masked(HWIO_SB_FRM_WAKEUP_ADDR,m,v,HWIO_SB_FRM_WAKEUP_shadow)
#define HWIO_SB_FRM_WAKEUP_WAKEUP_NOW_BMSK                                                               0x1
#define HWIO_SB_FRM_WAKEUP_WAKEUP_NOW_SHFT                                                                 0

#define HWIO_SB_FRM_CLKCTL_DONE_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000420)
#define HWIO_SB_FRM_CLKCTL_DONE_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000420)
#define HWIO_SB_FRM_CLKCTL_DONE_RMSK                                                                     0x1
#define HWIO_SB_FRM_CLKCTL_DONE_SHFT                                                                       0
#define HWIO_SB_FRM_CLKCTL_DONE_OUT(v)                                                            \
        out_dword(HWIO_SB_FRM_CLKCTL_DONE_ADDR,v)
#define HWIO_SB_FRM_CLKCTL_DONE_OUTM(m,v)                                                         \
        out_dword_masked(HWIO_SB_FRM_CLKCTL_DONE_ADDR,m,v,HWIO_SB_FRM_CLKCTL_DONE_shadow)
#define HWIO_SB_FRM_CLKCTL_DONE_CLKCTL_DONE_BMSK                                                         0x1
#define HWIO_SB_FRM_CLKCTL_DONE_CLKCTL_DONE_SHFT                                                           0

#define HWIO_SB_FRM_IE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x00000430)
#define HWIO_SB_FRM_IE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x00000430)
#define HWIO_SB_FRM_IE_STATUS_RMSK                                                                0xfffffffd
#define HWIO_SB_FRM_IE_STATUS_SHFT                                                                         0
#define HWIO_SB_FRM_IE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_FRM_IE_STATUS_ADDR, HWIO_SB_FRM_IE_STATUS_RMSK)
#define HWIO_SB_FRM_IE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_FRM_IE_STATUS_ADDR, m)
#define HWIO_SB_FRM_IE_STATUS_UNSPRTD_MSG_BMSK                                                           0x1
#define HWIO_SB_FRM_IE_STATUS_UNSPRTD_MSG_SHFT                                                             0
#define HWIO_SB_FRM_IE_STATUS_RECONFIG_OBJ_BMSK                                                          0x4
#define HWIO_SB_FRM_IE_STATUS_RECONFIG_OBJ_SHFT                                                          0x2
#define HWIO_SB_FRM_IE_STATUS_EX_ERROR_BMSK                                                              0x8
#define HWIO_SB_FRM_IE_STATUS_EX_ERROR_SHFT                                                              0x3
#define HWIO_SB_FRM_IE_STATUS_ACTIVE_FRAMER_BMSK                                                        0x10
#define HWIO_SB_FRM_IE_STATUS_ACTIVE_FRAMER_SHFT                                                         0x4
#define HWIO_SB_FRM_IE_STATUS_FS_TX_COL_BMSK                                                            0x20
#define HWIO_SB_FRM_IE_STATUS_FS_TX_COL_SHFT                                                             0x5
#define HWIO_SB_FRM_IE_STATUS_FI_TX_COL_BMSK                                                            0x40
#define HWIO_SB_FRM_IE_STATUS_FI_TX_COL_SHFT                                                             0x6
#define HWIO_SB_FRM_IE_STATUS_GC_TX_COL_BMSK                                                            0x80
#define HWIO_SB_FRM_IE_STATUS_GC_TX_COL_SHFT                                                             0x7
#define HWIO_SB_FRM_IE_STATUS_QUAL_BMSK                                                                0x300
#define HWIO_SB_FRM_IE_STATUS_QUAL_SHFT                                                                  0x8
#define HWIO_SB_FRM_IE_STATUS_DEV_CLASS_VER_BMSK                                                    0xff0000
#define HWIO_SB_FRM_IE_STATUS_DEV_CLASS_VER_SHFT                                                        0x10
#define HWIO_SB_FRM_IE_STATUS_DEV_CLASS_CODE_BMSK                                                 0xff000000
#define HWIO_SB_FRM_IE_STATUS_DEV_CLASS_CODE_SHFT                                                       0x18

#define HWIO_SB_FRM_VE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x00000440)
#define HWIO_SB_FRM_VE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x00000440)
#define HWIO_SB_FRM_VE_STATUS_RMSK                                                                0xffffffff
#define HWIO_SB_FRM_VE_STATUS_SHFT                                                                         0
#define HWIO_SB_FRM_VE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_FRM_VE_STATUS_ADDR, HWIO_SB_FRM_VE_STATUS_RMSK)
#define HWIO_SB_FRM_VE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_FRM_VE_STATUS_ADDR, m)
#define HWIO_SB_FRM_VE_STATUS_VE_VAL_BMSK                                                         0xffffffff
#define HWIO_SB_FRM_VE_STATUS_VE_VAL_SHFT                                                                  0

#define HWIO_SB_INTF_CFG_ADDR                                                                     (SLIMBUS_REG_BASE      + 0x00000600)
#define HWIO_SB_INTF_CFG_PHYS                                                                     (SLIMBUS_REG_BASE_PHYS + 0x00000600)
#define HWIO_SB_INTF_CFG_RMSK                                                                            0x1
#define HWIO_SB_INTF_CFG_SHFT                                                                              0
#define HWIO_SB_INTF_CFG_IN                                                                       \
        in_dword_masked(HWIO_SB_INTF_CFG_ADDR, HWIO_SB_INTF_CFG_RMSK)
#define HWIO_SB_INTF_CFG_INM(m)                                                                   \
        in_dword_masked(HWIO_SB_INTF_CFG_ADDR, m)
#define HWIO_SB_INTF_CFG_OUT(v)                                                                   \
        out_dword(HWIO_SB_INTF_CFG_ADDR,v)
#define HWIO_SB_INTF_CFG_OUTM(m,v)                                                                \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_INTF_CFG_ADDR,m,v,HWIO_SB_INTF_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_INTF_CFG_ENABLE_BMSK                                                                     0x1
#define HWIO_SB_INTF_CFG_ENABLE_SHFT                                                                       0

#define HWIO_SB_INTF_STATUS_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000604)
#define HWIO_SB_INTF_STATUS_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000604)
#define HWIO_SB_INTF_STATUS_RMSK                                                                      0x3fff
#define HWIO_SB_INTF_STATUS_SHFT                                                                           0
#define HWIO_SB_INTF_STATUS_IN                                                                    \
        in_dword_masked(HWIO_SB_INTF_STATUS_ADDR, HWIO_SB_INTF_STATUS_RMSK)
#define HWIO_SB_INTF_STATUS_INM(m)                                                                \
        in_dword_masked(HWIO_SB_INTF_STATUS_ADDR, m)
#define HWIO_SB_INTF_STATUS_ERROR_BMSK                                                                   0x3
#define HWIO_SB_INTF_STATUS_ERROR_SHFT                                                                     0
#define HWIO_SB_INTF_STATUS_ENUMERATED_BMSK                                                              0x4
#define HWIO_SB_INTF_STATUS_ENUMERATED_SHFT                                                              0x2
#define HWIO_SB_INTF_STATUS_DEV_LA_BMSK                                                                0x7f8
#define HWIO_SB_INTF_STATUS_DEV_LA_SHFT                                                                  0x3
#define HWIO_SB_INTF_STATUS_FRAME_SYNC_ACQUIRED_BMSK                                                   0x800
#define HWIO_SB_INTF_STATUS_FRAME_SYNC_ACQUIRED_SHFT                                                     0xb
#define HWIO_SB_INTF_STATUS_SUPERFRAME_SYNC_ACQUIRED_BMSK                                             0x1000
#define HWIO_SB_INTF_STATUS_SUPERFRAME_SYNC_ACQUIRED_SHFT                                                0xc
#define HWIO_SB_INTF_STATUS_MESSAGE_SYNC_ACQUIRED_BMSK                                                0x2000
#define HWIO_SB_INTF_STATUS_MESSAGE_SYNC_ACQUIRED_SHFT                                                   0xd

#define HWIO_SB_INTF_INT_EN_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000610)
#define HWIO_SB_INTF_INT_EN_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000610)
#define HWIO_SB_INTF_INT_EN_RMSK                                                                         0x3
#define HWIO_SB_INTF_INT_EN_SHFT                                                                           0
#define HWIO_SB_INTF_INT_EN_IN                                                                    \
        in_dword_masked(HWIO_SB_INTF_INT_EN_ADDR, HWIO_SB_INTF_INT_EN_RMSK)
#define HWIO_SB_INTF_INT_EN_INM(m)                                                                \
        in_dword_masked(HWIO_SB_INTF_INT_EN_ADDR, m)
#define HWIO_SB_INTF_INT_EN_OUT(v)                                                                \
        out_dword(HWIO_SB_INTF_INT_EN_ADDR,v)
#define HWIO_SB_INTF_INT_EN_OUTM(m,v)                                                             \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_INTF_INT_EN_ADDR,m,v,HWIO_SB_INTF_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_INTF_INT_EN_DEV_ERR_BMSK                                                                 0x1
#define HWIO_SB_INTF_INT_EN_DEV_ERR_SHFT                                                                   0
#define HWIO_SB_INTF_INT_EN_IE_VE_CHANGE_BMSK                                                            0x2
#define HWIO_SB_INTF_INT_EN_IE_VE_CHANGE_SHFT                                                            0x1

#define HWIO_SB_INTF_INT_STATUS_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000614)
#define HWIO_SB_INTF_INT_STATUS_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000614)
#define HWIO_SB_INTF_INT_STATUS_RMSK                                                                     0x3
#define HWIO_SB_INTF_INT_STATUS_SHFT                                                                       0
#define HWIO_SB_INTF_INT_STATUS_IN                                                                \
        in_dword_masked(HWIO_SB_INTF_INT_STATUS_ADDR, HWIO_SB_INTF_INT_STATUS_RMSK)
#define HWIO_SB_INTF_INT_STATUS_INM(m)                                                            \
        in_dword_masked(HWIO_SB_INTF_INT_STATUS_ADDR, m)
#define HWIO_SB_INTF_INT_STATUS_DEV_ERR_BMSK                                                             0x1
#define HWIO_SB_INTF_INT_STATUS_DEV_ERR_SHFT                                                               0
#define HWIO_SB_INTF_INT_STATUS_IE_VE_CHANGE_BMSK                                                        0x2
#define HWIO_SB_INTF_INT_STATUS_IE_VE_CHANGE_SHFT                                                        0x1

#define HWIO_SB_INTF_INT_CLR_ADDR                                                                 (SLIMBUS_REG_BASE      + 0x00000618)
#define HWIO_SB_INTF_INT_CLR_PHYS                                                                 (SLIMBUS_REG_BASE_PHYS + 0x00000618)
#define HWIO_SB_INTF_INT_CLR_RMSK                                                                        0x3
#define HWIO_SB_INTF_INT_CLR_SHFT                                                                          0
#define HWIO_SB_INTF_INT_CLR_OUT(v)                                                               \
        out_dword(HWIO_SB_INTF_INT_CLR_ADDR,v)
#define HWIO_SB_INTF_INT_CLR_OUTM(m,v)                                                            \
        out_dword_masked(HWIO_SB_INTF_INT_CLR_ADDR,m,v,HWIO_SB_INTF_INT_CLR_shadow)
#define HWIO_SB_INTF_INT_CLR_DEV_ERR_BMSK                                                                0x1
#define HWIO_SB_INTF_INT_CLR_DEV_ERR_SHFT                                                                  0
#define HWIO_SB_INTF_INT_CLR_IE_VE_CHANGE_BMSK                                                           0x2
#define HWIO_SB_INTF_INT_CLR_IE_VE_CHANGE_SHFT                                                           0x1

#define HWIO_SB_INTF_IE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000630)
#define HWIO_SB_INTF_IE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000630)
#define HWIO_SB_INTF_IE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_INTF_IE_STATUS_SHFT                                                                        0
#define HWIO_SB_INTF_IE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_INTF_IE_STATUS_ADDR, HWIO_SB_INTF_IE_STATUS_RMSK)
#define HWIO_SB_INTF_IE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_INTF_IE_STATUS_ADDR, m)
#define HWIO_SB_INTF_IE_STATUS_UNSPRTD_MSG_BMSK                                                          0x1
#define HWIO_SB_INTF_IE_STATUS_UNSPRTD_MSG_SHFT                                                            0
#define HWIO_SB_INTF_IE_STATUS_DATA_TX_COL_BMSK                                                          0x2
#define HWIO_SB_INTF_IE_STATUS_DATA_TX_COL_SHFT                                                          0x1
#define HWIO_SB_INTF_IE_STATUS_RECONFIG_OBJ_BMSK                                                         0x4
#define HWIO_SB_INTF_IE_STATUS_RECONFIG_OBJ_SHFT                                                         0x2
#define HWIO_SB_INTF_IE_STATUS_EX_ERROR_BMSK                                                             0x8
#define HWIO_SB_INTF_IE_STATUS_EX_ERROR_SHFT                                                             0x3
#define HWIO_SB_INTF_IE_STATUS_MC_TX_COL_BMSK                                                           0x10
#define HWIO_SB_INTF_IE_STATUS_MC_TX_COL_SHFT                                                            0x4
#define HWIO_SB_INTF_IE_STATUS_LOST_FS_BMSK                                                             0x20
#define HWIO_SB_INTF_IE_STATUS_LOST_FS_SHFT                                                              0x5
#define HWIO_SB_INTF_IE_STATUS_LOST_SFS_BMSK                                                            0x40
#define HWIO_SB_INTF_IE_STATUS_LOST_SFS_SHFT                                                             0x6
#define HWIO_SB_INTF_IE_STATUS_LOST_MS_BMSK                                                             0x80
#define HWIO_SB_INTF_IE_STATUS_LOST_MS_SHFT                                                              0x7
#define HWIO_SB_INTF_IE_STATUS_DS_OVERLAP_BMSK                                                         0x100
#define HWIO_SB_INTF_IE_STATUS_DS_OVERLAP_SHFT                                                           0x8
#define HWIO_SB_INTF_IE_STATUS_DEV_CLASS_VER_BMSK                                                   0xff0000
#define HWIO_SB_INTF_IE_STATUS_DEV_CLASS_VER_SHFT                                                       0x10
#define HWIO_SB_INTF_IE_STATUS_DEV_CLASS_CODE_BMSK                                                0xff000000
#define HWIO_SB_INTF_IE_STATUS_DEV_CLASS_CODE_SHFT                                                      0x18

#define HWIO_SB_INTF_VE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000640)
#define HWIO_SB_INTF_VE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000640)
#define HWIO_SB_INTF_VE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_INTF_VE_STATUS_SHFT                                                                        0
#define HWIO_SB_INTF_VE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_INTF_VE_STATUS_ADDR, HWIO_SB_INTF_VE_STATUS_RMSK)
#define HWIO_SB_INTF_VE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_INTF_VE_STATUS_ADDR, m)
#define HWIO_SB_INTF_VE_STATUS_VE_VAL_BMSK                                                        0xffffffff
#define HWIO_SB_INTF_VE_STATUS_VE_VAL_SHFT                                                                 0

#define HWIO_SB_NGD1_CFG_ADDR                                                                     (SLIMBUS_REG_BASE      + 0x00000800)
#define HWIO_SB_NGD1_CFG_PHYS                                                                     (SLIMBUS_REG_BASE_PHYS + 0x00000800)
#define HWIO_SB_NGD1_CFG_RMSK                                                                            0x7
#define HWIO_SB_NGD1_CFG_SHFT                                                                              0
#define HWIO_SB_NGD1_CFG_IN                                                                       \
        in_dword_masked(HWIO_SB_NGD1_CFG_ADDR, HWIO_SB_NGD1_CFG_RMSK)
#define HWIO_SB_NGD1_CFG_INM(m)                                                                   \
        in_dword_masked(HWIO_SB_NGD1_CFG_ADDR, m)
#define HWIO_SB_NGD1_CFG_OUT(v)                                                                   \
        out_dword(HWIO_SB_NGD1_CFG_ADDR,v)
#define HWIO_SB_NGD1_CFG_OUTM(m,v)                                                                \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD1_CFG_ADDR,m,v,HWIO_SB_NGD1_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD1_CFG_ENABLE_BMSK                                                                     0x1
#define HWIO_SB_NGD1_CFG_ENABLE_SHFT                                                                       0
#define HWIO_SB_NGD1_CFG_RX_MSGQ_EN_BMSK                                                                 0x2
#define HWIO_SB_NGD1_CFG_RX_MSGQ_EN_SHFT                                                                 0x1
#define HWIO_SB_NGD1_CFG_TX_MSGQ_EN_BMSK                                                                 0x4
#define HWIO_SB_NGD1_CFG_TX_MSGQ_EN_SHFT                                                                 0x2

#define HWIO_SB_NGD1_STATUS_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000804)
#define HWIO_SB_NGD1_STATUS_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000804)
#define HWIO_SB_NGD1_STATUS_RMSK                                                                   0x7ffffff
#define HWIO_SB_NGD1_STATUS_SHFT                                                                           0
#define HWIO_SB_NGD1_STATUS_IN                                                                    \
        in_dword_masked(HWIO_SB_NGD1_STATUS_ADDR, HWIO_SB_NGD1_STATUS_RMSK)
#define HWIO_SB_NGD1_STATUS_INM(m)                                                                \
        in_dword_masked(HWIO_SB_NGD1_STATUS_ADDR, m)
#define HWIO_SB_NGD1_STATUS_TX_MSG_BUFFER_BUSY_BMSK                                                      0x1
#define HWIO_SB_NGD1_STATUS_TX_MSG_BUFFER_BUSY_SHFT                                                        0
#define HWIO_SB_NGD1_STATUS_ENUMERATED_BMSK                                                              0x2
#define HWIO_SB_NGD1_STATUS_ENUMERATED_SHFT                                                              0x1
#define HWIO_SB_NGD1_STATUS_PIPE_NUM_OFFSET_BMSK                                                       0x3fc
#define HWIO_SB_NGD1_STATUS_PIPE_NUM_OFFSET_SHFT                                                         0x2
#define HWIO_SB_NGD1_STATUS_MSGQ_SUPPORT_BMSK                                                          0x400
#define HWIO_SB_NGD1_STATUS_MSGQ_SUPPORT_SHFT                                                            0xa
#define HWIO_SB_NGD1_STATUS_ERROR_BMSK                                                                0x1800
#define HWIO_SB_NGD1_STATUS_ERROR_SHFT                                                                   0xb
#define HWIO_SB_NGD1_STATUS_ACKED_TX_MSG_MC_BMSK                                                     0xfe000
#define HWIO_SB_NGD1_STATUS_ACKED_TX_MSG_MC_SHFT                                                         0xd
#define HWIO_SB_NGD1_STATUS_NACKED_TX_MSG_MC_BMSK                                                  0x7f00000
#define HWIO_SB_NGD1_STATUS_NACKED_TX_MSG_MC_SHFT                                                       0x14

#define HWIO_SB_NGD1_RX_MSGQ_CFG_ADDR                                                             (SLIMBUS_REG_BASE      + 0x00000808)
#define HWIO_SB_NGD1_RX_MSGQ_CFG_PHYS                                                             (SLIMBUS_REG_BASE_PHYS + 0x00000808)
#define HWIO_SB_NGD1_RX_MSGQ_CFG_RMSK                                                             0xffffffff
#define HWIO_SB_NGD1_RX_MSGQ_CFG_SHFT                                                                      0
#define HWIO_SB_NGD1_RX_MSGQ_CFG_IN                                                               \
        in_dword_masked(HWIO_SB_NGD1_RX_MSGQ_CFG_ADDR, HWIO_SB_NGD1_RX_MSGQ_CFG_RMSK)
#define HWIO_SB_NGD1_RX_MSGQ_CFG_INM(m)                                                           \
        in_dword_masked(HWIO_SB_NGD1_RX_MSGQ_CFG_ADDR, m)
#define HWIO_SB_NGD1_RX_MSGQ_CFG_OUT(v)                                                           \
        out_dword(HWIO_SB_NGD1_RX_MSGQ_CFG_ADDR,v)
#define HWIO_SB_NGD1_RX_MSGQ_CFG_OUTM(m,v)                                                        \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD1_RX_MSGQ_CFG_ADDR,m,v,HWIO_SB_NGD1_RX_MSGQ_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD1_RX_MSGQ_CFG_BLOCK_SIZE_BMSK                                                        0xff
#define HWIO_SB_NGD1_RX_MSGQ_CFG_BLOCK_SIZE_SHFT                                                           0
#define HWIO_SB_NGD1_RX_MSGQ_CFG_TRANS_SIZE_BMSK                                                      0xff00
#define HWIO_SB_NGD1_RX_MSGQ_CFG_TRANS_SIZE_SHFT                                                         0x8
#define HWIO_SB_NGD1_RX_MSGQ_CFG_TIME_OUT_VAL_BMSK                                                0xffff0000
#define HWIO_SB_NGD1_RX_MSGQ_CFG_TIME_OUT_VAL_SHFT                                                      0x10

#define HWIO_SB_NGD1_INT_EN_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000810)
#define HWIO_SB_NGD1_INT_EN_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000810)
#define HWIO_SB_NGD1_INT_EN_RMSK                                                                  0xff000000
#define HWIO_SB_NGD1_INT_EN_SHFT                                                                           0
#define HWIO_SB_NGD1_INT_EN_IN                                                                    \
        in_dword_masked(HWIO_SB_NGD1_INT_EN_ADDR, HWIO_SB_NGD1_INT_EN_RMSK)
#define HWIO_SB_NGD1_INT_EN_INM(m)                                                                \
        in_dword_masked(HWIO_SB_NGD1_INT_EN_ADDR, m)
#define HWIO_SB_NGD1_INT_EN_OUT(v)                                                                \
        out_dword(HWIO_SB_NGD1_INT_EN_ADDR,v)
#define HWIO_SB_NGD1_INT_EN_OUTM(m,v)                                                             \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD1_INT_EN_ADDR,m,v,HWIO_SB_NGD1_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD1_INT_EN_TX_MSG_SENT_BMSK                                                      0x80000000
#define HWIO_SB_NGD1_INT_EN_TX_MSG_SENT_SHFT                                                            0x1f
#define HWIO_SB_NGD1_INT_EN_RX_MSG_RCVD_BMSK                                                      0x40000000
#define HWIO_SB_NGD1_INT_EN_RX_MSG_RCVD_SHFT                                                            0x1e
#define HWIO_SB_NGD1_INT_EN_DEV_ERR_BMSK                                                          0x20000000
#define HWIO_SB_NGD1_INT_EN_DEV_ERR_SHFT                                                                0x1d
#define HWIO_SB_NGD1_INT_EN_IE_VE_CHANGE_BMSK                                                     0x10000000
#define HWIO_SB_NGD1_INT_EN_IE_VE_CHANGE_SHFT                                                           0x1c
#define HWIO_SB_NGD1_INT_EN_INVALID_TX_MSG_BMSK                                                    0x8000000
#define HWIO_SB_NGD1_INT_EN_INVALID_TX_MSG_SHFT                                                         0x1b
#define HWIO_SB_NGD1_INT_EN_TX_MSG_BUF_CONTENTION_BMSK                                             0x4000000
#define HWIO_SB_NGD1_INT_EN_TX_MSG_BUF_CONTENTION_SHFT                                                  0x1a
#define HWIO_SB_NGD1_INT_EN_TX_MSG_NACKED_TWICE_BMSK                                               0x2000000
#define HWIO_SB_NGD1_INT_EN_TX_MSG_NACKED_TWICE_SHFT                                                    0x19
#define HWIO_SB_NGD1_INT_EN_RECONFIG_DONE_BMSK                                                     0x1000000
#define HWIO_SB_NGD1_INT_EN_RECONFIG_DONE_SHFT                                                          0x18

#define HWIO_SB_NGD1_INT_STATUS_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000814)
#define HWIO_SB_NGD1_INT_STATUS_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000814)
#define HWIO_SB_NGD1_INT_STATUS_RMSK                                                              0xff000000
#define HWIO_SB_NGD1_INT_STATUS_SHFT                                                                       0
#define HWIO_SB_NGD1_INT_STATUS_IN                                                                \
        in_dword_masked(HWIO_SB_NGD1_INT_STATUS_ADDR, HWIO_SB_NGD1_INT_STATUS_RMSK)
#define HWIO_SB_NGD1_INT_STATUS_INM(m)                                                            \
        in_dword_masked(HWIO_SB_NGD1_INT_STATUS_ADDR, m)
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_SENT_BMSK                                                  0x80000000
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_SENT_SHFT                                                        0x1f
#define HWIO_SB_NGD1_INT_STATUS_RX_MSG_RCVD_BMSK                                                  0x40000000
#define HWIO_SB_NGD1_INT_STATUS_RX_MSG_RCVD_SHFT                                                        0x1e
#define HWIO_SB_NGD1_INT_STATUS_DEV_ERR_BMSK                                                      0x20000000
#define HWIO_SB_NGD1_INT_STATUS_DEV_ERR_SHFT                                                            0x1d
#define HWIO_SB_NGD1_INT_STATUS_IE_VE_CHANGE_BMSK                                                 0x10000000
#define HWIO_SB_NGD1_INT_STATUS_IE_VE_CHANGE_SHFT                                                       0x1c
#define HWIO_SB_NGD1_INT_STATUS_INVALID_TX_MSG_BMSK                                                0x8000000
#define HWIO_SB_NGD1_INT_STATUS_INVALID_TX_MSG_SHFT                                                     0x1b
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_BUF_CONTENTION_BMSK                                         0x4000000
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_BUF_CONTENTION_SHFT                                              0x1a
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_NACKED_TWICE_BMSK                                           0x2000000
#define HWIO_SB_NGD1_INT_STATUS_TX_MSG_NACKED_TWICE_SHFT                                                0x19
#define HWIO_SB_NGD1_INT_STATUS_RECONFIG_DONE_BMSK                                                 0x1000000
#define HWIO_SB_NGD1_INT_STATUS_RECONFIG_DONE_SHFT                                                      0x18

#define HWIO_SB_NGD1_INT_CLR_ADDR                                                                 (SLIMBUS_REG_BASE      + 0x00000818)
#define HWIO_SB_NGD1_INT_CLR_PHYS                                                                 (SLIMBUS_REG_BASE_PHYS + 0x00000818)
#define HWIO_SB_NGD1_INT_CLR_RMSK                                                                 0xff000000
#define HWIO_SB_NGD1_INT_CLR_SHFT                                                                          0
#define HWIO_SB_NGD1_INT_CLR_OUT(v)                                                               \
        out_dword(HWIO_SB_NGD1_INT_CLR_ADDR,v)
#define HWIO_SB_NGD1_INT_CLR_OUTM(m,v)                                                            \
        out_dword_masked(HWIO_SB_NGD1_INT_CLR_ADDR,m,v,HWIO_SB_NGD1_INT_CLR_shadow)
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_SENT_BMSK                                                     0x80000000
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_SENT_SHFT                                                           0x1f
#define HWIO_SB_NGD1_INT_CLR_RX_MSG_RCVD_BMSK                                                     0x40000000
#define HWIO_SB_NGD1_INT_CLR_RX_MSG_RCVD_SHFT                                                           0x1e
#define HWIO_SB_NGD1_INT_CLR_DEV_ERR_BMSK                                                         0x20000000
#define HWIO_SB_NGD1_INT_CLR_DEV_ERR_SHFT                                                               0x1d
#define HWIO_SB_NGD1_INT_CLR_IE_VE_CHANGE_BMSK                                                    0x10000000
#define HWIO_SB_NGD1_INT_CLR_IE_VE_CHANGE_SHFT                                                          0x1c
#define HWIO_SB_NGD1_INT_CLR_INVALID_TX_MSG_BMSK                                                   0x8000000
#define HWIO_SB_NGD1_INT_CLR_INVALID_TX_MSG_SHFT                                                        0x1b
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_BUF_CONTENTION_BMSK                                            0x4000000
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_BUF_CONTENTION_SHFT                                                 0x1a
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_NACKED_TWICE_BMSK                                              0x2000000
#define HWIO_SB_NGD1_INT_CLR_TX_MSG_NACKED_TWICE_SHFT                                                   0x19
#define HWIO_SB_NGD1_INT_CLR_RECONFIG_DONE_BMSK                                                    0x1000000
#define HWIO_SB_NGD1_INT_CLR_RECONFIG_DONE_SHFT                                                         0x18

#define HWIO_SB_NGD1_TX_MSGn_ADDR(n)                                                              (SLIMBUS_REG_BASE      + 0x00000830 + 4 * (n))
#define HWIO_SB_NGD1_TX_MSGn_PHYS(n)                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000830 + 4 * (n))
#define HWIO_SB_NGD1_TX_MSGn_RMSK                                                                 0xffffffff
#define HWIO_SB_NGD1_TX_MSGn_SHFT                                                                          0
#define HWIO_SB_NGD1_TX_MSGn_MAXn                                                                        0x9
#define HWIO_SB_NGD1_TX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_NGD1_TX_MSGn_ADDR(n),val)
#define HWIO_SB_NGD1_TX_MSGn_OUTMI(n,mask,val) \
        out_dword_masked(HWIO_SB_NGD1_TX_MSGn_ADDR(n),mask,val,HWIO_SB_NGD1_TX_MSGn_shadow[n])
#define HWIO_SB_NGD1_TX_MSGn_MSGVAL_BMSK                                                          0xffffffff
#define HWIO_SB_NGD1_TX_MSGn_MSGVAL_SHFT                                                                   0

#define HWIO_SB_NGD1_RX_MSGn_ADDR(n)                                                              (SLIMBUS_REG_BASE      + 0x00000870 + 4 * (n))
#define HWIO_SB_NGD1_RX_MSGn_PHYS(n)                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000870 + 4 * (n))
#define HWIO_SB_NGD1_RX_MSGn_RMSK                                                                 0xffffffff
#define HWIO_SB_NGD1_RX_MSGn_SHFT                                                                          0
#define HWIO_SB_NGD1_RX_MSGn_MAXn                                                                        0x9
#define HWIO_SB_NGD1_RX_MSGn_INI(n) \
        in_dword(HWIO_SB_NGD1_RX_MSGn_ADDR(n))
#define HWIO_SB_NGD1_RX_MSGn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_NGD1_RX_MSGn_ADDR(n), mask)
#define HWIO_SB_NGD1_RX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_NGD1_RX_MSGn_ADDR(n),val)
#define HWIO_SB_NGD1_RX_MSGn_MSGVAL_BMSK                                                          0xffffffff
#define HWIO_SB_NGD1_RX_MSGn_MSGVAL_SHFT                                                                   0

#define HWIO_SB_NGD1_IE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x000008f0)
#define HWIO_SB_NGD1_IE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x000008f0)
#define HWIO_SB_NGD1_IE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_NGD1_IE_STATUS_SHFT                                                                        0
#define HWIO_SB_NGD1_IE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_NGD1_IE_STATUS_ADDR, HWIO_SB_NGD1_IE_STATUS_RMSK)
#define HWIO_SB_NGD1_IE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_NGD1_IE_STATUS_ADDR, m)
#define HWIO_SB_NGD1_IE_STATUS_UNSPRTD_MSG_BMSK                                                          0x1
#define HWIO_SB_NGD1_IE_STATUS_UNSPRTD_MSG_SHFT                                                            0
#define HWIO_SB_NGD1_IE_STATUS_DATA_TX_COL_BMSK                                                          0x2
#define HWIO_SB_NGD1_IE_STATUS_DATA_TX_COL_SHFT                                                          0x1
#define HWIO_SB_NGD1_IE_STATUS_RECONFIG_OBJ_BMSK                                                         0x4
#define HWIO_SB_NGD1_IE_STATUS_RECONFIG_OBJ_SHFT                                                         0x2
#define HWIO_SB_NGD1_IE_STATUS_EX_ERROR_BMSK                                                             0x8
#define HWIO_SB_NGD1_IE_STATUS_EX_ERROR_SHFT                                                             0x3
#define HWIO_SB_NGD1_IE_STATUS_DEV_CLASS_VER_BMSK                                                   0xff0000
#define HWIO_SB_NGD1_IE_STATUS_DEV_CLASS_VER_SHFT                                                       0x10
#define HWIO_SB_NGD1_IE_STATUS_DEV_CLASS_CODE_BMSK                                                0xff000000
#define HWIO_SB_NGD1_IE_STATUS_DEV_CLASS_CODE_SHFT                                                      0x18

#define HWIO_SB_NGD1_VE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000900)
#define HWIO_SB_NGD1_VE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000900)
#define HWIO_SB_NGD1_VE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_NGD1_VE_STATUS_SHFT                                                                        0
#define HWIO_SB_NGD1_VE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_NGD1_VE_STATUS_ADDR, HWIO_SB_NGD1_VE_STATUS_RMSK)
#define HWIO_SB_NGD1_VE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_NGD1_VE_STATUS_ADDR, m)
#define HWIO_SB_NGD1_VE_STATUS_VE_VAL_BMSK                                                        0xffffffff
#define HWIO_SB_NGD1_VE_STATUS_VE_VAL_SHFT                                                                 0

#define HWIO_SB_NGD2_CFG_ADDR                                                                     (SLIMBUS_REG_BASE      + 0x00000a00)
#define HWIO_SB_NGD2_CFG_PHYS                                                                     (SLIMBUS_REG_BASE_PHYS + 0x00000a00)
#define HWIO_SB_NGD2_CFG_RMSK                                                                            0x7
#define HWIO_SB_NGD2_CFG_SHFT                                                                              0
#define HWIO_SB_NGD2_CFG_IN                                                                       \
        in_dword_masked(HWIO_SB_NGD2_CFG_ADDR, HWIO_SB_NGD2_CFG_RMSK)
#define HWIO_SB_NGD2_CFG_INM(m)                                                                   \
        in_dword_masked(HWIO_SB_NGD2_CFG_ADDR, m)
#define HWIO_SB_NGD2_CFG_OUT(v)                                                                   \
        out_dword(HWIO_SB_NGD2_CFG_ADDR,v)
#define HWIO_SB_NGD2_CFG_OUTM(m,v)                                                                \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD2_CFG_ADDR,m,v,HWIO_SB_NGD2_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD2_CFG_ENABLE_BMSK                                                                     0x1
#define HWIO_SB_NGD2_CFG_ENABLE_SHFT                                                                       0
#define HWIO_SB_NGD2_CFG_RX_MSGQ_EN_BMSK                                                                 0x2
#define HWIO_SB_NGD2_CFG_RX_MSGQ_EN_SHFT                                                                 0x1
#define HWIO_SB_NGD2_CFG_TX_MSGQ_EN_BMSK                                                                 0x4
#define HWIO_SB_NGD2_CFG_TX_MSGQ_EN_SHFT                                                                 0x2

#define HWIO_SB_NGD2_STATUS_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000a04)
#define HWIO_SB_NGD2_STATUS_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000a04)
#define HWIO_SB_NGD2_STATUS_RMSK                                                                   0x7ffffff
#define HWIO_SB_NGD2_STATUS_SHFT                                                                           0
#define HWIO_SB_NGD2_STATUS_IN                                                                    \
        in_dword_masked(HWIO_SB_NGD2_STATUS_ADDR, HWIO_SB_NGD2_STATUS_RMSK)
#define HWIO_SB_NGD2_STATUS_INM(m)                                                                \
        in_dword_masked(HWIO_SB_NGD2_STATUS_ADDR, m)
#define HWIO_SB_NGD2_STATUS_TX_MSG_BUFFER_BUSY_BMSK                                                      0x1
#define HWIO_SB_NGD2_STATUS_TX_MSG_BUFFER_BUSY_SHFT                                                        0
#define HWIO_SB_NGD2_STATUS_ENUMERATED_BMSK                                                              0x2
#define HWIO_SB_NGD2_STATUS_ENUMERATED_SHFT                                                              0x1
#define HWIO_SB_NGD2_STATUS_PIPE_NUM_OFFSET_BMSK                                                       0x3fc
#define HWIO_SB_NGD2_STATUS_PIPE_NUM_OFFSET_SHFT                                                         0x2
#define HWIO_SB_NGD2_STATUS_MSGQ_SUPPORT_BMSK                                                          0x400
#define HWIO_SB_NGD2_STATUS_MSGQ_SUPPORT_SHFT                                                            0xa
#define HWIO_SB_NGD2_STATUS_ERROR_BMSK                                                                0x1800
#define HWIO_SB_NGD2_STATUS_ERROR_SHFT                                                                   0xb
#define HWIO_SB_NGD2_STATUS_ACKED_TX_MSG_MC_BMSK                                                     0xfe000
#define HWIO_SB_NGD2_STATUS_ACKED_TX_MSG_MC_SHFT                                                         0xd
#define HWIO_SB_NGD2_STATUS_NACKED_TX_MSG_MC_BMSK                                                  0x7f00000
#define HWIO_SB_NGD2_STATUS_NACKED_TX_MSG_MC_SHFT                                                       0x14

#define HWIO_SB_NGD2_RX_MSGQ_CFG_ADDR                                                             (SLIMBUS_REG_BASE      + 0x00000a08)
#define HWIO_SB_NGD2_RX_MSGQ_CFG_PHYS                                                             (SLIMBUS_REG_BASE_PHYS + 0x00000a08)
#define HWIO_SB_NGD2_RX_MSGQ_CFG_RMSK                                                             0xffffffff
#define HWIO_SB_NGD2_RX_MSGQ_CFG_SHFT                                                                      0
#define HWIO_SB_NGD2_RX_MSGQ_CFG_IN                                                               \
        in_dword_masked(HWIO_SB_NGD2_RX_MSGQ_CFG_ADDR, HWIO_SB_NGD2_RX_MSGQ_CFG_RMSK)
#define HWIO_SB_NGD2_RX_MSGQ_CFG_INM(m)                                                           \
        in_dword_masked(HWIO_SB_NGD2_RX_MSGQ_CFG_ADDR, m)
#define HWIO_SB_NGD2_RX_MSGQ_CFG_OUT(v)                                                           \
        out_dword(HWIO_SB_NGD2_RX_MSGQ_CFG_ADDR,v)
#define HWIO_SB_NGD2_RX_MSGQ_CFG_OUTM(m,v)                                                        \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD2_RX_MSGQ_CFG_ADDR,m,v,HWIO_SB_NGD2_RX_MSGQ_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD2_RX_MSGQ_CFG_BLOCK_SIZE_BMSK                                                        0xff
#define HWIO_SB_NGD2_RX_MSGQ_CFG_BLOCK_SIZE_SHFT                                                           0
#define HWIO_SB_NGD2_RX_MSGQ_CFG_TRANS_SIZE_BMSK                                                      0xff00
#define HWIO_SB_NGD2_RX_MSGQ_CFG_TRANS_SIZE_SHFT                                                         0x8
#define HWIO_SB_NGD2_RX_MSGQ_CFG_TIME_OUT_VAL_BMSK                                                0xffff0000
#define HWIO_SB_NGD2_RX_MSGQ_CFG_TIME_OUT_VAL_SHFT                                                      0x10

#define HWIO_SB_NGD2_INT_EN_ADDR                                                                  (SLIMBUS_REG_BASE      + 0x00000a10)
#define HWIO_SB_NGD2_INT_EN_PHYS                                                                  (SLIMBUS_REG_BASE_PHYS + 0x00000a10)
#define HWIO_SB_NGD2_INT_EN_RMSK                                                                  0xff000000
#define HWIO_SB_NGD2_INT_EN_SHFT                                                                           0
#define HWIO_SB_NGD2_INT_EN_IN                                                                    \
        in_dword_masked(HWIO_SB_NGD2_INT_EN_ADDR, HWIO_SB_NGD2_INT_EN_RMSK)
#define HWIO_SB_NGD2_INT_EN_INM(m)                                                                \
        in_dword_masked(HWIO_SB_NGD2_INT_EN_ADDR, m)
#define HWIO_SB_NGD2_INT_EN_OUT(v)                                                                \
        out_dword(HWIO_SB_NGD2_INT_EN_ADDR,v)
#define HWIO_SB_NGD2_INT_EN_OUTM(m,v)                                                             \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_NGD2_INT_EN_ADDR,m,v,HWIO_SB_NGD2_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_NGD2_INT_EN_TX_MSG_SENT_BMSK                                                      0x80000000
#define HWIO_SB_NGD2_INT_EN_TX_MSG_SENT_SHFT                                                            0x1f
#define HWIO_SB_NGD2_INT_EN_RX_MSG_RCVD_BMSK                                                      0x40000000
#define HWIO_SB_NGD2_INT_EN_RX_MSG_RCVD_SHFT                                                            0x1e
#define HWIO_SB_NGD2_INT_EN_DEV_ERR_BMSK                                                          0x20000000
#define HWIO_SB_NGD2_INT_EN_DEV_ERR_SHFT                                                                0x1d
#define HWIO_SB_NGD2_INT_EN_IE_VE_CHANGE_BMSK                                                     0x10000000
#define HWIO_SB_NGD2_INT_EN_IE_VE_CHANGE_SHFT                                                           0x1c
#define HWIO_SB_NGD2_INT_EN_INVALID_TX_MSG_BMSK                                                    0x8000000
#define HWIO_SB_NGD2_INT_EN_INVALID_TX_MSG_SHFT                                                         0x1b
#define HWIO_SB_NGD2_INT_EN_TX_MSG_BUF_CONTENTION_BMSK                                             0x4000000
#define HWIO_SB_NGD2_INT_EN_TX_MSG_BUF_CONTENTION_SHFT                                                  0x1a
#define HWIO_SB_NGD2_INT_EN_TX_MSG_NACKED_TWICE_BMSK                                               0x2000000
#define HWIO_SB_NGD2_INT_EN_TX_MSG_NACKED_TWICE_SHFT                                                    0x19
#define HWIO_SB_NGD2_INT_EN_RECONFIG_DONE_BMSK                                                     0x1000000
#define HWIO_SB_NGD2_INT_EN_RECONFIG_DONE_SHFT                                                          0x18

#define HWIO_SB_NGD2_INT_STATUS_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00000a14)
#define HWIO_SB_NGD2_INT_STATUS_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000a14)
#define HWIO_SB_NGD2_INT_STATUS_RMSK                                                              0xff000000
#define HWIO_SB_NGD2_INT_STATUS_SHFT                                                                       0
#define HWIO_SB_NGD2_INT_STATUS_IN                                                                \
        in_dword_masked(HWIO_SB_NGD2_INT_STATUS_ADDR, HWIO_SB_NGD2_INT_STATUS_RMSK)
#define HWIO_SB_NGD2_INT_STATUS_INM(m)                                                            \
        in_dword_masked(HWIO_SB_NGD2_INT_STATUS_ADDR, m)
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_SENT_BMSK                                                  0x80000000
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_SENT_SHFT                                                        0x1f
#define HWIO_SB_NGD2_INT_STATUS_RX_MSG_RCVD_BMSK                                                  0x40000000
#define HWIO_SB_NGD2_INT_STATUS_RX_MSG_RCVD_SHFT                                                        0x1e
#define HWIO_SB_NGD2_INT_STATUS_DEV_ERR_BMSK                                                      0x20000000
#define HWIO_SB_NGD2_INT_STATUS_DEV_ERR_SHFT                                                            0x1d
#define HWIO_SB_NGD2_INT_STATUS_IE_VE_CHANGE_BMSK                                                 0x10000000
#define HWIO_SB_NGD2_INT_STATUS_IE_VE_CHANGE_SHFT                                                       0x1c
#define HWIO_SB_NGD2_INT_STATUS_INVALID_TX_MSG_BMSK                                                0x8000000
#define HWIO_SB_NGD2_INT_STATUS_INVALID_TX_MSG_SHFT                                                     0x1b
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_BUF_CONTENTION_BMSK                                         0x4000000
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_BUF_CONTENTION_SHFT                                              0x1a
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_NACKED_TWICE_BMSK                                           0x2000000
#define HWIO_SB_NGD2_INT_STATUS_TX_MSG_NACKED_TWICE_SHFT                                                0x19
#define HWIO_SB_NGD2_INT_STATUS_RECONFIG_DONE_BMSK                                                 0x1000000
#define HWIO_SB_NGD2_INT_STATUS_RECONFIG_DONE_SHFT                                                      0x18

#define HWIO_SB_NGD2_INT_CLR_ADDR                                                                 (SLIMBUS_REG_BASE      + 0x00000a18)
#define HWIO_SB_NGD2_INT_CLR_PHYS                                                                 (SLIMBUS_REG_BASE_PHYS + 0x00000a18)
#define HWIO_SB_NGD2_INT_CLR_RMSK                                                                 0xff000000
#define HWIO_SB_NGD2_INT_CLR_SHFT                                                                          0
#define HWIO_SB_NGD2_INT_CLR_OUT(v)                                                               \
        out_dword(HWIO_SB_NGD2_INT_CLR_ADDR,v)
#define HWIO_SB_NGD2_INT_CLR_OUTM(m,v)                                                            \
        out_dword_masked(HWIO_SB_NGD2_INT_CLR_ADDR,m,v,HWIO_SB_NGD2_INT_CLR_shadow)
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_SENT_BMSK                                                     0x80000000
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_SENT_SHFT                                                           0x1f
#define HWIO_SB_NGD2_INT_CLR_RX_MSG_RCVD_BMSK                                                     0x40000000
#define HWIO_SB_NGD2_INT_CLR_RX_MSG_RCVD_SHFT                                                           0x1e
#define HWIO_SB_NGD2_INT_CLR_DEV_ERR_BMSK                                                         0x20000000
#define HWIO_SB_NGD2_INT_CLR_DEV_ERR_SHFT                                                               0x1d
#define HWIO_SB_NGD2_INT_CLR_IE_VE_CHANGE_BMSK                                                    0x10000000
#define HWIO_SB_NGD2_INT_CLR_IE_VE_CHANGE_SHFT                                                          0x1c
#define HWIO_SB_NGD2_INT_CLR_INVALID_TX_MSG_BMSK                                                   0x8000000
#define HWIO_SB_NGD2_INT_CLR_INVALID_TX_MSG_SHFT                                                        0x1b
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_BUF_CONTENTION_BMSK                                            0x4000000
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_BUF_CONTENTION_SHFT                                                 0x1a
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_NACKED_TWICE_BMSK                                              0x2000000
#define HWIO_SB_NGD2_INT_CLR_TX_MSG_NACKED_TWICE_SHFT                                                   0x19
#define HWIO_SB_NGD2_INT_CLR_RECONFIG_DONE_BMSK                                                    0x1000000
#define HWIO_SB_NGD2_INT_CLR_RECONFIG_DONE_SHFT                                                         0x18

#define HWIO_SB_NGD2_TX_MSGn_ADDR(n)                                                              (SLIMBUS_REG_BASE      + 0x00000a30 + 4 * (n))
#define HWIO_SB_NGD2_TX_MSGn_PHYS(n)                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000a30 + 4 * (n))
#define HWIO_SB_NGD2_TX_MSGn_RMSK                                                                 0xffffffff
#define HWIO_SB_NGD2_TX_MSGn_SHFT                                                                          0
#define HWIO_SB_NGD2_TX_MSGn_MAXn                                                                        0x9
#define HWIO_SB_NGD2_TX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_NGD2_TX_MSGn_ADDR(n),val)
#define HWIO_SB_NGD2_TX_MSGn_OUTMI(n,mask,val) \
        out_dword_masked(HWIO_SB_NGD2_TX_MSGn_ADDR(n),mask,val,HWIO_SB_NGD2_TX_MSGn_shadow[n])
#define HWIO_SB_NGD2_TX_MSGn_MSGVAL_BMSK                                                          0xffffffff
#define HWIO_SB_NGD2_TX_MSGn_MSGVAL_SHFT                                                                   0

#define HWIO_SB_NGD2_RX_MSGn_ADDR(n)                                                              (SLIMBUS_REG_BASE      + 0x00000a70 + 4 * (n))
#define HWIO_SB_NGD2_RX_MSGn_PHYS(n)                                                              (SLIMBUS_REG_BASE_PHYS + 0x00000a70 + 4 * (n))
#define HWIO_SB_NGD2_RX_MSGn_RMSK                                                                 0xffffffff
#define HWIO_SB_NGD2_RX_MSGn_SHFT                                                                          0
#define HWIO_SB_NGD2_RX_MSGn_MAXn                                                                        0x9
#define HWIO_SB_NGD2_RX_MSGn_INI(n) \
        in_dword(HWIO_SB_NGD2_RX_MSGn_ADDR(n))
#define HWIO_SB_NGD2_RX_MSGn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_NGD2_RX_MSGn_ADDR(n), mask)
#define HWIO_SB_NGD2_RX_MSGn_OUTI(n,val) \
        out_dword(HWIO_SB_NGD2_RX_MSGn_ADDR(n),val)
#define HWIO_SB_NGD2_RX_MSGn_MSGVAL_BMSK                                                          0xffffffff
#define HWIO_SB_NGD2_RX_MSGn_MSGVAL_SHFT                                                                   0

#define HWIO_SB_NGD2_IE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000af0)
#define HWIO_SB_NGD2_IE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000af0)
#define HWIO_SB_NGD2_IE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_NGD2_IE_STATUS_SHFT                                                                        0
#define HWIO_SB_NGD2_IE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_NGD2_IE_STATUS_ADDR, HWIO_SB_NGD2_IE_STATUS_RMSK)
#define HWIO_SB_NGD2_IE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_NGD2_IE_STATUS_ADDR, m)
#define HWIO_SB_NGD2_IE_STATUS_UNSPRTD_MSG_BMSK                                                          0x1
#define HWIO_SB_NGD2_IE_STATUS_UNSPRTD_MSG_SHFT                                                            0
#define HWIO_SB_NGD2_IE_STATUS_DATA_TX_COL_BMSK                                                          0x2
#define HWIO_SB_NGD2_IE_STATUS_DATA_TX_COL_SHFT                                                          0x1
#define HWIO_SB_NGD2_IE_STATUS_RECONFIG_OBJ_BMSK                                                         0x4
#define HWIO_SB_NGD2_IE_STATUS_RECONFIG_OBJ_SHFT                                                         0x2
#define HWIO_SB_NGD2_IE_STATUS_EX_ERROR_BMSK                                                             0x8
#define HWIO_SB_NGD2_IE_STATUS_EX_ERROR_SHFT                                                             0x3
#define HWIO_SB_NGD2_IE_STATUS_DEV_CLASS_VER_BMSK                                                   0xff0000
#define HWIO_SB_NGD2_IE_STATUS_DEV_CLASS_VER_SHFT                                                       0x10
#define HWIO_SB_NGD2_IE_STATUS_DEV_CLASS_CODE_BMSK                                                0xff000000
#define HWIO_SB_NGD2_IE_STATUS_DEV_CLASS_CODE_SHFT                                                      0x18

#define HWIO_SB_NGD2_VE_STATUS_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00000b00)
#define HWIO_SB_NGD2_VE_STATUS_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00000b00)
#define HWIO_SB_NGD2_VE_STATUS_RMSK                                                               0xffffffff
#define HWIO_SB_NGD2_VE_STATUS_SHFT                                                                        0
#define HWIO_SB_NGD2_VE_STATUS_IN                                                                 \
        in_dword_masked(HWIO_SB_NGD2_VE_STATUS_ADDR, HWIO_SB_NGD2_VE_STATUS_RMSK)
#define HWIO_SB_NGD2_VE_STATUS_INM(m)                                                             \
        in_dword_masked(HWIO_SB_NGD2_VE_STATUS_ADDR, m)
#define HWIO_SB_NGD2_VE_STATUS_VE_VAL_BMSK                                                        0xffffffff
#define HWIO_SB_NGD2_VE_STATUS_VE_VAL_SHFT                                                                 0

#define HWIO_SB_PGD_CFG_ADDR                                                                      (SLIMBUS_REG_BASE      + 0x00001000)
#define HWIO_SB_PGD_CFG_PHYS                                                                      (SLIMBUS_REG_BASE_PHYS + 0x00001000)
#define HWIO_SB_PGD_CFG_RMSK                                                                             0x1
#define HWIO_SB_PGD_CFG_SHFT                                                                               0
#define HWIO_SB_PGD_CFG_IN                                                                        \
        in_dword_masked(HWIO_SB_PGD_CFG_ADDR, HWIO_SB_PGD_CFG_RMSK)
#define HWIO_SB_PGD_CFG_INM(m)                                                                    \
        in_dword_masked(HWIO_SB_PGD_CFG_ADDR, m)
#define HWIO_SB_PGD_CFG_OUT(v)                                                                    \
        out_dword(HWIO_SB_PGD_CFG_ADDR,v)
#define HWIO_SB_PGD_CFG_OUTM(m,v)                                                                 \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_CFG_ADDR,m,v,HWIO_SB_PGD_CFG_IN); \
        HWIO_INTFREE()
#define HWIO_SB_PGD_CFG_ENABLE_BMSK                                                                      0x1
#define HWIO_SB_PGD_CFG_ENABLE_SHFT                                                                        0

#define HWIO_SB_PGD_STATUS_ADDR                                                                   (SLIMBUS_REG_BASE      + 0x00001004)
#define HWIO_SB_PGD_STATUS_PHYS                                                                   (SLIMBUS_REG_BASE_PHYS + 0x00001004)
#define HWIO_SB_PGD_STATUS_RMSK                                                                     0x1fffff
#define HWIO_SB_PGD_STATUS_SHFT                                                                            0
#define HWIO_SB_PGD_STATUS_IN                                                                     \
        in_dword_masked(HWIO_SB_PGD_STATUS_ADDR, HWIO_SB_PGD_STATUS_RMSK)
#define HWIO_SB_PGD_STATUS_INM(m)                                                                 \
        in_dword_masked(HWIO_SB_PGD_STATUS_ADDR, m)
#define HWIO_SB_PGD_STATUS_NUM_PORTS_BMSK                                                               0xff
#define HWIO_SB_PGD_STATUS_NUM_PORTS_SHFT                                                                  0
#define HWIO_SB_PGD_STATUS_PIPE_NUM_OFFSET_BMSK                                                       0xff00
#define HWIO_SB_PGD_STATUS_PIPE_NUM_OFFSET_SHFT                                                          0x8
#define HWIO_SB_PGD_STATUS_NUM_PC_VFR_BLKS_BMSK                                                      0x70000
#define HWIO_SB_PGD_STATUS_NUM_PC_VFR_BLKS_SHFT                                                         0x10
#define HWIO_SB_PGD_STATUS_ERROR_BMSK                                                               0x180000
#define HWIO_SB_PGD_STATUS_ERROR_SHFT                                                                   0x13

#define HWIO_SB_PGD_DEV_INT_EN_ADDR                                                               (SLIMBUS_REG_BASE      + 0x00001010)
#define HWIO_SB_PGD_DEV_INT_EN_PHYS                                                               (SLIMBUS_REG_BASE_PHYS + 0x00001010)
#define HWIO_SB_PGD_DEV_INT_EN_RMSK                                                                      0x3
#define HWIO_SB_PGD_DEV_INT_EN_SHFT                                                                        0
#define HWIO_SB_PGD_DEV_INT_EN_IN                                                                 \
        in_dword_masked(HWIO_SB_PGD_DEV_INT_EN_ADDR, HWIO_SB_PGD_DEV_INT_EN_RMSK)
#define HWIO_SB_PGD_DEV_INT_EN_INM(m)                                                             \
        in_dword_masked(HWIO_SB_PGD_DEV_INT_EN_ADDR, m)
#define HWIO_SB_PGD_DEV_INT_EN_OUT(v)                                                             \
        out_dword(HWIO_SB_PGD_DEV_INT_EN_ADDR,v)
#define HWIO_SB_PGD_DEV_INT_EN_OUTM(m,v)                                                          \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_DEV_INT_EN_ADDR,m,v,HWIO_SB_PGD_DEV_INT_EN_IN); \
        HWIO_INTFREE()
#define HWIO_SB_PGD_DEV_INT_EN_DEV_ERR_BMSK                                                              0x1
#define HWIO_SB_PGD_DEV_INT_EN_DEV_ERR_SHFT                                                                0
#define HWIO_SB_PGD_DEV_INT_EN_IE_VE_CHANGE_BMSK                                                         0x2
#define HWIO_SB_PGD_DEV_INT_EN_IE_VE_CHANGE_SHFT                                                         0x1

#define HWIO_SB_PGD_DEV_INT_STATUS_ADDR                                                           (SLIMBUS_REG_BASE      + 0x00001014)
#define HWIO_SB_PGD_DEV_INT_STATUS_PHYS                                                           (SLIMBUS_REG_BASE_PHYS + 0x00001014)
#define HWIO_SB_PGD_DEV_INT_STATUS_RMSK                                                                  0x3
#define HWIO_SB_PGD_DEV_INT_STATUS_SHFT                                                                    0
#define HWIO_SB_PGD_DEV_INT_STATUS_IN                                                             \
        in_dword_masked(HWIO_SB_PGD_DEV_INT_STATUS_ADDR, HWIO_SB_PGD_DEV_INT_STATUS_RMSK)
#define HWIO_SB_PGD_DEV_INT_STATUS_INM(m)                                                         \
        in_dword_masked(HWIO_SB_PGD_DEV_INT_STATUS_ADDR, m)
#define HWIO_SB_PGD_DEV_INT_STATUS_DEV_ERR_BMSK                                                          0x1
#define HWIO_SB_PGD_DEV_INT_STATUS_DEV_ERR_SHFT                                                            0
#define HWIO_SB_PGD_DEV_INT_STATUS_IE_VE_CHANGE_BMSK                                                     0x2
#define HWIO_SB_PGD_DEV_INT_STATUS_IE_VE_CHANGE_SHFT                                                     0x1

#define HWIO_SB_PGD_DEV_INT_CLR_ADDR                                                              (SLIMBUS_REG_BASE      + 0x00001018)
#define HWIO_SB_PGD_DEV_INT_CLR_PHYS                                                              (SLIMBUS_REG_BASE_PHYS + 0x00001018)
#define HWIO_SB_PGD_DEV_INT_CLR_RMSK                                                                     0x3
#define HWIO_SB_PGD_DEV_INT_CLR_SHFT                                                                       0
#define HWIO_SB_PGD_DEV_INT_CLR_OUT(v)                                                            \
        out_dword(HWIO_SB_PGD_DEV_INT_CLR_ADDR,v)
#define HWIO_SB_PGD_DEV_INT_CLR_OUTM(m,v)                                                         \
        out_dword_masked(HWIO_SB_PGD_DEV_INT_CLR_ADDR,m,v,HWIO_SB_PGD_DEV_INT_CLR_shadow)
#define HWIO_SB_PGD_DEV_INT_CLR_DEV_ERR_BMSK                                                             0x1
#define HWIO_SB_PGD_DEV_INT_CLR_DEV_ERR_SHFT                                                               0
#define HWIO_SB_PGD_DEV_INT_CLR_IE_VE_CHANGE_BMSK                                                        0x2
#define HWIO_SB_PGD_DEV_INT_CLR_IE_VE_CHANGE_SHFT                                                        0x1

#define HWIO_SB_PGD_TRUST_OWN_EE0_ADDR                                                            (SLIMBUS_REG_BASE      + 0x00001020)
#define HWIO_SB_PGD_TRUST_OWN_EE0_PHYS                                                            (SLIMBUS_REG_BASE_PHYS + 0x00001020)
#define HWIO_SB_PGD_TRUST_OWN_EE0_RMSK                                                            0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE0_SHFT                                                                     0
#define HWIO_SB_PGD_TRUST_OWN_EE0_IN                                                              \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE0_ADDR, HWIO_SB_PGD_TRUST_OWN_EE0_RMSK)
#define HWIO_SB_PGD_TRUST_OWN_EE0_INM(m)                                                          \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE0_ADDR, m)
#define HWIO_SB_PGD_TRUST_OWN_EE0_OUT(v)                                                          \
        out_dword(HWIO_SB_PGD_TRUST_OWN_EE0_ADDR,v)
#define HWIO_SB_PGD_TRUST_OWN_EE0_OUTM(m,v)                                                       \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_TRUST_OWN_EE0_ADDR,m,v,HWIO_SB_PGD_TRUST_OWN_EE0_IN); \
        HWIO_INTFREE()
#define HWIO_SB_PGD_TRUST_OWN_EE0_PORT_OWN_BMSK                                                   0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE0_PORT_OWN_SHFT                                                            0

#define HWIO_SB_PGD_TRUST_OWN_EE1_ADDR                                                            (SLIMBUS_REG_BASE      + 0x00001024)
#define HWIO_SB_PGD_TRUST_OWN_EE1_PHYS                                                            (SLIMBUS_REG_BASE_PHYS + 0x00001024)
#define HWIO_SB_PGD_TRUST_OWN_EE1_RMSK                                                            0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE1_SHFT                                                                     0
#define HWIO_SB_PGD_TRUST_OWN_EE1_IN                                                              \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE1_ADDR, HWIO_SB_PGD_TRUST_OWN_EE1_RMSK)
#define HWIO_SB_PGD_TRUST_OWN_EE1_INM(m)                                                          \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE1_ADDR, m)
#define HWIO_SB_PGD_TRUST_OWN_EE1_OUT(v)                                                          \
        out_dword(HWIO_SB_PGD_TRUST_OWN_EE1_ADDR,v)
#define HWIO_SB_PGD_TRUST_OWN_EE1_OUTM(m,v)                                                       \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_TRUST_OWN_EE1_ADDR,m,v,HWIO_SB_PGD_TRUST_OWN_EE1_IN); \
        HWIO_INTFREE()
#define HWIO_SB_PGD_TRUST_OWN_EE1_PORT_OWN_BMSK                                                   0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE1_PORT_OWN_SHFT                                                            0

#define HWIO_SB_PGD_TRUST_OWN_EE2_ADDR                                                            (SLIMBUS_REG_BASE      + 0x00001028)
#define HWIO_SB_PGD_TRUST_OWN_EE2_PHYS                                                            (SLIMBUS_REG_BASE_PHYS + 0x00001028)
#define HWIO_SB_PGD_TRUST_OWN_EE2_RMSK                                                            0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE2_SHFT                                                                     0
#define HWIO_SB_PGD_TRUST_OWN_EE2_IN                                                              \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE2_ADDR, HWIO_SB_PGD_TRUST_OWN_EE2_RMSK)
#define HWIO_SB_PGD_TRUST_OWN_EE2_INM(m)                                                          \
        in_dword_masked(HWIO_SB_PGD_TRUST_OWN_EE2_ADDR, m)
#define HWIO_SB_PGD_TRUST_OWN_EE2_OUT(v)                                                          \
        out_dword(HWIO_SB_PGD_TRUST_OWN_EE2_ADDR,v)
#define HWIO_SB_PGD_TRUST_OWN_EE2_OUTM(m,v)                                                       \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_TRUST_OWN_EE2_ADDR,m,v,HWIO_SB_PGD_TRUST_OWN_EE2_IN); \
        HWIO_INTFREE()
#define HWIO_SB_PGD_TRUST_OWN_EE2_PORT_OWN_BMSK                                                   0xffffffff
#define HWIO_SB_PGD_TRUST_OWN_EE2_PORT_OWN_SHFT                                                            0

#define HWIO_SB_PGD_PORT_INT_EN_EEn_ADDR(n)                                                       (SLIMBUS_REG_BASE      + 0x00001030 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_EN_EEn_PHYS(n)                                                       (SLIMBUS_REG_BASE_PHYS + 0x00001030 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_EN_EEn_RMSK                                                          0xffffffff
#define HWIO_SB_PGD_PORT_INT_EN_EEn_SHFT                                                                   0
#define HWIO_SB_PGD_PORT_INT_EN_EEn_MAXn                                                                 0x2
#define HWIO_SB_PGD_PORT_INT_EN_EEn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_INT_EN_EEn_ADDR(n))
#define HWIO_SB_PGD_PORT_INT_EN_EEn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_INT_EN_EEn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_INT_EN_EEn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_INT_EN_EEn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_INT_EN_EEn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_INT_EN_EEn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_INT_EN_EEn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_INT_EN_EEn_PORT_INT_BMSK                                                 0xffffffff
#define HWIO_SB_PGD_PORT_INT_EN_EEn_PORT_INT_SHFT                                                          0

#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_ADDR(n)                                                   (SLIMBUS_REG_BASE      + 0x00001034 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_PHYS(n)                                                   (SLIMBUS_REG_BASE_PHYS + 0x00001034 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_RMSK                                                      0xffffffff
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_SHFT                                                               0
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_MAXn                                                             0x2
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_INT_STATUS_EEn_ADDR(n))
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_INT_STATUS_EEn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_INT_STATUS_EEn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_PORT_INT_BMSK                                             0xffffffff
#define HWIO_SB_PGD_PORT_INT_STATUS_EEn_PORT_INT_SHFT                                                      0

#define HWIO_SB_PGD_PORT_INT_CLR_EEn_ADDR(n)                                                      (SLIMBUS_REG_BASE      + 0x00001038 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_PHYS(n)                                                      (SLIMBUS_REG_BASE_PHYS + 0x00001038 + 16 * (n))
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_RMSK                                                         0xffffffff
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_SHFT                                                                  0
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_MAXn                                                                0x2
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_INT_CLR_EEn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_OUTMI(n,mask,val) \
        out_dword_masked(HWIO_SB_PGD_PORT_INT_CLR_EEn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_INT_CLR_EEn_shadow[n])
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_PORT_INT_BMSK                                                0xffffffff
#define HWIO_SB_PGD_PORT_INT_CLR_EEn_PORT_INT_SHFT                                                         0

#define HWIO_SB_PGD_PORT_CFGn_ADDR(n)                                                             (SLIMBUS_REG_BASE      + 0x00001080 + 32 * (n))
#define HWIO_SB_PGD_PORT_CFGn_PHYS(n)                                                             (SLIMBUS_REG_BASE_PHYS + 0x00001080 + 32 * (n))
#define HWIO_SB_PGD_PORT_CFGn_RMSK                                                                      0xff
#define HWIO_SB_PGD_PORT_CFGn_SHFT                                                                         0
#define HWIO_SB_PGD_PORT_CFGn_MAXn                                                                      0x17
#define HWIO_SB_PGD_PORT_CFGn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_CFGn_ADDR(n))
#define HWIO_SB_PGD_PORT_CFGn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_CFGn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_CFGn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_CFGn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_CFGn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_CFGn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_CFGn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_CFGn_ENABLE_BMSK                                                                0x1
#define HWIO_SB_PGD_PORT_CFGn_ENABLE_SHFT                                                                  0
#define HWIO_SB_PGD_PORT_CFGn_WATERMARK_BMSK                                                            0x3e
#define HWIO_SB_PGD_PORT_CFGn_WATERMARK_SHFT                                                             0x1
#define HWIO_SB_PGD_PORT_CFGn_PACK_BMSK                                                                 0x40
#define HWIO_SB_PGD_PORT_CFGn_PACK_SHFT                                                                  0x6
#define HWIO_SB_PGD_PORT_CFGn_ALIGN_MSB_BMSK                                                            0x80
#define HWIO_SB_PGD_PORT_CFGn_ALIGN_MSB_SHFT                                                             0x7

#define HWIO_SB_PGD_PORT_STATUSn_ADDR(n)                                                          (SLIMBUS_REG_BASE      + 0x00001084 + 32 * (n))
#define HWIO_SB_PGD_PORT_STATUSn_PHYS(n)                                                          (SLIMBUS_REG_BASE_PHYS + 0x00001084 + 32 * (n))
#define HWIO_SB_PGD_PORT_STATUSn_RMSK                                                                0xfffff
#define HWIO_SB_PGD_PORT_STATUSn_SHFT                                                                      0
#define HWIO_SB_PGD_PORT_STATUSn_MAXn                                                                   0x17
#define HWIO_SB_PGD_PORT_STATUSn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_STATUSn_ADDR(n))
#define HWIO_SB_PGD_PORT_STATUSn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_STATUSn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_STATUSn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_STATUSn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_SIZE_BMSK                                                          0x3
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_SIZE_SHFT                                                            0
#define HWIO_SB_PGD_PORT_STATUSn_OVERFLOW_BMSK                                                           0x4
#define HWIO_SB_PGD_PORT_STATUSn_OVERFLOW_SHFT                                                           0x2
#define HWIO_SB_PGD_PORT_STATUSn_UNDERFLOW_BMSK                                                          0x8
#define HWIO_SB_PGD_PORT_STATUSn_UNDERFLOW_SHFT                                                          0x3
#define HWIO_SB_PGD_PORT_STATUSn_PIPE_NUM_BMSK                                                         0xff0
#define HWIO_SB_PGD_PORT_STATUSn_PIPE_NUM_SHFT                                                           0x4
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_WORD_CNT_BMSK                                                  0x3f000
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_WORD_CNT_SHFT                                                      0xc
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_FILL_LEVEL_BMSK                                                0x40000
#define HWIO_SB_PGD_PORT_STATUSn_FIFO_FILL_LEVEL_SHFT                                                   0x12
#define HWIO_SB_PGD_PORT_STATUSn_PRT_DISCONN_BMSK                                                    0x80000
#define HWIO_SB_PGD_PORT_STATUSn_PRT_DISCONN_SHFT                                                       0x13

#define HWIO_SB_PGD_PORT_PARAMn_ADDR(n)                                                           (SLIMBUS_REG_BASE      + 0x00001088 + 32 * (n))
#define HWIO_SB_PGD_PORT_PARAMn_PHYS(n)                                                           (SLIMBUS_REG_BASE_PHYS + 0x00001088 + 32 * (n))
#define HWIO_SB_PGD_PORT_PARAMn_RMSK                                                              0x3fffffff
#define HWIO_SB_PGD_PORT_PARAMn_SHFT                                                                       0
#define HWIO_SB_PGD_PORT_PARAMn_MAXn                                                                    0x17
#define HWIO_SB_PGD_PORT_PARAMn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_PARAMn_ADDR(n))
#define HWIO_SB_PGD_PORT_PARAMn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_PARAMn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_PARAMn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_PARAMn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_PARAMn_CHANNEL_ACTIVE_BMSK                                                      0x1
#define HWIO_SB_PGD_PORT_PARAMn_CHANNEL_ACTIVE_SHFT                                                        0
#define HWIO_SB_PGD_PORT_PARAMn_CHANNEL_NUMBER_BMSK                                                    0x1fe
#define HWIO_SB_PGD_PORT_PARAMn_CHANNEL_NUMBER_SHFT                                                      0x1
#define HWIO_SB_PGD_PORT_PARAMn_SEG_DISTN_BMSK                                                      0x1ffe00
#define HWIO_SB_PGD_PORT_PARAMn_SEG_DISTN_SHFT                                                           0x9
#define HWIO_SB_PGD_PORT_PARAMn_TRANSPORT_PROTOCOL_BMSK                                            0x1e00000
#define HWIO_SB_PGD_PORT_PARAMn_TRANSPORT_PROTOCOL_SHFT                                                 0x15
#define HWIO_SB_PGD_PORT_PARAMn_SEG_LENGTH_BMSK                                                   0x3e000000
#define HWIO_SB_PGD_PORT_PARAMn_SEG_LENGTH_SHFT                                                         0x19

#define HWIO_SB_PGD_PORT_BLK_SIZEn_ADDR(n)                                                        (SLIMBUS_REG_BASE      + 0x0000108c + 32 * (n))
#define HWIO_SB_PGD_PORT_BLK_SIZEn_PHYS(n)                                                        (SLIMBUS_REG_BASE_PHYS + 0x0000108c + 32 * (n))
#define HWIO_SB_PGD_PORT_BLK_SIZEn_RMSK                                                           0xffffffff
#define HWIO_SB_PGD_PORT_BLK_SIZEn_SHFT                                                                    0
#define HWIO_SB_PGD_PORT_BLK_SIZEn_MAXn                                                                 0x17
#define HWIO_SB_PGD_PORT_BLK_SIZEn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_BLK_SIZEn_ADDR(n))
#define HWIO_SB_PGD_PORT_BLK_SIZEn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_BLK_SIZEn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_BLK_SIZEn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_BLK_SIZEn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_BLK_SIZEn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_BLK_SIZEn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_BLK_SIZEn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_BLK_SIZEn_BLK_SIZE_BMSK                                                  0xffffffff
#define HWIO_SB_PGD_PORT_BLK_SIZEn_BLK_SIZE_SHFT                                                           0

#define HWIO_SB_PGD_PORT_TRANS_SIZEn_ADDR(n)                                                      (SLIMBUS_REG_BASE      + 0x00001090 + 32 * (n))
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_PHYS(n)                                                      (SLIMBUS_REG_BASE_PHYS + 0x00001090 + 32 * (n))
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_RMSK                                                         0xffffffff
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_SHFT                                                                  0
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_MAXn                                                               0x17
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_TRANS_SIZEn_ADDR(n))
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_TRANS_SIZEn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_TRANS_SIZEn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_TRANS_SIZEn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_TRANS_SIZEn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_TRANS_SIZE_BMSK                                              0xffffffff
#define HWIO_SB_PGD_PORT_TRANS_SIZEn_TRANS_SIZE_SHFT                                                       0

#define HWIO_SB_PGD_PORT_MULTI_CHNLn_ADDR(n)                                                      (SLIMBUS_REG_BASE      + 0x00001094 + 32 * (n))
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_PHYS(n)                                                      (SLIMBUS_REG_BASE_PHYS + 0x00001094 + 32 * (n))
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_RMSK                                                         0xffffffff
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_SHFT                                                                  0
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_MAXn                                                               0x17
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_MULTI_CHNLn_ADDR(n))
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_MULTI_CHNLn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_MULTI_CHNLn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_MULTI_CHNLn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_MULTI_CHNLn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_PORTS_BMSK                                                   0xffffffff
#define HWIO_SB_PGD_PORT_MULTI_CHNLn_PORTS_SHFT                                                            0

#define HWIO_SB_PGD_PORT_PUSHPULLn_ADDR(n)                                                        (SLIMBUS_REG_BASE      + 0x00001098 + 32 * (n))
#define HWIO_SB_PGD_PORT_PUSHPULLn_PHYS(n)                                                        (SLIMBUS_REG_BASE_PHYS + 0x00001098 + 32 * (n))
#define HWIO_SB_PGD_PORT_PUSHPULLn_RMSK                                                           0xffffffff
#define HWIO_SB_PGD_PORT_PUSHPULLn_SHFT                                                                    0
#define HWIO_SB_PGD_PORT_PUSHPULLn_MAXn                                                                 0x17
#define HWIO_SB_PGD_PORT_PUSHPULLn_INI(n) \
        in_dword(HWIO_SB_PGD_PORT_PUSHPULLn_ADDR(n))
#define HWIO_SB_PGD_PORT_PUSHPULLn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PORT_PUSHPULLn_ADDR(n), mask)
#define HWIO_SB_PGD_PORT_PUSHPULLn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PORT_PUSHPULLn_ADDR(n),val)
#define HWIO_SB_PGD_PORT_PUSHPULLn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PORT_PUSHPULLn_ADDR(n),mask,val,HWIO_SB_PGD_PORT_PUSHPULLn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PORT_PUSHPULLn_RPT_PERIOD_BMSK                                                    0xffff
#define HWIO_SB_PGD_PORT_PUSHPULLn_RPT_PERIOD_SHFT                                                         0
#define HWIO_SB_PGD_PORT_PUSHPULLn_NUM_SAMPLES_BMSK                                               0xffff0000
#define HWIO_SB_PGD_PORT_PUSHPULLn_NUM_SAMPLES_SHFT                                                     0x10

#define HWIO_SB_PGD_PC_CFGn_ADDR(n)                                                               (SLIMBUS_REG_BASE      + 0x00001600 + 32 * (n))
#define HWIO_SB_PGD_PC_CFGn_PHYS(n)                                                               (SLIMBUS_REG_BASE_PHYS + 0x00001600 + 32 * (n))
#define HWIO_SB_PGD_PC_CFGn_RMSK                                                                  0x9fffffff
#define HWIO_SB_PGD_PC_CFGn_SHFT                                                                           0
#define HWIO_SB_PGD_PC_CFGn_MAXn                                                                         0x5
#define HWIO_SB_PGD_PC_CFGn_INI(n) \
        in_dword(HWIO_SB_PGD_PC_CFGn_ADDR(n))
#define HWIO_SB_PGD_PC_CFGn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PC_CFGn_ADDR(n), mask)
#define HWIO_SB_PGD_PC_CFGn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PC_CFGn_ADDR(n),val)
#define HWIO_SB_PGD_PC_CFGn_OUTMI(n,mask,val) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SB_PGD_PC_CFGn_ADDR(n),mask,val,HWIO_SB_PGD_PC_CFGn_INI(n));\
        HWIO_INTFREE()
#define HWIO_SB_PGD_PC_CFGn_INIT_VAL_BMSK                                                           0xffffff
#define HWIO_SB_PGD_PC_CFGn_INIT_VAL_SHFT                                                                  0
#define HWIO_SB_PGD_PC_CFGn_PORT_SEL_BMSK                                                         0x1f000000
#define HWIO_SB_PGD_PC_CFGn_PORT_SEL_SHFT                                                               0x18
#define HWIO_SB_PGD_PC_CFGn_INIT_BMSK                                                             0x80000000
#define HWIO_SB_PGD_PC_CFGn_INIT_SHFT                                                                   0x1f

#define HWIO_SB_PGD_PC_VALn_ADDR(n)                                                               (SLIMBUS_REG_BASE      + 0x00001604 + 32 * (n))
#define HWIO_SB_PGD_PC_VALn_PHYS(n)                                                               (SLIMBUS_REG_BASE_PHYS + 0x00001604 + 32 * (n))
#define HWIO_SB_PGD_PC_VALn_RMSK                                                                  0xffffffff
#define HWIO_SB_PGD_PC_VALn_SHFT                                                                           0
#define HWIO_SB_PGD_PC_VALn_MAXn                                                                         0x5
#define HWIO_SB_PGD_PC_VALn_INI(n) \
        in_dword(HWIO_SB_PGD_PC_VALn_ADDR(n))
#define HWIO_SB_PGD_PC_VALn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PC_VALn_ADDR(n), mask)
#define HWIO_SB_PGD_PC_VALn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PC_VALn_ADDR(n),val)
#define HWIO_SB_PGD_PC_VALn_PC_DMA_BMSK                                                             0xffffff
#define HWIO_SB_PGD_PC_VALn_PC_DMA_SHFT                                                                    0
#define HWIO_SB_PGD_PC_VALn_PC_FIFO_SAMPLES_BMSK                                                  0xff000000
#define HWIO_SB_PGD_PC_VALn_PC_FIFO_SAMPLES_SHFT                                                        0x18

#define HWIO_SB_PGD_PC_VFR_TSn_ADDR(n)                                                            (SLIMBUS_REG_BASE      + 0x00001608 + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TSn_PHYS(n)                                                            (SLIMBUS_REG_BASE_PHYS + 0x00001608 + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TSn_RMSK                                                               0xffffffff
#define HWIO_SB_PGD_PC_VFR_TSn_SHFT                                                                        0
#define HWIO_SB_PGD_PC_VFR_TSn_MAXn                                                                      0x5
#define HWIO_SB_PGD_PC_VFR_TSn_INI(n) \
        in_dword(HWIO_SB_PGD_PC_VFR_TSn_ADDR(n))
#define HWIO_SB_PGD_PC_VFR_TSn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PC_VFR_TSn_ADDR(n), mask)
#define HWIO_SB_PGD_PC_VFR_TSn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PC_VFR_TSn_ADDR(n),val)
#define HWIO_SB_PGD_PC_VFR_TSn_VAL_BMSK                                                           0xffffffff
#define HWIO_SB_PGD_PC_VFR_TSn_VAL_SHFT                                                                    0

#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_ADDR(n)                                                     (SLIMBUS_REG_BASE      + 0x0000160c + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_PHYS(n)                                                     (SLIMBUS_REG_BASE_PHYS + 0x0000160c + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_RMSK                                                               0x1
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_SHFT                                                                 0
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_MAXn                                                               0x5
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_INI(n) \
        in_dword(HWIO_SB_PGD_PC_VFR_TS_STATUSn_ADDR(n))
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_INMI(n,mask) \
        in_dword_masked(HWIO_SB_PGD_PC_VFR_TS_STATUSn_ADDR(n), mask)
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PC_VFR_TS_STATUSn_ADDR(n),val)
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_VFR_INT_BMSK                                                       0x1
#define HWIO_SB_PGD_PC_VFR_TS_STATUSn_VFR_INT_SHFT                                                         0

#define HWIO_SB_PGD_PC_VFR_TS_CLRn_ADDR(n)                                                        (SLIMBUS_REG_BASE      + 0x00001610 + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_PHYS(n)                                                        (SLIMBUS_REG_BASE_PHYS + 0x00001610 + 32 * (n))
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_RMSK                                                                  0x1
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_SHFT                                                                    0
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_MAXn                                                                  0x5
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_OUTI(n,val) \
        out_dword(HWIO_SB_PGD_PC_VFR_TS_CLRn_ADDR(n),val)
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_OUTMI(n,mask,val) \
        out_dword_masked(HWIO_SB_PGD_PC_VFR_TS_CLRn_ADDR(n),mask,val,HWIO_SB_PGD_PC_VFR_TS_CLRn_shadow[n])
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_VFR_INT_BMSK                                                          0x1
#define HWIO_SB_PGD_PC_VFR_TS_CLRn_VFR_INT_SHFT                                                            0

#define HWIO_SB_PGD_IE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x00001700)
#define HWIO_SB_PGD_IE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x00001700)
#define HWIO_SB_PGD_IE_STATUS_RMSK                                                                0xffffffff
#define HWIO_SB_PGD_IE_STATUS_SHFT                                                                         0
#define HWIO_SB_PGD_IE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_PGD_IE_STATUS_ADDR, HWIO_SB_PGD_IE_STATUS_RMSK)
#define HWIO_SB_PGD_IE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_PGD_IE_STATUS_ADDR, m)
#define HWIO_SB_PGD_IE_STATUS_UNSPRTD_MSG_BMSK                                                           0x1
#define HWIO_SB_PGD_IE_STATUS_UNSPRTD_MSG_SHFT                                                             0
#define HWIO_SB_PGD_IE_STATUS_DATA_TX_COL_BMSK                                                           0x2
#define HWIO_SB_PGD_IE_STATUS_DATA_TX_COL_SHFT                                                           0x1
#define HWIO_SB_PGD_IE_STATUS_RECONFIG_OBJ_BMSK                                                          0x4
#define HWIO_SB_PGD_IE_STATUS_RECONFIG_OBJ_SHFT                                                          0x2
#define HWIO_SB_PGD_IE_STATUS_EX_ERROR_BMSK                                                              0x8
#define HWIO_SB_PGD_IE_STATUS_EX_ERROR_SHFT                                                              0x3
#define HWIO_SB_PGD_IE_STATUS_DEV_CLASS_VER_BMSK                                                    0xff0000
#define HWIO_SB_PGD_IE_STATUS_DEV_CLASS_VER_SHFT                                                        0x10
#define HWIO_SB_PGD_IE_STATUS_DEV_CLASS_CODE_BMSK                                                 0xff000000
#define HWIO_SB_PGD_IE_STATUS_DEV_CLASS_CODE_SHFT                                                       0x18

#define HWIO_SB_PGD_VE_STATUS_ADDR                                                                (SLIMBUS_REG_BASE      + 0x00001710)
#define HWIO_SB_PGD_VE_STATUS_PHYS                                                                (SLIMBUS_REG_BASE_PHYS + 0x00001710)
#define HWIO_SB_PGD_VE_STATUS_RMSK                                                                0xffffffff
#define HWIO_SB_PGD_VE_STATUS_SHFT                                                                         0
#define HWIO_SB_PGD_VE_STATUS_IN                                                                  \
        in_dword_masked(HWIO_SB_PGD_VE_STATUS_ADDR, HWIO_SB_PGD_VE_STATUS_RMSK)
#define HWIO_SB_PGD_VE_STATUS_INM(m)                                                              \
        in_dword_masked(HWIO_SB_PGD_VE_STATUS_ADDR, m)
#define HWIO_SB_PGD_VE_STATUS_VE_VAL_BMSK                                                         0xffffffff
#define HWIO_SB_PGD_VE_STATUS_VE_VAL_SHFT                                                                  0


#endif /* __HAL_HALHWIOSLIMBUS_H__ */

