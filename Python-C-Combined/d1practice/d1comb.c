// Imagine this is embed.c
// Embed the Python interpreter in a C program
#include <Python.h>

int main(void) {
    Py_Initialize(); // Initialize the Python interpreter
    PyRun_SimpleString("print('Hello from embedded Python!')");
    PyRun_SimpleString("import math; print(math.sqrt(16))");
    Py_Finalize(); // Finalize the Python interpreter
    return 0;
}

// Why this matters: You can drive Python Code from C - handy for scripting, config, plugins, or using python libraries inside a native app

// Minimal C extension: expose a C function to Python; Why this matters: This is the "hello world" of Python-C extensions: parse Python args -> do fast native work -> return a Python object
// Pretend this is another C file called mymath.c
// #include <Python.h>
static PyObject* mm_add(PyObject *self, PyObject *args) { // Function to add two numbers
    long a, b; // Input numbers, long type is used for Python's int
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) {
        return NULL; // Error parsing arguments
    }
    return PyLong_FromLong(a + b); // Return the sum as a Python long object
}

static PyMethodDef MyMethods[] = {
    { "add", mm_add, METH_VARARGS, "Add two numbers" }, // Method definition
    { NULL, NULL, 0, NULL } // Sentinel
};

static struct PyModuleDef moduledef = {
    PyModuleDef_Head_INIT, "d1comb", "Minimal Math module for Python and here C", -1, MyMethods // Structure definition
};

PyMODINIT_FUNC PyInit_d1comb(void) {
    return PyModule_Create(&moduledef); // Module initialization function
}

// Reference Counting: own it, inc it, dec it
// returns a new reference
static PyObject* make_point(long x, long y) {
    PyObject *t = PyTuple_New(2); // Create a new tuple
    PyTuple_SetItem(t, 0, PyLong_FromLong(x)); // Set the first item
    PyTuple_SetItem(t, 1, PyLong_FromLong(y)); // Set the second item
    return t; // Return the new reference
}

// borrowing -> return safely
static PyObject* borrow_then_return(PyObject *obj) {
    // PyList_GET_ITEM returns a borrowed ref; never decref it directly
    PyObject *first = PyList_GET_ITEM(obj, 0); // Borrowed reference
    if (!first) return NULL; // Check for NULL
    Py_INCREF(first); // Increment the reference count, upgrade to NEW before returning
    return first; // Return the borrowed reference, caller owns 1 reference
}
// Rule of Thumb: Functions that create objects return new references -> caller must Py_DECREF() them
// "Borrowed" references (eg., from container accessors) must be Py_INCREF()ed before returning/storing them
// On every error path, DECREF anything you own before returning

// The GIL: When to release or acquire it - Long, blocking native work should release the GIL so other Python threads can run
static PyObject* mm_blocking(PyObject *self, PyObject *args) {
    int ms;
    if (!PyArg_ParseTuple(args, "i", &ms)) return NULL; // Error parsing arguments

    Py_BEGIN_ALLOW_THREADS; // Release the GIL
    // Simulate a long blocking operation
    #ifdef _WIN32
        Sleep(ms); // Sleep for ms milliseconds on Windows
    #else
        usleep(ms * 1000); // Sleep for ms milliseconds on Unix
    #endif
    Py_END_ALLOW_THREADS; // Reacquire the GIL

    Py_RETURN_NONE;
}
// If you embed Python and call into Python from a non-Python thread, use:
PyGILState_STATE st = PyGILState_Ensure();
// Call your Python code here
PyGILState_Release(st); 

// Why this matters: The Global Interpreter Lock protects Python objects. Releasing it around blocking C code improves concurrency. acquiring it is mandatory before touching Python objects from foreign threads.
