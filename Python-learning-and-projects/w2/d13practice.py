# Custom __repr__ for debugging - Defining __repr__ gives meaningful inspectable objects in the REPL and logs
class point:
    def __init__(self, x, y): # Initialize point with x and y coordinates
        self.x, self.y = x, y # Assign x and y to instance variables
    def __repr__(self): # Define the string representation of the point
        return f"point(x={self.x}, y={self.y})" # Return a string representation of the point

p = point(1, 2) # Create a point instance
print(p) # Print the point instance, which uses the __repr__ method

# functools.lru_cache for Memoization - Caches function results to speed up expensive or recursive calls
from functools import lru_cache
@lru_cache(maxsize=128)
def fib(n): # Fibonacci function with memoization
    return n if n < 2 else fib(n-1) + fib(n-2) # Return Fibonacci number for n
print(fib(30)) # fast computation of Fibonacci number at position 30

# namedtuple for Lightweight Records - Creates an immutable tuple subclass with named fields for clearer code (a tuple is like a const list)
from collections import namedtuple
Person = namedtuple("Person", ["name", "age"]) # Define a named tuple for Person with name and age
alice = Person(name="Alice", age=30) # Create a Person instance
print(alice.name, alice.age) # Print the Person instance, which shows its fields

# contextvars for Context-Local Storage - Provides variables local to async or threaded context flows
import contextvars
var = contextvars.ContextVar("var", default= 0) # Create a context variable
var.set(42) # Set the context variable to 42
print(var.get()) # Print the value of the context variable, which is 42

# secrets module for Security - Use secrets for generating secure tokens, passwords, and nonces (not that kind of nonce, it means a number used once)
import secrets
token = secrets.token_hex(16) # Generate a secure random token
print(token) # Print the secure token, which is a random hexadecimal string