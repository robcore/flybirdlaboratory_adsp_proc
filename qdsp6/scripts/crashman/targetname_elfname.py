import sys
import re

if (len(sys.argv) < 3):
    exit()

target=sys.argv[1]
writefile = open(sys.argv[2],"a")
writefile1 = open(sys.argv[3],"a")
elf_name_list = {'8x10':'M8x10AAAAAAAAQ1234', 
                 '8x26':'M8x26AAAAAAAAQ1234', 
                 '8626':'M8x26AAAAAAAAQ1234', 
                 '9x25':'M9x25AAAAAAAAAQ1234', 
                 '8994':'M8994AAAAAAAAQ1234', 
                 '8996':'M8996AAAAAAAAQ1234', 
                 '8974':'M8974AAAAAAAAQ1234', 
                 '9x35':'M9x35AAAAAAAAQ1234', 
                 '8084':'M8084AAAAAAAAQ1234', 
                 '8992':'M8992AAAAAAAAQ1234', 
                 '8952':'M8952AAAAAAAAQ1234' }

   
sensor_elf_name_list = {'8x10':'M8x10AAAAAAAAQ1234_SENSOR',
                        '8910':'M8x10AAAAAAAAQ1234_SENSOR',
                        '8x26':'M8x26AAAAAAAAQ1234_SENSOR',
                        '8626':'M8x26AAAAAAAAQ1234_SENSOR',
                        '8926':'M8x26AAAAAAAAQ1234_SENSOR',
                        '8994':'M8994AAAAAAAAQ1234_SENSOR',
                        '8996':'M8996AAAAAAAAQ1234_SENSOR',
                        '9x35':'M9x35AAAAAAAAQ1234_SENSOR',
                        '9x25':'M9x25AAAAAAAAAQ1234_SENSOR',
                        '8974':'M8974AAAAAAAAQ1234_SENSOR',
                        '8084':'M8084AAAAAAAAQ1234_SENSOR',
                        '8992':'M8992AAAAAAAAQ1234_SENSOR',
                        '8952':'M8952AAAAAAAAQ1234_SENSOR' }

for key in elf_name_list:
    if target.rstrip('\n') == key.rstrip('\n'):
        writefile.write(elf_name_list[key]+"\n")
        break
for key in sensor_elf_name_list:
    if target.rstrip('\n') == key.rstrip('\n'):
        writefile1.write(sensor_elf_name_list[key]+"\n")
        break
writefile.close()
writefile1.close()
