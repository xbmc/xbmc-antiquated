#include "../../stdafx.h"
#include "APECodec.h"
#include "../../APEv2Tag.h"

APECodec::APECodec()
{
  ZeroMemory(&m_dll, sizeof(APEdll));
  m_handle = NULL;
  m_SampleRate = 0;
  m_Channels = 0;
  m_BitsPerSample = 0;
  // dll stuff
  m_bDllLoaded = false;
  m_pDll = NULL;
}

APECodec::~APECodec()
{
  DeInit();
  CSectionLoader::UnloadDLL(APE_DLL);
}

bool APECodec::Init(const CStdString &strFile, unsigned int filecache)
{
  if (!LoadDLL())
    return false;

  int nRetVal = 0;
  m_handle = m_dll.Create(strFile.c_str(), &nRetVal);
	if (m_handle == NULL)
	{
		CLog::Log(LOGERROR, "Error opening APE file (error code: %d)", nRetVal);
		return false;
	}

  // Calculate the number of bytes per block
  m_SampleRate = m_dll.GetInfo(m_handle, APE_INFO_SAMPLE_RATE, 0, 0);
  m_BitsPerSample = m_dll.GetInfo(m_handle, APE_INFO_BITS_PER_SAMPLE, 0, 0);
  m_Channels = m_dll.GetInfo(m_handle, APE_INFO_CHANNELS, 0, 0);
  m_BytesPerBlock = m_BitsPerSample * m_Channels / 8;
  m_TotalTime = (__int64)m_dll.GetInfo(m_handle, APE_INFO_LENGTH_MS, 0, 0);

  // Get the replay gain data
  IAPETag *pTag = (IAPETag *)m_dll.GetInfo(m_handle, APE_INFO_TAG, 0, 0);
  if (pTag)
  {
    CAPEv2Tag tag;
    tag.GetReplayGainFromTag(pTag);
    m_replayGain = tag.GetReplayGain();
    // Don't delete the tag - it's deleted by the dll in Destroy()
  }

  return true;
}

void APECodec::DeInit()
{
  if (m_handle)
  {
	  m_dll.Destroy(m_handle);
    m_handle = NULL;
  }
}

__int64 APECodec::Seek(__int64 iSeekTime)
{
  // calculate our offset in blocks
  int iOffset = (int)((double)iSeekTime / 1000.0 * m_SampleRate);
  m_dll.Seek(m_handle, iOffset);
  return iSeekTime;
}

#define BLOCK_READ_SIZE 588*4  // read 4 frames of samples at a time

int APECodec::ReadPCM(BYTE *pBuffer, int size, int *actualsize)
{
  DWORD time = timeGetTime();
  int sizeToRead = min(size / m_BytesPerBlock, BLOCK_READ_SIZE);
  int iRetVal = m_dll.GetData(m_handle, (char *)pBuffer, sizeToRead, actualsize);
  *actualsize *= m_BytesPerBlock;
  if (iRetVal)
  {
    CLog::Log(LOGERROR, "APECodec: Read error %i", iRetVal);
    return READ_ERROR;
  }
  if (!*actualsize)
    return READ_EOF;
  return READ_SUCCESS;
}

bool APECodec::LoadDLL()
{
  if (m_bDllLoaded)
    return true;
  m_pDll = CSectionLoader::LoadDLL(APE_DLL);
  if (!m_pDll)
  {
    CLog::Log(LOGERROR, "APECodec: Unable to load dll %s", APE_DLL);
    return false;
  }
  // get handle to the functions in the dll
  m_pDll->ResolveExport("GetVersionNumber", (void**)&m_dll.GetVersionNumber);
  m_pDll->ResolveExport("c_APEDecompress_Create", (void**)&m_dll.Create);
  m_pDll->ResolveExport("c_APEDecompress_Destroy", (void**)&m_dll.Destroy);
  m_pDll->ResolveExport("c_APEDecompress_GetData", (void**)&m_dll.GetData);
  m_pDll->ResolveExport("c_APEDecompress_Seek", (void**)&m_dll.Seek);
  m_pDll->ResolveExport("c_APEDecompress_GetInfo", (void**)&m_dll.GetInfo);

  // Check resolves + version number
  if (!m_dll.GetVersionNumber || !m_dll.Create || !m_dll.Destroy ||
      !m_dll.GetData || !m_dll.Seek || !m_dll.GetInfo || m_dll.GetVersionNumber() != MAC_VERSION_NUMBER)
  {
    CLog::Log(LOGERROR, "APECodec: Unable to load our dll %s", APE_DLL);
    delete m_pDll;
    m_pDll = NULL;
    return false;
  }

  m_bDllLoaded = true;
  return true;
}

bool APECodec::HandlesType(const char *type)
{
  return ( strcmp(type, "ape") == 0 || strcmp(type, "mac") == 0 );
}