#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

int main(){
    auto fut = std::async([]{ return 42;}); // Example of using std::async to run a task asynchronously
    int result = fut.get();// Get the result of the asynchronous task
    // std::async returns a std::future object that can be used to retrieve the result of the asynchronous operation.

    std::thread t([]{ std::cout << "Hello from thread" << std::endl; }); // Create a thread that runs a lambda function
    t.join(); // Wait for the thread to finish

    std::mutex mtx; // Create a mutex for thread synchronization
    mtx.lock(); // Lock the mutex
    // Critical section of code that needs to be synchronized
    mtx.unlock(); // Unlock the mutex

    {
        std::lock_guard<std::mutex> lock(mtx); // Automatically locks the mutex and unlocks it when going out of scope
        // a safer alternative to manually locking and unlocking a mutex
    }

    std::atomic<int> count(0); // Example of using std::atomic for thread-safe operations
    count++; // Increment the atomic counter

    std::cout << "Result from async: " << result << std::endl; // Output the result from the async task
    std::cout << "Count: " << count.load() << std::endl; // Output the atomic counter value

    // Example of using a vector and algorithms
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::for_each(vec.begin(), vec.end(), [](int &n){ n *= 2; }); // Double each element in the vector
    for (const auto &n : vec) {
        std::cout << n << " "; // Output the modified vector
    }
    std::cout << std::endl;

    return 0; // Return success
}