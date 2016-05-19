import sys
import re

if (len(sys.argv) < 2):
    exit()

readfile = open(sys.argv[1],"rb")
writefile = open(sys.argv[2],"a")
#with open(sys.argv[1],"rb") as readfile:
#    with open(sys.argv[2],"a") as writefile:

match1 = 0
match2 = 0
for line in readfile:
    #print line
    if "OEM_IMAGE_UUID_STRING=Q_SENTINEL_{" in line:
        words = line.split('\x00')
        for word in words:
            if "OEM_IMAGE_UUID_STRING=Q_SENTINEL_{" in word:
                writefile.write(word.split("}_")[1])
                writefile.write('\n')
                break;
        break;
        
