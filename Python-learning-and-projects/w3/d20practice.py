# Asynchronous Generators - async def + yield make an async generator. You iterate with async for, and can await inside the generator.
import asyncio
async def countdown(n):
    while n > 0:
        yield n # Yield the current value of n
        n -= 1 # Decrement n
        await asyncio.sleep(1)  # Simulate a delay  
async def main():
    async for number in countdown(5):  # Use async for to iterate over the async generator
        print(number)  # Print the yielded value
asyncio.run(main())  # Run the main coroutine

# __slots__ to reduce memory - Defining __slots__ prevents the creation of __dict__ per instance, saving memory when you have many instances.
class Point:
    __slots__ = ('x', 'y')  # Define the allowed attributes
    def __init__(self, x, y): # Initialize the attributes
        self.x = x # Set the x coordinate
        self.y = y # Set the y coordinate

# Function Annotations and get_type_hints() - Annotations stored in __annotations__ can be retrieved at runtime for introspection or validation.
from typing import get_type_hints
def func(a: int, b: str) -> bool:
    return str(a) == b

hints = get_type_hints(func)  # Get the type hints of the function
print(hints)  # Output: {'a': <class 'int'>, 'b': <class 'str'>, 'return': <class 'bool'>}

# Context Variables for Async State - ContextVar maintains seperate values per async task, unlike globals
import asyncio
from contextvars import ContextVar
user = ContextVar('user', default='guest')  # Create a context variable with a default value
async def greet():
    print(f"Hello, {user.get()}!")  # Get the value of the context variable

async def main():
    token = user.set('Alice')  # Set a new value for the context variable
    await greet()  # Call the greet function
    user.reset(token)  # Reset the context variable to its previous value
    await greet()  # Call the greet function again
asyncio.run(main())  # Run the main coroutine

# TypedDict for Structured Dicts - TypedDict lets you define the expected keys and value types for dictionaries, improving type-checking.
from typing_extensions import TypedDict
class Movie(TypedDict):
    title: str  # Title of the movie
    year: int  # Release year of the movie
    
def print_movie(m: Movie):
    print(f"{m['title']} ({m['year']})")  # Print the movie title and year
movie = Movie(title="Inception", year=2010)  # Create a TypedDict instance
print_movie(movie)  # Call the function with the TypedDict instance
