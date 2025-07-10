#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> // Function template, lets us use any data type, and let you write generic functions and classes
T mymax(T a, T b){ // Function to find maximum of two values
    return (a > b) ? a : b;
}


template <typename T>
class Box {
    T value; // Class template member variable
public:
    Box(T v) : value(v) {} // Constructor to initialize value
    T getValue() const { return value; } // Method to get the value
};
// Function to demonstrate the use of the template class
// you can define whole classes generically

template <> // template customization for specific types of data
class Box<bool>{
    bool value; // Specialized class for bool type
public:
    Box(bool v) : value(v) {} // Constructor to initialize value
    bool getValue() const { return value;} // Method to get the value
};

// template can accept values as well as types
template <int N> // Template specialization for a specific integer value
class Array {
    int arr[N]; // Array of size N
};

//variadic templates allow you to pass a variable number of arguments to a function or class
template <typename... Args> //Templates can accept any number of arguments
void printall(Args... args){
    (cout << ... << args) << '\n' << endl; // Fold expression to print all arguments
}

int main() {
    cout << "Max of 10 and 20 is: " << mymax(10, 20) << endl; // Using function template with integers
    cout << "Max of 10.5 and 20.5 is: " << mymax(10.5, 20.5) << endl; // Using function template with doubles

    Box<int> intBox(100); // Using class template with int
    cout << "Value in intBox: " << intBox.getValue() << endl;

    Box<string> strBox("Hello"); // Using class template with string
    cout << "Value in strBox: " << strBox.getValue() << endl;

    Box<bool> boolBox(true); // Using specialized class for bool
    cout << "Value in boolBox: " << boolBox.getValue() << endl;

    Array<5> arr; // Using template class with a specific size
    printall("Hello", 42, 3.14); // Using variadic template to print multiple types

    return 0;
}
