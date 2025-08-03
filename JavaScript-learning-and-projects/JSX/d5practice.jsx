// PropTypes for Runtime Type Checking - prop-types lets you specify expected prop types and requirements, warning in development if mismatches occur
import PropTypes from 'prop-types';
function User({ name, age}){
    return <p>{name} is {age} years old.</p>
}
User.propTypes = {
    name: PropTypes.string.isRequired,
    age: PropTypes.number.isRequired
};

// Context API for Global State - createContext and useContext share values (like theme) deeply without prop drilling
import { createContext, useContext } from 'react';
const ThemeContext = createContext('dark');
function ThemedButton() {
    const theme = useContext(ThemeContext);
    return <button className={theme}>I am {theme} themed!</button>;
}

// Lazy Loading Components with React.lazy - React.lazy with Suspense splits code, loading components on demand and show a fallback while loading
import React, { Suspense } from 'react';
const LazyComp = React.lazy(() => import('./HeavyComp'));
function App() {
    return (
        <Suspense fallback={<div>Loading...</div>}>
            <LazyComp />
        </Suspense>
    );
}
