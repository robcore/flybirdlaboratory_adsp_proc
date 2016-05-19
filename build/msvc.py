#===============================================================================
#
# SCons MSVC tool rules
#
# GENERAL DESCRIPTION
#    This file contains build rules for the Microsoft Visual C++ (MSVC) compiler.
#
# Copyright (c) 2009-2014 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/dspbuild.adsp/2.5/msvc.py#1 $
#
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 02/02/11   enj     Initial version
#
#===============================================================================
import os, string, tempfile
import SCons.Action
from SCons.Script import *
import SCons.Warnings
   
#------------------------------------------------------------------------------
# Chain emitter for C files
# Adds explicit dep
#------------------------------------------------------------------------------
def C_static_obj_emitter(target, source, env):
   #import pdb; pdb.set_trace()
   
   # call defualt static object emitter
   tgt, src = SCons.Defaults.StaticObjectEmitter(target, source, env)
   
   preprocess = env.GetOption('preprocess')
   mixasm = env.GetOption('mixasm')
   hdeptree = env.GetOption('hdeptree')
   
   if preprocess:
      env.Clean(tgt, "".join([str(tgt[0]), ".i"]))
      env.Clean(tgt, "".join([str(tgt[0]), ".pp"]))
      
   if mixasm:
      env.Clean(tgt, "".join([str(tgt[0]), ".mix"]))
      
   if hdeptree:
      env.Clean(tgt, "".join([str(tgt[0]), ".dep"]))

   if 'EXPLICIT_DEPS' in env:
      env.Depends(tgt, env['EXPLICIT_DEPS'])
   
   return (tgt, src)

#------------------------------------------------------------------------------
# Chain emitter for asm files
# Adds explicit dep
#------------------------------------------------------------------------------
def S_static_obj_emitter(target, source, env):
   #import pdb; pdb.set_trace()
   
   # call defualt static object emitter
   tgt, src = SCons.Defaults.StaticObjectEmitter(target, source, env)
   
   # add cleaners for assembling side-effects, taht scons can't auto detect
   env.Clean(tgt, "".join([str(tgt[0]), ".i"]))
   env.Clean(tgt, "".join([str(tgt[0]), ".pp"]))
   env.Clean(tgt, "".join([str(tgt[0]), ".lst"]))
   
   if 'EXPLICIT_DEPS' in env:
      env.Depends(tgt, env['EXPLICIT_DEPS'])
   
   return (tgt, src)

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('msvc')

def generate(env):
   # Add extra command-line params
   vars = Variables()
   vars.AddVariables(('MSVC_VER', 'Version of MS Visual Studio to use (e.g. MSVC_VER=9 indicates MSVC 2008)', '9.0'))
   vars.AddVariables(('BULLSEYE', 'Enable bullseye code coverage tool (e.g. BULLSEYE=yes or BULLSEYE=path/to/bullseye)', 'no'))
   vars.Update(env)
   
   #===============================================================================
   # Load the MSVC Compiler, Assembler, Librarian, Linker
   #===============================================================================
   # Need to use 32-bit (x86) architecture
   env['TARGET_ARCH'] = 'x86'

   # Use the version to figure out which MSVC to load
   print "MSVC Ver      = " + env['MSVC_VER']
   env["TOOL"] = 'vc' + env['MSVC_VER'].split('.')[0]
   env["MSVC"] = {"VERSION": env['MSVC_VER']} 
   env["MSVC_VERSION"] = env["MSVC"]["VERSION"]
   env["MSVS_VERSION"] = env["MSVC_VERSION"]
   # Load the tools
   old = SCons.Warnings.warningAsException(1)
   for t in ['msvs', 'msvc', 'mslib', 'mslink', 'nasm']:
      SCons.Script.Tool(t)(env)    
   SCons.Warnings.warningAsException(old)

   # Check for Bullseye
   bullseye = env['BULLSEYE']
   if bullseye and bullseye != 'no':
      if not os.path.exists(bullseye):
         bullseye = os.path.join('c:' + os.sep + 'Program Files (x86)', 'BullseyeCoverage', 'bin')
      if not os.path.exists(bullseye):
         env.PrintError('')
         env.PrintError("-------------------------------------------------------------------------------")
         env.PrintError("*** BULLSEYE specified, but was not found!")
         env.PrintError("*** Please verify installation and specify path on command line:")
         env.PrintError("***   BULLSEYE=path/to/bullseye")
         env.PrintError("-------------------------------------------------------------------------------")
         env.PrintError('')
         Exit(1)
      print "Bullseye      = " + bullseye
      env.PrependENVPath('PATH', bullseye)
      
   # since we may have change to cygwin re init formatting
   env.LoadToolScript('formatting', toolpath = ['${BUILD_ROOT}/tools/build/scons/scripts'])       

   #===============================================================================
   # Special init for our tools and special dependency in CUST_H
   #===============================================================================
   # Replace Static Object Emitter
   env.Object.builder.add_emitter(suffix='.c', emitter=C_static_obj_emitter)
   env.Object.builder.add_emitter(suffix='.cpp', emitter=C_static_obj_emitter)
   env.Object.builder.add_emitter(suffix='.s', emitter=S_static_obj_emitter)
   
   # Standard include paths always searched
   env.Append(CPPPATH = [
      ".",
      "${INC_ROOT}/build/cust",
      "${INC_ROOT}/build/ms",
   ])
   
   # special dependencies in CUST_H
   cust_scanner = SCons.Scanner.C.CScanner()
   cust_path = cust_scanner.path(env)
   
   if 'CUST_H' in env:
      cust_h_file = env.FindFile(env['CUST_H'], env['CPPPATH'])
      if cust_h_file:
         env.Append(EXPLICIT_DEPS = [cust_h_file])
         deps = cust_scanner(cust_h_file, env, cust_path)
         if deps:
            env.Append(EXPLICIT_DEPS = deps)
      
   if 'AMSS_CUST_H' in env:
      cust_h_file = env.FindFile(env['AMSS_CUST_H'], env['CPPPATH'])
      if cust_h_file:
         env.Append(EXPLICIT_DEPS = [cust_h_file])
         deps = cust_scanner(cust_h_file, env, cust_path)
         if deps:
            env.Append(EXPLICIT_DEPS = deps)
            
   
   # Preprocess assembly cleaner
   env.Replace(PPASM_FILE = env.RealPath("${BUILD_SCRIPTS_ROOT}/ppasm.py"))   
   env.Replace(PPASM = "${PYTHONCMD} ${PPASM_FILE}")  

   #-------------------------------------------------------------------------------
   # Compiler/assembler debug options
   #-------------------------------------------------------------------------------
   if 'USES_NO_DEBUG' in env:
      env.Replace(MSVC_DBG = "")
   else:
      env.Replace(MSVC_DBG = "/Zi")

   #-------------------------------------------------------------------------------
   # Warnings Options
   #-------------------------------------------------------------------------------
   env.Replace(MSVC_WARN = "")

   #-------------------------------------------------------------------------------
   # Optimization Options
   #-------------------------------------------------------------------------------
   env.Replace(MSVC_OPT = "/Od")

   #-------------------------------------------------------------------------------
   # Misc Options
   #-------------------------------------------------------------------------------
   env.Replace(MSVC_MISC = "/nologo /EHa /RTCsu /MTd /Y-")

   #-------------------------------------------------------------------------------
   # Architecture defines
   #-------------------------------------------------------------------------------
   env.Replace(MSVC_DEFS = "/D_HAS_CPP0X=0 /DT_WINNT /DWIN32 /D_CONSOLE /D_DEBUG /DWINVER=0x0601 /D_WIN32_WINNT=0x0601 /D__i386__")


   #-------------------------------------------------------------------------------
   # HEXAGON Flags Def.
   #-------------------------------------------------------------------------------
   # max cmd line length
   # on a cmd sh for XP or newer max command line is 8191, on 2000 and NT is 2047
   # using CreateProcess (our internal spawn) 32766.
   env.Replace(MAXLINELENGTH = 8000)

   # For file redirection, use custom MSVC temp file munger.
   env["TEMPFILE"] = MSVCTempFileMunge
   
   # WARNING!! cmdn can't have any shell operation such as "<", ">" or "|"
   # if it does we will default back os shell and its cmd lenght restrictions 
   # will be in effect (8191).

   env.Replace(TEMPFILEPREFIX = "@")
   env.Replace(TEMPFILESUFFIX = "")
      
   # Header dependency tree generator
   env.Replace(HDEPTREE_FILE = env.RealPath("${BUILD_SCRIPTS_ROOT}/hdeptree.py"))   
   env.Replace(HDEPTREE = "${PYTHONCMD} ${HDEPTREE_FILE}")  

   # Init FLAGS   
   env.Replace(CCFLAGS   = "$MSVC_MISC $MSVC_WARN $MSVC_DBG $MSVC_OPT $MSVC_DEFS $BUILD_FLAGS $CC_DFLAGS $CFLAGS ")
   env.Replace(CXXFLAGS  = "$MSVC_MISC $MSVC_WARN $MSVC_DBG $MSVC_OPT $MSVC_DEFS $BUILD_FLAGS $CC_DFLAGS $CFLAGS ")
   env.Replace(ASMFLAGS  = "$MSVC_MISC $MSVC_WARN $MSVC_DBG $MSVC_OPT $MSVC_DEFS $BUILD_FLAGS $CC_DFLAGS ")
   env.Replace(ASFLAGS   = "$MSVC_MISC $MSVC_WARN $MSVC_DBG $MSVC_OPT $MSVC_DEFS $BUILD_FLAGS $CC_DFLAGS ")
   #env.Replace(ARFLAGS   = "$HEXAGONAR_LIB_QUITE $HEXAGONAR_LIB_REPLACE")

   env.Replace(CCCOMCPY  =    '$CCCOM')
   env.Replace(CXXCOMCPY =    '$CXXCOM')
   env.Replace(CCPPCOM   =    "${TEMPFILE('$CC /E /c $SOURCES $CFLAGS $CCFLAGS $_CCCOMCOM > $TARGET')}")
   env.Replace(CXXPPCOM  =    "${TEMPFILE('$CXX /E /c $SOURCES $CXXFLAGS $CCFLAGS $_CCCOMCOM > $TARGET')}")
   env.Replace(CCPPCLCOM =   "$PPASM -f $SOURCES.posix -o $TARGET.posix")
   env.Replace(CCPPCL_ACOM = "$PPASM -f ${TARGET.posix}.pp -o ${TARGET.posix}.i")
   env.Replace(HDEPTREECOM = "$HDEPTREE -f ${TARGET}.pp -o ${TARGET}.dep")      
   
   env.Replace(CXXPPCLCOM =   env['CCPPCLCOM'])
   env.Replace(CXXPPCL_ACOM = env['CCPPCL_ACOM'])   
   
   ASASCOM = "${TEMPFILE('$CC $ASFLAGS $_CCCOMCOM $INCPATHS $TARGET.posix /c $SOURCES.posix')}"
   env.Replace(ASCPPCOM  =  ASASCOM.replace('/c','/c /E $PPFLAGS'))
   env.Replace(ASASCOM   =  ASASCOM)

   AsmPreprocessAction = SCons.Action.Action('${TEMPFILE("$ASCPPCOM")}', '$ASCPPCOMSTR')
   AsmCleanAction = SCons.Action.Action('$CCPPCL_ACOM', '$CCPPCLCOM_ASTR')
   AsmAssemblyAction = SCons.Action.Action('$ASASCOM', '$ASCOMSTR')

   env.Replace(ASCOM = [
   #   AsmPreprocessAction,          # C pre-process assembly files
   #   AsmCleanAction,               # Removed junck generated by C preprocess
      AsmAssemblyAction,            # Do the actuall assymbly
   #   env.GetDeleteAction('${TARGET.posix}.pp'),
   #   env.GetDeleteAction('${TARGET.posix}.lst'),
   ])

   #-------------------------------------------------------------------------------
   # MOB LINK, very special procedure
   #-------------------------------------------------------------------------------
   # LINK special case in hexagon world
   env.Append(LINKFLAGS = '/NOLOGO')
   env.Append(LINKFLAGS = '/SUBSYSTEM:CONSOLE')
   env.Append(LINKFLAGS = '/MACHINE:X86')
   if 'USES_NO_DEBUG' not in env:
      env.Append(LINKFLAGS = '/DEBUG')
   env.Append(LINKFLAGS = '/OPT:NOREF')
   env.Append(LINKFLAGS = '/INCREMENTAL:NO')

   env.Append(LINKFLAGS = '/NODEFAULTLIB:msvcrt')
   env.Append(LINKFLAGS = '/NODEFAULTLIB:msvcprt')
   env.Append(LINKFLAGS = '/NODEFAULTLIB:msvcrtd')
   env.Append(LINKFLAGS = '/NODEFAULTLIB:msvcprtd')
   env.Append(LINKFLAGS = '/NODEFAULTLIB:libcmt')
   env.Append(LINKFLAGS = '/DEFAULTLIB:libcmtd')
   env.Append(LINKFLAGS = '/DEFAULTLIB:libcpmtd')

   env.Append(LIBS = ['Winmm', 'Ws2_32', 'user32.lib', 'Advapi32.lib'])
   
   #============================================================================
   # COMMON CC ADDITIONS
   #============================================================================
   comcc_addt = "${BUILD_SCRIPTS_ROOT}/comcc_addt.py"

   if env.PathExists(comcc_addt):
      env.LoadToolScript(comcc_addt)
   

class MSVCTempFileMunge:
   """A callable class.  You can set an Environment variable to this,
   then call it with a string argument, then it will perform temporary
   file substitution on it.  This is used to circumvent the long command
   line limitation.

   Example usage:
   env["TEMPFILE"] = MSVCTempFileMunge
   env["LINKCOM"] = "${TEMPFILE('$LINK $TARGET $SOURCES')}"

   By default, the name of the temporary file used begins with a
   prefix of '@'.  This may be configred for other tool chains by
   setting '$TEMPFILEPREFIX'.

   env["TEMPFILEPREFIX"] = '-@'        # diab compiler
   env["TEMPFILEPREFIX"] = '-via'      # arm tool chain
   """
   def __init__(self, cmd):
      """Constructor"""
      self.cmd       = cmd
      self.verbose = int(GetOption('verbose'))

   def __call__(self, target, source, env, for_signature):
      # If signature is desired, return immediately
      if for_signature:
         return self.cmd
      # Use the command passed and substitute variables to get a list 
      cmd = env.subst_list(self.cmd, 0, target, source)[0]

      # What is our max line length
      try:
         maxlineshell = int(env.subst('$MAXLINELENGTH'))
      except ValueError:
         maxlineshell = 8192

      # If we're not greater than the max line length, do nothing
      if (reduce(lambda x, y: x + len(y), cmd, 0) + len(cmd)) <= maxlineshell:
         return self.cmd

      # We do a normpath because mktemp() has what appears to be a
      # bug in Windows that will use a forward slash as a path
      # delimiter.  Windows's link mistakes that for a command line
      # switch and barfs.
      #
      # We use the .scons.tmp suffix for the benefit of the Phar Lap
      # linkloc linker, which likes to append an .lnk suffix if none
      # is given.

      # See if there's a redirection('>') in the command since it can't go in the tempfile
      capture_stdout = False
      for arg in cmd:
         if capture_stdout == True:
            capture_stdout = arg
         if arg == '>':
            capture_stdout = True
      # If redirecting, remove from the args list
      if capture_stdout:
         cmd.remove('>')
         cmd.remove(capture_stdout)
        
      # Don't use 'rm' if the shell is not sh, because rm won't
      # work with the Windows shells (cmd.exe or command.com) or
      # Windows path names.
      rm = 'del'

      prefix = env.subst('$TEMPFILEPREFIX')

      # Quote the spaces
      args = map(SCons.Subst.quote_spaces, cmd[1:])

      # Return an action based on a list
      action = [ cmd[0] ]
      verbose_cmd_str  = "[\'" + str(cmd[0]) + " "

      # Iterate through creating new files for every MAXLINEFILE characters
      maxlinefile = 128000 # ~128k with slop in case of math errors
      linelen = 0
      line    = ''
      tempfiles = []
      for arg in args:
         linelen += len(arg) + 1
         # Check if we've exceeded the max line length for files
         if( linelen > maxlinefile ):
            # Create a new temp file with the line contents so far
            tmp = os.path.normpath(tempfile.mktemp('.scons.tmp'))
            native_tmp = SCons.Util.get_native_path(tmp)
            f = open(tmp, 'w')
            f.write(line + '\n')
            f.close()
            # Add to the list of tempfiles
            tempfiles.append(native_tmp)
            # Update linelen and reset the line string
            linelen = len(arg)
            line    = ''
         # Add the arg to the line string
         line += arg + ' '

      # Flush the rest of the args to a temp file
      if linelen > 0:
         # Create a new temp file with the line contents so far
         tmp = os.path.normpath(tempfile.mktemp('.scons.tmp'))
         native_tmp = SCons.Util.get_native_path(tmp)
         f = open(tmp, 'w')
         f.write(line + '\n')
         f.close()
         # Add to the list of tempfiles
         tempfiles.append(native_tmp)
         
      # Add the tempfile redirection
      for tmpfile in tempfiles:
         action.append(prefix + tmpfile + " ")
         verbose_cmd_str += prefix + tmpfile + " "

      # Add stdout redirection if necessary
      if capture_stdout:
         action.append('>')
         action.append(capture_stdout)
         verbose_cmd_str += " > " + capture_stdout

      # Newline and delete tempfile
      for tmpfile in tempfiles:
         action.append('\n')
         action.append(rm)
         action.append(tmpfile)
         verbose_cmd_str += "\'],[\'" + rm + " " + tmpfile + "\']"

      if SCons.Action.print_actions and self.verbose > 1:
         print "** Using tempfile(s): " + str(tempfiles)
         print "** CMD: " + verbose_cmd_str

#      import pdb; pdb.set_trace()

      # Return the action
      return action
