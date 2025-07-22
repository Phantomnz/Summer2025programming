// Private Class Fields - Define truly private properties using #. They are not accessible outside the class.
class counter {
    #count = 0; // Private field
    increment() { this.#count++; } // Method to increment the private field
    get value() { return this.#count;} // Getter to access the private field
}
const c = new counter();
c.increment();
console.log(c.value);  // 1
// console.log(c.#count); // Error: Private field '#count' must be declared in an enclosing class

// Promise.finally() - Runs a callback when a promise settles, regardless of outcome -- useful for cleanup tasks.
fetch(url)
    .then(res => res.json()) // Process the response
    .catch(err => console.error(err)) // Handle errors
    .finally(() => console.log("Request completed")); // Runs after the promise settles

// Logical nullish Assignment (??=) - Assigns a value only if the left-hand side is null or undefined.
let settings = {timeout: 0};
settings.timeout ??= 5000; // stays 0, does not change
settings.delay ??= 1000; // Assigns 1000 
console.log(settings); // {timeout: 0, delay: 1000}

// structuredClone() - Deep-clones objects, Maps, Sets, Dates, RegExps, ArrayBuffers, etc. without manual serialization.
const original = { nested: { a: 1}}; // Original object
const copy = structuredClone(original); // Deep clone
copy.nested.a = 2; // Modify the copy
console.log(original.nested.a); // 1, original remains unchanged
console.log(copy.nested.a); // 2, copy reflects the change

// Top-Level await in Modules - In ES (ECMAScript) modules, you can await outside async functions at the top level.
// module.mjs
// const data = await fetch("/data.json").then(r => r.json()); // Fetch data at the top level
// console.log(data); // Use the fetched data directly

