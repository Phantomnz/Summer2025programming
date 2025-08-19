// Custom assertion functions (asserts...) - Teach the compiler about runtime checks so types narrow automatically
function assert(condition: unknown, msg = "Assertion failed"): asserts condition { // assert function for runtime checks
    if (!condition) { // Check if the condition is false
        throw new Error(msg); // Throw an error with the provided message
    }
}

function assertHasId(x: unknown): asserts x is { id: string }{
    if (!(typeof x === "object" && x !== null && "id" in x && typeof (x as any).id === "string")) { // checking if x is an object with a string 'id' property
        throw new Error("Assertion failed: Object does not have a string 'id' property"); // Throw an error if the assertion fails
    }
}
const data: unknown = JSON.parse('{"id":"u1"}'); // Parse JSON data
assertHasId(data); // Assert that data has a string 'id' property
data.id.toUpperCase(); // Now TypeScript knows data has a string 'id' property, so we can safely call toUpperCase

// Exhaustive checks with never - Guarantee all union checks are handled; fail fast at compile time if a case is missed
type Shape = 
| { kind: "circle"; radius: number }
| { kind: "square"; size: number; }
| { kind: "rectangle"; width: number; height: number; }

function assertNever(x: never): never { throw new Error("Unexpected: " + JSON.stringify(x));} // Exhaustive check for all Shape cases

function area(shape: Shape): number {
    switch (shape.kind) {
        case "circle":
            return Math.PI * shape.radius ** 2;
        case "square":
            return shape.size ** 2;
        case "rectangle":
            return shape.width * shape.height;
        default: return assertNever(shape); // error for if a new kind is added but not handled
    }
}

// Branded/ opaque types to avoid mixing IDs - Prevent accidental assignment of the same primitive across domains
declare const UserIdBrand: unique symbol; // Unique symbol for UserIdBrand
declare const OrderIdBrand: unique symbol; // Unique symbol for OrderIdBrand

type UserId = string & { readonly [UserIdBrand]: true }; // UserId branded type, readonly is enforced
type OrderId = string & { readonly [OrderIdBrand]: true }; // OrderId branded type, readonly is enforced

function asUserId(s: string): UserId { return s as UserId; } // Function to cast (cast meaning "tell TypeScript to treat this value as a different type") string to UserId
function asOrderId(s: string): OrderId { return s as OrderId; } // Function to cast (cast meaning "tell TypeScript to treat this value as a different type") string to OrderId

const uid = asUserId("user-123"); // Cast string to UserId
const oid = asOrderId("order-456"); // Cast string to OrderId
// uid = oid will now result in a type error

// this parameter types (context typing for functions) - Specify the required this type for plain functions (not arrows) to catch misuse
type Counter = { value: number }; // Counter type as an object with a single number property

function inc(this: Counter, by = 1) { this.value += by; } // Function to increment the value of the Counter object

const c: Counter = { value: 0 }; // Create a Counter object
inc.call(c, 2); // Call inc with c as the context, incrementing c.value by 2
// inc(2); // This will result in a type error as the 'this' context is not provided


