""" parse_map_8974.py script

This Python script parses a MAP file to retrieve information about image 
footprint. Although this should work for MAP files in general, it has only been 
tested on 8974 MAP files.

Usage:
python parse_map8974.py <path_to_map_file.elf.map> <path_to_hexagon_nm_output.txt> <path_to_output_dir> [<target_folder>]

"""
__author__ = "Philip Chan(likhengp@qualcomm.com)"
__version__ = "$Revision: #3 $"
__date__ = "$Date: 2014/12/26 $"
__copyright__ = "Copyright (c) 2012 Qualcomm Inc"
__license__ = "Python"

import sys
import re
import string
import os
from optparse import OptionParser
import csv
import subprocess

# Regex strings rom Michael's script
beg_text = re.compile(r'\.text\s+')
end_text = re.compile(r'\.(?!text)')
beg_rodata = re.compile(r'\.rodata\s+')
end_rodata = re.compile(r'\.(?!rodata)')
beg_data = re.compile(r'\.data\s+')
end_data = re.compile(r'\.(?!data)')
beg_bss = re.compile(r'\.bss\s+')
end_bss = re.compile(r'\.(?!bss)')
beg_sdata = re.compile(r'\.sdata\s+')
end_sdata = re.compile(r'\.(?!sdata)')
beg_sbss = re.compile(r'\.sbss\s+')
end_sbss = re.compile(r'\.(?!sbss)')

gnu_line = re.compile(r'\s*.gnu.*') # is within .sdata section
size_line = re.compile(r'(.+)0x([a-fA-F0-9]{8})\s+0x(\S+)(.*)')   # changed from (0x.{8}) -> 0x(.{8})
size_line_2 = re.compile(r'(.+)0x([a-fA-F0-9]{8})\s+0x(\S+)(.*)')
symbol_line = re.compile(r'\s+0x([a-fA-F0-9]{8})\s+(\S+)') #old: re.compile(r'\s.[a-z]+',re.I)
formatted_line = re.compile(r'\s*\S+\s+[a-fA-F0-9]{8}\s+[a-fA-F0-9]+\s+\S+')

#Sections regex strings
text_gen = re.compile(r'\s.text\s')
text_user = re.compile(r'\s*.text\..*')
rodata_gen = re.compile(r'\s.rodata\s')
rodata_user = re.compile(r'\s*.rodata\..*')
data_gen = re.compile(r'\s.data\s')
data_user = re.compile(r'\s*.data\..*')
bss_gen = re.compile(r'\s.bss\s')
bss_user = re.compile(r'\s*.bss\..*')
sdata_gen = re.compile(r'\s.sdata\s')
sdata_user = re.compile(r'\s*.sdata\..*')
sbss_gen = re.compile(r'\s.sbss\s')
sbss_user = re.compile(r'\s*.sbss\..*')
fill = re.compile(r'\s\*fill\*\s')

#nm output regex strings
nm_size = re.compile(r'(\S{8})\s(\S{8})\s\S\s(.*)')
nm_no_size = re.compile(r'(\S{8})\s\S\s(.*)')

#Folders regex strings
afe = re.compile(r'.*:/[^/]+/adsp_proc/afe/.*')
apr = re.compile(r'.*:/[^/]+/adsp_proc/apr/.*')
audio = re.compile(r'.*:/[^/]+/adsp_proc/audio/.*')
elite = re.compile(r'.*:/[^/]+/adsp_proc/elite/.*')
voice = re.compile(r'.*:/[^/]+/adsp_proc/voice/.*')
ultrasound = re.compile(r'.*:/[^/]+/adsp_proc/ultrasound/.*')
aDSPTest = re.compile(r'.*:/[^/]+/adsp_proc/aDSPTest/.*') 
adsptest_cosim = re.compile(r'.*:/[^/]+/adsp_proc/adsptest_cosim/.*')
api = re.compile(r'.*:/[^/]+/adsp_proc/api/.*')
avcs = re.compile(r'.*:/[^/]+/adsp_proc/avcs/.*')
build = re.compile(r'.*:/[^/]+/adsp_proc/build/.*')
build_test = re.compile(r'.*:/[^/]+/adsp_proc/build_test/.*')
core = re.compile(r'.*:/[^/]+/adsp_proc/core/.*')
deploypkg = re.compile(r'.*:/[^/]+/adsp_proc/deploypkg/.*')
doxygen = re.compile(r'.*:/[^/]+/adsp_proc/doxygen/.*')
hxgn_bld_utils_win = re.compile(r'.*:/[^/]+/adsp_proc/hxgn_bld_utils_win/.*')
jtag = re.compile(r'.*:/[^/]+/adsp_proc/jtag/.*')
manifest = re.compile(r'.*:/[^/]+/adsp_proc/manifest/.*')
obj = re.compile(r'.*:/[^/]+/adsp_proc/obj/.*')
pmic = re.compile(r'.*:/[^/]+/adsp_proc/pmic/.*')
qdsp6 = re.compile(r'.*:/[^/]+/adsp_proc/qdsp6/.*')
Sensors = re.compile(r'.*:/[^/]+/adsp_proc/Sensors/.*')
tools = re.compile(r'.*:/[^/]+/adsp_proc/tools/.*')
utils = re.compile(r'.*:/[^/]+/adsp_proc/utils/.*')
vsd = re.compile(r'.*:/[^/]+/adsp_proc/vsd/.*')

#==============================================================================
# checks which section (e.g. .text/.data/.rodata/etc) current line is in
# returns the section number
#==============================================================================
def identify_section(regex_list, line, curr_section):
    for regex,section in regex_list.items():
        if regex.match(line):
            return section
    return curr_section

#==============================================================================
# if line has only section name (e.g. .text.xyz) then data is on next line, join lines
#==============================================================================
def is_symbol_only(regex_list, line, flag):
    for regex in regex_list:
        if regex.match(line) and len(line.split()) < 2:
            return 1
    return flag

#==============================================================================
# checks if line is valid (of interest)
# Valid lines include: section names (e.g. \.text.*) and size lines (contains memory size)
# Invalid lines include lines with only virt. addr and symbol name (no size),
#  and other lines (basically, ^Valid)
#==============================================================================
def is_valid_line(regex_list, line):
    for regex in regex_list:
        if regex.match(line):
            return 1
    return 0

#==============================================================================
# Converts the memory size from hex to dec
# Returns a list (line.split())
#==============================================================================
def hex_to_dec(line):
    line = re.sub(r'0x','',line)
    line = line.split()
    if len(line) > 2:
        line[2] = int(line[2],16)
    return line

#===============================================================================
# make_path from directory name and file name
#===============================================================================
def make_path(dir_name,file_name):
    file_name = os.path.join(dir_name, file_name)
    out_dir = os.path.dirname(file_name)
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)
    return file_name

#===============================================================================
#    Write to csv output files
#    @param nm_dict: dictionary of symbols from hexagon-nm output
#    @param folder_dict: dictionary of each of the folders
#    @param sect_dict: dictionary of each of the sections (.text/.rodata/etc)
#    @param output_dir_path: string of the path of the output directory
#    @param is_specific_folder: boolean value, true if user provided specific folder
#                                search path
#    @param folder_regex: regex object for folder search path (will be ".*" if user
#                        did not provide string)
#    @param gen_folder: boolean, true if user used -f flag when running script
#    @param gen_section: boolean, true if user used -s flag when running script
#    
#    @return None
#===============================================================================
def write_to_csv(nm_dict, folder_dict, sect_dict, csv_file_name, output_dir_path, 
                 is_specific_folder, folder_regex, gen_folder, gen_section):
    
    # writes to csv output files (for folders and sections, symbols are done
    # separately below due to different formating)
    def helper(input_dict, output_dir, is_specific_folder_h, folder_re, csv_col_one):
        size_summary = {}
        # write to combined
        f = open(make_path(output_dir, '_'.join(['combined',csv_file_name])),'wb')
        try:
            c_writer = csv.writer(f)
            c_writer.writerow([csv_col_one,'Section(Detailed)','Virt. Addr','Size(Bytes)','Path'])
            c_size = 0
            # write to individual sections/folders
            for name, content in input_dict.items():
                if len(content) == 0:   # skip if no content
                    continue
                print 'Section/Folder: ',name
                size = 0
                g = open(make_path(output_dir, '_'.join([name,csv_file_name])),'wb')
                try:
                    writer = csv.writer(g)
                    writer.writerow(['Section','Virt. Addr','Size(Bytes)','Path'])
                    for line in content:
                        # check if user provided specific folder, if yes and line not
                        # in that folder, skip
                        if is_specific_folder_h and not folder_re.match(line):
                            continue
                        s_line = line.split()
                        writer.writerow(s_line)
                        c_writer.writerow([name]+s_line)   # write to combined
                        size += int(s_line[2])
                    c_size += size  # combined size
                    size_summary[name] = size   # add total size of section/folder to summary
                    writer.writerow([''])
                    writer.writerow(['total size','',size])
                finally:
                    g.close()
            c_writer.writerow([''])
            c_writer.writerow(['total size','','',c_size])
        finally:
            f.close()
            
        # write summary
        f = open(make_path(output_dir,'_'.join(['summary',csv_file_name])),'wb')
        try:
            s_writer = csv.writer(f)
            s_writer.writerow(['Section/Folder','Total Size(Bytes)'])
            for name,size in size_summary.items():
                s_writer.writerow([name,size])
        finally:
            f.close()
    
    # calculates size of each section in symbol csv   
    def calc_symb_sec_size(size_dict, sec, size):
        regex_dict = {'text':re.compile(r'\.text.*'),
                      'rodata':re.compile(r'(.rodata.*)'),
                      'data':re.compile(r'.data.*'),
                      'bss':re.compile(r'.bss.*'),
                      'sdata':re.compile(r'(.sdata.*)|(.gnu.*)|(.lita.*)'),
                      'sbss':re.compile(r'.sbss.*'),
                      'common':re.compile(r'(^COMMON)|(.scommon.*)')}
        for k,v in regex_dict.items():
            if v.match(sec):
                if k not in size_dict:
                    size_dict[k] = 0
                size_dict[k] += size
    
    if gen_section:        
        print 'Writing to Sections CSV'
        helper(sect_dict,os.path.join(output_dir_path,'sections'), 
               is_specific_folder, folder_regex,'Section(Gen)')
    
    if gen_folder:
        print 'Writing to Folders CSV'
        helper(folder_dict,os.path.join(output_dir_path,'folders'), 
               is_specific_folder, folder_regex, 'Folder')
    
    print 'Writing to Symbol CSV'
    size = 0
    symb_sec_size = {}
    output_dir = os.path.join(output_dir_path,'symbols')
    f = open(make_path(output_dir, '_'.join(['symbols',csv_file_name])),'wb')
    try:
        writer = csv.writer(f)
        for k,v in nm_dict.items():
            # check if user provided specific folder, if yes and line not
            # in that folder, skip
            if is_specific_folder and not folder_regex.match(k[3]):
                continue
            for symbol in v:
                if (symbol[1] is not None) and (not symbol[1] == "NO_SIZE"):
                    size += int(symbol[1])
                    calc_symb_sec_size(symb_sec_size, k[0], int(symbol[1]))
    
        writer.writerow(['Sections','Size(Bytes)'])
        for k,v in symb_sec_size.items():
            writer.writerow(['total_'+k, v])
        writer.writerow([''])
        writer.writerow(['total size',size])
        writer.writerow([''])
        
        # hack to enable having total sizes at the top instead of at the bottom
        # repeated loop to write to csv...
        writer.writerow(['Symbol','Size(Bytes)','Type','Path', 'Virt. Addr'])
        for k,v in nm_dict.items():
            if is_specific_folder and not folder_regex.match(k[3]):
                continue
            for symbol in v:
                if (symbol[1] is not None) and (not symbol[1] == "NO_SIZE"):
                    line = [symbol[2], symbol[1], k[0],k[3],symbol[0]]  # reorder columns
                    writer.writerow(line)
    finally:
        f.close()

#==============================================================================
# reads an output dump from hexagon-nm (hexagon-nm -S -C image.elf > output.txt)
#    - use -S flag to get output with size of symbol in bytes
#    - use -C flag to get demangled symbol names
# @Params:
#      fname: string that is name of nm output file
#      nm_list: list to which each line in fname file will be added to,
#               passed by reference (modifies passed in list)
#                - if symbol has size in nm_output, add tuple (addr,(size, symbol)) to
#                    symbol list
#                - if no size in nm_output, add tuple (addr,(None/Null, symbol)) to
#                    symbol list
#==============================================================================
def read_nm_output(f, nm_list):
    print 'Reading hexagon-nm output file'
    for line in f:
        if nm_size.match(line):
            line_list = line.rstrip().split(None,3)
            nm_list.append((line_list[0], (int(line_list[1],16), line_list[3])))
        elif nm_no_size.match(line):
            line_list = line.rstrip().split(None,2)
            nm_list.append((line_list[0], (None, line_list[2])))

#===============================================================================
# Checks if current line in MAP file contains a symbol (as opposed to path to
# obj file)
# format of symbol line is: \s+[a-fA-F0-9]{8}\s+\S+
#===============================================================================
def is_symbol_line(line, section_list, curr_regex, prev_regex):
    if len(section_list) <= 0:
        return 0
    curr_line_mo = curr_regex.match(line)
    prev_line_mo = prev_regex.match(section_list[-1])
    if curr_line_mo and prev_line_mo:
        return 1
    return 0

#===============================================================================
# Removes the '0x' in the hex address/size, and converts size field from hex
# to decimal
# Alters sect_dict parameter, no return value
#===============================================================================
def format_lines(sect_dict):
    for section in sect_dict.itervalues():
        for i,line in enumerate(section):
            line = (re.sub(r'0x','',line)).split()
            line[2] = str(int(line[2],16))
            section[i] = ' '.join(line)
#=============================================================================
# Params:
#    @symb_dict: same structure as symb_dict in "parse_logic" function
#    @nm_tuple: tuple of symbols read from "read_nm_output"
#            Format: (('address',('size'/None,'symbol')), ...)
#            e.g. (('c0001234',(372,'function_name(int, int)')),(...,(..,..)))
#=============================================================================
def insert_size_in_symb_dict(symb_dict, nm_tuple):
    nm_dict = dict(nm_tuple)
    for symb_key, symb_list in symb_dict.items():
        for i,symbol in enumerate(symb_list):
            # check if address from map file exists in hexagon-nm -S output
            if symbol[0] in nm_dict:  
                # check if size is known (from hexagon-nm -S)
                if nm_dict[symbol[0]][0] is None:
                    symb_dict[symb_key][i].insert(1,'NO_SIZE')
                else:
                    symb_dict[symb_key][i].insert(1,nm_dict[symbol[0]][0])
                # check if the symbol is know from map file, if not, get from
                # hexagon-nm output (i.e. nm_tuple/nm_dict)
                if symbol[2] is None:
                    symb_dict[symb_key][i][2] = nm_dict[symbol[0]][1]
            # if no symbol exists with that address, insert None into 'size'
            # file in tuple for future detection (see write_to_csv in how it is
            # checked)
            else:
                symb_dict[symb_key][i].insert(1,None)

           
#===========================================================================
#  Data structures storing parsed data:
#  @sect_dict:
#    stores all info on sections (.text/.rodata/.data/.sdata/.sbss) parsed
#    from the MAP file in a 
#    dictionary of lists: sect_dict = {'text':[...],'rodata':[...],...}.
#    Each of the dictionary items are a list of strings, each is a line 
#    in the MAP file,
#    e.g. {'text':['.text c0001234 723 z://abc.lib(abc.o)','...'],
#            'rodata':['..',..],...}
#    --> whole line is stored as a SINGLE string
#
#  @symb_dict:
#    stores all symbols in the MAP file as a dictionary of list of strings.
#    Each key is the tuple of the line to which the symbols lies under.
#    e.g. symb_dict = {('.text','c0001234',192,'z://abc.o'):[['c0001234','symbol(int, int*)']]}
#    Address and sizes stored in symb_dict are stripped of '0x', and sizes
#    are converted to decimal
#
# Notes:
# 1) 
#         append_flag == 1 if (addr/size/path) is on line after section name in
#         map file.
#         e.g. 
#         line n: .text.this_is_an_example
#         line n+1:             0xc0001234    0x928c    Z://this_is_an_example.lib
#         
#         This will append line n+1 to line n in sect_dict[section]
#
# 2)
#        Checks if the following condition is true:
#            line n    : [section] [addr] [size] [path]
#            line n+1  :            [addr]    [symbol name]
#        If yes, it will form a tuple with line n. This tuple will be the key
#        to retrieve line n+1 (and any following lines with that format) in a
#        symbols dictionary
#
# 3)
#        Checks if current line is not in a section of interest, if yes, set
#        curr_section to '', which is not a key in sect_dict, so it will not be
#        added to the sect_dict
#
# 4)
#        If current line is valid and is within a section of interest, add line
#        to sect_dict
#
# 5)
#         adds line to symbol dictionary even if it's not a symbol line, 
#         because symbols are not necessarily displayed as symbol lines
#         "insert_size_in_symbol_dict" will determine if this line has a symbol
#         or not after this function (parse_logic) returns
#         "symbol line" as in "line n+1" in Notes(2)
# 6)
#        Set curr_section to correct section
#===========================================================================
def parse_logic(sect_dict, symb_dict, f):
    user_regex_list = (text_user,rodata_user,data_user,bss_user, sdata_user, sbss_user)
    gen_regex_list = (text_gen, rodata_gen, data_gen, bss_gen, sdata_gen, sbss_gen)
    beg_regex_list = (beg_text, beg_rodata, beg_data, beg_bss, beg_sdata, beg_sbss)
    end_regex_list = (end_text, end_rodata, end_data, end_bss, end_sdata, end_sbss)
    sec_name_list = ('text', 'rodata', 'data', 'bss', 'sdata', 'sbss')
    append_flag = 0
#    symb_sec_flag = 0
    curr_section = -1
    
    valid_check_regex = user_regex_list + gen_regex_list + (size_line, gnu_line)
    
    print 'Parsing MAP file'
    for line in f:
        # Notes #1
        if append_flag:
            sect_dict[curr_section][-1] = \
                    ' '.join([string.rstrip(sect_dict[curr_section][-1]), line])
            append_flag = 0
            symb_key = tuple(hex_to_dec(sect_dict[curr_section][-1]))
            if not symb_key in symb_dict.iterkeys(): 
                symb_dict[symb_key] = [[symb_key[1],None]]
            continue
        # Notes #2
        if curr_section in sec_name_list and is_symbol_line(line, sect_dict[curr_section], symbol_line, size_line):
            symb_key = tuple(hex_to_dec(sect_dict[curr_section][-1]))
            if not symb_key in symb_dict or (len(symb_dict[symb_key]) == 1 and symb_dict[symb_key][0][1] is None):
                symb_dict[symb_key] = []                
            line = re.sub(r'0x','',line)
            symb_dict[symb_key].append((line.rstrip()).split(None,1)) 
        # Notes #3
        if curr_section in sec_name_list and dict(zip(sec_name_list, end_regex_list))[curr_section].match(line):
            curr_section = ''
        # Notes #4
        if curr_section in sec_name_list and is_valid_line(valid_check_regex, line):
            sect_dict[curr_section].append(line)
            append_flag = is_symbol_only(user_regex_list+(gnu_line,) + gen_regex_list, line, append_flag)
            # Notes #5
            if not append_flag:
                symb_key = tuple(hex_to_dec(line))
                if not symb_key in symb_dict.iterkeys() and not symb_key[2] == 0: 
                    symb_dict[symb_key] = [[symb_key[1],None]]
        # Notes #6
        curr_section = identify_section(dict(zip(beg_regex_list,sec_name_list)), line, curr_section)
    
    # formats each line in all sections, see format_lines(args) for explanation
    format_lines(sect_dict)

#===============================================================================
# parse_folders
# @param sect_dict: dictionary containing info of all sections parsed from map file
# @param folder_dict: dictionary containing info of all folders under 
#                        (1) adsp_proc OR (2) user specified folder
#                     Will be empty at time of function call, this function fills
#                     it with info
# @param folder: string containing folder path (starting from adsp_proc/),
#                defaults to adsp_proc if not provided
# @return: None, folder_dict contains all info processed by this function
#===============================================================================
def parse_folders(sect_dict, folder_dict, folder='default'):
    folder_re_list = (('afe',afe),('apr',apr),('audio',audio),('elite',elite),('voice',voice),('ultrasound',ultrasound)
                    ,('aDSPTest',aDSPTest), ('adsptest_cosim',adsptest_cosim),('api',api),('avcs',avcs)
                    ,('build',build),('build_test',build_test),('core',core),('deploypkg',deploypkg),('doxygen',doxygen)
                    ,('hxgn_bld_utils_win',hxgn_bld_utils_win),('jtag',jtag),('manifest',manifest),('obj',obj)
                    ,('pmic',pmic),('qdsp6',qdsp6),('Sensors',Sensors),('tools',tools),('utils',utils),('vsd',vsd))
    
    if folder == 'default':
        folder_re_dict = dict(folder_re_list)
    else:
        folder_name = re.sub(r'/','_', folder)
        folder_re_dict = {folder_name: re.compile(r'.*%s.*'%folder)}

    print 'Parsing Folders'
    for section in sect_dict.itervalues():
        for line in section:
            for name,re_obj in folder_re_dict.items():
                if not name in folder_dict:
                    folder_dict[name] = []
                if re_obj.match(line):
                    folder_dict[name].append(line)

#===============================================================================
# parses command line options or text file for list of folders to exlcude in
# results
# @param exclude_from_cmd: list of folder names/paths from command line directly,
#                        each folder separated by comma
# @param exlude_from_file: path to a text file that contains folder names/paths
# @return: exlude_src: "1" if parsing from cmd line,
#                      "0" if parsing from file,
#                      None/Null if not parsing
#===============================================================================
def get_exclusions(exclude_from_cmd,exclude_from_file):
    exclude_src = None
    X_CMD = 0
    X_FILE = 1
    if (exclude_from_cmd is not None) and (exclude_from_file is not None): 
        sys.exit("Error: Cannot take exclude input from both command line and file, please choose only 1 of the following options: \"-x\" or \"--exclude-from-file\", not both")
    elif exclude_from_cmd is not None:
        exclude_src = X_CMD
    elif exclude_from_file is not None:
        exclude_src = X_FILE
        
    if exclude_src == X_FILE:
        x_folders = []
        try:
            f = open(exclude_from_file, "rb")
            try:
                for line in f:
                    line = re.sub(r'\\', '/',line)
                    x_folders.append(line.rstrip())
            finally:
                f.close()
        except IOError:
            sys.exit("Error: Failed to open file containing exclude paths")
        if len(x_folders) == 0:
            x_folders = None
            exclude_src = None
        return (exclude_src, x_folders)
    elif exclude_src == X_CMD:
        path_list = exclude_from_cmd.split(",")
        x_folders = [re.sub(r'\\', '/',path) for path in path_list]
        if len(x_folders) == 0:
            x_folders = None
            exclude_src = None
        return (exclude_src, x_folders)
    return (None,None)
        
#===============================================================================
# remove_excludes
# if user provides --exclude/--exclude-from-file options, then remove those 
# results from the dictionaries
# @param x_folders: list containing strings of folder paths
# @return: None
#===============================================================================
def remove_excludes(symb_dict, folder_dict, sect_dict, x_folders):
    def check_match(re_list, data):
        for folder_re in re_list:
            if folder_re.match(data):
                return True
        return False
    
    list_of_re = []
    for folder in x_folders:
        list_of_re.append(re.compile(r".*%s.*"%str(folder)))
    
    # remove excludes from symbols dictionary
    for k in symb_dict.keys():
        for folder_re in list_of_re:
            if folder_re.match(k[3]):
                del symb_dict[k]
                break

    # remove excludes from folder_dict
    for v in folder_dict.values():
        v[:] = [line for line in v if not check_match(list_of_re,line)]
                
    # remove from sect_dict
    for v in sect_dict.values():
        v[:] = [line for line in v if not check_match(list_of_re,line)]
        
def main():
    
    #===========================================================================
    usage = 'This function parses a map file.'
    parser = OptionParser(description=usage)
    parser.add_option('-m','--map_file', help='Path to MAP file', default='../../../build/bsp/adsp_proc_img/build/ADSP_PROC_IMG_AAAAAAAAQ.elf.map')
    parser.add_option('-e','--elf_file', help='Path to ELF file', default='../../../build/bsp/adsp_proc_img/build/ADSP_PROC_IMG_AAAAAAAAQ.elf')
    parser.add_option('-f', '--gen-folder', help='Also Generate output categorized by folders', action='store_true', default=False)
    parser.add_option('-s','--gen-section', help='Also Generate output categorized by sections', action='store_true', default=False)
    parser.add_option('--folder', help='Only search for specific folder path', default='default')
    parser.add_option('-o','--output-dir', help='Output to specific directory. Defaults to ./parse_map_output', default='./parse_map_output')
    parser.add_option('-x','--exclude', help='Excludes specific folder path. E.g. -x adsp_proc/afe/', default=None)
    parser.add_option('--exclude-from-file', help='Same as -x option, but takes text file path as input, and reads file for a set of folder paths.\
                        e.g. --exclude-from-file ./excludes.txt\
                        Where excludes.txt contains, e.g.:\
                        adsp_proc/afe/\
                        adsp_proc/voice/some_folder', default=None)

    (options, args) = parser.parse_args()
        
    filename = options.map_file  # map file
    elf_name = options.elf_file  # ELF file
    output_dir = options.output_dir    # output directory
    folder = re.sub(r'\\', '/',options.folder)  # replace windows file separator
    gen_fold = options.gen_folder
    gen_sect = options.gen_section
    
    # Get exclusion folders if present
    exclude_from_cmd = options.exclude
    exclude_from_file = options.exclude_from_file
    (exclude_src, x_folders) = get_exclusions(exclude_from_cmd, exclude_from_file)
    
    #===========================================================================
    
    # run hexagon-nm on ELF file
    try:
        print 'Running hexagon-nm on ', elf_name
        f_hexagon = open('hexagon_nm_size_output.txt','wb')
        subprocess.call(['hexagon-nm', '-S', '-C', elf_name],stdout=f_hexagon)
        f_hexagon.close()
    except IOError:
        print "IOError: Failed to open output file for hexagon-nm"
        sys.exit()
    
    # parse map file
    try:
        f_map = open(filename,'rb')
        sect_dict = {'text':[],'rodata':[],'data':[], 'bss':[], 'sdata':[],'sbss':[]}
        symb_dict = {}
        try:
            parse_logic(sect_dict, symb_dict, f_map)
        finally:
            f_map.close()
    except IOError:
        print "Failed to read MAP file"
        sys.exit()
    
    # read demangled symbols and sizes from output generated by hexagon-nm
    # (command: hexagon-nm -S -C [elf file] > output_name.txt)
    try:
        nm_filename = 'hexagon_nm_size_output.txt'
        f_nm = open(nm_filename, 'rb')
        try:
            nm_list = []
            read_nm_output(f_nm, nm_list)
            insert_size_in_symb_dict(symb_dict, nm_list)
        finally:
            f_nm.close()
    except IOError:
        print "Failed to read hexagon-nm output"
        sys.exit()
         
    # separate into folders
    folder_dict = {}
        
    parse_folders(sect_dict, folder_dict, folder)
    if folder == 'default':
        folder_re = re.compile(r'.*')
        folder_specified = False
    else:
        folder_re = re.compile(r'.*%s.*'%folder)
        folder_specified = True
    
    # remove excluded folder
    if exclude_src == 0 or exclude_src == 1:
        remove_excludes(symb_dict, folder_dict, sect_dict, x_folders)
    
    # write results to csv files
    write_to_csv(symb_dict, folder_dict, sect_dict, 'output.csv', output_dir, 
                 folder_specified, folder_re, gen_fold, gen_sect)
 
    print 'Done\n'
    
if __name__ == "__main__":
    main()
