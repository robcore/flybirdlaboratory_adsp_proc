#Script to check timestamp and QURT_system state directly from dump and elf.. 

import sys
import os

def time_check(name,start_addr):
    if os.path.isfile(name):
        
        qcom = []
        engg = []
        qdss = []
        limit = 1
        time_found = False
        searchfile = open(name, "rb")
        index = int(start_addr,0)
        #print "index:",index
        searchfile.seek(index)
        for line in searchfile:
            if time_found:
                break
            elif "Q6_BUILD" in line and (len(qcom)<1 or len(engg)<1):
                if "M8610" in line:
                    limit = 0
                words = line.split('\x00')
                for word in words:
                    #print word
                    if "QCOM time:Q6_BUILD_TS_" in word:
                        qcom.append(word.split("QCOM time:Q6_BUILD_TS_")[1])
                    if "ENGG time:Q6_BUILD_TS_" in word:
                        engg.append(word.split("ENGG time:Q6_BUILD_TS_")[1])
                    if len(qcom)>0 and len(engg)>0 and len(qdss)>limit:
                        time_found = True
                        break
            elif "QDSS_TAG" in line:
                words = line.split('\x00')
                for word in words:
                    if "QDSS_TAG" in word:
                        tag = word.split("QDSS_TAG_")[1]
                        if len(tag)==10:
                            tag = tag+"00"
                        qdss.append(tag)
                    if len(qcom)>0 and len(engg)>0 and len(qdss)>limit:         #Two tags in case of Ram Dump
                        time_found = True
                        break

                    #if "Q6_BUILD" in word:
                        #f.write(word+"\n")
                        #string.append(word)
        
        searchfile.close()
            
        if (len(qcom)==0 or len(engg)==0) and len(qdss)==0:
            print "Time tag not found for "+name
            return False                # Timestamp not given in file
            sys.exit()
        else:
            #print qdss
            return engg,qcom,qdss,limit
    else:
        print "Given file name doesn't exist, please re-enter "


def time_stamp_check(dump,elf,sensor_elf,start_addr):
    third_arg=sensor_elf
    #Uncomment below lines to check for file existence 
    # if not os.path.isfile(dump):
        # print "File doesn't exist!"
        
    name= dump
    elf_match=False
    sensor_match=False
    elf_qdss=""
    elf_time=""
    dump_time = time_check(name,start_addr)
    #qcom_build = dump_time[0][0].split("_")[-1]
    #without tag issue
     
    size=True
    if elf:
        size_elf = os.path.getsize(elf)
        if size_elf<12870687:
            size=False
    if elf and size and os.path.isfile(elf):
        elf_time = time_check(elf,"0")
        if not elf_time:
            text = "\nNot able to find time stamp in elf!!"
            print text
        elif elf_time[0][0] == dump_time[0][0] or elf_time[1][0] == dump_time[1][0]:
            elf_match=True
    elif not size:
        text = "\nElf is stripped one please provide unstripped elf..now checking for sensor elf. Please wait..."
        print text
    if sensor_elf:
        elf_qdss = time_check(sensor_elf,"0")
        if not elf_qdss:
            text = "\nNot able to find time stamp in sensor elf!!"
            print text
        elif dump_time[2][1][:-3] == elf_qdss[2][0][:-3]:             #not the match upto second
            sensor_match=True
    print dump_time,elf_time,elf_qdss
    return elf_match,sensor_match





