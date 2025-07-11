# print function outputs text to the console, automatically adds a newline at the end
print("Hello, Python!")

# Variables and dynamic typing, Python variables aren't declared with types, the interpreter tracks each object's type at runtime
x = 5 # Integer variable
print(x) # Output: 5
x = 3.14 # Now x is a float variable
print(x) # Output: 3.14

# Lists and Indexing : lists are ordered, mutable sequences. You can access elements by zero-based index
fruits = ["apple", "banana", "cherry"]
print(fruits[0])  # Output: apple
print(fruits[1])  # Output: banana
print(fruits[2])  # Output: cherry

# for loops over sequences: iterates directly over list items. Here we call .upper() on each string to uppercase it
for fruit in fruits:
    print(fruit.upper())  # Output: APPLE, BANANA, CHERRY (each on a new line)

# defining a function: def introuduces a function. Parameters a and b are local names; return sends back the result
def add(a, b):
    return a + b  # Returns the sum of a and b

print(add(3, 4))  # Output: 7