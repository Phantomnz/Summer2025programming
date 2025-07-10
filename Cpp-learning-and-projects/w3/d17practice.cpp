#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int x = 5;
auto f = [x]() { return x + 1;}; // lambda function that captures x by value
// Lambdas can capture local variables by value, by reference, or explicitly

auto add = [](int a, int b) { return a + b; }; // lambda function that takes two parameters and returns their sum
// Lambda syntax enhancements - generic lambdas allow deduced parameter types

// variadic templates allow functions/classes to accept an arbitrary number of template parameters/arguments
template<typename... Args> // variadic template declaration
void printAll(Args... args){ // function template that takes a variable number of arguments
    (cout << ... << args) << '\n'; // fold expression to print all arguments (C++17 and later)
}

int z = 10;
decltype(auto) w = (z); // w is deduced to be of type int& due to the parentheses 

// namespace io = std::iostream; // namespace aliasing (not used in this example)
// you can alias a long namespace name for clarity and brevity

int main() {
    cout << "Hello, World!" << endl; // Output: Hello, World!
    
    cout << "f() = " << f() << endl; // Output: f() = 6
    cout << "add(3, 4) = " << add(3, 4) << endl; // Output: add(3, 4) = 7
    
    printAll("Hello", " ", "World", "!"); // Output: Hello World !
    
    cout << "w = " << w << endl; // Output: w = 10
    return 0;
}
