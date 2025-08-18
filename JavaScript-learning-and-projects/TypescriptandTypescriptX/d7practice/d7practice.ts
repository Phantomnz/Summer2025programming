// unknown vs any (use unknown + narrowing) -- any disables type checking -- unknown forces you to narrow before use (safer "top" type)
function parse(json: string): unknown {
    return JSON.parse(json);
}
const val = parse('{"n":42}'); // making a type assertion 
// val.n; // Error: Object is of type unknown
if (typeof val === "object" && val !== null && "n" in val) { // Type narrowing
    const n = (val as { n: number }).n; // Now TypeScript knows that val has a property n
}

// Meta Utility types: ReturnType, Parameters, InstanceType, ConstructorParameters, Awaited - These pull types from values -- handy for refactors and API surface typing
function make(id:number, name: string) { // function definition
    return { id, name };
}
type R = ReturnType<typeof make>; // { id: number; name: string; }
type P = Parameters<typeof make>; // [id: number, name: string]

class Box { constructor(public v: string) {} }
type B = InstanceType<typeof Box>; // Box
type C = ConstructorParameters<typeof Box>; // [v: string]

// 'Awaited' wraps unnested promises
type T1 = Awaited<Promise<string>>; // string
type T2 = Awaited<Promise<Promise<number>>>; // number

// Type-only imports & typeof import() (clean build zero runtime cost) -- Use import type when you only need types (works well with isolatedModules/bundlers) -- typeof import("./x") lets you reference a module's shape (shape as in "the structure of the module") from types
// pretend this is in lib.ts
export interface Config { mode: "dev"| "prod";} // defining the shape of the config object

// pretend this is in app.ts
import type { Config } from "./lib"; // importing only types, no runtime cost, erased at compile type
const cfg: Config = { mode: "dev" }; // creating a config object

// Grab a module's **value** types
type Lib = typeof import("./lib"); // { Config: Interface ... }


// Precision via tsconfig strictness: noUncheckedIndexedAccess & exactOptionalPropertyTypes
// JSON code is here in notes, this will be in a tsconfig.json file
const xs: number[] = []; // defining an array of numbers called xs
const maybe = xs[0]; // maybe is of type number | undefined due to noUncheckedIndexedAccess
if (maybe !== undefined) console.log(maybe.toFixed(2)); // checking if maybe is defined and formatting it
interface Opt { a?: number } // with exactOptionalPropertyTypes, defining an object type with an optional property
const o: Opt = {}; // creating an object of type Opt
// const p: Opt = { a: undefined } // with exactOptionalPropertyTypes not assignable unless `a: number | undefined`
// These flags help catch common errors and improve code quality, especially in larger TS/TSX codebases
