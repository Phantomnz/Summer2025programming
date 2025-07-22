// Conditional Rendering in JSX - You can embed tenary expressions (expressions that evaluate to true or false) directly in JSX to choose which element to render based on a boolean property.
function status ({ online}) {
    return (
        <div>
            { online ? <span>🟢Online</span> : <span>🔴Offline</span> }
        </div>
    );
}

// Event handling with properties - Pass a callback function via properties and attach it to an element's onclick. The arrow function lets you send arguments back to the parent
function Clicker({ onClick}) {
    return <button onClick={() => onClick("Clicked!")}>Click me!</button>;
}

// Passing children via props.children - JSX lets you nest content inside a component; inside the component you can access it as props.children
function Wrapper({ children}){
    return <div className="wrapper">{children}</div>;
}
// Usage:
<Wrapper>
    <p>This is some content inside the wrapper.</p>
</Wrapper>
