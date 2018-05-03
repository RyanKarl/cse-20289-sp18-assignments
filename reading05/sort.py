#!/usr/bin/env python3

import os
import sys

# Global Variables

REVERSE = False

# Usage function

def usage(status=0):
    print('''Usage: sort.py files...

    -r  reverse the result of comparisons'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-r':
        REVERSE = True
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if not args:
    args.append('-')

# Main execution

list = []

for path in args:
    stream = sys.stdin if path == '-' else open(path)

    for line in stream:
        line = line.rstrip()
        list.append(line)
    list.sort(reverse=REVERSE)
    
    for items in list:
        print(items)
