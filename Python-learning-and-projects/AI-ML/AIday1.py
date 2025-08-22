# Arrays are Typed, n-dimensional blocks (not Python Lists) 
import numpy as np

a = np.array([1, 2, 3], dtype=np.int32) # Create a 1D array of integers with dtype int32 
print(a.dtype, a.shape, a.ndim) # Output: int32 (3,) 1

b = np.array([[1.0,2.0], [3.5, 4.5]]) #  Create a 2D array of floats (float64 by default)
print(b.dtype, b.shape, b.ndim) # Output: float64 (2, 2) 2

c = b.astype(np.float32) # Change dtype to float32, safe d type cast
print(c.dtype) # Output: float32
# Why it matters: NumPy stores homogeneous data, contiguous (meaning it can be accessed in a cache-friendly way) data -- giving huge speedups and predictable memory use compared to Python lists.

# Vectorization beats Python loops
x = np.arange(1_000_000, dtype=np.float64) # Create an array with 1 million floats
y = np.arange(1_000_000, 0, -1, dtype=np.float64) # Create another array with 1 million floats

# Elementwise operations are SIMD (Single Instruction, Multiple Data)/Vectorized in C
z = x * 0.5 + y * 2.0
dot = (x*y).sum() # same as np.dot(x, y)
print(z[:3], dot) # output: [  1.5  3.5  5.5] 666666833333.0
# Why it matters: Elementwise math and reductions run in optimized C - cleaner code and orders of magnitude faster than Python for loops

# Broadcasting: align trailing dimensions, then "stretch" size-1
M = np.array ([[1., 2., 3.], [4., 5., 6.]]) # shape (2, 3)
row = np.array([[10., 20., 30.]]) # shape (3,)
# row is broadcasted to shape (2, 3) during addition
out = M + row
print(out)
# [[11. 22. 33.]
#  [14. 25. 36.]]
# Why it matters: No loops needed. Broadcasting rules: starting from the end, dimensions must be equal or one of them be 1; size-1 dims “stretch” virtually.
# broadcasting works for arrays of different shapes and various arithmetic operations.

# Boolean Masking & where select data without loops
arr = np.array([ -3, -1, 0, 2, 5, 8 ]) # 1D array
mask = (arr > 0) # boolean array where condition is met
print(arr[mask]) # Output: [2 5 8]

# Replace negatives with 0, keep positives
clean = np.where(arr > 0, arr, 0) # like a vectorized ternary
print(clean) # Output: [0 0 0 2 5 8]
# Why it matters: Masks and where make filtering and conditional transforms fast and concise-- core to preprocessing in ML

# Reductions along axes (and keeping dimensions) 
x = np.array([[1., 2., 3.], [4., 5., 6.], [7., 8., 9.]])
col_means = x.mean(axis=0) # mean of each column  shape (3,)
row_sums = x.sum(axis=1, keepdims=True) # sum of each row, keepdims for broadcasting shape (3, 1)
std_all = x.std() # standard deviation of all elements

print(col_means) # Output: [4. 5. 6.]
print(row_sums) # Output: [[ 6.], [15.], [24.]]
print(std_all) # Output: 2.581988897471611 (population standard deviation)