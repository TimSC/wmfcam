
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Mferror.h>

class MediaFoundation
{
public:
	void Init()
	{
		HRESULT hr = MFStartup(MF_VERSION);

		CoInitializeEx(NULL, COINIT_MULTITHREADED);
	}

	void DeInit()
	{
		MFShutdown();

		CoUninitialize();
	}	
};

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
	;
}
