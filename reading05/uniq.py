#!/usr/bin/env python3

import os
import sys

# Global Variables

COUNT = False

# Usage function

def usage(status=0):
    print('''Usage: uniq.py files...

    -c  prefix lines by the number of occurrences'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-c':
        COUNT = True
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if not args:
    args.append('-')

# Main execution

dictionary = {}

for path in args:
    stream = sys.stdin if path == '-' else open(path)

    for line in stream:
        line = line.rstrip()
        dictionary[line] = dictionary.get(line, 0) + 1
if COUNT == True:
    for key in dictionary:   
            print('{:>7} {}'.format(str(dictionary[key]), key))
else:
    for key in dictionary:
        print(key)


