
#=================================================================================
#   File Name: build.py
#
#   Python Script to call the QC-SCons build System for Badger
#
#   Copyright (c) 2013 QUALCOMM Technologies Incorporated.
#   All rights reserved. Qualcomm Proprietary and Confidential.
#
#---------------------------------------------------------------------------------
#
#  $Header: //components/rel/dspbuild.adsp/2.5/build.py#41 $
#  $DateTime: 2014/09/29 04:54:59 $
#  $Change: 6676211 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
#   when     who            what, where, why
# --------   ---        ----------------------------------------------------------
# 03/04/13   Haseeb Khan    Script to call the QC-SCons build System for Badger    
# 06/12/13   corinc         Moved Build.py to adsp_proc\build\
# 12/08/13   Haseeb Khan    Added Support to compile using verbose levels, 
#                           individual module compilation & with any Scons Options
# 04/15/14   corinc         Add tool version support from command line for both LLVM & gcc
# 04/29/14   corinc         Moved functions to new file adspprocess.py
# 04/29/14   corinc         reverted back because of BuildProducts.txt copying failure in Tiberium
# 05/07/14   corinc         re-architect build system phase 3
# 05/08/14   corinc         fixed the issue for alias
# 05/09/14   corinc         moved 2 OpenDSP code to be functions to new OpenDSP.py file
# 06/04/14   Haseeb Khan    Moved from optparse to argparse
# 06/12/14   corinc         Python version check when imprting argparse
# 06/16/14   Haseeb Khan    Inform user of the compilation result 
# 07/24/14   corinc         Default Compiler and Q6 version for each chipset
#=================================================================================


import os
import re
import subprocess
import sys
import time
import fnmatch
import shutil, errno
import adspprocess
import OpenDSP
from buildSysInfo import defaultSysInfo
from buildSysInfo import buildSysInfo

try:
   import argparse
   from argparse import RawTextHelpFormatter
except ImportError:
   print 'Python version is: ' + sys.version
   print 'ADSP build system  requires Python version 2.7.6 and above.'
   print 'If you have Python version 2.7.6 installed, please check the environment path.' 
   sys.exit(0)

if sys.version:
   print "\n\nPython Version::\n", sys.version
   if sys.version_info[0] != 2 and sys.version_info[1] != 7:
       print "ERROR:: You are not using Python 2.7.6. Please use 2.7.6, preferably 2.7.6 and above"
       sys.exit(0)
else:
   print '\n\nERROR: Python not installed!!!'
   print 'If installed already, please verify if respective path added to PATH environment variable!!!\n\n'
   sys.exit(0)

# Checking current working directory.
cwd_dir = os.getcwd()
adspproc_dir = os.getcwd()
print "\n\n checking adsp_proc, current working directory: %s" % adspproc_dir

# Now changing the directory to adsp_proc
adsp_dir = "adsp_proc"
bsp_dir  = "bsp"
ms_dir   = "ms"

if os.path.exists(adsp_dir):
    os.chdir(adsp_dir)
    print "1. Changed to \\adsp_proc\n\n"
    pass
elif os.path.exists(bsp_dir) and os.path.exists(ms_dir):
    os.chdir('../')
    print "2. in \\adsp_proc\\build, moved up to \\adsp_proc \n\n"
    pass
else:
    print "3. Your are already in \\adsp_proc\n\n"
    pass # do nothing!

     
#=================================================================================
#=================================================================================
#                  Software Paths & other definitions are below
#                    (edit these based on requirement)
#=================================================================================
#=================================================================================

#=============   For Windows Environment (Recommended locations)   =============
#Hexagon tools path for windows
#Donot specify path till version folder, path will be appended later using 'q6_rtos_tools_version'
q6_tools_path_win = r"C:/Qualcomm/HEXAGON_Tools"

#Python installation path for windows
#This python path is for internal builds in Qualcomm
#User need not modify it as python path will be directly taken from local path
python271_win = r"C:/CRMapps/Apps/Python271"
python276_win = r"C:/CRMapps/Apps/Python276-64"
if os.path.exists(python276_win):
   python_win = python276_win
else:
   python_win = python271_win
#=============   End of Windows Environment (Recommended locations)   =============


#=============   For Linux Environment (Recommended locations)   =============
#Hexagon tools from Local Linux machine
#Note: Hexagon tools from local Linux machine will be preferred if both(Local and Network paths) are present
q6_tools_path_linux = 'None'
if os.environ.get('HOME', None):   
   home_dir = os.environ.get('HOME', None)
   print '\nHOME directory is:', home_dir
   #Donot specify path till version folder, path will be appended later using 'q6_rtos_tools_version'
   q6_tools_path_linux = home_dir + "/Qualcomm/HEXAGON_Tools"

#Hexagon tools from Network Location
#Donot specify path till version folder, path will be appended later using 'q6_rtos_tools_version'
q6_tools_netpath_linux = '/pkg/qct/software/hexagon/releases/tools'

#Python installation path for Linux
#This python path is for internal builds in Qualcomm
#User need not modify it as python path will be directly taken from local path
python_linux = "/pkg/python/2.7.5/bin"

#=============   End of Linux Environment (Recommended locations)   =============

#=================================================================================
#=================================================================================
#                  Software Paths & other definitions ends here
#                    (edit these based on requirement)
#=================================================================================
#=================================================================================


#=================================================================================
#=================================================================================
#                  Main build.py starts here
#=================================================================================
#=================================================================================

#=================================================================================
print '\nbuild.py usage help...'
usage = " \
                 --Command for build/clean of dsp image \n \
                   cd adsp_proc \n \
                      To Build dsp image:           python build.py -b 0x8fffffff -c msm8974 -o all   (by default -p mapped to 'mpd') \n \
                      To Build sim-only dsp image:  python build.py -b 0x8fffffff -c msm8974 -o sim   (by default -p mapped to 'mpd') \n \
                      To Clean dsp image:           python build.py -b 0x8fffffff -c msm8974 -o clean (by default -p mapped to 'mpd') \n\n \
                 --Command for build/clean of dsp image with default parameters \n \
                   cd adsp_proc \n \
                      To Build dsp image:           python build.py -o all    (this will take default parameters as: -b 0x8fffffff, -c msm8974 and -p mpd) \n \
                      To Build sim-only dsp image:  python build.py -o sim    (this will take default parameters as: -b 0x8fffffff, -c msm8974 and -p mpd) \n \
                      To Clean dsp image:           python build.py -o clean  (this will take default parameters as: -b 0x8fffffff, -c msm8974 and -p mpd) \n\n \
                 --Command for Only CoSim (Assuming the dsp image is already built) \n \
                   cd adsp_proc \n \
                      Only Build CoSim & Run CoSim:  python build.py -o cosim \n \
                      Only Run CoSim:                python build.py -o cosim_run \n\n \
                 --Command for build/clean of dsp image & CoSim \n \
                   cd adsp_proc \n \
                      To Build dsp image & Build CoSim, Run CoSim:           python build.py -o all,cosim \n \
                      To Build dsp image & Run CoSim:                        python build.py -o all,cosim_run \n \
                      To Build sim-only dsp image & Build CoSim, Run CoSim:  python build.py -o sim,cosim \n \
                      To Build sim-only dsp image & Run CoSim:               python build.py -o sim,cosim_run \n \
                      To Build dsp image & Run CoSim for OEM_ROOT:           python build.py -o all,oemroot_cosim_run \n \
                      To Clean dsp image:                                    python build.py -o clean \n\n \
                 --Command to create HAP packages \n \
                   cd adsp_proc \n \
                      To create HK11 package:        python build.py -o pkg_hk11 \n \
                      To create HY11/HY31 package:   python build.py -o pkg_oem \n \
                      To create HD11 package:        python build.py -o pkg_hd11 \n \
                      To create HY22 package:        python build.py -o pkg_isv \n \
                      To create HCBSP_Test package:  python build.py -o pkg_hcbsp \n\n \
                 --Command to use Verbose levels \n \
                      To compile with verbose level 2:          python build.py -v 2 \n \
                      0[=off] or 1[=limited] or 2[=detailed] or 3[raw, no formatting] \n\n \
                 --Command to Compile Individual Module \n \
                      To Compile Individual Module in avs:      python build.py -m avs/aud/services/static_svcs/audio_dev_mgr \n \
                      (specify path just before 'build' folder)  \n\n \
                 --Command to add SCons Options \n \
                      To add SCons Options(seperated by comma): python build.py -s --implicit-deps-unchanged,--ignore-errors \n\n \
                 --Command to use different tools version for compilation \n \
                      python build.py -tv 5.1.04 \n\n \
                 --For help:  python build.py -h"
                 

parser = argparse.ArgumentParser(description=usage, formatter_class=RawTextHelpFormatter)  


parser.add_argument('-b', '--buildid', help='buildid option [Default: 0x8fffffff]', dest='buildid', action='store')

parser.add_argument('-c', '--chipset', help='chipset option, No Default, must specify chipset in ENGG build', dest='chipset', action='store')

parser.add_argument('-p', '--pid', help='protection domain option [Default: mpd]', dest='protection_domain', action='store')

parser.add_argument("-o", "--others", help='other variable number of options(seperated by comma): <ARG1>,<ARG2> ... \n\
Eg: all,sim,clean,cosim,cosim_run,oemroot_cosim_run \n\
    To create packages: pkg_hk11,pkg_oem,pkg_hd11,pkg_isv,pkg_hcbsp \n\
    all: Build the dsp image.          \n\
    sim: Build the sim-only dsp image.          \n\
    clean: Clean the dsp image.               \n\
    cosim: Build CoSim & Run CoSim will be Enabled. \n\
    cosim_run: Only Run CoSim will be Enabled. \n\
                   oemroot_cosim_run: Only Run CoSim for OEM_ROOT will be Enabled.\nAny new arguments, in future, can be added here. ', \
                   dest='other_option', action=adspprocess.other_options_cb)

parser.add_argument('-f', '--flags', help='Flags to pass to the build system(seperated by comma): <FLAG1>,<FLAG2> ... \n\
                   Any new flags, in future, can be added here', \
                   dest='flags', action=adspprocess.other_options_cb)
                   
parser.add_argument('-k', '--kloc', help='To enable klocwork [Default: Disabled]', dest='kloc', action='store_true')

parser.add_argument('-t', '--test', help='To automate testing of opendsp packages [Default: Disabled]', dest='test', action='store_true')

parser.add_argument('-v', '--verbose' , help='To compile with specified verbose levels [Default 1] \n\
                   0[=off] or 1[=limited] or 2[=detailed] or 3[raw, no formatting]', dest='verbose', action='store')

parser.add_argument('-m', '--module', help='To Compile Individual Module (specify path just before \'build\' folder) [Default: Disabled]', dest='module', action='store')

parser.add_argument('-a', '--alias', help='To specify image alias [core_libs, avs_libs,adsp_link, sensor_img, msm8974_MPD] etc. \n\
if not specified, script will assign the target specific image alias based on chipset information', dest='alias', action='store')

parser.add_argument('-s', '--sconsargs', help='To add SCons Options(seperated by comma) \n\
Like keep-going,implicit-deps-unchanged,implicit-cache,ignore-errors etc...', dest='sconsargs', action=adspprocess.other_options_cb)

parser.add_argument('-u', '--userargs', help='To add Custom User Options(seperated by comma) \n\
Like major_version=3,minor_version=5,is_qurt_enabled=yes etc...', dest='userargs', action=adspprocess.other_options_cb)

parser.add_argument('-tv', '--tv', '--toolversion', help='To specify HexagonTools version [Default: -tv 5.1.04], GCC tool version is 5.x.x and before, LLVM tool version is 6.x.x and beyond', dest='toolversion', action='store')

opts = parser.parse_args()
args = sys.argv
(opts, args) = adspprocess.postprocess_command_options(opts, args)

if opts.other_option is None:
   opts.other_option = 'all'

if type(opts.other_option) is not list:
   opts.other_option = [opts.other_option] 

sconsargs_values = ''
if opts.sconsargs is not None:
    sconsargs_values = opts.sconsargs.split(',')
    opts.sconsargs = ''    
    for arg in sconsargs_values:  
       opts.sconsargs += '--'+arg+','
    opts.sconsargs = opts.sconsargs.rstrip(',')
    opts.sconsargs = opts.sconsargs.rstrip('--')

if opts.userargs is not None:
    opts.userargs = opts.userargs.rstrip(',')
    
#print opts
#print args

#parser.print_help()
#print "\n\n"

alloptions = ['buildid', 'chipset', 'protection_domain', 'other_option', 'flags', 'kloc','verbose', 'module', 'alias', 'toolversion', 'sconsargs', 'userargs'] 

#=================================================
#  Initialize the build system info flags
#=================================================
defSysInfo=defaultSysInfo()
bldSysInfo=buildSysInfo()

############################################################################################
######## If 'hap/default_pack.txt' present then extract default parameters from this file ##
########       If user options specified, will override these default values              ##
############################################################################################
default_params_filelist = adspprocess.find_files('hap', 'default_pack.txt')
if default_params_filelist:
   default_params_file = open( "hap/default_pack.txt", "r" )
   lines = []
   for line in default_params_file:      
      if not re.search('#', line):
         default_chipset_match = re.search('--chipset (\w\w\w\w\w\w\w)', line)
         default_pid_match = re.search('--pid (\w\w\w)', line)
         default_buildid_match = re.search('--buildid (\w\w\w\w\w\w\w\w\w\w)', line)
         default_others_match = re.search('--others (.+)', line)
         default_flags_match = re.search('--flags (.+)', line)
         default_verbose_match = re.search('--verbose (\d+)', line)
         default_module_match = re.search('--module (.+)', line)
         default_alias_match = re.search('--alias (.+)', line)
         default_sconsargs_match = re.search('--sconsargs (.+)', line)
         default_userargs_match = re.search('--userargs (.+)', line)
         
         if default_chipset_match:
            defSysInfo.default_chipset = default_chipset_match.group(1)
         if default_pid_match:
            defSysInfo.default_pid = default_pid_match.group(1)
         if default_buildid_match:
            defSysInfo.default_buildid = default_buildid_match.group(1)   
         if default_others_match:
            defSysInfo.default_others = default_others_match.group(1)
         if default_flags_match:
            defSysInfo.default_flags = default_flags_match.group(1)
         if default_verbose_match:
            defSysInfo.default_verbose = default_verbose_match.group(1)
         if default_module_match:
            defSysInfo.default_module = default_module_match.group(1)  
         if default_alias_match:
            defSysInfo.default_alias = default_alias_match.group(1)
         if default_sconsargs_match:
            defSysInfo.default_sconsargs = default_sconsargs_match.group(1)   
         if default_userargs_match:
            defSysInfo.default_userargs = default_userargs_match.group(1)               
      
   default_params_file.close()   

############################################################################################      

sconsargs_values = ''
if defSysInfo.default_sconsargs is not None:
    sconsargs_values = defSysInfo.default_sconsargs.split(',')
    defSysInfo.default_sconsargs = ''    
    for arg in sconsargs_values:  
       defSysInfo.default_sconsargs += '--'+arg+','
    defSysInfo.default_sconsargs = defSysInfo.default_sconsargs.rstrip(',')
    defSysInfo.default_sconsargs = defSysInfo.default_sconsargs.rstrip('--')

if defSysInfo.default_userargs is not None:
    defSysInfo.default_userargs = defSysInfo.default_userargs.rstrip(',')

############################################################################################
######## If 'hap/default_test.txt' present then extract default parameters from this file ##
######## File 'hap/default_test.txt' used for testing purposes on CRM                     ##
######## This is ONLY for CRM i.e., with -k option ONLY                                   ##
######## Also, enables only for opendsp packages as it needs 'hap/default_test.txt'       ##
########       If user options specified, will override these default values              ##
############################################################################################

default_testparams_filelist = adspprocess.find_files('hap', 'default_test.txt')
if ((default_testparams_filelist and opts.kloc) or opts.test):
   default_testparams_file = open( "hap/default_test.txt", "r" )
   lines = []
   for line in default_testparams_file:      
      default_testothers_match = re.search('--others (.+)', line)
      if default_testothers_match:
         defSysInfo.default_testothers = default_testothers_match.group(1)   
   default_testparams_file.close()   

#=================================================================================
# Check all build options and set in the build system information flags
#=================================================================================
adspprocess.allOptionsCheck(opts, alloptions, defSysInfo, bldSysInfo)

#=================================================================================
# set_chipset_target() is the main function to set the chipset specific OS environment parameters, 
# such as: target, chipset, compiler version, Q6 version, 
# try to find BLD_ENV_BUILD_ID enviroment variable
#=================================================================================
env_bld_id = os.environ.get('BLD_ENV_BUILD_ID', None)
if env_bld_id and not opts.chipset:
   print 'Extracting CHIPSET from BLD_ENV_BUILD_ID'   
   adspprocess.set_chipset_target(env_bld_id, bldSysInfo.chipset_param, opts)       
   bldSysInfo.chipset_flag = 1
else:
   if bldSysInfo.chipset_param:
      #print 'Chipset Parameter:', bldSysInfo.chipset_param
      if not env_bld_id:
         print 'BLD_ENV_BUILD_ID enviroment variable is None'
      else:
         print '-c option provided from command-line over-rides chipset extraction from BLD_ENV_BUILD_ID', bldSysInfo.chipset_param
      adspprocess.set_chipset_target(env_bld_id, bldSysInfo.chipset_param, opts)
   else: # ENGG build and no chipset specified will come here.
      print 'Error: chipset param is not specified from the command line, exit the build process !!!'
      print 'Please use <-c CHIPSET> option in the command line!!!'
      sys.exit(0)   


#exit the build process, if HEXAGON_Q6VERSION is not set in the set_chipset_target()
if os.environ.get('HEXAGON_Q6VERSION', None) is None:
   print 'Error: HEXAGON_Q6VERSION is not set in set_chipset_target(), exit the build process !!!'
   sys.exit(0)
 
      
#update q6_rtos_tools_version, if the compiler is specified in the command line
q6_rtos_tools_version = os.environ.get('HEXAGON_RTOS_RELEASE', None)
if q6_rtos_tools_version is None:
   print 'Error: HEXAGON_RTOS_RELEASE is not set in set_chipset_target(), exit the build process !!!'
   sys.exit(0)
   
# get the main version number to specify the compiler bin path
q6_tools_major_version = int(q6_rtos_tools_version[0])
#print "Set HEXAGON_RTOS_RELEASE = q6_rtos_tools_version"
#print "q6_tools_major_version = ", q6_tools_major_version

#=================================================================================
# Set the tool version and path info after command parsing is done
#For internal builds in Qualcomm
#=================================================================================
kw_path = "\\\\qctdfsrt\\prj\\qct\\asw\\StaticAnalysis\\Windows\\Klocwork\\Server\\bin"
sagen_path = "\\\\stone\\aswcrm\\smart\\nt\\bin"

q6_tools_path_win = q6_tools_path_win.replace('\\', '/').rstrip('/')
python_win = python_win.replace('\\', '/').rstrip('/')
q6_tools_path_linux = q6_tools_path_linux.rstrip('/')
q6_tools_netpath_linux = q6_tools_netpath_linux.rstrip('/')
python_linux = python_linux.rstrip('/')


q6_tools_linux = 'None'
if os.environ.get('HOME', None):
   q6_tools_linux = q6_tools_path_linux + "/" + q6_rtos_tools_version   
if not os.path.exists(q6_tools_linux): 
   q6_tools_path_linux = q6_tools_netpath_linux
   q6_tools_linux = q6_tools_path_linux + "/" + q6_rtos_tools_version

if os.name == 'posix':
   #For Linux: If Hexagon tools installed at location other than Recommended location
   #then this code would try and search hexagon tools in local path
   if not os.path.exists(q6_tools_linux):
      (q6_tools_path_linux, q6_tools_linux) = adspprocess.search_exe_tool('which')
else:
   #For Windows: If Hexagon tools installed at location other than Recommended location
   #then this code would try and search hexagon tools in local path 
   where_tools_path = q6_tools_path_win  + "/" + q6_rtos_tools_version
   if not os.path.exists(where_tools_path):      
      q6_tools_path_win = adspprocess.search_exe_tool('where')    
   

# try to find CRM_BUILDID enviroment variable
env_bld_ver = os.environ.get('CRM_BUILDID', None)
if env_bld_ver:
    print 'Extracting QDSP6_BUILD_VERSION from CRM_BUILDID'
    build_ver = os.environ['CRM_BUILDID']
    build_ver_match = re.search(r'([\w\.\d-]+?)(AAAA\w+)', build_ver)
    if not build_ver_match:
       build_ver_match = re.search(r'([\w\.\d-]+)(-\d)', build_ver)
    os.environ['QDSP6_BUILD_VERSION'] = build_ver_match.group(1)
    bldSysInfo.buildid_flag = 1
else:    
    if bldSysInfo.buildid_param:       
        print 'CRM_BUILDID enviroment variable is None'
        os.environ['QDSP6_BUILD_VERSION'] = bldSysInfo.chipset_param.upper() + "_" + bldSysInfo.buildid_param
        build_ver_match = re.search('(..)\w', os.environ['QDSP6_BUILD_VERSION'])
        # if build_ver_match.group(1) != '0x':
          # print 'ERROR: QDSP6_BUILD_VERSION should be a 32-bit hexa-decimal value with 0x \n       Eg: 0x8fffffff'
          # sys.exit(0)

if bldSysInfo.build_flags or defSysInfo.default_flags:
      print 'flags Parameter:', bldSysInfo.flags_param
      os.environ['BUILD_FLAGS'] = bldSysInfo.flags_param
else:
      os.environ['BUILD_FLAGS'] = ''
      bldSysInfo.flags_param = ''
        
if bldSysInfo.build_verbose_flag or defSysInfo.default_verbose:
      os.environ['BUILD_VERBOSE'] = bldSysInfo.opts_verbose
else:
      os.environ['BUILD_VERBOSE'] = ''

if bldSysInfo.build_filter_flag or defSysInfo.default_module:      
      #opts_module = opts.module
      bldSysInfo.opts_module = bldSysInfo.opts_module.replace('\\', '/')      
      os.environ['BUILD_FILTER'] = bldSysInfo.opts_module
      extract_component = bldSysInfo.opts_module.split('/', 1)
      extract_component[0] = extract_component[0].lower()      
      if extract_component[0] == 'sensors':
         os.environ['BUILD_COMPONENT'] = 'sensor_img'
      else:
         os.environ['BUILD_COMPONENT'] = extract_component[0]+'_libs'
else:
      os.environ['BUILD_FILTER'] = ''
      os.environ['BUILD_COMPONENT'] = ''
      bldSysInfo.opts_module = ''
      extract_component = ''

# check after build_filter_flag
# if users use build_filter to specifiy tech area unit without specifying image alias, image alias will be extraced from component path and append a "_libs" or "_img" accordingly
# if the alias generated by extracting from build filter option doesn't work, users need to specify the image alias 
if bldSysInfo.image_alias_flag or defSysInfo.default_alias:
      os.environ['BUILD_COMPONENT'] = bldSysInfo.opts_alias
 
if bldSysInfo.build_sconsargs_flag or defSysInfo.default_sconsargs:
      #opts_sconsargs = opts.sconsargs
      os.environ['BUILD_SCONSARGS'] = bldSysInfo.opts_sconsargs
else:
      os.environ['BUILD_SCONSARGS'] = '' 
      bldSysInfo.opts_sconsargs = ''

if bldSysInfo.build_userargs_flag or defSysInfo.default_userargs:  
      if os.environ['BUILD_SCONSARGS'] == '':
         os.environ['BUILD_SCONSARGS'] = bldSysInfo.opts_userargs
      else:
         os.environ['BUILD_SCONSARGS'] = os.environ['BUILD_SCONSARGS'] + ',' + bldSysInfo.opts_userargs
else:      
      bldSysInfo.opts_userargs = ''

    
os.environ['BUILD_FLAVOR'] = 'mpd'
os.environ['BUILD_ACT'] = ''
if bldSysInfo.mpd_flag:
   os.environ['BUILD_FLAVOR'] = 'mpd'
if bldSysInfo.spd_flag:
   os.environ['BUILD_FLAVOR'] = 'spd'
if bldSysInfo.clean_flag:
   os.environ['BUILD_ACT'] = 'clean'
if bldSysInfo.sim_flag:
   os.environ['BUILD_ACT'] = 'SIM'
if bldSysInfo.all_flag:
   os.environ['BUILD_ACT'] = ''
if bldSysInfo.sim_check:
   os.system("python -c 'from utils import check_sim;check_sim()'")   
   sys.exit(0)


if os.name == 'posix':
   print '\n\nIt is Linux environment!!!\n\n'
   if os.environ.get('HEXAGON_ROOT', None):
      q6_tools_path_linux = os.environ.get('HEXAGON_ROOT', None)
   else:
      os.environ['HEXAGON_ROOT'] = q6_tools_path_linux  
   
   os.environ['Q6_TOOLS_ROOT'] =  q6_tools_linux
   os.environ['Q6_ROOT'] = os.environ.get('Q6_TOOLS_ROOT', None)
   q6_root = os.environ['Q6_ROOT']
   if q6_tools_major_version <= 6:
      q6_root_eclipse = ''.join([q6_root, '/eclipse'])
      q6_root_gnu_bin = ''.join([q6_root, '/gnu/bin'])
      q6_root_qc_lib = ''.join([q6_root, '/qc/lib/iss/v5'])
      q6_root_qc_bin = ''.join([q6_root, '/qc/bin'])
   else: # LLVM path >= version 7
      q6_root_eclipse = ''.join([q6_root, '/eclipse'])
      q6_root_gnu_bin = ''.join([q6_root, '/Tools/bin'])
      q6_root_qc_lib = ''.join([q6_root, '/Tools/lib/iss/v5'])
      q6_root_qc_bin = ''.join([q6_root, '/Tools/bin'])

   os.environ['PYTHON_ROOT'] = python_linux
   python_root = os.environ['PYTHON_ROOT']
# at this stage Python version is 2.7.x, set PYTHONPATH in os env, 
# because the PATHONPATH could still be set to 2.6.x and below
   if os.environ.get('PYTHONPATH') is not None:
      os.environ['PYTHONPATH'] = python_linux
   if os.environ.get('PYTHON_PATH') is not None:
      os.environ['PYTHON_PATH'] = python_linux

else:
   if os.environ.get('HEXAGON_ROOT', None):
      q6_tools_path_win = os.environ.get('HEXAGON_ROOT', None)
      q6_tools_path_win = q6_tools_path_win.replace('\\', '/')
      os.environ['HEXAGON_ROOT'] = q6_tools_path_win
   else:
      q6_tools_path_win = q6_tools_path_win.replace('\\', '/')
      os.environ['HEXAGON_ROOT'] = q6_tools_path_win
   
   # HEXAGON_TOOLS_ROOT is not used in build system. Added to support TestFramework as it uses HEXAGON_TOOLS_ROOT
   if os.environ.get('HEXAGON_TOOLS_ROOT', None):
      q6_tools_4tfwk = os.environ.get('HEXAGON_TOOLS_ROOT', None)
      q6_tools_4tfwk = q6_tools_4tfwk.replace('\\', '/')
      os.environ['HEXAGON_TOOLS_ROOT'] = q6_tools_4tfwk
   else:
      os.environ['HEXAGON_TOOLS_ROOT'] = q6_tools_path_win + "/" + q6_rtos_tools_version      
   
      
   q6_tools_win = q6_tools_path_win + "/" + q6_rtos_tools_version
   os.environ['Q6_TOOLS_ROOT'] = q6_tools_win
   q6_tools_root = os.environ['Q6_TOOLS_ROOT']
   os.environ['Q6_ROOT'] = os.environ.get('Q6_TOOLS_ROOT', None)
   q6_root = os.environ['Q6_ROOT']
   
   if q6_tools_major_version <= 6:
      q6_root_eclipse = ''.join([q6_root, '/eclipse'])
      q6_root_gnu_bin = ''.join([q6_root, '/gnu/bin'])
      q6_root_qc_lib = ''.join([q6_root, '/qc/lib/iss/v5'])
      q6_root_qc_bin = ''.join([q6_root, '/qc/bin'])
   else: # LLVM path >= version 7
      q6_root_eclipse = ''.join([q6_root, '/eclipse'])
      q6_root_gnu_bin = ''.join([q6_root, '/Tools/bin'])
      q6_root_qc_lib = ''.join([q6_root, '/Tools/lib/iss/v5'])
      q6_root_qc_bin = ''.join([q6_root, '/Tools/bin'])

   os.environ['PYTHON_ROOT'] = python_win
   python_root = os.environ['PYTHON_ROOT']   
   if os.environ.get('PYTHONPATH') is not None:
      os.environ['PYTHONPATH'] = python_win
   if os.environ.get('PYTHON_PATH') is not None:
      os.environ['PYTHON_PATH'] = python_win

print "Current OS Environment:"
print os.environ
print '\n'
bldSysInfo.local_path = os.environ['PATH']
print '\nOld PATH is:\n', os.environ['PATH']
print '\n\n'

if os.name != 'posix':
   cwd_dir = os.getcwd()
   print "\n\nCurrent working directory is %s" % cwd_dir
   path_remove_cmd = ''.join([cwd_dir + "/hap/remove_cygwin.cmd"])
   if os.path.isfile(path_remove_cmd):   
      print path_remove_cmd
      proc = subprocess.Popen(path_remove_cmd, shell=True)
      (out, err) = proc.communicate()
      file_withpath = open("path_with_cygwin_removed.txt", "r")
      line_path = file_withpath.readline()
      bldSysInfo.local_path = line_path.replace('PATH=', '')
      file_withpath.close()
      os.remove('path_with_cygwin_removed.txt')

cmddbg_dir = os.getcwd()
print "\n\nbuild command directory is %s \n" % cmddbg_dir

if os.path.isfile("./build/build.py"):
   build_cmd = ''.join(['.\\tools\\build\\scons\\SCons\\scons --directory=./build ' , '--chipset=', os.environ.get('CHIPSET', None), ' ', \
                     '--build_version=', os.environ.get('QDSP6_BUILD_VERSION', None), ' ', '--build_flavor=', os.environ.get('BUILD_FLAVOR', None), ' ', \
                     '--build_act=', os.environ.get('BUILD_ACT'), ' ', '--build_flags=', os.environ.get('BUILD_FLAGS', None), ' ', \
                     '--build_verbose=', os.environ.get('BUILD_VERBOSE', None), ' ', '--build_component=', os.environ.get('BUILD_COMPONENT', None), ' ', \
                     '--build_filter=', os.environ.get('BUILD_FILTER', None), ' ', '--build_sconsargs=', os.environ.get('BUILD_SCONSARGS', None)])
   linux_build_cmd = ''.join(['./tools/build/scons/SCons/scons --directory=./build ', '--chipset=', os.environ.get('CHIPSET', None), ' ', \
                     '--build_version=', os.environ.get('QDSP6_BUILD_VERSION', None), ' ', '--build_flavor=', os.environ.get('BUILD_FLAVOR', None), ' ', \
                     '--build_act=', os.environ.get('BUILD_ACT'), ' ', '--build_flags=', os.environ.get('BUILD_FLAGS', None), ' ', \
                     '--build_verbose=', os.environ.get('BUILD_VERBOSE', None), ' ', '--build_component=', os.environ.get('BUILD_COMPONENT', None), ' ', \
                     '--build_filter=', os.environ.get('BUILD_FILTER', None), ' ', '--build_sconsargs=', os.environ.get('BUILD_SCONSARGS', None)])
   kw_build_cmd = ''.join([kw_path, '\\', 'kwinject -T kw_trace.txt ', build_cmd])
   
else:
   build_cmd = ''.join(['.\\tools\\build\\scons\\SCons\\scons ', '--chipset=', os.environ.get('CHIPSET', None), ' ', \
                     '--build_version=', os.environ.get('QDSP6_BUILD_VERSION', None), ' ', '--build_flavor=', os.environ.get('BUILD_FLAVOR', None), ' ', \
                     '--build_act=', os.environ.get('BUILD_ACT'), ' ', '--build_flags=', os.environ.get('BUILD_FLAGS', None), ' ', \
                     '--build_verbose=', os.environ.get('BUILD_VERBOSE', None), ' ', '--build_component=', os.environ.get('BUILD_COMPONENT', None), ' ', \
                     '--build_filter=', os.environ.get('BUILD_FILTER', None), ' ', '--build_sconsargs=', os.environ.get('BUILD_SCONSARGS', None)])
   linux_build_cmd = ''.join(['./tools/build/scons/SCons/scons ', '--chipset=', os.environ.get('CHIPSET', None), ' ', \
                     '--build_version=', os.environ.get('QDSP6_BUILD_VERSION', None), ' ', '--build_flavor=', os.environ.get('BUILD_FLAVOR', None), ' ', \
                     '--build_act=', os.environ.get('BUILD_ACT'), ' ', '--build_flags=', os.environ.get('BUILD_FLAGS', None), ' ', \
                     '--build_verbose=', os.environ.get('BUILD_VERBOSE', None), ' ', '--build_component=', os.environ.get('BUILD_COMPONENT', None), ' ', \
                     '--build_filter=', os.environ.get('BUILD_FILTER', None), ' ', '--build_sconsargs=', os.environ.get('BUILD_SCONSARGS', None)])
   kw_build_cmd = ''.join([kw_path, '\\', 'kwinject -T kw_trace.txt ', build_cmd])
   

if os.name != 'posix':
   print "Setting paths now..."   
   new_path = ''.join([python_root, ';', q6_root_gnu_bin, ';', q6_root_qc_lib, ';', q6_root_qc_bin]) 

if os.name == 'posix':
   new_path = ''.join([python_root, ':', q6_root_gnu_bin, ':', q6_root_qc_lib, ':', q6_root_qc_bin, ':'])
   new_engg_path = ''.join([new_path, ':', bldSysInfo.local_path, ':'])
   os.environ['PATH'] = new_engg_path
   print 'New PATH w.r.t Linux:\n', os.environ['PATH']
   if bldSysInfo.all_flag or bldSysInfo.sim_flag or bldSysInfo.clean_flag:
      latestCmdFile = open('./build/latest_build_command.txt', 'w')
      latestCmdFile.write(' '.join(sys.argv))
      latestCmdFile.close()
      
      adspprocess.summary_build(opts, defSysInfo, bldSysInfo)   
      print '\n\nBuild Command on Linux:\n', linux_build_cmd
      print "\n"   
      proc = subprocess.Popen(linux_build_cmd, shell=True)
      (out, err) = proc.communicate()   
else: #The complete code below till end is for non-linux case      
   if bldSysInfo.all_flag or bldSysInfo.sim_flag or bldSysInfo.clean_flag:      
      latestCmdFile = open('./build/latest_build_command.txt', 'w')
      latestCmdFile.write(' '.join(sys.argv))
      latestCmdFile.close()
      
      arg_flag = 0
      if bldSysInfo.other_option_flag:
         arg_flag = adspprocess.verify_args('\Aklocwork\Z', opts.other_option)         
      if arg_flag or bldSysInfo.klocwork_flag:	
         os.environ['BUILDSPEC'] = 'KLOCWORK'         
         new_kw_path = ''.join([new_path, ';', bldSysInfo.local_path, ';'])
         os.environ['PATH'] = new_kw_path
         print 'New PATH w.r.t klockwork:\n', os.environ['PATH']
         adspprocess.summary_build(opts, defSysInfo, bldSysInfo)
                  
         print '\n\nBuild Command with Klocwork:\n', kw_build_cmd
         print "\n"         
         proc = subprocess.Popen(kw_build_cmd, shell=True)
         (out, err) = proc.communicate()
               
         temp_dir = ".."
         os.chdir(temp_dir)
         cwd_dir = os.getcwd()      
         sagenconfig_run_cmd = ''.join([sagen_path, '\\', 'sagenconfig -r ', os.getcwd(), ' -t trace -f ./adsp_proc/kw_trace.txt'])      
         proc = subprocess.Popen(sagenconfig_run_cmd, shell=True)
         (out, err) = proc.communicate()
         adsp_dir = "adsp_proc"
         os.chdir(adsp_dir)
         cwd_dir = os.getcwd()      
      else:         
         new_engg_path = ''.join([new_path, ';', bldSysInfo.local_path])
         os.environ['PATH'] = new_engg_path
         print 'New PATH w.r.t engineering build:\n', os.environ['PATH']         
         adspprocess.summary_build(opts, defSysInfo, bldSysInfo)
               
         print '\n\nBuild Command for Engineering build:\n', build_cmd
         print "\n"         
         proc = subprocess.Popen(build_cmd, shell=True)
         (out, err) = proc.communicate()

if (bldSysInfo.all_flag or bldSysInfo.sim_flag) and (not bldSysInfo.opts_module) and (not bldSysInfo.opts_alias):
   cwd_dir = os.getcwd()
   print 'Current working directory', cwd_dir
   build_artifacts = ''.join([cwd_dir + "/dsp.elf"])
   if os.path.exists(build_artifacts):
      print '\n\nCompilation Result:  SUCCESS'
   else:
      print '\n\nCompilation Result:  FAIL'


# Bit-exactness Verification
OpenDSP.bixExactnessVerify(bldSysInfo)
   
# Test framework build and run
adspprocess.test_framework(opts, bldSysInfo, new_path)

# HAP packages creation
OpenDSP.HAPPackagesCreate(bldSysInfo)

#=====================================================
# Print Build system flag information for debugging
#=====================================================
#defSysInfo.printDefaultInfo()
#bldSysInfo.printBuildSysInfo()
      
#=================================================================================            
#=================================================================================
#                  Main build.py ends here
#=================================================================================
#=================================================================================            
            
            

