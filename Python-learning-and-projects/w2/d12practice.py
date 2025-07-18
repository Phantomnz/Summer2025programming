# Custom Exceptions - Define your own exception type by subclassing Exception. Raising and catching specific exceptions makes error handling clearer
class ValidationError(Exception):
    pass # Custom exception for validation errors
def validate_age(age):
    if age < 0: # Check if age is negative
        raise ValidationError("Age cannot be negative")
try:
    validate_age(-5)
except ValidationError as e:
    print(f"Validation error occurred: {e}") # Custom exception handling

# Context Managers via contextlib - The @contextmaager decorator lets you write simpler context managers without defining __enter__ and __exit__ methods
from contextlib import contextmanager

@contextmanager
def open_file(path):
    f = open(path) # Open a file and ensure it gets closed after use
    try:
        yield f # Yield the file object to the caller
    finally:
        f.close() # Ensure the file is closed after use

# with open_file("data.txt") as f: # Use the context manager to open a file
#    print(f.read()) # Regular expression search # Example usage of the context manager

# Path Globbing with glob - The glob module finds files matching Unix shell-style patterns, useful for batch processing
import glob
for filename in glob.glob("*.py"): # Find all Python files in the current directory
    print(f"Found Python file: {filename}") # Search for a pattern in the text

# Regular Expressions with re - Use re.search() to find a pattern in a string, re.sub() to replace parts of a string, and re.compile() for performance with repeated use. r"..." creates a raw string so backslashes aren't interpreted by Python"
import re
text = "contact: alice@example.com"
match = re.search(r"[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+", text) # Search for an email pattern
if match:
    print(f"Found email: {match.group()}") # Print the found email address

# Itertools.groupby() for Grouping - groupby() groups consecutive items by a key function. Useful for summarizing sorted data
import itertools
data = [("fruit", "apple"), ("fruit", "banana"), ("fruit", "cherry"), ("vegetable", "carrot"), ("vegetable", "pea")] # Example data to group
for key, group in itertools.groupby(data, key=lambda x: x[0]): # Group by the first element of each tuple
    print(key, [item for _, item in group]) # Print the key and the grouped items