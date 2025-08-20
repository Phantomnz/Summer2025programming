// Wrap Opaque C pointers with PyCapsule - Safely pass native pointers between python and C without exposing their layout
#include <Python.h>
#include <stdlib.h>
static void buf_capsule_destructor(PyObject *cap) {
    void *p = PyCapsule_GetPointer(cap, "buf"); // Get the pointer from the capsule
    free(p); // Free the malloc'd buffer when capsule is GC'd
}
static PyObject* make_buffer(PyObject *self, PyObject *args) {
    Py_ssize_t n = 0; // Buffer size
    if (!PyArg_ParseTuple(args, "n", &n)) return NULL; // Parse the buffer size from the arguments
    void *p = malloc((size_t)n); // Allocate memory for the buffer
    if (!p) return PyErr_NoMemory(); // Check for allocation failure
    return PyCapsule_New(p, "buf", buf_capsule_destructor); // Wrap the pointer in a capsule
}
static PyObject* use_buffer(PyObject *self, PyObject *args) {
    PyObject *cap; // Pointer for capsule
    if(!PyArg_ParseTuple(args, "O!", &PyCapsule_Type, &cap)) return NULL; // Parse the capsule from the arguments
    void *p = PyCapsule_GetPointer(cap, "buf"); // Get the pointer from the capsule
    if (!p) return NULL; // Check for capsule validity
    // Use the buffer...
    Py_RETURN_NONE; // Indicate successful usage
}
// Why: PyCapsule lets you share C pointers across extension boundaries with a name and optional destructor-- no leaks, no ABI peeking

// Own an external resource in a custom type (close in tp_dealloc) - Model a file handle owned by a Python object; guarantee cleanup
#include <stdio.h>
typedef struct { PyObject_HEAD FILE *f; } FObj; // File object structure
static void File_dealloc(FObj *self) {
    if (self->f) { fclose(self->f); self->f = NULL; } // Close the file if it is open
    Py_TYPE(self)->tp_free((PyObject*)self); // Free the object memory
}
static PyObject* File_readline(FObj *self, PyObject *Py_UNUSED(ignored)) { // Read a line from the file
    if (!self->f) { PyErr_SetString(PyExc_ValueError,"file closed"); return NULL; } // Check if the file is closed
    char buf[1024]; // Buffer for reading a line
    if (!fgets(buf, sizeof(buf), self->f)) Py_RETURN_NONE; // Read a line from the file
    return PyUnicode_FromString(buf); // Return the line as a Python string
}
static PyObject* file_open(PyObject *self, PyObject *args) {
    const char *path, *mode = "r"; // Default mode is read
    if (!PyArg_ParseTuple(args, "s|s", &path, &mode)) return NULL; // Parse the file path and mode
    FILE *fp = fopen(path, mode); // Open the file 
    if (!fp) return PyErr_SetFromErrnoWithFilename(PyExc_OSError, path); // check for any error numbers
    FObj *obj = PyObject_New(FObj, &FileType); // Create a new file object
    if (!obj) {
        fclose(fp); // If object creation fails, close the file and return NULL
        return NULL;
    }
    obj->f = fp; // Associate the file pointer with the file object
    return (PyObject*)obj; // Return the new file object
}
// Why: If a Python object owns a native handle, release it in tp_dealloc. This mirrors RAII and prevents descriptor and pointer leaks

// Implement rich comparisons (==, <, ...) in tp_richcompare - Extend the Point type from Day 3 (yesterdays file) to compare by coordinates (equality) and by vector length (ordering)
// assuming PointObject { double x, y; } and PointType from Day 3
static PyObject* Point_richcompare(PyObject *a, PyObject *b, int op) { 
    if (!PyObject_TypeCheck(a, &PointType) || !PyObject_TypeCheck(b, &PointType)) {
        Py_RETURN_NOTIMPLEMENTED; // Ensure both objects are of Point type
    }
    PointObject *pa = (PointObject*)a, *pb = (PointObject*)b; // Cast to PointObject
    int result = 0;
    if (op == Py_EQ)       result = (pa->x == pb->x) && (pa->y == pb->y); // Check for equality
    else if (op == Py_NE)  result = (pa->x != pb->x) || (pa->y != pb->y); // Check for inequality
    else {
        double la = hypot(pa->x, pa->y), lb = hypot(pb->x, pb->y); // Compute lengths
        if (op == Py_LT) result = la <  lb; // Check for less than
        else if (op == Py_LE) result = la <= lb; // Check for less than or equal
        else if (op == Py_GT) result = la >  lb; // Check for greater than
        else if (op == Py_GE) result = la >= lb; // Check for greater than or equal
        else { Py_RETURN_NOTIMPLEMENTED; }
    }
    if (result) Py_RETURN_TRUE; else Py_RETURN_FALSE; // Return the result as a Python boolean
}
// remember to set: PointType.tp_richcompare = Point_richcompare;
// Why: tp_richcompare gives you full control over Python's comparison operators; return NotImplemented for unsupported types

// Make your type iterable (define tp_iter/tp_iternext) - Iterate a Point as (x,y)
#include <structmember.h>
typedef struct {
    PyObject_HEAD // Required macro for all Python objects
    PointObject *owner; // Pointer to the PointObject
    int idx; // Current index in the iteration
} PointIter; // Iterator for PointObject

static void PointIter_dealloc(PointIter *it) {
    Py_XDECREF(it->owner); // Decrement reference count for owner
    Py_TYPE(it)->tp_free((PyObject*)it); // Free the iterator object
}
static PyObject* PointIter_iternext(PointIter *it) {
    if (it->idx==0) { it->idx++; return PyFloat_FromDouble(it->owner->x);} // Return x coordinate on first call
    else if (it->idx==1) { it->idx++; return PyFloat_FromDouble(it->owner->y);} // Return y coordinate on second call
    PyErr_SetNone(PyStopIteration);
    return NULL;
}
static PyTypeObject PointIterType = {
    PyVarObject_HEAD_INIT(&PointType, 0)
    .tp_name = "geom._PointIter", // Name of the iterator type
    .tp_basicsize = sizeof(PointIter), // Basic size of the iterator type
    .tp_dealloc = (destructor)PointIter_dealloc, // Deallocate the iterator
    .tp_iternext = (getnextfunc)PointIter_iternext, // Get the next item in the iteration
    .tp_flags = Py_TPFLAGS_DEFAULT, // Default flags for the iterator
    .tp_new = PyType_GenericNew, // Create a new instance of the iterator
}
static PyObject* Point_iter(PyObject *self) {
    PointIter *it = PyObject_New(PointIter, &PointIterType); // Create a new PointIter object
    if (!it) return NULL; // Check for allocation failure
    Py_INCREF(self); // Increment reference count for the owner
    it->owner = (PointObject*)self; // Set the owner to the current PointObject
    it->idx = 0; // Initialize the index
    return (PyObject*)it; // Return the new iterator object 
}
// remember to set: PointType.tp_iter = Point_iter;
// Why: Python's iterator protocol is just 2 slots: return an iterator (tp_iter) and yield next items until raising StopIteration

// Participate in Python's cyclic GC (tp_traverse/tp_clear) - For Container-like types that hold PyObjects, enable GC so cycles can be collected
// PairObject holds references to two arbitrary PyObjects
typedef struct {
    PyObject *c; // First object
    PyObject *d; // Second object
} PairObject;

static int Pair_traverse(PairObject *self, visitproc visit, void *arg) {
    Py_VISIT(self->c); // Visit the first object
    Py_VISIT(self->d); // Visit the second object
    return 0;
}
static int Pair_clear(PairObject *self) {
    Py_CLEAR(self->c); // Clear the first object
    Py_CLEAR(self->d); // Clear the second object
    return 0;
}
static void Pair_dealloc(PairObject *self) {
    PyObject_GC_UnTrack(self); // Stop GC tracking
    Pair_clear(self); // drop contained references
    Py_TYPE(self)->tp_free((PyObject*)self); // Free the PairObject
}
static PyObject* Pair_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PairObject *self = (PairObject*)type->tp_alloc(type, 0); // Allocate a new PairObject
    if (!self) return NULL; // Check for allocation failure
    self->c = NULL; // Initialize first object
    self->d = NULL; // Initialize second object
    PyObject_GC_Track(self); // Start GC tracking
    return (PyObject*)self; // Return the new PairObject
}
static PyTypeObject PairType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "geom._Pair", // Name of the Pair type
    .tp_basicsize = sizeof(PairObject), // Basic size of the Pair type
    .tp_dealloc = (destructor)Pair_dealloc, // Deallocate the PairObject
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, // Flags for the Pair type
    .tp_traverse = (traverseproc)Pair_traverse, // Traverse the PairObject
    .tp_clear = (inquiry)Pair_clear, // Clear the PairObject
}
