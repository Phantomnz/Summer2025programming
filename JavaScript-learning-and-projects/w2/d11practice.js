// Typed Arrays for Binary Data - Typed arrays like Uint8array let you work with binary data buffers efficiently.
const buffer = new ArrayBuffer(16); // Create a buffer of 16 bytes
const view = new Uint16Array(buffer); // Create a view for 16-bit integers
view[0] = 500; // Set the first element to 500
view[1] = 1000; // Set the second element to 1000
console.log(view[0]); // Output: 500
console.log(view[1]); // Output: 1000

// The globalThis Object - Provides a standard way to access the global object across environments
console.log(globalThis === window); // true in browsers
console.log(globalThis === global); // true in Node.js

// Array.prototype.reduceRight() - Works like reduce but processes elements from right to left:
const arr = ['a', 'b', 'c'];
const result = arr.reduceRight((acc, v) => acc + v, 'Start: '); // Output: "Start: cba"
console.log(result); 

// Proxy for intercepting Operations - Wrap an object to customize property access, assignment, etc.
const target = {}; // The object to wrap
const p = new Proxy(target, {
    get(obj, prop) { console.log(`Getting ${prop}`); return obj[prop]; },
    set(obj, prop, value) { console.log(`Setting ${prop} to ${value}`); obj[prop] = value; return true; }
});
p.x = 10; // Logs: Setting x to 10
console.log(p.x); // Logs: Getting x, Output: 10

// WeakRef and FinalizationRegistry - Create weak references and cleanup callbacks when objects are garbage collected (experimental in some environments)
const registry = new FinalizationRegistry(token => console.log(`finalized ${token}`)); // Create a registry to track finalization
let obj = { data: 'heavy'}; // Create an object
registry.register(obj, 'myObject'); // Register the object with a token
obj = null; // Remove the reference to the object, allowing it to be garbage collected  

