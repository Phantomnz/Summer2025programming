# This an extreme practice day for Python jumping from day 6 to day 10 in one go

# day 6 content:

# modules and imports - Use import module to access functions and variables defined elsewhere, for example:
# in math.py you would have: 
# def square(x): return x * x
# IN main.py you would then use: 
# import math
# print(math.square(5))


# from ... import ... - more specific import, imports specific names directly into the current namespace
# from math import square
# print(square(5)) which would give 25


# __name__ == "__main__" guard - Ensures that main() runs only when the script is executed directly, not when imported as a module.
def main():
    print("Hello, World!") # This is the main function that will be executed when the script runs.
if __name__ == "__main__": # This checks if the script is being run directly
    main() # This will run main() only if this script is executed directly, not when imported.


# Virtual environments - Isolates dependencies per project to avoid version conflicts.
# To create a virtual environment, run the following command in your terminal:
# python3 -m venv venv  # Creates a virtual environment named 'venv'


# pip Package management - pip installs packages from the Python Package Index (PyPI) and can export your project's dependencies to a requirements.txt file.
# To install a package, use in the terminal:
# pip install package_name  # Installs a package
# To export dependencies, use in the terminal:
# pip freeze > requirements.txt  # Exports installed packages to a requirements.txt file
# pip show flask  # Shows information about the Flask package


# day 7 content:

# File I\O modes - "w" overwrites the file, "a" appends to the file, "r" reads the file. with ensures the file is closed after the block.
with open("example.txt", "w") as file:  # Opens example.txt in write mode
    file.write("Hello, World!\n")  # Writes to the file
with open("example.txt", "a") as file:  # Opens example.txt in append mode
    file.write("Appending a new line.\n")  # Appends to the file


# Binary File I\O - Use "rb" for reading binary files and "wb" for writing binary files. for non-text files like images.
# with open("image.png", "rb") as file:  # Opens image.png in binary read mode
#     data = file.read()  # Reads the binary data


# JSON serialization - Convert between Python dictionaries and JSON strings using the json module.
import json  # Import the json module for JSON serialization
data = {"name": "Alice", "age": 30}  # Example dictionary
json_string = json.dumps(data)  # Convert dictionary to JSON string
print(json_string)  # Print the JSON string
obj = json.loads(json_string)  # Convert JSON string back to dictionary


# HTTP requests with requests - Simplest way to call REST APIs and parse JSON responses
# import requests  # Import the requests module for making HTTP requests
# r = requests.get("https://api.example.com/data")  # Make a GET request to the API
# print(r.json())  # Print the JSON response from the API


# argparse for command-line arguments
import argparse  # Import the argparse module for parsing command-line arguments
p = argparse.ArgumentParser(description="Example script with command-line arguments")  # Create an ArgumentParser object
p.add_argument("--name", type=str, help="Your name")  # Add an argument for the user's name
args = p.parse_args()  # Parse the command-line arguments
print(args.name) # Print the value of the name argument if provided


# day 8 content:

# List vs Generator Comprehension - [] builds a list, while () builds a generator.
lst = [x * x for x in range(10)]  # List comprehension
gen = (x * x for x in range(10))  # Generator comprehension
print(lst)  # Prints the list
print(gen)  # Prints the generator object


# itertools Basics - itertools provides efficient looping constructs (permutations, combinations, infinite counters, etc.)
import itertools  # Import the itertools module for advanced looping constructs
for combo in itertools.combinations(range(5), 3):  # Generate combinations of 3 from range(5)
    print(combo)  # Print each combination


# Decorators - Wrap functions with pre/post behaviour using the @decorator syntax.
def timer(fn):
    import time # Import the time module for measuring execution time
    def wrapper(*args, **kw):
        start = time.time()  # Record the start time
        result = fn(*args, **kw)  # Call the original function
        print("Elapsed time:", time.time() - start)  # Print the elapsed time
        return result
    return wrapper
@timer  # Apply the timer decorator to the function
def add(x, y):
    return x + y
add(5, 10)  # Call the decorated function, which will print the elapsed time


# Context Managers for Custom objects - Implement __enter__ and __exit__ methods to use with the 'with' in your custom classes.
class ctx:
    def __enter__(self):
        print("Enter") # This method is called when entering the context
    def __exit__(self, exc_type, exc, tb): 
        print("Exit") # This method is called when exiting the context

with ctx():
    print("Inside context")


# Type hints - Annotate function signatures for better editor support and static analysis
def greet(name: str, times: int) -> None: # Function to greet a user specified number of times
    for _ in range(times): # Print the greeting multiple times
        print(f"Hello, {name}!") 
greet("Alice", 3)  # Call the function with type hints

# day 9 content:

# collections.Counter - Counts occurrences in iterables with convenient methods
from collections import Counter  # Import the Counter class from the collections module
cnt = Counter("hello world")  # Count occurrences of characters in the string
print(cnt.most_common(2))  # Print the two most common characters and their counts


# dataclasses - Auto-generates __init__, __repr__, and more for simple data containers
from dataclasses import dataclass  # Import the dataclass decorator
@dataclass  # Decorator to create a data class
class Point:
    x: int
    y: int

p = Point(10, 20)  # Create an instance of the Point data class
print(p)  # Print the data class instance, which uses the auto-generated __repr__


# pathlib for Filesystem paths - Object-oriented path manipulation, easier than os.path
from pathlib import Path  # Import the Path class from the pathlib module
p = Path("data") / "file.txt"  # Create a Path object for the file
print(p.exists())  # Check if the file exists


# Asynchronous programming with asyncio - async/await for non-blocking concurrency
import asyncio  # Import the asyncio module for asynchronous programming
async def say(msg):
    print(msg)  # Asynchronous function to print a message
    await asyncio.sleep(1)  # Simulate a non-blocking delay

asyncio.run(asyncio.gather(say ("Hello"), say("World")))  # Run multiple asynchronous tasks concurrently


# Multiprocessing basics - Spawn seperate processes to bypass the Global Interpreter Lock (GIL) for CPU-bound tasks
from multiprocessing import Process  # Import the Process class from the multiprocessing module
def task(name):
    print(f"Task {name} is running")  # Function to run in a separate process
if __name__ == "__main__":  # Ensure this block runs only when the script is executed directly
    processes = [Process(target=task, args=(1,)), Process(target=task, args=(2,))]  # Create two processes
    p.start()  # Start the first process
    p.join()  # Wait for the first process to finish

# day 10 content:

# File Watching with watchdog - React to filesystem events in real-time (requires pip install watchdog)
from watchdog.observers import Observer  # Import the Observer class from watchdog
from watchdog.events import FileSystemEventHandler  # Import the FileSystemEventHandler class

class Handler(FileSystemEventHandler):  # Custom event handler class
    def on_modified(self, event):  # Method called when a file is modified
        print(f"File {event.src_path} has been modified")  # Print the modified file path

obs = Observer()  # Create an Observer object
obs.schedule(Handler(), path='.', recursive=False)  # Schedule the handler for the current directory
obs.start()  # Start the observer to watch for events


# Virtualenv Activation Script - Activates the enviroment so python and pip point to your virtual environment
# On Windows, run: .venv\Scripts\activate
# On macOS/Linux, run: source .venv/bin/activate


# Profiling with cProfile - Reports function call counts and timings to help optimize hotspots
# python -m cProfile -s time d6practiceEX.py  # Run the script with cProfile to profile its performance

# Logging Module - Replace print() with structured logs and levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
import logging  # Import the logging module for structured logging
logging.basicConfig(level=logging.INFO)  # Configure the logging level
logger = logging.getLogger(__name__)  # Create a logger for the current module
logger.info("This is an info message")  # Log an info message

# Packaging with setuptools
# in setup.py you would have:
# from setuptools import setup, find_packages
# setup(name="mypkg", version="0.1", packages=find_packages())


