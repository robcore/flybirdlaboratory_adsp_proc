#==============================================================================
# SCONS Tool for Target-Specific Build Parameters.
#
# Copyright (c) 2012-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#==============================================================================
#==============================================================================
#
#                        EDIT HISTORY FOR MODULE
#
# $Header: //components/rel/core.adsp/2.6.1/bsp/build/tbc_core_devcfg.py#1 $
#
# when       who    what, where, why
# -------    ---    -------------------------------------------
# 08/14/12   aa   Initial Revision
#==============================================================================
import xml.dom.minidom
import unicodedata

def get_devcfg_xml_tags(env, xml_file):
   '''
   Get the devcfg tags that the clients need to use to pass in the xml information
   for different configurations by reading it from build\ms\image_cfg.xml
   '''
   xml_file = env.RealPath(xml_file)
   # parse the xml file
   image_cfg_tag = xml.dom.minidom.parse(xml_file)
   # Get the devcfg_info elements
   devcfginfotags = image_cfg_tag.getElementsByTagName("devcfg_info")
   # Get devcfg_xml_tag's elements, which has the xml tags in it that is required here
   if env.GetUsesFlag('USES_DEVCFG_MULTIPLE_CONFIG'):
      devcfgxmlelems = devcfginfotags[0].getElementsByTagName("devcfg_xml_tag_multiple_configs")
   else:
      devcfgxmlelems = devcfginfotags[0].getElementsByTagName("devcfg_xml_tag_single_config")
   # This will have only one child of devcfg_xml_tag type. It returns a unicode type data
   udata = devcfgxmlelems[0].firstChild.data
   # Convert it to string
   devcfg_xml_tags = unicodedata.normalize('NFKD', udata).encode('ascii','ignore')
   # Remove any \t, \n in the string and split it with demiliter ',' to give a list of the tags
   devcfg_xml_tag_list = (devcfg_xml_tags.replace('\t', '').replace('\n', '')).split(',')
   # Remove any spaces in the list elements
   devcfg_xml_tag_list = [word.strip() for word in devcfg_xml_tag_list]
   
   #import pdb;pdb.set_trace()
   # Get chipinfo(family number, device number) for all exposed tags, the values are defined in ipcat
   # description for TCSR_SOC_HW_VERSION register for all supported chipset in a family
   devcfgchipelems = devcfginfotags[0].getElementsByTagName("soc_hw_version")
   soc_data = devcfgchipelems[0].firstChild.data
   devcfg_soc_tags = unicodedata.normalize('NFKD', soc_data).encode('ascii','ignore')
   devcfg_soc_tag_list = (devcfg_soc_tags.replace('\t', '').replace('\n', '')).split(',')
   devcfg_soc_tag_list = [word.strip() for word in devcfg_soc_tag_list]
   devcfg_soc_tag_dict = {}
   for element in devcfg_soc_tag_list :
      val = element.split(':')
      devcfg_soc_tag_dict.setdefault(val[0].strip(),[]).append(val[1].strip())
   
   #Get the TCSR_SOC_HW_VERSION ADDRESS, the value is defined in ipcat and is fixed for a family
   tcsr_hw_version_addr_node = devcfginfotags[0].getElementsByTagName("tcsr_soc_hw_version_addr")
   tcsr_hw_version_addr = tcsr_hw_version_addr_node[0].firstChild.data
   tcsr_hw_version_addr = unicodedata.normalize('NFKD', tcsr_hw_version_addr).encode('ascii','ignore')
   tcsr_hw_version_addr = tcsr_hw_version_addr.strip()
   return devcfg_xml_tag_list, devcfg_soc_tag_dict, tcsr_hw_version_addr

def generate(env):
   #---------------------------------------------------------------------------
   # Add Device Configuration specific defines
   #---------------------------------------------------------------------------
   # Reason for doing this is because python does 
   # not like the 'x' in targets like '9x15'
   if env['MSM_ID'] in ['8974']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x${MSM_ID}')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8974/image_cfg.xml"
   elif env['MSM_ID'] in ['8994']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8994')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8994/image_cfg.xml"
   elif env['MSM_ID'] in ['8996']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8996')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8996/image_cfg.xml"
   elif env['MSM_ID'] in ['9x25']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x9025')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/mdm9x25/image_cfg.xml"	  
   elif env['MSM_ID'] in ['8x26']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8626')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8x26/image_cfg.xml"
   elif env['MSM_ID'] in ['8092']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8092')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/mpq8092/image_cfg.xml"
   elif env['MSM_ID'] in ['8x10']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8010') 	  
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8x10/image_cfg.xml"
   elif env['MSM_ID'] in ['8094']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8094')	  
      multi_config_xml = "${BUILD_ROOT}/build/chipset/apq8094/image_cfg.xml"
   elif env['MSM_ID'] in ['8084']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8084')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/apq8084/image_cfg.xml"
   elif env['MSM_ID'] in ['9x35']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x9635')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/mdm9x35/image_cfg.xml"
      if 'USES_MEMOPT' in env['USES_FLAGS_CL']:
         multi_config_xml = "${BUILD_ROOT}/build/chipset/mdm9x35MEMOPT/image_cfg.xml"
   elif env['MSM_ID'] in ['8962']:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x8962')
      multi_config_xml = "${BUILD_ROOT}/build/chipset/msm8962/image_cfg.xml"		  
   else:
      env.Replace(DAL_CONFIG_TARGET_ID = '0x${MSM_ID}')
      raise Exception("Dev Config XML to parse configuration tags not found for 0x${MSM_ID}")

   devcfg_xml_tag_list, devcfg_soc_tag_dict, tcsr_hw_version_addr = get_devcfg_xml_tags(env, multi_config_xml)
   # Create the preprocess tag list to be used in devcgh_builder.py
   devcfg_xml_dict = {}
   for word in devcfg_xml_tag_list:
      devcfg_xml_dict[word] = 'pp_' + word
   #devcfg_xml_pp_tag_list = {word:('pp_' + word) for word in devcfg_xml_tag_list}
   env.Replace(DEVCFG_XML_TAGS = devcfg_xml_tag_list)
   env.Replace(DEVCFG_XML_DICT = devcfg_xml_dict)
   env.Replace(DEVCFG_SOC_DICT = devcfg_soc_tag_dict)
   env.Replace(DEVCFG_TCSR_SOC_HW_ADDR = tcsr_hw_version_addr)
   #devcfg_used_tag_list = []
   #env.Replace(DEVCFG_ENV_USED_XML_TAGS = devcfg_used_tag_list)
   
   env.Append(CPPDEFINES = [
      "DAL_CONFIG_IMAGE_MODEM",
      "DAL_CONFIG_TARGET_ID=${DAL_CONFIG_TARGET_ID}",
      #"DEVCFG_XML_TAGS=DEVCFG_XML_TAGS",
      #"DEVCFG_XML_DICT=DEVCFG_XML_DICT",
      #"DEVCFG_ENV_USED_XML_TAGS=$DEVCFG_ENV_USED_XML_TAGS",
   ])

def exists(env):
    return env.Detect('tbc_core_devcfg')
