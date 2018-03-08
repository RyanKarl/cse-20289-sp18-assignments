#!/usr/bin/env python3

#curl -sL http://yld.me/raw/lmz | cut -d , -f 2 | grep -Eo '^B.*' | sort

import re
import os
import sys
import requests

PATH = "http://yld.me/raw/lmz"
DELIM = ","
FIELD = 2

response = requests.get(PATH)
curl_list = response.text.splitlines()
cut_list = [line.split(DELIM)[FIELD - 1] for line in curl_list]
grep_list = [items for items in cut_list if items[0] == 'B' and len(cut_list) >= 1]

for val in sorted(grep_list):
     print(val)

