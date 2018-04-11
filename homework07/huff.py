#!/usr/bin/env python3

import sys
import os
import yaml

print('|        FILE        | OLD SIZE | NEW SIZE |   RATIO   |');
print('|--------------------|----------|----------|-----------|');

names = os.listdir('data')

for name in names:
    path = 'data/' + name
    old_size = (os.stat(path).st_size)*8
    data = yaml.load(os.popen('./huff -f yaml {}'.format(path)))
    new_encoding = 0;
    for k in data.keys():
        sum_of_bits = len(data[k]['encoding']) * data[k]['count']
        new_encoding += sum_of_bits
    new_size = new_encoding
    ratio = (new_size/old_size)*100
    r = round(ratio, 2)
    print('|{:>20}|{:>10}|{:>10}|{:>10}%|'.format(path, old_size, new_size, r))
