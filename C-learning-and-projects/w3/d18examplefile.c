/*
 * File: macros_example.c
 * Description:
 *   A self-contained example demonstrating various C macro techniques and pitfalls.
 *   This single-file "project" showcases:
 *     - Function-like macros (e.g., SQUARE)
 *     - Variadic macros for logging (LOG)
 *     - Use of _Generic for type-based behavior (print_val)
 *     - Comments about include guards (in header files) but kept here for illustration
 *     - Pitfalls and best practices for macros
 *
 * Compile with:
 *   gcc -std=c11 -Wall -Wextra -o macros_example macros_example.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // for demonstration if needed

// =====================
// Macro Definitions
// =====================

// Example of function-like macro: squares a value.
// Be careful with parentheses to avoid precedence issues.
#define SQUARE(x) ((x) * (x))

// Variadic macro for logging to stderr with a newline.
// The do-while(0) pattern ensures it behaves like a statement.
#define LOG(fmt, ...) \
    do { \
        fprintf(stderr, fmt, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)

// Macro Pitfalls:
// - Multiple evaluation: SQUARE(x++) will increment x twice, leading to unexpected behavior.
// - No type checking: passing incompatible types may compile but misbehave at runtime.
// - Debugging difficulty: errors point to expanded code, not the macro definition.

// =====================
// Include Guard Illustration (for header files)
// =====================
// In a real header file, you might use:
// #ifndef MACROS_EXAMPLE_H
// #define MACROS_EXAMPLE_H
//   [Header file content with macro definitions, function declarations, etc.]
// #endif // MACROS_EXAMPLE_H
// or use #pragma once at the top.
// Here, we keep these comments in this single file example for teaching, but no actual guard is needed.

// =====================
// Type-based print_val Macro using C11 _Generic
// =====================
// print_val(x) will choose appropriate printf format based on type of x.
#define print_val(x) _Generic((x), \
    int: print_int, \
    float: print_float, \
    double: print_double, \
    char *: print_string, \
    const char *: print_string, \
    default: print_unknown_type \
)(x)

// Helper functions used by the print_val macro
void print_int(int v) {
    printf("int: %d\n", v);
}

void print_float(float v) {
    // Note: format %.2f prints two decimal places
    printf("float: %.2f\n", v);
}

void print_double(double v) {
    // Note: format %.2f prints two decimal places
    printf("double: %.2f\n", v);
}

void print_string(const char *s) {
    printf("string: %s\n", s);
}

void print_unknown_type(...) {
    printf("unknown type\n");
}

// =====================
// Demonstration of pitfalls with macros
// =====================

// To avoid multiple evaluation pitfalls, prefer inline functions when possible:
static inline int square_inline(int x) {
    return x * x;
}

// =====================
// Main: Demonstrates usage of macros
// =====================

int main(void) {
    // Demonstrate SQUARE macro
    int a = 5;
    printf("SQUARE(%d) = %d\n", a, SQUARE(a));  // Expected: 25

    // Pitfall demonstration:
    int i = 3;
    // Using SQUARE(i++) would evaluate i++ twice: e.g., SQUARE(i++) expands to ((i++) * (i++)),
    // leading to undefined behavior. Uncommenting below is not recommended:
    // printf("SQUARE(i++) = %d, final i = %d\n", SQUARE(i++), i);
    // Instead, use inline function to avoid multiple evaluation:
    i = 3;
    printf("square_inline(i++) = %d, final i = %d\n", square_inline(i++), i);  // Safe: i is incremented once

    // Demonstrate variadic LOG macro
    LOG("This is a log message: a = %d, i = %d", a, i);
    // If no variable arguments: careful, passing at least one argument after fmt is needed.
    // Could define another macro for no-arg logging if desired.

    // Demonstrate print_val macro with different types
    print_val(a);            // int
    float bf = 3.14f;
    print_val(bf);           // float
    double cd = 2.71828;
    print_val(cd);           // double
    const char *msg = "Hello, World!";
    print_val(msg);          // string
    // Example of unknown type: e.g., a pointer to int not matched above
    int arr[3] = {1, 2, 3};
    print_val((void*)arr);   // unknown type

    // Demonstrate LOG with formatted string containing literal percent
    const char *name = "Alice";
    int age = 30;
    LOG("User %s is %d years old", name, age);

    // Demonstrate combining macros carefully
    // For example, compute area = SQUARE(length) and log it:
    int length = 4;
    int area = SQUARE(length);
    LOG("Square of %d is %d", length, area);

    // Note: macros do not respect scopes in the same way as functions, so be cautious of side effects,
    // naming collisions, and debugging complexity.

    return 0;
}