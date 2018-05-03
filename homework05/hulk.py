#!/usr/bin/env python3

import functools
import hashlib
import itertools
import multiprocessing
import os
import string
import sys

# Constants

ALPHABET    = string.ascii_lowercase + string.digits
ARGUMENTS   = sys.argv[1:]
CORES       = 1
HASHES      = 'hashes.txt'
LENGTH      = 1
PREFIX      = ''

# Functions

def usage(exit_code=0):
    print('''Usage: {} [-a alphabet -c CORES -l LENGTH -p PREFIX -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file'''.format(os.path.basename(sys.argv[0])))
    sys.exit(exit_code)

def sha1sum(s):
    '''Generate sha1 digest for given string.

        >>> sha1sum('abc')
        'a9993e364706816aba3e25717850c26c9cd0d89d'

        >>> sha1sum('wake me up inside')
        '5bfb1100e6ef294554c1e99ff35ad11db6d7b67b'

        >>> sha1sum('baby now we got bad blood')
        '9c6d9c069682759c941a6206f08fb013c55a0a6e'
    '''
    # TODO: Implement
    #Use hashlib to encode sha1 in hex format
    hash = hashlib.sha1(s.encode()).hexdigest()
    return hash

def permutations(length, alphabet=ALPHABET):
    ''' Recursively yield all permutations of alphabet up to provided length.

    >>> list(permutations(1, 'ab'))
    ['a', 'b']

    >>> list(permutations(2, 'ab'))
    ['aa', 'ab', 'ba', 'bb']

    >>> list(permutations(1))       # doctest: +ELLIPSIS
    ['a', 'b', ..., '9']

    >>> list(permutations(2))       # doctest: +ELLIPSIS
    ['aa', 'ab', ..., '99']

    >>> import inspect; inspect.isgeneratorfunction(permutations)
    True
    '''
    # TODO: Implement as generator
    #Establish base case for generator
    if length == 1:
        for letter in alphabet:
            yield letter
    #Build permutations recursively based on length
    else:
        for value in alphabet:
            for element in permutations(length-1, alphabet):
                yield value + element

def smash(hashes, length, alphabet=ALPHABET, prefix=''):
    ''' Return all password permutations of specified length that are in hashes

    >>> smash([sha1sum('ab')], 2)
    ['ab']

    >>> smash([sha1sum('abc')], 2, prefix='a')
    ['abc']

    >>> smash(map(sha1sum, 'abc'), 1, 'abc')
    ['a', 'b', 'c']
    '''
    # TODO: Implement with list or generator comprehensions
    p = permutations(length, alphabet)
    #Use generator comprehension to build list
    possibilities = (prefix + element for element in p)
    #Use list comprehension to store values generated
    smashed = [value for value in possibilities if sha1sum(value) in hashes]

    return smashed

if __name__ == '__main__':
    # Parse command line arguments

    while ARGUMENTS:
        arg = ARGUMENTS.pop(0)
        if arg == '-a':
            ALPHABET = ARGUMENTS.pop(0)
        elif arg == '-c':
            CORES = int(ARGUMENTS.pop(0))
        elif arg == '-l':
            LENGTH = int(ARGUMENTS.pop(0))
        elif arg == '-p':
            PREFIX = ARGUMENTS.pop(0)
        elif arg == '-s':
            HASHES = ARGUMENTS.pop(0)
        elif arg == '-h':
            usage(0)
        else:
            usage(1)

    # Load hashes set
    hash_set = set()
    for line in open(HASHES):
        line = line.rstrip()
        hash_set.add(line)
        
# Execute smash function
    passwords = []

    # Allow for multiprocessing based on number of cores specified
    if CORES > 1 and LENGTH > 1:
        subsmash = functools.partial(smash, hash_set, LENGTH - 1, ALPHABET)
        pool = multiprocessing.Pool(CORES)
        #Build prefixes to simplify cracking
        prefixes = [PREFIX + a for a in ALPHABET] 
        passwords = itertools.chain.from_iterable(pool.imap(subsmash, prefixes))
    else:
        passwords = smash(hash_set, LENGTH, ALPHABET, PREFIX) 

# Print passwords
    for p in passwords:
        print(p)

    
# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
