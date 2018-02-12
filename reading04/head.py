#!/usr/bin/env python3

import os
import sys

# Global Variables

ENDING = 10

# Usage function

def usage(status):
    print('''Usage: head.py files...
    -n  NUM      print the first NUM lines instead of the first 10'''.format(os.path.basename(sys.argv[0]))) 
    sys.exit(status)
    
# Parse command line options

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-n':
        ENDING = args.pop(0)
    elif arg == '-h':
        usage(0)

if len(args) == 0:
    args.append('-')

# Main execution

ENDING = int(ENDING)

for path in args:
    if path == '-':
        stream = sys.stdin
    else:
        stream = open(path)
#    ENDING = int(ENDING)
#    print(stream)
#    print(path)
    N = 0
    for line in stream:
        if N < ENDING:    
            print(line.rstrip())
#            print(ENDING)
            N = N + 1
    stream.close()
