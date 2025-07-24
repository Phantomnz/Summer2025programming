# Chaining Comparisons - You can chain relational operators in Python for concise range checks; it's equivalent to (5 < x) and (x < 20).
x = 10
if 5 < x < 20:
    print("x is between 5 and 20")

# str.join() to Concatenate - join() concatenates an iterable of strings using the string it's called on as the separator, avoiding inefficient repeated + operations.
words = ["Hello", "world", "!"] 
sentence = " ".join(words)
print(sentence)  # Output: Hello world !

# Bytes and encoding - Convert between text (str) and binary data (bytes) using encode()/decode(), specifying the character encoding (e.g., UTF-8).
text = "cafe"
b = text.encode("utf-8")  # Convert str to bytes
print(b)  # Output: b'cafe'
print(b.decode("utf-8"))  # Convert bytes back to str

# random.sample() for unique sampling - Selects k unique elements from the population without replacement
import random
population = list(range(10)) # population = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
picks = random.sample(population, k =3) # Picks 3 unique elements
print(picks)  # Output: e.g., [2, 5, 7] (randomly selected unique elements)

# zip with Unequal lengths via itertools.zip_longest - Unlike zip(), which stops at the shortest iterable, zip_longest() continues to the longest iterable, filling missing values with a specified fill value.
from itertools import zip_longest
a = [1,2]
b = ["x","y","z"]
for x, y in zip_longest(a, b, fillvalue=None):
    print(x,y) # Output: (1, 'x'), (2, 'y'), (None, 'z')

