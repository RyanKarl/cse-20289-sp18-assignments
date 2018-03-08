#!/usr/bin/env python3

import os
import sys

# Global Variables

DELIM = '/t'
FIELDS = ''

# Usage function

def usage(status=0):
    print('''Usage: cut.py files...

    -d  DELIM   use DELIM instead of TAB for field delimiter
    -f  FIELDS  select only these fields'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-d':
        DELIM = args.pop(0)
    elif arg == '-f':
        FIELDS = args.pop(0)
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if not args:
    args.append('-')

# Main execution

list = []
FIELDS = FIELDS.split(',') 
FIELDS = set(FIELDS)
FIELDS = sorted(FIELDS)



for path in args:
    stream = sys.stdin if path == '-' else open(path)

    for line in stream:
        line = line.rstrip()
        line = line.split(DELIM)
        list.append(line)

for items in list: 
    list2 = []    
    for numbers in FIELDS:
        list2.append((items[(int(numbers) - 1)])) 
    print(DELIM.join(list2))


