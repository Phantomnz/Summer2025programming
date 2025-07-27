// Object Rest/Spread Properties - Use rest (...rest) and spread (...obj) properties to copy and merge objects
const { a, b, ...rest } = { a: 1, b: 2, c: 3, d: 4 }; // { a: 1, b: 2 } and rest will be { c: 3, d: 4 }
console.log(a, b, rest); // Output: 1 2 { c: 3, d: 4 }

const defaults = { x: 0, y: 0};
const point = { ...defaults, x: 5 }; // Merges defaults with new value for x
console.log(point); // Output: { x: 5, y: 0 }

// Exponentiation Operator - A succinct way to raise numbers to a power (ES2016)
console.log(2 ** 3); // Output: 8 (2 raised to the power of 3)
console.log(16 ** 0.5); // Output: 4 (Square root of 16

// Number.isFinite() vs Global.isFinite() - Number.isFinite() returns false for non-number types without coercion. The global isFinite() coerces types to numbers first.
console.log(Number.isFinite(10)); // Output: true
console.log(Number.isFinite("10")); // Output: false
console.log(isFinite("10")); // Output: true

// Intl.RelativeTimeFormat - Format human-friendly relative times (e.g., "3 days ago")
const rtf = new Intl.RelativeTimeFormat('en', { numeric: 'auto' });
console.log(rtf.format(-1, 'day')); // Output: "yesterday"
console.log(rtf.format(2, 'hour')); // Output: "in 2 hours"

// Reflect.construct() - Invoke a constructor with an arbitrary argument list, similar to new, but dynamic
class Point { constructor(x,y) {this.x = x; this.y = y;}}
const args = [10, 20];
const p = Reflect.construct(Point,args);
console.log(p); // Output: Point { x: 10, y: 20 }