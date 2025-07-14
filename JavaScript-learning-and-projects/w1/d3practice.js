// Closures - A closure lets a function "remember" variables from its creation scope even after that scope has finished executing.
function makeCounter() {
    let count = 0; // This variable is private to the closure
    return function() {
        return ++count; // Each time this function is called, it increments and returns the count
    };
}
const counter = makeCounter();
console.log(counter()); // 1
console.log(counter()); // 2

// Immediately Invoked Function Expression (IIFE) - A function that runs as soon as it is defined to create a private scope.
(function() {
    const secret = "hidden"; // This variable is private to the IIFE
    console.log("IIFE runs immediately and can access:", secret);
})();
// console.log(secret); // This would throw an error because 'secret' is not defined in this scope

// Promise chaining: Handle sequences of asynchronous operations cleanly by returning promises in .then()
fetch("/data.json")
    .then(res => res.json())
    .then(data => fetch(`/more/${data.id}`))
    .then(res => res.json())
    .then(more => console.log(more))
    .catch(err => console.error("Error:", err)); // Catch any errors in the chain

// Async/Await simplifies promises - Syntatic sugar over promises for sequential async code with try/catch for error handling
async function load(){
    try {
        const res1 = await fetch("/data.json");
        const data = await res1.json();
        const res2 = await fetch(`/more/${data.id}`);
        console.log(await res2.json());
    } catch (e) {
        console.error("Error:", e);
    }
}
load(); // Call the async function to execute the code

// Prototype-Based Inheritance - Objects inherit from other objects via the prototype chain; You can extend behaviour dynamically
const animal = {speak() {console.log("Animal speaks");}};
const dog = Object.create(animal); // Create a new object with 'animal' as its prototype
dog.speak = function() { // Override the speak method
    console.log("Dog barks");
};
dog.speak(); // "Dog barks"
console.log(dog.__proto__ === animal); // true, dog inherits from animal