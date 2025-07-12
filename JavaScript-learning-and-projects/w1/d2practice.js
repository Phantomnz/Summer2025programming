// Destructuring assignment: Allows unpacking values from arrays or properties from objects into distinct variables

// Array destructuring
const [first, second] = [15, 30];
console.log(first,second); // 15 30

// Object destructuring
const { name, age} = { name: "Martynas", age: 19 };
console.log(name, age); // Martynas 19

// Default Function Parameters: You can specify default values for parameters when calling a function without those arguments
function greet(name = "guest"){
    console.log('Hello, ${name}!')
}
greet(); // Hello guest!
greet("Bob"); // Hello Bob!

/*
Rest (..args) and Spread (..array) Syntax
- Rest collects multiple arguments into an array
- Spread expands an array into individual elements
*/

function sum(...nums){
    return nums.reduce((a,b) => a + b, 0);
}
console.log(sum(1,2,3)); //6

const arr = [1,2];
const extended = [...arr, 3,4];
console.log(extended); // [1,2,3,4]

// Array map and filter methods: Functional helpers for transforming and selecting array items without loops
const nums = [1,2,3,4];
const doubled = nums.map(n => n * 2); // [2,4,6,8] doubles entire array
const evens = nums.filter(n => n % 2 === 0); // [2,4] odd numbers are filtered out

// Modules: export/import: JavaScript Modules let you split code into reusable files

// math.js
// export function add(a,b) {return a+b;}

// main.js
// import { add } from "./math.js";
// console.log(add(2, 3)); // 5
