#!/usr/bin/env python3

#ls -l /etc | awk '{print $2}' | sort | uniq -c

import re
import os
import sys
import requests

DELIM = ""
FIELD = 2

ls_list = os.popen('ls -l /etc').read().splitlines()
cut_list = [line.split()[FIELD - 1] for line in ls_list]

dictionary = {key: cut_list.count(key) for key in cut_list}

for key in sorted(dictionary):
        print('{:>7} {}'.format(str(dictionary[key]), key))


