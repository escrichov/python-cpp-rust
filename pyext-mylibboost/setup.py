#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension

setup(name="mylibboost",
    ext_modules=[
        Extension("mylibboost", ["mylibboost.cpp"],
        libraries = ["boost_python"])
    ])
