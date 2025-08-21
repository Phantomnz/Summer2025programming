// Deep Read-Only Helper (recursive mapped type) - Lock nested objects to prevent accidental mutation in large apps
type ReadonlyDeep<T> = 
    T extends (...args: any) => any ? T : // If T is a function, return it as-is
    T extends object ? { readonly [K in keyof T]: ReadonlyDeep<T[K]> } : // If T is an object, make all properties readonly
    T;

type Config = ReadonlyDeep<{
    theme: { primary: string; spacing: number };
    features: { flags: string[] };
}>;
// cfg.theme.primary = "#000"; // readonly at every level

// Robust Error handling with Unknown + useUnknownInCatchVariables - Keep caught errors typed as unknown, then narrow safely
// tsconfig.json -> "useUnknownInCatchVariables": true
function isErrorWithCause(e: unknown): e is Error & { cause?: unknown} {
    return e instanceof Error; // Error type guard
}
try {
    // some code that may throw
} catch (e) {
    if (isErrorWithCause(e)) {
        console.error("Caught an error:", e.message);
        if (e.cause) {
            console.error("Caused by:", e.cause);
        }
    } else {
        console.error("Caught an unknown error:", e);
    }
}

// Context-aware Methods with ThisType (object literals) - give object-literal methods a typed this without classes
type Ctx = { x: number; y: number }; // Context type

const vector = {
    add(this: Ctx, dx: number, dy: number) { this.x += dx; this.y += dy; }, // Method that modifies context
    len(this: Ctx) { return Math.sqrt(this.x * this.x + this.y * this.y); }, // Method that reads context
};

const p: Ctx = { x: 3, y: 4 };
vector.add.call(p, 1, -2); 
console.log(vector.len.call(p)); // Outputs: 5
// Works best with "noImplicitThis": true so this must always be typed

// Practical Project Config & Declarations (interop ready) - Tidy interop and asset typing so builds are smooth:
// look at tsconfig.json for key settings at this point
declare module "*.png" { const src: string; export default src; } // PNG imports
declare module "*.svg" { const src: string; export default src; } // SVG imports
// Example for UMD (Universal Module Definition) globals:
declare const MySDK: { init(cfg: { apiKey: string }): void; }; // Global SDK type
