''' Builder '''
import os
import sys
from SCons.Script import *

def exists(env):
   return env.Detect('imagebuild_generator')

def imagebuild_generator(source, target, env, for_signature):
   ''' Find the "best" python interpreter to use '''
   ''' Execute the following strings one at a time,
       catching errors on a per line basis, until we get an interpreter '''
   interp = None
   for s in ['interp = env["PYTHON_INTERP"]',
             'import SCons',
             'interp = SCons.Util.python_interpreter_command()',
             'import sys',
             'interp = sys.executable',
             'interp = SCons.Util.WhereIs("python")',
             'interp = "python"']:
      if not interp:
         try:
            exec(s)
         except Exception:
            pass
   return ' '.join(Flatten([interp,
                            [str(w) for w in source if str(w).endswith('.py')],
                            [str(w) for w in source if str(w).endswith('.elf')],
                            '-o',
                            [str(w) for w in target if str(w).endswith('.pbn')],
                            '-p',
                            env['PHYS_ADDR']]))
def imagebuild_emitter(target, source, env):
   ''' For each foo.elf in the sources, add foo_reloc.elf in the targets '''
   ntargets = ['_reloc.'.join(str(w).rsplit('.',1))
               for w in source if str(w).endswith('.elf')]
   return (target + ntargets, source)

def generate(env):
   env['BUILDERS']['ImageBuild'] = Builder(generator = imagebuild_generator, emitter = imagebuild_emitter, PHYS_ADDR='0x1e000000')

