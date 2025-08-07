// Conditional Types - Define types that depend on a condition
type IsString<T> = T extends string ? true : false; // Example usage
type A = IsString<"hello">; // true
type B = IsString<42>; // false

// keyof operator - Extract the union of keys from an object type
interface User { id: number; name: string; } // Example usage
type UserKeys = keyof User; // "id" | "name", the keys of User

// Mapped Types - Create new types by transforming each property in an existing type
type Readonly1<T> = { readonly [P in keyof T]: T[P] }; // create a readonly version of T
type ReadonlyUser = Readonly1<User>; // { readonly id: number; readonly name: string; }

// infer in connditional types - Extract and reuse parts of a type
type ReturnType1<T> = T extends (...args: any[]) => infer R ? R : any; // infer the return type of a function
function fn(): string { return "hello"; } // Example usage
type R = ReturnType1<typeof fn>; // R is string, the return type of fn

// Utility Type Partial<T> - Make all properties of a type optional
interface config { host: string; port: number; } // Example usage
const cfg: Partial<config> = { host: "localhost" }; // cfg can have only host, port is optional


