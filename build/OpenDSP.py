
#=================================================================================
#   File Name: OpenDSP.py
#
#   ADSP build system: build process OpenDSP functions
#
#   Copyright (c) 2014 QUALCOMM Technologies Incorporated.
#   All rights reserved. Qualcomm Proprietary and Confidential.
#
#---------------------------------------------------------------------------------
#
#  $Header: //components/rel/dspbuild.adsp/2.5/OpenDSP.py#3 $
#  $DateTime: 2014/09/29 04:54:59 $
#  $Change: 6676211 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
#   when     who            what, where, why
# --------   ---        ----------------------------------------------------------
# 05/09/14   corinc      Moved code from build\build.py to OpenDSP.py, part of re-architect effort
# 05/09/14   corinc      Initial check-in and promotion to PW
#=================================================================================

import os
import re
import subprocess
import sys
import time
import fnmatch
import shutil, errno
import buildSysInfo

#=================================================================================
#=================================================================================
#                  Function definitions are below
#=================================================================================
#=================================================================================

# Bit-exactness Verification
def bixExactnessVerify(bldSysInfo):

   if bldSysInfo.check_dsp_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      compare_file_old = 'mpd_phdr.pbn' 
      compare_file_old2= 'M9x25AAAAAAAAAQ1234_phdr.pbn'
      compare_file_new = 'mpd_pre_dummy_seg_phdr.pbn'
      compare_file_new2 = 'adsp_phdr.pbn'
      where_compare_path = ''.join([cwd_dir + "/build/bsp/multi_pd_img/build/"])
      where_compare_path2 = ''.join([cwd_dir + "/build/bsp/devcfg_img/build/"])
      if os.environ['CHIPSET'] == "mdm9x25" and os.environ['BUILD_FLAVOR'] == 'spd':
         if os.path.exists(''.join([where_compare_path2 + compare_file_old2])):
            checkdsp_cmd = ''.join(["perl " + cwd_dir + "/../../adsp_proc/hap/scripts/HAP-DSP_verify.pl " + "../../adsp_proc/build/bsp/devcfg_img/build/" + compare_file_old2 + " ./build/bsp/devcfg_img/build/" + compare_file_old2, " > ./opendsp_bitmatch.log 2>&1"])
      if os.path.exists(''.join([where_compare_path + compare_file_old])):
         checkdsp_cmd = ''.join(["perl " + cwd_dir + "/../../adsp_proc/hap/scripts/HAP-DSP_verify.pl " + "../../adsp_proc/build/bsp/multi_pd_img/build/" + compare_file_old + " ./build/bsp/multi_pd_img/build/" + compare_file_old, " > ./opendsp_bitmatch.log 2>&1"])
      elif os.path.exists(''.join([where_compare_path + compare_file_new])):
         checkdsp_cmd = ''.join(["perl " + cwd_dir + "/../../adsp_proc/hap/scripts/HAP-DSP_verify.pl " + "../../adsp_proc/build/bsp/multi_pd_img/build/" + compare_file_new + " ./build/bsp/multi_pd_img/build/" + compare_file_new, " > ./opendsp_bitmatch.log 2>&1"])
      elif os.path.exists(''.join([where_compare_path + compare_file_new2])):
         checkdsp_cmd = ''.join(["perl " + cwd_dir + "/../../adsp_proc/hap/scripts/HAP-DSP_verify.pl " + "../../adsp_proc/build/bsp/multi_pd_img/build/" + compare_file_new2 + " ./build/bsp/multi_pd_img/build/" + compare_file_new2, " > ./opendsp_bitmatch.log 2>&1"])
      else:
         checkdsp_cmd = ''.join(["perl " + cwd_dir + "/../../adsp_proc/hap/scripts/HAP-DSP_verify.pl " + "../../adsp_proc/dsp.elf" + " ./dsp.elf", " > ./opendsp_bitmatch.log 2>&1"])  
      print checkdsp_cmd
      proc = subprocess.Popen(checkdsp_cmd, shell=True)
      (out, err) = proc.communicate()
      where_success_file = ''.join([cwd_dir + "/success"])
      where_bitmatchfail_file = ''.join([cwd_dir + "/bitmatch_fail.txt"])      
      if os.path.exists(where_success_file):
         if os.path.exists(where_bitmatchfail_file):
            os.remove(where_success_file)
            print "       Bit-match Failed, 'success' file is removed to reflect the CRM pack status!!! \n"
      print "\n\n"

      
      
#=================================================================================
# HAP packages creation
def HAPPackagesCreate(bldSysInfo):

   if bldSysInfo.pkg_all_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p all"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()

   if bldSysInfo.pkg_hk11_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/opendsp_hk11.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_hk11"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()

   if bldSysInfo.pkg_hk22_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/opendsp_hk22.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_hk22"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()
       
   if bldSysInfo.pkg_oem_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/opendsp.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_oem"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()

   if bldSysInfo.pkg_hd11_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/opendsp_hd11.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_hd11"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()
      
   if bldSysInfo.pkg_isv_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/opendsp_isv.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_isv"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()      
      
   if bldSysInfo.pkg_hcbsp_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/hcbsp.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_hcbsp"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()
      
   if bldSysInfo.pkg_hd22_flag:
      cwd_dir = os.getcwd()
      print "\n\nCurrent working directory is %s" % cwd_dir
      #pkg_cmd = ''.join([cwd_dir + "/hap/scripts/hevc.cmd"])
      pkg_cmd = ''.join(["python " + cwd_dir + "/hap/scripts/adsp_pack.py -p pkg_hd22"])
      print pkg_cmd
      proc = subprocess.Popen(pkg_cmd, shell=True)
      (out, err) = proc.communicate()      

#=================================================================================
#=================================================================================
#                  Function definitions ends here
#=================================================================================
#=================================================================================

