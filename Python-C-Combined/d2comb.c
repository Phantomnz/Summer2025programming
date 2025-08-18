// Parse positional arguments with PyArg_ParseTuple - Handles C<->Python type conversion and parity checking in one line
// pretend this is its own file called mm_stats.c
#include <Python.h>

static PyObject* mm_stats(PyObject* self, PyObject* args) { // Function definition including argument parsing
    long n;
    double scale = 1.0; // default when not provided
    const char *label = "none";

    // formats: "l" long, "d" double, "s" UTF-8 char* "|" starts optionals
    if (!PyArg_ParseTuple(args, "l|ds", &n, &scale, &label)) { // if PyArg_ParseTuple fails
        return NULL; // Type error set by CPython on failure
    }
    double val = n * scale; // Perform computation
    return Py_BuildValue("(ds)", val, label); // Return a tuple with the result (double, string)
}

static PyMethodDef Methods[] = {
    {"stats", mm_stats, METH_VARARGS, "Compute scaled value with optional label"} // Function to compute statistics, METH_VARARGS means it accepts variable arguments and it packs them into a tuple, a constant but otherwise superior array
};
static struct PyModuleDef mod = { PyModuleDef_HEAD_INIT, "mm", NULL, -1, Methods }; // Module definition
PyMODINIT_FUNC PyInit_mm(void) { return PyModule_Create(&mod); }// Module initialization function
// Why: PyArg_ParseTuple converts Python objects to C types (and handles missing/extra args). The | indicates optional parameters.


// Support keyword arguments with PyArg_ParseTupleAndKeywords - Accepts **kwargs (kwargs is a dictionary of keyword arguments) in addition to positional args, with explicit names
static PyObject* mm_line(PyObject *self, PyObject *args, PyObject *kw) { // definition of a new function 
    static char *kwlist[] = {"x1", "y1", "x2", "y2", "name", NULL};
    double x1, y1, x2, y2;
    const char *name = "segment"; // default name

    // "dddd|s" means 4 doubles followed by an optional string
    if (!PyArg_ParseTupleAndKeywords(args, kw, "dddd|s", kwlist, &x1, &y1, &x2, &y2, &name)) {
        return NULL;
    } // if not all double arguments are received return NULL; error
    double length = hypot(x2 - x1, y2 - y1); // Calculate length of the line segment
    return Py_BuildValue("{s:d, s:d, s:d, s:d, s:d, s:s}", "x1", x1, "y1", y1, "x2", x2, "y2", y2, "name", name);
}

static PyMethodDef KWMethods[] = {
    {"line", (PyCFunction)mm_line, METH_VARARGS | METH_KEYWORDS, "Draw a line segment"}, // Function to draw a line segment, METH_VARARGS | METH_KEYWORDS means it accepts both positional and keyword arguments
    {NULL, NULL, 0, NULL} // Sentinel (sentinel means end of the array)
};
// Why: Keyword Parsing gives clear call sites in Python (line(x1=..., y1=..., x2=..., y2=..., name=...)) and robust argument handling in C


// Proper Error Reporting: set and propagate Python exceptions - Always return NULL on failure after an exception
static PyObject* mm_div(PyObject *self, PyObject *args) {
    long a,b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) return NULL; // Parse arguments, return NULL if parsing fails
    if (b==0) {
        PyErr_SetString(PyExc_ZeroDivisionError, "Division by zero");
        return NULL;
    }
    return PyLong_FromLong(a / b); // Return the result as a Python long object
}

// Map errno (meaning error number) (e.g., EINVAL, ENOMEM) from a failed C call:
static PyObject* mm_open(PyObject *self, PyObject *args) { // function declaration
    const char *path; 
    if (!PyArg_ParseTuple(args, "s", &path)) return NULL; // Parse the path argument
    FILE *f = fopen(path, "rb"); // Attempt to open the file
    if (!f) {
        PyErr_SetFromErrnoWithFilename(PyExc_OSError, path); // includes errno & filename
        return NULL;
    }
    fclose(f);
    Py_RETURN_TRUE;
}
// Why: Python relies on exceptions, not error codes. PyErr_Set* helpers attach rich context (including errno & filename) for callers

// Reference counters tracks how many pointers exist to each python object (memory management)
// incrementing reference counts allows one more object to be using the object and prevents garbage collection
// decrementing reference counts allows one less object to be using the object, and if the count reaches zero the object is deallocated

// Build and mutate Python containers from C - Use the new "*_New / *_Set" (steals references) and dict APIs
static PyObject* mm_dict(PyObject *self, PyObject *args) {
    long a,b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) return NULL; // Parse arguments
    
    PyObject *lst = PyList_New(0) // Create a list with 0 elements, NEW REF
    if (!lst) return NULL; // Check for memory allocation failure

    PyObject *tup = PyTuple_New(2); // Create a new tuple with 2 elements, NEW REF
    if (!tup) { Py_DECREF(lst); return NULL; } // Check for memory allocation failure, if discovered decrement reference count and return NULL

    // PyTuple_SET_ITEM steals a reference -> Do not DECREF after setting
    PyTuple_SetItem(tup, 0, PyLong_FromLong(a)); // Set first element, NEW -> Stolen
    PyTuple_SetItem(tup, 1, PyLong_FromLong(b)); // Set second element
    
    if (PyList_Append(lst, tup) < 0) { // Does INCREF internally
        Py_DECREF(tup); // decrement reference for tuple
        Py_DECREF(lst); // decrement reference for list
        return NULL;
    }
    Py_DECREF(tup); // balance our own new reference
    return lst; // return the new list [ (a, b) ]
}

static PyObject* mm_dict(PyObject *self, PyObject *args) {
    PyObject *d = PyDict_New(); // Create a new dictionary, NEW REF
    if (!d) return NULL; // Check for memory allocation failure
    if (PyDict_SetItemString(d, "pi", PyFloat_FromDouble(3.14159)) < 0) {
        Py_DECREF(d);
        return NULL;
    }
    return d; // Return the new dictionary {"pi": 3.14159}
}
// Why: Knowing which APIs steal vs. borrow references prevents memory leaks and crashes

// Accept "bytes-like" data via the buffer protocol (PyObject_GetBuffer) - Works with bytes, bytearray, memoryview, NumPy arrays (via PEP 3118), etc.
#include <structmember.h>
static PyObject* mm_sum_u8(PyObject *self, PyObject *args) { // Function declaration to sum 8-bit unsigned integers
    PyObject *obj;
    if (!PyArg_ParseTuple(args,"O", &obj)) return NULL; // Parse the input object
    Py_buffer view; // view for the buffer protocol
    if (PyObject_GetBuffer(obj, &view, PyBUF_SIMPLE) < 0) { // Get the buffer
        // TypeError set if object doesn't support the buffer protocol
        return NULL;
    }

    const unsigned char *p = (const unsigned char*)view.buf; // Cast buffer to unsigned char pointer
    Py_ssize_t len = view.len; // Get the length of the buffer
    unsigned long sum = 0; // Initialize sum
    for (Py_ssize_t i = 0; i < len; i++) { // Iterate over each byte
        sum += p[i]; // Accumulate byte values
    }
    PyBuffer_Release(&view); // Release the buffer
    return PyLong_FromUnsignedLong(sum); // Return the sum as a Python long object
}
// Why: The buffer protocol gives zero-copy access to raw memory owned by Python objects - vital for high performance I/O and numeric work