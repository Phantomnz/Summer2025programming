#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// template instantiation - when you use a template with specific types, the compiler generates code/a concrete version for those types.
// This can increase code size but allows for type safety and flexibility and allows high performance.
int x = 10;
void print(int x){ // this is a regular function, not a template
    cout << "Value: " << x << endl;
}
template <typename T> void print(T x){ // templates can coexist with regular overloaded functions. The compiler will choose the most specific match.
    cout << "Value: " << x << endl;
}

template <int N> // template specialization
struct Factorial { // This is a template struct that calculates the factorial of N at compile time.
    static constexpr int value = N * Factorial<N - 1>::value; // Recursive definition
    // The value is computed at compile time using recursion
};
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};


// Templates are often defined in header files to allow for code reuse across multiple translation units. 
// Inline functions are often used with templates to avoid multiple definitions across translation units to avoid linker errors.

template <typename T> class Container {
private:
    vector<T> data; // Using std::vector to store elements of type T
};

template <class T> class holder {
private:
    T value; // This class holds a value of type T
};

// when declaring templates, you can use either `typename` or `class` interchangeably for type parameters as they are equivalent.

int main() {
    // Using the print function
    print(42); // Calls the regular function
    print(3.14); // Calls the template function

    // Using the Factorial template
    cout << "Factorial of 5: " << Factorial<5>::value << endl; // Outputs 120

    // Example of using the Container template
    Container<int> intContainer; // This creates a container for integers
    Container<double> doubleContainer; // This creates a container for doubles

    // Example of using the holder template
    holder<string> stringHolder; // This holds a string value

    return 0;
}
