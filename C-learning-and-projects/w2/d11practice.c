#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *names[] = { "John", "Jane", "Jack", "Jill", "James" }; // Pointer array, useful for strings

void (*funcs[2])() = { NULL, NULL }; // Array can hold function pointers like this

void *ptr; // Pointer to void, can point to any data type


struct point {
    int x; 
    int y;
};

int main() {
    // Print names using pointer array
    for (int i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
        printf("%s\n", names[i]); // Accessing elements of pointer array
    }

    // Example of function pointers
    funcs[0] = NULL; // Assigning NULL to function pointer
    funcs[1] = NULL; // Assigning NULL to function pointer

    // Example of void pointer usage
    // Cast void pointer to int pointer
    ptr = malloc(sizeof(int)); // Allocating memory for an integer
    if (!ptr) return 1; // Check if memory allocation was successful
    *(int *)ptr = 42; // Assigning value to the allocated memory
    int *p = (int *)ptr; // Cast void pointer to int pointer, required when working with void pointers, or to enforce type safety
    printf("Value pointed by p: %d\n", *p); // Dereferencing the pointer to get the value

    // Example of struct usage
    struct point pt = { .x = 1, .y = 2}; // Struct variable, can be used to access struct members
    struct point *q = &pt; // Pointer to struct variable, can be used to access struct members
    q->x = 10; // Assigning value to struct member using pointer
    q->y = 20; // Assigning value to struct member using pointer
    printf("Point coordinates: (%d, %d)\n", q->x, q->y); 
    free(ptr); // Freeing memory allocated to void pointer, if it was allocated
    return 0;
}