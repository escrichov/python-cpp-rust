from distutils.core import setup, Extension


setup(
    ext_modules=[
        Extension(
            '_mylibcswig',
            sources=['mylibcswig.i', 'mylibcswig.c'],
            depends=['setup.py', 'mylibcswig.h']
        )
    ]
)
