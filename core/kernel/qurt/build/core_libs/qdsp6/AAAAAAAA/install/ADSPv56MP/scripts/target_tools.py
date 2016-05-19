#===============================================================================
#
# Kernel HEXAGON tool rules
#
# GENERAL DESCRIPTION
#    HEXAGON Tools definitions
#===============================================================================

import sys
import re
import os
import string
import SCons.Action
from SCons.Script import *
from SCons.Platform import TempFileMunge

RDirsSCons = ""
RelPath = ""
NormPath = ""

if os.name == 'posix':
   default_root = '/pkg/qct/software/hexagon/releases/tools'
elif os.name == 'nt':
   default_root = os.path.realpath('C:/Qualcomm/HEXAGON_Tools')
else:
   print "Unknown platform!"
   sys.exit(0)
v4default=os.path.join(default_root,"3.1.04")
v5default=os.path.join(default_root,"5.0.14")
v55default=os.path.join(default_root,"5.1.04")
v55sim=os.path.join(default_root,"5.1.04")
v56default=os.path.join(default_root,"5.1.04")
v60default=os.path.join(default_root,"7.2")

toolsver_minor_whitelist = ["3.1", "5.0", "5.1", "6.2", "6.4", "7.0", "7.1", "7.2"]
#------------------------------------------------------------------------------
# Chain emitter for C files
# Adds explicit dep
#------------------------------------------------------------------------------
def C_static_obj_emitter(target, source, env):
   #import pdb; pdb.set_trace()

   # call defualt static object emitter
   tgt, src = SCons.Defaults.StaticObjectEmitter(target, source, env)

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

   return (tgt, src)

#------------------------------------------------------------------------------
# Chain emitter for asm files
# Adds explicit dep
#------------------------------------------------------------------------------
def P_static_prg_emitter(target, source, env):
   #import pdb; pdb.set_trace()

   # call defualt static object emitter
   tgt, src = SCons.Defaults.StaticProgramEmitter(target, source, env)

   # add cleaners for assembling side-effects, taht scons can't auto detect
   env.Clean(tgt, "".join([str(tgt[0]), ".map"]))

   return (tgt, src)

def build_flags(env):
   cmd = "python " + env.subst('$QURT_TOP') +"/scripts/build_flags.py " + env.subst('$CONFIG_DIR')
   return os.popen(cmd).read().replace('\n','')

def version_compare(v1, v2):
   def normalize(v):
      return [int(x) for x in re.sub("[a-zA-Z_-]", "", v).split(".")]
   return cmp(normalize(v1), normalize(v2))
#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('target_tools')

#default to hexagon version 5, if param and Q6_TOOLS_ROOT not specified
def generate(env, target='simv5'):
   #===============================================================================
   # figure out what tools set will be using
   #===============================================================================
   # The following environment variables must be defined prior to using this make
   # file: GNUPATH, QCTOOLS. In addition the PATH must be updated for
   # the GCC tools.
   if env.subst('$TRGT') is not '':
      target=env.subst('$TRGT')
   if target=='modemFWv4':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP') + "/config/modemFWv4"
      hexagon_ver=4
      env.Replace(T32_SYS_CPU = "HexagonV4C")
      env.Replace(T32_MCD_ARCH = "v4c")
   elif target=='modemSWv4':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/modemSWv4'
      hexagon_ver=4
      env.Replace(T32_SYS_CPU = "HexagonV4C")
      env.Replace(T32_MCD_ARCH = "v4c")
   elif target=='modemv5':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/modemv5'
      hexagon_ver=5
   elif target=='MMv4':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/MMv4'
      hexagon_ver=4
      env.Replace(T32_SYS_CPU = "HexagonV4M")
      env.Replace(T32_MCD_ARCH = "v4m")
   elif target=='MMv5':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/MMv5'
      hexagon_ver=5
   elif target=='ADSPv5MP':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv5MP'
      hexagon_ver=5
   elif target=='simv4':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sim'
      hexagon_ver=4
   elif target=='simv5':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sim'
      hexagon_ver=5
   elif target=='simv4_bitmask':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sim_bitmask'
      hexagon_ver=4
   elif target=='simv5_bitmask':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sim_bitmask'
      hexagon_ver=5
   elif target=='mpqurt':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/mpqurt'
      hexagon_ver=5
   elif target=='mpsecure':
      env['TEST_OBJS'] = True         # mpsecure is an internal target for advanced testing
                                      #  so we can force TEST_OBJS on for this target.
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/mpsecure'
      hexagon_ver=55
   elif target=='staticv4':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/static'
      hexagon_ver=4
   elif target=='staticv5':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/static'
      hexagon_ver=5
   elif target=='MBAv5':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/MBAv5'
      hexagon_ver=5
   elif target=='simv55':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sim'
      hexagon_ver=55
   elif target=='modemv55':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/modemv55'
      hexagon_ver=55
   elif target=='modemv56':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/modemv56'
      hexagon_ver=55
   elif target=='ADSPv55MP':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv55MP'
      hexagon_ver=55
   elif target=='ADSPv56MP':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv56MP'
      hexagon_ver=55
   elif target=='ADSPv56z':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv56z'
      hexagon_ver=55
   elif target=='ADSPv5MP_ISV':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv5MP_ISV'
      hexagon_ver=5
   elif target=='ADSPv60MP':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv60MP'
      hexagon_ver=60
   elif target=='ADSPv60z':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/ADSPv60z'
      hexagon_ver=60
   elif target=='sensorsv60':
      env['CONFIG_DIR'] = env.subst('$QURT_TOP')+'/config/sensorsv60'
      hexagon_ver=60
   elif os.path.exists(target):
      env['CONFIG_DIR'] = os.path.realpath(target)
      hexagon_ver=target[target.rindex("v") + len("v"):]
      target = os.path.basename(target)
   else:
      print target
      print "Unknown TARGET!!!"
      sys.exit(0)
   env.Replace(TRGT = target)
   if hexagon_ver == 5:
      env.Replace(T32_SYS_CPU = "HexagonV5")
      env.Replace(T32_MCD_ARCH = "v5")
   if hexagon_ver == 55:
      env.Replace(T32_SYS_CPU = "HexagonV55")
      env.Replace(T32_MCD_ARCH = "v55")
   if hexagon_ver == 60:
      env.Replace(T32_SYS_CPU = "HexagonV60")
      env.Replace(T32_MCD_ARCH = "v60")
   env.Replace(INSTALL_DIR = env.subst('$INSTALL_DIR') + "/" + target)
   env.Replace(BUILD_DIR = env.subst('$BUILD_DIR') + "/" + target)

   env['BUILD_CONFIG_FLAGS'] = build_flags(env)

   v55_workaround = "False"
   if 'CONFIG_V55_SW_WORKAROUND' in env.subst('$BUILD_CONFIG_FLAGS'):
      v55_workaround = "True"

   toolsver = env.subst('$Q6_TOOLS_VER')
   toolsver_major_minor = ''
   if(toolsver):
      toolsver_match =  re.search('^(\d+)\.(\d+).*', toolsver)
      if not toolsver_match:
        print("\nInvalide input of HEXAGON_RTOS_RELEASE or --q6_tools_ver: "+toolsver+". It should be the correct tool's release number starting with MajorVerdion.MinorVersion")
        Exit(1)
      toolsver_major_minor = toolsver_match.group(1) + "." + toolsver_match.group(2)
      if (toolsver_major_minor not in toolsver_minor_whitelist):
          print('\nError: Tools are untested for QuRT, please contact qurt.support\n')
          Exit(1)
      else:
          hexagon_root = os.path.join(default_root,toolsver)
          if int(toolsver_match.group(1)) <6:
           if(version_compare(toolsver, '5.1.03') < 0):
             v55_workaround = "False"
   else:
      hexagon_root = os.environ.get('Q6_TOOLS_ROOT')

   if not hexagon_root:
      if hexagon_ver == 4:
         hexagon_root = v4default
      elif hexagon_ver == 55:
         if (v55_workaround == "True"):
            hexagon_root = v55default
         else:
            hexagon_root = v55sim
      elif hexagon_ver == 56:
         hexagon_root = v56default
      elif hexagon_ver == 60:
         hexagon_root = v60default
      else:
         hexagon_root = v5default

   input_hexagon_root = env.subst('$HEXAGON_ROOT')
   if os.path.exists(input_hexagon_root):
     hexagon_root=string.replace(hexagon_root,default_root,input_hexagon_root)


   if not toolsver_major_minor:
     pathname = ""
     pathname = os.path.split(hexagon_root)
     toolsver_match =  re.search('^(\d+)\.(\d+).*', pathname[1])
     if not toolsver_match:
        print("\nInvalide input of Q6_TOOLS_ROOT: "+hexagon_root+". The last field of the path should be the correct tool's release number starting with MajorVerdion.MinorVersion")
        Exit(1)
     toolsver_major_minor = toolsver_match.group(1) + "." + toolsver_match.group(2)

   q6_tool_major=int(toolsver_match.group(1))
   q6_tool_minor=int(toolsver_match.group(2))
   env['Q6_TOOL_MAJOR_MINOR']= toolsver_major_minor

   if (q6_tool_major>=6):
     env.Replace(USE_LLVM='True')
   else:
     env.Replace(USE_LLVM='False')

   env.Replace(Q6_TOOLS_ROOT = hexagon_root)
   hexagon_image_entry = os.environ.get('HEXAGON_IMAGE_ENTRY', '0x1e000000')

   q6version = 'v'+str(hexagon_ver)
   hexagon_tools = "HEXAGON%s" % hexagon_ver

   # init variables to environment
   env.Replace(HEXAGON_IMAGE_ENTRY = hexagon_image_entry)
   env.Replace(HEXAGON_IMAGE_ENTRY_SECTION = '.start')
   env.Replace(HEXAGON_TOOLS = hexagon_tools)
   env.Replace(HEXAGONTOOLS = hexagon_tools)
   env.Replace(Q6VERSION = q6version)

   if not os.path.exists(hexagon_root):
      print("-------------------------------------------------------------------------------")
      print("*** HEXAGON tools are not present")
      print("*** "+hexagon_root+" is an invalid path for tools")
      print("-------------------------------------------------------------------------------")
      print('')
      Exit(1)

   # Replace Static Object Emitter
   env.Object.builder.add_emitter(suffix='.c', emitter=C_static_obj_emitter)
   env.Object.builder.add_emitter(suffix='.cpp', emitter=C_static_obj_emitter)
   env.Object.builder.add_emitter(suffix='.s', emitter=S_static_obj_emitter)
   #env.Program.builder.add_emitter(suffix='.pbn', emitter=P_static_prg_emitter)
   #env.Object.builder.add_emitter(suffix='.elf', emitter=P_static_obj_emitter)

   #===============================================================================
   #                             TOOL DEFINITIONS
   #===============================================================================
   if (q6_tool_major > 6):
    QDSP6BIN = os.path.realpath(hexagon_root+"/Tools/bin")
   else:
    QDSP6BIN = os.path.realpath(hexagon_root+"/gnu/bin")
   if (q6_tool_major > 6):
    QDSP6QCBIN = os.path.realpath(hexagon_root+"/Tools/bin")
   else:
    QDSP6QCBIN = os.path.realpath(hexagon_root+"/qc/bin")
   if (q6_tool_major > 6):
    env['QDSP6INCLUDE'] = os.path.realpath(hexagon_root+"/Tools/target/hexagon/include")
   else:
    env['QDSP6INCLUDE'] = os.path.realpath(hexagon_root+"/qc/include/common")

   if env['PLATFORM'] in ['windows', 'win32']:
      QDSP6BIN = QDSP6BIN + "\\"
      QDSP6QCBIN = QDSP6QCBIN + "\\"
   else:
      QDSP6BIN = QDSP6BIN + "/"
      QDSP6QCBIN = QDSP6QCBIN + "/"
   env.Replace(QDSP6BIN = QDSP6BIN)

   if (v55_workaround == "True")and (q6_tool_major <= 6):
        env.Replace(QDSP6_RELEASE_LIB_DIR = hexagon_root+"/no-dealloc_return-libs/dinkumware/lib/${Q6VERSION}")
   elif (q6_tool_major > 6):
        env.Replace(QDSP6_RELEASE_LIB_DIR = hexagon_root+"/Tools/target/hexagon/lib/${Q6VERSION}")
   else:
        env.Replace(QDSP6_RELEASE_LIB_DIR = hexagon_root+"/dinkumware/lib/${Q6VERSION}")


   if (q6_tool_major > 6):
    env.Replace(LIB_DSP_ROOT = hexagon_root+"/Tools/target/hexagon/lib/${Q6VERSION}")
   else:
    env.Replace(LIB_DSP_ROOT = hexagon_root+"/qc/lib/${Q6VERSION}")

   env.Replace(QDSP6_BINDIR = "${L4Q6_ROOT}/bin")

   if (q6_tool_major >6):
     if (q6_tool_minor==0):
        env['QURT_MODEL_DLL']= "/qurt_model_7_0.dll"
        env['QURT_MODEL_SO']= "/qurt_model_7_0.so"
     elif (q6_tool_minor==1) :
        env['QURT_MODEL_DLL']= "/qurt_model_7_1.dll"
        env['QURT_MODEL_SO']= "/qurt_model_7_1.so"
     elif (q6_tool_minor==2) :
        env['QURT_MODEL_DLL']= "/qurt_model_7_1.dll"
        env['QURT_MODEL_SO']= "/qurt_model_7_1.so"
   else:
      env['QURT_MODEL_DLL']= "/qurt_model.dll"
      env['QURT_MODEL_SO']= "/qurt_model.so"
   if os.name == 'posix':
      env.Replace(QURT_MODEL = env.subst('$Q6_RTOS_ROOT')+"/"+env.subst('$TRGT')+"/debugger/lnx64/qurt_model.so")
   elif os.name == 'nt':
      env['ENV']['TMP'] = os.environ['TMP']
      env.Replace(QURT_MODEL = env.subst('$Q6_RTOS_ROOT')+"/"+env.subst('$TRGT')+"/debugger/Win/qurt_model.dll")

   env.Replace(Q6_RTOS_ROOT = env.subst('$Q6_RTOS_ROOT')+"/"+env.subst('$TRGT'))

   if 'Q6_RTOS_ROOT' in env:
      qdsp6_libdir = env.subst('$Q6_RTOS_ROOT')+"/lib"
      env.Replace(Q6_RTOS_LIBS = qdsp6_libdir)
   else:
      print("-------------------------------------------------------------------------------")
      print("*** Q6_RTOS_ROOT is not defined")
      print("*** install location is required")
      print("-------------------------------------------------------------------------------")
      print('')
      Exit(1)
   env["TEMPFILE"] = TempFileMunge
   #-------------------------------------------------------------------------------
   # Tool path definitions (may be tool set dependent - ADS vs RVCT)
   #-------------------------------------------------------------------------------
   env.Replace(QDSP6_CPPPATH = [])

   env.Replace(CPPPATH = [env.subst('$CONFIG_DIR'), env.subst('$Q6_TOOLS_ROOT')+'/qc/bin',
                                     env.subst('$QURT_TOP')+'/libs/qurt/include', env.subst('$QURT_TOP')+'/libs/qurt/include/public',
                                     env.subst('$QURT_TOP')+'/qurtos/include', env.subst('$QURT_TOP')+'/kernel/include'])

   #-------------------------------------------------------------------------------
   # Defines to exapnd paths and libs with posix style even on a Windows env.
   #-------------------------------------------------------------------------------
   env.Replace(LIBFLAGS_NULL = '')
   env.Replace(_LIBFLAGS_POSIX = '$( ${_concat(LIBFLAGS_NULL, _LIBFLAGS, LIBFLAGS_NULL, __env__, RDirs)} $)')

   if env['PLATFORM'] in ['cygwin']:
      env.Replace(_QDSP6_CPPINCFLAGS = '$( ${_concat(INCPREFIX, QDSP6_CPPPATH, INCSUFFIX, __env__, PosixRDirs, TARGET, SOURCE)} $)')
   else:
      env.Replace(_QDSP6_CPPINCFLAGS = '$( ${_concat(INCPREFIX, QDSP6_CPPPATH, INCSUFFIX, __env__, RDirs, TARGET, SOURCE)} $)')

   if env.has_key('ENV'):
      env.AppendENVPath('PATH', '${QDSP6BIN}')
      #print env.Dump()

   #-------------------------------------------------------------------------------
   # Software tool and environment definitions
   #-------------------------------------------------------------------------------

   #import pdb; pdb.set_trace()
   if env['PLATFORM'] in ['cygwin']:
      QDSP6BIN = string.replace("/cygdrive/%s" % QDSP6BIN, ":", "")

   if hexagon_ver >= 5:
      if (q6_tool_major >= 6):
         env.Replace(CC = QDSP6QCBIN + "hexagon-clang${EXE_EXT}")
      else:
         env.Replace(CC = QDSP6BIN + "hexagon-gcc${EXE_EXT}")
   else:
      env.Replace(CC = QDSP6BIN + "qdsp6-gcc${EXE_EXT}")

   # HEXAGON set ANSI C++ compiler
   if hexagon_ver >= 5:
      if (q6_tool_major >= 6):
         env.Replace(CXX = QDSP6QCBIN + "hexagon-clang++${EXE_EXT}")
      else:
         env.Replace(CXX = QDSP6BIN + "hexagon-g++${EXE_EXT}")
   else:
      env.Replace(CXX = QDSP6BIN + "qdsp6-g++${EXE_EXT}")

   # HEXAGON assembler
   if hexagon_ver >= 5:
      if (q6_tool_major > 6):
        env.Replace(AS = QDSP6BIN + "hexagon-llvm-mc${EXE_EXT}")
      else:
        env.Replace(AS = QDSP6BIN + "hexagon-as${EXE_EXT}")
   else:
      env.Replace(AS = QDSP6BIN + "qdsp6-as${EXE_EXT}")

   # HEXAGON library archiver
   if hexagon_ver >= 5:
      env.Replace(AR = QDSP6BIN + "hexagon-ar${EXE_EXT}")
   else:
      env.Replace(AR = QDSP6BIN + "qdsp6-ar${EXE_EXT}")

   # HEXAGON linker
   if hexagon_ver >= 5:
        if (q6_tool_major > 6):
           env.Replace(LINK = QDSP6BIN + "hexagon-link${EXE_EXT}")
        else:
           env.Replace(LINK = QDSP6BIN + "hexagon-ld${EXE_EXT}")
   else:
      env.Replace(LINK = QDSP6BIN + "qdsp6-ld${EXE_EXT}")

   # HEXAGON library archiver
   if hexagon_ver >= 5:
      env.Replace(RANLIB = QDSP6BIN + "hexagon-ranlib${EXE_EXT}")
   else:
      env.Replace(RANLIB = QDSP6BIN + "qdsp6-ranlib${EXE_EXT}")

   # HEXAGON Object COPY
   if hexagon_ver >= 5:
       if (q6_tool_major > 6):
          env.Replace(OBJCOPY = QDSP6BIN + "hexagon-elfcopy${EXE_EXT}")
       else:
          env.Replace(OBJCOPY = QDSP6BIN + "hexagon-objcopy${EXE_EXT}")
   else:
      env.Replace(OBJCOPY = QDSP6BIN + "qdsp6-objcopy${EXE_EXT}")

   # HEXAGON Object Dump
   if hexagon_ver >= 5:
       if (q6_tool_major > 6):
          env.Replace(OBJDUMP = QDSP6BIN + "hexagon-llvm-objdump${EXE_EXT}")
       else:
          env.Replace(OBJDUMP = QDSP6BIN + "hexagon-objdump${EXE_EXT}")
   else:
      env.Replace(OBJDUMP = QDSP6BIN + "qdsp6-objdump${EXE_EXT}")

   # HEXAGON simulator
   if hexagon_ver >= 5:
      env.Replace(SIM = QDSP6QCBIN + "hexagon-sim${EXE_EXT}")
   else:
      env.Replace(SIM = QDSP6QCBIN + "qdsp6-sim${EXE_EXT}")

   #-------------------------------------------------------------------------------
   # Compiler output options
   #-------------------------------------------------------------------------------
   env.Replace(HEXAGON_COMPILE_CMD = "-c")
   env.Replace(HEXAGON_PREPROCESS_CMD = "-E -xc")
   env.Replace(HEXAGON_INHIBIT_WARN_CMD = "-w")
   env.Replace(HEXAGON_OUTPUT_CMD = "-o")
   env.Replace(HEXAGON_ASMOUT_CMD = "-S")
   env.Replace(HEXAGONAR_LIB_REPLACE = "-r")
   env.Replace(HEXAGONAR_LIB_QUITE = "c")
   env.Replace(HEXAGONLD_MAP_CMD = "-Map")

   env.Replace(ARMBIN_BIN_CMD = "--bin")
   env.Replace(ARMBIN_ELF_CMD = "--elf")
   env.Replace(ARMBIN_OUTPUT_CMD = "-o")
   env.Replace(ARMBIN_NODEBUG_CMD = "--nodebug")
   env.Replace(ARMBIN_NOLINKVIEW_CMD = "--nolinkview")



   #-------------------------------------------------------------------------------
   # Compiler/assembler debug options
   #-------------------------------------------------------------------------------
   env.Replace(HEXAGON_DBG = "-g")            # Enable DWARF2 format debug tables
   #env.Replace(HEXAGON_DBG = "")

   #-------------------------------------------------------------------------------
   # Compiler optimization options
   #-------------------------------------------------------------------------------
   env.Replace(HEXAGON_OPT_TIME = "-Otime")
   env.Replace(HEXAGON_OPT_SPACE = "-Ospace")
   env.Replace(HEXAGON_OPT_2 = "-O2")
   env.Replace(HEXAGON_OPT_1 = "-O1")
   env.Replace(HEXAGON_OPT_S = "-Os")

   # Let's optimize for time on the L4 build
   env.Replace(HEXAGONCC_OPT = "${HEXAGON_OPT_2}")

   # the other opts found
   env.Replace(HEXAGONCXX_OPT = "${HEXAGON_OPT_SPACE} ${HEXAGON_OPT_TIME} ${HEXAGON_OPT_S}")
   env.Replace(HEXAGONASM_OPT = "${HEXAGON_OPT_1}")

   #-------------------------------------------------------------------------------
   # HEXAGON Warnings Options
   #-------------------------------------------------------------------------------
   #env.Replace(HEXAGON_WARN = "-Wall -Wpointer-arith")
   env.Replace(HEXAGON_WARN = "-Werror -Wall")
   #env.Replace(HEXAGONCC_WARN = "${HEXAGON_WARN} -Wstrict-prototypes -Wnested-externs")
   env.Replace(HEXAGONCC_WARN = "${HEXAGON_WARN}")
   env.Replace(HEXAGONCXX_WARN = "${HEXAGON_WARN}")

   #-------------------------------------------------------------------------------
   # HEXAGON Machine Options
   #-------------------------------------------------------------------------------
   hexagon_machine = "-m${Q6VERSION}"
   if env.subst("$Q6VERSION") == "v1" or env.subst("$Q6VERSION") == "v2":
      hexagon_machine += " -mv1-v2-uncached-data"
   env.Replace(HEXAGON_MACHINE = hexagon_machine)

   #-------------------------------------------------------------------------------
   # HEXAGON Undef Options
   #-------------------------------------------------------------------------------
   #env.Replace(HEXAGON_UNDEF = "-Uqdsp6 -Uq6sim -Uqdsp6r0")
   env.Replace(HEXAGON_UNDEF = "")

   #-------------------------------------------------------------------------------
   # HEXAGON Lang independent options
   #-------------------------------------------------------------------------------
   #env.Replace(HEXAGON_LANIND = "-fdata-sections -ffunction-sections " \
   #      "-mno-literal-pool-addresses -nostdlib -fno-exceptions " \
   #      "-fno-merge-constants -fno-strict-aliasing ")
   if ('adsp' in target.lower()):
      env.Replace(HEXAGON_LANIND = ['-G0','-fdata-sections','-ffunction-sections'])
   else:
      env.Replace(HEXAGON_LANIND = ['-G0'])

   #-------------------------------------------------------------------------------
   # HEXAGON Stack Checking
   #-------------------------------------------------------------------------------
   if hexagon_ver >= 3 and 'USES_STACK_PROTECTOR' in env:
      env.Replace(HEXAGON_STKPRO = "-fstack-protector")
   else:
      env.Replace(HEXAGON_STKPRO = "")

   #----------------------------------------------------------------------------
   # common defines
   #----------------------------------------------------------------------------
   env.Replace(BUILD_CCFLAGS = env.subst('$BUILD_CONFIG_FLAGS').split(' '))

   env.Replace(BUILD_ASMFLAGS = '-DCUST_H=\\"${CUST_H}\\" -DBUILD_TARGET=\\"${BUILD_ID}\\" '\
      '-DBUILD_VER=\\"${BUILD_VER}\\" -DBUILD_ASIC=\\"${BUILD_ASIC}\\" -D__FILENAME__=\\"$SOURCE.file\\" ')

   #-------------------------------------------------------------------------------
   # HEXAGON Flags Def.
   #-------------------------------------------------------------------------------

   env.Replace(INCPREFIX = "-I")
   env.Replace(CPPDEFPREFIX  = "-D")
   env.Replace(OBJSUFFIX = ".o")

   env.Replace(LIBPREFIX = "")
   env.Replace(LIBSUFFIX = ".lib")
   env.Replace(LIBSUFFIXES = ['$LIBSUFFIX', '.l', '.a'])
   env.Replace(LIBLIKNPREFIX = "")
   env.Replace(DO_NOT_USE_LIBLINKSUFFIX = "")
   env.Replace(LIBDIRPREFIX = "-L")

   env.Replace(PROGPREFIX = "")
   env.Replace(PROGSUFFIX = '.elf')

   # max cmd line length
   # on a cmd sh for XP or newer max command line is 8191, on 2000 and NT is 2047
   # using CreateProcess (our internal spawn) 32766.
   # POSIX OSs is no issue command line limit usually in the 128k range.
   # cygwin has the added restriction of max 32k including OS env variables
   # we have seen a lot of issues with OS environment grater then 20k
   # (what is going on from MAKE world why is environment so large??)
   if env['PLATFORM'] in ['windows', 'win32']:
      # hexagon uses gcc code under the hood, gcc uses the OS env extensively
      # because of this we need to limit the command line as it is then added
      # to the OS env by gcc. the safe value we have been using is 8k
      env.Replace(MAXLINELENGTH = 32000)
   elif env['PLATFORM'] in ['cygwin']:
      env.Replace(MAXLINELENGTH = 8000)
   else:
      env.Replace(MAXLINELENGTH = 100000)

   # WARNING!! cmdn can't have any shell operation such as "<", ">" or "|"
   # if it does we will default back os shell and its cmd lenght restrictions
   # will be in effect (8191).

   if env['PLATFORM'] in ['cygwin']:
      env.Replace(TEMPFILEPREFIX = "`cat ")
      env.Replace(TEMPFILESUFFIX = "`")
   else:
      env.Replace(TEMPFILEPREFIX = "@")
      env.Replace(TEMPFILESUFFIX = "")

   if (q6_tool_major >= 6):
      env.Replace(LLVMCFLAGS = "-fgnu89-inline")
   else:
      env.Replace(LLVMCFLAGS = "")

   if (q6_tool_major >= 6):
      env.Replace(ERRATACFLAGS = "")
   else:
     if (v55_workaround == "True"):
        env.Replace(ERRATACFLAGS = "-mno-dealloc_return")
     else:
        env.Replace(ERRATACFLAGS = "")

   # Init FLAGS
   env.Replace(CCFLAGS   = "$HEXAGON_MACHINE $HEXAGONCC_WARN $HEXAGON_UNDEF $HEXAGONCC_OPT $HEXAGON_DBG $HEXAGON_LANIND $HEXAGON_STKPRO $BUILD_CCFLAGS $CC_DFLAGS $CFLAGS $LLVMCFLAGS $ERRATACFLAGS")
   env.Replace(CXXFLAGS  = "$HEXAGON_MACHINE $HEXAGONCXX_WARN $HEXAGON_UNDEF $HEXAGONCC_OPT $HEXAGON_DBG $HEXAGON_LANIND $HEXAGON_STKPRO $BUILD_CCFLAGS $CC_DFLAGS $CFLAGS $LLVMCFLAGS $ERRATACFLAGS")
   env.Replace(ASMFLAGS  = "$HEXAGON_MACHINE $HEXAGONCC_WARN $HEXAGON_UNDEF $HEXAGONCC_OPT $HEXAGON_DBG $HEXAGON_LANIND $HEXAGON_STKPRO $BUILD_CCFLAGS $CC_DFLAGS $ERRATACFLAGS")
   env.Replace(ASFLAGS   = "$HEXAGON_MACHINE $HEXAGONCC_WARN $HEXAGON_UNDEF $HEXAGONCC_OPT $HEXAGON_DBG $HEXAGON_LANIND $HEXAGON_STKPRO $BUILD_CCFLAGS $CC_DFLAGS $ERRATACFLAGS")
   #env.Replace(ARFLAGS   = "$HEXAGONAR_LIB_QUITE $HEXAGONAR_LIB_REPLACE")
   env.Replace(ARFLAGS   = "cru")

   CCCOM = "${TEMPFILE('$CC $HEXAGON_OUTPUT_CMD $TARGET.posix $HEXAGON_COMPILE_CMD $CCFLAGS $_CCCOMCOM $INCPATHS $_QDSP6_CPPINCFLAGS $SOURCES.posix')}"
   env.Replace(CCCOM =       CCCOM)
   env.Replace(CCCOMCPY =    CCCOM)
   env.Replace(CCPPCOM =     CCCOM.replace('$HEXAGON_COMPILE_CMD','$HEXAGON_PREPROCESS_CMD'))
   env.Replace(CCMIXCOM =    CCCOM.replace('$HEXAGON_COMPILE_CMD','$HEXAGON_ASMOUT_CMD'))
   env.Replace(CCPPCLCOM =   "$PPASM -f $SOURCES.posix -o $TARGET.posix")
   env.Replace(CCPPCL_ACOM = "$PPASM -f ${TARGET.posix}.pp -o ${TARGET.posix}.i")
   env.Replace(HDEPTREECOM = "$HDEPTREE -f ${TARGET}.pp -o ${TARGET}.dep")

   CXXCOM = "${TEMPFILE('$CXX $HEXAGON_OUTPUT_CMD $TARGET.posix $HEXAGON_COMPILE_CMD $CXXFLAGS $_CCCOMCOM $INCPATHS $_QDSP6_CPPINCFLAGS $SOURCES.posix')}"
   env.Replace(CXXCOM =       CXXCOM)
   env.Replace(CXXCOMCPY =    CXXCOM)
   env.Replace(CXXPPCOM =     CXXCOM.replace('$HEXAGON_COMPILE_CMD','$HEXAGON_PREPROCESS_CMD'))
   env.Replace(CXXMIXCOM =    CXXCOM.replace('$HEXAGON_COMPILE_CMD','$HEXAGON_ASMOUT_CMD'))
   env.Replace(CXXPPCLCOM =   env['CCPPCLCOM'])
   env.Replace(CXXPPCL_ACOM = env['CCPPCL_ACOM'])

   env.Replace(ARCOM     =  "${TEMPFILE('$AR $ARFLAGS $TARGET.posix $SOURCES.posix')}")
   env.Replace(RANLIBCOM =  "${TEMPFILE('$RANLIB $TARGET.posix')}")

   env.Replace(ASCPPCOM  =  "$CC $ASMFLAGS $AFLAGS $_CCCOMCOM $INCPATHS $HEXAGON_PREPROCESS_CMD $HEXAGON_OUTPUT_CMD ${TARGET.posix}.pp $SOURCES.posix")
   env.Replace(ASASCOM   =  "${TEMPFILE('$CC $HEXAGON_OUTPUT_CMD $TARGET.posix $HEXAGON_COMPILE_CMD $CCFLAGS $_CCCOMCOM $INCPATHS $_QDSP6_CPPINCFLAGS $SOURCES.posix')}")

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
   # HEXAGON LINK, very special procedure
   #-------------------------------------------------------------------------------
   env.Replace(LINKFLAGS = "-m${Q6VERSION} -nostdlib --section-start ${HEXAGON_IMAGE_ENTRY_SECTION}=${HEXAGON_IMAGE_ENTRY} ${HEXAGONLD_MAP_CMD} ${TARGET.posix}.map --entry=${HEXAGON_IMAGE_ENTRY} ${LFLAGS} ")
   env.Replace(LINK_DIRS = "-L${QDSP6_RELEASE_LIB_DIR}")
   env.Replace(CRT = '${Q6_RTOS_LIBS}/crt0.o')

   # LINK special case in hexagon world
   env.Replace(QDSP6OBJS1  = [
      '${CRT}',
      '${QDSP6_RELEASE_LIB_DIR}/init.o',
   ])

   env.Replace(QDSP6OBJS3  = [
      '${QDSP6_RELEASE_LIB_DIR}/libc.a',
      '${QDSP6_RELEASE_LIB_DIR}/libqcc.a',
      '${QDSP6_RELEASE_LIB_DIR}/libstdc++.a',
      '${Q6_RTOS_LIBS}/libqurt.a',
      '${Q6_RTOS_LIBS}/libqurtcfs.a',
      '${Q6_RTOS_LIBS}/libqurtkernel.a',
      '${Q6_RTOS_LIBS}/libqube_compat.a',
      '${Q6_RTOS_LIBS}/libtimer.a',
      '${Q6_RTOS_LIBS}/libposix.a',
      #'${LIB_DSP_ROOT}/libqdsp.a'
   ])
   if (q6_tool_major > 6):
      env.Append(QDSP6OBJS3 = ['${LIB_DSP_ROOT}/libhexagon.a'])
   else:
      env.Append(QDSP6OBJS3 = ['${LIB_DSP_ROOT}/libqdsp.a'])

   env.Replace(QDSP6OBJS4  = [
      '${QDSP6_RELEASE_LIB_DIR}/fini.o',\
   ])

   #-------------------------------------------------------------------------------------
   # if $SOURCES doesn't have any items in it, python is throwing an error $SOURCES.posix.
   # When linking there should always be at least one obj it is the entry point.
   # SOURCES should never be emty if it is someone added objects to library list instead
   # of object list. Fix that isntead of trying to get creative here.
   #-------------------------------------------------------------------------------------
   env.Replace(LINKOBJGRP = "--start-group ${QDSP6OBJS1} ${QDSP6OBJS3} " \
      "$_LIBFLAGS_POSIX  $SOURCES.posix ${QDSP6OBJS} --end-group ${QDSP6OBJS4}"
   )

   #cd $(TARGET_NAME); $(LD) $(LINKFLAGS) $(LINK_DIRS) $(LINKOBJGRP) $(OBJ_CMD) $(TARGET_NAME).$(EXETYPE) -Map $(TARGET_NAME).map; mv $(TARGET_NAME).$(EXETYPE) ../$(TARGET_NAME).$(EXETYPE); mv $(TARGET_NAME).map ../$(TARGET_NAME).map
   #$(CC) -nostdlib -nostartfiles -g -Xlinker --gc-sections -Xlinker -mv2 -moslib=qube -Xlinker -m$(Q6VERSION) -Xlinker --entry=_start -Xlinker --section-start -Xlinker .start=0x01200000 $(QDSP6_BINDIR)/lib/qube/qdsp6v2/ig_server -o ig_server.reloc
   #$(CC) -nostdlib -nostartfiles -g -Xlinker --gc-sections -Xlinker -mv2 -moslib=qube -Xlinker -m$(Q6VERSION) -Xlinker --entry=_start -Xlinker --section-start -Xlinker .start=0x01300000 $(TARGET_NAME).$(EXETYPE) -o $(TARGET_NAME).reloc

   env.Replace(LINKCOM = "${TEMPFILE('$LINK $LINKFLAGS $LINK_DIRS $LINKOBJGRP $HEXAGON_OUTPUT_CMD $TARGET.posix $LINKFLAGS_END')}")

