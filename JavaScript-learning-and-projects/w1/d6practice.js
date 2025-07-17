// Symbol.iterator and custom iterables - You can make objects iterable by defining a [Symbol.iterator] method that returns an iterator:
const collection = {
    items: [10, 20, 30], // An array of items to iterate over
    [Symbol.iterator]() { // This method returns an iterator object
        let index = 0; // Initialize index to 0
        return {
            next: () => ({ // The next method returns the next value in the iteration
                value: this.items[index++], // Return the current item and increment the index
                done: index > this.items.length // Indicate if the iteration is complete
            })
        };
    }
};
for (const num of collection){
    console.log(num); // 10, then 20, then 30
}

// Tagged template literals - A function can process template literals before they're turned into strings, useful for internationalization or safe HTML:
function tag(parts, ...values) {
    return parts.reduce((acc, part, i) => acc + part + (values[i] || ""), ""); // Combine parts and values into a single string
}
const unsafe = "<script>alert(1)</script>"; // A potentially unsafe string
console.log(tag`User input: ${unsafe}`); // User input: <script>alert(1)</script> - The tag function processes the template literal

// Intl API for Number Formatting - Format numbers based on locale and options without external libraries:
const nf = new Intl.NumberFormat("de-DE", { style: "currency", currency: "EUR" });
console.log(nf.format(1234567.89)); // 1.234.567,89 € - Formats the number as currency in German locale

// URL and URLSearchParams - Easily parse and manipulate URLs and query strings:
const url = new URL("https://example.com/path?name=John&age=30");
console.log(url.searchParams.get('name')); // John
console.log(url.searchParams.get('age')); // 30
url.searchParams.set('age', '31'); // Update the age parameter
console.log(url.toString()); // https://example.com/path?name=John&age=31 - Updated URL with new age parameter

// Promise.race() - Returns the first settled promise from an array of promises, useful for timeouts:
const fetchWithTimeout = (url, ms) => // This function fetches a URL and rejects if it takes too long
    Promise.race([
        fetch(url), // Fetch the URL
        new Promise((_, reject) => setTimeout(() => reject(new Error("Timeout")), ms)) // Reject after timeout
    ]);

