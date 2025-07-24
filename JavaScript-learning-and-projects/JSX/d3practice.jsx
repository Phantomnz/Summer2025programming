// Function Components with state (useState) - The useState Hook gives a state variable (count) and a setter function (setCount) in a functional component. Calling setCount re-renders with the new value
import { useState } from 'react';
function Counter() {
    const [count, setCount] = useState(0); // Initialize count to 0

    return (
        <div>
            <p>Count: {count}</p>
            <button onClick={() => setCount(count + 1)}>Increment</button>
        </div>
    );
}

// Side Effects with useEffect - useEffect runs after render. Returning a function cleans up (here clearing the interval). The empty array means "run once on mount".
import { useState, useEffect } from 'react';
function Timer(){
    const [seconds, setSeconds] = useState(0);

    useEffect(() => {
        const id = setInterval(() => setSeconds(s => s + 1), 1000); // Increment seconds every second
        return () => clearInterval(id); // Cleanup function to clear the interval
    }, []); // Empty array means this effect runs once on mount

    return <p>Seconds: {seconds}</p>;
}

// className instead of class - Since class is a reserved keyword in JavaScript, JSX uses className to set HTML classes.
function Alert(){
    return <div className="alert">This is an alert!</div>;
}
