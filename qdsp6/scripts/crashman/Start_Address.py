import sys
import re
import os.path
import binascii

#Function to check for a string in the range of 1000 bytes from provided index:
def is_string(file,index,string):
    length = len(string)
    for distance in range(1000):
        file.seek(index+distance)
        if string == file.read(length):return True
    return False
    

    
input=str(sys.argv[1])
output=str(sys.argv[2])
output1=str(sys.argv[3])
output2=str(sys.argv[4])
TargetName=str(sys.argv[5])
extension = os.path.splitext(input)[1]
sensor = str(sys.argv[6])
f4 = open(input,"r")
data = f4.read(4)
f4.close()
if extension == "":
	if binascii.hexlify(data) == "7f454c46":
		extension = ".ELF"

address = "0x0"

if (extension == ".elf" or extension == ".ELF"):
		f1 = open(output1, 'w')
		sys.stdout = f1
		print "2"
		sys.stdout = sys.__stdout__
		f1.close()
		f4 = open(input,"r")
		data = f4.read(4)
		f4.seek(60)
		s1=binascii.hexlify(f4.read(1))
                s2=binascii.hexlify(f4.read(1))
                s3=binascii.hexlify(f4.read(1))
                s4=binascii.hexlify(f4.read(1))
                address = "0x"+s4+s3+s2+s1
                f4.close()
else:
		f1 = open(output1, 'w')
		sys.stdout = f1
		print "1"
		sys.stdout = sys.__stdout__
		f1.close()



f3 = open(output2, 'r')
s = f3.read()
s1=( int (s)/1048576)
s1=(s1*1048576)

print "Please wait, finding start address..."

i=0x0
check_2_0_builds = 0
f = open(input, 'rb')
if (TargetName == "8994" or TargetName == "8996" or TargetName == "8992" or TargetName == "8952" or TargetName == "8976" or TargetName == "9x35"):
    key=f.read(28)
else:
    key=f.read(32)
f.seek(0x40)
key1=f.read(4)
if (TargetName == "8994" or TargetName == "8996" or TargetName == "8992" or TargetName == "8952" or TargetName == "8976" or TargetName == "9x35"):
    list=[0x00,0xc0,0x00,0x78,0x06,0x40,0x00,0x67,0x00,0xc5,0x0,0x78,0x12,0xc0,0x00,0x67,0x00,0xc0,0x00,0xa2,0x00,0xd0,0xc0,0x56,0x02,0xc0,0xc0,0x57]
else:
    list=[0x00,0xc0,0x00,0x78,0x06,0x40,0x00,0x67,0x00,0xc5,0x0,0x78,0x12,0xc0,0x00,0x67,0x00,0xc0,0x00,0xa2,0x00,0xd0,0xc0,0x56,0x02,0xc0,0xc0,0x57,0xf2,0xc1,0x00,0x58]
list1=[0x45,0x49,0x50,0x32]
string= ""
string1= ""


for item in list:
		string=string+chr(item)
for item in list1:
		string1=string1+chr(item)

if key1 == string1 and key == string:
    if sensor=="True": found = is_string(f,0,"SENSOR.pbn") 
    else: found = True
else: found = False

if (extension == ".elf" or extension == ".ELF"):
    print extension
else:
    while (not found):
        if (TargetName == "9x35"):
            i=i+(0x80000)
        else:
            i=i+(0x100000)
        f.seek(i)
        if (TargetName == "8994" or TargetName == "8996" or TargetName == "8992" or TargetName == "8952" or TargetName == "8976" or TargetName == "9x35"):
            key=f.read(28)
        else:
            key=f.read(32)
        k=i+0x40
        f.seek(k)
        key1=f.read(4)
        if key1 == string1 and key == string:
            if TargetName == "8996":
                found_sensor = is_string(f,k,"SENSOR.pbn")
                found_pbn = is_string(f,k,"1234.pbn")
                if (sensor=="True" and found_sensor == True): found = True
                elif (sensor=="False" and found_sensor == False): 
                    if found_pbn:
                        found = True 
                else: found = False
            else: found = True 
        if i >= s1:
            # print "ADSP start address not found in the Dump"
            check_2_0_builds = 1
            break
        if (found == True):
            if (TargetName == "8996" or sensor=="True" or TargetName == "8976"  or TargetName == "8952"): 
                i = i | 0x80000000


f.close()
start_address_trial_list= [ 0xdc00000, 0xbf00000, 0xc500000, 0x6400000, 0x2000000, 
                            0x1300000, 0x5a00000, 0xdb00000, 0xd800000, 0xc300000,   
                            0xc200000, 0xc700000, 0x6f00000, 0x6200000, 0xc800000] 
if check_2_0_builds == 1:
    exit = 1
    f_check = open(input, 'rb')
    for list in start_address_trial_list:
        f_check.seek(list)
        key=f_check.read(32)
        if key == string:
            i = list
            exit = 0
            break
    f_check.close()
    if exit == 1:
        sys.exit()

    

f4 = open(input,"rb")
data = f4.read(4)
if TargetName == "8994" or TargetName == "8992" or TargetName == "8952" or TargetName == "8976" or (TargetName == "8996" and sensor =="True"):
    VAAddr="000010f0"
else:
    VAAddr="000000f0"
if i == 0 and (extension != ".elf" or extension != ".ELF"):
    while binascii.hexlify(data)!=VAAddr:
		data=f4.read(4)
    else:
        if binascii.hexlify(data)==VAAddr:
            s1=binascii.hexlify(f4.read(1))
            s2=binascii.hexlify(f4.read(1))
            s3=binascii.hexlify(f4.read(1))
            s4=binascii.hexlify(f4.read(1))
            address = "0x"+s4+s3+s2+s1
        else:
            print "Not found !"
f4.close()
f2 = open(output, 'w')
sys.stdout = f2
if address == "0x0":
	print str(hex(i)).replace('L','')
else:
	print address
sys.stdout = sys.__stdout__
f2.close()


