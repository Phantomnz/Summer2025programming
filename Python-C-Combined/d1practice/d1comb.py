# Build the extension with setuptools
# Imagine this is a file called Setup.py
from setuptools import setup, Extension
setup(
    name="d1comb",
    version="1.0", 
    ext_modules=[Extension("d1comb", sources=["d1comb.c"])] # Build the C extension
)
# Install for dev and test the following in terminal:
# python -m pip install -U pip setuptools wheel
# python setup.py build_ext --inplace     # builds d1comb.*.so / .pyd next to sources
# python -c "import d1comb; print(d1comb.add(2, 3))"

# Why this matters: setuptools handles compiler flags/cross-platform details so you can import d1comb seamlessly like any other Python module