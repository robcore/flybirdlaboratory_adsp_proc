import sys
import os
import re
import shutil
import subprocess
from subprocess import call
from SCons.Script import *

def exists(env):
   return env.Detect('Qshrink_builder')


def generate(env):
   qshrinkutil_act = env.GetBuilderAction(Qshrink_execution)
   qshrinkutil_bld = env.Builder(action = qshrinkutil_act)
   env.Append(BUILDERS = {'QShrinkBuilder' : qshrinkutil_bld})
   
def Qshrink_execution(target, source, env):
   elf_name=env.RealPath(str(source[0]))
   ElfNamePathWin=re.search('(.+)\\\M(\w+\.\w+)', elf_name)
   if ElfNamePathWin:
         ElfPath=ElfNamePathWin.group(1)
         ElfName=ElfNamePathWin.group(2)
   ElfNamePathLin=re.search('(.+)\/\M(\w+\.\w+)', elf_name)		 
   if ElfNamePathLin:
         ElfPath=ElfNamePathLin.group(1)
         ElfName=ElfNamePathLin.group(2)		 
   TargetName=ElfName[0:4]
   ElfFileName = 'M' + ElfName  
   elf_path=env.RealPath(str(source[0]))      
   qshrinkelfname="".join(['qsr_',ElfFileName])
   qshrinkelfpath=os.path.join(ElfPath,qshrinkelfname)
   QSHRINKPATH = '../../qdsp6/qshrink/src/Qshrink20.py'
   ELFFILEPATH = elf_path
   ELFOUTFILEPATH = env.RealPath(str(target[0]))
   HASHFILEPATH = '../../qdsp6/qshrink/src/msg_hash.txt'
   LOGFILEPATH = '../../qdsp6/qshrink/src/qsr_.txt'
   RetCode = call(['python',
                    '-O',
                    QSHRINKPATH,
                    ELFFILEPATH,
                    '--output=' + ELFOUTFILEPATH,
                    '--hashfile=' + HASHFILEPATH,
                    '--log=' + LOGFILEPATH])
   return
