import sys
import os
import re

OutputPath    = sys.argv[1]

dump=OutputPath+"\\"+"DumpTimeStamp.txt"
try:
    if os.path.exists(dump):
        QCOM = []
        ENGG = []
        f_dump = open(dump,'r+')
        for line in f_dump:
            if "QCOM" in line:
                QCOM.append(line)
            if "ENGG" in line:
                ENGG.append(line)
        f_dump.close()        
    status = OutputPath+"\\"+"CheckDumpStatus.txt"
    f_status = open(status,'w')
    if QCOM[0] == QCOM[1] and ENGG[0] == ENGG[1]:
        f_status.write("1")
    else:    
        f_status.write("0")
    f_status.close()
except:
    print "File Not Exits DumpTimeStamp.txt"
    sys.exit()


