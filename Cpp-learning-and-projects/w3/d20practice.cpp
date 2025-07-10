#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

// a shared_ptr allows multiple pointers to manage the same object. Once all shared_ptr owners are destroyed or reset, the object is deleted automatically.

constexpr int square(int x) {
    return x * x;
} // constexpr function can be evaluated during compilation if given constant arguments.



template <typename T>
void wrapper(T&& arg){
    std::cout << "Real function called with: " << std::forward<T>(arg) << "\n";
}
// Perfect Forwarding with std::forward allows us to pass arguments to a function while preserving their value category (lvalue or rvalue). This is useful for template functions that can accept both lvalues and rvalues.

int main(){
    int a = 10;
    auto byvalue = [=]() {return a;}; // by value Lambda capture
    auto byreference = [&]() {return a;}; // by reference Lambda capture
    // Lambda expressions can capture outside variables by value or by reference.
    std::cout << "By value: " << byvalue() << "\n";
    std::cout << "By reference: " << byreference() << "\n";
    std::cout << "Square of 5: " << square(5) << "\n"; // constexpr function usage
    std::unique_ptr<FILE, decltype(&fclose)> fileptr(fopen("file.txt", "r"), &fclose);
    // unique_ptr can accept custom deleters for resources other than new
    std::cout << "File pointer: " << (fileptr ? "Opened" : "Failed to open") << "\n"; // unique_ptr with custom deleter
    wrapper(42); // forwarding reference example
    std::cout << "Wrapper called with 42\n";

}