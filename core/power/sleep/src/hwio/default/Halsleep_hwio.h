#ifndef __HALSLEEP_HWIO_H__
#define __HALSLEEP_HWIO_H__
/*
===========================================================================
*/
/**
  @file Halsleep_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6SS_CSR

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2012-2013 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/power/sleep/src/hwio/default/Halsleep_hwio.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_CSR_REG_BASE                                          (LPASS_BASE      + 0x00280000)

#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK                                        0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_BMSK                                     0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00001000)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_RMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR, HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_IN)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_VALUE_BMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_VALUE_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00001004)
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_RMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_ADDR, HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_IN)
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_VALUE_BMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_VALUE_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00001008)
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_ENABLE_ADDR, HWIO_LPASS_QDSP6SS_IDLT_ENABLE_RMSK)
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_ENABLE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IDLT_ENABLE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_IDLT_ENABLE_ADDR,m,v,HWIO_LPASS_QDSP6SS_IDLT_ENABLE_IN)
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_EN_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_EN_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_ADDR                            (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_RMSK                                   0x6
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_ADDR, HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_COUNT_SYNC_STATUS_BMSK                 0x4
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_COUNT_SYNC_STATUS_SHFT                 0x2
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_MATCH_SYNC_STATUS_BMSK                 0x2
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_MATCH_SYNC_STATUS_SHFT                 0x1

#define HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK                                           0x7
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK                                 0xf81fffff
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_BMSK               0x80000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_SHFT                     0x1f
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_BMSK           0x40000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_SHFT                 0x1e
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_BMSK           0x20000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_SHFT                 0x1d
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_BMSK            0x10000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_SHFT                  0x1c
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_BMSK            0x8000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_SHFT                 0x1b
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_BMSK                        0x1ffffe
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_SHFT                             0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                    0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                    0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK                                 0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK                            0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK                                 0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK                            0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK                                  0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_BMSK                             0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR                                   (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK                                     0x1fffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_TEST_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_BMSK                         0x100000
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_SHFT                             0x14
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_BMSK                           0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_IPC_ADDR                                         (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00005000)
#define HWIO_LPASS_QDSP6SS_IPC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IPC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IPC_INTR_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_INTR_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR                            (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00005010)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_RMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR, HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_RMSK)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR,v)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR,m,v,HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_IN)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_EN_L1_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_EN_L1_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_PD_HS_START_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000700c)
#define HWIO_LPASS_QDSP6SS_PD_HS_START_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_START_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PD_HS_START_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PD_HS_START_CMD_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_START_CMD_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007010)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR, HWIO_LPASS_QDSP6SS_PD_HS_DONE_RMSK)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_DONE_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_DONE_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PU_HS_START_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007014)
#define HWIO_LPASS_QDSP6SS_PU_HS_START_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_PU_HS_START_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PU_HS_START_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PU_HS_START_CMD_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PU_HS_START_CMD_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000701c)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK                                          0x3f
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLPC_CFG_IN)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_AVS_MACRO_EN_BMSK                             0x20
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_AVS_MACRO_EN_SHFT                              0x5
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_AVS_SRC_EN_BMSK                           0x10
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_AVS_SRC_EN_SHFT                            0x4
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_SRC_SEL_BMSK                                0x6
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_SRC_SEL_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_WAKEUP_ENA_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_WAKEUP_ENA_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007020)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_RMSK                                        0x3
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR, HWIO_LPASS_QDSP6SS_SLPC_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_FSM_STATE_BMSK                              0x3
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_FSM_STATE_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007024)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK                                    0x3f
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIS_BMSK                               0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIS_SHFT                                0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ATBM_BMSK                               0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ATBM_SHFT                                0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AHBM_BMSK                                0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AHBM_SHFT                                0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CORE_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CORE_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR                             (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007028)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_RMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000702c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK                                     0x3d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIS_BMSK                                0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIS_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ATBM_BMSK                                0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ATBM_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AHBM_BMSK                                 0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AHBM_SHFT                                 0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CORE_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CORE_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007030)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RMSK                                  0xf0007
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_MEM_PERIPH_BMSK                       0x80000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_MEM_PERIPH_SHFT                          0x13
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_STBY_BMSK                      0x40000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_STBY_SHFT                         0x12
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ETB_BMSK                              0x20000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ETB_SHFT                                 0x11
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2TAG_BMSK                            0x10000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2TAG_SHFT                               0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_BMSK                               0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007034)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_RMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_BHS_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_BHS_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007038)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_RMSK                                    0x1ff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_VREF_SEL_BMSK                           0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_VREF_SEL_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_BMSK                            0xe0
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_SHFT                             0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEON_BMSK                             0x1c
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEON_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_BMSK                          0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000703c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK                                     0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_BMSK                                 0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_SHFT                                  0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_BMSK                           0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_SHFT                            0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_MEM_BMSK                           0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_MEM_SHFT                            0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_IO_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_IO_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_BMSK                               0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_SHFT                               0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_BMSK                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_SHFT                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_SHFT                            0x0


#endif /* __HALSLEEP_HWIO_H__ */
