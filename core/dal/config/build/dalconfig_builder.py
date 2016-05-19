#===============================================================================
#
# DAL config autogen builder
#
# GENERAL DESCRIPTION
#    DAL config builder
#
# Copyright (c) 2009-2014 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/core.adsp/2.6.1/dal/config/build/dalconfig_builder.py#1 $
#  $DateTime: 2014/10/16 12:45:40 $
#  $Author: pwbldsvc $
#  $Change: 6781644 $
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 11/07/13   aa      Removed unused Scons builders and functions.
# 11/07/13   aa      cleanup_xml functionality converted to python.
# 09/20/10   vk      Add NOR tools image support
# 05/20/10   sc      Updated PROPGEN_CMD_WIN to use py version and replaced python with PYTHONCMD
# 03/24/10   wd      Added dependencies to have SCons rebuild when needed.
# 05/06/09   wd      Create
#
#===============================================================================
import os
import shutil
import subprocess
import string
import SCons.Scanner
from SCons.Script import *

#------------------------------------------------------------------------------
# Globals
#------------------------------------------------------------------------------
# can't call the exe from multiple treasd ath the same time a load dll fails
# for now call the perl file until this is fixed
#CLEANUP_XML_CMD_WIN = "${BUILD_ROOT}/dal/tools/cleanup_xml.exe"
CLEANUP_XML_CMD_WIN = "${DAL_ROOT}/tools/cleanup_xml.py"
CLEANUP_XML_CMD_LINUX = "${DAL_ROOT}/tools/cleanup_xml.py"

#PROPGEN_CMD_WIN = "${DAL_ROOT}/tools/propgen.exe"
PROPGEN_CMD_WIN = "${DAL_ROOT}/tools/propgen.py"
PROPGEN_CMD_LINUX = "${DAL_ROOT}/tools/propgen.py"

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('dalconfig_builder')

def generate(env):
   if env['PLATFORM'] == 'linux':
      env.Replace(CLEANUP_XML_CMD = CLEANUP_XML_CMD_LINUX)
      env.Replace(PROPGEN_CMD = PROPGEN_CMD_LINUX)
   else:
      env.Replace(CLEANUP_XML_CMD = CLEANUP_XML_CMD_WIN)
      env.Replace(PROPGEN_CMD = PROPGEN_CMD_WIN)
   
   dal_so_auto_generate(env)
   dal_moddir_src_auto_generate(env)
   dal_config_src_auto_generate(env)

   
#===============================================================================
# DAL Config SO Rules
#===============================================================================
def dal_so_auto_generate(env):
   DALConfig_so_act = env.GetBuilderAction(DALConfig_so_builder)
   DALConfig_so_bld = env.Builder(action = DALConfig_so_act)
   env.AddMethod(generate_devcfgso, "AddDevCfgSharedObj")
   env.Append(BUILDERS = {'DALConfigSOBuilder' : DALConfig_so_bld})  
   
     
#===============================================================================
# Common emitter function for auto generated DALModDir & DALConfig c files
#===============================================================================
def dal_src_emitter(target, source, env):
   # Add dependencies on tools
   env.Depends(target, env.SubstRealPath('${CLEANUP_XML_CMD}'))
   env.Depends(target, env.SubstRealPath('${PROPGEN_CMD}'))

   # Source file needs to be preprocess
   source_path, source_file = os.path.split(str(source[0]))
   target_path, target_file = os.path.split(str(target[0]))

   preprocess_xml = os.path.join(target_path, source_file)
   preprocess_xml = os.path.splitext(preprocess_xml)[0]
  
   pre_xml = env.PreProcess(preprocess_xml, source[0])
   env.Depends(target, pre_xml)
   
   # add clean for builder generated files
   env.Clean(target, preprocess_xml + '_out.xml')
   
   # add the preprocess file to the source for the builder to use
   source.append(pre_xml)

   # add explicit dependencies added by build system these are dependencies 
   # that SCons cannot detect because they are only known at compile time 
   # such as CUST_H (and all of its include files)
   if 'EXPLICIT_DEPS' in env:
      env.Depends(target, env['EXPLICIT_DEPS'])
   
   # here one can also add dependencies for say propgen.exe (if it needs to be build)
   # env.Depends(target, propgen_tool)
   return (target, source)


#===============================================================================
# Common action function for auto generated DALModDir & DALConfig c files
#===============================================================================
def dal_cmd_setup(env):
   
   # set root cmds depending on paltform
   if env['PLATFORM'] == 'linux':
      cleanup_root_cmd = "${PYTHONCMD} ${CLEANUP_XML_CMD}"
      propgen_root_cmd = "${PYTHONCMD} ${PROPGEN_CMD}"
   else:
      #cleanup_root_cmd = "${CLEANUP_XML_CMD}"
      cleanup_root_cmd = "${PYTHONCMD} ${CLEANUP_XML_CMD}"
      propgen_root_cmd = "${PYTHONCMD} ${PROPGEN_CMD}"
      
   return (cleanup_root_cmd, propgen_root_cmd)

   
#===============================================================================
# DAL ModDir Source build rules
#===============================================================================
def dal_moddir_src_auto_generate(env):
   DALModDir_src_act = env.GetBuilderAction(DALModDir_src_builder)
   DALModDir_src_bld = env.Builder(action = DALModDir_src_act, 
                               source_scanner = SCons.Scanner.C.CScanner(),
                               emitter = DALModDir_src_emitter,
                               suffix = '.c', src_suffix = '.xml')

   env.Append(BUILDERS = {'DALModDirSrcBuilder' : DALModDir_src_bld})
   
#-------------------------------------------------------------------------------
# DALModDir Emitter to add clean actions and other misc
#-------------------------------------------------------------------------------
def DALModDir_src_emitter(target, source, env):
   target, source = dal_src_emitter(target, source, env)
   return (target, source)

#-------------------------------------------------------------------------------
# DALModDir Source builder
#-------------------------------------------------------------------------------
def DALModDir_src_builder(target, source, env):
   
   target_path, target_file = os.path.split(str(target[0]))
   target_full = str(target[0])
   
   preprocess_xml = str(source[1]) # added by emitter
   clean_xml = os.path.splitext(preprocess_xml)[0] + '_out.xml'
   
   cleanup_root_cmd, propgen_root_cmd = dal_cmd_setup(env)
   
   #$(CC) -E $(CFLAGS) $(DMSS_CFLAGS) $(ALL_INCLUDES) $(DIRNAME) -I"$(ARMINC)" $(BUILD_VERSION) $(APPFLAGS) $(MSG_BT_SSID) $(OBJ_CMD) $(DALROOT)/config/dal_mod_modem_pre.xml $(DALROOT)/config/dal_mod_modem.xml
   #perl $(DALROOT)/tools/cleanup_xml.pl -post $(DALROOT)/config/dal_mod_modem_pre.xml $(DALROOT)/config/dal_mod_modem_out.xml $(DALROOT)/config/DALConfig_modem.c
   #$(DALPROPGEN) $(DALROOT)/config/dal_mod_modem_out.xml $(DALROOT)/config/ <DALModDir.c> <DALConfig.c> <devcfg_data.c>
   cmds = [
      cleanup_root_cmd +' -p '+ preprocess_xml +' -o '+ clean_xml +' -c '+ target_full,
      #propgen_root_cmd +' '+ clean_xml +' '+ target_path +'/ '+ str(target[0]) + ' "" ""'
      propgen_root_cmd + ' --XmlFile=' + clean_xml + ' --DirName=' + target_path + ' --ModDirFile=' + str(target[0]) + ' --RemoveDups=True'
   ]

   # run command(s)   
   data, err, rv = env.RunCmds(target, source, cmds)

   
   return None
   
   
#===============================================================================
# DAL Config Source build rules
#===============================================================================
def dal_config_src_auto_generate(env):
   DALConfig_src_act = env.GetBuilderAction(DALConfig_src_builder)
   DALConfig_src_bld = env.Builder(action = DALConfig_src_act, 
                               source_scanner = SCons.Scanner.C.CScanner(),
                               emitter = DALConfig_src_emitter,
                               src_suffix = '.xml')

   env.Append(BUILDERS = {'DALConfigSrcBuilder' : DALConfig_src_bld})

#-------------------------------------------------------------------------------
# DAL build Emitter to add clean actions and otheh misc
#-------------------------------------------------------------------------------
def DALConfig_src_emitter(target, source, env):
  target, source = dal_src_emitter(target, source, env)
  return (target, source)

#-------------------------------------------------------------------------------
# DAL Source builder
#-------------------------------------------------------------------------------
def DALConfig_src_builder(target, source, env):
   
   target_path, target_cfg_file = os.path.split(str(target[0]))
   target_config_full = str(target[0])
   target_devcfg_path, target_devcfgdata = os.path.split(str(target[1]))
   target_devcfgdata_full = str(target[1])
   
   preprocess_xml = str(source[1]) # added by emitter
   clean_xml = os.path.splitext(preprocess_xml)[0] + '_out.xml'
   
   cleanup_root_cmd, propgen_root_cmd = dal_cmd_setup(env)
   #import pdb; pdb.set_trace()
   #$(CC) -E $(CFLAGS) $(DMSS_CFLAGS) $(ALL_INCLUDES) $(DIRNAME) -I"$(ARMINC)" $(BUILD_VERSION) $(APPFLAGS) $(MSG_BT_SSID) $(OBJ_CMD) $(DALROOT)/config/dal_mod_modem_pre.xml $(DALROOT)/config/dal_mod_modem.xml
   #perl $(DALROOT)/tools/cleanup_xml.pl -post $(DALROOT)/config/dal_mod_modem_pre.xml $(DALROOT)/config/dal_mod_modem_out.xml $(DALROOT)/config/DALConfig_modem.c
   #$(DALPROPGEN) $(DALROOT)/config/dal_mod_modem_out.xml $(DALROOT)/config/ <DALModDir.c> <DALConfig.c> <devcfg_data.c>
   cmds = [
      cleanup_root_cmd +' -p '+ preprocess_xml +' -o ' + clean_xml +' -c '+ str(target[0]),
      #propgen_root_cmd +' '+ clean_xml +' '+ target_path +'/ '+ ' ' + target_config_full + ' ' + target_devcfgdata_full
      propgen_root_cmd + ' --XmlFile=' + clean_xml + ' --DirName=' + target_path + ' --ConfigFile=' + target_config_full + ' --DevcfgDataFile=' + target_devcfgdata_full + ' --ConfigType=' + env['CONFIG']
   ]

   # run command(s)   
   data, err, rv = env.RunCmds(target, source, cmds)
   return None


def generate_devcfgso(env, build_tags, include_path, target, source=[]):
   
   '''-------------------------------------------------------------------------
   DEVCFG SO builder wrapper

   This method wraps the builder to perform other operations that are require
   for partcilar build tag. In this case making sure the build tag it the correct 
   one.
   -------------------------------------------------------------------------'''
   
   #import pdb;pdb.set_trace()
   DALConfig_so = None
   devcfg_gen_so = str(target[0])
   DALConfig_src = source
   
   # don't do anything if tags doesnot match.
   if env.IsKeyEnable(build_tags):
      DALConfig_so = env.DALConfigSOBuilder(devcfg_gen_so, DALConfig_src, INC_LIST=include_path)

   return DALConfig_so
   
def DALConfig_so_builder(target, source, env):
   
   #import pdb; pdb.set_trace() 
   SO_NAME = str(target[0])
   SO_CMD = ""  
   
   '''------------------------------------------------------------------------------------------
   # hexagon-gcc -G0 -Wl,--no-as-needed -mv4 -fPIC -Wall -shared -nostartfiles -nostdlib 
   -shared -I      
   D:/....../adsp_proc/core/api/dal  
   D:/....../adsp_proc/core/dal/config/build/sensor_img/qdsp6/AAAAAAAA/DevCfg_sensor.c 
   D:/....../adsp_proc/core/dal/config/build/sensor_img/qdsp6/AAAAAAAA/devcfg_data_sensor.c -o 
   D:......./adsp_proc/core/dal/config/build/sensor_img/qdsp6/AAAAAAAA/DevCfg_sensor.so
   ----------------------------------------------------------------------------------------------'''
   
   if (os.name == 'posix') : #linux
       SO_CMD = env.get('QDSP6BIN') + "/"  
   else:                     #windows
       SO_CMD = env.get('QDSP6BIN') + "/" 
   
   SO_CMD = SO_CMD + "hexagon-gcc -G0 -Wl,--no-as-needed -m"+ env.get('Q6VERSION') + " -fPIC -Wall -shared -nostartfiles -nostdlib -shared" 

   for inc in env['INC_LIST']:
      SO_CMD = SO_CMD + " -I" + str(inc)
   
   for nodes in source :
      SO_CMD = SO_CMD + " " + str(nodes)
   SO_CMD =  SO_CMD + " -o " + SO_NAME
   env.ExecCmds(SO_CMD)
   return None
   
