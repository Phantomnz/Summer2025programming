// Interaction Types (&) - Combine multiple types into one -- result must satisfy all members
type HasID = { id: string;} // has an id
type Timestamps = { createdAt: Date; updatedAt: Date;} // has timestamps
type Entity = HasID & Timestamps; // has id and timestamps

const e: Entity = {
    id: "123",
    createdAt: new Date(),
    updatedAt: new Date()
}; // If intersected types define the same key with incompatible types, the result becomes 'never' for that key

// Discriminated Unions + Exhaustive checking - Tag each variant with a literal "discriminant" and use a switch that proves you handles every case.
type Shape =
| { kind: "circle"; radius: number; }
| { kind: "square"; size: number; }
| { kind: "rectangle"; width: number; height: number; }

function area(s: Shape): number {
    switch (s.kind) {
        case "circle": return Math.PI * s.radius ** 2;
        case "square": return s.size ** 2;
        case "rectangle": return s.width * s.height;
        default: {
            const _exhaustive: never = s; // Ensures all cases are handled
            return _exhaustive; // This line will cause a compile error if a new shape is added without handling it
        }
    }
}

// Index Access Types & Key-Safe get - Use keyof and T[K] to reference property types and write safe helpers
function getProp<T, K extends keyof T>(obj: T, key: K): T[K] {
    return obj[key]; // Safe access to property
}
interface User {id: number; name: string; active: boolean;}
const u: User = {id: 1, name: "Alice", active: true};

const id = getProp(u, "id"); // Safe access to id
const act = getProp(u, "active"); // Safe access to active
// getProp(u, "name"); // Error: Argument of type '"name"' is not assignable to parameter of type '"id" | "active"'.

// Module Augmentation (extend 3rd party types) - Adds fields to an existing module's types by reopening its declaration. Great for attaching metadata to framework objects
// types/express-augment.d.ts
//import "express-serve-static-core";
//declare module "express-serve-static-core" {
  //  interface Request {
    //    user?: {id: string; roles: string[];}
    //}
//}
// Now 'req.user' is typed in your app: app.get("/me", (req, res) => res.json({ id: req.user?.id }));
// Tip: Put augmentations in .d.ts files that are included by tsconfig.json's include

// Namespaces & Declaration Merging (ambient types): Namespaces are still handy for ambient type declarations (typing globals or UMD libs) and they support merging
// ambient.d.ts (no imports -> global context)
declare namespace MySDK {
    interface Config { apiKey: string; } // Configuration for MySDK
    function init(cfg: Config): void; // Initialize MySDK with config
}
// Usage (JS library on window provides MySDK at runtime):
MySDK.init({ apiKey: "XXX"});

// Declaration merging: 2 interfaces with the same name merge
interface Setting { theme: "light" | "dark"; }
interface Setting { locale: string;}
const s: Setting = { theme: "light", locale: "en-US" };
// Guidelines : Prefer ES modules for your own code; use namespace mainly to describe globals from non-module scripts