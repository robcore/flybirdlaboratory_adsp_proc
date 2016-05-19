#===========================================================================
#
#  @file hwio_msm8962.py
#  @brief HWIO config file for the HWIO generation scripts for MSM8962
#         LPASS.
#
#  This file can be invoked by calling:
#
#    HWIOGen.py --cfg=hwio_msmx62.py --flat=..\..\..\api\systemdrivers\hwio\msm8x62\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2013 Qualcomm Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hwio/build/hwio_msm8962.py#1 $
#  $DateTime: 2014/10/16 12:45:40 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

CHIPSET = 'msm8962'

# ============================================================================
# HWIO_BASE_FILES
# ============================================================================

bases = [
  # General bases
  'RPM',
  'RPM_SS_MSG_RAM_START_ADDRESS',
  'RPM_SS_MSG_RAM_END_ADDRESS',
  'SPDM_WRAPPER_TOP',
  'MPM2_MPM',
  'PERIPH_SS',
  'PMIC_ARB',
  'QDSS_.*',
  'CLK_CTL',
  'CONFIG_NOC',
  'CORE_TOP_CSR',
  'SECURITY_CONTROL',
  'SYSTEM_NOC',
  'TLMM',

  # LPASS bases
  'LPASS',
]

base_resize = {
  'CONFIG_NOC':                      0x1000,
  'SYSTEM_NOC':                      0x5000,  # Change to be compatible with 8084
  'MPM2_MPM':                        0xC000,
  'RPM':                            0x90000,
  'RPM_SS_MSG_RAM_START_ADDRESS':    0x4000,
  'RPM_SS_MSG_RAM_END_ADDRESS':         0x0,
  'CLK_CTL':                        0x20000,
  'PMIC_ARB':                       0x10000,
  'PERIPH_SS':                     0x500000,  # Change to be compatible with 8084
  'QDSS_QDSS':                      0x80000,
  'CORE_TOP_CSR':                   0x30000,
  'LPASS':                         0x300000,
  'SECURITY_CONTROL':                0x8000,
  'SPDM_WRAPPER_TOP':                0x6000,
  'TLMM':                           0x20000,
}


HWIO_BASE_FILES = [
  {
    'filename': '../../../api/systemdrivers/hwio/' + CHIPSET + '/msmhwiobase.h',
    'bases': bases,
    'map-type': 'qurt',
    'virtual-address-start': 0xE0000000,
    'virtual-address-end': 0xF0000000,
    'resize': base_resize,
    'qurt-memsection-filename': '../../../api/systemdrivers/hwio/' + CHIPSET + '/msmhwioplat.xml',
    'default-cache-policy': 'uncached',
    'devcfg-filename': '../config/' + CHIPSET + '/HWIOBaseMap.c',
    'check-sizes': True,
    'check-for-overlaps': True,
    
    # We need to manually map the LPASS region because the LPM region
    # which is right in the middle of LPASS needs special cache
    # attributes.  This is handled in the top-level qdsp6.xml file.
    'fixed-virtual-address': { 'LPASS': 0xEE000000 },
    'skip-memsection': ['LPASS'],
  }
]


# ============================================================================
# HWIO_T32VIEW_FILES
# ============================================================================

HWIO_T32VIEW_FILES = [
  {
    'symbol-filename': '../scripts/' + CHIPSET + '/hwio.cmm',
    'limit-array-size': [ 10, 4 ],
    'per-filename': '../scripts/' + CHIPSET + '/hwioreg',
    'filter-exclude': ['RESERVED', 'DUMMY']
  },
]


# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': '../hw/' + CHIPSET + '/msmhwioreg.h',
    'bases': bases,
    'filter-exclude': ['RESERVED', 'DUMMY'],
    'header': '''
#error This file is for reference only and cannot be included.  See "go/hwio" or mail corebsp.sysdrv.hwio for help.
'''
  }
]


# ============================================================================
# Main
#
# Entry point when invoking this directly.
# ============================================================================

if __name__ == "__main__":
  from subprocess import Popen
  Popen(["\\\\ben\\corebsp_labdata_0001\\sysdrv\\hwio\\HWIOGen.py", "--cfg=hwio_" + CHIPSET + ".py", "--flat=../../../api/systemdrivers/hwio/" + CHIPSET + "/ARM_ADDRESS_FILE.FLAT"], shell=True)


