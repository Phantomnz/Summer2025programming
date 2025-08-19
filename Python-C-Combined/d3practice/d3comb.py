# Usually in a project this would be called setup.py
from setuptools import setup, Extension
setup(
    name="d3comb",
    ext_modules=[
        Extension("d3comb", sources=["d3comb.c"]) # This is the extension module
    ]
)