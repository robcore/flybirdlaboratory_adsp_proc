""" load_so.py script

Loads so files to AMDB on the target.

Usage:
load_so.py -i <text file listing all modules>
the text file must list modules in the same way amdb_mgr expects
Eg. add_capi_v2 1 0x10BE9 0 1 HpMp3DecoderModule.so.2.9 hp_mp3_capi_v2_get_static_properties hp_mp3_capi_v2_init

"""

import sys
import re
import string
import os
from optparse import OptionParser, OptionGroup
import subprocess

##need to change to /system/vendor/lib/rfsa/adsp
LA_SO_PATH='/system/lib/rfsa/adsp/' #important to have '/' at the end 

MODULE_NAME='<module_name>'
CMD_STR='<cmd_str>'
SHARED_LIB_DIR='SHARED_LIB_DIR'
SHARED_LIB_DIR_ARG='$(SHARED_LIB_DIR)'
ADD_OTHER_CMD = 'add_other'

#list of commands to erase already existing modules		   
ERASING_CMDS = ['adb wait-for-device',
                'adb root',
                'adb wait-for-device',
                'adb remount',
                'adb shell mount -o remount,rw /system',
                'adb shell rm -f '+LA_SO_PATH+MODULE_NAME, #this instruction is repeated for every module.
                'adb shell sync',
                'adb reboot'];
                
#commands used for storing				
STORING_CMDS = ['adb wait-for-device',
                'adb root',
                'adb wait-for-device',
                'adb remount',
                'adb shell mount -o remount,rw /system',
                'adb shell mkdir -p '+LA_SO_PATH,
                'adb push libadsp_amdb_skel.so '+LA_SO_PATH,   
                'adb push '+MODULE_NAME+' '+LA_SO_PATH,           #this instruction is repeated for every module.
                'adb push amdb_mgr /data'];
                
#commands used for dynamic loading				
LOADING_CMDS = ['adb root',
                'adb wait-for-device',
                'adb shell cd data; chmod 777 amdb_mgr; ./amdb_mgr '+CMD_STR]; 
				
def is_comment(line):
   if line.strip()[0]=='#':
      #print line+' is comment'
      return True;
   else:
      #print line+' is not comment'
      return False;

def parse_input_text_file(filename,overridepath):
   modulenames = []; #contains full path
   load_commands = []; #commands for loading with basename of the modules.
   textfile=None;
   print
   #open file
   try:
      textfile=open(filename)
   except IOError:
      sys.exit('Error: file '+filename+' could not be opened. Exiting.');
      
   if overridepath == None:
      shared_lib_path='.'
   else:
      print 'Using override path for shared lib: '+overridepath
      shared_lib_path=overridepath;
      
   for line in textfile:
      if len(line.strip())>0 and not is_comment(line):
         splits=line.split('=');
         
         if splits[0].strip()==SHARED_LIB_DIR:
            if not overridepath == None:
               print '>>> ignoring the '+SHARED_LIB_DIR+' from the input file as override path is given.'
            else:
               if len(splits)>2:
                  sys.exit('>>> Error: SHARED_LIB_DIR contains spaces');
                  
               shared_lib_path=splits[1].strip();

               
               print '>>> Shared lib path is '+shared_lib_path
            continue; #continue once SHARED_LIB_DIR line 
         
         splits=line.split();
         #no comments, not SHARED_LIB_DIR. only regular commands, and add_other come here.
         #get module list first
         for s in splits:
            if '.so' in s:
               if SHARED_LIB_DIR_ARG in s:
                  s=s.replace(SHARED_LIB_DIR_ARG,shared_lib_path)
                  
               if os.path.isfile(s):
                  modulenames.append(s);
               else:
                  sys.exit('module '+s+' doesnot exist');
                  
         #prepare load command list
         lcmd=''
         for s in splits:
            if s==ADD_OTHER_CMD:
               break; #ignore add_other commands.
            if '.so' in s:
               lcmd += os.path.basename(s) +' ';
            else:
               lcmd += s+' '
         if len(lcmd)>0:
            load_commands.append(lcmd);

   textfile.close();  
   #print 'Modules found: ' + str(modulenames)
   #print 'Load commands: '+ str(load_commands)
   
   return modulenames,load_commands;
   
#===========================================================================
usage = 'Loads so files to AMDB on the target. Supports add_capi_v2, add_appi, add_capi and add_other (non-CAPI,non-APPI,non-CAPI_v2 library. these files don\'t need to be loaded to AMDB).'
parser = OptionParser(description=usage)
required_group = OptionGroup(parser, "Required Arguments")
required_group.add_option("-i","--input", default='', help="Input file containing command per module. Eg. format of cmd in this txt file is \"add_capi_v2 1 0x10BE9 0 1 HpMp3DecoderModule.so.2.9 hp_mp3_capi_v2_get_static_properties hp_mp3_capi_v2_init\"") 

opt_group = OptionGroup(parser, "Optional Arguments")
opt_group.add_option("-p", "--path", default=None, help="path where so files are present. this path overrides SHARED_LIB_DIR give in input file") 
opt_group.add_option("-s", "--store", default=True, help="Stores modules: 1/0") 
opt_group.add_option("-l", "--load", default=True, help="Loads modules: 1/0") 
opt_group.add_option("-d", "--dryrun", default=False, help="Dry Run. Does not do ADB calls. Useful only to debug : 1/0") 

parser.add_option_group(required_group)
parser.add_option_group(opt_group)

(options, args) = parser.parse_args()

txtfilename=options.input;

if txtfilename == '':
   sys.exit("Error: Insufficient Arguments, use -h option to see required arguments")
   
shared_lib_override_path=options.path;
isstore=True;
isload=True;
isdebug=False;
try : 
   isstore=int(options.store) > 0;
   isload=int(options.load) > 0;
   isdebug=int(options.dryrun) > 0; #ignores all subprocess (adb) calls.
except ValueError:
   sys.exit("Error: Invalid value for boolean arguments.")

call_stdout = sys.stdout

modulenames,load_commands=parse_input_text_file(txtfilename, shared_lib_override_path);

print
print '** Loading or storing to '+LA_SO_PATH+' in LA. Pls modify script (LA_SO_PATH) if this path is not correct.'
print 
if isstore: 
   print
   print '>>> Erasing previous shared libs... '
   for cmd in ERASING_CMDS:
      if MODULE_NAME in cmd:
         for module in modulenames:
            cmd1 = cmd;
            cmd1=cmd1.replace(MODULE_NAME,os.path.basename(module));
            print 'Running cmd : '+str(cmd1);
            if not isdebug:
               subprocess.call(cmd1, stdout=call_stdout, stderr=call_stdout)
      else:
         print 'Running cmd : '+str(cmd);
         if not isdebug:
            subprocess.call(cmd, stdout=call_stdout, stderr=call_stdout)   

   print
   print '>>> Storing....'        
   for cmd in STORING_CMDS:
      if MODULE_NAME in cmd:
         for module in modulenames:
            cmd1 = cmd;
            cmd1=cmd1.replace(MODULE_NAME,module);
            print 'Running cmd : '+str(cmd1);
            if not isdebug:
               subprocess.call(cmd1, stdout=call_stdout, stderr=call_stdout)
      else:
         print 'Running cmd : '+str(cmd);
         if not isdebug:
            subprocess.call(cmd, stdout=call_stdout, stderr=call_stdout)

if isload:
   print
   print '>>> Loading....'
   for cmd in LOADING_CMDS:
      if CMD_STR in cmd:
         for load_cmd in load_commands:
            cmd1 = cmd;
            cmd1=cmd1.replace(CMD_STR,load_cmd);
            print 'Running cmd : '+str(cmd1);
            if not isdebug:
               subprocess.call(cmd1, stdout=call_stdout, stderr=call_stdout)
      else:
         print 'Running cmd : '+str(cmd);
         if not isdebug:
            subprocess.call(cmd, stdout=call_stdout, stderr=call_stdout)

print 
print '>>> Done'
print 
