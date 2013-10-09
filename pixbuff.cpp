
#include "pixbuff.h"
#include <iostream>
using namespace std;

void DecodeYuy2ToPilImage(PyObject *buff, int height, int width, int stride, PyObject* out)
{
	char* buffIn = PyByteArray_AsString(buff);
	Py_ssize_t len = PyByteArray_Size(buff);
	int hwidth = width/2;
	PyObject* indexTuple = PyTuple_New(3);

	if(PySequence_Length(out) != height)
	{
		//TODO throw exception
	}

    for(int lineNum=0; lineNum < height; lineNum++)
	{
        int lineOffset = lineNum * stride;
		//PyTuple_SetItem(indexTuple, 0, lineNum);
		PyObject* lineOut = PySequence_GetItem(out, lineNum);

        for(int pxPairNum=0; pxPairNum < hwidth; pxPairNum++)
		{
			PyObject* pixelOut1 = PySequence_GetItem(lineOut, pxPairNum*2);
			PyObject* pixelOut2 = PySequence_GetItem(lineOut, pxPairNum*2+1);

            unsigned char Y1 = buffIn[pxPairNum * 4 + lineOffset];
            unsigned char Cb = buffIn[pxPairNum * 4 + lineOffset + 1];
            unsigned char Y2 = buffIn[pxPairNum * 4 + lineOffset + 2];
            unsigned char Cr = buffIn[pxPairNum * 4 + lineOffset + 3];

            //ITU-R BT.601 colour conversion
            double R1 = (Y1 + 1.402 * (Cr - 128));
            double G1 = (Y1 - 0.344 * (Cb - 128) - 0.714 * (Cr - 128));
            double B1 = (Y1 + 1.772 * (Cb - 128));
            double R2 = (Y2 + 1.402 * (Cr - 128));
            double G2 = (Y2 - 0.344 * (Cb - 128) - 0.714 * (Cr - 128));
            double B2 = (Y2 + 1.772 * (Cb - 128));

			PyObject *val1 = PyInt_FromLong(R1);
			PyObject *val2 = PyInt_FromLong(G1);
			PyObject *val3 = PyInt_FromLong(B1);
			PySequence_SetItem(pixelOut1, 0, val1);
			PySequence_SetItem(pixelOut1, 1, val2);
			PySequence_SetItem(pixelOut1, 2, val3);
			Py_CLEAR(val1);
			Py_CLEAR(val2);
			Py_CLEAR(val3);

			PyObject *val4 = PyInt_FromLong(R2);
			PyObject *val5 = PyInt_FromLong(G2);
			PyObject *val6 = PyInt_FromLong(B2);
			PySequence_SetItem(pixelOut2, 0, val4);
			PySequence_SetItem(pixelOut2, 1, val5);
			PySequence_SetItem(pixelOut2, 2, val6);
			Py_CLEAR(val4);
			Py_CLEAR(val5);
			Py_CLEAR(val6);
			
			Py_CLEAR(pixelOut1);
			Py_CLEAR(pixelOut2);
		}

		Py_CLEAR(lineOut);
	}

	PyTuple_ClearFreeList();
}
