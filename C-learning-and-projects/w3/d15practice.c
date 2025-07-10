#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

volatile int status; // volatile keyword tells the compiler not to optimize this variable, as it may change unexpectedly.
// so always read it from memory rather than from a register.

void copy(int *restrict dst, const int *restrict src, size_t n) { // restrict keyword tells the compiler that the pointers dst and src do not point to the same memory location.
    // enable optimization by using restrict pointers, restrict pointers are the optimal way to pass pointers to functions when you know they do not overlap.
    // Copy n integers from src to dst
    for (size_t i = 0; i < n; i++) {
        dst[i] = src[i];
    }
} 

static inline int max(int a, int b){ return (a > b) ? a : b; } // inline keyword tells the compiler to replace the function call with the function code, 
//which can improve performance for small functions.

// Members of a struct may be padded so each member is aligned to its natural boundary. You can inspect or control layout with offsetof and compiler-specific packing pragmas.
// The offsetof macro is defined in the stddef.h header file and returns the offset of a member within a struct.

_Atomic int counter; // _Atomic keyword indicates that the variable is an atomic type, which means it can be accessed by multiple threads without causing data races.

int main(){
    atomic_fetch_add(&counter, 1); // Increment the counter atomically (atomic_fetch_add is an atomic operation that adds a value to a variable and returns the old value.)
    printf("Counter value: %d\n", atomic_load(&counter)); // Print the current value of the counter.
    copy((int[]){1, 2, 3}, (int[]){4, 5, 6}, 3); // Copy 3 integers from one array to another using the copy function.
    printf("Copied values: %d, %d, %d\n", (int[]){1, 2, 3}[0], (int[]){1, 2, 3}[1], (int[]){1, 2, 3}[2]); // Print the copied values.
    printf("Max of 5 and 10 is: %d\n", max(5, 10)); // Call the max function to get the maximum of two integers.
}