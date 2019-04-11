#include <Python.h>

// Function 1: A simple 'hello world' function
static PyObject* helloworld(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_None;
}

// Function 2: A C fibonacci implementation
// this is nothing special and looks exactly
// like a normal C version of fibonacci would look
int Cfib(int n)
{
    if (n < 2)
        return n;
    else
        return Cfib(n-1)+Cfib(n-2);
}
// Our Python binding to our C function
// This will take one and only one non-keyword argument
static PyObject* fib(PyObject* self, PyObject* args)
{
    // instantiate our `n` value
    int n;
    // if our `n` value
    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    // return our computed fib number
    return Py_BuildValue("i", Cfib(n));
}

uint64_t CCountByteDoubles(char * str) {
  uint64_t count = 0;
  while (str[0] && str[1]) {
    if (str[0] == str[1]) count++;
    str++;
  }
  return count;
}

static PyObject* count_byte_doubles(PyObject* self, PyObject* args)
{
    // instantiate our `n` value
    char *s;
    // if our `n` value
    if(!PyArg_ParseTuple(args, "s", &s))
        return NULL;

    // return our computed fib number
    return Py_BuildValue("i", CCountByteDoubles(s));
}

// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
    { "helloworld", helloworld, METH_NOARGS, "Prints Hello World" },
    { "fib", fib, METH_VARARGS, "Calculates fibonacci of number" },
    { "count_byte_doubles", count_byte_doubles, METH_VARARGS, "Count byte Doubles" },
    { NULL, NULL, 0, NULL }
};

// Our Module Definition struct
static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "mylibcpython",
    "Test Module",
    -1,
    myMethods
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_mylibcpython(void)
{
    return PyModule_Create(&myModule);
}
