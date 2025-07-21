// Named function expression - You can give a name to a function expression for clearer stack traces and recursion.
const factorial = function fact(n) {
    return n <= 1 ? 1 : n * fact(n-1); // Recursive call using the named function
};
console.log(factorial(5)); // Output: 120

// Array flat() and flatmap() - flat(depth) flattens nested arrays  up to the given depth, flatMap(fn) maps each element and flattens one level.
const arr = [1,[2, [3]]];
console.log(arr.flat(2)); // Output: [1, 2, 3]
console.log([1,2,3].flatMap(x => [x,x*2])); // Output: [1, 2, 2, 4, 3, 6]

// Object.getOwnPropertyDescriptors() - Retrives descriptors (writable, enumerable, configurable) for all own properties at once
const obj = { get a() { return 1;}, b: 2}; // Using a getter and a data property
console.log(Object.getOwnPropertyDescriptors(obj)); 

// Intl.DateTimeFormat Options - Format dates/times with localization and custom options
const fmt = new Intl.DateTimeFormat('en-GB', {
    weekday: 'long', year: 'numeric', month: 'short', day: 'numeric', // Options for formatting
});
console.log(fmt.format(new Date())); // Output: e.g., "Monday, 1 Jan 2024"

// WeakRef and FinalizationRegistry (stage 3) - Create weak references and register cleanup callbacks for garbage-collected objects:
// Note: limited browser support
const ref = new WeakRef({heavy: true}); // Create a weak reference to an object
const registry = new FinalizationRegistry(token => { console.log(`cleaned up ${token}`); }); // Create a registry for cleanup
let obj1 = { name: 'resource' }; // Create an object to be tracked
registry.register(obj1, 'resource'); // Register the object with a token
obj1 = null; // Dereference the object, allowing it to be garbage collected ; registry callback invoked later


