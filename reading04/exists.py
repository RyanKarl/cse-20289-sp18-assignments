#!/usr/bin/env python3

import sys
import os

if len(sys.argv) == 1:
   print("Usage: exists.sh file0...")
   exit(1)

CODE=0

for arg in sys.argv[1:]:
   if os.path.isfile(arg):
      print(arg + " exists!")
   else:
      print (arg + " does not exist!")
      CODE=1
exit(CODE)
