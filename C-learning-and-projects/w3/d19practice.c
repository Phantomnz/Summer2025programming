#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void greet(){ printf("Hi \n");}
void (*fptr)() = greet;
// C allows storing and calling funcions using pointers

void run(void (*fptr)()) {
    fptr(); // Call the function using the function pointer
}
// Functions can receive and pass function pointers as arguments

int add(int a, int b) {
    return a + b;
}
int (*opr)(int, int) = add;
// C allows storing and calling functions with arguments using pointers
// the arguments must match the function signature, int and int in this case

void (*handlers[3])();

typedef int (*MathOp)(int, int);
MathOp op = add;
// C allows storing and calling functions with arguments using typedefs
// Makes signatures clearer

int main() {
    // Call the function using the function pointer
    fptr();
    
    // Call the function using the run function
    run(fptr);
    
    // Call the add function using the op pointer
    int result = op(2, 3);
    printf("Result of add: %d\n", result);
    
    // Store and call functions in an array
    handlers[0] = greet;
    handlers[1] = greet;
    handlers[2] = greet;
    
    for (int i = 0; i < 3; i++) {
        handlers[i]();
    }
    
    return 0;
}