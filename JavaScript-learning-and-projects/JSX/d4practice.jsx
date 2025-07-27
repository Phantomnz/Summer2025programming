// Managing component side effects cleanup - Returning a cleanup functions from useEffect ensures resources (like subscriptions) are released when dependencies change or component unmounts.
import { useEffect } from 'react';
function subscription({ source }){ // Function to manage subscriptions
    useEffect(() => {
        const sub = source.subscribe(data => console.log(data)); // Subscribe to data source
        return () => sub.unsubscribe(); // Cleanup on unmount or dependency change
    }, [source]); // Dependency array ensures effect runs when source changes
    return <p>Subscribed to {source.id}</p>
}

// Conditional component rendering with && - Using && lets you render a component only if a condition is truthy; otherwise it renders false (nothing).
function Warning({ show}){
    return (
        <div>
            {show && <p style={{ color: 'red' }}>This is a warning message!</p>} {/* Renders only if show is true */}
        </div>
    )
}

// Default Props via Function Parameters - Destructure props with default values to provide fallbacks when certain props aren't passed.
function Button({ label = "click me", onClick}){
    return <button onClick={onClick}>{label}</button>; // Renders button with default label if none provided
}
