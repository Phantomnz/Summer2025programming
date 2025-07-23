# super in Multiple inheritance - In a subclass, super() calls the parent's method, even with complex inheritance chains, ensuring each greet runs in the proper order
class A:
    def greet(self): # A's greet method
        print("Hello from A")

class B(A):
    def greet(self): # B's greet method
        super().greet()  # Calls A's greet
        print("and Hello from B")

b = B()
b.greet()  # This will call A's greet first, then B's greet

# operator module for functionified operators - The operator module provides functions like operator.add, operator.neg, etc., which you can pass to higher-order functions instead of using lambda functions
import operator
data = [1, 2, 3, 4, 5]
sorted_data = sorted(data, key=operator.neg)  # Sorts data in descending order
print(sorted_data)  # Output: [5, 4, 3, 2, 1]

# os.scandir() for efficient directory listing - scandir() yields DirEntry objects with extra metadata (is_file, stat) without extra system calls, much faster than os.listdir()
import os
with os.scandir('.') as it: # Open current directory
    for entry in it: # Iterate through entries
        print(entry.name, entry.is_file()) # Print entry name and if it's a file

# Thread Pool with concurrent.futures - ThreadPoolExecutor lets you run I/O-bound tasks in parallel threads with a simple map interface
from concurrent.futures import ThreadPoolExecutor
def fetch(url):
    import requests
    return requests.get(url).status_code
urls = ['http://example.com'] * 5  # Example URLs
with ThreadPoolExecutor(max_workers=3) as pool:
    results = pool.map(fetch, urls)  # Fetch URLs in parallel
print(list(results))  # Print status codes of fetched URLs

# asyncio.create_task() for Fire and Forget - create_task schedules a coroutine to run in the background without awaiting it immediately, allowing concurrent operations
import asyncio

async def background_work(): # Simulate some background work
    await asyncio.sleep(1) # Simulate a delay
    print("Background work done")

async def main():
    asyncio.create_task(background_work())  # Schedule background work
    print("Main function continues running")
    await asyncio.sleep(2)  # Wait to ensure background work completes

asyncio.run(main())  # Run the main coroutine


