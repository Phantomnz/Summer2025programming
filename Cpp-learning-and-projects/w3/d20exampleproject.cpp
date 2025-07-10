// File: example_single.cpp
// Description:
//   A single-file example demonstrating various C++ features, including:
//   - constexpr functions
//   - Lambda captures by value and by reference
//   - std::unique_ptr with custom deleter
//   - std::shared_ptr usage in a threaded/async context
//   - Perfect forwarding with std::forward
//   - std::async and std::thread with shared_ptr
//   - std::mutex and std::atomic for thread-safe operations
//   - STL containers and algorithms
//
// To compile (on Unix-like system with g++):
//   g++ -std=c++17 -pthread -Wall -Wextra -o example_single example_single.cpp
// Then run:
//   ./example_single

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>
#include <memory>    // for shared_ptr, unique_ptr
#include <cstdio>    // for FILE, fopen, fclose
#include <chrono>    // for timing

// a shared_ptr allows multiple pointers to manage the same object. Once all shared_ptr owners are destroyed or reset, the object is deleted automatically.

constexpr int square(int x) {
    return x * x;
} // constexpr function can be evaluated during compilation if given constant arguments.

template <typename T>
void wrapper(T&& arg) {
    std::cout << "Real function called with: " << std::forward<T>(arg) << "\n";
}
// Perfect Forwarding with std::forward allows us to pass arguments to a function while preserving their value category (lvalue or rvalue). This is useful for template functions that can accept both lvalues and rvalues.


// Helper for threaded demo: compute sum of a vector<int> and return it
int computeSum(const std::vector<int>& v) {
    int total = 0;
    for (int x : v) {
        total += x;
    }
    return total;
}

// Thread-safe print utility
void threadSafePrint(const std::string& msg) {
    static std::mutex printMutex;
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << msg << std::endl;
}

int main() {
    // Example usage of Lambda captures and constexpr
    int a = 10;
    auto byvalue = [=]() { return a; }; // by value Lambda capture
    auto byreference = [&]() { return a; }; // by reference Lambda capture
    // Lambda expressions can capture outside variables by value or by reference.
    std::cout << "By value: " << byvalue() << "\n";
    std::cout << "By reference: " << byreference() << "\n";
    std::cout << "Square of 5: " << square(5) << "\n"; // constexpr function usage

    // Example of unique_ptr with custom deleter for FILE*
    std::unique_ptr<FILE, decltype(&fclose)> fileptr(fopen("file.txt", "r"), &fclose);
    std::cout << "File pointer: " << (fileptr ? "Opened" : "Failed to open") << "\n"; // unique_ptr with custom deleter

    wrapper(42); // forwarding reference example
    std::cout << "Wrapper called with 42\n";

    // =====================================================================
    // Demonstrate shared_ptr usage in a threaded/async context
    // =====================================================================

    // Create a shared_ptr to a vector<int>
    auto sharedVec = std::make_shared<std::vector<int>>();
    // Fill the vector with some data
    for (int i = 1; i <= 20; ++i) {
        sharedVec->push_back(i);
    }
    std::cout << "\n[Main] sharedVec contents:";
    for (int x : *sharedVec) {
        std::cout << " " << x;
    }
    std::cout << "\n";

    // We'll launch multiple async tasks to compute partial sums.
    // Split the vector into chunks based on hardware concurrency.
    unsigned int concurrency = std::thread::hardware_concurrency();
    if (concurrency == 0) concurrency = 2;
    std::cout << "[Main] Launching " << concurrency << " async tasks to compute partial sums.\n";

    size_t totalSize = sharedVec->size();
    size_t chunkSize = totalSize / concurrency;
    size_t remainder = totalSize % concurrency;

    std::vector<std::future<int>> futures;
    futures.reserve(concurrency);
    size_t start = 0;
    for (unsigned int i = 0; i < concurrency; ++i) {
        size_t end = start + chunkSize + (i < remainder ? 1 : 0);
        if (start >= end) break;
        // Capture sharedPtr by value so each async keeps it alive
        futures.emplace_back(std::async(std::launch::async,
            [sharedVec, start, end]() -> int {
                // Compute sum of elements in [start, end)
                int subtotal = 0;
                for (size_t idx = start; idx < end; ++idx) {
                    subtotal += (*sharedVec)[idx];
                }
                threadSafePrint("[Async task] Processed indices [" + std::to_string(start) + ", " + std::to_string(end) + "), subtotal = " + std::to_string(subtotal));
                return subtotal;
            }
        ));
        start = end;
    }

    // Collect partial sums
    int grandTotal = 0;
    for (auto& fut : futures) {
        grandTotal += fut.get();
    }
    std::cout << "[Main] Grand total computed by async tasks: " << grandTotal << "\n";

    // =====================================================================
    // Demonstrate std::thread and std::atomic: count how many elements are odd
    // =====================================================================
    std::atomic<int> oddCount{0};
    auto countOdds = [sharedVec, &oddCount]() {
        for (int x : *sharedVec) {
            if (x % 2 != 0) {
                ++oddCount;
            }
        }
        threadSafePrint("[Thread] Finished counting odds. Count = " + std::to_string(oddCount.load()));
    };
    std::thread t(countOdds);
    t.join();
    std::cout << "[Main] Number of odd elements: " << oddCount.load() << "\n";

    // =====================================================================
    // Demonstrate timing a small workload
    // =====================================================================
    {
        auto startTime = std::chrono::steady_clock::now();
        // Dummy workload: compute sum again
        int sum2 = computeSum(*sharedVec);
        auto endTime = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "[Timing] Sum computed in main thread: " << sum2 << " in " << ms << " ms\n";
    }

    std::cout << "\nExample complete. Returning success.\n";
    return 0;
}
