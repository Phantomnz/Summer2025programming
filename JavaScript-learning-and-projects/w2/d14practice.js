// Array.prototype.find() and findIndex() - find(fn) returns the first element matching the predicate, or undefined if not found, findIndex(fn) returns its index or -1 if not found
const numbers = [{id:1}, {id:2}, {id:3}, {id:4}, {id:5}];
const u = numbers.find(num => num.id === 3);
const i = numbers.findIndex(num => num.id === 3);
console.log(u); // {id: 3}
console.log(i); // 2

// String.prototype.replaceAll() - Replaces all occurrences of a substring or pattern, unlike replace() which only does the first by default
const s = "foo bar foo";
const r = s.replaceAll("foo", "baz");
console.log(r); // "baz bar baz"

// AbortController for Cancelable Fetch - You can create a signal to cancel a fetch request if it takes too long or become unnecessary
const ac = new AbortController();
fetch('https://jsonplaceholder.typicode.com/posts', { signal: ac.signal })
  .then(response => response.json()) // Fetching posts from a placeholder API
  .then(data => console.log(data)) // Log the fetched data
  .catch(err => {
    if (err.name === 'AbortError') {
      console.log('Fetch aborted');
    } else {
      console.error('Fetch error:', err);
    }
  });
  ac.abort(); // Call this to cancel the fetch

// Web Crypto API (crypto.subtle) - Built-in browser API for secure crytptographic operations like hashing, encryption, and signing
(async function() {
  const data = new TextEncoder().encode("hello"); // Encode string to Uint8Array
  const hash = await crypto.subtle.digest("SHA-256", data); // Hash the data using SHA-256 (SHA-256 is a cryptographic hash function)
  console.log(new Uint8Array(hash)); // Log the hash as a byte array
})();

// BigInt.asUintN() and asIntN() - Constrain a BigInt to N-bit width, emulating fixed-size integers
const bigIntValue = 12345678901234567890n;
const uintN = BigInt.asUintN(8, bigIntValue); // Constrain to 8-bit unsigned integer
const intN = BigInt.asIntN(8, bigIntValue); // Constrain to 8-bit signed integer 
console.log(uintN); // 210n (last 8 bits)
console.log(intN); // -46n (last 8 bits interpreted as signed)

