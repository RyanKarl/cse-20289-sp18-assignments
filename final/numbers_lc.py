#!/usr/bin/env python3

import os
import sys

# Main execution

numbers = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
fives = []

fives = [x for x in numbers if not x % 5]

print(fives)

#for val in numbers:
#    if (val % 5 == 0):
#        fives.append(val)

#for item in fives:
#    print(item)

