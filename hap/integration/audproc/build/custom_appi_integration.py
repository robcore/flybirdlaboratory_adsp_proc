#===========================================================================================
#
# Custom APPI Integration
#
# GENERAL DESCRIPTION
#    If OEM_ROOT is set, then this script will parse the following xml files and 
#	 generates the required header files in adsp_proc\hap\integration\audproc\inc\ 
#       1) custom_static_appi_modules.xml
#       2) custom_static_topologies.xml
#       3) qualcomm_static_appi_modules.xml
#
# Copyright (c) 2013 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------------------
#
#  $Header: 
#  $Date  : 2013/04/10 $
#  $Author: coresvc $
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------------------
# 04/10/13   DS      Create APPI integration
# 06/28/13   DS		 Updated to insert error checks to report proper error to 
#					 the user
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
custom_appi_module_id_name_list = [] 		#Global list, To store Custom Module ID names
custom_appi_module_id_value_list = [] 		#Global list, To store Custom Module ID values
custom_appi_module_header_list = []			#Global list, To store Custom Module APPI header file names
custom_appi_module_kcps_var_name_list = []	#Global list, To store Custom Module KCPS variable names
custom_appi_module_kcps_var_value_list = []	#Global list, To store Custom Module KCPS values

# Custom Topologies Global lists
custom_topo_id_name_list = []				#Global list, To store Topology ID names
custom_topo_id_value_list = []				#Global list, To store Topology ID values
custom_topo_type_list = []					#Global list, To store Topology types
custom_topo_def_name_list = []				#Global list, To store Topology definition structure name
modules_in_custom_topo_list = []			#Global list, To store Module ID's in a topology
mod_info_table_name_in_custom_topo_list = []

# Qualcomm Modules Global Lists
qc_module_id_name_list = []					#Global list, To store Qualcomm Module ID names
qc_module_id_value_list = []				#Global list, To store Qualcomm Module ID values
qc_module_info_name_list = []				#Global list, To store Qualcomm Module Defintions Structure name
qc_module_is_lpm_list = []					#Global list, To store Qualcomm Module is_lpm flag
qc_module_init_params_list = []				#Global list, To store Qualcomm Module initialization parameters

global_mod_count = 0
#-------------------------------------------------------------------------------------------
# Function definitions
#-------------------------------------------------------------------------------------------
def exists(env):
	return env.Detect('custom_appi_integration')

def generate(env):
	env.AddMethod(create_static_appi_modules, "CreateStaticAPPIModules")
	env.AddMethod(create_static_topologies, "CreateStaticTopologies")
	return

#import pdb; pdb.set_trace()

#-------------------------------------------------------------------------------------------
# Function		: create_static_appi_modules
# Purpose 		: To create custom static modules definition table with module ID, get_size 
#				  and init API's name.
#				  To update Qualcomm staic modules lists.
#				  To create the KCPS lookup table for all existing custom static APPI modules
# Description 	: This function parse the custom_static_appi_modules.xml and 
#				  qualcomm_static_appi_modules.xml files located in 
#				  <ROOT>\hap\integration\audproc\config and creates the custom and qualcomm 
#				  static module tables in auto generated file "custom_audproc_db_if.h"
#-------------------------------------------------------------------------------------------
def create_static_appi_modules(env):
	if env.GetOption('clean'):
		return

	# Open XML document using minidom parser
	DOMTree = xml.dom.minidom.parse("../config/custom_static_appi_modules.xml")
	static_modules = DOMTree.documentElement

	#First create ../inc folder to generate required header files
	inc_path = "../inc"
	if not os.path.exists(inc_path):
		os.makedirs(inc_path)

	# Open "custom_audproc_db_if.h" file in write mode to create custom static modules table
	file_db = open("../inc/custom_audproc_db_if.h","w")

	file_db.write("/**\n"+"\tAuto Generated File\n\tFile: custom_audproc_db_if.h\n\n"+"\tHeader file contains all the modules and topologies information.\n")
	file_db.write("\tcustom_appi_integration.py in <ROOT>\hap\integration\\audproc\\build\n")
	file_db.write("\twill generate this file when OEM_ROOT is defined."+"\n*/\n\n")
	file_db.write("/*==========================================================================\n")
	file_db.write("Copyright (c) 2013 QUALCOMM, Incorporated.  All Rights Reserved.\n")
	file_db.write("QUALCOMM Proprietary.  Export of this technology or software is regulated\n")
	file_db.write("by the U.S. Government, Diversion contrary to U.S. law prohibited.\n")
	file_db.write("\n==========================================================================*/\n")
	file_db.write("#ifndef __CUSTOM_AUDPROC_DB_IF_H__\n")
	file_db.write("#define __CUSTOM_AUDPROC_DB_IF_H__\n\n")
	file_db.write("/*--------------------------------------------------------------------------\n")
	file_db.write(" * Includes \n")
	file_db.write(" * -------------------------------------------------------------------------*/\n")
	file_db.write("#include \"custom_audproc_appi_topo.h\"\n\n")
	file_db.write("/*--------------------------------------------------------------------------\n")
	file_db.write(" * Module Definition Structure \n")
	file_db.write(" * -------------------------------------------------------------------------*/\n")
	file_db.write("typedef struct _module_definition_t\n{\n")
	file_db.write("\tuint32_t module_id;\n")
	file_db.write("\tappi_getsize_f getsize_f;\n")
	file_db.write("\tappi_init_f init_f;\n")
	file_db.write("}module_definition_t;\n\n")
	file_db.write("/*--------------------------------------------------------------------------\n")
	file_db.write(" * Array Of Module Definition For All Custom Static Modules \n")
	file_db.write(" * -------------------------------------------------------------------------*/\n")
	file_db.write("const module_definition_t audproc_custom_module_definitions[] =\n{\n")

	# Check for the availability of 'num_modules' attribute
	if static_modules.hasAttribute("num_modules"):
		# Print the total number of modules attribute
		print "\n\nNumber of custom static modules : %s" % static_modules.getAttribute("num_modules")
	else:
		# If 'num_modules' attribute is not available, then print ERROR message and return
		frameinfo = getframeinfo(currentframe())
		print "\nERROR: Please add 'num_modules' attribute to static_modules element in custom_static_appi_modules.xml file	",(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
		return

	# Number of modules that are going to be added to AMDB
	num_modules = static_modules.getAttribute("num_modules")

	# Get all the modules in the static_modules.xml
	modules = static_modules.getElementsByTagName("module")

	# Total number of modules
	total_num_mod = int(num_modules, base=10) # Convert the string into integer

	cur_mod_num = 0 # current module number, initialized to zero
	spaces = "                                                  " # spaces to maintain alignment while writing the varibles in files
	
	# Print details of each module and write into the header file "custom_audproc_db_if.h"
	print "\n********** Custom Static Modules **********"
	
	# Loop through the number of module times to create table for all custom static APPI modules
	for module in modules:
		cur_mod_num += 1 # increment the current module number by 1
		if (module.getAttribute("type") == 'APPI'): # if the current module is APPI module then generate the APPI module information

			# Read the mod_id_name in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_id_name')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				# Append "ERROR" to custom_appi_module_id_name_list for checking the all valid entries in create_static_topologies function
				custom_appi_module_id_name_list.append("ERROR")
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_id_name' of module (%d) in custom_static_appi_modules.xml file		" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				module_id_name = module.getElementsByTagName('mod_id_name')[0]
				if(module_id_name.childNodes):
					module_id_name = module_id_name.childNodes[0].data
					module_id_name = module_id_name.strip() # Remove '\n'
					module_id_name = module_id_name.upper() # Keep the module name in upper case.
					custom_appi_module_id_name_list.append(module_id_name) # Append the module ID of the current module to 'custom_appi_module_id_name_list'
					print "Module Name\t\t:", module_id_name
				else:
					# If the childnodes are not there, print ERROR message and return
					# Append "NONE" to custom_appi_module_id_name_list for checking the values of the tag name in create_static_topologies function
					custom_appi_module_id_name_list.append("NONE")
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module ID name for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_id_value in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_id_value')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				# Append "ERROR" to custom_appi_module_id_value_list for checking the all valid entries in create_static_topologies function
				custom_appi_module_id_value_list.append("ERROR")
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_id_value' in custom_static_appi_modules.xml file for module (%d)	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				module_id_value = module.getElementsByTagName('mod_id_value')[0]
				if(module_id_value.childNodes):
					module_id_value = module_id_value.childNodes[0].data
					module_id_value = module_id_value.strip() # Remove '\n'
					custom_appi_module_id_value_list.append(module_id_value) # Append the current module ID to 'custom_appi_module_id_value_list'
					print "Module ID Value\t\t:", module_id_value
				else:
					# If the childnodes are not there, print ERROR message and return
					# Append "NONE" to custom_appi_module_id_value_list for checking the values of the tag name in create_static_topologies function
					custom_appi_module_id_value_list.append("NONE")
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module ID value for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_appi_header_file in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_appi_header_file')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				# Append "ERROR" to custom_appi_module_header_list for checking the all valid entries in create_static_topologies function
				custom_appi_module_header_list.append("ERROR")
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_appi_header_file' in custom_static_appi_modules.xml file for module (%d)	" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				appi_header_file = module.getElementsByTagName('mod_appi_header_file')[0]
				if(appi_header_file.childNodes):
					appi_header_file_name = appi_header_file.childNodes[0].data
					appi_header_file_name = appi_header_file_name.strip() # Remove '\n'
					custom_appi_module_header_list.append(appi_header_file_name) # Append the current module APPI header file to 'custom_appi_module_header_list'
					print "APPI Header File \t:", appi_header_file_name
					print "\n"
				else:
					# If the childnodes are not there, print ERROR message and return
					# Append "NONE" to custom_appi_module_header_list for checking the values of the tag name in create_static_topologies function
					custom_appi_module_header_list.append("NONE")
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module header file name for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Generate the kcps variable name of the current module in 'module' using 'module_id_name'
			# If module name starts with ASM_MODULE_ID_ or ADM_MODULE_ID_ then eliminate this starting string and use the remaining string for mod_kcps_var_name
			if ((module_id_name.startswith('ASM_MODULE_ID_')) or (module_id_name.startswith('ADM_MODULE_ID_'))):
				mod_kcps_var_name = module_id_name[14:len(module_id_name)]
			# If module name starts with AUDPROC_MODULE_ID_ then eliminate this starting string and use the remaining string for mod_kcps_var_name
			elif (module_id_name.startswith('AUDPROC_MODULE_ID_')):
				mod_kcps_var_name = module_id_name[18:len(module_id_name)]
			# If module name doesnt contain the above strings then use the given module name for mod_kcps_var_name
			else:
				mod_kcps_var_name = module_id_name

			# Update the 'mod_kcps_var_name' and add it to the list 'custom_appi_module_kcps_var_name_list'
			mod_kcps_var_name = mod_kcps_var_name.upper()
			custom_appi_module_kcps_var_name_list.append(mod_kcps_var_name)

			# Read the mod_kcps_value in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_kcps_value')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				# Append "ERROR" to custom_appi_module_kcps_var_value_list for checking the all valid entries in create_static_topologies function
				custom_appi_module_kcps_var_value_list.append("ERROR")
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_kcps_value' in custom_static_appi_modules.xml file for module (%d)		" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				module_kcps_value = module.getElementsByTagName('mod_kcps_value')[0]
				if(module_kcps_value.childNodes):
					module_kcps_value = module_kcps_value.childNodes[0].data
					module_kcps_value = module_kcps_value.strip() # Remove '\n'
					custom_appi_module_kcps_var_value_list.append(module_kcps_value) # append the KCPS value to 'custom_appi_module_kcps_var_value_list'
				else:
					# If the childnodes are not there, print ERROR message and return
					# Append "NONE" to custom_appi_module_kcps_var_value_list for checking the values of the tag name in create_static_topologies function
					custom_appi_module_kcps_var_value_list.append("NONE")
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module KCPS value for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_get_size_f in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_get_size_f')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_get_size_f' in custom_static_appi_modules.xml file for module (%d)		" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				get_size_f = module.getElementsByTagName('mod_get_size_f')[0]
				if(get_size_f.childNodes):
					mod_get_size = get_size_f.childNodes[0].data
					mod_get_size = mod_get_size.strip() # Remove '\n'
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module get_size API name for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Read the mod_init_f in 'module'
			# Check for the correct tag name
			if(len(module.getElementsByTagName('mod_init_f')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'mod_init_f' in custom_static_appi_modules.xml file for module (%d)		" %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				init_f = module.getElementsByTagName('mod_init_f')[0]
				if(init_f.childNodes):
					mod_init = init_f.childNodes[0].data
					mod_init = mod_init.strip() # Remove '\n'
				else:
					# If the childnodes are not there, print ERROR message and return
					frameinfo = getframeinfo(currentframe()) # to print line number and file name
					print "ERROR: Enter APPI Module init API name for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
					return

			# Create 'audproc_custom_module_definitions' table in "custom_audproc_db_if.h"
			module_id_name += "," # append ',' to the current APPI module name
			module_id_name += spaces[0:(50-len(module_id_name))] # To maintain alignment
			mod_get_size += "," # append ',' to the current APPI module get size API name
			mod_get_size += spaces[0:(50-len(mod_get_size))] # To maintain alignment
			file_db.write("\t{ " + module_id_name) # Write module_id
			file_db.write(mod_get_size) # Write get_size API name
			file_db.write(mod_init) # Write init API name
			if (total_num_mod != cur_mod_num): # if the current module is not the last module then write '},'
				file_db.write(" },\n")
			else:
				file_db.write(" }\n")  # if the current module is the last module then write '}'
		else:
			# If the module type is not APPI, print ERROR message and return
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter Module type or specify the type as 'APPI' for module (%d) in custom_static_appi_modules.xml file " %cur_mod_num,	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return


	file_db.write("};\n\n") # Close the table

	# Check the total number of modules updated correctly
	# Print ERROR message when 'num_modules' is not greater or equal to 'cur_mod_num'(actual modules adding to AMDB)
	if(total_num_mod < cur_mod_num):
		frameinfo = getframeinfo(currentframe()) # to print line number and file name
		print "ERROR: Update the 'num_modules' attribute of 'static_modules' correctly with total number of modules",	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
	elif(total_num_mod > cur_mod_num):
		frameinfo = getframeinfo(currentframe()) # to print line number and file name
		print "WARNING: Update the 'num_modules' attribute of 'static_modules' correctly with total number of modules",	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
	
	# Start parsing the quaclomm_static_modules.xml and generate the only module information tables for Qualcomm modules
	# Open XML document using minidom parser
	DOMTree = xml.dom.minidom.parse("../config/qualcomm_static_appi_modules.xml")
	qc_static_appi_modules = DOMTree.documentElement

	# Print the Number of modules attribute, if it is available for 'qc_static_appi_modules' element
	if qc_static_appi_modules.hasAttribute("num_modules"):
		print "\n\nNumber of Qualcomm static modules : %s" % qc_static_appi_modules.getAttribute("num_modules")

	# Number of modules that are going to be added to AMDB
	num_modules = qc_static_appi_modules.getAttribute("num_modules")

	# Get all the modules in the qc_static_appi_modules.xml
	qualocomm_modules = qc_static_appi_modules.getElementsByTagName("module")

	# Total number of modules
	total_num_mod = int(num_modules, base=10) # Convert the string into integer

	cur_mod_num = 0
	spaces = "                                                  "
	# Print details of each module and write into the header file "custom_audproc_db_if.h"
	print "\n********** Qualcomm Static Modules **********"
	# Loop through the number of module times to create table all custom static modules
	for qc_module in qualocomm_modules:
		if (qc_module.getAttribute("type") == 'APPI'): # if the current module is APPI module then generate the APPI module information
			# current module number
			cur_mod_num += 1

			# Read the module_id of the current module ID name in 'module'
			qc_module_id_name = qc_module.getElementsByTagName('mod_id_name')[0]
			qc_mod_id_name = qc_module_id_name.childNodes[0].data
			qc_mod_id_name = qc_mod_id_name.strip() # Remove '\n'
			qc_mod_id_name = qc_mod_id_name.upper() # Keep the module name in upper case.
			qc_module_id_name_list.append(qc_mod_id_name) # Append the current module name to 'qc_module_id_name_list'
			print "Module Name\t\t:", qc_mod_id_name

			# Read the module_id of the current module ID value in 'module'
			qc_module_id_value = qc_module.getElementsByTagName('mod_id_value')[0]
			qc_mod_id_value = qc_module_id_value.childNodes[0].data
			qc_mod_id_value = qc_mod_id_value.strip() # Remove '\n'
			qc_module_id_value_list.append(qc_mod_id_value) # Append the current module ID to 'qc_module_id_value_list'
			print "Module ID Value\t\t:", qc_mod_id_value
			print "\n"

	# Start writing all custom static modules KCPS information in "custom_audproc_db_if.h"
	# Write KCPS lookup table structure declration
	file_db.write("/*--------------------------------------------------------------------------\n")
	file_db.write(" * KCPS lookup table structure \n")
	file_db.write(" * -------------------------------------------------------------------------*/\n")
	file_db.write("struct CUSTOM_KCPS_LUT_t\n{\n\t")
	file_db.write("uint32_t module_id;\n\t")
	file_db.write("uint32_t KCPS;\n};\n")

	# Write KCPS names and values of all custom static modules
	file_db.write("\n")
	file_db.write("/*\n")
	file_db.write(" * KCPS lookup table for all custom static audio processing modules\n")
	file_db.write(" */\n")
	file_db.write("static const CUSTOM_KCPS_LUT_t Custom_KCPS_info[] =\n{\n")
	# Loop through the number of modules in 'custom_appi_module_id_name_list' to update KCPS lookup table for each module
	for i in range (len(custom_appi_module_id_name_list)):
		module_name = custom_appi_module_id_name_list[i]
		module_name += ","
		module_name += spaces[0:(50-len(module_name))] # To maintain alignment
		if (i == (len(custom_appi_module_id_name_list)-1)):
			# If current module number is total number of modules write '}' at the end
			file_db.write("\t{ " + module_name + "KCPS_" + custom_appi_module_kcps_var_name_list[i] + " }\n")
		else:
			# If current module number is not total number of modules write '},' at the end
			file_db.write("\t{ " + module_name + "KCPS_" + custom_appi_module_kcps_var_name_list[i] + " },\n")

	file_db.write("};\n\n") # close the table

	file_db.close() # close the file

	# Start creating the "..\inc\custom_audproc_appi_topo.h"
	create_custom_appi_topo_header()
	return


#-------------------------------------------------------------------------------------------
# Function		: create_static_topologies
# Purpose 		: To create custom static topologies table and each type of topology with 
#				  topology definition names
# Description 	: This function parse the custom_static_topologies.xml file located in 
#				  <ROOT>\hap\integration\audproc\config and creates the custom static 
#				  topologies definition tables and custom static topologies for each type with 
#				  topology definition names in newly generated file "custom_audproc_db_if.h"
#				  This function also generates the module information table for each modules 
#				  that is added in current topology
#-------------------------------------------------------------------------------------------
def create_static_topologies(env):
	if env.GetOption('clean'):
		return

	# Check values of tag names for all required lists, if any list not having a value for a tag name then print ERROR message and return
	# Check 'mod_id_name' tag name values in 'custom_appi_module_id_name_list'
	for i in range(len(custom_appi_module_id_name_list)):
		if(custom_appi_module_id_name_list[i] == 'NONE'):
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter APPI Module ID name for module (%d) in custom_static_appi_modules.xml file " %(i+1),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return
	
	# Check 'mod_id_value' tag name values in 'custom_appi_module_id_value_list'
	for i in range(len(custom_appi_module_id_value_list)):
		if(custom_appi_module_id_value_list[i] == 'NONE'):
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter APPI Module ID value for module (%d) in custom_static_appi_modules.xml file " %(i+1),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return

	# Check 'mod_appi_header_file' tag name values in 'custom_appi_module_header_list'
	for i in range(len(custom_appi_module_header_list)):
		if(custom_appi_module_header_list[i] == 'NONE'):
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter APPI Module header file name for module (%d) in custom_static_appi_modules.xml file " %(i+1),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return

	# Check 'mod_kcps_value' tag name values in 'custom_appi_module_kcps_var_value_list'
	for i in range(len(custom_appi_module_kcps_var_value_list)):
		if(custom_appi_module_kcps_var_value_list[i] == 'NONE'):
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Enter APPI Module KCPS value for module (%d) in custom_static_appi_modules.xml file " %(i+1),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return

	# Check all the required lists are having valid tag names, if any list having a wrong tag name then print ERROR message and return
	for i in range(len(custom_appi_module_id_name_list)):
		if((custom_appi_module_id_name_list[i] == 'ERROR') or (custom_appi_module_id_value_list[i] == 'ERROR') or (custom_appi_module_header_list[i] == 'ERROR') or (custom_appi_module_kcps_var_value_list[i] == 'ERROR')):
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Check the tag names of module (%d) in custom_static_appi_modules.xml file		" %(i+1),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return

	# Open XML document using minidom parser
	DOMTree = xml.dom.minidom.parse("../config/custom_static_topologies.xml")
	static_topologies = DOMTree.documentElement

	# Open "custom_audproc_db_if.h" file in append mode to add custom static topologies
	file_db = open("../inc/custom_audproc_db_if.h","a")

	# Check for the availability of 'num_topologies' attribute
	if static_topologies.hasAttribute("num_topologies"):
		# Print the total number of topologies
		print "\n\nNumber of custom static topologies : %s" % static_topologies.getAttribute("num_topologies")

	# Get all the Topologies in the static_topologies.xml
	Topologies = static_topologies.getElementsByTagName("topology")

	popp_type_count = 0 	# number of POPP topology types
	poprep_type_count = 0 	# number of POPREP topology types
	copp_type_count = 0 	# number of COPP topology types
	coprep_type_count = 0	# number of COPREP topology types
	main_loop_count = 1		# loop count used to get 'modules_in_topo' child from 'topology'

	# Print details of each topology and write into the header file
	print "\n********** Custom Static Topologies **********"
	
	# Loop through the number of topology times to create topology definitions
	for Topology in Topologies:
		# Read the topology_id_name in 'Topology'
		# Check for the correct tag name
		if(len(Topology.getElementsByTagName('topology_id_name')) == 0):
			# If the above tag name not found in the element, print ERROR message and return
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Check the tag name 'topology_id_name' of topology (%d) in custom_static_topologies.xml file	" %main_loop_count,(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return
		else:
			topology_id_name = Topology.getElementsByTagName('topology_id_name')[0]
			static_topology_name = topology_id_name.childNodes[0].data
			static_topology_name = static_topology_name.strip() # Remove '\n'
			static_topology_name = static_topology_name.upper() # Keep the topology name in upper case
			custom_topo_id_name_list.append(static_topology_name) # append the topology id name to 'custom_topo_id_name_list
			print "Topology ID Name\t:", static_topology_name

		# Read the topology_id_value in 'Topology'
		# Check for the correct tag name
		if(len(Topology.getElementsByTagName('topology_id_value')) == 0):
			# If the above tag name not found in the element, print ERROR message and return
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Check the tag name 'topology_id_value' of topology (%d) in custom_static_topologies.xml file	" %main_loop_count,(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return
		else:
			topology_id_value = Topology.getElementsByTagName('topology_id_value')[0]
			static_topology_value = topology_id_value.childNodes[0].data
			static_topology_value = static_topology_value.strip() # Remove '\n'
			custom_topo_id_value_list.append(static_topology_value) # append the topology id value to 'custom_topo_id_value_list
			print "Topology ID Value\t:", static_topology_value

		# Update the counter of each topology type depending on the current topology type
		if Topology.hasAttribute("type"):
			topo_type = Topology.getAttribute("type")
			print "Topology Type \t\t:", topo_type
			if (topo_type == "POPP"):
				popp_type_count += 1
			elif(topo_type == "POPREP"):
				poprep_type_count += 1
			elif(topo_type == "COPP"):
				copp_type_count += 1
			elif(topo_type == "COPREP"):
				coprep_type_count += 1
		else:
			# If 'type' attribute was not specified in 'topology' then the current topology will be added under POPP chain
			print "\nTYPE is not specified for this topology, default topology type is POPP\n"
			topo_type = "POPP"
			popp_type_count += 1
		# Append the topology type to the 'custom_topo_type_list'
		custom_topo_type_list.append(topo_type)

		# Read the topology_def_name in 'Topology'
		# Check for the correct tag name
		if(len(Topology.getElementsByTagName('topology_def_name')) == 0):
			# If the above tag name not found in the element, print ERROR message and return
			frameinfo = getframeinfo(currentframe()) # to print line number and file name
			print "ERROR: Check the tag name 'topology_def_name' of topology (%d) in custom_static_topologies.xml file	" %main_loop_count,(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
			return
		else:
			topo_def_name = Topology.getElementsByTagName('topology_def_name')[0]
			static_topo_def_name = topo_def_name.childNodes[0].data
			static_topo_def_name = static_topo_def_name.strip() # Remove '\n'
			custom_topo_def_name_list.append(static_topo_def_name) # Append the topology definition name to 'custom_topo_def_name_list'
			print "\nTopology Def. Struct Name: ", static_topo_def_name
			print "\n\n"

		# Get all the 'modules_in_topo' in 'topology' into 'Modules_In_Topo'
		Modules_In_Topo = DOMTree.documentElement.childNodes[main_loop_count].childNodes[7]
       
		# Get all the APPI modules in "modules_in_topo"
		Modules = Modules_In_Topo.getElementsByTagName("module")
		print "\n\n********** Modules in Custom Static Topologies **********"
		Num_Modules_In_Topo_int = 0
		# Loop through Module times in Modules to read all the Module's information that are present in topology
		loop_count = 1
		
		# Start writing custom module information tables in "custom_audproc_db_if.h"
		file_db.write("/*--------------------------------------------------------------------------\n")
		file_db.write(" * All Static Modules Information Including Qualcomm Modules\n")
		file_db.write(" * -------------------------------------------------------------------------*/\n")
		for Module in Modules:
			# Read the Module_ID in topology
			# Check for the correct tag name
			if(len(Module.getElementsByTagName('module_id')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'module_id' of module (%d) in custom_static_topologies.xml file for topology (%d)	" %(loop_count,main_loop_count),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				mod_id = Module.getElementsByTagName('module_id')[0]
				mod_id = mod_id.childNodes[0].data
				mod_id = mod_id.strip() # Remove '\n'
			
			# If 'mod_id' starts with 0x then search for the current module in 'custom_appi_module_id_value_list' or 'qc_module_id_value_list'
			if(mod_id.startswith('0x')):
				if mod_id in custom_appi_module_id_value_list:
					module_id_value_index = custom_appi_module_id_value_list.index(mod_id)
					modules_in_custom_topo_list.append(custom_appi_module_id_name_list[module_id_value_index]) # List used to print the modules in a topo
					cur_mod_in_topo = custom_appi_module_id_name_list[module_id_value_index] # Variable to store the current module in a topo
					Num_Modules_In_Topo_int += 1
					print "\nModule ID %d\t:" %loop_count, custom_appi_module_id_name_list[module_id_value_index]
				elif mod_id in qc_module_id_value_list:
					qc_module_id_value_index = qc_module_id_value_list.index(mod_id)
					modules_in_custom_topo_list.append(qc_module_id_name_list[qc_module_id_value_index]) # List used to print the modules in a topo
					cur_mod_in_topo = qc_module_id_name_list[qc_module_id_value_index] # Variable to store the current module in a topo
					Num_Modules_In_Topo_int += 1
					print "\nModule ID %d\t:" %loop_count, qc_module_id_name_list[qc_module_id_value_index]
				# If any module added in a topology without adding it to AMDB then print the below message,
				# print the available module names and its ID's
				else:
					print "\nModule ID \"%s\" is not present in the custom_appi_module_id_value_list" %mod_id
					print "\n\n\nAvailable Custom Module Names and Module IDs are:"
					print "-------------------------------------------------------"
					for i in range (len(custom_appi_module_id_name_list)):
						print custom_appi_module_id_name_list[i], "\t", custom_appi_module_id_value_list[i]
					
					print "\n\n\nAvailable Qualcomm Module Names and Module IDs are:"
					print "---------------------------------------------------------"
					for i in range (len(qc_module_id_name_list)):
						print qc_module_id_name_list[i], "\t", qc_module_id_value_list[i]
			# Search for current Module ID in the custom_appi_module_id_name_list, if present then get the index of the current module 
			else:
				if mod_id in custom_appi_module_id_name_list:
					modules_in_custom_topo_list.append(mod_id) # List used to print the modules in a topo
					cur_mod_in_topo = mod_id # Variable to store the current module in a topo
					Num_Modules_In_Topo_int += 1
					print "\nModule ID %d\t:" %loop_count, mod_id
				elif mod_id in qc_module_id_name_list:
					modules_in_custom_topo_list.append(mod_id) # List used to print the modules in a topo
					cur_mod_in_topo = mod_id # Variable to store the current module in a topo
					Num_Modules_In_Topo_int += 1
					print "\nModule ID %d\t:" %loop_count, mod_id
				# If any module added in a topology without adding it to AMDB then print the below message,
				# print the available module names and its ID's
				else:
					print "\nModule ID \"%s\" is not present in the custom_appi_module_id_name_list" %mod_id
					print "\n\n\nAvailable Custom Module Names and Module IDs are:"
					print "-------------------------------------------------------"
					for i in range (len(custom_appi_module_id_name_list)):
						print custom_appi_module_id_name_list[i], "\t", custom_appi_module_id_value_list[i]
					
					print "\n\n\nAvailable Qualcomm Module Names and Module IDs are:"
					print "---------------------------------------------------------"
					for i in range (len(qc_module_id_name_list)):
						print qc_module_id_name_list[i], "\t", qc_module_id_value_list[i]
			
			# Read the 'init_params' for the current Module in topology
			# Check for the correct tag name
			if(len(Module.getElementsByTagName('init_params')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'init_params' of module (%d) in custom_static_topologies.xml file for topology (%d)	" %(loop_count,main_loop_count),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				mod_init_params = Module.getElementsByTagName('init_params')[0]
				mod_init_params = mod_init_params.childNodes[0].data
				mod_init_params = mod_init_params.strip() # Remove '\n'

			# Read the 'is_lpm' flag for the current Module in topology
			# Check for the correct tag name
			if(len(Module.getElementsByTagName('is_lpm')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'is_lpm' of module (%d) in custom_static_topologies.xml file for topology (%d)	" %(loop_count,main_loop_count),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				mod_lpm = Module.getElementsByTagName('is_lpm')[0]
				mod_lpm = mod_lpm.childNodes[0].data
				mod_lpm = mod_lpm.strip() # Remove '\n'

			# Read the 'mod_info_table_name' for the current Module in topology
			# Check for the correct tag name
			if(len(Module.getElementsByTagName('module_info_table_name')) == 0):
				# If the above tag name not found in the element, print ERROR message and return
				frameinfo = getframeinfo(currentframe()) # to print line number and file name
				print "ERROR: Check the tag name 'module_info_table_name' of module (%d) in custom_static_topologies.xml file for topology (%d)		" %(loop_count,main_loop_count),	(frameinfo.lineno+1),	os.path.basename(frameinfo.filename) + "\n"
				return
			else:
				mod_info_table_name = Module.getElementsByTagName('module_info_table_name')[0]
				mod_info_table_name = mod_info_table_name.childNodes[0].data
				mod_info_table_name = mod_info_table_name.strip() # Remove '\n'
				mod_info_table_name_in_custom_topo_list.append(mod_info_table_name)  # append the module information table name to 'mod_info_table_name_in_custom_topo_list'

			# Create 'audproc_module_info_t' table for each module in "custom_audproc_db_if.h"
			file_db.write("/*" + "\n *" + " Module Information For Module ID: " + cur_mod_in_topo + "\n */\n")
			file_db.write("static const audproc_module_info_t " + mod_info_table_name + " =")
			file_db.write("\n{\n" + "\t"+ cur_mod_in_topo +",\n") # Write the Module ID of the current module into the table
			file_db.write("\t"+ mod_lpm +",\n") # Write 'is_lpm' into the table
			file_db.write("\t"+ mod_init_params) # Write 'init_params' into the table
			file_db.write("\n};\n\n") # Close the table
			
			loop_count += 1 # At the end of the loop

		if (main_loop_count == 1): # Write only once
			file_db.write("/*---------------------------------------------------------------------------\n")
			file_db.write(" * Topology Definition Structures For All Custom Static Topologies \n")
			file_db.write(" * -------------------------------------------------------------------------*/\n")

		# Writing the comments for the current topology definition structure
		file_db.write("/*\n *" + " Modules in topology '" + static_topology_name + "' of type " + topo_type + ":\n")
		for i in range (len(modules_in_custom_topo_list)):
			file_db.write(" * " + modules_in_custom_topo_list[i] + "\n" )
		file_db.write(" */\n" )

		# Start writing the topology definition structure name with topology_id, number of modules in topology 
		# and module information table names
		file_db.write("static const audproc_topology_definition_t " + static_topo_def_name + " =")
		file_db.write("\n{" + "\n\t" + static_topology_name + ",\n\t") # Write topology_id into the table
		file_db.write(repr(Num_Modules_In_Topo_int) + ",\n\t{") # Write number of modules in current topology into table
		loop_count = 0
		global  global_mod_count
		# Loop through module times in modules_in_custom_topo_list to write the module information table names
		for mod_count in range (len(modules_in_custom_topo_list)):
			# If the current module is not the last module in topology then write module information table name followed by ','
			if ((Num_Modules_In_Topo_int-1) != loop_count):
				file_db.write("\n\t\t"+ mod_info_table_name_in_custom_topo_list[mod_count+global_mod_count] + ",")
			else:
				file_db.write("\n\t\t"+ mod_info_table_name_in_custom_topo_list[mod_count+global_mod_count])
			loop_count += 1
		global_mod_count = global_mod_count + len(modules_in_custom_topo_list)
		file_db.write("\n\t}")
		file_db.write("\n};\n\n") # Close the table
		len_mod_in_topo_list = len(modules_in_custom_topo_list) # Get the lenght of the modules_in_custom_topo_list
		del modules_in_custom_topo_list[0:len_mod_in_topo_list] # Remove all the elements in modules_in_custom_topo_list
		main_loop_count += 2 # Incrementing the main loop count, to read the next 'Topology' child in 'static_topologies' element

	# Write the custom static POPP topologies
	write_topo_def_table("POPP", popp_type_count, file_db)

	# Write the custom static POPREP topologies
	write_topo_def_table("POPREP", poprep_type_count, file_db)

	# Write the custom static COPP topologies
	write_topo_def_table("COPP", copp_type_count, file_db)

	# Write the custom static COPREP topologies
	write_topo_def_table("COPREP", coprep_type_count, file_db)

	file_db.write('#endif //#ifdef __CUSTOM_AUDPROC_DB_IF_H__ \n')
	file_db.close() # Close the file

	# Start creating the "..\inc\custom_adsp_audproc_api.h"
	define_static_topologies_modules()
	return

#-------------------------------------------------------------------------------------------
# Function		: write_topo_def_table
# Purpose 		: To write custom static topologies table for each type of topology
# Description 	: This function receives the topology type, count of the topoogy type and 
#				  file pointer and write the custom static topology of type(topology type)
#-------------------------------------------------------------------------------------------
def write_topo_def_table(type, type_count, file):
	file.write("/*-------------------------------------------------------------------------- \n")
	file.write(" * Custom Static "+type+" Topologies" + "\n")
	file.write(" *--------------------------------------------------------------------------*/ \n")
	loop_count = 0
	topo_type_count = 0
	file.write("static const audproc_topology_definition_t audproc_custom_static_topos_"+type.lower()+"[] = \n{")
	for topo_type in custom_topo_type_list:
		if (custom_topo_type_list[loop_count] == type):
			topo_type_count += 1
			if (topo_type_count != type_count):
				file.write("\n\t" + custom_topo_def_name_list[loop_count] + ",")
			else:
				file.write("\n\t" + custom_topo_def_name_list[loop_count])
		loop_count += 1
	file.write("\n};\n\n")
	return

#-------------------------------------------------------------------------------------------
# Function		: define_static_topologies_modules
# Purpose 		: To create custom_adsp_audproc_api.h in <ROOT>\hap\integration\audproc\inc
# Description 	: This function creates the above file, to define all the topology IDs and 
#				  Module IDs
#-------------------------------------------------------------------------------------------
def define_static_topologies_modules():
	file_api = open("../inc/custom_adsp_audproc_api.h","w")
	file_api.write("/**\n"+"\tAuto Generated File\n\tFile: custom_adsp_audproc_api.h\n\n"+"\tHeader file for defining the Topology ID's, Module Id's.\n")
	file_api.write("\tcustom_appi_integration.py in <ROOT>\hap\integration\\audproc\\build\n")
	file_api.write("\twill generate this file when OEM_ROOT is defined."+"\n*/\n\n")
	file_api.write("/* =======================================================================\n\n")
	file_api.write("Copyright (c) 2013 QUALCOMM, Incorporated.  All Rights Reserved.\n")
	file_api.write("QUALCOMM Proprietary.  Export of this technology or software is regulated\n")
	file_api.write("by the U.S. Government, Diversion contrary to U.S. law prohibited.\n")
	file_api.write("\n==========================================================================*/\n")
	file_api.write("#ifndef __CUSTOM_ADSP_AUDPROC_API_H__\n")
	file_api.write("#define __CUSTOM_ADSP_AUDPROC_API_H__\n\n")
	file_api.write("/**\n *"+" Custom Static Audio Topologies, Maximum supported topologies: 128\n")
	file_api.write(" * To acquire range of topology ID's, email support.cdmatech@qualcomm.com\n */\n")

	spaces = "                                                  "

	# Loop through the number of topology times to write topology definitions
	for i in range (len(custom_topo_id_name_list)):
		static_topo_name = custom_topo_id_name_list[i] # get the custom topology id name
		static_topo_id = custom_topo_id_value_list[i] # get the custom topology id value
		static_topo_name += spaces[0:(50-len(static_topo_name))] # To maintain alignment
		file_api.write("#define " + static_topo_name + "\t\t" + static_topo_id + "\n") # write custom topology id name and value into header file

	# Write comments for defining Module IDs
	file_api.write("\n/**\n * " + "Define Module ID for the custom static audio processing modules.\n")
	file_api.write(" * Define Param ID  for the processing modules in respective APPI header file.\n")
	file_api.write(" * Param IDs are needed by unit testing also hence these values need to be defined in the\n")
	file_api.write(" * APPI header file.\n")
	file_api.write(" * To acquire range of unique Module ID's and Param ID's, email support.cdmatech@qualcomm.com\n" + " */\n")

	# Loop through the number of module times to write module definitions
	for i in range (len(custom_appi_module_id_name_list)):
		static_mod_name = custom_appi_module_id_name_list[i] # get the custom module id name
		static_mod_id = custom_appi_module_id_value_list[i] # get the custom module id value
		static_mod_name += spaces[0:(50-len(static_mod_name))] # To maintain alignment
		file_api.write("#define " + static_mod_name + "\t\t" + static_mod_id + "\n")

	file_api.write("\n\n#endif // #ifdef __CUSTOM_ADSP_AUDPROC_API_H__ \n")
	file_api.close() # Close the file
	return

#-------------------------------------------------------------------------------------------
# Function		: create_custom_appi_topo_header
# Purpose 		: To create custom_audproc_appi_topo.h in <ROOT>\hap\integration\audproc\inc
# Description 	: This function creates the above file, to include module APPI header files 
#				  and to add modules KCPS information
#-------------------------------------------------------------------------------------------
def create_custom_appi_topo_header():
	# Open the file
	file_appi_topo = open("../inc/custom_audproc_appi_topo.h","w")
	# Write file header and unchanged text in the begining of the file
	file_appi_topo.write("/**\n"+"\tAuto Generated File\n\tFile: custom_audproc_appi_topo.h\n\n"+"\tHeader file for adding custom static modules into database.\n")
	file_appi_topo.write("\tcustom_appi_integration.py in <ROOT>\hap\integration\\audproc\\build\n")
	file_appi_topo.write("\twill generate this file when OEM_ROOT is defined."+"\n*/\n\n")
	file_appi_topo.write("/* =======================================================================\n\n")
	file_appi_topo.write("Copyright (c) 2013 QUALCOMM, Incorporated.  All Rights Reserved.\n")
	file_appi_topo.write("QUALCOMM Proprietary.  Export of this technology or software is regulated\n")
	file_appi_topo.write("by the U.S. Government, Diversion contrary to U.S. law prohibited.\n")
	file_appi_topo.write("\n==========================================================================*/\n")
	file_appi_topo.write("#ifndef __CUSTOM_AUDPROC_APPI_TOPO_H__\n")
	file_appi_topo.write("#define __CUSTOM_AUDPROC_APPI_TOPO_H__\n\n")
	file_appi_topo.write("/*------------------------------------------------------------------------\n")
	file_appi_topo.write(" * Includes\n")
	file_appi_topo.write(" *------------------------------------------------------------------------*/\n")
	file_appi_topo.write("#include \"audproc_topology_db.h\"\n")
	file_appi_topo.write("#include \"AudDynaPPSvc.h\"\n")
	file_appi_topo.write("#include \"adsp_amdb_static.h\"\n\n")
	file_appi_topo.write("/*------------------------------------------------------------------------\n")
	file_appi_topo.write(" * Include files of APPI modules\n")
	file_appi_topo.write(" *------------------------------------------------------------------------*/\n")

	# Loop through the number of module times to include module APPI header file
	for i in range (len(custom_appi_module_header_list)):
		file_appi_topo.write("#include " + "\"" + custom_appi_module_header_list[i] + "\"" + "\n")

	# Write the two APIs declarations
	file_appi_topo.write("\n")
	file_appi_topo.write("/*------------------------------------------------------------------------\n")
	file_appi_topo.write(" * Function Declarations\n")
	file_appi_topo.write(" *------------------------------------------------------------------------*/\n")
	file_appi_topo.write(" ADSPResult hap_AddCustomStaticTopologiesAndModules(void);\n")
	file_appi_topo.write(" uint32_t hap_topo_init_get_custom_KCPS(const uint32_t module_id);\n")

	# Write Add module KCPS information
	file_appi_topo.write("\n")
	file_appi_topo.write("/*------------------------------------------------------------------------\n")
	file_appi_topo.write(" * Define KCPS of custom static APPI module\n")
	file_appi_topo.write(" *------------------------------------------------------------------------*/\n")

	spaces = "                                                  "
	# Loop through number of modules times in 'custom_appi_module_kcps_var_name_list' to define each module KCPS value
	for i in range(len(custom_appi_module_kcps_var_name_list)):
		mod_kcps_var_name = "KCPS_" + custom_appi_module_kcps_var_name_list[i]
		mod_kcps_var_name += spaces[0:(40-len(mod_kcps_var_name))] # To maintain alignment
		file_appi_topo.write(" static const uint32_t " + mod_kcps_var_name + " = " + custom_appi_module_kcps_var_value_list[i] + ";\n")

	file_appi_topo.write("\n\n#endif // #ifdef __CUSTOM_AUDPROC_APPI_TOPO_H__ \n")
	file_appi_topo.close() # Close the file
	return
