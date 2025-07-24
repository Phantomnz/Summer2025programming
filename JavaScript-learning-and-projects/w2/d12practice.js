// Event Bubbling and Capturing - In the DOM (Document Object Model), events bubble up from the target element to the root unless you specify capturing.
element.addEventListener('click', handler, true); // useCapture = true triggers during capture phase
// Capturing listens top-down; bubbling listens bottom-up (default). Use this to control propagation precisely

// The call() method - The call() method lets you invoke a function with a different this context
function greet() { console.log(`Hello, ${this.name}`); }
const person = { name: 'Alice' };
greet.call(person); // Outputs: Hello, Alice
// Its useful for borrowing methods across objects

// The new Keyword - Using new creates a new object and binds this to it. Omitting new returns undefined for this in strict mode
function Person(name) {
    this.name = name; // Assigns name to the new object
}
const p = new Person('Bob'); // Creates a new Person object
console.log(p.name); // Outputs: Bob

// Closure with Loops and let - Closures inside for loops behave predictably with let because let is block-scoped
for (let i = 0; i < 3; i++) {
    setTimeout(() => console.log(i), 100);
} // Outputs: 0, 1, 2 - Each iteration has its own i due to let

// Primitive vs Reference Types - Primitives are copied by value, objects by reference. Changing a primitive doesn't affect the original, but changing an object does
let a = 5, b = a; // b is a copy of a
a = 10; // a is now 10, b is still 5

let obj1 = { x: 1 }; 
let obj2 = obj1; // obj2 references the same object as obj1
obj1.x = 2; // Changing obj1 affects obj2

