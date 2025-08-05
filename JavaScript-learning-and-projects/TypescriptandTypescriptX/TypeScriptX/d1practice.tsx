// JSX in TSX files - in .tsx files, You can combine TypeScript with JSX syntax for React components. Props can be typed via interfaces or types.
interface ButtonProps {
    OnClick: () => void;
    label: string;
}
const Button = ({ OnClick, label }: ButtonProps) => (
    <button onClick={OnClick}>
        {label}
    </button>
);