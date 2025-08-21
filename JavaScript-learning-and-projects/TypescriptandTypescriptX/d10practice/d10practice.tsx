// Type-safe Reducers with Exhaustive Actions (React/TSX) - Make actions a discriminated union and force exhaustive handling- no silent fallthroughs
type State = { count: number }; // Defining state shape
type Action = 
| { type: "inc"; by?: number } // Increment the count
| { type: "dec"; by?: number } // Decrement the count
| { type: "reset" }; // Reset the count

function reducer(state: State, action: Action): State {
    switch(action.type) {
        case "inc":
            return { count: state.count + (action.by ?? 1) }; // Increment by action.by or default to 1
        case "dec":
            return { count: state.count - (action.by ?? 1) }; // Decrement by action.by or default to 1
        case "reset":
            return { count: 0 }; // Reset count to 0
        default:
            const _exhaustive: never = action; // Ensures all actions are handled
            return _exhaustive; // Fallback, should never be reached
    }
}

