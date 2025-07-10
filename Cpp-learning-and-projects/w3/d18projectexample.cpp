// File: multithreaded_example.cpp
// Description:
//   A single-file example demonstrating:
//   - std::async for task-based parallelism
//   - std::thread for simple thread usage
//   - std::mutex and std::lock_guard for thread-safe logging
//   - std::atomic for a thread-safe counter
//   - STL containers and algorithms (std::vector, std::for_each, insert, etc.)
//   - Splitting work into chunks based on hardware concurrency
//   - Preserved and extended comments to explain each concept

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <string>

// ======================
// Logger: thread-safe logging utility
// ======================
class Logger {
public:
    // Log a message with thread-safe access to std::cout
    static void log(const std::string &msg) {
        std::lock_guard<std::mutex> lock(getMutex());
        std::cout << msg << std::endl;
    }
private:
    // We use a function-local static mutex so initialization is thread-safe in C++11+
    static std::mutex& getMutex() {
        static std::mutex m;
        return m;
    }
};

// ======================
// DataProcessor: processes a vector of ints in parallel
// ======================
class DataProcessor {
public:
    // Constructor: takes reference to input data
    DataProcessor(const std::vector<int> &inputData)
        : data_(inputData), processedCount_(0)
    {
        // Reserve space for processed_ so we can insert results efficiently later.
        processed_.reserve(data_.size());
    }

    // Splits work into chunks and processes them via std::async tasks
    void processInParallel() {
        size_t length = data_.size();
        if (length == 0) {
            Logger::log("[DataProcessor] No data to process.");
            return;
        }

        // Determine number of hardware threads
        unsigned int concurrency = std::thread::hardware_concurrency();
        if (concurrency == 0) {
            concurrency = 2; // Fallback if detection fails
        }
        Logger::log("[DataProcessor] Launching processing using " + std::to_string(concurrency) + " tasks.");

        // Compute chunk sizes
        size_t chunkSize = length / concurrency;
        size_t remainder = length % concurrency;

        std::vector<std::future<std::vector<int>>> futures;
        futures.reserve(concurrency);

        size_t start = 0;
        // Launch async tasks for each chunk
        for (unsigned int i = 0; i < concurrency; ++i) {
            size_t end = start + chunkSize + (i < remainder ? 1 : 0);
            if (start >= end) {
                // No more data left; in case data size < concurrency
                break;
            }
            // Capture 'this', start, end by value in std::async call
            futures.emplace_back(
                std::async(std::launch::async,
                           &DataProcessor::processRange, this, start, end)
            );
            start = end;
        }

        // Collect results
        for (auto &fut : futures) {
            // get() will wait for the async task to finish and return its vector<int>
            std::vector<int> chunkResult = fut.get();
            // Append chunkResult into processed_
            // This demonstrates use of STL algorithm insert with iterators
            processed_.insert(processed_.end(), chunkResult.begin(), chunkResult.end());
        }

        Logger::log("[DataProcessor] All tasks completed. Total processed elements: "
                    + std::to_string(processedCount_.load()));
    }

    // Returns const ref to processed data
    const std::vector<int>& getProcessedData() const {
        return processed_;
    }

    // Returns how many elements were processed (atomic counter)
    int getProcessedCount() const {
        return processedCount_.load();
    }

private:
    const std::vector<int> &data_;     // Reference to original data
    std::vector<int> processed_;       // Holds processed results
    std::atomic<int> processedCount_;  // Counts processed elements safely

    // Process a sub-range [start, end) of data_. Example: double each element.
    std::vector<int> processRange(size_t start, size_t end) {
        std::vector<int> result;
        result.reserve(end - start);
        for (size_t i = start; i < end; ++i) {
            int value = data_[i];
            // Example processing: double the value
            int processedValue = value * 2;
            result.push_back(processedValue);
            // Increment atomic counter
            ++processedCount_;

            // Optional: per-element progress logging (commented out to reduce clutter)
            // Logger::log("[DataProcessor] Processed index " + std::to_string(i));
        }
        Logger::log("[DataProcessor] Chunk processed indices [" + std::to_string(start)
                    + ", " + std::to_string(end) + ")");
        return result;
    }
};

// ======================
// main(): orchestrates the example
// ======================
int main() {
    // Example input: vector of integers
    std::vector<int> data;
    // Fill data with some values; for demonstration, use 1..20
    for (int i = 1; i <= 20; ++i) {
        data.push_back(i);
    }

    Logger::log("[Main] Starting multithreaded processing example.");

    // Create DataProcessor instance
    DataProcessor processor(data);

    // Launch processing in parallel
    processor.processInParallel();

    // Retrieve processed data
    const auto &result = processor.getProcessedData();

    // Output the processed data using std::for_each and a lambda
    std::cout << "[Main] Processed data: ";
    std::for_each(result.begin(), result.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;

    // Example: launch a separate std::thread to do something concurrently
    std::thread t([] {
        Logger::log("[Main] Hello from a separate std::thread!");
    });
    t.join(); // Wait for the thread to finish

    // Show atomic counter result
    Logger::log("[Main] Total elements processed (atomic count): "
                + std::to_string(processor.getProcessedCount()));

    Logger::log("[Main] Example complete. Exiting.");
    return 0;
}
