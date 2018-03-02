#!/usr/bin/env python3

#grep -Po '9\d*9' /etc/passwd | wc -l

import re
import os
import sys

PATH = "/etc/passwd"
DELIM = ":"
FIELD = 1

grep_list = []
cut_list = [line.split(DELIM) for line in open(PATH)]
for val in cut_list:
    for item in val:
        if re.findall('9\d*9', item):
            grep_list.append(re.findall('9\d*9', item)) 
wc_list = len(grep_list)

print(wc_list)

