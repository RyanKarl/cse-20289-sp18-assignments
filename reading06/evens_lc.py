#!/usr/bin/env python3

import sys

print(' '.join([str.strip(x) for x in sys.stdin if int(x) % 2 == 0]))

