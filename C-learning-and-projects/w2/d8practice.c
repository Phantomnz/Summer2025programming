#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Point { // Define a structure named Point
    int x;
    int y;
}Point; // Use typedef to create an alias for struct Point
// This allows us to use Point instead of struct Point in the code.
// The typedef is useful for simplifying the syntax when declaring variables of this type.

struct Point p = {10, 20}; // Initialize a Point instance
void printPoint(Point p){
    printf("Point: (%d, %d)\n", p.x, p.y); // Function to print the coordinates of a Point
}

void movePoint(Point *p, int dx, int dy){ // Function to move a Point by dx and dy
    p->x += dx;
    p->y += dy;
}


struct flag { // Define a structure named flag
    unsigned int a : 1; // Define a bit-field with 1 bit
    unsigned int b : 1; // Define another bit-field with 1 bit
}; //bit-fields are used to save memory


union Data { // Define a union named Data
    int i; // Integer member
    float f; // Float member
    char str[20]; // String member
};

int main(){ 
    struct Point p1 = {5, 10}; // Create a Point instance
    printPoint(p1); // Print the initial coordinates of p1

    movePoint(&p1, 3, 4); // Move p1 by (3, 4)
    printPoint(p1); // Print the new coordinates of p1

    struct flag f = {1, 0}; // Initialize a flag instance
    printf("Flag: a=%u, b=%u\n", f.a, f.b); // Print the values of the flag

    union Data data; // Create a union instance
    data.i = 10; // Assign an integer value
    printf("Data as int: %d\n", data.i); // Print the integer value

    data.f = 220.5; // Assign a float value
    printf("Data as float: %f\n", data.f); // Print the float value

    strcpy(data.str, "Hello"); // Assign a string value
    printf("Data as string: %s\n", data.str); // Print the string value

    return 0; // Return success




}