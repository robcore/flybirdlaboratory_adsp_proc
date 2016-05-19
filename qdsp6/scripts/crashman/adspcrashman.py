# ::*****************************************************************************************************************************************************************
# :: Filename: adspcrashman.py
# ::
# :: Version : External_Release_1.14
# ::
# :: Usage:
# :: 	adspcrashman.py -t Target_Name[8994/8974/9x25/8x10/9x35/8084] -b EBI_Binary_File -o Output_folderpath -c CRM_Buildpath -e CustomerprovidedOBJPath[Optional]
# ::
# :: Example:
# :: 	adspcrashman.py  -t 8974 -b C:\Dropbox\DDRSCO.bin -o C:\dropbox\123456 -c C:\YUG_M8960AAAAANAZL1047\lpass_proc -e C:\Dropbox\8k_dumps\
# ::
# ::*****************************************************************************************************************************************************************
import os
import re
import subprocess
import sys
import time
import datetime
import fnmatch
import shutil, errno
VALID_TARGETS=["8994","8974","9x25","9x35","8x10","8084","8x26","8996","8952","8992","8976"]

usage = "\n\
python adspcrashman.py -t[arget] <TARGET> -d[ump] <DumpFile> -o[utput] <Output_Path> -b[uild] <CRM_Buildpath> -e[lf] <CustomerprovidedOBJPath[Optional]> -l[ite] -sofile <dynamic SO files Path[Optional] -smmu32/64 <32/64 bit vmlinux path[Optional]>\n\n\
Mandatory Arguments:\n\
   -t, --target    Targets Supported on Crashman \n \
  -d, --dump      Dump File along with path \n \
  -o, --output    Output folder \n \
  -b, --build     ADSP Build Path Location\n\n\
For SLPI Image:\n\
   -s, --slpi      Enables SLPI image loading \n\n\
Optional Arguments:\n\
   -e, --elf              Customer ELF Location \n\
   -l, --lite             Crashman Lite Version(Only Dumps are loaded)\n\
   -sofile, --sofile      Provide dynamic So files location\n\
   -smmu32, --smmu32      Provide 32 bit vmlinux path\n\
   -smmu64, --smmu64      Provide 64 bit vmlinux path\n\
\n\nExample:\n\n\
  python adspcrashman.py -t 8994 -d C:\DDRCS0.BIN -o C:\output -b \\snowcone\builds698\PROD\ADSP.8994.2.6.1-00120-00374-1\adsp_proc\n\n\
Example with ELF argument: \n\
  python adspcrashman.py  -target 9x35 -dump C:\DDRCS0.BIN -output C:\output -build \\cone\builds634\PROD\ADSP.BF.2.4.1.c1-00021-M9635AAAAANAZL-1 -elf \\rover\hyd_dspfw\ADSP_Tools\TriageTeam\Users\Praveen\Testing\9x35\ELFS\n\n\
Example with -smmu64 argument: \n\
  python adspcrashman.py -t 8952 -o C:\Temp -d \\lab3079\Sahara\matting_171\DDRCS0.BIN -b \\snowcone\builds677\PROD\ADSP.8952.2.6-00107-00000-1 -smmu64 \\holi\builds539\TEST\LA.BR.1.3.1-27101-8952.1-1\LINUX\android\out\\target\product\msm8952_64\obj\KERNEL_OBJ\\vmlinux\n\n "

if len(sys.argv) < 9:
    print usage
    sys.exit()

Crashman_Version = "External_Release_1.14"
print "************************************"
print "*******Crashman Started*************"
print "************************************"
print "Crashman version          : ",Crashman_Version

try:
   import argparse
   from argparse import RawTextHelpFormatter
except ImportError:
   print 'Python Version is: ' + sys.version
   print 'Crashman requires Python version 2.7.6 and above.'
   print 'If you have Python version 2.7.6 installed, please check the environment path.' 
   sys.exit(0)
   
   
if sys.version:
   print "Python Version Installed  : ", ((sys.version.rstrip('\n')).split('(default')[0]).split(' ')[0]
   if sys.version_info[0] != 2 and sys.version_info[1] != 7:
       print "ERROR:: You are not using Python 2.7.6. Please use 2.7.6, preferably 2.7.6 and above"
       sys.exit(0)
else:
   print '\n\nERROR: Python not installed!!!'
   print 'Recommended Python Installation v2.7.6'
   print 'Crashman tested on Python versions- v2.7.6  v2.5.2  v2.6.2  v2.7.2  v3.0.1  v2.7.6'
   print 'If installed already, please verify if respective path added to PATH environment variable!!!\n\n'
   sys.exit(0)

tool_version = ''.join(['perl -v'])
proc = subprocess.Popen(tool_version, stdout=subprocess.PIPE, shell=True)
(out, err) = proc.communicate()
if out:
    try:
        if " (v" in out:
            perl_version =  out.split('(')[1].split(')')[0]
        elif "This is perl," in out:    
            perl_version =  out.split('This is perl,')[1].split('built')[0]
        else:
            perl_version = "Untested Perl Version"
        print "Perl Version Installed    :", perl_version
    except:
        print "Perl Version Installed    :"
else:
   print '\n\nERROR: Perl not installed!!!'
   print 'Recommended perl Installation v5.6.1'
   print 'Crashman tested on Perl versions- v5.10.1 , v5.6.1 , v5.8.7 , v5.12.4 , v5.14.2 '
   print 'If installed already, please verify if respective path added to PATH environment variable!!!\n\n'
   sys.exit(0)


parser = argparse.ArgumentParser(description=usage, formatter_class=RawTextHelpFormatter)  
parser.add_argument('-target','--target', help='TARGET: '+', '.join(VALID_TARGETS), dest='TARGET', action='store')
parser.add_argument('-dump','--dump', help="DUMPFILE: Please Provide Proper Dump File Location", dest='DUMPFILE', action='store')
parser.add_argument('-output','--output', help="OUTPUT: Please Provide Proper Output Path Location", dest='OUTPUT', action='store')
parser.add_argument('-build','--build', help="CRM: Please Provide Proper CRM Build Path Location", dest='BUILD', action='store')
parser.add_argument('-elf','--elf', default="",help="ELF: Please Provide Proper ELF Path Location", dest='ELF', action='store')
parser.add_argument('-lite','--lite',help="To Enbale Crashman Lite give -l or -lite",action='store_true')
parser.add_argument('-asha','--asha',help="To Enbale Crashman for ASHA give -a or -asha",action='store_true')
parser.add_argument('-gdb','--gdb',help="To Enbale GDB Simulator give -g or -gdb",action='store_true')
parser.add_argument('-slpi','--slpi',help="To Enable SLPI for 8996 give -s or -slpi",action='store_true')
parser.add_argument('-sofile','--sofile', default="",help="ELF: Please Provide Dynamic so Path Location", dest='SOFILE', action='store')
parser.add_argument('-fullload','--fullload', default="",help="Full Load: please provide full dump path", dest='FL',action='store')
parser.add_argument('-smmu32','--smmu32', help="vmlinux 32 bit: Please Provide Proper 32 bit vmlinux Path Location", dest='SMMU32', action='store')
parser.add_argument('-smmu64','--smmu64', help="vmlinux 64 bit: Please Provide Proper 64 bit vmlinux Path Location", dest='SMMU64', action='store')

opts = parser.parse_args()

smmu_32bt = opts.SMMU32
if not smmu_32bt: smmu_32bt=False
smmu_64bt = opts.SMMU64
if not smmu_64bt: smmu_64bt=False
targetid = opts.TARGET
INDumpPath = opts.DUMPFILE
CustomerPath = opts.ELF
if not CustomerPath: CustomerPath=False
SOFILE = opts.SOFILE
if not SOFILE: SOFILE=False
UniqueNumber="NotGiven"
crashman_lite = opts.lite
load_dump_full = opts.FL
if not load_dump_full: load_dump_full=False
asha_flag = opts.asha
gdb_flag  = opts.gdb
slpi_flag = opts.slpi

        
if load_dump_full!=False:
    if not os.path.isfile(load_dump_full+"\\load.cmm"):
        print "**************************************************************"
        print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
        print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
        print "**************************************************************"
        sys.exit(0)
    if not os.path.isfile(load_dump_full+"\\DDRCS0.BIN"):
        print "**************************************************************"
        print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
        print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
        print "**************************************************************"
        sys.exit(0)
    if not os.path.isfile(load_dump_full+"\\DDRCS1.BIN"):
        print "**************************************************************"
        print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
        print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
        print "**************************************************************"
        sys.exit(0)
    

if crashman_lite==True and gdb_flag==True:
    print "Crashman Lite and GDB are not concurrently supported. Please select any one option"
    sys.exit(0)
    
if not os.path.isfile(INDumpPath):
    print "Dump File is not accessible/available. Please Check the File Path."
    sys.exit(0)


i = datetime.datetime.now()
dateref = str("{0:0=2d}".format(i.month))+"_"+str("{0:0=2d}".format(i.day))+"_"+str(i.hour)+"h"+str(i.minute)+"m"+str(i.second)+"s"
if len(opts.OUTPUT) > 34:
    print "Output folder path length is too long. Please reduce the output path length"
OUTDumpPath = opts.OUTPUT+"\\Crashman_"+dateref+"\\Logs"
if not os.path.exists(OUTDumpPath):
    try:    
        os.makedirs(OUTDumpPath) 
        os.makedirs(OUTDumpPath+"\\Qurt_logs") 
        os.makedirs(OUTDumpPath+"\\temp") 
        os.makedirs(OUTDumpPath+"\\ulog") 
    except:
        print "Output Folder is not accessible. Please Give Proper Output path."
        sys.exit(0)
        
print "Crashman Output Folder    : ",OUTDumpPath
print "Processing Inputs Please Wait..."

dump_path=None
if os.path.isfile(INDumpPath):
    if "DDRCS0.BIN" in INDumpPath:
        dump_path = INDumpPath.split('\DDRCS0.BIN')[0]

flag = 0
if smmu_32bt!=False:
    command = '''pushd \\\\rover\hyd_dspfw\ADSP_Tools\linux-ramdump-parser-v2 & python ramparse.py  -a %s  -o %s   -v %s  --print-iommu-pg-tables'''%(dump_path,OUTDumpPath+"\\temp",smmu_32bt)
    print "Processing SMMU pagetable parsing... it might take 4-5 minutes. Please wait..."
    os.system(command)
    load_dump_full=dump_path
    if load_dump_full!=None:
        if not os.path.isfile(load_dump_full+"\\load.cmm"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
        if not os.path.isfile(load_dump_full+"\\DDRCS0.BIN"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
        if not os.path.isfile(load_dump_full+"\\DDRCS1.BIN"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
    else:        
        print "**************************************************************"
        print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
        print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
        print "**************************************************************"
        sys.exit(0)
    flag = 1
    
if smmu_64bt!=False:
    command = '''pushd \\\\rover\hyd_dspfw\ADSP_Tools\linux-ramdump-parser-v2 & python ramparse.py --64-bit -a %s  -o %s   -v %s  --print-iommu-pg-tables'''%(dump_path,OUTDumpPath+"\\temp",smmu_64bt)
    print "Processing SMMU pagetable parsing... it might take 4-5 minutes. Please wait..."
    os.system(command)
    load_dump_full=dump_path
    if load_dump_full!=None:
        if not os.path.isfile(load_dump_full+"\\load.cmm"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
        if not os.path.isfile(load_dump_full+"\\DDRCS0.BIN"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
        if not os.path.isfile(load_dump_full+"\\DDRCS1.BIN"):
            print "**************************************************************"
            print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
            print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
            print "**************************************************************"
            sys.exit(0)
    else:        
        print "**************************************************************"
        print "If you are using -smmu32/smmu64 crahman option , the dump argument given in crashman must point to complete ramdump.\n"
        print "Mandatory contents to be present in dump path - load.cmm, DDRCS0.BIN , DDRCS1.BIN"
        print "**************************************************************"
        sys.exit(0)
    flag = 1
    
if flag == 1:
    if not os.path.isfile(OUTDumpPath+"\\temp\\msm_iommu_domain_02.txt"):
        print "**************************************************************"
        print "Not able to generate SMMU pagetable mappings with provided dumps and vmlinux."
        print "Please provide matching vmlinux and dumps"
        print "**************************************************************"
        sys.exit(0)
    
input = OUTDumpPath+"\\temp\\version_check.txt"
f_out = open(input,"w")
Pythonversion = sys.version
Pythonversion1 = Pythonversion.split() 
f_out.write('Python Version Installed : v' + Pythonversion1[0] + '\n' )
f_out.write('Perl   Version Installed : ' + perl_version + '\n' )
f_out.write('Crashman Version         : '+ Crashman_Version + '\n')
f_out.write('VersionFileEnd\n')
f_out.close()
win = 0
if ".dmp" in INDumpPath:
    win = 1
elif ".tmp" in INDumpPath:
    win = 1

if win == 1:
    print "\n\n************************************"
    print "Windows Dumps Extraction Started...\n"
    command = '''dexter.exe /v /i %s /o %s /SelImg /Img1 ADSP'''%(INDumpPath,OUTDumpPath)
    os.system(command)
    INDumpPath=OUTDumpPath+"\\ADSP0.bin"
    print "\nWindows Dumps Extraction Done\n"
    print "************************************\n\n\n"
        
CRM_buildpath = opts.BUILD
if os.path.exists(CRM_buildpath+"\\adsp_proc"):
    CRM_buildpath = CRM_buildpath+"\\adsp_proc"
if os.path.exists(CRM_buildpath+"\\slpi_proc"):
    slpi_flag=True
    CRM_buildpath = CRM_buildpath+"\\slpi_proc"

if "slpi_proc" in CRM_buildpath:
    slpi_flag=True
    
if not os.path.exists(CRM_buildpath+"\\core"):
    print "ADSP Build Path is not accessible/available. Please Check the Build Path."
    sys.exit(0)

Temp_DIR = "C:\Temp"
if not os.path.exists(Temp_DIR):
    os.makedirs(Temp_DIR) 

CurrDirectory =  os.getcwd()
command = '''dir %s /D /-C >%s'''%(INDumpPath,OUTDumpPath+"\\temp\\binarylength.txt")
os.system(command)

command = '''perl Check_Ram_Size.pl %s'''%(OUTDumpPath+"\\temp\\binarylength.txt")
process = subprocess.Popen(command, stdout=subprocess.PIPE)
process.wait() 

if gdb_flag == True:
    bin = OUTDumpPath+"\\binarylength.txt"
    line1 = 0
    f_bin = open(bin,'r+')
    for line in f_bin:
        line1 = line
        break;
    f_bin.close()
    DUMP_SIZE_CHECK = 36700160 #Dump file check as 35MB
    if (((".bin" in INDumpPath) or (".BIN" in INDumpPath)) and (int(line1) > DUMP_SIZE_CHECK)):
        command = '''cd gdb & python gdbADSPcrashman.py %s %s %s %s %s'''%(targetid,INDumpPath,OUTDumpPath,CRM_buildpath,CustomerPath)
        os.system(command)
    else:
        print "Please provide proper dumps for GDB simulator"
    sys.exit(0)

command = '''python Start_Address.py  %s %s %s %s %s %s'''%(INDumpPath,OUTDumpPath+"\\temp\\adspstartaddr.txt",OUTDumpPath+"\\temp\\dumpformant.txt",OUTDumpPath+"\\temp\\binarylength.txt",targetid,slpi_flag)
process = subprocess.Popen(command, stdout=subprocess.PIPE)
process.wait() 

print "\nStarting T32 for further processing."
print "************************************"
t32_file = OUTDumpPath+"\\temp\\config_sim_usb.t32"
f_t32 = open(t32_file,'w+')
f_t32.write("OS=\n")
f_t32.write("ID=SIM_${2}            ; unique ID needed for temporary file name uniqueness\n")
f_t32.write("TMP="+OUTDumpPath+"\\temp"+"           ; T32 temp file names are prepended with the unique ID above\n")
f_t32.write("SYS=C:\T32                ; make system directory the same as the executable directory\n\n")
f_t32.write("SCREEN=\n")
f_t32.write("HEADER=${2}\n\n")
f_t32.write("; Ethernet on Host information \n")
f_t32.write("PBI=SIM\n")
f_t32.write("\n")
f_t32.write("; Printer settings\n")
f_t32.write("PRINTER=WINDOWS\n\n")
f_t32.write("; Screen fonts\n")
f_t32.write("SCREEN=\n")
f_t32.write("FONT=SMALL\n\n")
f_t32.close()

Path = "C:\\T32\\bin\\windows64"
if os.path.exists(Path):
    command = '''start C:\\T32\\bin\\windows64\\t32mqdsp6.exe -c %s, %s %s %s %s %s %s %s %s %s %s %s %s %s'''%(OUTDumpPath+"\\temp\\config_sim_usb.t32",CurrDirectory+"\\DSP_load_memorydump_crashman.cmm",targetid,UniqueNumber,INDumpPath,OUTDumpPath,CRM_buildpath,CurrDirectory,CustomerPath,crashman_lite,slpi_flag,asha_flag,SOFILE,load_dump_full)
    os.system(command)
else:    
    command = '''start C:\\T32\\t32mqdsp6.exe -c %s, %s %s %s %s %s %s %s %s %s %s %s %s %s'''%(OUTDumpPath+"\\temp\\config_sim_usb.t32",CurrDirectory+"\\DSP_load_memorydump_crashman.cmm",targetid,UniqueNumber,INDumpPath,OUTDumpPath,CRM_buildpath,CurrDirectory,CustomerPath,crashman_lite,slpi_flag,asha_flag,SOFILE,load_dump_full)
    os.system(command)


if asha_flag == True:
    file_check=OUTDumpPath+"\\temp\\dumpsloaddone.txt"
    while True:
        time.sleep(10) #wait for 1min for checking
        if os.path.exists(file_check):
            print "Dumps and ELF Loading Done!!!!!"
            break

    minutes=10
    dsp_check=OUTDumpPath+"\\temp\\DSPAnalysis.end"
    dsp_analy=OUTDumpPath+"\\DSPAnalysis.txt"

    cond = 0
    for i in range(0,minutes):
        time.sleep(60) #wait for 1min for checking
        if os.path.exists(dsp_check):
            cond = 1
            break
                
    if cond == 0:    
        f_dsp_check = open(dsp_check,'w+')
        f_dsp_analy = open(dsp_analy,'r+')
        for line in f_dsp_analy:
            f_dsp_check.write(line)
        f_dsp_analy.close()
        f_dsp_check.close()
    print "Searching for JIRA tickets"
    log=OUTDumpPath+"\\temp\\JiraLog.txt"
    command = '''python \\\\rover\hyd_dspfw\ADSP_Tools\TriageTeam\DD_Modular_Script\DD_module.py %s > %s'''%(OUTDumpPath,log)
    os.system(command)
    dsp_check=OUTDumpPath+"\\temp\\DSPOutput.complete"
    dsp_analy=OUTDumpPath+"\\temp\\DSPAnalysis.end"
    f_dsp_check = open(dsp_check,'w+')
    f_dsp_analy = open(dsp_analy,'r+')
    for line in f_dsp_analy:
        f_dsp_check.write(line)
    f_dsp_analy.close()
    f_dsp_check.close()
    
    print "Searching for JIRA tickets Done"

    
file_check=OUTDumpPath+"\\temp\\DSPAnalysis.end"
while True:
    time.sleep(10) #wait for 1min for checking
    if os.path.exists(file_check):
        if os.path.exists(OUTDumpPath+"\\AvailableLogs.txt"):
            os.rename(OUTDumpPath+"\\AvailableLogs.txt", OUTDumpPath+"\\temp\\AvailableLogs.txt")
        if os.path.exists(OUTDumpPath+"\\f3tokens_temp.txt"):
            os.rename(OUTDumpPath+"\\f3tokens_temp.txt", OUTDumpPath+"\\temp\\f3tokens_temp.txt")
        if os.path.exists(OUTDumpPath+"\\BAM.ulog"):
            os.rename(OUTDumpPath+"\\BAM.ulog", OUTDumpPath+"\\temp\\BAM.ulog")
        if os.path.exists(OUTDumpPath+"\\NPA Log.ulog"):
            os.rename(OUTDumpPath+"\\NPA Log.ulog", OUTDumpPath+"\\temp\\NPA Log.ulog")
        if os.path.exists(OUTDumpPath+"\\SLIMBUS.ulog"):
            os.rename(OUTDumpPath+"\\SLIMBUS.ulog", OUTDumpPath+"\\ulog\\SLIMBUS.ulog")
        if os.path.exists(OUTDumpPath+"\\search_op.json"):
            os.rename(OUTDumpPath+"\\search_op.json", OUTDumpPath+"\\temp\\search_op.json")
        break
