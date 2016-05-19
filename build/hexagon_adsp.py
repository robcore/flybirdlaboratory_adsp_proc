#===============================================================================
#
# CoreBSP HEXAGON tool rules
#
# GENERAL DESCRIPTION
#    HEXAGON Tools definitions
#
# Copyright (c) 2009-2013 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/dspbuild.adsp/2.5/hexagon_adsp.py#19 $
#  $DateTime: 2014/11/06 17:14:38 $
#  $Author: pwbldsvc $
#  $Change: 6907538 $
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# when       who         what, where, why
# --------   ---         ---------------------------------------------------------
# 05/08/14   corinc      Check the tool version for the correct bin path
#===============================================================================
import sys
import os
import string
import SCons.Action
from SCons.Script import *


   
#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('hexagon_adsp')

def generate(env):
   #===============================================================================
   # load hexagon.py to environment
   #===============================================================================
   env.Tool('hexagon', toolpath = ['${BUILD_ROOT}/tools/build/scons/scripts'])

   #===============================================================================
   # figure out what tools set will be using
   #===============================================================================
   # The following environment variables must be defined prior to using this make
   # file: GNUPATH, QCTOOLS. In addition the PATH must be updated for
   # the GCC tools.

   hexagon_root = os.environ.get('HEXAGON_ROOT', None)   
   hexagon_image_entry = os.environ.get('HEXAGON_IMAGE_ENTRY', '0xf0000000')   
   hexagon_rtos_release = os.environ.get('HEXAGON_RTOS_RELEASE', None)
   q6version = os.environ.get('HEXAGON_Q6VERSION', None)
   q6_reqdversion = os.environ.get('HEXAGON_REQD_Q6VERSION', None)
   hexagon_major_tool_ver = int(hexagon_rtos_release[0])
      
   # init variables to environment
   env.Replace(QDSP6_RELEASE_DIR = "${HEXAGON_ROOT}/${HEXAGON_RTOS_RELEASE}")
   env.Replace(Q6_REQDVERSION = q6_reqdversion)
   env.Replace(HEXAGON_TOOL_MAJOR = hexagon_rtos_release[0])
   
   if not env.PathExists("${QDSP6_RELEASE_DIR}"):
      env.PrintError("-------------------------------------------------------------------------------")
      env.PrintError("*** HEXAGON tools are not present")
      env.PrintError("*** Please install HEXAGON tools")
      env.PrintError("*** Currently setup for RTOS: ${HEXAGON_RTOS_RELEASE}")
      env.PrintError("*** Missing RTOS PATH: ${QDSP6_RELEASE_DIR}")
      env.PrintError("*** Recommended locations:")
      env.PrintError("***      Windows: C:\Qualcomm\HEXAGON_Tools")
      env.PrintError("***      Linux: HOME/Qualcomm/HEXAGON_Tools (OR) /pkg/qct/software/hexagon/releases/tools")
      env.PrintError("***      Note: If installed at other location, please update \'Software Paths & other definitions\' section in \'build.py\' accordingly")
      env.PrintError("***            OR set HEXAGON_ROOT and HEXAGON_RTOS_RELEASE environment variables accordingly")
      env.PrintError("***               Eg: set HEXAGON_ROOT=C:\Qualtools\Hexagon")
      env.PrintError("***                   set HEXAGON_RTOS_RELEASE=5.1.04")
      env.PrintError("-------------------------------------------------------------------------------")
      Exit(1)


   
   #----------------------------------------------------------------------------
   # common defines for all components
   #----------------------------------------------------------------------------

   env.Append(CFLAGS='-D__qdsp6__=1')
   env.Append(CFLAGS='-fstack-protector')
   env.Append(CFLAGS = '-G0')

   if 'BUILD_BAREBONE' in env:
      env.Append(CFLAGS='-DBAREBONE_ADSP=1')

   if 'BUILD_SLPI' in env:
      env.Append(CFLAGS='-DSENSOR_LPI=1')
      
   if 'USES_AVS_TEST' in env or env.get('CHIPSET').startswith('mdm') or os.environ.get('BUILD_ACT')=='SIM' or 'BUILD_BAREBONE' in env or 'BUILD_SLPI' in env:
      env.AddUsesFlags('USES_PLATFORM_MINIMAL')
   else:
      env.AddUsesFlags('USES_PLATFORM_FS')
      
   if ARGUMENTS.get('SIM') == "1" or ARGUMENTS.get('SIM') == "TRUE":
      env.AddUsesFlags(['USES_AVS_TEST', 'USES_SENSORS_INTEGRATION_ENABLED'])
   else:
      env.AddUsesFlags(['USES_ADSPPM_INTEGRATION_ENABLED', 'USES_SENSORS_INTEGRATION_ENABLED','USES_VIDEO_INTEGRATION_ENABLED'])

   #---------------------------------------------------------------------------
   # Set the Kernel Target Configuration
   #---------------------------------------------------------------------------
   if env['MSM_ID'] in ['8992']:
      env.Replace(QURT_BUILD_CONFIG="ADSPv56MP")
   if env['MSM_ID'] in ['8994']:
      env.Replace(QURT_BUILD_CONFIG="ADSPv56MP")
   elif env['MSM_ID'] in ['8996']:
      env.Replace(QURT_BUILD_CONFIG="ADSPv60MP")
   else:
      env.Replace(QURT_BUILD_CONFIG="ADSPv5MP")

   env.Replace(QDSP6_QURT_TOOLDIR = "${COREBSP_ROOT}/kernel/qurt/build/core_libs/qdsp6/AAAAAAAA/install/${QURT_BUILD_CONFIG}/scripts")
   env.Replace(QDSP6_LIBDIR = "${COREBSP_ROOT}/kernel/qurt/build/core_libs/qdsp6/AAAAAAAA/install/${QURT_BUILD_CONFIG}/lib")

   #---------------------------------------------------------------------------
   # Enable Qshrink feature for 9x25, 8x10, 8994
   #---------------------------------------------------------------------------
   if env['MSM_ID'] in ['9x25'] or env['MSM_ID'] in ['8x10'] or env['MSM_ID'] in ['8994']:
      env.AddUsesFlags('USES_FEATURE_QSHRINK_ENABLED')

   #-------------------------------------------------------------------------------
   # set the flag to configure remote heap
   #-------------------------------------------------------------------------------
   if env['MSM_ID'] in ['8992'] or env['MSM_ID'] in ['8994']:
      env.AddUsesFlags('USES_REMOTE_HEAP')   

   #-------------------------------------------------------------------------------
   # set chipset directory where contain the XML file and etc, 
   # here didn't consider the case when multiple Flag presents, will update once this usecase is needed
   #-------------------------------------------------------------------------------

   if env['MSM_ID'] in ['8992'] or env['MSM_ID'] in ['8994']:
      env.AddUsesFlags('USES_L2LL')


   env.Replace(CHIPSET_DIR = "${CHIPSET}")

   if 'USES_MEMOPT' in env:
      env.Replace(CHIPSET_DIR = "${CHIPSET}MEMOPT")
   if 'USES_L2LL' in env:
      env.Replace(CHIPSET_DIR = "${CHIPSET}")
   if 'USES_L2TCM' in env:
      env.Replace(CHIPSET_DIR = "${CHIPSET}L2TCM")
   if 'AUDIO_IN_USERPD' in env:
      env.Replace(CHIPSET_DIR = "${CHIPSET}MPD")

   env.PrintInfo("chipset directory is  ${CHIPSET_DIR}")

   #Add ADSP Image specific linker inputs here
   env.LoadToolScript('qdsp6_defs_adsp', toolpath = ['${BUILD_ROOT}/build/ms'])
   #G0 flag is required so that it is uniform. kernel libs are compiled with G0
   print 'COMPILER= ', os.environ.get('COMPILER', None)
   if hexagon_major_tool_ver <= 6:
      env.Replace(QDSP6_RELEASE_LIB_DIR="${QDSP6_RELEASE_DIR}/dinkumware/lib/${Q6VERSION}/G0")
      env.Replace(LINKER_FILE="adsp.linker")
#      env.Replace(QDSP6BIN = "${QDSP6_RELEASE_DIR}/gnu/bin")
#      print 'QDSP6_RELEASE_LIB_DIR = dinkumware/lib'
   else: # LLVM (version >= 7) path for the Q6 released library path
      env.Replace(QDSP6_RELEASE_LIB_DIR="${QDSP6_RELEASE_DIR}/Tools/target/hexagon/lib/${Q6VERSION}/G0")
      env.Replace(LINKER_FILE="adsp_llvm.linker")
      env.Replace(QDSP6BIN = "${QDSP6_RELEASE_DIR}/Tools/bin")
      # temporary adding the hexgon warning flags for LLVM, -Wno-cast-align
      env.Replace(HEXAGON_WARN = "-Wall -Wpointer-arith -Wno-cast-align")
#      print 'QDSP6_RELEASE_LIB_DIR = Tools/target/hexagon'
   # builder to support dynamic linking -- 3 component need this builder core_libs.scons/devcfg_img.scons/platform_libs.scons
   env.LoadToolScript('platform_builders', toolpath = ['${BUILD_ROOT}/platform/build'])

     
   #-------------------------------------------------------------------------------
   # Software tool and environment definitions
   #-------------------------------------------------------------------------------

   env.PrintInfo("Print from hexagon_adsp.py version")
   env.PrintInfo("HEXAGON_TOOLS       = ${HEXAGON_TOOLS}")
   env.PrintInfo("HEXAGON_RTOS_REL    = ${HEXAGON_RTOS_RELEASE}")
   env.PrintInfo("Q6VERSION           = ${Q6VERSION}")      
   env.PrintInfo("HEXAGON_ROOT        = %s" % env.RealPath("${HEXAGON_ROOT}"))
   env.PrintInfo("QDSP6BIN            = ${QDSP6BIN}")
   env.PrintInfo("HEXAGON_IMAGE_ENTRY = ${HEXAGON_IMAGE_ENTRY}")   
   print "Hexagon tool version major: %s" %hexagon_major_tool_ver
   #============================================================================
   #print env.Dump()
