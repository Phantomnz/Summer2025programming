// Type aliases vs interfaces - Both can describe object shapes, but aliases can name any type (unions, primitives), while interfaces support declaration merging and extension
type ID = number | string; // Type alias for ID that can be either a number or a string - a union type
interface User {
  id: ID;
  name: string;
} // interface for an object representing a user

//Extending an Interface
interface Admin extends User {
  permissions: string[]; // Admin has additional property permissions which is an array of strings
}

// Generics for reusable components - Define functions, classes, or interfaces that work with any type, preserving type information
function wrap<T>(value: T): { value: T }{ // Generic function that takes a type parameter T
    return { value }; // Function that takes a value of type T and returns an object containing that value
}
const wrappedNumber = wrap(42); // wrappedNumber is inferred as { value: number }
const wrappedString = wrap("Hello"); // wrappedString is inferred as { value: string }

// Function Overloads - Provide multiple call signatures for a function with differing parameter or return types
function combine(a: string, b: string): string; // Overload for string input
function combine(a: number, b: number): number; // Overload for number input
function combine(a: any, b: any): any {
    return a + b; // Implementation that combines inputs, can be string or number
}
combine("x", "y");
combine(1, 2);

// Enums and const enum - Enumerations provide named constants, const enum inlines values at compile time for performance
enum Direction {
    Up = "UP", // Enum member with string value
    Down = "DOWN", // Enum member with string value
    Left = "LEFT", // Enum member with string value
    Right = "RIGHT" // Enum member with string value
}
const enum Status {
    Active = 1, // Const enum member with numeric value
    Inactive = 0 // Const enum member with numeric value
}
console.log(Direction.Up); // Outputs: UP
console.log(Status.Active); // Outputs: 1

// Type Assertions (as vs. <>) - Tell the compiler to treat a value as a specific type when you know more than it can infer
const someValue: any = "this is a string";
const strLength1: number = (someValue as string).length; // Using 'as' syntax for type assertion
const strLength2: number = (<string>someValue).length; // Using angle-bracket syntax for type assertion