// Custom Iterators with Generators - Generators simplify the creation of iterators. Use function* and yield:
function* counter() {
    let i = 1;
    while (true) {
        yield i++;
    }
}
const gen = counter();
console.log(gen.next().value); // 1
console.log(gen.next().value); // 2

// Modules: Dynamic import() - Loads code only when needed, returning a promise:
async function loadModule() {
    const {quiz} = await import('./quiz.js'); // Assuming quiz.js exports a function named quiz
    quiz.start(); // Start the quiz
}

// WeakSet for Object Tracking - Like Set, but holds only objects and does not prevent garbage collection:
const seen = new WeakSet(); 
let obj = {}; // Create an object
seen.add(obj); // Add it to the WeakSet
console.log(seen.has(obj)); // true
obj = null; // Now obj can be garbage collected

// String.prototype.padStart/ padEnd - Pad strings to a given length with a fill character:
console.log('5'.padStart(2,'0')); // '05'
console.log('7'.padEnd(3,'-')); // '7--'

// Reflect API for Meta-Programming - Provides methods like Reflect.get and Reflect.set as function-based equivalents to property access:
const user = {name: 'Alice'};
console.log(Reflect.get(user, 'name')); // 'Alice'
Reflect.set(user, 'age', 30);
console.log(user.age); // 30