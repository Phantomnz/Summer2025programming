#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Memory Segments in C:
A C program uses several memory segments: code (text), static/global, stack, and heap. Stack is used for function calls; heap for dynamic memory like malloc and calloc*/

/*Static vs. Dynamic Allocation:

    Static: memory allocated at compile time (e.g., global arrays).

    Dynamic: memory allocated during runtime using malloc, calloc, etc.*/

//Segmentation Faults:
//Occur when your program accesses memory it shouldn't—like dereferencing NULL or writing out of array bounds


int arr[3] = {1, 2, 3}; // Static allocation of an array of 3 integers
int (*q)[3] = &arr; // Pointer to an array of 3 integers
// q points to the entire array, not just the first element

int main(){
    int *p = malloc(sizeof(int)); // Dynamic allocation of an array of 1 integer
    free(p); // Freeing the dynamically allocated memory
    // doing *p = 10; is dangerous as it dereferences a freed pointer, leading to undefined behavior.
    printf("q[0][0] = %d\n", (*q)[0]); // Accessing the first element of the array pointed to by q
    printf("q[0][1] = %d\n", (*q)[1]); // Accessing the second element of the array pointed to by q
    printf("q[0][2] = %d\n", (*q)[2]); // Accessing the third element of the array pointed to by q
}