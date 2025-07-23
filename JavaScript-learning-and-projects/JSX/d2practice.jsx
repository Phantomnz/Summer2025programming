// Component Naming Convention - React treats lowercase tag names as HTML elements; custom components should start with an uppercase letter.
// correct:
function MyButton() { return <button>Click me</button>; 
}
// incorrect:
// function mybutton() { return <button>Click me</button>;

// Rendering Lists with key property - The key property gives React a stable identifier for each list item, optimizing rendering and avoiding bugs when items reorder
function FruitList({ fruits }) {
    return (
        <ul>
            {fruits.map(f => <li key={f.id}>{f.name}</li>)} 
            {/* Using the id as key ensures each item has a unique identifier */}
        </ul>
    )
}

// Inline Styling in JSX - The style property takes a JS object where CSS properties are in camelCase and values are strings (or numbers for unitless properties).
function ColoredBox(){
    return (
        <div style={{ backgroundColor: 'lightblue', padding: '1rem'}}>
            This box has inline styles!
        </div>
    );
}
