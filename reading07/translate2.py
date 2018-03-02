#!/usr/bin/env python3

#cat /etc/passwd | cut -d : -f 5 | grep -Po '[Uu]ser' | wc -l

import re
import os
import sys

PATH = "/etc/passwd"
DELIM = ":"
FIELD = 5

cut_list = [line.split(DELIM)[FIELD - 1] for line in open(PATH)]
grep_list = [re.findall('[Uu]ser', items) for items in cut_list if re.findall('[Uu]ser', items)]
wc_list = len(grep_list)

print(wc_list)

