import gdb
import os

def get(command):
    if os.path.isfile('temp.log'): os.remove('temp.log')
    gdb.execute('set logging file temp.log')
    gdb.execute('set logging on')
    gdb.execute(command)
    gdb.execute('set logging off')
    f=open('temp.log','r')
    name = f.readline()
    f.close()
    return name
    
def get_value(variable):
    name = get('print '+str(variable)).split("= ")[1]
    return name
    
def get_function(address):
    name = get('info symbol '+str(address)).split(" ")[0]
    return name

def extract_thread_name(string):
    return string.split("\\")[0]+'"'
 
def thread_context(TCB,arg):
    return int(get_value('((QURTK_thread_context*)'+str(TCB)+').'+arg)) 

def pointer_value(address):
    line = get('x '+str(address))
    return line.split('\t')[1]

    
# gdb.execute('target remote localhost:9010')
# gdb.execute('symbol-file M8974AAAAAAAAQ1234.elf')


#gdb.execute('quit')
filename=os.path.join(output_folder,"output.txt")
file = open(filename,'w')
gdb.execute('set logging off')
fatal = int(get_value('QURT_error_info.status.fatal'))
count = int(get_value('QURT_error_info.users_errors.counter'))

if count>5:count=5
counter = 0
TCB = 0
while counter<count:
    TCB = int(get_value('QURT_error_info.users_errors.entry['+str(counter)+'].error_tcb').split(" ")[-1],16)
    if TCB != 0:
        break
    counter += 1

if fatal == 1 and TCB==0:
    TCB = int(get_value('QURT_error_info.globregs.context').split(" ")[-1],16)
    
if TCB !=0:
    val = thread_context(TCB,'ugpgp')>>32
    nbits = 32
    ugp = (val + (1 << nbits)) % (1 << nbits)    #converts negative integer to hex
    elr = thread_context(TCB,'elr')
    ssr = thread_context(TCB,'ssr')
    LR_FP = thread_context(TCB,'r3130')
    val = LR_FP>>32
    LR = (val + (1 << nbits)) % (1 << nbits)
    FP = LR_FP&0xFFFFFFFF
    ASID = (ssr>>8)&255
    thread_name = extract_thread_name(get_value('((*((QURT_utcb_t*)'+str(ugp)+')).attr.name)'))
    file.write("Crash Information:\n")
    file.write("\nName of the crashed thread         : "+thread_name)
    if(ASID):
        file.write("\nPD where crash happened            : Sensors PD")
        gdb.execute('symbol-file '+sensor_elf)
    else:
        file.write("\nPD where crash happened            : Guest PD")
    
    file.write("\nSSR of crashed thread              : "+str(hex(ssr)))
    file.write("\nTCB Pointer of crashed thread      : "+str(hex(TCB))[:-1])
    file.write("\nUGP of crashed thread              : "+str(hex(ugp))[:-1])
    file.write("\nELR of crashed thread              : "+str(hex(elr))[:-1])
    file.write("\n\n\nCall Stack:\n.....................................")
    file.write("\n"+get_function(elr)+"()")
    file.write("\n"+get_function(LR)+"()")
    
    while(FP !=0):
        LR = FP+4
        LR = int(pointer_value(LR),16)
        FP = int(pointer_value(FP),16)
        file.write("\n"+get_function(LR)+"()")
        if "qurt_trampoline" in get_function(LR): break
    file.write("\n.....................................")
if os.path.isfile('temp.log'): os.remove('temp.log')
file.close()
