
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/detail/wrap_python.hpp>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Mferror.h>

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MediaFoundation
{
public:
	void Init()
	{
		HRESULT hr = MFStartup(MF_VERSION);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("Media foundation startup failed");

		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("CoInitializeEx failed");
	}

	void DeInit()
	{
		MFShutdown();

		CoUninitialize();
	}	

	int EnumDevices(IMFAttributes **pAttributesOut, IMFActivate ***ppDevicesOut)
	{
		//Allocate memory to store devices
		*pAttributesOut = NULL;
		*ppDevicesOut = NULL;
		HRESULT hr = MFCreateAttributes(pAttributesOut, 1);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("MFCreateAttributes failed");

		hr = (*pAttributesOut)->SetGUID(
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
            );
		if(!SUCCEEDED(hr))
		{
			SafeRelease(pAttributesOut);
			throw std::runtime_error("SetGUID failed");
		}

		//Get list of devices from media foundation
		UINT32 count;
		hr = MFEnumDeviceSources(*pAttributesOut, ppDevicesOut, &count);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(pAttributesOut);
			throw std::runtime_error("MFEnumDeviceSources failed");
		}
		return count;
	}

	PyObject* ListDevices()
	{
		PyObject* out = PyList_New(0);
		IMFAttributes *pAttributes = NULL;
		IMFActivate **ppDevices = NULL;
		int count = EnumDevices(&pAttributes, &ppDevices);
		
		//For each device
		for(int i=0; i<count; i++)
		{
			IMFActivate *pActivate = ppDevices[i];
			wchar_t *vd_pFriendlyName = NULL;

			//Get friendly names for devices
			HRESULT hr = pActivate->GetAllocatedString(
				MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
				&vd_pFriendlyName,
				NULL
				);
			if(!SUCCEEDED(hr))
			{
				SafeRelease(&pAttributes);
				SafeRelease(ppDevices);
				CoTaskMemFree(vd_pFriendlyName);
				throw std::runtime_error("GetAllocatedString failed");
			}

			PyObject *pyStr = PyUnicode_FromWideChar(vd_pFriendlyName, wcslen(vd_pFriendlyName));
			PyList_Append(out, pyStr);

			CoTaskMemFree(vd_pFriendlyName);
		}

		SafeRelease(&pAttributes);
		SafeRelease(ppDevices);
		return out;
	}

	int ActivateDevice(int sourceNum)
	{
		IMFAttributes *pAttributes = NULL;
		IMFActivate **ppDevices = NULL;
		int count = EnumDevices(&pAttributes, &ppDevices);

		if (sourceNum >= count)
			throw std::runtime_error("Source does not exist");

		IMFActivate *pActivate = ppDevices[sourceNum];
		
		IMFMediaSource *pSource = NULL;
		HRESULT hr = pActivate->ActivateObject(
			__uuidof(IMFMediaSource),
			(void**)&pSource
			);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			SafeRelease(ppDevices);
			throw std::runtime_error("ActivateObject failed");
		}

		IMFSourceReader *ppSourceReader = NULL;
		hr = MFCreateSourceReaderFromMediaSource(pSource, pAttributes, &ppSourceReader);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pSource);
			SafeRelease(&pAttributes);
			SafeRelease(ppDevices);
			throw std::runtime_error("ActivateObject failed");
		}



		SafeRelease(&pSource);
		SafeRelease(&pAttributes);
		SafeRelease(ppDevices);
		SafeRelease(&ppSourceReader);
		return 0;
	}

};

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
		.def("ListDevices", &MediaFoundation::ListDevices)
		.def("ActivateDevice", &MediaFoundation::ActivateDevice)
	;
}
