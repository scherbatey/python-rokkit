#include "rokkit_hash.h"

#include <stdio.h>
#include <Python.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define ERROR_MSG "Maximal input buffer size (" STR_HELPER(INT_MAX) ") is exceeded"

static_assert(sizeof(long long) > sizeof(int), "Unsupported int and long long sizes");

static PyObject * rokkit_hash_(PyObject * self, PyObject * args) {
    Py_buffer bytes;
    if (!PyArg_ParseTuple(args, "y*", &bytes))
        return NULL;
    if (bytes.len > INT_MAX) {
        PyErr_SetString(PyExc_ValueError, ERROR_MSG);
        return NULL;
    }
    uint32_t result = rokkit_hash(bytes.buf, (int)bytes.len);
    PyBuffer_Release(&bytes);
    return PyLong_FromLongLong(result);
}

static PyMethodDef Methods[] = {
    {"rokkit_hash",  rokkit_hash_, METH_VARARGS, "Calculates hash of bytes object."},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef Module = {
    PyModuleDef_HEAD_INIT,
    "rokkit_hash", //name of module
    NULL, // module documentation, may be NULL
    -1,   // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    Methods,
    NULL, // slots
    NULL, // traverse
    NULL, // clear
    NULL  // free
};

PyMODINIT_FUNC PyInit_rokkit_hash(void) {
   PyObject * m = PyModule_Create(&Module);
   return m;
}
