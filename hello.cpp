
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


#ifndef IF_EQUAL_RETURN
#define IF_EQUAL_RETURN(param, val) if(val == param) return L#val
#endif

LPCWSTR GetGUIDNameConst(const GUID& guid)
{
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ee663602%28v=vs.85%29.aspx
    IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_SUBTYPE);
    IF_EQUAL_RETURN(guid, MF_MT_ALL_SAMPLES_INDEPENDENT);
    IF_EQUAL_RETURN(guid, MF_MT_FIXED_SIZE_SAMPLES);
    IF_EQUAL_RETURN(guid, MF_MT_COMPRESSED);
    IF_EQUAL_RETURN(guid, MF_MT_SAMPLE_SIZE);
    IF_EQUAL_RETURN(guid, MF_MT_WRAPPED_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_NUM_CHANNELS);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FLOAT_SAMPLES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_AVG_BYTES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BLOCK_ALIGNMENT);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BITS_PER_SAMPLE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_VALID_BITS_PER_SAMPLE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_BLOCK);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_CHANNEL_MASK);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FOLDDOWN_MATRIX);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKREF);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKTARGET);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGREF);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGTARGET);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_PREFER_WAVEFORMATEX);
    IF_EQUAL_RETURN(guid, MF_MT_AAC_PAYLOAD_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_SIZE);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MAX);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MIN);
    IF_EQUAL_RETURN(guid, MF_MT_PIXEL_ASPECT_RATIO);
    IF_EQUAL_RETURN(guid, MF_MT_DRM_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_PAD_CONTROL_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_SOURCE_CONTENT_HINT);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_CHROMA_SITING);
    IF_EQUAL_RETURN(guid, MF_MT_INTERLACE_MODE);
    IF_EQUAL_RETURN(guid, MF_MT_TRANSFER_FUNCTION);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_PRIMARIES);
    IF_EQUAL_RETURN(guid, MF_MT_CUSTOM_VIDEO_PRIMARIES);
    IF_EQUAL_RETURN(guid, MF_MT_YUV_MATRIX);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_LIGHTING);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_NOMINAL_RANGE);
    IF_EQUAL_RETURN(guid, MF_MT_GEOMETRIC_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_MINIMUM_DISPLAY_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_ENABLED);
    IF_EQUAL_RETURN(guid, MF_MT_AVG_BITRATE);
    IF_EQUAL_RETURN(guid, MF_MT_AVG_BIT_ERROR_RATE);
    IF_EQUAL_RETURN(guid, MF_MT_MAX_KEYFRAME_SPACING);
    IF_EQUAL_RETURN(guid, MF_MT_DEFAULT_STRIDE);
    IF_EQUAL_RETURN(guid, MF_MT_PALETTE);
    IF_EQUAL_RETURN(guid, MF_MT_USER_DATA);
    IF_EQUAL_RETURN(guid, MF_MT_AM_FORMAT_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG_START_TIME_CODE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_PROFILE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_LEVEL);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG_SEQUENCE_HEADER);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_0);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_0);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_1);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_1);
    IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_SRC_PACK);
    IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_CTRL_PACK);
    IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_HEADER);
    IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_FORMAT);
    IF_EQUAL_RETURN(guid, MF_MT_IMAGE_LOSS_TOLERANT); 
    IF_EQUAL_RETURN(guid, MF_MT_MPEG4_SAMPLE_DESCRIPTION);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG4_CURRENT_SAMPLE_ENTRY);
    IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_4CC); 
    IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_WAVE_FORMAT_TAG);
    
    // Media types

    IF_EQUAL_RETURN(guid, MFMediaType_Audio);
    IF_EQUAL_RETURN(guid, MFMediaType_Video);
    IF_EQUAL_RETURN(guid, MFMediaType_Protected);
    IF_EQUAL_RETURN(guid, MFMediaType_SAMI);
    IF_EQUAL_RETURN(guid, MFMediaType_Script);
    IF_EQUAL_RETURN(guid, MFMediaType_Image);
    IF_EQUAL_RETURN(guid, MFMediaType_HTML);
    IF_EQUAL_RETURN(guid, MFMediaType_Binary);
    IF_EQUAL_RETURN(guid, MFMediaType_FileTransfer);

    IF_EQUAL_RETURN(guid, MFVideoFormat_AI44); //     FCC('AI44')
    IF_EQUAL_RETURN(guid, MFVideoFormat_ARGB32); //   D3DFMT_A8R8G8B8 
    IF_EQUAL_RETURN(guid, MFVideoFormat_AYUV); //     FCC('AYUV')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DV25); //     FCC('dv25')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DV50); //     FCC('dv50')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVH1); //     FCC('dvh1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVSD); //     FCC('dvsd')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVSL); //     FCC('dvsl')
    IF_EQUAL_RETURN(guid, MFVideoFormat_H264); //     FCC('H264')
    IF_EQUAL_RETURN(guid, MFVideoFormat_I420); //     FCC('I420')
    IF_EQUAL_RETURN(guid, MFVideoFormat_IYUV); //     FCC('IYUV')
    IF_EQUAL_RETURN(guid, MFVideoFormat_M4S2); //     FCC('M4S2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MJPG);
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP43); //     FCC('MP43')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP4S); //     FCC('MP4S')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP4V); //     FCC('MP4V')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MPG1); //     FCC('MPG1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MSS1); //     FCC('MSS1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MSS2); //     FCC('MSS2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_NV11); //     FCC('NV11')
    IF_EQUAL_RETURN(guid, MFVideoFormat_NV12); //     FCC('NV12')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P010); //     FCC('P010')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P016); //     FCC('P016')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P210); //     FCC('P210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P216); //     FCC('P216')
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB24); //    D3DFMT_R8G8B8 
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB32); //    D3DFMT_X8R8G8B8 
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB555); //   D3DFMT_X1R5G5B5 
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB565); //   D3DFMT_R5G6B5 
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB8);
    IF_EQUAL_RETURN(guid, MFVideoFormat_UYVY); //     FCC('UYVY')
    IF_EQUAL_RETURN(guid, MFVideoFormat_v210); //     FCC('v210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_v410); //     FCC('v410')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV1); //     FCC('WMV1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV2); //     FCC('WMV2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV3); //     FCC('WMV3')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WVC1); //     FCC('WVC1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y210); //     FCC('Y210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y216); //     FCC('Y216')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y410); //     FCC('Y410')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y416); //     FCC('Y416')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y41P);
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y41T);
    IF_EQUAL_RETURN(guid, MFVideoFormat_YUY2); //     FCC('YUY2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_YV12); //     FCC('YV12')
    IF_EQUAL_RETURN(guid, MFVideoFormat_YVYU);

    IF_EQUAL_RETURN(guid, MFAudioFormat_PCM); //              WAVE_FORMAT_PCM 
    IF_EQUAL_RETURN(guid, MFAudioFormat_Float); //            WAVE_FORMAT_IEEE_FLOAT 
    IF_EQUAL_RETURN(guid, MFAudioFormat_DTS); //              WAVE_FORMAT_DTS 
    IF_EQUAL_RETURN(guid, MFAudioFormat_Dolby_AC3_SPDIF); //  WAVE_FORMAT_DOLBY_AC3_SPDIF 
    IF_EQUAL_RETURN(guid, MFAudioFormat_DRM); //              WAVE_FORMAT_DRM 
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV8); //        WAVE_FORMAT_WMAUDIO2 
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV9); //        WAVE_FORMAT_WMAUDIO3 
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudio_Lossless); // WAVE_FORMAT_WMAUDIO_LOSSLESS 
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMASPDIF); //         WAVE_FORMAT_WMASPDIF 
    IF_EQUAL_RETURN(guid, MFAudioFormat_MSP1); //             WAVE_FORMAT_WMAVOICE9 
    IF_EQUAL_RETURN(guid, MFAudioFormat_MP3); //              WAVE_FORMAT_MPEGLAYER3 
    IF_EQUAL_RETURN(guid, MFAudioFormat_MPEG); //             WAVE_FORMAT_MPEG 
    IF_EQUAL_RETURN(guid, MFAudioFormat_AAC); //              WAVE_FORMAT_MPEG_HEAAC 
    IF_EQUAL_RETURN(guid, MFAudioFormat_ADTS); //             WAVE_FORMAT_MPEG_ADTS_AAC 

    return NULL;
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

	void ParseFormat(IMFMediaType *pType, int index)
	{
		GUID guid = { 0 };

	    PROPVARIANT var;
		PropVariantInit(&var);
		HRESULT hr = pType->GetItemByIndex(index, &guid, &var);

		LPCWSTR pcwsz1 = GetGUIDNameConst(guid);
		LPCWSTR pcwsz2 = NULL;
		ULARGE_INTEGER iuval2;
		iuval2.LowPart = 0;
		iuval2.HighPart = 0;
		int iuval2Set = 0;

		switch (var.vt)
        {
        case VT_UI4:
			iuval2.LowPart = var.ulVal;
			iuval2Set = 1;
            break;

        case VT_UI8:
			iuval2 = var.uhVal;
			iuval2Set = 1;
            break;

        case VT_R8:
            break;

        case VT_CLSID:
			cout << "VT_CLSID" << endl;
			pcwsz2 = GetGUIDNameConst(*var.puuid);
			cout << (long) pcwsz2 << endl;
			if (pcwsz2 == NULL)
			{
				LPOLESTR *lplpsz;
				StringFromCLSID(*pcwsz2, lplpsz);
				cout << lplpsz << endl;
				CoTaskMemFree(lplpsz);
			}

            break;

        case VT_LPWSTR:

            break;

        case VT_VECTOR | VT_UI1:
          
            break;

        case VT_UNKNOWN:
           
            break;

        default:
          
            break;
        }

		if (pcwsz1!=NULL)
			wcout << pcwsz1 << ", ";
		else
			wcout << "guid, ";


		if (pcwsz2!=NULL)
			wcout << pcwsz2;
		if (iuval2Set)
			cout << iuval2.HighPart<< ";" << iuval2.LowPart;
		cout << endl;

		//SafeRelease(&pPD);
		//SafeRelease(&pSD);
		//SafeRelease(&pHandler);
		PropVariantClear(&var);
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

		
		//Emumerate types
		IMFPresentationDescriptor *pPD = NULL;
		hr = pSource->CreatePresentationDescriptor(&pPD);
		BOOL fSelected;
		IMFStreamDescriptor *pSD = NULL;
		hr = pPD->GetStreamDescriptorByIndex(0, &fSelected, &pSD);
		IMFMediaTypeHandler *pHandler = NULL;
		hr = pSD->GetMediaTypeHandler(&pHandler);
		DWORD cTypes = 0;
		hr = pHandler->GetMediaTypeCount(&cTypes);
		for (DWORD i = 0; i < cTypes; i++)
		{
			IMFMediaType *pType = NULL;
			hr = pHandler->GetMediaTypeByIndex(i, &pType);
			
			UINT32 count = 0;
			hr = pType->LockStore();
			hr = pType->GetCount(&count);
			for(UINT32 j=0; j<count; j++)
			{
				cout << i << "," << j << endl;
				this->ParseFormat(pType, j);
			}
			hr = pType->UnlockStore();

			SafeRelease(&pType);

		}
		SafeRelease(&pPD);
		SafeRelease(&pSD);
		SafeRelease(&pHandler);

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
