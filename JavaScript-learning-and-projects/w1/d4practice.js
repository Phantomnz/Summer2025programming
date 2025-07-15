// Optional chaining (?.) : Safely access nested properties without checking each level
const user = { profile: {name: "Alice"}};
console.log(user.profile?.email); // undefined instead of error

// Nullish coalescing (??) : Provide a default value if the left-hand side is null or undefined, not other falsy values
const timeout = 0;
console.log(timeout ?? 5000); // 0, because timeout is not null or undefined (whereas '||' would return 5000)

// Dynamic import: Load modules asynchronously at runtime returning a promise:
async function loadUtil(){
    const { utilFunc} = await import('./util.js'); // Assuming util.js exports a function named utilFunc
    utilFunc(); // Call the imported function
    console.log("Util function loaded and executed.");
}
loadUtil(); // Call the function to load and execute utilFunc

// BigInt for large integers: Represent integers beyond the 2^53 - 1 limit of Number using the n suffix
const largeNumber = 1234567890123456789012345678901234567890n; // BigInt
console.log(largeNumber + 1n); // 1234567890123456789012345678901234567891n

// Unicode Property Escapes in Regular Expressions: Match characters based on Unicode properties e.g {\p{L}} for letters
const re = /\p{L}+/gu; // Matches one or more Unicode letters
console.log(re.test("Hello")); // true
console.log("cafe123".match(re)); // [ 'cafe' ]

