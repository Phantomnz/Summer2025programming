# Formatted String Literals (f-strings) with expressions - Prefix with f; embed expressions in {}; use format specifiers for (e.g. .2f) for precision
a, b = 5, 3
print(f"{a} x {b} = {a * b}") # Output: "5 x 3 = 15"
print(f"{3.1459:.2f}") # Output: "3.15"

# Pathlib: Writing Text to a File - Path.write_text() creates or overwrites a file with the given string, automatically handling open/close
from pathlib import Path
p = Path("notes.txt")
p.write_text("This is a note.") # Writes text to the file, creating it if it doesn't exist

# Secure Random with secrets - The secrets module provides cryptographicallt secure random numbers suitable for managing data such as passwords, account authentication, and security tokens
import secrets
token = secrets.token_hex(16) # Generates a secure random token in hexadecimal format
print(f"Secure token: {token}") # Output

# Decimal Arithmetic - Decimal avoids binary floating-point errors; set prec to control significant digits.
from decimal import Decimal, getcontext
getcontext().prec = 4 # Set precision to 4 significant digits
x = Decimal("1.10") + Decimal("2.20001") # Decimal addition
print(f"Decimal result: {x}") # Output: "Decimal result: 3.30"

# Sorting with sorted() and key - key extracts a comparison value for each item; sorted() returns a new sorted list
users = [{"name": "Alice", "age": 30}, {"name": "Bob", "age": 25}]
sorted_by_age = sorted(users, key=lambda u: u["age"]) # Sort by age
print(sorted_by_age) # Output: [{'name': 'Bob', 'age': 25}, {'name': 'Alice', 'age': 30}]
