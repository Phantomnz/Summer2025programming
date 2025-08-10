// Type narrowing (typeof/in/instanceof) - Use control-flow analysis to refine unions safely.
type ID = string | number | { id: string };
function toStringID(x: ID): string {
    if (typeof x === 'string') return x; // string
    if (typeof x === 'number') return String(x); // number
    if ("id" in x) return x.id; // { id: string }
    // never reached
    return "unknown";
}

// User defined type guards (x is T) - Write predicates that teach the compiler how to narrow
type Bird = {kind: "bird"; fly: () => void}; // User defined type guard for Bird
type Fish = {kind: "fish"; swim: () => void}; // User defined type guard for Fish
type Animal = Bird | Fish; // User defined type guard for Animal

function isBird(animal: Animal): animal is Bird {
    return animal.kind === "bird"; // User defined type guard for Bird
}

function isFish(animal: Animal): animal is Fish {
    return animal.kind === "fish"; // User defined type guard for Fish
}

function move(a: Animal) {
    if (isFish(a)) a.swim(); // User defined type guard for Fish
    if (isBird(a)) a.fly(); // User defined type guard for Bird
}

// as const (const assertions) for literal inference - Lock values to their most specific, readonly forms-- great for discriminants and tuples
const ACTIONS = ["create", "update", "delete"] as const;
// type ACTIONS = readonly ["create", "update", "delete"]
type Action = (typeof ACTIONS)[number]; // "create" | "update" | "delete"
const point = [10, 20] as const;
// readonly [10, 20]; prevents accidental mutation and keeps tuple shape


// Template literal types + string helpers - Compose string literal unions and transform them
type EventBase = "click" | "change" | "submit"; // Base event types
type EventHandlerName = `on${Capitalize<EventBase>}`; // "onClick" | "onChange" | "onSubmit"
type Shout<T extends string> = Uppercase<T>; // Convert to uppercase
type Loud = Shout<"ok">; // "OK"


// Key remapping in mapped types (as) - Generate new keys or filter keys when mapping over keyof.
type Getters<T> = {
    [K in keyof T as `get${Capitalize<string & K>}`]: () => T[K]; // Generate getter methods
};
interface User { id: number; name: string;}
type UserGetters = Getters<User>; // { getId: () => number; getName: () => string; }
/*
{
    getId: () => number;
    getName: () => string;
}
*/
type OnlyStrings<T> = {
    [K in keyof T as T[K] extends string ? K : never]: T[K]; // Filter keys with string values
};
type UserStrings = OnlyStrings<User>; // { name: string; }