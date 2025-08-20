// Distributive conditional types (and how to stop distribution) - Conditional types distribute over unions by default
type ToArray<T> = T extends any ? T[] : never; // This will distribute over unions
type A = ToArray<string | number>; // A is string[] | number[]
// Wrap the type in a tuple to turn off distribution
type ToArrayNondist<T> = [T] extends [any] ? [T[]] : never; // This will not distribute over unions
type B = ToArrayNondist<string | number>; // B is [string[]] | [number[]]
// Use nondistribution when you want to treat a union as a single whole

// Union->Intersection trick (UnionToIntersection) - Turn a union into an intersection -- handy for merging callable signatures or prop bags
type UnionToIntersection<U> = (U extends any ? (x: U) => void : never) extends (x: infer I) => void ? I : never; // This will turn a union into an intersection
type U = { a: string } | { b: number }; // U is { a: string } or { b: number } 
type I = UnionToIntersection<U>; // I is { a: string } & { b: number }
// This patterns underlies advanced helpers (e.g. composing middleware, merging HOC (Higher Order Component) props)

// Callback Variance: Parameters are (ideally) contravariant - A handler that accepts a broader event type is safer. Model that with generics
type Handler<T> = (value: T) => void; // A handler that accepts a value of type T
declare const onNumber: Handler<number>; // A handler that accepts a number
declare const onAny: Handler<number | string>; // A handler that accepts a number or string
// assign broader-accepting handler where narrower is expected:
const h: Handler<number> = onAny; // ok (can handle all numbers)
// const h2: Handler<number | string> = onNumber; // error (cannot handle all strings)
// IN TS, function parameters are bivariant (meaning they can be used in both covariant and contravariant positions) in some positions for practicality, but aim for contravariance (e.g. using `unknown` or more specific types) in your APIs (accept supertypes) to keep assignments safe-- especially for event systems

// Default generic parameters (safer API surfaces) - Provide sensible defaults while allowing callers to override
async function fetchJson<T = unknown>(url: string): Promise<T> { // function fetchJson
  const r = await fetch(url); // fetch the URL
  return (await r.json()) as T; // return the JSON response as type T
}
export {}
const a = await fetchJson("..."); // call fetchJson with a URL, a: unknown
const b = await fetchJson<{ id: number }>("..."); // call fetchJson with a URL and specify the type, b: { id: number }
// Great for fetchers, parsers, and utilities where callers can opt into stronger typing
