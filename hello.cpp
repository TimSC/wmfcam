
#include <stdexcept>
#include <iostream>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>

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

	void ListDevices()
	{
		//Allocate memory to store devices
		IMFAttributes *pAttributes = NULL;
		HRESULT hr = MFCreateAttributes(&pAttributes, 1);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("MFCreateAttributes failed");

		hr = pAttributes->SetGUID(
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
            );
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			throw std::runtime_error("SetGUID failed");
		}

		IMFActivate **ppDevices = NULL;
		UINT32 count;
		hr = MFEnumDeviceSources(pAttributes, &ppDevices, &count);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			throw std::runtime_error("MFEnumDeviceSources failed");
		}

		std::cout << "count" << count << std::endl;

		SafeRelease(&pAttributes);
	}

};

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
		.def("ListDevices", &MediaFoundation::ListDevices)
	;
}
