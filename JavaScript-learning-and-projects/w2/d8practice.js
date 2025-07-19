// SetTimeout Returns a Timer ID - Calling setTimeout() returns an ID you can pass to clearTimeout() to cancel the callback before it runs.
const id = setTimeout(() => console.log("This will not run"), 1000); 
clearTimeout(id); // This will prevent the callback from executing

// Function currying with bind() - You can partially apply arguments by binding null (or an object) and preset parameters
function multiply(a, b) { return a * b; }
const double = multiply.bind(null, 2); // Creates a new function that doubles the input
console.log(double(5)); // Outputs: 10

// Array.from() for Array-like Objects - Convert iterables or array-like (e.g. arguments, Nodelists) into true arrays
function listArgs() {
    return Array.from(arguments).map((x, i) => `${i}: ${x}`);
}
console.log(listArgs("a", "b", "c")); // Outputs: ["0: a", "1: b", "2: c"]

// Dynamic import.meta.url - In module context, import.meta.url gives the current module's URL. Useful for resolving relative paths
console.log(import.meta.url); // Outputs the URL (file path) of the current module

// Event Listeners Once Option - Add an event listener that automatically removes itself after the first invocation
// button.addEventListener("click", () => console.log("clicked once"), { once: true });

