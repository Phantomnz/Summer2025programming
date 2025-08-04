// String.prototype.codePointAt() - Retrieves the Unicode code point at a given position, properly handling characters outside the Basic Multilingual Plane (BMP).
const s = '𝌆A'; // U+1D306 (GREEK LETTER YPOGEGRAMMENI) outside BMP
console.log(s.codePointAt(0).toString(16)); // Output: 1d306
console.log(s.codePointAt(1).toString(16)); // Output: 41

// for-await-of on async Iterables - Loop over objects that implement the async iterator protocol. (e.g. streams, async generators):
async function *asyncGen() { // An async generator function
    yield 1; await Promise.resolve(); // Simulate async operation
    yield 2;
}
(async () => {
    for await (const n of asyncGen()){ // Using for-await-of to iterate over async generator
        console.log(n); // Output: 1, then 2
    }
})();

// Custom Events with CustomEvent - Create and dispatch your own DOM (Document Object Model) events, carrying arbitrary data.
if (typeof document !== 'undefined') {
    const evt = new CustomEvent('user:login', { detail: { userID: 42 } }); // Create a custom event with detail
    document.dispatchEvent(evt); // Dispatch the event
    document.addEventListener('user:login', e => {
        console.log(e.detail.userID); // Output: 42
    });
}

// Defining Non-Enumerable Properties - With Object.defineProperty(), you add properties that don't show up in for...in loops or Object.keys():
const obj = {};
Object.defineProperty(obj, 'secret', { // Define a non-enumerable property
    value: 'hidden', // The value of the property
    enumerable: false, // Make it non-enumerable
    writable: true, // Allow it to be changed
});
console.log(obj.secret); // Output: hidden
console.log(Object.keys(obj)); // Output: [] (does not show 'secret')

// Number.EPSILON for Precision Testing - The smallest difference between 1 and the next representable number, useful for floating-point precision checks.
function nearEqual(a, b){
    return Math.abs(a - b) < Number.EPSILON; // Check if two numbers are close enough
}
console.log(nearEqual(0.1 + 0.2, 0.3)); // Output: true (due to floating-point precision)