
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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
#include <Shlwapi.h>

#include "pixbuff.h"

#define MAX_DEVICE_ID_LEN 100

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

void PrintGuid(GUID guid)
{
	LPOLESTR lplpsz;
	StringFromCLSID(guid, &lplpsz);
	wcout << lplpsz << endl;
	CoTaskMemFree(lplpsz);
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

	//IF_EQUAL_RETURN(guid, FORMAT_VideoInfo); //Dshow dependent
	//IF_EQUAL_RETURN(guid, FORMAT_VideoInfo2);
    
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

HRESULT GetDefaultStride(IMFMediaType *pType, LONG *plStride)
{
	LONG lStride = 0;

	// Try to get the default stride from the media type.
	HRESULT hr = pType->GetUINT32(MF_MT_DEFAULT_STRIDE, (UINT32*)&lStride);

	if (FAILED(hr))
	{
		// Attribute not set. Try to calculate the default stride.

		GUID subtype = GUID_NULL;

		UINT32 width = 0;
		UINT32 height = 0;
		// Get the subtype and the image size.
		hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);
		if (FAILED(hr))
		{
			goto done;
		}
		hr = MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &width, &height);
		if (FAILED(hr))
		{
			goto done;
		}
		hr = MFGetStrideForBitmapInfoHeader(subtype.Data1, width, &lStride);
		if (FAILED(hr))
		{
			goto done;
		}

		// Set the attribute for later reference.
		(void)pType->SetUINT32(MF_MT_DEFAULT_STRIDE, UINT32(lStride));
	}

	if (SUCCEEDED(hr))
	{
		*plStride = lStride;
	}

done:
	return hr;
}

DWORD SampleToStaticObj(IMFSample *pSample, char **buff)
{
	if(*buff!=NULL)
		throw runtime_error("Buff ptr should be initially null");
	IMFMediaBuffer *ppBuffer = NULL;
	HRESULT hr = pSample->ConvertToContiguousBuffer(&ppBuffer);
	//cout << "ConvertToContiguousBuffer=" << SUCCEEDED(hr) << "\tstride="<< plStride << "\n";

	IMF2DBuffer *m_p2DBuffer = NULL;
	ppBuffer->QueryInterface(IID_IMF2DBuffer, (void**)&m_p2DBuffer);
	//cout << "IMF2DBuffer=" << (m_p2DBuffer != NULL) << "\n";

	DWORD pcbCurrentLength = 0;
	BYTE *ppbBuffer = NULL;
	DWORD pcbMaxLength = 0;

	if(SUCCEEDED(hr))
	{
		
		hr = ppBuffer->Lock(&ppbBuffer, &pcbMaxLength, &pcbCurrentLength);
		//cout << "pcbMaxLength="<< pcbMaxLength << "\tpcbCurrentLength=" <<pcbCurrentLength << "\n";

		//Return buffer as python format data
		*buff = new char[pcbCurrentLength];
		memcpy(*buff, ppbBuffer, pcbCurrentLength);

		ppBuffer->Unlock();
	}

	if(ppBuffer) ppBuffer->Release();
	return pcbCurrentLength;
}

PyObject* StaticObjToPythonObj(IMFSourceReader *pReader, 
	DWORD streamIndex, 
	DWORD flags, 
	LONGLONG llTimeStamp, 
	char *frame, DWORD buffLen)
{
	UINT32 width = 0;
	UINT32 height = 0;
	PyObject* out = PyDict_New();

	if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
	{
		PyDict_SetItemString(out, "end", PyInt_FromLong(1));
		return out;
	}
	else
		PyDict_SetItemString(out, "end", PyInt_FromLong(0));
	PyDict_SetItemString(out, "streamIndex", PyInt_FromLong(streamIndex));

	if (flags & MF_SOURCE_READERF_NEWSTREAM)
	{
	}
	if (flags & MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED)
	{
	}
	if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
	{
	}
	if (flags & MF_SOURCE_READERF_STREAMTICK)
	{
	}
	if (flags & MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED)
	{
	}

	if (frame!=NULL && buffLen > 0)
	{
		//PyDict_SetItemString(out, "isCompressed", PyBool_FromLong(isComp));
		PyObject* buff = PyByteArray_FromStringAndSize((const char *)frame, buffLen);
		PyDict_SetItemString(out, "buff", buff);
		//const WCHAR *typePtr = L"MFMediaType_Video";
		//const WCHAR *subTypePtr = L"MFVideoFormat_YUY2";
		//if(typePtr!=NULL) PyDict_SetItemString(out, "type", PyUnicode_FromWideChar(typePtr, wcslen(typePtr)));
		//if(subTypePtr!=NULL) PyDict_SetItemString(out, "subtype", PyUnicode_FromWideChar(subTypePtr, wcslen(subTypePtr)));

		//if(!isComp) PyDict_SetItemString(out, "stride", PyInt_FromLong(plStride));
		//PyDict_SetItemString(out, "width", PyInt_FromLong(width));
		//PyDict_SetItemString(out, "height", PyInt_FromLong(height));

		PyDict_SetItemString(out, "timestamp", PyLong_FromLongLong(llTimeStamp));
	}

	return out;
}


class SourceReaderCB : public IMFSourceReaderCallback
{
	//http://msdn.microsoft.com/en-us/library/windows/desktop/gg583871%28v=vs.85%29.aspx
public:
	LONG volatile m_nRefCount;
	CRITICAL_SECTION lock;
	int framePending;
	unsigned int maxNumFrames;

	vector<char *> frameBuff;
	vector<DWORD> frameLenBuff;
	vector<HRESULT> hrStatusBuff;
	vector<DWORD> dwStreamIndexBuff;
    vector<DWORD> dwStreamFlagsBuff;
	vector<LONGLONG> llTimestampBuff;
	
	SourceReaderCB()
	{
		m_nRefCount = 0;
		framePending = 0;
		InitializeCriticalSection(&lock);
		maxNumFrames = 10;
	}

	virtual ~SourceReaderCB()
	{
		 DeleteCriticalSection(&lock);
		 for(unsigned int i=0; i<this->frameBuff.size(); i++)
			 delete [] this->frameBuff[i];
	}

	STDMETHODIMP QueryInterface(REFIID iid, void** ppv)
	{
		static const QITAB qit[] =
        {
            QITABENT(SourceReaderCB, IMFSourceReaderCallback),
            { 0 },
        };
        return QISearch(this, qit, iid, ppv);
	}

    STDMETHODIMP OnReadSample(HRESULT hrStatus, DWORD dwStreamIndex,
        DWORD dwStreamFlags, LONGLONG llTimestamp, IMFSample *pSample)
	{
		//cout << "OnReadSample: " << llTimestamp << endl;
		EnterCriticalSection(&lock);

		if (pSample && this->frameBuff.size() < this->maxNumFrames)
		{
			char *buff = NULL;
			DWORD buffLen = SampleToStaticObj(pSample, &buff);
			//cout << (long) buff << "," << buffLen << endl;
			//if(buff!=NULL) delete [] buff;

			frameBuff.push_back(buff);
			frameLenBuff.push_back(buffLen);
			hrStatusBuff.push_back(hrStatus);
			dwStreamIndexBuff.push_back(dwStreamIndex);
			dwStreamFlagsBuff.push_back(dwStreamFlags);
			llTimestampBuff.push_back(llTimestamp);
		}

		this->framePending = 0;
		LeaveCriticalSection(&lock);
		return S_OK;
	}

	STDMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&m_nRefCount);
	}

    STDMETHODIMP_(ULONG) Release()
	{
		ULONG uCount = InterlockedDecrement(&m_nRefCount);
        if (uCount == 0)
        {
			cout << "self destruct" << endl;
            delete this;
        }
        return uCount;
	}

	STDMETHODIMP OnEvent(DWORD, IMFMediaEvent *)
	{
		return S_OK;
	}

    STDMETHODIMP OnFlush(DWORD)
	{
		return S_OK;
	}

	void SetPending()
	{
		EnterCriticalSection(&lock);
		this->framePending = 1;
		LeaveCriticalSection(&lock);
	}

	int GetPending()
	{
		EnterCriticalSection(&lock);
		int pendingCopy = this->framePending;
		LeaveCriticalSection(&lock);
		return pendingCopy;
	}

	void WaitForFrame()
    {
		while(1)
		{
			EnterCriticalSection(&lock);
			int pendingCopy = this->framePending;
			LeaveCriticalSection(&lock);
			if (!pendingCopy) return;
			Sleep(10);
		}
    }

	int GetFrame(HRESULT *hrStatus, DWORD *dwStreamIndex,
        DWORD *dwStreamFlags, LONGLONG *llTimestamp, char **frame, DWORD *buffLen)
	{
		int ret = 0;
		*hrStatus = S_OK;
		*dwStreamIndex = 0;
		*dwStreamFlags = 0;
		*llTimestamp = 0;
		*frame = NULL;
		*buffLen = 0;

		EnterCriticalSection(&lock);
		if(this->frameBuff.size()>0)
		{
			*frame = frameBuff[0];
			*buffLen = frameLenBuff[0];
			*hrStatus = hrStatusBuff[0];
			*dwStreamIndex = dwStreamIndexBuff[0];
			*dwStreamFlags = dwStreamFlagsBuff[0];
			*llTimestamp = llTimestampBuff[0];

			this->frameBuff.erase(this->frameBuff.begin());
			this->frameLenBuff.erase(this->frameLenBuff.begin());
			this->hrStatusBuff.erase(this->hrStatusBuff.begin());
			this->dwStreamIndexBuff.erase(this->dwStreamIndexBuff.begin());
			this->dwStreamFlagsBuff.erase(this->dwStreamFlagsBuff.begin());
			this->llTimestampBuff.erase(this->llTimestampBuff.begin());
			ret = 1;
		}
		LeaveCriticalSection(&lock);
		return ret;
	}
   
};

class MediaFoundation
{
protected:
	map<wstring, IMFSourceReader*> readerList;
	map<wstring, IMFMediaSource*> sourceList;
	int initDone;
	map<wstring, int> asyncMode;
	map<wstring, SourceReaderCB*> readerCallbacks;

public:
	MediaFoundation()
	{
		this->initDone = false;
	}

	virtual ~MediaFoundation()
	{

	}

	void Init()
	{
		if(this->initDone)
			throw runtime_error("Media Foundation init already done");

		HRESULT hr = MFStartup(MF_VERSION);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("Media foundation startup failed");

		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("CoInitializeEx failed");

		this->initDone = true;
	}

	void DeInit()
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		for(map<wstring, IMFSourceReader*>::iterator it = readerList.begin(); it!=readerList.end(); it++)
			SafeRelease(&it->second);
		for(map<wstring, IMFMediaSource*>::iterator it = sourceList.begin(); it!=sourceList.end(); it++)
			SafeRelease(&it->second);

		//Remove reader callback
		//for(map<wstring, SourceReaderCB*>::iterator it = readerCallbacks.begin(); it!=readerCallbacks.end(); it++)
		//	this->readerCallbacks.erase(it);

		MFShutdown();

		CoUninitialize();

		this->initDone = false;
	}	

	int EnumDevices(IMFActivate ***ppDevicesOut)
	{
		
		//Warning: the result from this function must be manually freed!

		//Allocate memory to store devices
		IMFAttributes *pAttributes = NULL;
		*ppDevicesOut = NULL;
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
		UINT32 count;
		hr = MFEnumDeviceSources(pAttributes, ppDevicesOut, &count);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			throw std::runtime_error("MFEnumDeviceSources failed");
		}

		SafeRelease(&pAttributes);
		return count;
	}

	PyObject* ListDevices()
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		PyObject* out = PyList_New(0);
		IMFActivate **ppDevices = NULL;
		int count = EnumDevices(&ppDevices);
		
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
				SafeRelease(ppDevices);
				CoTaskMemFree(vd_pFriendlyName);
				throw std::runtime_error("GetAllocatedString failed");
			}

			wchar_t *symbolicLink = NULL;
			hr = pActivate->GetAllocatedString(
				MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK,
				&symbolicLink,
				NULL
				);
			if(!SUCCEEDED(hr))
			{
				SafeRelease(ppDevices);
				CoTaskMemFree(vd_pFriendlyName);
				CoTaskMemFree(symbolicLink);
				throw std::runtime_error("GetAllocatedString failed");
			}

			PyObject *deviceTuple = PyTuple_New(2);
			PyTuple_SetItem(deviceTuple, 0, PyUnicode_FromWideChar(vd_pFriendlyName, wcslen(vd_pFriendlyName)));
			PyTuple_SetItem(deviceTuple, 1, PyUnicode_FromWideChar(symbolicLink, wcslen(symbolicLink)));
			PyList_Append(out, deviceTuple);

			CoTaskMemFree(vd_pFriendlyName);
			CoTaskMemFree(symbolicLink);
		}

		SafeRelease(ppDevices);
		return out;
	}

	void ParseFormat(IMFMediaType *pType, int index, PyObject *metaDataOut)
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
		int ui4 = 0, ui4set = 0;

		switch (var.vt)
        {
        case VT_UI4:
			ui4 = var.ulVal;
			ui4set = 1;
            break;

        case VT_UI8:
			iuval2 = var.uhVal;
			iuval2Set = 1;
            break;

        case VT_R8:
            break;

        case VT_CLSID:
			pcwsz2 = GetGUIDNameConst(*var.puuid);
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
		{
			if (pcwsz2!=NULL)
				PyDict_SetItem(metaDataOut, 
					PyUnicode_FromWideChar(pcwsz1, wcslen(pcwsz1)), 
					PyUnicode_FromWideChar(pcwsz2, wcslen(pcwsz2)));

			if (iuval2Set)
			{
				PyObject *tup = PyTuple_New(2);
				PyTuple_SetItem(tup, 0, PyInt_FromLong(iuval2.LowPart));
				PyTuple_SetItem(tup, 1, PyInt_FromLong(iuval2.HighPart));
				PyDict_SetItem(metaDataOut, 
					PyUnicode_FromWideChar(pcwsz1, wcslen(pcwsz1)), 
					tup);
			}

			if (ui4set)
				PyDict_SetItem(metaDataOut, 
					PyUnicode_FromWideChar(pcwsz1, wcslen(pcwsz1)), 
					PyInt_FromLong(ui4));
		}

		PropVariantClear(&var);
	}

	PyObject *EnumerateMediaTypes(PyObject *sourceId)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		PyObject *out = PyList_New(0);
		IMFMediaSource *pSource = this->GetSource(sourceId);

		//Emumerate types
		IMFPresentationDescriptor *pPD = NULL;
		HRESULT hr = pSource->CreatePresentationDescriptor(&pPD);
		BOOL fSelected;
		IMFStreamDescriptor *pSD = NULL;
		hr = pPD->GetStreamDescriptorByIndex(0, &fSelected, &pSD);
		IMFMediaTypeHandler *pHandler = NULL;
		hr = pSD->GetMediaTypeHandler(&pHandler);
		DWORD cTypes = 0;
		hr = pHandler->GetMediaTypeCount(&cTypes);
		for (DWORD i = 0; i < cTypes; i++)
		{
			PyObject *metaDataOut = PyDict_New();
			IMFMediaType *pType = NULL;
			hr = pHandler->GetMediaTypeByIndex(i, &pType);
			
			UINT32 count = 0;
			hr = pType->LockStore();
			hr = pType->GetCount(&count);
			
			for(UINT32 j=0; j<count; j++)
			{
				//cout << i << "," << j << endl;
				this->ParseFormat(pType, j, metaDataOut);
			}
			hr = pType->UnlockStore();

			SafeRelease(&pType);
			PyList_Append(out, metaDataOut);

		}
		SafeRelease(&pPD);
		SafeRelease(&pSD);
		SafeRelease(&pHandler);
		return out;
	}

	void SetMediaType(PyObject *sourceId, unsigned long dwFormatIndex)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		IMFMediaSource *pSource = this->GetSource(sourceId);

		IMFPresentationDescriptor *pPD = NULL;
		IMFStreamDescriptor *pSD = NULL;
		IMFMediaTypeHandler *pHandler = NULL;
		IMFMediaType *pType = NULL;
		
		HRESULT hr = pSource->CreatePresentationDescriptor(&pPD);
		BOOL fSelected;
		hr = pPD->GetStreamDescriptorByIndex(0, &fSelected, &pSD);
		hr = pSD->GetMediaTypeHandler(&pHandler);
		hr = pHandler->GetMediaTypeByIndex((DWORD)dwFormatIndex, &pType);
		hr = pHandler->SetCurrentMediaType(pType);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pPD);
			SafeRelease(&pSD);
			SafeRelease(&pHandler);
			SafeRelease(&pType);
			throw runtime_error("SetCurrentMediaType failed");
		}

		SafeRelease(&pPD);
		SafeRelease(&pSD);
		SafeRelease(&pHandler);
		SafeRelease(&pType);
	}

	PyObject* ProcessSamples(PyObject *sourceId)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");
		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';

		//Check if reader is ready
		map<wstring, IMFSourceReader*>::iterator it = this->readerList.find(w);
		if(it == this->readerList.end())
		{
			throw std::runtime_error("Reader not ready for this source");
		}

		IMFSourceReader *pReader = it->second;
		HRESULT hr = S_OK;
		IMFSample *pSample = NULL;
		int camAsyncMode = this->asyncMode[w];

		DWORD streamIndex=0, flags=0;
		LONGLONG llTimeStamp=0;

		if(camAsyncMode)
		{
			class SourceReaderCB* pCallback = this->readerCallbacks[w];
			if(!pCallback->GetPending())
			{
				hr = pReader->ReadSample(
					MF_SOURCE_READER_ANY_STREAM,    // Stream index.
					0, NULL, NULL, NULL, NULL
					);
				pCallback->SetPending();
			}

			HRESULT hrStatus = S_OK;
			DWORD dwStreamIndex = 0;
			DWORD dwStreamFlags = 0; 
			LONGLONG llTimestamp = 0;
			char *frame = NULL;
			DWORD buffLen = 0;

			int found = pCallback->GetFrame(&hrStatus, &dwStreamIndex,
				&dwStreamFlags, &llTimestamp, &frame, &buffLen);

			//cout << (long) frame << "," << buffLen << endl;
			if(found)
			{
				assert((frame == NULL) == (buffLen == 0));
				PyObject* out = StaticObjToPythonObj(pReader, 
					streamIndex, 
					flags, 
					llTimeStamp, 
					frame, buffLen);

				//Set meta data in output object
				IMFMediaType *pCurrentType = NULL;
				LONG plStride = 0;
				GUID majorType=GUID_NULL, subType=GUID_NULL;
				UINT32 width = 0;
				UINT32 height = 0;

				HRESULT hr = pReader->GetCurrentMediaType(streamIndex, &pCurrentType);
				if(!SUCCEEDED(hr)) cout << "Error 3\n";
				BOOL isComp = FALSE;
				hr = pCurrentType->IsCompressedFormat(&isComp);
				PyDict_SetItemString(out, "isCompressed", PyBool_FromLong(isComp));
				hr = pCurrentType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
				LPCWSTR typePtr = GetGUIDNameConst(majorType);
				if(!SUCCEEDED(hr)) cout << "Error 4\n";
				hr = pCurrentType->GetGUID(MF_MT_SUBTYPE, &subType);
				if(!SUCCEEDED(hr)) cout << "Error 5\n";
				int isVideo = (majorType==MFMediaType_Video);
				if(isVideo)
				{
					GetDefaultStride(pCurrentType, &plStride);
					hr = MFGetAttributeSize(pCurrentType, MF_MT_FRAME_SIZE, &width, &height);
					if(!SUCCEEDED(hr)) cout << "Error 20\n";
				}

				LPCWSTR subTypePtr = GetGUIDNameConst(subType);
				//if(subTypePtr!=0) wcout << "subtype\t" << subTypePtr << "\n";

				PyDict_SetItemString(out, "isCompressed", PyBool_FromLong(isComp));
				if(typePtr!=NULL) PyDict_SetItemString(out, "type", PyUnicode_FromWideChar(typePtr, wcslen(typePtr)));
				if(subTypePtr!=NULL) PyDict_SetItemString(out, "subtype", PyUnicode_FromWideChar(subTypePtr, wcslen(subTypePtr)));
				if(!isComp) PyDict_SetItemString(out, "stride", PyInt_FromLong(plStride));
				PyDict_SetItemString(out, "width", PyInt_FromLong(width));
				PyDict_SetItemString(out, "height", PyInt_FromLong(height));

				delete [] frame;
				return out;
			}
			else
				return PyDict_New();
		}
		else
		{
			hr = pReader->ReadSample(
				MF_SOURCE_READER_ANY_STREAM,    // Stream index.
				0,                              // Flags.
				&streamIndex,                   // Receives the actual stream index. 
				&flags,                         // Receives status flags.
				&llTimeStamp,                   // Receives the time stamp.
				&pSample                        // Receives the sample or NULL.
				);
		}

		if (FAILED(hr))
		{
			return PyDict_New();
		}

		if(pSample)
		{
			//PyObject* out = SampleToPythonObj(pReader, streamIndex, flags, llTimeStamp, pSample);
			pSample->Release();
			return PyDict_New();
		}

		if(pSample) pSample->Release();
		return PyDict_New();
	}

	int FindSourceWithId(PyObject *sourceId)
	{
		int outIndex = -1;
		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");

		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';

		IMFActivate **ppDevices = NULL;
		int count = EnumDevices(&ppDevices);

		//For each device
		for(int i=0; i<count; i++)
		{
			IMFActivate *pActivate = ppDevices[i];

			wchar_t *symbolicLink = NULL;
			HRESULT hr = pActivate->GetAllocatedString(
				MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK,
				&symbolicLink,
				NULL
				);
			if(!SUCCEEDED(hr))
			{
				SafeRelease(ppDevices);
				CoTaskMemFree(symbolicLink);
				throw std::runtime_error("GetAllocatedString failed");
			}

			if(wcscmp(symbolicLink, w)==0)
			{
				outIndex = i;
				i = count;
			}

			CoTaskMemFree(symbolicLink);
		}

		SafeRelease(ppDevices);
		return outIndex;
	}

	IMFMediaSource *GetSource(PyObject *sourceId)
	{
		//Check if source is already available
		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");
		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';
		map<wstring, IMFMediaSource*>::iterator it = this->sourceList.find(w);
		if(it != this->sourceList.end())
		{
			return it->second;
		}

		//Open a new source
		IMFActivate **ppDevices = NULL;

		int sourceNum = FindSourceWithId(sourceId);
		if (sourceNum < 0)
			throw std::runtime_error("Source id not found");

		int count = EnumDevices(&ppDevices);
		IMFActivate *pActivate = ppDevices[sourceNum];
		
		IMFMediaSource *source = NULL;
		HRESULT hr = pActivate->ActivateObject(
			__uuidof(IMFMediaSource),
			(void**)&source
			);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(ppDevices);
			throw std::runtime_error("ActivateObject failed");
		}

		this->sourceList[w] = source;

		SafeRelease(ppDevices);
		return source;
	}
	
	int IsCameraRunning(PyObject *sourceId)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");
		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';

		//Check if reader is already available
		map<wstring, IMFSourceReader*>::iterator it = this->readerList.find(w);
		return it != this->readerList.end();
	}

	void StartCamera(PyObject *sourceId, int blocking = 0)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");
		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';

		//Check if reader is already available
		map<wstring, IMFSourceReader*>::iterator it = this->readerList.find(w);
		if(it != this->readerList.end())
		{
			throw std::runtime_error("Camera has already started");
		}

		//Create reader
		IMFAttributes *pAttributes = NULL;
		HRESULT hr = MFCreateAttributes(&pAttributes, 1);
		if(!SUCCEEDED(hr))
			throw std::runtime_error("MFCreateAttributes failed");
		
		IMFMediaSource *source = this->GetSource(sourceId);

		//Set attributes for reader
		this->asyncMode[w] = !blocking;
		SourceReaderCB *pCallback = new SourceReaderCB();
		this->readerCallbacks[w] = pCallback;
		if(!blocking)
		{
			hr = pAttributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, pCallback);
		}

		IMFSourceReader *reader = NULL;
		hr = MFCreateSourceReaderFromMediaSource(source, pAttributes, &reader);
		if(!SUCCEEDED(hr))
		{
			SafeRelease(&pAttributes);
			throw std::runtime_error("MFCreateSourceReaderFromMediaSource failed");
		}

		this->readerList[w] = reader;

		SafeRelease(&pAttributes);
	}

	void StopCamera(PyObject *sourceId)
	{
		if(!this->initDone)
			throw runtime_error("Media Foundation init not done");

		if(!PyUnicode_CheckExact(sourceId))
			throw std::runtime_error("Argument must be a Unicode object");
		wchar_t w[MAX_DEVICE_ID_LEN];
		PyUnicode_AsWideChar((PyUnicodeObject *)sourceId, w, MAX_DEVICE_ID_LEN);
		w[MAX_DEVICE_ID_LEN-1] = L'\0';

		//Check if reader is already available
		map<wstring, IMFSourceReader*>::iterator it = this->readerList.find(w);
		if(it != this->readerList.end())
		{
			//Shut down reader
			SafeRelease(&it->second);

			this->readerList.erase(it);
		}

		//Remove asyncMode flag
		map<wstring, int>::iterator it2 = this->asyncMode.find(w);
		if(it2 != this->asyncMode.end())
			this->asyncMode.erase(it2);

		//Remove reader callback
		//map<wstring, SourceReaderCB*>::iterator it3 = this->readerCallbacks.find(w);
		//if(it3 != this->readerCallbacks.end())
		//	this->readerCallbacks.erase(it3);

		//Check if source is already available
		map<wstring, IMFMediaSource*>::iterator its = this->sourceList.find(w);
		if(its != this->sourceList.end())
		{
			//Shut down source
			SafeRelease(&its->second);

			this->sourceList.erase(its);
		}
	}

};

BOOST_PYTHON_MODULE(wmfbase)
{
    using namespace boost::python;

	def("DecodeYuy2ToPilImage", DecodeYuy2ToPilImage);

	class_<MediaFoundation>("MediaFoundation")
		.def("Init", &MediaFoundation::Init)
		.def("DeInit", &MediaFoundation::DeInit)
		.def("ListDevices", &MediaFoundation::ListDevices)
		.def("StartCamera", &MediaFoundation::StartCamera)
		.def("ProcessSamples", &MediaFoundation::ProcessSamples)
		.def("EnumerateMediaTypes", &MediaFoundation::EnumerateMediaTypes)
		.def("SetMediaType", &MediaFoundation::SetMediaType)
		.def("IsCameraRunning", &MediaFoundation::IsCameraRunning)
		.def("StopCamera", &MediaFoundation::StopCamera)
	;
}
