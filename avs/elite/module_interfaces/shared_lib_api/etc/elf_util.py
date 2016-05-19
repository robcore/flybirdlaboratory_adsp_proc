""" elf_util.py script

Contains utility for ELF

"""

import sys
import subprocess
import struct

UND=0xffff
class ReadElfSymbolItem:
    def __init__(self,addr=0,index=UND,name='',size=0):
        self.address=addr;
        self.index=index;
        self.name=name
        self.size=size;
        
    def __str__(self):
        return 'ELF Symbol: (addr,index,name,size): ('+str(self.address)+','+str(self.index)+','+str(self.name)+','+str(self.size)+')'

class ReadElfSectionItem:
    def __init__(self,addr=0,offset=0,size=0):
        self.address=addr;
        self.offset=offset;
        self.size=size      
    
    def __str__(self):
        return 'ELF Section: (addr,offset,size): ('+str(self.address)+','+str(self.offset)+','+str(self.size)+')'
        
# 708 232: f0117a40     4    FUNC GLOBAL DEFAULT  52 qurt_realloc     
#['f00202e0', '32', 'FUNC', 'GLOBAL', 'DEFAULT', '47', 'qurt_mem_region_create']
def parse_readelf_symbols(readelfoutstr):
    output=[];
    for line in readelfoutstr.split('\n'):
        line=line.strip();
        if len(line)==0:
            continue;
        if ':' in line:
            w=line.split(':')[0].split();
            if (w[-1]).isdigit():
                splits=line.split(':')[1].split();
                #print 'parse_readelf_symbols: '+str(splits)
                if len(splits)>0:
                    try: 
                        addr = int(splits[0],16);
                        size=int(splits[1]);
                    except ValueError:
                        print '>>> Error: parsing not going properly. results maybe wrong. line: '+line
                        continue;
                    if (len(splits)>=6):
                        ind=splits[5]
                        if ind.isdigit():
                            ind=int(ind);
                        elif ind=='UND':
                            ind=UND;
                        else:
                            ind=0;
                    name=''
                    if (len(splits)>=7):
                        name=splits[6]
                    item=ReadElfSymbolItem(addr,ind,name,size);
                    output.append(item);
                
    return output;
    
def is_hex(s):
    try:
        intgr = int(s, 16)
        return True
    except ValueError:
        return False
        
#['.strtab', 'STRTAB',   '00000000', '00e764', '000a91', '00', '0', '0', '1']
#['NULL',    '00000000', '000000',   '000000', '00',     '0',  '0', '0']    
def get_addr_offset_size(splits):
    addr=0;
    offset=0;
    size=0;
    #first 8 char thing, hexadecimal num.
    i=0;
    for word in splits:
        if len(word)==8 and is_hex(word):
            try:
                addr=int(word,16);
                offset=int(splits[i+1],16)
                size=int(splits[i+2],16)
            except ValueError:
                print '>>> Error: parsing sections output. results maynot be correct.i='+str(i)+', splits='+str(splits)
                offset=0;
                size=0;
            break;
        i+=1;
    #print addr,offset,size
    return addr,offset,size
    
    
# There are 21 section headers, starting at offset 0xd95c:

# Section Headers:
# [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
# [ 0]                   NULL            00000000 000000 000000 00      0   0  0
# [ 1] .hash             HASH            00000000 000100 0003ac 04   A  2   0  4
# [ 2] .dynsym           DYNSYM          000003ac 0004ac 000880 10   A  3   6  4    
# [20] .strtab           STRTAB          00000000 00e764 000a91 00      0   0  1
#  0    1     2       3             4       5         6     7    8    9
#['[', '0]', 'NULL', '00000000', '000000', '000000', '00', '0', '0', '0']
#['[20]', '.strtab', 'STRTAB', '00000000', '00e764', '000a91', '00', '0', '0', '1']

#complexity: column width changes,  some columns don't have values.
def parse_readelf_sections(readelfoutstr):
    output=[];
    for line in readelfoutstr.split('\n'):
        line=line.strip();
        if len(line)==0:
            continue;
        if ']' not in line:
            continue;
        splits=line.split(']')[1].split();
        #print 'parse_readelf_sections:'+line
        #['.strtab', 'STRTAB',   '00000000', '00e764', '000a91', '00', '0', '0', '1']
        #['NULL',    '00000000', '000000',   '000000', '00',     '0',  '0', '0']
        addr,offset,size=get_addr_offset_size(splits)
        item=ReadElfSectionItem(addr,offset,size);
        output.append(item);
    return output;
      
# Dynamic section at offset 0x2288 contains 16 entries:
  # Tag        Type                         Name/Value
 # 0x00000001 (NEEDED)                     Shared library: [HpMp3DecoderModule.so.1.0]
 # 0x00000001 (NEEDED)                     Shared library: [Mp3DecoderModule.so.1.0]
 # 0x00000004 (HASH)                       0x0
 # 0x00000005 (STRTAB)                     0x22c      
def parse_dynamic_section(readelfoutstr):
   output=[]
   for line in readelfoutstr.split('\n'):
      line=line.strip();
      if len(line)==0:
         continue;
      if 'Shared library:' in line:
         splits=line.split('[');
         if len(splits)>=2:
            output.append(splits[1].split(']')[0]);
   return output;
   
def run_hexagon_readelf(objectfilename, options):
    readelfitems=[];
    try:
        print 
        print '>>> Running hexagon-readelf on ' + objectfilename + ' options: '+ options
        f_hexagon=subprocess.check_output(['hexagon-readelf', options, objectfilename],stderr=sys.stderr)
        print '>>> Done hexagon-readelf, parsing readelf output.'
        if 'S' in options:
            readelfitems=parse_readelf_sections(f_hexagon);
        elif 'd' in options:
            readelfitems=parse_dynamic_section(f_hexagon);
        else:
            readelfitems=parse_readelf_symbols(f_hexagon);
        print '>>> Done parsing'
    except IOError as e:
        print ">>> IOError: file operation on temp output file for hexagon-readelf failed: "+str(e)
        sys.exit()
    except subprocess.CalledProcessError as e1:
        print ">>> Error: CalledProcessError: executing hexagon-readelf caused error: "+str(e1)
        sys.exit()

    return readelfitems;
    
def print_arr(a):
    for i in a:
        print str(i)

def list_all_syms(symItems):
   return [item.name for item in symItems if item.name!=''];
def list_und_syms(symItems):
   return [item.name for item in symItems if item.index==UND and item.name!=''] ; 

def find_sym_item(symitemlist, symname):
   for i in symitemlist:
      if i.name==symname:
         return i;
   return None;
   
def find_file_offset_of_sym(symaddr, secitemlist):
   for sec in secitemlist:
      if symaddr >= sec.address and symaddr < sec.address+sec.size:
         return sec.offset+(symaddr-sec.address);
   return 0;
   
def get_sym_pointed_data(elffilename, symname, symitemlist, secitemlist):
   elffile=None;
   #open file
   try:
       elffile=open(elffilename,'rb')
   except IOError as e:
       sys.exit('Error: file '+elffilename+' could not be opened. Exiting.'+str(e));
   
   symitem=find_sym_item(symitemlist, symname); #ReadElfSymbolItem:
   if None==symitem:
      print '>>> Symbol '+symname+' not found in '+elffilename
      return None;
      
   #ReadElfSectionItem
   fileoffset=find_file_offset_of_sym(symitem.address, secitemlist);
   
   elffile.seek(fileoffset,0);
   str=elffile.read(symitem.size);
   if (str==''):
      print '>>> Error: Elf file '+elffilename+' does not have symbol '+symname+': something is not right'
   
   elffile.close();
   
   return str;
  
