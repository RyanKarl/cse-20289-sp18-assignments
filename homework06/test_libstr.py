#!/usr/bin/env python3

import ctypes
import unittest

# Str Utilities - Library

libstr = ctypes.CDLL('./libstr.so')
libstr.str_lower.restype        = ctypes.c_char_p
libstr.str_upper.restype        = ctypes.c_char_p
libstr.str_startswith.restype   = ctypes.c_bool
libstr.str_endswith.restype     = ctypes.c_bool
libstr.str_chomp.restype        = ctypes.c_char_p
libstr.str_strip.restype        = ctypes.c_char_p
libstr.str_reverse.restype      = ctypes.c_char_p
libstr.str_translate.restype    = ctypes.c_char_p
libstr.str_to_int.restype       = ctypes.c_int

# Str Utilities - Test Case

class StrTestCase(unittest.TestCase):
    Points = 0

    def test_00_str_lower(self):
        words = [b'', b'abc', b'ABC', b'AbC']
        for s in map(ctypes.create_string_buffer, words):
            target = s.value.lower()
            self.assertTrue(libstr.str_lower(s) == target)
            StrTestCase.Points += 0.5 / len(words)

    def test_01_str_upper(self):
        words = [b'', b'abc', b'ABC', b'AbC']
        for s in map(ctypes.create_string_buffer, words):
            target = s.value.upper()
            self.assertTrue(libstr.str_upper(s) == target)
            StrTestCase.Points += 0.5 / len(words)

    def test_02_str_startswith(self):
        cases = [
            (b'', b''),
            (b'abc', b''),
            (b'abc', b'a'),
            (b'abc', b'ab'),
            (b'abc', b'abc'),
        ]
        for s, t in cases:
            self.assertTrue(libstr.str_startswith(s, t))
            StrTestCase.Points += 0.5 / len(cases)

        cases = [
            (b'', b'a'),
            (b'abc', b'bc'),
            (b'abc', b'aabc'),
            (b'abc', b' abc'),
        ]
        for s, t in cases:
            self.assertFalse(libstr.str_startswith(s, t))
            StrTestCase.Points += 0.5 / len(cases)

    def test_03_str_endswith(self):
        cases = [
            (b'', b''),
            (b'abc', b''),
            (b'abc', b'c'),
            (b'abc', b'bc'),
            (b'abc', b'abc'),
        ]
        for s, t in cases:
            self.assertTrue(libstr.str_endswith(s, t))
            StrTestCase.Points += 0.5 / len(cases)

        cases = [
            (b'', b'a'),
            (b'abc', b'a'),
            (b'abc', b'ab'),
            (b'abc', b'abc '),
            (b'bc', b'abc '),
            (b'bc', b'abc'),
        ]
        for s, t in cases:
            self.assertFalse(libstr.str_endswith(s, t))
            StrTestCase.Points += 0.5 / len(cases)
    
    def test_04_str_chomp(self):
        words = [b'', b'\n', b'abc', b'abc\n', b'\nabc']
        for s in map(ctypes.create_string_buffer, words):
            target = s.value.rstrip()
            self.assertTrue(libstr.str_chomp(s) == target)
            StrTestCase.Points += 0.75 / len(words)

    def test_05_str_strip(self):
        words = [b'', b' ', b' A', b'A ', b' A ', b' A B ']
        for s in map(ctypes.create_string_buffer, words):
            target = s.value.strip()
            self.assertTrue(libstr.str_strip(s) == target)
            StrTestCase.Points += 1.00 / len(words)

    def test_06_str_reverse(self):
        words = [b'', b' ', b' A', b'A ', b' A ', b' A B ']
        for s in map(ctypes.create_string_buffer, words):
            target= s.value[::-1]
            self.assertTrue(libstr.str_reverse(s) == target)
            StrTestCase.Points += 1.5 / len(words)

    def test_07_str_translate(self):
        cases = [
            (b'', b'', b'', b''),
            (b'hello', b'', b'430', b'hello'),
            (b'hello', b'aeo', b'', b'hello'),
            (b'hello', b'aeo', b'430', b'h3ll0'),
            (b' hello ', b'aeo', b'430', b' h3ll0 '),
            (b' hello ', b'aeol', b'4301', b' h3110 '),
        ]
        for a, b, c, d in cases:
            self.assertTrue(libstr.str_translate(a, b, c) == d)
            StrTestCase.Points += 1.5 / len(cases)

    def test_08_str_to_int(self):
        cases = (
            (b'0', 2),
            (b'1', 2),
            (b'10', 2),
            (b'11', 2),
            (b'0', 8),
            (b'44', 8),
            (b'644', 8),
            (b'0', 10),
            (b'9', 10),
            (b'10', 10),
            (b'19', 10),
            (b'0', 16),
            (b'A', 16),
            (b'AF', 16),
            (b'a', 16),
            (b'aF', 16),
        )

        for s, b in cases:
            self.assertTrue(libstr.str_to_int(s, b) == int(s, b))
            StrTestCase.Points += 1.25 / len(cases)

    @classmethod
    def setupClass(cls):
        cls.Points = 0

    @classmethod
    def tearDownClass(cls):
        print('   Score {:.2f}'.format(cls.Points))

# Main Execution

if __name__ == '__main__':
    unittest.main()
