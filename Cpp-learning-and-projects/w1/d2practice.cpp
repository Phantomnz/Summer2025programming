#include <iostream>
using namespace std;

int and1(int a, int b) {
    // This function ands two integers and returns the result
    return a & b;
}

void greet(string name = "User") {
    cout << "Hello, " << name << endl; //endl is used to print a new line
}


int main()
{   // This is the main function where the program starts executing
    cout << and1(0b10, 0b11) << endl; // This will print the result of the and function
    greet(); // This will call the greet function with the default name "User"
}
