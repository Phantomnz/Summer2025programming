#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SQUARE(x) ((x) * (x))// You can define function-like macros using the `#define` directive. be careful with parentheses to avoid precedence issues.
#define LOG(fmt, ...) \
    do { \
        fprintf(stderr, fmt, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)
// Variadic macros allow you to define a macro that can take a variable number of arguments. The `__VA_ARGS__` macro is used to represent the variable arguments passed to the macro.

// Macro Pitfalls:
// Multiple evaluation: SQUARE(x) will evaluate x multiple times if used like SQUARE(a++), which can lead to unexpected results.
// NO type checking: Macros do not perform type checking, so passing an incompatible type can lead to errors that are hard to debug.
// Debugging: Macros can make debugging harder because they do not have a type or scope, and errors point to the expanded code, not the macro itself.

// Repeated fact: Prevent Multiple Inclusions of Header Files with guards
// #ifndef HEADER_FILE_NAME_H
// #define HEADER_FILE_NAME_H
// // Header file content
// #endif // HEADER_FILE_NAME_H
// or using `#pragma once` at the top of the header file to ensure it is included only once in a single compilation unit.

#define print_val(x) \
    _Generic((x), \ 
        int: printf("int: %d\n", (x)), \
        float: printf("float: %.2f\n", (x)), \
        double: printf("double: %.2f\n", (x)), \
        char*: printf("string: %s\n", (x)), \
        default: printf("unknown type\n") \
    )

int main() {
    int x = 10;
    printf("SQUARE(%d) = %d\n", x, SQUARE(x)); // SQUARE(10) = 100
    int a = 5;
    float b = 3.14f;
    double c = 2.71828;
    char* d = "Hello, World!";
    print_val(d); // string: Hello, World!
    print_val(a); // int: 5
    print_val(b); // float: 3.14
    print_val(c); // double: 2.72
    
    LOG("This is a log message with value: %d", a);
    
    return 0;
}
