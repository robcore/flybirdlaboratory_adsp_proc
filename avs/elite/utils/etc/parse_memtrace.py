'''
Created on Jul 16, 2012

@author: likhengp
'''
from optparse import OptionParser, OptionGroup
from collections import defaultdict

import os
import os.path
import sys
import re
import subprocess
import csv
import time

objdump_line = re.compile(r"([0-9a-f]{8}).*\s+(\S+)\s+([0-9a-f]{8})\s+(.+)")
#Parse for "QURT_ELITE_MALLOC_FREE_TRACER:"
runlog_line = re.compile(r"QURT_ELITE_MALLOC_FREE_TRACER:\s+(\S+)\s+0x([0-9a-f]+)\s+([0-9]+)\s+(.+)")
#Parse for physical addresses
memtrace_line = re.compile(r"^TNUM.*:PADDR=([0-9a-f]+):.*$")
#kernel trace buffer line
kernel_tracebuf_line = re.compile(r"allocated kernel trace buffer at vaddr=.*paddr=([0-9a-f]+).*size 0x([0-9a-f]+) bytes")

#Known physical addresses of register pools and memory pools such as EBI
#This information is obtained from adsp_proc/msm8974/qdsp6.xml file
#Any changes in the above file must be reflected here too.
#TODO: How can this be generalized to any chipset such as 9x25 etc.
#May be take an additional chipset argument
#TODO: How can we automatically read this info from the XML without
#duplicating here.
reg_pool_dict = {0x00108000 : ['.mem_pool',   24576, 'RPM_Msg_RAM'],
                 0x00200000 : ['.reg_pool',    4096, 'MPM_Registers'],
                 0x00802000 : ['.reg_pool',    4096, 'ICB_Bus_Arb'],
                 0x00903000 : ['.reg_pool',    4096, 'LPASS_PLL4_Voting'],
                 0x01200000 : ['.mem_pool',    4096, 'SMD_HW_Splinlock'],
                 0xfb1a0000 : ['.reg_pool',    4096, 'RIVA_FM'],
                 0xfb206000 : ['.reg_pool',    4096, 'RIVA_CCU_MB0_CTRL'],
                 0xfb280000 : ['.mem_pool',  131072, 'RIVA_CMEM_SRAM'],
                 0xfd922000 : ['.reg_pool',    4096, 'HDMI_CTRL'],
                 0x12800000 : ['.reg_pool',    4096, 'SPS_Reg_Pool'],
                 0x0fa00000 : ['.mem_pool', 2097152, 'SMEM Pool'],
                 0xfe000000 : ['.reg_pool',  458752, 'ADSP_Reg_Pool_1'],
                 0xfe0c0000 : ['.reg_pool',  131072, 'ADSP_Reg_Pool_2'],
                 0xfe100000 : ['.reg_pool',  524288, 'Slimbus_Pool'],
                 0xfe200000 : ['.reg_pool', 1048576, 'Q6SS_CSR_SIRC_SAW'],
                 0xfe400000 : ['.mem_pool',  131072, 'TCM_Physpool'],
                 0xfe090000 : ['.mem_pool',   65536, 'LPM_memory'],
                 0x0fc00000 : ['.mem_pool', 4194304, 'EBI1 Pool'],
                 }
                 
                 
                 

#===============================================================================
# run hexagon-objdump on elf file and generate dump file
# @param elf_file: file path to elf file, this function will run objdump on it
#===============================================================================
def objdump_elf(elf_file, symtab_file, sectinfo_file):
    print "Running hexagon-objdump"
    
    try:
        f = open(symtab_file, "wb")
        try:
            try:
                subprocess.check_call(["hexagon-objdump","-t","-C",elf_file], stdout=f,stderr=sys.stderr)
            except:
                sys.exit("Hexagon-objdump failed")
        finally:
            f.close()
    except IOError:
        print "Could not open output file for hexagon-objdump output"
    
    #Get the details of .start section
    #The VMA of this section will be the starting virtual address
    #The LMA of this section will be the starting physical address
    with open(sectinfo_file, 'w') as f:
        try:
            subprocess.check_call(["hexagon-objdump", "-h", "-j", ".start",elf_file], stdout=f,stderr=sys.stderr)
        except:
            sys.exit("Hexagon-objdump failed")
    
#================================================================================
# Parses information of .start section and returns the offset between VMA and LMA
#================================================================================
def get_offset_phy_addr(sectinfo_file):
    #Parse sectinfo file and get the offset between LMA and VMA
    offset = 0
    with open(sectinfo_file, 'r') as f:
        for line in f:
            #check if the line contains ".start"
            if line.find(".start") != -1:
                line = line.lstrip().rstrip()
                wl = line.split()
                vma = int(wl[3], 16)
                lma = int(wl[4], 16)
                offset = lma - vma
                break
                
    return offset
    
#===============================================================================
# parses objdump output and creates dictionary of symbols
# -Created dictionary format:
#    key = starting paddr
#    content = [section/type (e.g. .text), size (decimal in bytes), symbol]
#===============================================================================
def parse_objdump(symtab_file, offset_phy_addr, prop_sym_search_path, verbose):
    #First go through all the proprietary symbols maps and prepare for de-obfuscatation
    prop_sym_map = {}
    if prop_sym_search_path != '':
        for root, dirnames, filenames in os.walk(prop_sym_search_path):
            for file in filenames:
                if file == 'proprietary_symbols.map':
                    file = os.path.join(root, file)
                    with open(file) as f:
                        for line in f:
                            word_list = line.rstrip().split()
                            if len(word_list) == 2:
                                #first word is de-obfuscated symbol
                                #second word is the obfuscated symbol
                                prop_sym_map[word_list[1]] = word_list[0]

    print "Parsing objdump output"
    f = open(symtab_file,"rb")
    parsed_dict = {}
    try:
        try:
            for line in f:
                m = objdump_line.match(line)
                if m:
                    #m.group(1) is VA. Convert to PA by adding the offset
                    paddr = int(m.group(1), 16) + offset_phy_addr
                    size = int(m.group(3), 16)
                    # if address already in dict, then overwrite if new one
                    # has larger size (cover more address space)
                    if paddr in parsed_dict.keys():
                        # Do not add symbol if it is inside another symbol (i.e. start addr equal, but
                        # end addr < another symbol
                        if parsed_dict[paddr][1] > size:
                            continue
                    # only add if symbol has size > 0
                    if size > 0:
                        sect_name = m.group(2).rstrip()
                        sym_name = m.group(4).rstrip()
                        
                        #Map the obfuscated symbol to its original name
                        if sym_name in prop_sym_map.keys():
                            sym_name = prop_sym_map[sym_name]
                            
                        parsed_dict[paddr] = [sect_name, size, sym_name.rstrip()]
                    elif verbose == True:
                        print "Zero Size, ignored: %s"%str(line)
        except IOError: 
            sys.exit("Failed to read hexagon-objdump output")
    finally:
        f.close()
    
    return parsed_dict

#===============================================================================
# parses runlog generated by test output (stdout)
# identifies all heap buffers allocated during setup and runtime
    # stores as dictionary in format:
    #     key: starting phy addr
    #     value: ["type", size (bytes in decimal), "symbol name"]
#===============================================================================
def parse_runlogs(rl_file, offset_phy_addr, verbose):
    # Checks for overlapping heap buffers and returns coalesced buffer info
    # If not overlapping, return (None, None, None)
    def check_overlap(key1, buf1, key2, buf2):
        start1 = key1
        end1 = start1 + buf1[1] - 1
        start2 = key2
        end2 = start2 + buf2[1] - 1
        if start1 >= end2 or start2 >= end1:
            return (None, None, None)
        new_symb_name = "|".join([buf1[2],buf2[2]])
        new_addr = min (start1,start2)
        new_size = max(end1,end2) - new_addr + 1
        return (new_symb_name, new_addr, new_size)
    
    # parse runlog for malloc on heap information
    # stores as dictionary in format:
    #     key: starting addr
    #     value: ["type", "size (bytes in decimal)", "symbol name"]
    print "Parsing runlogs"
    try:
        f= open(rl_file)
        parsed_dict = {}
        num_malloc_free_trans = 0
        prev_op = "None"
        try:
            for line in f:
                m = runlog_line.match(line)
                if m:
                    symbol = m.group(4).rstrip()
                    addr = int(m.group(2), 16) + offset_phy_addr
                    size = int(m.group(3), 10)
                    sect = ".heap"
                    malloc_free = m.group(1)
                    if malloc_free == "Malloc":
                        if addr in parsed_dict.keys():
                            # if current address alread exists, check if it is
                            # bigger than the pervious one, if no, ignore line
                            if size < parsed_dict[addr][1]:
                                if verbose == True:
                                    print "Buffer within buffer, ignored: %s"%str(line)
                                continue
                        # size in decimal (from runlog)
                        parsed_dict[addr] = [sect, size, symbol]
                    # if buffer is freeed before running test case, remove
                    elif malloc_free == "Free":
                        if prev_op == "Malloc":
                            num_malloc_free_trans += 1
                        if num_malloc_free_trans < 2 and addr in parsed_dict.keys():
                            if parsed_dict[addr][1] == size:
                                del parsed_dict[addr]
                    prev_op = malloc_free
        finally:
            f.close()
            
    except IOError:
        sys.exit("Failed to open runlog file: %s"%rl_file)
        
    # Identifies heaps with overlap with each other and combines them
    coalesced_dict = {}
    overlapped = False
    for k in sorted(parsed_dict.keys()):
        v = parsed_dict[k]
        if k not in coalesced_dict:
            overlapped = False
            for kn in sorted(coalesced_dict.keys()):
                vn = coalesced_dict[kn]
                (symb, addr, size) = check_overlap(kn, vn, k, v)
                if not (symb == addr == size == None):
                    del coalesced_dict[kn]
                    coalesced_dict[addr] = [".heap", size, symb]
                    print "(%x .heap %d %s) overlaps with (%x .heap %d %s) -> (%x .heap %d %s)"%(k, v[1], v[2],kn,vn[1],vn[2],addr,size,symb)
                    overlapped = True
                    break
            if not overlapped:
                coalesced_dict[k] = v
   
    #Search for kernel trace buffer regions
    mem_type = '.bss'
    mem_name = 'qurt_kernel_trace_buffers'
    
    with open(rl_file) as f:
        for line in f:
            m = kernel_tracebuf_line.match(line)
            if m:
                addr = int(m.group(1), 16)
                size = int(m.group(2), 16)
                coalesced_dict[addr] = [mem_type, size, mem_name]
                break
                        
    return coalesced_dict

#===============================================================================
# parse memtrace file for PADDR field
#  - keep trace of # of occurrences of unique addresses
#  - stores values as defaultdict
#===============================================================================
def parse_memtrace(mt_file):
    print "Parsing memtrace"

    num_trace = 0
    # parse memtrace file for PADDR field
    # keep trace of # of occurrences of unique addresses
    try:
        f = open(mt_file, "rb")
        try:

            addr_d = defaultdict(int)
            for line in f:
                m = memtrace_line.match(line)
                num_trace += 1
                addr = int(m.group(1), 16)
                addr_d[addr] += 1
                
        finally:
            f.close()
    except IOError:
        sys.exit("Failed to open memtrace file: %s"%mt_file)

    
    print "Number of memtrace accesses: %d"%(num_trace)
    return addr_d

#===============================================================================
# combines parsed data from objdump and runlog
# - output saved/merged into od_parsed_d parameter
# @param od_parsed_d: dictionary containing symbol info from hexagon-objdump
# @param rl_parsed_d: dictionary containing heap buffer info from runlogs
# @return: None
# Note: od_parsed_d and rl_parsed_d should have same formate and structure
#===============================================================================
def combine_od_rl(od_parsed_d, rl_parsed_d):
    for k,v in rl_parsed_d.iteritems():
            if k not in od_parsed_d:
                od_parsed_d[k] = v
            else:
                print "Overlapping HEAP & static buffers: %x %s"%(k,str(v))

def create_unknowns(symbols_d):
    print "Creating unknown regions"
    def has_gap(symb0, symb1):
        start0 = symb0[0]
        size0 = symb0[2]
        end0 = start0 + size0 -1
        
        start1 = symb1[0]
        
        if end0 > start1:
            print "Overlapping symbols: %s <--> %s"%(str(symb0),str(symb1))
            
        if end0 < start1:
            return True
        return False
    
    unkn_d = {}
    prev = None
    for k in sorted(symbols_d.keys()):
        v = symbols_d[k]
        if prev is None:
            prev = [k,] + v
            continue
        curr = [k,] + v
        if has_gap(prev, curr):
            start0 = prev[0]
            size0 = prev[2]
            end0 = start0 + size0 - 1
            start1 = curr[0]
            unkn_start = end0+1
            unkn_end = start1-1
            unkn_size = unkn_end - unkn_start + 1
            
            addr = unkn_start
            size = unkn_size
            unkn_d[addr] = ['.unknown',size, 'UNKNOWN' ]
            
        prev = curr
    
    symb_address_list = sorted(symbols_d.keys())
    if symb_address_list[0] > 0:
        size = symb_address_list[0]
        unkn_d[0] = ['.unknown',size, 'UNKNOWN' ]
    end_of_last = symb_address_list[-1] + symbols_d[symb_address_list[-1]][1]
    if end_of_last < 0xffffffff:
        start = end_of_last
        size = 0xffffffff - end_of_last + 1
        unkn_d[start] = ['.unknown',size, 'UNKNOWN' ]
    
    for k,v in unkn_d.items():
        if k not in symbols_d.keys():
            symbols_d[k] = v

#===============================================================================
# find_accesses
# - maps memtrace paddr's to symbols/buffers
# @param od_parsed_d: dictioary/hash-table containing symbol table
#                -Format: key - paddr, value - ["type", "size", "symbol"]
# @param mt_parsed_d: dictionary/hash-table containing PADDR from memtrace
#                -Format: key - PADDR, value - address access count (how many
#                            times it was accessed)
# @return: dictionary of unknown accesses
#                -Format: key - PADDR, value - count (number of times accessed)
#===============================================================================
def find_accesses(od_parsed_d, mt_parsed_d):
    #==========================================================================
    # Recursive binary search function to find memory region that PADDR (from memtrace) 
    # maps into. If found, returns True. Else, returns False.
    # @param target_addr: PADDR from memtrace (key of mt_parsed_d)
    # @param target_access_count: occurance count of PADDR (value of mt_parsed_d)
    # @param low: low index of binary search
    # @param high: high index of binary search
    # @param addr_list: list of sorted starting addresses of symbols/buffers (key of 
    #                   od_parsed_d). This is the list that is being binary searched
    # @param mem_region_d: same as od_parsed_d
    # @return: True if found, False if not found
    #==========================================================================
    def find_region(target_addr, target_access_count, low, high, addr_list, mem_region_d):
        if low > high:
            return False
        current = (high+low)//2
        current_address = addr_list[current]
        start_addr = current_address
        buff_size = mem_region_d[current_address][1]
        end_addr = start_addr+ buff_size - 1
        if target_addr >= start_addr and target_addr <= end_addr:
            # if found, add number of access to that address in od_parsed_d entry
            # updated od_parsed_d becomes: {'address': ['.section','size','symbol',\
            # '# of access', 'range addr low', 'range addr high', 'range'],...}
            this_access_count = target_access_count # memtrace_addr_d values are int
            if len(mem_region_d[current_address]) == 3:
                mem_region_d[current_address].append(this_access_count)
                mem_region_d[current_address].append(target_addr)
                mem_region_d[current_address].append(target_addr)
                mem_region_d[current_address].append(1)
            else:
                accum_access_count = mem_region_d[current_address][3]
                mem_region_d[current_address][3] = accum_access_count + this_access_count
                if mem_region_d[current_address][4] > target_addr:
                    mem_region_d[current_address][4] = target_addr
                if mem_region_d[current_address][5] < target_addr:
                    mem_region_d[current_address][5] = target_addr
                mem_region_d[current_address][6] = mem_region_d[current_address][5] - mem_region_d[current_address][4] + 1
            return True
        if target_addr < start_addr:
            high = current-1
        elif target_addr > end_addr:
            low = current+1
        return find_region(target_addr, target_access_count, low, high, addr_list, mem_region_d)
    
    print "Mapping Accesses to Symbols"
    trace_count = 0
    unknown_access_d = {}
    symb_addr_list = sorted(od_parsed_d.keys())
    low = 0
    high = len(symb_addr_list)-1
    # loop through memtrace PADDRes and map to symbol/buffer
    for k in mt_parsed_d.iterkeys():
        trace_count += mt_parsed_d[k]
        found = find_region(k, mt_parsed_d[k], low, high, symb_addr_list, od_parsed_d)
        if not found:
            unknown_access_d[k] = str(mt_parsed_d[k])

    return unknown_access_d

#===============================================================================
# Creates a valid file path
#===============================================================================
def make_path(dir_name,file_name):
    file_name = os.path.join(dir_name, file_name)
    out_dir = os.path.dirname(file_name)
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)
    return file_name

#===============================================================================
# Writes identified symbols/buffers to CSV file
#===============================================================================
def print_output(od_parsed_d, output_file_name):
    total_size = 0
    output_file = make_path("./memtrace_output/", output_file_name)

    title_row = ["Phy Addr","Type","Size(Bytes)","Symbol","Access Count", "Touched Low Addr", "Touched High Addr", "Range(Bytes)"]   
    #write_to_csv(od_parsed_d, output_file,title_row,7)
    try:
        f = open(output_file,"wb")
        try:
            writer = csv.writer(f)
            writer.writerow(title_row)
            size_d = {}
            for k,v in od_parsed_d.iteritems():
                if len(v) == 7:
                    line = []
                    line.append("%x"%k)
                    line.append(v[0])
                    line.append(v[1])
                    line.append(v[2])
                    line.append(v[3])
                    line.append("%x"%v[4])
                    line.append("%x"%v[5])
                    line.append(v[6])
                    writer.writerow(line)
                    total_size += v[3]

                    if v[0] not in size_d:
                        size_d[v[0]] = 0;
                    size_d[v[0]] += v[1]
        finally:
            f.close()
        print "\nTouched Section Sizes:"
        for k,v in size_d.items():
            print "    %s - %d bytes"%(k,v)
            
    except IOError:
        sys.exit("Failed to write to trace_output.csv")
#    print "Number of identified traces (access count)= %s"%str(total_size)
    return total_size


def main():
    usage = "This script parses the memory trace file obtained from running \
the Hexagon simulator. The accessed memory addresses are translated to \
accessed symbol names."
    parser = OptionParser(description=usage)
    required_group = OptionGroup(parser, "Required Arguments")
    required_group.add_option("-e", "--elf", default=None, help="Path to ELF file") 
    required_group.add_option("-l","--runlog", default=None, help="Path to runlog file") 
    required_group.add_option("-m", "--memtrace", default=None, help="Path to memtrace file") 
    opt_group = OptionGroup(parser, "Optional Arguments")
    opt_group.add_option("-o","--output-file",default="trace_output.csv",
                      help="Set output file name, defaults to %defualt") 
    opt_group.add_option("-v","--verbose",default=False, action="store_true", help="Prints out debug messages")
    opt_group.add_option("-p", "--prop-sym-search-path", default='',
                      help="Path for searching proprietary symbol map files. \
Will be used for de-obfuscating proprietary symbols. \
Default: no searching for the map files.")

    parser.add_option_group(required_group)
    parser.add_option_group(opt_group)
    (opts, args) = parser.parse_args()
    
    elf_file = opts.elf
    rl_file = opts.runlog
    mt_file = opts.memtrace
    out_file = opts.output_file
    verbose = opts.verbose
    prop_sym_search_path = opts.prop_sym_search_path
    
    if elf_file == None or rl_file == None or mt_file == None:
        sys.exit("Error: Insufficient Arugments, use -h option to see required arguments\n")
    
    start_time = time.time()
    
    symtab_file = 'symtab.txt'
    sectinfo_file = 'sectinfo.txt'
    objdump_elf(elf_file, symtab_file, sectinfo_file) # run hexagon-objdump
    offset_phy_addr = get_offset_phy_addr(sectinfo_file)
    od_parsed_d = parse_objdump(symtab_file, offset_phy_addr, prop_sym_search_path, verbose) # parse hexagon-objdump output
    rl_parsed_d = parse_runlogs(rl_file, offset_phy_addr, verbose) # parse runlog
    combine_od_rl(od_parsed_d, rl_parsed_d) # return dictionary stored in od_parsed_d
    #combine register and memory pool lists
    combine_od_rl(od_parsed_d, reg_pool_dict)
    mt_parsed_d = parse_memtrace(mt_file) # parse memtrace file
    create_unknowns(od_parsed_d)
    find_accesses(od_parsed_d, mt_parsed_d) # return dictionary stored in od_parsed_d

    identified_size = print_output(od_parsed_d, out_file) # write to csv
    print "Total number of identified traces = %d"%(identified_size)
    
    end_time = time.time()
    total_time = end_time - start_time
    print "Done!\nTotal Execution Time = %s\n"%(str(total_time))
    
    #delete symbol table file and sect info file
    os.remove(symtab_file)
    os.remove(sectinfo_file)
    
if __name__ == '__main__':
    main()



