// Basic Type Annotations - You can annotate variables, function parameters and return types to enforce static typing.
let count: number = 0;
function greet(name: string): string { // Function takes a string parameter and returns a string
    return `Hello, ${name}`;
}

// Interfaces for Object shape - Define an interface to describe the expected structure of an object, improving code clarity and tooling.
interface User {
    id: number;
    name: string;
    email?: string; // Optional property
}
const u: User = { id: 1, name: "Alice" };

// Union Types - Allow a variable to be one of several types, enabling more flexible APIs while retaining type safety.
function format(input: string | number): string { // Function can accept either a string or a number
    return typeof input === 'number' ? input.toFixed(2) : input.trim(); // Convert number to string with 2 decimal places or trim string
}

// Literal Types - Restrict a variable to specific literal values for tighter control
type Direction = 'up' | 'down' | 'left' | 'right'; // Only these values are allowed
function move(dir: Direction) { 
    console.log(`Moving ${dir}`); // Function accepts only the specified directions
}
move('up'); // Valid
// move('forward'); // Invalid, would cause a TypeScript error

