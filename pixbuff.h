
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>

void DecodeYuy2ToPilImage(PyByteArrayObject *buff, int height, int width, int stride, PyObject* out);
