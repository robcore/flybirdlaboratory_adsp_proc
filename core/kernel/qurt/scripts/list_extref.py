import os, sys, re, subprocess, optparse

#globals
libs=[]
undefdict = dict()
defdict_obj = dict()
defdict_arch = dict()
defdict_sect = dict() 
defdict_arch_obj = dict()   
size_obj = dict()
size_sym = dict()
size_arch = dict()
size_data = dict() #(.data .data.*), (.sdata .sdata.*)
size_text = dict() #(.text .text.*)
size_bss = dict() #(.bss .bss.* ) (.sbss .sbss.*)
size_common = dict() #(COMMON) (.scommon .scommon.*)
size_rodata = dict() #(.rodata .rodata.*)
size_other = dict() # Any unaccounted section

def parseArchive(archive_str, archive):

    #get archive match, save archive
    archpattern = re.compile('^(.*):\s')
    archmatch = archpattern.match(archive_str)

    object = None
    current_section = ""
    size_arch[archive] = 0
    size_data[archive] = 0 #(.data .data.*), (.sdata .sdata.*)
    size_text[archive] = 0 #(.text .text.*)
    size_bss[archive] = 0 #(.bss .bss.*) (.sbss .sbss.*)
    size_common[archive] = 0 #(COMMON) (.scommon .scommon.*)
    size_rodata[archive] = 0 #(.rodata .rodata.*)
    size_other[archive] = 0 # Any unaccounted section

    for archline in archive_str.split("\n"):
        objpattern = re.compile('^(.*\.o):\s')
        sympattern = re.compile('(\S{8}){1}\s+(\S*\s+\S*)\s+?(\S+){1}\s+(\S{8}){1}\s+(\S+){1}\s*')
        objmatch = objpattern.match(archline)
        symmatch = sympattern.match(archline)
        if objmatch:
            current_section = ""
            object = objmatch.group(1)
            size_obj[object] = 0
            size_data[object] = 0 #(.data* .sdata*)
            size_text[object] = 0 #(.text*)
            size_bss[object] = 0 #(.bss .bss.*) (.sbss .sbss.*)
            size_common[object] = 0 #(COMMON) (.scommon .scommon.*)
            size_rodata[object] = 0 #(.rodata*)
            size_other[object] = 0 # Any unaccounted section
        elif symmatch and object:
            if symmatch.group(3) != "*UND*":
                current_section = symmatch.group(3)
            if (((str(archive) in libs) or 
                (str(archive)+":"+object in libs) or 
                (str(archive)+":"+object+"("+current_section+")" in libs) or
                (object+"("+current_section+")" in libs) or
                (str(archive)+"("+current_section+")" in libs) or
                (object in libs) or
                ("("+symmatch.group(3)+")" in libs))):
                if ((symmatch.group(5) != symmatch.group(3)) and ("df" not in str(symmatch.group(2)))):
                    if ((symmatch.group(3) == "*UND*")):
                        referencers = set()
                        objstr = object
                        if archive:
                            objstr = archive + ":" + object
                        if undefdict.has_key(symmatch.group(5)):
                            referencers = set(undefdict[symmatch.group(5)])
                        referencers.add(objstr)
                        undefdict[symmatch.group(5)]=referencers
                    else:
                        defdict_obj[symmatch.group(5)]=object
                        defdict_sect[symmatch.group(5)]=current_section
                        if archive:
                            defdict_arch[symmatch.group(5)]=archive
                            
                            if archive not in defdict_arch_obj:
                                defdict_arch_obj[archive] = list()
                            if object not in defdict_arch_obj.get(archive):
                                defdict_arch_obj[archive].append(object)
                            
                            if (('.data' in current_section)or('.sdata' in current_section)):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_data[archive] = size_data[archive] + size_of_symbol
                            elif('.text' in current_section):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_text[archive] = size_text[archive] + size_of_symbol
                            elif(('.bss' in current_section)or('.sbss' in current_section)):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_bss[archive] = size_bss[archive] + size_of_symbol
                            elif('COM' in current_section):
                                size_of_symbol = int(symmatch.group(1).split()[0],16)
                                size_common[archive] = size_common[archive] + size_of_symbol
                            elif('.rodata' in current_section):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_rodata[archive] = size_rodata[archive] + size_of_symbol
                            else:
                                size_of_symbol = int(symmatch.group(4),16)
                                size_other[archive] = size_other[archive] + size_of_symbol

                            size_arch[archive] = size_arch[archive] + size_of_symbol
                        else:
                            if (('.data' in current_section)or('.sdata' in current_section)):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_data[object] = size_data[object] + size_of_symbol
                            elif('.text' in current_section):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_text[object] = size_text[object] + size_of_symbol
                            elif(('.bss' in current_section)or('.sbss' in current_section)):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_bss[object] = size_bss[object] + size_of_symbol
                            elif('COM' in current_section):
                                size_of_symbol = int(symmatch.group(1).split()[0],16)
                                size_common[object] = size_common[object] + size_of_symbol
                            elif('.rodata' in current_section):
                                size_of_symbol = int(symmatch.group(4),16)
                                size_rodata[object] = size_rodata[object] + size_of_symbol
                            else:
                                size_of_symbol = int(symmatch.group(4),16)
                                size_other[object] = size_other[object] + size_of_symbol

                            size_obj[object] = size_obj[object] + size_of_symbol
                        size_sym[symmatch.group(5)] = size_of_symbol

# Main function that prints object references
if __name__ == "__main__":
    usage = "usage: %prog [options]\nExample:\npython scripts\\footprint\\%prog -l ..\\install\\ADSPv5MP\\lib -l ..\\build\\ADSPv5MP\\libs\\qurt\\src -l ..\\build\\ADSPv5MP\\kernel\\asm -l build\\ADSPv5MP\\qurt_island_t1 -l ..\\build\\ADSPv5MP\\libs\\timer\\asm -l ..\\build\\ADSPv5MP\\libs\\qurt\\asm -l C:\\Qualcomm\\HEXAGON_Tools\\5.0.07\\dinkumware\\lib -s island.ispec -i island_ignore.txt -a island_api.txt"
    parser = optparse.OptionParser(usage=usage)
    parser.add_option('-s', '--spec', dest="spec", action="append", help="spec file to identify libs and objects")
    parser.add_option('-o', '--libs', dest="libs", action="append", default=[], help="specify an object or library")
    parser.add_option('-l', '--location', dest="locations", action="append", default=[], help="location to to find objects and libraries from command line and spec file (optional)")
    parser.add_option('-i', '--ignore', dest="ignore", action="append", default=[], help="symbols to ignore, or file with symbols to ignore (1 per line)")
    parser.add_option('-f', '--feedback', dest="feedback", action="store", default="", help="generate files for feedback, defined.txt and undefined.txt in the directory specified")
    parser.add_option('-t', '--tools', dest="toolsver", action="store", default="5.1.04", help="hexagon version number to find objdump (optional)")
    parser.add_option('-a', '--api', dest="api", action="append", help="list of API that should be defined in Objects and libraries that are specified (optional)")
    parser.add_option('-v', '--verbose', dest="verbose", action="store_true", default=False, help="print everything (optional)")
    parser.add_option('-e', '--executable', dest="exestr", action="store", default="", help="explicit objdump executable")
    parser.add_option('-d', '--debug', dest="debug", action="store_true", default=False, help="experimental")
    (options, args) = parser.parse_args(sys.argv)

    #setup parameters
    ispec = options.spec
    libs = options.libs
    locations = options.locations
    ignore = options.ignore
    default_tools_version = options.toolsver
    feedback_dir = options.feedback
    api = options.api
    verbose = options.verbose
    exestr = options.exestr
    debug = options.debug
    
    #where to find objdump
    if exestr == "":
        if os.name == 'posix':
            default_tools_root = os.path.join('/pkg/qct/software/hexagon/releases/tools',default_tools_version)
        elif os.name == 'nt':
            default_tools_root = os.path.join(os.path.realpath('C:/Qualcomm/HEXAGON_Tools'),default_tools_version)
        exestr = os.path.join(default_tools_root,"gnu/bin/hexagon-objdump")
    else:
        exestr = os.path.realpath(exestr)

    #read in any and all ispec files, add libs to libs list
    if ispec:
        for specfile in ispec:
            if os.path.isfile(specfile):
                f = file(specfile) 
                for line in f: 
                    comment_pattern = re.compile('^#')
                    lib_pattern = re.compile('\**(.*)(\s+)\**(.*)(\s+)\**(.*)\s*')
                    line = line.strip() 
                    comment_match = comment_pattern.match(line)
                    lib_match = lib_pattern.match(line)
                    if comment_match:
                        continue
                    elif lib_match:
                        libstr = ""
                        if lib_match.group(1) != '':
                            if lib_match.group(3) != '':
                                libstr = lib_match.group(1)+':'+lib_match.group(3)
                            else:
                                libstr = lib_match.group(1)
                        elif lib_match.group(3) != '':
                            libstr = lib_match.group(3)
                        if lib_match.group(5) != '':
                            libstr += "("+lib_match.group(5)+")"
                        libs.append(libstr)
                f.close()
            else:
                print "ispec file does not exist: "+specfile

    if len(libs) < 1:
        print "No Libs or Objects have been specified."
        exit(-1)

    #if api list specified, read in list of API that needs to be supported in island
    apis = set()
    if api:
        for apifile in api:
            if os.path.isfile(apifile):
                f = file(apifile) 
                for line in f: 
                    apis.add(line.strip())
                f.close() 
            else:
                apis.add(apifile.strip())

    #if ignore list is specified, read symbols which will be defined to be ignored.
    if ignore:
        for ignorefile in ignore:
            if os.path.isfile(ignorefile):
                f = file(ignorefile) 
                for line in f: 
                    defdict_obj[line.strip()]="ignorelist"
                f.close() 
            else:
                defdict_obj[ignorefile]="ignorelist"

    i=0
    libfiles=set()
    while(i<len(libs)):
        sectiontemp = libs[i].split('(',1)
        section=None
        if len(sectiontemp)>1:
            section=sectiontemp[1]
        temp = sectiontemp[0].split(":")
        obj=''
        #if first is a drive letter
        if len(temp[0]) == 1:
            file = temp[0]+":"+temp[1]
            if len(temp) > 2:
                obj = temp[2]
        else:
            file = temp[0]
            if len(temp) > 1:
                obj = temp[1]
        #find path
        if not os.path.isfile(file):
            for loc in locations:
                found = False
                fullpathlib = os.path.join(loc,file)
                if os.path.isfile(fullpathlib):
                    if obj:
                        libs[i]=fullpathlib+":"+obj
                    else:
                        libs[i]=fullpathlib
                    libfiles.add(fullpathlib)
                    found = True
                    break
            #if not found:
                #print "File could not be found: "+file
        else:
            libfiles.add(file)
        if section:
            libs[i] += "("+section
        i+=1

    libfiles = set(libfiles)
    for libfile in libfiles:
        command=[exestr, "-t", libfile]
        p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()
        parseArchive(out, libfile);

    undefined = set(undefdict.keys())
    defined = set(defdict_obj.keys())

    if verbose:
        print "################################################################################"
        print "# Defined Symbols                                                              #"
        print "################################################################################"
        
        for sym in sorted(defined):
            callers_str = "Caller:"
            if undefdict.has_key(sym):
                first = True
                for obj in undefdict[sym]:
                    if first:
                        callers_str += "\t"+obj
                        first = False
                    else:
                        callers_str += "\n\t"+obj
            else:
                callers_str += " Local or None"
            symsize = 0
            if sym in size_sym:
                symsize = size_sym[sym]
            print "Symbol:\t"+sym + " (" + str(symsize) +"b)"
            def_str = "Defined: "
            if sym in defdict_arch:
                def_str = def_str + defdict_arch[sym]
            print def_str + ":" + defdict_obj[sym]
            print callers_str
            print "--------------------------------------------------------------------------------"
        print "\nTotal: "+str(len(defined))+"\n"

        objset = set(defdict_obj.values())
        for file in sorted(size_arch, key=size_arch.get, reverse=True):
            print "\n%-69.69s: %.2f kb" % (str(file)[-69:], float(size_arch[file])/1024)
            if file in defdict_arch_obj:
                #for obj in defdict_arch_obj[file]:
                for obj in sorted(defdict_arch_obj[file]):
                    if obj in objset:
                        print "    " + obj + ":"
                        for sym in defdict_obj:
                            if defdict_obj[sym] == obj:
                                print "        %-56.56s: %s b" % (sym[-56:], str(size_sym[sym]))

    if api:
        print "################################################################################"
        print "# Unsupported API                                                              #"
        print "################################################################################"
        for sym in (apis - defined):
            print sym
        print "\nTotal: "+str(len(apis - defined))

        objects=[]
        for sym in apis:
            symobj="*"
            if sym in defdict_obj:
                symobj=defdict_obj[sym]
            symarch="*"
            if sym in defdict_arch:
                symarch=defdict_arch[sym]
            symsect="*"
            if sym in defdict_sect:
                symsect=defdict_sect[sym]
            objstr = symarch+" "+symobj+" "+symsect
            if objstr not in objects:
                objects.append(objstr)


        appended = True
        while appended:
            appended = False
            for objstr in objects:
                temp=[]
                obj = objstr.split(" ")[1]
                for sym in undefdict:
                    #if obj in undefdict[sym]:
                    if [s for s in undefdict[sym] if obj in s]:
                        temp.append(sym)
                for sym in temp:
                    symobj="*"
                    if sym in defdict_obj:
                        symobj=defdict_obj[sym]
                    symarch="*"
                    if sym in defdict_arch:
                        symarch=defdict_arch[sym]
                    symsect="*"
                    if sym in defdict_sect:
                        symsect=defdict_sect[sym]
                    objstr = symarch+" "+symobj+" "+symsect
                    if objstr not in objects:
                        objects.append(objstr)
                        appended = True


        print "required: "
        for obj in sorted(objects):
            print obj
            
    if feedback_dir != "":
        def_out = os.path.join(feedback_dir,"defined.txt")
        undef_out = os.path.join(feedback_dir,"undefined.text")
        def_fh=open(def_out, 'w+')
        undef_fh=open(undef_out, 'w+')
        for sym in (defined):
            def_fh.write(sym+"\n")
        for sym in (undefined - defined):
            undef_fh.write(sym+"\n")

    undef_total=len(undefined - defined)
    if undef_total > 0:
        print "################################################################################"
        print "# Undefined Island Symbols                                                     #"
        print "################################################################################"
        for sym in (undefined - defined):
            callers_str = "Caller:"
            first = True
            for obj in undefdict[sym]:
                if first:
                    callers_str += "\t"+obj
                    first = False
                else:
                    callers_str += "\n\t"+obj
            print "Symbol:\t"+sym
            print callers_str
            print "--------------------------------------------------------------------------------"
        print "\nTotal Undefined: "+str(undef_total)+"\n"

    print "################################################################################"
    print "# Island Footprint                                                             #"
    print "################################################################################"
    total=0
    all_sizes = size_arch
    for obj in sorted(size_obj, key=size_obj.get, reverse=True):
        if os.path.isfile(obj):
            all_sizes[obj] = size_obj[obj]
    for file in sorted(all_sizes, key=all_sizes.get, reverse=True):
        total+=all_sizes[file]
        print "\n\n"
        print "%s: %.2f kb" % (file, float(all_sizes[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(.data* .sdata*)")[-56:], float(size_data[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(.text*)")[-56:], float(size_text[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(.bss* .sbss* )")[-56:], float( size_bss[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(COMMON .scommon*)")[-56:], float( size_common[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(.rodata*)")[-56:], float(size_rodata[file])/1024)
        print "%   -56.56s: %.2f kb" % (str("(other sections)")[-56:], float(size_other[file])/1024)

    print "\nTotal: %.2f kb\n" % (float(total)/1024)
    sys.exit(undef_total)


