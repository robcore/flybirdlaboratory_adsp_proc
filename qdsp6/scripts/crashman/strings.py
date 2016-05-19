import sys
import re

if (len(sys.argv) < 3):
    exit()

readfile = open(sys.argv[1],"rb")
writefile = open(sys.argv[2],"a")
#with open(sys.argv[1],"rb") as readfile:
#    with open(sys.argv[2],"a") as writefile:
writefile.write("B::Analysis\n")

match1 = 0
match2 = 0
for line in readfile:
    #print line
    if "Q6_BUILD" in line:
        match = re.search(r'(QCOM time:Q6_BUILD[^\x00]+)\x00',line)
        if match:
            if match1 == 0:
                #print match.group(1)
                writefile.write(match.group(1)+"\n")
                match1 = 1
        match = re.search(r'(ENGG time:Q6_BUILD[^\x00]+)\x00',line)
        if match:
            if match2 == 0:
                # print match.group(1)
                writefile.write(match.group(1)+"\n")
                match2 = 1
    if match1 == 1:
        if match2 == 1:
            break;
    
