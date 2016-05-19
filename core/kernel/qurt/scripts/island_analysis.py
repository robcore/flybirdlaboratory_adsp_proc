#===============================================================================
#                    Copyright (c) 2013  by Qualcomm Technologies, Inc.  All Rights Reserved.
#                         QUALCOMM Proprietary/GTDR
#===============================================================================
import os

#----------------------------------------------------------------------------
# Hooks for SCons
#----------------------------------------------------------------------------
def exists(env):
   return env.Detect('island_analysis')

def generate(env):
    island_analysis_generate(env)
    
def island_analysis_generate(env):
    env.AddMethod(island_analysis_builder_wrapper, "IslandAnalysis")
    island_analysis_bld = env.Builder(action = island_analysis_builder)
    env['BUILDERS']['IslandAnalysisInternalBuilder'] = island_analysis_bld

def island_analysis_builder_wrapper(env, target, source, libdirs=[], ignorelist=[]):
    env.Replace(ISLAND_ANALYSIS_LIBDIRS = libdirs)
    env.Replace(ISLAND_ANALYSIS_IGNORELIST = ignorelist)
    return env.IslandAnalysisInternalBuilder(target, source)

def island_analysis_builder(target, source, env):
    libdirs = env.get('ISLAND_ANALYSIS_LIBDIRS')
    ignorelist = env.get('ISLAND_ANALYSIS_IGNORELIST')
    if int(env.get('HEXAGON_RTOS_RELEASE').split(".")[0]) >= 7:
        env.Replace(IA_OBJDUMP = "${QDSP6BIN}/hexagon-llvm-objdump${EXE_EXT}")
    else:
        env.Replace(IA_OBJDUMP = "${QDSP6BIN}/hexagon-objdump${EXE_EXT}")
    analysis_cmd = "python ${BUILD_ROOT}/core/kernel/qurt/scripts/list_extref.py -v -e ${IA_OBJDUMP} "
    for src in source:
        analysis_cmd += "-s "+str(src)+" "
    for libdir in libdirs:
        analysis_cmd += "-l "+libdir+" "
    for ilist in ignorelist:
        analysis_cmd += "-i "+ilist+" "
    analysis_cmd = env.subst(analysis_cmd)
    analysis_cmd = analysis_cmd+" > "+str(target[0])

    print analysis_cmd
    #std_out, std_err, return_val = env.ExecCmds(analysis_cmd)
    os.system(analysis_cmd)
    #return target
