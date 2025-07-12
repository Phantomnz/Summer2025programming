# Reading User Input with input()
name = input("Enter your name: ") # input() prompts the user for input and returns it as a string. In this case we store it in the variable 'name' 
print("Hello, " + name + "!")  # Concatenating strings to greet the user

# Type conversion
age_str = input("Enter your age: ") # Input is always a string, so we need to convert it
age = int(age_str)  # Convert the string input to an integer, allowing us to perform arithmetic operations
print(age + 5) # Print the age plus 5, showing type conversion in action

# Dictionaries (dict) - a dict maps keys to values. You access or assign entries via bracket notation
student = {"name": "Alice", "score": 95} # Creating a dictionary with keys 'name' and 'score'
print(student["name"])  # Accessing the value associated with the key 'name'
print(student["score"])  # Accessing the value associated with the key 'score'
student["score"] = 98  # Updating the value associated with the key 'score'
print(student["score"])  # Accessing the value associated with the key 'score'

# Looping with enumerate()
fruits = ["apple", "banana", "cherry"]  # A list of fruits
for index, fruit in enumerate(fruits, start=1):  # Using enumerate to get both index and value
    print("Fruit", index, "is", fruit) # Printing the index and value of each fruit in the list

# List comprehensions
numbers = [1, 2, 3, 4, 5]  # A list of numbers
squares = [n*n for n in numbers if n % 2 == 1]  # List comprehension to get squares of odd numbers
print("Squares of odd numbers:", squares)  # Printing the resulting list of squares
