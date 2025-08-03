# Metaclass __prepare__ for Ordered Attributes - __prepare__ returns the mapping used for the class namespace, letting you capture attribute definiton order.
class OrderedMeta(type):
    @classmethod # This method is called to prepare the class namespace
    def __prepare__(metacls, name, bases): # Prepare the class namespace
        from collections import OrderedDict
        return OrderedDict()
    def __new__(cls, name, bases, classdict):
        # Create the class using the ordered classdict
        result = type.__new__(cls, name, bases, dict(classdict)) # Convert OrderedDict to a regular dict
        result._order = list(classdict.keys()) # Store the order of attributes
        return result

class MyClass(metaclass=OrderedMeta):
    a = 1
    b = 2
    c = 3
print(MyClass._order)  # Output: ['a', 'b', 'c']

# Custom descriptor for attribute access - Descriptors (__get__/__set__) let you control attribute access and enforce rules like non-negative values.
class Positive:
    def __init__(self, name): # Initialize the descriptor with a name
        self.name = name # Store the name of the attribute
    def __get__(self, obj, objtype=None): # Get the value of the attribute
        return obj.__dict__[self.name] # Access the attribute from the instance's dictionary
    def __set__(self, obj, value): # Set the value of the attribute
        if value < 0: # Check if the value is negative
            raise ValueError("Value must be non-negative")
        obj.__dict__[self.name] = value

class Account:
    balance = Positive('balance')  # Use the Positive descriptor for balance
    def __init__(self, balance):
        self.balance = balance  # Set the initial balance using the descriptor

acct = Account(100)  # Create an account with a positive balance
print(acct.balance)  # Output: 100
# acct.balance = -50  # Attempt to set a negative balance raises ValueError

# Context Managers with @contextmanager and exception handling - Handles setup, yield, exception, and cleanup in one decorated function -- ideal for resource management with error reporting.
from contextlib import contextmanager
@contextmanager
def open_file(path):
    f = open(path)  # Open the file
    try:
        yield f  # Yield the file object for use
    except Exception as e:  # Handle exceptions
        print(f"Error: {e}")
        raise  # Re-raise the exception
    finally:
        f.close()  # Ensure the file is closed

with open_file('example.txt') as f:  # Use the context manager to open a file
    data = f.read()  # Read data from the file
    print(data)  # Print the data read from the file

# Custom Iterable with __getitem__ - Implementing __getitem__ (without __len__) makes an object iterable in for-loops until an exception (IndexError) stops iteration.
class Squares:
    def __getitem__(self, index): # Get the square of the index
        if index < 0:
            raise IndexError("Index must be non-negative")
        return index * index

sq = Squares()  # Create an instance of Squares
print(sq[5])  # Output: 25 (5 squared)
# print(sq[-1])   # Uncommenting this will raise IndexError after the last valid

# High-performance JSON parsing with orjson - orjson is a fast C-backed JSON library-- install via pip install orjson, it returns bytes on dumps and parses back to python types quickly.
import orjson
data = {"x": list(range(1000))} # Example data to serialize
j = orjson.dumps(data) # Serialize to JSON bytes
obj = orjson.loads(j) # Deserialize back to Python object
print(type(j), type(obj))  # Output: <class 'bytes'> <class 'dict'>