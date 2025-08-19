// In a normal project the following next 11 lines would be called point.c
// Define a heap-allocated custom type (Point) with PyTypeObject - create a C struct that embeds the python object header and your fields.
#include <Python.h>
#include <structmember.h>
#include <math.h>

typedef struct {
    PyObject_HEAD
    double x;
    double y;
} PointObject;
static PyTypeObject PointType; // forward declaration
// Why: PyObject_Head is mandatory; it allows the GC and runtime to manage your instances. Your fields (x, y) live directly in the object.

// Allocate and Initialize (tp_new/tp_init) - tp_new allocates the object; tp_init parses args and sets fields
static PyObject* Point_new(PyTypeObject* type, PyObject* args, PyObject* kwds) { //function declaration with parameters/pointers type, args, kwds
    PointObject* self = (PointObject*)type->tp_alloc(type, 0); // Allocate memory for the object
    if (!self) return NULL; // Check for allocation failure
    self->x = 0.0; // Initialize x
    self->y = 0.0; // Initialize y
    return (PyObject*)self; // Return the new object
}

static int Point_init(PointObject *self, PyObject *args, PyObject *kw){
    static char *kwlist[] = {"x", "y", NULL}; // Define keyword arguments
    double x = 0.0, y = 0.0; // Initialize x and y
    if (!PyArg_ParseTupleAndKeywords(args, kw, "|dd", kwlist, &x, &y))
        return -1; // Argument parsing failed
    self->x = x; // Set x coordinate
    self->y = y; // Set y coordinate
    return 0;
}
// Why: Splitting allocation and initialization mirrors Python's __new__ and __init__ methods and gives you finer control over defaults and validation.

// Lifetime and representation (tp_dealloc , tp_repr) - Provide a destructor and a helpful repr
static void Point_dealloc(PointObject* self) {
    Py_TYPE(self)->tp_free((PyObject*)self); // Free the object memory
}

static PyObject* Point_repr(PointObject* self) {
    return PyUnicode_FromFormat("Point(x=%f, y=%f)", self->x, self->y); // Return a string representation of the point
}
// Why: Properly freeing instances avoids leaks. A clear repr makes debugging pleasant. (it's what you see in the REPL)

// Expose Attributes safely (tp_members for raw fields, tp_getset for validation) -- Use PyMemberDef to expose simple C fields directly -- Use PyGetSetDef to validate or compute properties
// Direct field exposure (no validation):
static PyMemberDef Point_members[] = {
    {"x", T_DOUBLE, offsetof(PointObject, x), 0, "X coordinate"}, // x coordinate
    {"y", T_DOUBLE, offsetof(PointObject, y), 0, "Y coordinate"}, // y coordinate
    {NULL}  // Sentinel
};

// Derived/validated attribute via getters/setters:
static PyObject* Point_get_len(PointObject* self, void* closure) { // Getter for length
    double len = hypot(self->x, self->y); // Compute length using hypot
    return PyFloat_FromDouble(len); // Return length
}
static int Point_set_len(PointObject *self, PyObject *value, void *closure) {
    PyErr_SetString(PyExc_AttributeError, "Cannot set length directly"); // Prevent setting length
    return -1; // Indicate failure
}
static PyGetSetDef Point_getset[] = {
    {"length", (getter)Point_get_len, (setter)Point_set_len, "Length of the vector", NULL},
    {NULL}  // Sentinel
};
// Why: tp_members is the fastest way to expose plain fields; tp_getset lets you add computed properties or enforce rules

// Methods and operators (tp_methods and tp_as_number->nb_add) - Add instance methods and implement + between 2 Points
static PyObject* Point_scale(PointObject* self, PyObject* args) {
    double s;
    if (!PyArg_ParseTuple(args, "d", &s)) return NULL; // Parse the scale factor
    PointObject *out = (PointObject*)Py_TYPE(self)->tp_alloc(Py_TYPE(self), 0); // Allocate memory for the new Point
    if (!out) return NULL; // Check for allocation failure
    out->x = self->x * s; // Scale x coordinate
    out->y = self->y * s; // Scale y coordinate
    return (PyObject*)out; // Return the new scaled point
}

static PyMethodDef Point_methods[] = {
    {"scale", (PyCFunction)Point_scale, METH_VARARGS, "Return a scaled copy of the point"}, // Method to scale the point
    {NULL}  // Sentinel
};

// Support p + q
static PyObject* Point_add(PyObject* a, PyObject *b) {
    if (!PyObject_TypeCheck(a, &PointType) || !PyObject_TypeCheck(b, &PointType)) {
        PyErr_SetString(PyExc_TypeError, "Both operands must be Points"); // Ensure both operands are Points
        return NULL; // Return error
    }
    PointObject *pa = (PointObject*)a, *pb = (PointObject*)b; // Cast to PointObject
    PointObject *out = (PointObject*)PointType.tp_alloc(&PointType, 0); // Allocate memory for the new Point
    if (!out) return NULL; // Check for allocation failure
    out->x = pa->x + pb->x; // Add x coordinates
    out->y = pa->y + pb->y; // Add y coordinates
    return (PyObject*)out; // Return the new Point
}

static PyNumberMethods Point_as_number = {
    .nb_add = Point_add, // Implement addition
    .nb_subtract = NULL, // No subtraction implemented
    .nb_multiply = NULL, // No multiplication implemented
    .nb_remainder = NULL, // No remainder implemented
    .nb_divmod = NULL, // No divmod implemented
    .nb_power = NULL, // No power implemented
    .nb_negative = NULL, // No negation implemented
    .nb_positive = NULL, // No positive implemented
    .nb_absolute = NULL, // No absolute value implemented
    .nb_bool = NULL, // No boolean conversion implemented
    .nb_invert = NULL, // No inversion implemented
    .nb_lshift = NULL, // No left shift implemented
    .nb_rshift = NULL, // No right shift implemented
    .nb_and = NULL, // No bitwise AND implemented
    .nb_xor = NULL, // No bitwise XOR implemented
    .nb_or = NULL, // No bitwise OR implemented
};

static PyTypeObject PointType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "d3comb.Point", // Name of the type
    .tp_basicsize = sizeof(PointObject), // Size of the object
    .tp_itemsize = 0, // No item size
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, // Default flags with GC
    .tp_doc = "Point(x, y) - A 2D point", // Docstring
    .tp_new = Point_new, // tp_new function
    .tp_init = (initproc)Point_init, // tp_init function
    .tp_dealloc = (destructor)Point_dealloc, // tp_dealloc function
    .tp_repr = (reprfunc)Point_repr, // tp_repr function
    .tp_members = Point_members, // tp_members for direct field access
    .tp_getset = Point_getset, // tp_getset for computed properties
    .tp_methods = Point_methods, // tp_methods for instance methods
    .tp_as_number = &Point_as_number, // tp_as_number for operator overloading
};

// Module init: register the type
static PyModuleDef d3comb_mod = {
    PyModuleDef_HEAD_INIT, "d3comb", "day 3 combined (used as a geometry module)", -1, NULL, NULL, NULL, NULL, NULL // Definition of module d3comb for geometry
};

PyMODINIT_FUNC PyInit_d3comb(void) {
    if (PyType_Ready(&PointType) < 0) return NULL; // Initialize the Point type
    PyObject *m = PyModule_Create(&d3comb_mod); // Create the module
    if (!m) return NULL; // Check for creation failure
    Py_INCREF(&PointType); // Increment reference count
    if (PyModule_AddObject(m, (char*)"Point", (PyObject*)&PointType) < 0) { // Add Point type to module
        Py_DECREF(&PointType); // Decrement reference count for PointType
        Py_DECREF(m); // Decrement reference count for module
        return NULL;
    }
    return m; // Return the module
}
// Why: tp_methods exposes methods like scale() -- tp_as_number implements Python operators (+, -, *, /) -- PyType_Ready and PyModule_AddObject finalize registration so you can `from geom import Point`
