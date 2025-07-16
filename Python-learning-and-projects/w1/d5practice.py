# Tuples and immutability - Tuples are ordered, immutable sequences. You can unpack them into variables but cannot change their contents.
coords = (10, 20)
# coords[0] = 15  # This will raise a TypeError because tuples are immutable
x, y = coords # unpacking
print(x, y)  # Output: 10 20

# Sets and uniqueness - A set stores unique values. Converting a list to a set removes duplicates.
fruits = ['apple', 'banana', 'apple', 'orange']
unique = set(fruits)
print(unique)  # Output: {'banana', 'orange', 'apple'}

# zip() to combine sequences - zip() pairs elements from multiple sequences until one is exhausted.
names = ['Alice', 'Bob', 'Charlie']
ages = [25, 30, 35]
for name, age in zip(names, ages):
    print(f"{name} is {age} years old")

# Dictionary get() with Default - get() returns the value for a key or a default if the key is missing, avoiding KeyError.
d = {"a": 1}
print(d.get("b", "Not Found"))  # Output: Not Found
print(d.get("a", "Not Found"))  # Output: 1

# enumerate() with a start index - You can specify the starting index for enumeration, useful for human-friendly numbering.
items = ['apple', 'banana', 'cherry']
for index, item in enumerate(items, start=1):
    print(index, item)  # Output: 1 apple, 2 banana, 3 cherry