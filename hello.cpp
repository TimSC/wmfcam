
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

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

typedef std::string StdString;
typedef std::wstring StdWString;
typedef std::vector<StdString> StdVectorOfStrings;
typedef std::vector<StdWString> StdVectorOfWStrings;

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

	StdVectorOfStrings ListDevices()
	{
		StdVectorOfStrings out;

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

		//Get list of devices from media foundation
		IMFActivate **ppDevices = NULL;
		UINT32 count;
		hr = MFEnumDeviceSources(pAttributes, &ppDevices, &count);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			throw std::runtime_error("MFEnumDeviceSources failed");
		}

		//For each device
		for(UINT32 i=0; i<count; i++)
		{
			IMFActivate *pActivate = ppDevices[i];
			wchar_t *vd_pFriendlyName = NULL;

			//Get friendly names for devices
			hr = pActivate->GetAllocatedString(
				MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
				&vd_pFriendlyName,
				NULL
				);
			
			//std::wcout << vd_pFriendlyName << std::endl;
			//std::wstring tmp(vd_pFriendlyName);
			//out.push_back(tmp);
			
			CoTaskMemFree(vd_pFriendlyName);

			/*IMFMediaSource *pSource = NULL;
			hr = pActivate->ActivateObject(
				__uuidof(IMFMediaSource),
				(void**)&pSource
				);

			SafeRelease(&pSource);*/

			//std::cout << vd_pFriendlyName << std::endl;
			
		}

		SafeRelease(&pAttributes);

		out.push_back("test");
		return out;
	}

};

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;

	class_<StdVectorOfStrings>("StdVectorOfStrings")
        .def(vector_indexing_suite<StdVectorOfStrings>() );

	class_<StdVectorOfWStrings>("StdVectorOfWStrings")
        .def(vector_indexing_suite<StdVectorOfWStrings>() );

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
		.def("ListDevices", &MediaFoundation::ListDevices)
	;
}
