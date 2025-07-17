# Custom Iterators - By implementing __iter__() and __next__(), you make your class behave like a built-in sequence in loops
class Countdown:
    def __init__(self, start):
        self.current = start # Initialize the countdown starting point
    def __iter__(self):
        return self # The __iter__ method returns the iterator object itself
    def __next__(self):
        if self.current <= 0: # If the countdown has reached zero
            raise StopIteration # Stop the iteration
        value = self.current # Store the current value
        self.current -= 1 # Decrement the current value
        return value # Return the current value for the iteration

for num in Countdown(5): # Iterate through the countdown from 5 to 1
    print(num) # Print each number in the countdown

# Metaclasses - Metaclasses allow you to customize class creation. Here it will transform all attribute name to uppercase
class Upperattrmeta(type): # Define a metaclass that modifies class attributes
    def __new__(cls, name, bases, dct): # Define a new metaclass that modifies the class creation process
        uppercase_attrs = { k.upper(): v for k, v in dct.items() if not k.startswith('__')} # Create a new dictionary with uppercase keys for attributes
        return super().__new__(cls, name, bases, uppercase_attrs) # Call the superclass to create the class with modified attributes
class person(metaclass=Upperattrmeta): # Define a class using the Upperattrmeta metaclass
    name = 'John' # Define an attribute 'name'
    age = 30 # Define an attribute 'age'
print(hasattr(person, 'AGE')) # Check if the uppercase attribute 'AGE' exists, true
print(hasattr(person, 'name')) # Check if the lowercase attribute 'name' exists, false
print(hasattr(person, 'NAME')) # Check if the uppercase attribute 'NAME' exists, true

# Type hints & mypy - Annotations don't enforce types at runtime but enable tools like mypy to catch mismatches before execution
from typing import List
def sum_list(nums: List[int]) -> int: # Function that takes a list of integers and returns an integer
    return sum(nums) # Return the sum of the list
# run static checker mypy to check for type errors
# mypy d11practice.py  Command to run mypy on this file to check for type errors

# asyncio.wait_for with Timeout - wait_for() lets you bound an await with a timeout, raising TimeoutError if it exceeds
import asyncio  # Import the asyncio module for asynchronous programming
async def sleepy(n): # Define an asynchronous function that sleeps for n seconds
    await asyncio.sleep(n)  # Asynchronously sleep for n seconds
    return f"Slept {n} seconds"  # Return a message indicating how long it slept
async def main(): # Define the main asynchronous function
    try:
        result = await asyncio.wait_for(sleepy(5), timeout=2)  # Wait for the sleepy function to complete with a timeout of 2 seconds
        print(result)  # Print the result if it completes within the timeout
    except asyncio.TimeoutError:  # Catch the TimeoutError if the function takes too long
        print("Operation timed out")  # Print a timeout message
asyncio.run(main())  # Run the main function using asyncio's event loop

# Basic pandas DataFrame Usage - pandas provide powerful table-like structures. DataFrame.head() shows the first few rows, ideal for quick data inspection
import pandas as pd  # Import the pandas library for data manipulation
df = pd.DataFrame({  # Create a DataFrame with sample data
    'name': ['Alice', 'Bob', 'Charlie'],  # Column for names
    'score': [85, 90, 95]  # Column for scores
})
print(df.head())  # Print the first few rows of the DataFrame for inspection