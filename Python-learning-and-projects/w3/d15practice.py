# enum.Enum for Enumerations - Enum classes let you define named immutable contants. Access .name and .value for introspection.
from enum import Enum
class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3
print(Color.RED, Color.RED.name, Color.RED.value)
# output: Color.RED RED 1

# math.comb() for combinations - returns the binomial coefficient "5 choose 2" (number of ways to choose 2 items from 5) without importing additional libraries.
import math
print(math.comb(5, 2))  # output: 10

# Reading Binary Files with Path.read_bytes() - Quickly load an entire file into memory as bytes; useful for hashing or processing non-text files
from pathlib import Path
try:
    data = Path('d16practice.py').read_bytes() # read the file as bytes
    print(len(data), "bytes read from d16practice.py")  # output: <length> bytes read from d16practice.py
except FileNotFoundError:
    try:
        current_dir = Path(__file__).parent  # get the directory where this file resides
        file_path = current_dir / 'd16practice.py' # construct the path to d16practice.py
        data = file_path.read_bytes() # read the file as bytes
        print(len(data), "bytes read from d16practice.py") # output: <length> bytes read from d16practice.py
    except FileNotFoundError:
        print("File d16practice.py not found.") # output: File d16practice.py not found.

# subprocess.Popen() with Streaming I/O - Popen gives you a live handle to the process' stdout, letting you process output line-by-line as it happens.
import subprocess
proc = subprocess.Popen( ["ping", "-c", "4", "google.com"], stdout=subprocess.PIPE, text=True) # ping google.com and capture output
for line in proc.stdout:  # iterate over each line of output
    print(">>", line.strip())  # output each line as it comes in
proc.wait()  # wait for the process to finish

# Dynamic Imports via importlib - Load modules when you only know their names at runtime -- great for plugins systems or conditional feature loading.
import importlib
module_math = "math"  # module name as a string
math_mod = importlib.import_module(module_math)  # dynamically import the module
print(math_mod.sqrt(16))  # output: 4.0 (using the dynamically imported math module)

