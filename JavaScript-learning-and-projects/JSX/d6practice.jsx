// Higher-Order Component (HOC) - HOCs are functions that take a component and return a new component with additional functionality (here, logging props).
function withLogging(WrappedComponent) {
    return function(props) { // This is the new component
        console.log('Rendering with props:', props); // Log the props to the console
        return <WrappedComponent {...props} />; // Render the wrapped component with the original props
    };
}
const LoggedButton = withLogging(Button); // Create a new component that logs props when rendered

// Memorizing Functional Components with React.memo - React.memo wraps a component and skips re-rendering when its props haven't changed, optimizing performance.
import React from 'react';
const ExpensiveComponent = React.memo(function({ value }) { // This component will only re-render if 'value' prop changes
    // expensive calculations or rendering logic
    return <div>{value}</div>;
});

// Forwading Refs with React.forwardRef - React.forwardRef lets parent components pass a ref through to a DOM (<input>) element in a child component.
import React from 'react';
const Input = React.forwardRef((props, ref) => ( // This component forwards the ref to the input element
    <input ref={ref} {...props} /> // Forward the ref to the input element
));

const ref = React.createRef(); // Create a ref to be passed to the Input component
<Input ref={ref} placeholder="Type here..." />; // Use the Input component with the ref


