import subprocess
import os
import sys
from time_stamp import time_stamp_check

def write_gdb_starter(elf_file,sensor_elf,output_folder):
        f=open(output_folder+"\\gdb_starter.txt",'w')
        f.write("set tcp connect-timeout 900\n")
        f.write("target remote localhost:9010\n")
        f.write("symbol-file "+elf_file.replace('\\','\\\\')+"\n")
        f.write('python sensor_elf = "'+sensor_elf.replace('\\','\\\\\\\\')+'"\n')
        f.write('python output_folder = "'+output_folder.replace('\\','\\\\')+'"\n')
        f.write("python execfile('signature.py')\nquit\ny\n")
        f.close()
        
F010 = ['8994','8996','8992']        
        
def start_address(ramdump,TargetName):
    s1 = os.path.getsize(ramdump)
    f = open(ramdump, "rb")
    # Add frequent start addresss values to first line
    start_address_trial_list= [ 0xdc00000 , 0xbf00000, 0xc500000 , 0x6400000, 0x2000000, 0x1300000, 0x5a00000, 
                            0xdb00000 , 0xd800000, 0xc300000 ,   
                            0xc200000, 0xc700000 , 0x6f00000 , 0x6200000, 0xc800000 ] 

    file_offset_address=0x0
    file_offset_address2=0x0
    file_offset_address_count=0x0
    file_offset_address_number= 0x0
    file_offset_address_number = len(start_address_trial_list)
    i=0x0
    if (TargetName in F010):
        key=f.read(28)
    else:
        key=f.read(32)
    f.seek(0x40)
    key1=f.read(4)
    if (TargetName in F010):
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
    if ((TargetName != "8994" and TargetName != "8996") and (key1 != string1 or key !=string)):
        while (key1 != string1 or key !=string):
            file_offset_address= start_address_trial_list[file_offset_address_count]
            f.seek(file_offset_address)
            key=f.read(32) 
            file_offset_address2=file_offset_address+0x40
            f.seek(file_offset_address2)
            key1=f.read(4)
            file_offset_address_count = file_offset_address_count + 1
            if ( file_offset_address_count == file_offset_address_number):
                break
        if (key1 == string1 and key ==string):
#           Update start address if found		
            i = file_offset_address
            #print "Found In START_ADDRESS_TRIAL_LIST"

# We enter below while loop if start address is not in 	start_address_trial_list and is not 0x0		
    while (key1 != string1 or key !=string):
        i=i+(0x100000)
        f.seek(i)
        if (TargetName in F010):
            key=f.read(28)
        else:
            key=f.read(32)
	
        k=i+0x40
        f.seek(k)
        key1=f.read(4)
        if i >= s1:
            i = 0
            break;
    f.close()

    return str(hex(i))

    
    
if (len(sys.argv)!=5 and len(sys.argv)!=6): 
    print "Usage: python gdbADSPcrashman.py Target_Name[8974/9x25/8x10] EBI_Binary_File Output_folderpath CRM_Buildpath CustomerprovidedOBJPath[Optional]"
    sys.exit()

if len(sys.argv)==5: sensor_elf_file=sys.argv[4]
else: sensor_elf_file="NA"

#check for valid target
target = ["8x10","8974","8926","8x26","9x35","8084","8994","8996","9x25","8910","8610",'8992','8952']

#Creating elf name list from target name
elf_name_list = {'8x10':'M8x10AAAAAAAAQ1234.elf','8610':'M8x10AAAAAAAAQ1234.elf','8926':'M8x26AAAAAAAAQ1234.elf',
            '8x26':'M8x26AAAAAAAAQ1234.elf','8994':'M8994AAAAAAAAQ1234.elf','8996':'M8996AAAAAAAAQ1234.elf',
            '9x35':'M9x35AAAAAAAAQ1234.elf','9x25':'M9x25AAAAAAAAAQ1234.elf','8974':'M8974AAAAAAAAQ1234.elf',
            '8084':'M8084AAAAAAAAQ1234.elf','8992':'M8992AAAAAAAAQ1234.elf','8952':'M8952AAAAAAAAQ1234.elf'
            }

            
sensor_elf_name_list = {'8x10':'M8x10AAAAAAAAQ1234_SENSOR.elf','8610':'M8x10AAAAAAAAQ1234_SENSOR.elf','8926':'M8x26AAAAAAAAQ1234_SENSOR.elf',
            '8x26':'M8x26AAAAAAAAQ1234_SENSOR.elf','8994':'M8994AAAAAAAAQ1234_SENSOR.elf','8996':'M8996AAAAAAAAQ1234_SENSOR.elf',
            '9x35':'M9x35AAAAAAAAQ1234_SENSOR.elf','9x25':'M9x25AAAAAAAAAQ1234_SENSOR.elf','8974':'M8974AAAAAAAAQ1234_SENSOR.elf',
            '8084':'M8084AAAAAAAAQ1234_SENSOR.elf','8992':'M8992AAAAAAAAQ1234_SENSOR.elf','8952':'M8952AAAAAAAAQ1234_SENSOR.elf'
            }

            
Target_name = sys.argv[1]
if Target_name not in target:
    print "Target name not proper..try again\n"
    print "Correct Format is:  <start_address> <Dump> <ELF> <Sensor ELF>[Optional]"
    sys.exit()
    
filename = sys.argv[2]
output_folder=sys.argv[3]
build_path = sys.argv[4]

#Generate elfs name from path
elf_name=os.path.join(build_path,"\\build\\ms",elf_name_list[Target_name])
sensor_elf_file=os.path.join(build_path,"\\build\\ms",sensor_elf_name_list[Target_name])


if len(sys.argv)==6:
    elf_path=sys.argv[5]
    elf_name=os.path.join(elf_path,elf_name_list[Target_name])
    sensor_elf_file=os.path.join(elf_path,sensor_elf_name_list[Target_name])

if not os.path.isfile(filename):
    print "Dump Filename given does not exist!"
    sys.exit()

if not os.path.isfile(elf_name):
    print "Elf file %s given does not exist!"%elf_name
    sys.exit()

if not os.path.isfile(sensor_elf_file):
    sensor_elf_file=False



#Calculate start address
start_address = start_address(filename,Target_name)
print "\nChecking for timestamp. Please wait..."
timestamp=time_stamp_check(filename,elf_name,sensor_elf_file,start_address)
print timestamp
if not sensor_elf_file: sensor_elf_file=" "

if not True in timestamp:
    print "Timestamp match failed..!!"
    sys.exit()
else: print "\nTimestamp check passed!"

#If output folder doesn't exist, create one
if not os.path.exists(output_folder):
    os.makedirs(output_folder)


#Changing VA start according to target    
if Target_name in F010: va_start="0xf0100000"
else: va_start="0xf0000000"



print "start: "+start_address
size="0x1400000"
write_gdb_starter(elf_name,sensor_elf_file,output_folder)

#print Target_name,filename,start_address,elf_name,sensor_elf_file

command = "crash_sim.exe"+" -G "+"9010 "+"-dump "+filename+" 0x0 "+"0x1FFFFFFF "+"-dpage "+va_start+" "+start_address+" "+size+" -asid "+"0x0 "+"-elf "+elf_name
print command

os.system("start cmd /c "+command)
#p1 = subprocess.Popen(command)
#p2= subprocess.Popen("hexagon-gdb -q -x gdb_starter.txt")

command="hexagon-gdb -q -x "+output_folder+"\\gdb_starter.txt"
os.system("start cmd /c "+command)

