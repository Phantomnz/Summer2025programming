// Make your type hashable (consistent with equality) - If your object is immutable and defines equality, also define tp_hash. A common pattern is to hash a tuple of the fields used for equality.
// for Point (X, Y) assume equality compares (x, y)
static Py_hash_t Point_hash(PyObject *self_) {
    PointObject *self = (PointObject *)self_; // make sure to cast
    PyObject *t = Py_BuildValue("(dd)", self->x, self->y); // Create a tuple of (x, y), NEW REF
    if (!t) return -1; // Handle memory allocation failure
    Py_hash_t h = PyObject_Hash(t); // Compute the hash of the tuple
    Py_DECREF(t); // Decrease reference count
    return h; // Return the computed hash
}
// Hook it up with: PointType.tp_hash = Point_hash; in the type definition
// Why: Hashable objects can be dict keys/set elements. If your type is mutable, set tp_hash = PyObject_HashNotImplemented;

// Support the sequence protocol (len/indexing) - Expose your object as a short sequence; e.g., Point indexable as [0]=x, [1]=y
static Py_ssize_t Point_len(PyObject *self) { return 2; } // Length of the sequence (2 for Point)
static PyObject* Point_getitem(PyObject *self, Py_ssize_t i){
    PointObject *self = (PointObject *)self; // Cast to PointObject
    if (i == 0) return PyFloat_FromDouble(self->x); // Return x coordinate
    if (i == 1) return PyFloat_FromDouble(self->y); // Return y coordinate
    PyErr_SetString(PyExc_IndexError, "Index out of range"); // Set index error
    return NULL; // Return NULL for out of range index
}

static PySequenceMethods Point_as_sequence = {
    .sq_length = Point_len, // Length of the sequence
    .sq_item = Point_getitem, // Get item at index
    .sq_ass_item = Point_setitem, // Set item at index
};
// Hook it up with: PointType.tp_as_sequence = &Point_as_sequence; in the type definition
// Why: Implementing the sequence slots lets users do len(p) and p[0] and makes your type feel 'Pythonic'

// Implement the buffer protocol (zero-copy views) - for binary/numeric data, expose a contiguous buffer. Example: a dynamic vector of doubles
typedef struct {
    PyObject_HEAD
    double *data; // Pointer to the data buffer
    Py_ssize_t len; // Size of the buffer
} VecObject;

static int Vec_getbuffer(PyObject *self_, Py_buffer *view, int flags) {
    VecObject *self = (VecObject *)self_; // casting
    if (!view) return -1; // No view provided
    view->obj = self_; // Set the view's object
    view->buf = (void*)self->data; // Set the view's buffer
    view->len = self->len * (Py_ssize_t)sizeof(double); // Set the view's length
    view->readonly = 0; // Set the view's readonly flag
    view->itemsize = sizeof(double); // Set the view's item size
    view->ndim = 1; // Set the number of dimensions
    static Py_ssize_t shape[1], strides[1]; // setting shape and strides arrays
    shape[0] = self->len; // Set the shape
    strides[0] = sizeof(double); // Set the strides
    view->shape = shape; // Set the view's shape
    view->strides = strides; // Set the view's strides
    view->format = (flags & PyBUF_FORMAT) ? "<d" : NULL; // Set the view's format
    view->suboffsets = NULL; // No suboffsets
    Py_INCREF(self_); // Increase reference count for the object
    return 0;
}

static void Vec_releasebuffer(PyObject *self_, Py_buffer *view) {
    Py_DECREF(self_); // Decrease reference count for the object
}

static PyBufferProcs Vec_as_buffer = {
    .bf_getbuffer = Vec_getbuffer, // Get buffer
    .bf_releasebuffer = Vec_releasebuffer, // Release buffer
};
// Hook it up with: VecType.tp_as_buffer = &Vec_as_buffer; in the type definition
// VecType.tp_flags |= Py_TPFLAGS_DEFAULT; // Enable the buffer protocol
// Why: The buffer protocol enables zero-copy interop with memoryview, NumPy, and I/O -- critical for performance

// Enable pickling with __reduce__ - Return the constructor and its args so objects round-trip via pickle
static PyObject* Point_reduce(PyObject *self_) {
    PointObject *self = (PointObject *)self_; 
    // return (callable, args) -> Point (x, y)
    Py_INCREF((PyObject*)&PointType); // Increment reference count for the Point type
    return Py_BuildValue("(O(dd))", (PyObject*)&PointType, self->x, self->y); // Build the value
}

// Expose as a dunder method:
static PyMethodDef Point_methods[] = {
    {"__reduce__", (PyCFunction)Point_reduce, METH_NOARGS, "Return state for pickling"}, // Pickling support
    {NULL}  // Sentinel
}
// ensure: PointType.tp_methods = Point_methods;
// Why: With __reduce__, pickle.dumps(p)/pickle.loads(...) works out of the box -- handy for caching, multiprocessing, or IPC

// Modern Packaging (pyproject) & wheels - ship a proper wheel with no legacy setup.py invocations
// pyproject.toml goes in the root of your project (and on this line in the notes)
/*
Build and test in bash
python -m pip install -U build
python -m build            # creates sdist + wheel under dist/
python -m pip install dist/geom-0.1.0-*.whl
python - <<'PY'
from geom import Point
print(Point(1,2), len(Point(1,2)), Point(1,2)[0])
PY
*/
// Why: pyproject.toml is the current standard. Use build to create wheels; on Linux/macOS/Windows Cl you can produce platform wheels (e.g. manylinux) for easy installs