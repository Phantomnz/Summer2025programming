// Essential Utility Types (beyond Partial) - These compose powerfully to shape APIs without rewriting types
type User = { id: string; name: string; email?: string; active: boolean }; // User type definition

// Pick/Omit
type PublicUser = Pick<User, "id" | "name">; // Publicly accessible user information
type UserWithoutFlags = Omit<User, "active">; // User information without the active flag

// Required / Readonly 
type StrictUser = Required<User>; // All properties are required
type ReadonlyUser = Readonly<User>; // All properties are readonly

// Record 
type Flags = Record<"admin" | "beta", boolean>;


// Satisfies operator (type-check without widening) - Ensures a value conforms to a type while preserving the values literal inference
// Great for config objects where you want strict checking but precise literals
type Theme = { primary: `#${string}`; spacing: number }; // Theme type definition
const theme = {
    primary: "#0ea5e9", // Primary color
    spacing: 8 // Spacing value
} as const satisfies Theme; // Ensures theme conforms to Theme type without widening the type of primary

// Contrast with assertion:
const theme2 = { primary: "#0ea5e9", spacing: 8 } as Theme; // Asserts theme2 conforms to Theme type


// Readonly Arrays & Tuples (compile-time immutability) - readonly prevents accidental mutation in APIs; pair with as const to lock tuple shapes
function sum(xs: readonly number[]): number { // function definition
    // xs.push(1); // Error: Cannot modify a readonly array
    return xs.reduce((a, b) => a + b, 0); // Sum of elements
}
const pt = [10, 20] as const; // Tuple with fixed shape
type Point = typeof pt; // Point type inferred from tuple


// Path Aliases with tsconfig.json - organize imports with aliases; ensure your tooling understands them
// JSON stuff goes here in notes, it will be in a seperate tsconfig.json file
// Then:
import {api} from "@/services/api";
// For Node/Jest/Vite/Webpack, enable mathcing resolver support (e.g., tsconfig-paths, bundler config) so runtime can resolve the same aliases
