import sys
if (len(sys.argv) < 4):
    exit()
lines = []

readfile = open(sys.argv[1],"r")
for line in readfile:
    lines.append(line)
writefile = open(sys.argv[2],"a")
writefile.write("\nLast few ULogs:\n--------------\n")
for line in lines[(len(lines)-int(sys.argv[3])):]:
    writefile.write(line)
readfile.close()
writefile.close()
