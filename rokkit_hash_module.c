#include "SuperFastHash.h"

#include <stdio.h>
#include <Python.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define ERROR_MSG_BIG_BUFFER "Maximal input buffer size (" STR_HELPER(INT_MAX) ") is exceeded"
#define ERROR_MSG_BIG_SEED "Maximal seed value (" STR_HELPER(UINT_MAX) ") is exceeded"
#define ERROR_MSG_INVALID_TYPE "Seed value must be of unsigned int32 type"

static PyObject * rokkit_hash(PyObject * self, PyObject * args) {
    Py_buffer bytes;
    PyObject * seed_obj = Py_None;

    if (!PyArg_ParseTuple(args, "y* | O", &bytes, &seed_obj))
        return NULL;
    if (bytes.len > INT_MAX) {
        PyErr_SetString(PyExc_ValueError, ERROR_MSG_BIG_BUFFER);
        return NULL;    
    }

    unsigned long seed;

    if (seed_obj == Py_None) {
        seed = (unsigned long)bytes.len;
    } else {
        seed = PyLong_AsUnsignedLong(seed_obj);
        if (PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, ERROR_MSG_INVALID_TYPE);
            return NULL;
        }
        if (seed > UINT_MAX) {
            PyErr_SetString(PyExc_ValueError, ERROR_MSG_BIG_SEED);
            return NULL;
        }
    }

    uint32_t result = SuperFastHash(bytes.buf, (int)bytes.len, (uint32_t)seed);
    PyBuffer_Release(&bytes);
    return PyLong_FromUnsignedLong(result);
}

static PyMethodDef Methods[] = {
    {"rokkit_hash",  rokkit_hash, METH_VARARGS, "Calculates hash of bytes object."},
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
