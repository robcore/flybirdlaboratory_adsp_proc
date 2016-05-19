#ifndef __DOG_HAL_8994_H__
#define __DOG_HAL_8994_H__
/*
===========================================================================
*/
/**
  @file dog_hal_8994_lpass.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6SS_CSR

  'Include' filters applied: WDOG[LPASS_QDSP6SS_CSR]
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

  $Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hal_8994_lpass.h#1 $
  $DateTime: 2014/10/20 19:14:32 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/**
Instructions to Generate Content:

1. Browser to http://go/ipcat
2. Select to Generate HWIO
3. File Name : dog_hal_hwio.h
4. Filter for Appropriate Register Blocks such as LPASS_QDSP_CSR, MSS_QDSP6SS_CSR, QDSP6SS_CSR, ... Select Generate Offsets and Include Field Values
5. Select Generate
6. Copy Results to Clipboard
7. Paste to this File Between "Book Ends"
8. Save
*/

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_CSR_REG_BASE                                          (LPASS_BASE      + 0x00280000)
#define LPASS_QDSP6SS_CSR_REG_BASE_OFFS                                     0x00280000

#define HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OFFS                                  (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OFFS                                    (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002004)
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
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002008)
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
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000200c)
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
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002010)
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
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002014)
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
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR                                   (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OFFS                                   (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000201c)
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

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_CSR_REG_BASE                                          (LPASS_BASE      + 0x00280000)
#define LPASS_QDSP6SS_CSR_REG_BASE_OFFS                                     0x00280000

#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK                                        0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_BMSK                                     0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00001000)
#define HWIO_LPASS_QDSP6SS_IDLT_MATCH_VAL_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00001000)
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
#define HWIO_LPASS_QDSP6SS_IDLT_COUNT_VAL_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00001004)
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
#define HWIO_LPASS_QDSP6SS_IDLT_ENABLE_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00001008)
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
#define HWIO_LPASS_QDSP6SS_IDLT_SYNC_STATUS_OFFS                            (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000100c)
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
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OFFS                                  (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OFFS                                    (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002004)
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
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002008)
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
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000200c)
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
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002010)
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
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002014)
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
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR                                   (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OFFS                                   (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000201c)
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
#define HWIO_LPASS_QDSP6SS_IPC_OFFS                                         (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_QDSP6SS_IPC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IPC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IPC_INTR_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_INTR_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_ADDR                            (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00005010)
#define HWIO_LPASS_QDSP6SS_L1_IRQ_BACKUP_EN_OFFS                            (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00005010)
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

#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007008)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_OFFS                                  (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007008)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_RMSK                                         0x7
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR, HWIO_LPASS_QDSP6SS_BLOCK_INTR_RMSK)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR,m,v,HWIO_LPASS_QDSP6SS_BLOCK_INTR_IN)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_BMSK                             0x4
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_SHFT                             0x2
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_INTR_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_INTR_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PD_HS_START_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000700c)
#define HWIO_LPASS_QDSP6SS_PD_HS_START_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000700c)
#define HWIO_LPASS_QDSP6SS_PD_HS_START_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_START_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PD_HS_START_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PD_HS_START_CMD_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_START_CMD_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007010)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_OFFS                                  (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007010)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR, HWIO_LPASS_QDSP6SS_PD_HS_DONE_RMSK)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PD_HS_DONE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_DONE_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PD_HS_DONE_DONE_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PU_HS_START_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007014)
#define HWIO_LPASS_QDSP6SS_PU_HS_START_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007014)
#define HWIO_LPASS_QDSP6SS_PU_HS_START_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_PU_HS_START_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PU_HS_START_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PU_HS_START_CMD_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_PU_HS_START_CMD_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000701c)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OFFS                                    (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000701c)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK                                          0xff
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLPC_CFG_IN)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_BMSK                             0x80
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_SHFT                              0x7
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SLP_DELAY_CTL_BMSK                            0x40
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SLP_DELAY_CTL_SHFT                             0x6
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_BMSK                          0x20
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_SHFT                           0x5
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_HS_MODE_BMSK                               0x10
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_HS_MODE_SHFT                                0x4
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_SRC_SEL_BMSK                                0x6
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_PD_SRC_SEL_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_WAKEUP_ENA_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXT_WAKEUP_ENA_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007020)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007020)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_RMSK                                        0x3
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR, HWIO_LPASS_QDSP6SS_SLPC_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_FSM_STATE_BMSK                              0x3
#define HWIO_LPASS_QDSP6SS_SLPC_STATUS_FSM_STATE_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007024)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007024)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK                                   0x1ff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ARCH_BMSK                              0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ARCH_SHFT                                0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RET_BMSK                                0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RET_SHFT                                 0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM2_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM2_SHFT                               0x6
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
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_OFFS                             (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007028)
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
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000702c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK                                     0x7d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM2_BMSK                               0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM2_SHFT                                0x6
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
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007030)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RMSK                                 0x6fe0ff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CLAMP_QMC_MEM_BMSK                   0x400000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CLAMP_QMC_MEM_SHFT                       0x16
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CLAMP_WL_BMSK                        0x200000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CLAMP_WL_SHFT                            0x15
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_MEM_PERIPH_BMSK                       0x80000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_MEM_PERIPH_SHFT                          0x13
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_STBY_BMSK                      0x40000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_STBY_SHFT                         0x12
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ETB_BMSK                              0x20000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_ETB_SHFT                                 0x11
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2TAG_BMSK                            0x10000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2TAG_SHFT                               0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1IU_BMSK                              0x8000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1IU_SHFT                                 0xf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1DU_BMSK                              0x4000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1DU_SHFT                                 0xe
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2PLRU_BMSK                            0x2000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2PLRU_SHFT                               0xd
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_BMSK                              0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L2DATA_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007034)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007034)
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
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007038)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_RMSK                                    0x125
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
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_BMSK                            0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_SHFT                             0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEON_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEON_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_BMSK                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000703c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000703c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK                                    0x1ff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_BMSK                             0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_SHFT                               0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_BMSK                                 0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_SHFT                                  0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_BMSK                           0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_SHFT                            0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_MEM_BMSK                           0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_MEM_SHFT                            0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_IO_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLAMP_IO_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_BMSK                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_SHFT                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007040)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007040)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_RMSK                                     0x1f
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_FREEZE_BMSK                          0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_FREEZE_SHFT                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_BMSK                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_SHFT                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_BYPASS_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_BYPASS_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR                          (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007044)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_OFFS                          (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007044)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RMSK                                 0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_BMSK                        0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_SHFT                        0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_BMSK                         0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_SHFT                         0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SAVE_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SAVE_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007050)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007050)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK                                      0xf
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_BMSK                   0x8
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_SHFT                   0x3
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_BMSK                        0x4
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_SHFT                        0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_BMSK                        0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00007080)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00007080)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_RMSK                                 0xc0000003
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ADDR, HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_RMSK)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ADDR, m)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ADDR,v)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ADDR,m,v,HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_IN)
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_STATUS_BMSK                          0x80000000
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_STATUS_SHFT                                0x1f
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ACK_BMSK                             0x40000000
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_ACK_SHFT                                   0x1e
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_PWR_LVL_BMSK                                0x3
#define HWIO_LPASS_QDSP6SS_MVC_PWR_REQ_PWR_LVL_SHFT                                0x0


#endif /* __DOG_HAL_8994_H__ */
