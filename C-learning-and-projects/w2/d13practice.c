#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greet() { printf("Hello, World!\n"); } // Function to print greeting
void (*funcptr)() = greet; // Function pointer to greet

void add(int a, int b){int c = a + b;}// Function to add two integers
void (*func)(int a, int b) = add; // Function pointer to add


void operate(int a, int b, void (*func)(int, int)) { // passing a function pointer as a parameter
    printf("printing addition of a and b: %d\n", a + b);
}

//Functions can return function pointers, used in callback systems

void (*ops[1])() = {greet}; // Array of function pointers to functions with signature void(void)

int main() {
    greet(); // Call the greeting function
    operate(5, 10, add); // Call operate with function pointer of correct signature
    return 0;
}