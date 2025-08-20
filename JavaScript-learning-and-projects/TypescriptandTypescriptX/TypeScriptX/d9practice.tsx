// TSX XOR props (mutually exclusive prop sets) - Enforce "link or button" behaviour at the type level
type AnchorProps = { as?: "a"; href: string; onClick?: never }; // Anchor props that can be used with an <a> element
type ButtonProps = { as?: "button"; href?: never; onClick: () => void }; // Button props that can be used with a <button> element
type Props = (AnchorProps | ButtonProps) & { children: React.ReactNode }; // Props for the component that can be either anchor or button props
function Action(p: Props) {
    const Comp = (p.as ?? (p as any).href ? "a":"button") as any; // Determine the component type based on props
    return <Comp {...p}>{p.children}</Comp>; // Render the component with the provided props
}
// <Action as="a" href="...">Link</Action> allowed
// <Action as="button" onClick={...}>Button</Action> allowed
// <Action href="/go" onClick={() => {}}>Both</Action> type error
