#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type // This template utility conditionally enables function overloads based on type traits
isOdd(T i){ // Function to check if a number is odd, using modulus operator
    return bool(i % 2); // Returns true if the number is odd
}
// sfinae is used to enable this function only for integral types, preventing compilation errors for non-integral types

void func() noexcept {
    std::cout << "This function is noexcept, meaning it does not throw exceptions." << std::endl;
}// Improves optimization and helps with std::move_if_noexcept

template <typename T>
struct printer {
    void operator()(const T& value) const {
        std::cout << "Value: " << value << std::endl; // Prints the value of the passed argument
    }
};

template <>
struct printer<int>{ // custom behavior for int type
    void print() { std::cout << "integer! \n"; } // Specialization for int type, prints a specific message
};

class MyClass {
public:
    int& operator[](std::size_t index); // Overloaded operator[] to access elements by index, returns a reference to the element at the specified index
};
// prior to <=>, overload operator<, operator==, etc. to support sorting and comparisons in custom classes

int main(){
    // Example usage of isOdd function
    int number = 5;
    if (isOdd(number)) {
        std::cout << number << " is odd." << std::endl;
    } else {
        std::cout << number << " is even." << std::endl;
    }

    // Example usage of func
    func();

    // Example usage of printer struct
    printer<std::string> strPrinter;
    strPrinter("Hello, Printer!");

    printer<int> intPrinter;
    intPrinter.print(); // Calls the specialized print method for int

    return 0; // Return success code
}

