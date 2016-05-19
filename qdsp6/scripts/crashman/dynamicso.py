import os
import re
import subprocess
import sys
import time
import datetime
import fnmatch
import shutil, errno
from os import walk

log_mask = 1

def build_from_id(id):
    build=""
    output = subprocess.Popen(["//sun/CRMTools/Smart/nt/bin/Findbuild.exe","*"+id+"*"],stdout = subprocess.PIPE).communicate()[0]
    builds = output.split("\r\n\r\n\r\n")
    for build in builds:
        if build and ("\nStatus:         Completed" in build or "\nStatus:         Approved" in build):
            build = build.split("Location:")[1].split("\r\n")[0].strip()
            break
    return build

def GetBuildID(timestamp):
    buildid = None
    if "MSM8952" in timestamp:
        if "1.0" in timestamp:
            buildid=timestamp.split(".0")[0]
            buildid=buildid+".0"
        else:    
            buildid = temp2.split('_')[0]
    return buildid    
    
    
def GetStartAddress(list,OutputPath):
    log=OutputPath+"\\temp\\soaddress.txt"
    Addr=None
    if "_unstrip" in list:
        list = list.split("_unstrip")[0]
    elif "_unsigned" in list:
        list = list.split("_unsigned")[0]
    else:
        list = list.split(".")[0]
        
    try:
        if os.path.exists(log):
            f_log = open(log,'rb')
            for line in f_log:
                line=line.rstrip('\n').rstrip('\r')
                if list in line:
                    temp = line.split(" Start address: ")[1]
                    temp1 = temp.split(",")[0]
                    Addr = temp1
                    print list,Addr
                    break
    except:
        print "File Not Exits soaddress.bin"
    
    return Addr 

def GetFileNameExtension(soname,dynamicpath,OutputPath,SoNameList):

    ext=None
    for line in SoNameList:
        line=line.rstrip('\n').rstrip('\r')
        if soname in line:
            print soname,line
            if ".so" in line:
                ext = line.split('line')[-1]
                if "unstrip" in ext:
                    break
    return ext
    
def GetTimeStamp(file,name,DynamicSOList_temp):
    TS = []
    try:
        if os.path.exists(file):
            for list in DynamicSOList_temp:
                if list in name:
                    soname = list
                    break
            f_file = open(file,'rb')
            for line in f_file:
                if "Q6_BUILD_TS_Q6_BUILD_TS" in line:
                    if soname in line:
                        temp = line.split(soname)
                        for list in temp:
                            if "Q6_BUILD_TS_Q6_BUILD_TS" in list:
                                TS.append(list.replace('\x00',''))
            f_file.close()
    except:
        print "File Not Present"+file    
    return TS
    
def main():
    OutputPath  = sys.argv[1]
    crmpath     = sys.argv[2]
    dynamicpath = sys.argv[3]
    if dynamicpath == "False":
        dynamicpath = crmpath
    log=OutputPath+"\\temp\\soaddress.txt"
    if log_mask==1:
        error_log = OutputPath+"\\temp\\errorlog.txt"
        f_error = open(error_log,'a+')
    DynamicSOList=[]
    DynamicSOList_temp=[]
    SoNameList = []
    for (dirpath, dirnames, filenames) in walk(dynamicpath):
        SoNameList.extend(filenames)
        break    
    try:
        if os.path.exists(log):
            f_log = open(log,'rb')
            for line in f_log:
                if " Start address: " in line:
                    line = line.rstrip('\n').rstrip('\r')
                    temp1 = line.split("\"")[1]
                    if "./" in temp1:
                        soname = temp1.split("./")[1].split(".")[0]
                    else:
                        soname = temp1.split(".")[0]
                    DynamicSOList_temp.append(soname)
                    
            cmm=OutputPath+"\\temp\\loaddynmaic.cmm"
            f_cmm = open(cmm,'w+')
            load=OutputPath+"\\DynamicSoLoaded.txt"
            f_load=open(load,'w+')
            unload=OutputPath+"\\DSPAnalysis.txt"
            f_unload=open(unload,'a+')
            f_unload.write("\n\nDynamic So's Not Loaded\n")
            f_unload.write("==========================\n")
            first = 0

            print DynamicSOList_temp
            for soname in DynamicSOList_temp:
                print "Soname:"+soname
                list = GetFileNameExtension(soname,dynamicpath,OutputPath,SoNameList)
                print list
                if list != None:
                    if os.path.isfile(dynamicpath+"\\"+list):
                        ts_dump = []
                        ts_so_file = []
                        if  os.path.isfile(OutputPath+"\\slpi_Dump.bin"):
                            ts_dump = GetTimeStamp(OutputPath+"\\slpi_Dump.bin",list,DynamicSOList_temp)
                        if  os.path.isfile(OutputPath+"\\Adsp_Dump.bin"):
                            ts_dump = GetTimeStamp(OutputPath+"\\Adsp_Dump.bin",list,DynamicSOList_temp)
                        ts_so_file = GetTimeStamp(dynamicpath+"\\"+list,list,DynamicSOList_temp)
                        print ts_dump
                        print ts_so_file
                        res = cmp(ts_dump,ts_so_file)
                        print res
                        if res == 0:
                            f_cmm.write("area.select Crashman\n")
                            Addr = GetStartAddress(list,OutputPath)
                            if Addr != None:
                                f_cmm.write("print \"Dynamic Object Loading: "+dynamicpath+"\\"+list+"\"\n")
                                f_cmm.write("d.load.elf "+dynamicpath+"\\"+list+" "+Addr+" /nocode /noclear\n")
                                f_cmm.write("print \"Dynamic Object Loading: Done"+"\"\n")
                                if first == 0:
                                    f_load.write("Dynamic Loaded So's\n")
                                    f_load.write("==========================\n\n")
                                    first = 1
                                f_load.write(dynamicpath+"\\"+list+"\n")
                            else:
                                f_unload.write(dynamicpath+"\\"+list+"\n")
                        else:
                            f_unload.write("Mismatched Time Stamp "+dynamicpath+"\\"+list+"\n")
                    else:
                        f_unload.write(dynamicpath+"\\"+list+"\n")
                else:
                    f_unload.write(dynamicpath+"\\"+soname+"\n")
                
                
            f_log.close()
            f_cmm.close()
            f_unload.close()
            f_load.close()
                    
    except:
        print "File Not Exits Adsp_Dump.bin"
        if log_mask==1:f_error.write("File Not Exits Adsp_Dump.bin")
        sys.exit()
    if log_mask==1:
        f_error.close()

if __name__ == '__main__':
  main()
