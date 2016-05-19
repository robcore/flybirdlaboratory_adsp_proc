import sys
import re

input=str(sys.argv[1])

f_out = open(input,"w")

Pythonversion = sys.version
Pythonversion1 = Pythonversion.split() 
f_out.write('Python Version Installed : v' + Pythonversion1[0] + '\n' )


f_out.close()
