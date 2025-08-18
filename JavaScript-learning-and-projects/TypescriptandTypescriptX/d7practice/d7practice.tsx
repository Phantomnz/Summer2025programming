// Polymorphic "as prop" in TSX (component that renders different tags, preserves attrs) - The generic E makes props follow the rendered element -- safe polymorphism
type AsProp<E extends React.ElementType> = {// This line defines Type of the "as" prop and its behavior
    as?: E; // optional prop to specify the element type
} & React.ComponentPropsWithoutRef<E>; // props of the element type, excluding ref

function Text1<E extends React.ElementType = "span">( // function definition for Text1
    { as, children, ...rest }: AsProp<E> // destructuring props
){
    const Comp = as ?? "span"; // default to "span" if no "as" prop
    return <Comp {...rest}>{children}</Comp>; // render the component with props
}

// Usage:
<>
<Text1>Default Span</Text1>
<Text1 as="a" href="/docs">Link text</Text1> href allowed
<Text1 as="button" onClick={() => alert("Clicked!")}>Button text</Text1> onClick allowed
</>
