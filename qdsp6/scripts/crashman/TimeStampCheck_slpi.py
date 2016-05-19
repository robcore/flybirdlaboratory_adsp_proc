import sys
import os
import re

OutputPath    = sys.argv[1]

dump=OutputPath+"\\"+"DumpTimeStamp.txt"
try:
    if os.path.exists(dump):
        f_dump = open(dump,'r+')
        line1 = f_dump.readline()
        line2 = f_dump.readline()
    status = OutputPath+"\\"+"CheckDumpStatus.txt"
    f_status = open(status,'w')
    if line1 == line2:
        f_status.write("1")
    else:    
        f_status.write("0")
    f_status.close()
except:
    print "File Not Exits DumpTimeStamp.txt"
    sys.exit()


