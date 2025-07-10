// File: example_project.cpp
// Description:
//   A single-file example demonstrating various C++ features and type traits, including:
//   - template utilities with SFINAE and std::enable_if / std::is_integral
//   - noexcept functions
//   - template struct with specialization
//   - operator[] overloading in a custom class, plus operator< and operator== to support sorting/comparisons
//   - STL containers and algorithms (std::vector, std::for_each, std::sort)
//   - std::thread and std::async usage with std::atomic to demonstrate concurrency
//   - Preserved comments from the original snippet, plus added context to show how these pieces fit together.
//
// To compile (on Unix-like system with g++):
//   g++ -std=c++17 -pthread -Wall -Wextra -o example_project example_project.cpp
// Then run:
//   ./example_project

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>
#include <numeric>   // for std::accumulate
#include <random>    // for example data generation
#include <chrono>    // for timing demonstration (optional)

// =====================
// Template utility: isOdd for integral types only
// =====================
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type isOdd(T i) { // Function to check if a number is odd, using modulus operator
    return bool(i % 2); // Returns true if the number is odd
}
// SFINAE is used to enable this function only for integral types, preventing compilation errors for non-integral types

// =====================
// A noexcept function example
// =====================
void func() noexcept {
    std::cout << "This function is noexcept, meaning it does not throw exceptions." << std::endl;
}
// Improves optimization and helps with std::move_if_noexcept, etc.

// =====================
// Template struct printer with specialization
// =====================
template <typename T>
struct printer {
    void operator()(const T& value) const {
        std::cout << "Value: " << value << std::endl; // Prints the value of the passed argument
    }
};

template <>
struct printer<int> { // custom behavior for int type
    void print() { std::cout << "integer!\n"; } // Specialization for int type, prints a specific message
};

// =====================
// Class MyClass demonstrating operator[] and comparison operators
// =====================
class MyClass {
public:
    // Constructor: take a vector<int> to manage internally
    MyClass(const std::vector<int>& data)
        : data_(data)
    {
        // nothing else
    }

    // Overloaded operator[] to access elements by index, returns a reference to the element at the specified index
    // Note: no bounds checking here for brevity; in production consider at() or explicit checks.
    int& operator[](std::size_t index) {
        return data_[index];
    }
    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    // Provide size() to know the number of elements
    std::size_t size() const {
        return data_.size();
    }

    // Prior to <=>, overload operator<, operator==, etc. to support sorting and comparisons in custom classes
    // Here, we define: MyClass objects compare by the sum of their elements.
    bool operator<(const MyClass& other) const {
        int sum1 = std::accumulate(data_.begin(), data_.end(), 0);
        int sum2 = std::accumulate(other.data_.begin(), other.data_.end(), 0);
        return sum1 < sum2;
    }
    bool operator==(const MyClass& other) const {
        return data_ == other.data_;
    }
    // You could also overload !=, >, <=, >= or in C++20 use operator<=>.

    // For printing/debugging, let's add a method to get a string representation
    std::string toString() const {
        std::string s = "{ ";
        for (std::size_t i = 0; i < data_.size(); ++i) {
            s += std::to_string(data_[i]);
            if (i + 1 < data_.size()) s += ", ";
        }
        s += " }";
        return s;
    }

private:
    std::vector<int> data_;
};

// =====================
// Helper: count odd elements in MyClass (used in threaded example)
// =====================
void countOddsInMyClass(const MyClass& mc, std::atomic<int>& counter) {
    for (std::size_t i = 0; i < mc.size(); ++i) {
        int v = mc[i];
        if (isOdd(v)) {
            ++counter;
        }
    }
}

// =====================
// main(): orchestrates demonstration
// =====================
int main() {
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

    // Demonstrate MyClass and operator[]
    // Create a MyClass instance with some data
    std::vector<int> initialData1 = {3, 7, 2, 9, 4};
    MyClass mc1(initialData1);

    std::cout << "mc1 contents: " << mc1.toString() << std::endl;

    // Modify an element via operator[]
    mc1[2] = 20; // change third element from 2 to 20
    std::cout << "After modification, mc1 contents: " << mc1.toString() << std::endl;

    // Create another MyClass instance
    std::vector<int> initialData2 = {1, 1, 1};
    MyClass mc2(initialData2);
    std::cout << "mc2 contents: " << mc2.toString() << std::endl;

    // Compare mc1 and mc2 using operator<
    if (mc2 < mc1) {
        std::cout << "mc2 has smaller sum than mc1" << std::endl;
    } else {
        std::cout << "mc2 does not have smaller sum than mc1" << std::endl;
    }

    // Check equality operator==
    MyClass mc1_copy = mc1;
    if (mc1 == mc1_copy) {
        std::cout << "mc1 equals its copy mc1_copy" << std::endl;
    }

    // Demonstrate sorting a vector of MyClass instances
    std::vector<MyClass> vecOfMC;
    // Generate some random MyClass instances for demonstration
    std::mt19937 rng(static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 10);

    for (int i = 0; i < 5; ++i) {
        std::vector<int> data;
        int len = dist(rng) % 5 + 1; // length from 1 to 5
        for (int j = 0; j < len; ++j) {
            data.push_back(dist(rng));
        }
        vecOfMC.emplace_back(data);
    }

    std::cout << "\nBefore sorting vecOfMC by sum:\n";
    for (std::size_t i = 0; i < vecOfMC.size(); ++i) {
        std::cout << "  [" << i << "]: " << vecOfMC[i].toString()
                  << " (sum=" << std::accumulate(
                       // compute sum inline
                       std::begin(initialData1), std::end(initialData1), 0) // placeholder; will fix below
                  << ")"
                  << std::endl;
    }
    // Note: The above sum printed is placeholder; let's recompute properly below in loop:
    std::cout << "Recomputing sums properly:\n";
    for (std::size_t i = 0; i < vecOfMC.size(); ++i) {
        int sum = 0;
        for (std::size_t j = 0; j < vecOfMC[i].size(); ++j) {
            sum += vecOfMC[i][j];
        }
        std::cout << "  [" << i << "] sum=" << sum << ", contents=" << vecOfMC[i].toString() << "\n";
    }

    // Now sort using operator<
    std::sort(vecOfMC.begin(), vecOfMC.end());
    std::cout << "\nAfter sorting vecOfMC by sum ascending:\n";
    for (std::size_t i = 0; i < vecOfMC.size(); ++i) {
        int sum = 0;
        for (std::size_t j = 0; j < vecOfMC[i].size(); ++j) {
            sum += vecOfMC[i][j];
        }
        std::cout << "  [" << i << "] sum=" << sum << ", contents=" << vecOfMC[i].toString() << "\n";
    }

    // Demonstrate std::async: compute sum of elements of mc1 asynchronously
    {
        std::future<int> futSum = std::async(std::launch::async, [&mc1]() {
            int total = 0;
            for (std::size_t i = 0; i < mc1.size(); ++i) {
                total += mc1[i];
            }
            return total;
        });
        // Do other work (for demo, just print a message)
        std::cout << "\nComputing sum of mc1 asynchronously..." << std::endl;
        int sumResult = futSum.get(); // wait and get result
        std::cout << "Asynchronous sum of mc1 elements: " << sumResult << std::endl;
    }

    // Demonstrate std::thread and std::atomic: count odd values in mc1 in a separate thread
    {
        std::atomic<int> oddCount{0};
        std::thread t(countOddsInMyClass, std::cref(mc1), std::ref(oddCount));
        // Meanwhile, main thread can do something else; here we just wait.
        t.join();
        std::cout << "Number of odd elements in mc1 counted in separate thread: " << oddCount.load() << std::endl;
    }

    // Optionally, demonstrate timing a piece of code
    {
        auto start = std::chrono::steady_clock::now();
        // Some dummy workload: sum elements of all MyClass in vecOfMC
        int grandTotal = 0;
        for (const auto& mc : vecOfMC) {
            for (std::size_t i = 0; i < mc.size(); ++i) {
                grandTotal += mc[i];
            }
        }
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "\nGrand total of all elements in vecOfMC: " << grandTotal
                  << " computed in " << ms << " ms" << std::endl;
    }

    // End of demonstration
    std::cout << "\nExample complete. Returning success." << std::endl;
    return 0; // Return success code
}
