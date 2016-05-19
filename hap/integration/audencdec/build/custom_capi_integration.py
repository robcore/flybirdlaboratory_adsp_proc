#===========================================================================================
#
# Custom CAPI Integration
#
# GENERAL DESCRIPTION
#    If OEM_ROOT is set, then this script will parse the below xml file and 
#	 generates the required header files in adsp_proc\hap\integration\audencdec\inc\ 
#       1) custom_static_capi_modules.xml
#
# Copyright (c) 2013 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------------------
#
# $Header: 
# $Date  : 2013/06/28 $
# $Author: coresvc $
#                      EDIT HISTORY FOR FILE
#                      
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#  
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------------------
# 06/28/13   DS      Create CAPI integration
#
#===========================================================================================

import re
import os
import string

import xml.dom.minidom
from xml.dom.minidom import parse

import inspect
from inspect import currentframe, getframeinfo

#-------------------------------------------------------------------------------------------
# Globals
#-------------------------------------------------------------------------------------------
# Custom Modules Global lists
custom_capi_module_id_name_list = [] 		#Global list, To store Custom Module Media Format ID names
custom_capi_module_id_value_list = [] 		#Global list, To store Custom Module Media Format ID values
custom_capi_module_header_list = []			#Global list, To store Custom Module CAPI header file names
custom_capi_module_get_size_api_list = []	#Global list, To store Custom Module get_size API name
custom_capi_module_ctor_api_list = []		#Global list, To store Custom Module ctor API name

#-------------------------------------------------------------------------------------------
# Function definitions
#-------------------------------------------------------------------------------------------
def exists(env):
	return env.Detect('custom_capi_integration')

def generate(env):
	env.AddMethod(create_static_capi_modules, "CreateStaticCAPIModules")
	return

#import pdb; pdb.set_trace()

#-------------------------------------------------------------------------------------------
# Function		: create_static_capi_modules
# Purpose 		: To create Custom static modules definition table with media format ID, 
#				  get_size and ctor API's name.
# Description 	: This function parse the custom_static_capi_modules.xml file located in 
# 			      <ROOT>\hap\integration\audencdec\config and creates the custom static CAPI 
#				  module tables in auto generated file "custom_AudioDecSvc_Util.h"
#-------------------------------------------------------------------------------------------
def create_static_capi_modules(env):
	if env.GetOption('clean'):
		return

	# Open XML document using minidom parser
	DOMTree = xml.dom.minidom.parse("../config/custom_static_capi_modules.xml")
	static_modules = DOMTree.documentElement

	#First create ../inc folder to generate required header files
	inc_path = "../inc"
	if not os.path.exists(inc_path):
		os.makedirs(inc_path)

	# Open "custom_AudioDecSvc_Util.h" file in write mode to create custom static modules table
	file_util = open("../inc/custom_AudioDecSvc_Util.h","w")

	file_util.write("/**\n"+"\tAuto Generated File\n\tFile: custom_AudioDecSvc_Util.h\n\n"+"\tHeader file contains all the modules and topologies information.\n")
	file_util.write("\tcustom_capi_integration.py in <ROOT>\hap\integration\\audencdec\\build\n")
	file_util.write("\twill generate this file when OEM_ROOT is defined."+"\n*/\n\n")
	file_util.write("/*==========================================================================\n")
	file_util.write("Copyright (c) 2013 QUALCOMM, Incorporated.  All Rights Reserved.\n")
	file_util.write("QUALCOMM Proprietary.  Export of this technology or software is regulated\n")
	file_util.write("by the U.S. Government, Diversion contrary to U.S. law prohibited.\n")
	file_util.write("\n==========================================================================*/\n")
	file_util.write("#ifndef __CUSTOM_AUDIODECSVC_UTIL_H__\n")
	file_util.write("#define __CUSTOM_AUDIODECSVC_UTIL_H__\n\n")
	file_util.write("/*--------------------------------------------------------------------------\n")
	file_util.write(" * Includes \n")
	file_util.write(" * -------------------------------------------------------------------------*/\n")
	file_util.write("#include \"custom_adsp_media_fmt.h\"\n")
	file_util.write("#include \"adsp_amdb_static.h\"\n\n")

	# Check for the availability of 'num_modules' attribute
	if static_modules.hasAttribute("num_modules"):
		# Print the total number of modules
		print "\n\nNumber of custom static modules : %s" % static_modules.getAttribute("num_modules")
	else:
		# If 'num_modules' attribute is not available, then print ERROR message and return
		frameinfo = getframeinfo(currentframe()) # to print line number and file name
		print "\nERROR: Please add 'num_modules' attribute to static_modules element in custom_static_capi_modules.xml file	",(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
		return

	# Number of modules that are going to be added to AMDB
	num_modules = static_modules.getAttribute("num_modules")

	# Get all the modules in the static_modules.xml
	modules = static_modules.getElementsByTagName("module")

	# Total number of modules
	total_num_mod = int(num_modules, base=10) # Convert the string into integer

	spaces = "                                                  "
	# Print details of each module and write into the appropriate header file
	print "\n********** Custom Static CAPI Modules **********"
	# Loop through the number of module times to create table all custom static modules
	cur_mod_num = 0
	for module in modules:
		cur_mod_num += 1 # increment the curretnn module number by 1
		if (module.getAttribute("type") == 'CAPI'): # if the current module is CAPI module then generate the CAPI module information
			# Read the mod_fmt_id_name in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_fmt_id_name')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_fmt_id_name' of module (%d) in custom_static_capi_modules.xml file	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				# If the above tag name found in the element
				module_id_name = module.getElementsByTagName('mod_fmt_id_name')[0]
				# Check for the existance of childnodes
				if(module_id_name.childNodes):
					mod_id_name = module_id_name.childNodes[0].data
					mod_id_name = mod_id_name.strip() # Remove '\n'
					mod_id_name = mod_id_name.upper() # Keep the module name in upper case.
					custom_capi_module_id_name_list.append(mod_id_name) # Append the CAPI module format ID name of the current module to 'custom_capi_module_id_name_list'
					print "Module Name\t\t:", mod_id_name
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter Module Format ID name for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_fmt_id_value in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_fmt_id_value')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_fmt_id_value' of module (%d) in custom_static_capi_modules.xml file	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				# If the above tag name found in the element
				module_id_value = module.getElementsByTagName('mod_fmt_id_value')[0]
				if(module_id_value.childNodes):
					mod_id_value = module_id_value.childNodes[0].data
					mod_id_value = mod_id_value.strip() # Remove '\n'
					custom_capi_module_id_value_list.append(mod_id_value) # Append the current CAPI module format ID value to 'custom_capi_module_id_value_list'
					print "Module ID Value\t\t:", mod_id_value
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter Module Format ID value for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the module CAPI header file name in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_capi_header_file')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_capi_header_file' of module (%d) in custom_static_capi_modules.xml file	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				# If the above tag name found in the element
				appi_header_file = module.getElementsByTagName('mod_capi_header_file')[0]
				if(appi_header_file.childNodes):
					appi_header_file_name = appi_header_file.childNodes[0].data
					appi_header_file_name = appi_header_file_name.strip() # Remove '\n'
					custom_capi_module_header_list.append(appi_header_file_name) # Append the current module CAPI header file to 'custom_capi_module_header_list'
					print "CAPI Header File \t:", appi_header_file_name + "\n"
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter Module CAPI header file name for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_get_size_f in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_get_size_f')) ==0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_get_size_f' of module (%d) in custom_static_capi_modules.xml file	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				# If the above tag name found in the element
				get_size_f = module.getElementsByTagName('mod_get_size_f')[0]
				if(get_size_f.childNodes):
					mod_get_size = get_size_f.childNodes[0].data
					mod_get_size = mod_get_size.strip() # Remove '\n'
					custom_capi_module_get_size_api_list.append(mod_get_size) # Append the current module get_size API name to 'custom_capi_module_get_size_api_list'
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter Module get_size API name for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_ctor_f in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_ctor_f')) == 0):
				# If the above tag name not found in the element, print ERROR message and append "ERROR" string to the list
				# custom_capi_module_ctor_api_list.append("ERROR")
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_ctor_f' of module (%d) in custom_static_capi_modules.xml file	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				# If the above tag name found in the element
				ctor_f = module.getElementsByTagName('mod_ctor_f')[0]
				if(ctor_f.childNodes):
					mod_ctor = ctor_f.childNodes[0].data
					mod_ctor = mod_ctor.strip() # Remove '\n'
					custom_capi_module_ctor_api_list.append(mod_ctor) # Append the current module ctor API name to 'custom_capi_module_ctor_api_list'
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter Module ctor API name for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return
		else:
			# If the module type is not CAPI, print ERROR message and return
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter Module type or specify the type as 'CAPI' for module (%d) in custom_static_capi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return

	# Check the total number of modules updated correctly
	# Print ERROR message when 'num_modules' is not greater or equal to 'cur_mod_num'(actual modules adding to AMDB)
	if(total_num_mod < cur_mod_num):
		frameinfo = getframeinfo(currentframe()) # to print line number and file name
		print "ERROR: Update the 'num_modules' attribute of 'static_modules' correctly with total number of modules",	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
	elif(total_num_mod > cur_mod_num):
		frameinfo = getframeinfo(currentframe()) # to print line number and file name
		print "WARNING: Update the 'num_modules' attribute of 'static_modules' correctly with total number of modules",	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
	
	# Include the CAPI header files
	file_util.write("/*------------------------------------------------------------------------\n")
	file_util.write(" * Include files of CAPI modules\n")
	file_util.write(" *------------------------------------------------------------------------*/\n")

	# Loop through the number of module times to include each module CAPI header file
	for i in range (len(custom_capi_module_header_list)):
		file_util.write("#include " + "\"" + custom_capi_module_header_list[i] + "\"" + "\n")
	
	file_util.write("\n")
	file_util.write("/*------------------------------------------------------------------------\n")
	file_util.write(" * Function Declrations\n")
	file_util.write(" *------------------------------------------------------------------------*/\n")
	file_util.write(" ADSPResult hap_adsp_amdb_add_static_capi(void);\n\n")

	file_util.write("/*--------------------------------------------------------------------------\n")
	file_util.write(" * Module Definition Structure \n")
	file_util.write(" * -------------------------------------------------------------------------*/\n")
	file_util.write("typedef struct _capi_module_definition_t\n{\n")
	file_util.write("\tuint32_t media_fmt_id;\n")
	file_util.write("\tcapi_getsize_f getsize_f;\n")
	file_util.write("\tcapi_ctor_f ctor_f;\n")
	file_util.write("}capi_module_definition_t;\n\n")
	file_util.write("/*--------------------------------------------------------------------------\n")
	file_util.write(" * Array Of Module Definition For All Custom Static Modules \n")
	file_util.write(" * -------------------------------------------------------------------------*/\n")
	file_util.write("const capi_module_definition_t custom_capi_module_definitions[] =\n{\n")

	# Loop through the number of module times to write CAPI module definition table
	for i in range (len(custom_capi_module_id_name_list)):
		mod_fmt_id_name = custom_capi_module_id_name_list[i] # get the CAPI module format ID name
		mod_fmt_id_name += ","
		mod_fmt_id_name += spaces[0:(50-len(mod_fmt_id_name))] # To maintain alignment
		mod_get_size = custom_capi_module_get_size_api_list[i] # get the get_size API of CAPI module
		mod_get_size += ","
		mod_get_size += spaces[0:(50-len(mod_get_size))] # To maintain alignment
		file_util.write("\t{ " + mod_fmt_id_name) # Write media_fmt_id
		file_util.write(mod_get_size) # Write get_size API name
		file_util.write(custom_capi_module_ctor_api_list[i]) # Write ctor API name
		if (total_num_mod != (i+1)): # Check if the current module is not the last module then write '},'
			file_util.write(" },\n")
		else:
			file_util.write(" }\n")  # if the current module is the last module then write '}'

	file_util.write("};\n\n") # Close the table
	
	# Start creating the "..\inc\custom_adsp_media_fmt.h"
	create_custom_media_fmt_header()

	file_util.write("#endif // #ifdef __CUSTOM_AUDIODECSVC_UTIL_H__ \n")
	file_util.close() # Close the file
	return

#-------------------------------------------------------------------------------------------
# Function		: create_custom_media_fmt_header
# Purpose 		: To create custom_adsp_media_fmt.h in <ROOT>\hap\integration\audencdec\inc
# Description 	: This function creates the above file, to define CAPI module media format IDs
#-------------------------------------------------------------------------------------------
def create_custom_media_fmt_header():
	# Open the file
	file_api = open("../inc/custom_adsp_media_fmt.h","w")
	# Write file header and unchanged text in the begining of the file
	file_api.write("/**\n"+"\tAuto Generated File\n\tFile: custom_adsp_media_fmt.h\n\n"+"\tHeader file for adding custom static modules into database.\n")
	file_api.write("\tcustom_capi_integration.py in <ROOT>\hap\integration\\audencdec\\build\n")
	file_api.write("\twill generate this file when OEM_ROOT is defined."+"\n*/\n\n")
	file_api.write("/* =======================================================================\n\n")
	file_api.write("Copyright (c) 2013 QUALCOMM, Incorporated.  All Rights Reserved.\n")
	file_api.write("QUALCOMM Proprietary.  Export of this technology or software is regulated\n")
	file_api.write("by the U.S. Government, Diversion contrary to U.S. law prohibited.\n")
	file_api.write("\n==========================================================================*/\n")
	file_api.write("#ifndef __CUSTOM_ADSP_MEDIA_FMAT_H__\n")
	file_api.write("#define __CUSTOM_ADSP_MEDIA_FMAT_H__\n")

	# Write comments for defining Media Format IDs
	file_api.write("\n/**\n * " + "Define Media format ID for the custom static CAPI modules.\n")
	file_api.write(" * To acquire range of unique Media format ID's, email support.cdmatech@qualcomm.com\n" + " */\n")

	spaces = "                                                  "
	# Loop through number of modules times in 'custom_capi_module_id_name_list' to define each module Media Format ID
	for i in range(len(custom_capi_module_id_name_list)):
		mod_fmt_id_name = custom_capi_module_id_name_list[i] # get the module media foramt ID name
		mod_fmt_id_name += spaces[0:(40-len(custom_capi_module_id_name_list[i]))] # To maintain alignment
		file_api.write("#define " + mod_fmt_id_name + custom_capi_module_id_value_list[i] + "\n") # write the media format ID name and value

	file_api.write("\n\n#endif // #ifdef __CUSTOM_ADSP_MEDIA_FMAT_H__ \n")
	file_api.close() # Close the file
	return
