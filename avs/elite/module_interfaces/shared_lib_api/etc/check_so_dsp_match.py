""" check_so_dsp_match.py script

Checks for match between a given .so file and a DSP build.

Usage:
check_so_dsp_match.py -s so_file -d dsp_elf
Eg. check_so_dsp_match.py -s "X:\AVS.ADSP.2.6.dynloading2\adsp_proc\avs\install_dir\avs_shared_libs\qdsp6\AAAAAAAA\HpMp3DecoderModule_strip.so.1.0" -d "X:\AVS.ADSP.2.6.dynloading2\adsp_proc\build\ms\M8994AAAAAAAAQ1234.elf"

"""

import sys
import os
import struct
from optparse import OptionParser, OptionGroup
from compare_lists import *
from elf_util import *

#===========================================================================
usage = r'Checks for match between a given .so file and a DSP build. Returns 0->compatible, 1->not compatible, 2-> maybe compatible(when this .so depends on other .so files.). Eg. check_so_dsp_match.py ' + \
'-s X:\AVS.ADSP.2.6.dynloading2\adsp_proc\avs\install_dir\avs_shared_libs\qdsp6\AAAAAAAA\HpMp3DecoderModule_strip.so.1.0'+\
'-d X:\AVS.ADSP.2.6.dynloading2\adsp_proc\build\ms\M8994AAAAAAAAQ1234.elf'
parser = OptionParser(description=usage)
required_group = OptionGroup(parser, "Required Arguments")
required_group.add_option("-s","--so_file", default='', help="Input .so file of the shared library.") 
required_group.add_option("-d","--dsp_elf", default='', help="Input .elf file of the DSP build.") 

opt_group = OptionGroup(parser, "Optional Arguments")
opt_group.add_option("-c", "--csv", default='', help="CSV file name for comparing symbols")
opt_group.add_option("-v", "--verbose", default='', help="Verbose logging")

parser.add_option_group(required_group)
parser.add_option_group(opt_group)

(options, args) = parser.parse_args()

so_file_name=options.so_file;
dsp_elf_name=options.dsp_elf;
csv=options.csv;
verbose=options.verbose;

if so_file_name == '' or dsp_elf_name == '':
    sys.exit("Error: Insufficient Arguments, use -h option to see required arguments")
    
dsp_symbols_items=run_hexagon_readelf(dsp_elf_name, '-DWs')
so_symbols_items=run_hexagon_readelf(so_file_name, '-Ws') 
dsp_sections_items=run_hexagon_readelf(dsp_elf_name, '-S')
so_sections_items=run_hexagon_readelf(so_file_name, '-S')
so_dynamic_items=run_hexagon_readelf(so_file_name, '-d')

#print 'dsp_symbols_items :'
#print_arr(dsp_symbols_items)
#print 'so_symbols_items :'
#print_arr(so_symbols_items)
#print 'dsp_sections_items :'
#print_arr(dsp_sections_items)
#print 'so_sections_items :'
#print_arr(so_sections_items)

dsp_symbol_names=list_all_syms(dsp_symbols_items);
so_symbol_names=list_und_syms(so_symbols_items);

print 
print '>>> Comparing symbols: '
so_and_dsp, so_not_dsp, dsp_not_so=compare_lists_and_print(so_symbol_names,dsp_symbol_names, '.SO', 'DSP',csv);
so_not_dsp_new=[]
for i in so_not_dsp:
   if not i=='':
      so_not_dsp_new.append(i);
      
if not csv=='':
   print '>>> Symbols comparison between DSP and .SO is in '+csv
   print

print '-------------------------------------------------'   
print 'Build Properties of .SO file '+so_file_name
print '-------------------------------------------------'
data_str=get_sym_pointed_data(so_file_name, 'shared_lib_build_property', so_symbols_items, so_sections_items);   
build_property_version = struct.unpack('H',data_str[0:2]);
print '    Build Property Version     : '+str(build_property_version[0])

so_version_found=True;
if build_property_version[0]==1:
      fmt='HHHHHHHBBBB' #\x01\x00 \x00\x00 \x01\x00 \x00\x00 \x01\x00 \x07\x00 \x00\x00 \x05\x01\x05\x00
      str_size=len(data_str[2:])-struct.calcsize(fmt)
      fmt=fmt+str(str_size)+'s'
      #import pdb; pdb.set_trace()
      so_api_major_version,so_api_minor_version,lib_major_version,lib_minor_version,so_is_qurt_used,so_qurt_api_version,reserved,so_hexagon_tools_version1,so_hexagon_tools_version2,hexagon_tools_version3,hexagon_tools_version4,build_id= struct.unpack(fmt,data_str[2:]);
      print '    Shared Library API Version : '+str(so_api_major_version)+'.'+str(so_api_minor_version)
      print '    Library Version            : '+str(lib_major_version)+'.'+str(lib_minor_version)
      if so_is_qurt_used:
         print '    Qurt is used, Qurt Version : '+str(so_qurt_api_version)
      else:
         print '    Qurt is not used.'
      print '    Hexagon Tools Version      : %02d.%02d.%02d'%(so_hexagon_tools_version1,so_hexagon_tools_version2,hexagon_tools_version3)
      print '    Build ID                   : '+build_id
else:
      print '    Unknown build property version: '+str(build_property_version[0])
      so_version_found=False;
print '-------------------------------------------------'
#################################
print 'Build Properties of DSP Build '+dsp_elf_name
print '-------------------------------------------------'
data_str=get_sym_pointed_data(dsp_elf_name, 'adsp_avs_build_property', dsp_symbols_items, dsp_sections_items);  
if None == data_str:
     print '>>> ERROR: DSP build doesnot contain build property symbols'
     sys.exit(1)
     
#'\x01\x00 \x01\x00 \x00\x00 \x07\x00 \x05\x01\x05\x00'
build_property_version = struct.unpack('H',data_str[0:2]);
print '    Build Property Version     : '+str(build_property_version[0])
#import pdb; pdb.set_trace()
dsp_version_found=True;
if build_property_version[0]==1:
      fmt='HHHBBBB' #\x01\x00 \x00\x00 \x07\x00 \x05\x01\x05\x00'
      dsp_api_major_version,dsp_api_minor_version,dsp_qurt_api_version,dsp_hexagon_tools_version1,dsp_hexagon_tools_version2,hexagon_tools_version3,hexagon_tools_version4= struct.unpack(fmt,data_str[2:]);
      print '    Shared Library API Version : '+str(dsp_api_major_version)+'.'+str(dsp_api_minor_version)
      print '    Qurt Version               : '+str(dsp_qurt_api_version)
      print '    Hexagon Tools Version      : %02d.%02d.%02d'%(dsp_hexagon_tools_version1,dsp_hexagon_tools_version2,hexagon_tools_version3)
else:
      print '    Unknown build property version: '+str(build_property_version[0])
      dsp_version_found=False;
print '-------------------------------------------------'
#######################
print
any_error=False;
if so_version_found and dsp_version_found:
   if so_api_major_version != dsp_api_major_version:
      print '>>> ERROR: Shared library API versions are not compatible'
      any_error = True;
   if so_is_qurt_used:
      if so_qurt_api_version != dsp_qurt_api_version:
         print '>>> ERROR: Qurt API versions are not compatible'
         any_error=True;
   if so_hexagon_tools_version1 != dsp_hexagon_tools_version1 or so_hexagon_tools_version2 != dsp_hexagon_tools_version2:
      print '>>> ERROR: Hexagon Tools versions are not compatible'
      any_error=True;

if len(so_dynamic_items):
   print '>>> This so file depends on shared libraries: '+str(so_dynamic_items);
else:
   print '>>> This so file does not depend on other shared libraries'

ret = 0;
print   
if any_error:
   print '>>> ERROR: *** DSP and .SO file are not compatible ***'
   ret = 1;
else:
   if len(so_not_dsp_new)>0:
      print '>>> There are  dynamically linkable symbols in the .SO file that are not exposed by DSP as shown below:'
      print so_not_dsp_new
      print
      if len(so_dynamic_items):
         print '>>> Warning: Assuming that the dependent shared libraries provide the above symbols, DSP and .SO file are compatible.' 
         ret = 2;
      else:
         print '>>> Error: DSP and .SO file are not compatible' #since symbols may not be used?
         ret = 1;
   else:
      print '>>> DSP and .SO file are compatible'
      ret = 0;
      
   
#TODO dependent so files.

print   
print '>>> Done'
print 

sys.exit(ret)
