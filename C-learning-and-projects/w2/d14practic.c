#include <stdio.h>
#include <stdlib.h>

int factorial(int n) { // a recursive function to calculate factorial
    if (n <= 1) {
        return 1; // Base case: factorial of 0 or 1 is 1
    }
    return n * factorial(n - 1);
}
// a recursive function is one that calls itself, you need a base case to stop the recursion

// each recursive call pushes a new frame onto the call stack. Deep or infinite recursion can exhaust the stack space, leading to a stack overflow error, causing the program to crash.

int tail_fact(int m, int acc){ // a tail recursive function to calculate factorial
    if (m <= 1) return acc; // Base case: when m is 1 or less, return the accumulated value
    return tail_fact(m - 1, m * acc); // Recursive call with updated parameters
}
// this is a special form of recursion where the recursive call is the last operation in the function.
// some compilers can optimize tail recursion into a loop, saving stack space and preventing stack overflow errors.

// many recursive algorithms can be rewritten as iterative algorithms using loops, which can be more efficient in terms of memory usage and performance.
// recursive algorithms can be elegant and easier to understand for problems that have a natural recursive structure, such as tree traversals or combinatorial problems.

// algorithms like quicksort and binary search use recursion to divide the problem into smaller subproblems, making them easier to solve.

int binary_search(int arr[], int low, int high, int target){
    if (low > high) return -1; // Base case: target not found
    int mid = (low + high) / 2; // Calculate the middle index
    if (arr[mid] == target) return mid; // If the middle element is the target, return its index
    if (arr[mid] > target) 
        return binary_search(arr, low, mid - 1, target); // Search in the left half
    else 
        return binary_search(arr, mid + 1, high, target); // Search in the right half
}

int main() {
    int n = 5;
    printf("Factorial of %d is %d\n", n, factorial(n)); // Output: 120
    printf("Tail factorial of %d is %d\n", n, tail_fact(n, 1)); // Output: 120

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 5;
    int result = binary_search(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1, target);
    if (result != -1) {
        printf("Element found at index: %d\n", result); // Output: Element found at index: 4
    } else {
        printf("Element not found\n");
    }

    return 0;
}