#===============================================================================
#
# CBSP Products CMM Builder
#
# GENERAL DESCRIPTION
#    Contains rules to generate CMM scripts related info from the build
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/core.adsp/2.6.1/bsp/build/scripts/cmm_builder.py#1 $
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
# 07/07/2014 JB      Major Rev for correct scons implementation
# 04/30/2013 AJC	 v2 version. New checks and tags in place
# 10/27/2012 AJC	 Added debugtrace and products tech areas, cleaned up scripts
# 09/07/2012 AJC	 Added to RPM BF 1.0 Warehouse
# 09/07/2012 AJC	 Added support for args to be passed for each script
# 05/07/2012 AJC	 Added separate file for T32 extensions
# 11/11/2011 AJC	 Created for Aragorn (MPSS 2.0 and ADSP 2.0)
#==============================================================================

import os
import subprocess 
import string
import re
import glob
import fnmatch
import stat

# Define any globals out here
# Valid images on which the builder will be used
valid_images = {'core_rpm': 'RPM', 'core_adsp':'ADSP', 'core_modem':'MPSS','core_wcn':'WCNSS','core_apps':'APPS'}
# Tech teams
valid_areas = ['kernel','services','systemdrivers','power','debugtools','debugtrace','buses','storage','hwengines','dal', 'debug', 'mproc', 'securemsm', 'products']
# CMM Builder Globals
debug_filename='cmmbuilder_debug.txt'
t32menu_filename="std_scripts.men"
t32extn_filename="std_extensions.cmm"
t32config_filename="std_toolsconfig.cmm"
default_indent="\t"
IMAGE="image"
AREA="area"
CMMSCRIPTS="scripts"
ARGS="Arguments"
CMMBUILDER_LIST="ScriptsList"
CMMBUILDER_DICT="ScriptsDict"
MAINCMMDICT="MainCMMDict"
CMMFILES="CmmFiles"
CMMSCRIPTSCNT="ScriptsCount"
CMMBUILDER_TAG="ScriptsTag"
FILEPATTERNS=['*.cmm','*.per','*.men','*.t32']
EXTENSION_FILEPATTERNS=['.men','.t32']
# T32 icons to be used for the different extensions
FILEPATTERNS_ICONS={'.cmm':':FLASH','.per':':CHIP', '.men':':ACONFIG','.t32':':ACONFIG'}
FILEPATTERNS_CMDS={'.cmm':'cd.do','.per':'per.view', '.men':'menu.reprogram', '.t32':'task.config'}
RELPATH=''

# Other variables to be initialized
current_buildtag = ''


###############################################################
# Scons functions
###############################################################
def exists(env):
	return env.Detect('cmm_builder')

def generate(env):
	# Add methods to the scons environment
    env.AddUsesFlags('USES_CMMBUILDER')
   
    rootenv = env.get('IMAGE_ENV')
    rootenv[CMMFILES]=dict()
    rootenv[MAINCMMDICT]=dict()
    
    cmmbuilder_generate(env)

    
def cmmbuilder_generate(env):
    
    env.AddMethod(add_cmm_script, "AddCMMScripts")  
    env.AddMethod(cmmbuilder_generate_files, "CMMGenerateFiles")
    cmmbuilder_act = env.GetBuilderAction(	cmm_builder, action_source=None)
    
    
    cmmbuilder_bld = env.Builder(   action = cmmbuilder_act, 
                                    suffix='.men', 
                                    emitter = cmmbuilder_emit,
                                    src_suffix='.something')
                            
    env.Append(BUILDERS = {'CMMBuilder': cmmbuilder_bld})	   

	
def cmmbuilder_emit(target, source, env):
    rootenv = env.get('IMAGE_ENV')
    env.Depends(target, env.Value(str(rootenv[MAINCMMDICT])))

    return (target, source)

######################################################
#   Name: add_cmm_script
#   Action: Primary API by which tech team adds their script. 
#           Adds scripts and commands to 'scripts bucket' which 
#           is a dictionary in the env. Later this is picked up
#           by script generating methods
#   Notes:
#######################################################
def add_cmm_script(env, image, scriptpaths, scriptdict, area):
    rootenv = env.get('IMAGE_ENV')
    
    # Check the image argument and add it to the dictionary
    if image is False:
        raise RuntimeError, "Image entry cannot be empty. Error caused from area:" + str(area)
        return
    else:
        cmm_keys=valid_images.keys()
        for cmmkey in cmm_keys:
            if image == valid_images[cmmkey]:
                rootenv[CMMBUILDER_TAG]=image

        if rootenv[CMMBUILDER_TAG] == '':
            raise RuntimeError, "Unknown Image Specified: " + str(image) + ", In Area: " + str(area)

            
    cmmdict = dict()
    cmmdict[AREA]=[]
    # Check the area argument and add it to the dictionary
    if area is False:
        cmmbuilder_error(env, "Area cannot be empty")
        return
    elif area.lower() not in valid_areas:
        cmmbuilder_error(env, "Area: "+ area + " is not valid.")
        return
    else:
        cmmdict[AREA] = area[0].upper() + area[1:].lower()


    source_cmmscripts=[]
    for scriptname in scriptdict.keys():
        source_cmmscripts.append(rootenv.RealPath(scriptpaths[0]+'/'+scriptname))

    
    #Add this entry to the cmmscripts bucket
    arrayforthisarea=[source_cmmscripts,scriptdict]
    thisdictentry={area:arrayforthisarea}

    if area not in rootenv[CMMFILES]:
        rootenv[MAINCMMDICT].update(thisdictentry) 


###########################################################
#   Name: cmmbuilder_generate_files
#   Action: Wrapper Function which calls SCons Builder
#   Notes: Wrapper Function which calls SCons Builder
###########################################################
def cmmbuilder_generate_files(env):

	rootenv = env.get('IMAGE_ENV')
	
	cmmfiles = [rootenv.RealPath('${BUILD_ROOT}/core/products/scripts/std_scripts.men'),
				rootenv.RealPath('${BUILD_ROOT}/core/products/scripts/std_extensions.cmm'),
				rootenv.RealPath('${BUILD_ROOT}/core/products/scripts/std_toolsconfig.cmm')
			]	

	cmm_target_scripts_list=[]
	for key in rootenv[MAINCMMDICT].keys(): 
		for single_script in rootenv[MAINCMMDICT][key][0]: 
			cmm_target_scripts_list.append(single_script)
	
	
	cmm_master_hash=env.Value(str(rootenv[MAINCMMDICT]))
	env.Depends(cmmfiles,cmm_master_hash)
    
	cmmbuilderout = env.CMMBuilder(cmmfiles, cmm_target_scripts_list)
	
	
	return cmmbuilderout


###########################################################
#   Name: cmm_builder
#   Action: Calls sub-methods to generate cmm scripts
#   Notes: This is the main scons builder action
###########################################################
def cmm_builder(env, target, source):
    # This is a temporary test to see if the scripts are being added correctly.
    rootenv = env.get('IMAGE_ENV')
    cmmmasterlist=source


    a = cmm_menubuilder		    (env, str(target[0]))
    b = cmm_configbuilder		(env, str(target[1]))
    c = cmm_extensionbuilder	(env, str(target[2]))




###########################################################
#   Name: cmm_menubuilder
#   Action: Private method to generate menu T32 script
#   Notes:
###########################################################
def cmm_menubuilder(env, target ):
    rootenv = env.get('IMAGE_ENV')

    ###################################################
    # Create a file in the core/products/scripts folder
    ###################################################
    filename = env.RealPath(target)

    # This is the location of the scripts dir for this image
    scriptsdir_var = get_image_name(env) + "_SCRIPTSDIR"

    # Check if the file exists and change to writable
    if not os.path.exists( env['BUILD_ROOT']+'/core/products/scripts/' ):
                os.makedirs( env['BUILD_ROOT']+'/core/products/scripts/' )
    if os.path.isfile(filename):
        fileprops = os.stat(filename)[0]
        if (not fileprops & stat.S_IWRITE):
            os.chmod(filename, fileprops | stat.S_IWRITE)
        
    fptr = open(filename, 'w')
    indent = default_indent
    fptr.write("ADD \n"+ "MENU \n"+ "( \n")
    fptr.write(indent + "POPUP \"[:CORRELATE]&CoreBSP Scripts\" \n")
    fptr.write(indent + "( \n")
    indent = macro_incr_indent(indent)
    # Now add the entries for every script

    print rootenv[MAINCMMDICT]
    
    if rootenv[MAINCMMDICT]:
        for area in rootenv[MAINCMMDICT].keys():
            indent = "\t"
            fptr.write(indent + "POPUP \"[:PSTEP]&" + area + "\" \n")
            fptr.write(indent + "( \n")
            
            
            ListOfScriptFiles=[]
            for singlescript in rootenv[MAINCMMDICT][area][0]:
                ListOfScriptFiles.append(singlescript)
            
            
            
            for scriptpath in ListOfScriptFiles:
                scriptnamekey=os.path.basename(scriptpath)
                scriptname=rootenv.RelPath(scriptpath)
                argumentlist=rootenv[MAINCMMDICT][area][1][scriptnamekey]
                
                for properties in argumentlist:
                    #if it's not a list of lists, just set it
                    if type(argumentlist[0]) == type(''):
                        properties=argumentlist
                    #if type(argumentlist[0]) == type([]):
                    # properties has the following format
                    # [0] - Pretty Name of the script
                    # [1:] - Arguments to be passed to the script
                    # People might have zero arguments to pass along in which case,
                    # we identify that by checking the length
                    if (len(properties[0]) > 1):
                        # We have args
                        displayname = properties[0]
                        args = properties[1:]
                    else:
                        # We don't have any args
                        displayname = properties
                        args = []

                    indent = macro_incr_indent(indent)
                    (title, ext) = os.path.splitext(os.path.basename(scriptname))
                    fptr.write(indent + "MENUITEM \"[" + FILEPATTERNS_ICONS[ext] + "]&" + displayname[0].upper() + displayname[1:] + "\" \n")
                    fptr.write(indent + "( \n")
                    indent = macro_incr_indent(indent)
                    fptr.write(indent + "CD &"+ scriptsdir_var + "\n")
                    fptr.write(indent + FILEPATTERNS_CMDS[ext] + " " + scriptname + " "  + " ".join(args) + "\n")
                    indent = macro_decr_indent(indent)
                    fptr.write(indent + ")" + "\n")
                    indent = macro_decr_indent(indent)
                    
                    if properties == argumentlist:
                        break

            fptr.write(indent + ")" + "\n")

    # Now close the menu 
    indent = default_indent
    fptr.write(indent + ") \n")
    indent = macro_decr_indent(indent)
    fptr.write(")")
    fptr.close()

    return target

	

def cmm_extensionbuilder(env, target):
    rootenv = env.get('IMAGE_ENV')    
    
    filename = env.RealPath(target)
    
    # This is the location of the scripts dir for this image 
    scriptsdir_var = get_image_name(env) + "_SCRIPTSDIR"

    # Check if the file exists and change to writable
    if os.path.isfile(filename):
        fileprops = os.stat(filename)[0]
        if (not fileprops & stat.S_IWRITE):
            os.chmod(filename, fileprops | stat.S_IWRITE)
        
    fptr = open(filename, 'w')
    fptr.write((env.CreateFileBanner(os.path.basename(str(filename)), style="CMM")).replace('#','//'))
    fptr.write("\n")
    indent = ""


    ListOfScriptFiles=[]
    for area in rootenv[MAINCMMDICT].keys():
        for singlescript in rootenv[MAINCMMDICT][area][0]:
            singlescriptpath=rootenv.RelPath(singlescript)
            ListOfScriptFiles.append(singlescriptpath)
        

    # Now add the entries for every script
    for scriptname in ListOfScriptFiles:
        (title, ext) = os.path.splitext(os.path.basename(scriptname))
        # We are going to create extensions only for .t32 and .men files
        if ext in EXTENSION_FILEPATTERNS:
            fptr.write(indent + "CD &"+ scriptsdir_var + "\n")
            fptr.write(indent + FILEPATTERNS_CMDS[ext] + " " + scriptname + "\n")
            fptr.write("\n")
            
    # Now close the menu 
    indent = default_indent
    fptr.write("ENDDO")
    fptr.close()

    return target
	



def cmm_configbuilder(env, target):
    # Create a configuration file
    #filename = env['BUILD_ROOT']+'/core/products/scripts/'+t32config_filename
    filename = env.RealPath(target)
    RELPATH = os.path.dirname(filename)
    #env['BUILD_ROOT']+'/core/products/scripts'
    newline = "\n"

    # Get the values 
    build_root = str(os.path.relpath(env['BUILD_ROOT'], RELPATH)).replace('\\','/')
    build_root_core = str(os.path.relpath(env['COREBSP_ROOT'], RELPATH)).replace('\\','/')
    image_name = str(env.Dump('IMAGE_NAME')).replace('\'','')

    #Python variables for the CMM variables
    abs_build_root_var = get_image_name(env) + "_ABS_BUILD_ROOT";
    build_root_var = get_image_name(env) + "_BUILD_ROOT"
    build_root_core_var = get_image_name(env) + "_CBSP_ROOT"
    scriptsdir_var = get_image_name(env) + "_SCRIPTSDIR"
    buildmsdir_var = get_image_name(env) + "_BUILDMSDIR"

    # Check if the file exists and change to writable
    if ( not os.path.exists(RELPATH) ):
                os.makedirs(RELPATH)
    if os.path.isfile(filename):
        fileprops = os.stat(filename)[0]
        if (not fileprops & stat.S_IWRITE):
            os.chmod(filename,fileprops | stat.S_IWRITE)
    fptr = open(filename, 'w+')
    fptr.write((env.CreateFileBanner(os.path.basename(str(filename)), style="CMM")).replace('#','//'))
    fptr.write(newline + newline)

    fptr.write("GLOBAL &" + abs_build_root_var + newline)
    fptr.write("GLOBAL &" + build_root_var + newline)
    fptr.write("GLOBAL &" + build_root_core_var + newline)
    fptr.write("GLOBAL &" + scriptsdir_var + newline)
    fptr.write("GLOBAL &" + buildmsdir_var + newline)

    # Now assign the value
    # Now clean some space 
    fptr.write(newline * 3)
    fptr.write("&" + abs_build_root_var + "=\"" + str(env['BUILD_ROOT']).replace('\'','') + "\"" + newline)
    fptr.write("&" + build_root_var + "=os.ppd()" + "+\"/" +build_root + "\"" + newline)
    fptr.write("&" + build_root_core_var + "=os.ppd()" + "+\"/" + build_root_core + "\"" + newline)
    fptr.write("&" + scriptsdir_var + "=os.ppd()" + "+\"/" + build_root_core + "/products\"" + newline)
    fptr.write("&" + buildmsdir_var + "=os.ppd()" + "+\"/" + build_root + "/" + image_name.lower() + "/build/ms\"" + newline)
    fptr.write(newline * 2)
    fptr.write("ENDDO")
    fptr.close()

    return target


	
	
	
	
def cmmbuilder_debug_output(env, type, msg):
	# Create a file in the core/products/build folder
	filename = env['BUILD_ROOT']+'/core/products/build/'+debug_filename
	# Check if the file exists and change to writable
	if os.path.isfile(filename):
		fileprops = os.stat(filename)[0]
		if (not fileprops & stat.S_IWRITE):
			os.chmod(filename, fileprops | stat.S_IWRITE)
			
	fptr = open(filename, 'w+')
	
	# Depending on the type, you print the message accordingly. 
	if type == "string":
		fptr.write(msg)
	elif type == "list":
		fptr.write("List Debug:")
		for entry in msg:
			fptr.write(entry);
		fptr.write('\n \n')
	elif type == "table":
		fptr.write("Dictionary Debug:")
		for key,value in msg.iteritems():
			fptr.write(str(key)+':'+str(value))
			fptr.write('\n \n')
	else:
		cmmbuilder_error(env, "Unrecognized debug message type")
		
	
    
    
#################################
###Other various private methods
#################################
def get_image_name(env):
    try:
        
        #print env[CMMBUILDER_TAG]
        print "Current build tag : " + str(env[CMMBUILDER_TAG])
        return env[CMMBUILDER_TAG]
    except KeyError:
       raise RuntimeError, "cmmbuilder - CMMBUILDER_TAG is null!"
       return ''




def set_image_name(env, image_name, area):
    cmm_keys=valid_images.keys()
	
    for cmmkey in cmm_keys:
		if image_name == valid_images[cmmkey]:
			env[CMMBUILDER_TAG]=image_name
	
    if env[CMMBUILDER_TAG] == '':
		cmmbuilder_error(env, "CMM Builder tag null.")
		raise RuntimeError, "Unknown Image Specified: " + str(image_name) + ", In Area: " + str(area)
	
    return
    
    
def cmmbuilder_error(env, msg):
	env.PrintError(msg)
    
def macro_incr_indent(string):
	return (string +"\t")
	
def macro_decr_indent(string):
	return string[:-1]

	
	
	
	
	
#Note: structure should look something like the following:
#	(Pdb) pp rootenv[MAINCMMDICT]
#		{'DAL': [['B:\\adsp_proc\\core\\dal\\sys\\scripts\\DALLog.cmm'],
#				 {'DALLog.cmm': 'DAL Log'}],
#		 'Kernel': [['B:\\adsp_proc\\core\\kernel\\qurt\\build\\core_libs\\qdsp6\\AAAAAAAA\\install\\ADSPv56
#		MP\\debugger\\T32\\qurt_model.t32',
#					 'B:\\adsp_proc\\core\\kernel\\qurt\\build\\core_libs\\qdsp6\\AAAAAAAA\\install\\ADSPv56
#		MP\\debugger\\T32\\qurt_model.men'],
#					{'qurt_model.men': 'QuRT Menu',
#					 'qurt_model.t32': 'QuRT Extension'}],
#		 'Power': [['B:\\adsp_proc\\core\\power\\ulog\\scripts\\ULogDump.cmm'],
#				   {'ULogDump.cmm': 'ULog Dump'}],
#		 'SystemDrivers': [['B:\\adsp_proc\\core\\systemdrivers\\tlmm\\scripts\\tlmm_gpio_hw.cmm'],
#						   {'tlmm_gpio_hw.cmm': ['TLMM', '']}],
#		 'hwengines': [['B:\\adsp_proc\\core\\hwengines\\bam\\scripts\\bamsetup.cmm'],
#					   {'bamsetup.cmm': ['Setup BAM Scripts', '8994']}],
#		 'products': [['B:\\adsp_proc\\core\\products\\scripts\\std_cti_adsp.cmm',
#					   'B:\\adsp_proc\\core\\products\\scripts\\start_tracing_TPIU.cmm',
#					   'B:\\adsp_proc\\core\\products\\scripts\\start_tracing_ETB.cmm'],
#					  {'start_tracing_ETB.cmm': 'Start Trace ETB',
#					   'start_tracing_TPIU.cmm': 'Start Trace TPIU',
#					   'std_cti_adsp.cmm': ['Send CTI-GO to all cores', 'stuff']
#						}
#	
	
