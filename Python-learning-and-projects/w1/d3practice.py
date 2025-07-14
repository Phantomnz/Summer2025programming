# if/else/elif - Allows branching logic. Python require indentation to define blocks of code.
x = 10
if x < 5:
    print("x is less than 5")
elif x < 15:
    print("x is less than 15")
else:
    print("x is 15 or more")

# while - Repeats a block of code as long as a condition is true. 
count = 0
while count < 5:
    print("Count is:", count)
    count += 1  # Increment count to avoid infinite loop

# Default Argument values in functions - specifies a default if the caller does not provide a value.
def greet(name="Guest"):
    print(f"Hello, {name}")
greet()  # Calls with default value
greet("Alice")  # Calls with provided value

# List slicing - Extracts a portion of a list using start, stop, and step indices. generally in the form list[start:stop:step].
nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
sub = nums[2:8:2]  # Slices from index 2 to 8 with a step of 2
print("Sliced list:", sub)  # Output: [2, 4, 6]

# Exception handling - Catches and handles runtime errors. The finally block runs regardless of whether an exception occurred.
try: 
    result = 10 / 0  # This will raise a ZeroDivisionError
except ZeroDivisionError:
    print("Cannot divide by zero!")
finally:
    print("This will always execute, regardless of an error.")

