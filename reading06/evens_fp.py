#!/usr/bin/env python3

import sys

print(' '.join(filter(lambda x: int(x) % 2 == 0, map(str.strip, sys.stdin))))


