import re
import string
import random
import itertools
import numpy as np
import myrustlib  # <-- Importing Rust Implemented Library

import sys
sys.path.append('./pyext-mylibcswig')

import mylibpybind11
import mylibcython
import mylibcswig  # <-- Importing C Implemented Library with Swift
import mylibcpython # <-- Importing C Implemented Library with Python.h
#import mylibboost # <-- Importing C++ Implemented Library with Python Boost


def count_doubles(val):
    total = 0
    for c1, c2 in zip(val, val[1:]):
        if c1 == c2:
            total += 1
    return total


def count_doubles_once(val):
    total = 0
    chars = iter(val)
    c1 = next(chars)
    for c2 in chars:
        if c1 == c2:
            total += 1
        c1 = c2
    return total


def count_doubles_itertools(val):
    c1s, c2s = itertools.tee(val)
    next(c2s, None)
    total = 0
    for c1, c2 in zip(c1s, c2s):
        if c1 == c2:
            total += 1
    return total


double_re = re.compile(r'(?=(.)\1)')


def count_double_regex(val):
    return len(double_re.findall(val))


def count_double_numpy(val):
    ng = np.frombuffer(bytes(val, 'utf-8'), dtype=np.byte)
    return np.sum(ng[:-1] == ng[1:])


def count_doubles_comprehension(val):
    return sum(1 for c1, c2 in zip(val, val[1:]) if c1 == c2)


val = ''.join(random.choice(string.ascii_letters) for i in range(1000000))


def test_pure_python(benchmark):
    print(benchmark(count_doubles, val))


def test_pure_python_once(benchmark):
    print(benchmark(count_doubles_once, val))


def test_itertools(benchmark):
    print(benchmark(count_doubles_itertools, val))


def test_regex(benchmark):
    print(benchmark(count_double_regex, val))


def test_numpy(benchmark):
    print(benchmark(count_double_numpy, val))


def test_python_comprehension(benchmark):
    print(benchmark(count_doubles_comprehension, val))


def test_rust(benchmark):
    print(benchmark(myrustlib.count_doubles, val))


def test_rust_once(benchmark):
    print(benchmark(myrustlib.count_doubles_once, val))


def test_rust_bytes_once(benchmark):
    print(benchmark(myrustlib.count_doubles_once_bytes, val))


def test_c_swig_bytes_once(benchmark):
    print(benchmark(mylibcswig.count_byte_doubles, val))


def test_c_python_bytes_once(benchmark):
    print(benchmark(mylibcpython.count_byte_doubles, val))

def test_cython_bytes_once(benchmark):
    print(benchmark(mylibcython.count_doubles_once, val))

def test_pybind11_bytes_once(benchmark):
    print(benchmark(mylibpybind11.count_byte_doubles, val))
