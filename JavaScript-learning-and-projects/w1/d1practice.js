// let vs var scope
// let has block scope, var has function scope. This prevents accidental variable leakage in loops or conditionals.
if (true) {
    let x = 10;
    var y = 20;
}
// block scope means x is not accessible here, but y is
console.log(y); // 20
// console.log(x); // ReferenceError: x is not defined
// var can be redeclared, let cannot

// Truthy and falsy values: JavaScript treats certain values as falsy: false, 0, "", null, undefined, and NaN. Everything else is truthy.
if (!undefined) console.log("This is falsy"); // This will log "This is falsy"
if ("Hello") console.log("This is truthy"); // This will log "This is truthy"

// Arrow functions and this Binding : Arrow functions do not bind their own this; instead they inherit it from the surrounding scope. This is particularly useful in callbacks.
const obj = {
    val: 42,
    method: function() {
        setTimeout(() => console.log(this.val), 100);
    },
};
obj.method(); // Logs 42 after 100ms, because 'this' refers to obj

// Template literals: Use backticks (``) to interpolate variables or expressions directly in strings, making it easier to create complex strings.
const name = "Martynas";
console.log(`Hello, my name is ${name}.`); // Logs: Hello, my name is Martynas.

// Strict Equality (===) vs Loose Equality (==): Strict equality checks both value and type, while loose equality performs type coercion.
5 === '5'; // false, because types are different
5 == '5'; // true, because it coerces the string to a number 