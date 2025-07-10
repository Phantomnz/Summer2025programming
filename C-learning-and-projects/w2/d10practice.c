#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int x = 5; // Global variable
int *p = &x; // Pointer to an integer
int **pp = &p; // Pointer to pointer

void modify(int *p) {
    *p = 10; // Modify the value pointed to by p
}
int *arr = NULL; // Declare arr as a global pointer

void reallocation() {
    arr = realloc(arr, 10 * sizeof(int)); // Resize the array to hold 10 integers
}

int main(){
    printf("Value of x: %d\n", x);
    printf("Value pointed to by p: %d\n", *p);
    printf("Value pointed to by pp: %d\n", **pp);

    modify(p); // Call function to modify the value of x
    printf("Value of x after modification: %d\n", x);
    int *arr = calloc(5, sizeof(int)); // Allocate memory for an array of 5 integers
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    reallocation(); // Resize the array
    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1; // Initialize new elements
    }
    for (int i = 0; i < 10; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    free(arr); // Free the dynamically allocated memory
    return 0;
}
