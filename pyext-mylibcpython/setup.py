from distutils.core import setup, Extension
setup(name = 'mylibcpython', version = '1.0',  \
   ext_modules = [Extension('mylibcpython', ['mylibcpython.c'])])