// TSX: safe React context + custom hook - Type a context as nullable, then expose a hook that guarantees non-null usage
import React, { createContext, use, useContext } from 'react';
type User = { id: string; name: string }; // User type with id and name properties
const UsrCtx = createContext<User | null>(null); // Create a context that can be null
export function useUser(): User { // Custom hook to use the User context
    const u = useContext(UsrCtx); // Get the current context value
    if (!u) throw new Error("useUser must be used within a UserProvider"); // Ensure context is not null
    return u; // Return the user context
}
// usage:
function Greeting(){
    const user = useUser(); // Get the user context
    return <h1>Hello, {user.name}!</h1>; // Greet the user
}
