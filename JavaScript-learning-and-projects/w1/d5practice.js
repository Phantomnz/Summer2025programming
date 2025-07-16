// Symbols as Unique keys - Symbols create unique, non-string object keys, ideal for hiding internal properties
const id = Symbol("id"); // Unique identifier
const obj = { [id]: 123}; // Using a symbol as a key
console.log(obj[id]); // Accessing the value using the symbol key, outputs: 123

// WeakMap for Private data- A WeakMap allows you to associate private data with objects without preventing garbage collection
const privates = new WeakMap(); // Create a WeakMap to hold private data
class myclass {
    constructor(secret){
        privates.set(this, { secret }); // Store private data in the WeakMap
    }
    reveal(){
        return privates.get(this).secret; // Access private data from the WeakMap
    }
}

// Dynamic Property Names - You can comput object property names on the fly using bracket notation in literals
const prop = "score";
const player = { [prop]: 100 }; // Dynamic property name
console.log(player.score); // Accessing the dynamic property, outputs: 100

// Object.freeze() - Prevents modification of an objects properties (but not nested objects)
const config = Object.freeze({ mode: "dark" }); // Freezing the object
// config.mode = "light"; // This line would throw an error in strict mode, but in non-strict mode it fails silently

// Promise.allSettled() - Waits for all promises to settle (either fulfilled or rejected) and returns their results
const p1 = Promise.resolve(1);
const p2 = Promise.reject(new Error("Failed"));
Promise.allSettled([p1, p2]).then(console.log);
// Outputs: [{status: "fulfilled", value: 1}, {status: "rejected", reason: Error: Failed}]