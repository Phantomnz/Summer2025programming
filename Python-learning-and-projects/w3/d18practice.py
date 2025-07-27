# Context Managers for Multiple Resources - ExitStack lets you manage an arbitrary number of context managers dynamically, ensuring each is properly closed.
from contextlib import ExitStack
with ExitStack() as stack:
    files = [stack.enter_context(open(f)) for f in ["a.txt", "b.txt"]] # Open multiple files
    for f in files:
        print(f.read())
# This ensures all files are closed properly even if an error occurs.

# pathlib.Path.glob() for recursive searches - rglob() searches recursively for files matching the pattern, returning Path objects.
from pathlib import Path
for py_file in Path('src').rglob('*.py'):  # Recursively find all Python files
    print(py_file)

# heapq for Priority Queues - heapq maintains a min-heap for efficient small-element access -- Ideal for scheduling tasks based by priority.
import heapq

heap = []
for val in [5, 1, 3]:
    heapq.heappush(heap, val)  # Push elements onto the heap
while heap:
    print(heapq.heappop(heap))  # Pop elements in sorted order

# inspect.signature() for Function Introspection - Retrieve and examine a function's parameters at runtime, useful for decorator or dynamic APIs.
import inspect  
def func(a, b=2, *args, **kwargs): pass
sig = inspect.signature(func)  # Get the signature of the function
print(sig)  # Output: (a, b=2, *args, **kwargs)

# concurrent.futures.ProcessPoolExecutor - Runs CPU-bound tasks in separate processes, sidestepping the GIL (Global Interpreter Lock) for true parallelism.
from concurrent.futures import ProcessPoolExecutor
def square(n): return n * n
with ProcessPoolExecutor() as exec:
    results = list(exec.map(square, range(10)))  # Map function to a range of numbers
print(results)  # Output: [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
