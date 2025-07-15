# Dictionary Comprehension - Builds a dict in one expression, mapping each number to its square
nums = [1,2,3,4,5]
squared_dict = {n: n*n for n in nums}
print(squared_dict)  # Output: {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

# Unpacking with * and ** - * unpacks a list/tuple into positional arguments; ** unpacks a dict into keyword arguments
def func(a, b, c) : print(a, b, c)
args = [1, 2, 3]
func(*args)  # Output: 1 2 3 - positional unpacking
kwargs = {'a': 10, 'b': 20, 'c': 30}
func(**kwargs)  # Output: 10 20 30 - keyword unpacking

# Lambda Functions - Anonymous, inline functions for simple operations -- often used with map(), filter(), or reduce()
add = lambda x, y: x + y
print(add(5, 3))  # Output: 8

# Using map() and filter() - filter() selects elements based on a test, map() applies a function to (transforms) each element
numbers = [1, 2, 3, 4, 5]
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))  # Output: [2, 4]
doubled_numbers = list(map(lambda x: x * 2, numbers))  # Output: [2, 4, 6, 8, 10]
print(even_numbers, doubled_numbers)

# Context Managers - Using 'with' to ensure resources are properly managed (like file handling)
with open("data.txt") as file:
    content = file.read()
# file is automatically closed after the block, even if an error occurs

