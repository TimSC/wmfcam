
#include "pixbuff.h"
#include <iostream>
using namespace std;

void DecodeYuy2ToPilImage(PyObject *buff, int height, int width, int stride, PyObject* out)
{
	char* buffIn = PyByteArray_AsString(buff);
	Py_ssize_t lenIn = PyByteArray_Size(buff);

	char* buffOut = PyByteArray_AsString(out);
	Py_ssize_t lenOut = PyByteArray_Size(out);

	int hwidth = width/2;
    for(int lineNum=0; lineNum < height; lineNum++)
	{
        int lineOffset = lineNum * stride;
		int outOffset = lineNum * width * 3;
		
        for(int pxPairNum=0; pxPairNum < hwidth; pxPairNum++)
		{
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

			buffOut[outOffset + pxPairNum * 6] = R1;
			buffOut[outOffset + pxPairNum * 6 + 1] = G1;
			buffOut[outOffset + pxPairNum * 6 + 2] = B1;
			buffOut[outOffset + pxPairNum * 6 + 3] = R2;
			buffOut[outOffset + pxPairNum * 6 + 4] = G2;
			buffOut[outOffset + pxPairNum * 6 + 5] = B2;

		}

	}

	
}
