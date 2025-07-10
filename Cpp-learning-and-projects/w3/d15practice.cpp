#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <concepts>
#include <cmath>
#include <stdexcept>
using namespace std;

// RUN THIS CODE IN MSYS2 UCRT64 FOR C++23 SUPPORT
// This code demonstrates various C++23 features including concepts, constexpr, and type traits
// template<typename T>
// is_integral<T>::value checks if T is an integral type
// remove_const<T>::type removes const from T
// Utilities in type_traits let you query or modify types at compile time

constexpr int square(int x) {
    return x * x;
} // constexpr allowing compile-time evaluation for functions and variables

template<integral T> // Concepts let you constrain template parameters with readable requirements
T gcd(T a, T b){
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type // enable_if allows you to conditionally enable a function based on type traits
mysqrt(T x) { // Renamed to avoid conflict with std::sqrt
    static_assert(is_floating_point<T>::value, "T must be a floating-point type");
    if (x < 0) {
        throw invalid_argument("Cannot compute square root of negative number");
    }
    return static_cast<T>(std::sqrt(x)); // Using std::sqrt for floating-point types
}
// before concepts, you would use SFINAE and enable_if to selectively enable template overloads

consteval int five() { 
    return 5; // consteval ensures this function is evaluated at compile time
}
constexpr int arr_size = five();
int arr[arr_size] = {}; // Using consteval to define an array size at compile time and initializing the array

int main(){
    cout << "Square of 5: " << square(5) << endl; // Using constexpr function
    cout << "GCD of 48 and 18: " << gcd(48, 18) << endl; // Using template function with concepts
    cout << "Square root of 25.0: " << mysqrt(25.0) << endl; // Using enable_if for floating-point types
    cout << "Array size defined at compile time: " << sizeof(arr) / sizeof(arr[0]) << endl; // Using consteval for array size

    return 0;
}