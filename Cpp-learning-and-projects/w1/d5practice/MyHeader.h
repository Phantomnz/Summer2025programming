#include <iostream>
#ifndef MY_HEADER_H //this checks if MY_HEADER_H is not defined
// header guards are used to prevent multiple inclusions of the same header file
// This is a common practice in C++ to avoid redefinition errors and to improve compilation time.
// it requires the header file to be included only once in a single compilation/translation (cpp file) unit.
#define MY_HEADER_H //if not defined, it defines MY_HEADER_H

//#pragma once // This is a preprocessor directive that ensures the header file is included only once in a single compilation.

int fillervariable = 0;


#endif //MY_HEADER_H //this ends the if statement that checks if MY_HEADER_H is not defined