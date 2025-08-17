// Typing TSX components (props, children, refs); TIP: Prefer explicit children?: React.ReactNode in your props; avoid React.FC if you don't want implicit children
import { forwardRef } from "react";
// Reuse native button props + your own
type BtnProps = React.ComponentProps<"button"> & { // Extend button props
    variant?: "primary" | "ghost"; // Button variant
};

export const Button = forwardRef<HTMLButtonElement, BtnProps>( // Forward ref to button element
    ({ variant = "primary", children, ...rest }, ref) => ( // Destructure props
        <button ref={ref} data-variant={variant} {...rest}> // Button element
            {children} // Button content
        </button>
    )
);
// Usage: <Button onClick={...}>Save</Button>

