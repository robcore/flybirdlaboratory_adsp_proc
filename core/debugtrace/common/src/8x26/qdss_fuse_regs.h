#ifndef __QDSS_FUSE_REGS_H__
#define __QDSS_FUSE_REGS_H__

/*
===========================================================================
*/
/**
  @file qdss_fuse_regs.h
  @brief QDSS efuse HWIO interface file

  This file contains HWIO register definitions for the following modules:
    SECURITY_CONTROL_CORE

  'Include' filters applied: OEM_CONFIG[SECURITY_CONTROL_CORE] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================
  Copyright (c) 2013 QUALCOMM Technologies Inc.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.
  ===========================================================================
  $Header: //components/rel/core.adsp/2.6.1/debugtrace/common/src/8x26/qdss_fuse_regs.h#1 $
  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: SECURITY_CONTROL_CORE
 *--------------------------------------------------------------------------*/

/**
* The register addresses defined here are in the physical space.
* For virtual address accesses to these registers
* SECURITY_CONTROL_BASE is defined to SECURITY_CONTROL_BASE_PTR
* in qdsscommon.scons through: 
* env.Append(CCFLAGS = " 
* -DSECURITY_CONTROL_BASE=SECURITY_CONTROL_BASE_PTR") 
**/


#define SECURITY_CONTROL_BASE_SIZE                                  0x00008000
#define SECURITY_CONTROL_BASE_PHYS                                  0xfc4b8000

#ifndef SECURITY_CONTROL_BASE 
   #define SECURITY_CONTROL_BASE                                       SECURITY_CONTROL_BASE_PHYS
#endif

#define SECURITY_CONTROL_CORE_REG_BASE                                                                             (SECURITY_CONTROL_BASE      + 0x00000000)
#define SECURITY_CONTROL_CORE_REG_BASE_PHYS                                                                        (SECURITY_CONTROL_BASE_PHYS + 0x00000000)
#define SECURITY_CONTROL_CORE_REG_BASE_OFFS                                                                        0x00000000

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000e8)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PHYS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000000e8)
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_BMSK                                                              0x1e0000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPARE1_SHFT                                                                  0x11
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PHYS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000000ec)
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE2_BMSK                                                            0x78000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE2_SHFT                                                                  0x1b
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE0_BMSK                                                               0xffe00
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_SPARE0_SHFT                                                                   0x9
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_BMSK                                                     0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_SHFT                                                     0x3
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_BMSK                                                      0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_SHFT                                                      0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_BMSK                                                       0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_SHFT                                                       0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_BMSK                                                       0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000000f0)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_PHYS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000000f0)
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
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_PHYS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000000f4)
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

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040e8)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PHYS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000040e8)
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
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_BMSK                                                             0x1e0000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPARE1_SHFT                                                                 0x11
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
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PHYS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000040ec)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000040ec)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WDOG_EN_BMSK                                                          0x80000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WDOG_EN_SHFT                                                                0x1f
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE2_BMSK                                                           0x78000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE2_SHFT                                                                 0x1b
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
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE0_BMSK                                                              0xffe00
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_SPARE0_SHFT                                                                  0x9
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
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_BMSK                                                    0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_SHFT                                                    0x3
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_BMSK                                                     0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_SHFT                                                     0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_BMSK                                                      0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_SHFT                                                      0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_BMSK                                                      0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000040f0)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_PHYS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000040f0)
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
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_PHYS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x000040f4)
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

#define HWIO_OEM_CONFIG0_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006024)
#define HWIO_OEM_CONFIG0_PHYS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x00006024)
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
#define HWIO_OEM_CONFIG0_SPARE1_BMSK                                                                                 0x1e0000
#define HWIO_OEM_CONFIG0_SPARE1_SHFT                                                                                     0x11
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
#define HWIO_OEM_CONFIG1_PHYS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x00006028)
#define HWIO_OEM_CONFIG1_OFFS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006028)
#define HWIO_OEM_CONFIG1_RMSK                                                                                      0xffffffff
#define HWIO_OEM_CONFIG1_IN          \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, HWIO_OEM_CONFIG1_RMSK)
#define HWIO_OEM_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, m)
#define HWIO_OEM_CONFIG1_WDOG_EN_BMSK                                                                              0x80000000
#define HWIO_OEM_CONFIG1_WDOG_EN_SHFT                                                                                    0x1f
#define HWIO_OEM_CONFIG1_SPARE2_BMSK                                                                               0x78000000
#define HWIO_OEM_CONFIG1_SPARE2_SHFT                                                                                     0x1b
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
#define HWIO_OEM_CONFIG1_SPARE0_BMSK                                                                                  0xffe00
#define HWIO_OEM_CONFIG1_SPARE0_SHFT                                                                                      0x9
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
#define HWIO_OEM_CONFIG1_APPS_SPNIDEN_DISABLE_BMSK                                                                        0x8
#define HWIO_OEM_CONFIG1_APPS_SPNIDEN_DISABLE_SHFT                                                                        0x3
#define HWIO_OEM_CONFIG1_APPS_SPIDEN_DISABLE_BMSK                                                                         0x4
#define HWIO_OEM_CONFIG1_APPS_SPIDEN_DISABLE_SHFT                                                                         0x2
#define HWIO_OEM_CONFIG1_APPS_NIDEN_DISABLE_BMSK                                                                          0x2
#define HWIO_OEM_CONFIG1_APPS_NIDEN_DISABLE_SHFT                                                                          0x1
#define HWIO_OEM_CONFIG1_APPS_DBGEN_DISABLE_BMSK                                                                          0x1
#define HWIO_OEM_CONFIG1_APPS_DBGEN_DISABLE_SHFT                                                                          0x0

#define HWIO_OEM_CONFIG2_ADDR                                                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000602c)
#define HWIO_OEM_CONFIG2_PHYS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x0000602c)
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
#define HWIO_OEM_CONFIG3_PHYS                                                                                      (SECURITY_CONTROL_CORE_REG_BASE_PHYS + 0x00006030)
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


#endif /* __QDSS_FUSE_REGS_H__ */
