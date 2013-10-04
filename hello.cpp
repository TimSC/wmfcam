//  Copyright Joel de Guzman 2002-2004. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Mferror.h>

char const* greet()
{
   return "hello, world";
}

struct MediaFoundation
{
	void Init()
	{
		HRESULT hr = MFStartup(MF_VERSION);
	}

	void DeInit()
	{
		MFShutdown();
	}	
};

int test()
{
	HRESULT hr = MFStartup(MF_VERSION);
	return hr;
}

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
	def("greet", greet);
	def("test", test);

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
	;
}
